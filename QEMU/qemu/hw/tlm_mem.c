/*
 * QEMU device to interface with external SystemC simulators.
 *
 * Copyright (c) 2011 Edgar E. Iglesias.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "hw/sysbus.h"
#include "sysemu/sysemu.h"
#include "hw/qdev-addr.h"
#include "hw/ptimer.h"

#include "exec/gdbstub.h"
#include "tlm.h"

extern int tlm_debug;

#define TYPE_TLM_MEMORY "tlm,memory"
#define TLM_MEMORY(obj) \
    OBJECT_CHECK(struct TLMMemory, (obj), TYPE_TLM_MEMORY)

/* just quick hack to compile this file. FIXME */
uint64_t qemu_icount;

struct TLMMemory_base {
    uint64_t base_addr;
    uint64_t size;
    MemoryRegion iomem;
    struct tlmu_dmi dmi;
    int is_ram;
    const char *name;
};


/* There is one of these instantiated per memory/IO area. The first one
   is the only one with valid IRQ connections, the rest are only meant to
   be used for RAM maps.  */
struct TLMMemory {
    SysBusDevice busdev;
    struct TLMMemory_base info;
    void *cpu_env; //actually its type is CPUArchState *;

    QEMUBH *sync_bh;
    QEMUBH *irq_bh;
    ptimer_state *sync_ptimer;
    qemu_irq *cpu_irq;

    uint64_t sync_period_ns;
    uint32_t pending_irq[16]; /* max 512 irqs.  */
    uint32_t nr_irq;
    void *irq_vector;
};

struct TLMRegisterRamEntry {
    struct TLMMemory_base info;
    struct TLMRegisterRamEntry *next;
    int try_turbo_mode;
};

static struct TLMRegisterRamEntry *tlm_register_ram_entries = NULL;
struct TLMMemory *main_tlmdev = NULL;

void notdirty_mem_wr(hwaddr ram_addr, int len);

static void tlm_write_irq(struct tlmu_irq *qirq)
{
    assert(main_tlmdev);

    if ((qirq->addr / 4) > main_tlmdev->nr_irq) {
       /* This is a write to the vector.  */
       if (main_tlmdev->irq_vector) {
           * (uint32_t *) main_tlmdev->irq_vector = qirq->data;
       }
    }

    main_tlmdev->pending_irq[qirq->addr / 4] = qirq->data;
    qemu_bh_schedule(main_tlmdev->irq_bh);
}

int tlm_bus_access(int rw, uint64_t addr, void *data, int len)
{
    const int r = cpu_physical_memory_rw(addr, data, len, rw);
    return r;
}

void tlm_bus_access_dbg(int rw, uint64_t addr, void *data, int len)
{
    cpu_physical_memory_rw_debug(addr, data, len, rw);
}

int tlm_get_dmi_ptr(struct tlmu_dmi *dmi)
{
    hwaddr addr;
    int len;

    assert(dmi);
    addr = dmi->base;
    dmi->ptr = qemu_map_paddr_to_host(&addr, &len);
    dmi->base = addr;
    dmi->size = len;
    dmi->prot = TLMU_DMI_PROT_READ | TLMU_DMI_PROT_WRITE;
    dmi->read_latency = 0;
    dmi->write_latency = 0;
    return dmi->ptr != NULL;
}

static inline
int dmi_check_flags(struct TLMMemory *s, int flags) {
	return (s->info.dmi.prot & flags) == flags;
}

/*
 * Check if this particular TLMMemory needs to get it's dmi mappings
 * invalidated. If so, invalidate them.
 */
static void tlm_check_invalidate_dmi(struct TLMMemory_base *info,
                                     uint64_t start, uint64_t end)
{
    if (start > info->base_addr && start < (info->base_addr + info->size)) {
        info->dmi.ptr = NULL;
        info->dmi.prot = 0;
    }
}

/*
 * Walk the list of TLMMemory areas and if needed, invalidate their dmi
 * mappings.
 */
static void tlm_invalidate_dmi(struct tlmu_dmi *dmi)
{
    const uint64_t start = dmi->base;
    const uint64_t end = dmi->base + dmi->size;
    struct TLMRegisterRamEntry *ram;
    for(ram = tlm_register_ram_entries; ram; ram = ram->next){
        tlm_check_invalidate_dmi(&ram->info, start, end);
    }

    /* Also check the main dev.  */
    tlm_check_invalidate_dmi(&main_tlmdev->info, start, end);
}

static void tlm_try_dmi(struct TLMMemory_base *info, uint64_t addr, int len)
{
    if (tlm_get_dmi_ptr_cb) {
        tlm_get_dmi_ptr_cb(tlm_opaque, addr, &info->dmi);
        /* If we got a readable aligned ptr, make it a fast one!  */
        if (info->dmi.ptr && (info->dmi.prot & TLMU_DMI_PROT_READ)) {
            const intptr_t p = (intptr_t) info->dmi.ptr;
            if (info->dmi.base == info->base_addr
                    && info->dmi.size == info->size
                    && (p & 0x3) == 0) {
                info->dmi.prot |= TLMU_DMI_PROT_FAST;
            }
        }
    }
}

static
int dmi_is_allowed(struct TLMMemory_base *info, int flags, uint64_t addr, int len)
{
    if (info->dmi.ptr && info->dmi.prot & flags) {
        if (addr >= info->dmi.base
            && (addr + len - 1) <= (info->dmi.base + info->dmi.size)) {
            return 1;
        }
    }
    return 0;
}

static inline hwaddr adjust_address_for_endianness(hwaddr orig_addr, unsigned int len){
#if defined(TARGET_WORDS_BIGENDIAN) == defined(HOST_WORDS_BIGENDIAN)
    return orig_addr;
#else
#if TARGET_LONG_SIZE == 4 /* FIXME:TARGET_LONG_SIZE is word size ? FIXME:only word == 32bit is implemented */
    assert(!(orig_addr % len)); /* FIXME:only aligned access is implemented */
    switch(len & 0x3){
        case 0: /* word access */
            return orig_addr;
        case 1:return orig_addr ^ 0x3;
        case 2:return orig_addr ^ 0x2;
        case 3:assert(!"length 3 is not supported");
    }
    assert(!"Never comes here");
#endif
#endif
}

static inline uint64_t tlm_dbg_read(void *opaque, hwaddr addr, unsigned int len){
    struct TLMMemory_base *const info = opaque;
    const uint64_t eaddr = info->base_addr + adjust_address_for_endianness(addr, len);
    uint64_t r = 0;
    const int64_t clk = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    if (tlm_debug) { printf("tlm_dbg_read(%p, %08llX, %d)\n", opaque, (long long)eaddr, len); }
    tlm_bus_access_dbg_cb(tlm_opaque, clk, 0, eaddr, &r, len);
    return r;
}

static inline void tlm_dbg_write(void *opaque, hwaddr addr, uint64_t value, unsigned int len){
    struct TLMMemory_base *const info = opaque;
    const uint64_t eaddr = info->base_addr + adjust_address_for_endianness(addr, len);
    const int64_t clk = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    if (tlm_debug) { printf("tlm_dbg_write(%p, %08llX, %08llX, %d)\n", opaque, (long long)eaddr, (long long)value, len); }
    tlm_bus_access_dbg_cb(tlm_opaque, clk, 1, eaddr, &value, len);
}

static inline
uint64_t tlm_read(void *opaque, hwaddr addr, unsigned int len)
{
    struct TLMMemory_base *const info = opaque;
    uint64_t r = 0;
    const uint64_t eaddr = info->base_addr + adjust_address_for_endianness(addr, len);
    int64_t clk;
    int dmi_supported;

    if (tlm_debug) { printf("tlm_read(%p, %08llX, %d)\n", opaque, (long long)eaddr, len); }
    if (dmi_is_allowed(info, TLMU_DMI_PROT_READ, eaddr, len)) {
        int offset;
        char *p = info->dmi.ptr;

        offset = eaddr - info->dmi.base;
        p += offset;
        memcpy(&r, p, len);
        qemu_icount += info->dmi.read_latency * len;
        if (!info->is_ram) {
            clk = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
            tlm_sync(tlm_opaque, clk);
        }
        return r;
    }

    clk = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    dmi_supported = tlm_bus_access_cb(tlm_opaque, clk, 0, eaddr, &r, len);
    if (dmi_supported && !info->dmi.prot) {
        tlm_try_dmi(info, eaddr, len);
    }

    if (tlm_debug) { printf("%s: addr=%lx r=%lx len=%d)\n", __func__, eaddr, r, len); }
    return r;
}

static inline void
tlm_write(void *opaque, hwaddr addr, uint64_t value, unsigned int len)
{
    struct TLMMemory_base *const info = opaque;
    const uint64_t eaddr = info->base_addr + adjust_address_for_endianness(addr, len);
    int64_t clk;
    int dmi_supported;

    if (tlm_debug) { printf("tlm_write(%p, %08llX, %08llX, %d)\n", opaque, (long long)eaddr, (long long)value, len); }

    if (info->is_ram) {
        //notdirty_mem_wr(eaddr, len); //FIXME just to compile
    }

    if (dmi_is_allowed(info, TLMU_DMI_PROT_WRITE, eaddr, len)) {
        int offset;
        char *p = info->dmi.ptr;

        offset = eaddr - info->dmi.base;
        p += offset;
        memcpy(p, &value, len);
        qemu_icount += info->dmi.write_latency * len;
        if (!info->is_ram) {
            clk = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
            tlm_sync(tlm_opaque, clk);
        }
        return;
    }

    clk = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    dmi_supported = tlm_bus_access_cb(tlm_opaque, clk, 1, eaddr, &value, len);
    if (dmi_supported && !info->dmi.prot) {
        tlm_try_dmi(info, eaddr, len);
    }
}

static const MemoryRegionOps tlm_mem_ops[2] = {
    {
        .read = tlm_read,
        .write = tlm_write,
        .endianness = DEVICE_NATIVE_ENDIAN
    },
    {
        .read = tlm_dbg_read,
        .write = tlm_dbg_write,
        .endianness = DEVICE_NATIVE_ENDIAN
    }
};


static void update_irq(void *opaque)
{
    struct TLMMemory *s = opaque;
    int i;

    for (i = 0; i < s->nr_irq; i++) {
        int regnr = i / 32;
        int bitnr = i & 0x1f;
        uint32_t data;
        int level;

        data = s->pending_irq[regnr];
        level = !!(data & (1 << bitnr));
        qemu_set_irq(s->cpu_irq[i], level);
    }
}

static void timer_hit(void *opaque)
{
    struct TLMMemory *s = opaque;
    cpu_interrupt(s->cpu_env, CPU_INTERRUPT_EXITTB);
}

void tlm_notify_event(enum tlmu_event ev, void *d)
{
    CPUArchState *env;

    assert(main_tlmdev);
    env = main_tlmdev->cpu_env;

    switch (ev) {
        case TLMU_TLM_EVENT_SYNC:
            qemu_notify_event();
            break;
        case TLMU_TLM_EVENT_WAKE:
            CPU(env)->halted = 0;
            cpu_reset_interrupt(CPU(env), CPU_INTERRUPT_HALT);
            break;
        case TLMU_TLM_EVENT_SLEEP:
            cpu_interrupt(CPU(env), CPU_INTERRUPT_HALT);
            break;
        case TLMU_TLM_EVENT_IRQ:
            tlm_write_irq(d);
            break;
        case TLMU_TLM_EVENT_INVALIDATE_DMI:
            tlm_invalidate_dmi(d);
            break;
        case TLMU_TLM_EVENT_RESET:
            qemu_system_reset_request();
            break;
        case TLMU_TLM_EVENT_DEBUG_BREAK:
            if (current_cpu && gdbserver_has_client()) {
              cpu_interrupt(current_cpu, CPU_INTERRUPT_DEBUG);
            }
            break;
        default:
            break;
    }
}

static int tlm_memory_init(SysBusDevice *dev)
{
    struct TLMMemory *const s = TLM_MEMORY(dev);
    int i;

    if (s->nr_irq) {
        if (s->nr_irq > (sizeof (s->pending_irq) * 8)) {
            printf("%s: Failed: to many irqs %d!\n", __func__, s->nr_irq);
            return 1;
        }
        s->cpu_irq = g_malloc0(s->nr_irq * sizeof (*s->cpu_irq));
        for (i = 0; i < s->nr_irq; i++) {
            sysbus_init_irq(dev, &s->cpu_irq[i]);
        }
    }

    s->irq_bh = qemu_bh_new(update_irq, s);
    s->sync_bh = qemu_bh_new(timer_hit, s);
    s->sync_ptimer = ptimer_init(s->sync_bh);
    if (s->sync_period_ns) {
        ptimer_set_period(s->sync_ptimer, s->sync_period_ns / 10);
        ptimer_set_limit(s->sync_ptimer, 10, 1);
        ptimer_run(s->sync_ptimer, 0);
    }

    s->info.name = "tlm_memory";
    memory_region_init_io(&s->info.iomem, OBJECT(s), tlm_mem_ops, &s->info, s->info.name, s->info.size);
    sysbus_init_mmio(dev, &s->info.iomem);

    /* Register the main tlm dev.  Used for interrupts.  */
    main_tlmdev = s;
    if (tlm_debug) { printf("tlm_memory_init() called %p\n", main_tlmdev); }
    return 0;
}

static Property tlm_mem_props[] = {
    DEFINE_PROP_UINT64("base_addr", struct TLMMemory, info.base_addr, 0),
    DEFINE_PROP_UINT64("size", struct TLMMemory, info.size, 0),
    DEFINE_PROP_PTR("cpu_env", struct TLMMemory, cpu_env),
    DEFINE_PROP_UINT64("sync_period_ns", struct TLMMemory, sync_period_ns, 0),
    DEFINE_PROP_UINT32("nr_irq", struct TLMMemory, nr_irq, 0),
    DEFINE_PROP_PTR("irq_vector", struct TLMMemory, irq_vector),
    DEFINE_PROP_END_OF_LIST(),
};

static void tlm_memory_class_init(ObjectClass *klass, void *data){
    DeviceClass *const dc = DEVICE_CLASS(klass);
    SysBusDeviceClass *const k = SYS_BUS_DEVICE_CLASS(klass);
    k->init = tlm_memory_init;
    dc->props = tlm_mem_props;
}


static void tlm_memory_register_type(void){
    static const TypeInfo tlm_memory_type_info = {
        .name = TYPE_TLM_MEMORY,
        .parent = TYPE_SYS_BUS_DEVICE,
        .instance_size = sizeof(struct TLMMemory),
        .class_init = tlm_memory_class_init,
    };
    type_register_static(&tlm_memory_type_info);
}

type_init(tlm_memory_register_type)


static void map_ram(struct TLMRegisterRamEntry *ram)
{
    if (tlm_debug) {
        printf("map_ram(%p:%s) base:0x%08llX size:0x%08llX called\n",
            ram, ram->info.name, (long long)ram->info.base_addr, (long long)ram->info.size);
    }
    tlm_try_dmi(&ram->info, ram->info.base_addr, ram->info.size);
    if(ram->try_turbo_mode && ram->info.dmi.ptr){//turbo mode
        if (tlm_debug) { printf("DMI is OK\n"); }
        memory_region_init_ram_ptr(&ram->info.iomem, NULL, ram->info.name, ram->info.size, ram->info.dmi.ptr);
    }
    else{
        if(ram->try_turbo_mode){
            fprintf(stderr,
                    "Warning: ram(%s) is expected to use turmo mode, "
                    "but DMI(r/w) is not available for this area. This area will be accessed via b_transport()\n",
                    ram->info.name);
        }
        memory_region_init_ram(&ram->info.iomem, NULL, ram->info.name, ram->info.size);
        ram->info.iomem.ops = tlm_mem_ops;
        ram->info.iomem.opaque = &ram->info;
    }
    vmstate_register_ram_global(&ram->info.iomem);
    memory_region_add_subregion(&main_tlmdev->info.iomem, ram->info.base_addr, &ram->info.iomem);
    memory_region_set_readonly(&ram->info.iomem, ram->info.is_ram ? false : true);
}

void tlm_map_ram(const char *name, uint64_t addr, uint64_t size, int rw, int try_turbo_mode)
{
    struct TLMRegisterRamEntry *const ram = g_malloc0(sizeof *ram);
    ram->info.name = g_strdup(name);
    ram->info.base_addr = addr;
    ram->info.size = size;
    ram->info.is_ram = rw;
    ram->try_turbo_mode = try_turbo_mode;

    /* Insert.  */
    ram->next = tlm_register_ram_entries;
    tlm_register_ram_entries = ram;
}

void tlm_register_rams(void)
{
    struct TLMRegisterRamEntry *ram;
    for(ram = tlm_register_ram_entries; ram; ram = ram->next){
        map_ram(ram);
    }
}


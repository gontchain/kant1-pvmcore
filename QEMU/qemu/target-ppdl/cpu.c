/*
 * QEMU PPDL CPU
 *
 * Copyright (c) 2014 Anatoly Kostin <kostintk@gmail.com>
 *                    Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 *
 */

#include "cpu.h"
#include "qemu-common.h"
#include "translate.h"

static void ppdl_cpu_set_pc(CPUState *cs, vaddr value)
{
    PPDLCPU *cpu = PPDL_CPU(cs);

    cpu->env.pc = value;
}

static bool ppdl_cpu_has_work(CPUState *cs)
{
    //[TODO] true or false
    return false;
    //return cs->interrupt_request & (CPU_INTERRUPT_HARD |
    //                                CPU_INTERRUPT_TIMER);
}

void ppdl_cpu_reset_reg(PPDLCPU *cpu);

static void ppdl_cpu_reset(CPUState *s)
{
    PPDLCPU *cpu = PPDL_CPU(s);
    PPDLCPUClass *occ = PPDL_CPU_GET_CLASS(cpu);

    occ->parent_reset(s);

#ifndef CONFIG_USER_ONLY
    memset(&cpu->env, 0, offsetof(CPUPPDLState, tlb));
#else
    memset(&cpu->env, 0, offsetof(CPUPPDLState, irq));
#endif

    tlb_flush(s, 1);
    /*tb_flush(&cpu->env);    FIXME: Do we need it?  */

    ppdl_cpu_reset_reg(cpu); // Reset PPDL Regs

#ifndef CONFIG_USER_ONLY
    cpu->env.picmr = 0x00000000;
    cpu->env.picsr = 0x00000000;

    cpu->env.ttmr  = 0x00000000;
    cpu->env.ttcr  = 0x00000000;
#endif
}

void ppdl_cpu_reset_reg(PPDLCPU *cpu)
{
    RESET(&cpu->env);
}

static void set_feature(PPDLCPU *cpu, int feature)
{
    cpu->feature |= feature;
}

static void ppdl_cpu_realizefn(DeviceState *dev, Error **errp)
{
    CPUState *cs = CPU(dev);
    PPDLCPUClass *occ = PPDL_CPU_GET_CLASS(dev);

    qemu_init_vcpu(cs);
    cpu_reset(cs);

    occ->parent_realize(dev, errp);
}

static void ppdl_cpu_initfn(Object *obj)
{
    CPUState *cs = CPU(obj);
    PPDLCPU *cpu = PPDL_CPU(obj);

    cs->env_ptr = &cpu->env;
    cpu_exec_init(&cpu->env);

#ifndef CONFIG_USER_ONLY
    cpu_ppdl_mmu_init(cpu);
#endif

    ppdl_translate_init();
}

/* CPU models */

static ObjectClass *ppdl_cpu_class_by_name(const char *cpu_model)
{
    ObjectClass *oc;
    char *typename;

    if (cpu_model == NULL) {
        return NULL;
    }

    typename = g_strdup_printf("%s-" TYPE_PPDL_CPU, cpu_model);
    oc = object_class_by_name(typename);
    g_free(typename);
    if (oc != NULL && (!object_class_dynamic_cast(oc, TYPE_PPDL_CPU) ||
                       object_class_is_abstract(oc))) {
        return NULL;
    }
    return oc;
}

static void ppdl_initfn(Object *obj)
{
    PPDLCPU *cpu = PPDL_CPU(obj);

    set_feature(cpu, PPDL_FEATURE_ONE);
}

typedef struct PPDLCPUInfo {
    const char *name;
    void (*initfn)(Object *obj);
} PPDLCPUInfo;

static const PPDLCPUInfo ppdl_cpus[] = {
#if defined(CONFIG_LINUX_USER)
    { .name = "ppdl",         .initfn = ppdl_initfn },
#else
    { .name = "ppdl0",      .initfn = ppdl_initfn },
#endif
};

static void ppdl_cpu_class_init(ObjectClass *oc, void *data)
{
    PPDLCPUClass *occ = PPDL_CPU_CLASS(oc);
    CPUClass *cc = CPU_CLASS(occ);
    DeviceClass *dc = DEVICE_CLASS(oc);

    occ->parent_realize = dc->realize;
    dc->realize = ppdl_cpu_realizefn;

    occ->parent_reset = cc->reset;
    cc->reset = ppdl_cpu_reset;

    cc->class_by_name = ppdl_cpu_class_by_name;
    cc->has_work = ppdl_cpu_has_work;
    //cc->do_interrupt = ppdl_cpu_do_interrupt;
    cc->dump_state = ppdl_cpu_dump_state;
    cc->set_pc = ppdl_cpu_set_pc;
    cc->gdb_read_register = ppdl_cpu_gdb_read_register;
    cc->gdb_write_register = ppdl_cpu_gdb_write_register;
    cc->gdb_read_fifo = ppdl_cpu_gdb_read_fifo;
    cc->gdb_info_fifo = ppdl_cpu_gdb_info_fifo;
    cc->gdb_write_fifo = ppdl_cpu_gdb_write_fifo;
#ifdef CONFIG_USER_ONLY
    cc->handle_mmu_fault = ppdl_cpu_handle_mmu_fault;
#else
    cc->do_unassigned_access = ppdl_cpu_unassigned_access;
    cc->get_phys_page_debug = ppdl_cpu_get_phys_page_debug;
    dc->vmsd = &vmstate_ppdl_cpu;
#endif
    cc->gdb_num_core_regs = 152;
}

static void cpu_register(const PPDLCPUInfo *info)
{
    TypeInfo type_info = {
        .parent = TYPE_PPDL_CPU,
        .instance_size = sizeof(PPDLCPU),
        .instance_init = info->initfn,
        .class_size = sizeof(PPDLCPUClass),
    };

    type_info.name = g_strdup_printf("%s-" TYPE_PPDL_CPU, info->name);
    type_register(&type_info);
    g_free((void *)type_info.name);
}

static const TypeInfo ppdl_cpu_type_info = {
    .name = TYPE_PPDL_CPU,
    .parent = TYPE_CPU,
    .instance_size = sizeof(PPDLCPU),
    .instance_init = ppdl_cpu_initfn,
    .abstract = false,
    .class_size = sizeof(PPDLCPUClass),
    .class_init = ppdl_cpu_class_init,
};

static void ppdl_cpu_register_types(void)
{
    int i;

    type_register_static(&ppdl_cpu_type_info);
    for (i = 0; i < ARRAY_SIZE(ppdl_cpus); i++) {
        cpu_register(&ppdl_cpus[i]);
    }
}

PPDLCPU *cpu_ppdl_init(const char *cpu_model)
{
    return PPDL_CPU(cpu_generic_init(TYPE_PPDL_CPU, cpu_model));
}

static gint ppdl_cpu_list_compare(gconstpointer a, gconstpointer b)
{
    ObjectClass *class_a = (ObjectClass *)a;
    ObjectClass *class_b = (ObjectClass *)b;
    const char *name_a, *name_b;

    name_a = object_class_get_name(class_a);
    name_b = object_class_get_name(class_b);
#if defined(CONFIG_SOFTMMU)
    if (strcmp(name_a, "any-" TYPE_PPDL_CPU) == 0) {
        return 1;
    } else if (strcmp(name_b, "any-" TYPE_PPDL_CPU) == 0) {
        return -1;
    } else {
        return strcmp(name_a, name_b);
    }
#else
    if (strcmp(name_a, "any") == 0) {
        return 1;
    } else if (strcmp(name_b, "any") == 0) {
        return -1;
    } else {
        return strcmp(name_a, name_b);
    }
#endif
}

static void ppdl_cpu_list_entry(gpointer data, gpointer user_data)
{
    ObjectClass *oc = data;
    CPUListState *s = user_data;
    const char *typename;
    char *name;

    typename = object_class_get_name(oc);
    if (!strcmp(typename, TYPE_PPDL_CPU))
        return;
    name = g_strndup(typename, strlen(typename) - strlen("-" TYPE_PPDL_CPU));
    (*s->cpu_fprintf)(s->file, "  %s\n",
                      name);
    g_free(name);
}

void cpu_ppdl_list(FILE *f, fprintf_function cpu_fprintf)
{
    CPUListState s = {
        .file = f,
        .cpu_fprintf = cpu_fprintf,
    };
    GSList *list;

    list = object_class_get_list(TYPE_PPDL_CPU, false);
    list = g_slist_sort(list, ppdl_cpu_list_compare);
    (*cpu_fprintf)(f, "Available CPUs:\n");
    g_slist_foreach(list, ppdl_cpu_list_entry, &s);
    g_slist_free(list);
}

uint64_t pd_lsh(uint64_t aVal, uint64_t aOffs)
{
    if(aOffs >= 64)
        return 0;
    else
        return aVal << aOffs;
}

uint64_t pd_rsh(uint64_t aVal, uint64_t aOffs)
{
    if(aOffs >= 64)
        return 0;
    else
        return aVal >> aOffs;
}

type_init(ppdl_cpu_register_types)

/*
 * QEMU machine for wrapping QEMU cpus as TLM initiators.
 *
 * Copyright (c) 2011 Edgar E. Iglesias, Axis Communications AB.
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
#include "net/net.h"
#include "hw/block/flash.h"
#include "hw/boards.h"
#include "sysemu/sysemu.h"
#include "exec/cpu_ldst.h"

#ifdef TARGET_CRIS
#include "target-cris/cpu.h"
#include "hw/cris/etraxfs.h"
#endif
#ifdef TARGET_ARM
#include "target-arm/cpu.h"
#include "hw/arm/arm.h"
#endif
#ifdef TARGET_PPDL
#include "target-ppdl/cpu.h"
#include "hw/ppdl/ppdl.h"
extern uint64_t elf_entry;
#endif

#include "hw/loader.h"
#include "elf.h"

#include "tlm.h"
#include "tlm_mem.h"

extern int tlm_debug;
uint64_t CPU_ID = -1;
CPUArchState *env_;

#define VIRT_TO_PHYS_ADDEND (0LL)

static uint64_t bootstrap_pc;

static void main_cpu_reset(void *opaque)
{
    CPUArchState *env = opaque;
    cpu_reset(ENV_GET_CPU(env));

#ifdef TARGET_CRIS
    env->pc = bootstrap_pc;
#elif defined(TARGET_MIPS)
    env->active_tc.PC = bootstrap_pc;
#elif defined(TARGET_ARM)
    // if (env->aarch64) {
    //     env->pc = bootstrap_pc;
    // } else {
        env->regs[15] = bootstrap_pc;
    // }
#elif defined(TARGET_OPENRISC)
    env->pc = bootstrap_pc;
#endif

    if (tlm_boot_state == TLMU_BOOT_SLEEPING) {
        cpu_interrupt(CPU(env), CPU_INTERRUPT_HALT);
    }
}

static uint64_t translate_kaddr(void *opaque, uint64_t addr)
{
#if defined(TARGET_PPDL)
    return addr*4;
#else
    return addr + VIRT_TO_PHYS_ADDEND;
#endif
}

static
void tlm_mach_init_common (ram_addr_t ram_size,
                       const char *kernel_filename, const char *kernel_cmdline,
                       const char *initrd_filename, const char *cpu_model)
{
    qemu_irq *cpu_irq;
    int kernel_size;
    int is_bigendian = 0; /* arm, mips, cris are little endian */

    /* init CPUs */
    if (cpu_model == NULL) {
        fprintf(stderr, "FATAL: CPU model not chosen.\n");
        exit(1);
    }

    env_ = cpu_init(cpu_model);

    if (!env_) {
        fprintf(stderr, "FATAL: Unable to create cpu %s env=%p\n", cpu_model, env_);
        exit(1);
    }
    qemu_register_reset(main_cpu_reset, env_);

#ifdef TARGET_CRIS
    cpu_irq = cris_pic_init_cpu(env_);
    tlm_map(env_, 0x0ULL, 0xffffffffULL,
            tlm_sync_period_ns, cpu_irq, 1, &env_->interrupt_vector);
#elif defined(TARGET_ARM)
    cpu_irq = arm_pic_init_cpu(arm_env_get_cpu(env_));
    tlm_map(env_, 0x0ULL, 0xffffffffULL,
            tlm_sync_period_ns, cpu_irq, 2, NULL);
#elif defined(TARGET_PPDL)
    cpu_irq = ppdl_pic_init_cpu(env_);
    tlm_map(env_, 0x0ULL, 0xffffffffULL,
            tlm_sync_period_ns, cpu_irq, 2, NULL);
#endif

    tlm_register_rams();

   if (kernel_filename) {
        uint64_t entry, low, high;

        kernel_size = load_elf(kernel_filename, translate_kaddr, NULL,
                               &entry, &low, &high, is_bigendian, ELF_MACHINE, 0);

        bootstrap_pc = entry;
        if (kernel_size < 0) {
            kernel_size = load_image_targphys(kernel_filename,
                                              tlm_image_load_base,
                                              tlm_image_load_size);
            low = bootstrap_pc = tlm_image_load_base;
            high = tlm_image_load_base + kernel_size;
        }

        if (kernel_size < 0) {
            fprintf(stderr, "Unable to open %s\n", kernel_filename);
            exit(1);
        }
#ifdef TARGET_PPDL
        elf_entry = entry;
#endif
    } else {
#ifdef TARGET_CRIS
        bootstrap_pc = 0x0;
#endif
#ifdef TARGET_ARM
        bootstrap_pc = 0x0;
#endif
    }
}

void tlm_set_cpu_id(uint64_t rank)
{
    CPU_ID = rank;
}

void tlm_mem_access(int rw, uint64_t addr, void *data, int len)
{
    uint64_t data_;
    if (rw) {
        data_ = *((uint64_t*)data);
        cpu_stq_data(env_, addr, data_);
    } else {
        data_ = cpu_ldl_data(env_, addr);
        memcpy(data, &data_, len);
    }
}

int tlm_free_system_memory(uint64_t holder)
{
    // [TODO] implement proc memory clean
    return 0;
}

static
void tlm_mach_init (MachineState *machine)
{
    tlm_mach_init_common(machine->ram_size, machine->kernel_filename, machine->kernel_cmdline,
                         machine->initrd_filename, machine->cpu_model);
}

static QEMUMachine tlm_mach_machine = {
    .name = "tlm-mach",
    .desc = "TLM Machine",
    .init = tlm_mach_init,
    .is_default = 1,
};

static void tlm_mach_machine_init(void)
{
    qemu_register_machine(&tlm_mach_machine);
}

machine_init(tlm_mach_machine_init);

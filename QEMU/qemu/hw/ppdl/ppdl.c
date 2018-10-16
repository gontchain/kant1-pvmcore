/*
 * QEMU model for ppdl machine.
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "hw/hw.h"
#include "hw/boards.h"
#include "elf.h"
#include "hw/char/serial.h"
#include "net/net.h"
#include "hw/loader.h"
#include "exec/address-spaces.h"
#include "sysemu/sysemu.h"
#include "hw/sysbus.h"
#include "sysemu/qtest.h"

#ifdef EVM
#   define KERNEL_LOAD_ADDR 0x0
#else
#   define KERNEL_LOAD_ADDR 0x100
#endif

uint64_t elf_entry = 0x0;

static void main_cpu_reset(void *opaque)
{
    PPDLCPU *cpu = opaque;

    cpu_reset(CPU(cpu));
}

static uint64_t translate_kaddr(void *opaque, uint64_t addr)
{
    return addr*4;
}

static
void ppdl_init(MachineState *machine)
{
    ram_addr_t ram_size = machine->ram_size;
    const char *cpu_model = machine->cpu_model;
    const char *kernel_filename = machine->kernel_filename;
    PPDLCPU *cpu = NULL;
    MemoryRegion *ram;
    long kernel_size;
    uint64_t _elf_entry;
    hwaddr entry;
    int n;

    if (!cpu_model) {
        cpu_model = "ppdl0";
    }

    for (n = 0; n < smp_cpus; n++) {
        cpu = cpu_ppdl_init(cpu_model);
        if (cpu == NULL) {
            break;
        }
        qemu_register_reset(main_cpu_reset, cpu);
        main_cpu_reset(cpu);
    }
    if (cpu == NULL) {
        fprintf(stderr, "Unable to find CPU definition!\n");
        exit(1);
    }

    ram = g_malloc(sizeof(*ram));
    memory_region_init_ram(ram, NULL, "ppdl.ram", ram_size);
    vmstate_register_ram_global(ram);
    memory_region_add_subregion(get_system_memory(), 0, ram);

    //cpu_openrisc_pic_init(cpu);
    //cpu_openrisc_clock_init(cpu);

    if (kernel_filename && !qtest_enabled()) {
        kernel_size = load_elf(kernel_filename, translate_kaddr, NULL,
                               &_elf_entry, NULL, NULL, 0, ELF_MACHINE, 1);
        entry = _elf_entry;
        if (kernel_size < 0) {
            kernel_size = load_uimage(kernel_filename,
                                      &entry, NULL, NULL);
        }
        if (kernel_size < 0) {
            kernel_size = load_image_targphys(kernel_filename,
                                              KERNEL_LOAD_ADDR,
                                              ram_size - KERNEL_LOAD_ADDR);
            entry = KERNEL_LOAD_ADDR;
        }

        if (kernel_size < 0) {
            fprintf(stderr, "QEMU: couldn't load the kernel '%s'\n",
                    kernel_filename);
            exit(1);
        }
        elf_entry = entry;
    }
}

static QEMUMachine ppdl_machine = {
    .name = "ppdl",
    .desc = "PPDL",
    .init = ppdl_init,
    .is_default = 1,
};

static void ppdl_machine_init(void)
{
    qemu_register_machine(&ppdl_machine);
}

machine_init(ppdl_machine_init);

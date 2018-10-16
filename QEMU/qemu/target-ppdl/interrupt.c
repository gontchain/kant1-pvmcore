/*
 * PPDL virtual CPU header.
 *
 * Copyright (c) 2014 Anatoly Kostin <kostintk@gmail.com>
 *
 * [TODO] Add some description
 */

#include "cpu.h"
#include "qemu-common.h"
#include "exec/gdbstub.h"
#include "qemu/host-utils.h"
#ifndef CONFIG_USER_ONLY
#include "hw/loader.h"
#endif

void ppdl_cpu_do_interrupt(CPUPPDLState *env)
{
}

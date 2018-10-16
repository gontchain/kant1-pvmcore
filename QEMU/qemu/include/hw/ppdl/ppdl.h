/*
 * Misc PPDL declarations
 *
 * Copyright (c) 2017 Alexander Gerasimov <samik.mechanic@gmail.com>
 *
 */

#include "hw/irq.h"

#ifndef PPDL_MISC_H
#define PPDL_MISC_H 1

qemu_irq *ppdl_pic_init_cpu(CPUPPDLState *env);

#endif
/*
 * QEMU CRIS CPU interrupt wrapper logic.
 *
 * Copyright (c) 2017 Alexander Gerasimov <samik.mechanic@gmail.com>
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

#include "hw/hw.h"
#include "target-ppdl/cpu.h"
#include "hw/ppdl/ppdl.h"

#define D(x)

static void ppdl_pic_cpu_handler(void *opaque, int irq, int level)
{
    CPUPPDLState *env = (CPUPPDLState *)opaque;
    int type = irq ? CPU_PPDL_INTERRUPT : CPU_INTERRUPT_HARD;

    if (level)
        cpu_interrupt(CPU(env), type);
    else
        cpu_reset_interrupt(CPU(env), type);
}

qemu_irq *ppdl_pic_init_cpu(CPUPPDLState *env)
{
    return qemu_allocate_irqs(ppdl_pic_cpu_handler, env, 2);
}

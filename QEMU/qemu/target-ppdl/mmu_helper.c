/*
 * PPDL virtual CPU header.
 *
 * Copyright (c) 2014 Anatoly Kostin <kostintk@gmail.com>
 *
 * [TODO] Add some description
 */

#include "cpu.h"
#include "exec/cpu_ldst.h"

#ifndef CONFIG_USER_ONLY

void tlb_fill(CPUState *cs, target_ulong addr, int is_write,
              int mmu_idx, uintptr_t retaddr)
{
    int ret;

    ret = ppdl_cpu_handle_mmu_fault(cs, addr, is_write, mmu_idx);

    if (ret) {
        if (retaddr) {
            /* now we have a real cpu fault.  */
            cpu_restore_state(cs, retaddr);
        }
        /* Raise Exception.  */
        cpu_loop_exit(cs);
    }
}
#endif

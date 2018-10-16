/*
 * PPDL virtual CPU header.
 *
 * Copyright (c) 2014 Anatoly Kostin <kostintk@gmail.com>
 *
 * [TODO] Add some description
 */


#include "hw/hw.h"
#include "hw/boards.h"

#if defined(CONFIG_LINUX_USER)
// [TODO] Add FIFOARR registers from XML file
static const VMStateDescription vmstate_env = {
    .name = "env",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(gr, CPUPPDLState, 8),
        VMSTATE_UINT32_ARRAY(ar, CPUPPDLState, 8),
        VMSTATE_UINT32(pswr, CPUPPDLState),
        VMSTATE_UINT32(pc, CPUPPDLState),
        VMSTATE_UINT32(gmicr, CPUPPDLState),
        VMSTATE_UINT64_ARRAY(dir, CPUPPDLState, 2),
        VMSTATE_UINT64_ARRAY(dor, CPUPPDLState, 2),
        VMSTATE_UINT32(lmicr, CPUPPDLState),
        VMSTATE_UINT32(nb1l, CPUPPDLState),
        VMSTATE_UINT32(nb1h, CPUPPDLState),
        VMSTATE_UINT32(sb1l, CPUPPDLState),
        VMSTATE_UINT32(sb1h, CPUPPDLState),
        VMSTATE_UINT32(intr, CPUPPDLState),
        VMSTATE_UINT32(f1crl, CPUPPDLState),
        VMSTATE_UINT32(f1crh, CPUPPDLState),
        VMSTATE_UINT32(f2crl, CPUPPDLState),
        VMSTATE_UINT32(f2crh, CPUPPDLState),
        VMSTATE_UINT32(pcr, CPUPPDLState),
        VMSTATE_UINT32(nulreg, CPUPPDLState),
        VMSTATE_UINT32(ld_pipe_sync, CPUPPDLState),
        VMSTATE_UINT32(vrl, CPUPPDLState),
        VMSTATE_UINT32(vrh, CPUPPDLState),
        VMSTATE_UINT32(nb2l, CPUPPDLState),
        VMSTATE_UINT32(nb2h, CPUPPDLState),
        VMSTATE_UINT32(sb2l, CPUPPDLState),
        VMSTATE_UINT32(sb2h, CPUPPDLState),
        VMSTATE_UINT32(LMCR0, CPUPPDLState),
        VMSTATE_UINT32(LMCR1, CPUPPDLState),
        VMSTATE_UINT32(GMCR0, CPUPPDLState),
        VMSTATE_UINT32(GMCR1, CPUPPDLState),
        VMSTATE_UINT32(LEMA, CPUPPDLState),
        VMSTATE_UINT32(ram_size, CPUPPDLState),
        VMSTATE_UINT32(GEMA, CPUPPDLState),
        VMSTATE_UINT32(LIMA, CPUPPDLState),
        VMSTATE_UINT32(GIMA, CPUPPDLState),
        VMSTATE_UINT8(IOP, CPUPPDLState),
        VMSTATE_UINT8(IOPCR, CPUPPDLState),
        VMSTATE_UINT32(DMAC0, CPUPPDLState),
        VMSTATE_UINT32(DMAC1, CPUPPDLState),
        VMSTATE_UINT32_ARRAY(T, CPUPPDLState, 2),
        VMSTATE_UINT32_ARRAY(TH, CPUPPDLState, 2),
        VMSTATE_UINT32(is_stop_fetch, CPUPPDLState),
        VMSTATE_UINT32(stage3, CPUPPDLState),
        VMSTATE_UINT32(stage_alu, CPUPPDLState),
        VMSTATE_UINT32(ipc, CPUPPDLState),
        VMSTATE_UINT8(pc_changed, CPUPPDLState),
        VMSTATE_UINT8(pc_init, CPUPPDLState),
        VMSTATE_UINT8(decoded, CPUPPDLState),
        VMSTATE_UINT8(num_words_in_ir, CPUPPDLState),
        VMSTATE_UINT8(ret_irq_cnt, CPUPPDLState),
        VMSTATE_UINT8(miss_null_inst, CPUPPDLState),
        VMSTATE_UINT64_ARRAY(woper, CPUPPDLState, 32),
        VMSTATE_UINT32(ftw_wtw_locker, CPUPPDLState),
        VMSTATE_UINT32(eear, CPUPPDLState),
        VMSTATE_END_OF_LIST()
    }
};
#endif

const VMStateDescription vmstate_ppdl_cpu = {
    .name = "cpu",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_CPU(),
#if defined(CONFIG_LINUX_USER)
        VMSTATE_STRUCT(env, PPDLCPU, 1, vmstate_env, CPUPPDLState),
#endif
        VMSTATE_END_OF_LIST()
    }
};

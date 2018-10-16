#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wformat-zero-length"

#include <stdio.h>
#include <stdint.h>
#include "qemu-common.h"

#define OPCODE(type) (type)ocode
#define BIN(type) *((type*)(bin))
// output 64-bits data
// low 32 bits of the 64-bits word
#define LO_WRD(val) (uint32_t)(val&((uint32_t)(-1)))
// hight 32 bits of the 64-bits word
#define HI_WRD(val) (uint32_t)(val>>32)

void NM6407_DisasmList_WriteRegsList(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0, gr0"); break;
  case 1: sprintf(out_buf, "ar1, gr1"); break;
  case 2: sprintf(out_buf, "ar2, gr2"); break;
  case 3: sprintf(out_buf, "ar3, gr3"); break;
  case 4: sprintf(out_buf, "ar4, gr4"); break;
  case 5: sprintf(out_buf, "ar5, gr5"); break;
  case 6: sprintf(out_buf, "ar6, gr6"); break;
  case 7: sprintf(out_buf, "ar7, gr7"); break;
  case 8: sprintf(out_buf, "ar0"); break;
  case 9: sprintf(out_buf, "ar1"); break;
  case 10: sprintf(out_buf, "ar2"); break;
  case 11: sprintf(out_buf, "ar3"); break;
  case 12: sprintf(out_buf, "ar4"); break;
  case 13: sprintf(out_buf, "ar5"); break;
  case 14: sprintf(out_buf, "ar6"); break;
  case 15: sprintf(out_buf, "ar7"); break;
  case 16: sprintf(out_buf, "gr0"); break;
  case 17: sprintf(out_buf, "gr1"); break;
  case 18: sprintf(out_buf, "gr2"); break;
  case 19: sprintf(out_buf, "gr3"); break;
  case 20: sprintf(out_buf, "gr4"); break;
  case 21: sprintf(out_buf, "gr5"); break;
  case 22: sprintf(out_buf, "gr6"); break;
  case 23: sprintf(out_buf, "gr7"); break;
  case 24: sprintf(out_buf, "pc,pswr"); break;
  case 25: sprintf(out_buf, "sir"); break;
  case 26: sprintf(out_buf, "INTRreset"); break;
  case 27: sprintf(out_buf, "VL"); break;
  case 28: sprintf(out_buf, "PC"); break;
  case 29: sprintf(out_buf, "PSWRset"); break;
  case 30: sprintf(out_buf, "PSWRreset"); break;
  case 31: sprintf(out_buf, "pswr"); break;
  case 32: sprintf(out_buf, "nb1"); break;
  case 33: sprintf(out_buf, "sb"); break;
  case 34: sprintf(out_buf, "f1cr"); break;
  case 35: sprintf(out_buf, "f2cr"); break;
  case 36: sprintf(out_buf, "vr"); break;
  case 40: sprintf(out_buf, "nb1l"); break;
  case 41: sprintf(out_buf, "sbl"); break;
  case 42: sprintf(out_buf, "f1crl"); break;
  case 43: sprintf(out_buf, "f2crl"); break;
  case 44: sprintf(out_buf, "vrl"); break;
  case 48: sprintf(out_buf, "nb1h"); break;
  case 49: sprintf(out_buf, "sbh"); break;
  case 50: sprintf(out_buf, "f1crH"); break;
  case 51: sprintf(out_buf, "f2crH"); break;
  case 52: sprintf(out_buf, "vrh"); break;
  case 57: sprintf(out_buf, "sir2"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_ReadRegsList(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0, gr0"); break;
  case 1: sprintf(out_buf, "ar1, gr1"); break;
  case 2: sprintf(out_buf, "ar2, gr2"); break;
  case 3: sprintf(out_buf, "ar3, gr3"); break;
  case 4: sprintf(out_buf, "ar4, gr4"); break;
  case 5: sprintf(out_buf, "ar5, gr5"); break;
  case 6: sprintf(out_buf, "ar6, gr6"); break;
  case 7: sprintf(out_buf, "ar7, gr7"); break;
  case 8: sprintf(out_buf, "ar0"); break;
  case 9: sprintf(out_buf, "ar1"); break;
  case 10: sprintf(out_buf, "ar2"); break;
  case 11: sprintf(out_buf, "ar3"); break;
  case 12: sprintf(out_buf, "ar4"); break;
  case 13: sprintf(out_buf, "ar5"); break;
  case 14: sprintf(out_buf, "ar6"); break;
  case 15: sprintf(out_buf, "ar7"); break;
  case 16: sprintf(out_buf, "gr0"); break;
  case 17: sprintf(out_buf, "gr1"); break;
  case 18: sprintf(out_buf, "gr2"); break;
  case 19: sprintf(out_buf, "gr3"); break;
  case 20: sprintf(out_buf, "gr4"); break;
  case 21: sprintf(out_buf, "gr5"); break;
  case 22: sprintf(out_buf, "gr6"); break;
  case 23: sprintf(out_buf, "gr7"); break;
  case 24: sprintf(out_buf, "pc, pswr"); break;
  case 25: sprintf(out_buf, "sir"); break;
  case 26: sprintf(out_buf, "INTRreset"); break;
  case 27: sprintf(out_buf, "VL"); break;
  case 28: sprintf(out_buf, "PC"); break;
  case 31: sprintf(out_buf, "pswr"); break;
  case 38: sprintf(out_buf, "intr"); break;
  case 39: sprintf(out_buf, "pc"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_WriteRegsListFP(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "fp0_flags"); break;
  case 1: sprintf(out_buf, "fp0_lmask"); break;
  case 2: sprintf(out_buf, "fp0_hmask"); break;
  case 3: sprintf(out_buf, "fp0_dmask"); break;
  case 4: sprintf(out_buf, "fp1_flags"); break;
  case 5: sprintf(out_buf, "fp1_lmask"); break;
  case 6: sprintf(out_buf, "fp1_hmask"); break;
  case 7: sprintf(out_buf, "fp1_dmask"); break;
  case 8: sprintf(out_buf, "fp2_flags"); break;
  case 9: sprintf(out_buf, "fp2_lmask"); break;
  case 10: sprintf(out_buf, "fp2_hmask"); break;
  case 11: sprintf(out_buf, "fp2_dmask"); break;
  case 12: sprintf(out_buf, "fp3_flags"); break;
  case 13: sprintf(out_buf, "fp3_lmask"); break;
  case 14: sprintf(out_buf, "fp3_hmask"); break;
  case 15: sprintf(out_buf, "fp3_dmask"); break;
  case 16: sprintf(out_buf, "FPIOIR"); break;
  case 17: sprintf(out_buf, "FPOIR"); break;
  case 18: sprintf(out_buf, "FPUIR"); break;
  case 19: sprintf(out_buf, "FPIIR"); break;
  case 20: sprintf(out_buf, "FPIEIR"); break;
  case 23: sprintf(out_buf, "FPIRR"); break;
  case 24: sprintf(out_buf, "fp_pack_exp"); break;
  case 25: sprintf(out_buf, "sir"); break;
  case 31: sprintf(out_buf, "FPCCR"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_ReadRegsListFP(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "fp0_flags"); break;
  case 1: sprintf(out_buf, "fp0_lmask"); break;
  case 2: sprintf(out_buf, "fp0_hmask"); break;
  case 3: sprintf(out_buf, "fp0_dmask"); break;
  case 4: sprintf(out_buf, "fp1_flags"); break;
  case 5: sprintf(out_buf, "fp1_lmask"); break;
  case 6: sprintf(out_buf, "fp1_hmask"); break;
  case 7: sprintf(out_buf, "fp1_dmask"); break;
  case 8: sprintf(out_buf, "fp2_flags"); break;
  case 9: sprintf(out_buf, "fp2_lmask"); break;
  case 10: sprintf(out_buf, "fp2_hmask"); break;
  case 11: sprintf(out_buf, "fp2_dmask"); break;
  case 12: sprintf(out_buf, "fp3_flags"); break;
  case 13: sprintf(out_buf, "fp3_lmask"); break;
  case 14: sprintf(out_buf, "fp3_hmask"); break;
  case 15: sprintf(out_buf, "fp3_dmask"); break;
  case 16: sprintf(out_buf, "FPIOIR"); break;
  case 17: sprintf(out_buf, "FPOIR"); break;
  case 18: sprintf(out_buf, "FPUIR"); break;
  case 19: sprintf(out_buf, "FPIIR"); break;
  case 20: sprintf(out_buf, "FPIEIR"); break;
  case 21: sprintf(out_buf, "FPIRRset"); break;
  case 22: sprintf(out_buf, "FPIRRreset"); break;
  case 23: sprintf(out_buf, "FPIRR"); break;
  case 24: sprintf(out_buf, "fp_pack_exp"); break;
  case 25: sprintf(out_buf, "sir"); break;
  case 29: sprintf(out_buf, "FPCCRset"); break;
  case 30: sprintf(out_buf, "FPCCRreset"); break;
  case 31: sprintf(out_buf, "FPCCR"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_GrN(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "gr0"); break;
  case 1: sprintf(out_buf, "gr1"); break;
  case 2: sprintf(out_buf, "gr2"); break;
  case 3: sprintf(out_buf, "gr3"); break;
  case 4: sprintf(out_buf, "gr4"); break;
  case 5: sprintf(out_buf, "gr5"); break;
  case 6: sprintf(out_buf, "gr6"); break;
  case 7: sprintf(out_buf, "gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_ArN(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0"); break;
  case 1: sprintf(out_buf, "ar1"); break;
  case 2: sprintf(out_buf, "ar2"); break;
  case 3: sprintf(out_buf, "ar3"); break;
  case 4: sprintf(out_buf, "ar4"); break;
  case 5: sprintf(out_buf, "ar5"); break;
  case 6: sprintf(out_buf, "ar6"); break;
  case 7: sprintf(out_buf, "ar7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_LCond(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "if not carry"); break;
  case 1: sprintf(out_buf, "if vfalse"); break;
  case 2: sprintf(out_buf, "if >"); break;
  case 3: sprintf(out_buf, "if >="); break;
  case 4: sprintf(out_buf, "if v >"); break;
  case 5: sprintf(out_buf, "if v >="); break;
  case 6: sprintf(out_buf, "if <>0"); break;
  case 7: sprintf(out_buf, ""); break;
  case 8: sprintf(out_buf, "if carry"); break;
  case 9: sprintf(out_buf, "if vtrue "); break;
  case 10: sprintf(out_buf, "if <="); break;
  case 11: sprintf(out_buf, "if <"); break;
  case 12: sprintf(out_buf, "if v <="); break;
  case 13: sprintf(out_buf, "if v <"); break;
  case 14: sprintf(out_buf, "if = 0"); break;
  case 15: sprintf(out_buf, "never"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsCall(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "goto"); break;
  case 1: sprintf(out_buf, "call"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsDelay(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, "delayed"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_VArg(char* out_buf, uint32_t idx, uint32_t arg_i){
  switch (idx){
  case 0: sprintf(out_buf, "0"); break;
  case 1: sprintf(out_buf, "ram"); break;
  case 2: sprintf(out_buf, "afifo"); break;
  case 3: sprintf(out_buf, "data"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_RepVal(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "rep 1"); break;
  case 1: sprintf(out_buf, "rep 2"); break;
  case 2: sprintf(out_buf, "rep 3"); break;
  case 3: sprintf(out_buf, "rep 4"); break;
  case 4: sprintf(out_buf, "rep 5"); break;
  case 5: sprintf(out_buf, "rep 6"); break;
  case 6: sprintf(out_buf, "rep 7"); break;
  case 7: sprintf(out_buf, "rep 8"); break;
  case 8: sprintf(out_buf, "rep 9"); break;
  case 9: sprintf(out_buf, "rep 10"); break;
  case 10: sprintf(out_buf, "rep 11"); break;
  case 11: sprintf(out_buf, "rep 12"); break;
  case 12: sprintf(out_buf, "rep 13"); break;
  case 13: sprintf(out_buf, "rep 14"); break;
  case 14: sprintf(out_buf, "rep 15"); break;
  case 15: sprintf(out_buf, "rep 16"); break;
  case 16: sprintf(out_buf, "rep 17"); break;
  case 17: sprintf(out_buf, "rep 18"); break;
  case 18: sprintf(out_buf, "rep 19"); break;
  case 19: sprintf(out_buf, "rep 20"); break;
  case 20: sprintf(out_buf, "rep 21"); break;
  case 21: sprintf(out_buf, "rep 22"); break;
  case 22: sprintf(out_buf, "rep 23"); break;
  case 23: sprintf(out_buf, "rep 24"); break;
  case 24: sprintf(out_buf, "rep 25"); break;
  case 25: sprintf(out_buf, "rep 26"); break;
  case 26: sprintf(out_buf, "rep 27"); break;
  case 27: sprintf(out_buf, "rep 28"); break;
  case 28: sprintf(out_buf, "rep 29"); break;
  case 29: sprintf(out_buf, "rep 30"); break;
  case 30: sprintf(out_buf, "rep 31"); break;
  case 31: sprintf(out_buf, "rep 32"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_RamDataRead(char* out_buf, uint32_t idx, uint32_t arg_indxm){
  switch (idx){
  case 1: sprintf(out_buf, "wfifo"); break;
  case 2: sprintf(out_buf, "data"); break;
  case 3: sprintf(out_buf, "ram"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsRam(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, ",ram"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsFtw(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, ",ftw"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsWtw(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, ",wtw"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_VActiveLog(char* out_buf, uint32_t idx, uint32_t arg_val, uint32_t arg_IsY){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, "activate"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_VActiveArithm(char* out_buf, uint32_t idx, uint32_t arg_val, uint32_t arg_IsY){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, "activate"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsShift(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, "shift"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_MVArg(char* out_buf, uint32_t idx, uint32_t arg_indxm){
  switch (idx){
  case 0: sprintf(out_buf, "0"); break;
  case 1: sprintf(out_buf, "ram"); break;
  case 2: sprintf(out_buf, "afifo"); break;
  case 3: sprintf(out_buf, "data"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_MAddrMode(char* out_buf, uint32_t idx, uint32_t arg_ri, uint32_t arg_rdst){
  switch (idx){
  case 0: sprintf(out_buf, "gr%d", arg_ri); break;
  case 1: sprintf(out_buf, "ar%d += gr%d", arg_ri, arg_ri); break;
  case 2: sprintf(out_buf, "ar%d = gr%d", arg_ri, arg_ri); break;
  case 3: sprintf(out_buf, "ar%d + gr%d", arg_ri, arg_ri); break;
  case 4: sprintf(out_buf, "ar%d", arg_ri); break;
  case 5: sprintf(out_buf, "ar%d ++ gr%d", arg_ri, arg_ri); break;
  case 6: sprintf(out_buf, "--ar%d", arg_ri); break;
  case 7: sprintf(out_buf, "ar%d++", arg_ri); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_AddrIncAr(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0 += gr0"); break;
  case 1: sprintf(out_buf, "ar1 += gr1"); break;
  case 2: sprintf(out_buf, "ar2 += gr2"); break;
  case 3: sprintf(out_buf, "ar3 += gr3"); break;
  case 4: sprintf(out_buf, "ar4 += gr4"); break;
  case 5: sprintf(out_buf, "ar5 += gr5"); break;
  case 6: sprintf(out_buf, "ar6 += gr6"); break;
  case 7: sprintf(out_buf, "ar7 += gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_AddrArAsgGr(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0 = gr0"); break;
  case 1: sprintf(out_buf, "ar1 = gr1"); break;
  case 2: sprintf(out_buf, "ar2 = gr2"); break;
  case 3: sprintf(out_buf, "ar3 = gr3"); break;
  case 4: sprintf(out_buf, "ar4 = gr4"); break;
  case 5: sprintf(out_buf, "ar5 = gr5"); break;
  case 6: sprintf(out_buf, "ar6 = gr6"); break;
  case 7: sprintf(out_buf, "ar7 = gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_AddrArAddGr(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0 + gr0"); break;
  case 1: sprintf(out_buf, "ar1 + gr1"); break;
  case 2: sprintf(out_buf, "ar2 + gr2"); break;
  case 3: sprintf(out_buf, "ar3 + gr3"); break;
  case 4: sprintf(out_buf, "ar4 + gr4"); break;
  case 5: sprintf(out_buf, "ar5 + gr5"); break;
  case 6: sprintf(out_buf, "ar6 + gr6"); break;
  case 7: sprintf(out_buf, "ar7 + gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_AddrArPlusGr(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0 ++ gr0"); break;
  case 1: sprintf(out_buf, "ar1 ++ gr1"); break;
  case 2: sprintf(out_buf, "ar2 ++ gr2"); break;
  case 3: sprintf(out_buf, "ar3 ++ gr3"); break;
  case 4: sprintf(out_buf, "ar4 ++ gr4"); break;
  case 5: sprintf(out_buf, "ar5 ++ gr5"); break;
  case 6: sprintf(out_buf, "ar6 ++ gr6"); break;
  case 7: sprintf(out_buf, "ar7 ++ gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_AddrDecBefore(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "--ar0"); break;
  case 1: sprintf(out_buf, "--ar1"); break;
  case 2: sprintf(out_buf, "--ar2"); break;
  case 3: sprintf(out_buf, "--ar3"); break;
  case 4: sprintf(out_buf, "--ar4"); break;
  case 5: sprintf(out_buf, "--ar5"); break;
  case 6: sprintf(out_buf, "--ar6"); break;
  case 7: sprintf(out_buf, "--ar7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_AddrIncAfter(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0++"); break;
  case 1: sprintf(out_buf, "ar1++"); break;
  case 2: sprintf(out_buf, "ar2++"); break;
  case 3: sprintf(out_buf, "ar3++"); break;
  case 4: sprintf(out_buf, "ar4++"); break;
  case 5: sprintf(out_buf, "ar5++"); break;
  case 6: sprintf(out_buf, "ar6++"); break;
  case 7: sprintf(out_buf, "ar7++"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_ArPlusGr(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "ar0 + gr0"); break;
  case 1: sprintf(out_buf, "ar1 + gr1"); break;
  case 2: sprintf(out_buf, "ar2 + gr2"); break;
  case 3: sprintf(out_buf, "ar3 + gr3"); break;
  case 4: sprintf(out_buf, "ar4 + gr4"); break;
  case 5: sprintf(out_buf, "ar5 + gr5"); break;
  case 6: sprintf(out_buf, "ar6 + gr6"); break;
  case 7: sprintf(out_buf, "ar7 + gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_ArPlusPc(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "pc + gr0"); break;
  case 1: sprintf(out_buf, "pc + gr1"); break;
  case 2: sprintf(out_buf, "pc + gr2"); break;
  case 3: sprintf(out_buf, "pc + gr3"); break;
  case 4: sprintf(out_buf, "pc + gr4"); break;
  case 5: sprintf(out_buf, "pc + gr5"); break;
  case 6: sprintf(out_buf, "pc + gr6"); break;
  case 7: sprintf(out_buf, "pc + gr7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_FRegArg(char* out_buf, uint32_t idx, uint32_t arg_fp){
  switch (idx){
  case 0: sprintf(out_buf, "vreg0"); break;
  case 1: sprintf(out_buf, "vreg1"); break;
  case 2: sprintf(out_buf, "vreg2"); break;
  case 3: sprintf(out_buf, "vreg3"); break;
  case 4: sprintf(out_buf, "vreg4"); break;
  case 5: sprintf(out_buf, "vreg5"); break;
  case 6: sprintf(out_buf, "vreg6"); break;
  case 7: sprintf(out_buf, "vreg7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_FRegArgPair(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "vreg0,vreg1"); break;
  case 1: sprintf(out_buf, "vreg1,vreg2"); break;
  case 2: sprintf(out_buf, "vreg2,vreg3"); break;
  case 3: sprintf(out_buf, "vreg3,vreg4"); break;
  case 4: sprintf(out_buf, "vreg4,vreg5"); break;
  case 5: sprintf(out_buf, "vreg5,vreg6"); break;
  case 6: sprintf(out_buf, "vreg6,vreg7"); break;
  case 7: sprintf(out_buf, "vreg7,vreg8"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_FRegArgPairP(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "vreg0,vreg1"); break;
  case 1: sprintf(out_buf, "vreg2,vreg3"); break;
  case 2: sprintf(out_buf, "vreg4,vreg5"); break;
  case 3: sprintf(out_buf, "vreg6,vreg7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_FRegArgDst(char* out_buf, uint32_t idx, uint32_t arg_fp){
  switch (idx){
  case 0: sprintf(out_buf, "vreg0"); break;
  case 1: sprintf(out_buf, "vreg1"); break;
  case 2: sprintf(out_buf, "vreg2"); break;
  case 3: sprintf(out_buf, "vreg3"); break;
  case 4: sprintf(out_buf, "vreg4"); break;
  case 5: sprintf(out_buf, "vreg5"); break;
  case 6: sprintf(out_buf, "vreg6"); break;
  case 7: sprintf(out_buf, "vreg7"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_CellNum(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "fpu 0"); break;
  case 1: sprintf(out_buf, "fpu 1"); break;
  case 2: sprintf(out_buf, "fpu 2"); break;
  case 3: sprintf(out_buf, "fpu 3"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_DataType(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ".float"); break;
  case 2: sprintf(out_buf, ".complex"); break;
  case 3: sprintf(out_buf, ".double"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsSetMask(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, "noflags"); break;
  case 1: sprintf(out_buf, ""); break;
  case 2: sprintf(out_buf, ",set mask if >"); break;
  case 3: sprintf(out_buf, ",set mask if <"); break;
  case 4: sprintf(out_buf, ",set mask if =0"); break;
  case 5: sprintf(out_buf, ",set mask if <>0"); break;
  case 6: sprintf(out_buf, ",set mask if >="); break;
  case 7: sprintf(out_buf, ",set mask if <="); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsMask(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 2: sprintf(out_buf, "mask ?"); break;
  case 3: sprintf(out_buf, "not mask ?"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsNeg(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, "-"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsRetrive(char* out_buf, uint32_t idx, uint32_t arg_freg){
  char arg_freg_name[256];
  NM6407_DisasmList_FRegArg(arg_freg_name, arg_freg, 0);
  switch (idx){
  case 0: sprintf(out_buf, "%s", arg_freg_name); break;
  case 1: sprintf(out_buf, ".retrive(%s)", arg_freg_name); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsRetriveP(char* out_buf, uint32_t idx, uint32_t arg_freg){
  char arg_freg_name[256];
  NM6407_DisasmList_FRegArgPairP(arg_freg_name, arg_freg);
  switch (idx){
  case 0: sprintf(out_buf, "(%s)", arg_freg_name); break;
  case 1: sprintf(out_buf, ".retrive(%s)", arg_freg_name); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_IsTrans(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ""); break;
  case 1: sprintf(out_buf, ".trans"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_PackFormat(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ".fixed_32"); break;
  case 1: sprintf(out_buf, ".fixed_32 .in_high"); break;
  case 2: sprintf(out_buf, ".fixed_32 .in_low"); break;
  case 3: sprintf(out_buf, ".fixed_64"); break;
  case 4: sprintf(out_buf, ".float"); break;
  case 5: sprintf(out_buf, ".float .in_high"); break;
  case 6: sprintf(out_buf, ".float .in_low"); break;
  case 7: sprintf(out_buf, ".double"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
void NM6407_DisasmList_MaskType(char* out_buf, uint32_t idx){
  switch (idx){
  case 0: sprintf(out_buf, ".float"); break;
  case 1: sprintf(out_buf, ".double"); break;
  default: sprintf(out_buf, "wrong_code");
    break;
  }
}
int _VectorALog_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint16_t) & 0x0fff) == 0x00)){ return 1; }//;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0840)){ return 2; }//with not $FPX $X and not $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0880)){ return 3; }//with $FPX $X and not $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x08c0)){ return 4; }//with not $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0900)){ return 5; }//with not $FPX $X and $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0940)){ return 6; }//with not $FPX $X;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0980)){ return 7; }//with $FPX $X xor $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x09c0)){ return 8; }//with not $FPX $X or not $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0a00)){ return 9; }//with $FPX $X and $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0a40)){ return 10; }//with not $FPX $X xor $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0a80)){ return 11; }//with $FPX $X;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0ac0)){ return 12; }//with $FPX $X or not $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0b00)){ return 13; }//with $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0b40)){ return 14; }//with not $FPX $X or $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0b80)){ return 15; }//with $FPX $X or $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0800)){ return 16; }//with vfalse;
  if (((OPCODE(uint16_t) & 0x0fc0) == 0x0bc0)){ return 17; }//with vtrue;
  if (((OPCODE(uint16_t) & 0x0d80) == 0x0c00)){ return 18; }//with $FPX $X - $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0d80) == 0x0c80)){ return 19; }//with $FPX $X + 1;
  if (((OPCODE(uint16_t) & 0x0d80) == 0x0d00)){ return 20; }//with $FPX $X - 1;
  if (((OPCODE(uint16_t) & 0x0d80) == 0x0d80)){ return 21; }//with $FPX $X + $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0ce0) == 0x0440)){ return 22; }//with mask $M, shift $X, $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0cc0) == 0x0400)){ return 23; }//with mask $M, $FPX $X, $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0c80) == 0x00)){ return 24; }//with vsum $M, $SH $FPX $X, $FPY $Y;
  if (((OPCODE(uint16_t) & 0x0c80) == 0x080)){ return 25; }//with vsum $M, $SH $FPX $X, $FPY vr;
  if (((OPCODE(uint16_t) & 0x0f80) == 0x0480)){ return 26; }//with store vregs
  else{ return 0; }
}
int _Arithm_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint16_t) & 0x0ffff) == 0x00)){ return 1; }//;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06000)){ return 2; }//with $GRk = $GRj - $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0a000)){ return 3; }//with $GRj - $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0e000)){ return 4; }//with $GRk = $GRj - $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06200)){ return 5; }//with $GRk = $GRj - $GRi + -1 +carry noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0a200)){ return 6; }//with $GRj - $GRi + -1 + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0e200)){ return 7; }//with $GRk= $GRj - $GRi + -1 + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06400)){ return 8; }//with $GRk = $GRj + 1 noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0a400)){ return 9; }//with $GRj + 1;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0e400)){ return 10; }//with $GRk = $GRj + 1;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06600)){ return 11; }//with $GRk = $GRj + carry noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0a600)){ return 12; }//with $GRj + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0e600)){ return 13; }//with $GRk= $GRj + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06800)){ return 14; }//with $GRk = $GRj + -1 noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0a800)){ return 15; }//with $GRj + -1;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0e800)){ return 16; }//with $GRk = $GRj + -1;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06a00)){ return 17; }//with $GRk = $GRj + -1 +carry noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0aa00)){ return 18; }//with $GRj + -1 + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ea00)){ return 19; }//with $GRk = $GRj + -1 + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06c00)){ return 20; }//with $GRk = $GRj + $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ac00)){ return 21; }//with $GRj + $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ec00)){ return 22; }//with $GRk = $GRj + $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x06e00)){ return 23; }//with $GRk= $GRj + $GRi + carry noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ae00)){ return 24; }//with $GRj + $GRi + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ee00)){ return 25; }//with $GRk= $GRj + $GRi + carry;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0f000)){ return 26; }//with $GRk=$GRi *: $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0f200)){ return 27; }//with $GRk= $GRi * $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x07000)){ return 28; }//with $GRk=$GRi *: $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x07200)){ return 29; }//with $GRk= $GRi * $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x07800)){ return 30; }//with $GRk = -$GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0b800)){ return 31; }//with -$GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0f800)){ return 32; }//with $GRk = -$GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04000)){ return 33; }//with $GRk=false noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08000)){ return 34; }//with false;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0c000)){ return 35; }//with $GRk=false;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04200)){ return 36; }//with $GRk=not $GRj and not $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08200)){ return 37; }//with not $GRj and not $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0c200)){ return 38; }//with $GRk=not $GRj and not $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04400)){ return 39; }//with $GRk = $GRj and not $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08400)){ return 40; }//with $GRj and not $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0c400)){ return 41; }//with $GRk= $GRj and not $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04600)){ return 42; }//with $GRk=not $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08600)){ return 43; }//with not $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0c600)){ return 44; }//with $GRk=not $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04800)){ return 45; }//with $GRk =not $GRj and $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08800)){ return 46; }//with not $GRj and $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0c800)){ return 47; }//with $GRk = not $GRj and $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04a00)){ return 48; }//with $GRk=not $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08a00)){ return 49; }//with not $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ca00)){ return 50; }//with $GRk = not $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04c00)){ return 51; }//with $GRk = $GRi xor $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08c00)){ return 52; }//with $GRi xor $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0cc00)){ return 53; }//with $GRk = $GRi xor $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x04e00)){ return 54; }//with $GRk = not $GRi or not $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x08e00)){ return 55; }//with not $GRi or not $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0ce00)){ return 56; }//with $GRk = not $GRi or not $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05000)){ return 57; }//with $GRk = $GRi and $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09000)){ return 58; }//with $GRi and $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0d000)){ return 59; }// with $GRk = $GRi and $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05200)){ return 60; }//with $GRk = not $GRi xor $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09200)){ return 61; }//with not $GRi xor $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0d200)){ return 62; }//with $GRk = not $GRi xor $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05800)){ return 63; }//with $GRk = $GRi noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09800)){ return 64; }//with $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0d800)){ return 65; }//with $GRk = $GRi;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05400)){ return 66; }//with $GRk = $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09400)){ return 67; }//with $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0d400)){ return 68; }//with $GRk = $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05a00)){ return 69; }//with $GRk = $GRi or not $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09a00)){ return 70; }//with $GRi or not $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0da00)){ return 71; }//with $GRk = $GRi or not $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05600)){ return 72; }//with $GRk = not $GRi or $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09600)){ return 73; }//with not $GRi or $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0d600)){ return 74; }//with $GRk = not $GRi or $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05c00)){ return 75; }//with $GRk = $GRi or $GRj noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09c00)){ return 76; }//with $GRi or $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0dc00)){ return 77; }//with $GRk = $GRi or $GRj;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x05e00)){ return 78; }//with $GRk=true noflags;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x09e00)){ return 79; }//with true;
  if (((OPCODE(uint16_t) & 0x0fe00) == 0x0de00)){ return 80; }//with $GRk=true;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x00)){ return 81; }//with $GRk = $GRi R<< $shift_arg ;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x0800)){ return 82; }//with $GRk = $GRi R>> $shift_arg;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x01000)){ return 83; }//with $GRk=$GRi << $shift_arg;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x01800)){ return 84; }//with $GRk=$GRi >> $shift_arg;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x02000)){ return 85; }//with $GRk=$GRi A<< $shift_arg;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x02800)){ return 86; }//with $GRk=$GRi A>> $shift_arg;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x03000)){ return 87; }//with $GRk=$GRi C<< $shift_arg;
  if (((OPCODE(uint16_t) & 0x0f800) == 0x03800)){ return 88; }//with $GRk=$GRi C>> $shift_arg;
  else{ return 0; }
}
int _Scalar_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint32_t) & 0x072300000) == 0x050100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 1; }//nul $ar_arg
  if (((OPCODE(uint32_t) & 0x0e2000000) == 0x020000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 2; }//$Rdst = [$MaVal] $ar_inst
  if (((OPCODE(uint32_t) & 0x0e2000000) == 0x022000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 3; }//[$MaVal] = $Rdst $ar_inst
  if (((OPCODE(uint32_t) & 0x0f0000000) == 0x070000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 4; }//$dst_reg = $src_reg set $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x052100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 5; }//$arj = $ari addr $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x056100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 6; }//$arj = $ari addr $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x056100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 7; }//$arj += $ari addr $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x05a100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 8; }//$arj = $ari addr $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x05e100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 9; }//$arj = $ari addr $ar_inst
  if (((OPCODE(uint32_t) & 0x0fc300000) == 0x0200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 10; }//$cond $is_delay $is_call $areg $ar_inst
  if (((OPCODE(uint32_t) & 0x0fc300000) == 0x04200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 11; }//$cond $is_delay $is_call $areg $ar_inst
  if (((OPCODE(uint32_t) & 0x0fc300000) == 0x08200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 12; }//$cond $is_delay $is_call $areg $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x0c200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 13; }//$cond $is_delay skip $areg $ar_inst
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x0e200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 14; }//$cond $is_delay callrel $areg $ar_inst
  if (((OPCODE(uint32_t) & 0x0fff00000) == 0x07300000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 15; }//$cond $is_delay return $ar_inst
  if (((OPCODE(uint32_t) & 0x0fff00000) == 0x06300000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 16; }//$cond $is_delay ireturn $ar_inst
  else{ return 0; }
}
int _Scalar64_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint64_t) & 0x072300000) == 0x040100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 1; }//$const_arg $ar_arg
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x060000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 2; }//$Rdst=[$const_arg] $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x064000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 3; }//$Rdst=[$Rsrc+=$const_arg] $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x068000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 4; }//$Rdst=[$Rsrc=$const_arg] $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x06c000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 5; }//$Rdst=[$Rsrc+$const_arg] $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x062000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 6; }//[$const_arg] = $Rdst $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x066000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 7; }//[$Rsrc+=$const_arg]=$Rdst $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x06a000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 8; }//[$Rsrc=$const_arg]=$Rdst $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe000000) == 0x06e000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 9; }//[$Rsrc+$const_arg]=$Rdst $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x042100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 10; }//$arj = $ari $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x046100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 11; }//$arj = $ari + $const_arg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x046100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 12; }//$arj = $ari - $const_arg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x04a100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 13; }//$arj =  $const_arg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x04e100000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 14; }//$arj = pc + $const_arg addr $ar_inst
  if (((OPCODE(uint64_t) & 0x0f0300000) == 0x040000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 15; }//$dst = $const_arg set $ar_inst
  if (((OPCODE(uint64_t) & 0x0fc300000) == 0x040200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 16; }//$cond $is_delay $is_call $areg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fc300000) == 0x044200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 17; }//$cond $is_delay $is_call $areg + $const_arg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fc300000) == 0x048200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 18; }//$cond $is_delay $is_call $const_arg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x04c200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 19; }//$cond $is_delay skip $const_arg $ar_inst
  if (((OPCODE(uint64_t) & 0x0fe300000) == 0x04e200000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 20; }//$cond $is_delay callrel $const_arg $ar_inst
  else{ return 0; }
}
int _Vector_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint32_t) & 0x0e0380000) == 0x00) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 1; }//$rep_val $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x00) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 2; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x04000000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 3; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x08000000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 4; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x010000000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 5; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x014000000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 6; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x018000000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 7; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe200000) == 0x01c000000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 8; }//$rep_val $RW  = [$ARi] $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x02100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 9; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x06100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 10; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x0a100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 11; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x012100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 12; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x016100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 13; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x01a100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 14; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  if (((OPCODE(uint32_t) & 0x0fe300000) == 0x01e100000) && (_VectorALog_GetInstNum((ocode >> 1) & 0xFFF))){ return 15; }//$rep_val [$ARi] $RW = afifo $Ftw $Wtw $VP
  else{ return 0; }
}
int _FloatVector64_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint64_t) & 0x0f8300000) == 0x0c0000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 1; }//$dst_reg set $const_arg set $ar_inst
  else{ return 0; }
}
int _Float_Vector_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint32_t) & 0x0f0000000) == 0x0f0000000) && (_Arithm_GetInstNum((ocode >> 0) & 0xFFFF))){ return 1; }//$dst_reg = $src_reg set $ar_inst
  if (((OPCODE(uint32_t) & 0x0e6780000) == 0x080000000)){ return 2; }//instruction_3.1
  if (((OPCODE(uint32_t) & 0x0e67e0000) == 0x082020000)){ return 3; }//
  if (((OPCODE(uint32_t) & 0x0e67e0000) == 0x086020000)){ return 4; }//
  if (((OPCODE(uint32_t) & 0x0e6780000) == 0x082000000)){ return 5; }//instruction_3.2
  if (((OPCODE(uint32_t) & 0x0e6780000) == 0x084000000)){ return 6; }//instruction_3.3
  if (((OPCODE(uint32_t) & 0x0e6780000) == 0x086000000)){ return 7; }//
  if (((OPCODE(uint32_t) & 0x0e2380000) == 0x080080000)){ return 8; }//
  if (((OPCODE(uint32_t) & 0x0e2380000) == 0x082080000)){ return 9; }//
  if (((OPCODE(uint32_t) & 0x0e2380000) == 0x080100000)){ return 10; }//
  if (((OPCODE(uint32_t) & 0x0e2380000) == 0x082100000)){ return 11; }//
  if (((OPCODE(uint32_t) & 0x0e1f80000) == 0x080400000)){ return 12; }//$celld $vrd = $cells $vrs1;
  if (((OPCODE(uint32_t) & 0x0e1f80000) == 0x080c00000)){ return 13; }//$celld $vrd = $cells $ms mask ? $vrs1 : $vrs0;
  if (((OPCODE(uint32_t) & 0x0e1f81000) == 0x081400000)){ return 14; }//$cells .packer = $vrs1 with $df <= $sf;
  if (((OPCODE(uint32_t) & 0x0e1f81000) == 0x081401000)){ return 15; }//$cells .packer = ($vrs1) with $df <= $sf;
  if (((OPCODE(uint32_t) & 0x0e1f80040) == 0x081c00040)){ return 16; }//
  if (((OPCODE(uint32_t) & 0x0e1f80040) == 0x081c00000)){ return 17; }//
  else{ return 0; }
}
int Main_GetInstNum(uint64_t ocode){
  if (((OPCODE(uint32_t) & 0x00) == 0x00) && (_Scalar_GetInstNum((ocode >> 0) & 0x0FFFFFFFFl))){ return 1; }//$iscalar
  if (((OPCODE(uint64_t) & 0x00) == 0x00) && (_Scalar64_GetInstNum((ocode >> 0) & 0xFFFFFFFFFFFFFFFFl))){ return 2; }//$iscalar64
  if (((OPCODE(uint32_t) & 0x00) == 0x00) && (_Vector_GetInstNum((ocode >> 0) & 0x0FFFFFFFFl))){ return 3; }//$ivec
  if (((OPCODE(uint32_t) & 0x00) == 0x00) && (_Float_Vector_GetInstNum((ocode >> 0) & 0x0FFFFFFFFl))){ return 4; }//$ifvec
  if (((OPCODE(uint64_t) & 0x00) == 0x00) && (_FloatVector64_GetInstNum((ocode >> 0) & 0xFFFFFFFFFFFFFFFFl))){ return 5; }//$ifvec64
  else{ return 0; }
}
char VectorALog_dstr[1024];
char* VectorALog_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint16_t) & 0x0fff) == 0x00)){
    uint16_t ocode = BIN(uint16_t);
    sprintf(VectorALog_dstr, ";");
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0840)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s and not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s and not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0880)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s and not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s and not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x08c0)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s;", arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s;", arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0900)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s and %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s and %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0940)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0980)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s xor %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s xor %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x09c0)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s or not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s or not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0a00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s and %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s and %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0a40)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s xor %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s xor %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0a80)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0ac0)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s or not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s or not %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0b00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s;", arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s;", arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0b40)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s or %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with not %s %s or %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0b80)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "not %s %s or %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s or %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "vfalse;");
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with vfalse;");
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fc0) == 0x0bc0)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "vtrue;");
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with vtrue;");
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0d80) == 0x0c00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_xx = (uint32_t)((ocode >> 6) & 0x1);
    uint32_t arg_yy = (uint32_t)((ocode >> 9) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s - %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s - %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0d80) == 0x0c80)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_xx = (uint32_t)((ocode >> 6) & 0x1);
    uint32_t arg_yy = (uint32_t)((ocode >> 9) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s + 1;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s + 1;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0d80) == 0x0d00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_xx = (uint32_t)((ocode >> 6) & 0x1);
    uint32_t arg_yy = (uint32_t)((ocode >> 9) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s + 1;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s - 1;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0d80) == 0x0d80)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_xx = (uint32_t)((ocode >> 6) & 0x1);
    uint32_t arg_yy = (uint32_t)((ocode >> 9) & 0x1);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPX_name, arg_FPX, 0, 0);
    sprintf(VectorALog_dstr, "%s %s + 1;", arg_FPX_name, arg_X_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with %s %s + %s %s;", arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0ce0) == 0x0440)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_M = (uint32_t)((ocode >> 8) & 0x3);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_M_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_MVArg(arg_M_name, arg_M, 0);
    sprintf(VectorALog_dstr, "mask %s, shift %s, %s %s;", arg_M_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with mask %s, shift %s, %s %s;", arg_M_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0cc0) == 0x0400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_M = (uint32_t)((ocode >> 8) & 0x3);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    char arg_M_name[256];
    NM6407_DisasmList_VArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveLog(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveLog(arg_FPX_name, arg_FPX, 0, 0);
    NM6407_DisasmList_MVArg(arg_M_name, arg_M, 0);
    sprintf(VectorALog_dstr, "mask %s, %s %s, %s %s;", arg_M_name, arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with mask %s, %s %s, %s %s;", arg_M_name, arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0c80) == 0x00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_SH = (uint32_t)((ocode >> 6) & 0x1);
    uint32_t arg_M = (uint32_t)((ocode >> 8) & 0x3);
    char arg_Y_name[256];
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    char arg_SH_name[256];
    char arg_M_name[256];
    NM6407_DisasmList_MVArg(arg_Y_name, arg_Y, 0);
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPX_name, arg_FPX, 0, 0);
    NM6407_DisasmList_IsShift(arg_SH_name, arg_SH);
    NM6407_DisasmList_MVArg(arg_M_name, arg_M, 0);
    sprintf(VectorALog_dstr, "vsum %s, %s %s %s, %s %s;", arg_M_name, arg_SH_name, arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with vsum %s, %s %s %s, %s %s;", arg_M_name, arg_SH_name, arg_FPX_name, arg_X_name, arg_FPY_name, arg_Y_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0c80) == 0x080)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_Y = (uint32_t)((ocode >> 0) & 0x3);
    uint32_t arg_X = (uint32_t)((ocode >> 2) & 0x3);
    uint32_t arg_FPY = (uint32_t)((ocode >> 4) & 0x1);
    uint32_t arg_FPX = (uint32_t)((ocode >> 5) & 0x1);
    uint32_t arg_SH = (uint32_t)((ocode >> 6) & 0x1);
    uint32_t arg_M = (uint32_t)((ocode >> 8) & 0x3);
    char arg_X_name[256];
    char arg_FPY_name[256];
    char arg_FPX_name[256];
    char arg_SH_name[256];
    char arg_M_name[256];
    NM6407_DisasmList_VArg(arg_X_name, arg_X, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPY_name, arg_FPY, 0, 0);
    NM6407_DisasmList_VActiveArithm(arg_FPX_name, arg_FPX, 0, 0);
    NM6407_DisasmList_IsShift(arg_SH_name, arg_SH);
    NM6407_DisasmList_MVArg(arg_M_name, arg_M, 0);
    sprintf(VectorALog_dstr, "vsum %s, %s %s %s, %s vr;", arg_M_name, arg_SH_name, arg_FPX_name, arg_X_name, arg_FPY_name);
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with vsum %s, %s %s %s, %s vr;", arg_M_name, arg_SH_name, arg_FPX_name, arg_X_name, arg_FPY_name);
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f80) == 0x0480)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_yy = (uint32_t)((ocode >> 0) & 0xF);
    uint32_t arg_xx = (uint32_t)((ocode >> 4) & 0x7);
    sprintf(VectorALog_dstr, "store vregs");
    *size = 2;
    return VectorALog_dstr;
    sprintf(VectorALog_dstr, "with store vregs");
    *size = 2;
    return VectorALog_dstr;
    bin += 2;
  }
  sprintf(VectorALog_dstr, "undef inst");
  *size = 4;
  return VectorALog_dstr;
};

char Arithm_dstr[1024];
char* Arithm_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint16_t) & 0x0ffff) == 0x00)){
    uint16_t ocode = BIN(uint16_t);
    sprintf(Arithm_dstr, "with nul;");
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, ";");
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s - %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s -=%s noflags;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s -=%s noflags;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s = %s - %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0a000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s - %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s - %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0e000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s - %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s -= %s;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s -= %s;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s = %s - %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s - %s + -1 +carry noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s - %s - 1 +carry noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s - %s - 1 +carry noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s - %s + -1 +carry noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0a200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s - %s + -1 + carry;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s - %s -1 + carry;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s - %s -1 + carry;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s - %s + -1 + carry;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0e200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s - %s + -1 + carry;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s - %s -1 + carry;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s= %s - %s -1 + carry;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s - %s + -1 + carry;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + 1 noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s++ noflags;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s++ noflags;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s+=1 noflags;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s+=1 noflags;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s = %s + 1 noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0a400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s + 1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s + 1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0e400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + 1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s++;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s++;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s+=1;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s+=1;", arg_GRk_name);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s = %s + 1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s + carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0a600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0e600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + -1 noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s - 1 noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s - 1 noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s-- noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s-- noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s + -1 noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0a800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s + -1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s - 1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s - 1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s -1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s -1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s--;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s--;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s + -1;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0e800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + -1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s - 1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s - 1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s -1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s -1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s--;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s--;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s + -1;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06a00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + -1 +carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s - 1 +carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s - 1 +carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s -1 +carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s -1 +carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s + -1 +carry noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0aa00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s + -1 + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s - 1 + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s - 1 + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s -1 + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s -1 + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s + -1 + carry;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ea00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + -1 + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s -1 + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s -1 + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s - 1 + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "%s = %s - 1 + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s + -1 + carry;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06c00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s += %s noflags;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s += %s noflags;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s = %s + %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ac00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s + %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s + %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ec00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s + %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "with %s += %s;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRj == arg_GRk)){
      sprintf(Arithm_dstr, "%s += %s;", arg_GRk_name, arg_GRi_name);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s = %s + %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x06e00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s + %s + carry noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s + %s + carry noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ae00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s + %s + carry;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s + %s + carry;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ee00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s + %s + carry;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s + %s + carry;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0f000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=%s *: %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=%s *: %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0f200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s * %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s * %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x07000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=%s *: %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=%s *: %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x07200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s * %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s * %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x07800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = -%s noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = -%s noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0b800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "-%s;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with -%s;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0f800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " %s = -%s;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = -%s;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=false noflags;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=false noflags;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " false;");
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with false;");
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0c000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=false;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=false;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=not %s and not %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=not %s and not %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "not %s and not %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s and not %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0c200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=not %s and not %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=not %s and not %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s and not %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s and not %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s and not %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s and not %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0c400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s= %s and not %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s= %s and not %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=not %s noflags;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=not %s noflags;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "not %s;", arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s;", arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0c600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=not %s;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=not %s;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s =not %s and %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s =not %s and %s noflags;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "not %s and %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s and %s;", arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0c800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s and %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s and %s;", arg_GRk_name, arg_GRj_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04a00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=not %s noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=not %s noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08a00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " not %s;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ca00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04c00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s xor %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s xor %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08c00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " %s xor %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s xor %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0cc00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " %s = %s xor %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s xor %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x04e00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s or not %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s or not %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x08e00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " not %s or not %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s or not %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0ce00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s or not %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s or not %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s and %s noflags; ", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s and %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s and %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s and %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0d000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s and %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, " with %s = %s and %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s xor %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s xor %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " not %s xor %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s xor %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0d200)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s xor %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s xor %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s noflags;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s noflags;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s;", arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s;", arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0d800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s;", arg_GRk_name, arg_GRi_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s noflags; ", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s noflags;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " %s;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s;", arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0d400)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s; ", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s;", arg_GRk_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05a00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s or not %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s or not %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09a00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s or not %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s or not %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0da00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s or not %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s or not %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s or not %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s or %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, " not %s or %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with not %s or %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0d600)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = not %s or %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = not %s or %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05c00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s or %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s or %s noflags;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09c00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s or %s; ", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s or %s;", arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0dc00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s = %s or %s; ", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s or %s;", arg_GRk_name, arg_GRi_name, arg_GRj_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x05e00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=true noflags;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=true noflags;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x09e00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "true;");
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with true;");
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0fe00) == 0x0de00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_GRj = (uint32_t)((ocode >> 6) & 0x7);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    char arg_GRj_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    NM6407_DisasmList_GrN(arg_GRj_name, arg_GRj);
    sprintf(Arithm_dstr, "%s=true;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=true;", arg_GRk_name);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x00)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    sprintf(Arithm_dstr, "%s = %s R<< 0x%x ;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s R<< 0x%x ;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x0800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    ;
    arg_shift_arg = ((arg_shift_arg * (0 - 1)) & 31);
    sprintf(Arithm_dstr, "%s = %s R>> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s = %s R>> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x01000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    sprintf(Arithm_dstr, "%s=%s << 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRi == arg_GRk)){
      sprintf(Arithm_dstr, "with %s<<= 0x%x;", arg_GRk_name, arg_shift_arg);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRi == arg_GRk)){
      sprintf(Arithm_dstr, "%s<<= 0x%x;", arg_GRk_name, arg_shift_arg);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s=%s << 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x01800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    ;
    arg_shift_arg = ((arg_shift_arg * (0 - 1)) & 31);
    sprintf(Arithm_dstr, "%s=%s >> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    if ((arg_GRi == arg_GRk)){
      sprintf(Arithm_dstr, "with %s>>= 0x%x;", arg_GRk_name, arg_shift_arg);
      *size = 2;
      return Arithm_dstr;
    }
    if ((arg_GRi == arg_GRk)){
      sprintf(Arithm_dstr, "%s >>= 0x%x;", arg_GRk_name, arg_shift_arg);
      *size = 2;
      return Arithm_dstr;
    }
    sprintf(Arithm_dstr, "with %s=%s >> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x02000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    sprintf(Arithm_dstr, "%s = %s A << 0x%x; ", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=%s A<< 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x02800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    ;
    arg_shift_arg = ((arg_shift_arg * (0 - 1)) & 31);
    sprintf(Arithm_dstr, "%s=%s A>> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=%s A>> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x03000)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    sprintf(Arithm_dstr, "%s = %s C << 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=%s C<< 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  if (((BIN(uint16_t) & 0x0f800) == 0x03800)){
    uint16_t ocode = BIN(uint16_t);
    uint32_t arg_GRk = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_GRi = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_shift_arg = (uint32_t)((ocode >> 6) & 0x1F);
    char arg_GRk_name[256];
    char arg_GRi_name[256];
    NM6407_DisasmList_GrN(arg_GRk_name, arg_GRk);
    NM6407_DisasmList_GrN(arg_GRi_name, arg_GRi);
    ;
    arg_shift_arg = ((arg_shift_arg * (0 - 1)) & 31);
    sprintf(Arithm_dstr, "%s=%s C>> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    sprintf(Arithm_dstr, "with %s=%s C>> 0x%x;", arg_GRk_name, arg_GRi_name, arg_shift_arg);
    *size = 2;
    return Arithm_dstr;
    bin += 2;
  }
  sprintf(Arithm_dstr, "undef inst");
  *size = 4;
  return Arithm_dstr;
};

char Scalar_dstr[1024];
char* Scalar_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint32_t) & 0x072300000) == 0x050100000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_arg = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_nul_arg1 = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_nul_arg2 = (uint32_t)((ocode >> 26) & 0x3);
    uint32_t arg_p = (uint32_t)((ocode >> 31) & 0x1);
    sprintf(Scalar_dstr, "%s", Arithm_DisAssembly((char*)(&arg_ar_arg), &int_size));
    *size = 4;
    return Scalar_dstr;
    sprintf(Scalar_dstr, "nul %s", Arithm_DisAssembly((char*)(&arg_ar_arg), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e2000000) == 0x020000000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_MaVal = (uint32_t)((ocode >> 26) & 0x7);
    char arg_Rdst_name[256];
    char arg_MaVal_name[256];
    NM6407_DisasmList_WriteRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_MAddrMode(arg_MaVal_name, arg_MaVal, arg_Rsrc, 0);
    if ((arg_Rsrc == 0x7) && (arg_MaVal == 0x6)){
      sprintf(Scalar_dstr, "pop %s %s", arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_Rdst == 0x1D)){
      sprintf(Scalar_dstr, "pswr set [%s] %s", arg_MaVal_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_Rdst == 0x1E)){
      sprintf(Scalar_dstr, "pswr clear [%s] %s", arg_MaVal_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_Rdst == 0x1A)){
      sprintf(Scalar_dstr, "intr clear [%s] %s", arg_MaVal_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s = [%s] %s", arg_Rdst_name, arg_MaVal_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e2000000) == 0x022000000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_MaVal = (uint32_t)((ocode >> 26) & 0x7);
    char arg_Rdst_name[256];
    char arg_MaVal_name[256];
    NM6407_DisasmList_ReadRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_MAddrMode(arg_MaVal_name, arg_MaVal, arg_Rsrc, 0);
    if ((arg_Rsrc == 0x7) && (arg_MaVal == 0x7)){
      sprintf(Scalar_dstr, "push %s %s", arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "[%s] = %s %s", arg_MaVal_name, arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0f0000000) == 0x070000000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_src_reg = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_dst_reg = (uint32_t)((ocode >> 22) & 0x3F);
    char arg_src_reg_name[256];
    char arg_dst_reg_name[256];
    NM6407_DisasmList_ReadRegsList(arg_src_reg_name, arg_src_reg);
    NM6407_DisasmList_WriteRegsList(arg_dst_reg_name, arg_dst_reg);
    sprintf(Scalar_dstr, "%s = %s %s", arg_dst_reg_name, arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s = %s;", arg_dst_reg_name, arg_src_reg_name);
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s = %s set;", arg_dst_reg_name, arg_src_reg_name);
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_dst_reg == 0x1D)){
      sprintf(Scalar_dstr, "pswr set %s %s", arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_dst_reg == 0x1E)){
      sprintf(Scalar_dstr, "pswr clear %s %s", arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_dst_reg == 0x1D)){
      sprintf(Scalar_dstr, "pswr set %s set %s", arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_dst_reg == 0x1E)){
      sprintf(Scalar_dstr, "pswr clear %s set %s", arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_dst_reg == 0x1A)){
      sprintf(Scalar_dstr, "intr clear %s %s", arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    if ((arg_dst_reg == 0x1A)){
      sprintf(Scalar_dstr, "intr clear %s set %s", arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s = %s set %s", arg_dst_reg_name, arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x052100000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArN(arg_ari_name, arg_ari);
    sprintf(Scalar_dstr, "%s = %s %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    sprintf(Scalar_dstr, "%s = %s addr %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x056100000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArPlusGr(arg_ari_name, arg_ari);
    sprintf(Scalar_dstr, "%s = %s %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    sprintf(Scalar_dstr, "%s = %s addr %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x056100000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_GrN(arg_ari_name, arg_ari);
    sprintf(Scalar_dstr, "%s += %s %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    sprintf(Scalar_dstr, "%s += %s addr %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x05a100000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_GrN(arg_ari_name, arg_ari);
    sprintf(Scalar_dstr, "%s = %s %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    sprintf(Scalar_dstr, "%s = %s addr %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x05e100000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArPlusPc(arg_ari_name, arg_ari);
    sprintf(Scalar_dstr, "%s = %s %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    sprintf(Scalar_dstr, "%s = %s addr %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fc300000) == 0x0200000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_call = (uint32_t)((ocode >> 25) & 0x1);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    char arg_is_call_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArN(arg_areg_name, arg_areg);
    NM6407_DisasmList_IsCall(arg_is_call_name, arg_is_call);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s %s %s;", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s %s %s %s", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fc300000) == 0x04200000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_call = (uint32_t)((ocode >> 25) & 0x1);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    char arg_is_call_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArPlusGr(arg_areg_name, arg_areg);
    NM6407_DisasmList_IsCall(arg_is_call_name, arg_is_call);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s %s %s;", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s %s %s %s", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fc300000) == 0x08200000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_call = (uint32_t)((ocode >> 25) & 0x1);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    char arg_is_call_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_GrN(arg_areg_name, arg_areg);
    NM6407_DisasmList_IsCall(arg_is_call_name, arg_is_call);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s %s %s;", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s %s %s %s", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x0c200000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_GrN(arg_areg_name, arg_areg);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s skip %s;", arg_cond_name, arg_is_delay_name, arg_areg_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s skip %s %s", arg_cond_name, arg_is_delay_name, arg_areg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x0e200000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_GrN(arg_areg_name, arg_areg);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s callrel %s;", arg_cond_name, arg_is_delay_name, arg_areg_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s callrel %s %s", arg_cond_name, arg_is_delay_name, arg_areg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fff00000) == 0x07300000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s return;", arg_cond_name, arg_is_delay_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s return %s", arg_cond_name, arg_is_delay_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fff00000) == 0x06300000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar_dstr, "%s %s ireturn;", arg_cond_name, arg_is_delay_name);
      *size = 4;
      return Scalar_dstr;
    }
    sprintf(Scalar_dstr, "%s %s ireturn %s", arg_cond_name, arg_is_delay_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return Scalar_dstr;
    bin += 4;
  }
  sprintf(Scalar_dstr, "undef inst");
  *size = 4;
  return Scalar_dstr;
};

char Scalar64_dstr[1024];
char* Scalar64_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint64_t) & 0x072300000) == 0x040100000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_arg = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_null_1 = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_null_2 = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_null_3 = (uint32_t)((ocode >> 26) & 0x3);
    uint32_t arg_p = (uint32_t)((ocode >> 31) & 0x1);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    sprintf(Scalar64_dstr, "nul 0x%x %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_arg), &int_size));
    *size = 8;
    return Scalar64_dstr;
    sprintf(Scalar64_dstr, "0x%x %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_arg), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x060000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_WriteRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "%s=[0x%x] %s", arg_Rdst_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x064000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_WriteRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "%s=[%s+=0x%x] %s", arg_Rdst_name, arg_Rsrc_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x068000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_WriteRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "%s=[%s=0x%x] %s", arg_Rdst_name, arg_Rsrc_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x06c000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_WriteRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "%s=[%s+0x%x] %s", arg_Rdst_name, arg_Rsrc_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x062000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_ReadRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "[0x%x] = %s %s", arg_const_arg, arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x066000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_ReadRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "[%s+=0x%x]=%s %s", arg_Rsrc_name, arg_const_arg, arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x06a000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_ReadRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "[%s=0x%x]=%s %s", arg_Rsrc_name, arg_const_arg, arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe000000) == 0x06e000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_Rdst = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_Rsrc = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_Rdst_name[256];
    char arg_Rsrc_name[256];
    NM6407_DisasmList_ReadRegsList(arg_Rdst_name, arg_Rdst);
    NM6407_DisasmList_ArN(arg_Rsrc_name, arg_Rsrc);
    sprintf(Scalar64_dstr, "[%s+0x%x]=%s %s", arg_Rsrc_name, arg_const_arg, arg_Rdst_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x042100000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArN(arg_ari_name, arg_ari);
    sprintf(Scalar64_dstr, "%s = %s addr %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    sprintf(Scalar64_dstr, "%s = %s %s", arg_arj_name, arg_ari_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x046100000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArN(arg_ari_name, arg_ari);
    sprintf(Scalar64_dstr, "%s = %s + 0x%x addr %s", arg_arj_name, arg_ari_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    if ((arg_ari == arg_arj)){
      sprintf(Scalar64_dstr, "%s += 0x%x %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_ari == arg_arj)){
      sprintf(Scalar64_dstr, "%s += 0x%x addr %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    sprintf(Scalar64_dstr, "%s = %s + 0x%x %s", arg_arj_name, arg_ari_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x046100000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArN(arg_ari_name, arg_ari);
    sprintf(Scalar64_dstr, "%s = %s - 0x%x addr %s", arg_arj_name, arg_ari_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    if ((arg_ari == arg_arj)){
      sprintf(Scalar64_dstr, "%s -= 0x%x %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_ari == arg_arj)){
      sprintf(Scalar64_dstr, "%s -= 0x%x addr %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    sprintf(Scalar64_dstr, "%s = %s - 0x%x %s", arg_arj_name, arg_ari_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x04a100000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArN(arg_ari_name, arg_ari);
    sprintf(Scalar64_dstr, "%s =  0x%x addr %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    sprintf(Scalar64_dstr, "%s =  0x%x %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x04e100000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_arj = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_arj_name[256];
    char arg_ari_name[256];
    NM6407_DisasmList_ArN(arg_arj_name, arg_arj);
    NM6407_DisasmList_ArN(arg_ari_name, arg_ari);
    sprintf(Scalar64_dstr, "%s = pc + 0x%x %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    sprintf(Scalar64_dstr, "%s = pc + 0x%x addr %s", arg_arj_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0f0300000) == 0x040000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_dst = (uint32_t)((ocode >> 22) & 0x3F);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_dst_name[256];
    NM6407_DisasmList_WriteRegsList(arg_dst_name, arg_dst);
    if ((arg_dst == 0x1D)){
      sprintf(Scalar64_dstr, "pswr set 0x%x set %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_dst == 0x1D)){
      sprintf(Scalar64_dstr, "pswr set 0x%x %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_dst == 0x1E)){
      sprintf(Scalar64_dstr, "pswr clear 0x%x set %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_dst == 0x1E)){
      sprintf(Scalar64_dstr, "pswr clear 0x%x %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_dst == 0x1A)){
      sprintf(Scalar64_dstr, "intr clear 0x%x set %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_dst == 0x1A)){
      sprintf(Scalar64_dstr, "intr clear 0x%x %s", arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
      *size = 8;
      return Scalar64_dstr;
    }
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar64_dstr, "%s = 0x%x;", arg_dst_name, arg_const_arg);
      *size = 8;
      return Scalar64_dstr;
    }
    sprintf(Scalar64_dstr, "%s = 0x%x set %s", arg_dst_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fc300000) == 0x040200000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_call = (uint32_t)((ocode >> 25) & 0x1);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    char arg_is_call_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArN(arg_areg_name, arg_areg);
    NM6407_DisasmList_IsCall(arg_is_call_name, arg_is_call);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    sprintf(Scalar64_dstr, "%s %s %s %s %s", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fc300000) == 0x044200000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_call = (uint32_t)((ocode >> 25) & 0x1);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    char arg_is_call_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArN(arg_areg_name, arg_areg);
    NM6407_DisasmList_IsCall(arg_is_call_name, arg_is_call);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    sprintf(Scalar64_dstr, "%s %s %s %s + 0x%x %s", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_areg_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fc300000) == 0x048200000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_is_call = (uint32_t)((ocode >> 25) & 0x1);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    char arg_is_call_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArN(arg_areg_name, arg_areg);
    NM6407_DisasmList_IsCall(arg_is_call_name, arg_is_call);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    sprintf(Scalar64_dstr, "%s %s %s 0x%x %s", arg_cond_name, arg_is_delay_name, arg_is_call_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x04c200000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArN(arg_areg_name, arg_areg);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar64_dstr, "%s %s skip 0x%x;", arg_cond_name, arg_is_delay_name, arg_const_arg);
      *size = 8;
      return Scalar64_dstr;
    }
    sprintf(Scalar64_dstr, "%s %s skip 0x%x %s", arg_cond_name, arg_is_delay_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  if (((BIN(uint64_t) & 0x0fe300000) == 0x04e200000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_cond = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_areg = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    uint32_t arg_is_delay = 0;
    char arg_cond_name[256];
    char arg_areg_name[256];
    NM6407_DisasmList_LCond(arg_cond_name, arg_cond);
    NM6407_DisasmList_ArN(arg_areg_name, arg_areg);
    char arg_is_delay_name[256];
    NM6407_DisasmList_IsDelay(arg_is_delay_name, arg_is_delay);
    if ((arg_ar_inst == 0x0)){
      sprintf(Scalar64_dstr, "%s %s callrel 0x%x;", arg_cond_name, arg_is_delay_name, arg_const_arg);
      *size = 8;
      return Scalar64_dstr;
    }
    sprintf(Scalar64_dstr, "%s %s callrel 0x%x %s", arg_cond_name, arg_is_delay_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return Scalar64_dstr;
    bin += 8;
  }
  sprintf(Scalar64_dstr, "undef inst");
  *size = 4;
  return Scalar64_dstr;
};

char Vector_dstr[1024];
char* Vector_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint32_t) & 0x0e0380000) == 0x00) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_xv = (uint32_t)((ocode >> 22) & 0x7F);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    if ((arg_rep_val == 0x0)){
      sprintf(Vector_dstr, "%s %s %s", arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
      *size = 4;
      return Vector_dstr;
    }
    if ((arg_rep_val == 0x0) && (arg_Ftw == 0x1)){
      sprintf(Vector_dstr, "ftw %s %s", arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
      *size = 4;
      return Vector_dstr;
    }
    if ((arg_rep_val == 0x0) && (arg_Wtw == 0x1) && (arg_Ftw == 0x0)){
      sprintf(Vector_dstr, "wtw %s", VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
      *size = 4;
      return Vector_dstr;
    }
    if ((arg_Wtw == 0x0) && (arg_Ftw == 0x0)){
      sprintf(Vector_dstr, "%s vnul %s", arg_rep_val_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
      *size = 4;
      return Vector_dstr;
    }
    sprintf(Vector_dstr, "%s %s %s %s", arg_rep_val_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x00) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_GrN(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x04000000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_AddrIncAr(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x08000000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_AddrArAsgGr(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x010000000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_ArN(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x014000000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_AddrArPlusGr(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x018000000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_AddrDecBefore(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe200000) == 0x01c000000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x3);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_RamDataRead(arg_RW_name, arg_RW, 0);
    NM6407_DisasmList_AddrIncAfter(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s %s  = [%s] %s %s %s", arg_rep_val_name, arg_RW_name, arg_ARi_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x02100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_GrN(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x06100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_AddrIncAr(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x0a100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_AddrArAsgGr(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x012100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_ArN(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x016100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_AddrArPlusGr(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x01a100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_AddrDecBefore(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0fe300000) == 0x01e100000) && (_VectorALog_GetInstNum((BIN(uint32_t) >> 1) & 0xFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_Wtw = (uint32_t)((ocode >> 0) & 0x1);
    uint32_t arg_VP = (uint32_t)((ocode >> 1) & 0xFFF);
    uint32_t arg_rep_val = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_Ftw = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_RW = (uint32_t)((ocode >> 19) & 0x1);
    uint32_t arg_ARi = (uint32_t)((ocode >> 22) & 0x7);
    char arg_Wtw_name[256];
    char arg_rep_val_name[256];
    char arg_Ftw_name[256];
    char arg_RW_name[256];
    char arg_ARi_name[256];
    NM6407_DisasmList_IsWtw(arg_Wtw_name, arg_Wtw);
    NM6407_DisasmList_RepVal(arg_rep_val_name, arg_rep_val);
    NM6407_DisasmList_IsFtw(arg_Ftw_name, arg_Ftw);
    NM6407_DisasmList_IsRam(arg_RW_name, arg_RW);
    NM6407_DisasmList_AddrIncAfter(arg_ARi_name, arg_ARi);
    sprintf(Vector_dstr, "%s [%s] %s = afifo %s %s %s", arg_rep_val_name, arg_ARi_name, arg_RW_name, arg_Ftw_name, arg_Wtw_name, VectorALog_DisAssembly((char*)(&arg_VP), &int_size));
    *size = 4;
    return Vector_dstr;
    bin += 4;
  }
  sprintf(Vector_dstr, "undef inst");
  *size = 4;
  return Vector_dstr;
};

char FloatVector64_dstr[1024];
char* FloatVector64_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint64_t) & 0x0f8300000) == 0x0c0000000) && (_Arithm_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFF))){
    uint64_t ocode = BIN(uint64_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_nul_arg = (uint32_t)((ocode >> 16) & 0xF);
    uint32_t arg_dst_reg = (uint32_t)((ocode >> 22) & 0x1F);
    uint32_t arg_const_arg = (uint32_t)((ocode >> 32) & 0x0FFFFFFFFl);
    char arg_dst_reg_name[256];
    NM6407_DisasmList_WriteRegsListFP(arg_dst_reg_name, arg_dst_reg);
    sprintf(FloatVector64_dstr, "%s set 0x%x set %s", arg_dst_reg_name, arg_const_arg, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 8;
    return FloatVector64_dstr;
    bin += 8;
  }
  sprintf(FloatVector64_dstr, "undef inst");
  *size = 4;
  return FloatVector64_dstr;
};

char FloatVector_dstr[1024];
char* FloatVector_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint32_t) & 0x0f0000000) == 0x0f0000000) && (_Arithm_GetInstNum((BIN(uint32_t) >> 0) & 0xFFFF))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ar_inst = (uint32_t)((ocode >> 0) & 0xFFFF);
    uint32_t arg_src_reg = (uint32_t)((ocode >> 16) & 0x3F);
    uint32_t arg_dst_reg = (uint32_t)((ocode >> 22) & 0x3F);
    char arg_src_reg_name[256];
    char arg_dst_reg_name[256];
    NM6407_DisasmList_ReadRegsListFP(arg_src_reg_name, arg_src_reg);
    NM6407_DisasmList_WriteRegsListFP(arg_dst_reg_name, arg_dst_reg);
    sprintf(FloatVector_dstr, "%s = %s %s", arg_dst_reg_name, arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return FloatVector_dstr;
    sprintf(FloatVector_dstr, "%s = %s set %s", arg_dst_reg_name, arg_src_reg_name, Arithm_DisAssembly((char*)(&arg_ar_inst), &int_size));
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e6780000) == 0x080000000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_tmp = (uint32_t)((ocode >> 6) & 0x7F);
    uint32_t arg_vra = (uint32_t)((ocode >> 13) & 0x7);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 16) & 0x1);
    uint32_t arg_data_type = (uint32_t)((ocode >> 17) & 0x3);
    uint32_t arg_op_code = (uint32_t)((ocode >> 23) & 0x3);
    uint32_t arg_mask = (uint32_t)((ocode >> 27) & 0x3);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_vra_name[256];
    char arg_data_type_name[256];
    char arg_mask_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_FRegArg(arg_vra_name, arg_vra, 0);
    NM6407_DisasmList_DataType(arg_data_type_name, arg_data_type);
    NM6407_DisasmList_IsMask(arg_mask_name, arg_mask);
    if ((arg_op_code == 0x0)){
      sprintf(FloatVector_dstr, "%s %s  %s =  %s %s : %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1)){
      sprintf(FloatVector_dstr, "%s %s  %s =  %s /%s/ : %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2)){
      sprintf(FloatVector_dstr, "%s %s  %s =  %s -%s : %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3)){
      sprintf(FloatVector_dstr, "%s %s  %s =  %s -/%s/ : %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x0) && (arg_mask == 0x0)){
      sprintf(FloatVector_dstr, "%s %s  %s =  %s ;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1) && (arg_mask == 0x0)){
      sprintf(FloatVector_dstr, "%s %s  %s =  /%s/;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2) && (arg_mask == 0x0)){
      sprintf(FloatVector_dstr, "%s %s  %s =  -%s ;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3) && (arg_mask == 0x0)){
      sprintf(FloatVector_dstr, "%s %s  %s =  -/%s/;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "instruction_3.1");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e67e0000) == 0x082020000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_vrb = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_matr_first = (uint32_t)((ocode >> 9) & 0x1);
    uint32_t arg_vrc = (uint32_t)((ocode >> 10) & 0x3);
    uint32_t arg_matr = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_tmp = (uint32_t)((ocode >> 13) & 0xF);
    uint32_t arg_is_neg = (uint32_t)((ocode >> 23) & 0x1);
    uint32_t arg_tmp2 = (uint32_t)((ocode >> 24) & 0x1);
    uint32_t arg_mask = (uint32_t)((ocode >> 27) & 0x3);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_vrb_name[256];
    char arg_matr_first_name[256];
    char arg_vrc_name[256];
    char arg_matr_name[256];
    char arg_is_neg_name[256];
    char arg_mask_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_FRegArg(arg_vrb_name, arg_vrb, 0);
    NM6407_DisasmList_IsTrans(arg_matr_first_name, arg_matr_first);
    NM6407_DisasmList_FRegArgPairP(arg_vrc_name, arg_vrc);
    NM6407_DisasmList_IsRetriveP(arg_matr_name, arg_matr, arg_vrc);
    NM6407_DisasmList_IsNeg(arg_is_neg_name, arg_is_neg);
    NM6407_DisasmList_IsMask(arg_mask_name, arg_mask);
    if ((arg_matr_first == 0x0) && (arg_mask == 0x0)){
      sprintf(FloatVector_dstr, "%s .matrix %s = %s %s * %s %s;", arg_cell_name, arg_vrd_name, arg_is_neg_name, arg_vrb_name, arg_matr_first_name, arg_matr_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "%s .matrix %s = %s %s %s * %s %s : %s;", arg_cell_name, arg_vrd_name, arg_mask_name, arg_is_neg_name, arg_vrb_name, arg_matr_first_name, arg_matr_name, arg_vrd_name);
    *size = 4;
    return FloatVector_dstr;
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e67e0000) == 0x086020000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_vrb = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_matr_first = (uint32_t)((ocode >> 9) & 0x1);
    uint32_t arg_vrc = (uint32_t)((ocode >> 10) & 0x3);
    uint32_t arg_matr = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_vra = (uint32_t)((ocode >> 13) & 0x7);
    uint32_t arg_sa = (uint32_t)((ocode >> 16) & 0x1);
    uint32_t arg_op_code = (uint32_t)((ocode >> 23) & 0x3);
    uint32_t arg_mask = (uint32_t)((ocode >> 27) & 0x3);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_vrb_name[256];
    char arg_matr_first_name[256];
    char arg_vrc_name[256];
    char arg_matr_name[256];
    char arg_vra_name[256];
    char arg_sa_name[256];
    char arg_mask_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_FRegArg(arg_vrb_name, arg_vrb, 0);
    NM6407_DisasmList_IsTrans(arg_matr_first_name, arg_matr_first);
    NM6407_DisasmList_FRegArgPairP(arg_vrc_name, arg_vrc);
    NM6407_DisasmList_IsRetriveP(arg_matr_name, arg_matr, arg_vrc);
    NM6407_DisasmList_FRegArg(arg_vra_name, arg_vra, 0);
    NM6407_DisasmList_IsRetrive(arg_sa_name, arg_sa, arg_vra);
    NM6407_DisasmList_IsMask(arg_mask_name, arg_mask);
    if ((arg_op_code == 0x0)){
      sprintf(FloatVector_dstr, "%s .matrix %s = %s  %s* %s %s  + %s;", arg_cell_name, arg_vrd_name, arg_mask_name, arg_vrb_name, arg_matr_first_name, arg_matr_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1)){
      sprintf(FloatVector_dstr, "%s .matrix %s = %s -%s* %s %s  + %s;", arg_cell_name, arg_vrd_name, arg_mask_name, arg_vrb_name, arg_matr_first_name, arg_matr_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2)){
      sprintf(FloatVector_dstr, "%s .matrix %s = %s  %s* %s %s  - %s;", arg_cell_name, arg_vrd_name, arg_mask_name, arg_vrb_name, arg_matr_first_name, arg_matr_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3)){
      sprintf(FloatVector_dstr, "%s .matrix %s = %s -%s* %s %s  - %s;", arg_cell_name, arg_vrd_name, arg_mask_name, arg_vrb_name, arg_matr_first_name, arg_matr_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e6780000) == 0x082000000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_vrb = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrc = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_sb = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_tmp = (uint32_t)((ocode >> 13) & 0xF);
    uint32_t arg_data_type = (uint32_t)((ocode >> 17) & 0x3);
    uint32_t arg_is_neg = (uint32_t)((ocode >> 23) & 0x1);
    uint32_t arg_tmp2 = (uint32_t)((ocode >> 24) & 0x1);
    uint32_t arg_mask = (uint32_t)((ocode >> 27) & 0x3);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_vrb_name[256];
    char arg_vrc_name[256];
    char arg_sb_name[256];
    char arg_data_type_name[256];
    char arg_is_neg_name[256];
    char arg_mask_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_FRegArg(arg_vrb_name, arg_vrb, 0);
    NM6407_DisasmList_FRegArg(arg_vrc_name, arg_vrc, 0);
    NM6407_DisasmList_IsRetrive(arg_sb_name, arg_sb, arg_vrc);
    NM6407_DisasmList_DataType(arg_data_type_name, arg_data_type);
    NM6407_DisasmList_IsNeg(arg_is_neg_name, arg_is_neg);
    NM6407_DisasmList_IsMask(arg_mask_name, arg_mask);
    sprintf(FloatVector_dstr, "%s %s %s =  %s  %s  %s * %s : %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_is_neg_name, arg_vrb_name, arg_sb_name, arg_vrd_name);
    *size = 4;
    return FloatVector_dstr;
    if ((arg_mask == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s =  %s  %s * %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_is_neg_name, arg_vrb_name, arg_sb_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "instruction_3.2");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e6780000) == 0x084000000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_mgc = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrb = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_sb = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_vra = (uint32_t)((ocode >> 13) & 0x7);
    uint32_t arg_we = (uint32_t)((ocode >> 16) & 0x1);
    uint32_t arg_data_type = (uint32_t)((ocode >> 17) & 0x3);
    uint32_t arg_op_code = (uint32_t)((ocode >> 23) & 0x3);
    uint32_t arg_mask = (uint32_t)((ocode >> 27) & 0x3);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_mgc_name[256];
    char arg_vrb_name[256];
    char arg_sb_name[256];
    char arg_vra_name[256];
    char arg_data_type_name[256];
    char arg_mask_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_IsSetMask(arg_mgc_name, arg_mgc);
    NM6407_DisasmList_FRegArg(arg_vrb_name, arg_vrb, 0);
    NM6407_DisasmList_IsRetrive(arg_sb_name, arg_sb, arg_vrb);
    NM6407_DisasmList_FRegArg(arg_vra_name, arg_vra, 0);
    NM6407_DisasmList_DataType(arg_data_type_name, arg_data_type);
    NM6407_DisasmList_IsMask(arg_mask_name, arg_mask);
    if ((arg_op_code == 0x0) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = %s  %s + %s : %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = %s  %s - %s : %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = %s -%s + %s : %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = %s -%s - %s : %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x0) && (arg_mask == 0x0) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s =  %s + %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1) && (arg_mask == 0x0) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s =  %s - %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2) && (arg_mask == 0x0) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = -%s + %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3) && (arg_mask == 0x0) && (arg_we == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = -%s - %s %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x0) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s  %s + %s : %s %s;", arg_cell_name, arg_data_type_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s  %s - %s : %s %s;", arg_cell_name, arg_data_type_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s -%s + %s : %s %s;", arg_cell_name, arg_data_type_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s -%s - %s : %s %s;", arg_cell_name, arg_data_type_name, arg_mask_name, arg_vra_name, arg_sb_name, arg_vrd_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x0) && (arg_mask == 0x0) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s + %s %s;", arg_cell_name, arg_data_type_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1) && (arg_mask == 0x0) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s - %s %s;", arg_cell_name, arg_data_type_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2) && (arg_mask == 0x0) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s -%s + %s %s;", arg_cell_name, arg_data_type_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3) && (arg_mask == 0x0) && (arg_we == 0x0)){
      sprintf(FloatVector_dstr, "%s %s -%s - %s %s;", arg_cell_name, arg_data_type_name, arg_vra_name, arg_sb_name, arg_mgc_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "instruction_3.3");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e6780000) == 0x086000000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_vrc = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrb = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_sb = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_vra = (uint32_t)((ocode >> 13) & 0x7);
    uint32_t arg_sa = (uint32_t)((ocode >> 16) & 0x1);
    uint32_t arg_data_type = (uint32_t)((ocode >> 17) & 0x3);
    uint32_t arg_op_code = (uint32_t)((ocode >> 23) & 0x3);
    uint32_t arg_mask = (uint32_t)((ocode >> 27) & 0x3);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_vrc_name[256];
    char arg_vrb_name[256];
    char arg_sb_name[256];
    char arg_vra_name[256];
    char arg_sa_name[256];
    char arg_data_type_name[256];
    char arg_mask_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_FRegArg(arg_vrc_name, arg_vrc, 0);
    NM6407_DisasmList_FRegArg(arg_vrb_name, arg_vrb, 0);
    NM6407_DisasmList_IsRetrive(arg_sb_name, arg_sb, arg_vrb);
    NM6407_DisasmList_FRegArg(arg_vra_name, arg_vra, 0);
    NM6407_DisasmList_IsRetrive(arg_sa_name, arg_sa, arg_vra);
    NM6407_DisasmList_DataType(arg_data_type_name, arg_data_type);
    NM6407_DisasmList_IsMask(arg_mask_name, arg_mask);
    if ((arg_op_code == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s = %s  %s * %s + %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vrc_name, arg_sb_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x1)){
      sprintf(FloatVector_dstr, "%s %s %s = %s -%s * %s + %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vrc_name, arg_sb_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x2)){
      sprintf(FloatVector_dstr, "%s %s %s = %s  %s * %s - %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vrc_name, arg_sb_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_op_code == 0x3)){
      sprintf(FloatVector_dstr, "%s %s %s = %s -%s * %s - %s;", arg_cell_name, arg_data_type_name, arg_vrd_name, arg_mask_name, arg_vrc_name, arg_sb_name, arg_sa_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e2380000) == 0x080080000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_cell = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_tmp_var = (uint32_t)((ocode >> 6) & 0x3F);
    uint32_t arg_rep_src = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_rep_cnt = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_tmp_bit1 = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_addr = (uint32_t)((ocode >> 26) & 0x7);
    char arg_cell_name[256];
    char arg_vrd_name[256];
    char arg_rep_cnt_name[256];
    char arg_addr_name[256];
    NM6407_DisasmList_CellNum(arg_cell_name, arg_cell);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_RepVal(arg_rep_cnt_name, arg_rep_cnt);
    NM6407_DisasmList_MAddrMode(arg_addr_name, arg_addr, arg_ari, 0);
    if ((arg_rep_src == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s = [%s];", arg_cell_name, arg_rep_cnt_name, arg_vrd_name, arg_addr_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_rep_src == 0x1)){
      sprintf(FloatVector_dstr, "%s rep vlen %s = [%s];", arg_cell_name, arg_vrd_name, arg_addr_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e2380000) == 0x082080000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_tmp0 = (uint32_t)((ocode >> 0) & 0x3F);
    uint32_t arg_cell_s = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrs = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_rep_src = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_rep_cnt = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_tmp_bit1 = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_addr = (uint32_t)((ocode >> 26) & 0x7);
    char arg_cell_s_name[256];
    char arg_vrs_name[256];
    char arg_rep_src_name[256];
    char arg_rep_cnt_name[256];
    char arg_addr_name[256];
    NM6407_DisasmList_CellNum(arg_cell_s_name, arg_cell_s);
    NM6407_DisasmList_FRegArg(arg_vrs_name, arg_vrs, 0);
    NM6407_DisasmList_RepVal(arg_rep_src_name, arg_rep_src);
    NM6407_DisasmList_RepVal(arg_rep_cnt_name, arg_rep_cnt);
    NM6407_DisasmList_MAddrMode(arg_addr_name, arg_addr, arg_ari, 0);
    if ((arg_rep_src == 0x0)){
      sprintf(FloatVector_dstr, "%s %s [%s] = %s;", arg_cell_s_name, arg_rep_cnt_name, arg_addr_name, arg_vrs_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_rep_src == 0x1)){
      sprintf(FloatVector_dstr, "%s rep vlen [%s] = %s;", arg_cell_s_name, arg_addr_name, arg_vrs_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e2380000) == 0x080100000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_df = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_sf = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 6) & 0x3F);
    uint32_t arg_rep_src = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_rep_cnt = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_tmp_bit1 = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_addr = (uint32_t)((ocode >> 26) & 0x7);
    char arg_df_name[256];
    char arg_sf_name[256];
    char arg_rep_cnt_name[256];
    char arg_addr_name[256];
    NM6407_DisasmList_PackFormat(arg_df_name, arg_df);
    NM6407_DisasmList_PackFormat(arg_sf_name, arg_sf);
    NM6407_DisasmList_RepVal(arg_rep_cnt_name, arg_rep_cnt);
    NM6407_DisasmList_MAddrMode(arg_addr_name, arg_addr, arg_ari, 0);
    if ((arg_rep_src == 0x0)){
      sprintf(FloatVector_dstr, "fpu %s .packer = [%s] with %s <= %s;", arg_rep_cnt_name, arg_addr_name, arg_df_name, arg_sf_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_rep_src == 0x1)){
      sprintf(FloatVector_dstr, "fpu rep vlen .packer = [%s] with %s <= %s;", arg_addr_name, arg_df_name, arg_sf_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e2380000) == 0x082100000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 0) & 0xFFF);
    uint32_t arg_rep_src = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_rep_cnt = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_tmp_bit1 = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_ari = (uint32_t)((ocode >> 22) & 0x7);
    uint32_t arg_addr = (uint32_t)((ocode >> 26) & 0x7);
    char arg_rep_cnt_name[256];
    char arg_addr_name[256];
    NM6407_DisasmList_RepVal(arg_rep_cnt_name, arg_rep_cnt);
    NM6407_DisasmList_MAddrMode(arg_addr_name, arg_addr, arg_ari, 0);
    if ((arg_rep_src == 0x0)){
      sprintf(FloatVector_dstr, "fpu %s [%s] = .packer;", arg_rep_cnt_name, arg_addr_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_rep_src == 0x1)){
      sprintf(FloatVector_dstr, "fpu rep vlen [%s] = .packer;", arg_addr_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e1f80000) == 0x080400000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_celld = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_cells = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrs1 = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_tmp0 = (uint32_t)((ocode >> 12) & 0x7F);
    uint32_t arg_tmp2 = (uint32_t)((ocode >> 25) & 0xF);
    char arg_celld_name[256];
    char arg_vrd_name[256];
    char arg_cells_name[256];
    char arg_vrs1_name[256];
    NM6407_DisasmList_CellNum(arg_celld_name, arg_celld);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_CellNum(arg_cells_name, arg_cells);
    NM6407_DisasmList_FRegArg(arg_vrs1_name, arg_vrs1, 0);
    sprintf(FloatVector_dstr, "%s %s = %s %s;", arg_celld_name, arg_vrd_name, arg_cells_name, arg_vrs1_name);
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e1f80000) == 0x080c00000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_celld = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_cells = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrs1 = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_ms = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_vrs0 = (uint32_t)((ocode >> 13) & 0x7);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 16) & 0x7);
    uint32_t arg_tmp2 = (uint32_t)((ocode >> 25) & 0xF);
    char arg_celld_name[256];
    char arg_vrd_name[256];
    char arg_cells_name[256];
    char arg_vrs1_name[256];
    char arg_ms_name[256];
    char arg_vrs0_name[256];
    NM6407_DisasmList_CellNum(arg_celld_name, arg_celld);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_CellNum(arg_cells_name, arg_cells);
    NM6407_DisasmList_FRegArg(arg_vrs1_name, arg_vrs1, 0);
    NM6407_DisasmList_MaskType(arg_ms_name, arg_ms);
    NM6407_DisasmList_FRegArg(arg_vrs0_name, arg_vrs0, 0);
    sprintf(FloatVector_dstr, "%s %s = %s %s mask ? %s : %s;", arg_celld_name, arg_vrd_name, arg_cells_name, arg_ms_name, arg_vrs1_name, arg_vrs0_name);
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e1f81000) == 0x081400000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_df = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_sf = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_cells = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrs1 = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 13) & 0x3F);
    uint32_t arg_tmp2 = (uint32_t)((ocode >> 25) & 0xF);
    char arg_df_name[256];
    char arg_sf_name[256];
    char arg_cells_name[256];
    char arg_vrs1_name[256];
    NM6407_DisasmList_PackFormat(arg_df_name, arg_df);
    NM6407_DisasmList_PackFormat(arg_sf_name, arg_sf);
    NM6407_DisasmList_CellNum(arg_cells_name, arg_cells);
    NM6407_DisasmList_FRegArg(arg_vrs1_name, arg_vrs1, 0);
    sprintf(FloatVector_dstr, "%s .packer = %s with %s <= %s;", arg_cells_name, arg_vrs1_name, arg_df_name, arg_sf_name);
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e1f81000) == 0x081401000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_df = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_sf = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_cells = (uint32_t)((ocode >> 6) & 0x7);
    uint32_t arg_vrs1 = (uint32_t)((ocode >> 9) & 0x7);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 13) & 0x3F);
    uint32_t arg_tmp2 = (uint32_t)((ocode >> 25) & 0xF);
    char arg_df_name[256];
    char arg_sf_name[256];
    char arg_cells_name[256];
    char arg_vrs1_name[256];
    NM6407_DisasmList_PackFormat(arg_df_name, arg_df);
    NM6407_DisasmList_PackFormat(arg_sf_name, arg_sf);
    NM6407_DisasmList_CellNum(arg_cells_name, arg_cells);
    NM6407_DisasmList_FRegArgPair(arg_vrs1_name, arg_vrs1);
    sprintf(FloatVector_dstr, "%s .packer = (%s) with %s <= %s;", arg_cells_name, arg_vrs1_name, arg_df_name, arg_sf_name);
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e1f80040) == 0x081c00040)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_celld = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_tmp0 = (uint32_t)((ocode >> 7) & 0x1F);
    uint32_t arg_rep_src = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_rep_cnt = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_tmpbit0 = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 25) & 0xF);
    char arg_celld_name[256];
    char arg_vrd_name[256];
    char arg_rep_cnt_name[256];
    NM6407_DisasmList_CellNum(arg_celld_name, arg_celld);
    NM6407_DisasmList_FRegArgPair(arg_vrd_name, arg_vrd);
    NM6407_DisasmList_RepVal(arg_rep_cnt_name, arg_rep_cnt);
    if ((arg_rep_src == 0x0)){
      sprintf(FloatVector_dstr, "%s %s (%s) = .packer;", arg_celld_name, arg_rep_cnt_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_rep_src == 0x1)){
      sprintf(FloatVector_dstr, "%s rep vlen (%s) = .packer;", arg_celld_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x0e1f80040) == 0x081c00000)){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_celld = (uint32_t)((ocode >> 0) & 0x7);
    uint32_t arg_vrd = (uint32_t)((ocode >> 3) & 0x7);
    uint32_t arg_tmp0 = (uint32_t)((ocode >> 7) & 0x1F);
    uint32_t arg_rep_src = (uint32_t)((ocode >> 12) & 0x1);
    uint32_t arg_rep_cnt = (uint32_t)((ocode >> 13) & 0x1F);
    uint32_t arg_tmpbit0 = (uint32_t)((ocode >> 18) & 0x1);
    uint32_t arg_tmp1 = (uint32_t)((ocode >> 25) & 0xF);
    char arg_celld_name[256];
    char arg_vrd_name[256];
    char arg_rep_cnt_name[256];
    NM6407_DisasmList_CellNum(arg_celld_name, arg_celld);
    NM6407_DisasmList_FRegArgDst(arg_vrd_name, arg_vrd, 0);
    NM6407_DisasmList_RepVal(arg_rep_cnt_name, arg_rep_cnt);
    if ((arg_rep_src == 0x0)){
      sprintf(FloatVector_dstr, "%s %s %s = .packer;", arg_celld_name, arg_rep_cnt_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    if ((arg_rep_src == 0x1)){
      sprintf(FloatVector_dstr, "%s rep vlen %s = .packer;", arg_celld_name, arg_vrd_name);
      *size = 4;
      return FloatVector_dstr;
    }
    sprintf(FloatVector_dstr, "");
    *size = 4;
    return FloatVector_dstr;
    bin += 4;
  }
  sprintf(FloatVector_dstr, "undef inst");
  *size = 4;
  return FloatVector_dstr;
};

char Main_dstr[1024];
char* Main_DisAssembly(char *bin, int* size)
{
  int int_size;
  if (((BIN(uint32_t) & 0x00) == 0x00) && (_Scalar_GetInstNum((BIN(uint32_t) >> 0) & 0x0FFFFFFFFl))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_iscalar = (uint32_t)((ocode >> 0) & 0x0FFFFFFFFl);
    sprintf(Main_dstr, "%s", Scalar_DisAssembly((char*)(&arg_iscalar), &int_size));
    *size = 4;
    return Main_dstr;
    bin += 4;
  }
  if (((BIN(uint64_t) & 0x00) == 0x00) && (_Scalar64_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFFFFFFFFFFFFFFl))){
    uint64_t ocode = BIN(uint64_t);
    uint64_t arg_iscalar64 = ((ocode >> 0) & 0xFFFFFFFFFFFFFFFFl);
    sprintf(Main_dstr, "%s", Scalar64_DisAssembly((char*)(&arg_iscalar64), &int_size));
    *size = 8;
    return Main_dstr;
    bin += 8;
  }
  if (((BIN(uint32_t) & 0x00) == 0x00) && (_Vector_GetInstNum((BIN(uint32_t) >> 0) & 0x0FFFFFFFFl))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ivec = (uint32_t)((ocode >> 0) & 0x0FFFFFFFFl);
    sprintf(Main_dstr, "%s", Vector_DisAssembly((char*)(&arg_ivec), &int_size));
    *size = 4;
    return Main_dstr;
    bin += 4;
  }
  if (((BIN(uint32_t) & 0x00) == 0x00) && (_Float_Vector_GetInstNum((BIN(uint32_t) >> 0) & 0x0FFFFFFFFl))){
    uint32_t ocode = BIN(uint32_t);
    uint32_t arg_ifvec = (uint32_t)((ocode >> 0) & 0x0FFFFFFFFl);
    sprintf(Main_dstr, "%s", FloatVector_DisAssembly((char*)(&arg_ifvec), &int_size));
    *size = 4;
    return Main_dstr;
    bin += 4;
  }
  if (((BIN(uint64_t) & 0x00) == 0x00) && (_FloatVector64_GetInstNum((BIN(uint64_t) >> 0) & 0xFFFFFFFFFFFFFFFFl))){
    uint64_t ocode = BIN(uint64_t);
    uint64_t arg_ifvec64 = ((ocode >> 0) & 0xFFFFFFFFFFFFFFFFl);
    sprintf(Main_dstr, "%s", FloatVector64_DisAssembly((char*)(&arg_ifvec64), &int_size));
    *size = 8;
    return Main_dstr;
    bin += 8;
  }
  sprintf(Main_dstr, "undef inst");
  *size = 4;
  return Main_dstr;
};

char* disasm(char *bin, int* size)
{
  return Main_DisAssembly(bin, size);
};

void DevDisasm(CPUArchState* env, char* disasm_buf,uint32_t aCurPc)
{
  uint64_t opcode;
  char* disasm_code;
  int size = 0;
  static int i = 0;

  opcode = helper_mem_ld64(env, (aCurPc+i)<<2);

  disasm_code = disasm((char *)&opcode, &size);
  
  if (size == 4)
  {
    sprintf(disasm_buf, "%08X          %08X\t%s\t", aCurPc + i, LO_WRD(opcode), disasm_code);
    if (use_gdb && !use_cont)
        i = 0;
    else
        i = !i;
  }
  else
  {
    i = 0;
    sprintf(disasm_buf, "%08X %08X %08X\t%s\t", aCurPc, HI_WRD(opcode), LO_WRD(opcode), disasm_code);
  }
}


void PrintDisasmLine(CPUArchState* env, uint32_t aCurPc, uint32_t aTicks)
{
  char* sptr;
  char disasm_str[512];
  static int32_t prev_tick = -1;

  DevDisasm(env, disasm_str,aCurPc);
  if (aTicks > (prev_tick + 1))
    printf("%05d %s\n", aTicks - (aTicks - prev_tick - 1), disasm_str);
  else 
    printf("%05d %s\n", aTicks, disasm_str);
  prev_tick = aTicks;
  fflush(stdout);
}

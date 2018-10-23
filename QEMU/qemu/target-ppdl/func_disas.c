#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wformat-zero-length"

#include <stdio.h>
#include <stdint.h>
#include "qemu-common.h"
#include "exec/cpu_ldst.h" // cpu_ldsb_code

#define OPCODE(type) (type)ocode
#define BIN(type) *((type*)(bin))
// output 64-bits data
// low 32 bits of the 64-bits word
#define LO_WRD(val) (uint32_t)(val&((uint32_t)(-1)))
// hight 32 bits of the 64-bits word
#define HI_WRD(val) (uint32_t)(val>>32)
#define DECODER_CLASS EVM

void EVM_DisasmList_ArithmOps(char* out_buf,uint32 idx,uint32 arg_a,uint32 arg_b,uint32 arg_c ){
  switch(idx){
    case 0: sprintf(out_buf,"STOP"); break;
    case 1: sprintf(out_buf,"ADD"); break;
    case 2: sprintf(out_buf,"MUL"); break;
    case 3: sprintf(out_buf,"SUB"); break;
    case 4: sprintf(out_buf,"DIV"); break;
    case 5: sprintf(out_buf,"SDIV"); break;
    case 6: sprintf(out_buf,"MOD"); break;
    case 7: sprintf(out_buf,"SMOD"); break;
    case 8: sprintf(out_buf,"ADDMOD"); break;
    case 9: sprintf(out_buf,"MULMOD"); break;
    case 10: sprintf(out_buf,"EXP"); break;
    case 11: sprintf(out_buf,"SIGNEXTEND"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM_DisasmList_CompareLogOps(char* out_buf,uint32 idx,uint32 arg_a,uint32 arg_b ){
  switch(idx){
    case 0: sprintf(out_buf,"LT"); break;
    case 1: sprintf(out_buf,"GT"); break;
    case 2: sprintf(out_buf,"SLT"); break;
    case 3: sprintf(out_buf,"SGT"); break;
    case 4: sprintf(out_buf,"EQ"); break;
    case 5: sprintf(out_buf,"ISZERO"); break;
    case 6: sprintf(out_buf,"AND"); break;
    case 7: sprintf(out_buf,"OR"); break;
    case 8: sprintf(out_buf,"XOR"); break;
    case 9: sprintf(out_buf,"NOT"); break;
    case 10: sprintf(out_buf,"BYTE"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM_DisasmList_MemOps(char* out_buf,uint32 idx ){
  switch(idx){
    case 0: sprintf(out_buf,"POP"); break;
    case 1: sprintf(out_buf,"MLOAD"); break;
    case 2: sprintf(out_buf,"MSTORE"); break;
    case 3: sprintf(out_buf,"MSTORE8"); break;
    case 4: sprintf(out_buf,"SLOAD"); break;
    case 5: sprintf(out_buf,"SSTORE"); break;
    case 6: sprintf(out_buf,"JUMP"); break;
    case 7: sprintf(out_buf,"JUMPI"); break;
    case 8: sprintf(out_buf,"PC"); break;
    case 9: sprintf(out_buf,"MSIZE"); break;
    case 10: sprintf(out_buf,"GAS"); break;
    case 11: sprintf(out_buf,"JUMPDEST"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM_DisasmList_AccountsData(char* out_buf,uint32 idx ){
  switch(idx){
    case 0: sprintf(out_buf,"ADDRESS"); break;
    case 1: sprintf(out_buf,"BALANCE"); break;
    case 2: sprintf(out_buf,"ORIGIN"); break;
    case 3: sprintf(out_buf,"CALLER"); break;
    case 4: sprintf(out_buf,"CALLVALUE"); break;
    case 5: sprintf(out_buf,"CALLDATALOAD"); break;
    case 6: sprintf(out_buf,"CALLDATASIZE"); break;
    case 7: sprintf(out_buf,"CALLDATACOPY"); break;
    case 8: sprintf(out_buf,"CODESIZE"); break;
    case 9: sprintf(out_buf,"CODECOPY"); break;
    case 10: sprintf(out_buf,"GASPRICE"); break;
    case 11: sprintf(out_buf,"EXTCODESIZE"); break;
    case 12: sprintf(out_buf,"EXTCODECOPY"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM_DisasmList_BlockChain(char* out_buf,uint32 idx ){
  switch(idx){
    case 0: sprintf(out_buf,"BLOCKHASH"); break;
    case 1: sprintf(out_buf,"COINBASE"); break;
    case 2: sprintf(out_buf,"TIMESTAMP"); break;
    case 3: sprintf(out_buf,"NUMBER"); break;
    case 4: sprintf(out_buf,"DIFFICULTY"); break;
    case 5: sprintf(out_buf,"GASLIMIT"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM_DisasmList_SystemOps(char* out_buf,uint32 idx ){
  switch(idx){
    case 0: sprintf(out_buf,"CREATE"); break;
    case 1: sprintf(out_buf,"CALL"); break;
    case 2: sprintf(out_buf,"CALLCODE"); break;
    case 3: sprintf(out_buf,"RETURN"); break;
    case 4: sprintf(out_buf,"DELEGATECALL"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
#define SARG(aidx) aidx
inline int CheckNull_ArithmOps(uint32 aIdx){
  return 1;
}
inline int CheckNull_CompareLogOps(uint32 aIdx){
  return 1;
}
inline int CheckNull_MemOps(uint32 aIdx){
  return 1;
}
inline int CheckNull_AccountsData(uint32 aIdx){
  return 1;
}
inline int CheckNull_BlockChain(uint32 aIdx){
  return 1;
}
inline int CheckNull_SystemOps(uint32 aIdx){
  return 1;
}
inline int EVM_Main_GetInstNum(uint32 ocode){
    if (  ((OPCODE(uint8)&0x0f0) == 0x0f0)   && CheckNull_SystemOps((ocode>>0) & 0xF) ){ return 1;}//$syscall
    if (  ((OPCODE(uint8)&0x0ff) == 0x0fa)  ){ return 2;}//STATICCALL
    if (  ((OPCODE(uint8)&0x0ff) == 0x0fd)  ){ return 3;}//REVERT
    if (  ((OPCODE(uint8)&0x0ff) == 0x0ff)  ){ return 4;}//SUICIDE
    if (  ((OPCODE(uint8)&0x0f0) == 0x040)   && CheckNull_BlockChain((ocode>>0) & 0xF) ){ return 5;}//$gas_opcode
    if (  ((OPCODE(uint8)&0x0f0) == 0x030)   && CheckNull_AccountsData((ocode>>0) & 0xF) ){ return 6;}//$opcode
    if (  ((OPCODE(uint8)&0x0e0) == 0x060)  ){ return 7;}//PUSH$count
    if (  ((OPCODE(uint8)&0x0f0) == 0x080)  ){ return 8;}//DUP$count
    if (  ((OPCODE(uint8)&0x0f0) == 0x090)  ){ return 9;}//SWAP$count
    if (  ((OPCODE(uint8)&0x0f8) == 0x0a0)  ){ return 10;}//LOG$count
    if (  ((OPCODE(uint8)&0x0f0) == 0x050)   && CheckNull_MemOps((ocode>>0) & 0xF) ){ return 11;}//$opcode
    if (  ((OPCODE(uint8)&0x0f0) == 0x00)   && CheckNull_ArithmOps((ocode>>0) & 0xF) ){ return 12;}//$opcode
    if (  ((OPCODE(uint8)&0x0f0) == 0x010)   && CheckNull_CompareLogOps((ocode>>0) & 0xF) ){ return 13;}//$opcode
    if (  ((OPCODE(uint8)&0x0ff) == 0x020)  ){ return 14;}//SHA3
    else{ return 0; }
  }
char EVM_Main_dstr[1024];
char* EVM_Main_DisAssembly(char *bin,int* size)
{
  int int_size;
  if( ((BIN(uint8)&0x0f0) == 0x0f0)  && CheckNull_SystemOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_syscall = (uint32) ((ocode>>0)&0xF);
    char arg_syscall_name[256];
    EVM_DisasmList_SystemOps(arg_syscall_name,arg_syscall);
    sprintf(EVM_Main_dstr,"%s",arg_syscall_name);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x0fa)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"STATICCALL");
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x0fd)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"REVERT");
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x0ff)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"SUICIDE");
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x040)  && CheckNull_BlockChain((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_gas_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_gas_opcode_name[256];
    EVM_DisasmList_BlockChain(arg_gas_opcode_name,arg_gas_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_gas_opcode_name);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x030)  && CheckNull_AccountsData((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    EVM_DisasmList_AccountsData(arg_opcode_name,arg_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0e0) == 0x060)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0x1F);
    sprintf(EVM_Main_dstr,"PUSH0x%x",arg_count);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x080)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0xF);
    sprintf(EVM_Main_dstr,"DUP%d",arg_count);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x090)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0xF);
    sprintf(EVM_Main_dstr,"SWAP%d",arg_count);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f8) == 0x0a0)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0x7);
    sprintf(EVM_Main_dstr,"LOG%d",arg_count);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x050)  && CheckNull_MemOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    EVM_DisasmList_MemOps(arg_opcode_name,arg_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x00)  && CheckNull_ArithmOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    EVM_DisasmList_ArithmOps(arg_opcode_name,arg_opcode,0,0,0);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x010)  && CheckNull_CompareLogOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    EVM_DisasmList_CompareLogOps(arg_opcode_name,arg_opcode,0,0);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x020)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"SHA3");
    *size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  sprintf(EVM_Main_dstr,"undef inst");
  *size = 4;
  return EVM_Main_dstr;
};

char* disasm(char *bin,int* size)
{
  return EVM_Main_DisAssembly(bin,size);
};
int EVM_GetInstructNum(uint64 wrd){ return EVM_Main_GetInstNum((uint8)wrd);}

void DevDisasm(CPUArchState* env, char* disasm_buf,uint32_t aCurPc)
{
  uint64_t opcode;
  char* disasm_code;
  int size = 0;

  opcode = cpu_ldsb_code(env, aCurPc);

  disasm_code = disasm((char *)&opcode, &size);
  
  if (size == 4)
  {
    sprintf(disasm_buf, "%08X          %08X\t%s\t", aCurPc, LO_WRD(opcode), disasm_code);
  }
  else
  {
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

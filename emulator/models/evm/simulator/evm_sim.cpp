#include "evm_sim.h"

const char *reg_0 = "pc";
const char *reg_1 = "cur_addr";
const char *reg_2 = "caller_addr";
const char *reg_3 = "origin_addr";
const char *reg_4 = "gas_price";
const char *reg_5 = "gas_available";
const char *reg_6 = "code_size";
const char *reg_7 = "ext_code_size";
const char *reg_8 = "inp_data_size";
const char *reg_9 = "log_ptr";
const char *var_10 = "sp";
const char *var_11 = "CoinBase";
const char *var_12 = "TimeStamp";
const char *var_13 = "Number";
const char *var_14 = "Difficulty";
const char *var_15 = "GasLimit";

const tDRegister EVM_regs[16] = {
  {reg_0,4,0,0},
  {reg_1,20,0,0},
  {reg_2,20,0,0},
  {reg_3,20,0,0},
  {reg_4,4,0,0},
  {reg_5,4,0,0},
  {reg_6,32,0,0},
  {reg_7,32,0,0},
  {reg_8,32,0,0},
  {reg_9,4,0,0},
  {var_10,11,0,0},
  {var_11,12,0,0},
  {var_12,13,0,0},
  {var_13,14,0,0},
  {var_14,15,0,0},
  {var_15,16,0,0},
};


const tDMemBus EVM_membus[] = {
  {"prog_bus",4,4},
};


const tDProcCfg EVM_ProcCfg = {
  16,EVM_regs,
  1,EVM_membus,
  0,NULL,
  0,NULL,
};

void EVM::DisasmList_ArithmOps(char* out_buf,uint32 idx,uint32 arg_a,uint32 arg_b,uint32 arg_c ){
  switch(idx){
    case 0: sprintf(out_buf,"STOP"); break;
    case 1: sprintf(out_buf,"ADD"); break;
    case 2: sprintf(out_buf,"MUL"); break;
    case 3: sprintf(out_buf,"SUB"); break;
    case 4: sprintf(out_buf,"DIV"); break;
    case 5: sprintf(out_buf,"MOD"); break;
    case 6: sprintf(out_buf,"SMOD"); break;
    case 7: sprintf(out_buf,"ADDMOD"); break;
    case 8: sprintf(out_buf,"MULMOD"); break;
    case 9: sprintf(out_buf,"EXP"); break;
    case 10: sprintf(out_buf,"SIGNEXTEND"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM::DisasmList_CompareLogOps(char* out_buf,uint32 idx,uint32 arg_a,uint32 arg_b ){
  switch(idx){
    case 0: sprintf(out_buf,"LT"); break;
    case 1: sprintf(out_buf,"GT"); break;
    case 2: sprintf(out_buf,"SLT"); break;
    case 3: sprintf(out_buf,"SGT"); break;
    case 4: sprintf(out_buf,"EQ"); break;
    case 5: sprintf(out_buf,"IZSERO"); break;
    case 6: sprintf(out_buf,"AND"); break;
    case 7: sprintf(out_buf,"OR"); break;
    case 8: sprintf(out_buf,"XOR"); break;
    case 9: sprintf(out_buf,"NOT"); break;
    case 10: sprintf(out_buf,"BYTE"); break;
    default: sprintf(out_buf,"wrong_code");
 break;  }
}
void EVM::DisasmList_MemOps(char* out_buf,uint32 idx ){
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
void EVM::DisasmList_AccountsData(char* out_buf,uint32 idx ){
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
void EVM::DisasmList_BlockChain(char* out_buf,uint32 idx ){
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
void EVM::DisasmList_SystemOps(char* out_buf,uint32 idx ){
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
void EVM::CheckList_ArithmOps(int aPipeNum,int aIdx,uint256 a,uint256 b,uint256 c){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
void EVM::LockList_ArithmOps(int aPipeNum,int aIdx,uint256 a,uint256 b,uint256 c){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
void EVM::UnLockList_ArithmOps(int aPipeNum,int aIdx,uint256 a,uint256 b,uint256 c){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
void EVM::LLink_ArithmOps(int aIdx,uint256 a,uint256 b,uint256 c,TCycleCount aCycleCount,int aLockAdd){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
TCycleCount EVM::ArithmOps_GetLock(int aPipeNum,int aIdx,uint256 a,uint256 b,uint256 c){
  TCycleCount ret_val = 0;
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
  return ret_val;
}
inline uint256 EVM::Get_ArithmOps(uint32 aIdx,uint256 a,uint256 b,uint256 c){
  switch (aIdx){
    case 0: return StopExec(); break; // value of the element 0 of the list
    case 1: return (SARG(a) + SARG(b)); break; // value of the element 1 of the list
    case 2: return (SARG(a) * SARG(b)); break; // value of the element 2 of the list
    case 3: return (SARG(a) - SARG(b)); break; // value of the element 3 of the list
    case 4: return DivOp(SARG(a),SARG(b)); break; // value of the element 4 of the list
    case 5: return GetModule(SARG(a),SARG(b)); break; // value of the element 5 of the list
    case 6: return GetModuleS(SARG(a),SARG(b)); break; // value of the element 6 of the list
    case 7: return GetModule(SARG(a) + SARG(b),SARG(c)); break; // value of the element 7 of the list
    case 8: return GetModule(SARG(a) * SARG(b),SARG(c)); break; // value of the element 8 of the list
    case 9: return GetExp(SARG(a),SARG(b)); break; // value of the element 9 of the list
    case 10: return SignExtend(SARG(a),SARG(b)); break; // value of the element 10 of the list
    default: return aIdx; break;
  };
  return 0;
}

void EVM::CheckList_CompareLogOps(int aPipeNum,int aIdx,uint256 a,uint256 b){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
void EVM::LockList_CompareLogOps(int aPipeNum,int aIdx,uint256 a,uint256 b){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
void EVM::UnLockList_CompareLogOps(int aPipeNum,int aIdx,uint256 a,uint256 b){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
void EVM::LLink_CompareLogOps(int aIdx,uint256 a,uint256 b,TCycleCount aCycleCount,int aLockAdd){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
}
TCycleCount EVM::CompareLogOps_GetLock(int aPipeNum,int aIdx,uint256 a,uint256 b){
  TCycleCount ret_val = 0;
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    default: break;
  }
  return ret_val;
}
inline uint256 EVM::Get_CompareLogOps(uint32 aIdx,uint256 a,uint256 b){
  switch (aIdx){
    case 0: return (SARG(a) < SARG(b)); break; // value of the element 0 of the list
    case 1: return (SARG(a) > SARG(b)); break; // value of the element 1 of the list
    case 2: return  ((int256)((SARG(a) <  ((int256)(SARG(b)))))); break; // value of the element 2 of the list
    case 3: return  ((int256)((SARG(a) >  ((int256)(SARG(b)))))); break; // value of the element 3 of the list
    case 4: return (SARG(a) == SARG(b)); break; // value of the element 4 of the list
    case 5: return (SARG(a) == 0); break; // value of the element 5 of the list
    case 6: return (SARG(a) & SARG(b)); break; // value of the element 6 of the list
    case 7: return (SARG(a) | SARG(b)); break; // value of the element 7 of the list
    case 8: return (SARG(a) ^ SARG(b)); break; // value of the element 8 of the list
    case 9: return (~SARG(a)); break; // value of the element 9 of the list
    case 10: return ByteFromWord(SARG(a),SARG(b)); break; // value of the element 10 of the list
    default: return aIdx; break;
  };
  return 0;
}

void EVM::CheckList_MemOps(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    default: break;
  }
}
void EVM::LockList_MemOps(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    default: break;
  }
}
void EVM::UnLockList_MemOps(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    default: break;
  }
}
void EVM::LLink_MemOps(int aIdx,TCycleCount aCycleCount,int aLockAdd){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    default: break;
  }
}
TCycleCount EVM::MemOps_GetLock(int aPipeNum,int aIdx){
  TCycleCount ret_val = 0;
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    default: break;
  }
  return ret_val;
}
inline uint32 EVM::Get_MemOps(uint32 aIdx){
  switch (aIdx){
    case 0: return 0; break; // value of the element 0 of the list
    case 1: return 1; break; // value of the element 1 of the list
    case 2: return 2; break; // value of the element 2 of the list
    case 3: return 3; break; // value of the element 3 of the list
    case 4: return 4; break; // value of the element 4 of the list
    case 5: return 5; break; // value of the element 5 of the list
    case 6: return 6; break; // value of the element 6 of the list
    case 7: return 7; break; // value of the element 7 of the list
    case 8: return 8; break; // value of the element 8 of the list
    case 9: return 9; break; // value of the element 9 of the list
    case 10: return 10; break; // value of the element 10 of the list
    case 11: return 11; break; // value of the element 11 of the list
    default: return aIdx; break;
  };
  return 0;
}

void EVM::CheckList_AccountsData(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    case 12:
     break; // value of the element 12 of the list
    default: break;
  }
}
void EVM::LockList_AccountsData(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    case 12:
     break; // value of the element 12 of the list
    default: break;
  }
}
void EVM::UnLockList_AccountsData(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    case 12:
     break; // value of the element 12 of the list
    default: break;
  }
}
void EVM::LLink_AccountsData(int aIdx,TCycleCount aCycleCount,int aLockAdd){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    case 12:
     break; // value of the element 12 of the list
    default: break;
  }
}
TCycleCount EVM::AccountsData_GetLock(int aPipeNum,int aIdx){
  TCycleCount ret_val = 0;
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    case 6:
     break; // value of the element 6 of the list
    case 7:
     break; // value of the element 7 of the list
    case 8:
     break; // value of the element 8 of the list
    case 9:
     break; // value of the element 9 of the list
    case 10:
     break; // value of the element 10 of the list
    case 11:
     break; // value of the element 11 of the list
    case 12:
     break; // value of the element 12 of the list
    default: break;
  }
  return ret_val;
}
inline uint256 EVM::Get_AccountsData(uint32 aIdx){
  switch (aIdx){
    case 0: return cur_addr; break; // value of the element 0 of the list
    case 1: return GetBalance(Pop()); break; // value of the element 1 of the list
    case 2: return origin_addr; break; // value of the element 2 of the list
    case 3: return caller_addr; break; // value of the element 3 of the list
    case 4: return CallValue(); break; // value of the element 4 of the list
    case 5: return GetInputData(); break; // value of the element 5 of the list
    case 6: return inp_data_size; break; // value of the element 6 of the list
    case 7: return CallDataCopy(Pop(),Pop(),Pop()); break; // value of the element 7 of the list
    case 8: return code_size; break; // value of the element 8 of the list
    case 9: return CodeCopy(Pop(),Pop(),Pop()); break; // value of the element 9 of the list
    case 10: return gas_price; break; // value of the element 10 of the list
    case 11: return ext_code_size; break; // value of the element 11 of the list
    case 12: return ExtCodeCopy(Pop(),Pop(),Pop(),Pop()); break; // value of the element 12 of the list
    default: return aIdx; break;
  };
  return 0;
}

void EVM::CheckList_BlockChain(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    default: break;
  }
}
void EVM::LockList_BlockChain(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    default: break;
  }
}
void EVM::UnLockList_BlockChain(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    default: break;
  }
}
void EVM::LLink_BlockChain(int aIdx,TCycleCount aCycleCount,int aLockAdd){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    default: break;
  }
}
TCycleCount EVM::BlockChain_GetLock(int aPipeNum,int aIdx){
  TCycleCount ret_val = 0;
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    case 5:
     break; // value of the element 5 of the list
    default: break;
  }
  return ret_val;
}
inline uint256 EVM::Get_BlockChain(uint32 aIdx){
  switch (aIdx){
    case 0: return BlockChainHash(Pop()); break; // value of the element 0 of the list
    case 1: return CoinBase; break; // value of the element 1 of the list
    case 2: return TimeStamp; break; // value of the element 2 of the list
    case 3: return Number; break; // value of the element 3 of the list
    case 4: return Difficulty; break; // value of the element 4 of the list
    case 5: return GasLimit; break; // value of the element 5 of the list
    default: return aIdx; break;
  };
  return 0;
}

void EVM::CheckList_SystemOps(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    default: break;
  }
}
void EVM::LockList_SystemOps(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    default: break;
  }
}
void EVM::UnLockList_SystemOps(int aPipeNum,int aIdx){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    default: break;
  }
}
void EVM::LLink_SystemOps(int aIdx,TCycleCount aCycleCount,int aLockAdd){
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    default: break;
  }
}
TCycleCount EVM::SystemOps_GetLock(int aPipeNum,int aIdx){
  TCycleCount ret_val = 0;
  switch (aIdx){
    case 0:
     break; // value of the element 0 of the list
    case 1:
     break; // value of the element 1 of the list
    case 2:
     break; // value of the element 2 of the list
    case 3:
     break; // value of the element 3 of the list
    case 4:
     break; // value of the element 4 of the list
    default: break;
  }
  return ret_val;
}
inline uint256 EVM::Get_SystemOps(uint32 aIdx){
  switch (aIdx){
    case 0: return CreateAccount(); break; // value of the element 0 of the list
    case 1: return MakeCall(); break; // value of the element 1 of the list
    case 2: return MakeCallCode(); break; // value of the element 2 of the list
    case 3: return Return(); break; // value of the element 3 of the list
    case 4: return DelegateCall(); break; // value of the element 4 of the list
    default: return aIdx; break;
  };
  return 0;
}

#define SARG(aidx) aidx
inline int EVM::CheckNull_ArithmOps(uint32 aIdx){
  return 1;
}
inline int EVM::CheckNull_CompareLogOps(uint32 aIdx){
  return 1;
}
inline int EVM::CheckNull_MemOps(uint32 aIdx){
  return 1;
}
inline int EVM::CheckNull_AccountsData(uint32 aIdx){
  return 1;
}
inline int EVM::CheckNull_BlockChain(uint32 aIdx){
  return 1;
}
inline int EVM::CheckNull_SystemOps(uint32 aIdx){
  return 1;
}
#undef SARG
int EVM::SetReg(int rnum,int anum,char* val){
  switch(rnum){
  case 0: pc = *((uint32*)val); UpdateRegs(); break;
  case 1: cur_addr = *((uint160*)val); UpdateRegs(); break;
  case 2: caller_addr = *((uint160*)val); UpdateRegs(); break;
  case 3: origin_addr = *((uint160*)val); UpdateRegs(); break;
  case 4: gas_price = *((uint32*)val); UpdateRegs(); break;
  case 5: gas_available = *((uint32*)val); UpdateRegs(); break;
  case 6: code_size = *((uint256*)val); UpdateRegs(); break;
  case 7: ext_code_size = *((uint256*)val); UpdateRegs(); break;
  case 8: inp_data_size = *((uint256*)val); UpdateRegs(); break;
  case 9: log_ptr = *((uint32*)val); UpdateRegs(); break;
  case 10: sp = *((uint32*)val); break;
  case 11: CoinBase = *((uint256*)val); break;
  case 12: TimeStamp = *((uint256*)val); break;
  case 13: Number = *((uint256*)val); break;
  case 14: Difficulty = *((uint256*)val); break;
  case 15: GasLimit = *((uint256*)val); break;
    default: return 0;
    }
  return 1;
}
int EVM::GetReg(int rnum,int anum,char* val){
  switch(rnum){

    case 0:
     *((uint32*)val) = pc;
    break;
    case 1:
     *((uint160*)val) = cur_addr;
    break;
    case 2:
     *((uint160*)val) = caller_addr;
    break;
    case 3:
     *((uint160*)val) = origin_addr;
    break;
    case 4:
     *((uint32*)val) = gas_price;
    break;
    case 5:
     *((uint32*)val) = gas_available;
    break;
    case 6:
     *((uint256*)val) = code_size;
    break;
    case 7:
     *((uint256*)val) = ext_code_size;
    break;
    case 8:
     *((uint256*)val) = inp_data_size;
    break;
    case 9:
     *((uint32*)val) = log_ptr;
    break;
    case 10:
     *((uint32*)val) = sp;
    break;
    case 11:
     *((uint256*)val) = CoinBase;
    break;
    case 12:
     *((uint256*)val) = TimeStamp;
    break;
    case 13:
     *((uint256*)val) = Number;
    break;
    case 14:
     *((uint256*)val) = Difficulty;
    break;
    case 15:
     *((uint256*)val) = GasLimit;
    break;
    default: return 0;
    }
  return 1;
}

int EVM::SetFifo(int fifo_num,char* data,int size){
  switch(fifo_num){
    default: return 0;
    }
  return 0;
}
int EVM::GetFifo(int fifo_num,char* data,int& size){
  switch(fifo_num){
    default: return 0;
    }
  return 0;
}
int EVM::SetMem(void *mem,int busnum,int addr,int size){
  switch(busnum){
    case 0: return prog_bus->setmem(mem,addr,size);
    default: return 0;
    }
  return 0;
  };
int EVM::GetMem(void *mem,int busnum,int addr,int size){
  switch(busnum){
    case 0: return prog_bus->getmem(mem,addr,size);
    default: return 0;
    }
  return 0;
};
int EVM::IsMemInRange(int addr,int size,int busnum){
  switch(busnum){
    case 0: return prog_bus->IsMemInRange(addr,size);
    default: return 0;
    }
  return 0;
};
int EVM::FillMem(uint32 aVal,int busnum,int addr,int size){
  switch(busnum){
    case 0: return prog_bus->fillmem(aVal,addr,size);
    default: return 0;
    }
  return 0;
};
int EVM::GetCellSize(int busnum,int addr){
  switch(busnum){
    case 0: return prog_bus->GetCellSize(addr);
    default: return 0;
    }
  return 0;
};
#define SARG(aidx) aidx
inline uint256 EVM::GetExp(uint256 a,uint256 b)
{
  uint8 i ;
  uint256 res  = 1;
  uint256 mul_fact  = SARG(a);
  ;
 for( i  = 0; i  < 256; i  = ( i  + 1)){
  ;
  if(SARG(b).range( i , i ) == 1)
  {
   res  = ( res  *  mul_fact );
  }
   mul_fact  = ( mul_fact  *  mul_fact );
  }
    return  res ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::Pop()
{
  uint256 ret ;
  uint32 sp_tmp  = sp;
  ;
  sp = (sp + 1);
   ret  = data_bus[ sp_tmp ];
    return  ret ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline void EVM::Push(uint256 val)
{
  ;
  data_bus[sp] = SARG(val);
  sp = (sp - 1);
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::SignExtend(uint256 a,uint256 b)
{
  ;
    return 0;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::ByteFromWord(uint256 a,uint256 b)
{
  uint32 start_bit  =  (uint32)(((SARG(a) * 8)).to_uint64());
  uint32 end_bit  = ( start_bit  + 7);
  ;
    return SARG(b).range( end_bit , start_bit );
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::GetModule(uint256 a,uint256 mod)
{
  uint256 div ;
  ;
  if(SARG(mod) == 0)
  {
    return 0;
  }
  else
  {
  ;
   div  = (SARG(a) / SARG(mod));
    return SARG(a) - ( div  * SARG(mod));
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::GetModuleS(uint256 a,uint256 mod)
{
  uint256 div ;
  ;
  if(SARG(mod) == 0)
  {
    return 0;
  }
  else
  {
  ;
   div  =  ((int256)((SARG(a) /  ((int256)(SARG(mod))))));
    return  ((int256)((SARG(a) -  ((int256)(( div  * SARG(mod)))))));
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::StopExec()
{
  ;
  CheckError("@");
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::DivOp(uint256 a,uint256 b)
{
  ;
  if(SARG(b) == 0)
  {
    return 0;
  }
  else
  {
    return SARG(a) / SARG(b);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::CallValue()
{
  ;
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::CallDataCopy(uint256 a,uint256 b,uint256 c)
{
  ;
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::CodeCopy(uint256 a,uint256 b,uint256 c)
{
  ;
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::ExtCodeCopy(uint256 a,uint256 b,uint256 c,uint256 d)
{
  ;
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::GetBalance(uint256 a)
{
  ;
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::GetInputData()
{
  uint32 addr_val  =  (uint32)((Pop()).to_uint64());
  uint256 inp_data  = input_data[ addr_val ];
  ;
    return  inp_data ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::BlockChainHash(uint256 a)
{
  ;
  CoinBase = 16;
  TimeStamp = 4096;
  Number = 0x1234543234LL;
  Difficulty = 4326179;
  GasLimit = 4096;
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::CreateAccount()
{
  uint256 a ;
  uint256 b ;
  uint256 c ;
  uint256 account ;
  ;
   a  = Pop();
   b  = Pop();
   c  = Pop();
   account  = 1193046;
    return  account ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::MakeCall()
{
  uint256 callGas  = Pop();
  uint256 address  = Pop();
  uint256 inOff  = Pop();
  uint256 inSize  = Pop();
  uint256 outOff  = Pop();
  uint256 outSize  = Pop();
  uint256 g  = Pop();
  uint256 call_res  = 0;
  ;
    return  call_res ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::MakeCallCode()
{
  uint256 a  = Pop();
  uint256 b  = Pop();
  uint256 c  = Pop();
  uint256 d  = Pop();
  uint256 e  = Pop();
  uint256 f  = Pop();
  uint256 g  = Pop();
  uint256 call_res  = 0;
  ;
    return  call_res ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::Return()
{
  uint256 a  = Pop();
  uint256 b  = Pop();
  ;
  StopExec();
    return  (uint256)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint256 EVM::DelegateCall()
{
  uint256 a  = Pop();
  uint256 b  = Pop();
  uint256 c  = Pop();
  uint256 d  = Pop();
  uint256 e  = Pop();
  uint256 f  = Pop();
  uint256 call_res  = 0;
  ;
    return  call_res ;
  return 0;
};
#undef SARG
inline int EVM::Main_decode(uint32 ocode){
  TMainInst* cur_inst;
  RUN_PIPE(MainPipe,0);
  switch(EVM_Main_GetInstNum(ocode)){
  case 1: // $syscall 
  {
      cur_inst->inst1.syscall = ((ocode>>0)&0xF);
      cur_inst->inum = 1;
  #define SARG(aidx) cur_inst->inst1.aidx
      {
  uint256 res ;
  ;
  if(SARG(syscall) != 3)
  {
  Push( res );
  }
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 2: // STATICCALL 
  {
      cur_inst->inum = 2;
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 3: // REVERT 
  {
      cur_inst->inum = 3;
  #define SARG(aidx) cur_inst->inst3.aidx
      {
  uint256 a  = Pop();
  uint256 b  = Pop();
  ;
  StopExec();
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 4: // SUICIDE 
  {
      cur_inst->inum = 4;
  #define SARG(aidx) cur_inst->inst4.aidx
      {
  uint256 a  = Pop();
  ;
  StopExec();
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 5: // $gas_opcode 
  {
      cur_inst->inst5.gas_opcode = ((ocode>>0)&0xF);
      cur_inst->inum = 5;
  #define SARG(aidx) cur_inst->inst5.aidx
      {
  uint256 res  = Get_BlockChain(SARG(gas_opcode));
  ;
  Push( res );
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 6: // $opcode 
  {
      cur_inst->inst6.opcode = ((ocode>>0)&0xF);
      cur_inst->inum = 6;
  #define SARG(aidx) cur_inst->inst6.aidx
      {
  uint256 res  = Get_AccountsData(SARG(opcode));
  ;
  if(((SARG(opcode) != 7) & (SARG(opcode) != 9)) & (SARG(opcode) != 12))
  {
  Push( res );
  }
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 7: // PUSH$count 
  {
      cur_inst->inst7.count = ((ocode>>0)&0x1F);
      cur_inst->inum = 7;
  #define SARG(aidx) cur_inst->inst7.aidx
      {
  uint32 i ;
  uint256 a  = 0;
  uint256 tmp ;
  uint32 cnt  = (SARG(count) + 1);
  ;
  is_pc_within_inst = 1;
 for( i  = 0; i  <  cnt ; i  = ( i  + 1)){
  ;
   tmp  = ((*prog_bus)[((pc +  i ) + 1)] & 255);
   a  = ( a  | pd_lsh( tmp ,(8 *  i )));
  }
  Push( a );
  pc = ((pc +  cnt ) + 1);
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 8: // DUP$count 
  {
      cur_inst->inst8.count = ((ocode>>0)&0xF);
      cur_inst->inum = 8;
  #define SARG(aidx) cur_inst->inst8.aidx
      {
  uint256 a ;
  ;
   a  = data_bus[(sp + (SARG(count) + 1))];
  Push( a );
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 9: // SWAP$count 
  {
      cur_inst->inst9.count = ((ocode>>0)&0xF);
      cur_inst->inum = 9;
  #define SARG(aidx) cur_inst->inst9.aidx
      {
  uint256 first_el  = data_bus[(sp + 1)];
  ;
  data_bus[(sp + 1)] = data_bus[((sp + SARG(count)) + 2)];
  data_bus[((sp + SARG(count)) + 2)] =  first_el ;
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 10: // LOG$count 
  {
      cur_inst->inst10.count = ((ocode>>0)&0x7);
      cur_inst->inum = 10;
  #define SARG(aidx) cur_inst->inst10.aidx
      {
  uint32 i ;
  uint256 l1_data  = Pop();
  uint256 l2_data  = Pop();
  ;
  log_bus[log_ptr] =  l1_data ;
  log_bus[(log_ptr + 1)] =  l2_data ;
 for( i  = 0; i  < SARG(count); i  = ( i  + 1)){
  ;
  log_bus[((log_ptr + 2) + SARG(count))] = Pop();
  }
  log_ptr = (SARG(count) + 2);
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 11: // $opcode 
  {
      cur_inst->inst11.opcode = ((ocode>>0)&0xF);
      cur_inst->inum = 11;
  #define SARG(aidx) cur_inst->inst11.aidx
      {
  uint32 addr_val ;
  uint256 data_val ;
  uint256 pc_val ;
  ;
  if(Get_MemOps(SARG(opcode)) < 8)
  {
   addr_val  =  (uint32)((Pop()).to_uint64());
  }
  switch( (uint32)(Get_MemOps(SARG(opcode))))
  {
    case 0:
  ;
  Pop();
    break;
    case 1:
  ;
   data_val  = data_bus[ addr_val ];
  Push( data_val );
    break;
    case 2:
  ;
   data_val  = Pop();
  data_bus[ addr_val ] =  data_val ;
    break;
    case 3:
  ;
   data_val  = data_bus[ addr_val ];
   data_val  = ((Pop() & 255) | ( data_val  & -256));
  data_bus[ addr_val ] =  data_val ;
    break;
    case 4:
  ;
   data_val  = storage_bus[ addr_val ];
  Push( data_val );
    break;
    case 5:
  ;
   data_val  = Pop();
  storage_bus[ addr_val ] =  data_val ;
    break;
    case 6:
  ;
  pc =  addr_val ;
  is_pc_within_inst = 1;
    break;
    case 7:
  ;
  if(Pop() != 0)
  {
  ;
  pc =  (uint32)( addr_val );
  is_pc_within_inst = 1;
  }
    break;
    case 8:
  ;
   data_val  =  (uint256)(pc);
  Push( data_val );
    break;
    case 9:
  ;
   data_val  =  (uint256)(mem_size);
  Push( data_val );
    break;
    case 10:
  ;
  Push( (uint256)(gas_available));
    break;
    case 11:
  ;
    break;
  }
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 12: // $opcode 
  {
      cur_inst->inst12.opcode = ((ocode>>0)&0xF);
      cur_inst->inum = 12;
  #define SARG(aidx) cur_inst->inst12.aidx
      {
  uint256 a ;
  uint256 b ;
  uint256 c ;
  uint256 res ;
  ;
   a  = Pop();
   b  = Pop();
   c  =  ( ((SARG(opcode) == 7) & (SARG(opcode) == 8)) ? (Pop()) : (0) );
   res  = Get_ArithmOps(SARG(opcode), a , b , c );
  Push( res );
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 13: // $opcode 
  {
      cur_inst->inst13.opcode = ((ocode>>0)&0xF);
      cur_inst->inum = 13;
  #define SARG(aidx) cur_inst->inst13.aidx
      {
  uint256 a ;
  uint256 b ;
  uint256 c ;
  uint256 res ;
  ;
   a  = Pop();
   b  =  ( ((SARG(opcode) == 5) || (SARG(opcode) == 9)) ? (0) : (Pop()) );
   res  = Get_CompareLogOps(SARG(opcode), a , b );
  Push( res );
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 14: // SHA3 
  {
      cur_inst->inum = 14;
  #define SARG(aidx) cur_inst->inst14.aidx
      {
  uint256 a ;
  uint256 b ;
  ;
   a  = Pop();
   b  = Pop();
  Push( (uint256)(0x1234543234LL));
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  default:
  cur_inst->inum = 0;
  SEND_PIPE(MainPipe,0)
  return 0;
  break;  } // end of iset Main decode
  return 1;
  }
inline int EVM::EVM_Main_GetInstNum(uint32 ocode){
    if (  ((OPCODE(uint8)&0x0f0) == 0x0f0)   && CheckNull_SystemOps((ocode>>0) & 0xF) ){ return 1;}//$syscall
    if (  ((OPCODE(uint8)&0x0ff) == 0x0fa)  ){ return 2;}//STATICCALL
    if (  ((OPCODE(uint8)&0x0ff) == 0x0fd)  ){ return 3;}//REVERT
    if (  ((OPCODE(uint8)&0x0ff) == 0x0ff)  ){ return 4;}//SUICIDE
    if (  ((OPCODE(uint8)&0x0f0) == 0x040)   && CheckNull_BlockChain((ocode>>0) & 0xF) ){ return 5;}//$gas_opcode
    if (  ((OPCODE(uint8)&0x0f0) == 0x030)   && CheckNull_AccountsData((ocode>>0) & 0xF) ){ return 6;}//$opcode
    if (  ((OPCODE(uint8)&0x0e0) == 0x060)  ){ return 7;}//PUSH$count
    if (  ((OPCODE(uint8)&0x0f0) == 0x080)  ){ return 8;}//DUP$count
    if (  ((OPCODE(uint8)&0x0f0) == 0x090)  ){ return 9;}//SWAP$count
    if (  ((OPCODE(uint8)&0x0f8) == 0x050)  ){ return 10;}//LOG$count
    if (  ((OPCODE(uint8)&0x0f0) == 0x050)   && CheckNull_MemOps((ocode>>0) & 0xF) ){ return 11;}//$opcode
    if (  ((OPCODE(uint8)&0x0f0) == 0x00)   && CheckNull_ArithmOps((ocode>>0) & 0xF) ){ return 12;}//$opcode
    if (  ((OPCODE(uint8)&0x0f0) == 0x010)   && CheckNull_CompareLogOps((ocode>>0) & 0xF) ){ return 13;}//$opcode
    if (  ((OPCODE(uint8)&0x0ff) == 0x020)  ){ return 14;}//SHA3
    else{ return 0; }
  }
  void EVM::update(){
  this->UpdateRegs();
  MainPipe.Update();
}
void EVM::Operate(){
  uint8 code  = (*prog_bus)[pc];
  ;
  is_pc_within_inst = 0;
  Main_decode( code );
  if(is_pc_within_inst == 0)
  {
  pc = (pc + 1);
  }
  // update registers
 };
void EVM::ResetDevice(){
  ;
  pc = 0;
  sp = 1024;
  log_ptr = 0;
  MainPipe.Reset();
  pc.ResetMutable();
  prog_bus->ResetMemMutable();
  update();// update registers
};
const tDProcCfg* EVM::GetCfg(){
  return &EVM_ProcCfg;
  };

int EVM::SetPc(uint32 val){
  pc = val;
  update();
  return 0;
}uint32 EVM::GetPc(int val){
  return (uint32)pc;
}
  void EVM::ClearMem(){
  prog_bus->ClearMem();
}
EVM::EVM(char* aName):TDevice(aName)
{
};
char* EVM::EVM_Main_DisAssembly(char *bin,int& size)
{
  int int_size;
  if( ((BIN(uint8)&0x0f0) == 0x0f0)  && CheckNull_SystemOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_syscall = (uint32) ((ocode>>0)&0xF);
    char arg_syscall_name[256];
    DisasmList_SystemOps(arg_syscall_name,arg_syscall);
    sprintf(EVM_Main_dstr,"%s",arg_syscall_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x0fa)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"STATICCALL");
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x0fd)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"REVERT");
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x0ff)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"SUICIDE");
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x040)  && CheckNull_BlockChain((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_gas_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_gas_opcode_name[256];
    DisasmList_BlockChain(arg_gas_opcode_name,arg_gas_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_gas_opcode_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x030)  && CheckNull_AccountsData((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    DisasmList_AccountsData(arg_opcode_name,arg_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0e0) == 0x060)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0x1F);
    sprintf(EVM_Main_dstr,"PUSH0x%x",arg_count);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x080)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0xF);
    sprintf(EVM_Main_dstr,"DUP%d",arg_count);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x090)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0xF);
    sprintf(EVM_Main_dstr,"SWAP%d",arg_count);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f8) == 0x050)){
    uint8 ocode= BIN(uint8);
    uint32 arg_count = (uint32) ((ocode>>0)&0x7);
    sprintf(EVM_Main_dstr,"LOG%d",arg_count);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x050)  && CheckNull_MemOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    DisasmList_MemOps(arg_opcode_name,arg_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x00)  && CheckNull_ArithmOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    DisasmList_ArithmOps(arg_opcode_name,arg_opcode,0,0,0);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x010)  && CheckNull_CompareLogOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    DisasmList_CompareLogOps(arg_opcode_name,arg_opcode,0,0);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0ff) == 0x020)){
    uint8 ocode= BIN(uint8);
    sprintf(EVM_Main_dstr,"SHA3");
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  sprintf(EVM_Main_dstr,"undef inst");
  size = 4;
  return EVM_Main_dstr;
};

char* EVM::disasm(char *bin,int& size)
{
  return EVM_Main_DisAssembly(bin,size);
};
int EVM::GetInstructNum(uint64 wrd){ return EVM_Main_GetInstNum((uint8)wrd);}
char* EVM::GetNameFromPtr(void* ptr){
  if(ptr == (void*)&pc){ return "pc";}
  if(ptr == (void*)&cur_addr){ return "cur_addr";}
  if(ptr == (void*)&caller_addr){ return "caller_addr";}
  if(ptr == (void*)&origin_addr){ return "origin_addr";}
  if(ptr == (void*)&gas_price){ return "gas_price";}
  if(ptr == (void*)&gas_available){ return "gas_available";}
  if(ptr == (void*)&code_size){ return "code_size";}
  if(ptr == (void*)&ext_code_size){ return "ext_code_size";}
  if(ptr == (void*)&inp_data_size){ return "inp_data_size";}
  if(ptr == (void*)&log_ptr){ return "log_ptr";}
  if(ptr == (void*)prog_bus){ return "prog_bus";}
  return NULL;
}// end of function

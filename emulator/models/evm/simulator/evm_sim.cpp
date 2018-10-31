#include "evm_sim.h"

const char *reg_0 = "pc";
const char *reg_1 = "cur_addr";
const char *reg_2 = "caller_addr";
const char *reg_3 = "origin_addr";
const char *reg_4 = "gas_price";
const char *reg_5 = "ext_code_size";
const char *reg_6 = "inp_data_size";
const char *reg_7 = "log_ptr";
const char *var_8 = "sp";
const char *var_9 = "gas_available$";
const char *var_10 = "data_bus$";
const char *var_11 = "stack_arr$";
const char *var_12 = "CoinBase";
const char *var_13 = "TimeStamp";
const char *var_14 = "Number";
const char *var_15 = "Difficulty";
const char *var_16 = "GasLimit";

const tDRegister EVM_regs[17] = {
  {reg_0,4,0,0},
  {reg_1,8,0,0},
  {reg_2,8,0,0},
  {reg_3,8,0,0},
  {reg_4,8,0,0},
  {reg_5,8,0,0},
  {reg_6,8,0,0},
  {reg_7,4,0,0},
  {var_8,4,0},
  {var_9,8,4},
  {var_10,1,1024},
  {var_11,8,2048},
  {var_12,8,0},
  {var_13,8,0},
  {var_14,8,0},
  {var_15,8,0},
  {var_16,8,0},
};


const tDMemBus EVM_membus[] = {
  {"prog_bus",4,4},
};


const tDProcCfg EVM_ProcCfg = {
  17,EVM_regs,
  1,EVM_membus,
  0,NULL,
  0,NULL,
};

void EVM::DisasmList_ArithmOps(char* out_buf,uint32 idx ){
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
void EVM::DisasmList_CompareLogOps(char* out_buf,uint32 idx ){
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
void EVM::CheckList_ArithmOps(int aPipeNum,int aIdx){
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
void EVM::LockList_ArithmOps(int aPipeNum,int aIdx){
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
void EVM::UnLockList_ArithmOps(int aPipeNum,int aIdx){
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
void EVM::LLink_ArithmOps(int aIdx,TCycleCount aCycleCount,int aLockAdd){
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
TCycleCount EVM::ArithmOps_GetLock(int aPipeNum,int aIdx){
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
inline uint64 EVM::Get_ArithmOps(uint32 aIdx){
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

void EVM::CheckList_CompareLogOps(int aPipeNum,int aIdx){
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
void EVM::LockList_CompareLogOps(int aPipeNum,int aIdx){
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
void EVM::UnLockList_CompareLogOps(int aPipeNum,int aIdx){
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
void EVM::LLink_CompareLogOps(int aIdx,TCycleCount aCycleCount,int aLockAdd){
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
TCycleCount EVM::CompareLogOps_GetLock(int aPipeNum,int aIdx){
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
inline uint64 EVM::Get_CompareLogOps(uint32 aIdx){
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
inline uint64 EVM::Get_MemOps(uint32 aIdx){
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
inline uint64 EVM::Get_AccountsData(uint32 aIdx){
  switch (aIdx){
    case 0: return GetAddress(); break; // value of the element 0 of the list
    case 1: return GetBalance(); break; // value of the element 1 of the list
    case 2: return GetOrigin(); break; // value of the element 2 of the list
    case 3: return GetCaller(); break; // value of the element 3 of the list
    case 4: return CallValue(); break; // value of the element 4 of the list
    case 5: return GetInputData(); break; // value of the element 5 of the list
    case 6: return CallDataSize(); break; // value of the element 6 of the list
    case 7: return CallDataCopy(); break; // value of the element 7 of the list
    case 8: return GetCodeSize(); break; // value of the element 8 of the list
    case 9: return CodeCopy(); break; // value of the element 9 of the list
    case 10: return GetGasPrice(); break; // value of the element 10 of the list
    case 11: return ExtCodeSize(); break; // value of the element 11 of the list
    case 12: return ExtCodeCopy(); break; // value of the element 12 of the list
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
inline uint64 EVM::Get_BlockChain(uint32 aIdx){
  switch (aIdx){
    case 0: return BlockChainHash(); break; // value of the element 0 of the list
    case 1: return GetCoinBase(); break; // value of the element 1 of the list
    case 2: return GetTimeStamp(); break; // value of the element 2 of the list
    case 3: return GetNumber(); break; // value of the element 3 of the list
    case 4: return GetDifficulty(); break; // value of the element 4 of the list
    case 5: return GetGasLimit(); break; // value of the element 5 of the list
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
inline uint64 EVM::Get_SystemOps(uint32 aIdx){
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
  case 1: cur_addr = *((uint64*)val); UpdateRegs(); break;
  case 2: caller_addr = *((uint64*)val); UpdateRegs(); break;
  case 3: origin_addr = *((uint64*)val); UpdateRegs(); break;
  case 4: gas_price = *((uint64*)val); UpdateRegs(); break;
  case 5: ext_code_size = *((uint64*)val); UpdateRegs(); break;
  case 6: inp_data_size = *((uint64*)val); UpdateRegs(); break;
  case 7: log_ptr = *((uint32*)val); UpdateRegs(); break;
  case 8: sp = *((uint32*)val); break;
  case 9: gas_available[anum] = *((uint64*)val); break;
  case 10: data_bus[anum] = *((uint8*)val); break;
  case 11: stack_arr[anum] = *((uint64*)val); break;
  case 12: CoinBase = *((uint64*)val); break;
  case 13: TimeStamp = *((uint64*)val); break;
  case 14: Number = *((uint64*)val); break;
  case 15: Difficulty = *((uint64*)val); break;
  case 16: GasLimit = *((uint64*)val); break;
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
     *((uint64*)val) = cur_addr;
    break;
    case 2:
     *((uint64*)val) = caller_addr;
    break;
    case 3:
     *((uint64*)val) = origin_addr;
    break;
    case 4:
     *((uint64*)val) = gas_price;
    break;
    case 5:
     *((uint64*)val) = ext_code_size;
    break;
    case 6:
     *((uint64*)val) = inp_data_size;
    break;
    case 7:
     *((uint32*)val) = log_ptr;
    break;
    case 8:
     *((uint32*)val) = sp;
    break;
    case 9:
     *((uint64*)val) = gas_available[anum];
    break;
    case 10:
     *((uint8*)val) = data_bus[anum];
    break;
    case 11:
     *((uint64*)val) = stack_arr[anum];
    break;
    case 12:
     *((uint64*)val) = CoinBase;
    break;
    case 13:
     *((uint64*)val) = TimeStamp;
    break;
    case 14:
     *((uint64*)val) = Number;
    break;
    case 15:
     *((uint64*)val) = Difficulty;
    break;
    case 16:
     *((uint64*)val) = GasLimit;
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
inline uint64 EVM::USEGAS(uint64 value)
{
  ;
 UseGas((TDevice*)this,SARG(value));
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetSingleBlockFromStack()
{
  uint32 i ;
  uint64 data_val  = 0;
  uint64 data_tmp  = stack_arr[(sp - 3)];
  ;
  sp = (sp - 4);
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   data_val  = ( data_val  | pd_lsh((pd_rsh( data_tmp ,(8 * (7 -  i ))) & 255), i ));
  }
    return  data_val ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::PushSingleBlockToStack(uint64 data_tmp)
{
  uint32 i ;
  uint64 data_val  = 0;
  ;
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   data_val  = ( data_val  | pd_lsh((pd_rsh(SARG(data_tmp),(8 *  i )) & 255),(8 * (7 -  i ))));
  }
  sp = (sp + 1);
  stack_arr[sp] =  data_val ;
  stack_arr[(sp + 1)] = 0;
  stack_arr[(sp + 2)] = 0;
  stack_arr[(sp + 3)] = 0;
  sp = (sp + 3);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::StopExec()
{
  ;
  CheckError("@");
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetExp()
{
  uint64 base  = stack_arr[sp];
  uint64 pow  = stack_arr[(sp - 1)];
  uint64 i ;
  uint64 res  = 1;
  ;
  USEGAS(10);
 for( i  = 0; i  <  pow ; i  = ( i  + 1)){
  ;
   res  = ( res  *  base );
  }
  sp = (sp - 1);
  stack_arr[sp] =  res ;
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::Pop()
{
  uint64 ret ;
  ;
   ret  = stack_arr[sp];
  sp = (sp - 1);
    return  ret ;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline void EVM::Push(uint64 val)
{
  ;
  sp = (sp + 1);
  stack_arr[sp] = SARG(val);
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::SignExtend()
{
  uint32 testBit ;
  uint32 end_bit ;
  uint64 number ;
  uint64 mask ;
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(5);
  sp = (sp - 1);
  if( a  < 31)
  {
  ;
   testBit  = ( (uint32)(( a  * 8)) + 7);
   end_bit  = ( testBit  + 1);
   mask  = (pd_lsh( (uint64)(1), testBit ) - 1);
  if( TBitVE< uint64 >( b , end_bit , testBit ) == 1)
  {
   number  = ( b  | (~ mask ));
  }
  else
  {
   number  = ( b  &  mask );
  }
  stack_arr[sp] =  number ;
    return  (uint64)(0);
  }
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::ByteFromWord()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  uint32 start_bit  =  (uint32)(((31 -  a ) * 8));
  uint32 end_bit  = ( start_bit  + 7);
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] =  TBitVE< uint64 >( b , end_bit , start_bit );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetModule()
{
  uint64 a  = stack_arr[sp];
  uint64 mod  = stack_arr[(sp - 1)];
  uint64 div ;
  ;
  USEGAS(5);
  sp = (sp - 1);
  if( mod  == 0)
  {
  ;
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  }
  else
  {
  ;
   div  = ( a  /  mod );
  stack_arr[sp] = ( a  - ( div  *  mod ));
    return  (uint64)(0);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetModuleAdd()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  uint64 base  = ( a  +  b );
  uint64 mod  = stack_arr[(sp - 2)];
  uint64 div ;
  ;
  USEGAS(8);
  sp = (sp - 2);
  if( mod  == 0)
  {
  ;
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  }
  else
  {
  ;
   div  = ( base  /  mod );
  stack_arr[sp] = ( base  - ( div  *  mod ));
    return  (uint64)(0);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetModuleMul()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  uint64 base  = ( a  *  b );
  uint64 mod  = stack_arr[(sp - 2)];
  uint64 div ;
  ;
  USEGAS(8);
  sp = (sp - 2);
  if( mod  == 0)
  {
  ;
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  }
  else
  {
  ;
   div  = ( base  /  mod );
  stack_arr[sp] = ( base  - ( div  *  mod ));
    return  (uint64)(0);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetModuleS()
{
  uint64 a  = stack_arr[sp];
  uint64 mod  = stack_arr[(sp - 1)];
  uint64 div ;
  uint64 sign ;
  uint1 is_signed  = ( ((int64)( a )) < 0);
  ;
  USEGAS(5);
  sp = (sp - 1);
   sign  =  ( ( is_signed  != 0) ? ( (uint64)((0 - 1))) : ( (uint64)(1)) );
  if( mod  == 0)
  {
  ;
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  }
  else
  {
  ;
   div  = ( a  /  mod );
  stack_arr[sp] = ( sign  * ( a  - ( div  *  mod )));
    return  (uint64)(0);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::StopOp()
{
  ;
  USEGAS(0);
  CheckError("@");
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::AddOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  +  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::SubOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  -  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::MulOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(5);
  sp = (sp - 1);
  stack_arr[sp] = ( a  *  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::DivOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(5);
  sp = (sp - 1);
  if( b  == 0)
  {
  ;
  stack_arr[sp] =  (uint64)(0);
  }
  else
  {
  ;
  stack_arr[sp] = ( a  /  b );
  }
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::DivOpS()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(5);
  sp = (sp - 1);
  if( b  == 0)
  {
  ;
  stack_arr[sp] =  (uint64)(0);
  }
  else
  {
  ;
  stack_arr[sp] =  ((int64)(( a  /  ((int64)( b )))));
  }
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::LtOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  <  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::LtOpS()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] =  ((int64)(( a  <  ((int64)( b )))));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GtOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  >  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GtOpS()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] =  ((int64)(( a  >  ((int64)( b )))));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::EqOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  ==  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::IsZeroOp()
{
  uint64 a  = stack_arr[sp];
  ;
  USEGAS(3);
  stack_arr[sp] = ( a  == 0);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::AndOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  &  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::OrOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  |  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::XorOp()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(3);
  sp = (sp - 1);
  stack_arr[sp] = ( a  ^  b );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::NotOp()
{
  uint64 a  = stack_arr[sp];
  ;
  USEGAS(3);
  stack_arr[sp] = (~ a );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::CallValue()
{
  ;
  USEGAS(2);
  sp = (sp + 1);
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::CallDataCopy()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  uint64 c  = stack_arr[(sp - 2)];
  ;
  USEGAS(3);
  sp = (sp - 3);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::CallDataSize()
{
  ;
  USEGAS(2);
  PushSingleBlockToStack(inp_data_size);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::CodeCopy()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  uint64 c  = stack_arr[(sp - 2)];
  ;
  USEGAS(3);
  sp = (sp - 3);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::ExtCodeSize()
{
  ;
  USEGAS(20);
  PushSingleBlockToStack(ext_code_size);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::ExtCodeCopy()
{
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  uint64 c  = stack_arr[(sp - 2)];
  uint64 d  = stack_arr[(sp - 3)];
  ;
  USEGAS(20);
  sp = (sp - 4);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetAddress()
{
  uint64 ca  = cur_addr;
  ;
  USEGAS(2);
  PushSingleBlockToStack( (uint64)( ca ));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetBalance()
{
  uint64 a  = stack_arr[sp];
  ;
  USEGAS(20);
  stack_arr[sp] =  (uint64)(0);
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetOrigin()
{
  uint64 oa  = origin_addr;
  ;
  USEGAS(2);
  PushSingleBlockToStack( (uint64)( oa ));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetCaller()
{
  uint64 ca  = caller_addr;
  ;
  USEGAS(2);
  PushSingleBlockToStack( (uint64)( ca ));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetInputData()
{
  uint32 addr_val  =  (uint32)(stack_arr[sp]);
  uint64 inp_data  = input_data[ addr_val ];
  ;
  USEGAS(3);
  stack_arr[sp] =  inp_data ;
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetElfSizeStub()
{
  ;
    return GetElfSize((TDevice*)this);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetCodeSize()
{
  uint64 elf_size  = GetElfSizeStub();
  ;
  USEGAS(2);
  PushSingleBlockToStack( elf_size );
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetGasPrice()
{
  uint64 gp  = gas_price;
  ;
  USEGAS(2);
  PushSingleBlockToStack( (uint64)( gp ));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::BlockChainHash()
{
  uint64 a  = stack_arr[sp];
  ;
  USEGAS(20);
  CoinBase = 16;
  TimeStamp = 4096;
  Number = 0x1234543234LL;
  Difficulty = 4326179;
  GasLimit = 4096;
  PushSingleBlockToStack( (uint64)(0));
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetCoinBase()
{
  ;
  USEGAS(2);
  PushSingleBlockToStack(CoinBase);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetTimeStamp()
{
  ;
  USEGAS(2);
  PushSingleBlockToStack(TimeStamp);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetNumber()
{
  ;
  USEGAS(2);
  PushSingleBlockToStack(Number);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetDifficulty()
{
  ;
  USEGAS(2);
  PushSingleBlockToStack(Difficulty);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::GetGasLimit()
{
  ;
  USEGAS(2);
  PushSingleBlockToStack(GasLimit);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::CreateAccount()
{
  uint64 endowment  = stack_arr[sp];
  uint64 initOff  = stack_arr[(sp - 1)];
  uint64 initSize  = stack_arr[(sp - 2)];
  uint64 account ;
  ;
  USEGAS(32000);
   account  = 1193046;
  sp = (sp - 2);
  stack_arr[sp] =  account ;
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::MakeCall()
{
  uint64 callGas  = stack_arr[sp];
  uint64 address  = stack_arr[(sp - 1)];
  uint64 value  = stack_arr[(sp - 2)];
  uint64 inOff  = stack_arr[(sp - 3)];
  uint64 inSize  = stack_arr[(sp - 4)];
  uint64 outOff  = stack_arr[(sp - 5)];
  uint64 outSize  = stack_arr[(sp - 6)];
  uint64 call_res  = 0;
  ;
  USEGAS(40);
  sp = (sp - 6);
  stack_arr[sp] =  call_res ;
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::MakeCallCode()
{
  uint64 callGas  = stack_arr[sp];
  uint64 address  = stack_arr[(sp - 1)];
  uint64 value  = stack_arr[(sp - 2)];
  uint64 inOff  = stack_arr[(sp - 3)];
  uint64 inSize  = stack_arr[(sp - 4)];
  uint64 outOff  = stack_arr[(sp - 5)];
  uint64 outSize  = stack_arr[(sp - 6)];
  uint64 call_res  = 0;
  ;
  USEGAS(40);
  sp = (sp - 6);
  stack_arr[sp] =  call_res ;
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::Return()
{
  ;
  USEGAS(0);
  StopExec();
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::DelegateCall()
{
  uint64 callGas  = stack_arr[sp];
  uint64 address  = stack_arr[(sp - 1)];
  uint64 inOff  = stack_arr[(sp - 2)];
  uint64 inSize  = stack_arr[(sp - 3)];
  uint64 outOff  = stack_arr[(sp - 4)];
  uint64 outSize  = stack_arr[(sp - 5)];
  uint64 call_res  = 0;
  ;
  USEGAS(40);
  sp = (sp - 5);
  stack_arr[sp] =  call_res ;
    return  (uint64)(0);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::ArithmStub(uint32 opcode)
{
  ;
 DoArithm((TDevice*)this,SARG(opcode));
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::CompareStub(uint32 opcode)
{
  ;
 DoCompare((TDevice*)this,SARG(opcode));
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::PushInst(uint32 cnt)
{
  uint32 i ;
  uint32 j ;
  uint64 a  = 0;
  uint64 tmp ;
  uint64 block_cnt  = 0;
  ;
  sp = (sp + 1);
 for( j  = 0; j  < (SARG(cnt) / 8); j  = ( j  + 1)){
  ;
   a  = 0;
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   tmp  = ((*prog_bus)[(pc + ((SARG(cnt) -  i ) - (8 *  j )))] & 255);
   a  = ( a  | pd_lsh( tmp ,(8 * (7 -  i ))));
  }
  stack_arr[(sp +  block_cnt )] =  a ;
   block_cnt  = ( block_cnt  + 1);
  }
  if((SARG(cnt) & 7) != 0)
  {
  ;
   a  = 0;
 for( i  = 0; i  < (SARG(cnt) & 7); i  = ( i  + 1)){
  ;
   tmp  = ((*prog_bus)[(pc + ((SARG(cnt) & 7) -  i ))] & 255);
   tmp  = pd_lsh( tmp ,(8 * (7 -  i )));
   a  = ( a  |  tmp );
  }
  stack_arr[(sp +  block_cnt )] =  a ;
   block_cnt  = ( block_cnt  + 1);
  }
 for( j  = ( j  + 1); j  < 4; j  = ( j  + 1)){
  ;
  stack_arr[(sp +  j )] =  (uint64)(0);
  }
  sp = (sp + 3);
    return 0;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::LogInst(uint32 count,uint32 log_ptr)
{
  uint32 i ;
  ;
 for( i  = 0; i  < SARG(count); i  = ( i  + 1)){
  ;
  log_bus[((SARG(log_ptr) + 2) + SARG(count))] = stack_arr[sp];
  sp = (sp - 1);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::MloadInst(uint32 addr_val)
{
  uint32 i ;
  uint32 j ;
  uint64 data_val[4] ;
  uint32 init_shift ;
  uint64 data_tmp ;
  ;
 for( j  = 3; ((int32)( j )) >= 0; j  = ( j  - 1)){
  ;
   data_val[ j ]  = 0;
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   data_tmp  = pd_lsh( (uint64)(data_bus[SARG(addr_val)]),(8 *  i ));
   data_val[ j ]  = ( data_val[ j ]  |  data_tmp );
  SARG(addr_val) = (SARG(addr_val) + 1);
  }
  }
  stack_arr[(sp + 1)] =  data_val[0] ;
  stack_arr[(sp + 2)] =  data_val[1] ;
  stack_arr[(sp + 3)] =  data_val[2] ;
  stack_arr[(sp + 4)] =  data_val[3] ;
  sp = (sp + 4);
    return 0;
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::MStoreInst(uint64 addr_val)
{
  uint32 i ;
  uint32 j ;
  uint64 data_val[4] ;
  uint64 data_tmp ;
  ;
   data_val[3]  = stack_arr[sp];
   data_val[2]  = stack_arr[(sp - 1)];
   data_val[1]  = stack_arr[(sp - 2)];
   data_val[0]  = stack_arr[(sp - 3)];
  sp = (sp - 4);
 for( j  = 3; ((int32)( j )) >= 0; j  = ( j  - 1)){
  ;
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   data_tmp  = (pd_rsh( data_val[ j ] ,(8 *  i )) & 255);
  data_bus[SARG(addr_val)] =  (uint8)( data_tmp );
  SARG(addr_val) = (SARG(addr_val) + 1);
  }
  }
  if(SARG(addr_val) > mem_size)
  {
  mem_size = SARG(addr_val);
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::MSizeOp()
{
  uint32 i ;
  uint64 data_tmp  =  (uint64)(mem_size);
  uint64 data_val  = 0;
  ;
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   data_val  = ( data_val  | pd_lsh((pd_rsh( data_tmp ,(8 *  i )) & 255),(8 * (7 -  i ))));
  }
  sp = (sp + 1);
  stack_arr[sp] =  data_val ;
  stack_arr[(sp + 1)] = 0;
  stack_arr[(sp + 2)] = 0;
  stack_arr[(sp + 3)] = 0;
  sp = (sp + 3);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::SwapOp(uint32 count)
{
  uint32 i ;
  uint32 offs ;
  uint64 first_el[4] ;
  ;
  USEGAS(3);
   first_el[3]  = stack_arr[(sp - 3)];
   first_el[2]  = stack_arr[(sp - 3)];
   first_el[1]  = stack_arr[(sp - 1)];
   first_el[0]  = stack_arr[sp];
 for( i  = 0; i  < 4; i  = ( i  + 1)){
  ;
   offs  = (sp - ((4 * (SARG(count) + 1)) +  i ));
  stack_arr[(sp -  i )] = stack_arr[ offs ];
  stack_arr[ offs ] =  first_el[ i ] ;
  }
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::PcOp()
{
  uint32 i ;
  uint64 data_tmp  =  (uint64)(pc);
  uint64 data_val  = 0;
  ;
 for( i  = 0; i  < 8; i  = ( i  + 1)){
  ;
   data_val  = ( data_val  | pd_lsh((pd_rsh( data_tmp ,(8 *  i )) & 255),(8 * (7 -  i ))));
  }
  sp = (sp + 1);
  stack_arr[sp] =  data_val ;
  stack_arr[(sp + 1)] = 0;
  stack_arr[(sp + 2)] = 0;
  stack_arr[(sp + 3)] = 0;
  sp = (sp + 3);
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::SaveToStorageStub(uint64 addr)
{
  ;
 SaveToStorage((TDevice*)this,SARG(addr));
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::LoadFromStorageStub(uint64 addr)
{
  ;
 LoadFromStorage((TDevice*)this,SARG(addr));
  return 0;
};
#undef SARG
#define SARG(aidx) aidx
inline uint64 EVM::KeccakAlgStub()
{
  uint32 a  = GetSingleBlockFromStack();
  uint32 b  = GetSingleBlockFromStack();
  ;
 KeccakAlg((TDevice*)this, a , b );
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
  ;
  Get_SystemOps(SARG(syscall));
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 2: // STATICCALL 
  {
      cur_inst->inum = 2;
  #define SARG(aidx) cur_inst->inst2.aidx
      {
  uint64 callGas  = stack_arr[sp];
  uint64 address  = stack_arr[(sp - 1)];
  uint64 value  = 0;
  uint64 inOff  = stack_arr[(sp - 2)];
  uint64 inSize  = stack_arr[(sp - 3)];
  uint64 outOff  = stack_arr[(sp - 4)];
  uint64 outSize  = stack_arr[(sp - 5)];
  uint64 call_res  = 0;
  ;
  USEGAS(40);
  sp = (sp - 5);
  stack_arr[sp] =  call_res ;
      }
  #undef SARG
  SEND_PIPE(MainPipe,0)
  return 8;
  } break;
  case 3: // REVERT 
  {
      cur_inst->inum = 3;
  #define SARG(aidx) cur_inst->inst3.aidx
      {
  uint64 a  = stack_arr[sp];
  uint64 b  = stack_arr[(sp - 1)];
  ;
  USEGAS(0);
  sp = (sp - 2);
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
  uint64 a  = stack_arr[sp];
  ;
  USEGAS(0);
  sp = (sp - 1);
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
  ;
  Get_BlockChain(SARG(gas_opcode));
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
  ;
  Get_AccountsData(SARG(opcode));
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
  ;
  USEGAS(3);
  PushInst(SARG(count) + 1);
  is_pc_const_changed = 1;
  pc = ((pc + SARG(count)) + 2);
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
  uint64 a ;
  ;
  USEGAS(3);
   a  = stack_arr[(sp - (SARG(count) + 1))];
  sp = (sp + 1);
  stack_arr[sp] =  a ;
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
  ;
  SwapOp(SARG(count));
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
  uint64 l1_data  = stack_arr[sp];
  uint64 l2_data  = stack_arr[(sp - 1)];
  uint32 m_ptr  =  (uint32)( l1_data );
  uint32 m_size  =  (uint32)( l2_data );
  ;
  USEGAS(375 + (SARG(count) * 375));
  LogInst(SARG(count), m_ptr );
  log_ptr = (SARG(count) + 2);
  sp = (sp - 2);
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
  uint32 i ;
  uint32 dec_cnt ;
  uint64 addr_val  = 0;
  uint32 init_shift ;
  uint64 data_val ;
  uint64 pc_val ;
  uint64 data_tmp ;
  ;
  if((Get_MemOps(SARG(opcode)) < 8) & (Get_MemOps(SARG(opcode)) != 0))
  {
  ;
   addr_val  = GetSingleBlockFromStack();
  }
  switch( (uint32)(Get_MemOps(SARG(opcode))))
  {
    case 0:
  ;
  USEGAS(2);
  sp = (sp - 4);
    break;
    case 1:
  ;
  USEGAS(3);
  MloadInst( addr_val );
    break;
    case 2:
  ;
  USEGAS(3);
  MStoreInst( addr_val );
    break;
    case 3:
  ;
  USEGAS(3);
   data_val  = stack_arr[(sp - 3)];
  sp = (sp - 4);
  data_bus[ addr_val ] =  (uint8)((pd_rsh( data_val ,(7 * 8)) & 255));
  if( addr_val  > mem_size)
  {
  mem_size =  addr_val ;
  }
    break;
    case 4:
  ;
  USEGAS(50);
  LoadFromStorageStub( addr_val );
    break;
    case 5:
  ;
  USEGAS(0);
  SaveToStorageStub( addr_val );
    break;
    case 6:
  ;
  USEGAS(8);
  pc =  addr_val ;
  is_pc_within_inst = 1;
    break;
    case 7:
  ;
  USEGAS(10);
  if(stack_arr[sp] != 0)
  {
  ;
  pc =  (uint32)( addr_val );
  is_pc_within_inst = 1;
  }
  sp = (sp - 1);
    break;
    case 8:
  ;
  USEGAS(2);
  PcOp();
    break;
    case 9:
  ;
  USEGAS(2);
  MSizeOp();
    break;
    case 10:
  ;
  USEGAS(2);
  sp = (sp + 1);
  stack_arr[sp] = gas_available[0];
  stack_arr[(sp + 1)] = gas_available[1];
  stack_arr[(sp + 2)] = gas_available[2];
  stack_arr[(sp + 3)] = gas_available[3];
  sp = (sp + 3);
    break;
    case 11:
  ;
  USEGAS(1);
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
  ;
  ArithmStub( (uint32)(Get_ArithmOps(SARG(opcode))));
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
  ;
  CompareStub( (uint32)(Get_CompareLogOps(SARG(opcode))));
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
  ;
  USEGAS(30);
  KeccakAlgStub();
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
    if (  ((OPCODE(uint8)&0x0f8) == 0x0a0)  ){ return 10;}//LOG$count
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
  is_pc_const_changed = 0;
  Main_decode( code );
  if((is_pc_within_inst == 0) & (is_pc_const_changed == 0))
  {
  pc = (pc + 1);
  }
  // update registers
 };
void EVM::ResetDevice(){
  ;
  pc = 0;
  sp = (0 - 1);
  log_ptr = 0;
 for(counter = 0;counter < 1024;counter = (counter + 1)){
  ;
  data_bus[counter] = 0;
  }
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
  if( ((BIN(uint8)&0x0f8) == 0x0a0)){
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
    DisasmList_ArithmOps(arg_opcode_name,arg_opcode);
    sprintf(EVM_Main_dstr,"%s",arg_opcode_name);
    size = 1;
    return EVM_Main_dstr;
    bin+=1;
  }
  if( ((BIN(uint8)&0x0f0) == 0x010)  && CheckNull_CompareLogOps((BIN(uint8)>>0) & 0xF)){
    uint8 ocode= BIN(uint8);
    uint32 arg_opcode = (uint32) ((ocode>>0)&0xF);
    char arg_opcode_name[256];
    DisasmList_CompareLogOps(arg_opcode_name,arg_opcode);
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
  if(ptr == (void*)&ext_code_size){ return "ext_code_size";}
  if(ptr == (void*)&inp_data_size){ return "inp_data_size";}
  if(ptr == (void*)&log_ptr){ return "log_ptr";}
  if(ptr == (void*)prog_bus){ return "prog_bus";}
  return NULL;
}// end of function

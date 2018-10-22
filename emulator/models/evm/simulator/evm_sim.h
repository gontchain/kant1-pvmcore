#ifndef DECLARE_EVM_H
#define DECLARE_EVM_H

#include <device.h>

extern uint64 KeccakAlg(TDevice* dev,uint32 offs,uint32 size);
extern uint64 GetElfSize(TDevice* dev);
extern void SaveToStorage(TDevice* dev,uint32 offs,uint64 value);
extern uint64 LoadFromStorage(TDevice* dev,uint32 offs);
// class EVM
class EVM: public TDevice
{
  void DisasmList_ArithmOps(char* out_buf,uint32 idx,uint32 arg_a,uint32 arg_b,uint32 arg_c );
  void DisasmList_CompareLogOps(char* out_buf,uint32 idx,uint32 arg_a,uint32 arg_b );
  void DisasmList_MemOps(char* out_buf,uint32 idx );
  void DisasmList_AccountsData(char* out_buf,uint32 idx );
  void DisasmList_BlockChain(char* out_buf,uint32 idx );
  void DisasmList_SystemOps(char* out_buf,uint32 idx );
  struct Main_tinst1{
      uint8 syscall;
    }/*Main_inst1*/;
  struct Main_tinst2{
    }/*Main_inst2*/;
  struct Main_tinst3{
    }/*Main_inst3*/;
  struct Main_tinst4{
    }/*Main_inst4*/;
  struct Main_tinst5{
      uint8 gas_opcode;
    }/*Main_inst5*/;
  struct Main_tinst6{
      uint8 opcode;
    }/*Main_inst6*/;
  struct Main_tinst7{
      uint8 count;
    }/*Main_inst7*/;
  struct Main_tinst8{
      uint8 count;
    }/*Main_inst8*/;
  struct Main_tinst9{
      uint8 count;
    }/*Main_inst9*/;
  struct Main_tinst10{
      uint8 count;
    }/*Main_inst10*/;
  struct Main_tinst11{
      uint8 opcode;
    }/*Main_inst11*/;
  struct Main_tinst12{
      uint8 opcode;
    }/*Main_inst12*/;
  struct Main_tinst13{
      uint8 opcode;
    }/*Main_inst13*/;
  struct Main_tinst14{
    }/*Main_inst14*/;
  struct TMainInst: public TInst{
    union{
      struct Main_tinst1 inst1;
      struct Main_tinst2 inst2;
      struct Main_tinst3 inst3;
      struct Main_tinst4 inst4;
      struct Main_tinst5 inst5;
      struct Main_tinst6 inst6;
      struct Main_tinst7 inst7;
      struct Main_tinst8 inst8;
      struct Main_tinst9 inst9;
      struct Main_tinst10 inst10;
      struct Main_tinst11 inst11;
      struct Main_tinst12 inst12;
      struct Main_tinst13 inst13;
      struct Main_tinst14 inst14;
    };
  };
public:
  RegMutable< uint32 >  pc;
  PD_REG< uint64 >  cur_addr;
  PD_REG< uint64 >  caller_addr;
  PD_REG< uint64 >  origin_addr;
  PD_REG< uint32 >  gas_price;
  PD_REG< uint64 >  ext_code_size;
  PD_REG< uint64 >  inp_data_size;
  PD_REG<uint64>  input_data[1024];
  PD_REG<uint64>  log_bus[1024];
  PD_REG< uint32 >  log_ptr;
  uint32  sp;
  uint1  is_pc_within_inst;
  uint1  is_pc_const_changed;
  uint32  gas_available;
  uint32  mem_size;
  uint8  data_bus[1024];
  uint64  stack_arr[2048];
  uint64  CoinBase;
  uint64  TimeStamp;
  uint64  Number;
  uint64  Difficulty;
  uint64  GasLimit;
  iMemInterface<uint32,uint32>* prog_bus;
  void CheckList_ArithmOps(int aPipeNum,int aIdx,uint64 a,uint64 b,uint64 c);
void LockList_ArithmOps(int aPipeNum,int aIdx,uint64 a,uint64 b,uint64 c);
void UnLockList_ArithmOps(int aPipeNum,int aIdx,uint64 a,uint64 b,uint64 c);
void LLink_ArithmOps(int aIdx,uint64 a,uint64 b,uint64 c,TCycleCount aCount,int aLockAdd = 0);
TCycleCount ArithmOps_GetLock(int aPipeNum,int aIdx,uint64 a,uint64 b,uint64 c);
inline uint64 Get_ArithmOps(uint32 aIdx,uint64 a,uint64 b,uint64 c);
  void CheckList_CompareLogOps(int aPipeNum,int aIdx,uint64 a,uint64 b);
void LockList_CompareLogOps(int aPipeNum,int aIdx,uint64 a,uint64 b);
void UnLockList_CompareLogOps(int aPipeNum,int aIdx,uint64 a,uint64 b);
void LLink_CompareLogOps(int aIdx,uint64 a,uint64 b,TCycleCount aCount,int aLockAdd = 0);
TCycleCount CompareLogOps_GetLock(int aPipeNum,int aIdx,uint64 a,uint64 b);
inline uint64 Get_CompareLogOps(uint32 aIdx,uint64 a,uint64 b);
  void CheckList_MemOps(int aPipeNum,int aIdx);
void LockList_MemOps(int aPipeNum,int aIdx);
void UnLockList_MemOps(int aPipeNum,int aIdx);
void LLink_MemOps(int aIdx,TCycleCount aCount,int aLockAdd = 0);
TCycleCount MemOps_GetLock(int aPipeNum,int aIdx);
inline uint32 Get_MemOps(uint32 aIdx);
  void CheckList_AccountsData(int aPipeNum,int aIdx);
void LockList_AccountsData(int aPipeNum,int aIdx);
void UnLockList_AccountsData(int aPipeNum,int aIdx);
void LLink_AccountsData(int aIdx,TCycleCount aCount,int aLockAdd = 0);
TCycleCount AccountsData_GetLock(int aPipeNum,int aIdx);
inline uint64 Get_AccountsData(uint32 aIdx);
  void CheckList_BlockChain(int aPipeNum,int aIdx);
void LockList_BlockChain(int aPipeNum,int aIdx);
void UnLockList_BlockChain(int aPipeNum,int aIdx);
void LLink_BlockChain(int aIdx,TCycleCount aCount,int aLockAdd = 0);
TCycleCount BlockChain_GetLock(int aPipeNum,int aIdx);
inline uint64 Get_BlockChain(uint32 aIdx);
  void CheckList_SystemOps(int aPipeNum,int aIdx);
void LockList_SystemOps(int aPipeNum,int aIdx);
void UnLockList_SystemOps(int aPipeNum,int aIdx);
void LLink_SystemOps(int aIdx,TCycleCount aCount,int aLockAdd = 0);
TCycleCount SystemOps_GetLock(int aPipeNum,int aIdx);
inline uint64 Get_SystemOps(uint32 aIdx);
inline int CheckNull_ArithmOps(uint32 aIdx);
inline int CheckNull_CompareLogOps(uint32 aIdx);
inline int CheckNull_MemOps(uint32 aIdx);
inline int CheckNull_AccountsData(uint32 aIdx);
inline int CheckNull_BlockChain(uint32 aIdx);
inline int CheckNull_SystemOps(uint32 aIdx);
  TPipeLine<TMainInst,0> MainPipe;
  virtual int SetReg(int rnum,int anum,char* val);
  virtual int GetReg(int rnum,int anum,char* val);
  virtual int SetFifo(int fifo_num,char* data,int size);
  virtual int GetFifo(int fifo_num,char* data,int& size);
  virtual int SetMem(void *mem,int busnum,int addr,int size);
  virtual int GetMem(void *mem,int busnum,int addr,int size);
  int IsMemInRange(int addr,int size,int busnum);
  int FillMem(uint32 aVal,int busnum,int addr,int size);
  int GetCellSize(int busnum,int addr);
inline uint64 StopExec();
inline uint64 GetExp(uint64 base,uint64 pow);
inline uint64 Pop();
inline void Push(uint64 val);
inline uint64 SignExtend(uint64 a,uint64 b);
inline uint64 ByteFromWord(uint64 a,uint64 b);
inline uint64 GetModule(uint64 a,uint64 mod);
inline uint64 GetModuleAM(uint64 a,uint64 mod);
inline uint64 GetModuleS(uint64 a,uint64 mod);
inline uint64 StopOp();
inline uint64 AddOp(uint64 a,uint64 b);
inline uint64 SubOp(uint64 a,uint64 b);
inline uint64 MulOp(uint64 a,uint64 b);
inline uint64 DivOp(uint64 a,uint64 b);
inline uint64 DivOpS(uint64 a,uint64 b);
inline uint64 LtOp(uint64 a,uint64 b);
inline uint64 LtOpS(uint64 a,uint64 b);
inline uint64 GtOp(uint64 a,uint64 b);
inline uint64 GtOpS(uint64 a,uint64 b);
inline uint64 EqOp(uint64 a,uint64 b);
inline uint64 IsZeroOp(uint64 a);
inline uint64 AndOp(uint64 a,uint64 b);
inline uint64 OrOp(uint64 a,uint64 b);
inline uint64 XorOp(uint64 a,uint64 b);
inline uint64 NotOp(uint64 a);
inline uint64 CallValue();
inline uint64 CallDataCopy(uint64 a,uint64 b,uint64 c);
inline uint64 CallDataSize();
inline uint64 CodeCopy(uint64 a,uint64 b,uint64 c);
inline uint64 ExtCodeSize();
inline uint64 ExtCodeCopy(uint64 a,uint64 b,uint64 c,uint64 d);
inline uint64 GetAddress();
inline uint64 GetBalance(uint64 a);
inline uint64 GetOrigin();
inline uint64 GetCaller();
inline uint64 GetInputData();
inline uint64 GetCodeSize();
inline uint64 GetGasPrice();
inline uint64 BlockChainHash(uint64 a);
inline uint64 GetCoinBase();
inline uint64 GetTimeStamp();
inline uint64 GetNumber();
inline uint64 GetDifficulty();
inline uint64 GetGasLimit();
inline uint64 CreateAccount(uint64 endowment,uint64 initOff,uint64 initSize);
inline uint64 MakeCall();
inline uint64 MakeCallCode();
inline uint64 Return();
inline uint64 DelegateCall();
inline uint64 PushInst(uint32 cnt);
inline uint64 LogInst(uint32 count,uint32 log_ptr);
inline uint64 MloadInst(uint32 addr_val);
inline uint64 MStoreInst(uint32 addr_val);
  inline int Main_decode(uint32 ocode);
  inline int EVM_Main_GetInstNum(uint32 ocode);
  void update();
  void Operate();
  void ResetDevice();
  virtual const tDProcCfg* GetCfg();
  virtual int SetPc(uint32 val);
  virtual uint32 GetPc(int val);
  void ClearMem();
// constructor: device initialisation routine
  EVM(char* aName = "");
  char EVM_Main_dstr[1024];
  char* EVM_Main_DisAssembly(char *bin,int& size);
  char* disasm(char *bin,int& size);
  virtual int GetInstructNum(uint64 wrd);
  virtual char* GetNameFromPtr(void* ptr);

};
#define DEV_CLASS EVM
#endif
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H

#include "threads_cfg.h"
#include "ppdl.h"

#ifdef WIN32
extern  THDL          Thread;
extern  DWORD         OwnerId;
extern  DWORD         ThreadId;
#else
extern  THDL          Thread;
extern  THDL         OwnerId;
extern  THDL         ThreadId;
#endif

extern  volatile int  IsRunned;
extern  volatile int  IsNoBreakPoints;
extern  TDevice       *MainDevice;

// these functions must be implemented by user
LIB_EXPORT extern void* Init(void * aParam);
LIB_EXPORT extern void  Destroy();

//LIB_EXPORT extern TDevice* GetDevCore(int aCoreNum);
// these functions are exported
#ifdef __cplusplus
extern "C" {
#endif

extern tDProcCfg* GetProcCfg();
extern int ProcGetMem(void *mem, int busnum, int addr, int size);
extern int ProcGetCellSize(int busnum, int addr);
extern void ProcClearMem();
extern int ProcSetMem(void *mem, int busnum, int addr, int size);
extern int ProcGetMemCellSize(int busnum, int addr);
extern int ProcDisAsm(char *str, int busnum, int addr, int size);
extern int ProcSetReg(int rnum, int anum, char* val);
extern int ProcSetFifo(int fifo_num, char* data, int size);
extern int ProcGetFifo(int fifo_num, char* data, int* size);
extern int Disassembly(char* str, int busnum, int aAddr, int aSize);
extern int ProcSetPc(uint32_t pc);
extern unsigned long ProcGetPc();
extern int ProcGetReg(int rnum, int anum, char* buf);
extern int ProcSetBreakPoint(unsigned long addr);
extern int ProcClearBreakPoint(unsigned long addr);
extern int ProcStart();
extern int ProcStop();
extern int ProcIsRun();
extern unsigned long ProcStepInto();
extern void ProcReset();
extern int GetRegIndexByName(char* aName);
extern void* InitSys(void * mParams);
extern tDProcCfg* GetProcCfg();

LIB_EXPORT extern int ProcGetMem(void *mem, int busnum, int addr, int size);
LIB_EXPORT extern tDisAsmArea* ProcLoadElf(char* aName);
LIB_EXPORT extern void GetNextErrors();
LIB_EXPORT extern TDbgInterface* CreateDevice(void * aParam = 0);
LIB_EXPORT extern void* InitSysChipMem(char* aBspName,unsigned long aFlags);
LIB_EXPORT extern int SysDestroy();
LIB_EXPORT extern void FindStackInAbs(char* aAbsFileName,char* aStackSect = ".stack");
LIB_EXPORT extern TDevice* GetDevCore(int aCoreNum);

#ifdef __cplusplus
}
#endif

extern void SingleClock();
extern void SkipCycle();

#define SIMULATION_STOP 0xB0

//#define     MY_LOG

#ifdef MY_LOG
#include <stdio.h>
extern FILE*  LogFile;
#endif

#endif

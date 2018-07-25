#include "system.h"
#include "assert.h"

// данный набор функций используется только для поддержки совместимости
// со старой версией отладчика PPDL-Debugger


tDProcCfg* McProcGetCfg(int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return (tDProcCfg*)dev->GetCfg();  
}

int GetNumCores()
{
  return DeviceList.GetCout();
}

LIB_EXPORT char* GetDevName(int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->GetDeviceName(); 
}

LIB_EXPORT tDisAsmArea* McProcLoadElf(char* aName,int aCoreNum)
{
  try
  {
	  TDevice* dev = GetDevCore(aCoreNum);
 	  return dev->LoadElf(aName);
  }
  catch(.../*exception &exc*/) // output exception
  {
    return 0;
  };
}

// get memory
LIB_EXPORT int McProcGetMem(void *mem,int busnum,int addr,int size,int aCoreNum)
{
	TDevice* dev = GetDevCore(aCoreNum);
  return dev->GetMem(mem,busnum,addr,size);
}

LIB_EXPORT int McProcGetCellSize(int busnum,int addr,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->GetCellSize(busnum,addr);
}

// clear all memory
LIB_EXPORT void McProcClearMem(int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  dev->ClearMem();
}

// set memory
int McProcSetMem(void *mem,int busnum,int addr,int size,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->SetMem(mem,busnum,addr,size);
}


// disassembly 
int McProcDisAsm(char *str,int busnum,int addr,int size,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->DisAssembly(str,busnum,addr,size);
}

int McProcSetReg(int rnum,int anum,unsigned long val,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->SetReg(rnum,anum,(char*)&val);
}

int McProcSetPc(uint32 pc,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  dev->SetPc(pc);
  return 1;
}

unsigned long McProcGetPc(int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->GetPc(0);
}

unsigned long McProcGetReg(int rnum,int anum,int aCoreNum) 
{
  TDevice* dev = GetDevCore(aCoreNum);
  int reg_bit_size = dev->GetCfg()->regs[rnum].type;

  if(reg_bit_size <=4)
  {
    unsigned long val;
    dev->GetReg(rnum,anum,(char*)&val);
    return val;
  }
  else
  {
    uint64 wlong_val;
    dev->GetReg(rnum,anum,(char*)&wlong_val);
    return (unsigned long)(wlong_val);
  }
}

int McProcSetBreakPoint(unsigned long addr,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->SetBreakPoint(addr);
}

int McProcClearBreakPoint(unsigned long addr,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  return dev->ClearBreakPoint(addr);
}


void McProcReset(int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  dev->Reset();
}

void McProcGetFifo(int aFifoNum,char* aData,int& aSize,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  dev->GetFifo(aFifoNum,aData,aSize);
}

void McProcSetFifo(int aFifoNum,char* aData,int aSize,int aCoreNum)
{
  TDevice* dev = GetDevCore(aCoreNum);
  dev->SetFifo(aFifoNum,aData,aSize);
}


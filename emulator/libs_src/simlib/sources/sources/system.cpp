#include "system.h"

// данный набор функций используется только для поддержки совместимости
// со старой версией отладчика PPDL-Debugger
tDisAsmArea* ProcLoadElf(char* aName)
{
  try
  {
    return MainDevice->LoadElf(aName);
  }
  catch(...)// exception &exc) // output exception
  {
    return 0;
  };
}

// get memory
int ProcGetMem(void *mem,int busnum,int addr,int size)
{
  return MainDevice->GetMem(mem,busnum,addr,size);
}

int ProcGetCellSize(int busnum,int addr)
{
  return MainDevice->GetCellSize(busnum,addr);
}

// clear all memory
void ProcClearMem()
{
  MainDevice->ClearMem();
}

// set memory
int ProcSetMem(void *mem,int busnum,int addr,int size)
{
  return MainDevice->SetMem(mem,busnum,addr,size);
}

// get size of the memory cells
int ProcGetMemCellSize(int busnum,int addr)
{
  return MainDevice->GetCellSize(busnum,addr);
}

// disassembly 
int ProcDisAsm(char *str,int busnum,int addr,int size)
{
  return MainDevice->DisAssembly(str,busnum,addr,size);
}

int ProcSetReg(int rnum,int anum,unsigned long val)
{
  return MainDevice->SetReg(rnum,anum,val);
}

int ProcSetPc(uint32 pc)
{
  MainDevice->SetPc(pc);
  return 1;
}

unsigned long ProcGetPc()
{
  return MainDevice->GetPc(0);
}

unsigned long ProcGetReg(int rnum,int anum) 
{
  return MainDevice->GetReg(rnum,anum);
}

int ProcSetBreakPoint(unsigned long addr)
{
  return MainDevice->SetBreakPoint(addr);
}

int ProcClearBreakPoint(unsigned long addr)
{
  return MainDevice->ClearBreakPoint(addr);
}

int ProcStart()
{
  MainDevice->Start();
  return 0;
}

int ProcStop()
{
  MainDevice->Stop();
  return 0;
}

int ProcIsRun()
{
  return MainDevice->IsRun();
}

unsigned long ProcStepInto()
{
  MainDevice->StepInto();
  unsigned long pcval = MainDevice->GetPc(0);
  return pcval;
}

void ProcReset()
{
  MainDevice->Reset();
}
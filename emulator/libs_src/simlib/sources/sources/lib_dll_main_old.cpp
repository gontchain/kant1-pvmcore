// lib_dll_main.cpp

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// INCLUDE Direction write in Makefile for simlib ""
// DIR_BASE = /home/us/common/Interstron/linux/simulat12
// DIR_HEADERS = include
// INCLUDE_HEADERS = -I$(INCLUDE_BASE)/$(DIR_HEADERS)

#include <_typeWinUnix.h>  // nod dependence (it isn't dependent)
#include <datatypes.h>     // nod dependence
#include <debug_structs.h> // nod dependence
#include <dbg_interface.h>
#include <deviceTest.h>

//#include <threads_cfg.h>
//#include <system.h>


// nod dependence (it isn't dependent)
//#include "./../../include/_typeWinUnix.h"
//#include "./../../include/datatypes.h" // nod dependence

// nod dependence (it isn't dependent)
//#include "./_typeWinUnix.h"
//#include "./datatypes.h" // nod dependence


//////////////////////////////////
// 

/*
////#include "includeInitSys.h"
//#include "./headers-lib/_typeWinUnix.h"
#include "./headers-lib/threads_cfg.h"
//#include "./headers-lib/system.h"


#include "./../include/datatypes.h"
#include "./../include/lists.h"
#include "./../include/pd_reg.h"  //
#include "./../include/pd_fifo.h" //
#include "./../include/flag.h"    //
#include  "./../include/pipes.h"  //
#include "./../include/libelf.h"  //
#include "./../include/debug_structs.h"  //
#include "./../include/dbg_interface.h"  //

#include "./../include/device.h"
*/


/*
class TDevice : public TDbgInterface 
{
public:
  TDevice() 
   {};
  ~TDevice() 
   {};

  // functions
protected:

  virtual char* disasm(char *bin,int& size)=0;  // ?
  virtual void ResetDevice(void)=0;             // ?
  virtual void update(void)=0;                  // ?

public:


  virtual tDisAsmArea* LoadElf(char* aElfFile) //
   {}


//  virtual int GetCellSize(int busnum,int addr) 
//   {}
//  virtual const tDProcCfg* GetCfg() // depending on "debug_structs.h"
//   {}
//  virtual int GetMem(void *mem,int busnum,int addr,int size) 
//   {}
//  virtual int SetMem(void *mem,int busnum,int addr,int size)
//   {}
//  virtual int FillMem(uint32 aVal,int busnum,int addr,int size) 
//   {}


  virtual int DisAssembly(char *str,int busnum,int addr,int size) //
   {}


//  virtual int SetReg(int rnum,int anum,unsigned long val)
//   {}
//  virtual unsigned long GetReg(int rnum,int anum) 
//   {}
//  virtual int SetPc(unsigned long val) 
//   {}
//  virtual uint32 GetPc(int val)
//   {}


  virtual int SetBreakPoint(unsigned long addr, ePointType aType=BP_STANDARD) //
   {}
  // remove breakpoint
  virtual int ClearBreakPoint(unsigned long addr)  //
   {}

//  virtual void ClearMem() 
//   {}

  virtual void Reset()  //
   {}
  virtual void Start()  //
   {}
  virtual void Stop()   //
   {}
  virtual int IsRun()   //
   {}
  virtual void StepInto() //
   {}
  virtual unsigned int GetNumCycles()  //
   {}

  char* Test(void)
   {
     void *p_vptr=NULL;
     int  size=1024;
     p_vptr = (void*) new char [size];
     strncpy((char*)p_vptr, "TDevice::Test(): get string: Hello wold!",size);
     printf("TDevice::Test(): size=%d  p_vptr='%s'\n", size, (char*)p_vptr);
     return  (char*)p_vptr;
   }
}; // class TDevice
*/

/*
//
inline void SingleClock(void)
{
#ifdef SYSTEMC_USED   //
  clk_signal.write(true); 
  sc_cycle(1);
  clk_signal.write(false);
  sc_cycle(1);  
#else
  //
  MainDevice->Operate();
  MainDevice->UpdateDevice();
#endif
} // SingleClock()
*/

void* Init(void)
{
  tNM6403 *vptr;
  //vptr = static_cast<TDevice*>(new TDevice);
  vptr = new tNM6403(); 

  return (void*)vptr;
} 

//
void* CreateDevice(void)
{ 
  void *vptr = NULL;       // ->
  printf("CreateDevice() ...START... \n");
  printf("CreateDevice(): create object \n");

  vptr = Init();

//  void *vptr = Init();       // ->
//  MainDevice = (TDevice*)vptr;
//  OwnerId = GetCurrentThreadId();  // ->
//  IsRunned = 0;
//  CREATE_SIM_THREAD();         // ->

  printf("CreateDevice() ...END. \n");
  return vptr;
} // CreateDevice()


//
extern "C"
{

//
void* InitSys(void)
{
  void *p_vptr = NULL;

  ppdl_int<uint32>  m_clPPDL_int;
  enum tMemCelType  memCelType=MS_CHAR;
  struct tDProcCfg  m_struct;


  printf("InitSys() ...Start... \n");
  printf("InitSys(): sizeof_MS_CHAR=%d \n", sizeof(MS_CHAR));
  printf("InitSys(): sizeof_uint32=%d \n", sizeof(uint32));

  
  //int  size = 1024;
  //p_vptr = (void*) new char [size];
  //strncpy((char*)p_vptr, "InitSys(): get string: Hello wold!",size);
  //printf("InitSys(): size=%d  p_vptr='%s'\n", size, (char*)p_vptr);

  try {
    //void  *dev = CreateDevice();
    TDevice* dev = (TDevice*)CreateDevice();
    TDbgInterface* main_device = dynamic_cast<TDbgInterface*>(dev);
    p_vptr = (TDbgInterface*)main_device;
  } // try
  catch(...) {
    return NULL;
  } // catch(...)

  printf("InitSys() ...End. \n");
  return  p_vptr;
} // InitSys()

//
void SysDestroy(void)
{
  printf("SysDestroy() ...Start... \n");
  printf("SysDestroy(): call DESTROY_THREAD() ... \n");
//  DESTROY_THREAD();
  printf("SysDestroy(): call Destroy() ... \n");
//  Destroy();
  printf("SysDestroy() ...End. \n");
} // SysDestroy()

} // exterm "C"

//
extern "C" 
int TestInitSys(char **p)
{
  int size=0;
  printf("TestInitSys() ...Start... \n");
  size = 1024;
  *p = new char [size];
  strncpy(*p, "get string: Hello wold!",size);
  printf("TestInitSys(): size=%d \n", size);
  printf("TestInitSys() ...End. \n");
  return size;
} // TestInitSys()


/* EOF */

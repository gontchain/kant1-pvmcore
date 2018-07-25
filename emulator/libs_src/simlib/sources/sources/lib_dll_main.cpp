// lib_dll_main.cpp

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
//#include <unistd.h>

// INCLUDE Direction write in Makefile for simlib ""
// DIR_BASE = /home/us/common/Interstron/linux/simulat12
// DIR_HEADERS = include
// INCLUDE_HEADERS = -I$(INCLUDE_BASE)/$(DIR_HEADERS)

#include <_typeWinUnix.h>  // nod dependence (it isn't dependent)
#include <datatypes.h>     // nod dependence
#include <debug_structs.h> // nod dependence
#include <dbg_interface.h>
#include <deviceTest.h>

#include <threads_cfg.h>
#include <system.h>

THDL          Thread;  // "threads_cfg.h"
DWORD         OwnerId;
DWORD         ThreadId;
volatile int  IsRunned;
TDevice       *MainDevice;


// these functions must be imlemented by user
//extern "C" void* Init(void);
//extern "C" void  Destroy(void);
//extern "C" void* CreateDevice();
//extern "C" void* InitSys();


#ifdef SYSTEMC_USED
sc_signal<bool> clk_signal;
#endif

//
SIM_FUNC_DECL()
{   
#ifdef SYSTEMC_USED
  sc_initialize();
#endif
  // 
  while (true)
  {
    WAIT_START_MSG()
    if (IsRunned)
    {
      while (IsRunned)
        ; //SingleClock();
    }
    SEND_STOP_REASON(0xFFFFFF)
  }// while()
} // SIM_FUNC_DECL()


//
extern "C"
{

//
void* CreateDevice(void)
{
  printf("CreateDevice() ...START... \n");
  printf("CreateDevice(): create object \n");

  void *vptr = Init();       // ->
  MainDevice = (TDevice*)vptr;
  OwnerId = GetCurrentThreadId();  // ->  "thread_cfg.h"
  IsRunned = 0;
  CREATE_SIM_THREAD();             // ->  "thread_cfg.h"

  printf("CreateDevice() ...END. \n");
  return vptr;
} // CreateDevice()


//
void* InitSys(void)
{
  void *p_vptr = NULL;

  printf("InitSys() ...Start... \n");
  printf("InitSys(): sizeof_MS_CHAR=%d \n", sizeof(MS_CHAR));
  printf("InitSys(): sizeof_uint32=%d \n", sizeof(uint32));

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
  Destroy();

  printf("SysDestroy() ...End. \n");
} // SysDestroy()


//
inline void SingleClock(void)
{
#ifdef SYSTEMC_USED   //
  clk_signal.write(true); 
  sc_cycle(1);
  clk_signal.write(false);
  sc_cycle(1);  
#else
  //MainDevice->Operate();
  //MainDevice->UpdateDevice();
#endif
} // SingleClock()


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

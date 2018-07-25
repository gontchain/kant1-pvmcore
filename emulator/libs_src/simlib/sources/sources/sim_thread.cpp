// sim_thread.cpp

//#include "threads_cfg.h"
//#include "system.h"

// INCLUDE Direction write in Makefile for simlib ""
// DIR_BASE = /home/us/common/Interstron/linux/simulat12
// DIR_HEADERS = include
// INCLUDE_HEADERS = -I$(INCLUDE_BASE)/$(DIR_HEADERS)

#include <threads_cfg.h>
#include <system.h>


THDL       Thread;
DWORD      OwnerId;
DWORD      ThreadId;
volatile int        IsRunned;
TDevice*   MainDevice;


#ifdef WIN32

#ifdef SYSTEMC_USED
sc_signal<bool> clk_signal;
#endif

SIM_FUNC_DECL()
{   
#ifdef SYSTEMC_USED
  sc_initialize();
#endif
  // 
  while(true)
  {
    WAIT_START_MSG()
    if(IsRunned)
    {
      while(IsRunned)//
        SingleClock();
    }
    SEND_STOP_REASON(0xFFFFFF)
  }// while true
}

#endif


////////////////////////////////////////
// ��� � ���� ����� ����������� � ���������
LIB_EXPORT void* CreateDevice()
{ 
  // ������� �����
  void* vptr = Init();
  MainDevice = (TDevice*)vptr;
  // ���� 
  OwnerId = GetCurrentThreadId();
  // ���� �� ��������� 
  IsRunned = 0;
  // ������������
  CREATE_SIM_THREAD();
  return vptr;
} // CreateDevice()


//
LIB_EXPORT void* InitSys()
{
  void* vptr = NULL;
  try
  {
    TDevice* dev = (TDevice*)CreateDevice();
    TDbgInterface* main_device = dynamic_cast<TDbgInterface*>(dev);
    vptr = (TDbgInterface*)main_device;
  }
  catch( ... )
  {
    return NULL;
  }// end 

  return vptr; 
} // InitSys()


// ����� ����� ����� ��������
LIB_EXPORT int SysDestroy()
{
  // ���� ��������
  //  DESTROY_THREAD();
  // ���"���� ������
  //  Destroy();
  return 1;
}

/*
#ifdef SYSTEMC_USED   // ������ systemc �
int sc_main(int argc, char **argv)
{
  return 0;
}
#endif
*/

 /*
// ���, ���� �� �� ��� ���
inline void SingleClock()
{
#ifdef SYSTEMC_USED   // ������ systemc �
  clk_signal.write(true); 
  sc_cycle(1);
  clk_signal.write(false);
  sc_cycle(1);  
#else
  // ���� �� �����
  MainDevice->Operate();
  MainDevice->UpdateDevice();
#endif
}
*/

/* EOF */

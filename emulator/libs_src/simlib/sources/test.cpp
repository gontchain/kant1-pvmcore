#include "threads_cfg.h"
#include "system.h"


THDL                Thread;
DWORD               OwnerId;
DWORD               ThreadId;  
volatile int        IsRunned;

TDevice*            MainDevice; 

tList<TCyclic>      DeviceList; 


LIB_EXPORT void* InitSys(void* aParam)
{
  void* vptr = NULL;
  try
  {
    TDevice* dev = (TDevice*)CreateDevice(aParam);
    TDbgInterface* main_device = dynamic_cast<TDbgInterface*>(dev);
    vptr = (TDbgInterface*)main_device;
  }
  catch( ... )
  {
    return NULL;
  }// end 
  return vptr; 
} 

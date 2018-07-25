#define DATA_32BITS

#include "ppdl.h"

#define BLOCK_SIZE 1024*512 // 512 килобайт памяти
#define IMEM_WS 1


typedef tSimpleMemBlock<uint32,uint32,uint8> TSimpleMem;

TSimpleMem *mb1, *mb2, *mb3, *mb4;

TMemBus<uint32,uint32> *p_bus,*d_bus;

RiscV *my_risc;

void* Init(void* mParams)
{
  // инициализируем подсистему памяти
  cSwapClass::Init(0x10000000);
  unsigned int peripherals;  
  int is_log_mem;

  if (mParams == NULL)
  {
	  is_log_mem = 0;
  }
  else
  {
	  ChipMem * pm_ChipMem = (ChipMem*)mParams;// support specific memory config
	  is_log_mem = (pm_ChipMem->m_Flags >> 28) & 1;
  }

  // создаем банк памяти размером 128к
  mb1 = new TSimpleMem(BLOCK_SIZE,IMEM_WS);
  mb2 = new TSimpleMem(BLOCK_SIZE,IMEM_WS);
  mb3 = new TSimpleMem(BLOCK_SIZE,IMEM_WS);
  mb4 = new TSimpleMem(BLOCK_SIZE,IMEM_WS);
  // создаем шины памяти
  p_bus = new TMemBus<uint32,uint32>(1,is_log_mem);  
  // подключаем память к шинам по адресу 0
  p_bus->Link(mb1, 0,BLOCK_SIZE);
  //p_bus->Link(mb2, 0x80000000 - BLOCK_SIZE, BLOCK_SIZE);
  p_bus->Link(mb3, 0x80000000, BLOCK_SIZE);
 // p_bus->Link(mb4, 0xFFFFFFFF - BLOCK_SIZE, BLOCK_SIZE);
  p_bus->ClearMem();
  return NULL//(void*)my_risc;
}

void Destroy()
{
	delete mb1;
	delete mb2;
	delete mb3;
	delete mb4;
}

LIB_EXPORT void CheckPostProgram()
{
    Logger.CloseLog();
}
#ifndef PPDL_LIB_FILE_H
#define PPDL_LIB_FILE_H
// наносекунды
#define NS  * 1e-9
// микросекунды
#define MKS * 1e-6
// милисекунды
#define MS  * 1e-3

// килобайты
#define kb * 1024
// мегабайты
#define Mb  kb * 1024 


#include "device.h"

#include "mem_bus.h"
#include "pd_reg.h"
#include "pd_fifo.h"
// flags 
#include "flag.h"
// pipeline simulation
#include "pipes.h"
#include "export_config.h"

#ifndef USE_FOR_DEBUG // memory buses
#include <mem_space.h>
#endif
#include <simple_block.h>
#include <ddram_block.h>

#ifdef SYSTEMC_USED
#include <bus_splitter.h>
#endif

extern "C" LIB_EXPORT void InitMemConf(ChipMem* mParams);
extern "C" LIB_EXPORT void CheckPostProgram();

#ifdef  SYSTEMC_USED
extern  sc_signal<bool> clk_signal;
#endif 

typedef char TMessage[512];

LIB_EXPORT extern void RegErrors(TMessage *aMsgs,int aNumMessages);
LIB_EXPORT extern void RegWarnings(TMessage *aMsgs,int aNumMessages);

#define MAX2(i1,i2)    ((i1>i2) ? i1:i2)
#define MAX3(i1,i2,i3) MAX2(i1,MAX2(i2,i3))

#define MEM_BLOCK_TYPE_NM tSimpleMemBlock <uint32,uint64,uint32>
#define MEM_START_EADDR 0x20000000

// array of pairs "bus - start address"
template<class TBusType> class TBusArea
{
public:
  TBusType* Bus; 
  uint32    aAddr;
};

template<class TBusType> void Add2Bus(TBusArea<TBusType>* MemBusInt,MEM_BLOCK_TYPE_NM *aTmp,uint32 aAddr,uint32 aSize)
{
  TBusArea<TBusType>* bus  = MemBusInt;
  uint32 base_addr = 0;
  while(bus->Bus!=NULL)
  {
    if(aAddr < bus->aAddr)
    {
      bus->Bus->Link(aTmp,aAddr - base_addr, aSize);
      return;
    }
    base_addr = bus->aAddr;
    bus++;
  }
}

#define ADD2BUS() Add2Bus(MemBusInt,mb_Temp,pm_ChipMem->p_startAddr[i], pm_ChipMem->p_Size[i]);

template<class TBusType> void InitBusMem(TBusArea<TBusType>* MemBusInt,ChipMem * pm_ChipMem, TCycleCount aPipeLenExt =0)
{
  TCycleCount pipe_delay;

  if((pm_ChipMem==NULL)||(pm_ChipMem->m_BankNum==-1))
  {
    return;
  }
  // 
  if(pm_ChipMem->p_ReadWaitTime == NULL) // no delay information - just memory for functional modelinng
  {
    for(int i = 0; i < pm_ChipMem->m_BankNum; i++)
    {
      MEM_BLOCK_TYPE_NM *mb_Temp = new tSimpleMemBlock<uint32,uint64,uint32>(pm_ChipMem->p_Size[i],0);
      ADD2BUS()
    }
  }
  else if(pm_ChipMem->p_Configs == NULL) // only waitstate is enable - simple mem block
  {
    for(int i = 0; i < pm_ChipMem->m_BankNum; i++)
    {
      unsigned long wait_state = pm_ChipMem->p_ReadWaitTime[i];
      MEM_BLOCK_TYPE_NM *mb_Temp = new tSimpleMemBlock<uint32,uint64,uint32>(pm_ChipMem->p_Size[i],wait_state);
      ADD2BUS()
    }
  }
  else
  {
    for(int i = 0; i < pm_ChipMem->m_BankNum; i++)
    {
#ifdef FOR_NM_SDK
        tSimpleMemBlock <uint32,uint64,uint32> *mb_Temp = new tSimpleMemBlock<uint32,uint64,uint32>(pm_ChipMem->p_Size[i],0, 0);
        ADD2BUS()
#else
      unsigned long wait_state = (pm_ChipMem->p_ReadWaitTime == pm_ChipMem->p_WriteWaitTime) ? 0 : pm_ChipMem->p_ReadWaitTime[i];
      unsigned long wait_write = (pm_ChipMem->p_ReadWaitTime == pm_ChipMem->p_WriteWaitTime) ? 0 : pm_ChipMem->p_WriteWaitTime[i];
      pipe_delay = 0;//(pm_ChipMem->p_startAddr[i] < 0xA0000000) ? 0:aPipeLenExt; 
      // 
      if( (wait_state==0) || (wait_write > 1000*wait_state) )// to support emudbg
      {
        tSimpleMemBlock <uint32,uint64,uint32> *mb_Temp = new tSimpleMemBlock<uint32,uint64,uint32>(pm_ChipMem->p_Size[i],wait_state, pipe_delay);
        ADD2BUS()
      }
      else
      {
        SDRamConfig *cfg = pm_ChipMem->p_Configs + i;
        if(cfg->mKind == SMEM_SDRAM)
        {
          
          TDDramMemBlock<uint32,uint64,uint32>* mb_Temp = new TDDramMemBlock<uint32,uint64,uint32>(pm_ChipMem->p_Size[i],cfg->mPageSize,cfg->mLatency,aPipeLenExt,cfg->mMulFactor,
                                                                                                   cfg->mRegenPeriod,cfg->mRegenTime,cfg->mPageCloseTime + cfg->mPageOpenTime);
          ADD2BUS()
        }
        else
        {
          int is_pipelined = (cfg->mKind==SMEM_SSRAM) ? (cfg->mSSramLKind == SSMEM_PIPELINED):0;
          tSimpleMemBlock <uint32,uint64,uint32> *mb_Temp = new tSimpleMemBlock<uint32,uint64,uint32>(pm_ChipMem->p_Size[i],wait_state,pipe_delay,is_pipelined);
          ADD2BUS()
        }// end  if(cfg->mKind == SMEM_SDRAM) / else 
      } // if(wait_state ...
#endif
    }// for(int i = 0; i <....
  }
}//



template<class TBusType> void DestroyMem(TBusType* Bus)
{
  TMemBus<uint32,uint64>::TLink * pTempTLink = Bus->GetNextLink(NULL);
  if (pTempTLink==NULL)
    return;
  tSimpleMemBlock<uint32,uint64,uint32> *mb_Temp = (tSimpleMemBlock<uint32,uint64,uint32> *) pTempTLink->mArea;
  while(mb_Temp)
  {
    delete mb_Temp;
    pTempTLink = Bus->GetNextLink(pTempTLink);
    if(pTempTLink)
    {
      mb_Temp = (tSimpleMemBlock<uint32,uint64,uint32>*) pTempTLink->mArea;
    }
    else
    {
      mb_Temp = NULL;
    }
  }
}
#endif

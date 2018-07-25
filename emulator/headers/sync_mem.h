#ifndef SYNC_MEMORY_H
#define SYNC_MEMORY_H
#include "simple_block.h"

extern void SkipCycle();
extern uint32 GlobalCycleCounter;

#define PRINT_TRACE

#define SYNC_MEM_FRAME_SIZE 0x100
#define TYPE_BIT_SIZE(type) (sizeof(type)*8)

template<class vAddrType, class vDataType, class vCellType,class vSyncBufRegType>
class tSyncMemBlock : public tSimpleMemBlock<vAddrType, vDataType, vCellType>
{
protected:
    vSyncBufRegType*    mSyncBuf;
    vAddrType           mAddrLimit;

public:
  tSyncMemBlock(vAddrType aSize):tSimpleMemBlock(aSize,0,0,0)
  {
    vAddrType num_sync_cells = aSize / TYPE_BIT_SIZE(vSyncBufRegType);
    mSyncBuf = new uint32[num_sync_cells];// one bit per word
    mAddrLimit = aSize + (aSize / SYNC_MEM_FRAME_SIZE);

    for (vAddrType cnt = 0; cnt < num_sync_cells; cnt++)
    {
      mSyncBuf[cnt] = 0;
    }// end for 

  }

  inline void ResetFrame(vAddrType aAddr)
  {
    vAddrType num_cells = SYNC_MEM_FRAME_SIZE / TYPE_BIT_SIZE(vSyncBufRegType);

    for (vAddrType cnt = 0; cnt < num_cells; cnt++)
    {
      mSyncBuf[cnt] = 0;
    }// end for 
  }
  
  inline bool IsSyncSpace(vAddrType aAddr)
  {
    return (aAddr >= this->mSize) && (aAddr < mAddrLimit); 
  }

#define SYNC_ADDR (aAddr / TYPE_BIT_SIZE(vSyncBufRegType) )
#define SYNC_BIT  ((aAddr & ( TYPE_BIT_SIZE(vSyncBufRegType) - 1)))

#define SYNC_BUF_CELL mSyncBuf[ SYNC_ADDR]
#define SYNC_BUF_BIT (1<<SYNC_BIT)

  inline int IsLocked(vAddrType aAddr)
  {
    int sync_bit = (SYNC_BUF_CELL &  SYNC_BUF_BIT) ;
#ifdef PRINT_TRACE
 //   printf("check lock: addr = 0x%08X, cycles = %d, sync_addr = 0x%08X, sync_bit_addr = 0x%08X, sync_val =  0x%08X, sync_bit = %d\n", 
 //     aAddr, GlobalCycleCounter, SYNC_ADDR, SYNC_BIT, mSyncBuf[SYNC_ADDR], sync_bit); fflush(stdout);
#endif
    return (sync_bit == 0);
  }
  // 
  inline void  SetUnlock(vAddrType aAddr)
  {
     SYNC_BUF_CELL |= SYNC_BUF_BIT;
  }
  // 
  virtual vDataType ReadMem(vAddrType aAddr)
  {
    if (!IsSyncSpace(aAddr)) // sync space is ingnored for read
    {
      TDevice *dev = ((TDevice*)CurDevice);
#ifdef PRINT_TRACE
      uint32 init_cycles = GlobalCycleCounter;
#endif
      if (!IsLocked(aAddr))
      {
#ifdef PRINT_TRACE
        printf("%s: single cycle sync read addr 0x%08X, cycles = %d\n", dev->GetDeviceName(), aAddr, GlobalCycleCounter); fflush(stdout);
#endif
        return tSimpleMemBlock<vAddrType, vDataType, vCellType>::ReadMem(aAddr);
      }
       
#ifdef PRINT_TRACE
      printf("%s: start sync read addr 0x%08X, cycles = %d\n", dev->GetDeviceName(),aAddr, GlobalCycleCounter); fflush(stdout);
#endif

      do
      {
        SkipCycle();
        dev->IncSyscWaitCounter();
      }while (IsLocked(aAddr));
#ifdef PRINT_TRACE
      printf("%s: stop sync read addr 0x%08X, cycles = %d\n", dev->GetDeviceName(),aAddr, GlobalCycleCounter); fflush(stdout);
      printf("%s: mem delay addr 0x%08X, cycles = %d\n", dev->GetDeviceName(), aAddr, GlobalCycleCounter - init_cycles); fflush(stdout);
#endif
      return tSimpleMemBlock<vAddrType, vDataType, vCellType>::ReadMem(aAddr);
    }
    else
    {
      return 0;
    }
  }

  virtual void WriteMem(vAddrType aAddr, vDataType aData)
  {
#ifdef PRINT_TRACE
    printf("MEM64: write addr 0x%08X, cycles = %d\n", aAddr, GlobalCycleCounter); fflush(stdout);
#endif
    SetUnlock(aAddr);
    SetUnlock(aAddr+1);
    tSimpleMemBlock<vAddrType, vDataType, vCellType>::WriteMem(aAddr,aData);
  }
  virtual void WriteMem32(vAddrType aAddr, uint32 aData)
  {
#ifdef PRINT_TRACE
    printf("%s: MEM32 write addr 0x%08X, cycles = %d\n", ((TDevice*)CurDevice)->GetDeviceName(), aAddr, GlobalCycleCounter); fflush(stdout);
#endif
    SetUnlock(aAddr);
    tSimpleMemBlock<vAddrType, vDataType, vCellType>::WriteMem32(aAddr, aData);
  } 
};

#endif
#ifndef DDRAM_MEM_DESCRIPTION
#define DDRAM_MEM_DESCRIPTION


#include "datatypes.h"
#include "simple_block.h"

//#define MEM_LOG
#define  SEQUENCE_PIPELINE 1

#define START_REGEN_TIME 314
template<class vAddrType,class vDataType,class vCellType>
class TDDramMemBlock : public tSimpleMemBlock<vAddrType,vDataType,vCellType>
{
protected:
// ddram delays
  TCycleCount mRegenPeriod;     // regeneration perioud
  TCycleCount mRegenTime;       // regeneration time
  TCycleCount mWholeRegen;      // Regeneration perioud + regeneration time
  TCycleCount mFirstAccess;     // time of the first access to memory
  TCycleCount mPageSelTime;     // page selection time 
  TCycleCount mLastRegenTime;   // time of last regeneration
// page parameters 
  vAddrType mPageSize;
  vAddrType CurPage;

// last written block


  double mFreqMulFactor;

#define DDRAM_CLOCKS(iclocks) (TCycleCount)(((double)(iclocks))/mFreqMulFactor)
#define MCORE_CLOCKS(dclocks) (TCycleCount)(((double)(dclocks))*mFreqMulFactor)

  inline TCycleCount PageShiftDelay(vAddrType aAddr,TCycleCount aCurTime)
  {
    vAddrType page = aAddr / mPageSize;
    if(page==CurPage) return 0;
#ifdef USE_LOGGER
    Logger.Log(LOG_PAGE_SELECT,(uint32)this,MCORE_CLOCKS(aCurTime),MCORE_CLOCKS(mPageSelTime));
#endif 
    CurPage = page;
    return  (this->mFirstAccess != aCurTime) ?  mPageSelTime : mPageSelTime/2;
  }

  inline TCycleCount ShiftRegeneration(TCycleCount cycles,TCycleCount aCurTime)
  {
    TCycleCount per = cycles;  
    if(per < mLastRegenTime)
    {
      return cycles;
    }

#ifdef USE_LOGGER
    Logger.Log(LOG_REGEN_SDRAM,(uint32)this,MCORE_CLOCKS(aCurTime),MCORE_CLOCKS(mRegenTime));
#endif 
    mLastRegenTime += mRegenPeriod;
#ifdef MEM_LOG
    printf("\nregen at %d cycles, new value %d, next regen %d\n",MCORE_CLOCKS(cycles),MCORE_CLOCKS(cycles + mRegenTime),MCORE_CLOCKS(mLastRegenTime)); fflush(stdout);
#endif
    return (cycles + mRegenTime);
  }

public:
  // constructor
  TDDramMemBlock(vAddrType aSize, vAddrType aPageSize, TCycleCount aWaitTime, TCycleCount aPipeLatency,
                 double aMulFactor, TCycleCount aRegenPeriod, TCycleCount aRegenTime, TCycleCount aPageSelTime)
  {
    this->SimpleBlockInit(aSize,aWaitTime,aPipeLatency,0);
    this->mFreqMulFactor = aMulFactor;

    mRegenPeriod = aRegenPeriod;
    mWholeRegen  = aRegenPeriod + aRegenTime;
    mRegenTime   = aRegenTime;
    mPageSelTime = aPageSelTime;


    mFirstAccess = 0;
    mLastRegenTime = DDRAM_CLOCKS(START_REGEN_TIME);
    mPageSize = aPageSize;
    mPageSelTime = aPageSelTime;
    CurPage = aSize / aPageSize + 1;// no active page at the beginning
    this->mPipeLatency = aPipeLatency;
  }
  
  // 
  virtual TCycleCount GetDelay(vAddrType aAddr) 
  { 
    return (TCycleCount)this->mWaitTime; 
  }

  virtual TCycleCount SetMemLock(int aPipe)
  {
    TCycleCount cur_time_ref = CurDevice->NumCycles();
    TCycleCount cur_time = DDRAM_CLOCKS(cur_time_ref);
    TCycleCount new_time_offset;
    TCycleCount init_time;
    
    if((this->mLastAccessAddr == this->mCurAddr) && (this->mLastAccessTime == cur_time_ref))
    {
      return MCORE_CLOCKS(this->mCurAccessCycles + this->mPipeLatency);
    }


    this->mLastAccessTime  = cur_time_ref;
    this->mLastAccessAddr  = this->mCurAddr;
    this->mLastAccessType  = this->mCurAccessType;

/*    if((cur_time_ref<=(DDRAM_CLOCKS(this->mLastAccessTime)+2))&&(this->mFirstAccess) && ( this->mLastAccessType == this->mCurAccessType))
      new_time_offset = this->mCurAccessCycles + 1;
    else*/

//    if((this->mCurAccessType==MEM_ACC_READ) && (this->mLastWrittenAddr == this->mCurAddr))
 //     cur_time = max_val(cur_time,this->mLastWrittenCount);

    new_time_offset = max_val(cur_time,this->mCurAccessCycles) + this->mWaitTime;

    // registry first access 
    if(this->mFirstAccess==0)
    {
      this->mFirstAccess = cur_time;
      this->mLastRegenTime += cur_time;
    }

    // shift due to the page delay 
    new_time_offset += PageShiftDelay(this->mCurAddr,cur_time);
    // shift due to the regeneration
    new_time_offset = ShiftRegeneration(new_time_offset,cur_time);

    this->mCurAccessCycles = new_time_offset;   
    cur_time = MCORE_CLOCKS(new_time_offset + this->mPipeLatency);

 
    // out log message
#ifdef USE_LOGGER
  	Logger.Log(LOG_MEM_BLOCK_ACCESS,(uint32)this,this->mCurAddr,cur_time_ref,cur_time);
#endif 

#ifdef MEM_LOG
  //  printf("addr %8X, cur time - %d,access time %d\n",this->mCurAddr,cur_time_ref,cur_time); fflush(stdout);
#endif
    return cur_time;
  }
};
#endif

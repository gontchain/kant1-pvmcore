#ifndef MUTABLE_BASE_CLASS_H
#define MUTABLE_BASE_CLASS_H

class TMutable
{
protected:
  TCycleCount* mCount;
  int         Capacity;
  int         PipeStart;
  TCyclic*    PDevice;
  void*		  SuperClass;

public:
  inline TCycleCount GetLockCount(int aIdx=0){ return mCount[aIdx]; }

  inline void ResetMutable()
  {
    for(int i=0;i<Capacity;i++)
      mCount[i]  = 0;
  }
 
  TMutable(void* aSuperClass)
  { 
    mCount = new TCycleCount[1]; 
    PDevice = CurDevice;
    Capacity = 1;
    ResetMutable();
  	SuperClass = aSuperClass;
  }

  TMutable(void* aSuperClass,int aCapacity)
  { 
    mCount = new TCycleCount[aCapacity]; 
    PDevice = CurDevice;
    Capacity = aCapacity;
	  SuperClass = aSuperClass;
    ResetMutable();
  }

  inline void Check(/*int aPipe,*/int aIdx=0)
  { 
    if(aIdx==-1) return;
  
    TCycleCount cur_count = (TCycleCount)PDevice->NumCycles();      
    TCycleCount available_count = mCount[aIdx] ;// !!!2503 + 1 ;

    if((signed)available_count > (signed)cur_count )  
    {
#ifdef USE_LOGGER
      Logger.Log(LOG_REG_LOCK,(uint32)SuperClass,cur_count,available_count);
#endif      
      PDevice->SetCycles(available_count);
    }
  }
  
  inline int IsLocked(int aIdx = 0)
  {
    TCycleCount cur_cycles = PDevice->NumCycles();
    int is_locked = (mCount[aIdx] > cur_cycles);

#ifdef USE_LOGGER
    if(is_locked)
      Logger.Log(LOG_REG_CHECK_FALSE,(uint32)SuperClass,cur_cycles);
#endif 

    return is_locked;
  }

  inline void Lock(int aPipe,int aIdx=0)
  {
//   Check(/*aPipe,*/aIdx);
    PipeStart = aPipe;
  }
  
  inline void UnLock(int aPipe,int aIdx=0)
  {
    mCount[aIdx] = PDevice->NumCycles() + (aPipe - PipeStart);
  }


  inline void LockLink(TCycleCount aCycles,int aAddCount,int aIdx=0)
  {
    aCycles += aAddCount;
    if(mCount[aIdx] < aCycles)
      mCount[aIdx] = aCycles;
  }
  

  inline TCycleCount GetLock(int aIdx=0)
  {
    return mCount[aIdx];
  }
};


#endif
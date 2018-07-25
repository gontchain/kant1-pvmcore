#ifndef MEMORY_BUS_H
#define MEMORY_BUS_H

#include "mem_space.h"
#include "math.h"
#include "mutable.h"
#include "dbg_interface.h"
#include "stdio.h"
#include "pd_fifo.h"



#define  LOG_MEM_ACCESS
//#define LOG_MEM_DELAYS

template<class vAddrType,class vDataType> class TLinkStruct
{
public:
  typedef iMemInterface<vAddrType,vDataType> TMemArea;
  typedef TLinkStruct<vAddrType,vDataType> TLink;
    
  vAddrType   mStartAddr;
  vAddrType   mEndAddr;
  TMemArea*   mArea; 
  TLink*      mNext;
    
  TLinkStruct(TMemArea* aMa,vAddrType aStart,vAddrType aLen)
  {
    mStartAddr = aStart;
    mEndAddr = aLen + aStart;
    mArea = aMa;
    mNext = 0;
  }
};


template<class vAddrType,class vDataType> class TMemLinkList
{
  typedef iMemInterface<vAddrType,vDataType> TMemArea;
  typedef TLinkStruct<vAddrType,vDataType> TLink;

    
public:  
  TLink* FirstLink;
  TLink* LastLink;
  TLink* CurLink;
  // get link depends on the address
  inline TLink* GetArea(vAddrType aAddr)
  {
    TLink* l = FirstLink;
    while(l!=NULL)
    {
      if((aAddr>=l->mStartAddr)&&(aAddr< l->mEndAddr))
        return l;
      l = l->mNext;
    }
    return NULL;
  }

public:
  inline vAddrType max_addr(vAddrType v1,vAddrType v2){ if(v1>v2) return v1; else return v2;}
  inline vAddrType min_addr(vAddrType v1,vAddrType v2){ if(v1>v2) return v2; else return v1;}

  int Link(TMemArea* aMem,vAddrType aStart, vAddrType aLen)
  {
    TLink* l = new TLink(aMem,aStart,aLen);
    if(LastLink==NULL)
    {
      FirstLink = LastLink = l;
    }
    else
    {
      LastLink->mNext = l;
      LastLink = l;
    }
    return 1;
  }

  TLink * GetNextLink(TLink * pCurrTLink)
  {
    if(pCurrTLink == NULL)
      return FirstLink;
    else
      return pCurrTLink->mNext;
  }
// debug functions
#define IS_IN_BLOCK(addr) ((addr>=aAddr)&&(addr<end_addr))
#define IS_IN_SPACE(addr) ((addr>=lnk->mStartAddr)&&(addr<lnk->mEndAddr))
  
  inline int AddrRange(TLink* lnk,vAddrType aAddr,vAddrType& aStartAddr,int aInitSize,int& aSize,int& aOffs)
  {
    int cell_size = lnk->mArea->GetCellSize(0);
    vAddrType end_addr = aAddr + (vAddrType)((unsigned int)aInitSize/cell_size);

    if(IS_IN_SPACE(aAddr)||IS_IN_SPACE(end_addr)||((aAddr<lnk->mStartAddr)&&(end_addr>lnk->mEndAddr)))
    {
      vAddrType saddr_abs = IS_IN_SPACE(aAddr) ? aAddr : lnk->mStartAddr;      
      aStartAddr  = saddr_abs - lnk->mStartAddr;
      aSize = (int)(min_addr(end_addr,lnk->mEndAddr) - saddr_abs)*cell_size;
      aOffs = (saddr_abs - aAddr)*cell_size;
      return 1;
    }
    else
      return 0;
  }

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class vAddrType,class vDataType> 
class TMemBus: public iMemInterface<vAddrType,vDataType>,public TMutable//,public TMemLinkList<vAddrType,vDataType>
{
protected:
  char message_buf[128];
  ErrorHeader hdr;
  TCycleCount mPipeLen;  
  TCycleCount mLastLockCycles;
  TCycleCount mLastRequest;
  TDevice*	  WatchPointsDev;

  int          mWriteThanRead;
  int          mReadThanWrite;
  //
  TCycleCount   mLastWriteCycle;
  vAddrType     mLastWriteAddr;

  TCycleCount   mLastReadCycle;
  vAddrType     mLastReadAddr;
  int           mIsLogAccess; 

  void IncorrectAccess(vAddrType aAddr)
  {
    sprintf(message_buf,"%X\n",(uint32)aAddr);
    CheckError(message_buf,0xFFFF);
  }


public: 
  typedef iMemInterface<vAddrType,vDataType> TMemArea;
  typedef TLinkStruct<vAddrType,vDataType> TLink;
 
#define MYTHIS (this)
#define IFTHIS ((iMemInterface<vAddrType,vDataType>*)this)

public:  
  TLink* FirstLink;
  TLink* LastLink;
  TLink* CurLink;

  inline void SetWPDev(TDevice* aDev) {  WatchPointsDev = aDev;}

  // get link depends on the address
  inline TLink* GetArea(vAddrType aAddr)
  {
    TLink* l = FirstLink;
	if(WatchPointsDev!=NULL)
	    WatchPointsDev->CheckWatchPoints(aAddr);
    
    while(l!=NULL)
    {
      if((aAddr >= l->mStartAddr)&&(aAddr < l->mEndAddr))
        return l;
      l = l->mNext;
    }
    return NULL;
  }

public: 
  inline vAddrType max_addr(vAddrType v1,vAddrType v2){ if(v1>v2) return v1; else return v2;}
  inline vAddrType min_addr(vAddrType v1,vAddrType v2){ if(v1>v2) return v2; else return v1;}

  int Link(TMemArea* aMem,vAddrType aStart, vAddrType aLen)
  {
    TLink* l = new TLink(aMem,aStart,aLen);
 
    if(LastLink==NULL)
    {
      FirstLink = LastLink = l;
    }
    else
    {
      LastLink->mNext = l;
      LastLink = l;
    }
    return 1;
  }


  TLink * GetNextLink(TLink * pCurrTLink)
  {
    if(pCurrTLink == NULL)
      return FirstLink;
    else
      return pCurrTLink->mNext;
  }

// debug functions
#define IS_IN_BLOCK(addr) ( (addr>=aAddr) && (addr<end_addr) )
#define IS_IN_SPACE(addr) ( (addr>=lnk->mStartAddr) && (addr<lnk->mEndAddr) )
  
  inline int AddrRange(TLink* lnk,vAddrType aAddr,vAddrType& aStartAddr,int aInitSize,int& aSize,int& aOffs)
  {
    int cell_size = lnk->mArea->GetCellSize(aAddr);
    vAddrType end_addr;
      
    if(cell_size == 0)
      end_addr = aAddr;
    else
      end_addr = aAddr + (vAddrType)((unsigned int)aInitSize/cell_size);

    if(IS_IN_SPACE(aAddr)||IS_IN_SPACE(end_addr)||((aAddr<lnk->mStartAddr)&&(end_addr>lnk->mEndAddr)))
    {
      vAddrType saddr_abs;// =  max_addr(aAddr,lnk->mStartAddr);
      if(IS_IN_SPACE(aAddr))
        saddr_abs =  aAddr;
      else
        saddr_abs = lnk->mStartAddr;
      
      aStartAddr  = saddr_abs - lnk->mStartAddr;
      aSize = (int)(min_addr(end_addr,lnk->mEndAddr) - saddr_abs)*cell_size;
      aOffs = (saddr_abs - aAddr) * cell_size;
      return 1; 
    }
    else
      return 0;
  }


public:

  TMemBus(int aPipeLen = 0,int aLogAcces = 0):iMemInterface<vAddrType,vDataType>(),TMutable((void*)this)
  {
    MYTHIS->FirstLink = MYTHIS->LastLink = NULL;
    MYTHIS->CurLink = NULL;
    mPipeLen = aPipeLen;
	  mLastLockCycles = 0;
    mLastRequest  = 0;
	  WatchPointsDev = NULL;
    
    mWriteThanRead = 0;
    mReadThanWrite = 0;

    mLastWriteCycle = 0;
    mLastWriteAddr  = 0;

    mLastReadCycle = 0;
    mLastReadAddr  = 0;

    mIsLogAccess = aLogAcces;
  }


  virtual vDataType ReadMem(vAddrType aAddr)
  {
    TLink* lnk;
    
    mWriteThanRead = (mLastWriteAddr == aAddr) ;
    mReadThanWrite = 0;
    mLastReadAddr  = aAddr; 

    IFTHIS->MemCell.mCurAddr = aAddr;
    IFTHIS->MemCell.MemAccessTypeSign = MEM_READ;


    lnk = MYTHIS->GetArea(aAddr);

    if(lnk==NULL)
    {
      IncorrectAccess(aAddr);
      return (vDataType)0;
    }
    else
    {
      vDataType ret_val =  lnk->mArea->ReadMem(aAddr - lnk->mStartAddr);
#ifdef LOG_MEM_ACCESS
      if (mIsLogAccess)
      {
        fprintf(stdout," Read64(addr %X, val %08X%08X) ",(uint32)IFTHIS->MemCell.mCurAddr,(uint32)(ret_val>>32),(uint32)(ret_val&0xFFFFFFFF)); fflush(stdout);
      }
#endif
      return ret_val;
    }// if(lnk==NULL)
  }

  virtual void WriteMem32(vAddrType aAddr,uint32 aData)
  {
    TLink* lnk = MYTHIS->GetArea(aAddr);
    IFTHIS->MemCell.mCurAddr = aAddr;
    IFTHIS->MemCell.MemAccessTypeSign = MEM_WRITE;
    
    mWriteThanRead = 0;
    mReadThanWrite = (mLastReadAddr == aAddr);

    mLastWriteAddr = aAddr;

    if(lnk==NULL)
    {
      IncorrectAccess(aAddr);
    }
    else
    {
      lnk->mArea->WriteMem32(aAddr - lnk->mStartAddr,aData); 
#ifdef  LOG_MEM_ACCESS
      if (mIsLogAccess)
      {
        fprintf(stdout," Read32(addr %X, val %X)",(uint32)IFTHIS->MemCell.mCurAddr,aData); fflush(stdout);
      }
#endif
    }
  }

  virtual void WriteMem(vAddrType aAddr,vDataType aData)
  {
    TLink* lnk = MYTHIS->GetArea(aAddr);
    
    mWriteThanRead = 0;
    mLastWriteAddr = aAddr;
    
    mWriteThanRead = 0;
    mReadThanWrite = (mLastReadAddr == aAddr);

    IFTHIS->MemCell.mCurAddr = aAddr;
    IFTHIS->MemCell.MemAccessTypeSign = MEM_WRITE;

    if(lnk!=NULL)
    {
#ifdef  LOG_MEM_ACCESS
      if(mIsLogAccess)
      {
        fprintf(stdout," Write(addr %X, val %08X%08X)",(uint32)IFTHIS->MemCell.mCurAddr,(uint32)(aData>>32),(uint32)(aData&0xFFFFFFFF)); fflush(stdout);
      }
#endif
      lnk->mArea->WriteMem(aAddr - lnk->mStartAddr,aData); 
    }
    else
      IncorrectAccess(aAddr);   
  }

  virtual void SetAddr(vAddrType aAddr,eMemWriteMask aMask = MEM_MASK_U32)
  {
    CurLink = MYTHIS->GetArea(aAddr);
	  IFTHIS->MemCell.mCurAddr = aAddr;
	  if (CurLink != NULL)
        CurLink->mArea->SetAddr(aAddr - CurLink->mStartAddr,aMask);
	  if (mIsLogAccess)
	  {
		  fprintf(stdout, " SetAddr(addr %X)", (uint32)IFTHIS->MemCell.mCurAddr); fflush(stdout);
	  }
  }

  virtual int IsReady()
  {
    if(CurLink==NULL)
      return 0;
    return CurLink->mArea->IsReady();
  }

  virtual vDataType WriteData(vDataType aData)
  {
    if(MYTHIS->CurLink==NULL) return aData;
    IFTHIS->MemCell.MemAccessTypeSign = MEM_WRITE;
	  if (mIsLogAccess)
	  {
		  fprintf(stdout, " Write(addr %X, val %08X%08X)", (uint32)IFTHIS->MemCell.mCurAddr, (uint32)(aData >> 32), (uint32)(aData & 0xFFFFFFFF)); fflush(stdout);
	  }
	  return MYTHIS->CurLink->mArea->WriteData(aData);
  }
  
  
  virtual uint32 WriteData32(uint32 aData)
  {
    if(MYTHIS->CurLink==NULL) return aData;
    IFTHIS->MemCell.MemAccessTypeSign = MEM_WRITE;
    return MYTHIS->CurLink->mArea->WriteData32(aData);
	  if (mIsLogAccess)
	  {
		  fprintf(stdout, " Write32(addr %X, val %X)", (uint32)IFTHIS->MemCell.mCurAddr, aData); fflush(stdout);
	  }
  }

  virtual vDataType GetData()
  {  
    if(MYTHIS->CurLink==NULL) return 0;
    IFTHIS->MemCell.MemAccessTypeSign = MEM_READ;
    vDataType aData = MYTHIS->CurLink->mArea->GetData();
	  if (mIsLogAccess)
	  {
		  fprintf(stdout, " Read32(addr %X, val %X)", (uint32)IFTHIS->MemCell.mCurAddr, aData); fflush(stdout);
	  }
	  return aData;
  }

  virtual int IsMemInRange(vAddrType aAddr,uint32 aSizeInBytes)
  {
    TLink*     lnk  = MYTHIS->FirstLink;
    int        offs;
    int        size;
    vAddrType  saddr;
    int        res  = 0;
    
    while(lnk!=NULL)
    {
      if(AddrRange(lnk,aAddr,saddr,aSizeInBytes,size,offs))
        res +=size;
      if(res >= aSizeInBytes)
        return 1;
      lnk = lnk->mNext;
    }  
    return 0;
  }


  virtual int getmem(void* aDataArray,vAddrType aAddr,int aSizeInBytes)
  {
    TLink*     lnk  = MYTHIS->FirstLink;
    char*      data = (char*)aDataArray;
    int        res  = 0;
    int        offs;
    int        size;
    vAddrType  saddr;
    while(lnk!=NULL)
    {
      if(AddrRange(lnk,aAddr,saddr,aSizeInBytes,size,offs))
        res += lnk->mArea->getmem((void*)&data[offs],saddr,size);
      if(res >= aSizeInBytes)
        return aSizeInBytes;
      lnk = lnk->mNext;
    }
    return res;    
  }

  virtual int setmem(void* aDataArray,vAddrType aAddr,int aSizeInBytes)
  {
    TLink* lnk = MYTHIS->FirstLink;
    int res = 0;
    char* data = (char*)aDataArray;
    int        offs;
    int        size;
    vAddrType  saddr;

    while(lnk!=NULL)
    {
      if(AddrRange(lnk,aAddr,saddr,aSizeInBytes,size,offs))
        res += lnk->mArea->setmem((void*)&data[offs],saddr,size);
      if(res >= aSizeInBytes)
        return aSizeInBytes;
      lnk = lnk->mNext;
    }
    return res;
  }

  virtual void ClearMem()
  {
    TLink* lnk = MYTHIS->FirstLink;
    while(lnk!=NULL)
    {
      lnk->mArea->ClearMem();
      lnk = lnk->mNext;
    }
  }

  virtual int fillmem(vDataType aVal,vAddrType aAddr,int aSizeInBytes)
  {
    TLink* lnk = MYTHIS->FirstLink;
    int       res = 0;
    int       offs;
    int       size;
    vAddrType saddr;

    while(lnk!=NULL)
    {
      if(AddrRange(lnk,aAddr,saddr,aSizeInBytes,size,offs))
        res += lnk->mArea->fillmem(aVal,saddr,size);
      lnk = lnk->mNext;
    }
    return res;
  }

  virtual int GetCellSize(vAddrType aAddr)
  {
    TLink* lnk = MYTHIS->FirstLink;// GetArea(aAddr);
    if(lnk==NULL)
      return 0;
    else
      return lnk->mArea->GetCellSize(aAddr - lnk->mStartAddr); 
  }

  virtual void LockMem(int aPipe)
  {
    Lock(aPipe);
  }

  virtual void ResetMemMutable()
  {
    TLink* lnk;
    for(lnk = this->FirstLink;lnk!=NULL;lnk = lnk->mNext)
      lnk->mArea->ResetMemMutable();
  }

  inline TCycleCount SetLockCount(int aPipe=1)
  { 
    TLink* lnk = MYTHIS->GetArea(IFTHIS->MemCell.mCurAddr);
    if(lnk==NULL) return 0;   
    return lnk->mArea->GetDelay(IFTHIS->MemCell.mCurAddr);
  }

  virtual TCycleCount SetMemLock(int aPipe)
  {
    TCycleCount new_cycles;
    TCycleCount mem_lock_count;
    TCycleCount last_request;
    // error if delay is more than 1 cycle
    TLink* lnk = MYTHIS->GetArea(IFTHIS->MemCell.mCurAddr);
    if(lnk==NULL) return 0;

#if 0
    {
      TCycleCount cur_cycles = (TCycleCount)PDevice->NumCycles();
      TCycleCount piped_count = cur_cycles + this->mPipeLen;

      mLastLockCycles = max_val(piped_count, mLastLockCycles + 1);
      PDevice->SetCycles(mLastLockCycles);
      new_cycles = lnk->mArea->SetMemLock(aPipe);
      PDevice->SetCycles(cur_cycles);
      return new_cycles;
    }
//#error need to implement init cycles pipeline shift
#else
#if 1

    TCycleCount cur_cycles;// = (TCycleCount)PDevice->NumCycles();

#if 0
    if(this->mWriteThanRead)
    {
      cur_cycles= (TCycleCount)PDevice->NumCycles();
      PDevice->SetCycles(max_val(mLastWriteCycle,cur_cycles));
#ifdef LOG_MEM_DELAYS
      printf("WriteThanRead: %d,%d\n",cur_cycles,PDevice->NumCycles());
#endif 
    }
#endif

    mLastLockCycles = lnk->mArea->SetMemLock(aPipe) + mPipeLen;

#if 0
    if(this->mWriteThanRead)
    {
      PDevice->SetCycles(cur_cycles);
    }

    if(IFTHIS->MemCell.MemAccessTypeSign == MEM_WRITE)
    {
      mLastWriteCycle = mLastLockCycles;
      mLastWriteAddr  = IFTHIS->MemCell.mCurAddr;
    }
#endif

    return mLastLockCycles;
#else
   new_cycles = lnk->mArea->SetMemLock(aPipe);
    mLastLockCycles = max_val(new_cycles,mLastLockCycles + 1);
    new_cycles = mLastLockCycles;
    return new_cycles  + mPipeLen;
#endif
#endif
  }
  //
  virtual void UnlockMem(int aPipe)
  {
    int lock_delay = SetLockCount(aPipe);
    int delay = lock_delay - (aPipe - PipeStart);
    
    if(delay > 0 )
    {
      TCycleCount count = (TCycleCount)PDevice->NumCycles();
      PDevice->SetCycles((TCycleCount)delay + count);
    }
  }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define  MEM_WRITE_PIPE_DELAY 3
template<class vAddr> struct TAccessPoint
{
  vAddr       Addr;
  int         Access;
  TCycleCount Cycle;
};

template<class vAddrType,class vDataType, const int vNumRequests>  class TBusSwitcher: public TMemBus<vAddrType,vDataType>
{
#define MAX_NUM_REQUESTS vNumRequests
#define NUM_INTERNAL_SLOTS 3
#define NUM_SLOTS_ALL vNumRequests 

   TAccessPoint<vAddrType>  Accesses[vNumRequests];
   int                      AccessCount;
   int                      IsLogMem;
   
#define IFTHIS ((iMemInterface<vAddrType,vDataType>*)this)
  
  typedef TLinkStruct<vAddrType,vDataType> TLink;

public:

  TBusSwitcher(int aPipe = 0,int aLogMem = 0):TMemBus<vAddrType,vDataType>(aPipe,aLogMem)
  {
    AccessCount = 0;
  }

  inline void SetAccessCount(TCycleCount aInp,int aIdx)
  {
    this->Accesses[aIdx].Cycle  = aInp;
    this->Accesses[aIdx].Access = this->MemCell.MemAccessTypeSign;
    this->Accesses[aIdx].Addr   = this->MemCell.mCurAddr;
  }

  inline TCycleCount GetMemAccesTime(TLink* lnk,int aPipe)
  {
    TCycleCount res;
    TCycleCount cur_cycles;
    int reset_cycles = 0;

    if(this->mWriteThanRead)
    {
      cur_cycles= (TCycleCount)MYTHIS->PDevice->NumCycles();
      MYTHIS->PDevice->SetCycles(max_val(this->mLastWriteCycle,cur_cycles));
      reset_cycles = 1;
#ifdef LOG_MEM_DELAYS
      printf("WriteThanRead: %d,%d\n",cur_cycles,PDevice->NumCycles());
#endif 
    }
    /*else if(this->mReadThanWrite)
    {
      cur_cycles= (TCycleCount)PDevice->NumCycles();
      PDevice->SetCycles(max_val(mLastReadCycle,cur_cycles));
#ifdef LOG_MEM_DELAYS
      printf("ReadThenWrite: %d,%d\n",cur_cycles,PDevice->NumCycles());
#endif 
      reset_cycles = 1;
    }*/
    
    res = lnk->mArea->SetMemLock(aPipe);

    if(reset_cycles)
    {
      MYTHIS->PDevice->SetCycles(cur_cycles);
    }
    
    if(IFTHIS->MemCell.MemAccessTypeSign == MEM_WRITE)
    {
      this->mLastWriteCycle = res;
    }
    else
    {
      this->mLastReadCycle = res;
    }

    return res;
  }

 
#define MEM_ACCESS_CYCLE() GetMemAccesTime(lnk,aPipe) //lnk->mArea->SetMemLock(aPipe)

  inline TCycleCount MemAccessFifo(TLink* lnk,int aPipe,TCycleCount cur_cycles)
  {   
    vAddrType addr  = IFTHIS->MemCell.mCurAddr;
    TCycleCount final_cycles;
    TCycleCount slot_access_cycles;
    
    if( ((addr >> 24)== 0x10) || ((addr >> 24)== 0xA0) || ((addr >> 24)== 0x20) )// if external memory
      return MEM_ACCESS_CYCLE() + this->mPipeLen;

    int  num_slots = 3;

    if(AccessCount>=num_slots)
    {
      // MEM ACCESS FIFO IS FULL
      TCycleCount min_val = Accesses[0].Cycle;
      int idx = 0;

      for(int i=1; i < num_slots; i++)
      {
        TCycleCount cur = Accesses[i].Cycle; 
        if(cur < min_val)
        {
          min_val = cur;
          idx = i;
        }
      }// end for 

      // set time of access     
      if(min_val > cur_cycles)
      {
        this->PDevice->SetCycles(min_val);
      }

      // get cycles from mem_bus->mem_block
      final_cycles =  MEM_ACCESS_CYCLE() + this->mPipeLen;            

      if(min_val > cur_cycles)
      {
        this->PDevice->SetCycles(cur_cycles);
      }
      // set slot access cycles
      SetAccessCount(final_cycles,idx);
      // return final delay
      return final_cycles ;
    } 
    else // if(AccessCount==MAX_NUM_REQUESTS)
    {
      final_cycles =  MEM_ACCESS_CYCLE() ;   
      SetAccessCount(final_cycles,AccessCount++);
      return final_cycles+ this->mPipeLen;
    } // if(AccessCount==MAX_NUM_REQUESTS)
  }// end of function 
 

  virtual TCycleCount SetMemLock(int aPipe)
  {
    TCycleCount new_cycles;
    TCycleCount mem_lock_count;
    TCycleCount cur_cycles = MYTHIS->PDevice->NumCycles();
    // error if delay is more than 1 cycle
    TLink* lnk = MYTHIS->GetArea(IFTHIS->MemCell.mCurAddr);
    if(lnk==NULL) return 0;


    if(vNumRequests >=100)
      new_cycles = MEM_ACCESS_CYCLE() + this->mPipeLen; 
    else
      new_cycles = MemAccessFifo(lnk,0,cur_cycles);


#ifdef LOG_MEM_DELAYS
    fprintf(stdout,"\ncycles %4d: lock addr %08X, cycles %d delay %d\n",cur_cycles,(uint32)MemCell.mCurAddr,(int)new_cycles,(int)new_cycles - PDevice->NumCycles()); fflush(stdout);
#endif

#ifdef USE_LOGGER
    Logger.Log(LOG_MEM_BUS_ACCESS,(uint32)this,(uint32)this->MemCell.mCurAddr,cur_cycles,(int)new_cycles);
#endif 
    return new_cycles;
  }// end of function
};




#endif


#define MEM_BUS TMemBus

#ifndef SIMPLE_MEM_BLOCK
#define SIMPLE_MEM_BLOCK

#include <datatypes.h>
#include <mem_space.h>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif


inline void* AllocMemBlock(uint32 aSize)
{
  try 
  {
    return (void*)(new char[aSize]);
  }
  catch(...)
  {
    return NULL;
  }
}
// use 1Mb slots
#define SLOT_SIZE   (1024*1024) 
#define SLOT_SHIFT  20

extern void* AllocPtr(int aSize);

class cAllocUnit
{
private:
  uint32 Flags;
  union
  {
    void* Ptr;
    uint32 Ident;
  };

public:
  
  cAllocUnit()
  {
    Flags = 1;
    Ptr = AllocPtr(SLOT_SIZE);
  }          
  ~cAllocUnit()
  {
    if((Flags&1)==0)
    {
      char file_name[256];
      sprintf(file_name,".\\file_%X.swp",Ident);
#ifdef WIN32
      DeleteFileA((LPCSTR)file_name);
#else
	    remove(file_name);
#endif
    }
    else
    {
      delete Ptr;
    }
  }
  
  inline void IncAccess() { Flags+=2; }
  inline uint32 GetNumAccesses() { return Flags >> 1;}
  inline int IsRamPtr() { return Flags&1; }

  inline void* GetPtrNoCheck()
  {
    return Ptr;
  }

  inline void* GetPtr()
  {
    char file_name[256];
    if (Flags&1) return Ptr;
    
    sprintf(file_name,".\\file_%X.swp",Ident);
    FILE* fl = fopen(file_name,"rb");
  
    if(fl==0) 
      return NULL /*!!!*/;
    
    Ptr = AllocPtr(SLOT_SIZE);
 
    if(fread(Ptr,SLOT_SIZE,1,fl)!=SLOT_SIZE)
    {
      fclose(fl);
      return NULL;/*!!!*/
    }
    
    fclose(fl);
#ifdef WIN32
    DeleteFileA((LPCSTR)file_name);
#else
    remove(file_name);
#endif
    Flags|=1;
    return Ptr;
  }

  


  inline void SetSwap(uint32 aIdent)
  {
    char file_name[256];
    FILE* fout;

    sprintf(file_name,".\\file_%X.swp",aIdent); // build file 
    fout = fopen(file_name,"wb");
    fwrite(Ptr,SLOT_SIZE,1,fout);
    fclose(fout);
    Ident = aIdent;
    Flags&= ~((int32)1);
  }
};

typedef cAllocUnit* cAllocUnitPtr;

class cSwapClass
{
private:
  
public:
  static void Init(uint64 MaxRamSize);
  static void Destroy();
  static cAllocUnitPtr AllocUnit();
  static void* AllocPtrFromExistent();
};



template<class vAddrType,class vDataType,class vCellType>
class tSimpleMemBlock : public iMemInterface<vAddrType,vDataType>
{
protected:
  typedef vCellType* vSlot;

  cAllocUnitPtr      *Mems; 
  vAddrType          mSize;
  vAddrType          mCurAddr;
  // last access operation
  vAddrType          mLastAccessAddr;
  TCycleCount        mLastAccessTime;
  eMemAccess         mLastAccessType;
  eMemAccess         mCurAccessType;
  
  eMemWriteMask      mMask; 
  vAddrType          mReadAddr;
  int                mReqProc;
  int                mRwAllow;
  int                mRwStop;
  TCycleCount        mCurAccessCycles;
  TCycleCount        mWaitTime;
  int                sequence_access;
  int                mIsWriteThrow;
  TCycleCount        mPipeLatency;

  inline vDataType& MemBlock(vAddrType aAddr)
  {
    vCellType* cells_ptr;
    uint64 addr_long = (uint64)aAddr;  
#if 1
    
    uint32 aSlot  = (uint32)((addr_long * sizeof(vCellType))/ (SLOT_SIZE));
    uint32 idx = aAddr  - (aSlot * ( SLOT_SIZE/ sizeof(vCellType)));
    // check for sequence access
 
    if(Mems[aSlot]==NULL)
    {
      Mems[aSlot] = cSwapClass::AllocUnit();
    }
    cells_ptr = (vCellType*)Mems[aSlot]->GetPtr();
    return (vDataType&)cells_ptr[idx];  

#else
    uint32 hi_addr = (addr_long >> SLOT_SHIFT;
    uint32 aSlot  = hi_addr * sizeof(vCellType);
    uint32 idx = aAddr  & ~((1<<SLOT_SHIFT)-1);

    // check for sequence access
    if(Mems[aSlot]!=NULL)
    {
      cells_ptr = (vCellType*)Mems[aSlot]->GetPtr();
      return (vDataType&)cells_ptr[idx];  
    }

    Mems[aSlot] = cSwapClass::AllocUnit();
    cells_ptr = (vCellType*)Mems[aSlot]->GetPtrNoCheck();
    return (vDataType&)cells_ptr[idx];

#endif
  }


public:

#define ADDR_BETWEEN(val, lo_lim, hi_lim)  ( (lo_lim <= val) && ( val <= hi_lim ) )
#define SET_SEQ_FLAG()  sequence_access = mIsWriteThrow &&  ADDR_BETWEEN(aAddr,mCurAddr, mCurAddr+2)
  // read data from the memory
  virtual vDataType ReadMem(vAddrType aAddr)
  {
    if(aAddr < this->mSize)
	  {
      SET_SEQ_FLAG(); //((int)((aAddr <= (mCurAddr + 2)) && (aAddr >= mCurAddr)));
      mCurAddr = aAddr;
      mCurAccessType = MEM_ACC_READ;
      return *((vDataType*)(&MemBlock(aAddr)));
    }
    else // this should be a debug message  
      return 0;
  }
  
  // write data to the memorymjhgcxz
  virtual void WriteMem(vAddrType aAddr,vDataType aData)
  {
    if(aAddr < this->mSize)
    {
      SET_SEQ_FLAG();
      mCurAddr = aAddr;
      vDataType* cell = (vDataType*)(&MemBlock(aAddr));
      *cell= aData;
       mCurAccessType = MEM_ACC_WRITE;
    }
    // else - this should be a debug message  
  }

  virtual void WriteMem32(vAddrType aAddr,uint32 aData)
  {
    if(aAddr < this->mSize)
    {
      SET_SEQ_FLAG();
      mCurAddr = aAddr;
      uint32* cell = (uint32*)(&MemBlock(aAddr));
      *cell= (uint32)aData;
       mCurAccessType = MEM_ACC_WRITE;
    }
    // else - this should be a debug message  
  }


  // debug functions
  virtual int getmem(void* aDataArray,vAddrType aAddr,int aSizeInBytes)
  {
    int len = aSizeInBytes/sizeof(vCellType);
    // check if the requested area exist
    if(aAddr+len > this->mSize)
      return 0;
    vCellType* inp = (vCellType*)aDataArray;
    for(int i=0;i<len;i++)
      inp[i] = MemBlock(i+aAddr);
    return len*sizeof(vCellType);
  }
  
  virtual int setmem(void* aDataArray,vAddrType aAddr,int aSizeInBytes)
  {
    int len = aSizeInBytes/sizeof(vCellType);
    // check if the requested area exist
    if(aAddr+len > this->mSize)
      return 0;
   // vCellType *addr_ptr = (vCellType*)&MemBlock(aAddr);
    vCellType* inp = (vCellType*)aDataArray;
    for(int i=0;i<len;i++)
    {
      vCellType* vt = (vCellType*)&MemBlock(i + aAddr);
      *vt= inp[i];
    }
    return len*sizeof(vCellType);
  }
  
  virtual int fillmem(vDataType aVal,vAddrType aAddr,int aSizeInBytes)
  {
    int len = aSizeInBytes/sizeof(vCellType);
    // validate the address and the length 
    if(aAddr + len >= this->mSize)
      return 0;   
    vCellType *addr_ptr = (vCellType*)&MemBlock(aAddr);
    for(int i=0;i<len;i++)
      addr_ptr[i]= aVal;
    return len*sizeof(vCellType);
  }
  
  virtual int GetCellSize(vAddrType aAddr)
  {
    return sizeof(vCellType);
  }  

  virtual void ClearMem()
  {
    for(vAddrType i=0;i<this->mSize;i++)
    {
      vDataType *vt = &MemBlock((vAddrType)i);
      *vt = (vDataType)0;  
    }
  }

  virtual int IsMemInRange(vAddrType aAddr,uint32 aSizeInBytes)
  {
    return 0; 
  }

  // asynchronious access
  virtual void SetAddr(vAddrType aAddr, eMemWriteMask aMask = MEM_MASK_U32)
  {
    mReqProc = true;
    mCurAddr = aAddr;
    mMask = aMask;
  }

  virtual int IsReady()
  {
    return 1;
  }

  virtual void ResetReq(){}
  
  virtual int IsResetSet(){return (mReqProc==true);}

  virtual vDataType WriteData(vDataType aData)
  {
    vDataType wr_data = *((vDataType*)(&MemBlock(mCurAddr)));
    vDataType ref_mask;

#define SET_REF_MASK(bit) ref_mask = ((1<<bit)-1);

    switch (mMask)
    {
      case MEM_MASK_U1:   SET_REF_MASK(1);   break;
      case MEM_MASK_U8:   SET_REF_MASK(8);   break;
      case MEM_MASK_U16:  SET_REF_MASK(16);  break;
      case MEM_MASK_U32:  SET_REF_MASK(32);  break;
      case MEM_MASK_U64:  SET_REF_MASK(64);  break;
      case MEM_MASK_U128: SET_REF_MASK(128); break;
    }

    *((vDataType*)(&MemBlock(mCurAddr))) = (aData & ref_mask) | (wr_data & ~ref_mask);
    mCurAccessType = MEM_ACC_WRITE;
    return aData;
  }

  virtual uint32 WriteData32(uint32 aData)
  {
    *((uint32*)(&MemBlock(mCurAddr)))= aData;
    mCurAccessType = MEM_ACC_WRITE;
    //throw "test exception";
    return aData;
  }

  virtual vDataType GetData()
  {
    vDataType out = *((vDataType*)(&MemBlock(mCurAddr)));
    return out;
  }

  virtual TCycleCount GetDelay(vAddrType aAddr) 
  { 
    return (TCycleCount)mWaitTime; 
  }
  
  virtual void ResetMemMutable()
  {
    mCurAccessCycles = 0; 
    mLastAccessTime = 0;
  }

  virtual TCycleCount SetMemLock(int aPipe)
  {
    TCycleCount cur_init_cycles = (TCycleCount)CurDevice->NumCycles();


    if((mLastAccessAddr == mCurAddr)&&(mLastAccessTime==cur_init_cycles))
      return mCurAccessCycles;
    // set last access time and last  
    mLastAccessTime = cur_init_cycles;
    mLastAccessAddr = mCurAddr;

    //  
    if(mCurAccessCycles > cur_init_cycles)
      cur_init_cycles = mCurAccessCycles;
   
    cur_init_cycles += mWaitTime;  
    mCurAccessCycles = cur_init_cycles;

#ifdef USE_LOGGER
    Logger.Log(LOG_MEM_BLOCK_ACCESS,(uint32)this,mLastAccessTime,mCurAccessCycles + mPipeLatency);
#endif 
    return cur_init_cycles  + mPipeLatency;
  }
  
  inline void SimpleBlockInit(vAddrType aSize,TCycleCount aWaitTime,TCycleCount aPipeLatency,int aIsWriteThrow)
  {
    uint64 super_size = (uint64)aSize;
    uint32 size =  (uint32)((super_size * sizeof(vCellType))/ (SLOT_SIZE )) ;// aSize/(SLOT_SIZE*sizeof(vCellType));
    if((super_size*sizeof(vCellType))&(SLOT_SIZE-1))
      size++;
    
    if(size == 0 ) size = 1;
    mSize = aSize;
   
    Mems = new cAllocUnitPtr[size];
    for(int i=0; i<size; i++) 
      Mems[i] = NULL;// init

    mWaitTime = aWaitTime;

    mReqProc = false;
    mRwAllow = false;
    mRwStop  = false;
    sequence_access = 0;
    mCurAccessCycles = 0;
    mLastAccessAddr = 0xFECDF;
    mIsWriteThrow = aIsWriteThrow;
    mPipeLatency = aPipeLatency;

    this->mLastAccessType = MEM_ACC_READ;
  }
  
  tSimpleMemBlock(vAddrType aSize,TCycleCount aWaitTime=0,TCycleCount aPipeLatency = 0, int aIsWriteThrow = 0)
  {
    SimpleBlockInit(aSize,aWaitTime,aPipeLatency,aIsWriteThrow);  
  }

  tSimpleMemBlock()
  {
  }

  ~tSimpleMemBlock(void)
  {
   // delete mMem;
  }
};

#define MEM_BLOCK tSimpleMemBlock
#endif

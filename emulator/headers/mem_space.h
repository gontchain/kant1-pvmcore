#ifndef MEMORY_SPACE_H
#define MEMORY_SPACE_H

#include <datatypes.h>

#include <device.h>

LIB_EXPORT void CheckError(char* aMsg,int aIsImmideatly);
extern uint32 DbgFlags;


#ifdef SYSTEMC_USED
#include <systemc\systemc.h>
#endif 

typedef enum 
{
  MEM_MASK_U1,
  MEM_MASK_U8,
  MEM_MASK_U16,
  MEM_MASK_U32,
  MEM_MASK_U64,
  MEM_MASK_U128
}eMemWriteMask;

// memory interface
#ifdef SYSTEMC_USED
template<class vAddrType,class vDataType> class iMemInterface: public sc_interface
#else
template<class vAddrType,class vDataType> class iMemInterface
#endif
{
public:
  // function to access the memory from the simulator
  virtual vDataType ReadMem(vAddrType aAddr)=0;
  virtual void WriteMem(vAddrType aAddr,vDataType aData)=0;
  virtual void WriteMem32(vAddrType aAddr,uint32 aData)=0;
  virtual void SetAddr(vAddrType aAddr, eMemWriteMask aMask = MEM_MASK_U32) = 0;
  virtual vDataType WriteData(vDataType aData) = 0;
  virtual uint32 WriteData32(uint32 aData) = 0;
  virtual vDataType GetData() = 0;
  virtual int IsReady() = 0;

  // memory debug functions
  virtual int getmem(void* aDataArray,vAddrType aAddr,int aSizeInBytes)=0;
  virtual int setmem(void* aDataArray,vAddrType aAddr,int aSizeInBytes)=0;
  virtual int fillmem(vDataType aVal,vAddrType aAddr,int aSizeInBytes)=0;
  virtual int GetCellSize(vAddrType aAddr)=0;
  virtual void ClearMem() = 0;
  virtual int IsMemInRange(vAddrType aAddr,uint32 aSizeInBytes)=0;

  // cycle accurate modeling
  virtual TCycleCount GetDelay(vAddrType aAddr) { return 0; }
  virtual void LockMem(int aPipe){}
  virtual void UnlockMem(int aPipe){}
  virtual TCycleCount SetMemLock(int aPipe){ return 0;}
  virtual void ResetMemMutable(){};

  // memory abstractions 
  typedef iMemInterface<vAddrType,vDataType> TMemType;
  // addr bus
  class TAddr
  {
  public:
    TMemType* mMb;
    inline void operator = (vAddrType aVal){ mMb->SetAddr(aVal); }
  };

  // data bus 
  class TData
  {
    public:
      TMemType* mMb;
      eMemWriteMask mMask;
      inline vDataType operator = (vDataType aVal)
      {
        return mMb->WriteData(aVal);
      };     
#ifndef DATA_32BITS
      inline uint32 operator = (uint32 aVal){ mMb->WriteData32(aVal); return aVal; }    
#endif      
      inline operator vDataType() const { return mMb->GetData(); }
  };

  // memory cell incapsulation
#define MEM_WRITE 1
#define MEM_READ  0

  class tMemCell
  {
  public:
    vAddrType mCurAddr;  
    TMemType* mMb;
    int       MemAccessTypeSign;
    // 
    inline vDataType operator =(vDataType aVal)
    { 
      MemAccessTypeSign = MEM_WRITE;
      mMb->WriteMem(mCurAddr,aVal); 
      return aVal;
    }
    // write to mem   
#ifndef DATA_32BITS
    inline uint32 operator =(uint32 aVal)
    { 
      MemAccessTypeSign = MEM_WRITE;
      mMb->WriteMem32(mCurAddr,aVal); 
      return aVal; 
    }    
#endif
    // read mem
    inline operator vDataType() const 
    { 
      return this->mMb->ReadMem(mCurAddr); 
    }
  };// end of tMemCell class


  tMemCell MemCell;
  TAddr  mAddr;
  TData  mData; 
  // constructor
  iMemInterface()
  {  
    MemCell.mMb = (TMemType*)this; 
    mAddr.mMb   = (TMemType*)this; 
    mData.mMb   = (TMemType*)this;
  };
  
  // return memory cell
  inline tMemCell Cells(vAddrType aAddr)
  {
    MemCell.mCurAddr = aAddr;
    MemCell.MemAccessTypeSign = MEM_READ;
    return MemCell;
  }
  
  // return memory cell
  inline tMemCell operator[](vAddrType aAddr) 
  {
    return this->Cells(aAddr);
  }
  // return Addr property
  inline TAddr& Addr()
  {
    return mAddr;
  }

  // return Data property
  inline TData& Data()
  {
    return mData; 
  }
};

#ifdef SYSTEMC_USED
template<class vAddrType,class vDataType> 
class mem_port: public sc_port< iMemInterface<vAddrType,vDataType> > 
{
  typedef iMemInterface<vAddrType,vDataType> cMemInterface;
public:
  inline cMemInterface& bus() 
  { 
    cMemInterface* iff = dynamic_cast<cMemInterface*>(get_interface());
    return *iff; 
  }
  
  inline void operator() (cMemInterface& aIface)
  {
    bind(aIface);
  }
 
  inline operator cMemInterface&() const 
  {
    cMemInterface* iff = dynamic_cast<cMemInterface*>(get_interface());
    return *iff; 
  }
};
#endif

// type of access
typedef enum
{
  MEM_ACC_WRITE,
  MEM_ACC_READ
}eMemAccess;

#endif

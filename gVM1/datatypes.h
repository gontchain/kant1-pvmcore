#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef char int8;
typedef unsigned char uint8;

typedef short int16;
typedef unsigned short uint16;

typedef int int32;
typedef unsigned int uint32;

typedef long long int64;
typedef unsigned long long uint64;

typedef int tbit;

// 
typedef uint32 TTId;
#define NO_TRANSACTION 0xFFFFFFFF

// gcc can't find these functions
#define max_val(a,b)               (((a) > (b)) ? (a) : (b))
#define min_val(a,b)               (((a) < (b)) ? (a) : (b))
#define in_between(x,start,end)    ((start<=x)&&(x<end))

// bits extractor
template<const int vNumBits,class vBaseType>class ppdl_int
{
private:
  vBaseType mVal;

  inline vBaseType mask()
  { 
    return ((vBaseType)1<<vNumBits) - 1; 
  }

public:
  inline operator vBaseType() const
  {
    return (vBaseType)mVal;
  }

  inline vBaseType operator = (vBaseType aVal)
  {
    mVal = aVal & mask();
    return aVal;
  }
};


// output 64-bits data
// low 32 bits of the 64-bits word
#define LO_WRD(val) (uint32)(val&((uint32)(-1)))

// hight 32 bits of the 64-bits word
#define HI_WRD(val) (uint32)(val>>32)

#ifndef NULL
#define NULL 0
#endif

typedef enum
{
  IRQ_RESET = 0,
  IRQ_SET = 1,
}IrqType;

typedef uint32 TCycleCount;
template <class vValTypeDst, class vValType> inline void SetBits(vValTypeDst& dst, int start, int end, vValType aVal)
{
  int diff = (end - start);
  vValType mask = (diff == sizeof(vValType)* 8) ? (vValType)-1 : ((uint64)1 << diff) - 1;
  vValType masked_val = ((vValType)dst) & ~(mask << start);
  vValType new_val = ((vValType)aVal & mask) << start;
  dst = (vValType)(masked_val | new_val);
}


template <class vValType> inline vValType GetBits(vValType aVal, int start, int end)
{
  int diff = (end - start);
  vValType mask = (diff == sizeof(vValType)* 8) ? (vValType)-1 : ((uint64)1 << diff) - 1;
  vValType res = (aVal >> start) & mask;
  return res;

}

template<class vValType> class TBitVP
{
protected:
  vValType*  mVal;
  int       vStart; 
  int       vEnd;
public:
  
  TBitVP(vValType& aVal,int aStart,int aEnd)
  {
    mVal = &aVal;
    vStart = min_val(aStart,aEnd);
    vEnd   = max_val(aStart,aEnd) + 1;
  }

  inline operator vValType() const
  {
    return GetBits(*mVal,vStart,vEnd);
  }

  inline vValType operator = (vValType aVal)
  {
    SetBits(aVal, mVal, vStart, vEnd);
    return *mVal;
  }


};

//template<class vValType> 
class TBitVE
{
protected:
  uint64    mVal;
  int       vStart; 
  int       vEnd;
public:
  
  TBitVE(uint64 aVal,int aStart,int aEnd)
  {
    mVal = aVal;
    vStart = min_val(aStart,aEnd);
    vEnd   = max_val(aStart,aEnd) + 1;
  }

  inline operator uint64() const
  {
#if 0
    return GetBits(mVal, vStart, vEnd);
#else
    int diff = (vEnd - vStart);
    uint64 mask = (diff == sizeof(uint64)* 8) ? (uint64)-1 : ((uint64)1 << diff) - 1;
    uint64 res = (mVal>>vStart) & mask ;
    return res;
#endif
  }
};

typedef uint64 uint160;
typedef uint64 uint256;



#endif

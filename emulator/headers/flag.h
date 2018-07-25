#ifndef PPDL_FLAG_H
#define PPDL_FLAG_H

#include "ppdl_types.h"
#include "pd_reg.h"

// class bit flag
template<class vValType>class tBitFlag
{
private:
  uint32 mBitVal;
  tValPair<vValType>* mReg;
public:
  tBitFlag(uint32 aBitVal,tValPair<vValType>& aReg){mBitVal = aBitVal;mReg = &aReg;}
  
  inline tbit operator = (tbit aVal)
  {
    if((aVal&1)==1)
      mReg->mWrite = mReg->mWrite|(1<<mBitVal);
    else 
      mReg->mWrite = mReg->mWrite&(~(1<<mBitVal));  
    mReg->SetModifyed();   
    return aVal;
  };

  inline operator tbit() const
  {
    return (mReg->mRead>>mBitVal)&1;
  };
  inline tbit operator ~()
  {
    return *this == 1 ? 0:1;
  } 
};



template<typename vFieldTypeH,typename vFieldTypeL, typename vSrc>
  inline vSrc WriteToPairT(tValPair<vFieldTypeH>& aDstH,const int aBitLenH, // hight part of the pair
                           tValPair<vFieldTypeL>& aDstL,const int aBitLenL, // low part of the pair
                           vSrc aSrc)
{
  vFieldTypeL res_l = (vFieldTypeL)(aSrc&(((vSrc)1<<aBitLenL)-1) );
  aDstL = res_l; //(vFieldTypeL)(aSrc&((1<<aBitLenL)-1));

  vFieldTypeH res_h = (vFieldTypeH)((aSrc>>aBitLenL)&(((vSrc)1<<aBitLenH)-1));
  aDstH = res_h;// (vFieldTypeH)((aSrc>>aBitLenL)&((1<<aBitLenH)-1));
  return aSrc;
};

  template<typename vFieldTypeH, typename vFieldTypeL, typename vSrc>
  inline vSrc WriteToPairM(
    TValMutable<vFieldTypeH>& aDstH, const int aBitLenH, // hight part of the pair
    TValMutable<vFieldTypeL>& aDstL, const int aBitLenL, // low part of the pair
    vSrc aSrc)
  {
    vFieldTypeL res_l = (vFieldTypeL)(aSrc&(((vSrc)1 << aBitLenL) - 1));
    aDstL = res_l; //(vFieldTypeL)(aSrc&((1<<aBitLenL)-1));

    vFieldTypeH res_h = (vFieldTypeH)((aSrc >> aBitLenL)&(((vSrc)1 << aBitLenH) - 1));
    aDstH = res_h;// (vFieldTypeH)((aSrc>>aBitLenL)&((1<<aBitLenH)-1));
    return aSrc;
  };

template<typename vFieldTypeH,typename vFieldTypeL, typename vSrc >
  inline vSrc ReadFromPairT(vFieldTypeH aDstH,const int aBitLenH,
                            vFieldTypeL aDstL,const int aBitLenL)
{    
  vSrc res =(vSrc)(aDstL|(aDstH<<aBitLenL));
  return res;
};

#define ReadFromPair  ReadFromPairT<uint64,uint64,uint64>
#define WriteToPair   WriteToPairT<uint32,uint32,uint64>
#define WriteToPairM  WriteToPairM<uint32,uint32,uint64>


#endif
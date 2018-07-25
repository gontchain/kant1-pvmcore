#ifndef PPDL_COMPONENTS_H
#define PPDL_COMPONENTS_H
#include "datatypes.h"

template<class vType> inline void SetValBit(vType& Val,uint32 aNum,tbit aBit)
{
    if(aBit==1) Val = Val|(1<<aNum); else Val = Val&(~(1<<aNum));
}

template<class vType> inline tbit GetValBit(vType Val,uint32 aNum)
{
  return (Val>>aNum)&1;
}

template<class vType> inline vType GetValBitRange(vType Val,uint32 aSBit,uint32 aEBit)
{
#ifdef PPDL_DEBUG
    if((aSBit>=sizeof(vType)*8)||(aEBit>=sizeof(vType)*8)||(aSBit>=aEBit))
      return (vType)0; 
#endif
  return (vType)((Val>>aSBit)&((1<<(aEBit-aSBit))-1));
}

template<class vType> inline void SetValBitRange(vType& Val,uint32 aSBit,uint32 aEBit,vType aVal)
{
#ifdef PPDL_DEBUG
  if((aSBit>=sizeof(vType)*8)||(aEBit>=sizeof(vType)*8)||(aSBit>=aEBit))
    return (vType)0; 
#endif
    Val = ((Val>>aSBit)&~((1<<(aEBit-aSBit))-1))|(aVal&((1<<((aEBit-aSBit)-1))));
}




/*template <class vType> class tBaseType
{
private:
   vType Val;
   
public:
  inline operator tbit(uint32 aNum)
  {
#ifdef PPDL_DEBUG
    if(aNum>=sizeof(vType)*8)
      return 0; 
#endif
    return GetValBit<vType>(Val,aNum);
  }

// operators
// operator set
  operator vType(){ return Val; }
  
  inline  operator  vType(uint32 aNum,tbit aBit)
  {
#ifdef PPDL_DEBUG
    if(aNum<sizeof(vType)*8) return;
#endif
    SetValBit<vType>(Val,aNum,aBit);
  }

  inline operator vType(uint32 aSBit,uint32 aEBit,vType aVal)
  {
#ifdef PPDL_DEBUG
    if((aSBit>=sizeof(vType)*8)||(aEBit>=sizeof(vType)*8)||(aSBit>=aEBit))
      return (vType)0; 
#endif
    return SetValBitRange<vType>(Val,aSBit,aEBit);
  }


  inline vType GetBitRange(uint32 aSBit,uint32 aEBit)
  {
#ifdef PPDL_DEBUG
    if((aSBit>=sizeof(vType)*8)||(aEBit>=sizeof(vType)*8)||(aSBit>=aEBit))
      return (vType)0; 
#endif
    return GetValBitRange<vType>(Val,aSBit,aEBit);
  }

  operator vType(){ return Val; }
  vType operator =(vType aVal){Val = aVal; return Val;}
};
*/



#endif
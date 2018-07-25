#ifndef ASSEMBLY_VARIABLES_H
#define ASSEMBLY_VARIABLES_H

#include <section.h>

// variable type
class tVarType: public tNamedElem
{
public:
  uint32 mBitSize;    // size in bits
  int    mIsSigned;   // 1 if the variable is signed
  int    mIsFloat;    // 1 if the variable is floating point
  tVarType(char* aName,uint32 aBitSize,int aIsSigned=0,int aIsFloat=0);
}; // end of class


#define VAR_TYPE(name,bit_size) new tVarType(name,bit_size)
// assembly variably

struct tVarAsm : public tNamedElem
{
protected:
  void InitData(char* aVal);
public:
  char*      mAddr;        // address of variable
  int        mByteSize;    // size of variable in bytes
  char*      mData; 
  tObjSect*  mSection;     
  // class constructor
  tVarAsm(char* aName,uint32 aAddr,int aSize,char* aVal,tObjSect *aSect);
  // class destructor
  ~tVarAsm();
}; 
#define ASM_VAR(name,addr,size,val) new tVarAsm(name,addr,size,val,this->mCurSect)

#endif
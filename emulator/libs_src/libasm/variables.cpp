#include <variables.h>
#include <stdio.h>

// constructor of the variable type
tVarType::tVarType(char* aName,uint32 aBitSize,int aIsSigned,int aIsFloat):tNamedElem(aName)
{
  this->mBitSize = aBitSize;
  this->mIsFloat = aIsFloat;
  this->mIsSigned = aIsSigned;
}


// constructor of the class tVarAsm
tVarAsm::tVarAsm(uint32 aAddr,int aSize,char* aVal)
{
  // addres of the variable 
  this->mAddr = new char[aAddr/16+5];
  sprintf(this->mAddr,"0x%x",aAddr);
  // value of the variable
  if(aVal!=NULL)
  {
    this->mVal = new char[strlen(aVal)+1];
    strcpy(this->mVal,aVal);
  }; 
  // set size of var in bytes
  this->mByteSize = aSize;
}

// destructor of the class tVarAsm
tVarAsm::~tVarAsm()
{
  delete this->mAddr;
  delete this->mVal;
}

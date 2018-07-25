#ifndef BUFFERS_H
#define BUFFERS_H

#include "datatypes.h"

struct tValue
{
public:
  int     mSize;  //
  char*   mVal;
 // $2 Class constructor
 // $3 Arguments:
 // $4 aSize - a size of the value buffer
 tValue(int aSize);
  ~tValue();
};


class tBytesBuf
{
protected:
  int ExtendBuf();
public: 
  char*       mData;
  uint32      mSize;        // current size of the section
  uint32      mMaxBufSize;  // max buffer size
  tBytesBuf(uint32 aInitSize=65536);
  ~tBytesBuf();
  int Write2Buf(char* aData,uint32 aSize);
  char* AllocBuf(uint32 aSize);
  // write a value into the buffer
  inline int WriteVal(tValue* aVal)
  {
    return this->Write2Buf(aVal->mVal,aVal->mSize);
  };
}; 


#endif
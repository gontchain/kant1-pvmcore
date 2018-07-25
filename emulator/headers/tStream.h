#ifndef STREAM_H
#define STREAM_H
#include "datatypes.h"
#include <stdio.h>

class tStreamBuf
{ 
  char*        BufPtr;
  uint32       BufLen;
  tStreamBuf*  Next;
  tStreamBuf*  Prev;
}; 

class tInsertedBuf:public tStreamBuf
{
  uint32 InsPoint;
};

class tStream
{
protected:
  FILE*   mSrc;    // source file
  uint32  mBufLen; // size of the buffer
  uint32  mPos;    // actual pos in buffer
  char*   mBuf;
public:
  tStream(uint32 aBufLen);
  int IsValid();
  ~tStream(void);
};
#endif
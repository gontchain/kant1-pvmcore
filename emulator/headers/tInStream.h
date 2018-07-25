#ifndef INPUT_STREAM_H
#define INPUT_STREAM_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tStream.h"


class tInStream: public tStream
{
protected:
  // child stream
  tInStream* mChildStream;
  tInStream* mPrevChild;
  uint32    mPrevPos;
  // number of the frame
  uint32 mFrameCount;
  // size of the frame
  uint32 mFrameSize;
  // load buffer from the file
// returns eos if the stream has achieved 0
  int Eos();
// return symbol from the stream
  char GetChar();
// get char with offset
  char NextChar();
// offset stream 
  char GetChar(int32 aIdx);
// shift stream forward
  int ShiftStreamForward(int aOffsVal);
// return a rest of the shifted value
  int GetShiftRest(int aOffsVal);
// load buffer
  virtual void LoadBuf();
  inline void DeleteChildStream()
  {
    assert(this->mChildStream!=NULL);
    // delete previous child stream if any
	if(this->mPrevChild!=NULL)
	  delete this->mPrevChild;

    this->mPrevChild = this->mChildStream;
	this->mPrevPos = this->mPos;
	this->mChildStream = NULL;
  }
public:
// constructor
//    char*  aName - name of the input file
//    uint32 aBufLen - size of the temporary buffer 
  tInStream(uint32 aBufLen = 1024*64);
// class destructor
  ~tInStream(void);
// insert child stream
  void InsertStream(tInStream* aStream);
// return current position of the stream
  uint32 CurPos(); 
// check if the child stream is used
  inline int IsChildStream()
  {
    return (this->mChildStream!=NULL);
  }


// get symbol 
  inline operator char() 
  {
    return this->GetChar();
  }
//  
  inline char operator [](int32 aIdx)
  {
    return this->GetChar(aIdx);
  }

  inline char operator++()
  {
    return this->NextChar();
  }

  inline void operator+=(int aOffsVal)
  {
    this->ShiftStreamForward(aOffsVal);
  }

  inline void SetPrevIdx(uint32 aIdx)
  {
    this->mPos = aIdx;
  }

  inline char* ReadNChars(int aN)
  {
     char* def_text = new char[aN+1];
	   char* dptr = def_text;
     for(int i=0;i<aN;i++)
        *dptr++ = this->NextChar();
     *dptr = 0;
     return def_text;
  }
};

class tInFileStream:public tInStream
{
protected:
// load new portion of data into a buffer
  virtual void LoadBuf();
public:
  tInFileStream(char* aName,uint32 aBufLen = 1024*64);
  ~tInFileStream();
};

// text stream
class tInTextStream:public tInStream
{
protected:

public:
  tInTextStream(char *aText);
};


#include "stream_txt_funcs.h"

#endif
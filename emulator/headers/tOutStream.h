#pragma once
#include "tStream.h"

class tOutStream :public tStream
{
public: 
  char *mFileName;
  tOutStream(char *aName,uint32 aBufSize=1024);
  tOutStream(FILE *aOutStream,uint32 aBufSize=1024);
  int print(const char *str, ...);
  ~tOutStream(void);
};

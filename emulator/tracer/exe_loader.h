#ifndef EXEC_LOADER_H
#define EXEC_LOADER_H
#include "datatypes.h"
#include "dbg_interface.h"


struct TLoadStruct
{
  uint32 InitPc;
  uint32 StopPc;
  char   ErroMsg[512];
  int    IsElf;
};

#define PC_START_OFFSET 6

extern int LoadExecutable(char* aExeName,TDbgInterface* aDev,TLoadStruct* lds);


#endif
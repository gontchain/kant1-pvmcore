#include "exe_loader.h"
#include <stdio.h>

inline int IsAbs(char* aExeName)
{
  char buf[4];
  // open file 
  FILE* f = fopen(aExeName,"rt");
  if(f==NULL)
    return -1;

  // read first 4 bytes of the 
  fread(buf,4,1,f);
  fclose(f);

  // check ELF header
  if( (buf[1]=='E') && (buf[2]=='L') && (buf[3]=='F'))
    return 1;
  else
    return 0;
}

#define RET_ERROR(msg)  sprintf(lds->ErroMsg,msg,aExeName); return 0;


int LoadExecutable(char* aExeName,TDbgInterface* aDev,TLoadStruct* lds)
{
  int is_abs = IsAbs(aExeName);


  if(is_abs==-1)
  {
    RET_ERROR("error: can't open file %s");
  }

  // 
  if (is_abs == 1)
  {
    // load abs file 
    if(aDev->LoadElf(aExeName)==NULL)
    {
      RET_ERROR("error while loading file %s");
    }
    // set start and end of the program
    lds->InitPc = aDev->GetPc(0);
    lds->StopPc = lds->InitPc + PC_START_OFFSET;
    lds->IsElf = true;
    return 1;
  }
  else // if(is_abs) 
  {
#define PROG_BUF_SIZE 1024

    uint32 addrs[2];
    uint32 prog_size = 0;
    char   prog_buf[1024];
    size_t read_size;
    int    cell_size = aDev->GetCellSize(0,0);

    if(cell_size==0)
      cell_size =1;
    
    FILE *f = fopen(aExeName,"rb");
    // load address of the program
    read_size = fread(addrs,1,8,f);
    if(read_size < 8)
    {
      fclose(f);
      RET_ERROR("error while loading %s into the memory");
    }

    do
    {
      read_size = fread(prog_buf,1,PROG_BUF_SIZE,f);
      if(read_size==0)
        break;
      aDev->SetProgMem((void*)prog_buf,addrs[0] + prog_size/cell_size,read_size);      
      prog_size+=read_size;
    }while(read_size==PROG_BUF_SIZE);

    // if no programm loaded at all
    if(!prog_size)
    {
      fclose(f);
      RET_ERROR("error while loading %s into the memory");
    }

    lds->InitPc = addrs[0];
    lds->StopPc = addrs[0] + prog_size;
    lds->IsElf  = false;
    
    aDev->SetPc(lds->InitPc);
    fclose(f);
    return 1;
  }// if(is_abs)
}
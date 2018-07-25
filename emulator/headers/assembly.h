#ifndef ASSEMBLER_TYPES_H
#define ASSEMBLER_TYPES_H
#include <stdio.h>
#include <string.h>

#include "datatypes.h"
#include "asm_macros.h"
typedef unsigned int tTokType;

// binary instruction
struct tBinInst
{
  uint32 mBitSize;   // opcode bit size
  uint32 mInpSize;   // input char size
  uint64 Data;       // instruction opcode
  // class constructor
  tBinInst(uint32 aSize, uint32 aInpSize)
  {
    this->mBitSize = aSize;    // output opcode size in bits
    this->mInpSize = aInpSize; // input char size (in chars)
    this->Data = 0; 
  }  
};

struct tToken
{
  tTokType type;
  union
  {
    unsigned long val;    // imm value
    double        fval;   // imm floating point value
    char          *name;  // name
  };
  unsigned long size;     // size of the token
  char* strval;           // string value
  char* mStart;           // start of the token in the stream
  char* mEnd;             // end of the token in the stream
  // class constructor
  tToken(){ strval = NULL; }
  ~tToken(){ if(size>0) delete strval; }
 
  // initialize token string
  inline void SetTokString(char *ip,char *ep)
  {
    this->mStart = ip;
    this->mEnd = ep;
    size = (unsigned long)ep - (unsigned long)ip;
    strval = new char[size+1];
    memcpy(strval,ip,size);
    strval[size]=0;
  }

  void SetTokString(char *ip,char *ep,char* aStr)
  {
    this->mStart = ip;
    this->mEnd = ep;
    size =0;
    strval = aStr;
  }
};

#define TOK_STR_VAL 1
#define TOK_VAL     2

struct tAsmArg
{
  unsigned long long Val;
  unsigned int       IsSet;
};

inline tBinInst* CreateBinInst(int size, int inp_shift)
{
  tBinInst* bi = new tBinInst(size,inp_shift);
  return bi;
}

#include "tBaseAsm.h"

#endif
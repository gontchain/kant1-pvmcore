#ifndef BASE_ASSEMBLY_H
#define BASE_ASSEMBLY_H

#ifndef ASM_BINARY
#include <Structs.h>
#endif

#include "assembly.h"
#include "tokens.h"
#include "lists.h"
//using namespace std;
void PrintText(const char *text);
extern bool g_echo;
#define ECHO() if( g_echo ) { cout << __FUNCTION__ << "{" << str.c_str() << "}" << endl; }

struct tArea
{
  uint32 aStartAddr;     // start address of the area
  uint32 aEndAddr;       // end address of the area
};

// base assembly
class tBaseAsm
{
public:
  uint32 mDataStartAddr;
  uint32 mDataCurAddr;    // current data address

  uint32 mProgramStartAddr;
  uint32 mProgCurAddr;    // current program address
  uint32 mCellSize;       // size of the Cell in bytes
  uint32 mVarAlignment;   // alignment of the variable
  char*  mAlignmentInst;  // alignment instruction
  // list of variables 
  // init variable types
  int           InitTypes();
  char          mErrString[1024];
  int           mIsEvaluate; // mode of the disassembly
  // current line number
  int           NumLines;

#ifndef ASM_BINARY
  tList<tVarAsm>         *mVars;
  tNamedList<tVarType>   *mTypes;
  tIdentMap     mMapIdent; 
#endif
  uint32  mProgStartAddr;  // start progam address
  bool    mIsProgAddrSet;  //

  int    SetProgAddr(uint32 aAddr);
  int    ResetStartProgAddr(uint32 aAddr);

  // arguments:
  // aStartDataAddr - start addr
  tBaseAsm(uint32 aDataAddr, uint32 aProgAddr);
  tBaseAsm(char* aName);
  //  tBaseAsm();
  ~tBaseAsm(void);
  // get number of lines
  int GetNumLines(int aStartLine,char* str);
  // function returns a size of the instruction in memcells
  int GetInstCellSize(const char* aInst);
  // assembly file
  int Assembly(char* aIStream, uint32* aOutStream);
  // assembly input stream
  int AssemblyStream(char* aIStream, uint32* aOutStream,bool aIncPC=true);
  // functions to process the variable
#ifndef ASM_BINARY 
  // registry variable
  virtual int RegVar(char *aStrType,char* aVal,unsigned int aArrSize,int aScopeId);
  // return variable struct by its index
  tVarAsm* GetVarStruct(int idx);
#endif
  // return size of the program area
  unsigned long GetProgSize(void); 
  unsigned long GetDataSize(void);
  // transform token value
  int TokVal(tToken* aToks,int aCurNum,tAsmArg& aArg,char** ibuf,int aBitSize);
  // get token
  virtual int GetToken(char *istream,tToken *tok) = 0;
  // get expression
  virtual tBinInst* GetExp(char *ibuf)=0;
};  

#define ADD_TO_OUT(out_type,bit_size)\
   case bit_size: *((out_type*)out) = (out_type)inst->Data; out = (uint32*)((uint32)out+bit_size/8); break;

#define ASM_STR_OFFSET 0

#endif
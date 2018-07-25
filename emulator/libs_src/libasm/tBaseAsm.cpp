#include ".\tbaseasm.h"


#ifndef ASM_BINARY
#include "tStripCommentsParser.h"
#include "tExpandMacrosParser.h"
#include "tExpParser.h"
#include "tDecrValParser.h"
#endif

bool g_echo = false;
// initialize data types
int tBaseAsm::InitTypes()
{
#ifndef ASM_BINARY
  // init variable types
  this->mTypes = new tNamedList<tVarType>();
  // add types 
  // 32 bits word
  this->mTypes->Add(VAR_TYPE("word",32));
  // 64 bits long
  this->mTypes->Add(VAR_TYPE("long",64));
#endif
  return 1;
}

// base constructor
tBaseAsm::tBaseAsm(uint32 aStartData,uint32 aStartProg)
{
  // init data area
  this->mDataCurAddr = aStartData;
  this->mDataStartAddr = aStartData;
  // init program area
  this->mProgCurAddr = aStartProg;
  this->mProgramStartAddr = aStartProg;
  // init list of variables
#ifndef ASM_BINARY
  this->mVars = new tList<tVarAsm>(); 
  // init list of data types
  this->InitTypes();
  this->mMapIdent.clear();
#endif
  // set size of the Cell (now it is a constant)
  this->mCellSize = 1;
  this->mVarAlignment = 4;
  this->mAlignmentInst = "nop16";
  // set progstartaddr 
  this->mIsProgAddrSet = false;
}

tBaseAsm::tBaseAsm(char* aName)
{
  // init data area
  this->mDataCurAddr = 0;
  this->mDataStartAddr = 0;
  // init program area
  this->mProgCurAddr = 0;
  this->mProgramStartAddr = 0;
  // init list of variables
#ifndef ASM_BINARY
  this->mVars = new tList<tVarAsm>(); 
  // init list of data types
  this->InitTypes();
  this->mMapIdent.clear();
#endif
  // set size of the Cell (now it is a constant)
  this->mCellSize = 1;
  this->mVarAlignment = 4;
  this->mAlignmentInst = "nop16";
  // set progstartaddr 
  this->mIsProgAddrSet = false;
}

int tBaseAsm::SetProgAddr(uint32 aAddr)
{
  // check if the address has been set 
  if(this->mIsProgAddrSet==true)
    return 0;
  // set address
  this->mProgStartAddr = aAddr;
  this->mIsProgAddrSet = true;
  return 1;
}

int tBaseAsm::ResetStartProgAddr(uint32 aAddr)
{
  // check if the address has been set 
  this->mProgStartAddr = aAddr;
  return 1;
}

// class destructor
tBaseAsm::~tBaseAsm(void)
{
#ifndef ASM_BINARY
  // delete list of the temporary variables
  tVarAsm *tmp_var;
  // delete variables
  FOR_EACH_ELEM(tVarAsm,tmp_var,this->mVars)
    delete tmp_var;
  // delete a list of variables
  delete this->mVars;
#endif
}

#ifndef ASM_BINARY
// create a new variable
int tBaseAsm::RegVar(char *aStrType,char* aVal,unsigned int aArrSize,int aScopeId)
{
  // get type of the variable
  tVarType* tp = this->mTypes->GetElem(aStrType); 
  if(tp==NULL)
  {
    printf("error: a variable type %s is undefined\n",aStrType);
    return 0;
  }
  // add variable into a list
  tVarAsm* vasm = ASM_VAR(this->mDataCurAddr,tp->mBitSize,aVal);
  this->mVars->Add(vasm);
  // calculate an address offset 
  uint32 cell_offs = (tp->mBitSize/(8*this->mCellSize))*aArrSize;
  uint32 rest_of_align = cell_offs % this->mVarAlignment;
  // increment current data address
  this->mDataCurAddr+=cell_offs; 
  // return index of the variable
  return this->mVars->GetIdx(vasm);
}

// get variable pointer by index
tVarAsm* tBaseAsm::GetVarStruct(int aIdx)
{
  return this->mVars->GetElem(aIdx);
}
#endif

#define ADD_TO_OUT(iname,out_type,bit_size)\
   case bit_size: *((out_type*)out) = (out_type)iname->Data; out = (uint32*)((uint32)out + bit_size / 8); break;
//
int tBaseAsm::GetNumLines(int aStartLine,char* str)
{
  while(*str)
  {
    if(*str=='\n') aStartLine++;
    str++;
  }
  return aStartLine;
}

// preprocesss and assembly an input stream
int tBaseAsm::Assembly(char* aInStream, uint32* aOutStream)
{
  int bin_len;
  // get input stream
  try
  {
#ifndef ASM_BINARY
    this->mIsEvaluate = 1; // allow to recognize unknown names as labels 
    string text = string(aInStream);
    // remove comments
	  string no_comments = tStripCommentsParser::Process(text);
    // replace operations like += or -=
    string no_decr_exp = tDecExpParser::Process(no_comments);
    // extract and replace macros,variables and labels
	  string no_macros = tExpandMacrosParser::Process(*this,no_decr_exp, this->mMapIdent,this->GetProgSize());
    // assembly result stream
    this->mIsEvaluate = 0; // no names are decoded as label
    return this->AssemblyStream((char*)no_macros.c_str(),aOutStream);
#else
    this->mIsEvaluate = 0; // no names are decoded as label
    bin_len = this->AssemblyStream(aInStream,aOutStream);
#endif
  }
  catch(char* aExcName) // output exception
  {
    printf(aExcName);
    bin_len = 0;
  }
  catch(...)
  {
    printf("unexpected error\n");
    bin_len = 0;
  }

  return bin_len;
}

int tBaseAsm::TokVal(tToken* aToks,int aCurNum,tAsmArg& aArg,char** ibuf,int aBitSize)
{
  char *tmp_buf = *ibuf;
  tToken tmp_tok;
  if(aToks[aCurNum].type==TOK_VAL)
  {
    int32 val_mask = (1<<aBitSize) - 1;
	  int32 val_inv_mask = ~val_mask;
	  if (((aToks[aCurNum].val&val_mask) != aToks[aCurNum].val) && (((aToks[aCurNum].val&val_mask)|val_inv_mask) != aToks[aCurNum].val)  )
    {
      // push error here
      printf("too big val 0x%X, max val is 0x%X\n", aToks[aCurNum].val, val_mask);
      return 0; // too big value for the instruction
    }
    aArg.Val = aToks[aCurNum].val;
    aArg.IsSet = true;
    return 1;
  }
  return 0;
}

//  assembly char stream
int tBaseAsm::AssemblyStream(char* aIStream, uint32* aOutStream,bool aIncPC)
{ 
  char* sptr  = aIStream;    // input stream pointer 
  uint32* out = aOutStream;  // output file stream


  this->mErrString[0] = 0;
  this->NumLines = 1 ;
  while(*sptr)
  {
	  tBinInst* inst;
    // remove all non_significant symbols untill the end
next_line: 
    while((*sptr==' ')||(*sptr=='\t')||(*sptr=='\n') || (*sptr==13))
    {
      if(*sptr=='\n') NumLines++;
      sptr++;
    }
    
    if ((sptr[0] == '/') && (sptr[1] == '/'))
    {
      sptr+=2;
      while ((*sptr != '\n') && (*sptr != 0)){ sptr++; }
      goto next_line;
    }
    if(*sptr==0) break;

    // decode word 
	  if ((sptr[0] == 'd') && (sptr[1] == 'w') && (sptr[2] == ' '))
	  {
		  tToken t;
		  sptr += 3;
		  MISS_SPACES_PTR(sptr)
		  this->GetToken(sptr,&t);
		  if (t.type == TOK_VAL)
		  {
			  inst = new tBinInst(32, t.val);
			  sptr += t.size;
		  }
		  else
		  {
			  printf("error: unexpected symbol %s\n", t.strval); 
			  return 0;
		  }
	  }
	  else
	  {
		  // decode inst 
		  inst = this->GetExp(sptr);
	  }

	// return 0 if inst has not been detected
    assert(inst!=NULL);
    // shift input size
    // bit size
    if(inst->mBitSize==0)
    {
      // otherwise print output message and return
      printf("error %d: %s\n",NumLines,this->mErrString);
      sptr[inst->mInpSize] = 0;
      printf("incorrect instruction :%s\n",aIStream);   
      // delete instruction
      delete inst;
      // clear intruction stream
      this->mErrString[0] = 0;
      // return
      return 0;
    }

    sptr+=inst->mInpSize;

#define   ALIGN_MASK() (this->mVarAlignment - 1)
#define   OUT_AS_VAL() ((uint32)mProgCurAddr)
#define   IS_NOT_ALIGNED() ((OUT_AS_VAL() & ALIGN_MASK())!=0)

#define ADD_INST(iname)\
    switch (iname->mBitSize) \
    {\
      ADD_TO_OUT(iname,uint8, 8)     \
      ADD_TO_OUT(iname,uint16, 16)   \
      ADD_TO_OUT(iname,uint32, 32)   \
      ADD_TO_OUT(iname,uint64, 64)   \
      default: delete inst; return 0;\
    }


    // check if not aligned    
    if (this->mVarAlignment >0)
    {
     // if (IS_NOT_ALIGNED())
      {
        uint32 align_rest = OUT_AS_VAL() & ALIGN_MASK();
       // while ((inst->mBitSize / (this->mCellSize * 8) + align_rest) > this->mVarAlignment)
        if ((align_rest > 0) && (inst->mBitSize == 32))
        {
          tBinInst* in2 = this->GetExp(this->mAlignmentInst);
          ADD_INST(in2)
          if (aIncPC)
            this->mProgCurAddr += in2->mBitSize / (this->mCellSize * 8);
          delete in2;
        }
      }//  if (IS_NOT_ALIGNED())
    }//if (this->mVarAlignment >0){ 
    // copy data into an output stream
    ADD_INST(inst)
    // increment program address 
    if(aIncPC)
      this->mProgCurAddr+= inst->mBitSize/(this->mCellSize*8);
    // delete instruction structure
    delete inst;
  } // end while
  return (uint32)out - (uint32)aOutStream; // successfully finished
}

// function returns a size of the instruction in bytes
int tBaseAsm::GetInstCellSize(const char* aInst)
{
  uint32 local_buf[128];  // instruction buffer
  return this->AssemblyStream((char*)aInst,local_buf,false)/this->mCellSize;
}

unsigned long tBaseAsm::GetProgSize(void)
{
  return this->mProgCurAddr;
}

unsigned long tBaseAsm::GetDataSize(void)
{
  return this->mDataCurAddr;
}

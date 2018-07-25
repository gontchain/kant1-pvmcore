#ifndef PASE_CFG_H
#define PASE_CFG_H

#include <stdio.h>
#include "stream_txt_funcs.h"
#include <dbg_interface.h>

#define MAX_NAME_SIZE 512

typedef enum
{
  // strings 
  TOC_NAME,   // 
  TOC_INTVAL, //  
  TOC_RFB,    // '}'
  TOC_LFB,    // '}'
  TOC_COMA,   // ','
  TOC_EOEXP,  // ';'
  TOC_DPNT,   // ':'
  TOC_ASG,    // '='
  TOC_EOF,    // end of file
}eTOK_TYPE;


struct tToken
{
  eTOK_TYPE Tok;
  char      Symb[MAX_NAME_SIZE];
  union
  {
    uint64    Val;
    double    DVal;
  };
  int       IsFloatVal;
  int       AbsOffs;
  int       Line;
};


#define SET_TOK_POS()\
  aTok.AbsOffs = mCurPos;\
  aTok.Line    = mCurLine;   


// lexer macros
#define SYMB_TOK(symb, tok_id)\
  case symb:\
  {\
    aTok.Tok = tok_id;    \
    aTok.Symb[0] = symb;  \
    aTok.Symb[1] = 0;     \
    SET_TOK_POS()         \
    mCurPos++;            \
    return 1;             \
  }                       \
  break;

#define DELTA_CHAR(ptr1,ptr2) ((uint32)ptr1 -(uint32)ptr2)

inline int strcmp_test(char* str1,char* str2)
{
  while(*str1==*str2)
  {
    if(*str1==0)
      return 0;
    str1++; str2++;
  }
  return 1;
}


#define IS_NAME(name) (!strcmp(tok.Symb,name)) 
#define ERR_MSG(num) (char*)ErrorMessages[num*2 + mIsRusLang]


// parser macros
#define SKIP_UNTIL_NAME3(name1,name2,name3)\
do\
{\
  if(!GetToken(tok)){PrintError(ERR_MSG(8),mCurPos,tok.Symb); return 0;}\
  if(tok.Tok == TOC_EOF) return 1;\
  if((tok.Tok==TOC_NAME)&&(IS_NAME(name1)||IS_NAME(name2)||IS_NAME(name3)) )break;\
} while(1);\


#define CHECK_DEV_NAME(str,bit) if(IS_NAME(str)){periphery_flags|=1<<(bit);/* printf("device %s found\n",str); */continue;}


#define CHECK_TOK(toktype)\
if(tok.Tok!=toktype) \
{\
  PrintError(ERR_MSG(8),mCurLine,tok.Symb);\
  return 0;\
}

#define CHECK_TOK2(tok1,tok2)\
if( (tok.Tok!=tok1) && (tok.Tok!=tok2) ) \
{\
  PrintError(ERR_MSG(8),mCurLine,tok.Symb);\
  return 0;\
}

#define WAIT_TOK(toktype)\
{\
  if(!GetToken(tok)){PrintError(ERR_MSG(8),mCurPos,tok.Symb); return 0;}\
  CHECK_TOK(toktype)\
}

#define WAIT_TOK2(type1,type2)\
{\
  if(!GetToken(tok)){PrintError(ERR_MSG(8),mCurPos,tok.Symb); return 0;}\
  CHECK_TOK2(type1,type2)\
}

#define WAIT_NAME(name)\
{\
  WAIT_TOK(TOC_NAME)\
  if(strcmp(tok.Symb,name)){ PrintError(ERR_MSG(8),tok.Line,tok.Symb); return 0;}\
}

struct tMemSet
{
  char          name[MAX_NAME_SIZE];
  uint32        set_flags;
  SDRamConfig   Config;
};


#define PARAM_MEM_KIND          1
#define PARAM_PAGE_SIZE         2
#define PARAM_REGEN_PERIOD      4
#define PARAM_REGEN_TIME        8
#define PARAM_PAGE_OPEN_TIME   16
#define PARAM_PAGE_CLOSE_TIME  32
#define PARAM_LATENCY          64
#define PARAM_MUL_FACTOR       128

#define PARAM_SSMEM_KIND       256
#define PARAM_SRAM_LATENCY     512


// parser class
class tParseCfg
{
private: 
  char*     mStream;    // 
  int       mCurPos;    // current abs file position
  int       mCurLine;   // current line
  tMemSet   mMemSets[100]; // array of memsets
  int       mCurMemSet;
  ChipMem*  mCm;
  int       mIsRusLang;

  uint32    GetCfgFileSize(char* aFName);
  int       ReadStream(char* aName,uint32 size);
  int       GetToken(tToken& aTok);
  void      MissSeparators();
  int       Parse();
  int       ValidateMemsetParams();
  tMemSet*  GetMemSet(char* aName);
  
  int FillParamI(char* aName,uint64 aVal);
  int FillParamF(char* aName,double aVal);
  int FillParamS(char* aParamName,char* aName,int aLineNum);

public:
  void PrintError(char* aMsg,...);

  tParseCfg(char  *aConfFileName,ChipMem* aCm,int aIsRusLang);
  ~tParseCfg(void);
 
};

#define PARAMS_INT()\
  ADD_PARAM("CASLatency",mLatency,PARAM_LATENCY);\
  ADD_PARAM("RefreshPeriod",mRegenPeriod,PARAM_REGEN_PERIOD);\
  ADD_PARAM("RefreshDuration",mRegenTime,PARAM_REGEN_TIME);\
  ADD_PARAM("PageOpenTime",mPageOpenTime,PARAM_PAGE_OPEN_TIME);\
  ADD_PARAM("PageCloseTime",mPageCloseTime,PARAM_PAGE_CLOSE_TIME);\
  ADD_PARAM("PageSize",mPageSize,PARAM_PAGE_SIZE);

#define PARAMS_ALL()\
  PARAMS_INT()\
  ADD_PARAM("FreqRatio",mMulFactor,PARAM_MUL_FACTOR);\
  ADD_PARAM("RAMType",mKind,PARAM_MEM_KIND);



extern int bsp_parser(char* path_bsp_file,ChipMem* aCm,int rus_lang);


#endif

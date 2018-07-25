#ifndef ASSEMBLY_MACROS_H
#define ASSEMBLY_MACROS_H
#include <string.h>
#include <stream_txt_funcs.h>

// end of line or end of file
#define TOK_EOL			1


// the following set of macros is used by function GetTok
#define RET_OFFSET() return (uint32)sp - (uint32)istream;

#define IS_NOT_STRING(symbol) !IsSymb(symbol) 

#define RET_TOK(tnum)\
  tok->type = tnum; \
  tok->SetTokString(tbegin,sp);\
  RET_OFFSET()

#define MISS_SPACES_PTR(sp) while((*sp==' ')||(*sp=='\t')) sp++;
// miss spaces and tabs
#define MISS_SPACES() MISS_SPACES_PTR(sp)

// remove comments string 
#define REMOVE_COMMENTS(prefix)\
  if(strncmp(sp,prefix,strlen(prefix))==0)\
  {\
    while((*sp!=0xd)&&(*sp!=0xa)&&(*sp!=0)) sp++; \
    /*if(*sp==0xd) sp+=2; */\
    goto GET_TOKEN; \
  }

#define CHECK_EOL()\
  if (*sp == '\r'){ sp += 2; tok->type = TOK_EOL; tok->SetTokString(tbegin, sp, "end_of_line"); RET_OFFSET() }; \
  if (*sp == '\n'){ sp += 1; tok->type = TOK_EOL; tok->SetTokString(tbegin, sp, "end_of_line"); RET_OFFSET() }; \
  if (*sp == 0){ tok->type = TOK_EOL; tok->SetTokString(tbegin, sp, "end_of_file"); RET_OFFSET() };

// decode values
// check decimal value
#define IS_DEC() (((*sp>='0')&&(*sp<='9'))||((*sp=='-')&&((sp[1]>='0')&&(sp[1]<='9'))))
#define IS_HEXP() ((*sp=='0')&&(sp[1]=='x'))

// decode HEX value
#define DECODE_HEX(tok)\
{\
   sp+=2;\
   while(1)\
   {\
     if(IS_DEC()){tok->val =(tok->val<<4) + *sp - '0'; sp++;}\
     else if((*sp>='a')&&(*sp<='f')){tok->val =(tok->val<<4) + *sp - 'a' + 10; sp++;}\
     else if((*sp>='A')&&(*sp<='F')){tok->val =(tok->val<<4) + *sp - 'A' + 10; sp++;}\
     else{tok->SetTokString(tbegin,sp); return (uint32)sp - (uint32)istream;}\
   }\
}

// decode decimal value
#define DECODE_DEC(tok)\
{\
  int is_neg=1; if(*sp=='-'){ is_neg=-1; sp++;}\
  while(IS_DEC(*sp)){tok->val= tok->val*10 + (*sp - '0'); sp++;}\
  tok->val = (uint32)(tok->val*is_neg);\
  tok->SetTokString(tbegin,sp);\
  return (uint32)sp - (uint32)istream;\
}

#if 1


#define DECODE_VAL(tok)\
{\
  return ExtractTokVal(tok,sp,tbegin,istream);\
}


#else
// decode hex or decimal value
#define DECODE_VAL(tok)\
{\
  tok->type = TOK_VAL; tok->val = 0;\
  if(IS_HEXP()){ DECODE_HEX(tok) } else { DECODE_DEC(tok) }\
}
#endif



#define SET_TOK_NAME(tok)\
  if(IsFirstSymb(*sp))\
  {\
    sp++; while (IsSymb(*sp)) sp++; tok->type = TOK_STR_VAL; \
    tok->SetTokString(tbegin,sp); \
    return (uint32)sp - (uint32)istream;\
  } 
 

// return error token
#define ERR_TOK(tok)\
{\
  SET_TOK_NAME(tok) \
  if(*sp==0) tok->type = 1; else tok->type = 0; \
  tok->SetTokString(tbegin,sp); \
  sprintf(mErrString,"unexpected string %s",tok->strval); \
  return (uint32)sp - (uint32)istream + 1; \
}

// the following set of macros is used to decode an instruction
// set error 
// instruction related macros

#define SET_ERR_INST(level)\
{\
  if((t[max_idx].type ==0)||(t[max_idx].type ==1)){\
    sprintf(mErrString,"can't parse assembly string %s",t[level].strval);\
  }else if(t[max_idx].strval!=NULL){\
    sprintf(mErrString,"unexpected symbol %s",t[max_idx].strval);\
  }else{\
     sprintf(mErrString,"wrong symbols sequence");\
  }\
  tBinInst* bi = new tBinInst(0,(uint32)ibuf - (uint32)*aInpStr); \
  *aInpStr = ibuf;\
  return bi;\
}

// macros are used by the generated assembler
#define NEXT_TOK_INST(tnum)\
if((*tcount)<tnum){\
  ibuf+=GetToken(ibuf,&t[tnum]);\
  if((tnum==0)&&(*ibuf==0)&&(t[0].type==1))\
  {\
    return new tBinInst(0,(uint32)ibuf - (uint32)aInpStr);\
  }\
  (*tcount) = tnum;\
}\
if(tnum > max_idx) max_idx = tnum;

// argument related macros
#define SET_ERR_ARG(level)\
{\
  if((t[level].type==0)||(t[level].type ==1)){\
    sprintf(mErrString,"can't parse assembly string %s",t[level].strval);\
  }else if(t[level].strval!=NULL){\
    sprintf(mErrString,"unexpected symbol %s",t[level].strval);\
  }\
  *aInpStr = ibuf;\
}

#define NEXT_TOK_ARG(tnum)\
if((*tcount) < tnum ){\
  ibuf+=GetToken(ibuf,&t[tnum]);\
  if((tnum==0)&&(*ibuf==0)&&(t[0].type==1))\
  {\
    return -1;\
  }\
  *tcount = tnum;\
}

// check if the argumen value is repeated
#define CHECK_SET_ARG_ISET(argv,new_val)\
if(argv.IsSet == 0)\
{\
  argv.Val = new_val; \
  argv.IsSet = 1; \
}\
else if (argv.Val != new_val)\
{\
    sprintf(error_message,"instruction %s:the same argument is mentioned twice with different values\n",*aInpStr); \
    tBinInst* bInst = CreateBinInst(0, (uint32)ibuf - (uint32)aInpStr); \
    return bInst; \
}

#define CHECK_SET_ARG_LST(arg,new_val)\
if (arg.IsSet == 0){\
  arg.Val = new_val; \
  arg.IsSet = 1; \
}\
else if (arg.Val != new_val)\
{\
  printf("instruction %s:the same argument is mentioned twice with different values", aInpStr); \
  return -1; \
}

#define ASSIGN_ARG(out_arg,in_arg)\
if (out_arg->IsSet == 0){\
  out_arg->Val = in_arg.Val; \
  out_arg->IsSet = 1; \
}else if (out_arg->Val != in_arg.Val){\
  printf(mErrString, "the same argument is mentioned twice with different values"); \
  return -1; \
}

#define SET_ARG_VAL(val)\
if (arg->IsSet == 1)\
{\
  if (arg->Val != val)\
  {\
    printf(mErrString, "the same argument is mentioned twice with different values"); \
    return -1; \
  }\
}\
else\
{\
  arg->Val = val; \
  arg->IsSet = 1; \
}

#define GET_DEC_VAL(tok)\
{\
  int is_neg = 1; tok->val = 0; if (*sp == '-'){ is_neg = -1; sp++; }\
  while (IS_DEC()){ tok->val = tok->val * 10 + (*sp - '0'); sp++; }\
  tok->val = (uint32)(tok->val*is_neg); \
}


// reset argument values
#define INIT_ARG(argv)\
{\
   argv.Val = 0;\
   argv.IsSet = (int)0;\
}

#define INIT_ARG_NOPRINT(argv)  { fflush(stdout); argv.Val = 0; argv.IsSet = (int)0;}
#define INIT_ARGS(num) for(int icount = 0; icount < num; icount++) INIT_ARG_NOPRINT(arg[icount])
#define BIN_INSN(type_out) *((type_out*)insn)
#define PROCESS_INSN_GET(code,shift,mask) *imm_val =  (code >> shift) & mask;
#define PROCESS_INSN_SET(code,shift,mask) code =  (code  & (mask<<shift)) | ( (*imm_val&mask) << shift);


#endif
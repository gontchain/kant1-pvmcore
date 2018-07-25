#include "tParseCfg.h"
#include "stdio.h"
#include <stdarg.h>

#include <stdexcept>


const char ErrorMessages[20][128] = 
{
  //0
  "error: Can't open config file %s\n",
  "ошибка: невозможно открыть конфигурационный файл %s\n",
  //1
  "error: Parameter %s is undefined\n",
  "ошибка: Не определён параметр %s\n",
  //2
  "error %d: Unexpected kind of memory %s\n",
  "ошибка %d: Неопределён тип памяти %s\n",
  //3
  "error %d: Unexpected parameter SSType for non-SSRAM memory type\n",
  "ошибка %d: Неожиданное появлениее параметра SSType для не-SSRAM памяти\n",
  //4
  "error %d: Unexpected name of SSRAM type %s\n",
  "ошибка %d: Неизвестное название типа SSRAM-памяти %s\n",
  //5
  "error %d: Unknown parameter %s \n",
  "ошибка %d: Неизвестное имя параметра %s\n",
  //6
  "error %d: Illegal value of memset %s\n",
  "ошибка %d: Недопустимое значение memset %s\n",
  //7 
  "error %d: Undefined name %s\n",
  "ошибка %d: Неизвестное имя %s\n",
  //8
  "error %d : unexpected token %s",
  "ошибка %d: неожиданное появление %s",
  //9
  "error %d: unknown name of peripheral device - %s",
  "ошибка %d: неизвестное периферийное устройство - %s"
};

#define ERR_MSG(num) (char*)ErrorMessages[num*2 + mIsRusLang]
void tParseCfg::PrintError(char* aMsg,...)
{
  va_list(arglist);
  va_start(arglist, aMsg);
  char msg_buf[512]; // temp message buffer
  vsprintf(msg_buf,aMsg,arglist);
  throw std::runtime_error(msg_buf);
}

tParseCfg::tParseCfg(char  *aConfFileName,ChipMem* aCm,int aIsRusLang)
{
  tToken tok;
  uint32 file_size = GetCfgFileSize(aConfFileName);
  mIsRusLang = aIsRusLang;
  mCm = aCm;
  aCm->m_BankNum = 0;
  if(file_size==0)
  { 
    PrintError(ERR_MSG(0),aConfFileName);
    return;
  }
  mStream = new char[file_size +1];
  ReadStream(aConfFileName,file_size);
  mStream[file_size] =0;
  mCurPos = 0;
  mCurLine = 1;
  mCurMemSet = 0;
  // start parse
  if(!Parse())
    aCm->m_BankNum = 0; // parse error
}

tParseCfg::~tParseCfg(void)
{
}

uint32 tParseCfg::GetCfgFileSize(char* aFileName)
{
  uint32 size;
  FILE* f = fopen(aFileName,"rb");
  if(f==NULL)
    return 0;
  fseek(f,0,SEEK_END);
  size = ftell(f);
  fclose(f);
  return size;
}

int tParseCfg::ReadStream(char *aName, uint32 size)
{
  FILE* f = fopen(aName,"rb");
  uint32 len = fread(mStream,1,size,f);
  fclose(f);
  return len;
}

const char Separators[] ={0x0D,0x0A,' ','\t',0};


void tParseCfg::MissSeparators()
{
  while(InTextSet(mStream[mCurPos],(char*)Separators))
  { 
    if(mStream[mCurPos]=='\n')
      mCurLine++;
    mCurPos++;
  }
}

int tParseCfg::GetToken(tToken &aTok)
{
BEGIN_GET_TOK:
  MissSeparators();
  
  if(IsFirstSymb(mStream[mCurPos]) || (mStream[mCurPos]=='"'))
  {
    int str_len;
    char* cptr = mStream + mCurPos + (mStream[mCurPos]=='"');
    char* start_ptr = cptr;
    while(IsSymb(*cptr)) cptr++;// find the end of the name
    str_len = DELTA_CHAR(cptr,start_ptr);
    // fill token struct
    memcpy(aTok.Symb,start_ptr,str_len);
    aTok.Symb[str_len] = 0;
    if(mStream[mCurPos]=='"')
    {
      if(*cptr=='"')
        str_len+=2;
    }

    aTok.Tok = TOC_NAME;
    aTok.AbsOffs = mCurPos;
    aTok.Line = mCurLine;
    mCurPos += str_len;
    return 1;
  }
  else if(IsDigit(mStream[mCurPos]))
  {
    char *cptr = mStream + mCurPos;
    int len = 0;
    int is_float;
      
    uint64 val = 0;
    
    if(IsHexPrefix(cptr))
    {
      cptr+=2;
      mCurPos+=2;
      aTok.Val = GetHex<uint64>(cptr,len);
      aTok.IsFloatVal = 0;
    }
    else // decimal value
    {
      aTok.Val = GetDig<uint64>(cptr,len,aTok.IsFloatVal);     
    }

    if(len==0)
      return 0; // wrong token
    aTok.Tok = TOC_INTVAL;
    memcpy(aTok.Symb,mStream + mCurPos,len);
    aTok.Symb[len] = 0;
    SET_TOK_POS();
    mCurPos += len;
    return 1;
  }
  else
  {
    switch(mStream[mCurPos])
    {
      case '/':
        {
          char *cptr = mStream + mCurPos;
          if(*cptr==(char)'/') // comments
          {
            // single line comment - miss symbols until the end of line (or end of stream)
            while((*cptr!=(char)'\n')&&((*cptr)!=(char)0)) cptr++;
          }
          else if(*cptr==(char)'*') // multi-line comments
          {
            // multi-line comment - miss symbols until the '*/' sequence
            cptr++;// shift to the begin of comment
            while(*cptr!=(char)0)
            {
               if((*cptr=='*')&&(cptr[1]=='/')) // check end of the commennt
               {
                  cptr+=2;
                  return 1;// start process token from the beginning
               }
               // new line
              cptr++;
            }
          }// else if(*cptr==(char)'*') 
          else
          {
            mCurPos++;
            return 0;
          }
          mCurPos = DELTA_CHAR(cptr,mStream);
        }// end of token
        goto BEGIN_GET_TOK;
        break;

      SYMB_TOK(',',TOC_COMA)
      SYMB_TOK('{',TOC_LFB)
      SYMB_TOK('}',TOC_RFB)
      SYMB_TOK(':',TOC_DPNT)
      SYMB_TOK(';',TOC_EOEXP) // end of expression    
      SYMB_TOK('=',TOC_ASG) // end of expression    
      case 0: aTok.Tok = TOC_EOF; return 1;
      default:  aTok.Symb[0] = mStream[mCurPos]; aTok.Symb[1] = 1; mCurPos++; return 0;
    }
    return 0;
  }
}

#define ADD_PARAM(param_name,member,flag) if(!(mMemSets[mCurMemSet].set_flags&flag)){PrintError(ERR_MSG(1),param_name);return 0;}

int tParseCfg::ValidateMemsetParams()
{
  if(mMemSets[mCurMemSet].Config.mKind == SMEM_SDRAM)
  {
    PARAMS_ALL()  
  }
  else if(mMemSets[mCurMemSet].Config.mKind == SMEM_SSRAM)
  {
    ADD_PARAM("CASLatency",mLatency,PARAM_LATENCY); 
    ADD_PARAM("SSType",mKind,PARAM_SSMEM_KIND);
  }
  else // SRAM
  {
    ADD_PARAM("Latency",mLatency,PARAM_SRAM_LATENCY);
  }
   
  return 1;
}

#undef ADD_PARAM

int tParseCfg::FillParamS(char* aParamName,char* aName,int aLineNum)
{
  if(!strcmp(aParamName,"RAMType"))
  {
    mMemSets[mCurMemSet].set_flags |=1;
    if(!strcmp(aName,"SRAM"))
    {
      mMemSets[mCurMemSet].Config.mKind = SMEM_SRAM;
      return 1;
    }
    else if(!strcmp(aName,"SSRAM"))
    {
      mMemSets[mCurMemSet].Config.mKind = SMEM_SSRAM;
      return 1;
    }
    else if(!strcmp(aName,"SDRAM"))
    {
      mMemSets[mCurMemSet].Config.mKind = SMEM_SDRAM;
      return 1;
    } 
    PrintError(ERR_MSG(2),aName,aLineNum);
  }
  else if (!strcmp(aParamName,"SSType"))
  {
    if(mMemSets[mCurMemSet].Config.mKind!=SMEM_SSRAM)
    {
      PrintError(ERR_MSG(3), aLineNum);
    }
    if(!strcmp(aName,"Pipelined"))
      mMemSets[mCurMemSet].Config.mSSramLKind = SSMEM_PIPELINED;
    else if(!strcmp(aName,"FlowTrough"))
      mMemSets[mCurMemSet].Config.mSSramLKind = SSMEM_FLOWTROUGH;
    else
    {
      PrintError(ERR_MSG(4), aLineNum,aName);
      return 0;
    }
    mMemSets[mCurMemSet].set_flags |=PARAM_SSMEM_KIND;
    return 1;
  }
  else
  {
    PrintError("error %d: unexpected value %s  of parameter %s\n",aLineNum,aName,aParamName);
    return 0; 
  }
  
  return 0;
}

#define ADD_PARAM(param_name,member,flag)\
  if(!strcmp(aName,param_name)){ mMemSets[mCurMemSet].Config.member = aVal; mMemSets[mCurMemSet].set_flags |=flag; return 1;}

int tParseCfg::FillParamI(char* aName,uint64 aVal)
{
  PARAMS_INT()
  ADD_PARAM("Latency",mLatency,PARAM_SRAM_LATENCY); 
  return 0;
}

int tParseCfg::FillParamF(char* aName,double aVal)
{
  ADD_PARAM("FreqRatio",mMulFactor,PARAM_MUL_FACTOR);
  return 0;
}

tMemSet* tParseCfg::GetMemSet(char* aName)
{
  for(int i=0;i<mCurMemSet;i++)
    if(!strcmp(mMemSets[i].name,aName))
      return &mMemSets[i];

  return NULL;
}

int tParseCfg::Parse()
{
  tToken tok;
  while(1) // parse all sections of the file
  {
    SKIP_UNTIL_NAME3("MEMSETS","MEMORY","PERIPHERY");
    if(IS_NAME("MEMSETS"))
    {
      // decode list of memsets
      WAIT_TOK(TOC_LFB)
      while(1)
      { 

        WAIT_TOK2(TOC_RFB,TOC_NAME);
        if(tok.Tok == TOC_RFB)
        {
          break;
        }
        // store name 
        strcpy(mMemSets[mCurMemSet].name,tok.Symb); 
        mMemSets[mCurMemSet].set_flags = 0;
        mMemSets[mCurMemSet].Config.mMulFactor = 1.0;
        WAIT_TOK(TOC_DPNT);
        // parse arguments
        do
        {
          char param_name[MAX_NAME_SIZE];
          WAIT_TOK2(TOC_EOEXP,TOC_NAME);
          if(tok.Tok==TOC_EOEXP)
          {
            if(ValidateMemsetParams())
              return 0;
            mCurMemSet++;
            break;
          }    
          // name of param
          strcpy(param_name,tok.Symb);
          // 
          WAIT_TOK(TOC_ASG);
          WAIT_TOK2(TOC_INTVAL,TOC_NAME);
          
          if(tok.Tok == TOC_NAME)
          {
            // 
            if(!FillParamS(param_name,tok.Symb,tok.Line))
              return 0;
          }// end if
          else // int or float value
          {
            int fill_res;
            if(tok.IsFloatVal == 0)
              fill_res = FillParamI(param_name,tok.Val);
            else
              fill_res = FillParamF(param_name,tok.DVal);

            if(fill_res == 0)
            {
              PrintError(ERR_MSG(5),tok.Line,param_name);
              return 0;
            }
          }//  if(tok.Tok == TOC_NAME)
          WAIT_TOK2(TOC_COMA,TOC_EOEXP)

        }while(tok.Tok !=TOC_EOEXP);// end of parse param
        
        if(!ValidateMemsetParams())
          return 0;
        mCurMemSet++;
      }// end of parser 
    }// end of memset decode, then decode memory
    else if(IS_NAME("MEMORY")) // mem blocks;
    {
      WAIT_TOK(TOC_LFB)
      // extract memory block description
      while(1) // block1: at 0x1111, len = 0x44000, [memset = memset_name ] |  ( ws = 3) 
      {
        uint64      start_addr;
        uint64      len;
        bool        len_set = false;
        int         wait_state=0;
        char        memset_name[MAX_NAME_SIZE];
        tMemSet*    memset = NULL;

        WAIT_TOK2(TOC_NAME,TOC_RFB);
        if(tok.Tok == TOC_RFB)
          break; //end of section parsing
        // otherwise parse memory block
        WAIT_TOK(TOC_DPNT);
        WAIT_NAME("at");
        WAIT_TOK(TOC_INTVAL);
        start_addr = tok.Val;

        WAIT_TOK(TOC_COMA);
        WAIT_NAME("len");
        WAIT_TOK(TOC_ASG);
        WAIT_TOK(TOC_INTVAL);
        len = tok.Val;
        
        WAIT_TOK2(TOC_COMA,TOC_EOEXP);
      
        if(tok.Tok==TOC_EOEXP)
        {
          wait_state = 0;
        }
        else
        {  
          WAIT_TOK(TOC_NAME);
          // define waitstate or memset 
          if(IS_NAME("ws"))// if just waitstate
          {
            WAIT_TOK(TOC_ASG)
            WAIT_TOK(TOC_INTVAL)
            wait_state = tok.Val;
          }
          else if(IS_NAME("memset"))
          {
            WAIT_TOK(TOC_ASG);
            WAIT_TOK(TOC_NAME);          
            memset = GetMemSet(tok.Symb);
            if(memset == NULL)
            {
              PrintError(ERR_MSG(6),tok.Line,tok.Symb);
              return 0;
            }
          }// 
          else
          {
            PrintError(ERR_MSG(7),tok.Line,tok.Symb);
            return 0;
          }
          // end of expression
          WAIT_TOK(TOC_EOEXP);
        }//   if(tok.Tok==TOC_EOEXP)
        // fill memblock structure
        mCm->p_startAddr[mCm->m_BankNum] = (unsigned long)start_addr;
        mCm->p_Size[mCm->m_BankNum] = (unsigned long)len;

        if(memset == NULL)
        {
          // just watistate has been added
          mCm->p_WriteWaitTime[mCm->m_BankNum] = 1001;
          mCm->p_ReadWaitTime[mCm->m_BankNum] = wait_state;
          mCm->p_Configs[mCm->m_BankNum].mPageSize = 0;
        }
        else
        {
          // copy params	
          mCm->p_Configs[mCm->m_BankNum] = memset->Config;

          if(memset->Config.mKind == SMEM_SDRAM)
          {
            // config is need for SDRAM only
            mCm->p_WriteWaitTime[mCm->m_BankNum] = 1;
            mCm->p_ReadWaitTime[mCm->m_BankNum]  = 2;// memset->Config.mLatency;
          }
          else
          {
            mCm->p_WriteWaitTime[mCm->m_BankNum] = mCm->p_ReadWaitTime[mCm->m_BankNum] = (float)memset->Config.mLatency;
          }

        }
        mCm->m_BankNum++; // increment bank num
      } // while(1)
    }
    else if(IS_NAME("PERIPHERY"))
    {
      WAIT_TOK(TOC_ASG);
      int periphery_flags = 0;
      do
      {
        WAIT_TOK2(TOC_EOEXP,TOC_NAME)
        if(tok.Tok == TOC_EOEXP)
          break;
        // name of device
        CHECK_DEV_NAME("com0",0)
        CHECK_DEV_NAME("com1",1)
        CHECK_DEV_NAME("pcache",2)
        CHECK_DEV_NAME("pu",3)

        PrintError(ERR_MSG(9),tok.Line,tok.Symb);      
      }while(1);
      mCm->m_Flags |= periphery_flags<<PERIPHERAL_OFFSET; 
    }
  }// end of while(1) which parse the cfg
}

int bsp_parser(char* path_bsp_file,ChipMem* aCm,int rus_lang)
{
  tParseCfg* cfg = new tParseCfg(path_bsp_file,aCm,rus_lang);
  delete cfg;
  return (aCm->m_BankNum !=0);
}

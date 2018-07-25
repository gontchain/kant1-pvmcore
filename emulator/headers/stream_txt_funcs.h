#ifndef  STREAM_TEXT_FUNCTIONS_H
#define STREAM_TEXT_FUNCTIONS_H
#include <tInStream.h>
#include <stdio.h>
// a set of functions to operate within a text stream
// return 1 if the text is in the symbol range
inline int InTextRange(char val,char sp,char ep)
{
  return (val>=sp)&&(val<=ep);
}
// return 1 if the symbol
inline int NotInTextRange(char val,char sp,char ep)
{
  return (val<sp)||(val>ep);
}

// return 1 if the symbol belongs to the set
inline int InTextSet(char val,char* set)
{
  while(*set!=0){if(val==*set++)return 1;}return 0;
}


inline int NotInTextSet(char val,char* set)
{
  while(*set!=0){if(val==*set++)return 0;}return 1;
}

inline char* add(char* str1,char *str2)
{
  int str1_len = strlen(str1);
  int str2_len = strlen(str2);
  char *res = new char[str1_len+str2_len];
  strcpy(res,str1); strcpy(&res[str1_len],str2);
  return res;
  }


template<class vInpType> inline int IsPrefixP(vInpType* val,char* prefix)
{
  int sz = strlen(prefix);
  for(int i=0;i<sz;i++)
  {
    if(val[i] != *prefix++)
      return 0;
  }
  return 1;
}

template<class vInpType> inline int IsPrefix(vInpType& val,char* prefix)
{
  int sz = strlen(prefix);
  for(int i=0;i<sz;i++)
  {
    if(val[i] != *prefix++)
      return 0;
  }
  return 1;
}

inline int IsTextPrefix(tInStream&  val,char* prefix)
{
  return IsPrefix<tInStream>(val,prefix);
}

inline int IsTextPrefix(char* val,char* prefix){ return IsPrefixP<char>(val,prefix);}

inline int IsDigit(char val){ return InTextRange(val,'0','9');}
inline int IsHexPrefix(tInStream& val){return IsTextPrefix(val,"0x");}
inline int IsBinPrefix(tInStream& val){return IsTextPrefix(val,"0b");}

inline int IsHexPrefix(char* val){return IsTextPrefix(val,"0x");}
inline int IsBinPrefix(char* val){return IsTextPrefix(val,"0b");}
//template<class vStream> 

template<class vOutType> inline vOutType GetDig(tInStream& str)
{
   vOutType val=0;
   while(IsDigit(str))
   {
     val=(val*10)+(unsigned long)(str)-0x30;
     ++str;
   }
   return val;
}

template<class vOutType> inline vOutType GetDig(char* str)
{
   vOutType val=0;
   int sign = 1;
   if(*str=='-') // negative
   {
     *str++;
     sign = -1;
   }
   //
   while(IsDigit(*str))
   {
     val=(val*10)+(unsigned long)(*str)-0x30;
     str++;
   }
   return val*sign;
}

template<class vOutType> inline vOutType GetDig(char* str,int& size,int& is_float)
{
   vOutType val=0;
   char* start_ptr = str;
   while(IsDigit(*str))
   {
     val=(val*10) + (unsigned long)(*str) - '0';
     str++;
   }
   if(*str=='.')
   {
     double fval = (double)val;
     vOutType* fval_as_int = (vOutType*)(&fval);
     double neg_power = 0.1;
     if(IsDigit(str[1]))
     {
       str++;
       {
         fval+=((double)((unsigned long)(*str) - '0'))*neg_power;
         str++;
       }while(IsDigit(*str));
       // convert fval to val
       val =(vOutType)*fval_as_int ;
     }// end if(IsDigit...
     is_float = 1;
   }// if(*str=='.' ...
   else
   {
     is_float = 0;
   }

   size = (unsigned long long)str - (unsigned long long)start_ptr;
   return val;
}

template<class vFloatType> inline vFloatType GetFloat(char* str)
{
  vFloatType fval = 0.0;
  double tmp;
  sscanf(str,"%lf",&tmp);
  fval = (vFloatType)tmp;

  return fval;

  int sign =1;
  vFloatType dmult = 1.0;
  vFloatType mult_ten = 1;
  int pw; 

  if(*str=='-') sign= -1;
  
  while(IsDigit(*str))
  {
     fval=(fval*10.0)+(vFloatType)((*str)-0x30);
     str++;
  }
  
  if(*str == '.') // coma
  {
    str++;
    vFloatType vmul = 0.1;
    while(IsDigit(*str))
    {
      fval=fval+((vFloatType)((*str)-0x30)*vmul);
      vmul*=0.1;
      str++;
    }  
  }
  
  if(*str=='e') str++;

  if(*str=='-')
  {  
    mult_ten = 0.1;
    *str++;
  }
  else if(*str=='+')
  {
    mult_ten = 10.0;
    *str++;
  }
  else
  {
    return fval*(vFloatType)sign;
  }

  pw = GetDig<int>(str);
  
  for(int i=0;i<pw;i++) 
    dmult*=mult_ten;
  
  fval = fval*dmult;

  return fval*(vFloatType)sign;
}


template<class vOutType> inline vOutType GetHex(tInStream& str)
{
  vOutType val=0;
  while(true)
  {
// symbols
    if(IsDigit(str)) // 0..9
    {
      val=(val<<4)+(vOutType)(str)-0x30;
    }
    else if(InTextRange(str,'A','F'))  // if a..f
    {
      val=(val<<4)+(vOutType)(str)-'A'+0xA;
    }
    else if(InTextRange(str,'a','f')) // if A..F
    {
     val=(val<<4)+(vOutType)(str)-'a'+0xA;               
    }
    else 
    {
      return val;
    }
    ++str;
  } // end while
  return val;
}
template<class vOutType> inline vOutType GetHex(char* str,int& size)
{
  vOutType val=0;
  char* start_str =str;
  while(true)
  {
// symbols
    if(IsDigit(*str)) // 0..9
    {
      val=(val<<4)+(vOutType)(*str)-0x30;
    }
    else if(InTextRange(*str,'A','F'))  // if a..f
    {
      val=(val<<4)+(vOutType)(*str)-'A'+ 0xA;
    }
    else if(InTextRange(*str,'a','f')) // if A..F
    {
     val=(val<<4)+(vOutType)(*str)- 'a' + 0xA;
    }
    else
    {
      break;
    }
    str++;
  } // end while
  size = (unsigned long long)str - (unsigned long long)start_str;
  return val;
}


inline bool IsHexStr(const char* str,int last_idx=0)
{
  int len = strlen(str);
  if(last_idx == 0) last_idx = len;
  else if(last_idx > len ) last_idx = len;
  // 
  for(int i=0;i<last_idx;i++)
  {
    int is_hex_symb = IsDigit(str[i]) || InTextRange(str[i],'a','f') || InTextRange(str[i],'A','F');
    if(!is_hex_symb) // 
      return false;    
  }
  return true;
}

template<class vOutType> inline vOutType GetHex(char* str)
{
  vOutType val=0;
  while(true)
  {
// symbols
    if(IsDigit(*str)) // 0..9
    {
      val=(val<<4)+(vOutType)(*str)-0x30;
    }
    else if(InTextRange(*str,'A','F'))  // if a..f
    {
      val=(val<<4)+(vOutType)(*str)-'A'+0xA;
    }
    else if(InTextRange(*str,'a','f')) // if A..F
    {
     val=(val<<4)+(vOutType)(*str)-'a'+0xA;
    }
    else
    {
      return val;
    }
    str++;
  } // end while
  return val;
}

template<class vOutType> inline vOutType GetBin(tInStream& str)
{
  vOutType val=0;
  while((str=='0')||(str=='1')){ val = (val<<1)+((vOutType)str-'0'); ++str;}
  return val;
}



inline int IsFirstSymb(char val)
{
  return InTextRange(val,'a','z')||InTextRange(val,'A','Z')||(val=='_');
}

inline int IsSymb(char val)
{
  return IsDigit(val)||IsFirstSymb(val)||(val=='_');
}
// miss the symbols which belongs to the string *tsymb
inline int MissText(tInStream& val,char *tsymbs)
{
  int num_lines = 0;
  while(InTextSet(val,tsymbs))
  {
    if((val=='\n')&&(val.IsChildStream()==0))
      num_lines++;
    ++val;
  }
  return num_lines;
}
inline int MissText(char* val,char *tsymbs)
{
  int num_lines = 0;
  char* ptr = val;
  while(InTextSet(*ptr,tsymbs))
  {
    ++ptr;
  }
  return (int)ptr - (int)val;
}
template<class vInpType> inline void GetWord(vInpType* inp,char* buf)
{
  char *p = buf;
  while(IsSymb(*inp)&&(p!=&buf[254]))
  {
    char tmp = *inp++; 
    *p++ = tmp;
  }
  *p=0;
}

//check if the string is a sequense of digits
inline int IsStrDigit(const char* str)
{
  while(*str!=0)
  {
    if(!IsDigit(*str++)) return 0;
  }
  return 1;
}

inline int DecodeString(char* aDst,char* aSrc)
{
  char *src = aSrc;
  char *dst = aDst;

  while(*src)
  {
    if(*src=='\\')
    {
      
      if((src[1]>='0')&&(src[1]<='9'))
      {
       
        *dst++ = (*++src) - '0';   
      }
      else switch(*++src)
      {
        case 't': *dst++ = '\t'; break; // \t
        case 'n': *dst++ = '\n'; break; 
        case '0': *dst++ = 0; break;
        default : *dst++ = src[-1]; *dst++ = *src; break;
      }
      src++;
    }
    else
    {
      *dst++ = *src++;
    }
  }
  *dst= 0;
  return (int)strlen(aDst);
}




#endif

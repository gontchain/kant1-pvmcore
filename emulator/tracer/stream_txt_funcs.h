#ifndef  STREAM_TEXT_FUNCTIONS_H
#define STREAM_TEXT_FUNCTIONS_H
#include <string.h>
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


template<class vInpType> inline int IsPrefix(vInpType* val,char* prefix)
{
  int sz = strlen(prefix);
  for(int i=0;i<sz;i++)
  {
    if(val[i] != *prefix++)
      return 0;
  }
  return 1;
}


inline int IsTextPrefix(char* val,char* prefix){ return IsPrefix<char>(val,prefix);}

inline int IsDigit(char val){ return InTextRange(val,'0','9');}
inline int IsHexPrefix(char* val){return IsTextPrefix(val,"0x");}
inline int IsBinPrefix(char* val){return IsTextPrefix(val,"0b");}

//template<class vStream> 

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

   size = (int)str - (int)start_ptr;
   return val;
}

inline int IsFirstSymb(char val)
{
  return InTextRange(val,'a','z')||InTextRange(val,'A','Z')||(val=='_');
}

inline int IsSymb(char val)
{
  return IsDigit(val)||IsFirstSymb(val);
}


template<class vOutType> inline vOutType GetHex(char* str,char* str_val,int *process_flag=NULL)
{
  vOutType val=0;
  while(true)
  {
// symbols
    if(IsDigit(*str)) // 0..9
    {
      val=(val<<4)+(vOutType)(*str)- '0';
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
      break;
    }
    *str_val = *str; 
    str_val++;
    ++str;
  } // end while
  // error checking to prevent sequences like 0x1Z 
  if(process_flag!=NULL)
  {
	  if(IsSymb(*str))
    {
		  while(IsSymb(*str))
      {
        *str_val++ = *str; 
        ++str;
      }
      *process_flag = 0;
    }
    else
      *process_flag = 1;
  }  
  *str_val = 0;
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
  size = (int)str - (int)start_str;
  return val;
}

inline float GetFloat(char* str)
{
  float val = 0.0;
  float mul = 0.1;

  do
  {
    if(!IsDigit(*str))
      break;

    val = val*10 + (float)(*str - '0');
    str++;
  }while(1);
  if(*str!='.')
    return val;
  // process vals<1
  do
  {
    if(!IsDigit(*str))
      break;
    val = val + (float)(*str - '0')*mul;
    mul *= 0.1;

  }while(1);
 

}


// miss the symbols which belongs to the string *tsymb
/*inline int miss_text(char* val,char *tsymbs)
{
  int num_lines = 0;
  while(InTextSet(val,tsymbs)){ ++val; }
  return num_lines;
}*/

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



#endif

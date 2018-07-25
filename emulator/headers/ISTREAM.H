/***************************************************************************

***************************************************************************/

#ifndef istreamH
#define istreamH

#include <stdio.h>

//----------------------------------------------------------------------------------------------------------
#define max(a, b)  (((a) > (b)) ? (a) : (b)) 
#define seterr printf 
//----------------------------------------------------------------------------------------------------------
class TIStream
{
private:
  
protected:
  FILE            *FHandle;
  char            *beg;
  unsigned int    alloc;
public: 
  unsigned int    size;

  TIStream (unsigned int capacity)
  {
    alloc = max (capacity,1u);
    beg = new char[alloc+1];
    size = -1 ;
  }

  virtual  ~TIStream () { delete [] beg; }

  void* getstr (void)
  {  
    if(size)
      return (void*)beg;
    else 
      return (void*)NULL;
  }
  unsigned int getsize(void){return size;}
};

//----------------------------------------------------------------------------------------------------------
class  TFileIStream : public TIStream
{
private:

protected:
  void  ReadData (void)
  {
    size = fread(beg,1,alloc,FHandle);
    beg[size] = 0;
  }

public:
  // default stream buf size = 64k
  TFileIStream (char *fname,unsigned int capacity = 1024*64) : TIStream (capacity)
  {
    FHandle = fopen(fname,"rb");
    if (FHandle == NULL)
      seterr("error while opening file %s",fname);
    else
      ReadData();
  }
  int GetSize(){return size;}

  virtual  ~TFileIStream () { if(FHandle) fclose (FHandle); }
};
//----------------------------------------------------------------------------------------------------------
class TOStream
{
private:
  
protected:
  FILE            *FHandle;
  char            *beg;
  unsigned int    alloc;

public:
  unsigned int    size;
  TOStream (unsigned int capacity)
  {
    alloc = max (capacity,1u);
    beg = new char[alloc];
    size = -1 ;
  }

  virtual  ~TOStream () { delete [] beg; }

  void* getstr (void)
  {  
    if(size)
      return (void*)beg;
    else 
      return (void*)NULL;
  }
  unsigned int getsize(void){return size;}
};
//----------------------------------------------------------------------------------------------------------
class  TFileOStream: public TIStream
{
private:
protected:
  int mGenAsBin;
  int fsize;


  void  WriteData (void)
  {
    if(!mGenAsBin)
    {
      unsigned long bytes;
      bytes = fwrite(beg,fsize,1,FHandle);
    }
    else
    {
      // print as binary
 	  // skip start address  
      unsigned long* uval = ((unsigned long*)beg) + 2 ;
      unsigned long words_len = fsize/4 - 2; 
      unsigned long rest = (fsize &3)*8;

#define PRINT_VAL()\
  if(val&(1<<31)) \
    fprintf(FHandle,"1");\
  else\
    fprintf(FHandle,"0");\
  val <<= 1;

      for(int i=0;i < words_len;i++)
      {
        unsigned long val = *uval++;
        for(int j=0;j<32;j++)
        {
          PRINT_VAL()
        }//for(int j=0;j<32;j++)
        fprintf(FHandle,"\n");
      }//for(int i=0;i < words_len;i++)
      // last word 
      {
        int j;
        unsigned long val = *uval;
        for(j=0;j<rest;j++)
        {
          PRINT_VAL()
        }//for(int j=0;j<rest;j++)
        // 
        for(;j<32;j++)
          fprintf(FHandle,"0");
        fprintf(FHandle,"\n");
      }// end of last word
    }// end else 
  }

public:
  TFileOStream (char *fname,int aGenBin = 0,unsigned int capacity = 1024*32) : TIStream (max (capacity,1024u))
  {
    mGenAsBin = aGenBin;
    if(aGenBin)
      FHandle = fopen (fname,"wt");
    else
      FHandle = fopen (fname,"wb");
    if(FHandle == NULL)
      seterr("error while opening file %s for writing\n",fname);
    else
    {
      size = alloc;
      fsize = 0;
    }
  }

  virtual  ~TFileOStream () 
  { 
    WriteData (); 
    fclose (FHandle); 
  }

  void addsize(int aval) 
  {
    fsize+=aval;
  }
  
  int datadd(void *data,int size)
  {
    return 0;
  }
};

//----------------------------------------------------------------------------------------------------------
#endif

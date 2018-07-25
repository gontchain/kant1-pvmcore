#ifndef PD_FIFO_REG_H
#define PD_FIFO_REG_H

#include "pd_reg.h"

template <class vDataType,int vSize> class tRegFifo
{
protected:  
  vDataType cells[vSize];
  tPdReg<int> mReadCnt;
  tPdReg<int> mWriteCnt;
public:

  inline void Reset()
  {
    mReadCnt = -1;
    mWriteCnt = 0;
  }

  inline void Reset1()
  {
    mWriteCnt.mRead = (mReadCnt.mWrite + 1) % vSize;
  }

  tRegFifo()
  {
    Reset();
  }
  
  inline void Next()
  {
    int next_read;
    this->mReadCnt = next_read = (this->mReadCnt+1) % vSize;
    if(next_read!=this->mWriteCnt.mWrite)
      return;
    mReadCnt = -1; 
  }
  
  // read from fifo
  inline operator vDataType()
  {
    vDataType res;    
    if(mReadCnt==-1)
      return (vDataType)0;    
    res = this->cells[mReadCnt];
    Next();
    return res;
    mReadCnt.SetModifyed();
  }

  inline int GetReadCounter()       {return mReadCnt;}
  inline int GetWriteCounter()      {return mWriteCnt;}

  inline vDataType Get()
  {
    if(mReadCnt==-1) return 0; else return cells[mReadCnt];
  }

  // write to fifo
  inline vDataType operator = (vDataType aVal)
  {
    if(this->mReadCnt.mWrite==mWriteCnt)
      return aVal;

    this->cells[mWriteCnt] = aVal;
 
    if(this->mReadCnt.mWrite==-1)
    {
      mReadCnt = mWriteCnt;
    }
    this->mWriteCnt = (this->mWriteCnt+1) % vSize;
    return aVal;
  }; 

  // use as register
  inline vDataType& operator[](int aAddr) 
  {
    if(mReadCnt==-1)
      return cells[(aAddr + mWriteCnt) %vSize];
    else
      return cells[(aAddr + mReadCnt) %vSize];
  }

  inline void update()
  {
    this->mReadCnt.update();
    this->mWriteCnt.update();
  }

  inline void Restart()
  {
    this->update();
  }

  inline int GetCurSize()
  {
    if(this->mReadCnt.mWrite ==-1)
      return 0;
    int size = (this->mWriteCnt.mWrite - this->mReadCnt.mWrite);
    if(size<=0) size += vSize;
    return size; 
  }

  inline int GetData(char* aData,int& size)
  {
    vDataType* dval = (vDataType*)aData;
    size = GetCurSize();
    //
    for(int i=0; i<size; i++)
      dval[i] = cells[(mReadCnt+i) % vSize];   
    return 1;
  }

  inline int SetData(char* aData,int size)
  {
    vDataType* dval = (vDataType*)aData;
    if(size > vSize) return 0;

    mReadCnt = 0; 
    mWriteCnt = size;
    // 
    for(int i=0; i< size; i++)
      cells[i] = dval[i];   
    
    // update counters
    mWriteCnt.ParentDevice->UpdateRegs();
    return 1;
  }

  inline int Full()
  { 
    return mWriteCnt==mReadCnt; 
  }
  
  inline int Empty()
  { 
    return (this->mReadCnt == -1);
  }
  // DebugFunctions
  // read without incrementing
  inline vDataType Read(int aIdx)
  {
    return this->cells[(mReadCnt+aIdx) % vSize];
  }

  inline vDataType Write(int aIdx,vDataType aVal)
  {
    return this->cells[(mReadCnt+aIdx) % vSize] = aVal;
  }
  
  inline int Size()
  {
    return GetCurSize(); 
  }
};

// mutable fifo
template <class vDataType,int vSize> class TMuteFifo :public tRegFifo<vDataType,vSize>,public TMutable
{
public:
  TMuteFifo():tRegFifo<vDataType,vSize>(), TMutable((void*)this,vSize){}
#define MYTHIS this //((tRegFifo<vDataType,vSize>*)this)

  inline void Reset()
  {
    MYTHIS->mReadCnt = -1;
    MYTHIS->mWriteCnt = 0;
    MYTHIS->ResetMutable();
  }

  // write to fifo
  inline vDataType operator = (vDataType aVal)
  {
    if(MYTHIS->mReadCnt.mWrite==MYTHIS->mWriteCnt)
      return aVal;

    MYTHIS->cells[MYTHIS->mWriteCnt] = aVal;
 
    if(MYTHIS->mReadCnt.mWrite==-1)
    {
      MYTHIS->mReadCnt = MYTHIS->mWriteCnt;
    }
    MYTHIS->mWriteCnt = (MYTHIS->mWriteCnt+1) % vSize;
    return aVal;
  }; 

  // use as register
  inline vDataType& operator[](int aAddr) 
  {
    if(MYTHIS->mReadCnt==-1)
      return MYTHIS->cells[(aAddr + MYTHIS->mWriteCnt) %vSize];
    else
      return MYTHIS->cells[(aAddr + MYTHIS->mReadCnt) %vSize];
  }
};
#endif
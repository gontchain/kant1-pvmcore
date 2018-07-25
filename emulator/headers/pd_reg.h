#ifndef REGISTER_TYPE_H
#define REGISTER_TYPE_H

#include <updatable.h> 
#include <mutable.h>


template<class vTValType> class TValMutable:public TMutable
{

public:
  vTValType mVal; 
  //  virtual void update(){ mRead = mWrite; }
  inline operator vTValType() const { return mVal; }

  inline vTValType operator = (vTValType aVal)
  {
    mVal = aVal;
    return mVal;
  }
  
  TValMutable():TMutable((void*)this){}
};



template<class vTValType> class tValPair:public iUpdatable
{

public:
  TDevice* ParentDevice;
  vTValType mRead;
  vTValType mWrite;  

  inline void SetModifyed()
  {
    ParentDevice->AddUpdate(this);
  }
  //  virtual void update(){ mRead = mWrite; }
  inline operator vTValType() const { return mRead; }

  inline vTValType operator = (vTValType aVal)
  {
    mWrite = aVal;
    ParentDevice->AddUpdate(this);
    return mWrite;
  }

  tValPair()
  {
    ParentDevice = dynamic_cast<TDevice*>(CurDevice);
  }
};


template<class vRegType> class tPdReg: public tValPair<vRegType>
{

public:
  tPdReg(){}
#ifdef QEMU_TEST
  virtual void update(){ }
#else
  virtual void update()
  { 
    this->mRead = this->mWrite; 
  }
#endif
  inline operator vRegType() const 
  { 
      return this->mRead; 
  }

  inline vRegType operator = (vRegType aVal)
  {
    if(this->ParentDevice!=NULL)
      this->ParentDevice->AddUpdate(this);
#ifdef QEMU_TEST
    this->mRead = aVal;
    return aVal;
#else
    this->mWrite = aVal;
    return this->mWrite;
#endif
  }
  
  inline vRegType operator = (tPdReg<vRegType>& aVal)
  {
    if(this->ParentDevice!=NULL)
      this->ParentDevice->AddUpdate(this);
#ifdef QEMU_TEST
    this->mRead = aVal;
    return aVal;
#else
    this->mWrite = aVal;
    return this->mWrite;
#endif
  }

};





#define PD_REG tPdReg

  //#define QEMU_TEST

template<class vRegType> class RegMutable: public tValPair<vRegType>,public TMutable 
{
private:
  TCycleCount mCount;
  int         PipeStart;

public:
  RegMutable():TMutable((void*)this) { mCount = 0; }

  virtual void update()
  { 
    this->mRead = this->mWrite;
  }
  
  inline operator vRegType() const { return this->mRead; }

  inline vRegType operator = (vRegType aVal)
  {
    this->mWrite = aVal;
    this->ParentDevice->AddUpdate(this);
    return this->mWrite;
  }
};



template<class vRegType> class TProgramCounter: public tValPair<vRegType>
{
public:
  TProgramCounter(){}
  
  virtual void update()
  {  
    this->mRead = this->mWrite; 
  }

  inline operator vRegType() const
  {
    return this->mRead;
  }

  inline vRegType operator = (vRegType aVal)
  {
    this->mWrite = aVal;
    this->ParentDevice->AddUpdate(this);
    return this->mWrite;
  }

  inline vRegType operator = (tPdReg<vRegType> aVal)
  {
    this->mWrite = aVal;
    this->ParentDevice->AddUpdate(this);
    return this->mWrite;
  }
};

#endif
#ifndef TMEMBLOCK_H
#define TMEMBLOCK_H
#include <systemc.h>
#include "mem_space.h"
/////////////////////////////////////////////////////////////
//
//      Author: 
//      Email : 
//      Copyright: 
/////////////////////////////////////////////////////////////
//  	Comments: 
//		
/////////////////////////////////////////////////////////////

template<class vAddrType,class vDataType>
struct tMemBlock :
	public iMemInterface<vAddrType,vDataType>,
	public sc_module
{
private:
   vDataType mSize;
   vAddrType* mem;
   uint32    mWS;
  
   inline vDataType& GetMemCell(vAddrType aAddr)
   {
     return mem[aAddr];   
   }

public:

	virtual vDataType ReadMem(vAddrType aAddr)
	{
	  return this->mem[aAddr];
	}

	virtual void WriteMem(vAddrType aAddr, vDataType aData)
	{
    this->mem[aAddr] = aData;
	}

	virtual int GetMem(vDataType * aDataArray, vAddrType aAddr, uint32 aSizeInBytes)
	{
	  return (vDataType)0;
	}
	virtual int SetMem(vDataType * aDataArray, vAddrType aAddr, uint32 aSizeInBytes)
	{
	  return (vDataType)0;
	}

	SC_HAS_PROCESS(tMemBlock);
	tMemBlock(sc_module_name name,vDataType aSize,uint32 aWS):sc_module(name)
	{
	  // size - number of memory cells
	  this->mSize = aSize;
	  this->mem = new vAddrType[aSize];
	  this->mWS = aWS;
	}
};
#endif
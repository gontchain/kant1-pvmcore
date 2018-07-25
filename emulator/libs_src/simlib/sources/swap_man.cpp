#include <simple_block.h>
#include <assert.h>
#include <stdio.h>

//cSwapClass MainSwap;
cAllocUnit** Units;
uint32 CurNewUnit;
uint32 MaxNumUnits;

void cSwapClass::Init(uint64 MaxRamSize)
{
  MaxNumUnits = MaxRamSize/SLOT_SIZE + 1;
  Units = new cAllocUnitPtr[MaxRamSize/SLOT_SIZE + 1];
  CurNewUnit = 0;
  // 
}

void cSwapClass::Destroy()
{
  for(uint32 i = 0;i <CurNewUnit;i++)
  {
    delete Units[i];
  }
  delete Units;
}

cAllocUnitPtr cSwapClass::AllocUnit()
{
  assert(CurNewUnit <MaxNumUnits);
  Units[CurNewUnit] = new cAllocUnit();
  return Units[CurNewUnit++];
}

void* cSwapClass::AllocPtrFromExistent()
{
  void* ptr;
 
  cAllocUnitPtr min_ptr = NULL;// Units[0];
  uint32 min_acc = 0xFFFFFFFF; //min_ptr->GetNumAccesses();
 
  // find section with minimal offset
  for(int i=1; i < CurNewUnit;i++)
  {
    if(Units[i]->IsRamPtr())
    {
      uint32 cur_acc = Units[i]->GetNumAccesses();
      if(cur_acc < min_acc)
      {
        min_acc = cur_acc;
        min_ptr = Units[i];
      }
    }
  }
  // the memory unit has been found;
  if(min_ptr!=NULL)
  {
    ptr = min_ptr->GetPtr();
    min_ptr->SetSwap((uint32)min_ptr);// указатель на класс берем за основу имени файла
    return ptr;
  }
  else
  {
    throw "memory overflow";
  }
}

void* AllocPtr(int aSize)
{
  try 
  {
    return (void*)(new char[aSize]);
  }
  catch(...)
  {
    return cSwapClass::AllocPtrFromExistent();
  }
}

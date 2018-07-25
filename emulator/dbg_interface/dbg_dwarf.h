#ifndef DBG_DWARF_H
#define DBG_DWARF_H
#include <dbg_interface.h>



// абстрактный класс для управления симулятором.
class TDbgDwarfInterface: public TDbgInterface
{
  typedef enum
  {
    REL_ABSOLUTE,   // no relation
    REL_REG_PLUS,   // aAddr + reg
    REL_REG_MINUS,  // aAddr - reg
    REL_REG_NEG,    // reg - aAddr
    REL_REG_MAPPED, // registry mapped symbol
  }eRelType;      



public:
  // extends TDbgInterface by the list of functions for DWARF processing
  virtual int GetFileLine(uint32 aAddr,char* aFileName,uint32& aLine) = 0; // return -1 if the code not found or 
  virtual int GetPcRange(char* aFileName,uint32 aLine,uint32& aStart,uint32& aEnd) = 0 ; // return -1 if the file or line is incorrect, return -2 if the line has no source code 
  virtual int IsItCodeOrData(uint32 aAddr)= 0; // return 1 - if code, 2 - data, 0 - unknown area
  virtual int GetAddrOfSymbol(char* aSymb,uint32& aAddr,uint32& aRegIdx,uint32& aArrIdx,eRelType& aRelType) = 0;// return address of the symbol
  virtual int GetSymbolByAddr(uint32 aAddr,uint32 aRegIdx, uint32 aArrIdx,eRelType& aRelType,char* aSymb) = 0;
// 
//  virtual int 
 
  

};


#endif
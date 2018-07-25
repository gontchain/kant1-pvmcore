#ifndef OBJ_SECTIONS_H
#define OBJ_SECTIONS_H

#include <string>
#include <lists.h>
#include <buffers.h>
#include <libelf.h> 


#define DEFAULT_BUF_SIZE

class tObjSect :public tNamedElem,public tBytesBuf
{
private:
  ELF_DATA    *elf_data;
public:
  ELF*        mObjFile;     // parent elf file which contains this section
  ELF_SCN*    mElfSect;     // elf section
  tObjSect*   mRelSect;     // relocation section for this section
  tObjSect*   mRelaSect;     // relocation section for this section
  // elf header parameters 
  uint32      mType;        // type of the section
  uint32      mAttr;        // section's attributes
  uint32      mLinkIdx;     // section's link index
  uint32      mInfo;        // section's info 
  int         mHasInits;    // 1 if the section contains init data
  //  bool        mIsRel;       // is the section a relocation
  // class constructor
  //   aName - name of the secction
  //   aElfFile - parent elf file
  //   aType  - a type of the section
  tObjSect(char* aName,ELF* aElfFile,uint32 aType,uint32 aAttr,uint32 aLinkIdx=0);
  // add relocation 
  //  aOffset -relocation offset
  //  aInfo - a type of  the relocation
  int AddRel(uint32 aOffset,uint32 aInfo);
  int AddRela(uint32 aOffset,uint32 aInfo,uint32 aOffs);
  int FinalizeSection();
};

// string table
class tStringTable: public tObjSect
{
public: 
  tNamedList<tNamedElem>* mNames;
  tStringTable(ELF* aElfFile);
  int AddName(char* aName);
};


#include <Structs.h>  
class tSectSymbol: public tNamedElem
{
public:
  tAsmElem*   mEl;
  tObjSect*   mSector;
  uint32      mAddr;
  int         mStrIdx;
  int         mSize;
  char        mBind;
  bool        mIsExtern;
  char        mObjType;
  tSectSymbol(tAsmElem* aEl,int aStrIdx);
  void UpdateData(tAsmElem* aEl);
  int FillElfSymbStruct(Elf32_Sym* aSmb);
};  


class tSymbTable: public tObjSect
{
public:
  tSymbTable(ELF* aElfFile,uint32 aStringIdx);
  tNamedList<tSectSymbol>* mSymbols;
  int AddSymb(int aStringIdx,tAsmElem* aElem);
  int PushSymbols();
};

// section relocation 
class tRelocSect: public tObjSect
{
public:
  tObjSect* mBaseSect;
  uint32    mBaseIdx;
  uint32    mStrTabIdx;
  tRelocSect(tObjSect* aBaseSect);
};

class tRelaSect: public tObjSect
{
public:
  tObjSect* mBaseSect;
  uint32    mBaseIdx;
  uint32    mStrTabIdx;
  tRelaSect(tObjSect* aBaseSect);
};

struct tUndefReloc :public tNamedElem
{
public:
  int mOffset;          // symbol absolute offset
  int mLine;            // start line of the symbol definition
  bool mIsRelocated;    // flag =true if the symbol has been relocated
  tUndefReloc(char* aName,int aOffset,int aLine);
};

class tSectList: public tNamedList<tObjSect>
{
protected:
  ELF*                     mElfFile;
  tStringTable*            mStringTable;
  tSymbTable*              mSymbs;
public:
  tNamedList<tUndefReloc>  *mUndefRels;
  tSectList(ELF* aElfFile);
  tObjSect* GetSection(char* aName,uint32 aType,uint32 aAttr);
  int AddSection(char* aName,ELF* aElfFile,uint32 aType,uint32 aAttr);
  int AddSymbol(tAsmElem* aElem);
  int Update(tAsmElem* aElem);
  int CheckNewSymb(tAsmElem* aElem);
  int AddString(const char* aName);
  int SaveObjFile();
};

#endif
#ifndef ASM_STRUCT_H
#define ASM_STRUCT_H

#include <lists.h>
#include <section.h>

#include <map>
#include <string>
#include <vector>
#include <list>
#include <iostream>

#include "stream_txt_funcs.h"

using namespace std;

//#define OBJ_ECHO 1
// section
class tSection
{
public:
  enum eSectType {eUndef,eData,eNoBits,eText};
// name of the section
  string     mName;
// section type
  eSectType  mType;
// content of the section
  string     mContent;
  int        mIdx;
  // clear the section content
  void clear();
// set type of the section
  int SetSectionType(string& aStype);
};


struct tMacro
{
	string name;
	vector<string> params;
	string body;
	void clear();
  void print();
};


class tAsmElem
{
public:
	enum eScope 
  { 
    eOwn,     // label is inside the macro
    eLocal,   // local
    eGlobal,  // global
    eWeak,    // weak 
    eExtern,  // label is extern 
    eUnknown  // label is unknown
  };

  eScope     scope;       // scope of the element
  string     name;        // name of the element 
  tObjSect   *mSect;      // section
  int        ip;          // ip - a section offset (should be renamed)
  int        mSize;       // size of the object
  bool       mIsExtern;   // true if the symbol is external
  int        mSymbIdx;    // index of the element in the symbol table
  char       mObjType;    // type of the object

  virtual void ClearElem();
};


struct tLabel :public tAsmElem
{
public:
  void clear();
  void print();
};

struct tConstant:public tAsmElem
{
public:
	string value;
	void clear();
	void print();
};

typedef enum
{
  MOP_ADD,
  MOP_SUB,
  MOP_ELEM,
}eMopType;

struct tNode
{
  eMopType mMop;
  tNode* l;
  tNode* r;
  // constructor 
  tNode(eMopType aMop,tNode* aL = NULL,tNode* aR = NULL);
  // destructor
  ~tNode();
};

// add 
#define NODE_ADD(l,r) (new tNode(MOP_ADD,l,r))
#define NODE_SUB(l,r) (new tNode(MOP_SUB,l,r))

#define ASM_ELEM(elem) (new tNode(MOP_ELEM,(tNode*)elem))


typedef union
{
  uint32 val32;       // 32 bits value
  uint64 val64;       // 
  float  valf;        // float value
  double vald;        // double value
  char*  valstring;   // string value
  tAsmElem* elem;     // assembly element
  tNode* exp;         // expression
}uVal;


struct tStringVal: public tNamedElem
{
  enum eStrValType {SV_UNS = 0,SV_NEG =1,SV_HEX = 2,SV_FLOAT,SV_DOUBLE,SV_STRING,SV_ELEM,SV_NODE}; 
  eStrValType mType; // type of the string value
  bool mIsLong;
  string mStrVal;
  tAsmElem* mEl;
  tNode*    mNd;
  // constructor
  tStringVal(string& str,eStrValType aType,bool aIsLong = false);

  tStringVal(string& str,tAsmElem* aEl);

  tStringVal(string& str,tNode* aNd);
  uVal GetVal();

  inline int IsIntVal()
  {
    return ((int)this->mType <  (int)SV_FLOAT);
  }
};

struct tTmpNode
{
  tStringVal*       mLeft;
  tStringVal*       mRight;
  tNode*            mNode;

  inline void SetValElem(tStringVal* aVal)
  {
    if(mLeft==NULL)
    {
      mLeft = aVal;
      mNode = new tNode(MOP_ELEM,(tNode*)aVal);    
    }
    else
    {
      assert(mLeft!=NULL);
      mRight = aVal;
    }
  }
  
  void clear();
 
  void SetNode(eMopType aMop);
  uint64 CalcVal(tNode* aNode);
// check relocations
  tAsmElem* GetRelocElem(tNode* aNode);
};

struct tVariable:public tAsmElem
{
	string   type;
	string   value;
  tValue*  mDigVal;
  uint32   ArrSize;
//	string addr;	
  void clear();
  void print();
};


typedef char eRelType;


struct tRelocObj
{
public:
  static const char OBJ_VAR = 1;
  static const char OBJ_LABEL = 2;

  eRelType mRelType;
  int mSymbIdx;
  uint32 mInstOffset;
  tRelocObj(eRelType aRelType,int aSymbIdx,uint32 aInstOffset);
};

class tRelocList: public tList<tRelocObj>
{
public:
  inline int AddReloc(eRelType aRelType,int aSymbIdx,uint32 aInstOffset)
  {
    assert(aSymbIdx>=0);
    return this->Add(new tRelocObj(aRelType,aSymbIdx,aInstOffset));
  }
};

struct tInstruction
{
  string         body;
  string         postfix;
  int            expsize;
  bool           delayed;
  vector<string> content;
  tRelocList     mRelList;

  void clear();
  void print();
};

struct tMacroEx
{
	string name;
	vector<string> params;

	void clear(); 
	void print();
};

struct tMacroParams
{
	string macro_name;
	map<string, string> params;
};


class any
{
public: // structors

    any()
      : content(0)
    {
    }

    template<typename ValueType>
    any(const ValueType & value)
      : content(new holder<ValueType>(value))
    {
    }

    any(const any & other)
      : content(other.content ? other.content->clone() : 0)
    {
    }

    ~any()
    {
        delete content;
    }

public: // modifiers

    any & swap(any & rhs)
    {
        std::swap(content, rhs.content);
        return *this;
    }

    template<typename ValueType>
    any & operator=(const ValueType & rhs)
    {
        any(rhs).swap(*this);
        return *this;
    }

    any & operator=(const any & rhs)
    {
        any(rhs).swap(*this);
        return *this;
    }

public: // queries

    bool empty() const
    {
        return !content;
    }

    const std::type_info & type() const
    {
        return content ? content->type() : typeid(void);
    }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
private: // types
#else
public: // types (public so any_cast can be non-friend)
#endif

    class placeholder
    {
    public: // structors

        virtual ~placeholder()
        {
        }

    public: // queries

        virtual const std::type_info & type() const = 0;

        virtual placeholder * clone() const = 0;

    };

    template<typename ValueType>
    class holder : public placeholder
    {
    public: // structors

        holder(const ValueType & value)
          : held(value)
        {
        }

    public: // queries

        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }

        virtual placeholder * clone() const
        {
            return new holder(held);
        }

    public: // representation

        ValueType held;

    };

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS

private: // representation

    template<typename ValueType> friend ValueType * any_cast(any *);

#else

public: // representation (public so any_cast can be non-friend)

#endif

    placeholder * content;

};

template<typename ValueType>  ValueType * any_cast(any* operand)
  {
      return operand && operand->type() == typeid(ValueType)
                  ? &static_cast<any::holder<ValueType> *>(operand->content)->held
                  : 0;
  }

template<typename ValueType>  ValueType& any_cast(any& operand) { return *(any_cast<ValueType>(&operand));}




typedef map<string, any> tIdentMap;
typedef list<tMacroParams> tMacroNesting;

#endif
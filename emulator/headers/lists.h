#ifndef DATA_LISTS_H
#define DATA_LISTS_H

#include "datatypes.h"
#include <string.h>
#include <assert.h>

template<class vElem> class tListElem
{
public:
  vElem            *mElem; // pointer into the element 
  tListElem<vElem> *Next;  // pointer into the next element in the string
// constructor
  tListElem(vElem* aElem)
  {
    mElem = aElem; 
    Next = NULL; 
  }
};

template<class vElem> class tList
{
protected:
  // start element of the list
  tListElem<vElem> *mStartElem;
  // last element of the list
  tListElem<vElem> *mLastElem;
// current element of the list
  tListElem<vElem> *mCurElem;
  bool mIsEnumState; 
  uint32 Count;
public:
  tList()
  {
    mStartElem = mLastElem = NULL;
    this->mIsEnumState = false;
	  this->Count = 0;
  }

  ~tList()
  {
    tListElem<vElem>* tmp = mStartElem;
  	tListElem<vElem>* tmp_next;
	  // delete all list elements are added
	  while(tmp!=NULL)
	  {
	    tmp_next = tmp->Next;
	    delete tmp;
	    tmp = tmp_next;
	  }
  }
  // init the list enumeration and returns the first element in the list( if any)
  virtual vElem* GetFirst()
  {
    if(this->mStartElem!=NULL)
	  {
      this->mCurElem = mStartElem;
  	  return mStartElem->mElem;
	  }
	  else
	  {
	    this->mCurElem = NULL;
	    return NULL;
	  }
  }
  // get next element
  virtual vElem* GetNext()
  {
    // error if the null elem is requested
    if(this->mCurElem==NULL)
	    return NULL;
    // save current elem for return
    this->mCurElem = this->mCurElem->Next;
    if (this->mCurElem == NULL)
      return NULL;
    return this->mCurElem->mElem;
  }

  virtual vElem* GetCurrent()
  {
     return this->mCurElem->mElem;
  }

  virtual uint32 GetCout()
  {
    return this->Count;
  }
  // Add element to the list
  // arguments: 
  //   vElem* aElem - pointer into an element to add
  int Add(vElem* aElem)
  {
    // create new list element 
    tListElem<vElem>* elem = new tListElem<vElem>(aElem);
    // add to list
  	// if the list is empty sets the new elem as a start one and as last
    if(this->mStartElem==NULL) 
	  {
	    this->mStartElem = this->mLastElem = elem;
  	}
	  else
    {
      // set add to the end of the list
      this->mLastElem->Next = elem;
      this->mLastElem = elem;
    } 
    return this->Count++;
  }

// walk through the elements of the list 

//#define FOR_EACH_ELEM(type,elem,list)\
//  for(elem=(type*)list->GetFirst();elem!=NULL;(type*)elem=list->GetNext())
  
#define FOR_EACH_ELEM(type,elem,list)\
  for(elem=list->GetFirst();elem!=NULL;elem=list->GetNext())

  int CopyList(tList<vElem>* aSrcList)
  {
    vElem *tmp;
    FOR_EACH_ELEM(vElem,tmp,this)
      this->Add(tmp);    
  }
  int GetIdx(vElem* elem)
  {
    int count =0;
    vElem *tmp;
    FOR_EACH_ELEM(vElem,tmp,this)
    {
      if(tmp==elem)
        return count;
      count++;
    }
    return -1;
  }

 
  // get elem by index
  vElem* GetElem(int aIdx)
  {
    int count =0;
    vElem *tmp;
    FOR_EACH_ELEM(vElem,tmp,this)
    {
      if(count==aIdx)
        return tmp;
      count++;
    }
    return NULL;
  }

  inline vElem* operator[](int aIdx) 
  {
    return GetElem(aIdx);
  }

  virtual void Clear()
  {
    tListElem<vElem> *cur_elem = this->mStartElem;
    while(cur_elem!=NULL)
    {
      tListElem<vElem>* tmp = cur_elem->Next;
      delete cur_elem;
      cur_elem = tmp;
    }
    Count = 0;
    this->mStartElem = this->mLastElem = NULL;
  }

};

struct tNamedElem
{
  char *name;
  tNamedElem(char *aName);
  ~tNamedElem();
};

// element must be inherited from the class tNamedElem
template<class vNamedElem>
class tNamedList:public tList<vNamedElem>
{
public:
  // GetElem: get element by its name
  inline vNamedElem* GetElem(char *name)
  {
    vNamedElem *elm;
    FOR_EACH_ELEM(vNamedElem,elm,this)
    {
      if(!strcmp(((tNamedElem*)elm)->name,name))
        return elm;
    }
    return NULL;
  }

  int GetIdxByName(const char* aName)
  {
    int count =0;
    vNamedElem *tmp;
    FOR_EACH_ELEM(vNamedElem,tmp,this)
    {
      if(!strcmp(((tNamedElem*)tmp)->name,aName))
        return count;
      count++;
    }
    return -1;  
  }
};

// hierarhical list of elements
template<class vElemType> 
class tHierarchList: public tList<vElemType>
{
private:  
  // list of the lists are belongs to the list
  tList< tList<vElemType> >* mLists;
  tList<vElemType>* mCurList;
  bool  mUseLists;
public:
  tHierarchList():tList<vElemType>()
  {
    this->mLists = new tList< tList<vElemType> >;
	  this->mCurList = NULL;
	  this->mUseLists = false;
  }
// add child list to the lists
  void AddList(tList<vElemType>* aList)
  {
    this->mLists->Add(aList);
  }

  inline tList<vElemType>* NextList()
  {
	return this->mLists->GetNext;
  }

  vElemType* GetFirst()
  {
    vElemType* toret;
	  this->mCurList = this->mLists->GetFirst;
	  if(this->mCurList==NULL)
  	{
	    return NULL;
	  }
	  else
	  {
	    do
      {
        toret = this->mCurList->GetFirst();
        if(toret!=NULL)
          return toret;
        this->mCurList = this->mLists->GetNext();
      }while(this->mCurList!=NULL);
    }
    return NULL;
  }
  
  vElemType* GetNext()
  {
    return NULL;
  }
};

// oldlist notations
struct tCustomElem
{
  char        *name;  // name of element 
  uint32      id;     // or ID of element
  uint32      typeID;	// ID of element type
  void        *data;	// type specific data
  tCustomElem *next;	// next element
};

// set of named objects
class TObjSet
{
private:
  char   *setname;      // name of list
  uint32 typeID;        // type of list
  uint32 size;          // size of list
  tCustomElem  *first;  // first element in list
  tCustomElem  *last;   // last element in list
  tCustomElem  *rel; // pointer into the
  int          nel;  // number of elements
public:
  TObjSet(char *name);
  ~TObjSet(){};
  int AddElem(char *name,uint32 ID,void *data);
  int AddElem(int vid,uint32 typeID,void *data);
  tCustomElem* GetElem(char *name);
  tCustomElem* GetElem(int idx);
  int  GetElemIdx(char *name);
  char* GetListName();
  int AddList(TObjSet *list);
  uint32 GetElemID(char *name);
  int DelList(TObjSet *list);
// read an element
  int StartReading();
  tCustomElem* GetNextElem();
  
  inline tCustomElem* GetNext()
  { 
    return this->GetNextElem();
  };
  tCustomElem* GetFirst();
  int GetNumElems();
  // operation with lists
  // sum of two lists
 /* TObjSet* operator| (TObjSet *lst2);
  // crossing of two list
  TObjSet* operator&(TObjSet *lst2);
  // add to list
  void operator |= (TObjSet *lst2);
  void operator =  (TObjSet *lst2);
  void operator |=  (tCustomElem *el);*/
};

// range list 
class TRangeSet
{
private:
  char    *setname;      // name of list
  uint32  size;          // size of list
  double  start;         // start value
  double  end;           // end value
  double  step;          // step
public:
  TRangeSet(char *name,double sstart,double send,double sstep);
  ~TRangeSet();
  char* GetListName();
};

// global macros
#define COPY_NAME(dest,src)\
if(src!=NULL){dest = new char[strlen(src)+1]; strcpy(dest,src);} else{dest = NULL;}

#endif 
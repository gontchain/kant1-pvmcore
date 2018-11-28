#include "evm_client.h"
#include "dlfcn.h"

#ifdef _WIN32
#include "direct.h"
#endif

// base class for GVM1 
class TBaseGVM
{  
protected:
// evm client
  TEvmClient* EvmClient;
  
  typedef void (TBaseGVM::*TransactionFunc)();
  
  struct TTransaction
  {
    TTId TId; // Transaction ID
    TransactionFunc Func;
  };   
  // array of transactions
  TTransaction* TransArr; 
  // current Transaction;
  int  TransInitCounter;
  int  TransIDCounter;
  TTId CurTrans;

public:
  // set next transaction
  inline void SET_NEXT_TRANSACTION(TTId aTrans) 
  { 
    // 
    EvmClient->AddNextTransaction(aTrans);
  }
  
  // construct
  TBaseGVM(int aNumTrans,int aStorageSize)
  {
    // init array of transaction
    TransArr = new TTransaction[aNumTrans];
    // init transactions counter
    TransInitCounter = 0;
  } // end of constructor
  

  // run transaction
  bool RunTransaction(TEvmClient* aClient)
  {
    // load storage 
 //   aClient->LoadStorage(Storage);
    // get cur transaction from client
    EvmClient = aClient;
    CurTrans = aClient->GetCurState();
    // 
    if(CurTrans == NO_TRANSACTION) // contract finished
      return true; 
    // select and run transaction
    for(int i = 0; i < TransInitCounter; i++)
    {
      if(TransArr[i].TId == CurTrans)
      {
        TransactionFunc f =TransArr[i].Func; 
        // execute transaction
        (this->*(f))();
        // ok, exit
        return true;
      } // if(Transaction[i].TId = CurTrans)
    } // for(...
    return false; // transaction with this ID did not found
  }// end of RunTransaction
   
  void RunContractCode(const char *libname, int argc, const char **argv)
  {
    typedef void* (*LibRunFunc)(int, const char**, unsigned int);
    void *dl_handle = dlopen(libname, RTLD_LAZY);
    if (!dl_handle) {
      fprintf(stderr, "dlopen(%s):%s\n", libname,
#ifndef _WIN32
        dlerror());
#else
        "error reading library"); // GetLastError() call produces include header (windows.h) errors, so just output 'some error occures'
#endif
    }
    LibRunFunc runFunction;
    *(void**)(&runFunction) = dlsym_wrap(dl_handle, "RunProgram");
    runFunction(argc, argv, 0);
    dlclose(dl_handle);
  }

  // add state to SM    
  void AddState(TTId aID,TransactionFunc aFunc) 
  {
    // add new state 
    TransArr[TransInitCounter].TId = aID;
    TransArr[TransInitCounter++].Func = aFunc;    
  }

private:
  static void *dlsym_wrap(void *handle, const char *sym)
  {
    void *const ret = dlsym(handle, sym);
    if (!ret) fprintf(stderr, "Error dlsym(%p, \"%s\"):%s\n", handle, sym, dlerror());
    return ret;
  }
}; // end of class

#define ADD_STATE(id,func){ TransactionFunc f = (TransactionFunc)this->func; AddState(id,f);} 

#define VM_CREATE(ClassName,NumStates) ClassName():TBaseGVM(NumStates,1024)

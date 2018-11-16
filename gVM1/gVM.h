#include "evm_client.h"


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
   
  // add state to SM    
  void AddState(TTId aID,TransactionFunc aFunc) 
  {
    // add new state 
    TransArr[TransInitCounter].TId = aID;
    TransArr[TransInitCounter++].Func = aFunc;    
  }
}; // end of class

#define ADD_STATE(id,func){ TransactionFunc f = (TransactionFunc)this->func; AddState(id,f);} 

#define VM_CREATE(ClassName,NumStates) ClassName():TBaseGVM(NumStates,1024)

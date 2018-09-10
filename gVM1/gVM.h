#include "datatypes.h"


typedef uint32 TTId;

// this class will came from cpp-ethereum client
class TEvmClient
{
protected:
  TTId curTTid; 
 
public: 
  int LoadStorage(uint256* aStorage){return 1;}
  int SaveStorage(uint256* aStorage){return 1;}
  TTId GetID(){ return  curTTid;}
  void SaveTID(TTId aTID){ curTTid = aTID; } // save transaction ID to BlockChain 
  TEvmClient()
  {
  }
};


#define NO_TRANSACTION 0xFFFFFFFF

// base class for GVM1 
class TBaseGVM
{  
protected:
// evm client
  TEvmClient* EvmClient;
  // storage
  uint256* Storage;
  TTId*    History;
  uint32   HistoryCounter;
  // contract params
  uint160  cur_addr;
  uint160  caller_addr;
  uint160  origin_addr;
  uint256  gas_price;
  uint256  gas_available;
  
  typedef void (TBaseGVM::*TransactionFunc)();
  
  struct TTransaction
  {
    TTId TId; // Transaction ID
    TransactionFunc Func;
  };   
  // array of transactions
  TTransaction* TransArr; 
  // current Transaction;
  TTId CurTrans;  
  int  TransInitCounter;
  int  TransIDCounter;
  
public:
  // write to storage
  inline void sstore(uint256 key,uint256 val) { Storage[key.to_int()] = val; }
  // read from storage
  inline uint256 sload(uint256 key) { return Storage[key.to_int()];}
  // set next transaction
  inline void SET_NEXT_TRANSACTION(TTId aTrans) 
  { 
    // add curren transaction into history
    History[HistoryCounter] = CurTrans;
    // ... and set new trans
    CurTrans = aTrans;
  }
  
  // construct
  TBaseGVM(int aNumTrans,int aStorageSize,TEvmClient* aClient)
  {
    // init array of transaction
    TransArr = new TTransaction[aNumTrans];
    // set storage size
    Storage = new uint256[aStorageSize];
    // init transactions counter
    TransInitCounter = 0;
    // init History
    History = new TTId[1024];
    HistoryCounter = 0;    
    aClient->SaveTID(1);
  } // end of constructor
  
  // run transaction
  bool RunTransaction(TEvmClient* aClient)
  {
    // load storage 
    aClient->LoadStorage(Storage);
    // get cur transaction from client
    CurTrans = aClient->GetID();
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
        // we saved currently executed transaction into history log and increment history counter
        HistoryCounter++;
        // save storage
        aClient->SaveStorage(Storage);
        // save next state
        aClient->SaveTID(CurTrans);
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

#define VM_CREATE(ClassName,NumStates)\
  ClassName(TEvmClient* aClient):TBaseGVM(NumStates,1000,aClient)

#include "evm_client.h"
#ifndef _WIN32
#include <unistd.h>
#include <sys/wait.h>
#else
#include <windows.h>
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

  void RunContractCode(char* libname, char* bin)
  {
#ifndef _WIN32
    char* argv[7] = { libname, "-nodebug", "-nodefaults", "-nographic", "-kernel", bin, NULL };
    int pid, status;
    if (pid = fork()) {
      waitpid(pid, &status, 0); // wait for exit
    } else {
      execvp(*argv, argv);
    }
#else
    char argv[_MAX_PATH];
    sprintf(argv, "%s -nodebug -nographic -nodefaults -kernel %s", libname, bin);
    STARTUPINFO si; si.cb = sizeof(si); ZeroMemory(&si, sizeof(si));
    PROCESS_INFORMATION pi; ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(libname,   // No module name (use command line)
        argv,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#endif
  }

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

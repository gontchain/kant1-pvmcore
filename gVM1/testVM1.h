#include "gVM.h"
#include <stdio.h>

#define STATE1 1
#define STATE2 2
#define STATE3 3

// test state machine
class TestVm1: public TBaseGVM
{
protected:
   int counter;
public:
// state 1
  void State1Process()
  {
    printf("state 1\n");
    SET_NEXT_TRANSACTION(STATE2);
    counter = 10;
    EvmClient->sstore(uint256(1),uint256(counter));
  }
// state 2
  void State2Process()
  {
    printf("state 2\n");
    counter = EvmClient->sload(1);
    if(counter > 0)
    {
      counter--;
#ifndef _WIN32
#define _MAX_PATH 260
	  char evm_lib[_MAX_PATH] = "../QEMU/qemu/ppdl-softmmu/libevm-ppdl.so";
#else
    char evm_lib[_MAX_PATH] = "../QEMU/qemu/ppdl-softmmu/libevm-ppdl.dll";
#endif
	  const char* argv[6] = { evm_lib, "-nodebug", "-nodefaults", "-nographic", "-kernel", "add.bin" };
	  const int argc = 6;
	  RunContractCode(evm_lib, argc, argv);
      SET_NEXT_TRANSACTION(STATE2);
    }
    else
    {
      SET_NEXT_TRANSACTION(STATE3);
    }  // end if
    EvmClient->sstore(uint256(1),uint256(counter));
  }// end of state2
  
// state 3
  void State3Process()
  {
    printf("state 3\n");
    SET_NEXT_TRANSACTION(NO_TRANSACTION);
  }
  
// VM constructor
  VM_CREATE(TestVm1,3)
  {
    // init state variables
    // add states to gVM1
	  AddState(STATE1, (TransactionFunc)&TestVm1::State1Process);
	  AddState(STATE2, (TransactionFunc)&TestVm1::State2Process);
	  AddState(STATE3, (TransactionFunc)&TestVm1::State3Process);
	  /*    ADD_STATE(STATE1, TestVm1::State1Process)
    ADD_STATE(STATE2, TestVm1::State2Process)
    ADD_STATE(STATE3, TestVm1::State3Process)*/
  }
}; // end of class`

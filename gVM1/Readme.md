### gVM1 base class and usage example


About gVM1:
  GONT concept assumes two levels of virtual machines - gVM1 and one or many gVm2 machines. gVM1 is a state machine. Each transactio of gVM1 runs the function according to the current state of gVM1.
  
Within the transaction gVM1 can:
    1) Change the state of gVM1.; 
    2) Run contract on one or many gVM2 machines.
    3) Make any custom computations.
    
  GVM2 virtual machines should be implemented as dynamically linked libraries. For example testVM1 contains code of run Ethereum Virtual Machine (EVM - contract, where EVM is implemented as QEMU based simulator.

  // example of running EVM within the transaction of gVM1
  if(counter > 0)
    {
      counter--;
      // path to evm library
	  char evm_lib[_MAX_PATH] = "../QEMU/qemu/ppdl-softmmu/libevm-ppdl.dll";
    // arguments of EVM run
	  const char* argv[6] = { evm_lib, "-nodebug", "-nodefaults", "-nographic", "-kernel", "add.bin" };
	  const int argc = 6;
    // run EVM
	  RunContractCode(evm_lib, argc, argv);
    // set next transaction state
      SET_NEXT_TRANSACTION(STATE2);
    }
  
  
  
Files:
  gVm1.h - base class for gVM level 1
  emv_client.h - blockchain client emulator
  testVM1.h - example of gVM1, that has 
  test.stm - file, that contains full history of state transactions. Last word of file contains the state of gVM1, that defines the next transaction function
  test_ref.stm - init state of gVM1
  main.cpp - test that runs all the states of gVM1 
  
Build gVM1 for Linux: 
  run script ./run.sh without parameters
 
Build gVM1 for Windows:
  Buid solution gVm1\gVm1.sln

How to run test:
  copy test_ref.stm to test.stm
  run executable gvm (gvm.exe)
  
Result is a log of transactions of gVM1



  
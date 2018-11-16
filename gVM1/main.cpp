#include <stdio.h>
#include <string>
#include "testVM1.h"

//#define SINGLE_ITERATION

int main()
{
  int iteration = 0;
  uint256 storage[1024];

  while(1)
  {
    // emulate single iteration
    // on each iteraction we emulate new run of contract:
    //   create new EVM and make single iteraction within the state machine
    TEvmClient  client_tmp(std::string("test.stm"),storage); // read contract's history from file test.stm
    TestVm1     tvm1_tmp;
    // check actual transaction
    if(client_tmp.GetCurState() == NO_TRANSACTION)
    {
       // no more transactions 
      printf("nothing to do for executed contract\n");
      return 0;
    }
    // make one interation
    if (!tvm1_tmp.RunTransaction(&client_tmp))
    {
      // error while start transaction
      printf("undefined state %d\n", client_tmp.GetCurState());
      exit(-1);
    }
    printf("iteration %d state %d\n",iteration++,client_tmp.GetCurState());
  }
  //end of contract
  printf("success\n");
  return 0;
}

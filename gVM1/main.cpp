#include <stdio.h>
#include "testVM1.h"


int main()
{
  TEvmClient client;
  TestVm1 tvm1(&client);
  int tcount = 0;
  
  // blockchain emulation
  while(client.GetID()!=NO_TRANSACTION)
  {
    printf("interation %d\n",tcount++);
    tvm1.RunTransaction(&client);
  }
  
  //end of contract
  printf("success\n");
  return 0;
}

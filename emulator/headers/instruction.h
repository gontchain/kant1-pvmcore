#ifndef INSTRUCTION_H
#define INSTRUCTION_H

struct tDisAsmInst
{
  char   *AsmString; // assembly string
  uint64  Addr;      // address of instruction
  int     size;      //  size of inst
  tInst   *Next;
};

#endif
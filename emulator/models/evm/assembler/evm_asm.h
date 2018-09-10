#ifndef EVM_ASSEMBLER_H
#define EVM_ASSEMBLER_H




int EVM_GetToken(char *istream,tToken *tok);
// decode list SystemOps 
#define NEXT_TOK(arg) NEXT_TOK_ARG(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_ARG(arg)
// decode list SystemOps 
int EVM_GetArg1(char** aInpStr,tToken *t,int start,int* tcount,int* reads){// SystemOps 
  int32 anum;
  tAsmArg arg[16];
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  NEXT_TOK(tidx0)
  INIT_ARGS(16); 
// start parse instruction
  int inst_inp_shift;
if(t[tidx0].type==13){ // ' CREATE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 0;
}
if(t[tidx0].type==14){ // ' CALL ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 1;
}
if(t[tidx0].type==15){ // ' CALLCODE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 2;
}
if(t[tidx0].type==16){ // ' RETURN ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 3;
}
if(t[tidx0].type==17){ // ' DELEGATECALL ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 4;
}
  SET_ERROR(0);
  return -1;
}
#undef NEXT_TOK
#undef SET_ERROR

// decode list BlockChain 
#define NEXT_TOK(arg) NEXT_TOK_ARG(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_ARG(arg)
// decode list BlockChain 
int EVM_GetArg2(char** aInpStr,tToken *t,int start,int* tcount,int* reads){// BlockChain 
  int32 anum;
  tAsmArg arg[16];
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  NEXT_TOK(tidx0)
  INIT_ARGS(16); 
// start parse instruction
  int inst_inp_shift;
if(t[tidx0].type==21){ // ' BLOCKHASH ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 0;
}
if(t[tidx0].type==22){ // ' COINBASE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 1;
}
if(t[tidx0].type==23){ // ' TIMESTAMP ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 2;
}
if(t[tidx0].type==24){ // ' NUMBER ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 3;
}
if(t[tidx0].type==25){ // ' DIFFICULTY ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 4;
}
if(t[tidx0].type==26){ // ' GASLIMIT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 5;
}
  SET_ERROR(0);
  return -1;
}
#undef NEXT_TOK
#undef SET_ERROR

// decode list AccountsData 
#define NEXT_TOK(arg) NEXT_TOK_ARG(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_ARG(arg)
// decode list AccountsData 
int EVM_GetArg3(char** aInpStr,tToken *t,int start,int* tcount,int* reads){// AccountsData 
  int32 anum;
  tAsmArg arg[16];
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  NEXT_TOK(tidx0)
  INIT_ARGS(16); 
// start parse instruction
  int inst_inp_shift;
if(t[tidx0].type==27){ // ' ADDRESS ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 0;
}
if(t[tidx0].type==28){ // ' BALANCE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 1;
}
if(t[tidx0].type==29){ // ' ORIGIN ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 2;
}
if(t[tidx0].type==30){ // ' CALLER ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 3;
}
if(t[tidx0].type==31){ // ' CALLVALUE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 4;
}
if(t[tidx0].type==32){ // ' CALLDATALOAD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 5;
}
if(t[tidx0].type==33){ // ' CALLDATASIZE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 6;
}
if(t[tidx0].type==34){ // ' CALLDATACOPY ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 7;
}
if(t[tidx0].type==35){ // ' CODESIZE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 8;
}
if(t[tidx0].type==36){ // ' CODECOPY ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 9;
}
if(t[tidx0].type==37){ // ' GASPRICE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 10;
}
if(t[tidx0].type==38){ // ' EXTCODESIZE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 11;
}
if(t[tidx0].type==39){ // ' EXTCODECOPY ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 12;
}
  SET_ERROR(0);
  return -1;
}
#undef NEXT_TOK
#undef SET_ERROR

// decode list MemOps 
#define NEXT_TOK(arg) NEXT_TOK_ARG(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_ARG(arg)
// decode list MemOps 
int EVM_GetArg4(char** aInpStr,tToken *t,int start,int* tcount,int* reads){// MemOps 
  int32 anum;
  tAsmArg arg[16];
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  NEXT_TOK(tidx0)
  INIT_ARGS(16); 
// start parse instruction
  int inst_inp_shift;
if(t[tidx0].type==40){ // ' POP ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 0;
}
if(t[tidx0].type==41){ // ' MLOAD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 1;
}
if(t[tidx0].type==42){ // ' MSTORE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 2;
}
if(t[tidx0].type==43){ // ' MSTORE8 ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 3;
}
if(t[tidx0].type==44){ // ' SLOAD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 4;
}
if(t[tidx0].type==45){ // ' SSTORE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 5;
}
if(t[tidx0].type==46){ // ' JUMP ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 6;
}
if(t[tidx0].type==47){ // ' JUMPI ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 7;
}
if(t[tidx0].type==48){ // ' PC ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 8;
}
if(t[tidx0].type==49){ // ' MSIZE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 9;
}
if(t[tidx0].type==50){ // ' GAS ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 10;
}
if(t[tidx0].type==51){ // ' JUMPDEST ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 11;
}
  SET_ERROR(0);
  return -1;
}
#undef NEXT_TOK
#undef SET_ERROR

// decode list ArithmOps 
#define NEXT_TOK(arg) NEXT_TOK_ARG(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_ARG(arg)
// decode list ArithmOps 
int EVM_GetArg5(char** aInpStr,tToken *t,int start,int* tcount,int* reads){// ArithmOps 
  int32 anum;
  tAsmArg arg[16];
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  NEXT_TOK(tidx0)
  INIT_ARGS(16); 
// start parse instruction
  int inst_inp_shift;
if(t[tidx0].type==52){ // ' STOP ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 0;
}
if(t[tidx0].type==53){ // ' ADD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 1;
}
if(t[tidx0].type==54){ // ' MUL ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 2;
}
if(t[tidx0].type==55){ // ' SUB ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 3;
}
if(t[tidx0].type==56){ // ' DIV ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 4;
}
if(t[tidx0].type==57){ // ' SDIV ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 5;
}
if(t[tidx0].type==58){ // ' MOD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 6;
}
if(t[tidx0].type==59){ // ' SMOD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 7;
}
if(t[tidx0].type==60){ // ' ADDMOD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 8;
}
if(t[tidx0].type==61){ // ' MULMOD ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 9;
}
if(t[tidx0].type==62){ // ' EXP ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 10;
}
if(t[tidx0].type==63){ // ' SIGNEXTEND ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 11;
}
  SET_ERROR(0);
  return -1;
}
#undef NEXT_TOK
#undef SET_ERROR

// decode list CompareLogOps 
#define NEXT_TOK(arg) NEXT_TOK_ARG(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_ARG(arg)
// decode list CompareLogOps 
int EVM_GetArg6(char** aInpStr,tToken *t,int start,int* tcount,int* reads){// CompareLogOps 
  int32 anum;
  tAsmArg arg[16];
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  NEXT_TOK(tidx0)
  INIT_ARGS(16); 
// start parse instruction
  int inst_inp_shift;
if(t[tidx0].type==64){ // ' LT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 0;
}
if(t[tidx0].type==65){ // ' GT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 1;
}
if(t[tidx0].type==66){ // ' SLT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 2;
}
if(t[tidx0].type==67){ // ' SGT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 3;
}
if(t[tidx0].type==68){ // ' EQ ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 4;
}
if(t[tidx0].type==69){ // ' ISZERO ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 5;
}
if(t[tidx0].type==70){ // ' AND ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 6;
}
if(t[tidx0].type==71){ // ' OR ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 7;
}
if(t[tidx0].type==72){ // ' XOR ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 8;
}
if(t[tidx0].type==73){ // ' NOT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 9;
}
if(t[tidx0].type==74){ // ' BYTE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
      *aInpStr = ibuf;
    return 10;
}
  SET_ERROR(0);
  return -1;
}
#undef NEXT_TOK
#undef SET_ERROR

// A parser for an instruction set 0 
#define NEXT_TOK(arg) NEXT_TOK_INST(arg,EVM)
#define SET_ERROR(arg)  SET_ERR_INST(arg)
tBinInst* EVM_GetInst0(char** aInpStr,tToken *t,int start,int* tcount,int* reads)
{
  int tidx0 = start;
  *reads = 0;
  char* ibuf = *aInpStr;
  tBinInst* inst;         // output instruction s
  tBinInst* kid_inst;     // output instruction s
  tAsmArg arg[64];         // array of instruction arguments
  int max_idx = tidx0;     // max chieved index
  NEXT_TOK(tidx0)
  int32  anum;           // temporary argument value
  INIT_ARGS(64); 
// start parse instruction
  int inst_inp_shift;
if((anum = EVM_GetArg1(&ibuf,t,tidx0,tcount,reads ))!=-1){ // syscall
  CHECK_SET_ARG_ISET(arg[0],(uint32)anum,tidx0);
  ibuf = t[*tcount].mEnd;
  int tidx1 = tidx0 + *reads;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x0f0|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: $syscall
  INIT_ARG(arg[0]);
}
if(t[tidx0].type==18){ // ' STATICCALL ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x0fa|(((uint64)(arg[1].Val&0xFF))<<0);
  *aInpStr = ibuf;
    return inst;// inst: STATICCALL
}
if(t[tidx0].type==19){ // ' REVERT ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x0fd|(((uint64)(arg[1].Val&0xFF))<<0);
  *aInpStr = ibuf;
    return inst;// inst: REVERT
}
if(t[tidx0].type==20){ // ' SUICIDE ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x0ff|(((uint64)(arg[1].Val&0xFF))<<0);
  *aInpStr = ibuf;
    return inst;// inst: SUICIDE
}
if((anum = EVM_GetArg2(&ibuf,t,tidx0,tcount,reads ))!=-1){ // gas_opcode
  CHECK_SET_ARG_ISET(arg[0],(uint32)anum,tidx0);
  ibuf = t[*tcount].mEnd;
  int tidx1 = tidx0 + *reads;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x040|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: $gas_opcode
  INIT_ARG(arg[0]);
}
if((anum = EVM_GetArg3(&ibuf,t,tidx0,tcount,reads ))!=-1){ // opcode
  CHECK_SET_ARG_ISET(arg[0],(uint32)anum,tidx0);
  ibuf = t[*tcount].mEnd;
  int tidx1 = tidx0 + *reads;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x030|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: $opcode
  INIT_ARG(arg[0]);
}
if(TokStrPrefixed(t,tidx0,"PUSH",&arg[0],&ibuf,5)!=0){ // prefix: PUSH 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x060|(((uint64)(arg[0].Val&0x1F))<<0)|(((uint64)(arg[1].Val&0x7))<<5);
  *aInpStr = ibuf;
    return inst;// inst: PUSH$count
  INIT_ARG(arg[0]);
}
if(TokStrPrefixed(t,tidx0,"DUP",&arg[0],&ibuf,4)!=0){ // prefix: DUP 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x080|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: DUP$count
  INIT_ARG(arg[0]);
}
if(TokStrPrefixed(t,tidx0,"SWAP",&arg[0],&ibuf,4)!=0){ // prefix: SWAP 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x090|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: SWAP$count
  INIT_ARG(arg[0]);
}
if(TokStrPrefixed(t,tidx0,"LOG",&arg[0],&ibuf,3)!=0){ // prefix: LOG 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x0a0|(((uint64)(arg[0].Val&0x7))<<0)|(((uint64)(arg[1].Val&0x1))<<3)|(((uint64)(arg[2].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: LOG$count
  INIT_ARG(arg[0]);
}
if((anum = EVM_GetArg4(&ibuf,t,tidx0,tcount,reads ))!=-1){ // opcode
  CHECK_SET_ARG_ISET(arg[0],(uint32)anum,tidx0);
  ibuf = t[*tcount].mEnd;
  int tidx1 = tidx0 + *reads;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x050|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: $opcode
  INIT_ARG(arg[0]);
}
if((anum = EVM_GetArg5(&ibuf,t,tidx0,tcount,reads ))!=-1){ // opcode
  CHECK_SET_ARG_ISET(arg[0],(uint32)anum,tidx0);
  ibuf = t[*tcount].mEnd;
  int tidx1 = tidx0 + *reads;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x00|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: $opcode
  INIT_ARG(arg[0]);
}
if((anum = EVM_GetArg6(&ibuf,t,tidx0,tcount,reads ))!=-1){ // opcode
  CHECK_SET_ARG_ISET(arg[0],(uint32)anum,tidx0);
  ibuf = t[*tcount].mEnd;
  int tidx1 = tidx0 + *reads;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x010|(((uint64)(arg[0].Val&0xF))<<0)|(((uint64)(arg[1].Val&0xF))<<4);
  *aInpStr = ibuf;
    return inst;// inst: $opcode
  INIT_ARG(arg[0]);
}
if(t[tidx0].type==75){ // ' SHA3 ' 
  int tidx1 = tidx0 + 1;
  *reads = tidx1  - start;
  inst_inp_shift = (uint32)t[tidx1-1].mEnd - (uint32)*aInpStr;
  
    inst = CreateBinInst(8,inst_inp_shift);
    inst->Data = 0x020|(((uint64)(arg[1].Val&0xFF))<<0);
  *aInpStr = ibuf;
    return inst;// inst: SHA3
}
  SET_ERROR(0);
  return NULL;
} // end of the assembly generator
#undef NEXT_TOK(arg)
#undef SET_ERROR(arg)

int EVM_GetToken(char *istream,tToken *tok)
{
  char *sp = istream;
GET_TOKEN:
  MISS_SPACES() // miss tabs and space bars
  REMOVE_COMMENTS("//") // miss comments in the stream
  char *tbegin = sp; // start of the recognition stream
  CHECK_EOL()    // check the end of the document or end of the file
  if(IS_DEC())  DECODE_VAL(tok)
  if(sp[0]==':'){
  sp+=1; RET_TOK(10); // token : 
  }// if(sp[0]==':')
  if(sp[0]=='='){
  sp+=1; RET_TOK(11); // token = 
  }// if(sp[0]=='=')
  if(sp[0]==';'){
  sp+=1; RET_TOK(12); // token ; 
  }// if(sp[0]==';')
  if(sp[0]=='C'){
  if(sp[1]=='R'){
  if(sp[2]=='E'){
  if(sp[3]=='A'){
  if(sp[4]=='T'){
  if(sp[5]=='E'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(13); // token CREATE 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='E')
  }// if(sp[4]=='T')
  }// if(sp[3]=='A')
  }// if(sp[2]=='E')
  }// if(sp[1]=='R')
  if(sp[1]=='A'){
  if(sp[2]=='L'){
  if(sp[3]=='L'){
  if(sp[4]=='C'){
  if(sp[5]=='O'){
  if(sp[6]=='D'){
  if(sp[7]=='E'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(15); // token CALLCODE 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='E')
  }// if(sp[6]=='D')
  }// if(sp[5]=='O')
  }// if(sp[4]=='C')
  if(sp[4]=='E'){
  if(sp[5]=='R'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(30); // token CALLER 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='R')
  }// if(sp[4]=='E')
  if(sp[4]=='V'){
  if(sp[5]=='A'){
  if(sp[6]=='L'){
  if(sp[7]=='U'){
  if(sp[8]=='E'){
  if ( IS_NOT_STRING(sp[9]) ) {
  sp+=9; RET_TOK(31); // token CALLVALUE 
  }// if (IS_NOT_STRING(sp[9]) 
  }// if(sp[8]=='E')
  }// if(sp[7]=='U')
  }// if(sp[6]=='L')
  }// if(sp[5]=='A')
  }// if(sp[4]=='V')
  if(sp[4]=='D'){
  if(sp[5]=='A'){
  if(sp[6]=='T'){
  if(sp[7]=='A'){
  if(sp[8]=='L'){
  if(sp[9]=='O'){
  if(sp[10]=='A'){
  if(sp[11]=='D'){
  if ( IS_NOT_STRING(sp[12]) ) {
  sp+=12; RET_TOK(32); // token CALLDATALOAD 
  }// if (IS_NOT_STRING(sp[12]) 
  }// if(sp[11]=='D')
  }// if(sp[10]=='A')
  }// if(sp[9]=='O')
  }// if(sp[8]=='L')
  if(sp[8]=='S'){
  if(sp[9]=='I'){
  if(sp[10]=='Z'){
  if(sp[11]=='E'){
  if ( IS_NOT_STRING(sp[12]) ) {
  sp+=12; RET_TOK(33); // token CALLDATASIZE 
  }// if (IS_NOT_STRING(sp[12]) 
  }// if(sp[11]=='E')
  }// if(sp[10]=='Z')
  }// if(sp[9]=='I')
  }// if(sp[8]=='S')
  if(sp[8]=='C'){
  if(sp[9]=='O'){
  if(sp[10]=='P'){
  if(sp[11]=='Y'){
  if ( IS_NOT_STRING(sp[12]) ) {
  sp+=12; RET_TOK(34); // token CALLDATACOPY 
  }// if (IS_NOT_STRING(sp[12]) 
  }// if(sp[11]=='Y')
  }// if(sp[10]=='P')
  }// if(sp[9]=='O')
  }// if(sp[8]=='C')
  }// if(sp[7]=='A')
  }// if(sp[6]=='T')
  }// if(sp[5]=='A')
  }// if(sp[4]=='D')
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(14); // token CALL 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='L')
  }// if(sp[2]=='L')
  }// if(sp[1]=='A')
  if(sp[1]=='O'){
  if(sp[2]=='I'){
  if(sp[3]=='N'){
  if(sp[4]=='B'){
  if(sp[5]=='A'){
  if(sp[6]=='S'){
  if(sp[7]=='E'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(22); // token COINBASE 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='E')
  }// if(sp[6]=='S')
  }// if(sp[5]=='A')
  }// if(sp[4]=='B')
  }// if(sp[3]=='N')
  }// if(sp[2]=='I')
  if(sp[2]=='D'){
  if(sp[3]=='E'){
  if(sp[4]=='S'){
  if(sp[5]=='I'){
  if(sp[6]=='Z'){
  if(sp[7]=='E'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(35); // token CODESIZE 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='E')
  }// if(sp[6]=='Z')
  }// if(sp[5]=='I')
  }// if(sp[4]=='S')
  if(sp[4]=='C'){
  if(sp[5]=='O'){
  if(sp[6]=='P'){
  if(sp[7]=='Y'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(36); // token CODECOPY 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='Y')
  }// if(sp[6]=='P')
  }// if(sp[5]=='O')
  }// if(sp[4]=='C')
  }// if(sp[3]=='E')
  }// if(sp[2]=='D')
  }// if(sp[1]=='O')
  }// if(sp[0]=='C')
  if(sp[0]=='R'){
  if(sp[1]=='E'){
  if(sp[2]=='T'){
  if(sp[3]=='U'){
  if(sp[4]=='R'){
  if(sp[5]=='N'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(16); // token RETURN 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='N')
  }// if(sp[4]=='R')
  }// if(sp[3]=='U')
  }// if(sp[2]=='T')
  if(sp[2]=='V'){
  if(sp[3]=='E'){
  if(sp[4]=='R'){
  if(sp[5]=='T'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(19); // token REVERT 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='T')
  }// if(sp[4]=='R')
  }// if(sp[3]=='E')
  }// if(sp[2]=='V')
  }// if(sp[1]=='E')
  }// if(sp[0]=='R')
  if(sp[0]=='D'){
  if(sp[1]=='E'){
  if(sp[2]=='L'){
  if(sp[3]=='E'){
  if(sp[4]=='G'){
  if(sp[5]=='A'){
  if(sp[6]=='T'){
  if(sp[7]=='E'){
  if(sp[8]=='C'){
  if(sp[9]=='A'){
  if(sp[10]=='L'){
  if(sp[11]=='L'){
  if ( IS_NOT_STRING(sp[12]) ) {
  sp+=12; RET_TOK(17); // token DELEGATECALL 
  }// if (IS_NOT_STRING(sp[12]) 
  }// if(sp[11]=='L')
  }// if(sp[10]=='L')
  }// if(sp[9]=='A')
  }// if(sp[8]=='C')
  }// if(sp[7]=='E')
  }// if(sp[6]=='T')
  }// if(sp[5]=='A')
  }// if(sp[4]=='G')
  }// if(sp[3]=='E')
  }// if(sp[2]=='L')
  }// if(sp[1]=='E')
  if(sp[1]=='I'){
  if(sp[2]=='F'){
  if(sp[3]=='F'){
  if(sp[4]=='I'){
  if(sp[5]=='C'){
  if(sp[6]=='U'){
  if(sp[7]=='L'){
  if(sp[8]=='T'){
  if(sp[9]=='Y'){
  if ( IS_NOT_STRING(sp[10]) ) {
  sp+=10; RET_TOK(25); // token DIFFICULTY 
  }// if (IS_NOT_STRING(sp[10]) 
  }// if(sp[9]=='Y')
  }// if(sp[8]=='T')
  }// if(sp[7]=='L')
  }// if(sp[6]=='U')
  }// if(sp[5]=='C')
  }// if(sp[4]=='I')
  }// if(sp[3]=='F')
  }// if(sp[2]=='F')
  if(sp[2]=='V'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(56); // token DIV 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='V')
  }// if(sp[1]=='I')
  }// if(sp[0]=='D')
  if(sp[0]=='S'){
  if(sp[1]=='T'){
  if(sp[2]=='A'){
  if(sp[3]=='T'){
  if(sp[4]=='I'){
  if(sp[5]=='C'){
  if(sp[6]=='C'){
  if(sp[7]=='A'){
  if(sp[8]=='L'){
  if(sp[9]=='L'){
  if ( IS_NOT_STRING(sp[10]) ) {
  sp+=10; RET_TOK(18); // token STATICCALL 
  }// if (IS_NOT_STRING(sp[10]) 
  }// if(sp[9]=='L')
  }// if(sp[8]=='L')
  }// if(sp[7]=='A')
  }// if(sp[6]=='C')
  }// if(sp[5]=='C')
  }// if(sp[4]=='I')
  }// if(sp[3]=='T')
  }// if(sp[2]=='A')
  if(sp[2]=='O'){
  if(sp[3]=='P'){
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(52); // token STOP 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='P')
  }// if(sp[2]=='O')
  }// if(sp[1]=='T')
  if(sp[1]=='U'){
  if(sp[2]=='I'){
  if(sp[3]=='C'){
  if(sp[4]=='I'){
  if(sp[5]=='D'){
  if(sp[6]=='E'){
  if ( IS_NOT_STRING(sp[7]) ) {
  sp+=7; RET_TOK(20); // token SUICIDE 
  }// if (IS_NOT_STRING(sp[7]) 
  }// if(sp[6]=='E')
  }// if(sp[5]=='D')
  }// if(sp[4]=='I')
  }// if(sp[3]=='C')
  }// if(sp[2]=='I')
  if(sp[2]=='B'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(55); // token SUB 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='B')
  }// if(sp[1]=='U')
  if(sp[1]=='L'){
  if(sp[2]=='O'){
  if(sp[3]=='A'){
  if(sp[4]=='D'){
  if ( IS_NOT_STRING(sp[5]) ) {
  sp+=5; RET_TOK(44); // token SLOAD 
  }// if (IS_NOT_STRING(sp[5]) 
  }// if(sp[4]=='D')
  }// if(sp[3]=='A')
  }// if(sp[2]=='O')
  if(sp[2]=='T'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(66); // token SLT 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='T')
  }// if(sp[1]=='L')
  if(sp[1]=='S'){
  if(sp[2]=='T'){
  if(sp[3]=='O'){
  if(sp[4]=='R'){
  if(sp[5]=='E'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(45); // token SSTORE 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='E')
  }// if(sp[4]=='R')
  }// if(sp[3]=='O')
  }// if(sp[2]=='T')
  }// if(sp[1]=='S')
  if(sp[1]=='D'){
  if(sp[2]=='I'){
  if(sp[3]=='V'){
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(57); // token SDIV 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='V')
  }// if(sp[2]=='I')
  }// if(sp[1]=='D')
  if(sp[1]=='M'){
  if(sp[2]=='O'){
  if(sp[3]=='D'){
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(59); // token SMOD 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='D')
  }// if(sp[2]=='O')
  }// if(sp[1]=='M')
  if(sp[1]=='I'){
  if(sp[2]=='G'){
  if(sp[3]=='N'){
  if(sp[4]=='E'){
  if(sp[5]=='X'){
  if(sp[6]=='T'){
  if(sp[7]=='E'){
  if(sp[8]=='N'){
  if(sp[9]=='D'){
  if ( IS_NOT_STRING(sp[10]) ) {
  sp+=10; RET_TOK(63); // token SIGNEXTEND 
  }// if (IS_NOT_STRING(sp[10]) 
  }// if(sp[9]=='D')
  }// if(sp[8]=='N')
  }// if(sp[7]=='E')
  }// if(sp[6]=='T')
  }// if(sp[5]=='X')
  }// if(sp[4]=='E')
  }// if(sp[3]=='N')
  }// if(sp[2]=='G')
  }// if(sp[1]=='I')
  if(sp[1]=='G'){
  if(sp[2]=='T'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(67); // token SGT 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='T')
  }// if(sp[1]=='G')
  if(sp[1]=='H'){
  if(sp[2]=='A'){
  if(sp[3]=='3'){
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(75); // token SHA3 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='3')
  }// if(sp[2]=='A')
  }// if(sp[1]=='H')
  }// if(sp[0]=='S')
  if(sp[0]=='B'){
  if(sp[1]=='L'){
  if(sp[2]=='O'){
  if(sp[3]=='C'){
  if(sp[4]=='K'){
  if(sp[5]=='H'){
  if(sp[6]=='A'){
  if(sp[7]=='S'){
  if(sp[8]=='H'){
  if ( IS_NOT_STRING(sp[9]) ) {
  sp+=9; RET_TOK(21); // token BLOCKHASH 
  }// if (IS_NOT_STRING(sp[9]) 
  }// if(sp[8]=='H')
  }// if(sp[7]=='S')
  }// if(sp[6]=='A')
  }// if(sp[5]=='H')
  }// if(sp[4]=='K')
  }// if(sp[3]=='C')
  }// if(sp[2]=='O')
  }// if(sp[1]=='L')
  if(sp[1]=='A'){
  if(sp[2]=='L'){
  if(sp[3]=='A'){
  if(sp[4]=='N'){
  if(sp[5]=='C'){
  if(sp[6]=='E'){
  if ( IS_NOT_STRING(sp[7]) ) {
  sp+=7; RET_TOK(28); // token BALANCE 
  }// if (IS_NOT_STRING(sp[7]) 
  }// if(sp[6]=='E')
  }// if(sp[5]=='C')
  }// if(sp[4]=='N')
  }// if(sp[3]=='A')
  }// if(sp[2]=='L')
  }// if(sp[1]=='A')
  if(sp[1]=='Y'){
  if(sp[2]=='T'){
  if(sp[3]=='E'){
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(74); // token BYTE 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='E')
  }// if(sp[2]=='T')
  }// if(sp[1]=='Y')
  }// if(sp[0]=='B')
  if(sp[0]=='T'){
  if(sp[1]=='I'){
  if(sp[2]=='M'){
  if(sp[3]=='E'){
  if(sp[4]=='S'){
  if(sp[5]=='T'){
  if(sp[6]=='A'){
  if(sp[7]=='M'){
  if(sp[8]=='P'){
  if ( IS_NOT_STRING(sp[9]) ) {
  sp+=9; RET_TOK(23); // token TIMESTAMP 
  }// if (IS_NOT_STRING(sp[9]) 
  }// if(sp[8]=='P')
  }// if(sp[7]=='M')
  }// if(sp[6]=='A')
  }// if(sp[5]=='T')
  }// if(sp[4]=='S')
  }// if(sp[3]=='E')
  }// if(sp[2]=='M')
  }// if(sp[1]=='I')
  }// if(sp[0]=='T')
  if(sp[0]=='N'){
  if(sp[1]=='U'){
  if(sp[2]=='M'){
  if(sp[3]=='B'){
  if(sp[4]=='E'){
  if(sp[5]=='R'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(24); // token NUMBER 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='R')
  }// if(sp[4]=='E')
  }// if(sp[3]=='B')
  }// if(sp[2]=='M')
  }// if(sp[1]=='U')
  if(sp[1]=='O'){
  if(sp[2]=='T'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(73); // token NOT 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='T')
  }// if(sp[1]=='O')
  }// if(sp[0]=='N')
  if(sp[0]=='G'){
  if(sp[1]=='A'){
  if(sp[2]=='S'){
  if(sp[3]=='L'){
  if(sp[4]=='I'){
  if(sp[5]=='M'){
  if(sp[6]=='I'){
  if(sp[7]=='T'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(26); // token GASLIMIT 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='T')
  }// if(sp[6]=='I')
  }// if(sp[5]=='M')
  }// if(sp[4]=='I')
  }// if(sp[3]=='L')
  if(sp[3]=='P'){
  if(sp[4]=='R'){
  if(sp[5]=='I'){
  if(sp[6]=='C'){
  if(sp[7]=='E'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(37); // token GASPRICE 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='E')
  }// if(sp[6]=='C')
  }// if(sp[5]=='I')
  }// if(sp[4]=='R')
  }// if(sp[3]=='P')
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(50); // token GAS 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='S')
  }// if(sp[1]=='A')
  if(sp[1]=='T'){
  if ( IS_NOT_STRING(sp[2]) ) {
  sp+=2; RET_TOK(65); // token GT 
  }// if (IS_NOT_STRING(sp[2]) 
  }// if(sp[1]=='T')
  }// if(sp[0]=='G')
  if(sp[0]=='A'){
  if(sp[1]=='D'){
  if(sp[2]=='D'){
  if(sp[3]=='R'){
  if(sp[4]=='E'){
  if(sp[5]=='S'){
  if(sp[6]=='S'){
  if ( IS_NOT_STRING(sp[7]) ) {
  sp+=7; RET_TOK(27); // token ADDRESS 
  }// if (IS_NOT_STRING(sp[7]) 
  }// if(sp[6]=='S')
  }// if(sp[5]=='S')
  }// if(sp[4]=='E')
  }// if(sp[3]=='R')
  if(sp[3]=='M'){
  if(sp[4]=='O'){
  if(sp[5]=='D'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(60); // token ADDMOD 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='D')
  }// if(sp[4]=='O')
  }// if(sp[3]=='M')
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(53); // token ADD 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='D')
  }// if(sp[1]=='D')
  if(sp[1]=='N'){
  if(sp[2]=='D'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(70); // token AND 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='D')
  }// if(sp[1]=='N')
  }// if(sp[0]=='A')
  if(sp[0]=='O'){
  if(sp[1]=='R'){
  if(sp[2]=='I'){
  if(sp[3]=='G'){
  if(sp[4]=='I'){
  if(sp[5]=='N'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(29); // token ORIGIN 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='N')
  }// if(sp[4]=='I')
  }// if(sp[3]=='G')
  }// if(sp[2]=='I')
  if ( IS_NOT_STRING(sp[2]) ) {
  sp+=2; RET_TOK(71); // token OR 
  }// if (IS_NOT_STRING(sp[2]) 
  }// if(sp[1]=='R')
  }// if(sp[0]=='O')
  if(sp[0]=='E'){
  if(sp[1]=='X'){
  if(sp[2]=='T'){
  if(sp[3]=='C'){
  if(sp[4]=='O'){
  if(sp[5]=='D'){
  if(sp[6]=='E'){
  if(sp[7]=='S'){
  if(sp[8]=='I'){
  if(sp[9]=='Z'){
  if(sp[10]=='E'){
  if ( IS_NOT_STRING(sp[11]) ) {
  sp+=11; RET_TOK(38); // token EXTCODESIZE 
  }// if (IS_NOT_STRING(sp[11]) 
  }// if(sp[10]=='E')
  }// if(sp[9]=='Z')
  }// if(sp[8]=='I')
  }// if(sp[7]=='S')
  if(sp[7]=='C'){
  if(sp[8]=='O'){
  if(sp[9]=='P'){
  if(sp[10]=='Y'){
  if ( IS_NOT_STRING(sp[11]) ) {
  sp+=11; RET_TOK(39); // token EXTCODECOPY 
  }// if (IS_NOT_STRING(sp[11]) 
  }// if(sp[10]=='Y')
  }// if(sp[9]=='P')
  }// if(sp[8]=='O')
  }// if(sp[7]=='C')
  }// if(sp[6]=='E')
  }// if(sp[5]=='D')
  }// if(sp[4]=='O')
  }// if(sp[3]=='C')
  }// if(sp[2]=='T')
  if(sp[2]=='P'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(62); // token EXP 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='P')
  }// if(sp[1]=='X')
  if(sp[1]=='Q'){
  if ( IS_NOT_STRING(sp[2]) ) {
  sp+=2; RET_TOK(68); // token EQ 
  }// if (IS_NOT_STRING(sp[2]) 
  }// if(sp[1]=='Q')
  }// if(sp[0]=='E')
  if(sp[0]=='P'){
  if(sp[1]=='O'){
  if(sp[2]=='P'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(40); // token POP 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='P')
  }// if(sp[1]=='O')
  if(sp[1]=='C'){
  if ( IS_NOT_STRING(sp[2]) ) {
  sp+=2; RET_TOK(48); // token PC 
  }// if (IS_NOT_STRING(sp[2]) 
  }// if(sp[1]=='C')
  }// if(sp[0]=='P')
  if(sp[0]=='M'){
  if(sp[1]=='L'){
  if(sp[2]=='O'){
  if(sp[3]=='A'){
  if(sp[4]=='D'){
  if ( IS_NOT_STRING(sp[5]) ) {
  sp+=5; RET_TOK(41); // token MLOAD 
  }// if (IS_NOT_STRING(sp[5]) 
  }// if(sp[4]=='D')
  }// if(sp[3]=='A')
  }// if(sp[2]=='O')
  }// if(sp[1]=='L')
  if(sp[1]=='S'){
  if(sp[2]=='T'){
  if(sp[3]=='O'){
  if(sp[4]=='R'){
  if(sp[5]=='E'){
  if(sp[6]=='8'){
  if ( IS_NOT_STRING(sp[7]) ) {
  sp+=7; RET_TOK(43); // token MSTORE8 
  }// if (IS_NOT_STRING(sp[7]) 
  }// if(sp[6]=='8')
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(42); // token MSTORE 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='E')
  }// if(sp[4]=='R')
  }// if(sp[3]=='O')
  }// if(sp[2]=='T')
  if(sp[2]=='I'){
  if(sp[3]=='Z'){
  if(sp[4]=='E'){
  if ( IS_NOT_STRING(sp[5]) ) {
  sp+=5; RET_TOK(49); // token MSIZE 
  }// if (IS_NOT_STRING(sp[5]) 
  }// if(sp[4]=='E')
  }// if(sp[3]=='Z')
  }// if(sp[2]=='I')
  }// if(sp[1]=='S')
  if(sp[1]=='U'){
  if(sp[2]=='L'){
  if(sp[3]=='M'){
  if(sp[4]=='O'){
  if(sp[5]=='D'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(61); // token MULMOD 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='D')
  }// if(sp[4]=='O')
  }// if(sp[3]=='M')
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(54); // token MUL 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='L')
  }// if(sp[1]=='U')
  if(sp[1]=='O'){
  if(sp[2]=='D'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(58); // token MOD 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='D')
  }// if(sp[1]=='O')
  }// if(sp[0]=='M')
  if(sp[0]=='J'){
  if(sp[1]=='U'){
  if(sp[2]=='M'){
  if(sp[3]=='P'){
  if(sp[4]=='I'){
  if ( IS_NOT_STRING(sp[5]) ) {
  sp+=5; RET_TOK(47); // token JUMPI 
  }// if (IS_NOT_STRING(sp[5]) 
  }// if(sp[4]=='I')
  if(sp[4]=='D'){
  if(sp[5]=='E'){
  if(sp[6]=='S'){
  if(sp[7]=='T'){
  if ( IS_NOT_STRING(sp[8]) ) {
  sp+=8; RET_TOK(51); // token JUMPDEST 
  }// if (IS_NOT_STRING(sp[8]) 
  }// if(sp[7]=='T')
  }// if(sp[6]=='S')
  }// if(sp[5]=='E')
  }// if(sp[4]=='D')
  if ( IS_NOT_STRING(sp[4]) ) {
  sp+=4; RET_TOK(46); // token JUMP 
  }// if (IS_NOT_STRING(sp[4]) 
  }// if(sp[3]=='P')
  }// if(sp[2]=='M')
  }// if(sp[1]=='U')
  }// if(sp[0]=='J')
  if(sp[0]=='L'){
  if(sp[1]=='T'){
  if ( IS_NOT_STRING(sp[2]) ) {
  sp+=2; RET_TOK(64); // token LT 
  }// if (IS_NOT_STRING(sp[2]) 
  }// if(sp[1]=='T')
  }// if(sp[0]=='L')
  if(sp[0]=='I'){
  if(sp[1]=='S'){
  if(sp[2]=='Z'){
  if(sp[3]=='E'){
  if(sp[4]=='R'){
  if(sp[5]=='O'){
  if ( IS_NOT_STRING(sp[6]) ) {
  sp+=6; RET_TOK(69); // token ISZERO 
  }// if (IS_NOT_STRING(sp[6]) 
  }// if(sp[5]=='O')
  }// if(sp[4]=='R')
  }// if(sp[3]=='E')
  }// if(sp[2]=='Z')
  }// if(sp[1]=='S')
  }// if(sp[0]=='I')
  if(sp[0]=='X'){
  if(sp[1]=='O'){
  if(sp[2]=='R'){
  if ( IS_NOT_STRING(sp[3]) ) {
  sp+=3; RET_TOK(72); // token XOR 
  }// if (IS_NOT_STRING(sp[3]) 
  }// if(sp[2]=='R')
  }// if(sp[1]=='O')
  }// if(sp[0]=='X')
  ERR_TOK(tok)
}
tBinInst* EVM_GetExp(char *ibuf){
  tToken t[64];           // aray of input tokens
  int read_tokens = 0;          // tokens are read
  int start = 0;          // start token 
  int tcount = -1;        // token counter

  return EVM_GetInst0(&ibuf,t,start,&tcount,&read_tokens);
}

int EVM_Main_GetImmValue(unsigned int *insn,unsigned long *imm_val){
  if( ((BIN_INSN(uint8)&0x0f0) == 0x0f0) ){
  // inst: $syscall 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x0fa) ){
  // inst: STATICCALL 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x0fd) ){
  // inst: REVERT 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x0ff) ){
  // inst: SUICIDE 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x040) ){
  // inst: $gas_opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x030) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0e0) == 0x060) ){
  // inst: PUSH$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x080) ){
  // inst: DUP$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x090) ){
  // inst: SWAP$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f8) == 0x0a0) ){
  // inst: LOG$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x050) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x00) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x010) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x020) ){
  // inst: SHA3 
      return 1;
  }
  return 0;
}
int EVM_Main_SetImmValue(unsigned int *insn,unsigned long *imm_val){
  if( ((BIN_INSN(uint8)&0x0f0) == 0x0f0) ){
  // inst: $syscall 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x0fa) ){
  // inst: STATICCALL 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x0fd) ){
  // inst: REVERT 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x0ff) ){
  // inst: SUICIDE 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x040) ){
  // inst: $gas_opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x030) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0e0) == 0x060) ){
  // inst: PUSH$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x080) ){
  // inst: DUP$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x090) ){
  // inst: SWAP$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f8) == 0x0a0) ){
  // inst: LOG$count 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x050) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x00) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0f0) == 0x010) ){
  // inst: $opcode 
      return 1;
  }
  if( ((BIN_INSN(uint8)&0x0ff) == 0x020) ){
  // inst: SHA3 
      return 1;
  }
  return 0;
}
#define GET_INST_IMM_VAL EVM_Main_GetImmValue
#define SET_INST_IMM_VAL EVM_Main_SetImmValue
#endif
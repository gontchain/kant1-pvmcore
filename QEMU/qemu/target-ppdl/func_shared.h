#ifndef FUNC_SHARED_H
#define FUNC_SHARED_H
#include "cpu.h"

typedef uint64_t uint256;
uint64_t MakeCall(CPUPPDLState *env);
uint64_t EqOp(CPUPPDLState *env);
uint64_t GetInputData(CPUPPDLState *env);
uint64_t SignExtend(CPUPPDLState *env);
uint64_t AndOp(CPUPPDLState *env);
uint64_t GtOpS(CPUPPDLState *env);
uint64_t CallDataCopy(CPUPPDLState *env);
uint64_t DelegateCall(CPUPPDLState *env);
uint64_t StopOp(CPUPPDLState *env);
uint64_t DivOpS(CPUPPDLState *env);
uint64_t GetModuleAdd(CPUPPDLState *env);
uint64_t GtOp(CPUPPDLState *env);
uint64_t SubOp(CPUPPDLState *env);
uint64_t Return(CPUPPDLState *env);
uint64_t LtOpS(CPUPPDLState *env);
uint64_t GetOrigin(CPUPPDLState *env);
uint64_t GetModuleS(CPUPPDLState *env);
uint64_t GetGasPrice(CPUPPDLState *env);
uint64_t CallValue(CPUPPDLState *env);
uint64_t GetGasLimit(CPUPPDLState *env);
uint64_t CodeCopy(CPUPPDLState *env);
uint64_t ExtCodeCopy(CPUPPDLState *env);
uint64_t GetTimeStamp(CPUPPDLState *env);
uint64_t GetModuleMul(CPUPPDLState *env);
uint64_t XorOp(CPUPPDLState *env);
uint64_t BlockChainHash(CPUPPDLState *env);
uint64_t AddOp(CPUPPDLState *env);
uint64_t OrOp(CPUPPDLState *env);
uint64_t CreateAccount(CPUPPDLState *env);
uint64_t MulOp(CPUPPDLState *env);
uint64_t GetNumber(CPUPPDLState *env);
uint64_t IsZeroOp(CPUPPDLState *env);
uint64_t LtOp(CPUPPDLState *env);
uint64_t GetBalance(CPUPPDLState *env);
uint64_t GetElfSize(CPUPPDLState *env);
uint64_t GetAddress(CPUPPDLState *env);
uint64_t NotOp(CPUPPDLState *env);
uint64_t GetDifficulty(CPUPPDLState *env);
uint64_t Push(CPUPPDLState *env, uint64_t val);
uint64_t GetCodeSize(CPUPPDLState *env);
uint64_t MakeCallCode(CPUPPDLState *env);
uint64_t Pop(CPUPPDLState *env);
uint64_t CallDataSize(CPUPPDLState *env);
uint64_t GetCaller(CPUPPDLState *env);
uint64_t StopExec(CPUPPDLState *env);
uint64_t GetModule(CPUPPDLState *env);
uint64_t ByteFromWord(CPUPPDLState *env);
uint64_t GetCoinBase(CPUPPDLState *env);
uint64_t DivOp(CPUPPDLState *env);
uint64_t ExtCodeSize(CPUPPDLState *env);
uint64_t GetExp(CPUPPDLState *env);

#endif
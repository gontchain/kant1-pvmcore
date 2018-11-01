#ifndef FUNC_SHARED_H
#define FUNC_SHARED_H
#include "cpu.h"

typedef uint64_t uint256;
uint64_t MakeCall(CPUPPDLState *env);
uint64_t GetInputData(CPUPPDLState *env);
uint64_t CallDataCopy(CPUPPDLState *env);
uint64_t DelegateCall(CPUPPDLState *env);
uint64_t GetElfSizeStub(CPUPPDLState *env);
uint64_t Pop(CPUPPDLState *env);
uint64_t Return(CPUPPDLState *env);
uint64_t GetOrigin(CPUPPDLState *env);
uint64_t USEGAS(CPUPPDLState *env, uint64_t value);
uint64_t GetGasPrice(CPUPPDLState *env);
uint64_t CallValue(CPUPPDLState *env);
uint64_t GetGasLimit(CPUPPDLState *env);
uint64_t GetTimeStamp(CPUPPDLState *env);
uint64_t CodeCopy(CPUPPDLState *env);
uint64_t BlockChainHash(CPUPPDLState *env);
uint64_t GetSingleBlockFromStack(CPUPPDLState *env);
uint64_t GetCaller(CPUPPDLState *env);
uint64_t CreateAccount(CPUPPDLState *env);
uint64_t ExtCodeCopy(CPUPPDLState *env);
uint64_t GetNumber(CPUPPDLState *env);
uint64_t GetBalance(CPUPPDLState *env);
uint64_t GetDifficulty(CPUPPDLState *env);
uint64_t GetAddress(CPUPPDLState *env);
uint64_t MakeCallCode(CPUPPDLState *env);
uint64_t GetCodeSize(CPUPPDLState *env);
uint64_t PushSingleBlockToStack(CPUPPDLState *env, uint64_t data_tmp);
uint64_t CallDataSize(CPUPPDLState *env);
uint64_t StopExec(CPUPPDLState *env);
uint64_t GetCoinBase(CPUPPDLState *env);
uint64_t ExtCodeSize(CPUPPDLState *env);

#endif
#include "cpu.h"
#include "func_shared.h"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wshift-count-overflow"


uint64_t HELPER(AccountsData)(CPUPPDLState *env, uint64_t aVal) {
	switch (aVal) {
		case 0:
			return GetAddress(env);
			break;
		case 1:
			return GetBalance(env);
			break;
		case 2:
			return GetOrigin(env);
			break;
		case 3:
			return GetCaller(env);
			break;
		case 4:
			return CallValue(env);
			break;
		case 5:
			return GetInputData(env);
			break;
		case 6:
			return CallDataSize(env);
			break;
		case 7:
			return CallDataCopy(env);
			break;
		case 8:
			return GetCodeSize(env);
			break;
		case 9:
			return CodeCopy(env);
			break;
		case 10:
			return GetGasPrice(env);
			break;
		case 11:
			return ExtCodeSize(env);
			break;
		case 12:
			return ExtCodeCopy(env);
			break;
	}
}

uint64_t HELPER(SystemOps)(CPUPPDLState *env, uint64_t aVal) {
	switch (aVal) {
		case 0:
			return CreateAccount(env);
			break;
		case 1:
			return MakeCall(env);
			break;
		case 2:
			return MakeCallCode(env);
			break;
		case 3:
			return Return(env);
			break;
		case 4:
			return DelegateCall(env);
			break;
	}
}

uint64_t HELPER(ArithmOps)(CPUPPDLState *env, uint64_t aVal) {
	switch (aVal) {
		case 0:
			return StopOp(env);
			break;
		case 1:
			return AddOp(env);
			break;
		case 2:
			return MulOp(env);
			break;
		case 3:
			return SubOp(env);
			break;
		case 4:
			return DivOp(env);
			break;
		case 5:
			return DivOpS(env);
			break;
		case 6:
			return GetModule(env);
			break;
		case 7:
			return GetModuleS(env);
			break;
		case 8:
			return GetModuleAdd(env);
			break;
		case 9:
			return GetModuleMul(env);
			break;
		case 10:
			return GetExp(env);
			break;
		case 11:
			return SignExtend(env);
			break;
	}
}

uint64_t HELPER(MemOps)(CPUPPDLState *env, uint64_t aVal) {
	switch (aVal) {
		case 0:
			return 0x0;
			break;
		case 1:
			return 0x1;
			break;
		case 2:
			return 0x2;
			break;
		case 3:
			return 0x3;
			break;
		case 4:
			return 0x4;
			break;
		case 5:
			return 0x5;
			break;
		case 6:
			return 0x6;
			break;
		case 7:
			return 0x7;
			break;
		case 8:
			return 0x8;
			break;
		case 9:
			return 0x9;
			break;
		case 10:
			return 0xA;
			break;
		case 11:
			return 0xB;
			break;
	}
}

uint64_t HELPER(BlockChain)(CPUPPDLState *env, uint64_t aVal) {
	switch (aVal) {
		case 0:
			return BlockChainHash(env);
			break;
		case 1:
			return GetCoinBase(env);
			break;
		case 2:
			return GetTimeStamp(env);
			break;
		case 3:
			return GetNumber(env);
			break;
		case 4:
			return GetDifficulty(env);
			break;
		case 5:
			return GetGasLimit(env);
			break;
	}
}

uint64_t HELPER(CompareLogOps)(CPUPPDLState *env, uint64_t aVal) {
	switch (aVal) {
		case 0:
			return LtOp(env);
			break;
		case 1:
			return GtOp(env);
			break;
		case 2:
			return LtOpS(env);
			break;
		case 3:
			return GtOpS(env);
			break;
		case 4:
			return EqOp(env);
			break;
		case 5:
			return IsZeroOp(env);
			break;
		case 6:
			return AndOp(env);
			break;
		case 7:
			return OrOp(env);
			break;
		case 8:
			return XorOp(env);
			break;
		case 9:
			return NotOp(env);
			break;
		case 10:
			return ByteFromWord(env);
			break;
	}
}

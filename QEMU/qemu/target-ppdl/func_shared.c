#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "func_shared.h"
#include "functions.h"

uint64_t MakeCall(CPUPPDLState *env) {
	USEGAS(env, 0x28);
	return (uint64)( 0x0 );
}

uint64_t GetInputData(CPUPPDLState *env) {
	USEGAS(env, 0x3);
	return (uint64)( 0x0 );
}

uint64_t CallDataCopy(CPUPPDLState *env) {
	USEGAS(env, 0x3);
	return (uint64)( 0x0 );
}

uint64_t DelegateCall(CPUPPDLState *env) {
	USEGAS(env, 0x28);
	return (uint64)( 0x0 );
}

uint64_t GetElfSizeStub(CPUPPDLState *env) {
	return GetElfSize(env);
}

uint64_t Pop(CPUPPDLState *env) {
	env->sp = (env->sp-0x4);
}

uint64_t Return(CPUPPDLState *env) {
	USEGAS(env, 0x0);
	StopExec(env);
	return (uint64)( 0x0 );
}

uint64_t GetOrigin(CPUPPDLState *env) {
	uint64_t oa;
	oa = env->origin_addr;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( oa ));
	return (uint64)( 0x0 );
}

uint64_t USEGAS(CPUPPDLState *env, uint64_t value) {
	UseGas(env, value);
}

uint64_t GetGasPrice(CPUPPDLState *env) {
	uint64_t gp;
	gp = env->gas_price;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( gp ));
	return (uint64)( 0x0 );
}

uint64_t CallValue(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	return (uint64)( 0x0 );
}

uint64_t GetGasLimit(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->GasLimit);
}

uint64_t GetTimeStamp(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->TimeStamp);
}

uint64_t CodeCopy(CPUPPDLState *env) {
	USEGAS(env, 0x3);
	return (uint64)( 0x0 );
}

uint64_t BlockChainHash(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	PushSingleBlockToStack(env, (uint64)( 0x0 ));
	return (uint64)( 0x0 );
}

uint64_t GetSingleBlockFromStack(CPUPPDLState *env) {
	uint32_t i;
	uint64_t data_tmp;
	uint64_t data_val;
	data_val = 0x0;
	data_tmp = env->stack_arr[(env->sp-0x3)];
	env->sp = (env->sp-0x4);
	for (i = 0x0; (i < 0x8); i = (i+0x1)) {
		data_val = (data_val|pd_lsh((pd_rsh(data_tmp, (0x8*(0x7-i)))&0xFF), i));
	}
	return data_val;
}

uint64_t GetCaller(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->caller_addr;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( ca ));
	return (uint64)( 0x0 );
}

uint64_t CreateAccount(CPUPPDLState *env) {
	USEGAS(env, 0x7D00);
	return (uint64)( 0x0 );
}

uint64_t ExtCodeCopy(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	return (uint64)( 0x0 );
}

uint64_t GetNumber(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->Number);
}

uint64_t GetBalance(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	return (uint64)( 0x0 );
}

uint64_t GetDifficulty(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->Difficulty);
}

uint64_t GetAddress(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->cur_addr;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( ca ));
	return (uint64)( 0x0 );
}

uint64_t MakeCallCode(CPUPPDLState *env) {
	USEGAS(env, 0x28);
	return (uint64)( 0x0 );
}

uint64_t GetCodeSize(CPUPPDLState *env) {
	uint64_t elf_size;
	elf_size = GetElfSizeStub(env);
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, elf_size);
	return (uint64)( 0x0 );
}

uint64_t PushSingleBlockToStack(CPUPPDLState *env, uint64_t data_tmp) {
	uint32_t i;
	uint64_t data_val;
	data_val = 0x0;
	for (i = 0x0; (i < 0x8); i = (i+0x1)) {
		data_val = (data_val|pd_lsh((pd_rsh(data_tmp, (0x8*i))&0xFF), (0x8*(0x7-i))));
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = data_val;
	env->stack_arr[(env->sp+0x1)] = 0x0;
	env->stack_arr[(env->sp+0x2)] = 0x0;
	env->stack_arr[(env->sp+0x3)] = 0x0;
	env->sp = (env->sp+0x3);
}

uint64_t CallDataSize(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->inp_data_size);
	return (uint64)( 0x0 );
}

uint64_t StopExec(CPUPPDLState *env) {
	helper_error_message(env, 1, 0x0);
	result_message(env);
}

uint64_t GetCoinBase(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->CoinBase);
}

uint64_t ExtCodeSize(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	PushSingleBlockToStack(env, env->ext_code_size);
	return (uint64)( 0x0 );
}

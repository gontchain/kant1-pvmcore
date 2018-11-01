#include "func_shared.h"
#include "functions.h"
#include "qemu-common.h"
#include "exec/cpu_ldst.h"
#include "bitfield.h"
#include "Keccak.h"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

typedef uint64_t uint256;

uint64_t HELPER(MakeCall)(CPUPPDLState *env) {
	USEGAS(env, 0x28);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetInputData)(CPUPPDLState *env) {
	USEGAS(env, 0x3);
	return (uint64)( 0x0 );
}

uint64_t HELPER(SaveToStorageStub)(CPUPPDLState *env, uint64_t addr) {
	SaveToStorage(env, addr);
}

uint64_t HELPER(CallDataCopy)(CPUPPDLState *env) {
	USEGAS(env, 0x3);
	return (uint64)( 0x0 );
}

uint64_t HELPER(DelegateCall)(CPUPPDLState *env) {
	USEGAS(env, 0x28);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetElfSizeStub)(CPUPPDLState *env) {
	return GetElfSize(env);
}

uint64_t HELPER(Pop)(CPUPPDLState *env) {
	env->sp = (env->sp-0x4);
}

uint64_t HELPER(MSizeOp)(CPUPPDLState *env) {
	uint32_t i;
	uint64_t data_tmp;
	uint64_t data_val;
	data_tmp = (uint64)( env->mem_size );
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

uint64_t HELPER(DupOp)(CPUPPDLState *env, uint64_t count) {
	uint32_t i;
	uint64_t copy_el;
	uint32_t offset;
	uint32_t _count = (uint32_t)count;
	offset = (0x4*_count);
	for (i = 0x0; (i < 0x4); i = (i+0x1)) {
		copy_el = env->stack_arr[(env->sp-(offset+i))];
	}
	env->sp = (env->sp+0x1);
	for (i = 0x0; (i < 0x4); i = (i+0x1)) {
		env->stack_arr[(env->sp+i)] = copy_el;
	}
	env->sp = (env->sp+0x3);
}

uint64_t HELPER(MStoreInst)(CPUPPDLState *env, uint64_t addr_val) {
	uint32_t i;
	uint64_t data_tmp;
	uint32_t j;
	uint64_t data_val;
	data_val = env->stack_arr[env->sp];
	data_val = env->stack_arr[(env->sp-0x1)];
	data_val = env->stack_arr[(env->sp-0x2)];
	data_val = env->stack_arr[(env->sp-0x3)];
	env->sp = (env->sp-0x4);
	for (j = 0x3; ((signed)j >= 0x0); j = (j-0x1)) {
		for (i = 0x0; (i < 0x8); i = (i+0x1)) {
			data_tmp = (pd_rsh(data_val, (0x8*i))&0xFF);
			env->data_bus[addr_val] = (uint8)( data_tmp );
			addr_val = (addr_val+0x1);
		}
	}
	if ((addr_val > env->mem_size)) {
		env->mem_size = addr_val;
	}
}

uint64_t HELPER(Return)(CPUPPDLState *env) {
	USEGAS(env, 0x0);
	StopExec(env);
	return (uint64)( 0x0 );
}

uint64_t HELPER(ArithmStub)(CPUPPDLState *env, uint64_t opcode) {
	uint32_t _opcode = (uint32_t)opcode;
	DoArithm(env, _opcode);
}

uint64_t HELPER(MloadInst)(CPUPPDLState *env, uint64_t addr_val) {
	uint32_t i;
	uint64_t data_tmp;
	uint32_t j;
	uint64_t data_val;
	uint32_t init_shift;
	uint32_t _addr_val = (uint32_t)addr_val;
	for (j = 0x3; ((signed)j >= 0x0); j = (j-0x1)) {
		data_val = 0x0;
		for (i = 0x0; (i < 0x8); i = (i+0x1)) {
			data_tmp = pd_lsh((uint64)( env->data_bus[_addr_val] ), (0x8*i));
			data_val = (data_val|data_tmp);
			_addr_val = (_addr_val+0x1);
		}
	}
	env->stack_arr[(env->sp+0x1)] = data_val;
	env->stack_arr[(env->sp+0x2)] = data_val;
	env->stack_arr[(env->sp+0x3)] = data_val;
	env->stack_arr[(env->sp+0x4)] = data_val;
	env->sp = (env->sp+0x4);
	return 0x0;
}

uint64_t HELPER(GetOrigin)(CPUPPDLState *env) {
	uint64_t oa;
	oa = env->origin_addr;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( oa ));
	return (uint64)( 0x0 );
}

uint64_t HELPER(USEGAS)(CPUPPDLState *env, uint64_t value) {
	UseGas(env, value);
}

uint64_t HELPER(GetGasPrice)(CPUPPDLState *env) {
	uint64_t gp;
	gp = env->gas_price;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( gp ));
	return (uint64)( 0x0 );
}

uint64_t HELPER(CallValue)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetGasLimit)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->GasLimit);
}

uint64_t HELPER(PushInst)(CPUPPDLState *env, uint64_t cnt) {
	uint32_t i;
	uint64_t a;
	uint64_t block_cnt;
	uint32_t j;
	uint64_t tmp;
	uint32_t _cnt = (uint32_t)cnt;
	a = 0x0;
	block_cnt = 0x0;
	env->sp = (env->sp+0x1);
	for (j = 0x0; (j < (_cnt/0x8)); j = (j+0x1)) {
		a = 0x0;
		for (i = 0x0; (i < 0x8); i = (i+0x1)) {
			tmp = (helper_mem_ld8(env, (env->pc+((_cnt-i)-(0x8*j))))&0xFF);
			a = (a|pd_lsh(tmp, (0x8*(0x7-i))));
		}
		env->stack_arr[(env->sp+block_cnt)] = a;
		block_cnt = (block_cnt+0x1);
	}
	if (((_cnt&0x7) != 0x0)) {
		a = 0x0;
		for (i = 0x0; (i < (_cnt&0x7)); i = (i+0x1)) {
			tmp = (helper_mem_ld8(env, (env->pc+((_cnt&0x7)-i)))&0xFF);
			tmp = pd_lsh(tmp, (0x8*(0x7-i)));
			a = (a|tmp);
		}
		env->stack_arr[(env->sp+block_cnt)] = a;
		block_cnt = (block_cnt+0x1);
	}
	for (j = (j+0x1); (j < 0x4); j = (j+0x1)) {
		env->stack_arr[(env->sp+j)] = (uint64)( 0x0 );
	}
	env->sp = (env->sp+0x3);
	return 0x0;
}

uint64_t HELPER(KeccakAlgStub)(CPUPPDLState *env) {
	uint32_t a;
	uint32_t b;
	a = GetSingleBlockFromStack(env);
	b = GetSingleBlockFromStack(env);
	KeccakAlg(env, a, b);
}

uint64_t HELPER(CompareStub)(CPUPPDLState *env, uint64_t opcode) {
	uint32_t _opcode = (uint32_t)opcode;
	DoCompare(env, _opcode);
}

uint64_t HELPER(GetTimeStamp)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->TimeStamp);
}

uint64_t HELPER(CodeCopy)(CPUPPDLState *env) {
	USEGAS(env, 0x3);
	return (uint64)( 0x0 );
}

uint64_t HELPER(BlockChainHash)(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	PushSingleBlockToStack(env, (uint64)( 0x0 ));
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetSingleBlockFromStack)(CPUPPDLState *env) {
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

uint64_t HELPER(GetCaller)(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->caller_addr;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( ca ));
	return (uint64)( 0x0 );
}

uint64_t HELPER(SwapOp)(CPUPPDLState *env, uint64_t count) {
	uint32_t i;
	uint32_t offs;
	uint64_t first_el;
	uint32_t _count = (uint32_t)count;
	first_el = env->stack_arr[(env->sp-0x3)];
	first_el = env->stack_arr[(env->sp-0x2)];
	first_el = env->stack_arr[(env->sp-0x1)];
	first_el = env->stack_arr[env->sp];
	for (i = 0x0; (i < 0x4); i = (i+0x1)) {
		offs = (env->sp-((0x4*(_count+0x1))+i));
		env->stack_arr[(env->sp-i)] = env->stack_arr[offs];
		env->stack_arr[offs] = first_el;
	}
}

uint64_t HELPER(CreateAccount)(CPUPPDLState *env) {
	USEGAS(env, 0x7D00);
	return (uint64)( 0x0 );
}

uint64_t HELPER(ExtCodeCopy)(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetNumber)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->Number);
}

uint64_t HELPER(GetBalance)(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetDifficulty)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->Difficulty);
}

uint64_t HELPER(GetAddress)(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->cur_addr;
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, (uint64)( ca ));
	return (uint64)( 0x0 );
}

uint64_t HELPER(MakeCallCode)(CPUPPDLState *env) {
	USEGAS(env, 0x28);
	return (uint64)( 0x0 );
}

uint64_t HELPER(PcOp)(CPUPPDLState *env) {
	uint32_t i;
	uint64_t data_tmp;
	uint64_t data_val;
	data_tmp = (uint64)( env->pc );
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

uint64_t HELPER(LogInst)(CPUPPDLState *env, uint64_t count, uint64_t log_ptr) {
	uint32_t i;
	uint32_t _count = (uint32_t)count;
	uint32_t _log_ptr = (uint32_t)log_ptr;
	for (i = 0x0; (i < _count); i = (i+0x1)) {
		env->log_bus[((_log_ptr+0x2)+_count)] = env->stack_arr[env->sp];
		env->sp = (env->sp-0x1);
	}
}

uint64_t HELPER(LoadFromStorageStub)(CPUPPDLState *env, uint64_t addr) {
	LoadFromStorage(env, addr);
}

uint64_t HELPER(GetCodeSize)(CPUPPDLState *env) {
	uint64_t elf_size;
	elf_size = GetElfSizeStub(env);
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, elf_size);
	return (uint64)( 0x0 );
}

uint64_t HELPER(PushSingleBlockToStack)(CPUPPDLState *env, uint64_t data_tmp) {
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

uint64_t HELPER(CallDataSize)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->inp_data_size);
	return (uint64)( 0x0 );
}

uint64_t HELPER(StopExec)(CPUPPDLState *env) {
	helper_error_message(env, 1, 0x0);
	result_message(env);
	exit(0);
}

uint64_t HELPER(GetCoinBase)(CPUPPDLState *env) {
	USEGAS(env, 0x2);
	PushSingleBlockToStack(env, env->CoinBase);
}

uint64_t HELPER(ExtCodeSize)(CPUPPDLState *env) {
	USEGAS(env, 0x14);
	PushSingleBlockToStack(env, env->ext_code_size);
	return (uint64)( 0x0 );
}

uint64_t HELPER(input_data_get)(CPUPPDLState *env, uint64_t index) {
	return env->input_data[index];
}

void HELPER(input_data_set)(CPUPPDLState *env, uint64_t index, uint64_t data) {
	env->input_data[index] = data;
}

uint64_t HELPER(log_bus_get)(CPUPPDLState *env, uint64_t index) {
	return env->log_bus[index];
}

void HELPER(log_bus_set)(CPUPPDLState *env, uint64_t index, uint64_t data) {
	env->log_bus[index] = data;
}

uint64_t HELPER(data_bus_get)(CPUPPDLState *env, uint64_t index) {
	return env->data_bus[index];
}

void HELPER(data_bus_set)(CPUPPDLState *env, uint64_t index, uint64_t data) {
	env->data_bus[index] = data;
}

uint64_t HELPER(gas_available_get)(CPUPPDLState *env, uint64_t index) {
	return env->gas_available[index];
}

void HELPER(gas_available_set)(CPUPPDLState *env, uint64_t index, uint64_t data) {
	env->gas_available[index] = data;
}

uint64_t HELPER(stack_arr_get)(CPUPPDLState *env, uint64_t index) {
	return env->stack_arr[index];
}

void HELPER(stack_arr_set)(CPUPPDLState *env, uint64_t index, uint64_t data) {
	env->stack_arr[index] = data;
}

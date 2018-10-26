#include "func_shared.h"
#include "functions.h"
#include "qemu-common.h"
#include "exec/cpu_ldst.h"
#include "bitfield.h"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

typedef uint64_t uint256;

uint64_t HELPER(MakeCall)(CPUPPDLState *env) {
	uint64_t inOff;
	uint64_t outSize;
	uint64_t call_res;
	uint64_t inSize;
	uint64_t outOff;
	uint64_t address;
	uint64_t callGas;
	uint64_t value;
	callGas = env->stack_arr[env->sp];
	address = env->stack_arr[(env->sp-0x1)];
	value = env->stack_arr[(env->sp-0x2)];
	inOff = env->stack_arr[(env->sp-0x3)];
	inSize = env->stack_arr[(env->sp-0x4)];
	outOff = env->stack_arr[(env->sp-0x5)];
	outSize = env->stack_arr[(env->sp-0x6)];
	call_res = 0x0;
	if ((env->gas_available < 0x28)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x28);
	}
	env->sp = (env->sp-0x6);
	env->stack_arr[env->sp] = call_res;
	return (uint64)( 0x0 );
}

uint64_t HELPER(EqOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a == b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetInputData)(CPUPPDLState *env) {
	uint32_t addr_val;
	uint64_t inp_data;
	addr_val = (uint32)( env->stack_arr[env->sp] );
	inp_data = env->input_data[addr_val];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->stack_arr[env->sp] = inp_data;
	return (uint64)( 0x0 );
}

uint64_t HELPER(SignExtend)(CPUPPDLState *env) {
	uint64_t a;
	uint32_t testBit;
	uint64_t b;
	uint32_t end_bit;
	uint64_t mask;
	uint64_t number;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	env->sp = (env->sp-0x1);
	if ((a < 0x1F)) {
		testBit = ((uint32)( (a*0x8) )+0x7);
		end_bit = (testBit+0x1);
		mask = (pd_lsh((uint64)( 0x1 ), testBit)-0x1);
		if ((get_bitfield(b, testBit, end_bit) == 0x1)) {
			number = (b|(~mask));
		} else {
			number = (b&mask);
		}
		env->stack_arr[env->sp] = number;
		return (uint64)( 0x0 );
	}
	env->stack_arr[env->sp] = (uint64)( 0x0 );
	return (uint64)( 0x0 );
}

uint64_t HELPER(AndOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a&b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GtOpS)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (int64)(a > (int64)b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(CallDataCopy)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t c;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	c = env->stack_arr[(env->sp-0x2)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x3);
	return (uint64)( 0x0 );
}

uint64_t HELPER(DelegateCall)(CPUPPDLState *env) {
	uint64_t inOff;
	uint64_t outSize;
	uint64_t call_res;
	uint64_t inSize;
	uint64_t outOff;
	uint64_t address;
	uint64_t callGas;
	callGas = env->stack_arr[env->sp];
	address = env->stack_arr[(env->sp-0x1)];
	inOff = env->stack_arr[(env->sp-0x2)];
	inSize = env->stack_arr[(env->sp-0x3)];
	outOff = env->stack_arr[(env->sp-0x4)];
	outSize = env->stack_arr[(env->sp-0x5)];
	call_res = 0x0;
	if ((env->gas_available < 0x28)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x28);
	}
	env->sp = (env->sp-0x5);
	env->stack_arr[env->sp] = call_res;
	return (uint64)( 0x0 );
}

uint64_t HELPER(StopOp)(CPUPPDLState *env) {
	if ((env->gas_available < 0x0)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x0);
	}
	helper_error_message(env, 1, 0x0);
	return (uint64)( 0x0 );
}

uint64_t HELPER(DivOpS)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	env->sp = (env->sp-0x1);
	if ((b == 0x0)) {
		env->stack_arr[env->sp] = (uint64)( 0x0 );
		return (uint64)( 0x0 );
	} else {
		env->stack_arr[env->sp] = (int64)(a/(int64)b);
		return (uint64)( 0x0 );
	}
}

uint64_t HELPER(GetModuleAdd)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t div;
	uint64_t b;
	uint64_t base;
	uint64_t mod;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	base = (a+b);
	mod = env->stack_arr[(env->sp-0x2)];
	if ((env->gas_available < 0x8)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x8);
	}
	env->sp = (env->sp-0x2);
	if ((mod == 0x0)) {
		env->stack_arr[env->sp] = (uint64)( 0x0 );
		return (uint64)( 0x0 );
	} else {
		div = (base/mod);
		env->stack_arr[env->sp] = (base-(div*mod));
		return (uint64)( 0x0 );
	}
}

uint64_t HELPER(MStoreInst)(CPUPPDLState *env, uint64_t addr_val) {
	uint32_t i;
	uint64_t data_tmp;
	uint64_t data_val;
	uint32_t init_shift;
	uint32_t _addr_val = (uint32_t)addr_val;
	data_val = env->stack_arr[env->sp];
	env->sp = (env->sp-0x1);
	init_shift = (0x1F*0x8);
	for (i = 0x0; (i < 0x20); i = (i+0x1)) {
		data_tmp = pd_rsh(data_val, init_shift);
		env->data_bus[_addr_val] = (uint8)( data_tmp );
		_addr_val = (_addr_val+0x1);
		init_shift = (init_shift-0x8);
	}
	if ((_addr_val > env->mem_size)) {
		env->mem_size = _addr_val;
	}
}

uint64_t HELPER(GtOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a > b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(SubOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a-b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(Return)(CPUPPDLState *env) {
	if ((env->gas_available < 0x0)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x0);
	}
	StopExec(env);
	return (uint64)( 0x0 );
}

uint64_t HELPER(LtOpS)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (int64)(a < (int64)b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(MloadInst)(CPUPPDLState *env, uint64_t addr_val) {
	uint32_t i;
	uint64_t data_tmp;
	uint64_t data_val;
	uint32_t init_shift;
	uint32_t _addr_val = (uint32_t)addr_val;
	data_val = 0x0;
	init_shift = 0x0;
	for (i = 0x0; (i < 0x20); i = (i+0x1)) {
		data_val = (pd_lsh(data_val, init_shift)|(uint64)( env->data_bus[_addr_val] ));
		_addr_val = (_addr_val+0x1);
		init_shift = (init_shift+0x8);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = data_val;
	return 0x0;
}

uint64_t HELPER(GetOrigin)(CPUPPDLState *env) {
	uint64_t oa;
	oa = env->origin_addr;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = (uint64)( oa );
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetModuleS)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t div;
	uint64_t sign;
	uint8_t is_signed;
	uint64_t mod;
	a = env->stack_arr[env->sp];
	mod = env->stack_arr[(env->sp-0x1)];
	is_signed = ((int64)a < 0x0);
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	env->sp = (env->sp-0x1);
	sign = (is_signed != 0x0) ? (uint64)( (0x0-0x1) ) : (uint64)( 0x1 );
	if ((mod == 0x0)) {
		env->stack_arr[env->sp] = (uint64)( 0x0 );
		return (uint64)( 0x0 );
	} else {
		div = (a/mod);
		env->stack_arr[env->sp] = (sign*(a-(div*mod)));
		return (uint64)( 0x0 );
	}
}

uint64_t HELPER(GetGasPrice)(CPUPPDLState *env) {
	uint64_t gp;
	gp = env->gas_price;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = (uint64)( gp );
	return (uint64)( 0x0 );
}

uint64_t HELPER(CallValue)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = (uint64)( 0x0 );
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetGasLimit)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->GasLimit;
	return (uint64)( 0x0 );
}

uint64_t HELPER(CodeCopy)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t c;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	c = env->stack_arr[(env->sp-0x2)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x3);
	return (uint64)( 0x0 );
}

uint64_t HELPER(ExtCodeCopy)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t c;
	uint64_t b;
	uint64_t d;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	c = env->stack_arr[(env->sp-0x2)];
	d = env->stack_arr[(env->sp-0x3)];
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	env->sp = (env->sp-0x4);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetTimeStamp)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->TimeStamp;
	return (uint64)( 0x0 );
}

uint64_t HELPER(PushInst)(CPUPPDLState *env, uint64_t cnt) {
	uint32_t i;
	uint64_t a;
	uint64_t tmp;
	uint32_t _cnt = (uint32_t)cnt;
	a = 0x0;
	for (i = 0x0; (i < _cnt); i = (i+0x1)) {
		tmp = (helper_mem_ld8(env, ((env->pc+i)+0x1))&0xFF);
		a = (pd_lsh(a, 0x8)|tmp);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = a;
	return 0x0;
}

uint64_t HELPER(GetModuleMul)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t div;
	uint64_t b;
	uint64_t base;
	uint64_t mod;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	base = (a*b);
	mod = env->stack_arr[(env->sp-0x2)];
	if ((env->gas_available < 0x8)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x8);
	}
	env->sp = (env->sp-0x2);
	if ((mod == 0x0)) {
		env->stack_arr[env->sp] = (uint64)( 0x0 );
		return (uint64)( 0x0 );
	} else {
		div = (base/mod);
		env->stack_arr[env->sp] = (base-(div*mod));
		return (uint64)( 0x0 );
	}
}

uint64_t HELPER(XorOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a^b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(BlockChainHash)(CPUPPDLState *env) {
	uint64_t a;
	a = env->stack_arr[env->sp];
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	env->CoinBase = 0x10;
	env->TimeStamp = 0x1000;
	env->Number = 0x1234543234;
	env->Difficulty = 0x420323;
	env->GasLimit = 0x1000;
	env->stack_arr[env->sp] = (uint64)( 0x0 );
	return (uint64)( 0x0 );
}

uint64_t HELPER(AddOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a+b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(OrOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a|b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(CreateAccount)(CPUPPDLState *env) {
	uint64_t initSize;
	uint64_t initOff;
	uint64_t endowment;
	uint64_t account;
	endowment = env->stack_arr[env->sp];
	initOff = env->stack_arr[(env->sp-0x1)];
	initSize = env->stack_arr[(env->sp-0x2)];
	if ((env->gas_available < 0x7D00)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x7D00);
	}
	account = 0x123456;
	env->sp = (env->sp-0x2);
	env->stack_arr[env->sp] = account;
	return (uint64)( 0x0 );
}

uint64_t HELPER(MulOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a*b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetNumber)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->Number;
	return (uint64)( 0x0 );
}

uint64_t HELPER(IsZeroOp)(CPUPPDLState *env) {
	uint64_t a;
	a = env->stack_arr[env->sp];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->stack_arr[env->sp] = (a == 0x0);
	return (uint64)( 0x0 );
}

uint64_t HELPER(LtOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = (a < b);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetBalance)(CPUPPDLState *env) {
	uint64_t a;
	a = env->stack_arr[env->sp];
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	env->stack_arr[env->sp] = (uint64)( 0x0 );
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetElfSize)(CPUPPDLState *env) {
}

uint64_t HELPER(GetAddress)(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->cur_addr;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = (uint64)( ca );
	return (uint64)( 0x0 );
}

uint64_t HELPER(NotOp)(CPUPPDLState *env) {
	uint64_t a;
	a = env->stack_arr[env->sp];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->stack_arr[env->sp] = (~a);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetDifficulty)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->Difficulty;
	return (uint64)( 0x0 );
}

uint64_t HELPER(Push)(CPUPPDLState *env, uint64_t val) {
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = val;
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

uint64_t HELPER(KeccakAlg)(CPUPPDLState *env, uint64_t offs, uint64_t size) {
	uint32_t _offs = (uint32_t)offs;
	uint32_t _size = (uint32_t)size;
}

uint64_t HELPER(GetCodeSize)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = GetElfSize(env);
	return (uint64)( 0x0 );
}

uint64_t HELPER(MakeCallCode)(CPUPPDLState *env) {
	uint64_t inOff;
	uint64_t outSize;
	uint64_t call_res;
	uint64_t inSize;
	uint64_t outOff;
	uint64_t address;
	uint64_t callGas;
	uint64_t value;
	callGas = env->stack_arr[env->sp];
	address = env->stack_arr[(env->sp-0x1)];
	value = env->stack_arr[(env->sp-0x2)];
	inOff = env->stack_arr[(env->sp-0x3)];
	inSize = env->stack_arr[(env->sp-0x4)];
	outOff = env->stack_arr[(env->sp-0x5)];
	outSize = env->stack_arr[(env->sp-0x6)];
	call_res = 0x0;
	if ((env->gas_available < 0x28)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x28);
	}
	env->sp = (env->sp-0x6);
	env->stack_arr[env->sp] = call_res;
	return (uint64)( 0x0 );
}

uint64_t HELPER(SaveToStorage)(CPUPPDLState *env, uint64_t offs, uint64_t value) {
	uint32_t _offs = (uint32_t)offs;
}

uint64_t HELPER(Pop)(CPUPPDLState *env) {
	uint64_t ret;
	ret = env->stack_arr[env->sp];
	env->sp = (env->sp-0x1);
	return ret;
}

uint64_t HELPER(CallDataSize)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->inp_data_size;
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetCaller)(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->caller_addr;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = (uint64)( ca );
	return (uint64)( 0x0 );
}

uint64_t HELPER(LoadFromStorage)(CPUPPDLState *env, uint64_t offs) {
	uint32_t _offs = (uint32_t)offs;
}

uint64_t HELPER(StopExec)(CPUPPDLState *env) {
	helper_error_message(env, 1, 0x0);
	result_message(env);
	exit(0);
}

uint64_t HELPER(GetModule)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t div;
	uint64_t mod;
	a = env->stack_arr[env->sp];
	mod = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	env->sp = (env->sp-0x1);
	if ((mod == 0x0)) {
		env->stack_arr[env->sp] = (uint64)( 0x0 );
		return (uint64)( 0x0 );
	} else {
		div = (a/mod);
		env->stack_arr[env->sp] = (a-(div*mod));
		return (uint64)( 0x0 );
	}
}

uint64_t HELPER(ByteFromWord)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	uint32_t end_bit;
	uint32_t start_bit;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	start_bit = (uint32)( ((0x1F-a)*0x8) );
	end_bit = (start_bit+0x7);
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = get_bitfield(b, start_bit, end_bit);
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetCoinBase)(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->CoinBase;
	return (uint64)( 0x0 );
}

uint64_t HELPER(DivOp)(CPUPPDLState *env) {
	uint64_t a;
	uint64_t b;
	a = env->stack_arr[env->sp];
	b = env->stack_arr[(env->sp-0x1)];
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	env->sp = (env->sp-0x1);
	if ((b == 0x0)) {
		env->stack_arr[env->sp] = (uint64)( 0x0 );
		return (uint64)( 0x0 );
	} else {
		env->stack_arr[env->sp] = (a/b);
		return (uint64)( 0x0 );
	}
}

uint64_t HELPER(ExtCodeSize)(CPUPPDLState *env) {
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	env->sp = (env->sp+0x1);
	env->stack_arr[env->sp] = env->ext_code_size;
	return (uint64)( 0x0 );
}

uint64_t HELPER(GetExp)(CPUPPDLState *env) {
	uint64_t i;
	uint64_t pow;
	uint64_t base;
	uint64_t res;
	base = env->stack_arr[env->sp];
	pow = env->stack_arr[(env->sp-0x1)];
	res = 0x1;
	if ((env->gas_available < 0xA)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0xA);
	}
	for (i = 0x0; (i < pow); i = (i+0x1)) {
		res = (res*base);
	}
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = res;
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

uint64_t HELPER(stack_arr_get)(CPUPPDLState *env, uint64_t index) {
	return env->stack_arr[index];
}

void HELPER(stack_arr_set)(CPUPPDLState *env, uint64_t index, uint64_t data) {
	env->stack_arr[index] = data;
}

#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "func_shared.h"

uint64_t MakeCall(CPUPPDLState *env) {
	uint64_t inOff;
	uint64_t outSize;
	uint64_t call_res;
	uint64_t inSize;
	uint64_t outOff;
	uint64_t address;
	uint64_t callGas;
	uint64_t value;
	callGas = Pop(env);
	address = Pop(env);
	value = Pop(env);
	inOff = Pop(env);
	inSize = Pop(env);
	outOff = Pop(env);
	outSize = Pop(env);
	call_res = 0x0;
	if ((env->gas_available < 0x28)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x28);
	}
	return call_res;
}

uint64_t EqOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a == b);
}

uint64_t GetInputData(CPUPPDLState *env) {
	uint32_t addr_val;
	uint64_t inp_data;
	addr_val = (uint32)( Pop(env) );
	inp_data = env->input_data[addr_val];
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return inp_data;
}

uint64_t SignExtend(CPUPPDLState *env, uint64_t a, uint64_t b) {
	uint64_t mask;
	uint32_t testBit;
	uint32_t end_bit;
	uint64_t number;
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	if ((a < 0x1F)) {
		testBit = ((uint32)( (a*0x8) )+0x7);
		end_bit = (testBit+0x1);
		mask = (pd_lsh((uint256)( 0x1 ), testBit)-0x1);
		if ((get_bitfield(b, testBit, end_bit) == 0x1)) {
			number = (b|(~mask));
		} else {
			number = (b&mask);
		}
		return number;
	}
	return (uint256)( 0x0 );
}

uint64_t AndOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a&b);
}

uint64_t GtOpS(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (int64)(a > (int64)b);
}

uint64_t CallDataCopy(CPUPPDLState *env, uint64_t a, uint64_t b, uint64_t c) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (uint256)( 0x0 );
}

uint64_t DelegateCall(CPUPPDLState *env) {
	uint64_t inOff;
	uint64_t outSize;
	uint64_t call_res;
	uint64_t inSize;
	uint64_t outOff;
	uint64_t address;
	uint64_t callGas;
	callGas = Pop(env);
	address = Pop(env);
	inOff = Pop(env);
	inSize = Pop(env);
	outOff = Pop(env);
	outSize = Pop(env);
	call_res = 0x0;
	if ((env->gas_available < 0x28)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x28);
	}
	return call_res;
}

uint64_t StopOp(CPUPPDLState *env) {
	if ((env->gas_available < 0x0)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x0);
	}
    printf("---\n");
	helper_error_message(env, 1, 0x0);
	return (uint256)( 0x0 );
}

uint64_t DivOpS(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	if ((b == 0x0)) {
		return 0x0;
	} else {
		return (int64)(a/(int64)b);
	}
}

uint64_t GetModuleAM(CPUPPDLState *env, uint64_t a, uint64_t mod) {
	uint64_t div;
	if ((env->gas_available < 0x8)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x8);
	}
	if ((mod == 0x0)) {
		return (uint256)( 0x0 );
	} else {
		div = (a/mod);
		return (a-(div*mod));
	}
}

uint64_t GtOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a > b);
}

uint64_t SubOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a-b);
}

uint64_t Return(CPUPPDLState *env) {
	if ((env->gas_available < 0x0)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x0);
	}
	StopExec(env);
	return (uint256)( 0x0 );
}

uint64_t LtOpS(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (int64)(a < (int64)b);
}

uint64_t GetOrigin(CPUPPDLState *env) {
	uint64_t oa;
	oa = env->origin_addr;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return (uint256)( oa );
}

uint64_t GetModuleS(CPUPPDLState *env, uint64_t a, uint64_t mod) {
	uint64_t div;
	uint8_t is_signed;
	uint64_t sign;
	is_signed = ((int64)a < 0x0);
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	sign = (is_signed != 0x0) ? (uint256)( (0x0-0x1) ) : (uint256)( 0x1 );
	if ((mod == 0x0)) {
		return 0x0;
	} else {
		div = (a/mod);
		return (sign*(a-(div*mod)));
	}
}

uint64_t GetGasPrice(CPUPPDLState *env) {
	uint32_t gp;
	gp = env->gas_price;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return (uint256)( gp );
}

uint64_t CallValue(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return (uint256)( 0x0 );
}

uint64_t GetGasLimit(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return env->GasLimit;
}

uint64_t CodeCopy(CPUPPDLState *env, uint64_t a, uint64_t b, uint64_t c) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (uint256)( 0x0 );
}

uint64_t ExtCodeCopy(CPUPPDLState *env, uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	return (uint256)( 0x0 );
}

uint64_t GetTimeStamp(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return env->TimeStamp;
}

uint64_t XorOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a^b);
}

uint64_t BlockChainHash(CPUPPDLState *env, uint64_t a) {
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
	return (uint256)( 0x0 );
}

uint64_t AddOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a+b);
}

uint64_t OrOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a|b);
}

uint64_t CreateAccount(CPUPPDLState *env, uint64_t endowment, uint64_t initOff, uint64_t initSize) {
	uint64_t account;
	if ((env->gas_available < 0x7D00)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x7D00);
	}
	account = 0x123456;
	return account;
}

uint64_t MulOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	return (a*b);
}

uint64_t GetNumber(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return env->Number;
}

uint64_t IsZeroOp(CPUPPDLState *env, uint64_t a) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a == 0x0);
}

uint64_t LtOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (a < b);
}

uint64_t GetBalance(CPUPPDLState *env, uint64_t a) {
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	return (uint256)( 0x0 );
}

uint64_t GetElfSize(CPUPPDLState *env) {
}

uint64_t GetAddress(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->cur_addr;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return (uint256)( ca );
}

uint64_t NotOp(CPUPPDLState *env, uint64_t a) {
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return (~a);
}

uint64_t GetDifficulty(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return env->Difficulty;
}

uint64_t Push(CPUPPDLState *env, uint64_t val) {
	env->sp = (env->sp-0x1);
	env->stack_arr[env->sp] = val;
}

uint64_t GetCodeSize(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return GetElfSize(env);
}

uint64_t MakeCallCode(CPUPPDLState *env) {
	uint64_t inOff;
	uint64_t outSize;
	uint64_t call_res;
	uint64_t inSize;
	uint64_t outOff;
	uint64_t address;
	uint64_t callGas;
	uint64_t value;
	callGas = Pop(env);
	address = Pop(env);
	value = Pop(env);
	inOff = Pop(env);
	inSize = Pop(env);
	outOff = Pop(env);
	outSize = Pop(env);
	call_res = 0x0;
	if ((env->gas_available < 0x28)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x28);
	}
	return call_res;
}

uint64_t Pop(CPUPPDLState *env) {
	uint64_t ret;
	ret = env->stack_arr[env->sp];
	env->sp = (env->sp+0x1);
	return ret;
}

uint64_t CallDataSize(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return env->inp_data_size;
}

uint64_t GetCaller(CPUPPDLState *env) {
	uint64_t ca;
	ca = env->caller_addr;
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return (uint256)( ca );
}

uint64_t StopExec(CPUPPDLState *env) {
	helper_error_message(env, 1, 0x0);
    if ((signed)(env->gas_available) == -1) {
      printf("\ngas limit error\n");
      exit(-1);
    }

    int32 offs = (int32)Pop(env);
    int32 size = (int32)Pop(env);
    int i;
    printf("0x");
    for (i = 0; i < size; i++) {
        printf("%02X", env->data_bus[i + offs]);
    }
    printf("\n");
	exit(0);
}

uint64_t GetModule(CPUPPDLState *env, uint64_t a, uint64_t mod) {
	uint64_t div;
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	if ((mod == 0x0)) {
		return 0x0;
	} else {
		div = (a/mod);
		return (a-(div*mod));
	}
}

uint64_t ByteFromWord(CPUPPDLState *env, uint64_t a, uint64_t b) {
	uint32_t end_bit;
	uint32_t start_bit;
	start_bit = (uint32)( ((0x1F-a)*0x8) );
	end_bit = (start_bit+0x7);
	if ((env->gas_available < 0x3)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x3);
	}
	return get_bitfield(b, start_bit, end_bit);
}

uint64_t GetCoinBase(CPUPPDLState *env) {
	if ((env->gas_available < 0x2)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x2);
	}
	return env->CoinBase;
}

uint64_t DivOp(CPUPPDLState *env, uint64_t a, uint64_t b) {
	if ((env->gas_available < 0x5)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x5);
	}
	if ((b == 0x0)) {
		return 0x0;
	} else {
		return (a/b);
	}
}

uint64_t ExtCodeSize(CPUPPDLState *env) {
	if ((env->gas_available < 0x14)) {
		env->gas_available = 0xFFFFFFFF;
		StopExec(env);
	} else {
		env->gas_available = (env->gas_available-0x14);
	}
	return env->ext_code_size;
}

uint64_t GetExp(CPUPPDLState *env, uint64_t base, uint64_t pow) {
	uint64_t i;
	uint64_t res;
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
	return res;
}

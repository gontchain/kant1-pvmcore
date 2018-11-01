#include "cpu.h"
#include "qemu/trace.h"
#pragma GCC diagnostic ignored "-Wformat="

#ifdef CONFIG_SOFTMMU
extern uint64_t elf_entry;
#ifdef EVM
extern uint64_t gas;
extern uint64_t end_pc;
#endif
#endif

void RESET(CPUPPDLState *env) {
	int i;
	#ifdef CONFIG_USER_ONLY
	env->pc = 0x0;
	#else
	env->pc = elf_entry;
	#endif
	#ifdef EVM
	env->gas_available[0] = gas;
	env->GasLimit = gas;
	env->elfSize = end_pc;
	#endif
	env->sp = (0x0-0x1);
	env->log_ptr = 0x0;
	for (env->counter = 0x0; (env->counter < 0x400); env->counter = (env->counter+0x1)) {
		env->data_bus[env->counter] = 0x0;
	}
	saveState(&envSaved, env);
	initialize();
}

void OPER(CPUPPDLState *env) {
	int i;
	#ifdef CONFIG_USER_ONLY
	env->pc = 0x0;
	#else
	env->pc = elf_entry;
	#endif
	#ifdef EVM
	env->gas_available[0] = gas;
	env->GasLimit = gas;
	env->elfSize = end_pc;
	#endif
	env->sp = (0x0-0x1);
	env->log_ptr = 0x0;
	for (env->counter = 0x0; (env->counter < 0x400); env->counter = (env->counter+0x1)) {
		env->data_bus[env->counter] = 0x0;
	}
	saveState(&envSaved, env);
	initialize();
}

void saveState(CPUPPDLState *out, CPUPPDLState *in) {
	int i;
	out->pc = in->pc;
	out->cur_addr = in->cur_addr;
	out->caller_addr = in->caller_addr;
	out->origin_addr = in->origin_addr;
	out->gas_price = in->gas_price;
	out->ext_code_size = in->ext_code_size;
	out->inp_data_size = in->inp_data_size;
	out->log_ptr = in->log_ptr;
	out->sp = in->sp;
	for (i = 0; i < 4; i++) {
		out->gas_available[i] = in->gas_available[i];
	}
	for (i = 0; i < 1024; i++) {
		out->data_bus[i] = in->data_bus[i];
	}
	for (i = 0; i < 2048; i++) {
		out->stack_arr[i] = in->stack_arr[i];
	}
	out->CoinBase = in->CoinBase;
	out->TimeStamp = in->TimeStamp;
	out->Number = in->Number;
	out->Difficulty = in->Difficulty;
	out->GasLimit = in->GasLimit;
}

void compareState(CPUPPDLState *stateBefore, CPUPPDLState *state) {
	int i;
	if ((stateBefore->pc != state->pc) && qemu_reg_mask("pc", -1)) {
		if (use_regtracer) printf("pc: %016lx -> %016lx\n", stateBefore->pc, state->pc);
	}
	if ((stateBefore->cur_addr != state->cur_addr) && qemu_reg_mask("cur_addr", -1)) {
		if (use_regtracer) printf("cur_addr: %016lx -> %016lx\n", stateBefore->cur_addr, state->cur_addr);
		if (use_ctracer)   printf("cur_addr = %016lx\n", state->cur_addr);
	}
	if ((stateBefore->caller_addr != state->caller_addr) && qemu_reg_mask("caller_addr", -1)) {
		if (use_regtracer) printf("caller_addr: %016lx -> %016lx\n", stateBefore->caller_addr, state->caller_addr);
		if (use_ctracer)   printf("caller_addr = %016lx\n", state->caller_addr);
	}
	if ((stateBefore->origin_addr != state->origin_addr) && qemu_reg_mask("origin_addr", -1)) {
		if (use_regtracer) printf("origin_addr: %016lx -> %016lx\n", stateBefore->origin_addr, state->origin_addr);
		if (use_ctracer)   printf("origin_addr = %016lx\n", state->origin_addr);
	}
	if ((stateBefore->gas_price != state->gas_price) && qemu_reg_mask("gas_price", -1)) {
		if (use_regtracer) printf("gas_price: %016lx -> %016lx\n", stateBefore->gas_price, state->gas_price);
		if (use_ctracer)   printf("gas_price = %016lx\n", state->gas_price);
	}
	if ((stateBefore->ext_code_size != state->ext_code_size) && qemu_reg_mask("ext_code_size", -1)) {
		if (use_regtracer) printf("ext_code_size: %016lx -> %016lx\n", stateBefore->ext_code_size, state->ext_code_size);
		if (use_ctracer)   printf("ext_code_size = %016lx\n", state->ext_code_size);
	}
	if ((stateBefore->inp_data_size != state->inp_data_size) && qemu_reg_mask("inp_data_size", -1)) {
		if (use_regtracer) printf("inp_data_size: %016lx -> %016lx\n", stateBefore->inp_data_size, state->inp_data_size);
		if (use_ctracer)   printf("inp_data_size = %016lx\n", state->inp_data_size);
	}
	if ((stateBefore->log_ptr != state->log_ptr) && qemu_reg_mask("log_ptr", -1)) {
		if (use_regtracer) printf("log_ptr: %016lx -> %016lx\n", stateBefore->log_ptr, state->log_ptr);
		if (use_ctracer)   printf("log_ptr = %016lx\n", state->log_ptr);
	}
	if ((stateBefore->sp != state->sp) && qemu_reg_mask("sp", -1)) {
		if (use_regtracer) printf("sp%d: %016lx -> %016lx\n", i, stateBefore->sp, state->sp);
		if (use_ctracer)   printf("sp = %016lx\n", state->sp);
	}
	for (i = 0; i < 4; i++) {
		if ((stateBefore->gas_available[i] != state->gas_available[i])  && qemu_reg_mask("gas_available", i)) {
			if (use_regtracer) printf("gas_available%d: %016lx -> %016lx\n", i, stateBefore->gas_available[i], state->gas_available[i]);
			if (use_ctracer)   printf("gas_available%d = %016lx\n", i, state->gas_available[i]);
		}
	}
	for (i = 0; i < 1024; i++) {
		if ((stateBefore->data_bus[i] != state->data_bus[i])  && qemu_reg_mask("data_bus", i)) {
			if (use_regtracer) printf("data_bus%d: %016lx -> %016lx\n", i, stateBefore->data_bus[i], state->data_bus[i]);
			if (use_ctracer)   printf("data_bus%d = %016lx\n", i, state->data_bus[i]);
		}
	}
	for (i = 0; i < 2048; i++) {
		if ((stateBefore->stack_arr[i] != state->stack_arr[i])  && qemu_reg_mask("stack_arr", i)) {
			if (use_regtracer) printf("stack_arr%d: %016lx -> %016lx\n", i, stateBefore->stack_arr[i], state->stack_arr[i]);
			if (use_ctracer)   printf("stack_arr%d = %016lx\n", i, state->stack_arr[i]);
		}
	}
	if ((stateBefore->CoinBase != state->CoinBase) && qemu_reg_mask("CoinBase", -1)) {
		if (use_regtracer) printf("CoinBase%d: %016lx -> %016lx\n", i, stateBefore->CoinBase, state->CoinBase);
		if (use_ctracer)   printf("CoinBase = %016lx\n", state->CoinBase);
	}
	if ((stateBefore->TimeStamp != state->TimeStamp) && qemu_reg_mask("TimeStamp", -1)) {
		if (use_regtracer) printf("TimeStamp%d: %016lx -> %016lx\n", i, stateBefore->TimeStamp, state->TimeStamp);
		if (use_ctracer)   printf("TimeStamp = %016lx\n", state->TimeStamp);
	}
	if ((stateBefore->Number != state->Number) && qemu_reg_mask("Number", -1)) {
		if (use_regtracer) printf("Number%d: %016lx -> %016lx\n", i, stateBefore->Number, state->Number);
		if (use_ctracer)   printf("Number = %016lx\n", state->Number);
	}
	if ((stateBefore->Difficulty != state->Difficulty) && qemu_reg_mask("Difficulty", -1)) {
		if (use_regtracer) printf("Difficulty%d: %016lx -> %016lx\n", i, stateBefore->Difficulty, state->Difficulty);
		if (use_ctracer)   printf("Difficulty = %016lx\n", state->Difficulty);
	}
	if ((stateBefore->GasLimit != state->GasLimit) && qemu_reg_mask("GasLimit", -1)) {
		if (use_regtracer) printf("GasLimit%d: %016lx -> %016lx\n", i, stateBefore->GasLimit, state->GasLimit);
		if (use_ctracer)   printf("GasLimit = %016lx\n", state->GasLimit);
	}
}

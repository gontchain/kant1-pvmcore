#include "cpu.h"
#include "qemu/trace.h"
#pragma GCC diagnostic ignored "-Wformat="

#ifdef CONFIG_SOFTMMU
extern uint64_t elf_entry;
#ifdef EVM
extern uint64_t gas;
extern uint64_t data_bus[1024];
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
	env->gas_available = gas;
	env->GasLimit = gas;
	for (i = 0; i < 1024; i++) {
		env->data_bus[i] = data_bus[i];
	}
	#endif
	env->sp = 0x800;
	env->log_ptr = 0x0;
	saveState(&envSaved, env);
}

void OPER(CPUPPDLState *env) {
	int i;
	#ifdef CONFIG_USER_ONLY
	env->pc = 0x0;
	#else
	env->pc = elf_entry;
	#endif
	#ifdef EVM
	env->gas_available = gas;
	env->GasLimit = gas;
	for (i = 0; i < 1024; i++) {
		env->data_bus[i] = data_bus[i];
	}
	#endif
	env->sp = 0x800;
	env->log_ptr = 0x0;
	saveState(&envSaved, env);
}

void saveState(CPUPPDLState *out, CPUPPDLState *in) {
	int i;
	out->gas_price = in->gas_price;
	out->log_ptr = in->log_ptr;
	out->cur_addr = in->cur_addr;
	out->origin_addr = in->origin_addr;
	out->pc = in->pc;
	out->caller_addr = in->caller_addr;
	out->inp_data_size = in->inp_data_size;
	out->ext_code_size = in->ext_code_size;
	out->TimeStamp = in->TimeStamp;
	out->sp = in->sp;
	out->GasLimit = in->GasLimit;
	out->Number = in->Number;
	out->Difficulty = in->Difficulty;
	out->gas_available = in->gas_available;
	out->CoinBase = in->CoinBase;
	for (i = 0; i < 1024; i++) {
		out->data_bus[i] = in->data_bus[i];
	}
}

void compareState(CPUPPDLState *stateBefore, CPUPPDLState *state) {
	int i;
	if ((stateBefore->gas_price != state->gas_price) && qemu_reg_mask("gas_price", -1)) {
		if (use_regtracer) printf("gas_price: %08lx -> %08lx\n", stateBefore->gas_price, state->gas_price);
		if (use_ctracer)   printf("gas_price = %08lx\n", state->gas_price);
	}
	if ((stateBefore->log_ptr != state->log_ptr) && qemu_reg_mask("log_ptr", -1)) {
		if (use_regtracer) printf("log_ptr: %08lx -> %08lx\n", stateBefore->log_ptr, state->log_ptr);
		if (use_ctracer)   printf("log_ptr = %08lx\n", state->log_ptr);
	}
	if ((stateBefore->cur_addr != state->cur_addr) && qemu_reg_mask("cur_addr", -1)) {
		if (use_regtracer) printf("cur_addr: %08lx -> %08lx\n", stateBefore->cur_addr, state->cur_addr);
		if (use_ctracer)   printf("cur_addr = %08lx\n", state->cur_addr);
	}
	if ((stateBefore->origin_addr != state->origin_addr) && qemu_reg_mask("origin_addr", -1)) {
		if (use_regtracer) printf("origin_addr: %08lx -> %08lx\n", stateBefore->origin_addr, state->origin_addr);
		if (use_ctracer)   printf("origin_addr = %08lx\n", state->origin_addr);
	}
	if ((stateBefore->pc != state->pc) && qemu_reg_mask("pc", -1)) {
		if (use_regtracer) printf("pc: %08lx -> %08lx\n", stateBefore->pc, state->pc);
	}
	if ((stateBefore->caller_addr != state->caller_addr) && qemu_reg_mask("caller_addr", -1)) {
		if (use_regtracer) printf("caller_addr: %08lx -> %08lx\n", stateBefore->caller_addr, state->caller_addr);
		if (use_ctracer)   printf("caller_addr = %08lx\n", state->caller_addr);
	}
	if ((stateBefore->inp_data_size != state->inp_data_size) && qemu_reg_mask("inp_data_size", -1)) {
		if (use_regtracer) printf("inp_data_size: %08lx -> %08lx\n", stateBefore->inp_data_size, state->inp_data_size);
		if (use_ctracer)   printf("inp_data_size = %08lx\n", state->inp_data_size);
	}
	if ((stateBefore->ext_code_size != state->ext_code_size) && qemu_reg_mask("ext_code_size", -1)) {
		if (use_regtracer) printf("ext_code_size: %08lx -> %08lx\n", stateBefore->ext_code_size, state->ext_code_size);
		if (use_ctracer)   printf("ext_code_size = %08lx\n", state->ext_code_size);
	}
	if ((stateBefore->TimeStamp != state->TimeStamp) && qemu_reg_mask("TimeStamp", -1)) {
		if (use_regtracer) printf("TimeStamp%d: %08lx -> %08lx\n", i, stateBefore->TimeStamp, state->TimeStamp);
		if (use_ctracer)   printf("TimeStamp%d = %08lx\n", i, state->TimeStamp);
	}
	if ((stateBefore->sp != state->sp) && qemu_reg_mask("sp", -1)) {
		if (use_regtracer) printf("sp%d: %08lx -> %08lx\n", i, stateBefore->sp, state->sp);
		if (use_ctracer)   printf("sp%d = %08lx\n", i, state->sp);
	}
	if ((stateBefore->GasLimit != state->GasLimit) && qemu_reg_mask("GasLimit", -1)) {
		if (use_regtracer) printf("GasLimit%d: %08lx -> %08lx\n", i, stateBefore->GasLimit, state->GasLimit);
		if (use_ctracer)   printf("GasLimit%d = %08lx\n", i, state->GasLimit);
	}
	if ((stateBefore->Number != state->Number) && qemu_reg_mask("Number", -1)) {
		if (use_regtracer) printf("Number%d: %08lx -> %08lx\n", i, stateBefore->Number, state->Number);
		if (use_ctracer)   printf("Number%d = %08lx\n", i, state->Number);
	}
	if ((stateBefore->Difficulty != state->Difficulty) && qemu_reg_mask("Difficulty", -1)) {
		if (use_regtracer) printf("Difficulty%d: %08lx -> %08lx\n", i, stateBefore->Difficulty, state->Difficulty);
		if (use_ctracer)   printf("Difficulty%d = %08lx\n", i, state->Difficulty);
	}
	if ((stateBefore->gas_available != state->gas_available) && qemu_reg_mask("gas_available", -1)) {
		if (use_regtracer) printf("gas_available%d: %08lx -> %08lx\n", i, stateBefore->gas_available, state->gas_available);
		if (use_ctracer)   printf("gas_available%d = %08lx\n", i, state->gas_available);
	}
	if ((stateBefore->CoinBase != state->CoinBase) && qemu_reg_mask("CoinBase", -1)) {
		if (use_regtracer) printf("CoinBase%d: %08lx -> %08lx\n", i, stateBefore->CoinBase, state->CoinBase);
		if (use_ctracer)   printf("CoinBase%d = %08lx\n", i, state->CoinBase);
	}
	for (i = 0; i < 1024; i++) {
		if ((stateBefore->data_bus[i] != state->data_bus[i])  && qemu_reg_mask("data_bus", i)) {
			if (use_regtracer) printf("data_bus%d: %08lx -> %08lx\n", i, stateBefore->data_bus[i], state->data_bus[i]);
			if (use_ctracer)   printf("data_bus%d = %08lx\n", i, state->data_bus[i]);
		}
	}
}

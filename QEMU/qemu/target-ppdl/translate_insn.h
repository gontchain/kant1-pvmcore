#ifndef PPDL_INSN_H
#define PPDL_INSN_H
#include "cpu.h"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wformat-zero-length"

#if defined(CONFIG_DEBUG)
#   define ERROR_PRINT(...) (debug) ? printf("	::GEN ERROR:: error in " __VA_ARGS__ "\n") : printf("");
#   define INFO_PRINT(...) (debug) ? printf("	::GEN INFO:: " __VA_ARGS__ ) : printf("");
#else
#   define ERROR_PRINT(...)
#   define INFO_PRINT(...)
#endif

void genBlock_Main(CPUPPDLState *env, uint64_t insn, target_ulong pc) {
	/*
	 * $syscall
	 */
	if (( insn & 0xf0 ) == 0xf0) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0xf0 mask: 0xf0\n");
		uint8_t syscall = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_syscall = tcg_const_local_tl(syscall);
		// LST
		gen_helper_SystemOps(nores, cpu_env, tcg_syscall);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * STATICCALL
	 */
	if (( insn & 0xff ) == 0xfa) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0xfa mask: 0xff\n");
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x28));
		tcg_temp_free( nores );
		return;
	}
	/*
	 * REVERT
	 */
	if (( insn & 0xff ) == 0xfd) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0xfd mask: 0xff\n");
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x0));
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * SUICIDE
	 */
	if (( insn & 0xff ) == 0xff) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0xff mask: 0xff\n");
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x0));
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * $gas_opcode
	 */
	if (( insn & 0xf0 ) == 0x40) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x40 mask: 0xf0\n");
		uint8_t gas_opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_gas_opcode = tcg_const_local_tl(gas_opcode);
		// LST
		gen_helper_BlockChain(nores, cpu_env, tcg_gas_opcode);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x30) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x30 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// LST
		gen_helper_AccountsData(nores, cpu_env, tcg_opcode);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * PUSH$count
	 */
	if (( insn & 0xe0 ) == 0x60) {
		TCGv nores = tcg_temp_new();
		TCGv res_l_1 = tcg_temp_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv res_l_2 = tcg_temp_new();
		TCGv res_in_call1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x60 mask: 0xe0\n");
		uint8_t count = extract32((uint32_t)insn, 0, 5);
		TCGv tcg_count = tcg_const_local_tl(count);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x3));
		// CALL
		tcg_gen_addi_tl(res_in_call1, tcg_count, 0x1);
		gen_helper_PushInst(nores, cpu_env, res_in_call1);
		changed_pc = 1;
		tcg_gen_movi_tl(cpu_is_pc_const_changed, 0x1);
		tcg_gen_mov_tl(nores, cpu_is_pc_const_changed);
		tcg_gen_add_tl(res_l_2, cpu_pc, tcg_count);
		tcg_gen_addi_tl(res_r_1, res_l_2, 0x2);
		tcg_gen_mov_tl(cpu_pc, res_r_1);
		tcg_gen_mov_tl(nores, cpu_pc);
		tcg_temp_free( nores );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( res_in_call1 );
		return;
	}
	/*
	 * DUP$count
	 */
	if (( insn & 0xf0 ) == 0x80) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x80 mask: 0xf0\n");
		uint8_t count = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_count = tcg_const_local_tl(count);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x3));
		// CALL
		gen_helper_DupOp(nores, cpu_env, tcg_count);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * SWAP$count
	 */
	if (( insn & 0xf0 ) == 0x90) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x90 mask: 0xf0\n");
		uint8_t count = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_count = tcg_const_local_tl(count);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x3));
		// CALL
		gen_helper_SwapOp(nores, cpu_env, tcg_count);
		tcg_temp_free( nores );
		return;
	}
	/*
	 * LOG$count
	 */
	if (( insn & 0xf8 ) == 0xa0) {
		TCGv nores = tcg_temp_new();
		TCGv res_r_2 = tcg_temp_new();
		TCGv res_in_call1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0xa0 mask: 0xf8\n");
		uint8_t count = extract32((uint32_t)insn, 0, 3);
		TCGv tcg_count = tcg_const_local_tl(count);
		// CALL
		tcg_gen_muli_tl(res_r_2, tcg_count, 0x177);
		tcg_gen_add_tl(res_in_call1, tcg_const_local_tl(0x177), res_r_2);
		gen_helper_USEGAS(nores, cpu_env, res_in_call1);
		tcg_temp_free( nores );
		tcg_temp_free( res_r_2 );
		tcg_temp_free( res_in_call1 );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x50) {
		TCGv res_l_1 = tcg_temp_local_new();
		TCGv nores = tcg_temp_new();
		TCGv data_tmp = tcg_temp_local_new();
		TCGv res_l_2 = tcg_temp_local_new();
		TCGv res_in_if0 = tcg_temp_local_new();
		TCGv init_shift = tcg_temp_local_new();
		TCGv dec_cnt = tcg_temp_local_new();
		TCGv i = tcg_temp_local_new();
		TCGv res_in_reg1 = tcg_temp_new();
		TCGv data_val = tcg_temp_local_new();
		TCGv pc_val = tcg_temp_local_new();
		TCGv res_r_3 = tcg_temp_local_new();
		TCGv addr_val = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv res_in_reg2 = tcg_temp_new();
		TCGv res_in_switch0 = tcg_temp_local_new();
		TCGv res_val1 = tcg_temp_new();
		TCGv res_in_type = tcg_temp_local_new();
		TCGv res_in_if1 = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0x50 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// INITIAL_EXP
		tcg_gen_mov_tl(addr_val, tcg_const_local_tl(0x0));
		// IF
		int l_inner0 = gen_new_label();
		int l_outer0 = gen_new_label();
		int l_glob_outer1 = gen_new_label();
		// LST
		gen_helper_MemOps(res_l_2, cpu_env, tcg_opcode);
		tcg_gen_setcondi_tl(TCG_COND_NE, res_r_1, res_l_2, 0x0);
		// LST
		gen_helper_MemOps(res_l_2, cpu_env, tcg_opcode);
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_l_1, res_l_2, 0x8);
		tcg_gen_and_tl(res_in_if0, res_l_1, res_r_1);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if0, 0x0, l_inner0);
		tcg_gen_br(l_outer0);
		gen_set_label(l_inner0);
		// CALL
		gen_helper_GetSingleBlockFromStack(res_r_1, cpu_env);
		tcg_gen_mov_tl(addr_val, res_r_1);
		tcg_gen_mov_tl(nores, addr_val);
		tcg_gen_br(l_glob_outer1);
		gen_set_label(l_outer0);
		
		gen_set_label(l_glob_outer1);
		int l_o1 = gen_new_label();
		int l2 = gen_new_label();
		int l3 = gen_new_label();
		int l4 = gen_new_label();
		int l5 = gen_new_label();
		int l7 = gen_new_label();
		int l8 = gen_new_label();
		int l9 = gen_new_label();
		int l10 = gen_new_label();
		int l11 = gen_new_label();
		int l12 = gen_new_label();
		int l13 = gen_new_label();
		int l14 = gen_new_label();
		// SWITCH
		// TYPE to uint32
		// LST
		gen_helper_MemOps(res_in_type, cpu_env, tcg_opcode);
		tcg_gen_andi_tl(res_in_switch0, res_in_type, 0xFFFFFFFF);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 0, l2);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 1, l3);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 2, l4);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 3, l5);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 4, l7);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 5, l8);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 6, l9);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 7, l10);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 8, l11);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 9, l12);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 10, l13);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 11, l14);
		tcg_gen_br(l_o1);
		gen_set_label(l2);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x2));
		// CALL
		gen_helper_Pop(nores, cpu_env);
		tcg_gen_br(l_o1);
		gen_set_label(l3);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x3));
		// CALL
		gen_helper_MloadInst(nores, cpu_env, addr_val);
		tcg_gen_br(l_o1);
		gen_set_label(l4);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x3));
		// CALL
		gen_helper_MStoreInst(nores, cpu_env, addr_val);
		tcg_gen_br(l_o1);
		gen_set_label(l5);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x3));
		// REG
		tcg_gen_subi_tl(res_in_reg2, cpu_sp, 0x3);
		gen_helper_stack_arr_get(res_r_1, cpu_env, res_in_reg2);
		tcg_gen_mov_tl(data_val, res_r_1);
		tcg_gen_mov_tl(nores, data_val);
		tcg_gen_subi_tl(res_r_1, cpu_sp, 0x4);
		tcg_gen_mov_tl(cpu_sp, res_r_1);
		tcg_gen_mov_tl(nores, cpu_sp);
		tcg_gen_muli_tl(res_r_3, tcg_const_local_tl(0x7), 0x8);
		tcg_gen_shr_tl(res_l_2, data_val, res_r_3);
		tcg_gen_andi_tl(res_val1, res_l_2, 0xFF);
		// REG
		gen_helper_data_bus_set(cpu_env, addr_val, res_val1);
		// IF
		int l_inner6 = gen_new_label();
		int l_outer6 = gen_new_label();
		int l_glob_outer2 = gen_new_label();
		tcg_gen_setcond_tl(TCG_COND_GTU, res_in_if1, addr_val, cpu_mem_size);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if1, 0x0, l_inner6);
		tcg_gen_br(l_outer6);
		gen_set_label(l_inner6);
		tcg_gen_mov_tl(cpu_mem_size, addr_val);
		tcg_gen_mov_tl(nores, cpu_mem_size);
		tcg_gen_br(l_glob_outer2);
		gen_set_label(l_outer6);
		
		gen_set_label(l_glob_outer2);
		tcg_gen_br(l_o1);
		gen_set_label(l7);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x32));
		// CALL
		gen_helper_LoadFromStorageStub(nores, cpu_env, addr_val);
		tcg_gen_br(l_o1);
		gen_set_label(l8);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x0));
		// CALL
		gen_helper_SaveToStorageStub(nores, cpu_env, addr_val);
		tcg_gen_br(l_o1);
		gen_set_label(l9);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x8));
		tcg_gen_mov_tl(cpu_pc, addr_val);
		tcg_gen_mov_tl(nores, cpu_pc);
		tcg_gen_movi_tl(cpu_is_pc_within_inst, 0x1);
		tcg_gen_mov_tl(nores, cpu_is_pc_within_inst);
		tcg_gen_br(l_o1);
		gen_set_label(l10);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0xA));
		tcg_gen_br(l_o1);
		gen_set_label(l11);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x2));
		// CALL
		gen_helper_PcOp(nores, cpu_env);
		tcg_gen_br(l_o1);
		gen_set_label(l12);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x2));
		// CALL
		gen_helper_MSizeOp(nores, cpu_env);
		tcg_gen_br(l_o1);
		gen_set_label(l13);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x2));
		tcg_gen_addi_tl(res_r_1, cpu_sp, 0x1);
		tcg_gen_mov_tl(cpu_sp, res_r_1);
		tcg_gen_mov_tl(nores, cpu_sp);
		// REG
		gen_helper_gas_available_get(res_val1, cpu_env, tcg_const_local_tl(0x0));
		// REG
		gen_helper_stack_arr_set(cpu_env, cpu_sp, res_val1);
		// REG
		gen_helper_gas_available_get(res_val1, cpu_env, tcg_const_local_tl(0x1));
		// REG
		tcg_gen_addi_tl(res_in_reg2, cpu_sp, 0x1);
		gen_helper_stack_arr_set(cpu_env, res_in_reg2, res_val1);
		// REG
		gen_helper_gas_available_get(res_val1, cpu_env, tcg_const_local_tl(0x2));
		// REG
		tcg_gen_addi_tl(res_in_reg2, cpu_sp, 0x2);
		gen_helper_stack_arr_set(cpu_env, res_in_reg2, res_val1);
		// REG
		gen_helper_gas_available_get(res_val1, cpu_env, tcg_const_local_tl(0x3));
		// REG
		tcg_gen_addi_tl(res_in_reg2, cpu_sp, 0x3);
		gen_helper_stack_arr_set(cpu_env, res_in_reg2, res_val1);
		tcg_gen_addi_tl(res_r_1, cpu_sp, 0x3);
		tcg_gen_mov_tl(cpu_sp, res_r_1);
		tcg_gen_mov_tl(nores, cpu_sp);
		tcg_gen_br(l_o1);
		gen_set_label(l14);
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x1));
		tcg_gen_br(l_o1);
		gen_set_label(l_o1);
		tcg_temp_free( res_l_1 );
		tcg_temp_free( nores );
		tcg_temp_free( data_tmp );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( res_in_if0 );
		tcg_temp_free( init_shift );
		tcg_temp_free( dec_cnt );
		tcg_temp_free( i );
		tcg_temp_free( res_in_reg1 );
		tcg_temp_free( data_val );
		tcg_temp_free( pc_val );
		tcg_temp_free( res_r_3 );
		tcg_temp_free( addr_val );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_in_reg2 );
		tcg_temp_free( res_in_switch0 );
		tcg_temp_free( res_val1 );
		tcg_temp_free( res_in_type );
		tcg_temp_free( res_in_if1 );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x0) {
		TCGv nores = tcg_temp_new();
		TCGv res_in_type = tcg_temp_new();
		TCGv res_in_call1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x0 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// CALL
		// TYPE to uint32
		// LST
		gen_helper_ArithmOps(res_in_type, cpu_env, tcg_opcode);
		tcg_gen_andi_tl(res_in_call1, res_in_type, 0xFFFFFFFF);
		gen_helper_ArithmStub(nores, cpu_env, res_in_call1);
		tcg_temp_free( nores );
		tcg_temp_free( res_in_type );
		tcg_temp_free( res_in_call1 );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x10) {
		TCGv nores = tcg_temp_new();
		TCGv res_in_type = tcg_temp_new();
		TCGv res_in_call1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x10 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// CALL
		// TYPE to uint32
		// LST
		gen_helper_CompareLogOps(res_in_type, cpu_env, tcg_opcode);
		tcg_gen_andi_tl(res_in_call1, res_in_type, 0xFFFFFFFF);
		gen_helper_CompareStub(nores, cpu_env, res_in_call1);
		tcg_temp_free( nores );
		tcg_temp_free( res_in_type );
		tcg_temp_free( res_in_call1 );
		return;
	}
	/*
	 * SHA3
	 */
	if (( insn & 0xff ) == 0x20) {
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x20 mask: 0xff\n");
		// CALL
		gen_helper_USEGAS(nores, cpu_env, tcg_const_local_tl(0x1E));
		// CALL
		gen_helper_KeccakAlgStub(nores, cpu_env);
		tcg_temp_free( nores );
		return;
	}
}



#endif
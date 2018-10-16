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
		TCGv nores = tcg_temp_local_new();
		TCGv res = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv res_in_if0 = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0xf0 mask: 0xf0\n");
		uint8_t syscall = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_syscall = tcg_const_local_tl(syscall);
		// LST
		gen_helper_SystemOps(res_r_1, cpu_env, tcg_syscall);
		tcg_gen_mov_tl(res, res_r_1);
		tcg_gen_mov_tl(nores, res);
		// IF
		int l_inner0 = gen_new_label();
		int l_outer0 = gen_new_label();
		int l_glob_outer1 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_NE, res_in_if0, tcg_syscall, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if0, 0x0, l_inner0);
		tcg_gen_br(l_outer0);
		gen_set_label(l_inner0);
		// CALL
		gen_helper_Push(nores, cpu_env, res);
		tcg_gen_br(l_glob_outer1);
		gen_set_label(l_outer0);
		
		gen_set_label(l_glob_outer1);
		tcg_temp_free( nores );
		tcg_temp_free( res );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_in_if0 );
		return;
	}
	/*
	 * STATICCALL
	 */
	if (( insn & 0xff ) == 0xfa) {
		TCGv nores = tcg_temp_local_new();
		TCGv inOff = tcg_temp_local_new();
		TCGv outOff = tcg_temp_local_new();
		TCGv outSize = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_local_new();
		TCGv value = tcg_temp_local_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv inSize = tcg_temp_local_new();
		TCGv address = tcg_temp_local_new();
		TCGv callGas = tcg_temp_local_new();
		TCGv res_in_if1 = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0xfa mask: 0xff\n");
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(callGas, res_in_init);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(address, res_in_init);
		// INITIAL_EXP
		tcg_gen_mov_tl(value, tcg_const_local_tl(0x0));
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(inOff, res_in_init);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(inSize, res_in_init);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(outOff, res_in_init);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(outSize, res_in_init);
		// IF
		int l_inner1 = gen_new_label();
		int l_outer1 = gen_new_label();
		int l_glob_outer2 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if1, cpu_gas_available, 0x28);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if1, 0x0, l_inner1);
		tcg_gen_br(l_outer1);
		gen_set_label(l_inner1);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer2);
		gen_set_label(l_outer1);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x28);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer2);
		tcg_temp_free( nores );
		tcg_temp_free( inOff );
		tcg_temp_free( outOff );
		tcg_temp_free( outSize );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( value );
		tcg_temp_free( res_in_init );
		tcg_temp_free( inSize );
		tcg_temp_free( address );
		tcg_temp_free( callGas );
		tcg_temp_free( res_in_if1 );
		return;
	}
	/*
	 * REVERT
	 */
	if (( insn & 0xff ) == 0xfd) {
		TCGv a = tcg_temp_local_new();
		TCGv nores = tcg_temp_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv b = tcg_temp_local_new();
		TCGv res_in_if2 = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0xfd mask: 0xff\n");
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(a, res_in_init);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(b, res_in_init);
		// IF
		int l_inner2 = gen_new_label();
		int l_outer2 = gen_new_label();
		int l_glob_outer3 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if2, cpu_gas_available, 0x0);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if2, 0x0, l_inner2);
		tcg_gen_br(l_outer2);
		gen_set_label(l_inner2);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer3);
		gen_set_label(l_outer2);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x0);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer3);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_temp_free( a );
		tcg_temp_free( nores );
		tcg_temp_free( res_in_init );
		tcg_temp_free( b );
		tcg_temp_free( res_in_if2 );
		tcg_temp_free( res_r_1 );
		return;
	}
	/*
	 * SUICIDE
	 */
	if (( insn & 0xff ) == 0xff) {
		TCGv a = tcg_temp_local_new();
		TCGv nores = tcg_temp_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv res_in_if3 = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0xff mask: 0xff\n");
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(a, res_in_init);
		// IF
		int l_inner3 = gen_new_label();
		int l_outer3 = gen_new_label();
		int l_glob_outer4 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if3, cpu_gas_available, 0x0);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if3, 0x0, l_inner3);
		tcg_gen_br(l_outer3);
		gen_set_label(l_inner3);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer4);
		gen_set_label(l_outer3);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x0);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer4);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_temp_free( a );
		tcg_temp_free( nores );
		tcg_temp_free( res_in_init );
		tcg_temp_free( res_in_if3 );
		tcg_temp_free( res_r_1 );
		return;
	}
	/*
	 * $gas_opcode
	 */
	if (( insn & 0xf0 ) == 0x40) {
		TCGv nores = tcg_temp_new();
		TCGv res = tcg_temp_local_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv res1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x40 mask: 0xf0\n");
		uint8_t gas_opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_gas_opcode = tcg_const_local_tl(gas_opcode);
		// INITIAL_EXP
		// LST
		gen_helper_BlockChain(res_in_init, cpu_env, tcg_gas_opcode);
		tcg_gen_mov_tl(res, res_in_init);
		// CALL
		gen_helper_Push(nores, cpu_env, res);
		tcg_temp_free( nores );
		tcg_temp_free( res );
		tcg_temp_free( res_in_init );
		tcg_temp_free( res1 );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x30) {
		TCGv res_in_if4 = tcg_temp_local_new();
		TCGv res_l_1 = tcg_temp_local_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv res_l_2 = tcg_temp_local_new();
		TCGv res_r_2 = tcg_temp_local_new();
		TCGv res = tcg_temp_local_new();
		TCGv res1 = tcg_temp_new();
		TCGv res_r_1 = tcg_temp_local_new();
		TCGv nores = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0x30 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// INITIAL_EXP
		// LST
		gen_helper_AccountsData(res_in_init, cpu_env, tcg_opcode);
		tcg_gen_mov_tl(res, res_in_init);
		// IF
		int l_inner4 = gen_new_label();
		int l_outer4 = gen_new_label();
		int l_glob_outer5 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_NE, res_r_1, tcg_opcode, 0xC);
		tcg_gen_setcondi_tl(TCG_COND_NE, res_r_2, tcg_opcode, 0x9);
		tcg_gen_setcondi_tl(TCG_COND_NE, res_l_2, tcg_opcode, 0x7);
		tcg_gen_and_tl(res_l_1, res_l_2, res_r_2);
		tcg_gen_and_tl(res_in_if4, res_l_1, res_r_1);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if4, 0x0, l_inner4);
		tcg_gen_br(l_outer4);
		gen_set_label(l_inner4);
		// CALL
		gen_helper_Push(nores, cpu_env, res);
		tcg_gen_br(l_glob_outer5);
		gen_set_label(l_outer4);
		
		gen_set_label(l_glob_outer5);
		tcg_temp_free( res_in_if4 );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( res_in_init );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( res_r_2 );
		tcg_temp_free( res );
		tcg_temp_free( res1 );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( nores );
		return;
	}
	/*
	 * PUSH$count
	 */
	if (( insn & 0xe0 ) == 0x60) {
		TCGv nores = tcg_temp_new();
		TCGv res_in_if5 = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv res_l_2 = tcg_temp_new();
		TCGv res_l_1 = tcg_temp_new();
		TCGv res_in_call1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x60 mask: 0xe0\n");
		uint8_t count = extract32((uint32_t)insn, 0, 5);
		TCGv tcg_count = tcg_const_local_tl(count);
		// IF
		int l_inner5 = gen_new_label();
		int l_outer5 = gen_new_label();
		int l_glob_outer6 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if5, cpu_gas_available, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if5, 0x0, l_inner5);
		tcg_gen_br(l_outer5);
		gen_set_label(l_inner5);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer6);
		gen_set_label(l_outer5);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x3);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer6);
		// CALL
		tcg_gen_addi_tl(res_in_call1, tcg_count, 0x1);
		gen_helper_PushInst(nores, cpu_env, res_in_call1);
		tcg_gen_movi_tl(cpu_is_pc_within_inst, 0x1);
		tcg_gen_mov_tl(nores, cpu_is_pc_within_inst);
		tcg_gen_add_tl(res_l_2, cpu_pc, tcg_count);
		tcg_gen_addi_tl(res_r_1, res_l_2, 0x2);
		tcg_gen_mov_tl(cpu_pc, res_r_1);
		tcg_gen_mov_tl(nores, cpu_pc);
		tcg_temp_free( nores );
		tcg_temp_free( res_in_if5 );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( res_in_call1 );
		return;
	}
	/*
	 * DUP$count
	 */
	if (( insn & 0xf0 ) == 0x80) {
		TCGv a = tcg_temp_local_new();
		TCGv nores = tcg_temp_new();
		TCGv res_in_if6 = tcg_temp_local_new();
		TCGv res_r_2 = tcg_temp_new();
		TCGv res_in_reg2 = tcg_temp_new();
		TCGv res_r_3 = tcg_temp_new();
		TCGv res_in_reg1 = tcg_temp_new();
		TCGv res_r_1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x80 mask: 0xf0\n");
		uint8_t count = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_count = tcg_const_local_tl(count);
		// IF
		int l_inner6 = gen_new_label();
		int l_outer6 = gen_new_label();
		int l_glob_outer7 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if6, cpu_gas_available, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if6, 0x0, l_inner6);
		tcg_gen_br(l_outer6);
		gen_set_label(l_inner6);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer7);
		gen_set_label(l_outer6);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x3);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer7);
		// REG
		tcg_gen_addi_tl(res_r_3, tcg_count, 0x1);
		tcg_gen_add_tl(res_in_reg2, cpu_sp, res_r_3);
		gen_helper_stack_arr_get(res_r_1, cpu_env, res_in_reg2);
		tcg_gen_mov_tl(a, res_r_1);
		tcg_gen_mov_tl(nores, a);
		// CALL
		gen_helper_Push(nores, cpu_env, a);
		tcg_temp_free( a );
		tcg_temp_free( nores );
		tcg_temp_free( res_in_if6 );
		tcg_temp_free( res_r_2 );
		tcg_temp_free( res_in_reg2 );
		tcg_temp_free( res_r_3 );
		tcg_temp_free( res_in_reg1 );
		tcg_temp_free( res_r_1 );
		return;
	}
	/*
	 * SWAP$count
	 */
	if (( insn & 0xf0 ) == 0x90) {
		TCGv nores = tcg_temp_local_new();
		TCGv res_l_1 = tcg_temp_new();
		TCGv res_in_if7 = tcg_temp_local_new();
		TCGv first_el = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_local_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv res_l_2 = tcg_temp_new();
		TCGv res_in_reg2 = tcg_temp_new();
		TCGv res_in_reg1 = tcg_temp_new();
		TCGv res_val1 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x90 mask: 0xf0\n");
		uint8_t count = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_count = tcg_const_local_tl(count);
		// INITIAL_EXP
		// REG
		tcg_gen_addi_tl(res_in_reg2, cpu_sp, 0x1);
		gen_helper_stack_arr_get(res_in_init, cpu_env, res_in_reg2);
		tcg_gen_mov_tl(first_el, res_in_init);
		// IF
		int l_inner7 = gen_new_label();
		int l_outer7 = gen_new_label();
		int l_glob_outer8 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if7, cpu_gas_available, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if7, 0x0, l_inner7);
		tcg_gen_br(l_outer7);
		gen_set_label(l_inner7);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer8);
		gen_set_label(l_outer7);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x3);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer8);
		// REG
		tcg_gen_add_tl(res_l_2, cpu_sp, tcg_count);
		tcg_gen_addi_tl(res_in_reg1, res_l_2, 0x2);
		gen_helper_stack_arr_get(res_val1, cpu_env, res_in_reg1);
		// REG
		tcg_gen_addi_tl(res_in_reg2, cpu_sp, 0x1);
		gen_helper_stack_arr_set(cpu_env, res_in_reg2, res_val1);
		// REG
		tcg_gen_add_tl(res_l_2, cpu_sp, tcg_count);
		tcg_gen_addi_tl(res_in_reg1, res_l_2, 0x2);
		gen_helper_stack_arr_set(cpu_env, res_in_reg1, first_el);
		tcg_temp_free( nores );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( res_in_if7 );
		tcg_temp_free( first_el );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_in_init );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( res_in_reg2 );
		tcg_temp_free( res_in_reg1 );
		tcg_temp_free( res_val1 );
		return;
	}
	/*
	 * LOG$count
	 */
	if (( insn & 0xf8 ) == 0xa0) {
		TCGv nores = tcg_temp_new();
		TCGv m_ptr = tcg_temp_local_new();
		TCGv i = tcg_temp_local_new();
		TCGv res_in_if8 = tcg_temp_local_new();
		TCGv res_in_init = tcg_temp_new();
		TCGv l2_data = tcg_temp_local_new();
		TCGv res_r_3 = tcg_temp_local_new();
		TCGv res_r_2 = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv m_size = tcg_temp_local_new();
		TCGv l1_data = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0xa0 mask: 0xf8\n");
		uint8_t count = extract32((uint32_t)insn, 0, 3);
		TCGv tcg_count = tcg_const_local_tl(count);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(l1_data, res_in_init);
		// INITIAL_EXP
		// CALL
		gen_helper_Pop(res_in_init, cpu_env);
		tcg_gen_mov_tl(l2_data, res_in_init);
		// INITIAL_EXP
		// TYPE to uint32
		tcg_gen_andi_tl(res_in_init, l1_data, 0xFFFFFFFF);
		tcg_gen_mov_tl(m_ptr, res_in_init);
		// INITIAL_EXP
		// TYPE to uint32
		tcg_gen_andi_tl(res_in_init, l2_data, 0xFFFFFFFF);
		tcg_gen_mov_tl(m_size, res_in_init);
		// IF
		int l_inner8 = gen_new_label();
		int l_outer8 = gen_new_label();
		int l_glob_outer9 = gen_new_label();
		tcg_gen_muli_tl(res_r_2, tcg_count, 0x177);
		tcg_gen_add_tl(res_r_1, tcg_const_local_tl(0x177), res_r_2);
		tcg_gen_setcond_tl(TCG_COND_LTU, res_in_if8, cpu_gas_available, res_r_1);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if8, 0x0, l_inner8);
		tcg_gen_br(l_outer8);
		gen_set_label(l_inner8);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer9);
		gen_set_label(l_outer8);
		// ELSE
		tcg_gen_muli_tl(res_r_3, tcg_count, 0x177);
		tcg_gen_add_tl(res_r_2, tcg_const_local_tl(0x177), res_r_3);
		tcg_gen_sub_tl(res_r_1, cpu_gas_available, res_r_2);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer9);
		// CALL
		gen_helper_LogInst(nores, cpu_env, tcg_count, m_ptr);
		tcg_gen_addi_tl(res_r_1, tcg_count, 0x2);
		tcg_gen_mov_tl(cpu_log_ptr, res_r_1);
		tcg_gen_mov_tl(nores, cpu_log_ptr);
		tcg_temp_free( nores );
		tcg_temp_free( m_ptr );
		tcg_temp_free( i );
		tcg_temp_free( res_in_if8 );
		tcg_temp_free( res_in_init );
		tcg_temp_free( l2_data );
		tcg_temp_free( res_r_3 );
		tcg_temp_free( res_r_2 );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( m_size );
		tcg_temp_free( l1_data );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x50) {
		TCGv nores = tcg_temp_local_new();
		TCGv data_tmp = tcg_temp_local_new();
		TCGv init_shift = tcg_temp_local_new();
		TCGv dec_cnt = tcg_temp_local_new();
		TCGv res_in_switch0 = tcg_temp_local_new();
		TCGv data_val = tcg_temp_local_new();
		TCGv pc_val = tcg_temp_local_new();
		TCGv res_in_if9 = tcg_temp_local_new();
		TCGv res_in_if16 = tcg_temp_local_new();
		TCGv addr_val = tcg_temp_local_new();
		TCGv res_in_if14 = tcg_temp_local_new();
		TCGv res_in_if15 = tcg_temp_local_new();
		TCGv res_in_if12 = tcg_temp_local_new();
		TCGv res_in_if13 = tcg_temp_local_new();
		TCGv res_in_if10 = tcg_temp_local_new();
		TCGv res_in_if11 = tcg_temp_local_new();
		TCGv res_in_type = tcg_temp_local_new();
		TCGv res_in_if22 = tcg_temp_local_new();
		TCGv res_in_if18 = tcg_temp_local_new();
		TCGv res_in_if19 = tcg_temp_local_new();
		TCGv res_l_1 = tcg_temp_local_new();
		TCGv res_in_if17 = tcg_temp_local_new();
		TCGv i = tcg_temp_local_new();
		TCGv res_in_if23 = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_local_new();
		TCGv res_in_if21 = tcg_temp_local_new();
		TCGv res_in_if20 = tcg_temp_local_new();
		INFO_PRINT("Main::id: 0x50 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// IF
		int l_inner9 = gen_new_label();
		int l_outer9 = gen_new_label();
		int l_glob_outer10 = gen_new_label();
		// LST
		gen_helper_MemOps(res_l_1, cpu_env, tcg_opcode);
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if9, res_l_1, 0x8);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if9, 0x0, l_inner9);
		tcg_gen_br(l_outer9);
		gen_set_label(l_inner9);
		// TYPE to uint32
		// CALL
		gen_helper_Pop(res_in_type, cpu_env);
		tcg_gen_andi_tl(res_r_1, res_in_type, 0xFFFFFFFF);
		tcg_gen_mov_tl(addr_val, res_r_1);
		tcg_gen_mov_tl(nores, addr_val);
		tcg_gen_br(l_glob_outer10);
		gen_set_label(l_outer9);
		
		gen_set_label(l_glob_outer10);
		int l_o10 = gen_new_label();
		int l11 = gen_new_label();
		int l13 = gen_new_label();
		int l15 = gen_new_label();
		int l17 = gen_new_label();
		int l20 = gen_new_label();
		int l22 = gen_new_label();
		int l24 = gen_new_label();
		int l26 = gen_new_label();
		int l29 = gen_new_label();
		int l31 = gen_new_label();
		int l33 = gen_new_label();
		int l35 = gen_new_label();
		// SWITCH
		// TYPE to uint32
		// LST
		gen_helper_MemOps(res_in_type, cpu_env, tcg_opcode);
		tcg_gen_andi_tl(res_in_switch0, res_in_type, 0xFFFFFFFF);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 0, l11);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 1, l13);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 2, l15);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 3, l17);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 4, l20);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 5, l22);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 6, l24);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 7, l26);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 8, l29);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 9, l31);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 10, l33);
		tcg_gen_brcondi_tl(TCG_COND_EQ, res_in_switch0, 11, l35);
		tcg_gen_br(l_o10);
		gen_set_label(l11);
		// IF
		int l_inner12 = gen_new_label();
		int l_outer12 = gen_new_label();
		int l_glob_outer11 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if10, cpu_gas_available, 0x2);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if10, 0x0, l_inner12);
		tcg_gen_br(l_outer12);
		gen_set_label(l_inner12);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer11);
		gen_set_label(l_outer12);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x2);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer11);
		// CALL
		gen_helper_Pop(nores, cpu_env);
		tcg_gen_br(l_o10);
		gen_set_label(l13);
		// IF
		int l_inner14 = gen_new_label();
		int l_outer14 = gen_new_label();
		int l_glob_outer12 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if11, cpu_gas_available, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if11, 0x0, l_inner14);
		tcg_gen_br(l_outer14);
		gen_set_label(l_inner14);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer12);
		gen_set_label(l_outer14);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x3);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer12);
		// CALL
		gen_helper_MloadInst(nores, cpu_env, addr_val);
		tcg_gen_br(l_o10);
		gen_set_label(l15);
		// IF
		int l_inner16 = gen_new_label();
		int l_outer16 = gen_new_label();
		int l_glob_outer13 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if12, cpu_gas_available, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if12, 0x0, l_inner16);
		tcg_gen_br(l_outer16);
		gen_set_label(l_inner16);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer13);
		gen_set_label(l_outer16);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x3);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer13);
		// CALL
		gen_helper_MStoreInst(nores, cpu_env, addr_val);
		tcg_gen_br(l_o10);
		gen_set_label(l17);
		// IF
		int l_inner18 = gen_new_label();
		int l_outer18 = gen_new_label();
		int l_glob_outer14 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if13, cpu_gas_available, 0x3);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if13, 0x0, l_inner18);
		tcg_gen_br(l_outer18);
		gen_set_label(l_inner18);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer14);
		gen_set_label(l_outer18);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x3);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer14);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(data_val, res_r_1);
		tcg_gen_mov_tl(nores, data_val);
		// REG
		gen_helper_data_bus_set(cpu_env, addr_val, data_val);
		// IF
		int l_inner19 = gen_new_label();
		int l_outer19 = gen_new_label();
		int l_glob_outer15 = gen_new_label();
		tcg_gen_setcond_tl(TCG_COND_GTU, res_in_if14, addr_val, cpu_mem_size);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if14, 0x0, l_inner19);
		tcg_gen_br(l_outer19);
		gen_set_label(l_inner19);
		tcg_gen_mov_tl(cpu_mem_size, addr_val);
		tcg_gen_mov_tl(nores, cpu_mem_size);
		tcg_gen_br(l_glob_outer15);
		gen_set_label(l_outer19);
		
		gen_set_label(l_glob_outer15);
		tcg_gen_br(l_o10);
		gen_set_label(l20);
		// IF
		int l_inner21 = gen_new_label();
		int l_outer21 = gen_new_label();
		int l_glob_outer16 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if15, cpu_gas_available, 0x32);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if15, 0x0, l_inner21);
		tcg_gen_br(l_outer21);
		gen_set_label(l_inner21);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer16);
		gen_set_label(l_outer21);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x32);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer16);
		// CALL
		gen_helper_LoadFromStorage(res_r_1, cpu_env, addr_val);
		tcg_gen_mov_tl(data_val, res_r_1);
		tcg_gen_mov_tl(nores, data_val);
		// CALL
		gen_helper_Push(nores, cpu_env, data_val);
		tcg_gen_br(l_o10);
		gen_set_label(l22);
		// IF
		int l_inner23 = gen_new_label();
		int l_outer23 = gen_new_label();
		int l_glob_outer17 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if16, cpu_gas_available, 0x0);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if16, 0x0, l_inner23);
		tcg_gen_br(l_outer23);
		gen_set_label(l_inner23);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer17);
		gen_set_label(l_outer23);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x0);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer17);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(data_val, res_r_1);
		tcg_gen_mov_tl(nores, data_val);
		// CALL
		gen_helper_SaveToStorage(nores, cpu_env, addr_val, data_val);
		tcg_gen_br(l_o10);
		gen_set_label(l24);
		// IF
		int l_inner25 = gen_new_label();
		int l_outer25 = gen_new_label();
		int l_glob_outer18 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if17, cpu_gas_available, 0x8);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if17, 0x0, l_inner25);
		tcg_gen_br(l_outer25);
		gen_set_label(l_inner25);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer18);
		gen_set_label(l_outer25);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x8);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer18);
		tcg_gen_mov_tl(cpu_pc, addr_val);
		tcg_gen_mov_tl(nores, cpu_pc);
		tcg_gen_movi_tl(cpu_is_pc_within_inst, 0x1);
		tcg_gen_mov_tl(nores, cpu_is_pc_within_inst);
		tcg_gen_br(l_o10);
		gen_set_label(l26);
		// IF
		int l_inner27 = gen_new_label();
		int l_outer27 = gen_new_label();
		int l_glob_outer19 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if18, cpu_gas_available, 0xA);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if18, 0x0, l_inner27);
		tcg_gen_br(l_outer27);
		gen_set_label(l_inner27);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer19);
		gen_set_label(l_outer27);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0xA);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer19);
		// IF
		int l_inner28 = gen_new_label();
		int l_outer28 = gen_new_label();
		int l_glob_outer20 = gen_new_label();
		// CALL
		gen_helper_Pop(res_l_1, cpu_env);
		tcg_gen_setcondi_tl(TCG_COND_NE, res_in_if19, res_l_1, 0x0);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if19, 0x0, l_inner28);
		tcg_gen_br(l_outer28);
		gen_set_label(l_inner28);
		// TYPE to uint32
		tcg_gen_andi_tl(res_r_1, addr_val, 0xFFFFFFFF);
		tcg_gen_mov_tl(cpu_pc, res_r_1);
		tcg_gen_mov_tl(nores, cpu_pc);
		tcg_gen_movi_tl(cpu_is_pc_within_inst, 0x1);
		tcg_gen_mov_tl(nores, cpu_is_pc_within_inst);
		tcg_gen_br(l_glob_outer20);
		gen_set_label(l_outer28);
		
		gen_set_label(l_glob_outer20);
		tcg_gen_br(l_o10);
		gen_set_label(l29);
		// IF
		int l_inner30 = gen_new_label();
		int l_outer30 = gen_new_label();
		int l_glob_outer21 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if20, cpu_gas_available, 0x2);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if20, 0x0, l_inner30);
		tcg_gen_br(l_outer30);
		gen_set_label(l_inner30);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer21);
		gen_set_label(l_outer30);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x2);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer21);
		tcg_gen_mov_tl(data_val, cpu_pc);
		tcg_gen_mov_tl(nores, data_val);
		// CALL
		gen_helper_Push(nores, cpu_env, data_val);
		tcg_gen_br(l_o10);
		gen_set_label(l31);
		// IF
		int l_inner32 = gen_new_label();
		int l_outer32 = gen_new_label();
		int l_glob_outer22 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if21, cpu_gas_available, 0x2);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if21, 0x0, l_inner32);
		tcg_gen_br(l_outer32);
		gen_set_label(l_inner32);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer22);
		gen_set_label(l_outer32);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x2);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer22);
		tcg_gen_mov_tl(data_val, cpu_mem_size);
		tcg_gen_mov_tl(nores, data_val);
		// CALL
		gen_helper_Push(nores, cpu_env, data_val);
		tcg_gen_br(l_o10);
		gen_set_label(l33);
		// IF
		int l_inner34 = gen_new_label();
		int l_outer34 = gen_new_label();
		int l_glob_outer23 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if22, cpu_gas_available, 0x2);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if22, 0x0, l_inner34);
		tcg_gen_br(l_outer34);
		gen_set_label(l_inner34);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer23);
		gen_set_label(l_outer34);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x2);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer23);
		// CALL
		gen_helper_Push(nores, cpu_env, cpu_gas_available);
		tcg_gen_br(l_o10);
		gen_set_label(l35);
		// IF
		int l_inner36 = gen_new_label();
		int l_outer36 = gen_new_label();
		int l_glob_outer24 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if23, cpu_gas_available, 0x1);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if23, 0x0, l_inner36);
		tcg_gen_br(l_outer36);
		gen_set_label(l_inner36);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer24);
		gen_set_label(l_outer36);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x1);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer24);
		tcg_gen_br(l_o10);
		gen_set_label(l_o10);
		tcg_temp_free( nores );
		tcg_temp_free( data_tmp );
		tcg_temp_free( init_shift );
		tcg_temp_free( dec_cnt );
		tcg_temp_free( res_in_switch0 );
		tcg_temp_free( data_val );
		tcg_temp_free( pc_val );
		tcg_temp_free( res_in_if9 );
		tcg_temp_free( res_in_if16 );
		tcg_temp_free( addr_val );
		tcg_temp_free( res_in_if14 );
		tcg_temp_free( res_in_if15 );
		tcg_temp_free( res_in_if12 );
		tcg_temp_free( res_in_if13 );
		tcg_temp_free( res_in_if10 );
		tcg_temp_free( res_in_if11 );
		tcg_temp_free( res_in_type );
		tcg_temp_free( res_in_if22 );
		tcg_temp_free( res_in_if18 );
		tcg_temp_free( res_in_if19 );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( res_in_if17 );
		tcg_temp_free( i );
		tcg_temp_free( res_in_if23 );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_in_if21 );
		tcg_temp_free( res_in_if20 );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x0) {
		TCGv a = tcg_temp_local_new();
		TCGv res_l_1 = tcg_temp_new();
		TCGv c = tcg_temp_local_new();
		TCGv b = tcg_temp_local_new();
		TCGv is_c_opcode = tcg_temp_local_new();
		TCGv res_r1_2 = tcg_temp_local_new();
		TCGv res = tcg_temp_local_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv res_r_2 = tcg_temp_new();
		TCGv res_r1_1 = tcg_temp_local_new();
		TCGv res_l_2 = tcg_temp_new();
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x0 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(a, res_r_1);
		tcg_gen_mov_tl(nores, a);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(b, res_r_1);
		tcg_gen_mov_tl(nores, b);
		tcg_gen_setcondi_tl(TCG_COND_EQ, res_r_2, tcg_opcode, 0x9);
		tcg_gen_setcondi_tl(TCG_COND_EQ, res_l_2, tcg_opcode, 0x8);
		tcg_gen_or_tl(res_r_1, res_l_2, res_r_2);
		tcg_gen_mov_tl(is_c_opcode, res_r_1);
		tcg_gen_mov_tl(nores, is_c_opcode);
		// ?
		// CALL
		gen_helper_Pop(res_r1_2, cpu_env);
		tcg_gen_movcond_tl(TCG_COND_NE, res_r_1, is_c_opcode, tcg_const_local_tl(0x0), res_r1_2, tcg_const_local_tl(0x0));
		tcg_gen_mov_tl(c, res_r_1);
		tcg_gen_mov_tl(nores, c);
		// LST
		gen_helper_ArithmOps(res_r_1, cpu_env, tcg_opcode, a, b, c);
		tcg_gen_mov_tl(res, res_r_1);
		tcg_gen_mov_tl(nores, res);
		// CALL
		gen_helper_Push(nores, cpu_env, res);
		tcg_temp_free( a );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( c );
		tcg_temp_free( b );
		tcg_temp_free( is_c_opcode );
		tcg_temp_free( res_r1_2 );
		tcg_temp_free( res );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_r_2 );
		tcg_temp_free( res_r1_1 );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( nores );
		return;
	}
	/*
	 * $opcode
	 */
	if (( insn & 0xf0 ) == 0x10) {
		TCGv a = tcg_temp_local_new();
		TCGv res_l_1 = tcg_temp_new();
		TCGv c = tcg_temp_local_new();
		TCGv b = tcg_temp_local_new();
		TCGv res = tcg_temp_local_new();
		TCGv res_r2_1 = tcg_temp_local_new();
		TCGv res_r2_2 = tcg_temp_local_new();
		TCGv res_r_2 = tcg_temp_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv res_l_2 = tcg_temp_new();
		TCGv is_b_opcode = tcg_temp_local_new();
		TCGv nores = tcg_temp_new();
		INFO_PRINT("Main::id: 0x10 mask: 0xf0\n");
		uint8_t opcode = extract32((uint32_t)insn, 0, 4);
		TCGv tcg_opcode = tcg_const_local_tl(opcode);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(a, res_r_1);
		tcg_gen_mov_tl(nores, a);
		tcg_gen_setcondi_tl(TCG_COND_EQ, res_r_2, tcg_opcode, 0x9);
		tcg_gen_setcondi_tl(TCG_COND_EQ, res_l_2, tcg_opcode, 0x5);
		tcg_gen_or_tl(res_r_1, res_l_2, res_r_2);
		tcg_gen_mov_tl(is_b_opcode, res_r_1);
		tcg_gen_mov_tl(nores, is_b_opcode);
		// ?
		// CALL
		gen_helper_Pop(res_r2_2, cpu_env);
		tcg_gen_movcond_tl(TCG_COND_NE, res_r_1, is_b_opcode, tcg_const_local_tl(0x0), tcg_const_local_tl(0x0), res_r2_2);
		tcg_gen_mov_tl(b, res_r_1);
		tcg_gen_mov_tl(nores, b);
		// LST
		gen_helper_CompareLogOps(res_r_1, cpu_env, tcg_opcode, a, b);
		tcg_gen_mov_tl(res, res_r_1);
		tcg_gen_mov_tl(nores, res);
		// CALL
		gen_helper_Push(nores, cpu_env, res);
		tcg_temp_free( a );
		tcg_temp_free( res_l_1 );
		tcg_temp_free( c );
		tcg_temp_free( b );
		tcg_temp_free( res );
		tcg_temp_free( res_r2_1 );
		tcg_temp_free( res_r2_2 );
		tcg_temp_free( res_r_2 );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( res_l_2 );
		tcg_temp_free( is_b_opcode );
		tcg_temp_free( nores );
		return;
	}
	/*
	 * SHA3
	 */
	if (( insn & 0xff ) == 0x20) {
		TCGv a = tcg_temp_local_new();
		TCGv nores = tcg_temp_new();
		TCGv res_r_1 = tcg_temp_new();
		TCGv b = tcg_temp_local_new();
		TCGv res = tcg_temp_local_new();
		TCGv res_in_if24 = tcg_temp_local_new();
		TCGv res_in_call1 = tcg_temp_new();
		TCGv res_in_call3 = tcg_temp_new();
		TCGv res_in_call2 = tcg_temp_new();
		INFO_PRINT("Main::id: 0x20 mask: 0xff\n");
		// IF
		int l_inner37 = gen_new_label();
		int l_outer37 = gen_new_label();
		int l_glob_outer25 = gen_new_label();
		tcg_gen_setcondi_tl(TCG_COND_LTU, res_in_if24, cpu_gas_available, 0x1E);
		tcg_gen_brcondi_tl(TCG_COND_NE, res_in_if24, 0x0, l_inner37);
		tcg_gen_br(l_outer37);
		gen_set_label(l_inner37);
		tcg_gen_movi_tl(cpu_gas_available, 0xFFFFFFFF);
		tcg_gen_mov_tl(nores, cpu_gas_available);
		// CALL
		gen_helper_StopExec(nores, cpu_env);
		tcg_gen_br(l_glob_outer25);
		gen_set_label(l_outer37);
		// ELSE
		tcg_gen_subi_tl(res_r_1, cpu_gas_available, 0x1E);
		tcg_gen_mov_tl(cpu_gas_available, res_r_1);
		gen_set_label(l_glob_outer25);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(a, res_r_1);
		tcg_gen_mov_tl(nores, a);
		// CALL
		gen_helper_Pop(res_r_1, cpu_env);
		tcg_gen_mov_tl(b, res_r_1);
		tcg_gen_mov_tl(nores, b);
		// CALL
		// TYPE to uint32
		tcg_gen_andi_tl(res_in_call2, a, 0xFFFFFFFF);
		// TYPE to uint32
		tcg_gen_andi_tl(res_in_call3, b, 0xFFFFFFFF);
		gen_helper_KeccakAlg(res_r_1, cpu_env, res_in_call2, res_in_call3);
		tcg_gen_mov_tl(res, res_r_1);
		tcg_gen_mov_tl(nores, res);
		// CALL
		gen_helper_Push(nores, cpu_env, res);
		tcg_temp_free( a );
		tcg_temp_free( nores );
		tcg_temp_free( res_r_1 );
		tcg_temp_free( b );
		tcg_temp_free( res );
		tcg_temp_free( res_in_if24 );
		tcg_temp_free( res_in_call1 );
		tcg_temp_free( res_in_call3 );
		tcg_temp_free( res_in_call2 );
		return;
	}
}



#endif
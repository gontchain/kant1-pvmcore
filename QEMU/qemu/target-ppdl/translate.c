/*
 * PPDL translation
 *
 * Copyright (c) 2018 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "cpu.h"
#include "disas_ppdl_insn.h" //function definition (much long to put here)
#include "exec/exec-all.h"
#include "disas/disas.h"
#include "qemu/log.h"
#include "config.h"
#include "exec/cpu_ldst.h" // cpu_ldsb_code

#if defined(CONFIG_LINUX_USER)
#include "linux-user/qemu.h"
#else
#include "qemu-common.h" // shared variables
#endif

#include "exec/helper-proto.h"
#include "exec/helper-gen.h"

#pragma GCC diagnostic ignored "-Wformat-zero-length"

#define PPDL_DISAS

#ifdef PPDL_DISAS
#  define LOG_DIS(...) qemu_log_mask(CPU_LOG_TB_IN_ASM, ## __VA_ARGS__)
#else
#  define LOG_DIS(...) do { } while (0)
#endif

uint64_t end_pc;
CPUPPDLState envSaved;
int changed_pc = 0;

#include "translate_tcgreg.h"

#include "exec/gen-icount.h" // gen_tb_*

uint32_t delayed_branch = 0;
uint32_t is_branch_delayed_first = 1;

#include "translate_insn.h" // genBlock_*

#if defined(CONFIG_DEBUG)
#   define ERROR_PRINT(...) (debug) ? printf("::GEN ERROR:: error in " __VA_ARGS__ "\n") : printf("");
#   define INFO_PRINT(...) (debug) ? printf("::GEN INFO:: " __VA_ARGS__ ) : printf("");
#else
#   define ERROR_PRINT(...)
#   define INFO_PRINT(...)
#endif

#include "translate.h"
uint8_t     insn;

static void disas_ppdl_insn(DisasContext *dc, PPDLCPU *cpu)
{
    CPUPPDLState *env = &cpu->env;
    insn = cpu_ldsb_code(env, dc->pc);
    if (use_tracer || use_regtracer || use_ctracer)
        gen_helper_tracer(cpu_env, tcg_const_local_i32(1));
    dc->npc = dc->pc + 1;
    dc->pc = dc->npc; // инкрементируем счетчик pc
    INFO_PRINT("genBlock_Main: insn = %" PRIx8 "\n", insn); // DBG output
    genBlock_Main(env, insn, dc->pc - 1);
#if defined(CONFIG_DEBUG)
    gen_helper_print(cpu_env);
#endif
#ifdef CONFIG_USER_ONLY
    if (use_gdb)
        gen_helper_gdb_handling(cpu_env);
#endif
}

static void gen_exception(DisasContext *dc, unsigned int excp)
{
    TCGv_i32 tmp = tcg_const_i32(excp);
    gen_helper_exception(cpu_env, tmp);
    tcg_temp_free_i32(tmp);
}

static void gen_goto_tb(DisasContext *dc, int n, target_ulong dest)
{
    TranslationBlock *tb;
    tb = dc->tb;
    if ((tb->pc & TARGET_PAGE_MASK) == (dest & TARGET_PAGE_MASK) &&
                                       likely(!dc->singlestep_enabled)) {
        tcg_gen_movi_tl(cpu_pc, dest);
        tcg_gen_goto_tb(n);
        tcg_gen_exit_tb((uintptr_t)tb + n);
    } else {
        tcg_gen_movi_tl(cpu_pc, dest);
        if (dc->singlestep_enabled) {
            gen_exception(dc, EXCP_DEBUG);
        }
        tcg_gen_exit_tb(0);
    }
}

static int check_breakpoint(PPDLCPU *cpu, DisasContext *dc)
{
    CPUState *cs = CPU(cpu);
    CPUBreakpoint *bp;

    if (unlikely(!QTAILQ_EMPTY(&cs->breakpoints))) {
        QTAILQ_FOREACH(bp, &cs->breakpoints, entry) {
            if (bp->pc == dc->pc) {
                tcg_gen_movi_tl(cpu_pc, dc->pc);
                gen_exception(dc, EXCP_DEBUG);
                dc->is_jmp = DISAS_UPDATE;
                return 1;
            }
        }
    }
    return 0;
}

static inline void gen_intermediate_code_internal(PPDLCPU *cpu,
                                                  TranslationBlock *tb,
                                                  int search_pc)
{
    INFO_PRINT("gen_intermediate_code_internal\n");

    CPUState *cs = CPU(cpu);
    CPUPPDLState *env = &cpu->env;
    DisasContext dc1, *dc = &dc1;
    CPUBreakpoint *bp;
    uint16_t *gen_opc_end;
    int j, lj;
    target_ulong pc_start;
    target_ulong next_page_start;
    int num_insns;
    int max_insns;
    int breakpoint = 0;

    target_ulong stop_pc;

    /* generate intermediate code */

    pc_start = tb->pc;
    dc->tb = tb;
    dc->is_jmp = DISAS_NEXT;
    dc->pc = pc_start;
    dc->singlestep_enabled = cs->singlestep_enabled;

    gen_opc_end = tcg_ctx.gen_opc_buf + OPC_MAX_SIZE;
    next_page_start = (pc_start & TARGET_PAGE_MASK) + TARGET_PAGE_SIZE;
    lj = -1;
    num_insns = 0;
    max_insns = tb->cflags & CF_COUNT_MASK;
    if (max_insns == 0)
        max_insns = CF_COUNT_MASK;
    gen_tb_start();

    INFO_PRINT("max_insns: %i\n", max_insns);
    INFO_PRINT("pc_start: %x\n", pc_start);
    do {
        if (search_pc) {
            j = tcg_ctx.gen_opc_ptr - tcg_ctx.gen_opc_buf;
            if (lj < j) {
                lj++;
                while (lj < j)
                    tcg_ctx.gen_opc_instr_start[lj++] = 0;
            }
            tcg_ctx.gen_opc_pc[lj] = dc->pc;
            tcg_ctx.gen_opc_instr_start[lj] = 1;
            tcg_ctx.gen_opc_icount[lj] = num_insns;
        }
        if (num_insns + 1 == max_insns && (tb->cflags & CF_LAST_IO))
            gen_io_start();

        if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP | CPU_LOG_TB_OP_OPT))) {
            tcg_gen_debug_insn_start(dc->pc);
        }
        /* Translation stops when a conditional branch is encountered.
         * Otherwise the subsequent code could get translated several times.
         * Also stop translation when a page boundary is reached.  This
         * ensures prefetch aborts occur at the right place.  */
        disas_ppdl_insn(dc, cpu);
        num_insns++;
        if (dc->pc == end_pc) {
            break;
        }
        if (changed_pc && !singlestep) {
            changed_pc = 0;
            dc->is_jmp = DISAS_NEXT;
            break;
        } else {
            tcg_gen_addi_tl(cpu_pc, cpu_pc, 0x1);
        }
    } while (!dc->is_jmp
             && tcg_ctx.gen_opc_ptr < gen_opc_end
             && !cs->singlestep_enabled
             && !singlestep
             && (dc->pc < next_page_start)
             && num_insns < max_insns);

    INFO_PRINT("num_insns: %i\n", num_insns);

    if (tb->cflags & CF_LAST_IO) {
        gen_io_end();
    }
    if (dc->is_jmp == DISAS_NEXT) {
        dc->is_jmp = DISAS_UPDATE;
        int label = gen_new_label();
        tcg_gen_brcondi_tl(TCG_COND_NE, cpu_is_pc_const_changed, 0x0, label);
        tcg_gen_movi_tl(cpu_pc, dc->pc);
        gen_set_label(label);
        tcg_gen_movi_tl(cpu_is_pc_const_changed, 0x0);
    }
    if (unlikely(cs->singlestep_enabled)) {
        if (dc->is_jmp == DISAS_NEXT) {
            tcg_gen_movi_tl(cpu_pc, dc->pc);
        }
        gen_exception(dc, EXCP_DEBUG);
    } else {
        switch (dc->is_jmp) {
        case DISAS_NEXT:
            gen_goto_tb(dc, 0, dc->pc);
            break;
        default:
        case DISAS_JUMP:
            break;
        case DISAS_UPDATE:
            /* indicate that the hash table must be used
               to find the next TB */
            tcg_gen_exit_tb(0);
            break;
        case DISAS_TB_JUMP:
            /* nothing more to generate */
            break;
        }
    }

    if (singlestep) // в singlestep работаем лишь с одним и тем же TB
        tb_flush(env);

    gen_tb_end(tb, num_insns);
    *tcg_ctx.gen_opc_ptr = INDEX_op_end;

#ifdef DEBUG_DISAS
    if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {
        qemu_log("----------------\n");
        qemu_log("IN: %s\n", lookup_symbol(pc_start));
        log_target_disas(env, pc_start, dc->pc - pc_start,
                         /*dc->thumb | (dc->bswap_code << 1)*/ 0);
        qemu_log("\n");
    }
#endif
    if (search_pc) {
        j = tcg_ctx.gen_opc_ptr - tcg_ctx.gen_opc_buf;
        lj++;
        while (lj <= j)
            tcg_ctx.gen_opc_instr_start[lj++] = 0;
    } else {
        tb->size = dc->pc - pc_start;
        tb->icount = num_insns;
    }

}

void gen_intermediate_code(CPUPPDLState *env, struct TranslationBlock *tb)
{
    gen_intermediate_code_internal(ppdl_env_get_cpu(env), tb, 0);
}

void gen_intermediate_code_pc(CPUPPDLState *env,
                              struct TranslationBlock *tb)
{
    gen_intermediate_code_internal(ppdl_env_get_cpu(env), tb, 1);
}

void ppdl_cpu_dump_state(CPUState *env, FILE *f,
                    fprintf_function cpu_fprintf,
                    int flags)
{
    // [TODO] dump pc and registers
    // [TODO] the reason for exclude is CPUState vs CPUPPDLState
//    int i;
//    uint32_t *regs_pr = env->pr;
//    uint32_t *regs_ar = env->ar;
//    cpu_fprintf(f, "PC=%08x\n", env->pc);
//    for (i = 0; i < 8; ++i) {
//        cpu_fprintf(f, "R%02d=%08x%c", i, regs[i], ' ');
//    }
//    cpu_frpintf(f, "\n");
//    for (i = 0; i < 8; ++i) {
//        cpu_fprintf(f, "R%02d=%08x%c", i, regs[i], ' ');
//    }
}

void restore_state_to_opc(CPUPPDLState *env, TranslationBlock *tb,
                          int pc_pos)
{
    env->pc = tcg_ctx.gen_opc_pc[pc_pos];
}





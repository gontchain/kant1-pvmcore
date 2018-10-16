/*
 * PPDL virtual CPU header.
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#ifndef CPU_PPDL_H
#define CPU_PPDL_H

#define TARGET_LONG_BITS 64
#define HOST_LONG_BITS   64
//#define TARGET_PAGE_BITS 12 /* 4k */
#define TARGET_PAGE_BITS 8 /* 256 */
#define ELF_MACHINE    EM_PPDL

#define CPUArchState struct CPUPPDLState

#include "exec/cpu-defs.h"
#include "qemu-common.h"
#include "exec/cpu-all.h"
#include "exec/exec-all.h"
#include "tcg-op.h"
#include "config.h"
#include "qom/cpu.h"
#include "fpu/softfloat.h"

#define TARGET_HAS_ICE 1

// [TODO] Check if this define is right one for interrupt lines
#define CPU_PPDL_INTERRUPT CPU_INTERRUPT_TGT_EXT_3
#define SIZE_PPDL_MEMORY 0xFFFFF

#define TYPE_PPDL_CPU "ppdl-cpu"

#define PPDL_CPU_CLASS(klass) \
    OBJECT_CLASS_CHECK(PPDLCPUClass, (klass), TYPE_PPDL_CPU)
#define PPDL_CPU(obj) \
    OBJECT_CHECK(PPDLCPU, (obj), TYPE_PPDL_CPU)
#define PPDL_CPU_GET_CLASS(obj) \
    OBJECT_GET_CLASS(PPDLCPUClass, (obj), TYPE_PPDL_CPU)

/**
 * PPDLCPUClass:
 * @parent_realize: The parent class' realize handler.
 * @parent_reset: The parent class' reset handler.
 *
 * A PPDL CPU model.
 */
typedef struct PPDLCPUClass {
    /*< private >*/
    CPUClass parent_class;
    /*< public >*/

    DeviceRealize parent_realize;
    void (*parent_reset)(CPUState *cpu);
} PPDLCPUClass;

extern uint64_t CPU_ID;

#define NB_MMU_MODES    3

enum {
    MMU_NOMMU_IDX = 0,
    MMU_SUPERVISOR_IDX = 1,
    MMU_USER_IDX = 2,
};


#define TARGET_PHYS_ADDR_SPACE_BITS 32
#define TARGET_VIRT_ADDR_SPACE_BITS 32

#define SET_FP_CAUSE(reg, v)    do { (reg) = ((reg) & ~(0x3f << 12)) | ((v & 0x3f) << 12); } while (0)
#define GET_FP_ENABLE(reg)       (((reg) >>  7) & 0x1f)
#define UPDATE_FP_FLAGS(reg, v)   do { (reg) |= ((v & 0x1f) << 2); } while (0)

/* Exceptions indices */
enum {
    EXCP_RESET    = 0x1,
    EXCP_BUSERR   = 0x2,
    EXCP_DPF      = 0x3,
    EXCP_IPF      = 0x4,
    EXCP_TICK     = 0x5,
    EXCP_ALIGN    = 0x6,
    EXCP_ILLEGAL  = 0x7,
    EXCP_INT      = 0x8,
    EXCP_DTLBMISS = 0x9,
    EXCP_ITLBMISS = 0xa,
    EXCP_RANGE    = 0xb,
    EXCP_SYSCALL  = 0xc,
    EXCP_FPE      = 0xd,
    EXCP_TRAP     = 0xe,
    EXCP_NR,
    EXCP_IBE,
    EXCP_DBE
};

/* Supervisor register */
enum {
    SR_SM = (1 << 0),
    SR_TEE = (1 << 1),
    SR_IEE = (1 << 2),
    SR_DCE = (1 << 3),
    SR_ICE = (1 << 4),
    SR_DME = (1 << 5),
    SR_IME = (1 << 6),
    SR_LEE = (1 << 7),
    SR_CE  = (1 << 8),
    SR_F   = (1 << 9),
    SR_CY  = (1 << 10),
    SR_OV  = (1 << 11),
    SR_OVE = (1 << 12),
    SR_DSX = (1 << 13),
    SR_EPH = (1 << 14),
    SR_FO  = (1 << 15),
    SR_SUMRA = (1 << 16),
    SR_SCE = (1 << 17),
};

/* Float point control status register */
enum {
    FPCSR_FPEE = 1,
    FPCSR_RM = (3 << 1),
    FPCSR_OVF = (1 << 3),
    FPCSR_UNF = (1 << 4),
    FPCSR_SNF = (1 << 5),
    FPCSR_QNF = (1 << 6),
    FPCSR_ZF = (1 << 7),
    FPCSR_IXF = (1 << 8),
    FPCSR_IVF = (1 << 9),
    FPCSR_INF = (1 << 10),
    FPCSR_DZF = (1 << 11),
};

/* TLB size */
enum {
    DTLB_WAYS = 1,
    DTLB_SIZE = 64,
    DTLB_MASK = (DTLB_SIZE-1),
    ITLB_WAYS = 1,
    ITLB_SIZE = 64,
    ITLB_MASK = (ITLB_SIZE-1),
};

/* TLB prot */
enum {
    URE = (1 << 6),
    UWE = (1 << 7),
    SRE = (1 << 8),
    SWE = (1 << 9),

    SXE = (1 << 6),
    UXE = (1 << 7),
};

/* check if tlb available */
enum {
    TLBRET_INVALID = -3,
    TLBRET_NOMATCH = -2,
    TLBRET_BADADDR = -1,
    TLBRET_MATCH = 0
};

/* PPDL Hardware Capabilities */
enum {
    PPDL_FEATURE_ONE
};

/**
 * PPDLCPU:
 * @env: #CPUPPDLState
 *
 * A PPDL CPU.
 */

#define SIZE_FIFO_64_64 64
#define SIZE_FIFO_64_32 32
#define SIZE_FIFO_64_9 9
#define SIZE_FIFO_64_6 6
#define SIZE_FIFO_32_3 3

#include "translate_cpu.h"

void RESET(CPUPPDLState *);
void OPER(CPUPPDLState *);
void saveState(CPUPPDLState *out, CPUPPDLState *in);
void compareState(CPUPPDLState *stateBefore, CPUPPDLState *state);

typedef struct PPDLCPU {
    /*< private >*/
    CPUState parent_obj;
    /*< public >*/

    CPUPPDLState env;

    uint32_t feature;       /* CPU Capabilities */
} PPDLCPU;

static inline PPDLCPU *ppdl_env_get_cpu(CPUPPDLState *env)
{
    return container_of(env, PPDLCPU, env);
}

#define ENV_GET_CPU(e) CPU(ppdl_env_get_cpu(e))

#define ENV_OFFSET offsetof(PPDLCPU, env)

PPDLCPU *cpu_ppdl_init(const char *cpu_model);

void cpu_ppdl_list(FILE *f, fprintf_function cpu_fprintf);
int  cpu_ppdl_exec(CPUPPDLState *s);
void ppdl_cpu_do_interrupt(CPUPPDLState *env);
void ppdl_cpu_dump_state(CPUState *cpu, FILE *f,
                         fprintf_function cpu_fprintf, int flags);
int  cpu_ppdl_signal_handler(int host_signum, void *pinfo, void *puc);

int ppdl_cpu_gdb_read_register(CPUState *cpu, uint8_t *buf, int reg);
int ppdl_cpu_gdb_write_register(CPUState *cpu, uint8_t *buf, int reg);
int ppdl_cpu_gdb_read_fifo(CPUState *cpu, uint8_t *buf, int fifo);
int ppdl_cpu_gdb_info_fifo(CPUState *cs, char *buf, int arg);
int ppdl_cpu_gdb_write_fifo(CPUState *cpu, uint8_t *buf, int fifo, int data_size);
int ppdl_cpu_handle_mmu_fault(CPUState *cpu, vaddr address,
                                  int rw, int mmu_idx);

#define cpu_list cpu_ppdl_list
#define cpu_exec cpu_ppdl_exec
#define cpu_gen_code cpu_ppdl_gen_code
#define cpu_signal_handler cpu_ppdl_signal_handler

#ifndef CONFIG_USER_ONLY
extern const struct VMStateDescription vmstate_ppdl_cpu;
void cpu_ppdl_mmu_init(PPDLCPU *cpu);
void ppdl_cpu_unassigned_access(CPUState *cpu, hwaddr addr,
                                bool is_write, bool is_exec, int unused,
                                unsigned size);
hwaddr ppdl_cpu_get_phys_page_debug(CPUState *cs, vaddr addr);
int cpu_ppdl_get_phys_nommu(PPDLCPU *cpu,
                                hwaddr *physical,
                                int *prot, target_ulong address, int rw);
int cpu_ppdl_get_phys_code(PPDLCPU *cpu,
                               hwaddr *physical,
                               int *prot, target_ulong address, int rw);
int cpu_ppdl_get_phys_data(PPDLCPU *cpu,
                               hwaddr *physical,
                               int *prot, target_ulong address, int rw);
#endif

uint64_t pd_lsh(uint64_t aVal, uint64_t aOffs);
uint64_t pd_rsh(uint64_t aVal, uint64_t aOffs);

static inline CPUPPDLState *cpu_init(const char *cpu_model)
{
    PPDLCPU *cpu = cpu_ppdl_init(cpu_model);
    if (cpu) {
        cpu->env.cpu_id = CPU_ID;
        return &cpu->env;
    }
    return NULL;
}

#include "exec/cpu-all.h"

static inline void cpu_get_tb_cpu_state(CPUPPDLState *env,
                                        target_ulong *pc,
                                        target_ulong *cs_base, int *flags)
{
    *pc = env->pc;
    *cs_base = 0;
}

static inline int cpu_mmu_index(CPUPPDLState *env)
{
    return MMU_USER_IDX;
}

#include "exec/exec-all.h"

static inline target_ulong cpu_get_pc(CPUPPDLState *env)
{
    return env->pc;
}

#endif /* CPU_PPDL_H */

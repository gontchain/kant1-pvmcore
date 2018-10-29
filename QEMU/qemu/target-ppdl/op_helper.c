/*
 * PPDL helper routines
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "cpu.h"
#include "exec/helper-proto.h"
#include "exec/cpu_ldst.h"
#ifdef TLM
#include "tlm.h"
#endif

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wformat-zero-length"

#if defined(CONFIG_DEBUG)
#   define ERROR_PRINT(...) (debug) ? printf("\t\t::EXEC ERROR:: error in " __VA_ARGS__ "\n") : printf("");
#   define INFO_PRINT(...) (debug) ? printf("\t\t::EXEC INFO:: " __VA_ARGS__ ) : printf("");
#else
#   define ERROR_PRINT(...)
#   define INFO_PRINT(...)
#endif

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

extern int print_ticks;
extern int use_tracer;
extern int use_ctracer;
extern int use_regtracer;
uint64_t tick = 0;
extern void PrintDisasmLine(CPUArchState* env, uint32_t aCurPc, uint32_t aTicks);
int gdb_fd;
int gdb_interrupted = 0;
#ifdef __CYGWIN__
#define SIGINT_CHECK_PERIOD 500
int gdb_port;
int sigint_check_counter = 0;
#endif

void HELPER(wait_for_gdb)(uint64_t time)
{
#ifdef TLM
    tlm_wait_for_gdb_cb(tlm_opaque, time);
#endif
}

void HELPER(next_context)(uint64_t time_ns)
{
#ifdef TLM
   tlm_next_context_cb(tlm_opaque, time_ns);
#endif
}

static void raise_exception(CPUPPDLState *env, int tt)
{
    PPDLCPU *cpu = ppdl_env_get_cpu(env);
    CPUState *cs = CPU(cpu);

    cs->exception_index = tt;
    cpu_loop_exit(cs);
}

void HELPER(exception)(CPUPPDLState *env, uint32_t excp)
{
    raise_exception(env, excp);
}

void HELPER(tracer)(CPUPPDLState *env, uint32_t arg)
{
    static int32_t prev_tick = 0;
    if (print_ticks == 0) {
        if (use_regtracer || use_ctracer)
            compareState(&envSaved, env);
        saveState(&envSaved, env);
        if (use_tracer || use_ctracer) {
            PrintDisasmLine(env, env->pc, tick);
            if (tick > (prev_tick + 1))
                printf("      +%ld wait\n", tick - prev_tick - 1);
            prev_tick = tick;
        }
    }
    tick++;
}

void HELPER(gdb_handling)(CPUPPDLState *env)
{
#ifdef CONFIG_USER_ONLY
    PPDLCPU *cpu = ppdl_env_get_cpu(env);
    CPUState *cs = CPU(cpu);
    char buf[256] = {0};
#ifdef __CYGWIN__
    int n, i = 0;
    char name[255];
	// Getting user's Temp folder path and convert it to Cygwin-like path
    sprintf(name, "%s\\..\\Local\\Temp\\stop.%d", getenv("APPDATA"), gdb_port);
	while(name[i]) {
		if (name[i] == '\\')
			name[i] = '/';
		i++;
	}
	if (isalpha(name[0]) && name[1] == ':') {
		char fixed_drive_name[255] = {0};
		sprintf(fixed_drive_name, "/cygdrive/%c/%s", name[0] | 0x20, name + 3);
		strcpy(name, fixed_drive_name);
	}
    if (sigint_check_counter == SIGINT_CHECK_PERIOD) {
        if ( (n = open (name, O_RDONLY)) > 0 ) {
            buf[0] = 0x03;
            close(n);
            remove(name);
        }
        sigint_check_counter = 0;
    }
    else
        sigint_check_counter++;
#else
    int n = read(gdb_fd, buf, 256);
#endif
    if (n > 0) {
        if (buf[0] == 0x03) {
            gdb_interrupted = 1;
            cpu_exit(cs);
        }
    }
#endif
}

void HELPER(debug)()
{
    INFO_PRINT("Hello, World!\n");
}

void HELPER(print_value)(uint64_t val) // отладочный helper, позволяющий отображать любую TCGv переменную
{
    INFO_PRINT("value: 0x%" PRIX64 "\n", val);
}

void HELPER(print)(CPUPPDLState *env)
{
    PPDLCPU *cpu = ppdl_env_get_cpu(env);

    INFO_PRINT("pc: %" PRIX32 "\n", cpu->env.pc);
}

void HELPER(error_message)(CPUPPDLState *env, uint64_t index, uint64_t data)
{
    FILE *log_file = fopen("qemu.err.log", "w");
    switch (index) {
        case 1:
            //printf("@\n");
            fprintf(log_file, "@\n");
            break;
    }
    fclose(log_file);
}

int64_t HELPER(sign64)(uint64_t aVal)
{
	return (signed)aVal;
}

uint64_t HELPER(set_bitfield)(uint64_t dst, uint64_t start, uint64_t end, uint64_t aVal)
{
    start = min(start, end);
    end = max(start, end) + 1;
    int diff = (end - start);
    uint64_t mask = (diff == sizeof(uint64_t)* 8) ? (uint64_t)-1 : ((uint64)1 << diff) - 1;
    uint64_t masked_val = *((uint64_t*)dst) & ~(mask << start);
    uint64_t new_val = ((uint64_t)aVal & mask) << start;
    return (uint64_t)(masked_val | new_val);
}

uint64_t HELPER(get_bitfield)(uint64_t aVal, uint64_t start, uint64_t end)
{
    start = min(start, end);
    end = max(start, end) + 1;
    int diff = (end - start);
    uint64_t mask = (diff == sizeof(uint64_t)* 8) ? (uint64_t)-1 : ((uint64)1 << diff) - 1;
    uint64_t res = (aVal >> start) & mask;
    return res;
}

#if !defined(CONFIG_USER_ONLY)
void ppdl_cpu_unassigned_access(CPUState *cs, hwaddr addr,
                                bool is_write, bool is_exec, int unused,
                                unsigned size)
{
    PPDLCPU *cpu = PPDL_CPU(cs);
    CPUPPDLState *env = &cpu->env;

    if (is_exec) {
        // printf("Exception EXCP_IBE\n");
        raise_exception(env, EXCP_IBE);
    } else {
        // printf("Exception EXCP_DBE\n");
        raise_exception(env, EXCP_DBE);
    }
}
#endif

/*
 * PPDL helper routines
 *
 * Copyright (c) 2015 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "cpu.h"
#include "exec/helper-proto.h"
#include "exec/cpu_ldst.h"
#include "qemu/trace.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#pragma GCC diagnostic ignored "-Wformat-zero-length"

#if defined(CONFIG_DEBUG)
#   define ERROR_PRINT(...) (debug) ? printf("\t\t::EXEC ERROR:: error in " __VA_ARGS__ "\n") : printf("");
#   define INFO_PRINT(...) (debug) ? printf("\t\t::EXEC INFO:: " __VA_ARGS__ ) : printf("");
#else
#   define ERROR_PRINT(...)
#   define INFO_PRINT(...)
#endif

#define START_PPDL_RAM 0x20000000

#if defined(CONFIG_LINUX_USER)
#define START_SPECIAL_MEM 0x40000000
#define START_SPECIAL_MEM_STR "0x40000000"
#define END_SPECIAL_MEM 0x40004000
#define END_SPECIAL_MEM_STR "0x40004000"
#include "addr_table.h"
#define CUSTOM_MEMORY
#ifdef CUSTOM_MEMORY
void *customMemory = NULL;
uint64_t sizeCustomMemory;
void *customRAM = NULL;
uint64_t sizeCustomRAM;
#endif
#endif

/* load */
uint64_t HELPER(mem_ld64)(CPUPPDLState *env, uint64_t addr) {
    uint64_t _addr = addr>>2;
#ifndef TLM
    /*
     * Memory of devices is from 0x10000000 to 0x1FFFFFFF
     */
    if ((_addr > 0x10000000) && (_addr < 0x1FFFFFFF)) {
        printf("warning: access to memory of devices: %" PRIX64 "\n", _addr);
        return 0;
    }
#endif
    uint64_t data;
    if (_addr >= START_PPDL_RAM) {
#ifdef CONFIG_USER_ONLY
        if ( (_addr >= START_SPECIAL_MEM) && (_addr <= END_SPECIAL_MEM) ) {
            init_struct_addrInfo();
            printf("warning: special memory address: %" PRIX64 " from [" START_SPECIAL_MEM_STR ", " END_SPECIAL_MEM_STR "] %s\n", _addr, get_addr_description(_addr));
            return 0;
        }
        if (_addr - START_PPDL_RAM > sizeCustomRAM) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return 0;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_ld64: addr: %" PRIX64 "\n", addr);
        data = *(uint64_t*)(customRAM + 0x04*(_addr - START_PPDL_RAM)); // WARNING! customRAM + addr - 4*START_PPDL_RAM does not work!
#else
        INFO_PRINT("mem_ld64: addr: %" PRIX64 "\n", addr);
        data = cpu_ldq_data(env, addr);
#endif
        INFO_PRINT("mem_ld64: data: %" PRIX64 "\n", data);
    } else {
#ifdef CONFIG_USER_ONLY
        if (_addr > sizeCustomMemory) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return 0x0;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_ld64: addr: %" PRIX64 "\n", addr);
        data = *(uint64_t*)(customMemory + addr);
#else
        INFO_PRINT("mem_ld64: addr: %" PRIX64 "\n", addr);
        data = cpu_ldq_data(env, addr);
#endif
        INFO_PRINT("mem_ld64: data: %" PRIX64 "\n", data);
    }
    if (use_memtracer & qemu_mem_mask(_addr))
        printf("mem load 64: addr: %" PRIX64 ", data: %" PRIX64 "\n", _addr, data);
    return data;
}

uint64_t HELPER(mem_ld32)(CPUPPDLState *env, uint64_t addr) {
    uint64_t _addr = addr>>2;
#ifndef TLM
    /*
     * Memory of devices is from 0x10000000 to 0x1FFFFFFF
     */
    if ((_addr > 0x10000000) && (_addr < 0x1FFFFFFF)) {
        printf("warning: access to memory of devices: %" PRIX64 "\n", _addr);
        return 0;
    }
#endif
    uint64_t data;
    if (_addr >= START_PPDL_RAM) {
#ifdef CONFIG_USER_ONLY
        if ( (_addr >= START_SPECIAL_MEM) && (_addr <= END_SPECIAL_MEM) ) {
            init_struct_addrInfo();
            printf("warning: special memory address: %" PRIX64 " from [" START_SPECIAL_MEM_STR ", " END_SPECIAL_MEM_STR "] %s\n", _addr, get_addr_description(_addr));
            return 0;
        }
        if (_addr - START_PPDL_RAM > sizeCustomRAM) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return 0;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_ld32: addr: %" PRIX64 "\n", addr);
        data = *(uint32_t*)(customRAM + 0x04*(_addr - START_PPDL_RAM)); // WARNING! customRAM + addr - 4*START_PPDL_RAM does not work!
#else
        INFO_PRINT("mem_ld32: addr: %" PRIX64 "\n", addr);
        data = cpu_ldl_data(env, addr);
#endif
        INFO_PRINT("mem_ld32: data: %" PRIX64 "\n", data);
    } else {
#ifdef CONFIG_USER_ONLY
        if (_addr > sizeCustomMemory) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return 0x0;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_ld32: addr: %" PRIX64 "\n", addr);
        data = *(uint32_t*)(customMemory + addr);
#else
        INFO_PRINT("mem_ld32: addr: %" PRIX64 "\n", addr);
        data = cpu_ldl_data(env, addr);
#endif
        INFO_PRINT("mem_ld32: data: %" PRIX64 "\n", data);
    }
    if (use_memtracer & qemu_mem_mask(_addr))
        printf("mem load 32: addr: %" PRIX64 ", data: %" PRIX64 "\n", _addr, data);
    return data;
}

/* store */
void HELPER(mem_st64)(CPUPPDLState *env, uint64_t addr, uint64_t data) {
    uint64_t _addr = addr>>2;
    if (use_memtracer & qemu_mem_mask(_addr))
        printf("mem store 64: addr: %" PRIX64 ", data: %" PRIX64 "\n", _addr, data);
#ifndef TLM
    /*
     * Memory of devices is from 0x10000000 to 0x1FFFFFFF
     */
    if ((_addr > 0x10000000) && (_addr < 0x1FFFFFFF)) {
        printf("warning: access to memory of devices: %" PRIX64 "\n", _addr);
        return;
    }
#endif
    if (_addr >= START_PPDL_RAM) {
#ifdef CONFIG_USER_ONLY
        if ( (_addr >= START_SPECIAL_MEM) && (_addr <= END_SPECIAL_MEM) ) {
            init_struct_addrInfo();
            printf("warning: special memory address: %" PRIX64 " from [" START_SPECIAL_MEM_STR ", " END_SPECIAL_MEM_STR "] %s\n", _addr, get_addr_description(_addr));
            return;
        }
        if (_addr - START_PPDL_RAM > sizeCustomRAM) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_st64: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        *(uint64_t*)(customRAM + 0x04*(_addr - START_PPDL_RAM)) = data; // WARNING! customRAM + addr - 4*START_PPDL_RAM does not work!
#else
        INFO_PRINT("mem_st64: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        cpu_stq_data(env, addr, data);
#endif
    } else {
#ifdef CONFIG_USER_ONLY
        if (_addr > sizeCustomMemory) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_st64: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        *(uint64_t*)(customMemory + addr) = data;
#else
        INFO_PRINT("mem_st64: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        cpu_stq_data(env, addr, data);
#endif
    }
}

void HELPER(mem_st32)(CPUPPDLState *env, uint64_t addr, uint64_t data) {
    uint64_t _addr = addr>>2;
    if (use_memtracer & qemu_mem_mask(_addr))
        printf("mem store 32: addr: %" PRIX64 ", data: %" PRIX64 "\n", _addr, data);
#ifndef TLM
    /*
     * Memory of devices is from 0x10000000 to 0x1FFFFFFF
     */
    if ((_addr > 0x10000000) && (_addr < 0x1FFFFFFF)) {
        printf("warning: access to memory of devices: %" PRIX64 "\n", _addr);
        return;
    }
#endif
    if (_addr >= START_PPDL_RAM) {
#ifdef CONFIG_USER_ONLY
        if ( (_addr >= START_SPECIAL_MEM) && (_addr <= END_SPECIAL_MEM) ) {
            init_struct_addrInfo();
            printf("warning: special memory address: %" PRIX64 " from [" START_SPECIAL_MEM_STR ", " END_SPECIAL_MEM_STR "] %s\n", _addr, get_addr_description(_addr));
            return;
        }
        if (_addr - START_PPDL_RAM > sizeCustomRAM) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_st32: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        *(uint32_t*)(customRAM + 0x04*(_addr - START_PPDL_RAM)) = data; // WARNING! customRAM + addr - 4*START_PPDL_RAM does not work!
#else
        INFO_PRINT("mem_st32: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        cpu_stl_data(env, addr, data);
#endif
    } else {
#ifdef CONFIG_USER_ONLY
        if (_addr > sizeCustomMemory) {
            printf("warning: invalid memory address: %" PRIX64 " is out of [0x0, 0xBFFFF] and [0x20000000, 0x3FFFFFFF]\n", _addr);
            return;
        }
#endif
#ifdef CUSTOM_MEMORY
        INFO_PRINT("custom::mem_st32: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        *(uint32_t*)(customMemory + addr) = data;
#else
        INFO_PRINT("mem_st32: addr: %" PRIX64 ", data: %" PRIX64 "\n", addr, data);
        cpu_stl_data(env, addr, data);
#endif
    }
}

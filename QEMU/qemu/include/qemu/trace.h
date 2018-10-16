/*
 * Register / Memory Tracing support header
 *
 * Copyright (c) 2017 Alexander Gerasimov <samik.mechanic@gmail.com>
 *
 */

#ifndef QEMU_TRACE_H
#define QEMU_TRACE_H

#include <stdbool.h>
#include <stdio.h>
#include "qemu/trace_regs_defs.h"

typedef struct QEMURegTraceItem {
    const char *name;
    int index;
} QEMURegTraceItem;

extern int qemu_reg_trace_list[REGTRACE_LIST_LEN];
extern const QEMURegTraceItem qemu_reg_trace_items[];
extern char qemu_mem_trace_list[100][22];

/* Returns true if register mask is set in the current regisers tracing list
 */
static inline bool qemu_reg_mask(const char* reg, int idx)
{
    const QEMURegTraceItem *item;
    int reg_index, i = 0;
    char reg_name[REGTRACE_MAX_LEN];

    if (use_ctracer)
        return 1;
    if (idx == -1)
        sprintf(reg_name, "%s", reg);
    else
        sprintf(reg_name, "%s%d", reg, idx);
    for (item = qemu_reg_trace_items; item->index != -1; item++) {
        if (!strcmp(item->name, reg_name)) {
            reg_index = item->index;
            goto found;
        }
    }
    return 0;
found:
    for (i = 0; qemu_reg_trace_list[i] != -1; i++) {
        if (reg_index == qemu_reg_trace_list[i]) {
            return 1;
        }
    }
    return 0;
}

/* Returns true if requested address is present in the current memory tracing list
 */
static inline bool qemu_mem_mask(const uint64_t addr)
{
    char addrstring[10] = {'\0'};
    int addr_low = 0, addr_hi = 0, i = 0;
    char *p, *p1, *p2;

    for (i = 0; strcmp(qemu_mem_trace_list[i], "NA"); i++) {
        p = qemu_mem_trace_list[i];
        p1 = strchr(p, '\0');
        p2 = strchr(p, '-');
        if ((p2 < p1) && (p2 > p)) {
            strncpy(addrstring, p, p2-p);
            addr_low = (int)strtol(addrstring, NULL, 0);
            strncpy(addrstring, p2+1, p1-p2-1);
            addr_hi = (int)strtol(addrstring, NULL, 0);
            if ((addr >= addr_low) && (addr <= addr_hi))
                return 1;
        } else {
            strncpy(addrstring, p, p1-p);
            addr_low = (int)strtol(addrstring, NULL, 0);
            if (addr == addr_low)
                return 1;
        }
    }
    return 0;
}

void qemu_str_to_trace_list(const char *str);
void qemu_str_to_memtrace_list(const char *str);
void qemu_print_reg_trace_usage(void);
void qemu_print_mem_trace_usage(void);

#endif // QEMU_TRACE_H

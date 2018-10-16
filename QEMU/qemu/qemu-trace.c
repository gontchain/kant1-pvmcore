/*
 * Register / Memory Tracing support
 *
 * Copyright (c) 2017 Alexander Gerasimov <samik.mechanic@gmail.com>
 *
 */

#include "qemu-common.h"
#include "qemu/trace.h"
#include "qemu/trace_regs.h"

#define RAM_BASE_ADDR 0x0
#define RAM_MAX_ADDR  0xBFFFF
#define DDR_BASE_ADDR 0x20000000
#define DDR_MAX_ADDR  0x3FFFFFFF

static int regmatch(const char *s1, int n, const char *s2)
{
    if (strlen(s2) != n) {
        return 0;
    }
    return memcmp(s1, s2, n) == 0;
}

static int addrmatch(const char *s, const int n) {
    char addrstring[n];
    int addr, i = 0;
    strncpy(addrstring, s, n);
    if (strlen(addrstring) > 10)
        return 0;
    for (i = 2; i < n; i++) {
        if (((addrstring[i] >= '0') && (addrstring[i] <= '9'))
            | ((addrstring[i] >= 'a') && (addrstring[i] <= 'f'))
            | ((addrstring[i] >= 'A') && (addrstring[i] <= 'F'))) {
            continue;
        } else {
            return 0;
        }
    }
    addr = (int)strtol(addrstring, NULL, 0);
    if ((addr >= RAM_BASE_ADDR) && (addr <= RAM_MAX_ADDR) | (addr >= DDR_BASE_ADDR) && (addr <= DDR_MAX_ADDR)) {
        return 1;
    }
    return 0;
}

/* takes a comma separated list of general-purpose registers and parses it to trace mask. Return 0 if error. */
void qemu_str_to_trace_list(const char *str)
{
    const QEMURegTraceItem *item;
    int counter;
    const char *p, *p1;

    p = str;
    counter = 0;
    for (;;) {
        p1 = strchr(p, ',');
        if (!p1) {
            p1 = p + strlen(p);
        }
        if (regmatch(p,p1-p,"help")) {
            qemu_print_reg_trace_usage();
            exit(-1);
            return;
        }
        if (regmatch(p,p1-p,"all")) {
            for (item = qemu_reg_trace_items; item->index != -1; item++) {
                qemu_reg_trace_list[counter++] = item->index;
            }
            break;
        } else {
            for (item = qemu_reg_trace_items; item->index != -1; item++) {
                if (regmatch(p, p1 - p, item->name)) {
                    goto found;
                }
            }
            printf("Invalid trace list values.\n");
            qemu_print_reg_trace_usage();
            exit(-1);
            return;
        }
    found:
        qemu_reg_trace_list[counter++] = item->index;
        if (*p1 != ',') {
            break;
        }
        p = p1 + 1;
    }
    qemu_reg_trace_list[counter] = -1;
}

void qemu_str_to_memtrace_list(const char *str)
{
    int counter;
    const char *p, *p1, *p2;
    p = str;
    counter = 0;
    for (;;) {
        p1 = strchr(p, ',');
        if (!p1) {
            p1 = p + strlen(p);
        }
        if (regmatch(p,p1-p,"help")) {
            qemu_print_mem_trace_usage();
            exit(-1);
            return;
        }
        if (regmatch(p,p1-p,"all")) {
            strcpy(qemu_mem_trace_list[0], "0x0-0xBFFFF");
            strcpy(qemu_mem_trace_list[1], "0x20000000-0x3FFFFFFF");
            strcpy(qemu_mem_trace_list[2], "NA");
            return;
        } else {
            if (!strncmp(p, "0x", 2)) {
                p2 = strchr(p, '-');
                if ((p2 < p1) && (p2 > p)) {
                    if (addrmatch(p, p2-p) && addrmatch(p2+1, p1-p2-1))
                        goto found;
                } else {
                    if (addrmatch(p, p1-p))
                        goto found;
                }
            }
            printf("Invalid trace list values.\n");
            qemu_print_mem_trace_usage();
            exit(-1);
            return;
        }
    found:
        strncpy(qemu_mem_trace_list[counter++], p, p1-p);
        if (*p1 != ',') {
            break;
        }
        p = p1 + 1;
    }
    strcpy(qemu_mem_trace_list[counter], "NA");
}

void qemu_print_reg_trace_usage(void)
{
    const QEMURegTraceItem *item;
    printf("Register trace items (comma separated):\nall\n");
    for (item = qemu_reg_trace_items; item->index != -1; item++) {
        printf("%-16s", item->name);
    }
    printf("\n\nExample usage:\n");
    printf("nmc-qemu -regtrace all\n");
    printf("nmc-qemu -regtrace gr0,ar7,wbuf25\n");
}

void qemu_print_mem_trace_usage(void)
{
    printf("Memory trace items (comma separated):\n");
    printf("\tall\n\t0x[F...]\n\t0x[F...]-0x[F...]\n");
    printf("\nAvailable address spaces:\n");
    printf("\t1) RAM [ 0x%X - 0x%X ]\n\t2) DDR [ 0x%X - 0x%X ]\n", RAM_BASE_ADDR, RAM_MAX_ADDR, DDR_BASE_ADDR, DDR_MAX_ADDR);
}

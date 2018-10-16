/*
 * QEMU PPDL CPU
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "bitfield.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

void set_bitfield(uint64_t* dst, uint64_t start, uint64_t end, uint64_t aVal)
{
    start = min(start, end);
    end = max(start, end) + 1;
    int diff = (end - start);
    uint64_t mask = (diff == sizeof(uint64_t)* 8) ? (uint64_t)-1 : ((uint64)1 << diff) - 1;
    uint64_t masked_val = *((uint64_t*)dst) & ~(mask << start);
    uint64_t new_val = ((uint64_t)aVal & mask) << start;
    *dst = (uint64_t)(masked_val | new_val);
}

uint64_t get_bitfield(uint64_t aVal, uint64_t start, uint64_t end)
{
    start = min(start, end);
    end = max(start, end) + 1;
    int diff = (end - start);
    uint64_t mask = (diff == sizeof(uint64_t)* 8) ? (uint64_t)-1 : ((uint64)1 << diff) - 1;
    uint64_t res = (aVal >> start) & mask;
    return res;
}

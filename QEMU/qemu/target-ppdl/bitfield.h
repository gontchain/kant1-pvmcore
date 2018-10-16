/*
 * QEMU PPDL CPU
 *
 * Copyright (c) 2014 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#ifndef PPDL_BITFIELD_H
#define PPDL_BITFIELD_H

#include "qemu-common.h"

void set_bitfield(uint64_t*, uint64_t, uint64_t, uint64_t);
uint64_t get_bitfield(uint64_t, uint64_t, uint64_t);

#endif

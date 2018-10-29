/*
 * QEMU EVM
 *
 * Copyright (c) 2018 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 *
 */

#include "evm.h"
#include <stdlib.h>

void RunProgram(int argc, const char **argv/*char prog_name, unsigned int start_addr, void Environment*/) {
    vl_main(0, 1, 1, argc, argv, NULL);
}

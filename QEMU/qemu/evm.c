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

extern unsigned int load_addr;
extern int vl_main(int ignore_sigint, int no_sdl, int no_gui_timer,
            int argc, char **argv, char **envp);

void RunProgram(int argc, const char **argv, unsigned int start_addr/*char prog_name, unsigned int start_addr, void Environment*/) {
    load_addr = start_addr;
    vl_main(0, 1, 1, argc, (char **)argv, NULL);
}

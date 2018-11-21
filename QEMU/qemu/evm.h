/*
 * QEMU EVM
 *
 * Copyright (c) 2018 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 *
 */

#ifndef EVM_EVM_H
#define EVM_EVM_H


#ifdef __cplusplus
extern "C"{
#endif

void RunProgram(int argc, const char **argv, unsigned int start_addr/*char prog_name, unsigned int start_addr, void Environment*/);

#ifdef __cplusplus
}
#endif
#endif // EVM_EVM_H

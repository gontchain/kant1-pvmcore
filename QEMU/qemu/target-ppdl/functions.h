/*
 * QEMU PPDL CPU
 *
 * Copyright (c) 2018 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#ifndef FUNTIONS_H
#define FUNTIONS_H

#include <stdio.h>
#include "qemu-common.h"
#include "func_shared.h"
#include "Keccak.h"

void result_message(CPUArchState*);
void SaveToStorage(CPUArchState*, uint32);
void UseGas(CPUArchState*, uint64);
void DoCompare(CPUArchState*, uint32);
void LoadFromStorage(CPUArchState*, uint32);
void KeccakAlg(CPUArchState*, uint32, uint32);
uint64 GetElfSize(CPUArchState*);
void initialize(void);
void finalize(void);

#endif // FUNTIONS_H

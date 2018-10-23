/*
 * QEMU PPDL CPU
 *
 * Copyright (c) 2018 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "functions.h"

void result_message(CPUArchState* env) {
    if ((signed)(env->gas_available) == -1) {
        printf("\ngas limit error\n");
        exit(-1);
    }

    int32_t offs = Pop(env);
    int32_t size = Pop(env);
    printf("0x");
    int i;
    for (i = 0; i < size; i++) {
        int val = env->data_bus[i + offs];
        printf("%02X", val);
    }
    printf("\n");
}

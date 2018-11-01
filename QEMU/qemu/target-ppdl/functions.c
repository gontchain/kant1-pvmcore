/*
 * QEMU PPDL CPU
 *
 * Copyright (c) 2018 Perov Maxim <coder@frtk.ru>
 *
 * [TODO] Add some description
 */

#include "functions.h"
#include "v_bignum.h"
#include "gascost.h"
#include "Keccak.h"

struct Storage {
    uint32 key;
    uint64 value[4];
    struct Storage* next;
};

struct Storage* mainStorage = NULL;

void initialize() {
    if (mainStorage == NULL) {
        mainStorage = (struct Storage*)malloc(sizeof(struct Storage));
        mainStorage->key = -1;
        int i;
        for (i = 0; i < 4; i++)
            mainStorage->value[i] = 0x0;
        mainStorage->next = NULL;
    }
}

void finalize() {
    if (mainStorage != NULL) {
        struct Storage* curr = mainStorage->next;
        while (curr) {
            struct Storage* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        free(mainStorage);
    }
}

void result_message(CPUArchState* env) {
    finalize();
    if (env->gas_available[0] == 0)
    {
      printf("\ngas limit error\n");
      exit(-1);
    }
    uint64 offs = 0x0, size = 0x0, return_byte = 0x0;
    int i;
    // getting return offset and size (lower 64bit)
    for (i = 0; i < 8; i++) {
      return_byte = (env->stack_arr[env->sp-3] >> (8*i)) & 0xff;
      return_byte = return_byte << 8*(7-i);
      offs = offs | return_byte;
    }
    for (i = 0; i < 8; i++) {
      return_byte = (env->stack_arr[env->sp-7] >> (8*i)) & 0xff;
      return_byte = return_byte << 8*(7-i);
      size = size | return_byte;
    }
    env->sp -= 8;
    printf("0x");
    for (i = 0; i < size; i++)
    {
      uint8 val = env->data_bus[i + offs];
      printf("%02X", val);
    }
    printf("\n");
    exit(0);
}

void SaveToStorage(CPUArchState* env, uint32 offs) {
    struct Storage* node = mainStorage;
    struct Storage* tail;
    bool isFound = false;
    int i, j;
    int32 sp = env->sp;
    uint64 *data_val = &(env->stack_arr[sp-3]);
    uint64 data_tmp[4], byte;
    for (j = 0; j < 4; j++) {
        data_tmp[j] = 0;
        for (i = 0; i < 8; i++) {
            byte = ((data_val[3-j] >> (8*i)) & 0xFF) << (8*(7-i));
            data_tmp[j] |= byte;
        }
    }
    env->sp = sp - 4; // update sp
    while (node != NULL) {
        if (node->key == -1 | node->key == offs) { // if entry is empty or address is found
            isFound = true;
            break;
        }
        tail = node;
        node = node->next;
    }
    if (isFound) { // overwrite
        node->key = offs;
        for (i = 0; i < 4; i++) {
            node->value[i] = data_tmp[i];
        }
    } else { // create new entry
        tail->next = (struct Storage*)malloc(sizeof(struct Storage));
        tail->next->key = offs;
        for (i = 0; i < 4; i++) {
            tail->next->value[i] = data_tmp[i];
        }
        tail->next->next = NULL;
    }
}

void DoArithm(CPUArchState* env, uint32 opcode) {
    int i, arg_count = 0;
    int32 sp = env->sp;
    uint64 *arg1, *arg2, *arg3, *ret;
    VBigDig VBIGNUM(a, 256), VBIGNUM(b, 256), VBIGNUM(c, 256), VBIGNUM(tmp, 256), VBIGNUM(tmp2, 256);
    // printf("opcode: %x\n", opcode);
    // printf("stack: \n");
    // for (i = sp; i >=0; i--) {
    //   printf("%d: %llx\n", i, env->stack_arr[i]);
    // }
    // printf("\n");
    switch (opcode) {
        case 1 ... 7:
        case 10:
        case 11:
            arg1 = &(env->stack_arr[sp-3]);
            arg2 = &(env->stack_arr[sp-7]);
            v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1));
            v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2));
            // printf("a: ");
            // v_bignum_print_hex_lf(a);
            // printf("b: ");
            // v_bignum_print_hex_lf(b);
            sp = sp - (2*4 - 1);
            break;
        case 8:
        case 9:
            arg1 = &(env->stack_arr[sp-3]);
            arg2 = &(env->stack_arr[sp-7]);
            arg3 = &(env->stack_arr[sp-11]);
            v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1));
            v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2));
            v_bignum_set_bignum(c, v_bignum_reg_to_bignum(arg3));
            // printf("a: ");
            // v_bignum_print_hex_lf(a);
            // printf("b: ");
            // v_bignum_print_hex_lf(b);
            // printf("c: ");
            // v_bignum_print_hex_lf(c);
            sp = sp - (3*4 - 1);
            break;
    }
    ret = &(env->stack_arr[sp]); // set result pointer in stack
    env->sp = sp + 3; // update sp
    switch (opcode) {
        case 0: // STOP
            //CheckError("@");
            helper_error_message(env, 1, 0);
            break;
        case 1: // ADD
            UseGas(env, STEPGAS2);
            v_bignum_add(a, b);
            break;
        case 2: // MUL
            UseGas(env, STEPGAS3);
            v_bignum_mul(a, b);
            break;
        case 3: // SUB
            UseGas(env, STEPGAS2);
            v_bignum_sub(a, b);
            break;
        case 4: // DIV
        case 5: // SDIV
            UseGas(env, STEPGAS3);
            v_bignum_div(a, b, tmp);
            break;
        case 6: // MOD
            UseGas(env, STEPGAS3);
            v_bignum_mod(a, b);
          break;
        case 7: // SMOD
            UseGas(env, STEPGAS3);
            v_bignum_set_zero(tmp);
            // set signum multiplier
            if (v_bignum_bit_test(a, 255)) {
                v_bignum_set_one(tmp2);
                v_bignum_sub(tmp, tmp2); // -1
            } else {
                v_bignum_set_one(tmp); // 1
            }
            v_bignum_mod(a, b);
            v_bignum_mul(a, tmp); // apply signum
            break;
        case 8: // ADDMOD
            UseGas(env, STEPGAS4);
            v_bignum_add(a, b);
            v_bignum_mod(a, c);
            break;
        case 9: // MULMOD
            UseGas(env, STEPGAS4);
            v_bignum_mul(a, b);
            v_bignum_mod(a, c);
            break;
        case 10: // EXP
            UseGas(env, STEPGAS5);
            if (v_bignum_eq_zero(b)) {
                v_bignum_set_one(a);
            } else {
                v_bignum_set_one(tmp);
                v_bignum_set_bignum(tmp2, a);
                while (!v_bignum_eq_one(b)) {
                    v_bignum_mul(a, tmp2);
                    v_bignum_sub(b, tmp);
                }
            }
            break;
        case 11: // SIGNEXTEND
            UseGas(env, STEPGAS3);
            v_bignum_set_bignum(tmp, b);
            uint8 byte = arg1[0] >> 7*8 & 0xFF;
            if (byte < 31) {
                uint8 t = 8*byte + 7;
                for (i = t+1; i < 256; i++) {
                    if (v_bignum_bit_test(b, t))
                        v_bignum_bit_set(tmp, i);
                    else
                        v_bignum_bit_clear(tmp, i);
                }
            }
            v_bignum_set_bignum(a, tmp);
            break;
      }
      v_bignum_bignum_to_reg(ret, a);
      // printf("r: ");
      // v_bignum_print_hex_lf(a);
}

void UseGas(CPUArchState* env, uint64 value) {
    uint64 *gas = env->gas_available;
    uint64 ret[4];
    VBigDig VBIGNUM(x, 256), VBIGNUM(y, 64);
    char value_string[35];
    v_bignum_set_bignum(x, v_bignum_reg_to_bignum(gas));
    sprintf(value_string, "0x%llx", value);
    v_bignum_set_string_hex(y, value_string);
    if (v_bignum_gt(y, x)) {
        v_bignum_set_zero(x);
        v_bignum_bignum_to_reg(gas, x);
        printf("out of gas\n");
        //CheckError("@");
        helper_error_message(env, 1, 0);
    } else {
        v_bignum_sub(x, y);
        v_bignum_bignum_to_reg(gas, x);
    }
}

void DoCompare(CPUArchState* env, uint32 opcode) {
    int i, arg_count = 0;
    int32 sp = env->sp;
    uint64 *arg1, *arg2, *arg3, *ret;
    VBigDig VBIGNUM(a, 256), VBIGNUM(b, 256), VBIGNUM(tmp, 256);
    // printf("opcode: %x\n", opcode);
    // printf("stack: \n");
    // for (i = sp; i >=0; i--) {
    //   printf("%d: %llx\n", i, env->stack_arr[i]);
    // }
    // printf("\n");
    switch (opcode) {
        case 5:
        case 9:
            arg1 = &(env->stack_arr[sp-3]);
            v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1));
            // printf("a: ");
            // v_bignum_print_hex_lf(a);
            sp = sp - (1*4 - 1);
            break;
        case 0 ... 4:
        case 6 ... 8:
        case 10:
            arg1 = &(env->stack_arr[sp-3]);
            arg2 = &(env->stack_arr[sp-7]);
            v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1));
            v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2));
            // printf("a: ");
            // v_bignum_print_hex_lf(a);
            // printf("b: ");
            // v_bignum_print_hex_lf(b);
            sp = sp - (2*4 - 1);
            break;
    }
    ret = &(env->stack_arr[sp]); // set result pointer in stack
    env->sp = sp + 3; // update sp
    switch (opcode) {
        case 0: // LT
            UseGas(env, STEPGAS2);
            if (v_bignum_gt(b, a))
                v_bignum_set_one(a);
            else
                v_bignum_set_zero(a);
            break;
        case 1: // GT
            UseGas(env, STEPGAS2);
            if (v_bignum_gt(a, b))
                v_bignum_set_one(a);
            else
                v_bignum_set_zero(a);
            break;
        case 2: // SLT
            UseGas(env, STEPGAS2);
            if (v_bignum_gt(b, a))
                v_bignum_set_one(a);
            else
                v_bignum_set_zero(a);
            break;
        case 3: // SGT
            UseGas(env, STEPGAS2);
            if (v_bignum_gt(a, b))
                v_bignum_set_one(a);
            else
                v_bignum_set_zero(a);
            break;
        case 4: // EQ
            UseGas(env, STEPGAS2);
            if (v_bignum_eq(a, b))
                v_bignum_set_one(a);
            else
                v_bignum_set_zero(a);
            break;
        case 5: // ISZERO
            UseGas(env, STEPGAS2);
            if (v_bignum_eq_zero(a))
                v_bignum_set_one(a);
            else
                v_bignum_set_zero(a);
            break;
        case 6: // AND
            UseGas(env, STEPGAS2);
            v_bignum_and(a, b);
            break;
        case 7: // OR
            UseGas(env, STEPGAS2);
            v_bignum_or(a, b);
            break;
        case 8: // XOR
            UseGas(env, STEPGAS2);
            v_bignum_xor(a, b);
            break;
        case 9: // NOT
            UseGas(env, STEPGAS2);
            v_bignum_not(a);
            break;
        case 10: // BYTE
            UseGas(env, STEPGAS2);
            v_bignum_set_bignum_part(a, b, 255-((*arg1 >> 8*7) & 0xff)*8, 8);
            break;
    }
    v_bignum_bignum_to_reg(ret, a);
    // printf("r: ");
    // v_bignum_print_hex_lf(a);
}

void LoadFromStorage(CPUArchState* env, uint32 offs) {
    struct Storage* node = mainStorage;
    int i, j;
    int32 sp = env->sp;
    uint64 *ret = &(env->stack_arr[sp+1]);
    uint64 data_tmp[4], byte;
    while (node != NULL) {
        if (node->key == offs) {
            for (i = 0; i < 4; i++)
                data_tmp[i] = node->value[i];
            break;
        }
        node = node->next;
    }
    for (j = 0; j < 4; j++) {
        ret[j] = 0;
        for (i = 0; i < 8; i++) {
            byte = ((data_tmp[3-j] >> (8*i)) & 0xFF) << (8*(7-i));
            ret[j] |= byte;
        }
    }
    env->sp = sp + 4; // update sp
}

void KeccakAlg(CPUArchState* env, uint32 offs, uint32 size) {
    int32 sp = env->sp;
    uint64 *ret = &(env->stack_arr[sp+1]);
    uint8 *start = env->data_bus + offs;
    uint64 res_reg[4] = {0,0,0,0};
    unsigned char buf[255] = "";
    unsigned int hashSize = 256;
    // read memory
    memcpy(buf, start, size);
    // compute Keccak hash
    keccakState *st = keccakCreate(hashSize);
    keccakUpdate((uint8_t*)buf, 0, size, st);
    unsigned char *op = keccakDigest(st);
    // construct numbers blocks
    unsigned int i;
    for (i = 0; i != (hashSize / 8); i++) {
        uint32 block_idx = i == 0 ? 0 : i/8, shift = i == 0 ? 0 : 8*(i%8);
        uint64 byte = *(op++);
        byte <<= shift;
        res_reg[block_idx] |= byte;
    }
    // write to stack
    for (i = 0; i < 4; i++) {
        ret[i] = res_reg[3-i];
    }
    env->sp = sp + 4; // update sp
}

uint64 GetElfSize(CPUArchState* env) {
    return env->elfSize;
}

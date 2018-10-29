#define DATA_32BITS

#include "ppdl.h"
#include "evm_sim.h"
#include "sha3/Keccak.h"
#include "bignum/v_bignum.h"
#include "../gascost.h"

#define BLOCK_SIZE 1024*512 // 512 килобайт памяти
#define IMEM_WS 1

struct Storage {
  uint32 key;
#if 1
  uint64 value;
#else
  uint256 value;
#endif
  Storage* next;
};

Storage* mainStorage;

EVM *new_evm;

typedef tSimpleMemBlock<uint32, uint32, uint8> TProgMem;
typedef tSimpleMemBlock<uint32, uint256, uint256> TDataMem;

TProgMem* prog_mem;
TDataMem* data_mem;
TDataMem* storage_mem;
TDataMem* log_mem;
TDataMem* input_mem;

void UseGas(TDevice* dev, uint64 value) {
  uint64 *gas = ((EVM*)dev)->gas_available;
  uint64 ret[4];
  VBigDig VBIGNUM(x, 256), VBIGNUM(y, 64);
  char value_string[35];
  v_bignum_set_bignum(x, v_bignum_reg_to_bignum(gas, false));
  sprintf(value_string, "0x%llx", value);
  v_bignum_set_string_hex(y, value_string);
  v_bignum_sub(x, y);
  v_bignum_bignum_to_reg(ret, x);
  for (int i = 0; i < 4; i++) {
    gas[i] = ret[i];
  }
}

void DoArithm(TDevice* dev, uint32 opcode) {
  int i, arg_count = 0;
  int32 sp = ((EVM*)dev)->sp;
  uint64 *arg1, *arg2, *arg3, *ret;
  VBigDig VBIGNUM(a, 256), VBIGNUM(b, 256), VBIGNUM(c, 256), VBIGNUM(tmp, 256);
  // printf("opcode: %x\n", opcode);
  // printf("stack: \n");
  // for (i = sp; i >=0; i--) {
  //   printf("%d: %llx\n", i, ((EVM*)dev)->stack_arr[i]);
  // }
  // printf("\n");
  switch (opcode) {
    case 1 ... 7:
    case 10:
    case 11:
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      arg2 = &(((EVM*)dev)->stack_arr[sp-7]);
      v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1, true));
      v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2, true));
      // printf("a: ");
      // v_bignum_print_hex_lf(a);
      // printf("b: ");
      // v_bignum_print_hex_lf(b);
      sp = sp - (2*4 - 1);
      break;
    case 8:
    case 9:
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      arg2 = &(((EVM*)dev)->stack_arr[sp-7]);
      arg3 = &(((EVM*)dev)->stack_arr[sp-11]);
      v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1, true));
      v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2, true));
      v_bignum_set_bignum(c, v_bignum_reg_to_bignum(arg3, true));
      // printf("a: ");
      // v_bignum_print_hex_lf(a);
      // printf("b: ");
      // v_bignum_print_hex_lf(b);
      // printf("c: ");
      // v_bignum_print_hex_lf(c);
      sp = sp - (3*4 - 1);
      break;
  }
  ret = &(((EVM*)dev)->stack_arr[sp]); // set result pointer in stack
  ((EVM*)dev)->sp = sp + 3; // update sp
    switch (opcode) {
      case 0: // STOP
        CheckError("@");
        break;
      case 1: // ADD
        v_bignum_add(a, b);
        break;
      case 2: // MUL
        v_bignum_mul(a, b);
        break;
      case 3: // SUB
        v_bignum_sub(a, b);
        break;
      case 4: // DIV
        v_bignum_div(a, b, tmp);
        break;
      case 5: // SDIV
        v_bignum_div(a, b, tmp);
        break;
      case 6: // MOD
        v_bignum_mod(a, b);
        break;
      case 7: // SMOD
        // TODO
        v_bignum_mod(a, b);
        break;
      case 8: // ADDMOD
        v_bignum_add(a, b);
        v_bignum_mod(a, c);
        break;
      case 9: // MULMOD
        v_bignum_mul(a, b);
        v_bignum_mod(a, c);
        break;
      case 10: // EXP
        if (v_bignum_eq_zero(b)) {
          v_bignum_set_one(a);
        } else {
          v_bignum_set_one(tmp);
          while (!v_bignum_eq_one(b)) {
            v_bignum_mul(a, a);
            v_bignum_sub(b, tmp);
          }
        }
        break;
      case 11: // SIGNEXTEND
        // TODO
        break;
    }
    v_bignum_bignum_to_reg(ret, a);
    // printf("r: ");
    // v_bignum_print_hex_lf(a);
}

void DoCompare(TDevice* dev, uint32 opcode) {
  int i, arg_count = 0;
  int32 sp = ((EVM*)dev)->sp;
  uint64 *arg1, *arg2, *arg3, *ret;
  VBigDig VBIGNUM(a, 256), VBIGNUM(b, 256), VBIGNUM(tmp, 256);
  // printf("opcode: %x\n", opcode);
  // printf("stack: \n");
  // for (i = sp; i >=0; i--) {
  //   printf("%d: %llx\n", i, ((EVM*)dev)->stack_arr[i]);
  // }
  // printf("\n");
  switch (opcode) {
    case 5:
    case 9:
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1, true));
      // printf("a: ");
      // v_bignum_print_hex_lf(a);
      sp = sp - (1*4 - 1);
      break;
    case 0 ... 4:
    case 6 ... 8:
    case 10:
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      arg2 = &(((EVM*)dev)->stack_arr[sp-7]);
      v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1, true));
      v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2, true));
      // printf("a: ");
      // v_bignum_print_hex_lf(a);
      // printf("b: ");
      // v_bignum_print_hex_lf(b);
      sp = sp - (2*4 - 1);
      break;
  }
  ret = &(((EVM*)dev)->stack_arr[sp]); // set result pointer in stack
  ((EVM*)dev)->sp = sp + 3; // update sp
    switch (opcode) {
      case 0: // LT
        if (v_bignum_gt(b, a))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 1: // GT
        if (v_bignum_gt(a, b))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 2: // SLT
        if (v_bignum_gt(b, a))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 3: // SGT
        if (v_bignum_gt(a, b))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 4: // EQ
        if (v_bignum_eq(a, b))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 5: // ISZERO
        if (v_bignum_eq_zero(a))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 6: // AND
        v_bignum_and(a, b);
        break;
      case 7: // OR
        v_bignum_or(a, b);
        break;
      case 8: // XOR
        v_bignum_xor(a, b);
        break;
      case 9: // NOT
        v_bignum_not(a);
        break;
      case 10: // BYTE
        // TODO
        break;
    }
    v_bignum_bignum_to_reg(ret, a);
    // printf("r: ");
    // v_bignum_print_hex_lf(a);
}

// KECCAK algorithm
#if 1
uint64 KeccakAlg(TDevice* dev, uint32 offs, uint32 size)
{
  return 0;
}
#else
uint256 KeccakAlg(TDevice* dev, uint32 offs, uint32 size)
{
  EVM* my_evm = (EVM*)dev;
  char buf[255], ret[259] = "0x", tmp[3] = "";
  uint8 *start = my_evm->data_bus + offs;
  unsigned int hashSize = 256;

  memcpy(buf, my_evm->data_bus + offs, size);

  // Keccak
  keccakState *st = keccakCreate(hashSize);
  keccakUpdate((uint8_t*)buf, 0, size, st);
  unsigned char *op = keccakDigest(st);

  for (unsigned int i = 0; i != (hashSize / 8); i++)
  {
    sprintf(tmp, "%.2x", *(op++));
    strcat(ret, tmp);
  }
  return uint256(ret);
}
#endif

#if 1
uint64 GetElfSize(TDevice* dev)
#else
uint256 GetElfSize(TDevice* dev)
#endif
{
  return dev->elfSize;
}

#if 1
void SaveToStorage(TDevice* dev, uint32 offs, uint64 value)
#else
void SaveToStorage(TDevice* dev, uint32 offs, uint256 value)
#endif
{
  Storage* node = mainStorage;
  Storage* tail;
  bool isFound = false;
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
    node->value = value;
  } else { // create new entry
  tail->next = new Storage;
    tail->next->key = offs;
  tail->next->value = value;
  tail->next->next = NULL;
  }
}


#if 1
uint64 LoadFromStorage(TDevice* dev, uint32 offs)
#else
uint256 LoadFromStorage(TDevice* dev, uint32 offs)
#endif
{
  Storage* node = mainStorage;
  while (node != NULL) {
    if (node->key == offs) {
      return node->value;
    }
    node = node->next;
  }
  #if 1
  return uint64(0x0); // return 0x0 if nothing was found
  #else
  return uint256(0x0); // return 0x0 if nothing was found
  #endif
}

void* Init(void* mParams)
{
  // инициализируем подсистему памяти
  cSwapClass::Init(0x10000000);
  unsigned int peripherals;  
  int is_log_mem;

  prog_mem = new TProgMem(BLOCK_SIZE,IMEM_WS);
  data_mem = new TDataMem(BLOCK_SIZE,IMEM_WS);
  storage_mem = new TDataMem(BLOCK_SIZE,IMEM_WS);
  log_mem = new TDataMem(BLOCK_SIZE,IMEM_WS);
  input_mem = new TDataMem(BLOCK_SIZE, IMEM_WS);

  new_evm = new EVM("evm1");

  new_evm->prog_bus = prog_mem;
/*  new_evm->data_bus = data_mem;
  new_evm->storage_bus = storage_mem;
  new_evm->log_bus = log_mem;
  new_evm->input_data = input_mem;
  */
  // init gas price
  for (int i = 0; i < 4; i++)
    new_evm->gas_available[i] = ((ChipMem*)mParams)->GasLimit;
  new_evm->GasLimit = ((ChipMem*)mParams)->GasLimit;

  // init EVM storage
  mainStorage = new Storage;
  mainStorage->key = -1;
  mainStorage->value = 0x0;
  mainStorage->next = NULL;
  return (void*)new_evm;
}

void Destroy()
{
	delete prog_mem;
	delete data_mem;
	delete storage_mem;
	delete log_mem;
}

LIB_EXPORT void CheckPostProgram()
{
  // save storage mem and data mem 
  Logger.CloseLog();

  // 
  if (new_evm != NULL)
  {
    if ((signed)(new_evm->gas_available) == -1)
    {
      printf("\ngas limit error\n");
      exit(-1);
    }
    char value_string[67] = "0x", part_string[17];
    int32 offs = (int32)new_evm->stack_arr[new_evm->sp-3];
    int32 size = (int32)new_evm->stack_arr[new_evm->sp-7];
    new_evm->sp -= 8;
    printf("0x");
    for (int i = 0; i < size; i++)
    {
      int val = new_evm->data_bus[i + offs];
      printf("%02X", val);
    }
    printf("\n");
    exit(0);
  }
}

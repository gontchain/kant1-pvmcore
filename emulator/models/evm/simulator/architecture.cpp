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
  uint64 value[4];
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

  v_bignum_set_bignum(x, v_bignum_reg_to_bignum(gas));
  sprintf(value_string, "0x%llx", value);
  v_bignum_set_string_hex(y, value_string);
  if (v_bignum_gt(y, x)) {
    v_bignum_set_zero(x);
    v_bignum_bignum_to_reg(gas, x);
    printf("out of gas\n");
    CheckError("@");
  } else {
    v_bignum_sub(x, y);
    v_bignum_bignum_to_reg(gas, x);
  }
}

void DoArithm(TDevice* dev, uint32 opcode) {
  int i, arg_count = 0;
  int32 sp = ((EVM*)dev)->sp;
  uint64 *arg1, *arg2, *arg3, *ret;
  VBigDig VBIGNUM(a, 256), VBIGNUM(b, 256), VBIGNUM(c, 256), VBIGNUM(tmp, 256), VBIGNUM(tmp2, 256);
  // printf("opcode: %x\n", opcode);
  // printf("stack: \n");
  // for (i = sp; i >=0; i--) {
  //   printf("%d: %llx\n", i, ((EVM*)dev)->stack_arr[i]);
  // }
  // printf("\n");
  switch (opcode) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7:
    case 10:
    case 11:
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      arg2 = &(((EVM*)dev)->stack_arr[sp-7]);
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
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      arg2 = &(((EVM*)dev)->stack_arr[sp-7]);
      arg3 = &(((EVM*)dev)->stack_arr[sp-11]);
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
  ret = &(((EVM*)dev)->stack_arr[sp]); // set result pointer in stack
  ((EVM*)dev)->sp = sp + 3; // update sp
    switch (opcode) {
      case 0: // STOP
        CheckError("@");
        break;
      case 1: // ADD
        UseGas(dev, STEPGAS2);
        v_bignum_add(a, b);
        break;
      case 2: // MUL
        UseGas(dev, STEPGAS3);
        v_bignum_mul(a, b);
        break;
      case 3: // SUB
        UseGas(dev, STEPGAS2);
        v_bignum_sub(a, b);
        break;
      case 4: // DIV
      case 5: // SDIV
        UseGas(dev, STEPGAS3);
        v_bignum_div(a, b, tmp);
        break;
      case 6: // MOD
        UseGas(dev, STEPGAS3);
        v_bignum_mod(a, b);
        break;
      case 7: // SMOD
        UseGas(dev, STEPGAS3);
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
        UseGas(dev, STEPGAS4);
        v_bignum_add(a, b);
        v_bignum_mod(a, c);
        break;
      case 9: // MULMOD
        UseGas(dev, STEPGAS4);
        v_bignum_mul(a, b);
        v_bignum_mod(a, c);
        break;
      case 10: // EXP
        UseGas(dev, STEPGAS5);
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
        UseGas(dev, STEPGAS3);
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
      v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1));
      // printf("a: ");
      // v_bignum_print_hex_lf(a);
      sp = sp - (1*4 - 1);
      break;
    case 0: case 1: case 2: case 3: case 4:
    case 6: case 7: case 8:
    case 10:
      arg1 = &(((EVM*)dev)->stack_arr[sp-3]);
      arg2 = &(((EVM*)dev)->stack_arr[sp-7]);
      v_bignum_set_bignum(a, v_bignum_reg_to_bignum(arg1));
      v_bignum_set_bignum(b, v_bignum_reg_to_bignum(arg2));
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
        UseGas(dev, STEPGAS2);
        if (v_bignum_gt(b, a))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 1: // GT
        UseGas(dev, STEPGAS2);
        if (v_bignum_gt(a, b))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 2: // SLT
        UseGas(dev, STEPGAS2);
        if (v_bignum_gt(b, a))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 3: // SGT
        UseGas(dev, STEPGAS2);
        if (v_bignum_gt(a, b))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 4: // EQ
        UseGas(dev, STEPGAS2);
        if (v_bignum_eq(a, b))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 5: // ISZERO
        UseGas(dev, STEPGAS2);
        if (v_bignum_eq_zero(a))
          v_bignum_set_one(a);
        else
          v_bignum_set_zero(a);
        break;
      case 6: // AND
        UseGas(dev, STEPGAS2);
        v_bignum_and(a, b);
        break;
      case 7: // OR
        UseGas(dev, STEPGAS2);
        v_bignum_or(a, b);
        break;
      case 8: // XOR
        UseGas(dev, STEPGAS2);
        v_bignum_xor(a, b);
        break;
      case 9: // NOT
        UseGas(dev, STEPGAS2);
        v_bignum_not(a);
        break;
      case 10: // BYTE
        UseGas(dev, STEPGAS2);
        v_bignum_set_bignum_part(a, b, 255-((*arg1 >> 8*7) & 0xff)*8, 8);
        break;
    }
    v_bignum_bignum_to_reg(ret, a);
    // printf("r: ");
    // v_bignum_print_hex_lf(a);
}

// KECCAK algorithm
void KeccakAlg(TDevice* dev, uint32 offs, uint32 size)
{
  EVM* my_evm = (EVM*)dev;
  int32 sp = my_evm->sp;
  uint64 *ret = &(my_evm->stack_arr[sp+1]);
  uint8 *start = my_evm->data_bus + offs;
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
  for (unsigned int i = 0; i != (hashSize / 8); i++) {
    uint32 block_idx = i == 0 ? 0 : i/8,
           shift     = i == 0 ? 0 : 8*(i%8);
    uint64 byte = *(op++);
    byte <<= shift;
    res_reg[block_idx] |= byte;
  }
  // write to stack
  for (int i = 0; i < 4; i++) {
    ret[i] = res_reg[3-i];
  }
  my_evm->sp = sp + 4; // update sp
}

uint64 GetElfSize(TDevice* dev)
{
  return dev->elfSize;
}

void SaveToStorage(TDevice* dev, uint32 offs)
{
  Storage* node = mainStorage;
  Storage* tail;
  bool isFound = false;
  int i, j;
  int32 sp = ((EVM*)dev)->sp;
  uint64 *data_val = &(((EVM*)dev)->stack_arr[sp-3]);
  uint64 data_tmp[4], byte;

  for (j = 0; j < 4; j++) {
    data_tmp[j] = 0;
    for (i = 0; i < 8; i++) {
      byte = ((data_val[3-j] >> (8*i)) & 0xFF) << (8*(7-i));
      data_tmp[j] |= byte;
    }
  }
  ((EVM*)dev)->sp = sp - 4; // update sp
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
    tail->next = new Storage;
    tail->next->key = offs;
    for (i = 0; i < 4; i++) {
      tail->next->value[i] = data_tmp[i];
    }
    tail->next->next = NULL;
  }
}



void LoadFromStorage(TDevice* dev, uint32 offs)
{
  Storage* node = mainStorage;
  int i, j;
  int32 sp = ((EVM*)dev)->sp;
  uint64 *ret = &(((EVM*)dev)->stack_arr[sp+1]);
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
  ((EVM*)dev)->sp = sp + 4; // update sp
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
  // init gas price (lower 64bit)
  uint64 gasprice_byte, gasprice = 0x0;
  for (int i = 0; i < 4; i++) {
    if (i == 0) { // lower block
        for (int i = 0; i < 8; i++) {
          gasprice_byte = (((ChipMem*)mParams)->GasLimit >> (8*i)) & 0xff;
          gasprice |= gasprice_byte << 8*(7-i);
        }
        new_evm->gas_available[i] = gasprice;
    } else {
      new_evm->gas_available[i] = 0x0;
    }
  }
  new_evm->GasLimit = ((ChipMem*)mParams)->GasLimit;

  // init EVM storage
  mainStorage = new Storage;
  mainStorage->key = -1;
  for (int i = 0; i < 4; i++)
    mainStorage->value[i] = 0x0;
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
    if (new_evm->gas_available[0] == 0)
    {
      printf("\ngas limit error\n");
      exit(-1);
    }
    uint64 offs = 0x0, size = 0x0, return_byte = 0x0;
    // getting return offset and size (lower 64bit)
    for (int i = 0; i < 8; i++) {
      return_byte = (new_evm->stack_arr[new_evm->sp-3] >> (8*i)) & 0xff;
      return_byte = return_byte << 8*(7-i);
      offs = offs | return_byte;
    }
    for (int i = 0; i < 8; i++) {
      return_byte = (new_evm->stack_arr[new_evm->sp-7] >> (8*i)) & 0xff;
      return_byte = return_byte << 8*(7-i);
      size = size | return_byte;
    }
    new_evm->sp -= 8;
    printf("0x");
    for (int i = 0; i < size; i++)
    {
      uint8 val = new_evm->data_bus[i + offs];
      printf("%02X", val);
    }
    printf("\n");

    // free mainStorage
    // TODO pass it to the blockchain, then free
    Storage *temp = mainStorage->next;
    while (temp != NULL) {
      mainStorage->next = temp->next;
      temp->next = NULL;
      delete temp;
      temp = mainStorage->next;
    }
    delete mainStorage;
    exit(0);
  }
}

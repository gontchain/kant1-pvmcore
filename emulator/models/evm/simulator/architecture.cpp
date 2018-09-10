#define DATA_32BITS

#include "ppdl.h"
#include "evm_sim.h"
#include "sha3/Keccak.h"

#define BLOCK_SIZE 1024*512 // 512 килобайт памяти
#define IMEM_WS 1


EVM *new_evm;

typedef tSimpleMemBlock<uint32, uint32, uint8> TProgMem;
typedef tSimpleMemBlock<uint32, uint256, uint256> TDataMem;

TProgMem* prog_mem;
TDataMem* data_mem;
TDataMem* storage_mem;
TDataMem* log_mem;
TDataMem* input_mem;

// KECCAK algorithm
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

uint256 GetElfSize(TDevice* dev)
{
  return dev->elfSize;
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
  new_evm->gas_available = ((ChipMem*)mParams)->GasLimit;
  new_evm->GasLimit = ((ChipMem*)mParams)->GasLimit;
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

    int32 offs = (int32)new_evm->Pop().to_int();
    int32 size = (int32)new_evm->Pop().to_int();
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

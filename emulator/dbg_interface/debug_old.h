#ifndef DEBUG_STRUCTURES_H
#define DEBUG_STRUCTURES_H

// interrupt handling routine
#define  TestIRQ()
// arguments
#define  ARG1   arg[1]
#define  ARG2   arg[2]
#define  ARG3   arg[3]
#define  ARG4   arg[4]
#define  ARG5   arg[5]
#define  ARG6   arg[6]
#define  ARG7   arg[7]
#define  ARG8   arg[8]
#define  ARG9   arg[9]
#define  ARG10  arg[10]
#define  ARG11  arg[11]
#define  ARG12  arg[12]
#define  ARG13  arg[13]
#define  ARG14  arg[14]
#define  ARG15  arg[15]

// instruction
struct tInst
{
  unsigned int    na;           // number of arguments
  unsigned int    ocs;          // opcode size  
  const unsigned short  *sh;    // list of argument shifts
  const unsigned short  *bs;    // list of argument bitsizes
};

// instruction template structuries
struct tInstTempl
{
  unsigned int ni;              // number of instruction
  unsigned int msz;             // bit size of maximal instruction
  const tInst  *inst;           // list of instructios
  const int    *dect;           // decoding table 
};

enum tMemCelType
{
  MS_CHAR,
  MS_SHORT,
  MS_LONG,
};

struct tMemLinker
{
  unsigned int  saddr; // start address
  unsigned int  eaddr; // end address
  void          *ptr;  // pointer into memory block
  tMemCelType   mtype; // type of memory 
  tMemLinker    *next; // next mem link
};

#define MEM(name,addr) name->data_read(addr)


struct tDRegister
{
  const char *name; 
  int  type;        // char - 1
  int  arrsize;     // size of array
  int  flag;        // 
};

struct tDMemBus
{
  const char *name;
  int  asize;       // size of address bus
  int  dsize;       // size of data bus
};

struct tDProcFlags       // processor flag
{
  char              *name;       // name 
  const int         regnum;      // register number
  const int         reg_arrnum;  //  register array number
  int               bit;         // bit of register
};

struct tProcFifo
{
  const char  *name;         // name 
  int         ElemBitSize;   // bits of register
  int         NumElems;      // max num elements
};

// Structure proccfg
struct tDProcCfg
{
  int                nreg;     // number of registers
  const tDRegister   *regs;    // register description
  int                nbuses;   // number of memory buses
  const tDMemBus     *bus;     // memory buses
  int                nflags;   // number of flags
  const tDProcFlags  *flags;   // list of flag
  int                nfifos;   // number of fifos
  const tProcFifo    *fifos;   // list of fifos
};

typedef enum
{
  SMEM_SRAM, // simple memory model, just cell wait time is present
  SMEM_SDRAM,  // SDRAM model
  SMEM_SSRAM,
}eMemBlockKind;

typedef enum
{
  SSMEM_PIPELINED,
  SSMEM_FLOWTROUGH,
}eSSramKind;

struct SDRamConfig
{
  eMemBlockKind  mKind;
  eSSramKind     mSSramLKind;       // kind of ssram memory
  uint64         mPageSize;         // size of page
  TCycleCount    mRegenPeriod;      // regeneration perioud
  TCycleCount    mRegenTime;        // regeneration time
  TCycleCount    mPageOpenTime;     // page selection time 
  TCycleCount    mPageCloseTime;    // page close time 
  double         mMulFactor;        // frequency multyplier
  uint32         mLatency;
};




struct ChipMem {
  int	           m_BankNum;	        // количество банков памяти
  unsigned  long *p_startAddr;      // массив стартовых адресов банков памяти
  unsigned  long *p_Size;           // массив длин банков памяти
  unsigned  long *p_ReadWaitTime;   // массив значений времени задержки при чтения из памяти *
  unsigned  long *p_WriteWaitTime;  // массив значений времени задержки при записи в память (если значение равно 0xFFFFFFFF, то память считается долько для чтения)*
  unsigned  long m_StackStartAddr;  // начальный адрес стека
  unsigned  long m_EndStackAddr;    // Конечный адрес стека
  unsigned  long m_Flags;           // массив флагов (флаги определяют, какие ситуации проверять, а какие нет)
  unsigned  long m_SemiHostFiles;   // максимальное кол-во файлов, которые одновременно могут быть открыты через semihosting
  unsigned  long m_SemiHostAddr;    // адрес маппирования семихостинга
// DDRAM/SDRAM/SRAM specific parameters
  SDRamConfig*   p_Configs;          // array of SDRAM configurations
};

#define STACK_CHECK (1<<23)

struct ErrorHeader
{
public:
  char  m_Msg[512];
  int   m_MsgId;
  int   m_MsgType; 
};

#define MSGTYPE_UNCKNOWN_MSG  -1
#define MSGTYPE_ERROR         1
#define MSGTYPE_WARNING       2

#define LANG_FLAG_IDX         31
#define FLAG_RUS              (1<<LANG_FLAG_IDX)
#define LANG_IS_RUS(flag)     ((flag>>LANG_FLAG_IDX)&1)==1)

#define SEMIHOST_USED         (1<<30)
#define FLAG_USE_LOGGER	      (1<<29)

#endif
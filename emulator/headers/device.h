#ifndef CLASSES_HEADER_H
#define CLASSES_HEADER_H
// prevent warning "possible loss data"
#pragma warning( disable : 4244 )
#pragma warning( disable : 4101 )
#include "export_config.h"

#include <lists.h>
#include "logger.h"

#ifdef SYSTEMC_USED
#include <systemc.h>
#endif


#ifdef SYSTEMC_MODELING
#include <systemc.h>
extern sc_signal<bool> clk_signal;

#endif 

// data types 
/*#include "datatypes.h"
// registers
#include "pd_fifo.h"
// flags 
#include "flag.h"
// pipeline simulation
#include  "pipes.h"
*/
#ifndef USE_FOR_DEBUG // memory buses
#include <mem_space.h>
#endif

#undef SetMem
#include <libelf.h>
// special typedef to define a program address
typedef uint32 tPAddr;

#define DECODE_DELTA 128

// headers for debug structures
#include <debug_structs.h>
#include <dbg_interface.h>
#include <updatable.h> 

extern LIB_EXPORT void CheckError(char* aMsg,int aIsImmideatly=0);

struct tBPoint
{
  tPAddr        addr;   // address of the break point
  ePointType    mType;
  tBPoint       *next;
};
// 
struct tCodeArea
{
  tPAddr       mStartAddr;  // start address 
  tPAddr       mEndAddr;    // end address
  tCodeArea*   mNext;
};

typedef tList<tCodeArea> tCodeAreaLists;

#define DEV_CLASS_PERIPHERAL  0x1
#define IS_DEV_PERIPHERAL(DevPtr) (DevPtr->GetClassDevice()&DEV_CLASS_PERIPHERAL)
#define DEV_CLASS_PROCESSOR   (DEV_CLASS_PERIPHERAL|0x2)


// debug configuration structure
class TCyclic // interface for run device
{
protected:
  TCycleCount   mCycles;
  TCycleCount   mInitCycles;
public:
  int           IsLocked;
  virtual int  GetClassDevice()=0;
  virtual void Operate()=0;
  virtual void UpdateDevice(void) = 0;//{ this->update(); this->mCycles++;}
  inline  int  IsTime2Run(TCycleCount aGlobalCycles){ return mCycles<=aGlobalCycles;}
  inline  int  NumCycles(){return mCycles;}
  inline void  SetCycles(unsigned int NewCycles){ mCycles = NewCycles;}
  inline void  SetupInit() { mInitCycles  = mCycles;}
  inline TCycleCount  TimeOffset() { return mCycles - mInitCycles; }

};

extern tList<TCyclic> DeviceList;
extern TPPDLLogger    Logger;


// class device
class TDevice:public TDbgInterface,public TCyclic
{
protected:
  uint32  mSyncWaitCounter;
  char           mDevName[0x100];
  iUpdatable*    mToUpdate[0x2000];
  int            mUpdateCount;
  int            arg[16];
  int            instidx;
  int            isStart;
  tBPoint        *fbp; // first break point
  tBPoint        *lbp; // last break point
  int            isSingleStep;
  int            error(char* err_msg);
  unsigned int   hidden_mCycles; 
  unsigned int   pcount_max;
  // load elf file into the processors memory
  tDisAsmDbgArea mArea;   
  // internal function: loads a section into a memory
  int LoadSection(ELF_SCN* aSection,uint32_t& aAddr);
    
  // internal function which is called from LoadElf - load DIB
  tDisAsmArea* LoadDibFile(const char* file_name);
  int   DecodePair(char* f_str,uint32& aAddr,uint32 &aData);

  // внутренн€€ функци€, реализуема€ в наследнике,котора€ автоматически генерируетс€ из PPDL описани€
  virtual char* disasm(char *bin,int& size)=0;
  // 
  virtual void ResetDevice()=0;

  inline void pcount_start()
  {
    hidden_mCycles = mCycles;
  }

  inline void pcount_end()
  {
    pcount_max = mCycles;
    mCycles = hidden_mCycles;
  }
  
  inline void pcount_sync()
  {
    if(mCycles < pcount_max)
      mCycles = pcount_max;
  }
  // 
#ifdef SYSTEMC_USED
  void UpdateCycle();
#endif

public:
  // конструктор класса
  TDevice(char* aDevName="") ;
  // деструктор класса
  ~TDevice();
#ifdef SYSTEMC_USED
  sc_in<bool>    clock;
#endif

  // logger
  inline void IncSyscWaitCounter(uint32 aCount = 1) 
  {
    mSyncWaitCounter+=aCount;
  }
  
  inline uint32 GetSyncWaitCounter()
  {
    return mSyncWaitCounter;
  }
 
  virtual int  GetClassDevice();
  virtual void StepInto();
  virtual void update()=0; 
  // add register or fifo to the update list
  inline void AddUpdate(iUpdatable* aR)
  {
    mToUpdate[mUpdateCount++] = aR;
  }

  inline void UpdateRegs()
  {
    for(int i=0;i<mUpdateCount;i++)
      mToUpdate[i]->update();
    this->CheckBreakPoints(this->GetPc(0));
    mUpdateCount = 0;
  }

  // функции быстрого симул€тора
#ifndef SYSTEMC_USED
  // virtual void Operate()=0;
  virtual void UpdateDevice(void);
  inline void wait(){this->UpdateDevice();}
#else // функции точного симул€тора
  virtual void UpdateDevice(void);
  inline void WaitEx() {this->wait();}
#endif

  virtual char* GetDeviceName();
  virtual int   SetBreakPoint(uint32 addr,ePointType aType = BP_STANDARD); // set breakpoint
  virtual int   ClearBreakPoint(uint32 addr); // remove breakpoint
  virtual int   CheckBreakPoints(uint32 pc); // test if program_counter = break_point
  virtual int   CheckWatchPoints(uint32 addr); // chec
  virtual void  Reset(); 
  
  virtual int   DisAssembly(char *str,int busnum,int addr,int size);
  virtual int   GetKindOfInstruction(uint32 aAddr);
  
  virtual tDisAsmArea* LoadElf(char* aElfFile);
  // начать исполнение 
  virtual void Start();
  // остановить исполнение 
  virtual void  Stop();
  virtual int   IsRun();
  virtual unsigned int GetNumCycles();  
  virtual int GetProgMem(void *mem,int addr,int size);
  virtual int GetDataMem(void *mem,int addr,int size); 
  virtual int SetProgMem(void *mem,int addr,int size);
  virtual int SetDataMem(void *mem,int addr,int size);
  // find section
  int GetSectAddr(char* aElfFileName,uint32& aStart,uint32& aEnd,char* aSectName);  
};


#ifdef SYSTEMC_MODELING

class TScWrapper :public sc_module
{

public:
  TDevice* mDev;
  sc_in<bool> clk;
  void Operate();
  void Update();

//  SC_HAS_PROCESS(TScWrapper);
 // TScWrapper(TDevice* aDev) : sc_module(sc_module_name(aDev->GetDeviceName())), clk("clk")
  SC_CTOR(TScWrapper)
  {
//    mDev = aDev;
    // create new thread
    SC_CTHREAD(Operate, clk.pos());
//    SC_CTHREAD(Operate, m_clk.neg());
  }
};

#endif


extern TCyclic* CurDevice;

struct TInst{
  int inum;
};

template<typename vType> class pd_signal
{
protected:
  vType mVal;

public:
  inline operator vType() const { return mVal; }
  inline vType operator = (vType aVal){ mVal = aVal;}
};


template<typename vType> class pd_port
{
protected:
  pd_signal<vType>* Signal;

public:
  inline void operator() (pd_signal<vType>& aSigData)
  {
    Signal = &aSigData;  
  }    

  inline operator vType() const { return (*Signal); }
  inline vType operator = (vType aVal){ (*Signal) = aVal;}
};

typedef pd_signal<IrqType> IrqSignal;
typedef pd_port<IrqType> IrqPort;

inline uint64 pd_lsh(uint64 aVal,int aOffs)
{
  if(aOffs >= 64  ) 
    return 0;
  else
    return aVal << aOffs;
}

inline uint64 pd_rsh(uint64 aVal,int aOffs)
{
  if(aOffs >= 64 ) 
    return 0;
  else
    return aVal >> aOffs;
}

#ifdef SYSTEMC_USED

#define DEV_PROCESS_POS(proc_name) SC_THREAD(proc_name);  sensitive_pos << clock;
#define PROC_UPDATE()  SC_THREAD(UpdateCycle);  sensitive_neg << clock;

#else

#define DEV_PROCESS_POS(proc_name) 
#define PROC_UPDATE()  

#endif

// generate opcode
#define OPCODE(type) (type)ocode
#define BIN(type) *((type*)(bin))
#define PC_START_OFFSET  6

// device components
// registers
#include "pd_fifo.h"
// flags 
#include "flag.h"
// pipeline simulation
#include  "pipes.h"
#include "mem_space.h"


#endif

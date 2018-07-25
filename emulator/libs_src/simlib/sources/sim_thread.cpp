#include "threads_cfg.h"
#include "system.h"
#include <stdarg.h>
#include <stdexcept>

#ifdef LINOS
#include <sys/types.h>
#endif


#ifdef SYSTEMC_MODELING
#define SYSTEMC_USED
#include <systemc.h>

uint32 GlobalCycleCounter;
#endif

#define USE_PC_CACHE

//#include "ins_cache.h"

// переменные симул€тора
THDL                Thread;

#include "tParseCfg.h"


#define MAX_NUM_BLOCKS 1024
#define MAX_NUM_ERRORS 128

#ifdef MY_LOG

#define LOG_SWITCH
#define LOG_SWICH_INNER
// declare log file
FILE*  LogFile;

#endif


typedef struct
{
  TMessage    *ErrorTable;
  int         NumErrors;
  TMessage    *WarnTable;
  int         NumWarns;
}TMsgTable;


#ifdef WIN32
DWORD         OwnerId;
DWORD         ThreadId;  
#else
THDL          OwnerId;
THDL          ThreadId;
#endif


TMsgTable           MsgTable;
volatile int        IsRunned;
volatile int        IsNoBreakPoints;

/////// DBG info
uint32              IsRussianLang;
uint32              DbgFlags;
uint32              StackStartArea;
uint32              StackEndArea;
int                 StackPointerIndex;
// instansiated devices
TDevice*            MainDevice; // главный процессор
tList<TCyclic>      DeviceList; // список всех процессоров
ErrorHeader         GlobalErrorHeader[MAX_NUM_ERRORS];
int                 WarnFlag;
#ifdef FOR_NM_SDK
char ErrorBuffer[1024];
#endif

#ifdef SYSTEMC_USED
sc_signal<bool> clk_signal;
TDevice* GlobalDevice = NULL;
void*    GlobalParam = NULL;
extern int main(int argc, char **argv);

int sc_main(int argc, char **argv)
{
  GlobalDevice = (TDevice*)CreateDevice(GlobalParam);
  return 0;
}
#endif
// главна€ функци€ потока, отвечающа€ за симул€цию
SIM_FUNC_DECL()
{   
  LOGPT("SIMTHREAD:Thread started\n");
  while(true)
  {
    WAIT_START_MSG()
    if(IsRunned)
    {
	LOGPT("SIMTHREAD:IsRunned switched on\n");
#ifdef MY_LOG
  fprintf(LogFile,"start simulation\n");fflush(LogFile);
#endif
      while(IsRunned)
      {
        try
        {
 	  LOGPT("Single clock\n");
          SingleClock();
        }
        catch(ErrorHeader* aMsg)
        {
          if (aMsg->m_MsgType == MSGTYPE_EXIT)
          {
            IsRunned = 0;
            GlobalErrorHeader[WarnFlag++] = *aMsg;
            break;
          }
          WarnFlag++;
        }
        IsRunned &= (WarnFlag==0);
      }// end while
#ifdef MY_LOG
  fprintf(LogFile,"simulation stopped, IsRunned = %d\n",IsRunned);fflush(LogFile);
#endif
    }// end if
    else
    {
    	LOGPT("SIMTHREAD:IsRunned switched OFF!!!\n");
    }   
    SEND_STOP_REASON(0xFFFFFF)
  }// while true
}

LIB_EXPORT void RegErrors(TMessage* aMsgs,int aNumMessages)
{
  MsgTable.ErrorTable = aMsgs;
  MsgTable.NumErrors = aNumMessages;
}

LIB_EXPORT void RegWarnings(TMessage* aMsgs,int aNumMessages)
{
  MsgTable.WarnTable = aMsgs;
  MsgTable.NumWarns = aNumMessages;
}

LIB_EXPORT void FindStackInAbs(char* aAbsFileName,char* aStackSect)
{
  int res;
  if(MainDevice==NULL)
    return;
  res = MainDevice->GetSectAddr(aAbsFileName,StackStartArea,StackEndArea,aStackSect);
  if(res)// if success
  {
    DbgFlags |= STACK_CHECK; // switch on stack checking
  }
  else 
  {
    throw std::runtime_error("no stack section in abs file");
  }
}


LIB_EXPORT void* InitSys(void* aParam)
{
  void* vptr = NULL;
#ifdef MY_LOG
  LogFile = fopen("nm_sim.log","wt");
 fprintf(LogFile,"Start InitSys\n"); fflush(LogFile);
#endif

  try
  {
    MsgTable.NumErrors = 0;
    MsgTable.NumWarns  = 0;
    

#ifdef MY_LOG
  fprintf(LogFile,"init sim\n");fflush(LogFile);

  if(aParam!=NULL)
  {
    ChipMem* aMem = (ChipMem*)aParam;
    fprintf(LogFile,"num banks of chip struct = %d\n",aMem->m_BankNum);fflush(LogFile);
    for(int i=0;i<aMem->m_BankNum;i++)
    {
      fprintf(LogFile,"star addr=0x%X,len =%d\n",(int)aMem->p_startAddr[i],(int)aMem->p_Size[i]);
      fprintf(LogFile,"read time=%d,write time=%d\n",(int)aMem->p_ReadWaitTime[i],(int)aMem->p_WriteWaitTime[i]);
      fflush(LogFile);
    }
  }//
#endif

    TDevice* dev;

#ifdef SYSTEMC_MODELING
  {
    GlobalCycleCounter = 0;
    char args[2][64] = {"cemu.exe", "param"}; 
    GlobalParam = aParam;
    main(1, (char**)args);
    dev = GlobalDevice;
  }
#else
    dev = (TDevice*)CreateDevice(aParam);
#endif

  
#ifdef MY_LOG
    fprintf(LogFile,"device created\n");fflush(LogFile);
#endif    
    TDbgInterface* main_device = dynamic_cast<TDbgInterface*>(dev);
    // set language
    if(aParam!=NULL)
    {
      ChipMem* aMem = (ChipMem*)aParam;
      DbgFlags = aMem->m_Flags;
      StackStartArea = aMem->m_StackStartAddr;
      StackEndArea   = aMem->m_EndStackAddr;  
    }
    else
    {
      // no checks stack
      DbgFlags = (~(STACK_CHECK|FLAG_USE_LOGGER));
    }

#ifdef USE_LOGGER
 	  if(DbgFlags&FLAG_USE_LOGGER)
	    Logger.InitLog(LOG_FILE_NAME);
#endif 

    StackPointerIndex = main_device->GetRegIdx("ar$");
    vptr = (TDbgInterface*)main_device;
  }
  catch( ... )
  {
    return NULL;
  }// end 
  return vptr; 
}

uint32 StartAddresses[MAX_NUM_BLOCKS];
uint32 BlockSizes[MAX_NUM_BLOCKS];
unsigned int ReadTime[MAX_NUM_BLOCKS];
unsigned int WriteTime[MAX_NUM_BLOCKS];
SDRamConfig RamConfigs[MAX_NUM_BLOCKS];
ChipMem cm;


LIB_EXPORT void* InitSysChipMem(char* aBspName,unsigned long aFlags)
{
  cm.p_Size           = BlockSizes;
  cm.p_startAddr      = StartAddresses;
  cm.p_ReadWaitTime   = ReadTime;
  cm.p_WriteWaitTime  = WriteTime;
  cm.p_Configs        = RamConfigs;
  cm.m_Flags          = aFlags;
  cm.m_StackStartAddr = 0;
  cm.m_EndStackAddr   = 0xFFFFFFFF;

  // in case of error bsp_parser throws an exception
  bsp_parser(aBspName,&cm,aFlags>>31);
  // call initialization routine
  return InitSys((void*)&cm);
}

// ‘ункци€ дл€ создани€ устройства и инициализации системы дл€ запуска отладчика
LIB_EXPORT TDbgInterface* CreateDevice(void* aParam)
{ 
  // инициализируем архитекуру
  IsRussianLang = 1;
  TDbgInterface* vptr = (TDbgInterface*)Init(aParam);
  MainDevice = (TDevice*)vptr;
  // получаем 
#ifdef WIN32
  OwnerId = GetCurrentThreadId();
#else
  OwnerId = pthread_self();
#endif
#ifdef LOG_SWITCH
  fprintf(LogFile,"CreateDevice\n"); fflush(LogFile);
#endif

  // обнул€ем флаг запуска симул€тора 
  IsRunned = 0;
  // создаем поток симул€ции
  CREATE_SIM_THREAD(); 
  return vptr;
}


// уничтожаем архитекуру и закрываем поток симул€ции
LIB_EXPORT int SysDestroy()
{
  // закрываем поток симул€ции
  DESTROY_THREAD();
  // затем "убиваем" архитектуру
  Destroy();
  return 1;
}

#define TRANS_LANG(src,dst) if(!strcmp(aRefMsg,src)) return dst;

int GetMsgIdx(char* aMsg,TMessage *aMsgTable,int aNumMessages)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"GetMsgIdx\n"); fflush(LogFile);
#endif

 for(int i=3;i<aNumMessages;i+=2)
 {
   if(!strcmp(aMsgTable[i],aMsg))
     return (i>>1);
 }
 // here must be an error
 return -1;
}

inline char* Translate2Russian(int aIdx,TMessage* aTranslateTable)
{
  return (char*)aTranslateTable[aIdx*2];
}

inline void ValidateStack()
{
  if(DbgFlags&STACK_CHECK)
  {
    uint32 stack_val = MainDevice->GetReg32(StackPointerIndex,7);
    if((stack_val < StackStartArea)||(stack_val > StackEndArea))
      CheckError("Stack overflow, error result",1);
  }
}

#if 1
#define SET_LANG_MSG(MsgTable)\
if((DbgFlags>>31))\
  msg_ptr =  Translate2Russian(GlobalErrorHeader[WarnFlag].m_MsgId,MsgTable);\
else\
  msg_ptr  = aMsg;
#else

#define SET_LANG_MSG(MsgTable)\
  msg_ptr =  Translate2Russian(GlobalErrorHeader[WarnFlag].m_MsgId,MsgTable);

#endif


inline int IsRepeated(int aMsgIdx)
{
  for(int i=0;i<WarnFlag;i++)
    if((GlobalErrorHeader[i].m_MsgType == MSGTYPE_WARNING)&&(GlobalErrorHeader[i].m_MsgId==aMsgIdx))
      return 1;
  return 0;
}

LIB_EXPORT void CheckError(char* aMsg,int aIsImmideatly)
{
  char* msg_ptr = aMsg;
  if(aIsImmideatly==0xFFFF)
  {
    if(!(DbgFlags&(1<<0)))//  wrong memory access now is bit1
      return;
 
    // check limit of warnings
    if (WarnFlag < (MAX_NUM_ERRORS - 2))
    {
      GlobalErrorHeader[WarnFlag].m_MsgId = 0;
      if ((DbgFlags >> 31))
        sprintf((char*)GlobalErrorHeader[WarnFlag].m_Msg, "Address=0x%08X Warning: Incorrect command %d: некорректное обращение по адресу %s, нет физической пам€ти по данному адресу", MainDevice->GetPc(0), GlobalErrorHeader[WarnFlag].m_MsgId, msg_ptr);
    else
        sprintf((char*)GlobalErrorHeader[WarnFlag].m_Msg, "Address=0x%08X Warning: Incorrect command %d: incorrect memory access to address %s no physical memory at this address", MainDevice->GetPc(0), GlobalErrorHeader[WarnFlag].m_MsgId, msg_ptr);
    GlobalErrorHeader[WarnFlag].m_MsgType = MSGTYPE_WARNING;
    WarnFlag++; 
    }
    return;
  }
  // check exit
  if ((aMsg[0] == '@') && (aMsg[1] == 0))
  {
    GlobalErrorHeader[WarnFlag].m_MsgType = MSGTYPE_EXIT;
    throw &GlobalErrorHeader[WarnFlag];
  }
  //check if error
  int msg_idx = GetMsgIdx(aMsg,MsgTable.ErrorTable,MsgTable.NumErrors);
  
  if(msg_idx > 0) // if error. throw error message immediately
  {
    GlobalErrorHeader[WarnFlag].m_MsgId = msg_idx;
    GlobalErrorHeader[WarnFlag].m_MsgType = MSGTYPE_ERROR;
    SET_LANG_MSG(MsgTable.ErrorTable)

    sprintf((char*)GlobalErrorHeader[WarnFlag].m_Msg,"Address=0x%08X Error: Illegal command %d: %s",MainDevice->GetPc(0),GlobalErrorHeader[WarnFlag].m_MsgId,msg_ptr);
    throw &GlobalErrorHeader[WarnFlag];
  } 
  // check if warning
  msg_idx = GetMsgIdx(aMsg,MsgTable.WarnTable,MsgTable.NumWarns);
  
  if(msg_idx > 0)
  {     
    if((DbgFlags&(1<<msg_idx))==0)
      return;
    
    if(IsRepeated(msg_idx))
      return;

    GlobalErrorHeader[WarnFlag].m_MsgId = msg_idx;
    GlobalErrorHeader[WarnFlag].m_MsgType = MSGTYPE_WARNING;
    SET_LANG_MSG(MsgTable.WarnTable)

    sprintf((char*)GlobalErrorHeader[WarnFlag].m_Msg,"Address=0x%08X Warning: Incorrect command %d: %s",MainDevice->GetPc(0),GlobalErrorHeader[WarnFlag].m_MsgId,msg_ptr);
    WarnFlag++; 
    return;
  }
  else
  {
    GlobalErrorHeader[WarnFlag].m_MsgId = -1;
    sprintf((char*)GlobalErrorHeader[WarnFlag].m_Msg,"Address=0x%08X Warning: Incorrect command %d: %s",MainDevice->GetPc(0),GlobalErrorHeader[WarnFlag].m_MsgId,msg_ptr);
    GlobalErrorHeader[WarnFlag].m_MsgType = MSGTYPE_UNCKNOWN_MSG;
    throw &GlobalErrorHeader;
  }
}

extern "C" LIB_EXPORT void GetNextErrors()
{
	if(WarnFlag==0)
		return;
	throw &GlobalErrorHeader[--WarnFlag];
}

inline void HandleExc(ErrorHeader* aMsg)
{
#ifdef FOR_NM_SDK
  {
    if(aMsg->m_MsgType == MSGTYPE_WARNING)
      sprintf(ErrorBuffer,"warning %d: %s",aMsg->m_MsgId, aMsg->m_Msg);
    else      
      sprintf(ErrorBuffer,"error %d: %s",aMsg->m_MsgId, aMsg->m_Msg);
    throw ErrorBuffer;
  }
#else
  throw aMsg;
#endif
}

#ifdef SYSTEMC_MODELING

void SkipCycle()
{
  wait();
}


void SingleClock()
{
  IsNoBreakPoints = 1;
  // POSEDGE - OPERATE
  clk_signal.write(1);
  sc_start(10, SC_NS);
  clk_signal.write(0);
  sc_start(10, SC_NS);
  GlobalCycleCounter++;
}

#else


void SkipCycle()
{
  TCyclic* stop_device = DeviceList.GetCurrent();
  TCyclic* cur_dev = DeviceList.GetNext();

  stop_device->IsLocked = 1;
#ifdef LOG_SWICH_INNER
  printf("--------stopped device:%s\n", ((TDevice*)stop_device)->GetDeviceName()); fflush(stdout);
#endif

  try
  {
    // finish other cycles from other devices
    while (cur_dev != NULL)
    {
#ifdef SYSTEMC_MODELING
      if (!cur_dev->IsLocked)
#endif
      {
#ifdef LOG_SWICH_INNER
        printf("under wait device %s is worked\n", ((TDevice*)cur_dev)->GetDeviceName()); fflush(stdout);
#endif
        cur_dev->SetupInit();
        cur_dev->Operate();
      }
#ifdef SYSTEMC_MODELING
      else
      {
#ifdef LOG_SWICH_INNER
        printf("under wait device %s locked\n", ((TDevice*)cur_dev)->GetDeviceName()); fflush(stdout);
#endif
      }
#endif
      cur_dev = DeviceList.GetNext();
    }
      
    // update all
    FOR_EACH_ELEM(TCyclic, cur_dev, (&DeviceList))
    {
        cur_dev->UpdateDevice();
    }
    // restart untill the current device
    cur_dev = DeviceList.GetFirst();
    while (cur_dev != stop_device)
    {
      assert(cur_dev != NULL);
#ifdef SYSTEMC_MODELING
       if (!cur_dev->IsLocked)
#endif
      {
#ifdef LOG_SWICH_INNER
        printf("under wait device %s is worked\n", ((TDevice*)cur_dev)->GetDeviceName()); fflush(stdout);
#endif
        cur_dev->SetupInit();
        cur_dev->Operate(); 
      }//if (!cur_dev->IsLocked)
 #ifdef SYSTEMC_MODELING
     else
      {
#ifdef LOG_SWICH_INNER
        printf("under wait device %s is locked\n", ((TDevice*)cur_dev)->GetDeviceName()); fflush(stdout);
#endif

      }
#endif
      cur_dev = DeviceList.GetNext();
    } //  while (cur_dev != stop_device)
#ifdef LOG_SWICH_INNER
    printf("--------exit from stopped device:%s\n", ((TDevice*)stop_device)->GetDeviceName()); fflush(stdout);
#endif
  }
  catch (ErrorHeader* aMsg)
  {
    printf("error or warning: %s\n",aMsg->m_Msg);
  }
  stop_device->IsLocked = 0;
}

// функци€, эмулирующа€ один такт работы системы
void SingleClock()
{
  // исполн€ем одну инструкций
  TCyclic* cur_dev;
  TDevice* main_dev = ((TDevice*)DeviceList.GetFirst());
  unsigned long pc_prev;
  IsNoBreakPoints = 1;
#ifdef LOG_SWITCH
  fprintf(LogFile,"start single clock\n"); fflush(LogFile);
#endif
  try
  {
    pc_prev = main_dev->GetPc(0);
	// ориентируемс€ на главное устройство
    TCycleCount start_cycle = main_dev->NumCycles();
#ifdef USE_LOGGER
    Logger.Log(LOG_INSTRUCTION_BEGIN,pc_prev,start_cycle);
#endif   
    do
    {
    //  TCycleCount ct = main_dev->NumCycles();
      WarnFlag = 0;
      // operate (positive edge)
      FOR_EACH_ELEM(TCyclic,cur_dev,(&DeviceList))
      {
#ifdef  SYSTEMC_MODELING
       if (!cur_dev->IsLocked)
#endif
       {
#ifdef LOG_SWITCH
          fprintf(LogFile,"switch to %s\n", ((TDevice*)cur_dev)->GetDeviceName()); fflush(LogFile);
#endif
        cur_dev->SetupInit();
        cur_dev->Operate();
      }
#ifdef SYSTEMC_MODELING
        else
        {
#ifdef LOG_SWITCH
          fprintf(LogFile,"device %s locked\n", ((TDevice*)cur_dev)->GetDeviceName());  fflush(LogFile);
#endif

        }
#endif
      }
      // operate (negative edge)
      FOR_EACH_ELEM(TCyclic,cur_dev,(&DeviceList))
      {
	  	  	cur_dev->UpdateDevice();
      }
    }while(main_dev->GetPc(0)==pc_prev);


    IsRunned &= IsNoBreakPoints;
    if(WarnFlag > 0)
    {
      throw &GlobalErrorHeader[--WarnFlag];
    }
  }
  catch(ErrorHeader* aMsg)
  {
    FOR_EACH_ELEM(TCyclic,cur_dev,(&DeviceList))
      cur_dev->UpdateDevice();
#ifdef USE_LOGGER
    Logger.Log(LOG_INSTRUCTION_END,pc_prev,CurDevice->NumCycles());
#endif
  	HandleExc(aMsg);
  }
  // validate stack
  try 
  { 
    ValidateStack(); 
    if(WarnFlag > 0)
    {
#ifdef USE_LOGGER
    Logger.Log(LOG_INSTRUCTION_END,pc_prev,CurDevice->NumCycles());
#endif
      throw &GlobalErrorHeader[--WarnFlag];
    }// end if(WarnFlag > 0)
  } 
  catch(ErrorHeader* aMsg) 
  { 
    HandleExc(aMsg); 
  }
#ifdef USE_LOGGER
//  printf("exit single clock\n"); fflush(stdout);
    Logger.Log(LOG_INSTRUCTION_END,pc_prev,CurDevice->NumCycles());
#endif
}
#endif


LIB_EXPORT TDevice* GetDevCore(int aCoreNum)
{
  TDevice* dev = dynamic_cast<TDevice*>(DeviceList[aCoreNum]);
  return dev;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// C-interface for debug access
// данный набор функций используетс€ только дл€ поддержки совместимости
// со старой версией отладчика PPDL-Debugger
tDisAsmArea* ProcLoadElf(char* aName)
{
  try
  {
    return MainDevice->LoadElf(aName);
  }
  catch (.../*exception &exc*/) // output exception
  {
    return 0;
  };
}


// get memory
int ProcGetMem(void *mem, int busnum, int addr, int size)
{
  return MainDevice->GetMem(mem, busnum, addr, size);
}

int ProcGetCellSize(int busnum, int addr)
{
  return MainDevice->GetCellSize(busnum, addr);
}

// clear all memory
void ProcClearMem()
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"clear mem\n"); fflush(LogFile);
#endif
  MainDevice->ClearMem();
}

// set memory
int ProcSetMem(void *mem, int busnum, int addr, int size)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"set mem\n"); fflush(LogFile);
#endif
  return MainDevice->SetMem(mem, busnum, addr, size);
}

// get size of the memory cells
int ProcGetMemCellSize(int busnum, int addr)
{
  return MainDevice->GetCellSize(busnum, addr);
}

// disassembly
int ProcDisAsm(char *str, int busnum, int addr, int size)
{
  return MainDevice->DisAssembly(str, busnum, addr, size);
}

int ProcSetReg(int rnum, int anum, char* val)
{
  return MainDevice->SetReg(rnum, anum, val);
}

int ProcSetFifo(int fifo_num, char* data, int size)
{
  return MainDevice->SetFifo(fifo_num, data, size);
}

int ProcGetFifo(int fifo_num, char* data, int* size)
{
  return MainDevice->GetFifo(fifo_num, data, *size);
}

int Disassembly(char* str, int busnum, int aAddr, int aSize)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"Disassembly\n"); fflush(LogFile);
#endif

  return MainDevice->DisAssembly(str, busnum, aAddr, aSize);
}

int ProcSetPc(uint32 pc)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"set PC\n"); fflush(LogFile);
#endif

  MainDevice->SetPc(pc);
  return 1;
}

unsigned long ProcGetPc()
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"Get PC\n"); fflush(LogFile);
#endif

  return MainDevice->GetPc(0);
}

int ProcGetReg(int rnum, int anum, char* buf)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"Get register\n"); fflush(LogFile);
#endif

  return MainDevice->GetReg(rnum, anum, buf);
}

int ProcSetBreakPoint(unsigned long addr)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"set breakpoint\n"); fflush(LogFile);
#endif
  return MainDevice->SetBreakPoint(addr);
}

int ProcClearBreakPoint(unsigned long addr)
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"clear breakpoint\n"); fflush(LogFile);
#endif
  return MainDevice->ClearBreakPoint(addr);
}

int ProcStart()
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"ProcStart\n"); fflush(LogFile);
#endif

  MainDevice->Start();
  return 0;
}

int ProcStop()
{
  MainDevice->Stop();
  return 0;
}

int ProcIsRun()
{
  return MainDevice->IsRun();
}

unsigned long ProcStepInto()
{
#ifdef LOG_SWITCH
  fprintf(LogFile,"ProcStepInto start\n"); fflush(LogFile);
#endif
  MainDevice->StepInto();
//  SingleClock();
#ifdef LOG_SWITCH
  fprintf(LogFile,"ProcStepInto end start getpc\n"); fflush(LogFile);
#endif
  unsigned long pcval = MainDevice->GetPc(0);

#ifdef LOG_SWITCH
  fprintf(LogFile,"ProcStepInto:exit \n"); fflush(LogFile);
#endif
  return pcval;
}

void ProcReset()
{
  MainDevice->Reset();
}

int GetRegIndexByName(char* aName)
{
  tDProcCfg* proc_cfg = (tDProcCfg*)MainDevice->GetCfg();

  for (int i = 0; i<proc_cfg->nreg; i++)
  {
    if (!strcmp(proc_cfg->regs[i].name, aName))
      return i;
  }
  return -1;
}


tDProcCfg* GetProcCfg()
{
  return (tDProcCfg*)MainDevice->GetCfg();
}

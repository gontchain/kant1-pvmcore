#include <stdio.h>
#include <iostream>

#define PRINT_LOG(msg) //printf(msg);

#define MAX_NUM_WARNINGS 25

#ifdef WIN32
#include <windows.h>
#else
//including header with functions for library working
#include <dlfcn.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#endif


#include <stdexcept>


#include <dbg_interface.h>
#include "stream_txt_funcs.h"

//#include "profiler.h"

//#define USE_DWARF

#ifdef USE_DWARF
#include "libelf.h"
#include "lists.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "dwarferr.h"
#include "libdwarf.h"
#include "dwarferr.h"
#endif

////////////////////////////////
#define MAX_NUM_BLOCKS 1024

// defines 
#define ERR_NO_SIM_NAME       1
#define ERR_WRONG_SIM_NAME    2
#define ERR_CANT_INIT_SIM_API 3
#define ERR_NO_EXE_FILE       4
#define ERR_CANT_OPEN_EXE     5
#define ERR_TIMEOUT           6

#define OUT_TEST_REG          0
#define OUT_TEST_REG_ARR      10 // x[10| - return value
#define REG_TEST_VAL          0
#define PC_START_OFFSET       6

#define MUL_FACTOR 	  1000000

#define WARN_FLAGS "long_warn_flags"
// functions to control a simulation process
typedef TDbgInterface* (*TInitSys)(void* aPtr);
typedef TDbgInterface* (*TInitSysChipMem)(char* aBspName,unsigned long aFlags);
typedef void (*TCheckPostProgram)();
typedef void (*TGetNextErrors)();
typedef void (*TFindStackInAbs)(char* aAbsFileName,char* aStackSect);
typedef TDbgInterface* (*TGetDevCore)(int aCoreNum);
#ifdef WIN32
HANDLE LibHandler;
#else
void * LibHandler;
#endif
// LANGUAGE 
int IsRusLang;

// pointer into a device class 
TDbgInterface    *Device;
TDbgInterface    *SecondDev;

// function InitSystem
TInitSys          InitSystem;
TInitSysChipMem   InitChipMem;
TCheckPostProgram CheckPostProg;
TGetNextErrors    GetNextErrors;
TFindStackInAbs   FindStackInAbs;
TGetDevCore       GetDevCore;
// config file name
char*  ConfigFileName;
// GAS limit
uint64 GasMaxLimitValue = 0xFFFFFFFFFFFFFFFF;
uint64 GasLimitValue = 10000000000;
char*  ProfileFileName;
int    default_config_file;
// second device file name
char*  SecondDevFileName;

// registers arrays
char** RegNames;
int**  RegVal;

struct TFifo
{
	char* Name;     // name of fifo
	int   ByteSize; // size of one element in bytes
	int   Len;      // current size of fifo
	int   NumElems; // number of elements in fifo container
	union
	{
		int32* CurValL; 
		int64* CurValW;
	};
};

#define MAX_FIFO_LEN 128

TFifo*  Fifos;
int    NumFifos;
unsigned long num_warns;

#ifdef USE_DWARF
//dwarf
// индекс объекта отладочной информации в таблице объектов отладочной информации
typedef unsigned long cDwarfHandler; 
// тип данных для хранения значения счетчика программ
typedef unsigned long cPcVal;
//переменная списка. содержит указатель на ELF-a
tList<Dwarf_Debug> setElem;
//возвращаемое значение: cDwarfHandler - дескриптор DWARF структуры, соответствующей файлу
cDwarfHandler CreateDwarfInstance(char* elfpath);
//имя файла и строку в файле по значениею счетчика программ (далее PC)
int DwarfGetFileLine(cDwarfHandler aHandler,cPcVal aVal,int& aLine,char* aFileName);
/////////////
#endif
// user defined flags
unsigned long IsOutCode;
unsigned long IsRetValue;
unsigned long IsOutZero;
unsigned long IsLogMem;
unsigned long IsPrintArGr;
unsigned long IsWarnFlags;
unsigned long IsShowData;
unsigned long CheckResult;
unsigned long BuildProfile;

void PreInitFlags()
{
	IsOutCode = 1;
    IsRetValue = 0;
    IsOutZero = 0; 
	IsWarnFlags = 0;// (1 << MAX_NUM_WARNINGS) - 1; // 
	IsShowData = 1;
	CheckResult = 0;
	IsRusLang = 0;
	BuildProfile = 0;
  SecondDevFileName = NULL;
  IsLogMem = 0;
  IsPrintArGr = 0;
}

inline int IsDviFile(char *aElfFileName)
{
    int file_name_size = strlen(aElfFileName);
    if(!strcmp(aElfFileName +(file_name_size - 4),".dvi"))
      return 1;
    else
      return 0;
}

void InitFifos(TDbgInterface* aDevice,const tDProcCfg *cfg)
{
	NumFifos = cfg->nfifos;
	Fifos = new TFifo[NumFifos];
	// create new fifo
	for(int i=0;i<NumFifos;i++)
	{
		Fifos[i].Name = (char*)cfg->fifos[i].name;
		Fifos[i].ByteSize = cfg->fifos[i].ElemBitSize;
		Fifos[i].NumElems = cfg->fifos[i].NumElems;
		// allocate memory for fifos
		if(Fifos[i].ByteSize == 8)
			Fifos[i].CurValW = new int64[Fifos[i].NumElems];
		else // 32 bits is assumed
			Fifos[i].CurValL = new int32[Fifos[i].NumElems];
	}
	// init fifo
	for(int i=0;i<NumFifos;i++)
	{
		aDevice->GetFifo(i,(char*)Fifos[i].CurValW,Fifos[i].Len);
	}
}

int IsFifoDiffer(TFifo* aFifo,int64* buf,int aLen)
{
	if(aLen!=aFifo->Len) return 1;
	return memcmp((void*)aFifo->CurValL,(void*)buf,aFifo->Len * aFifo->ByteSize)!=0;
}

void CheckFifos(char* str)
{
	uint64 fifo_buf[MAX_FIFO_LEN];
	int fifo_len;

	if(!IsShowData)
		return;

	for(int i=0;i<NumFifos;i++)
	{ 
		Device->GetFifo(i,(char*)fifo_buf,fifo_len);   

		if(IsFifoDiffer(&Fifos[i],(int64*)fifo_buf,fifo_len))
		{
			// init fifo with new vals
			Fifos[i].Len = fifo_len;
			memcpy((char*)Fifos[i].CurValL, fifo_buf, Fifos[i].Len * Fifos[i].ByteSize);
			// print fifo
			str+=sprintf(str,"%s[%d] = {",Fifos[i].Name,fifo_len);

			if(Fifos[i].ByteSize==8)
			{
				for(int j=0;j<fifo_len;j++)
					str+=sprintf(str," %016llx",Fifos[i].CurValW[j]);
			}
			else
			{
				for(int j=0;j<fifo_len;j++)
					str+=sprintf(str," %08x",Fifos[i].CurValL[j]);
			}// end if(Fifos[i].ByteSize==8)
			str+=sprintf(str,"};\n");    
		}// end if
	} // end for(i...
}


//fill massive RegNames and RegVal
void InitRegs()
{
	int reg[2];
	TDbgInterface    *Dev = Device;
	const tDProcCfg *cfg = Dev->GetCfg();
	InitFifos(Dev,cfg);
	//create named arrays
	RegNames = new char*[cfg->nreg];
	RegVal = new int*[cfg->nreg];

	for( int i = 0; i < cfg->nreg; i++ )
	{
		//read register's name 
		const char* rnm = cfg->regs[i].name;
		//in case of array of registers
		if( cfg->regs[i].arrsize )
		{
			//type array position in register's name
			int len = strlen(rnm)+1;
			char cname[512];
			char *cn_ptr = cname; 

			for(const char* rptr = rnm; *rptr!=0;rptr++){ if(*rptr!='$') *cn_ptr++ = *rptr; }
			*cn_ptr = 0;
			RegNames[i] = new char[strlen(cname)+1];
			strcpy(RegNames[i], cname);
			//
			int t = cfg->regs[i].type;
			if (t == 8)
			{
				//in case of 64 bit registers
				RegVal[i] = new int[cfg->regs[i].arrsize * 2];	
				int tmp = 0;
				// initialize reg list
				for( int j = 0; j < cfg->regs[i].arrsize; j++, tmp+=2 )
				{
					Dev->GetReg(i, j, (char*)&reg);
					//fill register value from register array
					RegVal[i][tmp]   = reg[0];
					RegVal[i][tmp+1] = reg[1];
				}
			}
			else
			{
				//in case of 32 bit registers
				RegVal[i] = new int[cfg->regs[i].arrsize];
        reg[0] = 0;
				for( int j = 0; j < cfg->regs[i].arrsize; j++ ){
					Dev->GetReg(i, j, (char*)&reg);
					//fill register value from register array
					RegVal[i][j] = reg[0];
				}//end for
			}//end else
		}//end if
		else
		{
			//case of one register
			RegNames[i] = (char*)malloc(strlen(rnm));
			//fill register name
			strcpy(RegNames[i], rnm);
			int t = cfg->regs[i].type;
			Dev->GetReg(i, 0, (char*)&reg);
			//fill register value
			if (t == 8)//in case of 64 bit register
			{       
				RegVal[i] = new int[2];
				RegVal[i][0] = reg[0];
				RegVal[i][1] = reg[1];
			}
			else
			{
				RegVal[i] = new int[1];
				RegVal[i][0] = reg[0];
			}//end else
		}//end else
	}//end for
}


// function "InitRegisters
void InitPrintRegs()
{
	uint64 fifo_buf[MAX_FIFO_LEN];
	int fifo_len;

	typedef unsigned long long uint64;
	uint64 regval64;
	int reg[2],fl = 0, arrsize;
	const tDProcCfg *cfg = Device->GetCfg();
	bool flag;
	char tmpstr[128];

	for(int i = 0; i < cfg->nreg; i++){
		flag = false;
		if (strcmp(cfg->regs[i].name, "pc"))
		{ 
			if( cfg->regs[i].arrsize )
			{
				arrsize = cfg->regs[i].arrsize;
				int t = cfg->regs[i].type;
				if (t == 8){//64 bit
					int tmp = 0;
					for(int j = 0; j < arrsize; j++, tmp+=2){
						Device->GetReg(i, j, (char*)&reg);
						if ((RegVal[i][tmp] != reg[0]) || (RegVal[i][tmp+1] != reg[1])){
							regval64 = (((uint64)reg[1])<<32)|(((uint64)reg[0]));
							printf("\t%s%d = %016llx\n", RegNames[i], j, regval64);
						}		
					}//end for
				}
				else
				{//32 bit

					for( int j = 0; j < arrsize; j++ ){
						Device->GetReg(i, j, (char*)&reg);
						printf("\t%s%d = %08x\n", RegNames[i], j, reg[0]);
					}//end for
				}//end else
			}//end if
			else if(strcmp(cfg->regs[i].name,WARN_FLAGS))
			{
				int t = cfg->regs[i].type;
				Device->GetReg(i, 0, (char*)&reg);		  
				if (t == 8){//64 bit
					regval64 = (((uint64)reg[1])<<32)|(((uint64)reg[0]));
					printf("\t%s = %016llx\n", RegNames[i], regval64);
				}
				else 
				{
					printf("\t%s = %08x\n",RegNames[i],reg[0]);
				}
			}
		}// if (strcmp(cfg->regs[i].name, "pc"))
	}//end for
	//erase last symbol ','

	// output fifos
	printf("FIFOS:\n");
	for(int i=0;i<cfg->nfifos;i++)
	{ 
		Device->GetFifo(i,(char*)fifo_buf,fifo_len);   
		if(true)
		{
			// print fifo
			printf("\t%s[%d] = {",Fifos[i].Name,fifo_len);
			if(Fifos[i].ByteSize==8)
			{
				for(int j=0;j<fifo_len;j++)
					printf(" %016llx",fifo_buf[j]);
			}
			else
			{
				for(int j=0;j<fifo_len;j++)
					printf(" %08x",fifo_buf[j]);
			}// end if(Fifos[i].ByteSize==8)
			printf("};\n");    
		}// end if
	} // end for(i...
}
// -ra flag checking function
int CheckArGr(int aIdx)
{
	if (IsPrintArGr && (!strcmp(RegNames[aIdx], "ar") || !strcmp(RegNames[aIdx], "gr")))
		return 1;
	return 0;
}

//function create a string with name 
//of register's that has changed value
int CheckRegs(char* regnames)
{
	typedef unsigned long long uint64;
	uint64 regval64;
	int reg[2],fl = 0, arrsize;
	const tDProcCfg *cfg = Device->GetCfg();
	bool flag;
	char tmpstr[128];

	if(!IsShowData)
		return fl;

	strcpy(regnames, "");
	for(int i = 0; i < cfg->nreg; i++){
		flag = false;
		if (strcmp(cfg->regs[i].name, "pc"))
			if( cfg->regs[i].arrsize ){
				arrsize = cfg->regs[i].arrsize;
				int t = cfg->regs[i].type;
				if (t == 8){//64 bit
					int tmp = 0;
					for(int j = 0; j < arrsize; j++, tmp+=2){
						Device->GetReg(i, j, (char*)&reg);
						if ((RegVal[i][tmp] != reg[0]) || (RegVal[i][tmp+1] != reg[1])){
							RegVal[i][tmp] = reg[0];		
							RegVal[i][tmp+1] = reg[1];
							regval64 = (((uint64)reg[1])<<32)|(((uint64)reg[0]));
							sprintf(tmpstr,"%s%d = %016llx\n", RegNames[i], j, regval64);
							strcat(regnames, tmpstr);
							strcpy(tmpstr, "");
							flag = true;
						}		
					}//end for
				}
				else
				{//32 bit
					for( int j = 0; j < arrsize; j++ ){
            reg[0] = 0;
            Device->GetReg(i, j, (char*)&reg);
						if (RegVal[i][j] != reg[0]){
							RegVal[i][j] = reg[0];	
							sprintf(tmpstr,"%s%d = %08x\n", RegNames[i], j, reg[0]);
							strcat(regnames, tmpstr);
							strcpy(tmpstr, "");
							flag = true;
						}
					}//end for
				}//end else
			}//end if
			else if(strcmp(cfg->regs[i].name,WARN_FLAGS))
			{
				int t = cfg->regs[i].type;
        reg[0] = 0;
        Device->GetReg(i, 0, (char*)&reg);		  
<<<<<<< HEAD
				if (t == 8){//64 bit
=======
				if (t >= 8){//64 bit
>>>>>>> 83120b909ffb5490ad91c1b3b8460a37eff69b16
					if ((RegVal[i][0] != reg[0]) || RegVal[i][1] != reg[1]){
						RegVal[i][0] = reg[0];
						RegVal[i][1] = reg[1];
						regval64 = (((uint64)reg[1])<<32)|(((uint64)reg[0]));
						sprintf(tmpstr,"%s = %016llx\n", RegNames[i], regval64);
						strcat(regnames, tmpstr);
						strcpy(tmpstr, "");
						flag = true;
					}
				}
				else if (RegVal[i][0] != reg[0])
				{
					RegVal[i][0] = reg[0];
					sprintf(tmpstr,"%s = %08x\n", RegNames[i],reg[0]);
					strcat(regnames, tmpstr);
					strcpy(tmpstr, "");
					flag = true;
				}
			}
			if (flag) fl++;
	}//end for
	return fl;	
}

//Записывает строку кода в result из файла если PC указывает на неё
//возвращает 1 если PC указывает на строку с кодом, иначе 0
#ifdef USE_DWARF
int GetLineCode(cDwarfHandler ElfFileNumber, cPcVal &aStart, char* result)
{
	char fname[256];
	int lineno;
	char *res;
	//if PC correspond to code line
	if(DwarfGetFileLine(ElfFileNumber, aStart, lineno, fname)){
		FILE *f;
		int cnt = 0;
		char linecod[128];
		f = fopen(fname, "rt");
		if (f!=NULL)
			while (!feof(f)){
				//read strings until position != lineno or EOF
				res = fgets(linecod, 128, f);
				cnt++;
				if (cnt==lineno)
					break;
			}		
			if (cnt == lineno){
				strcpy(result, res);
				return 1;
			}
	}
	return 0;
}
#endif

#define MAX_NUM_BANKS 512

#define ADDR_OFFSET  0x40000000
#define BLOCK_SIZE   1024*1024

#define IS_TOK(str) (!strcmp(token,str))

#define IS_TOK(str) (!strcmp(token,str))
#define NEXT_TOK() if(feof(fcfg)){break;}fscanf(fcfg,"%s",token);  

#define FIND_TOK(str) do{ NEXT_TOK() }while(!IS_TOK(str));
#define FIND_TOK2(str1,str2) do{ NEXT_TOK() }while((!IS_TOK(str1)) && (!IS_TOK(str2)));
#define WAIT_TOK(str) NEXT_TOK() if(!IS_TOK(str)){printf("bsp preprocessing error: wrong token %s\n",token); return -1;} 
//#define IS_LAST_SYMB(symb) (token[strlen(token)-2]==symb)

inline int IS_LAST_SYMB(char* token,char symb)
{
	int len = strlen(token);
	if(token[len-1] == symb)
		return 1;
	else
		return 0;
}


#ifdef WIN32
#define GET_PROC_ADDR(hdr,name) GetProcAddress((HMODULE)hdr,name)
#else
// posix-based os is assumed
#define GET_PROC_ADDR(hdr,name) dlsym(hdr,name)
#endif


int Init()
{
	ChipMem cm;

	InitSystem     = (TInitSys)GET_PROC_ADDR(LibHandler,"InitSys");
	InitChipMem    = (TInitSysChipMem)GET_PROC_ADDR(LibHandler,"InitSysChipMem");
	CheckPostProg  = (TCheckPostProgram)GET_PROC_ADDR(LibHandler,"CheckPostProgram");
	GetNextErrors  = (TGetNextErrors)GET_PROC_ADDR(LibHandler,"GetNextErrors");  
	FindStackInAbs = (TFindStackInAbs)GET_PROC_ADDR(LibHandler,"FindStackInAbs");
  GetDevCore     = (TGetDevCore)GET_PROC_ADDR(LibHandler, "GetDevCore");

	if(InitSystem == NULL)
	{
		printf("can't get function InitSys\n");
		return 0;
	}
	if(InitChipMem == NULL)
	{
		printf("can't get function InitSysChipMem\n");
		return 0;
	}    

	if(CheckPostProg == NULL)
	{
		printf("can't get function CheckPostProg\n");
		return 0;
	}    

	if(GetNextErrors == NULL)
	{
		printf("can't get function GetNextErrors\n");
		return 0;
	}    

	if(FindStackInAbs == NULL)
	{
		printf("can't get function FindStackInAbs\n");
		return 0;
	}    

  if (GetDevCore == NULL)
  {
    printf("can't get function GetDevCore\n");
    return 0;
  }

	if(ConfigFileName!=NULL)
	{

		try
		{
			Device = InitChipMem(ConfigFileName,IsWarnFlags|(IsRusLang<<31)|(BuildProfile<<29)|(IsLogMem <<28)); //
      if (SecondDevFileName!=NULL)
        SecondDev = GetDevCore(1);
		}
		catch(std::runtime_error& err)
		{
			printf(err.what());
			exit(-1);
		}
	}
	else
	{
	ChipMem mem;
	mem.m_BankNum = 0;
    mem.GasLimit = GasLimitValue;
	mem.m_Flags = IsWarnFlags | (IsRusLang << 31) | (BuildProfile << 29) | (IsLogMem << 28);
	Device = InitSystem(&mem);
    if (SecondDevFileName != NULL)
      SecondDev = GetDevCore(1);
  }

	if(Device==NULL)
	{
		printf("can't initialize simulator\n");
		return 0;
	}
	return 1;
}

int PrintErrorHandle(void* aHrv,uint32 cur_pc)
{
	ErrorHeader* aHr = (ErrorHeader*)aHrv;
	if(aHr->m_MsgType == MSGTYPE_WARNING)
	{
		//    printf("\n\n      Address=0x%08X Warning: Incorrect command %d: %s\n\n",cur_pc,aHr->m_MsgId,aHr->m_Msg);
		if(IsWarnFlags==0) return 0;
		printf("\n\n      %s\n\n",aHr->m_Msg);
		num_warns++;
	}
  else if (aHr->m_MsgType == MSGTYPE_EXIT)
  {
    return -1;
  }
	else
	{
		//    printf("\n\n      Address=0x%08X Error: Illegal command %d: %s\n\n",cur_pc,aHr->m_MsgId,aHr->m_Msg);
		printf("\n\n      %s\n\n",aHr->m_Msg);
		return -1;
	}
	return 0;
}

int ProcessWarns(uint32 cur_pc)
{
	while(1)
	{
		try
		{
			GetNextErrors();    
			return 1;
		}
		catch(void* aHrv)
		{
      ErrorHeader *aMsg = (ErrorHeader*)aHrv;
      if (aMsg->m_MsgType == MSGTYPE_EXIT)
        return 2; 
			if(PrintErrorHandle(aHrv,cur_pc)==-1)
				return 0; // error found - return 0, othewise return 1;
		}// end  catch
	}// end while
}

#define USE_BREAK_POINTS 
inline void SetStackControl(char* aSimName)
{
	if(IsWarnFlags&STACK_CHECK)
	{
		try
		{
			FindStackInAbs(aSimName,".stack");
		}
		catch(std::runtime_error& err)
		{
			//      printf(err.what());
			//      exit(-1);
		}// end try-catch
	}// end if 
}

int RunSimulation(char* aSimName,uint32 aWait)
{
	char disasm[256];

	char *sptr;
	int out_flag = 0;
	unsigned long st, end;
	int ElfFileNumber = -1;
	char upregs[128*1024];//здесь имена регистров изменивших значение 
	tDisAsmArea* elf_res;
	uint32 cur_pc;
  

	printf("\nstart simulation\n"); 
	// reset device
	Device->Reset();
	// load an executable file
	elf_res = Device->LoadElf(aSimName);
	if((elf_res==NULL) || (elf_res->mSize==0))
	{
		printf("file load error\n");
		return ERR_CANT_OPEN_EXE;
	}

	// file is loaded
	uint32 pc_count = Device->GetPc(0);
#ifdef USE_DWARF
	//get number for dwarf instance//nesterenko
	ElfFileNumber = CreateDwarfInstance(aSimName);
#endif  
	// wait for the end of the program
	int cw = 0;
	int num_cycles = aWait*MUL_FACTOR;
	int reg_res;
	uint32 prev_tics = 0;
	/// initialization registers
 InitRegs();
  {
	// print init state of register
		// printf("Initial registers state:\n");
		// InitPrintRegs();
		// printf("\n");
	}

#ifdef USE_BREAK_POINTS
  if(IsDviFile(aSimName))
    Device->SetBreakPoint(elf_res->mSize);
  else
	 Device->SetBreakPoint(elf_res->mSize);
#endif
	printf("\n#### TRACE ####\n\n\
			\r-------------------------------------\n\
		    \rticks | address | opcode | assembler \n\
		    \r-------------------------------------\n");
	cur_pc = pc_count;
	// simulation cycle
	while(1)
	{
		char linec[128];
		uint32 cur_tics;
		cur_pc = Device->GetPc(0);

#ifndef USE_BREAK_POINTS
		if(lstr.StopPc==cur_pc)
			break;
#endif
		Device->DisAssembly(disasm,0,cur_pc,0);
		for(sptr = disasm; sptr!=&disasm[256]; sptr++)
			if(*sptr=='\n') *sptr = '\t';
		////check pc for executing code string in file
#ifdef USE_DWARF
		if (ElfFileNumber != -1) if (GetLineCode(ElfFileNumber, cur_pc, (char*)linec))
		{
			printf("Code line: %s\n", linec);//print code line
		}
#endif
		PRINT_LOG("get num cycles\n")
		cur_tics = Device->GetNumCycles();
		if(cur_tics > (prev_tics + 1))
			printf("      +%d wait\n",cur_tics - prev_tics - 1);
		PRINT_LOG("print line\n")
		printf("%05d %s", cur_tics, disasm);
		fflush(stdout);
		// execute StepInfo, check 
		PRINT_LOG("start \n")
		try
		{
			uint32 tmp_pc;
			do
			{
				PRINT_LOG("start step into\n")
  			Device->StepInto();
				PRINT_LOG("step finished, get pc\n")
				tmp_pc = Device->GetPc(0);    
			}while(cur_pc==tmp_pc);
		
			PRINT_LOG("check regs\n")
        printf("\n");
			if (CheckRegs((char*)upregs)) printf("%s", upregs); else printf("\n");
			upregs[0] = 0; 

			// PRINT_LOG("check fifos\n")
			// CheckFifos((char*)upregs); printf("%s",upregs);
			PRINT_LOG("end of check results\n")
		}
		catch(void* aHrv)
		{
			////check registers for update
      ErrorHeader* aHr = (ErrorHeader*)aHrv;
      if (CheckRegs((char*)upregs)) printf("%s", upregs); else printf("\n");
			upregs[0] = 0; //CheckFifos((char*)upregs);printf("%s",upregs);
			
      if (aHr->m_MsgType == MSGTYPE_EXIT)
      {
        // exit command - just exist from program
        break; //break from while loop
      }
      if(PrintErrorHandle(aHrv,cur_pc)==-1)
				return -1;
			ProcessWarns(cur_pc);
		}
    catch (ErrorHeader* Hdr)
    {
      if (Hdr->m_MsgType == MSGTYPE_EXIT)
        break;//
    } 
		catch(...)
		{
			printf("\n");
      break;
    }   

		prev_tics = cur_tics;
		num_cycles--;
		if(num_cycles == 0)
		{
			printf("timeout error\n");
			CheckPostProg();
			ProcessWarns(cur_pc);
			return -1;
		}
		fflush(stdout);

#ifdef USE_BREAK_POINTS
		if(!Device->IsRun())
			break;
#endif  
	} // end while

	if (IsOutCode)
	{
		printf("\n\n#### OUTPUT ####\n\n");
	}

	CheckPostProg();
	ProcessWarns(cur_pc);
	// after the end of the program we get the value of the "test register"


	  if(CheckResult)
	  {
		  Device->GetReg(OUT_TEST_REG, OUT_TEST_REG_ARR, (char*)&reg_res);
		  if (reg_res != REG_TEST_VAL) // wrong test register value
		  {
			  printf("error: wrong result of the program execution: return value = %d\n",reg_res);
			  return -1;
		  }
	  }
	  // print successful result
	  printf("success:  cycles = %d, %d warnings occurred\n",Device->GetNumCycles(),num_warns);
	  
    if (IsRetValue)
	  {
		  Device->GetReg(0, OUT_TEST_REG_ARR, (char*)&reg_res);
		  printf("return value = %d\n", reg_res);
		  if (!IsOutZero)
		    return reg_res;
		  else
		    return 0;
	  }
	  //print full time and middle time on each instruction
	//printf(", time = %lu, cycles per instruction = %f\n", dif, midtime);
	// clear breakpoint
	Device->ClearBreakPoint(pc_count + PC_START_OFFSET);
	//clear register massive//nesterenko
	if ((RegVal!=NULL) && (RegNames!=NULL)){
		delete RegVal;
		delete RegNames; 
	}
	return 0;
}



int RunSimulationNoOut(char* aSimName,uint32 aWait)
{
  tDisAsmArea* elf_res;
	int is_hi_addr = 0;
	unsigned long counter;
	
	num_warns = 0;
	uint32 cur_pc;
	uint32 mytest_start; 
	
  // reset device
	PRINT_LOG("device reset\n");
	Device->Reset(); 
	PRINT_LOG("load elf\n");

	// load an executable file
  elf_res = Device->LoadElf(aSimName);
  if ((elf_res == NULL) || (elf_res->mSize == 0))
  {
		printf("file load error\n");
		return ERR_CANT_OPEN_EXE;
	}


  if (SecondDevFileName != NULL)
  {
    if (SecondDev == NULL)
    {
      printf("can't load second abs into single core system\n");
      return ERR_CANT_OPEN_EXE;
    }
    if (SecondDev->LoadElf(SecondDevFileName) == NULL)
    {
      printf("can't load input abs file %s\n",SecondDevFileName);
      return ERR_CANT_OPEN_EXE;
    }
  }
	// check Stack area
	SetStackControl(aSimName);  

	// file is loaded
	uint32 pc_count = Device->GetPc(0);
	// wait for the end of the program
	int cw = 0;
	int num_cycles = aWait*MUL_FACTOR;
	int reg_res;

	unsigned long end_pc = 0x7FFFFFFF;
	cur_pc = Device->GetPc(0);
	//Device->SetBreakPoint(lstr.StopPc);
	// start 
	do
  {
	  PRINT_LOG("THREAD:start execution\n");
    try
    {
      while (true)
      {
        Device->StepInto();
      }
    }
    catch (...)
    {
    }
    PRINT_LOG("THREAD:stop execution\n");
    CheckPostProg();
    cur_pc = Device->GetPc(0);
    {
      int process_warn = ProcessWarns(cur_pc);

      if (process_warn == 0)
        return -1;
      else if (process_warn == 2)
        break;
    }

	}while(cur_pc!=end_pc);

	PRINT_LOG("out of while\n");

	CheckPostProg(); 
	ProcessWarns(cur_pc);
	
	// post-process profiling if need
	if(BuildProfile)
	{
		//Profiler p(LOG_FILE_NAME,Device,aSimName);
		//p.Run(ProfileFileName);
	}


	// after the end of the program we get the value of the "test register"
	if(!CheckResult)
	{
	    printf("success: cycles = %d, %d warnings occuired\n",Device->GetNumCycles(),num_warns);
      if (IsRetValue)
      {
        Device->GetReg(OUT_TEST_REG,7,(char*)&reg_res);
        printf("return value = %d\n",reg_res);
        if (!IsOutZero)
          return reg_res;
        else 
          return 0; 
     } // if (IsRetValue)
  }
	else
	{
    Device->GetReg(OUT_TEST_REG,OUT_TEST_REG_ARR,(char*)&reg_res);
		if(reg_res!=REG_TEST_VAL) // wrong test register value
		{
			printf("error: wrong result of the program execution: return value = %d\n",reg_res);
			return -1;
		}
		// print successful result
		printf("success: cycles = %d, %d warnings occuired\n",Device->GetNumCycles(),num_warns);
		// clear breakpoint
	}

  if(IsDviFile(aSimName))
  {
//    Device->SetBreakPoint(elf_res->mEndPoint);
  }
  else
  {
    Device->ClearBreakPoint(pc_count + PC_START_OFFSET);
  }  
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_DWARF
cDwarfHandler CreateDwarfInstance(char* elfpath)
{
	ELF* new_elf = new ELF(elfpath, ELF_C_READ);
	Dwarf_Debug* new_dbg;
	try 
	{
		new_dbg = new Dwarf_Debug(new_elf);
	}
	catch (Dwarf_Error_Debug dwarf_dbg) 
	{ 
//		std::cout <<dwarf_dbg;
		return -1; 
	}
	//должен вернуть int-овскую переменную(индекс в списке)
	return setElem.Add(new_dbg);
}

int DwarfGetFileLine(cDwarfHandler aHandler,cPcVal aVal,int& aLine, char* aFileName)
{
	Dwarf_Debug* dbg = setElem.GetElem(aHandler);

	if(!dbg)
		return 0;

	Dwarf_Line_Tab* lineTab;
	Dwarf_Line* line;
	Dwarf_Line_Tab* slide;

	Dwarf_CU* cu = dbg->next_cu(0);
	//получаем таблицу ограничений
	Dwarf_Arange_Tab* arangeTab = dbg->get_arangeinfo();
	//получаем диапазон ограничений для aVal
	Dwarf_Arange* arange;
	try{ 
		arange = arangeTab->get_arange(aVal); 
	}
	catch(Dwarf_No_Entry)
	{ 
		return 0; 
	}
	
	//получаем CU через ограничение
	cu = arange->cu();
	//получаем таблицу строк
	lineTab = cu->get_lineinfo();
	//поиск в CU строки с PC равным aVal
	try 
	{ 
		line = lineTab->pcline(aVal,slide->DW_DLS_NOSLIDE); 
	}
	catch(Dwarf_No_Entry)
	{ 
		return 0; 
	}

	aLine = line->lineno();//номер строки
	strcpy(aFileName, line->file()->fullname());//имя файла
	return 1;
}
#endif

char usage_text[] = "usage: cemu [keys] [-bsp bsp_file_name]simulator_lib_name executable file name <max_num_cycles>\n"\
  "  max_num_cycles - optional parameter, maximal numbers of MILLIONS of cycles"\
  "keys:\n"\
  "  -bsp bsp_file_name - use memory map as defined in bsp_file_name\n"\
	"  -flags=WARN_FLAGS,WARN_FLAGS- warnings bit mask\n"\
	"  -nw - no warnings: disable warnings \n"\
	"  -nt - no trace: disable instruction trace output\n"\
	"  -nd - no data: disable output of register values\n"\
	"  -cr - check test result value (gr0 must be equal to 0)\n"\
	"  -p  - create profile (executed with -nt only), this options disables warning and trace output)\n"\
	"  -ru - russian language (english by default)\n"\
	"  -rv - return value, tracer returns the result of program execution;\n"\
	"  -rp - print return value, but returns 0 if success, -1 or -2 if error;\n"\
	"  -lmem - out log of memory operations;\n"\
	"  -ra - print all 'gr', 'ar' values every tact;\n"\
	"  -gas GASLIMIT - gas limit for the evm (default: 10000000000, '-gas 0x0' - set infinite gas);\n";


void usage(int exit_code)
{
	printf(usage_text);
	exit(exit_code);
}

int main(int argc,char* argv[])
{
	char* sim_dll_name;
	uint32 wait_time = 10;
	int sim_args_start = 1;
	int i_args = 1; 

	PreInitFlags();
	default_config_file = 1;
	ConfigFileName = NULL;//"mc5103.cfg";

	while(i_args < argc)
	{
		if(argv[i_args][0] == '-')
		{
			if(!strcmp(argv[i_args],"-nt"))
			{
				  IsOutCode = 0;
			}
      if (!strcmp(argv[i_args], "-lmem"))
      {
        IsLogMem = 1;
      }
      if (!strcmp(argv[i_args], "-ra"))
      {
		IsPrintArGr = 1;
      }
      else if(!strcmp(argv[i_args],"-rv"))
      {
        IsRetValue = 1;
      }
      else if (!strcmp(argv[i_args], "-pv"))
      {
        IsRetValue = 1;
        IsOutZero  = 1;
      }
      else if (!strcmp(argv[i_args], "-nw"))
			{
				IsWarnFlags = 0x0;
			}
			else if(!strcmp(argv[i_args],"-nd"))
			{
				IsShowData = 0;
			}
			else if(!strcmp(argv[i_args],"-cr"))
			{
        CheckResult = 1;
			}
			else if(!strcmp(argv[i_args],"-p"))
			{
				BuildProfile = 1;
				if(argv[i_args+1]==NULL)
					ProfileFileName = "defaul_prof.txt";
        else if(argv[i_args+1][0]=='-')
        {
          printf ("error profiler output file name %s\n",argv[i_args+1]);
          exit(-1);
        }
        else
				{
					ProfileFileName = argv[i_args+1];
					i_args++;
				}
        // no trace output
        IsOutCode = 0;
        // no warnings
        IsWarnFlags = 0x0;
			}
			else if(!strcmp(argv[i_args],"-ru"))
			{
				IsRusLang = 1;
			}
			else if(!strcmp(argv[i_args],"-en"))
			{
				IsRusLang = 0;
			}
			else if(!strcmp(argv[i_args],"-bsp"))
			{
				if(argv[i_args+1]==NULL)
				{
					printf("no config file entered\n");
					exit(-1);
				}
				// set name of bsp
				ConfigFileName = argv[i_args+1];
				default_config_file = 0;
				i_args++;
			}
			else if(!strcmp(argv[i_args],"-gas"))
			{
				if(argv[i_args+1]==NULL)
				{
					printf("no GAS limit was set\n");
					exit(-1);
				}
				// set GAS limit
				try {
					char gasLimitString[255];
					int isHexValue = 0;
					if(argv[i_args+1][0]!='0' || argv[i_args+1][1]!='x')
					{
						GasLimitValue = strtol(argv[i_args+1], NULL, 10);
						sprintf(gasLimitString, "%d", GasLimitValue);
					} else {
						GasLimitValue = strtol(argv[i_args+1], NULL, 16);
						sprintf(gasLimitString, "%x", GasLimitValue);
						isHexValue = 2; // strip '0x' prefix in hex value check
					}
					if (strlen(gasLimitString) != strlen(argv[i_args+1]) - isHexValue)
					{
						printf("invalid GAS limit value syntax\n");
						exit(-1);
					}
				} catch (...) {
					printf("invalid GAS limit value\n");
					exit(-1);
				}
				// if Gas limit was set 0x0 - set infinite GAS
				if (GasLimitValue == 0x0) {
					GasLimitValue = GasMaxLimitValue;
				}
				i_args++;
			}
			else if(!strncmp(argv[i_args],"-flags",strlen("-flags")))
			{
				char str_num[256];
				int is_success = 1;
				char *num_str = argv[i_args] + strlen("-flags=");
				uint32 warn_flags = GetHex<uint32>(num_str,str_num,&is_success);
				if(num_str[strlen(str_num)]!=0)
				{
					printf("wrong flag option value %s\n",argv[i_args]);
					exit(-1);
				}
				IsWarnFlags &= warn_flags;
			}// end if(!strcmp(...
			// next arg
			i_args++;
		}
		else
		{
			sim_args_start = i_args;
			break;
		}
	}


	if(argv[sim_args_start]==NULL)
	{
		printf(" error: simulator name is not entered as a program's argument\n");
		usage(ERR_NO_SIM_NAME);
	}

	if(argv[sim_args_start+1]==NULL)
	{
		printf(" error: execute file name is not entered as a program's argument\n");
		usage(ERR_NO_SIM_NAME);
	}
	// set waiting time
#if 1 //def WIN32  
	if(argv[sim_args_start+2]!=NULL)
	{
    char* arg_name = argv[sim_args_start + 2];
    int   arg_len  = strlen(arg_name); 

    if ((arg_name[arg_len - 3] == 'a') && (arg_name[arg_len - 2] == 'b') && (arg_name[arg_len - 1] == 's'))
    {
      SecondDevFileName = arg_name;
    }
    else
    {
      
		  int len;
		  int is_float;
		  wait_time = GetDig<uint32>(argv[sim_args_start+2],len,is_float);
		  if(!wait_time)
		  {
			  wait_time = 10; // wait for 10 000 000 cycles
			  printf(" warning: waiting time has not been set properly\n");
		  }
    }// if ((arg_name[arg_len - 3] == 'a') && (arg_name[arg_len - 2] == 'b') && (arg_name[arg_len - 1] == 's'))
	}
#else
	wait_time = 10000; // wait for 10 000 cycles
#endif


#ifdef WIN32
	// try to load dll
	LibHandler = LoadLibrary(argv[sim_args_start]); 
	if(LibHandler==NULL) // error during the dll loading - wrong file name
	{
		printf("error: can't read simulator library\n");
		exit(ERR_WRONG_SIM_NAME); // 
	}
#else
	LibHandler = dlopen(argv[sim_args_start], RTLD_GLOBAL | RTLD_LAZY);
	if(LibHandler==NULL) // error during the dll loading - wrong file name
	{
		printf("error: can't read dll: %s\n", dlerror());
		return (ERR_WRONG_SIM_NAME); // 
	}
#endif

	if(!Init())
		exit(ERR_CANT_INIT_SIM_API);
  int retcode;


	if(IsOutCode)
		retcode = RunSimulation(argv[sim_args_start+1],wait_time);
	else
		retcode = RunSimulationNoOut(argv[sim_args_start+1],wait_time);

	exit(retcode);
  return retcode;
}

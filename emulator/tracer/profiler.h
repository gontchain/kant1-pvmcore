#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <iosfwd>

//#include "common.h"
#include "datatypes.h"

#ifndef uint32_t 
#define uint32_t uint32
#endif
//typedef uint32 uint32_t;


#include "logger.h"

#include <dbg_interface.h>

// dwarf related headers
#include "libelf.h"
#include "lists.h"
#include "dwarftyp.h"
#include "dwarf.h"
#include "dwarferr.h"
#include "libdwarf.h"
#include "dwarferr.h"

using namespace std;


#define NULL_ASM "null asm"
#define DISASM_MAX_LEN 85
// offset between addresses of 
//  call and  addres of return
#define CALL_RETURN_OFFSET 4



#define CALL_JUMP_MASK	((0x7<<28)|(1<<25)|(0x3<<20))	//0x72300000

#define INST_JUMP       ((0x0<<28)|(0<<25)|(0x2<<20))
#define INST_CALL       ((0x0<<28)|(1<<25)|(0x2<<20))
#define INST_JUMP64  	((0x4<<28)|(0<<25)|(0x2<<20))
#define INST_CALL64	((0x4<<28)|(1<<25)|(0x2<<20))

#define RETURN_MASK	((0x7<<28)|(31<<20)|(7<<25))
#define RETURN          ((0x0<<28)|(31<<20)|(4<<25))

#define WSUM_MASK		0x00000C00
#define WSUM_VALUE		0

#define MAX_MUL_COEFF 20

extern const char *EventTypeDictionary[NumberOfEventsTypes];
        
        
typedef struct{        
        // address of the instruction
        uint32_t i_addr;
        // длительность исполнения инструкции
        int i_duration;
        int i_last_cur_cycle;
        int i_waits_cur_cycle;
        
        // возможные причины задержки
        int i_waits;
        int i_reg_locks;
        int i_reg_check_false;
        
        // причина долгого исполнения инструкции
        std::string i_long_execution_cause;
        std::string i_blocked_registers;
        // количество исполненй данной инструкции
        int i_iteration;
	// количество обращений к памяти
        int i_mem_access;
        // ожидание чтения из памяти данных
        int i_mem_acc_delay;

    } instr_stat;

typedef struct func_stat{
        uint32_t f_addr;
        uint32_t f_end_addr;
        int f_execution_time;
        int f_clear_execution_time;
	int f_total_execution_time;
        int f_iteration;
	std::map<uint32_t, int> nest;
    } func_stat;
        
typedef struct jump_stat{
        int j_iteration;
        int j_executed_jump;
        int j_nonexecuted_jump;
      	int j_true_delay;
	      int j_false_delay;
    } jump_stat;
	
typedef struct prof_stat{
        // общее время работы 
        int totalExecTime;
        
        // время работы скалярного процессора
        int scalarExecTime;
        
        // время работы векторного процессора
        int vectorExecTime;
        
        // кол-во обращений к внутренней памяти
        int internalMemoryAccess;
        
        // кол-во обращения к внешней памяти
        int externalMemoryAccess;
        
        // суммарное время задержки обращений к памяти
        int totalDelayMemoryAccess;
        
        // кол-во переключений страниц
        int totalSwitchingPage;
        
        // суммарное время переключений
        int timeSwitchingPage;
        
        // доля переключений в общем времени
        int percentageSwitchingPage;
        
        // время регенерации по кажд. блоку памяти
        std::map<uint32_t, int> regenDelay;
        
        // время простоя конвейера в тактах
        int pipelineDowntime;
        
        int w_sum;

	int readingInstrFromMem;
        
    } prof_stat;        

                    
class Profiler{    
private:

    FILE *logFile;

    std::ofstream f_out;

    int logFileSize;

    int numberOfEvents;

    // memory to keep log file
    TLogEvent *Events;
    
    prof_stat RESULT;

    // блокировки на этапе декодирования
    std::map<uint32_t, instr_stat> InstrLock;    

    std::map<uint32_t, func_stat>  functions;

    std::map<uint32_t, jump_stat>  jumps;

	TDbgInterface    *Device;
	Dwarf_Debug		 *DbgInfo;
	ELF				 *ElfFile;

	Dwarf_Die* GetDieFuncName(Dwarf_Die* aStartDie,uint32 aAddr);
	std::string GetFunctionName(uint32_t address);

  int DwarfGetFileLine(uint32_t aVal,int& aLine, char* aFileName);
  int PrintDwarfInstruction(uint32_t addr,char* result); 
  bool DwarfFilesOk;

public:
	// returns 1 if the instruction is jump
	inline int IsJumpInst(uint32_t inst)
	{
		uint32_t inst_masked = inst & CALL_JUMP_MASK;
		return (inst_masked == INST_JUMP)||(inst_masked == INST_JUMP64);
	}
	// returns 1 if the instruction is call
	inline int IsCallInst(uint32_t inst)
	{
		uint32_t inst_masked = inst & CALL_JUMP_MASK;
		return (inst_masked == INST_CALL)||(inst_masked == INST_CALL64);
	}


	void tree_call_hierarchy(uint32_t addr, int nesting_level, int my_repeats);
	
  
  // Print Instruction's stat
	int PrintInstruction(map<uint32_t, instr_stat>::iterator& iter,ofstream& f_out);

    // constructor
    // opens log file and
    // copies all logs to array Events
    Profiler(const char *logFileName,TDbgInterface *aDevice,const char* aInpFIle);
    
    // this method returns 
    // instruction type
    // return: 0 - scalar
    //         1 - vector
    //        -1 - error
    int GetInstrType(uint32_t address);
    
    // returns instruction opcode
    uint32_t GetInstruction(uint32_t address);

    // this method writes
    // disassembled instruction
    // in aOutString 
    void Disasm(uint32_t address, char* aOutString);
    
    // this method is for
    // checking if block is from internal or
    // external memory
    // return: 1 - internal memory
    //         0 - external memory  
    int MemoryBlockLocation(uint32_t block_address);
    
    // this method parses the log file
    // fills struct prof_stat
    void Run(char* aOutName); 
    
    // destructor
    // frees taken memory
    // and closes log file
    ~Profiler();
    
};


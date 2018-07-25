#include "profiler.h"

#include <stdlib.h>
#include <stdio.h>

#define CALL_RETURN_OFFSET 4
#define REG_LOCK "Blocking due to unavailability of register"
#define REG_CHECK_FALSE "Blocking due to unavailability of FIFO"


// itoa is missing
#ifndef WIN32
       
char* itoa (int value, char * buffer, int radix);
       
/* This is no strict ANSI definition, and not in newlib */
char* itoa (int value, char * buffer, int radix) {
  if (sprintf(buffer, "%d", value)) return buffer;
  else return NULL;
}
       
#endif

void reeplachar(char *buff, char old, char neo){
    char *ptr;        
    for(;;){
        ptr = strchr(buff, old);
        if(ptr==NULL) break; 
        buff[(int)(ptr-buff)]=neo;
    }        
    return;
}

const char *EventTypeDictionary[NumberOfEventsTypes] = {
  "LOG_INSTRUCTION_BEGIN",// {LOG_INSTRUCTION inst_addr,inst_start_time}
  "LOG_INSTRUCTION_END",  // {LOG_INSTRUCTION inst_addr,inst_end_time}
  "LOG_MEM_BUS_ACCESS",   // {LOG_MEM_BUS_ACCESS, BUS_PTR, addr, cur_cycle, lock_cycle}
  "LOG_MEM_BLOCK_ACCESS", // {LOG_MEM_BLOCK_ACCESS, BLOCK_PTR, addr, cur_cycle, lock_cycle}
  "LOG_PAGE_SELECT",      // {LOG_PAGE_SELECT, BLOCK_PTR, cur_cycle, lock_cycle}
  "LOG_REGEN_SDRAM",      // {LOG_REGEN_SDRAM, BLOCK_PTR, cur_cycle, shift_delay}
  "LOG_REG_LOCK",         // {LOG_REG_LOCK, BLOCK_PTR, cur_cycle, regen_delay}
  "LOG_REG_CHECK_FALSE",  // {LOG_REG_CHECK_FALSE,REG_PTR,cur_cycle}
  "LOG_WAIT"              // {LOG_WAIT,0,cur_cycle}
};


Profiler::Profiler( const char *logFileName,TDbgInterface *aDevice,const char* aInpFile)
{
  Device = aDevice;

  if (!(logFile = fopen(logFileName, "rb"))){
    perror("The following error is occured:");
    exit(-1);
  }

  // get length of log file
  fseek(logFile, 0, SEEK_END);
  logFileSize = ftell(logFile);
  fseek(logFile, 0, SEEK_SET);

  if ( logFileSize == 0 ){
    std::cout<<"The following error is occured: log file size is 0"<<std::endl;
    exit(-1);
  }

  //std::cout<<"LogFile size is "<<logFileSize<<std::endl;
  // get memory for all events from file
  Events = (TLogEvent*)malloc(logFileSize);

  // put all logEvents to array Events
  int read;
  if ((read = fread(Events, logFileSize, 1, logFile)) != 1 ){
    std::cout<<"The following error occured: can't read file, read "<<read<<" bytes"<<std::endl;
    exit(-1);
  }
  numberOfEvents = logFileSize/sizeof(TLogEvent);


  RESULT.totalExecTime = 0;
  RESULT.scalarExecTime = 0;
  RESULT.vectorExecTime = 0;
  RESULT.internalMemoryAccess = 0;
  RESULT.externalMemoryAccess = 0;
  RESULT.totalDelayMemoryAccess = 0;
  RESULT.totalSwitchingPage = 0;
  RESULT.timeSwitchingPage = 0;
  RESULT.percentageSwitchingPage = 0;
  RESULT.pipelineDowntime = 0;
  RESULT.w_sum = 0;
  RESULT.readingInstrFromMem = 0;
  fclose(logFile);
  //////////////////////////////// try do create DWARF_INSTANCE
  if(aInpFile!=NULL)
  {
    try
    {
      ElfFile = new ELF(aInpFile, ELF_C_READ);
      DbgInfo = new Dwarf_Debug(ElfFile);
    }
    catch(ELF_ERROR* err)
    {
      std::cout<< "error while getting DWARF info:" << *err <<endl;
      ElfFile = NULL;
      DbgInfo = NULL;
    }
    catch(...)
    {
      std::cout<< "unknown error while trying to get DWARF info" <<endl;
      ElfFile = NULL;
      DbgInfo = NULL;
    }
  } // end if(aInpFile!=NULL)
}    
// 0 -scalare
// 1 - vector
int Profiler::GetInstrType(uint32_t opcode){
  int inst_type = Device->GetInstructNum((uint64)opcode);
  return inst_type == 3; // return 1 if the insturction is vector, 0 if the scalar
}

int Profiler::DwarfGetFileLine(uint32_t aVal,int& aLine, char* aFileName)
{
	Dwarf_Debug* dbg = DbgInfo;

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


int Profiler::PrintDwarfInstruction(uint32 addr,char* result)
{
	char fname[256];
	char buf[512];
  int lineno;
	char *res;

	//if PC correspond to code line
	if(!DwarfGetFileLine(addr, lineno, fname))
    return 0;

  {
		FILE *f;
		int cnt = 0;

#ifdef WIN32
    reeplachar(fname,'/','\\');
#endif

		f = fopen(fname, "rt");
		if (f==NULL)
    {
      if(DwarfFilesOk)
      {
        printf(" DWARF error: can't find file %s\n",fname);
        DwarfFilesOk = false;
      }
      return 0;
    } //if (f==NULL)

    while (!feof(f)){
      //read strings until position != lineno or EOF
      res = fgets(buf, 512, f);
      cnt++;
      if (cnt==lineno)
      {
//        sprintf(result,"%s line %d: %s",fname,lineno,buf);
        sprintf(result,"%s",buf);
        break;
      }
    }	// while (!feof(f)){

    fclose(f);
    return (cnt == lineno);

  } //if(DwarfGetFileLine(addr, lineno, fname)){
  return 0;
}

int Profiler::PrintInstruction(map<uint32_t, instr_stat>::iterator& iter,ofstream& f_out)
{
  int	   i;
  uint32 addr = (*iter).first;
  int    inst_size = 0;
  char   disasm[512]; 
  char*  sptr;
  int	   disasm_len;
  uint32 mems[2];
  char   dwarf_inst[1024];

  if(PrintDwarfInstruction(addr,dwarf_inst))
  {
    f_out << endl << std::string(dwarf_inst);
  }

  //print function name if need
  if(functions.count(addr))
  {
    //
    std::string str = GetFunctionName(addr);
    f_out << endl << GetFunctionName(addr) << ":" << endl;
  }


  Device->DisAssembly(disasm,0,addr,inst_size);
  inst_size = 1 + (Device->GetInstructNum(GetInstruction(addr)) == 2);

  for(sptr = disasm; sptr!=&disasm[512]; sptr++)
    if(*sptr=='\n') *sptr = ' ';

  disasm_len = strlen(disasm);

  for(i = disasm_len ;i <DISASM_MAX_LEN; i++)
    disasm[i] = ' ';

  disasm[i] = 0;

  f_out<< disasm << setw(10) << dec << setw(10) << (*iter).second.i_iteration << setw(10) << (*iter).second.i_duration ;

  if( (*iter).second.i_duration > 1 )
  {        

    if((*iter).second.i_waits)
      f_out << " waits(" << (*iter).second.i_waits << ")";

    if((*iter).second.i_reg_check_false) 
      f_out << " instruction fetching(" << (*iter).second.i_reg_check_false << ")";//<<endl;

    if ((*iter).second.i_reg_locks) 
      f_out << " register locks(" << (*iter).second.i_blocked_registers << ") ";

    if(jumps.count(addr)!= NULL)
    {
      f_out << " jumps executed(" << jumps[addr].j_executed_jump << ") jump delay(" << jumps[addr].j_true_delay << ")";
      f_out << " jumps missed(" << jumps[addr].j_nonexecuted_jump << ") no jump delay(" << jumps[addr].j_false_delay << ")";
    }
    
//    if ((*iter).second.i_mem_access) 
//      f_out << " mem accesses(" << (*iter).second.i_mem_access << ") ";
    
//    if ((*iter).second.i_mem_acc_delay) 
//      f_out << " mem_acc delays(" << (*iter).second.i_mem_acc_delay << ") ";
  } 
  f_out<<endl;	
  return inst_size;
}

int Profiler::MemoryBlockLocation(uint32_t block_address)
{
  int is_external = in_between(block_address,0x10000000,0x80000000) || (block_address > 0xA0000000);
//  printf("addr %08X, is_external  = %d\n",block_address,is_external);
  return  is_external;
}

uint32_t Profiler::GetInstruction(uint32_t address)
{
  uint32_t instr;
  Device->GetProgMem((void*)&instr,address,4);
  return instr;
}

Dwarf_Die* Profiler::GetDieFuncName(Dwarf_Die* die,uint32 aAddr)
{

  while(die!=NULL)
  {
    Dwarf_Half tag = die->tag(); 
    if( tag == DW_TAG_subprogram)
    {
      Dwarf_Addr low_addr = die->lowpc(); 
      Dwarf_Addr hi_addr  = die->highpc(); 
      //			printf("func %8X,name %s\n",addr,die->name());
      if((low_addr == aAddr)/*||(hi_addr == aAddr)*/)
      {
        return die;
      }
    }//if(die->tag() == DW_TAG_subprogram)
    else if(die->tag() == DW_TAG_compile_unit)
    {
      Dwarf_Die* res_die = GetDieFuncName(die->child(),aAddr);
      if(res_die!=NULL)
        return res_die;
    }
    die = die->next();
  }// while(die!=NULL);

  return NULL;
}


std::string Profiler::GetFunctionName(uint32_t address)
{
  char dig_buf[256];

  if(DbgInfo!=NULL)
  {
    Dwarf_CU* cu = NULL; 
    while( (cu=DbgInfo->next_cu(cu))!=NULL)
    {
      Dwarf_Die* die = cu->get_first_die();
      die = GetDieFuncName(die,address);
      if(die!=NULL)
      {
        return std::string(die->name());
      }
    }//while( (cu=DbgInfo->next_cu(cu))!=NULL)
  }

  sprintf(dig_buf,"Nonamed_%08X",address);
  return std::string(dig_buf);
}



void Profiler::tree_call_hierarchy(uint32_t addr, int nesting_level, int my_repeats)
{
  std::map<uint32_t, int>::iterator i = functions[addr].nest.begin();
  int j;

  for (j = 0; j < nesting_level; j++)
  {
    f_out<<"    ";
  }

  f_out << std::setw(64-4*j);
  f_out << GetFunctionName(addr);
  f_out << "0x" << std::setw(10) << std::hex << addr;
  f_out << std::setw(16) << std::dec << my_repeats;
  f_out << setw(7) << right << 100*(static_cast<double>(functions[addr].f_total_execution_time))/(static_cast<double>(RESULT.totalExecTime)) << "% " << left<< std::endl;

  for (i = functions[addr].nest.begin(); i != functions[addr].nest.end(); i++)
  {
    tree_call_hierarchy((*i).first, nesting_level+1, (*i).second);
  }
}

void Profiler::Run(char* aOutName)
{
  bool instruction_end, was_jump, func_return; 
  char DisassemledInstriction[256];
  int i = 0;
  int waits, reg_locks, reg_check_false;
  string reg_lock_reason;
  int instructionCounter = 0;							 
  int prevInstAddress = Events->Data[0];
  int jumpInstAddr;
  int instrStartTime = 0;
  int InstructionCoutner = 0;
  int regen_time  = 0; 
  int jump_delay;
  std::stack<func_stat> FunctionsCallStack;


  was_jump = false;

  printf("Start profiling log analysis\n");
  while (1)
  {
    instruction_end = false;    
    while ( (instruction_end == false) && (i< numberOfEvents) )
    {
      if ( (Events+i)->Event == LOG_INSTRUCTION_BEGIN )
      {

        InstructionCoutner++;
        // at the beginning of new instruction
        // find if the instruction has been exectued at least once
        if ( InstrLock.count((Events+i)->Data[0]) == 0 )
        {
          // no - create new inst strut
          InstrLock[(Events+i)->Data[0]].i_addr = (Events+i)->Data[0];
          InstrLock[(Events+i)->Data[0]].i_waits = 0;
          InstrLock[(Events+i)->Data[0]].i_reg_locks = 0;
          InstrLock[(Events+i)->Data[0]].i_reg_check_false = 0;
          InstrLock[(Events+i)->Data[0]].i_duration = 0;
          InstrLock[(Events+i)->Data[0]].i_iteration = 1;
          InstrLock[(Events+i)->Data[0]].i_mem_access = 0;
      	  InstrLock[(Events+i)->Data[0]].i_mem_acc_delay = 0;
        } else if ( InstrLock.count((Events+i)->Data[0]) == 1 ) {
          // exist
          InstrLock[(Events+i)->Data[0]].i_iteration++;
        }

        reg_lock_reason = "";
        waits = reg_locks = reg_check_false = 0;
        InstrLock[(Events+i)->Data[0]].i_last_cur_cycle = (Events+i)->Data[1];

        uint32_t instr = GetInstruction((Events+i)->Data[0]);

        if ( was_jump )
        {
          if( ( abs(static_cast<int>((Events+i)->Data[0]) - static_cast<int>(jumpInstAddr&(~1))) > 3 ) || (abs(static_cast<int>((Events+i)->Data[0]) == jumpInstAddr)) )
          {
            jump_delay =  (Events+i)->Data[1] - InstrLock[jumpInstAddr].i_last_cur_cycle;
            if( static_cast<int>((Events+i)->Data[0]) != ((static_cast<int>(jumpInstAddr)&(~1)) + 4) ) //jump occuired
            {
              jumps[jumpInstAddr].j_executed_jump++;               
              jumps[jumpInstAddr].j_true_delay += jump_delay;
            } 
            else 
            {
              jumps[jumpInstAddr].j_nonexecuted_jump++;
              jumps[jumpInstAddr].j_false_delay += jump_delay;
            }//if(static_cast<int>(Events+i)->Data[0]) != ((jumpInstAddrjumpInstAddr&(~1)) +4 ) ) 
            was_jump = false;
          }// if ( abs(static_cast<int>((Events+i)->Data[0]) - static_cast<int>(jumpInstAddr&(~1))) > 3 )
        }
        // if this instruction is jump then
        if ( IsJumpInst(instr) )
        {
          jumpInstAddr = (Events+i)->Data[0];
          if ( jumps.count(jumpInstAddr) == 0 )
          {
            jumps[jumpInstAddr].j_iteration = 1;
            jumps[jumpInstAddr].j_executed_jump = 0;
            jumps[jumpInstAddr].j_nonexecuted_jump = 0;
            jumps[jumpInstAddr].j_true_delay = 0;
            jumps[jumpInstAddr].j_false_delay = 0;
          } else {
            jumps[jumpInstAddr].j_iteration++;
          }
          was_jump = true; 
        } else if ( IsCallInst(instr) ){
          // put address into FunctionsCallStack
          func_stat call;
          uint32_t instr;
          Device->GetProgMem((void*)&instr,(Events+i)->Data[0] + 1,4);

          call.f_addr = instr;
          call.f_execution_time = 0;
          call.f_clear_execution_time = 0;
          call.f_total_execution_time = 0;

          if (!FunctionsCallStack.empty())
          {
            if (FunctionsCallStack.top().nest.count(instr) == 0)
            {
              FunctionsCallStack.top().nest[instr] = 1;
            } else {
              FunctionsCallStack.top().nest[instr]++;
            }
          }

          FunctionsCallStack.push(call);

          // and fill proper structure
          if ( functions.count(call.f_addr) == 0 )
          {
            functions[call.f_addr].f_addr = instr;//(Events+i)->Data[0];
            functions[call.f_addr].f_iteration = 1;
            functions[call.f_addr].f_execution_time = 0;
            functions[call.f_addr].f_clear_execution_time = 0;
            functions[call.f_addr].f_total_execution_time = 0;
          } else {
            functions[call.f_addr].f_iteration++;
          }
        } else if ( (instr & RETURN_MASK) == RETURN ) {
          if( !FunctionsCallStack.empty() )
          {
            uint32_t addr = FunctionsCallStack.top().f_addr;
            if ( functions[addr].f_iteration == 1 )
              functions[addr].f_end_addr = (Events+i)->Data[0];
          }
          func_return = true;
        } else {
          func_return = false;
        //  was_jump = false; 
        }

        if ( GetInstrType(instr) == 1 )
        {
          if ( (instr & 0x00000C00) == 0 )
          {
            RESULT.w_sum++;
          }
        }   

        prevInstAddress = (Events+i)->Data[0];
        instrStartTime = (Events+i)->Data[1];

      } 
      else if ( (Events+i)->Event == LOG_REG_CHECK_FALSE ){

        reg_check_false++;
        InstrLock[prevInstAddress].i_last_cur_cycle = (Events+i)->Data[1];
        RESULT.readingInstrFromMem += 1;

      } 
      else if ( (Events+i)->Event == LOG_REG_LOCK )
      {
        char *reg_name;
        char name_buf[16];
        uint32_t reg_delay = (Events+i)->Data[2] - InstrLock[prevInstAddress].i_last_cur_cycle;

        reg_locks +=  reg_delay;
        reg_name = Device->GetNameFromPtr( (void*)(Events+i)->Data[0] );

        if(reg_name==NULL) 
          reg_name = "internal reg";

        reg_lock_reason = string(reg_name) + string(" ") + string(itoa(reg_delay,name_buf,10));

        InstrLock[prevInstAddress].i_last_cur_cycle = (Events+i)->Data[2];

      } else if ( (Events+i)->Event == LOG_WAIT ){

        waits++;
        InstrLock[prevInstAddress].i_waits_cur_cycle = (Events+i)->Data[1];

      } else if ( (Events+i)->Event == LOG_MEM_BLOCK_ACCESS ){

        InstrLock[prevInstAddress].i_last_cur_cycle = (Events+i)->Data[2];

      } 
      else if ( (Events+i)->Event == LOG_MEM_BUS_ACCESS )
      {
       
        InstrLock[prevInstAddress].i_last_cur_cycle = (Events+i)->Data[2];
        InstrLock[prevInstAddress].i_mem_access += 1;
        
        int delay = (Events+i)->Data[3] - (Events+i)->Data[2];
        if (delay > InstrLock[prevInstAddress].i_mem_acc_delay) {
          InstrLock[prevInstAddress].i_mem_acc_delay =+ delay;
        }
#define MEM_ACC_TIME_ADD(st)\
        {\
          uint32 start_time = st > (Events+i)->Data[2] ? st : (Events+i)->Data[2];\
          uint32 delay_time = (Events+i)->Data[3] - start_time;\
          st +=delay_time;\
          RESULT.totalDelayMemoryAccess += delay_time;\
        }
        
        if (MemoryBlockLocation((Events+i)->Data[1])){
          MEM_ACC_TIME_ADD(RESULT.externalMemoryAccess)          
        } else {
          MEM_ACC_TIME_ADD(RESULT.internalMemoryAccess)
        }

      } 
      else if ( (Events+i)->Event == LOG_REGEN_SDRAM )
      {
        regen_time = (Events+i)->Data[2];
        //printf("regeneration time %8X, len %d\n",(Events+i)->Data[1],regen_time);

        if ( RESULT.regenDelay.count((Events+i)->Data[0]) != 0 ){
          RESULT.regenDelay[(Events+i)->Data[0]] += regen_time;
        } else {
          RESULT.regenDelay[(Events+i)->Data[0]] = regen_time;
        }
        
        RESULT.timeSwitchingPage += (Events+i)->Data[2]; //!!! switching page
        RESULT.totalSwitchingPage++;
        InstrLock[prevInstAddress].i_last_cur_cycle = (Events+i)->Data[1];

      } else if ( (Events+i)->Event == LOG_PAGE_SELECT ){

        InstrLock[prevInstAddress].i_last_cur_cycle = (Events+i)->Data[1];

      } else if ( (Events+i)->Event == LOG_INSTRUCTION_END ){

        int inst_delta = (Events+i)->Data[1] - instrStartTime; 
        uint32_t cur_duration = static_cast<uint32_t>(InstrLock[(Events+i)->Data[0]].i_duration);
        instruction_end = true;
        
	// delay on "jump" execution
        if (was_jump) {
          jump_delay = inst_delta;
        }

        RESULT.pipelineDowntime += inst_delta - 1;
        RESULT.totalExecTime = (Events+i)->Data[1];

        int instr_type;
        if ((instr_type=GetInstrType(GetInstruction((Events+i)->Data[0]))) == 0){
          RESULT.scalarExecTime += inst_delta;
        } else if ( instr_type == 1 ){
          RESULT.vectorExecTime += inst_delta;
        }

        // if duration of this instruction is longer than earlier execution
        if( ( inst_delta > cur_duration) && ((inst_delta < cur_duration* MAX_MUL_COEFF) || (cur_duration > inst_delta*MAX_MUL_COEFF) || (cur_duration==0))  )
        {
          char buf[10];

          InstrLock[(Events+i)->Data[0]].i_duration = inst_delta ; 
          InstrLock[(Events+i)->Data[0]].i_waits = waits;
          InstrLock[(Events+i)->Data[0]].i_reg_locks = reg_locks;
          InstrLock[(Events+i)->Data[0]].i_blocked_registers = reg_lock_reason;
          InstrLock[(Events+i)->Data[0]].i_reg_check_false = reg_check_false;


          // here we figure out why instruction executed so long
          // if LOG_WAIT is the only cause of long execution
          if ((waits != 0) && (reg_locks == 0) && (reg_check_false == 0)){
            if ( waits == 1 ){
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause = "wait";
            } else {
              sprintf( buf, "%d", waits);
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause = string(buf);
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" waits");
            }
          } else if ( waits == 0){ // if there are no waits
            if ( reg_locks > reg_check_false ){
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause = REG_LOCK;
            } else if ( reg_locks < reg_check_false ){
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause = REG_CHECK_FALSE;
            } 
          } else if ( waits != 0 ){ // there are waits, reg_locks, and reg_check_falses
            if ( reg_locks > reg_check_false ){
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause = REG_LOCK;
              if ( InstrLock[(Events+i)->Data[0]].i_waits_cur_cycle > reg_locks ){
                if ( waits == 1 ){
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" + wait");
                } else {
                  sprintf( buf, "%d", waits);
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" + ");
                  string a(buf);
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(a);
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" waits");
                }
              }
            } else if ( reg_locks < reg_check_false ){
              InstrLock[(Events+i)->Data[0]].i_long_execution_cause = REG_CHECK_FALSE;
              if ( InstrLock[(Events+i)->Data[0]].i_waits_cur_cycle > reg_check_false){
                if ( waits == 1 ){
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" + wait");
                } else {
                  sprintf( buf, "%d", waits);
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" + ");
                  string a(buf);
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(a);
                  InstrLock[(Events+i)->Data[0]].i_long_execution_cause.append(" waits");
                }
              }
            }
          }
        }

        int exec_time = (Events+i)->Data[1] - instrStartTime;
        if ( !FunctionsCallStack.empty() )
        {
          FunctionsCallStack.top().f_execution_time += exec_time;
          FunctionsCallStack.top().f_clear_execution_time += exec_time;
          FunctionsCallStack.top().f_total_execution_time	+= exec_time;
        } 

        if ( func_return )
        {
          if(!FunctionsCallStack.empty())
          {
            int function_execution_time = functions[FunctionsCallStack.top().f_addr].f_execution_time;
            int function_total_execution_time = FunctionsCallStack.top().f_total_execution_time;

            functions[FunctionsCallStack.top().f_addr].f_clear_execution_time += FunctionsCallStack.top().f_clear_execution_time;
            functions[FunctionsCallStack.top().f_addr].nest = *(new map<uint32_t, int>(FunctionsCallStack.top().nest));
            functions[FunctionsCallStack.top().f_addr].f_total_execution_time += function_total_execution_time;						  
            function_execution_time = functions[FunctionsCallStack.top().f_addr].f_execution_time;

            // pop address from stack and add execution time to function                                
            FunctionsCallStack.pop();
            if (!FunctionsCallStack.empty()) 
            {
              FunctionsCallStack.top().f_execution_time += function_execution_time;
              FunctionsCallStack.top().f_total_execution_time += function_total_execution_time;
            }
          }
          func_return = false;
        }
      } else {
        cout<< "Unknown event, check events log file" <<endl;
      }
      i++;     
    }

    if (i >= numberOfEvents)
    {
      while (!FunctionsCallStack.empty())
      {
        int function_execution_time = functions[FunctionsCallStack.top().f_addr].f_execution_time;
        int function_total_execution_time = FunctionsCallStack.top().f_total_execution_time;
        functions[FunctionsCallStack.top().f_addr].f_clear_execution_time += FunctionsCallStack.top().f_clear_execution_time;

        functions[FunctionsCallStack.top().f_addr].nest = *(new map<uint32_t, int>(FunctionsCallStack.top().nest));
        functions[FunctionsCallStack.top().f_addr].f_total_execution_time += function_total_execution_time;
        function_execution_time = functions[FunctionsCallStack.top().f_addr].f_execution_time;

        // pop address from stack and add execution time to function                                
        FunctionsCallStack.pop();
        if (!FunctionsCallStack.empty()) 
        {
          FunctionsCallStack.top().f_execution_time += function_execution_time;
          FunctionsCallStack.top().f_total_execution_time += function_total_execution_time;
        } // end if
      }// end while (!FunctionsCallStack.empty())
      break;
    }

  }

  f_out.open(aOutName);
  f_out << "Total execution time : " << RESULT.totalExecTime << endl;
  f_out << "Scalar execution time :" << RESULT.scalarExecTime << endl;
  f_out << "Vector execution time :" << RESULT.vectorExecTime << endl;
  f_out << "Instructions in total : " << InstructionCoutner << endl;
  f_out << "Internal memory access time: " << RESULT.internalMemoryAccess << endl;
  f_out << "External memory access time: " << RESULT.externalMemoryAccess << endl;
  f_out << "Total time of memory access delays : " << RESULT.totalDelayMemoryAccess << endl;
  f_out << "Number of switching pages : " << RESULT.totalSwitchingPage << endl;
  f_out << "Total switching pages time : " << RESULT.timeSwitchingPage << endl;
  f_out << "Persentage of switching to the whole executing time : " << static_cast<double>(RESULT.timeSwitchingPage)/static_cast<double>(RESULT.totalExecTime) << endl;
  f_out << "Regeneration time of each emulated memory block : "<<endl;

  for ( map<uint32_t, int>::iterator iter = RESULT.regenDelay.begin(); iter!=RESULT.regenDelay.end(); iter++ )
  {
    f_out<<"\t" << "Memory block : "<<(*iter).first<<", regeneration time : "<<(*iter).second<<endl;
  }
  f_out << "Pipeline total downtime : "<< RESULT.pipelineDowntime<<endl;
  f_out << "Number of weighted sums : " << RESULT.w_sum << endl;
  f_out << "Instructions locks:  " << endl;

  f_out << endl << "Functions : " <<left<< endl;
  f_out << setw(48)<< "Name" << setw(12) << "Address" << setw(12) << "Repeats"  << setw(12) << "  Time" << setw(12) << "Clear" << setw(12) << "% of execution" << endl;
  
  for ( map<uint32_t, func_stat>::iterator it = functions.begin(); it != functions.end(); it++ ) 
  {
    f_out << setw(48) << GetFunctionName((*it).first);// << endl; // function name 
    f_out << "0x" << setw(12) << hex << (*it).first;// << endl;	 // address
    f_out << dec << setw(12) << (*it).second.f_iteration;// << endl;
    f_out << setw(12) << (*it).second.f_total_execution_time;// << endl;
    f_out << setw(12) << (*it).second.f_clear_execution_time;// << endl;
    f_out << setw(12) << right << 100*(static_cast<double>((*it).second.f_total_execution_time))/(static_cast<double>(RESULT.totalExecTime)) << "% " << left;// << endl;
    f_out << endl;
  }
  f_out << endl << "Calls tree:" << endl;

  if( functions.size() > 0)
    tree_call_hierarchy((*functions.begin()).first, 0, 1);
  f_out << endl;


  f_out << setw(9) << "address" << setw(9) << "opcode" << setw(60) << "assembler" << setw(10) << "repeats"<< setw(10) << "cycles"  << setw(20) << "delay reason" << endl;

  DwarfFilesOk = true;
  for (map<uint32_t, instr_stat>::iterator iter = InstrLock.begin(); iter != InstrLock.end(); iter++ )
  {
    PrintInstruction(iter,f_out);
  }
  
  f_out.close();

}


Profiler::~Profiler(){
  free(Events);
}

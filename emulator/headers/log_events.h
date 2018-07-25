// logger event
typedef enum
{
  // {LOG_INSTRUCTION inst_addr,inst_start_time}
  LOG_INSTRUCTION_BEGIN ,
  // {LOG_INSTRUCTION inst_addr,inst_end_time}
  LOG_INSTRUCTION_END ,
  // {LOG_MEM_BLOCK_ACCESS, BUS_PTR, addr, cur_cycle, lock_cycle}
  LOG_MEM_BUS_ACCESS,
  // {LOG_PAGE_SELECT, BLOCK_PTR, cur_cycle, lock_cycle}
  LOG_MEM_BLOCK_ACCESS,
  // {LOG_PAGE_SELECT, BLOCK_PTR, cur_cycle, lock_cycle}
  LOG_PAGE_SELECT,
  // {LOG_REGEN_SDRAM, BLOCK_PTR, cur_cycle, shift_delay}
  LOG_REGEN_SDRAM,
  // {LOG_REG_LOCK, BLOCK_PTR, cur_cycle, regen_delay}
  LOG_REG_LOCK,
  // {LOG_REG_CHECK_FALSE,REG_PTR,cur_cycle}
  LOG_REG_CHECK_FALSE,
  // just a wait for one cycle
  // {LOG_WAIT,0,cur_cycle}
  LOG_WAIT
}eLogType;
	
#define NumberOfEventsTypes LOG_WAIT + 1

 
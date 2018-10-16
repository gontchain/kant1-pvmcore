#ifndef PPDL_CPU_H
#define PPDL_CPU_H

/* cpu_ppdl_map_address_* in CPUPPDLTLBContext need this decl.  */
struct PPDLCPU;

typedef struct PPDLTLBEntry {
	uint32_t mr;
	uint32_t tr;
} PPDLTLBEntry;

typedef struct CPUPPDLTLBContext {
	#ifndef CONFIG_USER_ONLY
	PPDLTLBEntry itlb[ITLB_WAYS][ITLB_SIZE];
	PPDLTLBEntry dtlb[DTLB_WAYS][DTLB_SIZE];
	int (*cpu_ppdl_map_address_code)(struct PPDLCPU *cpu, hwaddr *physical, int *prot, target_ulong address, int rw);
	int (*cpu_ppdl_map_address_data)(struct PPDLCPU *cpu, hwaddr *physical, int *prot, target_ulong address, int rw);
	#endif
} CPUPPDLTLBContext;

typedef struct CPUPPDLState {
	#ifndef CONFIG_USER_ONLY
	CPUPPDLTLBContext * tlb;
	#endif
	uint32_t 	pc;
	uint64_t 	stack_arr[2048];
	uint64_t 	gas_price;
	uint64_t 	log_ptr;
	uint64_t 	cur_addr;
	uint64_t 	origin_addr;
	uint64_t 	input_data[1024];
	uint64_t 	caller_addr;
	uint64_t 	inp_data_size;
	uint64_t 	log_bus[1024];
	uint64_t 	ext_code_size;
	/*--------------------- VARS ---------------------*/
	uint64_t 	Difficulty;
	uint64_t 	gas_available;
	uint64_t 	data_bus[1024];
	uint64_t 	is_pc_within_inst;
	uint64_t 	mem_size;
	uint64_t 	CoinBase;
	uint64_t 	TimeStamp;
	uint64_t 	sp;
	uint64_t 	GasLimit;
	uint64_t 	Number;
	uint32_t sr;
	target_ulong eear;
	#ifndef CONFIG_USER_ONLY
	struct QEMUTimer *timer;
	uint32_t ttmr;          /* Timer tick mode register */
	uint32_t ttcr;          /* Timer tick count register */
	uint32_t picmr;         /* Interrupt mask register */
	uint32_t picsr;         /* Interrupt contrl register*/
	#endif
	void *irq[32];          /* Interrupt irq input */
	uint32_t fpcsr;         /* Float register */
	uint64_t cpu_id;        /* CPU rank in SystemC simulator */
	float_status fp_status; /* Floating point ops status */
	CPU_COMMON;
} CPUPPDLState;

extern CPUPPDLState envSaved;


#endif
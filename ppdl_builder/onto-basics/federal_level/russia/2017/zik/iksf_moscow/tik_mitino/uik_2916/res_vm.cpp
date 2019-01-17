#include "res_vm.h"

const char *reg_0 = "pc";

const tDRegister nnn_regs[1] = {
  {reg_0,4,0,0},
};


const tDMemBus nnn_membus[] = {
  {"prog_bus",4,4},
};


const tDProcCfg nnn_ProcCfg = {
  1,nnn_regs,
  1,nnn_membus,
  0,NULL,
  0,NULL,
};

#define SARG(aidx) aidx
#define SARG(aidx) aidx
#undef SARG
int nnn::SetReg(int rnum,int anum,char* val){
  switch(rnum){
  case 0: pc = *((uint32*)val); UpdateRegs(); break;
    default: return 0;
    }
  return 1;
}
int nnn::GetReg(int rnum,int anum,char* val){
  switch(rnum){

    case 0:
     *((uint32*)val) = pc;
    break;
    default: return 0;
    }
  return 1;
}

int nnn::SetFifo(int fifo_num,char* data,int size){
  switch(fifo_num){
    default: return 0;
    }
  return 0;
}
int nnn::GetFifo(int fifo_num,char* data,int& size){
  switch(fifo_num){
    default: return 0;
    }
  return 0;
}
int nnn::SetMem(void *mem,int busnum,int addr,int size){
  switch(busnum){
    case 0: return prog_bus->setmem(mem,addr,size);
    default: return 0;
    }
  return 0;
  };
int nnn::GetMem(void *mem,int busnum,int addr,int size){
  switch(busnum){
    case 0: return prog_bus->getmem(mem,addr,size);
    default: return 0;
    }
  return 0;
};
int nnn::IsMemInRange(int addr,int size,int busnum){
  switch(busnum){
    case 0: return prog_bus->IsMemInRange(addr,size);
    default: return 0;
    }
  return 0;
};
int nnn::FillMem(uint32 aVal,int busnum,int addr,int size){
  switch(busnum){
    case 0: return prog_bus->fillmem(aVal,addr,size);
    default: return 0;
    }
  return 0;
};
int nnn::GetCellSize(int busnum,int addr){
  switch(busnum){
    case 0: return prog_bus->GetCellSize(addr);
    default: return 0;
    }
  return 0;
};
inline int nnn::Main_decode(uint32 ocode){
  TMainInst* cur_inst;
  RUN_PIPE(MainPipe,0);
  switch(nnn_Main_GetInstNum(ocode)){
  case 1: // uik-2914 
  {
      cur_inst->inum = 1;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 2: // uik-2915 
  {
      cur_inst->inum = 2;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 3: // uik-2916 
  {
      cur_inst->inum = 3;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 4: // uik-2917 
  {
      cur_inst->inum = 4;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 5: // uik-2918 
  {
      cur_inst->inum = 5;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 6: // tik-mitino 
  {
      cur_inst->inum = 6;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 7: // iksf-moscow 
  {
      cur_inst->inum = 7;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 8: // zik 
  {
      cur_inst->inum = 8;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 9: // 2017 
  {
      cur_inst->inum = 9;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 10: // russia 
  {
      cur_inst->inum = 10;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 11: // federal-level 
  {
      cur_inst->inum = 11;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  case 12: // private-level 
  {
      cur_inst->inum = 12;
  SEND_PIPE(MainPipe,0)
  return 64;
  } break;
  default:
  cur_inst->inum = 0;
  SEND_PIPE(MainPipe,0)
  return 0;
  break;  } // end of iset Main decode
  return 1;
  }
inline int nnn::nnn_Main_GetInstNum(uint32 ocode){
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x02090a5)  ){ return 1;}//uik-2914
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x04090a5)  ){ return 2;}//uik-2915
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x06090a5)  ){ return 3;}//uik-2916
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x08090a5)  ){ return 4;}//uik-2917
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x0a090a5)  ){ return 5;}//uik-2918
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x090a5)  ){ return 6;}//tik-mitino
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x010a5)  ){ return 7;}//iksf-moscow
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x0a5)  ){ return 8;}//zik
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x025)  ){ return 9;}//2017
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x025)  ){ return 10;}//russia
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x01)  ){ return 11;}//federal-level
    if (  ((OPCODE(uint64)&0xffffffffffffffff) == 0x02)  ){ return 12;}//private-level
    else{ return 0; }
  }
  void nnn::update(){
  this->UpdateRegs();
  MainPipe.Update();
}
void nnn::Operate(){

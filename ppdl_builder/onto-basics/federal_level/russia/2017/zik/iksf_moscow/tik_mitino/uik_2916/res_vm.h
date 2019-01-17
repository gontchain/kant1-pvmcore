#ifndef DECLARE_nnn_H
#define DECLARE_nnn_H

#include <device.h>

// class nnn
class nnn: public TDevice
{
  struct Main_tinst1{
    }/*Main_inst1*/;
  struct Main_tinst2{
    }/*Main_inst2*/;
  struct Main_tinst3{
    }/*Main_inst3*/;
  struct Main_tinst4{
    }/*Main_inst4*/;
  struct Main_tinst5{
    }/*Main_inst5*/;
  struct Main_tinst6{
    }/*Main_inst6*/;
  struct Main_tinst7{
    }/*Main_inst7*/;
  struct Main_tinst8{
    }/*Main_inst8*/;
  struct Main_tinst9{
    }/*Main_inst9*/;
  struct Main_tinst10{
    }/*Main_inst10*/;
  struct Main_tinst11{
    }/*Main_inst11*/;
  struct Main_tinst12{
    }/*Main_inst12*/;
  struct TMainInst: public TInst{
    union{
      struct Main_tinst1 inst1;
      struct Main_tinst2 inst2;
      struct Main_tinst3 inst3;
      struct Main_tinst4 inst4;
      struct Main_tinst5 inst5;
      struct Main_tinst6 inst6;
      struct Main_tinst7 inst7;
      struct Main_tinst8 inst8;
      struct Main_tinst9 inst9;
      struct Main_tinst10 inst10;
      struct Main_tinst11 inst11;
      struct Main_tinst12 inst12;
    };
  };
public:
  PD_REG< uint32 >  pc;
  iMemInterface<uint32,uint32>* prog_bus;
  TPipeLine<TMainInst,0> MainPipe;
  virtual int SetReg(int rnum,int anum,char* val);
  virtual int GetReg(int rnum,int anum,char* val);
  virtual int SetFifo(int fifo_num,char* data,int size);
  virtual int GetFifo(int fifo_num,char* data,int& size);
  virtual int SetMem(void *mem,int busnum,int addr,int size);
  virtual int GetMem(void *mem,int busnum,int addr,int size);
  int IsMemInRange(int addr,int size,int busnum);
  int FillMem(uint32 aVal,int busnum,int addr,int size);
  int GetCellSize(int busnum,int addr);
  inline int Main_decode(uint32 ocode);
  inline int nnn_Main_GetInstNum(uint32 ocode);
  void update();
  void Operate();

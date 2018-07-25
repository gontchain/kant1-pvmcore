#ifndef DEBUGGER_INTERFACE_H
#define DEBUGGER_INTERFACE_H
#include <datatypes.h>
#include <debug_structs.h>
#include <string.h>


#define PERIPHERAL_OFFSET  25

// breakpoint
enum ePointType
{
  BP_STANDARD,
  BP_SINGLE_EXEC,
  BP_ON_NEXT,
  BP_WATCHPOINT,
};

typedef struct
{
  uint32 mStartAddr; // start disassembly addr
  uint32 mSize;
}tDisAsmArea;


struct tDisAsmDbgArea :public tDisAsmArea
{
  uint32 mEndPoint;
};

// абстрактный класс для управления симулятором.
class TDbgInterface
{
public:
  // загрузить elf файл в память процессора
  // Аргументы:
  //
  virtual tDisAsmArea* LoadElf(char* aElfFile) = 0;

  // Возвращает размер минимально адресуемой ячейки памяти в байтах
  // Аргументы:
  //    busnum - индекс шины памяти
  //    addr - адрес ячейки
  virtual int GetCellSize(int busnum,int addr) = 0;

  // Возвращает указатель на структуру, описывающую конфигурацию процессора,
  // как то:
  //   список регистров, включающий название регистра, размер в битах и размер массива
  // (для массива регистров)
  //   количество и названия доступных шин памяти
  //  список флагов процессора
  virtual const tDProcCfg* GetCfg()= 0;

  // возвращает size байт памяти начиная с адреса addr в область mem.
  // аргументы:
  //   mem-  указатель на массив, в который будет считана памяти из симулятора
  //   busnum - индекс шины памяти
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, который необходимо вернуть
  virtual int GetMem(void *mem, int busnum, int addr,int size)=0;

  // возвращает size байт памяти програм начиная с адреса addr в область mem.
  // аргументы:
  //   mem-  указатель на массив, в который будет считана памяти из симулятора
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, который необходимо вернуть
  virtual int GetProgMem(void *mem, int addr, int size)=0;
  // возвращает size байт памяти данных начиная с адреса addr в область mem.
  // аргументы:
  //   mem-  указатель на массив, в который будет считана памяти из симулятора
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, который необходимо вернуть
  virtual int GetDataMem(void *mem,int addr,int size)=0;

  // записывает size байт памяти начиная с адреса addr, данные беруться из области mem.
  // аргументы:
  //   mem-  указатель на массив, в который будет считана памяти из симулятора
  //   busnum - индекс шины памяти
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, в который пишуться данные
  virtual int SetMem(void *mem,int busnum,int addr,int size)=0;

  // Проверяет, есть ли для заданного диапазона адресов физическая память.
  // аргументы:
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, в который пишуться данные
  //   busnum - индекс шины памяти
  virtual int IsMemInRange(int addr,int size,int busnum = 0) = 0;

  // записывает size байт памяти начиная с адреса addr, данные беруться из области mem.
  // аргументы:
  //   mem-  указатель на массив, в который будет считана памяти из симулятора
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, в который пишуться данные
  virtual int SetProgMem(void *mem,int addr,int size)=0;

  // записывает size байт памяти начиная с адреса addr, данные беруться из области mem.
  // аргументы:
  //   mem-  указатель на массив, в который будет считана памяти из симулятора
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, в который пишуться данные
  virtual int SetDataMem(void *mem,int addr,int size)=0;

  // заполнить область памяти значением aVal
  //   busnum - индекс шины памяти
  //   addr - стартовый адрес в памяти симулятора
  //   size - размер памяти в байтах, в который пишуться данные
  virtual int FillMem(uint32 aVal,int busnum,int addr,int size)=0;

  // дизассемблировать программу размером size, находящуюся по адресу bin
  // функция возвращает указатель на строку, содержащую набор инструкций в следующем
  // формате : "адрес     код инструкции\n дизасемблированная инструкция\n
  virtual int DisAssembly(char *str,int busnum,int addr,int size) = 0;

  // записать значение в регистр с индексом rnum, или в элемент регистрового массива rnum
  // с адресом anum.
  // Аргументы:
  // rnum - индекс регистра или массива регистров
  // anum - индекс регистра в регистровом массиве (в случае регистра игнорируется)
  // val - значение для записи
  virtual int SetReg(int rnum,int anum,char* val)=0;

  // возвращает значение регистра с индексом rnum, или элемент регистрового массива rnum
  // с адресом anum.
  // Аргументы:
  // rnum - индекс регистра или массива регистров
  // anum - индекс регистра в регистровом массиве (в случае регистра игнорируется)
  // val - указатель на область памяти для сохранения регистра
  virtual int GetReg(int rnum,int anum,char* val)=0;

  // установить значение счетчика программы
  virtual int SetPc(uint32 val)=0;


  // устанавливает значение ФИФО с индексом fifo_num
  // Аргументы:
  // fifo_num - индекс ФИФО
  // data - указатель на массив новых значений фифо
  // size - новая длинна ФИФО
  virtual int SetFifo(int fifo_num,char* data,int size)=0;

  // устанавливает значение ФИФО с индексом fifo_num
  // Аргументы:
  // fifo_num - индекс ФИФО
  // data - указатель на массив, в который будут сохранено фифо
  // size - длинна ФИФО
  virtual int GetFifo(int fifo_num,char* data,int& size)=0;

  // вернуть значение счетчика программы
  virtual uint32 GetPc(int val) = 0;

  // установить точку останова по адресу addr
  virtual int SetBreakPoint(uint32 addr,ePointType aType = BP_STANDARD) = 0; // set breakpoint

  // убрать точку останова по адресу addr
  virtual int ClearBreakPoint(uint32 addr) = 0 ; // remove breakpoint
  //
  // очистить память
  virtual void ClearMem()  = 0;

  //  сбросить процессор
  virtual void Reset() = 0;

  // начать исполнение
  virtual void Start() = 0;

  // остановить исполнение
  virtual void Stop() = 0;

  // проверить, запущен ли процесс симуляции
  virtual int IsRun()=0;

  // эмуляция исполнения одной инструкции
  virtual void StepInto() = 0;

  // функция возвращает количество тактов с момента последней перезагрузки
  virtual unsigned int GetNumCycles() = 0;

  // функция возвращает номер инструкции
  virtual int   GetInstructNum(uint64 wrd) = 0;
  virtual int   GetKindOfInstruction(uint32 aAddr) = 0;
  virtual char* GetNameFromPtr(void* ptr) = 0;

  // new service functions
  inline uint8 GetReg8(int rnum,int anum)
  {
    uint8 reg;
    this->GetReg(rnum,anum,(char*)&reg);
    return reg;
  }

  inline uint16 GetReg16(int rnum,int anum)
  {
    uint16 reg;
    this->GetReg(rnum,anum,(char*)&reg);
    return reg;
  }

  inline uint32 GetReg32(int rnum,int anum)
  {
    uint32 reg;
    this->GetReg(rnum,anum,(char*)&reg);
    return reg;
  }

  inline uint64 GetReg64(int rnum,int anum)
  {
    uint64 reg;
    this->GetReg(rnum,anum,(char*)&reg);
    return reg;
  }

  inline int SetReg8(int rnum,int anum,uint8 val)
  {
    return this->SetReg(rnum,anum,(char*)&val);
  }

  inline int SetReg16(int rnum,int anum,uint16 val)
  {
    return this->SetReg(rnum,anum,(char*)&val);
  }

  inline int SetReg32(int rnum,int anum,uint32 val)
  {
    return this->SetReg(rnum,anum,(char*)&val);
  }

  inline int SetReg64(int rnum,int anum,uint64 val)
  {
    return this->SetReg(rnum,anum,(char*)&val);
  }

  inline int GetRegIdx(char* aRegName)
  {
    const tDProcCfg* cfg = this->GetCfg();
    for(int i = 0;i < cfg->nreg;i++)
    {
      if(!strcmp(cfg->regs[i].name,aRegName))
        return i;
    }
    return -1;
  }
};


#endif

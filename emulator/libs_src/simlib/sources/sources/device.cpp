// device.cpp

#include "device.h"
#include "system.h"
#include <exception>

#ifdef SYSTEMC_USED
TDevice::TDevice():sc_module("nnn")
#else
TDevice::TDevice()
#endif
{
  isStart=0;         // processor is not starded
  fbp=lbp=NULL;      // no breakpoints
  isSingleStep=0;    // 
}

TDevice::~TDevice()
{
  // delete all break-points
  tBPoint *bp =fbp;
  while(bp!=NULL)
  {
    bp = fbp->next;
    delete fbp;
    fbp = bp;
  }
}

// break points routine
int TDevice::SetBreakPoint(uint32 addr,ePointType aType)
{
  tBPoint *bp = new tBPoint;
  bp->addr = addr;
  bp->next = NULL;
  bp->mType = aType;
  
  if(fbp==NULL)
  {
    fbp = lbp = bp;
  }
  else
  {
    lbp->next = bp;
    lbp = bp;
  }
  return 1;
}


int TDevice::CheckBreakPoints(unsigned long pc)
{
  tBPoint *bp = fbp;
  int next_bp = 1;
  while(bp!=NULL)
  {
    if((bp->addr==pc)||(bp->mType==BP_ON_NEXT))
    {
      if((bp->mType==BP_SINGLE_EXEC)||(bp->mType==BP_ON_NEXT))
      {
        tBPoint* nbp = bp;
        bp = bp->next;
        this->ClearBreakPoint(nbp->addr);
        next_bp = 0;
      }
      // stop the simulation
      IsRunned = 0;
//      return 1;
    }   
    if(next_bp)
      bp= bp->next;
    else
      next_bp = 1;
  }
  return (IsRunned==0);
}


int TDevice::ClearBreakPoint(unsigned long addr)
{
  tBPoint *bp = fbp;
  tBPoint *prev = NULL;
 
  while(bp!=NULL)
  {
    if((bp->addr==addr)||(bp->addr==-1))
    {
      if(prev==NULL) // if first break point
        fbp = bp->next;
      else
        prev->next = bp->next;

      if(bp->next==NULL) // if last break point
        lbp = prev;
      delete bp;     
      return 1;
    } // end if
    prev = bp;
    bp = bp->next; // goto next element
  }
  return 0;
}

void TDevice::Reset()
{
  this->ResetDevice();
  this->ClearMem();
#ifndef SYSTEMC_USED
  this->cycles = 0;
#endif
}

int TDevice::error(char* err_msg)
{
  return 0;
}

// arguments:
// 
int TDevice::DisAssembly(char *aStr,int aBusNum,int aAddr,int aSize)
{
  char *inbuf = new char[max(aSize,64)+4];
  char *iptr = inbuf;  // pointer into an opcode memory buffer
  char *sptr = aStr;   // pointer into an output string
  int cell_size = this->GetCellSize(0,aAddr);
  if(cell_size==0)
    return 0;
  unsigned int end_addr = aAddr + aSize/cell_size;
  if(aSize<64)
    aSize = 64;

  if(!GetMem(inbuf,aBusNum,aAddr,aSize))
  {
    delete inbuf;
    return 0;
  }
  
  do // disassembly cycle
  {
    // disassemby instruction
    try
    {
      int offs_size;   // instruction offset
      uint64 opcode;   // instruction opcode
      // disassembly an instruction, read a bytes size into a variable offset size
      char *istr = (char*)this->disasm(iptr,offs_size);
      // read opcode and increment counter
      if(offs_size==4)
      {  
        // offset instruction in bytes
        opcode = *((uint32*)iptr);
        sptr+=sprintf(sptr,"%08X         %08X\n%s\n",aAddr,LO_WRD(opcode),istr);
      }
      else
      {
        opcode = *((uint64*)iptr);
        sptr+=sprintf(sptr,"%08X %08X %08X\n%s\n",aAddr,HI_WRD(opcode),LO_WRD(opcode),istr);
      }
      // output disassembly string
      // increment address of the variable
      aAddr+= offs_size / cell_size;
      // shift input stream pointer
      iptr+=offs_size;
    }
    catch(...) //exception &exc) // output exception
    {
      printf("disassembly exception") ;// exc.what());
      return 0;
    }
  }while(aAddr < end_addr);

  delete inbuf;
  return (uint32)sptr - (uint32)aStr;
}

int TDevice::LoadSection(ELF_SCN* aSection,uint32& aAddr)
{
  // section's header
  Elf32_Shdr *shdr = aSection->GetShdr();
  // section's data
  ELF_DATA   *sh_data = aSection->GetData(0);
  int        size = shdr->sh_size; // size in bytes
  // load 
  if(!this->SetMem(sh_data->d_buf,0,aAddr,size))
    return 0;
  // align address
  // aAddr += size/this->GetCellSize(0,aAddr);
  return size;
}


// load ELF file
tDisAsmArea* TDevice::LoadElf(char* aElfFileName)
{
//  ELF_FILE *elf_file;
  try
  {
    ELF* aElfFile = new ELF(aElfFileName,ELF_C_READ);
    if(aElfFile==NULL)
      return NULL;

    uint32 start_addr = 0;                 // start from the address   
    uint32 init_pos = 0;
    uint32 cell_size = 1;
    ELF_SCN  *csect = aElfFile->GetScn(0); // get first section
    // symbol table  
    Elf32_Sym *symb_table = NULL;               
    uint32  symb_table_size = 0;
    uint32  named_symbols = 0;
    // reset processor
    this->Reset();
    // clear memory before the start
    
    // clear all previouse breakpoints
    while(this->fbp!=NULL)
    {
      tBPoint* bp = this->fbp;
      this->fbp = bp->next;
      delete bp;
    }

    this->mArea.mStartAddr = (uint32)(-1);
    this->mArea.mSize      = 0;

    while(csect!=NULL)// walt throw the sections and load data if need
    { 
      // process current section
      Elf32_Shdr *shdr = csect->GetShdr();
      char* sect_name  = csect->GetName(); 
      ELF_DATA   *data;
      int         size;
      // 
      if((shdr->sh_flags&(SHF_WRITE|SHF_ALLOC|SHF_EXECINSTR))&&(shdr->sh_type!=SHT_NOBITS))
      {
        if(!this->LoadSection(csect,shdr->sh_addr))
          return 0;

        if(this->mArea.mStartAddr > shdr->sh_addr)
          this->mArea.mStartAddr = shdr->sh_addr; 
        this->mArea.mSize += shdr->sh_size / this->GetCellSize(0,shdr->sh_addr);
      }
      csect = aElfFile->NextScn(csect);
    }// end while
    
    // set start program counter
    Elf32_Ehdr*  ehdr = aElfFile->GetEhdr();
    this->SetPc(ehdr->e_entry);
    this->SetBreakPoint(ehdr->e_entry + PC_START_OFFSET);
    
    cell_size = this->GetCellSize(0,this->mArea.mStartAddr);
    init_pos = ehdr->e_entry * cell_size;

    if((signed)init_pos - (signed)(DECODE_DELTA*cell_size) >=0)
    {
      this->mArea.mStartAddr = init_pos - DECODE_DELTA*cell_size;
      this->mArea.mSize = init_pos + DECODE_DELTA*cell_size;
    }
    else
    {
      this->mArea.mStartAddr = 0;
      this->mArea.mSize = init_pos + DECODE_DELTA*cell_size*2;
    }
    // correct size
    // this->mArea.mSize = this->mArea.mSize * this->GetCellSize(0,this->mArea.mStartAddr);
    delete aElfFile; 
    return (&this->mArea);
  }
  catch(...)//exception &exc) 
  {
    return 0;
  } 
  return (&this->mArea); 
}

void TDevice::StepInto()
{
  if(IsRunned==1)
    return; // must be an exeption

  this->SetBreakPoint(-1,BP_ON_NEXT);
  IsRunned = 1;

  SEND_START_MSG();
  while(IsRunned) ;
//    SingleClock();
//  OwnerId = GetCurrentThreadId();
//  WAIT_STOP_MESSAGE();
}

int TDevice::IsRun()
{
  return IsRunned;
}

void TDevice::Start()
{
  IsRunned = 1;
  SEND_START_MSG();
}
void TDevice::Stop()
{
  IsRunned = 0;
  WAIT_STOP_MESSAGE(); 
}

#ifdef SYSTEMC_USED
void TDevice::UpdateCycle()
{
  do{
    wait();
    this->update();
  }while(true);
}
#endif

char* TDevice::Test()
{
     void *p_vptr=NULL;
     int  size=1024;
     p_vptr = (void*) new char [size];
     strncpy((char*)p_vptr, "device::Test(): get string: Hello wold!",size);
     printf("device::Test(): size=%d  p_vptr='%s'\n", size, (char*)p_vptr);
     return  (char*)p_vptr;
}
void TDevice::Test1(void)
{ 
  printf("device::Test1(): ... \n"); 
}

unsigned int TDevice::GetNumCycles()
{
  return this->cycles;
}
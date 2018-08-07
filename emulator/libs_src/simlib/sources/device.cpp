#include "device.h"
#include "system.h"
#include <stdarg.h>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stream_txt_funcs.h>

TCyclic* CurDevice;

extern uint32 StackStartArea;
extern uint32 StackEndArea;
extern uint32 GlobalCycleCounter;


TPPDLLogger    Logger;

#define ELFLOG 0

TDevice::TDevice(char* aDevName)
{
  isStart=0;         // processor is not starded
  fbp=lbp=NULL;      // no breakpoints
  isSingleStep=0;    //
  CurDevice = this;  // set this processor as current
  mUpdateCount = 0;
  DeviceList.Add(this);
  // add device name
  IsLocked = 1;
  strcpy(mDevName,aDevName);
  mSyncWaitCounter = 0;
  // create wrapper 
#ifdef SYSTEMC_MODELING
  {
    TScWrapper * wrap = new TScWrapper(sc_module_name(aDevName));
    wrap->mDev = this;
    wrap->clk(clk_signal);
  }
#endif
}

void TDevice::UpdateDevice(void)
{
   this->update();
   this->mCycles++;
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


int TDevice::GetClassDevice()
{
  return DEV_CLASS_PROCESSOR;
}
// break points routine
int TDevice::SetBreakPoint(uint32 addr,ePointType aType)
{
  tBPoint *bp = new tBPoint;
  bp->addr = addr;
  bp->next = NULL;
  bp->mType = aType;

#ifdef MY_LOG
  fprintf(LogFile,"breakpoint at %X, type %d\n",addr,aType);fflush(LogFile);
#endif 
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


int TDevice::CheckBreakPoints(uint32 pc)
{
  tBPoint *bp = fbp;
  int next_bp = 1;
#ifdef MY_LOG
  fprintf(LogFile,"check BPs at pc =%X\n",pc);fflush(LogFile);
#endif 

  while(bp!=NULL)
  {
#ifdef MY_LOG
    fprintf(LogFile,"validate BP at %X\n",bp->addr);fflush(LogFile);
#endif
    if(((bp->addr==pc)&&(bp->mType!=BP_WATCHPOINT))||(bp->mType==BP_ON_NEXT))
    {
#ifdef MY_LOG
      fprintf(LogFile,"success\n");fflush(LogFile);
#endif
      if((bp->mType==BP_SINGLE_EXEC)||(bp->mType==BP_ON_NEXT))
      {
        tBPoint* nbp = bp;
        bp = bp->next;
        this->ClearBreakPoint(nbp->addr);
        next_bp = 0;
      }
      // stop the simulation
      IsNoBreakPoints = 0;
      return 1;
    }
    if(next_bp)
      bp= bp->next;
    else
      next_bp = 1;
  }
  return (IsNoBreakPoints==0);
}

int TDevice::CheckWatchPoints(uint32 aAddr)
{
  tBPoint *bp = fbp;
  int next_bp = 1;
  if(IsRunned==0)
    return 1;
  while(bp!=NULL)
  {
    if((bp->addr==aAddr)&&(bp->mType==BP_WATCHPOINT))
    {
      // stop the simulation
      IsNoBreakPoints = 0;
      return (IsNoBreakPoints==0);
    }
    bp= bp->next;
  }
  return (IsNoBreakPoints==0);
}



int TDevice::ClearBreakPoint(uint32 addr)
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
 // this->ClearMem();
  this->mCycles = 0;
}

int TDevice::error(char* err_msg)
{
  return 0;
}

// arguments:
//
//#ifndef WIN32

int max_v(int x1,int x2)
{
  if(x1>x2) return x1; else return x2;
}
#define max(a,b) max_v(a,b)


int TDevice::GetKindOfInstruction(uint32 aAddr)
{
  char inbuf[sizeof(uint64)*2];
  if(!GetMem(inbuf,0,aAddr,sizeof(uint64)*2))
  {
    return -1;
  }
  else
  {
    uint64 code = *((uint64*)inbuf);
    return GetInstructNum(code);
  }
}
  

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
        sptr+=sprintf(sptr,"%08X",aAddr);
        for(int ii=0;ii<10;ii++) *sptr++ = ' ';
        sptr+=sprintf(sptr,"%08X\n%s\n",LO_WRD(opcode),istr);
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
    catch(.../*exception &exc*/) // output exception
    {
     // printf(exc.what());
      return 0;
    }
  }while(aAddr < end_addr);

  delete inbuf;
  return (uint32)sptr - (uint32)aStr;
}

int TDevice::LoadSection(ELF_SCN* aSection, uint32_t& aAddr)
{
  // section's header
  Elf32_Shdr *shdr = aSection->GetShdr();
  // section's data
  ELF_DATA   *sh_data = aSection->GetData(0);
  int        size = shdr->sh_size; // size in bytes
  if(size <= 0){
#ifdef ELF_LOAD_LOG
  printf(" section %s size error\n",aSection->GetName());
#endif
    return 1;
  }
  // load
  if(!this->SetMem(sh_data->d_buf,0,aAddr,size))
  {
    printf(" error loading section %s into the memory, can't load data at address 0x%X size %d bytes\n",aSection->GetName(),aAddr,size); 
    return 0;
  }
#ifdef ELF_LOAD_LOG
  printf("load section %s from %X to %X\n",aSection->GetName(),aAddr,aAddr + size/4);
#endif
  // align address
  // aAddr += size/this->GetCellSize(0,aAddr);
  return size;
}


#define PRINT_ERROR(ptr) {printf("wrong DIB string %s\n",ptr); return -1;}

int TDevice::DecodePair(char* f_ptr,uint32& aAddr,uint32 &aData)
{
        char* f_start = f_ptr;
        int offset; 
        // decode address and data
        if(!IsHexPrefix(f_ptr))
          PRINT_ERROR(f_ptr);
        
        f_ptr+=2;
        aAddr = GetHex<uint32>(f_ptr,offset);
        
        //
        if(offset==0)
          PRINT_ERROR(f_ptr);
        // 
        f_ptr += offset;
        f_ptr += MissText(f_ptr," ");
        
        if(!IsHexPrefix(f_ptr))
          PRINT_ERROR(f_ptr);
        
        f_ptr+=2;
        aData = GetHex<uint32>(f_ptr,offset);
        
        //
        if(offset==0)
          PRINT_ERROR(f_ptr);
        return (int)f_ptr - (int)f_ptr;
}


tDisAsmArea* TDevice::LoadDibFile(const char* aDibFileName)
{
  uint32 addr;
  uint32 data;
  int size = 0;

  uint32 start_addr;
  uint32 end_addr;


  std::string line;
  std::ifstream myfile (aDibFileName);

  if (myfile.is_open())
  {
    char* f_ptr;
    while( myfile.good())
    {
      getline (myfile,line);

      f_ptr = (char*)line.c_str();
      if(*f_ptr==0) continue;

      if( !((f_ptr[0]==47) && (f_ptr[1]==47)) )
      {
        int offset = DecodePair((char*)line.c_str(),start_addr,end_addr);
        if(offset==-1)
        {
          myfile.close();
          return NULL;
        }
        break;
      }// if( !((f_ptr[0]==47) && (f_ptr[1]==47)) )
    }// if( myfile.good())

    while ( myfile.good() )
    {
      getline (myfile,line);
//      std::cout << line << std::endl;
      
      f_ptr = (char*)line.c_str();
      if(*f_ptr==0) continue;

      if( !( (f_ptr[0]==47) && (f_ptr[1]==47)) )
      {
        int offset = DecodePair(f_ptr,addr,data);
        if(offset==-1)
        {
          myfile.close();
          return NULL;
        }
        SetMem((void*)&data,0,addr,4);
        size++;
      }
    }
    // decode 
    myfile.close();
    SetPc(start_addr);
    mArea.mStartAddr = start_addr;
    mArea.mSize = size;
    mArea.mEndPoint = end_addr;
    return &mArea;
  }
  else
  {
    printf("error: can't open file %s\n",aDibFileName);
  }

  return NULL;
}


// load ELF file
tDisAsmArea* TDevice::LoadElf(char* aElfFileName)
{
  FILE *fin;
  try
  {
	  // reset 
	  this->Reset();
	  int size = 0;
	  char ibuf[3]; ibuf[2] = 0;
	  // try to open
	  fin = fopen(aElfFileName, "rt");
	  if (fin == NULL)
	  {
		  printf("error: can't open contract %S\n", aElfFileName);
		  this->mArea.mSize = 0;
		  return &(this->mArea);
	  }
	  // read file
	  while (!feof(fin)) // file read loop
	  { 
		  char value;
		  fread(ibuf, 1, 2, fin);
		  value = GetHex<char>(ibuf);
		  this->SetMem(&value,0, size, 1);
		  size++;
	  }
	  this->mArea.mStartAddr = 0;
	  this->mArea.mEndPoint = size;
	  this->mArea.mSize = size;
    this->IsLocked = 0;
  }
  catch(...)
  {
    printf("error while reading file %s,wrong executable\n",aElfFileName);
    this->mCycles = 0;
    this->IsLocked = 0;
    return (&this->mArea);
  }
  return (&this->mArea);
}


// load ELF file
int TDevice::GetSectAddr(char* aElfFileName,uint32& aStart,uint32& aEnd,char* aSectName)
{
//  ELF_FILE *elf_file;
  ELF* aElfFile;
  char err_buf[1024];
  aStart = 0;
  aEnd = 0xFFFFFFFF;
  
  try
  {
    try
    {
      aElfFile = new ELF(aElfFileName,ELF_C_READ);
      if(aElfFile==NULL)
        return NULL;
    }
    catch(...)
    {      
      sprintf(err_buf,"error while opening file %s,wrong abs file\n",aElfFileName);
      throw std::runtime_error(err_buf);
    }

    ELF_SCN  *csect = aElfFile->GetScn((Elf32_Word)0); // get first section
   
    // symbol table
    Elf32_Sym *symb_table = NULL;
   
    while(csect!=NULL)// walt throw the sections and load data if need
    {
      // process current section
        Elf32_Shdr *shdr = csect->GetShdr();
        char* sect_name  = csect->GetName();
        try
        {
          // load section into the memory (if need
          ELF_DATA   *data;
          int         size;
          //
          char *name = csect->GetName();
          if((name!=NULL)&&(!strcmp(csect->GetName(),aSectName)))
          {
            aStart =  shdr->sh_addr;
            aEnd = shdr->sh_addr + (shdr->sh_size/ 1);           
            delete aElfFile;
            return 1;
          }
          csect = aElfFile->NextScn(csect);
        }
        catch(...)
        {
          sprintf(err_buf,"error section %s,can't load section\n",sect_name);         
          throw std::runtime_error(err_buf);
        }
    }// end while

    delete aElfFile;
    return 0; // no section found
  }
  catch(std::runtime_error& err)
  {
    throw err;// 
  }
  catch(...)
  {
    throw std::runtime_error("unknown error during the file parsing");
  }
  return 0;
}


void TDevice::StepInto()
{
  IsRunned = 1;
  SingleClock();
  if(CheckBreakPoints(GetPc(0)))
    IsRunned = 0;
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

unsigned int TDevice::GetNumCycles()
{
#ifdef SYSTEMC_MODELING
   return GlobalCycleCounter;
#else
  return this->mCycles;
#endif
}

int TDevice::GetProgMem(void *mem,int addr,int size)
{
  if(this->GetCfg()->nbuses == 0)
    return 0;
  return this->GetMem(mem,0,addr,size);
}

int TDevice::GetDataMem(void *mem,int addr,int size)
{
  if(this->GetCfg()->nbuses > 1)
    return this->GetMem(mem,1,addr,size);
  else if(this->GetCfg()->nbuses == 0)
    return 0;
  else
    return this->GetMem(mem,0,addr,size);
}

int TDevice::SetProgMem(void *mem,int addr,int size)
{
  if(this->GetCfg()->nbuses == 0)
    return 0;
  return this->SetMem(mem,0,addr,size);
}

int TDevice::SetDataMem(void *mem,int addr,int size)
{
  if(this->GetCfg()->nbuses > 1)
    return this->SetMem(mem,1,addr,size);
  else if(this->GetCfg()->nbuses == 0)
    return 0;
  else
    return this->SetMem(mem,0,addr,size);
}

char* TDevice::GetDeviceName()
{
  return this->mDevName;
}


#ifdef SYSTEMC_MODELING
void TScWrapper::Operate()
{
  for (;;)
  {
    if (!mDev->IsLocked)
    {
       CurDevice = mDev;
       mDev->Operate();
       mDev->UpdateDevice();
    } // end if
    wait();
  } // end for
}

void TScWrapper::Update()
{
}
#endif
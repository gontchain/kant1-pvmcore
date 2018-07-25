#include "istream.h"
#include "tBaseAsm.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef ASM_BINARY
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/spirit.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include "tStripCommentsParser.h"
#include "tExpandMacrosParser.h"
#include "TestParser.h"
#endif

extern tBaseAsm* CreateAsmObject(char* aName);

#include "tBaseAsm.h"

const char help_msg[] = " Syntax: asm.exe [-?] assembly_file1 [assembly_file2] ..[assembly_fileN] -o output_bin\n\
                        Options:\n\
                        assembly_fileN     \tinput assembly file\n\
                        -o [output_bin]    \toutput binary file\n\
                        -?                 \toutputs this help message\n\
                        -b                 \toutput format is text (like a '010001001')\n";

                        void OutHelpString()
{
  printf(help_msg);
}

int AssemblyFile(uint32* aOutStream, char* aInpFile,tBaseAsm* aAsm)
{
  try
  {
    // number of bytes read
    int out_bytes;
    // open bitstream 
    TFileIStream*  inp_stream = new TFileIStream(aInpFile);
    //start assembly message
    printf("start assembly file %s\n",aInpFile);
    // check if the bitstream is valid
    if(inp_stream->size == -1)
    {
      printf("error: can't open input file %",aInpFile);
      return 0;
    }
    // assembly file
    out_bytes = aAsm->Assembly((char*)inp_stream->getstr(),aOutStream);
    // delete input stream stream
    delete inp_stream;
    // return number of bytes read
    return out_bytes;
  }
  catch(...) // output exception
  {
    return 0;
  }
}


void main(int argc, char *argv[])
{
  int i;
  TFileOStream  *bin;     // output file stream;0,4096
  // processor assembly
  //PROC_ASSEMBLY* proc_asm = new PROC_ASSEMBLY(0,4096);// 
  tBaseAsm* proc_asm = (tBaseAsm*)CreateAsmObject("asm");
  g_echo = false;

  char  *outbuf = NULL;   // pointer into an output buffer
  int fnames[32];         // maximum 32 files can be processed at once 
  int fnp = 0;            // number of files are recognized as an output
  int bytewr = 8;         // number of bytes are written 


  if(argc<=1)
  {
    OutHelpString();
    exit(-1);
  }

  for(i=1;i<argc;i++)
  {
    if(!strcmp(argv[i],"-o"))
    {
      if(argv[i+1]==NULL)
      {
        printf("error: no output file name\n");
        OutHelpString();
        exit(-1);
      }
      bin = new TFileOStream(argv[i+1],0,65536*16); // max size of the output file is 64k
      outbuf = (char*)bin->getstr();
      i++;
    }
    else if(!strcmp(argv[i],"-b"))
    {
      if(argv[i+1]==NULL)
      {
        printf("error: no output file name\n");
        OutHelpString();
        exit(-1);
      }
      bin = new TFileOStream(argv[i+1],1,65536*16); // max size of the output file is 64k
      outbuf = (char*)bin->getstr();
      i++;
    } 
    else // it is an input file name
    {
      // put file name into the list of input files  
      if(fnp < 32) fnames[fnp++] = i;
    } 
  }

  if(outbuf==NULL)
  {
    printf("no output file\n");
    OutHelpString();
    exit(-1);
  }

  if(fnp==0)
  {
    printf("no input files to assembly\n");
    OutHelpString();
    exit(-1);
  }
    
  int is_success = 1;
  // assembly routine
  for(i=0;i<fnp;i++)
  {
    int bytes_written = AssemblyFile((uint32*)&outbuf[bytewr],argv[fnames[i]],proc_asm);
    // check if the assembly was succsessful
    is_success = (bytes_written >0)&is_success;
    // offset output stream count
    bytewr+=bytes_written;
  }

  // save output into a stream  
  if(is_success)
  {
    if(proc_asm->mIsProgAddrSet == false)
    {
#ifndef ASM_BINARY
      printf("start address of the program (label <start>) is undefined\n");
      exit(-1);
#else 
      proc_asm->mProgramStartAddr = 0;
      proc_asm->mProgStartAddr = bytewr / proc_asm->mCellSize;
#endif
    }

    *((uint32*)outbuf)    = proc_asm->mProgramStartAddr;
    ((uint32*)outbuf)[1]  = proc_asm->mProgStartAddr;

    bin->addsize((int)bytewr);
    printf("assembler file has been successfully finished\n");
  }
  else
  {
    printf("assembly errors has occuired\n");
  }
  delete bin;
}
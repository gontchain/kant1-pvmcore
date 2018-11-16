#ifndef  EVM_CLIEN_H
#define  EVM_CLIENT_H

#include "datatypes.h"
#include <string>

// this class will came from cpp-ethereum client
class TEvmClient
{
protected:
  TTId curTTid;
  // storage
  uint256* Storage;
  TTId*    History;
  uint32   HistoryBufSize;
  uint32   HistoryCounter;
  // contract params
  uint160  cur_addr;
  uint160  caller_addr;
  uint160  origin_addr;
  uint256  gas_price;
  uint256  gas_available;
  // history file name
  std::string hist_file_name;


public:
  // write to storage
  inline void sstore(uint256 key, uint256 val) { Storage[key] = val; }
  // read from storage
  inline uint256 sload(uint256 key) { return Storage[key]; }
  inline uint256* GetStoragePtr() { return Storage ; }
  TTId GetCurState() { return  (HistoryCounter > 0)  ?  History[HistoryCounter-1] : HistoryCounter; }

  void AddNextTransaction(TTId aTid)
  {
    FILE* hist_file =fopen(hist_file_name.c_str(),"ab");
    if(hist_file !=NULL)
    {
      fwrite(&aTid,sizeof(TTId),1,hist_file);
      fclose(hist_file);
    }
    else
    {
      printf("can't save transaction\n");
    }
    // 
    History[HistoryCounter++] = aTid;
  }

  TEvmClient(std::string aEvmName,uint256* aStorage, uint32 aInitBufSize = 256)
  {
    // load history from file    
    History = new TTId[aInitBufSize];
    HistoryBufSize = aInitBufSize;
    HistoryCounter = 0;
    hist_file_name  = aEvmName;    

    FILE* hist_file = fopen(hist_file_name.c_str(), "rb");

    if(hist_file!=NULL) // if the file is exist
    {
      while (fread(&History[HistoryCounter], sizeof(TTId), 1, hist_file)!=0 )
      {
        HistoryCounter++;
      } 
      fclose(hist_file);
    }
    else

    {
      // by default we have set a nul state
      History[0] = 0;
      HistoryCounter = 1;
    }
    // set storage size
    Storage = aStorage;
  }// end of constructore

};

#endif
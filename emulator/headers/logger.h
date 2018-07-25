#ifndef PPDL_LOGGER_H
#define PPDL_LOGGER_H

#include "datatypes.h"
#include "log_events.h"

#include <stdio.h>

#define MAX_NUM_LOG_EVENTS 1000

// define который включает/выключает логгер
#define USE_LOGGER
#define LOG_FILE_NAME "log_arch.bin"

// структура сообщения логгера
struct TLogEvent
{
  eLogType Event;
  uint32   Data[4]; // max 4 arguments. 
};


class TPPDLLogger
{
protected:
  TLogEvent  mEvents[MAX_NUM_LOG_EVENTS];
  TLogEvent  *mEPtr;
  TLogEvent  *mEEnd;
  FILE       *mOutLog;

  inline void InitPointers()
  {
    mEPtr = mEvents;
    mEEnd = mEvents + MAX_NUM_LOG_EVENTS;
  }
  
public:
  TPPDLLogger()
  {
    InitPointers();
    mOutLog = NULL;
  }

  inline void InitLog(char* aFileName)
  {
    mOutLog = fopen(aFileName,"wb");
    if(!mOutLog)
      printf("error while opening log file %s\n",aFileName);
  }
  
  inline void CloseLog()
  {
    if(mOutLog==NULL)
      return;    
    int byte_len = (uint32)mEPtr - (uint32)mEvents;
    fwrite(mEvents,byte_len,1,mOutLog);
    fclose(mOutLog);
  }
  
  ~TPPDLLogger()
  {
//    CloseLog();
  }


  inline void IncLog()
  {
    // next log container
    if((++mEPtr) == mEEnd )
    {
      // if the log container is full, save it into file
      fwrite(mEvents,sizeof(TLogEvent)*MAX_NUM_LOG_EVENTS,1,mOutLog);
      InitPointers();
    }
  }

  // write log message
  inline void Log(eLogType aEv)
  {
    if(mOutLog==NULL)
      return;
    mEPtr->Event = aEv;
    IncLog();
  }

  // write log message
  inline void Log(eLogType aEv,uint32 a0)
  {
    if(mOutLog==NULL)
      return;

    mEPtr->Event = aEv;
    mEPtr->Data[0] = a0;
    IncLog();
  }
  // write log message
  inline void Log(eLogType aEv,uint32 a0,uint32 a1)
  {
    if(mOutLog==NULL)
      return;
    mEPtr->Event = aEv;
    mEPtr->Data[0] = a0;
    mEPtr->Data[1] = a1;
    IncLog();
  }

  // write log message
  inline void Log(eLogType aEv,uint32 a0,uint32 a1,uint32 a2)
  {
    if(mOutLog==NULL)
      return;
    mEPtr->Event = aEv;
    mEPtr->Data[0] = a0;
    mEPtr->Data[1] = a1;
    mEPtr->Data[2] = a2;
    IncLog();
  }
  
  // write log message
  inline void Log(eLogType aEv,uint32 a0,uint32 a1,uint32 a2,uint32 a3)
  {
    if(mOutLog==NULL)
      return;
    mEPtr->Event = aEv;
    mEPtr->Data[0] = a0;
    mEPtr->Data[1] = a1;
    mEPtr->Data[2] = a2;
    mEPtr->Data[3] = a3;
    IncLog();
  }
};

#endif

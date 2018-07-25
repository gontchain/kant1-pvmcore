#ifndef PIPE_LINE_MACROS_H
#define PIPE_LINE_MACROS_H

#ifdef SYSTEMC_USED
#define STOP_PIPE_VAL (-1)

template<class TInstType,const int pipe_count>  class TPipeLine
{
public:
   class TPipe
   {
   protected:
      TInstType* CurInst;
      TInstType* WriteInst;
      int MaxBufSize;
      int BufSize; 

  public:
      int NextReq;
      int WriteReq;
      int RepeateCount;
      int AllowNext;
 
      inline TInstType* Inst2Write()
      { 
        return WriteInst;
      }
      
      inline int BufNotEmpty()
      { 
        return (BufSize > 0); 
      }

      inline int WriteAllow() 
      { 
        return (BufSize < MaxBufSize ); 
      }

      inline void WriteInst2Pipe(TInstType* aInst) 
      { 
        CurInst = aInst; 
        BufSize++;
        NextReq = (BufSize < MaxBufSize );
      }
      
      inline TInstType* GetCurInst()
      {
        RepeateCount = 0;
        if (BufSize == 1) 
          return CurInst;
        else
          return NULL;
      }
      
      inline void SendNext(int aNextReq = 1)
      { 
        WriteInst = CurInst;
        BufSize--; 
        WriteReq = 1;
        NextReq = aNextReq; 
        RepeateCount = 0;
      }

      inline void Repeate()
      {
        if(RepeateCount==1)
        {
          WriteReq = 0;
          return; 
        }
        SendNext(0);
        RepeateCount = 1; 
      }
      
      inline void Reset()
      {
        CurInst = NULL;
        WriteInst = NULL;
        NextReq = 1;
        WriteReq = 0;
        AllowNext = 1;
        BufSize = 0;
        MaxBufSize = 1;
        RepeateCount = 0;
      }
   };// end of TPipe 

private:
  TInstType mPipes[(pipe_count+1)*2];
  TPipe Pipes[pipe_count+1];
  int cur_count;  
public:
  
  inline void Reset()
  {
    for(int i=0;i<=pipe_count;i++)
      Pipes[i].Reset();
    cur_count = 0;
  }

  TPipeLine()
  {
    Reset();
  };

  inline void Update()
  {
    for(int i=0; i < pipe_count ; i++)
    {
      if((Pipes[i+1].NextReq==1) && (Pipes[i].WriteReq==1))
      {
        Pipes[i+1].WriteInst2Pipe(Pipes[i].Inst2Write());        
        Pipes[i+1].AllowNext = 1;
        Pipes[i].WriteReq = 0; // сбросили запрос на запись
      }      
      else
      {
        Pipes[i+1].AllowNext = Pipes[i+1].NextReq;
      }
    }
  }

  inline TInstType* GetCurInst(const int aPipeNum)
  {
    if(!aPipeNum)
    {
      TInstType *t = &mPipes[cur_count++];
      Pipes[0].WriteInst2Pipe(t);
      if(cur_count==((pipe_count+1)*2))
        cur_count = 0;
      return t;
    }
    else
      return Pipes[aPipeNum].GetCurInst();
  }
  

  inline int AllowExec(const int pipe)
  {
    int res; 
    if(pipe == (pipe_count))
      res = Pipes[pipe].BufNotEmpty();
    else if (pipe==0)
      res = (Pipes[pipe+1].AllowNext);
    else
      res =  ((Pipes[pipe+1].AllowNext || Pipes[pipe].RepeateCount)&&( Pipes[pipe].BufNotEmpty() ));
    if(res==0) Pipes[pipe].WriteReq = 0;
    return res;
  }

    

  inline void Repeate(const int aPipeNum)
  {

  }

  inline void SendNext(const int aPipeNum)
  {
    Pipes[aPipeNum].SendNext();
  }
 
  // free pipe without sending to the next stage 
  inline void Stop(const int aPipeNum)
  { 
    throw "not implemented";  
  }

};

#define RUN_PIPE(Iset,pipe)\
  {\
  if(Iset.AllowExec(pipe)==0){ return STOP_PIPE_VAL; }\
    cur_inst = Iset.GetCurInst(pipe);   \
  }

#define SEND_PIPE(Iset,next_pipe) Iset.SendNext(next_pipe);

#define REPEATE(Iset,next_pipe){ Iset.Repeate(next_pipe); return 1; }

#else

// fast emulator
template<class TInstType,const int pipe_count> class TPipeLine
{
public: 
  TInstType inst;
  inline void Update(){}
  inline void Reset(){}
};

#define RUN_PIPE(Iset,pipe) int aPipeNum = pipe; cur_inst=&Iset.inst;
#define SEND_PIPE(Iset,next_pipe)
#define REPEATE(Iset,next_pipe){ }

#endif


#endif
#ifndef THREADS_CONTROL_CONFIGURATION_H
#define THREADS_CONTROL_CONFIGURATION_H
// windows-specific functions
#include <stdio.h>

#include "export_config.h"

#define LOGPT(msg) //printf(msg)
#define LOGPT1(msg,par) //printf(msg,par)


#ifdef WIN32

#include <windows.h>
// тип указател€ на симул€ционный поток 
// содержит дескирптор потока, в котором происходит симул€ци€ работы процессора
// используетс€ только внутри макросов, может быть структурой
#define THDL   HANDLE
// тип дл€ описани€ идентификатора потока отладчика OwnerID, 
// используетс€ как адрес потока, которому поток симул€ции должен посылать сообщени€ об ошибках
#define TOwnerID DWORD
// макрос дл€ создани€ симул€ционного потока
// макрос создает поток и сохран€ет информацию (дескриптор или указатель, в зависимости от ќ—) в переменную Thread
// переменна€ Thread - глобальна€, она имеет тип THDL
#define CREATE_SIM_THREAD(){\
  Thread = CreateThread(0,0,Runner,(LPVOID)NULL,0,&ThreadId); \
}
// макрос "убивает" поток и все ассоциированные с ним структуры
#define DESTROY_THREAD()\
  TerminateThread(Thread,0);\
  CloseHandle(Thread);
// деклараци€ основной функции потока
#define SIM_FUNC_DECL() DWORD WINAPI Runner(LPVOID pParam)

#define SIM_START_IN_CONST 65536
// коды сообщений симул€тору от отладчика (дл€ Windows, дл€ Linux может и без кодов удобнее обойтись:
// запустить программу
#define SIM_START_IN      SIM_START_IN_CONST + 1
// остановить программу
#define SIM_STOP_IN       SIM_START_IN_CONST + 2
// коды сообщений отладчику от симул€тора:
// программа остановлена (например приехали к точке останова
#define SIM_STOPPED_OUT   SIM_START_IN_CONST + 3
// произошла ошибка
#define SIM_ERROR_OUT     SIM_START_IN_CONST + 4
// вызов функции ожидани€ сигнала старта симул€ции
// макрос ожидает, пока со стороны отладчика не придет событие "запустить программу на исполнение"
#define WAIT_START_MSG(){\
  MSG tmp_msg;\
  do{\
    GetMessage(&tmp_msg,NULL,SIM_START_IN,SIM_START_IN+1);\
  }while(tmp_msg.message != SIM_START_IN);\
}

// отправить отладчику сообщение об остановке
#define SEND_STOP_REASON(reason) PostThreadMessage(OwnerId,SIM_STOPPED_OUT,0,0);
// отправить (из команды Start) сообщение о запуске симул€тора
#define SEND_START_MSG() while(PostThreadMessage(ThreadId,SIM_START_IN,0,0)==FALSE);
// макрос используетс€ вне потока симул€ции
// ожидаем пока от симул€тора не придет сообщение "программа остановлена"
#define WAIT_STOP_MESSAGE(){\
  MSG tmp_msg;\
  GetMessage(&tmp_msg,NULL,SIM_STOPPED_OUT,SIM_ERROR_OUT);\
}

#else 
#ifdef LINOS

#include <pthread.h>
#include <signal.h>


#define THDL pthread_t 
#define DWORD unsigned long

#define LIB_EXPORT


#define CREATE_SIM_THREAD()\
{\
	int rc;\
	sigset_t   signal_mask;\
	sigemptyset(&signal_mask);\
    	sigaddset(&signal_mask, SIGUSR1);\
    	sigaddset(&signal_mask, SIGUSR2);\
    	rc = pthread_sigmask (SIG_BLOCK, &signal_mask, NULL);\
	if(rc!=0) printf("Error while sigmask setting\n");\
	LOGPT("create thread\n");\
	pthread_create(&Thread, NULL, Runner, NULL);\
	LOGPT1("Thread ID = %X\n",Thread);\
	pthread_detach(Thread);\
}


#define DESTROY_THREAD() {\
	LOGPT("thread destroyed\n");\
	pthread_cancel(Thread);\
}
 
 
#define SIM_FUNC_DECL() void* Runner(void*)
 
#define SIM_START_IN_CONST 65536

#define SIM_START_IN      SIM_START_IN_CONST + 1
#define SIM_STOP_IN       SIM_START_IN_CONST + 2

#define SIM_STOPPED_OUT   SIM_START_IN_CONST + 3
#define SIM_ERROR_OUT     SIM_START_IN_CONST + 4

#define GET_CUR_THREAD_ID() pthread_self();


#define WAIT_START_MSG()\
{\
	int i;\
	sigset_t ss;\
	sigemptyset(&ss);\
	sigaddset(&ss, SIGUSR1);\
	LOGPT("wait start signal\n");\
  	do sigwait(&ss, &i); while(i!=SIGUSR1);\
}


#define SEND_STOP_REASON(reason) \
	LOGPT("send stop reason\n");\
	pthread_kill(OwnerId,SIGUSR2);


#define SEND_START_MSG(){\
	LOGPT("send start signal\n");\
	pthread_kill(Thread, SIGUSR1);\
	LOGPT("start signal sent\n");\
}


#define WAIT_STOP_MESSAGE()\
{\
	int i;\
	sigset_t ss;\
	sigemptyset(&ss);\
	sigaddset(&ss, SIGUSR2);\
	LOGPT("send stop reason\n");\
  	do sigwait(&ss, &i); while(i!=SIGUSR2);\
} 

#else

#error platform is not supported

#endif // ifdef LINOS

#endif // WINDOWS



#ifdef FONIN_DEBUG_SUPPORT
#define OLDDBG_EXPORT extern "C" LIB_EXPORT
#else
#define OLDDBG_EXPORT
#endif  // FONIN_DEBUG_SUPPORT

#endif

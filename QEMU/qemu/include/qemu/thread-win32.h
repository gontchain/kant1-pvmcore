#ifndef __QEMU_THREAD_WIN32_H
#define __QEMU_THREAD_WIN32_H 1
#include <windows.h>

typedef struct  {
    CRITICAL_SECTION lock;
    LONG owner;
}QemuMutex;

typedef struct  {
    LONG waiters, target;
    HANDLE sema;
    HANDLE continue_event;
}QemuCond;

typedef struct  {
    HANDLE sema;
}QemuSemaphore;

typedef struct  {
    HANDLE event;
}QemuEvent;

typedef struct QemuThreadData QemuThreadData;

typedef struct {
    QemuThreadData *data;
    unsigned tid;
}QemuThread;
/* Only valid for joinable threads.  */
HANDLE qemu_thread_get_handle(QemuThread *thread);

#endif

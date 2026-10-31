#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02114410.h"
typedef unsigned int u32;
typedef int s32;

extern OSThreadInfo data_021fcc2c;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 state);
void OSi_DequeueItem(OSThread *thread, OSMutex *mutex);
void OSi_EnqueueTail(OSThread *thread, OSMutex *mutex);

void OS_InitMutex(OSMutex *mutex) {
    mutex->queue.head = mutex->queue.tail = 0;
    mutex->thread = 0;
    mutex->count = 0;
}

void OS_LockMutex(OSMutex *mutex) {
    u32 enabled = OS_DisableInterrupts();
    OSThread *currentThread = data_021fcc2c.current;
    for (;;) {
        if (mutex->thread == 0) {
            mutex->thread = currentThread;
            mutex->count++;
            OSi_EnqueueTail(currentThread, mutex);
            break;
        }
        if (mutex->thread == currentThread) {
            mutex->count++;
            break;
        }
        currentThread->mutex = mutex;
        OS_SleepThread(&mutex->queue);
        currentThread->mutex = 0;
    }
    OS_RestoreInterrupts(enabled);
}

void OS_UnlockMutex(OSMutex *mutex) {
    u32 enabled = OS_DisableInterrupts();
    OSThread *currentThread = data_021fcc2c.current;
    if (mutex->thread == currentThread) {
        if (--mutex->count == 0) {
            OSi_DequeueItem(currentThread, mutex);
            mutex->thread = 0;
            OS_WakeupThread(&mutex->queue);
        }
    }
    OS_RestoreInterrupts(enabled);
}

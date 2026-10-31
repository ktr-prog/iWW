#include "ds_div.h"
#include "host_mem.h"
#include "sys/OSThread.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

#include "ds_stdarg.h"
#include "proto/autoload_2/unk_021127c0.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02113fd8.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/itcm/unk_01ffa3cc.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0206d49c.h"

typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct {
    OSThreadQueue sendQueue;
    OSThreadQueue recvQueue;
    void **msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

typedef struct {
    s32 len;
    char *ptr;
} StrBuf;

extern OSThreadInfo data_021fcc2c;
extern OSThread *data_021fcc30;
extern OSThread **data_021fcc24;
extern u32 data_021fcc14;
extern u32 data_021fcc18;
extern u32 data_021fcc1c;
extern void (*data_021fcc20)(OSThread *, OSThread *);
extern u32 data_021fcc28;
extern OSThread data_021fcc3c;
extern OSThread data_021fccfc;
extern u32 data_021fce84;
extern u32 data_0213bff0;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 e);
u32 OS_GetProcMode(void);
void OS_LoadContext(OSThread *t);
BOOL OS_SaveContext(OSThread *t);
u32 OS_GetLockID(void);
u16 OS_ReadOwnerOfLockWord(void *p);
u32 OS_TryLockCartridge(u32 id);
void OS_UnlockCartridge(u32 id);
void MIi_CpuClear32(u32 data, void *dest, u32 size);

void *OS_SetSwitchThreadCallback(void (*cb)(OSThread *, OSThread *));
void OS_VSPrintf(char *dst, const char *fmt, va_list ap);
void OS_WakeupThreadDirect(OSThread *t);
u32 OS_DisableScheduler(void);
u32 OS_EnableScheduler(void);
void OSi_RemoveThreadFromList(OSThread *t);
void OSi_InsertThreadToList(OSThread *t);
OSThread *OSi_RemoveLinkFromQueue(OSThreadQueue *q);
void OSi_InsertLinkToQueue(OSThreadQueue *q, OSThread *t);
void OS_InitContext(OSContext *c, uptr pc, uptr sp);
void OSi_ExitThread_ArgSpecified(OSThread *t, void *arg);
void OSi_CancelThreadAlarmForSleep(OSThread *t);
void OS_SetThreadDestructor(OSThread *t, void (*d)(void *));
BOOL OS_SetThreadPriority(OSThread *t, u32 prio);
OSThread *OS_SelectThread(void);
void OSi_UnlockAllMutex(OSThread *t);
void OSi_EnqueueTail(OSThread *t, OSMutex *m);
OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutex **q);
u32 OSi_DetectDeviceType(void);
BOOL func_02113ed0(void);
u32 OSi_GetUnusedThreadId(void);
void OSi_SleepAlarmCallback(void *arg);
void OS_WakeupThreadDirect(OSThread *t);
void OS_KillThreadWithPriority(OSThread *t, void *arg, u32 prio);
u32 OS_GetThreadPriority(OSThread *t);
void OS_CreateThread(OSThread *t, void (*f)(void *), void *arg, void *stack, u32 size, u32 prio);

void OSi_UnlockAllMutex(OSThread *t) {
    OSMutex **q;
    if (t->mutexHead == 0) return;
    q = &t->mutexHead;
    do {
        OSMutex *m = OSi_RemoveMutexLinkFromQueue(q);
        m->count = 0;
        m->thread = 0;
        OS_WakeupThread(&m->queue);
    } while (t->mutexHead != 0);
}

BOOL OS_TryLockMutex(OSMutex *m) {
    BOOL r;
    u32 e = OS_DisableInterrupts();
    OSThread *cur = data_021fcc2c.current;
    if (m->thread == 0) {
        m->thread = cur;
        m->count++;
        OSi_EnqueueTail(cur, m);
        r = 1;
    } else if (m->thread == cur) {
        m->count++;
        r = 1;
    } else {
        r = 0;
    }
    OS_RestoreInterrupts(e);
    return r;
}

void OSi_EnqueueTail(OSThread *t, OSMutex *m) {
    OSMutex *tail = t->mutexTail;
    if (tail == 0) t->mutexHead = m;
    else tail->next = m;
    m->prev = tail;
    m->next = 0;
    t->mutexTail = m;
}

void OSi_DequeueItem(OSThread *t, OSMutex *m) {
    OSMutex *next = m->next;
    OSMutex *prev = m->prev;
    if (next == 0) t->mutexTail = prev;
    else next->prev = prev;
    if (prev == 0) t->mutexHead = next;
    else prev->next = next;
}

void OS_InitMessageQueue(OSMessageQueue *mq, void **buf, s32 count) {
    mq->sendQueue.tail = 0;
    mq->sendQueue.head = mq->sendQueue.tail;
    mq->recvQueue.tail = 0;
    mq->recvQueue.head = mq->recvQueue.tail;
    mq->msgArray = buf;
    mq->msgCount = count;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

BOOL OS_SendMessage(OSMessageQueue *mq, void *msg, s32 flags) {
    u32 e = OS_DisableInterrupts();
    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(e);
            return 0;
        }
        OS_SleepThread(&mq->sendQueue);
    }
    mq->msgArray[DS_MOD((mq->firstIndex + mq->usedCount), mq->msgCount)] = msg;
    mq->usedCount++;
    OS_WakeupThread(&mq->recvQueue);
    OS_RestoreInterrupts(e);
    return 1;
}

BOOL OS_ReceiveMessage(OSMessageQueue *mq, void **msg, s32 flags) {
    u32 e = OS_DisableInterrupts();
    while (mq->usedCount == 0) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(e);
            return 0;
        }
        OS_SleepThread(&mq->recvQueue);
    }
    if (msg != 0) *msg = mq->msgArray[mq->firstIndex];
    mq->firstIndex = DS_MOD((mq->firstIndex + 1), mq->msgCount);
    mq->usedCount--;
    OS_WakeupThread(&mq->sendQueue);
    OS_RestoreInterrupts(e);
    return 1;
}

BOOL OS_JamMessage(OSMessageQueue *mq, void *msg, s32 flags) {
    u32 e = OS_DisableInterrupts();
    while (mq->msgCount <= mq->usedCount) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(e);
            return 0;
        }
        OS_SleepThread(&mq->sendQueue);
    }
    mq->firstIndex = DS_MOD((mq->firstIndex + mq->msgCount - 1), mq->msgCount);
    mq->msgArray[mq->firstIndex] = msg;
    mq->usedCount++;
    OS_WakeupThread(&mq->recvQueue);
    OS_RestoreInterrupts(e);
    return 1;
}

BOOL OS_ReadMessage(OSMessageQueue *mq, void **msg, s32 flags) {
    u32 e = OS_DisableInterrupts();
    while (mq->usedCount == 0) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(e);
            return 0;
        }
        OS_SleepThread(&mq->recvQueue);
    }
    if (msg != 0) *msg = mq->msgArray[mq->firstIndex];
    OS_RestoreInterrupts(e);
    return 1;
}

u32 OS_GetConsoleType(void) {
    if (data_0213bff0 == 0xffffffff) {
        u32 base = OSi_DetectDeviceType();
        u32 v;
        if (OS_IsRunOnEmulator() != 0) v = base | 0x10000000;
        else if (func_02113ed0() != 0) v = base | 0x40000000;
        else if (base & 0x01000000) v = base | 0x20000000;
        else v = base | 0x80000000;
        data_0213bff0 = v | *HW_SYSWORK(volatile u16, mmemCheckerSub);
    }
    return data_0213bff0;
}

u32 data_0213bff0 = 0xffffffff;

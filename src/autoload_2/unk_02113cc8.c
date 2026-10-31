#include "sys/OSThread.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

#include "ds_stdarg.h"
#include "proto/autoload_2/unk_021127c0.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02113cc8.h"
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

u32 OSi_GetUnusedThreadId(void) {
    data_021fcc1c++;
    return data_021fcc1c;
}

void OSi_InsertLinkToQueue(OSThreadQueue *q, OSThread *thread) {
    OSThread *cur = q->head;
    OSThread *prev;
    for (; cur != 0 && cur->priority <= thread->priority; cur = cur->linkNext) {
        if (cur == thread) return;
    }
    if (cur == 0) {
        prev = q->tail;
        if (prev == 0) q->head = thread;
        else prev->linkNext = thread;
        thread->linkPrev = prev;
        thread->linkNext = 0;
        q->tail = thread;
        return;
    }
    prev = cur->linkPrev;
    if (prev == 0) q->head = thread;
    else prev->linkNext = thread;
    thread->linkPrev = prev;
    thread->linkNext = cur;
    cur->linkPrev = thread;
}

OSThread *OSi_RemoveLinkFromQueue(OSThreadQueue *q) {
    OSThread *t = q->head;
    if (t != 0) {
        OSThread *n = t->linkNext;
        q->head = n;
        if (n != 0) n->linkPrev = 0;
        else {
            q->tail = 0;
            t->queue = 0;
        }
    }
    return t;
}

OSMutex *OSi_RemoveMutexLinkFromQueue(OSMutex **q) {
    OSMutex *m = q[0];
    if (m != 0) {
        OSMutex *n = m->next;
        q[0] = n;
        if (n != 0) n->prev = 0;
        else q[1] = 0;
    }
    return m;
}

void OSi_InsertThreadToList(OSThread *thread) {
    OSThread *t;
    OSThread *prev;
    OSThread *head;
    prev = 0;
    head = data_021fcc2c.list;
    t = head;
    while (t != 0 && t->priority < thread->priority) {
        prev = t;
        t = t->next;
    }
    if (prev == 0) {
        thread->next = head;
        data_021fcc2c.list = thread;
    } else {
        thread->next = prev->next;
        prev->next = thread;
    }
}

void OSi_RemoveThreadFromList(OSThread *thread) {
    OSThread *prev = 0;
    OSThread *t = data_021fcc2c.list;
    for (; t != 0 && t != thread; prev = t, t = t->next) {}
    if (prev == 0) data_021fcc2c.list = thread->next;
    else prev->next = thread->next;
}


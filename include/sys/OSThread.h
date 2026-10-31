#ifndef SYS_OSTHREAD_H
#define SYS_OSTHREAD_H

#include "types.h"


typedef struct OSThread OSThread;
typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct OSContext {
    u32 cpsr;
    uptr r[15];
    u32 pc_plus4;
    u32 sp_svc;
    u32 cp_context[7];
} OSContext;

struct OSThread {
    OSContext context;
    u32 state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    OSThreadQueue *queue;
    OSThread *linkPrev;
    OSThread *linkNext;
    void *mutex;
    OSMutex *mutexHead;
    OSMutex *mutexTail;
    u8 *stackTop;
    u8 *stackBottom;
    u32 stackWarningOffset;
    OSThreadQueue joinQueue;
    void *specific[3];
    void *alarm;
    void (*destructor)(void *);
    void *parameter;
    u32 systemErrno;
};

struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutex *next;
    OSMutex *prev;
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void (*switchCallback)(OSThread *, OSThread *);
} OSThreadInfo;

#endif

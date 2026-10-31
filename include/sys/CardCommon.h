#ifndef SYS_CARDCOMMON_H
#define SYS_CARDCOMMON_H

#include "types.h"
#include "sys/OSThread.h"

struct CardCommon {
    /* 0x00 */ u32 *result;
    /* 0x04 */ u32 arg;
    /* 0x08 */ volatile u32 lockOwner;
    /* 0x0c */ volatile u32 lockCount;
    /* 0x10 */ OSThreadQueue lockQueue;
    /* 0x18 */ u32 lockType;
    /* 0x1c */ uptr src;
    /* 0x20 */ uptr dst;
    /* 0x24 */ u32 len;
    /* 0x28 */ u32 dma;
    /* 0x2c */ u32 _2c[3];
    /* 0x38 */ void (*callback)(u32);
    /* 0x3c */ uptr callbackArg;
    /* 0x40 */ void (*task)(struct CardCommon *);
    /* 0x44 */ OSThread thread;
    /* 0x104 */ void *waiter;
    /* 0x108 */ u32 priority;
    /* 0x10c */ OSThreadQueue queue;
    /* 0x114 */ u32 flag;
};

#endif

#ifndef NET_SIMPLESTART_H
#define NET_SIMPLESTART_H

#include "types.h"

typedef struct SimpleStartStatus SimpleStartStatus;
struct SimpleStartStatus {
    s32 state;
    s32 remainingMs;
    s32 result;
};

typedef void (*SimpleStartStatusFunc)(SimpleStartStatus *status);
typedef void *(*SimpleStartAllocFunc)(u32 size);
typedef void (*SimpleStartFreeFunc)(void *p);
typedef void (*SimpleStartWcmNotifyFunc)(u32 msg, u32 arg);

#endif

#ifndef SYS_OSMESSAGEQUEUE_H
#define SYS_OSMESSAGEQUEUE_H

#include "types.h"
#include "sys/OSThread.h"


typedef void *OSMessage;

typedef struct OSMessageQueue {
    /* 0x00 */ OSThreadQueue queueSend;
    /* 0x08 */ OSThreadQueue queueReceive;
    /* 0x10 */ OSMessage *msgArray;
    /* 0x14 */ s32 msgCount;
    /* 0x18 */ s32 firstIndex;
    /* 0x1c */ s32 usedCount;
} OSMessageQueue;

#endif

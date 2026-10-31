#ifndef NITRO_OS_ALARM_H
#define NITRO_OS_ALARM_H

#include "types.h"


typedef struct OSAlarm OSAlarm;
struct OSAlarm {
    /* 0x00 */ void (*handler)(void *);
    /* 0x04 */ void *arg;
    /* 0x08 */ u32 tag;
    /* 0x0c */ u64 fire;
    /* 0x14 */ OSAlarm *prev;
    /* 0x18 */ OSAlarm *next;
    /* 0x1c */ u64 period;
    /* 0x24 */ u64 start;
};

typedef struct {
    OSAlarm *head;
    OSAlarm *tail;
} OSAlarmQueue;

#endif

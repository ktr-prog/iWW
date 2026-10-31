#ifndef SYS_CLOCKDATETIME_H
#define SYS_CLOCKDATETIME_H

#include "types.h"

typedef struct ClockDateTime {
    /* 0x0 */ u8 second;
    /* 0x1 */ u8 minute;
    /* 0x2 */ u8 hour;
    /* 0x3 */ u8 day;
    /* 0x4 */ u8 month;
    /* 0x5 */ u8 year;
    /* 0x6 */ u8 unk_06;
    /* 0x7 */ u8 unk_07;
} ClockDateTime;

typedef union ClockDateTimeWords {
    ClockDateTime dt;
    u32 words[2];
} ClockDateTimeWords;

#endif

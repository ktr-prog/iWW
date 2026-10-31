#ifndef NITRO_OS_RTC_H
#define NITRO_OS_RTC_H

#include "types.h"


typedef struct RTCDate {
    /* 0x0 */ u32 year;
    /* 0x4 */ u32 month;
    /* 0x8 */ u32 day;
    /* 0xc */ s32 week;
} RTCDate;

typedef struct RTCTime {
    /* 0x0 */ u32 hour;
    /* 0x4 */ u32 minute;
    /* 0x8 */ u32 second;
} RTCTime;

typedef struct OSOwnerInfo {
    /* 0x00 */ u8 language;
    /* 0x01 */ u8 favoriteColor;
    /* 0x02 */ u8 birthMonth;
    /* 0x03 */ u8 birthDay;
    /* 0x04 */ u16 nickName[10];
    /* 0x18 */ u16 nickNameLength;
    /* 0x1a */ u16 comment[26];
    /* 0x4e */ u16 commentLength;
} OSOwnerInfo;

#endif

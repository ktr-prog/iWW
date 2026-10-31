#ifndef SYS_CLOCKDATE_H
#define SYS_CLOCKDATE_H

#include "types.h"


struct ClockDate {
    /* 0x00 */ u8 day;
    /* 0x01 */ u8 month;
    /* 0x02 */ u8 year;
    /* 0x03 */ u8 pad_03;
};
#ifndef __cplusplus
typedef struct ClockDate ClockDate;
#endif

#endif

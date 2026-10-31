#ifndef TOWN_TOWNEVENTRECORD_H
#define TOWN_TOWNEVENTRECORD_H

#include "types.h"


struct TownEventRecord {
    /* 0x00 */ u16 eventId;
    /* 0x02 */ u8 year;
    /* 0x04 */ s32 start;
    /* 0x08 */ s32 end;
};
#ifndef __cplusplus
typedef struct TownEventRecord TownEventRecord;
#endif

#endif

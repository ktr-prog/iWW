#ifndef SAVE_DRAMAPART_H
#define SAVE_DRAMAPART_H

#include "types.h"
#include "sys/ClockDate.h"

#ifndef __cplusplus
typedef struct Unk_020874e8_Bits Unk_020874e8_Bits;
typedef struct DramaRecord DramaRecord;
#endif

struct Unk_020874e8_Bits {
    u8 a : 2;
    u8 b : 3;
    u8 c : 3;
};

struct DramaRecord {
    /* 0x0 */ Unk_020874e8_Bits lastPart;
    /* 0x1 */ ClockDate date;
};

#endif

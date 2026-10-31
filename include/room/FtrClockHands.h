#ifndef ROOM_FTRCLOCKHANDS_H
#define ROOM_FTRCLOCKHANDS_H

#include "types.h"

struct FtrClockHands {
    ~FtrClockHands();
    void set(s32 a, s32 b);
    void clear();

    /* 0x00 */ s8 hourJnt;
    /* 0x01 */ s8 minJnt;
    /* 0x02 */ u8 valid;
};

#endif

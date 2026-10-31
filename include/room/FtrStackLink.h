#ifndef ROOM_FTRSTACKLINK_H
#define ROOM_FTRSTACKLINK_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "room/FtrActorParts.h"

struct FtrStackLink {
    ~FtrStackLink();
    BOOL attachAt(s32 x, s32 y, s16 z);
    BOOL set(s32 idx, VecFx32 *pos, s32 ang);
    s32 getRelAngle();
    VecFx32 *getRelPos();
    s32 getParentIndex();
    BOOL isAttached();
    void clear();
    /* 0x00 */ s16 parentIndex;
    /* 0x02 */ s16 relAngle;
    /* 0x04 */ VecFx32 relPos;
};

#endif

#ifndef FIELD_BOTTLETHROW_H
#define FIELD_BOTTLETHROW_H
#include "game/CollisionState.h"

#include "types.h"
#include "gfx/VecFx32.h"


struct BottleThrow {
    BottleThrow();
    ~BottleThrow();
    /* 0x00 */ CollisionState collisionState;
    /* 0x30 */ u8 state;
    /* 0x31 */ u8 pad_31[3];
    /* 0x34 */ VecFx32 position;
    /* 0x40 */ VecFx32 startPos;
    /* 0x4c */ VecFx32 targetPos;
    /* 0x58 */ s32 stateTimer;
    /* 0x5c */ u8 isLocal;
    /* 0x5d */ u8 pad_5d[3];
};

#endif

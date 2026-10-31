#ifndef PLAYER_PLAYERWALKTOWORK_H
#define PLAYER_PLAYERWALKTOWORK_H

#include "types.h"
#include "gfx/VecFx32.h"

struct PlayerWalkToWork {
    /* 0x00 */ VecFx32Ctor targetPos;
    /* 0x0c */ s32 walkSpeed;
    /* 0x10 */ s32 maxSpeed;
    /* 0x14 */ s32 prevAction;
    void initWalkTo(VecFx32Ctor v, s32 a, s32 b);
};

#endif

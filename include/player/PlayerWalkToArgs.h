#ifndef PLAYER_PLAYERWALKTOARGS_H
#define PLAYER_PLAYERWALKTOARGS_H

#include "types.h"
#include "gfx/VecFx32.h"


struct PlayerWalkToArgs {
    /* 0x00 */ VecFx32Ctor targetPos;
    /* 0x0c */ s32 maxSpeed;
    void setWalkToArgs(VecFx32Ctor v, s32 a);
};

#endif

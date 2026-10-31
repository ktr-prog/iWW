#ifndef PLAYER_PLAYERACT32LOCALS_H
#define PLAYER_PLAYERACT32LOCALS_H

#include "types.h"
#include "gfx/VecFx32.h"


struct PlayerAct32Locals {
    /* 0x00 */ VecFx32 cur;
    /* 0x0c */ VecFx32 pos;
    /* 0x18 */ VecFx32 diff;
};

#endif

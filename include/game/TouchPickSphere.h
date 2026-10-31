#ifndef GAME_TOUCHPICKSPHERE_H
#define GAME_TOUCHPICKSPHERE_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/HitSphere.h"


struct TouchPickSphere : HitSphere {
    TouchPickSphere();
    ~TouchPickSphere();
    BOOL setupCurved(VecFx32 *pos, s32 radius, s32 kind, u8 index);
    BOOL setup(VecFx32 *pos, s32 radius, s32 kind, u8 index);
    /* 0x10 */ u8 index;
    /* 0x14 */ s32 kind;
    /* 0x18 */ TouchPickSphere *next;
};

#endif

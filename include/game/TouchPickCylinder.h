#ifndef GAME_TOUCHPICKCYLINDER_H
#define GAME_TOUCHPICKCYLINDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/CollisionCylinder.h"

struct TouchPickCylinder : CollisionCylinderX {
    TouchPickCylinder();
    ~TouchPickCylinder();
    BOOL setup(VecFx32 *pos, s32 radius, s32 height, s32 kind, u8 index);
    /* 0x14 */ s32 kind;
    /* 0x18 */ u8 index;
    /* 0x1c */ TouchPickCylinder *next;
};

#endif

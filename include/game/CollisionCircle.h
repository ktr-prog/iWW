#ifndef GAME_COLLISIONCIRCLE_H
#define GAME_COLLISIONCIRCLE_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_0202f2ac_V3.h"

class CollisionCircle {
public:
    /* 0x0 */ VecFx32 center;
    /* 0xc */ s32 circleRadius;

    BOOL containsXZ(VecFx32 *pt);
    void setCircle(VecFx32 *pos, s32 radius);
    ~CollisionCircle();
    CollisionCircle(VecFx32 *pos, s32 radius);
    CollisionCircle();
};

#endif

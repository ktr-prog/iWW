#ifndef GAME_COLLISIONSEGMENT_H
#define GAME_COLLISIONSEGMENT_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_0202f2ac_V3.h"

class CollisionSegment {
public:
    /* 0x00 */ VecFx32 start;
    /* 0x0c */ VecFx32 end;
    /* 0x18 */ VecFx32 dir;

    BOOL isBetweenEnds(VecFx32 *pt);
    void projectPoint(VecFx32 *out, VecFx32 *pt);
    s32 closestPoint(VecFx32 *out, VecFx32 *pt);
    void set(VecFx32 *a, VecFx32 *b);
    s32 distanceTo(VecFx32 *pt);
    s32 calcDir(VecFx32 *out);
    ~CollisionSegment();
    CollisionSegment(VecFx32 *a, VecFx32 *b);
};

#endif

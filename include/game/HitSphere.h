#ifndef GAME_HITSPHERE_H
#define GAME_HITSPHERE_H

#include "types.h"
#include "gfx/VecFx32.h"

class CollisionSegment;

struct HitSphere {
    /* 0x0 */ VecFx32 center;
    /* 0xc */ s32 radius;

    HitSphere();
    ~HitSphere();
    BOOL intersectSegment(VecFx32Ctor *out, CollisionSegment *cap);
    void set(VecFx32Ctor *p, s32 r);
};

#endif

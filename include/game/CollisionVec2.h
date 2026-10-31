#ifndef GAME_COLLISIONVEC2_H
#define GAME_COLLISIONVEC2_H

#include "types.h"

class CollisionVec2 {
public:
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;

    CollisionVec2() {}
    CollisionVec2(s32 a, s32 b);
    MODERN_EMIT ~CollisionVec2() {}
    void operator=(const CollisionVec2 &o) { x = o.x; y = o.y; }
    CollisionVec2(const CollisionVec2 &o) { x = o.x; y = o.y; }
    void set(s32 a, s32 b);
    CollisionVec2 *setFrom(CollisionVec2 *p);
    void add(CollisionVec2 *p);
    void setSum(CollisionVec2 *a, CollisionVec2 *b);
    void setDiff(CollisionVec2 *a, CollisionVec2 *b);
    CollisionVec2 *scale(s32 k);
    s64 distSq(CollisionVec2 *p);
    BOOL normalize();
    void rotate(s16 a);
    void setEdgeNormal(CollisionVec2 *a, CollisionVec2 *b);
};

#endif

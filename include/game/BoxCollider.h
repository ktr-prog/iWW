#ifndef GAME_BOXCOLLIDER_H
#define GAME_BOXCOLLIDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/CollisionVec2.h"

class CollisionEdge;
class Actor;

struct ZeroedCollisionVec2 : CollisionVec2 {
    ZeroedCollisionVec2() { set(0, 0); }
    ~ZeroedCollisionVec2() {}
};

struct BoxCollider {
    virtual void onEdgeContact(CollisionEdge *edge, Actor *actor, s32 r);
    /* 0x04 */ VecFx32 boxPos;
    /* 0x10 */ VecFx32 size;
    /* 0x1c */ VecFx32 scale;
    /* 0x28 */ s16 angle;
    /* 0x2a */ s16 numCorners;
    /* 0x2c */ BoxCollider *next;
    /* 0x30 */ VecFx32 worldCorners[4];
    /* 0x60 */ ZeroedCollisionVec2 edgeNormals[4];
    /* 0x80 */ VecFx32 boundsCenter;
    /* 0x8c */ VecFx32 boundsHalfSize;
    /* 0x98 */ u8 isActive;

    BoxCollider();
    ~BoxCollider();
    BOOL setupBox(s32 a, s32 b, s32 c, VecFx32 *p, s16 s, VecFx32 *q);
    void resetBox();
};

struct BoxColliderShape : BoxCollider {
    BOOL updateTransform(VecFx32 *a, s32 ang, VecFx32 *b);
};

#endif

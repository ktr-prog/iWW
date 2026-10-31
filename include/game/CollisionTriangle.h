#ifndef GAME_COLLISIONTRIANGLE_H
#define GAME_COLLISIONTRIANGLE_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_0202f2ac_V3.h"

class CollisionTriangle {
public:
    CollisionTriangle();
    CollisionTriangle(VecFx32 *a, VecFx32 *b, VecFx32 *c, VecFx32 *d);
    ~CollisionTriangle();
    virtual BOOL pushOutFace(Unk_0202f2ac_V3 *a, Unk_0202f2ac_V3 *b, s32 c);
    virtual BOOL pushBackCrossing(Unk_0202f2ac_V3 *a, Unk_0202f2ac_V3 *b, s32 c);
    virtual BOOL pushOutEdges(Unk_0202f2ac_V3 *a, Unk_0202f2ac_V3 *b, s32 c);
    virtual BOOL collide(Unk_0202f2ac_V3 *a, Unk_0202f2ac_V3 *b, s32 c);
    /* 0x04 */ Unk_0202f2ac_V3 vertex0;
    /* 0x10 */ Unk_0202f2ac_V3 vertex1;
    /* 0x1c */ Unk_0202f2ac_V3 vertex2;
    /* 0x28 */ Unk_0202f2ac_V3 normal;
    /* 0x34 */ s32 offset;
    BOOL intersectLine(Unk_0202f2ac_V3 *out, Unk_0202f2ac_V3 *p, Unk_0202f2ac_V3 *q);
    BOOL intersectSegment(Unk_0202f2ac_V3 *out, Unk_0202f2ac_V3 *p, Unk_0202f2ac_V3 *q);
    BOOL containsYZ(Unk_0202f2ac_V3 *p);
    BOOL containsXY(Unk_0202f2ac_V3 *p);
    s32 distanceTo(Unk_0202f2ac_V3 *p);
    s32 calcOffset();
    BOOL containsXZ(Unk_0202f2ac_V3 *p);
    BOOL set(Unk_0202f2ac_V3 *a, Unk_0202f2ac_V3 *b, Unk_0202f2ac_V3 *c, Unk_0202f2ac_V3 *d);
};

#endif

#ifndef GAME_COLLISIONEDGE_H
#define GAME_COLLISIONEDGE_H

#include "types.h"
#include "game/CollisionVec2.h"

class CollisionEdge {
public:
    CollisionEdge() {
        start.set(0, 0);
        end.set(0, 0);
        normal.set(0, 0);
    }
    CollisionEdge(CollisionVec2 *a, CollisionVec2 *b);
    CollisionEdge(CollisionVec2 *a, CollisionVec2 *b, CollisionVec2 *c);
    ~CollisionEdge();
    virtual BOOL hasRoundEnds();

    BOOL pushBackCrossing(CollisionVec2 *a, CollisionVec2 *b, s32 c);
    BOOL pushOutEnds(CollisionVec2 *a, CollisionVec2 *b, s32 c);
    BOOL pushOutFace(CollisionVec2 *a, CollisionVec2 *b, s32 c);
    BOOL isBetweenEnds(CollisionVec2 *a);
    BOOL intersectSegment(CollisionVec2 *out, CollisionVec2 *a, CollisionVec2 *b);
    BOOL intersectLine(CollisionVec2 *out, CollisionVec2 *a, CollisionVec2 *b);
    s32 distanceTo(CollisionVec2 *p);
    s32 calcOffset();
    void set(CollisionVec2 *a, CollisionVec2 *b, CollisionVec2 *c);

    /* 0x04 */ CollisionVec2 start;
    /* 0x0c */ CollisionVec2 end;
    /* 0x14 */ CollisionVec2 normal;
    /* 0x1c */ s32 offset;
};

#endif

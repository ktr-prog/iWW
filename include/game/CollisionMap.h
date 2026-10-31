#ifndef GAME_COLLISIONMAP_H
#define GAME_COLLISIONMAP_H

#include "types.h"

struct UnitShapeQueryX;

class CollisionBlockRef {
public:
    CollisionBlockRef()
    {
        attrs = 0;
        walkLinks = 0;
    }
    ~CollisionBlockRef() {}

    u8 *attrs;
    u8 *walkLinks;
};

class CollisionMap {
public:
    CollisionMap() { reset(); }
    ~CollisionMap() {}
    void reset();

    CollisionBlockRef blocks[6][6];
    UnitShapeQueryX *shapeQuery;
    u32 numBlocksX;
    u32 numBlocksZ;
    s32 lockedExit;
    u8 allBlocksSet;
    u8 pad_131;
    s16 prevWaveLevel;
    s16 waveLevel;
};

extern "C" CollisionMap *gCurCollisionMap;

#endif

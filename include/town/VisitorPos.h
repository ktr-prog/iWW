#ifndef TOWN_VISITORPOS_H
#define TOWN_VISITORPOS_H

#include "types.h"
#include "gfx/VecFx32.h"

class BlockMap;


struct VisitorPos {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 z;

    void getPos(VecFx32 *out) const;
    void setPos(s32 a, s32 b);
    BOOL pickRandomPos();
    BOOL pickFreeInAcre(VecFx32 *out, s32 *pos, BlockMap *map);
    s32 countFreeInAcre(s32 *pos, BlockMap *map);
};

#endif

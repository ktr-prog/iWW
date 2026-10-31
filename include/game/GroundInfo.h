#ifndef GAME_GROUNDINFO_H
#define GAME_GROUNDINFO_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/GroundInfoBase.h"

class GroundInfo : public GroundInfoBase {
public:
    GroundInfo() {}
    GroundInfo(VecFx32 *v, s32 a, s32 b);
    GroundInfo(u32 x, u32 y, u32 z, u32 w) { initAtUnit(x, y, z, w); }
    ~GroundInfo();
    GroundInfo *initAtUnit(s32 x, s32 z, s32 a, s32 b);
    GroundInfo *initAtPos(VecFx32 *v, s32 a, s32 b);
};

#endif

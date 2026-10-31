#ifndef GFX_V3_H
#define GFX_V3_H

#include "types.h"
#include "gfx/VecFx32.h"

struct V3 {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 z;
};

struct V3Arr {
    /* 0x0 */ s32 v[3];
};

typedef u16 (*SplPosFn)(VecFx32 *pos, VecFx32 v);

#endif

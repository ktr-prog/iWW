#ifndef GFX_MAGF_H
#define GFX_MAGF_H

#include "types.h"

struct MagF {
    /* 0x0 */ s32 x, y, z;
    /* 0xc */ s16 force;
};

#endif

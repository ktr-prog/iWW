#ifndef GFX_QUAT_H
#define GFX_QUAT_H

#include "types.h"

struct Quat {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0c */ s32 w;
};

#endif

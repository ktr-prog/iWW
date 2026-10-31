#ifndef GFX_VEC3Z_H
#define GFX_VEC3Z_H

#include "types.h"

struct Vec3Z2 {
    /* 0x0 */ s32 x, y, z;
    Vec3Z2() {
        x = 0;
        y = 0;
        z = 0x1000;
    }
};

struct Vec3Z {
    /* 0x0 */ s32 x, y, z;
    Vec3Z() {
        x = 0;
        y = 0;
        z = 0;
    }
};

#endif

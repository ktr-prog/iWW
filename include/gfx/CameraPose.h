#ifndef GFX_CAMERAPOSE_H
#define GFX_CAMERAPOSE_H

#include "types.h"

struct CameraPose {
    /* 0x00 */ s16 h0, h1;
    /* 0x04 */ s32 w0;
    /* 0x08 */ s32 x, y, z;
};

#endif

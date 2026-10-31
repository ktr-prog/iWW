#ifndef GFX_CAMERASETUP_H
#define GFX_CAMERASETUP_H

#include "types.h"

struct CameraSetup {
    /* 0x00 */ s16 a, b;
    /* 0x04 */ s32 c0, c1, c2, c3, c4, c5, c6;
    ~CameraSetup();
};

#endif

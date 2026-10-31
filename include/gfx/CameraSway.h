#ifndef GFX_CAMERASWAY_H
#define GFX_CAMERASWAY_H

#include "types.h"

struct CameraSwayState {
    /* 0x0 */ s16 bobPhase;
    /* 0x2 */ s16 rollPhase;
    /* 0x4 */ u16 bobTimer;
    /* 0x6 */ u16 rollTimer;
    /* 0x8 */ u8 bobPattern;
    /* 0x9 */ u8 rollPattern;
};

struct CameraSwayPattern {
    /* 0x00 */ u16 duration;
    /* 0x02 */ u16 durationRand;
    /* 0x04 */ s16 phaseStep;
    /* 0x06 */ s16 pad;
    /* 0x08 */ s32 amplitude;
};

#endif

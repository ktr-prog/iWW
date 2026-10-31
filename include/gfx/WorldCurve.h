#ifndef GFX_WORLDCURVE_H
#define GFX_WORLDCURVE_H

#include "types.h"

class WorldCurve {
public:
    WorldCurve();
    ~WorldCurve();

    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0c */ s16 centerAngle;
    /* 0x10 */ s32 flatDistance;
    /* 0x14 */ s32 dropSlope;
};

#endif

#ifndef GAME_GROUNDINFOBASE_H
#define GAME_GROUNDINFOBASE_H

#include "types.h"

class GroundInfoBase {
public:
    void setWaveDir(s32 a, s32 b, s32 c);
    BOOL isBelowWaterSurface(s32 x);
    s32 getWaterSurfaceY();
    s32 getHeight(s32 flag);

    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ u8 queryPos[0xc];
    /* 0x1c */ s32 unitX;
    /* 0x20 */ s32 unitZ;
    /* 0x24 */ s32 flowDir;
    /* 0x28 */ s32 flowDirY;
    /* 0x2c */ s32 flowDirZ;
    /* 0x30 */ s32 waterKind;
    /* 0x34 */ s32 attr;
    /* 0x38 */ s32 height;
    /* 0x3c */ s32 waterSurfaceY;
};

#endif

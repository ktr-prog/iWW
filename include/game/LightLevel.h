#ifndef GAME_LIGHTLEVEL_H
#define GAME_LIGHTLEVEL_H

#include "types.h"

class LightLevel {
public:
    LightLevel();
    ~LightLevel();
    s32 getLevel();
    BOOL switchLight(BOOL on, s32 a, s32 b, u32 param);
    void update();
    BOOL switchLightAnimated(BOOL on);

    /* 0x00 */ s32 level;
    /* 0x04 */ s32 targetLevel;
    /* 0x08 */ u32 fadeStep;
    /* 0x0c */ s32 isFlickering;
    /* 0x10 */ u16 flickerIndex;
    /* 0x12 */ u16 flickerDelay;
};

#endif

#ifndef GFX_SCREENTRANSITION_H
#define GFX_SCREENTRANSITION_H

#include "types.h"

struct ScreenTransition {
    u8 state;
    u8 type;
    u8 unk_02[2];
    s32 progress;
    s32 step;
    s32 brightness;
    s32 unk_10;
};

#endif

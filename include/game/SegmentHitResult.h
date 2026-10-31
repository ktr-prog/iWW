#ifndef GAME_SEGMENTHITRESULT_H
#define GAME_SEGMENTHITRESULT_H

#include "types.h"
#include "gfx/VecFx32.h"

struct SegmentHitResult {
    /* 0x00 */ u8 attr;
    /* 0x04 */ void *callback;
    /* 0x08 */ VecFx32 hitNormal;
};

#endif

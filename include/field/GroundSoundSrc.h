#ifndef FIELD_GROUNDSOUNDSRC_H
#define FIELD_GROUNDSOUNDSRC_H

#include "types.h"
#include "gfx/VecFx32.h"

class GroundSoundSrc {
public:
    /* 0x00 */ u8 found;
    /* 0x04 */ VecFx32 pos;
    /* 0x10 */ s32 distance;
    /* 0x14 */ s32 kind;
};

#endif

#ifndef GFX_CAMERATOWNTOUR_H
#define GFX_CAMERATOWNTOUR_H

#include "types.h"
#include "gfx/VecFx32.h"

struct CameraTownTourState {
    /* 0x00 */ u16 holdTimer;
    /* 0x02 */ s16 buildingIndex;
    /* 0x04 */ VecFx32 building;
    /* 0x10 */ VecFx32 *offset;
    /* 0x14 */ s32 speed;
};

#endif

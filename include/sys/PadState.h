#ifndef SYS_PADSTATE_H
#define SYS_PADSTATE_H

#include "types.h"

struct PadState {
    /* 0x0 */ u16 cur;
    /* 0x2 */ u16 trig;
    /* 0x4 */ s16 dir;
};

extern PadState gPad;

#endif

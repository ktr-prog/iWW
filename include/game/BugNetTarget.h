#ifndef GAME_BUGNETTARGET_H
#define GAME_BUGNETTARGET_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/TouchPickSphere.h"

class BugNetTarget : public TouchPickSphere {
public:
    BugNetTarget();
    ~BugNetTarget();
    void submit(VecFx32 *a, s32 b, s32 radius, u8 d);
    /* 0x1c */ BugNetTarget *nextTarget;
    /* 0x20 */ u8 isHit;
    /* 0x24 */ s32 hitRadius;
};

#endif

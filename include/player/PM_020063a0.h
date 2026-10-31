#ifndef PLAYER_PM_020063A0_H
#define PLAYER_PM_020063A0_H

#include "types.h"
#include "player/PMRaw.h"
#include "player/Unk_02005e7c.h"

union PM_020063a0 {
    PMRaw raw;
    void (Unk_02005e7c::*fn)(s32);
};

#endif

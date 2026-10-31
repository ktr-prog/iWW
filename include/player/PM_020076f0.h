#ifndef PLAYER_PM_020076F0_H
#define PLAYER_PM_020076F0_H

#include "types.h"
#include "player/PMRaw.h"
#include "player/Unk_02007694.h"

union PM_020076f0 {
    PMRaw raw;
    void (Unk_02007694::*fn)(u32);
};

#endif

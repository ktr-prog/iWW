#ifndef GAME_UNK_02095774_ENT_H
#define GAME_UNK_02095774_ENT_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "town/TownBlockMap.h"



struct SaveTownStateView {
    /* 0x00 */ u8 pad_00[0x58];
    /* 0x58 */ u32 nativeFruit;
};

#endif

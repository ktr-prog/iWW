#ifndef PLAYER_PLAYERPICKUPARGS_H
#define PLAYER_PLAYERPICKUPARGS_H

#include "types.h"
#include "gfx/VecFx32.h"


struct PlayerNetPickUpArgs {
    /* 0x0 */ u8 commitUnit;
    /* 0x1 */ u8 item;
    /* 0x2 */ u8 itemHi;
    /* 0x3 */ s8 ftrActorIndex;
    /* 0x4 */ u8 unitX;
    /* 0x5 */ u8 unitZ;
};

struct PlayerPickUpArgs {
    /* 0x0 */ u16 item;
    /* 0x2 */ u16 pad_02;
    /* 0x4 */ s32 ftrActorIndex;
    /* 0x8 */ u8 unitX;
    /* 0x9 */ u8 unitZ;
    /* 0xa */ u8 commitUnit;
};

#endif

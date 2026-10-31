#ifndef PLAYER_PLAYERPICKUPWORK_H
#define PLAYER_PLAYERPICKUPWORK_H

#include "types.h"


struct PlayerPickUpWork {
    /* 0x0 */ u8 commitUnit;
    /* 0x1 */ u8 fanfareStep;
    /* 0x2 */ u8 unitX;
    /* 0x3 */ u8 unitZ;
    /* 0x4 */ union { s32 s; struct { u8 unk_04, unk_05, unk_06, unk_07; } b; } unk_04;
    /* 0x8 */ u8 storeStep;
    /* 0x9 */ u8 pickUnitX;
    /* 0xa */ u8 pickUnitZ;
};

#endif

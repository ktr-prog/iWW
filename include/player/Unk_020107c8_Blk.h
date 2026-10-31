#ifndef PLAYER_UNK_020107C8_BLK_H
#define PLAYER_UNK_020107C8_BLK_H

#include "types.h"

struct Unk_020107c8_Blk {
    /* 0x0 */ u32 x;
    /* 0x4 */ u32 y;
    /* 0x8 */ u32 z;
};

struct PlayerNetApproachLocals {
    /* 0x0 */ u8 scene;
    /* 0x2 */ s16 netAngle;
    /* 0x4 */ s16 curAngle;
};

struct Unk_02010a58_Blk {
    /* 0x0 */ u16 rotX;
    /* 0x2 */ s16 rotY;
};

struct Unk_02010b08_Time {
    /* 0x0 */ u32 unk_00;
    /* 0x4 */ u32 unk_04;
};

struct Unk_02010b08_Bits {
    /* 0x0 */ u16 year : 7;
    u16 month : 4;
    u16 day : 5;
};


#endif

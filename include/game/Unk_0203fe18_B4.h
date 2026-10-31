#ifndef GAME_UNK_0203FE18_B4_H
#define GAME_UNK_0203FE18_B4_H

#include "types.h"


struct Unk_0203fe18_B4Bytes {
    /* 0x00 */ u8 b0, b1, b2, b3;
};

union Unk_0203fe18_B4 {
    /* 0x00 */ u32 w;
    /* 0x00 */ Unk_0203fe18_B4Bytes b;
};

#endif

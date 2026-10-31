#ifndef PLAYER_UNK_020092C8_LOC_H
#define PLAYER_UNK_020092C8_LOC_H

#include "types.h"


struct Unk_020092c8_Date {
    union {
        struct {
            /* 0x0 */ u32 w0;
            /* 0x4 */ u32 w1;
        };
        /* 0x0 */ u8 b[8];
    };
};

struct Unk_020092c8_Bits {
    /* 0x0 */ u16 y : 7;
    /* 0x0 */ u16 m : 4;
    /* 0x0 */ u16 d : 5;
};

struct Unk_020092c8_Loc {
    /* 0x0 */ Unk_020092c8_Bits bits;
    /* 0x2 */ u16 pad;
    /* 0x4 */ Unk_020092c8_Date date;
};

#endif

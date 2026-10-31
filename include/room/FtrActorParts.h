#ifndef ROOM_FTRACTORPARTS_H
#define ROOM_FTRACTORPARTS_H

#include "types.h"
#include "sys/StackPad.h"
#include "sys/NNSFndArchive.h"
#include "gfx/VecFx32.h"
#include "gfx/NNSG3dResAnmCommon.h"


struct Unk_ov004_02206520_Ent {
    /* 0x0 */ s32 x, y;
    Unk_ov004_02206520_Ent() {
        x = 0;
        y = 0;
    }
};

struct Unk_ov004_02205b14_Obj {
    /* 0x00 */ u8 pad[0x18];
    /* 0x18 */ u8 numMat;
};

struct Unk_ov004_0220a648_Bits {
    u32 lo : 12;
    u32 mid : 16;
    u32 hi : 4;
};


#endif

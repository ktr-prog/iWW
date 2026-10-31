#ifndef PLAYER_PLAYERACTIONWORK_H
#define PLAYER_PLAYERACTIONWORK_H

#include "types.h"

struct PlayerActionWork {
    union {
        struct { s16 unk_00; u8 unk_02, unk_03, unk_04, unk_05, unk_06; };
        struct { s32 w0; s32 w4; s32 w8; s32 wc; s32 w10; s32 w14; };
        struct { u16 h0, h2; u16 h4; u8 b6; };
        struct { u8 c0, c1; u8 pad_02[2]; u8 b4, b5; };
    };
    void set_h2(s16 v) { h2 = v; }
};

#endif

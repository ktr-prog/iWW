#ifndef PLAYER_PLAYERACT76ARGS_H
#define PLAYER_PLAYERACT76ARGS_H

#include "types.h"


struct PlayerAct76Args {
    /* 0x0 */ u8 kind;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ u8 unk_02;
    /* 0x3 */ u8 pad_03[0xd];
    void set(u8 a, u8 b, u8 c) { kind = a; unk_01 = b; unk_02 = c; }
};

#endif

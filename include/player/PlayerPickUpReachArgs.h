#ifndef PLAYER_PLAYERPICKUPREACHARGS_H
#define PLAYER_PLAYERPICKUPREACHARGS_H

#include "types.h"


struct Unk_0200b750_Pair {
    /* 0x0 */ u32 unitX;
    /* 0x4 */ u32 unitZ;
    Unk_0200b750_Pair(u32 a, u32 b) : unitX(a), unitZ(b) {}
    Unk_0200b750_Pair(const Unk_0200b750_Pair &o) : unitX(o.unitX), unitZ(o.unitZ) {}
};

struct PlayerNetPickUpReachArgs {
    /* 0x0 */ u8 unk_00;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ u8 pad_02[2];
    /* 0x4 */ s32 ftrActorIndex;
    void readPickUpReachNet(Unk_0200b750_Pair *pr, s32 *out);
    void writePickUpReachNet(Unk_0200b750_Pair pr, s32 v);
    void readEmotionNet(u8 *a, u8 *b);
    void writeEmotionNet(u8 a, u8 b);
};

struct PlayerPickUpReachArgs {
    /* 0x0 */ u32 ftrActorIndex;
    /* 0x4 */ u8 unitX;
    /* 0x5 */ u8 unitZ;
    void setPickUpReachArgs(Unk_0200b750_Pair pr, u32 v);
};

#endif

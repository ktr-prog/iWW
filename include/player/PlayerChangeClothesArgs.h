#ifndef PLAYER_PLAYERCHANGECLOTHESARGS_H
#define PLAYER_PLAYERCHANGECLOTHESARGS_H

#include "types.h"


struct PlayerChangeClothesArgs {
    /* 0x0 */ u16 unk_00;
    /* 0x4 */ s32 changeKind;
    /* 0x8 */ s32 wearStyle;
    /* 0xc */ s32 unk_0c;
    void setChangeClothesArgs(u16 a, s32 b, s32 c);
    void setAct05Args(u16 a);
    void setSkidTurnArgs(u16 a);
};

struct PlayerChangeClothesWork {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ s16 skidEffectAngle;
    /* 0x04 */ s32 changeKind;
    /* 0x08 */ s32 wearStyle;
    /* 0x0c */ u8 isApplied;
    /* 0x0e */ s16 spinStep;
    /* 0x10 */ u8 unk_10[0x1c - 0x10];
    void initChangeClothes(u16 a, s32 b, s32 c, s16 d);
    void initSkidTurn(s16 a);
};

struct PlayerNetChangeClothesArgs {
    /* 0x0 */ u16 item;
    /* 0x2 */ u8 changeKind;
    /* 0x3 */ u8 wearStyle;
    void readChangeClothesNet(u16 *a, u8 *b, u8 *c);
    void writeChangeClothesNet(u16 a, u8 b, u8 c);
};

#endif

#ifndef PLAYER_UNK_0200B908_OBJ_H
#define PLAYER_UNK_0200B908_OBJ_H

#include "types.h"


#ifdef HOST64
#include "npc/NpcEmotionFx.h"
struct Unk_0200b908_Obj {
    u32 animId;
    u8 pad_04[sizeof(NpcEmotionPhase) - 4];
    volatile u32 nextAnimId;
    u8 pad_10[sizeof(NpcEmotionPhase) - 4];
    u8 animPlayMode;
};
#else
struct Unk_0200b908_Obj {
    /* 0x00 */ u32 animId;
    /* 0x04 */ u8 pad_04[8];
    /* 0x0c */ volatile u32 nextAnimId;
    /* 0x10 */ u8 pad_10[8];
    /* 0x18 */ u8 animPlayMode;
};
#endif

#endif

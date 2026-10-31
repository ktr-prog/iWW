#ifndef NPC_VILLAGERSTATE_H
#define NPC_VILLAGERSTATE_H

#include "types.h"
#include "npc/ErrandRecord.h"


struct TalkRepeat {
    /* 0x0 */ u16 window;
    /* 0x2 */ u8 grace;
    /* 0x3 */ u8 count;
};

struct VillagerState {
    VillagerState();
    ~VillagerState();

    /* 0x00 */ u8 role;
    /* 0x01 */ u8 presence;
    /* 0x04 */ ErrandRecord errand;
    /* 0x10 */ u32 trendScores[2];
    /* 0x18 */ u8 mood;
    /* 0x19 */ u8 unk_19;
    /* 0x1a */ u16 moodTimer;
    /* 0x1c */ u8 activity;
    /* 0x1d */ u8 flags;
    /* 0x1e */ u8 talkUrge;
    /* 0x20 */ s32 roomScore;
    /* 0x24 */ u16 roomBonusFlags;
    /* 0x26 */ u16 heldItem;
    /* 0x28 */ TalkRepeat talkRepeat;
};

#endif

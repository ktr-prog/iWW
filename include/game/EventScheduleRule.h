#ifndef GAME_EVENTSCHEDULERULE_H
#define GAME_EVENTSCHEDULERULE_H

#include "types.h"


struct Unk_0203f554_Sub {
    u32 flags;
    s32 off;
    u32 hour;
};

struct EventScheduleRule {
    u16 id;
    u16 kind;
    Unk_0203f554_Sub a;
    Unk_0203f554_Sub b;
};

union Unk_0203f218_Ver {
    /* 0x00 */ u32 word;
    /* 0x00 */ u8 b[4];
};

#endif

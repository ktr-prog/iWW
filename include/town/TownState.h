#ifndef TOWN_TOWNSTATE_H
#define TOWN_TOWNSTATE_H

#include "types.h"
#include "sys/ClockDate.h"

struct TownState {
    /* 0x00 */ ClockDate lastUpdate;
    /* 0x04 */ s32 nativeFruit;
    /* 0x08 */ u8 nextWeekDay;
    /* 0x09 */ u8 nextWeekMonth;
    /* 0x0a */ u8 nextWeekYear;
    /* 0x0b */ u8 unk_0b;
    /* 0x0c */ u8 unk_0c[10];
    /* 0x16 */ u8 unk_16[11];
    /* 0x21 */ s8 perfectStreak;
    /* 0x22 */ u8 unk_22;
    /* 0x23 */ u8 pad_23;
    /* 0x24 */ u8 events[0x30];
    /* 0x54 */ u8 eventUpdateDay;
    /* 0x55 */ u8 eventUpdateMonth;
    /* 0x56 */ u8 eventUpdateYear;
    /* 0x57 */ u8 unk_57;
    /* 0x58 */ ClockDate playerDates[4];
    /* 0x68 */ u8 unk_68;
    /* 0x69 */ u8 unk_69;
    /* 0x6a */ u8 unk_6a;
    /* 0x6b */ u8 unk_6b;
};

static_assert(sizeof(TownState) == 0x6c, "TownState: SaveData::townState");

#endif

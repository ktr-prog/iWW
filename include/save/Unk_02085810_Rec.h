#ifndef SAVE_UNK_02085810_REC_H
#define SAVE_UNK_02085810_REC_H

#include "types.h"
#include "npc/VillagerId.h"


struct Unk_02085810_Base {
    /* 0x00 */ u16 townId;
    /* 0x02 */ u8 townName[8];
    /* 0x0a */ u16 playerId;
    /* 0x0c */ u8 playerName[8];
    /* 0x14 */ s8 gender;
    /* 0x15 */ u8 unk_15;
};

#endif

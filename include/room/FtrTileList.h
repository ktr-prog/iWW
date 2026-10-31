#ifndef ROOM_FTRTILELIST_H
#define ROOM_FTRTILELIST_H

#include "types.h"
#include "room/FtrActorParts.h"

struct FtrTileList {
    /* 0x00 */ u32 count;
    /* 0x04 */ Unk_ov004_02206520_Ent tiles[4];
    Unk_ov004_02206520_Ent *get(s32 i);
    u32 getCount();
    BOOL add(u32 a, u32 b);
    void release();
    FtrTileList();
};

#endif

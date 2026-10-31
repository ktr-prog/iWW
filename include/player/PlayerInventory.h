#ifndef PLAYER_PLAYERINVENTORY_H
#define PLAYER_PLAYERINVENTORY_H

#include "types.h"

class PlayerInventory {
public:
    /* 0x000 */ u8 letters[0x988];
    /* 0x988 */ u8 letterDefaults[0x52];
    /* 0x9da */ u16 pockets[15];
    /* 0x9f8 */ u32 wallet;
    /* 0x9fc */ u32 pocketFlags;

    s32 getTotalBells(BOOL flag);
    s32 getBellsSpace(s32 n);
    s32 getPocketBells();
    void *getUnk988();
    void *getEmptyLetter();
    s32 findEmptyLetter();
    void *getLetter(s32 idx);
    BOOL isPocketFlagsClear(s32 idx);
    u32 getPocketFlags(s32 idx);
    s32 findEmptyPocket();
    void setPocketFlags(s32 idx, u32 val);
    BOOL setPocket(u16 *p, s32 idx, u32 val);
    u16 *getPocket(s32 idx);
    void clear();
};

#endif

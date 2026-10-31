#ifndef PLAYER_FOREIGNVILLAGERRECORD_H
#define PLAYER_FOREIGNVILLAGERRECORD_H

#include "types.h"
#include "save/TownId.h"
#include "npc/VillagerId.h"

class ForeignVillagerRecord {
public:
    ForeignVillagerRecord();
    ~ForeignVillagerRecord();
    /* 0x00 */ TownId town;
    /* 0x0a */ VillagerId villager;
    /* 0x16 */ u16 present;
    /* 0x18 */ s8 friendship;

    BOOL offer(void *a1, s32 a2, void *a3);
    void set(void *a1, s32 a2, void *a3, u16 *p);
    BOOL isSet();
    void clear();
};

#endif

#ifndef ROOM_FTRSTACKEDSET_H
#define ROOM_FTRSTACKEDSET_H

#include "types.h"

struct FtrTileList;
class FtrActor;

struct FtrStackedSet {
    FtrStackedSet();
    FtrStackedSet(FtrTileList *l, s32 flag);
    BOOL add(FtrActor *o);
    FtrActor *get(u32 i);
    u32 getCount();
    void collect(FtrTileList *l, s32 flag);
    void clear();

    /* 0x00 */ u32 count;
    /* 0x04 */ FtrActor *actors[4];
};

#endif

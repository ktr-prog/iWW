#ifndef ROOM_FTRACTORTABLE_H
#define ROOM_FTRACTORTABLE_H

#include "types.h"

class FtrActor;

class FtrActorTable {
public:
    /* 0x00 */ void *actors[0x1c];

    FtrActorTable();
    ~FtrActorTable();
    FtrActor *get(u32 idx);
    s32 indexOf(void *v);
    s32 countFree();
    s32 countUsed();
    s32 remove(void *v);
    s32 add(void *v);
    void clear();
};

#endif

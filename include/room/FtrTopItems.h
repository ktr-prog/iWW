#ifndef ROOM_FTRTOPITEMS_H
#define ROOM_FTRTOPITEMS_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "room/FtrActorParts.h"
#include "room/FtrTopItem.h"

class FtrActor;

struct FtrTopItems {
    FtrTopItems();
    ~FtrTopItems();
    void dropAll(FtrActor *o);
    BOOL pickUpAll(FtrActor *o);
    BOOL canPickUp(FtrActor *o);
    BOOL add(u16 *id, VecFx32 *pos);
    void drawAll(FtrActor *o);
    FtrTopItem *get(u32 i);
    void clearAll();
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ FtrTopItem items[4];
};

#endif

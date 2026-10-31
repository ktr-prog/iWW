#ifndef ROOM_FTRTOPITEM_H
#define ROOM_FTRTOPITEM_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "room/FtrActorParts.h"

class FtrActor;

struct FtrTopItem {
    FtrTopItem();
    ~FtrTopItem();
    BOOL set(u16 *id, VecFx32 *pos);
    u16 *getItem();
    VecFx32 *getPos();
    void clear();
    BOOL isSet();
    void draw(FtrActor *o);
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 item;
    /* 0x04 */ VecFx32 relPos;
};

#endif

#ifndef ROOM_FTRSWITCH_H
#define ROOM_FTRSWITCH_H

#include "types.h"

class FtrActor;

struct FtrSwitch {
    ~FtrSwitch();
    void set(u32 v, s32 flag);
    void toggle(s32 flag);
    BOOL isChanging();
    u8 isOn();
    void saveToMap(FtrActor *o);
    void commit(FtrActor *o);
    void loadFromMap(FtrActor *o);
    void clear();

    /* 0x00 */ u8 cur;
    /* 0x01 */ u8 next;
};

#endif

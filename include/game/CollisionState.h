#ifndef GAME_COLLISIONSTATE_H
#define GAME_COLLISIONSTATE_H

#include "types.h"

struct CollisionContacts {
    /* 0x00 */ s16 angles[2];
    /* 0x04 */ u8 numContacts;
    /* 0x05 */ u8 unk_05[3];
    /* 0x08 */ s32 attrs[2];
    /* 0x10 */ s32 kinds[2];

    CollisionContacts();
    ~CollisionContacts();
    BOOL addContact(s32 a, s32 b, s32 c);
    void clear();
};

struct CollisionState {
    /* 0x00 */ u32 prevFlags;
    /* 0x04 */ volatile u32 flags;
    /* 0x08 */ s32 groundAttr;
    /* 0x0c */ CollisionContacts contacts;
    /* 0x24 */ s32 moveDelta, moveDeltaY, moveDeltaZ;

    CollisionState();
    ~CollisionState();
    void reset();
    void beginStep();
    void updateWallFlags(s32 v);
};

#endif

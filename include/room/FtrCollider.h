#ifndef ROOM_FTRCOLLIDER_H
#define ROOM_FTRCOLLIDER_H

#include "types.h"
#include "game/BoxCollider.h"

class FtrActor;

struct FtrCollider : BoxCollider {
    /* 0x9c */ FtrActor *owner;
    FtrCollider();
    ~FtrCollider();
    void onEdgeContact(CollisionEdge *a, Actor *b, s32 c);
    void slideOwnerForWideFtr(Actor *b);
    void clearOwner();
    void setOwner(FtrActor *p);
};

#endif

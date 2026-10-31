#ifndef ACTOR_ACTORFOLLOWCOLLIDER_H
#define ACTOR_ACTORFOLLOWCOLLIDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorCollider.h"

class Actor;

class ActorFollowCollider : public ActorCollider {
public:
    ActorFollowCollider();
    ~ActorFollowCollider();
    virtual VecFx32 *getPos();
    virtual u32 getOwnerId();
    void setupForActor(void *p, s32 a, s32 b, u32 c, u32 d, u32 e, u8 f, s32 g);

    /* 0x40 */ Actor *ownerActor;
};

#endif

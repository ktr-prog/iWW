#ifndef ACTOR_ACTORPLACEDCOLLIDER_H
#define ACTOR_ACTORPLACEDCOLLIDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorFollowCollider.h"

class ActorPlacedCollider : public ActorFollowCollider {
public:
    ActorPlacedCollider();
    ~ActorPlacedCollider();
    virtual VecFx32 *getPos();
    virtual u32 getOwnerId();
    void setupForActorAt(void *p, VecFx32 *v, s32 a, s32 b, u32 c, u32 d, u32 e, u8 f, s32 g);
    /* 0x44 */ VecFx32 position;
};

#endif

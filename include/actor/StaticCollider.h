#ifndef ACTOR_STATICCOLLIDER_H
#define ACTOR_STATICCOLLIDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorCollider.h"

class StaticCollider : public ActorCollider {
public:
    StaticCollider();
    ~StaticCollider();
    virtual VecFx32 *getPos();
    virtual u32 getOwnerId();
    void setupAtPos(VecFx32 *v, s32 a, s32 b, u32 c, u32 d, u32 e, u8 f, s32 g);

    /* 0x40 */ VecFx32 position;
};

#endif

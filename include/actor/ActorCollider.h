#ifndef ACTOR_ACTORCOLLIDER_H
#define ACTOR_ACTORCOLLIDER_H

#include "types.h"
#include "gfx/VecFx32.h"

class Actor;

class ActorCollider {
public:
    ActorCollider();
    ~ActorCollider();
    virtual VecFx32 *getPos() = 0;
    virtual u32 getOwnerId() = 0;
    virtual void onCollide(u32 a, u32 b, u32 c);
    void submit();
    void resetHit();
    BOOL isHitByGroup(u32 mask);
    BOOL canCollideWith(ActorCollider *o);
    void setup(s32 a, s32 b, s32 c, s32 d, u32 e, u8 f, s32 g);
    Actor *getHitActor();
    BOOL isPushedFromAngle(s32 a);

    /* 0x04 */ s32 radius;
    /* 0x08 */ s32 height;
    /* 0x0c */ u8 targetKind;
    /* 0x0d */ u8 targetIndex;
    /* 0x0e */ u8 hitTargetKind;
    /* 0x0f */ u8 hitTargetIndex;
    /* 0x10 */ s32 pushX;
    /* 0x14 */ s32 pushY;
    /* 0x18 */ s32 pushZ;
    /* 0x1c */ u32 groups;
    /* 0x20 */ u32 collideMask;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u32 hitGroups;
    /* 0x2c */ u32 hitOwnerId;
    /* 0x30 */ s32 hitDepth;
    /* 0x34 */ s32 weight;
    /* 0x38 */ ActorCollider *next;
    /* 0x3c */ u8 isHit;
};

#endif

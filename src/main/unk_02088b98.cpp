#include "types.h"
#include "gfx/VecFx32.h"


#include "actor/ActorCollider.h"
#include "actor/ActorFollowCollider.h"
#include "actor/ActorPlacedCollider.h"
#include "actor/StaticCollider.h"

#include "actor/ActorCollider.h"
#include "actor/Actor.h"
#include "gfx/SpriteAnim.h"
#include "proto/main/unk_02088b98.h"

#include "game/BugNetTarget.h"
BugNetTarget *data_021ce63c;


extern "C" {
s16 Math_Atan2(s32 a, s32 b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
void Vec_Sub(VecFx32 *out, VecFx32 *a, VecFx32 *b);
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 Vec_MagXZ(VecFx32 *v);
}

ActorCollider *gActorColliderList;

void SpriteAnim::update() {
    if (playOnce == 0) {
        frameTime = frameTime + speed;
        s32 f = frameTime >> 12;
        if (f >= seq->frames[frameIndex].duration) {
            frameTime = 0;
            s32 n = seq->frameCount;
            frameIndex = frameIndex + 1;
            if (frameIndex >= n) {
                frameIndex = 0;
            }
        }
    } else {
        frameTime = frameTime + speed;
        SpriteAnimSeq *t = seq;
        s32 f = frameTime >> 12;
        if (f >= t->frames[frameIndex].duration) {
            s32 n = t->frameCount;
            frameIndex = frameIndex + 1;
            if (frameIndex < n) {
                frameTime = 0;
            } else {
                frameIndex = n - 1;
            }
        }
    }
}

u32 StaticCollider::getOwnerId() { return FALSE; }

VecFx32 *StaticCollider::getPos() { return &position; }

u32 ActorPlacedCollider::getOwnerId() { return ActorFollowCollider::getOwnerId(); }

VecFx32 *ActorPlacedCollider::getPos() { return &position; }

extern "C" void ActorCollider_InitList(void) { ActorCollider_ClearList(); }

extern "C" void ActorCollider_ClearList(void) { gActorColliderList = 0; }

ActorCollider::ActorCollider() {
    resetHit();
}

ActorCollider::~ActorCollider() {}

void ActorCollider::onCollide(u32 a, u32 b, u32 c) {}

BOOL ActorCollider::isPushedFromAngle(s32 a) {
    if (isHit != 0) {
        s32 t = Math_Atan2(pushX, pushZ);
        if (Math_AngleDiffAbs(t, (s16)(a + 0x8000)) <= 0x2000) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

Actor *ActorCollider::getHitActor() {
    if (hitOwnerId != 0) {
        return (Actor *)Actor::findById(hitOwnerId);
    }
    return 0;
}

void ActorCollider::setup(s32 a, s32 b, s32 c, s32 d, u32 e, u8 f, s32 g) {
    radius = a;
    height = b;
    groups = c;
    collideMask = d;
    targetKind = e;
    targetIndex = f;
    weight = g;
}

void ActorCollider::resetHit() {
    next = 0;
    pushX = 0;
    pushY = 0;
    pushZ = 0;
    isHit = 0;
    hitOwnerId = 0;
    hitGroups = 0;
    hitTargetKind = 0;
    hitTargetIndex = 0xff;
}

void ActorCollider::submit() {
    resetHit();
    next = gActorColliderList;
    gActorColliderList = this;
}

BOOL ActorCollider::canCollideWith(ActorCollider *o) {
    BOOL r;
    if ((groups & o->collideMask) && (collideMask & o->groups)) {
        r = TRUE;
    } else {
        r = FALSE;
    }
    if (r) {
        u32 a = getOwnerId();
        if (a != 0) {
            if (a == o->getOwnerId()) {
                return FALSE;
            }
        }
        if (this != o) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" void ActorCollider_ResolveAll() {
    ActorCollider *o;
    VecFx32 *cv;
    VecFx32 d;
    s32 len;
    s32 pen;
    s32 t;
    s32 sumM, w1, k, w0;
    for (o = gActorColliderList; o; o = o->next) {
        if (o->groups & 1) {
            o->hitDepth = -0x1000;
        }
    }
    while (gActorColliderList) {
        cv = gActorColliderList->getPos();
        for (o = gActorColliderList->next; o; o = o->next) {
            if (!gActorColliderList->canCollideWith(o)) {
                continue;
            }
            Vec_Sub(&d, o->getPos(), cv);
            if (d.y < 0) {
                t = o->height + d.y;
            } else {
                t = gActorColliderList->height - d.y;
            }
            if (t <= 0) {
                continue;
            }
            len = Vec_MagXZ(&d);
            if (len == 0) {
                d.x = 0x1000;
                len = 0x1000;
            }
            pen = gActorColliderList->radius + o->radius - len;
            if (pen <= 0) {
                continue;
            }
            o->isHit = 1;
            gActorColliderList->isHit = o->isHit;
            if (gActorColliderList->groups & 1) {
                if (pen >= gActorColliderList->hitDepth) {
                    gActorColliderList->hitDepth = pen;
                    gActorColliderList->hitGroups = o->groups;
                    gActorColliderList->hitOwnerId = o->getOwnerId();
                    gActorColliderList->hitTargetKind = o->targetKind;
                    gActorColliderList->hitTargetIndex = o->targetIndex;
                }
            } else {
                gActorColliderList->hitGroups = o->groups;
                gActorColliderList->hitOwnerId = o->getOwnerId();
                gActorColliderList->hitTargetKind = o->targetKind;
                gActorColliderList->hitTargetIndex = o->targetIndex;
            }
            if (o->groups & 1) {
                if (pen >= o->hitDepth) {
                    o->hitGroups = gActorColliderList->groups;
                    o->hitOwnerId = gActorColliderList->getOwnerId();
                    o->hitTargetKind = gActorColliderList->targetKind;
                    o->hitTargetIndex = gActorColliderList->targetIndex;
                }
            } else {
                o->hitGroups = gActorColliderList->groups;
                o->hitOwnerId = gActorColliderList->getOwnerId();
                o->hitTargetKind = gActorColliderList->targetKind;
                o->hitTargetIndex = gActorColliderList->targetIndex;
            }
            gActorColliderList->onCollide(o->targetKind, o->targetIndex, o->groups);
            o->onCollide(gActorColliderList->targetKind, gActorColliderList->targetIndex, gActorColliderList->groups);
            if (gActorColliderList->groups & 1) {
                continue;
            }
            if (o->groups & 1) {
                continue;
            }
            if (gActorColliderList->groups & 2) {
                if (o->groups & 2) {
                    continue;
                }
            }
            if (gActorColliderList->groups & 2) {
                o->pushY = 0;
                pen = FX_Div(pen, len);
                o->pushX += func_01ffcb0c(d.x, pen);
                o->pushZ += func_01ffcb0c(d.z, pen);
            } else if (o->groups & 2) {
                gActorColliderList->pushY = 0;
                pen = FX_Div(pen, len);
                gActorColliderList->pushX -= func_01ffcb0c(d.x, pen);
                gActorColliderList->pushZ -= func_01ffcb0c(d.z, pen);
            } else {
                w0 = gActorColliderList->weight;
                w1 = o->weight;
                k = FX_Div(pen, len) >> 1;
                sumM = w0 + w1;
                s32 f1 = func_01ffcb0c(k, FX_Div(w1, sumM));
                pen = func_01ffcb0c(k, FX_Div(w0, sumM));
                o->pushY = 0;
                gActorColliderList->pushY = 0;
                gActorColliderList->pushX -= func_01ffcb0c(d.x, f1);
                gActorColliderList->pushZ -= func_01ffcb0c(d.z, f1);
                o->pushX += func_01ffcb0c(d.x, pen);
                o->pushZ += func_01ffcb0c(d.z, pen);
            }
        }
        gActorColliderList = gActorColliderList->next;
    }
}

BOOL ActorCollider::isHitByGroup(u32 mask) {
    if (isHit) {
        if (hitGroups & mask) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

ActorFollowCollider::ActorFollowCollider() {
    ownerActor = 0;
}

ActorFollowCollider::~ActorFollowCollider() {
}

VecFx32 *ActorFollowCollider::getPos() { return &ownerActor->position; }

u32 ActorFollowCollider::getOwnerId() { return ownerActor->id; }

void ActorFollowCollider::setupForActor(void *p, s32 a, s32 b, u32 c, u32 d, u32 e, u8 f, s32 g) {
    ownerActor = static_cast<Actor *>(p);
    setup(a, b, c, d, e, f, g);
}

void StaticCollider::setupAtPos(VecFx32 *v, s32 a, s32 b, u32 c, u32 d, u32 e, u8 f, s32 g) {
    position = *v;
    setup(a, b, c, d, e, f, g);
}

ActorPlacedCollider::ActorPlacedCollider() {
}

ActorPlacedCollider::~ActorPlacedCollider() {
}

void ActorPlacedCollider::setupForActorAt(void *p, VecFx32 *v, s32 a, s32 b, u32 c, u32 d, u32 e, u8 f, s32 g) {
    setupForActor(p, a, b, c, d, e, f, g);
    position = *v;
}

StaticCollider::StaticCollider() {
}

StaticCollider::~StaticCollider() {
}


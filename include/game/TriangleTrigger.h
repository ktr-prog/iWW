#ifndef GAME_TRIANGLETRIGGER_H
#define GAME_TRIANGLETRIGGER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/CollisionTriangleX.h"

class Actor;

struct TriangleTrigger : CollisionTriangleX {
    /* 0x38 */ TriangleTrigger *next;
    /* 0x3c */ VecFx32 center;
    /* 0x48 */ s32 radiusSq;

    TriangleTrigger();
    virtual void onActorNear(VecFx32 *a, Actor *o, s32 off) = 0;
    void setupTrigger(VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 d);
    VecFx32 *getCenter();
    void resetTrigger();
};

#endif

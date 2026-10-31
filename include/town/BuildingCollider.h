#ifndef TOWN_BUILDINGCOLLIDER_H
#define TOWN_BUILDINGCOLLIDER_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/TriangleTrigger.h"

class BuildingActor;
class Actor;

class BuildingCollider : public TriangleTrigger {
public:
    BuildingCollider();
    virtual void onActorNear(VecFx32 *a, Actor *o, s32 off);
    BOOL isPlayerAtDoor(VecFx32 *v, s32 off, Actor *o);
    static void *operator new(size_t, void *p) { return p; }

    /* 0x4c */ BuildingActor *building;
    /* 0x50 */ s32 entranceType;
};

#endif

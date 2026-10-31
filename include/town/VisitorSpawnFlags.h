#ifndef TOWN_VISITORSPAWNFLAGS_H
#define TOWN_VISITORSPAWNFLAGS_H

#include "types.h"
#include "gfx/VecFx32.h"

class VisitorSpawnFlags {
public:
    void setVisitorSpawned();
    void clearVisitorSpawned();
    BOOL isVisitorSpawned();
    void rollGulliverSpot();
    void clear();
    void destruct();
    void construct();
    void getGulliverSpawn(VecFx32 *v, u16 *out, VecFx32 *p);

    u8 visitorSpawned : 1;
    u8 gulliverSpotRolled : 1;
    u8 gulliverSpot : 2;
    u8 gulliverFacing : 2;
};

#endif

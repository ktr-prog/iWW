#ifndef ROOM_FTRACTORGRID_H
#define ROOM_FTRACTORGRID_H

#include "types.h"
#include "gfx/VecFx32.h"

class FtrActor;

class FtrActorGrid {
public:
    u8 cells[2][16][16];
    FtrActorGrid();
    ~FtrActorGrid();
    FtrActor *getActorAtPos(VecFx32 *p, s32 layer);
    FtrActor *getActor(s32 x, s32 y, s32 layer);
    s32 getIndex(s32 x, s32 y, s32 layer);
    BOOL clearCell(FtrActor *actor, s32 x, s32 y, u8 layer);
    BOOL setCell(FtrActor *actor, s32 x, s32 y, u8 layer);
    void clear();
};

#endif

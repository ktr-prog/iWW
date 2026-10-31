#ifndef TOWN_PETEFALLSTATE_H
#define TOWN_PETEFALLSTATE_H

#include "types.h"
#include "gfx/VecFx32.h"

class PeteFallState {
public:
    BOOL pickFallPos(VecFx32 *px, s32 flip);
    s16 getFacing();
    void setVisitorActive();
    void clearVisitorActive();
    BOOL isVisitorActive();
    void unmarkFallPos();
    void markFallPos();
    BOOL hasFallPos();
    void getPos(VecFx32 *out);
    void setPos(VecFx32 *v);
    void clear();
    void destruct();
    void construct();

    s32 fallPosX;
    s32 fallPosZ;
    u8 fallPosValid : 1;
    u8 visitorActive : 1;
    u8 facing : 2;
};

#endif

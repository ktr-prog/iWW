#ifndef TOWN_KATIEVISITSTATE_H
#define TOWN_KATIEVISITSTATE_H

#include "types.h"
#include "gfx/VecFx32.h"

class KatieVisitState {
public:
    void clearFollowing();
    void setFollowing();
    BOOL isFollowing();
    void getPos(VecFx32 *out);
    void setPos(VecFx32 *v);
    void pickKatiePos();
    void clear();
    void destruct();
    void construct();

    s32 posX;
    s32 posZ;
    u8 following;
};

#endif

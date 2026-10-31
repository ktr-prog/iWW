#ifndef TOWN_TOWNTRAVELSTATE_H
#define TOWN_TOWNTRAVELSTATE_H

#include "types.h"

class TownTravelState {
public:
    s16 getAngle();
    void setAngle(s32 v);
    u8 getMode();
    void setMode(u32 v);
    void clearMode();
    void destruct();
    void construct();

    s16 angle;
    u8 mode;
};

#endif

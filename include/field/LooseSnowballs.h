#ifndef FIELD_LOOSESNOWBALLS_H
#define FIELD_LOOSESNOWBALLS_H

#include "types.h"

class LooseSnowball {
public:
    LooseSnowball();
    ~LooseSnowball();

    /* 0x0 */ s32 posX;
    /* 0x4 */ s32 posY;
    /* 0x8 */ s32 posZ;
    /* 0xc */ s32 radius;
};

class LooseSnowballs {
public:
    ~LooseSnowballs();
    void reset();

    LooseSnowball items[2];
};

#endif

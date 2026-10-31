#ifndef TOWN_TOWNACRECELL_H
#define TOWN_TOWNACRECELL_H

#include "types.h"

class TownAcreCell {
public:
    TownAcreCell();
    ~TownAcreCell();
    BOOL setType(s32 v);
    void setAcreId(s32 v);
    s32 getType();
    s32 getAcreId();

    /* 0x00 */ s32 type;
    /* 0x04 */ s32 acreId;
};

#endif

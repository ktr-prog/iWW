#ifndef TOWN_MAPBLOCKACRE_H
#define TOWN_MAPBLOCKACRE_H

#include "types.h"

class MapBlockAcre {
public:
    s32 hasPond();
    u32 getAcreId();
    void setAcreId(u32 v);
    u8 *getUnk04();
    u32 acreId;
};

#endif

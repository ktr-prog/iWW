#ifndef TOWN_ROOMBLOCKMAP_H
#define TOWN_ROOMBLOCKMAP_H

#include "types.h"
#include "town/BlockMap.h"

struct RoomBlockMap : BlockMap {
    u16 *itemGrid;
};

#endif

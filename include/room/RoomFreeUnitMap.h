#ifndef ROOM_ROOMFREEUNITMAP_H
#define ROOM_ROOMFREEUNITMAP_H

#include "types.h"

struct RoomFreeUnitMap {
    /* 0x00 */ u16 rows[16];
    RoomFreeUnitMap();
    ~RoomFreeUnitMap();
};

#endif

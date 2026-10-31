#ifndef ROOM_ROOMOBJTEXAUTO_H
#define ROOM_ROOMOBJTEXAUTO_H

#include "types.h"
#include "room/RoomObjTex.h"
#include "host_shared_calls.h"

struct RoomObjTexAuto : public RoomObjTexHandle {
    inline RoomObjTexAuto() { Shared_RoomObjTex_Construct(this); }
    inline ~RoomObjTexAuto() { RoomObjTex_Destruct(this); }
};

#endif

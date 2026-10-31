#ifndef ROOM_ROOMOBJTEX_H
#define ROOM_ROOMOBJTEX_H

#include "room/RoomObjRes.h"

struct RoomObjTexHandle {
    inline void RoomObjTex_Reset() { ::RoomObjTex_Reset(this); }
    inline void RoomObjTex_Load(const char *s) { ::RoomObjTex_Load(this, s); }
    inline void *RoomObjTex_Get() { return ::RoomObjTex_Get(this); }

    /* 0x0 */ void *texture;
};

class RoomObjTex : public RoomObjTexHandle {
public:
    inline RoomObjTex() { RoomObjTex_Construct(this); }

    /* 0x4 */ u8 syncState;
};

#endif

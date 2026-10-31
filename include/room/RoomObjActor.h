#ifndef ROOM_ROOMOBJACTOR_H
#define ROOM_ROOMOBJACTOR_H

#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"


class RoomObjActor : public Character {
public:
    RoomObjActor();
    virtual ~RoomObjActor();
    virtual BOOL preCreate();
    virtual BOOL preDelete();
    virtual BOOL preExecute();
    virtual BOOL postExecute(u32 a);
    virtual BOOL changeSyncState(u32 v);
    virtual void getSoundPos(VecFx32 *out);

    void setSyncSlot(u32 v);
    s32 storeSyncState(u8 v);
    s32 getSyncState();
    void releaseResources();
    void loadResourcesByName(char *name);
    void loadResources(char *a, char *b);

    /* 0xea */ u8 syncSlot;
    /* 0xeb */ u8 pad_eb;
    /* 0xec */ AnimModel model;
    /* 0x1a4 */ RoomObjRes res;
    /* 0x248 */ RoomObjTex tex;
    /* 0x250 */ RoomObjSe se;
};

#endif

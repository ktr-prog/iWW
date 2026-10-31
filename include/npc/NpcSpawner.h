#ifndef NPC_NPCSPAWNER_H
#define NPC_NPCSPAWNER_H

#include "types.h"
#include "sys/ProcBase.h"
#include "room/RoomFreeUnitMap.h"

struct VisitorSpawnEntry;

class NpcSpawner : public GameProc {
public:
    NpcSpawner() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();

    BOOL pickVisitor();
    u16 *spawnScheduledVisitor(VisitorSpawnEntry *tbl, s32 n);
    void setVisitorOverlay(u32 *p);
    void clearVisitorOverlay();
    void releaseVisitorOverlay();

    /* 0x50 */ RoomFreeUnitMap freeUnitMap;
    /* 0x70 */ u8 visitorOverlayLoaded;
    /* 0x74 */ u32 visitorOverlayId;
};

#endif

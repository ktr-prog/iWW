#include "types.h"
#include "net/CommManager.h"
#include "game/NibblePair.h"
#include "room/Unk_0209c41c_Actor.h"
#include "room/RoomObjActor.h"



extern "C" {
extern CommManager *gCommManager;
extern u8 gFieldSceneKind;

u8 sRoomObjSyncStates[3];
}



extern "C" BOOL RoomObjSync_ChangeState(RoomObjActor *self, u8 v) {
    BOOL is1;
    if (gFieldSceneKind == 1) is1 = TRUE;
    else is1 = FALSE;
    if (is1) {
        if (self->changeSyncState(v)) {
            u8 idx = self->syncSlot;
            if (idx < 3) {
                if (gCommManager->isOnline()) {
                    NibblePair pk;
                    pk.lo = idx;
                    pk.hi = v;
                    CommManager *g = gCommManager;
                    g->beginRecord();
                    g->writeRecord((u8 *)&pk, 1);
                    g->endRecord(0x25, 4);
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void RoomObjSync_Reset() {
    u32 i = 0;
    u8 z = i;
    for (; i < 3; i++) sRoomObjSyncStates[i] = z;
}

extern "C" u32 RoomObjSync_GetState(u32 idx) {
    if (idx < 3) return sRoomObjSyncStates[idx];
    return 0;
}

extern "C" BOOL RoomObjSync_SetState(u32 idx, u8 v) {
    if (idx < 3) {
        sRoomObjSyncStates[idx] = v;
        return TRUE;
    }
    return FALSE;
}

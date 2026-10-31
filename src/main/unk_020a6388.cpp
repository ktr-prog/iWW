#include "types.h"
#include "net/CommManager.h"
#include "net/NetSessionParts.h"
#include "net/NetSessionState.h"
#include "proto/main/unk_020a6388.h"
#include "proto/main/unk_020a427c.h"


extern CommManager *gCommManager;

extern "C" s32 NetArea_IsBusyStubB() { return 0; }

extern "C" s32 NetArea_IsBusyStubA() { return 0; }

extern "C" void NetArea_OnSceneCreateNop() {}

extern "C" void NetArea_QueueMoveRequest(u32 a, u8 b) {
    NetMoveRequest *p = gNetSessionState.moveQueue;
    s32 i;
    for (i = 3; i >= 0; p++, i--) {
        s32 v;
        u8 t;
        p->get(&v, &t);
        if (v >= 4) {
            p->set(a, b);
            break;
        }
    }
}

extern "C" void NetArea_SetSlotStatus(s32 idx, u32 b, u32 c, u32 d, u32 e) {
    NetSlotStatus *t = &gNetSessionState.slotStatus[idx];
    u8 v[3];
    t->get(&v[0], &v[1], &v[2]);
    if (e & 1) {
        v[0] = b;
    }
    if (e & 2) {
        v[1] = c;
    }
    if (e & 4) {
        v[2] = d;
    }
    t->set(v[0], v[1], v[2]);
    gCommManager->flushDeferred();
}

extern "C" void NetArea_SetMoveReady(s32 idx, u32 v) { gNetSessionState.moveReady[idx].set(v); }

extern "C" void NetArea_SetPendingStatus(u32 idx, u32 a, u32 b, u32 c, u32 d) {
    gNetSessionState.pendingStatus[idx].setMasked(a, b, c, d);
}

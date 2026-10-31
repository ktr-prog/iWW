#include "types.h"
#include "host_labels.h"
#include "net/CommManager.h"
#include "net/NetSessionParts.h"
#include "net/NetSessionState.h"
#include "save/LostChildRecord.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "sys/SceneBase.h"
#include "save/TownId.h"
#include "sys/ProcProfile.h"
#include "nitro/io_access.h"
#include "gfx/ScreenTransition.h"
#include "player/PlayerData.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/autoload_2/unk_02110c98.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0203e7d0.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_0208e6d8.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c390.h"
#include "proto/main/unk_0209c9f8.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020a6388.h"
#include "proto/main/unk_020a647c.h"
#include "proto/main/unk_020a6564.h"
#include "proto/main/unk_020a65fc.h"
#include "proto/main/unk_020a6914.h"
#include "proto/main/unk_020b7190.h"
struct NetStatusUpdateMsg {
    u8 bytes[8];
    NetStatusUpdateMsg() { NetStatusUpdateMsg_Init(this); }
    ~NetStatusUpdateMsg() { NetStatusUpdateMsg_Fini(this); }
    void NetStatusUpdateMsg_Pack(u32 a, u32 b, u32 c, u32 d) { ::NetStatusUpdateMsg_Pack(bytes, a, b, c, d); }
};

struct NetSceneMsg {
    u8 bytes[8];
    NetSceneMsg() { NetSceneMsg_Init(); }
    ~NetSceneMsg() { NetSceneMsg_Fini(); }
    void NetSceneMsg_Set(u32 a) { ::NetSceneMsg_Set(bytes, a); }
};

struct NetStatusMsg {
    u8 v[5];
    NetStatusMsg() { NetStatusMsg_Init(this); }
    ~NetStatusMsg() { NetStatusMsg_Fini(this); }
};




extern "C" {
extern CommManager *gCommManager;
#define gSaveTownId HOST_LABEL(TownId *, gSaveTownId)
}

static inline BOOL Unk_020a42c4_IsTwo(u8 v) { return v == 2 ? TRUE : FALSE; }
static inline BOOL Unk_020a42c4_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }
static inline BOOL IsZero_020a5d4c(u8 v) {
    return v == 0 ? TRUE : FALSE;
}

extern "C" {
void TalkRequest_EndNetSyncHold(void);
BOOL TalkRequest_BeginNetSyncHold(void);
s32 TalkRequestQueue_Reset(void);
void Field_UpdateActions(void);
s32 Scene_GetCurrent(void);
s32 OS_ResetSystem(s32 v);
void MI_CpuCopy8(void *src, void *dst, u32 size);
}






extern "C" s32 NetArea_GetSlotScene(s32 a) {
    u8 v[3];
    if (a < 4) {
        gNetSessionState.slotStatus[a].get(&v[0], &v[1], &v[2]);
        return v[0];
    }
    return 0x3f;
}

extern "C" s32 NetArea_IsSlotOwner(s32 a) {
    u8 v[3];
    if (a < 4) {
        gNetSessionState.slotStatus[a].get(&v[0], &v[1], &v[2]);
        return v[1];
    }
    return 1;
}

extern "C" s32 NetArea_IsSlotMoving(s32 a) {
    u8 v[3];
    if (a < 4) {
        gNetSessionState.slotStatus[a].get(&v[0], &v[1], &v[2]);
        return v[2];
    }
    return 0;
}

extern "C" s32 NetArea_IsLocalOwner() {
    s32 r2 = gCommManager->myAid;
    u8 v[3];
    if (r2 >= 4) {
        return 1;
    }
    gNetSessionState.slotStatus[r2].get(&v[0], &v[1], &v[2]);
    if (v[2] == 0) {
        return v[1];
    }
    if (gNetSessionState.getMoveState() < 7) {
        return v[1];
    }
    return gNetSessionState.getBecomesOwner();
}

extern "C" s32 NetArea_IsLocalMoving() {
    s32 v = gCommManager->myAid;
    if (v < 4) {
        return NetArea_IsSlotMoving(v);
    }
    return 1;
}

extern "C" s32 NetArea_FindOwner(u32 a) {
    s32 r6 = 4;
    s32 i;
    u8 v[3];
    i = 3;
    CommManager *o = gCommManager;
    for (; i >= 0; i--) {
        if (o->isSlotActive(i)) {
            gNetSessionState.slotStatus[i].get(&v[0], &v[1], &v[2]);
            if (v[0] == a && v[1] != 0 && v[2] == 0) {
                r6 = i;
                break;
            }
        }
    }
    return r6;
}

extern "C" s32 NetArea_ResolveRoute(s32 a, s32 b, u32 c, u8 *d) {
    s32 r4 = gCommManager->myAid;
    u8 v[6];
    *d = 0;
    if (b == 0) {
        if (a != 0) goto fail;
        return a;
    } else if (b == 0) {
        if (a != 0) goto fail;
        return a;
    } else if (b == 1) {
        if (a != 1) goto fail;
        return a;
    } else if (b == 2) {
        if (a != 2) goto fail;
        return a;
    } else if (b == 3) {
        if (a != 3) goto fail;
        return a;
    } else if (b == 4) {
        if (a == r4) goto fail;
        return a;
    } else if (b == 5) {
        if (a == 0) goto fail;
        return a;
    } else if (b == 6) {
        s32 t = NetArea_FindOwner(c);
        if (t < 4) {
            if (t != a) goto fail;
            return a;
        }
        gNetSessionState.slotStatus[a].get(&v[0], &v[1], &v[2]);
        if (v[0] == c && v[1] != 0 && v[2] != 0) {
            *d = 1;
        }
        goto fail;
    } else if (b == 7) {
        gNetSessionState.slotStatus[a].get(&v[3], &v[4], &v[5]);
        if (v[3] == c) {
            if (v[4] != 0) goto fail;
            if (v[5] != 0) goto fail;
            if (a == r4) goto fail;
            return a;
        } else {
            s32 t = gNetSessionState.getArrivingSlot();
            if (t >= 4) goto fail;
            if (t != a) goto fail;
            if (a == r4) goto fail;
            return a;
        }
    }
fail:
    return 4;
}

extern "C" void NetArea_SendStateA(s32 a) {
    NetArea_BuildStateA();
    CommManager *o = gCommManager;
    o->beginRecord();
    u8 *r6 = o->getAuxBufA();
    u32 r2 = o->getAuxLenA();
    o->writeRecord(r6, r2);
    o->endRecord(0xf, a);
    ((CommManager *)(o))->clearAuxLenA();
}

extern "C" void NetArea_SendStateB(s32 a) {
    NetArea_BuildStateB();
    CommManager *o = gCommManager;
    o->beginRecord();
    u8 *r6 = o->getAuxBufB();
    u32 r2 = o->getAuxLenB();
    o->writeRecord(r6, r2);
    o->endRecord(0x10, a);
    ((CommManager *)(o))->clearAuxLenB();
}

extern "C" s32 NetArea_FindSlotInScene(u32 a) {
    s32 r5 = 4, r4 = 4;
    u8 v[3];
    NetSlotStatus *p = gNetSessionState.slotStatus;
    u32 i;
    for (i = 0; i < 4; p++, i++) {
        p->get(&v[0], &v[1], &v[2]);
        if (v[0] == a && v[1] != 0) {
            if (v[2] != 0) {
                r5 = i;
            } else {
                r4 = i;
            }
        }
    }
    if (r5 == 4 && r4 == 4) {
        return 4;
    }
    if (r5 != 4 && r4 != 4) {
        return r4;
    }
    if (r5 != 4) {
        return r5;
    }
    return r4;
}

extern "C" void NetArea_SendMoveTarget() {
    CommManager *o = gCommManager;
    if (o->isMyAid(0)) {
        s32 r4 = o->myAid;
        NetArea_QueueMoveRequest(r4, Scene_GetRequestedScene());
    } else {
        NetSceneMsg tmp;
        tmp.NetSceneMsg_Set(Scene_GetRequestedScene());
        o = gCommManager;
        o->beginRecord();
        o->writeRecord((u8 *)&tmp, 1);
        o->endRecord(8, 0);
    }
}

extern "C" void NetSession_SetSyncState(s32 a, s32 b) {
    gNetSessionState.setSyncState(a, b);
}

extern "C" s32 NetSession_GetSyncState(s32 a) {
    return gNetSessionState.getSyncState(a);
}

extern "C" void NetSession_SetSyncMemberMask(s32 a) {
    ((NetSessionState *)(&gNetSessionState))->setSyncMemberMask(a);
}

extern "C" u16 NetSession_GetSyncMemberMask() {
    return gNetSessionState.getSyncMemberMask();
}

extern "C" void NetSession_SetSyncRequester(s32 a) {
    gNetSessionState.setSyncRequester(a);
}

extern "C" void NetSession_SetMemberSyncReply(s32 a, s32 b) {
    gNetSessionState.setMemberSyncReply(a, b);
}

extern "C" void NetSession_SetSyncKind(s32 a) {
    gNetSessionState.setSyncKind(a);
}

extern "C" s32 NetSession_GetSyncKind() {
    return gNetSessionState.getSyncKind();
}

extern "C" void NetSession_SetActiveSyncKind(s32 a) {
    gNetSessionState.setActiveSyncKind(a);
}

extern "C" s32 NetSession_GetActiveSyncKind() {
    return gNetSessionState.getActiveSyncKind();
}

extern "C" s32 NetSession_GetLastSyncSlot() {
    return gNetSessionState.getLastSyncSlot();
}

extern "C" void NetSession_SetLastSyncSlot(s32 a) {
    gNetSessionState.setLastSyncSlot(a);
}

extern "C" void NetArea_SetMoveState(s32 a) {
    gNetSessionState.setMoveState(a);
}

extern "C" s32 NetArea_GetMoveState() {
    return gNetSessionState.getMoveState();
}

extern "C" void NetArea_SetMemberAck(s32 a, s32 b) {
    gNetSessionState.setMemberAck(a, b);
}

extern "C" void NetArea_SetStateRequester(s32 a) {
    gNetSessionState.setStateRequester(a);
}

extern "C" void NetArea_SetOwnerAck(s32 a) {
    gNetSessionState.setOwnerAck(a);
}

extern "C" void NetArea_GetSlotStatus(s32 idx, u8 *a, u8 *b, u8 *c) {
    if (idx < 4) {
        gNetSessionState.slotStatus[idx].get(a, b, c);
    }
}

extern "C" void NetArea_OnStateAReceived() {
    CommManager *o = gCommManager;
    s32 r5 = o->myAid;
    if (o->isSlotActive(r5)) {
        if (((CommManager *)(o))->getAuxLenA()) {
            NetArea_ParseStateA();
            NetArea_SetSlotStatus(r5, 0x3f, 1, 0, 2);
            if (o->isOnline()) {
                if (r5 != 0) {
                    NetStatusUpdateMsg tmp;
                    tmp.NetStatusUpdateMsg_Pack(0x3f, 1, 0, 2);
                    o = gCommManager;
                    o->beginRecord();
                    o->writeRecord((u8 *)&tmp, 2);
                    o->endRecord(0xb, 0);
                } else {
                    NetArea_SetPendingStatus(r5, 0x3f, 1, 0, 2);
                }
            }
        }
    }
}

extern "C" void NetArea_ApplyStateB() {
    CommManager *o = gCommManager;
    if (o->isSlotActive(o->myAid)) {
        if (((CommManager *)(o))->getAuxLenB()) {
            NetArea_ParseStateB();
        }
    }
}

extern "C" void NetArea_SendStateToNewOwner() {
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        if (gNetSessionState.getMoveState() == 3) {
            if (IsZero_020a5d4c(gScreenTransition.state)) {
                if (!NetArea_IsUnsharedScene(Scene_GetCurrent())) {
                    NetArea_SendStateA(gNetSessionState.getHandoffSlot());
                }
                gNetSessionState.setMoveState(5);
            }
        }
    }
}

extern "C" void NetArea_SendStateToRequester() {
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        s32 r4 = gNetSessionState.getStateRequester();
        if (r4 < 4) {
            NetArea_SendStateB(r4);
            gNetSessionState.setArrivingSlot(r4);
            gNetSessionState.setStateRequester(4);
        }
    }
}

extern "C" void NetSession_SetCtrl07Received(s32 a) {
    ((NetSessionState *)(&gNetSessionState))->setCtrl07Received(a);
}

extern "C" u8 NetSession_GetCtrl07Received() {
    return gNetSessionState.getCtrl07Received();
}

extern "C" BOOL NetArea_IsUnsharedScene(s32 v) {
    switch (v) {
    case 0xc:
    case 0xd:
    case 0xe:
    case 0x2e:
    case 0x2f:
        return TRUE;
    }
    return FALSE;
}

extern "C" void NetSession_Init() {
}

extern "C" void NetSession_Exit() {
}

extern "C" void NetSession_OnBeginHost() {
}

extern "C" void NetSession_Reset() {
    gNetSessionState.reset();
}

extern "C" void NetSession_RemoveSlot(s32 a) {
    gNetSessionState.resetSlot(a);
}

extern "C" void NetSession_Update() {
    s32 r4 = gCommManager->myAid;
    if (gCommManager->isSlotActive(r4)) {
        gNetSessionState.updateArrivingSlot();
        gNetSessionState.notifyMovingMember();
        if (r4 == 0) {
            gNetSessionState.updateMoveQueue();
            gNetSessionState.flushStatusUpdates();
        }
        if (r4 != 0) {
            gNetSessionState.sendMoveReady();
        }
        if (r4 == 0) {
            gNetSessionState.updateSyncHost();
        }
        gNetSessionState.updateSyncClient();
        gNetSessionState.updateMove();
        gNetSessionState.notifyMovingOwner();
    }
}

extern "C" void NetSession_PostUpdate() {
}

NetSessionState::NetSessionState() {
    reset();
}

NetSessionState::~NetSessionState() {
}

void NetSessionState::resetSlot(s32 idx) {
    slotStatus[idx].reset();
    moveQueue[idx].reset();
    moveReady[idx].reset();
    pendingStatus[idx].reset();
    resetMemberSyncReply(idx);
    setMemberAck(idx, 0);
    if (idx != 0) {
        setSyncState(idx, 7);
    }
    if (idx == getHandoffSlot()) {
        setHandoffSlot(4);
    }
    if (idx == getNotifiedOwnerMover()) {
        setNotifiedOwnerMover(4);
    }
    if (idx == getNotifiedMemberMover()) {
        setNotifiedMemberMover(4);
    }
    if (idx == getStateRequester()) {
        setStateRequester(4);
    }
    if (idx == getArrivingSlot()) {
        setArrivingSlot(4);
    }
    if (idx == getStateSourceSlot()) {
        setStateSourceSlot(4);
    }
}

void NetSessionState::reset() {
    s32 i;
    for (i = 3; i >= 0; i--) {
        slotStatus[i].reset();
        moveQueue[i].reset();
        moveReady[i].reset();
        pendingStatus[i].reset();
    }
    resetSyncPhase();
    resetSyncRequester();
    resetSyncKind();
    resetAllMemberSyncReplies();
    setReplyTimer(0);
    resetSyncStates();
    setHandoffSlot(4);
    clearMemberAcks();
    setNotifiedOwnerMover(4);
    setMoveState(16);
    setStateRequester(4);
    setArrivingSlot(4);
    setStateSourceSlot(4);
    setOwnerAck(0);
    setNotifiedMemberMover(4);
    setLastSyncSlot(4);
    setBecomesOwner(0);
    setGoDelay(0);
    setActiveSyncKind(4);
    setCtrl07Received(0);
}

u8 sSceneFadeInType;
u8 data_021eda58;
NetSessionState gNetSessionState;
ProcProfile sSceneBaseProfile = {(void *(*)())SceneBase_Create, 2, 1};

void NetSessionState::updateMoveQueue() {
    struct {
        u8 b0, b1, b2;
        u8 buf[5];
    } l;
    u32 idx[2] = {4, 4};
    u32 cnt[2];
    func_02133ef8(cnt, 8);
    processMoveRequest(&idx[0], &cnt[0]);
    startNextMove(&idx[1], &cnt[1]);
    u32 i = 0;
    CommManager *o = gCommManager;
    for (; i < 2; i++) {
        u32 off = i << 2;
        s32 r7 = *(u32 *)((u8 *)idx + off);
        if (r7 < 4) {
            slotStatus[r7].get(&l.b0, &l.b1, &l.b2);
            NetStatusMsg_Init(l.buf);
            NetStatusMsg_Pack(l.buf, r7, l.b0, l.b1, l.b2, *(u32 *)((u8 *)cnt + off));
            o->beginRecord();
            o->writeRecord(l.buf, 2);
            o->endRecord(9, 4);
            NetStatusMsg_Fini(l.buf);
        }
    }
}

void NetSessionState::startNextMove(u32 *a, u32 *b) {
    s32 r5 = 4;
    s32 i;
    for (i = 3; i >= 0; i--) {
        if (NetArea_IsSlotMoving(i) != 0) {
            r5 = i;
            break;
        }
    }
    if (r5 >= 4) {
        s32 r4 = peekMoveRequest();
        if (r4 < 4) {
            NetArea_SetSlotStatus(r4, 0x3f, 0, 1, 4);
            *a = r4;
            *b = 4;
        }
    }
}

s32 NetSessionState::peekMoveRequest() {
    s32 v;
    u8 byte;
    moveQueue[0].get(&v, &byte);
    return v;
}

void NetSessionState::popMoveRequest() {
    if (peekMoveRequest() < 4) {
        NetMoveRequest *p = moveQueue;
        s32 i;
        for (i = 2; i >= 0; i--) {
            NetMoveRequest *q = p + 1;
            s32 v;
            u8 byte;
            q->get(&v, &byte);
            if (v >= 4) break;
            MI_CpuCopy8(q, p, sizeof(NetMoveRequest));
            p++;
        }
        p->reset();
    }
}

void NetSessionState::sendMoveReady() {
    s32 idx = ((volatile CommManager *)gCommManager)->myAid;
    NetMoveReady *p = &moveReady[idx];
    s32 v;
    p->get((u32 *)&v);
    if (v != 0) {
        u8 b = v;
        CommManager *o = gCommManager;
        o->beginRecord();
        o->writeRecord(&b, 1);
        o->endRecord(10, 0);
        p->reset();
    }
}

void NetSessionState::processMoveRequest(u32 *a, u32 *b) {
    CommManager *o;
    s32 r5 = peekMoveRequest();
    if (r5 < 4) {
        NetMoveReady *p = &moveReady[r5];
        s32 v;
        p->get((u32 *)&v);
        if (v == 1) {
            s32 r7 = 1;
            s32 tmp;
            u8 byte;
            moveQueue[0].get(&tmp, &byte);
            s32 i;
            i = 3;
            o = gCommManager;
            for (; i >= 0; i--) {
                if (r5 != i && o->isSlotActive(i) != 0 && byte == NetArea_GetSlotScene(i)) {
                    r7 = 0;
                    break;
                }
            }
            NetArea_SetSlotStatus(r5, byte, r7, 0, 7);
            p->reset();
            popMoveRequest();
            *a = r5;
            *b = 7;
        }
    }
}

void NetSessionState::flushStatusUpdates() {
    u32 i = 0;
    CommManager *o = gCommManager;
    for (; i < 4; i++) {
        u8 b0, b1, b2;
        u8 buf[5];
        u32 out;
        NetPendingStatus *p = &pendingStatus[i];
        p->get(&b0, &b1, &b2, &out);
        if (out != 0) {
            NetArea_SetSlotStatus(i, b0, b1, b2, out);
            NetStatusMsg_Init(buf);
            NetStatusMsg_Pack(buf, i, b0, b1, b2, out);
            o->beginRecord();
            o->writeRecord(buf, 2);
            o->endRecord(9, 4);
            p->reset();
            NetStatusMsg_Fini(buf);
        }
    }
}

void NetSessionState::setBecomesOwner(u32 v) { becomesOwner = v; }

u32 NetSessionState::getBecomesOwner() { return becomesOwner; }

void NetSessionState::setMoveState(s32 v) { moveState = v; }

s32 NetSessionState::getMoveState() { return moveState; }

void NetSessionState::updateMove() {
    CommManager *o = gCommManager;
    s32 r7 = o->myAid;
    u8 b0, b1, b2, b3, b4, b5;
    s32 best;
    s32 flag;
    s32 i;
    switch ((u32)getMoveState()) {
    case 16:
        if (gNextSceneProfile == 5) {
            NetArea_SendMoveTarget();
            clearMemberAcks();
            setOwnerAck(0);
            NetArea_SetMoveState(0);
        }
        break;
    case 0:
        if (NetArea_IsSlotMoving(r7) != 0) {
            setMoveState(1);
        }
        break;
    case 1:
        if (NetArea_IsBusyStubB() != 0) break;
        if (NetArea_IsBusyStubA() != 0) break;
        NetArea_GetSlotStatus(r7, &b0, &b1, &b2);
        if (b1 != 0) {
            best = 4;
            for (i = 0; i < 4; i++) {
                if (i != r7 && o->isSlotActive(i) != 0 && b0 == NetArea_GetSlotScene(i)) {
                    best = i;
                    break;
                }
            }
            if (best < 4) {
                setHandoffSlot(best);
                setMoveState(2);
            } else {
                setHandoffSlot(4);
                setMoveState(5);
            }
        } else {
            setHandoffSlot(4);
            setMoveState(4);
        }
        break;
    case 2:
        flag = 1;
        if (NetArea_IsUnsharedScene(Scene_GetCurrent()) == 0) {
            for (i = 3; i >= 0; i--) {
                if (i != r7 && o->isSlotActive(i) != 0) {
                    s32 t = NetArea_GetSlotScene(i);
                    if (t == Scene_GetCurrent() && getMemberAck(i) == 0) {
                        flag = 0;
                        break;
                    }
                }
            }
        }
        if (flag != 0) {
            if (o->getDeferredLen() != 0) break;
            if (o->getHeldLen() != 0) break;
            if (o->getLoopbackLen() != 0) break;
            if (NetArea_IsBusyStubA() != 0) break;
            clearMemberAcks();
            o->clearAuxLenA();
            setMoveState(3);
        }
        break;
    case 4:
        if (getOwnerAck() == 0 && NetArea_IsUnsharedScene(Scene_GetCurrent()) == 0) break;
        setOwnerAck(0);
        setMoveState(5);
        break;
    case 8:
        if (getHandoffSlot() != 4) {
            if (NetArea_IsSlotOwner(getHandoffSlot()) == 0 && NetArea_IsUnsharedScene(Scene_GetCurrent()) == 0) break;
            setMoveState(9);
        } else {
            setMoveState(9);
        }
        break;
    case 9: {
        u32 v = Scene_GetRequestedScene();
        best = 4;
        for (i = 3; i >= 0; i--) {
            if (i != r7 && o->isSlotActive(i) != 0) {
                NetArea_GetSlotStatus(i, &b3, &b4, &b5);
                if (b3 == v && b4 != 0) {
                    best = i;
                    break;
                }
            }
        }
        if (best < 4) {
            setStateSourceSlot(best);
            setBecomesOwner(0);
            o->clearAuxLenB();
            if (NetArea_IsUnsharedScene(Scene_GetRequestedScene()) == 0) {
                CommManager *o2 = gCommManager;
                o2->beginRecord();
                o2->endRecord(0xe, getStateSourceSlot());
            }
            setMoveState(10);
        } else {
            setStateSourceSlot(4);
            setBecomesOwner(1);
            setMoveState(11);
        }
        break;
    }
    case 10:
        if (o->getAuxLenB() != 0 || NetArea_IsUnsharedScene(Scene_GetRequestedScene()) != 0) {
            setMoveState(11);
        }
        break;
    case 11:
    case 12:
    case 13:
        break;
    case 14:
        NetArea_SetMoveReady(((CommManager *)o)->myAid, 1);
        setMoveState(15);
        break;
    case 15:
        if (NetArea_IsLocalMoving() == 0) {
            setMoveState(16);
        }
        break;
    }
}

void NetSessionState::setHandoffSlot(s32 v) { handoffSlot = v; }

s32 NetSessionState::getHandoffSlot() { return handoffSlot; }

void NetSessionState::setMemberAck(s32 i, u32 v) { memberAck[i] = v; }

u32 NetSessionState::getMemberAck(s32 i) { return memberAck[i]; }

void NetSessionState::clearMemberAcks() {
    u8 *p = memberAck;
    s32 i;
    for (i = 3; i >= 0; i--) *p++ = 0;
}

void NetSessionState::setNotifiedOwnerMover(s32 v) { notifiedOwnerMover = v; }

s32 NetSessionState::getNotifiedOwnerMover() { return notifiedOwnerMover; }

void NetSessionState::notifyMovingOwner() {
    s32 r5 = 4;
    s32 i = 3;
    CommManager *o = gCommManager;
    for (; i >= 0; i--) {
        if (o->isSlotActive(i) != 0 && NetArea_IsSlotMoving(i) != 0) {
            r5 = i;
            break;
        }
    }
    if (r5 != getNotifiedOwnerMover()) {
        if (r5 < 4) {
            if (o->isMyAid(r5) == 0 && (s32)NetArea_GetSlotScene(r5) == Scene_GetCurrent() &&
                NetArea_IsSlotOwner(r5) != 0 && NetArea_IsUnsharedScene(Scene_GetCurrent()) == 0) {
                CommManager *o2 = gCommManager;
                o2->beginRecord();
                o2->endRecord(0xd, r5);
            }
            setNotifiedOwnerMover(r5);
        } else {
            setNotifiedOwnerMover(4);
        }
    }
}

void NetSessionState::setStateSourceSlot(s32 v) { stateSourceSlot = v; }

s32 NetSessionState::getStateSourceSlot() { return stateSourceSlot; }

void NetSessionState::setStateRequester(s32 v) { stateRequester = v; }

s32 NetSessionState::getStateRequester() { return stateRequester; }

void NetSessionState::setArrivingSlot(s32 v) { arrivingSlot = v; }

s32 NetSessionState::getArrivingSlot() { return arrivingSlot; }

void NetSessionState::updateArrivingSlot() {
    s32 c = getArrivingSlot();
    if (c < 4) {
        u32 t = NetArea_GetSlotScene(c);
        if ((s32)t == Scene_GetCurrent()) {
            setArrivingSlot(4);
        }
    }
}

void NetSessionState::setOwnerAck(u32 v) { ownerAck = v; }

u32 NetSessionState::getOwnerAck() { return ownerAck; }

void NetSessionState::setNotifiedMemberMover(s32 v) { notifiedMemberMover = v; }

s32 NetSessionState::getNotifiedMemberMover() { return notifiedMemberMover; }

void NetSessionState::notifyMovingMember() {
    s32 r5 = 4;
    CommManager *o = gCommManager;
    s32 saved = o->myAid;
    s32 i;
    for (i = 3; i >= 0; i--) {
        if (o->isSlotActive(i) != 0 && NetArea_IsSlotMoving(i) != 0) {
            r5 = i;
            break;
        }
    }
    if (r5 != getNotifiedMemberMover()) {
        if (r5 < 4) {
            if (o->isMyAid(r5) == 0 && NetArea_IsSlotOwner(saved) != 0 &&
                (s32)NetArea_GetSlotScene(r5) == Scene_GetCurrent() && NetArea_IsUnsharedScene(Scene_GetCurrent()) == 0) {
                CommManager *o2 = gCommManager;
                o2->beginRecord();
                o2->endRecord(0x11, r5);
            }
            setNotifiedMemberMover(r5);
        } else {
            setNotifiedMemberMover(4);
        }
    }
}

void NetSessionState::setSyncState(s32 i, u32 v) { syncState[i] = v; }

u32 NetSessionState::getSyncState(s32 i) { return syncState[i]; }

void NetSessionState::resetSyncStates() {
    u32 *p = syncState;
    s32 i;
    for (i = 3; i >= 0; i--) *p++ = 7;
}

void NetSessionState::rejectSyncRequest(u32 a, u32 b) {
    if (b != 0) {
        setSyncState(a, 6);
    } else if (a == 0) {
        setSyncState(0, 6);
    } else {
        u8 buf = 6;
        CommManager *o = gCommManager;
        o->beginRecord();
        o->writeRecord(&buf, 1);
        o->endRecord(1, a);
        setSyncState(a, 7);
    }
}

void NetSessionState::updateSyncHost() {
    u32 i;
    u32 slot;
    s32 ok;
    s32 j;
    s32 z24 = 0, z28 = 0, z14 = 0, z18 = 0, z1c = 0, z20 = 0, z2c = 0;
    u8 m[5];
    s32 mode;
    CommManager *g;
    s32 c18;
    s32 k;
    BOOL all;
    BOOL all2;
    i = 0;
    do {
        slot = getSyncState(i);
        if (slot <= 3) {
            ok = TRUE;
            for (j = 3; j >= 0; j--) {
                switch (getSyncState(j)) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 7:
                    break;
                default:
                    ok = z14;
                    break;
                }
                if (!ok) {
                    break;
                }
            }
            if (ok) {
                if (getSyncPhase() != 4) {
                    ok = z18;
                }
            }
            if (ok) {
                if (Scene_GetCurrent() == 0x2e || Scene_GetCurrent() == 0x2f || Scene_GetCurrent() == 0xd) {
                    ok = z1c;
                }
            }
            if (ok) {
                if (SceneWarp_GetScene(Scene_GetWarpRequest()) == 0x2e || SceneWarp_GetScene(Scene_GetWarpRequest()) == 0x2f ||
                    SceneWarp_GetScene(Scene_GetWarpRequest()) == 0xd) {
                    ok = z20;
                }
            }
            if (ok) {
                setSyncPhase(z24);
                setSyncRequester(i);
                if (slot == 0) {
                    setSyncKind(z28);
                } else if (slot == 1) {
                    setSyncKind(1);
                } else if (slot == 2) {
                    setSyncKind(2);
                } else {
                    setSyncKind(3);
                }
                setSyncState(i, 4);
            } else {
                rejectSyncRequest(i, slot == 0 ? 1 : z2c);
            }
        }
        i++;
    } while (i < 4);

    if (getSyncPhase() == 0) {
        c18 = getSyncRequester();
        k = 3;
        g = gCommManager;
        for (; k >= 0; k--) {
            if (k != c18 && g->isSlotActive(k)) {
                if (k == 0) {
                    setMemberSyncReply(0, 0);
                } else {
                    NetSyncMsg_Init();
                    mode = getSyncKind();
                    NetSyncMsg_Pack(&m[0], 0, mode, getSyncRequester());
                    g->beginRecord();
                    g->writeRecord(&m[0], 1);
                    g->endRecord(0xc, k);
                    setMemberSyncReply(k, 1);
                    NetSyncMsg_Fini();
                }
            }
        }
        setSyncPhase(1);
    }
    if (getSyncPhase() == 1) {
        all = TRUE;
        c18 = getSyncRequester();
        k = 3;
        g = gCommManager;
        for (; k >= 0; k--) {
            if (k != c18 && g->isSlotActive(k)) {
                s32 v = getMemberSyncReply(k);
                if (v != 2 && v != 3) {
                    all = FALSE;
                    break;
                }
            }
        }
        if (all) {
            all2 = TRUE;
            for (k = 3; k >= 0; k--) {
                if (k != c18 && g->isSlotActive(k) && getMemberSyncReply(k) == 3) {
                    all2 = FALSE;
                    break;
                }
            }
            if (all2) {
                for (k = 3; k >= 0; k--) {
                    if (k != c18 && g->isSlotActive(k)) {
                        if (k == 0) {
                            setMemberSyncReply(0, 5);
                        } else {
                            NetSyncMsg_Init();
                            NetSyncMsg_Pack(&m[1], 5, 4, getSyncRequester());
                            g->beginRecord();
                            g->writeRecord(&m[1], 1);
                            g->endRecord(0xc, k);
                            setMemberSyncReply(k, 5);
                            NetSyncMsg_Fini();
                        }
                    }
                }
                if (getSyncKind() == 0 || g->isMyAid(c18) != 0) {
                    setSyncState(c18, 5);
                } else {
                    m[2] = 5;
                    CommManager *g5 = gCommManager;
                    g5->beginRecord();
                    g5->writeRecord(&m[2], 1);
                    g5->endRecord(1, c18);
                    setSyncState(c18, 7);
                }
                if (getSyncKind() == 0) {
                    NetSession_SetCtrl07Received(0);
                }
                setLastSyncSlot(c18);
                setSyncPhase(2);
            } else {
                for (k = 3; k >= 0; k--) {
                    if (k != c18 && g->isSlotActive(k)) {
                        if (getMemberSyncReply(k) == 2) {
                            if (k == 0) {
                                setMemberSyncReply(0, 4);
                            } else {
                                NetSyncMsg_Init();
                                NetSyncMsg_Pack(&m[3], 4, 4, getSyncRequester());
                                g->beginRecord();
                                g->writeRecord(&m[3], 1);
                                g->endRecord(0xc, k);
                                setMemberSyncReply(k, 4);
                                NetSyncMsg_Fini();
                            }
                        } else {
                            setMemberSyncReply(k, 6);
                        }
                    }
                }
                setSyncPhase(3);
            }
        }
    }
    if (getSyncPhase() == 2) {
        BOOL all3 = TRUE;
        s32 c18b = getSyncRequester();
        k = 3;
        CommManager *g6 = gCommManager;
        for (; k >= 0; k--) {
            if (k != c18b && g6->isSlotActive(k) && getMemberSyncReply(k) != 6) {
                all3 = FALSE;
                break;
            }
        }
        if (all3) {
            setSyncPhase(4);
        }
    }
    if (getSyncPhase() == 3) {
        BOOL all4 = TRUE;
        s32 c18c = getSyncRequester();
        k = 3;
        CommManager *g7 = gCommManager;
        for (; k >= 0; k--) {
            if (k != c18c && g7->isSlotActive(k) && getMemberSyncReply(k) != 6) {
                all4 = FALSE;
                break;
            }
        }
        if (all4) {
            if (getSyncKind() == 0 || g7->isMyAid(c18c) != 0) {
                setSyncState(c18c, 6);
            } else {
                m[4] = 6;
                CommManager *g8 = gCommManager;
                g8->beginRecord();
                g8->writeRecord(&m[4], 1);
                g8->endRecord(1, c18c);
                setSyncState(c18c, 7);
            }
            if (getSyncKind() == 0) {
                Net_WifiHostKeepAlive();
            }
            setSyncPhase(4);
        }
    }
}

void NetSessionState::setLastSyncSlot(s32 v) { lastSyncSlot = v; }

s32 NetSessionState::getLastSyncSlot() { return lastSyncSlot; }

void NetSessionState::setSyncMemberMask(u16 v) { syncMemberMask = v; }

u16 NetSessionState::getSyncMemberMask() { return syncMemberMask; }

void NetSessionState::setSyncPhase(s32 v) { syncPhase = v; }

s32 NetSessionState::getSyncPhase() { return syncPhase; }

void NetSessionState::resetSyncPhase() { syncPhase = 4; }

void NetSessionState::setSyncRequester(s32 v) { syncRequester = v; }

s32 NetSessionState::getSyncRequester() { return syncRequester; }

void NetSessionState::resetSyncRequester() { syncRequester = 4; }

void NetSessionState::setSyncKind(s32 v) { syncKind = v; }

s32 NetSessionState::getSyncKind() { return syncKind; }

void NetSessionState::resetSyncKind() { syncKind = 4; }

void NetSessionState::setMemberSyncReply(s32 i, s32 v) { memberSyncReply[i] = v; }

s32 NetSessionState::getMemberSyncReply(s32 i) { return memberSyncReply[i]; }

void NetSessionState::resetMemberSyncReply(s32 i) { memberSyncReply[i] = 6; }

void NetSessionState::resetAllMemberSyncReplies() {
    s32 i;
    for (i = 3; i >= 0; i--) {
        memberSyncReply[i] = 6;
    }
}


u16 gNextSceneProfile = 0xd8;

void NetSessionState::updateSyncClient() {
    CommManager *g = gCommManager;
    s32 st = g->myAid;
    s32 mode;
    s32 v;
    s32 st2;
    u8 m[4];
    if (getMemberSyncReply(st) == 0) {
        setReplyTimer(0);
        setMemberSyncReply(st, 1);
    }
    st = g->myAid;
    if (getMemberSyncReply(st) == 1) {
        BOOL r7 = FALSE;
        s32 t = Scene_GetCurrent();
        if (t != 0x2e && t != 0xc && t != 0xd && t != 0xe && t != 0x2f) {
            if (SceneWarp_GetScene(Scene_GetWarpRequest()) == 0x3f && gSceneCreating == 0) {
                if (TalkRequest_BeginNetSyncHold()) {
                    r7 = TRUE;
                }
            }
        }
        mode = getSyncKind();
        if (r7) {
            setGoDelay(0x28);
            setReplyTimer(0);
            if (st != 0) {
                NetSyncMsg_Init();
                NetSyncMsg_Pack(&m[0], 2, 4, getSyncRequester());
                CommManager *g2 = gCommManager;
                g2->beginRecord();
                g2->writeRecord(&m[0], 1);
                g2->endRecord(0xc, 0);
                NetSyncMsg_Fini();
            }
            FieldInfoBalloon_ShowSyncKindMsg(mode);
            setMemberSyncReply(st, 2);
            g->setSessionMemberMask(Comm_GetMemberMask());
        } else {
            u32 n = getReplyTimer() + 1;
            if (n >= 0xa0) {
                if (st == 0) {
                    setMemberSyncReply(0, 3);
                } else {
                    NetSyncMsg_Init();
                    NetSyncMsg_Pack(&m[1], 3, 4, getSyncRequester());
                    CommManager *g2 = gCommManager;
                    g2->beginRecord();
                    g2->writeRecord(&m[1], 1);
                    g2->endRecord(0xc, 0);
                    setMemberSyncReply(st, 6);
                    NetSyncMsg_Fini();
                }
                MenuCtrl_ResetForceClose();
                setReplyTimer(0);
            } else {
                setReplyTimer(n);
            }
            FieldInfoBalloon_ShowSyncWaitMsg(mode);
        }
    }
    st2 = g->myAid;
    v = getMemberSyncReply(st2);
    if (v == 2) {
        FieldInfoBalloon_ShowSyncKindMsg(getSyncKind());
    } else if (v == 4) {
        TalkRequest_EndNetSyncHold();
        MenuCtrl_ResetForceClose();
        FieldInfoBalloon_ShowCancelled();
        setGoDelay(0);
        if (st2 != 0) {
            NetSyncMsg_Init();
            NetSyncMsg_Pack(&m[2], 6, 4, getSyncRequester());
            CommManager *g3 = gCommManager;
            g3->beginRecord();
            g3->writeRecord(&m[2], 1);
            g3->endRecord(0xc, 0);
            NetSyncMsg_Fini();
        }
        setMemberSyncReply(st2, 6);
    } else if (v == 5) {
        BOOL r7;
        s32 md = getSyncKind();
        s32 sl;
        FieldInfoBalloon_ShowSyncKindMsg(md);
        u8 u = gNetSessionState.getGoDelay();
        if (u != 0) {
            gNetSessionState.setGoDelay(u - 1);
        }
        r7 = FALSE;
        if (getGoDelay() != 0) {
            r7 = TRUE;
        }
        if (!r7) {
            if (md == 0) {
                sl = getSyncRequester();
                if (PlayerData_IsUsedByIndex(sl + 3) == 0) {
                    r7 = TRUE;
                    if (st2 == 0) {
                        u32 irq = Net_GetConnectedMask();
                        u16 mask = 1 << sl;
                        if (mask != (mask & irq)) {
                            u32 f = g->getErrorFlags();
                            if ((f & 4) == 0) {
                                g->setErrorFlags(f | 4);
                            }
                        }
                    }
                }
            } else if (md == 1) {
                setLastSyncSlot(getSyncRequester());
            }
        }
        if (r7) {
            return;
        }
        setActiveSyncKind(getSyncKind());
        Net_SetJoiningAid(getSyncRequester());
        Scene_SavePlayerPos(Scene_GetWarpRequest(), 0);
        if (getSyncKind() == 0) {
            PlayerData *x = PlayerData_Get(getSyncRequester() + 3);
            u16 *p;
            if (x != 0 && ((LostChildRecord *)x->getLostChildRecord())->isEscorting() &&
                (p = ((LostChildRecord *)x->getLostChildRecord())->getTownId(), p[0] == gSaveTownId.townId) &&
                memcmp(p + 1, gSaveTownId.townName, 8) == 0) {
                SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2f, 2, 2);
            } else {
                static FxVec3 s(0x10000, 0, 0x5000);
                SceneWarp_RequestAt(Scene_GetWarpRequest(), 0xd, &s, 0x800000, 0, 2, 2);
            }
        } else {
            SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2e, 2, 3);
        }
        if (g->isMyAid(0)) {
            if (md == 0) {
                SaveManager_RequestAct15();
            } else if (md == 1) {
                SaveManager_RequestAct18();
            }
        } else {
            if (md == 0) {
                SaveManager_RequestAct16();
            } else if (md == 1) {
                SaveManager_RequestAct19();
            } else if (md == 2) {
                SaveManager_RequestAct1B();
                SaveManager_SetEndSessionSave(0);
            } else {
                SaveManager_RequestAct1B();
                SaveManager_SetEndSessionSave(1);
            }
        }
        if (st2 != 0) {
            NetSyncMsg_Init();
            NetSyncMsg_Pack(&m[3], 6, 4, getSyncRequester());
            CommManager *g3 = gCommManager;
            g3->beginRecord();
            g3->writeRecord(&m[3], 1);
            g3->endRecord(0xc, 0);
            NetSyncMsg_Fini();
        }
        setMemberSyncReply(st2, 6);
    }
}

void NetSessionState::setReplyTimer(s32 v) { replyTimer = v; }

s32 NetSessionState::getReplyTimer() { return replyTimer; }

void NetSessionState::setGoDelay(u8 v) { goDelay = v; }

u8 NetSessionState::getGoDelay() { return goDelay; }

void NetSessionState::setActiveSyncKind(s32 v) { activeSyncKind = v; }

s32 NetSessionState::getActiveSyncKind() { return activeSyncKind; }

void NetSessionState::setCtrl07Received(u8 v) { ctrl07Received = v; }


u8 NetSessionState::getCtrl07Received() { return ctrl07Received; }

extern "C" SceneBase *SceneBase_Create(void) {
    return new SceneBase();
}

extern "C" void SceneBase_SetupGraphics(void) {
    Gfx_ResetDisplayRegs();
    G3X_Init();
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(1);
    GX_SetBankForBGExtPltt(0x40);
    GX_SetBankForTex(6);
    GX_SetBankForTexPltt(0x10);
    IO_W((volatile u32 *)0x40004c8, 0x20000000);
    IO_W((volatile u32 *)0x40004cc, 0x7fff);
    IO_W((volatile u32 *)0x40004c0, 0x7fff);
    IO_W((volatile u32 *)0x40004c4, 0);
    Gfx3d_InitEngine();
}

BOOL SceneBase::preCreate() {
    if (!ProcBase::preCreate()) {
        return FALSE;
    }
    if (gSceneCreating != 0) {
        return TRUE;
    }
    SceneBase_SetupGraphics();
    TransitionCommIcon_Suspend();
    gActorDefaultParent = this;
    sSceneFadeInDelay = 4;
    NetArea_OnSceneCreateNop();
    NetArea_ApplyStateB();
    gSceneCreating++;
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        switch (NetArea_GetMoveState()) {
        case 6:
            NetArea_SetMoveState(7);
            break;
        case 0xd:
            NetArea_SetMoveState(0xe);
            break;
        }
    }
    data_021eda50 = 0;
    data_021eda58 = 0;
    return TRUE;
}

void SceneBase::postCreate(s32 a) {
    if (a == 2) {
        gSceneCreating = 0;
        if (profile != 6) {
            ScreenTransition_ShowCover();
        }
        Comm_ProcessReceived(0);
        NetSession_Update();
        Field_UpdateActions();
        Scene_PostCreateStub();
    }
    GameProc::postCreate(a);
}

BOOL SceneBase::preDelete() {
    if (ProcBase::preDelete()) {
        return TRUE;
    }
    return FALSE;
}


BOOL SceneBase::postDelete(s32 a) {
    if (a == 2) {
        sSceneExists = 0;
        if (gSoftResetRequested != 0) {
            SoftReset_ClearSystems();
        }
        gActorDefaultParent = 0;
        Snd_DestroyScene();
    }
    return ProcBase::postDelete(a);
}

BOOL SceneBase::preExecute() {
    Comm_ProcessReceived(0);
    NetSession_Update();
    Field_UpdateActions();
    if (ProcBase::preExecute() == 0) {
        return FALSE;
    }
    if (gSoftResetRequested != 0) {
        if (Unk_020a42c4_IsTwo(gScreenTransition.state) != 0) {
            sSceneFadeOutType = 2;
            sSceneFadeInType = 0;
            ScreenTransition_StartFadeOut(2, 0x10);
        }
        return FALSE;
    }
    if (gNextSceneProfile != 0xd8) {
        if (Unk_020a42c4_IsTwo(gScreenTransition.state) != 0 || data_021c3cb8 != 0) {
            ScreenTransition_StartFadeOut(sSceneFadeOutType, 0xf);
        }
        return FALSE;
    }
    if (procFlags & 1) {
        if (ProcBase_HasCreatingChild(this) == 0) {
            procFlags &= ~1;
            procFlags &= ~4;
        } else {
            return FALSE;
        }
    }
    if (sSceneFadeInDelay != 0) {
        if (Unk_020a42c4_IsZero(gScreenTransition.state) != 0) {
            sSceneFadeInDelay = sSceneFadeInDelay - 1;
            if (sSceneFadeInDelay == 0) {
                if (ScreenTransition_StartFadeIn(sSceneFadeInType, 0xf, 0) == 0) {
                    sSceneFadeInDelay = 1;
                }
            }
        }
    }
    return TRUE;
}

BOOL SceneBase::postExecute(u32 status) { return ProcBase::postExecute(status); }

BOOL SceneBase::preDraw() {
    if (ProcBase::preDraw()) {
        return TRUE;
    }
    return FALSE;
}

BOOL SceneBase::postDraw(s32 status) { return ProcBase::postDraw(status); }

extern "C" void Scene_Request(u32 a, u32 b, u32 c, u32 d) {
    gNextSceneProfile = a;
    sSceneFadeOutType = b;
    sSceneFadeInType = c;
}

extern "C" void Scene_RequestBoot(void) {
    gNextSceneProfile = 1;
    sSceneFadeOutType = 3;
    sSceneFadeInType = 3;
    sSceneExists = 0;
}

extern "C" BOOL Scene_CreateRequested(void) {
    if (sSceneExists != 0 || gNextSceneProfile == 0xd8) {
        return FALSE;
    }
    if (gNextSceneProfile == 2) {
        OS_ResetSystem(1);
    }
    ProcBase *r = GameProc_CreateChild(gNextSceneProfile, gGameRoot, 0, 2);
    if (r != NULL) {
        gNextSceneProfile = 0xd8;
        sSceneExists = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" void Scene_CheckExit(ProcBase *p) {
    if (gSoftResetRequested != 0) {
        u8 m = gScreenTransition.state;
        if (Unk_020a42c4_IsTwo(m) == 0) {
            if (Unk_020a42c4_IsZero(m) != 0) {
                Scene_Request(0xd4, 0, 0, 0);
                ProcBase_RequestDelete(p);
                TalkRequestQueue_Reset();
                CharInteractSync_Reset();
            }
        }
    } else if (gNextSceneProfile != 0xd8) {
        u8 m = gScreenTransition.state;
        if (Unk_020a42c4_IsTwo(m) == 0) {
            if (data_021c3cb8 == 0) {
                if (Unk_020a42c4_IsZero(m) != 0) {
                    if (gCommManager->isSlotActive(gCommManager->myAid) != 0) {
                        switch (NetArea_GetMoveState()) {
                        case 5:
                            ProcBase_RequestDelete(p);
                            NetArea_SetMoveState(6);
                            break;
                        case 12:
                            ProcBase_RequestDelete(p);
                            NetArea_SetMoveState(0xd);
                            break;
                        }
                    } else {
                        ProcBase_RequestDelete(p);
                    }
                }
            }
        }
    }
}


ProcBase *gActorDefaultParent;
u8 sSceneFadeOutType;
volatile u8 sSceneFadeInDelay;
u8 gSceneCreating;
u8 sSceneExists = 1;
u8 data_021eda50;


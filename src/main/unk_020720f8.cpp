#include "uptr.h"
#include "types.h"
#include "sdk_linker_symbols.h"


#include "net/CommManager.h"
#include "save/PatternOrder.h"
#include "save/EncodedName8.h"
#include "sys/OverlayHandle.h"
#include "save/Unk_020942c8.h"
#include "save/Pattern.h"
#include "talk/EncodedString16Buf.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "sys/Heap.h"
#include "net/FriendEntry.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_0203e7d0.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/main/unk_0206f804.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098d20.h"
#include "proto/main/unk_0209c3e0.h"
#include "proto/main/unk_0209c4a8.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020a6388.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/main/unk_020b7190.h"

extern SaveData gSaveData;

enum Unk_020720f8_Id { Unk_020720f8_Id_0 = 0 };

struct CommRecordUnpackLocals {
    u8 a;
    u8 b;
    u8 buf[5];
};
struct CommDeferredFlushLocals {
    u8 a;
    u8 b;
    u8 buf[5];
    u8 buf3[5];
    u8 buf2[5];
};




namespace n4 {
extern "C" {
extern CommManager *const gCommManager;
}
extern "C" {
void MI_CpuFill8(void *, u32, u32);
}
extern "C" {
FriendEntry *FriendList_GetEntries(FriendEntry *p);
}
extern "C" {
void MI_CpuCopy8(const void *, void *, u32);
}
extern "C" {
s32 Scene_GetCurrent();
}
extern "C" {
void OS_EnableInterrupts();
}
extern "C" {
void OS_DisableInterrupts();
}
extern "C" {
void DC_FlushAll(u32);
}
extern "C" {
void VillagerStates_ResetRuntime();
}
extern "C" {
u16 Item_MakeBuilding(u32 x);
}
extern "C" {
void ReddPassword_ForgetVisitor();
}

extern "C" void Comm_ResetPeerState(s32 r4) {
    if (r4 == 4) {
        VillagerStates_ResetRuntime();
        TownSessionState_Reset(TownSessionState_Get());
    }
    RoomFtrState_ResetAll();
    RoomObjSync_Reset();
    BuildingStates_Reset();
    CharInteractSync_Reset();
    CommSub_ResetPostReply();
    if (r4 < 0) {
        CommManager *o = gCommManager;
        if ((o)->isMyAid(0) != 0 || (o)->isMyAid(4) != 0) {
            if (r4 == -4) {
                for (u32 i = 0; i < 0x22; i++) {
                    u16 r6 = Item_MakeBuilding(i);
                    BuildingOccupancy_Leave(r6, 1);
                    BuildingOccupancy_Leave(r6, 2);
                    BuildingOccupancy_Leave(r6, 3);
                }
                SpotSync_Release(1);
                SpotSync_Release(2);
                SpotSync_Release(3);
                for (u32 i = 0; i < 0x33; i++) {
                    u32 r6 = (u8)i;
                    RoomEntry_Leave(r6, 1);
                    RoomEntry_Leave(r6, 2);
                    RoomEntry_Leave(r6, 3);
                }
            } else {
                s32 r6 = -r4;
                for (u32 i = 0; i < 0x22; i++) {
                    BuildingOccupancy_Leave(Item_MakeBuilding(i), r6);
                }
                SpotSync_Release(r6);
                for (u32 i = 0; i < 0x33; i++) {
                    RoomEntry_Leave((u8)i, r6);
                }
            }
        }
    }
    if (r4 < 0) {
        if (r4 == -4) {
            for (u32 i = 0; i < 4; i++) {
                PlayerSession_ResetLastState(i);
            }
        } else {
            PlayerSession_ResetLastState(-r4);
        }
    }
    if (r4 == -4) {
        ReddPassword_ForgetVisitor();
    }
    if ((r4 < 0 ? -r4 : r4) < 4) {
        if (r4 < 0) r4 = -r4;
        (gCommManager)->resetNoAckFrames(r4);
    }
}
extern "C" void Comm_EnterCritical() {
    OS_DisableInterrupts();
}
extern "C" void Comm_LeaveCritical() {
    OS_EnableInterrupts();
}
extern "C" void Comm_OnReceive(u32 a, u8 *b, u32 c) {
    DC_FlushAll(a);
    s32 r2 = CommPacket_GetAck(b);
    if (r2 != 0) {
        (gCommManager)->addSendCredit(a, r2);
    }
    if (CommPacket_IsControl(b) != 0) {
        s32 r3 = CommPacket_GetType(b);
        if (r3 < 0x18) {
            CommCtrl_Dispatch(b + 1, c - 1, a, r3);
        }
    } else {
        (gCommManager)->resetNoAckFrames(a);
        if (c > 1) {
            CommManager *o = gCommManager;
            (o)->setRecvLen(a, (o)->getRecvWriteSlot(a), c);
            (o)->pushRecvSlot(a);
            u8 *r4 = o->getRecvBuf(a, o->getRecvWriteSlot(a));
            NetOverlay_AssertAny();
            Net_SetRecvBuffer((u16)a, r4, 0x1000);
        }
    }
}
extern "C" s32 Comm_IsSeqAtOrBefore(s32 a, s32 b) {
    if (b < 0) return 0;
    if (a < 0) return 1;
    s32 d = a - b;
    if (d != 0) {
        if (d > 0x3fff) {
            d -= 0x7fff;
        } else if (d < -0x3fff) {
            d = 0x7fff - d;
        }
        if (d > 0) return 0;
    }
    return 1;
}
extern "C" s32 Comm_IsSeqConfirmed(s32 a) {
    return Comm_IsSeqAtOrBefore(a, gCommManager->getConfirmedSeq());
}
extern "C" void Comm_WriteAckHeaders() {
    s32 i = 3;
    CommManager *o = gCommManager;
    for (; i >= 0; i--) {
        if ((o)->isSlotActive(i)) {
            if ((o)->isMyAid(i) == 0) {
                u8 *p = o->getSendBuf(i);
                CommPacket_SetAckHeader(p, o->getAckCount(i));
            }
        }
    }
}
extern "C" s32 Comm_WriteSyncVars(u8 *dst, void *src, s32 n) {
    if (src == 0) {
        s32 cnt = 0;
        s32 i = 0x45;
        CommManager *o = gCommManager;
        for (; i >= 0; i--) {
            if ((o)->isSyncVarDirty(i)) {
                u8 tmp;
                tmp = i;
                MI_CpuCopy8(&tmp, dst, 1);
                dst++;
                cnt++;
                void *p = (o)->getSyncVar(i);
                s32 sz = CommSyncVar_GetVarSize(i);
                MI_CpuCopy8(p, dst, sz);
                dst += sz;
                cnt += sz;
            }
        }
        *dst = 0x46;
        return cnt + 1;
    }
    MI_CpuCopy8(src, dst, n);
    return n;
}
extern "C" u32 Comm_CollectRecordsFor(u8 *dst, u32 id) {
    u32 r7 = 0;
    u32 size, l0c, l14;
    CommManager *o;
    u8 a[8];
    o = gCommManager;
    size = (o)->getSendQueueLen();
    u8 *r5 = (u8 *)(o)->getSendQueueBuf();
    u32 r6 = 0;
    while (r6 < size) {
        MI_CpuCopy8(r5, a + 3, 5);
        l0c = a[6];
        CommRecord_UnpackSource(a + 7, a, a + 1);
        u32 r4 = CommRecord_GetLength(a + 3);
        Scene_GetCurrent();
        u32 r = NetArea_ResolveRoute(id, l0c, a[0], a + 2);
        if (a[2] != 0) {
            l14 = (o)->getDeferredLen();
            u8 *d2 = (u8 *)(o)->getDeferredBuf() + l14;
            MI_CpuCopy8(r5, d2, r4 + 5);
            l14 += r4 + 5;
            (o)->setDeferredLen(l14);
        } else if (r == id) {
            MI_CpuCopy8(r5, dst, r4 + 5);
            dst += r4 + 5;
            r7 += r4 + 5;
        }
        r5 += r4 + 5;
        r6 += r4 + 5;
    }
    return r7;
}
extern "C" s32 Comm_IsSyncFinished(u32 a) {
    u32 v = NetSession_GetSyncState(a);
    if (v - 5 <= 1) return 1;
    return 0;
}
extern "C" s32 Comm_WriteSyncReply(u32 a) {
    s32 r5 = 0;
    if (Comm_IsSyncFinished(a)) {
        u8 *r6 = (u8 *)(gCommManager)->getSendBuf(a);
        CommPacket_SetHeader(r6, r5, 6);
        u32 r4 = NetSession_GetSyncState(a);
        u32 t = Comm_GetMemberMask();
        r6[1] = (r4 & 7) | ((t << 4) & 0xf0);
        r5 += 2;
    }
    return r5;
}
extern "C" void Comm_RemoveMember(s32 a) {
    s32 i = 3;
    CommManager *o = gCommManager;
    for (; i >= 0; i--) {
        if ((o)->isSlotActive(i)) {
            if (i == 0) {
                NetArea_SetSlotStatus(0, 0x3f, 1, 0, 2);
            } else {
                NetArea_SetSlotStatus(i, 0x3f, 0, 0, 2);
            }
        }
    }
    NetArea_SetSlotStatus(a, 0x3f, 0, 0, 7);
    o = gCommManager;
    (o)->setSlotActive(a, 0);
    (o)->setMemberCount((u8)(o->memberCount - 1));
    (o)->resetSendCredit(a);
    (o)->setAckCount(a, 0);
    NetSession_RemoveSlot(a);
    Comm_ResetPeerState(-a);
}
extern "C" void Comm_CreateHeap(Heap *a) {
    u32 r5 = 0;
    for (s32 i = 0x45; i >= 0; i--) {
        u32 v = CommSyncVar_GetVarSize(i);
        if (v > r5) r5 = v;
    }
    gCommManager->maxSyncVarSize = r5;
    NetHeap_Create(0x4b000, a);
    Net_OnHeapCreatedNop();
}
extern "C" void Comm_Start(s32 a, u32 b, u32 c) {
    CommManager *o = gCommManager;
    o->started = 1;
    CommSyncVar_Init();
    o->syncCompareBuf = NetHeap_Alloc(o->maxSyncVarSize, 4);
    (o)->setSendBufs((u8 *)(NetHeap_Alloc(0x3000, 4)));
    (o)->setRecvBufs((u8 *)(NetHeap_Alloc(0x9000, 4)));
    (o)->setRecordBuf((u8 *)(NetHeap_Alloc(0x92e, 4)));
    (o)->setSendQueueBuf((u8 *)(NetHeap_Alloc(0x92e, 4)));
    (o)->setDeferredBuf((u8 *)(NetHeap_Alloc(0x92e, 4)));
    (o)->setHeldBuf((u8 *)(NetHeap_Alloc(0x92e, 4)));
    (o)->setLoopbackBuf((u8 *)(NetHeap_Alloc(0x92e, 4)));
    o->setAuxBufA((u8 *)NetHeap_Alloc(0xc00, 4));
    o->setAuxBufB((u8 *)NetHeap_Alloc(0xc00, 4));
    NetOverlay_AssertAny();
    Net_Init(0x41444d45, 0x400040, 1, 0x4fe752, b, (NetAllocFn)NetHeap_Alloc, NetHeap_Free);
    if ((u8)(a + 0xff) <= 1) {
        NetOverlay_AssertWireless();
        Net_StartLocal(a, Comm_OnReceive);
    } else {
        CommManager *p = gCommManager;
        u8 *r5 = (u8 *)(p)->getWifiFriendList();
        u8 *r6 = (u8 *)(p)->getWifiUserData();
        MI_CpuFill8(r5, 0, 0x3e0);
        MI_CpuFill8(r6, 0, 0x50);
        PlayerData *l18 = PlayerData_GetCurrent();
        FriendEntry *l1c = FriendList_GetEntries((FriendEntry *)l18->getFriendList());
        for (s32 i = 0; i < 0x20; i++) {
            MI_CpuCopy8(DwcFriendData_GetBytes(FriendEntry_GetFriendData(l1c)), r5 + i * 12, 12);
            l1c++;
        }
        MI_CpuCopy8(((PlayerId *)(l18->getPlayerId()))->getName(), r6, 8);
        MI_CpuCopy8(TownId_GetName((u16 *)gSaveData.townId), r6 + 8, 8);
        MI_CpuCopy8(PlayerWifiData_GetDwcUserData(l18->getWifiUserData()), r6 + 0x10, 0x40);
        NetOverlay_AssertWifi();
        Net_StartWifi(a, Comm_OnReceive, (NetFriendFn)Comm_OnFriendDeletedNop, r6, r5);
    }
    (o)->setErrorMode(c);
}
extern "C" void Comm_StartOv067Mode() {
    gCommManager->started = 1;
    NetOverlay_AssertAny();
    Net_Init(0x41444d45, 0x400083, 1, 0x4fe752, 2, (NetAllocFn)NetHeap_Alloc, NetHeap_Free);
}
extern "C" s32 Comm_End() {
    s32 r5 = 1;
    if (gCommManager->started != 0) {
        Heap *r4 = gNetHeap;
        u32 r6 = r4->setFlags(0x8000);
        r4->setFlags(r6 | 0x2000);
        NetOverlay_AssertAny();
        if (Net_Shutdown() == 0) {
            Comm_ReportShutdownError();
            r5 = 0;
        }
        r4->setFlags(r6);
        CommManager *o = gCommManager;
        NetHeap_Free(o->getAuxBufB());
        o->setAuxBufB(NULL);
        NetHeap_Free(o->getAuxBufA());
        o->setAuxBufA(NULL);
        NetHeap_Free((o)->getLoopbackBuf());
        (o)->setLoopbackBuf((u8 *)(0));
        NetHeap_Free((o)->getHeldBuf());
        (o)->setHeldBuf((u8 *)(0));
        NetHeap_Free((o)->getDeferredBuf());
        (o)->setDeferredBuf((u8 *)(0));
        NetHeap_Free((o)->getSendQueueBuf());
        (o)->setSendQueueBuf((u8 *)(0));
        NetHeap_Free((o)->getRecordBuf());
        (o)->setRecordBuf((u8 *)(0));
        NetHeap_Free((o)->getRecvBuf(4, 0));
        (o)->setRecvBufs((u8 *)(0));
        NetHeap_Free((o)->getSendBuf(4));
        (o)->setSendBufs((u8 *)(0));
        NetHeap_Free(o->syncCompareBuf);
        o->syncCompareBuf = 0;
        NetHeap_Free((o)->getSyncVarBuf());
        (o)->setSyncVarBuf((u8 *)(0));
        (o)->reset();
        o->started = 0;
    }
    return r5;
}
extern "C" void Comm_EndOv067Mode() {
    if (gCommManager->started != 0) {
        Heap *const r5 = gNetHeap;
        u32 r4 = r5->setFlags(0x8000);
        r5->setFlags(r4 | 0x2000);
        NetOverlay_AssertAny();
        if (Net_Shutdown() == 0) {
            Comm_ReportShutdownError();
        }
        r5->setFlags(r4);
        CommManager *o = gCommManager;
        (o)->reset();
        o->started = 0;
    }
}
extern "C" void Comm_DestroyHeap() {
    Net_OnHeapDestroyNop();
    NetHeap_Destroy();
}
extern "C" void Comm_ProcessReceived(s32 x) {
    if (x == 0) {
        CommManager *o = gCommManager;
        if ((o)->isSlotActive(o->myAid)) {
            if ((o)->getMode()) {
                o = gCommManager;
                (o)->dispatchHeld();
                (o)->dispatchLoopback();
                (o)->processReceived();
            }
        }
    }
}
}

namespace n5 {
extern "C" {
extern CommManager *const gCommManager;
}

extern "C" void Comm_Update(s32 a) {
    CommManager *g = gCommManager;
    s32 self = g->myAid;
    u32 mode;
    u32 saved;
    u8 *first;
    s32 flen;
    u8 *p3;
    BOOL ok;
    s32 i;
    u8 *bufs[3];
    u32 lens[3];
    u16 masks[3];
    u8 *bufs2[3];
    u32 lens2[3];
    u16 masks2[3];
    u32 lens3[3];
    u16 masks3[3];
    u8 *bufs3[3];

    if (!g->isSlotActive(self)) {
        return;
    }
    ok = g->isSendReady();
    if (ok) {
        s16 t = g->getSentSeq();
        if (t >= 0) {
            CommManager *o = gCommManager;
            o->setConfirmedSeq(t);
            o->clearSentSeq();
        }
    }
    if (ok) {
        if (g->getPendingMode() == 1) {
            CommManager *o = gCommManager;
            o->setMode(1);
            o->setPendingMode(3);
        }
    }
    mode = g->getMode();
    if (mode != 0) {
        u32 n = g->getRecordLen();
        if (n != 0) {
            CommManager *o = gCommManager;
            u32 fl = o->getErrorFlags();
            if (Comm_QueueRecords(o, o->getRecordBuf(), n)) {
                g->resetRecordBuf();
                if (fl & 2) {
                    if (!CommCaution_IsShutDown()) {
                        g->setErrorFlags(fl ^ 2);
                    }
                }
            } else {
                if (!(fl & 2)) {
                    g->setErrorFlags(fl | 2);
                }
            }
        }
    }
    if (ok) {
        if (mode == 2) {
            if (Comm_HasSendCreditAll()) {
                saved = g->getDeferredLen();
                Comm_WriteAckHeaders();
                first = NULL;
                flen = 0;
                func_02133ef8(bufs, 12);
                func_02133ef8(lens, 12);
                func_02133ef8(masks, 6);
                for (i = 3; i >= 0; i--) {
                    if (g->isSlotActive(i)) {
                        if (!g->isMyAid(i)) {
                            u8 *p = g->getSendBuf(i);
                            u32 len = 0;
                            p++;
                            len++;
                            if (first == NULL) {
                                first = p;
                                flen = Comm_WriteSyncVars(p, NULL, 0);
                                p += flen;
                                len += flen;
                            } else {
                                Comm_WriteSyncVars(p, first, flen);
                                p += flen;
                                len += flen;
                            }
                            len += Comm_CollectRecordsFor(p, i);
                            u32 idx = Comm_AidToPeerIndex(i);
                            bufs[idx] = g->getSendBuf(i);
                            lens[idx] = len;
                            masks[idx] = 1 << i;
                        } else {
                            u32 c = g->getLoopbackLen();
                            u32 r = Comm_CollectRecordsFor(g->getLoopbackBuf() + c, i);
                            if (r != 0) {
                                c += r;
                                g->setLoopbackLen(c);
                            }
                        }
                    } else {
                        if (g->isMyAid(0)) {
                            s32 r = Comm_WriteSyncReply(i);
                            if (r != 0) {
                                s32 idx = i - 1;
                                bufs[idx] = g->getSendBuf(i);
                                lens[idx] = r;
                                masks[idx] = 1 << i;
                            }
                        }
                    }
                }
                BOOL sent = g->sendPackets(bufs[0], lens[0], masks[0], bufs[1], lens[1], masks[1], bufs[2], lens[2], masks[2]);
                if (sent || g->memberCount <= 1) {
                    CommManager *o = gCommManager;
                    o->setSentSeq(o->getSendSeq());
                    o->clearSyncVarDirty();
                    o->resetSendQueueLen();
                    for (i = 3; i >= 0; i--) {
                        if (g->isSlotActive(i)) {
                            if (!g->isMyAid(i)) {
                                Comm_EnterCritical();
                                g->subSendCredit(i, 1);
                                Comm_LeaveCritical();
                                g->setAckCount(i, 0);
                            }
                        } else if (sent) {
                            if (g->isMyAid(0)) {
                                if (Comm_IsSyncFinished(i)) {
                                    NetSession_SetSyncState(i, 7);
                                }
                            }
                        }
                    }
                    if (NetArea_GetMoveState() == 7) {
                        NetArea_SetMoveState(8);
                    }
                } else {
                    g->setDeferredLen(saved);
                }
            } else {
                if (ok) {
                    Comm_WriteAckHeaders();
                    func_02133ef8(bufs2, 12);
                    func_02133ef8(lens2, 12);
                    func_02133ef8(masks2, 6);
                    s32 cnt = 0;
                    for (i = 3; i >= 0; i--) {
                        if (g->isSlotActive(i) && !g->isMyAid(i)) {
                            u8 *p = g->getSendBuf(i);
                            if (CommPacket_GetAck(p)) {
                                bufs2[cnt] = p;
                                lens2[cnt] = 1;
                                masks2[cnt] = 1 << i;
                                cnt++;
                            }
                        }
                    }
                    if (cnt != 0) {
                        if (g->sendPackets(bufs2[0], lens2[0], masks2[0], bufs2[1], lens2[1], masks2[1], bufs2[2], lens2[2], masks2[2]) || g->memberCount <= 1) {
                            for (i = 3; i >= 0; i--) {
                                if (g->isSlotActive(i) && !g->isMyAid(i)) {
                                    g->setAckCount(i, 0);
                                }
                            }
                        }
                    } else {
                        if (g->isMyAid(0)) {
                            if (g->memberCount != 4) {
                                Comm_SendEmpty();
                            }
                        }
                    }
                } else {
                    if (g->isMyAid(0)) {
                        if (g->memberCount != 4) {
                            Comm_SendEmpty();
                        }
                    }
                }
            }
        } else if (mode == 1) {
            if (g->isOnline()) {
                NetOverlay_AssertAny();
                if (Net_IsReadyToSend()) {
                    func_02133ef8(lens3, 12);
                    func_02133ef8(masks3, 6);
                    func_02133ef8(bufs3, 12);
                    for (i = 3; i >= 0; i--) {
                        if (g->isSlotActive(i) && !g->isMyAid(i)) {
                            u32 v = g->getAckCount(i);
                            u32 idx = Comm_AidToPeerIndex(i);
                            if (v != 0) {
                                p3 = &sCommAckPackets[idx];
                                CommPacket_SetHeader(p3, v, 0x18);
                                bufs3[idx] = p3;
                                lens3[idx]++;
                                masks3[idx] = 1 << i;
                            }
                        }
                    }
                    if (g->sendPackets(bufs3[0], lens3[0], masks3[0], bufs3[1], lens3[1], masks3[1], bufs3[2], lens3[2], masks3[2])) {
                        for (i = 3; i >= 0; i--) {
                            if (g->isSlotActive(i) && !g->isMyAid(i)) {
                                g->setAckCount(i, 0);
                            }
                        }
                    }
                }
            }
        }
    }
    if (mode == 2) {
        Comm_EnterCritical();
        CommManager *o = gCommManager;
        Comm_CountNoAckFrames(o);
        Comm_LeaveCritical();
        Comm_EnterCritical();
        BOOL r = Comm_AnyPeerTimedOut();
        Comm_LeaveCritical();
        u32 fl = o->getErrorFlags();
        if (r) {
            if (!(fl & 1)) {
                g->setErrorFlags(fl | 1);
            }
        } else {
            if (fl & 1) {
                if (!CommCaution_IsShutDown()) {
                    g->setErrorFlags(fl ^ 1);
                }
            }
        }
        if (self == 0) {
            u16 m = 0;
            for (i = 3; i >= 0; i--) {
                if (g->isSlotActive(i) && !g->isMyAid(i)) {
                    m |= 1 << i;
                }
            }
            u32 x = Net_GetConnectedMask();
            if (m != (m & x)) {
                u32 f = g->getErrorFlags();
                if (!(f & 4)) {
                    g->setErrorFlags(f | 4);
                }
            }
        } else {
            NetOverlay_AssertAny();
            if (!Net_PollConnected()) {
                u32 f = g->getErrorFlags();
                if (!(f & 8)) {
                    g->setErrorFlags(f | 8);
                }
            }
        }
    }
    if (a == 0) {
        g->incSendSeq();
    }
}
}

namespace n3 {
extern "C" {
s32 Scene_GetCurrent();
}
extern "C" {
extern CommManager *const gCommManager;
}

extern "C" BOOL Comm_SendEmpty() { return gCommManager->sendPackets(0, 0, 0, 0, 0, 0, 0, 0, 0); }
extern "C" void Comm_SetRecvBuffersAsHost() { Comm_SetRecvBuffers(0); }
extern "C" void Comm_BeginHostSession() {
    CommManager *o = gCommManager;
    o->setMode(2);
    o->myAid = 0;
    o->setSlotActive(o->myAid, 1);
    Comm_SetRecvBuffers(0);
    NetSession_OnBeginHost();
    NetArea_SetSlotStatus(0, Scene_GetCurrent(), 1, 0, 7);
}
extern "C" void Comm_PrepareJoin(u32 a) {
    gCommManager->setMode(0);
    Comm_SetRecvBuffers(a);
}
extern "C" void Comm_ResetNetSession() { NetSession_Reset(); }
extern "C" void Comm_SetRecvBuffers(u32 a) {
    s32 i = 3;
    CommManager *g = gCommManager;
    for (; i >= 0; i--) {
        if (i < a) {
            u8 *p = g->getRecvBufByPeer(i, 0);
            NetOverlay_AssertAny();
            Net_SetRecvBuffer(i, p, 0x1000);
        } else if (i > a) {
            u8 *p = g->getRecvBufByPeer(i - 1, 0);
            NetOverlay_AssertAny();
            Net_SetRecvBuffer(i, p, 0x1000);
        }
    }
}
extern "C" BOOL Comm_RequestSync(u8 a) {
    u8 tmp;
    CommManager *o = gCommManager;
    s32 idx = o->myAid;
    if (!o->isSlotActive(idx)) {
        NetSession_SetSyncState(3, 4);
        o = gCommManager;
        u8 *p = o->getSendBuf(4);
        CommPacket_SetHeader(p, 0, 5);
        p[1] = 0;
        return o->sendPackets(o->getSendBuf(4), 2, 1, 0, 0, 0, 0, 0, 0);
    }
    if (o->isMyAid(0)) {
        NetSession_SetSyncState(idx, a);
    } else {
        NetSession_SetSyncState(idx, 4);
        tmp = a;
        o = gCommManager;
        o->beginRecord();
        o->writeRecord(&tmp, 1);
        o->endRecord(0, 0);
    }
    return TRUE;
}
extern "C" s32 Comm_GetSyncState() {
    s32 a = gCommManager->myAid;
    if (!gCommManager->isSlotActive(a)) {
        return NetSession_GetSyncState(3);
    }
    return NetSession_GetSyncState(a);
}
extern "C" void Comm_ClearSyncState() {
    s32 a = gCommManager->myAid;
    if (!gCommManager->isSlotActive(a)) {
        NetSession_SetSyncState(3, 7);
    } else {
        NetSession_SetSyncState(a, 7);
    }
}
extern "C" u32 Comm_GetRemoteMask() {
    u32 r = 0;
    s32 i = 3;
    CommManager *o = gCommManager;
    for (; i >= 0; i--) {
        if (o->isSlotActive(i) && !o->isMyAid(i)) {
            r |= (u8)(1 << i);
        }
    }
    return r;
}
extern "C" u32 Comm_GetMemberMask() {
    u32 r = Comm_GetRemoteMask();
    CommManager *o = gCommManager;
    s32 i = o->myAid;
    if (i < 4) {
        r |= (u16)(1 << i);
    }
    return r;
}
extern "C" s32 Comm_Shutdown() {
    Comm_ResetNetSession();
    return Comm_End();
}
extern "C" void Comm_SetLostFlag() {
    CommManager *o = gCommManager;
    u32 v = o->getErrorFlags();
    if ((v & 0x40) == 0) {
        o->setErrorFlags(v | 0x40);
    }
}
extern "C" BOOL Comm_IsConnectionLost(s32 a) {
    CommManager *o = gCommManager;
    u32 n = o->getSendRetryLimit();
    if (n != 0) {
        if (o->isSendReady()) {
            o = gCommManager;
            o->setSendRetry(0);
            o->setSendRetryLimit(0);
        } else {
            u32 c = o->getSendRetry();
            if (c >= n) {
                return TRUE;
            }
            o->setSendRetry((u16)(c + 1));
        }
    }
    if (a >= 0) {
        u16 h = a;
        if (Net_GetMyAid()) {
            if (a <= 0) {
                goto zero;
            }
            NetOverlay_AssertAny();
            if (Net_PollConnected()) {
                goto zero;
            }
            return TRUE;
        }
        u32 m = Net_GetConnectedMask();
        if (h == (h & m)) {
            goto zero;
        }
        return TRUE;
    }
    if (Net_GetConnectedMask() != 0) {
        goto zero;
    }
    return TRUE;
zero:
    return FALSE;
}
}
CommManager::CommManager() {
    using namespace n3; init(); }
CommManager::~CommManager() {
    using namespace n3;}
void CommManager::init() {
    using namespace n3;
    initLocal();
    reset();
}
void CommManager::initLocal() {
    using namespace n3;
    localSlot = 4;
    clearMemberCount();
    setLatchedErrorFlags(0);
    setErrorFlags(0);
}
void CommManager::reset() {
    using namespace n3;
    clearSlotsActive();
    setMode(0);
    setPendingMode(3);
    resetSendCredits();
    clearAckCounts();
    clearRecvRings();
    myAid = 4;
    clearSyncVarDirty();
    resetRecordBuf();
    resetSendQueueLen();
    clearDeferredLen();
    clearHeldLen();
    clearLoopbackLen();
    clearAuxLenA();
    clearAuxLenB();
    clearSentSeq();
    clearConfirmedSeq();
    clearNoAckFrames();
    setSendRetry(0);
    setSendRetryLimit(0);
    setErrorMode(0);
}
BOOL CommManager::sendPackets(u8 *a1, u32 a2, u32 a3, u8 *s4, u32 s5, u16 s6, u8 *s7, u32 s8, u16 s9) {
    using namespace n3;
    NetOverlay_AssertAny();
    if (Net_SendPackets3(a1, a2, a3, 0, s4, s5, s6, 0, s7, s8, s9, 0)) {
        if (getMode() != 2) {
            if ((a1 != NULL || s4 != NULL || s7 != NULL) && (a2 != 0 || s5 != 0 || s8 != 0)) {
                if (a1 != NULL && a2 != 0) {
                    CommPacket_IsControl(a1);
                }
                if (s4 != NULL && s5 != 0) {
                    CommPacket_IsControl(s4);
                }
                if (s7 != NULL && s8 != 0) {
                    CommPacket_IsControl(s7);
                }
                setSendRetry(0);
                Comm_IsWifi();
                setSendRetryLimit(0x258);
            }
        } else {
            setSendRetry(0);
            setSendRetryLimit(0);
        }
        return TRUE;
    }
    return FALSE;
}
BOOL CommManager::isSendReady() {
    using namespace n3;
    s32 n = myAid;
    if (isSlotActive(n)) {
        if (n == 0) {
            if (Net_GetMemberCount() > 1) {
                NetOverlay_AssertAny();
                if (Net_IsReadyToSend()) {
                    return TRUE;
                }
                return FALSE;
            }
        } else {
            NetOverlay_AssertAny();
            if (Net_IsReadyToSend()) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return TRUE;
}
void CommManager::setSlotActive(s32 i, u32 v) {
    using namespace n3; slotActive[i] = v; }
u32 CommManager::isSlotActive(s32 i) {
    using namespace n3;
    if (i < 4) {
        return slotActive[i];
    }
    return 0;
}
void CommManager::clearSlotsActive() {
    using namespace n3;
    for (s32 i = 3; i >= 0; i--) {
        setSlotActive(i, 0);
    }
}
BOOL CommManager::isOnline() {
    using namespace n3;
    if (isSlotActive(myAid) && memberCount >= 2) {
        return TRUE;
    }
    return FALSE;
}
s16 CommManager::getSendSeq() {
    using namespace n3; return (s16)(sendSeq & 0x7fff); }
void CommManager::incSendSeq() {
    using namespace n3; sendSeq = sendSeq + 1; }
void CommManager::setMode(u32 v) {
    using namespace n3; mode = v; }
u8 CommManager::getMode() {
    using namespace n3; return mode; }
void CommManager::setPendingMode(u32 v) {
    using namespace n3; pendingMode = v; }
u8 CommManager::getPendingMode() {
    using namespace n3; return pendingMode; }
void CommManager::setSendBufs(u8 *p) {
    using namespace n3; sendBufs = p; }
u8 *CommManager::getSendBuf(s32 i) {
    using namespace n3;
    if (i >= 4) {
        return sendBufs;
    }
    if (isMyAid(i)) {
        return NULL;
    }
    if (i < myAid) {
        return sendBufs + (i << 12);
    }
    return sendBufs + ((i - 1) << 12);
}
u32 CommManager::getSendCredit(s32 a) {
    using namespace n3; return sendCredits[Comm_AidToPeerIndex(a)]; }
void CommManager::addSendCredit(s32 a, u32 b) {
    using namespace n3; sendCredits[Comm_AidToPeerIndex(a)] += b; }
void CommManager::subSendCredit(s32 a, u32 b) {
    using namespace n3; sendCredits[Comm_AidToPeerIndex(a)] -= b; }
void CommManager::resetSendCredit(s32 a) {
    using namespace n3; sendCredits[Comm_AidToPeerIndex(a)] = 3; }
void CommManager::resetSendCredits() {
    using namespace n3;
    u32 *p = sendCredits;
    for (s32 i = 2; i >= 0; i--) {
        *p++ = 3;
    }
}

namespace n2 {
extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
}
extern "C" {
s32 Scene_GetCurrent();
}
extern "C" {
extern CommManager *const gCommManager;
}

}
u32 CommManager::getAckCount(s32 a) {
    using namespace n2; return ackCounts[Comm_AidToPeerIndex(a)]; }
void CommManager::setAckCount(s32 a, u32 v) {
    using namespace n2; ackCounts[Comm_AidToPeerIndex(a)] = v; }
void CommManager::incAckCount(s32 a) {
    using namespace n2; ackCounts[Comm_AidToPeerIndex(a)] += 1; }
void CommManager::clearAckCounts() {
    using namespace n2;
    s32 i;
    u32 *p = ackCounts;
    for (i = 2; i >= 0; i--) *p++ = 0;
}
u8 *CommManager::getRecvBuf(s32 a, s32 b) {
    using namespace n2;
    if (a >= 4) return recvBufs;
    if (isMyAid(a)) return 0;
    if (a < myAid) {
        return recvBufs + ((b + a * 3) << 12);
    }
    return recvBufs + ((b + (a - 1) * 3) << 12);
}
u8 *CommManager::getRecvBufByPeer(s32 a, s32 b) {
    using namespace n2;
    return recvBufs + ((b + a * 3) << 12);
}
void CommManager::setRecvBufs(u8 *v) {
    using namespace n2; recvBufs = v; }
u32 CommManager::getRecvLen(s32 a, u32 b) {
    using namespace n2;
    return unk_28[Comm_AidToPeerIndex(a)].v[b];
}
void CommManager::setRecvLen(s32 a, u32 b, u32 c) {
    using namespace n2;
    unk_28[Comm_AidToPeerIndex(a)].v[b] = c;
}
void CommManager::clearRecvLen(s32 a, u32 b) {
    using namespace n2; setRecvLen(a, b, 0); }
void CommManager::clearRecvRings() {
    using namespace n2;
    u32 *p = (u32 *)&unk_28[0];
    s32 i;
    for (i = 4; i >= 0; i--) {
        *p++ = 0;
    }
    clearRecvRingIndices();
}
void CommManager::processReceived() {
    using namespace n2;
    s32 outer;
    u32 i;
    u32 x;
    u32 lim;
    s32 cc;
    u32 k;
    u32 bb;
    u32 dbg;
    u32 len;
    CommManager *g;
    u32 rem;
    u32 n;
    u32 t;
    u8 *p;
    u16 j;
    u8 c;
    u8 a, b;
    u8 buf[5];
    outer = 2;
    g = gCommManager;
    do {
        for (i = 0; i < 4; i++) {
            if (isMyAid(i)) continue;
            x = getRecvReadSlot(i);
            if (x >= 3) continue;
            lim = getRecvLen(i, x) - 1;
            p = getRecvBuf(i, x) + 1;
            j = 0;
            do {
                MI_CpuCopy8(p, &c, 1);
                p++;
                j = (u16)(j + 1);
                cc = c;
                if (cc >= 0x46) break;
                n = CommSyncVar_GetVarSize(c);
                MI_CpuCopy8(p, getSyncVar(cc), n);
                p += n;
                j = (u16)(j + n);
            } while (j < lim);
            k = 0;
            rem = (u16)(lim - j);
            while (k < rem) {
                MI_CpuCopy8(p, buf, 5);
                p += 5;
                k += 5;
                t = buf[3];
                CommRecord_UnpackSource(&buf[4], &a, &b);
                bb = b;
                dbg = Scene_GetCurrent();
                len = CommRecord_GetLength(buf);
                if (NetArea_IsSlotMoving(myAid) && t == 7 && a != dbg) {
                    t = getHeldLen();
                    u8 *dd = getHeldBuf() + t;
                    MI_CpuCopy8(p - 5, dd, len + 5);
                    u32 nf = t; nf += len + 5; setHeldLen(nf);
                } else {
                    if (NetArea_IsLocalOwner() == 0 && t == 6) {
                    } else if (t == 6 && a != dbg) {
                    } else if (t == 7 && a != dbg) {
                    } else {
                        CommRecv_Dispatch(buf[2], p, len, t, a, bb);
                    }
                }
                p += len;
                k += len;
            }
            Comm_EnterCritical();
            g->clearRecvLen(i, x);
            g->popRecvSlot(i);
            g->incAckCount(i);
            Comm_LeaveCritical();
        }
        outer--;
    } while (outer >= 0);
}
void CommManager::clearRecvRingIndices() {
    using namespace n2;
    u32 *p = unk_28t.a4c;
    u32 *q = unk_28t.a58;
    s32 i;
    for (i = 2; i >= 0; i--) {
        *p++ = 0;
        *q++ = 0;
    }
}
void CommManager::pushRecvSlot(s32 a) {
    using namespace n2;
    u32 i = Comm_AidToPeerIndex(a);
    unk_28t.a58[i] += 1;
}
void CommManager::popRecvSlot(s32 a) {
    using namespace n2;
    u32 i = Comm_AidToPeerIndex(a);
    unk_28t.a58[i] -= 1;
    u32 t = unk_28t.a4c[i] + 1;
    if (t >= 3) t = 0;
    unk_28t.a4c[i] = t;
}
u32 CommManager::getRecvReadSlot(s32 a) {
    using namespace n2;
    u32 i = Comm_AidToPeerIndex(a);
    if (unk_28t.a58[i] == 0) return 3;
    return unk_28t.a4c[i];
}
u32 CommManager::getRecvWriteSlot(s32 a) {
    using namespace n2;
    u32 i = Comm_AidToPeerIndex(a);
    u32 c = unk_28t.a58[i];
    if (c >= 3) {
        return unk_28t.a4c[i];
    }
    u32 r = c + unk_28t.a4c[i];
    if (r >= 3) r -= 3;
    return r;
}
BOOL CommManager::isMyAid(u32 v) {
    using namespace n2;
    if (v == myAid) return TRUE;
    return FALSE;
}
BOOL CommManager::isLocalSlot(u32 v) {
    using namespace n2;
    if (v == localSlot) return TRUE;
    return FALSE;
}
void CommManager::setMemberCount(u32 v) {
    using namespace n2;
    if (v > 4) {
        memberCount = 0;
        return;
    }
    memberCount = v;
}
void CommManager::clearMemberCount() {
    using namespace n2; setMemberCount(0); }
u8 *CommManager::getSyncVarBuf() {
    using namespace n2; return syncVarBuf; }
void CommManager::setSyncVarBuf(u8 *v) {
    using namespace n2; syncVarBuf = v; }
u8 *CommManager::getSyncVar(u32 i) {
    using namespace n2;
    u8 *p = getSyncVarBuf();
    if (p == 0) return 0;
    return p + CommSyncVar_GetVarOffset(i);
}
u32 CommManager::isSyncVarDirty(s32 i) {
    using namespace n2; return syncVarDirty[i]; }
void CommManager::setSyncVarDirty(s32 i, u32 v) {
    using namespace n2; syncVarDirty[i] = v; }
void CommManager::clearSyncVarDirty() {
    using namespace n2;
    s32 i;
    for (i = 0x45; i >= 0; i--) {
        setSyncVarDirty(i, 0);
    }
}
u8 *CommManager::getRecordBuf() {
    using namespace n2; return recordBuf; }
void CommManager::setRecordBuf(u8 *v) {
    using namespace n2;
    recordBuf = v;
    recordWritePtr = v;
}
void CommManager::resetRecordBuf() {
    using namespace n2;
    setRecordLen(0);
    recordWritePtr = getRecordBuf();
}
void CommManager::setRecordLen(u32 v) {
    using namespace n2; recordLen = v; }
u32 CommManager::getRecordLen() {
    using namespace n2; return recordLen; }
void CommManager::beginRecord() {
    using namespace n2;
    if (((CommManager *)(this))->isOnline()) {
        curRecordStart = recordWritePtr;
        curRecordEnd = recordWritePtr + 5;
    }
}
void CommManager::writeRecord(u8 *p, u32 n) {
    using namespace n2;
    if (((CommManager *)(this))->isOnline()) {
        MI_CpuCopy8(p, curRecordEnd, n);
        curRecordEnd += n;
    }
}
void CommManager::endRecord(u32 a, u32 b) {
    using namespace n2;
    u8 buf[8];
    if (((CommManager *)(this))->isOnline()) {
        if (b - 6 <= 1) {
            NetArea_IsUnsharedScene(Scene_GetCurrent());
        }
        u32 len = curRecordEnd - curRecordStart;
        CommRecord_SetLength(buf, (u16)(len - 5));
        buf[2] = a;
        buf[3] = b;
        CommRecord_PackSource(buf + 4, Scene_GetCurrent(), (u8)myAid);
        MI_CpuCopy8(buf, curRecordStart, 5);
        recordLen += len;
        recordWritePtr = curRecordEnd;
    }
}
u8 *CommManager::getSendQueueBuf() {
    using namespace n2; return sendQueueBuf; }
void CommManager::setSendQueueBuf(u8 *v) {
    using namespace n2; sendQueueBuf = v; }
void CommManager::resetSendQueueLen() {
    using namespace n2; setSendQueueLen(0); }
void CommManager::setSendQueueLen(u32 v) {
    using namespace n2; sendQueueLen = v; }
u32 CommManager::getSendQueueLen() {
    using namespace n2; return sendQueueLen; }
namespace n2 {
extern "C" BOOL Comm_QueueRecords(void *unused, u8 *buf, u32 n) {
    u32 o = gCommManager->getSendQueueLen();
    if (0x92e - o >= n) {
        CommManager *g = gCommManager;
        MI_CpuCopy8(buf, g->getSendQueueBuf() + o, n);
        g->setSendQueueLen(o + n);
        return TRUE;
    }
    return FALSE;
}
}
void CommManager::setReadPtr(u8 *v) {
    using namespace n2; readPtr = v; }
u8 *CommManager::getReadPtr() {
    using namespace n2; return readPtr; }
void CommManager::readRecord(u8 *src, u32 n) {
    using namespace n2;
    u8 *d = getReadPtr();
    MI_CpuCopy8(d, src, n);
    setReadPtr(d + n);
}
u8 *CommManager::getDeferredBuf() {
    using namespace n2; return deferredBuf; }
void CommManager::setDeferredBuf(u8 *v) {
    using namespace n2; deferredBuf = v; }
void CommManager::clearDeferredLen() {
    using namespace n2; setDeferredLen(0); }
void CommManager::setDeferredLen(u32 v) {
    using namespace n2; deferredLen = v; }
u32 CommManager::getDeferredLen() {
    using namespace n2; return deferredLen; }
void CommManager::flushDeferred() {
    using namespace n2;
    CommDeferredFlushLocals l;
    s32 v6 = myAid;
    if (((CommManager *)(this))->isSlotActive(v6)) {
        u32 total = getDeferredLen();
        if (total != 0) {
            u8 *p = getDeferredBuf();
            MI_CpuCopy8(p, l.buf, 5);
            CommRecord_UnpackSource(&l.buf[4], &l.a, &l.b);
            s32 v = NetArea_FindOwner(l.a);
            if (v >= 4) return;
            if (v == v6) {
                u32 c6 = getLoopbackLen();
                u8 *dst = getLoopbackBuf() + c6;
                u32 cnt = 0;
                u32 len;
                while (cnt < total) {
                    MI_CpuCopy8(p, l.buf3, 5);
                    len = CommRecord_GetLength(l.buf3);
                    MI_CpuCopy8(p, dst, len + 5);
                    dst += len + 5;
                    c6 += len + 5;
                    p += len + 5;
                    cnt += len + 5;
                }
                setLoopbackLen(c6);
            } else {
                u32 c6 = 0;
                while (c6 < total) {
                    MI_CpuCopy8(p, l.buf2, 5);
                    p += 5;
                    c6 += 5;
                    u32 len = CommRecord_GetLength(l.buf2);
                    beginRecord();
                    writeRecord(p, len);
                    endRecord(l.buf2[2], l.buf2[3]);
                    p += len;
                    c6 += len;
                }
            }
            clearDeferredLen();
        }
    }
}
u8 *CommManager::getHeldBuf() {
    using namespace n2; return heldBuf; }
void CommManager::setHeldBuf(u8 *v) {
    using namespace n2; heldBuf = v; }
void CommManager::clearHeldLen() {
    using namespace n2; setHeldLen(0); }
void CommManager::setHeldLen(u32 v) {
    using namespace n2; heldLen = v; }
u32 CommManager::getHeldLen() {
    using namespace n2; return heldLen; }
void CommManager::dispatchHeld() {
    using namespace n2;
    CommRecordUnpackLocals l;
    u32 size = getHeldLen();
    if (size != 0) {
        u8 *p = getHeldBuf();
        MI_CpuCopy8(p, l.buf, 5);
        CommRecord_UnpackSource(&l.buf[4], &l.a, &l.b);
        if (l.a == Scene_GetCurrent()) {
            u32 pos = 0;
            while (pos < size) {
                MI_CpuCopy8(p, l.buf, 5);
                p += 5;
                pos += 5;
                CommRecord_UnpackSource(&l.buf[4], &l.a, &l.b);
                u32 t = l.b;
                u32 len = CommRecord_GetLength(l.buf);
                CommRecv_Dispatch(l.buf[2], p, len, l.buf[3], l.a, t);
                p += len;
                pos += len;
            }
            clearHeldLen();
        }
    }
}
u8 *CommManager::getLoopbackBuf() {
    using namespace n2; return loopbackBuf; }
void CommManager::setLoopbackBuf(u8 *v) {
    using namespace n2; loopbackBuf = v; }
void CommManager::clearLoopbackLen() {
    using namespace n2; setLoopbackLen(0); }
void CommManager::setLoopbackLen(u32 v) {
    using namespace n2; loopbackLen = v; }
u32 CommManager::getLoopbackLen() {
    using namespace n2; return loopbackLen; }
void CommManager::dispatchLoopback() {
    using namespace n2;
    CommRecordUnpackLocals l;
    u32 size = getLoopbackLen();
    if (size != 0) {
        u32 pos = 0;
        u8 *p = getLoopbackBuf();
        while (pos < size) {
            MI_CpuCopy8(p, l.buf, 5);
            p += 5;
            pos += 5;
            CommRecord_UnpackSource(&l.buf[4], &l.a, &l.b);
            u32 t = l.b;
            u32 len = CommRecord_GetLength(l.buf);
            CommRecv_Dispatch(l.buf[2], p, len, l.buf[3], l.a, t);
            p += len;
            pos += len;
        }
        clearLoopbackLen();
    }
}
u8 *CommManager::getAuxBufA() {
    using namespace n2; return auxBufA; }
void CommManager::setAuxBufA(u8 *v) {
    using namespace n2; auxBufA = v; }
void CommManager::clearAuxLenA() {
    using namespace n2; setAuxLenA(0); }
void CommManager::setAuxLenA(u32 v) {
    using namespace n2; auxLenA = v; }
u32 CommManager::getAuxLenA() {
    using namespace n2; return auxLenA; }
void CommManager::appendAuxA(u8 *src, u32 n) {
    using namespace n2;
    MI_CpuCopy8(src, auxWritePtrA, n);
    auxWritePtrA += n;
}
u8 *CommManager::getAuxBufB() {
    using namespace n2; return auxBufB; }
void CommManager::setAuxBufB(u8 *v) {
    using namespace n2; auxBufB = v; }
void CommManager::clearAuxLenB() {
    using namespace n2; setAuxLenB(0); }
void CommManager::setAuxLenB(u32 v) {
    using namespace n2; auxLenB = v; }
u32 CommManager::getAuxLenB() {
    using namespace n2; return auxLenB; }
void CommManager::setSentSeq(s16 v) {
    using namespace n2; sentSeq = v; }
void CommManager::setConfirmedSeq(s16 v) {
    using namespace n2; confirmedSeq = v; }
s16 CommManager::getSentSeq() {
    using namespace n2; return sentSeq; }
s16 CommManager::getConfirmedSeq() {
    using namespace n2; return confirmedSeq; }
void CommManager::clearSentSeq() {
    using namespace n2; sentSeq = -1; }
void CommManager::clearConfirmedSeq() {
    using namespace n2; confirmedSeq = -1; }

namespace n1 {
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern u16 data_020cb6f4;
}
extern "C" {
extern u16 data_020d03cc;
}
extern "C" {
extern CommManager *const gCommManager;
}
extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
}

}
void CommManager::setControlLen(u32 v) {
    using namespace n1; controlLen = v; }
u32 CommManager::getControlLen() {
    using namespace n1; return controlLen; }
void CommManager::clearControlLen() {
    using namespace n1; controlLen = 0; }
void CommManager::appendControl(void *src, u32 n) {
    using namespace n1;
    u8 *d = getSendBuf(4);
    d = d + controlLen;
    MI_CpuCopy8(src, d, n);
    controlLen += n;
}
void CommManager::setLatchedErrorFlags(u32 v) {
    using namespace n1; latchedErrorFlags = v; }
u32 CommManager::getLatchedErrorFlags() {
    using namespace n1; return latchedErrorFlags; }
void CommManager::setErrorFlags(u32 v) {
    using namespace n1; errorFlags = v; }
u32 CommManager::getErrorFlags() {
    using namespace n1; return errorFlags; }
void CommManager::setErrorMode(u32 v) {
    using namespace n1; errorMode = v; }
u32 CommManager::getErrorMode() {
    using namespace n1; return errorMode; }
void Comm_CountNoAckFrames(CommManager *self) {
    using namespace n1;
    s32 i;
    CommManager *g;
    i = 3;
    g = gCommManager;
    for (; i >= 0; i--) {
        if (g->isSlotActive(i) && !g->isMyAid(i)) {
            s32 idx = Comm_AidToPeerIndex(i);
            u32 v = g->getNoAckFrames(i);
            Comm_IsWifi();
            if (v <= 0x258) self->noAckFrames[idx]++;
        }
    }
}
u32 CommManager::getNoAckFrames(s32 i) {
    using namespace n1;
    return noAckFrames[Comm_AidToPeerIndex(i)];
}
BOOL Comm_AnyPeerTimedOut() {
    using namespace n1;
    s32 i;
    CommManager *g;
    i = 3;
    g = gCommManager;
    for (; i >= 0; i--) {
        if (g->isSlotActive(i) && !g->isMyAid(i)) {
            Comm_AidToPeerIndex(i);
            u32 v = g->getNoAckFrames(i);
            Comm_IsWifi();
            if (v > 0x258) return TRUE;
        }
    }
    return FALSE;
}
void CommManager::resetNoAckFrames(s32 i) {
    using namespace n1;
    noAckFrames[Comm_AidToPeerIndex(i)] = 0;
}
void CommManager::clearNoAckFrames() {
    using namespace n1;
    u16 *p = noAckFrames;
    for (s32 i = 2; i >= 0; i--) *p++ = 0;
}
void CommManager::setSendRetry(u32 v) {
    using namespace n1; sendRetry = v; }
u32 CommManager::getSendRetry() {
    using namespace n1; return sendRetry; }
void CommManager::setSendRetryLimit(u32 v) {
    using namespace n1; sendRetryLimit = v; }
u32 CommManager::getSendRetryLimit() {
    using namespace n1; return sendRetryLimit; }
void CommManager::setSessionMemberMask(u32 v) {
    using namespace n1; sessionMemberMask = v; }
u8 *CommManager::getWifiFriendList() {
    using namespace n1; return wifiFriendList; }
u8 *CommManager::getWifiUserData() {
    using namespace n1; return wifiUserData; }
void NetOverlay_AssertWifi() {
    using namespace n1;
    u32 x;
    if (gOverlayHandle.isLoading) x = (u32)-1; else x = gOverlayHandle.overlayId;
    BOOL ok;
    if (OVERLAY_65_ID == x) ok = TRUE; else ok = FALSE;
    if (!ok) Fatal_Trap();
}
void NetOverlay_AssertWireless() {
    using namespace n1;
    u32 x;
    if (gOverlayHandle.isLoading) x = (u32)-1; else x = gOverlayHandle.overlayId;
    BOOL ok;
    if (OVERLAY_66_ID == x) ok = TRUE; else ok = FALSE;
    if (!ok) Fatal_Trap();
}
void NetOverlay_AssertOv067() {
    using namespace n1;
    u32 x;
    if (gOverlayHandle.isLoading) x = (u32)-1; else x = gOverlayHandle.overlayId;
    BOOL ok;
    if (OVERLAY_67_ID == x) ok = TRUE; else ok = FALSE;
    if (!ok) Fatal_Trap();
}
void NetOverlay_AssertAny() {
    using namespace n1;
    u32 x;
    if (gOverlayHandle.isLoading) x = (u32)-1; else x = gOverlayHandle.overlayId;
    BOOL ok;
    Unk_020720f8_Id a = (Unk_020720f8_Id)OVERLAY_65_ID;
    Unk_020720f8_Id b = (Unk_020720f8_Id)OVERLAY_66_ID;
    Unk_020720f8_Id c = (Unk_020720f8_Id)OVERLAY_67_ID;
    if (x == a || x == b || x == c) ok = TRUE; else ok = FALSE;
    if (!ok) Fatal_Trap();
}

u8 sCommAckPackets[4];

CommManager gCommManagerInstance;

namespace U126_def {
extern "C" {
extern CommManager *const gCommManager;
CommManager *const gCommManager = &gCommManagerInstance;
}
}

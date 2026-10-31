#include "types.h"
#include "net/CommManager.h"
#include "net/NetStateBlockHeader.h"
#include "net/NetSessionParts.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020a65fc.h"
#include "proto/main/unk_020a6914.h"


extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 Scene_GetCurrent();
}

extern CommManager *gCommManager;


extern void (*const sNetStateAWriters[2])(s32);
void (*const sNetStateAWriters[2])(s32) = {(void (*)(s32))NetArea_WriteStateAPart0, (void (*)(s32))NetArea_WriteStateANpcTalk};

extern "C" void NetStatusMsgBase_Unpack(u8 *p, s32 *a, u8 *b, u8 *c, u8 *d, s32 *e) {
    u8 loc;
    CommRecord_UnpackSource(p, b, &loc);
    if (loc & 1) {
        *c = 1;
    } else {
        *c = 0;
    }
    if (loc & 2) {
        *d = 1;
    } else {
        *d = 0;
    }
    *e = p[1] & 0x3f;
    *a = ((u32)p[1] >> 6) & 3;
}

extern "C" void *NetStatusUpdateMsg_Init(void *p) {
    NetStatusMsgBase_Init();
    return p;
}

extern "C" void *NetStatusUpdateMsg_Fini(void *p) {
    NetStatusMsgBase_Fini();
    return p;
}

extern "C" void NetStatusUpdateMsg_Pack(u8 *p, s32 b, s32 c, s32 d, s32 e) { NetStatusMsgBase_Pack(p, 0, b, c, d, e); }

extern "C" void NetStatusUpdateMsg_Unpack(u8 *p, u8 *b, u8 *c, u8 *d, s32 *e) {
    s32 x;
    NetStatusMsgBase_Unpack(p, &x, b, c, d, e);
}

extern "C" void *NetStatusMsg_Init(void *p) {
    NetStatusMsgBase_Init();
    return p;
}

extern "C" void *NetStatusMsg_Fini(void *p) {
    NetStatusMsgBase_Fini();
    return p;
}

extern "C" void NetStatusMsg_Pack(u8 *p, s32 a, s32 b, s32 c, u8 d, s32 e) { NetStatusMsgBase_Pack(p, a, b, c, d, e); }

extern "C" void NetStatusMsg_Unpack(u8 *p, s32 *a, u8 *b, u8 *c, u8 *d, s32 *e) { NetStatusMsgBase_Unpack(p, a, b, c, d, e); }

NetPendingStatus::NetPendingStatus() { reset(); }

NetPendingStatus::~NetPendingStatus() {}

void NetPendingStatus::setMasked(u8 a, u8 b, u8 c, u32 mask) {
    if (mask & 1) {
        sceneId = a;
    }
    if (mask & 2) {
        isOwner = b;
    }
    if (mask & 4) {
        isMoving = c;
    }
    dirtyMask |= mask;
}

void NetPendingStatus::get(u8 *a, u8 *b, u8 *c, u32 *d) {
    *a = sceneId;
    *b = isOwner;
    *c = isMoving;
    *d = dirtyMask;
}

void NetPendingStatus::reset() {
    sceneId = 0x3f;
    isOwner = 0;
    isMoving = 0;
    dirtyMask = 0;
}

NetSlotStatus::NetSlotStatus() { reset(); }

NetSlotStatus::~NetSlotStatus() {}

void NetSlotStatus::set(u8 a, u8 b, u8 c) {
    sceneId = a;
    isOwner = b;
    isMoving = c;
}

void NetSlotStatus::get(u8 *a, u8 *b, u8 *c) {
    *a = sceneId;
    *b = isOwner;
    *c = isMoving;
}

void NetSlotStatus::reset() {
    sceneId = 0x3f;
    isOwner = 0;
    isMoving = 0;
}

NetMoveRequest::NetMoveRequest() { reset(); }

NetMoveRequest::~NetMoveRequest() {}

void NetMoveRequest::set(u32 a, u8 b) {
    slot = a;
    targetScene = b;
}

void NetMoveRequest::get(s32 *a, u8 *b) {
    *a = slot;
    *b = targetScene;
}

void NetMoveRequest::reset() {
    slot = 4;
    targetScene = 0x3f;
}

NetMoveReady::NetMoveReady() { reset(); }

NetMoveReady::~NetMoveReady() {}

void NetMoveReady::set(u32 v) { readyFlag = v; }

void NetMoveReady::get(u32 *out) { *out = readyFlag; }

void NetMoveReady::reset() { readyFlag = 0; }

extern "C" void NetSyncMsg_Init() {}

extern "C" void NetSyncMsg_Fini() {}

extern "C" void NetSyncMsg_Pack(u8 *p, s32 a, s32 b, s32 c) {
    *p = (a & 7) | (((b << 5) & 0xe0) | (c << 3));
}

extern "C" void NetSyncMsg_Unpack(u8 *p, s32 *a, s32 *b, s32 *c) {
    *a = *p & 7;
    *b = (*p >> 5) & 7;
    *c = (*p >> 3) & 3;
}

extern "C" void NetArea_WriteStateAPart0() {}

extern "C" void NetArea_WriteStateANpcTalk() {
    u8 v = 1;
    gCommManager->appendAuxA(&v, 1);
}

extern "C" void NetArea_BuildStateA() {
    CommManager *g = gCommManager;
    g->clearAuxLenA();
    u8 *base = (u8 *)g->getAuxBufA();
    u8 *p = base + 2;
    s32 m = Scene_GetCurrent();
    NetStateBlockHeader b;
    u32 i;
    for (i = 0; i < 2; i++) {
        g->auxWritePtrA = p + 4;
        u8 *start = g->auxWritePtrA;
        sNetStateAWriters[i](m);
        u8 *cur = g->auxWritePtrA;
        s32 diff = cur - start;
        if (diff != 0) {
            b.len = diff;
            b.id = i;
            MI_CpuCopy8(&b.len, p, 4);
            p = cur;
        }
    }
    s32 tot = p - base;
    b.total = tot - 2;
    MI_CpuCopy8(&b.total, base, 2);
    g->setAuxLenA(tot);
}


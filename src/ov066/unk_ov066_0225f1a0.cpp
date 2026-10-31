#include "ds_div.h"
#include "uptr.h"
#include "types.h"

#include "nitro/os_alarm.h"
#include "nitro/wm.h"
#include "proto/autoload_2/unk_02114d84.h"
#include "proto/autoload_2/unk_02114ef4.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/ov066/unk_ov066_0225f1a0.h"


struct LocalWlConfig {
    u32 ggid;
    u8 maxMembers;
    u8 maxBeacons;
    u8 recordSize;
    u8 mpFreq;
};

struct LocalWlWorkBits {
    s32 f0 : 1;
    s32 f1 : 1;
    s32 f2 : 1;
    s32 stopScanOnParent : 1;
    s32 skipNoGameInfo : 1;
    s32 filterGgid : 1;
    s32 filterScanSlot : 1;
    s32 filterVersion : 1;
    s32 f8 : 1;
    s32 f9 : 1;
    s32 resetting : 1;
    s32 modeRequestPending : 1;
    s32 mpStarted : 1;
    s32 rest : 19;
};

struct LocalWlWork {
    /* 0x00 */ u32 requestedMode;
    /* 0x04 */ u32 state;
    /* 0x08 */ u8 channel;
    /* 0x09 */ u8 numScanChannels;
    /* 0x0a */ u8 maxChildren;
    /* 0x0b */ u8 maxMembers;
    /* 0x0c */ u8 maxBeacons;
    /* 0x0d */ u8 dmaNo;
    /* 0x0e */ u8 pad_0e[2];
    /* 0x10 */ u8 *scanChannels;
    /* 0x14 */ u8 parentWaitBeacons;
    /* 0x15 */ u8 resetRetryCount;
    /* 0x16 */ u8 abortRequest;
    /* 0x17 */ u8 mpFreq;
    /* 0x18 */ u16 recvChildSize;
    /* 0x1a */ u16 parentMaxSize;
    /* 0x1c */ u16 recvParentSize;
    /* 0x1e */ u16 childMaxSize;
    /* 0x20 */ u16 scanLoopTime;
    /* 0x22 */ u16 scanMaxChannelTime;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 pad_26[2];
    /* 0x28 */ u32 ggid;
    /* 0x2c */ u32 unk_2c;
    /* 0x30 */ void (*doneCallback)(u32);
    /* 0x34 */ u32 doneCallbackArg;
    /* 0x38 */ void (*eventCallback)(void *);
    /* 0x3c */ union {
        u32 flags;
        LocalWlWorkBits bits;
    };
};

struct LocalWlMpRecord {
    u8 type : 2;
    u8 isLast : 1;
    u8 hasAck : 1;
    u8 frameId : 4;
    u8 length;
    u16 destMask;
    u16 totalSizeLo;
    u16 totalSizeHi;
    u8 data[1];
};

struct LocalWlMpRecordHdr {
    u8 type : 2;
    u8 pad : 1;
    u8 hasAck : 1;
    u8 frameId : 4;
    u8 length;
};

struct LocalWlMpRecvEntry {
    u8 *buffer;
    u32 bufferSize;
    u32 totalSize;
    u32 receivedSize;
};

struct LocalWlMpFramePayload {
    u8 frameId;
    u8 unk_01;
    u16 aidMask;
    u8 records[1];
};

struct LocalWlMpFrame {
    /* 0x00 */ LocalWlMpFrame *prev;
    /* 0x04 */ LocalWlMpFrame *next;
    /* 0x08 */ u16 frameSize;
    /* 0x0a */ u16 destMask;
    /* 0x0c */ u16 ackMask;
    /* 0x0e */ u8 pad[0x20 - 0x0e];
    /* 0x20 */ LocalWlMpFramePayload payload;
};

struct LocalWlMpFlags {
    u8 waitFirstFrame : 1;
    u8 frameLost : 1;
    u8 resendRequest : 1;
    u8 sending : 1;
    u8 lastRecordPut : 1;
};

struct LocalWlMpWork {
    /* 0x00 */ u8 recordSize;
    /* 0x01 */ u8 lastFrameId : 4;
    u8 missingFrameId : 4;
    /* 0x02 */ s8 numPendingSends;
    /* 0x03 */ s8 numRecordsInFlight;
    /* 0x04 */ LocalWlMpFlags flags;
    /* 0x05 */ u8 pad[3];
    /* 0x08 */ LocalWlMpFrame *sendRing;
    /* 0x0c */ LocalWlMpFrame *recvRing;
    /* 0x10 */ LocalWlMpFrame *curSendFrame;
    /* 0x14 */ LocalWlMpFrame *resendFrame;
    /* 0x18 */ LocalWlMpFrame **recvCursors;
    /* 0x1c */ u16 recvActiveMask;
    /* 0x1e */ u16 sendDestMask;
    /* 0x20 */ u8 *sendData;
    /* 0x24 */ u32 sendSize;
    /* 0x28 */ s32 sendOffset;
    /* 0x2c */ void (*sendDoneCallback)(u32);
    /* 0x30 */ LocalWlMpRecvEntry *recvEntries;
};

struct LocalWlEventMsg {
    u16 apiid;
    u16 errcode;
    u16 mpEvent;
    u16 unk_06;
    u16 event;
    union {
        u16 myAid;
        u8 peerMac[6];
    };
    u16 peerAid;
};

struct LocalWlGameInfo {
    u16 tag;
    u16 nonce;
    u8 scanSlot;
    u8 memberCount;
    u8 version;
    u8 userDataSize;
    u8 userData[0x68];
};

struct LocalWlBeaconList;

struct LocalWlBeacon {
    /* 0x00 */ u16 inUse;
    /* 0x02 */ u8 macAddr[6];
    /* 0x08 */ u16 tag;
    /* 0x0a */ u8 linkLevel;
    /* 0x0b */ u8 linkLevelPos;
    /* 0x0c */ u8 linkLevels[6];
    /* 0x12 */ u8 pad[2];
    /* 0x14 */ LocalWlBeaconList *ownerList;
    /* 0x18 */ u8 pad2[8];
    /* 0x20 */ WMBssDesc bssDesc;
};

struct LocalWlBeaconList {
    u8 listId;
    u8 numUsed;
    u8 capacity;
    u8 pad;
    LocalWlBeacon *entries;
    OSAlarm *alarms;
    void (*changeCallback)(LocalWlBeacon *);
};

struct LocalWlScanFlags {
    s32 stopPending : 1;
    s32 looping : 1;
    s32 rest : 30;
};

struct LocalWlScanWork {
    /* 0x00 */ WMScanParam *scanParam;
    /* 0x04 */ WMBssDesc *scanBuffer;
    /* 0x08 */ LocalWlBeaconList *beaconLists;
    /* 0x0c */ LocalWlScanFlags scanFlags;
    /* 0x10 */ OSAlarm scanTimer;
    /* 0x3c */ OSAlarm stopTimer;
    /* 0x68 */ u32 unk_68;
    /* 0x6c */ s32 (*beaconFilter)(void *);
};

struct LocalWlMacAddr {
    u8 b[6];
};

struct LocalWlControlHdr {
    u16 type;
    u16 size;
    u32 nonce;
};

struct LocalWlSessionBits {
    s32 sendingMemberTable : 1;
    s32 memberTableResend : 1;
    s32 endRequested : 1;
    s32 ending : 1;
    s32 gameInfoDirty : 1;
    s32 startMpOnGameInfo : 1;
    s32 retryConnect : 1;
    s32 autoChannel : 1;
    s32 parentFound : 1;
    s32 beaconSelected : 1;
    s32 f10 : 1;
    s32 rest : 21;
};

struct LocalWlSession {
    /* 0x00 */ WMParentParam *parentParam;
    /* 0x04 */ WMArm9Buf *wmBuf;
    /* 0x08 */ LocalWlGameInfo *gameInfo;
    /* 0x0c */ void *recvBuf;
    /* 0x10 */ void *sendBuf;
    /* 0x14 */ u8 *controlBuf;
    /* 0x18 */ u16 gameInfoLength;
    /* 0x1a */ u16 recvBufSize;
    /* 0x1c */ u16 sendBufSize;
    /* 0x1e */ u16 myAid;
    /* 0x20 */ u16 tgid;
    /* 0x22 */ u8 myMac[6];
    /* 0x28 */ LocalWlMacAddr memberMacs[16];
    /* 0x88 */ LocalWlBeacon *selectedBeacon;
    /* 0x8c */ u8 numMembers;
    /* 0x8d */ u8 channel;
    /* 0x8e */ u8 scanChannel;
    /* 0x8f */ u8 fixedChannel;
    /* 0x90 */ u16 allowedChannelMask;
    /* 0x92 */ u8 numAllowedChannels;
    /* 0x93 */ u8 roleTurnTarget;
    /* 0x94 */ u8 roleTurnCount;
    /* 0x95 */ u8 scanSlot;
    /* 0x96 */ u8 numBeaconsSent;
    /* 0x97 */ u8 unk_97;
    /* 0x98 */ u16 readyMask;
    /* 0x9a */ u8 pad_9a[2];
    /* 0x9c */ void (*resetHook)(void);
    /* 0xa0 */ void (*parentSendHook)(void);
    /* 0xa4 */ void (*childSendHook)(void);
    /* 0xa8 */ void (*shutdownHook)(void);
    /* 0xac */ void (*sendControlHook)(u8 *, u32, u32, void (*)(void));
    /* 0xb0 */ s32 (*sendHook)(u8 *, u32, u32, void (*)(u32));
    /* 0xb4 */ s32 (*isReadyToSendHook)(void);
    /* 0xb8 */ void (*recvCallback)(u32, u8 *, u32);
    /* 0xbc */ void (*memberLeftHook)(u32);
    /* 0xc0 */ union {
        u32 flags;
        LocalWlSessionBits bits;
    };
};

extern "C" {
s32 WM_Enable(void *);
s32 WM_Disable(void *);
s32 WM_PowerOn(void *);
s32 WM_PowerOff(void *);
s32 (*sLocalWlPowerApis[4])(void *) = {WM_Enable, WM_Disable, WM_PowerOn, WM_PowerOff};
u32 data_ov066_022647c4;
u32 data_ov066_022647c0;
u32 data_ov066_022647bc;
u32 sLocalWlRandSeed;
LocalWlSession *sLocalWlSession;
LocalWlMpWork *sLocalWlMp;
LocalWlWork *sLocalWl;
void *(*sLocalWlAllocHook)(u32, u32);
LocalWlScanWork *sLocalWlScan;
void (*sLocalWlErrorHook)(u32);
void (*sLocalWlFreeHook)(void *);

u32 OS_DisableInterrupts(void);
s32 OS_RestoreInterrupts(u32);
void DC_InvalidateRange(void *p, s32 v);
s32 DC_StoreRange(void *, s32);
s32 OS_CancelAlarms(u32);
s32 OS_SetAlarmTag(void *, u32);
void OS_GetMacAddress(void *p);
s32 MIi_CpuClearFast(s32, void *, s32);
s32 MIi_CpuCopyFast(void *, void *, s32);
void MI_CpuFill8(void *p, u32 v, u32 n);
s32 MI_CpuCopy8(void *, void *, s32);
s32 WM_Finish(void);
s32 WM_Init(void *p, s32 v);
u32 WM_GetDispersionBeaconPeriod(void);
s32 WM_GetLinkLevel(void);
s32 func_0211f7e4(void);
u32 WM_GetAllowedChannel(void);
s32 WM_SetPortCallback(u32, void *, s32);
s32 WM_SetIndCallback(void *);
s32 WM_Disconnect(void *, u32);
s32 WM_StartConnectEx(void *, void *, u32, u32, u32);
s32 WM_EndScan(void *);
s32 WM_StartScan(void *, void *);
s32 WM_EndParent(void *);
s32 WM_StartParent(void *);
s32 WM_SetParentParameter(void *, void *);
s32 WM_Reset(WMCallback cb);
s32 WM_EndMP(void *);
s32 WM_SetMPDataToPortEx(void *, void *, void *, u32, u32, u32, u32);
s32 WM_StartMPEx(void *, void *, u32, void *, u32, u32, u32, s32, s32, s32, s32);
s32 WM_SetEntry(void *, u32);
s32 WM_MeasureChannel(void *, s32, s32, u32, s32);
s32 WM_SetGameInfo(void *, void *, u32, u32, u32, u8);
u32 func_0213335c(u32 a, u32 b);
void * LocalWl_GetBeaconGameInfo(LocalWlBeacon *r);
void LocalWl_OnSetEntry(LocalWlEventMsg *m);
void LocalWl_OnEndMp(LocalWlEventMsg *m);
void LocalWl_OnMpEvent(LocalWlEventMsg *m);
void LocalWl_OnSetGameInfo(LocalWlEventMsg *m);
void LocalWl_OnDisconnect(LocalWlEventMsg *m);
void LocalWl_OnChildConnectEvent(LocalWlEventMsg *m);
void LocalWl_OnEndParent(LocalWlEventMsg *m);
void LocalWl_OnParentEvent(LocalWlEventMsg *m);
void LocalWl_OnSetParentParameter(LocalWlEventMsg *m);
void LocalWl_OnChildConnected(LocalWlEventMsg *m);
void LocalWl_OnChildLeft(LocalWlEventMsg *m);
void LocalWl_OnChildJoined(LocalWlEventMsg *m);
void LocalWlBcn_Clear(LocalWlBeaconList *o);
void LocalWlBcn_CancelAlarms(LocalWlBeaconList *o);
void LocalWlBcn_OnExpire(void *arg);
void LocalWlBcn_Free(LocalWlBeaconList *o);
void LocalWlMp_DeliverFrame(LocalWlMpFramePayload *p);
void LocalWlMp_PutParentRecord(LocalWlMpFrame *o);
void LocalWl_ApplyConfig(LocalWlConfig *in);
}

#pragma thumb off
extern "C" {

#define LocalWl_Alloc ((void * (*)(u32, u32))LocalWl_Alloc)

void LocalWl_ApplyConfig(LocalWlConfig *in) {
    u8 w = in->recordSize;
    u32 sz = w * in->maxMembers;
    u16 t = sz + 4;
    sLocalWl->ggid = in->ggid;
    sLocalWl->bits.stopScanOnParent = 0;
    sLocalWl->bits.f0 = 0;
    sLocalWl->bits.filterGgid = -1;
    sLocalWl->bits.filterScanSlot = -1;
    sLocalWl->bits.filterVersion = -1;
    sLocalWl->bits.f9 = 0;
    sLocalWl->bits.f8 = 0;
    sLocalWl->bits.f2 = -1;
    sLocalWl->bits.f1 = -1;
    sLocalWl->mpFreq = in->mpFreq;
    sLocalWl->channel = 0xfe;
    sLocalWl->numScanChannels = 1;
    sLocalWl->maxChildren = in->maxMembers - 1;
    sLocalWl->maxMembers = in->maxMembers;
    sLocalWl->maxBeacons = in->maxBeacons;
    sLocalWl->recvChildSize = w;
    sLocalWl->parentMaxSize = t;
    sLocalWl->recvParentSize = t;
    sLocalWl->childMaxSize = w;
    sLocalWl->scanMaxChannelTime = 0x1e;
    sLocalWl->scanLoopTime = 0x5a;
    sLocalWl->unk_24 = 0xc8;
    sLocalWl->parentWaitBeacons = 4;
}

void *LocalWlMp_AllocRing(s32 n) {
    u32 sz = (__builtin_offsetof(LocalWlMpFrame, payload.records) + sLocalWl->parentMaxSize + 0x1f) & ~0x1f;
    u32 tot = sz * n;
    LocalWlMpFrame *p = (LocalWlMpFrame *)LocalWl_Alloc(tot, 0x20);
    u16 i;
    LocalWlMpFrame *q;
    LocalWlMpFrame *head;
    MI_CpuFill8(p, 0, tot);
    head = p;
    s32 last = n - 1;
    for (i = 0; (s32)i < last; ) {
        i++;
        p->payload.frameId = 0;
        q = p;
        p->next = (LocalWlMpFrame *)((u8 *)p + sz);
        p = p->next;
        p->prev = q;
    }
    p->payload.frameId = last;
    p->next = head;
    head->prev = p;
    return head;
}

void LocalWlMp_ClearRing(LocalWlMpFrame *p, s32 n) {
    u16 i;
    for (i = 0; (s32)i < n; ) {
        i++;
        p->frameSize = 0;
        p->destMask = 0;
        p->ackMask = 0;
        p = p->next;
    }
}
#undef LocalWl_Alloc

#define MI_CpuFill8 ((void (*)(void *, s32, u32))MI_CpuFill8)
#define MI_CpuCopy8 ((s32 (*)(void *, void *, u32))MI_CpuCopy8)
#define LocalWl_Alloc ((void * (*)(u32, u32))LocalWl_Alloc)
#define LocalWl_OnControlRecv ((void (*)(void))LocalWl_OnControlRecv)
#define LocalWlMp_OnDataRecv ((void (*)(void))LocalWlMp_OnDataRecv)
#define LocalWlMp_OnMemberLeft ((void (*)(void))LocalWlMp_OnMemberLeft)
#define LocalWl_ApplyConfig ((void (*)(u8 *))LocalWl_ApplyConfig)
#define LocalWlMp_AllocRing ((void * (*)(u32))LocalWlMp_AllocRing)

void LocalWlMp_Start(u8 *msg) {
    u32 n;
    if (sLocalWlMp != NULL) {
        return;
    }
    LocalWl_ApplyConfig(msg);
    LocalWl_InitWm();
    sLocalWlSession->resetHook = LocalWlMp_Reset;
    sLocalWlSession->parentSendHook = LocalWlMp_ParentSendStep;
    sLocalWlSession->childSendHook = LocalWlMp_ChildSendStep;
    sLocalWlSession->sendControlHook = LocalWlMp_SendControl;
    sLocalWlSession->sendHook = LocalWlMp_Send;
    sLocalWlSession->isReadyToSendHook = LocalWlMp_IsReadyToSend;
    sLocalWlSession->shutdownHook = LocalWlMp_Shutdown;
    sLocalWlSession->memberLeftHook = (void (*)(u32))LocalWlMp_OnMemberLeft;
    sLocalWlMp = (LocalWlMpWork *)LocalWl_Alloc(sizeof(LocalWlMpWork), 4);
    n = sLocalWl->maxMembers * sizeof(LocalWlMpRecvEntry);
    sLocalWlMp->recvEntries = (LocalWlMpRecvEntry *)LocalWl_Alloc(n, 4);
    MI_CpuFill8(sLocalWlMp->recvEntries, 0, n);
    sLocalWlMp->sendRing = (LocalWlMpFrame *)LocalWlMp_AllocRing(3);
    sLocalWlMp->recvRing = (LocalWlMpFrame *)LocalWlMp_AllocRing(3);
    n = sLocalWl->maxMembers << 2;
    sLocalWlMp->recvCursors = (LocalWlMpFrame **)LocalWl_Alloc(n, 4);
    MI_CpuFill8(sLocalWlMp->recvCursors, 0, n);
    sLocalWlMp->recordSize = msg[6];
    WM_SetPortCallback(0xc, (void *)LocalWl_OnControlRecv, 0);
    WM_SetPortCallback(0xd, (void *)LocalWlMp_OnDataRecv, 0);
    WM_SetIndCallback((void *)LocalWlMp_OnIndicationStub);
    LocalWlMp_Reset();
}

void LocalWlMp_Shutdown(void) {
    if (sLocalWlMp == NULL) {
        return;
    }
    WM_SetPortCallback(0xc, 0, 0);
    WM_SetPortCallback(0xd, 0, 0);
    LocalWl_Free(sLocalWlMp->recvCursors);
    LocalWl_Free((void *)sLocalWlMp->recvRing);
    LocalWl_Free((void *)sLocalWlMp->sendRing);
    LocalWl_Free(sLocalWlMp->recvEntries);
    LocalWl_Free(sLocalWlMp);
    LocalWl_FinishWm();
    sLocalWlMp = NULL;
}

s32 LocalWlMp_IsReadyToSend(void) {
    LocalWlMpWork *g = sLocalWlMp;
    s32 r = 0;
    if (g == NULL) {
        return r;
    }
    s32 t = sLocalWl->state;
    switch (t) {
    case 10:
    case 11:
        r = g->flags.sending;
        if (r == 0) {
            r = 1;
        } else {
            r = 0;
        }
    }
    return r;
}

s32 LocalWlMp_Send(u8 *a, u32 b, u32 c, void (*d)(u32)) {
    s32 r = 0;
    u32 irq = OS_DisableInterrupts();
    if (LocalWlMp_IsReadyToSend() != 0) {
        sLocalWlMp->flags.sending = 1;
        sLocalWlMp->flags.lastRecordPut = 0;
        sLocalWlMp->sendData = a;
        sLocalWlMp->sendSize = b;
        sLocalWlMp->sendOffset = r;
        r = 1;
        sLocalWlMp->sendDestMask = c;
        sLocalWlMp->sendDoneCallback = d;
    }
    OS_RestoreInterrupts(irq);
    return r;
}

void LocalWlMp_OnIndicationStub(void) {
}

void LocalWlMp_FinishSend(void) {
    LocalWlMpWork *g = sLocalWlMp;
    u32 n = g->sendSize;
    void (*cb)(u32) = g->sendDoneCallback;
    g->flags.sending = 0;
    sLocalWlMp->sendDestMask = 0;
    sLocalWlMp->sendData = 0;
    sLocalWlMp->sendSize = 0;
    sLocalWlMp->sendOffset = -1;
    sLocalWlMp->sendDoneCallback = 0;
    if (cb == NULL) {
        return;
    }
    cb(n);
}

void LocalWlMp_OnChildPacketSent(WMPortSendCallback *w) {
    LocalWlMpRecord *rec = (LocalWlMpRecord *)w->data;
    sLocalWlMp->numPendingSends--;
    if (rec->type != 0) {
        if (rec->type != 1) {
            return;
        }
    }
    if (rec->isLast == 0) {
        return;
    }
    rec->isLast = 0;
    LocalWlMp_FinishSend();
}

void LocalWlMp_OnFrameSent(void) {
    sLocalWlMp->numPendingSends--;
}

u16 LocalWlMp_PutSendRecord(LocalWlMpRecord *rec) {
    u8 *dst;
    u8 *base;
    s32 off;
    u32 rem;
    u32 tot;
    u8 *src;
    u16 ret;
    LocalWlMpWork *g;
    u32 len;
    u32 n;
    off = sLocalWlMp->sendOffset;
    tot = sLocalWlMp->sendSize;
    base = sLocalWlMp->sendData;
    rem = tot - off;
    src = base + off;
    if (off == 0) {
        rec->type = 0;
        dst = rec->data;
        rec->destMask = sLocalWlMp->sendDestMask;
        rec->totalSizeLo = sLocalWlMp->sendSize;
        rec->totalSizeHi = sLocalWlMp->sendSize >> 16;
        g = sLocalWlMp;
        n = g->sendSize;
        if (n > (u32)(g->recordSize - 8)) {
            n = g->recordSize - 8;
        }
        len = (u8)n;
        ret = (len + 9) & ~1;
    } else {
        rec->type = 1;
        dst = (u8 *)&rec->destMask;
        g = sLocalWlMp;
        n = rem;
        if (n > (u32)(g->recordSize - 2)) {
            n = g->recordSize - 2;
        }
        len = (u8)n;
        ret = (len + 3) & ~1;
    }
    g->sendOffset += len;
    rec->length = len;
    rec->isLast = (sLocalWlMp->sendOffset == (s32)sLocalWlMp->sendSize) ? 1 : 0;
    sLocalWlMp->flags.lastRecordPut = rec->isLast;
    MI_CpuCopy8(src, dst, len);
    return ret;
}

void LocalWlMp_PutParentRecord(LocalWlMpFrame *o) {
    LocalWlMp_PutSendRecord((LocalWlMpRecord *)o->payload.records);
    if (((LocalWlMpRecord *)o->payload.records)->isLast == 0) {
        return;
    }
    LocalWlMp_FinishSend();
}

void LocalWlMp_BuildChildPacket(void) {
    LocalWlMpWork *g = sLocalWlMp;
    s32 sent = 0;
    LocalWlMpRecord *rec = (LocalWlMpRecord *)&g->curSendFrame->payload;
    if (g->flags.resendRequest != 0) {
        rec->type = 3;
        sent = 2;
        rec->frameId = sLocalWlMp->missingFrameId;
    } else if (g->flags.sending != 0) {
        if (g->numRecordsInFlight < 2) {
            if (g->flags.lastRecordPut == 0) {
                if (g->flags.frameLost == 0) {
                    sent = LocalWlMp_PutSendRecord(rec);
                    sLocalWlMp->numRecordsInFlight++;
                }
            }
        }
    }
    if (sLocalWlMp->recvCursors[0] != sLocalWlMp->recvCursors[1]) {
        if (sent == 0) {
            rec->type = 2;
            sent = 2;
            rec->isLast = 0;
        }
        rec->hasAck = 1;
        rec->frameId = sLocalWlMp->recvCursors[1]->payload.frameId;
        sLocalWlMp->recvCursors[1] = sLocalWlMp->recvCursors[1]->next;
    } else {
        rec->hasAck = 0;
    }
    if (sent != 0) {
        sLocalWlMp->numPendingSends++;
        LocalWlMp_SetMpData(0xd, rec, sent, 1, (void *)LocalWlMp_OnChildPacketSent);
        sLocalWlMp->curSendFrame = sLocalWlMp->curSendFrame->next;
    }
    sLocalWlMp->flags.frameLost = 0;
}

void LocalWlMp_ReceiveRecord(u32 idx, u8 *msg) {
    u32 len = 0;
    LocalWlMpRecvEntry *e = sLocalWlMp->recvEntries + idx;
    u8 *p;
    u32 t = ((LocalWlMpRecord *)msg)->type;
    switch (t) {
    case 0:
        p = msg + 8;
        if ((*(u16 *)(msg + 2) & (1 << LocalWl_GetMyAid())) != 0) {
            sLocalWlMp->recvActiveMask |= 1 << idx;
            e->receivedSize = len;
            e->totalSize = (*(u16 *)(msg + 6) << 16) | *(u16 *)(msg + 4);
            len = e->totalSize;
            if (len > (u32)(sLocalWlMp->recordSize - 8)) {
                len = sLocalWlMp->recordSize - 8;
            }
        }
        break;
    case 1:
        p = msg + 2;
        len = msg[1];
        break;
    }
    if ((sLocalWlMp->recvActiveMask & (1 << idx)) == 0) {
        return;
    }
    if (e->receivedSize + len <= e->bufferSize) {
        MI_CpuCopy8(p, e->buffer + e->receivedSize, len);
        e->receivedSize += len;
    }
    if (e->totalSize != e->receivedSize) {
        return;
    }
    sLocalWlMp->recvActiveMask ^= 1 << idx;
    if (sLocalWlSession->recvCallback == NULL) {
        return;
    }
    sLocalWlSession->recvCallback(idx, e->buffer, e->totalSize);
}
#undef MI_CpuFill8
#undef MI_CpuCopy8
#undef LocalWl_Alloc
#undef LocalWl_OnControlRecv
#undef LocalWlMp_OnDataRecv
#undef LocalWlMp_OnMemberLeft
#undef LocalWl_ApplyConfig
#undef LocalWlMp_AllocRing

#define LocalWl_GetMyAid ((s32 (*)(void))LocalWl_GetMyAid)
#define LocalWlMp_ClearRing ((void (*)(void *, s32))LocalWlMp_ClearRing)
#define LocalWlMp_PutParentRecord ((void (*)(void *))LocalWlMp_PutParentRecord)
#define LocalWlMp_ReceiveRecord ((void (*)(s32, void *))LocalWlMp_ReceiveRecord)
void LocalWlMp_DeliverFrame(LocalWlMpFramePayload *p);

void LocalWlMp_DeliverFrame(LocalWlMpFramePayload *p) {
    u16 i;
    u8 *q = p->records;
    for (i = 0; i < sLocalWl->maxMembers; i++) {
        if ((p->aidMask & (1 << i)) != 0) {
            if (i == LocalWl_GetMyAid()) {
                sLocalWlMp->numRecordsInFlight = sLocalWlMp->numRecordsInFlight - 1;
            }
            LocalWlMp_ReceiveRecord(i, q);
            q += sLocalWlMp->recordSize & ~1;
        }
    }
}

s32 LocalWlMp_MergeFrame(LocalWlMpFrame *dst, LocalWlMpFrame *src) {
    u16 mask;
    u16 i;
    u16 total;
    s32 result = 0;
    u8 sz;
    u8 *rd;
    u8 *rp;
    mask = src->payload.aidMask;
    if (mask != 0) {
        u32 t;
        sz = sLocalWlMp->recordSize;
        rd = src->payload.records;
        total = 4;
        rp = dst->payload.records;
        dst->payload.aidMask = mask;
        t = sLocalWlMp->lastFrameId;
        sLocalWlMp->lastFrameId = t + 1;
        dst->payload.frameId = t;
        for (i = 0; i < sLocalWl->maxMembers; i++) {
            if ((mask & (1 << i)) != 0) {
                MI_CpuCopy8(rd + sz * i, rp, sz);
                rp += sz;
                total = total + sz;
            }
            if (sLocalWlMp->recvCursors[i] == src) {
                sLocalWlMp->recvCursors[i] = src->next;
            }
        }
        src->payload.aidMask = 0;
        dst->destMask = sLocalWlSession->readyMask;
        dst->ackMask = 0;
        dst->frameSize = total;
        LocalWlMp_DeliverFrame(&dst->payload);
        result = 1;
    }
    return result;
}

void LocalWlMp_ParentSendStep(void) {
    LocalWlMpWork *g = sLocalWlMp;
    LocalWlMpFrame *n14;
    LocalWlMpFrame *r5;
    LocalWlMpFrame *e0;
    if (g->numPendingSends >= 1) {
        return;
    }
    e0 = g->recvCursors[0];
    r5 = 0;
    n14 = g->resendFrame;
    if (n14 != 0) {
        LocalWlMpFrame *nx = n14->next;
        r5 = n14;
        if (nx == g->curSendFrame) {
            g->resendFrame = 0;
        } else {
            g->resendFrame = nx;
        }
    } else {
        LocalWlMpFrame *p = g->curSendFrame->prev->prev;
        u16 a = p->destMask;
        if (a == 0 || a == p->ackMask) {
            if (g->flags.sending) {
                LocalWlMp_PutParentRecord(e0);
                e0->payload.aidMask = e0->payload.aidMask | 1;
                sLocalWlMp->numRecordsInFlight = sLocalWlMp->numRecordsInFlight + 1;
            }
            if (LocalWlMp_MergeFrame(sLocalWlMp->curSendFrame, e0) != 0) {
                g = sLocalWlMp;
                r5 = g->curSendFrame;
                g->curSendFrame = r5->next;
            }
        }
    }
    if (r5 == 0) {
        return;
    }
    if (r5->destMask == 0) {
        return;
    }
    g = sLocalWlMp;
    g->numPendingSends = g->numPendingSends + 1;
    LocalWlMp_SetMpData(0xd, &r5->payload, r5->frameSize, r5->destMask, (void *)LocalWlMp_OnFrameSent);
}

void LocalWlMp_ChildSendStep(void) {
    if (sLocalWlMp->numPendingSends >= 2) {
        return;
    }
    LocalWlMp_BuildChildPacket();
}

void LocalWlMp_OnMemberLeft(u32 idx) {
    u16 mask = ~(1 << idx);
    LocalWlMpFrame *head = sLocalWlMp->curSendFrame;
    LocalWlMpFrame *n = head;
    do {
        n->destMask = n->destMask & mask;
        n->ackMask = n->ackMask & mask;
        n = n->prev;
    } while (head != n);
}

s32 LocalWlMp_SetMpData(u32 port, void *data, u32 size, u32 destMask, void *done) {
    s32 r = WM_SetMPDataToPortEx((void *)LocalWlMp_OnSetMpData, done, data, size, destMask, port, 2);
    if (r != 2 && r != 7) {
        LocalWl_SetError(r);
        return 0;
    }
    return 1;
}

void LocalWlMp_SendControl(u8 *data, u32 size, u32 destMask, void (*done)(void)) {
    LocalWlMp_SetMpData(0xc, data, size, destMask, (void *)done);
}

void LocalWlMp_OnSetMpData(WMPortSendCallback *m) {
    if (m->errcode == 0) {
        if (m->arg == 0) {
            return;
        }
        ((void (*)(void *))m->arg)(m);
        return;
    }
    LocalWl_SetError(m->errcode);
    Fatal_Trap();
}

LocalWlMpFrame *LocalWlMp_FindFrame(u32 id, LocalWlMpFrame *head) {
    LocalWlMpFrame *n;
    for (n = head->prev; head != n; n = n->prev) {
        if (n->payload.frameId == id) {
            return n;
        }
    }
    return 0;
}

void LocalWlMp_StoreChildPacket(u32 idx, void *src, u32 size) {
    LocalWlMpRecordHdr h;
    LocalWlMpFrame *r;
    LocalWlMpFrame *e;
    MI_CpuCopy8(src, &h, 2);
    if (h.hasAck) {
        r = LocalWlMp_FindFrame(h.frameId, sLocalWlMp->curSendFrame);
        if (r != 0) {
            r->ackMask = r->ackMask | (r->destMask & (1 << idx));
        }
    }
    if (h.type == 3) {
        if (sLocalWlMp->resendFrame != 0) {
            return;
        }
        r = LocalWlMp_FindFrame(h.frameId, sLocalWlMp->curSendFrame);
        if (r != 0) {
            sLocalWlMp->resendFrame = r;
        }
        return;
    }
    if (h.type == 2) {
        return;
    }
    e = sLocalWlMp->recvCursors[idx];
    MI_CpuCopy8(src, e->payload.records + idx * sLocalWlMp->recordSize, size);
    e->payload.aidMask = e->payload.aidMask | (1 << idx);
    sLocalWlMp->recvCursors[idx] = e->next;
}

void LocalWlMp_OnPacket(WMPortRecvCallback *m) {
    LocalWlMpWork *g;
    LocalWlMpFramePayload *p;
    if (m->length == 0) {
        return;
    }
    if (m->aid != 0) {
        LocalWlMp_StoreChildPacket(m->aid, m->data, m->length);
        return;
    }
    g = sLocalWlMp;
    p = (LocalWlMpFramePayload *)m->data;
    if (g->flags.waitFirstFrame == 0) {
        if (p->frameId != ((g->lastFrameId + 1) & 0xf)) {
            goto cc;
        }
    }
    {
        LocalWlMpFrame *e = g->recvCursors[0];
        e->payload.frameId = p->frameId;
        sLocalWlMp->recvCursors[0] = e->next;
    }
    LocalWlMp_DeliverFrame(p);
    sLocalWlMp->flags.waitFirstFrame = 0;
    sLocalWlMp->flags.resendRequest = 0;
    sLocalWlMp->lastFrameId = p->frameId;
    return;
cc:
    if (p->frameId != ((g->lastFrameId + 2) & 0xf)) {
        g->flags.frameLost = 1;
        return;
    }
    g->flags.resendRequest = 1;
    sLocalWlMp->missingFrameId = (sLocalWlMp->lastFrameId + 1) & 0xf;
}

void LocalWlMp_OnDataDisconnectStub(WMPortRecvCallback *m) {
}

void LocalWlMp_OnDataRecv(WMPortRecvCallback *m) {
    u32 t;
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode != 0) {
        return;
    }
    t = m->state;
    if (t == 7) {
        return;
    }
    if (t != 9) {
        if (t == 0x15) {
            LocalWlMp_OnPacket(m);
        }
    } else {
        LocalWlMp_OnDataDisconnectStub(m);
    }
}

void LocalWlMp_Reset(void) {
    u32 t = OS_DisableInterrupts();
    u16 i;
    sLocalWlMp->curSendFrame = sLocalWlMp->sendRing;
    LocalWlMp_ClearRing(sLocalWlMp->sendRing, 3);
    LocalWlMp_ClearRing(sLocalWlMp->recvRing, 3);
    for (i = 0; i < sLocalWl->maxMembers; i++) {
        sLocalWlMp->recvCursors[i] = sLocalWlMp->recvRing;
    }
    sLocalWlMp->lastFrameId = 0;
    sLocalWlMp->missingFrameId = 0;
    sLocalWlMp->numPendingSends = 0;
    sLocalWlMp->numRecordsInFlight = 0;
    sLocalWlMp->flags.waitFirstFrame = 1;
    sLocalWlMp->flags.frameLost = 0;
    sLocalWlMp->flags.resendRequest = 0;
    sLocalWlMp->flags.sending = 0;
    sLocalWlMp->resendFrame = 0;
    sLocalWlMp->recvActiveMask = 0;
    sLocalWlMp->sendDestMask = 0;
    sLocalWlMp->sendData = 0;
    sLocalWlMp->sendSize = 0;
    sLocalWlMp->sendOffset = -1;
    sLocalWlMp->sendDoneCallback = 0;
    OS_RestoreInterrupts(t);
}
#undef LocalWl_GetMyAid
#undef LocalWlMp_ClearRing
#undef LocalWlMp_PutParentRecord
#undef LocalWlMp_ReceiveRecord

#define data_ov066_022647bc (*(u8 *)&data_ov066_022647bc)
#define data_ov066_022647c0 (*(u16 *)&data_ov066_022647c0)
#define data_ov066_022647c4 (*(u16 *)&data_ov066_022647c4)
#define LocalWl_Alloc ((void * (*)(u32, u32))LocalWl_Alloc)
#define LocalWl_PickChannel ((s32 (*)(u32))LocalWl_PickChannel)
#define LocalWl_CompareMac ((s32 (*)(void *, void *))LocalWl_CompareMac)

s32 LocalWlMp_SetRecvBuffer(s32 idx, u8 *a, u32 b) {
    BOOL r = FALSE;
    u32 t = OS_DisableInterrupts();
    LocalWlMpWork *g = sLocalWlMp;
    LocalWlMpRecvEntry *p;
    if (g != NULL && (p = g->recvEntries) != NULL && sLocalWlSession != NULL && idx < (s32)sLocalWl->maxMembers) {
        if ((g->recvActiveMask & (1 << idx)) == 0) {
            p[idx].buffer = a;
            r = TRUE;
            p[idx].bufferSize = b;
        }
    }
    OS_RestoreInterrupts(t);
    return r;
}

void LocalWlBcn_Init(LocalWlBeaconList *o, u32 id, s32 n) {
    volatile s32 z;
    s32 i;
    s32 size = n * sizeof(LocalWlBeacon);
    o->listId = id;
    o->numUsed = 0;
    o->capacity = n;
    o->changeCallback = NULL;
    o->entries = (LocalWlBeacon *)LocalWl_Alloc(size, 0x20);
    o->alarms = (OSAlarm *)LocalWl_Alloc(n * sizeof(OSAlarm), 0x20);
    z = 0;
    MIi_CpuClearFast(z, o->entries, size);
    DC_StoreRange(o->entries, size);
    for (i = 0; i < n; i++) {
        OS_CreateAlarm(&o->alarms[i]);
    }
}

void LocalWlBcn_Free(LocalWlBeaconList *o) {
    o->numUsed = 0;
    o->capacity = 0;
    OS_CancelAlarms(o->listId + 0x80);
    LocalWl_Free(o->alarms);
    LocalWl_Free(o->entries);
}

s32 LocalWlBcn_Add(LocalWlBeaconList *o, s32 a, u8 *b, u32 c, u16 d, void *e) {
    u8 v8;
    LocalWlBeacon *r;
    s32 i;
    u32 t;
    u32 v = d;
    s32 i2;
    if (v > 0xff) {
        v = 0xff;
    }
    v8 = v;
    if (o->numUsed != 0) {
        for (i = 0; i < o->capacity; i++) {
            LocalWlBeacon *r = &o->entries[i];
            if (r->inUse == 1 && LocalWl_CompareMac(r->macAddr, b) == 0) {
                s32 j, sum, k;
                u8 nw;
                OS_CancelAlarm(&o->alarms[i]);
                t = OS_DisableInterrupts();
                o->entries[i].tag = c;
                k = (u8)(o->entries[i].linkLevelPos + 1);
                nw = k % 6;
                o->entries[i].linkLevelPos = nw;
                o->entries[i].linkLevels[nw] = v8;
                sum = 0;
                for (j = 0; j < 6; j++) {
                    sum += o->entries[i].linkLevels[j];
                }
                o->entries[i].linkLevel = sum / 6;
                MIi_CpuCopyFast(e, &o->entries[i].bssDesc, 0xc0);
                DC_StoreRange(&o->entries[i].bssDesc, 0xc0);
                OS_RestoreInterrupts(t);
                OS_SetAlarm(&o->alarms[i], a * 0x82ea / 64, LocalWlBcn_OnExpire, &o->entries[i]);
                OS_SetAlarmTag(&o->alarms[i], o->listId + 0x80);
                return TRUE;
            }
        }
    }
    i2 = 0;
    if (i2 < *(volatile u8 *)&o->capacity) {
    r = o->entries;
    do {
        if (r->inUse == 0) {
            s32 j, q;
            t = OS_DisableInterrupts();
            o->numUsed = o->numUsed + 1;
            r->inUse = 1;
            r->macAddr[0] = b[0];
            r->macAddr[1] = b[1];
            r->macAddr[2] = b[2];
            r->macAddr[3] = b[3];
            r->macAddr[4] = b[4];
            r->macAddr[5] = b[5];
            r->tag = c;
            r->ownerList = o;
            r->linkLevelPos = 0;
            for (j = 0; j < 6; j++) {
                r->linkLevels[j] = v8;
            }
            r->linkLevel = v8;
            MIi_CpuCopyFast(e, &r->bssDesc, 0xc0);
            DC_StoreRange(&r->bssDesc, 0xc0);
            OS_RestoreInterrupts(t);
            OS_CancelAlarm(&o->alarms[i2]);
            OS_SetAlarm(&o->alarms[i2], a * 0x82ea / 64, LocalWlBcn_OnExpire, &o->entries[i2]);
            OS_SetAlarmTag(&o->alarms[i2], o->listId + 0x80);
            if (o->changeCallback != NULL) {
                o->changeCallback(&o->entries[i2]);
            }
            return TRUE;
        }
        i2++;
        r++;
    } while (i2 < *(volatile u8 *)&o->capacity);
    }
    return FALSE;
}

void LocalWlBcn_OnExpire(void *arg) {
    LocalWlBeacon *r = (LocalWlBeacon *)arg;
    LocalWlBeaconList *o = r->ownerList;
    if (r->inUse != 1) {
        return;
    }
    o->numUsed = o->numUsed - 1;
    r->inUse = 0;
    if (o->changeCallback != NULL) {
        o->changeCallback(r);
    }
}

u32 LocalWlBcn_Count(LocalWlBeaconList *o) {
    return o->numUsed;
}

LocalWlBeacon *LocalWlBcn_Get(LocalWlBeaconList *o, u32 i) {
    if (i < o->capacity) {
        return &o->entries[i];
    }
    return NULL;
}

void LocalWlBcn_CancelAlarms(LocalWlBeaconList *o) {
    OS_CancelAlarms(o->listId + 0x80);
}

void LocalWlBcn_Clear(LocalWlBeaconList *o) {
    volatile s32 z;
    u32 n;
    LocalWlBcn_CancelAlarms(o);
    o->numUsed = 0;
    n = *(volatile u8 *)&o->capacity;
    z = 0;
    MIi_CpuClearFast(z, o->entries, n * sizeof(LocalWlBeacon));
    DC_StoreRange(o->entries, o->capacity * sizeof(LocalWlBeacon));
}

void LocalWlBcn_RefreshTimeouts(LocalWlBeaconList *o, s32 x) {
    s32 i = 0;
    if (i < o->capacity) {
        s32 q = x * 0x82ea / 64;
        do {
            if (o->entries[i].inUse == 1) {
                OS_CancelAlarm(&o->alarms[i]);
                OS_SetAlarm(&o->alarms[i], q, LocalWlBcn_OnExpire, &o->entries[i]);
                OS_SetAlarmTag(&o->alarms[i], o->listId + 0x80);
            }
            i++;
        } while (i < o->capacity);
    }
}

s32 LocalWl_MeasureNextChannel(u32 i) {
    if (i < 0xe) {
        do {
            if (sLocalWlSession->allowedChannelMask & (1 << i)) {
                if (LocalWl_MeasureChannel((u16)(i + 1)) != 0) {
                    return TRUE;
                }
            }
            i = (u16)(i + 1);
        } while (i < 0xe);
    }
    return FALSE;
}

void LocalWl_UpdateAllowedChannels(void) {
    u32 r = WM_GetAllowedChannel();
    if (r == 0) {
        LocalWl_SetError(0x41);
        return;
    }
    sLocalWlSession->allowedChannelMask = r;
    r = MATH_CountPopulation(r);
    sLocalWlSession->numAllowedChannels = r;
}

u32 LocalWl_NextAllowedChannel(u32 a) {
    u32 idx = a;
    u32 n = 0;
    do {
        idx = (u16)(idx + 1);
        if (idx > 0xe) {
            idx = 1;
        }
        if (sLocalWlSession->allowedChannelMask & (1 << (idx - 1))) {
            return idx;
        }
        n = (u16)(n + 1);
    } while (n < 0xe);
    return a;
}

s32 LocalWl_MeasureChannel(u32 a) {
    s32 r = WM_MeasureChannel((void *)LocalWl_OnMeasureChannel, 3, 0x11, a, 0x1e);
    if (r == 2) {
        return TRUE;
    }
    LocalWl_SetError(r);
    return FALSE;
}

void LocalWl_OnMeasureChannel(WMMeasureChannelCallback *m) {
    if (m->errcode == 0) {
        u16 a = m->ccaBusyRatio;
        u16 b = m->channel;
        if (data_ov066_022647c4 > a) {
            data_ov066_022647c4 = a;
            data_ov066_022647c0 = 1 << (b - 1);
            data_ov066_022647bc = 1;
        } else if (data_ov066_022647c4 == a) {
            data_ov066_022647c0 = data_ov066_022647c0 | (1 << (b - 1));
            data_ov066_022647bc = data_ov066_022647bc + 1;
        }
        if (LocalWl_PickChannel(b) != 0) {
            sLocalWl->state = 4;
            if (sLocalWl->channel == 0xfe) {
                sLocalWlSession->flags &= ~0x80;
            }
            LocalWl_Advance();
        }
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_StartMeasureChannels(void) {
    sLocalWl->state = 5;
    data_ov066_022647bc = 0;
    data_ov066_022647c0 = 0;
    data_ov066_022647c4 = 0x65;
    sLocalWlSession->channel = 0;
    LocalWl_PickChannel(0);
}
#undef data_ov066_022647bc
#undef data_ov066_022647c0
#undef data_ov066_022647c4
#undef LocalWl_Alloc
#undef LocalWl_PickChannel
#undef LocalWl_CompareMac

#define data_ov066_022647bc (*(u8 *)&data_ov066_022647bc)
#define data_ov066_022647c0 (*(u16 *)&data_ov066_022647c0)
#define MI_CpuFill8 ((void (*)(void *, s32, s32))MI_CpuFill8)
#define LocalWl_Alloc ((void * (*)(s32, s32))LocalWl_Alloc)
#define LocalWl_ReadBe32 ((u32 (*)(void *))LocalWl_ReadBe32)
#define LocalWl_StartConnect ((void (*)(void *))LocalWl_StartConnect)

s32 LocalWl_PickChannel(u32 start) {
    if (LocalWl_MeasureNextChannel(start) == 0) {
        if (data_ov066_022647bc != 0) {
            u8 i = 0;
            u32 t = LocalWl_Rand();
            u32 sel = (u8)(DS_UMOD(t, data_ov066_022647bc));
            u16 m = data_ov066_022647c0;
            do {
                if ((m & (1 << i)) != 0) {
                    if (sel != 0) {
                        sel = (u8)(sel - 1);
                    } else {
                        sLocalWlSession->channel = i + 1;
                        return 1;
                    }
                }
                i = i + 1;
            } while (i < 14);
        }
    }
    return 0;
}

void LocalWl_ResetSessionInfo(void) {
    u8 buf[6];
    sLocalWlSession->myAid = 0xffff;
    sLocalWlSession->numMembers = 1;
    sLocalWlSession->bits.sendingMemberTable = 0;
    sLocalWlSession->bits.memberTableResend = 0;
    sLocalWlSession->bits.endRequested = 0;
    sLocalWlSession->bits.ending = 0;
    sLocalWlSession->bits.gameInfoDirty = 0;
    sLocalWlSession->bits.startMpOnGameInfo = 0;
    sLocalWlSession->bits.retryConnect = 0;
    sLocalWlSession->bits.f10 = 0;
    if ((u8)(sLocalWl->channel + 2) <= 1) {
        sLocalWlSession->bits.autoChannel = 1;
        sLocalWlSession->channel = 0;
        sLocalWlSession->scanChannel = 0;
        sLocalWlSession->fixedChannel = 0;
    } else {
        sLocalWlSession->bits.autoChannel = 0;
        sLocalWlSession->channel = sLocalWl->channel;
        sLocalWlSession->scanChannel = 0;
        sLocalWlSession->fixedChannel = sLocalWl->channel;
    }
    MI_CpuFill8(buf, 0, 6);
    s32 i;
    for (i = 0; i < 16; i++) {
        sLocalWlSession->memberMacs[i] = *(LocalWlMacAddr *)buf;
    }
}

void LocalWl_AllocBuffers(void) {
    sLocalWlSession->parentParam = (WMParentParam *)LocalWl_Alloc(sizeof(WMParentParam), 0x20);
    sLocalWlSession->gameInfo = (LocalWlGameInfo *)LocalWl_Alloc(sizeof(LocalWlGameInfo), 0x20);
    sLocalWlSession->gameInfoLength = 8;
    u32 a = ((sLocalWl->recvChildSize + 0xe) * sLocalWl->maxChildren + 0x29) & ~0x1f;
    u32 b = (sLocalWl->recvParentSize + 0x55) & ~0x1f;
    u16 x = (u16)(a << 1);
    u16 y = (u16)(b << 1);
    if (x <= y) {
        x = y;
    }
    sLocalWlSession->recvBufSize = x;
    sLocalWlSession->recvBuf = LocalWl_Alloc(sLocalWlSession->recvBufSize, 0x20);
    a = (sLocalWl->parentMaxSize + 0x23) & ~0x1f;
    b = (sLocalWl->childMaxSize + 0x21) & ~0x1f;
    x = (u16)a;
    y = (u16)b;
    if (x <= y) {
        x = y;
    }
    sLocalWlSession->sendBufSize = x;
    sLocalWlSession->sendBuf = LocalWl_Alloc(sLocalWlSession->sendBufSize, 0x20);
    sLocalWlSession->controlBuf = (u8 *)LocalWl_Alloc(sLocalWl->childMaxSize * 2, 0x20);
    sLocalWlSession->recvCallback = 0;
    LocalWl_AllocScanWork();
    OS_GetMacAddress(sLocalWlSession->myMac);
    sLocalWlRandSeed = LocalWl_ReadBe32(sLocalWlSession->myMac + 2);
    sLocalWl->state = 2;
    sLocalWl->requestedMode = 0;
    LocalWl_ResetSessionInfo();
}

void LocalWl_InitWm(void) {
    if (sLocalWlSession != NULL) {
        return;
    }
    sLocalWlSession = (LocalWlSession *)LocalWl_Alloc(sizeof(LocalWlSession), 4);
    sLocalWlSession->wmBuf = (WMArm9Buf *)LocalWl_Alloc(0xf00, 0x20);
    if (WM_Init(sLocalWlSession->wmBuf, sLocalWl->dmaNo) == 0) {
        LocalWl_AllocBuffers();
        return;
    }
    LocalWl_Free(sLocalWlSession->wmBuf);
}

void LocalWl_FinishWm(void) {
    if (sLocalWl->state == 2) {
        if (WM_Finish() != 0) {
            return;
        }
        LocalWl_FreeScanWork();
        LocalWl_Free(sLocalWlSession->controlBuf);
        LocalWl_Free(sLocalWlSession->sendBuf);
        LocalWl_Free(sLocalWlSession->recvBuf);
        LocalWl_Free(sLocalWlSession->gameInfo);
        LocalWl_Free(sLocalWlSession->parentParam);
        LocalWl_Free(sLocalWlSession->wmBuf);
        LocalWl_Free(sLocalWlSession);
        sLocalWlSession = NULL;
        sLocalWl->state = 1;
    } else {
        LocalWl_SetError(0x44);
    }
}

void LocalWl_StartSession(void) {
    LocalWl_SetBeaconFilter(0);
    sLocalWlSession->bits.endRequested = 0;
    sLocalWlSession->resetHook();
    sLocalWlSession->bits.sendingMemberTable = 0;
    sLocalWlSession->bits.memberTableResend = 0;
    sLocalWlSession->roleTurnTarget = 0;
    sLocalWlSession->roleTurnCount = 0;
    sLocalWlSession->scanSlot = 0;
    sLocalWlSession->readyMask = 0;
    LocalWl_ClearMembers();
    LocalWl_UpdateAllowedChannels();
}

u32 LocalWl_Rand(void) {
    u32 t = sLocalWlRandSeed * 0x5eedf715 + 0x1b0cb173;
    sLocalWlRandSeed = t;
    return t;
}

u32 LocalWl_GetMyAid(void) {
    if (sLocalWlSession != NULL) {
        return sLocalWlSession->myAid;
    }
    return 0xffff;
}

u32 LocalWl_GetConnectedMask(void) {
    if (LocalWl_GetState() != 10) {
        return 0;
    }
    WMStatus *d = sLocalWlSession->wmBuf->status;
    DC_InvalidateRange(&d->f17e, 2);
    return d->f17e;
}

s32 LocalWl_IsReadyToSend(void) {
    if (sLocalWlSession != NULL) {
        if (sLocalWlSession->isReadyToSendHook != NULL) {
            return sLocalWlSession->isReadyToSendHook();
        }
    }
    return 0;
}

s32 LocalWl_Send(u8 *a, u32 b, u32 c, void (*d)(u32)) {
    if (sLocalWlSession != NULL) {
        if (sLocalWlSession->sendHook != NULL) {
            return sLocalWlSession->sendHook(a, b, c, d);
        }
    }
    return 0;
}

void LocalWl_BuildGameInfo(u32 a, u32 b) {
    LocalWlGameInfo *r = sLocalWlSession->gameInfo;
    if (a != 0xe34d) {
        r->tag = a;
    }
    sLocalWlRandSeed = sLocalWlRandSeed * 0x5eedf715 + 0x1b0cb173;
    r->nonce = sLocalWlRandSeed;
    r->scanSlot = sLocalWlSession->scanSlot;
    r->memberCount = b;
    r->version = 5;
}

void LocalWl_BuildParentParameter(u32 a) {
    WMParentParam *r = sLocalWlSession->parentParam;
    sLocalWlSession->numMembers = 1;
    LocalWl_BuildGameInfo(a, 1);
    r->userGameInfo = sLocalWlSession->gameInfo;
    r->userGameInfoLength = sLocalWlSession->gameInfoLength;
    r->ggid = sLocalWl->ggid;
    sLocalWlRandSeed = sLocalWlRandSeed * 0x5eedf715 + 0x1b0cb173;
    sLocalWlSession->tgid = sLocalWlRandSeed;
    r->tgid = sLocalWlSession->tgid;
    r->entryFlag = 1;
    r->multiBootFlag = 0;
    r->KS_Flag = 0;
    r->CS_Flag = 0;
    r->maxEntry = sLocalWl->maxChildren;
    r->beaconPeriod = WM_GetDispersionBeaconPeriod();
    r->channel = sLocalWlSession->channel;
    r->parentMaxSize = sLocalWl->parentMaxSize;
    r->childMaxSize = sLocalWl->childMaxSize;
}

void LocalWl_BeginParent(u32 a) {
    sLocalWl->state = 6;
    sLocalWlSession->numBeaconsSent = 0;
    LocalWl_BuildParentParameter(a);
    LocalWl_SetParentParameter();
}

void LocalWl_ConnectToSelected(void) {
    LocalWl_ConnectToBeacon((u8 *)sLocalWlSession->selectedBeacon, 0);
}

void LocalWl_ConnectToBeacon(u8 *p, u32 v) {
    if (sLocalWl->state != 4) {
        return;
    }
    if (p == NULL) {
        return;
    }
    sLocalWl->state = 8;
    {
        u32 w = v & 1;
        u32 c = *(u32 *)&sLocalWlSession->flags;
        *(u32 *)&sLocalWlSession->flags = (c & ~0x40) | (w << 6);
    }
    LocalWl_StartConnect(&((LocalWlBeacon *)p)->bssDesc);
}
#undef data_ov066_022647bc
#undef data_ov066_022647c0
#undef MI_CpuFill8
#undef LocalWl_Alloc
#undef LocalWl_ReadBe32
#undef LocalWl_StartConnect

#define MI_CpuFill8 ((s32 (*)(void *, u32, u32))MI_CpuFill8)
#define LocalWl_ApplyMemberTable ((void (*)(u8 *))LocalWl_ApplyMemberTable)

s32 LocalWl_SetGameInfo(void *a, u32 n) {
    if (sLocalWlSession != NULL && n <= 0x68) {
        u8 *p = (u8 *)sLocalWlSession->gameInfo;
        sLocalWlSession->bits.gameInfoDirty = 1;
        MI_CpuCopy8(a, p + 8, n);
        p[7] = n;
        sLocalWlSession->gameInfoLength = (n + 9) & ~1;
        return TRUE;
    }
    return FALSE;
}

void LocalWl_SetMember(u32 idx, u8 *src) {
    u8 buf[6];
    u8 *r;
    if (src != NULL) {
        MI_CpuCopy8(src, buf, 6);
    } else {
        MI_CpuFill8(buf, 0, 6);
    }
    r = (u8 *)sLocalWlSession->memberMacs + idx * 6;
    *(LocalWlMacAddr *)r = *(LocalWlMacAddr *)buf;
    LocalWl_CountMembers();
}

void LocalWl_SendReady(void) {
    LocalWlControlHdr h;
    u32 seed;
    seed = sLocalWlRandSeed * 0x5eedf715 + 0x1b0cb173;
    h.type = 2;
    h.size = 8;
    sLocalWlRandSeed = seed;
    h.nonce = seed;
    MI_CpuCopy8(&h, sLocalWlSession->controlBuf, 8);
    sLocalWlSession->sendControlHook(sLocalWlSession->controlBuf, 8, 1, 0);
}

void LocalWl_SendMemberTable(void) {
    LocalWlControlHdr h;
    u32 seed;
    if (sLocalWlSession->bits.sendingMemberTable != 0) {
        sLocalWlSession->bits.memberTableResend = 1;
        return;
    }
    sLocalWlSession->bits.sendingMemberTable = 1;
    sLocalWlSession->bits.memberTableResend = 0;
    h.type = 0;
    h.size = 0x68;
    seed = sLocalWlRandSeed * 0x5eedf715 + 0x1b0cb173;
    sLocalWlRandSeed = seed;
    h.nonce = seed;
    MI_CpuCopy8(&h, sLocalWlSession->controlBuf, 8);
    MI_CpuCopy8(sLocalWlSession->memberMacs, sLocalWlSession->controlBuf + 8, 0x60);
    sLocalWlSession->sendControlHook(sLocalWlSession->controlBuf, 0x68, 0xffff, LocalWl_OnMemberTableSent);
}

void LocalWl_OnMemberTableSent(void) {
    sLocalWlSession->bits.sendingMemberTable = 0;
    if (sLocalWlSession->bits.memberTableResend == 0) {
        return;
    }
    LocalWl_SendMemberTable();
}

void LocalWl_MergeMemberTable(u8 *a, u8 *b) {
    u16 i = 0;
    do {
        BOOL ra = LocalWl_IsMacSet(a + i * 6);
        BOOL rb = LocalWl_IsMacSet(b + i * 6);
        *(LocalWlMacAddr *)(a + i * 6) = *(LocalWlMacAddr *)(b + i * 6);
        if (ra == 0 && rb != 0) {
            LocalWl_PostEvent(0, i);
        }
        if (ra != 0 && rb == 0) {
            LocalWl_PostEvent(1, i);
        }
        i++;
    } while (i < 16);
}

void LocalWl_CountMembers(void) {
    s32 i;
    u8 n;
    s32 off;
    n = 0;
    i = 0;
    off = 0;
    do {
        if (LocalWl_IsMacSet((u8 *)sLocalWlSession->memberMacs + off) != 0) {
            n++;
        }
        i++;
        off += 6;
    } while (i < 16);
    sLocalWlSession->numMembers = n;
}

void LocalWl_ClearMembers(void) {
    MI_CpuFill8(sLocalWlSession->memberMacs, 0, 0x60);
}

void LocalWl_OnControlRecv(WMPortRecvCallback *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (LocalWl_CheckEndRequest() != 0) {
        return;
    }
    if (sLocalWlSession->myAid == 0) {
        LocalWl_OnParentControl(m);
        return;
    }
    LocalWl_OnChildControl(m);
}

void LocalWl_CallMemberLeftCb(u32 a) {
    if (sLocalWlSession->memberLeftHook == NULL) {
        return;
    }
    sLocalWlSession->memberLeftHook(a);
}

void LocalWl_OnBeaconSent(void) {
    if (sLocalWlSession->bits.gameInfoDirty != 0) {
        LocalWl_BuildGameInfo(0xe34d, sLocalWlSession->numMembers);
        LocalWl_UpdateGameInfo();
        sLocalWlSession->bits.gameInfoDirty = 0;
    }
    if (sLocalWl->state != 6) {
        return;
    }
    sLocalWlSession->numBeaconsSent++;
    if (sLocalWlSession->numBeaconsSent < sLocalWl->parentWaitBeacons) {
        return;
    }
    LocalWl_Advance();
}

void LocalWl_OnChildJoined(LocalWlEventMsg *m) {
    sLocalWlSession->bits.gameInfoDirty = 1;
    if (sLocalWl->state == 6) {
        sLocalWl->state = 9;
        sLocalWlSession->myAid = 0;
        LocalWl_ClearMembers();
        sLocalWlSession->bits.startMpOnGameInfo = 1;
        LocalWl_BuildGameInfo(0xbd8a, sLocalWlSession->numMembers);
        LocalWl_UpdateGameInfo();
    }
    LocalWl_SetMember(m->peerAid, m->peerMac);
    LocalWl_PostEvent(0, m->peerAid);
    if (sLocalWlSession->numMembers < sLocalWl->maxMembers) {
        return;
    }
    LocalWl_SetEntry(0);
}

void LocalWl_OnChildLeft(LocalWlEventMsg *m) {
    if (sLocalWlSession->numMembers == sLocalWl->maxMembers) {
        LocalWl_SetEntry(1);
    }
    sLocalWlSession->readyMask &= ~(1 << m->peerAid);
    LocalWl_SetMember(m->peerAid, 0);
    LocalWl_PostEvent(1, m->peerAid);
    if (sLocalWlSession->numMembers <= 1) {
        if (sLocalWlSession->bits.endRequested != 0) {
            return;
        }
        sLocalWlSession->resetHook();
        sLocalWlSession->bits.sendingMemberTable = 0;
        sLocalWlSession->bits.memberTableResend = 0;
    } else {
        LocalWl_CallMemberLeftCb(m->peerAid);
        LocalWl_SendMemberTable();
        sLocalWlSession->bits.gameInfoDirty = 1;
    }
}

void LocalWl_OnParentControl(WMPortRecvCallback *m) {
    u16 b[4];
    if (m->length == 0) {
        return;
    }
    MI_CpuCopy8(m->data, b, 4);
    if (b[0] == 0) {
        return;
    }
    if (b[0] == 1) {
        return;
    }
    if (b[0] != 2) {
        return;
    }
    LocalWl_OnChildReady(m->aid, (u8 *)m->data);
}

void LocalWl_OnChildReady(u32 idx, u8 *src) {
    u8 buf[8];
    MI_CpuCopy8(src, buf, 8);
    sLocalWlSession->readyMask |= 1 << idx;
    LocalWl_SendMemberTable();
}

void LocalWl_OnChildConnected(LocalWlEventMsg *m) {
    sLocalWl->state = 9;
    sLocalWlSession->myAid = m->myAid;
    LocalWl_StartMp();
}

void LocalWl_OnChildEvent8Stub(void) {
}

void LocalWl_OnParentLost(void) {
    sLocalWl->state = 4;
    sLocalWlSession->resetHook();
    if (sLocalWl->bits.f8 != 0) {
        LocalWl_SetMember(0, 0);
    }
    if (sLocalWlSession->bits.endRequested == 0) {
        LocalWl_Abort();
    }
    LocalWl_PostEvent(2, 0);
}

void LocalWl_OnChildControl(WMPortRecvCallback *m) {
    u16 b[4];
    if (m->length == 0) {
        return;
    }
    MI_CpuCopy8(m->data, b, 4);
    switch (b[0]) {
    case 0:
        LocalWl_ApplyMemberTable((u8 *)m->data);
        break;
    case 1:
        return;
    case 2:
        break;
    }
}
#undef MI_CpuFill8
#undef LocalWl_ApplyMemberTable

#define OS_DisableInterrupts ((s32 (*)(void))OS_DisableInterrupts)
#define OS_RestoreInterrupts ((s32 (*)(s32))OS_RestoreInterrupts)
#define LocalWl_SetMember ((void (*)(u32, void *))LocalWl_SetMember)
#define LocalWl_OnChildConnected ((void (*)(void *))LocalWl_OnChildConnected)
#define LocalWl_OnChildEvent8Stub ((void (*)(void *))LocalWl_OnChildEvent8Stub)
#define LocalWl_OnParentLost ((void (*)(void *))LocalWl_OnParentLost)
#define LocalWl_OnBeaconSent ((void (*)(void *))LocalWl_OnBeaconSent)
#define LocalWl_OnChildJoined ((void (*)(void *))LocalWl_OnChildJoined)
#define LocalWl_OnChildLeft ((void (*)(void *))LocalWl_OnChildLeft)
#define LocalWl_MergeMemberTable ((void (*)(void *, void *))LocalWl_MergeMemberTable)
#define LocalWl_OnConnectFailReset ((void (*)(void))LocalWl_OnConnectFailReset)

void LocalWl_ApplyMemberTable(void *m) {
    u8 buf[8];
    MI_CpuCopy8(m, buf, 8);
    LocalWl_MergeMemberTable((u8 *)sLocalWlSession->memberMacs, (u8 *)m + 8);
    LocalWl_CountMembers();
    if (sLocalWl->state == 9) {
        sLocalWl->state = 11;
    }
    LocalWl_Advance();
}

void LocalWl_RequestEnd(void) {
    s32 t = OS_DisableInterrupts();
    LocalWlSession *v = sLocalWlSession;
    if (v->bits.ending == 0) {
        v->bits.endRequested = 1;
    }
    OS_RestoreInterrupts(t);
}

s32 LocalWl_CheckEndRequest(void) {
    if (sLocalWlSession->bits.endRequested != 0 && sLocalWlSession->bits.ending == 0) {
        LocalWl_EndMp();
        sLocalWlSession->bits.ending = 1;
        sLocalWlSession->bits.endRequested = 0;
        return 1;
    }
    return 0;
}

void LocalWl_SetParentParameter(void) {
    s32 r = WM_SetParentParameter((void *)LocalWl_OnSetParentParameter, sLocalWlSession->parentParam);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnSetParentParameter(LocalWlEventMsg *m) {
    if (m->errcode == 0) {
        LocalWl_StartParentNow();
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_StartParentNow(void) {
    s32 r = WM_StartParent((void *)LocalWl_OnParentEvent);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnParentEvent(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        switch (m->event) {
        case 0:
            break;
        case 2:
            LocalWl_OnBeaconSent(m);
            break;
        case 7:
            LocalWl_OnChildJoined(m);
            break;
        case 9:
            if (sLocalWlSession->bits.endRequested != 0) {
                LocalWl_Abort();
            } else {
                LocalWl_OnChildLeft(m);
            }
            break;
        }
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_EndParent(void) {
    s32 r = WM_EndParent((void *)LocalWl_OnEndParent);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnEndParent(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        sLocalWl->state = 4;
        if (sLocalWlSession->bits.ending != 0) {
            LocalWl_ResetSessionInfo();
        }
        LocalWl_Advance();
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_StartConnect(void *a) {
    s32 r = WM_StartConnectEx((void *)LocalWl_OnChildConnectEvent, a, 0, 1, 0);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnChildConnectEvent(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        switch (m->event) {
        case 6:
            break;
        case 7:
            LocalWl_OnChildConnected(m);
            break;
        case 8:
            LocalWl_OnChildEvent8Stub(m);
            break;
        case 9:
            if (sLocalWlSession->bits.endRequested != 0) {
                LocalWl_Abort();
            } else {
                LocalWl_OnParentLost(m);
            }
            break;
        default:
            LocalWl_SetError(0x10);
            break;
        }
    } else if (m->errcode == 1) {
        if (sLocalWlSession->bits.retryConnect != 0) {
            LocalWl_Reset((void *)LocalWl_OnConnectFailReset);
        } else {
            LocalWl_Abort();
        }
    } else {
        LocalWl_SetError(m->errcode);
    }
}

s32 LocalWl_Disconnect(u32 a) {
    s32 r = WM_Disconnect((void *)LocalWl_OnDisconnect, a);
    if (r == 2) {
        return 1;
    }
    LocalWl_SetError(r);
    return 0;
}

void LocalWl_OnDisconnect(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        sLocalWl->state = 4;
        LocalWl_ResetSessionInfo();
        LocalWl_Advance();
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_UpdateGameInfo(void) {
    LocalWlWork *s = sLocalWl;
    u32 t = s->maxMembers;
    u32 f = (*(LocalWlSession *volatile *)&sLocalWlSession)->numMembers < t;
    LocalWlSession *v = *(LocalWlSession *volatile *)&sLocalWlSession;
    s32 r = WM_SetGameInfo((void *)LocalWl_OnSetGameInfo, v->gameInfo, v->gameInfoLength, s->ggid, v->tgid, f);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnSetGameInfo(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        if (sLocalWlSession->bits.startMpOnGameInfo == 0) {
            return;
        }
        LocalWl_StartMp();
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_StartMp(void) {
    s32 r = WM_StartMPEx((void *)LocalWl_OnMpEvent, sLocalWlSession->recvBuf, sLocalWlSession->recvBufSize,
                          sLocalWlSession->sendBuf, sLocalWlSession->sendBufSize, sLocalWl->mpFreq, 4,
                          sLocalWl->bits.f0, sLocalWl->bits.f1, 1,
                          sLocalWl->bits.f2);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnMpEvent(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        switch (m->mpEvent) {
        case 10:
            sLocalWlSession->bits.startMpOnGameInfo = 0;
            sLocalWl->bits.mpStarted = 1;
            sLocalWlSession->resetHook();
            sLocalWlSession->bits.sendingMemberTable = 0;
            sLocalWlSession->bits.memberTableResend = 0;
            if (sLocalWlSession->myAid == 0) {
                LocalWl_SetMember(0, &sLocalWlSession->myMac[0]);
                if (sLocalWl->state != 10) {
                    sLocalWl->state = 10;
                }
                LocalWl_SendMemberTable();
                LocalWl_Advance();
            } else {
                LocalWl_SendReady();
            }
            break;
        case 11:
            LocalWl_CheckEndRequest();
            if (sLocalWlSession->parentSendHook != NULL) {
                sLocalWlSession->parentSendHook();
            }
            break;
        case 12:
            LocalWl_CheckEndRequest();
            break;
        case 13:
            if (sLocalWlSession->childSendHook != NULL) {
                sLocalWlSession->childSendHook();
            }
            break;
        }
    } else {
        if (m->errcode != 9 && m->errcode != 0xd && m->errcode != 0xf) {
            LocalWl_SetError(m->errcode);
        }
    }
}

void LocalWl_EndMp(void) {
    s32 r = WM_EndMP((void *)LocalWl_OnEndMp);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnEndMp(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        if (sLocalWlSession->bits.ending == 0) {
            return;
        }
        if (sLocalWlSession->myAid == 0) {
            LocalWl_EndParent();
        } else {
            LocalWl_Disconnect(0);
        }
    } else {
        LocalWl_SetError(m->errcode);
    }
}

void LocalWl_SetEntry(u32 a) {
    s32 r = WM_SetEntry((void *)LocalWl_OnSetEntry, a);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnSetEntry(LocalWlEventMsg *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        return;
    }
    LocalWl_SetError(m->errcode);
}
#undef OS_DisableInterrupts
#undef OS_RestoreInterrupts
#undef LocalWl_SetMember
#undef LocalWl_OnChildConnected
#undef LocalWl_OnChildEvent8Stub
#undef LocalWl_OnParentLost
#undef LocalWl_OnBeaconSent
#undef LocalWl_OnChildJoined
#undef LocalWl_OnChildLeft
#undef LocalWl_MergeMemberTable
#undef LocalWl_OnConnectFailReset

#define OS_CancelAlarm ((void (*)(void *))OS_CancelAlarm)
#define OS_CreateAlarm ((void (*)(void *))OS_CreateAlarm)
#define OS_RestoreInterrupts ((void (*)(u32))OS_RestoreInterrupts)
#define LocalWl_Alloc ((void * (*)(u32, u32))LocalWl_Alloc)
#define LocalWl_ConnectToBeacon ((void (*)(void *, s32))LocalWl_ConnectToBeacon)
#define LocalWl_StartMeasureChannels ((void (*)(u32))LocalWl_StartMeasureChannels)
#define LocalWlBcn_RefreshTimeouts ((void (*)(void *, s32))LocalWlBcn_RefreshTimeouts)
#define LocalWlBcn_Clear ((void (*)(void *))LocalWlBcn_Clear)
#define LocalWlBcn_Free ((void (*)(void *))LocalWlBcn_Free)
#define LocalWlBcn_Init ((void (*)(void *, u8, u32))LocalWlBcn_Init)

void LocalWl_OnConnectFailReset(WMMsg *m) {
    LocalWl_ClearResetFlag();
    if (m->errcode == 0) {
        sLocalWl->state = 4;
        LocalWl_StartScanLoop(0x64);
    } else {
        LocalWl_SetError(m->errcode);
    }
}

u32 LocalWl_ReadBe32(u8 *p) {
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
}

s32 LocalWl_CompareMac(u8 *a, u8 *b) {
    s32 i;
    for (i = 0; i < 6; i++) {
        u32 bb = b[i];
        u32 aa = a[i];
        if (aa > bb) {
            return 1;
        }
        if (aa < bb) {
            return -1;
        }
    }
    return 0;
}

void LocalWl_StartParent(u32 v) {
    if (sLocalWlSession->bits.autoChannel) {
        LocalWl_StartMeasureChannels(v);
    } else {
        LocalWl_BeginParent(v);
    }
}

s32 LocalWl_ConnectToParent(LocalWlBeacon *p, void (*a)(u32), u32 b) {
    if (p != NULL && p->inUse != 0 && (p->tag == 0x2348 || p->tag == 0xbd8a)) {
        sLocalWlSession->selectedBeacon = p;
        sLocalWlSession->bits.beaconSelected = 1;
        return LocalWl_RequestMode(5, a, b);
    }
    return 0;
}

void LocalWl_StartScanMode(void) {
    LocalWl_StartScanLoop(0);
    LocalWl_Advance();
}

void LocalWl_NextRoleTurn(void) {
    sLocalWlSession->roleTurnCount = sLocalWlSession->roleTurnCount + 1;
    if (sLocalWlSession->roleTurnCount >= 4) {
        sLocalWlSession->roleTurnCount = 0;
        sLocalWlRandSeed = sLocalWlRandSeed * 0x5eedf715 + 0x1b0cb173;
        sLocalWlSession->roleTurnTarget = sLocalWlRandSeed & 3;
    }
}

BOOL LocalWl_JoinBestParent(void) {
    u8 i;
    LocalWlBeacon *best = NULL;
    i = 0;
    if (i < sLocalWl->maxBeacons) {
        do {
            LocalWlBeacon *e = LocalWl_GetBeacon(sLocalWlSession->scanSlot, i);
            if (e->inUse != 0) {
                if (*(volatile u16 *)&e->tag == 0xbd8a) {
                    best = e;
                    break;
                }
                if (*(volatile u16 *)&e->tag == 0x2348) {
                    if (best != NULL) {
                        if (LocalWl_CompareMac(e->macAddr, best->macAddr) != 0) {
                            best = e;
                        }
                    } else {
                        best = e;
                    }
                }
            }
            i++;
        } while (i < sLocalWl->maxBeacons);
    }
    if (best == NULL) {
        return FALSE;
    }
    LocalWl_ConnectToBeacon(best, 1);
    return TRUE;
}

void LocalWl_StepAuto(void) {
    s32 r = 0;
    if (sLocalWlSession->bits.parentFound) {
        if (LocalWl_GetBeaconCount(sLocalWlSession->scanSlot) > 0) {
            r = LocalWl_JoinBestParent();
        }
    }
    if (r != 0) {
        return;
    }
    if (sLocalWlSession->roleTurnCount == sLocalWlSession->roleTurnTarget) {
        switch (sLocalWl->state) {
        case 6:
            LocalWl_EndParent();
            break;
        case 4:
        case 7:
            LocalWl_NextRoleTurn();
            LocalWl_StartScanLoop(sLocalWl->scanLoopTime);
            break;
        }
    } else {
        switch (sLocalWl->state) {
        case 4:
            LocalWl_StartParent(0x2348);
        case 6:
            LocalWl_NextRoleTurn();
            break;
        }
    }
}

u8 LocalWl_GetMemberCount(void) {
    if (sLocalWlSession != NULL) {
        return sLocalWlSession->numMembers;
    }
    return 0;
}

BOOL LocalWl_IsMacSet(u8 *p) {
    if (p[0] != 0 || p[1] != 0 || p[2] != 0 || p[3] != 0 || p[4] != 0 || p[5] != 0) {
        return TRUE;
    }
    return FALSE;
}

void LocalWl_SetRecvCallback(void (*v)(u32, u8 *, u32)) {
    if (sLocalWlSession == NULL) {
        return;
    }
    u32 s = OS_DisableInterrupts();
    sLocalWlSession->recvCallback = v;
    OS_RestoreInterrupts(s);
}

void LocalWl_AllocScanWork(void) {
    s32 i;
    sLocalWlScan = (LocalWlScanWork *)LocalWl_Alloc(sizeof(LocalWlScanWork), 4);
    sLocalWlScan->scanParam = (WMScanParam *)LocalWl_Alloc(sizeof(WMScanParam), 0x20);
    sLocalWlScan->scanBuffer = (WMBssDesc *)LocalWl_Alloc(sizeof(WMBssDesc), 0x20);
    sLocalWlScan->beaconLists = (LocalWlBeaconList *)LocalWl_Alloc(sLocalWl->numScanChannels * sizeof(LocalWlBeaconList), 4);
    for (i = 0; i < sLocalWl->numScanChannels; i++) {
        LocalWlBcn_Init(&sLocalWlScan->beaconLists[i], i, sLocalWl->maxBeacons);
    }
    OS_CreateAlarm(&sLocalWlScan->scanTimer);
    OS_CreateAlarm(&sLocalWlScan->stopTimer);
}

void LocalWl_FreeScanWork(void) {
    s32 i;
    for (i = sLocalWl->numScanChannels - 1; i >= 0; i--) {
        LocalWlBcn_Free(&sLocalWlScan->beaconLists[i]);
    }
    LocalWl_Free(sLocalWlScan->beaconLists);
    LocalWl_Free((void *)sLocalWlScan->scanBuffer);
    LocalWl_Free(sLocalWlScan->scanParam);
    sLocalWlScan->beaconFilter = 0;
    sLocalWlScan->scanFlags.stopPending = 0;
    OS_CancelAlarm(&sLocalWlScan->stopTimer);
    OS_CancelAlarm(&sLocalWlScan->scanTimer);
    LocalWl_Free(sLocalWlScan);
    sLocalWlScan = NULL;
}

void LocalWl_SetBeaconFilter(s32 (*v)(void *)) {
    u32 s = OS_DisableInterrupts();
    sLocalWlScan->beaconFilter = v;
    OS_RestoreInterrupts(s);
}

u32 LocalWl_GetScanChannel(u32 idx) {
    u8 *p = sLocalWl->scanChannels;
    if (p != NULL) {
        return p[idx];
    }
    return LocalWl_NextAllowedChannel(sLocalWlSession->scanChannel);
}

void LocalWl_StartScanLoop(s32 t) {
    if (sLocalWl->bits.stopScanOnParent) {
        LocalWlBcn_Clear(&sLocalWlScan->beaconLists[sLocalWlSession->scanSlot]);
    } else {
        LocalWlBcn_RefreshTimeouts(&sLocalWlScan->beaconLists[sLocalWlSession->scanSlot], 0x1f4);
        LocalWl_SetBeaconFilter(0);
    }
    sLocalWlScan->scanFlags.looping = 1;
    sLocalWlScan->scanFlags.stopPending = 0;
    if (t != 0) {
        OS_CancelAlarm(&sLocalWlScan->scanTimer);
        OS_SetAlarm(&sLocalWlScan->scanTimer, t * 0x82ea / 64, LocalWl_OnScanTimer, NULL);
    }
    LocalWl_ScanNextChannel();
}

void LocalWl_OnScanTimer(void *) {
    if (sLocalWlScan->scanFlags.stopPending) {
        return;
    }
    LocalWl_StopScanLoop();
}

void LocalWl_ScanNextChannel(void) {
    sLocalWl->state = 7;
    LocalWl_SetupScanParam();
    LocalWl_StartScan();
    sLocalWlSession->scanSlot++;
    if (sLocalWlSession->scanSlot >= sLocalWl->numScanChannels) {
        sLocalWlSession->scanSlot = 0;
    }
}

void LocalWl_StopScanLoop(void) {
    sLocalWlScan->scanFlags.looping = 0;
    OS_CancelAlarm(&sLocalWlScan->scanTimer);
}

void LocalWl_SetupScanParam(void) {
    WMScanParam *r = sLocalWlScan->scanParam;
    sLocalWlSession->scanChannel = LocalWl_GetScanChannel(sLocalWlSession->scanSlot);
    r->scanBuf = sLocalWlScan->scanBuffer;
    r->channel = sLocalWlSession->scanChannel;
    r->maxChannelTime = sLocalWl->scanMaxChannelTime;
    r->bssid[0] = 0xff;
    r->bssid[1] = 0xff;
    r->bssid[2] = 0xff;
    r->bssid[3] = 0xff;
    r->bssid[4] = 0xff;
    r->bssid[5] = 0xff;
}
#undef OS_CancelAlarm
#undef OS_CreateAlarm
#undef OS_RestoreInterrupts
#undef LocalWl_Alloc
#undef LocalWl_ConnectToBeacon
#undef LocalWl_StartMeasureChannels
#undef LocalWlBcn_RefreshTimeouts
#undef LocalWlBcn_Clear
#undef LocalWlBcn_Free
#undef LocalWlBcn_Init

#define DC_InvalidateRange ((s32 (*)(void *, s32))DC_InvalidateRange)
#define LocalWl_Alloc ((void * (*)(u32, u32))LocalWl_Alloc)

void LocalWl_OnBeaconFound(WMStartScanCallback *m) {
    volatile u16 buf[4];
    DC_InvalidateRange(sLocalWlScan->scanBuffer, 0xc0);
    WMBssDesc *w = sLocalWlScan->scanBuffer;
    if (w->gameInfoLength == 0) {
        if (sLocalWl->bits.skipNoGameInfo != 0) {
            return;
        }
        LocalWlBcn_Add(&sLocalWlScan->beaconLists[sLocalWlSession->scanSlot], 0xfa0, m->macAddress, 0xacce, m->linkLevel, w);
        return;
    }
    if ((w->gameInfo.attribute & 1) == 0) {
        return;
    }
    MI_CpuCopy8(w->gameInfo.userGameInfo, (void *)buf, 8);
    DC_StoreRange((void *)buf, 8);
    if (LocalWl_FilterBeacon(m, (u8 *)buf) == 0) {
        return;
    }
    LocalWlBcn_Add(&sLocalWlScan->beaconLists[sLocalWlSession->scanSlot], 0xfa0, m->macAddress, buf[0], m->linkLevel, sLocalWlScan->scanBuffer);
    if (sLocalWl->bits.stopScanOnParent == 0) {
        return;
    }
    if (buf[0] == 0xbd8a) {
        LocalWl_StopScanSoon();
        return;
    }
    if (buf[0] != 0x2348) {
        return;
    }
    if (sLocalWlScan->scanFlags.stopPending != 0) {
        return;
    }
    OS_CancelAlarm(&sLocalWlScan->stopTimer);
    OS_SetAlarm(&sLocalWlScan->stopTimer, 0x3d5d, LocalWl_OnScanStopTimer, NULL);
    sLocalWlScan->scanFlags.stopPending = 1;
}

void LocalWl_OnScanStopTimer(void *) {
    LocalWl_StopScanSoon();
}

void LocalWl_StopScanSoon(void) {
    sLocalWlSession->flags |= 0x100;
    OS_CancelAlarm(&sLocalWlScan->stopTimer);
    LocalWl_StopScanLoop();
}

s32 LocalWl_FilterBeacon(void *a, u8 *b) {
    LocalWlWork *s = sLocalWl;
    if (s->bits.filterGgid != 0) {
        if (sLocalWlScan->scanBuffer->gameInfo.ggid != s->ggid) {
            goto fail;
        }
    }
    if (s->bits.filterScanSlot != 0) {
        if (b[4] != sLocalWlSession->scanSlot) {
            goto fail;
        }
    }
    if (s->bits.filterVersion != 0) {
        if (b[6] != 5) {
            goto fail;
        }
    }
    if (sLocalWlScan->beaconFilter == NULL) {
        return 1;
    }
    return sLocalWlScan->beaconFilter(a);
fail:
    return 0;
}

s32 LocalWl_GetBeaconCount(u32 idx) {
    LocalWlScanWork *t = sLocalWlScan;
    if (t != NULL && idx < sLocalWl->numScanChannels) {
        return LocalWlBcn_Count(&t->beaconLists[idx]);
    }
    return 0;
}

LocalWlBeacon *LocalWl_GetBeacon(u32 idx, u32 b) {
    LocalWlScanWork *t = sLocalWlScan;
    if (t != NULL && idx < sLocalWl->numScanChannels) {
        return LocalWlBcn_Get(&t->beaconLists[idx], b);
    }
    return 0;
}

void LocalWl_StartScan(void) {
    s32 r = WM_StartScan((void *)LocalWl_OnScan, sLocalWlScan->scanParam);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnScan(WMStartScanCallback *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        if (m->state != 4) {
            if (m->state != 5) {
                return;
            }
            LocalWl_OnBeaconFound(m);
        }
        if (sLocalWlScan->scanFlags.looping != 0) {
            LocalWl_ScanNextChannel();
            return;
        }
        LocalWlBcn_CancelAlarms(&sLocalWlScan->beaconLists[sLocalWlSession->scanSlot]);
        LocalWl_EndScan();
        return;
    }
    LocalWl_SetError(m->errcode);
}

s32 LocalWl_EndScan(void) {
    return WM_EndScan((void *)LocalWl_OnEndScan);
}

void LocalWl_OnEndScan(WMStartScanCallback *m) {
    if (LocalWl_IsAborting() != 0) {
        return;
    }
    if (m->errcode == 0) {
        sLocalWl->state = 4;
        LocalWl_Advance();
        return;
    }
    LocalWl_SetError(m->errcode);
}

s32 LocalWl_GetState(void) {
    s32 r = 0;
    u32 irq = OS_DisableInterrupts();
    LocalWlWork *s = sLocalWl;
    if (s != NULL) {
        r = s->state;
    }
    OS_RestoreInterrupts(irq);
    return r;
}

void LocalWl_ResetSettings(u32 a) {
    sLocalWl->requestedMode = 7;
    sLocalWl->state = 1;
    sLocalWl->channel = 0xfe;
    sLocalWl->numScanChannels = 1;
    sLocalWl->maxChildren = 0;
    sLocalWl->maxMembers = 0;
    sLocalWl->maxBeacons = 0;
    sLocalWl->dmaNo = a;
    sLocalWl->scanChannels = 0;
    sLocalWl->resetRetryCount = 0;
    sLocalWl->abortRequest = 0;
    sLocalWl->doneCallback = 0;
    sLocalWl->doneCallbackArg = 0;
    sLocalWl->eventCallback = 0;
    sLocalWl->bits.modeRequestPending = 0;
    sLocalWl->bits.resetting = 0;
    sLocalWl->bits.mpStarted = 0;
    sLocalWl->bits.modeRequestPending = 0;
}

s32 LocalWl_Init(u32 a, void *(*b)(u32, u32), void (*c)(void *), void (*d)(u32)) {
    if (sLocalWl == NULL) {
        sLocalWlAllocHook = b;
        sLocalWlFreeHook = c;
        sLocalWlErrorHook = d;
        sLocalWl = (LocalWlWork *)LocalWl_Alloc(sizeof(LocalWlWork), 4);
        if (sLocalWl != NULL) {
            OS_InitTick();
            OS_InitAlarm();
            if (func_0211f7e4() != 0) {
                LocalWl_ResetSettings(a);
                return 1;
            }
            LocalWl_SetError(0x41);
            LocalWl_Free(sLocalWl);
        }
    }
    return 0;
}

s32 LocalWl_Finish(void) {
    if (sLocalWl->state == 1) {
        sLocalWl->state = 0;
        LocalWl_Free(sLocalWl);
        sLocalWlAllocHook = NULL;
        sLocalWlFreeHook = NULL;
        sLocalWlErrorHook = NULL;
        sLocalWl = NULL;
        return 1;
    }
    LocalWl_SetError(0x44);
    return 0;
}

s32 LocalWl_IsModeReached(void) {
    s32 r = 0;
    switch (sLocalWl->requestedMode) {
    case 0:
        if (sLocalWl->state == 2) {
            r = 1;
        }
        break;
    case 1:
        if (sLocalWl->state == 3) {
            r = 1;
        }
        break;
    case 2:
        if (sLocalWl->state == 4) {
            r = 1;
        }
        break;
    case 3:
        if (sLocalWl->state == 10) {
            r = 1;
        }
        break;
    case 4:
        if (sLocalWl->state == 7) {
            r = 1;
        }
        break;
    case 5:
        if (sLocalWl->state == 11) {
            r = 1;
        }
        break;
    case 6:
        {
            s32 t = 1;
            if (sLocalWl->state != 10) {
                if (sLocalWl->state != 11) {
                    t = r;
                }
            }
            r = t;
        }
        break;
    }
    return r;
}

s32 LocalWl_RequestMode(s32 a, void (*b)(u32), u32 c) {
    if (sLocalWl == NULL) {
        return 0;
    }
    if (a >= 7 || a == sLocalWl->requestedMode) {
        return 0;
    }
    sLocalWl->requestedMode = a;
    sLocalWl->doneCallback = b;
    sLocalWl->doneCallbackArg = c;
    if (sLocalWl->bits.modeRequestPending == 0) {
        sLocalWl->bits.modeRequestPending = 1;
        LocalWl_Step();
    }
    return 1;
}

void LocalWl_StepReady(void) {
    s32 v = sLocalWl->requestedMode;
    if (v <= 0) {
        return;
    }
    LocalWl_CallPowerApi(0);
}

void LocalWl_StepEnabled(void) {
    s32 v = sLocalWl->requestedMode;
    if (v < 1) {
        LocalWl_CallPowerApi(1);
        return;
    }
    if (v <= 1) {
        return;
    }
    LocalWl_CallPowerApi(2);
}

void LocalWl_StepIdle(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
        LocalWl_CallPowerApi(3);
        break;
    case 2:
        break;
    case 3:
        LocalWl_StartParent(0xbd8a);
        break;
    case 4:
        LocalWl_StartScanMode();
        break;
    case 5:
        LocalWl_ConnectToSelected();
        break;
    case 6:
        LocalWl_StepAuto();
        break;
    }
}

void LocalWl_StepParentWaiting(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        LocalWl_Abort();
        break;
    case 3:
        break;
    }
}
#undef DC_InvalidateRange
#undef LocalWl_Alloc

#define sLocalWlAllocHook (*(s32 (**)(s32, s32))&sLocalWlAllocHook)

void LocalWl_StepScanning(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
        LocalWl_Abort();
        break;
    case 5:
        LocalWl_StopScanLoop();
        break;
    case 4:
        break;
    }
}

void LocalWl_StepConnecting(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
        LocalWl_Abort();
        break;
    case 5:
        break;
    }
}

void LocalWl_StepMeasuring(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
    case 2:
        LocalWl_Abort();
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        break;
    }
}

void LocalWl_StepParentMp(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 6:
        LocalWl_Abort();
        break;
    case 5:
        LocalWl_RequestEnd();
        break;
    case 3:
        break;
    }
}

void LocalWl_StepChildMp(void) {
    switch (sLocalWl->requestedMode) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 6:
        LocalWl_Abort();
        break;
    case 3:
        LocalWl_RequestEnd();
        break;
    case 5:
        break;
    }
}

void LocalWl_Step(void) {
    switch (sLocalWl->state) {
    case 2:
        LocalWl_StepReady();
        break;
    case 3:
        LocalWl_StepEnabled();
        break;
    case 4:
        LocalWl_StepIdle();
        break;
    case 6:
        LocalWl_StepParentWaiting();
        break;
    case 7:
        LocalWl_StepScanning();
        break;
    case 8:
        LocalWl_StepConnecting();
        break;
    case 5:
        LocalWl_StepMeasuring();
        break;
    case 10:
        LocalWl_StepParentMp();
        break;
    case 11:
        LocalWl_StepChildMp();
        break;
    case 0:
    case 1:
        LocalWl_SetError(0x44);
        break;
    default:
        LocalWl_Abort();
        break;
    }
}

void LocalWl_Abort(void) {
    LocalWl_ResetIfActive();
}

s32 LocalWl_IsAborting(void) {
    BOOL r = FALSE;
    if (sLocalWl->bits.resetting != 0) {
        r = TRUE;
    } else if (sLocalWl->abortRequest == 1) {
        LocalWl_ResetIfActive();
        r = TRUE;
    }
    return r;
}

void LocalWl_ResetIfActive(void) {
    switch (sLocalWl->state) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    default:
        LocalWl_Reset((void *)LocalWl_OnReset);
        break;
    }
}

s32 LocalWl_GetLinkLevel(void) {
    switch (sLocalWl->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    case 10:
    case 11:
        switch (WM_GetLinkLevel()) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        return 4;
    }
    return 5;
}

s32 LocalWl_GetBeaconGameInfoSize(LocalWlBeacon *r) {
    if (r != NULL && r->bssDesc.gameInfoLength != 0) {
        return ((LocalWlGameInfo *)r->bssDesc.gameInfo.userGameInfo)->userDataSize;
    }
    return 0;
}

void *LocalWl_GetBeaconGameInfo(LocalWlBeacon *r) {
    if (r != NULL && r->bssDesc.gameInfoLength != 0) {
        if (LocalWl_GetBeaconGameInfoSize(r) != 0) {
            return ((LocalWlGameInfo *)r->bssDesc.gameInfo.userGameInfo)->userData;
        }
    }
    return NULL;
}

u32 LocalWl_IsBeaconValid(WMMsg *m) {
    if (m != NULL) {
        return m->id;
    }
    return 0;
}

void LocalWl_Advance(void) {
    if (LocalWl_IsModeReached() != 0) {
        sLocalWl->flags &= ~0x800;
        if (sLocalWl->doneCallback != NULL) {
            sLocalWl->doneCallback(sLocalWl->doneCallbackArg);
            if (sLocalWl != NULL) {
                sLocalWl->doneCallback = NULL;
            }
        }
        if (sLocalWl != NULL) {
            sLocalWl->requestedMode = 7;
        }
        return;
    }
    LocalWl_Step();
}

void LocalWl_OnPowerApiDone(WMMsg *m) {
    switch (m->id) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        LocalWl_OnEnable(m);
        break;
    case 4:
        LocalWl_OnDisable(m);
        break;
    case 5:
        LocalWl_OnPowerOn(m);
        break;
    case 6:
        LocalWl_OnPowerOff(m);
        break;
    }
    LocalWl_Advance();
}

void LocalWl_CallPowerApi(u32 idx) {
    s32 r = sLocalWlPowerApis[idx]((void *)LocalWl_OnPowerApiDone);
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnEnable(WMMsg *m) {
    if (m->errcode == 0) {
        sLocalWl->state = 3;
        return;
    }
    LocalWl_SetError(m->errcode);
}

void LocalWl_OnDisable(WMMsg *m) {
    if (m->errcode == 0) {
        sLocalWl->state = 2;
        return;
    }
    LocalWl_SetError(m->errcode);
}

void LocalWl_OnPowerOn(WMMsg *m) {
    if (m->errcode == 0) {
        sLocalWl->state = 4;
        LocalWl_StartSession();
        return;
    }
    LocalWl_SetError(m->errcode);
}

void LocalWl_OnPowerOff(WMMsg *m) {
    if (m->errcode == 0) {
        sLocalWl->state = 3;
        return;
    }
    LocalWl_SetError(m->errcode);
}

void LocalWl_Reset(void *p) {
    s32 r = WM_Reset((WMCallback)p);
    sLocalWl->flags |= 0x400;
    if (r == 2) {
        return;
    }
    LocalWl_SetError(r);
}

void LocalWl_OnReset(WMMsg *m) {
    sLocalWl->abortRequest = 0;
    LocalWl_ClearResetFlag();
    if (m->errcode == 0) {
        sLocalWl->resetRetryCount = 0;
        sLocalWl->state = 4;
        LocalWl_Advance();
        return;
    }
    sLocalWl->resetRetryCount++;
    if (sLocalWl->resetRetryCount > 0x10) {
        LocalWl_SetError(m->errcode);
        return;
    }
    LocalWl_Reset((void *)LocalWl_OnReset);
}

void LocalWl_ClearResetFlag(void) {
    sLocalWl->flags &= ~0x400;
}

s32 LocalWl_Alloc(s32 a, s32 b) {
    if (sLocalWlAllocHook != NULL) {
        s32 r = sLocalWlAllocHook(a, b);
        if (r != 0) {
            return r;
        }
    }
    LocalWl_SetError(0x42);
    return 0;
}

void LocalWl_Free(void *p) {
    if (sLocalWlFreeHook == NULL) {
        return;
    }
    if (p == NULL) {
        return;
    }
    sLocalWlFreeHook(p);
}

void LocalWl_SetError(u32 v) {
    sLocalWl->state = v | 0x80;
    sLocalWl->flags &= ~0x800;
    if (sLocalWlErrorHook == NULL) {
        return;
    }
    sLocalWlErrorHook(v);
}

void LocalWl_CallEventCallback(void *p) {
    if (sLocalWl == NULL) {
        return;
    }
    if (sLocalWl->eventCallback == NULL) {
        return;
    }
    sLocalWl->eventCallback(p);
}

void LocalWl_PostEvent(u32 a, u32 b) {
    u8 buf[2];
    buf[0] = a;
    buf[1] = b;
    LocalWl_CallEventCallback(buf);
}

s32 LocalWl_SetEventCallback(void (*fn)(void *)) {
    if (sLocalWl != NULL) {
        sLocalWl->eventCallback = fn;
        return TRUE;
    }
    return FALSE;
}
#undef sLocalWlAllocHook

}
#pragma thumb reset

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov066_0225f1a0) {
    HOST_OVERLAY_VAR(sLocalWlPowerApis),
    HOST_OVERLAY_VAR(data_ov066_022647c4),
    HOST_OVERLAY_VAR(data_ov066_022647c0),
    HOST_OVERLAY_VAR(data_ov066_022647bc),
    HOST_OVERLAY_VAR(sLocalWlRandSeed),
    HOST_OVERLAY_VAR(sLocalWlSession),
    HOST_OVERLAY_VAR(sLocalWlMp),
    HOST_OVERLAY_VAR(sLocalWl),
    HOST_OVERLAY_VAR(sLocalWlAllocHook),
    HOST_OVERLAY_VAR(sLocalWlScan),
    HOST_OVERLAY_VAR(sLocalWlErrorHook),
    HOST_OVERLAY_VAR(sLocalWlFreeHook),
    HOST_OVERLAY_VARS_END
};

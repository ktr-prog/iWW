#include "nitro/wm.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_0211ef94.h"
#include "proto/autoload_2/unk_0211f800.h"
#include "proto/autoload_2/unk_02120fe8.h"
#include "proto/autoload_2/unk_0212703c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct {
    u8 _0[4];
    u16 num;
    u16 size;
    u16 _8;
    u8 data[1];
} WMSet;

typedef struct {
    u16 hdr;
    u8 data[510];
} WMPacket;

typedef struct {
    WMPacket pkt[4];
    u16 slot[4];
    u16 cur;
    u16 f80a;
    u16 f80c;
    u16 f80e;
    u16 f810;
    u16 f812;
    u16 f814;
    u16 f816;
    u16 f818;
    u16 f81a;
    u16 f81c;
} WMPool;

#define W8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define W16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern u32 WMi_CheckInitialized(void);
extern u32 WMi_CheckIdle(void);
extern u32 WMi_CheckStateEx(int n, ...);
extern u32 WMi_SendCommand(u32 id, u16 paramNum, ...);
extern void WMi_SetCallbackTable(u32 idx, WMCallback cb);
extern u32 WM_Init(void *buf, u16 dmaNo);
extern void DC_InvalidateRange(void *, u32);
extern void DC_StoreRange(void *, u32);
extern void MIi_CpuCopyFast(void *, void *, u32);
extern void MI_CpuCopy8(void *, void *, u32);
extern void MI_CpuFill8(void *, u32, u32);
extern void MIi_CpuClear16(u32, void *, u32);
extern u32 MATH_CountPopulation(u32);
extern u32 WMi_StartParentEx(WMCallback cb, u32 arg);

u32 WM_SetMPDataToPortEx(WMCallback cb, void *arg, void *sendData, u16 size, u16 destBitmap, u16 port, u16 prio);
u16 *WmGetSharedDataAddress(u8 *base, u32 x, u16 *y, u32 n);
BOOL WmCheckParentParameter(WMParentParam *p);
void WmDataSharingSendDataSet(WMPool *buf, BOOL flag) {
    WMStatus *st = WMi_GetSystemWork()->status;
    u32 irq = OS_DisableInterrupts();
    if (buf->pkt[buf->cur].hdr == 0) {
        u32 nextNext, cur, ack, next;
        volatile u16 zero;
        int ret;
        DC_InvalidateRange(&st->f86, 2);
        cur = buf->cur;
        ack = st->f86;
        next = (u16)((cur + 1) & 3);
        if (buf->f818 == 1) {
            nextNext = (u16)((next + 1) & 3);
        } else {
            nextNext = next;
        }
        zero = 0;
        MIi_CpuClear16(zero, &buf->pkt[nextNext], 512);
        buf->pkt[nextNext].hdr = buf->f80e & (ack | 1);
        buf->cur = next;
        buf->pkt[cur].hdr = buf->f80e;
        if (flag == 1) buf->pkt[cur].hdr &= ~1;
        OS_RestoreInterrupts(irq);
        ret = WM_SetMPDataToPortEx(WmDataSharingSetDataCallback, buf, &buf->pkt[cur], buf->f814, buf->f80e & ack, buf->f816, 1);
        if (ret == 7) {
            buf->slot[cur] = 0xffff;
            buf->f80a = (buf->f80a + 1) & 3;
        } else if (ret != 0) {
            if (ret != 2) buf->f81c = 5;
        }
    } else {
        OS_RestoreInterrupts(irq);
    }
}

u16 *WM_GetSharedDataAddress(u8 *base, u16 *p, u32 n) {
    u32 b = p[1];
    u32 m = 1 << n;
    u32 a = p[0];
    if (base == 0) return 0;
    if (p == 0) return 0;
    if ((a & m) == 0) return 0;
    if ((b & m) == 0) return 0;
    return WmGetSharedDataAddress(base, a, p + 2, n);
}

u16 *WmGetSharedDataAddress(u8 *base, u32 x, u16 *y, u32 n) {
    return (u16 *)((u8 *)y + W16(base, 0x810) * MATH_CountPopulation(x & ((1 << n) - 1)));
}

u32 WM_StartDCF(WMCallback cb, void *ptr, u32 len) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(1, 8);
    if (r != 0) return r;
    DC_InvalidateRange(&w->status->f10, 4);
    if (w->status->f10 == 1) return 3;
    if (len < 16) return 6;
    if (ptr == 0) return 6;
    DC_StoreRange(ptr, len);
    WMi_SetCallbackTable(17, cb);
    r = WMi_SendCommand(17, 2, WM_ARM7_ADDR(ptr), len);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetDCFData(WMCallback cb, void *mac, void *buf, u32 len) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 m[2];
    u32 r = WMi_CheckStateEx(1, 11);
    if (r != 0) return r;
    DC_InvalidateRange(&w->status->f10, 4);
    if (w->status->f10 == 0) return 3;
    if (len > 0x5e4) return 6;
    DC_StoreRange(buf, len);
    WMi_SetCallbackTable(18, cb);
    MI_CpuCopy8(mac, m, 6);
    r = WMi_SendCommand(18, 4, m[0], m[1], WM_ARM7_ADDR(buf), len);
    if (r == 0) r = 2;
    return r;
}

u32 WM_EndDCF(WMCallback cb) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(1, 11);
    if (r != 0) return r;
    DC_InvalidateRange(&w->status->f10, 4);
    if (w->status->f10 == 0) return 3;
    WMi_SetCallbackTable(19, cb);
    r = WMi_SendCommand(19, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_StartMPEx(WMCallback cb, void *a, u16 len, void *c, u16 s1, u16 s2, u16 s3, u32 s4, u32 s5, u32 s6, u32 s7) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(2, 7, 8);
    if (r != 0) return r;
    DC_InvalidateRange(&w->status->f184, 2);
    DC_InvalidateRange(&w->status->fc2, 2);
    if (w->status->f184 != 0) {
        if (w->status->fc2 != 1) return 3;
    }
    DC_InvalidateRange(&w->status->f0c, 4);
    if (w->status->f0c == 1) return 3;
    if (len < WM_GetMPReceiveBufferSize()) return 6;
    if ((len & 0x3f) != 0) return 6;
    {
        int t = s1;
        if (t < WM_GetMPSendBufferSize()) return 6;
        if ((t & 0x1f) != 0) return 6;
    }
    WMi_SetCallbackTable(14, cb);
    r = WMi_SendCommand(14, 10, WM_ARM7_ADDR(a), (u32)len >> 1, WM_ARM7_ADDR(c), s1, s2, s3, s4, s5, s6, s7);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetMPDataToPortEx(WMCallback cb, void *arg, void *sendData, u16 size, u16 destBitmap, u16 port, u16 prio) {
    int maxSize;
    u16 mask = 1;
    WMStatus *st = WMi_GetSystemWork()->status;
    BOOL parent;
    u32 r = WMi_CheckStateEx(2, 9, 10);
    if (r != 0) return r;
    DC_InvalidateRange(&st->f18e, 2);
    maxSize = st->f18e;
    DC_InvalidateRange(&st->f184, 2);
    parent = st->f184 == 0 ? 1 : 0;
    if (parent == 1) {
        DC_InvalidateRange(&st->f17e, 2);
        mask = st->f17e;
        DC_InvalidateRange(&st->f86, 2);
    }
    if (sendData == 0) return 6;
    if (mask == 0) return 7;
    DC_InvalidateRange(&st->f50, 2);
    if (WM_ARM7_ADDR(sendData) == st->f50) return 6;
    if (size + (parent != 0 ? 4 : 2) > maxSize) return 6;
    if (size == 0) return 6;
    DC_StoreRange(sendData, size);
    r = WMi_SendCommand(15, 7, WM_ARM7_ADDR(sendData), size, destBitmap, port, prio, WM_ARM7_ADDR(cb),
                        WM_ARM7_ADDR(arg));
    if (r == 0) r = 2;
    return r;
}

u32 WM_EndMP(WMCallback cb) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(2, 9, 10);
    if (r != 0) return r;
    DC_InvalidateRange(&w->status->f0c, 4);
    if (w->status->f0c == 0) return 3;
    WMi_SetCallbackTable(16, cb);
    r = WMi_SendCommand(16, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_Enable(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 0);
    if (r != 0) return r;
    WMi_SetCallbackTable(3, cb);
    {
        WMArm9Buf *w = WMi_GetSystemWork();
        r = WMi_SendCommand(3, 3, WM_ARM7_ADDR(w->w0), WM_ARM7_ADDR(w->status), WM_ARM7_ADDR(w->f10));
    }
    if (r == 0) r = 2;
    return r;
}

u32 WM_Disable(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 1);
    if (r != 0) return r;
    WMi_SetCallbackTable(4, cb);
    r = WMi_SendCommand(4, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_PowerOn(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 1);
    if (r != 0) return r;
    WMi_SetCallbackTable(5, cb);
    r = WMi_SendCommand(5, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_PowerOff(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 2);
    if (r != 0) return r;
    WMi_SetCallbackTable(6, cb);
    r = WMi_SendCommand(6, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_Initialize(void *buf, WMCallback cb, u16 dmaNo) {
    WMArm9Buf *w;
    u32 r = WM_Init(buf, dmaNo);
    if (r != 0) return r;
    WMi_SetCallbackTable(0, cb);
    w = WMi_GetSystemWork();
    r = WMi_SendCommand(0, 3, WM_ARM7_ADDR(w->w0), WM_ARM7_ADDR(w->status), WM_ARM7_ADDR(w->f10));
    if (r == 0) r = 2;
    return r;
}

u32 WM_Reset(WMCallback cb) {
    u32 r = WMi_CheckIdle();
    if (r != 0) return r;
    WMi_SetCallbackTable(1, cb);
    r = WMi_SendCommand(1, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_End(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 2);
    if (r != 0) return r;
    WMi_SetCallbackTable(2, cb);
    r = WMi_SendCommand(2, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetParentParameter(WMCallback cb, WMParentParam *p) {
    u32 r = WMi_CheckStateEx(1, 2);
    u32 n;
    if (r != 0) return r;
    if (p == 0) return 6;
    if (p->userGameInfoLength != 0) {
        if (p->userGameInfo == 0) return 6;
    }
    n = p->KS_Flag;
    if (p->parentMaxSize + (n != 0 ? 42 : 0) > 512 || p->childMaxSize + (n != 0 ? 6 : 0) > 512) return 6;
    WmCheckParentParameter(p);
    WMi_SetCallbackTable(7, cb);
    DC_StoreRange(p, sizeof(WMParentParam));
    if (p->userGameInfoLength != 0) DC_StoreRange(p->userGameInfo, p->userGameInfoLength);
    r = WMi_SendCommand(7, 1, WM_ARM7_ADDR(p));
    if (r == 0) r = 2;
    return r;
}

BOOL WmCheckParentParameter(WMParentParam *p) {
    u32 v = p->userGameInfoLength;
    if (v > 0x70) return 0;
    v = p->beaconPeriod;
    if (v < 10 || v > 1000) return 0;
    v = p->channel;
    if (v < 1 || v > 14) return 0;
    return 1;
}

u32 WMi_StartParentEx(WMCallback cb, u32 arg) {
    u32 r = WMi_CheckStateEx(1, 2);
    if (r != 0) return r;
    WMi_SetCallbackTable(8, cb);
    r = WMi_SendCommand(8, 1, arg);
    if (r == 0) r = 2;
    return r;
}

u32 WM_StartParent(WMCallback cb) {
    return WMi_StartParentEx(cb, 1);
}

u32 WM_EndParent(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 7);
    if (r != 0) return r;
    WMi_SetCallbackTable(9, cb);
    r = WMi_SendCommand(9, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_StartScan(WMCallback cb, WMScanParam *p) {
    u32 r = WMi_CheckStateEx(3, 2, 3, 5);
    WMScanReq *m;
    if (r != 0) return r;
    if (p == 0) return 6;
    if (p->scanBuf == 0) return 6;
    if (p->channel < 1 || p->channel > 14) return 6;
    WMi_SetCallbackTable(10, cb);
    m = (WMScanReq *)WMi_GetSystemWork()->req;
    m->apiid = 10;
    m->channel = p->channel;
    m->scanBuf = WM_ARM7_ADDR(p->scanBuf);
    m->maxChannelTime = p->maxChannelTime;
    m->bssid[0] = p->bssid[0];
    m->bssid[1] = p->bssid[1];
    m->bssid[2] = p->bssid[2];
    m->bssid[3] = p->bssid[3];
    m->bssid[4] = p->bssid[4];
    m->bssid[5] = p->bssid[5];
    r = WMi_SendCommand(10, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_StartScanEx(WMCallback cb, WMScanExParam *p) {
    u32 r = WMi_CheckStateEx(3, 2, 3, 5);
    WMScanExReq *m;
    u32 v;
    if (r != 0) return r;
    if (p == 0) return 6;
    if (p->scanBuf == 0) return 6;
    if (p->scanBufSize > 0x400) return 6;
    if (p->ssidLength > 32) return 6;
    v = p->scanType;
    if (v != 0 && v != 1 && v != 2 && v != 3) return 6;
    if ((u16)(v + 0xfffe) <= 1) {
        if (p->ssidMatchLength > 32) return 6;
    }
    WMi_SetCallbackTable(38, cb);
    m = (WMScanExReq *)WMi_GetSystemWork()->req;
    m->apiid = 38;
    m->channelList = p->channelList;
    m->scanBuf = WM_ARM7_ADDR(p->scanBuf);
    m->scanBufSize = p->scanBufSize;
    m->maxChannelTime = p->maxChannelTime;
    MI_CpuCopy8(p->bssid, m->bssid, 6);
    m->scanType = p->scanType;
    m->ssidMatchLength = p->ssidMatchLength;
    m->ssidLength = p->ssidLength;
    MI_CpuCopy8(p->ssid, m->ssid, 32);
    r = WMi_SendCommand(38, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_EndScan(WMCallback cb) {
    u32 r = WMi_CheckStateEx(1, 5);
    if (r != 0) return r;
    WMi_SetCallbackTable(11, cb);
    r = WMi_SendCommand(11, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_StartConnectEx(WMCallback cb, WMBssDesc *bss, u8 *ssid, u32 arg, u16 extra) {
    u32 r = WMi_CheckStateEx(1, 2);
    WMConnectReq *m;
    if (r != 0) return r;
    if (bss == 0) return 6;
    DC_StoreRange(bss, bss->length << 1);
    WMi_SetCallbackTable(12, cb);
    m = (WMConnectReq *)WMi_GetSystemWork()->req;
    m->apiid = 12;
    m->pInfo = WM_ARM7_ADDR(bss);
    if (ssid != 0) {
        MI_CpuCopy8(ssid, m->ssid, 24);
    } else {
        MI_CpuFill8(m->ssid, 0, 24);
    }
    m->powerSave = arg;
    m->authMode = extra;
    r = WMi_SendCommand(12, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_Disconnect(WMCallback cb, u32 aid) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(5, 7, 9, 8, 10, 11);
    if (r != 0) return r;
    if (w->status->state == 7 || w->status->state == 9) {
        if (aid < 1 || aid > 15) return 6;
        DC_InvalidateRange(&w->status->f17e, 2);
        if ((w->status->f17e & (1 << aid)) == 0) return 7;
    } else {
        if (aid != 0) return 6;
    }
    WMi_SetCallbackTable(13, cb);
    r = WMi_SendCommand(13, 1, 1 << aid);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetIndCallback(WMCallback cb) {
    u32 irq = OS_DisableInterrupts();
    u32 r = WMi_CheckInitialized();
    if (r != 0) {
        OS_RestoreInterrupts(irq);
        return r;
    }
    WMi_GetSystemWork()->cbC0 = cb;
    OS_RestoreInterrupts(irq);
    return 0;
}

u32 WM_SetPortCallback(u16 port, WMCallback cb, void *arg) {
    u32 irq = OS_DisableInterrupts();
    u32 r = WMi_CheckInitialized();
    if (r != 0) {
        OS_RestoreInterrupts(irq);
        return r;
    }
    {
        WMArm9Buf *w = WMi_GetSystemWork();
        w->portCb[port] = cb;
        w->portArg[port] = arg;
    }
    OS_RestoreInterrupts(irq);
    return 0;
}

u32 WM_ReadStatus(void *dst) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckInitialized();
    if (r != 0) return r;
    if (dst == 0) return 6;
    DC_InvalidateRange(w->status, 0x7bc);
    MIi_CpuCopyFast(w->status, dst, 0x7bc);
    return 0;
}

int WM_GetMPSendBufferSize(void) {
    WMArm9Buf *w = WMi_GetSystemWork();
    if (WMi_CheckStateEx(2, 7, 8) != 0) return 0;
    DC_InvalidateRange(&w->status->f0c, 4);
    if (w->status->f0c == 1) return 0;
    DC_InvalidateRange(&w->status->f18e, 4);
    return (w->status->f18e + 31) & ~31;
}

int WM_GetMPReceiveBufferSize(void) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 a;
    BOOL idle;
    if (WMi_CheckStateEx(2, 7, 8) != 0) return 0;
    DC_InvalidateRange(&w->status->f0c, 4);
    if (w->status->f0c == 1) return 0;
    DC_InvalidateRange(&w->status->f184, 2);
    idle = w->status->f184 == 0 ? 1 : 0;
    DC_InvalidateRange(&w->status->f190, 2);
    a = w->status->f190;
    if (idle != 1) return ((a + 81) & ~31) << 1;
    DC_InvalidateRange(&w->status->ff4, 2);
    return (((a + 12) * w->status->ff4 + 41) & ~31) << 1;
}

u8 *WM_ReadMPData(WMSet *p, u32 ch) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u8 *a[16];
    int i;
    if (WMi_CheckInitialized() != 0) return 0;
    if (ch < 1 || ch > 15) return 0;
    DC_InvalidateRange(&w->status->f17e, 2);
    if ((w->status->f17e & (1 << ch)) == 0) return 0;
    if (p->num == 0) return 0;
    a[0] = p->data;
    i = 0;
    do {
        if (ch == W16(a[i], 4)) return a[i];
        i++;
        a[i] = a[i - 1] + p->size;
    } while (i < p->num);
    return 0;
}

u32 WM_GetAllowedChannel(void) {
    if (WMi_CheckInitialized() != 0) return 0x8000;
    return *HW_SYSWORK_AT(u16, nvramUserInfo, 0x7a);
}

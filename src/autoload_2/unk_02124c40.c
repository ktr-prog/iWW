#include "proto/autoload_2/unk_02122e24.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_02124480.h"
#include "proto/autoload_2/unk_02124c40.h"
#include "proto/autoload_2/unk_02125c94.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
typedef int s32;
typedef int BOOL;

typedef void (*WCb)(void *);

typedef struct { u32 w[32]; } W128;

typedef struct {
    u8 scan[0xc0];
    u8 _c0[10];
    u8 mac[6];
    u8 _d0[0x26];
    u16 f0f6;
    W128 f0f8;
    u8 _178[8];
} WScan;

typedef struct {
    u8 _00[8];
    u32 f08;
    u16 f0c;
    u16 f0e;
    u16 f10;
    u16 f12;
    u16 f14;
    u16 f16;
    u16 f18;
    u8 _1a[0x32 - 0x1a];
    u16 f32;
    u16 f34;
    u16 f36;
    u8 _38[0x440 - 0x38];
    u8 scanbuf[0x500 - 0x440];
    u16 f500;
    u16 f502;
    void *f504;
    WCb cb508;
    u8 f50c;
    u8 f50d;
    u8 _50e[0x518 - 0x50e];
    u16 f518;
    u16 f51a;
    void (*cb51c)(u32, void *);
    u32 f520;
    u16 f524;
    u16 f526;
    u16 f528;
    u16 f52a;
    u16 f52c;
    u8 _52e[0x530 - 0x52e];
    u16 f530[4];
    u16 f538[16];
    u8 _558[0x5e0 - 0x558];
    u16 f5e0;
    u16 f5e2;
    u32 f5e4;
    u32 f5e8;
    u32 f5ec;
    u8 _5f0[0x600 - 0x5f0];
    WScan scan[16];
} WCtl;

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    u8 mac[6];
    u8 _10[0x26];
    u16 f36;
    W128 f38;
} WMsg;

typedef struct {
    u8 _0;
    u8 n;
} WChList;

typedef struct {
    void *buf;
    u16 f4;
    u16 f6;
    u8 bssid[6];
} WScanParam;

typedef struct {
    u8 _0[0x1300];
    u8 f1300[22];
    u16 f1316;
    u32 f1318;
    u32 f131c;
    u32 f1320;
    u8 _1324[0x1340 - 0x1324];
    u8 ent[15][22];
    u16 f148a[15];
    u32 f14a8[15];
    void (*cb)();
    u32 state[15];
    u8 f1524;
    u8 _1525;
    s8 slot[15];
    u8 cnt1535;
    u16 mask1536;
    u8 _1538[0x1754 - 0x1538];
    u16 st16[15];
    u8 _1772[0x1788 - 0x1772];
    u8 peers[16][0x5d4];
} WWork;

extern WCtl *data_02200018;
extern WWork *data_0220001c;
extern u16 data_02200010;
extern u8 *data_02200014;
extern WScanParam data_02200020;
extern u16 data_0213c20c;
extern u16 data_0213c210;
extern u16 data_0213c214;
extern u16 data_0213c218;
extern u16 *data_0213c21c;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void DC_InvalidateRange(void *, u32);
extern void OS_GetMacAddress(u8 *);
extern void MI_DmaCopy16(u32, void *, void *, u32);
extern void MIi_CpuClear16(u32, void *, u32);
extern void MIi_CpuCopy16(void *, void *, u32);
extern void MIi_CpuClear32(u32, void *, u32);
extern void MI_CpuFill8(void *, u32, u32);
extern void MI_CpuCopy8(void *, void *, u32);
extern u32 PXI_IsCallbackReady(u32, u32);
extern u32 WM_GetNextTgid(void);
extern u32 WM_SetPortCallback(u32, void *, u32);
extern u32 WM_SetIndCallback(WCb);
extern u32 WM_Disconnect(WCb, u32);
extern u32 WM_StartConnectEx(WCb, u32, u32, u32, u32);
extern u32 WM_StartScan(WCb, void *);
extern u32 WM_End(WCb);
extern u32 WM_Reset(WCb);
extern u32 WM_Initialize(void *, WCb, u32);
extern u32 WM_SetMPDataToPortEx(WCb cb, void *arg, void *data, u16 size, u16 bitmap, u16 port, u16 prio);
extern u32 WM_StartMPEx(WCb, void *, u32, void *, u32, u32, u32, u32, u32, u32, u32);
extern u32 WM_SetLifeTime(WCb, u32, u32, u32, u32);
extern u32 MBi_IsSendEnabled(void);
extern u32 changeScanChannel(void *);
extern void MBi_EndTaskThread(void *);
extern u32 MBi_IsTaskAvailable(void);
extern void MBi_ClearParentPieceBuffer(u32);
extern void MBi_SetChildMPMaxSize(u32);
extern void MBi_ParentCallback(void *);
extern void MBi_CommParentCallback(u32, void *);
extern void MBi_ChildPortCallback(void *);

void MBi_CheckWmErrcode(u32 id, u32 res);
void MBi_SetMaxScanTime(u32 t);
u32 MBi_SetMPData(WCb cb, void *a, u32 b, u32 c, u16 d);
BOOL MBi_CommEnd(void);
BOOL MBi_OnReset(void);
BOOL MBi_CallReset(void);
u32 MBi_StartParentCore(u32 a);
u32 MBi_StartCommon(void);
BOOL MBi_IsCommSizeValid(u32 a, u32 c, u32 d);
u32 MBi_GetBeaconPeriodDispersion(void);

void MBi_ChildCallback(void *arg) {
    WMsg *msg = arg;
    WCtl *g = data_02200018;
    int i;
    switch (msg->f0) {
    case 0:
        if (msg->f2 != 0) {
            g->cb51c(0x100, msg);
            return;
        }
        g->cb51c(21, msg);
        MBi_CheckWmErrcode(29, WM_SetLifeTime(MBi_ChildCallback, data_0213c218, data_0213c210, data_0213c20c, data_0213c214));
        return;
    case 29:
        if (msg->f2 != 0) {
            g->cb51c(0x100, msg);
            return;
        }
        data_02200020.buf = g->scanbuf;
        if (data_02200020.f4 == 0) data_02200020.f4 = 1;
        if (data_02200020.f6 == 0) data_02200020.f6 = 200;
        data_02200020.bssid[0] = 0xff;
        data_02200020.bssid[1] = 0xff;
        data_02200020.bssid[2] = 0xff;
        data_02200020.bssid[3] = 0xff;
        data_02200020.bssid[4] = 0xff;
        data_02200020.bssid[5] = 0xff;
        g->f5e4 = 1;
        g->f5e8 = 1;
        MBi_CheckWmErrcode(10, WM_StartScan(MBi_ChildCallback, &data_02200020));
        return;
    case 10:
        if (msg->f2 != 0) {
            g->cb51c(0x100, msg);
            return;
        }
        switch (msg->f8) {
        case 3:
            return;
        case 5: {
            WScan *base = g->scan;
            i = 0;
            if ((s32)g->f5e0 > 0) {
                WScan *s = base;
                do {
                    if (msg->mac[0] == s->mac[0] && msg->mac[1] == s->mac[1] && msg->mac[2] == s->mac[2] &&
                        msg->mac[3] == s->mac[3] && msg->mac[4] == s->mac[4] && msg->mac[5] == s->mac[5]) {
                        base[i].f0f6 = msg->f36;
                        base[i].f0f8 = msg->f38;
                        DC_InvalidateRange(&g->scan[i], 0xc0);
                        MI_DmaCopy16(data_02200010, g->scanbuf, &g->scan[i], 0xc0);
                        g->f5ec = i;
                        goto done;
                    }
                    i++;
                    s++;
                } while (i < g->f5e0);
            }
            if (i < 16) {
                g->f5e0 = i + 1;
                MIi_CpuCopy16(msg, (u8 *)&base[i] + 0xc0, 0xb8);
                DC_InvalidateRange(&g->scan[i], 0xc0);
                MI_DmaCopy16(data_02200010, g->scanbuf, &g->scan[i], 0xc0);
                g->f5ec = i;
            }
        done:
            g->cb51c(4, msg);
            if (g->f5e4 == 0) return;
            if (g->f5e8 != 0) {
                if (changeScanChannel(&data_02200020) == 0) MBi_CommEnd();
            }
            MBi_CheckWmErrcode(10, WM_StartScan(MBi_ChildCallback, &data_02200020));
            return;
        }
        case 4:
            g->cb51c(5, msg);
            if (g->f5e4 == 0) return;
            if (g->f5e8 != 0) {
                if (changeScanChannel(&data_02200020) == 0) MBi_CommEnd();
            }
            MBi_CheckWmErrcode(10, WM_StartScan(MBi_ChildCallback, &data_02200020));
            return;
        default:
            g->cb51c(0x100, msg);
            return;
        }
    case 11:
        if (msg->f2 != 0) {
            g->cb51c(0x100, msg);
            return;
        }
        MBi_CheckWmErrcode(12, WM_StartConnectEx(MBi_ChildCallback, g->f520, 0, 1, 0));
        return;
    case 12:
        if (msg->f2 != 0) {
            g->f5e0 = 0;
            g->cb51c(11, msg);
            return;
        }
        switch (msg->f8) {
        case 6:
            g->f52a = 0;
            g->f528 = 1;
            return;
        case 7:
            g->f5e2 = ((u16 *)msg)[5];
            g->cb51c(6, msg);
            g->f52a = 1;
            if (WM_SetPortCallback(1, MBi_ChildPortCallback, 0) != 0) return;
            MBi_CheckWmErrcode(14, WM_StartMPEx(MBi_ChildCallback, g->f504, g->f51a, (u8 *)g + 0x40, g->f518, (u16)(g->f52c == 0), 0, 0, 0, 1, 1));
            return;
        case 9:
            g->cb51c(10, msg);
            g->f52a = 0;
            g->f528 = 0;
            return;
        default:
            g->cb51c(0x100, msg);
            return;
        }
    case 14:
        switch (msg->f4) {
        case 10:
            g->f528 = 1;
            if (MBi_IsSendEnabled() == 0) return;
            g->cb51c(25, 0);
            return;
        case 12:
            return;
        case 13:
            return;
        default:
            g->cb51c(0x100, msg);
            return;
        }
    case 15:
        g->f50c = 0;
        if (msg->f2 == 0) {
            g->cb51c(8, msg);
        } else if (msg->f2 == 9) {
            g->cb51c(41, msg);
        } else {
            g->cb51c(18, msg);
        }
        g->cb51c(25, 0);
        return;
    case 1:
        if (msg->f2 != 0) {
            g->f526 = 0;
            g->cb51c(0x100, msg);
            return;
        }
        g->f52a = 0;
        data_02200018->f528 = 0;
        MBi_CheckWmErrcode(2, WM_End(MBi_ChildCallback));
        return;
    case 2:
        if (msg->f2 != 0) {
            g->f526 = 0;
            g->cb51c(0x100, msg);
            return;
        }
        g->f50d = 0;
        data_0220001c->f1316 = 0;
        g->cb51c(17, msg);
        return;
    case 21:
        if (MBi_IsSendEnabled() == 0) return;
        g->cb51c(25, 0);
        return;
    case 128:
        switch (msg->f4) {
        case 22:
            Fatal_Trap();
            break;
        case 23:
            break;
        }
        return;
    case 3:

    default:
        g->cb51c(0x100, msg);
        return;
    }
}

u32 MBi_GetBeaconPeriodDispersion(void) {
    u8 mac[6];
    u32 sum;
    int i;
    OS_GetMacAddress(mac);
    sum = i = 0;
    for (; i < 6; i++) sum += mac[i];
    return (sum + *HW_SYSWORK(u32, vblankCount)) * 7 % 20;
}

u32 MB_Init(u8 *buf, WChList *list, u32 a, u32 b, u32 dma) {
    WCtl *g;
    WWork *w;
    u32 e;
    volatile u32 zero32;
    volatile u16 zero;
    int i;
    u16 *dst;
    u16 *dst2;
    int j;
    if (data_0220001c != 0) {
        if (data_0220001c->f1316 != 0) return 2;
    }
    g = (WCtl *)(((uptr)buf + 31) & ~(uptr)31);
    w = (WWork *)(((uptr)g + 0x1e1f) & ~(uptr)31);
    if (b == 0x10000) b = WM_GetNextTgid();
    e = OS_DisableInterrupts();
    zero32 = 0;
    data_02200018 = g;
    data_0220001c = w;
    data_02200010 = dma;
    MIi_CpuClear32(zero32, g, 0x1e00);
    zero = 0;
    MIi_CpuClear16(zero, w, 0x1340);
    dst = g->f530;
    for (i = 0; i < list->n; i++) {
        *dst++ = ((u16 *)((u8 *)list + 2))[i];
    }
    dst2 = g->f538;
    for (j = 0; j < 16; j++) {
        if (*data_0213c21c == 0) break;
        *dst2++ = *data_0213c21c++;
    }
    MI_CpuCopy8(list, w->f1300, 22);
    if (list->n < 10) *(u16 *)((u8 *)w + 0x1302 + list->n * 2) = 0;
    g->f500 = 0x100;
    g->f502 = 8;
    g->f518 = 0;
    g->f51a = 0;
    g->f52c = 1;
    g->f504 = (u8 *)w + 0x400;
    g->f0e = 1;
    g->f12 = 0;
    g->f16 = 1;
    g->f14 = 0;
    g->f08 = a;
    g->f0c = b;
    g->f18 = MBi_GetBeaconPeriodDispersion() + 200;
    g->f10 = 15;
    g->f50c = 0;
    g->f50d = 0;
    w->f1316 = 1;
    w->f131c = 0;
    OS_RestoreInterrupts(e);
    return 0;
}

BOOL MBi_IsCommSizeValid(u32 a, u32 c, u32 d) {
    s32 v;
    if (a > 0x1fe || a < 228) return 0;
    if (c > 16 || c < 8) return 0;
    v = 0x14a + (a + 38) * 4 + d * ((c + 32) * 4 + 112);
    return v < 0x15e0;
}

BOOL MB_SetParentCommParam(u32 a, u32 b) {
    u32 e = OS_DisableInterrupts();
    if (data_02200018->f50d != 0) {
        OS_RestoreInterrupts(e);
        return 0;
    }
    if (MBi_IsCommSizeValid(a, 8, b) == 0) {
        OS_RestoreInterrupts(e);
        return 0;
    }
    data_02200018->f10 = b;
    data_02200018->f500 = a;
    data_02200018->f502 = 8;
    OS_RestoreInterrupts(e);
    return 1;
}

u32 MBi_StartCommon(void) {
    data_02200018->f528 = 0;
    data_02200018->f52a = 0;
    data_02200018->f526 = 0;
    data_02200018->f538[8] = 0;
    MBi_SetMaxScanTime(10);
    if (data_0220001c->f1320 == 0) {
        u32 r;
        do {
            r = WM_Initialize(data_02200014, data_02200018->cb508, data_02200010);
        } while (r == 4);
        if (r != 2) return 8;
        WM_SetIndCallback(data_02200018->cb508);
        data_02200018->f50d = 1;
        return 0;
    } else {
        WM_SetIndCallback(data_02200018->cb508);
        data_02200018->f50d = 1;
        MBi_OnInitializeDone();
        return 0;
    }
}

u32 MBi_StartParentCore(u32 a) {
    u32 e;
    u32 r;
    void (*cb)();
    volatile u16 zero1;
    volatile u16 zero2;
    int i;
    e = OS_DisableInterrupts();
    data_02200018->f32 = a;
    data_02200014 = (u8 *)(((uptr)data_0220001c + 0x7d1f) & ~(uptr)31);
    cb = data_0220001c->cb;
    zero1 = 0;
    MIi_CpuClear16(zero1, data_0220001c->ent, 0x69c0);
    MB_CommSetParentStateCallback((void *)cb);
    data_0220001c->f1318 = data_02200018->f500 - 6;
    MBi_SetChildMPMaxSize(data_02200018->f502);
    MBi_SetParentPieceBuffer((u8 *)data_0220001c + 0x1538);
    for (i = 0; i < 15; i++) {
        data_0220001c->state[i] = 0;
        data_0220001c->slot[i] = -1;
    }
    data_0220001c->f1524 = 0;
    zero2 = 0;
    MIi_CpuClear16(zero2, data_0220001c->peers, 0x5d40);
    MI_CpuFill8((u8 *)data_0220001c + 0x1754, 0, 30);
    data_02200018->f524 = 1;
    data_02200018->cb51c = MBi_CommParentCallback;
    data_02200018->cb508 = MBi_ParentCallback;
    data_02200018->f34 = data_02200018->f500;
    data_02200018->f518 = (data_02200018->f34 + 35) & ~31;
    data_02200018->f36 = data_02200018->f502;
    data_02200018->f51a = (((data_02200018->f36 + 14) * 15 + 41) & ~31) << 1;
    MB_InitSendGameInfoStatus();
    r = MBi_StartCommon();
    OS_RestoreInterrupts(e);
    *(u32 *)((u8 *)data_0220001c + 0x74c8) = PXI_IsCallbackReady(15, 1);
    return r;
}

u32 MB_StartParentFromIdle(u32 a) {
    data_0220001c->f1320 = 1;
    return MBi_StartParentCore(a);
}

BOOL MBi_CallReset(void) {
    u32 r = WM_Reset(data_02200018->cb508);
    MBi_CheckWmErrcode(1, r);
    if (r == 2) r = 0;
    return r;
}

BOOL MBi_OnReset(void) {
    return MBi_CallReset();
}

BOOL MBi_CommEnd(void) {
    BOOL r = 1;
    u32 e = OS_DisableInterrupts();
    if (data_02200018->f526 == 0) {
        data_02200018->f5e4 = 0;
        data_02200018->f526 = r;
        if (MBi_IsTaskAvailable() != 0) {
            MBi_EndTaskThread((void *)MBi_OnReset);
            r = 0;
        } else {
            r = MBi_CallReset();
        }
    }
    OS_RestoreInterrupts(e);
    return r;
}

void MB_End(void) {
    u32 e = OS_DisableInterrupts();
    if (data_0220001c->f1320 == 0) Fatal_Trap();
    MBi_CommEnd();
    OS_RestoreInterrupts(e);
}

extern u16 data_0213c224[10];
u16 data_0213c224[10] = {'m', 'u', 'l', 't', 'i', 'b', 'o', 'o', 't', 0};
u16 *data_0213c21c = data_0213c224;
u32 data_0213c220 = 1;
u16 data_0213c214 = 40;
u16 data_0213c20c = 0xffff;
u16 data_0213c218 = 0xffff;
u16 data_0213c210 = 40;

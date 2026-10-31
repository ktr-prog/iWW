#include "proto/autoload_2/unk_02122e24.h"
#include "proto/autoload_2/unk_02124480.h"
#include "proto/autoload_2/unk_02124830.h"
#include "proto/autoload_2/unk_02124c40.h"
#include "proto/autoload_2/unk_02125c94.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
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

WCtl *data_02200018;
WWork *data_0220001c;
u16 data_02200010;
u8 *data_02200014;
WScanParam data_02200020;
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

void MBi_SetMaxScanTime(u32 t) {
    data_02200020.f6 = t;
}

u32 MBi_SetMPData(WCb cb, void *a, u32 b, u32 c, u16 d) {
    u32 r = WM_SetMPDataToPortEx(cb, 0, a, b, d, 1, 3);
    MBi_CheckWmErrcode(15, r);
    return r;
}

u32 MBi_SendMP(void *a, u32 b0, u32 c0) {
    WCtl *g = data_02200018;
    u16 b = b0;
    u16 c = c0;
    u32 r;
    if (g->f528 == 0 || g->f526 == 1) return 1;
    switch (g->f524) {
    case 1:
        r = MBi_SetMPData(g->cb508, a, b, (u16)(g->f52c == 0 ? 1000 : 0), c);
        if (r == 2) data_02200018->f50c = 1;
        if (r == 2) r = 0;
        return r;
    case 2:
        r = MBi_SetMPData(MBi_ChildCallback, a, b, 0, c);
        if (r == 2) data_02200018->f50c = 1;
        if (r == 2) r = 0;
        return r;
    default:
        return 1;
    }
}

u32 MBi_GetGgid(void) {
    return data_02200018->f08;
}

u32 MBi_GetTgid(void) {
    return data_02200018->f0c;
}

u8 MBi_GetAttribute(void) {
    WCtl *g = data_02200018;
    return (u8)(((g->f0e != 0) ? 1 : 0) | ((g->f12 != 0) ? 2 : 0) | ((g->f14 != 0) ? 4 : 0) | ((g->f16 != 0) ? 8 : 0));
}

BOOL MBi_IsStarted(void) {
    return data_02200018->f50d == 1;
}

void MBi_CheckWmErrcode(u32 id, u32 res) {
    u16 buf[2];
    if (res == 2) return;
    if (res == 0) return;
    buf[0] = id;
    buf[1] = res;
    data_02200018->cb51c(0xff, buf);
}


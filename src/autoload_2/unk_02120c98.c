#include "nitro/wm.h"
#include "proto/autoload_2/unk_0211ef94.h"
#include "proto/autoload_2/unk_02120c98.h"
#include "proto/autoload_2/unk_02120ed4.h"
#include "proto/autoload_2/unk_02120fe8.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct {
    u16 hdr;
    u16 recv;
    u8 data[508];
} WMPacket;

typedef struct {
    WMPacket pkt[4];
    u16 slot[4];
    u16 f808;
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

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern u32 WMi_CheckIdle(void);
extern u32 WMi_CheckStateEx(int n, ...);
extern u32 WMi_SendCommand(u32 id, u16 paramNum, ...);
extern void WMi_SetCallbackTable(u32 idx, WMCallback cb);
extern u32 WM_SetPortCallback(u32 port, WMCallback cb, void *arg);
extern void DC_InvalidateRange(void *, u32);
extern void DC_StoreRange(void *, u32);
extern void MIi_CpuClear16(u32, void *, u32);
extern void MIi_CpuCopy16(void *, void *, u32);
extern void MIi_CpuClearFast(u32, void *, u32);
extern u32 WM_SetMPDataToPortEx(WMCallback cb, void *arg, void *sendData, u16 size, u16 destBitmap, u16 port, u16 prio);
extern void *WmGetSharedDataAddress(void *base, u32 x, void *y, u32 n);
extern void WmDataSharingSendDataSet(WMPool *ds, BOOL flag);
extern u8 data_021fff00[];
extern u32 MBi_CommChangeParentStateCallbackOnly(u32, u32, u16 *);

void WmDataSharingReceiveData(WMPool *ds, u32 n, u16 *buf);
u32 WM_EndDataSharing(WMPool *ds);
u32 WM_StartDataSharing(WMPool *ds, u32 port, u32 aidBitmap, u32 dataLength, BOOL doubleMode);

extern u32 WM_EndDataSharing(WMPool *ds);
extern u32 WM_EndKeySharing(WMPool *ds);
extern u32 WM_StartKeySharing(WMPool *ds, u32 port);
extern u32 WM_SetEntry(WMCallback cb, u32 arg);
extern u32 WM_MeasureChannel(WMCallback cb, u32 tableNumber, u32 camInterval, u32 frameInterval, u16 beaconInterval);
extern u32 WM_SetLifeTime(WMCallback cb, u32 ccaMode, u32 edThreshold, u32 channel, u16 measureTime);
extern u32 WM_SetBeaconIndication(WMCallback cb, u32 flag);
extern u32 WM_SetGameInfo(WMCallback cb, void *userGameInfo, u32 size, u32 ggid, u16 tgid, u8 attr);
extern u32 WM_SetWEPKeyEx(WMCallback cb, u32 wepmode, u32 wepkeyid, void *key);
extern u32 WM_SetWEPKey(WMCallback cb, u32 wepmode, void *key);
extern u32 WM_StartDataSharing(WMPool *ds, u32 port, u32 aidBitmap, u32 dataLength, BOOL doubleMode);
extern u32 WM_StepDataSharing(WMPool *ds, u16 *data, u16 *out);
extern u32 MBi_CommCallParentError(u32 a, u32 b);
extern BOOL IsChildAidValid(u32 x);
extern u32 MBi_calc_nextsendblock(u32 a, u32 b);
extern void MBi_calc_sendblock(u32 idx);
extern u32 MBi_CommParentSendData(void);
extern u32 MBi_CommParentSendBlock(void);

void WmDataSharingReceiveCallback_Child(WMMsg *msg) {
    WMStatus *st;
    WMPool *ds;
    u32 len;
    u32 bitmap;
    u16 *p;
    u32 aid;
    st = WMi_GetSystemWork()->status;
    ds = (WMPool *)msg->arg;
    if (ds == 0) return;
    if (msg->errcode == 0) {
        if (msg->f04 == 7) return;
        if (msg->f04 == 9) return;
        if (msg->f04 != 21) return;
        p = msg->f0c;
        bitmap = *p;
        len = msg->f10;
        DC_InvalidateRange(&st->f184, 2);
        aid = st->f184;
        if (len != ds->f814) {
            if (len > 512) len = 512;
        }
        if (len < 4) return;
        if ((bitmap & (1 << aid)) == 0) return;
        MIi_CpuCopy16(p, &ds->pkt[ds->f808], len);
        ds->slot[ds->f808] = msg->f1a >> 1;
        ds->f808 = (ds->f808 + 1) & 3;
    } else {
        ds->f81c = 5;
    }
}

void WmDataSharingReceiveData(WMPool *ds, u32 n, u16 *buf) {
    u16 mask = (u16)(1 << n);
    u32 idx;
    u32 x;
    void *addr;
    u32 irq;
    if ((ds->f80e & mask) == 0) return;
    idx = ds->f808;
    if ((mask & ds->pkt[idx].hdr) == 0) {
        if (ds->f818 != 1) return;
        idx = (u16)((idx + 1) & 3);
        if ((mask & ds->pkt[idx].hdr) == 0) return;
    }
    x = ds->f80e;
    addr = WmGetSharedDataAddress(ds, x, ds->pkt[idx].data, n);
    if (buf != 0) {
        MIi_CpuCopy16(buf, addr, ds->f810);
    } else {
        volatile u16 zero = 0;
        MIi_CpuClear16(zero, addr, ds->f810);
    }
    irq = OS_DisableInterrupts();
    ds->pkt[idx].hdr &= ~mask;
    ds->pkt[idx].recv |= mask;
    OS_RestoreInterrupts(irq);
}

typedef struct {
    u32 w0;
    u32 w4;
    u32 w8;
    u8 wc;
} Out2123294;

typedef struct {
    u8 cmd;
    u16 idx;
    u16 len;
} Msg2126e00;

typedef struct {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 state;
} Slot;

typedef struct {
    u8 _0[0x1d2c];
    u32 a1d2c[7];
    u16 f1d48;
    u16 f1d4a;
    u16 f1d4c;
    u8 _1d4e[4];
    u8 f1d52;
    u8 _1d53;
    u32 *f1d54;
    u32 *f1d58;
} Ent;

typedef struct {
    u8 _0[0x14e8];
    u32 state[15];
    u8 f1524;
    u8 cur;
    u8 _1526[0x262];
    u8 ent[16][0x5d4];
    u8 _74c8[0x818];
    u8 f7ce0[0x30];
} Ctx;

#define ENT(c, i) ((Ent *)((u8 *)(c) + (i) * 0x5d4))

extern Ctx *data_0220001c;
extern u32 MBi_CommParentSendMsg(u32, u32);
extern u32 MBi_CommParentSendDLFileInfo(u32);
extern u32 MBi_get_blockinfo(void *out, void *arr, u32 count, void *ent);
extern u32 MBi_MakeParentSendBuffer(void *msg, void *dst);
extern u32 MBi_ReadFromCache(void *, u32, u32, u32);
extern u32 MBi_IsTaskBusy(void *);
extern void MBi_SetTask(void *, void *, u32, u32);
extern u32 MBi_BlockHeaderEnd(u32, u32, void *);
extern u32 MBi_ReloadCache(void);
u32 MBi_CommParentSendBlock(void);
void MBi_calc_sendblock(u32 idx);


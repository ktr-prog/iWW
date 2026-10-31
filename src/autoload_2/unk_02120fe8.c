#include "nitro/wm.h"
#include "proto/autoload_2/unk_0211ef94.h"
#include "proto/autoload_2/unk_02120c98.h"
#include "proto/autoload_2/unk_02120ed4.h"
#include "proto/autoload_2/unk_02120fe8.h"
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
extern u32 MATH_CountPopulation(u32);
extern u32 WM_SetMPDataToPortEx(WMCallback cb, void *arg, void *sendData, u16 size, u16 destBitmap, u16 port, u16 prio);
extern u16 *WmGetSharedDataAddress(u8 *base, u32 x, u16 *y, u32 n);
extern void WmDataSharingSendDataSet(WMPool *ds, BOOL flag);
extern u8 data_021fff00[0x80];
extern u32 MBi_CommChangeParentStateCallbackOnly(u32, u32, u16 *);

void WmDataSharingReceiveData(WMPool *ds, u32 n, u16 *buf);
u32 WM_EndDataSharing(WMPool *ds);
u32 WM_StartDataSharing(WMPool *ds, u32 port, u32 aidBitmap, u32 dataLength, BOOL doubleMode);

extern void WmDataSharingReceiveData(WMPool *ds, u32 n, u16 *buf);
extern u32 MBi_CommParentSendBlock(void);

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

u32 MBi_CommParentSendData(void) {
    volatile u16 zero = 0;
    u16 m[5];
    u16 i;
    u32 r;
    MIi_CpuClear16(zero, m, 10);
    for (i = 1; i <= 15; i++) {
        switch (data_0220001c->state[i - 1]) {
        case 2:
            m[0] |= 1 << i;
            break;
        case 5:
            m[1] |= 1 << i;
            break;
        case 4:
            m[2] |= 1 << i;
            break;
        case 8:
            m[3] |= 1 << i;
            break;
        case 11:
            m[4] |= 1 << i;
            break;
        }
    }
    if (m[3] != 0) {
        r = MBi_CommParentSendMsg(5, m[3]);
    } else if (m[0] != 0) {
        r = MBi_CommParentSendMsg(1, m[0]);
    } else if (m[4] != 0) {
        r = MBi_CommParentSendMsg(6, m[4]);
    } else if (m[2] != 0) {
        r = MBi_CommParentSendMsg(2, m[2]);
    } else if (m[1] != 0) {
        r = MBi_CommParentSendDLFileInfo(m[1]);
    } else {
        r = MBi_CommParentSendBlock();
    }
    if (r == 21) r = MBi_CommParentSendMsg(0, 0xffff);
    return r;
}

void MBi_calc_sendblock(u32 idx) {
    if (ENT(data_0220001c, idx)->f1d52 == 0) return;
    if (ENT(data_0220001c, idx)->f1d4c == 0) return;
    {
        u16 a = ENT(data_0220001c, idx)->f1d48;
        u16 b = ENT(data_0220001c, idx)->f1d4a;
        if (b <= a) {
            if (a <= b + 2) {
                ENT(data_0220001c, idx)->f1d48 = a + 1;
                return;
            }
        }
        ENT(data_0220001c, idx)->f1d48 = b;
    }
}

u32 MBi_calc_nextsendblock(u32 a, u32 b) {
    if (b <= a) b = a;
    return b;
}

BOOL IsChildAidValid(u32 x) {
    if (x >= 1 && x <= 15) return 1;
    return 0;
}

u32 MBi_CommCallParentError(u32 a, u32 b) {
    u16 v = (u16)b;
    return MBi_CommChangeParentStateCallbackOnly(a, 13, &v);
}

u32 WM_SetWEPKey(WMCallback cb, u32 wepmode, void *key) {
    u32 r = WMi_CheckIdle();
    if (r != 0) return r;
    if (wepmode > 3) return 6;
    if (wepmode != 0) {
        if (key == 0) return 6;
        DC_StoreRange(key, 0x50);
    }
    WMi_SetCallbackTable(20, cb);
    r = WMi_SendCommand(20, 2, wepmode, WM_ARM7_ADDR(key));
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetWEPKeyEx(WMCallback cb, u32 wepmode, u32 wepkeyid, void *key) {
    u32 r = WMi_CheckIdle();
    if (r != 0) return r;
    if (wepmode > 3) return 6;
    if (wepmode != 0) {
        if (key == 0) return 6;
        DC_StoreRange(key, 0x50);
    }
    WMi_SetCallbackTable(39, cb);
    r = WMi_SendCommand(39, 3, wepmode, WM_ARM7_ADDR(key), wepkeyid);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetGameInfo(WMCallback cb, void *userGameInfo, u32 size, u32 ggid, u16 tgid, u8 attr) {
    u32 r = WMi_CheckStateEx(2, 7, 9);
    if (r != 0) return r;
    if (userGameInfo == 0) return 6;
    if (size > 0x70) return 6;
    MIi_CpuCopy16(userGameInfo, data_021fff00, size);
    DC_StoreRange(data_021fff00, size);
    WMi_SetCallbackTable(24, cb);
    r = WMi_SendCommand(24, 5, WM_ARM7_ADDR(data_021fff00), size, ggid, tgid, attr);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetBeaconIndication(WMCallback cb, u32 flag) {
    u32 r = WMi_CheckIdle();
    if (r != 0) return r;
    if (flag != 0 && flag != 1) return 6;
    WMi_SetCallbackTable(25, cb);
    r = WMi_SendCommand(25, 1, flag);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetLifeTime(WMCallback cb, u32 ccaMode, u32 edThreshold, u32 channel, u16 measureTime) {
    u32 r = WMi_CheckIdle();
    if (r != 0) return r;
    WMi_SetCallbackTable(29, cb);
    r = WMi_SendCommand(29, 4, ccaMode, edThreshold, channel, measureTime);
    if (r == 0) r = 2;
    return r;
}

u32 WM_MeasureChannel(WMCallback cb, u32 tableNumber, u32 camInterval, u32 frameInterval, u16 beaconInterval) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(1, 2);
    u16 *req;
    if (r != 0) return r;
    WMi_SetCallbackTable(30, cb);
    req = (u16 *)w->req;
    req[0] = 30;
    req[1] = tableNumber;
    req[2] = camInterval;
    req[3] = frameInterval;
    req[4] = beaconInterval;
    r = WMi_SendCommand(30, 0);
    if (r == 0) r = 2;
    return r;
}

u32 WM_SetEntry(WMCallback cb, u32 arg) {
    u32 r = WMi_CheckStateEx(2, 7, 9);
    if (r != 0) return r;
    WMi_SetCallbackTable(33, cb);
    r = WMi_SendCommand(33, 1, arg);
    if (r == 0) r = 2;
    return r;
}

u32 WM_StartKeySharing(WMPool *ds, u32 port) {
    return WM_StartDataSharing(ds, port, 0xffff, 2, 1);
}

u32 WM_EndKeySharing(WMPool *ds) {
    return WM_EndDataSharing(ds);
}

u32 WM_StartDataSharing(WMPool *ds, u32 port, u32 aidBitmap, u32 dataLength, BOOL doubleMode) {
    u32 ack = 1;
    u32 aid;
    WMStatus *st;
    u16 mask;
    u32 r;
    st = WMi_GetSystemWork()->status;
    r = WMi_CheckStateEx(2, 9, 10);
    if (r != 0) return r;
    DC_InvalidateRange(&st->f0c, 4);
    if (st->f0c == 0) return 3;
    if (ds == 0) return 6;
    if (port >= 16) return 6;
    if (aidBitmap == 0) return 6;
    DC_InvalidateRange(&st->f184, 2);
    aid = st->f184;
    if (aid == 0) {
        DC_InvalidateRange(&st->f86, 2);
        ack = st->f86;
    }
    {
        volatile u32 zero = 0;
        MIi_CpuClearFast(zero, ds, 0x820);
    }
    ds->f808 = 0;
    ds->f80a = 0;
    ds->f80c = 0;
    ds->f810 = dataLength;
    ds->f816 = port;
    ds->f80e = 0;
    ds->f818 = (doubleMode != 0);
    mask = aidBitmap | (1 << aid);
    ds->f80e = mask;
    r = MATH_CountPopulation(mask);
    ds->f812 = r;
    ds->f814 = dataLength * r;
    if (ds->f814 > 0x1fc) {
        ds->f80e = 0;
        return 6;
    }
    ds->f814 = ds->f814 + 4;
    ds->f81c = 1;
    if (aid == 0) {
        int i;
        WMPacket *p;
        for (i = 0; i < 4; i++) {
            ds->pkt[i].hdr = ds->f80e & (ack | 1);
        }
        WM_SetPortCallback(port, WmDataSharingReceiveCallback_Parent, ds);
        p = ds->pkt;
        for (i = 0; i < (ds->f818 == 1 ? 2 : 1); i++) {
            u32 ret;
            ds->f808 = (ds->f808 + 1) & 3;
            ret = WM_SetMPDataToPortEx(WmDataSharingSetDataCallback, ds, p, ds->f814, ds->f80e & ack, ds->f816, 1);
            if (ret == 7) {
                ds->slot[i] = 0xffff;
                ds->f80a = (ds->f80a + 1) & 3;
            } else if (ret != 0) {
                if (ret != 2) {
                    ds->f81c = 5;
                    return 1;
                }
            }
            p++;
        }
    } else {
        ds->f80a = 3;
        WM_SetPortCallback(port, WmDataSharingReceiveCallback_Child, ds);
    }
    return 0;
}

u32 WM_EndDataSharing(WMPool *ds) {
    WMArm9Buf *w = WMi_GetSystemWork();
    u32 r = WMi_CheckStateEx(2, 9, 10);
    if (r != 0) return r;
    if (ds == 0) return 6;
    if (ds->f80e == 0 || (w->portCb[ds->f816] != WmDataSharingReceiveCallback_Parent && w->portCb[ds->f816] != WmDataSharingReceiveCallback_Child)) {
        return 3;
    }
    WM_SetPortCallback(ds->f816, 0, 0);
    ds->f80e = 0;
    ds->f81c = 0;
    return 0;
}

u32 WM_StepDataSharing(WMPool *ds, u16 *data, u16 *out) {
    u32 flag2;
    u32 ack;
    u32 ready;
    u32 aid;
    WMStatus *st;
    u32 r;
    u32 rr;
    st = WMi_GetSystemWork()->status;
    r = WMi_CheckStateEx(2, 9, 10);
    if (r != 0) return r;
    DC_InvalidateRange(&st->f0c, 4);
    if (st->f0c == 0) return 3;
    if (ds == 0) return 6;
    if (data == 0) return 6;
    if (out == 0) return 6;
    DC_InvalidateRange(&st->f184, 2);
    aid = st->f184;
    if (aid == 0) {
        DC_InvalidateRange(&st->f86, 2);
        ack = st->f86;
    }
    if (ds->f81c == 5) return 1;
    if (ds->f81c != 1 && ds->f81c != 4) return 3;
    r = 5;
    if (aid == 0) {
        ready = 0;
        flag2 = 0;
        if (ds->f81c == 4) {
            u32 idx;
            ds->f81c = 1;
            idx = (u16)((ds->f808 + 3) & 3);
            rr = WM_SetMPDataToPortEx(WmDataSharingSetDataCallback, ds, &ds->pkt[idx], ds->f814, ds->f80e & ack, ds->f816, 1);
            if (rr == 7) {
                ds->slot[idx] = 0xffff;
                ds->f80a = (ds->f80a + 1) & 3;
            } else if (rr != 0) {
                if (rr != 2) {
                    ds->f81c = 5;
                    return 1;
                }
            }
        }
        if (ds->f80c != ds->f80a) {
            ds->pkt[ds->f80c].hdr |= 1;
            MIi_CpuCopy16(&ds->pkt[ds->f80c], out, 512);
            ready = 1;
            r = 0;
            ds->f81a = ds->slot[ds->f80c];
            ds->f80c = (ds->f80c + 1) & 3;
            if (ds->f818 == 0 && ack != 0 && ds->pkt[ds->f808].hdr == 1) {
                flag2 = ready;
            } else {
                flag2 = 0;
            }
        }
        WmDataSharingSendDataSet(ds, 0);
        if (ready != 0) {
            WmDataSharingReceiveData(ds, 0, data);
            if (ds->f818 == 0) WmDataSharingSendDataSet(ds, flag2);
        }
    } else {
        ready = 0;
        if (ds->f81c == 4) {
            ds->f81c = 1;
            ready = 1;
        } else if (ds->f80c != ds->f808) {
            u32 idx = ds->f80c;
            if ((ds->pkt[idx].hdr & 1) == 0) {
                ds->pkt[idx].hdr |= 1;
            } else {
                MIi_CpuCopy16(&ds->pkt[idx], out, 512);
                ds->f81a = ds->slot[ds->f80c];
                ds->f80c = (ds->f80c + 1) & 3;
                ready = 1;
                r = 0;
            }
        }
        if (ready != 0) {
            u8 *p = &ds->pkt[ds->f80a].data[28];
            MIi_CpuCopy16(data, p, ds->f810);
            rr = WM_SetMPDataToPortEx(WmDataSharingSetDataCallback, ds, p, ds->f810, ds->f80e, ds->f816, 1);
            ds->f80a = (ds->f80a + 1) & 3;
            if (rr != 2) {
                if (rr != 0) {
                    ds->f81c = 5;
                    r = 1;
                }
            }
        }
    }
    return r;
}

void WmDataSharingSetDataCallback(WMMsg *msg) {
    WMArm9Buf *w = WMi_GetSystemWork();
    WMStatus *st = w->status;
    WMPool *ds;
    u32 err, aid;
    ds = w->portArg[msg->f0a];
    if (w->portCb[msg->f0a] != WmDataSharingReceiveCallback_Parent && w->portCb[msg->f0a] != WmDataSharingReceiveCallback_Child) return;
    if (ds == 0) return;
    if ((void *)ds != ((WMPortSendCallback *)msg)->arg) return;
    DC_InvalidateRange(&st->f184, 2);
    err = msg->errcode;
    aid = st->f184;
    if (err == 0) {
        if (aid != 0) return;
        ds->slot[ds->f80a] = msg->f1a >> 1;
        ds->f80a = (ds->f80a + 1) & 3;
        return;
    }
    if (err == 10) {
        if (aid != 0) ds->f80a = (ds->f80a + 3) & 3;
        ds->f81c = 4;
        return;
    }
    ds->f81c = 5;
}

u8 data_021fff00[0x80];

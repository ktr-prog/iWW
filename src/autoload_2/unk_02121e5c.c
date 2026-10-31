#include "nitro/wm.h"
#include "proto/autoload_2/unk_0211ef94.h"
#include "proto/autoload_2/unk_02120c98.h"
#include "proto/autoload_2/unk_02120ed4.h"
#include "proto/autoload_2/unk_02120fe8.h"
#include "proto/autoload_2/unk_02121e5c.h"
#include "proto/autoload_2/unk_0212703c.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "host_ptr32.h"
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

typedef struct {
    u32 f0;
    u8 _4[44];
    Slot slot[4];
} SlotBuf;

u32 MBi_CommParentSendBlock(void) {
    Msg2126e00 msg;
    Out2123294 out;
    u8 i;
    if (data_0220001c->f1524 == 0) return 21;
    for (i = 0; i < 16; i++) {
        data_0220001c->cur = (u8)((data_0220001c->cur + 1) % 16);
        if (ENT(data_0220001c, data_0220001c->cur)->f1d52 != 0 && ENT(data_0220001c, data_0220001c->cur)->f1d4c != 0) break;
    }
    if (i == 16) return 21;
    MBi_calc_sendblock(data_0220001c->cur);
    if (MBi_get_blockinfo(&out, (u8 *)data_0220001c + 0x1d2c + data_0220001c->cur * 0x5d4, ENT(data_0220001c, data_0220001c->cur)->f1d48,
                      (u8 *)data_0220001c + 0x1788 + data_0220001c->cur * 0x5d4) == 0) {
        return 21;
    }
    msg.cmd = 4;
    msg.idx = data_0220001c->cur;
    msg.len = ENT(data_0220001c, data_0220001c->cur)->f1d48;
    {
        u32 r = MBi_MakeParentSendBuffer(&msg, data_0220001c);
        u32 addr = out.w8 - ENT(data_0220001c, data_0220001c->cur)->a1d2c[out.wc] + ENT(data_0220001c, data_0220001c->cur)->f1d58[out.wc];
        SlotBuf *buf = (SlotBuf *)ENT(data_0220001c, data_0220001c->cur)->f1d54;
        if (MBi_ReadFromCache(buf, addr, r, out.w4) == 0) {
            void *job = (u8 *)data_0220001c + 0x7ce0;
            if (MBi_IsTaskBusy(job) == 0 && buf->f0 != 0) {
                Slot *slot = buf->slot;
                Slot *best = 0;
                int j;
                for (j = 0; j < 4; j++) {
                    if (slot[j].state == 2) {
                        if (best == 0 || best->f0 > slot[j].f0) {
                            best = &slot[j];
                        }
                    }
                }
                if (best == 0) Fatal_Trap();
                buf->f0 = 0;
                best->state = 1;
                best->f0 = addr & ~31;
                ((u32 *)job)[4] = HostPtr32_Of(best);
                ((u32 *)job)[5] = HostPtr32_Of(buf);
                MBi_SetTask(job, MBi_ReloadCache, 0, 4);
            }
            return 21;
        } else {
            return MBi_BlockHeaderEnd(out.w4 + 6, ENT(data_0220001c, data_0220001c->cur)->f1d4c, data_0220001c);
        }
    }
    return 21;
}

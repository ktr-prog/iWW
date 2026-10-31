#include "nitro/pxi_ptr.h"
#include "uptr.h"
#include "host_mem.h"
#include "sys/CardCommon.h"
#include "nitro/wm.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

#include "ds_stdarg.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211d20c.h"
#include "proto/autoload_2/unk_0211e558.h"
#include "proto/autoload_2/unk_0211ea4c.h"
#include "proto/autoload_2/unk_0211eb00.h"
#include "proto/autoload_2/unk_0211ef94.h"
#include "proto/autoload_2/unk_0211f488.h"
#include "proto/main/unk_0206d49c.h"

typedef struct CardCommon CardCommon;

extern CardCommon data_021fec00;
extern u32 data_021ff240[];
extern int (*data_021ff464)(void);
extern u32 data_021ff460;
extern WMArm9Buf *data_021ff46c;
extern u16 data_021ff468;
extern u8 data_021ff470[];
extern u8 data_021ff490[];
extern WMMsg data_021ff4b8;
extern u8 data_021ff4cc[0x10];
extern u8 data_021ff4dc[0x24];
extern u8 data_021ff500[0xa00];
extern u32 data_0213c1fc;

extern void CPi_RestoreContext(void);
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void OS_SetIrqFunction(u32, void (*)(void));
extern void OS_ResetRequestIrqMask(u32);
extern void OS_EnableIrqMask(u32);
extern void OS_DisableIrqMask(u32);
extern void OS_SpinWait(u32);
extern void DC_InvalidateRange(void *, u32);
extern void DC_StoreRange(void *, u32);
extern void DC_FlushRange(void *, u32);
extern void IC_InvalidateRange(void *, u32);
extern void DC_WaitWriteBufferEmpty(void);
extern void *OS_GetDTCMAddress(void);
extern void MI_StopDma(u32);
extern void MIi_CardDmaCopy32(u32, uptr, uptr, u32);
extern void MI_CpuCopy8(void *, void *, u32);
extern void OS_WakeupThreadDirect(void *);
extern int PXI_IsCallbackReady(u32, u32);
extern int PXI_SendWordByFifo(u32, u32, u32);
extern void PXI_SetFifoRecvCallback(u32, void *);
extern void WaitByLoop(u32);
extern void PM_ForceToPowerOff(void);
extern int OS_ReceiveMessage(void *, void *, u32);
extern void OS_JamMessage(void *, void *, u32);
extern void OS_SendMessage(void *, void *, u32);
extern void OS_InitMessageQueue(void *, void *, u32);
extern void MI_DmaCopy32(u32, void *, void *, u32);
extern void MI_DmaFill32(u32, void *, u32, u32);
extern void MIi_CpuCopy16(void *, void *, u32);
extern void MIi_CpuClear16(u32, void *, u32);
extern void OS_GetMacAddress(u8 *);
extern int RTC_GetTime(u32 *);
extern u32 WM_SetPortCallback(u16 port, WMCallback cb, void *arg);

BOOL func_0211f7e4(void);
u32 WM_GetLinkLevel(void);
u32 WM_GetDispersionBeaconPeriod(void);
u32 WM_GetDispersionScanPeriod(void);
u32 WM_GetNextTgid(void);
u32 WM_Init(void *buf, u16 dmaNo);
u32 WmInitCore(void *buf, u16 dmaNo, u32 size);
u32 WM_Finish(void);
void WMi_SetCallbackTable(u32 idx, void (*cb)(WMMsg *));
u32 WMi_SendCommand(u32 id, u16 paramNum, ...);
u32 WMi_CheckInitialized(void);
u32 WMi_CheckIdle(void);
u32 WMi_CheckStateEx(int n, ...);
void WmReceiveFifo(u32 tag, u32 data, BOOL err);
WMStatus *WMi_GetStatusAddress(void);
void CARDi_PulledOutCallback(u32 tag, u32 data, BOOL err);
void CARDi_SendtoPxi(u32 data, u32 n);
void CARDi_OnFifoRecv(u32 tag, u32 data, BOOL err);
BOOL CARDi_Request(CardCommon *c, u32 arg, int retry);
BOOL CARDi_ReadFromCache(u8 *cache);
void CARDi_SetRomOp(u32 hi, u32 lo);
BOOL CARDi_TryReadCardDma(CardCommon *req);

void WmReceiveFifo(u32 tag, u32 data, BOOL err) {
    WMMsg *m;
    if (err != 0) return;
    m = (WMMsg *)HostPxi_TakeArm7Pointer(tag);
    DC_InvalidateRange(data_021ff46c->f10, 0x100);
    if (data_021ff46c->f16 == 0) DC_InvalidateRange(data_021ff46c->status, 0x800);
    if (m != (WMMsg *)data_021ff46c->f10) DC_InvalidateRange(m, 0x100);
    if (m->id >= 42) {
        if (m->id == 0x80) {
            if (m->errcode == 19) Fatal_Trap();
            if (data_021ff46c->cbC0 != 0) data_021ff46c->cbC0(m);
        } else if (m->id == 0x82) {
            if (data_021ff46c->portCb[m->f06] != 0) {
                m->arg = data_021ff46c->portArg[m->f06];
                DC_InvalidateRange(WMi_Arm7Ptr(m->f08), data_021ff46c->status->f46);
                data_021ff46c->portCb[m->f06](m);
            }
        } else if (m->id == 0x81) {
            m->id = 15;
            if (m->arg != 0) ((void (*)(WMMsg *))m->arg)(m);
        }
    } else {
        void (*cb)(WMMsg *);
        u32 r8;
        u32 r7;
        u32 r6;
        u8 *r5;
        u8 *r4;
        if (m->id == 14 && (u16)(m->f04 + 0xfff5) <= 1 && m->errcode == 0)
            DC_InvalidateRange(WMi_Arm7Ptr(m->f08), data_021ff46c->status->f46);
        if (m->id == 2 && m->errcode == 0) {
            cb = data_021ff46c->cb18[m->id];
            WM_Finish();
            if (cb != 0) cb(m);
            return;
        }
        cb = data_021ff46c->cb18[m->id];
        if (cb != 0) {
            cb(m);
            if (data_021ff468 == 0) return;
        }
        if (m->id == 8 || m->id == 12) {
            if (m->id == 8) {
                WMStartParentCallback *p = (WMStartParentCallback *)m;
                r5 = p->macAddress;
                r4 = (u8 *)p + 0x14;
                r8 = p->state;
                r7 = p->aid;
                r6 = 0;
            } else if (m->id == 12) {
                WMStartConnectCallback *c = (WMStartConnectCallback *)m;
                r7 = 0;
                r8 = c->state;
                r6 = c->aid;
                r4 = NULL;
                r5 = c->macAddress;
            }
            if (r8 == 7 || r8 == 9) {
                u16 i;
                data_021ff4b8.id = 0x82;
                data_021ff4b8.errcode = 0;
                data_021ff4b8.f04 = r8;
                data_021ff4b8.f08 = 0;
                data_021ff4b8.f0c = 0;
                data_021ff4b8.f10 = 0;
                data_021ff4b8.f12 = r7;
                data_021ff4b8.f20h = r6;
                data_021ff4b8.f1a = 0xffff;
                MI_CpuCopy8(r5, ((WMPortRecvCallback *)&data_021ff4b8)->macAddress, 6);
                if (r4 != 0) {
                    MIi_CpuCopy16(r4, data_021ff4dc, 0x18);
                } else {
                    volatile u16 z = 0;
                    MIi_CpuClear16(z, data_021ff4dc, 0x18);
                }
                for (i = 0; i < 16; i++) {
                    data_021ff4b8.f06 = i;
                    if (data_021ff46c->portCb[i] != 0) {
                        data_021ff4b8.arg = data_021ff46c->portArg[i];
                        data_021ff46c->portCb[i](&data_021ff4b8);
                    }
                }
            }
        }
    }
    DC_InvalidateRange(data_021ff46c->f10, 0x100);
    WmClearFifoRecvFlag();
    if (m != (WMMsg *)data_021ff46c->f10) {
        m->id |= 0x8000;
        DC_StoreRange(m, 0x100);
    }
}

void WmClearFifoRecvFlag(void) {
    u16 *p = HW_SYSWORK(u16, wmCallbackControl);
    if (*p & 1) *p &= ~1;
}

WMStatus *WMi_GetStatusAddress(void) {
    return WMi_CheckInitialized() != 0 ? NULL : data_021ff46c->status;
}

u8 data_021ff4cc[0x10];
u8 data_021ff4dc[0x24];
u8 data_021ff500[0xa00];

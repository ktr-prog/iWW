#include "nitro/pxi_ptr.h"
#include "sys/OSMessageQueue.h"
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
extern void *data_021ff490[10];
extern WMMsg data_021ff4b8;
extern u8 data_021ff4cc[];
extern u8 data_021ff4dc[];
extern u8 data_021ff500[];
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
extern void WM_SetPortCallback(u16, u32, u32);

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

u32 WM_GetNextTgid(void) {
    if (data_0213c1fc == 0x10000) {
        u32 t[3];
        RTC_Init();
        if (RTC_GetTime(t) == 0) {
            data_0213c1fc = (u16)(t[2] + (t[1] << 8));
        }
    }
    data_0213c1fc = (u16)(data_0213c1fc + 1);
    return (u16)data_0213c1fc;
}

u32 WM_Init(void *buf, u16 dmaNo) {
    u32 r = WmInitCore(buf, dmaNo, 0xf00);
    if (r == 0) data_021ff46c->f16 = 0;
    return r;
}

u32 WmInitCore(void *buf, u16 dmaNo, u32 size) {
    WMArm9Buf *w;
    int i;
    int j;
    u8 *p;
    if (data_021ff468 != 0) return 3;
    data_021ff468 = 1;
    if (buf == 0) {
        data_021ff468 = 0;
        return 6;
    }
    if (dmaNo > 3) {
        data_021ff468 = 0;
        return 6;
    }
    if (((uptr)buf & 31) != 0) {
        data_021ff468 = 0;
        return 6;
    }
    PXI_Init();
    if (PXI_IsCallbackReady(10, 1) == 0) {
        data_021ff468 = 0;
        return 4;
    }
    DC_InvalidateRange(buf, size);
    MI_DmaFill32(dmaNo, buf, 0, size);
    data_021ff46c = (WMArm9Buf *)buf;
    ((WMArm9Buf *)buf)->w0 = (u8 *)buf + 0x200;
    data_021ff46c->status = (WMStatus *)((u8 *)data_021ff46c->w0 + 0x300);
    data_021ff46c->req = (u8 *)data_021ff46c->status + 0x800;
    data_021ff46c->f10 = data_021ff46c->req + 0x100;
    WmClearFifoRecvFlag();
    data_021ff46c->dmaNo = dmaNo;
    for (i = 0; i < 16; i++) WM_SetPortCallback(i, 0, 0);
    OS_InitMessageQueue(data_021ff470, data_021ff490, 10);
    p = data_021ff500;
    for (j = 0; j < 10; j++) {
        *(u16 *)p = 0x8000;
        DC_StoreRange(p, 2);
        OS_SendMessage(data_021ff470, p, 1);
        p += 0x100;
    }
    PXI_SetFifoRecvCallback(10, WmReceiveFifo);
    return 0;
}

u32 WM_Finish(void) {
    u32 r;
    if (WMi_CheckInitialized() != 0) return 3;
    r = WMi_CheckStateEx(1, 0);
    if (r != 0) return r;
    WmClearFifoRecvFlag();
    PXI_SetFifoRecvCallback(10, 0);
    data_021ff46c = 0;
    data_021ff468 = 0;
    return 0;
}

void WMi_SetCallbackTable(u32 idx, void (*cb)(WMMsg *)) {
    data_021ff46c->cb18[idx] = cb;
}

u32 WMi_SendCommand(u32 id, u16 paramNum, ...) {
    WMMsg *msg;
    va_list va;
    int r;
    int i;
    if (OS_ReceiveMessage(data_021ff470, &msg, 0) == 0) return 8;
    DC_InvalidateRange(msg, 2);
    if ((msg->id & 0x8000) == 0) {
        OS_JamMessage(data_021ff470, msg, 1);
        return 8;
    }
    if (paramNum == 0) {
        DC_StoreRange(data_021ff46c->req, 0x100);
        DC_InvalidateRange(msg, 0x100);
        MI_DmaCopy32(data_021ff46c->dmaNo, data_021ff46c->req, msg, 0x100);
    }
    msg->id = id;
    va_start(va, paramNum);
    for (i = 0; i < paramNum; i++) {
        ((struct { u16 id; u16 pad; u32 p[1]; } *)msg)->p[i] = va_arg(va, u32);
    }
    DC_StoreRange(msg, 0x100);
    r = PXI_SendWordByFifo(10, PXI_PointerWord(10, msg), 0);
    OS_SendMessage(data_021ff470, msg, 1);
    return r < 0 ? 8 : 2;
}

WMArm9Buf *WMi_GetSystemWork(void) {
    return data_021ff46c;
}

u32 WMi_CheckInitialized(void) {
    return data_021ff468 != 0 ? 0 : 3;
}

u32 WMi_CheckIdle(void) {
    u32 r = WMi_CheckInitialized();
    if (r != 0) return r;
    DC_InvalidateRange(data_021ff46c->status, 2);
    return data_021ff46c->status->state <= 1 ? 3 : 0;
}

u32 data_0213c1fc = 0x10000;

u16 data_021ff468;
WMArm9Buf *data_021ff46c;
_Alignas(8) u8 data_021ff470[sizeof(OSMessageQueue)];
void *data_021ff490[10];

#include "sys/CardCommon.h"
#include "host_mem.h"
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
#include "proto/autoload_2/unk_0211e3fc.h"
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
WMMsg data_021ff4b8;
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


static inline BOOL CARDi_IsInTcm(uptr buf, u32 len) {
const uptr i = (uptr)HW_ITCM_BLOCK;
    const uptr d = (uptr)OS_GetDTCMAddress();
return ((i < buf + len) && (i + 0x8000 > buf)) || ((d < buf + len) && (d + 0x4000 > buf));
}
BOOL CARDi_TryReadCardDma(CardCommon *req) {
    CardCommon *const c = &data_021fec00;
    uptr dst = c->dst;
    u32 len = c->len;
    BOOL use = 0;
    BOOL aligned = 0;
    BOOL ok = 0;
if ((dst & 3) == 0 && c->dma <= 3) { if (!CARDi_IsInTcm(dst, len)) ok = 1; }
    if (ok) {
        if (((c->src | len) & 0x1ff) == 0) aligned = 1;
    }
    if (aligned) {
        if (len != 0) use = 1;
    }
    req->arg = (*HW_SYSWORK_AT(u32, romHeader, 0x60) & ~0x7000000) | 0xa1000000;
    if (use) {
        u32 irq = OS_DisableInterrupts();
        IC_InvalidateRange((void *)dst, len);
        if ((dst & 31) != 0) {
            dst -= dst & 31;
            DC_StoreRange((void *)dst, 32);
            DC_StoreRange((void *)(dst + len), 32);
            len += 32;
        }
        DC_InvalidateRange((void *)dst, len);
        DC_WaitWriteBufferEmpty();
        OS_SetIrqFunction(0x80000, (void (*)(void))CARDi_OnReadCard);
        OS_ResetRequestIrqMask(0x80000);
        OS_EnableIrqMask(0x80000);
        OS_RestoreInterrupts(irq);
        CARDi_SetCardDma();
    }
    return use;
}

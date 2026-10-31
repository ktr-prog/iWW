#include "nitro/pxi_ptr.h"
#include "host_mem.h"
#include "sys/CardCommon.h"
#include "nitro/wm.h"
#include "nitro/io_access.h"
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
extern u32 OS_GetDTCMAddress(void);
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
BOOL CARDi_TryReadCardDma(CardCommon *req);void CARD_TerminateForPulledOut(void) {
    if ((*HW_SYSWORK(u16, buttonXY) & 0x8000) >> 15) PM_ForceToPowerOff();
    CARDi_SendtoPxi(1, 1);
    Fatal_Trap();
}

void CARDi_SendtoPxi(u32 data, u32 n) {
    if (PXI_SendWordByFifo(14, data, 0) == 0) return;
    do {
        WaitByLoop(n);
    } while (PXI_SendWordByFifo(14, data, 0) != 0);
}

void CARDi_OnFifoRecv(u32 tag, u32 data, BOOL err) {
    if (tag != 11) return;
    if (err == 0) return;
    {
        CardCommon *const c = &data_021fec00;
        c->flag &= ~0x20;
        OS_WakeupThreadDirect(c->waiter);
    }
}

void CARDi_TaskThread(void) {
    CardCommon *const c = &data_021fec00;
    u32 irq;
    for (;;) {
        irq = OS_DisableInterrupts();
        while ((c->flag & 8) == 0) {
            c->waiter = &c->thread;
            OS_SleepThread(0);
        }
        OS_RestoreInterrupts(irq);
        c->task(c);
    }
}

BOOL CARDi_Request(CardCommon *c, u32 arg, int retry) {
    u32 irq;
    if ((*(volatile u32 *)&c->flag & 2) == 0) {
        c->flag |= 2;
        if (PXI_IsCallbackReady(11, 1) == 0) {
            do {
                OS_SpinWait(100);
            } while (PXI_IsCallbackReady(11, 1) == 0);
        }
        CARDi_Request(c, 0, 1);
    }
    DC_FlushRange(c->result, 64);
    DC_WaitWriteBufferEmpty();
    do {
        c->arg = arg;
        c->flag |= 0x20;
        while (PXI_SendWordByFifo(11, arg, 1) < 0) {}
        if (arg == 0) {
            u32 r = PXI_PointerWord(11, c->result);
            while (PXI_SendWordByFifo(11, r, 1) < 0) {}
        }
        irq = OS_DisableInterrupts();
        if ((c->flag & 0x20) != 0) {
            do {
                OS_SleepThread(0);
            } while ((c->flag & 0x20) != 0);
        }
        OS_RestoreInterrupts(irq);
    } while (*c->result == 4 && --retry > 0);
    return *c->result == 0;
}

typedef struct {
    void (*fn)(void *);
    u32 f4;
    u32 page;
    u32 fc;
    u32 f10, f14, f18, f1c;
    u32 buf[128];
} RomCache;

BOOL CARDi_ReadFromCache(u8 *cache) {
    CardCommon *c = &data_021fec00;
    RomCache *rc = (RomCache *)cache;
    u32 base = c->src & -512;
    if (base == rc->page) {
        u32 off = c->src - base;
        u32 n = 512 - off;
        if (n > c->len) n = c->len;
        MI_CpuCopy8((u8 *)rc->buf + off, (void *)c->dst, n);
        c->src += n;
        c->dst += n;
        c->len -= n;
    }
    return c->len != 0;
}

void CARDi_SetRomOp(u32 hi, u32 lo) {
    while (IO_R((volatile u32 *)0x040001a4) & 0x80000000) {}
    IO_W((volatile u8 *)0x040001a1, 0xc0);
    IO_W((volatile u8 *)0x040001a8, hi >> 24);
    IO_W((volatile u8 *)0x040001a9, hi >> 16);
    IO_W((volatile u8 *)0x040001aa, hi >> 8);
    IO_W((volatile u8 *)0x040001ab, hi);
    IO_W((volatile u8 *)0x040001ac, lo >> 24);
    IO_W((volatile u8 *)0x040001ad, lo >> 16);
    IO_W((volatile u8 *)0x040001ae, lo >> 8);
    IO_W((volatile u8 *)0x040001af, lo);
}

void CARDi_SetCardDma(void) {
    CardCommon *const c = &data_021fec00;
    u32 dma = c->dma;
    uptr dst = c->dst;
    MIi_CardDmaCopy32(dma, 0x04100010, dst, 512);
    CARDi_SetRomOp(0xb7000000 | (c->src >> 8), c->src << 24);
    IO_W((volatile u32 *)0x040001a4, data_021ff240[1]);
}

void CARDi_OnReadCard(void) {
    MI_StopDma(data_021fec00.dma);
    data_021fec00.src += 0x200;
    data_021fec00.dst += 0x200;
    data_021fec00.len -= 0x200;
    if (data_021fec00.len == 0) {
        OS_DisableIrqMask(0x80000);
        OS_ResetRequestIrqMask(0x80000);
        {
            CardCommon *const c = &data_021fec00;
            void (*cb)(u32);
            u32 arg;
            u32 irq;
            *c->result = 0;
            cb = c->callback;
            arg = c->callbackArg;
            irq = OS_DisableInterrupts();
            c->flag &= ~0x4c;
            OS_WakeupThread(&c->queue);
            if ((c->flag & 0x10) != 0) OS_WakeupThreadDirect(&c->thread);
            OS_RestoreInterrupts(irq);
            if (cb != 0) cb(arg);
        }
    } else {
        CARDi_SetCardDma();
    }
}

#include "nitro/os_rtc.h"
#include "uptr.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
#include "types64.h"
#include "nitro/io_access.h"
typedef int BOOL;

#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211d680.h"
#include "proto/autoload_2/unk_0211dc4c.h"
#include "proto/autoload_2/unk_0211e558.h"
#include "proto/autoload_2/unk_0211ea4c.h"
#include "proto/main/unk_02000b44.h"
#include "proto/main/unk_0206d49c.h"
typedef OSThreadQueue OSQ;
typedef OSThread OST;

typedef struct {
    u32 lock;
    uptr f4, f8, fc, f10;
    u32 command;
    u32 f18;
    uptr f1c;
    u32 result;
} RTCWork;

#include "sys/CardCmd.h"

typedef struct CARDCommon {
    CARDCmd *cmd;
    u32 f4;
    volatile u32 lockOwner;
    volatile u32 lockCount;
    OSQ queue;
    u32 lockType;
    uptr src;
    uptr dst;
    u32 len;
    u32 op;
    u32 f2c, f30, f34;
    void (*callback)(void *);
    void *cbArg;
    void (*task)(struct CARDCommon *);
    OST thread;
    OST *curThread;
    u32 priority;
    OSQ tq;
    volatile u32 flag;
    u32 f118, f11c;
    u8 buf[0x100];
} CARDCommon;

typedef struct {
    void (*fn)(void *);
    u32 f4;
    u32 f8;
    u32 fc;
    u32 f10, f14, f18, f1c;
    u32 buf[128];
} RomDev;

extern RTCWork data_021feb90;
extern u16 data_021feb8c;
extern CARDCommon data_021fec00;
extern u32 data_021febb4;
extern u8 data_021febc0[];
extern u32 data_021ff220;
extern RomDev data_021ff240;
extern OSThreadInfo data_021fcc2c;

u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32);
void OS_UnlockCard(u32);
void OS_LockCard(u32);
void OS_SetThreadPriority(void *, u32);
void OS_WakeupThreadDirect(void *);
void OS_CreateThread(void *, void (*)(void *), void *, void *, u32, u32);
void DC_InvalidateRange(void *, u32);
void DC_FlushRange(void *, u32);
void DC_WaitWriteBufferEmpty(void);
void MI_StopDma(u32);
void MIi_CpuClearFast(u32, void *, u32);
void MI_CpuFill8(void *, u32, u32);
void MI_CpuCopy8(const void *, void *, u32);
BOOL PXI_IsCallbackReady(u32, u32);
s32 PXI_SendWordByFifo(u32, u32, u32);
void PXI_SetFifoRecvCallback(u32, void *);
void RtcWaitBusy(void);
void RtcGetResultCallback(void);
void RtcCommonCallback(void);
void CARDi_OnFifoRecv(void);
BOOL CARDi_Request(void *, u32, u32);
void CARDi_SetRomOp(u32, u32);
BOOL CARDi_ReadFromCache(void *);
BOOL CARDi_TryReadCardDma(void *);

u32 RTC_GetDateTimeAsync(void *, void *, void (*)(void), void *);
u32 RTC_GetTimeAsync(void *, void (*)(void), void *);
u32 RTC_GetDateAsync(void *, void (*)(void), void *);
BOOL RtcSendPxiCommand(u32);
BOOL RTCi_ReadRawDateAsync(void);
BOOL RTCi_ReadRawTimeAsync(void);
BOOL RTCi_ReadRawDateTimeAsync(void);
s32 RTCi_ConvertTimeToSecond(RTCTime *);
s32 RTC_ConvertDateToDay(RTCDate *);
void CARD_Enable(u32);
u32 CARD_IsEnabled(void);
void CARDi_UnlockResource(u32, u32);
void CARDi_LockResource(u32, u32);
void CARDi_SetTask(void (*)(CARDCommon *));
void CARDi_IdentifyBackupCore(s32);
void CARDi_RequestStreamCommandCore(CARDCommon *);
BOOL CARD_WaitRomAsync(void);
void CARDi_ReadRomSyncCore(CARDCommon *);
BOOL CARDi_TryWaitAsync(void);
BOOL CARDi_WaitAsync(void);

#define REG_MCCNT1 (*(volatile u32 *)0x040001a4)
#define REG_MCD1 (*(volatile u32 *)0x04100010)

void CARDi_ReadCard(void *p) {
    RomDev *d = (RomDev *)p;
    CARDCommon *const c = &data_021fec00;
    u32 *dst;
    u32 *buf = d->buf;
    u32 mask = -512;
    do {
        u32 src = c->src;
        u32 page = src & mask;
        u32 n;
        u32 st;
        if (page != src || (dst = (u32 *)c->dst, ((uptr)dst & 3)) || c->len < 512) {
            dst = buf;
            d->f8 = page;
        }
        {
            extern void host_card_read(u32 addr, void *dst, u32 n);
            host_card_read(page, dst, 512);
            (void)n; (void)st;
        }
        if (dst == (u32 *)c->dst) {
            data_021fec00.src += 512;
            data_021fec00.dst += 512;
            data_021fec00.len -= 512;
            if (data_021fec00.len == 0) return;
        } else {
            if (!CARDi_ReadFromCache(d)) return;
        }
    } while (1);
}

void CARDi_ReadRomSyncCore(CARDCommon *unused) {
    RomDev *d = &data_021ff240;
    if (CARDi_ReadFromCache(d)) d->fn(d);
    {
        CARDCommon *const c = &data_021fec00;
        void (*cb)(void *);
        void *arg;
        u32 irq;
        c->cmd->result = 0;
        cb = c->callback;
        arg = c->cbArg;
        irq = OS_DisableInterrupts();
        c->flag &= ~0x4c;
        OS_WakeupThread(&c->tq);
        if (c->flag & 0x10) OS_WakeupThreadDirect(&c->thread);
        OS_RestoreInterrupts(irq);
        if (cb) cb(arg);
    }
}

void CARDi_ReadRom(u32 cmd, u32 off, void *dst, u32 len, void (*cb)(void *), void *arg, BOOL async) {
    CARDCommon *const c = &data_021fec00;
    RomDev *d = &data_021ff240;
    u32 irq;
    CARD_CheckEnabled();
    irq = OS_DisableInterrupts();
    while (c->flag & 4) OS_SleepThread(&c->tq);
    c->flag |= 4;
    c->callback = cb;
    c->cbArg = arg;
    OS_RestoreInterrupts(irq);
    c->op = cmd;
    c->src = off + data_021ff220;
    c->dst = (uptr)dst;
    c->len = len;
    if (cmd <= 3) MI_StopDma(cmd);
    if (CARDi_TryReadCardDma(d)) {
        if (async) return;
        CARD_WaitRomAsync();
        return;
    }
    if (async) {
        CARDi_SetTask(CARDi_ReadRomSyncCore);
        return;
    }
    c->curThread = data_021fcc2c.current;
    CARDi_ReadRomSyncCore(c);
}

void CARD_Init(void) {
    CARDCommon *const c = &data_021fec00;
    if (c->flag != 0) return;
    c->flag = 1;
    c->src = c->dst = c->len = 0;
    c->op = -1;
    c->callback = 0;
    c->cbArg = 0;
    data_021ff220 = 0;
    CARDi_InitCommon();
    data_021ff240.fn = (void (*)(void *))CARDi_GetRomAccessor();
    CARD_InitPulledOutCallback();
}

BOOL CARD_WaitRomAsync(void) {
    return CARDi_WaitAsync();
}

void *CARDi_GetRomAccessor(void) {
    return CARDi_ReadCard;
}

void CARDi_RequestStreamCommandCore(CARDCommon *c) {
    u32 g = c->f2c;
    u32 mode = c->f34;
    u32 h = c->f30;
    u32 pg = 256;
    u32 one = 1;
    void (*cb)(void *);
    void *arg;
    u32 irq;
    OSi_ReferSymbol(0);
    do {
        u32 len = c->len;
        if (len > pg) len = pg;
        c->cmd->len = len;
        if (c->flag & 0x40) {
            c->flag &= ~0x40;
            c->cmd->result = 7;
            break;
        }
        if (mode == 0) {
            DC_InvalidateRange(c->buf, len);
            c->cmd->srcBuf = c->src;
            c->cmd->dstBuf = (uptr)c->buf;
        } else {
            MI_CpuCopy8((void *)c->src, c->buf, len);
            DC_FlushRange(c->buf, len);
            DC_WaitWriteBufferEmpty();
            c->cmd->srcBuf = (uptr)c->buf;
            c->cmd->dstBuf = c->dst;
        }
        if (!CARDi_Request(c, g, h)) break;
        if (mode == 2) {
            if (!CARDi_Request(c, 9, one)) break;
        } else if (mode == 0) {
            MI_CpuCopy8(c->buf, (void *)c->dst, len);
        }
        c->src += len;
        c->dst += len;
        c->len -= len;
    } while (c->len != 0);
    cb = c->callback;
    arg = c->cbArg;
    irq = OS_DisableInterrupts();
    c->flag &= ~0x4c;
    OS_WakeupThread(&c->tq);
    if (c->flag & 0x10) OS_WakeupThreadDirect(&c->thread);
    OS_RestoreInterrupts(irq);
    if (cb) cb(arg);
}

BOOL CARDi_RequestStreamCommand(uptr a, uptr b, u32 len, void (*cb)(void *), void *arg, BOOL async, u32 g, u32 h, u32 mode) {
    CARDCommon *const c = &data_021fec00;
    u32 irq;
    OSi_ReferSymbol(0);
    irq = OS_DisableInterrupts();
    while (c->flag & 4) OS_SleepThread(&c->tq);
    c->flag |= 4;
    c->callback = cb;
    c->cbArg = arg;
    OS_RestoreInterrupts(irq);
    c->src = a;
    c->dst = b;
    c->len = len;
    c->f2c = g;
    c->f30 = h;
    c->f34 = mode;
    if (async) {
        CARDi_SetTask(CARDi_RequestStreamCommandCore);
        return 1;
    }
    data_021fec00.curThread = data_021fcc2c.current;
    CARDi_RequestStreamCommandCore(c);
    return c->cmd->result == 0;
}

u32 CARD_GetBackupTotalSize(void) {
    return data_021fec00.cmd->f18;
}

BOOL CARD_IdentifyBackup(u32 op) {
    CARDCommon *c = &data_021fec00;
    void (*cb)(void *);
    void *arg;
    u32 irq;
    OSi_ReferSymbol(0);
    if (op == 0) Fatal_Trap();
    CARD_CheckEnabled();
    irq = OS_DisableInterrupts();
    while (c->flag & 4) OS_SleepThread(&c->tq);
    c->flag |= 4;
    c->callback = 0;
    c->cbArg = 0;
    OS_RestoreInterrupts(irq);
    CARDi_IdentifyBackupCore(op);
    data_021fec00.curThread = data_021fcc2c.current;
    CARDi_Request(c, 2, 1);
    c->cmd->srcBuf = 0;
    c->cmd->dstBuf = (uptr)c->buf;
    c->cmd->len = 1;
    CARDi_Request(c, 6, 1);
    cb = c->callback;
    arg = c->cbArg;
    irq = OS_DisableInterrupts();
    c->flag &= ~0x4c;
    OS_WakeupThread(&c->tq);
    if (c->flag & 0x10) OS_WakeupThreadDirect(&c->thread);
    OS_RestoreInterrupts(irq);
    if (cb) cb(arg);
    return c->cmd->result == 0;
}

BOOL CARD_TryWaitBackupAsync(void) {
    return CARDi_TryWaitAsync();
}

void CARD_CancelBackupAsync(void) {
    u32 irq = OS_DisableInterrupts();
    data_021fec00.flag |= 0x40;
    OS_RestoreInterrupts(irq);
}

u32 data_021ff220;
RomDev data_021ff240 __attribute__((aligned(32)));

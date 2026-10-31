#include "nitro/os_rtc.h"
#include "uptr.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
#include "types64.h"
typedef int BOOL;

#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211d20c.h"
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
    u32 buf[512];
} RomDev;

extern RTCWork data_021feb90;
extern u16 data_021feb8c;
extern CARDCommon data_021fec00;
extern u32 data_021febb4;
extern u8 data_021febc0[];
extern u32 data_021ff220;
extern RomDev data_021ff240;
extern OSThreadInfo data_021fcc2c;
extern u32 data_0213c1cc[12];

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
s32 RTC_ConvertDateToDay(RTCDate *date) {
    s32 days;
    if (date->year >= 100 || date->month < 1 || date->month > 12 || date->day < 1 || date->day > 31 || date->week >= 7 || date->month < 1 || date->month > 12)
        return -1;
    days = date->day - 1 + (data_0213c1cc - 1)[date->month];
    if (date->month >= 3 && (date->year & 3) == 0) days++;
    return date->year * 365 + days + ((date->year + 3) >> 2);
}

s32 RTCi_ConvertTimeToSecond(RTCTime *t) {
    return (t->hour * 60 + t->minute) * 60 + t->second;
}

s64 RTC_ConvertDateTimeToSecond(RTCDate *date, RTCTime *time) {
    s32 day = RTC_ConvertDateToDay(date);
    s32 sec;
    if (day == -1) return -1;
    sec = RTCi_ConvertTimeToSecond(time);
    if (sec == -1) return -1;
    return (s64)day * 86400 + sec;
}

BOOL RTCi_ReadRawDateTimeAsync(void) {
    return RtcSendPxiCommand(0x10);
}

BOOL RTCi_ReadRawDateAsync(void) {
    return RtcSendPxiCommand(0x11);
}

BOOL RTCi_ReadRawTimeAsync(void) {
    return RtcSendPxiCommand(0x12);
}

BOOL RTCi_WriteRawStatus2Async(void) {
    return RtcSendPxiCommand(0x27);
}

BOOL RtcSendPxiCommand(u32 cmd) {
    return PXI_SendWordByFifo(5, (cmd << 8) & 0x7f00, 0) >= 0;
}

void RTC_Init(void) {
    if (data_021feb8c) return;
    data_021feb8c = 1;
    data_021feb90.lock = 0;
    data_021feb90.f4 = 0;
    data_021feb90.f1c = 0;
    data_021feb90.f8 = 0;
    data_021feb90.fc = 0;
    PXI_Init();
    while (!PXI_IsCallbackReady(5, 1)) {
    }
    PXI_SetFifoRecvCallback(5, RtcCommonCallback);
}

u32 RTC_GetDateAsync(void *a, void (*cb)(void), void *arg) {
    u32 irq = OS_DisableInterrupts();
    if (data_021feb90.lock) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    data_021feb90.lock = 1;
    OS_RestoreInterrupts(irq);
    data_021feb90.command = 0;
    data_021feb90.f18 = 0;
    data_021feb90.f8 = (uptr)a;
    data_021feb90.f4 = (uptr)cb;
    data_021feb90.f10 = (uptr)arg;
    return RTCi_ReadRawDateAsync() ? 0 : 3;
}

u32 RTC_GetDate(void *a) {
    u32 r = RTC_GetDateAsync(a, RtcGetResultCallback, 0);
    data_021feb90.result = r;
    if (!r) RtcWaitBusy();
    return data_021feb90.result;
}

u32 RTC_GetTimeAsync(void *a, void (*cb)(void), void *arg) {
    u32 irq = OS_DisableInterrupts();
    if (data_021feb90.lock) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    data_021feb90.lock = 1;
    OS_RestoreInterrupts(irq);
    data_021feb90.command = 1;
    data_021feb90.f18 = 0;
    data_021feb90.f8 = (uptr)a;
    data_021feb90.f4 = (uptr)cb;
    data_021feb90.f10 = (uptr)arg;
    return RTCi_ReadRawTimeAsync() ? 0 : 3;
}

u32 RTC_GetTime(void *a) {
    u32 r = RTC_GetTimeAsync(a, RtcGetResultCallback, 0);
    data_021feb90.result = r;
    if (!r) RtcWaitBusy();
    return data_021feb90.result;
}

u32 RTC_GetDateTimeAsync(void *a, void *b, void (*cb)(void), void *arg) {
    u32 irq = OS_DisableInterrupts();
    if (data_021feb90.lock) {
        OS_RestoreInterrupts(irq);
        return 1;
    }
    data_021feb90.lock = 1;
    OS_RestoreInterrupts(irq);
    data_021feb90.command = 2;
    data_021feb90.f18 = 0;
    data_021feb90.f8 = (uptr)a;
    data_021feb90.fc = (uptr)b;
    data_021feb90.f4 = (uptr)cb;
    data_021feb90.f10 = (uptr)arg;
    return RTCi_ReadRawDateTimeAsync() ? 0 : 3;
}

u32 RTC_GetDateTime(void *a, void *b) {
    u32 r = RTC_GetDateTimeAsync(a, b, RtcGetResultCallback, 0);
    data_021feb90.result = r;
    if (!r) RtcWaitBusy();
    return data_021feb90.result;
}

u32 data_0213c1cc[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

u16 data_021feb8c;
RTCWork data_021feb90;

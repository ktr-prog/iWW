#include "sys/PMCbInfo.h"
#include "host_mem.h"
#include "uptr.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "sys/OSThread.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211c8e8.h"
#include "proto/main/unk_0206d49c.h"
typedef signed short s16;
typedef signed int s32;
typedef int BOOL;

typedef struct {
    s16 x0;
    s16 y0;
    s16 xDotSize;
    s16 yDotSize;
} TPCalibrateParam;

typedef struct {
    u8 pad[0x58];
    u16 x1;
    u16 y1;
    u8 dx1;
    u8 dy1;
    u16 x2;
    u16 y2;
    u8 dx2;
    u8 dy2;
} TPUserInfo;

typedef void (*TPCallback)(u32 type, u32 result, u32 arg);

typedef struct {
    TPCallback callback;
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
    u16 index;
    u16 pad0e;
    void *buf;
    u16 bufSize;
    u16 pad16;
    s32 x0;
    s32 xDot;
    s32 xRatio;
    s32 y0;
    s32 yDot;
    s32 yRatio;
    u16 calibrated;
    volatile u16 state;
    volatile u16 pending;
    volatile u16 busy;
} TPWork;

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPData;

typedef union {
    u32 raw;
    u16 half[2];
    struct {
        u32 x : 12;
        u32 y : 12;
        u32 touch : 1;
        u32 validity : 2;
        u32 pad : 5;
    } b;
} TPRaw;


typedef struct PMCbInfo PMCbInfo;

typedef void (*PMCallback)(u32 result, void *arg);

typedef struct {
    u32 lock;
    PMCallback volatile callback;
    void *arg;
    u32 *out;
} PMWork;

typedef struct {
    u32 lock;
    PMCallback callback;
    u32 *dst1;
    u32 *dst2;
    void *arg;
    u32 command;
    u32 busy;
    void (*intCallback)(void);
    u32 cb20;
} RTCWork;

typedef struct {
    u32 pad0;
    PMCallback callback;
    u32 pad1[2];
    void *arg;
} RTCCb;

typedef struct {
    u32 year : 8;
    u32 month : 5;
    u32 pad0 : 3;
    u32 day : 6;
    u32 pad1 : 2;
    u32 week : 3;
    u32 pad2 : 5;
} RTCRawDate;

typedef struct {
    u32 hour : 6;
    u32 pad0 : 2;
    u32 minute : 7;
    u32 pad1 : 1;
    u32 second : 7;
    u32 pad2 : 9;
} RTCRawTime;

typedef struct {
    u32 week : 3;
    u32 pad0 : 4;
    u32 weekOn : 1;
    u32 hour : 6;
    u32 pad1 : 1;
    u32 hourOn : 1;
    u32 minute : 7;
    u32 minuteOn : 1;
    u32 pad2 : 8;
} RTCRawAlarm;

typedef struct {
    u16 mode : 4;
    u16 pad0 : 2;
    u16 flag : 1;
    u16 pad1 : 9;
} RTCRawStatus;

extern TPWork data_021feaf4;
extern u16 data_021feaf0;

extern PMWork data_021feb44;
extern u16 data_021feb2c;
extern u32 data_021feb30;
extern u32 data_021feb34;
extern PMCbInfo *data_021feb38;
extern u32 data_021feb3c;
extern PMCbInfo *data_021feb40;
extern OSMutex data_021feb54;
PMRegInfo data_021feb6c[4];
extern RTCWork data_021feb90;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern u32 TP_CalcCalibrateParam(TPCalibrateParam *p, u16 x1, u16 y1, u8 dx1, u8 dy1, u16 x2, u16 y2, u8 dx2, u8 dy2);
extern BOOL PXI_IsCallbackReady(u32 tag, u32 proc);
extern void PXI_SetFifoRecvCallback(u32 tag, void *cb);
extern s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);
extern BOOL RTCi_WriteRawStatus2Async(void);

void PMi_DeleteList(PMCbInfo **head, PMCbInfo *info);
void PMi_AppendList(PMCbInfo **head, PMCbInfo *info);
void PMi_PrependList(PMCbInfo **head, PMCbInfo *info);
u32 PM_GetLEDPatternAsync(u32 *out, PMCallback cb, void *arg);
void PMi_DummyCallback(u32 result, void *arg);
BOOL PMi_Lock(void);
void PMi_SendPxiData(u32 data);
u32 PMi_SendLEDPatternCommandAsync(u32 a, PMCallback cb, void *arg);
u32 PMi_SetLED(u32 a);
u32 PMi_SetLEDAsync(u32 a, PMCallback cb, void *arg);
u32 PMi_ReadRegister(u32 type, u16 *out);
u32 PMi_ReadRegisterAsync(u32 type, u16 *out, PMCallback cb, void *arg);
u32 PM_SendUtilityCommandAsync(u32 cmd, PMCallback cb, void *arg);
u32 PM_ForceToPowerOffAsync(PMCallback cb, void *arg);
u32 PM_SetBackLightAsync(u32 a, u32 b, PMCallback cb, void *arg);
void PMi_CallCallbackAndUnlock(u32 result);
u32 RtcBCD2HEX(u32 bcd);
void TPi_TpCallback(u32 tag, u32 data, u32 err);
void PMi_CommonCallback(u32 tag, u32 data, u32 err);
u32 PMi_SetLCDPower(u32 mode, u32 target, u32 noWait, u32 sync);

BOOL PMi_Lock(void) {
    u32 e = OS_DisableInterrupts();
    if (data_021feb44.lock != 0) {
        OS_RestoreInterrupts(e);
        return 0;
    }
    data_021feb44.lock = 1;
    OS_RestoreInterrupts(e);
    return 1;
}

void PMi_WaitBusy(void) {
    volatile u32 *p = &data_021feb44.lock;
    while (*p != 0) {
    }
}

void PMi_DummyCallback(u32 result, void *arg) {
    *(u32 *)arg = result;
}

void PMi_CallCallbackAndUnlock(u32 result) {
    u32 lock = data_021feb44.lock;
    PMCallback cb = data_021feb44.callback;
    void *arg = data_021feb44.arg;
    if (lock != 0) {
        data_021feb44.lock = 0;
    }
    if (cb != 0) {
        data_021feb44.callback = 0;
        cb(result, arg);
    }
}

void PM_Init(void) {
    int i;
    if (data_021feb2c != 0) {
        return;
    }
    data_021feb2c = 1;
    data_021feb44.lock = 0;
    data_021feb44.callback = 0;
    PXI_Init();
    while (!PXI_IsCallbackReady(8, 1)) {
    }
    PXI_SetFifoRecvCallback(8, PMi_CommonCallback);
    for (i = 0; i < 4; i++) {
        data_021feb6c[i].flag = 0;
    }
    OS_InitMutex(&data_021feb54);
    data_021feb3c = *HW_SYSWORK(volatile u32, vblankCount);
}

void PMi_CommonCallback(u32 tag, u32 data, u32 err) {
    u32 result;
    if (err) {
        PMi_CallCallbackAndUnlock(2);
        return;
    }
    {
        u16 cmd = (u16)((data & 0x7f00) >> 8);
        u16 val = (u16)(data & 0xff);
        result = val;
        if (cmd >= 0x70 && cmd <= 0x73) {
            u16 *p = data_021feb6c[cmd - 0x70].ptr;
            u16 w = (u16)(result & 0xff);
            if (p != 0) {
                *p = w;
            }
            data_021feb6c[cmd - 0x70].flag = 1;
            result = 0;
        } else if (cmd == 0x60) {
            data_021feb30 = 1;
        } else if (cmd == 0x62) {
            data_021feb34 = 1;
        } else if (cmd == 0x67) {
            u32 *p = data_021feb44.out;
            if (p != 0) {
                *p = result;
            }
            result = 0;
        }
        PMi_CallCallbackAndUnlock(result);
    }
}

u32 PM_SendUtilityCommandAsync(u32 cmd, PMCallback cb, void *arg) {
    if (!PMi_Lock()) {
        return 1;
    }
    data_021feb44.callback = cb;
    data_021feb44.arg = arg;
    PMi_SendPxiData(((cmd >> 16) & 0xff) | 0x02006300);
    PMi_SendPxiData((cmd & 0xffff) | 0x01010000);
    return 0;
}

u16 data_021feb2c;
u32 data_021feb3c;
PMCbInfo *data_021feb40;
u32 data_021feb34;
PMCbInfo *data_021feb38;
u32 data_021feb30;
PMWork data_021feb44;
OSMutex data_021feb54;

#include "sys/PMCbInfo.h"
#include "host_mem.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02117984.h"
#include "proto/autoload_2/unk_0211bcdc.h"
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
extern u8 data_021feb54[];
extern PMRegInfo data_021feb6c[4];
extern RTCWork data_021feb90;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern u32 TP_CalcCalibrateParam(TPCalibrateParam *p, u16 x1, u16 y1, u16 dx1, u16 dy1, u16 x2, u16 y2, u16 dx2, u16 dy2);
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

u32 PMi_ReadRegister(u32 type, u16 *out) {
    u32 result;
    u32 r = PMi_ReadRegisterAsync(type, out, PMi_DummyCallback, &result);
    if (r != 0) {
        return r;
    }
    PMi_WaitBusy();
    return result;
}

u32 PMi_SetLEDAsync(u32 a, PMCallback cb, void *arg) {
    u32 cmd;
    switch (a) {
    case 1:
        cmd = 1;
        break;
    case 3:
        cmd = 2;
        break;
    case 2:
        cmd = 3;
        break;
    default:
        cmd = 0;
        break;
    }
    if (cmd == 0) {
        return 0xffff;
    }
    return PM_SendUtilityCommandAsync(cmd, cb, arg);
}

u32 PMi_SetLED(u32 a) {
    u32 result;
    u32 r = PMi_SetLEDAsync(a, PMi_DummyCallback, &result);
    if (r != 0) {
        return r;
    }
    PMi_WaitBusy();
    return result;
}

u32 PM_SetBackLightAsync(u32 a, u32 b, PMCallback cb, void *arg) {
    u32 cmd = 0;
    if (a == 0) {
        if (b == 1) {
            cmd = 6;
        }
        if (b == 0) {
            cmd = 7;
        }
    } else if (a == 1) {
        if (b == 1) {
            cmd = 4;
        }
        if (b == 0) {
            cmd = 5;
        }
    } else if (a == 2) {
        if (b == 1) {
            cmd = 8;
        }
        if (b == 0) {
            cmd = 9;
        }
    }
    if (cmd == 0) {
        return 0xffff;
    }
    return PM_SendUtilityCommandAsync(cmd, cb, arg);
}

u32 PM_SetBackLight(u32 a, u32 b) {
    u32 result;
    u32 r = PM_SetBackLightAsync(a, b, PMi_DummyCallback, &result);
    if (r != 0) {
        return r;
    }
    PMi_WaitBusy();
    return result;
}

u32 PM_ForceToPowerOffAsync(PMCallback cb, void *arg) {
    return PM_SendUtilityCommandAsync(14, cb, arg);
}

u32 PM_ForceToPowerOff(void) {
    u32 result;
    u32 r = PM_ForceToPowerOffAsync(PMi_DummyCallback, &result);
    if (r != 0) {
        return r;
    }
    PMi_WaitBusy();
    return result;
}

u32 PM_GetBattery(u32 *p) {
    u16 v;
    u32 r = PMi_ReadRegister(1, &v);
    if (r != 0) {
        return r;
    }
    if (p != 0) {
        *p = (v & 1) ? 1 : 0;
    }
    return r;
}

u32 PM_GetBackLight(u32 *p1, u32 *p2) {
    u16 v;
    u32 r = PMi_ReadRegister(0, &v);
    if (r != 0) {
        return r;
    }
    if (p1 != 0) {
        *p1 = (v & 8) ? 1 : 0;
    }
    if (p2 != 0) {
        *p2 = (v & 4) ? 1 : 0;
    }
    return r;
}

void PMi_SendPxiData(u32 data) {
    while (PXI_SendWordByFifo(8, data, 0) != 0) {
    }
}

u32 PMi_SetLCDPower(u32 mode, u32 target, u32 noWait, u32 sync) {
    switch (mode) {
    case 1:
        if (noWait == 0) {
            if (*HW_SYSWORK(volatile u32, vblankCount) - data_021feb3c <= 7) {
                return 0;
            }
        }
        if (target != 0) {
            if (sync != 0) {
                PMi_SetLED(target);
            } else {
                PMi_SetLEDAsync(target, 0, 0);
            }
        }
        IO_OR((volatile u16 *)0x04000304, 1);
        break;
    case 0:
        IO_AND((volatile u16 *)0x04000304, ~1);
        data_021feb3c = *HW_SYSWORK(volatile u32, vblankCount);
        if (target != 0) {
            if (sync != 0) {
                PMi_SetLED(target);
            } else {
                PMi_SetLEDAsync(target, 0, 0);
            }
        }
        break;
    }
    return 1;
}

u32 PM_SetLCDPower(u32 a) {
    if (a != 1) {
        a = 0;
    }
    return PMi_SetLCDPower(a, 0, 0, 1);
}

BOOL PM_GetLCDPower(void) {
    return (IO_R((volatile u16 *)0x04000304) & 1) != 0;
}

u32 PMi_SendLEDPatternCommandAsync(u32 a, PMCallback cb, void *arg) {
    if (!PMi_Lock()) {
        return 1;
    }
    data_021feb44.callback = cb;
    data_021feb44.arg = arg;
    PMi_SendPxiData(0x03006600 | (u8)a);
    return 0;
}

u32 PMi_SendLEDPatternCommand(u32 a) {
    u32 result;
    u32 r = PMi_SendLEDPatternCommandAsync(a, PMi_DummyCallback, &result);
    if (r != 0) {
        return r;
    }
    PMi_WaitBusy();
    return result;
}

u32 PM_GetLEDPatternAsync(u32 *out, PMCallback cb, void *arg) {
    if (!PMi_Lock()) {
        return 1;
    }
    data_021feb44.callback = cb;
    data_021feb44.arg = arg;
    data_021feb44.out = out;
    PMi_SendPxiData(0x03006700);
    return 0;
}

u32 PM_GetLEDPattern(u32 *out) {
    u32 result;
    u32 r = PM_GetLEDPatternAsync(out, PMi_DummyCallback, &result);
    if (r != 0) {
        return r;
    }
    PMi_WaitBusy();
    return result;
}

void PMi_PrependList(PMCbInfo **head, PMCbInfo *info) {
    if (head != 0) {
        info->next = *head;
        *head = info;
    }
}

void PMi_AppendList(PMCbInfo **head, PMCbInfo *info) {
    PMCbInfo *cur;
    if (head == 0) {
        return;
    }
    cur = *head;
    if (cur == 0) {
        info->next = 0;
        *head = info;
        return;
    }
    while (cur->next != 0) {
        cur = cur->next;
    }
    info->next = cur->next;
    cur->next = info;
}

void PMi_DeleteList(PMCbInfo **head, PMCbInfo *info) {
    PMCbInfo *cur;
    PMCbInfo *prev;
    if (head == 0) {
        return;
    }
    cur = *head;
    prev = cur;
    for (; cur != 0; prev = cur, cur = cur->next) {
        if (cur == info) {
            if (cur == prev) {
                *head = cur->next;
            } else {
                prev->next = cur->next;
            }
            return;
        }
    }
}

void PM_PrependPreSleepCallback(PMCbInfo *info) {
    PMi_PrependList(&data_021feb38, info);
}

void PM_AppendPostSleepCallback(PMCbInfo *info) {
    PMi_AppendList(&data_021feb40, info);
}

void PM_DeletePreSleepCallback(PMCbInfo *info) {
    PMi_DeleteList(&data_021feb38, info);
}

void PM_DeletePostSleepCallback(PMCbInfo *info) {
    PMi_DeleteList(&data_021feb40, info);
}

void TPi_TpCallback(u32 tag, u32 data, u32 err) {
    u16 d = (u16)data;
    u16 type = (u16)((d & 0x7f00) >> 8);
    if (err) {
        data_021feaf4.pending |= 1 << type;
        if (data_021feaf4.callback) {
            data_021feaf4.callback(type, 4, 0);
        }
        return;
    }
    if (type == 16) {
        TPRaw tp;
        TPData *e;
        data_021feaf4.index++;
        if (data_021feaf4.index >= data_021feaf4.bufSize) {
            data_021feaf4.index = 0;
        }
        e = &((TPData *)data_021feaf4.buf)[data_021feaf4.index];
        tp.half[0] = *HW_SYSWORK(volatile u16, touchPanel);
        tp.half[1] = *HW_SYSWORK_AT(volatile u16, touchPanel, 0x2);
        e->x = tp.b.x;
        e->y = tp.b.y;
        e->touch = (u8)tp.b.touch;
        e->validity = (u8)tp.b.validity;
        if (data_021feaf4.callback) {
            data_021feaf4.callback(type, 0, (u8)data_021feaf4.index);
        }
        return;
    }
    if (!(data & 0x1000000)) {
        return;
    }
    {
        u32 ev;
        switch ((u8)d) {
        case 0:
            switch (type) {
            case 0: {
                TPRaw tp;
                tp.half[0] = *HW_SYSWORK(volatile u16, touchPanel);
                tp.half[1] = *HW_SYSWORK_AT(volatile u16, touchPanel, 0x2);
                data_021feaf4.state = 0;
                data_021feaf4.x = tp.b.x;
                data_021feaf4.y = tp.b.y;
                data_021feaf4.touch = (u8)tp.b.touch;
                data_021feaf4.validity = (u8)tp.b.validity;
                break;
            }
            case 1:
                data_021feaf4.state = 2;
                break;
            case 2:
                data_021feaf4.state = 0;
                break;
            }
            data_021feaf4.busy &= ~(1 << type);
            if (data_021feaf4.callback) {
                data_021feaf4.callback(type, 0, 0);
            }
            return;
        case 4:
            ev = 3;
            goto done;
        case 2:
            ev = 1;
            goto done;
        case 3:
            ev = 2;
        done:
            data_021feaf4.pending |= 1 << type;
            data_021feaf4.busy &= ~(1 << type);
            if (data_021feaf4.callback) {
                data_021feaf4.callback(type, (u8)ev, 0);
            }
            return;
        }
        Fatal_Trap();
    }
}

void TP_Init(void) {
    if (data_021feaf0 != 0) {
        return;
    }
    data_021feaf0 = 1;
    PXI_Init();
    data_021feaf4.state = 0;
    data_021feaf4.busy = 0;
    data_021feaf4.index = 0;
    data_021feaf4.callback = 0;
    data_021feaf4.buf = 0;
    data_021feaf4.calibrated = 0;
    data_021feaf4.pending = 0;
    while (!PXI_IsCallbackReady(6, 1)) {
    }
    PXI_SetFifoRecvCallback(6, TPi_TpCallback);
}

BOOL TP_GetUserInfo(TPCalibrateParam *p) {
    u8 *nv = HW_SYSWORK(u8, nvramUserInfo);
    u8 dy2;
    u16 x2;
    u16 y2;
    u16 x1;
    u16 y1;
    u8 dy1;
    u8 dx2;
    u8 dx1;
    x1 = *(u16 *)(nv + 0x58);
    y1 = *(u16 *)(nv + 0x5a);
    dx1 = nv[0x5c];
    dy1 = nv[0x5d];
    x2 = *(u16 *)(nv + 0x5e);
    y2 = *(u16 *)(nv + 0x60);
    dx2 = nv[0x62];
    dy2 = nv[0x63];
    if (x1 != 0 || x2 != 0 || y1 != 0 || y2 != 0) {
        if (TP_CalcCalibrateParam(p, x1, y1, dx1, dy1, x2, y2, dx2, dy2) == 0) {
            goto ret;
        }
    }
    p->x0 = 0;
    p->y0 = 0;
    p->xDotSize = 0;
    p->yDotSize = 0;
    return 1;
ret:
    return 1;
}

void TP_SetCalibrateParam(TPCalibrateParam *p) {
    u32 e;
    s32 dot;
    if (p == 0) {
        data_021feaf4.calibrated = 0;
        return;
    }
    e = OS_DisableInterrupts();
    dot = p->xDotSize;
    if (dot != 0) {
        IO_W((volatile u16 *)0x04000280, 0);
        IO_W((volatile u32 *)0x04000290, 0x10000000);
        IO_W((volatile u64 *)0x04000298, (u64)(u32)dot);
        data_021feaf4.x0 = p->x0;
        data_021feaf4.xDot = p->xDotSize;
        while (IO_R((volatile u16 *)0x04000280) & 0x8000) {
        }
        data_021feaf4.xRatio = IO_R((volatile u32 *)0x040002a0);
    } else {
        data_021feaf4.x0 = 0;
        data_021feaf4.xDot = 0;
        data_021feaf4.xRatio = 0;
    }
    dot = p->yDotSize;
    if (dot != 0) {
        IO_W((volatile u16 *)0x04000280, 0);
        IO_W((volatile u32 *)0x04000290, 0x10000000);
        IO_W((volatile u64 *)0x04000298, (u64)(u32)dot);
        data_021feaf4.y0 = p->y0;
        data_021feaf4.yDot = p->yDotSize;
        while (IO_R((volatile u16 *)0x04000280) & 0x8000) {
        }
        data_021feaf4.yRatio = IO_R((volatile u32 *)0x040002a0);
    } else {
        data_021feaf4.y0 = 0;
        data_021feaf4.yDot = 0;
        data_021feaf4.yRatio = 0;
    }
    OS_RestoreInterrupts(e);
    data_021feaf4.calibrated = 1;
}

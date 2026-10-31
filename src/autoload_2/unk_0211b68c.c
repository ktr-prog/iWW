typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
#include "types64.h"
#include "host_labels.h"

typedef void (*TPCallback)(u32 command, u32 result, u32 arg);

typedef struct {
    u16 x, y, touch, validity;
} TPData;

typedef struct {
    TPCallback callback;
    u32 pad04;
    u32 pad08;
    u16 sampling;
    u16 range;
    TPData *buf;
    u16 bufSize;
    u8 pad16[0x30 - 0x16];
    u16 calibrateOn;
    u16 pad32;
    volatile u16 state;
    volatile u16 ack;
} TPWork;

typedef struct {
    s16 x0, y0, xDotSize, yDotSize;
} TPCalibrateParam;

typedef struct {
    s32 x0, pad04, xScale, y0, pad10, yScale;
} TPCalibInternal;

extern TPWork data_021feaf4;
#define data_021feb0c HOST_LABEL(TPCalibInternal *, data_021feb0c)

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 e);
extern s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);

#define reg_DIVCNT (*(volatile u16 *)0x04000280)
#define reg_DIV_NUMER (*(volatile u32 *)0x04000290)
#define reg_DIV_DENOM (*(volatile u32 *)0x04000298)
#define reg_DIV_DENOM_HI (*(volatile u32 *)0x0400029c)
#define reg_DIV_RESULT (*(volatile s32 *)0x040002a0)

void TP_GetCalibratedPoint(TPData *disp, const TPData *raw) {
    TPCalibInternal *p;
    if (data_021feaf4.calibrateOn == 0) {
        *disp = *raw;
        return;
    }
    disp->touch = raw->touch;
    disp->validity = raw->validity;
    p = &data_021feb0c;
    if (raw->touch == 0) {
        disp->x = 0;
        disp->y = 0;
        return;
    }
    disp->x = (((s64)(raw->x << 2) - p->x0) * p->xScale) >> 22;
    if ((s16)disp->x < 0) {
        disp->x = 0;
    } else if ((s16)disp->x > 255) {
        disp->x = 255;
    }
    disp->y = (((s64)(raw->y << 2) - p->y0) * p->yScale) >> 22;
    if ((s16)disp->y < 0) {
        disp->y = 0;
        return;
    }
    if ((s16)disp->y > 191) {
        disp->y = 191;
    }
}

void TP_WaitBusy(u32 mask) {
    while (data_021feaf4.ack & mask)
        ;
}

u32 TP_CheckError(u32 mask) {
    return data_021feaf4.state & mask;
}

u16 data_021feaf0;
TPWork data_021feaf4;

#include "host_labels.h"

HOST_LABEL_DEFINE(data_021feb0c, (char *)&data_021feaf4.pad16[2]);

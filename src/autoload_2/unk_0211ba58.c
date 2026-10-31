typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
#include "types64.h"

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
extern TPCalibInternal data_021feb0c;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 e);
extern s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);

#define reg_DIVCNT (*(volatile u16 *)0x04000280)
#define reg_DIV_NUMER (*(volatile u32 *)0x04000290)
#define reg_DIV_DENOM (*(volatile u32 *)0x04000298)
#define reg_DIV_DENOM_HI (*(volatile u32 *)0x0400029c)
#define reg_DIV_RESULT (*(volatile s32 *)0x040002a0)

void TP_RequestAutoSamplingStartAsync(u32 a, u32 b, TPData *buf, u32 n) {
    u32 i;
    TPWork *w = &data_021feaf4;
    u32 e;
    u32 ok;
    w->buf = buf;
    w->sampling = 0;
    w->range = b;
    w->bufSize = n;
    for (i = 0; i < n; i++) {
        w->buf[i].touch = 0;
    }
    e = OS_DisableInterrupts();
    if (PXI_SendWordByFifo(6, (b & 0xff) | 0x02000100, 0) < 0) {
        ok = 0;
    } else if (PXI_SendWordByFifo(6, a | 0x01010000, 0) < 0) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (!(u8)ok) {
        OS_RestoreInterrupts(e);
        data_021feaf4.state |= 2;
        if (data_021feaf4.callback) {
            data_021feaf4.callback(1, 4, 0);
        }
        return;
    }
    data_021feaf4.ack |= 2;
    data_021feaf4.state &= ~2;
    OS_RestoreInterrupts(e);
}

void TP_RequestAutoSamplingStopAsync(void) {
    u32 e = OS_DisableInterrupts();
    u32 ok = PXI_SendWordByFifo(6, 0x03000200, 0) >= 0;
    if (!ok) {
        OS_RestoreInterrupts(e);
        data_021feaf4.state |= 4;
        if (data_021feaf4.callback) {
            data_021feaf4.callback(2, 4, 0);
        }
    } else {
        data_021feaf4.ack |= 4;
        data_021feaf4.state &= ~4;
        OS_RestoreInterrupts(e);
    }
}

void TP_RequestSetStabilityAsync(u32 unused, u32 data) {
    u32 e = OS_DisableInterrupts();
    u32 ok = PXI_SendWordByFifo(6, data | 0x03000300, 0) >= 0;
    if (!ok) {
        OS_RestoreInterrupts(e);
        data_021feaf4.state |= 8;
        if (data_021feaf4.callback) {
            data_021feaf4.callback(3, 4, 0);
        }
    } else {
        data_021feaf4.ack |= 8;
        data_021feaf4.state &= ~8;
        OS_RestoreInterrupts(e);
    }
}

u16 TP_GetLatestIndexInAuto(void) {
    return data_021feaf4.sampling;
}

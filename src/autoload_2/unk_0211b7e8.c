#include "nitro/io_access.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    s16 x0, y0, xDotSize, yDotSize;
} TPCalibrateParam;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 e);

static inline void CP_SetDiv32_32(u32 numer, u32 denom) {
    IO_W((volatile u16 *)0x04000280, 0);
    IO_W((volatile u32 *)0x04000290, numer);
    IO_W((volatile unsigned long long *)0x04000298, denom);
}
static inline void CP_WaitDiv(void) {
    while (IO_R((volatile u16 *)0x04000280) & 0x8000) {
    }
}
static inline s32 CP_GetDivResult32(void) {
    CP_WaitDiv();
    return IO_R((volatile s32 *)0x040002a0);
}
u32 TP_CalcCalibrateParam(void *param, u16 x1, u16 y1, u16 dx1, u16 dy1, u16 x2, u16 y2, u16 dx2, u16 dy2) {
    TPCalibrateParam *p = (TPCalibrateParam *)param;
    s32 rx_width, dx_width, ry_width, dy_width;
    s32 tmp32;
    u32 e;
    if (x1 >= 0x1000 || y1 >= 0x1000 || x2 >= 0x1000 || y2 >= 0x1000) {
        return 1;
    }
    if (dx1 >= 0x100 || dx2 >= 0x100 || dy1 >= 0xc0 || dy2 >= 0xc0) {
        return 1;
    }
    if (dx1 == dx2 || dy1 == dy2 || x1 == x2 || y1 == y2) {
        return 1;
    }
    rx_width = x1 - x2;
    dx_width = dx1 - dx2;
    e = OS_DisableInterrupts();
    CP_SetDiv32_32(((u32)rx_width) << 8, (u32)dx_width);
    ry_width = y1 - y2;
    dy_width = dy1 - dy2;
    tmp32 = CP_GetDivResult32();
    CP_SetDiv32_32(((u32)ry_width) << 8, (u32)dy_width);
    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    p->xDotSize = (s16)tmp32;
    tmp32 = (s16)(((((s32)(x1 + x2)) << 8) - (dx1 + dx2) * p->xDotSize) >> 7);
    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    p->x0 = (s16)tmp32;
    tmp32 = CP_GetDivResult32();
    OS_RestoreInterrupts(e);
    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        return 1;
    }
    p->yDotSize = (s16)tmp32;
    tmp32 = (s16)(((((s32)(y1 + y2)) << 8) - (dy1 + dy2) * p->yDotSize) >> 7);
    if (tmp32 >= 0x8000 || tmp32 < -0x8000) {
        return 1;
    }
    p->y0 = (s16)tmp32;
    return 0;
}

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
#include "types64.h"
#include "nitro/io_access.h"
typedef int BOOL;

#define R32(a) (*(volatile u32 *)(a))

extern s32 FX_Div(s32 numer, s32 denom);
extern s32 FX_GetDivResult(void);
extern s64 FX_GetDivResultFx64c(void);

static inline s32 FX_Mul32x64c(s32 v32, s64 v64c) {
    s64 tmp = v64c * v32 + 0x80000000LL;
    return (s32)(tmp >> 32);
}

static inline s32 FX_Mul(s32 v1, s32 v2) {
    return (s32)(((s64)v1 * v2 + 0x800LL) >> 12);
}

void G3i_PerspectiveW_(s32 fovySin, s32 fovyCos, s32 aspect, s32 near, s32 far, s32 scale, BOOL load, s32 *mtx) {
    s32 cot, a, m22, m32, t;
    s64 inv;
    volatile u32 *fifo;
    cot = FX_Div(fovyCos, fovySin);
    if (scale != 0x1000) cot = cot * scale / 0x1000;
    IO_W((volatile u64 *)0x04000290, (u64)cot << 32);
    IO_W((volatile u64 *)0x04000298, (u32)aspect);
    if (load) {
        IO_W(&R32(0x04000440), 0);
        fifo = (volatile u32 *)0x04000458;
    }
    if (mtx) {
        mtx[1] = 0;
        mtx[2] = 0;
        mtx[3] = 0;
        mtx[4] = 0;
        mtx[6] = 0;
        mtx[7] = 0;
        mtx[8] = 0;
        mtx[9] = 0;
        mtx[11] = -scale;
        mtx[12] = 0;
        mtx[13] = 0;
        mtx[15] = 0;
    }
    a = FX_GetDivResult();
    IO_W((volatile u64 *)0x04000290, (u64)0x1000 << 32);
    IO_W((volatile u64 *)0x04000298, (u32)(near - far));
    if (load) {
        IO_W(fifo, a);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
        IO_W(fifo, cot);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
    }
    if (mtx) {
        mtx[0] = a;
        mtx[5] = cot;
    }
    inv = FX_GetDivResultFx64c();
    if (scale != 0x1000) inv = inv * scale / 0x1000;
    m22 = FX_Mul32x64c(far + near, inv);
    m32 = FX_Mul32x64c(FX_Mul(near << 1, far), inv);
    if (load) {
        IO_W(fifo, m22);
        IO_W(fifo, -scale);
        IO_W(fifo, 0);
        IO_W(fifo, 0);
        IO_W(fifo, m32);
        IO_W(fifo, 0);
    }
    if (mtx) {
        mtx[10] = m22;
        mtx[14] = m32;
    }
}

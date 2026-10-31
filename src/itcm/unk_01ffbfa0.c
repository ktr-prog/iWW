#include "nitro/mtx.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "nitro/io_access.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0

typedef s32 fx32;
typedef s16 fx16;
typedef s64 fx64;
typedef s64 fx64c;

#define FX32_SHIFT 12
#define FX32_ONE ((fx32)0x00001000L)
#define FX64C_SHIFT 20

typedef struct VecFx32 { fx32 x, y, z; } VecFx32;
typedef struct VecFx16 { fx16 x, y, z; } VecFx16;
typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;
typedef struct MtxFx44 {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

#define reg_CP_DIVCNT      (*(vu16 *)0x04000280)
#define reg_CP_DIV_NUMER   (*(vu64 *)0x04000290)
#define reg_CP_DIV_NUMER_L (*(vu32 *)0x04000290)
#define reg_CP_DIV_DENOM   (*(vu64 *)0x04000298)
#define reg_CP_DIV_RESULT  (*(vu64 *)0x040002a0)
#define reg_CP_DIV_RESULT_L (*(vu32 *)0x040002a0)
#define reg_CP_DIVREM_RESULT_L (*(vu32 *)0x040002a8)
#define reg_CP_SQRTCNT     (*(vu16 *)0x040002b0)
#define reg_CP_SQRT_RESULT (*(vu32 *)0x040002b4)
#define reg_CP_SQRT_PARAM  (*(vu64 *)0x040002b8)

#define CP_DIV_32_32_MODE 0
#define CP_DIV_64_32_MODE 1
#define CP_DIV_64_64_MODE 2
#define CP_DIV_BUSY       0x8000
#define CP_SQRT_32_MODE   0
#define CP_SQRT_64_MODE   1
#define CP_SQRT_BUSY      0x8000

static inline fx32 FX_Mul(fx32 v1, fx32 v2) {
    return (fx32)(((fx64)v1 * v2 + 0x800LL) >> FX32_SHIFT);
}

static inline fx32 FX_Mul32x64c(fx64c v64c, fx32 v32) {
    return (fx32)(((fx64c)v32 * v64c + 0x80000LL) >> FX64C_SHIFT);
}

static inline void CP_SetDiv32_32(u32 numer, u32 denom) {
    IO_W(&reg_CP_DIVCNT, CP_DIV_32_32_MODE);
    IO_W(&reg_CP_DIV_NUMER_L, numer);
    IO_W(&reg_CP_DIV_DENOM, (u64)denom);
}

static inline void CP_SetDiv64_32(u64 numer, u32 denom) {
    IO_W(&reg_CP_DIVCNT, CP_DIV_64_32_MODE);
    IO_W(&reg_CP_DIV_NUMER, numer);
    IO_W(&reg_CP_DIV_DENOM, (u64)denom);
}

static inline void CP_SetDiv64_64(u64 numer, u64 denom) {
    IO_W(&reg_CP_DIVCNT, CP_DIV_64_64_MODE);
    IO_W(&reg_CP_DIV_NUMER, numer);
    IO_W(&reg_CP_DIV_DENOM, denom);
}

static inline void CP_WaitDiv(void) {
    while (IO_R(&reg_CP_DIVCNT) & CP_DIV_BUSY) {
    }
}

static inline u32 CP_GetDivResult32(void) {
    CP_WaitDiv();
    return (u32)IO_R(&reg_CP_DIV_RESULT_L);
}

static inline u32 CP_GetDivRemResult32(void) {
    CP_WaitDiv();
    return (u32)IO_R(&reg_CP_DIVREM_RESULT_L);
}

static inline u64 CP_GetDivResult64(void) {
    CP_WaitDiv();
    return IO_R(&reg_CP_DIV_RESULT);
}

static inline void CP_SetSqrt64(u64 param) {
    IO_W(&reg_CP_SQRTCNT, CP_SQRT_64_MODE);
    IO_W(&reg_CP_SQRT_PARAM, param);
}

static inline void CP_WaitSqrt(void) {
    while (IO_R(&reg_CP_SQRTCNT) & CP_SQRT_BUSY) {
    }
}

static inline u32 CP_GetSqrtResult32(void) {
    CP_WaitSqrt();
    return IO_R(&reg_CP_SQRT_RESULT);
}

/* PROTOS */
fx64c FX_GetDivResultFx64c(void);
fx32 FX_GetDivResult(void);
void FX_InvAsync(fx32 x);
void func_01ffc3d8(fx32 x);
fx32 FX_GetSqrtResult(void);
void FX_DivAsync(fx32 numer, fx32 denom);
fx32 FX_DivS32(fx32 numer, fx32 denom);
fx32 FX_ModS32(fx32 numer, fx32 denom);
void MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab);

/* END PROTOS */

fx64c FX_GetDivResultFx64c(void) {
    return (fx64c)CP_GetDivResult64();
}

fx32 FX_GetDivResult(void) {
    return (fx32)((CP_GetDivResult64() + 0x80000) >> 20);
}

void FX_InvAsync(fx32 x) {
    CP_SetDiv64_32((u64)FX32_ONE << 32, (u32)x);
}

void func_01ffc3d8(fx32 x) {
    if (x > 0) {
        CP_SetSqrt64((u64)x << 32);
    } else {
        CP_SetSqrt64(0);
    }
}

fx32 FX_GetSqrtResult(void) {
    return (fx32)((CP_GetSqrtResult32() + 0x200) >> 10);
}

void FX_DivAsync(fx32 numer, fx32 denom) {
    CP_SetDiv64_32((u64)numer << 32, (u32)denom);
}

fx32 FX_DivS32(fx32 numer, fx32 denom) {
    CP_SetDiv32_32((u32)numer, (u32)denom);
    return (fx32)CP_GetDivResult32();
}

fx32 FX_ModS32(fx32 numer, fx32 denom) {
    CP_SetDiv32_32((u32)numer, (u32)denom);
    return (fx32)CP_GetDivRemResult32();
}

void MTX_Concat44(const MtxFx44 *a, const MtxFx44 *b, MtxFx44 *ab) {
    MtxFx44 tmp;
    MtxFx44 *p = ab;
    fx32 x, y, z, w;
    fx32 c0, c1, c2, c3;
    if (ab == b) {
        p = &tmp;
    }
    x = a->_00; y = a->_01; z = a->_02; w = a->_03;
    p->_00 = (fx32)(((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20 + (fx64)w * b->_30) >> FX32_SHIFT);
    p->_01 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21 + (fx64)w * b->_31) >> FX32_SHIFT);
    p->_03 = (fx32)(((fx64)x * b->_03 + (fx64)y * b->_13 + (fx64)z * b->_23 + (fx64)w * b->_33) >> FX32_SHIFT);
    c0 = b->_02; c1 = b->_12; c2 = b->_22; c3 = b->_32;
    p->_02 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2 + (fx64)w * c3) >> FX32_SHIFT);
    x = a->_10; y = a->_11; z = a->_12; w = a->_13;
    p->_12 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2 + (fx64)w * c3) >> FX32_SHIFT);
    p->_11 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21 + (fx64)w * b->_31) >> FX32_SHIFT);
    p->_13 = (fx32)(((fx64)x * b->_03 + (fx64)y * b->_13 + (fx64)z * b->_23 + (fx64)w * b->_33) >> FX32_SHIFT);
    c0 = b->_00; c1 = b->_10; c2 = b->_20; c3 = b->_30;
    p->_10 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2 + (fx64)w * c3) >> FX32_SHIFT);
    x = a->_20; y = a->_21; z = a->_22; w = a->_23;
    p->_20 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2 + (fx64)w * c3) >> FX32_SHIFT);
    p->_21 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21 + (fx64)w * b->_31) >> FX32_SHIFT);
    p->_23 = (fx32)(((fx64)x * b->_03 + (fx64)y * b->_13 + (fx64)z * b->_23 + (fx64)w * b->_33) >> FX32_SHIFT);
    c0 = b->_02; c1 = b->_12; c2 = b->_22; c3 = b->_32;
    p->_22 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2 + (fx64)w * c3) >> FX32_SHIFT);
    x = a->_30; y = a->_31; z = a->_32; w = a->_33;
    p->_32 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2 + (fx64)w * c3) >> FX32_SHIFT);
    p->_31 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21 + (fx64)w * b->_31) >> FX32_SHIFT);
    p->_30 = (fx32)(((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20 + (fx64)w * b->_30) >> FX32_SHIFT);
    p->_33 = (fx32)(((fx64)x * b->_03 + (fx64)y * b->_13 + (fx64)z * b->_23 + (fx64)w * b->_33) >> FX32_SHIFT);
    if (p == &tmp) {
        *ab = tmp;
    }
}


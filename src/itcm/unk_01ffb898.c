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
void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab);
void MTX_MultVec43(const VecFx32 *pSrc, const MtxFx43 *pMtx, VecFx32 *pDst);

/* END PROTOS */

void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *ab) {
    MtxFx43 tmp;
    MtxFx43 *p = ab;
    fx32 x, y, z;
    fx32 c0, c1, c2;
    if (ab == b) {
        p = &tmp;
    }
    x = a->_00; y = a->_01; z = a->_02;
    p->_00 = (fx32)(((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20) >> FX32_SHIFT);
    p->_01 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> FX32_SHIFT);
    c0 = b->_02; c1 = b->_12; c2 = b->_22;
    p->_02 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2) >> FX32_SHIFT);
    x = a->_10; y = a->_11; z = a->_12;
    p->_12 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2) >> FX32_SHIFT);
    p->_11 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> FX32_SHIFT);
    c0 = b->_00; c1 = b->_10; c2 = b->_20;
    p->_10 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2) >> FX32_SHIFT);
    x = a->_20; y = a->_21; z = a->_22;
    p->_20 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2) >> FX32_SHIFT);
    p->_21 = (fx32)(((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> FX32_SHIFT);
    c0 = b->_02; c1 = b->_12; c2 = b->_22;
    p->_22 = (fx32)(((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2) >> FX32_SHIFT);
    x = a->_30; y = a->_31; z = a->_32;
    p->_32 = (fx32)((((fx64)x * c0 + (fx64)y * c1 + (fx64)z * c2) >> FX32_SHIFT) + b->_32);
    p->_31 = (fx32)((((fx64)x * b->_01 + (fx64)y * b->_11 + (fx64)z * b->_21) >> FX32_SHIFT) + b->_31);
    p->_30 = (fx32)((((fx64)x * b->_00 + (fx64)y * b->_10 + (fx64)z * b->_20) >> FX32_SHIFT) + b->_30);
    if (p == &tmp) {
        *ab = tmp;
    }
}

void MTX_MultVec43(const VecFx32 *pSrc, const MtxFx43 *pMtx, VecFx32 *pDst) {
    fx32 x = pSrc->x;
    fx32 y = pSrc->y;
    fx32 z = pSrc->z;
    pDst->x = (fx32)(((fx64)x * pMtx->_00 + (fx64)y * pMtx->_10 + (fx64)z * pMtx->_20) >> FX32_SHIFT);
    pDst->x += pMtx->_30;
    pDst->y = (fx32)(((fx64)x * pMtx->_01 + (fx64)y * pMtx->_11 + (fx64)z * pMtx->_21) >> FX32_SHIFT);
    pDst->y += pMtx->_31;
    pDst->z = (fx32)(((fx64)x * pMtx->_02 + (fx64)y * pMtx->_12 + (fx64)z * pMtx->_22) >> FX32_SHIFT);
    pDst->z += pMtx->_32;
}


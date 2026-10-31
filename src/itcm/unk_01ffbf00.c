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

extern void MTX_ScaleApply33(const MtxFx33 *pSrc, MtxFx33 *pDst, fx32 x, fx32 y, fx32 z);
/* PROTOS */
void MTX_ScaleApply43(const MtxFx43 *pSrc, MtxFx43 *pDst, fx32 x, fx32 y, fx32 z);

/* END PROTOS */

void MTX_ScaleApply43(const MtxFx43 *pSrc, MtxFx43 *pDst, fx32 x, fx32 y, fx32 z) {
    MTX_ScaleApply33((const MtxFx33 *)pSrc, (MtxFx33 *)pDst, x, y, z);
    pDst->_30 = pSrc->_30;
    pDst->_31 = pSrc->_31;
    pDst->_32 = pSrc->_32;
}


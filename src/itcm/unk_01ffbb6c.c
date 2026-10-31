typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef s32 fx32;
typedef s64 fx64;

#define FX32_SHIFT 12
#define FX32_ONE ((fx32)0x00001000L)

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

void MI_Copy48B(void *src, void *dst);
void FX_InvAsync(fx32 x);
fx32 FX_GetDivResult(void);

int MTX_Inverse43(const MtxFx43 *pSrc, MtxFx43 *pDst) {
    MtxFx43 tmp;
    MtxFx43 *p;
    fx32 det0, det1, det2, det;
    fx32 var0, var1, var2, var3;
    fx64 inv;
    if (pSrc == pDst) {
        p = &tmp;
    } else {
        p = pDst;
    }
    det0 = (fx32)(((fx64)pSrc->_11 * pSrc->_22 - (fx64)pSrc->_12 * pSrc->_21 + (fx64)(FX32_ONE >> 1)) >> FX32_SHIFT);
    det1 = (fx32)(((fx64)pSrc->_10 * pSrc->_22 - (fx64)pSrc->_12 * pSrc->_20 + (fx64)(FX32_ONE >> 1)) >> FX32_SHIFT);
    det2 = (fx32)(((fx64)pSrc->_10 * pSrc->_21 - (fx64)pSrc->_11 * pSrc->_20 + (fx64)(FX32_ONE >> 1)) >> FX32_SHIFT);
    det = (fx32)(((fx64)pSrc->_00 * det0 - (fx64)pSrc->_01 * det1 + (fx64)pSrc->_02 * det2 + (fx64)(FX32_ONE >> 1)) >> FX32_SHIFT);
    if (det == 0) {
        return -1;
    }
    FX_InvAsync(det);
    var0 = (fx32)(((fx64)pSrc->_01 * pSrc->_22 - (fx64)pSrc->_21 * pSrc->_02) >> FX32_SHIFT);
    var1 = (fx32)(((fx64)pSrc->_01 * pSrc->_12 - (fx64)pSrc->_11 * pSrc->_02) >> FX32_SHIFT);
    var2 = (fx32)(((fx64)pSrc->_00 * pSrc->_22 - (fx64)pSrc->_20 * pSrc->_02) >> FX32_SHIFT);
    var3 = (fx32)(((fx64)pSrc->_00 * pSrc->_12 - (fx64)pSrc->_10 * pSrc->_02) >> FX32_SHIFT);
    inv = FX_GetDivResult();
    p->_00 = (fx32)((inv * det0) >> FX32_SHIFT);
    p->_01 = -(fx32)((inv * var0) >> FX32_SHIFT);
    p->_02 = (fx32)((inv * var1) >> FX32_SHIFT);
    p->_10 = -(fx32)((inv * det1) >> FX32_SHIFT);
    p->_11 = (fx32)((inv * var2) >> FX32_SHIFT);
    p->_12 = -(fx32)((inv * var3) >> FX32_SHIFT);
    p->_20 = (fx32)((inv * det2) >> FX32_SHIFT);
    p->_21 = -(fx32)((inv * (fx32)(((fx64)pSrc->_00 * pSrc->_21 - (fx64)pSrc->_20 * pSrc->_01) >> FX32_SHIFT)) >> FX32_SHIFT);
    p->_22 = (fx32)((inv * (fx32)(((fx64)pSrc->_00 * pSrc->_11 - (fx64)pSrc->_10 * pSrc->_01) >> FX32_SHIFT)) >> FX32_SHIFT);
    p->_30 = -(fx32)(((fx64)p->_00 * pSrc->_30 + (fx64)p->_10 * pSrc->_31 + (fx64)p->_20 * pSrc->_32) >> FX32_SHIFT);
    p->_31 = -(fx32)(((fx64)p->_01 * pSrc->_30 + (fx64)p->_11 * pSrc->_31 + (fx64)p->_21 * pSrc->_32) >> FX32_SHIFT);
    p->_32 = -(fx32)(((fx64)p->_02 * pSrc->_30 + (fx64)p->_12 * pSrc->_31 + (fx64)p->_22 * pSrc->_32) >> FX32_SHIFT);
    if (p == &tmp) {
        MI_Copy48B(&tmp, pDst);
    }
    return 0;
}

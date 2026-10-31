#include "types.h"
#include "gfx/VecFx32.h"
#include "game/FxVec3.h"
#include "nitro/io_access.h"

typedef volatile u64 vu64;

extern "C" {
void VEC_Normalize(const VecFx32 *pSrc, VecFx32 *pDst);
void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
s32 FX_Div(s32 a, s32 b);
s32 Math_Sqrt64(u64 x);
void Math_InitSqrt64(void);
void Vec_NormalizeCopy(VecFx32 *out, VecFx32 *in);
extern const s16 data_02135f44[];
}

static inline s32 FX_Mul(s32 a, s32 b) {
    return (s32)(((s64)a * b + 0x800) >> 12);
}

#define FX_SinIdx(a) data_02135f44[((a) >> 4) * 2]
#define FX_CosIdx(a) data_02135f44[((a) >> 4) * 2 + 1]

extern "C" s32 Math_Sqrt64(u64 x) {
    IO_W((vu16 *)0x040002b0, 1);
    IO_W((vu64 *)0x040002b8, x << 2);
    while (IO_R((vu16 *)0x040002b0) & 0x8000) {
    }
    return ((s32)IO_R((vu32 *)0x040002b4) + 1) >> 1;
}

extern "C" void Math_InitSqrt64(void) {
    IO_W((vu16 *)0x040002b0, 1);
}

extern "C" void Vec_Sub(VecFx32 *out, VecFx32 *a, VecFx32 *b) {
    s32 ax = a->x;
    s32 bx = b->x;
    s32 az = a->z;
    s32 bz = b->z;
    s32 ay = a->y;
    s32 by = b->y;
    out->x = ax - bx;
    out->y = ay - by;
    out->z = az - bz;
}

extern "C" void Vec_ScaleTo(VecFx32 *out, VecFx32 *in, s32 s) {
    s32 x = in->x;
    s32 y = in->y;
    s32 z = in->z;
    s32 rz = FX_Mul(z, s);
    s32 ry = FX_Mul(y, s);
    s32 rx = FX_Mul(x, s);
    out->x = rx;
    out->y = ry;
    out->z = rz;
}

extern "C" void Vec_Scale(VecFx32 *v, s32 s) {
    v->x = FX_Mul(v->x, s);
    v->y = FX_Mul(v->y, s);
    v->z = FX_Mul(v->z, s);
}

extern "C" void Vec_DivScalar(VecFx32 *v, s32 d) {
    if (d == 0) {
        if (v->x > 0) v->x = 0x7fffffff;
        else if (v->x < 0) v->x = 0x80000000;
        if (v->y > 0) v->y = 0x7fffffff;
        else if (v->y < 0) v->y = 0x80000000;
        if (v->z > 0) v->z = 0x7fffffff;
        else if (v->z < 0) v->z = 0x80000000;
    } else {
        v->x = FX_Div(v->x, d);
        v->y = FX_Div(v->y, d);
        v->z = FX_Div(v->z, d);
    }
}

extern "C" void Vec_ShiftRightTo(VecFx32 *out, VecFx32 *in, s32 n) {
    s32 x = in->x;
    s32 y = in->y;
    s32 z = in->z;
    out->x = x >> n;
    out->y = y >> n;
    out->z = z >> n;
}

extern "C" void Vec_ShiftRight(VecFx32 *v, s32 n) {
    v->x >>= n;
    v->y >>= n;
    v->z >>= n;
}

extern "C" s32 Vec_Equal(VecFx32 *a, VecFx32 *b) {
    if (a->x == b->x && a->y == b->y && a->z == b->z) return 1;
    return 0;
}

extern "C" s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b) {
    if (a->x != b->x || a->y != b->y || a->z != b->z) return 1;
    return 0;
}

extern "C" s32 Vec_Distance(VecFx32 *a, VecFx32 *b) {
    s32 dx = a->x - b->x;
    s64 sq = (s64)dx * dx;
    s32 dy = a->y - b->y;
    sq += (s64)dy * dy;
    s32 dz = a->z - b->z;
    sq += (s64)dz * dz;
    return Math_Sqrt64(sq);
}

extern "C" s32 Vec_MagXZ(VecFx32 *v) {
    s32 x = v->x;
    s32 z = v->z;
    s64 sq = (s64)x * x + (s64)z * z;
    return Math_Sqrt64(sq);
}

extern "C" s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b) {
    s32 dx = a->x - b->x;
    s32 dz = a->z - b->z;
    s64 sq = (s64)dx * dx + (s64)dz * dz;
    return Math_Sqrt64(sq);
}

extern "C" s64 Vec_MagSqXZ(VecFx32 *v) {
    s32 x = v->x;
    s32 z = v->z;
    return ((s64)x * x + (s64)z * z) >> 12;
}

extern "C" s64 Vec_DistSqXZ(VecFx32 *a, VecFx32 *b) {
    s32 dx = a->x - b->x;
    s32 dz = a->z - b->z;
    return ((s64)dx * dx + (s64)dz * dz) >> 12;
}

extern "C" s32 Vec_DotXZ(VecFx32 *a, VecFx32 *b) {
    return (s32)(((s64)a->x * b->x + (s64)a->z * b->z) >> 12);
}

extern "C" void Vec_CrossCopy(VecFx32 *out, VecFx32 *in, VecFx32 *a, VecFx32 *b) {
    VEC_CrossProduct(a, b, in);
    *out = *in;
}

extern "C" void Vec_NormalizeCopy(VecFx32 *out, VecFx32 *in) {
    VEC_Normalize(in, in);
    *out = *in;
}

extern "C" s32 Vec_SafeNormalize(VecFx32 *v) {
    VecFx32 t;
    if (v->x == 0 && v->y == 0 && v->z == 0) return 0;
    Vec_NormalizeCopy(&t, v);
    return 1;
}

extern "C" void Vec_RotateX(VecFx32 *v, s32 angle) {
    s32 s = FX_SinIdx((u16)angle);
    s32 c = FX_CosIdx((u16)angle);
    s32 y = v->y;
    s32 z = v->z;
    v->y = FX_Mul(c, y) - FX_Mul(s, z);
    v->z = FX_Mul(s, y) + FX_Mul(c, z);
}

extern "C" void Vec_RotateY(VecFx32 *v, s32 angle) {
    s32 c = FX_CosIdx((u16)angle);
    s32 s = FX_SinIdx((u16)angle);
    s32 z = v->z;
    s32 x = v->x;
    v->x = FX_Mul(c, x) + FX_Mul(s, z);
    v->z = FX_Mul(c, z) - FX_Mul(s, x);
}

extern "C" void Vec_RotateZ(VecFx32 *v, s32 angle) {
    s32 s = FX_SinIdx((u16)angle);
    s32 c = FX_CosIdx((u16)angle);
    s32 x = v->x;
    s32 y = v->y;
    v->x = FX_Mul(c, x) - FX_Mul(s, y);
    v->y = FX_Mul(s, x) + FX_Mul(c, y);
}

FxVec3 gVec3Zero(0, 0, 0);

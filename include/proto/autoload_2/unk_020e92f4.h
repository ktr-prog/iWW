#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_020E92F4_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_020E92F4_H


#include "types.h"
#include "types64.h"
#ifdef __cplusplus
#include "game/FxVec3.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Math_Sqrt64
s32 Math_Sqrt64(u64 x);
#endif
#ifndef PROTO_LOCAL_Math_InitSqrt64
void Math_InitSqrt64(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Vec_Sub
void Vec_Sub(VecFx32 *out, VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_ScaleTo
void Vec_ScaleTo(VecFx32 *out, VecFx32 *in, s32 s);
#endif
#ifndef PROTO_LOCAL_Vec_Scale
void Vec_Scale(VecFx32 *v, s32 s);
#endif
#ifndef PROTO_LOCAL_Vec_DivScalar
void Vec_DivScalar(VecFx32 *v, s32 d);
#endif
#ifndef PROTO_LOCAL_Vec_ShiftRightTo
void Vec_ShiftRightTo(VecFx32 *out, VecFx32 *in, s32 n);
#endif
#ifndef PROTO_LOCAL_Vec_ShiftRight
void Vec_ShiftRight(VecFx32 *v, s32 n);
#endif
#ifndef PROTO_LOCAL_Vec_Equal
s32 Vec_Equal(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_NotEqual
s32 Vec_NotEqual(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_Distance
s32 Vec_Distance(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_MagXZ
s32 Vec_MagXZ(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Vec_DistXZ
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_MagSqXZ
s64 Vec_MagSqXZ(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Vec_DistSqXZ
s64 Vec_DistSqXZ(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_DotXZ
s32 Vec_DotXZ(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_CrossCopy
void Vec_CrossCopy(VecFx32 *out, VecFx32 *in, VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Vec_NormalizeCopy
void Vec_NormalizeCopy(VecFx32 *out, VecFx32 *in);
#endif
#ifndef PROTO_LOCAL_Vec_SafeNormalize
s32 Vec_SafeNormalize(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Vec_RotateX
void Vec_RotateX(VecFx32 *v, s32 angle);
#endif
#ifndef PROTO_LOCAL_Vec_RotateY
void Vec_RotateY(VecFx32 *v, s32 angle);
#endif
#ifndef PROTO_LOCAL_Vec_RotateZ
void Vec_RotateZ(VecFx32 *v, s32 angle);
#endif
}
#ifndef PROTO_LOCAL_gVec3Zero
extern FxVec3 gVec3Zero;
#endif
#endif

#endif

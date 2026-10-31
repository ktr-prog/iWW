#ifndef PROTO_PROTO_MAIN_UNK_020B6B44_H
#define PROTO_PROTO_MAIN_UNK_020B6B44_H


#include "types.h"
#ifdef __cplusplus
#include "game/Basis.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TouchPick_HitCylinder
BOOL TouchPick_HitCylinder(VecFx32 *p, VecFx32 *q, VecFx32 *r, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_TouchPick_CalcRay
void TouchPick_CalcRay(Basis *out, s32 x, s32 z);
#endif
}
#endif

#endif

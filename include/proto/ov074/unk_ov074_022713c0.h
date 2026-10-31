#ifndef PROTO_PROTO_OV074_UNK_OV074_022713C0_H
#define PROTO_PROTO_OV074_UNK_OV074_022713C0_H


#include "types.h"
#ifdef __cplusplus
#include "game/FxVec3.h"
#include "gfx/VecFx32.h"
class SpNpcBlanca;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcBlanca_Create
SpNpcBlanca *SpNpcBlanca_Create();
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_ChangeAct
void SpNpcBlanca_ChangeAct(SpNpcBlanca *self, s32 state);
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_IsInFocusBox
s32 SpNpcBlanca_IsInFocusBox(SpNpcBlanca *self, VecFx32 *pa, VecFx32 *pb);
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_IsInCameraBox
s32 SpNpcBlanca_IsInCameraBox(SpNpcBlanca *self);
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_PickWanderTarget
s32 SpNpcBlanca_PickWanderTarget(SpNpcBlanca *self, s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_FindSidestepPos
s32 SpNpcBlanca_FindSidestepPos(SpNpcBlanca *self, VecFx32 *o, FxVec3 *offset);
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_SteerAroundObstacle
s32 SpNpcBlanca_SteerAroundObstacle(SpNpcBlanca *self);
#endif
#ifndef PROTO_LOCAL_SpNpcBlanca_TryAvoidObstacle
BOOL SpNpcBlanca_TryAvoidObstacle(SpNpcBlanca *self);
#endif
}
#endif

#endif

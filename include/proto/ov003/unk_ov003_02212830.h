#ifndef PROTO_PROTO_OV003_UNK_OV003_02212830_H
#define PROTO_PROTO_OV003_UNK_OV003_02212830_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "field/Snowball.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Snowball_Create
void *Snowball_Create();
#endif
#ifndef PROTO_LOCAL_Snowball_GetMinRadius
s32 Snowball_GetMinRadius();
#endif
#ifndef PROTO_LOCAL_Snowball_GetMaxRadius
s32 Snowball_GetMaxRadius();
#endif
#ifndef PROTO_LOCAL_Snowball_DropDisplacedItem
BOOL Snowball_DropDisplacedItem(u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Snowball_UpdateMatrix
void Snowball_UpdateMatrix(Snowball *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Snowball_UpdateCarry
void Snowball_UpdateCarry(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_UpdateRolling
void Snowball_UpdateRolling(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_TrySetPos
BOOL Snowball_TrySetPos(Snowball *o, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Snowball_GetRadius
s32 Snowball_GetRadius(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_Break
s32 Snowball_Break(Snowball *o, s32 a);
#endif
#ifndef PROTO_LOCAL_Snowball_TryPush
BOOL Snowball_TryPush(Snowball *o, VecFx32 *outPos, s16 *outAng, s32 *outVal, s32 speed, s32 ang);
#endif
#ifndef PROTO_LOCAL_Snowball_IsInBallState
BOOL Snowball_IsInBallState(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_IsLooseBall
BOOL Snowball_IsLooseBall(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_IsSnowmanPart
BOOL Snowball_IsSnowmanPart(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_IsSnowmanHead
BOOL Snowball_IsSnowmanHead(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_IsSnowmanBody
BOOL Snowball_IsSnowmanBody(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_InitState
void Snowball_InitState(Snowball *o);
#endif
#ifndef PROTO_LOCAL_Snowball_CanBuildSnowmanAt
BOOL Snowball_CanBuildSnowmanAt(VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_Snowball_PlaceSnowmanAt
BOOL Snowball_PlaceSnowmanAt(u32 a, VecFx32 *pos, u16 *out);
#endif
#ifndef PROTO_LOCAL_Snowball_PlaceSnowmanNearby
BOOL Snowball_PlaceSnowmanNearby(u32 a, VecFx32 *pos, u16 *out);
#endif
#ifndef PROTO_LOCAL_Snowball_ClearItemAt
BOOL Snowball_ClearItemAt(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_sSnowballProfile
extern ActorProfile sSnowballProfile;
#endif
#ifndef PROTO_LOCAL_Snowball_ChangeState
BOOL Snowball_ChangeState(Snowball *o, s32 st);
#endif
#ifndef PROTO_LOCAL_Snowball_RunState
void Snowball_RunState(Snowball *o);
#endif
}
#endif

#endif

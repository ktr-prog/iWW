#ifndef PROTO_PROTO_OV004_UNK_OV004_02204F24_H
#define PROTO_PROTO_OV004_UNK_OV004_02204F24_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/ModelSlotPool.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
class FtrActor;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FtrActor_Create
void *FtrActor_Create();
#endif
#ifndef PROTO_LOCAL_FtrActor_IsLightKind1
u32 FtrActor_IsLightKind1(u32 a);
#endif
#ifndef PROTO_LOCAL_FtrActor_TurnOnRoomLight
void FtrActor_TurnOnRoomLight(u32 a);
#endif
#ifndef PROTO_LOCAL_FtrActor_MakeSpawnArg
u32 FtrActor_MakeSpawnArg(u32 a, u32 b, u32 c, u32 d, u8 f, u32 e);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetArgFtrIndex
u32 FtrActor_GetArgFtrIndex(u32 v);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetArgMode
u32 FtrActor_GetArgMode(u32 v);
#endif
#ifndef PROTO_LOCAL_FtrActor_TestPlayerUnk
BOOL FtrActor_TestPlayerUnk();
#endif
#ifndef PROTO_LOCAL_FtrActor_AngleToDir
u32 FtrActor_AngleToDir(s32 v);
#endif
#ifndef PROTO_LOCAL_FtrActor_TestSceneUnk
s32 FtrActor_TestSceneUnk(s32 a);
#endif
#ifndef PROTO_LOCAL_FtrActor_TestCurSceneUnk
s32 FtrActor_TestCurSceneUnk();
#endif
#ifndef PROTO_LOCAL_FtrActor_GetDragSe
s32 FtrActor_GetDragSe(void);
#endif
#ifndef PROTO_LOCAL_FtrGlowMat_GetBaseEmission
u16 FtrGlowMat_GetBaseEmission();
#endif
#ifndef PROTO_LOCAL_FtrVisNodes_Construct
void FtrVisNodes_Construct(void *);
#endif
#ifndef PROTO_LOCAL_FtrVisNodes_Destruct
void FtrVisNodes_Destruct(void *);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_FtrActor_MatCallback
void FtrActor_MatCallback(NNSG3dRS *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_NodeDescCallbackA
void FtrActor_NodeDescCallbackA(NNSG3dRS *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_NodeDescCallbackB
void FtrActor_NodeDescCallbackB(NNSG3dRS *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_NodeCallback
void FtrActor_NodeCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_FtrActor_SetModelCallbacks
void FtrActor_SetModelCallbacks(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_FtrActor_IsLightSource
BOOL FtrActor_IsLightSource(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrActor_IsStereo
BOOL FtrActor_IsStereo(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrActor_PlayAnimsFromLastFrame
void FtrActor_PlayAnimsFromLastFrame(FtrActor *self, u32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_FtrActor_StepAnims
BOOL FtrActor_StepAnims(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetHeap
ModelSlot *FtrActor_GetHeap(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_LocalToWorld
void FtrActor_LocalToWorld(FtrActor *self, VecFx32 *out, VecFx32 *src);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetCorner
void FtrActor_GetCorner(FtrActor *self, VecFx32 *out, s32 i);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetCenter
void FtrActor_GetCenter(FtrActor *self, VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_FtrActor_IsWithinDist
BOOL FtrActor_IsWithinDist(VecFx32 *pos, s32 a, VecFx32 *p, s32 b);
#endif
#ifndef PROTO_LOCAL_FtrActor_IsPosClearOfCharacters
BOOL FtrActor_IsPosClearOfCharacters(VecFx32 *pos, s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetParent
FtrActor *FtrActor_GetParent(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetFtrIndex
s32 FtrActor_GetFtrIndex(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_RequestToggle
BOOL FtrActor_RequestToggle(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetLayer
u8 FtrActor_GetLayer(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_CalcWorldMtx
void FtrActor_CalcWorldMtx(FtrActor *self, VecFx32 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_FtrActor_UpdateMtx
void FtrActor_UpdateMtx(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetBoxSize
void FtrActor_GetBoxSize(FtrActor *self, VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_FtrActor_InitCollider
void FtrActor_InitCollider(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_ReleaseCollider
void FtrActor_ReleaseCollider(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_UpdateBox
void FtrActor_UpdateBox(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_UpdateTopItemBoxes
void FtrActor_UpdateTopItemBoxes(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_SetInitialAct
void FtrActor_SetInitialAct(FtrActor *self);
#endif
#ifndef PROTO_LOCAL_FtrActor_MakeItemForAngle
void FtrActor_MakeItemForAngle(u16 *out, FtrActor *obj, s32 ang);
#endif
#ifndef PROTO_LOCAL_FtrActor_SpawnActorC0
void FtrActor_SpawnActorC0(VecFx32 *a, u32 x);
#endif
#ifndef PROTO_LOCAL_FtrActor_PredIsLightSource
s32 FtrActor_PredIsLightSource(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrActor_PredIsStereo
s32 FtrActor_PredIsStereo(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrActor_PredIsSeatOrBed
s32 FtrActor_PredIsSeatOrBed(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrActor_PredIsGyroid
s32 FtrActor_PredIsGyroid(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrActor_GetItemId
void FtrActor_GetItemId(u16 *out, FtrActor *o);
#endif
#ifndef PROTO_LOCAL_FtrStack_CalcRelPlacement
BOOL FtrStack_CalcRelPlacement(s32 *idx, VecFx32 *pos, s16 *ang, s32 x, s32 a, s16 b);
#endif
}
#endif

#endif

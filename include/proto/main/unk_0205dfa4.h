#ifndef PROTO_PROTO_MAIN_UNK_0205DFA4_H
#define PROTO_PROTO_MAIN_UNK_0205DFA4_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#include "gfx/ModelAnim.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/TexVramSlot.h"
#include "gfx/TexVramTask.h"
#include "gfx/TwoLayerAnimModel.h"
#include "player/FishBobber.h"
#include "player/HeldItemModel.h"
#include "sys/Heap.h"
class HeldItemModelBank;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HeldItemModels_Destroy
void HeldItemModels_Destroy(void);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetModelPath
char *HeldItem_GetModelPath(u32 x);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetModelId
s32 HeldItem_GetModelId(u16 *p);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetHandPose
u16 HeldItem_GetHandPose(u16 *p);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetAnimId
s32 HeldItem_GetAnimId(u16 *p);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetModelBufferSize
u32 HeldItem_GetModelBufferSize(void);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetAnimHeapSize
u32 HeldItem_GetAnimHeapSize(void);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetTexVramSize
u32 HeldItem_GetTexVramSize(void);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetTex4x4VramSize
u32 HeldItem_GetTex4x4VramSize(void);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetPlttVramSize
u32 HeldItem_GetPlttVramSize(void);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetAnimPath
char *HeldItem_GetAnimPath(u32 x);
#endif
#ifndef PROTO_LOCAL_HeldItem_GetTexAnimPath
char *HeldItem_GetTexAnimPath(u32 x);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_GetModel
void *HeldItemModel_GetModel(u8 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HeldItemModels_Init
void HeldItemModels_Init(Heap *x);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_AllocVram
void HeldItemModels_AllocVram(HeldItemModelBank *self);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_CreateAnimHeaps
void HeldItemModels_CreateAnimHeaps(HeldItemModelBank *self);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_ReleaseAll
void HeldItemModels_ReleaseAll(HeldItemModelBank *self);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetModelBuffer
void *HeldItemModels_GetModelBuffer(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetAnimHeap
void *HeldItemModels_GetAnimHeap(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetAnimBuffer
void *HeldItemModels_GetAnimBuffer(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_SetAnimBuffer
void HeldItemModels_SetAnimBuffer(HeldItemModelBank *self, u32 idx, void *v, u16 w);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetAnimBufferSize
u32 HeldItemModels_GetAnimBufferSize(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetTexAnimBuffer
void *HeldItemModels_GetTexAnimBuffer(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_SetTexAnimBuffer
void HeldItemModels_SetTexAnimBuffer(HeldItemModelBank *self, u32 idx, void *v, u16 w);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetTexAnimBufferSize
u32 HeldItemModels_GetTexAnimBufferSize(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetMatAnmHeap
void *HeldItemModels_GetMatAnmHeap(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_SetMatAnmHeap
void HeldItemModels_SetMatAnmHeap(HeldItemModelBank *self, u32 idx, void *v);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_LoadAnim
s32 HeldItemModels_LoadAnim(HeldItemModelBank *self, u32 idx, u32 x);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_LoadTexAnim
s32 HeldItemModels_LoadTexAnim(HeldItemModelBank *self, u32 idx, u32 x);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_PlayAnim
void HeldItemModels_PlayAnim(HeldItemModelBank *self, u32 idx, u32 x, u32 y, u8 z);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_PlayTexAnim
void HeldItemModels_PlayTexAnim(HeldItemModelBank *self, u32 idx, u32 x, u32 y);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetVramSlot
TexVramSlot *HeldItemModels_GetVramSlot(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetTexTask
TexVramTask *HeldItemModels_GetTexTask(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetModel
BlendAnimModel *HeldItemModels_GetModel(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_SetTexAnim
void HeldItemModels_SetTexAnim(HeldItemModelBank *self, u32 idx, ModelAnim *v);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetTexAnim
ModelAnim *HeldItemModels_GetTexAnim(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_GetItem
u16 *HeldItemModels_GetItem(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_CancelTexUpload
void HeldItemModels_CancelTexUpload(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_LoadModel
void HeldItemModels_LoadModel(HeldItemModelBank *self, u32 idx, u32 x);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_RelocateTexture
void HeldItemModels_RelocateTexture(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_PollTexUpload
s32 HeldItemModels_PollTexUpload(HeldItemModelBank *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_OnJointCalcPre
void HeldItemModels_OnJointCalcPre(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_HeldItemModels_OnJointCalcPost
void HeldItemModels_OnJointCalcPost(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_Setup
void HeldItemModel_Setup(HeldItemModel *o, u32 id, Character *x, u16 *code, void *a5, s32 flag);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_Release
void HeldItemModel_Release(HeldItemModel *o);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_SetItem
void HeldItemModel_SetItem(HeldItemModel *o, u16 *code, void *c);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_PlayAnim
void HeldItemModel_PlayAnim(HeldItemModel *o, s32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_SetAnimSpeed
void HeldItemModel_SetAnimSpeed(HeldItemModel *o, u32 v);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_Update
void HeldItemModel_Update(HeldItemModel *o);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_Draw
void HeldItemModel_Draw(HeldItemModel *o, Mtx43 *src);
#endif
#ifndef PROTO_LOCAL_HeldItemModel_GetJointMtx
void HeldItemModel_GetJointMtx(Mtx43 *out, HeldItemModel *o, u32 a);
#endif
}
#ifndef PROTO_LOCAL_sHeldItemModelPathBuf
extern char sHeldItemModelPathBuf[0x18];
#endif
#ifndef PROTO_LOCAL_sHeldItemAnimPathBuf
extern char sHeldItemAnimPathBuf[0x18];
#endif
#ifndef PROTO_LOCAL_sHeldItemTexAnimPathBuf
extern char sHeldItemTexAnimPathBuf[0x1c];
#endif
#ifndef PROTO_LOCAL_sHeldItemModelBank
extern HeldItemModelBank sHeldItemModelBank;
#endif
#endif

#endif

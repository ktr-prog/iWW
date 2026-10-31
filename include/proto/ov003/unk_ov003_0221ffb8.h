#ifndef PROTO_PROTO_OV003_UNK_OV003_0221FFB8_H
#define PROTO_PROTO_OV003_UNK_OV003_0221FFB8_H


#include "types.h"
#include "sys/ProcProfile.h"
struct BottleThrowStateEntry;
struct FishAiStateEntry;
struct FishBiteStateEntry;
struct FishBiteWindow;
struct FishCatch;
struct FishCatchStateEntry;
struct FishMoveStateEntry;
struct FishRodParams;
struct FishShadowStateEntry;
struct FishSight;
#ifndef __cplusplus
typedef struct BottleThrowStateEntry BottleThrowStateEntry;
typedef struct FishAiStateEntry FishAiStateEntry;
typedef struct FishBiteStateEntry FishBiteStateEntry;
typedef struct FishBiteWindow FishBiteWindow;
typedef struct FishCatch FishCatch;
typedef struct FishCatchStateEntry FishCatchStateEntry;
typedef struct FishMoveStateEntry FishMoveStateEntry;
typedef struct FishRodParams FishRodParams;
typedef struct FishShadowStateEntry FishShadowStateEntry;
typedef struct FishSight FishSight;
#endif
#ifdef __cplusplus
#include "field/BottleThrow.h"
#include "field/FishShadow.h"
#include "gfx/ModelSlotPool.h"
#include "gfx/VecFx32.h"
class BottleThrowStateOwner;
class FishFinModel;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov003_02257a7c
extern void *data_ov003_02257a7c;
#endif
#ifndef PROTO_LOCAL_sFishShadowAnimPath
extern char *sFishShadowAnimPath;
#endif
#ifndef PROTO_LOCAL_sFishFinTexAnimPath
extern char *sFishFinTexAnimPath;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234820
extern void *data_ov003_02234820[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347b0
extern void *data_ov003_022347b0[2];
#endif
#ifndef PROTO_LOCAL_sBottleDriftSpeed
extern s32 sBottleDriftSpeed;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234830
extern void *data_ov003_02234830[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234838
extern void *data_ov003_02234838[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234898
extern void *data_ov003_02234898[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022348a0
extern void *data_ov003_022348a0[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022348a8
extern void *data_ov003_022348a8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347a0
extern void *data_ov003_022347a0[2];
#endif
#ifndef PROTO_LOCAL_sBottleSinkStep
extern s32 sBottleSinkStep;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234888
extern void *data_ov003_02234888[2];
#endif
#ifndef PROTO_LOCAL_sFishShadowAnimPathStr
extern char sFishShadowAnimPathStr[];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234870
extern void *data_ov003_02234870[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347c8
extern void *data_ov003_022347c8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234858
extern void *data_ov003_02234858[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234850
extern void *data_ov003_02234850[2];
#endif
#ifndef PROTO_LOCAL_sFishFinAnimPathStr
extern char sFishFinAnimPathStr[];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234798
extern void *data_ov003_02234798[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347b8
extern void *data_ov003_022347b8[2];
#endif
#ifndef PROTO_LOCAL_sFishCastSplashTimer
extern u16 sFishCastSplashTimer;
#endif
#ifndef PROTO_LOCAL_sFishShadowModelPathStr
extern char sFishShadowModelPathStr[];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234790
extern void *data_ov003_02234790[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234800
extern void *data_ov003_02234800[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347f8
extern void *data_ov003_022347f8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234890
extern void *data_ov003_02234890[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347e8
extern void *data_ov003_022347e8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347e0
extern void *data_ov003_022347e0[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347d8
extern void *data_ov003_022347d8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347d0
extern void *data_ov003_022347d0[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234880
extern void *data_ov003_02234880[2];
#endif
#ifndef PROTO_LOCAL_sFishPullJitter
extern s32 sFishPullJitter;
#endif
#ifndef PROTO_LOCAL_data_ov003_02234808
extern void *data_ov003_02234808[2];
#endif
#ifndef PROTO_LOCAL_sFishFinAnimPath
extern char *sFishFinAnimPath;
#endif
#ifndef PROTO_LOCAL_sFishFinTexAnimPathStr
extern char sFishFinTexAnimPathStr[];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234828
extern void *data_ov003_02234828[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347a8
extern void *data_ov003_022347a8[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_022347c0
extern void *data_ov003_022347c0[2];
#endif
#ifndef PROTO_LOCAL_sFishShadowModelPath
extern char *sFishShadowModelPath;
#endif
#ifndef PROTO_LOCAL_data_ov003_022347f0
extern void *data_ov003_022347f0[2];
#endif
#ifndef PROTO_LOCAL_sFishFinModelPathStr
extern char sFishFinModelPathStr[];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234818
extern void *data_ov003_02234818[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234848
extern void *data_ov003_02234848[2];
#endif
#ifndef PROTO_LOCAL_sFishFinModelPath
extern char *sFishFinModelPath;
#endif
#ifndef PROTO_LOCAL_data_ov003_022348b0
extern u8 data_ov003_022348b0[16];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234878
extern void *data_ov003_02234878[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234840
extern void *data_ov003_02234840[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234810
extern void *data_ov003_02234810[2];
#endif
#ifndef PROTO_LOCAL_data_ov003_02234868
extern void *data_ov003_02234868[2];
#endif
#ifndef PROTO_LOCAL_FieldFishManager_Create
void *FieldFishManager_Create();
#endif
#ifndef PROTO_LOCAL_BottleThrow_IsActive
BOOL BottleThrow_IsActive(s32 i);
#endif
#ifndef PROTO_LOCAL_BottleThrow_Start
s32 BottleThrow_Start(s32 i);
#endif
#ifndef PROTO_LOCAL_BottleThrow_GetSeCue
s32 BottleThrow_GetSeCue(s32 i);
#endif
#ifndef PROTO_LOCAL_BottleThrow_StateIdle
void BottleThrow_StateIdle();
#endif
#ifndef PROTO_LOCAL_FieldFish_AddSinX
void FieldFish_AddSinX(s32 *p, s32 a, s32 ang);
#endif
#ifndef PROTO_LOCAL_FieldFish_AddCosZ
void FieldFish_AddCosZ(s32 *p, s32 a, s32 ang);
#endif
#ifndef PROTO_LOCAL_FishShadow_AppearAttached
void FishShadow_AppearAttached();
#endif
#ifndef PROTO_LOCAL_FishCatch_StartLift
BOOL FishCatch_StartLift(s32 idx, s32 flag);
#endif
#ifndef PROTO_LOCAL_FishCatch_IsActive
BOOL FishCatch_IsActive(s32 idx);
#endif
#ifndef PROTO_LOCAL_FishCatch_NetSendStored
BOOL FishCatch_NetSendStored(s32 idx);
#endif
#ifndef PROTO_LOCAL_FieldFish_StartCastSplash
void FieldFish_StartCastSplash();
#endif
#ifndef PROTO_LOCAL_FieldFish_IsCastSplashActive
BOOL FieldFish_IsCastSplashActive();
#endif
#ifndef PROTO_LOCAL_FieldFish_TickCastSplash
void FieldFish_TickCastSplash();
#endif
#ifndef PROTO_LOCAL_FishCatch_StateIdle
s32 FishCatch_StateIdle();
#endif
#ifndef PROTO_LOCAL_FishShadow_EnterSpawn
void FishShadow_EnterSpawn();
#endif
#ifndef PROTO_LOCAL_FishShadow_EnterWaitInView
void FishShadow_EnterWaitInView();
#endif
#ifndef PROTO_LOCAL_FishShadow_EnterAppear
void FishShadow_EnterAppear();
#endif
#ifndef PROTO_LOCAL_FishShadow_EnterOutOfView
void FishShadow_EnterOutOfView(void);
#endif
#ifndef PROTO_LOCAL_FishShadow_EnterSwim
void FishShadow_EnterSwim(void);
#endif
#ifndef PROTO_LOCAL_FieldFish_IsPlayerRunning
BOOL FieldFish_IsPlayerRunning(s32 idx);
#endif
#ifndef PROTO_LOCAL_FieldFish_HasPassed1D
BOOL FieldFish_HasPassed1D(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_FieldFish_RandRange
s32 FieldFish_RandRange(s32 a, u16 b);
#endif
#ifndef PROTO_LOCAL_FieldFish_RandRangeSigned
s32 FieldFish_RandRangeSigned(s32 a, u16 b);
#endif
#ifndef PROTO_LOCAL_FishShadow_GetFishId
s32 FishShadow_GetFishId(s32 id);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sFishShadows
extern FishShadow sFishShadows[6];
#endif
#ifndef PROTO_LOCAL_sFishFinModel
extern FishFinModel sFishFinModel;
#endif
#ifndef PROTO_LOCAL_sFishCatches
extern FishCatch sFishCatches[4];
#endif
#ifndef PROTO_LOCAL_sBottleThrowStateOwner
extern BottleThrowStateOwner sBottleThrowStateOwner;
#endif
#ifndef PROTO_LOCAL_sBottleThrows
extern BottleThrow sBottleThrows[4];
#endif
#ifndef PROTO_LOCAL_sBottleThrowStates
extern BottleThrowStateEntry sBottleThrowStates[3];
#endif
#ifndef PROTO_LOCAL_sFishCatchStates
extern FishCatchStateEntry sFishCatchStates[5];
#endif
#ifndef PROTO_LOCAL_sFishShadowAiTable
extern FishAiStateEntry sFishShadowAiTable[2];
#endif
#ifndef PROTO_LOCAL_sFishShadowMoveStates
extern FishMoveStateEntry sFishShadowMoveStates[6];
#endif
#ifndef PROTO_LOCAL_sFishBiteStates
extern FishBiteStateEntry sFishBiteStates[8];
#endif
#ifndef PROTO_LOCAL_sFishRodParams
extern FishRodParams sFishRodParams[2];
#endif
#ifndef PROTO_LOCAL_sFieldFishManagerProfile
extern ProcProfile sFieldFishManagerProfile;
#endif
#ifndef PROTO_LOCAL_sFishSightGoldenRod
extern FishSight sFishSightGoldenRod[5];
#endif
#ifndef PROTO_LOCAL_sFishBiteWindowGoldenRod
extern FishBiteWindow sFishBiteWindowGoldenRod;
#endif
#ifndef PROTO_LOCAL_sFishBiteWindowFishingRod
extern FishBiteWindow sFishBiteWindowFishingRod;
#endif
#ifndef PROTO_LOCAL_sFishSightFishingRod
extern FishSight sFishSightFishingRod[5];
#endif
#ifndef PROTO_LOCAL_sFishShadowStates
extern FishShadowStateEntry sFishShadowStates[5];
#endif
#ifndef PROTO_LOCAL_FieldFish_MoveXZ
void FieldFish_MoveXZ(VecFx32 *p, s32 a, s32 ang);
#endif
#ifndef PROTO_LOCAL_FishShadow_CanSeeBobber
BOOL FishShadow_CanSeeBobber(VecFx32 *self, s32 a1, s32 a2, s32 a3);
#endif
#ifndef PROTO_LOCAL_FishCroak_Clear
void FishCroak_Clear(FishCroak *s);
#endif
#ifndef PROTO_LOCAL_FishCatch_Update
void FishCatch_Update(FishCatch *self, s32 arg);
#endif
#ifndef PROTO_LOCAL_FishCroak_Init
void FishCroak_Init(FishCroak *p);
#endif
#ifndef PROTO_LOCAL_FishCroak_Destroy
void FishCroak_Destroy(FishCroak *p);
#endif
#ifndef PROTO_LOCAL_FieldFish_ScareAround
BOOL FieldFish_ScareAround(VecFx32 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_FieldWater_ApplyFlow
void FieldWater_ApplyFlow(VecFx32 *p, s32 b);
#endif
#ifndef PROTO_LOCAL_FishShadow_TickRespawnTimer
void FishShadow_TickRespawnTimer(FishShadow *self);
#endif
#ifndef PROTO_LOCAL_FieldFish_IsInBox
BOOL FieldFish_IsInBox(VecFx32 *a, VecFx32 *b, s32 c, s32 d, s32 e);
#endif
#ifndef PROTO_LOCAL_FieldFish_HasPassed
BOOL FieldFish_HasPassed(VecFx32 *a, VecFx32 *b, VecFx32 *c);
#endif
#ifndef PROTO_LOCAL_FishCatch_GetReelTarget
BOOL FishCatch_GetReelTarget(VecFx32 *out, s32 idx);
#endif
#ifndef PROTO_LOCAL_FishCatch_StartRelease
BOOL FishCatch_StartRelease(s32 idx, u16 id0, VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_FishShadow_SetAnimSpeed
void FishShadow_SetAnimSpeed(FishShadow *self, s32 v);
#endif
#ifndef PROTO_LOCAL_FishShadow_LoadModel
BOOL FishShadow_LoadModel(FishShadow *self, void *p, ModelSlotPool *q);
#endif
#ifndef PROTO_LOCAL_FishFinModel_Load
BOOL FishFinModel_Load(FishFinModel *self, ModelSlotPool *a);
#endif
#ifndef PROTO_LOCAL_FishShadow_GetActive
FishShadow *FishShadow_GetActive(s32 i);
#endif
#ifndef PROTO_LOCAL_FishShadow_GetPos
BOOL FishShadow_GetPos(VecFx32 *out, s32 id);
#endif
}
#endif

#endif

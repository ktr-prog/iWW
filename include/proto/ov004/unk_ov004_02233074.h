#ifndef PROTO_PROTO_OV004_UNK_OV004_02233074_H
#define PROTO_PROTO_OV004_UNK_OV004_02233074_H


#include "types.h"
#include "sys/ProcProfile.h"
struct FtrMoveAnim;
struct FtrSoundRecord;
struct TvProgSlot;
struct TvScreen;
#ifndef __cplusplus
typedef struct FtrMoveAnim FtrMoveAnim;
typedef struct FtrSoundRecord FtrSoundRecord;
typedef struct TvProgSlot TvProgSlot;
typedef struct TvScreen TvScreen;
#endif
#ifdef __cplusplus
#include "actor/Actor.h"
#include "gfx/ModelSlotPool.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#include "room/FtrActorGrid.h"
#include "room/FtrActorTable.h"
#include "room/FtrManager.h"
#include "room/FtrPreviewer.h"
#include "snd/TvSound.h"
class FtrActor;
class FurnitureManager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FtrMgr_IsSaleMode
u32 FtrMgr_IsSaleMode();
#endif
#ifndef PROTO_LOCAL_FtrMgr_SetSaleMode
void FtrMgr_SetSaleMode();
#endif
#ifndef PROTO_LOCAL_FtrSoundEmitter_Destroy
void FtrSoundEmitter_Destroy();
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e934
extern char data_ov004_0224e934[8];
#endif
#ifndef PROTO_LOCAL_sFtrMoveAnimModelName
extern char sFtrMoveAnimModelName[0x10];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e954
extern char data_ov004_0224e954[8];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e964
extern char data_ov004_0224e964[8];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e944
extern char data_ov004_0224e944[8];
#endif
#ifndef PROTO_LOCAL_FtrMgr_IsFurnitureEditable
s32 FtrMgr_IsFurnitureEditable();
#endif
#ifndef PROTO_LOCAL_FtrMgr_IsFurnitureUsable
s32 FtrMgr_IsFurnitureUsable();
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetSurfaceHeight
s32 FtrMgr_GetSurfaceHeight(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e96c
extern char data_ov004_0224e96c[8];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e974
extern char data_ov004_0224e974[8];
#endif
#ifndef PROTO_LOCAL_FtrMgr_BroadcastStereosAct0
BOOL FtrMgr_BroadcastStereosAct0();
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetCycleCounter
u16 FtrMgr_GetCycleCounter();
#endif
#ifndef PROTO_LOCAL_FtrMgr_PickFurnitureComment
s32 FtrMgr_PickFurnitureComment(u32 key);
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetMaxFurniture
u32 FtrMgr_GetMaxFurniture();
#endif
#ifndef PROTO_LOCAL_FtrMgr_IsShopScene
BOOL FtrMgr_IsShopScene();
#endif
#ifndef PROTO_LOCAL_FtrMgr_CreateHook
void FtrMgr_CreateHook(void *);
#endif
#ifndef PROTO_LOCAL_FtrMgr_SpawnAllFromMap
void FtrMgr_SpawnAllFromMap(void *);
#endif
#ifndef PROTO_LOCAL_FtrMgr_NotifyNearestCabinClock
void FtrMgr_NotifyNearestCabinClock(void *);
#endif
#ifndef PROTO_LOCAL_FtrMgr_NotifyNearestSoundingClock
void FtrMgr_NotifyNearestSoundingClock(void *);
#endif
#ifndef PROTO_LOCAL_FtrMgr_FindFurnitureFacingPlayer
s32 FtrMgr_FindFurnitureFacingPlayer(s32 *a, s32 *b, u16 *c, u16 *d);
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetActorLayer
u8 FtrMgr_GetActorLayer(u32 i);
#endif
#ifndef PROTO_LOCAL_FtrMgr_RemoveActor
s32 FtrMgr_RemoveActor(s32 idx, u16 *p1, u16 *p2);
#endif
#ifndef PROTO_LOCAL_FtrMgr_RemoveActorByIndex
s32 FtrMgr_RemoveActorByIndex(s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrMgr_IsPickableByIndex
s32 FtrMgr_IsPickableByIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrMgr_TryPlaceAt
s32 FtrMgr_TryPlaceAt(u32 *out, s32 x, s32 y, s32 dir, s32 pl, u32 layer, s32 cx, s32 cy);
#endif
#ifndef PROTO_LOCAL_FtrMgr_FindPlacementForPlayer
s32 FtrMgr_FindPlacementForPlayer(u32 *a, u16 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetCurPlayerIndex
s32 FtrMgr_GetCurPlayerIndex();
#endif
#ifndef PROTO_LOCAL_FtrMgr_TakeDisplayedWearable
s32 FtrMgr_TakeDisplayedWearable(void *o0);
#endif
#ifndef PROTO_LOCAL_FtrMgr_TakeDisplayedWearableAt
s32 FtrMgr_TakeDisplayedWearableAt(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_FtrMgr_RestoreDisplayedWearable
s32 FtrMgr_RestoreDisplayedWearable(void *o0);
#endif
#ifndef PROTO_LOCAL_FtrMgr_RestoreDisplayedWearableAt
s32 FtrMgr_RestoreDisplayedWearableAt(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_FtrMgr_OnRemoteStorageOpen
BOOL FtrMgr_OnRemoteStorageOpen(void);
#endif
#ifndef PROTO_LOCAL_FtrMgr_OnRemoteStorageHold
BOOL FtrMgr_OnRemoteStorageHold(void);
#endif
#ifndef PROTO_LOCAL_FtrMgr_OnRemoteStorageClose
BOOL FtrMgr_OnRemoteStorageClose(void);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetTvTex
void *FurnitureManager_GetTvTex(void);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetTvProgram
s32 FurnitureManager_GetTvProgram(void);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetTvLoopCount
s32 FurnitureManager_GetTvLoopCount(void);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetTvFrame
s32 FurnitureManager_GetTvFrame(void);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_SetTvProgramChanged
void FurnitureManager_SetTvProgramChanged(void);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_IsTvProgramChanged
u8 FurnitureManager_IsTvProgramChanged(void);
#endif
#ifndef PROTO_LOCAL_FtrMoveFlag_Init
void FtrMoveFlag_Init(u8 *p);
#endif
#ifndef PROTO_LOCAL_FtrMoveFlag_Destroy
void FtrMoveFlag_Destroy(u8 *p);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetMoveAnim
void *FurnitureManager_GetMoveAnim(void);
#endif
#ifndef PROTO_LOCAL_TvWeather_GetName
const char *TvWeather_GetName(u32 i);
#endif
#ifndef PROTO_LOCAL_TvSchedule_GetCurrentProgram
u8 TvSchedule_GetCurrentProgram(void *);
#endif
#ifndef PROTO_LOCAL_TvWeather_IsUnkPeriod
s32 TvWeather_IsUnkPeriod();
#endif
#ifndef PROTO_LOCAL_TvWeather_GetForecastIndex
s32 TvWeather_GetForecastIndex(void *);
#endif
#ifndef PROTO_LOCAL_FtrSound_GetSe0
u16 FtrSound_GetSe0(s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrSound_GetSe1
u16 FtrSound_GetSe1(s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrSound_GetSe2
u16 FtrSound_GetSe2(s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrSound_GetSe3
u16 FtrSound_GetSe3(s32 idx);
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e95c
extern char data_ov004_0224e95c[8];
#endif
#ifndef PROTO_LOCAL_sFtrMgrTvSoundEnabled
extern u8 sFtrMgrTvSoundEnabled;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e97c
extern char data_ov004_0224e97c[8];
#endif
#ifndef PROTO_LOCAL_sFtrMgrSaleMode
extern u8 sFtrMgrSaleMode;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e93c
extern char data_ov004_0224e93c[8];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e984
extern char data_ov004_0224e984[8];
#endif
#ifndef PROTO_LOCAL_sFtrMgrCycleCounter
extern u16 sFtrMgrCycleCounter;
#endif
#ifndef PROTO_LOCAL_data_ov004_0224e94c
extern char data_ov004_0224e94c[8];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_FurnitureManager_Create
FurnitureManager *FurnitureManager_Create();
#endif
#ifndef PROTO_LOCAL_FtrPreviewer_GetInstance
FtrPreviewer *FtrPreviewer_GetInstance();
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetSoundList
FtrSoundList *FurnitureManager_GetSoundList();
#endif
#ifndef PROTO_LOCAL_FtrActorHeap_GetInstance
FtrActorHeap *FtrActorHeap_GetInstance();
#endif
#ifndef PROTO_LOCAL_FtrActorTable_GetInstance
FtrActorTable *FtrActorTable_GetInstance();
#endif
#ifndef PROTO_LOCAL_FtrActorGrid_GetInstance
FtrActorGrid *FtrActorGrid_GetInstance();
#endif
#ifndef PROTO_LOCAL_FtrContactSet_GetInstance
FtrContactSet *FtrContactSet_GetInstance();
#endif
#ifndef PROTO_LOCAL_FtrMgr_SpawnFromArg
Actor *FtrMgr_SpawnFromArg(u32 self);
#endif
#ifndef PROTO_LOCAL_FtrMgr_SpawnFurniture
Actor *FtrMgr_SpawnFurniture(s32 x, s32 y, s32 a, s32 b, u8 c, s32 d);
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetSurfaceHeightAtPos
s32 FtrMgr_GetSurfaceHeightAtPos(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_FtrMgr_CheckBedStep
s32 FtrMgr_CheckBedStep(VecFx32 *pos, s32 ang, VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_sFurnitureManagerProfile
extern ProcProfile sFurnitureManagerProfile;
#endif
#ifndef PROTO_LOCAL_FtrMgr_CheckBedStepFront
s32 FtrMgr_CheckBedStepFront(VecFx32 *pos, s32 ang);
#endif
#ifndef PROTO_LOCAL_FtrMgr_CheckBedStepBack
s32 FtrMgr_CheckBedStepBack(VecFx32 *pos, s32 ang);
#endif
#ifndef PROTO_LOCAL_FtrMgr_TestStepTarget
s32 FtrMgr_TestStepTarget(VecFx32 *p, s16 ang, s32 dist);
#endif
#ifndef PROTO_LOCAL_FtrMgr_CanStepForward
BOOL FtrMgr_CanStepForward(VecFx32 *pos, s32 ang);
#endif
#ifndef PROTO_LOCAL_FtrMgr_CanStepSidePlus90
BOOL FtrMgr_CanStepSidePlus90(VecFx32 *pos, s32 ang);
#endif
#ifndef PROTO_LOCAL_FtrMgr_CanStepSideMinus90
BOOL FtrMgr_CanStepSideMinus90(VecFx32 *pos, s32 ang);
#endif
#ifndef PROTO_LOCAL_FtrMgr_SetSwitchAll
void FtrMgr_SetSwitchAll(u32 v, BOOL (*f)(FtrActor *), s32 a);
#endif
#ifndef PROTO_LOCAL_FtrMgr_CountSwitchedOn
s32 FtrMgr_CountSwitchedOn(BOOL (*f)(FtrActor *));
#endif
#ifndef PROTO_LOCAL_FtrMgr_SwitchOffRandom
FtrActor *FtrMgr_SwitchOffRandom(BOOL (*f)(FtrActor *), s32 a);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_UpdateTvSound
void FurnitureManager_UpdateTvSound(FurnitureManager *self);
#endif
#ifndef PROTO_LOCAL_FtrMgr_FindFacingFurniture
s32 FtrMgr_FindFacingFurniture(s32 *ox, s32 *oy, VecFx32 *pos, s32 ang, u16 *p1, u16 *p2);
#endif
#ifndef PROTO_LOCAL_FtrMgr_PollRemovedPos
VecFx32 *FtrMgr_PollRemovedPos(s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrMgr_SetRemovePos
void FtrMgr_SetRemovePos(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FtrMgr_IsPickable
s32 FtrMgr_IsPickable(FtrActor *p);
#endif
#ifndef PROTO_LOCAL_FtrMgr_GetProbeTile
s32 FtrMgr_GetProbeTile(s32 *ox, s32 *oy, VecFx32 *pos, s32 ang, s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrMgr_FindPlacement
s32 FtrMgr_FindPlacement(u32 *out, u16 *tile, VecFx32 *pos, s32 ang, s32 mode);
#endif
#ifndef PROTO_LOCAL_FurnitureManager_GetTvSound
TvSound *FurnitureManager_GetTvSound(void);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_NodeCallback
void FtrMoveAnim_NodeCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_InstallCallback
void FtrMoveAnim_InstallCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_Load
void FtrMoveAnim_Load(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_Unload
void FtrMoveAnim_Unload(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_GetMtx
void *FtrMoveAnim_GetMtx(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_SetPos
void FtrMoveAnim_SetPos(FtrMoveAnim *r, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_Start
BOOL FtrMoveAnim_Start(FtrMoveAnim *r, void *x, volatile u8 *flag, VecFx32 *pos, s32 e);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_StartPush
BOOL FtrMoveAnim_StartPush(FtrMoveAnim *r, volatile u8 *a, VecFx32 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_StartPull
BOOL FtrMoveAnim_StartPull(FtrMoveAnim *r, volatile u8 *a, VecFx32 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_Step
BOOL FtrMoveAnim_Step(FtrMoveAnim *r, volatile u8 *a, VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_CreateHeap
BOOL FtrMoveAnim_CreateHeap(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_DestroyHeap
BOOL FtrMoveAnim_DestroyHeap(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_LoadAnims
BOOL FtrMoveAnim_LoadAnims(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_ClearAnims
BOOL FtrMoveAnim_ClearAnims(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_LoadModel
BOOL FtrMoveAnim_LoadModel(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_ClearModel
BOOL FtrMoveAnim_ClearModel(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_GetPushAnim
void *FtrMoveAnim_GetPushAnim(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_GetPullAnim
void *FtrMoveAnim_GetPullAnim(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_FtrMoveAnim_GetHaniwaAnim
void *FtrMoveAnim_GetHaniwaAnim(FtrMoveAnim *r);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_Init
void TvProgSlot_Init(TvProgSlot *p, void *a);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_Load
BOOL TvProgSlot_Load(TvProgSlot *p, u32 id, s32 x);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_FreeFiles
void TvProgSlot_FreeFiles(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_Update
void TvProgSlot_Update(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_Release
void TvProgSlot_Release(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_GetProgram
s32 TvProgSlot_GetProgram(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_GetWeather
s32 TvProgSlot_GetWeather(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_GetLoopCount
u16 TvProgSlot_GetLoopCount(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvProgSlot_GetFrame
u32 TvProgSlot_GetFrame(TvProgSlot *p);
#endif
#ifndef PROTO_LOCAL_TvScreen_Load
void TvScreen_Load(TvScreen *q);
#endif
#ifndef PROTO_LOCAL_TvScreen_SetProgram
BOOL TvScreen_SetProgram(TvScreen *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_TvScreen_UpdateSchedule
void TvScreen_UpdateSchedule(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_Update
void TvScreen_Update(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_Release
void TvScreen_Release(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_IsLoaded
BOOL TvScreen_IsLoaded(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_GetProgram
s32 TvScreen_GetProgram(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_GetWeather
s32 TvScreen_GetWeather(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_GetTex
void *TvScreen_GetTex(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_GetSound
TvSound *TvScreen_GetSound(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_GetLoopCount
s32 TvScreen_GetLoopCount(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_TvScreen_GetFrame
s32 TvScreen_GetFrame(TvScreen *o);
#endif
#ifndef PROTO_LOCAL_FtrSound_GetRecord
const FtrSoundRecord *FtrSound_GetRecord(s32 idx);
#endif
#ifndef PROTO_LOCAL_FtrMgr_PlaySeatSound1At
void FtrMgr_PlaySeatSound1At(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_FtrMgr_PlaySeatSound0At
void FtrMgr_PlaySeatSound0At(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_FtrMgr_PlaySeatSound2At
void FtrMgr_PlaySeatSound2At(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_sFurnitureManager
extern FurnitureManager *sFurnitureManager;
#endif
}
#ifndef PROTO_LOCAL_sFtrMgrPool
extern ModelSlotPool sFtrMgrPool;
#endif
#ifndef PROTO_LOCAL_sFtrActorTable
extern FtrActorTable sFtrActorTable;
#endif
#ifndef PROTO_LOCAL_sFtrActorHeap
extern FtrActorHeap sFtrActorHeap;
#endif
#ifndef PROTO_LOCAL_sFtrPreviewer
extern FtrPreviewer sFtrPreviewer;
#endif
#ifndef PROTO_LOCAL_sFtrActorGrid
extern FtrActorGrid sFtrActorGrid;
#endif
#ifndef PROTO_LOCAL_sFtrContactSet
extern FtrContactSet sFtrContactSet;
#endif
#ifndef PROTO_LOCAL_sFtrMgrSoundRangeSq
extern s32 sFtrMgrSoundRangeSq;
#endif
#endif

#endif

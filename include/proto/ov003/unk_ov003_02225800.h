#ifndef PROTO_PROTO_OV003_UNK_OV003_02225800_H
#define PROTO_PROTO_OV003_UNK_OV003_02225800_H


#include "types.h"
#include "gfx/Mtx43.h"
#include "sys/ProcProfile.h"
struct InsectBehavior;
struct InsectModelParams;
#ifndef __cplusplus
typedef struct InsectBehavior InsectBehavior;
typedef struct InsectModelParams InsectModelParams;
#endif
#ifdef __cplusplus
#include "actor/Actor.h"
#include "field/Insect.h"
#include "game/FxVec3.h"
#include "gfx/VecFx32.h"
class InsectManager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov003_02258f10
extern u16 data_ov003_02258f10;
#endif
#ifndef PROTO_LOCAL_sWateringActive
extern u8 sWateringActive;
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaskDry
extern u16 sInsectSpawnMaskDry[4][4][16];
#endif
#ifndef PROTO_LOCAL_sTrashFlySpawnEnabled
extern s8 sTrashFlySpawnEnabled;
#endif
#ifndef PROTO_LOCAL_sAntSpawnEnabled
extern u8 sAntSpawnEnabled;
#endif
#ifndef PROTO_LOCAL_data_ov003_02258f08
extern u8 data_ov003_02258f08;
#endif
#ifndef PROTO_LOCAL_data_ov003_02258f04
extern u8 data_ov003_02258f04;
#endif
#ifndef PROTO_LOCAL_sInsectSpawnTimer
extern u8 sInsectSpawnTimer;
#endif
#ifndef PROTO_LOCAL_sInsectSpawnMaskLand
extern u16 sInsectSpawnMaskLand[4][4][16];
#endif
#ifndef PROTO_LOCAL_sFieldInsectPurgeTimer
extern u16 sFieldInsectPurgeTimer;
#endif
#ifndef PROTO_LOCAL_sInsectCatchResult
extern u8 sInsectCatchResult;
#endif
#ifndef PROTO_LOCAL_Insect_LikesFlower
BOOL Insect_LikesFlower(s32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_Insect_GetSeId
s32 Insect_GetSeId(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Insect_GetFlowerSpeciesMask
s32 Insect_GetFlowerSpeciesMask(s32 a);
#endif
#ifndef PROTO_LOCAL_Insect_ReflectAngle
s32 Insect_ReflectAngle(s32 a, s32 mode);
#endif
#ifndef PROTO_LOCAL_Insect_RandomTurn
s16 Insect_RandomTurn(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Insect_RandomAngle
s16 Insect_RandomAngle();
#endif
#ifndef PROTO_LOCAL_InsectManager_Create
void *InsectManager_Create();
#endif
#ifndef PROTO_LOCAL_FieldInsect_GetKindAndAlarm
s32 FieldInsect_GetKindAndAlarm(u8 *out, u32 idx);
#endif
#ifndef PROTO_LOCAL_FieldInsect_IsTreeKind
BOOL FieldInsect_IsTreeKind(u32 idx);
#endif
#ifndef PROTO_LOCAL_HeldInsect_Release
void HeldInsect_Release(s32 idx, s32 v);
#endif
#ifndef PROTO_LOCAL_HeldInsect_GetStage
u32 HeldInsect_GetStage(s32 idx);
#endif
#ifndef PROTO_LOCAL_HeldInsect_Start
void HeldInsect_Start(s32 t, s32 idx);
#endif
#ifndef PROTO_LOCAL_Insect_OnNetRemove
void Insect_OnNetRemove(s32 id);
#endif
#ifndef PROTO_LOCAL_Insect_CanHopAway
BOOL Insect_CanHopAway(s32 t);
#endif
#ifndef PROTO_LOCAL_Insect_OnClaimGranted
void Insect_OnClaimGranted(s32 id);
#endif
#ifndef PROTO_LOCAL_HeldInsect_Remove
void HeldInsect_Remove(u8 id, s32 flag);
#endif
#ifndef PROTO_LOCAL_Insect_FinishCatch
s32 Insect_FinishCatch(u8 id);
#endif
#ifndef PROTO_LOCAL_Insect_GetCatchResult
s32 Insect_GetCatchResult(s32 id);
#endif
#ifndef PROTO_LOCAL_Insect_CancelCatch
void Insect_CancelCatch(s32 id);
#endif
#ifndef PROTO_LOCAL_Insect_TryCatch
s32 Insect_TryCatch(u8 id);
#endif
#ifndef PROTO_LOCAL_Insect_EnableTrashFlies
void Insect_EnableTrashFlies(void);
#endif
#ifndef PROTO_LOCAL_Insect_Spawn
BOOL Insect_Spawn(void *obj, s32 kind, u8 sub, s32 flag);
#endif
#ifndef PROTO_LOCAL_HeldInsect_SetHandMatrix
BOOL HeldInsect_SetHandMatrix(s32 idx, s16 *p, Mtx43 *q, s32 flag);
#endif
#ifndef PROTO_LOCAL_Insect_NetClaim
BOOL Insect_NetClaim(s32 x);
#endif
#ifndef PROTO_LOCAL_Insect_IsBeeSwarmOut
BOOL Insect_IsBeeSwarmOut(void);
#endif
#ifndef PROTO_LOCAL_Insect_RollKind
BOOL Insect_RollKind(u8 *out);
#endif
#ifndef PROTO_LOCAL_Insect_GetTimeSlot
s32 Insect_GetTimeSlot();
#endif
#ifndef PROTO_LOCAL_Insect_PickSpecialSpawn
BOOL Insect_PickSpecialSpawn(s8 *a, s8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Insect_IsAllowedOnline
BOOL Insect_IsAllowedOnline(s32 a);
#endif
#ifndef PROTO_LOCAL_Insect_RollFromSpawnTable
BOOL Insect_RollFromSpawnTable(u32 a, u32 b, u8 *out);
#endif
#ifndef PROTO_LOCAL_FieldInsect_PurgeStale
void FieldInsect_PurgeStale();
#endif
#ifndef PROTO_LOCAL_Insect_GetWeatherReaction
s32 Insect_GetWeatherReaction(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InsectSpawn_CopyMask
void InsectSpawn_CopyMask(void *p, s32 t);
#endif
#ifndef PROTO_LOCAL_InsectSpawn_BuildLightMask
void InsectSpawn_BuildLightMask(u16 (*arr)[4][16]);
#endif
#ifndef PROTO_LOCAL_InsectSpawn_ClearLitUnits
void InsectSpawn_ClearLitUnits(u16 (*arr)[4][16]);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sFieldInsects
extern Insect sFieldInsects[8];
#endif
#ifndef PROTO_LOCAL_sSpecialInsects
extern Insect sSpecialInsects[2];
#endif
#ifndef PROTO_LOCAL_sHeldInsects
extern Insect sHeldInsects[4];
#endif
#ifndef PROTO_LOCAL_sInsectModelParams
extern InsectModelParams sInsectModelParams[60];
#endif
#ifndef PROTO_LOCAL_sInsectManagerProfile
extern ProcProfile sInsectManagerProfile;
#endif
#ifndef PROTO_LOCAL_sInsectBehaviors
extern InsectBehavior sInsectBehaviors[60];
#endif
#ifndef PROTO_LOCAL_sWateringPos
extern FxVec3NoCtor sWateringPos;
#endif
#ifndef PROTO_LOCAL_Insect_IsOverWater
BOOL Insect_IsOverWater(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Insect_FindNearestPlayer
Actor *Insect_FindNearestPlayer(VecFx32 *pos);
#endif
#ifndef PROTO_LOCAL_Insect_IsOnFlower
BOOL Insect_IsOnFlower(VecFx32 *pp);
#endif
#ifndef PROTO_LOCAL_Insect_InitDragonflyParams
void Insect_InitDragonflyParams(Insect *a, s32 x, s32 y, s32 z, u8 p4, u8 p5);
#endif
#ifndef PROTO_LOCAL_Insect_InitDragonfly
void Insect_InitDragonfly(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateDragonfly
void Insect_UpdateDragonfly(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitPondskater
void Insect_InitPondskater(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdatePondskater
void Insect_UpdatePondskater(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitOnPlant
void Insect_InitOnPlant(Insect *a, s32 x, s32 y, s32 z, s16 w);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateCrawler
void Insect_UpdateCrawler(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitCrawler
void Insect_InitCrawler(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitBurrower
void Insect_InitBurrower(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateMoleCricket
void Insect_UpdateMoleCricket(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdatePillBug
void Insect_UpdatePillBug(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitBee
void Insect_InitBee(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateBee
void Insect_UpdateBee(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitHoneybee
void Insect_InitHoneybee(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateHoneybee
void Insect_UpdateHoneybee(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitFly
void Insect_InitFly(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateFly
void Insect_UpdateFly(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitFlea
void Insect_InitFlea(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateFlea
void Insect_UpdateFlea(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitSpider
void Insect_InitSpider(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateSpider
void Insect_UpdateSpider(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateStinger
void Insect_UpdateStinger(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitTarantula
void Insect_InitTarantula(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitScorpion
void Insect_InitScorpion(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitAnt
void Insect_InitAnt(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateAnt
void Insect_UpdateAnt(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitDungBeetle
void Insect_InitDungBeetle(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateDungBeetle
void Insect_UpdateDungBeetle(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_InitKind38
void Insect_InitKind38(Insect *a);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateKind38
void Insect_UpdateKind38(Insect *a);
#endif
#ifndef PROTO_LOCAL_FieldInsect_GetPosAndKind
s32 FieldInsect_GetPosAndKind(VecFx32Ctor *out, u32 idx);
#endif
#ifndef PROTO_LOCAL_Insect_UpdateSpawning
void Insect_UpdateSpawning(InsectManager *self);
#endif
#ifndef PROTO_LOCAL_FieldInsect_UpdateAll
void FieldInsect_UpdateAll(InsectManager *a);
#endif
#ifndef PROTO_LOCAL_SpecialInsect_UpdateAll
void SpecialInsect_UpdateAll(InsectManager *a);
#endif
#ifndef PROTO_LOCAL_HeldInsect_UpdateAll
void HeldInsect_UpdateAll(InsectManager *a);
#endif
#ifndef PROTO_LOCAL_Insect_IsTreeKindForCulling
BOOL Insect_IsTreeKindForCulling(InsectManager *a, s32 t);
#endif
#ifndef PROTO_LOCAL_InsectPool_UpdateInViewOfPlayer
void InsectPool_UpdateInViewOfPlayer(InsectManager *obj, s32 flag, s32 idx, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_InsectPool_UpdateInView
void InsectPool_UpdateInView(InsectManager *obj, s32 flag);
#endif
#ifndef PROTO_LOCAL_Insect_TrySpawnRandom
s32 Insect_TrySpawnRandom(InsectManager *a, s32 b, u8 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Insect_SpawnBeeSwarm
void Insect_SpawnBeeSwarm(VecFx32Ctor *v);
#endif
#ifndef PROTO_LOCAL_Insect_IsAtWateringPoint
BOOL Insect_IsAtWateringPoint(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_Insect_TickFrame
void Insect_TickFrame(Insect *self);
#endif
#ifndef PROTO_LOCAL_Insect_SetAnimSpeed
void Insect_SetAnimSpeed(Insect *self, u32 v);
#endif
#ifndef PROTO_LOCAL_InsectSpawn_PickPos
s32 InsectSpawn_PickPos(Insect *self, u16 *a, s32 code, u32 flag);
#endif
}
#endif

#endif

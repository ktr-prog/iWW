#ifndef PROTO_PROTO_MAIN_UNK_020B0E60_H
#define PROTO_PROTO_MAIN_UNK_020B0E60_H


#include "types.h"
#include "game/NibblePair.h"
#include "town/BuildingInfo.h"
struct Flags1;
#ifndef __cplusplus
typedef struct Flags1 Flags1;
#endif
#ifdef __cplusplus
#include "field/FieldObjectShapeQuery.h"
#include "game/StrBSizeData.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#include "town/BuildingActor.h"
#include "town/MapBlock.h"
class FieldStructureMgr;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Math_CountBits4
u32 Math_CountBits4(s32 v);
#endif
#ifndef PROTO_LOCAL_Item_GetBuildingIndex
s32 Item_GetBuildingIndex(u32 arg);
#endif
#ifndef PROTO_LOCAL_StrBSize_Load
void StrBSize_Load(void);
#endif
#ifndef PROTO_LOCAL_StrBSize_Unload
void StrBSize_Unload(void);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_Unregister
BOOL FieldStructureMgr_Unregister(void);
#endif
#ifndef PROTO_LOCAL_TownStyleRecord_DestructStub
void TownStyleRecord_DestructStub(void *p);
#endif
#ifndef PROTO_LOCAL_TownStyleRecord_ConstructStub
void TownStyleRecord_ConstructStub(void *p);
#endif
#ifndef PROTO_LOCAL_TownStyle_RollVillagerHouseStyles
void TownStyle_RollVillagerHouseStyles(u8 *out);
#endif
#ifndef PROTO_LOCAL_TownStyle_GetVillagerHouseStyle
u32 TownStyle_GetVillagerHouseStyle(u8 *p, u32 idx);
#endif
#ifndef PROTO_LOCAL_TownFlag_SetPattern
void TownFlag_SetPattern(void *p, void *src);
#endif
#ifndef PROTO_LOCAL_TownFlag_GetPattern
void *TownFlag_GetPattern(void *p);
#endif
#ifndef PROTO_LOCAL_TownStyleRecord_InitNew
void TownStyleRecord_InitNew(u8 *self);
#endif
#ifndef PROTO_LOCAL_Light_GetBaseEmission
u16 Light_GetBaseEmission(void);
#endif
#ifndef PROTO_LOCAL_BuildingStates_Reset
void BuildingStates_Reset(void);
#endif
#ifndef PROTO_LOCAL_BuildingState_Get
u8 BuildingState_Get(u32 id);
#endif
#ifndef PROTO_LOCAL_BuildingState_Set
BOOL BuildingState_Set(u32 id, u8 val);
#endif
#ifndef PROTO_LOCAL_Town_GetEventPlotItem
u16 *Town_GetEventPlotItem(s32 *outX, s32 *outY);
#endif
#ifndef PROTO_LOCAL_TownStructure_PlaceAtEventPlot
void TownStructure_PlaceAtEventPlot(u16 id);
#endif
#ifndef PROTO_LOCAL_TownStructure_RemoveFromEventPlot
BOOL TownStructure_RemoveFromEventPlot(u16 id);
#endif
#ifndef PROTO_LOCAL_Town_PlaceReddTent
void Town_PlaceReddTent(void);
#endif
#ifndef PROTO_LOCAL_Town_RemoveReddTent
BOOL Town_RemoveReddTent(void);
#endif
#ifndef PROTO_LOCAL_Town_PlaceKatrinaTent
void Town_PlaceKatrinaTent(void);
#endif
#ifndef PROTO_LOCAL_Town_RemoveKatrinaTent
BOOL Town_RemoveKatrinaTent(void);
#endif
#ifndef PROTO_LOCAL_Town_PlaceGracieCar
void Town_PlaceGracieCar(void);
#endif
#ifndef PROTO_LOCAL_Town_RemoveGracieCar
BOOL Town_RemoveGracieCar(void);
#endif
#ifndef PROTO_LOCAL_Town_PlaceCountdownSign
void Town_PlaceCountdownSign(void);
#endif
#ifndef PROTO_LOCAL_Town_RemoveCountdownSign
BOOL Town_RemoveCountdownSign(void);
#endif
#ifndef PROTO_LOCAL_Town_PlaceGulliverShip
BOOL Town_PlaceGulliverShip(s32 *pos, BOOL flag);
#endif
#ifndef PROTO_LOCAL_Town_RemoveGulliverShip
BOOL Town_RemoveGulliverShip(void);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_Copy
void BuildingInfo_Copy(BuildingInfo *dst, const BuildingInfo *src);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_Destroy
void BuildingInfo_Destroy(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetProfile
u16 BuildingInfo_GetProfile(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetEntranceType
u8 BuildingInfo_GetEntranceType(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetKind
u8 BuildingInfo_GetKind(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetInteriorScene
s8 BuildingInfo_GetInteriorScene(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetFlickeringLights
u8 BuildingInfo_GetFlickeringLights(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetViewRangeX
u8 BuildingInfo_GetViewRangeX(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetViewRangeFront
u8 BuildingInfo_GetViewRangeFront(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetViewRangeBack
u8 BuildingInfo_GetViewRangeBack(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_GetCapacity
u8 BuildingInfo_GetCapacity(BuildingInfo *i);
#endif
#ifndef PROTO_LOCAL_BuildingInfo_MakeKey
u32 BuildingInfo_MakeKey(BuildingInfo *i, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_BuildingKey_Make
u32 BuildingKey_Make(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Field_HasExitedBuildingKey
BOOL Field_HasExitedBuildingKey(void);
#endif
#ifndef PROTO_LOCAL_Field_CacheExitedBuildingKey
void Field_CacheExitedBuildingKey(void);
#endif
#ifndef PROTO_LOCAL_Field_GetExitedBuildingKey
u32 Field_GetExitedBuildingKey(void);
#endif
#ifndef PROTO_LOCAL_SaveVillager_IsAsleepAt
u32 SaveVillager_IsAsleepAt(s32 v);
#endif
#ifndef PROTO_LOCAL_Building_IsOwnerAsleep
u32 Building_IsOwnerAsleep(u32 v);
#endif
#ifndef PROTO_LOCAL_Building_ApplyStateRecord
BOOL Building_ApplyStateRecord(u16 *p);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_OnLeaveRecord
void BuildingOccupancy_OnLeaveRecord(u8 *p, s32 bit);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_Reset
void BuildingOccupancy_Reset(void);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_RequestEnter
void BuildingOccupancy_RequestEnter(u32 arg);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_GetAnswer
u8 BuildingOccupancy_GetAnswer(u32 a);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_Leave
void BuildingOccupancy_Leave(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_HouseVisitor_IsPresent
u8 HouseVisitor_IsPresent(void);
#endif
#ifndef PROTO_LOCAL_HouseVisitor_SetPresent
void HouseVisitor_SetPresent(void);
#endif
#ifndef PROTO_LOCAL_HouseVisitor_ClearPresent
void HouseVisitor_ClearPresent(void);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_GetPlayersForScene
u32 BuildingOccupancy_GetPlayersForScene(u32 a);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_CountForScene
u32 BuildingOccupancy_CountForScene(u32 a);
#endif
#ifndef PROTO_LOCAL_Room_CountOccupants
u32 Room_CountOccupants(void);
#endif
#ifndef PROTO_LOCAL_Taxi_SetLeaving
void Taxi_SetLeaving(void);
#endif
#ifndef PROTO_LOCAL_Taxi_ClearLeaving
void Taxi_ClearLeaving(void);
#endif
#ifndef PROTO_LOCAL_Taxi_IsLeaving
u8 Taxi_IsLeaving(void);
#endif
#ifndef PROTO_LOCAL_Taxi_SetArriving
void Taxi_SetArriving(void);
#endif
#ifndef PROTO_LOCAL_Taxi_ClearArriving
void Taxi_ClearArriving(void);
#endif
#ifndef PROTO_LOCAL_Taxi_IsArriving
u8 Taxi_IsArriving(void);
#endif
#ifndef PROTO_LOCAL_Building_SetLastEntranceType
void Building_SetLastEntranceType(u32 a);
#endif
#ifndef PROTO_LOCAL_Building_GetLastEntranceType
u32 Building_GetLastEntranceType(void);
#endif
#ifndef PROTO_LOCAL_Building_PlayDoorChime
void Building_PlayDoorChime(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_StrBSize_Get
StrBSizeData *StrBSize_Get(u16 *p);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_Register
BOOL FieldStructureMgr_Register(FieldStructureMgr *v);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_Get
FieldStructureMgr *FieldStructureMgr_Get(void);
#endif
#ifndef PROTO_LOCAL_JointCb_RotateClockHourHand
void JointCb_RotateClockHourHand(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_JointCb_RotateClockMinuteHand
void JointCb_RotateClockMinuteHand(NNSG3dRS *rs);
#endif
#ifndef PROTO_LOCAL_MapBlock_CountSigns
u32 MapBlock_CountSigns(MapBlock *cell);
#endif
#ifndef PROTO_LOCAL_MapBlock_ReplaceNthSign
u32 MapBlock_ReplaceNthSign(MapBlock *cell, u32 target, u32 v);
#endif
#ifndef PROTO_LOCAL_MapBlock_ReplaceRandomSign
BOOL MapBlock_ReplaceRandomSign(MapBlock *cell, u32 v);
#endif
#ifndef PROTO_LOCAL_Building_GetDoorAnimParamAt
u32 Building_GetDoorAnimParamAt(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_Building_RequestState
BOOL Building_RequestState(BuildingActor *o, s32 v);
#endif
#ifndef PROTO_LOCAL_BuildingOccupancy_OnEnterRecord
void BuildingOccupancy_OnEnterRecord(Flags1 *p, s32 bit);
#endif
}
#ifndef PROTO_LOCAL_Math_LerpFx
s32 Math_LerpFx(s32 t, s32 lo, s32 hi);
#endif
#ifndef PROTO_LOCAL_sHourHandFrame
extern s32 sHourHandFrame;
#endif
#ifndef PROTO_LOCAL_sLastEntranceType
extern u32 sLastEntranceType;
#endif
#ifndef PROTO_LOCAL_sStrBSizeArchive
extern void *sStrBSizeArchive;
#endif
#ifndef PROTO_LOCAL_sTaxiLeaving
extern u8 sTaxiLeaving;
#endif
#ifndef PROTO_LOCAL_sExitedBuildingKey
extern u32 sExitedBuildingKey;
#endif
#ifndef PROTO_LOCAL_sBuildingOccupancy
extern NibblePair sBuildingOccupancy[0x22];
#endif
#ifndef PROTO_LOCAL_sLampMatNameBuf
extern char sLampMatNameBuf[12];
#endif
#ifndef PROTO_LOCAL_sFieldObjectShapeQuery
extern FieldObjectShapeQuery sFieldObjectShapeQuery;
#endif
#ifndef PROTO_LOCAL_sBuildingStates
extern u8 sBuildingStates[0x22];
#endif
#ifndef PROTO_LOCAL_sFieldStructureMgr
extern FieldStructureMgr *sFieldStructureMgr;
#endif
#ifndef PROTO_LOCAL_sHouseVisitorPresent
extern u8 sHouseVisitorPresent;
#endif
#ifndef PROTO_LOCAL_sHourHandCos
extern s32 sHourHandCos;
#endif
#ifndef PROTO_LOCAL_sStrBSizeTable
extern StrBSizeData *sStrBSizeTable[0x22];
#endif
#ifndef PROTO_LOCAL_sTaxiArriving
extern u8 sTaxiArriving;
#endif
#ifndef PROTO_LOCAL_sHourHandSin
extern s32 sHourHandSin;
#endif
#endif

#endif

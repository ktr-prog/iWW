#ifndef PROTO_PROTO_OV003_UNK_OV003_022187FC_H
#define PROTO_PROTO_OV003_UNK_OV003_022187FC_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "field/FieldStructureMgr.h"
#include "gfx/VecFx32.h"
#include "town/BuildingActor.h"
class FieldStructureMgr;
class PlayerHouseTex;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sDoorExitMode
extern u8 sDoorExitMode;
#endif
#ifndef PROTO_LOCAL_sSpawnedBuildingCount1
extern u16 sSpawnedBuildingCount1;
#endif
#ifndef PROTO_LOCAL_data_ov003_02235888
extern char data_ov003_02235888[0x28];
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_Create
void *FieldStructureMgr_Create();
#endif
#ifndef PROTO_LOCAL_Field_GetStructureTexSuffix
s32 Field_GetStructureTexSuffix();
#endif
#ifndef PROTO_LOCAL_Field_GetSpawnedKind1Count
u32 Field_GetSpawnedKind1Count();
#endif
#ifndef PROTO_LOCAL_Field_GetDoorExitMode
u32 Field_GetDoorExitMode();
#endif
#ifndef PROTO_LOCAL_Field_SetDoorExitMode
void Field_SetDoorExitMode(u32 v);
#endif
#ifndef PROTO_LOCAL_VillagerHouse_TryOpenDoorForEntry
s32 VillagerHouse_TryOpenDoorForEntry(s32 a);
#endif
#ifndef PROTO_LOCAL_VillagerHouse_TryOpenDoorForExit
s32 VillagerHouse_TryOpenDoorForExit(s32 a);
#endif
#ifndef PROTO_LOCAL_BuildingList_Add
s32 BuildingList_Add(void *p);
#endif
#ifndef PROTO_LOCAL_BuildingList_Remove
s32 BuildingList_Remove(void *p);
#endif
#ifndef PROTO_LOCAL_BuildingList_GetAt
void *BuildingList_GetAt(s32 i);
#endif
#ifndef PROTO_LOCAL_BuildingList_IndexOf
s32 BuildingList_IndexOf(void *p);
#endif
#ifndef PROTO_LOCAL_BuildingList_Init
void BuildingList_Init();
#endif
#ifndef PROTO_LOCAL_BuildingList_Clear
void BuildingList_Clear();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sPlayerHouseTex
extern PlayerHouseTex sPlayerHouseTex;
#endif
#ifndef PROTO_LOCAL_sVillagerHouseTex
extern VillagerHouseTex sVillagerHouseTex;
#endif
#ifndef PROTO_LOCAL_sHouseLightUpDeco
extern HouseLightUpDeco sHouseLightUpDeco;
#endif
#ifndef PROTO_LOCAL_sFieldStructureMgrProfile
extern ProcProfile sFieldStructureMgrProfile;
#endif
#ifndef PROTO_LOCAL_sBuildingList
extern BuildingActor *sBuildingList[0x20];
#endif
#ifndef PROTO_LOCAL_func_ov003_02219164
void func_ov003_02219164(FieldStructureMgr *self);
#endif
#ifndef PROTO_LOCAL_func_ov003_02219160
void func_ov003_02219160(FieldStructureMgr *self);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_SpawnAll
s32 FieldStructureMgr_SpawnAll(FieldStructureMgr *self);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_SpawnBuilding
s32 FieldStructureMgr_SpawnBuilding(FieldStructureMgr *self, u16 *pv, s32 x, s32 y, u8 flag);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_ApplyFootprint
s32 FieldStructureMgr_ApplyFootprint(FieldStructureMgr *self, u16 *b, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_CreateHeap
void FieldStructureMgr_CreateHeap(FieldStructureMgr *self);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_DestroyHeap
void FieldStructureMgr_DestroyHeap(FieldStructureMgr *self);
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_GetPlayerHouseTex
PlayerHouseTex *FieldStructureMgr_GetPlayerHouseTex();
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_GetVillagerHouseTex
VillagerHouseTex *FieldStructureMgr_GetVillagerHouseTex();
#endif
#ifndef PROTO_LOCAL_FieldStructureMgr_GetLightUpDeco
HouseLightUpDeco *FieldStructureMgr_GetLightUpDeco();
#endif
#ifndef PROTO_LOCAL_Building_OpenDoorForEntryAt
s32 Building_OpenDoorForEntryAt(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_Building_OpenDoorForExitAt
s32 Building_OpenDoorForExitAt(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_Building_FindNearPos
BuildingActor *Building_FindNearPos(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_BuildingList_FindByGrid
BuildingActor *BuildingList_FindByGrid(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_BuildingList_FindByItem
BuildingActor *BuildingList_FindByItem(u32 id);
#endif
#ifndef PROTO_LOCAL_VillagerHouseTex_Load
s32 VillagerHouseTex_Load(VillagerHouseTex *self);
#endif
#ifndef PROTO_LOCAL_VillagerHouseTex_Clear
void VillagerHouseTex_Clear(VillagerHouseTex *o);
#endif
#ifndef PROTO_LOCAL_VillagerHouseTex_GetHouseTex
void *VillagerHouseTex_GetHouseTex(VillagerHouseTex *o, u32 i);
#endif
#ifndef PROTO_LOCAL_VillagerHouseTex_GetLightTex
void *VillagerHouseTex_GetLightTex(VillagerHouseTex *o, u32 i);
#endif
#ifndef PROTO_LOCAL_VillagerHouseTex_GetDoorInAnim
void *VillagerHouseTex_GetDoorInAnim(VillagerHouseTex *o);
#endif
#ifndef PROTO_LOCAL_VillagerHouseTex_GetDoorOutAnim
void *VillagerHouseTex_GetDoorOutAnim(VillagerHouseTex *o);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_Clear
void HouseLightUpDeco_Clear(HouseLightUpDeco *o);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_Load
s32 HouseLightUpDeco_Load(HouseLightUpDeco *r);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_Release
void HouseLightUpDeco_Release(HouseLightUpDeco *p);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_GetTex
void *HouseLightUpDeco_GetTex(HouseLightUpDeco *p);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_GetModel
void *HouseLightUpDeco_GetModel(HouseLightUpDeco *r, u32 idx);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_GetTexPattern
void *HouseLightUpDeco_GetTexPattern(HouseLightUpDeco *r);
#endif
#ifndef PROTO_LOCAL_HouseLightUpDeco_IsLoaded
u8 HouseLightUpDeco_IsLoaded(HouseLightUpDeco *r);
#endif
#ifndef PROTO_LOCAL_PlayerHouseTex_Load
s32 PlayerHouseTex_Load(PlayerHouseTex *self);
#endif
#ifndef PROTO_LOCAL_PlayerHouseTex_Release
void PlayerHouseTex_Release(PlayerHouseTex *p);
#endif
}
#endif

#endif

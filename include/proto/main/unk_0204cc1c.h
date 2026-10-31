#ifndef PROTO_PROTO_MAIN_UNK_0204CC1C_H
#define PROTO_PROTO_MAIN_UNK_0204CC1C_H


#include "types.h"
#include "town/MapBlockEntry.h"
struct FgDataIndex;
#ifndef __cplusplus
typedef struct FgDataIndex FgDataIndex;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "sys/Heap.h"
#include "town/BlockMap.h"
#include "town/MapBlock.h"
#include "town/RoomBlockMap.h"
#include "town/TownBlockMap.h"
#include "town/TownMap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BlockMap_DebugStub
void BlockMap_DebugStub();
#endif
#ifndef PROTO_LOCAL_MapBlockEntry_NewArray
MapBlockEntry *MapBlockEntry_NewArray(s32 n, void *heap);
#endif
#ifndef PROTO_LOCAL_FieldUnit_FromBlockUnit
void FieldUnit_FromBlockUnit(s32 *ox, s32 *oz, s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_ItemGrid_Clear
void ItemGrid_Clear(u16 *p);
#endif
#ifndef PROTO_LOCAL_TownBlockMap_Create
BOOL TownBlockMap_Create(void *heap);
#endif
#ifndef PROTO_LOCAL_TownBlockMap_Destroy
void TownBlockMap_Destroy(void *heap);
#endif
#ifndef PROTO_LOCAL_HouseRoomMaps_Create
BOOL HouseRoomMaps_Create(void *heap);
#endif
#ifndef PROTO_LOCAL_HouseRoomMaps_Destroy
void HouseRoomMaps_Destroy(void *heap);
#endif
#ifndef PROTO_LOCAL_HouseRoomMaps_UpdateAll
void HouseRoomMaps_UpdateAll();
#endif
#ifndef PROTO_LOCAL_HouseRoomMaps_BindBg
void HouseRoomMaps_BindBg();
#endif
#ifndef PROTO_LOCAL_VillagerRoom_BuildEntry
MapBlockEntry *VillagerRoom_BuildEntry(u16 *dst, u32 b, void *heap);
#endif
#ifndef PROTO_LOCAL_VillagerRoom_LoadLayout
BOOL VillagerRoom_LoadLayout(u16 *dst, u32 b, void *heap);
#endif
#ifndef PROTO_LOCAL_VillagerRoomMap_Destroy
void VillagerRoomMap_Destroy(void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_Load
BOOL FgData_Load(void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_Unload
void FgData_Unload(void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_HasLayout
BOOL FgData_HasLayout(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_ItemGrid_Alloc
u16 *ItemGrid_Alloc(void *heap, s32 align);
#endif
#ifndef PROTO_LOCAL_FgData_ApplyLayoutGlobal
BOOL FgData_ApplyLayoutGlobal(u16 *dst, s32 i, s32 j, void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_CreateLayoutGrid
u16 *FgData_CreateLayoutGrid(s32 a, s32 b, void *heap, s32 d);
#endif
#ifndef PROTO_LOCAL_FgData_GetVillagerLayout
void *FgData_GetVillagerLayout(s32 *count, s32 villager, void *heap);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_FieldPos_ToBlockUnit
void FieldPos_ToBlockUnit(s32 *ax, s32 *az, s32 *cx, s32 *cz, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FieldPos_ToBlockUnit2
void FieldPos_ToBlockUnit2(s32 *a, s32 *c, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FieldPos_ToUnit
void FieldPos_ToUnit(s32 *ox, s32 *oz, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_FieldPos_SnapToUnitCenter
void FieldPos_SnapToUnitCenter(VecFx32 *dst, VecFx32 *src);
#endif
#ifndef PROTO_LOCAL_FieldPos_FromBlockUnitCenter
void FieldPos_FromBlockUnitCenter(VecFx32 *v, s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_FieldPos_FromUnitCenter
void FieldPos_FromUnitCenter(VecFx32 *v, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_FieldPos_FromBlockUnit
void FieldPos_FromBlockUnit(VecFx32 *v, s32 a, s32 b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_BlockMap_FindBlockAllAttr
MapBlock *BlockMap_FindBlockAllAttr(BlockMap *g, s32 filter);
#endif
#ifndef PROTO_LOCAL_BlockMap_FindBlockAnyAttr
MapBlock *BlockMap_FindBlockAnyAttr(BlockMap *g, s32 filter);
#endif
#ifndef PROTO_LOCAL_BlockMap_GetBlockAttr
s32 BlockMap_GetBlockAttr(BlockMap *g, s32 hx, s32 hy);
#endif
#ifndef PROTO_LOCAL_BlockMap_BlockHasAllAttr
BOOL BlockMap_BlockHasAllAttr(BlockMap *g, s32 hx, s32 hy, s32 a);
#endif
#ifndef PROTO_LOCAL_BlockMap_GetItemPtr
u16 *BlockMap_GetItemPtr(BlockMap *g, s32 hx, s32 hy, s32 lx, s32 ly, u8 layer);
#endif
#ifndef PROTO_LOCAL_BlockMap_GetItemPtrAtPos
u16 *BlockMap_GetItemPtrAtPos(BlockMap *g, VecFx32 *v, u8 layer);
#endif
#ifndef PROTO_LOCAL_BlockMap_SetItem
BOOL BlockMap_SetItem(BlockMap *g, u16 *a, u32 hx, u32 hy, u32 lx, u32 ly, u8 d);
#endif
#ifndef PROTO_LOCAL_BlockMap_SetItemAtUnit
BOOL BlockMap_SetItemAtUnit(BlockMap *g, u16 *a, s32 x, s32 z, u8 d);
#endif
#ifndef PROTO_LOCAL_BlockMap_FindItemAllAttr
BOOL BlockMap_FindItemAllAttr(BlockMap *g, s32 *outx, s32 *outz, s32 *a3, s32 *p4, u16 *p5, u16 *p6, s32 filter, u8 p8);
#endif
#ifndef PROTO_LOCAL_BlockMap_FindItemAnyAttr
BOOL BlockMap_FindItemAnyAttr(BlockMap *g, s32 *outx, s32 *outz, s32 *a3, s32 *p4, u16 *p5, u16 *p6, s32 filter, u8 p8);
#endif
#ifndef PROTO_LOCAL_BlockMap_SetBuried
s32 BlockMap_SetBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly);
#endif
#ifndef PROTO_LOCAL_BlockMap_SetBuriedAtUnit
s32 BlockMap_SetBuriedAtUnit(BlockMap *g, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_BlockMap_ClearBuried
s32 BlockMap_ClearBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly);
#endif
#ifndef PROTO_LOCAL_BlockMap_ClearBuriedAtUnit
s32 BlockMap_ClearBuriedAtUnit(BlockMap *g, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_BlockMap_IsBuried
s32 BlockMap_IsBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly);
#endif
#ifndef PROTO_LOCAL_BlockMap_IsBuriedAtUnit
s32 BlockMap_IsBuriedAtUnit(BlockMap *g, s32 x, s32 z);
#endif
#ifndef PROTO_LOCAL_BlockMap_IsBuriedAtPos
s32 BlockMap_IsBuriedAtPos(BlockMap *g, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_TownMap_HasEnoughSigns
BOOL TownMap_HasEnoughSigns(TownMap *o);
#endif
#ifndef PROTO_LOCAL_TownMap_HasEnoughRocks
BOOL TownMap_HasEnoughRocks(TownMap *o);
#endif
#ifndef PROTO_LOCAL_TownMap_ApplyAcreLayouts
void TownMap_ApplyAcreLayouts(TownMap *o, Heap *heap);
#endif
#ifndef PROTO_LOCAL_TownMap_Generate
void TownMap_Generate(TownMap *o, Heap *heap);
#endif
#ifndef PROTO_LOCAL_TownMap_GetAcres
u8 *TownMap_GetAcres(TownMap *p);
#endif
#ifndef PROTO_LOCAL_AcreItemGrid_Get
u16 *AcreItemGrid_Get(AcreItemGrid *p);
#endif
#ifndef PROTO_LOCAL_TownBlockMap_Get
TownBlockMap *TownBlockMap_Get();
#endif
#ifndef PROTO_LOCAL_BlockMap_PutStructure
BOOL BlockMap_PutStructure(BlockMap *a, u16 *b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_BlockMap_RemoveStructure
BOOL BlockMap_RemoveStructure(BlockMap *a, s32 b, s32 c, u16 *d);
#endif
#ifndef PROTO_LOCAL_BlockMap_RemoveStructureAt
BOOL BlockMap_RemoveStructureAt(BlockMap *a, s32 b, s32 c, s32 d, s32 e, u16 *f);
#endif
#ifndef PROTO_LOCAL_BlockMap_FindItem
void BlockMap_FindItem(u16 *ret, BlockMap *m, VecFx32 *pos, s32 *p4, s32 *p5, u16 a6, u16 a7, s32 a8);
#endif
#ifndef PROTO_LOCAL_BlockMap_FindStructure
void BlockMap_FindStructure(u16 *ret, BlockMap *m, VecFx32 *pos, s32 *p4, s32 *p5, u16 a6, u16 a7, s32 a8);
#endif
#ifndef PROTO_LOCAL_Town_FindTownHall
BOOL Town_FindTownHall(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4);
#endif
#ifndef PROTO_LOCAL_Town_FindPlayerHouse
BOOL Town_FindPlayerHouse(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4);
#endif
#ifndef PROTO_LOCAL_Town_FindGateHouse
BOOL Town_FindGateHouse(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4);
#endif
#ifndef PROTO_LOCAL_Town_FindTownHallFront
BOOL Town_FindTownHallFront(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4);
#endif
#ifndef PROTO_LOCAL_Town_FindGulliverShip
BOOL Town_FindGulliverShip(BlockMap *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_HouseRoomMap_Clear
void HouseRoomMap_Clear(RoomBlockMap *p);
#endif
#ifndef PROTO_LOCAL_HouseRoomMaps_Get
RoomBlockMap *HouseRoomMaps_Get(s32 i);
#endif
#ifndef PROTO_LOCAL_HouseRoomMaps_GetForScene
RoomBlockMap *HouseRoomMaps_GetForScene(s32 a);
#endif
#ifndef PROTO_LOCAL_HouseRoomMap_Update
void HouseRoomMap_Update(RoomBlockMap *p, s32 i);
#endif
#ifndef PROTO_LOCAL_HouseRoomMap_BindBg
void HouseRoomMap_BindBg(RoomBlockMap *p);
#endif
#ifndef PROTO_LOCAL_HouseRoomMap_ReleaseBg
void HouseRoomMap_ReleaseBg(RoomBlockMap *p);
#endif
#ifndef PROTO_LOCAL_HouseRoomMap_Init
BOOL HouseRoomMap_Init(RoomBlockMap *p, s32 i, void *heap);
#endif
#ifndef PROTO_LOCAL_HouseRoomMap_FreeBlocks
void HouseRoomMap_FreeBlocks(RoomBlockMap *p, void *heap);
#endif
#ifndef PROTO_LOCAL_VillagerRoomMap_Clear
void VillagerRoomMap_Clear(RoomBlockMap *p);
#endif
#ifndef PROTO_LOCAL_VillagerRoomMap_Init
BOOL VillagerRoomMap_Init(RoomBlockMap *p, u32 a, void *heap);
#endif
#ifndef PROTO_LOCAL_VillagerRoomMap_Create
RoomBlockMap *VillagerRoomMap_Create(u32 a, void *heap);
#endif
#ifndef PROTO_LOCAL_VillagerRoomMap_Free
void VillagerRoomMap_Free(RoomBlockMap *p, void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_ClearIndices
void FgData_ClearIndices(FgDataIndex *t);
#endif
#ifndef PROTO_LOCAL_FgData_LoadIndices
BOOL FgData_LoadIndices(FgDataIndex *t, void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_FreeIndices
void FgData_FreeIndices(FgDataIndex *t, void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_IsValidTable
BOOL FgData_IsValidTable(FgDataIndex *t, s32 i);
#endif
#ifndef PROTO_LOCAL_FgData_GetLayoutOffset
s32 FgData_GetLayoutOffset(FgDataIndex *t, s32 i, s32 j);
#endif
#ifndef PROTO_LOCAL_FgData_GetLayoutSize
s32 FgData_GetLayoutSize(FgDataIndex *t, s32 i, s32 j);
#endif
#ifndef PROTO_LOCAL_FgData_ReadLayout
BOOL FgData_ReadLayout(FgDataIndex *t, void *dst, s32 i, s32 j, s32 n);
#endif
#ifndef PROTO_LOCAL_FgData_ApplyLayout
BOOL FgData_ApplyLayout(FgDataIndex *t, u16 *dst, s32 i, s32 j, void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_ReadLayoutEntries
void *FgData_ReadLayoutEntries(FgDataIndex *t, s32 *b, s32 c, s32 d, void *heap);
#endif
#ifndef PROTO_LOCAL_FgData_ReadVillagerLayout
void *FgData_ReadVillagerLayout(FgDataIndex *a, s32 *b, s32 c, void *d);
#endif
}
#ifndef PROTO_LOCAL_sFgDataFoIndexPath
extern char sFgDataFoIndexPath[];
#endif
#ifndef PROTO_LOCAL_gFgDataIndex
extern FgDataIndex *gFgDataIndex;
#endif
#ifndef PROTO_LOCAL_sFgDataNfPath
extern char sFgDataNfPath[];
#endif
#ifndef PROTO_LOCAL_gTownBlockMap
extern TownBlockMap *gTownBlockMap;
#endif
#ifndef PROTO_LOCAL_sFgDataFiPath
extern char sFgDataFiPath[];
#endif
#ifndef PROTO_LOCAL_sFgDataNrPath
extern char sFgDataNrPath[];
#endif
#ifndef PROTO_LOCAL_sFgDataNrIndexPath
extern char sFgDataNrIndexPath[];
#endif
#ifndef PROTO_LOCAL_gVillagerRoomMap
extern RoomBlockMap *gVillagerRoomMap;
#endif
#ifndef PROTO_LOCAL_sFgDataFoPath
extern char sFgDataFoPath[];
#endif
#ifndef PROTO_LOCAL_sFgDataFiIndexPath
extern char sFgDataFiIndexPath[];
#endif
#ifndef PROTO_LOCAL_sFgDataNfIndexPath
extern char sFgDataNfIndexPath[];
#endif
#ifndef PROTO_LOCAL_gHouseRoomMaps
extern RoomBlockMap *gHouseRoomMaps[5];
#endif
#endif

#endif

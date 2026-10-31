#ifndef PROTO_PROTO_MAIN_UNK_02077AC4_H
#define PROTO_PROTO_MAIN_UNK_02077AC4_H


#include "types.h"
#include "sys/ClockDateTime.h"
struct ClockDateTimeRaw;
struct HousePos;
struct NpcTexPatBufPool;
struct SpNpcAnimHeapPool;
struct VillagerAnimHeapPool;
#ifndef __cplusplus
typedef struct ClockDateTimeRaw ClockDateTimeRaw;
typedef struct HousePos HousePos;
typedef struct NpcTexPatBufPool NpcTexPatBufPool;
typedef struct SpNpcAnimHeapPool SpNpcAnimHeapPool;
typedef struct VillagerAnimHeapPool VillagerAnimHeapPool;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#include "npc/ErrandRecord.h"
#include "npc/SickVillagerRecord.h"
#include "npc/VillagerDataItemView.h"
#include "npc/VillagerId.h"
#include "npc/VillagerState.h"
#include "npc/VillagerStateTable.h"
#include "player/PlayerErrands.h"
#include "player/PlayerId.h"
#include "save/TownId.h"
#include "save/VillagerData.h"
#include "talk/EncodedString.h"
#include "talk/EncodedString10.h"
#include "talk/MsgString.h"
#include "town/BlockMap.h"
class PlayerData;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sVillagerLetterPath
extern u8 sVillagerLetterPath[0x28];
#endif
#ifndef PROTO_LOCAL_VillagerInfo_Get
const u8 *VillagerInfo_Get(u32 n);
#endif
#ifndef PROTO_LOCAL_SpNpc_GetInfo
const u8 *SpNpc_GetInfo(u16 *p);
#endif
#ifndef PROTO_LOCAL_Npc_GetVoiceType
u32 Npc_GetVoiceType(u16 *p);
#endif
#ifndef PROTO_LOCAL_Npc_GetInfoByte2
u32 Npc_GetInfoByte2(u16 *p);
#endif
#ifndef PROTO_LOCAL_SpNpc_GetInfoByte0
s32 SpNpc_GetInfoByte0(u16 *p);
#endif
#ifndef PROTO_LOCAL_FurnitureTaste_GetTextIndex
u8 FurnitureTaste_GetTextIndex(u8 *p);
#endif
#ifndef PROTO_LOCAL_Date_GetStarSign
u32 Date_GetStarSign(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Date_GetStarSignOf
u32 Date_GetStarSignOf(const u8 *p);
#endif
#ifndef PROTO_LOCAL_Town_GetMaxOutdoorVillagers
u32 Town_GetMaxOutdoorVillagers();
#endif
#ifndef PROTO_LOCAL_Personality_GetSleepHours
const u8 *Personality_GetSleepHours(u32 idx);
#endif
#ifndef PROTO_LOCAL_Personality_IsAsleep
BOOL Personality_IsAsleep(u32 idx, ClockDateTime *buf);
#endif
#ifndef PROTO_LOCAL_HousePos_Clear
void HousePos_Clear(u8 *p);
#endif
#ifndef PROTO_LOCAL_HousePos_IsValid
BOOL HousePos_IsValid(u8 *p);
#endif
#ifndef PROTO_LOCAL_HousePos_Set
void HousePos_Set(u8 *p, u8 a, u8 b);
#endif
#ifndef PROTO_LOCAL_HousePos_SetFromUnit
void HousePos_SetFromUnit(u8 *out, s32 *in);
#endif
#ifndef PROTO_LOCAL_Villager_GetDefaultShirt
void Villager_GetDefaultShirt(u16 *out, void *idx);
#endif
#ifndef PROTO_LOCAL_Villager_GetDefaultUmbrella
void Villager_GetDefaultUmbrella(u16 *out, void *idx);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_IsFormerResident
s32 VillagerMemory_IsFormerResident(void *a, void *townId, void *players);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_IsOtherTown
s32 VillagerMemory_IsOtherTown(void *a, u16 *p, void *c);
#endif
#ifndef PROTO_LOCAL_Villager_IsMoreAttachedThan
BOOL Villager_IsMoreAttachedThan(void *a, void *b, ClockDateTime *c);
#endif
#ifndef PROTO_LOCAL_Villager_GetNicknameFor
void Villager_GetNicknameFor(void *a, void *b, void *c);
#endif
#ifndef PROTO_LOCAL_Villager_DiscardItem
BOOL Villager_DiscardItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Villager_DiscardItemMaybe
BOOL Villager_DiscardItemMaybe(u16 *p);
#endif
#ifndef PROTO_LOCAL_Villager_GetPackedFurniture
void Villager_GetPackedFurniture(u16 *out, void *a, u16 *in);
#endif
#ifndef PROTO_LOCAL_Villager_IsHouseAvailable
BOOL Villager_IsHouseAvailable();
#endif
#ifndef PROTO_LOCAL_Villager_ClearTalkedToday
void Villager_ClearTalkedToday(u8 *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_IsValidIndex
BOOL SaveVillagers_IsValidIndex(u32 n);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_IsOccupied
BOOL SaveVillagers_IsOccupied(u8 *base, s32 idx);
#endif
#ifndef PROTO_LOCAL_Text_TrimmedLength
s32 Text_TrimmedLength(u8 *s, s32 n);
#endif
#ifndef PROTO_LOCAL_Mem_Equal
BOOL Mem_Equal(u8 *a, u8 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindByName
u8 *SaveVillagers_FindByName(u8 *base, u8 *a1, s32 a2, void *a3);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_GetByHouseRoom
void *SaveVillagers_GetByHouseRoom(void *self, u32 x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindFreeSlot
s32 SaveVillagers_FindFreeSlot(void *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickRandomExcept
void *SaveVillagers_PickRandomExcept(u8 *base, void **arr, s32 n);
#endif
#ifndef PROTO_LOCAL_Random_PickSetBit
s32 Random_PickSetBit(u32 mask, s32 cnt, s32 n);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickRandomTalkPartner
void *SaveVillagers_PickRandomTalkPartner(u8 *base, void **arr, s32 n);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindBestFriendOf
void *SaveVillagers_FindBestFriendOf(u8 *base, void *x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_CountImpl
s32 SaveVillagers_CountImpl(u8 *base);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_Count
s32 SaveVillagers_Count(u8 *base);
#endif
#ifndef PROTO_LOCAL_SpeciesBits_Test
BOOL SpeciesBits_Test(s32 n, u32 *bits);
#endif
#ifndef PROTO_LOCAL_SpeciesBits_Set
void SpeciesBits_Set(u32 *bits, s32 n);
#endif
#ifndef PROTO_LOCAL_SpeciesBits_AllEligibleSet
BOOL SpeciesBits_AllEligibleSet(u32 *bits);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PlaceMissingHouses
void SaveVillagers_PlaceMissingHouses(u8 *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_GetRelationLevel
u32 SaveVillagers_GetRelationLevel(u8 *self, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_GetRelationLevelOf
s32 SaveVillagers_GetRelationLevelOf(u8 *self, u8 *p1, u8 *p2);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_AddRelation
void SaveVillagers_AddRelation(u8 *self, u8 *a, u8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindByRelation
u8 *SaveVillagers_FindByRelation(u8 *self, u8 *p, BOOL (**cmp)(s32, s32), s32 best);
#endif
#ifndef PROTO_LOCAL_Relation_IsHigher
BOOL Relation_IsHigher(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Relation_IsLower
BOOL Relation_IsLower(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindFriendOf
u8 *SaveVillagers_FindFriendOf(u8 *self, u8 *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindEnemyOf
u8 *SaveVillagers_FindEnemyOf(u8 *self, u8 *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ShouldAssignErrands
BOOL SaveVillagers_ShouldAssignErrands(u8 *self);
#endif
#ifndef PROTO_LOCAL_VillagerStates_ResetErrands
void VillagerStates_ResetErrands();
#endif
#ifndef PROTO_LOCAL_SaveVillagers_AssignErrands
void SaveVillagers_AssignErrands(void *bb);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateErrands
void SaveVillagers_UpdateErrands(u8 *b);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdatePlayerErrandKind15
void SaveVillagers_UpdatePlayerErrandKind15(void *unused, ClockDateTime *q);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_DailyVillagerUpdate
void SaveVillagers_DailyVillagerUpdate(u8 *p, s32 q);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_GetUnk3830Index
s32 SaveVillagers_GetUnk3830Index(void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickSickVillager
s32 SaveVillagers_PickSickVillager(void *pp, u32 idx);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_CanSomeoneGetSick
BOOL SaveVillagers_CanSomeoneGetSick(u8 *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_AdvanceSickDay
void SaveVillagers_AdvanceSickDay(void *pp);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateSickVillager
void SaveVillagers_UpdateSickVillager(u8 *b);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickGreeter
void SaveVillagers_PickGreeter(u8 *base);
#endif
#ifndef PROTO_LOCAL_VillagerEvent_GetTodayIndex
s32 VillagerEvent_GetTodayIndex();
#endif
#ifndef PROTO_LOCAL_VillagerEvent_FindUpcomingIndex
s32 VillagerEvent_FindUpcomingIndex(u32 n, void *src);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_InitTalkUrges
void SaveVillagers_InitTalkUrges(u8 *p, void *q);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_DoubleTalkUrges
void SaveVillagers_DoubleTalkUrges(u8 *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ApplyBadFortune
void SaveVillagers_ApplyBadFortune(void *self0);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_GiveFortuneGreeting
void SaveVillagers_GiveFortuneGreeting(void *self0, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ApplyGoodFortune
void SaveVillagers_ApplyGoodFortune(u8 *self, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateRoomInfo
void SaveVillagers_UpdateRoomInfo(void *self, s32 idx);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateAllRoomInfo
void SaveVillagers_UpdateAllRoomInfo(void *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ResetMoods
void SaveVillagers_ResetMoods(u8 *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateBirthdayNotices
void SaveVillagers_UpdateBirthdayNotices(u8 *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickBirthdayGuest
s32 SaveVillagers_PickBirthdayGuest(void *self0, s32 x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindBirthdayVillager
s32 SaveVillagers_FindBirthdayVillager(void *self0, void *p0);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateBirthdayParty
void SaveVillagers_UpdateBirthdayParty(u8 *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ApplyBirthdayParty
void SaveVillagers_ApplyBirthdayParty(u8 *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickFleaMarketBuyer
s32 SaveVillagers_PickFleaMarketBuyer(void *self0);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickFleaMarketBuyerNow
void SaveVillagers_PickFleaMarketBuyerNow(void *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindBestFriendIndexOf
s32 SaveVillagers_FindBestFriendIndexOf(void *self0, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickPlayerBirthdayVisitor
void SaveVillagers_PickPlayerBirthdayVisitor(u8 *self, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_AllKnowPlayer
BOOL SaveVillagers_AllKnowPlayer(u8 *self, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_DeliverLetter
s32 SaveVillagers_DeliverLetter(void *self, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ClearTalkedToday
void SaveVillagers_ClearTalkedToday(u8 *p);
#endif
#ifndef PROTO_LOCAL_VillagerFlea_GetMonthlyChance
s32 VillagerFlea_GetMonthlyChance();
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Destruct
void OutdoorSchedule_Destruct();
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_ClearOrder
void OutdoorSchedule_ClearOrder(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_CopyOrder
void OutdoorSchedule_CopyOrder(void *a, void *b, void *c);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_SetOrderEntry
BOOL OutdoorSchedule_SetOrderEntry(u8 *self, s32 a, s32 v);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_AddToOrder
void OutdoorSchedule_AddToOrder(s8 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_RemoveFromOrder
void OutdoorSchedule_RemoveFromOrder(s8 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_InitOrder
void OutdoorSchedule_InitOrder(s8 *out, u8 *p);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_Construct
void VillagerRelations_Construct();
#endif
#ifndef PROTO_LOCAL_VillagerRelations_Destruct
void VillagerRelations_Destruct();
#endif
#ifndef PROTO_LOCAL_VillagerRelations_Clear
void VillagerRelations_Clear(void *p);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_IsValidIndex
BOOL VillagerRelations_IsValidIndex(void *a, u32 i);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_PairIndex
s32 VillagerRelations_PairIndex(s8 *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_ResetSlot
void VillagerRelations_ResetSlot(s8 *a, s32 x);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_AddAt
void VillagerRelations_AddAt(s8 *a, s32 i, s32 d);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_Add
void VillagerRelations_Add(s8 *a, s32 p, s32 q, s32 r);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_GetStored
s32 VillagerRelations_GetStored(s8 *a, s32 p, s32 q);
#endif
#ifndef PROTO_LOCAL_Relation_GetPersonalityScore
s32 Relation_GetPersonalityScore(void *a, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Relation_GetStarElementScore
u32 Relation_GetStarElementScore(void *a, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Relation_GetSpeciesScore
u32 Relation_GetSpeciesScore(void *a, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Relation_GetInfoBonus
u32 Relation_GetInfoBonus(void *a, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Relation_GetInfo04Diff
u32 Relation_GetInfo04Diff(void *a, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Relation_CalcBaseScore
s32 Relation_CalcBaseScore(void *a, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_VillagerRelations_GetScore
s32 VillagerRelations_GetScore(void *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_VillagerTransfer_ConstructVillager
void *VillagerTransfer_ConstructVillager(void *p);
#endif
#ifndef PROTO_LOCAL_VillagerTransfer_DestructVillager
void *VillagerTransfer_DestructVillager(void *p);
#endif
#ifndef PROTO_LOCAL_func_020789a8
void *func_020789a8(void *p);
#endif
#ifndef PROTO_LOCAL_Villager_IsActorInBox
BOOL Villager_IsActorInBox(u16 *h, s32 x0, s32 x1, s32 z0, s32 z1);
#endif
#ifndef PROTO_LOCAL_VillagerTrend_OnClothesBought
void VillagerTrend_OnClothesBought();
#endif
#ifndef PROTO_LOCAL_VillagerTrend_OnFurnitureBought
void VillagerTrend_OnFurnitureBought();
#endif
#ifndef PROTO_LOCAL_VillagerTrend_NotifyIdle
void VillagerTrend_NotifyIdle();
#endif
#ifndef PROTO_LOCAL_VillagerTrend_TickIdle
void VillagerTrend_TickIdle();
#endif
#ifndef PROTO_LOCAL_VillagerStates_IsValidIndex
BOOL VillagerStates_IsValidIndex(s32 i);
#endif
#ifndef PROTO_LOCAL_VillagerStateTable_Destroy
void VillagerStateTable_Destroy();
#endif
#ifndef PROTO_LOCAL_VillagerStates_Init
void VillagerStates_Init();
#endif
#ifndef PROTO_LOCAL_VillagerStates_Destroy
void VillagerStates_Destroy();
#endif
#ifndef PROTO_LOCAL_VillagerStates_ResetRuntime
void VillagerStates_ResetRuntime();
#endif
#ifndef PROTO_LOCAL_VillagerStates_ClearUnk1dBit0
void VillagerStates_ClearUnk1dBit0();
#endif
#ifndef PROTO_LOCAL_VillagerStates_ClearUnk1dBit2
void VillagerStates_ClearUnk1dBit2();
#endif
#ifndef PROTO_LOCAL_VillagerStates_ResetTalkRepeats
void VillagerStates_ResetTalkRepeats();
#endif
#ifndef PROTO_LOCAL_VillagerStates_ClearFleaVillager
void VillagerStates_ClearFleaVillager();
#endif
#ifndef PROTO_LOCAL_VillagerStates_SetBirthdayHost
void VillagerStates_SetBirthdayHost(s32 v);
#endif
#ifndef PROTO_LOCAL_VillagerStates_GetBirthdayHost
s32 VillagerStates_GetBirthdayHost();
#endif
#ifndef PROTO_LOCAL_VillagerStates_SetBirthdayGuest
void VillagerStates_SetBirthdayGuest(s32 v);
#endif
#ifndef PROTO_LOCAL_VillagerStates_GetBirthdayGuest
s32 VillagerStates_GetBirthdayGuest();
#endif
#ifndef PROTO_LOCAL_VillagerStates_SetBirthdayVisitor
void VillagerStates_SetBirthdayVisitor(s32 v);
#endif
#ifndef PROTO_LOCAL_VillagerStates_GetBirthdayVisitor
s32 VillagerStates_GetBirthdayVisitor();
#endif
#ifndef PROTO_LOCAL_VillagerStates_SetFleaMarketBuyer
void VillagerStates_SetFleaMarketBuyer(s32 v);
#endif
#ifndef PROTO_LOCAL_VillagerStates_GetFleaMarketBuyer
s32 VillagerStates_GetFleaMarketBuyer();
#endif
#ifndef PROTO_LOCAL_VillagerStates_ResetIdleFrames
void VillagerStates_ResetIdleFrames();
#endif
#ifndef PROTO_LOCAL_SaveVillagers_OnNewDay
void SaveVillagers_OnNewDay(u8 *a, void *b);
#endif
#ifndef PROTO_LOCAL_Field_FindPlayerAtUnit
void *Field_FindPlayerAtUnit(s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_Field_IsUnitOccupied
BOOL Field_IsUnitOccupied(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_TownMap_FindBuildingAbove
BOOL TownMap_FindBuildingAbove(s32 x, s32 y, s32 h, s32 *px, s32 *py);
#endif
#ifndef PROTO_LOCAL_NpcHeapPools_CreateAll
void NpcHeapPools_CreateAll();
#endif
#ifndef PROTO_LOCAL_NpcHeapPools_DestroyAll
void NpcHeapPools_DestroyAll();
#endif
#ifndef PROTO_LOCAL_NpcModelHeap_GetVillagerModelSize
s32 NpcModelHeap_GetVillagerModelSize();
#endif
#ifndef PROTO_LOCAL_NpcModelHeap_GetSpNpcModelSize
s32 NpcModelHeap_GetSpNpcModelSize();
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufs_Create
void NpcTexPatBufs_Create(void *parent);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufs_Destroy
void NpcTexPatBufs_Destroy();
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufPool_Get
void *NpcTexPatBufPool_Get(void **p, s32 i);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufPool_Alloc
void NpcTexPatBufPool_Alloc(void **p);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufPool_Free
void NpcTexPatBufPool_Free(void **p);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeaps_Create
void VillagerAnimHeaps_Create(void *parent);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeaps_Destroy
void VillagerAnimHeaps_Destroy();
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapPool_Get
void *VillagerAnimHeapPool_Get(void **p, s32 i);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapPool_Alloc
void VillagerAnimHeapPool_Alloc(void **p);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapPool_Free
void VillagerAnimHeapPool_Free(void **p);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeaps_Create
void SpNpcAnimHeaps_Create(void *parent);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeaps_Destroy
void SpNpcAnimHeaps_Destroy();
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapPool_Get
void *SpNpcAnimHeapPool_Get(void **p, s32 i);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapPool_Alloc
void SpNpcAnimHeapPool_Alloc(void **p);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapPool_Free
void SpNpcAnimHeapPool_Free(void **p);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRef_Init
void NpcTexPatBufRef_Init(s32 *p);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRef_Deinit
void NpcTexPatBufRef_Deinit();
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRef_Assign
void NpcTexPatBufRef_Assign(s32 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRef_Set
void NpcTexPatBufRef_Set(s32 *p, s32 v);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRef_LoadFile
void NpcTexPatBufRef_LoadFile(s32 *p, void *dst);
#endif
#ifndef PROTO_LOCAL_NpcTexPatBufRef_GetBuffer
void *NpcTexPatBufRef_GetBuffer(s32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapRef_Init
void VillagerAnimHeapRef_Init(s32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapRef_Deinit
void VillagerAnimHeapRef_Deinit();
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapRef_Assign
void VillagerAnimHeapRef_Assign(s32 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_VillagerAnimHeapRef_GetHeap
void *VillagerAnimHeapRef_GetHeap(s32 *p);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapRef_Init
void SpNpcAnimHeapRef_Init(s32 *p);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapRef_Deinit
void SpNpcAnimHeapRef_Deinit();
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapRef_Assign
void SpNpcAnimHeapRef_Assign(s32 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_SpNpcAnimHeapRef_GetHeap
void *SpNpcAnimHeapRef_GetHeap(s32 *p);
#endif
#ifndef PROTO_LOCAL_data_020e05ac
extern s32 data_020e05ac[3];
#endif
#ifndef PROTO_LOCAL_sErrandKindTaken
extern u8 sErrandKindTaken[0x14];
#endif
#ifndef PROTO_LOCAL_sVillagerLetter4Path
extern u8 sVillagerLetter4Path[0x28];
#endif
#ifndef PROTO_LOCAL_sErrandVillagerDone
extern u8 sErrandVillagerDone[8];
#endif
#ifndef PROTO_LOCAL_sSpeciesCandidateBits
extern u32 sSpeciesCandidateBits[5];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTransferVillager
extern VillagerData sTransferVillager;
#endif
#ifndef PROTO_LOCAL_sVillagerTrendFilters
extern Unk_0207ed1c_Fn sVillagerTrendFilters[5];
#endif
#ifndef PROTO_LOCAL_gVillagerStates
extern VillagerStateTable gVillagerStates;
#endif
#ifndef PROTO_LOCAL_sNpcTexPatBufPool
extern NpcTexPatBufPool sNpcTexPatBufPool;
#endif
#ifndef PROTO_LOCAL_sVillagerAnimHeapPool
extern VillagerAnimHeapPool sVillagerAnimHeapPool;
#endif
#ifndef PROTO_LOCAL_Villager_GetSpeciesName
BOOL Villager_GetSpeciesName(MsgString *buf, u32 x);
#endif
#ifndef PROTO_LOCAL_Npc_GetName
BOOL Npc_GetName(MsgString *self, u16 *p);
#endif
#ifndef PROTO_LOCAL_Villager_GetDefaultCatchphrase
BOOL Villager_GetDefaultCatchphrase(MsgString *buf, u32 x);
#endif
#ifndef PROTO_LOCAL_Villager_GetDefaultCatchphraseEncoded
BOOL Villager_GetDefaultCatchphraseEncoded(EncodedString *self, u32 x);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_Construct
VillagerMemory *VillagerMemory_Construct(VillagerMemory *self);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_Destruct
VillagerMemory *VillagerMemory_Destruct(VillagerMemory *self);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_Clear
void VillagerMemory_Clear(VillagerMemory *self);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_IsUsed
BOOL VillagerMemory_IsUsed(VillagerMemory *p);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_InitForPlayer
BOOL VillagerMemory_InitForPlayer(VillagerMemory *self, PlayerId *a, TownId *b, ClockDateTime *c);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_RecordTalk
void VillagerMemory_RecordTalk(VillagerMemory *self, PlayerId *a, TownId *b, ClockDateTime *c);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_GetTalkDate
ClockDateTime *VillagerMemory_GetTalkDate(VillagerMemory *p);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_UpdateTalkStreak
BOOL VillagerMemory_UpdateTalkStreak(VillagerMemory *self, ClockDateTime *p);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_AddStreakFriendship
void VillagerMemory_AddStreakFriendship(VillagerMemory *p);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_GetTownId
TownId *VillagerMemory_GetTownId(VillagerMemory *p);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_GetPlayerId
PlayerId *VillagerMemory_GetPlayerId(VillagerMemory *p);
#endif
#ifndef PROTO_LOCAL_VillagerMemory_MatchesPlayer
BOOL VillagerMemory_MatchesPlayer(PlayerId *a, PlayerId *b);
#endif
#ifndef PROTO_LOCAL_Villager_SendBirthdayLetter
void Villager_SendBirthdayLetter(VillagerData *t, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Villager_SendNewYearLetter
void Villager_SendNewYearLetter(VillagerData *t, void *p, void *q);
#endif
#ifndef PROTO_LOCAL_Villager_SendByeLetter
void Villager_SendByeLetter(VillagerData *t, void *p);
#endif
#ifndef PROTO_LOCAL_Villager_GetUmbrella
void Villager_GetUmbrella(u16 *out, VillagerData *o);
#endif
#ifndef PROTO_LOCAL_Villager_SetCatchphraseFromMsg
void Villager_SetCatchphraseFromMsg(VillagerData *a, MsgString *b);
#endif
#ifndef PROTO_LOCAL_Villager_SetCatchphraseEncoded
void Villager_SetCatchphraseEncoded(VillagerData *a, EncodedString10 *b);
#endif
#ifndef PROTO_LOCAL_Villager_SetCatchphrase
void Villager_SetCatchphrase(VillagerData *a, void *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Villager_GetBirthday
const u8 *Villager_GetBirthday(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetUpcomingBirthdayDay
s32 Villager_GetUpcomingBirthdayDay(VillagerData *a, s32 b, u8 *c);
#endif
#ifndef PROTO_LOCAL_Villager_CanAttendParty
BOOL Villager_CanAttendParty(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetStarSign
u32 Villager_GetStarSign(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetAnimalKind
u32 Villager_GetAnimalKind(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetInfoByte2
u32 Villager_GetInfoByte2(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetFashionTaste
const u8 *Villager_GetFashionTaste(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetInfo
const u8 *Villager_GetInfo(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetFurnitureTaste
const u8 *Villager_GetFurnitureTaste(VillagerData *t, u32 i);
#endif
#ifndef PROTO_LOCAL_Villager_GetFurnitureTasteScore
u8 Villager_GetFurnitureTasteScore(VillagerData *a, u16 *b);
#endif
#ifndef PROTO_LOCAL_Villager_GetInfo3a
const u8 *Villager_GetInfo3a(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_IsValidMemoryIndex
BOOL Villager_IsValidMemoryIndex(VillagerMemory *t, u32 i);
#endif
#ifndef PROTO_LOCAL_Villager_FindMemoryIndex
s32 Villager_FindMemoryIndex(VillagerMemory *t, void *id);
#endif
#ifndef PROTO_LOCAL_Villager_GetMemory
VillagerMemory *Villager_GetMemory(VillagerMemory *t, u32 i);
#endif
#ifndef PROTO_LOCAL_Villager_FindMemory
VillagerMemory *Villager_FindMemory(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_Villager_FindFreeMemoryIndex
s32 Villager_FindFreeMemoryIndex(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_FindMemoryIndexById
s32 Villager_FindMemoryIndexById(VillagerMemory *t, void *id);
#endif
#ifndef PROTO_LOCAL_Villager_GetMaxFriendship
s32 Villager_GetMaxFriendship(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_GetMinutesSinceLastTalk
s32 Villager_GetMinutesSinceLastTalk(VillagerMemory *t, ClockDateTime *o);
#endif
#ifndef PROTO_LOCAL_Villager_PickMemoryToReplace
s32 Villager_PickMemoryToReplace(VillagerMemory *t, s32 (*cb)(void *, void *, void *));
#endif
#ifndef PROTO_LOCAL_Villager_PickFormerResidentMemoryToReplace
s32 Villager_PickFormerResidentMemoryToReplace(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_PickOtherTownMemoryToReplace
s32 Villager_PickOtherTownMemoryToReplace(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_PickMemorySlotForNew
s32 Villager_PickMemorySlotForNew(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_GetMemorySlotForNew
VillagerMemory *Villager_GetMemorySlotForNew(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_FindOrCreateMemory
VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b);
#endif
#ifndef PROTO_LOCAL_Villager_CollectOtherMemories
s32 Villager_CollectOtherMemories(VillagerMemory *t, VillagerMemory **out, void *id0, s32 mode);
#endif
#ifndef PROTO_LOCAL_Villager_CountMemories
s32 Villager_CountMemories(VillagerMemory *t);
#endif
#ifndef PROTO_LOCAL_Villager_SetNicknameFromMsgFor
VillagerMemory *Villager_SetNicknameFromMsgFor(void *a, void *b, void *c);
#endif
#ifndef PROTO_LOCAL_Villager_SetNicknameFor
VillagerMemory *Villager_SetNicknameFor(void *a, void *b, u32 c, void *d);
#endif
#ifndef PROTO_LOCAL_Villagers_ShareNickname
void Villagers_ShareNickname(VillagerData *a, void *b, void *c);
#endif
#ifndef PROTO_LOCAL_Villager_PlaceItemInHouse
BOOL Villager_PlaceItemInHouse(VillagerData *a, u16 *b);
#endif
#ifndef PROTO_LOCAL_Villager_CountFurnitureLike
s32 Villager_CountFurnitureLike(VillagerData *a, u16 *b);
#endif
#ifndef PROTO_LOCAL_Villager_CountFurniture
s32 Villager_CountFurniture(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_DropRandomFurniture
void Villager_DropRandomFurniture(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_ClearFurnitureSlots1To2
void Villager_ClearFurnitureSlots1To2(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_ResolveRoomLayout
void Villager_ResolveRoomLayout(VillagerData *a, u16 *b);
#endif
#ifndef PROTO_LOCAL_Villager_PlaceReceivedItems
void Villager_PlaceReceivedItems(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_PickRoomLayout
void Villager_PickRoomLayout(VillagerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Villager_GetFurnitureSlotAt
s32 Villager_GetFurnitureSlotAt(VillagerData *a, u32 *b, u8 *c, s32 d);
#endif
#ifndef PROTO_LOCAL_Villager_RemoveFurnitureAt
BOOL Villager_RemoveFurnitureAt(VillagerData *a, u32 *b, u8 *c, s32 d);
#endif
#ifndef PROTO_LOCAL_Villager_HasShownFurnitureAt
BOOL Villager_HasShownFurnitureAt(VillagerData *a, u32 *b, u8 *c, s32 d);
#endif
#ifndef PROTO_LOCAL_Villager_GetWallpaper
u32 Villager_GetWallpaper(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetCarpet
u32 Villager_GetCarpet(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_SetWallpaper
void Villager_SetWallpaper(VillagerData *a, u8 b);
#endif
#ifndef PROTO_LOCAL_Villager_SetCarpet
void Villager_SetCarpet(VillagerData *a, u8 b);
#endif
#ifndef PROTO_LOCAL_Villager_GetInfo4d
u32 Villager_GetInfo4d(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_FindOwnIndex
s32 Villager_FindOwnIndex(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetIndex
s32 Villager_GetIndex(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetState
VillagerState *Villager_GetState(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetWhereabouts
s32 Villager_GetWhereabouts(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetPlan
void *Villager_GetPlan(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_GetTrend
s32 Villager_GetTrend(VillagerData *a, MsgString *out);
#endif
#ifndef PROTO_LOCAL_Villager_GetResidentStatus
s32 Villager_GetResidentStatus(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_IsMovingOut
BOOL Villager_IsMovingOut(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_IsMovingIn
BOOL Villager_IsMovingIn(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_IsJustMovedIn
BOOL Villager_IsJustMovedIn(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_CanBeTalkPartner
BOOL Villager_CanBeTalkPartner(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_IsInPlayerErrand
BOOL Villager_IsInPlayerErrand(VillagerData *a, PlayerErrands *b);
#endif
#ifndef PROTO_LOCAL_Villager_GetMoveInKind
u32 Villager_GetMoveInKind(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_SetMoveInKind
void Villager_SetMoveInKind(VillagerData *a, u32 b);
#endif
#ifndef PROTO_LOCAL_Villager_GetFriendName
void Villager_GetFriendName(void *a, MsgString *b);
#endif
#ifndef PROTO_LOCAL_Villager_GetEnemyName
void Villager_GetEnemyName(void *a, MsgString *b);
#endif
#ifndef PROTO_LOCAL_Villager_GetRandomOtherName
void Villager_GetRandomOtherName(VillagerData *a, MsgString *b);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_PlayerFaceFlag
BOOL ImpressionCond_PlayerFaceFlag(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WeedsAround
BOOL ImpressionCond_WeedsAround(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FlowersAround
BOOL ImpressionCond_FlowersAround(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FewVillagers
BOOL ImpressionCond_FewVillagers(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_VillagerEventToday
BOOL ImpressionCond_VillagerEventToday(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Mood1
BOOL ImpressionCond_Mood1(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Mood2or4
BOOL ImpressionCond_Mood2or4(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HoldingNet
BOOL ImpressionCond_HoldingNet(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HoldingAxe
BOOL ImpressionCond_HoldingAxe(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HoldingRod
BOOL ImpressionCond_HoldingRod(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HoldingWateringCan
BOOL ImpressionCond_HoldingWateringCan(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13c1
BOOL ImpressionCond_WearingHat13c1(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13b2
BOOL ImpressionCond_WearingHat13b2(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13a8
BOOL ImpressionCond_WearingHat13a8(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13bc
BOOL ImpressionCond_WearingHat13bc(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat1405
BOOL ImpressionCond_WearingHat1405(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13e6
BOOL ImpressionCond_WearingHat13e6(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13ea
BOOL ImpressionCond_WearingHat13ea(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13f5
BOOL ImpressionCond_WearingHat13f5(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13e3
BOOL ImpressionCond_WearingHat13e3(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat13e4
BOOL ImpressionCond_WearingHat13e4(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingHat1406
BOOL ImpressionCond_WearingHat1406(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FlowerAccessory
BOOL ImpressionCond_FlowerAccessory(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HoldingUmbrella
BOOL ImpressionCond_HoldingUmbrella(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Raining
BOOL ImpressionCond_Raining(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Snowing
BOOL ImpressionCond_Snowing(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_WearingShirt12a8
BOOL ImpressionCond_WearingShirt12a8(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_TimeOfDay0
BOOL ImpressionCond_TimeOfDay0(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_TimeOfDay3
BOOL ImpressionCond_TimeOfDay3(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_PocketsFull
BOOL ImpressionCond_PocketsFull(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FriendshipVeryLow
BOOL ImpressionCond_FriendshipVeryLow(PlayerData *a, s32 b, s32);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FriendshipLow
BOOL ImpressionCond_FriendshipLow(PlayerData *a, s32 b, s32);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FriendshipHigh
BOOL ImpressionCond_FriendshipHigh(PlayerData *a, s32 b, s32);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FriendshipVeryHigh
BOOL ImpressionCond_FriendshipVeryHigh(PlayerData *a, s32 b, s32);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HalfInsectsCaught
BOOL ImpressionCond_HalfInsectsCaught(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_AllInsectsCaught
BOOL ImpressionCond_AllInsectsCaught(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_HalfFishCaught
BOOL ImpressionCond_HalfFishCaught(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_AllFishCaught
BOOL ImpressionCond_AllFishCaught(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_BellsUpTo300
BOOL ImpressionCond_BellsUpTo300(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_BellsUpTo1000
BOOL ImpressionCond_BellsUpTo1000(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Bells10000To20000
BOOL ImpressionCond_Bells10000To20000(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Bells20000To40000
BOOL ImpressionCond_Bells20000To40000(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Bells40000To60000
BOOL ImpressionCond_Bells40000To60000(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_BellsOver60000
BOOL ImpressionCond_BellsOver60000(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_AccessoryHairD
BOOL ImpressionCond_AccessoryHairD(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_AccessoryHairC
BOOL ImpressionCond_AccessoryHairC(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_AccessoryHairB
BOOL ImpressionCond_AccessoryHairB(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_AccessoryHairA
BOOL ImpressionCond_AccessoryHairA(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair0
BOOL ImpressionCond_Hair0(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair1
BOOL ImpressionCond_Hair1(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair2
BOOL ImpressionCond_Hair2(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair3
BOOL ImpressionCond_Hair3(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair4
BOOL ImpressionCond_Hair4(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair5
BOOL ImpressionCond_Hair5(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair6
BOOL ImpressionCond_Hair6(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Hair7
BOOL ImpressionCond_Hair7(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_ImpressionCond_FourResidents
BOOL ImpressionCond_FourResidents(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_TwoPlusResidents
BOOL ImpressionCond_TwoPlusResidents(PlayerData *a, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Winter
BOOL ImpressionCond_Winter(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Autumn
BOOL ImpressionCond_Autumn(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Summer
BOOL ImpressionCond_Summer(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_ImpressionCond_Always
BOOL ImpressionCond_Always(PlayerData *, s32, s32 );
#endif
#ifndef PROTO_LOCAL_Impression_Evaluate
u32 Impression_Evaluate(PlayerData *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Villager_UpdateImpression
u32 Villager_UpdateImpression(VillagerData *self, VillagerMemory *r, PlayerData *p);
#endif
#ifndef PROTO_LOCAL_Villager_GetImpressionText
void Villager_GetImpressionText(void *self, MsgString *out, PlayerData *p);
#endif
#ifndef PROTO_LOCAL_Villager_ClearReceivedItems
void Villager_ClearReceivedItems(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_GetReceivedItem
u16 *Villager_GetReceivedItem(VillagerData *self, u32 idx);
#endif
#ifndef PROTO_LOCAL_Villager_CompactReceivedItems
void Villager_CompactReceivedItems(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_AddReceivedItem
void Villager_AddReceivedItem(VillagerData *self, u16 *val);
#endif
#ifndef PROTO_LOCAL_Villager_FindReceivedItem
s32 Villager_FindReceivedItem(VillagerData *self, u16 *key);
#endif
#ifndef PROTO_LOCAL_Villager_RemoveReceivedItem
BOOL Villager_RemoveReceivedItem(VillagerData *self, u16 *key);
#endif
#ifndef PROTO_LOCAL_Villager_PickRandomReceivedItem
void Villager_PickRandomReceivedItem(u16 *out, VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_GetMostValuableReceivedItem
void Villager_GetMostValuableReceivedItem(u16 *out, VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_HasFlea
BOOL Villager_HasFlea(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_RemoveFlea
void Villager_RemoveFlea(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_IsGreeter
BOOL Villager_IsGreeter(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_GetFurnitureTasteIndex
u32 Villager_GetFurnitureTasteIndex(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_NextFurnitureTaste
void Villager_NextFurnitureTaste(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_IsFreeOfPlayerErrands
BOOL Villager_IsFreeOfPlayerErrands(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_StartMovingOut
void Villager_StartMovingOut(VillagerData *a, void *b);
#endif
#ifndef PROTO_LOCAL_Villager_StartMovingIn
void Villager_StartMovingIn(VillagerData *a, void *b);
#endif
#ifndef PROTO_LOCAL_Villager_IsMoveTimeReached
s32 Villager_IsMoveTimeReached(VillagerData *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_Villager_ShareTrendWith
void Villager_ShareTrendWith(VillagerData *a, VillagerData *b);
#endif
#ifndef PROTO_LOCAL_Villager_RecordPlayerActivity
void Villager_RecordPlayerActivity(VillagerData *a, u32 kind, s32 v);
#endif
#ifndef PROTO_LOCAL_Villager_UpdateTrendDays
void Villager_UpdateTrendDays(VillagerData *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_Villager_InitPlanDateA
void Villager_InitPlanDateA(VillagerData *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_Villager_InitPlanDateB
void Villager_InitPlanDateB(VillagerData *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_Villager_UpdatePlan
s32 Villager_UpdatePlan(VillagerData *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_Villager_UpdatePlanState
s32 Villager_UpdatePlanState(VillagerData *a, void *b, void *c, ClockDateTime *d);
#endif
#ifndef PROTO_LOCAL_Villager_UpdatePlanErrand
void Villager_UpdatePlanErrand(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_CanGoOutdoors
s32 Villager_CanGoOutdoors(VillagerData *a);
#endif
#ifndef PROTO_LOCAL_Villager_PickShownFurniture
void Villager_PickShownFurniture(VillagerData *p);
#endif
#ifndef PROTO_LOCAL_Villager_IsFurnitureShown
s32 Villager_IsFurnitureShown(VillagerData *p, s32 n);
#endif
#ifndef PROTO_LOCAL_Villager_HideFurniture
void Villager_HideFurniture(VillagerData *p, s32 n);
#endif
#ifndef PROTO_LOCAL_Villager_IsAsleep
s32 Villager_IsAsleep(VillagerData *a, ClockDateTime *b);
#endif
#ifndef PROTO_LOCAL_Villager_SetFleaMarketVisited
void Villager_SetFleaMarketVisited(VillagerData *a, void *b);
#endif
#ifndef PROTO_LOCAL_Villager_UpdateVisitorRecord
s32 Villager_UpdateVisitorRecord(VillagerData *a, void *b);
#endif
#ifndef PROTO_LOCAL_Villager_SendLetter4
s32 Villager_SendLetter4(void *a, u32 b, u32 c, void *d, VillagerId *e, u16 *f);
#endif
#ifndef PROTO_LOCAL_Villager_SendLetter
s32 Villager_SendLetter(void *a, u32 b, void *c, VillagerId *d, u16 *e);
#endif
#ifndef PROTO_LOCAL_Villager_InitTalkUrge
void Villager_InitTalkUrge(VillagerData *self, void *x);
#endif
#ifndef PROTO_LOCAL_Villager_CanSeekPlayer
BOOL Villager_CanSeekPlayer(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_RaiseTalkUrge
void Villager_RaiseTalkUrge(VillagerData *self, void *x);
#endif
#ifndef PROTO_LOCAL_Villager_IsTalkUrgeFull
BOOL Villager_IsTalkUrgeFull(VillagerData *self, void *x);
#endif
#ifndef PROTO_LOCAL_Villager_ClearTalkUrge
void Villager_ClearTalkUrge(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_HalveTalkUrge
void Villager_HalveTalkUrge(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_DoubleTalkUrge
void Villager_DoubleTalkUrge(VillagerData *self);
#endif
#ifndef PROTO_LOCAL_Villager_AddTalkUrge
void Villager_AddTalkUrge(VillagerData *self, s32 d);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_Construct
SaveVillagers *SaveVillagers_Construct(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_Destruct
SaveVillagers *SaveVillagers_Destruct(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_Clear
void SaveVillagers_Clear(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindIndex
s32 SaveVillagers_FindIndex(u8 *base, VillagerId *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_Get
VillagerData *SaveVillagers_Get(void *base, s32 idx);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_Find
u8 *SaveVillagers_Find(u8 *base, VillagerId *x);
#endif
#ifndef PROTO_LOCAL_SpeciesBits_Clear
void SpeciesBits_Clear(SaveVillagers *unused, u32 *bits, s32 n);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateHistory
void SaveVillagers_UpdateHistory(u32 *bits, SaveVillagers *p0);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickNewSpecies
s32 SaveVillagers_PickNewSpecies(SaveVillagers *self, u32 idx, s32 flag);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickRarePersonality
u32 SaveVillagers_PickRarePersonality(SaveVillagers *self, s32 mask);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_InitNewTown
void SaveVillagers_InitNewTown(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdateOutdoor
void SaveVillagers_UpdateOutdoor(SaveVillagers *self, s32 x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_IsOutdoors
s32 SaveVillagers_IsOutdoors(SaveVillagers *self, VillagerId *o);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdatePlans
void SaveVillagers_UpdatePlans(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_CanMoveIn
s32 SaveVillagers_CanMoveIn(SaveVillagers *self, ClockDateTime *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickMoveInSpecies
s32 SaveVillagers_PickMoveInSpecies(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_TryRandomMoveIn
void SaveVillagers_TryRandomMoveIn(SaveVillagers *self, ClockDateTime *out);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindBySpecies
void *SaveVillagers_FindBySpecies(SaveVillagers *self, u32 id);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_SetLastMovedIn
void SaveVillagers_SetLastMovedIn(SaveVillagers *self, s8 v);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_SetLastMovedInById
void SaveVillagers_SetLastMovedInById(SaveVillagers *self, VillagerId *o);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_MoveIn
void SaveVillagers_MoveIn(SaveVillagers *self, VillagerData *a, s32 idx, VillagerData *b, u8 c, ClockDateTime *out);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_MoveOut
void SaveVillagers_MoveOut(SaveVillagers *self, VillagerData *a, VillagerData *b, s32 idx, ClockDateTime *out);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ProcessTransfer
void SaveVillagers_ProcessTransfer(SaveVillagers *self, ClockDateTime *arg);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindMovingOut
s32 SaveVillagers_FindMovingOut(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindMovingOutDue
s32 SaveVillagers_FindMovingOutDue(SaveVillagers *self, ClockDateTime *name);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_FindJustMovedIn
s32 SaveVillagers_FindJustMovedIn(VillagerData *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ShouldStartMoveOut
BOOL SaveVillagers_ShouldStartMoveOut(SaveVillagers *self, ClockDateTime *x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickMoveOutCandidate
s32 SaveVillagers_PickMoveOutCandidate(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_TryStartMoveOut
void SaveVillagers_TryStartMoveOut(SaveVillagers *self, ClockDateTime *x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdatePlanStates
void SaveVillagers_UpdatePlanStates(SaveVillagers *self, ClockDateTimeRaw *x);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_RefreshPlanStates
void SaveVillagers_RefreshPlanStates(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_UpdatePlansNow
void SaveVillagers_UpdatePlansNow(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_DailyUpdate
void SaveVillagers_DailyUpdate(SaveVillagers *self, s32 flag);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_DailyFurnitureUpdate
void SaveVillagers_DailyFurnitureUpdate(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_HousePos_FindNthValid
s32 HousePos_FindNthValid(HousePos *p, s32 n, u32 k);
#endif
#ifndef PROTO_LOCAL_VillagerStates_GetEntry
VillagerState *VillagerStates_GetEntry(u32 a);
#endif
#ifndef PROTO_LOCAL_Villager_GetPlayerErrandKind
s32 Villager_GetPlayerErrandKind(u8 *self, u8 *p, PlayerData *r4);
#endif
#ifndef PROTO_LOCAL_Villager_GetErrandKind
s32 Villager_GetErrandKind(u8 *self, u8 *p, PlayerData *r5);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_GetUnk3830
SickVillagerRecord *SaveVillagers_GetUnk3830(void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_IsNicknameCooldownOver
BOOL SaveVillagers_IsNicknameCooldownOver(SaveVillagers *self, u8 *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_SetNicknameDate
void SaveVillagers_SetNicknameDate(SaveVillagers *self, void *p);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_ClearTuneRequester
void SaveVillagers_ClearTuneRequester(SaveVillagers *self);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_SetTuneRequester
void SaveVillagers_SetTuneRequester(SaveVillagers *self, VillagerId *u);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_IsTuneRequester
BOOL SaveVillagers_IsTuneRequester(SaveVillagers *self, VillagerId *u);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_PickFleaVillager
void SaveVillagers_PickFleaVillager(u8 *p, PlayerId *a1);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Construct
void OutdoorSchedule_Construct(OutdoorSchedule *p);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Clear
void OutdoorSchedule_Clear(OutdoorSchedule *self);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_ClearOutdoor
void OutdoorSchedule_ClearOutdoor(OutdoorSchedule *self);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_SetOutdoorSlot
BOOL OutdoorSchedule_SetOutdoorSlot(OutdoorSchedule *self, u32 i, s32 v);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_FindOutdoorSlotImpl
s32 OutdoorSchedule_FindOutdoorSlotImpl(OutdoorSchedule *self, s32 x);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_RemoveOutdoor
void OutdoorSchedule_RemoveOutdoor(OutdoorSchedule *self, s32 x);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Remove
void OutdoorSchedule_Remove(OutdoorSchedule *self, s32 x);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_FindOutdoorSlot
s32 OutdoorSchedule_FindOutdoorSlot(OutdoorSchedule *a, s32 b);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_ForceReroll
void OutdoorSchedule_ForceReroll(OutdoorSchedule *p);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_IsRerollDue
BOOL OutdoorSchedule_IsRerollDue(OutdoorSchedule *self, ClockDateTime *out);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_PickRandom
void OutdoorSchedule_PickRandom(OutdoorSchedule *self, s8 *out, s32 *cnt, s8 *list, u8 *players, s32 limit);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_AssignIndoor
void OutdoorSchedule_AssignIndoor(OutdoorSchedule *self, s8 *list, s32 *cnt, VillagerState *slots);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_AssignOutdoor
void OutdoorSchedule_AssignOutdoor(OutdoorSchedule *self, s8 *list, s32 *cnt, VillagerState *slots, s32 n);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_AddBirthdayVisitor
void OutdoorSchedule_AddBirthdayVisitor(OutdoorSchedule *self, s8 *out, s32 *cnt, s8 *list, u8 *players);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_ApplySleep
void OutdoorSchedule_ApplySleep(OutdoorSchedule *self, u8 *p, ClockDateTime *x);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Reroll
void OutdoorSchedule_Reroll(OutdoorSchedule *self, u8 *p);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Apply
void OutdoorSchedule_Apply(OutdoorSchedule *self, u8 *p);
#endif
#ifndef PROTO_LOCAL_OutdoorSchedule_Update
void OutdoorSchedule_Update(OutdoorSchedule *self, u8 *p, s32 keep);
#endif
#ifndef PROTO_LOCAL_SaveVillagers_NotifyPlayerActivity
void SaveVillagers_NotifyPlayerActivity(u32 kind, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerTrend_OnFishCaught
void VillagerTrend_OnFishCaught(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerTrend_OnInsectCaught
void VillagerTrend_OnInsectCaught(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerTrend_OnItemDug
void VillagerTrend_OnItemDug(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerTrend_NotifyUnk5
void VillagerTrend_NotifyUnk5(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_TownMap_HasAttr8AtPos
BOOL TownMap_HasAttr8AtPos(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerTrend_NotifyUnk6
void VillagerTrend_NotifyUnk6(VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_VillagerState_Init
void VillagerState_Init(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetRole
u32 VillagerState_GetRole(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetRole
void VillagerState_SetRole(VillagerState *e, u32 v);
#endif
#ifndef PROTO_LOCAL_VillagerState_ResetRole
void VillagerState_ResetRole(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetPresence
u32 VillagerState_GetPresence(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetPresence
void VillagerState_SetPresence(VillagerState *e, u32 v);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetErrand
ErrandRecord *VillagerState_GetErrand(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetActivity
u32 VillagerState_GetActivity(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetActivity
void VillagerState_SetActivity(VillagerState *e, u32 v);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetMood
u32 VillagerState_GetMood(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetMood
void VillagerState_SetMood(VillagerState *e, u32 v);
#endif
#ifndef PROTO_LOCAL_VillagerState_AddMoodTimer
void VillagerState_AddMoodTimer(VillagerState *e, s32 v);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetMoodTimer
void VillagerState_SetMoodTimer(VillagerState *e, u16 v);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetMoodTimer
u32 VillagerState_GetMoodTimer(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_TickMoodTimer
void VillagerState_TickMoodTimer(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetUnk1dBit1
void VillagerState_SetUnk1dBit1(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_DoubleTalkUrge
void VillagerState_DoubleTalkUrge(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetHeldItem
u16 *VillagerState_GetHeldItem(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_SetHeldItem
void VillagerState_SetHeldItem(VillagerState *e, u16 *p);
#endif
#ifndef PROTO_LOCAL_VillagerState_ClearHeldItem
void VillagerState_ClearHeldItem(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_VillagerState_GetTalkRepeat
TalkRepeat *VillagerState_GetTalkRepeat(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_Construct
void TalkRepeat_Construct(TalkRepeat *t);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_Destruct
void TalkRepeat_Destruct(TalkRepeat *t);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_Reset
void TalkRepeat_Reset(TalkRepeat *t);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_Tick
void TalkRepeat_Tick(TalkRepeat *t, s32 v);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_Count
void TalkRepeat_Count(TalkRepeat *t);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_StartWindow
void TalkRepeat_StartWindow(TalkRepeat *t);
#endif
#ifndef PROTO_LOCAL_TalkRepeat_GetLevel
s32 TalkRepeat_GetLevel(TalkRepeat *t);
#endif
#ifndef PROTO_LOCAL_VillagerStateTable_Init
void VillagerStateTable_Init(VillagerStateTable *m);
#endif
#ifndef PROTO_LOCAL_VillagerStates_Get
VillagerStateTable *VillagerStates_Get();
#endif
#ifndef PROTO_LOCAL_VillagerStateTable_GetEntry
VillagerState *VillagerStateTable_GetEntry(VillagerStateTable *m, s32 i);
#endif
#ifndef PROTO_LOCAL_VillagerStateTable_ResetRuntime
void VillagerStateTable_ResetRuntime(VillagerState *e);
#endif
#ifndef PROTO_LOCAL_TownMap_IsUnitWalkable
BOOL TownMap_IsUnitWalkable(s32 x, s32 y, BlockMap *grid);
#endif
#ifndef PROTO_LOCAL_TownMap_IsPosWalkable
BOOL TownMap_IsPosWalkable(VecFx32 *a, BlockMap *grid);
#endif
#ifndef PROTO_LOCAL_TownMap_FindBuildingAbovePos
BOOL TownMap_FindBuildingAbovePos(VecFx32 *a, s32 h, s32 *px, s32 *py);
#endif
#ifndef PROTO_LOCAL_sSpNpcAnimHeapPool
extern SpNpcAnimHeapPool sSpNpcAnimHeapPool;
#endif
}
#endif

#endif

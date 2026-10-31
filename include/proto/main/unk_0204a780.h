#ifndef PROTO_PROTO_MAIN_UNK_0204A780_H
#define PROTO_PROTO_MAIN_UNK_0204A780_H


#include "types.h"
#include "field/MoneyRockState.h"
#include "sys/ClockDate.h"
#include "town/TownEventRecord.h"
#ifdef __cplusplus
#include "town/TownState.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Town_ReplaceSouthCedars
void Town_ReplaceSouthCedars();
#endif
#ifndef PROTO_LOCAL_TownState_PickNextWeekDate
void TownState_PickNextWeekDate(u8 *dst, u8 *src);
#endif
#ifndef PROTO_LOCAL_TownState_GetEvent
TownEventRecord *TownState_GetEvent(s32 i);
#endif
#ifndef PROTO_LOCAL_TownState_ClearEvents
void TownState_ClearEvents();
#endif
#ifndef PROTO_LOCAL_TownState_GetPlayerDate
ClockDate *TownState_GetPlayerDate(u8 *p, s32 i);
#endif
#ifndef PROTO_LOCAL_TownState_SetPlayerDateToday
void TownState_SetPlayerDateToday(u8 *p);
#endif
#ifndef PROTO_LOCAL_TownState_IsPlayerDateNotToday
BOOL TownState_IsPlayerDateNotToday(u8 *p);
#endif
#ifndef PROTO_LOCAL_TownState_IsPerfectStreak15
BOOL TownState_IsPerfectStreak15();
#endif
#ifndef PROTO_LOCAL_TownState_GetSeasonPeriod
u32 TownState_GetSeasonPeriod();
#endif
#ifndef PROTO_LOCAL_TownState_SetSeasonPeriod
void TownState_SetSeasonPeriod(u32 n);
#endif
#ifndef PROTO_LOCAL_Item_IsFruit
BOOL Item_IsFruit(u16 *p);
#endif
#ifndef PROTO_LOCAL_TownState_GetNativeFruit
s32 TownState_GetNativeFruit(u8 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeFruit
u16 Item_MakeFruit(s32 n);
#endif
#ifndef PROTO_LOCAL_Item_Equals
BOOL Item_Equals(u16 *a, u16 *b);
#endif
#ifndef PROTO_LOCAL_Item_GetPrice
s32 Item_GetPrice(u16 *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_GetRankOf
s32 NookPoints_GetRankOf(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetMemberPrice
s32 Item_GetMemberPrice(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsMoneyBag
BOOL Item_IsMoneyBag(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetSaveData
u8 *Item_GetSaveData();
#endif
#ifndef PROTO_LOCAL_Item_GetShopPrice
s32 Item_GetShopPrice(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsInvalid
BOOL Item_IsInvalid(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsMarker
BOOL Item_IsMarker(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetInfoUnk02
s32 Item_GetInfoUnk02(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetInfoUnk07
s32 Item_GetInfoUnk07(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFossil
BOOL Item_IsFossil(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsGyroid
BOOL Item_IsGyroid(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPainting
BOOL Item_IsPainting(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetKind
s32 Item_GetKind(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsHoldable
s32 Item_IsHoldable(u16 *p);
#endif
#ifndef PROTO_LOCAL_func_0204bab8
BOOL func_0204bab8(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_Copy
void Item_Copy(u16 *dst, u16 *src);
#endif
#ifndef PROTO_LOCAL_Item_GetIfNotCreature
BOOL Item_GetIfNotCreature(u16 *a, u16 *out);
#endif
#ifndef PROTO_LOCAL_Item_GetFishWaterClass
s32 Item_GetFishWaterClass(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFish
BOOL Item_IsFish(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFishIndex
s32 Item_GetFishIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFishBaseSize
s32 Item_GetFishBaseSize(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsInsect
BOOL Item_IsInsect(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetInsectIndex
s32 Item_GetInsectIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetInsectBaseSize
u16 Item_GetInsectBaseSize(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_TestInfoFlag3
BOOL Item_TestInfoFlag3(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_TestInfoFlag4
BOOL Item_TestInfoFlag4(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetShirtUnkGroup
BOOL Item_GetShirtUnkGroup(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeMoneyBag
u16 Item_MakeMoneyBag(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_FindMoneyBagForAmount
s32 Item_FindMoneyBagForAmount(s32 a, BOOL up, s32 *out);
#endif
#ifndef PROTO_LOCAL_Item_GetDesignPlayer
s32 Item_GetDesignPlayer(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsDesign
BOOL Item_IsDesign(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetDesignIndex
s32 Item_GetDesignIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetDesignSlot
s32 Item_GetDesignSlot(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeDesignByIndex
u16 Item_MakeDesignByIndex(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeDesign
u16 Item_MakeDesign(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Item_SetDesign
void Item_SetDesign(u16 *out, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Item_GetFlowerItemOrdinal
s32 Item_GetFlowerItemOrdinal(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFlowerAltOrdinal
s32 Item_GetFlowerAltOrdinal(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetNthFlowerItem
void Item_GetNthFlowerItem(u16 *out, u32 n);
#endif
#ifndef PROTO_LOCAL_Item_MakeFlowerAlt
u16 Item_MakeFlowerAlt(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_CopyB
void Item_CopyB(u16 *dst, u16 *src);
#endif
#ifndef PROTO_LOCAL_Item_GetNthFlowerAlt
void Item_GetNthFlowerAlt(u16 *out, u32 n);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerItemRange
BOOL Item_IsFlowerItemRange(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFlowerItemIndex
s32 Item_GetFlowerItemIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerItem
BOOL Item_IsFlowerItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerAltRange
BOOL Item_IsFlowerAltRange(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFlowerAltIndex
s32 Item_GetFlowerAltIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeFlowerItem
u16 Item_MakeFlowerItem(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerAltItem
BOOL Item_IsFlowerAltItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetPaperIndex
s32 Item_GetPaperIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetPaperCount
s32 Item_GetPaperCount(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakePaper
u16 Item_MakePaper(u32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Item_IsNormalItem
BOOL Item_IsNormalItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetIdClass
s32 Item_GetIdClass(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFurniture
BOOL Item_IsFurniture(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsFurniture
BOOL ItemList_IsFurniture(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsOccupiedF031
BOOL Item_IsOccupiedF031(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFurnitureOrF031
BOOL Item_IsFurnitureOrF031(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFurnitureDirection
s32 Item_GetFurnitureDirection(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFurnitureIndex
s32 Item_GetFurnitureIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeFurniture
u16 Item_MakeFurniture(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Item_SetFurnitureDirection
void Item_SetFurnitureDirection(u16 *p, s32 y);
#endif
#ifndef PROTO_LOCAL_Item_IsBuilding
BOOL Item_IsBuilding(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsBuildingOrOccupied
BOOL Item_IsBuildingOrOccupied(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeBuilding
u16 Item_MakeBuilding(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeNeighborHouse
u16 Item_MakeNeighborHouse(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_IsNookShop
BOOL Item_IsNookShop(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetNookShopLevel
s32 Item_GetNookShopLevel(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeNookShop
u16 Item_MakeNookShop(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_IsSnowman
BOOL Item_IsSnowman(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetSnowmanIndex
s32 Item_GetSnowmanIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeSnowman
u16 Item_MakeSnowman(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_IsPlayerHouse
BOOL Item_IsPlayerHouse(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakePlayerHouse
u16 Item_MakePlayerHouse(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeStage0
BOOL Item_IsTreeStage0(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeStage1
BOOL Item_IsTreeStage1(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeStage2
BOOL Item_IsTreeStage2(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeStage3
BOOL Item_IsTreeStage3(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeGrown
BOOL Item_IsTreeGrown(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFruitTreeLastNoFruit
BOOL Item_IsFruitTreeLastNoFruit(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreePlain
BOOL Item_IsTreePlain(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsCedarPlain
BOOL Item_IsCedarPlain(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFruitTree
BOOL Item_IsFruitTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsMoneyTree
BOOL Item_IsMoneyTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsSpecialTree
BOOL Item_IsSpecialTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsAcornTree
BOOL Item_IsAcornTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsSpecialCedar
BOOL Item_IsSpecialCedar(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFestiveCedar
BOOL Item_IsFestiveCedar(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPalmTree
BOOL Item_IsPalmTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTree
BOOL Item_IsTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetTreeStage
s32 Item_GetTreeStage(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_Assign
void Item_Assign(u16 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_Item_IsAppleTree
BOOL Item_IsAppleTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsOrangeTree
BOOL Item_IsOrangeTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPearTree
BOOL Item_IsPearTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPeachTree
BOOL Item_IsPeachTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsCherryTree
BOOL Item_IsCherryTree(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFruitTreeFruit
s32 Item_GetFruitTreeFruit(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsSmallStump
BOOL Item_IsSmallStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsMediumStump
BOOL Item_IsMediumStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsLargeStump
BOOL Item_IsLargeStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeStump
BOOL Item_IsTreeStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsSpecialStump
BOOL Item_IsSpecialStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTreeOrSpecialStump
BOOL Item_IsTreeOrSpecialStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsCedarStump
BOOL Item_IsCedarStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPalmStump
BOOL Item_IsPalmStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsStump
BOOL Item_IsStump(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetStumpSize
s32 Item_GetStumpSize(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsParchedTulip
BOOL Item_IsParchedTulip(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsParchedPansy
BOOL Item_IsParchedPansy(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsParchedCosmos
BOOL Item_IsParchedCosmos(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsParchedRose
BOOL Item_IsParchedRose(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerParched
BOOL Item_IsFlowerParched(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsTulip
BOOL Item_IsTulip(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPansy
BOOL Item_IsPansy(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsCosmos
BOOL Item_IsCosmos(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsRose
BOOL Item_IsRose(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerFresh
BOOL Item_IsFlowerFresh(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsWateredTulip
BOOL Item_IsWateredTulip(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsWateredPansy
BOOL Item_IsWateredPansy(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsWateredCosmos
BOOL Item_IsWateredCosmos(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsInRange
BOOL Item_IsInRange(u16 *p, u32 lo, u32 hi);
#endif
#ifndef PROTO_LOCAL_Item_IsWateredRose
BOOL Item_IsWateredRose(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFlowerWatered
BOOL Item_IsFlowerWatered(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetId
s32 Item_GetId(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFlower
BOOL Item_IsFlower(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_SetId
void Item_SetId(u16 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_Item_MakeInsect
u16 Item_MakeInsect(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeHat
u16 Item_MakeHat(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeCarpet
u16 Item_MakeCarpet(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeShirt
u16 Item_MakeShirt(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeAccessory
u16 Item_MakeAccessory(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_IsHat
BOOL Item_IsHat(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsHat
BOOL ItemList_IsHat(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsCarpet
BOOL Item_IsCarpet(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsCarpet
BOOL ItemList_IsCarpet(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsShirt
BOOL Item_IsShirt(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsShirt
BOOL ItemList_IsShirt(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsAccessory
BOOL Item_IsAccessory(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsAccessory
BOOL ItemList_IsAccessory(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsPaper
BOOL Item_IsPaper(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsPaper
BOOL ItemList_IsPaper(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsUmbrella
BOOL Item_IsUmbrella(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsUmbrella
BOOL ItemList_IsUmbrella(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsWallpaper
BOOL Item_IsWallpaper(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsWallpaper
BOOL ItemList_IsWallpaper(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_IsFullHeadwear
BOOL Item_IsFullHeadwear(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemList_IsFullHeadwear
BOOL ItemList_IsFullHeadwear(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_MakeUmbrella
u16 Item_MakeUmbrella(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeWallpaper
u16 Item_MakeWallpaper(u32 x);
#endif
#ifndef PROTO_LOCAL_Item_MakeFullHeadwear
u16 Item_MakeFullHeadwear(u32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TownState_ClearUnk0c
void TownState_ClearUnk0c(TownState *p);
#endif
#ifndef PROTO_LOCAL_TownState_ClearUnk16
void TownState_ClearUnk16(TownState *p);
#endif
#ifndef PROTO_LOCAL_TownState_RemoveEvent
void TownState_RemoveEvent(TownState *x, u32 id);
#endif
#ifndef PROTO_LOCAL_TownState_FindEvent
s32 TownState_FindEvent(TownState *x, u32 id);
#endif
#ifndef PROTO_LOCAL_TownState_AddEvent
s32 TownState_AddEvent(TownState *x, u32 id);
#endif
#ifndef PROTO_LOCAL_TownState_UpdatePerfectStreak
void TownState_UpdatePerfectStreak(TownState *p, s32 k, s32 add);
#endif
}
#ifndef PROTO_LOCAL_data_021c47bc
extern MoneyRockState data_021c47bc;
#endif
#endif

#endif

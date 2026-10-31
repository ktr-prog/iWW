#ifndef PROTO_PROTO_MAIN_UNK_02061478_H
#define PROTO_PROTO_MAIN_UNK_02061478_H


#include "types.h"
#ifdef __cplusplus
#include "item/ItemId.h"
#include "item/ItemInfoTables.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ItemInfo_CountHoldable
void ItemInfo_CountHoldable();
#endif
#ifndef PROTO_LOCAL_ItemInfo_CountFlowerItems
void ItemInfo_CountFlowerItems();
#endif
#ifndef PROTO_LOCAL_ItemInfo_CountClass1dHeadwear
void ItemInfo_CountClass1dHeadwear();
#endif
#ifndef PROTO_LOCAL_ItemInfo_IsReady
BOOL ItemInfo_IsReady();
#endif
#ifndef PROTO_LOCAL_ItemInfo_Init
s32 ItemInfo_Init();
#endif
#ifndef PROTO_LOCAL_ItemInfo_Exit
void ItemInfo_Exit();
#endif
#ifndef PROTO_LOCAL_ItemInfo_LoadIndoor
void ItemInfo_LoadIndoor(s32 a);
#endif
#ifndef PROTO_LOCAL_ItemInfo_FreeIndoor
void ItemInfo_FreeIndoor();
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetName
u16 *ItemInfo_GetName(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetUnk02
s32 ItemInfo_GetUnk02(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetNameForm
s32 ItemInfo_GetNameForm(u16 *);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetNameAttrB
s32 ItemInfo_GetNameAttrB(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetNameAttrA
s32 ItemInfo_GetNameAttrA(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetSeries
s32 ItemInfo_GetSeries(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetPrice
u32 ItemInfo_GetPrice(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetKind
s32 ItemInfo_GetKind(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetClass
s32 ItemInfo_GetClass(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetUnk07
s32 ItemInfo_GetUnk07(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetSeason
s32 ItemInfo_GetSeason(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_IsHoldable
BOOL ItemInfo_IsHoldable(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_TestFlag1
BOOL ItemInfo_TestFlag1(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_TestFlag2
BOOL ItemInfo_TestFlag2(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_TestFlag3
BOOL ItemInfo_TestFlag3(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_TestFlag4
BOOL ItemInfo_TestFlag4(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetIndoorUnk1
u32 ItemInfo_GetIndoorUnk1(u16 *p);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetIndoorUnk0
u32 ItemInfo_GetIndoorUnk0(u16 *p);
#endif
#ifndef PROTO_LOCAL_Series_GetType
u32 Series_GetType(s32 i);
#endif
#ifndef PROTO_LOCAL_Series_GetName
u8 *Series_GetName(s32 i);
#endif
#ifndef PROTO_LOCAL_FtrClass_GetBasePoints
u32 FtrClass_GetBasePoints(s32 i);
#endif
#ifndef PROTO_LOCAL_Item_GetIconModelName
const char *Item_GetIconModelName(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetHoldableCount
u32 ItemInfo_GetHoldableCount();
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetNthHoldable
void ItemInfo_GetNthHoldable(u16 *out, s32 idx);
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetHoldableIndex
s32 ItemInfo_GetHoldableIndex(u16 *p);
#endif
#ifndef PROTO_LOCAL_Item_GetFlowerItemCount
u32 Item_GetFlowerItemCount();
#endif
#ifndef PROTO_LOCAL_Item_GetFlowerAltCount
u32 Item_GetFlowerAltCount();
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetHatClass1dCount
u32 ItemInfo_GetHatClass1dCount();
#endif
#ifndef PROTO_LOCAL_ItemInfo_GetFullHeadwearClass1dCount
u32 ItemInfo_GetFullHeadwearClass1dCount();
#endif
#ifndef PROTO_LOCAL_Item_FromPlacedForm
void Item_FromPlacedForm(u16 *out, u16 *in);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ItemInfoTables_Open
s32 ItemInfoTables_Open(ItemInfoTables *o);
#endif
#ifndef PROTO_LOCAL_ItemInfoTables_Close
void ItemInfoTables_Close(ItemInfoTables *o);
#endif
#ifndef PROTO_LOCAL_ItemInfoTables_LoadIndoor
void ItemInfoTables_LoadIndoor(ItemInfoTables *p, s32 x);
#endif
#ifndef PROTO_LOCAL_ItemInfoTables_FreeIndoor
void ItemInfoTables_FreeIndoor(ItemInfoTables *p);
#endif
}
#ifndef PROTO_LOCAL_sIconModelStrPresent
extern char sIconModelStrPresent[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint11
extern char sIconModelStrPaint11[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint14
extern char sIconModelStrPaint14[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint06
extern char sIconModelStrPaint06[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrWall
extern char sIconModelStrWall[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrFishingrod
extern char sIconModelStrFishingrod[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrSeedpitfall
extern char sIconModelStrSeedpitfall[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrMoneybag
extern char sIconModelStrMoneybag[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint09
extern char sIconModelStrPaint09[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrHanabi
extern char sIconModelStrHanabi[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrBottleMail
extern char sIconModelStrBottleMail[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrTane
extern char sIconModelStrTane[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrWig
extern char sIconModelStrWig[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrDust
extern char sIconModelStrDust[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint12
extern char sIconModelStrPaint12[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint08
extern char sIconModelStrPaint08[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint15
extern char sIconModelStrPaint15[];
#endif
#ifndef PROTO_LOCAL_sFlowerAltCount
extern s32 sFlowerAltCount;
#endif
#ifndef PROTO_LOCAL_sIconModelStrBox
extern char sIconModelStrBox[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaper
extern char sIconModelStrPaper[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrAxe
extern char sIconModelStrAxe[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCracker
extern char sIconModelStrCracker[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrMakigai
extern char sIconModelStrMakigai[];
#endif
#ifndef PROTO_LOCAL_gItemInfo
extern ItemInfoTables gItemInfo;
#endif
#ifndef PROTO_LOCAL_sIconModelStrPeach
extern char sIconModelStrPeach[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrOrange
extern char sIconModelStrOrange[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCap
extern char sIconModelStrCap[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrMakigai2
extern char sIconModelStrMakigai2[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrScoop
extern char sIconModelStrScoop[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint03
extern char sIconModelStrPaint03[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrSeed
extern char sIconModelStrSeed[];
#endif
#ifndef PROTO_LOCAL_sHoldableItemCount
extern s32 sHoldableItemCount;
#endif
#ifndef PROTO_LOCAL_sIconModelStrGwatering
extern char sIconModelStrGwatering[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrMedicine
extern char sIconModelStrMedicine[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGpachinko
extern char sIconModelStrGpachinko[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCage
extern char sIconModelStrCage[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGscoop
extern char sIconModelStrGscoop[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaperbag
extern char sIconModelStrPaperbag[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrApple
extern char sIconModelStrApple[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrUmbrella
extern char sIconModelStrUmbrella[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrKabu
extern char sIconModelStrKabu[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGtoolbox
extern char sIconModelStrGtoolbox[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint05
extern char sIconModelStrPaint05[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPachinko
extern char sIconModelStrPachinko[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCloth
extern char sIconModelStrCloth[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrMusic
extern char sIconModelStrMusic[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGnet
extern char sIconModelStrGnet[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCherry
extern char sIconModelStrCherry[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCoin
extern char sIconModelStrCoin[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrAcorn
extern char sIconModelStrAcorn[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrLeaf
extern char sIconModelStrLeaf[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGear
extern char sIconModelStrGear[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrToolbox
extern char sIconModelStrToolbox[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrHoneycomb
extern char sIconModelStrHoneycomb[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint01
extern char sIconModelStrPaint01[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint02
extern char sIconModelStrPaint02[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrSeedling
extern char sIconModelStrSeedling[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrNet
extern char sIconModelStrNet[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrSeedlingC
extern char sIconModelStrSeedlingC[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrHaniwa
extern char sIconModelStrHaniwa[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrFossil
extern char sIconModelStrFossil[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrSango
extern char sIconModelStrSango[];
#endif
#ifndef PROTO_LOCAL_sFlowerItemCount
extern s32 sFlowerItemCount;
#endif
#ifndef PROTO_LOCAL_sFullHeadwearClass1dCount
extern s32 sFullHeadwearClass1dCount;
#endif
#ifndef PROTO_LOCAL_sIconModelStrCarpet
extern char sIconModelStrCarpet[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint10
extern char sIconModelStrPaint10[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint13
extern char sIconModelStrPaint13[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGfishingrod
extern char sIconModelStrGfishingrod[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrCoconut
extern char sIconModelStrCoconut[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrDeliverL
extern char sIconModelStrDeliverL[];
#endif
#ifndef PROTO_LOCAL_sHatClass1dCount
extern s32 sHatClass1dCount;
#endif
#ifndef PROTO_LOCAL_sIconModelStrPear
extern char sIconModelStrPear[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrRKabu
extern char sIconModelStrRKabu[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrWatering
extern char sIconModelStrWatering[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGaxe
extern char sIconModelStrGaxe[];
#endif
#ifndef PROTO_LOCAL_sFirstHoldableItem
extern ItemId sFirstHoldableItem;
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint04
extern char sIconModelStrPaint04[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrTimer
extern char sIconModelStrTimer[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint07
extern char sIconModelStrPaint07[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrSoldout
extern char sIconModelStrSoldout[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrGlasses
extern char sIconModelStrGlasses[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrClover
extern char sIconModelStrClover[];
#endif
#ifndef PROTO_LOCAL_sIconModelStrPaint00
extern char sIconModelStrPaint00[];
#endif
#endif

#endif

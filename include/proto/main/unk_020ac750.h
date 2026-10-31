#ifndef PROTO_PROTO_MAIN_UNK_020AC750_H
#define PROTO_PROTO_MAIN_UNK_020AC750_H


#include "types.h"
#include "item/ItemId.h"
#include "item/ShopPurchaseBits.h"
struct NookPoints;
struct S1;
#ifndef __cplusplus
typedef struct NookPoints NookPoints;
typedef struct S1 S1;
#endif
#ifdef __cplusplus
#include "game/NookShop.h"
#include "game/ReddShop.h"
#include "game/ShopAckCounter.h"
#include "item/DateSeededRandomSource.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_StockList_AddFromPickList
void StockList_AddFromPickList(ItemId *buf, u32 *pos, s32 r2, s32 r3, u32 n, s32 unused, u8 flag);
#endif
#ifndef PROTO_LOCAL_StockList_AddFromRange
void StockList_AddFromRange(ItemId *buf, u32 *pos, s32 r2, s32 r3, u32 n, s32 unused, u8 flag);
#endif
#ifndef PROTO_LOCAL_StockList_Clear
void StockList_Clear(ItemId *a, u8 *b, u32 n);
#endif
#ifndef PROTO_LOCAL_StockList_IsSold
BOOL StockList_IsSold(u32 i, u32 n, u8 *bits);
#endif
#ifndef PROTO_LOCAL_StockList_MarkSold
BOOL StockList_MarkSold(u32 i, u32 n, u8 *bits);
#endif
#ifndef PROTO_LOCAL_StockList_GetItem
u16 *StockList_GetItem(u32 i, ItemId *arr, u8 *bits, u32 n, u16 *out);
#endif
#ifndef PROTO_LOCAL_StockList_FindItem
s32 StockList_FindItem(u16 *key, ItemId *arr, u8 *bits, u32 n);
#endif
#ifndef PROTO_LOCAL_Shop_RemoveSoldItemAt
void Shop_RemoveSoldItemAt(s32 x, s32 y, u32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Shop_RemoveSoldItem
void Shop_RemoveSoldItem(u16 *p, u32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NookShop_PostPointSpecialNotice
void NookShop_PostPointSpecialNotice(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NookShop_PostSaleNotice
void NookShop_PostSaleNotice(s32 x);
#endif
#ifndef PROTO_LOCAL_NookShop_PostSpecialItemNotice
void NookShop_PostSpecialItemNotice(u16 *s);
#endif
#ifndef PROTO_LOCAL_NookShop_PostRenovationNotice
void NookShop_PostRenovationNotice(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NookShop_PostReopenNotice
void NookShop_PostReopenNotice(void);
#endif
#ifndef PROTO_LOCAL_Shop_IsPurchaseSynced
BOOL Shop_IsPurchaseSynced(void);
#endif
#ifndef PROTO_LOCAL_NookShop_InitNew
void NookShop_InitNew(NookShop *a);
#endif
#ifndef PROTO_LOCAL_NookShop_HasVisitorBought
int NookShop_HasVisitorBought(void*);
#endif
#ifndef PROTO_LOCAL_NookShop_IsBlockingEvent
BOOL NookShop_IsBlockingEvent(int x);
#endif
#ifndef PROTO_LOCAL_NookShop_ApplyRenovation
u32 NookShop_ApplyRenovation(void);
#endif
#ifndef PROTO_LOCAL_AbleShop_Construct
AbleShop *AbleShop_Construct(AbleShop *p);
#endif
#ifndef PROTO_LOCAL_AbleShop_Destruct
AbleShop *AbleShop_Destruct(AbleShop *p);
#endif
#ifndef PROTO_LOCAL_AbleShop_InitNew
void AbleShop_InitNew(void);
#endif
#ifndef PROTO_LOCAL_AbleShop_StockHeadwear
void AbleShop_StockHeadwear(AbleShop *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_AbleShop_StockAccessory
void AbleShop_StockAccessory(AbleShop *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_AbleShop_RestockEnd
void AbleShop_RestockEnd(AbleShop *s);
#endif
#ifndef PROTO_LOCAL_ReddPassword_ForgetVisitor
void ReddPassword_ForgetVisitor(void);
#endif
#ifndef PROTO_LOCAL_ReddPassword_VisitorKnows
BOOL ReddPassword_VisitorKnows(void);
#endif
#ifndef PROTO_LOCAL_ReddShop_IsTentOpen
BOOL ReddShop_IsTentOpen(void);
#endif
#ifndef PROTO_LOCAL_ReddPassword_ForgetResident
void ReddPassword_ForgetResident(u32 i);
#endif
#ifndef PROTO_LOCAL_ReddPassword_CurrentPlayerKnows
BOOL ReddPassword_CurrentPlayerKnows(void);
#endif
#ifndef PROTO_LOCAL_ReddPassword_LearnCurrentPlayer
BOOL ReddPassword_LearnCurrentPlayer(void);
#endif
#ifndef PROTO_LOCAL_ReddShop_SendPasswordLetters
void ReddShop_SendPasswordLetters(void);
#endif
#ifndef PROTO_LOCAL_NookPoints_SendMemberLetters
void NookPoints_SendMemberLetters(void);
#endif
#ifndef PROTO_LOCAL_NookPoints_Add
void NookPoints_Add(u16 *p, u32 add);
#endif
#ifndef PROTO_LOCAL_NookPoints_AddForPurchase
void NookPoints_AddForPurchase(u16 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_NookPoints_GetRank
u32 NookPoints_GetRank(u32 v);
#endif
#ifndef PROTO_LOCAL_NookPoints_GetRankThreshold
u32 NookPoints_GetRankThreshold(u32 i);
#endif
#ifndef PROTO_LOCAL_NookPoints_GetToNextRank
u16 NookPoints_GetToNextRank(u16 *p);
#endif
#ifndef PROTO_LOCAL_Shop_RecordPurchase
void Shop_RecordPurchase(u32 a, u32 b, u32 c, u32 d, int mode, u8 flag, int e);
#endif
#ifndef PROTO_LOCAL_NookShop_RecordBuyback
void NookShop_RecordBuyback(int a);
#endif
#ifndef PROTO_LOCAL_NookShop_BuyAt
void NookShop_BuyAt(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_NookShop_IsPurchaseSynced
u32 NookShop_IsPurchaseSynced(void);
#endif
#ifndef PROTO_LOCAL_NookShop_CanTakeCatalogOrder
BOOL NookShop_CanTakeCatalogOrder(void);
#endif
#ifndef PROTO_LOCAL_NookShop_SendCatalogOrder
BOOL NookShop_SendCatalogOrder(void *name);
#endif
#ifndef PROTO_LOCAL_AbleShop_BuyAt
void AbleShop_BuyAt(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_AbleShop_IsPurchaseSynced
u32 AbleShop_IsPurchaseSynced(void);
#endif
#ifndef PROTO_LOCAL_ReddShop_RecordPurchase
void ReddShop_RecordPurchase(u32 a, u32 b, u8 c, u32 d);
#endif
#ifndef PROTO_LOCAL_ReddShop_BuyAt
void ReddShop_BuyAt(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_ReddShop_IsPurchaseSynced
u32 ReddShop_IsPurchaseSynced(void);
#endif
#ifndef PROTO_LOCAL_Shop_OnPurchaseAck
u32 Shop_OnPurchaseAck(void);
#endif
#ifndef PROTO_LOCAL_NookShop_PickFlowerBag
void NookShop_PickFlowerBag(u16 *p);
#endif
#ifndef PROTO_LOCAL_NookShop_IsOpenHour
BOOL NookShop_IsOpenHour(void);
#endif
#ifndef PROTO_LOCAL_NookShop_GetVisitState
int NookShop_GetVisitState(void);
#endif
#ifndef PROTO_LOCAL_NookShop_SetVisitState
void NookShop_SetVisitState(int v);
#endif
#ifndef PROTO_LOCAL_NookShop_OnSceneLoad
void NookShop_OnSceneLoad(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_ShopAckCounter_Clear
void ShopAckCounter_Clear(ShopAckCounter *c);
#endif
#ifndef PROTO_LOCAL_ShopAckCounter_Start
void ShopAckCounter_Start(ShopAckCounter *c);
#endif
#ifndef PROTO_LOCAL_ShopAckCounter_IsDone
BOOL ShopAckCounter_IsDone(ShopAckCounter *c);
#endif
#ifndef PROTO_LOCAL_ShopAckCounter_Add
BOOL ShopAckCounter_Add(ShopAckCounter *c);
#endif
#ifndef PROTO_LOCAL_NookShop_GetReopenDateTime
BOOL NookShop_GetReopenDateTime(ClockDateTime *out);
#endif
#ifndef PROTO_LOCAL_NookShop_Clear
void NookShop_Clear(NookShop *p);
#endif
#ifndef PROTO_LOCAL_AbleShop_Clear
void AbleShop_Clear(AbleShop *s);
#endif
#ifndef PROTO_LOCAL_AbleShop_Reset
void AbleShop_Reset(AbleShop *s);
#endif
#ifndef PROTO_LOCAL_AbleShop_UpdateDaily
void AbleShop_UpdateDaily(AbleShop *s);
#endif
#ifndef PROTO_LOCAL_AbleShop_Restock
void AbleShop_Restock(AbleShop *s, u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_AbleShop_IsStockStale
u32 AbleShop_IsStockStale(AbleShop *s, ClockDateTime *p);
#endif
#ifndef PROTO_LOCAL_AbleShop_SetStockDate
void AbleShop_SetStockDate(AbleShop *s, ClockDateTime *p);
#endif
#ifndef PROTO_LOCAL_AbleShop_GetItem
u16 *AbleShop_GetItem(AbleShop *s, u32 a, u16 *c);
#endif
#ifndef PROTO_LOCAL_AbleShop_FindItem
s32 AbleShop_FindItem(AbleShop *s, u16 *key);
#endif
#ifndef PROTO_LOCAL_AbleShop_MarkSold
u32 AbleShop_MarkSold(AbleShop *s, u32 a);
#endif
#ifndef PROTO_LOCAL_AbleShop_MarkSoldItem
u32 AbleShop_MarkSoldItem(AbleShop *s, u16 *key);
#endif
#ifndef PROTO_LOCAL_AbleShop_StockUmbrella
void AbleShop_StockUmbrella(AbleShop *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_AbleShop_StockShirts
void AbleShop_StockShirts(AbleShop *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_ReddShop_Reset
void ReddShop_Reset(ReddShop *g);
#endif
#ifndef PROTO_LOCAL_ReddShop_MarkSold
u32 ReddShop_MarkSold(ReddShop *g, u32 a);
#endif
#ifndef PROTO_LOCAL_ReddShop_MarkSoldItem
u32 ReddShop_MarkSoldItem(ReddShop *g, u16 *ptr);
#endif
#ifndef PROTO_LOCAL_ReddShop_GetItem
u16 *ReddShop_GetItem(ReddShop *g, u32 a, u16 *b);
#endif
#ifndef PROTO_LOCAL_ReddShop_FindItem
s32 ReddShop_FindItem(ReddShop *g, u16 *key);
#endif
#ifndef PROTO_LOCAL_NookPoints_Create
NookPoints *NookPoints_Create(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_Destroy
NookPoints *NookPoints_Destroy(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_Reset
void NookPoints_Reset(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_Init
void NookPoints_Init(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_GetValuePtr
u16 *NookPoints_GetValuePtr(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_Construct
NookPoints *NookPoints_Construct(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_Destruct
void NookPoints_Destruct(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_NookPoints_Clear
void NookPoints_Clear(NookPoints *p);
#endif
#ifndef PROTO_LOCAL_Shop_OnPurchaseRecord
void Shop_OnPurchaseRecord(Bits *p, u32 arg);
#endif
}
#ifndef PROTO_LOCAL_data_020e2e34
extern u32 data_020e2e34;
#endif
#ifndef PROTO_LOCAL_sShopRandom
extern DateSeededRandomSource sShopRandom;
#endif
#ifndef PROTO_LOCAL_data_020e2e48
extern u32 data_020e2e48;
#endif
#ifndef PROTO_LOCAL_sNookShopVisitState
extern s32 sNookShopVisitState;
#endif
#ifndef PROTO_LOCAL_data_020e2e38
extern u32 data_020e2e38;
#endif
#ifndef PROTO_LOCAL_data_020e2e44
extern u32 data_020e2e44;
#endif
#ifndef PROTO_LOCAL_sReddVisitorKnowsPassword
extern u8 sReddVisitorKnowsPassword;
#endif
#ifndef PROTO_LOCAL_sStockNoItem
extern ItemId sStockNoItem;
#endif
#ifndef PROTO_LOCAL_data_020e2e40
extern u32 data_020e2e40;
#endif
#ifndef PROTO_LOCAL_sStockSoldOutItem
extern ItemId sStockSoldOutItem;
#endif
#ifndef PROTO_LOCAL_data_020e2e3c
extern u32 data_020e2e3c;
#endif
#ifndef PROTO_LOCAL_sShopAckCounter
extern ShopAckCounter sShopAckCounter;
#endif
#endif

#endif

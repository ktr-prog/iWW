#include "uptr.h"
#include "host_labels.h"
#include "types.h"
#include "town/BlockMap.h"
#include "town/MapBlock.h"
#include "town/TownBlockMap.h"
#include "gfx/VecFx32.h"
#include "game/GroundInfoBase.h"
#include "gfx/ObjShadowTexture.h"
#include "gfx/NNSG3dResTex.h"
#include "gfx/ObjShadowTexDef.h"
#include "gfx/NNSG3dResMatData.h"
#include "item/PickedItem.h"
#include "item/ItemId.h"
#include "item/ItemPickSpec.h"
#include "item/RandomSource.h"
#include "game/Unk_020aec00.h"
#include "game/ReddPassword.h"
#include "game/ShopAckCounter.h"
#include "item/Letter.h"
#include "gfx/ObjShadowBits.h"
#include "item/ShopPurchaseBits.h"
#include "item/DateSeededRandomSource.h"
#include "game/Elem2a.h"
#include "gfx/Vec3Z.h"
#include "gfx/Mtx43.h"
#include "game/Loc488.h"
#include "gfx/ObjShadowStrip.h"
#include "game/ReddShop.h"
#include "game/NookShop.h"
#include "game/AbleShop.h"
#include "sys/ClockDateTime.h"
#include "sys/ClockDate.h"
#include "talk/MsgString.h"
#include "talk/MsgString25.h"


#include "item/ItemName.h"
#include "item/LetterView.h"
#include "net/CommManager.h"
#include "player/PlayerData.h"
#include "room/FtrActorTable.h"
#include "room/FtrActorGrid.h"
#include "player/PlayerId.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_020742f4.h"

extern DateSeededRandomSource sShopRandom;
#include "save/SaveData.h"
#include "save/TownId.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_021104ac.h"
#include "proto/itcm/unk_01ff8ad4.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/main/unk_020abea8.h"
#include "proto/main/unk_020ac750.h"
#include "proto/main/unk_020af258.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov004/unk_ov004_0223e9bc.h"
#include "proto/main/unk_0204cc1c.h"
#include "proto/main/unk_0209cb74.h"
#include "proto/main/unk_0204a780.h"



















class ReddPasswordString : public MsgString {
public:
    ReddPasswordString();
    virtual ~ReddPasswordString();
    virtual u32 capacity();
    virtual u8 *data();

    /* 0x12 */ u8 text[0x21];
};



struct NookPoints {
    u16 v;
};

struct E12 { u16 h; u8 pad[10]; };



extern const s32 sObjShadowCoordShift;
extern const u8 kNookCarpetCounts[4];
extern const u8 kNookPaintCounts[4];
extern const u8 kNookWallpaperCounts[4];
extern const u8 kNookStationeryCounts[4];
extern const u8 kNookToolCounts[4];
extern const u8 kNookFurnitureCounts[4];
extern const u8 kNookFlowerBagCounts[4];
extern const u8 kNookSaplingCounts[4];
extern const u8 kNookBottleCounts[4];
extern const u16 kNookMemberGiftItems[4];
extern const u16 kNookPointRankThresholds[6];
extern const u8 sReddStockOrders[6][3];
extern const u16 kNookFlowerBagItems[12];

extern "C" {
#define data_021ed104 HOST_LABEL(NookShop *, data_021ed104)
#define data_021ed2c0 HOST_LABEL(ReddShop *, data_021ed2c0)
#define data_021ed2d4 HOST_LABEL(AbleShop *, data_021ed2d4)
u32 Scene_GetCurrent(void);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void AbleShop_BuyAt(u32 a, u32 b, u32 c);
void AbleShop_Clear(AbleShop *s);
AbleShop *AbleShop_Construct(AbleShop *p);
AbleShop *AbleShop_Destruct(AbleShop *p);
s32 AbleShop_FindItem(AbleShop *s, u16 *key);
u16 *AbleShop_GetItem(AbleShop *s, u32 a, u16 *c);
void AbleShop_InitNew(void);
u32 AbleShop_IsPurchaseSynced(void);
u32 AbleShop_IsStockStale(AbleShop *s, ClockDateTime *p);
u32 AbleShop_MarkSold(AbleShop *s, u32 a);
u32 AbleShop_MarkSoldItem(AbleShop *s, u16 *key);
void AbleShop_Reset(AbleShop *s);
void AbleShop_Restock(AbleShop *s, u32 a, u32 b, u32 c);
void AbleShop_RestockEnd(AbleShop *s);
void AbleShop_SetStockDate(AbleShop *s, ClockDateTime *p);
void AbleShop_StockAccessory(AbleShop *a, u32 *b);
void AbleShop_StockHeadwear(AbleShop *a, u32 *b);
void AbleShop_StockShirts(AbleShop *a, u32 *b);
void AbleShop_StockUmbrella(AbleShop *a, u32 *b);
void AbleShop_UpdateDaily(AbleShop *s);
void NookPoints_Add(u16 *p, u32 add);
void NookPoints_AddForPurchase(u16 *p, u32 v);
void NookPoints_Clear(NookPoints *p);
NookPoints *NookPoints_Construct(NookPoints *p);
NookPoints *NookPoints_Create(NookPoints *p);
NookPoints *NookPoints_Destroy(NookPoints *p);
void NookPoints_Destruct(NookPoints *p);
u32 NookPoints_GetRank(u32 v);
u32 NookPoints_GetRankThreshold(u32 i);
u16 NookPoints_GetToNextRank(u16 *p);
u16 *NookPoints_GetValuePtr(NookPoints *p);
void NookPoints_Init(NookPoints *p);
void NookPoints_Reset(NookPoints *p);
void NookPoints_SendMemberLetters(void);
void NookShop_AddSales(NookShop *self, int add, int arg);
u32 NookShop_ApplyRenovation(void);
void NookShop_BuyAt(u32 a, u32 b, u32 c, u32 d);
BOOL NookShop_CanTakeCatalogOrder(void);
void NookShop_Clear(NookShop *p);
void NookShop_ClearStock(NookShop *self);
int NookShop_FindItem(NookShop *self, u16 *key);
u32 NookShop_GetBottleCount(NookShop *s);
u32 NookShop_GetCarpetCount(NookShop *s);
int NookShop_GetEarnedLevel(NookShop *self);
u32 NookShop_GetFlowerBagCount(NookShop *s);
u32 NookShop_GetFurnitureCount(NookShop *s);
u16 *NookShop_GetItem(NookShop *self, int idx, u16* p);
u32 NookShop_GetLevel(NookShop *s);
u32 NookShop_GetMedicineCount(NookShop *s);
u32 NookShop_GetPaintCount(NookShop *s);
NookShopRenovation *NookShop_GetRenovation(NookShop *self);
BOOL NookShop_GetReopenDateTime(ClockDateTime *out);
u32 NookShop_GetSaplingCount(NookShop *s);
u32 NookShop_GetStationeryCount(NookShop *s);
u32 NookShop_GetToolCount(NookShop *s);
u32 NookShop_GetUpgradeSales(NookShop *self, int mode);
int NookShop_GetVisitState(void);
u32 NookShop_GetWallpaperCount(NookShop *s);
BOOL NookShop_HasClass4Furniture(NookShop *self);
int NookShop_HasVisitorBought(void*);
void NookShop_InitNew(NookShop *a);
BOOL NookShop_IsBlockingEvent(int x);
int NookShop_IsClosedNextDay(NookShop *self, ClockDateTime *d);
int NookShop_IsClosedOn(NookShop *self, ClockDateTime *d);
int NookShop_IsClosedToday(NookShop *self);
int NookShop_IsClosedTomorrow(NookShop *self);
BOOL NookShop_IsOpenHour(void);
int NookShop_IsPointSpecialDay(NookShop *self, ClockDateTime *d);
int NookShop_IsPointSpecialToday(NookShop *self);
u32 NookShop_IsPurchaseSynced(void);
int NookShop_IsReopenDue(NookShop *self, ClockDateTime *d);
int NookShop_IsReopenDueNow(NookShop *self);
BOOL NookShop_IsSaleTime(NookShop *self);
int NookShop_IsSold(NookShop *self, int idx);
int NookShop_IsStockStale(NookShop *self, ClockDateTime *d);
void NookShop_NoteBuyer(NookShop *self, int flag);
void NookShop_OnSceneLoad(void);
void NookShop_PickFlowerBag(u16 *p);
void NookShop_PostPointSpecialNotice(s32 a, s32 b);
void NookShop_PostRenovationNotice(s32 a, s32 b);
void NookShop_PostReopenNotice(void);
void NookShop_PostSaleNotice(s32 x);
void NookShop_PostSpecialItemNotice(u16 *s);
void NookShop_RecordBuyback(int a);
void NookShop_Restock(NookShop *self, int a, int b, int c);
void NookShop_RestockEnd(NookShop *s);
void NookShop_ScheduleRenovation(NookShop *self);
BOOL NookShop_SellSlot(NookShop *self, u32 idx, int add, int arg);
BOOL NookShop_SendCatalogOrder(void *name);
void NookShop_SetLevel(NookShop *s, u32 v);
void NookShop_SetStockDate(NookShop *self, ClockDateTime *d);
void NookShop_SetVisitState(int v);
void NookShop_StockBottle(NookShop *s, u32 *p);
void NookShop_StockCarpets(NookShop *s, u32 *p);
void NookShop_StockFlowerBags(NookShop *s, u32 *p);
void NookShop_StockFurniture(NookShop *s, u32 *p);
void NookShop_StockMedicine(NookShop *s, u32 *p);
void NookShop_StockPaint(NookShop *s, u32 *p);
void NookShop_StockSaplings(NookShop *s, u32 *p);
void NookShop_StockStationery(NookShop *s, u32 *p);
void NookShop_StockTools(NookShop *s, u32 *p);
void NookShop_StockWallpaper(NookShop *s, u32 *p);
void NookShop_UpdateDaily(NookShop *self, int force);
void NookShop_UpdatePointSpecial(NookShop *s, ClockDateTime *p);
BOOL ReddPassword_CurrentPlayerKnows(void);
void ReddPassword_ForgetResident(u32 i);
void ReddPassword_ForgetVisitor(void);
BOOL ReddPassword_LearnCurrentPlayer(void);
BOOL ReddPassword_VisitorKnows(void);
void ReddShop_BuyAt(u32 a, u32 b, u32 c);
s32 ReddShop_FindItem(ReddShop *g, u16 *key);
u16 *ReddShop_GetItem(ReddShop *g, u32 a, u16 *b);
u32 ReddShop_IsPurchaseSynced(void);
BOOL ReddShop_IsTentOpen(void);
u32 ReddShop_MarkSold(ReddShop *g, u32 a);
u32 ReddShop_MarkSoldItem(ReddShop *g, u16 *ptr);
void ReddShop_RecordPurchase(u32 a, u32 b, u8 c, u32 d);
void ReddShop_Reset(ReddShop *g);
void ReddShop_SendPasswordLetters(void);
BOOL ShopAckCounter_Add(ShopAckCounter *c);
void ShopAckCounter_Clear(ShopAckCounter *c);
BOOL ShopAckCounter_IsDone(ShopAckCounter *c);
void ShopAckCounter_Start(ShopAckCounter *c);
BOOL Shop_IsPurchaseSynced(void);
u32 Shop_OnPurchaseAck(void);
void Shop_OnPurchaseRecord(Bits *p, u32 arg);
void Shop_RecordPurchase(u32 a, u32 b, u32 c, u32 d, int mode, u8 flag, int e);
void Shop_RemoveSoldItem(u16 *p, u32 a, s32 b);
void Shop_RemoveSoldItemAt(s32 x, s32 y, u32 a, s32 b);
void StockList_AddFromPickList(ItemId *buf, u32 *pos, s32 r2, s32 r3, u32 n, s32 unused, u8 flag);
void StockList_AddFromRange(ItemId *buf, u32 *pos, s32 r2, s32 r3, u32 n, s32 unused, u8 flag);
void StockList_Clear(ItemId *a, u8 *b, u32 n);
s32 StockList_FindItem(u16 *key, ItemId *arr, u8 *bits, u32 n);
u16 *StockList_GetItem(u32 i, ItemId *arr, u8 *bits, u32 n, u16 *out);
BOOL StockList_IsSold(u32 i, u32 n, u8 *bits);
BOOL StockList_MarkSold(u32 i, u32 n, u8 *bits);
}


namespace n5 {
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {

}
extern "C" {
}
extern "C" {
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void *func_0223xxxx();
}
extern "C" {

}
extern "C" {

}
extern "C" {

}
extern "C" {
s32 PM_GetLCDPower();
}
extern "C" {
s32 PM_SetLCDPower(s32 a);
}
extern "C" {
void PM_SetBackLight(s32 a, s32 b);
}
extern "C" {
void PM_GetBackLight(void *a, void *b);
}
extern "C" {
void *func_020986c8(void *a);
}
extern "C" {
}
extern "C" {

}
extern "C" {

}
extern "C" {
}
extern "C" {
}
extern "C" {
extern u8 data_020e2e9c[];
}
extern "C" {
extern u8 data_020e2ea8[];
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern u8 gFieldSceneKind;
}
extern "C" {
extern BlockMap *gSceneBlockMap;
}
extern "C" {
extern u16 sSnowmanPrizeItems[];
}
extern "C" {
static inline BOOL R1(u16 *p, u32 lo, u32 hi) { BOOL r = FALSE; if (*p >= lo && *p <= hi) r = TRUE; return r; }
}
extern "C" {
static inline BOOL R2(u16 *p, u32 lo, u32 hi) { if (*p >= lo && *p <= hi) return TRUE; return FALSE; }
}
extern "C" {
static inline BOOL InRange(u32 c, u32 lo, u32 hi) { BOOL r = FALSE; if (c >= lo && c <= hi) r = TRUE; return r; }
}
extern "C" {
static inline BOOL IsEq(u32 c, u32 v) { if (c >= v && c <= v) return TRUE; return FALSE; }
}
extern "C" {
static inline BOOL IsZ() { if (gFieldSceneKind == 0) return TRUE; return FALSE; }
}

extern "C" void NookShop_Clear(NookShop *p);

}
extern "C" ShopAckCounter::ShopAckCounter() {
    using namespace n5; ShopAckCounter_Clear(this); }

extern "C" ShopAckCounter::~ShopAckCounter() {
    using namespace n5; ShopAckCounter_Clear(this); }

namespace n5 {
extern "C" void ShopAckCounter_Clear(ShopAckCounter *c) {
    c->needed = 0;
    c->received = 0;
}
extern "C" void ShopAckCounter_Start(ShopAckCounter *c) {
    c->received = 0;
    CommManager *p = gCommManager;
    if (p->isOnline()) c->needed = p->memberCount - 1;
    else c->needed = 0;
}
extern "C" BOOL ShopAckCounter_IsDone(ShopAckCounter *c) {
    if (c->received >= c->needed) return TRUE;
    return FALSE;
}
extern "C" BOOL ShopAckCounter_Add(ShopAckCounter *c) {
    if (c->received < c->needed) c->received++;
    return ShopAckCounter_IsDone(c);
}
extern "C" void StockList_AddFromPickList(ItemId *buf, u32 *pos, s32 r2, s32 r3, u32 n, s32 unused, u8 flag) {
    if (n != 0) {
        u16 tmp;
        {
            ItemPickSpec o(r2, r3);
            ItemPick_OneEx(&buf[*pos].id, n, &o, NULL, &sShopRandom, 0, 1, NULL);
        }
        if (flag) {
            for (u32 i = 0; i < n; i++) {
                Item_ToPlacedForm(&tmp, &buf[i + *pos].id, 1);
                buf[i + *pos].id = tmp;
            }
        }
        *pos += n;
    }
}
extern "C" void StockList_AddFromRange(ItemId *buf, u32 *pos, s32 r2, s32 r3, u32 n, s32 unused, u8 flag) {
    if (n != 0) {
        u16 tmp;
        ItemPick_FillFromRange(&buf[*pos].id, n, r2, r3, NULL, 0, 10, &sShopRandom, 0);
        if (flag) {
            for (u32 i = 0; i < n; i++) {
                Item_ToPlacedForm(&tmp, &buf[i + *pos].id, 1);
                buf[i + *pos].id = tmp;
            }
        }
        *pos += n;
    }
}
extern "C" void StockList_Clear(ItemId *a, u8 *b, u32 n) {
    for (u32 i = 0; i < n; i++) a[i].id = 0xfff1;
    u32 m = n / 8 + 1;
    for (u32 j = 0; j < m; j++) b[j] = 0;
}
extern "C" BOOL StockList_IsSold(u32 i, u32 n, u8 *bits) {
    if (i < n) {
        if ((bits[i >> 3] >> (i & 7)) & 1) return TRUE;
        return FALSE;
    }
    return TRUE;
}
extern "C" BOOL StockList_MarkSold(u32 i, u32 n, u8 *bits) {
    if (i < n && !StockList_IsSold(i, n, bits)) {
        bits[i >> 3] |= 1 << (i & 7);
        return TRUE;
    }
    return FALSE;
}
extern "C" u16 *StockList_GetItem(u32 i, ItemId *arr, u8 *bits, u32 n, u16 *out) {
    if (i < n) {
        u16 *p = &arr[i].id;
        if (out) *out = *p;
        if (StockList_IsSold(i, n, bits)) return &sStockSoldOutItem.id;
        return p;
    }
    return &sStockNoItem.id;
}
extern "C" s32 StockList_FindItem(u16 *key, ItemId *arr, u8 *bits, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        u16 *p = StockList_GetItem(i, arr, bits, n, 0);
        BOOL eq;
        if (Item_IsFurniture(p)) eq = Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(key);
        else eq = *p == *key;
        if (eq) {
            BOOL eq2;
            if (Item_IsFurniture(key)) eq2 = Item_GetFurnitureIndex(key) == Item_GetFurnitureIndex(&sStockSoldOutItem.id);
            else eq2 = *key == sStockSoldOutItem.id;
            if (!eq2) return i;
        }
    }
    return -1;
}
extern "C" void Shop_RemoveSoldItemAt(s32 x, s32 y, u32 a, s32 b) {
    if (IsZ()) return;
    if (a != Scene_GetCurrent()) return;
    BlockMap *w = gSceneBlockMap;
    s32 bx = x >> 4;
    s32 by = y >> 4;
    u16 *o = BlockMap_GetItemPtr(w, bx, by, x - (bx << 4), y - (by << 4), 0);
    if (o == 0) return;
    if (Item_IsFurnitureOrF031(o)) {
        void *r = FtrActorGrid_GetInstance();
        void *t = ((FtrActorGrid *)r)->getActor(x, y, 0);
        if (t != 0) {
            FtrMgr_RemoveActorByIndex(((FtrActorTable *)(FtrActorTable_GetInstance()))->indexOf(t));
        }
        if (b != 0) Snd_PlaySe(0x2e);
    } else if (Item_IsNormalItem(o)) {
        u16 *pc = (u16 *)o;
        if (!R1(pc, 0x1000, 0x10ff)) {
            if (!R2(pc, 0x151f, 0x151f)) BlockMap_SetItemAtUnit(w, &sStockSoldOutItem.id, x, y, 0);
        }
        if (b != 0) Snd_PlaySe(0x2e);
    }
}
extern "C" void Shop_RemoveSoldItem(u16 *p, u32 a, s32 b) {
    if (IsZ()) return;
    if (a != Scene_GetCurrent()) return;
    BlockMap *s = gSceneBlockMap;
    if (s == 0) return;
    MapBlock *q; u32 k = 0;
    if (s->width > k && s->height > k && s->blocks != 0) q = s->blocks;
    else q = 0;
    if (q == 0) return;
    for (s32 y = 0; y < 16; y++) {
        for (s32 x = 0; x < 16; x++) {
            u16 *e = MapBlock_GetItemPtr(q, x, y, 0);
            if (e == 0) continue;
            BOOL eq;
            if (Item_IsFurniture(e)) eq = Item_GetFurnitureIndex(e) == Item_GetFurnitureIndex(p);
            else eq = *e == *p;
            if (eq) {
                Shop_RemoveSoldItemAt(x, y, a, b);
                return;
            }
        }
    }
}
extern "C" void NookShop_PostPointSpecialNotice(s32 a, s32 b) {
    MailText_SetSlotMonth(0, a);
    MailText_SetSlotDayOrdinal(1, b);
    Bbs_PostMsgToday(Random_GlobalBelow(2), "bbs_shopinfo");
}
extern "C" void NookShop_PostSaleNotice(s32 x) {
    MsgString25 o;
    s32 m = x % 12;
    m = (u8)m;
    String_FormatNumber(&o, m, 10, 0, 0, 0);
    MailText_SetSlot(2, &o);
    Bbs_PostMsgToday(Random_GlobalBelow(2) + 2, "bbs_shopinfo");
}
extern "C" void NookShop_PostSpecialItemNotice(u16 *s) {
    ItemName str(s);
    MailText_SetSlot(3, &str);
    Bbs_PostMsgToday(Random_GlobalBelow(2) + 4, "bbs_shopinfo");
}
extern "C" void NookShop_PostRenovationNotice(s32 a, s32 b) {
    MailText_SetSlotMonth(2, a);
    MailText_SetSlotDayOrdinal(3, b);
    Bbs_PostMsgToday(NookShop_GetLevel(&data_021ed104), "bbs_raccoon");
}
extern "C" void NookShop_PostReopenNotice() {
    Bbs_PostMsgToday(NookShop_GetLevel(&data_021ed104) + 3, "bbs_raccoon");
}
extern "C" BOOL NookShop_GetReopenDateTime(ClockDateTime *out) {
    NookShop *h = &data_021ed104;
    if (NookShop_GetRenovation(h)->scheduled != 0) {
        out->year = NookShop_GetRenovation(h)->date.year;
        out->month = NookShop_GetRenovation(h)->date.month;
        out->day = NookShop_GetRenovation(h)->date.day;
        out->hour = 6;
        out->minute = 0;
        out->second = 0;
        out->unk_06 = 0;
        out->unk_07 = 0;
        return TRUE;
    }
    return FALSE;
}
extern "C" BOOL Shop_IsPurchaseSynced() {
    if (gCommManager->isOnline()) {
        return ShopAckCounter_IsDone(&sShopAckCounter);
    }
    return TRUE;
}
}
extern "C" NookShop::NookShop() {
    using namespace n5; NookShop_Clear(this); }

extern "C" Unk_020aec00::Unk_020aec00() {
    using namespace n5;
    for (s32 i = 0x25 - 1; i >= 0; i--) {
        ((ItemId *)&e[i])->~ItemId();
    }
}

namespace n5 {
extern "C" void NookShop_Clear(NookShop *p) {
    NookShop_ClearStock(p);
    p->packedState.level = 0;
    p->sales = 0;
    p->packedState.saleHour = 0;
    p->stockStale = 1;
    p->renovation.scheduled = 0;
}
}

namespace n4 {
extern "C" {
extern CommManager *gCommManager;
extern u8 data_021ee17c[], data_021ee180[], data_021ee20c[], gSaveData[];
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void NookShop_SetVisitState(int);
}
extern "C" {
u8 Scene_GetRequestedScene();
}
extern "C" {
int SceneId_IsNookShop(u32 a);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void NookPoints_SendMemberLetters();
}
extern "C" {
}
extern "C" {
void NookShop_PostSpecialItemNotice(u16*);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}


static inline BOOL inRange(u16 v, u16 lo, u16 hi) {
    BOOL r = FALSE;
    if (v >= lo && v <= hi) r = TRUE;
    return r;
}extern "C" {
}
extern "C" {
void NookShop_ScheduleRenovation(NookShop *self);
}
extern "C" {
}
extern "C" {
int NookShop_IsSold(NookShop *self, int idx);
}
extern "C" {
}
extern "C" {
u32 NookShop_GetUpgradeSales(NookShop *self, int mode);
}
extern "C" {
}
extern "C" {
int NookShop_IsClosedOn(NookShop *self, ClockDateTime *d);
}
extern "C" {
int NookShop_IsPointSpecialDay(NookShop *self, ClockDateTime *d);
}
extern "C" {
int NookShop_IsClosedNextDay(NookShop *self, ClockDateTime *d);
}
extern "C" {
void NookShop_NoteBuyer(NookShop *self, int f);
}
extern "C" {
}
extern "C" {
int NookShop_IsReopenDue(NookShop *self, ClockDateTime *d);
}
extern "C" {
int NookShop_IsClosedTomorrow(NookShop *self);
}
extern "C" {
int NookShop_HasVisitorBought(void*);
}
extern "C" {
void NookShop_Restock(NookShop *self, int a, int b, int c);
}
extern "C" {
int NookShop_IsStockStale(NookShop *self, ClockDateTime *d);
}
extern "C" {
void NookShop_SetStockDate(NookShop *self, ClockDateTime *d);
}
extern "C" {
static inline BOOL inRangeP(u16* p, u16 lo, u16 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}
}
extern "C" {
struct Rgba {
    u8 a, b, c, d;
};
}


extern "C" BOOL NookShop_IsSaleTime(NookShop *self) {
    ClockDateTime d;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    int v = self->packedState.saleHour;
    if (v != 0) {
        if (d.hour >= v && d.hour < 0x17) return TRUE;
        return FALSE;
    }
    return FALSE;
}
extern "C" int NookShop_IsPointSpecialDay(NookShop *self, ClockDateTime *d) {
    if (((SaveData *)(gSaveData))->testFlag(5) != 0 && self->pointSpecialDate.year == d->year && self->pointSpecialDate.month == d->month &&
        self->pointSpecialDate.day == d->day)
        return TRUE;
    return FALSE;
}
extern "C" int NookShop_IsPointSpecialToday(NookShop *self) {
    ClockDateTime d;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    return NookShop_IsPointSpecialDay(self, &d);
}
extern "C" BOOL NookShop_HasClass4Furniture(NookShop *self) {
    int z = 0;
    u32 i;
    for (i = 0; i < 0x25; i++) {
        u16 v = 0xfff1;
        u16* p = NookShop_GetItem(self, i, &v);
        if (Item_IsFurniture(p) != 0 && ItemList_GetTownClassRank(p, z) == 4) return TRUE;
    }
    return FALSE;
}
extern "C" NookShopRenovation *NookShop_GetRenovation(NookShop *self) {
    return &self->renovation;
}
extern "C" Rgba NookShop_GetClosedDate(NookShop *self) {
    Rgba r;
    ClockDateTime d;
    r.d = 0;
    r.a = r.d;
    r.b = r.a;
    r.c = r.b;
    if (NookShop_GetRenovation(self)->scheduled != 0) {
        ((u32*)&d)[0] = 0;
        ((u32*)&d)[1] = 0;
        d.year = NookShop_GetRenovation(self)->date.year;
        d.month = NookShop_GetRenovation(self)->date.month;
        d.day = NookShop_GetRenovation(self)->date.day;
        d.hour = 6;
        d.minute = 0;
        d.second = 0;
        d.unk_06 = 0;
        d.unk_07 = 0;
        DateTime_SubDays(&d, 1);
        r.c = d.year;
        r.b = d.month;
        r.a = d.day;
    }
    return r;
}
extern "C" int NookShop_IsReopenDue(NookShop *self, ClockDateTime *d) {
    ClockDateTime t;
    ((u32*)&t)[0] = 0;
    ((u32*)&t)[1] = 0;
    if (NookShop_GetReopenDateTime(&t) != 0) {
        if ((u32)(DateTime_Compare(&t, d, 0x3c) + 1) <= 1) return TRUE;
    }
    return FALSE;
}
extern "C" int NookShop_IsReopenDueNow(NookShop *self) {
    ClockDateTime d;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    return NookShop_IsReopenDue(self, &d);
}
extern "C" int NookShop_IsClosedOn(NookShop *self, ClockDateTime *d) {
    ClockDateTime t;
    if (NookShop_GetRenovation(self)->scheduled != 0) {
        ((u32*)&t)[0] = 0;
        ((u32*)&t)[1] = 0;
        t.year = NookShop_GetRenovation(self)->date.year;
        t.month = NookShop_GetRenovation(self)->date.month;
        t.day = NookShop_GetRenovation(self)->date.day;
        t.hour = 6;
        t.minute = 0;
        t.second = 0;
        t.unk_06 = 0;
        t.unk_07 = 0;
        DateTime_SubDays(&t, 1);
        if (t.year == d->year && t.month == d->month && t.day == d->day) return TRUE;
        return FALSE;
    }
    return FALSE;
}
extern "C" int NookShop_IsClosedToday(NookShop *self) {
    ClockDateTime d;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    return NookShop_IsClosedOn(self, &d);
}
extern "C" int NookShop_IsClosedNextDay(NookShop *self, ClockDateTime *d) {
    DateTime_AddDays(d, 1);
    return NookShop_IsClosedOn(self, d);
}
extern "C" int NookShop_IsClosedTomorrow(NookShop *self) {
    ClockDateTime d;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    return NookShop_IsClosedNextDay(self, &d);
}
extern "C" u32 NookShop_GetUpgradeSales(NookShop *self, int mode) {
    switch (mode) {
    case 0: return 0x61a8;
    case 1: return 0x15f90;
    case 2: return 0x3a980;
    default: return 0x3a980;
    }
}
extern "C" int NookShop_GetEarnedLevel(NookShop *self) {
    int t = NookShop_GetLevel(self);
    if (t == 3) return t;
    if (self->sales >= NookShop_GetUpgradeSales(self, t)) {
        int r = NookShop_HasVisitorBought(&data_021ed104);
        if (t == 2) {
            if (r != 0) return t + 1;
        } else {
            return t + 1;
        }
    }
    return NookShop_GetLevel(self);
}
extern "C" void NookShop_InitNew(NookShop *a) {
    NookShop_Clear(a);
}
extern "C" void NookShop_ClearStock(NookShop *self) {
    StockList_Clear(self->e, self->sold, 0x25);
}
extern "C" int NookShop_IsSold(NookShop *self, int idx) {
    return StockList_IsSold(idx, 0x25, self->sold);
}
extern "C" u16* NookShop_GetItem(NookShop *self, int idx, u16* p) {
    return StockList_GetItem(idx, self->e, self->sold, 0x25, p);
}
extern "C" int NookShop_FindItem(NookShop *self, u16 *key) {
    return StockList_FindItem(key, self->e, self->sold, 0x25);
}
extern "C" void NookShop_ScheduleRenovation(NookShop *self) {
    ClockDateTime d;
    ClockDateTime t;
    int r4 = NookShop_GetEarnedLevel(self);
    if (gCommManager->isOnline() != 0) return;
    if (NookShop_GetLevel(self) >= r4) return;
    if (NookShop_GetRenovation(self)->scheduled != 0) return;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    DateTime_AddDays(&d, 2);
    MI_CpuCopy8(&d, &t, 8);
    DateTime_SubDays(&t, 1);
    if (NookShop_IsPointSpecialDay(self, &t) != 0) DateTime_AddDays(&d, 1);
    NookShop_GetRenovation(self)->scheduled = 1;
    u8 u;
    u = d.year;
    NookShop_GetRenovation(self)->date.year = u;
    u = d.month;
    NookShop_GetRenovation(self)->date.month = u;
    u = d.day;
    NookShop_GetRenovation(self)->date.day = u;
    DateTime_SubDays(&d, 1);
    NookShop_PostRenovationNotice(d.month, d.day);
}
extern "C" void NookShop_AddSales(NookShop *self, int add, int arg) {
    u32 lim = NookShop_GetUpgradeSales(self, NookShop_GetLevel(self));
    self->sales += add;
    if (self->sales > lim) self->sales = lim;
    NookShop_NoteBuyer(self, arg);
    NookShop_ScheduleRenovation(self);
}
extern "C" BOOL NookShop_SellSlot(NookShop *self, u32 idx, int add, int arg) {
    if (idx < 0x25) {
        u32 lim = NookShop_GetUpgradeSales(self, NookShop_GetLevel(self));
        self->sales += add;
        if (self->sales > lim) self->sales = lim;
        if (NookShop_IsSold(self, idx) == 0) {
            u32 byte = idx >> 3;
            u32 bit = idx & 7;
            if (!inRangeP(NookShop_GetItem(self, idx, 0), 0x1000, 0x10ff)) {
                if (!inRangeP(NookShop_GetItem(self, idx, 0), 0x151f, 0x151f)) {
                    self->sold[byte] |= 1 << bit;
                }
            }
        }
        NookShop_NoteBuyer(self, arg);
        NookShop_ScheduleRenovation(self);
        return TRUE;
    } else {
        u32 lim = NookShop_GetUpgradeSales(self, NookShop_GetLevel(self));
        self->sales += add;
        if (self->sales > lim) self->sales = lim;
        NookShop_NoteBuyer(self, arg);
        NookShop_ScheduleRenovation(self);
        return FALSE;
    }
}
extern "C" void NookShop_NoteBuyer(NookShop *self, int flag) {
    if (flag == 0) ((SaveData *)(gSaveData))->setFlag(7);
}
extern "C" int NookShop_HasVisitorBought(void*) {
    return ((SaveData *)(gSaveData))->testFlag(7);
}
}
u32 data_020e2e34 = 3;
DateSeededRandomSource sShopRandom;
const u8 kNookSaplingCounts[4] = {0, 1, 2, 3};
namespace n4 {
extern "C" void NookShop_UpdateDaily(NookShop *self, int force) {
    int fresh;
    ClockDateTime d;
    int ok;
    int i;
    int n;
    void* p;

    AbleShop_UpdateDaily(&data_021ed2d4);
    if (NookShop_GetVisitState() == 1) {
        NookShop_SetVisitState(2);
        return;
    }
    if (SceneId_IsNookShop(Scene_GetRequestedScene()) == 0) {
        int r = Scene_GetCurrent();
        if (r == 0x2c) return;
        if (r == 0x3f) return;
    }
    fresh = 1;
    ((u32*)&d)[0] = 0;
    ((u32*)&d)[1] = 0;
    Clock_GetDateTime(&d);
    if (d.hour < 6) {
        DateTime_SubDays(&d, fresh);
        fresh = 0;
    }
    if (force == 0 && NookShop_IsStockStale(self, &d) == 0) return;
    self->packedState.saleHour = 0;
    if (gCommManager->isOnline() != 0) return;
    NookPoints_SendMemberLetters();
    NookShop_SetStockDate(self, &d);
    NookShop_Restock(self, d.year, d.month, d.day);
    ok = 1;
    int cnt = PlayerDataArray_CountUsed(gSavePlayers);
    if (cnt != 0 && cnt != 1) {
        for (i = 0; i < 4; i++) {
            p = PlayerData_GetResident(gSavePlayers, i);
            if (p != 0 && ((PlayerData *)(p))->isUsed() != 0 && ((PlayerData *)(p))->testFlag(1) == 0) {
                ok = 0;
                break;
            }
        }
    }
    if (ok == 0 && NookShop_GetRenovation(self)->scheduled == 0) {
        NookShop_UpdatePointSpecial(self, &d);
        if (sShopRandom.random(0xe) == 0) {
            self->packedState.saleHour = (u8)(sShopRandom.random(4) + 0x11);
            if (fresh != 0) NookShop_PostSaleNotice(self->packedState.saleHour);
        }
        if (self->packedState.saleHour == 0 && NookShop_IsPointSpecialDay(self, &d) == 0) {
            static ItemPickSpec sx(0, 4);
            if (sShopRandom.random(5) == 0) {
                for (i = 0; (u32)i < 0x25; i++) {
                    u16* q = &self->e[i].id;
                    if (Item_IsFurniture(q) != 0) {
                        ItemPickSpec spec = sx;
                        ItemPick_One(q, &spec, NULL, &sShopRandom, 0, 1, NULL);
                        if (fresh != 0) NookShop_PostSpecialItemNotice(q);
                        break;
                    }
                }
            }
        }
    }
    if (d.month == 0xc) {
        u8 v = d.day;
        int t = 0x2e;
        if (v >= 0xa && v <= 0x18)
            t = 0x2b;
        else if (v >= 0x1a && v <= 0x1f)
            t = 0x2c;
        if (t == 0x2e) return;
        n = 0;
        for (i = 0; (u32)i < 0x25; i++) {
            u16* q = &self->e[i].id;
            if (Item_IsFurniture(q) != 0) {
                if (n == 1) {
                    ItemPickSpec tmp(0, t);
                    {
                        ItemPickSpec spec = tmp;
                        ItemPick_One(q, &spec, NULL, &sShopRandom, 0, 1, NULL);
                    }
                    break;
                }
                n++;
            }
        }
    }
}
extern "C" void NookShop_Restock(NookShop *self, int a, int b, int c) {
    u32 z;
    NookShop_ClearStock(self);
    z = 0;
    sShopRandom.seed(a, b, c);
    NookShop_StockTools(self, &z);
    NookShop_StockFurniture(self, &z);
    NookShop_StockFlowerBags(self, &z);
    NookShop_StockSaplings(self, &z);
    NookShop_StockWallpaper(self, &z);
    NookShop_StockCarpets(self, &z);
    NookShop_StockStationery(self, &z);
    NookShop_StockPaint(self, &z);
    NookShop_StockBottle(self, &z);
    NookShop_StockMedicine(self, &z);
    NookShop_RestockEnd(self);
}
extern "C" int NookShop_IsStockStale(NookShop *self, ClockDateTime *d) {
    ClockDateTime t;
    MI_CpuCopy8(d, &t, 8);
    if (self->stockDate.year != t.year || self->stockDate.month != t.month || self->stockDate.day != t.day || self->stockStale != 0) return TRUE;
    return FALSE;
}
extern "C" void NookShop_SetStockDate(NookShop *self, ClockDateTime *d) {
    ClockDateTime t;
    MI_CpuCopy8(d, &t, 8);
    self->stockDate.year = t.year;
    self->stockDate.month = t.month;
    self->stockDate.day = t.day;
    self->stockStale = 0;
}
extern "C" BOOL NookShop_IsBlockingEvent(int x) {
    if (x < 0x1c) return TRUE;
    return FALSE;
}
}

namespace n3 {
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern u8 gSaveData[];
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
}
extern "C" {
void __cxa_vec_ctor(void*, u32, u32, void (*)(void*), void (*)(void*));
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
}
extern "C" {
BOOL Item_IsNookShop(u16 *p);
}
extern "C" {
u16 Item_MakeNookShop(u32);
}
extern "C" {
BOOL MapBlock_SetItem(void *cell, u16 *t, u32 x, u32 y, u8 z);
}
extern "C" {
}
extern "C" {
void NookShop_PostReopenNotice(void);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
s32 EventSchedule_CollectDayAll(E12 *a, ClockDateTime *d);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}


extern "C"

void NookShop_UpdatePointSpecial(NookShop *s, ClockDateTime *p) {
    ClockDateTime A;
    ClockDate B;
    ClockDateTime C, D, E, F, G, H, I;
    E12 arr1[7];
    E12 arr2[7];
    s32 mode;
    u8 d5;
    u8 e5;
    s32 n1;
    s32 n2;
    u8 d4;
    u8 d3;
    u8 e4;
    u8 e3;
    s32 k, i, cnt1, cnt2, r, r5;
    MI_CpuCopy8(p, &A, 8);
    mode = sShopRandom.random(2);
    if (((SaveData *)(gSaveData))->testFlag(5)) {
        Clock_GetDate(&B.day);
        r = Date_DaysBetween(&B.day, &s->pointSpecialDate.day);
        if (r >= 1) {
            ((SaveData *)(gSaveData))->clearFlag(5);
        } else if (r <= -7) {
            ((SaveData *)(gSaveData))->clearFlag(5);
        }
    }
    if (!((SaveData *)gSaveData)->testFlag(5)) {
        MI_CpuCopy8(p, &C, 8);
        k = Date_GetWeekday(C.year, C.month, C.day);
        if (k != 6 && k != 0) {
            r5 = 6 - k;
            if (r5 < 0) r5 = -r5;
            MI_CpuCopy8(&C, &D, 8);
            MI_CpuCopy8(&C, &E, 8);
            DateTime_AddDays(&D, r5);
            DateTime_AddDays(&E, r5 + 1);
            d4 = D.month;
            d3 = D.day;
            d5 = D.year;
            e4 = E.month;
            e3 = E.day;
            e5 = E.year;
            MI_CpuCopy8(&D, &H, 8);
            n1 = EventSchedule_CollectDayAll(arr1, &H);
            MI_CpuCopy8(&E, &I, 8);
            n2 = EventSchedule_CollectDayAll(arr2, &I);
            cnt1 = 0;
            cnt2 = 0;
            for (i = 0; i < n1; i++) {
                if (NookShop_IsBlockingEvent(arr1[i].h)) cnt1++;
            }
            for (i = 0; i < n2; i++) {
                if (NookShop_IsBlockingEvent(arr2[i].h)) cnt2++;
            }
            if (cnt1 == 0 && cnt2 == 0) {
                if (mode == 0) {
                    s->pointSpecialDate.year = d5;
                    s->pointSpecialDate.month = d4;
                    s->pointSpecialDate.day = d3;
                    s->pointSpecialDate.pad_03 = 0;
                } else {
                    s->pointSpecialDate.year = e5;
                    s->pointSpecialDate.month = e4;
                    s->pointSpecialDate.day = e3;
                    s->pointSpecialDate.pad_03 = 0;
                }
                ((SaveData *)(gSaveData))->clearFlag(6);
                ((SaveData *)(gSaveData))->setFlag(5);
            }
        }
    }
    if (((SaveData *)(gSaveData))->testFlag(5)) {
        ((u32*)&F)[0] = 0;
        ((u32*)&F)[1] = 0;
        F.year = s->pointSpecialDate.year;
        F.month = s->pointSpecialDate.month;
        F.day = s->pointSpecialDate.day;
        F.hour = 6;
        F.minute = 0;
        if (DateTime_Compare(&F, &A, 0x38) == -1) {
            ((SaveData *)(gSaveData))->clearFlag(5);
        } else {
            MI_CpuCopy8(&F, &G, 8);
            DateTime_SubDays(&G, 4);
            if (DateTime_Compare(&G, &A, 0x38) == -1) {
                if (DateTime_Compare(&A, &F, 0x38) == -1) {
                    if (!((SaveData *)gSaveData)->testFlag(6)) {
                        NookShop_PostPointSpecialNotice(s->pointSpecialDate.month, s->pointSpecialDate.day);
                        ((SaveData *)(gSaveData))->setFlag(6);
                    }
                }
            }
        }
    }
}
extern "C" void NookShop_RestockEnd(NookShop *s) {}
extern "C" u32 NookShop_GetLevel(NookShop *s) { return s->packedState.level & 3; }
extern "C" void NookShop_SetLevel(NookShop *s, u32 v) { s->packedState.level = (u16)(v & 3); }
extern "C" u32 NookShop_GetToolCount(NookShop *s) { return kNookToolCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetFurnitureCount(NookShop *s) { return kNookFurnitureCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetFlowerBagCount(NookShop *s) { return kNookFlowerBagCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetSaplingCount(NookShop *s) { return kNookSaplingCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetWallpaperCount(NookShop *s) { return kNookWallpaperCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetCarpetCount(NookShop *s) { return kNookCarpetCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetStationeryCount(NookShop *s) { return kNookStationeryCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetPaintCount(NookShop *s) { return kNookPaintCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetBottleCount(NookShop *s) { return kNookBottleCounts[NookShop_GetLevel(s)]; }
extern "C" u32 NookShop_GetMedicineCount(NookShop *s) { return 1; }
}
const u16 kNookMemberGiftItems[4] = {0x3860, 0x3864, 0x3868, 0x386c};
const u8 kNookFurnitureCounts[4] = {2, 3, 5, 8};
const u8 sReddStockOrders[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 2, 0}, {1, 0, 2}, {2, 0, 1}, {2, 1, 0}};
const u8 kNookCarpetCounts[4] = {1, 1, 2, 3};
u32 data_020e2e48 = 0x19;
const u8 kNookBottleCounts[4] = {1, 1, 1, 1};
const u16 kNookFlowerBagItems[12] = {0x14fe, 0x14ff, 0x1500, 0x1504, 0x1505, 0x1506, 0x150a, 0x150b, 0x150c, 0x1510, 0x1511, 0x1512};
const u8 kNookPaintCounts[4] = {0, 0, 0, 1};
s32 sNookShopVisitState;
const s32 sObjShadowCoordShift = 5;
namespace n3 {
extern "C" void NookShop_StockTools(NookShop *s, u32 *p) {
    static ItemId tbl[7] = {ItemId(0x1369), ItemId(0x1378), ItemId(0x1376), ItemId(0x1374), ItemId(0x156c), ItemId(0x136b), ItemId(0x137a)};
    s32 t = (NookShop_GetLevel(s) == 0) ? ~2 : 0;
    u32 start = *p;
    u32 i;
    StockList_AddFromRange(s->e, p, 0, t + 7, NookShop_GetToolCount(s), 0x25, 0);
    if (NookShop_GetLevel(s) == 0) {
        u32 cnt = 0;
        u32 j = 0;
        for (; j < NookShop_GetToolCount(s); j++) {
            u16 *q = &s->e[start + j].id;
            u32 m;
            if (Item_IsFurniture(q)) {
                u16 three = 3;
                u32 a = Item_GetFurnitureIndex(q);
                m = (a == Item_GetFurnitureIndex(&three)) ? 1 : 0;
            } else {
                m = (s->e[start + j].id == 3) ? 1 : 0;
            }
            if (m) cnt++;
        }
        if (cnt == 0) {
            u16 *d = &s->e[start + Random_GlobalBelow(2)].id;
            *d = 3;
        }
    }
    i = 0;
    for (; i < NookShop_GetToolCount(s); i++) {
        s->e[start + i].id = tbl[s->e[start + i].id].id;
    }
}
extern "C" void NookShop_StockFurniture(NookShop *s, u32 *p) {
    StockList_AddFromPickList(s->e, p, 0, 0, NookShop_GetFurnitureCount(s), 0x25, 0);
}
extern "C" void NookShop_StockFlowerBags(NookShop *s, u32 *p) {
    u32 start = *p;
    u32 i;
    StockList_AddFromRange(s->e, p, 0, 0xc, NookShop_GetFlowerBagCount(s), 0x25, 0);
    for (i = start; i < start + NookShop_GetFlowerBagCount(s); i++) {
        s->e[i].id = kNookFlowerBagItems[s->e[i].id];
    }
}
extern "C" void NookShop_StockSaplings(NookShop *s, u32 *p) {
    StockList_AddFromRange(s->e, p, 0x151d, 2, NookShop_GetSaplingCount(s), 0x25, 0);
}
extern "C" void NookShop_StockWallpaper(NookShop *s, u32 *p) {
    StockList_AddFromPickList(s->e, p, 4, 0, NookShop_GetWallpaperCount(s), 0x25, 0);
}
extern "C" void NookShop_StockCarpets(NookShop *s, u32 *p) {
    StockList_AddFromPickList(s->e, p, 3, 0, NookShop_GetCarpetCount(s), 0x25, 0);
}
extern "C" void NookShop_StockStationery(NookShop *s, u32 *p) {
    StockList_AddFromPickList(s->e, p, 1, 0, NookShop_GetStationeryCount(s), 0x25, 0);
}
extern "C" void NookShop_StockPaint(NookShop *s, u32 *p) {
    u32 i;
    for (i = 0; i < NookShop_GetPaintCount(s); i++) {
        u32 c = s->packedState.paintCounter & 0xf;
        u16 v;
        if (c < 16) v = 0x1521 + c; else v = 0x1521;
        s->e[(*p)++].id = v;
        s->packedState.paintCounter++;
    }
}
extern "C" void NookShop_StockBottle(NookShop *s, u32 *p) {
    StockList_AddFromRange(s->e, p, 0x151f, 1, NookShop_GetBottleCount(s), 0x25, 0);
}
extern "C" void NookShop_StockMedicine(NookShop *s, u32 *p) {
    StockList_AddFromRange(s->e, p, 0x155e, 1, NookShop_GetMedicineCount(s), 0x25, 0);
}
extern "C" u32 NookShop_ApplyRenovation(void) {
    u32 r6;
    MapBlock *r7;
    u32 y, x;
    if (NookShop_GetVisitState() == 1) return 0;
    if (NookShop_IsReopenDueNow(&data_021ed104)) {
        r6 = NookShop_GetEarnedLevel(&data_021ed104);
        TownBlockMap *t = TownBlockMap_Get();
        if (t) {
            r7 = BlockMap_FindBlockAnyAttr(t, 2);
            if (r7) {
                for (y = 0; y < 16; y++) {
                    for (x = 0; x < 16; x++) {
                        u16 *item;
                        if ((item = MapBlock_GetItemPtr(r7, x, y, 0)) && Item_IsNookShop(item)) {
                            u16 name;
                            ClockDateTimeWords a;
                            ClockDateTimeWords b;
                            name = Item_MakeNookShop(r6);
                            MapBlock_SetItem(r7, &name, x, y, 0);
                            NookShop_SetLevel(&data_021ed104, r6);
                            a.words[0] = 0; a.words[1] = 0;
                            if (NookShop_GetReopenDateTime(&a.dt)) {
                                b.words[0] = 0; b.words[1] = 0;
                                Clock_GetDateTime(&b.dt);
                                if (b.dt.year == a.dt.year && b.dt.month == a.dt.month && b.dt.day == a.dt.day) NookShop_PostReopenNotice();
                            }
                            NookShop_GetRenovation(&data_021ed104)->scheduled = 0;
                            NookShop_UpdateDaily(&data_021ed104, 1);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
extern "C" AbleShop *AbleShop_Construct(AbleShop *p) {
    for (s32 i = 0; i < 6; i++) {
        new (&p->items[i]) ItemId();
    }
    return p;
}
extern "C" AbleShop *AbleShop_Destruct(AbleShop *p) {
    for (s32 i = 6 - 1; i >= 0; i--) {
        p->items[i].~ItemId();
    }
    return p;
}
extern "C" void AbleShop_Clear(AbleShop *s) {
    StockList_Clear(s->items, s->sold, 6);
    s->stockStale = 1;
}
extern "C" void AbleShop_Reset(AbleShop *s) { AbleShop_Clear(s); }
extern "C" void AbleShop_InitNew() {}
extern "C" void AbleShop_UpdateDaily(AbleShop *s) {
    ClockDateTime t;
    ((u32*)&t)[0] = 0;
    ((u32*)&t)[1] = 0;
    Clock_GetDateTime(&t);
    if (t.hour < 6) DateTime_SubDays(&t, 1);
    if (!gCommManager->isOnline() && AbleShop_IsStockStale(s, &t)) {
        AbleShop_Restock(s, t.year, t.month, t.day);
        AbleShop_SetStockDate(s, &t);
    }
}
extern "C" void AbleShop_Restock(AbleShop *s, u32 a, u32 b, u32 c) {
    u32 x;
    AbleShop_Clear(s);
    sShopRandom.seed(a, b, c);
    x = 0;
    AbleShop_StockUmbrella(s, &x);
    AbleShop_StockShirts(s, &x);
    AbleShop_StockHeadwear(s, &x);
    AbleShop_StockAccessory(s, &x);
    AbleShop_RestockEnd(s);
}
extern "C" u32 AbleShop_IsStockStale(AbleShop *s, ClockDateTime *p) {
    ClockDateTime buf;
    MI_CpuCopy8(p, &buf, 8);
    if (s->stockDate.year != buf.year || s->stockDate.month != buf.month || s->stockDate.day != buf.day || s->stockStale != 0) return 1;
    return 0;
}
extern "C" void AbleShop_SetStockDate(AbleShop *s, ClockDateTime *p) {
    ClockDateTime buf;
    MI_CpuCopy8(p, &buf, 8);
    s->stockDate.year = buf.year;
    s->stockDate.month = buf.month;
    s->stockDate.day = buf.day;
    s->stockStale = 0;
}
extern "C" u16* AbleShop_GetItem(AbleShop *s, u32 a, u16 *c) {
    return StockList_GetItem(a, s->items, s->sold, 6, c);
}
extern "C" s32 AbleShop_FindItem(AbleShop *s, u16 *key) {
    return StockList_FindItem(key, s->items, s->sold, 6);
}
extern "C" u32 AbleShop_MarkSold(AbleShop *s, u32 a) {
    return StockList_MarkSold(a, 6, s->sold);
}
extern "C" u32 AbleShop_MarkSoldItem(AbleShop *s, u16 *key) {
    u32 i;
    for (i = 0; i < 6; i++) {
        u16 *p = AbleShop_GetItem(s, i, 0);
        BOOL m;
        if (Item_IsFurniture(p)) {
            m = (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(key)) ? TRUE : FALSE;
        } else {
            m = (*p == *key) ? TRUE : FALSE;
        }
        if (m) {
            return AbleShop_MarkSold(s, i);
        }
    }
    return 0;
}
extern "C" void AbleShop_StockUmbrella(AbleShop *a, u32 *b) {
    StockList_AddFromPickList(a->items, b, 7, 0x1d, 1, 6, 1);
}
extern "C" void AbleShop_StockShirts(AbleShop *a, u32 *b) {
    StockList_AddFromPickList(a->items, b, 2, 0, 3, 6, 1);
}
}

namespace n2 {
extern "C" {
u32 FengShui_GetTotal();
}
extern "C" {
u8 FengShui_GetEastTotal();
}
extern "C" {
u8 FengShui_GetSouthTotal();
}
extern "C" {
u32 ItemInfo_GetFullHeadwearClass1dCount();
}
extern "C" {
u32 ItemInfo_GetHatClass1dCount();
}
extern "C" {
}
extern "C" {
}
extern "C" {
void ReddLastSale_Clear(void *p);
}
extern "C" {

}
extern "C" {

}
extern "C" {
}
extern "C" {
}
extern "C" {
void func_02135558x();
}
extern "C" {
BOOL MapBlock_FindItemInRange(MapBlock *cell, s32 *x, s32 *z, ItemId *lo, ItemId *hi, u8 d);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern u8 gSaveData[];
}
extern "C" {
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)
}
extern "C" {
#define data_021ed284 HOST_LABEL(u8 (*)[], data_021ed284)
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern const char data_020e2e80[];
}
extern "C" {
extern const char data_020e2e90[];
}
extern "C" {
}
extern "C" {
extern u32 data_021ee170;
}
extern "C" {
extern void *data_021ee188x;
}
extern "C" {
extern u16 data_021ee16c;
}
extern "C" {
extern u8 data_021ee188[];
}


extern "C" {
void NookPoints_Clear(NookPoints *p);
}
extern "C" {
void NookPoints_Destruct(NookPoints *p);
}
extern "C" {
NookPoints *NookPoints_Construct(NookPoints *p);
}
extern "C" {
void NookPoints_Init(NookPoints *p);
}
extern "C" {
void NookPoints_Reset(NookPoints *p);
}

extern "C" u16 *ReddShop_GetItem(ReddShop *g, u32 a, u16 *b);



extern "C" void AbleShop_StockHeadwear(AbleShop *a, u32 *b) {
    u32 x = ItemInfo_GetHatClass1dCount();
    u32 y = ItemInfo_GetFullHeadwearClass1dCount();
    if (sShopRandom.random(x + y) < ItemInfo_GetHatClass1dCount()) {
        StockList_AddFromPickList(a->items, b, 6, 0x1d, 1, 6, 1);
    } else {
        StockList_AddFromPickList(a->items, b, 8, 0x1d, 1, 6, 1);
    }
}

extern "C" void AbleShop_StockAccessory(AbleShop *a, u32 *b) {
    StockList_AddFromPickList(a->items, b, 5, 0x1d, 1, 6, 1);
}

extern "C" void AbleShop_RestockEnd(AbleShop *s) {}}


ReddPasswordString::ReddPasswordString() {
    using namespace n2;
    clear();
}


ReddPasswordString::~ReddPasswordString() {
    using namespace n2;}


u8 *ReddPasswordString::data() {
    using namespace n2;
    return text;
}


u32 ReddPasswordString::capacity() {
    using namespace n2;
    return 0x21;
}


ReddPassword::ReddPassword() {
    using namespace n2;
    clear();
}


ReddPassword::~ReddPassword() {
    using namespace n2;}


void ReddPassword::clear() {
    using namespace n2;
    bits = 0;
    slot = -1;
    clearAllResidentKnows();
    ((SaveData *)(gSaveData))->clearFlag(8);
}


BOOL ReddPassword::pickPassword() {
    using namespace n2;
    if (slot == -1) {
        u32 cnt = countUnused();
        if (cnt != 0) {
            u32 target = Random_GlobalBelow(cnt);
            u32 n = 0;
            u32 i;
            for (i = 0; i < 32; i++) {
                if (!isUsed(i)) {
                    if (target == n) {
                        slot = i;
                        markUsed(i);
                        ReddLastSale_Clear(data_021ed284);
                        data_021ed2c0.restock();
                        clearAllResidentKnows();
                        ((SaveData *)(gSaveData))->clearFlag(8);
                        return TRUE;
                    }
                    n++;
                }
            }
        }
        return FALSE;
    }
    return TRUE;
}


BOOL ReddPassword::dropPassword() {
    using namespace n2;
    slot = -1;
    if (countUnused() == 0) {
        bits = 0;
    }
    clearAllResidentKnows();
    ((SaveData *)(gSaveData))->clearFlag(8);
    return TRUE;
}


u32 ReddPassword::getPromptText(void *w) {
    using namespace n2;
    if (slot != -1) {
        u8 b = (slot & 0x1f) << 1;
        return String_LoadResolveAltText((MsgString *)w, &b, "st_password");
    }
    return 0;
}


u8 ReddPassword::getAnswerIndex() {
    using namespace n2;
    if (slot != -1) {
        return slot * 2 + 1;
    }
    return 0;
}


u32 ReddPassword::getAnswerText(void *w) {
    using namespace n2;
    if (slot != -1) {
        u8 b = ((slot & 0x1f) << 1) + 1;
        return String_LoadResolveAltText((MsgString *)w, &b, "st_password");
    }
    return 0;
}


BOOL ReddPassword::needsLetter() {
    using namespace n2;
    if (slot != -1) {
        if (((SaveData *)(gSaveData))->testFlag(8) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}


void ReddPassword::markLetterSent() {
    using namespace n2;
    if (slot != -1) {
        ((SaveData *)(gSaveData))->setFlag(8);
    }
}


void ReddPassword::clearAllResidentKnows() {
    using namespace n2;
    flags = 0;
}


BOOL ReddPassword::residentKnows(u32 i) {
    using namespace n2;
    if (slot != -1) {
        return ((flags >> (i & 3)) & 1) != 0;
    }
    return FALSE;
}


void ReddPassword::setResidentKnows(u32 i) {
    using namespace n2;
    if (slot != -1) {
        flags |= 1 << (i & 3);
    }
}


void ReddPassword::clearResidentKnows(u32 i) {
    using namespace n2;
    flags &= ~(1 << (i & 3));
}
namespace n2 {


extern "C" void ReddPassword_ForgetVisitor() {
    sReddVisitorKnowsPassword = 0;
}

extern "C" BOOL ReddPassword_VisitorKnows() {
    if (((TownId *)(((PlayerData *)(PlayerData_GetCurrent()))->getPlayerId()))->getTownRelation() == 1) {
        return sReddVisitorKnowsPassword;
    }
    return FALSE;
}}


BOOL ReddPassword::setVisitorKnows() {
    using namespace n2;
    if (slot != -1) {
        if (((TownId *)(((PlayerData *)(PlayerData_GetCurrent()))->getPlayerId()))->getTownRelation() == 1) {
            sReddVisitorKnowsPassword = 1;
            return TRUE;
        }
    }
    return FALSE;
}


u32 ReddPassword::countUnused() {
    using namespace n2;
    u32 n = 0;
    u32 i;
    for (i = 0; i < 32; i++) {
        if (!isUsed(i)) {
            n++;
        }
    }
    return n;
}


BOOL ReddPassword::isUsed(u32 i) {
    using namespace n2;
    return (bits & (1 << (i & 0x1f))) != 0;
}


void ReddPassword::markUsed(u32 i) {
    using namespace n2;
    bits |= 1 << (i & 0x1f);
}


ReddShop::ReddShop() {
    using namespace n2;}


ReddShop::~ReddShop() {
    using namespace n2;}


void ReddShop::reset() {
    using namespace n2;
    clearStock();
    s.clear();
}


void ReddShop::clearStock() {
    using namespace n2;
    StockList_Clear(arr, sold, 3);
}
namespace n2 {


extern "C" void ReddShop_Reset(ReddShop *g) {
    g->reset();
}}


ReddPassword *ReddShop::getPassword() {
    using namespace n2;
    return &s;
}
namespace n2 {


}
u32 data_020e2e38 = 0x18;
const u8 kNookWallpaperCounts[4] = {1, 1, 2, 3};
u32 data_020e2e44 = 0xb;
u8 sReddVisitorKnowsPassword;
namespace n2 {
extern "C" BOOL ReddShop_IsTentOpen() {
    s32 x, z;
    ClockDateTimeWords now;
    BlockMap *map = TownBlockMap_Get();
    if (map != NULL) {
        MapBlock *b = BlockMap_FindBlockAnyAttr(map, 0x200);
        if (b != NULL) {
            static ItemId tmp(0x5012);
            if (MapBlock_FindItemInRange(b, &x, &z, &tmp, &tmp, 0) != 0) {
                now.words[0] = 0;
                now.words[1] = 0;
                Clock_GetDateTime(&now.dt);
                if (now.dt.hour >= 6) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

extern "C" void ReddPassword_ForgetResident(u32 i) {
    data_021ed2c0.getPassword()->clearResidentKnows((u8)i);
}

extern "C" BOOL ReddPassword_CurrentPlayerKnows() {
    void *p = PlayerData_GetCurrent();
    if (p != NULL) {
        PlayerId *q = ((PlayerData *)p)->getPlayerId();
        if (q->getTownRelation() == 1) {
            return ReddPassword_VisitorKnows();
        }
        u8 v = PlayerDataArray_FindById(gSavePlayers, (u16 *)q) & 3;
        return data_021ed2c0.getPassword()->residentKnows(v);
    }
    return FALSE;
}

extern "C" BOOL ReddPassword_LearnCurrentPlayer() {
    void *p = PlayerData_GetCurrent();
    if (p != NULL) {
        PlayerId *q = ((PlayerData *)p)->getPlayerId();
        if (q->getTownRelation() == 1) {
            return data_021ed2c0.getPassword()->setVisitorKnows();
        }
        u8 v = PlayerDataArray_FindById(gSavePlayers, (u16 *)q) & 3;
        data_021ed2c0.getPassword()->setResidentKnows(v);
        return TRUE;
    }
    return FALSE;
}

extern "C" void ReddShop_SendPasswordLetters() {
    data_021ed2c0.getPassword()->pickPassword();
    if (data_021ed2c0.getPassword()->needsLetter()) {
        if (gCommManager->isOnline() == 0) {
            Letter ctx;
            u8 r = Random_GlobalBelow(3);
            ReddPasswordString w;
            data_021ed2c0.getPassword()->getAnswerText(&w);
            MailText_SetSlot(2, &w);
            s32 i;
            for (i = 0; i < 4; i++) {
                void *p = PlayerData_GetResident(gSavePlayers, i);
                if (p != NULL && ((PlayerData *)p)->isUsed() != 0 && ((PlayerData *)p)->testFlag(12) != 0) {
                    Letter_ComposeFromMail((LetterView *)&ctx, &r, "sp_npc_foxmail", (u8 *)&data_020e2e44, (u8 *)&data_020e2e48, ((PlayerData *)p)->getPlayerId());
                    if (LetterDelivery_PutInAddresseeMailbox(&ctx) == 0) {
                        LetterDelivery_QueueOutgoing(&ctx, 0);
                    }
                }
            }
            data_021ed2c0.getPassword()->markLetterSent();
        }
    }
}}


void ReddShop::restock() {
    using namespace n2;
    u16 buf[3];
    u16 *p;
    u32 a, b;
    u32 i;
    clearStock();
    a = FengShui_GetTotal() / 10 + 0x32;
    if (Random_GlobalBelow(100) < a) {
        ItemPickSpec q(0, 0x26);
        ItemPick_One(&arr[0].id, &q, NULL, NULL, 0, 1, NULL);
    } else {
        ItemPickSpec q(0, 0x27);
        ItemPick_One(&arr[0].id, &q, NULL, NULL, 0, 1, NULL);
    }
    b = (FengShui_GetEastTotal() + FengShui_GetSouthTotal()) / 10 + 0x32;
    for (i = 1; i < 3; i++) {
        if (Random_GlobalBelow(100) < b) {
            ItemPickSpec q(0, 5);
            ItemPick_One(&arr[i].id, &q, NULL, NULL, 0, 1, NULL);
        } else {
            ItemPickSpec q(0, 0);
            ItemPick_One(&arr[i].id, &q, NULL, NULL, 0, 1, NULL);
        }
    }
    buf[0] = 0xfff1;
    buf[1] = 0xfff1;
    buf[2] = 0xfff1;
    for (i = 0; i < 3; i++) {
        buf[i] = arr[i].id;
    }
    u32 r = Random_GlobalBelow(6);
    for (i = 0; i < 3; i++) {
        arr[i].id = buf[sReddStockOrders[r][i]];
    }
}
namespace n2 {


extern "C" u32 ReddShop_MarkSold(ReddShop *g, u32 a) {
    return StockList_MarkSold(a, 3, g->sold);
}

extern "C" u32 ReddShop_MarkSoldItem(ReddShop *g, u16 *ptr) {
    u32 i;
    for (i = 0; i < 3; i++) {
        u16 *p = ReddShop_GetItem(g, i, 0);
        BOOL eq;
        if (Item_IsFurniture(p) != 0) {
            eq = Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(ptr);
        } else {
            eq = *p == *ptr;
        }
        if (eq) {
            return ReddShop_MarkSold(g, i);
        }
    }
    return 0;
}

extern "C" u16 *ReddShop_GetItem(ReddShop *g, u32 a, u16 *b) {
    return StockList_GetItem(a, g->arr, g->sold, 3, b);
}

extern "C" s32 ReddShop_FindItem(ReddShop *g, u16 *key) {
    return StockList_FindItem(key, g->arr, g->sold, 3);
}

extern "C" NookPoints *NookPoints_Create(NookPoints *p) {
    NookPoints_Construct(p);
    NookPoints_Init(p);
    return p;
}

extern "C" NookPoints *NookPoints_Destroy(NookPoints *p) {
    NookPoints_Destruct(p);
    return p;
}

extern "C" void NookPoints_Reset(NookPoints *p) {
    NookPoints_Clear(p);
}

extern "C" void NookPoints_Init(NookPoints *p) {
    NookPoints_Reset(p);
}

extern "C" u16 *NookPoints_GetValuePtr(NookPoints *p) { return (u16 *)p; }

extern "C" NookPoints *NookPoints_Construct(NookPoints *p) {
    NookPoints_Clear(p);
    return p;
}

extern "C" void NookPoints_Destruct(NookPoints *p) {}

extern "C" void NookPoints_Clear(NookPoints *p) {
    p->v = 0;
}
}
namespace n1 {
extern "C" {
s32 FX_Div(s32 a, s32 b);
}
extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
}
extern "C" {
u32 _s32_div_f(u32 a, u32 b);
}
extern "C" {
}
extern "C" {
void NNS_G3dMdlSetMdlDiff(u32 a, u32 b, u32 c);
}
extern "C" {
void NNSi_G3dModifyMatFlag(u32 a, u32 b, u32 c);
}
extern "C" {
void Mtx43_SetTranslate(void *m, s32 a, s32 b, s32 c);
}
extern "C" {
void Mtx43_RotateX(void *m, s32 a);
}
extern "C" {
void Mtx43_Scale(void *m, s32 a, s32 b, s32 c);
}
extern "C" {
void MTX_Concat43(void *a, void *b, void *c);
}
extern "C" {
void VEC_Normalize(void *a, void *b);
}
extern "C" {
s32 Ground_GetDefaultY(s32 a);
}
extern "C" {
void func_020339bc(GroundInfoBase *p, VecFx32 *pos, s32 a, s32 b);
}
extern "C" {
s32 func_02033914(GroundInfoBase *p, s32 a);
}
extern "C" {
void GroundInfo_Destruct(GroundInfoBase *p);
}
extern "C" {
BOOL Scene_InMuseumRoom(void);
}
extern "C" {
void func_0205553c(void *a, VecFx32 *scale);
}
extern "C" {
void func_02054b14(void *a);
}
extern "C" {
u8 SceneLights_GetLightParam(s32 a);
}
extern "C" {
}
extern "C" {
BOOL func_02054c88(void *a, void *b, s32 c);
}
extern "C" {
void func_02000c8c();
}
extern "C" {
extern u8 gFieldSceneKind;
}
extern "C" {
extern u32 sCharaShadowModelPath;
}
extern "C" {
extern u8 data_021f47e0[];
}
extern "C" {
extern u8 data_021edf04[];
}
extern "C" {
}
extern "C" {
extern u32 data_021edf3c;
}
extern "C" {
extern ObjShadowTexDef sObjShadowTexDefs[];
}
extern "C" {
extern u8 sObjShadowTexPath[];
}
extern "C" {
extern u8 sObjShadowPlttNameFmt[];
}
extern "C" {
u8 *NNS_G3dGetTex(void *p);
}
extern "C" {
void Gfx3d_LoadTexAndPltt(void *p, s32 a);
}
extern "C" {
u8 *Gfx3d_CopyTex(void *p, s32 heap);
}
extern "C" {
u32 func_02057100(u8 *base, char *name);
}
extern "C" {
u32 func_02057078(u8 *base, char *name);
}
extern "C" {
extern u32 data_021edf40;
}
extern "C" {
extern s32 data_021edf48;
}
extern "C" {
}
extern "C" {
extern VecFx32 gCameraLookAt;
}
extern "C" {
BOOL Scene_InTown(void);
}
extern "C" {
}
extern "C" {
void NookShop_SetVisitState(int v);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
void Shop_RecordPurchase(u32 a, u32 b, u32 c, u32 d, int mode, u8 flag, int e);
}
extern "C" {
void ReddShop_RecordPurchase(u32 a, u32 b, u8 c, u32 d);
}
extern "C" {
BOOL SceneId_IsNookShop(u32 v);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
BOOL NookShop_CanTakeCatalogOrder(void);
}
extern "C" {
void Item_FromPlacedForm(void *a, void *b);
}
extern "C" {
}
extern "C" {

}
extern "C" {
}
extern "C" {

}
extern "C" {
}
extern "C" {
}
extern "C" {
void NookPoints_AddForPurchase(u16 *p, u32 v);
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
u32 NookPoints_GetRank(u32 v);
}
extern "C" {
u32 NookPoints_GetRankThreshold(u32 i);
}
extern "C" {
void NookPoints_Add(u16 *p, u32 add);
}
extern "C" {
void NookPoints_SendMemberLetters(void);
}
extern "C" {
extern CommManager *gCommManager;
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
}
extern "C" {
extern u8 data_020e2e64[];
}
extern "C" {
}
extern "C" {
extern u8 data_020e2e74[];
}

static inline BOOL inRange2(const u16 &a, const u16 &b) {
    BOOL r = FALSE;
    if (b >= 0x151d && a <= 0x151e) {
        r = TRUE;
    }
    return r;
}

static inline BOOL inRange2v(volatile u16 *p) {
    BOOL r = FALSE;
    u16 a = *p;
    u16 b = *p;
    if (b >= 0x151d && a <= 0x151e) {
        r = TRUE;
    }
    return r;
}

static inline BOOL cmp16(u16 *a, u16 *b) {
    if (Item_IsFurniture(a)) {
        return Item_GetFurnitureIndex(a) == Item_GetFurnitureIndex(b);
    }
    return *a == *b;
}

static inline BOOL isOne() {
    if (gFieldSceneKind == 1) {
        return TRUE;
    }
    return FALSE;
}
static inline void *Unk_020ac500_Data(const NNSG3dResDict *dict, u32 idx) {
    NNSG3dResDictEntryHeader *hdr = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
    return &hdr->data[hdr->sizeUnit * idx];
}
static inline u32 *Unk_020ac500_TexData(const NNSG3dResTex *tex, u32 idx) {
    return (u32 *)Unk_020ac500_Data(&tex->dict, idx);
}
static inline NNSG3dResDictPlttData *Unk_020ac500_PlttData(const NNSG3dResTex *tex, u32 idx) {
    return (NNSG3dResDictPlttData *)Unk_020ac500_Data((const NNSG3dResDict *)((u8 *)tex + tex->ofsPlttDict), idx);
}




extern "C" void NookPoints_SendMemberLetters(void) {
    if (!gCommManager->isOnline()) {
        void *r5 = PlayerData_GetCurrent();
        if (r5) {
            u32 n = NookPoints_GetRank(*NookPoints_GetValuePtr(static_cast<NookPoints *>(((PlayerData *)r5)->getNookPoints())));
            if (n) {
                u32 i;
                int z = 0;
                for (i = 0; i < n; i++) {
                    u32 j = i + 0x1c;
                    if (i < 4 && !((PlayerData *)r5)->testFlag(j)) {
                        Letter obj;
                        u8 ib;
                        ib = i;
                        Letter_ComposeFromMail((LetterView *)&obj, &ib, "sp_npc_atm", (u8 *)&data_020e2e34, (u8 *)&data_020e2e38, ((PlayerData *)r5)->getPlayerId());
                        ((LetterView *)&obj)->setPresent(kNookMemberGiftItems[i & 3], 1);
                        if (LetterDelivery_QueueOutgoing(&obj, z)) {
                            ((PlayerData *)(r5))->setFlag(j);
                        }
                    }
                }
            }
        }
    }
}

extern "C" void NookPoints_Add(u16 *p, u32 add) {
    u32 k = NookPoints_GetRank(*p);
    int s = add + *p;
    if (s >= 0xc350) {
        s = 0xc350;
    }
    *p = s;
    if (k != NookPoints_GetRank(*p)) {
        NookPoints_SendMemberLetters();
    }
}

extern "C" void NookPoints_AddForPurchase(u16 *p, u32 v) {
    u16 t = _s32_div_f(v, 100);
    if (NookShop_IsPointSpecialToday(&data_021ed104)) {
        t = t * 5;
    }
    NookPoints_Add(p, t);
}

extern "C" u32 NookPoints_GetRank(u32 v) {
    int i;
    for (i = 4; i >= 0; i--) {
        if (v >= NookPoints_GetRankThreshold(i)) {
            return i;
        }
    }
    return 0;
}

extern "C" u32 NookPoints_GetRankThreshold(u32 i) {
    if (i < 5) {
        return kNookPointRankThresholds[i];
    }
    return 0;
}

extern "C" u16 NookPoints_GetToNextRank(u16 *p) {
    u32 k = NookPoints_GetRank(*p);
    if (k != 4) {
        return NookPoints_GetRankThreshold(k + 1) - *p;
    }
    return 0;
}

extern "C" void Shop_RecordPurchase(u32 a, u32 b, u32 c, u32 d, int mode, u8 flag, int e) {
    u16 cur;
    Pack p1;
    s32 x, y;
    Pack p2;
    e = e;
    if (a == 0x3f) {
        NookShop_AddSales(&data_021ed104, b, d);
        if (gCommManager->isOnline() && flag) {
            p1.a = a;
            p1.b = b;
            p1.c = d;
            p1.d = c;
            void *h = gCommManager;
            ((CommManager *)(h))->beginRecord();
            ((CommManager *)(h))->writeRecord((u8 *)(&p1), 4);
            ((CommManager *)(h))->endRecord(0x26, 4);
        }
    } else {
        cur = sStockSoldOutItem.id;
        switch (mode) {
        case 0:
            cur = *NookShop_GetItem(&data_021ed104, a, 0);
            break;
        case 1:
            cur = *AbleShop_GetItem(&data_021ed2d4, a, 0);
            break;
        case 2:
            cur = *ReddShop_GetItem(&data_021ed2c0, a, 0);
            break;
        }
        if (!cmp16(&cur, &sStockSoldOutItem.id)) {
            switch (mode) {
            case 0:
                NookShop_SellSlot(&data_021ed104, a, b, d);
                if (flag) {
                    NookPoints_AddForPurchase(NookPoints_GetValuePtr(static_cast<NookPoints *>(((PlayerData *)(PlayerData_GetCurrent()))->getNookPoints())), b);
                }
                if (isOne()) {
                    if (ShopStock_FindTileOfStock(&x, &y, a)) {
                        if (a == 0x3f) {
                            e = 0;
                        }
                        Shop_RemoveSoldItemAt(x, y, c, e);
                    }
                }
                break;
            case 1:
                AbleShop_MarkSoldItem(&data_021ed2d4, &cur);
                Shop_RemoveSoldItem(&cur, c, e);
                break;
            case 2:
                ReddShop_MarkSoldItem(&data_021ed2c0, &cur);
                Shop_RemoveSoldItem(&cur, c, e);
                break;
            }
            if (gCommManager->isOnline() && flag) {
                p2.a = a;
                p2.b = b;
                p2.c = d;
                p2.d = c;
                void *h = gCommManager;
                ((CommManager *)(h))->beginRecord();
                ((CommManager *)(h))->writeRecord((u8 *)(&p2), 4);
                ((CommManager *)(h))->endRecord(0x26, 4);
            }
        }
    }
}

extern "C" void NookShop_RecordBuyback(int a) {
    BOOL x = ((TownId *)(((PlayerData *)(PlayerData_GetCurrent()))->getPlayerId()))->getTownRelation() == 0;
    if (a > 0x249f0) {
        a = 0x249f0;
    }
    Shop_RecordPurchase(0x3f, a, Scene_GetCurrent(), x, 0, 1, 0);
}

extern "C" void NookShop_BuyAt(u32 a, u32 b, u32 c, u32 d) {
    u16 v[2];
    u32 r;
    v[0] = *ShopStock_GetItemAt(a, b);
    if (inRange2(v[0], v[0]) && Scene_GetCurrent() == 0x1d) {
        u32 i;
        v[1] = 0xfff1;
        for (i = 0; i < 0x25; i++) {
            NookShop_GetItem(&data_021ed104, i, &v[1]);
            if (inRange2v(&v[1])) {
                break;
            }
        }
        r = i + ShopStock_GetCode22Index(a, b);
    } else {
        r = NookShop_FindItem(&data_021ed104, v);
    }
    if (r != (u32)-1) {
        BOOL x = ((TownId *)(((PlayerData *)(PlayerData_GetCurrent()))->getPlayerId()))->getTownRelation() == 0;
        ShopAckCounter_Start(&sShopAckCounter);
        Shop_RecordPurchase(r, c, d, x, 0, 1, 0);
    }
}

extern "C" u32 NookShop_IsPurchaseSynced(void) {
    return Shop_IsPurchaseSynced();
}

extern "C" BOOL NookShop_CanTakeCatalogOrder(void) {
    if (gCommManager->isOnline()) {
        return FALSE;
    }
    if (LetterDelivery_HasFreeOutgoingSlot()) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL NookShop_SendCatalogOrder(void *name) {
    if (NookShop_CanTakeCatalogOrder()) {
        u16 id;
        u8 by;
        Item_FromPlacedForm(&id, name);
        ItemName s1(&id);
        MailText_SetSlot(1, &s1);
        Letter obj;
        void *r4 = PlayerData_GetCurrent();
        NookShop *d = &data_021ed104;
        by = NookShop_GetLevel(d);
        Letter_ComposeFromMail((LetterView *)&obj, &by, "sp_npc_raccoon", (u8 *)&data_020e2e40, (u8 *)&data_020e2e3c, ((PlayerData *)r4)->getPlayerId());
        ((LetterView *)&obj)->setPresent(id, 1);
        u32 r = Item_GetMemberPrice(&id);
        if (LetterDelivery_QueueOutgoing(&obj, 0)) {
            NookShop_AddSales(d, r, 1);
            NookPoints_AddForPurchase(NookPoints_GetValuePtr(static_cast<NookPoints *>(((PlayerData *)(PlayerData_GetCurrent()))->getNookPoints())), r);
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void AbleShop_BuyAt(u32 a, u32 b, u32 c) {
    u16 v = *ShopStock_GetItemAtTile(a, b);
    u32 r = AbleShop_FindItem(&data_021ed2d4, &v);
    if (r != (u32)-1) {
        ShopAckCounter_Start(&sShopAckCounter);
        Shop_RecordPurchase(r, 0, c, 1, 1, 1, 0);
    }
}

extern "C" u32 AbleShop_IsPurchaseSynced(void) {
    return Shop_IsPurchaseSynced();
}

extern "C" void ReddShop_RecordPurchase(u32 a, u32 b, u8 c, u32 d) {
    Shop_RecordPurchase(a, 0, b, 1, 2, c, d);
}

extern "C" void ReddShop_BuyAt(u32 a, u32 b, u32 c) {
    u32 r = ReddShop_FindItem(&data_021ed2c0, ShopStock_GetItemAt(a, b));
    if (r != (u32)-1) {
        ShopAckCounter_Start(&sShopAckCounter);
        ReddShop_RecordPurchase(r, c, 1, 0);
    }
}

extern "C" u32 ReddShop_IsPurchaseSynced(void) {
    return Shop_IsPurchaseSynced();
}

extern "C" void Shop_OnPurchaseRecord(Bits *p, u32 arg) {
    u32 a = p->a;
    u8 d = p->d;
    BOOL c = p->c ? TRUE : FALSE;
    if (d == 10) {
        Shop_RecordPurchase(a, 0, d, 1, 1, 0, 1);
    } else if (d == 15) {
        ReddShop_RecordPurchase(a, d, 0, 1);
    } else if (SceneId_IsNookShop(d)) {
        Shop_RecordPurchase(a, p->b, d, c, 0, 0, 1);
    }
    if (a != 0x3f) {
        void *h = gCommManager;
        ((CommManager *)(h))->beginRecord();
        ((CommManager *)(h))->endRecord(0x27, arg);
    }
}

extern "C" u32 Shop_OnPurchaseAck(void) {
    return ShopAckCounter_Add(&sShopAckCounter);
}

extern "C" void NookShop_PickFlowerBag(u16 *p) {
    *p = kNookFlowerBagItems[Random_GlobalBelow(12)];
}

extern "C" BOOL NookShop_IsOpenHour(void) {
    u8 s[4];
    Clock_GetMinuteHour(s);
    if (s[1] >= 8 && s[1] < 0x17) {
        return TRUE;
    }
    return FALSE;
}

extern "C" int NookShop_GetVisitState(void) {
    return sNookShopVisitState;
}

extern "C" void NookShop_SetVisitState(int v) {
    sNookShopVisitState = v;
}

extern "C" void NookShop_OnSceneLoad(void) {
    if (Scene_InTown()) {
        if (NookShop_GetVisitState() == 2) {
            if (!gCommManager->isOnline()) {
                NookShop_ApplyRenovation();
                NookShop_UpdateDaily(&data_021ed104, 0);
            }
        }
        NookShop_SetVisitState(0);
    }
}}


ItemId sStockNoItem(0xfff1);
u32 data_020e2e40 = 3;
const u8 kNookStationeryCounts[4] = {1, 2, 3, 4};
const u8 kNookFlowerBagCounts[4] = {1, 2, 4, 7};
ItemId sStockSoldOutItem(0x1547);
const u8 kNookToolCounts[4] = {2, 3, 4, 6};
u32 data_020e2e3c = 0x18;
const u16 kNookPointRankThresholds[6] = {0, 0x12c, 0x1388, 0x2710, 0x4e20, 0};
ShopAckCounter sShopAckCounter;

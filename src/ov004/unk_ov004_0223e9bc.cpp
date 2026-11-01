#pragma opt_loop_invariants off
#include "types.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "Unk_020d8c7c.h"
#include "item/ItemId.h"
#include "sys/ProcProfile.h"
#include "room/FtrActorGrid.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov004/unk_ov004_0223e9bc.h"
#include "proto/main/unk_0204cc1c.h"

class ShopStockPlacer;

extern "C" {
extern BlockMap *gSceneBlockMap;
#define data_021ed104 HOST_LABEL(u8 (*)[], data_021ed104)
#define data_021ed2d4 HOST_LABEL(u8 (*)[], data_021ed2d4)
#define data_021ed2c0 HOST_LABEL(u8 (*)[], data_021ed2c0)
extern const u32 sNookShopLayouts[];
extern const u32 sScene10ShopLayout[];
extern const u32 sScene15ShopLayout[];

BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
BOOL Item_IsFurnitureOrF031(u16 *p);
BOOL Item_IsNormalItem(u16 *p);
BOOL Item_IsHoldable(u16 *p);
s32 Item_GetKind(u16 *p);
u16 Item_MakeFurniture(s32 a, s32 b);
u32 Scene_GetCurrent();
BOOL Scene_InNookShop();
BOOL SceneId_IsNookShop(u32 id);
s32 Scene_GetNookShop();
void Item_FromPlacedForm(u16 *out, u16 *in);
u16 *AbleShop_GetItem(void *tbl, s32 idx, u16 *out);
u16 *NookShop_GetItem(void *tbl, s32 idx, u16 *out);
s32 NookShop_FindItem(void *tbl, u16 *p);
s32 AbleShop_FindItem(void *tbl, u16 *p);
s32 ReddShop_FindItem(void *tbl, u16 *p);
s32 FtrActor_GetFtrIndex(void *o);

u16 *ReddShop_GetItem(void *p, u32 a, void *b);
}

class ShopStockPlacer : public GameProc {
public:
    typedef BOOL (ShopStockPlacer::*Fn)();

    ShopStockPlacer();
    virtual ~ShopStockPlacer();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    BOOL setupScene10Shop();
    BOOL setupNookShop();
    void placeScene10Stock();
    void placeNookStock();
    BOOL placeItem(u16 *item, s32 code);
    BOOL setupNoShop();
    BOOL setupScene15Shop();
    void placeScene15Stock();
    static u16 *callGetItemAt(s32 x, s32 y);

    /* 0x50 */ s32 nookShop;
    /* 0x54 */ s32 shopKind;
};

static inline BOOL Unk_ov004_0223eb8c_Chk(u16 *p) {
    u16 c = 0xfff1;
    if (Item_IsFurniture(p)) {
        s32 a = Item_GetFurnitureIndex(p);
        if (a == Item_GetFurnitureIndex(&c)) return TRUE;
        return FALSE;
    }
    if (*p == 0xfff1) return TRUE;
    return FALSE;
}


static inline BOOL Unk_ov004_0223ed40_Chk(u16 *p, u16 *c, u16 k) {
    if (Item_IsFurniture(p)) {
        *c = k;
        s32 a = Item_GetFurnitureIndex(p);
        if (a == Item_GetFurnitureIndex(c)) return TRUE;
        return FALSE;
    }
    if (*p == k) return TRUE;
    return FALSE;
}

static inline BOOL Unk_ov004_0223f210_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

extern "C" ShopStockPlacer *ShopStockPlacer_Create() { return new ShopStockPlacer; }

extern "C" const u32 *ShopStock_GetLayout() {
    if (Scene_InNookShop()) {
        return sNookShopLayouts + (Scene_GetNookShop() << 8);
    }
    if (Scene_GetCurrent() == 10) return sScene10ShopLayout;
    return sScene15ShopLayout;
}

extern "C" s32 ShopStock_GetItemCode(u16 *p) {
    u16 c;
    Item_FromPlacedForm(&c, p);
    if (Item_IsFurniture(&c)) return 0x19;
    if (Item_IsHoldable(&c)) goto e;
    if (!Unk_ov004_0223f210_R(&c, 0x156c, 0x156c)) goto rest;
e:
    return 0x42;
rest:
    if (c >= 0x13a8 && c <= 0x13c7) return 9;
    return Item_GetKind(&c);
}

ShopStockPlacer::ShopStockPlacer() {}

ShopStockPlacer::~ShopStockPlacer() {}

ProcProfile sShopStockPlacerProfile = {(void *(*)())ShopStockPlacer_Create, 0xc6, 0xd3};

const u32 sNookShopLayouts[1536] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x1, 0, 0x19, 0, 0x19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x4, 0, 0x42, 0x42, 0x31, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x19, 0, 0, 0x1, 0x2, 0x42, 0x42, 0x42, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x19, 0, 0, 0x4, 0x4, 0x29, 0x31, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x19, 0, 0, 0x20, 0x20, 0x22, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x19, 0, 0x19, 0, 0x19, 0, 0x19, 0, 0x19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x20, 0, 0x1, 0x1, 0x2, 0x2, 0, 0x29, 0x31, 0, 0, 0, 0, 0, 0,
    0, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x20, 0, 0x42, 0, 0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x20, 0, 0x42, 0, 0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x22, 0, 0x42, 0, 0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x22, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x4, 0, 0x20, 0x20, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x4, 0, 0x20, 0x20, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x4, 0, 0x22, 0x20, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x4, 0, 0x22, 0x20, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x29, 0, 0x22, 0x20, 0, 0x42, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x1, 0, 0x19, 0, 0x19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x2, 0, 0, 0, 0, 0, 0, 0, 0x19, 0, 0, 0, 0, 0, 0,
    0, 0x2, 0, 0x19, 0, 0x19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0x26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x19, 0, 0x19, 0, 0, 0, 0x19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u32 sScene10ShopLayout[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x42, 0x5, 0x5, 0x5, 0x9, 0xa, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0x31, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u32 sScene15ShopLayout[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0x19, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0x19, 0, 0, 0, 0x19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0x31, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

BOOL ShopStockPlacer::onCreate() {
    nookShop = Scene_GetNookShop();
    if (Scene_InNookShop()) {
        shopKind = 0;
    } else if (Scene_GetCurrent() == 0xa) {
        shopKind = 1;
    } else if (Scene_GetCurrent() == 0xf) {
        shopKind = 2;
    } else {
        shopKind = 3;
    }
    static Fn tbl[4] = {&ShopStockPlacer::setupNookShop, &ShopStockPlacer::setupScene10Shop,
                        &ShopStockPlacer::setupScene15Shop, &ShopStockPlacer::setupNoShop};
    (this->*tbl[shopKind])();
    return TRUE;
}

BOOL ShopStockPlacer::onExecute() { return TRUE; }

BOOL ShopStockPlacer::onDraw() { return TRUE; }

BOOL ShopStockPlacer::onDelete() { return TRUE; }

BOOL ShopStockPlacer::placeItem(u16 *item, s32 code) {
    const u32 *tbl = ShopStock_GetLayout();
    BlockMap *g = gSceneBlockMap;
    s32 y;
    s32 x;
    s32 hx;
    s32 hy;
    u16 *t;
    const u32 *row;
    if (g) {
        s32 x0 = 0;
        for (y = 0; y < 16; y++) {
            x = x0;
            row = tbl + y * 16;
            if (x < 16) {
                goto testx;
            loopx:
                hx = x >> 4;
                hy = y >> 4;
                t = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
                if (t) {
                    BOOL r;
                    s32 f1 = 0, f2 = 0;
                    if (Item_IsFurniture(t)) {
                        u16 c = 0xfff1;
                        s32 a = Item_GetFurnitureIndex(t);
                        r = (a == Item_GetFurnitureIndex(&c)) ? 1 : f1;
                    } else {
                        r = (*t == 0xfff1) ? 1 : f2;
                    }
                    if (r) {
                        if (code == row[x]) {
                            if (BlockMap_SetItemAtUnit(g, item, x, y, 0)) return TRUE;
                        }
                    }
                }
                x++;
            testx:
                if (x < 16) goto loopx;
            }
        }
    }
    return FALSE;
}

void ShopStockPlacer::placeNookStock() {
    u32 i;
    s32 f1 = 0, f2 = 0, f3 = 0, f4 = 0;
    u16 v[3];
    for (i = 0; i < 0x25; i++) {
        BOOL a, b;
        v[0] = 0xfff1;
        u16 *r = NookShop_GetItem(data_021ed104, i, &v[0]);
        if (Item_IsFurniture(r)) {
            v[1] = 0xfff1;
            s32 x = Item_GetFurnitureIndex(r);
            a = (x == Item_GetFurnitureIndex(&v[1])) ? 1 : f1;
        } else {
            a = (*r == 0xfff1) ? 1 : f2;
        }
        if (!a) {
            if (Item_IsFurniture(&v[0])) {
                v[2] = 0xfff1;
                s32 x = Item_GetFurnitureIndex(&v[0]);
                b = (x == Item_GetFurnitureIndex(&v[2])) ? 1 : f3;
            } else {
                b = (v[0] == 0xfff1) ? 1 : f4;
            }
            if (!b) {
                placeItem(r, ShopStock_GetItemCode(&v[0]));
            }
        }
    }
}

BOOL ShopStockPlacer::setupNookShop() {
    if (Scene_GetCurrent() != 0x1f) placeNookStock();
    return TRUE;
}

extern "C" BOOL ShopStock_IsForSale(u16 *p) {
    s32 t = Scene_GetCurrent();
    if (SceneId_IsNookShop(t)) {
        s32 r = NookShop_FindItem(data_021ed104, p);
        BOOL k = FALSE;
        if (r != -1) k = TRUE;
        return k;
    }
    if (t == 10) {
        BOOL k = TRUE;
        BOOL r = FALSE;
        u32 v = *p;
        if (v >= 0x3e04 && v <= 0x3e23) r = TRUE;
        if (!r) {
            if (AbleShop_FindItem(data_021ed2d4, p) == -1) k = FALSE;
        }
        return k;
    }
    s32 r = ReddShop_FindItem(data_021ed2c0, p);
    BOOL k = FALSE;
    if (r != -1) k = TRUE;
    return k;
}

ItemId ShopStock_GetItemAt_dflt;
u8 ShopStock_GetItemAt_dflt_init;
ItemId ShopStock_GetItemAt_v2;
u8 ShopStock_GetItemAt_v2_init;
extern "C" u16 *ShopStock_GetItemAt(s32 x, s32 y) {
    if (!ShopStock_GetItemAt_dflt_init) {
        HOST_STATIC_INIT(ShopStock_GetItemAt_dflt, ItemId(0xfff1));
        ShopStock_GetItemAt_dflt_init = 1;
    }
    u16 cv[3];
    BlockMap *g = gSceneBlockMap;
    if (g) {
        s32 hx = x >> 4;
        s32 hy = y >> 4;
        u16 *r4 = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (r4) {
            if (!Unk_ov004_0223ed40_Chk(r4, &cv[1], 0xfff1)) {
                if (Item_IsFurnitureOrF031(r4)) {
                    FtrActor *o = FtrActorGrid_GetInstance()->getActor(x, y, 0);
                    if (!o) return &ShopStock_GetItemAt_dflt.id;
                    if (!ShopStock_GetItemAt_v2_init) {
                        HOST_STATIC_INIT(ShopStock_GetItemAt_v2, ItemId(0xfff1));
                        ShopStock_GetItemAt_v2_init = 1;
                    }
                    ShopStock_GetItemAt_v2.id = Item_MakeFurniture(FtrActor_GetFtrIndex(o), 0);
                    if (ShopStock_IsForSale(&ShopStock_GetItemAt_v2.id)) return &ShopStock_GetItemAt_v2.id;
                } else if (Item_IsNormalItem(r4)) {
                    if (!Unk_ov004_0223ed40_Chk(r4, &cv[2], 0x1547)) {
                        if (ShopStock_IsForSale(r4)) return r4;
                    }
                }
            }
        }
    }
    return &ShopStock_GetItemAt_dflt.id;
}

extern "C" s32 ShopStock_GetCode22Index(s32 x, s32 y) {
    const u32 *tbl = ShopStock_GetLayout();
    s32 n = 0;
    s32 j = n;
    s32 i0 = 0;
    goto testj;
loopj:
    {
        s32 i = i0;
        const u32 *row = tbl + j * 16;
        goto testi;
    loopi:
        if (row[i] == 0x22) {
            if (i == x && j == y) return n;
            n++;
        }
        i++;
    testi:
        if (i < 16) goto loopi;
        j++;
    }
testj:
    if (j < 16) goto loopj;
    return -1;
}

extern "C" BOOL ShopStock_FindTileOfStock(s32 *px, s32 *py, s32 code) {
    const u32 *tbl = ShopStock_GetLayout();
    u16 c = 0xfff1;
    NookShop_GetItem(data_021ed104, code, &c);
    s32 key = ShopStock_GetItemCode(&c);
    s32 n = 0;
    s32 i = n;
    goto test0;
loop0:
    {
        u16 c2 = 0xfff1;
        NookShop_GetItem(data_021ed104, i, &c2);
        if (code == i) goto done0;
        if (key == ShopStock_GetItemCode(&c2)) n++;
        i++;
    }
test0:
    if ((u32)i < 0x25) goto loop0;
done0:
    {
        s32 cnt = 0;
        s32 y = cnt;
        s32 x0 = 0;
        goto testy;
    loopy:
        {
            s32 x = x0;
            const u32 *row = tbl + y * 16;
            goto testx;
        loopx:
            if (key == row[x]) {
                if (cnt == n) {
                    *px = x;
                    *py = y;
                    return TRUE;
                }
                cnt++;
            }
            x++;
        testx:
            if (x < 16) goto loopx;
            y++;
        }
    testy:
        if (y < 16) goto loopy;
    }
    *py = -1;
    *px = *py;
    return FALSE;
}

void ShopStockPlacer::placeScene10Stock() {
    u32 i;
    s32 f1 = 0, f2 = 0, f3 = 0, f4 = 0;
    u16 v[3];
    for (i = 0; i < 6; i++) {
        BOOL a, b;
        v[0] = 0xfff1;
        u16 *r = AbleShop_GetItem(data_021ed2d4, i, &v[0]);
        if (Item_IsFurniture(r)) {
            v[1] = 0xfff1;
            s32 x = Item_GetFurnitureIndex(r);
            a = (x == Item_GetFurnitureIndex(&v[1])) ? 1 : f1;
        } else {
            a = (*r == 0xfff1) ? 1 : f2;
        }
        if (!a) {
            if (Item_IsFurniture(&v[0])) {
                v[2] = 0xfff1;
                s32 x = Item_GetFurnitureIndex(&v[0]);
                b = (x == Item_GetFurnitureIndex(&v[2])) ? 1 : f3;
            } else {
                b = (v[0] == 0xfff1) ? 1 : f4;
            }
            if (!b) {
                placeItem(r, ShopStock_GetItemCode(&v[0]));
            }
        }
    }
}

BOOL ShopStockPlacer::setupScene10Shop() {
    placeScene10Stock();
    BlockMap *g = gSceneBlockMap;
    u16 v;
    v = 0xfff1;
    v = 0x3e04;
    BlockMap_SetItemAtUnit(g, &v, 6, 10, 0);
    v = 0x3e08;
    BlockMap_SetItemAtUnit(g, &v, 7, 10, 0);
    v = 0x3e0c;
    BlockMap_SetItemAtUnit(g, &v, 8, 10, 0);
    v = 0x3e10;
    BlockMap_SetItemAtUnit(g, &v, 9, 10, 0);
    v = 0x3e14;
    BlockMap_SetItemAtUnit(g, &v, 6, 11, 0);
    v = 0x3e18;
    BlockMap_SetItemAtUnit(g, &v, 7, 11, 0);
    v = 0x3e1c;
    BlockMap_SetItemAtUnit(g, &v, 8, 11, 0);
    v = 0x3e20;
    BlockMap_SetItemAtUnit(g, &v, 9, 11, 0);
    return TRUE;
}

extern "C" u16 *ShopStock_GetItemAtTile(s32 x, s32 y) { return ShopStock_GetItemAt(x, y); }

void ShopStockPlacer::placeScene15Stock() {
    u32 i = 0;
    s32 z1 = 0, z2 = 0, z3 = 0, z4 = 0;
    u16 buf[3];
    for (; i < 3; i++) {
        u16 *r4;
        BOOL f;
        buf[0] = 0xfff1;
        r4 = ReddShop_GetItem(data_021ed2c0, i, buf);
        if (Item_IsFurniture(r4)) {
            s32 a, b;
            buf[1] = 0xfff1;
            a = Item_GetFurnitureIndex(r4);
            b = Item_GetFurnitureIndex(&buf[1]);
            f = (a == b) ? 1 : z1;
        } else {
            f = (*r4 == 0xfff1) ? 1 : z2;
        }
        if (!f) {
            if (Item_IsFurniture(buf)) {
                s32 a, b;
                buf[2] = 0xfff1;
                a = Item_GetFurnitureIndex(buf);
                b = Item_GetFurnitureIndex(&buf[2]);
                f = (a == b) ? 1 : z3;
            } else {
                f = (buf[0] == 0xfff1) ? 1 : z4;
            }
            if (!f) {
                placeItem(r4, ShopStock_GetItemCode(buf));
            }
        }
    }
}

BOOL ShopStockPlacer::setupScene15Shop() {
    placeScene15Stock();
    return TRUE;
}

u16 *ShopStockPlacer::callGetItemAt(s32 x, s32 y) {
    return ShopStock_GetItemAt(x, y);
}

BOOL ShopStockPlacer::setupNoShop() {
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0223e9bc) {
    HOST_OVERLAY_VAR(sShopStockPlacerProfile),
    HOST_OVERLAY_VAR(ShopStock_GetItemAt_dflt),
    HOST_OVERLAY_VAR(ShopStock_GetItemAt_dflt_init),
    HOST_OVERLAY_VAR(ShopStock_GetItemAt_v2),
    HOST_OVERLAY_VAR(ShopStock_GetItemAt_v2_init),
    HOST_OVERLAY_VARS_END
};

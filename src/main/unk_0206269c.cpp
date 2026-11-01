#include "types.h"
#include "host_labels.h"
#include "item/ItemClassOrders.h"
#include "item/ItemId.h"
#include "item/ItemPickSpec.h"
#include "item/RandomSource.h"
#include "item/DateSeededRandomSource.h"
#include "player/PlayerData.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0204a780.h"

extern "C" {
u32 Random_NextBelow(void *st, u32 n);
void Random_SetSeed(u32 *seed, u32 v);
void Clock_GetDateTime(void *p);
u8 FengShui_GetEastTotal(void);
u8 FengShui_GetSouthTotal(void);
s32 FX_Div(s32 a, s32 b);
s32 ItemInfo_GetClass(u16 *p);
s32 ItemInfo_GetSeason(u16 *p);
}



struct ItemPickList {
    u16 (*unk_00)(u32);
    s32 (*unk_04)(u16 *);
    s32 (*unk_08)(u16 *);
    u32 count;
    s32 (*unk_10)(u16 *);
};

#define data_021ed30c HOST_LABEL(ItemClassOrders *, data_021ed30c)
extern const u8 sItemClassWeightOrders[];
extern const u32 sItemClassRanks[];
extern const ItemPickList sItemPickLists[];
extern u8 gSaveData[];

extern "C" {
}

extern const u32 sItemClassRanks[3] = {1, 2, 3};
extern const u8 sItemClassWeightOrders[18] = {
    0x3c, 0x1e, 0x0a, 0x3c, 0x0a, 0x1e, 0x1e, 0x3c, 0x0a,
    0x0a, 0x3c, 0x1e, 0x1e, 0x0a, 0x3c, 0x0a, 0x1e, 0x3c,
};
extern const ItemPickList sItemPickLists[9] = {
    {(u16(*)(u32))ItemList_MakeFurniture, (s32(*)(u16 *))ItemList_GetNoSeason, Ftr_GetClass, 0x6e9, ItemList_IsFurniture},
    {ItemList_MakePaper, ItemInfo_GetSeason, ItemInfo_GetClass, 0x40, ItemList_IsPaper},
    {Item_MakeShirt, ItemInfo_GetSeason, ItemInfo_GetClass, 0x100, ItemList_IsShirt},
    {Item_MakeCarpet, ItemInfo_GetSeason, ItemInfo_GetClass, 0x44, ItemList_IsCarpet},
    {Item_MakeWallpaper, ItemInfo_GetSeason, ItemInfo_GetClass, 0x44, ItemList_IsWallpaper},
    {Item_MakeAccessory, ItemInfo_GetSeason, ItemInfo_GetClass, 0x40, ItemList_IsAccessory},
    {Item_MakeHat, ItemInfo_GetSeason, ItemInfo_GetClass, 0x40, ItemList_IsHat},
    {Item_MakeUmbrella, ItemInfo_GetSeason, ItemInfo_GetClass, 0x20, ItemList_IsUmbrella},
    {Item_MakeFullHeadwear, ItemInfo_GetSeason, ItemInfo_GetClass, 0x20, ItemList_IsFullHeadwear},
};

static inline BOOL Unk_0206277c_Bad1(u16 *p, u16 *e) {
    BOOL r;
    if (Item_IsFurniture(p)) {
        *e = 0xfff1;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(e)) r = TRUE;
        else r = FALSE;
    } else {
        if (*p == 0xfff1) r = TRUE;
        else r = FALSE;
    }
    return r;
}

static inline BOOL Unk_0206277c_Bad2(u16 *p, u16 *e) {
    BOOL r;
    if (Item_IsFurniture(p)) {
        *e = 0xfff1;
        s32 x = Item_GetFurnitureIndex(p);
        if (x == Item_GetFurnitureIndex(e)) r = TRUE;
        else r = FALSE;
    } else {
        if (*p == 0xfff1) r = TRUE;
        else r = FALSE;
    }
    return r;
}

ItemClassOrder::ItemClassOrder() {}

ItemClassOrder::~ItemClassOrder() {}

void ItemClassOrder::randomize() { orderIndex = Random_GlobalBelow(6); }

u8 *ItemClassOrder::getWeights() {
    if (orderIndex >= 6) orderIndex = orderIndex % 6;
    return (u8 *)sItemClassWeightOrders + orderIndex * 3;
}

u32 ItemClassOrder::pickClass(s32 mode, RandomSource *rng) {
    u32 a = (u8)(60 - (u8)FX_Div(FengShui_GetEastTotal() + FengShui_GetSouthTotal(), 0xa000));
    u32 b = (u8)(70 - a);
    if (mode == 0) {
        RandomSource local;
        if (rng == NULL) rng = &local;
        u32 r = rng->random(100);
        if (r < a) {
            return pickClass(1, rng);
        } else if (r < a + b) {
            return pickClass(3, rng);
        } else {
            return pickClass(2, rng);
        }
    } else if (mode == 1) {
        if (a >= 30 && a >= b) return getClassOfWeight(60);
        if (a <= 30 && b <= 30) return getClassOfWeight(30);
        return getClassOfWeight(10);
    } else if (mode == 2) {
        if ((a <= 30 && a >= b) || (a >= 30 && a <= b)) return getClassOfWeight(60);
        if ((a >= 30 && b <= 30) || (a <= 30 && b >= 30)) return getClassOfWeight(30);
        return getClassOfWeight(10);
    } else if (mode == 3) {
        if (a <= 30 && a <= b) return getClassOfWeight(60);
        if (a >= 30 && b >= 30) return getClassOfWeight(30);
        return getClassOfWeight(10);
    }
    return mode;
}

extern "C" u8 ItemPick_GetClassWeight(u32 idx) {
    u32 m = (u8)FX_Div(FengShui_GetEastTotal() + FengShui_GetSouthTotal(), 0xa000);
    u8 t[3] = {0, 30, 0};
    t[0] = 0x3c - m;
    t[2] = m + 10;
    if (idx < 3) return t[idx];
    return t[0];
}

u32 ItemClassOrder::getIndex() { return orderIndex; }

u32 ItemClassOrder::getClassOfWeight(u32 x) {
    u8 *p = getWeights();
    for (u32 i = 0; i < 3; i++) {
        if (x == p[i]) return i + 1;
    }
    return 1;
}

ItemClassOrders::ItemClassOrders() {}

ItemClassOrders::~ItemClassOrders() {}

void ItemClassOrders::randomizeAll() {
    for (u32 i = 0; i < 9; i++) {
        orders[i].randomize();
    }
}

ItemClassOrder *ItemClassOrders::get(s32 i) {
    ItemClassOrder *p = orders;
    if (i < 9) p += i;
    return p;
}

RandomSource::RandomSource() {}

RandomSource::~RandomSource() {}

u32 RandomSource::random(u32 n) { return Random_NextBelow(&gRandom.seed, n); }

u8 RandomSource::getYear() {
    u32 t[2];
    t[0] = 0;
    t[1] = 0;
    Clock_GetDateTime(t);
    return ((u8 *)t)[5];
}

u8 RandomSource::getMonth() {
    u32 t[2];
    t[0] = 0;
    t[1] = 0;
    Clock_GetDateTime(t);
    return ((u8 *)t)[4];
}

u8 RandomSource::getDay() {
    u32 t[2];
    t[0] = 0;
    t[1] = 0;
    Clock_GetDateTime(t);
    return ((u8 *)t)[3];
}

DateSeededRandomSource::DateSeededRandomSource() {
    Random_SetSeed(&rngState, 1);
    seedFromToday();
}

DateSeededRandomSource::~DateSeededRandomSource() {}

void DateSeededRandomSource::seedFromToday() {
    u32 t[2];
    t[0] = 0;
    t[1] = 0;
    Clock_GetDateTime(t);
    seed(((u8 *)t)[5], ((u8 *)t)[4], ((u8 *)t)[3]);
}

extern "C" u32 ItemPick_CalcDateSeed(u32 a, u32 b, u32 c) {
    u32 v0, v1, v6, v4, v3, v2;
    v0 = (u8)data_021ed30c.get(0)->getIndex();
    v4 = data_021ed30c.get(4)->getIndex() << 24;
    v1 = (u8)data_021ed30c.get(1)->getIndex();
    v6 = (u8)data_021ed30c.get(6)->getIndex();
    v3 = (u8)data_021ed30c.get(3)->getIndex();
    v2 = (u8)data_021ed30c.get(2)->getIndex();
    u32 x = a | ((c << 11) | (b << 7));
    return (c << 30) ^ ((v2 << 25) ^ ((v3 << 20) ^ ((v6 << 15) ^ ((v1 << 10) ^ ((v4 >> 19) ^ (v0 ^ (x | (x << 16))))))));
}

void DateSeededRandomSource::seed(u8 a, u8 b, u8 c) {
    year = a;
    month = b;
    day = c;
    Random_SetSeed(&rngState, ItemPick_CalcDateSeed(a, b, c));
}

u32 DateSeededRandomSource::random(u32 n) { return Random_NextBelow(&rngState, n); }

void ItemPickSpec::set(s32 a, s32 b) {
    listIndex = a;
    itemClass = b;
}

ItemPickSpec::~ItemPickSpec() {}

s32 ItemPickSpec::getList() { return listIndex; }

s32 ItemPickSpec::getClass() { return itemClass; }

extern "C" s32 ItemList_MakeFurniture(s32 a) { return Item_MakeFurniture(a, 0); }

extern "C" u16 ItemList_MakePaper(u32 a) { return Item_MakePaper(a, 4); }

extern "C" s32 ItemList_GetNoSeason(void) { return -1; }

extern "C" s32 Item_FindInArray(u16 *c, u16 *arr, u32 n) {
    u32 i;
    s32 f1 = 0, f2 = 0;
    for (i = 0; i < n; arr++, i++) {
        s32 t;
        if (Item_IsFurniture(arr)) {
            s32 x = Item_GetFurnitureIndex(arr);
            t = (x == Item_GetFurnitureIndex(c)) ? 1 : f1;
        } else {
            t = (*arr == *c) ? 1 : f2;
        }
        if (t) return i;
    }
    return -1;
}

extern "C" BOOL ItemPick_SeasonMatches(s32 a, s32 b) {
    BOOL r = FALSE;
    if (a == -1 || a == 4 || a == b) r = TRUE;
    return r;
}

extern "C" s32 ItemPick_GetSeason(s32 a, u32 b) {
    switch (a) {
    case 1:
        return 3;
    case 2:
        if (b > 0x18) return 0;
        return 3;
    case 3:
    case 4:
        return 0;
    case 5:
        if (b > 0x1a) return 1;
        return 0;
    case 6:
    case 7:
        return 1;
    case 8:
        if (b > 0x1a) return 2;
        return 1;
    case 9:
    case 10:
        return 2;
    case 11:
        if (b > 0x1a) return 3;
        return 2;
    }
    return 3;
}

extern "C" BOOL ItemPick_IsCatalogued(void *p, u16 *q) {
    if (p != NULL) {
        return Catalog_HasItem(((PlayerData *)(p))->getCatalog(), q);
    }
    return FALSE;
}

extern "C" u32 ItemPick_FromLists(u16 *out, u32 n, ItemPickSpec *tbl, u32 x3, u8 *a4, RandomSource *rng, u32 a6, u32 a7, s32 *outp) {
    u16 tmp[2];
    RandomSource *r;
    u32 result;
    u8 *const g = gSaveData;
    result = 1;
    RandomSource local;
    r = rng;
    if (r == NULL) r = &local;
    s32 t1 = r->getMonth();
    s32 t2 = r->getDay();
    s32 k = ItemPick_GetSeason(t1, t2);
    u32 i;
    for (i = 0; i < n; i++) out[i] = 0xfff1;
    if (outp != NULL) *outp = 1;
    u32 cnt = 0;
    while (cnt < n) {
        u32 idx = r->random(x3);
        ItemPickSpec *e = tbl + idx;
        s32 type = e->getList();
        ItemClassOrder *el = ((ItemClassOrders *)(g + 0x15fbc))->get(type);
        s32 kind;
        if (a7 == 1) {
            kind = el->pickClass(e->getClass(), r);
        } else {
            kind = e->getClass();
        }
        u32 flag1 = a6;
        if (kind != 0 && kind != 1 && kind != 2 && kind != 3 && kind != 0x1d && kind != 5) flag1 = 0;
        if (outp != NULL) *outp = kind;
        const ItemPickList *row = sItemPickLists + type;
        u32 m = 0;
        u32 j;
        for (j = 0; j < row->count; j++) {
            tmp[0] = row->unk_00(j);
            if (kind == row->unk_08(&tmp[0])) {
                if (ItemPick_SeasonMatches(row->unk_04(&tmp[0]), k)) {
                    if (!ItemPick_IsCatalogued(a4, &tmp[0])) {
                        if (flag1 == 0 || !Item_TestInfoFlag4(&tmp[0])) {
                            if (Item_FindInArray(&tmp[0], out, cnt) == -1) m++;
                        }
                    }
                }
            }
        }
        u32 flagB = 0;
        if (m == 0) {
            if (a4 != NULL) {
                return 0;
            }
            m = row->count;
            flagB = 1;
        }
        u32 pick = r->random(m);
        u32 found = 0;
        m = 0;
        for (j = 0; j < row->count; j++) {
            tmp[1] = row->unk_00(j);
            if (kind == row->unk_08(&tmp[1])) {
                if (ItemPick_SeasonMatches(row->unk_04(&tmp[1]), k)) {
                    if (!ItemPick_IsCatalogued(a4, &tmp[1])) {
                        if (flag1 == 0 || !Item_TestInfoFlag4(&tmp[1])) {
                            if (flagB) {
                                if (pick == m) {
                                    out[cnt++] = tmp[1];
                                    found = 1;
                                    break;
                                } else m++;
                            } else if (Item_FindInArray(&tmp[1], out, cnt) == -1) {
                                if (pick == m) {
                                    out[cnt++] = tmp[1];
                                    found = 1;
                                    break;
                                } else m++;
                            }
                        }
                    }
                }
            }
        }
        if (found == 0) {
            out[cnt++] = row->unk_00(0);
            result = 0;
        }
    }
    return result;
}

extern "C" void ItemPick_One(u16 *out, ItemPickSpec *o, u8 *a, RandomSource *b, u8 c, u32 d, s32 *e) {
    *out = 0xfff1;
    ItemPickSpec t = *o;
    ItemPick_OneEx(out, 1, &t, a, b, c, d, e);
}

extern "C" void ItemPick_OneEx(u16 *out, s32 one, ItemPickSpec *o, u8 *a, RandomSource *b, u8 c, u32 d, s32 *e) {
    ItemPick_FromLists(out, one, o, 1, a, b, c, d, e);
}

extern "C" void ItemPick_OneSimple(u16 *out, ItemPickSpec *o) {
    ItemPickSpec t = *o;
    ItemPick_One(out, &t, 0, 0, 1, 0, 0);
}

extern "C" BOOL ItemPick_FillFromRange(u16 *arr, u32 n, s32 base, u32 cnt, void *a4, s32 a5, s32 a6, RandomSource *a7, s32 a8) {
    BOOL result = TRUE;
    BOOL t1 = TRUE, f1 = FALSE, t2 = TRUE, f2 = FALSE, f3 = FALSE;
    u16 tmp[2];
    for (u32 i = 0; i < n; i++) {
        ItemPick_FromRange(&tmp[0], base, cnt, arr, i, a4, a5, a6, a7, a8);
        u16 *p = arr + i;
        *p = tmp[0];
        BOOL c;
        if (Item_IsFurniture(p)) {
            tmp[1] = 0xfff1;
            c = Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&tmp[1]) ? t1 : f1;
        } else {
            c = *p == 0xfff1 ? t2 : f2;
        }
        if (c) result = f3;
    }
    return result;
}

extern "C" void ItemPick_FromRange(u16 *out, s32 base, u32 cnt, u16 *list, u32 listLen, void *a5, s32 a6, s32 a7, RandomSource *rng, s32 a9) {
    u16 v[4];
    s32 step;
    RandomSource dflt;
    RandomSource *obj;
    if (rng != 0) obj = rng;
    else obj = &dflt;
    v[0] = base;
    step = Item_IsFurniture(&v[0]) ? 2 : 0;
    u32 count = 0;
    {
        BOOL r = FALSE;
        if (v[0] >= 0x450c && v[0] <= 0x45db) r = TRUE;
        if (r || (v[0] >= 0x45dc && v[0] <= 0x47d7) || (v[0] >= 0x1323 && v[0] <= 0x1368)) a9 = 0;
    }
    u32 i = 0;
    BOOL z40, z3c;
    BOOL z2c = FALSE, z34 = FALSE, z38 = FALSE;
    z3c = FALSE;
    z40 = FALSE;
    BOOL z44 = FALSE;
    for (; i < cnt; i++) {
        v[2] = base + (i << step);
        BOOL found = z2c;
        u32 j = z2c;
        for (; j < listLen; j++) {
            BOOL m;
            if (Item_IsFurniture(&v[2])) {
                m = Item_GetFurnitureIndex(&v[2]) == Item_GetFurnitureIndex(list + j) ? TRUE : z34;
            } else {
                m = v[2] == list[j] ? TRUE : z38;
            }
            if (m) {
                found = TRUE;
                break;
            }
        }
        if (found) continue;
        BOOL r = z3c;
        if (v[2] >= 0x11a8 && v[2] <= 0x12a7) r = TRUE;
        BOOL ok;
        if (r) {
            if (a7 == 10) ok = TRUE;
            else if (a7 == Item_GetShirtUnkGroup(&v[2])) ok = TRUE; else ok = z40;
        } else {
            ok = TRUE;
        }
        if (!ok) continue;
        s32 t = z44;
        if (Item_IsNormalItem(&v[2])) t = ItemInfo_GetClass(&v[2]);
        else if (Item_IsFurniture(&v[2])) t = Ftr_GetClass(&v[2]);
        if (t == 0x19 || t == 0x18) continue;
        if (a9 && Item_TestInfoFlag4(&v[2])) continue;
        if (a5) {
            if (a6) {
                if (Catalog_HasItem(((PlayerData *)(a5))->getCatalog(), &v[2])) count++;
            } else {
                if (!Catalog_HasItem(((PlayerData *)(a5))->getCatalog(), &v[2])) count++;
            }
        } else {
            count++;
        }
    }
    BOOL flag = FALSE;
    if (count == 0) {
        if (a5) {
            *out = 0xfff1;
            return;
        }
        flag = TRUE;
        count = cnt;
    }
    u32 pick = obj->random(count);
    u32 idx = 0;
    u32 i2 = 0;
    BOOL z5c, z58;
    BOOL z48 = FALSE, z50 = FALSE, z54 = FALSE;
    z58 = FALSE;
    z5c = FALSE;
    BOOL z60 = FALSE;
    for (; i2 < cnt; i2++) {
        v[3] = base + (i2 << step);
        BOOL found = z48;
        if (!flag) {
            u32 j = z48;
            for (; j < listLen; j++) {
                BOOL m;
                if (Item_IsFurniture(&v[3])) {
                    m = Item_GetFurnitureIndex(&v[3]) == Item_GetFurnitureIndex(list + j) ? TRUE : z50;
                } else {
                    m = v[3] == list[j] ? TRUE : z54;
                }
                if (m) {
                    found = TRUE;
                    break;
                }
            }
        }
        if (found) continue;
        BOOL r = z58;
        if (v[3] >= 0x11a8 && v[3] <= 0x12a7) r = TRUE;
        BOOL ok;
        if (r) {
            if (a7 == 10) ok = TRUE;
            else if (a7 == Item_GetShirtUnkGroup(&v[3])) ok = TRUE; else ok = z5c;
        } else {
            ok = TRUE;
        }
        if (!ok) continue;
        s32 t = z60;
        if (Item_IsNormalItem(&v[3])) t = ItemInfo_GetClass(&v[3]);
        else if (Item_IsFurniture(&v[3])) t = Ftr_GetClass(&v[3]);
        if (t == 0x19 || t == 0x18) continue;
        if (a9 && Item_TestInfoFlag4(&v[3])) continue;
        if (a5) {
            if (a6) {
                if (Catalog_HasItem(((PlayerData *)(a5))->getCatalog(), &v[3])) {
                    if (pick == idx) {
                        *out = v[3];
                        return;
                    }
                    idx++;
                }
            } else {
                if (!Catalog_HasItem(((PlayerData *)(a5))->getCatalog(), &v[3])) {
                    if (pick == idx) {
                        *out = v[3];
                        return;
                    }
                    idx++;
                }
            }
        } else {
            if (pick == idx) {
                *out = v[3];
                return;
            }
            idx++;
        }
    }
    *out = 0xfff1;
}

extern "C" void ItemPick_FtrWallCarpetByClass(u16 *out, u8 *a, RandomSource *rng) {
    u16 t0, t1, t2, t3, t4, t5, t6, t7, t8;
    u16 e1, e2;
    RandomSource dflt;
    RandomSource *obj;
    if (rng != 0) obj = rng;
    else obj = &dflt;
    u8 mask[3] = {1, 1, 1};
    ItemId h[9];
    {
        ItemPickSpec o;
        o.set(0, 1);
        ItemPick_One(&t0, &o, a, rng, 1, 1, 0);
        h[0].id = t0;
    }
    {
        ItemPickSpec o;
        o.set(4, 1);
        ItemPick_One(&t1, &o, a, rng, 1, 1, 0);
        h[1].id = t1;
    }
    {
        ItemPickSpec o;
        o.set(3, 1);
        ItemPick_One(&t2, &o, a, rng, 1, 1, 0);
        h[2].id = t2;
    }
    {
        ItemPickSpec o;
        o.set(0, 2);
        ItemPick_One(&t3, &o, a, rng, 1, 1, 0);
        h[3].id = t3;
    }
    {
        ItemPickSpec o;
        o.set(4, 2);
        ItemPick_One(&t4, &o, a, rng, 1, 1, 0);
        h[4].id = t4;
    }
    {
        ItemPickSpec o;
        o.set(3, 2);
        ItemPick_One(&t5, &o, a, rng, 1, 1, 0);
        h[5].id = t5;
    }
    {
        ItemPickSpec o;
        o.set(0, 3);
        ItemPick_One(&t6, &o, a, rng, 1, 1, 0);
        h[6].id = t6;
    }
    {
        ItemPickSpec o;
        o.set(4, 3);
        ItemPick_One(&t7, &o, a, rng, 1, 1, 0);
        h[7].id = t7;
    }
    {
        ItemPickSpec o;
        o.set(3, 3);
        ItemPick_One(&t8, &o, a, rng, 1, 1, 0);
        h[8].id = t8;
    }
    u32 idx;
    u32 count;
    u32 pick;
    u32 acc;
    u32 pick2;
    u32 j;
    u32 cnt;
    u32 k;
    for (;;) {
        count = 0;
        for (k = 0; k < 3; k++) {
            if (mask[k]) count += ItemPick_GetClassWeight(k);
        }
        if (count == 0) break;
        pick = obj->random(count);
        acc = 0;
        for (k = 0; k < 3; k++) {
            if (mask[k]) {
                acc += ItemPick_GetClassWeight(k);
                if (pick < acc) {
                    cnt = 0;
                    j = 0;
                    for (; j < 3; j++) {
                        if (!Unk_0206277c_Bad1(&h[k * 3 + j].id, &e1)) cnt++;
                    }
                    if (cnt == 0) {
                        mask[k] = 0;
                        goto next;
                    }
                    pick2 = obj->random(cnt);
                    idx = 0;
                    for (j = 0; j < 3; j++) {
                        u16 *p = &h[k * 3 + j].id;
                        if (!Unk_0206277c_Bad2(p, &e2)) {
                            if (idx == pick2) {
                                *out = *p;
                                return;
                            }
                            idx++;
                        }
                    }
                }
            }
        }
    next:;
    }
    *out = 0xfff1;
}

extern "C" s32 ItemList_Find(u16 *p) {
    u32 i;
    for (i = 0; i < 9; i++) {
        if (sItemPickLists[i].unk_10(p)) return i;
    }
    return 9;
}

extern "C" s32 ItemList_GetTownClassRank(u16 *p, s32 mode) {
    s32 idx = ItemList_Find(p);
    if (idx != 9) {
        u8 *g = gSaveData;
        const ItemPickList *t = sItemPickLists + idx;
        s32 v = (t->unk_08)(p);
        if (mode != 0) return v;
        {
            ItemClassOrder *base = ((ItemClassOrders *)(g + 0x15fbc))->get(idx);
            for (u32 i = 0; i < 3; i++) {
                if (v == base->pickClass(((volatile u32 *)sItemClassRanks)[i], NULL)) return ((volatile u32 *)sItemClassRanks)[i];
            }
        }
        return v;
    }
    return 0x18;
}

extern "C" BOOL Item_IsClass4Furniture(u16 *p) {
    if (Item_IsFurniture(p)) {
        if (ItemList_GetTownClassRank(p, 0) == 4) return TRUE;
    }
    return FALSE;
}

u8 DateSeededRandomSource::getDay() { return day; }

u8 DateSeededRandomSource::getMonth() { return month; }

u8 DateSeededRandomSource::getYear() { return year; }


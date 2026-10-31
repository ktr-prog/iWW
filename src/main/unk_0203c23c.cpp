#include "types.h"
#include "Unk_020d8c7c.h"
#include "gfx/Unk_0203bd10_Dtcm.h"
class VillagerActor;
#include "gfx/CameraPose.h"
#include "gfx/FxMtx43.h"
#include "item/ItemId.h"
#include "sys/CameraBase.h"
#include "gfx/Camera.h"
#include "player/PlayerData.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02097444.h"


extern "C" {
BOOL Item_IsNormalItem(u16 *p);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Item_GetPaperIndex(u16 *p);
s32 Item_MakeFurniture(s32 a, s32 b);
BOOL Item_TestInfoFlag3(u16 *p);
}


static inline BOOL Unk_0203c23c_InRange(u16 c, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (c >= lo && c <= hi) r = TRUE;
    return r;
}

static inline BOOL Unk_0203c23c_InRangeP(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

static inline s32 Unk_0203c23c_Idx(u16 c, u32 lo, u32 hi) {
    if (Unk_0203c23c_InRange(c, lo, hi)) return c - lo;
    return -1;
}

static inline s32 Unk_0203c23c_None() {
    return Unk_0203c23c_Idx(0, 1, 0);
}

extern "C" u8 *Catalog_GetBit(u8 *base, u8 *out, u16 *p) {
    u16 c;
    s32 n;
    Item_ToPlacedForm(&c, p, 1);
    if (Item_IsFurniture(&c)) {
        n = Item_GetFurnitureIndex(&c);
        *out = 1 << (n & 7);
        return base + (n >> 3);
    }
    if (Unk_0203c23c_InRangeP(&c, 0x1100, 0x1143)) {
        n = Unk_0203c23c_Idx(c, 0x1100, 0x1143);
        *out = 1 << (n & 7);
        return base + 0x100 + (n >> 3);
    }
    if (c >= 0x1144 && c <= 0x1187) {
        n = Unk_0203c23c_Idx(c, 0x1144, 0x1187);
        *out = 1 << (n & 7);
        return base + 0x109 + (n >> 3);
    }
    if (c >= 0x1323 && c <= 0x1368) {
        n = Unk_0203c23c_Idx(c, 0x1323, 0x1368);
        *out = 1 << (n & 7);
        return base + 0x112 + (n >> 3);
    }
    if (c >= 0x1000 && c <= 0x10ff) {
        n = Item_GetPaperIndex(&c);
        *out = 1 << (n & 7);
        return base + 0x11b + (n >> 3);
    }
    *out = 0;
    return 0;
}

extern "C" BOOL Catalog_HasItem(u8 *base, u16 *p) {
    u8 mask;
    u8 *b = Catalog_GetBit(base, &mask, p);
    if (b) {
        if (*b & mask) return TRUE;
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL Catalog_SetItem(u8 *base, u16 *p, s32 skip, s32 set) {
    u8 mask;
    u8 *b;
    if (skip == 0) {
        if (Unk_0203c23c_InRangeP(p, 0x12e8, 0x131f) || (*p >= 0x12b0 && *p <= 0x12e7) ||
            (*p >= 0x4384 && *p <= 0x4463) || (*p >= 0x42a4 && *p <= 0x4383))
            return FALSE;
    }
    b = Catalog_GetBit(base, &mask, p);
    if (b) {
        if (set) {
            *b |= mask;
        } else {
            *b &= ~mask;
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Catalog_AddItem(void *a, u16 *p, s32 c) {
    return Catalog_SetItem((u8 *)a, p, c, 1);
}

extern "C" s32 Catalog_CountRange(u16 base, u32 n) {
    PlayerData *s = PlayerData_GetCurrent();
    s32 count = 0;
    u16 v[6];
    v[0] = base;
    if (!s) return count;
    if (Item_IsNormalItem(&v[0])) {
        u32 i;
        for (i = 0; i < n; i++) {
            v[1] = base + i;
            Item_ToPlacedForm(&v[4], &v[1], 1);
            v[1] = v[4];
            if (Item_TestInfoFlag3(&v[1])) {
                if (Catalog_HasItem(s->getCatalog(), &v[1])) count++;
            }
        }
        return count;
    }
    if (Item_IsFurniture(&v[0])) {
        u32 i;
        s32 z;
        v[2] = base;
        s32 r = Item_GetFurnitureIndex(&v[2]);
        z = 0;
        for (i = 0; i < n; i++) {
            v[3] = Item_MakeFurniture(r + i, z);
            if (Item_TestInfoFlag3(&v[3])) {
                if (Catalog_HasItem(s->getCatalog(), &v[3])) count++;
            }
        }
    }
    return count;
}

extern "C" BOOL Catalog_HasAllFish() {
    if (Catalog_CountFish() == Catalog_GetFishTotal()) return TRUE;
    return FALSE;
}

extern "C" BOOL Catalog_HasAllInsects() {
    if (Catalog_CountInsects() == Catalog_GetInsectTotal()) return TRUE;
    return FALSE;
}

extern "C" s32 Catalog_GetFishTotal() {
    return 0x38;
}

extern "C" s32 Catalog_GetInsectTotal() {
    return 0x38;
}

extern "C" s32 Catalog_CountFish() {
    return Catalog_CountRange(0x12e8, 0x38);
}

extern "C" s32 Catalog_CountInsects() {
    return Catalog_CountRange(0x12b0, 0x38);
}

extern "C" BOOL Catalog_AddCreature(u16 *p) {
    PlayerData *s = PlayerData_GetCurrent();
    if (s) return Catalog_AddItem(s->getCatalog(), p, 1);
    return FALSE;
}

extern "C" void *CarpetTex_Init(void *p) { return p; }

extern "C" BOOL CarpetTex_Load(void *a, u16 *p) {
    u16 c = *p;
    BOOL ok = Unk_0203c23c_InRange(c, 0x1144, 0x1187);
    s32 idx;
    if (ok) idx = c - 0x1144;
    else idx = -1;
    if (idx != -1) {
        if (File_LoadToBufferF(a, -1, "/carpet/floor_%d.nsbtx", idx)) return TRUE;
        return FALSE;
    }
    static ItemId s(0x1144);
    return CarpetTex_Load(a, &s.id);
}

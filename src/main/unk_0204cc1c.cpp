#include "uptr.h"
#include "host_labels.h"
#include "town/TownBlockCell.h"
#include "types.h"
#include "sys/StackPad.h"
#include "gfx/VecFx32.h"

#include "Unk_020d8c7c.h"
#include "town/SceneMapInfo.h"
#include "sys/ClockDate.h"
#include "item/ItemId.h"
#include "town/MapBlockEntry.h"
#include "town/MapBlock.h"
#include "town/BlockMap.h"
#include "town/TownMap.h"
#include "town/TownBlockMap.h"
#include "town/TownState.h"
#include "town/TownUnitShapeQuery.h"
#include "game/StrBSizeData.h"
#include "gfx/BgModelCache.h"
#include "net/CommManager.h"
#include "npc/VillagerDataItemView.h"
#include "room/HouseData.h"
#include "save/SnowmanRecords.h"
#include "save/VillagerData.h"
#include "game/Unk_02037674_V3.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0211a6c0.h"
#include "proto/main/unk_02036c58.h"
#include "proto/main/unk_02039c08.h"
#include "town/RoomBlockMap.h"
#include "proto/main/unk_0204cc1c.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_0204f134.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02060034.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206d49c.h"
#include "proto/main/unk_0209b598.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_022187fc.h"


struct FgDataIndex {
    u16 *data;
    s32 count;
};

struct FgLayoutEntry {
    u16 v;
    u8 x;
    u8 y;
};

struct Unk_020ca2f4_Ent {
    const char *indexPath;
    const char *dataPath;
};


struct TownBlockMapBuildLocals { volatile s32 xy[2]; VecFx32 v, w; };

struct BlockMapBuildLocals {
    volatile s32 x, y;
    VecFx32 v;
};

extern "C" {
extern const Unk_020ca2f4_Ent sFgDataFiles[4];
extern s32 data_020c8cbc;
extern s32 data_020c8cb8;
}
#define gSaveHouse HOST_LABEL(HouseData *, gSaveHouse)
#define gSaveTownMap HOST_LABEL(TownMap *, gSaveTownMap)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
#define data_021ed2e6 HOST_LABEL(SnowmanRecords *, data_021ed2e6)
extern CommManager *gCommManager;

extern "C" {
BOOL Item_IsTreeStage0(u16 *p);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
BOOL Item_IsNormalItem(u16 *p);
BOOL Item_IsSnowman(u16 *p);
s32 Item_GetSnowmanIndex(u16 *p);
s32 Item_GetStumpSize(u16 *p);
s32 SceneId_IsHouseRoom(s32 x);
s32 SceneId_GetHouseRoom(u32 x);
u8 *SaveVillagers_Get(u8 *base, s32 idx);
void Villager_ResolveRoomLayout(VillagerData *a, u16 *b);
MapBlock *MapBlock_NewArray(s32 n, void *heap, s32 x);
void MapBlock_Init(MapBlock *self, s32 a, VecFx32 *v, u16 *layer0, u16 *layer1, u16 *buriedMask, BgAcreModel *k2,
                   void *bcl, Unk_02037638_S8 *k45, u32 mapSlot);
BOOL CollisionMap_Bind(u32 a, u32 b, UnitShapeQueryX *o, s32 idx);
void CollisionMap_Release(s32 idx);
void CollisionMap_Select(s32 v);
s32 Ground_ClearPlantFlag(s32 a, s32 b);
s32 Ground_GetWalkLinks(s32 a, s32 b);
s32 Ground_GetPlantFlag(s32 a, s32 b);
s32 Ground_GetDigKind(s32 a, s32 b);
s32 Ground_IsShore(s32 a, s32 b);
s32 Ground_IsGrassSurface(s32 a, s32 b);
s32 Ground_IsWalkable(s32 a, s32 b);
s32 Ground_CanPlaceItem(s32 a, s32 b);
s32 Ground_GetDefaultY(void);
u32 GroundSeason_CalcPhase(void);
void BuriedMask_Reset(void *p);
BOOL MapBlock_ClearBuried(MapBlock *o, u32 a, u32 b);
BOOL MapBlock_SetBuried(MapBlock *o, u32 a, u32 b);
BOOL MapBlock_HasAnyAttr(MapBlock *o, u32 mask);
BOOL MapBlock_HasAllAttr(MapBlock *o, u32 mask);
u32 MapBlock_GetAttr(MapBlock *o);
BOOL MapBlock_FindItemInRange(void *cell, s32 *a, s32 *b, u16 *lo, u16 *hi, u8 d);
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
BOOL MapBlock_SetItem(void *cell, u16 *t, u32 x, u32 y, u8 z);
fx32 FX_Div(fx32 numer, fx32 denom);
}

extern "C" {
s32 FgData_GetLayoutSize(FgDataIndex *t, s32 i, s32 j);
s32 FgData_GetLayoutOffset(FgDataIndex *t, s32 i, s32 j);
BOOL FgData_IsValidTable(FgDataIndex *t, s32 i);
void FgData_FreeIndices(FgDataIndex *t, void *heap);
BOOL FgData_LoadIndices(FgDataIndex *t, void *heap);
void FgData_Unload(void *heap);
void FgData_ClearIndices(FgDataIndex *t);
BOOL FgData_ReadLayout(FgDataIndex *t, void *dst, s32 i, s32 j, s32 n);
BOOL FgData_ApplyLayout(FgDataIndex *t, u16 *dst, s32 i, s32 j, void *heap);
BOOL FgData_ApplyLayoutGlobal(u16 *dst, s32 i, s32 j, void *heap);
void *FgData_ReadLayoutEntries(FgDataIndex *t, s32 *b, s32 c, s32 d, void *heap);
void *FgData_ReadVillagerLayout(FgDataIndex *a, s32 *b, s32 c, void *d);
u16 *ItemGrid_Alloc(void *heap, s32 align);
void ItemGrid_Clear(u16 *p);
u16 *AcreItemGrid_Get(AcreItemGrid *p);
u8 *TownMap_GetAcres(TownMap *p);
BOOL TownMap_HasEnoughRocks(TownMap *o);
BOOL TownMap_HasEnoughSigns(TownMap *o);
void TownMap_ApplyAcreLayouts(TownMap *o, Heap *heap);
MapBlockEntry *MapBlockEntry_NewArray(s32 n, void *heap);
void VillagerRoomMap_Destroy(void *heap);
void VillagerRoomMap_Free(RoomBlockMap *p, void *heap);
BOOL VillagerRoomMap_Init(RoomBlockMap *p, u32 a, void *heap);
BOOL VillagerRoom_LoadLayout(u16 *dst, u32 b, void *heap);
void VillagerRoomMap_Clear(RoomBlockMap *p);
void HouseRoomMap_FreeBlocks(RoomBlockMap *p, void *heap);
BOOL HouseRoomMap_Init(RoomBlockMap *p, s32 i, void *heap);
void HouseRoomMap_ReleaseBg(RoomBlockMap *p);
void HouseRoomMap_BindBg(RoomBlockMap *p);
void HouseRoomMap_Update(RoomBlockMap *p, s32 i);
void HouseRoomMaps_Destroy(void *heap);
RoomBlockMap *HouseRoomMaps_Get(s32 i);
void HouseRoomMap_Clear(RoomBlockMap *p);
void BlockMap_FindItem(u16 *ret, BlockMap *m, VecFx32 *pos, s32 *p4, s32 *p5, u16 a6, u16 a7, s32 a8);
BOOL BlockMap_FindItemAnyAttr(BlockMap *g, s32 *outx, s32 *outz, s32 *a3, s32 *p4, u16 *p5, u16 *p6, s32 filter, u8 p8);
BOOL BlockMap_SetItemAtUnit(BlockMap *g, u16 *a, s32 x, s32 z, u8 d);
BOOL BlockMap_SetItem(BlockMap *g, u16 *a, u32 hx, u32 hy, u32 lx, u32 ly, u8 d);
u16 *BlockMap_GetItemPtr(BlockMap *g, s32 hx, s32 hy, s32 lx, s32 ly, u8 layer);
s32 BlockMap_IsBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly);
s32 BlockMap_ClearBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly);
s32 BlockMap_ClearBuriedAtUnit(BlockMap *g, s32 x, s32 z);
s32 BlockMap_SetBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly);
BOOL BlockMap_RemoveStructure(BlockMap *a, s32 b, s32 c, u16 *d);
void FieldPos_FromUnitCenter(VecFx32 *v, s32 x, s32 z);
void FieldUnit_FromBlockUnit(s32 *ox, s32 *oz, s32 a, s32 b, s32 c, s32 d);
void FieldPos_ToUnit(s32 *ox, s32 *oz, VecFx32 *v);
void FieldPos_ToBlockUnit2(s32 *a, s32 *c, VecFx32 *v);
void FieldPos_ToBlockUnit(s32 *ax, s32 *az, s32 *cx, s32 *cz, VecFx32 *v);
}

static inline BOOL Unk_0204c5c0_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }

static inline BOOL Unk_0204cab4_IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }

static inline BOOL Unk_0204c318_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

static inline BOOL Unk_0204c6a4_Check(u16 *p) {
    BOOL f9 = TRUE, f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v >= 0x26 && v <= 0x2a) f1 = TRUE;
    if (!f1 && !(v >= 0x5d && v <= 0x61)) f2 = FALSE;
    if (!f2 && !(v >= 0x2f && v <= 0x56)) f3 = FALSE;
    if (!f3 && !(v >= 0x57 && v <= 0x5b)) f4 = FALSE;
    if (!f4 && !(v >= 0x66 && v <= 0x68)) f5 = FALSE;
    if (!f5 && !(v == 0x69)) f6 = FALSE;
    if (!f6 && !(v >= 0x6a && v <= 0x6c)) f7 = FALSE;
    if (!f7 && !(v == 0x6d)) f8 = FALSE;
    if (!f8 && !(v >= 0xc8 && v <= 0xcf)) f9 = FALSE;
    return f9;
}

static inline BOOL Unk_0204cd00_R(FgLayoutEntry *g) {
    u32 y = g->y;
    u32 x = g->x;
    BOOL r = FALSE;
    if (x < 0x10 && y < 0x10) r = TRUE;
    return r;
}

static inline BOOL Unk_0204d560_Chk(u16 *t) {
    if (Item_IsFurniture(t)) {
        t[1] = 0xfff1;
        return Item_GetFurnitureIndex(t) == Item_GetFurnitureIndex(t + 1) ? TRUE : FALSE;
    } else {
        return t[0] == 0xfff1 ? TRUE : FALSE;
    }
}

static inline BOOL Unk_0204e51c_InRange(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}


static inline MapBlock *Unk_0204e858_GetCell(BlockMap *g, u32 x, u32 y) {
    if (x < (u32)g->width && y < (u32)g->height && g->blocks != NULL) {
        return &g->blocks[y * g->width + x];
    }
    return NULL;
}

static inline BOOL Unk_0204e8b0_Bit(u16 *m, u32 x, u32 y) {
    BOOL r = FALSE;
    if (x >= 16 || y >= 16) {
    } else {
        r = TRUE;
    }
    if (r) {
        if (x < 16) {
            u32 v = m[y];
            r = TRUE;
            if ((v & (r << x)) != 0) {
                return r;
            }
        }
        r = FALSE;
    } else {
        r = FALSE;
    }
    return r;
}

extern "C" void BlockMap_DebugStub() {}

MapBlockEntry::MapBlockEntry() {
    u16 **p = layers;
    acreId = 0x102a;
    for (s32 i = 0; i < 2; i++) {
        *p++ = NULL;
    }
    buried = NULL;
}

extern "C" MapBlockEntry *MapBlockEntry_NewArray(s32 n, void *heap) {
    MapBlockEntry *p = (MapBlockEntry *)Heap_AllocTail((Heap *)heap, n * sizeof(MapBlockEntry));
    if (p != NULL) {
        for (s32 i = 0; i < n; i++) {
            new (&p[i]) MapBlockEntry;
        }
    }
    return p;
}

extern "C" void FieldPos_ToBlockUnit(s32 *ax, s32 *az, s32 *cx, s32 *cz, VecFx32 *v) {
    *ax = v->x >> 17;
    *az = v->z >> 17;
    *cx = (v->x >> 13) & 15;
    *cz = (v->z >> 13) & 15;
}

extern "C" void FieldPos_ToBlockUnit2(s32 *a, s32 *c, VecFx32 *v) {
    FieldPos_ToBlockUnit(a, a + 1, c, c + 1, v);
}

extern "C" void FieldPos_ToUnit(s32 *ox, s32 *oz, VecFx32 *v) {
    *ox = v->x >> 13;
    *oz = v->z >> 13;
}

extern "C" void FieldUnit_FromBlockUnit(s32 *ox, s32 *oz, s32 a, s32 b, s32 c, s32 d) {
    *ox = (a << 4) + c;
    *oz = (b << 4) + d;
}

extern "C" void FieldPos_SnapToUnitCenter(VecFx32 *dst, VecFx32 *src) {
    FieldPos_FromUnitCenter(dst, src->x >> 13, src->z >> 13);
    dst->y = src->y;
}

extern "C" void FieldPos_FromBlockUnitCenter(VecFx32 *v, s32 a, s32 b, s32 c, s32 d) {
    s32 x = 0, z = 0;
    FieldUnit_FromBlockUnit(&x, &z, a, b, c, d);
    FieldPos_FromUnitCenter(v, x, z);
}

extern "C" void FieldPos_FromUnitCenter(VecFx32 *v, s32 x, s32 z) {
    v->x = (x << 13) + 0x1000;
    v->z = (z << 13) + 0x1000;
    v->y = 0;
}

extern "C" void FieldPos_FromBlockUnit(VecFx32 *v, s32 a, s32 b, s32 c, s32 d) {
    v->x = a << 17;
    v->z = b << 17;
    v->x = v->x + (c << 13);
    v->z = v->z + (d << 13);
}

extern "C" MapBlock *BlockMap_FindBlockAllAttr(BlockMap *g, s32 filter) {
    s32 x, y;
    if (filter != 0) {
        s32 w = g->width;
        s32 h = g->height;
        s32 x0 = 0;
        MapBlock *nullc = NULL;
        for (y = 0; y < h; y++) {
            for (x = x0; x < w; x++) {
                MapBlock *cell;
                if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                    cell = &g->blocks[y * g->width + x];
                } else {
                    cell = nullc;
                }
                if (cell != NULL && MapBlock_HasAllAttr(cell, filter) != 0) {
                    return cell;
                }
            }
        }
    }
    return NULL;
}

extern "C" MapBlock *BlockMap_FindBlockAnyAttr(BlockMap *g, s32 filter) {
    s32 x, y;
    s32 w = g->width;
    s32 h = g->height;
    s32 x0 = 0;
    MapBlock *nullc = NULL;
    for (y = 0; y < h; y++) {
        for (x = x0; x < w; x++) {
            MapBlock *cell;
            if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                cell = &g->blocks[y * g->width + x];
            } else {
                cell = nullc;
            }
            if (cell != NULL && MapBlock_HasAnyAttr(cell, filter) != 0) {
                return cell;
            }
        }
    }
    return NULL;
}

extern "C" s32 BlockMap_GetBlockAttr(BlockMap *g, s32 hx, s32 hy) {
    s32 r = 0;
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    if (cell != NULL) {
        r = MapBlock_GetAttr(cell);
    }
    return r;
}

extern "C" BOOL BlockMap_BlockHasAllAttr(BlockMap *g, s32 hx, s32 hy, s32 a) {
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    s32 r = 0;
    if (cell != NULL) {
        r = MapBlock_HasAllAttr(cell, a);
    }
    return r;
}

extern "C" u16 *BlockMap_GetItemPtr(BlockMap *g, s32 hx, s32 hy, s32 lx, s32 ly, u8 layer) {
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    if (cell != NULL) {
        return MapBlock_GetItemPtr(cell, lx, ly, layer);
    }
    return NULL;
}

extern "C" u16 *BlockMap_GetItemPtrAtPos(BlockMap *g, VecFx32 *v, u8 layer) {
    s32 a[2], c[2];
    a[0] = 0;
    a[1] = 0;
    c[0] = 0;
    c[1] = 0;
    FieldPos_ToBlockUnit2(a, c, v);
    return BlockMap_GetItemPtr(g, a[0], a[1], c[0], c[1], layer);
}

extern "C" BOOL BlockMap_SetItem(BlockMap *g, u16 *a, u32 hx, u32 hy, u32 lx, u32 ly, u8 d) {
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    BOOL r = FALSE;
    if (cell != NULL) {
        r = MapBlock_SetItem(cell, a, lx, ly, d);
    }
    return r;
}

extern "C" BOOL BlockMap_SetItemAtUnit(BlockMap *g, u16 *a, s32 x, s32 z, u8 d) {
    s32 hx = x >> 4;
    s32 hz = z >> 4;
    return BlockMap_SetItem(g, a, hx, hz, x - (hx << 4), z - (hz << 4), d);
}

extern "C" BOOL BlockMap_FindItemAllAttr(BlockMap *g, s32 *outx, s32 *outz, s32 *a3, s32 *p4, u16 *p5, u16 *p6, s32 filter,
                                         u8 p8) {
    s32 x, y;
    s32 w = g->width;
    s32 h = g->height;
    s32 x0 = 0;
    MapBlock *nullc = NULL;
    for (y = 0; y < h; y++) {
        for (x = x0; x < w; x++) {
            MapBlock *cell;
            if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                cell = &g->blocks[y * g->width + x];
            } else {
                cell = nullc;
            }
            if (cell != NULL && MapBlock_HasAllAttr(cell, filter) != 0) {
                if (MapBlock_FindItemInRange(cell, a3, p4, p5, p6, p8) != 0) {
                    *outx = x;
                    *outz = y;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

extern "C" BOOL BlockMap_FindItemAnyAttr(BlockMap *g, s32 *outx, s32 *outz, s32 *a3, s32 *p4, u16 *p5, u16 *p6, s32 filter,
                                         u8 p8) {
    s32 x, y;
    s32 w = g->width;
    s32 h = g->height;
    s32 x0 = 0;
    MapBlock *nullc = NULL;
    for (y = 0; y < h; y++) {
        for (x = x0; x < w; x++) {
            MapBlock *cell;
            if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                cell = &g->blocks[y * g->width + x];
            } else {
                cell = nullc;
            }
            if (cell != NULL) {
                if (filter == 0 || MapBlock_HasAnyAttr(cell, filter) != 0) {
                    if (MapBlock_FindItemInRange(cell, a3, p4, p5, p6, p8) != 0) {
                        *outx = x;
                        *outz = y;
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

extern "C" s32 BlockMap_SetBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly) {
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    s32 r = 0;
    if (cell != NULL) {
        r = MapBlock_SetBuried(cell, lx, ly);
    }
    return r;
}

extern "C" s32 BlockMap_SetBuriedAtUnit(BlockMap *g, s32 x, s32 z) {
    s32 hx = x >> 4;
    s32 hz = z >> 4;
    return BlockMap_SetBuried(g, hx, hz, x - (hx << 4), z - (hz << 4));
}

extern "C" s32 BlockMap_ClearBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly) {
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    s32 r = 0;
    if (cell != NULL) {
        r = MapBlock_ClearBuried(cell, lx, ly);
    }
    return r;
}

extern "C" s32 BlockMap_ClearBuriedAtUnit(BlockMap *g, s32 x, s32 z) {
    s32 hx = x >> 4;
    s32 hz = z >> 4;
    return BlockMap_ClearBuried(g, hx, hz, x - (hx << 4), z - (hz << 4));
}

extern "C" s32 BlockMap_IsBuried(BlockMap *g, u32 hx, u32 hy, u32 lx, u32 ly) {
    MapBlock *cell = Unk_0204e858_GetCell(g, hx, hy);
    BOOL r = FALSE;
    if (cell != NULL && cell->buried != 0) {
        r = Unk_0204e8b0_Bit(cell->buried, lx, ly);
    }
    return r;
}

extern "C" s32 BlockMap_IsBuriedAtUnit(BlockMap *g, s32 x, s32 z) {
    s32 hx = x >> 4;
    s32 hz = z >> 4;
    return BlockMap_IsBuried(g, hx, hz, x - (hx << 4), z - (hz << 4));
}

extern "C" s32 BlockMap_IsBuriedAtPos(BlockMap *g, VecFx32 *v) {
    s32 a[2], c[2];
    a[0] = 0;
    a[1] = 0;
    c[0] = 0;
    c[1] = 0;
    FieldPos_ToBlockUnit2(a, c, v);
    return BlockMap_IsBuried(g, a[0], a[1], c[0], c[1]);
}

BOOL BlockMap::replaceStructure(u16 *a, u16 *b, u16 *c, volatile s32 x, volatile s32 y) {
    BOOL result;
    u32 cnt, cnt2;
    BOOL f9, f8, f7, f6, f5, f4, f3, f2, f1;
    s32 qy;
    s32 gx, gy;
    CommManager *g;
    s32 py;
    u32 j;
    StrBSizeData *h;
    u16 tile, empty, key;
    s32 dx, dy;
    u32 i;
    s32 px, qx;
    u16 *p, *cell, *cell2;
    s32 hx, hy, tx, ty;
    BOOL ok;
    u32 v;
    h = NULL;
    result = FALSE;
    tx = x;
    ty = y;
    hx = tx >> 4;
    hy = ty >> 4;
    p = BlockMap_GetItemPtr(this, hx, hy, tx - (hx << 4), ty - (hy << 4), 0);
    if (p) {
        tile = *p;
        if (Item_IsNormalItem(&tile) || Item_IsFurniture(&tile)) LostAndFound_Add(tile);
    }
    if (Unk_0204e51c_InRange(b, 0x5000, 0x5021)) h = StrBSize_Get(b);
    if (h) {
        cnt = h->getFootprintUnitCount();
        i = 0;
        gx = x;
        gy = y;
        g = gCommManager;
        for (; i < cnt; i++) {
            if (h->getFootprintUnit(&dx, &dy, i)) {
                px = gx + dx;
                py = gy + dy;
                hx = px >> 4;
                hy = py >> 4;
                cell = BlockMap_GetItemPtr(this, hx, hy, px - (hx << 4), py - (hy << 4), 0);
                if (cell) {
                    if (Item_IsFurniture(cell) || Item_IsNormalItem(cell)) {
                        if (!g->isOnline()) LostAndFound_Add(*cell);
                    } else if (Item_IsSnowman(cell)) {
                        data_021ed2e6.remove(Item_GetSnowmanIndex(cell));
                    }
                }
                BlockMap_SetItemAtUnit(this, c, px, py, 0);
                BlockMap_ClearBuriedAtUnit(this, px, py);
            }
        }
        BlockMap_SetItemAtUnit(this, a, x, y, 0);
        if (Item_IsFurniture(c)) {
            key = 0xf030;
            ok = Item_GetFurnitureIndex(c) == Item_GetFurnitureIndex(&key);
        } else {
            ok = *c == 0xf030;
        }
        if (ok) {
            cnt2 = h->getClearUnitCount();
            for (j = 0; j < cnt2; j++) {
                if (h->getClearUnit(&dx, &dy, j)) {
                    qx = gx + dx;
                    qy = gy + dy;
                    hx = qx >> 4;
                    hy = qy >> 4;
                    cell2 = BlockMap_GetItemPtr(this, hx, hy, qx - (hx << 4), qy - (hy << 4), 0);
                    if (cell2) {
                        f9 = TRUE; f8 = TRUE; f7 = TRUE; f6 = TRUE; f5 = TRUE; f4 = TRUE; f3 = TRUE; f2 = TRUE; f1 = FALSE;
                        v = *cell2;
                        if (v >= 0x26 && v <= 0x2a) f1 = TRUE;
                        if (!f1 && !(v >= 0x5d && v <= 0x61)) f2 = FALSE;
                        if (!f2 && !(v >= 0x2f && v <= 0x56)) f3 = FALSE;
                        if (!f3 && !(v >= 0x57 && v <= 0x5b)) f4 = FALSE;
                        if (!f4 && !(v >= 0x66 && v <= 0x68)) f5 = FALSE;
                        if (!f5 && !(v == 0x69)) f6 = FALSE;
                        if (!f6 && !(v >= 0x6a && v <= 0x6c)) f7 = FALSE;
                        if (!f7 && !(v == 0x6d)) f8 = FALSE;
                        if (!f8 && !(v >= 0xc8 && v <= 0xcf)) f9 = FALSE;
                        if ((f9 && !Item_IsTreeStage0(cell2)) || Item_GetStumpSize(cell2) != -1) {
                            empty = 0xfff1;
                            BlockMap_SetItemAtUnit(this, &empty, qx, qy, 0);
                        }
                    }
                }
            }
        }
        result = TRUE;
    }
    return result;
}

BOOL BlockMap::putStructure(u16 *a, s32 x, s32 y) {
    BOOL r = FALSE;
    if (Unk_0204e51c_InRange(a, 0x5000, 0x5021)) {
        u16 t = 0xf030;
        r = replaceStructure(a, a, &t, x, y);
    }
    return r;
}

BOOL BlockMap::removeStructure(s32 x, s32 y, u16 *p) {
    u16 t[2];
    s32 hx = x >> 4, hy = y >> 4;
    u16 *c = BlockMap_GetItemPtr(this, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    BOOL r = FALSE;
    if (c) {
        if (Unk_0204e51c_InRange(c, 0x5000, 0x5021)) {
            t[0] = 0xfff1;
            if (p) t[0] = *p;
            t[1] = 0xfff1;
            r = replaceStructure(t, c, &t[1], x, y);
        }
    }
    return r;
}

s32 BlockMap::canPlaceItem(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_CanPlaceItem(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::canPlaceItemAtBlockUnit(s32 a, s32 b, s32 c, s32 d) {
    s32 x = 0, y = 0;
    FieldUnit_FromBlockUnit(&x, &y, a, b, c, d);
    return canPlaceItem(x, y);
}

s32 BlockMap::isWalkable(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_IsWalkable(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::isGrassSurface(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_IsGrassSurface(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::isShore(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_IsShore(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::getDigKind(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_GetDigKind(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::getPlantFlag(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_GetPlantFlag(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::getWalkLinks(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_GetWalkLinks(a, b);
    CollisionMap_Select(0);
    return r;
}

s32 BlockMap::getWalkLinksAtPos(void *a) {
    s32 x = 0, y = 0;
    FieldPos_ToUnit(&x, &y, (VecFx32 *)a);
    return getWalkLinks(x, y);
}

s32 BlockMap::clearPlantFlag(s32 a, s32 b) {
    CollisionMap_Select(mapSlot);
    s32 r = Ground_ClearPlantFlag(a, b);
    CollisionMap_Select(0);
    return r;
}

void BlockMap::clear() {
    s32 z = 0;
    width = z;
    height = z;
    unitsX = z;
    unitsZ = z;
    blocks = NULL;
    mapSlot = z;
}

void BlockMap::free(void *heap) {
    if (blocks) {
        Heap_Free((Heap *)heap, blocks);
        blocks = NULL;
    }
    CollisionMap_Release(mapSlot);
}
char sFgDataFoIndexPath[] = "fg_data/fo_h.bin";

FgDataIndex *gFgDataIndex;

char sFgDataNfPath[] = "fg_data/nf.bin";

TownBlockMap *gTownBlockMap;

char sFgDataFiPath[] = "fg_data/fi.bin";

char sFgDataNrPath[] = "fg_data/nr.bin";

char sFgDataNrIndexPath[] = "fg_data/nr_h.bin";

RoomBlockMap *gVillagerRoomMap;

char sFgDataFoPath[] = "fg_data/fo.bin";

char sFgDataFiIndexPath[] = "fg_data/fi_h.bin";

BOOL BlockMap::build(MapBlockEntry *e, BlockMapSize *sz, void *heap) {
    s32 count = sz->v[0] * sz->v[1];
    BOOL r = FALSE;
    mapSlot = 0;
    if (blocks == NULL) blocks = MapBlock_NewArray(count, heap, 4);
    if (blocks) {
        BlockMapBuildLocals l;
        MapBlock *buf;
        s32 zero = 0;
        l.x = zero;
        l.y = zero;
        l.v.x = zero;
        l.v.y = zero;
        l.v.z = zero;
        buf = blocks;
        width = sz->v[0];
        height = sz->v[1];
        worldWidth = width * data_020c8cbc;
        worldHeight = height * data_020c8cb8;
        FieldUnit_FromBlockUnit(&unitsX, &unitsZ, width, height, 0, 0);
        static TownUnitShapeQuery obj;
        CollisionMap_Bind(width, height, &obj, mapSlot);
        for (l.y = 0; l.y < height; l.y++) {
            for (l.x = 0; l.x < width; l.x++) {
                VecFx32 w;
                l.v.x = l.x << 17;
                l.v.z = l.y << 17;
                w = l.v;
                BgAcreModel *h = BgModelCache_Get()->getAcre(e->acreId);
                MapBlock_Init(buf, e->acreId, &w, e->layers[0], e->layers[1], e->buried, h, NULL,
                              (Unk_02037638_S8 *)&l, 0);
                buf++;
                e++;
            }
        }
        r = TRUE;
    }
    return r;
}

BOOL BlockMap::placeStructure(u16 *a, s32 x, s32 y, u8 flag) {
    u16 tile;
    s32 hx = x >> 4, hy = y >> 4;
    u16 *p = BlockMap_GetItemPtr(this, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    tile = 0xfff1;
    if (p) tile = *p;
    if (flag && FieldStructureMgr_Get()) {
        return FieldStructureMgr_SpawnBuilding(FieldStructureMgr_Get(), a, x, y, 1);
    }
    if (putStructure(a, x, y)) {
        if (Item_IsNormalItem(&tile) || Item_IsFurniture(&tile)) LostAndFound_Add(tile);
        return TRUE;
    }
    return FALSE;
}

TownMap::TownMap() {}

TownMap::~TownMap() {}

void TownMap::clear() {
    u8 *p = acres;
    AcreItemGrid *a = items;
    BuriedMask *b = buried;
    s32 i, j;
    for (i = 0; i < 0x24; i++) *p++ = 0x86;
    for (j = 0; j < 16; j++) {
        ItemGrid_Clear(&a->e[0].id);
        BuriedMask_Reset(b);
        a++;
        b++;
    }
    grassType = 0;
}

u16 *TownMap::getAcreItems(Vec2 *in) {
    u16 *r = NULL;
    Vec2 a, b;
    a.x = 0;
    a.y = 0;
    b.x = in->x;
    b.y = in->y;
    if (toTownAcreIndex(&a, &b)) {
        r = AcreItemGrid_Get(&items[a.y * 4 + a.x]);
    }
    return r;
}

u16 *TownMap::getAcreBuried(Vec2 *in) {
    u16 *r = NULL;
    Vec2 a, b;
    a.x = 0;
    a.y = 0;
    b.x = in->x;
    b.y = in->y;
    if (toTownAcreIndex(&a, &b)) {
        r = (u16 *)buried[a.y * 4 + a.x].data;
    }
    return r;
}

BOOL TownMap::isTownAcre(s32 x, s32 y) {
    if (x > 0 && x < 5 && y > 0 && y < 5) return TRUE;
    return FALSE;
}

BOOL TownMap::toTownAcreIndex(Vec2 *out, Vec2 *in) {
    BOOL r = FALSE;
    if (isTownAcre(in->x, in->y)) {
        out->x = in->x - 1;
        out->y = in->y - 1;
        r = TRUE;
    }
    return r;
}

u32 TownMap::getGrassType() {
    return grassType;
}

void TownMap::updateGroundSeason() {
    u32 v = GroundSeason_CalcPhase();
    groundSeason = v;
    data_021ed2e6.updateDaily();
}

MapBlockEntry *TownMap::buildBlockEntries(void *heap) {
    volatile s32 zero0, zero1;
    Vec2 pos;
    MapBlockEntry *r;
    s32 idx;
    pos.x = 0;
    pos.y = 0;
    r = MapBlockEntry_NewArray(0x24, heap);
    if (r) {
        idx = 0;
        pos.y = 0;
        zero0 = 0;
        zero1 = 0;
        for (; pos.y < 6; pos.y++) {
            for (pos.x = zero0; pos.x < 6; pos.x++) {
                MapBlockEntry *e = &r[idx];
                e->acreId = acres[pos.y * 6 + pos.x];
                e->layers[0] = getAcreItems(&pos);
                e->layers[1] = NULL;
                e->buried = getAcreBuried(&pos);
                idx++;
            }
        }
    }
    return r;
}

extern "C" BOOL TownMap_HasEnoughSigns(TownMap *o) {
    s32 cnt = 0;
    Vec2 xy;
    BOOL r;
    u16 *p;
    s32 k;
    xy.x = 0;
    xy.y = 0;
    r = FALSE;
    k = 0;
    for (xy.y = 0; xy.y < 6; xy.y++) {
        for (xy.x = 0; xy.x < 6; xy.x++) {
            p = o->getAcreItems(&xy);
            if (p) {
                for (k = 0; k < 0x100; p++, k++) {
                    if (*p == 0x500a) cnt++;
                }
            }
        }
    }
    if (cnt >= 9) r = TRUE;
    return r;
}

extern "C" BOOL TownMap_HasEnoughRocks(TownMap *o) {
    s32 cnt = 0;
    Vec2 xy;
    BOOL r;
    u16 *p;
    s32 k;
    BOOL f;
    xy.x = 0;
    xy.y = 0;
    r = FALSE;
    k = 0;
    f = FALSE;
    for (xy.y = 0; xy.y < 6; xy.y++) {
        for (xy.x = 0; xy.x < 6; xy.x++) {
            p = o->getAcreItems(&xy);
            if (p) {
                for (k = 0; k < 0x100; p++, k++) {
                    f = FALSE;
                    if (*p >= 0xe3 && *p <= 0xe7) f = TRUE;
                    if (f) cnt++;
                }
            }
        }
    }
    if (cnt >= 5) r = TRUE;
    return r;
}

extern "C" void TownMap_ApplyAcreLayouts(TownMap *o, Heap *heap) {
    Vec2 xy;
    xy.x = 0;
    xy.y = 0;
    for (xy.y = 0; xy.y < 6; xy.y++) {
        for (xy.x = 0; xy.x < 6; xy.x++) {
            u16 *p = o->getAcreItems(&xy);
            if (p) {
                FgData_ApplyLayoutGlobal(p, 0, o->acres[xy.y * 6 + xy.x] & 0xfff, heap);
            }
        }
    }
}

extern "C" void TownMap_Generate(TownMap *o, Heap *heap) {
    o->clear();
    o->grassType = Random_GlobalBelow(3);
    do {
        Town_GenerateAcres(o->acres);
        TownMap_ApplyAcreLayouts(o, heap);
    } while (!TownMap_HasEnoughSigns(o) || !TownMap_HasEnoughRocks(o));
}

extern "C" u8 *TownMap_GetAcres(TownMap *p) {
    return p->acres;
}

AcreItemGrid::AcreItemGrid() {}

AcreItemGrid::~AcreItemGrid() {}

extern "C" void ItemGrid_Clear(u16 *p) {
    s32 i;
    for (i = 0; i < 0x100; p++, i++) *p = 0xfff1;
}

extern "C" u16 *AcreItemGrid_Get(AcreItemGrid *p) { return &p->e[0].id; }

void TownBlockMap::clear() {
    width = 0;
    height = 0;
    unitsX = 0;
    unitsZ = 0;
    blocks = 0;
    mapSlot = 1;
}

extern "C" BOOL TownBlockMap_Create(void *heap) {
    BOOL r = TRUE;
    TownBclHeap_Create((Heap *)heap);
    if (!gTownBlockMap) {
        gTownBlockMap = (TownBlockMap *)Heap_Alloc((Heap *)heap, sizeof(TownBlockMap));
        if (gTownBlockMap) {
            if (gTownBlockMap) gTownBlockMap->clear();
            r = gTownBlockMap->build(heap);
        }
    }
    return r;
}

extern "C" void TownBlockMap_Destroy(void *heap) {
    if (gTownBlockMap) {
        gTownBlockMap->releaseBg();
        gTownBlockMap->freeBlocks(heap);
        Heap_Free((Heap *)heap, gTownBlockMap);
        gTownBlockMap = 0;
    }
    TownBclHeap_Destroy();
}

BOOL TownBlockMap::build(void *heap) {
     BOOL result; TownBlockMapBuildLocals l; MapBlock *cell; MapBlockEntry *q; MapBlockEntry *tbl;
    result = FALSE;
    mapSlot = 1;
    if (!blocks) blocks = MapBlock_NewArray(0x24, heap, 4);
    tbl = gSaveTownMap.buildBlockEntries(heap);
    if (blocks && tbl) {
        l.xy[0] = 0;
        l.xy[1] = 0;
        l.v.x = 0;
        l.v.y = 0;
        l.v.z = 0;
        cell = blocks;
        q = tbl;
        width = 6;
        height = 6;
        worldWidth = width * data_020c8cbc;
        worldHeight = height * data_020c8cb8;
        FieldUnit_FromBlockUnit(&unitsX, &unitsZ, width, height, 0, 0);
        for (l.xy[1] = 0; l.xy[1] < height; l.xy[1]++) {
            for (l.xy[0] = 0; l.xy[0] < width; l.xy[0]++) {
                l.v.x = l.xy[0] << 17;
                l.v.z = l.xy[1] << 17;
                l.w.x = l.v.x;
                l.w.y = l.v.y;
                l.w.z = l.v.z;
                MapBlock_Init(cell, q->acreId, &l.w, q->layers[0], q->layers[1], q->buried, 0, NULL, (Unk_02037638_S8 *)l.xy,
                              mapSlot);
                cell++;
                q++;
            }
        }
        result = TRUE;
    }
    if (tbl) Heap_Free((Heap *)heap, tbl);
    return result;
}

void TownBlockMap::freeBlocks(void *heap) {
    if (blocks) {
        Heap_Free((Heap *)heap, blocks);
        blocks = 0;
    }
}

void TownBlockMap::updateAcreIds() {
    s32 x; u8 *p; s32 y; MapBlock *c;
    p = TownMap_GetAcres(&gSaveTownMap);
    if (p) {
        c = blocks;
        for (y = 0; y < height; y++) {
            for (x = 0; x < width; x++) {
                if (c) ((MapBlockAcre *)c)->setAcreId(*p);
                c++;
                p++;
            }
        }
    }
}

void TownBlockMap::bindBg() {
    s32 x, y;
    ((Heap *)gTownBclHeap)->freeAll();
    CollisionMap_Bind(width, height, 0, mapSlot);
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            MapBlock *c;
            if ((u32)x < (u32)width && (u32)y < (u32)height && blocks) {
                c = blocks + (x + y * width);
            } else {
                c = 0;
            }
            if (c) {
                u32 t = ((MapBlockAcre *)c)->getAcreId();
                void *d = gTownBclHeap;
                BgModelCache_Get();
                c->bindBg(0, BgModel_LoadBcl(t, d), mapSlot);
            }
        }
    }
}

void TownBlockMap::releaseBg() {
    CollisionMap_Release(mapSlot);
}

extern "C" TownBlockMap *TownBlockMap_Get() {
    return gTownBlockMap;
}

extern "C" BOOL BlockMap_PutStructure(BlockMap *a, u16 *b, s32 c, s32 d) {
    return a->putStructure(b, c, d);
}

extern "C" BOOL BlockMap_RemoveStructure(BlockMap *a, s32 b, s32 c, u16 *d) {
    return a->removeStructure(b, c, d);
}

extern "C" BOOL BlockMap_RemoveStructureAt(BlockMap *a, s32 b, s32 c, s32 d, s32 e, u16 *f) {
    s32 l8 = 0, lc = 0;
    FieldUnit_FromBlockUnit(&l8, &lc, b, c, d, e);
    return BlockMap_RemoveStructure(a, l8, lc, f);
}

extern "C" void BlockMap_FindItem(u16 *ret, BlockMap *m, VecFx32 *pos, s32 *p4, s32 *p5, u16 a6, u16 a7, s32 a8) {
    u16 t[2];
    s32 l1c, l20, l24, l28;
    StackPad16 pad;
    t[0] = a6;
    t[1] = a7;
    if (BlockMap_FindItemAnyAttr(m, &l24, &l28, &l1c, &l20, &t[0], &t[1], a8, 0)) {
        FieldUnit_FromBlockUnit(p4, p5, l24, l28, l1c, l20);
        FieldPos_FromUnitCenter(pos, *p4, *p5);
        s32 x = *p4;
        s32 y = *p5;
        s32 tx = x >> 4;
        s32 ty = y >> 4;
        u16 *r = BlockMap_GetItemPtr(m, tx, ty, x - (tx << 4), y - (ty << 4), 0);
        if (r) {
            *ret = *r;
            return;
        }
    }
    *ret = 0xfff1;
}

extern "C" void BlockMap_FindStructure(u16 *ret, BlockMap *m, VecFx32 *pos, s32 *p4, s32 *p5, u16 a6, u16 a7, s32 a8) {
    StrBSizeData *h; u32 n; s32 sx, sz, ax; u16 t[2]; s32 a, b; VecFx32 v; u32 i; s32 d, az, zz;
    BlockMap_FindItem(t, m, &v, &a, &b, a6, a7, a8);
    if (!Unk_0204d560_Chk(t)) {
        h = StrBSize_Get(t);
        if (h) {
            n = h->getTriangleCount();
            sx = 0; sz = 0; i = 0;
            for (; i < n; i++) {
                VecFx32 v1, v2, v3;
                if (h->getTriangle(&v1.x, &v2.x, &v3.x, i)) {
                    sx += v1.x; sx += v2.x; sx += v3.x;
                    sz += v1.z; sz += v2.z; sz += v3.z;
                }
            }
            d = (s32)h->getTriangleCount() * 3 << 12;
            ax = FX_Div(sx, d);
            az = FX_Div(sz, d);
            zz = v.z + az + 0x1000;
            s32 yy = Ground_GetDefaultY();
            pos->x = v.x + ax;
            pos->y = yy;
            pos->z = zz;
            if (p4) *p4 = a;
            if (p5) *p5 = b;
            *ret = t[0];
            return;
        }
    }
    *ret = 0xfff1;
}

extern "C" BOOL Town_FindTownHall(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4) {
    u16 t[2];
    BlockMap_FindStructure(t, a, pos, p3, p4, 0x5000, 0x5000, 0x200);
    return Unk_0204d560_Chk(t) ? FALSE : TRUE;
}

extern "C" BOOL Town_FindPlayerHouse(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4) {
    u16 t[2];
    BlockMap_FindStructure(t, a, pos, p3, p4, 0x5014, 0x501a, 1);
    return Unk_0204d560_Chk(t) ? FALSE : TRUE;
}

extern "C" BOOL Town_FindGateHouse(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4) {
    u16 t[2];
    BlockMap_FindStructure(t, a, pos, p3, p4, 0x500b, 0x500b, 0x400);
    return Unk_0204d560_Chk(t) ? FALSE : TRUE;
}

extern "C" BOOL Town_FindTownHallFront(BlockMap *a, VecFx32 *pos, s32 *p3, s32 *p4) {
    u16 t[2];
    BlockMap_FindStructure(t, a, pos, p3, p4, 0x5000, 0x5000, 0x200);
    if (!Unk_0204d560_Chk(t)) {
        pos->x -= 0x2000;
        pos->z += 0x8000;
        if (p3) *p3 -= 1;
        if (p4) *p4 += 4;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Town_FindGulliverShip(BlockMap *a, VecFx32 *b) {
    u16 t[2];
    s32 x, y;
    BlockMap_FindItem(t, a, b, &x, &y, 0x5020, 0x5020, 0);
    return Unk_0204d560_Chk(t) ? FALSE : TRUE;
}

extern "C" void HouseRoomMap_Clear(RoomBlockMap *p) {
    p->width = 0;
    p->height = 0;
    p->unitsX = 0;
    p->unitsZ = 0;
    p->blocks = 0;
    p->mapSlot = 2;
}

extern "C" RoomBlockMap *HouseRoomMaps_Get(s32 i) {
    RoomBlockMap *r = 0;
    if (HouseData_IsValidRoomIndex(i)) r = gHouseRoomMaps[i];
    return r;
}

extern "C" RoomBlockMap *HouseRoomMaps_GetForScene(s32 a) {
    RoomBlockMap *r = 0;
    if (SceneId_IsHouseRoom(a)) {
        r = HouseRoomMaps_Get(SceneId_GetHouseRoom(a));
    }
    return r;
}

extern "C" BOOL HouseRoomMaps_Create(void *heap) {
    BOOL r = TRUE;
    s32 i;
    RoomBclHeap_Create((Heap *)heap);
    for (i = 0; i < 5; i++) {
        RoomBlockMap **e = &gHouseRoomMaps[i];
        if (!*e) {
            *e = (RoomBlockMap *)Heap_Alloc((Heap *)heap, sizeof(RoomBlockMap));
            if (*e) {
                if (*e) HouseRoomMap_Clear(*e);
                if (!HouseRoomMap_Init(*e, i, heap)) {
                    r = FALSE;
                    break;
                }
            } else {
                r = FALSE;
                break;
            }
        }
    }
    if (!r) HouseRoomMaps_Destroy(heap);
    return r;
}

extern "C" void HouseRoomMaps_Destroy(void *heap) {
    s32 i;
    for (i = 0; i < 5; i++) {
        RoomBlockMap **e = &gHouseRoomMaps[i];
        if (*e) {
            HouseRoomMap_ReleaseBg(*e);
            HouseRoomMap_FreeBlocks(*e, heap);
            Heap_Free((Heap *)heap, *e);
            *e = 0;
        }
    }
    RoomBclHeap_Destroy();
}

extern "C" void HouseRoomMaps_UpdateAll() {
    s32 i;
    for (i = 0; i < 5; i++) {
        if (gHouseRoomMaps[i]) HouseRoomMap_Update(gHouseRoomMaps[i], i);
    }
}

extern "C" void HouseRoomMap_Update(RoomBlockMap *p, s32 i) {
    u32 v = gSaveHouse.getRoomAcreId(i);
    if (p->blocks) ((MapBlockAcre *)p->blocks)->setAcreId(v);
}

extern "C" void HouseRoomMaps_BindBg() {
    s32 i;
    ((Heap *)(gRoomBclHeap))->freeAll();
    for (i = 0; i < 5; i++) {
        if (gHouseRoomMaps[i]) HouseRoomMap_BindBg(gHouseRoomMaps[i]);
    }
}

extern "C" void HouseRoomMap_BindBg(RoomBlockMap *p) {
    MapBlock *h;
    CollisionMap_Bind(p->width, p->height, 0, p->mapSlot);
    if ((u32)p->width != 0 && (u32)p->height != 0) {
        h = p->blocks;
        if (h != 0) goto join;
    }
    h = 0;
join:
    if (h) {
        u32 a = ((MapBlockAcre *)h)->getAcreId();
        void *g = gRoomBclHeap;
        BgModelCache_Get();
        h->bindBg(0, BgModel_LoadBcl(a, g), p->mapSlot);
    }
}

extern "C" void HouseRoomMap_ReleaseBg(RoomBlockMap *p) {
    CollisionMap_Release(p->mapSlot);
}

extern "C" BOOL HouseRoomMap_Init(RoomBlockMap *p, s32 i, void *heap) {
    BOOL r = FALSE;
    MapBlockEntry *info;
    struct { VecFx32 v, w; } l;
    p->mapSlot = i + 2;
    if (!p->blocks) {
        p->blocks = MapBlock_NewArray(1, heap, 4);
    }
    info = gSaveHouse.buildRoomBlockEntry(i, heap);
    if (p->blocks && info) {
        l.v.x = 0; l.v.y = 0; l.v.z = 0;
        p->width = 1;
        p->height = 1;
        p->worldWidth = data_020c8cbc;
        p->worldHeight = data_020c8cb8;
        FieldUnit_FromBlockUnit(&p->unitsX, &p->unitsZ, p->width, p->height, 0, 0);
        CollisionMap_Bind(p->width, p->height, 0, p->mapSlot);
        l.v.x = 0; l.v.z = 0;
        l.w = l.v;
        p->blocks->init(info->acreId, &l.w, info->layers[0], info->layers[1], info->buried, 0, NULL, 0, 0, p->mapSlot);
        Heap_Free((Heap *)heap, info);
        r = TRUE;
    }
    return r;
}

extern "C" void HouseRoomMap_FreeBlocks(RoomBlockMap *p, void *heap) {
    if (p->blocks) {
        Heap_Free((Heap *)heap, p->blocks);
        p->blocks = 0;
    }
}

extern "C" void VillagerRoomMap_Clear(RoomBlockMap *p) {
    p->width = 0;
    p->height = 0;
    p->unitsX = 0;
    p->unitsZ = 0;
    p->blocks = 0;
    p->mapSlot = 7;
    p->itemGrid = 0;
}

extern "C" MapBlockEntry *VillagerRoom_BuildEntry(u16 *dst, u32 b, void *heap) {
    MapBlockEntry *p = MapBlockEntry_NewArray(1, heap);
    if (p) {
        VillagerDataItemView *h = (VillagerDataItemView *)SaveVillagers_Get(gSaveVillagers, b);
        if (h) {
            p->acreId = h->getInfo28Item();
        } else {
            p->acreId = 0x1010;
        }
        VillagerRoom_LoadLayout(dst, b, heap);
        p->layers[0] = dst;
        p->layers[1] = NULL;
        p->buried = NULL;
    }
    return p;
}

extern "C" BOOL VillagerRoom_LoadLayout(u16 *dst, u32 b, void *heap) {
    s32 x, y;
    VillagerDataItemView *h;
    BOOL r;
    x = 2;
    y = 0;
    r = FALSE;
    h = (VillagerDataItemView *)SaveVillagers_Get(gSaveVillagers, b);
    if (h) h->getRoomLayout(&x, &y);
    if (h) {
        if (FgData_ApplyLayoutGlobal(dst, x, y, heap)) {
            Villager_ResolveRoomLayout((VillagerData *)h, dst);
            r = TRUE;
        }
    }
    return r;
}

extern "C" BOOL VillagerRoomMap_Init(RoomBlockMap *p, u32 a, void *heap) {
    BOOL r = FALSE;
    MapBlockEntry *info;
    struct { VecFx32 v, w; } l;
    p->mapSlot = 7;
    if (!p->blocks) {
        p->blocks = MapBlock_NewArray(1, heap, -4);
    }
    if (!p->itemGrid) {
        p->itemGrid = ItemGrid_Alloc(heap, -4);
    }
    info = VillagerRoom_BuildEntry(p->itemGrid, a, heap);
    if (p->blocks && info && p->itemGrid) {
        l.v.x = 0; l.v.y = 0; l.v.z = 0;
        p->width = 1;
        p->height = 1;
        p->worldWidth = data_020c8cbc;
        p->worldHeight = data_020c8cb8;
        FieldUnit_FromBlockUnit(&p->unitsX, &p->unitsZ, p->width, p->height, 0, 0);
        CollisionMap_Bind(p->width, p->height, 0, p->mapSlot);
        l.v.x = 0; l.v.z = 0;
        void *t = BgModelCache_Get()->getAcreBcl(info->acreId);
        l.w = l.v;
        p->blocks->init(info->acreId, &l.w, info->layers[0], info->layers[1], info->buried, 0, t, 0, 0, p->mapSlot);
        Heap_Free((Heap *)heap, info);
        r = TRUE;
    }
    return r;
}

extern "C" RoomBlockMap *VillagerRoomMap_Create(u32 a, void *heap) {
    RoomBlockMap *r = 0;
    if (!gVillagerRoomMap) {
        gVillagerRoomMap = (RoomBlockMap *)Heap_AllocTail((Heap *)heap, sizeof(RoomBlockMap));
        if (gVillagerRoomMap) {
            if (gVillagerRoomMap) VillagerRoomMap_Clear(gVillagerRoomMap);
            if (VillagerRoomMap_Init(gVillagerRoomMap, a, heap)) {
                r = gVillagerRoomMap;
            } else {
                VillagerRoomMap_Destroy(heap);
            }
        }
    }
    return r;
}

extern "C" void VillagerRoomMap_Free(RoomBlockMap *p, void *heap) {
    if (p->blocks) {
        Heap_Free((Heap *)heap, p->blocks);
        p->blocks = 0;
    }
    if (p->itemGrid) {
        Heap_Free((Heap *)heap, p->itemGrid);
        p->itemGrid = 0;
    }
    CollisionMap_Release(p->mapSlot);
}

extern "C" void VillagerRoomMap_Destroy(void *heap) {
    if (gVillagerRoomMap) {
        VillagerRoomMap_Free(gVillagerRoomMap, heap);
        Heap_Free((Heap *)heap, gVillagerRoomMap);
        gVillagerRoomMap = 0;
    }
}

extern "C" void FgData_ClearIndices(FgDataIndex *t) {
    s32 i;
    for (i = 0; i < 4; i++) {
        t[i].data = 0;
        t[i].count = 0;
    }
}

extern "C" BOOL FgData_Load(void *heap) {
    BOOL r = FALSE;
    if (!gFgDataIndex) {
        gFgDataIndex = (FgDataIndex *)Heap_Alloc((Heap *)heap, sizeof(FgDataIndex[4]));
        if (gFgDataIndex) {
            if (gFgDataIndex) FgData_ClearIndices(gFgDataIndex);
            if (FgData_LoadIndices(gFgDataIndex, heap)) {
                r = TRUE;
            } else {
                FgData_Unload(heap);
                gFgDataIndex = 0;
            }
        }
    }
    return r;
}

extern "C" void FgData_Unload(void *heap) {
    if (gFgDataIndex) {
        FgData_FreeIndices(gFgDataIndex, heap);
        Heap_Free((Heap *)heap, gFgDataIndex);
        gFgDataIndex = 0;
    }
}

extern "C" BOOL FgData_LoadIndices(FgDataIndex *t, void *heap) {
    const Unk_020ca2f4_Ent *e = sFgDataFiles;
    s32 i = 0;
    u32 size = 0;
    BOOL r = TRUE;
    for (; i < 4; t++, e++, i++) {
        t->data = (u16 *)File_LoadAlloc(e->indexPath, heap, 4, &size);
        if (t->data) {
            t->count = size >> 1;
        } else {
            r = FALSE;
            t->count = 0;
            break;
        }
    }
    return r;
}

extern "C" void FgData_FreeIndices(FgDataIndex *t, void *heap) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (t->data) {
            Heap_Free((Heap *)heap, t->data);
            t->data = 0;
            t->count = 0;
            t++;
        }
    }
}

extern "C" BOOL FgData_IsValidTable(FgDataIndex *t, s32 i) {
    if (i >= 0 && i < 4) return TRUE;
    return FALSE;
}

extern "C" s32 FgData_GetLayoutOffset(FgDataIndex *t, s32 i, s32 j) {
    s32 r = 0;
    if (FgData_IsValidTable(t, i)) {
        FgDataIndex *e = &t[i];
        u16 *d = e->data;
        if (d && j < e->count) {
            s32 k;
            for (k = 0; k < j; d++, k++) {
                r += *d;
            }
        }
    }
    return r;
}

extern "C" s32 FgData_GetLayoutSize(FgDataIndex *t, s32 i, s32 j) {
    s32 r = 0;
    if (FgData_IsValidTable(t, i)) {
        FgDataIndex *e = &t[i];
        u16 *d = e->data;
        if (d && j < e->count) {
            r = d[j];
        }
    }
    return r;
}

extern "C" BOOL FgData_HasLayout(s32 a, s32 b) {
    BOOL r = FALSE;
    if (gFgDataIndex) {
        if (FgData_GetLayoutSize(gFgDataIndex, a, b) > 0) r = TRUE;
    }
    return r;
}

extern "C" u16 *ItemGrid_Alloc(void *heap, s32 align) {
    u16 *p = (u16 *)Heap_AllocAligned((Heap *)heap, 0x200, align);
    if (p) {
        s32 i;
        for (i = 0; i < 0x100; i++) {
            p[i] = 0xfff1;
        }
    }
    return p;
}

extern "C" BOOL FgData_ReadLayout(FgDataIndex *t, void *dst, s32 i, s32 j, s32 n) {
    s32 off = FgData_GetLayoutOffset(t, i, j);
    const Unk_020ca2f4_Ent *e = &sFgDataFiles[i];
    File_ReadRangeByPath(e->dataPath, dst, n, off);
    return TRUE;
}

extern "C" BOOL FgData_ApplyLayoutGlobal(u16 *dst, s32 i, s32 j, void *heap) {
    BOOL r = FALSE;
    if (gFgDataIndex) {
        r = FgData_ApplyLayout(gFgDataIndex, dst, i, j, heap);
    }
    return r;
}

extern "C" u16 *FgData_CreateLayoutGrid(s32 a, s32 b, void *heap, s32 d) {
    u16 *r = 0;
    if (gFgDataIndex) {
        r = ItemGrid_Alloc(heap, d);
        if (r) {
            if (!FgData_ApplyLayout(gFgDataIndex, r, a, b, heap)) {
                Heap_Free((Heap *)heap, r);
                r = 0;
            }
        }
    }
    return r;
}

extern "C" BOOL FgData_ApplyLayout(FgDataIndex *t, u16 *dst, s32 i, s32 j, void *heap) {
    s32 n = FgData_GetLayoutSize(t, i, j);
    BOOL result = FALSE;
    if (dst && n > 0 && (n & 3) == 0 && FgData_IsValidTable(t, i)) {
        void *buf = Heap_AllocTail((Heap *)heap, n);
        FgLayoutEntry *p = (FgLayoutEntry *)buf;
        if (p) {
            if (FgData_ReadLayout(t, buf, i, j, n)) {
                s32 cnt = n >> 2;
                s32 k;
                for (k = 0; k < cnt; p++, k++) {
                    if (Unk_0204cd00_R(p)) {
                        dst[(p->y << 4) + p->x] = p->v;
                    }
                }
            }
            Heap_Free((Heap *)heap, buf);
            result = TRUE;
        }
    }
    return result;
}

extern "C" void *FgData_ReadLayoutEntries(FgDataIndex *t, s32 *b, s32 c, s32 d, void *heap) {
    s32 n = FgData_GetLayoutSize(t, c, d);
    if (n > 0 && (n & 3) == 0 && FgData_IsValidTable(t, c)) {
        void *buf = Heap_AllocAligned((Heap *)heap, n, 4);
        if (buf) {
            if (FgData_ReadLayout(t, buf, c, d, n)) {
                *b = n >> 2;
                return buf;
            }
            Heap_Free((Heap *)heap, buf);
        }
    }
    return 0;
}

extern "C" void *FgData_ReadVillagerLayout(FgDataIndex *a, s32 *b, s32 c, void *d) {
    VillagerDataItemView *h = (VillagerDataItemView *)SaveVillagers_Get(gSaveVillagers, c);
    s32 x = 2, y = 0;
    if (h && h->getRoomLayout(&x, &y)) {
        return FgData_ReadLayoutEntries(a, b, x, y, d);
    }
    return 0;
}

extern "C" void *FgData_GetVillagerLayout(s32 *count, s32 villager, void *heap) {
    if (gFgDataIndex != NULL) return FgData_ReadVillagerLayout(gFgDataIndex, count, villager, heap);
    return 0;
}

char sFgDataNfIndexPath[] = "fg_data/nf_h.bin";

RoomBlockMap *gHouseRoomMaps[5];

const Unk_020ca2f4_Ent sFgDataFiles[4] = {
    {sFgDataFoIndexPath, sFgDataFoPath},
    {sFgDataFiIndexPath, sFgDataFiPath},
    {sFgDataNrIndexPath, sFgDataNrPath},
    {sFgDataNfIndexPath, sFgDataNfPath},
};

#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_02037674_V3.h"
#include "gfx/BgModelCache.h"
#include "town/MapBlock.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_02037260.h"
#include "proto/main/unk_0202fa70.h"
#include "proto/main/unk_02037358.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0209bca8.h"


extern "C" {
void MI_CpuFill8(void *, s32, s32);
}

u8 *sAcreAttrData;
u32 sAcreAttrSize;


struct Marker1 {
    u16 v;
};

static inline BOOL Unk_020374f4_Range(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}


extern "C" u32 AcreAttr_GetType(u32 i);
extern "C" BOOL Bits16_Clear(void *, u16 *p, s32 bit);
extern "C" BOOL Bits16_Set(void *, u16 *p, s32 bit);
extern "C" u32 MapBlock_GetAttr(MapBlock *o);
extern "C" u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
extern "C" void Unit_SplitIndex(s32 *a, s32 *b, s32 v);

void MapBlock::clear() {
    blockX = 0;
    blockZ = 0;
    for (s32 i = 0; i < 2; i++) {
        layers[i] = 0;
    }
}

void MapBlock::init(s32 a, VecFx32 *v, u16 *layer0, u16 *layer1, u16 *buriedMask, BgAcreModel *k2, void *bcl, s32 k4,
                    s32 k5, u32 mapSlot) {
    acreId = a;
    pos.x = v->x;
    pos.y = v->y;
    pos.z = v->z;
    layers[0] = layer0;
    layers[1] = layer1;
    buried = buriedMask;
    blockX = k4;
    blockZ = k5;
    bindBg(k2, bcl, mapSlot);
}

extern "C" void MapBlock_Init(MapBlock *self, s32 a, VecFx32 *v, u16 *layer0, u16 *layer1, u16 *buriedMask, BgAcreModel *k2,
                              void *bcl, Unk_02037638_S8 *k45, u32 mapSlot) {
    VecFx32 t;
    t.x = v->x;
    t.y = v->y;
    t.z = v->z;
    self->init(a, &t, layer0, layer1, buriedMask, k2, bcl, k45->a, k45->b, mapSlot);
}

void MapBlock::bindBg(BgAcreModel *s, void *bcl, u32 mapSlot) {
    bgModel = s;
    if (bgModel != 0) {
        bcl = bgModel->bcl;
    }
    if (bcl != 0) {
        CollisionMap_SetBlock(blockX, blockZ, bcl, mapSlot);
    }
}

extern "C" MapBlock *MapBlock_NewArray(s32 n, void *heap, s32 x) {
    MapBlock *p = (MapBlock *)Heap_AllocAligned(static_cast<Heap *>(heap), n * sizeof(MapBlock), x);
    if (p != 0) {
        s32 i;
        for (i = 0; i < n; i++) {
            MapBlock *o = p + i;
            if (o != 0) {
                o->clear();
            }
        }
    }
    return p;
}

u8 *MapBlockAcre::getUnk04() { return (u8 *)&reinterpret_cast<MapBlock *>(this)->blockX; }

void MapBlockAcre::setAcreId(u32 v) { acreId = v; }

u32 MapBlockAcre::getAcreId() { return acreId; }

s32 MapBlockAcre::hasPond() {
    return Acre_HasPond(getAcreId());
}

extern "C" BOOL MapBlock_SetItem(void *cell, u16 *t, u32 x, u32 y, u8 z) {
    u16 *p = MapBlock_GetItemPtr(cell, x, y, z);
    BOOL r = FALSE;
    if (p != 0) {
        *p = *t;
        r = TRUE;
    }
    return r;
}

#pragma thumb off
extern "C" u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z) {
    u16 *r = 0;
    if (z < 2 && x < 0x10 && y < 0x10) {
        u16 *t = ((MapBlock *)cell)->layers[z];
        if (t != 0) {
            r = t + (x + y * 16);
        }
    }
    return r;
}
#pragma thumb reset

extern "C" BOOL MapBlock_FindItemInRange(void *cell, s32 *a, s32 *b, Marker1 *m, Marker1 *c, u8 d) {
    u16 *p = MapBlock_GetItemPtr(cell, 0, 0, d);
    BOOL found = FALSE;
    if (p != 0) {
        s32 i;
        for (i = 0; i < 0x100; i++) {
            if (Unk_020374f4_Range(p, m->v, c->v)) {
                Unit_SplitIndex(a, b, i);
                found = TRUE;
                break;
            }
            p++;
        }
    }
    return found;
}

extern "C" u32 MapBlock_GetAttr(MapBlock *o) {
    return Acre_GetAttr(o->acreId);
}

extern "C" BOOL MapBlock_HasAllAttr(MapBlock *o, u32 mask) {
    u32 m = mask & MapBlock_GetAttr(o);
    if (mask == m) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MapBlock_HasAnyAttr(MapBlock *o, u32 mask) {
    if ((mask & MapBlock_GetAttr(o)) != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL BuriedMask_Set(void *base, u32 a, u32 b);
extern "C" BOOL BuriedMask_Clear(void *base, u32 a, u32 b);

extern "C" BOOL MapBlock_SetBuried(MapBlock *o, u32 a, u32 b) {
    BOOL r = FALSE;
    if (o->buried != 0) {
        r = BuriedMask_Set(o->buried, a, b);
    }
    return r;
}

extern "C" BOOL MapBlock_ClearBuried(MapBlock *o, u32 a, u32 b) {
    BOOL r = FALSE;
    if (o->buried != 0) {
        r = BuriedMask_Clear(o->buried, a, b);
    }
    return r;
}

extern "C" void Unit_SplitIndex(s32 *a, s32 *b, s32 v) {
    *a = v & 0xf;
    *b = (v >> 4) & 0xf;
}

extern "C" void BuriedMask_Construct() {}

extern "C" void BuriedMask_Destruct() {}

extern "C" void BuriedMask_Reset(void *p) {
    MI_CpuFill8(p, 0, 0x20);
}

extern "C" BOOL Bits16_Set(void *, u16 *p, s32 bit) {
    BOOL r = FALSE;
    if (bit >= 0 && bit < 0x10) {
        *p |= (1 << bit);
        r = TRUE;
    }
    return r;
}

extern "C" BOOL Bits16_Clear(void *, u16 *p, s32 bit) {
    BOOL r = FALSE;
    if (bit >= 0 && bit < 0x10) {
        *p &= ~(1 << bit);
        r = TRUE;
    }
    return r;
}

extern "C" BOOL BuriedMask_Set(void *base, u32 a, u32 b) {
    BOOL r = FALSE;
    if (a < 0x10 && b < 0x10) {
        r = Bits16_Set(base, (u16 *)base + b, a);
    }
    return r;
}

extern "C" BOOL BuriedMask_Clear(void *base, u32 a, u32 b) {
    BOOL r = FALSE;
    if (a < 0x10 && b < 0x10) {
        r = Bits16_Clear(base, (u16 *)base + b, a);
    }
    return r;
}

extern "C" BOOL AcreAttr_Load() {
    sAcreAttrData = (u8 *)File_LoadAlloc("/bg/bkattr.bin", gCurrentHeap, 4, &sAcreAttrSize);
    return TRUE;
}

extern "C" BOOL AcreAttr_Unload() {
    Mem_Free(sAcreAttrData);
    sAcreAttrData = 0;
    return TRUE;
}

extern "C" u32 AcreAttr_GetType(u32 i) {
    if (i < sAcreAttrSize) {
        return sAcreAttrData[i];
    }
    return 0;
}

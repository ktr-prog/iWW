#include "types.h"
#include "net/CommManager.h"
#include "sys/StackPad.h"
#include "actor/CharaClothTexRef.h"
#include "item/ItemId.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205c91c.h"
#include "proto/main/unk_02082d74.h"



struct CharaClothTexPool;

extern "C" {
extern CommManager *gCommManager;

BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
u32 Scene_GetCurrent();
u32 Scene_GetMaxPlayers(u32 a);
u32 Scene_GetMaxCharacters(u32 a);
void MI_CpuCopy8(void *dst, void *src, u32 n);
}


struct CharaClothTexPool {
    void *ptr[10];
    ItemId id[10];
    CharaClothTexRef sub;
    CharaClothTexPool();
    ~CharaClothTexPool();
    s32 findItem(u16 *s);
    void setItem(u32 idx, u16 *s);
    CharaClothTexRef *getOwnRef();
    void *getBuffer(u32 idx);
    void freeBuffers();
    void allocBuffers();
};

extern "C" void CharaClothTexPool_Create(Heap *parent) {
    CharaClothTexHeap_Create(parent);
    sCharaClothTexPool.allocBuffers();
    if (gCharaClothTexHeap) static_cast<Heap *>(gCharaClothTexHeap)->adjust();
}

extern "C" void CharaClothTexPool_Destroy() {
    sCharaClothTexPool.freeBuffers();
    CharaClothTexHeap_Destroy();
}

extern "C" CharaClothTexRef *CharaClothTexPool_GetOwnRef() { return sCharaClothTexPool.getOwnRef(); }

CharaClothTexPool::CharaClothTexPool() {
    for (s32 i = 0; i < 10; i++) id[i].id = 0xfff1;
}

CharaClothTexPool::~CharaClothTexPool() {}

void CharaClothTexPool::allocBuffers() {
    Heap *heap = static_cast<Heap *>(gCharaClothTexHeap);
    u32 n = gCommManager->memberCount;
    u32 m = Scene_GetMaxPlayers(Scene_GetCurrent());
    u32 i;
    if (n < m) m = n;
    for (i = 0; i < m; i++) {
        ptr[i] = Heap_AllocAligned(heap, ClothTex_GetBufferSize(), 4);
    }
    ptr[4] = Heap_AllocAligned(heap, ClothTex_GetBufferSize(), 4);
    if (m == 0) m = 1;
    u32 q = Scene_GetMaxCharacters(Scene_GetCurrent());
    m = (q + NpcSpawn_GetSpNpcSlotCount()) - m;
    for (i = 5; i < m + 5; i++) {
        ptr[i] = Heap_AllocAligned(heap, ClothTex_GetBufferSize(), 4);
    }
    sub.assign(4);
}

void CharaClothTexPool::freeBuffers() {
    StackPad8 pad;
    sub.release();
    for (s32 i = 0; i < 10; i++) {
        ptr[i] = NULL;
        id[i].id = 0xfff1;
    }
    if (gCharaClothTexHeap) static_cast<Heap *>(gCharaClothTexHeap)->freeAll();
}

void *CharaClothTexPool::getBuffer(u32 idx) { return ptr[idx]; }

CharaClothTexRef *CharaClothTexPool::getOwnRef() { return &sub; }

extern "C" void CharaClothTexPool_GetItem(u16 *out, CharaClothTexPool *t, u32 idx) { *out = t->id[idx].id; }

void CharaClothTexPool::setItem(u32 idx, u16 *s) { id[idx].id = *s; }

s32 CharaClothTexPool::findItem(u16 *s) {
    u16 *p;
    BOOL z1 = FALSE, z2 = FALSE;
    for (s32 i = 0; i < 10; i++) {
        BOOL r;
        p = &id[i].id;
        if (Item_IsFurniture(p)) {
            r = (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(s)) ? TRUE : z1;
        } else {
            u16 a = id[i].id;
            r = (a == *s) ? TRUE : z2;
        }
        if (r) return i;
    }
    return 10;
}

CharaClothTexRef::CharaClothTexRef() { v = 10; }

CharaClothTexRef::~CharaClothTexRef() {}

void CharaClothTexRef::assign(u32 x) {
    setSlot(x);
    u16 s = 0xfff1;
    loadItem(&s, 0, 0, 0);
}

void CharaClothTexRef::release() { v = 10; }
void CharaClothTexRef::setSlot(u32 x) { v = x; }

void CharaClothTexRef::loadItem(u16 *s, void *a, s32 b, s32 c) {
    u32 st = v;
    BOOL r4, r2, r1;
    if (*s == 0xfff1) {
        sCharaClothTexPool.setItem(st, s);
    }
    r4 = TRUE;
    r2 = TRUE;
    r1 = FALSE;
    u32 h = *s;
    if (h >= 0x12a8 && h <= 0x12af) r1 = TRUE;
    if (!r1) {
        if (h < 0x1429 || h > 0x1430) r2 = FALSE;
    }
    if (!r2) {
        if (h < 0x13a0 || h > 0x13a7) r4 = FALSE;
    }
    if (c == 0 && !r4) {
        u16 tmp;
        BOOL eq;
        CharaClothTexPool_GetItem(&tmp, &sCharaClothTexPool, st);
        if (Item_IsFurniture(s)) {
            s32 t = Item_GetFurnitureIndex(s);
            if (t == Item_GetFurnitureIndex(&tmp)) eq = TRUE; else eq = FALSE;
        } else {
            if (*s == tmp) eq = TRUE; else eq = FALSE;
        }
        if (eq) return;
    }
    if (b != 0 && !r4) {
        s32 idx = sCharaClothTexPool.findItem(s);
        if (idx != 10) {
            CharaClothTexRef_CopyFromSlot(this, idx);
            return;
        }
    }
    if (ClothTex_LoadItemThunk(sCharaClothTexPool.getBuffer(st), s, a)) {
        sCharaClothTexPool.setItem(st, s);
    }
}

extern "C" void CharaClothTexRef_LoadPattern(u8 *p, void *q) {
    u32 cur = *p;
    if (ClothTex_LoadPatternThunk(sCharaClothTexPool.getBuffer(cur), q)) {
        static ItemId dflt(0xffff);
        sCharaClothTexPool.setItem(cur, &dflt.id);
    }
}

extern "C" void CharaClothTexRef_CopyFromSlot(void *pp, s32 x) {
    u8 *p = (u8 *)pp;
    u32 cur = *p;
    if (x != cur) {
        u16 v[2];
        CharaClothTexPool_GetItem(&v[0], &sCharaClothTexPool, x);
        CharaClothTexPool_GetItem(&v[1], &sCharaClothTexPool, cur);
        BOOL ok = FALSE;
        volatile u16 *pv = v;
        u16 a = *pv;
        u16 b = *pv;
        if (b >= 0x12a8 && a <= 0x12af) ok = TRUE;
        if (ok) {
            BOOL ok2;
            if (a >= 0x1429 && a <= 0x1430) ok2 = TRUE; else ok2 = FALSE;
            if (ok2) {
                BOOL ok3;
                if (a >= 0x13a0 && a <= 0x13a7) ok3 = TRUE; else ok3 = FALSE;
                if (ok3) goto copy;
            }
        }
        {
            BOOL eq;
            if (Item_IsFurniture(v)) {
                s32 q = Item_GetFurnitureIndex(v);
                if (q == Item_GetFurnitureIndex(&v[1])) eq = TRUE; else eq = FALSE;
            } else {
                if (v[0] == v[1]) eq = TRUE; else eq = FALSE;
            }
            if (eq) return;
        }
    copy:
        void *pa = sCharaClothTexPool.getBuffer(x);
        void *pb = sCharaClothTexPool.getBuffer(cur);
        if (pa != 0 && pb != 0) {
            MI_CpuCopy8(pa, pb, ClothTex_GetBufferSize());
            sCharaClothTexPool.setItem(cur, v);
        }
    }
}

extern "C" void *CharaClothTexRef_GetBuffer(u8 *p) { return sCharaClothTexPool.getBuffer(*p); }

CharaClothTexPool sCharaClothTexPool;

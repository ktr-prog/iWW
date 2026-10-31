#include "sys/Heap.h"
#include "types.h"
#include "net/CommManager.h"
#include "sys/PrioListNode.h"
#include "room/Unk_0209c41c_Actor.h"
#include "gfx/TexVramSlot.h"
#include "town/TownAcreIndex.h"
#include "gfx/ModelSlotPool.h"
#include "gfx/TexTransfer.h"
#include "sys/RecordFile.h"
#include "town/TownAcreCell.h"
#include "gfx/VramTask.h"
#include "town/TownAcreGrid.h"
#include "gfx/TexVramTask.h"
#include "gfx/ModelResource.h"
#include "gfx/PooledModel.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0209c08c.h"


class SavedFadeIn {
public:
    SavedFadeIn();
    ~SavedFadeIn();
    u8 fadeIn;
};

SavedFadeIn sSavedFadeIn;


extern "C" void ModelSlotHandle_Init(u16 *p) {
    *p = 0xffff;
}

extern "C" void ModelSlotHandle_Destroy(u16 *p) {
    *p = 0xffff;
}

ModelSlot::ModelSlot() {
    inUse = 0;
    heap = 0;
}

Heap *ModelSlot::getHeap() {
    return heap;
}

TexVramSlot *ModelSlot::getVramSlot() {
    return &vramSlot;
}


BOOL ModelSlot::init(u32 texSize, u32 plttSize, u32 heapSize, Heap *parent) {
    if (heapSize) {
        heap = (Heap *)FrameHeap_Create((heapSize + 3) & ~3, parent);
    }
    if (texSize != 0 || plttSize != 0) {
        if (vramSlot.alloc(texSize, 0, plttSize)) return TRUE;
        return FALSE;
    }
    return TRUE;
}

BOOL ModelSlot::clear() {
    inUse = 0;
    heap = 0;
    return TRUE;
}

ModelSlotPool::ModelSlotPool() {
    allocFunc = 0;
    freeFunc = 0;
    slots = 0;
    numSlots = 0;
    numInUse = 0;
    lastFreed = 0xffff;
}

ModelSlotPool::~ModelSlotPool() {}

ModelSlot *ModelSlotPool::acquire(u16 *idx) {
    u32 i = *idx;
    if (i == 0xffff) {
        ModelSlot *e;
        u16 k;
        u32 n;
        ModelSlot *arr;
        arr = slots;
        e = arr;
        k = 0;
        n = numSlots;
        for (; k < n; e++, k++) {
            if (e->inUse == 0 && k != lastFreed) {
                e->inUse = 1;
                *idx = k;
                numInUse++;
                return e;
            }
        }
        u32 h = lastFreed;
        ModelSlot *r = &arr[h];
        if (arr[h].inUse == 0) {
            r->inUse = 1;
            *idx = lastFreed;
            numInUse++;
            return r;
        }
    } else {
        if (i < numSlots) return &slots[i];
        *idx = 0xffff;
    }
    return 0;
}

void ModelSlotPool::release(u16 *idx) {
    u32 i = *idx;
    if (i != 0xffff) {
        ModelSlot *arr = slots;
        ModelSlot *e = &arr[i];
        arr[i].inUse = 0;
        lastFreed = *idx;
        *idx = 0xffff;
        if (e->heap) e->heap->freeAll();
        numInUse--;
    }
}

BOOL ModelSlotPool::init(u32 n, u32 texSize, u32 plttSize, u32 size, ModelSlotAllocFunc alloc, ModelSlotFreeFunc free) {
    Heap *mem;
    allocFunc = alloc;
    freeFunc = free;
    u32 total = n * ((size + MODELSLOT_HEAP_OVERHEAD) & ~3);
    numSlots = n;
    mem = 0;
    numInUse = 0;
    if (size) mem = allocFunc(total, 0);
    slots = (ModelSlot *)Mem_Alloc(numSlots * sizeof(ModelSlot));
    ModelSlot *e = slots;
    if (e) {
        u32 i;
        for (i = 0; i < numSlots; i++) {
            e = new (e) ModelSlot;
            if (!e->init(texSize, plttSize, size, mem)) return FALSE;
            e++;
        }
    }
    return TRUE;
}

BOOL ModelSlotPool::destroy() {
    ModelSlot *e = slots;
    if (e != 0) {
        u32 i;
        for (i = 0; i < numSlots; i++) {
            e->clear();
            e++;
        }
        Mem_Free(slots);
    }
    if (freeFunc) freeFunc();
    allocFunc = 0;
    freeFunc = 0;
    numSlots = 0;
    numInUse = 0;
    lastFreed = 0xffff;
    slots = 0;
    return TRUE;
}

PooledModel::PooledModel() {
    isLoaded = 0;
    slot = 0;
}

PooledModel::~PooledModel() {
    unload();
}

s32 PooledModel::loadFromSlot(ModelSlot *e, const char *name) {
    if (slot == 0) slot = e;
    if (isLoaded == 0) {
        TexVramSlot *r = e->getVramSlot();
        void *t = e->getHeap();
        if (resource.loadModel((void *)name, r, t, gCurrentHeap) == 3) isLoaded = 1;
    }
    return isLoaded;
}

void PooledModel::reset() {
    unload();
}

void PooledModel::unload() {
    isLoaded = 0;
    slot = 0;
    unk_3c = 0;
    resource.release();
}

void *PooledModel::getModel() {
    return resource.getModel();
}

SavedFadeIn::SavedFadeIn() {}

SavedFadeIn::~SavedFadeIn() {}

extern "C" void Scene_SaveFadeIn(u32 v) {
    sSavedFadeIn.fadeIn = v;
}

extern "C" u32 Scene_GetSavedFadeIn() {
    return sSavedFadeIn.fadeIn;
}



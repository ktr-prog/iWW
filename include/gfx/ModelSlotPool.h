#ifndef GFX_MODELSLOTPOOL_H
#define GFX_MODELSLOTPOOL_H

#include "types.h"
#include "gfx/TexVramSlot.h"

class Heap;

class ModelSlot {
public:
    ModelSlot();
    BOOL clear();
    BOOL init(u32 texSize, u32 plttSize, u32 heapSize, Heap *parent);
    TexVramSlot *getVramSlot();
    Heap *getHeap();

    /* 0x00 */ u8 inUse;
    /* 0x04 */ Heap *heap;
    /* 0x08 */ TexVramSlot vramSlot;
};

typedef void (*ModelSlotFreeFunc)();
typedef Heap *(*ModelSlotAllocFunc)(u32 size, Heap *parent);

extern "C" void ModelSlotHandle_Init(u16 *p);
extern "C" void ModelSlotHandle_Destroy(u16 *p);
class ModelSlotHandle {
public:
    ModelSlotHandle() { ModelSlotHandle_Init(&index); }
    ~ModelSlotHandle() { ModelSlotHandle_Destroy(&index); }
    /* 0x0 */ u16 index;
};

class ModelSlotPool {
public:
    ModelSlotPool();
    ~ModelSlotPool();
    BOOL destroy();
    BOOL init(u32 n, u32 texSize, u32 plttSize, u32 size, ModelSlotAllocFunc alloc, ModelSlotFreeFunc free);
    void release(u16 *idx);
    ModelSlot *acquire(u16 *idx);

    /* 0x00 */ u16 lastFreed;
    /* 0x04 */ u32 numSlots;
    /* 0x08 */ u32 numInUse;
    /* 0x0c */ ModelSlot *slots;
    /* 0x10 */ ModelSlotAllocFunc allocFunc;
    /* 0x14 */ ModelSlotFreeFunc freeFunc;
};

#endif

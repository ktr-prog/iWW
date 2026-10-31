#ifndef SYS_HEAP_H
#define SYS_HEAP_H

#include "types.h"

class Heap {
public:
    Heap(void *start, u32 size, Heap *parent);
    virtual ~Heap();
    virtual void doLock();
    virtual void doUnlock();
    virtual BOOL tryLock();
    virtual void doDestroy() = 0;
    virtual void *doAlloc(u32 size, s32 align) = 0;
    virtual void doFree(void *p) = 0;
    virtual void doFreeAll() = 0;
    virtual BOOL vfunc_24() = 0;
    virtual void doDump() = 0;
    virtual s32 doResize(void *p, u32 size) = 0;
    virtual u32 vfunc_30(void *p) = 0;
    virtual u32 doGetFreeSize() = 0;
    virtual u32 doGetMaxFreeBlockSize() = 0;
    virtual u32 vfunc_3c(s32 align) = 0;
    virtual u32 getTotalFreeSize() = 0;
    virtual u16 changeGroupId(u16 id) = 0;
    virtual u16 getGroupId() = 0;
    virtual u32 doAdjust() = 0;

    void lock();
    void unlock();
    void destroy();
    void destroy2();
    void *alloc(u32 size, s32 align);
    void dump();
    u32 getFreeSize();
    u32 getMaxFreeBlockSize();
    u32 maxAlloc(s32 align);
    s32 resize(void *p, u32 size);
    void free(void *p);
    void freeAll();
    u32 adjust();
    u32 setFlags(u32 flags);

    /* 0x04 */ void *regionStart;
    /* 0x08 */ u32 regionSize;
    /* 0x0c */ Heap *parentHeap;
    /* 0x10 */ u32 heapFlags;
    /* 0x14 */ void *heapHandle;
};

#define FRAMEHEAP_OVERHEAD_ROUNDED (0x4b * 2)

#define MODELSLOT_HEAP_OVERHEAD (0x5b * 2)

#endif

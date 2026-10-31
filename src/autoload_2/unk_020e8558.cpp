#include "uptr.h"
#include "types.h"
#include "sys/Heap.h"
#include "sys/OSThread.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/main/unk_0206d49c.h"

#ifdef HOST64
#define NNS_EXPHEAP_OVERHEAD (0x4c * 2)
#define NNS_FRMHEAP_OVERHEAD (0x30 * 2)
#else
#define NNS_EXPHEAP_OVERHEAD 0x4c
#define NNS_FRMHEAP_OVERHEAD 0x30
#endif




class FrameHeap : public Heap {
public:
    FrameHeap(void *block, u32 size, Heap *parent, void *handle);
    virtual ~FrameHeap();
    virtual void doDestroy();
    virtual void *doAlloc(u32 size, s32 align);
    virtual void doFree(void *p);
    virtual void doFreeAll();
    virtual BOOL vfunc_24();
    virtual void doDump();
    virtual s32 doResize(void *p, u32 size);
    virtual u32 vfunc_30(void *p);
    virtual u32 doGetFreeSize();
    virtual u32 doGetMaxFreeBlockSize();
    virtual u32 vfunc_3c(s32 align);
    virtual u32 getTotalFreeSize();
    virtual u16 changeGroupId(u16 id);
    virtual u16 getGroupId();
    virtual u32 doAdjust();
};

class ExpHeap : public Heap {
public:
    ExpHeap(void *block, u32 size, Heap *parent, void *handle);
    virtual ~ExpHeap();
    virtual void doLock();
    virtual void doUnlock();
    virtual BOOL tryLock();
    virtual void doDestroy();
    virtual void *doAlloc(u32 size, s32 align);
    virtual void doFree(void *p);
    virtual void doFreeAll();
    virtual BOOL vfunc_24();
    virtual void doDump();
    virtual s32 doResize(void *p, u32 size);
    virtual u32 vfunc_30(void *p);
    virtual u32 doGetFreeSize();
    virtual u32 doGetMaxFreeBlockSize();
    virtual u32 vfunc_3c(s32 align);
    virtual u32 getTotalFreeSize();
    virtual u16 changeGroupId(u16 id);
    virtual u16 getGroupId();
    virtual u32 doAdjust();

    /* 0x18 */ OSMutex mutex;
};

typedef void (*HeapFreeHook)(Heap *heap, void *p);
typedef void (*HeapAllocHook)(Heap *heap, void *p, u32 size, s32 align);
typedef void (*ThreadHook)(void *, void *);

extern "C" {
u32 OS_DisableInterrupts(void);
u32 OS_RestoreInterrupts(u32);
u32 OS_GetProcMode(void);
u32 NNS_FndAdjustFrmHeap(void *heap);
u16 NNS_FndGetGroupIDForExpHeap(void *heap);
u16 NNS_FndSetGroupIDForExpHeap(void *heap, u16 id);
u32 NNS_FndGetSizeForMBlockExpHeap(void *p);
u32 NNS_FndFreeToFrmHeap(void *heap, s32);
void NNS_FndVisitAllocatedForExpHeap(void *heap, void (*visitor)(void *block, void *heap, u32 param), u32 param);
void NNS_FndFreeToExpHeap(void *heap, void *p);
u32 NNS_FndResizeForMBlockFrmHeap(void *heap, void *mem, u32 size);
s32 NNS_FndResizeForMBlockExpHeap(void *heap, void *p, u32 size);
u32 NNS_FndGetAllocatableSizeForFrmHeapEx(void *heap, s32 align);
u32 NNS_FndGetTotalFreeSizeForExpHeap(void *heap);
u32 NNS_FndGetAllocatableSizeForExpHeapEx(void *heap, s32 align);
void *NNS_FndAllocFromFrmHeapEx(void *heap, u32 size, s32 align);
void *NNS_FndAllocFromExpHeapEx(void *heap, u32 size, s32 align);
void NNS_FndDestroyFrmHeap(void *heap);
void NNS_FndDestroyExpHeap(void *heap);
void *NNS_FndCreateFrmHeapEx(void *p, u32 size, u32 opt);
void *NNS_FndCreateExpHeapEx(void *p, u32 size, u32 opt);
BOOL OS_TryLockMutex(void *p);
void *OS_GetArenaLo(s32 id);
void *OS_GetArenaHi(s32 id);
void *OS_AllocFromArenaLo(s32 id, u32 size, u32 align);
ThreadHook OS_SetSwitchThreadCallback(ThreadHook);
void OS_SetThreadParameter(void *thread, void *v);
void *OS_GetThreadParameter(void *thread);

extern OSThreadInfo data_021fcc2c;

}

u32 sRootHeapSize;
u8 sHeapSystemReady;
HeapAllocHook sHeapAllocHook;
u32 sRootHeapArenaId;
Heap *gCurrentHeap;
u16 gHeapCreateOption = 3;
Heap *sSavedCurrentHeap[16];
ThreadHook sPrevThreadSwitchCallback;
HeapFreeHook sHeapFreeHook;
Heap *gProcHeap;
Heap *gRootHeap;


#ifdef HOST64
extern "C" void Heap_HostTrace(Heap *h, HeapAllocHook a, HeapFreeHook f) {
    sHeapAllocHook = a;
    sHeapFreeHook = f;
    if (h != NULL) h->heapFlags |= 0xc00;
}
extern "C" void Heap_HostFreeSpace(Heap *h, u32 *all, u32 *largest) {
    *all = h->getFreeSize();
    *largest = h->getMaxFreeBlockSize();
}
extern "C" void *Heap_HostHandle(Heap *h) { return h->heapHandle; }
#endif

extern "C" void Heap_OnThreadSwitch(void *a, void *b) {
    OS_SetThreadParameter(a, gCurrentHeap);
    gCurrentHeap = (Heap *)OS_GetThreadParameter(b);
    OS_SetThreadParameter(b, NULL);
    if (sPrevThreadSwitchCallback != NULL) sPrevThreadSwitchCallback(a, b);
}


extern "C" void Heap_SetThreadHeap(void *thread, Heap *heap) {
    if (thread == data_021fcc2c.current) {
        Heap_SetCurrent(heap);
        return;
    }
    OS_SetThreadParameter(thread, heap);
}

extern "C" void Heap_InstallThreadSwitchCallback(void) {
    u32 e = OS_DisableInterrupts();
    sPrevThreadSwitchCallback = OS_SetSwitchThreadCallback(Heap_OnThreadSwitch);
    OS_RestoreInterrupts(e);
}


extern "C" ExpHeap *Heap_CreateRootHeap(void *p, u32 n) {
    ExpHeap *h = ExpHeap_CreateInPlace(p, n);
    if (h != NULL) {
        gRootHeap = h;
        gCurrentHeap = h;
    }
    sHeapSystemReady = 1;
    return h;
}

#ifdef HOST64
extern "C" void *host_root_heap_region(unsigned int *size);
#endif

extern "C" void Heap_InitSystem(void) {
    u32 size;
    u32 t;
    sRootHeapArenaId = 0;
    t = *(s32 *)&sRootHeapSize;
    size = sRootHeapSize;
    if (t == 0) {
        uptr lo = (uptr)OS_GetArenaLo(0);
        size = (uptr)OS_GetArenaHi(sRootHeapArenaId) - ((lo + 31) & ~(uptr)31);
    }
#ifdef HOST64
    {
        unsigned int hs;
        void *p = host_root_heap_region(&hs);
        if (p != NULL) {
            if (Heap_CreateRootHeap(p, hs) != NULL) Heap_InstallThreadSwitchCallback();
            return;
        }
    }
#endif
    if (Heap_CreateRootHeap(OS_AllocFromArenaLo(sRootHeapArenaId, size, 32), size) != NULL) Heap_InstallThreadSwitchCallback();
}

Heap::Heap(void *start, u32 size, Heap *parent) {
    regionStart = start;
    regionSize = size;
    parentHeap = parent;
    heapFlags = 0;
    heapFlags = 0x4000;
}

ExpHeap::ExpHeap(void *block, u32 size, Heap *parent, void *handle)
    : Heap(block, size, parent) {
    heapHandle = handle;
    OS_InitMutex(&mutex);
}

FrameHeap::FrameHeap(void *block, u32 size, Heap *parent, void *handle)
    : Heap(block, size, parent) {
    heapHandle = handle;
}

Heap::~Heap() {
}

ExpHeap::~ExpHeap() {
}

FrameHeap::~FrameHeap() {
}

extern "C" ExpHeap *ExpHeap_CreateInPlace(void *p, u32 n) {
    u32 region = n - sizeof(ExpHeap);
    void *q = (u8 *)p + sizeof(ExpHeap);
    void *h = NNS_FndCreateExpHeapEx(q, region, gHeapCreateOption);
    if (h != NULL) {
        new (p) ExpHeap(q, region, NULL, h);
        return (ExpHeap *)p;
    }
    return NULL;
}

extern "C" ExpHeap *ExpHeap_Create(u32 size, Heap *parent) {
    u32 region;
    u32 total;
    ExpHeap *p;
    void *q;
    void *h;
    if (parent == NULL) parent = gCurrentHeap;
    if (size == 0xffffffff) {
        total = parent->maxAlloc(4);
        if (total < sizeof(ExpHeap) + NNS_EXPHEAP_OVERHEAD) return NULL;
        region = total - sizeof(ExpHeap);
    } else {
#ifdef HOST64
        size *= 2;
#endif
        region = ((size + 3) & ~3) + NNS_EXPHEAP_OVERHEAD;
        total = region + sizeof(ExpHeap);
    }
    p = (ExpHeap *)parent->alloc(total, 4);
    if (p != NULL) {
        q = (u8 *)p + sizeof(ExpHeap);
        h = NNS_FndCreateExpHeapEx(q, region, gHeapCreateOption);
        if (h == NULL) {
            parent->free(p);
            p = NULL;
        } else {
            new (p) ExpHeap(q, region, parent, h);
        }
    }
    return p;
}

extern "C" FrameHeap *FrameHeap_Create(u32 size, Heap *parent) {
    u32 region;
    u32 total;
    FrameHeap *p;
    void *q;
    void *h;
    if (parent == NULL) parent = gCurrentHeap;
    if (size == 0xffffffff) {
        total = parent->maxAlloc(4);
        if (total < sizeof(FrameHeap) + NNS_FRMHEAP_OVERHEAD) return NULL;
        region = total - sizeof(FrameHeap);
    } else {
#ifdef HOST64
        size *= 2;
#endif
        region = ((size + 3) & ~3) + NNS_FRMHEAP_OVERHEAD;
        total = region + sizeof(FrameHeap);
    }
    p = (FrameHeap *)parent->alloc(total, 4);
    if (p != NULL) {
        q = (u8 *)p + sizeof(FrameHeap);
        h = NNS_FndCreateFrmHeapEx(q, region, gHeapCreateOption);
        if (h == NULL) {
            parent->free(p);
            p = NULL;
        } else {
            new (p) FrameHeap(q, region, parent, h);
        }
    }
    return p;
}

void Heap::lock() {
    if (OS_GetProcMode() != 31 && (heapFlags & 0x2000) == 0) Fatal_Trap();
    doLock();
}

void Heap::unlock() {
    doUnlock();
}

void Heap::doLock() {
}

void Heap::doUnlock() {
}

BOOL Heap::tryLock() {
    return TRUE;
}

void ExpHeap::doLock() {
    OS_LockMutex(&mutex);
}

void ExpHeap::doUnlock() {
    OS_UnlockMutex(&mutex);
}

BOOL ExpHeap::tryLock() {
    return OS_TryLockMutex(&mutex);
}

void Heap::destroy() {
    Heap *parent;
    lock();
    doDestroy();
    regionStart = NULL;
    regionSize = 0;
    unlock();
    parent = parentHeap;
    this->~Heap();
    if (parent != NULL) parent->free(this);
}

void Heap::destroy2() {
    destroy();
}

void ExpHeap::doDestroy() {
    NNS_FndDestroyExpHeap(heapHandle);
    heapHandle = NULL;
}

void FrameHeap::doDestroy() {
    NNS_FndDestroyFrmHeap(heapHandle);
    heapHandle = NULL;
}

void *Heap::alloc(u32 size, s32 align) {
    void *p;
    lock();
    if (size == 0xffffffff) size = maxAlloc(align);
    p = doAlloc(size, align);
    if (sHeapAllocHook != NULL && (heapFlags & 0x400)) sHeapAllocHook(this, p, size, align);
    if (p == NULL && (heapFlags & 0x4000)) Fatal_Trap();
    unlock();
    return p;
}

void *ExpHeap::doAlloc(u32 size, s32 align) {
    return NNS_FndAllocFromExpHeapEx(heapHandle, size, align);
}

void *FrameHeap::doAlloc(u32 size, s32 align) {
    return NNS_FndAllocFromFrmHeapEx(heapHandle, size, align);
}

BOOL ExpHeap::vfunc_24() {
    return TRUE;
}

BOOL FrameHeap::vfunc_24() {
    return TRUE;
}

void Heap::dump() {
    lock();
    doDump();
    unlock();
}

void ExpHeap::doDump() {
}

void FrameHeap::doDump() {
}

u32 Heap::getFreeSize() {
    u32 r;
    lock();
    r = doGetFreeSize();
    unlock();
    return r;
}

u32 ExpHeap::doGetFreeSize() {
    return NNS_FndGetAllocatableSizeForExpHeapEx(heapHandle, 4);
}

u32 FrameHeap::doGetFreeSize() {
    return NNS_FndGetAllocatableSizeForFrmHeapEx(heapHandle, 4);
}

u32 Heap::getMaxFreeBlockSize() {
    u32 r;
    lock();
    r = doGetMaxFreeBlockSize();
    unlock();
    return r;
}

u32 ExpHeap::doGetMaxFreeBlockSize() {
    return NNS_FndGetAllocatableSizeForExpHeapEx(heapHandle, 4);
}

u32 FrameHeap::doGetMaxFreeBlockSize() {
    return NNS_FndGetAllocatableSizeForFrmHeapEx(heapHandle, 4);
}

u32 Heap::maxAlloc(s32 align) {
    u32 r;
    lock();
    r = vfunc_3c(align);
    unlock();
    return r;
}

u32 ExpHeap::vfunc_3c(s32 align) {
    return NNS_FndGetAllocatableSizeForExpHeapEx(heapHandle, align);
}

u32 FrameHeap::vfunc_3c(s32 align) {
    return NNS_FndGetAllocatableSizeForFrmHeapEx(heapHandle, align);
}

u32 ExpHeap::getTotalFreeSize() {
    return NNS_FndGetTotalFreeSizeForExpHeap(heapHandle);
}

u32 FrameHeap::getTotalFreeSize() {
    return NNS_FndGetAllocatableSizeForFrmHeapEx(heapHandle, 4);
}

s32 Heap::resize(void *p, u32 size) {
    s32 r;
    lock();
    r = doResize(p, size);
    unlock();
    return r;
}

s32 ExpHeap::doResize(void *p, u32 size) {
    return NNS_FndResizeForMBlockExpHeap(heapHandle, p, size);
}

s32 FrameHeap::doResize(void *p, u32 size) {
    return (s32)NNS_FndResizeForMBlockFrmHeap(heapHandle, p, size);
}

void Heap::free(void *p) {
    if (p == NULL) return;
    lock();
    if (sHeapFreeHook != NULL && (heapFlags & 0x800)) sHeapFreeHook(this, p);
    doFree(p);
    unlock();
}

void ExpHeap::doFree(void *p) {
    if (p == NULL) return;
    NNS_FndFreeToExpHeap(heapHandle, p);
}

void FrameHeap::doFree(void *p) {
    if (p == NULL) return;
    Fatal_Trap();
}

void Heap::freeAll() {
    lock();
    if (sHeapFreeHook != NULL && (heapFlags & 0x800)) sHeapFreeHook(this, NULL);
    doFreeAll();
    unlock();
}

extern "C" void ExpHeap_FreeBlockVisitor(void *block, void *heap, u32 param) {
    NNS_FndFreeToExpHeap(heap, block);
}

void ExpHeap::doFreeAll() {
    NNS_FndVisitAllocatedForExpHeap(heapHandle, ExpHeap_FreeBlockVisitor, 0);
}

void FrameHeap::doFreeAll() {
    NNS_FndFreeToFrmHeap(heapHandle, 3);
}

u32 ExpHeap::vfunc_30(void *p) {
    return NNS_FndGetSizeForMBlockExpHeap(p);
}

u32 FrameHeap::vfunc_30(void *p) {
    return (u32)-1;
}

u16 ExpHeap::changeGroupId(u16 id) {
    return NNS_FndSetGroupIDForExpHeap(heapHandle, id);
}

u16 FrameHeap::changeGroupId(u16 id) {
    return 0;
}

u16 ExpHeap::getGroupId() {
    return NNS_FndGetGroupIDForExpHeap(heapHandle);
}

u16 FrameHeap::getGroupId() {
    return 0;
}

u32 Heap::adjust() {
    u32 r;
    lock();
    r = doAdjust();
    if (r == 0 && (heapFlags & 0x4000)) Fatal_Trap();
    unlock();
    return r;
}

u32 ExpHeap::doAdjust() {
    return 0;
}

u32 FrameHeap::doAdjust() {
    u32 heapSize = NNS_FndAdjustFrmHeap(heapHandle);
    u32 total;
    if (heapSize == 0) return 0;
    total = heapSize + sizeof(FrameHeap);
    if (parentHeap->resize(this, total) < 0) return 0;
    regionSize = heapSize;
    return total;
}

u32 Heap::setFlags(u32 flags) {
    u32 irq = OS_DisableInterrupts();
    u32 old = heapFlags;
    if (!(flags & 0x8000)) heapFlags = flags;
    OS_RestoreInterrupts(irq);
    return old;
}

extern "C" Heap *Heap_SetCurrent(Heap *heap) {
    u32 irq = OS_DisableInterrupts();
    Heap *old = gCurrentHeap;
    gCurrentHeap = heap;
    OS_RestoreInterrupts(irq);
    return old;
}


extern "C" Heap *FrameHeap_CreateAsCurrent(u32 size, Heap *parent) {
    Heap *heap = FrameHeap_Create(size, parent);
    if (heap == NULL) return NULL;
    Heap_SaveCurrent();
    Heap_SetCurrent(heap);
    return heap;
}

extern "C" void Heap_SaveCurrent(void) {
    sSavedCurrentHeap[data_021fcc2c.current->id] = gCurrentHeap;
}

extern "C" void Heap_RestoreCurrent(void) {
    u32 id = data_021fcc2c.current->id;
    Heap_SetCurrent(sSavedCurrentHeap[id]);
    sSavedCurrentHeap[id] = NULL;
}

extern "C" void *Heap_AllocAligned(Heap *heap, u32 size, s32 align) {
    return heap->alloc(size, align);
}

extern "C" void *Heap_AllocTail(Heap *heap, u32 size) {
    return heap->alloc(size, -4);
}

extern "C" void *Heap_Alloc(Heap *heap, u32 size) {
    return heap->alloc(size, 4);
}

extern "C" void Heap_Free(Heap *heap, void *p) {
    heap->free(p);
}

extern "C" void Heap_CreateProcHeap(u32 size, Heap *parent) {
    gProcHeap = ExpHeap_Create(size, parent);
}

extern "C" void *Mem_AllocAligned(u32 size, s32 align) {
    return gCurrentHeap->alloc(size, align);
}

extern "C" void *Mem_AllocTail(u32 size) {
    return gCurrentHeap->alloc(size, -4);
}

extern "C" void *Mem_Alloc(u32 size) {
    return gCurrentHeap->alloc(size, 4);
}

extern "C" void Mem_Free(void *p) {
    gCurrentHeap->free(p);
}

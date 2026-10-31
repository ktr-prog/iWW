#include "proto/autoload_2/unk_02100d44.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_0210169c.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_0212703c.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
#include "uptr.h"
#include "host_asan.h"

typedef struct NNSFndLink { void *prev; void *next; } NNSFndLink;
typedef struct NNSFndList { void *head; void *tail; u16 num; u16 offset; } NNSFndList;
typedef struct Region { uptr start; uptr end; } Region;

typedef struct MBlock {
    u16 sig;
    union {
        u16 raw;
        struct { u16 groupID : 8; u16 alignment : 7; u16 allocDir : 1; } f;
    } attr;
    u32 size;
    struct MBlock *prev;
    struct MBlock *next;
} MBlock;

typedef struct FrmState { u32 tag; uptr head; uptr tail; struct FrmState *prev; } FrmState;

typedef struct FrmHead {
    uptr head;
    uptr tail;
    FrmState *state;
} FrmHead;

typedef struct HeapHead {
    u32 sig;
    NNSFndLink link;
    NNSFndList childList;
    uptr start;
    uptr end;
    union {
        u32 raw;
        struct { u32 optFlag : 8; u32 pad : 24; } f;
    } attr;
    union {
        struct {
            MBlock *freeHead, *freeTail;
            MBlock *usedHead, *usedTail;
            u16 groupID;
            union { u16 raw; struct { u16 allocMode : 1; u16 pad : 15; } f; } feature;
        } exp;
        FrmHead frm;
    } u;
} HeapHead;
typedef struct ExpHead {
    MBlock *freeHead, *freeTail;
    MBlock *usedHead, *usedTail;
    u16 groupID;
    union { u16 raw; struct { u16 allocMode : 1; u16 pad : 15; } f; } feature;
} ExpHead;

extern void MIi_CpuClear32(u32, void *, u32);
extern u32 data_021f5ca0;
extern NNSFndList data_021f5ca4;


#define HH(e) ((HeapHead *)((u8 *)(e) - __builtin_offsetof(HeapHead, u)))
#define EXP(h) ((ExpHead *)&(h)->u)

static inline u16 GetOptFlag(HeapHead *h) { return (u16)(h->attr.raw & 0xff); }
static inline u16 GetAllocMode(ExpHead *e) { return (u16)(e->feature.raw & 1); }
static inline void SetAllocDir(MBlock *b, u16 d) {
    b->attr.raw &= ~0x8000;
    b->attr.raw |= (d & 1) << 15;
}
static inline void SetAlignment(MBlock *b, u16 a) {
    b->attr.raw &= ~0x7f00;
    b->attr.raw |= (a & 0x7f) << 8;
}
static inline void SetGroupID(MBlock *b, u32 g) {
    b->attr.raw &= ~0xff;
    b->attr.raw |= (u8)g;
}
static inline void SetGroupIDFrom(MBlock *b, ExpHead *e) {
    b->attr.raw &= ~0xff;
    b->attr.raw |= e->groupID & 0xff;
}
static inline uptr GetMBlockEnd(MBlock *b) { return b->size + ((uptr)b + sizeof(MBlock)); }
static inline uptr RoundUp(uptr v, uptr a) { return (v + (a - 1)) & ~(a - 1); }
static inline void ClearMem(HeapHead *h, uptr dst, u32 size) {
    if (GetOptFlag(h) & 1) {
        volatile u32 zero = 0;
        MIi_CpuClear32(zero, (void *)dst, size);
    }
}

void NNSi_FndFinalizeHeap(HeapHead *heap);
NNSFndList *FindListContainHeap(HeapHead *heap);
HeapHead *FindContainHeap(NNSFndList *list, HeapHead *mem);
void NNS_FndInitList(NNSFndList *list, u16 offset);
void NNS_FndRemoveListObject(NNSFndList *list, void *obj);
void NNS_FndAppendListObject(NNSFndList *list, void *obj);
void *NNS_FndGetNextListObject(NNSFndList *list, void *obj);
MBlock *InitMBlock(Region *r, u16 sig);
MBlock *InsertMBlock(void *list, MBlock *blk, MBlock *prev);
MBlock *RemoveMBlock(void *list, MBlock *blk);
void GetRegionOfMBlock(Region *r, MBlock *blk);
BOOL RecycleRegion(ExpHead *e, Region *r);
void *AllocUsedBlockFromFreeBlock(ExpHead *e, MBlock *free, void *mblock, u32 size, u16 dir);
void *AllocFromHead__ExpHeap(HeapHead *h, u32 size, s32 alignment);
void *AllocFromTail__ExpHeap(HeapHead *h, u32 size, s32 alignment);
HeapHead *InitExpHeap(void *start, void *end, u16 opt);
void NNSi_FndInitHeapHead(HeapHead *heap, u32 sig, void *start, void *end, u16 opt);
void SetFirstObject(NNSFndList *list, void *obj);
void NNS_FndPrependListObject(NNSFndList *list, void *obj);
void *AllocFromHead__FrameHeap(FrmHead *f, u32 size, u32 alignment);
void *AllocFromTail__FrameHeap(FrmHead *f, u32 size, u32 alignment);
void FreeHead(HeapHead *h);
void FreeTail(HeapHead *h);
void FreeHead(HeapHead *h);
void FreeTail(HeapHead *h);
HeapHead *InitFrameHeap(void *start, void *end, u16 opt);


#define FRM(h) (&(h)->u.frm)

extern BOOL FS_OpenFile(void *file, const char *path);
extern void FS_CloseFile(void *file);
extern BOOL FS_UnloadArchive(void *arc);
extern u32 strlen(const char *s);
extern BOOL FS_RegisterArchiveName(void *arc, const char *name, u32 len);
extern BOOL FS_LoadArchive(void *arc, uptr base, u32 fat, u32 fatSize, u32 fnt, u32 fntSize, void *rd, void *wr);

BOOL func_0210149c(u32 *narc);

typedef struct GfdMan {
    u32 start;
    u32 end;
    u32 enabled;
    u32 flag;
    u16 kind;
    u16 pad;
    u32 base;
} GfdMan;

extern GfdMan data_0213bc3c[5];
extern GfdMan *data_0213bc20[];
extern GfdMan *data_0213bc28[];
extern u16 data_021f5cb0;

void NNSi_GfdSetTexNrmSearchArray(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4);
u32 NNS_GfdAllocFrmTexVram(u32 szByte, BOOL is4x4, BOOL opt);
s32 NNS_GfdFreeFrmTexVram();

void *NNS_FndGetPrevListObject(NNSFndList *list, void *obj);
void *NNS_FndGetNextListObject(NNSFndList *list, void *obj);
void NNS_FndRemoveListObject(NNSFndList *list, void *obj);
void NNS_FndInsertListObject(NNSFndList *list, void *target, void *obj);
void NNS_FndPrependListObject(NNSFndList *list, void *obj);
void NNS_FndAppendListObject(NNSFndList *list, void *obj);
void SetFirstObject(NNSFndList *list, void *obj);
void NNS_FndInitList(NNSFndList *list, u16 offset);
void NNSi_FndFinalizeHeap(HeapHead *heap);
void NNSi_FndInitHeapHead(HeapHead *heap, u32 sig, void *start, void *end, u16 opt);
NNSFndList *FindListContainHeap(HeapHead *heap);
HeapHead *FindContainHeap(NNSFndList *list, HeapHead *mem);
u32 NNS_FndGetSizeForMBlockExpHeap(const void *memBlock);
void NNS_FndVisitAllocatedForExpHeap(HeapHead *heap, void (*visitor)(void *, HeapHead *, u32), u32 param);
u16 NNS_FndGetGroupIDForExpHeap(HeapHead *heap);
u16 NNS_FndSetGroupIDForExpHeap(HeapHead *heap, u16 id);
u32 NNS_FndGetAllocatableSizeForExpHeapEx(HeapHead *heap, s32 alignment);
u32 NNS_FndGetTotalFreeSizeForExpHeap(HeapHead *heap);
void NNS_FndFreeToExpHeap(HeapHead *heap, void *mem);
u32 NNS_FndResizeForMBlockExpHeap(HeapHead *heap, void *memBlock, u32 size);
void *NNS_FndAllocFromExpHeapEx(HeapHead *heap, u32 size, s32 alignment);
void NNS_FndDestroyExpHeap(HeapHead *heap);
HeapHead *NNS_FndCreateExpHeapEx(void *start, u32 size, u16 opt);
BOOL RecycleRegion(ExpHead *e, Region *rgn);
void *AllocFromTail__ExpHeap(HeapHead *heap, u32 size, s32 alignment);
void *AllocFromHead__ExpHeap(HeapHead *heap, u32 size, s32 alignment);
void *AllocUsedBlockFromFreeBlock(ExpHead *e, MBlock *freeBlk, void *mblock, u32 size, u16 dir);
HeapHead *InitExpHeap(void *start, void *end, u16 opt);
MBlock *InitMBlock(Region *rgn, u16 sig);
MBlock *InsertMBlock(void *listp, MBlock *blk, MBlock *prev);
MBlock *RemoveMBlock(void *listp, MBlock *blk);
void GetRegionOfMBlock(Region *rgn, MBlock *blk);
u32 NNS_FndResizeForMBlockFrmHeap(HeapHead *heap, void *mem, u32 size);
u32 NNS_FndAdjustFrmHeap(HeapHead *heap);
BOOL NNS_FndFreeByStateToFrmHeap(HeapHead *heap, u32 tag);
BOOL NNS_FndRecordStateForFrmHeap(HeapHead *heap, u32 tag);
u32 NNS_FndGetAllocatableSizeForFrmHeapEx(HeapHead *heap, s32 alignment);
void NNS_FndFreeToFrmHeap(HeapHead *heap, u32 mode);
void *NNS_FndAllocFromFrmHeapEx(HeapHead *heap, u32 size, s32 alignment);
void NNS_FndDestroyFrmHeap(HeapHead *heap);
HeapHead *NNS_FndCreateFrmHeapEx(void *start, u32 size, u16 opt);
void FreeTail(HeapHead *heap);
void FreeHead(HeapHead *heap);
void *AllocFromTail__FrameHeap(FrmHead *f, u32 size, u32 alignment);
void *AllocFromHead__FrameHeap(FrmHead *f, u32 size, u32 alignment);
HeapHead *InitFrameHeap(void *start, void *end, u16 opt);
BOOL NNS_FndUnmountArchive(void *arc);
BOOL NNS_FndMountArchive(u32 *arc, const char *name, u32 *narc);
BOOL func_0210149c(u32 *narc);
s32 FreeTexVram_();
s32 AllocTexVram_();
s32 FreePlttVram_();
s32 AllocPlttVram_();
s32 NNS_GfdFreeFrmTexVram();
u32 NNS_GfdAllocFrmTexVram(u32 szByte, BOOL is4x4, BOOL opt);
void NNS_GfdInitFrmTexVramManager(u32 mode, BOOL setFuncs);
void NNSi_GfdSetTexNrmSearchArray(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4);

BOOL NNS_FndRecordStateForFrmHeap(HeapHead *heap, u32 tag) {
    uptr oldHead;
    FrmHead *f = FRM(heap);
    FrmState *st;
    oldHead = f->head;
    HOST_ASAN_UNPOISON(f->head, f->tail - f->head);
    st = (FrmState *)AllocFromHead__FrameHeap(f, sizeof(FrmState), 4);
    HOST_ASAN_POISON(f->head, f->tail - f->head);
    if (st == 0) return 0;
    st->tag = tag;
    st->head = oldHead;
    st->tail = f->tail;
    st->prev = f->state;
    f->state = st;
    return 1;
}

BOOL NNS_FndFreeByStateToFrmHeap(HeapHead *heap, u32 tag) {
    FrmState *st;
    FrmHead *f = FRM(heap);
    st = f->state;
    if (tag != 0) {
        for (; st != 0; st = st->prev) {
            if (st->tag == tag) break;
        }
    }
    if (st == 0) return 0;
    f->head = st->head;
    f->tail = st->tail;
    f->state = st->prev;
    HOST_ASAN_POISON(f->head, f->tail - f->head);
    return 1;
}

u32 NNS_FndAdjustFrmHeap(HeapHead *heap) {
    FrmHead *f = FRM(heap);
    if (heap->end - f->tail != 0) return 0;
    heap->end = f->head;
    f->tail = heap->end;
    return (u32)(heap->end - (uptr)heap);
}

u32 NNS_FndResizeForMBlockFrmHeap(HeapHead *heap, void *mem, u32 size) {
    FrmHead *f = FRM(heap);
    uptr oldHead;
    uptr newHead;
    u32 oldSize;
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    oldHead = f->head;
    newHead = size + (uptr)mem;
    oldSize = (u32)(oldHead - (uptr)mem);
    if (size == oldSize) return size;
    if (size > oldSize) {
        if ((s32)(newHead - f->tail) > 0) return 0;
        HOST_ASAN_UNPOISON(oldHead, size - oldSize);
        ClearMem(heap, oldHead, size - oldSize);
    }
    f->head = newHead;
    HOST_ASAN_UNPOISON(mem, size);
    HOST_ASAN_POISON(f->head, f->tail - f->head);
    return size;
}

void GetRegionOfMBlock(Region *rgn, MBlock *blk) {
    rgn->start = (uptr)blk - (u16)((blk->attr.raw >> 8) & 0x7f);
    rgn->end = blk->size + ((uptr)blk + sizeof(MBlock));
}

MBlock *RemoveMBlock(void *listp, MBlock *blk) {
    MBlock **list = (MBlock **)listp;
    MBlock *prev = blk->prev;
    MBlock *next = blk->next;
    if (prev != 0) prev->next = next;
    else list[0] = next;
    if (next != 0) next->prev = prev;
    else list[1] = prev;
    return prev;
}

MBlock *InsertMBlock(void *listp, MBlock *blk, MBlock *prev) {
    MBlock **list = (MBlock **)listp;
    MBlock *next;
    blk->prev = prev;
    if (prev != 0) {
        next = prev->next;
        prev->next = blk;
    } else {
        next = list[0];
        list[0] = blk;
    }
    blk->next = next;
    if (next != 0) next->prev = blk;
    else list[1] = blk;
    return blk;
}

MBlock *InitMBlock(Region *rgn, u16 sig) {
    MBlock *b = (MBlock *)rgn->start;
    b->sig = sig;
    b->attr.raw = 0;
    b->size = (u32)(rgn->end - ((uptr)b + sizeof(MBlock)));
    b->prev = 0;
    b->next = 0;
    return b;
}

HeapHead *InitExpHeap(void *start, void *end, u16 opt) {
    HeapHead *heap = (HeapHead *)start;
    ExpHead *e = EXP(heap);
    Region rgn;
    MBlock *b;
    NNSi_FndInitHeapHead(heap, 0x45585048, e + 1, end, opt);
    e->groupID = 0;
    e->feature.raw = 0;
    e->feature.f.allocMode = 0;
    rgn.start = heap->start;
    rgn.end = heap->end;
    b = InitMBlock(&rgn, 0x4652);
    e->freeHead = b;
    e->freeTail = b;
    e->usedHead = 0;
    e->usedTail = 0;
    return heap;
}

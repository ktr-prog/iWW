#include "proto/autoload_2/unk_02100708.h"
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

typedef struct PRegion { void *start; void *end; } PRegion;
static inline void *AddU32ToPtr(void *p, u32 v) { return (void *)((uptr)p + v); }
static inline void *SubU32ToPtr(void *p, u32 v) { return (void *)((uptr)p - v); }
static inline u32 GetOffsetFromPtr(const void *start, const void *end) { return (u32)((uptr)end - (uptr)start); }
static inline void *GetMemPtr(MBlock *b) { return AddU32ToPtr(b, sizeof(MBlock)); }
static inline void *GetEndAddr(MBlock *b) { return AddU32ToPtr(GetMemPtr(b), b->size); }
static inline MBlock *GetMBlockHeadPtr(void *mem) { return (MBlock *)SubU32ToPtr(mem, sizeof(MBlock)); }
static inline ExpHead *GetExpHead(HeapHead *h) { return (ExpHead *)AddU32ToPtr(h, (u32)__builtin_offsetof(HeapHead, u)); }
static inline void FillAlloc(HeapHead *h, void *dst, u32 size) {
    if (GetOptFlag(h) & 1) {
        volatile u32 zero = 0;
        MIi_CpuClear32(zero, dst, size);
    }
}

static void HostAsan_FreeBlocks(HeapHead *heap, int poison) {
#ifdef HOST_ASAN
    MBlock *b;
    for (b = heap->u.exp.freeHead; b != 0; b = b->next) {
        if (poison) HOST_ASAN_POISON((u8 *)b + sizeof(MBlock), b->size);
        else HOST_ASAN_UNPOISON((u8 *)b + sizeof(MBlock), b->size);
    }
#endif
}

static u32 ResizeForMBlockExpHeap(HeapHead *heap, void *memBlock, u32 size);
u32 NNS_FndResizeForMBlockExpHeap(HeapHead *heap, void *memBlock, u32 size) {
#ifdef HOST_ASAN
    MBlock *b = GetMBlockHeadPtr(memBlock);
    u32 r;
    HOST_ASAN_UNPOISON(memBlock, b->size);
    HostAsan_FreeBlocks(heap, 0);
    r = ResizeForMBlockExpHeap(heap, memBlock, size);
    HostAsan_FreeBlocks(heap, 1);
    if (r) {
        HOST_ASAN_UNPOISON(memBlock, size);
        HOST_ASAN_POISON((u8 *)memBlock + size, b->size - size);
    }
    return r;
#else
    return ResizeForMBlockExpHeap(heap, memBlock, size);
#endif
}
static u32 ResizeForMBlockExpHeap(HeapHead *heap, void *memBlock, u32 size) {
    ExpHead *e;
    MBlock *b;
    e = GetExpHead(heap);
    b = GetMBlockHeadPtr(memBlock);
    size = (size + 3) & ~3;
    if (size == b->size) return size;
    if (size > b->size) {
        void *crUsedEnd = GetEndAddr(b);
        MBlock *block;
        for (block = e->freeHead; block; block = block->next) {
            if (block == crUsedEnd) break;
        }
        if (!block || size > b->size + sizeof(MBlock) + block->size) return 0;
        {
            PRegion rgn;
            void *oldEnd;
            MBlock *prev;
            GetRegionOfMBlock((Region *)&rgn, block);
            prev = RemoveMBlock(&e->freeHead, block);
            oldEnd = rgn.start;
            rgn.start = AddU32ToPtr(memBlock, size);
            if (GetOffsetFromPtr(rgn.start, rgn.end) < sizeof(MBlock)) rgn.start = rgn.end;
            b->size = GetOffsetFromPtr(memBlock, rgn.start);
            if (GetOffsetFromPtr(rgn.start, rgn.end) >= sizeof(MBlock)) {
                InsertMBlock(&e->freeHead, InitMBlock((Region *)&rgn, 0x4652), prev);
            }
            FillAlloc(heap, oldEnd, GetOffsetFromPtr(oldEnd, rgn.start));
        }
    } else {
        PRegion rgn;
        const u32 oldSize = b->size;
        rgn.start = AddU32ToPtr(memBlock, size);
        rgn.end = GetEndAddr(b);
        b->size = size;
        if (!RecycleRegion(e, (Region *)&rgn)) b->size = oldSize;
    }
    return b->size;
}

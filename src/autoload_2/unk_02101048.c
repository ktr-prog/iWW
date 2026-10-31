typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
#include "uptr.h"

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
BOOL func_0210149c(u32 *narc);
s32 NNS_GfdFreeFrmTexVram(u32 texKey);
u32 NNS_GfdAllocFrmTexVram(u32 szByte, BOOL is4x4, BOOL opt);
void NNS_GfdInitFrmTexVramManager(u32 mode, BOOL setFuncs);
void NNSi_GfdSetTexNrmSearchArray(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4);

s32 NNS_GfdFreeFrmTexVram(u32 texKey) { return 0; }

static u32 AllocPlttVram_(u32 szByte, BOOL is4pltt, u32 opt) { return 0; }

static s32 FreePlttVram_(u32 plttKey) { return -1; }

static u32 AllocTexVram_(u32 szByte, BOOL is4x4comp, u32 opt) { return 0; }

static s32 FreeTexVram_(u32 texKey) { return -1; }

BOOL func_0210149c(u32 *narc) {
    if (narc[0] != 0x4352414e) return 0;
    if (*(u16 *)(narc + 1) != 0xfffe) return 0;
    return *(u16 *)((u8 *)narc + 6) == 0x100;
}

#include "sys/NNSFndArchive.h"
#include "uptr.h"
#include "host_asan.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/autoload_2/unk_0210169c.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_0212703c.h"
extern BOOL FS_OpenFile(FSFile *file, const char *path);
extern BOOL FS_CloseFile(FSFile *file);
extern BOOL FS_UnloadArchive(FSArc *arc);
extern u32 strlen(const char *s);
extern BOOL FS_RegisterArchiveName(FSArc *arc, const char *name, int len);
extern BOOL FS_LoadArchive(FSArc *arc, uptr base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size, FSIoFunc rd,
                           FSIoFunc wr);
BOOL NNS_FndMountArchive(struct NNSFndArchive *arc, const char *name, u32 *narc) {
    u8 *fat;
    u8 *fnt;
    u8 *img;
    int i;
    u32 *chunk;
    uptr base;
    int count;
    img = fnt = fat = 0;
    if (func_0210149c(narc) == 0) return 0;
    chunk = (u32 *)((u8 *)narc + *(u16 *)((u8 *)narc + 12));
    count = *(u16 *)((u8 *)narc + 14);
    for (i = 0; i < count; i++) {
        switch (chunk[0]) {
        case 0x464e5442: fnt = (u8 *)chunk; break;
        case 0x46415442: fat = (u8 *)chunk; break;
        case 0x46494d47: img = (u8 *)chunk; break;
        }
        chunk = (u32 *)((u8 *)chunk + chunk[1]);
    }
    FS_InitArchive(&arc->arc);
    arc->arcBinary = narc;
    arc->fatData = fat;
    base = (uptr)(img + 8);
    arc->fileImage = img + 8;
    if (FS_RegisterArchiveName(&arc->arc, name, strlen(name)) == 0) return 0;
    if (FS_LoadArchive(&arc->arc, base, (u32)(fat + 12 - (img + 8)), ((u32 *)fat)[1] - 12, (u32)(fnt + 8 - (img + 8)),
                       ((u32 *)fnt)[1] - 8, 0, 0) != 0) return 1;
    FS_ReleaseArchiveName(&arc->arc);
    return 0;
}

BOOL NNS_FndUnmountArchive(struct NNSFndArchive *arc) {
    if (FS_UnloadArchive(&arc->arc) == 0) return 0;
    FS_ReleaseArchiveName(&arc->arc);
    return 1;
}

void *NNS_FndGetArchiveFileByName(const char *path) {
    FSFile file;
    u8 *result = 0;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path)) {
        result = (u8 *)((struct NNSFndArchive *)file.arc)->fileImage + file.prop.file.start;
        FS_CloseFile(&file);
    }
    return result;
}

HeapHead *InitFrameHeap(void *start, void *end, u16 opt) {
    HeapHead *heap = (HeapHead *)start;
    FrmHead *f = FRM(heap);
    NNSi_FndInitHeapHead(heap, 0x46524d48, f + 1, end, opt);
    f->head = heap->start;
    f->tail = heap->end;
    f->state = 0;
    return heap;
}

void *AllocFromHead__FrameHeap(FrmHead *f, u32 size, u32 alignment) {
    uptr head = f->head;
    uptr start = (alignment - 1 + head) & ~(uptr)(alignment - 1);
    uptr newHead = size + start;
    if (newHead > f->tail) return 0;
    {
        u32 len = (u32)(newHead - head);
        ClearMem(HH(f), head, len);
    }
    f->head = newHead;
    return (void *)start;
}

void *AllocFromTail__FrameHeap(FrmHead *f, u32 size, u32 alignment) {
    uptr tail = f->tail;
    uptr newTail = (tail - size) & ~(uptr)(alignment - 1);
    if (newTail < f->head) return 0;
    {
        u32 len = (u32)(tail - newTail);
        ClearMem(HH(f), newTail, len);
    }
    f->tail = newTail;
    return (void *)newTail;
}

void FreeHead(HeapHead *heap) {
    FrmHead *f = FRM(heap);
    f->head = heap->start;
    f->state = 0;
}

void FreeTail(HeapHead *heap) {
    FrmState *st;
    FrmHead *f = FRM(heap);
    st = f->state;
    for (; st != 0; st = st->prev) st->tail = heap->end;
    f->tail = heap->end;
}

HeapHead *NNS_FndCreateFrmHeapEx(void *start, u32 size, u16 opt) {
    uptr end = ((uptr)start + size) & ~(uptr)3;
    uptr st = ((uptr)start + 3) & ~(uptr)3;
    if (st > end || end - st < __builtin_offsetof(HeapHead, u) + sizeof(FrmHead)) return 0;
#ifdef HOST_ASAN
    {
        HeapHead *heap = InitFrameHeap((void *)st, (void *)end, opt);
        HOST_ASAN_POISON(FRM(heap)->head, FRM(heap)->tail - FRM(heap)->head);
        return heap;
    }
#else
    return InitFrameHeap((void *)st, (void *)end, opt);
#endif
}

void NNS_FndDestroyFrmHeap(HeapHead *heap) {
    NNSi_FndFinalizeHeap(heap);
}

void *NNS_FndAllocFromFrmHeapEx(HeapHead *heap, u32 size, s32 alignment) {
    FrmHead *f = FRM(heap);
#ifdef HOST_ASAN
    void *mem;
    u32 asked = size;
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    HOST_ASAN_UNPOISON(f->head, f->tail - f->head);
    mem = alignment >= 0 ? AllocFromHead__FrameHeap(f, size, alignment) : AllocFromTail__FrameHeap(f, size, -alignment);
    HOST_ASAN_POISON(f->head, f->tail - f->head);
    if (mem) HOST_ASAN_UNPOISON(mem, asked);
    return mem;
#else
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    if (alignment >= 0) return AllocFromHead__FrameHeap(f, size, alignment);
    return AllocFromTail__FrameHeap(f, size, -alignment);
#endif
}

void NNS_FndFreeToFrmHeap(HeapHead *heap, u32 mode) {
    if (mode & 1) FreeHead(heap);
    if (mode & 2) FreeTail(heap);
    HOST_ASAN_POISON(FRM(heap)->head, FRM(heap)->tail - FRM(heap)->head);
}

u32 (*data_0213bc18)(u32 szByte, BOOL is4pltt, u32 opt) = AllocPlttVram_;
s32 (*data_0213bc14)(u32 texKey) = FreeTexVram_;
u32 (*data_0213bc10)(u32 szByte, BOOL is4x4comp, u32 opt) = AllocTexVram_;
s32 (*data_0213bc1c)(u32 plttKey) = FreePlttVram_;

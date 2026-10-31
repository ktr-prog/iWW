#include "nitro/fs.h"
#include "nnsys/snd_arc.h"
#include "proto/autoload_2/unk_0210a9c4.h"
#include "proto/autoload_2/unk_0210b1b0.h"
#include "proto/autoload_2/unk_0210b448.h"
#include "proto/autoload_2/unk_02119434.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
typedef struct NNSFndLink { void *prev; void *next; } NNSFndLink;
typedef struct NNSFndList { void *head; void *tail; u16 num; u16 offset; } NNSFndList;
typedef void (*CapCb)(void *, void *, u32, s32, void *);
typedef struct Cap {
    s32 active;
    s32 mode;
    s32 fmt;
    u8 *bufL;
    u8 *bufR;
    u32 size;
    u32 blkSize;
    s32 blkIdx;
    u32 chMask;
    u32 startCh;
    u32 capMask;
    s32 alarm;
    s32 nBlocks;
    CapCb cb;
    void *cbArg;
    u32 fader[4];
    s32 faderOn;
    s32 vol;
} Cap;
typedef struct FatEnt { u32 off; u32 size; u32 ptr; u32 fc; } FatEnt;
typedef struct Fat { u32 w0; u32 w4; u32 count; FatEnt e[1]; } Fat;
static inline void *FatEnt_Ptr(const FatEnt *e) {
    void *p;
    __builtin_memcpy(&p, &e->ptr, sizeof p);
    return p;
}
static inline void FatEnt_SetPtr(FatEnt *e, void *p) { __builtin_memcpy(&e->ptr, &p, sizeof p); }
typedef NNSSndArc Arc;
typedef struct InfoTbl { u32 count; u32 ent[1]; } InfoTbl;
typedef struct SndHeap { void *heap; NNSFndList list; } SndHeap;
typedef struct SndHeapBlk {
    NNSFndLink link;
    u32 size;
    void (*cb)(void *, u32, void *, u32);
    void *arg0;
    u32 arg1;
    u8 pad[8];
} SndHeapBlk;
#define SNDHEAP_HDR ((sizeof(SndHeap) + 3) & ~3)
#define SNDHEAP_BLK_HDR ((sizeof(SndHeapBlk) + 31) & ~31)

extern Cap data_021fb7b4;
extern void NNS_FndInitList(NNSFndList *, u16);
extern void DC_FlushRange(void *, u32);
extern void MIi_CpuClear32(u32, void *, u32);
extern u32 SND_GetCurrentCommandTag(void);
extern u32 SND_WaitForCommandProc(u32);
extern u32 SND_FlushCommand(u32);
extern u32 data_027e038c;
extern s32 data_027e0390;
extern u32 data_021fb774;
extern void SND_SetChannelVolume(u32, u32, u32);
extern u32 data_021fb8a8;
extern void NNSi_SndFaderUpdate(void *);
extern u32 NNSi_SndFaderIsFinished(void *);
extern s32 NNSi_SndFaderGet(void *);
extern void OS_InitMessageQueue(void *, void *, s32);
extern void OS_CreateThread(void *, void *, void *, void *, u32, u32);
extern void OS_WakeupThreadDirect(void *);
extern BOOL NNSi_SndCaptureStart(s32 mode, void *bufL, void *bufR, u32 len, s32 fmt, s32 a5, s32 a6, BOOL loop, int rate, int vol, int pan1, int pan2, int nBlocks, CapCb cb, void *cbArg);
extern Arc *data_021fbd68;
extern BOOL FS_SeekFile(void *, u32, u32);
extern s32 FS_ReadFile(void *, void *, u32);
extern u8 *NNSi_SndSeqArcGetSeqInfo(void *, u32);
extern void *NNS_SndHeapAlloc(SndHeap *, u32, void (*)(void *, u32, void *, u32), void *, u32);
extern void MIi_CpuCopy32(void *, void *, u32);
extern BOOL FS_ConvertPathToFileID();
extern BOOL FS_OpenFileFast(void *, FSFileID);
extern void *NNS_FndAllocFromFrmHeapEx(void *, u32, u32);
extern void NNS_FndAppendListObject(NNSFndList *, void *);
extern void InitHeapSection(NNSFndList *);
extern BOOL NNS_SndArcSetup(Arc *, void *, BOOL);
extern void *NNS_SndArcGetSeqArcInfo(s32);
extern void *NNS_SndArcGetFileAddress(u32);
extern void SymbolDisposeCallback(void *, u32, void *, u32);
extern void FatDisposeCallback(void *, u32, void *, u32);
extern void InfoDisposeCallback(void *, u32, void *, u32);
extern void *NNS_FndGetPrevListObject(NNSFndList *, void *);
extern void NNS_FndRemoveListObject(NNSFndList *, void *);
extern void NNS_FndAppendListObject(NNSFndList *, void *);
extern BOOL NNS_FndFreeByStateToFrmHeap(void *, u32);
extern BOOL NNS_FndRecordStateForFrmHeap(void *, u32);
extern void NNS_FndFreeToFrmHeap(void *, u32);
extern void NNS_FndDestroyFrmHeap(void *);
extern void *NNS_FndCreateFrmHeapEx(void *, u32, u16);
extern void NNS_SndHeapClear(SndHeap *);
extern BOOL NewSection(SndHeap *);
extern BOOL InitHeap(SndHeap *, void *);
SndHeap *NNS_SndHeapCreate(void *start, u32 size)
{
    uptr end = (uptr)start + size;
    SndHeap *h = (SndHeap *)(((uptr)start + 3) & ~(uptr)3);
    void *heap;
    u32 avail;
    if ((uptr)h > end) {
        return 0;
    }
    avail = (u32)(end - (uptr)h);
    if (avail < SNDHEAP_HDR) {
        return 0;
    }
    heap = NNS_FndCreateFrmHeapEx((u8 *)h + SNDHEAP_HDR, avail - SNDHEAP_HDR, 0);
    if (heap == 0) {
        return 0;
    }
    if (InitHeap(h, heap) != 0) {
        return h;
    }
    NNS_FndDestroyFrmHeap(heap);
    return 0;
}

void NNS_SndHeapDestroy(SndHeap *h)
{
    NNS_SndHeapClear(h);
    NNS_FndDestroyFrmHeap(h->heap);
}

void NNS_SndHeapClear(SndHeap *h)
{
    NNSFndList *lv;
    SndHeapBlk *b;
    BOOL called = 0;
    lv = NNS_FndGetPrevListObject(&h->list, 0);
    if (lv != 0) {
        do {
            b = NNS_FndGetPrevListObject(lv, 0);
            while (b != 0) {
                if (b->cb != 0) {
                    b->cb((void *)((u8 *)b + SNDHEAP_BLK_HDR), b->size, b->arg0, b->arg1);
                    called = 1;
                }
                b = NNS_FndGetPrevListObject(lv, b);
            }
            NNS_FndRemoveListObject(&h->list, lv);
            lv = NNS_FndGetPrevListObject(&h->list, 0);
        } while (lv != 0);
    }
    NNS_FndFreeToFrmHeap(h->heap, 3);
    if (called) {
        EraseSync();
    }
    NewSection(h);
}

void *NNS_SndHeapAlloc(SndHeap *h, u32 size, void (*cb)(void *, u32, void *, u32), void *a, u32 b)
{
    SndHeapBlk *blk = NNS_FndAllocFromFrmHeapEx(h->heap, ((size + 31) & ~31) + SNDHEAP_BLK_HDR, 32);
    NNSFndList *lv;
    if (blk == 0) {
        return 0;
    }
    lv = NNS_FndGetPrevListObject(&h->list, 0);
    blk->size = size;
    blk->cb = cb;
    blk->arg0 = a;
    blk->arg1 = b;
    NNS_FndAppendListObject(lv, blk);
    return (u8 *)blk + SNDHEAP_BLK_HDR;
}

s32 NNS_SndHeapSaveState(SndHeap *h)
{
    if (NNS_FndRecordStateForFrmHeap(h->heap, h->list.num) == 0) {
        return -1;
    }
    if (NewSection(h) != 0) {
        return h->list.num - 1;
    }
    NNS_FndFreeByStateToFrmHeap(h->heap, 0);
    return -1;
}

void NNS_SndHeapLoadState(SndHeap *h, s32 level)
{
    NNSFndList *lv;
    SndHeapBlk *b = 0;
    BOOL called = 0;
    if (level == 0) {
        NNS_SndHeapClear(h);
        return;
    }
    if (level < h->list.num) {
        do {
            lv = NNS_FndGetPrevListObject(&h->list, 0);
            b = NNS_FndGetPrevListObject(lv, b);
            while (b != 0) {
                if (b->cb != 0) {
                    b->cb((void *)((u8 *)b + SNDHEAP_BLK_HDR), b->size, b->arg0, b->arg1);
                    called = 1;
                }
                b = NNS_FndGetPrevListObject(lv, b);
            }
            NNS_FndRemoveListObject(&h->list, lv);
        } while (level < h->list.num);
    }
    NNS_FndFreeByStateToFrmHeap(h->heap, level);
    if (called) {
        EraseSync();
    }
    NNS_FndRecordStateForFrmHeap(h->heap, h->list.num);
    NewSection(h);
}

s32 NNS_SndHeapGetCurrentLevel(SndHeap *h)
{
    return h->list.num - 1;
}

void InitHeapSection(NNSFndList *l)
{
    NNS_FndInitList(l, 0);
}

BOOL InitHeap(SndHeap *h, void *heap)
{
    NNS_FndInitList(&h->list, sizeof(NNSFndList));
    h->heap = heap;
    return NewSection(h) != 0;
}

BOOL NewSection(SndHeap *h)
{
    NNSFndList *lv = NNS_FndAllocFromFrmHeapEx(h->heap, sizeof(NNSFndList) + sizeof(NNSFndLink), 8);
    if (lv == 0) {
        return 0;
    }
    InitHeapSection(lv);
    NNS_FndAppendListObject(&h->list, lv);
    return 1;
}

void EraseSync(void)
{
    u32 tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(tag);
}

void NNS_SndArcInit(Arc *arc, void *path, void *heap, BOOL loadSymb)
{
    arc->info = 0;
    arc->fat = 0;
    arc->symb = 0;
    if (FS_ConvertPathToFileID(&arc->id, path) == 0) {
        return;
    }
    FS_InitFile(&arc->file);
    if (FS_OpenFileFast(&arc->file, arc->id) == 0) {
        return;
    }
    arc->fromFile = 1;
    if (NNS_SndArcSetup(arc, heap, loadSymb)) {
        data_021fbd68 = arc;
    }
}

BOOL NNS_SndArcSetup(Arc *arc, void *heap, BOOL loadSymb)
{
    s32 n;
    if (FS_SeekFile(&arc->file, 0, 0) == 0) {
        return 0;
    }
    if (FS_ReadFile(&arc->file, arc, 0x30) != 0x30) {
        return 0;
    }
    if (heap != 0 && 1) {
        arc->info = NNS_SndHeapAlloc(heap, arc->infoSize, InfoDisposeCallback, arc, 0);
        if (arc->info == 0) {
            return 0;
        }
        if (FS_SeekFile(&arc->file, arc->infoOff, 0) == 0) {
            return 0;
        }
        n = FS_ReadFile(&arc->file, arc->info, arc->infoSize);
        if (n != arc->infoSize) {
            return 0;
        }
        arc->fat = NNS_SndHeapAlloc(heap, arc->fatSize, FatDisposeCallback, arc, 0);
        if (arc->fat == 0) {
            return 0;
        }
        if (FS_SeekFile(&arc->file, arc->fatOff, 0) == 0) {
            return 0;
        }
        n = FS_ReadFile(&arc->file, arc->fat, arc->fatSize);
        if (n != arc->fatSize) {
            return 0;
        }
        if (loadSymb != 0 && arc->symbSize != 0) {
            arc->symb = NNS_SndHeapAlloc(heap, arc->symbSize, SymbolDisposeCallback, arc, 0);
            if (arc->symb == 0) {
                return 0;
            }
            if (FS_SeekFile(&arc->file, arc->symbOff, 0) == 0) {
                return 0;
            }
            n = FS_ReadFile(&arc->file, arc->symb, arc->symbSize);
        if (n != arc->symbSize) {
                return 0;
            }
        }
    }
    return 1;
}

void NNS_SndArcInitOnMemory(Arc *arc, u8 *base)
{
    u32 i;
    FatEnt *e;
    MIi_CpuCopy32(base, arc, 0x30);
    arc->info = (arc->infoOff == 0) ? 0 : base + arc->infoOff;
    arc->fat = (arc->fatOff == 0) ? 0 : (Fat *)(base + arc->fatOff);
    arc->symb = (arc->symbOff == 0) ? 0 : base + arc->symbOff;
    for (i = 0; i < arc->fat->count; i++) {
        e = &arc->fat->e[i];
        FatEnt_SetPtr(e, (e->off == 0) ? 0 : base + e->off);
    }
    arc->fromFile = 0;
    data_021fbd68 = arc;
}

Arc *NNS_SndArcSetCurrent(Arc *arc)
{
    Arc *old = data_021fbd68;
    data_021fbd68 = arc;
    return old;
}

Arc *NNS_SndArcGetCurrent(void)
{
    return data_021fbd68;
}

void *NNS_SndArcGetSeqArcSeqParam(u32 seqArc, u32 idx)
{
    u32 *info = (u32 *)NNS_SndArcGetSeqArcInfo(seqArc);
    u8 *data;
    if (info == 0) {
        return 0;
    }
    data = (u8 *)NNS_SndArcGetFileAddress(*info);
    if (data == 0) {
        return 0;
    }
    data = NNSi_SndSeqArcGetSeqInfo(data, idx);
    return (data == 0) ? 0 : data + 4;
}

void *NNS_SndArcGetSeqInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x8);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetSeqArcInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0xc);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetBankInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x10);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetWaveArcInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x14);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetStrmInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x24);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetPlayerInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x18);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetStrmPlayerInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x20);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

void *NNS_SndArcGetGroupInfo(s32 idx)
{
    Arc *arc = data_021fbd68;
    u8 *info = arc->info;
    u32 off = *(u32 *)(info + 0x1c);
    InfoTbl *tbl;
    u32 e;
    u8 *base;
    if (off == 0) {
        tbl = 0;
    } else {
        tbl = (InfoTbl *)(info + off);
    }
    if (tbl == 0) {
        return 0;
    }
    if (idx < 0) {
        return 0;
    }
    if ((u32)idx >= tbl->count) {
        return 0;
    }
    e = tbl->ent[idx];
    base = arc->info;
    return (e == 0) ? 0 : base + e;
}

u32 NNS_SndArcGetFileOffset(u32 idx)
{
    Fat *fat = data_021fbd68->fat;
    if (idx >= fat->count) {
        return 0;
    }
    return fat->e[idx].off;
}

u32 NNS_SndArcGetFileSize(u32 idx)
{
    Fat *fat = data_021fbd68->fat;
    if (idx >= fat->count) {
        return 0;
    }
    return fat->e[idx].size;
}

s32 NNS_SndArcReadFile(u32 idx, void *buf, u32 len, u32 offset)
{
    Arc *arc = data_021fbd68;
    Fat *fat = arc->fat;
    FatEnt *e;
    u32 rem;
    if (idx >= fat->count) {
        return -1;
    }
    e = &fat->e[idx];
    rem = e->size - offset;
    if (len > rem) {
        len = rem;
    }
    if (FS_SeekFile(&arc->file, e->off + offset, 0) == 0) {
        return -1;
    }
    return FS_ReadFile(&arc->file, buf, len);
}

void func_0210b48c(FSFileID *out)
{
    *out = data_021fbd68->id;
}

void *NNS_SndArcGetFileAddress(u32 idx)
{
    Fat *fat = data_021fbd68->fat;
    if (idx >= fat->count) {
        return 0;
    }
    return FatEnt_Ptr(&fat->e[idx]);
}

void NNS_SndArcSetFileAddress(u32 idx, void *v)
{
    FatEnt_SetPtr(&data_021fbd68->fat->e[idx], v);
}

Arc *data_021fbd68;

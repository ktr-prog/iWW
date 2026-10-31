#include "uptr.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
#include "types64.h"
typedef int BOOL;

#include "nnsys/fnd_list.h"
#include "sys/PMCbInfo.h"
#include "proto/autoload_2/unk_021093f4.h"
#include "proto/autoload_2/unk_021096d4.h"
#include "proto/autoload_2/unk_02109830.h"
#include "proto/autoload_2/unk_0210a9c4.h"
#include "proto/autoload_2/unk_0210b1b0.h"
#include "proto/autoload_2/unk_0210da28.h"
#include "proto/autoload_2/unk_02116c0c.h"
#include "proto/itcm/unk_01ff9e10.h"

typedef struct Seq Seq;
typedef struct Handle { Seq *seq; } Handle;

typedef struct Player {
    NNSFndList seqList;
    NNSFndList heapList;
    u32 playable;
    u32 bank;
    u8 vol;
    u8 pad[3];
} Player;

typedef struct HeapBlk {
    NNSFndLink link;
    void *heap;
    Seq *seq;
    s32 playerNo;
} HeapBlk;
#define HEAPBLK_SIZE ((sizeof(HeapBlk) + 3) & ~3)

struct Seq {
    Handle *handle;
    Player *player;
    HeapBlk *heap;
    NNSFndLink plink;
    NNSFndLink glink;
    u32 fader[4];
    u8 status;
    u8 started;
    u8 f2e;
    u8 pending;
    u32 tag;
    u16 cmd;
    u16 f36;
    u16 a38;
    u16 a3a;
    u8 id;
    u8 prio;
    s16 vol;
    u8 v40;
    u8 v41;
    u8 pad42[2];
};

typedef struct StrmEnt { uptr buf; u32 pos; } StrmEnt;
typedef void (*StrmCb)(s32, s32, uptr *, u32, s32, void *);

typedef struct Strm {
    NNSFndLink link;
    PMCbInfo pm0;
    PMCbInfo pm1;
    s32 fmt;
    struct { s32 setup : 1; s32 started : 1; } f;
    u32 blockSize;
    s32 blkCount;
    StrmCb cb;
    void *arg;
    s32 blk;
    u32 timer;
    s32 alarm;
    u32 chMask;
    s32 chCount;
    u8 chIdx[16];
} Strm;

typedef struct SndBuf { u8 b[0x11e0]; } SndBuf;

extern s8 data_021f89d0;
extern u32 data_021f89d4;
extern u32 data_021f89d8;
extern u32 data_021f89dc;
extern PMCbInfo data_021f89e0;
extern PMCbInfo data_021f89ec;
extern SndBuf data_021f8a00[];
extern u32 data_021fadc0;
extern u32 data_021fadc4;
extern u32 data_021fadc8;
extern NNSFndList data_021fadcc;
extern NNSFndList data_021fadd8;
extern Seq data_021fade4[];
extern Player data_021fb224[];
extern NNSFndList data_021fb6a8;
extern uptr data_021fb6b4[];
extern StrmEnt data_021fb6f4[];
extern s16 data_02139fb4[];

extern void *NNS_FndGetNextListObject(NNSFndList *, void *);
extern void NNS_FndRemoveListObject(NNSFndList *, void *);
extern void NNS_FndInsertListObject(NNSFndList *, void *, void *);
extern void NNS_FndAppendListObject(NNSFndList *, void *);
extern void NNS_FndInitList(NNSFndList *, u16);
extern void FX_DivAsync(s32, s32);
extern s32 FX_GetDivResult(void);
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern u32 _u32_div_f();
extern void NNS_SndHeapClear(void *);
extern void *NNS_SndHeapAlloc();
extern void *NNS_SndHeapCreate(void *, u32);
extern void NNS_SndHeapDestroy(void *);
extern u32 NNSi_SndFaderIsFinished(void *);
extern void NNSi_SndFaderUpdate(void *);
extern s32 NNSi_SndFaderGet(void *);
extern void NNSi_SndFaderSet(void *, s32, s32);
extern void NNSi_SndFaderInit(void *);
extern void DC_InvalidateRange(void *, u32);
extern void SND_ReadDriverInfo(void *);
extern void SND_SetupChannelPcm();
extern void SND_SetChannelPan(u32, u32);
extern void SND_SetChannelVolume(u32, u32, u32);
extern void SND_UnlockChannel(u32, u32);
extern void SND_LockChannel(u32, u32);
extern void SND_SetTrackMute();
extern void SND_SetupAlarm();
extern void SND_StopTimer(u32, u32, u32, u32);
extern void SND_StartTimer(u32, u32, u32, u32);
extern void SND_SetTrackAllocatableChannel();
extern void SND_SetTrackPan();
extern void SND_SetTrackPitch();
extern void SND_SetTrackVolume();
extern void SND_SetPlayerGlobalVariable();
extern void SND_SetPlayerLocalVariable();
extern void SND_SetPlayerChannelPriority();
extern void SND_SetPlayerVolume(u32, s32);
extern void SND_SetPlayerTempoRatio();
extern void SND_StartPreparedSeq(u32);
extern void SND_PrepareSeq(u32 player, uptr seqBase, u32 seqOffset, uptr bank);
extern void SND_StopSeq(u32);
extern u32 SND_IsFinishedCommandTag(u32);
extern u32 SND_GetCurrentCommandTag(void);
extern u32 SND_WaitForCommandProc(u32);
extern u32 SND_FlushCommand(u32);
extern void *SND_RecvCommandReply(u32);
extern u32 SND_ReadTrackInfo();
extern u32 SND_ReadPlayerInfo();
extern s32 SND_GetPlayerGlobalVariable(s32);
extern s32 SND_GetPlayerLocalVariable();
extern u32 SND_GetPlayerStatus(void);
extern s32 SND_CalcChannelVolume(s32);
extern void SND_SetMasterVolume(u32);
extern void PM_DeletePostSleepCallback(void *);
extern void PM_DeletePreSleepCallback(void *);
extern void PM_AppendPostSleepCallback(void *);
extern void PM_PrependPreSleepCallback(void *);

void SetPlayerPriority(Seq *, u8);
void InsertPrioList(Seq *);
void InsertPlayerList(NNSFndList *, Seq *);
void ShutdownPlayer(Seq *);
void ForceStopSeq(Seq *);
Seq *AllocSeqPlayer(s32);
void NNS_SndHandleReleaseSeq(Handle *);
void StrmCallback(Strm *, s32);
void ShutdownStrm(Strm *);
void ForceStopStrm(Strm *);
void NNS_SndStrmStop(Strm *);
void NNS_SndFreeAlarm(s32);
s32 NNS_SndAllocAlarm(void);
void NNSi_SndPlayerStopSeq(Seq *, s32);
void InitPlayer(Seq *);
void PlayerHeapDisposeCallback(HeapBlk *);
u32 BeginSleep(void);
u32 NNSi_SndReadDriverPlayerInfo(u32, void *);
u32 NNSi_SndReadDriverTrackInfo(u32, u32, void *);

typedef struct TexSrt {
    u8 pad[0x18];
    s32 sx;
    s32 sy;
    s16 sn;
    s16 cs;
    s32 tx;
    s32 ty;
    u16 w;
    u16 h;
} TexSrt;
#define FXM(a, b) ((s32)(((s64)(a) * (b)) >> 12))
void NNS_SndPlayerSetPlayerVolume(s32 i, u8 v)
{
    data_021fb224[i].vol = v;
}

void NNS_SndPlayerSetPlayableSeqCount(s32 i, u32 v)
{
    data_021fb224[i].playable = (u16)v;
}

void NNS_SndPlayerSetAllocatableChannel(s32 i, u32 v)
{
    data_021fb224[i].bank = v;
}

BOOL NNS_SndPlayerCreateHeap(s32 playerNo, void *heap, u32 size)
{
    HeapBlk *b;
    void *h;
    b = NNS_SndHeapAlloc(heap, size + HEAPBLK_SIZE, PlayerHeapDisposeCallback, 0, 0);
    if (b == 0) {
        return 0;
    }
    b->seq = 0;
    b->playerNo = playerNo;
    b->heap = 0;
    h = NNS_SndHeapCreate((u8 *)b + HEAPBLK_SIZE, size);
    if (h == 0) {
        return 0;
    }
    b->heap = h;
    NNS_FndAppendListObject(&data_021fb224[playerNo].heapList, b);
    return 1;
}

void NNS_SndPlayerStopSeq(Handle *h, s32 frames)
{
    NNSi_SndPlayerStopSeq(h->seq, frames);
}

void NNS_SndPlayerStopSeqByPlayerNo(s32 playerNo, s32 frames)
{
    s32 i;
    Seq *s;
    Player *p;
    p = &data_021fb224[playerNo];
    s = data_021fade4;
    for (i = 0; i < 16; i++, s++) {
        if (s->status != 0 && s->player == p) {
            NNSi_SndPlayerStopSeq(s, frames);
        }
    }
}

void NNS_SndPlayerStopSeqBySeqNo(u32 a, u32 b, s32 c)
{
    s32 i;
    Seq *s = data_021fade4;
    for (i = 0; i < 16; i++, s++) {
        if (s->status != 0 && s->cmd == 2 && s->a38 == a && s->a3a == b) {
            NNSi_SndPlayerStopSeq(s, c);
        }
    }
}

void NNS_SndHandleInit(Handle *h)
{
    h->seq = 0;
}

void NNS_SndHandleReleaseSeq(Handle *h)
{
    Seq *s = h->seq;
    if (s != 0) {
        s->handle = 0;
        h->seq = 0;
    }
}

void NNS_SndPlayerSetVolume(Handle *h, u8 v)
{
    Seq *s = h->seq;
    if (s != 0) {
        s->v41 = v;
    }
}

void NNS_SndPlayerSetInitialVolume(Handle *h, u8 v)
{
    Seq *s = h->seq;
    if (s != 0) {
        s->v40 = v;
    }
}

void NNS_SndPlayerMoveVolume(Handle *h, s32 v, s32 frames)
{
    Seq *s = h->seq;
    if (s == 0) {
        return;
    }
    if (s->status == 2) {
        return;
    }
    NNSi_SndFaderSet(s->fader, v << 8, frames);
}

void NNS_SndPlayerSetPlayerPriority(Handle *h, u8 prio)
{
    if (h->seq == 0) {
        return;
    }
    SetPlayerPriority(h->seq, prio);
}

void NNS_SndPlayerSetChannelPriority(Handle *h, u32 b)
{
    if (h->seq == 0) {
        return;
    }
    SND_SetPlayerChannelPriority(h->seq->id, b);
}

void NNS_SndPlayerSetTrackMute(Handle *h, u32 b, u32 c)
{
    if (h->seq == 0) {
        return;
    }
    SND_SetTrackMute(h->seq->id, b, c);
}

void NNS_SndPlayerSetTrackVolume(Handle *h, u32 b, s32 c)
{
    if (h->seq == 0) {
        return;
    }
    SND_SetTrackVolume(h->seq->id, b, data_02139fb4[c]);
}

void NNS_SndPlayerSetTrackPitch(Handle *h, u32 b, u32 c)
{
    if (h->seq == 0) {
        return;
    }
    SND_SetTrackPitch(h->seq->id, b, c);
}

void NNS_SndPlayerSetTrackPan(Handle *h, u32 b, u32 c)
{
    if (h->seq == 0) {
        return;
    }
    SND_SetTrackPan(h->seq->id, b, c);
}

void NNS_SndPlayerSetTempoRatio(Handle *h, u32 b)
{
    if (h->seq == 0) {
        return;
    }
    SND_SetPlayerTempoRatio(h->seq->id, b);
}

void NNS_SndPlayerSetSeqNo(Handle *h, u16 a)
{
    Seq *s = h->seq;
    if (s != 0) {
        s->cmd = 1;
        h->seq->a38 = a;
    }
}

void NNS_SndPlayerSetSeqArcNo(Handle *h, u16 a, u16 b)
{
    Seq *s = h->seq;
    if (s == 0) {
        return;
    }
    s->cmd = 2;
    h->seq->a38 = a;
    h->seq->a3a = b;
}

BOOL NNS_SndPlayerReadVariable(Handle *h, s32 b, s16 *out)
{
    Seq *s = h->seq;
    if (s == 0) {
        return 0;
    }
    if (s->started == 0) {
        *out = -1;
        return 1;
    }
    *out = SND_GetPlayerLocalVariable(s->id, b);
    return 1;
}

BOOL NNS_SndPlayerReadGlobalVariable(s32 a, u16 *out)
{
    *out = SND_GetPlayerGlobalVariable(a);
    return 1;
}

BOOL NNS_SndPlayerWriteVariable(Handle *h, u32 b, u32 c)
{
    if (h->seq == 0) {
        return 0;
    }
    SND_SetPlayerLocalVariable(h->seq->id, b, c);
    return 1;
}

BOOL NNS_SndPlayerWriteGlobalVariable(u32 a, u32 b)
{
    SND_SetPlayerGlobalVariable(a, b);
    return 1;
}

u32 NNS_SndPlayerReadDriverPlayerInfo(Handle *h, void *b)
{
    if (h->seq == 0) {
        return 0;
    }
    return NNSi_SndReadDriverPlayerInfo(h->seq->id, b);
}

u32 NNS_SndPlayerReadDriverTrackInfo(Handle *h, u32 b, void *c)
{
    if (h->seq == 0) {
        return 0;
    }
    return NNSi_SndReadDriverTrackInfo(h->seq->id, b, c);
}

void NNSi_SndPlayerInit(void)
{
    s32 i;
    Seq *s;
    Player *p;
    NNS_FndInitList(&data_021fadd8, __builtin_offsetof(Seq, glink));
    NNS_FndInitList(&data_021fadcc, __builtin_offsetof(Seq, glink));
    s = data_021fade4;
    for (i = 0; i < 16; i++, s++) {
        s->status = 0;
        s->id = i;
        NNS_FndAppendListObject(&data_021fadcc, s);
    }
    p = data_021fb224;
    for (i = 0; i < 32; i++, p++) {
        NNS_FndInitList(&p->seqList, __builtin_offsetof(Seq, plink));
        NNS_FndInitList(&p->heapList, 0);
        p->vol = 127;
        p->playable = 1;
        p->bank = 0;
    }
}

void NNSi_SndPlayerMain(void)
{
    u32 mask = SND_GetPlayerStatus();
    Seq *s = NNS_FndGetNextListObject(&data_021fadd8, 0);
    Seq *next;
    s32 vol;
    s32 a, b, c, d;
    if (s == 0) {
        return;
    }
    do {
        next = NNS_FndGetNextListObject(&data_021fadd8, s);
        if (s->started == 0) {
            if (SND_IsFinishedCommandTag(s->tag) != 0) {
                s->started = 1;
            }
        }
        if (s->started != 0 && (mask & (1 << s->id)) == 0) {
            ShutdownPlayer(s);
        } else {
            NNSi_SndFaderUpdate(s->fader);
            a = data_02139fb4[s->v41];
            b = data_02139fb4[s->v40];
            c = data_02139fb4[s->player->vol];
            d = data_02139fb4[NNSi_SndFaderGet(s->fader) >> 8];
            vol = d + (c + (b + a));
            if (vol < -723) {
                vol = -723;
            } else if (vol > 0) {
                vol = 0;
            }
            if (vol != s->vol) {
                SND_SetPlayerVolume(s->id, vol);
                s->vol = vol;
            }
            if (s->status == 2) {
                if (NNSi_SndFaderIsFinished(s->fader) != 0) {
                    ForceStopSeq(s);
                }
            }
            if (s->pending != 0) {
                SND_StartPreparedSeq(s->id);
                s->pending = 0;
            }
        }
        s = next;
    } while (s != 0);
}

Seq *NNSi_SndPlayerAllocSeqPlayer(Handle *h, s32 playerNo, s32 prio)
{
    Player *p = &data_021fb224[playerNo];
    Seq *s = h->seq;
    if (s != 0) {
        NNS_SndHandleReleaseSeq(h);
    }
    if (p->seqList.num >= p->playable) {
        Seq *o = NNS_FndGetNextListObject(&p->seqList, 0);
        if (o == 0) {
            return 0;
        }
        if (prio < o->prio) {
            return 0;
        }
        ForceStopSeq(o);
    }
    s = AllocSeqPlayer(prio);
    if (s == 0) {
        return 0;
    }
    InsertPlayerList(&p->seqList, s);
    s->handle = h;
    h->seq = s;
    return s;
}

void NNSi_SndPlayerFreeSeqPlayer(Seq *s)
{
    ShutdownPlayer(s);
}

void NNSi_SndPlayerStartSeq(Seq *s, const void *seqBase, u32 seqOffset, const void *bank)
{
    Player *p = s->player;
    SND_PrepareSeq(s->id, (uptr)seqBase, seqOffset, (uptr)bank);
    if (p->bank != 0) {
        SND_SetTrackAllocatableChannel(s->id, 0xffff, p->bank);
    }
    InitPlayer(s);
    s->tag = SND_GetCurrentCommandTag();
    s->pending = 1;
    s->status = 1;
}

void NNSi_SndPlayerStopSeq(Seq *s, s32 frames)
{
    if (s == 0) {
        return;
    }
    if (s->status == 0) {
        return;
    }
    if (frames == 0) {
        ForceStopSeq(s);
        return;
    }
    NNSi_SndFaderSet(s->fader, 0, frames);
    SetPlayerPriority(s, 0);
    s->status = 2;
}

void *NNSi_SndPlayerAllocHeap(s32 playerNo, Seq *seq)
{
    Player *p = &data_021fb224[playerNo];
    HeapBlk *b = NNS_FndGetNextListObject(&p->heapList, 0);
    if (b == 0) {
        return 0;
    }
    NNS_FndRemoveListObject(&p->heapList, b);
    b->seq = seq;
    seq->heap = b;
    NNS_SndHeapClear(b->heap);
    return b->heap;
}

void InitPlayer(Seq *s)
{
    s->f2e = 0;
    s->started = 0;
    s->pending = 0;
    s->cmd = 0;
    s->vol = 0;
    s->v40 = 127;
    s->v41 = 127;
    NNSi_SndFaderInit(s->fader);
    NNSi_SndFaderSet(s->fader, 0x7f00, 1);
}

void InsertPlayerList(NNSFndList *l, Seq *s)
{
    Seq *o = NNS_FndGetNextListObject(l, 0);
    while (o != 0) {
        if (s->prio < o->prio) {
            break;
        }
        o = NNS_FndGetNextListObject(l, o);
    }
    NNS_FndInsertListObject(l, o, s);
    s->player = (Player *)l;
}

void InsertPrioList(Seq *s)
{
    Seq *o = NNS_FndGetNextListObject(&data_021fadd8, 0);
    while (o != 0) {
        if (s->prio < o->prio) {
            break;
        }
        o = NNS_FndGetNextListObject(&data_021fadd8, o);
    }
    NNS_FndInsertListObject(&data_021fadd8, o, s);
}

void ForceStopSeq(Seq *s)
{
    if (s->status == 2) {
        SND_SetPlayerVolume(s->id, -723);
    }
    SND_StopSeq(s->id);
    ShutdownPlayer(s);
}

Seq *AllocSeqPlayer(s32 prio)
{
    Seq *s = NNS_FndGetNextListObject(&data_021fadcc, 0);
    if (s == 0) {
        s = NNS_FndGetNextListObject(&data_021fadd8, 0);
        if (prio < s->prio) {
            return 0;
        }
        ForceStopSeq(s);
    }
    NNS_FndRemoveListObject(&data_021fadcc, s);
    s->prio = prio;
    InsertPrioList(s);
    return s;
}

void ShutdownPlayer(Seq *s)
{
    Player *p;
    if (s->handle != 0) {
        s->handle->seq = 0;
        s->handle = 0;
    }
    p = s->player;
    NNS_FndRemoveListObject(&p->seqList, s);
    s->player = 0;
    if (s->heap != 0) {
        NNS_FndAppendListObject(&p->heapList, s->heap);
        s->heap->seq = 0;
        s->heap = 0;
    }
    NNS_FndRemoveListObject(&data_021fadd8, s);
    NNS_FndAppendListObject(&data_021fadcc, s);
    s->status = 0;
}

void PlayerHeapDisposeCallback(HeapBlk *b)
{
    if (b->heap == 0) {
        return;
    }
    NNS_SndHeapDestroy(b->heap);
    if (b->seq != 0) {
        b->seq->heap = 0;
        return;
    }
    NNS_FndRemoveListObject(&data_021fb224[b->playerNo].heapList, b);
}

void SetPlayerPriority(Seq *s, u8 prio)
{
    Player *p = s->player;
    if (p != 0) {
        NNS_FndRemoveListObject(&p->seqList, s);
        s->player = 0;
    }
    NNS_FndRemoveListObject(&data_021fadd8, s);
    s->prio = prio;
    if (p != 0) {
        InsertPlayerList(&p->seqList, s);
    }
    InsertPrioList(s);
}

Player data_021fb224[32];
Seq data_021fade4[16];
NNSFndList data_021fadd8;
NNSFndList data_021fadcc;

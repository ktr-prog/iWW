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
#include "proto/autoload_2/unk_0210a478.h"
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
extern void SND_PrepareSeq();
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
BOOL NNS_SndStrmSetup(Strm *st, s32 fmt, uptr buf, u32 size, s32 timer, s32 interval, StrmCb cb, void *arg)
{
    s32 i;
    u32 q;
    u32 period;
    u32 t;
    u32 e;
    if (st->f.setup) {
        NNS_SndStrmStop(st);
    }
    q = _u32_div_f(size, st->chCount * (interval << 5));
    st->blockSize = (q * interval) << 5;
    t = st->blockSize;
    if (fmt == 1) {
        t >>= 1;
    }
    period = _u32_div_f(timer * t, interval);
    st->alarm = NNS_SndAllocAlarm();
    if (st->alarm < 0) {
        return 0;
    }
    for (i = 0; i < st->chCount; i++) {
        u32 ch = st->chIdx[i];
        data_021fb6f4[ch].buf = st->blockSize * i + buf;
        data_021fb6f4[ch].pos = 0;
        SND_SetupChannelPcm(ch, fmt, data_021fb6f4[ch].buf, 1, 0, st->blockSize >> 2, 127, 0, timer << 5, 64);
    }
    SND_SetupAlarm(st->alarm, period, period, AlarmCallback__stream, st);
    NNS_FndAppendListObject(&data_021fb6a8, st);
    st->fmt = fmt;
    st->blkCount = interval;
    st->cb = cb;
    st->arg = arg;
    st->blk = 0;
    st->timer = 0;
    st->f.setup = 1;
    e = OS_DisableInterrupts();
    st->blkCount = 1;
    StrmCallback(st, 0);
    st->blkCount = interval;
    OS_RestoreInterrupts(e);
    return 1;
}

void NNS_SndStrmStart(Strm *st)
{
    SND_StartTimer(st->chMask, 0, 1 << st->alarm, 0);
    if (st->f.started) {
        return;
    }
    PM_PrependPreSleepCallback(&st->pm0);
    PM_AppendPostSleepCallback(&st->pm1);
    st->f.started = 1;
}

void NNS_SndStrmStop(Strm *st)
{
    if (!st->f.setup) {
        return;
    }
    ForceStopStrm(st);
}

void NNS_SndStrmSetVolume(Strm *st, u32 timer)
{
    u32 ch;
    s32 i;
    st->timer = timer;
    i = 0;
    if (st->chCount <= 0) {
        return;
    }
    do {
        s32 v;
        ch = st->chIdx[i];
        v = SND_CalcChannelVolume(st->timer + data_021fb6f4[ch].pos);
        SND_SetChannelVolume(1 << ch, v & 0xff, v >> 8);
        i++;
    } while (i < st->chCount);
}

void NNS_SndStrmSetChannelPan(Strm *st, s32 ch, u32 v)
{
    if (ch > st->chCount - 1) {
        return;
    }
    SND_SetChannelPan(1 << st->chIdx[ch], v);
}

void ForceStopStrm(Strm *st)
{
    u32 t;
    if (st->f.started) {
        SND_StopTimer(st->chMask, 0, 1 << st->alarm, 0);
        PM_DeletePreSleepCallback(&st->pm0);
        PM_DeletePostSleepCallback(&st->pm1);
        st->f.started = 0;
        t = SND_GetCurrentCommandTag();
        SND_FlushCommand(1);
        SND_WaitForCommandProc(t);
    }
    ShutdownStrm(st);
}

void ShutdownStrm(Strm *st)
{
    NNS_SndFreeAlarm(st->alarm);
    NNS_FndRemoveListObject(&data_021fb6a8, st);
    st->f.setup = 0;
}

void StrmCallback(Strm *st, s32 flag)
{
    u32 q = _u32_div_f(st->blockSize, st->blkCount);
    u32 off = q * st->blk;
    s32 i;
    for (i = 0; i < st->chCount; i++) {
        uptr b = data_021fb6f4[st->chIdx[i]].buf;
        data_021fb6b4[i] = b + off;
    }
    st->cb(flag, st->chCount, data_021fb6b4, q, st->fmt, st->arg);
    st->blk = st->blk + 1;
    if (st->blk >= st->blkCount) {
        st->blk = 0;
    }
}

void BeginSleep__stream(Strm *st)
{
    u32 t;
    if (!st->f.started) {
        return;
    }
    SND_StopTimer(st->chMask, 0, 1 << st->alarm, 0);
    t = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(t);
}

void EndSleep__stream(Strm *st)
{
    u32 e;
    if (!st->f.started) {
        return;
    }
    while (st->blk != 0) {
        e = OS_DisableInterrupts();
        StrmCallback(st, 1);
        OS_RestoreInterrupts(e);
    }
    SND_StartTimer(st->chMask, 0, 1 << st->alarm, 0);
}

StrmEnt data_021fb6f4[16];
uptr data_021fb6b4[16];
NNSFndList data_021fb6a8;
s32 data_021fb6a4;

#ifdef HOST64
_Static_assert(sizeof(Strm) == 136, "Ctx::strm in unk_0210da28.c");
#endif

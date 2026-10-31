#include "ds_div.h"
#include "host_labels.h"
#include "uptr.h"
#include "nitro/fs.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "types64.h"
#include "proto/autoload_2/unk_0210b448.h"
#include "proto/autoload_2/unk_0210c084.h"
#include "proto/autoload_2/unk_0210ec0c.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02119434.h"
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef int BOOL;

#include "nnsys/fnd_list.h"

typedef struct Fader {
    s32 start;
    s32 end;
    s32 cnt;
    s32 frames;
} Fader;

#define HDR(c) ((u8 *)(c)->pad_a8)

typedef struct Ctx {
#ifdef HOST64
    u8 strm[136] __attribute__((aligned(8)));
#else
    u8 strm[0x5c];
#endif
    FSFile file;
    u32 a4;
    u8 pad_a8[0x18];
    u8 type;
    u8 c1;
    u8 c2;
    u8 c3;
    u16 rate;
    u16 c6;
    u8 pad_c8[4];
    u32 cc;
    u8 pad_d0[0x18];
    Fader fader;
    u8 pad_f8[0x18];
    struct {
        s32 a : 1;
        s32 b : 1;
        s32 c : 1;
        s32 d : 1;
        s32 e : 1;
        s32 f : 1;
        s32 g : 1;
    } fl;
    s32 v114;
    s32 v118;
    s32 pending;
    s32 users;
    u8 nch;
    u8 pad125;
    u8 chIdx[6];
    void *buf;
    u32 bufSize;
    s32 v134;
    s32 v138;
    void *cb;
    void *cbArg;
    s32 v144;
    s32 v148;
    struct Ctx **handle;
    s32 prio;
    s32 v154;
    s32 vol;
    u32 v15c;
} Ctx;

typedef struct Job {
    NNSFndLink link;
    Ctx *owner;
    s32 tag;
    s32 n;
    u32 buf[6];
    u32 size;
} Job;

typedef struct ThreadInfo {
    u8 thread[0x4c0];
    u32 queue[3];
    u8 mutex[0x18];
    NNSFndList list;
} ThreadInfo;

typedef struct SInfo {
    void *file;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
} SInfo;

typedef struct EffCtl {
    s32 type;
    void (*fn)();
    void (*pre)();
    void *preArg;
    void (*post)();
    void *postArg;
    union {
        struct { s32 a; s32 b; } e[24];
        s32 w[48];
    } u;
} EffCtl;

typedef struct ArcTbl {
    u8 pad[0x1c];
    u32 count;
    struct { u32 a; u32 b; u32 c; } ent[1];
} ArcTbl;

extern Ctx data_021fc650[4];
extern ThreadInfo data_021fc160;
extern ThreadInfo *data_021fbdac;
extern u8 data_021fc62c[0x18];
extern NNSFndList data_021fc644;
extern s32 data_021fbda8;
extern NNSFndList data_021fbdb4;
extern u8 data_021fbdc0[0x18];
extern Job data_021fbdd8[8];
extern void *data_021fbdb0;
extern u8 data_021fbf60[];
extern EffCtl data_0213bf10;
#define data_0213bf28 HOST_LABEL(s32 (*)[], data_0213bf28)
extern s16 data_02139fb4[];

extern void *NNS_FndGetNextListObject(NNSFndList *, void *);
extern void NNS_FndRemoveListObject(NNSFndList *, void *);
extern void NNS_FndAppendListObject(NNSFndList *, void *);
extern void NNS_FndInitList(NNSFndList *, u16);
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void OS_CreateThread(void *, void *, void *, void *, u32, u32);
extern void OS_WakeupThreadDirect(void *);
extern void MI_CpuFill8(u32, u32, u32);
extern void MIi_CpuClear16(u32, void *, u32);
extern void MIi_CpuCopyFast();
extern void DC_FlushRange(void *, u32);
extern void SND_SetSurroundDecay(u32);
extern void FS_CloseFile(void *);
extern BOOL FS_OpenFileFast(void *, FSFileID);
extern void NNS_SndStrmSetChannelPan(Ctx *, s32, s32);
extern void NNS_SndStrmSetVolume(Ctx *, s32);
extern void NNS_SndStrmStop(Ctx *);
extern void NNS_SndStrmStart(Ctx *);
extern BOOL NNS_SndStrmSetup();
extern void NNS_SndStrmFreeChannel(Ctx *);
extern BOOL NNS_SndStrmAllocChannel();
extern void NNS_SndStrmInit(Ctx *);
extern void NNS_SndCaptureStartEffect();
extern s32 NNS_SndArcReadFile();
extern u32 NNS_SndArcGetFileOffset();
extern u8 *NNS_SndArcGetStrmPlayerInfo();
extern SInfo *NNS_SndArcGetStrmInfo();
extern void *NNS_SndHeapAlloc();

void RequestNextStrm(Ctx *);
void StrmDataCallback(s32, s32, u32 *, u32, s32, Ctx *);
void FreeCommandBuffer(Job *);
Job *AllocCommandBuffer(void);
Job *PopCommandBuffer(NNSFndList *);
void RemoveCommandByPlayer(NNSFndList *, Ctx *);
void CreateStrmThread(ThreadInfo *, u32);
void FreeChannel(Ctx *);
BOOL AllocChannel();
void ShutdownPlayer__sndarc_stream(Ctx *);
void ForceStopStrm__sndarc_stream(Ctx *);
void StopStrm(Ctx *, s32);
BOOL PrepareStrmCore();
void FreePlayer(Ctx *);
Ctx *AllocPlayer(Ctx **, s32, s32);
void NNS_SndStrmHandleRelease(Ctx **);
void NNS_SndArcStrmStartPrepared(Ctx **);
BOOL NNS_SndArcStrmPrepare(Ctx **, s32, s32);
BOOL SetupStrmPlayers(void *);
void OutputEffectHeadphone();
void OutputEffectMono();
void OutputEffectSurround();
void OutputEffectCallback();
void NNS_SndCaptureChangeOutputEffect(s32);
BOOL NNSi_SndFaderIsFinished(Fader *);
void NNSi_SndFaderInit(Fader *);
s32 NNSi_SndFaderGet(Fader *);
void NNSi_SndFaderSet(Fader *, s32, s32);
void NNSi_SndFaderUpdate(Fader *);

void GXx_SetMasterBrightness_(u16 *p, s32 v)
{
    if (v == 0) {
        *p = 0;
    } else if (v > 0) {
        *p = v | 0x4000;
    } else {
        *p = (-v) | 0x8000;
    }
}

void NNSi_SndFaderInit(Fader *f)
{
    f->end = 0;
    f->start = f->end;
    f->frames = 0;
    f->cnt = f->frames;
}

void NNSi_SndFaderSet(Fader *f, s32 target, s32 frames)
{
    f->start = NNSi_SndFaderGet(f);
    f->end = target;
    f->frames = frames;
    f->cnt = 0;
}

s32 NNSi_SndFaderGet(Fader *f)
{
    s32 start;
    if (f->cnt >= f->frames) return f->end;
    start = f->start;
    return start + DS_DIV((f->cnt * (f->end - start)), f->frames);
}

void NNSi_SndFaderUpdate(Fader *f)
{
    if (f->cnt < f->frames) f->cnt++;
}

BOOL NNSi_SndFaderIsFinished(Fader *f)
{
    return f->cnt >= f->frames;
}

void *NNSi_SndSeqArcGetSeqInfo(ArcTbl *t, s32 i)
{
    if (i < 0) return 0;
    if ((u32)i >= t->count) return 0;
    if (t->ent[i].a == (u32)-1) return 0;
    return &t->ent[i];
}

void NNS_SndCaptureStartOutputEffect(void *a, u32 b, s32 effect)
{
    NNS_SndCaptureChangeOutputEffect(effect);
    NNS_SndCaptureStartEffect(a, b, 0, 32000, 2, OutputEffectCallback, &data_0213bf10);
}

void NNS_SndCaptureChangeOutputEffect(s32 effect)
{
    u32 irq;
    volatile u16 zero;
    if (effect == data_0213bf10.type) return;
    if (data_0213bf10.type == 1) SND_SetSurroundDecay(0);
    irq = OS_DisableInterrupts();
    zero = 0;
    MIi_CpuClear16(zero, data_0213bf28, 0xc0);
    data_0213bf10.type = effect;
    switch (effect) {
    case 1:
        data_0213bf10.fn = OutputEffectSurround;
        break;
    case 2:
        data_0213bf10.fn = OutputEffectHeadphone;
        break;
    case 3:
        data_0213bf10.fn = OutputEffectMono;
        break;
    case 0:
        data_0213bf10.fn = OutputEffectNormal;
        break;
    default:
        data_0213bf10.fn = OutputEffectNormal;
        break;
    }
    OS_RestoreInterrupts(irq);
    if (effect != 1) return;
    SND_SetSurroundDecay(0x3000);
}

void OutputEffectCallback(void *l, void *r, u32 len, s32 fmt, EffCtl *c)
{
    if (c->pre != 0) c->pre(l, r, len, fmt, c->preArg);
    c->fn(l, r, len, c);
    if (c->post != 0) c->post(l, r, len, fmt, c->postArg);
    DC_FlushRange(l, len);
    DC_FlushRange(r, len);
}

void OutputEffectNormal(void)
{
}

void OutputEffectSurround(s16 *l, s16 *r, u32 len, EffCtl *c)
{
    s16 tmp[2];
    u32 n = len >> 1;
    s16 *lp;
    s16 *rp;
    s32 i;
    s32 d;
    s16 *p;
    s16 *q;
    s32 t, x, y;
    i = 0;
    lp = l + n;
    rp = r + n;
    for (; i < 2; i++) {
        d = (l + n + i)[-2] - (r + n + i)[-2];
        tmp[i] = (d < -32768) ? -32768 : (d > 32767) ? 32767 : d;
    }
    p = l + (n - 1);
    q = r + (n - 1);
    if (p >= l + 2) {
        do {
            t = p[-2] - q[-2];
            x = p[0] + t;
            y = q[0] - t;
            if (t >= 0) {
                if (x < 32767) p[0] = x; else p[0] = 32767;
                if (y > -32768) q[0] = y; else q[0] = -32768;
            } else {
                if (x > -32768) p[0] = x; else p[0] = -32768;
                if (y < 32767) q[0] = y; else q[0] = 32767;
            }
            p--;
            q--;
        } while (p >= l + 2);
    }
    for (i = 1; i >= 0; i--) {
        x = l[i] + c->u.w[i];
        l[i] = (x < -32768) ? -32768 : (x > 32767) ? 32767 : x;
        y = r[i] - c->u.w[i];
        r[i] = (y < -32768) ? -32768 : (y > 32767) ? 32767 : y;
    }
    for (i = 0; i < 2; i++) {
        c->u.w[i] = tmp[i];
    }
}

EffCtl data_0213bf10 = {-1};

#include "host_labels.h"

HOST_LABEL_DEFINE(data_0213bf28, (char *)&data_0213bf10.u.w[0]);

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;
#define NULL 0
typedef enum { SND_WAVE_FORMAT_PCM8, SND_WAVE_FORMAT_PCM16 } SNDWaveFormat;
typedef struct NNSFndLink { void *prev; void *next; } NNSFndLink;
typedef struct NNSFndList { void *head; void *tail; u16 num; u16 offset; } NNSFndList;
#include "ds_div.h"
#include "sys/PMCbInfo.h"
#include "proto/autoload_2/unk_0210a9c4.h"
typedef struct Strm {
    NNSFndLink link;
    PMCbInfo pm0;
    PMCbInfo pm1;
    s32 fmt;
    struct { s32 setup : 1; s32 started : 1; } f;
    u32 blockSize;
    s32 blkCount;
    void *cb;
    void *arg;
    s32 blk;
    u32 timer;
    s32 alarm;
    u32 chMask;
    s32 chCount;
    u8 chIdx[16];
} Strm;
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
typedef struct CapMsg { Cap *cap; u32 size; u32 off; u8 *l; u8 *r; } CapMsg;

extern s32 data_021fb6a4;
extern NNSFndList data_021fb6a8;
extern Cap data_021fb7b4;
extern void NNS_FndInitList(NNSFndList *, u16);
extern void BeginSleep__stream(void *);
extern void EndSleep__stream(void *);
extern void AlarmCallback(Cap *);
extern void NNS_SndUnlockChannel(u32);
extern u32 NNS_SndLockChannel(u32);
extern s32 OS_ReceiveMessage();
extern s32 OS_SendMessage();
extern void DC_InvalidateRange(void *, u32);
extern void DC_FlushRange(void *, u32);
extern void MIi_CpuClear32(u32, void *, u32);
extern void SND_StartTimer(u32, u32, u32, u32);
extern void SND_StopTimer(u32, u32, u32, u32);
extern u32 SND_GetCurrentCommandTag(void);
extern u32 SND_WaitForCommandProc(u32);
extern u32 SND_FlushCommand(u32);
extern void NNS_SndUnlockCapture(u32);
extern void NNS_SndFreeAlarm(s32);
extern void SND_SetOutputSelector(u32, u32, u32, u32);
extern u32 data_027e038c;
extern s32 data_027e0390;
extern CapMsg data_021fb808[];
extern u32 data_021fb774;
extern s32 NNS_SndAllocAlarm(void);
extern BOOL NNS_SndLockCapture(u32);
extern void SND_SetupChannelPcm(s32 ch, s32 format, void *data, s32 loop, s32 loopStart, s32 loopLen, s32 volume,
                                s32 shift, s32 timer, s32 pan);
extern void SND_SetupCapture(s32 cap, s32 format, void *buf, u32 len, BOOL loop, s32 in, s32 out);
extern void SND_SetupAlarm(s32 alarm, u32 tick, u32 period, void (*cb)(Cap *), void *arg);
extern void NNSi_SndFaderInit(void *);
extern void NNSi_SndFaderSet(void *, s32, s32);

BOOL NNSi_SndCaptureStart(s32 type, void *buffer0, void *buffer1, u32 bufLen, s32 format, s32 input, s32 output, BOOL loopFlag,
                          int sampleRate, int volume, int pan0, int pan1, int interval, CapCb callback, void *arg)
{
    SNDWaveFormat wave_format;
    s32 capture_format;
    u32 chBitMask     = 0;
    u32 playChBitMask = 0;
    u32 capBitMask    = 0;
    int alarmNo       = -1;
    unsigned int samples;
    int timer;
    u32 alarmTimer;
    u32 alarmOffset;
    BOOL is8bit;
    Cap *cap = &data_021fb7b4;

    DC_FlushRange(buffer0, bufLen);
    DC_FlushRange(buffer1, bufLen);

    is8bit = format == 1 ? 1 : 0;

    timer = DS_DIV(16756991, sampleRate);

    if (callback != NULL)
    {
        samples = bufLen;
        if (!is8bit)
            samples >>= 1;

        timer      = ((timer + 16) & ~0x1f);
        alarmTimer = (timer >> 5) * (DS_UDIV(samples, interval));

        alarmOffset = 32;
        if (!is8bit)
            alarmOffset >>= 1;
        alarmOffset *= (timer >> 5);
    }

    wave_format    = is8bit ? SND_WAVE_FORMAT_PCM8 : SND_WAVE_FORMAT_PCM16;
    capture_format = is8bit ? 1 : 0;

    chBitMask |= (1 << 1) | (1 << 3);
    capBitMask |= (1 << 0) | (1 << 1);

    if (type != 2)
    {
        playChBitMask = chBitMask;
    }

    if (callback != NULL)
    {
        alarmNo = NNS_SndAllocAlarm();
        if (alarmNo < 0)
            return 0;
    }

    if (!NNS_SndLockCapture(capBitMask))
    {
        if (alarmNo >= 0)
            NNS_SndFreeAlarm(alarmNo);
        return 0;
    }

    if (!NNS_SndLockChannel(chBitMask))
    {
        if (alarmNo >= 0)
            NNS_SndFreeAlarm(alarmNo);
        NNS_SndUnlockCapture(capBitMask);
        return 0;
    }

    SND_SetupChannelPcm(1, wave_format, buffer0, loopFlag ? 1 : 2, 0, (int)(bufLen >> 2), volume, 0, timer, pan0);
    SND_SetupCapture(0, capture_format, buffer0, bufLen >> 2, loopFlag, input, output);
    SND_SetupChannelPcm(3, wave_format, buffer1, loopFlag ? 1 : 2, 0, (int)(bufLen >> 2), volume, 0, timer, pan1);
    SND_SetupCapture(1, capture_format, buffer1, bufLen >> 2, loopFlag, input, output);

    if (alarmNo >= 0)
    {
        SND_SetupAlarm(alarmNo, alarmTimer + alarmOffset, alarmTimer, AlarmCallback, cap);
    }

    if (type == 1)
    {
        SND_SetOutputSelector(1, 2, 1, 1);
    }

    SND_StartTimer(playChBitMask, capBitMask, alarmNo >= 0 ? (u32)(1 << alarmNo) : 0, 0);

    cap->active = 1;
    cap->mode       = type;
    cap->chMask     = chBitMask;
    cap->startCh = playChBitMask;
    cap->capMask    = capBitMask;
    cap->alarm       = alarmNo;
    cap->fmt    = format;
    cap->bufL   = buffer0;
    cap->bufR   = buffer1;
    cap->size    = bufLen;
    cap->blkSize = DS_UDIV(bufLen, interval);
    cap->blkIdx = 0;
    cap->nBlocks    = interval;
    cap->cb    = callback;
    cap->cbArg = arg;
    cap->vol = volume;
    NNSi_SndFaderInit(cap->fader);
    NNSi_SndFaderSet(cap->fader, volume << 8, 1);
    cap->faderOn = 0;
    return 1;
}

void NNSi_SndCaptureStop(void)
{
    BOOL hasAlarm;
    u32 tag;
    Cap *c = &data_021fb7b4;
    if (c->active == 0) {
        return;
    }
    hasAlarm = c->alarm >= 0;
    SND_StopTimer(c->startCh, c->capMask,
                  hasAlarm ? 1 << c->alarm : 0, 0);
    if (hasAlarm) {
        tag = SND_GetCurrentCommandTag();
        SND_FlushCommand(1);
        SND_WaitForCommandProc(tag);
        do {
        } while (OS_ReceiveMessage(&data_021fb774, 0, 0) != 0);
    }
    if (c->capMask != 0) {
        NNS_SndUnlockCapture(c->capMask);
    }
    if (c->chMask != 0) {
        NNS_SndUnlockChannel(c->chMask);
    }
    if (hasAlarm) {
        NNS_SndFreeAlarm(c->alarm);
    }
    if (c->mode == 1) {
        SND_SetOutputSelector(0, 0, 0, 0);
    }
    c->active = 0;
}

void NNSi_SndCaptureBeginSleep(void)
{
    Cap *c = &data_021fb7b4;
    u32 tag;
    if (c->active == 0) {
        return;
    }
    SND_StopTimer(c->startCh, c->capMask,
                  (c->alarm >= 0) ? 1 << c->alarm : 0, 0);
    tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(tag);
}

void NNSi_SndCaptureEndSleep(void)
{
    Cap *c = &data_021fb7b4;
    volatile u32 zero1;
    volatile u32 zero2;
    if (c->active == 0) {
        return;
    }
    c->blkIdx = 0;
    zero1 = 0;
    MIi_CpuClear32(zero1, c->bufL, c->size);
    zero2 = 0;
    MIi_CpuClear32(zero2, c->bufR, c->size);
    DC_FlushRange(c->bufL, c->size);
    DC_FlushRange(c->bufR, c->size);
    SND_StartTimer(c->startCh, c->capMask, (c->alarm >= 0) ? 1 << c->alarm : 0, 0);
}

void AlarmCallback(Cap *cap)
{
    u8 *l;
    u8 *r;
    u32 size;
    u32 off;
    size = cap->blkSize;
    off = size * cap->blkIdx;
    l = cap->bufL + off;
    r = cap->bufR + off;
    if (data_027e038c != 0) {
        CapMsg *m = &data_021fb808[data_027e0390];
        m->cap = cap;
        m->size = size;
        m->off = off;
        m->l = l;
        m->r = r;
        OS_SendMessage(&data_021fb774, m, 0);
        data_027e0390++;
        if (data_027e0390 >= 8) {
            data_027e0390 = 0;
        }
    } else {
        DC_InvalidateRange(l, size);
        DC_InvalidateRange(r, size);
        cap->cb(l, r, size, cap->fmt, cap->cbArg);
    }
    cap->blkIdx++;
    if (cap->blkIdx >= cap->nBlocks) {
        cap->blkIdx = 0;
    }
}

void CaptureThread(void *arg)
{
    void *m;
    CapMsg *msg;
    for (;;) {
        OS_ReceiveMessage(&data_021fb774, &m, 1);
        msg = (CapMsg *)m;
        DC_InvalidateRange(msg->l, msg->size);
        DC_InvalidateRange(msg->r, msg->size);
        msg->cap->cb(msg->l, msg->r, msg->size, msg->cap->fmt, msg->cap->cbArg);
    }
}

void NNS_SndStrmInit(Strm *st)
{
    if (data_021fb6a4 == 0) {
        NNS_FndInitList(&data_021fb6a8, 0);
        data_021fb6a4 = 1;
    }
    st->pm0.cb = (void (*)(void *))BeginSleep__stream;
    st->pm0.arg = st;
    st->pm1.cb = (void (*)(void *))EndSleep__stream;
    st->pm1.arg = st;
    st->chMask = 0;
    st->chCount = 0;
    st->f.setup = 0;
    st->f.started = 0;
}

BOOL NNS_SndStrmAllocChannel(Strm *st, s32 n, u8 *ch)
{
    u32 mask = 0;
    s32 i;
    for (i = 0; i < n; i++) {
        st->chIdx[i] = ch[i];
        mask |= 1 << ch[i];
    }
    if (NNS_SndLockChannel(mask) == 0) {
        return 0;
    }
    st->chCount = n;
    st->chMask = mask;
    return 1;
}

void NNS_SndStrmFreeChannel(Strm *st)
{
    if (st->chMask == 0) {
        return;
    }
    NNS_SndUnlockChannel(st->chMask);
    st->chMask = 0;
    st->chCount = 0;
}

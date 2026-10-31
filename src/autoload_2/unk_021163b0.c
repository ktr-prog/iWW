typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"

extern void *SND_AllocCommand(u32 n);
extern void SND_PushCommand(void *p);
extern u32 SNDi_SetAlarmHandler(u32 a, uptr b, uptr c);
extern void SNDi_IncAlarmId(u32 a);

extern void MI_SetWramBank(u32 v);
extern void MI_StopDma(u32 dmaNo);

void PushCommand_impl(u32 cmd, uptr a, uptr b, uptr c, uptr d);
void SNDi_SetPlayerParam(u32 a, u32 b, u32 c, u32 d);
void SNDi_SetTrackParam(u32 a, u32 b, u32 c, u32 d, u32 e);

u32 SearchLZ(const u8 *startp, const u8 *nextp, u32 remainSize, u16 *offp);

typedef struct {
    u8 *destp;
    int destCount;
    u16 u8_;
    u8 u10;
    u8 b0b;
    u8 b0c;
    u8 b0d;
    u8 b0e;
} UncompContextLZ;

void SND_SetPlayerVolume(u32 a, u32 b) { SNDi_SetPlayerParam(a, 6, b, 2); }

void SND_SetPlayerChannelPriority(u32 a, u32 b) { SNDi_SetPlayerParam(a, 4, b, 1); }

void SND_SetPlayerLocalVariable(u32 a, u32 b, u32 c) { PushCommand_impl(10, a, b, c, 0); }

void SND_SetPlayerGlobalVariable(u32 a, u32 b) { PushCommand_impl(11, a, b, 0, 0); }

void SND_SetTrackVolume(u32 a, u32 b, u32 c) { SNDi_SetTrackParam(a, b, 10, c, 2); }

void SND_SetTrackPitch(u32 a, u32 b, u32 c) { SNDi_SetTrackParam(a, b, 12, c, 2); }

void SND_SetTrackPan(u32 a, u32 b, u32 c) { SNDi_SetTrackParam(a, b, 9, c, 1); }

void SND_SetTrackAllocatableChannel(u32 a, u32 b, u32 c) { PushCommand_impl(9, a, b, c, 0); }

void SND_StartTimer(u32 a, u32 b, u32 c, u32 d) { PushCommand_impl(12, a, b, c, d); }

void SND_StopTimer(u32 a, u32 b, u32 c, u32 d) {
    int i;
    u32 m = c;
    for (i = 0; i < 8 && m != 0; i++, m >>= 1) {
        if (m & 1) SNDi_IncAlarmId(i);
    }
    PushCommand_impl(13, a, b, c, d);
}

void SND_SetupCapture(u32 a, u32 b, uptr c, u32 d, u32 e, u32 f, u32 g) {
    PushCommand_impl(17, c, d, (a << 31) | (b << 30) | (e << 29) | (f << 28) | (g << 27), 0);
}

void SND_SetupAlarm(u32 a, u32 b, u32 c, uptr d, uptr e) {
    u32 x = SNDi_SetAlarmHandler(a, d, e);
    PushCommand_impl(18, a, b, c, x);
}

void SND_SetTrackMute(u32 a, u32 b, u32 c) { PushCommand_impl(8, a, b, c, 0); }

void SND_LockChannel(u32 a, u32 b) { PushCommand_impl(26, a, b, 0, 0); }

void SND_UnlockChannel(u32 a, u32 b) { PushCommand_impl(27, a, b, 0, 0); }

void SND_SetChannelVolume(u32 a, u32 b, u32 c) { PushCommand_impl(20, a, b, c, 0); }

void SND_SetChannelPan(u32 a, u32 b) { PushCommand_impl(21, a, b, 0, 0); }

void SND_SetupChannelPcm(u32 a0, u32 a1, uptr a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7, u32 a8, u32 a9) {
    PushCommand_impl(14, a0 | (a8 << 16), a2, a5 | ((a6 << 24) | (a7 << 22)), a4 | (((a3 << 26) | (a1 << 24)) | (a9 << 16)));
}

void SND_InvalidateSeqData(uptr a, uptr b) { PushCommand_impl(30, a, b, 0, 0); }

void SND_InvalidateBankData(uptr a, uptr b) { PushCommand_impl(31, a, b, 0, 0); }

void SND_InvalidateWaveData(uptr a, uptr b) { PushCommand_impl(32, a, b, 0, 0); }

void SND_SetMasterVolume(u32 a) { PushCommand_impl(23, a, 0, 0, 0); }

void SND_SetOutputSelector(u32 a, u32 b, u32 c, u32 d) { PushCommand_impl(25, a, b, c, d); }

void SND_ReadDriverInfo(uptr a) { PushCommand_impl(33, a, 0, 0, 0); }

void SNDi_SetPlayerParam(u32 a, u32 b, u32 c, u32 d) { PushCommand_impl(6, a, b, c, d); }

void SNDi_SetTrackParam(u32 a, u32 b, u32 c, u32 d, u32 e) { PushCommand_impl(7, a | (e << 24), b, c, d); }

void SND_SetSurroundDecay(u32 a) { PushCommand_impl(22, a, 0, 0, 0); }

typedef struct SndCommand {
    struct SndCommand *next;
    u32 id;
    uptr arg[4];
} SndCommand;

void PushCommand_impl(u32 cmd, uptr a, uptr b, uptr c, uptr d) {
    SndCommand *p = (SndCommand *)SND_AllocCommand(1);
    if (p == 0) return;
    p->id = cmd;
    p->arg[0] = a;
    p->arg[1] = b;
    p->arg[2] = c;
    p->arg[3] = d;
    SND_PushCommand(p);
}

void MI_Init(void) {
    MI_SetWramBank(3);
    MI_StopDma(0);
}

u32 MI_CompressLZ(const u8 *srcp, u32 size, u8 *dstp) {
    const u8 *src0 = srcp;
    u32 LZDstCount;
    u8 LZCompFlags;
    u8 i;
    u32 dstMax;
    u8 *LZCompFlagsp;
    u16 lastOffset;
    u32 lastLength;

    *(u32 *)dstp = (size << 8) | 0x10;
    dstp += 4;
    LZDstCount = 4;
    dstMax = size;
    while (size > 0) {
        LZCompFlags = 0;
        LZCompFlagsp = dstp++;
        LZDstCount++;
        for (i = 0; i < 8; i++) {
            LZCompFlags <<= 1;
            if (size > 0) {
                lastLength = SearchLZ(src0, srcp, size, &lastOffset);
                if (lastLength != 0) {
                    LZCompFlags |= 1;
                    if (LZDstCount + 2 >= dstMax) return 0;
                    *dstp++ = (u8)(((lastLength - 3) << 4) | ((lastOffset - 1) >> 8));
                    *dstp++ = (u8)(lastOffset - 1);
                    srcp += lastLength;
                    size -= lastLength;
                    LZDstCount += 2;
                } else {
                    *dstp++ = *srcp++;
                    size--;
                    LZDstCount++;
                    if (LZDstCount >= dstMax) return 0;
                }
            }
        }
        *LZCompFlagsp = LZCompFlags;
    }
    i = 0;
    while (((LZDstCount + i) & 3) != 0) {
        *dstp++ = 0;
        i++;
    }
    return LZDstCount;
}

u32 SearchLZ(const u8 *startp, const u8 *nextp, u32 remainSize, u16 *offp) {
    const u8 *searchp;
    const u8 *headp;
    const u8 *searchHeadp;
    u16 maxOffset;
    u32 maxLength = 2;
    u8 tmpLength;

    if (remainSize < 3) return 0;
    searchp = nextp - 4096;
    if (searchp < startp) searchp = startp;
    while (nextp - searchp >= 2) {
        headp = nextp;
        while (*headp != searchp[0] || headp[1] != searchp[1] || headp[2] != searchp[2]) {
            searchp++;
            if (nextp - searchp < 2) goto done;
        }
        searchHeadp = searchp + 3;
        headp += 3;
        tmpLength = 3;
        while (*headp == *searchHeadp) {
            tmpLength++;
            headp++;
            searchHeadp++;
            if (tmpLength == 18) break;
            if ((u32)(headp - nextp) >= remainSize) break;
        }
        if (tmpLength > maxLength) {
            maxLength = tmpLength;
            maxOffset = (u16)(nextp - searchp);
            if (tmpLength == 18) break;
        }
        searchp++;
    }
done:
    if (maxLength < 3) return 0;
    *offp = maxOffset;
    return maxLength;
}

void MI_InitUncompContextLZ(UncompContextLZ *ctx, u8 *dest, const u32 *src) {
    ctx->destp = dest;
    ctx->destCount = (int)(*src >> 8);
    ctx->b0b = 0;
    ctx->b0c = 0;
    ctx->b0d = 0;
    ctx->b0e = 0;
    ctx->u8_ = 0;
    ctx->u10 = 0;
}


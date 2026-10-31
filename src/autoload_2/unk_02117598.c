#include "uptr.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02116c0c.h"
#include "proto/autoload_2/unk_02116d24.h"
#include "proto/autoload_2/unk_02117518.h"
#include "proto/autoload_2/unk_02117598.h"
#include "proto/autoload_2/unk_02117e8c.h"
#include "proto/itcm/unk_01ffa3cc.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Cmd {
    struct Cmd *next;
    u32 id;
    uptr arg[4];
} Cmd;

typedef struct SndWork {
    u32 f0;
    u32 f4;
    u16 f8;
    u16 fa;
    u8 pad[0x14];
    struct {
        s16 v[16];
        u32 w;
    } t[16];
    s16 u[16];
} SndWork;

typedef struct Slot {
    void *a;
    struct Slot *next;
} Slot;

typedef struct Obj {
    u8 pad[0x18];
    Slot s[4];
} Obj;

typedef struct Pair {
    u32 a;
    u32 b;
} Pair;

typedef struct Bank {
    u8 pad[0x38];
    u32 count;
    u32 ent[1];
} Bank;

typedef struct H5 {
    u16 h[5];
} H5;

typedef struct H6 {
    u16 h[6];
} H6;

typedef union InstOut {
    u8 type;
    u16 h[6];
} InstOut;

typedef struct TrackOut {
    u16 a;
    u8 b;
    u8 c;
    s8 d;
    u8 e;
    u8 f;
    s8 g;
    u8 pad8;
    u8 cnt;
    u8 list[1];
} TrackOut;

typedef struct ChOut {
    u32 bit0 : 1;
    u32 bit1 : 1;
    u16 mask;
    u16 h6;
    u8 b8;
} ChOut;

typedef struct ChRec {
    u8 f0_0 : 1;
    u8 f0_1 : 1;
    u8 f0_2 : 1;
    u8 pad1[4];
    u8 b5;
    u8 pad6[2];
    u8 x[16];
    u16 h24;
    u8 pad26[10];
} ChRec;

typedef struct SlotEnt {
    uptr a;
    uptr b;
    u8 cnt;
} SlotEnt;

extern Cmd data_021fd260[256];
extern Cmd *data_021fcf88;
extern u32 data_021fcf8c;
extern Cmd *data_021fcf90;
extern Cmd *data_021fcf94;
extern Cmd *data_021fcf98;
extern s32 data_021fcf9c;
extern s32 data_021fcfa0;
extern s32 data_021fcfa4;
extern u32 data_021fcfa8;
extern Cmd *data_021fcfac[];
extern u32 data_021fcf6c;
extern u32 data_021fcf70;
extern SndWork data_021fcfe0;
extern SndWork *data_021fea60;
extern const u8 data_0213a0b4[724];
extern SlotEnt data_027e032c[];

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void OS_SpinWait(u32);
extern void PxiFifoCallback(void);
extern void DC_InvalidateRange(void *, u32);
extern void DC_StoreRange(void *, u32);
extern void DC_FlushRange(void *, u32);
extern void SNDi_SetPlayerParam(u32, u32, u32, u32);
extern void PushCommand_impl(u32, uptr, uptr, uptr, uptr);

typedef union PxiMsg {
    u32 raw;
    struct {
        u32 tag : 5;
        u32 err : 1;
        u32 data : 26;
    } b;
} PxiMsg;

#define reg_IPCSYNC (*(volatile u16 *)0x04000180)
#define reg_IPCFIFOCNT (*(volatile u16 *)0x04000184)
#define reg_IPCFIFOSEND (*(volatile u32 *)0x04000188)

s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err);
Cmd *AllocCommand(void);
u32 IsCommandAvailable(void);
u32 SND_CountWaitingCommand(void);
u32 SND_CountReservedCommand(void);
u32 SND_CountFreeCommand(void);
u32 SND_IsFinishedCommandTag(u32 t);
Cmd *SND_RecvCommandReply(u32 flags);
u32 SND_FlushCommand(u32 flags);
void SND_PushCommand(Cmd *c);
Cmd *SND_AllocCommand(u32 flags);
void SNDi_InitSharedWork(SndWork *w);
u32 SNDi_GetFinishedCommandTag(void);
extern void PXI_SetFifoRecvCallback(u32 tag, void (*cb)(void));
extern u32 PXI_IsCallbackReady(u32 tag, u32 proc);u32 SND_GetPlayerStatus(void) {
    DC_InvalidateRange((u8 *)data_021fea60 + 4, 4);
    return data_021fea60->f4;
}

s32 SND_GetPlayerLocalVariable(s32 a, s32 b) {
    DC_InvalidateRange(&data_021fea60->t[a].v[b], 2);
    return data_021fea60->t[a].v[b];
}

s32 SND_GetPlayerGlobalVariable(s32 idx) {
    DC_InvalidateRange(&data_021fea60->u[idx], 2);
    return data_021fea60->u[idx];
}

u32 SND_ReadPlayerInfo(u8 *w, s32 ch, ChOut *out) {
    ChRec *p;
    s32 i;
    if (ch < 0 || ch > 15) {
        return 0;
    }
    p = (ChRec *)(w + 0x540) + ch;
    out->mask = 0;
    for (i = 0; i < 16; i++) {
        if (p->x[i] != 0xff) {
            out->mask |= 1 << i;
        }
    }
    out->bit0 = p->f0_0;
    out->bit1 = p->f0_2;
    out->h6 = p->h24;
    out->b8 = p->b5;
    return 1;
}

u32 SND_ReadTrackInfo(u8 *w, s32 a, s32 b, TrackOut *o) {
    u8 *e;
    u8 *k;
    u32 v;
    u32 off;
    u32 bs;
    if (a < 0 || a > 15) {
        return 0;
    }
    if (b < 0 || b > 15) {
        return 0;
    }
    v = ((ChRec *)(w + 0x540) + a)->x[b];
    if (v == 0xff) {
        return 0;
    }
    e = w + 0x780 + v * 64;
    o->a = *(u16 *)(e + 2);
    o->b = e[4];
    o->c = e[5];
    o->d = *(s8 *)(e + 6);
    o->e = e[7];
    o->f = *(s8 *)(e + 8) + 64;
    o->g = *(s8 *)(e + 19);
    off = *(u32 *)(e + 0x3c);
    bs = *(u32 *)(w + 0x11c0);
    k = off == 0 ? 0 : w + (off - bs);
    o->cnt = 0;
    while (k != 0) {
        o->list[o->cnt] = k[0];
        o->cnt++;
        bs = *(u32 *)(w + 0x11c0);
        off = *(u32 *)(k + 0x50);
        k = off == 0 ? 0 : w + (off - bs);
    }
    return 1;
}

u32 SNDi_GetFinishedCommandTag(void) {
    DC_InvalidateRange(data_021fea60, 4);
    return data_021fea60->f0;
}

void SNDi_InitSharedWork(SndWork *w) {
    s32 i;
    s32 j;
    w->f4 = 0;
    w->f8 = 0;
    w->fa = 0;
    w->f0 = 0;
    for (i = 0; i < 16; i++) {
        w->t[i].w = 0;
        for (j = 0; j < 16; j++) {
            w->t[i].v[j] = -1;
        }
    }
    for (j = 0; j < 16; j++) {
        w->u[j] = -1;
    }
    DC_FlushRange(w, 0x280);
}

SndWork *data_021fea60;

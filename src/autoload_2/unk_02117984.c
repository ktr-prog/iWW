#include "uptr.h"
#include "host_ptr32.h"
#include "nitro/io_access.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02116c0c.h"
#include "proto/autoload_2/unk_02116d24.h"
#include "proto/autoload_2/unk_02117518.h"
#include "proto/autoload_2/unk_02117984.h"
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
extern u32 PXI_IsCallbackReady(u32 tag, u32 proc);
s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err) {
    PxiMsg m;
    u32 e;
    m.b.tag = tag;
    m.b.err = err;
    m.b.data = data;
    if (IO_R(&reg_IPCFIFOCNT) & 0x4000) {
        IO_OR(&reg_IPCFIFOCNT, 0xc000);
        return -1;
    }
    e = OS_DisableInterrupts();
    if (IO_R(&reg_IPCFIFOCNT) & 2) {
        OS_RestoreInterrupts(e);
        return -2;
    }
    IO_W(&reg_IPCFIFOSEND, m.raw);
    OS_RestoreInterrupts(e);
    return 0;
}

void PXI_Init(void) {
    PXI_InitFifo();
}

typedef struct Slot32 {
    u32 a;
    u32 next;
} Slot32;
typedef struct Obj32 {
    u8 pad[0x18];
    Slot32 s[4];
} Obj32;
#define P32(v) HostPtr32_Get(v)
#define U32(p) HostPtr32_Of(p)

void SND_AssignWaveArc(Obj *p_, s32 i, Obj *item_) {
    Obj32 *p = (Obj32 *)p_, *item = (Obj32 *)item_;
    Obj32 *old;
    SNDi_LockMutex();
    old = (Obj32 *)P32(p->s[i].a);
    if (old != 0) {
        Slot32 *q;
        if (item == old) {
            SNDi_UnlockMutex();
            return;
        }
        q = (Slot32 *)P32(old->s[0].a);
        if (&p->s[i] == q) {
            old->s[0].a = p->s[i].next;
            DC_StoreRange(P32(p->s[i].a), 0x3c);
        } else {
            if (q != 0) {
                Slot32 *n;
                do {
                    n = (Slot32 *)P32(q->next);
                    if (&p->s[i] == n) {
                        break;
                    }
                    q = n;
                } while (n != 0);
            }
            q->next = p->s[i].next;
            DC_StoreRange(q, 8);
        }
    }
    {
        u32 prev = item->s[0].a;
        item->s[0].a = U32(&p->s[i]);
        p->s[i].next = prev;
        p->s[i].a = U32(item);
    }
    SNDi_UnlockMutex();
    DC_StoreRange(p, 0x3c);
    DC_StoreRange(item, 0x3c);
}

void SND_DestroyBank(Obj *p_) {
    Obj32 *p = (Obj32 *)p_;
    s32 i;
    SNDi_LockMutex();
    for (i = 0; i < 4; i++) {
        Obj32 *o = (Obj32 *)P32(p->s[i].a);
        if (o != 0) {
            Slot32 *q = (Slot32 *)P32(o->s[0].a);
            if (&p->s[i] == q) {
                o->s[0].a = p->s[i].next;
                DC_StoreRange(o, 0x3c);
            } else {
                if (q != 0) {
                    Slot32 *n;
                    do {
                        n = (Slot32 *)P32(q->next);
                        if (&p->s[i] == n) {
                            break;
                        }
                        q = n;
                    } while (n != 0);
                }
                q->next = p->s[i].next;
                DC_StoreRange(q, 8);
            }
        }
    }
    SNDi_UnlockMutex();
}

void SND_DestroyWaveArc(Obj *p_) {
    Obj32 *p = (Obj32 *)p_;
    Slot32 *n;
    SNDi_LockMutex();
    n = (Slot32 *)P32(p->s[0].a);
    if (n != 0) {
        do {
            Slot32 *nx = (Slot32 *)P32(n->next);
            n->a = 0;
            n->next = 0;
            DC_StoreRange(n, 8);
            n = nx;
        } while (n != 0);
    }
    SNDi_UnlockMutex();
}

void SND_GetFirstInstDataPos(Pair *p) {
    Pair t;
    t.a = 0;
    t.b = 0;
    *p = t;
}

u32 SND_GetNextInstData(Bank *b, InstOut *out, u32 *idx) {
    while (idx[0] < b->count) {
        u32 e;
        e = b->ent[idx[0]];
        out->type = e;
        switch (out->type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5: {
            u16 *p = (u16 *)((u8 *)b + (e >> 8));
            *(H5 *)&out->h[1] = *(H5 *)p;
            idx[0]++;
            return 1;
        }
        case 16: {
            u8 *p = (u8 *)b + (e >> 8);
            while (idx[1] < (u32)(p[1] - p[0] + 1)) {
                u16 *q = (u16 *)(p + idx[1] * 12);
                *(H6 *)out = *(H6 *)(q + 1);
                idx[1]++;
                return 1;
            }
            break;
        }
        case 17: {
            u8 *p = (u8 *)b + (e >> 8);
            while (idx[1] < 8) {
                if (p[idx[1]] == 0) {
                    break;
                }
                {
                    u16 *q = (u16 *)(p + idx[1] * 12);
                    *(H6 *)out = *(H6 *)(q + 4);
                    idx[1]++;
                    return 1;
                }
            }
            break;
        }
        }
        idx[0]++;
        idx[1] = 0;
    }
    return 0;
}

u32 SND_GetWaveDataCount(Bank *b) {
    return b->count;
}

void SND_SetWaveDataAddress(u8 *base, s32 i, const void *p) {
    SNDi_LockMutex();
    *(u32 *)(base + i * 4 + 0x3c) = HostPtr32_Of(p);
    DC_StoreRange(base + 0x3c + i * 4, 4);
    SNDi_UnlockMutex();
}

void *SND_GetWaveDataAddress(u8 *base, s32 i) {
    u32 off;
    u8 *r;
    SNDi_LockMutex();
    off = *(u32 *)(base + i * 4 + 0x3c);
    if (off != 0) {
        r = (u8 *)HostPtr32_Get(off);
        if (off < 0x2000000) {
            r = base + off;
        }
    } else {
        r = 0;
    }
    SNDi_UnlockMutex();
    return r;
}

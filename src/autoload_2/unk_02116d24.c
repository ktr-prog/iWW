#include "nitro/pxi_ptr.h"
#include "uptr.h"
#include "proto/autoload_2/unk_02114410.h"
#include "proto/autoload_2/unk_02116c0c.h"
#include "proto/autoload_2/unk_02116d24.h"
#include "proto/autoload_2/unk_02117518.h"
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
extern Cmd *data_021fcfac[13];
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
void SND_CommandInit(void) {
    s32 i;
    Cmd *p;
    InitPXI();
    p = data_021fd260;
    data_021fcf88 = p;
    for (i = 0; i < 255; i++) {
        p->next = &data_021fd260[i + 1];
        p++;
    }
    data_021fd260[255].next = 0;
    data_021fcf98 = &data_021fd260[255];
    data_021fcf90 = 0;
    data_021fcf94 = 0;
    data_021fcfa4 = 0;
    data_021fcf9c = 0;
    data_021fcfa0 = 0;
    data_021fcfa8 = 1;
    data_021fcf8c = 0;
    data_021fea60 = &data_021fcfe0;
    SNDi_InitSharedWork(&data_021fcfe0);
    {
        Cmd *c = SND_AllocCommand(1);
        if (c == 0) {
            return;
        }
        c->id = 29;
        c->arg[0] = (uptr)data_021fea60;
        SND_PushCommand(c);
        SND_FlushCommand(1);
    }
}

Cmd *SND_RecvCommandReply(u32 flags) {
    u32 e = OS_DisableInterrupts();
    Cmd *c;
    Cmd *last;
    s32 idx;
    if (flags & 1) {
        while (data_021fcf8c == SNDi_GetFinishedCommandTag()) {
            OS_RestoreInterrupts(e);
            OS_SpinWait(100);
            e = OS_DisableInterrupts();
        }
    } else {
        if (data_021fcf8c == SNDi_GetFinishedCommandTag()) {
            OS_RestoreInterrupts(e);
            return 0;
        }
    }
    idx = data_021fcf9c;
    c = data_021fcfac[idx];
    data_021fcf9c = idx + 1;
    if (data_021fcf9c > 8) {
        data_021fcf9c = 0;
    }
    last = c;
    if (last->next != 0) {
        do {
            last = last->next;
        } while (last->next != 0);
    }
    if (data_021fcf98 != 0) {
        data_021fcf98->next = c;
    } else {
        data_021fcf88 = c;
    }
    data_021fcf98 = last;
    data_021fcfa4 = data_021fcfa4 - 1;
    data_021fcf8c = data_021fcf8c + 1;
    OS_RestoreInterrupts(e);
    return c;
}

Cmd *SND_AllocCommand(u32 flags) {
    Cmd *c;
    if (!IsCommandAvailable()) {
        return 0;
    }
    c = AllocCommand();
    if (c != 0) {
        return c;
    }
    if (!(flags & 1)) {
        return 0;
    }
    if ((s32)SND_CountWaitingCommand() > 0) {
        while (SND_RecvCommandReply(0) != 0) {
        }
        c = AllocCommand();
        if (c != 0) {
            return c;
        }
    } else {
        SND_FlushCommand(1);
    }
    RequestCommandProc();
    do {
        SND_RecvCommandReply(1);
        c = AllocCommand();
    } while (c == 0);
    return c;
}

void SND_PushCommand(Cmd *c) {
    u32 e = OS_DisableInterrupts();
    if (data_021fcf94 == 0) {
        data_021fcf94 = c;
        data_021fcf90 = c;
    } else {
        data_021fcf94->next = c;
        data_021fcf94 = c;
    }
    c->next = 0;
    OS_RestoreInterrupts(e);
}

u32 SND_FlushCommand(u32 flags) {
    u32 e = OS_DisableInterrupts();
    if (data_021fcf90 == 0) {
        OS_RestoreInterrupts(e);
        return 1;
    }
    if (data_021fcfa4 >= 8) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(e);
            return 0;
        }
        do {
            SND_RecvCommandReply(1);
        } while (data_021fcfa4 >= 8);
    }
    DC_FlushRange(data_021fd260, 0x1800);
    if (PXI_SendWordByFifo(7, PXI_PointerWord(7, data_021fcf90), 0) < 0) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(e);
            return 0;
        }
        while (PXI_SendWordByFifo(7, PXI_PointerWord(7, data_021fcf90), 0) < 0) {
            OS_RestoreInterrupts(e);
            OS_SpinWait(100);
            e = OS_DisableInterrupts();
        }
    }
    if (flags & 2) {
        RequestCommandProc();
    }
    {
        s32 c4;
        u32 c8;
        data_021fcfac[data_021fcfa0] = data_021fcf90;
        data_021fcfa0 = data_021fcfa0 + 1;
        if (data_021fcfa0 > 8) {
            data_021fcfa0 = 0;
        }
        c4 = data_021fcfa4;
        c8 = data_021fcfa8;
        data_021fcf90 = 0;
        data_021fcf94 = 0;
        data_021fcfa4 = c4 + 1;
        data_021fcfa8 = c8 + 1;
    }
    OS_RestoreInterrupts(e);
    return 1;
}

u32 SND_WaitForCommandProc(u32 t) {
    u32 r = SND_IsFinishedCommandTag(t);
    if (r == 0) {
        while (SND_RecvCommandReply(0) != 0) {
        }
        r = SND_IsFinishedCommandTag(t);
        if (r == 0) {
            RequestCommandProc();
            r = SND_IsFinishedCommandTag(t);
            if (r == 0) {
                do {
                    SND_RecvCommandReply(1);
                    r = SND_IsFinishedCommandTag(t);
                } while (r == 0);
            }
        }
    }
    return r;
}

u32 SND_GetCurrentCommandTag(void) {
    u32 e = OS_DisableInterrupts();
    u32 r;
    if (data_021fcf90 == 0) {
        r = data_021fcf8c;
    } else {
        r = data_021fcfa8;
    }
    OS_RestoreInterrupts(e);
    return r;
}

u32 SND_IsFinishedCommandTag(u32 t) {
    u32 e = OS_DisableInterrupts();
    u32 r;
    u32 cur = data_021fcf8c;
    if (t > cur) {
        if ((t - cur) < 0x80000000) {
            r = 0;
        } else {
            r = 1;
        }
    } else {
        r = (cur - t) < 0x80000000;
    }
    OS_RestoreInterrupts(e);
    return r;
}

u32 SND_CountFreeCommand(void) {
    u32 e = OS_DisableInterrupts();
    u32 n = 0;
    Cmd *c = data_021fcf88;
    while (c != 0) {
        c = c->next;
        n++;
    }
    OS_RestoreInterrupts(e);
    return n;
}

u32 SND_CountReservedCommand(void) {
    u32 e = OS_DisableInterrupts();
    u32 n = 0;
    Cmd *c = data_021fcf90;
    while (c != 0) {
        c = c->next;
        n++;
    }
    OS_RestoreInterrupts(e);
    return n;
}

u32 SND_CountWaitingCommand(void) {
    u32 a = SND_CountFreeCommand();
    return 256 - a - SND_CountReservedCommand();
}

void InitPXI(void) {
    PXI_SetFifoRecvCallback(7, PxiFifoCallback);
    if (!IsCommandAvailable()) {
        return;
    }
    if (PXI_IsCallbackReady(7, 1) != 0) {
        return;
    }
    do {
        OS_SpinWait(100);
    } while (PXI_IsCallbackReady(7, 1) == 0);
}

void RequestCommandProc(void) {
    while (PXI_SendWordByFifo(7, 0, 0) < 0) {
    }
}

Cmd *AllocCommand(void) {
    u32 e = OS_DisableInterrupts();
    Cmd *c = data_021fcf88;
    if (c == 0) {
        OS_RestoreInterrupts(e);
        return 0;
    }
    data_021fcf88 = c->next;
    if (data_021fcf88 == 0) {
        data_021fcf98 = 0;
    }
    OS_RestoreInterrupts(e);
    return c;
}

u32 IsCommandAvailable(void) {
    u32 r;
    u32 e;
    if (OS_IsRunOnEmulator() == 0) {
        return 1;
    }
    e = OS_DisableInterrupts();
    *(volatile u32 *)0x04fff200 = 16;
    r = *(volatile u32 *)0x04fff200;
    OS_RestoreInterrupts(e);
    return r != 0;
}

u32 data_021fcf8c;
u32 data_021fcfa8;
Cmd *data_021fcf98;
Cmd *data_021fcf90;
Cmd *data_021fcf88;
Cmd *data_021fcf94;
s32 data_021fcf9c;
s32 data_021fcfa0;
s32 data_021fcfa4;
Cmd *data_021fcfac[13];
SndWork data_021fcfe0 __attribute__((aligned(32)));
Cmd data_021fd260[256] __attribute__((aligned(32)));

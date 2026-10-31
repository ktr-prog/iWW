#include "sys/OSThread.h"
#include "host_mem.h"
#include "proto/autoload_2/unk_02113088.h"
#include "proto/autoload_2/unk_02125c94.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef int BOOL;

typedef struct { s32 size; s32 count; s32 total; } WQCfg;
extern u8 *data_02200044;
extern WQCfg data_02200048;
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void MI_CpuFill8(void *, u32, u32);
extern void MI_CpuCopy8(void *, void *, u32);
extern s32 _s32_div_f(s32, s32);
extern s32 PXI_SendWordByFifo(s32, u32, u32);
extern void WaitByLoop(u32);
extern void OS_UnLockCartridge(u32);
extern u16 OS_ReadOwnerOfLockWord(volatile void *lock);
extern u32 OS_TryLockCartridge(u32);

typedef struct WJob WJob;
struct WJob {
    WJob *next;
    u32 busy : 1;
    u32 prio : 31;
    void (*pre)(WJob *);
    void (*post)(WJob *);
    u8 pad[0x10];
};
#define HEAD(sys) ((sys)->head)
typedef struct {
    OSThread thread;
    WJob *volatile head;
    WJob sentinel;
} WSys;
typedef struct {
    u32 addr;
    u32 size;
    u8 *ptr;
    u32 state;
} WSlot;
typedef struct {
    u32 f0;
    u8 pad[0x2c];
    WSlot slot[4];
} WSlotTab;

extern WSys *data_02200040;
extern u32 OS_GetThreadPriority(void *);
extern void OS_SetThreadPriority(void *, u32);
extern void OS_CreateThread(void *, void *, void *, void *, u32, u32);
extern void OS_WakeupThreadDirect(void *);
extern u32 WM_GetAllowedChannel(void);

typedef struct { u32 flag; u32 irq; } WLock;

typedef struct {
    u8 _0[0x40];
    u8 f40[0x4c4];
    u32 f504;
    u32 _508;
    u8 f50c;
    u8 f50d;
    u8 _50e[10];
    u16 f518;
    u16 f51a;
    void (*cb)();
    u8 _520[6];
    u16 f526;
    u16 f528;
    u16 f52a;
    u16 f52c;
} WS18;
extern WS18 *data_02200018;
extern u16 data_0213c20c;
extern u16 data_0213c210;
extern u16 data_0213c214;
extern u16 data_0213c218;
extern u32 WM_SetIndCallback(void *);
#define W8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define W16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(u32 *)((u8 *)(p) + (o)))
extern u8 *data_0220001c;
extern u32 data_0213c220;
extern void OS_SpinWait(u32);
extern u32 WM_SetParentParameter(void *, void *);
extern u32 WM_SetBeaconIndication(void *, u32);
extern u32 WMi_StartParentEx(void *, u32);
extern u32 WM_StartMPEx(void *, u32, u32, void *, u32, u32, u32, u32, u32, u32, u32);
extern u32 WM_End(void *);
extern void WM_SetPortCallback(u32, u32, u32);
typedef struct { u8 _0[0x131c]; u32 f131c; u32 f1320; u8 _1324[0x1340-0x1324]; u8 _1340[0x14e8-0x1340]; u32 state[15]; } WWork;
typedef struct { u16 id; u16 res; u16 sub; u16 f6; u16 f8; u16 fa; u16 fc; u16 fe; u16 f10; } WMsg2;

extern void MBi_CheckWmErrcode(u32, u32);
extern u32 WM_SetLifeTime(void *, u32, u32, u32, u32);
void MBi_ParentCallback(WMsg2 *m);

BOOL MBi_IsTaskAvailable(void);
BOOL MBi_IsTaskBusy(WJob *job);
void MBi_SetTask(WJob *job, void (*pre)(WJob *), void (*post)(WJob *), u32 prio);
BOOL IsGetAllRequestData(u32 n);
u8 *MBi_ReceiveRequestDataPiece(u8 *msg, u32 aid);
void MBi_TaskThread(WSys *sys);
typedef struct { u8 pad[4]; u16 cur; } WRot;

void CTRDGi_LockByProcessor(u32 a, WLock *st) {
    volatile u32 *const p = HW_SYSWORK(volatile u32, ctrdgLock);
    for (;;) {
        st->irq = OS_DisableInterrupts();
        st->flag = OS_ReadOwnerOfLockWord(p) & 0x40;
        if (st->flag != 0) return;
        if (OS_TryLockCartridge(a) == 0) return;
        OS_RestoreInterrupts(st->irq);
        WaitByLoop(1);
    }
}

void CTRDGi_UnlockByProcessor(u32 a, WLock *st) {
    if (st->flag == 0) OS_UnLockCartridge(a);
    OS_RestoreInterrupts(st->irq);
}

void CTRDGi_SendtoPxi(u32 x) {
    if (PXI_SendWordByFifo(13, x, 0) == 0) return;
    do {
        WaitByLoop(1);
    } while (PXI_SendWordByFifo(13, x, 0) != 0);
}

void MBi_SetChildMPMaxSize(s32 n) {
    data_02200048.size = n - 2;
    data_02200048.count = _s32_div_f(30, n - 2);
    data_02200048.total = 30;
}

void MBi_SetParentPieceBuffer(void *p) {
    data_02200044 = p;
    MI_CpuFill8(p, 0, 0x21c);
}

void MBi_ClearParentPieceBuffer(u32 n) {
    u32 i;
    if (data_02200044 == 0) return;
    i = n - 1;
    MI_CpuFill8(data_02200044 + i * 32, 0, 30);
    *(u32 *)(data_02200044 + i * 4 + 0x1e0) = 0;
}

u8 *MBi_MakeParentSendBuffer(u8 *src, u8 *dst) {
    u8 *p = dst;
    *p++ = *src;
    switch (*src) {
    case 4:
        *p++ = *(u16 *)(src + 2);
        *p++ = (*(u16 *)(src + 2) & 0xff00) >> 8;
        *p++ = *(u16 *)(src + 4);
        *p++ = (*(u16 *)(src + 4) & 0xff00) >> 8;
        break;
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        break;
    default:
        return 0;
    }
    return p;
}

u8 *MBi_SetRecvBufferFromChild(u8 *src, u8 *dst, u32 aid) {
    u8 *ret;
    dst[0] = src[0];
    switch (dst[0]) {
    case 7:
        if (IsGetAllRequestData(aid) != 0) return data_02200044 + (aid - 1) * 32;
        dst[2] = src[1];
        if (dst[2] > data_02200048.count) return 0;
        MI_CpuCopy8(src + 2, dst + 3, data_02200048.size);
        ret = MBi_ReceiveRequestDataPiece(dst, aid);
        break;
    case 8:
        ret = src + 3;
        *(u16 *)(dst + 2) = src[1] & 0xff;
        *(u16 *)(dst + 2) |= (src[2] << 8) & 0xff00;
        break;
    case 9:
        ret = src + 3;
        *(u16 *)(dst + 2) = src[1] & 0xff;
        *(u16 *)(dst + 2) |= (src[2] << 8) & 0xff00;
        MI_CpuCopy8(ret, dst + 4, data_02200048.size);
        ret += data_02200048.size;
        break;
    default:
        return 0;
    }
    return ret;
}

u8 *MBi_ReceiveRequestDataPiece(u8 *msg, u32 aid) {
    u32 j; u32 off; s32 i; u32 *w;
    u8 *base = data_02200044;
    if (base == 0) return 0;
    i = msg[2];
    if (i > data_02200048.count) return 0;
    j = aid - 1;
    off = j << 5;
    MI_CpuCopy8(msg + 3, base + j * 32 + i * data_02200048.size, data_02200048.size);
    ((u32 *)(data_02200044 + 0x1e0))[j] |= 1 << i;
    if (IsGetAllRequestData(aid) != 0) return data_02200044 + off;
    return 0;
}

BOOL IsGetAllRequestData(u32 n) {
    u16 i = 0;
    if (data_02200048.count > 0) {
        u32 m = *(u32 *)(data_02200044 + (n - 1) * 4 + 0x1e0);
        do {
            if (((1 << i) & m) == 0) return 0;
            i++;
        } while (i < data_02200048.count);
    }
    return 1;
}

void MBi_TaskThread(WSys *sys) {
    WJob *job;
    u32 irq;
    u32 irq2;
    u32 zero = 0;
    void (*post)(WJob *);
    u32 cur;
    u32 np;
    for (;;) {
        irq = OS_DisableInterrupts();
        while (HEAD(sys) == 0) {
            OS_SetThreadPriority(sys, zero);
            OS_SleepThread(NULL);
        }
        job = HEAD(sys);
        HEAD(sys) = HEAD(sys)->next;
        OS_SetThreadPriority(sys, job->prio);
        OS_RestoreInterrupts(irq);
        if (job->pre != 0) job->pre(job);
        irq2 = OS_DisableInterrupts();
        post = job->post;
        cur = OS_GetThreadPriority(sys);
        if (HEAD(sys) == 0) {
            np = zero;
        } else if (cur < HEAD(sys)->prio) {
            np = HEAD(sys)->prio;
        } else {
            np = cur;
        }
        if (np != cur) OS_SetThreadPriority(sys, np);
        job->next = 0;
        job->busy = 0;
        if (post != 0) post(job);
        if (job == &sys->sentinel) break;
        OS_RestoreInterrupts(irq2);
    }
    OS_ExitThread();
}

void MBi_InitTaskThread(WSys *sys, u32 size) {
    u32 irq = OS_DisableInterrupts();
    if (data_02200040 == 0) {
        u32 ss;
        data_02200040 = sys;
        MBi_InitTaskInfo(&sys->sentinel);
        sys->head = 0;
        ss = (size - 0xe4) & ~3;
        OS_CreateThread(sys, (void *)MBi_TaskThread, sys, (u8 *)sys + 0xe4 + ss, ss, 0);
        OS_WakeupThreadDirect(sys);
    }
    OS_RestoreInterrupts(irq);
}

BOOL MBi_IsTaskAvailable(void) {
    return data_02200040 != 0;
}

void MBi_InitTaskInfo(void *p) {
    MI_CpuFill8(p, 0, 0x20);
}

BOOL MBi_IsTaskBusy(WJob *job) {
    return job->busy ? 1 : 0;
}

void MBi_SetTask(WJob *job, void (*pre)(WJob *), void (*post)(WJob *), u32 prio) {
    WSys *sys = data_02200040;
    u32 irq;
    if (MBi_IsTaskAvailable() == 0) Fatal_Trap();
    if (job->busy != 0) Fatal_Trap();
    if (prio > 31) {
        u32 cur = OS_GetThreadPriority(sys);
        if (prio == 32) {
            prio = cur != 0 ? cur - 1 : 0;
        } else if (prio == 33) {
            prio = cur < 31 ? cur + 1 : 31;
        } else if (prio == 34) {
            prio = cur;
        } else {
            prio = 31;
        }
    }
    irq = OS_DisableInterrupts();
    job->busy = 1;
    job->prio = prio;
    job->pre = pre;
    job->post = post;
    if (HEAD(sys) == 0) {
        if (job == &sys->sentinel) data_02200040 = 0;
        HEAD(sys) = job;
        OS_WakeupThreadDirect(sys);
    } else {
        WJob *t = HEAD(sys);
        if (job == &sys->sentinel) {
            while (t->next != 0) t = t->next;
            t->next = job;
            data_02200040 = 0;
        } else if (t->prio > prio) {
            HEAD(sys) = job;
            job->next = t;
        } else {
            WJob *n;
            for (; (n = t->next) != 0 && n->prio <= prio; t = n) {
            }
            job->next = n;
            t->next = job;
        }
    }
    OS_RestoreInterrupts(irq);
}

void MBi_EndTaskThread(void (*post)(WJob *)) {
    u32 irq = OS_DisableInterrupts();
    if (MBi_IsTaskAvailable() != 0) MBi_SetTask(&data_02200040->sentinel, 0, post, 0);
    OS_RestoreInterrupts(irq);
}

void MBi_InitCache(void *p) {
    MI_CpuFill8(p, 0, 0x70);
}

void MBi_AttachCacheBuffer(WSlotTab *t, u32 addr, u32 size, u8 *ptr, u32 state) {
    u32 irq = OS_DisableInterrupts();
    WSlot *e = t->slot;
    WSlot *end = t->slot + 4;
    for (;;) {
        if (e >= end) Fatal_Trap();
        if (e->state == 0) {
            e->addr = addr;
            e->size = size;
            e->ptr = ptr;
            e->state = state;
            break;
        }
        e++;
    }
    OS_RestoreInterrupts(irq);
}

BOOL MBi_ReadFromCache(WSlotTab *t, u32 addr, void *src, u32 len) {
    BOOL ok = 0;
    u32 irq = OS_DisableInterrupts();
    WSlot *e = t->slot;
    WSlot *end = t->slot + 4;
    for (; e < end; e++) {
        if (e->state >= 2) {
            s32 off = addr - e->addr;
            if (off >= 0 && off + len <= e->size) {
                MI_CpuCopy8(e->ptr + off, src, len);
                ok = 1;
                t->f0 = ok;
                break;
            }
        }
    }
    OS_RestoreInterrupts(irq);
    return ok;
}

BOOL changeScanChannel(WRot *p) {
    u32 mask = WM_GetAllowedChannel();
    u16 lr;
    u16 n;
    u16 cur;
    if (mask == 0) return 0;
    cur = p->cur;
    n = 0;
    lr = cur;
    do {
        if ((mask & (1 << (lr - 1))) != 0) {
            if (cur != lr) {
                p->cur = lr;
                break;
            }
        }
        n++;
        lr = lr == 16 ? 1 : lr + 1;
    } while (n < 16);
    return 1;
}

BOOL MBi_IsSendEnabled(void) {
    BOOL r = 0;
    BOOL b = 0;
    BOOL a = 0;
    WS18 *s = data_02200018;
    if (s->f528 == 1) {
        if (s->f50c == 0) a = 1;
    }
    if (a) {
        if (s->f526 == 0) b = 1;
    }
    if (b) {
        if (s->f52a != 0) r = 1;
    }
    return r;
}

void MBi_OnInitializeDone(void) {
    MBi_CheckWmErrcode(0x80, WM_SetIndCallback((void *)MBi_ParentCallback));
    MBi_CheckWmErrcode(0x1d, WM_SetLifeTime((void *)MBi_ParentCallback, data_0213c218, data_0213c210, data_0213c20c, data_0213c214));
}

void MBi_ParentCallback(WMsg2 *m) {
    switch (m->id) {
    case 0:
        if (m->res != 0) {
            data_02200018->cb(0x100, m);
            return;
        }
        MBi_OnInitializeDone();
        return;
    case 29:
        if (m->res != 0) {
            data_02200018->cb(0x100, m);
            return;
        }
        MBi_CheckWmErrcode(7, WM_SetParentParameter((void *)MBi_ParentCallback, data_02200018));
        return;
    case 7:
        data_02200018->cb(21, m);
        MBi_CheckWmErrcode(25, WM_SetBeaconIndication((void *)MBi_ParentCallback, 1));
        return;
    case 25:
        if (m->res != 0) {
            data_02200018->cb(0x100, m);
            return;
        }
        MBi_CheckWmErrcode(8, WMi_StartParentEx((void *)MBi_ParentCallback, data_0213c220));
        return;
    case 8:
        if (m->res != 0) {
            data_02200018->cb(0x100, m);
            return;
        }
        switch (m->f8) {
        case 0:
            data_02200018->f52a = 0;
            data_02200018->f528 = 0;
            return;
        case 7:
            if (data_02200018->f526 == 1) return;
            data_02200018->f52a |= 1 << m->f10;
            data_02200018->cb(0, m);
            if (data_02200018->f528 == 0 && ((WWork *)data_0220001c)->f131c == 0) {
                u16 x;
                ((WWork *)data_0220001c)->f131c = 1;
                x = (data_02200018->f52c == 0) ? 1 : 0;
                MBi_CheckWmErrcode(14, WM_StartMPEx((void *)MBi_ParentCallback, data_02200018->f504, data_02200018->f51a, data_02200018->f40, data_02200018->f518, x, 0, 0, 0, 1, 1));
                return;
            }
            if (MBi_IsSendEnabled() == 0) return;
            data_02200018->cb(25, 0);
            return;
        case 9:
            data_02200018->f52a &= ~(1 << m->f10);
            data_02200018->cb(1, m);
            return;
        case 2:
            if (data_02200018->f526 == 1) return;
            data_02200018->cb(0x1c, m);
            return;
        default:
            data_02200018->cb(0x100, m);
            return;
        }
    case 14:
        ((WWork *)data_0220001c)->f131c = 0;
        switch (m->sub) {
        case 10:
            data_02200018->f528 = 1;
            data_02200018->cb(25, 0);
            return;
        case 11:
            data_02200018->cb(3, *(u32 *)&m->f8);
            return;
        default:
            data_02200018->cb(0x100, m);
            return;
        }
    case 15: {
        u32 cnt;
        u32 i;
        if (W32(data_0220001c + 0x7000, 0x4c8) != 0) {
            i = cnt = 0;
            do {
                if (((WWork *)data_0220001c)->state[i] != 0) {
                    cnt++;
                    if (cnt >= 2) break;
                }
                i++;
            } while (i < 15);
            if (cnt == 1) OS_SpinWait(0x32c8);
        }
        data_02200018->f50c = 0;
        if (m->res == 0) {
            data_02200018->cb(2, m);
            data_02200018->cb(25, 0);
            return;
        }
        if (m->res == 10) {
            data_02200018->cb(42, m);
            return;
        }
        data_02200018->cb(19, m);
        data_02200018->cb(25, 0);
        return;
    }
    case 1:
        if (W32(data_0220001c + 0x1000, 0x320) == 0) {
            if (m->res != 0) {
                data_02200018->f526 = 0;
                data_02200018->cb(0x100, m);
                return;
            }
            data_02200018->f52a = 0;
            data_02200018->f528 = 0;
            MBi_CheckWmErrcode(2, WM_End((void *)MBi_ParentCallback));
            return;
        }
        WM_SetPortCallback(1, 0, 0);
        WM_SetIndCallback(0);
    case 2:
        if (m->res != 0) {
            data_02200018->f526 = 0;
            data_02200018->cb(0x100, m);
            return;
        }
        data_02200018->f50d = 0;
        W16(data_0220001c + 0x1300, 0x16) = 0;
        data_02200018->cb(17, m);
        return;
    case 13:
        if (m->res != 0) return;
        data_02200018->f52a &= ~m->fa;
        return;
    case 128:
        switch (m->sub - 16) {
        case 0:
            data_02200018->cb(29, m);
            return;
        case 1:
            data_02200018->cb(31, m);
            return;
        case 2:
            data_02200018->cb(32, m);
            return;
        case 3:
            data_02200018->cb(33, m);
            return;
        case 6:
            Fatal_Trap();
            return;
        case 4:
        case 5:
        case 7:
            break;
        }
        break;
    default:
        data_02200018->cb(0x100, m);
        break;
    }
}

void MBi_ChildPortCallback(WMsg2 *m) {
    if (m->res != 0) return;
    if (m->sub == 7) return;
    if (m->sub == 9) return;
    if (m->sub != 21) return;
    data_02200018->cb(9, m);
}

u8 *data_02200044;
WSys *data_02200040;
WQCfg data_02200048;

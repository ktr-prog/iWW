#include "ds_div.h"
#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02122114.h"
#include "proto/autoload_2/unk_02122e24.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "host_ptr32.h"
typedef int s32;
typedef int BOOL;

#define W8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define W16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern u8 *data_0220001c;
extern u8 data_0213c200;
extern const u32 data_0213a3ec[3];
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void MI_CpuFill8(void *, u32, u32);
extern void MI_CpuCopy8(void *, void *, u32);
extern u32 func_0213335c(u32, u32);
extern void *MBi_MakeParentSendBuffer(void *, void *);
extern u32 IsChildAidValid(u32);
extern u32 MBi_BlockHeaderEnd(u32, u32, void *);
extern u8 *WM_ReadMPData(void *, u32);
extern u32 FS_OpenFileDirect(void *, void *, u32, u32, int);
extern u32 FS_ReadFile(void *, void *, u32);
extern void FS_CloseFile(void *);
extern u8 *MBi_SetRecvBufferFromChild(void *, void *, u32);
extern u32 MBi_calc_nextsendblock(u32, u32);
extern void MBi_ClearParentPieceBuffer(u32);
extern void MBi_CommParentSendData(void);
extern void MB_UpdateGameInfoMember(void *, void *, u32, u32);
extern u32 MBi_GetGgid(void);
extern u32 MBi_GetTgid(void);
extern u32 MBi_GetAttribute(void);
extern void MB_SendGameInfoBeacon(u32, u32, u32);
extern void MBi_CommCallParentError(u32, u32);
extern void MIi_CpuClearFast(u32, void *, u32);
typedef struct { u32 a[3]; u16 b[3]; u16 n; } WTab;
typedef struct { u32 w0, w4, w8, wc; } WSeg;
typedef struct { u8 pad[12]; WSeg seg[3]; } WSrc;
typedef struct { u32 a[3]; u16 b[4]; } WDst;
BOOL IsAbleToLoad(u32 idx, u32 addr, u32 size);
BOOL MBi_IsAbleToRecv(u32 idx, u32 addr, u32 size);
void MBi_CommChangeParentStateCallbackOnly(u32 a, u32 b, void *c);
void MBi_CommParentRecvDataPerChild(u8 *msg, u32 aid);
typedef struct { u8 id; u16 aid; u16 pad; } WMsg;
typedef struct { u32 f0, f4, f8, fc; } WJob;
typedef struct { u8 pad[0x14]; u32 f14; } WObj;
typedef struct { u8 pad[0x10]; WJob *job; WObj *obj; } WArg;
typedef struct { u8 f0 : 4; u8 aid : 4; } WEnt;
void MBi_CommChangeParentState(u32 a, u32 b, void *c);
typedef struct { u8 f0 : 4; u8 aid : 4; u8 pad[21]; } WEnt22;
typedef struct { u8 _0[0x14]; u32 f14; u8 f18; } WObj2;
typedef struct {
    u8 _0[0x5b8];
    WObj2 *obj;
    u8 _5bc[4];
    u16 f5c0;
    u16 f5c2;
    u16 f5c4;
    u16 f5c6;
    u16 f5c8;
    u8 f5ca;
    u8 _5cb[9];
} WPeer;
typedef struct {
    u8 _0[0x1318];
    u32 f1318;
    u8 _131c[0x1340 - 0x131c];
    WEnt22 ent[15];
    u16 f148a[15];
    u32 f14a8[15];
    void (*cb)();
    u32 state[15];
    u8 _1524[2];
    u8 slot[15];
    u8 cnt1535;
    u16 mask1536;
    u8 _1538[0x1754 - 0x1538];
    u16 st16[15];
    u8 buf1772[22];
    WPeer peer[16];
} WWork;
#define WK2 ((WWork *)data_0220001c)
BOOL MBi_MakeBlockInfoTable(WDst *dst, WSrc *src) {
    u16 *tab = dst->b;
    u8 i;
    u32 sum;
    sum = 0;
    if (src == 0) return 0;
    for (i = 0; i < 3; i++) {
        dst->a[i] = sum;
        sum += src->seg[i].w8;
    }
    tab[0] = 0;
    for (i = 0; i < 3; i++) {
        WSeg *e = &src->seg[i];
        u32 sz = W32(data_0220001c + 0x1000, 0x318);
        u32 len = e->w8;
        u16 nx = tab[i] + (u16)(DS_UDIV((len + sz - 1), sz));
        if (IsAbleToLoad(i, e->w4, len) == 0) return 0;
        if (i < 2) tab[i + 1] = nx;
        else W16(dst, 18) = nx;
    }
    return 1;
}
BOOL MBi_get_blockinfo(u32 *out, WTab *tbl, u32 v, u8 *t3) {
    s8 i;
    u8 *e;
    u32 d, diff;
    if (v >= tbl->n) return 0;
    i = 2;
    for (;;) {
        if (v >= tbl->b[i]) break;
        i--;
        if (i < 0) break;
    }
    if (i < 0) return 0;
    diff = v - tbl->b[i];
    d = diff * W32(data_0220001c + 0x1000, 0x318);
    e = t3 + 12 + i * 16;
    out[1] = W32(e, 8) - d;
    if (out[1] > W32(data_0220001c + 0x1000, 0x318)) out[1] = W32(data_0220001c + 0x1000, 0x318);
    out[2] = d + tbl->a[i];
    out[0] = d + W32(e, 0);
    W8(out, 12) = i;
    return 1;
}

BOOL MBi_IsAbleToRecv(u32 idx, u32 addr, u32 size) {
    switch (data_0213a3ec[idx]) {
    case 2:
        if (addr >= 0x27ffe00 && addr + size <= 0x27fff60) return 1;
        break;
    case 0:
        if (addr >= 0x2000000 && addr + size <= 0x22c0000) return 1;
        break;
    case 1:
        if (addr >= 0x22c0000) {
            if (addr + size <= 0x2300000) return 1;
        }
        if (addr >= 0x2000000 && addr + size <= 0x2300000) return 1;
        break;
    default:
        return 0;
    }
    return 0;
}

BOOL IsAbleToLoad(u32 idx, u32 addr, u32 size) {
    switch (data_0213a3ec[idx]) {
    case 0:
    case 2:
        return MBi_IsAbleToRecv(idx, addr, size);
    case 1:
        if (addr >= 0x2000000 && addr < 0x23fe800) {
            u32 end = addr + size;
            if (addr < 0x2300000) {
                if (end > 0x2300000) return 0;
            }
            if (end <= 0x2300000) return 1;
            if (end < 0x23fe800) {
                if (size <= 0x40000) return 1;
            }
            return 0;
        }
        if (addr >= 0x37f8000 && addr < 0x380f000) {
            return addr + size <= 0x380f000;
        }
        break;
    default:
        return 0;
    }
    return 0;
}
void MB_CommSetParentStateCallback(void (*cb)()) {
    u32 irq = OS_DisableInterrupts();
    W32(data_0220001c + 0x1000, 0x4e4) = HostPtr32_Of((const void *)cb);
    OS_RestoreInterrupts(irq);
}
u8 *MB_CommGetChildUser(u32 n) {
    u32 irq = OS_DisableInterrupts();
    if (data_0220001c != 0 && IsChildAidValid(n) != 0) {
        MI_CpuCopy8(data_0220001c + 0x1340 + (n - 1) * 22, data_0220001c + 0x1772, 22);
        OS_RestoreInterrupts(irq);
        return data_0220001c + 0x1772;
    }
    OS_RestoreInterrupts(irq);
    return 0;
}


BOOL MB_CommIsBootable(u32 n) {
    if (data_0220001c != 0 && IsChildAidValid(n) != 0) {
        if (W32(data_0220001c + (n - 1) * 4 + 0x1000, 0x4e8) == 7) return 1;
    }
    return 0;
}

BOOL MB_CommResponseRequest(u32 n, u32 kind) {
    u32 b, a, irq;
    irq = OS_DisableInterrupts();
    switch (kind) {
    case 0: a = 10; b = 4; break;
    case 1: a = 10; b = 3; break;
    case 2: a = 14; b = 2; break;
    case 3: a = 7; b = 5; break;
    default:
        OS_RestoreInterrupts(irq);
        return 0;
    }
    if (data_0220001c != 0 && IsChildAidValid(n) != 0) {
        u32 i = n - 1;
        u8 *w = data_0220001c;
        if (a == W32(w + i * 4 + 0x1000, 0x4e8)) {
            W16(w + i * 2 + 0x1700, 0x54) = b;
            OS_RestoreInterrupts(irq);
            return 1;
        }
    }
    OS_RestoreInterrupts(irq);
    return 0;
}

void MBi_CommChangeParentState(u32 a, u32 b, void *c) {
    if (IsChildAidValid(a) != 0) {
        W32(data_0220001c + (a - 1) * 4 + 0x1000, 0x4e8) = b;
    }
    MBi_CommChangeParentStateCallbackOnly(a, b, c);
}

void MBi_CommChangeParentStateCallbackOnly(u32 a, u32 b, void *c) {
    void (*cb)() = (void (*)())HostPtr32_Get(W32(data_0220001c + 0x1000, 0x4e4));
    if (cb != 0) cb(a, b, c);
}

const u32 data_0213a3ec[3] = {2, 0, 1};

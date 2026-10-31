#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02122114.h"
#include "proto/main/unk_0206d49c.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#include "uptr.h"
#include "host_ptr32.h"
typedef int s32;
typedef int BOOL;

#define W8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define W16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W32(p, o) (*(u32 *)((u8 *)(p) + (o)))

extern u8 *data_0220001c;
extern u8 data_0213c200;
extern u32 data_0213a3ec[];
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32);
extern void MI_CpuFill8(void *, u32, u32);
extern void MI_CpuCopy8(void *, void *, u32);
extern u32 func_0213335c(u32, u32);
extern void *MBi_MakeParentSendBuffer(void *, void *);
extern u32 IsChildAidValid(u32);
extern u32 MBi_BlockHeaderEnd(u32, u32, void *);
extern u8 *WM_ReadMPData(void *, u32);
extern BOOL FS_OpenFileDirect(FSFile *file, FSArc *arc, u32 start, u32 end, int id);
extern s32 FS_ReadFile(FSFile *file, void *dst, s32 len);
extern BOOL FS_CloseFile(FSFile *file);
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
typedef struct { u8 pad[0x10]; char name[4]; u32 f14; } WObj;
typedef struct { u8 pad[0x10]; u32 job; u32 obj; } WArg;
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
static inline void wsave(u32 idx, u8 *buf, u32 aid) {
    WK2->f14a8[idx] = *(u32 *)(buf + 20);
    WK2->f148a[idx] = *(u16 *)(buf + 46);
    MI_CpuCopy8(buf + 24, &WK2->ent[idx], 22);
    WK2->ent[idx].aid = (u8)aid;
}

#define PEER(x) ((u8 *)data_0220001c + (x) * 0x5d4)
void MBi_CommParentRecvDataPerChild(u8 *msg, u32 aid) {
    u8 buf[56];
    u8 x;
    u8 type;
    u32 state;
    u8 *p;
    u32 i;
    if (aid == 0) return;
    if (aid > 15) return;
    p = MBi_SetRecvBufferFromChild(msg + 10, buf, aid);
    type = buf[0];
    i = aid - 1;
    state = WK2->state[i];
    switch (type) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 11:
        break;
    case 7:
        if (state == 2) {

            if (p == 0) return;
            MI_CpuCopy8(p, buf + 20, 29);
            wsave(aid - 1, buf, aid);
            MBi_CommChangeParentState(aid, 10, buf + 24);
        }
        if (state != 10) return;
        x = p[28];
        {
            u8 cnt = 0;
            u8 *e;
            WObj2 *o;
            if (x >= 16 || W8((e = PEER(x)) + 0x1000, 0xd52) == 0 ||
                WK2->f14a8[i] != (o = (WObj2 *)(uptr)W32(e + 0x1000, 0xd40))->f14) {
                WK2->st16[i] = 4;
            } else {
                u16 mask = W16(e + 0x1d00, 0x4e);
                u8 j;
                for (j = 0; j < 16; j++) {
                    if (((1 << j) & mask) != 0) cnt++;
                }
                if (cnt >= o->f18) {
                    WK2->st16[i] = 0;
                    MBi_CommChangeParentState(aid, 11, 0);
                    return;
                }
            }
        }
        {
            u8 *sp = data_0220001c + i * 2 + 0x1700;
            switch (W16(sp, 0x54)) {
            case 3: {
                u32 bit = 1 << aid;
                if ((WK2->mask1536 & bit) != 0) return;
                WK2->cnt1535++;
                WK2->mask1536 |= bit;
                WK2->slot[aid - 1] = x;
                *(u16 *)(PEER(x) + 0x1d4e) |= bit;
                *(u16 *)(PEER(x) + 0x1d50) |= bit;
                WK2->st16[aid - 1] = 0;
                MBi_CommChangeParentState(aid, 5, 0);
                return;
            }
            case 4:
                W16(sp, 0x54) = 0;
                MBi_CommChangeParentState(aid, 4, 0);
                return;
            }
            return;
        }
    case 8:
        if (state == 5) {
            MBi_CommChangeParentState(aid, 14, 0);
            return;
        }
        if (state != 14) return;
        if (WK2->st16[i] != 2) return;
        {
            u32 off = WK2->slot[i] * 0x5d4;
            *(u16 *)(data_0220001c + off + 0x1d4c) |= 1 << aid;
            *(u16 *)(data_0220001c + off + 0x1d48) = 0;
            WK2->st16[i] = 0;
            MBi_CommChangeParentState(aid, 6, 0);
        }
        return;
    case 9:
        if (state != 6) return;
        {
            u32 x = WK2->slot[i];
            u32 off;
            if (x == 0xff) return;
            off = x * 0x5d4;
            *(u16 *)(data_0220001c + off + 0x1d4a) = MBi_calc_nextsendblock(*(u16 *)(data_0220001c + off + 0x1d4a), *(u16 *)(buf + 2));
        }
        return;
    case 10:
        if (state == 6) {
            u32 x = WK2->slot[i];
            u32 off;
            if (x == 0xff) return;
            off = x * 0x5d4;
            *(u16 *)(data_0220001c + off + 0x1d4c) &= ~(1 << aid);
            MBi_CommChangeParentState(aid, 7, 0);
            return;
        }
        if (state != 7) return;
        if (WK2->st16[i] != 5) return;
        WK2->st16[i] = 0;
        MBi_CommChangeParentState(aid, 8, 0);
        return;
    default:
        break;
    }
}
void MBi_CommParentRecvData(void *arg) {
    u16 i;
    u8 *w;
    for (i = 0; i < 16; i++) {
        w = data_0220001c + i * 0x5d4;
        if (W8(w + 0x1000, 0xd52) != 0) W16(w + 0x1d00, 0x4a) = 0;
    }
    for (i = 1; i <= 15; i++) {
        u16 *p = (u16 *)WM_ReadMPData(arg, i);
        if (p != 0 && *p != 0xffff && *p != 0) MBi_CommParentRecvDataPerChild((u8 *)p, i);
    }
}

u32 MBi_CommParentSendMsg(u8 a, u32 b) {
    u8 buf = a;
    MBi_MakeParentSendBuffer(&buf, data_0220001c);
    return MBi_BlockHeaderEnd(6, b, data_0220001c);
}
u32 MBi_CommParentSendDLFileInfo(void) {
    s8 best = -1;
    u16 mask = 0;
    WMsg msg;
    u8 cnt[16];
    u16 i;
    u8 j, k;
    void *ent;
    MI_CpuFill8(cnt, 0, 16);
    for (i = 1; i <= 15; i++) {
        if (W32(data_0220001c + (i - 1) * 4 + 0x1000, 0x4e8) == 5) {
            s8 idx = (s8)W8(data_0220001c + (i - 1) + 0x1500, 0x26);
            cnt[idx]++;
        }
    }
    k = data_0213c200;
    for (j = 0; j < 16; j++) {
        k = (k + 1) % 16;
        if (W8(data_0220001c + k * 0x5d4 + 0x1000, 0xd52) != 0 && cnt[k] != 0) {
            best = (s8)k;
            break;
        }
    }
    if (best == -1) return 21;
    data_0213c200 = best;
    for (i = 1; i <= 15; i++) {
        if (W32(data_0220001c + (i - 1) * 4 + 0x1000, 0x4e8) == 5) {
            if (best == (s8)W8(data_0220001c + (i - 1) + 0x1500, 0x26)) mask = mask | (1 << i);
        }
    }
    msg.id = 3;
    msg.aid = best;
    ent = MBi_MakeParentSendBuffer(&msg, data_0220001c);
    if (ent != 0) MI_CpuCopy8(data_0220001c + 0x1788 + best * 0x5d4, ent, 0xe4);
    return MBi_BlockHeaderEnd(0xea, mask, data_0220001c);
}
void MBi_ReloadCache(WArg *arg) {
    FSFile file;
    WJob *job;
    WObj *obj;
    u32 base;
    FSArc *rp;
    obj = HostPtr32_Get(arg->obj);
    job = HostPtr32_Get(arg->job);
    FS_InitFile(&file);
    base = job->f0;
    rp = FS_FindArchive(obj->name, obj->f14);
    if (FS_OpenFileDirect(&file, rp, base, base + job->f4, -1) != 0) {
        if (job->f4 == FS_ReadFile(&file, (void *)(uptr)job->f8, job->f4)) job->fc = 2;
        FS_CloseFile(&file);
    }
    if (job->fc == 2) return;
    Fatal_Trap();
}

u8 data_0213c200 = 0xff;

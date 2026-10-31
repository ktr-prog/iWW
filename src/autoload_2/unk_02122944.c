#include "proto/autoload_2/unk_02119020.h"
#include "proto/autoload_2/unk_02119434.h"
#include "proto/autoload_2/unk_02122114.h"
#include "proto/autoload_2/unk_02122944.h"
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
void MBi_CommParentCallback(int code, u8 *msg) {
    switch (code) {
    case 21:
        MBi_CommChangeParentState(0, 1, msg);
        break;
    case 0: {
        u16 a = W16(msg, 16);
        if (a != 0 && a < 16) MBi_CommChangeParentState(a, 2, msg);
        break;
    }
    case 1: {
        u16 a = W16(msg, 16);
        if (a == 0 || a >= 16) break;
        WK2->f148a[a - 1] = 0;
        MI_CpuFill8(&WK2->f14a8[W16(msg, 16) - 1], 0, 4);
        MI_CpuFill8(&WK2->ent[W16(msg, 16) - 1], 0, 22);
        MBi_ClearParentPieceBuffer(W16(msg, 16));
        WK2->st16[W16(msg, 16) - 1] = 0;
        {
            u32 aid = W16(msg, 16);
            u32 idx = aid - 1;
            u8 *w = data_0220001c;
            s8 none = -1;
            s8 sl = (s8)W8(w + idx + 0x1500, 0x26);
            if (sl != none) {
                u32 off = (u8)sl * 0x5d4;
                u32 nb = ~(1 << aid);
                *(u16 *)(w + off + 0x1d4e) &= nb;
                *(u16 *)(data_0220001c + off + 0x1d50) |= 1 << aid;
                ((s8 *)WK2->slot)[idx] = none;
                *(u16 *)(data_0220001c + off + 0x1d4c) &= nb;
            }
        }
        if ((WK2->mask1536 & (1 << W16(msg, 16))) != 0) {
            WK2->cnt1535--;
            WK2->mask1536 &= ~(1 << W16(msg, 16));
        }
        {
            u32 a2 = W16(msg, 16);
            if (WK2->state[a2 - 1] == 8) MBi_CommChangeParentState(a2, 9, 0);
        }
        MBi_CommChangeParentState(W16(msg, 16), 3, msg);
        WK2->state[W16(msg, 16) - 1] = 0;
        break;
    }
    case 3:
        MBi_CommParentRecvData(msg);
        break;
    case 25:
        MBi_CommParentSendData();
        break;
    case 28: {
        u8 i;
        u32 r5, r4, r2;
        for (i = 0; i < 16; i++) {
            u32 off = i * 0x5d4;
            u8 *w = data_0220001c;
            u8 *e = w + off;
            if (W8(e + 0x1000, 0xd52) != 0) {
                if (*(u16 *)(e + 0x1d50) != 0) {
                    MB_UpdateGameInfoMember(w + 0x186c + off, w + 0x1340, *(u16 *)(e + 0x1d4e), *(u16 *)(e + 0x1d50));
                    *(u16 *)(data_0220001c + off + 0x1d50) = 0;
                }
            }
        }
        r5 = MBi_GetGgid();
        r4 = MBi_GetTgid();
        r2 = MBi_GetAttribute();
        MB_SendGameInfoBeacon(r5, r4, r2);
        break;
    }
    case 255:
        switch (W16(msg, 2)) {
        case 1: case 4: case 5: case 6: case 8: case 9:
            MBi_CommCallParentError(0, 9);
            break;
        case 0: case 2: case 3: case 7: case 10: case 11: case 12: case 13: case 14: case 15:
        default:
            MBi_CommCallParentError(0, 8);
            break;
        }
        break;
    case 256:
        switch (W16(msg, 0)) {
        case 0: case 7: case 8: case 13: case 14: case 15: case 17: case 18: case 21: case 25: case 29:
            MBi_CommCallParentError(0, 9);
            break;
        case 1: case 2: case 3: case 4: case 5: case 6: case 9: case 10: case 11: case 12:
        case 16: case 19: case 20: case 22: case 23: case 24: case 26: case 27: case 28:
        default:
            MBi_CommCallParentError(0, 8);
            break;
        }
        break;
    case 17:
        break;
    }
    if (code != 17) return;
    {
        void (*cb)() = (void (*)())HostPtr32_Get(W32(data_0220001c + 0x1000, 0x4e4));
        volatile u32 zero = 0;
        MIi_CpuClearFast(zero, data_0220001c, 32000);
        data_0220001c = 0;
        if (cb == 0) return;
        cb(0, 12, 0);
    }
}

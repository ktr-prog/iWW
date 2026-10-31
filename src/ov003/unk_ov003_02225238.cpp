#include "town/TownBlockCell.h"
#pragma opt_loop_invariants off
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "field/BottleThrow.h"
#include "actor/Character.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02094810.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02224e68.h"
#include "proto/ov003/unk_ov003_02225108.h"
#include "proto/ov003/unk_ov003_02225238.h"
#include "proto/ov003/unk_ov003_02225800.h"
#include "proto/main/unk_0204cc1c.h"








extern "C" {

s32 Ground_GetWaterKind(s32 x, s32 y);
u32 MapBlock_GetAttr(void *block);
s32 Ground_IsGrassUnit(s32 x, s32 y);
s32 Ground_IsPond(s32 x, s32 y);
s32 Ground_GetDigKind(s32 x, s32 y);

}

static inline MapBlock *Unk_ov003_02225238_Cell(BlockMap *g, u32 x, u32 y)
{
    if (x < (u32)g->width && y < (u32)g->height && g->blocks != 0) {
        return g->blocks + (y * g->width + x);
    }
    return 0;
}

static inline BOOL Unk_ov003_02225238_ChkA(u16 *p)
{
    BOOL f9 = TRUE, f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v >= 0x26 && v <= 0x2a) f1 = TRUE;
    if (!f1) {
        if (!(v >= 0x5d && v <= 0x61)) f2 = FALSE;
    }
    if (!f2) {
        if (!(v >= 0x2f && v <= 0x56)) f3 = FALSE;
    }
    if (!f3) {
        if (!(v >= 0x57 && v <= 0x5b)) f4 = FALSE;
    }
    if (!f4) {
        if (!(v >= 0x66 && v <= 0x68)) f5 = FALSE;
    }
    if (!f5) {
        if (v != 0x69) f6 = FALSE;
    }
    if (!f6) {
        if (!(v >= 0x6a && v <= 0x6c)) f7 = FALSE;
    }
    if (!f7) {
        if (v != 0x6d) f8 = FALSE;
    }
    if (!f8) {
        if (!(v >= 0xc8 && v <= 0xcf)) f9 = FALSE;
    }
    return f9;
}

static inline BOOL Unk_ov003_02225238_ChkB(u16 *p)
{
    BOOL f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v <= 5) f1 = TRUE;
    if (!f1) {
        if (!(v >= 6 && v <= 0xb)) f2 = FALSE;
    }
    if (!f2) {
        if (!(v >= 0xc && v <= 0x11)) f3 = FALSE;
    }
    if (!f3) {
        if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) f4 = FALSE;
    }
    if (!f4) {
        if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) ||
              (v >= 0x9c && v <= 0xa3) || v == 0xa5))
            f5 = FALSE;
    }
    if (!f5) {
        if (v != 0x1a) f6 = FALSE;
    }
    if (!f6) {
        if (v != 0xa4) f7 = FALSE;
    }
    if (!f7) {
        if (v != 0x1d) f8 = FALSE;
    }
    return f8;
}

#define CHK_A(p, a1, a2, a3, a4, a5, a6, a7, a8, a9, res) { \
    a9 = TRUE; a8 = TRUE; a7 = TRUE; a6 = TRUE; a5 = TRUE; a4 = TRUE; a3 = TRUE; a2 = TRUE; a1 = FALSE; \
    u32 v = *(p); \
    if (v >= 0x26 && v <= 0x2a) a1 = TRUE; \
    if (!a1) { if (!(v >= 0x5d && v <= 0x61)) a2 = FALSE; } \
    if (!a2) { if (!(v >= 0x2f && v <= 0x56)) a3 = FALSE; } \
    if (!a3) { if (!(v >= 0x57 && v <= 0x5b)) a4 = FALSE; } \
    if (!a4) { if (!(v >= 0x66 && v <= 0x68)) a5 = FALSE; } \
    if (!a5) { if (v != 0x69) a6 = FALSE; } \
    if (!a6) { if (!(v >= 0x6a && v <= 0x6c)) a7 = FALSE; } \
    if (!a7) { if (v != 0x6d) a8 = FALSE; } \
    if (!a8) { if (!(v >= 0xc8 && v <= 0xcf)) a9 = FALSE; } \
    res = a9; }
#define CHK_B(p, a1, a2, a3, a4, a5, a6, a7, a8, res) { \
    a8 = TRUE; a7 = TRUE; a6 = TRUE; a5 = TRUE; a4 = TRUE; a3 = TRUE; a2 = TRUE; a1 = FALSE; \
    u32 v = *(p); \
    if (v <= 5) a1 = TRUE; \
    if (!a1) { if (!(v >= 6 && v <= 0xb)) a2 = FALSE; } \
    if (!a2) { if (!(v >= 0xc && v <= 0x11)) a3 = FALSE; } \
    if (!a3) { if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) a4 = FALSE; } \
    if (!a4) { if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) || (v >= 0x9c && v <= 0xa3) || v == 0xa5)) a5 = FALSE; } \
    if (!a5) { if (v != 0x1a) a6 = FALSE; } \
    if (!a6) { if (v != 0xa4) a7 = FALSE; } \
    if (!a7) { if (v != 0x1d) a8 = FALSE; } \
    res = a8; }
extern "C" BOOL InsectSpawn_FindUnitInBlock(u16 *buf, s32 kind, s32 *px, s32 *py, BlockMap *grid, s32 mode)
{
    u16 *blk = buf + (*px + *py * 4) * 0x10;
    s32 cnt0 = 0;
    s32 cnt = 0;
    s32 found = 0;
    s32 f20 = 0;
    s32 z = 0;
    if (mode == 6) {
        MapBlock *cell = Unk_ov003_02225238_Cell(grid, *px + 1, *py + 1);
        if (cell == 0) {
            return FALSE;
        }
        if ((MapBlock_GetAttr(cell) & 0x100) != 0) f20 = 1;
    }
    s32 xo = (*px + 1) << 4;
    s32 yo = (*py + 1) << 4;
    s32 ty = 0;
    BOOL A9,A8,A7,A6,A5,A4,A3,A2,A1,B8,B7,B6,B5,B4,B3,B2,B1,C8,C7,C6,C5,C4,C3,C2,C1, ra, rb, rc;
    u8 k = (s8)(kind - 2);
    for (; ty < 16; ty++) {
        s32 tx = z;
        u16 *row = blk + ty;
        s32 wy = yo + ty;
        {
        loop0:
            if (((*row >> tx) & 1) == 0) {
                s32 wx = xo + tx;
                cnt0 = cnt;
                s32 hx = wx >> 4;
                s32 hy = wy >> 4;
                u16 *c = BlockMap_GetItemPtr(grid, hx, hy, wx - (hx << 4), wy - (hy << 4), 0);
                if (c == 0) goto next0;
                switch (mode) {
                case 7:
                    if (kind == 0x33) {
                        BOOL fa = FALSE;
                        u32 v = *c;
                        if (v >= 0x154a && v <= 0x1553) fa = TRUE;
                        if (fa != 0 || (v >= 0x1320 && v <= 0x1322)) {
                            if (BlockMap_IsBuriedAtUnit(grid, wx, wy) == 0) {
                                found = 1;
                                cnt++;
                                break;
                            }
                        }
                        if (*c == 0xfff1) cnt++;
                    } else {
                        BOOL fb = FALSE;
                        u32 v = *c;
                        if (v >= 0x154a && v <= 0x1553) fb = TRUE;
                        if (fb != 0) {
                            if (BlockMap_IsBuriedAtUnit(grid, wx, wy) == 0) cnt++;
                        }
                    }
                    break;
                case 4:
                    if (Ground_IsGrassUnit(wx, wy) != 0) {
                        if (*c == 0xfff1) cnt++;
                    }
                    break;
                case 6:
                    if (Ground_IsPond(wx, wy) != 0) {
                        cnt++;
                    } else if (f20 != 0 && tx > 3 && ty > 3 && tx < 13 && ty < 13) {
                        if (Ground_GetWaterKind(wx, wy) == 2) cnt++;
                    }
                    break;
                case 1:
                    CHK_A(c, A1,A2,A3,A4,A5,A6,A7,A8,A9, ra)
                    if (!ra) {
                        if (found == 0) {
                            CHK_B(c, B1,B2,B3,B4,B5,B6,B7,B8, rb)
                            if (rb) {
                                if (k <= 1) {
                                    if (Insect_LikesFlower(kind, c) != 0) found = 1;
                                } else {
                                    found = 1;
                                }
                            }
                        }
                        cnt++;
                    }
                    break;
                case 2:
                    CHK_B(c, C1,C2,C3,C4,C5,C6,C7,C8, rc)
                    if (rc) {
                        if (kind == 0xf) {
                            if (Insect_LikesFlower(kind, c) != 0) cnt++;
                        } else {
                            cnt++;
                        }
                    }
                    break;
                case 9:
                    if (Ground_GetDigKind(wx, wy) == 0) {
                        if (*c == 0xfff1) cnt++;
                    }
                    break;
                case 8:
                    if (*c == 0x1b) {
                        found = 1;
                        cnt++;
                    } else if (*c == 0xfff1) {
                        cnt++;
                    }
                    break;
                case 0:
                    if (*c == 0xfff1) cnt++;
                    break;
                case 11:
                    if (((*row << tx) & 1) == 0) cnt++;
                    break;
                case 10: {
                    BOOL fc = FALSE;
                    u32 v = *c;
                    if (v >= 0xe3 && v <= 0xe7) fc = TRUE;
                    if (fc) cnt++;
                    break;
                }
                case 12:
                    if (Field_IsGrownTreeItem(c)) cnt++;
                    break;
                case 14:
                    if (Field_IsGrownTreeItem(c) || Field_IsGrownSpecialTreeItem(c)) cnt++;
                    break;
                case 15:
                    if (Field_IsGrownTreeItem(c) || Field_IsGrownSpecialTreeItem(c) || Field_IsGrownPalmTreeItem(c)) cnt++;
                    break;
                case 13:
                    if (Field_IsGrownPalmTreeItem(c)) cnt++;
                    break;
                case 5:
                    if (Ground_GetWaterKind(wx, wy) == 2) cnt++;
                    break;
                case 3:
                    break;
                }
            }
            if (cnt == cnt0) {
                *row |= 1 << tx;
            }
        next0:
            tx++;
            if (tx < 16) goto loop0;
        }
    }
    if (mode == 1 || mode == 8 || (mode == 7 && kind == 0x33)) {
        if (cnt > 0 && found != 0) {
            SpawnMask_PickFreeUnit(cnt, blk, px, py);
            return TRUE;
        }
    } else {
        if (cnt > 0) {
            SpawnMask_PickFreeUnit(cnt, blk, px, py);
            return TRUE;
        }
    }
    return FALSE;
}

#pragma opt_loop_invariants off
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "field/BottleThrow.h"
#include "field/Unk_ov003_02225238_Grid.h"
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
}

BOOL Field_IsGrownTreeItem(u16 *p)
{
    u32 v = *p;
    if (v == 0x2a || v == 0x61 || (v >= 0x33 && v <= 0x36) || (v >= 0x3b && v <= 0x3e) || (v >= 0x43 && v <= 0x46) ||
        (v >= 0x4b && v <= 0x4e) || (v >= 0x53 && v <= 0x56)) {
        return TRUE;
    }
    return FALSE;
}

BOOL Field_IsGrownSpecialTreeItem(u16 *p)
{
    u32 v = *p;
    if (v == 0x5b || (v >= 0x66 && v <= 0x6d)) {
        return TRUE;
    }
    return FALSE;
}

BOOL Field_IsGrownPalmTreeItem(u16 *p)
{
    BOOL r = FALSE;
    if (*p >= 0xcc && *p <= 0xcf) {
        r = TRUE;
    }
    return r;
}

void SpawnMask_PickFreeUnit(u32 n0, u16 *tbl, s32 *px, s32 *py)
{
    u32 n = Random_GlobalBelow(n0);
    s32 y = 0;
    s32 x0 = 0;
    for (; y < 16; y++) {
        s32 x = x0;
        u16 *row = tbl + y;
        for (; x < 16; x++) {
            if (((*row >> x) & 1) == 0) {
                if (n-- == 0) {
                    VecFx32 t;
                    FieldPos_FromBlockUnitCenter(&t, *px + 1, *py + 1, x, y);
                    *px = t.x;
                    *py = t.z;
                    return;
                }
            }
        }
    }
}

void SpawnMask_MarkRect(u16 *buf, s32 x, s32 y, s32 rad, u8 a, u8 b)
{
    s32 ox = 0;
    s32 oy = 0;
    VecFx32Ctor pos(x, 0, y);
    s32 bo;
    s32 t;
    s32 l;
    s32 r;
    s32 x0;
    s32 y0;
    s32 by;
    s32 bb;
    s32 bx;
    s32 lx;
    s32 aa;
    s32 ly;
    s32 e1;
    s32 w1;
    s32 e2;
    s32 h1;
    s32 i;
    s32 lo;
    s32 bx16;
    u16 m0;
    u16 *p2;
    u16 *pp;
    s32 n;
    u16 *p1;
    u16 m2;
    u16 m3;
    u16 *p0;
    s32 q;
    FieldPos_ToUnit(&ox, &oy, &pos);
    x0 = ox;
    l = x0 - rad;
    aa = a;
    y0 = oy;
    t = y0 - aa;
    r = x0 + rad;
    bb = b;
    bo = y0 + bb;
    if (l < 0x10) l = 0x10;
    if (t < 0x10) t = 0x10;
    if (r > 0x50) r = 0x50;
    if (bo > 0x50) bo = 0x50;
    if (l >= 0x10 && l < r && r <= 0x50 && t >= 0x10 && t < bo && bo <= 0x50) {
        bx = l >> 4;
        by = t >> 4;
        lx = l - (bx << 4);
        ly = t - (by << 4);
        e1 = lx + rad * 2;
        w1 = e1 > 0x10 ? 0x10 : e1;
        e2 = ly + aa + bb;
        h1 = e2 > 0x10 ? 0x10 : e2;
        if (bx == 1) {
            x0 -= 0x10;
            q = x0 - rad;
            if (q < 0) w1 += q;
        }
        if (by == 1) {
            y0 -= 0x10;
            q = y0 - aa;
            if (q < 0) h1 += q;
        }
        lo = lx > 0 ? (2 << lx) - 1 : 0;
        m0 = (2 << w1) - 1 - lo;
        bx16 = bx << 4;
        p0 = buf + (by - 1) * 0x40 + bx16;
        pp = p0 - 0x10;
        for (i = ly; i < h1; i++) {
            pp[i] |= m0;
        }
        if (e2 > 0x10 && by < 4) {
            n = e2 - 0x10;
            p1 = buf + by * 0x40 + bx16 - 0x10;
            for (i = 0; i < n; i++) {
                p1[i] |= m0;
            }
        }
        if (e1 > 0x10 && bx < 4) {
            m2 = (2 << (e1 - 0x10)) - 1;
            for (; ly < h1; ly++) {
                p0[ly] |= m2;
            }
        }
        if (e2 > 0x10 && e1 > 0x10 && bx < 4 && by < 4) {
            e1 -= 0x10;
            m3 = (2 << e1) - 1;
            n = e2 - 0x10;
            p2 = buf + by * 0x40 + bx16;
            for (i = 0; i < n; i++) {
                p2[i] |= m3;
            }
        }
    }
}

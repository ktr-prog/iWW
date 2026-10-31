#pragma opt_common_subs off
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
s32 Item_IsBuildingOrOccupied(u16 *p);
s32 Ground_GetWaterKind(s32 x, s32 y);
void *MI_CpuFill8(void *p, s32 v, u32 n);
}

void InsectSpawn_BuildMasks()
{
    u8 ty;
    BlockMap *g;
    s32 wy;
    u32 xo;
    u32 yo;
    s32 hy;
    u16 *rowa;
    u16 *rowb;
    s32 wx;
    s32 xs;
    s32 m;
    s32 hx;
    u16 *c;
    u8 o1;
    u8 o2;
    u8 tx;
    g = TownBlockMap_Get();
    if (g != 0) {
        MI_CpuFill8(sInsectSpawnMaskLand, 0, 0x200);
        MI_CpuFill8(sInsectSpawnMaskDry, 0, 0x200);
        o1 = 0;
    l1:
        xo = (u8)((o1 + 1) << 4);
        o2 = 0;
    l2:
        yo = (u8)((o2 + 1) << 4);
        ty = 0;
    l3:
        tx = 0;
        wy = yo + ty;
        hy = wy >> 4;
        rowa = &sInsectSpawnMaskLand[o2][o1][ty];
        rowb = &sInsectSpawnMaskDry[o2][o1][ty];
    l4:
        wx = xo + tx;
        hx = wx >> 4;
        c = BlockMap_GetItemPtr(g, hx, hy, wx - (hx << 4), wy - (hy << 4), 0);
        if (c != 0) {
            if (Item_IsBuildingOrOccupied(c) != 0 || (xs = xo + tx, Ground_GetWaterKind(xs, wy) == 1)) {
                m = 1 << tx;
                *rowa |= m;
                *rowb |= m;
            } else if (Ground_GetWaterKind(xs, wy) == 2) {
                m = 1 << tx;
                *rowb |= m;
            }
        }
        tx++;
        if (tx < 16) goto l4;
        ty++;
        if (ty < 16) goto l3;
        o2++;
        if (o2 < 4) goto l2;
        o1++;
        if (o1 < 4) goto l1;
    }
}

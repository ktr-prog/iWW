#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "game/Unk_0202f2ac_V3.h"
#include "game/CollisionCylinder.h"



extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
#define data_02136f44 HOST_LABEL(s16 (*)[], data_02136f44)
#define data_02138f44 HOST_LABEL(s16 (*)[], data_02138f44)
}

struct TouchPickDrumStackPad {
    s32 v[3];
    TouchPickDrumStackPad() {}
    ~TouchPickDrumStackPad() {}
};

extern const u8 sTouchPickKindHasTarget[];
const u8 sTouchPickKindHasTarget[0x18] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
};

extern "C" BOOL TouchPick_HitWorldDrum(VecFx32 *out, VecFx32 *a, VecFx32 *b, s32 c, s32 d) {
    VecFx32 zero, v24, v30;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    CollisionCylinderX o(&zero, c, d);
    TouchPickDrumStackPad pad;
    s32 az = a->z, ay = a->y, ax = a->x;
    v24.x = ax;
    v24.y = ay;
    v24.z = az;
    s32 bz = b->z, by = b->y, bx = b->x;
    v30.x = bx;
    v30.y = by;
    v30.z = bz;
    s32 sn = data_02136f44[0];
    s32 cs = data_02136f44[1];
    v24.x = func_01ffcb0c(cs, ax) - func_01ffcb0c(sn, ay);
    v24.y = func_01ffcb0c(sn, ax) + func_01ffcb0c(cs, ay);
    s32 y = v30.y;
    s32 x = v30.x;
    v30.x = func_01ffcb0c(cs, x) - func_01ffcb0c(sn, y);
    v30.y = func_01ffcb0c(sn, x) + func_01ffcb0c(cs, y);
    if (o.clipSegmentSideBounded(&v30, &v24)) {
        s32 y2, x2, sn2, cs2;
        y2 = v30.y;
        sn2 = data_02138f44[0];
        x2 = v30.x;
        cs2 = data_02138f44[1];
        v30.x = func_01ffcb0c(cs2, x2) - func_01ffcb0c(sn2, y2);
        v30.y = func_01ffcb0c(sn2, x2) + func_01ffcb0c(cs2, y2);
        *out = v30;
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 TouchPickKind_HasTarget(s32 i) {
    if (i >= 0 && i < 0x17) {
        return sTouchPickKindHasTarget[i];
    }
    return 0;
}


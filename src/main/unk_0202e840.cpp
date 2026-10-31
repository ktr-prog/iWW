#include "types.h"
#include "gfx/VecFx32.h"
#include "game/HitSphere.h"
#include "game/Unk_0202f2ac_V3.h"
#include "game/CollisionSegment.h"
#include "sys/ProcBase.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_0202e840.h"



extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
s32 PM_GetBattery(s32 *out);
}



u8 sLowBatteryWarned;
s32 sLowBatteryPollTimer;

HitSphere::HitSphere() {
    center.x = 0;
    center.y = 0;
    center.z = 0;
    radius = 0;
}

HitSphere::~HitSphere() {}

void HitSphere::set(VecFx32Ctor *p, s32 r) {
    center.x = p->x;
    center.y = p->y;
    center.z = p->z;
    radius = r;
}

BOOL HitSphere::intersectSegment(VecFx32Ctor *out, CollisionSegment *cap) {
    s32 z;
    s32 r = radius;
    if (cap->distanceTo(&center) <= r) {
        z = center.z + func_01ffcb0c(cap->dir.z, radius);
        s32 y = center.y + func_01ffcb0c(cap->dir.y, radius);
        s32 x = center.x + func_01ffcb0c(cap->dir.x, radius);
        VecFx32Ctor a(x, y, z);
        VecFx32Ctor b(center.x - x, center.y - y, center.z - z);
        s64 s1 = Vec_DistSq(&cap->start, &a);
        s64 s2 = Vec_DistSq(&cap->start, &b);
        if (s1 < s2) {
            out->x = a.x;
            out->y = a.y;
            out->z = a.z;
        } else {
            out->x = b.x;
            out->y = b.y;
            out->z = b.z;
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL LowBattery_Poll() {
    BOOL r = FALSE;
    if (sLowBatteryWarned == 0) {
        if (--sLowBatteryPollTimer <= 0) {
            s32 v;
            sLowBatteryPollTimer = 0x14;
            if (PM_GetBattery(&v) == 0 && v == 1) {
                r = TRUE;
            }
        }
    }
    return r;
}

extern "C" void LowBattery_SetWarned() { sLowBatteryWarned = 1; }

extern "C" void LowBattery_Reset() {
    sLowBatteryWarned = 0;
    sLowBatteryPollTimer = 0x14;
}

void GameProc::postCreate(int a) {
    if (a == 1) {
        ProcBase_RequestDelete(this);
    }
    ProcBase::postCreate(a);
}

extern "C" ProcBase *GameProc_CreateChild(u32 a, void *parent, u32 c, u32 d) {
    return Proc_CreateChild(a, static_cast<ProcBase *>(parent), c, d);
}

extern "C" ProcBase *GameProc_CreateRoot(u32 a, u32 b, u32 c) { return Proc_CreateRoot(a, b, c); }

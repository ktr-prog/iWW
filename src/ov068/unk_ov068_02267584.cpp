#include "types.h"
#include "host_tick.h"
#include "gfx/VecFx32.h"
#include "actor/Actor.h"
#include "field/Snowball.h"
#include "game/GroundInfo.h"
#include "game/GroundInfoBase.h"
#include "field/LooseSnowballs.h"
#include "field/SnowmanRecords.h"
#include "save/SaveData.h"
#include "town/BlockMap.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/ov003/unk_ov003_02212830.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02225800.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/ov068/unk_ov068_02267584.h"
#include "proto/main/unk_0204cc1c.h"

extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
s32 FX_Div(s32 a, s32 b);
extern BlockMap *gSceneBlockMap;
extern s16 data_02135f44[];
extern s32 data_020c7c1c;
extern SaveData gSaveData;
u16 Item_MakeSnowman(u32 x);
BOOL Item_IsMarker(u16 *p);
s32 Ground_GetDigKind(s32 x, s32 y);
void Math_ApproachS32Max(s32 *p, s32 target, s32 ratio, s32 max);
s16 Math_Atan2(s32 x, s32 y);
s32 Math_AngleDiffAbs(s32 a, s32 b);
}

#define FX32_CONST(x) ((s32)((x) > 0 ? (x) * 4096.0f + 0.5f : (x) * 4096.0f - 0.5f))

static inline BOOL Snowball_IsHoleItem(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0xfc && *p <= 0xfd) {
        r = TRUE;
    }
    return r;
}

void Snowball::applySnowballMotion() {
    if ((collisionState.prevFlags & 1) != 0) {
        velocity.y = 0;
    } else {
        velocity.y = velocity.y + TICK_PART(0x6d);
        if (velocity.y > 0x200) {
            velocity.y = 0x200;
        }
    }
    position.y = position.y - TICK_PART(velocity.y);
    if (snowballFlags.e == 0 && snowballFlags.i == 0) {
        position.x = position.x + TICK_PART(rollVelX);
        position.z = position.z + TICK_PART(rollVelZ);
    }
}

extern "C" s32 Snowball_GetSizeRatioRank(s32 v) {
    if (v < 0x99a) {
        return 3;
    }
    if (v < 0xb33) {
        return 2;
    }
    if (v < 0xccd) {
        return 1;
    }
    if (v < 0xe66) {
        return 0;
    }
    if (v < 0x1000) {
        return 1;
    }
    if (v < 0x119a) {
        return 2;
    }
    return 3;
}

void Snowball::spawnSnowballBreak() {
    VecFx32 v;
    s16 h;
    Vec_Add(&v, &position, &drawOffset);
    v.y = v.y + (radius - 0x400);
    h = FX_Div(radius, 0x1000);
    Effect_Create(0x3e, &v, 0, &h);
    Snd_SeEmitterPlayOneShot(&seEmitter, 0x81f, 0x7f, 0);
}

void Snowball::spawnSnowballSplash() {
    VecFx32 v;
    s16 h;
    v.x = position.x;
    v.y = position.y;
    v.z = position.z;
    v.y = data_020c7c1c + 0x100;
    h = FX_Div(radius, 0x1000);
    Effect_Create(0x3f, &v, 0, &h);
    Snd_SeEmitterPlayOneShot(&seEmitter, 0x821, 0x7f, 0);
    FieldFish_ScareAround(&position, 0x5000);
}

BOOL Snowball::enterSnowballRoll() {
    snowballFlagBits |= 0x10;
    snowballFlagBits &= ~0x20;
    return TRUE;
}

void Snowball::execSnowballRoll() {
    BlockMap *grid = gSceneBlockMap;
    s32 sx, sy;
    u16 cell;
    GroundInfo ground;
    VecFx32 unitCenter;
    s32 d, t;
    collisionRadius = radius;
    s32 a = rollVelZ;
    s32 sum = func_01ffcb0c(rollVelX, rollVelX) + func_01ffcb0c(a, a);
    if (talkAct == 0 && snowballState == 0 && sum > 0 && radius >= 0xa00 && snowballFlags.e != 0) {
        Snowball *o = Snowball_FindOtherInBallState(this);
        if (o != 0 && o->radius >= 0xa00) {
            d = Vec_Distance(&position, &o->position);
            t = FX_Div(0, 0x64000) + 0x400;
            FieldPos_ToUnit(&sx, &sy, &o->position);
            cell = 0xfff1;
            if (grid != 0) {
                u32 x = sx;
                u32 y = sy;
                s32 hx = (s32)x >> 4;
                s32 hy = (s32)y >> 4;
                u16 *c = BlockMap_GetItemPtr(grid, hx, hy, x - (hx << 4), y - (hy << 4), 0);
                if (c != 0) {
                    cell = *c;
                }
            }
            if (Item_IsMarker(&cell) == 0 && o != 0 && d < t + (radius + o->radius) &&
                o->talkAct == 0 && o->snowballState == 0) {
                s32 r = Ground_GetDigKind(sx, sy);
                switch (r) {
                case 0:
                case 1:
                    s32 lv;
                    lv = Snowball_GetSizeRatioRank(FX_Div(radius, o->radius));
                    s32 res = ((SnowmanRecords *)gSaveData.snowmen)->add(radius, o->radius, lv);
                    if (res != -1) {
                        SnowballFlags &of = o->snowballFlags;
                        of.a = res;
                        snowballFlags.a = of.a;
                        of.b = lv;
                        snowballFlags.b = of.b;
                        of.g = 1;
                        snowballFlags.g = of.g;
                        Snowball_ChangeState(this, 8);
                        Snowball_ChangeState(o, 7);
                        if (lv == 0) {
                            Snowman_SendPrizeLetter();
                        }
                        return;
                    }
                }
            }
        }
    }
    applySnowballMotion();
    ground.initAtPos(&position, 0, 0);
    if (ground.getHeight(0) < 0) {
        Snowball_ChangeState(this, 1);
        return;
    }
    {
        GroundInfo water;
        water.initAtPos(&position, 1, 0);
        if (water.waterKind == 1) {
            switch (water.attr) {
            case 0x16:
            case 0x17:
                Snowball_ChangeState(this, 5);
                return;
            }
        }
    }
    if (grid != NULL) {
        FieldPos_SnapToUnitCenter(&unitCenter, &position);
        u16 *c = BlockMap_GetItemPtrAtPos(grid, &position, 0);
        if (c != NULL && Snowball_IsHoleItem(c) != 0) {
            if (Vec_DistXZ(&unitCenter, &position) < 0x1000) {
                Snowball *o = Snowball_FindOtherInBallState(this);
                if (o != 0 && o->talkAct == 0 && o->snowballState == 4) {
                    if (Vec_DistXZ(&o->position, &position) > o->radius + radius) {
                        if (Snowball_ChangeState(this, 4) != 0) {
                            return;
                        }
                    }
                } else {
                    if (Snowball_ChangeState(this, 4) != 0) {
                        return;
                    }
                }
            }
        }
    }
    moveVelX = rollVelX;
    moveVelZ = position.z - prevPosition.z;
    if (talkAct == 0 && snowballState == 0 && snowballFlags.e == 0) {
        s32 v36c = moveVelZ;
        u32 n;
        s32 ang;
        u32 i;
        s32 m = func_01ffcb0c(moveVelX, moveVelX) + func_01ffcb0c(v36c, v36c);
        if (m >= FX_Div(0x12c000, 0x2710000)) {
            n = collisionState.contacts.numContacts;
            if (n != 0) {
                ang = Math_Atan2(moveVelX, moveVelZ);
                for (i = 0; i < n; i++) {
                    if (Math_AngleDiffAbs((s16)(collisionState.contacts.angles[i] + 0x8000), ang) < 0x1000) {
                        if (Snowball_Break(this, 1) != 0) {
                            return;
                        }
                    }
                }
            }
        }
    }
}

s32 Snowball::enterSnowballFall() {
    snowballFlags.c = 1;
    snowballFlags.d = 0;
    collisionRadius = 0;
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    position.y = 0;
    velocity.y = 0;
    rollVelX = func_01ffcb0c(rollVelX, 0x119a);
    rollVelZ = func_01ffcb0c(rollVelZ, 0x119a);
    fallFrames = 0;
    VecFx32Ctor v(rollVelX, 0, rollVelZ);
    s32 d = Vec_MagXZ(&v);
    if (d < 0x2b8) {
        if (d == 0) {
            Actor *r = (Actor *)PlayerActor_GetActor(4);
            if (r) {
                s32 a = ((u16)r->rotY >> 4) * 2;
                rollVelX = func_01ffcb0c(0x2b8, data_02135f44[a]);
                rollVelZ = func_01ffcb0c(0x2b8, data_02135f44[a + 1]);
                position.x = prevPosition.x + rollVelX;
                position.z = prevPosition.z + rollVelZ;
            }
        } else {
            s32 r = FX_Div(0x2b8, d);
            rollVelX = func_01ffcb0c(rollVelX, r);
            rollVelZ = func_01ffcb0c(rollVelZ, r);
        }
    }
    return 1;
}

void Snowball::execSnowballFall() {
    s32 lim;
    s32 t = radius;
    t = t + (t >> 1);
    Math_ApproachS32Max(&collisionRadius, t, 0xcc, t);
    position.x += TICK_PART(rollVelX);
    position.z += TICK_PART(rollVelZ);
    if (fallFrames < 0xc) {
        velocity.y = velocity.y + TICK_PART(1);
        position.y -= TICK_PART(0x100);
        fallFrames = fallFrames + (TICK_STEP_ENDS() ? 1 : 0);
    } else {
        velocity.y = velocity.y + TICK_PART((FX_Div(0, 0x2710000) + 0xe9));
        position.y = position.y - TICK_PART(velocity.y);
    }
    if (collisionState.flags & 2) {
        GroundInfo ground;
        ground.initAtPos(&position, 0, 0);
        lim = ground.waterSurfaceY - radius - 0x200;
        if (position.y < lim) {
            spawnSnowballSplash();
            position.y = lim;
            Snowball_ChangeState(this, 2);
        }
    }
}

s32 Snowball::enterSnowballSink() {
    snowballFlags.c = 1;
    snowballFlags.d = 0;
    wobblePhase = 0;
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    VecFx32 *g = &gVec3Zero;
    drawOffset.x = g->x;
    drawOffset.y = g->y;
    drawOffset.z = g->z;
    velocity.y = 0;
    return 1;
}

void Snowball::execSnowballSink() {
    GroundInfo ground;
    s32 t = radius;
    t = t + (t >> 1);
    Math_ApproachS32Max(&collisionRadius, t, 0x200, t);
    ground.initAtPos(&position, 0, 0);
    position.x += TICK_PART(ground.flowDir >> 5);
    position.z += TICK_PART(ground.flowDirZ >> 5);
    radius = func_01ffcb0c(radius, 0xfd7);
    drawOffset.y = func_01ffcb0c(0x100, data_02135f44[((u16)wobblePhase >> 4) * 2]);
    wobblePhase = (s16)wobblePhase + 0x400;
    if (radius < 0x80) {
        radius = 0;
        ProcBase_RequestDelete(this);
    }
    applySnowballMotion();
    position.y = ground.waterSurfaceY - radius - 0x200;
}

s32 Snowball::enterSnowballBreak() {
    snowballFlags.c = 1;
    snowballFlags.d = 0;
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    spawnSnowballBreak();
    return 1;
}

void Snowball::execSnowballBreak() {
    collisionRadius = radius;
    ProcBase_RequestDelete(this);
}

s32 Snowball::enterSnowballHole() {
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    FieldPos_SnapToUnitCenter(&holePos, &position);
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    return 1;
}

void Snowball::execSnowballHole() {
    collisionRadius = radius;
    VecFx32 v;
    Vec_Sub(&v, &holePos, &position);
    Vec_SafeNormalize(&v);
    Vec_Scale(&v, 0x80);
    position.x += TICK_PART(v.x);
    position.z += TICK_PART(v.z);
    applySnowballMotion();
    s32 d = Vec_DistXZ(&position, &holePos);
    s32 lim = 0;
    if (d < 0x1000) {
        lim = -((0x1000 - d) / 5);
    }
    if (position.y < lim) {
        position.y = lim;
        if (d < 0x333) {
            Snowball_Break(this, 1);
        }
    }
}

s32 Snowball::enterSnowball05() {
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    targetPos.x = position.x;
    targetPos.y = position.y;
    targetPos.z = position.z;
    return 1;
}

s32 Snowball_execSnowball05_thr;
u8 Snowball_execSnowball05_thr_init;
void Snowball::execSnowball05() {
    rollVelZ += FX_Div(0, 0x3e8000) + 0x158;
    position.x += TICK_PART(rollVelX);
    position.z += TICK_PART(rollVelZ);
    s32 d = position.z - targetPos.z;
    if (d < 0) {
        d = -d;
    }
    position.y = -func_01ffcb0c(d, 0x3d7);
    if (!Snowball_execSnowball05_thr_init) {
        Snowball_execSnowball05_thr = FX_Div(0, 0x64000) + 0x3000;
        Snowball_execSnowball05_thr_init = 1;
    }
    if (d >= Snowball_execSnowball05_thr) {
        Snowball_ChangeState(this, 6);
    }
}

s32 Snowball::enterSnowballSplash() {
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    wobblePhase = 0;
    rollVelZ >>= 1;
    spawnSnowballSplash();
    return 1;
}

void Snowball::execSnowballSplash() {
    GroundInfo ground;
    ground.initAtPos(&position, 0, 0);
    position.x += TICK_PART(ground.flowDir >> 5);
    position.z += TICK_PART(ground.flowDirZ >> 5);
    radius = func_01ffcb0c(radius, 0xf85);
    drawOffset.y = func_01ffcb0c(0x100, data_02135f44[((u16)wobblePhase >> 4) * 2]);
    wobblePhase = (s16)wobblePhase + 0x400;
    if (radius < 0x100) {
        radius = 0;
        ProcBase_RequestDelete(this);
    }
    s32 lim = ground.waterSurfaceY - radius - 0x200;
    position.y -= TICK_PART(0x400);
    if (position.y < lim) {
        position.y = lim;
    }
}

s32 Snowball::enterSnowballToSnowman() {
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    FieldPos_SnapToUnitCenter(&targetPos, &position);
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    stepX = FX_Div(targetPos.x - position.x, 0x10000);
    stepZ = FX_Div(targetPos.z - position.z, 0x10000);
    stepCount = 0;
    return 1;
}

void Snowball::execSnowballToSnowman() {
    collisionRadius = radius;
    position.x += TICK_PART(stepX);
    position.y = 0;
    position.z += TICK_PART(stepZ);
    if (stepCount++ >= 0x10) {
        position.x = targetPos.x;
        position.y = targetPos.y;
        position.z = targetPos.z;
        BlockMap *g = gSceneBlockMap;
        if (g) {
            s32 x, y;
            FieldPos_ToUnit(&x, &y, &position);
            s32 tx = *(volatile s32 *)&x;
            s32 ty = *(volatile s32 *)&y;
            s32 hx = tx >> 4;
            s32 hy = ty >> 4;
            u16 *c = BlockMap_GetItemPtr(g, hx, hy, tx - (hx << 4), ty - (hy << 4), 0);
            if (c) {
                displacedItem = *c;
            }
            u16 v = Item_MakeSnowman(snowballFlags.a);
            BlockMap_SetItemAtUnit(g, &v, x, y, 0);
        }
        Snowball_DropDisplacedItem(&displacedItem);
        Snowball_ChangeState(this, 9);
    }
}

s32 Snowball::enterSnowballStack() {
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    Snowball *o = Snowball_FindOtherInBallState(this);
    FieldPos_SnapToUnitCenter(&targetPos, &o->position);
    targetPos.y += ((o->radius * 2 - (o->radius >> 3)) - (radius >> 3)) - 0x400;
    velocity.y = -(FX_Div(0, 0x3e8000) + 0x8f2);
    u32 ei = param & 1;
    LooseSnowball *e = LooseSnowballs_Get()->items;
    e[ei & 1].posX = 0;
    e[ei & 1].posY = 0;
    e[ei & 1].posZ = 0;
    e[ei & 1].radius = 0x800;
    stepX = FX_Div(targetPos.x - position.x, 0x10000);
    stepZ = FX_Div(targetPos.z - position.z, 0x10000);
    stepCount = 0;
    Snd_SeEmitterPlayOneShot(&seEmitter, 0x81e, 0x7f, 0);
    return 1;
}

void Snowball::execSnowballStack() {
    collisionRadius = radius;
    position.x += TICK_PART(stepX);
    position.z += TICK_PART(stepZ);
    velocity.y += TICK_PART(FX_Div(0, 0x2710000) + 0xdf);
    position.y -= TICK_PART(velocity.y);
    if (velocity.y >= 0) {
        s32 t = targetPos.y - 0x200;
        if (position.y < t) {
            position.y = t;
            Snowball_ChangeState(this, 0xa);
        }
    }
    if (stepCount++ >= 0x10) {
        position.x = targetPos.x;
        position.z = targetPos.z;
    }
}

BOOL Snowball::enterSnowballSettle() {
    snowballFlagBits &= ~0x10;
    snowballFlagBits |= 0x20;
    wobblePhase = 0;
    velocity.y = FX_Div(targetPos.y - position.y, 0x1333);
    return TRUE;
}

void Snowball::execSnowballSettle() {
    collisionRadius = radius;
    position.x += TICK_PART(stepX);
    position.z += TICK_PART(stepZ);
    position.y += TICK_PART(velocity.y);
    if (position.y > targetPos.y) {
        position.y = targetPos.y;
    }
    if (stepCount++ >= 0x10) {
        position.y = targetPos.y;
        Snowball_ChangeState(this, 0xb);
    }
}

BOOL Snowball::enterSnowballCrumble() {
    snowballFlagBits &= ~0x10;
    snowballFlagBits |= 0x20;
    Snowball_ClearItemAt(&position);
    drawOffset.x = gVec3Zero.x;
    drawOffset.y = gVec3Zero.y;
    drawOffset.z = gVec3Zero.z;
    wobblePhase = 0;
    crumbleTimer = 0xc;
    return TRUE;
}

void Snowball::execSnowballCrumble() {
    s32 a;
    collisionRadius = radius;
    a = data_02135f44[((u16)wobblePhase >> 4) * 2 + 1];
    drawOffset.x = -func_01ffcb0c(0x100, a);
    drawOffset.z = func_01ffcb0c(0x100, a);
    wobblePhase = wobblePhase + TICK_PART(0x3800);
    if (crumbleTimer != 0) {
        crumbleTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (crumbleTimer == 0) {
        spawnSnowballBreak();
        ProcBase_RequestDelete(this);
    }
}

BOOL Snowball::enterSnowballCrumble2() {
    snowballFlagBits &= ~0x10;
    snowballFlagBits |= 0x20;
    drawOffset.x = gVec3Zero.x;
    drawOffset.y = gVec3Zero.y;
    drawOffset.z = gVec3Zero.z;
    wobblePhase = 0;
    crumbleTimer = 0xc;
    return TRUE;
}

void Snowball::execSnowballCrumble2() {
    s32 a;
    collisionRadius = radius;
    a = data_02135f44[((u16)wobblePhase >> 4) * 2 + 1];
    drawOffset.x = func_01ffcb0c(0x100, a);
    drawOffset.z = -func_01ffcb0c(0x100, a);
    wobblePhase = wobblePhase + TICK_PART(0x5000);
    if (crumbleTimer != 0) {
        crumbleTimer -= TICK_STEP_ENDS() ? 1 : 0;
    }
    if (crumbleTimer == 0) {
        spawnSnowballBreak();
        ProcBase_RequestDelete(this);
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_02267584) {
    HOST_OVERLAY_VAR(Snowball_execSnowball05_thr),
    HOST_OVERLAY_VAR(Snowball_execSnowball05_thr_init),
    HOST_OVERLAY_VARS_END
};

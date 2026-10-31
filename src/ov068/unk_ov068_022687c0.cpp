#include "ds_div.h"
#include "host_shared_calls.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "field/Insect.h"
#include "game/StrBSizeData.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/AnimModel.h"
#include "gfx/PooledModel.h"
#include "town/BuildingActor.h"
#include "town/BlockMap.h"
#include "player/PlayerActor.h"
#include "field/Snowball.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_02212830.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/ov003/unk_ov003_02225800.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/ov068/unk_ov068_022687c0.h"

#pragma opt_loop_invariants off

typedef VecFx32Ctor V3;

struct MothLightStackPad {
    s32 v[3];
    MothLightStackPad() {}
    ~MothLightStackPad() {}
};

struct Unk_ov068_0226a004_Save {
    s32 x, y;
    volatile s32 z;
};







extern "C" {
extern BlockMap *gSceneBlockMap;
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 _s32_div_f(s32 a, s32 b);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
void NNS_G3dMdlSetMdlAlpha(u8 *res, u32 i, u32 v);
u32 NNS_G3dMdlGetMdlAlpha(u8 *res, u32 i);
BOOL Math_StepAngle(s16 *p, s16 target, s16 step);
s32 Math_ApproachS32(s32 *p, s32 target, s32 ratio, s32 max, s32 min);
void FieldPos_ToUnit(s32 *ox, s32 *oz, VecFx32 *v);
void FieldPos_FromUnitCenter(VecFx32 *v, s32 x, s32 z);
u16 *BlockMap_GetItemPtr(BlockMap *g, s32 hx, s32 hy, s32 lx, s32 ly, u8 layer);
s32 Flower_GetSpecies(u16 *p);
u16 Item_MakeBuilding(u32 x);
s32 Ground_GetWaterKind(s32 x, s32 y);
void Town_ClearBeesReleased(void);
void Insect_GetDirVec(VecFx32Ctor *o, s32 a);
BOOL Insect_TickTimer(Insect *self);
void Insect_SetWanderBox(Insect *self);
void Insect_ClampStepXZ(VecFx32Ctor *out, VecFx32Ctor *in, s32 c);
void Insect_PlaySe(Insect *o, s32 a, s32 b);
BOOL Insect_FadeOut(Insect *self, s32 a);
void Insect_Despawn(Insect *self);
s32 Insect_UpdateAlarm(Insect *o, VecFx32 *out);
BOOL Insect_GroundWalk(Insect *self);
void Insect_FlapWings(Insect *self);
s32 Insect_CheckAlarm(Insect *self);
void Insect_FlutterBob(Insect *self, s32 a, s32 b, s32 c);
s32 Insect_CheckObstacle(Insect *o, s32 a, s32 b);
s32 Field_IsRafflesiaNear(VecFx32Copy *out, VecFx32 *b);
s32 Field_FindFlowerNear(VecFx32Copy *out, VecFx32Copy pos, s32 mask);
s32 PlayerActor_IsLocalAct67HitAt(VecFx32Ctor *a);
void Insect_AccumAlarmOffline(Insect *o, u8 *fp, V3 *out);
s32 Moth_SteerToLight(Insect *o, u16 *p, V3 *out);
s32 Moth_FindNearestLight(Insect *o, V3 *out);
void Bee_UpdateSwarmAnim(V3 *a, AnimModel *b, s32 d);
}

#define FX32_CONST(x) ((s32)((x) > 0 ? (x) * 4096.0f + 0.5f : (x) * 4096.0f - 0.5f))


extern "C" void Insect_AccumAlarmOffline(Insect *o, u8 *fp, V3 *out) {
    s32 best;
    s32 d;
    V3 *me;
    s32 zero;
    u8 flag;
    u8 i;
    Actor *p;

    best = 0xfffffff;
    flag = 1;
    p = (Actor *)PlayerActor_GetActor(4);
    me = &o->position;
    if (p != NULL) {
        VecFx32 *q = &p->position;
        out->x = q->x;
        out->y = q->y;
        out->z = q->z;
        best = Vec_DistXZ(out, me);
        Insect_AccumAlarmFromActor(o, &flag, p->speed, best);
        *fp = (*fp & flag) ? 1 : 0;
    }
    zero = 0;
    i = zero;
    for (; i < NpcRegistry_GetSlotCount(); i++) {
        NpcActor *e = NpcRegistry_GetBySlot(i);
        if (e != NULL) {
            VecFx32 *q = &e->position;
            V3 t;
            t.x = q->x;
            t.y = q->y;
            t.z = q->z;
            d = Vec_DistXZ(&t, me);
            Insect_AccumAlarmFromActor(o, &flag, e->speed, d);
            *fp = (*fp & flag) ? 1 : zero;
            if (best > d) {
                best = d;
                out->x = t.x;
                out->y = t.y;
                out->z = t.z;
            }
        }
    }
}


void Insect_AccumAlarmFromActor(Insect *o, u8 *flag, s32 a, s32 b) {
    s16 t = o->alarm;
    s32 lim = o->disturbRadius;
    *flag = 0;
    if (b < 0x2000) {
        t = t + 0x19;
    } else if (b > lim || a == 0) {
        *flag = 1;
    } else if (a <= 0x3e8) {
        t = t + 1;
    } else if (a <= 0x44c) {
        t = t + 3;
    } else if (a <= 0x490) {
        t = t + 5;
    } else if (a == 0x491) {
        t = t + 8;
    } else {
        t = t + 0xf;
    }
    if (t > 0xfe) {
        t = 0xfe;
    }
    o->alarm = t;
}


s32 Dragonfly_FindPerch(Insect *o) {
    V3 *v1e0 = &o->perchPos;
    s32 t;
    u8 zlo, xhi, zhi;
    V3 *pos;
    BlockMap *grid;
    s32 x, z;
    u8 xlo;
    u8 i, j;
    s32 lo;
    s32 hx, hz;
    u16 *cell;

    pos = &o->position;
    t = 0;
    x = 0;
    z = 0;
    grid = gSceneBlockMap;
    FieldPos_ToUnit(&x, &z, pos);
    lo = x - 1;
    if (lo < 0x10) {
        lo = 0x10;
    }
    xlo = lo;
    lo = z - 1;
    if (lo < 0x10) {
        lo = 0x10;
    }
    zlo = lo;
    lo = x + 1;
    if (lo > 0x50) {
        lo = 0x50;
    }
    xhi = lo;
    lo = z + 1;
    if (lo > 0x50) {
        lo = 0x50;
    }
    zhi = lo;
    for (i = xlo; i <= xhi; i++) {
        j = zlo;
        goto test0;
    loop0:
        hx = i >> 4;
        hz = j >> 4;
        cell = BlockMap_GetItemPtr(grid, hx, hz, i - (hx << 4), j - (hz << 4), 0);
        if (cell != 0) {
            u32 v = *cell;
            if (v == 0x500a) {
                t = 1;
            } else if (v >= 0xe3 && v <= 0xe7) {
                t = 2;
            }
            if (t != 0) {
                FieldPos_FromUnitCenter(v1e0, i, j);
                if (t == 1) {
                    v1e0->z = v1e0->z + 0x59a;
                }
                o->behaviorWork = o->behaviorWork + 0x10;
                {
                    s32 old = o->rotY;
                    s32 rr = Math_AngleXZ(pos, v1e0);
                    o->turnAngle = rr + old;
                }
                o->state = 0xe;
                return 1;
            }
        }
        j++;
    test0:
        if (j <= zhi) goto loop0;
    }
    return 0;
}


void Pondskater_Skate(Insect *o, s16 *p) {
    V3 *b2;
    s32 x;
    s32 z;
    V3 w;
    volatile V3 sv[1];
    V3 *pos;
    V3 *b1;
    s32 r;

    pos = &o->position;
    sv[0].x = pos->x;
    sv[0].y = pos->y;
    sv[0].z = pos->z;
    b2 = &o->wanderBoxMax;
    b1 = &o->wanderBoxMin;
    x = 0;
    z = 0;
    w.x = 0;
    w.y = 0;
    w.z = 0x29;
    Vec_RotateY(&w, o->rotY);
    o->position.x = o->position.x + func_01ffcb0c((*p * o->moveSpeed) << 12, w.x);
    pos->z = pos->z + func_01ffcb0c((*p * o->moveSpeed) << 12, w.z);
    *p = *p - 1;
    FieldPos_ToUnit(&x, &z, pos);
    r = Ground_GetWaterKind(x, z);
    if (r != 2 || pos->x < b1->x || pos->x > b2->x || pos->z > b1->z || pos->z < b2->z) {
        s32 base = -0x8000;
        pos->x = sv[0].x;
        pos->y = sv[0].y;
        pos->z = sv[0].z;
        base += Insect_RandomTurn(0xc, 1);
        o->turnAngle = base;
        o->state = 0xf;
        *p = 0;
    } else if (*p <= 0) {
        o->state = 0x13;
        o->auxTimer = Random_GlobalBelow(0x14) * 3;
    }
}


void Pondskater_StartSkate(Insect *o, u16 *p) {
    s16 a;
    s16 r;
    u8 k;
    V3 v;

    s16 a0 = o->rotY;
    a = a0;
    r = 0;
    if (o->state == 0xf) {
        r = a0 + o->turnAngle;
    } else {
        k = 0;
        for (; k < Random_GlobalBelow(5); k++) {
            r = r + 0xaaa;
        }
        if (Random_GlobalBelow(100) > 0x32) {
            r = -r;
        }
        r += a;
    }
    o->state = 4;
    o->rotY = r;
    *p = Random_GlobalBelow(8) + 8;
    V3 *pv = &o->position;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    v.y = v.y + 0x100;
    Effect_PlayById2(0x1f, &v, &a, 0);
}


void Pondskater_CheckObstacle(Insect *o, u16 *p) {
    if (Insect_CheckObstacle(o, 0xa0, 0xe38) != 0) {
        s32 base = -0x8000;
        base += Insect_RandomTurn(0xc, 1);
        o->turnAngle = base;
        o->state = 0xf;
        *p = 0;
    }
}


void Dragonfly_FlyToPerch(Insect *o) {
    s32 d;
    V3 *pos = &o->position;
    V3 *v1e0 = &o->perchPos;
    BlockMap *grid = gSceneBlockMap;
    s32 wx;
    s32 ang;
    s32 t;
    s32 x, z;
    s32 hx, hz;
    u8 cnt;
    u16 *cell;
    V3 dv;

    t = 0;
    x = 0;
    z = 0;
    d = Vec_DistXZ(pos, v1e0);
    cnt = 0;
    FieldPos_ToUnit(&x, &z, v1e0);
    wx = *(volatile s32 *)&x;
    s32 bz = *(volatile s32 *)&z;
    hx = wx >> 4;
    hz = bz >> 4;
    cell = BlockMap_GetItemPtr(grid, hx, hz, wx - (hx << 4), bz - (hz << 4), 0);
    if (cell != 0) {
        u32 v = *cell;
        if (v == 0x500a) {
            t = 0x27ae;
        } else if (v >= 0xe3 && v <= 0xe7) {
            t = 0x191f;
        }
    }
    if (t > 0 && o->isAlarmed == 0) {
        if (d > 0x266) {
            ang = Math_AngleXZ(pos, v1e0);
            Insect_GetDirVec(&dv, ang);
            o->rotY = ang;
            pos->x = pos->x + func_01ffcb0c(dv.x, 0xa000);
            pos->z = pos->z + func_01ffcb0c(dv.z, 0xa000);
        } else {
            cnt++;
        }
        if (t < pos->y - 0x19a) {
            pos->y = pos->y - 0xcd;
        } else {
            cnt++;
        }
        if (cnt >= 2) {
            o->state = 0x13;
        }
    } else {
        o->behaviorWork = o->behaviorWork & 0xff0f;
        o->state = 0x13;
    }
}


void Moth_CircleLight(Insect *o) {
    u32 rnd;
    u32 k24b, k24c;
    V3 *pos;
    V3 *v1e0;
    Unk_ov068_0226a004_Save save;
    s32 cnt;

    k24b = o->unk_24b;
    rnd = (u8)Random_GlobalBelow(100);
    pos = &o->position;
    v1e0 = &o->perchPos;
    k24c = o->unk_24c;
    save.x = pos->x;
    save.y = pos->y;
    save.z = pos->z;
    Insect_CheckAlarm(o);
    if (o->isAlarmed != 0) {
        Actor *player = (Actor *)PlayerActor_GetActor(4);
        if (player != NULL) {
            VecFx32 *q = &player->position;
            if (o->rotX == 1 && o->kind == 8) {
                s32 v;
                if (pos->x > q->x) {
                    v = 0x2aaa;
                } else {
                    v = -0x2aaa;
                }
                o->rotX = 0;
                o->rotY = v;
                Insect_SetAnimSpeed(o, 0x119a);
            }
        }
    } else {
        cnt = o->frameCounter;
        if (cnt % 10 == 0 && rnd > 0x1e) {
            o->unk_24c = k24c == 0 ? 1 : 0;
        } else if (cnt % 5 == 0 && rnd > 0x1e) {
            o->unk_24b = k24b == 0 ? 1 : 0;
        }
        if (k24b != 0) {
            pos->x = pos->x + o->moveSpeed * 0x30;
        } else {
            pos->x = pos->x - o->moveSpeed * 0x30;
        }
        if (k24c != 0) {
            pos->y = pos->y + o->moveSpeed * 0x30;
        } else {
            pos->y = pos->y - o->moveSpeed * 0x30;
        }
        if (Moth_FindNearestLight(o, v1e0) != 0) {
            o->unk_24b = k24b == 0 ? 1 : 0;
            pos->x = save.x;
        }
        if (FX_Div(0x15000, 0x10000) > pos->y || FX_Div(0x32000, 0x10000) < pos->y) {
            o->unk_24c = k24c == 0 ? 1 : 0;
            pos->y = save.y;
        }
    }
}


extern "C" s32 Moth_SteerToLight(Insect *o, u16 *p, V3 *out) {
    V3 a;
    V3 *pos;
    s32 r;
    a.x = 0;
    a.y = 0;
    a.z = 0;
    pos = &o->position;
    r = Moth_FindNearestLight(o, &a);
    if (r == 0) {
        o->rotY = -0x8000;
        o->rotX = 1;
        o->state = 0;
        Insect_SetAnimSpeed(o, 0x1000);
    } else if (r > 0 && r < 5) {
        V3 t;
        Vec_Sub(&t, pos, &a);
        out->x = t.x;
        out->y = t.y;
        out->z = t.z;
        out->y = 0;
        Insect_ClampStepXZ(out, out, 2);
        VEC_Subtract(pos, out, pos);
        return 1;
    } else {
        o->state = 9;
        *p = 0;
    }
    return 0;
}

extern "C" s32 Moth_FindNearestLight(Insect *o, V3 *out) {
    s32 best;
    V3 bv;
    V3 cur;
    s32 bx, bz;
    s32 x, z;
    u32 i;
    s32 zj = 0, zt = 0, zp = 0;

    bx = 0;
    best = -1;
    x = 0;
    z = 0;
    bz = 0;
    bv.x = best;
    bv.y = 0;
    bv.z = best;
    cur.x = 0;
    cur.y = 0;
    cur.z = 0;
    FieldPos_ToUnit(&x, &z, &o->position);
    cur.x = x;
    cur.y = 0;
    cur.z = z;
    for (i = 0; i < 0x22; i++) {
        u16 id = Item_MakeBuilding(i);
        StrBSizeData *obj = StrBSize_Get(&id);
        if (obj != NULL) {
            u32 cnt = obj->getLightUnitCount();
            s32 px = zp, pz = zp;
            if (cnt != 0) {
                BuildingActor *q = (BuildingActor *)Shared_BuildingList_FindByItem(id);
                if (q != NULL) {
                    u32 j;
                    for (j = zj; j < cnt; j++) {
                        if (obj->getLightUnit(&px, &pz, j) != 0 && q->callIsLit() == 1) {
                            V3 t;
                            MothLightStackPad pad;
                            s32 d;
                            s32 tx = px + q->getGridX();
                            s32 tz = pz + q->getGridZ();
                            t.x = tx;
                            t.y = zt;
                            t.z = tz;
                            d = Vec_DistXZ(&cur, &t);
                            if ((cur.z <= tz && best < 0) || d < best) {
                                best = d;
                                bx = tx;
                                bz = tz;
                            }
                        }
                    }
                }
            }
        }
    }
    if (best >= 0) {
        FieldPos_FromUnitCenter(&bv, bx, bz);
        out->x = bx;
        out->z = bz;
    }
    return best;
}


void Insect::hovererFly() {
    s16 h = rotY;
    s32 t = auxTimer;
    Insect_FlapWings(this);
    if (Insect_CheckAlarm(this) == 2) {
        isAlarmed = 0;
    }
    Insect_PlaySe(this, 0, 1);
    if (isAlarmed == 0 && Insect_ApproachFlower(this, &h) == 0 && kind == 10) {
        stateTimer = 0;
        state = 9;
        return;
    }
    insectWanderSteer(&h, 0xaaa, 0x1e, 0x46, moveSpeed << 12);
    if (kind == 10) {
        s32 x = FX_Div(0x12000, 0x10000);
        Insect_FlutterBob(this, t, x, (Random_GlobalBelow(8) + 10) << 12);
        auxTimer = t + 0xaaa;
    } else {
        Insect_FlutterBob(this, t, 0x19a, (Random_GlobalBelow(8) + 0x12) << 12);
        auxTimer = t + 0x1554;
    }
}


void Insect::dungBeetleWalk() {
    s32 t = auxTimer;
    if (Insect_GroundWalk(this) != 0) {
        if (t <= 0) {
            state = 9;
            stateTimer = 0;
        } else {
            auxTimer = t - 1;
        }
    }
}


s32 Insect_dungBeetlePushSnowball_base;
u8 Insect_dungBeetlePushSnowball_base_init;
void Insect::dungBeetlePushSnowball() {
    Snowball *a = Snowball_GetLooseBall(behaviorWork);
    VecFx32 *pos = &position;
    VecFx32Ctor w2;
    VecFx32 w;
    s16 ang;
    volatile s32 c;
    volatile s32 tmp;
    if (a != NULL) {
        s32 rot, r6;
        VecFx32 *q = &a->position;
        r6 = Snowball_GetRadius(a);
        ang = (s16)Math_AngleXZ(q, pos);
        rot = ang;
        w.x = q->x;
        w.y = q->y;
        w.z = q->z;
        if (!Insect_dungBeetlePushSnowball_base_init) {
            Insect_dungBeetlePushSnowball_base = (tmp = Snowball_GetMaxRadius(), tmp - Snowball_GetMinRadius());
            Insect_dungBeetlePushSnowball_base_init = 1;
        }
        r6 -= func_01ffcb0c(0x4cd, FX_Div(r6 - Snowball_GetMinRadius(), Insect_dungBeetlePushSnowball_base));
        if (frameCounter % 0x14 == 0) {
            s32 t = (s32)(Insect_RandomTurn(6, 1) << 17) >> 16;
            ang += t;
            auxTimer = t;
        } else {
            s32 u = *(volatile s16 *)&auxTimer;
            ang += u;
        }
        s32 cv = frameCounter;
        c = cv;
        if (cv % 4 == 0) {
            rot = (s16)(rot + 0x38e);
        } else if (c % 2 == 0) {
            rot = (s16)(rot - 0x38e);
        }
        rotY = rot;
        Insect_GetDirVec(&w2, ang);
        w.x = w.x - func_01ffcb0c(w2.x, 0x2666);
        w.z = w.z - func_01ffcb0c(w2.z, 0x2666);
        s32 d = Vec_DistXZ(&w, pos);
        if (d < r6) {
            pos->x = pos->x - w2.x;
            pos->z = pos->z - w2.z;
        } else if (d > r6 + 0x333) {
            pos->x = pos->x - func_01ffcb0c(w2.x, 0x3000);
            pos->z = pos->z - func_01ffcb0c(w2.z, 0x3000);
        } else {
            pos->x = pos->x - func_01ffcb0c(w2.x, 0x2666);
            pos->z = pos->z - func_01ffcb0c(w2.z, 0x2666);
        }
        if (Snowball_TrySetPos(a, &w) == 0) {
            state = 5;
            model.setFrame(0);
            auxTimer = Random_GlobalBelow(0x14) + 0x28;
        }
    } else {
        state = 5;
        model.setFrame(0);
        auxTimer = Random_GlobalBelow(0x14) + 0x28;
    }
}


BOOL Insect::spiderCheckPlayerHit() {
    VecFx32Ctor *v = &position;
    if (PlayerActor_IsLocalAct67HitAt(v) != 0) {
        Actor *p = (Actor *)PlayerActor_GetActor(4);
        if (p != NULL) {
            if (v->x < p->position.x) {
                v->x = v->x - FX_Div(0x14000, 0x10000);
            } else {
                v->x = v->x + FX_Div(0x14000, 0x10000);
            }
            if (Random_GlobalBelow(0x64) > 0x32) {
                unk_24c = 0;
            } else {
                unk_24c = 1;
            }
            return TRUE;
        }
    }
    return FALSE;
}


BOOL Insect::spiderSway() {
    s16 a = rotY;
    s32 b = (s16)(auxTimer - 1);
    if (b < 0) {
        return TRUE;
    }
    if (unk_24c != 0) {
        if (a > 0xaaa) {
            unk_24c = 0;
        }
    } else {
        if (a < -0xaaa) {
            unk_24c = 1;
        }
    }
    if (unk_24c != 0) {
        a += 0x222;
    } else {
        a -= 0x222;
    }
    rotY = a;
    auxTimer = b;
    return FALSE;
}


void Insect::mosquitoChase(s16 *p) {
    s32 dist;
    u32 rnd;
    Actor *tp = (Actor *)PlayerActor_GetActor(4);
    VecFx32 *pos = &position;
    s32 ang = 0;
    VecFx32Ctor v;
    v.x = ang;
    v.y = ang;
    v.z = ang;
    *p = *p + 0xaaa;
    Insect_PlaySe(this, 0, 1);
    Insect_FlapWings(this);
    if (tp != NULL) {
        VecFx32 *pp = &tp->position;
        dist = Vec_DistXZ(pp, pos);
        rnd = (u8)Random_GlobalBelow(0x64);
        s32 c = alarm;
        s32 h = rotY;
        ang = (s16)(Math_AngleXZ(pos, pp) - h);
        if (isAlarmed != 0) {
            if (c < 0xfe) {
                c = (s16)(c + 1);
                alarm = c;
            }
            if (c >= 0x3c) {
                if (dist < FX_Div(0x1000, 0x10000)) {
                    if (PlayerActor_RequestAct79() != 0) {
                        isAlarmed = 0;
                        *p = 0;
                        state = 9;
                    }
                }
            }
        }
        if (dist < 0x2000) {
            if (dist < FX_Div(0x1000, 0x4000) && isAlarmed == 0) {
                isAlarmed = 1;
                alarm = 0;
            }
            if (ang < -0x555 || ang > 0x555) {
                if (ang > 0 && rnd > 0xf) {
                    ang = 0x555;
                } else if (ang < 0 && rnd > 0xf) {
                    ang = -0x555;
                } else {
                    ang = 0;
                }
            }
        } else {
            if (dist > FX_Div(0x1000, 0x2000) && isAlarmed != 0 && c < 0x3c) {
                isAlarmed = 0;
                alarm = 0;
            }
            s32 lim = (s16)FX_Div(0x555, 0x4000);
            s32 nlim = -lim;
            if (ang < (s16)nlim || ang > lim) {
                if (ang > 0 && rnd > 0x14) {
                    ang = lim;
                } else if (ang < 0 && rnd > 0x14) {
                    ang = (s16)nlim;
                } else {
                    ang = 0;
                }
            }
        }
    }
    s16 na = ang + rotY;
    rotY = na;
    Insect_GetDirVec(&v, na);
    pos->x += func_01ffcb0c(v.x, 0x8000);
    pos->z += func_01ffcb0c(v.z, 0x8000);
    s32 r = Random_GlobalBelow(8);
    Insect_FlutterBob(this, *p, 0x2800, (r + 0x12) << 12);
}


void Insect::beeEnterSwarm() {
    Actor *tp = (Actor *)PlayerActor_GetActor(4);
    VecFx32 *v = &scale;
    if (tp != NULL) {
        rotY = Math_AngleXZ(&position, &tp->position);
    }
    NNS_G3dMdlSetMdlAlpha((u8 *)pooledModel.getModel(), 0, 0x1f);
    state = 2;
    v->x = 1;
    v->y = 1;
    v->z = 1;
    auxTimer = 0x28;
    model.curFrame = 0x2d000;
    behaviorWork = 0xf0;
    Bgm_RequestSilence(0x19, 0, 0);
}


void Insect::beeSwarmDescend() {
    VecFx32 *pos = &position;
    VecFx32 *v = &scale;
    s32 t = v->x;
    BOOL flag = FALSE;
    if (Math_ApproachS32(&t, 0x1000, 0x200, 0x1000, 0x19a) == 0) {
        flag = TRUE;
    }
    v->x = t;
    v->y = t;
    v->z = t;
    if (Math_ApproachS32(&pos->y, 0x2800, 0x199, 0x1000, 0x400) == 0 && flag) {
        state = 0;
        v->x = 0x1000;
        v->y = 0x1000;
        v->z = 0x1000;
        Bgm_ReleasePriority(0x19);
        Bgm_Request(0x1a, 0x3f, 0x7f, 0);
        PlayerActor_SetSlotFlag(0x1a, 4);
    }
}


extern "C" void Bee_StretchSwarm(VecFx32 *v, s32 up) {
    if (up == 0) {
        v->z = v->z - 0x52;
    } else {
        v->z = v->z + 0x52;
    }
    s32 t = v->z;
    if (t < 0x1000) {
        v->z = 0x1000;
        return;
    }
    if (t > 0x2000) {
        v->z = 0x2000;
    }
}

void Insect::beeChasePlayer() {
    Actor *tp = (Actor *)PlayerActor_GetActor(4);
    s32 ang, dist;
    VecFx32 *pos = &position;
    s32 cur = rotY;
    s16 h = cur;
    VecFx32Ctor v;
    VecFx32Ctor w;
    s32 t = auxTimer;
    u8 *cnt = &unk_256;
    if (t > 0) {
        auxTimer = t - 1;
    } else if (MenuCtrl_IsMenuOpen() != 0) {
        h = h + 0x1554;
        rotY = h;
        Insect_GetDirVec(&v, h);
        pos->x += func_01ffcb0c(0x23000, v.x);
        pos->z += func_01ffcb0c(0x23000, v.z);
        Bee_UpdateSwarmAnim(&scale, &model, cur - h);
        *cnt = 9;
        return;
    }
    if (tp == NULL) {
        return;
    }
    VecFx32 *pp = &tp->position;
    ang = Math_AngleXZ(pos, pp);
    s32 r6 = moveSpeed + behaviorWork;
    dist = Vec_DistXZ(pos, pp);
    if (dist < 0x1000) {
        state = 3;
        stateTimer = 0;
        return;
    }
    if (*cnt != 0) {
        *cnt = *cnt - 1;
        Math_StepAngle(&h, ang, 0xe38);
    } else if (r6 < 0xfa) {
        Math_StepAngle(&h, ang, 0x93e);
    } else if (r6 < 0x104) {
        Math_StepAngle(&h, ang, 0x7d2);
    } else {
        Math_StepAngle(&h, ang, 0x666);
    }
    s32 hh = h;
    s32 diff = _s32_div_f(ang - hh, 0xb6);
    if (diff < 0) {
        diff = -diff;
    }
    if ((u8)diff > 0xf && r6 > 0xb4) {
        r6 -= 2;
        behaviorWork = r6;
    } else if (r6 < 0x122) {
        r6 += 7;
        behaviorWork = r6;
    }
    rotY = hh;
    Insect_GetDirVec(&w, h);
    if (dist > 0xe000) {
        r6 <<= 12;
        pos->x += FX_Div(func_01ffcb0c(r6, w.x), 0x3800);
        pos->z += FX_Div(func_01ffcb0c(r6, w.z), 0x3800);
    } else {
        r6 <<= 12;
        pos->x += FX_Div(func_01ffcb0c(r6, w.x), 0x5000);
        pos->z += FX_Div(func_01ffcb0c(r6, w.z), 0x5000);
    }
    Bee_UpdateSwarmAnim(&scale, &model, (cur - h) * 5);
}


extern "C" void Bee_UpdateSwarmAnim(V3 *a, AnimModel *b, s32 d) {
    s32 ang = (s16)((u32)(b->curFrame << 4) >> 16);
    s32 t = d;
    if (d < 0) t = -d;
    if (t > 0x38e) {
        Bee_StretchSwarm(a, 0);
        if (d > 0) {
            static_cast<AnimFrameCtrl *>(b)->setup(0, 3, 0x4000, (u16)ang);
        } else {
            static_cast<AnimFrameCtrl *>(b)->setup(0x5a, 1, 0x4000, (u16)ang);
        }
    } else {
        Bee_StretchSwarm(a, 1);
        if (ang > 0x2d) {
            static_cast<AnimFrameCtrl *>(b)->setup(0x2e, 3, 0x4000, (u16)ang);
        } else {
            static_cast<AnimFrameCtrl *>(b)->setup(0x2e, 1, 0x4000, (u16)ang);
        }
    }
}


void Bee_StingAndLeave(Insect *o) {
    s16 *r7 = &o->stateTimer;
    V3 *r4 = &o->scale;
    V3 *r6 = &o->position;
    u32 st = o->state;
    if (st == 3) {
        Actor *q = (Actor *)PlayerActor_GetActor(4);
        if (q) {
            s16 c = o->rotY;
            s16 buf = c;
            V3 vec;
            Math_StepAngle(&buf, Math_AngleXZ(r6, &q->position), 0x1554);
            o->rotY = buf;
            Insect_GetDirVec(&vec, buf);
            r6->x = r6->x + func_01ffcb0c(0x23000, vec.x);
            r6->z = r6->z + func_01ffcb0c(0x23000, vec.z);
            Bee_UpdateSwarmAnim(&o->scale, &o->model, c - buf);
        }
        if (*r7 == 0) {
            if (PlayerActor_LocalBeeSting()) {
                Insect_PlaySe(o, 1, 0);
                *r7 = *r7 + 1;
            } else {
                Insect_PlaySe(o, 0, 1);
            }
        } else {
            *r7 = *r7 + 1;
            if (*r7 > 0x42) {
                o->state = 7;
                *r7 = 0;
            }
        }
    } else {
        V3 vec;
        Insect_GetDirVec(&vec, o->rotY);
        if (st == 7) {
            r6->x = r6->x + func_01ffcb0c(vec.x, 0x64000);
            r6->z = r6->z + func_01ffcb0c(vec.z, 0x64000);
            r4->x = r4->x + 0x266;
            r4->y = r4->y + 0x266;
            r4->z = r4->z + 0x266;
            Bee_UpdateSwarmAnim(r4, &o->model, 0);
        } else {
            r6->x = r6->x + FX_Div(func_01ffcb0c(vec.x, o->behaviorWork << 12), 0x5000);
            r6->z = r6->z + FX_Div(func_01ffcb0c(vec.z, o->behaviorWork << 12), 0x5000);
            r4->x = r4->x + 0x333;
            r4->y = r4->y + 0x333;
            r4->z = r4->z + 0x333;
        }
        if (Insect_FadeOut(o, 4)) {
            V3 *z;
            o->state = 0x13;
            o->inView = 0;
            z = &o->position;
            z->x = 0;
            z->y = 0;
            z->z = 0;
            o->behaviorWork = 0;
            Town_ClearBeesReleased();
            NNS_G3dMdlSetMdlAlpha((u8 *)o->pooledModel.getModel(), 0, 0);
        }
    }
}


void Stinger_Walk(Insect *o, s16 *p, u32 mode) {
    Insect_GroundWalk(o);
    if (o->state == 4) {
        Insect_PlaySe(o, 0, 1);
        if (Insect_TickTimer(o)) {
            o->state = 0x13;
            o->waitTimer = (Random_GlobalBelow(9) + 2) * 0x14;
        }
    } else if (o->state == 5) {
        if (o->kind == 0x36 &&
            (*p > 0 || (o->frameCounter % 10 == 0 && Random_GlobalBelow(100) > 0x4b))) {
            s32 t = *p;
            o->position.y = o->position.y + (func_01ffcb0c(FX_Div(0x1000, 0x12000), t << 12) + t * t * -10);
            if (*p == 0) {
                Actor *q = (Actor *)PlayerActor_GetActor(4);
                if (q) {
                    o->rotY = Math_AngleXZ(&o->position, &q->position);
                    Insect_PlaySe(o, 1, 0);
                }
            }
            *p = *p + 3;
            if (*p > 3) {
                if (Insect_IsOverWater(&o->position) == 0 && o->position.y <= 0) {
                    *p = 0;
                }
            }
        } else {
            Insect_PlaySe(o, 0, 1);
        }
        if (o->kind == 0x37 || *p == 0) {
            if (mode != 2) {
                o->state = 0x13;
                *p = 0;
            }
        }
    }
}


s32 Stinger_UpdateChase(Insect *o, s16 *p) {
    s32 r = 0;
    Actor *q = (Actor *)PlayerActor_GetActor(4);
    if (q) {
        VecFx32 *qq = &q->position;
        V3 vec;
        s32 st = (s8)Insect_UpdateAlarm(o, &vec);
        s16 c = o->alarm;
        if (c > 0) {
            s32 lim = o->disturbRadius;
            if (Vec_DistXZ(&vec, &o->position) > lim) {
                c = c - 3;
                o->alarm = c > 0 ? c : 0;
            }
        }
        if (c >= 0x14 || o->auxTimer > 0) {
            if (o->playerHoldsNet) {
                r = Stinger_Threaten(o, (u8)st, qq);
            } else {
                st = 1;
            }
        }
        if (c >= 0x14 && o->playerHoldsNet == 0) goto call;
        if (c >= o->alarmThreshold) goto call;
        if (*p <= 0) goto done;
    call:
        r = Stinger_TryAttack(o, (u8)st, qq, p);
    }
done:
    return r;
}


s32 Stinger_Threaten(Insect *o, u32 mode, VecFx32 *q) {
    V3 *v = &o->position;
    s32 c232 = o->auxTimer;
    s16 t23a = o->rotY;
    s16 *r6 = &o->unk_23e;
    AnimModel *s = &o->model;
    if (*r6 == 0 || o->kind == 0x37) {
        if (NNS_G3dMdlGetMdlAlpha((u8 *)o->pooledModel.getModel(), 0) == 0x1f) {
            if (mode == 1) {
                if (*r6 == 0) {
                    Insect_PlaySe(o, 1, 0);
                    t23a = Math_AngleXZ(v, q);
                }
                *r6 = *r6 + 1;
            }
            if (c232 > 0) {
                o->auxTimer = c232 - 1;
            } else if (mode == 0) {
                o->auxTimer = 0x3c;
                if (o->kind == 0x37) {
                    if ((u32)(s->curFrame << 4) >> 16 < 4 && (u32)(s->numFrames << 4) >> 16 < 0xb) {
                        Insect_PlaySe(o, 1, 0);
                    }
                }
            }
            if (o->unk_24b) {
                if (Vec_DistXZ(v, q) < 0x2000) {
                    Math_StepAngle(&t23a, Math_AngleXZ(v, q), 0xe38);
                } else {
                    Math_StepAngle(&t23a, Math_AngleXZ(v, q), 0x71c);
                }
                o->rotY = t23a;
            }
        }
    }
    if (o->kind == 0x37) {
        s32 a = (s32)s->numFrames >> 12;
        if ((u16)a == 0xe && (u32)(s->curFrame << 4) >> 16 == 0xd) {
            s->curFrame = 0xa000;
        } else {
            s32 b = (s32)s->curFrame >> 12;
            if ((u16)b < 4 && (u16)a < 0xb) {
                static_cast<AnimFrameCtrl *>(s)->setup(0xb, 1, 0x1000, 4);
            } else if ((u16)a == 0xb && (u16)b == 0xa) {
                static_cast<AnimFrameCtrl *>(s)->setup(0xe, 0, 0x1000, 10);
            }
        }
    }
    return 1;
}


s32 Stinger_TryAttack(Insect *o, u32 mode, VecFx32 *q, s16 *p) {
    V3 *v = &o->position;
    if (o->playerHoldsNet != 0 && (*p == 0 || *p > 0x1f) && NNS_G3dMdlGetMdlAlpha((u8 *)o->pooledModel.getModel(), 0) == 0x1f) {
        if (mode == 3 || mode == 1) {
            if (Vec_DistXZ(q, v) < 0x1000) {
                s16 *pp = &o->unk_23e;
                if (PlayerActor_LocalFaint(o->kind == 0x37 ? 1 : 0)) {
                    o->state = 0x13;
                    o->unk_24c = 1;
                    static_cast<AnimFrameCtrl *>(&o->model)->setup(0, 2, 0x1000, (u32)(o->model.curFrame << 4) >> 16);
                } else {
                    s32 t = *pp;
                    if (t > 0 && o->kind == 0x36) {
                        v->y = v->y + (func_01ffcb0c(FX_Div(0x1000, 0x12000), t << 12) + t * t * -10);
                        *pp = *pp + 3;
                        if (v->y <= 0) {
                            *pp = 0;
                        }
                    }
                }
                return 1;
            }
            o->state = 5;
            return 2;
        }
        if (o->state == 7) {
            o->state = 4;
            *p = 0;
        }
    } else {
    if ((mode == 1 || mode == 3) && *p == 0) {
        *p = 0x12c;
    } else {
        if (*p < 0x1f) {
            if (Insect_FadeOut(o, 1)) {
                Insect_Despawn(o);
            }
        } else if (o->unk_24b) {
            s16 t = o->rotY;
            Insect_PlaySe(o, 0, 1);
            Math_StepAngle(&t, Math_AngleXZ(q, v), 0x666);
            o->rotY = t;
            o->state = 7;
        }
    }
    *p = *p - 1;
    }
    return 0;
}

s32 Insect_ApproachFlower(Insect *o, s16 *p) {
    s32 inside = Insect_TickTimer(o);
    V3 *v = &o->position;
    s16 a;
    s32 b;
    V3 c;
    if (o->insectFindFlowerTarget(&a, &b, &c) != 0) {
        if (inside != 0) {
            if (b <= FX_Div(0x1000, 0x4000) && v->y <= c.y + FX_Div(0x1000, 0x8000) &&
                v->y >= c.y - FX_Div(0x1000, 0x8000)) {
                o->state = 6;
                o->waitTimer = (Random_GlobalBelow(5) + 0x10) * 0x14;
                o->stateTimer = 0;
                if (o->kind == 0x33) {
                    if (o->behaviorWork != 1) {
                        o->state = 0;
                    } else {
                        Insect_SetWanderBox(o);
                    }
                }
            } else {
                u32 t = o->cooldownTimer;
                if (Random_GlobalBelow(100) > (s32)(t - 0x14)) {
                    V3 *d = &o->targetPos;
                    if (d->x != *(volatile s32 *)&c.x || d->z != *(volatile s32 *)&c.z) {
                        V3 *d2 = &o->targetPos;
                        V3 *e2;
                        d2->x = c.x;
                        d2->y = c.y;
                        d2->z = c.z;
                        e2 = &o->homePos;
                        e2->x = v->x;
                        e2->y = v->y;
                        e2->z = v->z;
                    }
                    if (b <= 0x3000) {
                        o->targetHeight = c.y;
                    } else {
                        o->targetHeight = o->baseHeight;
                    }
                    *p = *p + a;
                    VEC_Subtract(&c, v, &c);
                    Insect_ClampStepXZ(&c, &c, 1);
                    VEC_Add(v, &c, v);
                }
            }
        } else {
            o->targetHeight = o->baseHeight;
        }
        return 1;
    }
    o->targetHeight = o->baseHeight;
    return 0;
}


BOOL Insect::insectFindFlowerTarget(s16 *out, s32 *dist, VecFx32 *pos) {
    u32 x;
    VecFx32Ctor *p = &position;
    u32 t = *(u8 *)&kind;
    BOOL ok;
    if (t == 0x33) {
        if (Field_IsRafflesiaNear((VecFx32Copy *)pos, p) != 0) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
    } else {
        if (Field_FindFlowerNear((VecFx32Copy *)pos, *(VecFx32Copy *)p, Insect_GetFlowerSpeciesMask((s8)t)) != 0) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
    }
    if (ok != 0) {
    s32 gx = 0;
    s32 gy = 0;
    FieldPos_ToUnit(&gx, &gy, pos);
    x = gx;
    u32 y = gy;
    s32 hx = (s32)x >> 4;
    s32 hy = (s32)y >> 4;
    u16 *cell = BlockMap_GetItemPtr(gSceneBlockMap, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    if ((u8)(t + 0xfe) <= 1) {
        if (Insect_LikesFlower((s8)t, cell) == 0) {
            return FALSE;
        }
    }
    if (t != 0x33) {
        Insect_AdjustFlowerLandingPos((s8)Flower_GetSpecies(cell), pos);
    } else {
        pos->x += 0x1000;
        pos->y = FX_Div(0xb000, 0x10000);
        pos->z += 0x1000;
    }
    *out = Math_AngleXZ(p, pos);
    *out = *out - rotY;
    if (*out > 0x38e) {
        *out = 0x38e;
    } else if (*out < -0x38e) {
        *out = -0x38e;
    }
    *dist = Vec_DistXZ(pos, p);
    return TRUE;
    }
    return FALSE;
}


extern "C" void Insect_AdjustFlowerLandingPos(s32 code, VecFx32 *v) {
    if (code == 1 || code == 4) {
        v->x += FX_Div(-0x1000, 0x10000);
        v->y = FX_Div(0x10000, 0x10000);
        v->z += FX_Div(-0x4000, 0x10000);
    } else {
        v->y = FX_Div(0x9000, 0x10000);
        v->z += FX_Div(0x3000, 0x10000);
    }
}


void Insect::insectWanderSteer(s16 *p, s32 a, s32 b, u8 thr, s32 sc) {
    u32 flag = unk_24b;
    u32 rnd = (u8)Random_GlobalBelow(100);
    VecFx32 *d = &position;
    VecFx32Ctor vec;
    if (DS_MOD(frameCounter, b) == 0 && rnd > thr) {
        if (flag == 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        unk_24b = flag;
    }
    if (rnd > cooldownTimer) {
        if (flag != 0) {
            *p = *p + a;
        } else {
            *p = *p - a;
        }
    }
    Insect_GetDirVec(&vec, *p);
    rotY = *p;
    if (isAlarmed != 0) {
        float f = 1.25f;
        if (kind == 10 || kind == 0x33) {
            f = 1.5f;
        }
        d->x += func_01ffcb0c(func_01ffcb0c(FX32_CONST(f), sc), vec.x);
        d->z += func_01ffcb0c(func_01ffcb0c(FX32_CONST(f), sc), vec.z);
    } else {
        d->x += func_01ffcb0c(sc, vec.x);
        d->z += func_01ffcb0c(sc, vec.z);
    }
}


void Insect::insectFleeFrom(VecFx32 *p) {
    if (p->x > 0 && isAlarmed == 0 && alarm >= alarmThreshold) {
        turnAngle = Math_AngleXZ(p, &position);
        waitTimer = (Random_GlobalBelow(4) + 7) * 20;
        state = 7;
        isAlarmed = 1;
        targetHeight = baseHeight;
    }
}

void Insect::antsAppear() {
    NNS_G3dMdlSetMdlAlpha((u8 *)pooledModel.getModel(), 0, 0x1f);
    state = 0x12;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_022687c0) {
    HOST_OVERLAY_VAR(Insect_dungBeetlePushSnowball_base),
    HOST_OVERLAY_VAR(Insect_dungBeetlePushSnowball_base_init),
    HOST_OVERLAY_VARS_END
};

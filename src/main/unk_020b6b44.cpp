#include "types.h"
#include "gfx/VecFx32.h"
#include "game/Unk_0202f2ac_V3.h"
#include "game/Basis.h"
#include "gfx/Mtx43.h"
#include "game/TouchPickTriangle.h"
#include "game/CollisionTriangle.h"
#include "game/CollisionCylinder.h"
#include "gfx/Camera.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_020b6b44.h"











extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
extern s16 data_02135f44[];
extern Camera *gCamera;
extern s32 data_020c8cb8;
s32 FX_Div(s32 a, s32 b);
void Vec_SafeNormalize(VecFx32 *v);
void Vec_Scale(VecFx32 *v, s32 s);
void MTX_Inverse43(Mtx43 *a, Mtx43 *b);
void MTX_MultVec43(VecFx32 *v, Mtx43 *m, VecFx32 *out);
void Vec_Sub(VecFx32 *out, VecFx32 *a, VecFx32 *b);
void Vec_RotateY(VecFx32 *v, s32 angle);
void Vec_RotateX(VecFx32 *v, s32 angle);
}

struct Pair {
    VecFx32 p, q;
};

extern "C" BOOL TouchPick_HitCylinder(VecFx32 *p, VecFx32 *q, VecFx32 *r, s32 a, s32 b) {
    VecFx32 v28;
    s32 ang = WorldCurve_ToCurved(&v28, r);
    s32 sn, cs;
    s32 z;
    s32 y, y2, y3;
    VecFx32 v34, v40, v4c;
    z = q->z;
    y = q->y;
    v34.x = q->x;
    v34.y = y;
    v34.z = z;
    s32 pz = p->z, py = p->y, px = p->x;
    v40.x = px;
    v40.y = py;
    v40.z = pz;
    v4c = v28;
    u32 idx = ((u16)(s16)-ang) >> 4;
    sn = data_02135f44[idx * 2];
    cs = data_02135f44[idx * 2 + 1];
    v34.y = func_01ffcb0c(cs, y) - func_01ffcb0c(sn, z);
    v34.z = func_01ffcb0c(sn, y) + func_01ffcb0c(cs, z);
    z = v40.z;
    y2 = v40.y;
    v40.y = func_01ffcb0c(cs, y2) - func_01ffcb0c(sn, z);
    v40.z = func_01ffcb0c(sn, y2) + func_01ffcb0c(cs, z);
    z = v4c.z;
    y3 = v4c.y;
    v4c.y = func_01ffcb0c(cs, y3) - func_01ffcb0c(sn, z);
    v4c.z = func_01ffcb0c(sn, y3) + func_01ffcb0c(cs, z);
    CollisionCylinderX o((VecFx32 *)&v4c, a, b);
    if (o.clipSegmentCaps((VecFx32 *)&v40, (VecFx32 *)&v34) ||
        o.clipSegmentSideBounded((VecFx32 *)&v40, (VecFx32 *)&v34)) {
        Vec_RotateX(&v40, ang);
        s32 rz = v40.z, ry = v40.y, rx = v40.x;
        p->x = rx;
        p->y = ry;
        p->z = rz;
        return TRUE;
    }
    return FALSE;
}

extern "C" void TouchPick_CalcRay(Basis *out, s32 x, s32 z) {
    VecFx32 zero;
    Pair t;
    VecFx32 c, d, e;
    Mtx43 m;
    VecFx32 f;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    s32 k = -FX_Div(0x60000, gCamera->getFovTan());
    t.p.x = (x << 12) - 0x80000;
    t.p.y = -((z << 12) - 0x60000);
    t.p.z = k;
    t.q = t.p;
    Vec_SafeNormalize(&t.q);
    Vec_Scale(&t.q, data_020c8cb8);
    Vec_Add(&c, &zero, &t.q);
    m = gViewMtx;
    MTX_Inverse43(&m, &m);
    MTX_MultVec43(&zero, &m, &d);
    MTX_MultVec43(&c, &m, &e);
    out->a = d;
    out->b = e;
    Vec_Sub(&f, &out->b, &out->a);
    out->c = f;
    Vec_SafeNormalize(&out->c);
}

TouchPickBox::TouchPickBox() {
}

TouchPickBox::~TouchPickBox() {
}

BOOL TouchPickBox::build(VecFx32 *pos, s32 w, s32 h, s32 d, s32 angle, s32 e, u8 f) {
    VecFx32 c[8];
    s32 hw = w >> 1;
    c[0].x = c[4].x = c[1].x = c[5].x = -hw;
    c[2].x = c[6].x = c[3].x = c[7].x = hw;
    s32 hd = h >> 1;
    c[0].z = c[4].z = c[3].z = c[7].z = -hd;
    c[1].z = c[5].z = c[2].z = c[6].z = hd;
    if (angle != 0) {
        Vec_RotateY(&c[0], angle);
        Vec_RotateY(&c[1], angle);
        Vec_RotateY(&c[2], angle);
        Vec_RotateY(&c[3], angle);
        c[4] = c[0];
        c[5] = c[1];
        c[6] = c[2];
        c[7] = c[3];
    }
    c[0].x += pos->x;
    c[1].x += pos->x;
    c[2].x += pos->x;
    c[3].x += pos->x;
    c[4].x += pos->x;
    c[5].x += pos->x;
    c[6].x += pos->x;
    c[7].x += pos->x;
    c[0].z += pos->z;
    c[1].z += pos->z;
    c[2].z += pos->z;
    c[3].z += pos->z;
    c[4].z += pos->z;
    c[5].z += pos->z;
    c[6].z += pos->z;
    c[7].z += pos->z;
    c[0].y = c[1].y = c[2].y = c[3].y = pos->y;
    c[4].y = c[5].y = c[6].y = c[7].y = pos->y + d;
    BOOL ok = TRUE;
    ok = (ok | triangles[0].setup(&c[4], &c[5], &c[6], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[1].setup(&c[4], &c[6], &c[7], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[2].setup(&c[5], &c[1], &c[2], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[3].setup(&c[5], &c[2], &c[6], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[4].setup(&c[6], &c[2], &c[3], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[5].setup(&c[6], &c[3], &c[7], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[6].setup(&c[4], &c[0], &c[1], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[7].setup(&c[4], &c[1], &c[5], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[8].setup(&c[7], &c[3], &c[0], e, f)) ? TRUE : FALSE;
    ok = (ok | triangles[9].setup(&c[7], &c[0], &c[4], e, f)) ? TRUE : FALSE;
    return ok;
}

TouchPickTriangle::TouchPickTriangle() {
    kind = 0;
    next = 0;
    index = 0xff;
}

TouchPickTriangle::~TouchPickTriangle() {}


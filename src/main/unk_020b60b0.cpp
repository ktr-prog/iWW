#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorCollider.h"
#include "game/HitSphere.h"
#include "game/Basis.h"
#include "game/TouchPicker.h"
#include "game/TouchPickSphere.h"
#include "gfx/Mtx43.h"
#include "game/CollisionCylinder.h"
#include "game/TouchPickCylinder.h"
#include "game/TouchPickTriangle.h"
#include "gfx/DebugColor.h"
#include "game/SceneInfo.h"
#include "game/CollisionSegment.h"
#include "game/CollisionTriangle.h"
#include "game/GroundInfo.h"
#include "game/GroundInfoBase.h"
#include "game/Unk_0202f2ac_V3.h"
#include "gfx/Camera.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020027b4.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_02088b98.h"
#include "proto/main/unk_020b60b0.h"
#include "proto/main/unk_020b705c.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/main/unk_0204cc1c.h"


extern "C" {
s32 func_01ffcb0c(s32 a, s32 b);
s32 FX_Div(s32 a, s32 b);
void MTX_MultVec43(const VecFx32 *src, const Mtx43 *m, VecFx32 *dst);
s32 Collision_CalcTriangleNormal(Unk_0202f2ac_V3 *n, Unk_0202f2ac_V3 *p, Unk_0202f2ac_V3 *a, Unk_0202f2ac_V3 *b);
}

BOOL TouchPickTriangle::setup(VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 d, u8 e) {
    VecFx32 va, vb, vc;
    WorldCurve_Apply(&va, a);
    WorldCurve_Apply(&vb, b);
    WorldCurve_Apply(&vc, c);
    return setupCurved(&va, &vb, &vc, d, e);
}

BOOL TouchPickTriangle::setupCurved(VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 d, u8 e) {
    Unk_0202f2ac_V3 n;
    if (Collision_CalcTriangleNormal(&n, (Unk_0202f2ac_V3 *)a, (Unk_0202f2ac_V3 *)b, (Unk_0202f2ac_V3 *)c) != 0) {
        kind = d;
        index = e;
        return ((CollisionTriangle *)this)->set((Unk_0202f2ac_V3 *)a, (Unk_0202f2ac_V3 *)b, (Unk_0202f2ac_V3 *)c, &n);
    }
    return FALSE;
}

TouchPickSphere::TouchPickSphere() {
    kind = 0;
    index = 0;
    next = 0;
}

TouchPickSphere::~TouchPickSphere() {
}

BOOL TouchPickSphere::setup(VecFx32 *pos, s32 r, s32 c, u8 d) {
    VecFx32 v;
    WorldCurve_Apply(&v, pos);
    return setupCurved(&v, r, c, d);
}

BOOL TouchPickSphere::setupCurved(VecFx32 *pos, s32 r, s32 c, u8 d) {
    kind = c;
    index = d;
    set((VecFx32Ctor *)pos, r);
    return TRUE;
}

TouchPickCylinder::TouchPickCylinder() {
    kind = 0;
    next = 0;
    index = 0xff;
}

TouchPickCylinder::~TouchPickCylinder() {
}

BOOL TouchPickCylinder::setup(VecFx32 *pos, s32 r, s32 h, s32 d, u8 e) {
    kind = d;
    index = e;
    setCylinder(pos, r, h);
    return TRUE;
}

void TouchPickResult::resetResult(u8 a) {
    groundX = 0;
    groundY = 0;
    groundZ = 0;
    groundX = (s32)0xffed4000;
    targetKind = 0;
    targetIndex = 0;
    targetX = 0;
    targetY = 0;
    targetZ = 0;
    enabled = a;
}

void TouchPicker::reset() {
    resetResult(0);
    triangles = 0;
    spheres = 0;
    cylinders = 0;
}

TouchPicker::~TouchPicker() {
}

TouchPicker::TouchPicker() {
    resetResult(0);
    triangles = 0;
    spheres = 0;
    cylinders = 0;
}

BOOL TouchPicker::pushBox(TouchPickBox *box) {
    BOOL ok = TRUE;
    TouchPickTriangle *p = box->triangles;
    for (u32 i = 0; i < 10; i++) {
        BOOL r = pushTriangle(p);
        p++;
        ok = (ok | r) ? TRUE : FALSE;
    }
    return ok;
}

BOOL TouchPicker::addBox(TouchPickBox *box, VecFx32 *pos, s32 w, s32 h, s32 d, s16 angle, s32 e, u8 f) {
    box->build(pos, w, h, d, angle, e, f);
    return pushBox(box);
}

BOOL TouchPicker::pushSphere(TouchPickSphere *o) {
    o->next = 0;
    if (spheres == 0) {
        spheres = o;
        return TRUE;
    }
    o->next = spheres;
    spheres = o;
    return TRUE;
}

BOOL TouchPicker::addSphere(TouchPickSphere *o, VecFx32 *pos, s32 r, s32 c, u8 d) {
    o->setup(pos, r, c, d);
    return pushSphere(o);
}

BOOL TouchPicker::pushCylinder(TouchPickCylinder *o) {
    o->next = 0;
    if (cylinders == 0) {
        cylinders = o;
        return TRUE;
    }
    o->next = cylinders;
    cylinders = o;
    return TRUE;
}

BOOL TouchPicker::addCylinder(TouchPickCylinder *o, VecFx32 *pos, s32 r, s32 h, s32 d, u8 e) {
    o->setup(pos, r, h, d, e);
    return pushCylinder(o);
}

BOOL TouchPicker::pushTriangle(TouchPickTriangle *o) {
    o->next = 0;
    if (triangles == 0) {
        triangles = o;
        return TRUE;
    }
    o->next = triangles;
    triangles = o;
    return TRUE;
}

BOOL TouchPicker::addTriangle(TouchPickTriangle *o, VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 d, u8 e) {
    o->setup(a, b, c, d, e);
    return pushTriangle(o);
}

DebugColor sColorPaleRed(31, 20, 20, 31);
DebugColor sColorPaleBlue(20, 20, 31, 31);
DebugColor sColorPaleYellow(31, 31, 20, 31);
DebugColor sColorPaleGreen(20, 31, 20, 31);
DebugColor sColorPaleCyan(20, 31, 31, 31);
DebugColor sColorGreyCyan(20, 24, 24, 31);


namespace Unk_020b60dc_NS {

extern "C" {
void TouchPick_CalcRay(Basis *out, s32 x, s32 z);
BOOL TouchPick_HitCylinder(VecFx32 *p, VecFx32 *q, VecFx32 *r, s32 a, s32 b);
BOOL TouchPick_GetGroundPos(TouchPickResult *r, VecFx32 *out);
void Mtx43_SetRotX(Mtx43 *m, s32 angle);
void Mtx43_Translate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(Mtx43 *m, s32 angle);
BOOL Collision_GetUnitShape(s32 x, s32 z, s32 *p, s32 *q, s32 *r);

extern s32 gGfxMainOnTop;
extern SceneInfo *gCurSceneInfo;
extern s32 data_020c8cbc;
extern s32 data_020c8cb8;
extern s32 data_020c7c1c;
extern Camera *gCamera;
extern VecFx32 gCameraLookAt;
extern u8 gFieldSceneKind;
}

inline BOOL Unk_020b60dc_IsMode0() {
    return gFieldSceneKind == 0;
}

extern "C" void TouchPick_Cast(TouchPicker *self, s32 sx, s32 sy, u8 flag) {
    VecFx32 t[3];
    VecFx32 p0, p1, r, v;

    self->resetResult(flag);
    if (flag == 0 || gGfxMainOnTop == 1) {
        self->spheres = 0;
        self->cylinders = 0;
        self->triangles = 0;
        return;
    }
    TouchPick_CalcRay((Basis *)t, sx, sy);
    p0 = t[0];
    VecFx32 *pb = &t[1];
    p1 = *pb;
    if (gCurSceneInfo->isOutdoor == 1) {
        static s32 k1 = data_020c8cbc * 6;
        static s32 k2 = data_020c7c1c + WorldCurve_GetRadius();
        s32 kk = k1;
        if (TouchPick_HitWorldDrum(&r, &p0, &p1, k2, kk)) {
            WorldCurve_FromCurved(&v, &r);
            GroundInfo x;
            x.initAtPos(&v, 0, 0);
            if (x.waterKind != 0) {
                p1 = r;
                v.y = data_020c7c1c;
                self->groundX = v.x;
                self->groundY = v.y;
                self->groundZ = v.z;
            }
        }
        if (!TouchPick_GetGroundPos(self, 0)) {
            if (TouchPick_HitWorldDrum(&r, &p0, &p1, WorldCurve_GetRadius(), kk)) {
                p1 = r;
                VecFx32 w;
                WorldCurve_FromCurved(&w, &r);
                w.y = 0;
                self->groundX = w.x;
                self->groundY = w.y;
                self->groundZ = w.z;
            }
        }
        if (!TouchPick_GetGroundPos(self, 0)) {
            Camera *cam = gCamera;
            if (cam != NULL) {
                struct { VecFx32 a, b, c; } l;
                l.a = gCameraLookAt;
                VecFx32 *pc = &t[2];
                l.b = *pc;
                s32 h = data_020c8cb8;
                Vec_Scale(&l.b, h << 2);
                Vec_Add(&l.c, &p0, &l.b);
                s32 k = data_020c8cbc;
                VecFx32 q[4];
                q[0].x = l.a.x - k;
                q[0].y = h;
                q[0].z = 0;
                q[1].x = q[0].x;
                q[1].y = -0x2000;
                q[1].z = 0;
                q[2].x = l.a.x + k;
                q[2].y = -0x2000;
                q[2].z = 0;
                q[3].x = q[2].x;
                q[3].y = h;
                q[3].z = 0;
                Mtx43 m;
                Mtx43_SetRotX(&m, cam->getEyeCurveAngle());
                Mtx43_Translate(&m, 0, WorldCurve_GetRadius(), 0);
                Mtx43_RotateX(&m, -0x1000);
                Mtx43_RotateX(&m, 0);
                VecFx32 rr[4];
                MTX_MultVec43(&q[0], &m, &rr[0]);
                MTX_MultVec43(&q[1], &m, &rr[1]);
                MTX_MultVec43(&q[2], &m, &rr[2]);
                MTX_MultVec43(&q[3], &m, &rr[3]);
                Unk_0202f2ac_V3 pl;
                Collision_CalcTriangleNormal(&pl, (Unk_0202f2ac_V3 *)&rr[0], (Unk_0202f2ac_V3 *)&rr[1], (Unk_0202f2ac_V3 *)&rr[2]);
                CollisionTriangle tri[2] = {CollisionTriangle(&rr[0], &rr[1], &rr[2], &pl),
                                            CollisionTriangle(&rr[0], &rr[2], &rr[3], &pl)};
                CollisionTriangle *tp = &tri[0];
                for (u32 i = 0; i < 2; tp++, i++) {
                    if (tp->distanceTo((Unk_0202f2ac_V3 *)&p0) >= 0) {
                        BOOL in;
                        if (tp->distanceTo((Unk_0202f2ac_V3 *)&l.c) >= 0) {
                            in = TRUE;
                        } else {
                            in = FALSE;
                        }
                        if (!in) {
                            VecFx32 ip;
                            if (tp->intersectSegment((Unk_0202f2ac_V3 *)&ip, (Unk_0202f2ac_V3 *)&p0, (Unk_0202f2ac_V3 *)&l.c)) {
                                p1 = ip;
                                VecFx32 j;
                                WorldCurve_FromCurved(&j, &ip);
                                self->groundX = j.x;
                                self->groundY = j.y;
                                self->groundZ = j.z;
                                self->groundY = 0;
                            }
                        }
                    }
                }
            }
        }
    } else {
        s32 x0 = p0.x >> 13;
        s32 z0 = p0.z >> 13;
        s32 x1 = p1.x >> 13;
        s32 z1 = p1.z >> 13;
        s32 xlo, zhi, zlo, xhi;
        xhi = x1;
        if (x0 <= x1) {
            xlo = x0;
        } else {
            xlo = x1;
            xhi = x0;
        }
        zhi = z1;
        if (z0 <= z1) {
            zlo = z0;
        } else {
            zlo = z1;
            zhi = z0;
        }
        s32 found = 0;
        for (s32 gx = xlo; gx <= xhi; gx++) {
            for (s32 gz = zlo; gz <= zhi; gz++) {
                GroundInfo y;
                y.initAtUnit(gx, gz, 0, 0);
                s32 h = y.getHeight(0);
                if (h < 0x4000 && h != 0) {
                    s32 cx = (gx << 13) + 0x1000;
                    VecFx32 s[5];
                    s[0].x = cx; s[0].y = 0;
                    s32 cz = (gz << 13) + 0x1000;
                    s[0].z = cz;
                    s[1].x = cx; s[1].y = 0; s[1].z = cz;
                    s[2].x = cx; s[2].y = 0; s[2].z = cz;
                    s[3].x = cx; s[3].y = 0; s[3].z = cz;
                    s[4].x = cx; s[4].y = 0; s[4].z = cz;
                    s[1].x = cx - 0x1000; s[1].y = h; s[1].z = cz - 0x1000;
                    s[2].x = cx - 0x1000; s[2].y = h; s[2].z = cz + 0x1000;
                    s[3].x = cx + 0x1000; s[3].y = h; s[3].z = cz + 0x1000;
                    s[4].x = cx + 0x1000; s[4].y = h; s[4].z = cz - 0x1000;
                    VecFx32 n;
                    n.x = 0; n.y = 0x1000; n.z = 0;
                    CollisionTriangle ua[2];
                    ua[0].set((Unk_0202f2ac_V3 *)&s[1], (Unk_0202f2ac_V3 *)&s[2], (Unk_0202f2ac_V3 *)&s[4], (Unk_0202f2ac_V3 *)&n);
                    ua[1].set((Unk_0202f2ac_V3 *)&s[2], (Unk_0202f2ac_V3 *)&s[3], (Unk_0202f2ac_V3 *)&s[4], (Unk_0202f2ac_V3 *)&n);
                    CollisionTriangle *up = &ua[0];
                    for (u32 i = 0; i < 2; up++, i++) {
                        if (up->distanceTo((Unk_0202f2ac_V3 *)&p0) >= 0) {
                            BOOL in;
                            if (up->distanceTo((Unk_0202f2ac_V3 *)&p1) >= 0) {
                                in = TRUE;
                            } else {
                                in = FALSE;
                            }
                            if (!in) {
                                VecFx32 ip;
                                if (up->intersectSegment((Unk_0202f2ac_V3 *)&ip, (Unk_0202f2ac_V3 *)&p0, (Unk_0202f2ac_V3 *)&p1)) {
                                    p1 = ip;
                                    self->groundX = p1.x;
                                    self->groundY = p1.y;
                                    self->groundZ = p1.z;
                                    found = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (found == 0 && p0.y > 0 && p1.y <= 0) {
            struct { VecFx32 d, dd; } dl;
            Vec_Sub(&dl.d, &p1, &p0);
            s32 ay = p0.y < 0 ? -p0.y : p0.y;
            s32 dy = p0.y - p1.y;
            if (dy < 0) {
                dy = -dy;
            }
            s32 ratio = FX_Div(ay, dy);
            r.x = p0.x + func_01ffcb0c(dl.d.x, ratio);
            r.y = p0.y + func_01ffcb0c(dl.d.y, ratio);
            r.z = p0.z + func_01ffcb0c(dl.d.z, ratio);
            p1.x = r.x;
            p1.y = r.y;
            p1.z = r.z;
            GroundInfo z;
            z.initAtPos(&r, 0, 0);
            self->groundX = r.x;
            self->groundY = r.y;
            self->groundZ = r.z;
        }
    }

    for (TouchPickCylinder *n = self->cylinders; n != 0; n = n->next) {
        if (TouchPick_HitCylinder(&p1, &p0, &n->center, n->circleRadius, n->cylinderHeight)) {
            self->targetX = n->center.x;
            self->targetY = n->center.y;
            self->targetZ = n->center.z;
            self->targetKind = n->kind;
            self->targetIndex = n->index;
        }
    }
    for (ActorCollider *col = gActorColliderList; col != 0; col = col->next) {
        if (TouchPickKind_HasTarget(col->targetKind)) {
            if (TouchPick_HitCylinder(&p1, &p0, col->getPos(), col->radius, col->height)) {
                VecFx32 *vp = col->getPos();
                self->targetX = vp->x;
                self->targetY = vp->y;
                self->targetZ = vp->z;
                self->targetKind = col->targetKind;
                self->targetIndex = col->targetIndex;
            }
        }
    }

    struct { VecFx32 e0, e1, lo, hi; } el;
    WorldCurve_FromCurved(&el.e0, &p0);
    WorldCurve_FromCurved(&el.e1, &p1);
    if (el.e0.x < el.e1.x) {
        el.lo.x = el.e0.x;
        el.hi.x = el.e1.x;
    } else {
        el.lo.x = el.e1.x;
        el.hi.x = el.e0.x;
    }
    el.e1.y = 0;
    el.e0.y = 0;
    if (el.e0.z < el.e1.z) {
        el.lo.z = el.e0.z;
        el.hi.z = el.e1.z;
    } else {
        el.lo.z = el.e1.z;
        el.hi.z = el.e0.z;
    }
    s32 bxl, bxh, bzl, bzh;
    bxl = el.lo.x >> 13;
    bzl = el.lo.z >> 13;
    bxh = el.hi.x >> 13;
    bzh = el.hi.z >> 13;
    s32 gx, gz;
    for (gz = bzh; gz >= bzl; gz--) {
        for (gx = bxh; gx >= bxl; gx--) {
            s32 ta, tb, tc;
            tc = 0;
            if (Collision_GetUnitShape(gx, gz, &ta, &tb, &tc) && tc != 0) {
                VecFx32 f;
                f.x = (gx << 13) + 0x1000;
                f.y = 0;
                f.z = (gz << 13) + 0x1000;
                if (TouchPick_HitCylinder(&p1, &p0, &f, ta, tb)) {
                    self->targetX = f.x;
                    self->targetY = f.y;
                    self->targetZ = f.z;
                    self->targetIndex = 0;
                    if (Unk_020b60dc_IsMode0()) {
                        if (tc == 10) {
                            self->targetKind = 6;
                            s32 g1, g2;
                            FieldPos_ToUnit(&g1, &g2, (VecFx32 *)&self->targetX);
                            self->targetIndex = BuildingList_IndexOf(BuildingList_FindByGrid(g1, g2));
                        } else {
                            self->targetKind = 5;
                        }
                    } else {
                        self->targetKind = 5;
                    }
                }
            }
        }
    }
    VecFx32 ip;
    for (TouchPickTriangle *n = self->triangles; n != 0; n = n->next) {
        if (((CollisionTriangle *)n)->distanceTo((Unk_0202f2ac_V3 *)&p0) >= 0) {
            BOOL in;
            if (((CollisionTriangle *)n)->distanceTo((Unk_0202f2ac_V3 *)&p1) >= 0) {
                in = TRUE;
            } else {
                in = FALSE;
            }
            if (!in) {
                if (((CollisionTriangle *)n)->intersectSegment((Unk_0202f2ac_V3 *)&ip, (Unk_0202f2ac_V3 *)&p0, (Unk_0202f2ac_V3 *)&p1)) {
                    p1 = ip;
                    VecFx32 kk;
                    WorldCurve_FromCurved(&kk, &p1);
                    self->targetX = kk.x;
                    self->targetY = kk.y;
                    self->targetZ = kk.z;
                    self->targetKind = n->kind;
                    self->targetIndex = n->index;
                }
            }
        }
    }
    TouchPickSphere *n = self->spheres;
    while (n != 0) {
        CollisionSegment l(&p0, &p1);
        if (n->intersectSegment((VecFx32Ctor *)&ip, &l)) {
            VecFx32 m2;
            WorldCurve_FromCurved(&m2, &n->center);
            self->targetX = m2.x;
            self->targetY = m2.y;
            self->targetZ = m2.z;
            self->targetKind = n->kind;
            self->targetIndex = n->index;
        }
        n = n->next;
    }
    self->spheres = 0;
    self->cylinders = 0;
    self->triangles = 0;
}

}

TouchPickResult::TouchPickResult() {}

TouchPickResult::~TouchPickResult() {}

extern "C" BOOL TouchPick_GetGroundPos(TouchPickResult *r, VecFx32 *out) {
    if (out) {
        out->x = r->groundX;
        out->y = r->groundY;
        out->z = r->groundZ;
    }
    if (r->groundX != (s32)0xffed4000) {
        return TRUE;
    }
    return FALSE;
}

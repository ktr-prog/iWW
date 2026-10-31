#include "types.h"
#include "host_overlay_vars.h"
#include "gfx/VecFx32.h"
#include "gfx/Camera.h"
#include "gfx/DebugColor.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020943dc.h"
#include "proto/ov004/unk_ov004_0223f43c.h"


struct CameraSetup {
    s16 a, b;
    s32 w0;
    VecFx32CtorDtor p;
    VecFx32CtorDtor q;
    ~CameraSetup();
};

struct CameraKkShowState {
    s16 yawOffset, shotIndex, shotState, recentShot0, recentShot1, recentSlot, numChoices;
    u8 b0 : 1;
    u8 b1 : 1;
};

struct CameraKkShowShot {
    s32 focusX, focusY, focusZ, orbitX, orbitZ, distance, distanceStep;
    s16 yaw, pitch, yawStep;
    s16 pad;
};

extern "C" {
extern Camera *gCamera;
extern VecFx32 gVec3Zero;
extern s16 data_02135f44[];
extern u32 sCameraPoseGrid[][3];
extern CameraSetup sCameraKkShowSetup;
extern CameraSetup sCameraKkShowPrevSetup;
extern CameraSetup sCameraKkShowWideSetup;
extern u32 data_ov004_0224f31c[];
extern u32 data_ov004_0224f32c[];
extern u32 data_ov004_0224f33c[];
extern CameraKkShowShot sCameraKkShowShots[];
extern const VecFx32 data_ov004_02246838;
extern const VecFx32 data_ov004_0224682c;
s32 Scene_GetCurrent(void);
s32 func_01ffcb0c(s32 a, s32 b);
s32 FX_Div(s32 a, s32 b);
void VEC_Subtract(void *a, void *b, void *c);
void VEC_Add(void *a, void *b, void *c);
void Vec_ShiftRightTo(void *out, void *in, s32 s);
void Vec_RotateY(void *v, s32 a);
void Camera_StartBlend(void);
void Camera_FinishBlend(void);
void Camera_PlaySe(Camera *o, s32 a);
s32 Camera_CalcPointSpan(void *p, void *a, s32 *b, s32 *out);

void Camera_KkShowResetShot(Camera *o);
void Camera_KkShowPickShot(Camera *o);
void Camera_KkShowWideShot(Camera *o);
}

#define Unk_0223f44c_Finish(o)                                          \
    do {                                                                \
        VecFx32 cam;                                           \
        s32 p, q;                                                       \
        (o)->updateBlend();                                             \
        Camera_GetLookAtPoint(&cam, o);                                 \
        p = (o)->getPitch();                                            \
        q = (o)->getYaw();                                              \
        (o)->setLookAtOrbit(&cam, p, q, (o)->getDistance());            \
    } while (0)

extern "C" {

void Camera_UpdateRoomFocus(Camera *self) {
    VecFx32 *p;
    s32 lim;
    s32 sp4;
    s32 sp8;
    s32 inv;
    s32 sc;
    s32 dy;
    VecFx32 d;
    s32 ang, r7;
    s32 t;
    p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    t = Camera_CalcPointSpan(p, &self->focusPointA, &self->targetFocus.x, &dy);
    if (t < 0x4800) {
        t = 0x4800;
    } else if (t > 0xb000) {
        t = 0xb000;
    }
    sc = FX_Div(t - 0x4800, 0x6800);
    inv = 0x1000 - sc;
    self->closeUpFactorTarget = inv;
    (self)->lerpPoses(0xb, sCameraPoseGrid[self->presetRow][self->presetCol], sc);
    d = gVec3Zero;
    if (p->z > self->focusPointA.z) {
        d = *p;
    } else {
        d.x = self->focusPointA.x;
        d.y = self->focusPointA.y;
        d.z = self->focusPointA.z;
    }
    sp4 = (self)->getRoomEdgeSide(&self->targetFocus.x);
    sp8 = 0;
    ang = Math_AngleXZ(&self->targetFocus, &d);
    s32 av = ang < 0 ? (s16)-ang : ang;
    t = 0x2000 - av;
    if (t < 0) t = 0;
    s32 q = func_01ffcb0c(t >> 1, 0x2000);
    lim = (s16)func_01ffcb0c(q, 0xe02);
    if (lim > 0xe02) lim = 0xe02;
    if (lim > 0 && self->focusYawLocked == 0) {
        if (self->roomFocusSide == 3) {
            if (ang > 0) r7 = 1; else r7 = 2;
            if (sp4 == 1 && r7 == 1) {
                s32 b = ang < 0 ? (s16)-ang : ang;
                if (b > 0x701) r7 = 0; else r7 = 2;
            }
            if (sp4 == 2 && r7 == 2) {
                if (ang < 0) ang = (s16)-ang;
                if (ang > 0x701) r7 = 0; else r7 = 1;
            }
            if (Scene_GetCurrent() == 0x10) r7 = 1;
            self->roomFocusSide = r7;
        }
        u32 m = self->roomFocusSide;
        if (m == 1) lim = (s16)-lim;
        if (m != 0) {
            self->target.h0 = func_01ffcb0c(lim, inv);
            sp8 = func_01ffcb0c(dy, data_02135f44[((u16)self->target.h0 >> 4) * 2]);
        }
    }
    self->targetFocus.z += dy;
    self->targetFocus.x += sp8;
}

BOOL Camera_InitMode10(Camera *self) {
    (self)->loadPose(0x11, (CameraPose *)(0));
    (self)->setBlendPreset(0);
    self->targetFocus.x = gVec3Zero.x;
    self->targetFocus.y = gVec3Zero.y;
    self->targetFocus.z = gVec3Zero.z;
    Camera_FinishBlend();
    return TRUE;
}

BOOL Camera_StartBlendToPlayer(Camera *self) {
    (self)->loadPose(sCameraPoseGrid[1][1], (CameraPose *)(0));
    (self)->setBlendPreset(0);
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    self->targetFocus.x = p->x;
    self->targetFocus.y = p->y;
    self->targetFocus.z = p->z;
    Camera_StartBlend();
    return TRUE;
}

void Camera_UpdateMode10(Camera *self) {
    VecFx32 v;
    (self)->updateBlend();
    Camera_GetLookAtPoint(&v, self);
    s32 a = (self)->getPitch();
    s32 b = (self)->getYaw();
    (self)->setLookAtOrbit(&v, a, b, (self)->getDistance());
}

s32 Camera_GetShopTier() {
    s32 r = 0;
    switch (Scene_GetCurrent()) {
    case 0x1a:
        r = 0;
        break;
    case 0x1b:
        r = 1;
        break;
    case 0x1c:
        r = 2;
        break;
    case 0x1d:
    case 0x1e:
        r = 3;
        break;
    }
    return r;
}

BOOL Camera_SetMode11() {
    if (gCamera) {
        return (gCamera)->setMode(11);
    }
    return FALSE;
}

BOOL Camera_SetMode12() {
    if (gCamera) {
        return (gCamera)->setMode(12);
    }
    return FALSE;
}

BOOL Camera_InitMode11(Camera *o) {
    (o)->loadPose(Camera_GetShopTier() + 0x12, (CameraPose *)(0));
    (o)->setBlendPreset(0);
    Camera_StartBlend();
    return TRUE;
}

void Camera_UpdateMode11(Camera *o) {
    volatile s32 a, b, c;
    a = 0;
    b = 0;
    c = 0;
    o->targetFocus.x = 0;
    o->targetFocus.y = b;
    o->targetFocus.z = c;
    Unk_0223f44c_Finish(o);
}

BOOL Camera_InitMode12(Camera *o) {
    (o)->loadPose(Camera_GetShopTier() + 0x16, (CameraPose *)(0));
    (o)->setBlendPreset(0);
    Camera_StartBlend();
    return TRUE;
}

void Camera_UpdateMode12(Camera *o) {
    volatile s32 a, b, c;
    a = 0;
    b = 0;
    c = 0;
    o->targetFocus.x = 0;
    o->targetFocus.y = b;
    o->targetFocus.z = c;
    Unk_0223f44c_Finish(o);
}

BOOL Camera_SetMode16At(VecFx32 *v) {
    Camera *c = gCamera;
    if (c) {
        VecFx32 *d = (VecFx32 *)&c->focusPointA;
        *d = *v;
        return (gCamera)->setMode(0x10);
    }
    return FALSE;
}

BOOL Camera_InitMode16(Camera *o) {
    PlayerActor_GetBodyPos(4);
    (o)->loadPose(0x1e, (CameraPose *)(0));
    (o)->setBlendPreset(0);
    Camera_StartBlend();
    Camera_PlaySe(o, 0x2f);
    return TRUE;
}

void Camera_UpdateMode16(Camera *o) {
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 a, b;
    s32 d;
    Vec_Add(&a, p, &o->focusPointA);
    Vec_ShiftRightTo(&b, &a, 1);
    o->targetFocus.x = b.x;
    o->targetFocus.y = b.y;
    o->targetFocus.z = b.z;
    d = p->z - o->focusPointA.z;
    if (d < 0) {
        d = -d;
    }
    o->targetFocus.z = o->targetFocus.z + (d >> 1);
    Unk_0223f44c_Finish(o);
}

BOOL Camera_InitMode14(Camera *o) {
    (o)->loadPose(sCameraPoseGrid[o->presetRow][o->presetCol], (CameraPose *)(0));
    (o)->setBlendPreset(0);
    Camera_StartBlend();
    return TRUE;
}

void Camera_UpdateMode14(Camera *o) {
    o->targetFocus.x = data_ov004_0224682c.x;
    o->targetFocus.y = data_ov004_0224682c.y;
    o->targetFocus.z = data_ov004_0224682c.z;
    Unk_0223f44c_Finish(o);
}

BOOL Camera_InitMode15(Camera *o) {
    (o)->loadPose(0x1d, (CameraPose *)(0));
    (o)->setBlendPreset(4);
    Camera_StartBlend();
    return TRUE;
}

void Camera_UpdateMode15(Camera *o) {
    o->targetFocus.x = data_ov004_02246838.x;
    o->targetFocus.y = data_ov004_02246838.y;
    o->targetFocus.z = data_ov004_02246838.z;
    Unk_0223f44c_Finish(o);
}

void Camera_SetMode14(void) {
    (gCamera)->setMode(0xe);
}

void Camera_SetMode15(void) {
    (gCamera)->setMode(0xf);
}

BOOL Camera_InitMode20(Camera *o) {
    (o)->loadPose(0x20, (CameraPose *)(0));
    Camera_FinishBlend();
    return TRUE;
}

void Camera_UpdateMode20(Camera *o) {
    o->targetFocus.x = o->focusPointA.x;
    o->targetFocus.y = o->focusPointA.y;
    o->targetFocus.z = o->focusPointA.z;
    Unk_0223f44c_Finish(o);
}

void Camera_SetMode20At(VecFx32 *v) {
    *(VecFx32 *)&gCamera->focusPointA = *v;
    (gCamera)->setMode(0x14);
}

void Camera_SetMode18(void) {
    (gCamera)->setMode(0x12);
}

void RoomCamera_KkShowWideShot(void) {
    Camera_KkShowWideShot(gCamera);
}

void RoomCamera_KkShowPickShot(void) {
    Camera_KkShowPickShot(gCamera);
}

void RoomCamera_KkShowResetShot(void) {
    Camera_KkShowResetShot(gCamera);
}

#define COPY_TBL(o, t)                 \
    o->target.h0 = t.a;                   \
    o->target.h1 = t.b;                   \
    o->target.w0 = t.w0;                 \
    o->target.x = t.p.x;                \
    o->target.y = t.p.y;                \
    o->target.z = t.p.z;                \
    o->targetFocus.x = t.q.x;                \
    o->targetFocus.y = t.q.y;                \
    o->targetFocus.z = t.q.z

BOOL Camera_InitMode18(Camera *o) {
    CameraKkShowState *m = (CameraKkShowState *)&o->modeParam;
    m->yawOffset = 0;
    m->shotIndex = -1;
    m->shotState = 0;
    m->recentShot0 = -1;
    m->recentShot1 = -1;
    m->recentSlot = 0;
    m->numChoices = 0xe;
    m->b0 = 0;
    m->b1 = 0;
    COPY_TBL(o, sCameraKkShowSetup);
    (o)->setBlendParams(data_ov004_0224f32c);
    Camera_StartBlend();
    return TRUE;
}

void Camera_UpdateMode18(Camera *o) {
    CameraKkShowState *m = (CameraKkShowState *)&o->modeParam;
    CameraKkShowShot *e;
    if (m->shotState == 1) {
        e = &sCameraKkShowShots[m->shotIndex];
        o->targetFocus.x = e->focusX;
        o->targetFocus.y = e->focusY;
        o->targetFocus.z = e->focusZ;
        VEC_Subtract(&o->targetFocus.x, &o->target.x, &o->targetFocus.x);
        if ((o)->getDistance() > 0x1400) {
            o->target.w0 = o->target.w0 + e->distanceStep;
        }
        o->target.h0 = o->target.h0 + e->yawStep;
        m->yawOffset = m->yawOffset + e->yawStep;
        {
            VecFx32Ctor t(e->orbitX, 0, e->orbitZ);
            VEC_Add(&o->targetFocus.x, &t, &o->targetFocus.x);
            Vec_RotateY(&t, m->yawOffset);
            VEC_Subtract(&o->targetFocus.x, &t, &o->targetFocus.x);
        }
    }
    Unk_0223f44c_Finish(o);
}

void Camera_KkShowWideShot(Camera *o) {
    COPY_TBL(o, sCameraKkShowWideSetup);
    (o)->setBlendParams(data_ov004_0224f33c);
    Camera_StartBlend();
}

void Camera_KkShowPickShot(Camera *o) {
    CameraKkShowState *m = (CameraKkShowState *)&o->modeParam;
    CameraKkShowShot *e;
    s32 lim[2];
    s32 i;
    m->yawOffset = 0;
    if (Random_GlobalBelow(2) == 1) {
        m->shotIndex = Random_GlobalBelow(m->numChoices - 2);
    } else {
        m->shotIndex = Random_GlobalBelow(m->numChoices);
    }
    {
        s32 b = m->recentShot1;
        s32 a = m->recentShot0;
        if (a > b) {
            lim[0] = b;
            lim[1] = a;
        } else {
            lim[0] = a;
            lim[1] = b;
        }
    }
    for (i = 0; i < 2; i++) {
        s32 l = lim[i];
        if (l != -1 && m->shotIndex >> 1 >= l >> 1) {
            m->shotIndex += 2;
        }
    }
    if ((&m->recentShot0)[m->recentSlot] == -1) {
        m->numChoices = m->numChoices - 2;
    }
    (&m->recentShot0)[m->recentSlot] = m->shotIndex;
    m->recentSlot = m->recentSlot ^ 1;
    m->shotState = 1;
    e = &sCameraKkShowShots[m->shotIndex];
    o->targetFocus.x = e->focusX;
    o->targetFocus.y = e->focusY;
    o->targetFocus.z = e->focusZ;
    {
        void *p = &o->targetFocus.x;
        VEC_Subtract(p, &o->target.x, p);
    }
    o->target.h1 = e->pitch;
    o->target.h0 = e->yaw;
    o->target.w0 = e->distance;
    Camera_FinishBlend();
}

void Camera_KkShowResetShot(Camera *o) {
    CameraKkShowState *m = (CameraKkShowState *)&o->modeParam;
    m->yawOffset = 0;
    m->shotIndex = 0;
    m->shotState = 2;
    COPY_TBL(o, sCameraKkShowSetup);
    o->current = sCameraKkShowPrevSetup.a;
    o->currentPitch = sCameraKkShowPrevSetup.b;
    o->currentDistance = sCameraKkShowPrevSetup.w0;
    o->currentOffset = sCameraKkShowPrevSetup.p.x;
    o->currentOffsetY = sCameraKkShowPrevSetup.p.y;
    o->currentOffsetZ = sCameraKkShowPrevSetup.p.z;
    o->currentFocus = sCameraKkShowPrevSetup.q.x;
    o->currentFocusY = sCameraKkShowPrevSetup.q.y;
    o->currentFocusZ = sCameraKkShowPrevSetup.q.z;
    (o)->setBlendParams(data_ov004_0224f31c);
    Camera_StartBlend();
}

void RoomCamera_StartBlendToPlayer(void) {
    Camera_StartBlendToPlayer(gCamera);
}

}

DebugColor data_ov004_022589a4(31, 20, 20, 31);
DebugColor data_ov004_02258994(20, 20, 31, 31);
DebugColor data_ov004_02258990(31, 31, 20, 31);
const VecFx32 data_ov004_02246838 = {0x10000, 0, 0x11000};
DebugColor data_ov004_022589a0(20, 31, 20, 31);
const VecFx32 data_ov004_0224682c = {0x10000, 0, 0x11000};
u32 data_ov004_0224f32c[4] = {0, 0x3c000, 0x5000, 0x5000};
DebugColor data_ov004_02258998(20, 31, 31, 31);
DebugColor data_ov004_0225899c(20, 24, 24, 31);
CameraSetup sCameraKkShowSetup;
u32 data_ov004_0224f31c[4] = {0, 0x438000, 0, 0x384000};
u32 data_ov004_0224f33c[4] = {0, 0x7d0000, 0x7d0000, 0};
CameraSetup sCameraKkShowWideSetup;
CameraKkShowShot sCameraKkShowShots[14] = {
    {0xf9fc, 0x2000, 0x157c2, -2009, -8523, 0xe700, 0x0, -12544, 3328, 40, 0},
    {0xf623, 0x1b00, 0x11405, -1571, 0x1bfb, 0xb000, 0x20, 15104, 1280, -48, 0},
    {0x10fba, 0x2000, 0x14874, -9072, -4623, 0x8d00, 0x0, -17408, -256, 48, 0},
    {0x1291d, 0x2500, 0x14105, -14621, -4357, 0x3d00, 0x0, 10496, 768, -48, 0},
    {0x122ac, 0x2000, 0x12de6, -12972, 0x21a, 0x13c00, -32, -6144, 512, 32, 0},
    {0xf895, 0x1b00, 0xf717, -1621, 0x3df2, 0x14600, 0x0, 7680, 1536, -32, 0},
    {0x13600, 0x2000, 0x16200, 0x0, 0x0, 0x12300, 0x80, 0, 15616, -96, 0},
    {0x13179, 0x1b00, 0x15f6e, 0x3ae, 0xf2, 0x15f00, -48, 15872, 11008, 96, 0},
    {0x10400, 0x2000, 0x13000, -5120, 0x0, 0x8800, 0x70, 0, 2816, 16, 0},
    {0x12070, 0x2a00, 0x13425, -12400, -1061, 0x3800, 0xa0, 12032, 2304, -16, 0},
    {0xf826, 0x2000, 0x199af, 0x39ee, 0xdd8, 0x11e00, 0x0, 22784, 2304, 24, 0},
    {0x12f28, 0x2000, 0x1b890, -261, -5145, 0x8300, 0x0, -26112, 0, -40, 0},
    {0x18412, 0x1100, 0x15882, 0x124b, -2178, 0x7900, 0x0, 29952, 5120, 24, 0},
    {0x1a6f6, 0x2000, 0x15892, -5483, -2535, 0xe700, -48, -13568, 2560, -24, 0},
};

CameraSetup sCameraKkShowPrevSetup;

extern "C" void StaticInit_unk_ov004_0223f43c(void) {
    HOST_STATIC_INIT(sCameraKkShowSetup, {0, 0x1100, 0x14100, VecFx32CtorDtor(0, 0x1e14, 0xf0a), VecFx32CtorDtor(0x13600, 0x200, 0x17600)});
    HOST_STATIC_INIT(sCameraKkShowWideSetup, {0, -0x200, 0x6a00, VecFx32CtorDtor(0, 0x1e14, 0xf0a), VecFx32CtorDtor(0x10400, 0x200, 0x12b00)});
    HOST_STATIC_INIT(sCameraKkShowPrevSetup, {0x1b00, 0x1000, 0x9700, VecFx32CtorDtor(0, 0x1e14, 0xf0a), VecFx32CtorDtor(0xf5ad, 0x200, 0x12757)});
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0223f43c) {
    HOST_OVERLAY_VAR(data_ov004_022589a4),
    HOST_OVERLAY_VAR(data_ov004_02258994),
    HOST_OVERLAY_VAR(data_ov004_02258990),
    HOST_OVERLAY_VAR(data_ov004_022589a0),
    HOST_OVERLAY_VAR(data_ov004_0224f32c),
    HOST_OVERLAY_VAR(data_ov004_02258998),
    HOST_OVERLAY_VAR(data_ov004_0225899c),
    HOST_OVERLAY_VAR(sCameraKkShowSetup),
    HOST_OVERLAY_VAR(data_ov004_0224f31c),
    HOST_OVERLAY_VAR(data_ov004_0224f33c),
    HOST_OVERLAY_VAR(sCameraKkShowWideSetup),
    HOST_OVERLAY_VAR(sCameraKkShowShots),
    HOST_OVERLAY_VAR(sCameraKkShowPrevSetup),
    HOST_OVERLAY_VARS_END
};

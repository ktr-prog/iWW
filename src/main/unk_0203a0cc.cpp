#include "uptr.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "gfx/Unk_0203bd10_Dtcm.h"
#include "actor/VillagerActor.h"
#include "town/BlockMap.h"
#include "town/MapBlock.h"
#include "gfx/CameraPose.h"
#include "gfx/CameraSetup.h"
#include "gfx/FxMtx43.h"
#include "sys/CameraBase.h"
#include "gfx/Camera.h"
#include "game/SceneInfo.h"
#include "sys/ProcProfile.h"
#include "gfx/CameraSway.h"
#include "gfx/DebugColor.h"
#include "gfx/ViewFrustum.h"
#include "player/PlayerData.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203a0cc.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_0222ee6c.h"
#include "proto/ov068/unk_ov068_0226647c.h"

typedef VecFx32 V3;

struct FxVec3 : VecFx32Copy {
    FxVec3() {}
};

struct MtxFx43 {
    s32 m[12];
};




struct CameraPoseGridRow {
    s32 v[3];
};

struct CameraShakeParam {
    s32 len;
    s16 ang, vel;
};











class Camera;
typedef BOOL (*CameraModeInitFn)(Camera *c);
typedef void (*CameraModeUpdateFn)(Camera *c);
struct CameraModeEntry {
    CameraModeInitFn init;
    CameraModeUpdateFn update;
};


static inline BOOL Unk_0203c23c_InRange(u16 c, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (c >= lo && c <= hi) r = TRUE;
    return r;
}

static inline BOOL Unk_0203c23c_InRangeP(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

static inline s32 Unk_0203c23c_Idx(u16 c, u32 lo, u32 hi) {
    if (Unk_0203c23c_InRange(c, lo, hi)) return c - lo;
    return -1;
}

static inline s32 Unk_0203c23c_None() {
    return Unk_0203c23c_Idx(0, 1, 0);
}

#define R096_TAIL(V) \
    updateBlend(); \
    Camera_GetLookAtPoint(&V, this); \
    s32 a = getPitch(); \
    s32 b = getYaw(); \
    setLookAtOrbit(&V, a, b, getDistance());

extern "C" {
extern Camera *gCamera;
extern MtxFx43 data_021f47e0;
extern s32 sCameraSpanDepthScale;
extern s32 sCameraFollowVillagerIdx;
extern s16 data_02135f44[];
extern VecFx32 gVec3Zero;
extern SceneInfo *gCurSceneInfo;
extern const CameraPoseGridRow sCameraPoseGrid[3];
extern s32 data_020c8cb8;
extern BlockMap *gSceneBlockMap;
extern u8 gViewFrustum[];
extern u32 data_021c3240;
extern u16 data_021c323c;
extern u8 data_020d9400[];
#define data_027e0148 HOST_LABEL(u32 (*)[], data_027e0148)
#define data_027e02c8 HOST_LABEL(Unk_0203bd10_Dtcm *, data_027e02c8)
#define data_027e00d0 HOST_LABEL(u32 (*)[], data_027e00d0)
#define data_027e0114 HOST_LABEL(u32 (*)[], data_027e0114)
}
extern CameraModeEntry sCameraModeTable[];
extern const u32 sCameraBlendTable[6][4];
extern const CameraPose sCameraPoseTable[33];
extern FxVec3 gCameraLookAt;
extern FxVec3 gCameraEye;
extern FxVec3 sCameraSavedEye;
extern CameraSetup sCameraSavedSetup;
extern s32 gCameraDistance;

extern "C" {
void MTX_MultVec43(void *in, void *m, void *out);
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
void Vec_Scale(void *v, s32 s);
s32 Scene_GetCurrent();
void Vec_Sub(void *out, void *a, void *b);
void Vec_ShiftRightTo(void *out, void *in, s32 s);
s32 VEC_Mag(void *v);
void MTX_MultVec33(void *a, void *b, void *c);
void VEC_Add(void *a, void *b, void *c);
void Math_StepS16(s16 *p, s32 a, s32 b);
void Math_ApproachS32(s32 *p, s32 a, s32 b, s32 c, s32 d);
s32 Vec_MagXZ(void *v);
void Vec_RotateX(void *v, s32 a);
void Vec_RotateY(void *v, s32 a);
s32 Scene_InHouseRoom();
s32 Scene_InVillagerHouse();
s32 Scene_InMuseumRoom();
void Camera_UpdateRoomFocus(Camera *self);
BOOL Vec_SafeNormalize(void *v);
void Vec_RotateZ(void *v, s32 a);
s32 FX_Inv(s32);
s32 Ground_GetFloorBounds(s32 *, s32 *, s32 *, s32 *);
void MTX_Inverse43(void *a, void *b);
void Vec_ScaleTo(void *out, void *a, s32 n);
void G3i_PerspectiveW_(s32 fovySin, s32 fovyCos, s32 aspect, s32 near, s32 far, s32 scale, BOOL load, s32 *mtx);
void G3i_LookAt_(void *a, void *b, void *c, s32 d, void *e);
u8 Scene_GetPrevious();
BOOL SceneId_IsHouseRoom(s32 x);
void *NNS_G3dGetTex(void *p);
void func_02135558(void *a, void *b, void *c);
void *func_020986c8(void *s);
BOOL Item_IsNormalItem(u16 *p);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Item_GetPaperIndex(u16 *p);
s32 Item_MakeFurniture(s32 a, s32 b);
BOOL Item_TestInfoFlag3(u16 *p);
}


extern "C" {
BOOL Camera_SetModeDefault(void);
MtxFx43 *Camera_GetViewMatrix(void);
void Camera_StartBlend(void);
void Camera_FinishBlend(void);
s32 Camera_CalcPointSpan(VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 *d);
s32 Camera_CalcTriangleSpan(VecFx32 *a, VecFx32 *b, VecFx32 *c, VecFx32 *d, s32 *e);
BOOL Camera_ProjectToScreen(s32 *x, s32 *y, VecFx32 *p);
BOOL Camera_IsBlending(void);
void Camera_RestoreView(void);
void Camera_PlaySe(Camera *o, s32 a);
void Camera_GetLookAtBlock(Camera *a, s32 *x, s32 *z);
}

extern "C" {
}

extern "C" void *CarpetTex_GetTex(void *p) {
    return NNS_G3dGetTex(p);
}

CameraSetup::~CameraSetup() {}

extern "C" Camera *Camera_Create() {
    return new Camera();
}

void Camera::loadPose(s32 i, CameraPose *out) {
    if (!out) out = &target;
    out->x = sCameraPoseTable[i].x;
    out->y = sCameraPoseTable[i].y;
    out->z = sCameraPoseTable[i].z;
    out->w0 = sCameraPoseTable[i].w0;
    out->h1 = sCameraPoseTable[i].h1;
    out->h0 = sCameraPoseTable[i].h0;
}

void Camera::lerpPoses(s32 a, s32 b, s32 n) {
    VecFx32 d, q;
    d.x = sCameraPoseTable[b].x - sCameraPoseTable[a].x;
    d.y = sCameraPoseTable[b].y - sCameraPoseTable[a].y;
    d.z = sCameraPoseTable[b].z - sCameraPoseTable[a].z;
    target.x = sCameraPoseTable[a].x;
    target.y = sCameraPoseTable[a].y;
    target.z = sCameraPoseTable[a].z;
    s32 w = sCameraPoseTable[a].w0;
    target.w0 = w;
    s16 h1 = sCameraPoseTable[a].h1;
    target.h1 = h1;
    s16 h0 = sCameraPoseTable[a].h0;
    target.h0 = h0;
    Vec_ScaleTo(&q, &d, n);
    VEC_Add(&target.x, &q, &target.x);
    target.w0 += func_01ffcb0c(sCameraPoseTable[b].w0 - w, n);
    target.h1 = target.h1 + (s16)func_01ffcb0c((s16)(sCameraPoseTable[b].h1 - h1), n);
    target.h0 = target.h0 + (s16)func_01ffcb0c((s16)(sCameraPoseTable[b].h0 - h0), n);
}

void Camera::setBlendPreset(s32 i) {
    setBlendParams((u32 *)sCameraBlendTable[i]);
}

void Camera::setBlendParams(u32 *src) {
    blendDelay = src[0];
    blendEnd = src[1];
    blendEaseIn = src[2];
    blendEaseOut = src[3];
}

BOOL Camera::onCreate() {
    gCamera = (Camera *)this;
    resetOffsets();
    presetCol = 1;
    presetRow = 1;
    fovy = 0x1555;
    closeUpFactorTarget = 0;
    closeUpFactor = 0;
    mode = prevMode = 0;
    if (setMode(0)) {
        CameraPose *p = (CameraPose *)PlayerActor_GetBodyPos(4);
        if (p) {
            targetFocus.x = ((s32 *)p)[0];
            targetFocus.y = ((s32 *)p)[1];
            targetFocus.z = ((s32 *)p)[2];
        }
    }
    calcRoomBounds();
    s32 r = Scene_GetCurrent();
    if (r == 9) {
        sCameraSpanDepthScale = 0x1000;
    } else {
        sCameraSpanDepthScale = 0x1800;
    }
    switch (r) {
    case 0x2c: {
        VillagerActor *p = 0;
        s32 *g = &sCameraFollowVillagerIdx;
        s32 i = *g;
        if (i == 8) {
            p = (VillagerActor *)NpcRegistry_PickRandomVillager(g);
        } else {
            i = i + 1;
            if (i == 8) {
                i = 0;
            } else {
                while (i != sCameraFollowVillagerIdx) {
                    p = (VillagerActor *)NpcRegistry_GetVillager(i);
                    if (p) {
                        if (p->isPickable()) break;
                    }
                    i++;
                    if (i == 8) {
                        i = 0;
                        break;
                    }
                }
            }
            sCameraFollowVillagerIdx = i;
        }
        if (p) {
            followTarget = p;
            setMode(7);
        } else {
            sCameraFollowVillagerIdx = 8;
            setMode(8);
        }
        break;
    }
    case 0x2d:
        setMode(9);
        break;
    case 6:
        setMode(0xa);
        break;
    case 13:
    case 14:
    case 0x2f:
        setMode(0xe);
        break;
    case 12:
        setMode(6);
        break;
    case 0: {
        void *s = PlayerData_GetCurrent();
        if (s) {
            if (((PlayerData *)(s))->testFlag(0x23)) {
                if (SceneId_IsHouseRoom(Scene_GetPrevious()) != 0 || Scene_GetPrevious() == 6) setMode(0xd);
            }
        }
        break;
    }
    }
    onDraw();
    prevMode = mode;
    startMode = prevMode;
    Camera_FinishBlend();
    return TRUE;
}

BOOL Camera::onExecute() {
    s32 v[4];
    updateMode();
    Camera_GetLookAtPoint((VecFx32 *)v, this);
    WorldCurve_Update(&gWorldCurve, (VecFx32 *)v);
    return TRUE;
}

BOOL Camera::onDraw() {
    s32 i = fovy >> 5;
    s32 k = i * 2;
    G3i_PerspectiveW_(data_02135f44[k], data_02135f44[k + 1], aspect, nearClip, farClip, 0x1000, 1, NULL);
    G3i_LookAt_(&lookEye, &lookUp, &lookTarget, 1, pad_00);
    MTX_Inverse43(pad_00, invViewMtx);
    s32 j = (s16)(fovy + fovyOffset) >> 5;
    s32 m = j * 2;
    G3i_PerspectiveW_(data_02135f44[m], data_02135f44[m + 1], aspect, nearClip + nearOffset, farClip + farOffset, 0x1000, 0,
                  (s32 *)data_027e00d0);
    data_027e0148[0x7c / 4] &= ~0x50;
    data_027e02c8.a = lookEye;
    data_027e02c8.b = lookEyeY;
    data_027e02c8.c = lookEyeZ;
    data_027e02c8.d = lookUp;
    data_027e02c8.e = lookUpY;
    data_027e02c8.f = lookUpZ;
    data_027e02c8.g = lookTarget;
    data_027e02c8.h = lookTargetY;
    data_027e02c8.i = lookTargetZ;
    G3i_LookAt_(&lookEye, &lookUp, &lookTarget, 0, data_027e0114);
    data_027e0148[0x7c / 4] &= ~0xe8;
    return CameraBase::onDraw();
}

BOOL Camera::onDelete() {
    gCamera = 0;
    return TRUE;
}

void Camera::resetOffsets() {
    distanceOffset = 0;
    pitchOffset = 0;
    yawOffset = 0;
    unk_84 = 0;
    unk_88 = 0;
    unk_8c = 0;
    fovyOffset = 0;
    nearOffset = 0;
    farOffset = 0;
    followSlackOffset = 0;
    blendDelayOffset = 0;
    blendEndOffset = 0;
    blendEaseInOffset = 0;
    blendEaseOutOffset = 0;
}

V3 *Camera::getEye() {
    return (V3 *)&eye;
}

s16 Camera::getEyeCurveAngle() {
    return eyeCurveAngle;
}

s16 Camera::getPitch() {
    return currentPitch + pitchOffset;
}

s16 Camera::getYaw() {
    return current + yawOffset;
}

s32 Camera::getFollowSlack() {
    return followSlackOffset + 0xf0a;
}

s32 Camera::getDistance()
{
    return currentDistance + distanceOffset;
}

s32 Camera::getFovTan()
{
    return fovTan;
}

s32 Camera::getBlendDelay()
{
    s32 r = blendDelay + blendDelayOffset;
    if (r < 0) r = 0;
    return r;
}

s32 Camera::getBlendEnd()
{
    s32 a = getBlendEaseOut();
    s32 b = getBlendDelay();
    s32 tot = a + (b + getBlendEaseIn());
    if (blendEnd < tot) blendEnd = tot;
    s32 t = blendEnd + blendEndOffset;
    if (t >= tot) tot = t;
    return tot;
}

s32 Camera::getBlendEaseIn()
{
    s32 r = blendEaseIn + blendEaseInOffset;
    if (r < 0) r = 0;
    return r;
}

s32 Camera::getBlendEaseOut()
{
    s32 r = blendEaseOut + blendEaseOutOffset;
    if (r < 0) r = 0;
    return r;
}

void Camera::setFovy(s32 a)
{
    fovy = a;
    s32 i = (u16)((s16)(fovy + fovyOffset) >> 1) >> 4;
    fovSin = data_02135f44[i * 2];
    i = (u16)((s16)(fovy + fovyOffset) >> 1) >> 4;
    fovCos = data_02135f44[i * 2 + 1];
    fovTan = func_01ffcb0c(fovSin, FX_Inv(fovCos));
    ((ViewFrustum *)(gViewFrustum))->setPerspective(aspect, (s16)(fovy + fovyOffset), nearClip + nearOffset,
                  farClip + farOffset);
}

void Camera::updateEyeCurveAngle()
{
    eyeCurveAngle = WorldCurve_GetHorizonAngle((VecFx32 *)&lookEye);
}

extern "C" void Camera_GetLookAtBlock(Camera *a, s32 *x, s32 *z)
{
    V3 t;
    Camera_GetLookAtPoint(&t, a);
    *x = t.x >> 17;
    *z = t.z >> 17;
}

void Camera::calcRoomBounds()
{
    if (gCurSceneInfo->isOutdoor == 0) {
        Ground_GetFloorBounds(&roomMinX, &roomMaxX, &roomMinZ, &roomMaxZ);
        s32 m = data_020c8cb8;
        if (roomMaxZ < m) {
            roomMaxZ = m;
        }
    }
    if (Scene_GetCurrent() == 0x29) {
        roomMaxX += 0x4000;
        roomMaxZ += 0x4000;
    } else {
        BlockMap *g = gSceneBlockMap;
        MapBlock *arg;
        if ((u32)g->width > 0 && (u32)g->height > 0 && g->blocks != 0) {
            arg = g->blocks;
        } else {
            arg = NULL;
        }
        switch ((u32)arg->acreId - 0x1009) {
        case 0:
        case 3:
            roomMinX += 0x2000;
            break;
        case 1:
            roomMaxX -= 0x2000;
            break;
        case 2:
        case 4:
            roomMinX += 0x2000;
            roomMaxX -= 0x2000;
            break;
        }
    }
}

BOOL Camera::clampToRoomBounds(s32 *p)
{
    BOOL r = FALSE;
    if (roomMaxX - roomMinX <= 0xa000) {
        p[0] = (roomMaxX + roomMinX) >> 1;
        r = TRUE;
    } else if (p[0] < roomMinX + 0x5000) {
        p[0] = roomMinX + 0x5000;
        r = TRUE;
    } else if (p[0] > roomMaxX - 0x5000) {
        p[0] = roomMaxX - 0x5000;
        r = TRUE;
    }
    if (roomMaxZ - roomMinZ <= 0x7000) {
        p[2] = (roomMaxZ + roomMinZ) >> 1;
        r = TRUE;
    } else if (p[2] < roomMinZ + 0x2000) {
        p[2] = roomMinZ + 0x2000;
        r = TRUE;
    } else if (p[2] > roomMaxZ - 0x5000) {
        p[2] = roomMaxZ - 0x5000;
        r = TRUE;
    }
    return r;
}

void Camera::setFocusPreset11(u8 *o, V3 *v)
{
    if (o == NULL) {
        o = (u8 *)&target;
    }
    loadPose(0xb, 0);
    ((V3 *)(o + 0x14))->x = v->x;
    ((V3 *)(o + 0x14))->y = v->y;
    ((V3 *)(o + 0x14))->z = v->z;
}

s32 Camera::getRoomEdgeSide(s32 *p)
{
    s32 v = *p;
    if (v < roomMinX + 0x5000) {
        return 1;
    }
    if (v > roomMaxX - 0x5000) {
        return 2;
    }
    return 0;
}

BOOL Camera::setMode(s32 idx)
{
    if (idx < 0x15) {
        if (idx != mode) {
            prevMode = mode;
            if (idx != startMode) {
                saved = target.h0;
                savedPitch = target.h1;
                savedDistance = target.w0;
                savedOffset = target.x;
                savedOffsetY = target.y;
                savedOffsetZ = target.z;
                savedFocus = targetFocus.x;
                savedFocusY = targetFocus.y;
                savedFocusZ = targetFocus.z;
                savedEye = eye;
                savedEyeY = eyeY;
                savedEyeZ = eyeZ;
            }
        }
        viewPushed = 0;
        if (sCameraModeTable[idx].init(this)) {
            setDefaultProjection();
            mode = idx;
            updateMode();
            return TRUE;
        }
    }
    return FALSE;
}

void Camera::updateMode()
{
    s32 i = mode;
    if (i < 0x15) {
        sCameraModeTable[i].update(this);
        updateEyeCurveAngle();
    }
}

void Camera::setDefaultProjection()
{
    aspect = 0x1548;
    nearClip = 0xf6;
    farClip = 0x3e800;
    setFovy(fovy);
}

void Camera::updateBlend()
{
    V3 t1, t2, o1, o2;
    s32 a, b, c, d;
    if (Camera_IsBlending()) {
        a = getBlendDelay();
        b = getBlendEnd();
        c = getBlendEaseIn();
        d = getBlendEaseOut();
        a = Math_EaseRampProgress(blendTime, a, b, c, d);
        Vec_Sub(&t1, (V3 *)&targetFocus.x, (V3 *)&currentFocus);
        Vec_Scale(&t1, a);
        Vec_Add(&o1, (V3 *)&currentFocus, &t1);
        currentFocus = o1.x;
        currentFocusY = o1.y;
        currentFocusZ = o1.z;
        Vec_Sub(&t2, (V3 *)&target.x, (V3 *)&currentOffset);
        Vec_Scale(&t2, a);
        Vec_Add(&o2, (V3 *)&currentOffset, &t2);
        currentOffset = o2.x;
        currentOffsetY = o2.y;
        currentOffsetZ = o2.z;
        currentPitch += func_01ffcb0c(target.h1 - currentPitch, a);
        current += func_01ffcb0c(target.h0 - current, a);
        currentDistance += func_01ffcb0c(target.w0 - currentDistance, a);
        closeUpFactor += func_01ffcb0c(closeUpFactorTarget - closeUpFactor, a);
        blendTime += 0x1000;
    } else {
        currentFocus = targetFocus.x;
        currentFocusY = targetFocus.y;
        currentFocusZ = targetFocus.z;
        currentOffset = target.x;
        currentOffsetY = target.y;
        currentOffsetZ = target.z;
        currentPitch = target.h1;
        current = target.h0;
        currentDistance = target.w0;
        closeUpFactor = closeUpFactorTarget;
    }
}

void Camera::setLookAtOrbit(V3 *a, s32 r, s32 s, s32 z)
{
    V3 t, o;
    t.x = 0;
    t.y = 0;
    t.z = z;
    Vec_RotateX(&t, (s16)-r);
    Vec_RotateY(&t, s);
    Vec_Add(&o, a, &t);
    eye = o.x;
    eyeY = o.y;
    eyeZ = o.z;
    s32 ang = WorldCurve_Apply((VecFx32 *)&lookTarget, a);
    WorldCurve_Apply((VecFx32 *)&lookEye, getEye());
    lookUp = 0;
    lookUpY = 0x1000;
    lookUpZ = 0;
    Vec_RotateX((V3 *)&lookUp, ang);
    Vec_RotateZ((V3 *)&lookUp, roll);
    gCameraLookAt.x = a->x;
    gCameraLookAt.y = a->y;
    gCameraLookAt.z = a->z;
    V3 *c = getEye();
    gCameraEye.x = c->x;
    gCameraEye.y = c->y;
    gCameraEye.z = c->z;
    gCameraDistance = z;
}

void Camera::setLookAt(V3 *a, V3 *b)
{
    V3 d;
    s32 ang = WorldCurve_Apply((VecFx32 *)&lookTarget, a);
    WorldCurve_Apply((VecFx32 *)&lookEye, b);
    lookUp = 0;
    lookUpY = 0x1000;
    lookUpZ = 0;
    s32 i = (u16)ang >> 4;
    lookUpY = data_02135f44[i * 2 + 1];
    lookUpZ = data_02135f44[i * 2];
    Vec_RotateZ((V3 *)&lookUp, roll);
    gCameraLookAt.x = a->x;
    gCameraLookAt.y = a->y;
    gCameraLookAt.z = a->z;
    gCameraEye.x = b->x;
    gCameraEye.y = b->y;
    gCameraEye.z = b->z;
    Vec_Sub(&d, a, b);
    gCameraDistance = VEC_Mag(&d);
}

void Camera::dragFocusTo(V3 *p)
{
    V3 d;
    s32 len, ex;
    targetFocus.y = p->y;
    Vec_Sub(&d, &targetFocus, p);
    len = Vec_MagXZ(&d);
    if (len > getFollowSlack()) {
        ex = len - getFollowSlack();
        if (Vec_SafeNormalize(&d)) {
            targetFocus.x -= func_01ffcb0c(d.x, ex);
            targetFocus.z -= func_01ffcb0c(d.z, ex);
        }
    }
}

BOOL Camera::initModeDefault() {
    if (gCurSceneInfo->isOutdoor == 0) {
        if (prevMode == 2) {
            focusYawLocked = 0;
        }
        loadPose(sCameraPoseGrid[presetRow].v[presetCol], 0);
    } else {
        loadPose(0, 0);
    }
    setBlendPreset(0);
    s32 t = prevMode;
    if (t == 2 || t == 4 || t == 0x10 || t == 5 || t == 6 || t == 0x12 || (u32)(t - 0xb) <= 1) {
        Camera_StartBlend();
        closeUpFactorTarget = 0;
    } else {
        closeUpFactorTarget = 0;
        closeUpFactor = 0;
        Camera_FinishBlend();
    }
    if (prevMode == 2 || prevMode == 0x10) {
        Camera_PlaySe((Camera *)this, 0x30);
    }
    return TRUE;
}

void Camera::updateModeDefault() {
    volatile VecFx32 cur;
    cur.x = targetFocus.x;
    cur.y = targetFocus.y;
    cur.z = targetFocus.z;
    volatile VecFx32 d;
    d.x = gVec3Zero.x;
    d.y = gVec3Zero.y;
    d.z = gVec3Zero.z;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p) {
        d.x = p->x;
        d.y = p->y;
        d.z = p->z;
    }
    if (gCurSceneInfo->isOutdoor == 0) {
        if (Scene_InHouseRoom() || Scene_InVillagerHouse() || (Scene_InMuseumRoom() && Scene_GetCurrent() != 0x20 && Scene_GetCurrent() != 0x22)) {
            loadPose(sCameraPoseGrid[presetRow].v[presetCol], 0);
            targetFocus.x = d.x;
            targetFocus.y = d.y;
            targetFocus.z = d.z;
            if (presetRow != 0) {
                clampToRoomBounds((s32 *)&targetFocus.x);
            }
        } else {
            targetFocus.x = d.x;
            targetFocus.y = d.y;
            targetFocus.z = d.z;
            clampToRoomBounds((s32 *)&targetFocus.x);
        }
    } else {
        dragFocusTo((VecFx32 *)&d);
    }
    VecFx32 v;
    R096_TAIL(v)
}

void Camera::pushView() {
    viewPushed = 1;
    saved = target.h0;
    savedPitch = target.h1;
    savedDistance = target.w0;
    savedOffset = target.x;
    savedOffsetY = target.y;
    savedOffsetZ = target.z;
    savedFocus = targetFocus.x;
    savedFocusY = targetFocus.y;
    savedFocusZ = targetFocus.z;
    savedEye = eye;
    savedEyeY = eyeY;
    savedEyeZ = eyeZ;
    initMode1();
}

void Camera::popView() {
    viewPushed = 0;
    initMode1();
    target.h0 = saved;
    target.h1 = savedPitch;
    target.w0 = savedDistance;
    target.x = savedOffset;
    target.y = savedOffsetY;
    target.z = savedOffsetZ;
    targetFocus.x = savedFocus;
    targetFocus.y = savedFocusY;
    targetFocus.z = savedFocusZ;
    eye = savedEye;
    eyeY = savedEyeY;
    eyeZ = savedEyeZ;
    restoreFocus = targetFocus.x;
    restoreFocusY = targetFocus.y;
    restoreFocusZ = targetFocus.z;
    restoreEye = eye;
    restoreEyeY = eyeY;
    restoreEyeZ = eyeZ;
    Camera_StartBlend();
    setBlendPreset(2);
}

BOOL Camera::initMode1() {
    VecFx32 v;
    if (viewPushed == 0) {
        Camera_GetLookAtPoint(&v, this);
        restoreFocus = v.x;
        restoreFocusY = v.y;
        restoreFocusZ = v.z;
        VecFx32 *p = getEye();
        restoreEye = p->x;
        restoreEyeY = p->y;
        restoreEyeZ = p->z;
        Camera_FinishBlend();
    } else {
        if (gCurSceneInfo->isOutdoor == 0) {
            loadPose(0xf, 0);
        } else {
            loadPose(0xe, 0);
        }
        setBlendPreset(1);
        Camera_StartBlend();
    }
    return TRUE;
}

void Camera::updateMode1() {
    volatile VecFx32 d;
    VecFx32 v, e, r, o, v2;
    d.x = gVec3Zero.x;
    d.y = gVec3Zero.y;
    d.z = gVec3Zero.z;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p) {
        d.x = p->x;
        d.y = p->y;
        d.z = p->z;
    }
    if (viewPushed == 0) {
        updateBlend();
        Camera_GetLookAtPoint(&v, this);
        VecFx32 *pp = getEye();
        e.x = pp->x;
        e.y = pp->y;
        e.z = pp->z;
        if (Camera_IsBlending()) {
            s32 z = getDistance();
            r.x = 0;
            r.y = 0;
            r.z = z;
            Vec_RotateX(&r, (s16)-getPitch());
            Vec_RotateY(&r, getYaw());
            Vec_Add(&o, &v, &r);
            e.x = o.x;
            e.y = o.y;
            e.z = o.z;
        }
        v.y = v.y + (0x1000 - MenuCtrl_GetTransitionProgress()) * 15;
        e.y = e.y + (0x1000 - MenuCtrl_GetTransitionProgress()) * 2;
        if (prevMode == 9) {
            v.y = v.y + Camera_UpdateSway(this);
        }
        setLookAt(&v, &e);
    } else {
        targetFocus.x = d.x;
        targetFocus.y = d.y;
        targetFocus.z = d.z;
        R096_TAIL(v2)
    }
}

BOOL Camera::initModeFocus() {
    if (gCurSceneInfo->isOutdoor == 0) {
        loadPose(0xb, 0);
        roomFocusSide = 3;
        Camera_UpdateRoomFocus(this);
    } else {
        loadPose(0xa, 0);
        FieldCamera_UpdateFocusZoom(this);
    }
    setBlendPreset(0);
    if (prevMode == 1) {
        Camera_FinishBlend();
    } else {
        Camera_StartBlend();
    }
    Camera_PlaySe((Camera *)this, 0x2f);
    return TRUE;
}

void Camera::updateModeFocus() {
    if (gCurSceneInfo->isOutdoor == 0) {
        Camera_UpdateRoomFocus(this);
    } else {
        FieldCamera_UpdateFocusZoom(this);
    }
    VecFx32 v;
    R096_TAIL(v)
}

BOOL Camera::initMode3() {
    if (gCurSceneInfo->isOutdoor == 0) {
        loadPose(0x1c, 0);
    } else {
        loadPose(0x1b, 0);
    }
    setBlendPreset(3);
    Camera_StartBlend();
    return TRUE;
}

void Camera::updateMode3() {
    volatile VecFx32 d;
    d.x = gVec3Zero.x;
    d.y = gVec3Zero.y;
    d.z = gVec3Zero.z;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p) {
        d.x = p->x;
        d.y = p->y;
        d.z = p->z;
    }
    targetFocus.x = d.x;
    targetFocus.y = d.y;
    targetFocus.z = d.z;
    VecFx32 v;
    R096_TAIL(v)
}

BOOL Camera::initMode4() {
    if (gCurSceneInfo->isOutdoor == 0) {
        loadPose(0xd, 0);
    } else {
        loadPose(0xc, 0);
    }
    setBlendPreset(0);
    Camera_StartBlend();
    closeUpFactorTarget = 0x1000;
    return TRUE;
}

void Camera::updateMode4() {
    volatile VecFx32 d;
    d.x = gVec3Zero.x;
    d.y = gVec3Zero.y;
    d.z = gVec3Zero.z;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p) {
        d.x = p->x;
        d.y = p->y;
        d.z = p->z;
    }
    targetFocus.x = d.x;
    targetFocus.y = d.y;
    targetFocus.z = d.z;
    VecFx32 v;
    R096_TAIL(v)
}

BOOL Camera::initModeTrackPair() {
    loadPose(0, 0);
    setBlendPreset(0);
    Camera_StartBlend();
    return TRUE;
}

void Camera::updateModeTrackPair() {
    VecFx32 d;
    d = gVec3Zero;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 *q = (VecFx32 *)Shared_PlayerActor_GetTrackTarget(4);
    if (p && q) {
        VecFx32 t;
        Vec_Sub(&t, p, q);
        s32 len = Vec_MagXZ(&t);
        s32 ang = Math_AngleXZ(p, q);
        s32 sc = func_01ffcb0c(len, 0xb33);
        d = *p;
        s32 idx = ((u16)ang >> 4) * 2;
        d.x += func_01ffcb0c(sc, data_02135f44[idx]);
        d.z += func_01ffcb0c(sc, data_02135f44[idx + 1]);
    }
    dragFocusTo(&d);
    VecFx32 v;
    R096_TAIL(v)
}

BOOL Camera::initModeRestore() {
    Camera_RestoreView();
    Camera_FinishBlend();
    return TRUE;
}

void Camera::updateModeRestore() {
    VecFx32 v;
    Camera_RestoreView();
    R096_TAIL(v)
}

BOOL Camera::initModeShake() {
    CameraShakeParam *sub = (CameraShakeParam *)&modeParam;
    sub->ang = 0;
    sub->vel = 0x2000;
    Camera_FinishBlend();
    return TRUE;
}

extern "C" void Camera_UpdateModeShake(Camera *o) {
    VecFx32 v;
    VecFx32 cam;
    CameraShakeParam *r = (CameraShakeParam *)&o->modeParam;
    s32 sc;
    r->ang = r->ang + r->vel;
    Math_StepS16(&r->vel, 0x6000, 0x180);
    sc = func_01ffcb0c(data_02135f44[((u16)r->ang >> 4) * 2], o->modeParam);
    (o)->dragFocusTo((V3 *)(&o->savedFocus));
    Math_ApproachS32((s32 *)r, 0, 0x400, 0x80, 0x10);
    (o)->updateBlend();
    Camera_GetLookAtPoint(&cam, o);
    s32 p = (o)->getPitch();
    s32 q = (o)->getYaw();
    (o)->setLookAtOrbit((V3 *)(&cam), p, q, (o)->getDistance());
    v.x = 0;
    v.y = 0x1000;
    v.z = 0;
    MTX_MultVec33(&v, &o->invViewMtx, &v);
    Vec_Scale(&v, sc);
    VEC_Add(&o->lookEye, &v, &o->lookEye);
    VEC_Add(&o->lookTarget, &v, &o->lookTarget);
}

extern "C" BOOL Camera_InitMode19(Camera *o) {
    (o)->loadPose(0x1f, (CameraPose *)(0));
    (o)->setBlendPreset(5);
    Camera_StartBlend();
    return TRUE;
}

extern "C" void Camera_UpdateMode19(Camera *o) {
    VecFx32 v;
    (o)->updateBlend();
    Camera_GetLookAtPoint(&v, o);
    s32 p = (o)->getPitch();
    s32 q = (o)->getYaw();
    (o)->setLookAtOrbit((V3 *)(&v), p, q, (o)->getDistance());
}

extern "C" BOOL Camera_SetModeDefault(void) {
    s32 t = gCamera->mode;
    if (t == 9) {
        return FALSE;
    }
    if (t == 0) {
        return TRUE;
    }
    return (gCamera)->setMode(0);
}

extern "C" s32 Camera_SetMode1(void) {
    return (gCamera)->setMode(1);
}

extern "C" s32 Camera_CalcPointSpan(VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 *d) {
    s32 len;
    VecFx32 sub, v2, t1, t2;
    Vec_Sub(&sub, a, b);
    v2.x = sub.x;
    v2.y = sub.y;
    v2.z = sub.z;
    v2.z = func_01ffcb0c(*(volatile s32 *)&sub.z, sCameraSpanDepthScale);
    len = VEC_Mag(&v2);
    if (c != NULL) {
        Vec_Add(&t1, a, b);
        Vec_ShiftRightTo(&t2, &t1, 1);
        c->x = t2.x;
        c->y = t2.y;
        c->z = t2.z;
        if (d != NULL) {
            s32 t = sub.z >> 1;
            if (t < 0) {
                t = -t;
            }
            *d = t;
        }
    }
    return len;
}

extern "C" s32 Camera_CalcTriangleSpan(VecFx32 *a, VecFx32 *b, VecFx32 *c, VecFx32 *d, s32 *e) {
    VecFx32 lo, hi, diff, t1, t2;
    s32 r;
    lo.x = a->x;
    lo.y = a->y;
    lo.z = a->z;
    hi.x = a->x;
    hi.y = a->y;
    hi.z = a->z;
    if (lo.x > b->x) {
        lo.x = b->x;
    } else {
        hi.x = b->x;
    }
    if (lo.z > b->z) {
        lo.z = b->z;
    } else {
        hi.z = b->z;
    }
    if (lo.x > c->x) {
        lo.x = c->x;
    }
    if (lo.z > c->z) {
        lo.z = c->z;
    }
    if (hi.x < c->x) {
        hi.x = c->x;
    }
    if (hi.z < c->z) {
        hi.z = c->z;
    }
    Vec_Sub(&diff, &hi, &lo);
    s32 z = diff.z;
    r = diff.x;
    if (r <= z) {
        r = z;
    }
    if (d != NULL) {
        Vec_Add(&t1, &lo, &hi);
        Vec_ShiftRightTo(&t2, &t1, 1);
        d->x = t2.x;
        d->y = t2.y;
        d->z = t2.z;
        d->y = (a->y + b->y) >> 1;
        if (e != NULL) {
            *e = diff.z >> 1;
        }
    }
    return r;
}

extern "C" BOOL Camera_FocusOnPoint(VecFx32 *a) {
    if (gCamera->mode == 9) {
        return FALSE;
    }
    if (Scene_GetCurrent() == 0xc) {
        return FALSE;
    }
    s32 r = Camera_CalcPointSpan((VecFx32 *)PlayerActor_GetBodyPos(4), a, NULL, NULL);
    if (r >= 0xb000) {
        return Camera_SetModeDefault();
    }
    gCamera->focusIsPair = 0;
    gCamera->focusPointA = *a;
    return (gCamera)->setMode(2);
}

extern "C" void Camera_FocusOnPair(VecFx32 *a, VecFx32 *b) {
    s32 r = Camera_CalcTriangleSpan((VecFx32 *)PlayerActor_GetBodyPos(4), a, b, NULL, NULL);
    if (r >= 0xb000) {
        Camera_SetModeDefault();
    } else {
        gCamera->focusIsPair = 1;
        gCamera->focusPointA = *a;
        gCamera->focusPointB = *b;
        (gCamera)->setMode(2);
    }
}

extern "C" void Camera_StartShake(s32 a) {
    gCamera->modeParam = a;
    (gCamera)->setMode(0x11);
}

extern "C" void Camera_SetMode19(void) {
    (gCamera)->setMode(0x13);
}

extern "C" void Camera_SetMode3(void) {
    (gCamera)->setMode(3);
}

extern "C" s32 Camera_RestorePrevMode(void) {
    return (gCamera)->setMode(gCamera->prevMode);
}

extern "C" void Camera_SetMode4(void) {
    (gCamera)->setMode(4);
}

extern "C" void Camera_SetMode5(void) {
    (gCamera)->setMode(5);
}

extern "C" BOOL Camera_RetargetFocus(VecFx32 *v) {
    if (gCamera->mode == 0x13) {
        gCamera->blendTime = 0;
        gCamera->blendDelay = 0;
        gCamera->blendEnd = 0x15000;
        return TRUE;
    }
    VecFx32 *d = &gCamera->focusPointA;
    *d = *v;
    gCamera->blendTime = 0;
    gCamera->roomFocusSide = 3;
    return TRUE;
}

extern "C" BOOL Camera_IsBlockingFocusView(VecFx32 *v, s32 unused, s32 h) {
    Camera *o = gCamera;
    if (o != NULL) {
        s32 t = o->mode;
        if (t != 2 && t != 4) {
            if (t == 1 && o->prevMode == 2) {
            } else if (o->viewPushed == 0) {
                return FALSE;
            }
        }
        if (v->z - (h >> 1) > o->targetFocus.z - 0x2000) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" s32 Camera_GetCloseUpFactor(void) {
    return gCamera->closeUpFactor;
}

extern "C" BOOL Camera_IsBlending(void) {
    if (gCamera->blendTime <= (gCamera)->getBlendEnd()) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void Camera_FinishBlend(void) {
    gCamera->blendTime = (gCamera)->getBlendEnd();
}

extern "C" void Camera_StartBlend(void) {
    gCamera->blendTime = 0;
}

extern "C" u8 Camera_GetBlendFramesLeft(void) {
    return ((gCamera)->getBlendEnd() - gCamera->blendTime) >> 12;
}

extern "C" void Camera_SaveView(void) {
    sCameraSavedSetup = *(CameraSetup *)&gCamera->target;
    *(VecFx32 *)&sCameraSavedEye = *(VecFx32 *)&gCamera->eye;
}

extern "C" void Camera_RestoreView(void) {
    *(CameraSetup *)&gCamera->target = sCameraSavedSetup;
    *(VecFx32 *)&gCamera->eye = *(VecFx32 *)&sCameraSavedEye;
}

extern "C" BOOL Camera_IsViewPushed(void) {
    if (gCamera->viewPushed != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Camera_PushView(void) {
    (gCamera)->pushView();
    return TRUE;
}

extern "C" BOOL Camera_PopView(void) {
    (gCamera)->popView();
    return TRUE;
}

extern "C" void Camera_SetSwayPattern3(void) {
    Camera_SetSwayPattern(gCamera, 3);
}

extern "C" void Camera_LockFocusYaw(void) {
    gCamera->focusYawLocked = 1;
}

extern "C" void Camera_SnapToFocus(VecFx32 *a) {
    (gCamera)->setFocusPreset11((u8 *)(void *)((CameraSetup *)&gCamera->target), a);
    *(CameraSetup *)&gCamera->current = *(CameraSetup *)&gCamera->target;
    VecFx32 v;
    Camera_GetLookAtPoint(&v, gCamera);
    s32 p = (gCamera)->getPitch();
    s32 q = (gCamera)->getYaw();
    (gCamera)->setLookAtOrbit((V3 *)(&v), p, q, (gCamera)->getDistance());
}

extern "C" void Camera_MuteSe(void) {
    gCamera->seMuted = 1;
}

extern "C" void Camera_UnmuteSe(void) {
    gCamera->seMuted = 0;
}

extern "C" void Camera_PlaySe(Camera *o, s32 a) {
    if (o->seMuted == 0) {
        Snd_PlaySe(a);
    }
}

extern "C" MtxFx43 *Camera_GetViewMatrix(void) {
    if (gCamera != NULL) {
        return (MtxFx43 *)&(FxMtx43 &)*gCamera;
    }
    return NULL;
}

extern "C" BOOL Camera_SetPresetCell(s32 a, s32 b) {
    Camera *o = gCamera;
    if (o != NULL) {
        if (o->presetCol != b || o->presetRow != a) {
            Camera_StartBlend();
            gCamera->presetRow = a;
            gCamera->presetCol = b;
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

extern "C" BOOL Camera_ProjectToScreen(s32 *x, s32 *y, VecFx32 *p) {
    struct {
        VecFx32 v;
        MtxFx43 m;
    } l;
    if (gCamera != NULL) {
        MtxFx43 *src = Camera_GetViewMatrix();
        l.m = *src;
        data_021f47e0 = l.m;
        MTX_MultVec43(p, &data_021f47e0, &l.v);
        s32 t = FX_Div(0x60000, (gCamera)->getFovTan());
        t = FX_Div(-t, l.v.z);
        Vec_Scale(&l.v, t);
        *x = l.v.x >> 12;
        *y = -(l.v.y >> 12);
        return TRUE;
    }
    return FALSE;
}


extern "C" BOOL Camera_ProjectCurvedToScreen(s32 *x, s32 *y, VecFx32 *p) {
    VecFx32 v;
    WorldCurve_Apply(&v, p);
    return Camera_ProjectToScreen(x, y, &v);
}

DebugColor data_021c3060(31, 20, 20, 31);
DebugColor data_021c3074(20, 20, 31, 31);
DebugColor data_021c3064(31, 31, 20, 31);
DebugColor data_021c305c(20, 31, 20, 31);
DebugColor data_021c3058(20, 31, 31, 31);
DebugColor data_021c306c(20, 24, 24, 31);
FxVec3 gCameraEye;
FxVec3 gCameraLookAt;
CameraSetup sCameraSavedSetup;
FxVec3 sCameraSavedEye;
extern "C" {
BOOL Camera_InitMode10(Camera *c);
BOOL Camera_InitMode11(Camera *c);
BOOL Camera_InitMode12(Camera *c);
BOOL Camera_InitMode14(Camera *c);
BOOL Camera_InitMode15(Camera *c);
BOOL Camera_InitMode16(Camera *c);
BOOL Camera_InitMode18(Camera *c);
BOOL Camera_InitMode20(Camera *c);
void Camera_UpdateMode10(Camera *c);
void Camera_UpdateMode11(Camera *c);
void Camera_UpdateMode12(Camera *c);
void Camera_UpdateMode14(Camera *c);
void Camera_UpdateMode15(Camera *c);
void Camera_UpdateMode16(Camera *c);
void Camera_UpdateMode18(Camera *c);
void Camera_UpdateMode20(Camera *c);
BOOL CameraEventModes_InitMode13(Camera *c);
BOOL CameraEventModes_InitModeFollowTarget(Camera *c);
BOOL CameraEventModes_InitModeSway(Camera *c);
BOOL CameraEventModes_InitModeTownTour(Camera *c);
void CameraEventModes_UpdateMode13(Camera *c);
void CameraEventModes_UpdateModeFollowTarget(Camera *c);
void CameraEventModes_UpdateModeSway(Camera *c);
void CameraEventModes_UpdateModeTownTour(Camera *c);
}
static BOOL Camera_InitMode1Thunk(Camera *c) { return c->initMode1(); }
static BOOL Camera_InitMode3Thunk(Camera *c) { return c->initMode3(); }
static BOOL Camera_InitMode4Thunk(Camera *c) { return c->initMode4(); }
static BOOL Camera_InitModeDefaultThunk(Camera *c) { return c->initModeDefault(); }
static BOOL Camera_InitModeFocusThunk(Camera *c) { return c->initModeFocus(); }
static BOOL Camera_InitModeRestoreThunk(Camera *c) { return c->initModeRestore(); }
static BOOL Camera_InitModeShakeThunk(Camera *c) { return c->initModeShake(); }
static BOOL Camera_InitModeTrackPairThunk(Camera *c) { return c->initModeTrackPair(); }
static void Camera_UpdateMode1Thunk(Camera *c) { c->updateMode1(); }
static void Camera_UpdateMode3Thunk(Camera *c) { c->updateMode3(); }
static void Camera_UpdateMode4Thunk(Camera *c) { c->updateMode4(); }
static void Camera_UpdateModeDefaultThunk(Camera *c) { c->updateModeDefault(); }
static void Camera_UpdateModeFocusThunk(Camera *c) { c->updateModeFocus(); }
static void Camera_UpdateModeRestoreThunk(Camera *c) { c->updateModeRestore(); }
static void Camera_UpdateModeTrackPairThunk(Camera *c) { c->updateModeTrackPair(); }

CameraModeEntry sCameraModeTable[21] = {
    { Camera_InitModeDefaultThunk, Camera_UpdateModeDefaultThunk },
    { Camera_InitMode1Thunk, Camera_UpdateMode1Thunk },
    { Camera_InitModeFocusThunk, Camera_UpdateModeFocusThunk },
    { Camera_InitMode3Thunk, Camera_UpdateMode3Thunk },
    { Camera_InitMode4Thunk, Camera_UpdateMode4Thunk },
    { Camera_InitModeTrackPairThunk, Camera_UpdateModeTrackPairThunk },
    { Camera_InitModeRestoreThunk, Camera_UpdateModeRestoreThunk },
    { CameraEventModes_InitModeFollowTarget, CameraEventModes_UpdateModeFollowTarget },
    { CameraEventModes_InitModeTownTour, CameraEventModes_UpdateModeTownTour },
    { CameraEventModes_InitModeSway, CameraEventModes_UpdateModeSway },
    { Camera_InitMode10, Camera_UpdateMode10 },
    { Camera_InitMode11, Camera_UpdateMode11 },
    { Camera_InitMode12, Camera_UpdateMode12 },
    { CameraEventModes_InitMode13, CameraEventModes_UpdateMode13 },
    { Camera_InitMode14, Camera_UpdateMode14 },
    { Camera_InitMode15, Camera_UpdateMode15 },
    { Camera_InitMode16, Camera_UpdateMode16 },
    { Camera_InitModeShakeThunk, Camera_UpdateModeShake },
    { Camera_InitMode18, Camera_UpdateMode18 },
    { Camera_InitMode19, Camera_UpdateMode19 },
    { Camera_InitMode20, Camera_UpdateMode20 }
};
Camera *gCamera;
s32 gCameraDistance;

s32 sCameraFollowVillagerIdx = 0x8;
s32 sCameraSpanDepthScale = 0x1800;
ProcProfile sCameraProfile = { (void *(*)())Camera_Create, 0xb, 0x6 };

extern const u8 data_020c8ce4[4];
const u8 data_020c8ce4[4] = { 0, 0, 0, 0 };
const CameraPoseGridRow sCameraPoseGrid[3] = { { { 1, 2, 3 } }, { { 4, 5, 6 } }, { { 7, 8, 9 } } };
extern const CameraSwayPattern kCameraSwayPatterns[4];
const CameraSwayPattern kCameraSwayPatterns[4] = {
    { 0x0, 0x14, 0x0, 0x0, 0x0 },
    { 0xa, 0x1, 0x2000, 0x0, 0x28 },
    { 0xa, 0x1, 0x2000, 0x0, 0x64 },
    { 0xa, 0x1, 0x2000, 0x0, 0x96 }
};
const u32 sCameraBlendTable[6][4] = {
    { 0x0, 0x1e000, 0x5000, 0x5000 },
    { 0x0, 0xa000, 0x3000, 0x3000 },
    { 0x0, 0x4000, 0x1000, 0x1000 },
    { 0x0, 0x5a000, 0x50000, 0xa000 },
    { 0x0, 0xb4000, 0xf000, 0xf000 },
    { 0x0, 0x3c000, 0xa000, 0xa000 }
};
const CameraPose sCameraPoseTable[33] = {
    { 0x0, 0x27f6, 0x10e14, 0x0, 0x1e14, 0xf0a },
    { -0xe02, 0x13fb, 0xb000, 0x0, 0x1e14, 0xf0a },
    { 0x0, 0x13fb, 0xb000, 0x0, 0x1e14, 0xf0a },
    { 0xe02, 0x13fb, 0xb000, 0x0, 0x1e14, 0xf0a },
    { -0xe02, 0x21fd, 0x10e14, 0x0, 0x1e14, 0xf0a },
    { 0x0, 0x21fd, 0x10e14, 0x0, 0x1e14, 0xf0a },
    { 0xe02, 0x21fd, 0x10e14, 0x0, 0x1e14, 0xf0a },
    { -0xe02, 0x3000, 0x19000, 0x0, 0x1e14, 0xf0a },
    { 0x0, 0x3000, 0x19000, 0x0, 0x1e14, 0xf0a },
    { 0xe02, 0x3000, 0x19000, 0x0, 0x1e14, 0xf0a },
    { 0x0, 0x20ec, 0xb000, 0x0, 0x4f6, 0xf0a },
    { 0x0, 0x13fb, 0xb000, 0x0, 0x4f6, 0xf0a },
    { 0x0, 0x1eee, 0xb000, 0x0, 0xf0a, 0xf0a },
    { 0x0, 0x13fb, 0xb000, 0x0, 0xf0a, 0xf0a },
    { 0x0, 0x1eee, 0xa000, 0x0, 0x18f6, 0xf0a },
    { 0x0, 0x13fb, 0xb000, 0x0, 0x1e14, 0xf0a },
    { 0xd03, 0x8f5, 0x1e14, 0x11614, 0x1e14, 0x1c9ec },
    { 0x0, 0x21a2, 0x12c00, 0x10000, 0x1e14, 0x17e14 },
    { 0x0, 0xdf0, 0xf000, 0x10000, 0x4000, 0x1c000 },
    { 0x0, 0xdf0, 0xf000, 0x8000, 0x4000, 0x1c000 },
    { 0x0, 0xdf0, 0xf000, 0x8000, 0x4000, 0x14000 },
    { 0x0, 0xdf0, 0xf000, 0x8000, 0x4000, 0x14000 },
    { 0x0, 0x17f6, 0xa000, 0x10000, 0x4000, 0x1ee14 },
    { 0x0, 0x17f6, 0xa000, 0x8000, 0x4000, 0x1ee14 },
    { 0x0, 0x17f6, 0xa000, 0x8000, 0x4000, 0x16e14 },
    { 0x0, 0x17f6, 0xa000, 0x8000, 0x4000, 0x16e14 },
    { 0x0, 0x27f6, 0x10e14, 0x0, 0x1e14, 0x2cf6 },
    { 0x0, 0x1eee, 0x8000, 0x0, 0xf0a, -0x10f6 },
    { 0x0, 0x13fb, 0x8000, 0x0, 0xf0a, -0x10f6 },
    { 0x0, 0x9f4, 0xa000, 0x0, 0x1e14, 0xf0a },
    { -0x19ab, 0x9f4, 0xa000, -0x230a, 0x4f6, 0xf0a },
    { 0x0, 0x21fd, 0x10e14, 0x0, 0x1e14, 0x40f6 },
    { 0x0, 0xe02, 0x8819, 0x0, 0x1400, 0xf0a }
};

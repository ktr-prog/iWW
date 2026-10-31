#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "field/Unk_ov003_02217b78_Ent.h"
#include "field/FieldGroundBackdrop.h"
#include "gfx/Model.h"
#include "gfx/DebugColor.h"
#include "gfx/BgModelCache.h"
#include "gfx/Camera.h"
#include "proto/main/unk_02036c58.h"
#include "proto/ov003/unk_ov003_02217b10.h"



struct NNSG3dResMdl;








extern "C" {
extern void *gCamera;
extern s32 data_020c8cb4;
extern u8 data_021f47e0[];
extern VecFx32 gCameraLookAt;

void Mtx43_SetTranslate(void *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(void *m, s32 a);
void *BgModelCache_getAcre(void *self, s32 i);
}

extern "C" {
DebugColor data_ov003_02235478(31, 20, 20, 31);
DebugColor data_ov003_0223547c(20, 20, 31, 31);
DebugColor data_ov003_02235488(31, 31, 20, 31);
DebugColor data_ov003_02235484(20, 31, 20, 31);
DebugColor data_ov003_02235480(20, 31, 31, 31);
DebugColor data_ov003_0223548c(20, 24, 24, 31);
}


FieldGroundBackdrop::FieldGroundBackdrop() {
    clear();
}

FieldGroundBackdrop::~FieldGroundBackdrop() {
}

void FieldGroundBackdrop::clear() {
    modelRes = 0;
}

BOOL FieldGroundBackdrop::init() {
    Unk_ov003_02217b78_Ent *e = (Unk_ov003_02217b78_Ent *)BgModelCache_Get()->getAcre(0x83);
    void *t = BgModelCache_Get()->getGroundTex();
    modelRes = e->modelRes;
    ((Model *)&model)->setResourceAndBind(modelRes, (NNSG3dResTex *)t);
    followCamera();
    return TRUE;
}

BOOL FieldGroundBackdrop::followCamera() {
    VecFx32CtorDtor v;
    void *cam = gCamera;
    if (cam != 0) {
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        Mtx43_SetTranslate(data_021f47e0, v.x - data_020c8cb4, 0, 0);
        Mtx43_RotateX(data_021f47e0, ((Camera *)(cam))->getEyeCurveAngle());
        ((Model *)&model)->mtx = *(Mtx43 *)data_021f47e0;
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02217b10) {
    HOST_OVERLAY_VAR(data_ov003_02235478),
    HOST_OVERLAY_VAR(data_ov003_0223547c),
    HOST_OVERLAY_VAR(data_ov003_02235488),
    HOST_OVERLAY_VAR(data_ov003_02235484),
    HOST_OVERLAY_VAR(data_ov003_02235480),
    HOST_OVERLAY_VAR(data_ov003_0223548c),
    HOST_OVERLAY_VARS_END
};

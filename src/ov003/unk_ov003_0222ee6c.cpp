#include "types.h"
#include "Unk_020d8c7c.h"
#include "sys/ProcProfile.h"
#include "gfx/DebugColor.h"
#include "gfx/Camera.h"
#include "proto/main/unk_020943dc.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/ov003/unk_ov003_0222ee6c.h"

class SnowballSpawner : public GameProc {
public:
    SnowballSpawner();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~SnowballSpawner();
};


extern "C" {
s32 Camera_CalcTriangleSpan(void *a, void *b, void *c, void *d, s32 *e);
s32 Camera_CalcPointSpan(void *a, void *b, void *c, s32 *d);
s32 FX_Div(s32 a, s32 b);
}


extern "C" {
ProcProfile sSnowballSpawnerProfile = {(void *(*)())SnowballSpawner_Create, 0xf, 0x11};
DebugColor data_ov003_0225b748(31, 20, 20, 31);
DebugColor data_ov003_0225b744(20, 20, 31, 31);
DebugColor data_ov003_0225b740(31, 31, 20, 31);
DebugColor data_ov003_0225b73c(20, 31, 20, 31);
DebugColor data_ov003_0225b738(20, 31, 31, 31);
DebugColor data_ov003_0225b74c(20, 24, 24, 31);
}


extern "C" void FieldCamera_UpdateFocusZoom(Camera *cam) {
    void *c = PlayerActor_GetBodyPos(4);
    s32 t;
    s32 v;
    if (cam->focusIsPair != 0) {
        v = Camera_CalcTriangleSpan(c, &cam->focusPointA, &cam->focusPointB, &cam->targetFocus, &t);
    } else {
        v = Camera_CalcPointSpan(c, &cam->focusPointA, &cam->targetFocus, &t);
    }
    cam->targetFocus.z = cam->targetFocus.z + t;
    if (v < 0x4800) {
        v = 0x4800;
    } else if (v > 0xb000) {
        v = 0xb000;
    }
    u32 q = FX_Div(v - 0x4800, 0x6800);
    cam->closeUpFactorTarget = 0x1000 - q;
    ((Camera *)(cam))->lerpPoses(0xa, 0, q);
}

extern "C" SnowballSpawner *SnowballSpawner_Create() {
    return new SnowballSpawner;
}

SnowballSpawner::SnowballSpawner() {}

SnowballSpawner::~SnowballSpawner() {}

BOOL SnowballSpawner::onCreate() {
    SnowballSpawner_SpawnSnowmen(this);
    SnowballSpawner_SpawnLooseBalls(this);
    return TRUE;
}

BOOL SnowballSpawner::onExecute() { return TRUE; }
BOOL SnowballSpawner::onDraw() { return TRUE; }
BOOL SnowballSpawner::onDelete() { return TRUE; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_0222ee6c) {
    HOST_OVERLAY_VAR(sSnowballSpawnerProfile),
    HOST_OVERLAY_VAR(data_ov003_0225b748),
    HOST_OVERLAY_VAR(data_ov003_0225b744),
    HOST_OVERLAY_VAR(data_ov003_0225b740),
    HOST_OVERLAY_VAR(data_ov003_0225b73c),
    HOST_OVERLAY_VAR(data_ov003_0225b738),
    HOST_OVERLAY_VAR(data_ov003_0225b74c),
    HOST_OVERLAY_VARS_END
};

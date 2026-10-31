#include "types.h"
#include "actor/CharacterListNode.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "room/RoomObjTexAuto.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov068/unk_ov068_0226d8a0.h"

struct RoostCafeSetResMdl {
    /* 0x00 */ u8 pad[0x18];
    /* 0x18 */ u8 numMat;
};

extern "C" {
void NNS_G3dMdlSetMdlAlpha(u8 *res, u32 i, u32 v);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
}

class RoostCafeSet : public RoomObjActor {
public:
    RoostCafeSet();
    virtual ~RoostCafeSet();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL changeSyncState(u32 v);

    void execShown();
    BOOL enterShown();
    void execHidden();
    BOOL enterHidden();
    void updateFadeState();

    /* 0x290 */ s32 alpha;
    /* 0x294 */ s32 targetAlpha;
    /* 0x298 */ u8 chrLoaded;
    /* 0x299 */ u8 pad_299[3];
    /* 0x29c */ AnimModel chrModel;
    /* 0x354 */ RoomObjRes chrRes;
    /* 0x3f8 */ RoomObjTexAuto chrTex;
};

extern "C" DebugColor data_ov068_02271268(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov068_02271264(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov068_02271254(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_0227126c(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_02271258(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov068_0227125c(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sRoostCafeSetProfile = {(void *(*)())RoostCafeSet_Create, 0x10, 0x12, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" {
RoostCafeSet *sRoostCafeSet;
}

extern "C" RoostCafeSet *RoostCafeSet_Create() {
    return new RoostCafeSet();
}

RoostCafeSet::RoostCafeSet() {
    sRoostCafeSet = NULL;
}

RoostCafeSet::~RoostCafeSet() {}

BOOL RoostCafeSet::onCreate() {
    sRoostCafeSet = this;
    setSyncSlot(1);
    loadResourcesByName("obj_ms_cafe");
    alpha = targetAlpha = 1;
    RoomObj_LoadResourcesByName("obj_cf_chr", &chrModel, &chrRes, &chrTex);
    changeSyncState(1);
    chrLoaded = 1;
    return TRUE;
}

BOOL RoostCafeSet::onExecute() {
    updateFadeState();
    if (alpha != targetAlpha) {
        Math_StepS32(&alpha, targetAlpha, 2);
    }
    u32 n = ((RoostCafeSetResMdl *)model.resMdl)->numMat;
    for (u32 i = 0; i < n; i++) {
        NNS_G3dMdlSetMdlAlpha((u8 *)model.resMdl, i, (u8)alpha);
    }
    return TRUE;
}

BOOL RoostCafeSet::onDraw() {
    model.drawAnimated(0);
    if (chrLoaded != 0) {
        chrModel.drawAnimated(0);
    }
    return TRUE;
}

BOOL RoostCafeSet::onDelete() {
    releaseResources();
    if (chrLoaded != 0) {
        RoomObj_ReleaseResources(&chrRes, &chrTex);
    }
    sRoostCafeSet = NULL;
    return TRUE;
}

BOOL RoostCafeSet::changeSyncState(u32 v) {
    static BOOL (RoostCafeSet::*tbl[2])() = {
        &RoostCafeSet::enterHidden,
        &RoostCafeSet::enterShown,
    };
    if (v < 2) {
        if ((this->*tbl[v])()) {
            if (storeSyncState(v)) {
                tex.syncState = v;
                return TRUE;
            }
        }
    }
    return FALSE;
}

void RoostCafeSet::updateFadeState() {
    static void (RoostCafeSet::*tbl[2])() = {
        &RoostCafeSet::execHidden,
        &RoostCafeSet::execShown,
    };
    if (tex.syncState < 2) {
        (this->*tbl[tex.syncState])();
    }
}

BOOL RoostCafeSet::enterHidden() {
    targetAlpha = 1;
    return TRUE;
}

void RoostCafeSet::execHidden() {
    targetAlpha = 1;
}

BOOL RoostCafeSet::enterShown() {
    targetAlpha = 0x1f;
    return TRUE;
}

void RoostCafeSet::execShown() {
    targetAlpha = 0x1f;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0226d8a0) {
    HOST_OVERLAY_VAR(data_ov068_02271268),
    HOST_OVERLAY_VAR(data_ov068_02271264),
    HOST_OVERLAY_VAR(data_ov068_02271254),
    HOST_OVERLAY_VAR(data_ov068_0227126c),
    HOST_OVERLAY_VAR(data_ov068_02271258),
    HOST_OVERLAY_VAR(data_ov068_0227125c),
    HOST_OVERLAY_VAR(sRoostCafeSetProfile),
    HOST_OVERLAY_VAR(sRoostCafeSet),
    HOST_OVERLAY_VARS_END
};

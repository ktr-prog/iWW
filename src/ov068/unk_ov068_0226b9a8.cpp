#include "gfx/Model.h"
#include "host_shared_calls.h"
#include "types.h"
#include "actor/CharacterListNode.h"
#include "actor/ActorProfile.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/NNSG3dRS.h"
#include "room/RoomObjRes.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "gfx/ModelAnim.h"
#include "room/RoomObjActor.h"
#include "room/RoomObjTexAuto.h"
#include "gfx/G3dResAccess.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov051/unk_ov051_02258de0.h"
#include "proto/ov068/unk_ov068_0226b9a8.h"
struct Unk_ov068_022702b4_Bits {
    u32 lo : 12;
    u32 mid : 16;
    u32 hi : 4;
};



extern "C" void NNS_G3dMdlSetMdlAlpha(u8 *res, u32 i, u32 v);

class TaxiInterior : public RoomObjActor {
public:
    TaxiInterior();
    virtual ~TaxiInterior();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    void execDry();
    BOOL enterDry();
    void execRainFading();
    BOOL enterRainFading();
    void execRaining();
    BOOL enterRaining();
    void updateRainState();
    BOOL setRainState(s32 s);
    void playBodyAnim(s32 a);
    void loadModels();

    /* 0x290 */ ModelAnim bodyMatAnim;
    /* 0x2b0 */ ModelAnim bodyTexAnim;
    /* 0x2d0 */ AnimModel driverModel;
    /* 0x388 */ RoomObjRes driverRes;
    /* 0x42c */ RoomObjTexAuto driverTex;
    /* 0x430 */ u8 isDriverAnimating;
    /* 0x431 */ u8 pad_431[3];
    /* 0x434 */ AnimModel wheelModel;
    /* 0x4ec */ RoomObjRes wheelRes;
    /* 0x590 */ RoomObjTexAuto wheelTex;
    /* 0x594 */ s32 rainState;
    /* 0x598 */ u16 rainFadeFrame;
    /* 0x59a */ s16 rainAlpha;
    /* 0x59c */ s16 rainAMatIdx;
    /* 0x59e */ s16 rainBMatIdx;
    /* 0x5a0 */ s16 splashMatIdx;
    /* 0x5a2 */ u16 pad_5a2;
};

extern "C" ActorProfile sTaxiInteriorProfile = {(void *(*)())TaxiInterior_Create, 0x13, 0x17, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" {
TaxiInterior *sTaxiInterior;
}

extern "C" TaxiInterior *TaxiInterior_Create() {
    return new TaxiInterior;
}

extern "C" void TaxiInterior_ModelCallback(NNSG3dRS *p) {
    TaxiInterior *o = (TaxiInterior *)p->pRenderObj->ptrUser;
    if (o) {
        TaxiInterior_OnModelNode(o, p->c[1], p);
    }
}

extern "C" void TaxiInterior_InitModelCallback(NNSG3dRS *p) {
    p->cbVecFunc[4] = (void *)TaxiInterior_ModelCallback;
    p->cbVecTiming[4] = 2;
}

TaxiInterior::TaxiInterior() {}

TaxiInterior::~TaxiInterior() {}

BOOL TaxiInterior::onCreate() {
    sTaxiInterior = this;
    loadModels();
    model.setInitCallback(TaxiInterior_InitModelCallback, this);
    rainAMatIdx = ((G3dResAccess *)model.resMdl)->findMatIdx("m_rainA");
    rainBMatIdx = ((G3dResAccess *)model.resMdl)->findMatIdx("m_rainB");
    splashMatIdx = ((G3dResAccess *)model.resMdl)->findMatIdx("m_splash");
    setRainState(0);
    Snd_PlaySeOnHandle(0x884);
    Snd_PlaySeOnHandle(0x885);
    return TRUE;
}

BOOL TaxiInterior::onExecute() {
    updateRainState();
    bodyTexAnim.step();
    ((G3dAnmObj *)bodyTexAnim.anmObj)->frame = bodyTexAnim.curFrame;
    model.stepAnim();
    bodyMatAnim.step();
    ((G3dAnmObj *)bodyMatAnim.anmObj)->frame = bodyMatAnim.curFrame;
    if (isDriverAnimating) {
        driverModel.stepAnim();
    }
    s32 t = Shared_SpNpcKappn_GetAnimState();
    SpNpcKappn_GetAnimFrame();
    s32 k = 0;
    switch (t) {
    case 0xfb:
        k = 0;
        break;
    case 0x8d:
        k = 1;
        break;
    case 0x8e:
        k = 2;
        break;
    case 0x8f:
        k = 3;
        break;
    case 0x90:
        k = 4;
        break;
    case 0x91:
        k = 5;
        break;
    }
    TaxiInterior_SetPartAnim(this, k, &wheelModel, &wheelRes, 0, 0x1000, 0, 0);
    wheelModel.stepAnim();
    NNS_G3dMdlSetMdlAlpha((u8 *)model.resMdl, rainAMatIdx, (u8)rainAlpha);
    NNS_G3dMdlSetMdlAlpha((u8 *)model.resMdl, rainBMatIdx, (u8)rainAlpha);
    NNS_G3dMdlSetMdlAlpha((u8 *)model.resMdl, splashMatIdx, (u8)rainAlpha);
    return TRUE;
}

BOOL TaxiInterior::onDraw() {
    model.drawAnimated(NULL);
    driverModel.drawAnimated(NULL);
    wheelModel.drawAnimated(NULL);
    return TRUE;
}

BOOL TaxiInterior::onDelete() {
    sTaxiInterior = NULL;
    releaseResources();
    RoomObj_ReleaseResources(&driverRes, &driverTex);
    RoomObj_ReleaseResources(&wheelRes, &wheelTex);
    Snd_StopSe(0x884, 1);
    Snd_StopSe(0x885, 1);
    return TRUE;
}

void TaxiInterior::loadModels() {
    loadResourcesByName("obj_taxi");
    if (RoomObjRes_GetBca(&res, 0)) {
        if (model.allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)&model)->initAnim(RoomObjRes_GetBca(&res, 0), 0, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    if (RoomObjRes_GetBta(&res, 0)) {
        if (bodyTexAnim.allocMatAnm(model.resMdl, gBgHeap)) {
            bodyTexAnim.init(RoomObjRes_GetBta(&res, 0), 0, 0x1000, 0);
            bodyTexAnim.addToRenderObj(model.getRenderObj());
        }
    }
    if (RoomObjRes_GetBma(&res, 0)) {
        if (bodyMatAnim.allocMatAnm(model.resMdl, gBgHeap)) {
            bodyMatAnim.init(RoomObjRes_GetBma(&res, 0), 0, 0x1000, 0);
            bodyMatAnim.addToRenderObj(model.getRenderObj());
        }
    }
    RoomObj_LoadResourcesByName("obj_taxi_fig", &driverModel, &driverRes, &driverTex);
    if (RoomObjRes_GetBca(&driverRes, 0)) {
        if (driverModel.allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)&driverModel)->initAnim(RoomObjRes_GetBca(&driverRes, 0), 1, 0x1000, 0, 0);
            driverModel.attachAnim();
        }
    }
    RoomObj_LoadResourcesByName("obj_taxi_hdl", &wheelModel, &wheelRes, &wheelTex);
    if (RoomObjRes_GetBca(&wheelRes, 0)) {
        if (wheelModel.allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)&wheelModel)->initAnim(RoomObjRes_GetBca(&wheelRes, 0), 0, 0x1000, 0, 0);
            wheelModel.attachAnim();
        }
    }
}

void TaxiInterior::playBodyAnim(s32 a) {
    void *p = RoomObjRes_GetBca(&res, 0);
    ((BlendAnimModel *)&model)->initAnim(p, a, 0x1000, ((Unk_ov068_022702b4_Bits *)&model.curFrame)->mid, 0);
    void *r6 = model.getRenderObj();
    void *q = RoomObjRes_GetBma(&res, 0);
    bodyMatAnim.replace(r6, q, a, 0x1000, ((Unk_ov068_022702b4_Bits *)&bodyMatAnim.curFrame)->mid);
}

BOOL TaxiInterior::setRainState(s32 s) {
    static BOOL (TaxiInterior::*tbl[3])() = {
        &TaxiInterior::enterRaining,
        &TaxiInterior::enterRainFading,
        &TaxiInterior::enterDry,
    };
    if (s < 3) {
        if ((this->*tbl[s])()) {
            rainState = s;
            return TRUE;
        }
    }
    return FALSE;
}

void TaxiInterior::updateRainState() {
    static void (TaxiInterior::*tbl[3])() = {
        &TaxiInterior::execRaining,
        &TaxiInterior::execRainFading,
        &TaxiInterior::execDry,
    };
    s32 s = rainState;
    if (s < 3) {
        (this->*tbl[s])();
    }
}

BOOL TaxiInterior::enterRaining() {
    rainAlpha = 0x1f;
    playBodyAnim(0);
    return TRUE;
}

void TaxiInterior::execRaining() {
    if (model.hasPassedFrame(0)) {
        Snd_PlaySe(0x886);
    } else if (model.hasPassedFrame(0x1c)) {
        Snd_PlaySe(0x887);
    }
}

BOOL TaxiInterior::enterRainFading() {
    playBodyAnim(0);
    return TRUE;
}

void TaxiInterior::execRainFading() {
    if (model.hasPassedFrame(0)) {
        Snd_PlaySe(0x886);
    } else if (model.hasPassedFrame(0x1c)) {
        Snd_PlaySe(0x887);
    }
    if (rainFadeFrame % 3 == 0) {
        if (rainAlpha >= 0) {
            rainAlpha = rainAlpha - 1;
            if (rainAlpha == 0) {
                setRainState(2);
            }
        }
    }
    rainFadeFrame++;
}

BOOL TaxiInterior::enterDry() {
    rainAlpha = 0;
    playBodyAnim(1);
    return TRUE;
}

void TaxiInterior::execDry() {}

extern "C" BOOL TaxiInterior_StopRain() {
    TaxiInterior *g = sTaxiInterior;
    if (g) {
        return g->setRainState(1);
    }
    return TRUE;
}

extern "C" BOOL TaxiInterior_StartDriverAnim() {
    TaxiInterior *g = sTaxiInterior;
    if (g) {
        g->isDriverAnimating = 1;
        ((BlendAnimModel *)(&sTaxiInterior->driverModel))->initAnim(RoomObjRes_GetBca(&sTaxiInterior->driverRes, 0), 1, 0x1000, 0, 0);
        return TRUE;
    }
    return FALSE;
}

extern "C" void TaxiInterior_OnModelNode(TaxiInterior *self, u32 node, NNSG3dRS *rs) {
}

extern "C" void TaxiInterior_SetPartAnim(TaxiInterior *self, u8 k, AnimModel *part, RoomObjRes *res, u8 s0, u32 s1, u16 s2, u16 s3) {
    void *cur = ((BlendAnimModel *)part)->getAnmRes();
    if (cur != RoomObjRes_GetBca(res, k)) {
        ((BlendAnimModel *)part)->initAnim(RoomObjRes_GetBca(res, k), s0, s1, s2, s3);
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0226b9a8) {
    HOST_OVERLAY_VAR(sTaxiInteriorProfile),
    HOST_OVERLAY_VAR(sTaxiInterior),
    HOST_OVERLAY_VARS_END
};

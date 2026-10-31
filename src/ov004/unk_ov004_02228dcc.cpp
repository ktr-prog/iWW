#include "types.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/Mtx43.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "nnsys/g3d_rt.h"
#include "gfx/Model.h"
#include "gfx/ModelAnim.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/ov004/unk_ov004_02228dcc.h"
#include "proto/ov045/unk_02258de0.h"

class TarotProps : public RoomObjActor {
public:
    TarotProps();
    virtual ~TarotProps();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    void releasePart(s32 i);
    void loadPart(s32 i, void *a, void *b);
    void execAct03();
    BOOL enterAct03();
    void execAct02();
    BOOL enterAct02();
    void execAct01();
    BOOL enterAct01();
    void execAct00();
    BOOL enterAct00();
    void execAct();
    BOOL changeAct(s32 i);
    void drawAtKatrina();

    /* 0x290 */ AnimModel partModels[3];
    /* 0x4b8 */ RoomObjRes partRes[3];
    /* 0x6a4 */ RoomObjTexHandle partTex[3];
    /* 0x6b0 */ u8 partVisible[3];
    /* 0x6b3 */ u8 pad_6b3;
    /* 0x6b4 */ ModelAnim part1MatAnim;
    /* 0x6d4 */ u8 modelVisible;
    /* 0x6d5 */ u8 pad_6d5[3];
    /* 0x6d8 */ s32 act;
};

typedef void (TarotProps::*Unk_ov004_02229148_Fn)();
typedef BOOL (TarotProps::*Unk_ov004_022291d4_Fn)();

extern "C" {
extern Mtx43 data_021f47e0;
void *__cxa_vec_ctor(void *array, u32 count, u32 size, void *(*ctor)(void *), void *(*dtor)(void *, s32));
void *__cxa_vec_cleanup(void *array, u32 count, u32 size, void *(*dtor)(void *, s32));
void Mtx43_SetTranslate(void *m, s32 x, s32 y, s32 z);
Mtx43 *SpNpcKatrina_GetJointMtx();
s32 NNS_G3dBindMdlTex(void *, void *);
s32 NNS_G3dBindMdlPltt(void *, void *);
}

extern "C" ActorProfile sTarotPropsProfile = {(void *(*)())TarotProps_Create, 0x71, 0x1b, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" TarotProps *sTarotProps = 0;

extern "C" TarotProps *TarotProps_Create() {
    return new TarotProps();
}

TarotProps::TarotProps() {
    __cxa_vec_ctor(partTex, 3, sizeof(partTex[0]), (void *(*)(void *))RoomObjTex_Construct, (void *(*)(void *, s32))RoomObjTex_Destruct);
}

TarotProps::~TarotProps() {
    __cxa_vec_cleanup(partTex, 3, sizeof(partTex[0]), (void *(*)(void *, s32))RoomObjTex_Destruct);
}

BOOL TarotProps::onCreate() {
    sTarotProps = this;
    loadResources("/roomObj/obj_tarot1.arc", "/roomObj/obj_tarot1.nsbtx");
    loadPart(0, (void *)"/roomObj/obj_tarot2.arc", (void *)"/roomObj/obj_tarot2.nsbtx");
    loadPart(1, (void *)"/roomObj/obj_tarot3.arc", (void *)"/roomObj/obj_tarot3.nsbtx");
    loadPart(2, (void *)"/roomObj/obj_tarot4.arc", (void *)"/roomObj/obj_tarot4.nsbtx");
    if (RoomObjRes_GetBca(&partRes[2], 0)) {
        if (partModels[2].allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)&partModels[2])->initAnim(RoomObjRes_GetBca(&partRes[2], 0), 1, 0x1000, 0, 0);
            partModels[2].attachAnim();
            partModels[2].frameStep = 0;
        }
    }
    if (part1MatAnim.allocMatAnm(partModels[1].resMdl, gBgHeap)) {
        part1MatAnim.init(RoomObjRes_GetBta(&partRes[1], 0), 1, 0x1000, 0);
        part1MatAnim.addToRenderObj(partModels[1].getRenderObj());
        part1MatAnim.frameStep = 0;
    }
    changeAct(0);
    return TRUE;
}

BOOL TarotProps::onExecute() {
    partModels[2].stepAnim();
    part1MatAnim.step();
    ((G3dAnmObj *)part1MatAnim.anmObj)->frame = part1MatAnim.curFrame;
    Mtx43_SetTranslate(&data_021f47e0, position.x, position.y, position.z);
    partModels[1].mtx = data_021f47e0;
    partModels[2].mtx = data_021f47e0;
    execAct();
    return TRUE;
}

BOOL TarotProps::onDraw() {
    return TRUE;
}

void TarotProps::drawAtKatrina() {
    Mtx43 *m = SpNpcKatrina_GetJointMtx();
    u8 i;
    data_021f47e0 = *m;
    model.mtx = data_021f47e0;
    partModels[0].mtx = data_021f47e0;
    if (modelVisible) {
        model.drawAnimated(0);
    }
    for (i = 0; i < 3; i++) {
        if (partVisible[i]) {
            partModels[i].drawAnimated(0);
        }
    }
}

BOOL TarotProps::onDelete() {
    releaseResources();
    releasePart(0);
    releasePart(1);
    releasePart(2);
    sTarotProps = 0;
    return TRUE;
}

BOOL TarotProps::changeAct(s32 i) {
    static Unk_ov004_022291d4_Fn tbl[4] = {&TarotProps::enterAct00, &TarotProps::enterAct01,
                                           &TarotProps::enterAct02, &TarotProps::enterAct03};
    if (i < 4) {
        if ((this->*tbl[i])()) {
            act = i;
            return TRUE;
        }
    }
    return FALSE;
}

void TarotProps::execAct() {
    static Unk_ov004_02229148_Fn tbl[4] = {&TarotProps::execAct00, &TarotProps::execAct01,
                                           &TarotProps::execAct02, &TarotProps::execAct03};
    if (act < 4) {
        (this->*tbl[act])();
    }
}

BOOL TarotProps::enterAct00() {
    u8 i;
    modelVisible = 0;
    for (i = 0; i < 3; i++) {
        partVisible[i] = 0;
    }
    return TRUE;
}

void TarotProps::execAct00() {}

BOOL TarotProps::enterAct01() {
    modelVisible = 1;
    partVisible[0] = 0;
    partVisible[1] = 1;
    partVisible[2] = 0;
    ((BlendAnimModel *)&partModels[2])->initAnim(RoomObjRes_GetBca(&partRes[2], 0), 1, 0x1000, 0, 0);
    part1MatAnim.init(RoomObjRes_GetBta(&partRes[1], 0), 1, 0x1000, 0);
    return TRUE;
}

void TarotProps::execAct01() {
    if (SpNpcKatrina_GetAnimFrame() == 0xb) {
        modelVisible = 0;
        partVisible[2] = 1;
    }
}

BOOL TarotProps::enterAct02() {
    modelVisible = 0;
    partVisible[0] = 0;
    partVisible[1] = 1;
    partVisible[2] = 1;
    partModels[2].curFrame = (u32)((s32)partModels[2].numFrames >> 12) << 16 >> 4;
    partModels[2].frameStep = 0;
    part1MatAnim.curFrame = (u32)((s32)part1MatAnim.numFrames >> 12) << 16 >> 4;
    part1MatAnim.frameStep = 0;
    return TRUE;
}

void TarotProps::execAct02() {
    if (SpNpcKatrina_GetAnimFrame() == 9) {
        partVisible[0] = 1;
    }
}

BOOL TarotProps::enterAct03() {
    modelVisible = 0;
    partVisible[0] = 1;
    partVisible[1] = 1;
    partVisible[2] = 1;
    ((BlendAnimModel *)&partModels[2])->initAnim(RoomObjRes_GetBca(&partRes[2], 1), 1, 0x1000, 0, 0);
    part1MatAnim.init(RoomObjRes_GetBta(&partRes[1], 1), 1, 0x1000, 0);
    return TRUE;
}

void TarotProps::execAct03() {
    if (SpNpcKatrina_GetAnimFrame() == 7) {
        partVisible[0] = 0;
    }
    if (SpNpcKatrina_GetAnimFrame() == 0x12) {
        partVisible[2] = 0;
    }
    if (SpNpcKatrina_GetAnimFrame() == 0x13) {
        modelVisible = 1;
    }
    if (SpNpcKatrina_GetAnimFrame() == 0x25) {
        modelVisible = 0;
    }
    if (partModels[2].isFinished()) {
        changeAct(0);
    }
}

extern "C" BOOL TarotProps_StartAct01() {
    if (sTarotProps) {
        return sTarotProps->changeAct(1);
    }
    return FALSE;
}

extern "C" BOOL TarotProps_StartAct02() {
    if (sTarotProps) {
        return sTarotProps->changeAct(2);
    }
    return FALSE;
}

extern "C" BOOL TarotProps_StartAct03() {
    if (sTarotProps) {
        return sTarotProps->changeAct(3);
    }
    return FALSE;
}

extern "C" void TarotProps_Draw() {
    if (sTarotProps) {
        sTarotProps->drawAtKatrina();
    }
}

void TarotProps::loadPart(s32 i, void *a, void *b) {
    RoomObjRes *t1 = &partRes[i];
    RoomObjRes_Load(t1, (const char *)a);
    RoomObjTexHandle *t2 = &partTex[i];
    RoomObjTex_Load(t2, (const char *)b);
    partModels[i].setResource((NNSG3dResMdl *)RoomObjRes_GetModel(t1), 0);
    {
        void *x = RoomObjRes_GetModel(t1);
        NNS_G3dBindMdlTex(x, RoomObjTex_Get(t2));
    }
    {
        void *x = RoomObjRes_GetModel(t1);
        NNS_G3dBindMdlPltt(x, RoomObjTex_Get(t2));
    }
}

void TarotProps::releasePart(s32 i) {
    RoomObjRes_Free(&partRes[i]);
    RoomObjTex_Reset(&partTex[i]);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02228dcc) {
    HOST_OVERLAY_VAR(sTarotPropsProfile),
    HOST_OVERLAY_VAR(sTarotProps),
    HOST_OVERLAY_VARS_END
};

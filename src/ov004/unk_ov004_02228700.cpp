#include "gfx/MatTexVramTask.h"
#include "host_overlay_vars.h"
#include "gfx/ModelAnim.h"
#include "item/DateSeededRandomSource.h"
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
#include "gfx/TwoLayerAnimModel.h"
#include "item/ItemPickSpec.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov004/unk_ov004_02228700.h"

struct Unk_ov004_022288c0_Bits {
    u32 lo : 12;
    u32 mid : 16;
    u32 hi : 4;
};

extern "C" void ClothTex_Construct();
extern "C" void ClothTex_Destruct();
struct ClothTex {
    ClothTex() { ClothTex_Construct(); }
    ~ClothTex() { ClothTex_Destruct(); }
    u8 pad_00[0x2c4];
};

class SewingMachine : public RoomObjActor {
public:
    SewingMachine();
    virtual ~SewingMachine();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL changeSyncState(u32 idx);

    void updateState03();
    BOOL enterState03();
    void updateState02();
    BOOL enterState02();
    void updateState01();
    BOOL enterState01();
    void updateState00();
    BOOL enterState00();
    void updateState();

    /* 0x290 */ AnimModel partModel;
    /* 0x348 */ RoomObjRes partRes;
    /* 0x3ec */ RoomObjTexHandle partTex;
    /* 0x3f0 */ MatTexVramTask clothTexTask;
    /* 0x418 */ ModelAnim matAnim;
    /* 0x438 */ u32 pad_438;
    /* 0x43c */ s32 stopFrame;
};


extern "C" {
extern Mtx43 data_021f47e0;
void Mtx43_SetTranslate(void *m, s32 x, s32 y, s32 z);
s32 NNS_G3dBindMdlTex(void *, void *);
s32 NNS_G3dBindMdlPltt(void *, void *);
s32 Math_IsInRange(s32 a, s32 b, s32 c);
}

typedef void (SewingMachine::*Unk_ov004_022288c0_Fn)();
typedef BOOL (SewingMachine::*Unk_ov004_0222894c_Fn)();

extern "C" ActorProfile sSewingMachineProfile = {(void *(*)())SewingMachine_Create, 0x78, 0x15, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" SewingMachine *sSewingMachine = 0;
ClothTex sSewingMachineCloth;

extern "C" SewingMachine *SewingMachine_Create() {
    return new SewingMachine();
}

SewingMachine::SewingMachine() {
    RoomObjTex_Construct(&partTex);
}

SewingMachine::~SewingMachine() {
    RoomObjTex_Destruct(&partTex);
}

BOOL SewingMachine::onCreate() {
    sSewingMachine = this;
    loadResources("/roomObj/obj_tailor1.arc", "/roomObj/obj_tailor1.nsbtx");
    RoomObjRes_Load(&partRes, "/roomObj/obj_tailor2.arc");
    RoomObjTex_Load(&partTex, "/roomObj/obj_tailor2.nsbtx");
    partModel.setResource((NNSG3dResMdl *)RoomObjRes_GetModel(&partRes), 0);
    {
        void *a = RoomObjRes_GetModel(&partRes);
        NNS_G3dBindMdlTex(a, RoomObjTex_Get(&partTex));
    }
    {
        void *a = RoomObjRes_GetModel(&partRes);
        NNS_G3dBindMdlPltt(a, RoomObjTex_Get(&partTex));
    }
    if (RoomObjRes_GetBca(&res, 0) && model.allocAnmObj(gBgHeap)) {
        ((BlendAnimModel *)&model)->initAnim(RoomObjRes_GetBca(&res, 0), 0, 0x1000, 0, 0);
        model.attachAnim();
        model.frameStep = 0;
    }
    if (matAnim.allocMatAnm(model.resMdl, gBgHeap)) {
        matAnim.init(RoomObjRes_GetBta(&res, 0), 0, 0x1000, 0);
        matAnim.addToRenderObj(model.getRenderObj());
        matAnim.frameStep = 0;
    }
    if (RoomObjRes_GetBca(&partRes, 0) && partModel.allocAnmObj(gBgHeap)) {
        ((BlendAnimModel *)&partModel)->initAnim(RoomObjRes_GetBca(&partRes, 0), 0, 0x1000, 0, 0);
        partModel.attachAnim();
        partModel.frameStep = 0;
    }
    {
        DateSeededRandomSource rnd;
        u16 z;
        {
            ItemPickSpec spec;
            spec.set(2, 0);
            ItemPick_One(&z, &spec, 0, &rnd, 1, 1, 0);
        }
        ClothTex_LoadItem(&sSewingMachineCloth, &z, 0);
        NNSG3dResMdl *mdl = partModel.resMdl;
        void *t = ClothTex_GetTex(&sSewingMachineCloth);
        clothTexTask.request(mdl, "w", t, 0, 0);
        enterState00();
    }
    return TRUE;
}

BOOL SewingMachine::onExecute() {
    model.stepAnim();
    partModel.stepAnim();
    matAnim.step();
    ((G3dAnmObj *)matAnim.anmObj)->frame = matAnim.curFrame;
    Mtx43_SetTranslate(&data_021f47e0, position.x, position.y, position.z);
    model.mtx = data_021f47e0;
    partModel.mtx = data_021f47e0;
    updateState();
    return TRUE;
}

BOOL SewingMachine::onDraw() {
    model.drawAnimated(0);
    partModel.drawAnimated(0);
    return TRUE;
}

BOOL SewingMachine::onDelete() {
    releaseResources();
    RoomObjRes_Free(&partRes);
    RoomObjTex_Reset(&partTex);
    sSewingMachine = 0;
    return TRUE;
}

BOOL SewingMachine::changeSyncState(u32 idx) {
    static Unk_ov004_0222894c_Fn tbl[4] = {
        (Unk_ov004_0222894c_Fn)&SewingMachine::enterState00,
        (Unk_ov004_0222894c_Fn)&SewingMachine::enterState01,
        (Unk_ov004_0222894c_Fn)&SewingMachine::enterState02,
        (Unk_ov004_0222894c_Fn)&SewingMachine::enterState03,
    };
    if (idx < 4) {
        if ((this->*tbl[idx])()) {
            tex.syncState = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void SewingMachine::updateState() {
    static Unk_ov004_022288c0_Fn tbl[4] = {
        &SewingMachine::updateState00,
        &SewingMachine::updateState01,
        &SewingMachine::updateState02,
        &SewingMachine::updateState03,
    };
    u32 i = tex.syncState;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL SewingMachine::enterState00() {
    return TRUE;
}

void SewingMachine::updateState00() {}

BOOL SewingMachine::enterState01() {
    partModel.frameStep = 0x1000;
    stopFrame = 0;
    return TRUE;
}

void SewingMachine::updateState01() {
    model.frameStep = 0x1000;
    matAnim.frameStep = 0x1000;
    changeSyncState(2);
}

BOOL SewingMachine::enterState02() {
    return TRUE;
}

static inline u32 SewingMachine_PartFrame(SewingMachine *g) {
    return ((Unk_ov004_022288c0_Bits *)&g->partModel.curFrame)->mid;
}

void SewingMachine::updateState02() {
    s32 t = SewingMachine_PartFrame(this);
    u32 q = (u16)(t / 0x38);
    if (Math_IsInRange((u16)(t - q * 0x38), 0x11, 0x34)) {
        if (!MenuCtrl_IsMenuOpen()) {
            RoomObj_PlaySeHeld(&se, 0x85e);
        }
    }
}

BOOL SewingMachine::enterState03() {
    partModel.frameStep = 0;
    stopFrame = 0;
    return TRUE;
}

void SewingMachine::updateState03() {
    s32 r = 0x1000 - Math_EaseRampProgress(stopFrame, 0, 0x28000, 0xa000, 0xa000);
    model.frameStep = r;
    matAnim.frameStep = r;
    stopFrame += 0x1000;
    if (r == 0) {
        changeSyncState(0);
    }
}

extern "C" BOOL SewingMachine_Start() {
    SewingMachine *g = sSewingMachine;
    if (g) {
        return g->changeSyncState(1);
    }
    return 0;
}

extern "C" BOOL SewingMachine_Stop() {
    SewingMachine *g = sSewingMachine;
    if (g) {
        return g->changeSyncState(3);
    }
    return 0;
}

extern "C" BOOL SewingMachine_IsStopped() {
    SewingMachine *g = sSewingMachine;
    if (g) {
        u32 t = g->tex.syncState;
        if (t == 3 || t == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void SewingMachine_SetFrame(u32 x) {
    SewingMachine *g = sSewingMachine;
    if (g) {
        g->partModel.curFrame = x << 12;
    }
}

extern "C" u32 SewingMachine_GetFrame() {
    SewingMachine *g = sSewingMachine;
    if (g) {
        return SewingMachine_PartFrame(g);
    }
    return 0;
}

extern "C" void StaticInit_unk_ov004_02228700(void) {
    HOST_STATIC_CONSTRUCT(sSewingMachineCloth);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02228700) {
    HOST_OVERLAY_VAR(sSewingMachineProfile),
    HOST_OVERLAY_VAR(sSewingMachine),
    HOST_OVERLAY_VAR(sSewingMachineCloth),
    HOST_OVERLAY_VARS_END
};

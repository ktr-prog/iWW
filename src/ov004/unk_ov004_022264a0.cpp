#include "types.h"
#include "gfx/VecFx32.h"
#include "snd/BgmBeatPhase.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "room/RoomObjTexAuto.h"
#include "gfx/CachedModel.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "gfx/Model.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02090268.h"
#include "proto/ov004/unk_ov004_0221c01c.h"
#include "proto/ov004/unk_ov004_022264a0.h"


class CafeCoffeeSet : public RoomObjActor {
public:
    CafeCoffeeSet();
    virtual ~CafeCoffeeSet();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    /* 0x290 */ AnimModel partModels[9];
    /* 0x908 */ RoomObjRes partRes[9];
    /* 0xecc */ RoomObjTexAuto partTex[9];
    /* 0xef0 */ u8 partVisible[9];
    /* 0xef9 */ u8 modelVisible;
    /* 0xefa */ u8 pad_efa[2];
    /* 0xefc */ s32 serveState;
    /* 0xf00 */ u8 unk_f00[0x10];
    /* 0xf10 */ VecFx32 pourEffectPos;
    /* 0xf1c */ VecFx32 part4EffectPos;
    /* 0xf28 */ VecFx32 part6EffectPos;
    /* 0xf34 */ u16 part4EffectAngle;
    /* 0xf36 */ u16 part6EffectAngle;
    /* 0xf38 */ s32 pourEffect;
    /* 0xf3c */ s32 part4Effect;
    /* 0xf40 */ s32 part6Effect;
};

static inline u32 FrameInt(u32 v) {
    return (v >> 12) & 0xffff;
}

extern "C" {
extern Mtx43 data_021f47e0;
BOOL Math_IsInRange(s32 v, s32 a, s32 b);
BOOL NNS_G3dBindMdlTex(void *mdl, void *tex);
BOOL NNS_G3dBindMdlPltt(void *mdl, void *tex);
s32 Camera_RestorePrevMode(void);
s32 Camera_MuteSe(void);
s32 Camera_SetMode4(void);
void Mtx43_SetTranslate(Mtx43 *m, s32 a, s32 b, s32 c);

BOOL CafeCoffeeSet_ChangeState(CafeCoffeeSet *o, s32 n);
void CafeCoffeeSet_UpdateState(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateMatrices(CafeCoffeeSet *o);
void CafeCoffeeSet_LoadPart(CafeCoffeeSet *o, u32 idx, const char *id, const char *x);
void CafeCoffeeSet_ReleasePart(CafeCoffeeSet *o, u32 idx);
void CafeCoffeeSet_InitPartAnim(CafeCoffeeSet *o, u32 idx);
void CafeCoffeeSet_SwitchAnim(CafeCoffeeSet *self, u32 id, AnimModel *m, RoomObjRes *res, u8 a5, s32 a6, u32 a7, u32 a8);
BOOL CafeCoffeeSet_EnterState00(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState01(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState02(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState03(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState04(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState05(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState06(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState08(CafeCoffeeSet *o);
BOOL CafeCoffeeSet_EnterState09(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState00(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState01(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState02(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState03(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState04(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState05(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState06(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState08(CafeCoffeeSet *o);
void CafeCoffeeSet_UpdateState09(CafeCoffeeSet *o);
}

#define M0 (&o->partModels[0])
#define M1 (&o->partModels[1])
#define M2 (&o->partModels[2])
#define R0 (&o->partRes[0])
#define R1 (&o->partRes[1])
#define R2 (&o->partRes[2])
#define UP(id, m, r, a5, a7) CafeCoffeeSet_SwitchAnim(o, id, m, r, a5, 0x1000, a7, 0)

extern "C" CafeCoffeeSet *volatile sCafeCoffeeSet = 0;

extern "C" FxVec3 data_ov004_02250d2c(0, 0, 0);
extern "C" FxVec3 data_ov004_02250d44(0x17700, 0x1900, 0x15800);
extern "C" FxVec3 data_ov004_02250d5c(0x17800, 0x1a00, 0x13400);
extern "C" FxVec3 data_ov004_02250cd8(0x10c00, 0x1600, 0x1b000);
extern "C" FxVec3 data_ov004_02250cf0(0x16a00, 0x1900, 0x13000);
extern "C" FxVec3 data_ov004_02250d08(0x16600, 0x1900, 0x11e00);

extern "C" CafeCoffeeSet *CafeCoffeeSet_Create() {
    return new CafeCoffeeSet();
}

CafeCoffeeSet::CafeCoffeeSet() {
}

CafeCoffeeSet::~CafeCoffeeSet() {
}

BOOL CafeCoffeeSet::onCreate() {
    sCafeCoffeeSet = this;
    loadResources("/roomObj/obj_cafe1.arc", "/roomObj/obj_cafe1.nsbtx");
    CafeCoffeeSet_LoadPart(this, 0, "/roomObj/obj_cafe2.arc", "/roomObj/obj_cafe2.nsbtx");
    CafeCoffeeSet_LoadPart(this, 1, "/roomObj/obj_cafe3.arc", "/roomObj/obj_cafe3.nsbtx");
    CafeCoffeeSet_LoadPart(this, 2, "/roomObj/obj_cafe4.arc", "/roomObj/obj_cafe4.nsbtx");
    CafeCoffeeSet_LoadPart(this, 3, "/roomObj/obj_cafe5.arc", "/roomObj/obj_cafe5.nsbtx");
    CafeCoffeeSet_LoadPart(this, 4, "/roomObj/obj_cafe3.arc", "/roomObj/obj_cafe3.nsbtx");
    CafeCoffeeSet_LoadPart(this, 5, "/roomObj/obj_cafe4.arc", "/roomObj/obj_cafe4.nsbtx");
    CafeCoffeeSet_LoadPart(this, 6, "/roomObj/obj_cafe3.arc", "/roomObj/obj_cafe3.nsbtx");
    CafeCoffeeSet_LoadPart(this, 7, "/roomObj/obj_cafe4.arc", "/roomObj/obj_cafe4.nsbtx");
    CafeCoffeeSet_LoadPart(this, 8, "/roomObj/obj_cafe6.arc", "/roomObj/obj_cafe6.nsbtx");
    if (RoomObjRes_GetBca(&res, 0) != 0) {
        if (model.allocAnmObj(gBgHeap) != 0) {
            ((BlendAnimModel *)&model)->initAnim(RoomObjRes_GetBca(&res, 0), 1, 0x1000, 0, 0);
            model.attachAnim();
            model.frameStep = 0;
        }
    }
    u8 i = 0;
    do {
        CafeCoffeeSet_InitPartAnim(this, i);
        i++;
    } while (i < 9);
    CafeCoffeeSet_ChangeState(this, 0);
    partVisible[3] = 1;
    CafeCoffeeSet_SwitchAnim(this, 8, &partModels[4], &partRes[4], 0, 0x1000, 0, 0);
    CafeCoffeeSet_SwitchAnim(this, 6, &partModels[5], &partRes[5], 0, 0x1000, 0, 0);
    CafeCoffeeSet_SwitchAnim(this, 8, &partModels[6], &partRes[6], 0, 0x1000, 0, 0);
    CafeCoffeeSet_SwitchAnim(this, 6, &partModels[7], &partRes[7], 0, 0x1000, 0, 0);
    part4EffectPos = data_ov004_02250cd8;
    part6EffectPos = data_ov004_02250cf0;
    part4EffectAngle = 0;
    part6EffectAngle = 0;
    partModels[4].frameStep = 0;
    partModels[4].curFrame = (u16)(FrameInt(partModels[4].numFrames) - 1) << 12;
    partModels[5].frameStep = 0;
    partModels[5].curFrame = (u16)(FrameInt(partModels[5].numFrames) - 1) << 12;
    partModels[6].frameStep = 0;
    partModels[6].curFrame = (u16)(FrameInt(partModels[6].numFrames) - 1) << 12;
    partModels[7].frameStep = 0;
    partModels[7].curFrame = (u16)(FrameInt(partModels[7].numFrames) - 1) << 12;
    pourEffect = -1;
    part4Effect = -1;
    part6Effect = -1;
    return TRUE;
}

BOOL CafeCoffeeSet::onExecute() {
    u8 i;
    if (Math_IsInRange(Bgm_GetCurrent(), 0x63, 0xab)) {
        BgmBeatPhase *t = (BgmBeatPhase *)Snd_GetBeatState();
        if (t != NULL) {
            if (t->seqVar2 != 1) {
                model.curFrame = 0;
                model.frameStep = t->loopFrame32;
                model.stepAnim();
                model.frameStep = 0;
                partModels[0].curFrame = 0;
                partModels[0].frameStep = t->loopFrame32;
                partModels[0].stepAnim();
                partModels[0].frameStep = 0;
            }
        }
    }
    model.stepAnim();
    for (i = 0; i < 9; i++) {
        partModels[i].stepAnim();
    }
    CafeCoffeeSet_UpdateState(this);
    if (pourEffect != -1) {
        Effect_SetPosition(pourEffect, &pourEffectPos, 0, 0);
    }
    if (partVisible[4] != 0) {
        if (part4Effect == -1) {
            part4Effect = Effect_CreateById(0x6b, &part4EffectPos, (s16 *)&part4EffectAngle, 0);
        }
    }
    if (partVisible[6] != 0) {
        if (part6Effect == -1) {
            part6Effect = Effect_CreateById(0x6b, &part6EffectPos, (s16 *)&part6EffectAngle, 0);
        }
    }
    return TRUE;
}

BOOL CafeCoffeeSet::onDraw() {
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateMatrices(CafeCoffeeSet *o) {
    const FxVec3 &zero = data_ov004_02250d2c;
    u8 i;
    data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
    o->model.mtx = data_021f47e0;
    data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxE();
    o->partModels[0].mtx = data_021f47e0;
    s32 st = o->serveState;
    if ((u32)(st - 8) <= 1) {
        Mtx43_SetTranslate(&data_021f47e0, zero.x, zero.y, zero.z);
        o->partModels[1].mtx = data_021f47e0;
    } else if (st == 5) {
        if (FrameInt(o->partModels[1].curFrame) >= 0x10) {
            Mtx43_SetTranslate(&data_021f47e0, zero.x, zero.y, zero.z);
            o->pourEffectPos.x = 0x16a00;
            o->pourEffectPos.y = 0x1900;
            o->pourEffectPos.z = 0x15000;
        } else {
            data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
            o->pourEffectPos.x = data_021f47e0.m[9];
            o->pourEffectPos.y = data_021f47e0.m[10];
            o->pourEffectPos.z = data_021f47e0.m[11];
        }
    } else if (st == 6) {
        if ((s32)FrameInt(o->partModels[1].curFrame) >= (s32)FrameInt(o->partModels[1].numFrames) - 0x2d) {
            Mtx43_SetTranslate(&data_021f47e0, zero.x, zero.y, zero.z);
            o->pourEffectPos.x = 0x16a00;
            o->pourEffectPos.y = 0x1900;
            o->pourEffectPos.z = 0x15000;
        } else {
            data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
            o->pourEffectPos.x = data_021f47e0.m[9];
            o->pourEffectPos.y = data_021f47e0.m[10];
            o->pourEffectPos.z = data_021f47e0.m[11];
        }
    } else {
        data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
        o->pourEffectPos.x = data_021f47e0.m[9];
        o->pourEffectPos.y = data_021f47e0.m[10];
        o->pourEffectPos.z = data_021f47e0.m[11];
    }
    o->partModels[1].mtx = data_021f47e0;
    st = o->serveState;
    if ((u32)(st - 8) <= 1) {
        Mtx43_SetTranslate(&data_021f47e0, zero.x, zero.y, zero.z);
        o->partModels[2].mtx = data_021f47e0;
    } else if (st == 5) {
        if (FrameInt(o->partModels[2].curFrame) >= 0x10) {
            Mtx43_SetTranslate(&data_021f47e0, zero.x, zero.y, zero.z);
        } else {
            data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
        }
    } else if (st == 6) {
        if ((s32)FrameInt(o->partModels[2].curFrame) >= (s32)FrameInt(o->partModels[2].numFrames) - 0x2d) {
            Mtx43_SetTranslate(&data_021f47e0, zero.x, zero.y, zero.z);
        } else {
            data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
        }
    } else {
        data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxB();
    }
    o->partModels[2].mtx = data_021f47e0;
    if (FrameInt(o->partModels[3].curFrame) >= 0xf && FrameInt(o->partModels[3].curFrame) <= 0x48) {
        data_021f47e0 = *(Mtx43 *)SpNpcBrewster_GetJointMtxE();
    } else {
        Mtx43_SetTranslate(&data_021f47e0, data_ov004_02250d5c.x, data_ov004_02250d5c.y, data_ov004_02250d5c.z);
    }
    o->partModels[3].mtx = data_021f47e0;
    Mtx43_SetTranslate(&data_021f47e0, data_ov004_02250cd8.x, data_ov004_02250cd8.y, data_ov004_02250cd8.z);
    o->partModels[4].mtx = data_021f47e0;
    o->partModels[5].mtx = data_021f47e0;
    Mtx43_SetTranslate(&data_021f47e0, data_ov004_02250cf0.x, data_ov004_02250cf0.y, data_ov004_02250cf0.z);
    o->partModels[6].mtx = data_021f47e0;
    o->partModels[7].mtx = data_021f47e0;
    Mtx43_SetTranslate(&data_021f47e0, data_ov004_02250d08.x, data_ov004_02250d08.y, data_ov004_02250d08.z);
    o->partModels[8].mtx = data_021f47e0;
    if (o->modelVisible != 0) {
        o->model.drawAnimated(NULL);
    }
    for (i = 0; i < 9; i++) {
        if (o->partVisible[i] != 0) {
            o->partModels[i].drawAnimated(NULL);
        }
    }
}

BOOL CafeCoffeeSet::onDelete() {
    u8 i;
    releaseResources();
    for (i = 0; i < 9; i++) {
        CafeCoffeeSet_ReleasePart(this, i);
    }
    sCafeCoffeeSet = NULL;
    return TRUE;
}

extern "C" BOOL CafeCoffeeSet_ChangeState(CafeCoffeeSet *o, s32 n) {
    static BOOL (*const tbl[10])(CafeCoffeeSet *) = {
        CafeCoffeeSet_EnterState00, CafeCoffeeSet_EnterState01, CafeCoffeeSet_EnterState02, CafeCoffeeSet_EnterState03,
        CafeCoffeeSet_EnterState04, CafeCoffeeSet_EnterState05, CafeCoffeeSet_EnterState06, CafeCoffeeSet_EnterState03,
        CafeCoffeeSet_EnterState08, CafeCoffeeSet_EnterState09};
    if (n < 10) {
        if (tbl[n](o)) {
            o->serveState = n;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void CafeCoffeeSet_UpdateState(CafeCoffeeSet *o) {
    static void (*const tbl[10])(CafeCoffeeSet *) = {
        CafeCoffeeSet_UpdateState00, CafeCoffeeSet_UpdateState01, CafeCoffeeSet_UpdateState02, CafeCoffeeSet_UpdateState03,
        CafeCoffeeSet_UpdateState04, CafeCoffeeSet_UpdateState05, CafeCoffeeSet_UpdateState06, CafeCoffeeSet_UpdateState03,
        CafeCoffeeSet_UpdateState08, CafeCoffeeSet_UpdateState09};
    s32 i = o->serveState;
    if (i < 10) {
        tbl[i](o);
    }
}

extern "C" ActorProfile sCafeCoffeeSetProfile = {(void *(*)())CafeCoffeeSet_Create, 0x64, 0x13, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" BOOL CafeCoffeeSet_EnterState00(CafeCoffeeSet *o) {
    o->modelVisible = 1;
    o->partVisible[0] = 1;
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState00(CafeCoffeeSet *o) {
    SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf2) {
        CafeCoffeeSet_SwitchAnim(o, 0, &o->model, &o->res, 0, 0x1000, 0, 0);
        CafeCoffeeSet_SwitchAnim(o, 0, M0, R0, 0, 0x1000, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf4) {
        CafeCoffeeSet_SwitchAnim(o, 1, &o->model, &o->res, 0, 0x1000, 0, 0);
        CafeCoffeeSet_SwitchAnim(o, 1, M0, R0, 0, 0x1000, 0, 0);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState01(CafeCoffeeSet *o) {
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState01(CafeCoffeeSet *o) {
    SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf3) {
        CafeCoffeeSet_SwitchAnim(o, 0, M1, R1, 0, 0x1000, 0, 0);
        CafeCoffeeSet_SwitchAnim(o, 0, M2, R2, 0, 0x1000, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf5) {
        CafeCoffeeSet_SwitchAnim(o, 1, M1, R1, 0, 0x1000, 0, 0);
        CafeCoffeeSet_SwitchAnim(o, 1, M2, R2, 0, 0x1000, 0, 0);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState02(CafeCoffeeSet *o) {
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState02(CafeCoffeeSet *o) {
    SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf3) {
        CafeCoffeeSet_SwitchAnim(o, 3, M1, R1, 0, 0x1000, 0, 0);
        CafeCoffeeSet_SwitchAnim(o, 0, M2, R2, 0, 0x1000, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf5) {
        CafeCoffeeSet_SwitchAnim(o, 4, M1, R1, 0, 0x1000, 0, 0);
        CafeCoffeeSet_SwitchAnim(o, 1, M2, R2, 0, 0x1000, 0, 0);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState03(CafeCoffeeSet *o) {
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState03(CafeCoffeeSet *o) {
    u32 t = SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf2) {
        UP(0, &o->model, &o->res, 0, 0);
        UP(0, M0, R0, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf4) {
        UP(1, &o->model, &o->res, 0, 0);
        UP(1, M0, R0, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf6) {
        if (t <= 6) {
            o->modelVisible = 1;
            o->partVisible[0] = 1;
        } else {
            o->modelVisible = 0;
            o->partVisible[0] = 0;
        }
        if (t >= 0x12) {
            o->partVisible[1] = 1;
            o->partVisible[2] = 1;
        } else {
            o->partVisible[1] = 0;
            o->partVisible[2] = 0;
        }
        UP(2, &o->model, &o->res, 0, 0);
        UP(2, M0, R0, 0, 0);
        UP(2, M1, R1, 0, 0);
        UP(2, M2, R2, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf3) {
        UP(0, M1, R1, 0, 0);
        UP(0, M2, R2, 0, 0);
    } else if (SpNpcBrewster_GetAnimState() == 0xf5) {
        UP(1, M1, R1, 0, 0);
        UP(1, M2, R2, 0, 0);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState04(CafeCoffeeSet *o) {
    ((BlendAnimModel *)&o->partModels[3])->initAnim(RoomObjRes_GetBca(&o->partRes[3], 0), 1, 0x1000, 0, 0);
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState04(CafeCoffeeSet *o) {
    SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf7) {
        UP(5, M1, R1, 0, 0);
        UP(3, M2, R2, 0, 0);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState05(CafeCoffeeSet *o) {
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState05(CafeCoffeeSet *o) {
    u32 t = SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf8) {
        UP(6, M1, R1, 1, 0);
        UP(4, M2, R2, 1, 0);
        if (t == 0x3b) {
            o->pourEffect = Effect_CreateById(0x6b, &o->pourEffectPos, &o->rotY, 0);
        }
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState06(CafeCoffeeSet *o) {
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState06(CafeCoffeeSet *o) {
    u32 t = SpNpcBrewster_GetAnimFrame();
    if (SpNpcBrewster_GetAnimState() == 0xf8) {
        UP(7, M1, R1, 3, t);
        UP(5, M2, R2, 3, t);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState08(CafeCoffeeSet *o) {
    Effect_End(o->pourEffect);
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState08(CafeCoffeeSet *o) {
    AnimFrameCtrl *f1 = &o->partModels[1];
    if (((BlendAnimModel *)M1)->getAnmRes() == RoomObjRes_GetBca(R1, 6) && f1->isFinished()) {
        UP(9, M1, R1, 1, 0);
        UP(7, M2, R2, 1, 0);
    } else if (((BlendAnimModel *)M1)->getAnmRes() == RoomObjRes_GetBca(R1, 9) && f1->isFinished()) {
        UP(0xa, M1, R1, 1, 0);
        UP(8, M2, R2, 1, 0);
    } else if (((BlendAnimModel *)M1)->getAnmRes() == RoomObjRes_GetBca(R1, 0xa) && f1->isFinished()) {
        Camera_MuteSe();
        Camera_SetMode4();
        UP(0xb, M1, R1, 1, 0);
        UP(9, M2, R2, 1, 0);
    }
}

extern "C" BOOL CafeCoffeeSet_EnterState09(CafeCoffeeSet *o) {
    Camera_RestorePrevMode();
    return TRUE;
}

extern "C" void CafeCoffeeSet_UpdateState09(CafeCoffeeSet *o) {
    if (((BlendAnimModel *)M1)->getAnmRes() == RoomObjRes_GetBca(R1, 0xb)) {
        if (static_cast<AnimFrameCtrl *>(M1)->isFinished()) {
            UP(0xc, M1, R1, 1, 0);
            UP(0xa, M2, R2, 1, 0);
        }
    }
}

extern "C" void CafeCoffeeSet_SyncToBrewster(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        CafeCoffeeSet_UpdateMatrices(g);
    }
}

extern "C" void CafeCoffeeSet_LoadPart(CafeCoffeeSet *o, u32 idx, const char *id, const char *x) {
    RoomObjRes *r = &o->partRes[idx];
    RoomObjTexAuto *q;
    RoomObjRes_Load(r, id);
    q = &o->partTex[idx];
    RoomObjTex_Load(q, x);
    o->partModels[idx].setResource((NNSG3dResMdl *)RoomObjRes_GetModel(r), 0);
    NNS_G3dBindMdlTex(RoomObjRes_GetModel(r), RoomObjTex_Get(q));
    NNS_G3dBindMdlPltt(RoomObjRes_GetModel(r), RoomObjTex_Get(q));
}

extern "C" void CafeCoffeeSet_ReleasePart(CafeCoffeeSet *o, u32 idx) {
    RoomObjRes_Free(&o->partRes[idx]);
    RoomObjTex_Reset(&o->partTex[idx]);
}

extern "C" void CafeCoffeeSet_InitPartAnim(CafeCoffeeSet *o, u32 idx) {
    RoomObjRes *r = &o->partRes[idx];
    if (RoomObjRes_GetBca(r, 0)) {
        AnimModel *m = &o->partModels[idx];
        if (m->allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)m)->initAnim(RoomObjRes_GetBca(r, 0), 1, 0x1000, 0, 0);
            m->attachAnim();
            m->frameStep = 0;
        }
    }
}

extern "C" s32 CafeCoffeeSet_SetState00(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 0);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState01(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 1);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState02(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 2);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState03(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 3);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState04(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 4);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState05(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 5);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState06(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 6);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState07(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 7);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState08(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 8);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_SetState09(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return CafeCoffeeSet_ChangeState(g, 9);
    }
    return 0;
}

extern "C" s32 CafeCoffeeSet_GetState(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        return g->serveState;
    }
    return 0;
}

extern "C" BOOL CafeCoffeeSet_IsAnim0BAtFrame9(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        void *t = ((BlendAnimModel *)&g->partModels[1])->getAnmRes();
        if (t == RoomObjRes_GetBca(&g->partRes[1], 0xb)) {
            if (FrameInt(sCafeCoffeeSet->partModels[1].curFrame) == 9) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

extern "C" BOOL CafeCoffeeSet_IsAnim0CDone(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        void *t = ((BlendAnimModel *)&g->partModels[1])->getAnmRes();
        if (t == RoomObjRes_GetBca(&g->partRes[1], 0xc)) {
            if (static_cast<AnimFrameCtrl *>(&sCafeCoffeeSet->partModels[1])->isFinished()) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

extern "C" void CafeCoffeeSet_SwitchAnim(CafeCoffeeSet *self, u32 id, AnimModel *m, RoomObjRes *res, u8 a5, s32 a6, u32 a7, u32 a8) {
    void *t = ((BlendAnimModel *)m)->getAnmRes();
    if (t != RoomObjRes_GetBca(res, id)) {
        ((BlendAnimModel *)m)->initAnim(RoomObjRes_GetBca(res, id), a5, a6, (u16)a7, (u16)a8);
    }
}

extern "C" void CafeCoffeeSet_StartEffectB(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        g->partVisible[6] = 1;
        sCafeCoffeeSet->partVisible[7] = 1;
    }
}

extern "C" void CafeCoffeeSet_SetFlagEF8(void) {
    CafeCoffeeSet *g = sCafeCoffeeSet;
    if (g) {
        g->partVisible[8] = 1;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_022264a0) {
    HOST_OVERLAY_VAR(sCafeCoffeeSet),
    HOST_OVERLAY_VAR(data_ov004_02250d2c),
    HOST_OVERLAY_VAR(data_ov004_02250d44),
    HOST_OVERLAY_VAR(data_ov004_02250d5c),
    HOST_OVERLAY_VAR(data_ov004_02250cd8),
    HOST_OVERLAY_VAR(data_ov004_02250cf0),
    HOST_OVERLAY_VAR(data_ov004_02250d08),
    HOST_OVERLAY_VAR(sCafeCoffeeSetProfile),
    HOST_OVERLAY_VARS_END
};

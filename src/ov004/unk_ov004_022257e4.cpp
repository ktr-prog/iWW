#include "uptr.h"
#include "game/BoxCollider.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "gfx/CachedModel.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "gfx/ModelAnim.h"
#include "gfx/Model.h"
#include "gfx/TwoLayerAnimModel.h"
#include "net/CommManager.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02036c58.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/ov004/unk_ov004_022257e4.h"
#include "gfx/G3dResAccess.h"
#include "gfx/BgModelCache.h"
#include "town/TownTravelState.h"
#include "nnsys/g3d_rt.h"



















class CheckInGate : public RoomObjActor {
public:
    CheckInGate();
    virtual ~CheckInGate();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL changeSyncState(u32 a);

    void updateState03();
    BOOL enterState03();
    void updateState02();
    BOOL enterState02();
    void updateState01();
    BOOL enterState01();
    void updateState00();
    BOOL enterState00();
    void updateState();
    void removeDoorCollision();
    void updateDoorCollision();
    void setDoorOffset(s32 a);
    void clearDoorUpdate();
    void applyHourLight(u32 a, NNSG3dRS *p);
    BOOL initMatAnim();
    BOOL initBodyAnim();
    void setGroundMatFlags();
    BOOL bindTextures();

    /* 0x290 */ ModelAnim matAnim;
    /* 0x2b0 */ u32 matIdx[3];
    /* 0x2bc */ BoxCollider doorCollider;
    /* 0x358 */ BoxCollider leftCollider;
    /* 0x3f4 */ BoxCollider rightCollider;
    /* 0x490 */ u8 doorUpdate;
    /* 0x494 */ s32 doorOffset;
};

typedef CheckInGate Cls;
typedef void (Cls::*Fn1)();
typedef BOOL (Cls::*Fn2)();

extern "C" {
extern CommManager *gCommManager;

void CheckInGate_SetInstance(Cls *c);

void Math_ApproachS32Max(s32 *, s32, s32, s32);
s32 BoxCollider_Unregister(BoxCollider *);
s32 BoxCollider_Register(BoxCollider *, s32, s32, s32, VecFx32 *, s16, VecFx32 *);
void Clock_GetMinuteHour(u8 *);
s32 FX_Div(s32, s32);
s32 func_01ffcb0c(s32, s32);
s32 Scene_GetCurrent(void);
void NNS_G3dBindMdlTex(void *, void *);
void NNS_G3dBindMdlPltt(void *, void *);
}

extern "C" const u8 sCheckInGateHourLight[];
#ifdef HOST
#define data_ov004_0224016c (sCheckInGateHourLight + 0x20)
#else
extern "C" const u8 data_ov004_0224016c[];
#endif
#define data_ov004_0224014d (sCheckInGateHourLight + 1)
#define data_ov004_0224014e (sCheckInGateHourLight + 2)
#define data_ov004_02240150 (sCheckInGateHourLight + 4)
#define data_ov004_02240154 (sCheckInGateHourLight + 8)

extern "C" { extern DebugColor data_ov004_02250c48; }
extern "C" { extern DebugColor data_ov004_02250c4c; }
extern "C" { extern DebugColor data_ov004_02250c40; }
extern "C" { extern DebugColor data_ov004_02250c44; }
extern "C" { extern char data_ov004_0224d7ac[]; }
extern "C" { extern DebugColor data_ov004_02250c50; }
extern "C" { extern char *sCheckInGateGroundMats[7]; }
extern "C" { extern Cls *sCheckInGate; }
extern "C" { extern char data_ov004_0224d7b8[]; }
extern "C" { extern char data_ov004_0224d77c[]; }
extern "C" { extern char data_ov004_0224d7c4[]; }
extern "C" { extern char data_ov004_0224d788[]; }
extern "C" { extern char data_ov004_0224d794[]; }
extern "C" { extern char data_ov004_0224d7a0[]; }
extern "C" { extern DebugColor data_ov004_02250c38; }
extern "C" { extern ActorProfile sCheckInGateProfile; }
#ifdef HOST
extern "C" { extern const u8 sCheckInGateHourLight[0x124]; }
#else
extern "C" { extern const u8 sCheckInGateHourLight[0x20]; }
#endif
#ifndef HOST
extern "C" { extern const u8 data_ov004_0224016c[0x104]; }
#endif

extern "C" CheckInGate *CheckInGate_Create() {
    return new CheckInGate();
}

extern "C" void CheckInGate_MatCallback(NNSG3dRS *o);
extern "C" void CheckInGate_MatCallback(NNSG3dRS *o) {
    NNSG3dRenderObj *s = o->pRenderObj;
    if (s->ptrUser != 0) {
        ((Cls *)s->ptrUser)->applyHourLight(o->c[1], o);
    }
}

extern "C" void CheckInGate_InitRenderObj(NNSG3dRS *o) {
    o->cbVecFunc[4] = (void *)CheckInGate_MatCallback;
    o->cbVecTiming[4] = 2;
}

CheckInGate::CheckInGate() {
}

CheckInGate::~CheckInGate() {
}

FxVec3 CheckInGate_onCreate_sa(0xb000, 0, 0x10800);
FxVec3 CheckInGate_onCreate_sb(0x15000, 0, 0x10800);
BOOL CheckInGate::onCreate() {
    s32 v;
    TownTravelState *s = (TownTravelState *)TownSessionState_GetTravelState(TownSessionState_Get());
    RoomObjRes_Load(&res, "/roomObj/obj_check_in.arc");
    RoomObjTex_Load(&tex, "/roomObj/obj_check_in.nsbtx");
    model.setResource((NNSG3dResMdl *)RoomObjRes_GetModel(&res), 0);
    matIdx[0] = ((G3dResAccess *)RoomObjRes_GetModel(&res))->findMatIdx("m_lt");
    matIdx[1] = ((G3dResAccess *)RoomObjRes_GetModel(&res))->findMatIdx("m_ltdoor");
    matIdx[2] = ((G3dResAccess *)RoomObjRes_GetModel(&res))->findMatIdx("m_open");
    model.setInitCallback(CheckInGate_InitRenderObj, this);
    bindTextures();
    setGroundMatFlags();
    initBodyAnim();
    initMatAnim();
    v = Scene_GetCurrent();
    switch (v) {
    case 0xb:
        if (gCommManager->isSlotActive(gCommManager->myAid)) {
            changeSyncState(2);
        } else {
            changeSyncState(0);
        }
        break;
    case 0xc:
        if (s->getMode() == 1) {
            changeSyncState(0);
        } else {
            changeSyncState(2);
        }
        break;
    case 0xd:
    case 0xe:
    case 0x2f:
        changeSyncState(2);
        break;
    }
    CheckInGate_SetInstance(this);
    doorOffset = -1;
    BoxCollider_Register(&leftCollider, 0x2000, 0x1c00, 0x2000, &CheckInGate_onCreate_sa, 0, 0);
    BoxCollider_Register(&rightCollider, 0x2000, 0x1c00, 0x2000, &CheckInGate_onCreate_sb, 0, 0);
    return TRUE;
}

BOOL CheckInGate::onExecute() {
    clearDoorUpdate();
    updateState();
    updateDoorCollision();
    return TRUE;
}

BOOL CheckInGate::onDraw() {
    model.drawAnimated(0);
    return TRUE;
}

BOOL CheckInGate::onDelete() {
    RoomObjRes_Free(&res);
    RoomObjTex_Reset(&tex);
    removeDoorCollision();
    BoxCollider_Unregister(&leftCollider);
    BoxCollider_Unregister(&rightCollider);
    return TRUE;
}

BOOL CheckInGate::bindTextures() {
    void *o;
    o = RoomObjRes_GetModel(&res);
    NNS_G3dBindMdlTex(o, BgModelCache_Get()->getGroundTex());
    o = RoomObjRes_GetModel(&res);
    NNS_G3dBindMdlPltt(o, BgModelCache_Get()->getGroundTex());
    o = RoomObjRes_GetModel(&res);
    NNS_G3dBindMdlTex(o, RoomObjTex_Get(&tex));
    o = RoomObjRes_GetModel(&res);
    NNS_G3dBindMdlPltt(o, RoomObjTex_Get(&tex));
    return TRUE;
}

void CheckInGate::setGroundMatFlags() {
    u32 i;
    u8 *base;
    u32 col;
    { u8 *h = (u8 *)RoomObjRes_GetModel(&res); base = h + *(s32 *)(h + 8); }
    i = 0;
    col = ((const u32 *)data_ov004_0224016c)[0x40];
    for (; i < 7; i++) {
        s32 x = ((G3dResAccess *)(RoomObjRes_GetModel(&res)))->findMatIdx((const char *)(sCheckInGateGroundMats[i]));
        u8 *t = base + 4 + *(u16 *)(base + 0xa);
        u8 *q = t + *(u16 *)t * x;
        u32 *rec = (u32 *)(base + *(s32 *)(q + 4));
        if (rec != 0) {
            rec[4] &= ~0xf;
            rec[4] |= col;
            rec[3] &= ~0xf;
            rec[3] |= col;
        }
    }
}

BOOL CheckInGate::initBodyAnim() {
    if (RoomObjRes_GetBca(&res, 0) != 0 && model.allocAnmObj(gBgHeap) != 0) {
        ((BlendAnimModel *)(&model))->initAnim(RoomObjRes_GetBca(&res, 0), 0, 0x1000, 0, 0);
        model.attachAnim();
        return TRUE;
    }
    return FALSE;
}

BOOL CheckInGate::initMatAnim() {
    if (RoomObjRes_GetBma(&res, 0) != 0 && matAnim.allocMatAnm(model.resMdl, gBgHeap)) {
        matAnim.init(RoomObjRes_GetBma(&res, 0), 0, 0x1000, 0);
        matAnim.addToRenderObj(model.getRenderObj());
        return TRUE;
    }
    return FALSE;
}

extern "C" void CheckInGate_SetInstance(Cls *c) {
    sCheckInGate = c;
}

extern "C" BOOL CheckInGate_Open() {
    if (sCheckInGate != 0) {
        return sCheckInGate->changeSyncState(1);
    }
    return FALSE;
}

extern "C" BOOL CheckInGate_Close() {
    if (sCheckInGate != 0) {
        return sCheckInGate->changeSyncState(3);
    }
    return FALSE;
}

extern "C" BOOL CheckInGate_IsOpen() {
    if (sCheckInGate != 0 && sCheckInGate->tex.syncState == 2) {
        return TRUE;
    }
    return FALSE;
}

void CheckInGate::applyHourLight(u32 a, NNSG3dRS *p) {
    u8 tm[2];
    Clock_GetMinuteHour(tm);
    s32 hr = tm[1];
    s32 f = FX_Div(tm[0] << 12, 0x3c000);
    u32 i0 = (u8)((hr + 1) % 24) * 12;
    u32 i1 = (u8)(hr % 24) * 12;
    u32 packed;
    s32 w1, w2;
    packed = (u8)(((0x1000 - f) * data_ov004_0224014e[i1] + f * data_ov004_0224014e[i0]) >> 12) << 10;
    {
        u32 c = (u8)(((0x1000 - f) * sCheckInGateHourLight[i1] + f * sCheckInGateHourLight[i0]) >> 12);
        u32 d = (u8)(((0x1000 - f) * data_ov004_0224014d[i1] + f * data_ov004_0224014d[i0]) >> 12) << 5;
        packed |= c | d;
    }
    u16 pk = (u16)packed;
    w1 = ((0x1000 - f) * *(s32 *)(data_ov004_02240154 + i1) + f * *(s32 *)(data_ov004_02240154 + i0)) >> 12;
    w2 = ((0x1000 - f) * *(s32 *)(data_ov004_02240150 + i1) + f * *(s32 *)(data_ov004_02240150 + i0)) >> 12;
    u32 e0 = matIdx[0];
    if (a == e0 || a == matIdx[1] || a == matIdx[2]) {
        u8 b = (p->pMatAnmResult->prmPolygonAttr >> 16) & 0x1f;
        u8 r;
        if (a == e0) {
            r = (func_01ffcb0c(b << 12, w2) >> 12) & 0x1f;
        } else {
            r = (func_01ffcb0c(b << 12, w1) >> 12) & 0x1f;
        }
        p->pMatAnmResult->prmPolygonAttr &= 0xffe0ffff;
        p->pMatAnmResult->prmPolygonAttr |= r << 16;
        p->flag &= ~0x100;
        p->pMatAnmResult->prmMatColor0 &= 0xffff8000;
        p->pMatAnmResult->prmMatColor0 |= pk;
    }
}

void CheckInGate::clearDoorUpdate() {
    doorUpdate = 0;
}

void CheckInGate::setDoorOffset(s32 a) {
    doorUpdate = 1;
    doorOffset = a;
}

void CheckInGate::updateDoorCollision() {
    if (doorCollider.isActive) {
        BoxCollider_Unregister(&doorCollider);
    }
    if (doorUpdate) {
        VecFx32 v;
        s32 z = doorOffset + 0x10000;
        v.x = 0x10000;
        v.y = 0;
        v.z = z;
        BoxCollider_Register(&doorCollider, 0x8000, 0, 0x2000, &v, 0, 0);
    }
}

void CheckInGate::removeDoorCollision() {
    if (doorCollider.isActive) {
        BoxCollider_Unregister(&doorCollider);
    }
}

extern "C" char data_ov004_0224d7ac[] = "m_grd_soi";

extern "C" Cls *sCheckInGate = 0;

extern "C" char data_ov004_0224d788[] = "m_grd_g_s";

extern "C" DebugColor data_ov004_02250c48(31, 20, 20, 31);

extern "C" DebugColor data_ov004_02250c4c(20, 20, 31, 31);

extern "C" DebugColor data_ov004_02250c40(31, 31, 20, 31);

#ifndef HOST
extern "C" const u8 data_ov004_0224016c[0x104] = {
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1c, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x66, 0x06, 0x00, 0x00, 0x1f, 0x1e, 0x16, 0x00, 0x00, 0x08, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x9a, 0x09, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x9a, 0x09, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1e, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x1c, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x15, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x18, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
};
#endif

extern "C" char data_ov004_0224d7b8[] = "m_grd_clf2";

#ifdef HOST
extern "C" const u8 sCheckInGateHourLight[0x124] = {
    0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0x04, 0x00, 0x00,
    0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0x04, 0x00, 0x00,
    0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1c, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x66, 0x06, 0x00, 0x00, 0x1f, 0x1e, 0x16, 0x00, 0x00, 0x08, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x9a, 0x09, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x33, 0x0b, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x00, 0x9a, 0x09, 0x00, 0x00,
    0xcd, 0x0c, 0x00, 0x00, 0x1f, 0x1e, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x1c, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x15, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x0b, 0x00, 0x00, 0x1f, 0x18, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0x04, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
};
#else
extern "C" const u8 sCheckInGateHourLight[0x20] = {
    0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0x04, 0x00, 0x00,
    0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0x04, 0x00, 0x00,
    0x1f, 0x1f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

extern "C" DebugColor data_ov004_02250c44(20, 31, 20, 31);

extern "C" char data_ov004_0224d794[] = "m_grd_grs";

extern "C" DebugColor data_ov004_02250c50(20, 31, 31, 31);

extern "C" char data_ov004_0224d7a0[] = "m_grd_s_s";

extern "C" char data_ov004_0224d7c4[] = "m_grd_clf3";

extern "C" char *sCheckInGateGroundMats[7] = {data_ov004_0224d77c, data_ov004_0224d7b8, data_ov004_0224d7c4, data_ov004_0224d788,
                                           data_ov004_0224d794, data_ov004_0224d7a0, data_ov004_0224d7ac};

extern "C" DebugColor data_ov004_02250c38(20, 24, 24, 31);

extern "C" char data_ov004_0224d77c[] = "m_grd_clf";

extern "C" ActorProfile sCheckInGateProfile = {(void *(*)())CheckInGate_Create, 0x11, 0x14, 0, 0xc8000, 0x12c000, 0x258000};

BOOL CheckInGate::changeSyncState(u32 a) {
    static Fn2 tbl[4] = {&Cls::enterState00, &Cls::enterState01, &Cls::enterState02,
                         &Cls::enterState03};
    if (a < 4) {
        if ((this->*tbl[a])()) {
            tex.syncState = a;
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void CheckInGate::updateState() {
    static Fn1 tbl[4] = {&Cls::updateState00, &Cls::updateState01, &Cls::updateState02,
                         &Cls::updateState03};
    u32 i = tex.syncState;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL CheckInGate::enterState00() {
    void *r = RoomObjRes_GetBca(&res, 0);
    ((BlendAnimModel *)(&model))->initAnim(r, 0, 0x1000, 0, 0);
    void *o = model.getRenderObj();
    matAnim.replace(o, RoomObjRes_GetBma(&res, 0), 0, 0x1000, 0);
    return TRUE;
}

void CheckInGate::updateState00() {
    model.stepAnim();
    matAnim.step();
    ((G3dAnmObj *)matAnim.anmObj)->frame = matAnim.curFrame;
    setDoorOffset(0);
}

BOOL CheckInGate::enterState01() {
    void *r = RoomObjRes_GetBca(&res, 1);
    ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
    void *o = model.getRenderObj();
    matAnim.replace(o, RoomObjRes_GetBma(&res, 1), 1, 0x1000, 0);
    Snd_PlaySe(0x4eb);
    return TRUE;
}

void CheckInGate::updateState01() {
    s32 v;
    model.stepAnim();
    matAnim.step();
    ((G3dAnmObj *)matAnim.anmObj)->frame = matAnim.curFrame;
    v = doorOffset;
    Math_ApproachS32Max(&v, -0x2000, 0x100, 0x1000);
    setDoorOffset(v);
    if (model.isFinished()) {
        changeSyncState(2);
    } else if (model.hasPassedFrame(0x3a)) {
        Snd_PlaySe(0x4ed);
    }
}

BOOL CheckInGate::enterState02() {
    void *r = RoomObjRes_GetBca(&res, 2);
    ((BlendAnimModel *)(&model))->initAnim(r, 0, 0x1000, 0, 0);
    void *o = model.getRenderObj();
    matAnim.replace(o, RoomObjRes_GetBma(&res, 2), 0, 0x1000, 0);
    return TRUE;
}

void CheckInGate::updateState02() {
    model.stepAnim();
    matAnim.step();
    ((G3dAnmObj *)matAnim.anmObj)->frame = matAnim.curFrame;
    if (Scene_GetCurrent() == 0xb) {
        setDoorOffset(-0x2000);
    }
}

BOOL CheckInGate::enterState03() {
    void *r = RoomObjRes_GetBca(&res, 3);
    ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
    void *o = model.getRenderObj();
    matAnim.replace(o, RoomObjRes_GetBma(&res, 3), 1, 0x1000, 0);
    Snd_PlaySe(0x4ec);
    return TRUE;
}

void CheckInGate::updateState03() {
    model.stepAnim();
    matAnim.step();
    ((G3dAnmObj *)matAnim.anmObj)->frame = matAnim.curFrame;
    u32 t = doorOffset;
    Math_ApproachS32Max((s32 *)&t, 0, 0x100, 0x1000);
    setDoorOffset(t);
    if (model.isFinished() != 0) {
        changeSyncState(0);
    } else {
        if (model.hasPassedFrame(0x3a) != 0) {
            Snd_PlaySe(0x4ee);
        }
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_022257e4) {
    HOST_OVERLAY_VAR(CheckInGate_onCreate_sa),
    HOST_OVERLAY_VAR(CheckInGate_onCreate_sb),
    HOST_OVERLAY_VAR(data_ov004_0224d7ac),
    HOST_OVERLAY_VAR(sCheckInGate),
    HOST_OVERLAY_VAR(data_ov004_0224d788),
    HOST_OVERLAY_VAR(data_ov004_02250c48),
    HOST_OVERLAY_VAR(data_ov004_02250c4c),
    HOST_OVERLAY_VAR(data_ov004_02250c40),
    HOST_OVERLAY_VAR(data_ov004_0224d7b8),
    HOST_OVERLAY_VAR(data_ov004_02250c44),
    HOST_OVERLAY_VAR(data_ov004_0224d794),
    HOST_OVERLAY_VAR(data_ov004_02250c50),
    HOST_OVERLAY_VAR(data_ov004_0224d7a0),
    HOST_OVERLAY_VAR(data_ov004_0224d7c4),
    HOST_OVERLAY_VAR(sCheckInGateGroundMats),
    HOST_OVERLAY_VAR(data_ov004_02250c38),
    HOST_OVERLAY_VAR(data_ov004_0224d77c),
    HOST_OVERLAY_VAR(sCheckInGateProfile),
    HOST_OVERLAY_VARS_END
};

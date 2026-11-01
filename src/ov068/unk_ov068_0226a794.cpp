#include "types.h"
#include "host_tick.h"
#include "host_shared_calls.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "player/PlayerActionRequest.h"
#include "sys/ProcBase.h"
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "gfx/DebugColor.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/NNSG3dRenderObj.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/AnimModel.h"
#include "gfx/TwoLayerAnimModel.h"
#include "player/PlayerActor.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/Unk_02007694.h"
#include "save/SaveData.h"
#include "snd/BuildingSeEmitter.h"
#include "sys/ClockDateTime.h"
#include "game/SceneWarp.h"
#include "player/Unk_0200f070_V3.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/ov068/unk_ov068_0226a794.h"
#include "proto/main/unk_020b4828.h"














class KappnTaxi : public BuildingActor {
public:
    KappnTaxi();
    virtual ~KappnTaxi();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual void onJointCalcPost(u32 a, void *b);
    virtual BOOL initBuilding();
    virtual void onMessageEnd(u32 attr);
    virtual BOOL needsMatrixUpdate();
    virtual VecFx32Ctor getSoundPos();
    virtual s32 getVoiceType();

    void execTaxiLeaveEnd();
    void execTaxiLeaveDrive();
    void execTaxiPlayerGetIn();
    void execTaxiLeaveDoorAnim();
    void execTaxiLeaveDoorOpen();
    void execTaxiPlayerExitTownHall();
    void execTaxiLeave();
    void execTaxiWarpTownHall();
    void execTaxiEnterTownHall();
    void execTaxiWaitPlayerWalk();
    void execTaxiDepart();
    void execTaxiTalkWait();
    void execTaxiTalk();
    void execTaxiPlayerGetOut();
    void execTaxiDoorOpen();
    void execTaxiArrive();
    void execTaxiIdle();
    BOOL enterTaxiLeaveEnd();
    BOOL enterTaxiLeaveDrive();
    BOOL enterTaxiPlayerGetIn();
    BOOL enterTaxiLeaveDoorAnim();
    BOOL enterTaxiLeaveDoorOpen();
    BOOL enterTaxiPlayerExitTownHall();
    BOOL enterTaxiLeave();
    BOOL enterTaxiWarpTownHall();
    BOOL enterTaxiEnterTownHall();
    BOOL enterTaxiWaitPlayerWalk();
    BOOL enterTaxiDepart();
    BOOL enterTaxiTalkWait();
    BOOL enterTaxiTalk();
    BOOL enterTaxiPlayerGetOut();
    BOOL enterTaxiDoorOpen();
    BOOL enterTaxiArrive();
    BOOL enterTaxiIdle();

    void updateTaxiState();
    BOOL setTaxiState(s32 idx);
    void stopEffect42();
    void updateEffect42();
    void startEffect42();
    void stopEffect41();
    void updateEffect41();
    void startEffect41();
    s32 getAngleToPlayer();
    VecFx32Copy getDoorPoint();
    void *callGetBca2Anim();

    /* 0x2b0 */ s32 taxiState;
    /* 0x2b4 */ s32 townHallGridX;
    /* 0x2b8 */ s32 townHallGridZ;
    /* 0x2bc */ VecFx32Ctor townHallWalkTarget;
    /* 0x2c8 */ VecFx32Copy carPos;
    /* 0x2d4 */ u16 warpDelayTimer;
    /* 0x2d6 */ u8 getInTimer;
    /* 0x2d7 */ u8 exitWalkDelay;
    /* 0x2d8 */ u8 departFrameCount;
    /* 0x2d9 */ u8 getOutFrameCount;
    /* 0x2da */ u8 ownsTaxiFlags;
    /* 0x2db */ u8 pad_2db;
    /* 0x2dc */ s32 effect41;
    /* 0x2e0 */ s32 effect42;
};

struct KappnNpcIdBuf {
    u16 pad;
    u16 npcId;
};



extern "C" {
extern SaveData gSaveData;
void *PlayerActor_GetPlayerData(void *p);
void Clock_GetDateTime(ClockDateTime *p);
void DateTime_SubDays(ClockDateTime *p, s32 n);
void PlayerActor_SetLastPlayDate(PlayerActor *o, PlayerData *a, Unk_0200f17c_Date *d);
void TalkRequestFlags_ClearSceneHold();
void TalkRequestFlags_SetSceneHold();
u32 Scene_GetCurrent();
BOOL Npc_GetName(MsgString *self, u16 *p);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s16 Math_Atan2(s32 x, s32 y);
s32 FX_Div(s32 numer, s32 denom);
}



extern "C" DebugColor data_ov068_02271090(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov068_02271098(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov068_022710a4(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_022710a0(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_02271094(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov068_0227109c(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sKappnTaxiProfile = {(void *(*)())KappnTaxi_Create, 0x23, 0x29, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" void *KappnTaxi_Create() {
    return new KappnTaxi();
}

KappnTaxi::KappnTaxi() {
}

KappnTaxi::~KappnTaxi() {
}

BOOL KappnTaxi::initBuilding() {
    PlayerData *p = PlayerData_GetCurrent();
    carPos.x = position.x;
    carPos.y = position.y;
    carPos.z = position.z;
    if (Taxi_IsArriving()) {
        ownsTaxiFlags = 1;
        Scene_ResetTownReturnPos(0);
        setTaxiState(1);
    } else if (Taxi_IsLeaving()) {
        ownsTaxiFlags = 1;
        if (p) {
            u16 t = 0xfff1;
            p->setHeldItem(&t);
        }
        Scene_ResetTownReturnPos(0);
        setTaxiState(0xa);
    } else {
        setTaxiState(0);
    }
    return TRUE;
}

BOOL KappnTaxi::onExecute() {
    updateTaxiState();
    if (taxiState) {
        PlayerActor_SetEventLock(1);
    }
    return TRUE;
}

BOOL KappnTaxi::onDraw() {
    return TRUE;
}

BOOL KappnTaxi::onDelete() {
    if (taxiState) {
        TalkRequestFlags_ClearSceneHold();
    }
    if (ownsTaxiFlags) {
        ownsTaxiFlags = 0;
        Taxi_ClearArriving();
        Taxi_ClearLeaving();
    }
    return TRUE;
}

VecFx32Ctor KappnTaxi::getSoundPos() {
    VecFx32Ctor r;
    r.x = carPos.x;
    r.y = carPos.y;
    r.z = carPos.z;
    return r;
}

void *KappnTaxi::callGetBca2Anim() {
    return getBca2Anim();
}

BOOL KappnTaxi::needsMatrixUpdate() {
    if (taxiState) {
        return TRUE;
    }
    return FALSE;
}

void KappnTaxi::onJointCalcPost(u32 a, void *b) {
    if (a == 0) {
        NNSG3dJntAnmResult *o = ((NNSG3dRS *)b)->pJntAnmResult;
        VecFx32Copy v;
        VecFx32Copy out;
        VecFx32 *pv = &o->trans;
        v.x = pv->x;
        v.y = pv->y;
        v.z = pv->z;
        Vec_Add(&out, &position, &v);
        carPos.x = out.x;
        carPos.y = out.y;
        carPos.z = out.z;
    }
}

s32 KappnTaxi::getVoiceType() {
    return 0;
}

void KappnTaxi::onMessageEnd(u32) {
}

VecFx32Copy KappnTaxi::getDoorPoint() {
    VecFx32Copy r;
    r.x = carPos.x;
    r.y = carPos.y;
    r.z = carPos.z;
    r.x += FX_Div(0x19000, 0x64000) - 0xf6;
    return r;
}

s32 KappnTaxi::getAngleToPlayer() {
    if (PlayerActor_GetBodyPos(4)) {
        VecFx32Copy a;
        VecFx32Copy c;
        VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
        a.x = p->x;
        a.y = p->y;
        a.z = p->z;
        VecFx32Copy b = getDoorPoint();
        Vec_Sub(&c, &b, &a);
        return Math_Atan2(c.x, c.z);
    }
    return 0;
}

void KappnTaxi::startEffect41() {
    effect41 = Effect_Create(0x41, &carPos, 0, 0);
}

void KappnTaxi::updateEffect41() {
    u32 v = (u16)(model.curFrame >> 12);
    if (v >= 0x2d && v <= 0x31) {
        if (v == 0x2d) {
            startEffect41();
        }
        Effect_SetPosition(effect41, &carPos, 0, 0);
        if (v == 0x31) {
            stopEffect41();
        }
    }
}

void KappnTaxi::stopEffect41() {
    Effect_End(effect41);
}

void KappnTaxi::startEffect42() {
    effect42 = Effect_Create(0x42, &carPos, 0, 0);
}

void KappnTaxi::updateEffect42() {
    u32 v = (u16)(model.curFrame >> 12);
    if (v >= 0x25 && v <= 0x32) {
        if (v == 0x25) {
            startEffect42();
        }
        Effect_SetPosition(effect42, &carPos, 0, 0);
        if (v == 0x32) {
            stopEffect42();
        }
    }
}

void KappnTaxi::stopEffect42() {
    Effect_End(effect42);
}

BOOL KappnTaxi::setTaxiState(s32 idx) {
    static BOOL (KappnTaxi::*tbl[17])() = {
        &KappnTaxi::enterTaxiIdle, &KappnTaxi::enterTaxiArrive,
        &KappnTaxi::enterTaxiDoorOpen, &KappnTaxi::enterTaxiPlayerGetOut,
        &KappnTaxi::enterTaxiTalk, &KappnTaxi::enterTaxiTalkWait,
        &KappnTaxi::enterTaxiDepart, &KappnTaxi::enterTaxiWaitPlayerWalk,
        &KappnTaxi::enterTaxiEnterTownHall, &KappnTaxi::enterTaxiWarpTownHall,
        &KappnTaxi::enterTaxiLeave, &KappnTaxi::enterTaxiPlayerExitTownHall,
        &KappnTaxi::enterTaxiLeaveDoorOpen, &KappnTaxi::enterTaxiLeaveDoorAnim,
        &KappnTaxi::enterTaxiPlayerGetIn, &KappnTaxi::enterTaxiLeaveDrive,
        &KappnTaxi::enterTaxiLeaveEnd,
    };
    if (idx < 0x11) {
        if ((this->*tbl[idx])()) {
            taxiState = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void KappnTaxi::updateTaxiState() {
    static void (KappnTaxi::*tbl[17])() = {
        &KappnTaxi::execTaxiIdle, &KappnTaxi::execTaxiArrive,
        &KappnTaxi::execTaxiDoorOpen, &KappnTaxi::execTaxiPlayerGetOut,
        &KappnTaxi::execTaxiTalk, &KappnTaxi::execTaxiTalkWait,
        &KappnTaxi::execTaxiDepart, &KappnTaxi::execTaxiWaitPlayerWalk,
        &KappnTaxi::execTaxiEnterTownHall, &KappnTaxi::execTaxiWarpTownHall,
        &KappnTaxi::execTaxiLeave, &KappnTaxi::execTaxiPlayerExitTownHall,
        &KappnTaxi::execTaxiLeaveDoorOpen, &KappnTaxi::execTaxiLeaveDoorAnim,
        &KappnTaxi::execTaxiPlayerGetIn, &KappnTaxi::execTaxiLeaveDrive,
        &KappnTaxi::execTaxiLeaveEnd,
    };
    if (taxiState < 0x11) {
        (this->*tbl[taxiState])();
    }
}

extern "C" {
s16 sKappnTaxiLeaveTimer;
}

BOOL KappnTaxi::enterTaxiIdle() {
    static_cast<BlendAnimModel *>(&model)->initAnim(getDoorInAnim(), 1, 0x1000, 0, 0);
    return TRUE;
}

void KappnTaxi::execTaxiIdle() {
}

BOOL KappnTaxi::enterTaxiArrive() {
    static_cast<BlendAnimModel *>(&model)->initAnim(getDoorInAnim(), 1, 0x1000, 0, 0);
    TalkRequestFlags_SetSceneHold();
    return TRUE;
}

void KappnTaxi::execTaxiArrive() {
    if (PlayerActor_GetActor(4)) {
        setTaxiState(2);
    }
}

BOOL KappnTaxi::enterTaxiDoorOpen() {
    static_cast<BlendAnimModel *>(&model)->initAnim(getDoorInAnim(), 1, 0x1000, 0, 0);
    return TRUE;
}

void KappnTaxi::execTaxiDoorOpen() {
    seEmitter.playSeHeld(0x888);
    if (model.isFinished()) {
        setTaxiState(3);
    }
    updateEffect41();
    model.stepAnim();
}

BOOL KappnTaxi::enterTaxiPlayerGetOut() {
    getOutFrameCount = 0;
    if (KappnTaxi_RequestPlayerGetOut()) {
        static_cast<BlendAnimModel *>(&model)->initAnim(getDoorOutAnim(), 1, 0x1000, 0, 0);
        seEmitter.playSe(0x88a);
        return TRUE;
    }
    return FALSE;
}

void KappnTaxi::execTaxiPlayerGetOut() {
    if (model.isFinished()) {
        switch (getOutFrameCount) {
        case 0x12:
            PlayerActor_KeepAnimForNextAction();
            PlayerActor_RequestTurnTo(getAngleToPlayer(), 4);
            break;
        case 0x1c:
            setTaxiState(4);
            break;
        }
        if (getOutFrameCount < 0xc8) {
            getOutFrameCount++;
        }
    } else {
        model.stepAnim();
    }
}

BOOL KappnTaxi::enterTaxiTalk() {
    TalkWindowState *rec = TalkWindow_Get(0);
    this->TalkMsgRequest::resetMsg();
    this->setFileName("sp_etc_sequence4");
    BOOL r;
    PlayerData *c = PlayerData_GetCurrent();
    if (c != NULL && ((PlayerId *)c->getPlayerId())->getGender() == 1) {
        r = TRUE;
    } else {
        r = FALSE;
    }
    msgIndex = r;
    rec->attachRequest(this);
    rec->nextState = 1;
    KappnNpcIdBuf l;
    MsgString9B o;
    l.npcId = 0xd014;
    Npc_GetName(&o, &l.npcId);
    this->setSpeakerName(o.data(), 0);
    return TRUE;
}

void KappnTaxi::execTaxiTalk() {
    setTaxiState(5);
}

BOOL KappnTaxi::enterTaxiTalkWait() {
    return TRUE;
}

void KappnTaxi::execTaxiTalkWait() {
    TalkWindowState *r = TalkWindow_Get(0);
    u32 t = r->state;
    if (t == 0) {
        r->detachRequest();
        setTaxiState(6);
    }
}

BOOL KappnTaxi::enterTaxiDepart() {
    void *r1 = callGetBca2Anim();
    static_cast<BlendAnimModel *>(&model)->initAnim(r1, 1, 0x1000, 0, 0);
    seEmitter.playSe(0x88b);
    departFrameCount = 0;
    return TRUE;
}

void KappnTaxi::execTaxiDepart() {
    seEmitter.playSeHeld(0x889);
    updateEffect42();
    if (model.isFinished() != 0) {
        setTaxiState(7);
    } else {
        model.stepAnim();
        PlayerActor *o = (PlayerActor *)PlayerActor_GetActor(4);
        if (o != NULL) {
            s32 r4 = o->rotY;
            if (Math_AngleDiffAbs(r4, getAngleToPlayer()) < 0x1200) {
                PlayerActor_SetHeadTilt(0, (s16)(getAngleToPlayer() - r4), 4);
            } else {
                if (departFrameCount < 0xc8) {
                    departFrameCount = departFrameCount + 1;
                }
                if (departFrameCount == 0x10) {
                    BuildingActor *q = (BuildingActor *)Shared_BuildingList_FindByItem(0x5000);
                    if (q != NULL) {
                        s16 doorAngle;
                        VecFx32 door;
                        if (q->getDoorPos(&door, &doorAngle) != 0) {
                            townHallWalkTarget.x = door.x;
                            townHallWalkTarget.y = door.y;
                            townHallWalkTarget.z = door.z;
                            townHallWalkTarget.z += 0x200;
                            PlayerActor_SetHeadTilt(0, 0, 4);
                            PlayerActor_RequestWalkTo(&townHallWalkTarget, 0x400, 4);
                        }
                    }
                }
            }
        }
    }
}

BOOL KappnTaxi::enterTaxiWaitPlayerWalk() {
    return TRUE;
}

void KappnTaxi::execTaxiWaitPlayerWalk() {
    if (PlayerActor_IsScriptedWalking(4) == 0) {
        setTaxiState(8);
    }
}

BOOL KappnTaxi::enterTaxiEnterTownHall() {
    if (PlayerActor_LocalRequestDoorEnter(1, &townHallWalkTarget.x, &townHallWalkTarget.z, -0x8000) != 0) {
        return TRUE;
    }
    return FALSE;
}

void KappnTaxi::execTaxiEnterTownHall() {
    BuildingActor *q = (BuildingActor *)Shared_BuildingList_FindByItem(0x5000);
    if (q != NULL) {
        q->openDoorForEntry();
        townHallGridX = q->getGridX();
        townHallGridZ = q->getGridZ();
        setTaxiState(9);
    }
}

BOOL KappnTaxi::enterTaxiWarpTownHall() {
    warpDelayTimer = 0x14;
    return TRUE;
}

void KappnTaxi::execTaxiWarpTownHall() {
    VecFx32 v;
    s16 sv;
    if (warpDelayTimer != 0) {
        warpDelayTimer = warpDelayTimer - (TICK_STEP_ENDS() ? 1 : 0);
    }
    if (warpDelayTimer == 0) {
        BuildingActor *q = (BuildingActor *)Shared_BuildingList_FindByItem(0x5000);
        if (q != NULL) {
            if (q->getDoorPos(&v, &sv) != 0) {
                SceneWarp_RequestExit(Scene_GetWarpRequest(), 9);
                v.z = v.z + 0x1000;
                Scene_SetTownReturnPos(0, Scene_GetCurrent(), &v, 0xf000000, (s16)(sv + 0x8000), townHallGridX, townHallGridZ);
                TalkRequestFlags_ClearSceneHold();
            }
        }
    }
}

BOOL KappnTaxi::enterTaxiLeave() {
    TalkRequestFlags_SetSceneHold();
    Field_SetDoorExitMode(1);
    return TRUE;
}

void KappnTaxi::execTaxiLeave() {
    setTaxiState(0xb);
}

BOOL KappnTaxi::enterTaxiPlayerExitTownHall() {
    BuildingActor *q = (BuildingActor *)Shared_BuildingList_FindByItem(0x5000);
    if (q != NULL) {
        exitWalkDelay = 0x10;
        return q->openDoorForExit();
    }
    return TRUE;
}

void KappnTaxi::execTaxiPlayerExitTownHall() {
    BuildingActor *q = (BuildingActor *)Shared_BuildingList_FindByItem(0x5000);
    if (q != NULL) {
        if (q->isDoorIdle() != 0) {
            PlayerActor *o = (PlayerActor *)PlayerActor_GetActor(4);
            if (o != NULL) {
                if (exitWalkDelay == 0) {
                    VecFx32Ctor v;
                    VecFx32 *pv = &o->position;
                    v.x = pv->x;
                    v.y = pv->y;
                    v.z = pv->z;
                    v.z = v.z + 0x4000;
                    if (PlayerActor_RequestWalkTo(&v, 0x400, 4) != 0) {
                        setTaxiState(0xc);
                    }
                }
            }
            if (exitWalkDelay != 0) {
                exitWalkDelay = exitWalkDelay - (TICK_STEP_ENDS() ? 1 : 0);
            }
        }
    }
}

BOOL KappnTaxi::enterTaxiLeaveDoorOpen() {
    void *r1 = getDoorInAnim();
    static_cast<BlendAnimModel *>(&model)->initAnim(r1, 1, 0x1000, 0, 0);
    return TRUE;
}

void KappnTaxi::execTaxiLeaveDoorOpen() {
    seEmitter.playSeHeld(0x888);
    if (model.isFinished() != 0) {
        setTaxiState(0xd);
    }
    updateEffect41();
    model.stepAnim();
    PlayerActor *o = (PlayerActor *)PlayerActor_GetActor(4);
    if (o != NULL) {
        s32 r4 = o->rotY;
        if (Math_AngleDiffAbs(r4, getAngleToPlayer()) < 0x1200) {
            PlayerActor_SetHeadTilt(0, (s16)(getAngleToPlayer() - r4), 4);
        }
    }
}

BOOL KappnTaxi::enterTaxiLeaveDoorAnim() {
    void *r1 = getDoorOutAnim();
    static_cast<BlendAnimModel *>(&model)->initAnim(r1, 1, 0x1000, 0, 0);
    seEmitter.playSe(0x88a);
    return TRUE;
}

void KappnTaxi::execTaxiLeaveDoorAnim() {
    if (model.isFinished() != 0) {
        setTaxiState(0xe);
    }
    model.stepAnim();
}

BOOL KappnTaxi::enterTaxiPlayerGetIn() {
    getInTimer = 0x1e;
    if (KappnTaxi_RequestPlayerGetIn() != 0) {
        return TRUE;
    }
    return FALSE;
}

void KappnTaxi::execTaxiPlayerGetIn() {
    if (getInTimer == 0) {
        setTaxiState(0xf);
    }
    if (getInTimer != 0) {
        PlayerActor_SetHeadTilt(0, 0, 4);
        getInTimer = getInTimer - (TICK_STEP_ENDS() ? 1 : 0);
    }
    model.stepAnim();
}

BOOL KappnTaxi::enterTaxiLeaveDrive() {
    void *r1 = callGetBca2Anim();
    static_cast<BlendAnimModel *>(&model)->initAnim(r1, 1, 0x1000, 0, 0);
    seEmitter.playSe(0x88b);
    return TRUE;
}

void KappnTaxi::execTaxiLeaveDrive() {
    seEmitter.playSeHeld(0x889);
    if (model.isFinished() != 0) {
        setTaxiState(0x10);
    }
    updateEffect42();
    model.stepAnim();
}

BOOL KappnTaxi::enterTaxiLeaveEnd() {
    sKappnTaxiLeaveTimer = 0x41;
    return TRUE;
}

void KappnTaxi::execTaxiLeaveEnd() {
    if (sKappnTaxiLeaveTimer == 0) {
        TalkRequestFlags_ClearSceneHold();
        SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2c, 2, 2);
        PlayerData_GetCurrent()->reset();
        gSaveData.resetPlayer(PlayerData_GetCurrentIndex());
    }
    if (sKappnTaxiLeaveTimer >= 0) {
        sKappnTaxiLeaveTimer = sKappnTaxiLeaveTimer - (TICK_STEP_ENDS() ? 1 : 0);
    }
}

extern "C" s32 KappnTaxi_RequestPlayerGetOut() {
    PlayerActor *p = PlayerActor_Get(4);
    if (p != 0) {
        p->actionPriority = ((Unk_02007694 *)p)->getActionDonePriority(p->action);
        return p->requestTaxiGetOut(6, -1);
    }
    return 0;
}

extern "C" s32 KappnTaxi_RequestPlayerGetIn() {
    PlayerActor *p = PlayerActor_Get(4);
    if (p != 0) {
        p->actionPriority = ((Unk_02007694 *)p)->getActionDonePriority(p->action);
        return p->requestTaxiGetIn(6, -1);
    }
    return 0;
}

s32 PlayerActor::requestTaxiGetOut(s32 a, s32 b) {
    PlayerActionRequest m;
    m.assign(0x87, a, b);
    return pushRequest(&m);
}

void PlayerActor::setupTaxiGetOut() {
    ClockDateTime w = {};
    startAnimOnce(0x82, 0, 0);
    rotY = 0;
    clearActionFlag(0);
    PlayerData *r4 = (PlayerData *)PlayerActor_GetPlayerData(this);
    if (r4 != NULL) {
        Unk_0200f17c_Date bits;
        Clock_GetDateTime(&w);
        DateTime_SubDays(&w, 1);
        bits.a = w.year;
        bits.b = w.month;
        bits.c = w.day;
        PlayerActor_SetLastPlayDate(this, r4, &bits);
    }
}

void PlayerActor::netTaxiGetOut() {
}

void PlayerActor::endTaxiGetOut() {
    position.x = position.x + 0x1c00;
    position.z = position.z - 0x2c00;
    rotY = rotY + 0x8000;
}

void PlayerActor::mainTaxiGetOutAnim() {
    advanceAnim();
    if (bodyModel.hasPassedFrame(0x16) != 0) {
        playFootstepSe();
    }
}

void PlayerActor::mainTaxiGetOutFinish() {
    if (bodyModel.isFinished() != 0) {
        actionPriority = ((Unk_02007694 *)this)->getActionDonePriority(action);
        requestAct10(0, 5, -1);
        *(u8 *)PlayerSession_GetSessionFlags() = 0;
    }
}

void PlayerActor::mainTaxiGetOut() {
    mainTaxiGetOutAnim();
    mainTaxiGetOutFinish();
}

s32 PlayerActor::requestTaxiGetIn(s32 a, s32 b) {
    PlayerActionRequest m;
    m.assign(0x88, a, b);
    return pushRequest(&m);
}

void PlayerActor::setupTaxiGetIn() {
    startAnimOnce(0x83, 3, 0);
    rotY = 0;
}

void PlayerActor::netTaxiGetIn() {
}

void PlayerActor::endTaxiGetIn() {
    position.x = position.x - 0x1c00;
    position.z = position.z + 0x2c00;
    rotY = rotY + 0x8000;
}

void PlayerActor::mainTaxiGetInAnim() {
    advanceAnim();
    if (bodyModel.hasPassedFrame(8) != 0) {
        playFootstepSe();
    }
}

void PlayerActor::mainTaxiGetInFinish() {
    if (bodyModel.isFinished() != 0) {
        actionPriority = ((Unk_02007694 *)this)->getActionDonePriority(action);
        requestAct01(9, -1);
    }
}

void PlayerActor::mainTaxiGetIn() {
    mainTaxiGetInAnim();
    mainTaxiGetInFinish();
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0226a794) {
    HOST_OVERLAY_VAR(data_ov068_02271090),
    HOST_OVERLAY_VAR(data_ov068_02271098),
    HOST_OVERLAY_VAR(data_ov068_022710a4),
    HOST_OVERLAY_VAR(data_ov068_022710a0),
    HOST_OVERLAY_VAR(data_ov068_02271094),
    HOST_OVERLAY_VAR(data_ov068_0227109c),
    HOST_OVERLAY_VAR(sKappnTaxiProfile),
    HOST_OVERLAY_VAR(sKappnTaxiLeaveTimer),
    HOST_OVERLAY_VARS_END
};

#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"


#include "types.h"
#include "actor/ActorProfile.h"
#include "talk/TalkTopicMsg.h"
#include "net/CommManager.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/ChoiceList.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "gfx/JointBlend.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveAnimSet.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/PlayerSpNpcRecord.h"
#include "snd/BgmBeatPhase.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02089fbc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov004/unk_ov004_0221c01c.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov004/unk_ov004_022264a0.h"


class ActorTalkRequest;
















struct Unk_ov004_0224d0a0_Bits {
    u32 lo : 12;
    u32 mid : 16;
    u32 hi : 4;
};

class SpNpcBrewster;
class SpNpcBrewsterTalk;

typedef void (SpNpcBrewsterTalk::*Unk_ov004_0224d010_Fn)();
typedef BOOL (SpNpcBrewster::*Unk_ov004_0224d0a0_Fn)();

struct SpNpcBrewsterTalkScript {
    Unk_ov004_0224d010_Fn fn;
    u8 flag;
    u8 pad[3];
};

struct SpNpcBrewsterActEntry {
    Unk_ov004_0224d0a0_Fn fn1;
    Unk_ov004_0224d0a0_Fn fn2;
};


extern "C" {
extern CommManager *gCommManager;
extern s32 data_020c6d1c;
extern u16 data_020c6cc8;
extern VecFx32 gVec3Zero;
extern SpNpcBrewsterTalkScript sSpNpcBrewsterTalkScripts[];
extern SpNpcBrewsterActEntry sSpNpcBrewsterActTable[];
extern const u32 data_ov004_02240120[];
extern const u32 sSpNpcBrewsterGuestSpawnPos[];

void Camera_UnmuteSe();
s32 Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
s32 SpNpcRoostGuest_GetGuest(void *p);
void TalkRequest_SetTargetDone(void *p);
void TalkRequest_AddPlayerTalk7(void *p, s32 a);
void Model_GetJointWorldMtx(void *p, void *q, s32 n);
s32 Math_IsInRange(s32 a, s32 b, s32 c);
}

class SpNpcBrewsterTalk : public ActorTalkRequest {
public:
    SpNpcBrewsterTalk();
    virtual ~SpNpcBrewsterTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void onWindowClose();
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void runScript03();
    void runDrinkScript();
    void runCoffeeScript();
    void setScript(s32 v);
    void attachOwner(SpNpcBrewster *v);

    /* 0xac */ s32 scriptIndex;
    /* 0xb0 */ SpNpcBrewster *owner;
    /* 0xb4 */ u8 scriptStep;
    /* 0xb5 */ u8 useMsg30;
    /* 0xb6 */ u8 pad_b6[2];
};

class SpNpcBrewster : public SpNpcActor {
public:
    SpNpcBrewster() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 idx, u8 v);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct07();
    BOOL setupAct07();
    BOOL mainAct06();
    BOOL setupAct06();
    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 idx);

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcBrewsterTalk talk;
    /* 0x710 */ s16 homeAngle;
    /* 0x712 */ u8 pad_712[2];
    /* 0x714 */ u8 jointMtxE[0x30];
    /* 0x744 */ u8 jointMtxB[0x30];
    /* 0x774 */ s32 lookAtTimer;
    /* 0x778 */ u16 scriptFrame;
    /* 0x77a */ u8 beatSyncStarted;
    /* 0x77b */ u8 pad_77b;
};


extern "C" SpNpcBrewster *SpNpcBrewster_Create() { return new SpNpcBrewster; }

BOOL SpNpcBrewster::preCreate() {
    if (SpNpcActor::preCreate() == 0) {
        return FALSE;
    }
    setTalkRequest(&talk);
    talk.attachOwner(this);
    setCollisionRadius(0x100);
    setInteractionRange(0x5000);
    moveCtrl.setSpeedPreset(2, 0x166, 0xcc, 0x133);
    moveAnimSet.setStandAnim(0xf2);
    moveAnimSet.setWalkAnim(0xf4);
    moveAnimSet.setRunAnim(0xf4);
    return TRUE;
}

BOOL SpNpcBrewster::onCreate() {
    if (SpNpcActor::onCreate() == 0) {
        return FALSE;
    }
    sSpNpcBrewster = this;
    homeAngle = rotY;
    collider.groups |= 2;
    if (gCommManager->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
        if (NetArea_IsLocalOwner() != 0) {
            changeAct(0);
        } else {
            changeAct(5);
        }
    } else {
        changeAct(0);
    }
    if (gCommManager->isSlotActive(gCommManager->myAid) == 0) {
        Actor::spawn(0x66, 0xd01d, (void *)sSpNpcBrewsterGuestSpawnPos, (void *)data_ov004_02240120, 0);
    }
    return TRUE;
}

BOOL SpNpcBrewster::onDelete() {
    if (SpNpcActor::onDelete() == 0) {
        return FALSE;
    }
    sSpNpcBrewster = 0;
    return TRUE;
}

BOOL SpNpcBrewster::onDraw() {
    if (NpcActor::onDraw() == 0) {
        return FALSE;
    }
    Model_GetJointWorldMtx(&model, jointMtxE, 0xe);
    Model_GetJointWorldMtx(&model, jointMtxB, 0xb);
    CafeCoffeeSet_SyncToBrewster();
    return TRUE;
}

u8 *SpNpcBrewster::getTexturePath() {
    return sSpNpcBrewsterTexturePath;
}

u8 *SpNpcBrewster::getModelPath() {
    return sSpNpcBrewsterModelPath;
}

BOOL SpNpcBrewster::updateAct() {
    BOOL r = FALSE;
    s32 i = act;
    if (sSpNpcBrewsterActTable[i].fn2 != 0) {
        r = (this->*sSpNpcBrewsterActTable[i].fn2)();
    }
    if (Math_IsInRange(Bgm_GetCurrent(), 0x63, 0xab) != 0) {
        if (beatSyncStarted == 0) {
            if ((((u32)model.curFrame << 4) >> 16) != 0) {
                model.JointBlend::start(10);
            }
            beatSyncStarted = 1;
        }
        BgmBeatPhase *q = (BgmBeatPhase *)Snd_GetBeatState();
        if (q != 0) {
            if (q->seqVar2 != 1) {
                model.curFrame = 0;
                model.frameStep = q->loopFrame32;
                model.updateLayers3();
                model.frameStep = 0;
            }
        }
    } else {
        beatSyncStarted = 0;
    }
    return r;
}

void SpNpcBrewster::changeAct(s32 idx) {
    BOOL r = TRUE;
    if (sSpNpcBrewsterActTable[idx].fn1 != 0) {
        r = (this->*sSpNpcBrewsterActTable[idx].fn1)();
    }
    if (r != 0) {
        act = idx;
    }
}

BOOL SpNpcBrewster::setupAct00() {
    lookAtTimer = 0;
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcBrewster::mainAct00() {
    if (lookAtTimer > 0) {
        lookAtTimer++;
        if (lookAtTimer > 0x14) {
            lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
            lookAtTimer = -1;
        }
    } else if (lookAtTimer == 0) {
        if (lookAt.yaw > 0x2000) {
            lookAtTimer = 1;
        }
    }
    if (gCommManager->isOnline() == 0 && *DebugVar_GetPtr(0, 0x4a) == 0) {
        if (PlayerActor_IsInAction(0x27, 4) != 0) {
            TalkRequest_AddPlayerTalk7(this, 0);
        }
    }
    if (homeAngle != rotY) {
        changeAct(3);
        return TRUE;
    }
    return TRUE;
}

BOOL SpNpcBrewster::setupAct01() {
    void *p = talk.getTalkPlayer();
    s32 r = 0;
    lookAt.setTarget(1, r, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    if (p != 0) {
        r = getAngleTo((NpcActor *)p);
    }
    talkCtrl.requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcBrewster::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        if (gCommManager->isOnline() == 0 && *DebugVar_GetPtr(0, 0x4a) == 0) {
            if (PlayerActor_IsInAction(0x28, 4) != 0) {
                PlayerActor_LocalRequestStandUp(2);
            }
            Hud_Show();
        }
        lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcBrewster::setupAct02() {
    return TRUE;
}

BOOL SpNpcBrewster::mainAct02() {
    return TRUE;
}

BOOL SpNpcBrewster::setupAct03() {
    actionCtrl.requestAction(3, 2, 0, 0, 0, homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcBrewster::mainAct03() {
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone() != 0) {
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcBrewster::setupAct04() {
    return TRUE;
}

BOOL SpNpcBrewster::mainAct04() {
    if (PlayerActor_IsInAction(0x28, 4) != 0) {
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcBrewster::setupAct05() {
    lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcBrewster::mainAct05() {
    if (isNetOwner() != 0) {
        s32 a = 4;
        s32 b = 4;
        if (netGetSlots(&a, &b) != 0 && a == (s32)gCommManager->myAid && a == b) {
            netSetSlotsIfOwner(1, gCommManager->myAid, gCommManager->myAid);
            talk.resetMsg();
            Character *r = getPlayerActor(4);
            talk.setTalkPlayer(r);
            changeAct(1);
        } else if (NetArea_IsLocalOwner() != 0 && b == 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcBrewster::setupAct06() {
    lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcBrewster::mainAct06() {
    if (isNetOwner() != 0) {
        s32 a = 4;
        s32 b = 4;
        if (netGetSlots(&a, &b) != 0) {
            if (a == 4) {
                if (NetArea_IsLocalOwner() != 0) {
                    netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    changeAct(0);
                }
            }
        }
    }
    return TRUE;
}

BOOL SpNpcBrewster::setupAct07() {
    return TRUE;
}


BOOL SpNpcBrewster::mainAct07() {
    return TRUE;
}

SpNpcBrewsterTalk::SpNpcBrewsterTalk() {}

SpNpcBrewsterTalk::~SpNpcBrewsterTalk() {}

void SpNpcBrewsterTalk::attachOwner(SpNpcBrewster *v) {
    resetMsg();
    owner = v;
}

void SpNpcBrewsterTalk::start(TalkStartMsg *out) {
    PlayerSpNpcRecord *h = (PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord();
    if (GameStart_IsActive() != 0) {
        out->msgKey = (const char *)sSpNpcBrewsterMsgFiles[1];
        out->msgIndex = 0x1f;
    } else {
        out->msgKey = (const char *)sSpNpcBrewsterMsgFiles[0];
        void *o = Actor::findByProfile(0x66, (Actor *)(0));
        if (gCommManager->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
            out->msgIndex = Random_GlobalBelow(3) + 0x55;
        } else if (Talk_CheckAndSetPlayerFlag(0x17, 0) != 0) {
            if (o != 0 && SpNpcRoostGuest_GetGuest(o) == 7) {
                out->msgIndex = 0x58;
            } else {
                s32 c = h->getCafeVisits() >> 2;
                out->msgIndex = data_ov004_0224cec8[c] + Random_GlobalBelow(3);
            }
        } else if (PlayerActor_IsInAction(0x28, 4) == 0) {
            if (Talk_CheckAndSetPlayerFlag(0x16, 1) == 0) {
                out->msgIndex = h->getCafeVisits() >> 1;
            } else if (o != 0 && SpNpcRoostGuest_GetGuest(o) == 7) {
                out->msgIndex = 0x58;
            } else {
                out->msgIndex = (h->getCafeVisits() >> 2) + 0x49;
            }
        } else {
            if (Talk_CheckAndSetPlayerFlag(0x17, 0) == 0) {
                Hud_Hide();
            }
            out->msgIndex = (h->getCafeVisits() >> 2) + 0x14;
        }
    }
}

void SpNpcBrewsterTalk::onMessageEnd(u32) {
    PlayerSpNpcRecord *h = (PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord();
    TalkWindowState *o = window;
    u8 *d = sSpNpcBrewsterMsgFiles[0];
    u32 r = 0xff;
    if (GameStart_IsActive() == 0) {
        if ((s32)msgIndex >= 0x1c && (s32)msgIndex <= 0x23) {
            if ((u32)h->getCafeVisits() >= 5) {
                if (Random_GlobalBelow(3) == 0) {
                    r = 0x2c;
                    goto next0;
                }
            }
            o->openMode = 0;
            setScript(1);
        }
    next0:
        if (msgIndex != 0x2d && msgIndex != 0x2e) {
            goto next1;
        }
        if (msgIndex == 0x2d) {
            useMsg30 = 1;
        }
        o->openMode = 0;
        setScript(1);
    next1:
        if ((s32)msgIndex >= 0x30 && (s32)msgIndex <= 0x3b) {
            o->openMode = 0;
            setScript(3);
        }
        if (r != 0xff) {
            u8 buf;
            buf = r;
            window->setNextMessage(&buf, d);
        }
    }
}

void SpNpcBrewsterTalk::onChoice(u32) {
    PlayerSpNpcRecord *h = (PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord();
    s32 t = getChoiceList()->getResult();
    u8 *d = sSpNpcBrewsterMsgFiles[0];
    u32 r = 0xff;
    if ((s32)msgIndex >= 0x24 && (s32)msgIndex <= 0x2b) {
        if (t != 0) {
            r = (u8)((h->getCafeVisits() >> 2) + 0x28);
        } else {
            window->openMode = 0;
            setScript(2);
        }
    }
    switch (msgIndex) {
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
        if (t == 0) {
            if (NpcActor_CanPlayerPay(owner, 200) == 0) {
                r = 0x2f;
            } else {
                NpcActor_ChargePlayer(owner, 200);
                r = Random_GlobalBelow(2);
                r = (u8)(r + (((h->getCafeVisits() >> 2) << 1) + 0x1c));
            }
        } else {
            r = (u8)((h->getCafeVisits() >> 2) + 0x18);
        }
        break;
    }
    if (r != 0xff) {
        u8 buf;
        buf = r;
        window->setNextMessage(&buf, d);
    }
}

void SpNpcBrewsterTalk::update() {
    s32 i = scriptIndex;
    if (sSpNpcBrewsterTalkScripts[i].flag != 0) {
        if (sSpNpcBrewsterTalkScripts[i].fn != 0) {
            (this->*sSpNpcBrewsterTalkScripts[i].fn)();
        }
    }
}

void SpNpcBrewsterTalk::onTaskDone(u32) {
    s32 i = scriptIndex;
    if (sSpNpcBrewsterTalkScripts[i].flag == 0) {
        if (sSpNpcBrewsterTalkScripts[i].fn != 0) {
            (this->*sSpNpcBrewsterTalkScripts[i].fn)();
            setScript(0);
        }
    }
}

void SpNpcBrewsterTalk::setScript(s32 v) {
    scriptIndex = v;
    scriptStep = 0;
}

void SpNpcBrewsterTalk::runCoffeeScript() {
    TalkWindowState *r6 = window;
    u8 r7 = (u8)((((PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord())->getCafeVisits() >> 2) + 0x24);
    NpcActionCtrl *r5 = &owner->actionCtrl;
    u8 buf;
    switch (scriptStep) {
    case 0:
        if (r6->state == 5) {
            owner->lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
            r5->requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            scriptStep = 1;
        }
        break;
    case 1:
        if (r5->isActionDone()) {
            r5->requestPlayAnim(1, 0xf6, 1, data_020c6cc8, 0);
            CafeCoffeeSet_SetState03();
            owner->moveAnimSet.setStandAnim(0xf3);
            owner->moveAnimSet.setWalkAnim(0xf5);
            owner->moveAnimSet.setRunAnim(0xf5);
            scriptStep = 2;
            owner->scriptFrame = 0;
        }
        break;
    case 2:
        owner->scriptFrame++;
        if (owner->scriptFrame == 5) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4db, 0x7f, 0);
        }
        if (r5->isActionDone()) {
            owner->moveCtrl.setTurnMode(2);
            r5->requestAction(3, 1, 0, 0, 0, (s16)0x8000, 0, 0, data_020c6cc8, 0);
            CafeCoffeeSet_SetState01();
            scriptStep = 3;
        }
        break;
    case 3:
        if (r5->isActionDone()) {
            r5->requestAction(2, 1, 0x19700, 0x14000, 0, 0, 0, 0, data_020c6cc8, 0);
            scriptStep = 4;
        }
        break;
    case 4:
        if (r5->isActionDone()) {
            owner->moveCtrl.setTurnMode(0);
            r5->requestAction(3, 1, 0, 0, 0, (s16)0xc000, 0, 0, data_020c6cc8, 0);
            scriptStep = 5;
        }
        break;
    case 5:
        if (r5->isActionDone()) {
            r5->requestPlayAnim(1, 0xf7, 1, data_020c6cc8, 0);
            CafeCoffeeSet_SetState04();
            scriptStep = 6;
            owner->scriptFrame = 0;
        }
        break;
    case 6:
        owner->scriptFrame++;
        if (owner->scriptFrame == 0xd) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4dc, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x1e) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4dd, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x46) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4de, 0x7f, 0);
        }
        if (r5->isActionDone()) {
            CafeCoffeeSet_SetState02();
            r5->requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            scriptStep = 7;
        }
        break;
    case 7:
        if (r5->isActionDone()) {
            r5->requestAction(2, 1, 0x19700, 0x15000, 0, 0, 0, 0, data_020c6cc8, 0);
            scriptStep = 8;
        }
        break;
    case 8:
        if (r5->isActionDone()) {
            r5->requestAction(3, 1, 0, 0, 0, (s16)0xc000, 0, 0, data_020c6cc8, 0);
            scriptStep = 9;
        }
        break;
    case 9:
        if (r5->isActionDone()) {
            owner->lookAt.setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
            r5->requestPlayAnim(1, 0xf8, 1, data_020c6cc8, 0);
            CafeCoffeeSet_SetState05();
            scriptStep = 10;
            owner->scriptFrame = 0;
        }
        break;
    case 10:
        owner->scriptFrame++;
        if (owner->scriptFrame == 0xf) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4df, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x1e) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e0, 0x7f, 0);
        }
        if (r5->isActionDone()) {
            buf = r7;
            r6->setNextMessage(&buf, sSpNpcBrewsterMsgFiles[0]);
            r6->nextState = 1;
            setScript(0);
        }
        break;
    }
}

void SpNpcBrewsterTalk::runDrinkScript() {
    TalkWindowState *r6 = window;
    if (r6->state == 5) {
        if (CafeCoffeeSet_GetState() == 5) {
            CafeCoffeeSet_SetState08();
            PlayerActor_LocalRequestDrinkCoffee();
            owner->scriptFrame = 0;
        }
        owner->scriptFrame++;
        if (owner->scriptFrame == 7) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e1, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x14) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e2, 0x7f, 0);
            Bgm_RequestSilence(0x10, 0x14, 0);
        }
        if (owner->scriptFrame == 0x28) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e3, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x46) {
            if (PlayerData_GetCurrent()->getPlayerId()->getGender() == 0) {
                Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e4, 0x7f, 0);
            } else {
                Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e5, 0x7f, 0);
            }
        }
        if (CafeCoffeeSet_IsAnim0BAtFrame9()) {
            u8 r4;
            u8 buf;
            if (useMsg30 != 0) {
                r4 = 0x30;
            } else {
                r4 = (u8)(Random_GlobalBelow(0xb) + 0x31);
            }
            Bgm_ReleasePriority(0x10);
            Bgm_RequestSilence(0xc, 0, 0xa);
            Bgm_Request(0xd, 0x3e, 0x7f, 1);
            buf = r4;
            r6->setNextMessage(&buf, sSpNpcBrewsterMsgFiles[0]);
            r6->nextState = 1;
            Talk_CheckAndSetPlayerFlag(0x17, 1);
            PlayerSpNpcRecord *p = (PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord();
            if (Random_GlobalBelow(0xa) < 5) {
                p->setCafeVisits(p->getCafeVisits() + 1);
            }
            setScript(0);
        }
    }
}

void SpNpcBrewsterTalk::onWindowClose() {
    s32 t = msgIndex;
    if (t >= 0x30 && t <= 0x3b) {
        Bgm_Release(0x3e);
        Bgm_RequestSilence(0xc, 6, 0x1a);
    }
}

void SpNpcBrewsterTalk::runScript03() {
    TalkWindowState *r6 = window;
    u8 r7 = (u8)((((PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord())->getCafeVisits() >> 2) + 0x51);
    NpcActionCtrl *r5 = &owner->actionCtrl;
    u8 buf;
    switch (scriptStep) {
    case 0:
        if (r6->state == 5) {
            PlayerActor_LocalPlayAnim98();
            CafeCoffeeSet_SetState09();
            scriptStep = 1;
            owner->scriptFrame = 0;
        }
        break;
    case 1:
        owner->scriptFrame++;
        if (owner->scriptFrame == 0xf) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e6, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x14) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e7, 0x7f, 0);
        }
        if (CafeCoffeeSet_IsAnim0CDone()) {
            Camera_UnmuteSe();
            owner->lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
            r5->requestPlayAnim(4, 0xf8, 3, data_020c6cc8, 0);
            CafeCoffeeSet_SetState06();
            scriptStep = 2;
            owner->scriptFrame = 0;
        }
        break;
    case 2:
        owner->scriptFrame++;
        if (owner->scriptFrame == 0x12) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e8, 0x7f, 0);
        }
        if (owner->scriptFrame == 0x2d) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4e9, 0x7f, 0);
        }
        if (r5->isActionDone()) {
            CafeCoffeeSet_SetState01();
            r5->requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            scriptStep = 3;
        }
        break;
    case 3:
        if (r5->isActionDone()) {
            r5->requestPlayAnim(1, 0xf6, 3, data_020c6cc8, 0);
            CafeCoffeeSet_SetState07();
            owner->moveAnimSet.setStandAnim(0xf2);
            owner->moveAnimSet.setWalkAnim(0xf4);
            owner->moveAnimSet.setRunAnim(0xf4);
            scriptStep = 4;
            owner->scriptFrame = 0;
        }
        break;
    case 4:
        owner->scriptFrame++;
        if (owner->scriptFrame == 0xa) {
            Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x4ea, 0x7f, 0);
        }
        if (r5->isActionDone()) {
            CafeCoffeeSet_SetState00();
            owner->lookAt.setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
            r5->requestAction(3, 1, 0, 0, 0, (s16)0xc000, 0, 0, data_020c6cc8, 0);
            scriptStep = 5;
        }
        break;
    case 5:
        if (r5->isActionDone()) {
            buf = r7;
            r6->setNextMessage(&buf, sSpNpcBrewsterMsgFiles[0]);
            r6->nextState = 1;
            setScript(0);
            useMsg30 = 0;
        }
        break;
    }
}


BOOL SpNpcBrewster::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcBrewster::onInteractionEvent(u32 cmd, u8 arg) {
    s32 a, b;
    switch (cmd) {
    case 3:
        partnerPlayer = arg;
        if (arg != 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, arg);
            changeAct(7);
        } else if (isNetOwner()) {
            s32 g = gCommManager->myAid;
            netSetSlotsIfOwner(1, g, g);
            changeAct(7);
        }
        break;
    case 1:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            netSetSlotsIfOwner(1, arg, arg);
            changeAct(6);
        } else if (isNetOwner()) {
            CommManager *gl = gCommManager;
            s32 g = gl->myAid;
            netSetSlotsIfOwner(1, g, g);
            ActorTalkRequest *p = &talk;
            p->resetMsg();
            talk.setTalkPlayer(getPlayerActor(4));
            if (gl->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
                changeAct(1);
            } else {
                changeAct(4);
            }
        }
        break;
    case 0:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            netSetSlotsIfOwner(1, arg, arg);
            changeAct(6);
        } else if (isNetOwner()) {
            s32 g = gCommManager->myAid;
            netSetSlotsIfOwner(1, g, g);
            ActorTalkRequest *p = &talk;
            p->resetMsg();
            talk.setTalkPlayer(getPlayerActor(4));
            changeAct(1);
        }
        break;
    case 8:
        if (arg == 4) {
            if (NetArea_IsLocalOwner()) {
                netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                changeAct(3);
            } else {
                netSetSlotsIfOwner(1, 4, gCommManager->myAid);
                changeAct(5);
            }
        }
        break;
    case 4:
        if (netIsTalkLocked() && isNetOwner()) {
            a = 4;
            b = 4;
            if (netGetSlots(&a, &b)) {
                if (arg != 4) {
                    if (arg == b) {
                        goto body;
                    }
                }
                if (arg == 4) {
                body:
                    netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    changeAct(0);
                }
            }
        }
        break;
    case 2:
    case 5:
    case 6:
    case 7:
        break;
    }
    NpcActor::onInteractionEvent(cmd, arg);
}

extern "C" void *SpNpcBrewster_GetJointMtxE() { return &sSpNpcBrewster->jointMtxE; }

extern "C" void *SpNpcBrewster_GetJointMtxB() { return &sSpNpcBrewster->jointMtxB; }

extern "C" u32 SpNpcBrewster_GetAnimFrame() { return ((u32)sSpNpcBrewster->model.curFrame << 4) >> 16; }

extern "C" s32 SpNpcBrewster_GetAnimState() { return sSpNpcBrewster->animCtrl.getAnimId(0); }



extern "C" const u32 data_ov004_02240120[2] = {0x40000000, 0};
extern "C" const u32 sSpNpcBrewsterGuestSpawnPos[3] = {0x15000, 0x1000, 0x13000};
extern "C" u8 data_ov004_0224cec8[4] = {0x08, 0x0b, 0x0e, 0x11};
extern "C" u8 data_ov004_0224cf6c[12] = {'s', 'p', '_', 'n', 'p', 'c', '_', 'c', 'a', 'f', 'e', 0};
extern "C" u8 data_ov004_0224cf78[17] = {'s', 'p', '_', 'e', 't', 'c', '_', 's', 'e', 'q', 'u', 'e', 'n', 'c', 'e', '4', 0};
extern "C" u8 sSpNpcBrewsterModelPath[23] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'p', 'g', 'e', '.', 'n', 's', 'b', 'm', 'd', 0};
extern "C" u8 sSpNpcBrewsterTexturePath[27] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'p', 'g', 'e', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" ActorProfile sSpNpcBrewsterProfile = {(void *(*)())SpNpcBrewster_Create, 0x63, 0x6a, 0, 0x5000, 0x5000, 0x3e800};
extern "C" u8 *sSpNpcBrewsterMsgFiles[2] = {data_ov004_0224cf6c, data_ov004_0224cf78};
typedef SpNpcBrewster SNB;
extern "C" SpNpcBrewsterTalkScript sSpNpcBrewsterTalkScripts[4] = {
    {0, 0},
    {&SpNpcBrewsterTalk::runCoffeeScript, 1},
    {&SpNpcBrewsterTalk::runDrinkScript, 1},
    {&SpNpcBrewsterTalk::runScript03, 1},
};
extern "C" SpNpcBrewsterActEntry sSpNpcBrewsterActTable[8] = {
    {&SNB::setupAct00, &SNB::mainAct00},
    {&SNB::setupAct01, &SNB::mainAct01},
    {&SNB::setupAct02, &SNB::mainAct02},
    {&SNB::setupAct03, &SNB::mainAct03},
    {&SNB::setupAct04, &SNB::mainAct04},
    {&SNB::setupAct05, &SNB::mainAct05},
    {&SNB::setupAct06, &SNB::mainAct06},
    {&SNB::setupAct07, &SNB::mainAct07},
};
extern "C" SpNpcBrewster *sSpNpcBrewster = 0;

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221c01c) {
    HOST_OVERLAY_VAR(data_ov004_0224cec8),
    HOST_OVERLAY_VAR(data_ov004_0224cf6c),
    HOST_OVERLAY_VAR(data_ov004_0224cf78),
    HOST_OVERLAY_VAR(sSpNpcBrewsterModelPath),
    HOST_OVERLAY_VAR(sSpNpcBrewsterTexturePath),
    HOST_OVERLAY_VAR(sSpNpcBrewsterProfile),
    HOST_OVERLAY_VAR(sSpNpcBrewsterMsgFiles),
    HOST_OVERLAY_VAR(sSpNpcBrewsterTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcBrewsterActTable),
    HOST_OVERLAY_VAR(sSpNpcBrewster),
    HOST_OVERLAY_VARS_END
};

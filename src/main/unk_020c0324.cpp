#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "net/CommManager.h"
#include "gfx/Mtx43.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "talk/TalkWindowState.h"
#include "snd/SndSeEmitterKind1.h"
#include "actor/NpcActor.h"
#include "actor/ActorFollowCollider.h"
#include "actor/SpNpcActor.h"
#include "talk/SpNpcTalkRequest.h"
#include "talk/SpNpcKatieTalk.h"
#include "npc/SpNpcKatie.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcFaceAnim.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveAnimSet.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcTalkCtrl.h"
#include "player/PlayerData.h"
#include "save/LostChildRecord.h"
#include "talk/ChoiceList.h"
#include "town/KatieVisitState.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020b7190.h"
#include "proto/main/unk_020c0324.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_0204cc1c.h"


class SpNpcKatie;

extern "C" {
s32 Scene_GetCurrent(void);
s32 Scene_GetPrevious(void);
BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
void TalkRequest_SetTargetDone(void *a);
void TalkRequestFlags_ClearSceneHold(void);
void TalkRequestFlags_SetSceneHold(void);
BOOL TownMap_FindBuildingAbovePos(VecFx32 *a, s32 b, s32 c, s32 d);
void TownMap_IsPosWalkable(VecFx32 *a, s32 b);
s32 Vec_DistXZ(void *a, void *b);
BOOL Math_CountDownU16(void *a);
void Camera_SetMode19(void);
extern u16 data_020c6cc8;
extern u32 data_020c6d1c;
extern u8 gVec3Zero[];
extern CommManager *gCommManager;
}
void SpNpcKaitlin_ChangeAct04(void);
void SpNpcKaitlin_ChangeAct06(void);
static inline BOOL Unk_020c06a0_IsMode2() {
    return gScreenTransition.state == 2;
}















typedef BOOL (SpNpcKatie::*SpNpcKatieActFn)();
struct SpNpcKatieActEntry {
    SpNpcKatieActFn setup;
    SpNpcKatieActFn main;
};


extern SpNpcKatieActEntry sSpNpcKatieActTable[9];
extern SpNpcKatie *sSpNpcKatieInstance;
extern char sSpNpcKatieKey[16];
extern char sSpNpcKatieModelPath[23];
extern char sSpNpcKatieTexPath[27];
extern char *sSpNpcKatieMsgKey;
extern const VecFx32 sSpNpcKatieReunionWalkPos;
extern "C" SpNpcKatie *SpNpcKatie_Create(void);

extern "C" SpNpcKatie *SpNpcKatie_Create(void) {
    return new SpNpcKatie();
}

BOOL SpNpcKatie::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    ((NpcActor *)(this))->setTalkRequest((ActorTalkRequest *)(&talk));
    talk.attachOwner(this);
    ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(2, 0x333, 0xcc, 0x133);
    ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(1, 0x1b3, 0xcc, 0x133);
    if (Scene_GetCurrent() == 0xb) {
        rotY = -0x8000;
        moveAngleY = -0x8000;
    }
    if (Scene_GetCurrent() == 0xc) {
        rotY = -0x8000;
        moveAngleY = -0x8000;
    }
    if (Scene_GetCurrent() == 0x2f) {
        rotY = 0;
        moveAngleY = 0;
        position.x = 0xe000;
        position.z = 0x4000;
        ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(1, 0x280, 0xcc, 0x133);
    }
    netSyncOff = 1;
    return TRUE;
}

BOOL SpNpcKatie::onCreate() {
    void *p;
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    sSpNpcKatieInstance = this;
    effectHandle = -1;
    p = PlayerData_GetCurrent();
    if (Scene_GetCurrent() == 0) {
        FieldPos_SnapToUnitCenter((VecFx32 *)&position, (VecFx32 *)&position);
        if (TownMap_FindBuildingAbovePos((VecFx32 *)&position, 1, 0, 0)) {
            TownMap_IsPosWalkable((VecFx32 *)&position, 0);
            position.x += 0x2000;
            position.z += 0x2000;
        }
        if (TownSessionState_GetKatieState(TownSessionState_Get())->isFollowing() != 0) {
            if (Scene_GetPrevious() == 0xb) {
                Town_FindGateHouse(TownBlockMap_Get(), &position, NULL, NULL);
                position.z -= 0x2000;
                talk.setTopic(3);
                changeAct(5);
                collisionEnabled = 0;
            } else {
                talk.setTopic(5);
                changeAct(1);
            }
        } else if (((PlayerData *)(p))->testFlag(0x33) == 0) {
            if (((PlayerData *)(p))->testFlag(0x31) == 0) {
                talk.setTopic(0);
            } else {
                talk.setTopic(1);
            }
            changeAct(1);
        } else {
            if (Talk_CheckAndSetPlayerFlag(0x29, 0) == 0) {
                talk.setTopic(2);
            } else {
                talk.setTopic(3);
            }
            changeAct(1);
        }
    } else if (Scene_GetCurrent() == 0xb) {
        talk.setTopic(3);
        changeAct(5);
        collisionEnabled = 0;
    } else if (Scene_GetCurrent() == 0xc) {
        TownSessionState_GetKatieState(TownSessionState_Get())->getPos(&position);
        talk.setTopic(3);
        changeAct(5);
    } else if (Scene_GetCurrent() == 0x2f) {
        collisionEnabled = 0;
        TalkRequestFlags_SetSceneHold();
        changeAct(8);
    }
    return TRUE;
}

BOOL SpNpcKatie::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    sSpNpcKatieInstance = NULL;
    if (Scene_GetCurrent() == 0x2f) {
        TalkRequestFlags_ClearSceneHold();
    }
    return TRUE;
}

u8 *SpNpcKatie::getTexturePath() {
    return (u8 *)sSpNpcKatieTexPath;
}

u8 *SpNpcKatie::getModelPath() {
    return (u8 *)sSpNpcKatieModelPath;
}

BOOL SpNpcKatie::updateAct() {
    s32 r = 0;
    if (sSpNpcKatieActTable[act].main != 0) {
        r = (this->*(sSpNpcKatieActTable[act].main))();
    }
    if (Scene_GetCurrent() == 0) {
        TownSessionState_GetKatieState(TownSessionState_Get())->setPos(&position);
    }
    if (Scene_GetCurrent() == 0xb) {
        if (((LostChildRecord *)(PlayerData_GetCurrent()->getLostChildRecord()))->isEscorting()) {
            TownSessionState_GetKatieState(TownSessionState_Get())->setPos(&position);
        }
    }
    return r;
}

BOOL SpNpcKatie::acceptsInteraction(void *) {
    return ((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0;
}

void SpNpcKatie::onInteractionEvent(u32 state, u8) {
    switch (state) {
    case 0:
    case 1:
        talk.resetMsg();
        ((ActorTalkRequest *)(&talk))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        if (talk.getTopic() != 6) {
            changeAct(3);
        }
        break;
    case 8:
        talk.setTopic(3);
        if (TownSessionState_GetKatieState(TownSessionState_Get())->isFollowing() != 0) {
            changeAct(5);
        } else if (escortDeclined != 0) {
            changeAct(2);
        } else {
            changeAct(0);
        }
        break;
    }
}

void SpNpcKatie::changeAct(s32 state) {
    BOOL result = TRUE;
    SpNpcKatieActEntry *e = &sSpNpcKatieActTable[state];
    if (e->setup != 0) {
        result = (this->*(e->setup))();
    }
    if (result) {
        if (state != 1 && effectHandle != -1) {
            Effect_End(effectHandle);
            effectHandle = -1;
        }
        act = state;
    }
}

BOOL SpNpcKatie::setupAct00() {
    collider.groups |= 2;
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcKatie::mainAct00() {
    return TRUE;
}

BOOL SpNpcKatie::setupAct01() {
    VecFx32 a, b;
    collider.groups |= 2;
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0x53, 1, data_020c6cc8, 0);
    Town_FindGateHouse(TownBlockMap_Get(), &a, NULL, NULL);
    FieldPos_SnapToUnitCenter(&b, (VecFx32 *)&position);
    if (b.z < a.z) {
        if (b.x >= a.x - 0x4000 && b.x <= a.x + 0x4000) {
            position.z = a.z + 0x1000;
        }
    }
    collisionEnabled = 1;
    return TRUE;
}

BOOL SpNpcKatie::mainAct01() {
    if (((NpcAnimCtrl *)(&animCtrl))->isPlayingAnim(0x53, &moveAnimSet) && ((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
        ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0x54);
        ((NpcMoveAnimSet *)(&moveAnimSet))->setWalkAnim(0x54);
    }
    if (effectHandle == -1) {
        effectHandle = Effect_Create(0x54, &jointPos[0], &rotY, 0);
    }
    if (effectHandle != -1) {
        Effect_SetPosition(effectHandle, &jointPos[0], &rotY, 0);
    }
    return TRUE;
}

BOOL SpNpcKatie::setupAct02() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xab, 1, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcKatie::mainAct02() {
    collider.groups |= 2;
    if (((NpcAnimCtrl *)(&animCtrl))->isPlayingAnim(0xab, &moveAnimSet) && ((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
        ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0xac);
        ((NpcMoveAnimSet *)(&moveAnimSet))->setWalkAnim(0xac);
    }
    return TRUE;
}

BOOL SpNpcKatie::setupAct03() {
    s32 r4;
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
    Character *p = talk.getTalkPlayer();
    r4 = 0;
    if (p != NULL) {
        r4 = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0xac);
    ((NpcMoveAnimSet *)(&moveAnimSet))->setWalkAnim(0xac);
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r4, 0);
    return TRUE;
}

BOOL SpNpcKatie::mainAct03() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(7);
    }
    return TRUE;
}

BOOL SpNpcKatie::setupAct07() {
    return TRUE;
}

BOOL SpNpcKatie::mainAct07() {
    return TRUE;
}

BOOL SpNpcKatie::setupAct04() {
    collider.groups &= ~2;
    waitTimer = 0x28;
    return TRUE;
}

BOOL SpNpcKatie::mainAct04() {
    if (Math_CountDownU16(&waitTimer) == 0) {
        changeAct(5);
    }
    return TRUE;
}

BOOL SpNpcKatie::setupAct05() {
    collider.groups &= ~2;
    stuckTimer = 0x28;
    prevPos = *(VecFx32 *)&position;
    return TRUE;
}

BOOL SpNpcKatie::mainAct05() {
    VecFx32 a, b, c, d;
    void *p = PlayerData_GetCurrent();
    void *q;
    s32 t;
    if (p == NULL) {
        return TRUE;
    }
    if (collisionEnabled == 0 && Scene_GetCurrent() == 0) {
        Town_FindGateHouse(TownBlockMap_Get(), &a, NULL, NULL);
        FieldPos_SnapToUnitCenter(&b, (VecFx32 *)&position);
        if (b.z > a.z) {
            collisionEnabled = 1;
        }
    }
    if (collisionEnabled == 0 && Scene_GetCurrent() == 0xb) {
        FieldPos_SnapToUnitCenter(&d, (VecFx32 *)&position);
        FieldPos_FromUnitCenter(&c, 6, 15);
        if (d.z < c.z) {
            collisionEnabled = 1;
        }
    }
    q = PlayerActor_GetBodyPos(4);
    if (q == NULL) {
        return TRUE;
    }
    t = ((NpcActor *)(this))->getDistanceToPlayer(4);
    if ((Scene_GetCurrent() == 0 || (Scene_GetCurrent() == 0xc && ((LostChildRecord *)(((PlayerData *)(p))->getLostChildRecord()))->isEscorting() == 0)) && ((NpcActionCtrl *)(&actionCtrl))->getAction() == 2) {
        s32 v, d2;
        if (t > 0x6000) {
            changeAct(6);
            return TRUE;
        }
        v = ((NpcLookAt *)(&obstacleProbe))->getObstacleBits();
        d2 = Vec_DistXZ(&prevPos, &position);
        prevPos = *(VecFx32 *)&position;
        if (d2 <= 0x29 || v != 0) {
            if (Math_CountDownU16(&stuckTimer) == 0) {
                changeAct(1);
                return TRUE;
            }
        } else {
            stuckTimer = 0x28;
        }
    }
    if (t > 0x2800) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() != 2) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(2, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
        ((NpcMoveCtrl *)(&moveCtrl))->setWaypoint((VecFx32 *)(q));
    } else if (((NpcActionCtrl *)(&actionCtrl))->getAction() != 0) {
        ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    }
    return TRUE;
}

BOOL SpNpcKatie::setupAct06() {
    if (Scene_GetCurrent() == 0) {
        TownSessionState_GetKatieState(TownSessionState_Get())->clearFollowing();
    }
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0x122, 1, data_020c6cc8, 0);
    talk.setTopic(4);
    Snd_SeEmitterPlayOneShot(&seEmitter, 0x7db, 0x7f, 0);
    return TRUE;
}

BOOL SpNpcKatie::mainAct06() {
    VecFx32 v;
    s16 a;
    if (((NpcAnimCtrl *)(&animCtrl))->isPlayingAnim(0x122, &moveAnimSet)) {
        a = rotY;
        VecFx32 *src = (VecFx32 *)&position;
        v = *src;
        if ((((u32)model.curFrame << 4) >> 16) == 7) {
            Effect_Create(0x39, &v, &a, 0);
        }
        if ((((u32)model.curFrame << 4) >> 16) == 9) {
            Effect_Create(0x38, &v, &a, 0);
        }
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0x123, 1, data_020c6cc8, 0);
        }
    }
    if (((NpcAnimCtrl *)(&animCtrl))->isPlayingAnim(0x123, &moveAnimSet)) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(1);
        }
    }
    return TRUE;
}

BOOL SpNpcKatie::setupAct08() {
    reunionStep = 0;
    return TRUE;
}

BOOL SpNpcKatie::mainAct08() {
    u8 buf;
    VecFx32 vec24;
    VecFx32Ctor vec30;
    s32 r5 = Net_GetJoiningAid();
    CommManager *r7 = gCommManager;
    s32 r6 = r7->localSlot;
    PlayerData *s = PlayerData_GetBySessionSlot(r5);
    switch (reunionStep) {
    case 0:
        if (Unk_020c06a0_IsMode2()) {
            if (PlayerActor_SetNetFollowPaused(1, r5)) {
                reunionStep = 1;
            }
        }
        break;
    case 1:
        static_cast<VecFx32 &>(vec30) = sSpNpcKatieReunionWalkPos;
        PlayerActor_RequestWalkTo(&vec30, 0x35c, r5);
        ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0xe000, 0x10800, 0, 0, 0, 0, data_020c6cc8, 0);
        reunionStep = 2;
        break;
    case 2:
        if (PlayerActor_IsScriptedWalking(r5)) {
            break;
        }
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            reunionStep = 3;
            talk.setTopic(6);
            ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            ((NpcTalkCtrl *)(&talkCtrl))->requestTalk(0, 1);
        }
        break;
    case 3:
        if (talk.window->state == 5) {
            ((TalkWindowState *)(talk.window))->lockAdvance();
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(2, 2, 0xea00, 0x12e00, 0, 0, 0, 0, data_020c6cc8, 0);
            SpNpcKaitlin_ChangeAct04();
            Camera_SetMode19();
            reunionStep = 4;
        }
        break;
    case 4:
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, (VecFx32 *)(gVec3Zero), 4, data_020c6d1c, 1);
            NpcActor *t = NpcRegistry_FindSpNpc(0x23);
            if (t) {
                ((ActorTalkRequest *)(&talk))->setPartnerActor(t);
            }
            buf = 10;
            talk.window->setNextMessage(&buf, sSpNpcKatieMsgKey);
            talk.window->nextState = 1;
            ((TalkWindowState *)(talk.window))->unlockAdvance();
            reunionStep = 5;
        }
        break;
    case 5:
        if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
            vec24.x = 0xde00;
            vec24.y = 0;
            vec24.z = 0x13a00;
            s32 t = Math_AngleXZ(&position, &vec24);
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, t, 0, 0, data_020c6cc8, 0);
            reunionStep = 6;
        }
        break;
    case 6:
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0xde00, 0x13a00, 0, 0, 0, 0, data_020c6cc8, 0);
            PlayerActor_RequestTurnTo(0, r5);
            SpNpcKaitlin_ChangeAct06();
            reunionStep = 7;
        }
        break;
    case 7:
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            reunionStep = 8;
        }
        break;
    case 8:
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(1, 1, 0xf000, 0x1d000, 0, 0, 0, 0, data_020c6cc8, 0);
            reunionStep = 9;
        }
        break;
    case 9:
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            if (r5 != r6 && !SaveManager_IsSessionJoined()) {
                FieldInfoBalloon_ShowPleaseWait();
                break;
            }
            reunionStep = 10;
        }
        break;
    case 10:
        if ((r7)->isMyAid(0)) {
            LostChildRecord *x = static_cast<LostChildRecord *>(PlayerData_GetCurrent()->getLostChildRecord());
            if (x->isKaitlinRole() == 1) {
                x->clear();
            }
            PlayerData_GetCurrent()->setFlag(0x39);
            ((LostChildRecord *)(s->getLostChildRecord()))->clear();
            TownSessionState_GetKatieState(TownSessionState_Get())->clear();
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 1);
        }
        if (r5 == r6) {
            ((LostChildRecord *)(PlayerData_GetCurrent()->getLostChildRecord()))->clear();
            TownSessionState_GetKatieState(TownSessionState_Get())->clear();
            PlayerData_GetCurrent()->setFlag(0x31);
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        } else {
            SceneWarp_RequestExit(Scene_GetWarpRequest(), 1);
        }
        reunionStep = 11;
        break;
    }
    return TRUE;
}

SpNpcKatieTalk::SpNpcKatieTalk() {}

SpNpcKatieTalk::~SpNpcKatieTalk() {}

void SpNpcKatieTalk::attachOwner(SpNpcKatie *owner) {
    resetMsg();
    katie = owner;
}

void SpNpcKatieTalk::setTopic(s32 v) {
    topic = v;
}

s32 SpNpcKatieTalk::getTopic() {
    return topic;
}

void SpNpcKatieTalk::onEventTag(u32 p) {
    ((NpcMoveAnimSet *)(&katie->moveAnimSet))->setStandAnim(0);
    ((NpcMoveAnimSet *)(&katie->moveAnimSet))->setWalkAnim(1);
    ((ActorTalkRequest *)(this))->ActorTalkRequest::onEventTag(p);
}

void SpNpcKatieTalk::start(TalkStartMsg *out_) {
    TalkStartMsg *out = (TalkStartMsg *)out_;
    void *t = PlayerData_GetCurrent();
    out->msgKey = (const char *)sSpNpcKatieMsgKey;
    switch (getTopic()) {
    case 0:
        ((PlayerData *)(t))->setFlag(0x33);
        out->msgIndex = 0;
        break;
    case 1:
        ((PlayerData *)(t))->setFlag(0x33);
        out->msgIndex = Random_GlobalBelow(3) + 1;
        break;
    case 2:
        out->msgIndex = Random_GlobalBelow(3) + 4;
        Talk_CheckAndSetPlayerFlag(0x29, 1);
        break;
    case 3:
        out->msgIndex = Random_GlobalBelow(3) + 7;
        break;
    case 4:
        out->msgIndex = Random_GlobalBelow(3) + 0x19;
        break;
    case 5:
        out->msgIndex = Random_GlobalBelow(3) + 0x22;
        break;
    case 6:
        out->msgIndex = 0x14;
        break;
    }
    katie->escortDeclined = 0;
}

void SpNpcKatieTalk::onMessageStart(u32) {
    LostChildRecord *a = static_cast<LostChildRecord *>(PlayerData_GetCurrent()->getLostChildRecord());
    ((ActorTalkRequest *)this)->setTownNameSlot(a->getTownId(), 0);
    ((ActorTalkRequest *)this)->setTownNameSlot(a->getTownId(), 1);
}

void SpNpcKatieTalk::onMessageEnd(u32) {
    if (msgIndex == 0x14) {
        window->openMode = 0;
    }
}

void SpNpcKatieTalk::onChoice(u32) {
    switch (msgIndex) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
    case 25: case 26: case 27:
    case 34: case 35: case 36: {
        u8 v[2];
        switch (((ChoiceList *)(((TalkWindowState *)(window))->getChoiceList()))->getResult()) {
        case 0:
            v[0] = Random_GlobalBelow(3) + 0x1c;
            window->setNextMessage(&v[0], sSpNpcKatieMsgKey);
            TownSessionState_GetKatieState(TownSessionState_Get())->setFollowing();
            break;
        case 1:
            v[1] = Random_GlobalBelow(3) + 0x1f;
            window->setNextMessage(&v[1], sSpNpcKatieMsgKey);
            if (Scene_GetCurrent() == 0) {
                TownSessionState_GetKatieState(TownSessionState_Get())->clearFollowing();
            }
            katie->escortDeclined = 1;
            break;
        }
        break;
    }
    case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21:
    case 22: case 23: case 24: case 28: case 29: case 30: case 31: case 32: case 33:
        break;
    }
}

extern "C" BOOL SpNpcKatie_IsIdle() {
    SpNpcKatie *p = sSpNpcKatieInstance;
    if (p) {
        if (((NpcFaceAnim *)(&p->faceAnim))->getMouthAnim() == 0xba && sSpNpcKatieInstance->act == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

extern "C" void SpNpcKatie_ResetAct() {
    SpNpcKatie *p = sSpNpcKatieInstance;
    if (p) {
        if (p->act != 0) {
            p->changeAct(0);
        }
    }
}

extern "C" void SpNpcKatie_ChangeAct05() {
    SpNpcKatie *p = sSpNpcKatieInstance;
    if (p) {
        if (p->act != 5) {
            p->changeAct(5);
        }
    }
}

DebugColor data_021f458c(31, 20, 20, 31);
DebugColor data_021f4580(20, 20, 31, 31);
DebugColor data_021f4584(31, 31, 20, 31);
DebugColor data_021f457c(20, 31, 20, 31);
DebugColor data_021f4590(20, 31, 31, 31);
DebugColor data_021f4588(20, 24, 24, 31);
const VecFx32 sSpNpcKatieReunionWalkPos = { 0x10000, 0, 0x11800 };
SpNpcKatieActEntry sSpNpcKatieActTable[9] = {
    { &SpNpcKatie::setupAct00, &SpNpcKatie::mainAct00 },
    { &SpNpcKatie::setupAct01, &SpNpcKatie::mainAct01 },
    { &SpNpcKatie::setupAct02, &SpNpcKatie::mainAct02 },
    { &SpNpcKatie::setupAct03, &SpNpcKatie::mainAct03 },
    { &SpNpcKatie::setupAct04, &SpNpcKatie::mainAct04 },
    { &SpNpcKatie::setupAct05, &SpNpcKatie::mainAct05 },
    { &SpNpcKatie::setupAct06, &SpNpcKatie::mainAct06 },
    { &SpNpcKatie::setupAct07, &SpNpcKatie::mainAct07 },
    { &SpNpcKatie::setupAct08, &SpNpcKatie::mainAct08 },
};
SpNpcKatie *sSpNpcKatieInstance;
char sSpNpcKatieKey[] = "sp_npc_missing1";
char *sSpNpcKatieMsgKey = sSpNpcKatieKey;
char sSpNpcKatieTexPath[] = "npc_sp/model/los_tex.nsbtx";
char sSpNpcKatieModelPath[] = "npc_sp/model/los.nsbmd";
ActorProfile sSpNpcKatieProfile = {(void *(*)())SpNpcKatie_Create, 0x7e, 0x82, 2, 0x5000, 0x5000, 0x3e800};

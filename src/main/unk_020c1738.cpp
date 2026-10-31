#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "snd/SndSeEmitterKind1.h"
#include "actor/NpcActor.h"
#include "actor/ActorFollowCollider.h"
#include "actor/SpNpcActor.h"
#include "talk/SpNpcTalkRequest.h"
#include "game/Unk_0201acf8.h"
#include "player/PlayerData.h"
#include "game/Random.h"
#include "save/LostChildRecord.h"

#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020c1738.h"
#include "proto/main/unk_0204cc1c.h"

extern "C" {
s32 Scene_GetCurrent(void);
s32 func_01ffcb0c(s32 a, s32 b);
u8 Math_CountDownU8(u8 *p);
u32 Random_Next(u32 *seed);
s32 TownMap_IsPosWalkable(void *v, s32 a);
s32 Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
BOOL TalkRequest_SetTargetDone(void *p);
extern u16 data_020c6cc8;
extern u32 data_020c6d1c;
extern void *gCamera;
extern VecFx32 gCameraLookAt;
extern s16 data_02135f44[];
extern s32 data_020c6cf0;
}




class SpNpcKaitlinTalk : public SpNpcTalkRequest {
public:
    SpNpcKaitlinTalk();
    virtual ~SpNpcKaitlinTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    s32 getTopic();
    void setTopic(s32 v);
    void attachOwner(void *p);

    void *owner;
    s32 topic;
};



class SpNpcKaitlin;
typedef BOOL (SpNpcKaitlin::*SpNpcKaitlinActFn)();
struct SpNpcKaitlinActEntry {
    SpNpcKaitlinActFn setup;
    SpNpcKaitlinActFn main;
};

class SpNpcKaitlin : public SpNpcActor {
public:
    SpNpcKaitlin() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual ~SpNpcKaitlin() {}
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual void onJoinTalk();
    virtual void onLeaveTalk();
    virtual BOOL getWalkAnimSpeedScale();

    BOOL mainAct08();
    BOOL setupAct08();
    BOOL mainAct07();
    BOOL tryAvoidObstacle();
    BOOL avoidObstacle();
    BOOL findSidestepPos(VecFx32 *out, VecFx32 *offset);
    BOOL findRandomWalkTarget(s32 *px, s32 *pz);
    BOOL isInCameraView();
    BOOL isInViewBox(VecFx32 *a, VecFx32 *b);
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
    BOOL mainAct09();
    BOOL setupAct09();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    s32 act;
    SpNpcKaitlinTalk talk;
    u32 unk_70c;
};


extern SpNpcKaitlinActEntry sSpNpcKaitlinActTable[10];
extern SpNpcKaitlin *sSpNpcKaitlinInstance;
extern FxVec3 data_021f4658[2];
extern char sSpNpcKaitlinKey[16];
extern char sSpNpcKaitlinModelPath[23];
extern char sSpNpcKaitlinTexPath[27];
extern const char *sSpNpcKaitlinMsgKey;
extern "C" SpNpcKaitlin *SpNpcKaitlin_Create();
void SpNpcKaitlin_ChangeAct06();
void SpNpcKaitlin_ChangeAct04();

extern "C" SpNpcKaitlin *SpNpcKaitlin_Create() {
    return new SpNpcKaitlin();
}

BOOL SpNpcKaitlin::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    sSpNpcKaitlinInstance = this;
    ((NpcActor *)(this))->setTalkRequest((ActorTalkRequest *)(&talk));
    talk.attachOwner(this);
    if (Scene_GetCurrent()) {
        ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(2, 0x333, 0xcc, 0x133);
        ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(1, 0x280, 0xcc, 0x133);
    }
    netSyncOff = 1;
    return TRUE;
}

BOOL SpNpcKaitlin::getWalkAnimSpeedScale() {
    if (Scene_GetCurrent()) {
        return SpNpcActor::getWalkAnimSpeedScale();
    }
    return data_020c6cf0;
}

BOOL SpNpcKaitlin::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    PlayerData_GetCurrent();
    changeAct(0);
    if (Scene_GetCurrent() == 0x2f) {
        collisionEnabled = 0;
        lookAt.setTarget(0, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
        position.x = 0x10000;
        position.z = 0x16800;
    }
    return TRUE;
}

BOOL SpNpcKaitlin::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    sSpNpcKaitlinInstance = NULL;
    return TRUE;
}

void SpNpcKaitlin_ChangeAct04() {
    if (sSpNpcKaitlinInstance != NULL) {
        sSpNpcKaitlinInstance->changeAct(4);
    }
}

void SpNpcKaitlin_ChangeAct06() {
    if (sSpNpcKaitlinInstance != NULL) {
        sSpNpcKaitlinInstance->changeAct(6);
    }
}

u8 *SpNpcKaitlin::getTexturePath() {
    return (u8 *)sSpNpcKaitlinTexPath;
}

u8 *SpNpcKaitlin::getModelPath() {
    return (u8 *)sSpNpcKaitlinModelPath;
}

BOOL SpNpcKaitlin::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcKaitlinActTable[act].main != NULL) {
        result = (this->*sSpNpcKaitlinActTable[act].main)();
    }
    return result;
}

BOOL SpNpcKaitlin::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        return TRUE;
    }
    return FALSE;
}

void SpNpcKaitlin::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        changeAct(1);
        break;
    case 0:
        changeAct(1);
        break;
    case 3:
        talk.resetMsg();
        talk.setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
        changeAct(9);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

void SpNpcKaitlin::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcKaitlinActTable[state].setup != NULL) {
        ok = (this->*sSpNpcKaitlinActTable[state].setup)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcKaitlin::setupAct00() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct00() {
    if (Scene_GetCurrent() == 0) {
        changeAct(7);
    }
    return TRUE;
}

BOOL SpNpcKaitlin::setupAct01() {
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct01() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcKaitlin::setupAct09() {
    u32 x;
    void *p = talk.getTalkPlayer();
    x = 0;
    if (p != NULL) {
        x = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct09() {
    return TRUE;
}

BOOL SpNpcKaitlin::setupAct02() {
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct02() {
    return TRUE;
}

void SpNpcKaitlin::onJoinTalk() {
    changeAct(3);
}

void SpNpcKaitlin::onLeaveTalk() {
    lookAt.setTarget(1, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    changeAct(0);
}

BOOL SpNpcKaitlin::setupAct03() {
    return setupAct00();
}

BOOL SpNpcKaitlin::mainAct03() {
    return TRUE;
}

BOOL SpNpcKaitlin::setupAct04() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(2, 2, 0xf400, 0x14600, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct04() {
    if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 2) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 2, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    return TRUE;
}

BOOL SpNpcKaitlin::setupAct05() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 2, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcMoveCtrl *)(&moveCtrl))->setTurnMode(2);
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct05() {
    if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 2, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    return TRUE;
}

BOOL SpNpcKaitlin::setupAct06() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(4, 2, 0x10000, 0x1d000, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct06() {
    if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
        if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1) {
            ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 2, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    }
    return TRUE;
}

SpNpcKaitlinTalk::SpNpcKaitlinTalk() {}

SpNpcKaitlinTalk::~SpNpcKaitlinTalk() {}

void SpNpcKaitlinTalk::attachOwner(void *p) {
    resetMsg();
    owner = p;
}

void SpNpcKaitlinTalk::setTopic(s32 v) {
    topic = v;
}

s32 SpNpcKaitlinTalk::getTopic() {
    return topic;
}

void SpNpcKaitlinTalk::start(TalkStartMsg *outp) {
    TalkStartMsg *out = (TalkStartMsg *)outp;
    void *p = PlayerData_GetCurrent();
    out->msgKey = sSpNpcKaitlinMsgKey;
    if (((PlayerData *)(p))->testFlag(0x33) == 0) {
        if (((PlayerData *)(p))->testFlag(0x39) == 0) {
            setTopic(0);
        } else {
            setTopic(1);
        }
    } else {
        if (Talk_CheckAndSetPlayerFlag(0x2a, 0) == 0) {
            setTopic(2);
        } else {
            setTopic(3);
        }
    }
    switch (getTopic()) {
    case 0:
        ((PlayerData *)(p))->setFlag(0x33);
        out->msgIndex = 0;
        break;
    case 1:
        ((PlayerData *)(p))->setFlag(0x33);
        out->msgIndex = Random_GlobalBelow(3) + 1;
        break;
    case 2:
        out->msgIndex = Random_GlobalBelow(3) + 4;
        Talk_CheckAndSetPlayerFlag(0x2a, 1);
        break;
    case 3:
        out->msgIndex = Random_GlobalBelow(3) + 7;
        break;
    }
}

void SpNpcKaitlinTalk::onMessageStart(u32) {
    LostChildRecord *r4 = (LostChildRecord *)PlayerData_GetCurrent()->getLostChildRecord();
    ((ActorTalkRequest *)this)->setTownNameSlot(r4->getTownId(), 0);
    ((ActorTalkRequest *)this)->setTownNameSlot(r4->getTownId(), 1);
}

void SpNpcKaitlinTalk::onMessageEnd(u32) {}

void SpNpcKaitlinTalk::onChoice(u32) {}

BOOL SpNpcKaitlin::setupAct07() {
    actCounter = 0;
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    ((NpcFootstepFx *)(&footstepFx))->enableFootsteps();
    lookAt.setTarget(1, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcKaitlin::isInViewBox(VecFx32 *a, VecFx32 *b) {
    BOOL r = FALSE, c = FALSE, d = FALSE;
    s32 x = a->x;
    s32 bx = b->x;
    if (bx > x - 0x10000 && bx < x + 0x10000) {
        d = TRUE;
    }
    if (d) {
        if (b->z > a->z - 0x1a000) {
            c = TRUE;
        }
    }
    if (c) {
        if (b->z < a->z + 0xa000) {
            r = TRUE;
        }
    }
    return r;
}

BOOL SpNpcKaitlin::isInCameraView() {
    VecFx32 *pos = (VecFx32 *)&position;
    s32 r = 0;
    if (gCamera != NULL) {
        VecFx32 v;
        v.x = gCameraLookAt.x;
        v.y = gCameraLookAt.y;
        v.z = gCameraLookAt.z;
        r = isInViewBox(&v, pos);
    }
    return r;
}

BOOL SpNpcKaitlin::findRandomWalkTarget(s32 *px, s32 *pz) {
    s32 *ppx = px;
    s32 *ppz = pz;
    BOOL result = FALSE;
    VecFx32 v;
    s32 i;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    for (i = 0; i < 6; i++) {
        s32 idx = ((u16)(s16)Random_Next(&gRandom.seed) >> 4) * 2;
        s32 m = func_01ffcb0c(0xc000, data_02135f44[idx]);
        v.x = m + position.x;
        m = func_01ffcb0c(0xc000, data_02135f44[idx + 1]);
        v.z = m + position.z;
        FieldPos_SnapToUnitCenter(&v, &v);
        if (TownMap_IsPosWalkable(&v, 0)) {
            *ppx = v.x;
            *ppz = v.z;
            result = TRUE;
            break;
        }
    }
    return result;
}

BOOL SpNpcKaitlin::findSidestepPos(VecFx32 *out, VecFx32 *offset) {
    BOOL result = FALSE;
    VecFx32 v;
    Npc_RotateOffsetXZ(&v, (VecFx32 *)&position, offset, moveAngleY);
    if (Npc_IsPosBlocked(&v) != 1) {
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
        result = TRUE;
    }
    return result;
}

BOOL SpNpcKaitlin::avoidObstacle() {
    void *p564 = &actionCtrl;
    void *p350 = &moveCtrl;
    s32 st = ((NpcLookAt *)(&obstacleProbe))->getObstacleBits();
    BOOL result = FALSE;
    VecFx32 v;
    if (((NpcMoveCtrl *)(p350))->hasArrived((Character *)(this), 1) == 0) {
        switch (st) {
        case 3:
            ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            result = TRUE;
            break;
        case 1:
            if (findSidestepPos(&v, &data_021f4658[1])) {
                ((NpcMoveCtrl *)(p350))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            result = TRUE;
            break;
        case 2:
            if (findSidestepPos(&v, &data_021f4658[0])) {
                ((NpcMoveCtrl *)(p350))->setDestination((VecFx32 *)(&v));
            } else {
                ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
            }
            result = TRUE;
            break;
        }
    } else {
        if (((NpcMoveCtrl *)(p350))->hasNextLeg()) {
            ((NpcMoveCtrl *)(p350))->resetDestination();
        }
    }
    return result;
}

BOOL SpNpcKaitlin::tryAvoidObstacle() {
    if (speed != 0) {
        if (avoidObstacle()) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL SpNpcKaitlin::mainAct07() {
    void *p564 = &actionCtrl;
    BOOL a = isInCameraView();
    Math_CountDownU8(&actCounter);
    if (a) {
        if (!tryAvoidObstacle()) {
            if (((NpcActionCtrl *)(p564))->isActionDone()) {
                if (((Unk_0201acf8 *)(&unk_3aa))->getLevel() == 2) {
                    ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                } else if ((Random_Next(&gRandom.seed) & 7) == 0) {
                    VecFx32 v1;
                    v1.x = gVec3Zero.x;
                    v1.y = gVec3Zero.y;
                    v1.z = gVec3Zero.z;
                    if (findRandomWalkTarget(&v1.x, &v1.z)) {
                        s32 ang = Math_AngleXZ(&position, &v1);
                        if (NpcActor_IsFrontAngle(ang - rotY)) {
                            s32 k = 1;
                            if (Random_GlobalBelow(4) == 0) {
                                k = 2;
                            }
                            if (k != ((NpcActionCtrl *)(&actionCtrl))->getAction()) {
                                ((NpcActionCtrl *)(p564))->requestAction(k, 1, v1.x, v1.z, 0, 0, 0, 0, data_020c6cc8, 0);
                                actCounter = 0x64;
                            }
                        } else {
                            if (((NpcActionCtrl *)(&actionCtrl))->getAction() != 4) {
                                ((NpcActionCtrl *)(p564))->requestAction(4, 1, v1.x, v1.z, 0, ang, 0, 0, data_020c6cc8, 0);
                                actCounter = 0x50;
                            }
                        }
                    } else {
                        ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                    }
                } else {
                    ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                }
            } else {
                if (speed != 0) {
                    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 1 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 2 || ((NpcActionCtrl *)(&actionCtrl))->getAction() == 4) {
                        if (actCounter == 0) {
                            ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                        } else {
                            VecFx32 *src = (VecFx32 *)((NpcMoveCtrl *)(&moveCtrl))->getDestination();
                            VecFx32 v2;
                            v2.x = src->x;
                            v2.y = src->y;
                            v2.z = src->z;
                            s32 ang = Math_AngleXZ(&position, &v2);
                            if (!NpcActor_IsFrontAngle(ang - rotY)) {
                                ((NpcActionCtrl *)(p564))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (speed != 0) {
            changeAct(8);
        }
    }
    return FALSE;
}

BOOL SpNpcKaitlin::setupAct08() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    actCounter = 0;
    ((NpcFootstepFx *)(&footstepFx))->disableFootsteps();
    return TRUE;
}

BOOL SpNpcKaitlin::mainAct08() {
    if (isInCameraView()) {
        changeAct(7);
    }
    return TRUE;
}

DebugColor data_021f4630(31, 20, 20, 31);
DebugColor data_021f463c(20, 20, 31, 31);
DebugColor data_021f4634(31, 31, 20, 31);
DebugColor data_021f4624(20, 31, 20, 31);
DebugColor data_021f4628(20, 31, 31, 31);
DebugColor data_021f462c(20, 24, 24, 31);
SpNpcKaitlinActEntry sSpNpcKaitlinActTable[10] = {
    { &SpNpcKaitlin::setupAct00, &SpNpcKaitlin::mainAct00 },
    { &SpNpcKaitlin::setupAct01, &SpNpcKaitlin::mainAct01 },
    { &SpNpcKaitlin::setupAct02, &SpNpcKaitlin::mainAct02 },
    { &SpNpcKaitlin::setupAct03, &SpNpcKaitlin::mainAct03 },
    { &SpNpcKaitlin::setupAct04, &SpNpcKaitlin::mainAct04 },
    { &SpNpcKaitlin::setupAct05, &SpNpcKaitlin::mainAct05 },
    { &SpNpcKaitlin::setupAct06, &SpNpcKaitlin::mainAct06 },
    { &SpNpcKaitlin::setupAct07, &SpNpcKaitlin::mainAct07 },
    { &SpNpcKaitlin::setupAct08, &SpNpcKaitlin::mainAct08 },
    { &SpNpcKaitlin::setupAct09, &SpNpcKaitlin::mainAct09 },
};
FxVec3 data_021f4658[2] = { FxVec3(0x800, 0, 0x1000), FxVec3(0xfffff800, 0, 0x1000) };
SpNpcKaitlin *sSpNpcKaitlinInstance;
char sSpNpcKaitlinKey[] = "sp_npc_missing2";
const char *sSpNpcKaitlinMsgKey = sSpNpcKaitlinKey;
char sSpNpcKaitlinModelPath[] = "npc_sp/model/mum.nsbmd";
char sSpNpcKaitlinTexPath[] = "npc_sp/model/mum_tex.nsbtx";
ActorProfile sSpNpcKaitlinProfile = {(void *(*)())SpNpcKaitlin_Create, 0x7f, 0x83, 2, 0x5000, 0x5000, 0x3e800};

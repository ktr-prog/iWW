#include "types.h"
#include "actor/ActorProfile.h"
#include "npc/VillagerClothModel.h"
#include "npc/VillagerMood.h"
#include "snd/SndSeEmitter.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcMoveAnimSet.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/NpcFaceAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "talk/TalkTopicMsg.h"
#include "npc/VillagerId.h"
#include "save/VillagerData.h"
#include "proto/main/unk_02063904.h"
#include "proto/ov004/unk_ov004_0221a218.h"

class CafeVillager;

typedef BOOL (CafeVillager::*Unk_ov004_0224c994_Fn)();

struct CafeVillagerActEntry {
    Unk_ov004_0224c994_Fn a;
    Unk_ov004_0224c994_Fn b;
};


extern "C" {
extern u16 data_020c6cc8;
void TalkRequest_SetTargetDone(void *o);
}

class CafeVillagerTalk : public VillagerTalk {
public:
    CafeVillagerTalk();
    virtual ~CafeVillagerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(CafeVillager *owner);

    /* 0x1a0 */ CafeVillager *villager;
};

class CafeVillager : public VillagerActor {
public:
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();

    BOOL mainAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    BOOL mainAct02();
    BOOL setupAct02();
    void changeAct(s32 idx);

    /* 0x894 */ s32 act;
    /* 0x898 */ CafeVillagerTalk talk;
};

extern "C" ActorProfile sCafeVillagerProfile = {(void *(*)())CafeVillager_Create, 0x88, 0x8c, 2, 0x5000, 0x5000, 0x3e800};
extern "C" {
char data_ov004_022508e0[0x28];
}
extern "C" CafeVillagerActEntry sCafeVillagerActTable[3] = {
    {&CafeVillager::setupAct00, &CafeVillager::mainAct00},
    {0, &CafeVillager::mainAct01},
    {&CafeVillager::setupAct02, &CafeVillager::mainAct02}};

extern "C" CafeVillager *CafeVillager_Create() {
    return new CafeVillager;
}

BOOL CafeVillager::preCreate() {
    if (!VillagerActor::preCreate()) {
        return FALSE;
    }
    moveAnimSet.setStandAnim(0x1e);
    moveAnimSet.setWalkAnim(0x1e);
    moveAnimSet.setRunAnim(0x1e);
    setTalkRequest(&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL CafeVillager::onCreate() {
    if (!VillagerActor::onCreate()) {
        return FALSE;
    }
    changeAct(2);
    return TRUE;
}

BOOL CafeVillager::updateAct() {
    BOOL r = FALSE;
    if (sCafeVillagerActTable[act].b) {
        r = (this->*sCafeVillagerActTable[act].b)();
    }
    return r;
}

void CafeVillager::changeAct(s32 idx) {
    BOOL ok = TRUE;
    if (sCafeVillagerActTable[idx].a) {
        ok = (this->*sCafeVillagerActTable[idx].a)();
    }
    if (ok) {
        act = idx;
    }
}

BOOL CafeVillager::setupAct02() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL CafeVillager::mainAct02() { return TRUE; }

BOOL CafeVillager::setupAct00() {
    NpcActor *p = (NpcActor *)talk.getTalkPlayer();
    s32 v = 0;
    if (p) {
        v = getAngleTo(p);
    }
    talkCtrl.requestTurnAndTalk(0, v, 0);
    return TRUE;
}

BOOL CafeVillager::mainAct00() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(1);
    }
    return TRUE;
}

BOOL CafeVillager::mainAct01() { return TRUE; }

CafeVillagerTalk::CafeVillagerTalk() {}

CafeVillagerTalk::~CafeVillagerTalk() {}

void CafeVillagerTalk::attachOwner(CafeVillager *owner) {
    resetMsg();
    begin(owner, 0x11);
    villager = owner;
}

void CafeVillagerTalk::start(TalkStartMsg *arg) {
    TalkTopicMsg *out = (TalkTopicMsg *)arg;
    ((VillagerData *)villager->villagerData)->getVillagerId()->makeFileName(data_ov004_022508e0, 0x28, "ai_shop3");
    out->fileName = data_ov004_022508e0;
    out->msgIndex = Random_GlobalBelow(5);
}

void CafeVillagerTalk::onMessageEnd(u32) {}

void CafeVillagerTalk::onChoice(u32) {}

BOOL CafeVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() == 0) {
        return TRUE;
    }
    return FALSE;
}

void CafeVillager::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(0);
        break;
    case 8:
        changeAct(2);
        break;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221a218) {
    HOST_OVERLAY_VAR(sCafeVillagerProfile),
    HOST_OVERLAY_VAR(data_ov004_022508e0),
    HOST_OVERLAY_VAR(sCafeVillagerActTable),
    HOST_OVERLAY_VARS_END
};

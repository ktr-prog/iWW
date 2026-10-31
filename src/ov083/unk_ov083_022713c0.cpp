#include "types.h"
#include "host_labels.h"
#include "talk/TalkStartMsg.h"
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
#include "actor/ActorProfile.h"
#include "player/PlayerData.h"
#include "player/PlayerSpNpcRecord.h"
#include "save/ContestRecord.h"
#include "save/SaveData.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov083/unk_ov083_022713c0.h"


class ActorTalkRequest;
class SpNpcTortimerFlowerFest;
class SpNpcTortimerFlowerFestTalk;




extern "C" {
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
void TalkRequest_SetTargetDone(void *p);
void NookShop_PickFlowerBag(u16 *p);
void Clock_GetDateTime(ClockDateTime *p);
s32 Event_GetDaysSinceStart(u32 id);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
#define gContestRecord HOST_LABEL(u8 (*)[], gContestRecord)
extern SaveData gSaveData;
}







class SpNpcTortimerFlowerFestTalk : public SpNpcTalkRequest {
public:
    SpNpcTortimerFlowerFestTalk();
    virtual ~SpNpcTortimerFlowerFestTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(SpNpcTortimerFlowerFest *owner);

    SpNpcTortimerFlowerFest *ownerNpc;
    s32 massageChairSlot;
    u16 giftItem;
};








class SpNpcTortimerFlowerFest : public SpNpcActor {
public:
    SpNpcTortimerFlowerFest() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 v, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    s32 tickTimer(s32 *p);
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    s32 judgeTimer;
    s32 act;
    SpNpcTortimerFlowerFestTalk talk;
    u8 festDay;
};

struct SpNpcTortimerFlowerFestActEntry {
    BOOL (SpNpcTortimerFlowerFest::*enter)();
    BOOL (SpNpcTortimerFlowerFest::*exit)();
};

extern "C" {
}

SpNpcTortimerFlowerFestActEntry sSpNpcTortimerFlowerFestActTable[3] = {
    {&SpNpcTortimerFlowerFest::setupAct00, &SpNpcTortimerFlowerFest::mainAct00},
    {&SpNpcTortimerFlowerFest::setupAct01, &SpNpcTortimerFlowerFest::mainAct01},
    {NULL, &SpNpcTortimerFlowerFest::mainAct02},
};

extern "C" u8 sSpNpcTortimerFlowerFestTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'l', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" u8 sSpNpcTortimerFlowerFestModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'l', '.', 'n', 's', 'b', 'm', 'd', 0};

extern "C" ActorProfile sSpNpcTortimerFlowerFestProfile = {(void *(*)())SpNpcTortimerFlowerFest_Create, 0x59, 0x60, 2, 0x5000, 0x5000, 0x3e800};


extern "C" SpNpcTortimerFlowerFest *SpNpcTortimerFlowerFest_Create() {
    return new SpNpcTortimerFlowerFest();
}

BOOL SpNpcTortimerFlowerFest::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcTortimerFlowerFest::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    festDay = Event_GetDaysSinceStart(0xe);
    ContestRecord_BeginFestival((ContestRecord *)gContestRecord, 0);
    return TRUE;
}

u8 *SpNpcTortimerFlowerFest::getTexturePath() { return sSpNpcTortimerFlowerFestTexturePath; }

u8 *SpNpcTortimerFlowerFest::getModelPath() { return sSpNpcTortimerFlowerFestModelPath; }

BOOL SpNpcTortimerFlowerFest::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcTortimerFlowerFestActTable[act].exit != NULL) {
        result = (this->*sSpNpcTortimerFlowerFestActTable[act].exit)();
    }
    return result;
}

void SpNpcTortimerFlowerFest::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimerFlowerFestActTable[state].enter != NULL) {
        ok = (this->*sSpNpcTortimerFlowerFestActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimerFlowerFest::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimerFlowerFest::mainAct00() {
    if (tickTimer(&judgeTimer)) {
        return TRUE;
    }
    judgeTimer = 0x258;
    ContestRecord *const g = (ContestRecord *)gContestRecord;
    ContestRecord_JudgeGardens(g);
    g->setKind(3);
    gSaveData.setFlag(0xf);
    return TRUE;
}

s32 SpNpcTortimerFlowerFest::tickTimer(s32 *p) {
    if (*p != 0) {
        *p = *p - 1;
    }
    return *p;
}

BOOL SpNpcTortimerFlowerFest::setupAct01() {
    Character *p = talk.getTalkPlayer();
    u32 x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcTortimerFlowerFest::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcTortimerFlowerFest::mainAct02() { return TRUE; }

SpNpcTortimerFlowerFestTalk::SpNpcTortimerFlowerFestTalk() : giftItem(0xfff1) {}

SpNpcTortimerFlowerFestTalk::~SpNpcTortimerFlowerFestTalk() {}

void SpNpcTortimerFlowerFestTalk::attachOwner(SpNpcTortimerFlowerFest *owner) {
    resetMsg();
    ownerNpc = owner;
    massageChairSlot = -1;
}

void SpNpcTortimerFlowerFestTalk::start(TalkStartMsg *out) {
    u16 h;
    ClockDateTimeWords w;
    PlayerData_GetCurrent()->getErrands();
    out->msgKey = "sp_npc_turtle3";
    if (massageChairSlot == -1) {
        h = 0x37e0;
        massageChairSlot = Pocket_FindItem(&h);
        if (massageChairSlot >= 0) {
            out->msgKey = "sp_npc_turtle";
            out->msgIndex = 0;
            return;
        }
    }
    w.words[0] = 0;
    w.words[1] = 0;
    Clock_GetDateTime(&w.dt);
    {
        u32 v = w.dt.hour;
        if (v < 6 || v >= 0x12) {
            out->msgIndex = 0;
            return;
        }
    }
    if (!TownSessionState_TestFlag(TownSessionState_Get(), 1)) {
        u32 c;
        TownSessionState_SetFlag(TownSessionState_Get(), 1);
        c = ownerNpc->festDay;
        if (c == 0) {
            out->msgIndex = 1;
        } else if (c >= 1 && c <= 5) {
            out->msgIndex = 2;
        } else {
            out->msgIndex = 3;
        }
    } else {
        out->msgIndex = 0xa;
    }
}

void SpNpcTortimerFlowerFestTalk::onMessageEnd(u32) {
    u8 b1;
    u8 b2;
    u16 h1, h2, h3;
    u8 *s = (u8 *)"sp_npc_turtle3";
    u8 msg = 0xff;
    if (massageChairSlot >= 0) {
        if (msgIndex == 1 || msgIndex == 4) {
            massageChairSlot = -2;
        }
        if (msgIndex == 2) {
            h1 = 0x1559;
            requestGiveItem(&h1, 0, 5, 0);
            h2 = 0x1559;
            Pocket_AddItem(&h2, 0);
            b1 = 4;
            window->setNextMessage(&b1, (void *)"sp_npc_turtle");
        }
    } else {
        if (msgIndex == 5 || msgIndex == 6 || msgIndex == 9) {
            if (!Talk_CheckAndSetPlayerFlag(0x1d, 1)) {
                ((PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord())->setFestivalGift();
                if (Pocket_FindEmpty() >= 0) {
                    msg = 7;
                    NookShop_PickFlowerBag(&h3);
                    giftItem = h3;
                }
            }
        }
        if (msgIndex == 7) {
            requestGiveItem(&giftItem, 0, 5, 0);
            Pocket_AddItem(&giftItem, 0);
            setItemNameSlot(&giftItem, 0, 7);
            msg = 8;
        }
        if (msg != 0xff) {
            b2 = msg;
            window->setNextMessage(&b2, s);
        }
    }
}

void SpNpcTortimerFlowerFestTalk::onChoice(u32) {
    u8 b1;
    u8 b2;
    u16 h;
    s32 t = getChoiceList()->getResult();
    u8 *s = (u8 *)"sp_npc_turtle3";
    u8 msg = 0xff;
    if (massageChairSlot >= 0) {
        s = (u8 *)"sp_npc_turtle";
        if (msgIndex == 0 && t == 0) {
            if (massageChairSlot >= 0) {
                Pocket_RemoveItem(massageChairSlot);
                h = 0x37e0;
                requestTakeItem(&h, 0, 5, 0);
            }
            msg = 2;
        }
        if (msg != 0xff) {
            b1 = msg;
            window->setNextMessage(&b1, s);
        }
    } else {
        if (msgIndex == 0xa && t == 0) {
            if (Random_GlobalBelow(3) == 0) {
                msg = 0xc;
            } else {
                msg = Random_GlobalBelow(0xb) + 0x1c;
            }
        }
        if (msg != 0xff) {
            b2 = msg;
            window->setNextMessage(&b2, s);
        }
    }
}

BOOL SpNpcTortimerFlowerFest::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcTortimerFlowerFest::onInteractionEvent(u32 v, u8) {
    switch (v) {
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov083_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcTortimerFlowerFestActTable),
    HOST_OVERLAY_VAR(sSpNpcTortimerFlowerFestTexturePath),
    HOST_OVERLAY_VAR(sSpNpcTortimerFlowerFestModelPath),
    HOST_OVERLAY_VAR(sSpNpcTortimerFlowerFestProfile),
    HOST_OVERLAY_VARS_END
};

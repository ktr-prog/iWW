#include "types.h"
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
#include "actor/ActorProfile.h"
#include "npc/NpcMoveAnimSet.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "save/SaveData.h"
#include "gfx/ScreenTransition.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209b598.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov051/unk_ov051_02258de0.h"
#include "proto/ov068/unk_ov068_0226b9a8.h"
#include "proto/main/unk_0204cc1c.h"


class SpNpcKappn;
class TownBlockMap;
class SpNpcKappnTalk;
class ActorTalkRequest;

struct KappnFaceStyle {
    u8 hairStyle;
    u8 hairColor;
    u16 shirt;
};



extern "C" {
void Clock_GetDateTime(ClockDateTime *p);
void SaveData_Setup(SaveData *p, u32 idx);
void SaveData_Apply(SaveData *p);
void TalkRequestFlags_ClearSceneHold(void);
void TalkRequestFlags_SetSceneHold(void);
void Camera_SetSwayPattern3(void);
u16 Math_CountDownU16(u16 *p);
u8 Math_CountDownU8(u8 *p);
extern u16 data_020c6cc8;
extern SaveData gSaveData;
extern const KappnFaceStyle data_020d0544[8][2];
extern u8 gTalkMsgIndexEnd[];
}












class SpNpcKappnTalk : public ActorTalkRequest {
public:
    typedef void (SpNpcKappnTalk::*Fn)();
    typedef void (SpNpcKappnTalk::*FnU)(u32);

    SpNpcKappnTalk();
    virtual ~SpNpcKappnTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void onSignalTag(s32 a);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    u8 genderMsg(u32 v);
    void onMoneyChoice(u32 sel);
    void onPurposeChoice(u32 sel);
    void onRainChoice(u32 sel);
    void onVisitPlanChoice(u32 sel);
    void onTownReasonChoice(u32 sel);
    void onGirlNameChoice(u32 sel);
    void onBoyNameChoice(u32 sel);
    void onTownNameConfirmChoice(u32 sel);
    void applyFaceFromAnswers();
    void announceArrival();
    void askMoneyOrArrive();
    void askAfterGirlCorrection();
    void askAfterBoyCorrection();
    void askDestination();
    void askReasonOrMoney();
    void askVisitPlan();
    void openTownNameEntry();
    void openPlayerNameEntry();
    void openClockSetting();
    void onClockSet();
    void onPlayerNameEntered();
    void onTownNameEntered();
    void setResultHandler(s32 idx);
    void attachOwner(SpNpcKappn *owner);

    SpNpcKappn *ownerNpc;
    Fn resultHandler;
    s32 answerBits;
};

struct SpNpcKappnActEntry {
    BOOL (SpNpcKappn::*enter)();
    BOOL (SpNpcKappn::*exit)();
};

class SpNpcKappn : public SpNpcActor {
public:
    SpNpcKappn() : talk() {}

    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual u16 getSpecies();
    virtual u16 getEmotion0BlendFrames();

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
    void changeAct(s32 state);

    s32 act;
    SpNpcKappnTalk talk;
    u16 startDelay;
    u8 animTimer;
    u8 pad_717;
};

extern "C" {
extern const u8 sSpNpcKappnMoneyReplyMsgs[];
extern const u8 sSpNpcKappnPurposeReplyMsgs[];
extern const u8 sSpNpcKappnRainReplyMsgs[];
extern const u8 sSpNpcKappnRainReplyMsgsMode3[];
extern const u32 sSpNpcKappnFaceTable[];
}



extern "C" u8 sSpNpcKappnKey[];
static inline BOOL Unk_ov051_02259a8c_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }
static inline BOOL Unk_ov051_02259b98_IsTwo(u8 v) { return v == 2 ? TRUE : FALSE; }

struct SpNpcKappnChoiceHandler {
    u32 id;
    void (SpNpcKappnTalk::*fn)(u32);
};

struct SpNpcKappnMessageEndHandler {
    u32 id;
    void (SpNpcKappnTalk::*fn)();
};

extern "C" SpNpcKappn *SpNpcKappn_Create() { return new SpNpcKappn; }

BOOL SpNpcKappn::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    moveAnimSet.setStandAnim(0xfb);
    return TRUE;
}

BOOL SpNpcKappn::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    sSpNpcKappnInstance = this;
    changeAct(0);
    collider.groups |= 2;
    TalkRequestFlags_SetSceneHold();
    startDelay = 0x29;
    return TRUE;
}

BOOL SpNpcKappn::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    TalkRequestFlags_ClearSceneHold();
    return TRUE;
}

u8 *SpNpcKappn::getTexturePath() { return sSpNpcKappnTexturePath; }

u8 *SpNpcKappn::getModelPath() { return sSpNpcKappnModelPath; }

BOOL SpNpcKappn::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcKappnActTable[act].exit) {
        r = (this->*sSpNpcKappnActTable[act].exit)();
    }
    if (Math_CountDownU8(&animTimer) == 1) {
        actionCtrl.requestPlayAnim(1, 0x8f, 1, data_020c6cc8, 0);
    }
    return r;
}

void SpNpcKappn::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcKappnActTable[state].enter) {
        ok = (this->*sSpNpcKappnActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

u16 SpNpcKappn::getSpecies() { return 0xffff; }

u16 SpNpcKappn::getEmotion0BlendFrames() { return 10; }

BOOL SpNpcKappn::setupAct00() { return TRUE; }

BOOL SpNpcKappn::mainAct00() {
    if (Unk_ov051_02259b98_IsTwo(gScreenTransition.state)) {
        if (Math_CountDownU16(&startDelay) == 0) {
            changeAct(1);
        }
    }
    return TRUE;
}

BOOL SpNpcKappn::setupAct01() {
    talkCtrl.requestTalk(1, 0);
    return TRUE;
}

BOOL SpNpcKappn::mainAct01() { return TRUE; }

BOOL SpNpcKappn::setupAct02() { return TRUE; }

BOOL SpNpcKappn::mainAct02() { return TRUE; }

BOOL SpNpcKappn::setupAct03() { return TRUE; }

BOOL SpNpcKappn::mainAct03() {
    ClockDateTime now;
    VecFx32 pos;
    if (Unk_ov051_02259a8c_IsZero(gScreenTransition.state)) {
        ScreenTransition_StartFadeIn(3, 0, 1);
        Taxi_SetArriving();
        if (GameStart_IsMode3() || GameStart_IsNewTown()) {
            now = ClockDateTime();
            Clock_GetDateTime(&now);
            MenuCtrl_SetDateTime(&now);
        }
        if (GameStart_IsNewTown()) {
            SaveData_Setup(&gSaveData, 0);
            SaveData_Apply(&gSaveData);
        } else if (GameStart_IsMode3()) {
            SaveData_Setup(&gSaveData, 6);
            SaveData_Apply(&gSaveData);
        } else if (GameStart_IsNewResident()) {
            SaveData_Setup(&gSaveData, 1);
            SaveData_Apply(&gSaveData);
        }
        gSaveData.clearFlag(0x12);
        Town_FindTownHallFront(TownBlockMap_Get(), &pos, NULL, NULL);
        SceneWarp_RequestAt(Scene_GetWarpRequest(), 0, &pos, 0x400000, -0x8000, 3, 2);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcKappn::setupAct04() { return TRUE; }

BOOL SpNpcKappn::mainAct04() {
    if (TalkWindow_Get(0)->state == 0) {
        if (Random_GlobalBelow(4) == 0) {
            TaxiInterior_StartDriverAnim();
            Camera_SetSwayPattern3();
            animTimer = 10;
        }
        ScreenTransition_StartFadeOut(0, 0xf);
        Snd_FadeOutScene();
        changeAct(3);
    }
    return TRUE;
}

SpNpcKappnTalk::SpNpcKappnTalk() {}

SpNpcKappnTalk::~SpNpcKappnTalk() {}

void SpNpcKappnTalk::attachOwner(SpNpcKappn *owner) {
    resetMsg();
    ownerNpc = owner;
}

void SpNpcKappnTalk::onSignalTag(s32 a) {
    if (a == 0) {
        TaxiInterior_StopRain();
    }
}

void SpNpcKappnTalk::start(TalkStartMsg *out) {
    out->msgKey = (const char *)sSpNpcKappnMsgKey;
    if (GameStart_IsNewTown() || GameStart_IsMode3()) {
        out->msgIndex = 0;
    } else {
        out->msgIndex = 0x28;
    }
}

void SpNpcKappnTalk::onTaskDone(u32) {
    if (resultHandler) {
        (this->*resultHandler)();
        resultHandler = NULL;
    }
}



void SpNpcKappnTalk::setResultHandler(s32 idx) {
    static Fn tbl[3] = {
        &SpNpcKappnTalk::onTownNameEntered,
        &SpNpcKappnTalk::onPlayerNameEntered,
        &SpNpcKappnTalk::onClockSet,
    };
    resultHandler = tbl[idx];
}

void SpNpcKappnTalk::onTownNameEntered() {
    u8 m[1];
    m[0] = genderMsg(0x11);
    window->setNextMessage(m, sSpNpcKappnMsgKey);
}

void SpNpcKappnTalk::onPlayerNameEntered() {
    u8 m[2];
    if (MenuCtrl_IsResultDuplicateName()) {
        m[0] = 0x29;
        window->setNextMessage(m, sSpNpcKappnMsgKey);
    } else {
        m[1] = 9;
        window->setNextMessage(&m[1], sSpNpcKappnMsgKey);
    }
}

void SpNpcKappnTalk::onClockSet() {
    u8 m[1];
    m[0] = 2;
    window->setNextMessage(m, sSpNpcKappnMsgKey);
}

void SpNpcKappnTalk::onMessageStart(u32) {
    u8 msg;
    ClockDateTime now;
    if (msgIndex == 0 || msgIndex == 2) {
        TalkWindowState *h = TalkWindow_Get(0);
        s32 r4 = 0x19;
        now = ClockDateTime();
        Clock_GetDateTime(&now);
        if (now.hour >= 0xc) {
            r4 = 0x1a;
        }
        msg = r4;
        h->setSlotFromString(0, &msg, "st_general");
        u32 t = now.hour;
        if (t >= 0xc) {
            t -= 0xc;
        }
        if (t == 0) {
            t = 0xc;
        }
        setNumberSlot(t, 1, 2, 0, 0);
    }
}

void SpNpcKappnTalk::openClockSetting() {
    setSubSceneKind(0x30, 0);
    openSubScene(2);
    setResultHandler(2);
}

void SpNpcKappnTalk::openPlayerNameEntry() {
    setSubSceneKind(0xf, 0);
    openSubScene(2);
    setResultHandler(1);
}

void SpNpcKappnTalk::openTownNameEntry() {
    setSubSceneKind(0x10, 0);
    openSubScene(2);
    setResultHandler(0);
}

void SpNpcKappnTalk::askVisitPlan() {
    u8 m[2];
    if (GameStart_IsMode4()) {
        m[0] = 0x30;
        window->setNextMessage(m, sSpNpcKappnMsgKey);
    }
}

void SpNpcKappnTalk::askReasonOrMoney() {
    u8 m[2];
    if (GameStart_IsNewTown()) {
        m[0] = genderMsg(0x15);
        window->setNextMessage(m, sSpNpcKappnMsgKey);
    } else {
        m[1] = genderMsg(0x1f);
        window->setNextMessage(&m[1], sSpNpcKappnMsgKey);
    }
}

void SpNpcKappnTalk::askDestination() {
    u8 msg;
    msg = genderMsg(0xf);
    window->setNextMessage(&msg, sSpNpcKappnMsgKey);
}

void SpNpcKappnTalk::askAfterBoyCorrection() {
    u8 msg[2];
    if (GameStart_IsNewResident()) {
        msg[0] = 0x19;
        window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
    } else {
        msg[1] = 0xf;
        window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
    }
}

void SpNpcKappnTalk::askAfterGirlCorrection() {
    u8 msg[2];
    if (GameStart_IsNewResident()) {
        msg[0] = 0x1a;
        window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
    } else {
        msg[1] = 0x10;
        window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
    }
}

void SpNpcKappnTalk::askMoneyOrArrive() {
    u8 msg[2];
    if (GameStart_IsMode3()) {
        msg[0] = genderMsg(0x25);
        window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
    } else {
        msg[1] = genderMsg(0x1f);
        window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
    }
}

void SpNpcKappnTalk::announceArrival() {
    u8 msg;
    msg = genderMsg(0x25);
    window->setNextMessage(&msg, sSpNpcKappnMsgKey);
}

void SpNpcKappnTalk::applyFaceFromAnswers() {
    if (GameStart_IsNewResident() || GameStart_IsNewTown()) {
        PlayerData *h = PlayerData_GetCurrent();
        u32 res = h->getPlayerId()->getGender();
        u32 v = sSpNpcKappnFaceTable[ownerNpc->talk.answerBits * 2 + res];
        u32 r1;
        if (res == 0) {
            r1 = (u8)v;
        } else {
            r1 = (u8)(v + 8);
        }
        const KappnFaceStyle *e = &data_020d0544[v][res];
        u16 c;
        h->setFaceType(r1);
        h->setHairColor(e->hairColor);
        h->setHairStyle(e->hairStyle);
        c = e->shirt;
        h->setShirt(&c);
    }
    window->setNextMessage(gTalkMsgIndexEnd, 0);
    ownerNpc->changeAct(4);
}


void SpNpcKappnTalk::onMessageEnd(u32) {
    static SpNpcKappnMessageEndHandler tbl[32] = {
        {0x01, &SpNpcKappnTalk::openClockSetting},
        {0x04, &SpNpcKappnTalk::openClockSetting},
        {0x08, &SpNpcKappnTalk::openPlayerNameEntry},
        {0x0a, &SpNpcKappnTalk::openPlayerNameEntry},
        {0x29, &SpNpcKappnTalk::openPlayerNameEntry},
        {0x0f, &SpNpcKappnTalk::openTownNameEntry},
        {0x10, &SpNpcKappnTalk::openTownNameEntry},
        {0x13, &SpNpcKappnTalk::openTownNameEntry},
        {0x14, &SpNpcKappnTalk::openTownNameEntry},
        {0x25, &SpNpcKappnTalk::applyFaceFromAnswers},
        {0x26, &SpNpcKappnTalk::applyFaceFromAnswers},
        {0x06, &SpNpcKappnTalk::askVisitPlan},
        {0x07, &SpNpcKappnTalk::askVisitPlan},
        {0x1b, &SpNpcKappnTalk::askReasonOrMoney},
        {0x1c, &SpNpcKappnTalk::askReasonOrMoney},
        {0x1d, &SpNpcKappnTalk::askReasonOrMoney},
        {0x1e, &SpNpcKappnTalk::askReasonOrMoney},
        {0x2b, &SpNpcKappnTalk::askDestination},
        {0x2c, &SpNpcKappnTalk::askDestination},
        {0x2d, &SpNpcKappnTalk::askDestination},
        {0x2e, &SpNpcKappnTalk::askDestination},
        {0x0d, &SpNpcKappnTalk::askAfterBoyCorrection},
        {0x0e, &SpNpcKappnTalk::askAfterGirlCorrection},
        {0x17, &SpNpcKappnTalk::askMoneyOrArrive},
        {0x18, &SpNpcKappnTalk::askMoneyOrArrive},
        {0x21, &SpNpcKappnTalk::announceArrival},
        {0x22, &SpNpcKappnTalk::announceArrival},
        {0x23, &SpNpcKappnTalk::announceArrival},
        {0x24, &SpNpcKappnTalk::announceArrival},
        {0x2f, &SpNpcKappnTalk::announceArrival},
        {0x31, &SpNpcKappnTalk::announceArrival},
        {0x32, &SpNpcKappnTalk::announceArrival},
    };
    for (u32 i = 0; i < 0x20; i++) {
        if (tbl[i].id == msgIndex) {
            (this->*tbl[i].fn)();
        }
    }
}

void SpNpcKappnTalk::onTownNameConfirmChoice(u32 sel) {
    u8 msg[3];
    switch (sel) {
    case 0:
        if (GameStart_IsMode3()) {
            msg[0] = genderMsg(0x15);
            window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
        } else {
            msg[1] = genderMsg(0x19);
            window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
        }
        break;
    case 1:
        msg[2] = genderMsg(0x13);
        window->setNextMessage(&msg[2], sSpNpcKappnMsgKey);
        break;
    }
}

void SpNpcKappnTalk::onBoyNameChoice(u32 sel) {
    u8 msg[3];
    switch (sel) {
    case 0:
        PlayerData_GetCurrent()->getPlayerId()->setGender(0);
        if (GameStart_IsNewResident()) {
            msg[0] = genderMsg(0x19);
            window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
        } else {
            msg[1] = genderMsg(0xf);
            window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
        }
        break;
    case 1:
        PlayerData_GetCurrent()->getPlayerId()->setGender(1);
        msg[2] = 0xe;
        window->setNextMessage(&msg[2], sSpNpcKappnMsgKey);
        break;
    }
}

void SpNpcKappnTalk::onGirlNameChoice(u32 sel) {
    u8 msg[3];
    switch (sel) {
    case 0:
        PlayerData_GetCurrent()->getPlayerId()->setGender(1);
        if (GameStart_IsNewResident()) {
            msg[0] = genderMsg(0x19);
            window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
        } else {
            msg[1] = genderMsg(0xf);
            window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
        }
        break;
    case 1:
        PlayerData_GetCurrent()->getPlayerId()->setGender(0);
        msg[2] = 0xd;
        window->setNextMessage(&msg[2], sSpNpcKappnMsgKey);
        break;
    }
}

void SpNpcKappnTalk::onTownReasonChoice(u32 sel) {
    u8 msg;
    msg = genderMsg(0x17);
    window->setNextMessage(&msg, sSpNpcKappnMsgKey);
    Town_SetGenGateMode(sel);
}

void SpNpcKappnTalk::onVisitPlanChoice(u32 sel) {
    u8 msg[2];
    switch (sel) {
    case 0:
        msg[0] = 0x31;
        window->setNextMessage(&msg[0], sSpNpcKappnMsgKey);
        break;
    case 1:
        msg[1] = 0x32;
        window->setNextMessage(&msg[1], sSpNpcKappnMsgKey);
        break;
    }
}

void SpNpcKappnTalk::onRainChoice(u32 sel) {
    u8 msg;
    u32 v;
    if (GameStart_IsMode3()) {
        v = sSpNpcKappnRainReplyMsgsMode3[sel * 2 + PlayerData_GetCurrent()->getPlayerId()->getGender()];
    } else {
        v = sSpNpcKappnRainReplyMsgs[sel];
    }
    msg = v;
    window->setNextMessage(&msg, sSpNpcKappnMsgKey);
    if (sel == 1) {
        ownerNpc->talk.answerBits += 4;
    }
}

void SpNpcKappnTalk::onPurposeChoice(u32 sel) {
    u8 msg;
    msg = genderMsg(sSpNpcKappnPurposeReplyMsgs[sel]);
    window->setNextMessage(&msg, sSpNpcKappnMsgKey);
    if (sel == 1) {
        ownerNpc->talk.answerBits += 2;
    }
}

void SpNpcKappnTalk::onMoneyChoice(u32 sel) {
    u8 msg;
    u32 v;
    if (GameStart_IsNewTown()) {
        v = genderMsg(sSpNpcKappnMoneyReplyMsgs[sel]);
    } else if (sel == 0) {
        if (PlayerData_GetCurrent()->getPlayerId()->getGender() == 0) {
            v = 0x21;
        } else {
            v = 0x2f;
        }
    } else {
        v = genderMsg(0x23);
    }
    msg = v;
    window->setNextMessage(&msg, sSpNpcKappnMsgKey);
    if (sel == 1) {
        ownerNpc->talk.answerBits++;
    }
}

u8 SpNpcKappnTalk::genderMsg(u32 v) {
    u8 r = (u8)PlayerData_GetCurrent()->getPlayerId()->getGender();
    return (u8)(v + r);
}

extern "C" u8 sSpNpcKappnTexturePath[] = "npc_sp/model/wip_tex.nsbtx";
SpNpcKappnActEntry sSpNpcKappnActTable[5] = {
    {&SpNpcKappn::setupAct00, &SpNpcKappn::mainAct00},
    {&SpNpcKappn::setupAct01, &SpNpcKappn::mainAct01},
    {&SpNpcKappn::setupAct02, &SpNpcKappn::mainAct02},
    {&SpNpcKappn::setupAct03, &SpNpcKappn::mainAct03},
    {&SpNpcKappn::setupAct04, &SpNpcKappn::mainAct04},
};
extern "C" u8 sSpNpcKappnModelPath[] = "npc_sp/model/wip.nsbmd";
extern "C" const u8 sSpNpcKappnRainReplyMsgs[4] = {6, 7, 0, 0};
extern "C" const u8 sSpNpcKappnRainReplyMsgsMode3[4] = {0x2b, 0x2c, 0x2d, 0x2e};
extern "C" u8 sSpNpcKappnKey[] = "sp_etc_sequence3";
SpNpcKappn *sSpNpcKappnInstance;
extern "C" ActorProfile sSpNpcKappnProfile = {(void *(*)())SpNpcKappn_Create, 0x7b, 0x7f, 2, 0x5000, 0x5000, 0x3e800};
extern "C" const u8 sSpNpcKappnPurposeReplyMsgs[4] = {0x1d, 0x1b, 0, 0};
extern "C" char *sSpNpcKappnMsgKey = (char *)sSpNpcKappnKey;
extern "C" const u8 sSpNpcKappnMoneyReplyMsgs[4] = {0x21, 0x23, 0, 0};

void SpNpcKappnTalk::onChoice(u32) {
    static SpNpcKappnChoiceHandler tbl[14] = {
        {0x05, &SpNpcKappnTalk::onRainChoice},
        {0x03, &SpNpcKappnTalk::onRainChoice},
        {0x28, &SpNpcKappnTalk::onRainChoice},
        {0x0b, &SpNpcKappnTalk::onGirlNameChoice},
        {0x0c, &SpNpcKappnTalk::onBoyNameChoice},
        {0x15, &SpNpcKappnTalk::onTownReasonChoice},
        {0x16, &SpNpcKappnTalk::onTownReasonChoice},
        {0x19, &SpNpcKappnTalk::onPurposeChoice},
        {0x1a, &SpNpcKappnTalk::onPurposeChoice},
        {0x1f, &SpNpcKappnTalk::onMoneyChoice},
        {0x20, &SpNpcKappnTalk::onMoneyChoice},
        {0x11, &SpNpcKappnTalk::onTownNameConfirmChoice},
        {0x12, &SpNpcKappnTalk::onTownNameConfirmChoice},
        {0x30, &SpNpcKappnTalk::onVisitPlanChoice},
    };
    for (u32 i = 0; i < 0xe; i++) {
        if (tbl[i].id == msgIndex) {
            u32 arg = window->getChoiceList()->getResult();
            (this->*tbl[i].fn)(arg);
        }
    }
}

extern "C" u32 SpNpcKappn_GetAnimFrame() {
    return (u16)(sSpNpcKappnInstance->model.curFrame >> 12);
}


extern "C" s32 SpNpcKappn_GetAnimState() {
    return sSpNpcKappnInstance->animCtrl.getAnimId(0);
}

extern "C" const u32 sSpNpcKappnFaceTable[16] = {4, 6, 5, 5, 1, 0, 0, 1, 6, 4, 3, 2, 2, 7, 7, 3};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov051_02258de0) {
    HOST_OVERLAY_VAR(sSpNpcKappnTexturePath),
    HOST_OVERLAY_VAR(sSpNpcKappnActTable),
    HOST_OVERLAY_VAR(sSpNpcKappnModelPath),
    HOST_OVERLAY_VAR(sSpNpcKappnKey),
    HOST_OVERLAY_VAR(sSpNpcKappnInstance),
    HOST_OVERLAY_VAR(sSpNpcKappnProfile),
    HOST_OVERLAY_VAR(sSpNpcKappnMsgKey),
    HOST_OVERLAY_VARS_END
};

#include "types.h"
#include "proto/main/unk_020b4828.h"
#include "gfx/VecFx32.h"
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
#include "talk/MsgString256.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/ConstellationMsgString17.h"
#include "talk/ChoiceList.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "net/CommManager.h"
#include "npc/NpcLookAt.h"
#include "talk/MsgString.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a8c9c.h"
#include "proto/main/unk_020afeb4.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/ov046/unk_ov046_02258de0.h"


class ActorTalkRequest;
class SpNpcCelesteTalk;
class SpNpcCeleste;
typedef void (SpNpcCelesteTalk::*SpNpcCelesteTalkFn)();
typedef void (SpNpcCelesteTalk::*SpNpcCelesteChoiceFn)(s32);




extern "C" {
extern CommManager *gCommManager;
extern u16 gPad[];
extern u16 data_020c6cc8;
extern s32 data_020c6d1c;
extern VecFx32 gVec3Zero;

BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
void Camera_LockFocusYaw(void);
BOOL TalkRequest_AddPlayerTalk6(Character *c, s32 b);
BOOL TalkRequest_SetTargetDone(Character *c);
s32 Clock_GetTimeOfDay(void);
u16 Math_CountDownU16(u16 *p);
}












struct SpNpcCelesteMessageEndHandler {
    u32 id;
    SpNpcCelesteTalkFn f;
};

struct SpNpcCelesteChoiceHandler {
    u32 id;
    SpNpcCelesteChoiceFn fn;
};

class SpNpcCelesteTalk : public SpNpcTalkRequest {
public:
    SpNpcCelesteTalk();
    virtual ~SpNpcCelesteTalk();
    virtual void resetMsg();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);
    virtual void openConstellationPage();

    void onRenameChoice(s32 a);
    void onLookOrTimesChoice(s32 a);
    void onRemakeChoice(s32 a);
    void onMakeNewOrLeaveChoice(s32 a);
    void onStargazeMenuChoice(s32 a);
    void onMakeOrChangeChoice(s32 a);
    void onEraseConfirmChoice(s32 a);
    void onFullMenuChoice(s32 a);
    void onTelescopeMenuChoice(s32 a);
    void onDiscardNewChoice(s32 a);
    void onMakeNewOrMenuChoice(s32 a);
    void onConstellationListChoice(s32 idx);
    void onViewingTimeChoice(s32 a);
    void startStargazing();
    void startRenameEntry();
    void startNameEntry();
    void showConstellationList();
    void showFollowUpMenu();
    void reactToConstellationName();
    void startConstellationEditor();
    void showTelescopeMenu();
    void announceNewConstellations();
    s32 getFollowUpMenuMsg();
    void setTopic(s32 v);
    void attachOwner(SpNpcCeleste *p);
    void onConstellationRenamed();
    void onConstellationRedrawn();
    void onConstellationNamed();
    void onConstellationDrawn();
    void onStargazingDone();
    void setResultHandler(s32 idx);

    /* 0xac */ s32 topic;
    /* 0xb0 */ SpNpcCeleste *owner;
    /* 0xb4 */ SpNpcCelesteTalkFn resultHandler;
    /* 0xbc */ s32 constellationSlot;
    /* 0xc0 */ u8 listStart;
    /* 0xc1 */ u8 listRemaining;
    /* 0xc2 */ u8 listMode;
    /* 0xc3 */ u8 pad_c3;
    /* 0xc4 */ s32 listSlots[5];
    /* 0xd8 */ s32 nextMsg;
};

class SpNpcCeleste : public SpNpcActor {
public:
    SpNpcCeleste() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL tryStartTelescopeTalk();
    BOOL isPlayerAtTelescope();
    BOOL mainAct04();
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
    SpNpcCelesteTalk talk;
    u16 sleepTimer;
    s16 homeAngle;
    u16 sleepBlend;
    u8 isAsleep;
    u8 pad_73b;
    s32 effectHandle;
};

struct SpNpcCelesteActEntry {
    BOOL (SpNpcCeleste::*enter)();
    BOOL (SpNpcCeleste::*exit)();
};


extern "C" DebugColor data_ov046_0225ae04;
extern "C" DebugColor data_ov046_0225ae08;
extern "C" DebugColor data_ov046_0225ae20;
extern "C" DebugColor data_ov046_0225ae10;
extern "C" DebugColor data_ov046_0225ae00;
extern "C" DebugColor data_ov046_0225ae0c;
extern "C" u8 sSpNpcCelesteModelPath[];
extern "C" u8 sSpNpcCelesteTexturePath[];
extern "C" const TalkStartMsg sSpNpcCelesteTopicMsgs[5];
extern "C" ActorProfile sSpNpcCelesteProfile;
extern "C" u8 sSpNpcCelesteKey[];

static inline BOOL Unk_ov046_02258e68_Both() {
    if (gTouchPrevHeld != 0 && gTouchPrevChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void *SpNpcCeleste_Create() {
    return new SpNpcCeleste();
}

BOOL SpNpcCeleste::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    effectHandle = -1;
    return TRUE;
}

BOOL SpNpcCeleste::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    homeAngle = rotY;
    sleepBlend = 0;
    collider.groups |= 2;
    talk.setTopic(5);
    if (Clock_GetTimeOfDay() == 2 || Clock_GetTimeOfDay() == 3 || gCommManager->isOnline() != 0 ||
        *DebugVar_GetPtr(0, 0x4a) != 0) {
        changeAct(0);
    } else {
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcCeleste::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    if (effectHandle != -1) {
        Effect_End(effectHandle);
        effectHandle = -1;
    }
    return TRUE;
}

u8 *SpNpcCeleste::getTexturePath() { return sSpNpcCelesteTexturePath; }

u8 *SpNpcCeleste::getModelPath() { return sSpNpcCelesteModelPath; }

BOOL SpNpcCeleste::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcCelesteActTable[act].exit) {
        r = (this->*sSpNpcCelesteActTable[act].exit)();
    }
    return r;
}

void SpNpcCeleste::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcCelesteActTable[state].enter) {
        ok = (this->*sSpNpcCelesteActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcCeleste::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    sleepTimer = 0x78;
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcCeleste::mainAct00() {
    if (tryStartTelescopeTalk()) {
        return TRUE;
    }
    if (gCommManager->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0 || Clock_GetTimeOfDay() == 2 ||
        Clock_GetTimeOfDay() == 3) {
        return TRUE;
    }
    if (Math_CountDownU16(&sleepTimer) == 0) {
        sleepBlend = 0x18;
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcCeleste::setupAct01() {
    actionCtrl.requestAction(3, 1, 0, 0, 0, homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcCeleste::mainAct01() {
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcCeleste::setupAct02() {
    actionCtrl.requestPlayAnim(1, 0xf0, 0, sleepBlend, 0);
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    isAsleep = 1;
    return TRUE;
}

BOOL SpNpcCeleste::mainAct02() {
    if (tryStartTelescopeTalk()) {
        return TRUE;
    }
    if (effectHandle == -1) {
        effectHandle = Effect_Create(0x3c, &jointPos[0], &rotY, 0);
    } else {
        Effect_SetPosition(effectHandle, &jointPos[0], &rotY, 0);
    }
    return TRUE;
}

BOOL SpNpcCeleste::setupAct03() {
    NpcActor *p = (NpcActor *)talk.getTalkPlayer();
    s32 r = 0;
    if (p) {
        r = getAngleTo(p);
    }
    if (effectHandle != -1) {
        Effect_End(effectHandle);
        effectHandle = -1;
    }
    talkCtrl.requestTurnAndTalk(0, r, 0);
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcCeleste::mainAct03() {
    if (talkCtrl.isBusy() == 0) {
        isAsleep = 0;
        talk.setTopic(5);
        TalkRequest_SetTargetDone(this);
        changeAct(4);
    }
    return TRUE;
}

BOOL SpNpcCeleste::mainAct04() { return TRUE; }

void SpNpcCelesteTalk::openConstellationPage() {
    TalkWindowState *o = window;
    ChoiceList *r7 = o->getChoiceList();
    u8 v = 0xf;
    r7->clear();
    ConstellationMsgString17 a;
    ConstellationMsgString17 b;
    v = 0x7d;
    String_Load2d(&b, &v, 0);
    s32 i;
    for (i = 0; i < 5; i++) {
        listSlots[i] = -1;
    }
    s32 r6 = listStart;
    s32 r4 = 0;
    for (; r6 < 0x10 && r4 < 4 && listRemaining != 0; r6++) {
        if (Constellation_GetName(&a, r6)) {
            MsgString256 c;
            ChoiceEntry *q = r7->getEntry(r4);
            ((MsgString *)(&c))->appendString((MsgString *)(&a));
            ((MsgString *)(&c))->appendString((MsgString *)(&b));
            ((MsgString *)(q->getText()))->copy((MsgString *)(&c));
            listSlots[r4] = r6;
            r4++;
            listRemaining = listRemaining - 1;
        }
    }
    listStart = r6;
    if (listStart >= 0x10) {
        listStart = 0xf;
    }
    v = 0xf;
    if (listRemaining == 0) {
        v = 0x10;
    }
    ChoiceEntry *p = r7->getEntry(r4);
    p->setMsgIndex(&v);
    p->setBmgName(Choice_GetBmgName(1));
    p->loadText();
    r7->setCount(r4 + 1);
    r7->setCancelToLast();
    window->openChoices(1);
}

void SpNpcCelesteTalk::onTaskDone(u32) {
    if (resultHandler) {
        (this->*resultHandler)();
        resultHandler = NULL;
    }
}

extern "C" DebugColor data_ov046_0225ae04 = DebugColor(31, 20, 20, 31);

extern "C" DebugColor data_ov046_0225ae08 = DebugColor(20, 20, 31, 31);

extern "C" DebugColor data_ov046_0225ae20 = DebugColor(31, 31, 20, 31);

extern "C" DebugColor data_ov046_0225ae10 = DebugColor(20, 31, 20, 31);

extern "C" DebugColor data_ov046_0225ae00 = DebugColor(20, 31, 31, 31);

extern "C" DebugColor data_ov046_0225ae0c = DebugColor(20, 24, 24, 31);

extern "C" u8 sSpNpcCelesteModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'o', 'w', 's', '.', 'n', 's', 'b', 'm', 'd', 0};

extern "C" u8 sSpNpcCelesteTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'o', 'w', 's', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};

extern "C" const TalkStartMsg sSpNpcCelesteTopicMsgs[5] = {
    {(const char *)sSpNpcCelesteKey, 0},
    {(const char *)sSpNpcCelesteKey, 0x2c},
    {(const char *)sSpNpcCelesteKey, 0x2d},
    {(const char *)sSpNpcCelesteKey, 0x2e},
    {(const char *)sSpNpcCelesteKey, 4},
};

extern "C" ActorProfile sSpNpcCelesteProfile = {(void *(*)())SpNpcCeleste_Create, 0x6d, 0x73, 2, 0x5000, 0x5000, 0x3e800};

SpNpcCelesteActEntry sSpNpcCelesteActTable[5] = {
    {&SpNpcCeleste::setupAct00, &SpNpcCeleste::mainAct00},
    {&SpNpcCeleste::setupAct01, &SpNpcCeleste::mainAct01},
    {&SpNpcCeleste::setupAct02, &SpNpcCeleste::mainAct02},
    {&SpNpcCeleste::setupAct03, &SpNpcCeleste::mainAct03},
    {NULL, &SpNpcCeleste::mainAct04},
};

void SpNpcCelesteTalk::setResultHandler(s32 idx) {
    static SpNpcCelesteTalkFn tbl[5] = {
        &SpNpcCelesteTalk::onStargazingDone,
        &SpNpcCelesteTalk::onConstellationDrawn,
        &SpNpcCelesteTalk::onConstellationNamed,
        &SpNpcCelesteTalk::onConstellationRedrawn,
        &SpNpcCelesteTalk::onConstellationRenamed,
    };
    resultHandler = tbl[idx];
}

void SpNpcCelesteTalk::onStargazingDone() {
    TalkWindowState *o = window;
    u8 v = 0x12;
    o->setNextMessage(&v, sSpNpcCelesteKey);
}

void SpNpcCelesteTalk::onConstellationDrawn() {
    TalkWindowState *o = window;
    u8 msg[4];
    ClockDateTime t;
    msg[0] = 0xc;
    if (MenuCtrl_IsResultOk()) {
        t = ClockDateTime();
        Constellation_GetViewingTime(&t, constellationSlot);
        setMonthSlot(t.month, 2);
        setDaySlot(t.day, 3);
        setNumberSlot(t.minute, 5, 2, 0, 0);
        s32 h = 0x19;
        s32 m = t.hour;
        if (m > 0xc) {
            h = 0x1a;
            m -= 0xc;
        }
        if (m == 0) {
            m = 0xc;
        }
        setNumberSlot(m, 4, 2, 0, 0);
        msg[1] = h;
        o->setSlotFromString(8, &msg[1], "st_general");
        msg[0] = 8;
    } else {
        Constellation_Erase(constellationSlot);
        listRemaining = 0x10 - Constellation_CountFreeSlots();
        listStart = 0;
    }
    o->setNextMessage(msg, sSpNpcCelesteKey);
}

void SpNpcCelesteTalk::onConstellationNamed() {
    TalkWindowState *o = window;
    u8 v = 5;
    if (MenuCtrl_IsFinished()) {
        if (MenuCtrl_IsResultOk()) {
            ConstellationMsgString17 s;
            v = 0xb;
            Constellation_GetName(&s, constellationSlot);
            window->setSlot(0, &s);
        }
        o->setNextMessage(&v, sSpNpcCelesteKey);
    }
}

void SpNpcCelesteTalk::onConstellationRedrawn() {
    TalkWindowState *o = window;
    u8 v = 0x1d;
    if (MenuCtrl_IsResultOk()) {
        v = 0x38;
    } else {
        listRemaining = 0x10 - Constellation_CountFreeSlots();
        listStart = 0;
        v = 0x1d;
    }
    o->setNextMessage(&v, sSpNpcCelesteKey);
}

void SpNpcCelesteTalk::onConstellationRenamed() {
    TalkWindowState *o = window;
    u8 v = 5;
    if (MenuCtrl_IsFinished()) {
        if (MenuCtrl_IsResultOk()) {
            v = 0x3d;
            ConstellationMsgString17 s;
            Constellation_GetName(&s, constellationSlot);
            window->setSlot(0, &s);
        }
        o->setNextMessage(&v, sSpNpcCelesteKey);
    }
}

SpNpcCelesteTalk::SpNpcCelesteTalk() {}

SpNpcCelesteTalk::~SpNpcCelesteTalk() {}

void SpNpcCelesteTalk::resetMsg() {
    ActorTalkRequest::resetMsg();
    resultHandler = NULL;
    constellationSlot = Constellation_FindFreeSlot();
}

void SpNpcCelesteTalk::attachOwner(SpNpcCeleste *p) {
    resetMsg();
    owner = p;
    listStart = 0;
    listRemaining = 0x10 - Constellation_CountFreeSlots();
}

void SpNpcCelesteTalk::setTopic(s32 v) {
    topic = v;
}

void SpNpcCelesteTalk::start(TalkStartMsg *out) {
    if (GameStart_IsActive()) {
        out->msgKey = "sp_etc_sequence4";
        out->msgIndex = 0x14;
        return;
    }
    if (topic == 5) {
        if (Talk_CheckAndSetPlayerFlag(2, 1) == 0) {
            if (owner->isAsleep == 0) {
                topic = 1;
            } else {
                topic = 0;
            }
        } else {
            if (owner->isAsleep == 0) {
                topic = 3;
            } else {
                topic = 2;
            }
        }
    }
    s32 t = topic;
    if (t == 4 && owner->isAsleep == 0) {
        if (gCommManager->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
            if (Constellation_CountFreeSlots() < 0x10) {
                out->msgIndex = 0x13;
            } else {
                out->msgIndex = 0x10;
            }
        } else {
            if (Constellation_CountFreeSlots() < 0x10) {
                out->msgIndex = 0x14;
            } else {
                out->msgIndex = 1;
            }
        }
        out->msgKey = (const char *)sSpNpcCelesteKey;
    } else if (t >= 0 && t < 5) {
        out->msgIndex = sSpNpcCelesteTopicMsgs[t].msgIndex;
        out->msgKey = (const char *)sSpNpcCelesteTopicMsgs[topic].msgKey;
    }
}

s32 SpNpcCelesteTalk::getFollowUpMenuMsg() {
    listRemaining = 0x10 - Constellation_CountFreeSlots();
    listStart = 0;
    if (gCommManager->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
        if (Constellation_CountFreeSlots() < 0x10) {
            return 0x27;
        }
        return 0x26;
    }
    if (Constellation_CountFreeSlots() < 0x10) {
        return 0x28;
    }
    return 0x29;
}
extern "C" u8 sSpNpcCelesteKey[] = {'s', 'p', '_', 'n', 'p', 'c', '_', 'a', 's', 't', 'r', 'o', 0};


SpNpcCelesteMessageEndHandler SpNpcCelesteTalk_onMessageEnd_tbl[29] = {
            {0x00, &SpNpcCelesteTalk::announceNewConstellations},
            {0x04, &SpNpcCelesteTalk::showTelescopeMenu},
            {0x05, &SpNpcCelesteTalk::startNameEntry},
            {0x07, &SpNpcCelesteTalk::startConstellationEditor},
            {0x09, &SpNpcCelesteTalk::startNameEntry},
            {0x0b, &SpNpcCelesteTalk::reactToConstellationName},
            {0x0c, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x12, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x15, &SpNpcCelesteTalk::showConstellationList},
            {0x16, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x17, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x1a, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x1b, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x1d, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x1e, &SpNpcCelesteTalk::showConstellationList},
            {0x1f, &SpNpcCelesteTalk::showConstellationList},
            {0x21, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x2c, &SpNpcCelesteTalk::announceNewConstellations},
            {0x2d, &SpNpcCelesteTalk::announceNewConstellations},
            {0x2e, &SpNpcCelesteTalk::announceNewConstellations},
            {0x30, &SpNpcCelesteTalk::startStargazing},
            {0x32, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x33, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x3b, &SpNpcCelesteTalk::startRenameEntry},
            {0x3d, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x3e, &SpNpcCelesteTalk::showFollowUpMenu},
            {0x3f, &SpNpcCelesteTalk::showConstellationList},
            {0x40, &SpNpcCelesteTalk::showConstellationList},
            {0x41, &SpNpcCelesteTalk::showConstellationList},
        };
void SpNpcCelesteTalk::onMessageEnd(u32) {
    if (GameStart_IsActive() == 0) {
        PlayerData_GetCurrent();
        nextMsg = 0xff;
        s32 i = 0;
        u8 *p = &msgIndex;
        SpNpcCelesteMessageEndHandler *t = SpNpcCelesteTalk_onMessageEnd_tbl;
        for (; (u32)i < 0x1d; i++) {
            u32 a = SpNpcCelesteTalk_onMessageEnd_tbl[i].id;
            u32 b = *p;
            if (a == b) {
                (this->*t[i].f)();
            }
        }
        if (nextMsg != 0xff) {
            u8 v = nextMsg;
            window->setNextMessage(&v, sSpNpcCelesteKey);
        }
    }
}

void SpNpcCelesteTalk::announceNewConstellations() {
    s32 v = 0;
    if (Constellation_GetNewStatus(&v) == 0) {
        if (gCommManager->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
            nextMsg = 0x2f;
        } else {
            nextMsg = 0x11;
        }
    } else {
        if (Constellation_GetNewStatus(&v) == 1) {
            ConstellationMsgString17 s;
            Constellation_GetName(&s, v);
            window->setSlot(7, &s);
            nextMsg = 0x39;
        } else {
            nextMsg = 0x3a;
        }
        Constellation_ClearNewFlags();
    }
}

void SpNpcCelesteTalk::showTelescopeMenu() {
    if (gCommManager->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
        if (Constellation_CountFreeSlots() < 0x10) {
            nextMsg = 0x13;
        } else {
            nextMsg = 0x10;
        }
    } else {
        if (Constellation_CountFreeSlots() < 0x10) {
            nextMsg = 0x14;
        } else {
            nextMsg = 1;
        }
    }
}

void SpNpcCelesteTalk::startConstellationEditor() {
    constellationSlot = Constellation_FindFreeSlot();
    if (constellationSlot >= 0) {
        setSubSceneKindArg(0x2e, (u8)constellationSlot, 0);
        openSubScene(3);
        setResultHandler(1);
    } else {
        nextMsg = 0x3e;
    }
}

void SpNpcCelesteTalk::reactToConstellationName() {
    s32 r = Random_GlobalBelow(0x65);
    if (r < 0x46) {
        nextMsg = getFollowUpMenuMsg();
    } else if (r < 0x55) {
        nextMsg = 0x32;
    } else {
        nextMsg = 0x33;
    }
}

void SpNpcCelesteTalk::showFollowUpMenu() {
    nextMsg = getFollowUpMenuMsg();
}

void SpNpcCelesteTalk::showConstellationList() {
    openConstellationPage();
}

void SpNpcCelesteTalk::startNameEntry() {
    setSubSceneKind(0x12, 0);
    openSubScene(2);
    setResultHandler(2);
}

void SpNpcCelesteTalk::startRenameEntry() {
    setSubSceneKind(0x12, 0);
    openSubScene(2);
    setResultHandler(4);
}

void SpNpcCelesteTalk::startStargazing() {
    setSubSceneKind(0x2d, 0);
    openSubScene(2);
    setResultHandler(0);
}

void SpNpcCelesteTalk::onChoice(u32) {
    s32 t = getChoiceList()->getResult();
    nextMsg = 0xff;
    static SpNpcCelesteChoiceHandler tbl[26] = {
        {0x01, &SpNpcCelesteTalk::onTelescopeMenuChoice},
        {0x08, &SpNpcCelesteTalk::onViewingTimeChoice},
        {0x10, &SpNpcCelesteTalk::onStargazeMenuChoice},
        {0x13, &SpNpcCelesteTalk::onStargazeMenuChoice},
        {0x14, &SpNpcCelesteTalk::onFullMenuChoice},
        {0x15, &SpNpcCelesteTalk::onConstellationListChoice},
        {0x18, &SpNpcCelesteTalk::onMakeOrChangeChoice},
        {0x19, &SpNpcCelesteTalk::onEraseConfirmChoice},
        {0x1e, &SpNpcCelesteTalk::onConstellationListChoice},
        {0x1f, &SpNpcCelesteTalk::onConstellationListChoice},
        {0x20, &SpNpcCelesteTalk::onMakeNewOrLeaveChoice},
        {0x23, &SpNpcCelesteTalk::onDiscardNewChoice},
        {0x24, &SpNpcCelesteTalk::onRemakeChoice},
        {0x25, &SpNpcCelesteTalk::onMakeOrChangeChoice},
        {0x26, &SpNpcCelesteTalk::onStargazeMenuChoice},
        {0x27, &SpNpcCelesteTalk::onStargazeMenuChoice},
        {0x28, &SpNpcCelesteTalk::onFullMenuChoice},
        {0x29, &SpNpcCelesteTalk::onTelescopeMenuChoice},
        {0x2a, &SpNpcCelesteTalk::onMakeOrChangeChoice},
        {0x2b, &SpNpcCelesteTalk::onMakeOrChangeChoice},
        {0x31, &SpNpcCelesteTalk::onMakeNewOrMenuChoice},
        {0x35, &SpNpcCelesteTalk::onLookOrTimesChoice},
        {0x38, &SpNpcCelesteTalk::onRenameChoice},
        {0x3f, &SpNpcCelesteTalk::onConstellationListChoice},
        {0x40, &SpNpcCelesteTalk::onConstellationListChoice},
        {0x41, &SpNpcCelesteTalk::onConstellationListChoice},
    };
    u32 i = 0;
    u8 *pe = &msgIndex;
    goto test;
loop:
    {
        u32 id = tbl[i].id;
        u32 cur = *pe;
        if (id == cur) {
            (this->*tbl[i].fn)(t);
        }
    }
    i++;
test:
    if (i < 26) {
        goto loop;
    }
    if (nextMsg != 0xff) {
        u8 b = nextMsg;
        window->setNextMessage(&b, sSpNpcCelesteKey);
    }
}

void SpNpcCelesteTalk::onViewingTimeChoice(s32 a) {
    if (a == 0) {
        nextMsg = 9;
    } else {
        nextMsg = 0x23;
    }
}

void SpNpcCelesteTalk::onConstellationListChoice(s32 idx) {
    u8 msg;
    ClockDateTime time;
    TalkWindowState *o = window;
    constellationSlot = listSlots[idx];
    if (constellationSlot >= 0) {
        ConstellationMsgString17 name;
        Constellation_GetName(&name, constellationSlot);
        window->setSlot(6, &name);
        if (listMode == 0) {
            nextMsg = 0x19;
            listStart = 0;
        } else if (listMode == 1) {
            time = ClockDateTime();
            Constellation_GetViewingTime(&time, constellationSlot);
            setMonthSlot(time.month, 2);
            setDaySlot(time.day, 3);
            setNumberSlot(time.minute, 5, 2, 0, 0);
            s32 t4 = time.hour;
            s32 r1 = 0x19;
            if (t4 > 0xc) {
                r1 = 0x1a;
                t4 -= 0xc;
            }
            if (t4 == 0) {
                t4 = 0xc;
            }
            msg = r1;
            o->setSlotFromString(8, &msg, "st_general");
            setNumberSlot(t4, 4, 2, 0, 0);
            nextMsg = 0x17;
        } else if (listMode == 2) {
            setSubSceneKindArg(0x2e, (u8)constellationSlot, 0);
            openSubScene(3);
            setResultHandler(3);
        }
        listMode = 0;
    } else {
        if (listRemaining == 0) {
            nextMsg = getFollowUpMenuMsg();
            if ((u8)(listMode + 0xff) <= 1) {
                if (Constellation_CountFreeSlots() < 0x10) {
                    if (listMode == 1) {
                        nextMsg = 0x16;
                    } else {
                        nextMsg = 0x1d;
                    }
                }
            }
            listMode = 0;
        } else {
            if (msgIndex == 0x15) {
                goto set3f;
            }
            if (msgIndex == 0x1e) {
                goto set3f;
            }
            if (msgIndex == 0x1f) {
            set3f:
                nextMsg = 0x3f;
            } else if (msgIndex == 0x3f) {
                nextMsg = 0x40;
            } else if (msgIndex == 0x40) {
                nextMsg = 0x41;
            }
        }
    }
}

void SpNpcCelesteTalk::onMakeNewOrMenuChoice(s32 a) {
    if (a == 0) {
        nextMsg = 7;
    } else if (Constellation_CountFreeSlots() < 0x10) {
        nextMsg = 0x2a;
    } else {
        nextMsg = getFollowUpMenuMsg();
    }
}

void SpNpcCelesteTalk::onDiscardNewChoice(s32 a) {
    if (a == 0) {
        if (constellationSlot >= 0) {
            Constellation_Erase(constellationSlot);
        }
        listRemaining = 0x10 - Constellation_CountFreeSlots();
        listStart = 0;
        nextMsg = 0x21;
    } else {
        nextMsg = 9;
    }
}

void SpNpcCelesteTalk::onTelescopeMenuChoice(s32 a) {
    if (a == 0) {
        if (Constellation_CountFreeSlots() < 0x10) {
            nextMsg = 0x18;
        } else {
            nextMsg = 7;
        }
    } else if (a == 1) {
        nextMsg = 0x30;
    } else {
        nextMsg = 2;
    }
}

void SpNpcCelesteTalk::onFullMenuChoice(s32 a) {
    listRemaining = 0x10 - Constellation_CountFreeSlots();
    listStart = 0;
    if (a == 0) {
        if (Constellation_CountFreeSlots() < 0x10) {
            nextMsg = 0x18;
        } else {
            nextMsg = 7;
        }
    } else if (a == 1) {
        nextMsg = 0x35;
    } else if (a == 2) {
        listRemaining = 0x10 - Constellation_CountFreeSlots();
        u8 z = 0;
        listStart = z;
        nextMsg = 0x1f;
        listMode = z;
    } else {
        nextMsg = 2;
    }
}

void SpNpcCelesteTalk::onEraseConfirmChoice(s32 a) {
    listStart = 0;
    if (a == 0) {
        if (constellationSlot >= 0) {
            ConstellationMsgString17 name;
            Constellation_GetName(&name, constellationSlot);
            window->setSlot(6, &name);
            Constellation_Erase(constellationSlot);
        }
        listRemaining = 0x10 - Constellation_CountFreeSlots();
        listStart = 0;
        nextMsg = 0x1b;
    } else {
        nextMsg = getFollowUpMenuMsg();
    }
}

void SpNpcCelesteTalk::onMakeOrChangeChoice(s32 a) {
    listRemaining = 0x10 - Constellation_CountFreeSlots();
    listStart = 0;
    if (a == 0) {
        if (Constellation_CountFreeSlots() == 0) {
            nextMsg = 0x3e;
        } else {
            nextMsg = 7;
        }
    } else if (a == 1) {
        listMode = 2;
        nextMsg = 0x1e;
    } else {
        nextMsg = 0xc;
    }
}

void SpNpcCelesteTalk::onStargazeMenuChoice(s32 a) {
    if (a == 0) {
        if (Constellation_CountFreeSlots() < 0x10) {
            nextMsg = 0x35;
        } else {
            nextMsg = 0x30;
        }
    } else {
        nextMsg = 2;
    }
}

void SpNpcCelesteTalk::onMakeNewOrLeaveChoice(s32 a) {
    if (a == 0) {
        nextMsg = 7;
    } else {
        nextMsg = 0xc;
    }
}

void SpNpcCelesteTalk::onRemakeChoice(s32 a) {
    listRemaining = 0x10 - Constellation_CountFreeSlots();
    listStart = 0;
    if (a == 0) {
        listMode = 2;
        nextMsg = 0x1e;
    } else if (Constellation_CountFreeSlots() < 0x10) {
        nextMsg = 0x25;
    } else {
        nextMsg = getFollowUpMenuMsg();
    }
}

void SpNpcCelesteTalk::onLookOrTimesChoice(s32 a) {
    if (a == 0) {
        nextMsg = 0x30;
    } else if (a == 1) {
        listMode = 1;
        nextMsg = 0x15;
    } else {
        nextMsg = 0x16;
    }
}


void SpNpcCelesteTalk::onRenameChoice(s32 a) {
    if (a == 0) {
        nextMsg = 0x3b;
    } else {
        nextMsg = getFollowUpMenuMsg();
    }
}

BOOL SpNpcCeleste::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

BOOL SpNpcCeleste::acceptsSelfRequestedInteraction(void *) {
    return talkCtrl.isBusy() == 0 ? TRUE : FALSE;
}

void SpNpcCeleste::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 0:
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(3);
        break;
    case 8:
        changeAct(1);
        break;
    }
}

BOOL SpNpcCeleste::isPlayerAtTelescope() {
    VecFx32 v0;
    VecFx32 v1;
    s32 out;
    VecFx32 pos;
    BOOL result;
    Actor *p = (Actor *)PlayerActor_GetActor(4);
    BOOL r6;
    if (Unk_ov046_02258e68_Both()) {
        r6 = TRUE;
    } else {
        r6 = FALSE;
    }
    if (p == 0 || talkCtrl.isBusy() != 0) {
        talk.setTopic(5);
        result = FALSE;
        goto end;
    }
    VecFx32 *pv;
    pv = &p->position;
    v0.x = p->position.x;
    v0.y = pv->y;
    v0.z = pv->z;
    v1.x = p->position.x;
    v1.y = pv->y;
    v1.z = pv->z;
    v1.x = 0x10800;
    v1.z = 0x17000;
    s32 d;
    d = Vec_DistXZ(&v0, &v1);
    s32 a;
    a = p->rotY;
    if (d < 0x1000) {
        a = a & 0xffff;
        if (a < 0x6000 || a > 0xa000) {
            talk.setTopic(5);
            result = FALSE;
            goto end;
        }
        if (r6 == 0) {
            if ((gPad[1] & 1) != 0) {
                result = TRUE;
                goto end;
            }
        }
        if (r6 != 0) {
            if (TouchPickResult_GetTarget(Scene_GetTouchPicker(), &pos, &out, NULL) != 0) {
                if (out == 0x16) {
                    result = TRUE;
                    goto end;
                }
            }
        }
    }
    result = FALSE;
end:
    return result;
}

BOOL SpNpcCeleste::tryStartTelescopeTalk() {
    if (isPlayerAtTelescope()) {
        talk.setTopic(4);
        Camera_LockFocusYaw();
        TalkRequest_AddPlayerTalk6(this, 0);
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov046_02258de0) {
    HOST_OVERLAY_VAR(data_ov046_0225ae04),
    HOST_OVERLAY_VAR(data_ov046_0225ae08),
    HOST_OVERLAY_VAR(data_ov046_0225ae20),
    HOST_OVERLAY_VAR(data_ov046_0225ae10),
    HOST_OVERLAY_VAR(data_ov046_0225ae00),
    HOST_OVERLAY_VAR(data_ov046_0225ae0c),
    HOST_OVERLAY_VAR(sSpNpcCelesteModelPath),
    HOST_OVERLAY_VAR(sSpNpcCelesteTexturePath),
    HOST_OVERLAY_VAR(sSpNpcCelesteProfile),
    HOST_OVERLAY_VAR(sSpNpcCelesteActTable),
    HOST_OVERLAY_VAR(sSpNpcCelesteKey),
    HOST_OVERLAY_VAR(SpNpcCelesteTalk_onMessageEnd_tbl),
    HOST_OVERLAY_VARS_END
};

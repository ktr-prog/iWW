#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "snd/BgmBeatPhase.h"
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
#include "item/ItemName.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/EncodedString16Buf.h"
#include "talk/ChoiceList.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "net/CommManager.h"
#include "npc/NpcFaceAnim.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcMoveAnimSet.h"
#include "player/PlayerData.h"
#include "save/SaveRecord4.h"
#include "talk/MsgString.h"
#include "game/RoostGuestRoll.h"
#include "save/SaveData.h"
#include "sys/ClockDateTime.h"
#include "text/Unk_02050288.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov004/unk_ov004_022264a0.h"
#include "proto/ov068/unk_ov068_0226c2e0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;


















class SpNpcRoostGuest;

class SpNpcRoostGuestTalk : public SpNpcTalkRequest {
public:
    SpNpcRoostGuestTalk();
    virtual ~SpNpcRoostGuestTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void scriptRestoreLook();
    void scriptEndPerformance();
    void scriptPerform();
    void scriptStartPerformance();
    void scriptReadSongRequest();
    void setScript(s32 state);
    void onKkChoiceRequest(s32 a);
    void onKkChoiceTradeGuitar(s32 a);
    void onKkChoiceListen(s32 a);
    void dispatchKkChoice(s32 a);
    void onKkStartShow();
    void onKkAskSongRequest();
    void dispatchKkMessageEnd(s32 a);
    void fillKkSongName(s32 a);
    s32 getTalkMode();
    void setTalkMode(s32 v);
    void attachOwner(SpNpcRoostGuest *o);

    /* 0xac */ s32 talkMode;
    /* 0xb0 */ SpNpcRoostGuest *owner;
    /* 0xb4 */ s32 script;
    /* 0xb8 */ BgmBeatPhase lastBeatState;
    /* 0xcc */ u8 beatPoseStarted;
    /* 0xcd */ u8 pad_cd[3];
};

class SpNpcRoostGuest : public SpNpcActor {
public:
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL checkPlayerSeated();
    u32 getGuest();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    /* 0x652 */ u16 songItem;
    /* 0x654 */ s32 showBgm;
    /* 0x658 */ s32 act;
    /* 0x65c */ SpNpcRoostGuestTalk talk;
    /* 0x72c */ s32 guestType;
    /* 0x730 */ u8 requestText[0x10];
    /* 0x740 */ u16 showTimer;
    /* 0x742 */ u8 showAccepted;
    /* 0x743 */ u8 isRandomSong;
    /* 0x744 */ u8 hasSongRequest;
};

typedef BOOL (SpNpcRoostGuest::*SpNpcRoostGuestActFn)();
struct SpNpcRoostGuestActEntry {
    SpNpcRoostGuestActFn enter;
    SpNpcRoostGuestActFn exit;
};



struct KkShowStackPad {
    s32 v[2];
    KkShowStackPad() {}
    ~KkShowStackPad() {}
};

typedef void (SpNpcRoostGuestTalk::*SpNpcRoostGuestTalkScriptFn)();
typedef void (SpNpcRoostGuestTalk::*SpNpcRoostGuestChoiceFn)(s32);
typedef void (SpNpcRoostGuestTalk::*SpNpcRoostGuestMessageEndFn)();

struct SpNpcRoostGuestTalkScript {
    SpNpcRoostGuestTalkScriptFn fn;
    u32 flag;
};

struct SpNpcRoostGuestChoiceHandler {
    u32 id;
    SpNpcRoostGuestChoiceFn fn;
};

struct SpNpcRoostGuestMessageEndHandler {
    u32 id;
    SpNpcRoostGuestMessageEndFn fn;
};

extern "C" {
extern ActorProfile sSpNpcRoostGuestProfile;
extern const char *sRoostGuestMsgFiles[9];
extern const char *sRoostGuestModelPaths[9];
extern const char *sRoostGuestTexPaths[9];
extern const u8 sKkTalkModeMessages[4];
extern const u16 sRoostGuestNpcHandles[10];
extern SpNpcRoostGuestActEntry sSpNpcRoostGuestActTable[5];
extern SpNpcRoostGuestTalkScript sKkShowScripts[6];
}

extern "C" {
extern u16 data_020c6cc8;
extern s16 data_020c6cc4;
extern s16 data_020c6cbc;
extern s32 data_020c6d1c;
extern VecFx32 gVec3Zero;
extern SaveData gSaveData;
extern CommManager *gCommManager;
void MI_CpuCopy8(const void *src, void *dst, u32 n);
void Clock_GetDateTime(ClockDateTime *p);
s32 Clock_GetWeekday();
u16 Math_CountDownU16(u16 *p);
BOOL TalkRequest_AddPlayerTalk7(Character *a, s32 b);
BOOL TalkRequest_SetTargetDone(Character *x);
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
BOOL EncodedString_SetRaw(StrBuf *buf, const void *src, s32 len);
void LightSwitch_SetOff(s32 i, u32 v);
void LightSwitch_SetOn(s32 i, u32 a, u32 b);
u32 NookShop_GetLevel(void *p);
BOOL Camera_SetModeDefault(void);
void Camera_SetMode18(void);
void RoomCamera_KkShowWideShot(void);
void RoomCamera_KkShowPickShot(void);
void RoomCamera_KkShowResetShot(void);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *a, u32 b, u32 c);
void NNS_G3dMdlSetMdlLightEnableFlagAll(u8 *m, u32 x);
void KkShowFx_Start(void);
void KkShowFx_Stop();
void KkShowFx_Update(void);
void KkShowFx_SetParam(s32 a);
s32 KkShowFx_GetState();
void KkShowFx_CallUnk1de4();
void KkShowFx_CallUnk1f70(void);
}

static inline BOOL Unk_ov068_0226c340_R(volatile u16 *p) {
    BOOL r = FALSE;
    u16 a = *p;
    u16 b = *p;
    if (b >= 0x1323 && a <= 0x1368) r = TRUE;
    return r;
}

extern "C" char sRoostTexMof[27] = "npc_sp/model/mof_tex.nsbtx";
extern "C" char sRoostTexEnd[27] = "npc_sp/model/end_tex.nsbtx";
extern "C" char sRoostMsgCf3[11] = "sp_npc_cf3";
extern "C" char sRoostTexPga[27] = "npc_sp/model/pga_tex.nsbtx";
extern "C" char sRoostModelPga[23] = "npc_sp/model/pga.nsbmd";
extern "C" char sKkMouthM5[4] = "m.5";
extern "C" char sKkMouthM4[4] = "m.4";
extern "C" char sRoostTexPgb[27] = "npc_sp/model/pgb_tex.nsbtx";
extern "C" char sRoostModelPgb[23] = "npc_sp/model/pgb.nsbmd";



extern "C" SpNpcRoostGuest *SpNpcRoostGuest_Create() {
    return new SpNpcRoostGuest();
}

BOOL SpNpcRoostGuest::preCreate() {
    ClockDateTime d = {};
    u16 h;
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest(&talk);
    talk.attachOwner(this);
    shadowEnabled = 0;
    Clock_GetDateTime(&d);
    u8 mo = d.hour;
    u8 dy = d.minute;
    guestType = 8;
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        return TRUE;
    }
    if (((SaveRecord4 *)gSaveData.unk_15fc5)->isDateActive()) {
        return TRUE;
    }
    RoostGuestRoll *g = (RoostGuestRoll *)gSaveData.roostGuestRoll;
    switch (Clock_GetWeekday()) {
    case 6:
        if ((mo == 0x13 && dy >= 0x1e) || mo == 0x14 || mo == 0x15 || mo == 0x16 || (mo == 0x17 && dy <= 0x3b)) {
            guestType = 7;
            Actor::spawn(0x10, 0, NULL, NULL, NULL);
        }
        break;
    case 0:
        if (mo == 0x15 && dy < 0x37) {
            guestType = 1;
        }
        break;
    default:
        if (mo == 0x15 && dy < 0x37) {
            guestType = 1;
        }
        if (mo == 0x17 && dy <= 0x3b) {
            if (g->hasLateGuest()) {
                if (NookShop_GetLevel(gSaveData.nookShop) == 3) {
                    guestType = 2;
                }
            }
        }
        break;
    }
    if (mo == 0xc || (mo == 0xd && dy < 0x1e)) {
        switch (g->getNoonGuest()) {
        case 2:
            guestType = 5;
            break;
        case 1:
            guestType = 4;
            break;
        case 3:
            guestType = 6;
            break;
        case 4:
            guestType = 3;
            break;
        }
    }
    if ((mo == 0xe && dy >= 0x1e) || (mo == 0xf && dy <= 0x3b)) {
        switch (g->getAfternoonGuest()) {
        case 2:
            guestType = 5;
            break;
        case 1:
            guestType = 4;
            break;
        case 3:
            guestType = 6;
            break;
        case 4:
            guestType = 3;
            break;
        }
    }
    if (mo == 6 && dy < 0x37 && g->hasMorningGuest()) {
        guestType = 0;
    }
    h = sRoostGuestNpcHandles[guestType];
    setNpcHandle(&h);
    if (guestType == 7) {
        setInteractionRange(0x5000);
        position.x = 0xf000;
        position.z = 0x13000;
        rotY = 0;
        moveAngleY = 0;
        moveAnimSet.setStandAnim(0x102);
        moveAnimSet.setWalkAnim(0x102);
        moveAnimSet.setRunAnim(0x102);
        lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    } else {
        moveAnimSet.setStandAnim(0x1e);
        moveAnimSet.setWalkAnim(0x1e);
        moveAnimSet.setRunAnim(0x1e);
        lookAt.setPitchLimit(0);
    }
    return TRUE;
}

BOOL SpNpcRoostGuest::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    if (guestType == 7) {
        NNS_G3dMdlSetMdlLightEnableFlagAll((u8 *)model.resMdl, 3);
    }
    changeAct(0);
    collider.groups |= 2;
    if (guestType == 3) {
        animCtrl.playAnim(this, 0x142, 0, 0, 0x1000, 0, 1);
        ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    }
    return TRUE;
}

BOOL SpNpcRoostGuest::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    if (guestType == 7) {
        KkShowFx_Stop();
    }
    return TRUE;
}

u8 *SpNpcRoostGuest::getTexturePath() {
    return (u8 *)sRoostGuestTexPaths[guestType];
}

u8 *SpNpcRoostGuest::getModelPath() {
    return (u8 *)sRoostGuestModelPaths[guestType];
}

BOOL SpNpcRoostGuest::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcRoostGuestActTable[act].exit != NULL) {
        result = (this->*sSpNpcRoostGuestActTable[act].exit)();
    }
    return result;
}

void SpNpcRoostGuest::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcRoostGuestActTable[state].enter != NULL) {
        ok = (this->*sSpNpcRoostGuestActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcRoostGuest::setupAct00() {
    if (guestType == 7) {
        lookAt.setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
        actionCtrl.requestPlayAnim(1, 0x105, 0, data_020c6cc8, 0);
        lookAt.setManualAngles(0, -0xc18, 0, data_020c6cc4, data_020c6cbc);
    } else {
        lookAt.setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    }
    return TRUE;
}

BOOL SpNpcRoostGuest::mainAct00() {
    if (guestType == 8) {
        ProcBase_RequestDelete(this);
        return TRUE;
    }
    if (guestType == 7) {
        checkPlayerSeated();
    } else {
        CafeCoffeeSet_StartEffectB();
    }
    if (guestType == 6) {
        CafeCoffeeSet_SetFlagEF8();
    }
    return TRUE;
}

BOOL SpNpcRoostGuest::setupAct01() {
    if (guestType == 7) {
        actionCtrl.requestPlayAnim(1, 0x102, 0, data_020c6cc8, 0);
    }
    lookAt.setTarget(4, 0, 0, &gVec3Zero, 4, data_020c6d1c, 0);
    talkCtrl.requestTalk(0, 0);
    return TRUE;
}

BOOL SpNpcRoostGuest::mainAct01() {
    if (talkCtrl.isBusy()) {
        return TRUE;
    }
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(4);
    }
    return TRUE;
}

BOOL SpNpcRoostGuest::setupAct04() {
    return TRUE; }

BOOL SpNpcRoostGuest::mainAct04() {
    return TRUE; }

BOOL SpNpcRoostGuest::setupAct03() {
    return TRUE; }

BOOL SpNpcRoostGuest::mainAct03() {
    if (PlayerActor_IsInAction(0x28, 4)) {
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcRoostGuest::setupAct02() {
    actionCtrl.requestPlayAnim(1, 0x102, 0, data_020c6cc8, 0);
    Camera_SetMode18();
    lookAt.setManualAngles(0, 0, 0x1000, data_020c6cc4, data_020c6cbc);
    talkCtrl.requestTalk(0, 1);
    Bgm_RequestSilence(0x10, 0xf, 0);
    Bgm_DisableHourChime();
    return TRUE;
}

BOOL SpNpcRoostGuest::mainAct02() {
    if (talkCtrl.isBusy()) {
        return TRUE;
    }
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        if (PlayerActor_IsInAction(0x28, 4)) {
            PlayerActor_LocalRequestStandUp(0);
        }
        Bgm_ReleasePriority(0x10);
        Bgm_EnableHourChime();
        Camera_SetModeDefault();
        changeAct(4);
    }
    return TRUE;
}

SpNpcRoostGuestTalk::SpNpcRoostGuestTalk() {}

SpNpcRoostGuestTalk::~SpNpcRoostGuestTalk() {}

void SpNpcRoostGuestTalk::attachOwner(SpNpcRoostGuest *o) {
    resetMsg();
    owner = o;
}

void SpNpcRoostGuestTalk::setTalkMode(s32 v) {
    talkMode = v; }

s32 SpNpcRoostGuestTalk::getTalkMode() {
    return talkMode; }

void SpNpcRoostGuestTalk::start(TalkStartMsg *out_) {
    TalkStartMsg *out = (TalkStartMsg *)out_;
    u16 h0, h2, h4, h6;
    lastBeatState.seqVar4 = -1;
    lastBeatState.trackAnim = -1;
    lastBeatState.seqVar0 = -1;
    lastBeatState.seqVar2 = -1;
    lastBeatState.seqVar3 = -1;
    PlayerData *p = PlayerData_GetCurrent();
    out->msgKey = sRoostGuestMsgFiles[owner->guestType];
    if (owner->guestType == 7) {
        if (getTalkMode() == 0) {
            ClockDateTime d = {};
            Clock_GetDateTime(&d);
            u8 m = d.hour;
            if (m < 0x14 && m >= 0x13) {
                h0 = 0x3530;
                s32 r = Pocket_FindItem(&h0);
                BOOL ok = FALSE;
                if (r != -1) {
                    ok = TRUE;
                }
                if (ok) {
                    out->msgIndex = 0xe;
                } else {
                    out->msgIndex = 0x13;
                }
            } else if (owner->showAccepted != 0) {
                out->msgIndex = 0;
            } else if (Talk_CheckAndSetPlayerFlag(0xd, 0) != 0) {
                h2 = 0x3530;
                s32 r = Pocket_FindItem(&h2);
                BOOL ok = FALSE;
                if (r != -1) {
                    ok = TRUE;
                }
                if (ok) {
                    out->msgIndex = 0xe;
                } else {
                    out->msgIndex = 0x12;
                }
            } else if (p->testFlag(7) == 0) {
                out->msgIndex = 1;
                p->setFlag(7);
            } else if (Talk_CheckAndSetPlayerFlag(0xc, 1) == 0) {
                out->msgIndex = 2;
            } else {
                out->msgIndex = 3;
            }
        } else {
            if (getTalkMode() == 1) {
                ItemName a;
                EncodedString16Buf b;
                EncodedString_SetRaw((StrBuf *)&b, owner->requestText, 0x10);
                a.fromEncoded(&b, 0, 0);
                window->setNamedSlot(0, &a, 7);
            } else if (getTalkMode() == 2) {
                h4 = owner->songItem;
                setItemNameSlot(&h4, 1, 7);
                h6 = owner->songItem;
                setItemNameSlot(&h6, 2, 7);
            }
            out->msgIndex = sKkTalkModeMessages[talkMode];
            out->msgKey = sRoostGuestMsgFiles[owner->guestType];
        }
    } else {
        if (Talk_CheckAndSetPlayerFlag(owner->guestType + 0x21, 1) == 0) {
            out->msgIndex = Random_GlobalBelow(3);
        } else {
            out->msgIndex = Random_GlobalBelow(5) + 3;
        }
    }
}

void SpNpcRoostGuestTalk::onMessageStart(u32 a_) {
    s32 a = (s32)a_;
    if (owner->guestType == 7) {
        fillKkSongName(a);
    }
}

void SpNpcRoostGuestTalk::fillKkSongName(s32 a) {
    switch (msgIndex) {
    case 12:
    case 13: {
        u16 v = owner->songItem;
        setItemNameSlot(&v, 1, 7);
        break;
    }
    case 11: {
        ItemName a;
        EncodedString16Buf b;
        EncodedString_SetRaw((StrBuf *)&b, owner->requestText, 0x10);
        a.fromEncoded(&b, 0, 0);
        window->setNamedSlot(0, &a, 7);
        break;
    }
    }
}

void SpNpcRoostGuestTalk::onMessageEnd(u32 a_) {
    s32 a = (s32)a_;
    if (owner->guestType == 7) {
        dispatchKkMessageEnd(a);
    }
}

void SpNpcRoostGuestTalk::dispatchKkMessageEnd(s32 a) {
    static SpNpcRoostGuestMessageEndHandler tbl[3] = {
        {7, &SpNpcRoostGuestTalk::onKkAskSongRequest},
        {6, &SpNpcRoostGuestTalk::onKkStartShow},
        {9, &SpNpcRoostGuestTalk::onKkStartShow},
    };
    s32 i = 0;
    u8 *pc = &msgIndex;
    for (; (u32)i < 3; i++) {
        u32 id = tbl[i].id;
        if (id == *pc) {
            SpNpcRoostGuestMessageEndHandler *e = &tbl[i];
            (this->*e->fn)();
        }
    }
}

extern "C" const char *sRoostGuestTexPaths[9] = {sRoostTexPga, sRoostTexPgb, sRoostTexPoo, sRoostTexOtt, sRoostTexWip, sRoostTexXct, sRoostTexMof, sRoostTexEnd, sRoostTexEnd};
extern const u16 sRoostGuestNpcHandles[10] = {0xd006, 0xd007, 0xd017, 0xd00d, 0xd014, 0xd024, 0xd011, 0xd01d, 0xd01d, 0x0000};
extern "C" char sRoostMsgCf4[11] = "sp_npc_cf4";
extern "C" char sRoostModelWip[23] = "npc_sp/model/wip.nsbmd";
extern "C" ActorProfile sSpNpcRoostGuestProfile = {(void *(*)())SpNpcRoostGuest_Create, 0x66, 0x6c, 0, 0x5000, 0x5000, 0x3e800};
extern const u8 sKkTalkModeMessages[4] = {0x00, 0x09, 0x06, 0x00};
extern "C" char sRoostMsgCf2[11] = "sp_npc_cf2";


void SpNpcRoostGuestTalk::onKkAskSongRequest() {
    setSubSceneKind(0xd, 0);
    openSubScene(2);
    setScript(1);
}

void SpNpcRoostGuestTalk::onKkStartShow() {
    window->openMode = 0;
    owner->showTimer = 0x2d;
    setScript(2);
}

void SpNpcRoostGuestTalk::onChoice(u32 a_) {
    s32 a = (s32)a_;
    if (owner->guestType == 7) {
        dispatchKkChoice(a);
    }
}

void SpNpcRoostGuestTalk::dispatchKkChoice(s32 a) {
    static SpNpcRoostGuestChoiceHandler tbl[5] = {
        {1, &SpNpcRoostGuestTalk::onKkChoiceListen},
        {2, &SpNpcRoostGuestTalk::onKkChoiceListen},
        {3, &SpNpcRoostGuestTalk::onKkChoiceListen},
        {5, &SpNpcRoostGuestTalk::onKkChoiceRequest},
        {0xe, &SpNpcRoostGuestTalk::onKkChoiceTradeGuitar},
    };
    u32 i = 0;
    u8 *pe = &msgIndex;
    goto test;
loop:
    u32 idv;
    idv = tbl[i].id;
    if (idv == *pe) {
        u32 x = window->getChoiceList()->getResult();
        SpNpcRoostGuestChoiceFn *fp = &tbl[i].fn;
        (this->*(*fp))(x);
    }
    i++;
test:
    if (i < 5) goto loop;
}

extern "C" char sRoostTexWip[27] = "npc_sp/model/wip_tex.nsbtx";
extern "C" char sRoostModelEnd[23] = "npc_sp/model/end.nsbmd";
extern "C" char sKkMouthM2[4] = "m.2";
extern "C" const char *sRoostGuestMsgFiles[9] = {sRoostMsgCf1, sRoostMsgCf2, sRoostMsgCf3, sRoostMsgCf4, sRoostMsgCf5, sRoostMsgCf6, sRoostMsgCf7, sRoostMsgDog, sRoostMsgCf7};
extern "C" const char *sRoostGuestModelPaths[9] = {sRoostModelPga, sRoostModelPgb, sRoostModelPoo, sRoostModelOtt, sRoostModelWip, sRoostModelXct, sRoostModelMof, sRoostModelEnd, sRoostModelEnd};
extern "C" char sKkMouthM1[4] = "m.1";
extern "C" char sRoostModelMof[23] = "npc_sp/model/mof.nsbmd";
extern "C" char sRoostMsgDog[11] = "sp_npc_dog";
extern "C" char sRoostModelOtt[23] = "npc_sp/model/ott.nsbmd";
extern "C" char sRoostTexPoo[27] = "npc_sp/model/poo_tex.nsbtx";
extern "C" char sRoostTexOtt[27] = "npc_sp/model/ott_tex.nsbtx";
extern "C" SpNpcRoostGuestTalkScript sKkShowScripts[6] = {{NULL, 0}, {&SpNpcRoostGuestTalk::scriptReadSongRequest, 0}, {&SpNpcRoostGuestTalk::scriptStartPerformance, 1}, {&SpNpcRoostGuestTalk::scriptPerform, 1}, {&SpNpcRoostGuestTalk::scriptEndPerformance, 1}, {&SpNpcRoostGuestTalk::scriptRestoreLook, 1}};
extern "C" char sRoostMsgCf7[11] = "sp_npc_cf7";
extern "C" char sKkMouthM3[4] = "m.3";
extern "C" char sRoostTexXct[27] = "npc_sp/model/xct_tex.nsbtx";
extern "C" char sRoostMsgCf1[11] = "sp_npc_cf1";
extern "C" char *sKkMouthTextures[6] = {sKkMouthM0, sKkMouthM1, sKkMouthM2, sKkMouthM3, sKkMouthM4, sKkMouthM5};
extern "C" char sRoostMsgCf6[11] = "sp_npc_cf6";
extern "C" char sRoostMsgCf5[11] = "sp_npc_cf5";
extern "C" char sRoostModelXct[23] = "npc_sp/model/xct.nsbmd";
extern "C" char sKkMouthM0[4] = "m.0";
extern "C" SpNpcRoostGuestActEntry sSpNpcRoostGuestActTable[5] = {{&SpNpcRoostGuest::setupAct00, &SpNpcRoostGuest::mainAct00}, {&SpNpcRoostGuest::setupAct01, &SpNpcRoostGuest::mainAct01}, {&SpNpcRoostGuest::setupAct02, &SpNpcRoostGuest::mainAct02}, {&SpNpcRoostGuest::setupAct03, &SpNpcRoostGuest::mainAct03}, {&SpNpcRoostGuest::setupAct04, &SpNpcRoostGuest::mainAct04}};
extern "C" char sRoostModelPoo[23] = "npc_sp/model/poo.nsbmd";


void SpNpcRoostGuestTalk::onKkChoiceListen(s32 a) {
    if (a == 0) {
        owner->showAccepted = 1;
    }
}

void SpNpcRoostGuestTalk::onKkChoiceTradeGuitar(s32 a) {
    u16 h0;
    u16 h1;
    if (a == 0) {
        h0 = 0x3530;
        s32 slot;
        if ((slot = Pocket_FindItem(&h0)) != -1) {
            Pocket_RemoveItem(slot);
            h1 = 0x4a34;
            Pocket_AddItem(&h1, 0);
        }
    }
}

void SpNpcRoostGuestTalk::onKkChoiceRequest(s32 a) {
    if (a == 0) {
        owner->hasSongRequest = 1;
    } else {
        owner->hasSongRequest = 0;
        owner->isRandomSong = 0;
        owner->songItem = RoostGuest_PickKKSong(owner);
    }
}

void SpNpcRoostGuestTalk::update() {
    s32 i = script;
    if (sKkShowScripts[i].flag != 0) {
        SpNpcRoostGuestTalkScript *e = &sKkShowScripts[i];
        if (e->fn != 0) {
            (this->*e->fn)();
        }
    }
}

void SpNpcRoostGuestTalk::onTaskDone(u32) {
    s32 i = script;
    if (sKkShowScripts[i].flag == 0) {
        SpNpcRoostGuestTalkScript *e = &sKkShowScripts[i];
        if (e->fn != 0) {
            (this->*e->fn)();
            setScript(0);
        }
    }
}

void SpNpcRoostGuestTalk::setScript(s32 state) {
    script = state;
}

void SpNpcRoostGuestTalk::scriptReadSongRequest() {
    u8 cmd;
    u16 tmp;
    MI_CpuCopy8(MenuCtrl_GetText(), owner->requestText, 0x10);
    ItemName objA;
    EncodedString16Buf objB;
    EncodedString_SetRaw((StrBuf *)&objB, owner->requestText, 0x10);
    objA.fromEncoded(&objB, 0, 0);
    (window)->setNamedSlot(0, &objA, 7);
    if (MenuCtrl_IsResultOk()) {
        u32 v;
        u16 h;
        owner->isRandomSong = 0;
        v = MenuCtrl_GetIndex();
        if (v < 0x46) {
            h = v + 0x1323;
        } else {
            h = 0x1323;
        }
        owner->songItem = h;
        tmp = owner->songItem;
        setItemNameSlot(&tmp, 1, 7);
    } else {
        owner->isRandomSong = 1;
        owner->songItem = RoostGuest_PickKKSong(owner);
    }
    cmd = 8;
    window->setNextMessage(&cmd, (void *)sRoostGuestMsgFiles[owner->guestType]);
}

void SpNpcRoostGuestTalk::scriptStartPerformance() {
    KkShowStackPad pad;
    TalkWindowState *q = TalkWindow_Get(0);
    if (q->state == 5) {
        if (owner->showTimer == 0x2d) {
            LightSwitch_SetOff(0, 0x1e);
            LightSwitch_SetOn(1, 1, 0);
            owner->lookAt.setManualAngles(0, -0xc18, 0, 0x276, 0x276);
        }
        if (Math_CountDownU16(&owner->showTimer) == 0) {
            RoomCamera_KkShowWideShot();
            owner->showBgm = 0;
            if (owner->isRandomSong != 0) {
                owner->showBgm = Random_GlobalBelow(3) + 0xa9;
                s16 *r = (s16 *)DebugVar_GetPtr(0, 0x4e);
                if (*r != 0) {
                    r = (s16 *)DebugVar_GetPtr(0, 0x4e);
                    s32 t = *r - 1;
                    if (t < 0) {
                        t = 0;
                    } else if (t > 3) {
                        t = 3;
                    }
                    owner->showBgm = t + 0xa9;
                }
            } else {
                u32 h = owner->songItem;
                s32 t;
                if (h >= 0x1323 && h <= 0x1368) {
                    t = h - 0x1323;
                } else {
                    t = -1;
                }
                owner->showBgm = t + 0x63;
            }
            Bgm_Request(0xf, (u16)owner->showBgm, 0x7f, 0);
            beatPoseStarted = 0;
            KkShowFx_Start();
            setScript(3);
        }
    }
}

void SpNpcRoostGuestTalk::scriptPerform() {
    BgmBeatPhase *p = (BgmBeatPhase *)Snd_GetBeatState();
    KkShowFx_Update();
    if (p != NULL) {
        if (p->seqVar2 == 1 && lastBeatState.seqVar2 == 1) {
            goto end;
        }
        s32 t4 = p->seqVar3;
        if (t4 != lastBeatState.seqVar3) {
            if (t4 == 2) {
                RoomCamera_KkShowResetShot();
                KkShowFx_CallUnk1de4();
            } else if ((u8)t4 <= 1) {
                RoomCamera_KkShowPickShot();
            }
        }
        s32 t1 = p->trackAnim;
        if (t1 != lastBeatState.trackAnim) {
            if (t1 == -1) {
                owner->faceAnim.setMouthTexture(sKkMouthM0);
            } else {
                owner->faceAnim.setMouthTexture(sKkMouthTextures[t1]);
            }
        }
        s32 t2 = p->seqVar0;
        if (t2 != lastBeatState.seqVar0 || p->seqVar4 != lastBeatState.seqVar4) {
            if (t2 == 1) {
                owner->lookAt.setManualAngles(0, 0, 0, 0x100, 0x200);
            } else {
                owner->lookAt.setManualAngles(0, -0xc18, 0, 0x100, 0x200);
            }
            u16 v = data_020c6cc8;
            if (beatPoseStarted == 0) {
                v = 0x28;
                beatPoseStarted = 1;
            }
            s32 t0 = p->seqVar4;
            if (t0 == 3) {
                owner->actionCtrl.requestPlayAnim(2, 0x103, 0, v, 0);
            } else if (t0 == 4) {
                owner->actionCtrl.requestPlayAnim(2, 0x104, 0, v, 0);
            }
        }
        if ((u8)(s8)(p->seqVar4 - 3) <= 1) {
            owner->model.curFrame = 0;
            owner->model.frameStep = p->beatFrame;
            owner->model.updateLayers3();
            owner->model.frameStep = 0;
        }
        {
            s32 t3 = p->seqVar2;
            if (t3 != lastBeatState.seqVar2) {
                if (t3 == 0) {
                    KkShowFx_Update();
                    KkShowFx_SetParam(0);
                    KkShowFx_CallUnk1f70();
                }
                if (p->seqVar2 == 1) {
                    owner->faceAnim.setMouthTexture(sKkMouthM0);
                    owner->faceAnim.resumeMouthMaterial();
                    owner->actionCtrl.requestStand(2, 0x28);
                }
            }
        }
    }
end:
    KkShowFx_CallUnk1f70();
    MI_CpuCopy8(p, &lastBeatState, sizeof(BgmBeatPhase));
    if (KkShowFx_GetState()) {
        owner->showTimer = 0x14;
        setScript(4);
    }
}

void SpNpcRoostGuestTalk::scriptEndPerformance() {
    u8 c0, c1, c2;
    u16 h;
    if (Math_CountDownU16(&owner->showTimer) == 0) {
        owner->showAccepted = 0;
        if (owner->isRandomSong != 0) {
            c0 = 0xb;
            window->setNextMessage(&c0, (void *)sRoostGuestMsgFiles[owner->guestType]);
        } else {
            h = owner->songItem;
            if (Pocket_AddItem(&h, 0) == 0) {
                c1 = 0xd;
                window->setNextMessage(&c1, (void *)sRoostGuestMsgFiles[owner->guestType]);
            } else {
                Talk_CheckAndSetPlayerFlag(0xd, 1);
                c2 = 0xc;
                window->setNextMessage(&c2, (void *)sRoostGuestMsgFiles[owner->guestType]);
            }
        }
        KkShowFx_Stop();
        Bgm_Release(owner->showBgm);
        owner->showTimer = 0x1e;
        LightSwitch_SetOff(1, 1);
        LightSwitch_SetOn(0, 0x1e, 0);
        setScript(5);
    }
}

void SpNpcRoostGuestTalk::scriptRestoreLook() {
    if (Math_CountDownU16(&owner->showTimer) == 0) {
        owner->lookAt.setManualAngles(0, 0, 0x1000, 0x276, 0x276);
        window->nextState = 1;
        setScript(0);
    }
}

BOOL SpNpcRoostGuest::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (act == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcRoostGuest::onInteractionEvent(u32 mode, u8) {
    switch (mode) {
    case 0:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        if (guestType == 7) {
            talk.setTalkMode(0);
        }
        changeAct(1);
        break;
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        if (hasSongRequest != 0) {
            talk.setTalkMode(1);
        } else {
            talk.setTalkMode(2);
        }
        changeAct(3);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL SpNpcRoostGuest::checkPlayerSeated() {
    if (showAccepted == 0) {
        return FALSE;
    }
    PlayerData_GetCurrent();
    VecFx32 v;
    v = *(VecFx32 *)PlayerActor_GetBodyPos(4);
    s32 a = 0;
    s32 b = 0;
    FieldPos_ToUnit(&a, &b, &v);
    if (PlayerActor_IsInAction(0x25, 4) != 0 && a == 9 && b == 0xd) {
        TalkRequest_AddPlayerTalk7(this, 0);
    }
    return TRUE;
}

extern "C" u16 RoostGuest_PickKKSong(void *self) {
    u16 arr[2];
    ItemPick_FromRange(&arr[0], 0x1323, 0x46, 0, 0, PlayerData_GetCurrent(), 0, 10, 0, 1);
    if (!Unk_ov068_0226c340_R(&arr[0])) {
        ItemPick_FromRange(&arr[1], 0x1323, 0x46, 0, 0, 0, 1, 10, 0, 1);
        arr[0] = arr[1];
    }
    return arr[0];
}

u32 SpNpcRoostGuest::getGuest() {
    return guestType;
}

extern "C" s32 SpNpcRoostGuest_GetGuest(void *p) { return static_cast<SpNpcRoostGuest *>(p)->SpNpcRoostGuest::getGuest(); }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0226c2e0) {
    HOST_OVERLAY_VAR(sRoostTexMof),
    HOST_OVERLAY_VAR(sRoostTexEnd),
    HOST_OVERLAY_VAR(sRoostMsgCf3),
    HOST_OVERLAY_VAR(sRoostTexPga),
    HOST_OVERLAY_VAR(sRoostModelPga),
    HOST_OVERLAY_VAR(sKkMouthM5),
    HOST_OVERLAY_VAR(sKkMouthM4),
    HOST_OVERLAY_VAR(sRoostTexPgb),
    HOST_OVERLAY_VAR(sRoostModelPgb),
    HOST_OVERLAY_VAR(sRoostGuestTexPaths),
    HOST_OVERLAY_VAR(sRoostMsgCf4),
    HOST_OVERLAY_VAR(sRoostModelWip),
    HOST_OVERLAY_VAR(sSpNpcRoostGuestProfile),
    HOST_OVERLAY_VAR(sRoostMsgCf2),
    HOST_OVERLAY_VAR(sRoostTexWip),
    HOST_OVERLAY_VAR(sRoostModelEnd),
    HOST_OVERLAY_VAR(sKkMouthM2),
    HOST_OVERLAY_VAR(sRoostGuestMsgFiles),
    HOST_OVERLAY_VAR(sRoostGuestModelPaths),
    HOST_OVERLAY_VAR(sKkMouthM1),
    HOST_OVERLAY_VAR(sRoostModelMof),
    HOST_OVERLAY_VAR(sRoostMsgDog),
    HOST_OVERLAY_VAR(sRoostModelOtt),
    HOST_OVERLAY_VAR(sRoostTexPoo),
    HOST_OVERLAY_VAR(sRoostTexOtt),
    HOST_OVERLAY_VAR(sKkShowScripts),
    HOST_OVERLAY_VAR(sRoostMsgCf7),
    HOST_OVERLAY_VAR(sKkMouthM3),
    HOST_OVERLAY_VAR(sRoostTexXct),
    HOST_OVERLAY_VAR(sRoostMsgCf1),
    HOST_OVERLAY_VAR(sKkMouthTextures),
    HOST_OVERLAY_VAR(sRoostMsgCf6),
    HOST_OVERLAY_VAR(sRoostMsgCf5),
    HOST_OVERLAY_VAR(sRoostModelXct),
    HOST_OVERLAY_VAR(sKkMouthM0),
    HOST_OVERLAY_VAR(sSpNpcRoostGuestActTable),
    HOST_OVERLAY_VAR(sRoostModelPoo),
    HOST_OVERLAY_VARS_END
};

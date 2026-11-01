#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "talk/TalkStartMsg.h"
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
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "net/CommManager.h"
#include "npc/NpcLookAt.h"
#include "player/PlayerData.h"
#include "save/MuseumData.h"
#include "save/SaveData.h"
#include "player/PlayerErrands.h"
#include "talk/ChoiceList.h"
#include "talk/TalkWindowState.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206fde4.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov047/unk_ov047_02258de0.h"


class ActorTalkRequest;
class NpcActor;
class SpNpcBlathers;
class SpNpcBlathersTalk;


struct SpNpcBlathersStartLocal {
    u8 lo : 2;
    u8 b : 3;
    u8 c : 3;
    u8 pad_01;
    u16 npcHandle;
};


struct Unk_ov047_0225a3e4_Msg {
    u8 msgIndex;
    u8 pad_01;
    u16 item;
    u16 cmpItem;
};

struct SpNpcBlathersMsgLocal {
    u8 msgIndex;
    u8 pad_01;
    u16 cmpItem;
};


typedef BOOL (*PocketFilterFn)(u16 *p, s32 m);
typedef BOOL (SpNpcBlathers::*SpNpcBlathersActFn)();

extern SaveData gSaveData;

static inline MuseumData *Museum() { return (MuseumData *)gSaveData.museum; }

extern "C" {
extern CommManager *gCommManager;
extern u16 data_020c6cc8;
extern s32 data_020c6d1c;
extern VecFx32 gVec3Zero;

BOOL Talk_IsInOwnTown();
void Talk_AdvanceDrama(void *self, void *out);
BOOL Talk_IsDramaPending(void *self, void *out, s32 x);
void TalkRequest_SetTargetDone(void *self);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 Clock_GetTimeOfDay();
u16 Math_CountDownU16(void *p);
s32 strncmp(const char *a, const char *b, u32 n);
u32 strlen(const char *s);
}












class SpNpcBlathersTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcBlathersTalk::*Fn)();
    typedef void (SpNpcBlathersTalk::*Fn1)(u32);
    typedef void (SpNpcBlathersTalk::*Fni)(s32);

    SpNpcBlathersTalk();
    virtual ~SpNpcBlathersTalk();
    virtual void resetMsg();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 a);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    void onDeliveryChoice(u32 a);
    void onDonateMoreChoice(u32 a);
    void onAnythingElseChoice(u32 a);
    void onAppraiseDonatedFossilChoice(u32 a);
    void onAppraiseAnotherChoice(u32 a);
    void onKeepFossilChoice(u32 a);
    void onDonateMoreChoice2(u32 a);
    void onDonationOfferChoice(u32 a);
    void onMainMenuChoice(u32 choice);
    void dispatchChoice(u32 a);
    void onDramaChoice(u32 unused);
    void openExhibitList();
    void returnItemAndAskMore();
    void onAlreadyDonated();
    void showFishComment();
    void showInsectComment();
    void onPaintingDonated();
    void onExhibitCompleted();
    void onFossilPartDonated();
    void returnAppraisedFossil();
    void offerFossilDonation();
    void afterFossilIdentified();
    void appraiseFossil();
    void returnHeldItem();
    void showMuseumMenu();
    void returnItemAndAskShowMore();
    void returnItemAndShowMenu();
    void openAppraisalPicker();
    void openDonationPicker();
    void commitDonation();
    void attachOwner(SpNpcBlathers *owner);
    void scriptDeliveryItemChosen();
    void scriptExhibitListClosed();
    void scriptAppraisalItemChosen();
    void scriptCloseItemSelect();
    void scriptDonationItemChosen();
    void setNextScript(s32 idx);
    void setScript(s32 idx);

    /* 0xac */ s32 dramaTalk;
    /* 0xb0 */ SpNpcBlathers *ownerNpc;
    /* 0xb4 */ Fn script;
    /* 0xbc */ Fn nextScript;
    /* 0xc4 */ s32 pocketSlot;
    /* 0xc8 */ u8 appraisalFlow;
    /* 0xc9 */ u8 pad_c9;
    /* 0xca */ u16 item;
    /* 0xcc */ s32 nextMsg;
};

class SpNpcBlathers : public SpNpcActor {
public:
    SpNpcBlathers() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 cmd, u8 arg);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct08();
    BOOL setupAct08();
    BOOL mainAct07();
    BOOL setupAct07();
    BOOL mainAct06();
    BOOL setupAct06();
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
    SpNpcBlathersTalk talk;
    u8 dramaShown;
    u8 pad_729;
    u16 dramaTimer;
    u16 standBlend;
    u16 sleepTimer;
    s16 homeAngle;
    u8 isAsleep;
    u8 pad_733;
    u16 sleepBlend;
    s16 pad_736;
    s32 effectHandle;
};


struct SpNpcBlathersActEntry {
    BOOL (SpNpcBlathers::*enter)();
    BOOL (SpNpcBlathers::*exit)();
};


extern "C" void SpNpcBlathersTalk_GetScript(SpNpcBlathersTalk *self, SpNpcBlathersTalk::Fn *out, s32 idx);
#define sSpNpcBlathersKey ((char *)"sp_npc_owl")
#define sSpNpcBlathersSequence4Key ((char *)"sp_etc_sequence4")
#define sSpNpcBlathersDramaKey ((char *)"sp_npc_drama1")
extern "C" u8 sSpNpcBlathersModelPath[];
extern "C" u8 sSpNpcBlathersTexturePath[];
extern "C" const u8 sSpNpcBlathersDramaMsgTable[32];
extern "C" ActorProfile sSpNpcBlathersProfile;

struct SpNpcBlathersMsgByte {
    u8 v;
    SpNpcBlathersMsgByte() {}
};

struct SpNpcBlathersChoiceHandler {
    u32 id;
    void (SpNpcBlathersTalk::*fn)(u32);
};

typedef void (SpNpcBlathersTalk::*SpNpcBlathersTalkFn)();

struct SpNpcBlathersMessageEndHandler {
    u32 id;
    SpNpcBlathersTalkFn fn;
};

static inline BOOL Unk_ov047_022596e8_IsNoneT(u16 *p, u16 &v) {
    BOOL ok;
    if (Item_IsFurniture(p)) {
        v = 0xfff1;
        if (Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&v)) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
    } else {
        if (*p == 0xfff1) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
    }
    return ok;
}

static inline BOOL Unk_ov047_022596e8_IsNone(u16 *p) {
    u16 v;
    return Unk_ov047_022596e8_IsNoneT(p, v);
}

static inline BOOL Unk_ov047_0225a4a8_R(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov047_0225a3e4_Same(u16 *p, u16 *t) {
    if (Item_IsFurniture(p)) {
        *t = 0xfff1;
        s32 a = Item_GetFurnitureIndex(p);
        s32 b = Item_GetFurnitureIndex(t);
        if (a == b) {
            return TRUE;
        }
        return FALSE;
    }
    if (*p == 0xfff1) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov047_0225a864_R(u16 *p, u32 lo, u32 hi) {
    return (*p >= lo && *p <= hi) ? TRUE : FALSE;
}

static inline s32 Unk_ov047_0225a5e8_Idx(u32 v, u32 lo, u32 hi) {
    if (v >= lo && v <= hi) {
        return v - lo;
    }
    return -1;
}

extern "C" void *SpNpcBlathers_Create() {
    return new SpNpcBlathers();
}

BOOL SpNpcBlathers::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    standBlend = data_020c6cc8;
    effectHandle = -1;
    return TRUE;
}

BOOL SpNpcBlathers::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    u8 buf[8];
    dramaShown = 0;
    homeAngle = rotY;
    dramaTimer = 0xff;
    collider.groups |= 2;
    sleepBlend = 0;
    if (((CommManager *)(gCommManager))->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
        collider.groups |= 2;
        if (NetArea_IsLocalOwner()) {
            position.x = 0xf000;
            position.z = 0x15000;
            rotY = 0;
            moveAngleY = 0;
            changeAct(0);
        } else {
            changeAct(6);
        }
        return TRUE;
    }
    if (Clock_GetTimeOfDay() == 2 || Clock_GetTimeOfDay() == 3 || Talk_IsDramaPending(this, buf, 1)) {
        changeAct(0);
    } else {
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcBlathers::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    if (effectHandle != -1) {
        Effect_End(effectHandle);
        effectHandle = -1;
    }
    return TRUE;
}

u8 *SpNpcBlathers::getTexturePath() { return sSpNpcBlathersTexturePath; }

u8 *SpNpcBlathers::getModelPath() { return sSpNpcBlathersModelPath; }

BOOL SpNpcBlathers::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcBlathersActTable[act].exit) {
        r = (this->*sSpNpcBlathersActTable[act].exit)();
    }
    return r;
}

void SpNpcBlathers::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcBlathersActTable[state].enter) {
        ok = (this->*sSpNpcBlathersActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcBlathers::setupAct00() {
    u8 buf[8];
    dramaTimer = 0xff;
    ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, standBlend);
    if (dramaShown == 0) {
        if (Talk_IsDramaPending(this, buf, 1)) {
            dramaTimer = Random_GlobalBelow(5) * 0x14 + 0x64;
        }
    }
    isAsleep = 0;
    standBlend = data_020c6cc8;
    sleepTimer = 0x78;
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct00() {
    if (dramaTimer != 0xff) {
        if (Math_CountDownU16(&dramaTimer) == 0) {
            changeAct(5);
        }
        return TRUE;
    }
    if (((CommManager *)(gCommManager))->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0 || Clock_GetTimeOfDay() == 2 ||
        Clock_GetTimeOfDay() == 3) {
        return TRUE;
    }
    if (Math_CountDownU16(&sleepTimer) == 0) {
        sleepBlend = 0x18;
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcBlathers::setupAct01() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct01() {
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcBlathers::setupAct02() {
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xf0, 0, sleepBlend, 0);
    isAsleep = 1;
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct02() {
    if (effectHandle == -1) {
        effectHandle = Effect_Create(0x3c, &jointPos[0], &rotY, 0);
    } else {
        Effect_SetPosition(effectHandle, &jointPos[0], &rotY, 0);
    }
    return TRUE;
}

BOOL SpNpcBlathers::setupAct03() {
    NpcActor *p = (NpcActor *)talk.getTalkPlayer();
    s32 r = 0;
    if (p) {
        r = getAngleTo(p);
    }
    if (effectHandle != -1) {
        Effect_End(effectHandle);
        effectHandle = -1;
    }
    ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct03() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        isAsleep = 0;
        TalkRequest_SetTargetDone(this);
        changeAct(4);
    }
    return TRUE;
}

BOOL SpNpcBlathers::mainAct04() { return TRUE; }

BOOL SpNpcBlathers::setupAct06() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct06() {
    if (isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        u32 x, t;
        if (((NpcActor *)(this))->netGetSlots(&a, &b) && ((x = a), x == (t = gCommManager->myAid)) && x == b) {
            netSetSlotsIfOwner(1, t, t);
            talk.resetMsg();
            ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
            changeAct(3);
        } else if (NetArea_IsLocalOwner() && b == 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcBlathers::setupAct07() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct07() {
    if (isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b) && a == 4 && NetArea_IsLocalOwner()) {
            netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcBlathers::setupAct08() { return TRUE; }

BOOL SpNpcBlathers::mainAct08() { return TRUE; }


void SpNpcBlathersTalk::onTaskDone(u32) {
    if (script) {
        (this->*script)();
        Fn n = NULL;
        script = n;
        if (nextScript) {
            script = nextScript;
            nextScript = n;
        }
    }
}

extern "C" void SpNpcBlathersTalk_GetScript(SpNpcBlathersTalk *self, SpNpcBlathersTalk::Fn *out, s32 idx) {
    static SpNpcBlathersTalk::Fn tbl[5] = {
        &SpNpcBlathersTalk::scriptDonationItemChosen,
        &SpNpcBlathersTalk::scriptAppraisalItemChosen,
        &SpNpcBlathersTalk::scriptDeliveryItemChosen,
        &SpNpcBlathersTalk::scriptExhibitListClosed,
        &SpNpcBlathersTalk::scriptCloseItemSelect,
    };
    *out = tbl[idx];
}

void SpNpcBlathersTalk::setScript(s32 idx) {
    SpNpcBlathersTalk_GetScript(this, &script, idx);
}

void SpNpcBlathersTalk::setNextScript(s32 idx) {
    SpNpcBlathersTalk_GetScript(this, &nextScript, idx);
}

extern "C" BOOL SpNpcBlathers_IsDonatableItem(u16 *p, s32 m) {
    if (m == 0) {
        BOOL a = Unk_ov047_0225a4a8_R(p, 0x450c, 0x45db);
        BOOL b = Unk_ov047_0225a864_R(p, 0x3934, 0x3983);
        BOOL c = Unk_ov047_0225a864_R(p, 0x38e4, 0x3933);
        BOOL d = Unk_ov047_0225a864_R(p, 0x12e8, 0x131f);
        BOOL e = Unk_ov047_0225a864_R(p, 0x12b0, 0x12e7);
        BOOL f = Unk_ov047_0225a864_R(p, 0x3894, 0x38e3);
        BOOL g = Unk_ov047_0225a864_R(p, 0x1549, 0x1549);
        return b | (c | (d | (e | (f | (g | a)))));
    }
    return FALSE;
}

void SpNpcBlathersTalk::scriptDonationItemChosen() {
    void *o = window;
    SpNpcBlathersMsgLocal m;
    m.msgIndex = 0x22;
    if (MenuCtrl_IsResultOk()) {
        MsgString9B ob;
        pocketSlot = -1;
        pocketSlot = MenuCtrl_GetIndex();
        item = Pocket_GetItem(pocketSlot);
        if (!Unk_ov047_0225a3e4_Same(&item, &m.cmpItem)) {
            ((ActorTalkRequest *)(this))->setItemNameSlot(&item, 0, 7);
            if (Unk_ov047_0225a4a8_R(&item, 0x1549, 0x1549)) {
                m.msgIndex = 0x21;
            } else {
                MuseumData *g = Museum();
                if (g->isDonated(&item) == 0) {
                    if (Unk_ov047_0225a4a8_R(&item, 0x450c, 0x45db)) {
                        appraisalFlow = 0;
                        m.msgIndex = 0x25;
                    } else if (item >= 0x3894 && item <= 0x38e3) {
                        m.msgIndex = Random_GlobalBelow(3) + 0x2e;
                    } else if (item >= 0x12b0 && item <= 0x12e7) {
                        if (Unk_ov047_0225a5e8_Idx(item, 0x12b0, 0x12e7) != 0x34) {
                            m.msgIndex = 0x32;
                        } else {
                            m.msgIndex = 0x33;
                        }
                    } else if (item >= 0x12e8 && item <= 0x131f) {
                        m.msgIndex = 0x35;
                    } else if (item >= 0x38e4 && item <= 0x3933) {
                        s32 idx = item >= 0x38e4 && item <= 0x3933 ? (s32)(item - 0x38e4) >> 2 : -1;
                        item = (u32)idx < 0x14 ? idx * 4 + 0x3934 : 0x3934;
                        s32 t = pocketSlot;
                        if (t >= 0) {
                            Pocket_SetItem(&item, 0, t);
                        }
                        m.msgIndex = 0x42;
                    } else if (item >= 0x3934 && item <= 0x3983) {
                        m.msgIndex = 0x43;
                    }
                } else {
                    switch (g->getDonationState(&item)) {
                    case 0:
                        m.msgIndex = 0x39;
                        break;
                    case 1:
                        if (g->getDonorName(&ob, &item)) {
                            ((TalkWindowState *)(o))->setSlot(0, &ob);
                        }
                        m.msgIndex = 0x38;
                        break;
                    case 2:
                        m.msgIndex = 0x37;
                        break;
                    }
                }
            }
            ((ActorTalkRequest *)(this))->requestTakeItem(&item, 0, 10, 0);
            setNextScript(4);
        }
    } else {
        item = 0xfff1;
        ((ActorTalkRequest *)(this))->requestReopenWindow();
    }
    ((TalkWindowState *)(o))->setNextMessage((u8 *)(&m), sSpNpcBlathersKey);
}

void SpNpcBlathersTalk::scriptCloseItemSelect() {
    ((ActorTalkRequest *)(this))->requestReopenWindow();
}

extern "C" BOOL SpNpcBlathers_IsUnidentifiedFossil(u16 *p, s32 m) {
    if (m == 0) {
        return Unk_ov047_0225a4a8_R(p, 0x1549, 0x1549);
    }
    return FALSE;
}

void SpNpcBlathersTalk::scriptAppraisalItemChosen() {
    void *o = window;
    SpNpcBlathersMsgLocal m;
    m.msgIndex = 0x22;
    if (MenuCtrl_IsResultOk()) {
        pocketSlot = MenuCtrl_GetIndex();
        item = Pocket_GetItem(pocketSlot);
        ((ActorTalkRequest *)(this))->requestTakeItem(&item, 0, 10, 0);
        m.msgIndex = 0x19;
    } else {
        item = 0xfff1;
        ((ActorTalkRequest *)(this))->requestReopenWindow();
    }
    setNextScript(4);
    ((TalkWindowState *)(o))->setNextMessage((u8 *)(&m), sSpNpcBlathersKey);
}

void SpNpcBlathersTalk::scriptExhibitListClosed() {
    void *o = window;
    if (MenuCtrl_IsResultOk()) {
        u8 cmd = 0x13;
        MuseumData *g = Museum();
        s32 v = g->getDonationPercent();
        if (v == 0) {
            cmd = 0x10;
        } else if (v <= 0x1e000) {
            cmd = 0x11;
        } else if (v <= 0x46000) {
            cmd = 0x12;
        } else if (g->isComplete()) {
            cmd = 0x49;
        }
        ((TalkWindowState *)(o))->setNextMessage((u8 *)(&cmd), sSpNpcBlathersKey);
    }
}

extern "C" BOOL SpNpcBlathers_IsDeliveryItem(u16 *p, s32 m) {
    if (m == 2) {
        return Unk_ov047_0225a4a8_R(p, 0x155f, 0x1560);
    }
    return FALSE;
}

void SpNpcBlathersTalk::scriptDeliveryItemChosen() {
    void *o = window;
    Unk_ov047_0225a3e4_Msg m;
    m.msgIndex = 0xe8;
    PlayerData *r7 = PlayerData_GetCurrent();
    if (MenuCtrl_IsResultOk() && Talk_IsInOwnTown()) {
        s32 r5 = MenuCtrl_GetIndex();
        m.item = Pocket_GetItem(r5);
        if (r5 >= 0) {
            Pocket_RemoveItem(r5);
        }
        if (!Unk_ov047_0225a3e4_Same(&m.item, &m.cmpItem)) {
            ((ActorTalkRequest *)(this))->requestTakeItem(&m.item, 2, 5, 0);
        }
        ((ErrandRecord *)ParcelErrand_GetRecord(&(r7->getErrands())->parcelErrand))->setStep(1);
        m.msgIndex = 0xe7;
    }
    ((TalkWindowState *)(o))->setNextMessage((u8 *)(&m), sSpNpcBlathersKey);
}

BOOL SpNpcBlathers::setupAct05() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0xa, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcBlathers::mainAct05() {
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 10) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            standBlend = 0x18;
            changeAct(0);
        }
    }
    return TRUE;
}

SpNpcBlathersTalk::SpNpcBlathersTalk() {
    item = 0xfff1;
}

SpNpcBlathersTalk::~SpNpcBlathersTalk() {}

void SpNpcBlathersTalk::resetMsg() {
    ActorTalkRequest::resetMsg();
    pocketSlot = -1;
    item = 0xfff1;
    Fn t = NULL;
    script = t;
    nextScript = t;
}

void SpNpcBlathersTalk::attachOwner(SpNpcBlathers *owner) {
    resetMsg();
    ownerNpc = owner;
    dramaTalk = 0;
    pocketSlot = -1;
    appraisalFlow = 0;
    item = 0xfff1;
}

void SpNpcBlathersTalk::start(TalkStartMsg *out) {
    if (GameStart_IsActive()) {
        out->msgKey = (const char *)sSpNpcBlathersSequence4Key;
        out->msgIndex = 8;
        return;
    }
    out->msgKey = (const char *)sSpNpcBlathersKey;
    ParcelErrand *r7 = &(PlayerData_GetCurrent()->getErrands())->parcelErrand;
    void *g = gCommManager;
    SpNpcBlathersStartLocal l;
    if (!((CommManager *)(g))->isOnline() && *DebugVar_GetPtr(0, 0x4a) == 0) {
        l.npcHandle = 0xd00c;
        if (ParcelErrand_IsFor(r7, &l.npcHandle)) {
            if (ownerNpc->isAsleep == 0) {
                out->msgIndex = 0xe6;
            } else {
                out->msgIndex = 0xe5;
            }
            return;
        }
    }
    if (ownerNpc->dramaShown == 0 && dramaTalk != 1 && !((CommManager *)(g))->isOnline() && *DebugVar_GetPtr(0, 0x4a) == 0) {
        if (Talk_IsDramaPending(ownerNpc, &l, 1)) {
            out->msgKey = (const char *)sSpNpcBlathersDramaKey;
            out->msgIndex = (sSpNpcBlathersDramaMsgTable + l.b * 6)[l.c];
            dramaTalk = 1;
            ownerNpc->dramaShown = 1;
            return;
        }
    }
    dramaTalk = 0;
    if (Talk_IsInOwnTown() == 0) {
        if (TownSessionState_TestFlag(TownSessionState_Get(), 9) == 0) {
            if (ownerNpc->isAsleep != 0) {
                out->msgIndex = 4;
            } else {
                out->msgIndex = 5;
            }
        } else {
            if (ownerNpc->isAsleep != 0) {
                out->msgIndex = 6;
            } else {
                out->msgIndex = 7;
            }
        }
        TownSessionState_SetFlag(TownSessionState_Get(), 9);
    } else if (TownSessionState_TestFlag(TownSessionState_Get(), 9) == 0) {
        if (Museum()->isComplete()) {
            if (ownerNpc->isAsleep != 0) {
                out->msgIndex = 0;
            } else {
                out->msgIndex = 1;
            }
        } else {
            if (ownerNpc->isAsleep != 0) {
                out->msgIndex = 8;
            } else {
                out->msgIndex = 9;
            }
        }
        ownerNpc->isAsleep = 0;
        TownSessionState_SetFlag(TownSessionState_Get(), 9);
    } else if (Museum()->isComplete()) {
        if (ownerNpc->isAsleep != 0) {
            out->msgIndex = 3;
            ownerNpc->isAsleep = 0;
        } else {
            out->msgIndex = 2;
        }
    } else {
        if (ownerNpc->isAsleep != 0) {
            out->msgIndex = 10;
            ownerNpc->isAsleep = 0;
        } else {
            out->msgIndex = 11;
        }
    }
}

void SpNpcBlathersTalk::commitDonation() {
    if (!Unk_ov047_022596e8_IsNone(&item)) {
        void *p = PlayerData_GetCurrent();
        Museum()->donate(&item);
        gSaveData.setFlag(0xc);
        ((PlayerData *)(p))->setFlag(8);
        if (pocketSlot >= 0) {
            Pocket_RemoveItem(pocketSlot);
            pocketSlot = -1;
        }
        item = 0xfff1;
    }
}

SpNpcBlathersActEntry sSpNpcBlathersActTable[9] = {
    {&SpNpcBlathers::setupAct00, &SpNpcBlathers::mainAct00},
    {&SpNpcBlathers::setupAct01, &SpNpcBlathers::mainAct01},
    {&SpNpcBlathers::setupAct02, &SpNpcBlathers::mainAct02},
    {&SpNpcBlathers::setupAct03, &SpNpcBlathers::mainAct03},
    {NULL, &SpNpcBlathers::mainAct04},
    {&SpNpcBlathers::setupAct05, &SpNpcBlathers::mainAct05},
    {&SpNpcBlathers::setupAct06, &SpNpcBlathers::mainAct06},
    {&SpNpcBlathers::setupAct07, &SpNpcBlathers::mainAct07},
    {&SpNpcBlathers::setupAct08, &SpNpcBlathers::mainAct08},
};
extern "C" ActorProfile sSpNpcBlathersProfile = {(void *(*)())SpNpcBlathers_Create, 0x6e, 0x74, 2, 0x5000, 0x5000, 0x3e800};
SpNpcBlathersMessageEndHandler SpNpcBlathersTalk_onMessageEnd_tbl[35] = {
        {0x14, &SpNpcBlathersTalk::openDonationPicker}, {0x15, &SpNpcBlathersTalk::returnHeldItem},
        {0x16, &SpNpcBlathersTalk::openAppraisalPicker}, {0x17, &SpNpcBlathersTalk::openAppraisalPicker},
        {0x18, &SpNpcBlathersTalk::showMuseumMenu}, {0x19, &SpNpcBlathersTalk::appraiseFossil},
        {0x1a, &SpNpcBlathersTalk::afterFossilIdentified}, {0x1b, &SpNpcBlathersTalk::afterFossilIdentified},
        {0x1c, &SpNpcBlathersTalk::afterFossilIdentified}, {0x1d, &SpNpcBlathersTalk::offerFossilDonation},
        {0x1f, &SpNpcBlathersTalk::returnAppraisedFossil}, {0x26, &SpNpcBlathersTalk::onFossilPartDonated},
        {0x29, &SpNpcBlathersTalk::onExhibitCompleted}, {0x2e, &SpNpcBlathersTalk::onPaintingDonated},
        {0x2f, &SpNpcBlathersTalk::onPaintingDonated}, {0x30, &SpNpcBlathersTalk::onPaintingDonated},
        {0x31, &SpNpcBlathersTalk::onExhibitCompleted}, {0x32, &SpNpcBlathersTalk::showInsectComment},
        {0x33, &SpNpcBlathersTalk::showInsectComment}, {0x34, &SpNpcBlathersTalk::onExhibitCompleted},
        {0x35, &SpNpcBlathersTalk::showFishComment}, {0x36, &SpNpcBlathersTalk::onExhibitCompleted},
        {0x37, &SpNpcBlathersTalk::onAlreadyDonated}, {0x38, &SpNpcBlathersTalk::onAlreadyDonated},
        {0x39, &SpNpcBlathersTalk::onAlreadyDonated}, {0x3a, &SpNpcBlathersTalk::returnItemAndAskMore},
        {0x3b, &SpNpcBlathersTalk::returnItemAndAskMore}, {0x3c, &SpNpcBlathersTalk::returnItemAndAskMore},
        {0x3d, &SpNpcBlathersTalk::returnItemAndAskMore}, {0x3f, &SpNpcBlathersTalk::openExhibitList},
        {0x40, &SpNpcBlathersTalk::showMuseumMenu}, {0x41, &SpNpcBlathersTalk::showMuseumMenu},
        {0x42, &SpNpcBlathersTalk::returnItemAndShowMenu}, {0x43, &SpNpcBlathersTalk::returnItemAndShowMenu},
        {0x6a, &SpNpcBlathersTalk::returnItemAndAskShowMore},
    };
void SpNpcBlathersTalk::onMessageEnd(u32) {
    void *p;
    volatile u8 hdr[4];
    volatile u16 tt[3];
    if (GameStart_IsActive()) {
        goto end;
    }
    if (strncmp((char *)&fileName, sSpNpcBlathersKey, strlen(sSpNpcBlathersKey)) != 0) {
        goto end;
    }
    if ((s32)msgIndex < 0xc) {
        if (gSaveData.testFlag(0xc)) {
            nextMsg = 0x44;
        } else {
            nextMsg = 0xc;
        }
        hdr[0] = nextMsg;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)((u8 *)&hdr[0]), sSpNpcBlathersKey);
        goto end;
    }
    if (msgIndex == 0x33 || ((s32)msgIndex >= 0x6e && (s32)msgIndex <= 0xa5)) {
        commitDonation();
        if (Museum()->isInsectsComplete()) {
            nextMsg = 0x34;
        } else {
            nextMsg = 0x27;
        }
        ((ActorTalkRequest *)(this))->requestKeepItem();
        hdr[1] = nextMsg;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)((u8 *)&hdr[1]), sSpNpcBlathersKey);
        goto end;
    }
    if ((s32)msgIndex >= 0xaa && (s32)msgIndex <= 0xe1) {
        commitDonation();
        if (Museum()->isFishComplete()) {
            nextMsg = 0x36;
        } else {
            nextMsg = 0x27;
        }
        ((ActorTalkRequest *)(this))->requestKeepItem();
        hdr[2] = nextMsg;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)((u8 *)&hdr[2]), sSpNpcBlathersKey);
        goto end;
    }
    p = PlayerData_GetCurrent();
    nextMsg = 0xff;
    u32 i;
    i = 0;
    u8 *pid;
    pid = &msgIndex;
    SpNpcBlathersMessageEndHandler *tp;
    tp = SpNpcBlathersTalk_onMessageEnd_tbl;
    goto test;
loop:
    u32 ida;
    ida = tp[i].id;
    u32 idb;
    idb = *pid;
    if (ida == idb) {
        (this->*tp[i].fn)();
    }
    i++;
test:
    if (i < 0x23) goto loop;
    s32 v50;
    v50 = *(volatile u8 *)&msgIndex;
    if (v50 >= 0x50 && v50 <= 0x67) {
        if (Museum()->isFossilsComplete()) {
            nextMsg = 0x29;
        } else if (appraisalFlow == 0) {
            nextMsg = 0x27;
        } else {
            nextMsg = 0x20;
        }
        item = 0xfff1;
        ((ActorTalkRequest *)(this))->requestKeepItem();
    }
    if (msgIndex == 0x25 || msgIndex == 0x2c || msgIndex == 0x2d || msgIndex == 0x69) {
        if (!Unk_ov047_022596e8_IsNoneT(&item, *(u16 *)&tt[0])) {
            MuseumData *g = Museum();
            s32 a, b, r;
            g->donate(&item);
            gSaveData.setFlag(0xc);
            ((PlayerData *)(p))->setFlag(8);
            if (pocketSlot >= 0) {
                Pocket_RemoveItem(pocketSlot);
                pocketSlot = -1;
            }
            a = Item_GetFossilGroup(&item);
            b = Fossil_CountInGroup(a);
            r = Museum_CountDonatedFossilsInGroup(g, a);
            if (b == 1) {
                if (msgIndex == 0x2d) {
                    if (!Unk_ov047_022596e8_IsNoneT(&item, *(u16 *)&tt[1])) {
                        nextMsg = (u8)(a + 0x50);
                    }
                } else {
                    nextMsg = 0x2d;
                }
            } else if (b == r) {
                if (!Unk_ov047_022596e8_IsNoneT(&item, *(u16 *)&tt[2])) {
                    nextMsg = (u8)(a + 0x50);
                }
            } else {
                nextMsg = 0x26;
            }
        }
    }
    if (nextMsg != 0xff) {
        hdr[3] = nextMsg;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)((u8 *)&hdr[3]), sSpNpcBlathersKey);
    }
end:;
}

void SpNpcBlathersTalk::openDonationPicker() {
    ((ActorTalkRequest *)(this))->setPocketFilter(SpNpcBlathers_IsDonatableItem, 0xd, 1);
    ((ActorTalkRequest *)(this))->openSubScene(0);
    setScript(0);
}

void SpNpcBlathersTalk::openAppraisalPicker() {
    ((ActorTalkRequest *)(this))->setPocketFilter(SpNpcBlathers_IsUnidentifiedFossil, 0xd, 1);
    ((ActorTalkRequest *)(this))->openSubScene(0);
    setScript(1);
}

void SpNpcBlathersTalk::returnItemAndShowMenu() {
    ((ActorTalkRequest *)(this))->requestReturnItem();
    showMuseumMenu();
}

void SpNpcBlathersTalk::returnItemAndAskShowMore() {
    ((ActorTalkRequest *)(this))->requestReturnItem();
    nextMsg = 0x6b;
}

void SpNpcBlathersTalk::showMuseumMenu() {
    if (gSaveData.testFlag(0xc)) {
        nextMsg = 0x46;
    } else {
        nextMsg = 0x45;
    }
}

void SpNpcBlathersTalk::returnHeldItem() {
    if (item != 0xfff1) {
        ((ActorTalkRequest *)(this))->requestReturnItem();
    }
}

void SpNpcBlathersTalk::appraiseFossil() {
    u16 bufa, bufb;
    if (!Unk_ov047_022596e8_IsNone(&item)) {
        void *p = PlayerData_GetCurrent();
        ((PlayerData *)(p))->setFlag(0x35);
        ItemPick_FromRange(&bufb, 0x450c, 0x34, 0, 0, 0, 1, 10, 0, 1);
        item = bufb;
        if (pocketSlot >= 0) {
            Pocket_SetItem(&item, 0, pocketSlot);
        }
        ((ActorTalkRequest *)(this))->setItemNameSlot(&item, 0, 7);
        ItemPick_FromRange(&bufa, 0x450c, 0x34, &item, 1, 0, 1, 10, 0, 1);
        ((ActorTalkRequest *)(this))->setItemNameSlot(&bufa, 1, 7);
    }
    nextMsg = (u8)(Random_GlobalBelow(3) + 0x1a);
}

void SpNpcBlathersTalk::afterFossilIdentified() {
    if (appraisalFlow == 0) {
        if (((CommManager *)(gCommManager))->isOnline() == 0 && *DebugVar_GetPtr(0, 0x4a) == 0 && Talk_IsInOwnTown() != 0 &&
            Museum()->isDonated(&item) == 0) {
            nextMsg = 0x69;
        } else {
            nextMsg = 0x6a;
        }
    } else {
        nextMsg = 0x1d;
    }
}

void SpNpcBlathersTalk::offerFossilDonation() {
    if (((CommManager *)(gCommManager))->isOnline() != 0 || *DebugVar_GetPtr(0, 0x4a) != 0) {
        ((ActorTalkRequest *)(this))->requestReturnItem();
        nextMsg = 0x20;
    } else if (Talk_IsInOwnTown() != 0 && Museum()->isDonated(&item) == 0) {
        nextMsg = 0x1e;
    } else {
        ((ActorTalkRequest *)(this))->requestReturnItem();
        nextMsg = 0x20;
    }
}

void SpNpcBlathersTalk::returnAppraisedFossil() {
    ((ActorTalkRequest *)(this))->requestReturnItem();
    nextMsg = 0x20;
}

void SpNpcBlathersTalk::onFossilPartDonated() {
    ((ActorTalkRequest *)(this))->requestKeepItem();
    commitDonation();
    if (appraisalFlow == 0) {
        nextMsg = 0x27;
    } else {
        nextMsg = 0x20;
    }
}

void SpNpcBlathersTalk::onExhibitCompleted() {
    if (Museum()->isComplete()) {
        nextMsg = 0x2a;
    } else {
        nextMsg = 0x2b;
    }
}

void SpNpcBlathersTalk::onPaintingDonated() {
    commitDonation();
    if (Museum()->isPaintingsComplete()) {
        nextMsg = 0x31;
    } else {
        nextMsg = 0x27;
    }
    ((ActorTalkRequest *)(this))->requestKeepItem();
}

void SpNpcBlathersTalk::showInsectComment() {
    if (msgIndex == 0x32) {
        if (!Unk_ov047_022596e8_IsNone(&item)) {
            BOOL f = FALSE;
            u32 v = item;
            if (v >= 0x12b0 && v <= 0x12e7) {
                f = TRUE;
            }
            s32 x;
            if (f) {
                x = v - 0x12b0;
            } else {
                x = -1;
            }
            nextMsg = (u8)(x + 0x6e);
        }
    }
}

void SpNpcBlathersTalk::showFishComment() {
    BOOL eq;
    if (Item_IsFurniture(&item)) {
        u16 t = 0xfff1;
        s32 x = Item_GetFurnitureIndex(&item);
        if (x == Item_GetFurnitureIndex(&t)) {
            eq = TRUE;
        } else {
            eq = FALSE;
        }
    } else if (item == 0xfff1) {
        eq = TRUE;
    } else {
        eq = FALSE;
    }
    if (!eq) {
        BOOL f = FALSE;
        u32 v = item;
        if (v >= 0x12e8 && v <= 0x131f) {
            f = TRUE;
        }
        s32 t;
        if (f) {
            t = v - 0x12e8;
        } else {
            t = -1;
        }
        nextMsg = (u8)(t + 0xaa);
    }
}

void SpNpcBlathersTalk::onAlreadyDonated() {
    BOOL eq;
    if (Item_IsFurniture(&item)) {
        u16 t = 0xfff1;
        s32 x = Item_GetFurnitureIndex(&item);
        if (x == Item_GetFurnitureIndex(&t)) {
            eq = TRUE;
        } else {
            eq = FALSE;
        }
    } else if (item == 0xfff1) {
        eq = TRUE;
    } else {
        eq = FALSE;
    }
    if (!eq) {
        BOOL f = FALSE;
        u32 v = item;
        if (v >= 0x450c && v <= 0x45db) {
            f = TRUE;
        }
        if (f) {
            nextMsg = 0x3a;
        } else if (v >= 0x12b0 && v <= 0x12e7) {
            nextMsg = 0x3b;
        } else if (v >= 0x12e8 && v <= 0x131f) {
            nextMsg = 0x3c;
        } else {
            nextMsg = 0x3d;
        }
    }
}

void SpNpcBlathersTalk::returnItemAndAskMore() {
    ((ActorTalkRequest *)(this))->requestReturnItem();
    item = 0xfff1;
    nextMsg = 0x23;
}

void SpNpcBlathersTalk::openExhibitList() {
    ((ActorTalkRequest *)(this))->setSubSceneKind(0x41, 0);
    ((ActorTalkRequest *)(this))->openSubScene(2);
    setScript(3);
}

void SpNpcBlathersTalk::onChoice(u32 a) {
    if (!GameStart_IsActive()) {
        static void (SpNpcBlathersTalk::*tbl[2])(u32) = {
            &SpNpcBlathersTalk::dispatchChoice,
            &SpNpcBlathersTalk::onDramaChoice,
        };
        u32 i = 0;
        PlayerData_GetCurrent()->getErrands();
        if (dramaTalk == 1) {
            i = 1;
        }
        (this->*tbl[i])(a);
    }
}

void SpNpcBlathersTalk::onDramaChoice(u32) {
    u8 buf[4];
    s32 a = msgIndex;
    if (a <= 0x15) {
        u32 r = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
        nextMsg = 0xff;
        if (r != 0) {
            if (gSaveData.testFlag(0xc)) {
                nextMsg = 0x47;
            } else {
                nextMsg = 0x48;
            }
            dramaTalk = 0;
            buf[1] = nextMsg;
            ((TalkWindowState *)(window))->setNextMessage((u8 *)(&buf[1]), sSpNpcBlathersKey);
        } else {
            if (Talk_IsDramaPending(ownerNpc, buf, 1)) {
                Talk_AdvanceDrama(ownerNpc, buf);
            }
        }
    }
}

extern "C" u8 sSpNpcBlathersModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'o', 'w', 'l', '.', 'n', 's', 'b', 'm', 'd', 0};
void SpNpcBlathersTalk::dispatchChoice(u32 a) {
    u32 arg = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
    nextMsg = 0xff;
    static SpNpcBlathersChoiceHandler tbl[17] = {
        {0xc, &SpNpcBlathersTalk::onMainMenuChoice},
        {0xe, &SpNpcBlathersTalk::onDonationOfferChoice},
        {0x1e, &SpNpcBlathersTalk::onKeepFossilChoice},
        {0x20, &SpNpcBlathersTalk::onAppraiseAnotherChoice},
        {0x21, &SpNpcBlathersTalk::onAppraiseDonatedFossilChoice},
        {0x23, &SpNpcBlathersTalk::onAnythingElseChoice},
        {0x27, &SpNpcBlathersTalk::onDonateMoreChoice},
        {0x44, &SpNpcBlathersTalk::onMainMenuChoice},
        {0x45, &SpNpcBlathersTalk::onMainMenuChoice},
        {0x46, &SpNpcBlathersTalk::onMainMenuChoice},
        {0x47, &SpNpcBlathersTalk::onMainMenuChoice},
        {0x48, &SpNpcBlathersTalk::onMainMenuChoice},
        {0x6b, &SpNpcBlathersTalk::onDonateMoreChoice2},
        {0xe5, &SpNpcBlathersTalk::onDeliveryChoice},
        {0xe6, &SpNpcBlathersTalk::onDeliveryChoice},
        {0xe9, &SpNpcBlathersTalk::onMainMenuChoice},
        {0xea, &SpNpcBlathersTalk::onMainMenuChoice},
    };
    u32 i = 0;
    u8 *idp = &msgIndex;
    goto test0;
loop0:
    u32 id;
    id = tbl[i].id;
    if (id == *idp) {
        (this->*(&tbl[i])->fn)(arg);
    }
    i++;
test0:
    if (i < 0x11) goto loop0;
    if (nextMsg != 0xff) {
        SpNpcBlathersMsgByte b;
        b.v = nextMsg;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(&b), sSpNpcBlathersKey);
    }
}

extern "C" u8 sSpNpcBlathersTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'o', 'w', 'l', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" const u8 sSpNpcBlathersDramaMsgTable[32] = {0, 1, 2, 3, 0, 0, 4, 5, 6, 0, 0, 0, 7, 8, 9, 10, 0, 0, 11, 12, 13, 14, 15, 0, 16, 17, 18, 19, 20, 21, 0, 0};
void SpNpcBlathersTalk::onMainMenuChoice(u32 choice) {
    s32 a = choice;
    if (gSaveData.testFlag(0xc)) {
        if (a == 2) {
            a = 4;
        } else if (a > 2) {
            a--;
        }
    }
    switch (a) {
    case 0:
        appraisalFlow = 0;
        if (Talk_IsInOwnTown()) {
            if (((CommManager *)(gCommManager))->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
                nextMsg = 0x41;
            } else {
                nextMsg = 0x14;
            }
        } else {
            nextMsg = 0x40;
        }
        break;
    case 1: {
        appraisalFlow = 0;
        PlayerData *r = PlayerData_GetCurrent();
        if (MenuCtrl_BuildPocketMask(SpNpcBlathers_IsUnidentifiedFossil) == 0) {
            nextMsg = 0x18;
        } else if (r->testFlag(0x35) == 0) {
            appraisalFlow = 1;
            nextMsg = 0x17;
        } else {
            appraisalFlow = 1;
            nextMsg = 0x16;
        }
        break;
    }
    case 2:
        if (((CommManager *)(gCommManager))->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
            nextMsg = 0x4a;
        } else {
            nextMsg = 0xd;
        }
        break;
    case 3: {
        MuseumData *g = Museum();
        s32 r = g->getDonationPercent();
        nextMsg = 0x13;
        if (r == 0) {
            nextMsg = 0x10;
        } else if (r <= 0x1e000) {
            nextMsg = 0x11;
        } else if (r <= 0x46000) {
            nextMsg = 0x12;
        } else if (g->isComplete()) {
            nextMsg = 0x49;
        }
        break;
    }
    case 4:
        nextMsg = 0x3f;
        break;
    }
}

void SpNpcBlathersTalk::onDonationOfferChoice(u32 a) {
    if (a == 0) {
        nextMsg = 0x14;
    }
}

void SpNpcBlathersTalk::onDonateMoreChoice2(u32 a) {
    if (a == 0) {
        nextMsg = 0x14;
    } else {
        nextMsg = 0x28;
    }
}

void SpNpcBlathersTalk::onKeepFossilChoice(u32 a) {
    if (a == 0) {
        nextMsg = 0x2c;
    } else {
        nextMsg = 0x1f;
    }
}

void SpNpcBlathersTalk::onAppraiseAnotherChoice(u32 a) {
    if (a == 0) {
        if (MenuCtrl_BuildPocketMask(SpNpcBlathers_IsUnidentifiedFossil) == 0) {
            nextMsg = 0x18;
        } else {
            nextMsg = 0x16;
        }
    } else {
        nextMsg = 0x3e;
    }
}

void SpNpcBlathersTalk::onAppraiseDonatedFossilChoice(u32 a) {
    if (a == 0) {
        if (PlayerData_GetCurrent()->testFlag(0x35) == 0) {
            nextMsg = 0x4b;
        } else {
            nextMsg = 0x19;
        }
    } else {
        nextMsg = 0x15;
    }
}

void SpNpcBlathersTalk::onAnythingElseChoice(u32 a) {
    if (a == 0) {
        if (Talk_IsInOwnTown()) {
            if (((CommManager *)(gCommManager))->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
                nextMsg = 0x41;
            } else {
                nextMsg = 0x14;
            }
        } else {
            nextMsg = 0x40;
        }
    } else {
        nextMsg = 0x24;
    }
}

void SpNpcBlathersTalk::onDonateMoreChoice(u32 a) {
    if (a == 0) {
        nextMsg = 0x14;
    } else {
        nextMsg = 0x28;
    }
}

void SpNpcBlathersTalk::onDeliveryChoice(u32 a) {
    if (a == 0) {
        ((ActorTalkRequest *)(this))->setPocketFilter(SpNpcBlathers_IsDeliveryItem, 0xd, 0);
        ((ActorTalkRequest *)(this))->openSubScene(0);
        setScript(2);
    } else if (gSaveData.testFlag(0xc)) {
        nextMsg = 0xea;
    } else {
        nextMsg = 0xe9;
    }
}

BOOL SpNpcBlathers::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() || netIsTalkLocked()) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcBlathers::onInteractionEvent(u32 cmd, u8 arg) {
    s32 a, b;
    switch (cmd) {
    case 3:
        partnerPlayer = arg;
        if (arg != 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, arg);
            changeAct(8);
        } else if (isNetOwner()) {
            s32 g = gCommManager->myAid;
            netSetSlotsIfOwner(1, g, g);
            changeAct(8);
        }
        break;
    case 0:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            netSetSlotsIfOwner(1, arg, arg);
            changeAct(7);
        } else if (isNetOwner()) {
            s32 g = gCommManager->myAid;
            netSetSlotsIfOwner(1, g, g);
            ActorTalkRequest *p = &talk;
            p->resetMsg();
            ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
            changeAct(3);
        }
        break;
    case 8:
        if (arg == 4) {
            if (NetArea_IsLocalOwner()) {
                CommManager *gl = gCommManager;
                netSetSlotsIfOwner(1, gl->myAid, 4);
                if (((CommManager *)(gl))->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
                    changeAct(0);
                } else {
                    changeAct(1);
                }
            } else {
                netSetSlotsIfOwner(1, 4, gCommManager->myAid);
                changeAct(6);
            }
        }
        break;
    case 4:
        if (netIsTalkLocked()) {
            if (isNetOwner()) {
                a = 4;
                b = 4;
                if (((NpcActor *)(this))->netGetSlots(&a, &b)) {
                    if ((arg != 4 && (s32)arg == b) || arg == 4) {
                        netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                        changeAct(0);
                    }
                }
            }
        }
        break;
    case 1: case 2: case 5: case 6: case 7:
        break;
    }
}


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov047_02258de0) {
    HOST_OVERLAY_VAR(sSpNpcBlathersActTable),
    HOST_OVERLAY_VAR(sSpNpcBlathersProfile),
    HOST_OVERLAY_VAR(SpNpcBlathersTalk_onMessageEnd_tbl),
    HOST_OVERLAY_VAR(sSpNpcBlathersModelPath),
    HOST_OVERLAY_VAR(sSpNpcBlathersTexturePath),
    HOST_OVERLAY_VARS_END
};

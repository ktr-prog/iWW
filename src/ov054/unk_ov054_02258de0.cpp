#include "uptr.h"
#include "host_labels.h"
#include "save/ErrandRecord.h"
#include "save/SickVillagerRecord.h"
#include "talk/EncodedString8B.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "net/CommManager.h"
#include "talk/TalkStartMsg.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "npc/NpcFaceAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "talk/TalkWindowState.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "item/FutureLetter.h"
#include "npc/NpcActionCtrl.h"
#include "npc/NpcMoveCtrl.h"
#include "player/PlayerData.h"
#include "room/HouseData.h"
#include "save/SaveData.h"
#include "talk/ChoiceList.h"
#include "talk/MsgString.h"
#include "talk/MsgString9C.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_0203c92c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02095cdc.h"
#include "proto/main/unk_02097110.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov004/unk_ov004_0221e3a4.h"
#include "proto/ov054/unk_ov054_02258de0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;
class Character;
class SpNpcPellyPhyllis;
class SpNpcPellyPhyllisTalk;


struct Unk_ov054_0225b3ac_Row {
    s32 a, b, c;
};


struct SpNpcPellyPhyllisSpawnLocal {
    u8 minute;
    u8 hour;
    u16 npcHandle;
    u16 cmpItem;
    u16 spawnRot[3];
};




struct Unk_ov054_0225a3cc_Data {
    u32 w0;
    u32 w1;
};

struct FutureLetterDateLocal {
    u8 id;
    u8 pad[3];
    Unk_ov054_0225a3cc_Data d;
};

struct Unk_ov054_0225a7c4_Bits {
    u8 lo : 2;
    u8 mid : 3;
    u8 hi : 3;
};












typedef void (SpNpcPellyPhyllisTalk::*SpNpcPellyPhyllisTalkScriptFn)();
typedef void (SpNpcPellyPhyllisTalk::*Unk_ov054_0225b9c4_FnI)(s32);

struct SpNpcPellyPhyllisTalkScript {
    SpNpcPellyPhyllisTalkScriptFn fn;
    u8 flag;
};


class SpNpcPellyPhyllisTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcPellyPhyllisTalk::*Fn)();

    SpNpcPellyPhyllisTalk();
    virtual ~SpNpcPellyPhyllisTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void updateDonationLevel(s32 a);
    void askSavings();
    void askLoanPayment();
    void openLetterStorage();
    void showGoodbye();
    void startMailLetters();
    void onPostOfficeMenuChoice(s32 a);
    void openPostOfficeMenu(s32 a);
    void onSequence4Choice(s32 a);
    void onDramaChoice(s32 a);
    void onPostOfficeChoice(s32 a);
    void onSequence4MsgEnd(s32 a);
    void onDramaMsgEnd(s32 a);
    void onPostOfficeMsgEnd(s32 a);
    void waitMoveSave();
    void startMoveSave();
    void waitMoveConnected();
    void scanForMoveTarget();
    void endHandItem();
    void waitMailboxSave();
    void startMailboxSave();
    void onDeliveryItemPicked();
    void onSavingsDone();
    void onLoanPaymentEntered();
    void onFutureLetterDateEntered();
    void onTownTuneDone();
    void onDonationEntered();
    void onLetterStorageDone();
    void onMailLettersDone();
    void setScript(s32 v);
    void giveBackLetters();
    u32 getMailAcceptedMsg();
    u8 getFullMailboxMsg();
    u32 getAddressErrorMsg();
    u32 getMailResultMsg();
    void endComm();
    void attachOwner(SpNpcPellyPhyllis *o);

    /* 0xac */ SpNpcPellyPhyllis *owner;
    /* 0xb0 */ s32 menuKind;
    /* 0xb4 */ s32 script;
    /* 0xb8 */ u8 lettersGivenBack;
    /* 0xb9 */ u8 pad_b9[3];
    /* 0xbc */ s32 savingsBefore;
    /* 0xc0 */ s32 donationBefore;
    /* 0xc4 */ u16 netTimer;
    /* 0xc6 */ u8 pad_c6[0x1a8 - 0xc6];
};

class SpNpcPellyPhyllis : public SpNpcActor {
public:
    SpNpcPellyPhyllis() : talk() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *o);
    virtual void onInteractionEvent(u32 cmd, u8 arg);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    s32 isOnline();
    s32 isLocalSlotActive();
    BOOL canStartSave();
    BOOL mainAct0B();
    BOOL setupAct0B();
    BOOL mainAct0A();
    BOOL setupAct0A();
    BOOL mainAct09();
    BOOL setupAct09();
    BOOL mainAct08();
    BOOL setupAct08();
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
    BOOL updateWindow();
    void changeAct(s32 state);

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcPellyPhyllisTalk talk;
    /* 0x800 */ s16 homeAngle;
    /* 0x802 */ u8 pad_802[2];
    /* 0x804 */ s32 sister;
    /* 0x808 */ s32 window;
    /* 0x80c */ u16 dramaTimer;
    /* 0x80e */ u16 standBlend;
    /* 0x810 */ u8 dramaShown;
    /* 0x811 */ u8 pad_811[3];
};

typedef BOOL (SpNpcPellyPhyllis::*SpNpcPellyPhyllisActFn)();

struct SpNpcPellyPhyllisActEntry {
    SpNpcPellyPhyllisActFn enter;
    SpNpcPellyPhyllisActFn exit;
};




extern "C" {
extern CommManager *gCommManager;
extern u16 data_020c6cc8;
#define gSaveHouse HOST_LABEL(u8 (*)[], gSaveHouse)
extern u8 gSaveData[];
#define gSavePlayers HOST_LABEL(u8 (*)[], gSavePlayers)

BOOL Talk_IsInOwnTown(...);
void TalkChoiceList_SetIndices(void *self, void *tbl, s32 n, s32 m);
s32 Talk_IsDramaPending(void *o, void *b, s32 c);
void Talk_AdvanceDrama(void *o, void *b);

s32 strlen(const char *s);
s32 strncmp(const void *a, const char *b, s32 n);
BOOL TownState_IsPerfectStreak15();
s32 Town_GetEnvironmentRank();
u8 *TownEval_GetAdvice();
u16 Math_CountDownU16(void *p);
void MI_CpuCopy8(void *dst, void *src, u32 n);
BOOL EncodedString_SetRaw(void *dst, const void *src, s32 n);

BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);

s32 TalkRequest_AddPlayerTalk6(void *self, s32 a);
void TalkRequest_SetTargetDone(void *self);
void Clock_GetMinuteHour(void *p);

}

extern "C" {
extern const u8 sSpNpcPellyPhyllisGreetingMsgs[2];
extern const u8 data_ov054_0225b344[2];
extern const u8 data_ov054_0225b348[2];
extern const u8 data_ov054_0225b34c[2];
extern const u8 data_ov054_0225b350[2];
extern const u8 data_ov054_0225b354[3];
extern const u8 data_ov054_0225b358[4];
extern const u16 sSpNpcPellyPhyllisHandles[2];
extern const u8 data_ov054_0225b360[4];
extern const u8 data_ov054_0225b364[5];
extern const s32 sSpNpcPellyPhyllisMenuSizes[5];
extern const VecFx32 sSpNpcPellyPhyllisWindowSpots[2];
extern const Unk_ov054_0225b3ac_Row sSpNpcPellyPhyllisCounterPos[2];
extern const u8 sSpNpcPellyPhyllisDramaMsgTable[30];
extern const s32 sSpNpcPellyPhyllisDonationLevels[22];
extern ActorProfile sSpNpcPellyPhyllisProfile;
extern SpNpcPellyPhyllisTalkScript sSpNpcPellyPhyllisTalkScripts[16];
extern SpNpcPellyPhyllisActEntry sSpNpcPellyPhyllisActTable[12];
}

extern "C" const u8 data_ov054_0225b350[2] = {0x34, 0};
extern "C" char *sSpNpcPellyPhyllisMsgKeys[2][3] = {
    {sSpNpcPellyKey, sSpNpcPellyDramaKey, sSpNpcPellyPhyllisSequence4Key},
    {sSpNpcPhyllisKey, sSpNpcPhyllisDramaKey, NULL},
};
extern "C" const u8 data_ov054_0225b344[2] = {0x34, 0};
extern "C" char sSpNpcPellyDramaKey[] = "sp_npc_drama5";
extern "C" void *sSpNpcPellyPhyllisMenus[5] = {
    (void *)data_ov054_0225b358, (void *)data_ov054_0225b364, (void *)data_ov054_0225b34c,
    (void *)data_ov054_0225b354, (void *)data_ov054_0225b360,
};
extern "C" const s32 sSpNpcPellyPhyllisDonationLevels[22] = {
    0,        10000,   50000,   100000,  200000,  300000,  400000,  500000,  600000,  700000,  800000,
    900000,   1000000, 1100000, 1200000, 1300000, 1400000, 1500000, 1600000, 3200000, 6400000, 9999999,
};
extern "C" SpNpcPellyPhyllisTalkScript sSpNpcPellyPhyllisTalkScripts[16] = {
    {NULL, 0},
    {&SpNpcPellyPhyllisTalk::onMailLettersDone, 0},
    {&SpNpcPellyPhyllisTalk::onLetterStorageDone, 0},
    {&SpNpcPellyPhyllisTalk::onDonationEntered, 0},
    {&SpNpcPellyPhyllisTalk::onTownTuneDone, 0},
    {&SpNpcPellyPhyllisTalk::onFutureLetterDateEntered, 0},
    {&SpNpcPellyPhyllisTalk::onLoanPaymentEntered, 0},
    {&SpNpcPellyPhyllisTalk::onSavingsDone, 0},
    {&SpNpcPellyPhyllisTalk::startMailboxSave, 1},
    {&SpNpcPellyPhyllisTalk::waitMailboxSave, 1},
    {&SpNpcPellyPhyllisTalk::endHandItem, 0},
    {&SpNpcPellyPhyllisTalk::onDeliveryItemPicked, 0},
    {&SpNpcPellyPhyllisTalk::scanForMoveTarget, 1},
    {&SpNpcPellyPhyllisTalk::waitMoveConnected, 1},
    {&SpNpcPellyPhyllisTalk::startMoveSave, 1},
    {&SpNpcPellyPhyllisTalk::waitMoveSave, 1},
};
extern "C" u8 sSpNpcPellyTexturePath[] = "npc_sp/model/pga_tex.nsbtx";
extern "C" u8 *sSpNpcPellyPhyllisTexturePaths[2] = {sSpNpcPellyTexturePath, sSpNpcPhyllisTexturePath};
extern "C" SpNpcPellyPhyllisActEntry sSpNpcPellyPhyllisActTable[12] = {
    {&SpNpcPellyPhyllis::setupAct00, &SpNpcPellyPhyllis::mainAct00},
    {&SpNpcPellyPhyllis::setupAct01, &SpNpcPellyPhyllis::mainAct01},
    {&SpNpcPellyPhyllis::setupAct02, &SpNpcPellyPhyllis::mainAct02},
    {&SpNpcPellyPhyllis::setupAct03, &SpNpcPellyPhyllis::mainAct03},
    {&SpNpcPellyPhyllis::setupAct04, &SpNpcPellyPhyllis::mainAct04},
    {&SpNpcPellyPhyllis::setupAct05, &SpNpcPellyPhyllis::mainAct05},
    {&SpNpcPellyPhyllis::setupAct06, &SpNpcPellyPhyllis::mainAct06},
    {&SpNpcPellyPhyllis::setupAct07, &SpNpcPellyPhyllis::mainAct07},
    {&SpNpcPellyPhyllis::setupAct08, &SpNpcPellyPhyllis::mainAct08},
    {&SpNpcPellyPhyllis::setupAct09, &SpNpcPellyPhyllis::mainAct09},
    {&SpNpcPellyPhyllis::setupAct0A, &SpNpcPellyPhyllis::mainAct0A},
    {&SpNpcPellyPhyllis::setupAct0B, &SpNpcPellyPhyllis::mainAct0B},
};
extern "C" u8 sSpNpcPhyllisTexturePath[] = "npc_sp/model/pgb_tex.nsbtx";
extern "C" const u8 sSpNpcPellyPhyllisGreetingMsgs[2] = {0x34, 0};

extern "C" SpNpcPellyPhyllis *SpNpcPellyPhyllis_Create() { return new SpNpcPellyPhyllis; }

BOOL SpNpcPellyPhyllis::preCreate() {
    SpNpcPellyPhyllisSpawnLocal l;
    VecFx32 vec;
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    if (isOnline()) {
        BOOL m;
        if (Item_IsFurniture(&npcHandle)) {
            l.cmpItem = sSpNpcPellyPhyllisHandles[0];
            if (Item_GetFurnitureIndex(&npcHandle) == Item_GetFurnitureIndex(&l.cmpItem)) {
                m = TRUE;
            } else {
                m = FALSE;
            }
        } else {
            if (npcHandle == sSpNpcPellyPhyllisHandles[0]) {
                m = TRUE;
            } else {
                m = FALSE;
            }
        }
        if (m) {
            sister = 0;
            window = 1;
            position.x = sSpNpcPellyPhyllisCounterPos[1].a;
            position.y = sSpNpcPellyPhyllisCounterPos[1].b;
            position.z = sSpNpcPellyPhyllisCounterPos[1].c;
            l.spawnRot[0] = 0;
            l.spawnRot[1] = 0;
            l.spawnRot[2] = 0;
            vec.x = sSpNpcPellyPhyllisCounterPos[0].a;
            vec.y = sSpNpcPellyPhyllisCounterPos[0].b;
            vec.z = sSpNpcPellyPhyllisCounterPos[0].c;
            Actor::spawn(0x7a, sSpNpcPellyPhyllisHandles[1], &vec, &l.spawnRot[0], this);
        } else {
            sister = 1;
            window = 0;
            position.x = sSpNpcPellyPhyllisCounterPos[0].a;
            position.y = sSpNpcPellyPhyllisCounterPos[0].b;
            position.z = sSpNpcPellyPhyllisCounterPos[0].c;
        }
    } else {
        Clock_GetMinuteHour(&l);
        u8 b = l.hour;
        sister = 0;
        if (!GameStart_IsActive()) {
            if (b >= 0x16 || b < 7) {
                sister = 1;
            }
        }
        ((NpcMoveCtrl *)(&moveCtrl))->setSpeedPreset(2, 0x399, 0xcc, 0x133);
        l.npcHandle = sSpNpcPellyPhyllisHandles[sister];
        setNpcHandle(&l.npcHandle);
        npcHandle = sSpNpcPellyPhyllisHandles[sister];
    }
    setInteractionRange(0x5000);
    standBlend = data_020c6cc8;
    return TRUE;
}

BOOL SpNpcPellyPhyllis::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    void *r = PlayerData_GetCurrent();
    if (isOnline()) {
        if (NetArea_IsLocalOwner()) {
            changeAct(2);
        } else {
            changeAct(9);
        }
    } else {
        if (GameStart_IsActive() && ((PlayerData *)(r))->testFlag(9) == 0) {
            changeAct(0);
        } else {
            changeAct(2);
        }
    }
    homeAngle = rotY;
    collider.groups |= 2;
    if (sister == 0) {
        Bgm_Request(0x11, 0x55, 0x7f, 0);
    } else if (sister == 1) {
        if (!isOnline()) {
            Bgm_Request(0x11, 0x56, 0x7f, 0);
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    if (sister == 0) {
        Bgm_Release(0x55);
    } else if (sister == 1) {
        if (!isOnline()) {
            Bgm_Release(0x56);
        }
    }
    return TRUE;
}

u8 *SpNpcPellyPhyllis::getTexturePath() { return ((u8 **)sSpNpcPellyPhyllisTexturePaths)[sister]; }

u8 *SpNpcPellyPhyllis::getModelPath() { return ((u8 **)sSpNpcPellyPhyllisModelPaths)[sister]; }

BOOL SpNpcPellyPhyllis::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcPellyPhyllisActTable[act].exit) {
        r = (this->*sSpNpcPellyPhyllisActTable[act].exit)();
    }
    return r;
}

void SpNpcPellyPhyllis::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcPellyPhyllisActTable[state].enter) {
        ok = (this->*sSpNpcPellyPhyllisActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcPellyPhyllis::updateWindow() {
    s32 a, b;
    s32 c, d;
    VecFx32 v;
    VecFx32 w;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    a = 0;
    b = 0;
    FieldPos_ToUnit(&a, &b, &v);
    s32 old = window;
    s32 i = 0;
    s32 z = i;
    for (; i < 2; i++) {
        c = z;
        d = z;
        const VecFx32 *q = &sSpNpcPellyPhyllisWindowSpots[i];
        w.x = q->x;
        w.y = q->y;
        w.z = q->z;
        FieldPos_ToUnit(&c, &d, &w);
        if (a == c && b == d) {
            window = i;
            break;
        }
    }
    BOOL r;
    if (old == window) {
        r = FALSE;
    } else {
        r = TRUE;
    }
    return r;
}

BOOL SpNpcPellyPhyllis::setupAct00() { return TRUE; }

BOOL SpNpcPellyPhyllis::mainAct00() {
    TalkRequest_AddPlayerTalk6(this, 0);
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct01() {
    VecFx32Ctor v;
    const VecFx32 *p = &sSpNpcPellyPhyllisWindowSpots[0];
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    PlayerActor_RequestWalkTo(&v, 0x400, 4);
    return TRUE;
}

BOOL SpNpcPellyPhyllis::mainAct01() {
    if (PlayerActor_IsScriptedWalking(4) == 0) {
        changeAct(4);
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct02() {
    ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, standBlend);
    dramaTimer = 0xff;
    if (dramaShown == 0) {
        s32 v;
        if (Talk_IsDramaPending(this, &v, 0)) {
            dramaTimer = Random_GlobalBelow(5) * 20 + 100;
        }
    }
    standBlend = data_020c6cc8;
    return TRUE;
}

BOOL SpNpcPellyPhyllis::mainAct02() {
    if (!isOnline()) {
        if (updateWindow()) {
            changeAct(3);
            ((NpcMoveCtrl *)(&moveCtrl))->setTurnMode(data_ov054_0225b348[window]);
        }
        if (dramaTimer != 0xff) {
            if (!Math_CountDownU16(&dramaTimer)) {
                changeAct(7);
            }
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct03() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(6, 1, sSpNpcPellyPhyllisCounterPos[window].a, sSpNpcPellyPhyllisCounterPos[window].c, 0x800, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcPellyPhyllis::mainAct03() {
    isOnline();
    if (updateWindow()) {
        changeAct(3);
        ((NpcMoveCtrl *)(&moveCtrl))->setTurnMode(data_ov054_0225b348[window]);
        return TRUE;
    }
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 6) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(6);
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct04() {
    ((NpcTalkCtrl *)(&talkCtrl))->requestTalk(1, 0);
    return TRUE;
}

BOOL SpNpcPellyPhyllis::mainAct04() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(5);
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct05() { return TRUE; }

BOOL SpNpcPellyPhyllis::mainAct05() { return TRUE; }

BOOL SpNpcPellyPhyllis::setupAct06() {
    ((NpcMoveCtrl *)(&moveCtrl))->setTurnMode(0);
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcPellyPhyllis::mainAct06() {
    isOnline();
    if (updateWindow()) {
        changeAct(3);
        return TRUE;
    }
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(2);
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct07() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(10, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcPellyPhyllis::mainAct07() {
    VecFx32CtorDtor v;
    isOnline();
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 10) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            standBlend = 0x18;
            changeAct(2);
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct08() { return TRUE; }

BOOL SpNpcPellyPhyllis::mainAct08() {
    s32 a, b;
    VecFx32 v;
    if (TalkWindow_Get(0)->state == 5) {
        Taxi_SetLeaving();
        BlockMap *r = TownBlockMap_Get();
        if (r) {
            if (Town_FindTownHall(r, &v, &a, &b)) {
                v.z += 0x1000;
                SceneWarp_RequestAt(Scene_GetWarpRequest(), 0, &v, 0xec00000, 0, 2, 2);
            }
        }
        changeAct(5);
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct09() { return TRUE; }

BOOL SpNpcPellyPhyllis::mainAct09() {
    if (isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b) && a == gCommManager->myAid && a == b) {
            netSetSlotsIfOwner(1, gCommManager->myAid, gCommManager->myAid);
            talk.resetMsg();
            ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
            changeAct(4);
        } else if (NetArea_IsLocalOwner() && b == 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(2);
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct0A() { return TRUE; }

BOOL SpNpcPellyPhyllis::mainAct0A() {
    if (isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b)) {
            if (a == 4) {
                if (NetArea_IsLocalOwner()) {
                    netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    changeAct(2);
                }
            }
        }
    }
    return TRUE;
}

BOOL SpNpcPellyPhyllis::setupAct0B() { return TRUE; }

BOOL SpNpcPellyPhyllis::mainAct0B() { return TRUE; }

SpNpcPellyPhyllisTalk::SpNpcPellyPhyllisTalk() {}

SpNpcPellyPhyllisTalk::~SpNpcPellyPhyllisTalk() {}

void SpNpcPellyPhyllisTalk::attachOwner(SpNpcPellyPhyllis *o) {
    resetMsg();
    owner = o;
}

void SpNpcPellyPhyllisTalk::endComm() {
    if (Comm_End()) {
        NetOverlay_Restore();
    }
}

void SpNpcPellyPhyllisTalk::start(TalkStartMsg *out) {
    void *g0 = PlayerData_GetCurrent();
    s32 r4 = 0;
    ParcelErrand *g1 = ((PlayerData *)(g0))->getErrands()->getParcelErrand();
    BOOL r7 = r4;
    u16 v[3];
    if (owner->isOnline()) {
        r7 = TRUE;
        goto end;
    }
    if (GameStart_IsActive()) {
        if (!((PlayerData *)(g0))->testFlag(9)) {
            if (GameStart_IsNewTown() || GameStart_IsNewResident()) {
                out->msgIndex = 0x12;
            } else {
                out->msgIndex = 0x20;
            }
            ((PlayerData *)(g0))->setFlag(9);
        } else {
            out->msgIndex = 7;
        }
        r4 = 2;
        goto end;
    }
    v[1] = 0xd006;
    if (ParcelErrand_IsFor(g1, &v[1]) || (v[2] = 0xd007, ParcelErrand_IsFor(g1, &v[2]))) {
        out->msgIndex = 0x5f;
        r4 = 0;
        goto end;
    }
    if (owner->dramaShown == 0) {
        if (Talk_IsDramaPending(owner, v, r4)) {
            Unk_ov054_0225a7c4_Bits *b = (Unk_ov054_0225a7c4_Bits *)v;
            out->msgIndex = *(sSpNpcPellyPhyllisDramaMsgTable + b->mid * 6 + b->hi);
            r4 = 1;
            owner->dramaShown = r4;
            goto end;
        }
    }
    r7 = TRUE;
end:
    if (r7) {
        out->msgIndex = sSpNpcPellyPhyllisGreetingMsgs[owner->window];
        r4 = 0;
        if (owner->window == 0) {
            if (owner->isLocalSlotActive()) {
                out->msgIndex = 8;
            }
        }
    }
    out->msgKey = sSpNpcPellyPhyllisMsgKeys[owner->sister][r4];
}

u32 SpNpcPellyPhyllisTalk::getMailResultMsg() {
    if (MenuCtrl_PostOfficeWasRejected()) {
        return 0x61;
    }
    return getAddressErrorMsg();
}

u32 SpNpcPellyPhyllisTalk::getAddressErrorMsg() {
    if (MenuCtrl_PostOfficeHadBadAddress()) {
        return 0x58;
    }
    return getFullMailboxMsg();
}

u8 SpNpcPellyPhyllisTalk::getFullMailboxMsg() {
    s32 r = MenuCtrl_GetPostOfficeFullMailboxes();
    if (r) {
        return r + 0x58;
    }
    return 9;
}

u32 SpNpcPellyPhyllisTalk::getMailAcceptedMsg() {
    if (MenuCtrl_PostOfficeLettersSent()) {
        return 5;
    }
    return 9;
}

void SpNpcPellyPhyllisTalk::giveBackLetters() {
    if (lettersGivenBack == 0) {
        u16 v = 0x1565;
        ((ActorTalkRequest *)(this))->requestGiveItem(&v, 0, 5, 1);
        lettersGivenBack = 1;
    }
}

void SpNpcPellyPhyllisTalk::update() {
    s32 i = script;
    if (sSpNpcPellyPhyllisTalkScripts[i].flag != 0) {
        SpNpcPellyPhyllisTalkScript *e = &sSpNpcPellyPhyllisTalkScripts[i];
        if (e->fn) {
            (this->*e->fn)();
        }
    }
}

void SpNpcPellyPhyllisTalk::onTaskDone(u32) {
    s32 i = script;
    if (sSpNpcPellyPhyllisTalkScripts[i].flag == 0) {
        SpNpcPellyPhyllisTalkScript *e = &sSpNpcPellyPhyllisTalkScripts[i];
        if (e->fn) {
            (this->*e->fn)();
        }
    }
}

void SpNpcPellyPhyllisTalk::setScript(s32 v) {
    script = v;
}

void SpNpcPellyPhyllisTalk::onMailLettersDone() {
    TalkWindowState *m = window;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r4 = 0;
    u16 v[2];
    lettersGivenBack = r4;
    if (MenuCtrl_IsResultOk()) {
        switch (MenuCtrl_GetPostOfficeOutcome()) {
        case 0:
            r4 = getMailResultMsg();
            if (r4 == 9) {
                r4 = 7;
            }
            break;
        case 1:
            if (LetterDelivery_HasFutureLetter(NULL)) {
                r4 = 0xf;
            } else {
                r4 = 0xb;
            }
            break;
        case 2:
            r4 = 0x5c;
            break;
        case 3:
            r4 = 0x62;
            break;
        }
        v[1] = 0x1565;
        ((ActorTalkRequest *)(this))->requestTakeItem(&v[1], 0, 5, 1);
        setScript(10);
    } else {
        r4 = 3;
        ((ActorTalkRequest *)(this))->requestReopenWindow();
        setScript(0);
    }
    *(u8 *)v = r4;
    m->setNextMessage((u8 *)(v), cb);
}

void SpNpcPellyPhyllisTalk::onLetterStorageDone() {
    TalkWindowState *m = window;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    u8 buf[1];
    s32 r1;
    if (MenuCtrl_IsResultOk()) {
        r1 = 0x54;
    } else {
        r1 = 0x53;
    }
    buf[0] = r1;
    m->setNextMessage((u8 *)(buf), cb);
    setScript(0);
}

void SpNpcPellyPhyllisTalk::onDonationEntered() {
    TalkWindowState *m = window;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r4, r6;
    u16 v[3];
    if (MenuCtrl_IsResultOk()) {
        r4 = MenuCtrl_GetAmount();
        ((ActorTalkRequest *)(this))->setNumberSlot(r4, 7, 10, 1, 0);
        if (r4 >= 0x1388) {
            r6 = 0x1d;
        } else {
            r6 = 0x1e;
        }
        v[1] = 0x149b;
        ((ActorTalkRequest *)(this))->requestTakeItem(&v[1], 0, 5, 1);
        setScript(10);
        donationBefore = Donation_GetTotal();
        Donation_SetTotal(donationBefore + r4);
    } else {
        r6 = 0x1c;
        ((ActorTalkRequest *)(this))->requestReopenWindow();
        setScript(0);
    }
    *(u8 *)v = r6;
    m->setNextMessage((u8 *)(v), cb);
}

void SpNpcPellyPhyllisTalk::onTownTuneDone() {
    TalkWindowState *m = window;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    u8 buf[1];
    s32 r4;
    if (owner->isLocalSlotActive()) {
        if (MenuCtrl_IsResultOk()) {
            r4 = 0x63;
        } else {
            r4 = 0x64;
        }
    } else {
        if (MenuCtrl_IsResultOk()) {
            r4 = 0x5d;
        } else {
            r4 = 0x5e;
        }
    }
    setScript(0);
    buf[0] = r4;
    m->setNextMessage((u8 *)(buf), cb);
}

void SpNpcPellyPhyllisTalk::onFutureLetterDateEntered() {
    TalkWindowState *m = window;
    char *cb[1] = {sSpNpcPellyPhyllisMsgKeys[owner->sister][0]};
    s32 r4;
    FutureLetterDateLocal l;
    if (MenuCtrl_IsResultOk()) {
        r4 = 0xc;
        l.d.w0 = 0;
        l.d.w1 = 0;
        MenuCtrl_GetDateTime(&l.d);
        u8 *q = (u8 *)&l;
        u32 b8 = q[8];
        u32 b7 = q[7];
        ((ActorTalkRequest *)(this))->setNumberSlot(q[9] + 0x7d0, 1, 4, 0, 0);
        ((ActorTalkRequest *)(this))->setMonthSlot(b8, 2);
        ((ActorTalkRequest *)(this))->setDaySlot(b7, 3);
    } else {
        r4 = 0xe;
        MenuCtrl_ReturnFutureLetter();
    }
    setScript(0);
    l.id = r4;
    m->setNextMessage((u8 *)(&l), cb[0]);
}

void SpNpcPellyPhyllisTalk::onLoanPaymentEntered() {
    TalkWindowState *m = window;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r5;
    u16 v[2];
    if (MenuCtrl_IsResultOk()) {
        r5 = ((HouseData *)(gSaveHouse))->getDebt();
        ((ActorTalkRequest *)(this))->setNumberSlot(r5, 4, 10, 1, 0);
        if (r5 == 0) {
            r5 = 0x15;
            TownSessionState_SetFlag(TownSessionState_Get(), 0);
            ((SaveData *)(gSaveData))->clearFlag(0x10);
        } else {
            r5 = 0x14;
        }
        v[1] = 0x149b;
        ((ActorTalkRequest *)(this))->requestTakeItem(&v[1], 0, 5, 1);
        setScript(10);
    } else {
        r5 = 0x13;
        ((ActorTalkRequest *)(this))->requestReopenWindow();
        setScript(0);
    }
    *(u8 *)v = r5;
    m->setNextMessage((u8 *)(v), cb);
}

void SpNpcPellyPhyllisTalk::onSavingsDone() {
    TalkWindowState *m = window;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r4;
    u16 v[3];
    if (MenuCtrl_IsResultOk()) {
        s32 r6 = PlayerBank_GetBalance(PlayerData_GetCurrent()->getBankAccount());
        ((ActorTalkRequest *)(this))->setNumberSlot(r6, 5, 10, 1, 0);
        ((ActorTalkRequest *)(this))->setNumberSlot(r6 / 200, 6, 10, 1, 0);
        r4 = 0x17;
        if (r6 > savingsBefore) {
            v[1] = 0x149b;
            ((ActorTalkRequest *)(this))->requestTakeItem(&v[1], 0, 5, 1);
        } else {
            v[2] = 0x149b;
            ((ActorTalkRequest *)(this))->requestGiveItem(&v[2], 0, 5, 1);
        }
        setScript(10);
    } else {
        r4 = 0x18;
        ((ActorTalkRequest *)(this))->requestReopenWindow();
        setScript(0);
    }
    *(u8 *)v = r4;
    m->setNextMessage((u8 *)(v), cb);
}

extern "C" BOOL SpNpcPellyPhyllis_IsDeliveryItem(u16 *p, s32 k) {
    if (k == 2) {
        BOOL r = FALSE;
        u32 v = *p;
        if (v >= 0x155f && v <= 0x1560) {
            r = TRUE;
        }
        return r;
    }
    return FALSE;
}

void SpNpcPellyPhyllisTalk::onDeliveryItemPicked() {
    TalkWindowState *m = window;
    ParcelErrand *p;
    char *cb = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r4 = 0x51;
    u16 v[3];
    if (MenuCtrl_IsResultOk()) {
        p = PlayerData_GetCurrent()->getErrands()->getParcelErrand();
        if (Talk_IsInOwnTown(p)) {
            BOOL same;
            s32 r5 = MenuCtrl_GetIndex();
            v[1] = Pocket_GetItem(r5);
            if (r5 >= 0) {
                Pocket_RemoveItem(r5);
            }
            if (Item_IsFurniture(&v[1])) {
                v[2] = 0xfff1;
                s32 a = Item_GetFurnitureIndex(&v[1]);
                if (a == Item_GetFurnitureIndex(&v[2])) {
                    same = TRUE;
                } else {
                    same = FALSE;
                }
            } else {
                if (v[1] == 0xfff1) {
                    same = TRUE;
                } else {
                    same = FALSE;
                }
            }
            if (!same) {
                ((ActorTalkRequest *)(this))->requestTakeItem(&v[1], 2, 5, 1);
                if (!ParcelErrand_IsFor(p, &owner->npcHandle)) {
                    r4 = 0x57;
                } else {
                    r4 = 0x50;
                }
                static_cast<ErrandRecord *>(ParcelErrand_GetRecord(p))->setStep(1);
            }
        }
    }
    setScript(0);
    *(u8 *)v = r4;
    m->setNextMessage((u8 *)(v), cb);
}

void SpNpcPellyPhyllisTalk::startMailboxSave() {
    if (owner->canStartSave()) {
        SaveManager_RequestAct12();
        setScript(9);
    }
}

void SpNpcPellyPhyllisTalk::waitMailboxSave() {
    TalkWindowState *m = window;
    if (SaveManager_HasAct12Failed()) {
        u8 buf[1];
        m->hideBusyIcon();
        m->unlockAdvance();
        buf[0] = 2;
        m->setNextMessage((u8 *)(buf), sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
        setScript(0);
    } else if (SaveManager_IsIdle()) {
        m->hideBusyIcon();
        m->unlockAdvance();
        setScript(0);
    }
}

void SpNpcPellyPhyllisTalk::endHandItem() {
    ((ActorTalkRequest *)(this))->requestReopenWindow();
    setScript(0);
}

void SpNpcPellyPhyllisTalk::scanForMoveTarget() {
    u8 buf[16];
    TalkWindowState *ctx = window;
    u8 i;
    char *key = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    Comm_SendEmpty();
    s32 n = Net_CountHostCandidates();
    if (Math_CountDownU16(&netTimer) == 0) {
        endComm();
        buf[0] = 0x37;
        ctx->setNextMessage(buf, sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
        ctx->hideBusyIcon();
        ctx->unlockAdvance();
        setScript(0);
    } else if (n > 0) {
        NetOverlay_AssertWireless();
        void **results = Net_GetScanResults();
        MsgString9C name;
        EncodedString8B encoded;
        for (i = 0; i < n; i++) {
            void *beacon = results[i];
            if (beacon) {
                NetOverlay_AssertWireless();
                s32 size = Net_GetBeaconGameInfoSize(beacon);
                if (size == 10) {
                    NetOverlay_AssertWireless();
                    MI_CpuCopy8(Net_GetBeaconGameInfo(beacon), &buf[3], size);
                    if (buf[12] == 1) {
                        u32 m = 0x38;
                        if (buf[11] == 0) {
                            EncodedString_SetRaw(&encoded, &buf[3], 8);
                            name.fromEncoded(&encoded, 0, 0);
                            ctx->setSlot(8, &name);
                            m = 0x39;
                        }
                        buf[1] = m;
                        ctx->setNextMessage(&buf[1], key);
                        NetOverlay_AssertWireless();
                        if (Net_ConnectToParent(beacon)) {
                            setScript(0xd);
                            break;
                        } else {
                            endComm();
                            buf[2] = 0x37;
                            ctx->setNextMessage(&buf[2], sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
                            ctx->hideBusyIcon();
                            ctx->unlockAdvance();
                            setScript(0);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void SpNpcPellyPhyllisTalk::waitMoveConnected() {
    TalkWindowState *ctx = window;
    if (Math_CountDownU16(&netTimer) == 0) {
        u8 msg;
        endComm();
        msg = 0x37;
        ctx->setNextMessage(&msg, sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
        ctx->hideBusyIcon();
        ctx->unlockAdvance();
        setScript(0);
    } else if ((NetOverlay_AssertAny(), Net_PollConnected())) {
        ctx->hideBusyIcon();
        ctx->unlockAdvance();
        setScript(0);
    }
}

void SpNpcPellyPhyllisTalk::startMoveSave() {
    if (owner->canStartSave()) {
        SaveManager_RequestAct1F();
        setScript(0xf);
    }
}

void SpNpcPellyPhyllisTalk::waitMoveSave() {
    TalkWindowState *ctx = window;
    if (SaveManager_HasAct1FFailed()) {
        setScript(0);
    } else if (SaveManager_IsIdleAfterAct1F()) {
        u8 msg;
        ctx->hideBusyIcon();
        ctx->unlockAdvance();
        msg = 0x3c;
        ctx->setNextMessage(&msg, sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
        setScript(0);
    }
}

void SpNpcPellyPhyllisTalk::onMessageStart(u32) {
    if (msgIndex == 0xf) {
        u8 *p = ((FutureLetter *)(PlayerData_GetFutureLetter(PlayerData_GetCurrent())))->getDeliveryDate();
        u32 b1 = p[1];
        u32 b0 = p[0];
        ((ActorTalkRequest *)(this))->setNumberSlot((s32)(p[2] + 0x7d0), 1, 4, 0, 0);
        ((ActorTalkRequest *)(this))->setMonthSlot(b1, 2);
        ((ActorTalkRequest *)(this))->setDaySlot(b0, 3);
    }
    if (GameStart_IsActive()) {
        u32 id = msgIndex;
        if (id != 0x24 && id != 0x25 && id != 0x26) {
            return;
        }
        s32 cnt = 0;
        s32 i = cnt;
        u8 *g = gSavePlayers;
        do {
            if (PlayerDataArray_IsUsed(g, i)) {
                if (i != (s32)PlayerData_GetCurrentIndex()) {
                    ((ActorTalkRequest *)this)->setPlayerNameSlot(reinterpret_cast<PlayerData *>(PlayerData_GetResident(g, i))->getPlayerId(), cnt + 2);
                    cnt++;
                }
            }
            i++;
        } while (i < 4);
    }
}

void SpNpcPellyPhyllisTalk::onMessageEnd(u32 a_) {
    s32 a = (s32)a_;
    static Unk_ov054_0225b9c4_FnI tbl[3] = {
        &SpNpcPellyPhyllisTalk::onPostOfficeMsgEnd,
        &SpNpcPellyPhyllisTalk::onDramaMsgEnd,
        &SpNpcPellyPhyllisTalk::onSequence4MsgEnd,
    };
    char *s = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r = strncmp(fileName, s, strlen(s));
    s32 i;
    if (GameStart_IsActive()) {
        i = 2;
    } else if (r == 0) {
        i = 0;
    } else {
        i = 1;
    }
    (this->*tbl[i])(a);
}

void SpNpcPellyPhyllisTalk::onPostOfficeMsgEnd(s32 a) {
    TalkWindowState *ctx = window;
    void *h = PlayerData_GetCurrent();
    PlayerBank *hd = ((PlayerData *)(h))->getBankAccount();
    char *tbl = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r5 = 0;
    u8 msg;
    u16 half0;
    u16 half1;
    switch (msgIndex) {
    case 0x02:
        ctx->lockAdvance();
        break;
    case 0x00:
    case 0x52:
    case 0x53:
    case 0x56:
        openPostOfficeMenu(a);
        break;
    case 0x0e:
    case 0x5c:
    case 0x62:
        giveBackLetters();
        if (MenuCtrl_PostOfficeHadNoLetter()) {
            r5 = 9;
        } else {
            r5 = getMailResultMsg();
            if (r5 == 9) {
                r5 = 5;
            }
        }
        break;
    case 0x07:
        r5 = getMailResultMsg();
        break;
    case 0x61:
        giveBackLetters();
        break;
    case 0x58:
        giveBackLetters();
        r5 = getFullMailboxMsg();
        if (r5 == 9) {
            r5 = getMailAcceptedMsg();
        }
        break;
    case 0x59:
    case 0x5a:
    case 0x5b:
        giveBackLetters();
        r5 = getMailAcceptedMsg();
        break;
    case 0x0b:
    case 0x0d:
    case 0x11:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x33, r5);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(5);
        break;
    case 0x12:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x34, 1);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(6);
        break;
    case 0x16:
        savingsBefore = PlayerBank_GetBalance(hd);
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x3b, 1);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(7);
        break;
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x17:
    case 0x18:
        r5 = 0x52;
        break;
    case 0x55:
        ctx->lockAdvance();
        ctx->showBusyIcon(r5);
        setScript(8);
        break;
    case 0x19:
    case 0x1b:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x37, 1);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(3);
        break;
    case 0x49:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x3f, r5);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(4);
        break;
    case 0x1d:
    case 0x1e:
        updateDonationLevel(a);
        break;
    case 0x36:
        ctx->lockAdvance();
        ctx->showBusyIcon(1);
        NetOverlay_LoadWireless();
        Comm_Start(2, 2, r5);
        netTimer = 0x258;
        setScript(0xc);
        break;
    case 0x3d:
        switch (Town_GetEnvironmentRank()) {
        case 0:
            r5 = 0x42;
            break;
        case 1:
            r5 = 0x41;
            break;
        case 2:
            r5 = 0x40;
            break;
        case 3:
            r5 = 0x3f;
            break;
        case 4:
            r5 = 0x3e;
            break;
        default:
            r5 = 0x40;
            break;
        }
        break;
    case 0x3e:
        if (((PlayerData *)(h))->testFlag(0x20)) {
            r5 = 0x4b;
            break;
        }
        if (TownState_IsPerfectStreak15()) {
            if (Talk_IsInOwnTown()) {
                half0 = 0x1379;
                if (Pocket_AddItem(&half0, r5)) {
                    r5 = 0x4d;
                    break;
                }
            }
        }
        r5 = 0x4c;
        break;
    case 0x40:
    case 0x41:
    case 0x42:
        switch (*(s32 *)(TownEval_GetAdvice() + 8)) {
        case 0:
            r5 = 0x43;
            break;
        case 1:
            r5 = 0x44;
            break;
        case 2:
            r5 = 0x45;
            break;
        case 3:
            r5 = 0x46;
            break;
        case 4:
            r5 = 0x47;
            break;
        case 5:
            r5 = 0x48;
            break;
        default:
            r5 = 0x43;
            break;
        }
        break;
    case 0x4e:
        half1 = 0x1379;
        ((ActorTalkRequest *)(this))->requestGiveItem(&half1, r5, 5, 1);
        ((PlayerData *)(h))->setFlag(0x20);
        break;
    case 0x3b:
        ctx->lockAdvance();
        ctx->showBusyIcon(r5);
        setScript(0xe);
        break;
    case 0x3c:
        *(u32 *)((u8 *)ctx + 0x14) = 0;
        owner->changeAct(8);
        break;
    }
    if (r5 != 0) {
        msg = r5;
        ctx->setNextMessage(&msg, tbl);
    }
}

void SpNpcPellyPhyllisTalk::onDramaMsgEnd(s32 a) {}

void SpNpcPellyPhyllisTalk::onSequence4MsgEnd(s32 a) {
    TalkWindowState *ctx = window;
    char *tbl = sSpNpcPellyPhyllisMsgKeys[owner->sister][2];
    u32 r4 = 0;
    u8 msg;
    switch (msgIndex) {
    case 0x02:
    case 0x20:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x2f, 0);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        break;
    case 0x13:
        r4 = PlayerDataArray_CountUsed(gSavePlayers);
        if (GameStart_IsNewTown()) {
            r4 = 2;
        } else {
            r4 = (u8)(r4 + 0x22);
        }
        break;
    }
    if (r4 != 0) {
        msg = r4;
        ctx->setNextMessage(&msg, tbl);
    }
}

void SpNpcPellyPhyllisTalk::onChoice(u32 a_) {
    s32 a = (s32)a_;
    static Unk_ov054_0225b9c4_FnI tbl[3] = {
        &SpNpcPellyPhyllisTalk::onPostOfficeChoice,
        &SpNpcPellyPhyllisTalk::onDramaChoice,
        &SpNpcPellyPhyllisTalk::onSequence4Choice,
    };
    char *s = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    s32 r = strncmp(fileName, s, strlen(s));
    s32 i;
    if (GameStart_IsActive()) {
        i = 2;
    } else if (r == 0) {
        i = 0;
    } else {
        i = 1;
    }
    (this->*tbl[i])(a);
}

void SpNpcPellyPhyllisTalk::onPostOfficeChoice(s32 a) {
    TalkWindowState *o = window;
    s32 r = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
    void *g = PlayerData_GetCurrent();
    u32 id = 0xff;
    u8 m;
    switch (msgIndex) {
    case 0x5f:
        if (r == 0) {
            ((ActorTalkRequest *)(this))->setPocketFilter(SpNpcPellyPhyllis_IsDeliveryItem, 0xd, 0);
            ((ActorTalkRequest *)(this))->openSubScene(0);
            setScript(0xb);
        } else if (r == 1) {
            id = data_ov054_0225b344[owner->window];
        }
        break;
    case 0:
    case 0x52:
    case 0x53:
    case 0x56:
        onPostOfficeMenuChoice(a);
        break;
    case 3:
    case 9:
        if (r == 0) {
            ((ActorTalkRequest *)(this))->openSubScene(1);
            setScript(1);
        }
        break;
    case 0x10:
        if (r == 0) {
            id = 0x11;
        } else if (r == 1) {
            id = 0xe;
            MenuCtrl_ReturnFutureLetter();
        }
        break;
    case 0xc:
        if (r == 0) {
            MenuCtrl_StoreFutureLetter();
            id = 7;
        }
        break;
    case 4:
    case 0x1c:
    case 0x34:
    case 0x5d:
    case 0x5e:
        if (r == 2) {
            if (((PlayerData *)(g))->testFlag(4) == 0) {
                id = 0x1a;
                ((PlayerData *)(g))->setFlag(4);
            } else {
                id = 0x19;
            }
        } else if (r == 3) {
            if (((PlayerData *)(g))->testFlag(1) != 0) {
                id = 0x60;
            } else {
                id = 0x35;
            }
        }
        break;
    case 0x38:
    case 0x39:
        if (r == 1) {
            endComm();
            id = 0x3a;
        }
        break;
    case 1:
        break;
    }
    if (id != 0xff) {
        m = id;
        o->setNextMessage((u8 *)(&m), sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
    }
}

void SpNpcPellyPhyllisTalk::onDramaChoice(s32 a) {
    TalkWindowState *o = window;
    s32 r = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
    u32 id = 0xff;
    u32 k = 1;
    u8 m[2];
    s32 t = msgIndex;
    if (t >= 0 && t <= 0x19) {
        if (r == 1) {
            id = data_ov054_0225b350[owner->window];
            k = 0;
        } else if (Talk_IsDramaPending(owner, m, 0)) {
            Talk_AdvanceDrama(owner, m);
        }
    }
    if (id != 0xff) {
        char *name = sSpNpcPellyPhyllisMsgKeys[owner->sister][k];
        m[1] = id;
        o->setNextMessage(&m[1], name);
    }
}

void SpNpcPellyPhyllisTalk::onSequence4Choice(s32 a) {
    s32 r = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
    PlayerData_GetCurrent();
    if (msgIndex == 0x12) {
        switch (r) {
        case 0:
            PlayerOptions_SetHiragana(0);
            break;
        case 1:
            PlayerOptions_SetHiragana(1);
            break;
        }
        PlayerOptions_Commit();
    }
}

void SpNpcPellyPhyllisTalk::openPostOfficeMenu(s32 a) {
    TalkWindowState *o = window;
    void *g = PlayerData_GetCurrent();
    menuKind = 0;
    if (!Talk_IsInOwnTown()) {
        menuKind = 2;
    } else if (((PlayerData *)(g))->testFlag(1) == 0 && ((HouseData *)(gSaveHouse))->getDebt() != 0) {
        if (owner->isLocalSlotActive()) {
            menuKind = 4;
        } else {
            menuKind = 1;
        }
    } else {
        if (owner->isLocalSlotActive()) {
            menuKind = 3;
        }
    }
    s32 n = sSpNpcPellyPhyllisMenuSizes[menuKind];
    TalkChoiceList_SetIndices(this, sSpNpcPellyPhyllisMenus[menuKind], n, n - 1);
    o->openChoices(1);
}

typedef void (SpNpcPellyPhyllisTalk::*SpNpcPellyPhyllisTalk_Fn)();
SpNpcPellyPhyllisTalk_Fn SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a1[2] = {&SpNpcPellyPhyllisTalk::startMailLetters, &SpNpcPellyPhyllisTalk::showGoodbye};
SpNpcPellyPhyllisTalk_Fn SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a2[4] = {&SpNpcPellyPhyllisTalk::startMailLetters, &SpNpcPellyPhyllisTalk::askSavings, &SpNpcPellyPhyllisTalk::openLetterStorage,
                       &SpNpcPellyPhyllisTalk::showGoodbye};
SpNpcPellyPhyllisTalk_Fn SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a3[5] = {&SpNpcPellyPhyllisTalk::startMailLetters, &SpNpcPellyPhyllisTalk::askLoanPayment, &SpNpcPellyPhyllisTalk::askSavings,
                       &SpNpcPellyPhyllisTalk::openLetterStorage, &SpNpcPellyPhyllisTalk::showGoodbye};
SpNpcPellyPhyllisTalk_Fn SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a4[3] = {&SpNpcPellyPhyllisTalk::startMailLetters, &SpNpcPellyPhyllisTalk::askSavings, &SpNpcPellyPhyllisTalk::showGoodbye};
SpNpcPellyPhyllisTalk_Fn SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a5[4] = {&SpNpcPellyPhyllisTalk::startMailLetters, &SpNpcPellyPhyllisTalk::askLoanPayment, &SpNpcPellyPhyllisTalk::askSavings,
                       &SpNpcPellyPhyllisTalk::showGoodbye};
void SpNpcPellyPhyllisTalk::onPostOfficeMenuChoice(s32 a) {
    s32 idx = ((ChoiceList *)(((ActorTalkRequest *)(this))->getChoiceList()))->getResult();
    static Fn *tbls[5] = {SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a2, SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a3, SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a1, SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a4, SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a5};
    static const s32 cnt[5] = {4, 5, 2, 3, 4};
    if (idx < cnt[menuKind]) {
        (this->*tbls[menuKind][idx])();
    }
}

void SpNpcPellyPhyllisTalk::startMailLetters() {
    ((ActorTalkRequest *)(this))->openSubScene(1);
    setScript(1);
}

void SpNpcPellyPhyllisTalk::showGoodbye() {
    u8 m = 1;
    window->setNextMessage((u8 *)(&m), sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
}

void SpNpcPellyPhyllisTalk::openLetterStorage() {
    ((ActorTalkRequest *)(this))->setSubSceneKind(0x26, 0);
    ((ActorTalkRequest *)(this))->openSubScene(2);
    setScript(2);
}

void SpNpcPellyPhyllisTalk::askLoanPayment() {
    ((ActorTalkRequest *)(this))->setNumberSlot(((HouseData *)(gSaveHouse))->getDebt(), 4, 10, 1, 0);
    u8 m = 0x12;
    window->setNextMessage((u8 *)(&m), sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
}

void SpNpcPellyPhyllisTalk::askSavings() {
    u8 m = 0x16;
    window->setNextMessage((u8 *)(&m), sSpNpcPellyPhyllisMsgKeys[owner->sister][0]);
}

void SpNpcPellyPhyllisTalk::updateDonationLevel(s32 a) {
    TalkWindowState *o = window;
    void *g;
    PlayerBank *h;
    char *name;
    name = sSpNpcPellyPhyllisMsgKeys[owner->sister][0];
    g = PlayerData_GetCurrent();
    h = ((PlayerData *)(g))->getBankAccount();
    s32 pos = Donation_GetTotal();
    u8 v = PlayerBank_GetDonationLevel(h) + 0x1f;
    s32 i;
    for (i = 1; i < 0x15; i++) {
        s32 t = sSpNpcPellyPhyllisDonationLevels[i];
        if (pos >= t && pos < sSpNpcPellyPhyllisDonationLevels[i + 1]) {
            PlayerBank_SetDonationLevel(h, i);
            if (donationBefore < t) {
                ((PlayerData *)(g))->setFlag(0x16);
                v = i + 0x1f;
            } else {
                v = i + 0x1f;
            }
        }
    }
    u8 m = v;
    o->setNextMessage(&m, name);
}

BOOL SpNpcPellyPhyllis::acceptsInteraction(void *other) {
    Character *o = (Character *)other;
    BOOL r = FALSE;
    s32 bx, by, cx, cy;
    VecFx32 pos;
    VecFx32 *pv = (VecFx32 *)&o->position;
    pos.x = o->position.x;
    pos.y = pv->y;
    pos.z = pv->z;
    bx = 0;
    by = 0;
    cx = 0;
    cy = 0;
    FieldPos_ToUnit(&bx, &by, &pos);
    VecFx32 dst;
    const VecFx32 *pd = &sSpNpcPellyPhyllisWindowSpots[window];
    dst.x = sSpNpcPellyPhyllisWindowSpots[window].x;
    dst.y = pd->y;
    dst.z = pd->z;
    FieldPos_ToUnit(&cx, &cy, &dst);
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || netIsTalkLocked()) {
        return FALSE;
    }
    if (act == 2 || act == 0 || act == 9) {
        if (bx == cx && by == cy) {
            r = TRUE;
        }
    }
    return r;
}

void SpNpcPellyPhyllis::onInteractionEvent(u32 cmd, u8 arg) {
    s32 a, b;
    switch (cmd) {
    case 3:
        partnerPlayer = arg;
        if (arg != 4) {
            netSetSlotsIfOwner(1, gCommManager->myAid, arg);
            changeAct(0xb);
        } else if (isNetOwner()) {
            u32 t = gCommManager->myAid;
            netSetSlotsIfOwner(1, t, t);
            changeAct(0xb);
        }
        break;
    case 1:
        talk.resetMsg();
        ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 0:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            netSetSlotsIfOwner(1, arg, arg);
            changeAct(0xa);
        } else if (isNetOwner()) {
            u32 t = gCommManager->myAid;
            netSetSlotsIfOwner(1, t, t);
            talk.resetMsg();
            ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
            changeAct(4);
        }
        break;
    case 8:
        if (arg == 4) {
            if (NetArea_IsLocalOwner()) {
                netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                changeAct(2);
            } else {
                netSetSlotsIfOwner(1, 4, gCommManager->myAid);
                changeAct(9);
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
                        changeAct(2);
                    }
                }
            }
        }
        break;
    }
}

BOOL SpNpcPellyPhyllis::canStartSave() {
    if (faceAnim.getMouthAnim() == 0xba && SpNpcTortimer2_IsIdle() && talk.window->state == 2) {
        return TRUE;
    }
    return FALSE;
}

s32 SpNpcPellyPhyllis::isLocalSlotActive() {
    return ((CommManager *)(gCommManager))->isSlotActive(gCommManager->myAid);
}

s32 SpNpcPellyPhyllis::isOnline() {
    return ((CommManager *)(gCommManager))->isOnline();
}

extern "C" ActorProfile sSpNpcPellyPhyllisProfile = {(void *(*)())SpNpcPellyPhyllis_Create, 0x7a, 0x7e, 2, 0x5000, 0x5000, 0x3e800};
extern "C" u8 *sSpNpcPellyPhyllisModelPaths[2] = {sSpNpcPellyModelPath, sSpNpcPhyllisModelPath};
extern "C" const u8 data_ov054_0225b358[4] = {0xeb, 0xec, 0xd5, 0x56};
extern "C" char sSpNpcPellyKey[] = "sp_npc_ypelican";
extern "C" const s32 sSpNpcPellyPhyllisMenuSizes[5] = {4, 5, 2, 3, 4};
extern "C" const u8 data_ov054_0225b360[4] = {0xeb, 0xed, 0xec, 0x56};
extern "C" u8 sSpNpcPellyModelPath[] = "npc_sp/model/pga.nsbmd";
extern "C" const u16 sSpNpcPellyPhyllisHandles[2] = {0xd006, 0xd007};
extern "C" const u8 data_ov054_0225b34c[2] = {0xeb, 0x56};
extern "C" char sSpNpcPhyllisKey[] = "sp_npc_opelican";
extern "C" u8 sSpNpcPhyllisModelPath[] = "npc_sp/model/pgb.nsbmd";
extern "C" const VecFx32 sSpNpcPellyPhyllisWindowSpots[2] = {{0xf000, 0, 0x17000}, {0x13000, 0, 0x17000}};
extern "C" char sSpNpcPellyPhyllisSequence4Key[] = "sp_etc_sequence4";
extern "C" const u8 sSpNpcPellyPhyllisDramaMsgTable[30] = {
    0x00, 0x01, 0x02, 0x03, 0xfe, 0xfe, 0x04, 0x05, 0x06, 0x07, 0xfe, 0xfe, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
};
extern "C" char sSpNpcPhyllisDramaKey[] = "sp_npc_drama6";
extern "C" const u8 data_ov054_0225b354[3] = {0xeb, 0xec, 0x56};
extern "C" const u8 data_ov054_0225b364[5] = {0xeb, 0xed, 0xec, 0xd5, 0x56};
extern "C" const u8 data_ov054_0225b348[2] = {2, 1};
extern "C" const Unk_ov054_0225b3ac_Row sSpNpcPellyPhyllisCounterPos[2] = {{0xf000, 0, 0x13000}, {0x13000, 0, 0x13000}};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov054_02258de0) {
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisMsgKeys),
    HOST_OVERLAY_VAR(sSpNpcPellyDramaKey),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisMenus),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcPellyTexturePath),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisTexturePaths),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisActTable),
    HOST_OVERLAY_VAR(sSpNpcPhyllisTexturePath),
    HOST_OVERLAY_VAR(SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a1),
    HOST_OVERLAY_VAR(SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a2),
    HOST_OVERLAY_VAR(SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a3),
    HOST_OVERLAY_VAR(SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a4),
    HOST_OVERLAY_VAR(SpNpcPellyPhyllisTalk_onPostOfficeMenuChoice_a5),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisProfile),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisModelPaths),
    HOST_OVERLAY_VAR(sSpNpcPellyKey),
    HOST_OVERLAY_VAR(sSpNpcPellyModelPath),
    HOST_OVERLAY_VAR(sSpNpcPhyllisKey),
    HOST_OVERLAY_VAR(sSpNpcPhyllisModelPath),
    HOST_OVERLAY_VAR(sSpNpcPellyPhyllisSequence4Key),
    HOST_OVERLAY_VAR(sSpNpcPhyllisDramaKey),
    HOST_OVERLAY_VARS_END
};

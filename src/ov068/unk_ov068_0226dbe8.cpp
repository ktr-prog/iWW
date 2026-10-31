#include "types.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "npc/VillagerId.h"
#include "player/PlayerErrands.h"
#include "save/VillagerData.h"
#include "sys/ClockDateTime.h"
#include "town/BlockMap.h"
#include "gfx/VecFx32.h"
#include "npc/VillagerClothModel.h"
#include "talk/MsgStringBase.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "npc/VillagerMood.h"
#include "talk/TalkWindowState.h"
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
#include "talk/EncodedString.h"
#include "npc/NpcFaceAnim.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/EncodedString16Buf.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/VillagerActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/VillagerTalk.h"
#include "talk/MsgString.h"
#include "talk/MsgString33.h"
#include "proto/autoload_2/unk_0213510c.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov004/unk_ov004_02215f04.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/ov068/unk_ov068_0226dbe8.h"
#include "player/PlayerData.h"
#include "proto/main/unk_020b4828.h"


class HouseVisitVillager;

struct HouseVisitStarText {
    u8 b[16];
};

struct Unk_ov068_02270a6c_Bits {
    u8 lo : 3;
    u8 hi : 5;
};



typedef void (HouseVisitVillager::*Unk_ov068_02270afc_Fn)();
typedef BOOL (HouseVisitVillager::*Unk_ov068_02270afc_BFn)();








#define SPEAK(str) ((VillagerData *)ownerVillager->villagerData)->getVillagerId()->makeFileName(sHouseVisitMsgFileName, 0x28, str)

class HouseVisitVillagerTalk : public VillagerTalk {
public:
    inline HouseVisitVillagerTalk() {}
    virtual void onMessageStart(u32 a);
    virtual void onMessageEnd(u32 a);
    virtual void onChoice(u32 a);
    virtual void start(TalkStartMsg *out);

    void attachOwner(HouseVisitVillager *owner);

    /* 0x1a0 */ HouseVisitVillager *ownerVillager;
};

class HouseVisitVillager : public VillagerActor {
public:
    inline HouseVisitVillager() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL preDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 idx, u8 v);
    virtual BOOL updateAct();
    virtual BOOL canPlayTalkMelody();
    virtual void onTalkMelodyPlayed();

    void execVisitLeave();
    BOOL enterVisitLeave();
    void execVisitTalkWait();
    BOOL enterVisitTalkWait();
    void execVisitTalk();
    BOOL enterVisitTalk();
    void execVisitIdle7();
    BOOL enterVisitIdle7();
    void execVisitWander();
    BOOL enterVisitWander();
    void execVisitStay();
    BOOL enterVisitStay();
    void execVisitGreetEnd();
    BOOL enterVisitGreetEnd();
    void execVisitWalkIn();
    BOOL enterVisitWalkIn();
    void execVisitDoorOpen();
    BOOL enterVisitDoorOpen();
    void execVisitCall();
    BOOL enterVisitCall();
    void execVisitOutside();
    BOOL enterVisitOutside();
    void updateVisitState();
    BOOL setVisitState(s32 idx);
    void setVisitWalkSpeed();
    void recordTalkWithPlayer();
    void unlinkFurnitureUnits();
    BOOL drawModel();

    /* 0x894 */ s32 visitState;
    /* 0x898 */ HouseVisitVillagerTalk talk;
    /* 0xa3c */ Unk_ov068_02270afc_BFn drawFn;
    /* 0xa44 */ u32 roomStars;
    /* 0xa48 */ u8 walkInTimer;
    /* 0xa49 */ u8 pad_a49;
    /* 0xa4a */ u16 wanderTimer;
    /* 0xa4c */ u32 roomRateFlags;
    /* 0xa50 */ u8 wantsToLeave;
    /* 0xa51 */ u8 playerAtExit;
    /* 0xa52 */ u8 talkTopic;
    /* 0xa53 */ u8 pad_a53;
    /* 0xa54 */ u8 talksLeft;
    /* 0xa55 */ u8 pad_a55;
    /* 0xa56 */ s16 stayTimer;
    /* 0xa58 */ u8 leaveTalkDelay;
    /* 0xa59 */ s8 callTimer;
    /* 0xa5a */ s16 wanderAngle;
    /* 0xa5c */ VecFx32 waypoint;
    /* 0xa68 */ VecFx32 walkTarget;
};
class RoomScoreEvaluator;
class VillagerState;
struct VillagerMemory;

extern "C" {
extern HouseVisitStarText data_ov068_02270a3c;
extern u16 data_020c6cc8;
extern s32 data_020c6d1c;
extern s32 data_020c8cb4;
extern s32 data_020c8cb8;
extern s32 data_020c8cbc;
extern BlockMap *gSceneBlockMap;
extern VillagerTalkTopicFns sHouseVisitTsuTopicTable[];
#define data_021be810 HOST_LABEL(VillagerTalkTopicFns (*)[], data_021be810)
extern u8 gTalkMsgIndexEnd;

BOOL Ground_IsOnLockedExit(VecFx32 *p);
BOOL Ground_LockExit(s32 v);
void Ground_UnlinkUnit(s32 x, s32 z);
u8 Scene_GetPrevious();
BOOL SceneId_IsTown(u32 a);
VillagerState *Villager_GetState(VillagerData *a);
void VillagerState_ResetRole(VillagerState *e);
void VillagerState_SetRole(VillagerState *e, s32 role);
BOOL TalkRequest_SetTargetDone(Character *x);
BOOL TalkRequest_AddPlayerTalk6(Character *a, s32 b);
void RoomScoreEvaluator_Construct(RoomScoreEvaluator *p);
void RoomScoreEvaluator_Destruct();
u32 HappyRoom_RateMainRoom(RoomScoreEvaluator *p, s32 *out);
void MI_CpuCopy8(const void *src, void *dst, u32 n);
void DateTime_AddMinutes(ClockDateTime *p, s32 n);
void Clock_GetDateTime(ClockDateTime *p);
s32 DateTime_Compare(ClockDateTime *a, ClockDateTime *b, u32 mask);
VillagerMemory *Villager_FindOrCreateMemory(VillagerMemory *t, void *b);
void VillagerMemory_RecordTalk(VillagerMemory *self, void *a, u8 *b, u8 *c);
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
BOOL Item_IsFurnitureOrF031(u16 *p);
}

static PlayerErrands *HouseVisit_GetErrands() {
    return PlayerData_GetCurrent()->getErrands();
}

extern "C" {
HouseVisitVillager *sHouseVisitVillager;
}


extern "C" HouseVisitVillager *HouseVisitVillager_Create() {
    return new HouseVisitVillager;
}

BOOL HouseVisitVillager::preCreate() {
    if (VillagerActor::preCreate() == 0) {
        return FALSE;
    }
    sHouseVisitVillager = this;
    setTalkRequest(&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL HouseVisitVillager::onCreate() {
    if (VillagerActor::onCreate() == 0) {
        return FALSE;
    }
    drawFn = &HouseVisitVillager::drawModel;
    unlinkFurnitureUnits();
    footstepFx.enableFootsteps();
    stayTimer = -1;
    talksLeft = 3;
    leaveTalkDelay = 0xb0;
    if (SceneId_IsTown(Scene_GetPrevious()) != 0) {
        setVisitState(0);
    } else if (HouseVisit_IsCalled(&talk) != 0) {
        u32 buf[6];
        RoomScoreEvaluator *eval = (RoomScoreEvaluator *)buf;
        HouseVisitor_SetPresent();
        stayTimer = (Random_GlobalBelow(0x14) + 0x28) * 0x3c;
        talksLeft = Random_GlobalBelow(4) + 2;
        RoomScoreEvaluator_Construct(eval);
        roomRateFlags = HappyRoom_RateMainRoom(eval, (s32 *)&roomStars);
        setVisitState(6);
        RoomScoreEvaluator_Destruct();
    } else {
        stayTimer = (Random_GlobalBelow(0x28) + 0x3c) * 0x3c;
        talksLeft = Random_GlobalBelow(4) + 7;
        setVisitState(0);
    }
    return TRUE;
}

BOOL HouseVisitVillager::drawModel() {
    if (NpcActor::onDraw() != 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL HouseVisitVillager::onDraw() {
    if (drawFn) {
        return (this->*drawFn)();
    }
    return TRUE;
}

BOOL HouseVisitVillager::preDelete() {
    if (VillagerActor::preDelete() == 0) {
        return FALSE;
    }
    ErrandRecord *e = &HouseVisit_GetErrands()->houseVisitInvite.errand;
    if (e->getStep() == 1) {
        e->setStep(2);
    }
    sHouseVisitVillager = NULL;
    return TRUE;
}

BOOL HouseVisitVillager::updateAct() {
    updateVisitState();
    return TRUE;
}

void HouseVisitVillager::unlinkFurnitureUnits() {
    BlockMap *g = gSceneBlockMap;
    void *grid;
    s32 y, x;
    s32 z;
    if (g->width != 0 && g->height != 0 && g->blocks != NULL) {
        grid = g->blocks;
    } else {
        grid = NULL;
    }
    y = 0;
    z = 0;
    for (; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            u16 *item;
            if ((item = MapBlock_GetItemPtr(grid, x, y, z)) != NULL) {
                if (Item_IsFurnitureOrF031(item) != 0) {
                    Ground_UnlinkUnit(x, y);
                }
            }
        }
    }
}

void HouseVisitVillager::recordTalkWithPlayer() {
    PlayerData *p = PlayerData_GetCurrent();
    if (p != NULL) {
        if (villagerData != NULL) {
            VillagerMemory_RecordTalk(Villager_FindOrCreateMemory(((VillagerData *)villagerData)->memories, p->getPlayerId()), NULL, NULL, NULL);
        }
    }
}

void HouseVisitVillager::setVisitWalkSpeed() {
    moveCtrl.setSpeedPreset(1, 0x100, 0x19, 0x33);
}

extern "C" BOOL HouseVisit_IsAppointmentNow(void *) {
    ClockDateTimeWords a, b, c;
    MI_CpuCopy8(&HouseVisit_GetErrands()->houseVisitInvite.visitTime, &a, 8);
    MI_CpuCopy8(&a, &b, 8);
    DateTime_AddMinutes(&b.dt, 0x1e);
    c.words[0] = 0;
    c.words[1] = 0;
    Clock_GetDateTime(&c.dt);
    if (DateTime_Compare(&a.dt, &c.dt, 0x3e) == -1 || DateTime_Compare(&a.dt, &c.dt, 0x3e) == 0) {
        if (DateTime_Compare(&c.dt, &b.dt, 0x3e) == -1) {
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void HouseVisit_SetFinished(void *) {
    HouseVisit_GetErrands()->houseVisitInvite.errand.setStep(4);
}

BOOL HouseVisitVillager::acceptsInteraction(void *) {
    if (talkCtrl.isBusy() != 0) {
        return FALSE;
    }
    if ((u32)(visitState - 5) <= 1) {
        return TRUE;
    }
    return FALSE;
}

void HouseVisitVillager::onInteractionEvent(u32 idx, u8 v) {
    switch (idx) {
    case 3:
        partnerPlayer = v;
        if (visitState != 0) {
            if (visitState == 5) {
                stayTimer = (Random_GlobalBelow(0x28) + 0x3c) * 0x3c;
            }
            setVisitState(7);
        }
        break;
    case 0:
        partnerPlayer = v;
        talk.attachOwner(this);
        setVisitState(8);
        break;
    case 1:
        partnerPlayer = v;
        talk.attachOwner(this);
        if (visitState == 0) {
            setVisitState(1);
        } else {
            setVisitState(8);
        }
        break;
    case 8:
        leaveTalkDelay = 0x14;
        recordTalkWithPlayer();
        if (visitState != 0xa && visitState != 5) {
            setVisitState(6);
        }
        break;
    case 4:
        setVisitState(6);
        break;
    case 2:
    case 5:
    case 6:
    case 7:
        break;
    }
}

extern "C" BOOL HouseVisit_IsCalled(void *) {
    if (HouseVisit_GetErrands()->houseVisitInvite.errand.getStep() != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void HouseVisit_SetCalled(void *p) {
    if (HouseVisit_IsCalled(p) == 0) {
        HouseVisit_GetErrands()->houseVisitInvite.errand.setStep(1);
    }
}

extern "C" BOOL HouseVisit_IsDoorTalkDone(void *) {
    if ((u32)HouseVisit_GetErrands()->houseVisitInvite.errand.getStep() > 1) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void HouseVisit_SetDoorTalkDone(void *p) {
    if (HouseVisit_IsDoorTalkDone(p) == 0) {
        HouseVisit_GetErrands()->houseVisitInvite.errand.setStep(2);
    }
}

extern "C" BOOL HouseVisit_IsFirstTalkPending(void *) {
    if (HouseVisit_GetErrands()->houseVisitInvite.errand.getStep() == 2) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void HouseVisit_SetFirstTalkDone(void *) {
    HouseVisit_GetErrands()->houseVisitInvite.errand.setStep(3);
}

void HouseVisitVillagerTalk::attachOwner(HouseVisitVillager *owner) {
    begin((VillagerActor *)owner, 0x11);
    ownerVillager = owner;
}

void HouseVisitVillagerTalk::start(TalkStartMsg *arg) {
    TalkStartMsg *out = (TalkStartMsg *)arg;
    out->msgKey = (const char *)sHouseVisitMsgFileName;
    if (ownerVillager->visitState == 1) {
        ownerVillager->talkTopic = 1;
        SPEAK("q10_call");
        out->msgIndex = Random_GlobalBelow(3);
        HouseVisit_SetCalled(this);
        return;
    }
    if (ownerVillager->wantsToLeave != 0 && ownerVillager->playerAtExit != 0) {
        ownerVillager->wantsToLeave = 0;
    }
    if (ownerVillager->wantsToLeave != 0) {
        ownerVillager->talkTopic = 6;
        SPEAK("q10_back");
        out->msgKey = (const char *)sHouseVisitMsgFileName;
        out->msgIndex = Random_GlobalBelow(3);
        return;
    }
    if (ownerVillager->playerAtExit != 0) {
        ownerVillager->talkTopic = 8;
        SPEAK("q10_wait");
        out->msgKey = (const char *)sHouseVisitMsgFileName;
        out->msgIndex = Random_GlobalBelow(2);
        return;
    }
    if (HouseVisit_IsDoorTalkDone(this) == 0) {
        ownerVillager->talkTopic = 2;
        SPEAK("q10_door");
        out->msgIndex = Random_GlobalBelow(3);
        HouseVisit_SetDoorTalkDone(this);
        return;
    }
    if (HouseVisit_IsFirstTalkPending(this)) {
        ownerVillager->talkTopic = 5;
        SPEAK("q10_first");
        out->msgKey = (const char *)sHouseVisitMsgFileName;
        out->msgIndex = Random_GlobalBelow(3);
        HouseVisit_SetFirstTalkDone(this);
        return;
    }
    if (ownerVillager->talksLeft != 0) {
        ownerVillager->talksLeft = ownerVillager->talksLeft - 1;
    }
    u32 rnd = Random_GlobalBelow(100);
    s32 v = FtrMgr_PickFurnitureComment(VillagerId_GetPersonality(((VillagerData *)ownerVillager->villagerData)->getVillagerId()));
    u32 n = ownerVillager->roomStars;
    if (n >= 5) {
        n = 5;
    }
    HouseVisitStarText buf = data_ov068_02270a3c;
    for (u32 i = n; i < 16; i++) {
        buf.b[i] = 0;
    }
    EncodedString16Buf obj1(buf.b);
    MsgString33 obj2;
    obj2.fromEncoded(&obj1, 0, 0);
    window->setSlot(3, &obj2);
    if (rnd < 30 && v != -1) {
        ownerVillager->talkTopic = 3;
        SPEAK("q10_furniture");
        out->msgKey = (const char *)sHouseVisitMsgFileName;
        out->msgIndex = v;
        return;
    }
    if (rnd < 50) {
        ownerVillager->talkTopic = 4;
        SPEAK("q10_layout");
        out->msgKey = (const char *)sHouseVisitMsgFileName;
        u32 f = ownerVillager->roomRateFlags;
        if (f & 1) {
            out->msgIndex = Random_GlobalBelow(2);
        } else if (f & 2) {
            out->msgIndex = Random_GlobalBelow(2) + 2;
        } else if ((f & 4) == 0) {
            out->msgIndex = Random_GlobalBelow(2) + 4;
        } else if (f & 0x10) {
            out->msgIndex = 10;
        } else if (f & 0x20) {
            out->msgIndex = Random_GlobalBelow(2) + 8;
        } else {
            out->msgIndex = Random_GlobalBelow(2) + 6;
        }
        ((Unk_ov068_02270a6c_Bits *)HouseVisit_GetErrands()->houseVisitInvite.unk_20)->lo = n;
    } else if (rnd < 70) {
        ownerVillager->talkTopic = 0;
        setTopicFns(sHouseVisitTsuTopicTable);
        VillagerTalk::start((TalkStartMsg *)out);
    } else {
        ownerVillager->talkTopic = 0;
        setTopicFns(data_021be810);
        VillagerTalk::start((TalkStartMsg *)out);
    }
}

void HouseVisitVillagerTalk::onMessageStart(u32 a) {
    if (ownerVillager->talkTopic == 0) {
        VillagerTalk::onMessageStart(a);
    }
}

void HouseVisitVillagerTalk::onMessageEnd(u32 a) {
    u8 buf[2];
    HouseVisitVillager *o = ownerVillager;
    u32 st = o->talkTopic;
    if (st == 0) {
        VillagerTalk::onMessageEnd(a);
    } else if (o != NULL) {
        if (st == 1) {
            o->setVisitState(2);
        } else if (st == 6 || st == 8) {
            o->talkTopic = 7;
            ((VillagerData *)ownerVillager->villagerData)->getVillagerId()->makeFileName(data_ov068_022712b8, 0x28, "q_bye");
            buf[0] = Random_GlobalBelow(3);
            ownerVillager->talk.window->setNextMessageIfUnset(buf, data_ov068_022712b8);
        } else if (st == 7) {
            buf[1] = gTalkMsgIndexEnd;
            ownerVillager->talk.window->setNextMessage(&buf[1], 0);
            ownerVillager->setVisitState(10);
            Snd_PlaySe(0x5f);
        }
    }
}

void HouseVisitVillagerTalk::onChoice(u32 a) {
    if (ownerVillager->talkTopic == 0) {
        VillagerTalk::onChoice(a);
    }
}

BOOL HouseVisitVillager::setVisitState(s32 idx) {
    static Unk_ov068_02270afc_BFn tbl[11] = {
        &HouseVisitVillager::enterVisitOutside,
        &HouseVisitVillager::enterVisitCall,
        &HouseVisitVillager::enterVisitDoorOpen,
        &HouseVisitVillager::enterVisitWalkIn,
        &HouseVisitVillager::enterVisitGreetEnd,
        &HouseVisitVillager::enterVisitStay,
        &HouseVisitVillager::enterVisitWander,
        &HouseVisitVillager::enterVisitIdle7,
        &HouseVisitVillager::enterVisitTalk,
        &HouseVisitVillager::enterVisitTalkWait,
        &HouseVisitVillager::enterVisitLeave,
    };
    if (idx < 11) {
        if ((this->*tbl[idx])()) {
            visitState = idx;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" DebugColor data_ov068_022712a8(0x1f, 0x14, 0x14, 0x1f);
extern "C" {
u8 sHouseVisitMsgFileName[0x28];
}
extern "C" ActorProfile sHouseVisitVillagerProfile = {(void *(*)())HouseVisitVillager_Create, 0x82, 0x86, 2, 0x5000, 0x5000, 0x3e800};
extern "C" DebugColor data_ov068_02271298(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov068_022712b0(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_022712a0(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_0227129c(0x14, 0x1f, 0x1f, 0x1f);
extern "C" HouseVisitStarText data_ov068_02270a3c = {{0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
extern "C" DebugColor data_ov068_022712a4(0x14, 0x18, 0x18, 0x1f);
extern "C" {
u8 data_ov068_022712b8[0x28];
}


void HouseVisitVillager::updateVisitState() {
    static Unk_ov068_02270afc_Fn tbl[11] = {
        &HouseVisitVillager::execVisitOutside,
        &HouseVisitVillager::execVisitCall,
        &HouseVisitVillager::execVisitDoorOpen,
        &HouseVisitVillager::execVisitWalkIn,
        &HouseVisitVillager::execVisitGreetEnd,
        &HouseVisitVillager::execVisitStay,
        &HouseVisitVillager::execVisitWander,
        &HouseVisitVillager::execVisitIdle7,
        &HouseVisitVillager::execVisitTalk,
        &HouseVisitVillager::execVisitTalkWait,
        &HouseVisitVillager::execVisitLeave,
    };
    if (visitState < 11) {
        (this->*tbl[visitState])();
    }
}



BOOL HouseVisitVillager::enterVisitOutside() {
    position.x = data_020c8cb4;
    position.z = data_020c8cb8 - 0x1000;
    moveAngleY = -0x8000;
    rotY = moveAngleY;
    moveCtrl.setTargetAngle(-0x8000);
    drawFn = NULL;
    collisionEnabled = 0;
    return TRUE;
}

void HouseVisitVillager::execVisitOutside() {
    if (HouseVisit_IsAppointmentNow(this)) {
        Actor *p = (Actor *)PlayerActor_GetActor(4);
        if (p) {
            VecFx32 v;
            VecFx32 *pv = &p->position;
            v.x = pv->x;
            v.y = pv->y;
            v.z = pv->z;
            if (Vec_DistXZ(&v, &position) > 0x4e66) {
                TalkRequest_AddPlayerTalk6(this, 0);
            }
        }
    }
}

BOOL HouseVisitVillager::enterVisitCall() {
    u32 loc[6];
    RoomScoreEvaluator *eval = (RoomScoreEvaluator *)loc;
    drawFn = NULL;
    collisionEnabled = 0;
    Ground_LockExit(0);
    RoomScoreEvaluator_Construct(eval);
    roomRateFlags = HappyRoom_RateMainRoom(eval, (s32 *)&roomStars);
    HouseVisitor_SetPresent();
    if (getVillagerData()) {
        VillagerState_SetRole(Villager_GetState((VillagerData *)getVillagerData()), 2);
    }
    callTimer = 30;
    Snd_SeEmitterPlayOneShot(&seEmitter, 0x4ca, 0x7f, 0);
    RoomScoreEvaluator_Destruct();
    return TRUE;
}

void HouseVisitVillager::execVisitCall() {
    if (callTimer > 0) {
        callTimer = callTimer - 1;
    }
    if (callTimer == 0) {
        talkCtrl.requestTalk(0, 1);
        callTimer = -1;
    }
}

BOOL HouseVisitVillager::enterVisitDoorOpen() {
    drawFn = NULL;
    collisionEnabled = 1;
    return TRUE;
}

void HouseVisitVillager::execVisitDoorOpen() {
    if (talk.window->state == 0) {
        Snd_SeEmitterPlayOneShot(&seEmitter, 0x4cb, 0x7f, 0);
        Building_PlayDoorChime();
        setVisitState(3);
    }
}

BOOL HouseVisitVillager::enterVisitWalkIn() {
    walkTarget.x = position.x;
    walkTarget.y = position.y;
    walkTarget.z = position.z;
    walkTarget.z = walkTarget.z - 0x2000;
    drawFn = NULL;
    collisionEnabled = 1;
    walkInTimer = 0x28;
    return TRUE;
}

void HouseVisitVillager::execVisitWalkIn() {
    if (walkInTimer == 1) {
        drawFn = &HouseVisitVillager::drawModel;
        actionCtrl.requestAction(1, 2, walkTarget.x, walkTarget.z, 0, 0, 0, 0, 0, 0);
    } else if (walkInTimer == 0) {
        if (actionCtrl.isActionDone()) {
            setVisitState(4);
        }
    }
    if (walkInTimer != 0) {
        walkInTimer = walkInTimer - 1;
    }
}

BOOL HouseVisitVillager::enterVisitGreetEnd() {
    if (talkCtrl.isBusy()) {
        return actionCtrl.requestStand(2, data_020c6cc8);
    } else {
        return actionCtrl.requestStand(1, data_020c6cc8);
    }
}

void HouseVisitVillager::execVisitGreetEnd() {
    if (setVisitState(5)) {
        TalkRequest_SetTargetDone(this);
    }
}

BOOL HouseVisitVillager::enterVisitStay() {
    wanderTimer = 5;
    moveCtrl.setSpeedPreset(1, 0x148, 0x25, 0x25);
    stayTimer = 0x258;
    return TRUE;
}

void HouseVisitVillager::execVisitStay() {
    if (talkCtrl.isBusy() == 0) {
        if (stayTimer == 0 || talksLeft == 0) {
            if (leaveTalkDelay == 0) {
                TalkRequest_AddPlayerTalk6(this, 0);
                wantsToLeave = 1;
                return;
            } else if (leaveTalkDelay != 0) {
                leaveTalkDelay = leaveTalkDelay - 1;
            }
        }
        if (stayTimer > 0) {
            stayTimer = stayTimer - 1;
        }
    }
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p) {
        VecFx32 v;
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
        if (Ground_IsOnLockedExit(&v)) {
            TalkRequest_AddPlayerTalk6(this, 0);
            playerAtExit = 1;
        }
    }
}

BOOL HouseVisitVillager::enterVisitWander() {
    if (actionCtrl.requestStand(1, data_020c6cc8)) {
        lookAt.setTarget(1, 0, NULL, &gVec3Zero, 4, data_020c6d1c, 1);
        Ground_LockExit(0);
        return TRUE;
    }
    return FALSE;
}

void HouseVisitVillager::execVisitWander() {
    VecFx32 v;
    VecFx32 tmp;
    VecFx32 *pv = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (visitState == 6) {
        if (talkCtrl.isBusy() == 0) {
            if (stayTimer == 0 || talksLeft == 0) {
                if (leaveTalkDelay == 0) {
                    TalkRequest_AddPlayerTalk6(this, 0);
                    wantsToLeave = 1;
                    return;
                }
                if (leaveTalkDelay > 0) {
                    leaveTalkDelay--;
                }
            }
            if (stayTimer > 0) {
                stayTimer--;
            }
        }
    }
    if (visitState == 6) {
        if (pv != NULL) {
            v.x = pv->x;
            v.y = pv->y;
            v.z = pv->z;
            if (Ground_IsOnLockedExit(&v)) {
                TalkRequest_AddPlayerTalk6(this, 0);
                playerAtExit = 1;
                return;
            }
        }
    }
    s32 d = data_020c8cbc;
    if (pv != NULL) {
        d = Vec_DistXZ(pv, &position);
    }
    if (collider.isHit != 0 || (visitState != 6 && d < 0x2334)) {
        if (actionCtrl.getAction() == 1 || visitState == 3) {
            if (actionCtrl.requestStand(2, data_020c6cc8)) {
                setVisitWalkSpeed();
                return;
            }
        }
    }
    if (actionCtrl.getAction() == 0) {
        if (wanderTimer != 0) {
            wanderTimer--;
        }
        if (wanderTimer == 0) {
            wanderAngle = Shared_Room_PickRandomWalkTarget(&walkTarget, &position, rotY);
            waypoint.x = walkTarget.x;
            waypoint.y = walkTarget.y;
            waypoint.z = walkTarget.z;
            if (wanderAngle != rotY) {
                if (!actionCtrl.requestAction(3, 1, 0, 0, 0, wanderAngle, 0, 0, data_020c6cc8, 0)) {
                    return;
                }
                wanderTimer = Random_GlobalBelow(0x46) + 0x14;
            } else {
                if (!actionCtrl.requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0)) {
                    return;
                }
                wanderTimer = Random_GlobalBelow(0x50) + 0x14;
            }
        } else {
            if (actionCtrl.isActionDone()) {
                actionCtrl.requestStand(1, data_020c6cc8);
            }
        }
    } else if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            actionCtrl.requestAction(1, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0);
        }
    } else if (actionCtrl.getAction() == 1) {
        switch (findAvoidPos(&tmp)) {
        case 1:
            if (actionCtrl.requestStand(1, data_020c6cc8)) {
                setVisitWalkSpeed();
            }
            break;
        case 2:
            waypoint.x = tmp.x;
            waypoint.y = tmp.y;
            waypoint.z = tmp.z;
            moveCtrl.setWaypoint(&waypoint);
            break;
        default:
            if (Vec_NotEqual(&waypoint, &walkTarget) != 0) {
                waypoint.x = walkTarget.x;
                waypoint.y = walkTarget.y;
                waypoint.z = walkTarget.z;
                moveCtrl.setWaypoint(&walkTarget);
            } else if (Vec_DistXZ(&walkTarget, &position) < 0x200) {
                actionCtrl.requestStand(1, data_020c6cc8);
                setVisitWalkSpeed();
            }
            break;
        }
    }
}

BOOL HouseVisitVillager::enterVisitIdle7() {
    return TRUE;
}

void HouseVisitVillager::execVisitIdle7() {}

BOOL HouseVisitVillager::enterVisitTalk() {
    void *p = PlayerActor_GetActor(4);
    if (p != NULL) {
        u32 x = getAngleTo((NpcActor *)p);
        if (wantsToLeave != 0 || playerAtExit != 0) {
            talkCtrl.requestTurnAndTalk(0, x, 1);
        } else {
            talkCtrl.requestTurnAndTalk(0, x, 0);
        }
        return TRUE;
    }
    return FALSE;
}

void HouseVisitVillager::execVisitTalk() {
    setVisitState(9);
}

BOOL HouseVisitVillager::enterVisitTalkWait() {
    return TRUE;
}

void HouseVisitVillager::execVisitTalkWait() {
    if (talk.window != NULL) {
        if (talk.window->state == 0) {
            TalkRequest_SetTargetDone(this);
        }
    }
}

BOOL HouseVisitVillager::enterVisitLeave() {
    return TRUE;
}

void HouseVisitVillager::execVisitLeave() {
    if (talk.window != NULL) {
        if (talk.window->state == 0) {
            HouseVisitor_ClearPresent();
            if (getVillagerData() != NULL) {
                VillagerState_ResetRole(Villager_GetState((VillagerData *)getVillagerData()));
            }
            HouseVisit_SetFinished(this);
            if (wantsToLeave != 0) {
                Scene_SavePlayerPos(0, 0);
                SceneWarp_RequestExit(Scene_GetWarpRequest(), 6);
            } else {
                SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
            }
        }
    }
}

void HouseVisitVillager::onTalkMelodyPlayed() {
    mood.severeSickness = 1;
}

BOOL HouseVisitVillager::canPlayTalkMelody() {
    if (mood.severeSickness == 0) {
        return TRUE;
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0226dbe8) {
    HOST_OVERLAY_VAR(sHouseVisitVillager),
    HOST_OVERLAY_VAR(data_ov068_022712a8),
    HOST_OVERLAY_VAR(sHouseVisitMsgFileName),
    HOST_OVERLAY_VAR(sHouseVisitVillagerProfile),
    HOST_OVERLAY_VAR(data_ov068_02271298),
    HOST_OVERLAY_VAR(data_ov068_022712b0),
    HOST_OVERLAY_VAR(data_ov068_022712a0),
    HOST_OVERLAY_VAR(data_ov068_0227129c),
    HOST_OVERLAY_VAR(data_ov068_02270a3c),
    HOST_OVERLAY_VAR(data_ov068_022712a4),
    HOST_OVERLAY_VAR(data_ov068_022712b8),
    HOST_OVERLAY_VARS_END
};

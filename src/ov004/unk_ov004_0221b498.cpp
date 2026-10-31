#include "types.h"
#include "gfx/VecFx32.h"



#include "types.h"
#include "actor/ActorProfile.h"
#include "talk/TalkTopicMsg.h"
#include "net/CommManager.h"
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
#include "npc/NpcLookAt.h"
#include "player/PlayerData.h"
#include "player/PlayerSpNpcRecord.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c37c.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov004/unk_ov004_0221b498.h"
#include "proto/ov004/unk_ov004_02228700.h"


class ActorTalkRequest;















struct SpNpcSableTalkRange {
    u8 firstMsg;
    s32 count;
};

struct Unk_ov004_0221b6d4_Bits {
    u8 a : 2;
    u8 b : 3;
    u8 c : 3;
};


extern "C" {
extern CommManager *gCommManager;
extern s32 data_020c6d1c;
extern u16 data_020c6cc8;
extern VecFx32 gVec3Zero;
extern const u8 sSpNpcSableDramaMsgs[4][7];
extern const u8 sSpNpcSableWeekdayMsgs[8];
extern const SpNpcSableTalkRange sSpNpcSableTalkMsgs[12];
extern const char *sSpNpcSableMsgFiles[3];

BOOL Talk_CheckAndSetPlayerFlag(s32 a, s32 b);
BOOL Talk_IsDramaPending(void *self, void *out, s32 x);
void Talk_AdvanceDrama(void *self, void *p);
s32 Clock_GetWeekday();
void TalkRequest_SetTargetDone(void *self);
}

class SpNpcSable;

class SpNpcSableTalk : public SpNpcTalkRequest {
public:
    SpNpcSableTalk();
    virtual ~SpNpcSableTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(SpNpcSable *o);

    /* 0xac */ SpNpcSable *owner;
};

class SpNpcSable : public SpNpcActor {
public:
    SpNpcSable() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 idx, u8 v);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();
    virtual void onLeaveTalk();

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
    void changeAct(s32 state);

    s32 act;
    SpNpcSableTalk talk;
    s16 homeAngle;
    u8 isDramaTalk;
    u8 pad_70b;
    u16 resumeFrame;
    u8 sewCycle;
};

struct SpNpcSableActEntry {
    BOOL (SpNpcSable::*enter)();
    BOOL (SpNpcSable::*update)();
};

extern "C" {
extern SpNpcSableActEntry sSpNpcSableActTable[7];
}


extern "C" SpNpcSable *SpNpcSable_Create() { return new SpNpcSable; }

BOOL SpNpcSable::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    ((NpcActor *)(this))->setTalkRequest((ActorTalkRequest *)(&talk));
    talk.attachOwner(this);
    ((SpNpcActor *)(this))->setColliderSize(0x119a, 0x2000);
    ((NpcActor *)(this))->setCollisionRadius(0);
    ((Character *)(this))->setInteractionRange(0x3000);
    return TRUE;
}

BOOL SpNpcSable::onCreate() {
    s32 v;
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    homeAngle = rotY;
    collider.groups |= 2;
    if (((CommManager *)(gCommManager))->isOnline() || *DebugVar_GetPtr(0, 0x4a) != 0) {
        if (NetArea_IsLocalOwner()) {
            changeAct(0);
        } else {
            ((NpcActor *)(this))->getNetUserBytes(&sewCycle, 1);
            changeAct(4);
        }
    } else {
        changeAct(0);
        if (Talk_IsDramaPending(this, &v, 2)) {
            isDramaTalk = 1;
        }
    }
    return TRUE;
}

u8 *SpNpcSable::getTexturePath() { return sSpNpcSableTexturePath; }

u8 *SpNpcSable::getModelPath() { return sSpNpcSableModelPath; }

BOOL SpNpcSable::updateAct() {
    sewCycle = SewingMachine_GetFrame() / 0x38;
    ((NpcActor *)(this))->setNetUserBytes(&sewCycle, 1);
    BOOL r = FALSE;
    if (sSpNpcSableActTable[act].update) {
        r = (this->*sSpNpcSableActTable[act].update)();
    }
    return r;
}

void SpNpcSable::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcSableActTable[state].enter) {
        ok = (this->*sSpNpcSableActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcSable::setupAct00() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xe4, 0, data_020c6cc8, resumeFrame);
    return TRUE;
}

BOOL SpNpcSable::mainAct00() {
    if (homeAngle != rotY) {
        changeAct(3);
        return TRUE;
    }
    if (((NpcAnimCtrl *)(&animCtrl))->isPlayingAnim(0xe4, &moveAnimSet)) {
        if (SewingMachine_IsStopped()) {
            SewingMachine_Start();
            u32 t = sewCycle * 0x38;
            SewingMachine_SetFrame((u16)(t + (((u32)model.curFrame << 4) >> 16)));
        }
    }
    return TRUE;
}

BOOL SpNpcSable::setupAct01() {
    if (SpNpcSable_GetTalkCount(this) >= 6) {
        ((NpcLookAt *)(&lookAt))->setTarget(1, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    }
    SewingMachine_Stop();
    if (SpNpcSable_GetTalkCount(this) < 6) {
        ((NpcTalkCtrl *)(&talkCtrl))->requestTalk(1, 0);
    } else {
        NpcActor *p = (NpcActor *)talk.getTalkPlayer();
        s32 r = 0;
        if (p) {
            r = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
        }
        ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r, 0);
    }
    return TRUE;
}

BOOL SpNpcSable::mainAct01() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy()) {
        return TRUE;
    }
    if (!((CommManager *)(gCommManager))->isOnline() && !Talk_CheckAndSetPlayerFlag(0x11, 1)) {
        u32 t = (u8)(SpNpcSable_GetTalkCount(this) + 1);
        if (t > 0xf) {
            t = 0xf;
        }
        SpNpcSable_SetTalkCount(this, t);
    }
    TalkRequest_SetTargetDone(this);
    changeAct(2);
    return TRUE;
}

BOOL SpNpcSable::setupAct02() { return TRUE; }

BOOL SpNpcSable::mainAct02() { return TRUE; }

BOOL SpNpcSable::setupAct03() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcSable::mainAct03() {
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcSable::setupAct04() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcSable::mainAct04() {
    s32 a, b;
    if (((NpcActor *)(this))->isNetOwner()) {
        a = 4;
        b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b)) {
            s32 av = a;
            s32 g = gCommManager->myAid;
            if (av == g && av == b) {
                ((NpcActor *)(this))->netSetSlotsIfOwner(1, g, g);
                ActorTalkRequest *p = &talk;
                p->resetMsg();
                ((ActorTalkRequest *)(&talk))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
                changeAct(1);
                goto end;
            }
        }
        if (NetArea_IsLocalOwner() && b == 4) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0);
        }
    } else if (!NetArea_IsLocalOwner()) {
        if (((NpcAnimCtrl *)(&animCtrl))->isPlayingAnim(0xe4, &moveAnimSet)) {
            if (SewingMachine_IsStopped()) {
                SewingMachine_Start();
                u32 t = sewCycle * 0x38;
                SewingMachine_SetFrame((u16)(t + (((u32)model.curFrame << 4) >> 16)));
            }
        } else if (!SewingMachine_IsStopped()) {
            SewingMachine_Stop();
        }
    }
end:
    return TRUE;
}

BOOL SpNpcSable::setupAct05() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
    return TRUE;
}

BOOL SpNpcSable::mainAct05() {
    if (((NpcActor *)(this))->isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b) && a == 4 && NetArea_IsLocalOwner()) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcSable::setupAct06() {
    SewingMachine_Stop();
    resumeFrame = model.curFrame >> 12;
    return TRUE;
}

BOOL SpNpcSable::mainAct06() { return TRUE; }

void SpNpcSable::onLeaveTalk() {
    ((NpcLookAt *)(&lookAt))->setTarget(0, 0, 0, &gVec3Zero, 4, data_020c6d1c, 1);
}

SpNpcSableTalk::SpNpcSableTalk() {}

SpNpcSableTalk::~SpNpcSableTalk() {}

void SpNpcSableTalk::attachOwner(SpNpcSable *o) {
    resetMsg();
    owner = o;
}

void SpNpcSableTalk::start(TalkStartMsg *out_) {
    TalkStartMsg *out = out_;
    u32 idx = SpNpcSable_GetTalkCount(owner);
    void *g = gCommManager;
    if (((CommManager *)(g))->isOnline() != 0 || *(s16 *)DebugVar_GetPtr(0, 0x4a) != 0) {
        idx = 0;
        out->msgIndex = 0x57;
    } else if (GameStart_IsActive() != 0) {
        idx = 2;
        out->msgIndex = 5;
    } else {
        Unk_ov004_0221b6d4_Bits bits;
        if (Talk_IsDramaPending(owner, &bits, 2) != 0) {
            idx = 1;
            owner->isDramaTalk = idx;
            out->msgIndex = sSpNpcSableDramaMsgs[bits.b][bits.c];
            Talk_AdvanceDrama(owner, &bits);
        } else if (Talk_CheckAndSetPlayerFlag(0x10, 1) == 0) {
            if (idx >= 0xc) {
                out->msgIndex = sSpNpcSableWeekdayMsgs[Clock_GetWeekday()];
            } else {
                out->msgIndex = sSpNpcSableTalkMsgs[idx].firstMsg;
            }
            idx = 0;
        } else {
            if (idx > 0xc) {
                out->msgIndex = Random_GlobalBelow(5) + 0x28;
            } else {
                s32 t = idx - 1;
                if (t < 0) {
                    t = 0;
                } else if (t > 0xb) {
                    t = 0xb;
                }
                s32 r = Random_GlobalBelow(sSpNpcSableTalkMsgs[t].count) + 1;
                out->msgIndex = r + sSpNpcSableTalkMsgs[t].firstMsg;
            }
            idx = 0;
        }
    }
    out->msgKey = sSpNpcSableMsgFiles[idx];
    if (((CommManager *)(g))->isOnline() == 0 && *(s16 *)DebugVar_GetPtr(0, 0x4a) == 0 && idx == 0) {
        switch (out->msgIndex) {
        case 2:
        case 5:
        case 8:
        case 9:
        case 12:
        case 15:
        case 17:
        case 18:
        case 19:
        case 21:
        case 23:
        case 24:
        case 27:
        case 28:
        case 30:
        case 40:
        case 43: {
            void *r = NpcRegistry_FindSpNpc(4);
            if (r) {
                ((ActorTalkRequest *)(this))->setPartnerActor((NpcActor *)(r));
            }
            break;
        }
        }
    }
}

void SpNpcSableTalk::onMessageEnd(u32) {}

void SpNpcSableTalk::onChoice(u32) {}

BOOL SpNpcSable::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || ((NpcActor *)(this))->netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcSable::onInteractionEvent(u32 idx, u8 v) {
    switch (idx) {
    case 3:
        partnerPlayer = v;
        if (v != 4) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, v);
            changeAct(6);
        } else {
            if (((NpcActor *)(this))->isNetOwner() != 0) {
                s32 g = gCommManager->myAid;
                ((NpcActor *)(this))->netSetSlotsIfOwner(1, g, g);
                changeAct(6);
            }
        }
        break;
    case 0:
        partnerPlayer = v;
        if (v != 4 && v != gCommManager->myAid) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, v, v);
            changeAct(5);
        } else {
            if (((NpcActor *)(this))->isNetOwner() != 0) {
                s32 g = gCommManager->myAid;
                ((NpcActor *)(this))->netSetSlotsIfOwner(1, g, g);
                talk.resetMsg();
                ((ActorTalkRequest *)(&talk))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
                changeAct(1);
            }
        }
        break;
    case 8:
        if (v == 4) {
            if (NetArea_IsLocalOwner() != 0) {
                ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                changeAct(3);
            } else {
                ((NpcActor *)(this))->netSetSlotsIfOwner(1, 4, gCommManager->myAid);
                changeAct(4);
            }
        }
        break;
    case 4:
        if (((NpcActor *)(this))->netIsTalkLocked() != 0) {
            if (((NpcActor *)(this))->isNetOwner() != 0) {
                s32 a = 4;
                s32 b = 4;
                if (((NpcActor *)(this))->netGetSlots(&a, &b) != 0) {
                    if (v == 4) {
                        goto chk;
                    }
                    if (v == b) {
                        goto body;
                    }
                chk:
                    if (v != 4) {
                        break;
                    }
                body:
                    ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                    changeAct(0);
                }
            }
        }
        break;
    }
    NpcActor::onInteractionEvent(idx, v);
}

extern "C" u32 SpNpcSable_GetTalkCount(void *unused) {
    return ((PlayerSpNpcRecord *)(PlayerData_GetCurrent()->getSpNpcRecord()))->getSableTalkCount();
}

extern "C" void SpNpcSable_SetTalkCount(void *unused, u32 a) {
    ((PlayerSpNpcRecord *)(PlayerData_GetCurrent()->getSpNpcRecord()))->setSableTalkCount(a);
}


extern "C" const u8 sSpNpcSableWeekdayMsgs[8] = {0x27, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x00};
extern "C" const u8 sSpNpcSableDramaMsgs[4][7] = {
    {0, 1, 2, 3, 0xfe, 0xfe, 0xfe}, {4, 5, 6, 0xfe, 0xfe, 0xfe, 0xfe}, {7, 8, 9, 10, 11, 0xfe, 0xfe}, {11, 12, 13, 14, 15, 16, 17},
};
extern "C" const SpNpcSableTalkRange sSpNpcSableTalkMsgs[12] = {
    {0, 5}, {0, 5}, {0, 5}, {6, 2}, {9, 2}, {12, 2}, {15, 2}, {18, 2}, {21, 2}, {24, 2}, {27, 2}, {30, 2},
};
extern "C" u8 data_ov004_0224cd04[14] = {'s', 'p', '_', 'n', 'p', 'c', '_', 'd', 'r', 'a', 'm', 'a', '3', 0};
extern "C" u8 data_ov004_0224cd14[15] = {'s', 'p', '_', 'n', 'p', 'c', '_', 'o', 's', 'i', 's', 't', 'e', 'r', 0};
extern "C" u8 data_ov004_0224cd24[17] = {'s', 'p', '_', 'e', 't', 'c', '_', 's', 'e', 'q', 'u', 'e', 'n', 'c', 'e', '4', 0};
extern "C" const char *sSpNpcSableMsgFiles[3] = {(const char *)data_ov004_0224cd14, (const char *)data_ov004_0224cd04, (const char *)data_ov004_0224cd24};
extern "C" u8 sSpNpcSableModelPath[23] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'h', 'g', 's', '.', 'n', 's', 'b', 'm', 'd', 0};
extern "C" u8 sSpNpcSableTexturePath[27] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'h', 'g', 's', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" ActorProfile sSpNpcSableProfile = {(void *(*)())SpNpcSable_Create, 0x77, 0x7c, 2, 0x5000, 0x5000, 0x3e800};
extern "C" SpNpcSableActEntry sSpNpcSableActTable[7] = {
    {&SpNpcSable::setupAct00, &SpNpcSable::mainAct00},
    {&SpNpcSable::setupAct01, &SpNpcSable::mainAct01},
    {&SpNpcSable::setupAct02, &SpNpcSable::mainAct02},
    {&SpNpcSable::setupAct03, &SpNpcSable::mainAct03},
    {&SpNpcSable::setupAct04, &SpNpcSable::mainAct04},
    {&SpNpcSable::setupAct05, &SpNpcSable::mainAct05},
    {&SpNpcSable::setupAct06, &SpNpcSable::mainAct06},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221b498) {
    HOST_OVERLAY_VAR(data_ov004_0224cd04),
    HOST_OVERLAY_VAR(data_ov004_0224cd14),
    HOST_OVERLAY_VAR(data_ov004_0224cd24),
    HOST_OVERLAY_VAR(sSpNpcSableMsgFiles),
    HOST_OVERLAY_VAR(sSpNpcSableModelPath),
    HOST_OVERLAY_VAR(sSpNpcSableTexturePath),
    HOST_OVERLAY_VAR(sSpNpcSableProfile),
    HOST_OVERLAY_VAR(sSpNpcSableActTable),
    HOST_OVERLAY_VARS_END
};

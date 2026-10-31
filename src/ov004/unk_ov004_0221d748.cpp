#include "types.h"
#include "host_labels.h"


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
#include "npc/NpcMoveAnimSet.h"
#include "player/PlayerData.h"
#include "save/Pattern.h"
#include "save/PatternOrder.h"
#include "npc/SickVillagerRecord.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02039c08.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_02082d74.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov004/unk_ov004_0221d748.h"


class ActorTalkRequest;
















class SpNpcBookerTalk;
class SpNpcBooker;

typedef void (SpNpcBookerTalk::*Unk_ov004_0224d248_Fn)();
typedef BOOL (SpNpcBooker::*Unk_ov004_0224d2d8_Fn)();

struct SpNpcBookerTalkScript {
    Unk_ov004_0224d248_Fn fn;
    u8 flag;
    u8 pad[3];
};

struct SpNpcBookerActEntry {
    Unk_ov004_0224d2d8_Fn enter;
    Unk_ov004_0224d2d8_Fn update;
};


extern "C" {
extern CommManager *gCommManager;
extern s32 data_020c6d1c;
extern u16 data_020c6cc8;
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern SpNpcBookerTalkScript sSpNpcBookerTalkScripts[];
extern SpNpcBookerActEntry sSpNpcBookerActTable[];
extern const char *sSpNpcBookerMsgFiles[1];

s32 Talk_IsInOwnTown(void);
void TalkRequest_SetTargetDone(void *p);
s32 SaveVillagers_GetUnk3830Index(void *p);
SickVillagerRecord *SaveVillagers_GetUnk3830(void *p);
s32 Scene_GetCurrent(void);
}

class SpNpcBookerTalk : public ActorTalkRequest {
public:
    SpNpcBookerTalk();
    virtual ~SpNpcBookerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void runScript03();
    void runScript02();
    void runScript01();
    void setScript(s32 v);
    void attachOwner(NpcActor *o);

    /* 0xac */ NpcActor *owner;
    /* 0xb0 */ s32 scriptIndex;
};

class SpNpcBooker : public SpNpcActor {
public:
    SpNpcBooker() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 cmd, u8 arg);
    virtual BOOL acceptsSelfRequestedInteraction(void *p);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

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

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcBookerTalk talk;
    /* 0x70c */ s16 homeAngle;
    /* 0x70e */ u8 pad_70e[2];
};


struct ItemIdRange {
    static inline BOOL Chk(u16 *p, u32 lo, u32 hi) {
        BOOL r = FALSE;
        if (*p >= lo && *p <= hi) {
            r = TRUE;
        }
        return r;
    }
};

extern "C" SpNpcBooker *SpNpcBooker_Create() { return new SpNpcBooker; }

BOOL SpNpcBooker::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    ((NpcActor *)(this))->setTalkRequest((ActorTalkRequest *)(&talk));
    talk.attachOwner(this);
    ((NpcActor *)(this))->setCollisionRadius(0x100);
    ((NpcMoveAnimSet *)(&moveAnimSet))->setWalkAnim(0xd9);
    ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0xd8);
    if (Scene_GetCurrent() != 0xb) {
        netSyncOff = 1;
    }
    return TRUE;
}

BOOL SpNpcBooker::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    homeAngle = rotY;
    collider.groups |= 2;
    if (((CommManager *)(gCommManager))->isOnline() && Scene_GetCurrent() == 0xb) {
        if (((NpcActor *)(this))->isNetOwner()) {
            changeAct(0);
        } else {
            changeAct(4);
        }
    } else {
        changeAct(0);
    }
    return TRUE;
}

BOOL SpNpcBooker::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    CommManager *g = gCommManager;
    if (((CommManager *)(g))->isSlotActive(g->myAid) && !((CommManager *)(g))->isOnline()) {
        void *p = gSaveVillagers;
        if (SaveVillagers_GetUnk3830Index(p) != -1) {
            SaveVillagers_GetUnk3830(p)->resetRecord();
        }
    }
    return TRUE;
}

u8 *SpNpcBooker::getTexturePath() { return sSpNpcBookerTexturePath; }

u8 *SpNpcBooker::getModelPath() { return sSpNpcBookerModelPath; }

BOOL SpNpcBooker::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcBookerActTable[act].update) {
        r = (this->*sSpNpcBookerActTable[act].update)();
    }
    return r;
}

void SpNpcBooker::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcBookerActTable[state].enter) {
        ok = (this->*sSpNpcBookerActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcBooker::setupAct00() {
    ((NpcActionCtrl *)(&actionCtrl))->requestStand(1, data_020c6cc8);
    return TRUE;
}

BOOL SpNpcBooker::mainAct00() { return TRUE; }

BOOL SpNpcBooker::setupAct01() {
    ActorTalkRequest *p = &talk;
    p->resetMsg();
    ((ActorTalkRequest *)(&talk))->setTalkPlayer(((NpcActor *)(this))->getPlayerActor(4));
    void *q = ((ActorTalkRequest *)(&talk))->getTalkPlayer();
    s32 r = 0;
    if (q) {
        r = ((NpcActor *)(this))->getAngleTo((NpcActor *)(q));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcBooker::mainAct01() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy()) {
        return TRUE;
    }
    if (!((NpcTalkCtrl *)(&talkCtrl))->isBusy()) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcBooker::setupAct02() { return TRUE; }

BOOL SpNpcBooker::mainAct02() { return TRUE; }

BOOL SpNpcBooker::setupAct03() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(3, 1, 0, 0, 0, homeAngle, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcBooker::mainAct03() {
    if (((NpcActionCtrl *)(&actionCtrl))->getAction() == 3) {
        if (((NpcActionCtrl *)(&actionCtrl))->isActionDone()) {
            changeAct(0);
        }
    }
    return TRUE;
}

BOOL SpNpcBooker::setupAct04() { return TRUE; }

BOOL SpNpcBooker::mainAct04() {
    s32 a, b;
    if (((NpcActor *)(this))->isNetOwner()) {
        a = 4;
        b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b)) {
            s32 av = a;
            s32 g = gCommManager->myAid;
            if (av == g && av == b) {
                ((NpcActor *)(this))->netSetSlotsIfOwner(1, g, g);
                changeAct(1);
                goto end;
            }
        }
        if (NetArea_IsLocalOwner() && b == 4) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(0);
        }
    }
end:
    return TRUE;
}

BOOL SpNpcBooker::setupAct05() { return TRUE; }

BOOL SpNpcBooker::mainAct05() {
    if (((NpcActor *)(this))->isNetOwner()) {
        s32 a = 4;
        s32 b = 4;
        if (((NpcActor *)(this))->netGetSlots(&a, &b) && a == 4 && NetArea_IsLocalOwner()) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
            changeAct(3);
        }
    }
    return TRUE;
}

BOOL SpNpcBooker::setupAct06() { return TRUE; }


BOOL SpNpcBooker::mainAct06() { return TRUE; }

SpNpcBookerTalk::SpNpcBookerTalk() {}

SpNpcBookerTalk::~SpNpcBookerTalk() {}

void SpNpcBookerTalk::attachOwner(NpcActor *o) {
    resetMsg();
    owner = o;
}

void SpNpcBookerTalk::start(TalkStartMsg *out) {
    void *g = PlayerData_GetCurrent();
    if (Talk_IsInOwnTown() == 0 || GameStart_IsActive() != 0) {
        out->msgIndex = Random_GlobalBelow(3) + 8;
    } else if (((PlayerData *)(g))->testFlag(0x1b) == 0) {
        out->msgIndex = 0;
        ((PlayerData *)(g))->setFlag(0x1b);
    } else {
        out->msgIndex = Random_GlobalBelow(4) + 4;
    }
    out->msgKey = sSpNpcBookerMsgFiles[0];
}

void SpNpcBookerTalk::onMessageEnd(u32) {
    switch (msgIndex) {
    case 0x1a:
        ((ActorTalkRequest *)(this))->setSubSceneKind(0x1f, 0);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(3);
        break;
    case 0x17:
        ((ActorTalkRequest *)(this))->setSubSceneKind(9, 0);
        ((ActorTalkRequest *)(this))->openSubScene(2);
        setScript(2);
        break;
    }
}

void SpNpcBookerTalk::onChoice(u32) {
    u8 c;
    u16 x;
    void *o = window;
    s32 t = ((ChoiceList *)(((TalkWindowState *)(o))->getChoiceList()))->getResult();
    const char *d = sSpNpcBookerMsgFiles[0];
    u32 r = 0xff;
    switch (msgIndex) {
    case 0xf:
        if (t == 0) {
            CommManager *s = gCommManager;
            if (((CommManager *)(s))->isSlotActive(s->myAid) != 0) {
                if (((CommManager *)(s))->isOnline() != 0) {
                    PlayerData *q = PlayerData_GetBySessionSlot(JoinHistory_GetLatest());
                    if (q != 0) {
                        ((ActorTalkRequest *)this)->setPlayerNameSlot(q->getPlayerId(), 1);
                    }
                    r = 0x30;
                } else {
                    r = 0x2f;
                }
            } else {
                Visitor_GetTodaysNpc(&x);
                switch (x) {
                case 0xd00a:
                    r = 0x22;
                    break;
                case 0xd00e:
                    r = 0x23;
                    break;
                case 0xd003:
                    r = 0x24;
                    break;
                case 0xd013:
                    r = 0x25;
                    break;
                case 0xd00b:
                    r = 0x26;
                    break;
                case 0xd002:
                    r = 0x27;
                    break;
                case 0xd00d:
                    r = 0x28;
                    break;
                case 0xd021:
                    r = 0x29;
                    break;
                case 0xd020:
                    r = 0x2a;
                    break;
                case 0xd022:
                    r = 0x2b;
                    break;
                case 0xd023:
                    r = 0x2c;
                    break;
                default:
                    r = 0x2e;
                    break;
                }
            }
        } else if (t == 1) {
            if (LostAndFound_HasAny() != 0) {
                ((ActorTalkRequest *)(this))->setNumberSlot(LostAndFound_Count(), 0, 2, 0, 0);
                r = 0x1a;
            } else {
                r = 0x1b;
            }
        }
        break;
    case 0x16:
        if (t == 0) {
            ((ActorTalkRequest *)(this))->setSubSceneKind(6, 0);
            ((ActorTalkRequest *)(this))->openSubScene(2);
            setScript(1);
        }
        break;
    }
    if (r != 0xff) {
        c = r;
        ((TalkWindowState *)(o))->setNextMessage((u8 *)(&c), (void *)(d));
    }
}

void SpNpcBookerTalk::update() {
    s32 i = scriptIndex;
    if (sSpNpcBookerTalkScripts[i].flag != 0) {
        if (sSpNpcBookerTalkScripts[i].fn != 0) {
            (this->*sSpNpcBookerTalkScripts[i].fn)();
        }
    }
}

void SpNpcBookerTalk::onTaskDone(u32) {
    s32 i = scriptIndex;
    if (sSpNpcBookerTalkScripts[i].flag == 0) {
        if (sSpNpcBookerTalkScripts[i].fn != 0) {
            (this->*sSpNpcBookerTalkScripts[i].fn)();
            setScript(0);
        }
    }
}

void SpNpcBookerTalk::setScript(s32 v) {
    scriptIndex = v;
}

void SpNpcBookerTalk::runScript01() {
    u8 buf[2];
    if (MenuCtrl_IsResultOk() != 0) {
        void *g = PlayerData_GetCurrent();
        u32 idx = MenuCtrl_GetIndex();
        s32 t = ((PatternOrder *)(((PlayerPatterns *)(((PlayerData *)(g))->getPatterns()))->getPatternOrder()))->getSlot(idx);
        PatternSrc_Copy(9, t, 5, 0, 1);
        Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x50, 0x7f, 0);
        buf[0] = 0x18;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(buf), (void *)sSpNpcBookerMsgFiles[0]);
    } else {
        buf[1] = 1;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(&buf[1]), (void *)sSpNpcBookerMsgFiles[0]);
    }
}

void SpNpcBookerTalk::runScript02() {
    struct {
        u8 c0;
        u8 c1;
        u16 a;
        u16 b;
    } m;
    if (MenuCtrl_IsResultOk() != 0) {
        void *g = PlayerData_GetCurrent();
        u32 idx = MenuCtrl_GetIndex();
        u32 t = ((PatternOrder *)(((PlayerPatterns *)(((PlayerData *)(g))->getPatterns()))->getPatternOrder()))->getSlot(idx);
        PatternSrc_Swap(9, t, 5, 0, 1);
        Snd_SeEmitterPlayOneShotAlt(&owner->seEmitter, 0x50, 0x7f, 0);
        u32 x;
        u32 y;
        if (t < 8) {
            x = (u16)(t + 0x12a8);
        } else {
            x = 0x12a8;
        }
        if (t < 8) {
            y = (u16)(t + 0x1429);
        } else {
            y = 0x1429;
        }
        u32 p1 = *((PlayerData *)(g))->getShirt();
        u32 p2 = *((PlayerData *)(g))->getHat();
        if (x == p1) {
            if (ItemIdRange::Chk(((PlayerData *)(g))->getShirt(), 0x12a8, 0x12af)) {
                m.a = x;
                PlayerActor_RequestWearShirtAlt(&m.a);
            }
        }
        if (y == p2) {
            if (ItemIdRange::Chk(((PlayerData *)(g))->getHat(), 0x1429, 0x1430)) {
                m.b = y;
                PlayerActor_RequestWearHatAlt(&m.b);
            }
        }
        m.c0 = 0x19;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(&m), (void *)sSpNpcBookerMsgFiles[0]);
    } else {
        m.c1 = 1;
        ((TalkWindowState *)(window))->setNextMessage((u8 *)(&m.c1), (void *)sSpNpcBookerMsgFiles[0]);
    }
}


void SpNpcBookerTalk::runScript03() {
    void *o = window;
    u8 c;
    u16 v;
    c = 0x20;
    if (MenuCtrl_IsResultOk() != 0) {
        if (MenuCtrl_GetIndex() > 1) {
            c = 0x1c;
        } else {
            v = *MenuCtrl_GetChosenItems();
            ((ActorTalkRequest *)(this))->setItemNameSlot(&v, 0, 7);
            c = 0x1e;
        }
    }
    ((TalkWindowState *)(o))->setNextMessage((u8 *)(&c), (void *)sSpNpcBookerMsgFiles[0]);
}

BOOL SpNpcBooker::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || ((NpcActor *)(this))->netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

BOOL SpNpcBooker::acceptsSelfRequestedInteraction(void *p) {
    if (netSyncOff != 0) {
        return TRUE;
    }
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || ((NpcActor *)(this))->netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcBooker::onInteractionEvent(u32 cmd, u8 arg) {
    s32 a;
    s32 b;
    switch (cmd) {
    case 3:
        partnerPlayer = arg;
        if (arg != 4) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, arg);
            changeAct(6);
            break;
        }
        if (((NpcActor *)(this))->isNetOwner() != 0) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, gCommManager->myAid);
            changeAct(6);
        }
        break;
    case 1:
        changeAct(1);
        break;
    case 0:
        partnerPlayer = arg;
        if (arg != 4 && arg != gCommManager->myAid) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, arg, arg);
            changeAct(5);
            break;
        }
        if (((NpcActor *)(this))->isNetOwner() != 0) {
            ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, gCommManager->myAid);
            changeAct(1);
        }
        break;
    case 8:
        if (arg == 4) {
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
                a = 4;
                b = 4;
                if (((NpcActor *)(this))->netGetSlots(&a, &b) != 0) {
                    if ((arg != 4 && arg == (u32)b) || arg == 4) {
                        ((NpcActor *)(this))->netSetSlotsIfOwner(1, gCommManager->myAid, 4);
                        changeAct(0);
                    }
                }
            }
        }
        break;
    }
}



extern "C" u8 data_ov004_0224d1e0[19] = {'s', 'p', '_', 'n', 'p', 'c', '_', 'g', 'a', 't', 'e', 'k', 'e', 'e', 'p', 'e', 'r', '2', 0};
extern "C" u8 data_ov004_0224d1f4[23] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'p', 'l', 'a', '.', 'n', 's', 'b', 'm', 'd', 0};
extern "C" u8 data_ov004_0224d224[27] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 'p', 'l', 'a', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" const char *sSpNpcBookerMsgFiles[1] = {(const char *)data_ov004_0224d1e0};
extern "C" u8 *sSpNpcBookerModelPath = data_ov004_0224d1f4;
extern "C" u8 *sSpNpcBookerTexturePath = data_ov004_0224d224;
extern "C" ActorProfile sSpNpcBookerProfile = {(void *(*)())SpNpcBooker_Create, 0x73, 0x78, 2, 0x5000, 0x5000, 0x3e800};
extern "C" SpNpcBookerTalkScript sSpNpcBookerTalkScripts[4] = {
    {0, 0},
    {&SpNpcBookerTalk::runScript01, 0},
    {&SpNpcBookerTalk::runScript02, 0},
    {&SpNpcBookerTalk::runScript03, 0},
};
extern "C" SpNpcBookerActEntry sSpNpcBookerActTable[7] = {
    {&SpNpcBooker::setupAct00, &SpNpcBooker::mainAct00},
    {&SpNpcBooker::setupAct01, &SpNpcBooker::mainAct01},
    {&SpNpcBooker::setupAct02, &SpNpcBooker::mainAct02},
    {&SpNpcBooker::setupAct03, &SpNpcBooker::mainAct03},
    {&SpNpcBooker::setupAct04, &SpNpcBooker::mainAct04},
    {&SpNpcBooker::setupAct05, &SpNpcBooker::mainAct05},
    {&SpNpcBooker::setupAct06, &SpNpcBooker::mainAct06},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221d748) {
    HOST_OVERLAY_VAR(data_ov004_0224d1e0),
    HOST_OVERLAY_VAR(data_ov004_0224d1f4),
    HOST_OVERLAY_VAR(data_ov004_0224d224),
    HOST_OVERLAY_VAR(sSpNpcBookerMsgFiles),
    HOST_OVERLAY_VAR(sSpNpcBookerModelPath),
    HOST_OVERLAY_VAR(sSpNpcBookerTexturePath),
    HOST_OVERLAY_VAR(sSpNpcBookerProfile),
    HOST_OVERLAY_VAR(sSpNpcBookerTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcBookerActTable),
    HOST_OVERLAY_VARS_END
};

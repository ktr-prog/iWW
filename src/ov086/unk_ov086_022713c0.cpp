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
#include "talk/MsgString33.h"
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
#include "sys/ClockDateTime.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_02065330.h"
#include "proto/ov086/unk_ov086_022713c0.h"

#pragma opt_loop_invariants off


class ActorTalkRequest;
class SpNpcTortimerCountdown;
class SpNpcTortimerCountdownTalk;
struct TalkStartMsg;


extern "C" {
void TalkRequest_SetTargetDone(void *p);
void Clock_GetDateTime(ClockDateTime *p);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
}






class SpNpcTortimerCountdownTalk : public SpNpcTalkRequest {
public:
    SpNpcTortimerCountdownTalk();
    virtual ~SpNpcTortimerCountdownTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(SpNpcTortimerCountdown *owner);

    SpNpcTortimerCountdown *ownerNpc;
    s32 massageChairSlot;
};








class SpNpcTortimerCountdown : public SpNpcActor {
public:
    SpNpcTortimerCountdown() {}
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
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    s32 act;
    SpNpcTortimerCountdownTalk talk;
};

struct SpNpcTortimerCountdownActEntry {
    BOOL (SpNpcTortimerCountdown::*enter)();
    BOOL (SpNpcTortimerCountdown::*exit)();
};

struct Unk_ov086_022714e4_Ent {
    const char *a;
    s32 b;
};


extern "C" {
u16 Item_MakePaper(u32 a, s32 b);
void Clock_GetDate(u8 *out);
s32 Clock_GetTimeOfDay();
extern const Unk_ov086_022714e4_Ent sSpNpcTortimerCountdownFortuneLines[4];
}

extern "C" char sSpNpcTortimerCountdownFortuneStrKey[];
extern "C" char sSpNpcTortimerCountdownFortuneStr2Key[];
extern "C" u32 data_ov086_02271c24 = 0x1d;
extern "C" u32 data_ov086_02271c20 = 0xe;
extern "C" char sSpNpcTortimerCountdownFortuneStrKey[] = "st_fortune";
extern "C" const Unk_ov086_022714e4_Ent sSpNpcTortimerCountdownFortuneLines[4] = {
    {sSpNpcTortimerCountdownFortuneStrKey, 0}, {sSpNpcTortimerCountdownFortuneStr2Key, 1}, {sSpNpcTortimerCountdownFortuneStr2Key, 2}, {sSpNpcTortimerCountdownFortuneStr2Key, 3},
};
SpNpcTortimerCountdownActEntry sSpNpcTortimerCountdownActTable[3] = {
    {&SpNpcTortimerCountdown::setupAct00, &SpNpcTortimerCountdown::mainAct00},
    {&SpNpcTortimerCountdown::setupAct01, &SpNpcTortimerCountdown::mainAct01},
    {NULL, &SpNpcTortimerCountdown::mainAct02},
};
extern "C" char sSpNpcTortimerCountdownFortuneStr2Key[] = "st_fortune2";
extern "C" u8 sSpNpcTortimerCountdownModelPath[] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','t','t','l','.','n','s','b','m','d',0};
extern "C" ActorProfile sSpNpcTortimerCountdownProfile = {(void *(*)())SpNpcTortimerCountdown_Create, 0x5c, 0x63, 2, 0x5000, 0x5000, 0x3e800};
extern "C" u8 sSpNpcTortimerCountdownTexturePath[] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','t','t','l','_','t','e','x','.','n','s','b','t','x',0};

struct TortimerCountdownDateLocals {
    u8 day, month, year, zero;
    u8 pad[2];
};

extern "C" SpNpcTortimerCountdown *SpNpcTortimerCountdown_Create() {
    return new SpNpcTortimerCountdown();
}

BOOL SpNpcTortimerCountdown::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcTortimerCountdown::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    return TRUE;
}

u8 *SpNpcTortimerCountdown::getTexturePath() { return sSpNpcTortimerCountdownTexturePath; }

u8 *SpNpcTortimerCountdown::getModelPath() { return sSpNpcTortimerCountdownModelPath; }

BOOL SpNpcTortimerCountdown::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcTortimerCountdownActTable[act].exit != NULL) {
        result = (this->*sSpNpcTortimerCountdownActTable[act].exit)();
    }
    return result;
}

void SpNpcTortimerCountdown::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimerCountdownActTable[state].enter != NULL) {
        ok = (this->*sSpNpcTortimerCountdownActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimerCountdown::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimerCountdown::mainAct00() { return TRUE; }

BOOL SpNpcTortimerCountdown::setupAct01() {
    Character *p = talk.getTalkPlayer();
    s32 x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcTortimerCountdown::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcTortimerCountdown::mainAct02() { return TRUE; }

SpNpcTortimerCountdownTalk::SpNpcTortimerCountdownTalk() {}

SpNpcTortimerCountdownTalk::~SpNpcTortimerCountdownTalk() {}

void SpNpcTortimerCountdownTalk::attachOwner(SpNpcTortimerCountdown *owner) {
    resetMsg();
    ownerNpc = owner;
    massageChairSlot = -1;
}

void SpNpcTortimerCountdownTalk::start(TalkStartMsg *out) {
    u16 h;
    TortimerCountdownDateLocals a;
    ClockDateTimeWords t;
    BOOL f;
    PlayerData_GetCurrent()->getErrands();
    out->msgKey = "sp_npc_turtle6";
    if (massageChairSlot == -1) {
        h = 0x37e0;
        massageChairSlot = Pocket_FindItem(&h);
        if (massageChairSlot >= 0) {
            out->msgKey = "sp_npc_turtle";
            out->msgIndex = 0;
            return;
        }
    }
    Clock_GetDate(&a.day);
    t.words[0] = 0;
    t.words[1] = 0;
    Clock_GetDateTime(&t.dt);
    f = FALSE;
    if (a.month == 0xc) {
        if (Clock_GetTimeOfDay() == 0) {
            out->msgIndex = Random_GlobalBelow(3);
        } else if (Clock_GetTimeOfDay() == 1) {
            out->msgIndex = Random_GlobalBelow(3);
            if (out->msgIndex != 0) {
                out->msgIndex += 2;
            }
        } else if (t.dt.hour < 0x17) {
            out->msgIndex = Random_GlobalBelow(3);
            if (out->msgIndex != 0) {
                out->msgIndex += 4;
            }
        } else if (t.dt.hour == 0x17 && t.dt.minute < 0x1e) {
            out->msgIndex = Random_GlobalBelow(3);
            if (out->msgIndex != 0) {
                out->msgIndex += 6;
            }
        } else if (t.dt.hour == 0x17 && t.dt.minute < 0x37) {
            out->msgIndex = Random_GlobalBelow(3) + 9;
        } else if (t.dt.hour == 0x17 && t.dt.minute < 0x3b) {
            out->msgIndex = Random_GlobalBelow(2) + 0xc;
            f = TRUE;
        } else {
            out->msgIndex = Random_GlobalBelow(2) + 0xe;
            f = TRUE;
        }
    } else if (t.dt.hour < 6) {
        out->msgIndex = Random_GlobalBelow(3) + 0x10;
        f = TRUE;
    } else if (TownSessionState_TestFlag(TownSessionState_Get(), 4) != 0) {
        out->msgIndex = Random_GlobalBelow(3) + 0x16;
        f = TRUE;
    } else {
        out->msgIndex = 0x13;
        f = TRUE;
    }
    if (!f) {
        if (Pocket_FindEmpty() != -1) {
            if (Random_GlobalBelow(2) == 0) {
                out->msgIndex = Random_GlobalBelow(3) + 0x19;
            }
        }
    }
}

void SpNpcTortimerCountdownTalk::onMessageEnd(u32) {
    struct {
        u8 bb[6];
        u16 h1, h2, h3, h4, h5, h6;
    } l;
    const Unk_ov086_022714e4_Ent *e;
    u8 *s6 = (u8 *)"sp_npc_turtle6";
    u8 msg = 0xff;
    Letter *p;
    PlayerData *g;
    u32 v, base;
    s32 i;
    if (massageChairSlot >= 0) {
        if (msgIndex == 1 || msgIndex == 4) {
            massageChairSlot = -2;
        }
        if (msgIndex == 2) {
            l.h1 = 0x1559;
            requestGiveItem(&l.h1, 0, 5, 0);
            l.h2 = 0x1559;
            Pocket_AddItem(&l.h2, 0);
            l.bb[1] = 4;
            window->setNextMessage(&l.bb[1], (u8 *)"sp_npc_turtle");
        }
    } else {
        s32 r = Inventory_FindEmptyLetter();
        switch (msgIndex) {
        case 0x13:
            msg = 0x14;
            if (r != -1) {
                p = Inventory_GetEmptyLetter();
                if (p != NULL) {
                    g = PlayerData_GetCurrent();
                    l.bb[0] = 2;
                    MsgString33 obj;
                    v = Random_GlobalBelow(4);
                    i = 0;
                    base = v << 2;
                    do {
                        l.bb[0] = v;
                        e = &sSpNpcTortimerCountdownFortuneLines[i];
                        String_Load(&obj, &l.bb[0], sSpNpcTortimerCountdownFortuneLines[i].a);
                        MailText_SetSlot(e->b, &obj);
                        v = base + Random_GlobalBelow(4);
                        v = v + (i << 4);
                        i++;
                    } while (i < 4);
                    l.bb[0] = 0;
                    Letter_ComposeFromMail((LetterView *)p, &l.bb[0], "ev_fortune", &data_ov086_02271c20, &data_ov086_02271c24, g->getPlayerId());
                    if (g != NULL) {
                        l.h3 = Item_MakePaper(0x1d, 4);
                        Catalog_AddItem(g->getCatalog(), &l.h3, 0);
                    }
                    TownSessionState_SetFlag(TownSessionState_Get(), 4);
                    l.h4 = 0x1565;
                    requestGiveItem(&l.h4, 0, 5, 0);
                    msg = 0x15;
                }
            }
            break;
        case 0x19:
        case 0x1a:
        case 0x1b:
            l.h5 = 0x137d;
            requestGiveItem(&l.h5, 0, 5, 0);
            l.h6 = 0x137d;
            Pocket_AddItem(&l.h6, 0);
            msg = 0x1c + Random_GlobalBelow(3);
            break;
        }
        if (msg != 0xff) {
            l.bb[4] = msg;
            window->setNextMessage(&l.bb[4], s6);
        }
    }
}

void SpNpcTortimerCountdownTalk::onChoice(u32) {
    u8 b;
    u16 h;
    u8 *s;
    s32 t = getChoiceList()->getResult();
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
            b = msg;
            window->setNextMessage(&b, s);
        }
    }
}

BOOL SpNpcTortimerCountdown::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcTortimerCountdown::onInteractionEvent(u32 v, u8) {
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

HOST_OVERLAY_VARS(unk_ov086_022713c0) {
    HOST_OVERLAY_VAR(data_ov086_02271c24),
    HOST_OVERLAY_VAR(data_ov086_02271c20),
    HOST_OVERLAY_VAR(sSpNpcTortimerCountdownFortuneStrKey),
    HOST_OVERLAY_VAR(sSpNpcTortimerCountdownActTable),
    HOST_OVERLAY_VAR(sSpNpcTortimerCountdownFortuneStr2Key),
    HOST_OVERLAY_VAR(sSpNpcTortimerCountdownModelPath),
    HOST_OVERLAY_VAR(sSpNpcTortimerCountdownProfile),
    HOST_OVERLAY_VAR(sSpNpcTortimerCountdownTexturePath),
    HOST_OVERLAY_VARS_END
};

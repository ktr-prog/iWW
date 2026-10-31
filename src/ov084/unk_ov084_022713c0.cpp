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
#include "player/PlayerId.h"
#include "player/PlayerSpNpcRecord.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov084/unk_ov084_022713c0.h"

#pragma opt_loop_invariants off


class ActorTalkRequest;
class SpNpcTortimerFireworks;
class SpNpcTortimerFireworksTalk;
struct TalkStartMsg;


extern "C" {
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
void TalkRequest_SetTargetDone(void *p);
void Clock_GetDateTime(ClockDateTime *p);
s32 Event_GetDaysSinceStart(u32 id);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
}






class SpNpcTortimerFireworksTalk : public SpNpcTalkRequest {
public:
    SpNpcTortimerFireworksTalk();
    virtual ~SpNpcTortimerFireworksTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(SpNpcTortimerFireworks *owner);

    SpNpcTortimerFireworks *ownerNpc;
    s32 massageChairSlot;
    u16 giftItem;
    u8 pad_b6[2];
};








class SpNpcTortimerFireworks : public SpNpcActor {
public:
    SpNpcTortimerFireworks() {}
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

    u8 pad_652[2];
    s32 act;
    SpNpcTortimerFireworksTalk talk;
    u8 showWeek;
};

struct SpNpcTortimerFireworksActEntry {
    BOOL (SpNpcTortimerFireworks::*enter)();
    BOOL (SpNpcTortimerFireworks::*exit)();
};

struct SpNpcTortimerFireworksFortuneLine {
    const char *a;
    s32 b;
};


extern "C" {
u16 Item_MakePaper(u32 a, s32 b);
s32 Date_GetNthWeekdayDay(u32 a, u32 b, s32 c, s32 d);
void Clock_GetDate(u8 *out);
#define gContestRecord HOST_LABEL(u8 (*)[], gContestRecord)
extern const SpNpcTortimerFireworksFortuneLine sSpNpcTortimerFireworksFortuneLines[4];
}

extern "C" char sSpNpcTortimerFireworksFortuneStrKey[];
extern "C" char sSpNpcTortimerFireworksFortuneStr2Key[];
extern "C" u32 data_ov084_02271d44 = 0xe;
extern "C" u8 sSpNpcTortimerFireworksTexturePath[] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','t','t','l','_','t','e','x','.','n','s','b','t','x',0};
extern "C" ActorProfile sSpNpcTortimerFireworksProfile = {(void *(*)())SpNpcTortimerFireworks_Create, 0x5a, 0x61, 2, 0x5000, 0x5000, 0x3e800};
extern "C" char sSpNpcTortimerFireworksFortuneStrKey[] = "st_fortune";
extern "C" const SpNpcTortimerFireworksFortuneLine sSpNpcTortimerFireworksFortuneLines[4] = {
    {sSpNpcTortimerFireworksFortuneStrKey, 0}, {sSpNpcTortimerFireworksFortuneStr2Key, 1}, {sSpNpcTortimerFireworksFortuneStr2Key, 2}, {sSpNpcTortimerFireworksFortuneStr2Key, 3},
};
SpNpcTortimerFireworksActEntry sSpNpcTortimerFireworksActTable[3] = {
    {&SpNpcTortimerFireworks::setupAct00, &SpNpcTortimerFireworks::mainAct00},
    {&SpNpcTortimerFireworks::setupAct01, &SpNpcTortimerFireworks::mainAct01},
    {NULL, &SpNpcTortimerFireworks::mainAct02},
};
extern "C" u8 sSpNpcTortimerFireworksModelPath[] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','t','t','l','.','n','s','b','m','d',0};
extern "C" char sSpNpcTortimerFireworksFortuneStr2Key[] = "st_fortune2";
extern "C" u32 data_ov084_02271d40 = 0x1d;

static inline BOOL Unk_ov084_022717ac_Rng(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 a = *p;
    u32 b = *p;
    if (b >= lo && a <= hi) {
        r = TRUE;
    }
    return r;
}

extern "C" SpNpcTortimerFireworks *SpNpcTortimerFireworks_Create() {
    return new SpNpcTortimerFireworks();
}

BOOL SpNpcTortimerFireworks::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcTortimerFireworks::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    ContestRecord_BeginContestDay((ContestRecord *)gContestRecord, 0);
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    u8 buf[8];
    Clock_GetDate(buf);
    s32 n = buf[0] - 1;
    u8 *q = &showWeek;
    *q = n / 7;
    *q = *q + 1;
    return TRUE;
}

u8 *SpNpcTortimerFireworks::getTexturePath() { return sSpNpcTortimerFireworksTexturePath; }

u8 *SpNpcTortimerFireworks::getModelPath() { return sSpNpcTortimerFireworksModelPath; }

BOOL SpNpcTortimerFireworks::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcTortimerFireworksActTable[act].exit != NULL) {
        result = (this->*sSpNpcTortimerFireworksActTable[act].exit)();
    }
    return result;
}

void SpNpcTortimerFireworks::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimerFireworksActTable[state].enter != NULL) {
        ok = (this->*sSpNpcTortimerFireworksActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimerFireworks::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimerFireworks::mainAct00() { return TRUE; }

BOOL SpNpcTortimerFireworks::setupAct01() {
    Character *p = talk.getTalkPlayer();
    s32 x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcTortimerFireworks::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcTortimerFireworks::mainAct02() { return TRUE; }

SpNpcTortimerFireworksTalk::SpNpcTortimerFireworksTalk() {
    giftItem = 0xfff1;
}

SpNpcTortimerFireworksTalk::~SpNpcTortimerFireworksTalk() {}

void SpNpcTortimerFireworksTalk::attachOwner(SpNpcTortimerFireworks *owner) {
    resetMsg();
    ownerNpc = owner;
    massageChairSlot = -1;
}

void SpNpcTortimerFireworksTalk::start(TalkStartMsg *out) {
    u16 h[4];
    ClockDateTimeWords loc;
    PlayerData_GetCurrent()->getErrands();
    out->msgKey = "sp_npc_turtle4";
    if (massageChairSlot == -1) {
        h[1] = 0x37e0;
        massageChairSlot = Pocket_FindItem(&h[1]);
        if (massageChairSlot >= 0) {
            out->msgKey = "sp_npc_turtle";
            out->msgIndex = 0;
            return;
        }
    }
    if (Talk_CheckAndSetPlayerFlag(0x1e, 1)) {
        PlayerActor_GetSlotHeldItem(&h[0], Net_GetJoiningAid());
        h[2] = 0x137e;
        s32 t1 = Pocket_FindItem(&h[2]);
        BOOL f1 = FALSE;
        if (t1 == -1) f1 = TRUE;
        if (!f1) {
            h[3] = 0x137f;
            s32 t2 = Pocket_FindItem(&h[3]);
            BOOL f2 = FALSE;
            if (t2 == -1) f2 = TRUE;
            if (!f2) goto skip;
        }
        if (!Unk_ov084_022717ac_Rng(&h[0], 0x137e, 0x137f)) {
            out->msgIndex = 6;
            return;
        }
    skip:
        if (TownSessionState_TestFlag(TownSessionState_Get(), 3) == 0) {
            out->msgIndex = 7;
        } else {
            out->msgIndex = Random_GlobalBelow(4) + 0xd;
        }
    } else {
        if (TownSessionState_TestFlag(TownSessionState_Get(), 2) == 0) {
            TownSessionState_SetFlag(TownSessionState_Get(), 2);
            if (ownerNpc->showWeek == 1) {
                out->msgIndex = 0;
            } else {
                loc.words[0] = 0;
                loc.words[1] = 0;
                Clock_GetDateTime(&loc.dt);
                s32 r = Date_GetNthWeekdayDay(loc.dt.year, loc.dt.month, 6, 5);
                if (r == -1) {
                    if (ownerNpc->showWeek <= 3) {
                        out->msgIndex = 1;
                    } else {
                        out->msgIndex = 2;
                    }
                } else {
                    if (ownerNpc->showWeek <= 4) {
                        out->msgIndex = 1;
                    } else {
                        out->msgIndex = 2;
                    }
                }
            }
        }
    }
}

void SpNpcTortimerFireworksTalk::onMessageEnd(u32) {
    u8 b;
    u8 b2;
    u16 h[7];
    u8 *s = (u8 *)"sp_npc_turtle4";
    u8 msg = 0xff;
    if (massageChairSlot >= 0) {
        if (msgIndex == 1 || msgIndex == 4) {
            massageChairSlot = -2;
        }
        if (msgIndex == 2) {
            h[1] = 0x1559;
            requestGiveItem(&h[1], 0, 5, 0);
            h[2] = 0x1559;
            Pocket_AddItem(&h[2], 0);
            b = 4;
            window->setNextMessage(&b, (u8 *)"sp_npc_turtle");
        }
    } else {
        switch (msgIndex) {
        case 0:
        case 1:
        case 2:
        case 6: {
            s32 r5 = Pocket_FindEmpty();
            h[0] = 0xfff1;
            h[3] = 0x137e;
            s32 t1 = Pocket_FindItem(&h[3]);
            BOOL f1 = FALSE;
            if (t1 == -1) f1 = TRUE;
            if (f1) {
                h[4] = 0x137f;
                s32 t2 = Pocket_FindItem(&h[4]);
                BOOL f2 = FALSE;
                if (t2 == -1) f2 = TRUE;
                if (f2) {
                    h[0] = 0x137e;
                    if (Random_GlobalBelow(2) == 0) {
                        h[0] = 0x137f;
                    }
                    goto after;
                }
            }
            h[5] = 0x137e;
            {
                s32 t3 = Pocket_FindItem(&h[5]);
                BOOL f3 = FALSE;
                if (t3 == -1) f3 = TRUE;
                if (f3) {
                    h[0] = 0x137e;
                } else {
                    h[0] = 0x137f;
                }
            }
        after:
            if (r5 >= 0) {
                PlayerSpNpcRecord *g2 = (PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord();
                if (g2->getFireworksGiven() < 10) {
                    g2->addFireworksGiven();
                    s32 r = ((PlayerId *)(PlayerData_GetCurrent()->getPlayerId()))->getGender();
                    requestGiveItem(&h[0], 0, 5, 0);
                    Pocket_AddItem(&h[0], 0);
                    setItemNameSlot(&h[0], 0, 7);
                    if (r == 0) {
                        msg = 3;
                    } else {
                        msg = 4;
                    }
                } else {
                    msg = 0xb;
                }
            } else {
                setItemNameSlot(&h[0], 0, 7);
                msg = 5;
            }
            break;
        }
        case 9:
            h[6] = 0x1565;
            requestGiveItem(&h[6], 0, 5, 0);
            msg = 0xa;
            break;
        }
        if (msg != 0xff) {
            b2 = msg;
            window->setNextMessage(&b2, s);
        }
    }
}

void SpNpcTortimerFireworksTalk::onChoice(u32) {
    u8 *t4 = (u8 *)"sp_npc_turtle4";
    s32 t = getChoiceList()->getResult();
    u8 buf[6];
    u16 h[2];
    u8 msg = 0xff;
    if (massageChairSlot >= 0) {
        u8 *s = (u8 *)"sp_npc_turtle";
        switch (msgIndex) {
        case 0:
            if (t == 0) {
                if (massageChairSlot >= 0) {
                    Pocket_RemoveItem(massageChairSlot);
                    h[0] = 0x37e0;
                    requestTakeItem(&h[0], 0, 5, 0);
                }
                msg = 2;
            }
            break;
        }
        if (msg != 0xff) {
            buf[1] = msg;
            window->setNextMessage(&buf[1], s);
        }
    } else {
        if (msgIndex == 7 && t == 0) {
            msg = 0xc;
            if (Inventory_FindEmptyLetter() != -1) {
                Letter *obj = Inventory_GetEmptyLetter();
                if (obj != NULL) {
                    msg = 9;
                    PlayerData *g = PlayerData_GetCurrent();
                    buf[0] = 2;
                    MsgString33 o;
                    u32 base = Random_GlobalBelow(4) + 8;
                    s32 i = 0;
                    u32 v = base;
                loop0:
                    buf[0] = v;
                    String_Load(&o, &buf[0], sSpNpcTortimerFireworksFortuneLines[i].a);
                    MailText_SetSlot(sSpNpcTortimerFireworksFortuneLines[i].b, &o);
                    v = (base - 8) * 4;
                    v = v + Random_GlobalBelow(4);
                    v = v + i * 16;
                    i++;
                    if (i < 4) goto loop0;
                    buf[0] = 1;
                    Letter_ComposeFromMail((LetterView *)obj, &buf[0], "ev_fortune", &data_ov084_02271d44, &data_ov084_02271d40,
                                           g->getPlayerId());
                    if (g != NULL) {
                        h[1] = Item_MakePaper(0x1d, 4);
                        Catalog_AddItem(g->getCatalog(), &h[1], 0);
                    }
                    TownSessionState_SetFlag(TownSessionState_Get(), 3);
                }
            }
        }
        if (msg != 0xff) {
            buf[4] = msg;
            window->setNextMessage(&buf[4], t4);
        }
    }
}

BOOL SpNpcTortimerFireworks::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcTortimerFireworks::onInteractionEvent(u32 v, u8) {
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

HOST_OVERLAY_VARS(unk_ov084_022713c0) {
    HOST_OVERLAY_VAR(data_ov084_02271d44),
    HOST_OVERLAY_VAR(sSpNpcTortimerFireworksTexturePath),
    HOST_OVERLAY_VAR(sSpNpcTortimerFireworksProfile),
    HOST_OVERLAY_VAR(sSpNpcTortimerFireworksFortuneStrKey),
    HOST_OVERLAY_VAR(sSpNpcTortimerFireworksActTable),
    HOST_OVERLAY_VAR(sSpNpcTortimerFireworksModelPath),
    HOST_OVERLAY_VAR(sSpNpcTortimerFireworksFortuneStr2Key),
    HOST_OVERLAY_VAR(data_ov084_02271d40),
    HOST_OVERLAY_VARS_END
};

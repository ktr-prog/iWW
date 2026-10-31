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
#include "player/PlayerSpNpcRecord.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_02065330.h"
#include "proto/ov087/unk_ov087_022713c0.h"

#pragma opt_loop_invariants off


class ActorTalkRequest;
class SpNpcCornimer;
class SpNpcCornimerTalk;
struct TalkStartMsg;


extern "C" {
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
void TalkRequest_SetTargetDone(void *p);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
#define gContestRecord HOST_LABEL(u8 (*)[], gContestRecord)
}






class SpNpcCornimerTalk : public SpNpcTalkRequest {
public:
    SpNpcCornimerTalk();
    virtual ~SpNpcCornimerTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);

    void attachOwner(SpNpcCornimer *owner);

    SpNpcCornimer *ownerNpc;
};








class SpNpcCornimer : public SpNpcActor {
public:
    SpNpcCornimer() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct00();
    BOOL setupAct00();
    BOOL setupAct01();
    BOOL mainAct01();
    BOOL mainAct02();
    void changeAct(s32 state);

    s32 act;
    SpNpcCornimerTalk talk;
};

struct SpNpcCornimerActEntry {
    BOOL (SpNpcCornimer::*enter)();
    BOOL (SpNpcCornimer::*exit)();
};

struct Unk_ov087_02271cc4_Ent {
    const char *a;
    s32 b;
};

struct SpNpcCornimerPrize {
    u16 item;
    u8 acornsNeeded;
    u8 pad;
};


extern "C" {
u16 Item_MakePaper(u32 a, s32 b);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
extern const SpNpcCornimerPrize sSpNpcCornimerPrizeTable[12];
extern const Unk_ov087_02271cc4_Ent sSpNpcCornimerFortuneLines[4];
}

extern "C" char sSpNpcCornimerFortuneStrKey[];
extern "C" char sSpNpcCornimerFortuneStr2Key[];
extern "C" u32 data_ov087_02271d84 = 0xe;
extern "C" u8 sSpNpcCornimerTexturePath[] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','d','n','k','_','t','e','x','.','n','s','b','t','x',0};
extern "C" ActorProfile sSpNpcCornimerProfile = {(void *(*)())SpNpcCornimer_Create, 0x5f, 0x66, 2, 0x5000, 0x5000, 0x3e800};
extern "C" char sSpNpcCornimerFortuneStrKey[] = "st_fortune";
extern "C" const Unk_ov087_02271cc4_Ent sSpNpcCornimerFortuneLines[4] = {
    {sSpNpcCornimerFortuneStrKey, 0}, {sSpNpcCornimerFortuneStr2Key, 1}, {sSpNpcCornimerFortuneStr2Key, 2}, {sSpNpcCornimerFortuneStr2Key, 3},
};
extern "C" const SpNpcCornimerPrize sSpNpcCornimerPrizeTable[12] = {
    {0x3218, 5, 0},   {0x3220, 10, 0},  {0x3224, 25, 0},  {0x3214, 40, 0},  {0x320c, 60, 0},  {0x3210, 80, 0},
    {0x3228, 100, 0}, {0x321c, 120, 0}, {0x322c, 140, 0}, {0x3208, 170, 0}, {0x110d, 200, 0}, {0x1151, 230, 0},
};
SpNpcCornimerActEntry sSpNpcCornimerActTable[3] = {
    {&SpNpcCornimer::setupAct00, &SpNpcCornimer::mainAct00},
    {&SpNpcCornimer::setupAct01, &SpNpcCornimer::mainAct01},
    {NULL, &SpNpcCornimer::mainAct02},
};
extern "C" u8 sSpNpcCornimerModelPath[] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','d','n','k','.','n','s','b','m','d',0};
extern "C" char sSpNpcCornimerFortuneStr2Key[] = "st_fortune2";
extern "C" u32 data_ov087_02271d80 = 0x1d;

static inline BOOL Unk_ov087_02271478_Rng(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 h = *p;
    u32 l = *p;
    if (l >= lo && h <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov087_02271478_Chk(u16 *c, u16 *slot, u16 val) {
    BOOL r;
    if (Item_IsFurniture(c)) {
        *slot = val;
        r = (Item_GetFurnitureIndex(c) == Item_GetFurnitureIndex(slot)) ? TRUE : FALSE;
    } else {
        if (*c == val) {
            r = TRUE;
        } else {
            r = FALSE;
        }
    }
    return r;
}

struct CornimerChoiceLocals {
    u8 a;
    u8 pad_01[2];
    u8 v;
    u16 s[4];
};

#pragma opt_loop_invariants off

static inline BOOL Unk_ov087_02271670_Z(BOOL x) {
    if (x == 0) {
        return TRUE;
    }
    return FALSE;
}

struct CornimerMsgEndLocals {
    u8 t;
    u8 pad_01;
    u16 v[6];
};

extern "C" SpNpcCornimer *SpNpcCornimer_Create() {
    return new SpNpcCornimer();
}

BOOL SpNpcCornimer::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcCornimer::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    ContestRecord_BeginFestival((ContestRecord *)gContestRecord, 2);
    return TRUE;
}

u8 *SpNpcCornimer::getTexturePath() { return sSpNpcCornimerTexturePath; }

u8 *SpNpcCornimer::getModelPath() { return sSpNpcCornimerModelPath; }

BOOL SpNpcCornimer::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcCornimerActTable[act].exit != NULL) {
        result = (this->*sSpNpcCornimerActTable[act].exit)();
    }
    return result;
}

void SpNpcCornimer::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcCornimerActTable[state].enter != NULL) {
        ok = (this->*sSpNpcCornimerActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcCornimer::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcCornimer::mainAct00() { return TRUE; }

BOOL SpNpcCornimer::setupAct01() {
    Character *p = talk.getTalkPlayer();
    u32 x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcCornimer::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcCornimer::mainAct02() { return TRUE; }

SpNpcCornimerTalk::SpNpcCornimerTalk() {}

SpNpcCornimerTalk::~SpNpcCornimerTalk() {}

void SpNpcCornimerTalk::attachOwner(SpNpcCornimer *owner) {
    resetMsg();
    ownerNpc = owner;
}

void SpNpcCornimerTalk::start(TalkStartMsg *out) {
    PlayerData *g = PlayerData_GetCurrent();
    g->getErrands();
    out->msgKey = "sp_npc_acorn";
    if (g->testFlag(0xf) == 0) {
        out->msgIndex = 0;
        g->setFlag(0xf);
        Talk_CheckAndSetPlayerFlag(0x19, 1);
    } else if (Talk_CheckAndSetPlayerFlag(0x19, 1) == 0) {
        out->msgIndex = 2;
    } else if (Random_GlobalBelow(2) == 0 || Talk_CheckAndSetPlayerFlag(0x1a, 0) != 0) {
        out->msgIndex = 3;
    } else {
        out->msgIndex = 0x10;
    }
}

extern "C" BOOL SpNpcCornimer_IsAcorn(u16 *p, s32 m) {
    BOOL r;
    if (m == 0) {
        r = FALSE;
        if (*p >= 0x1542 && *p <= 0x1546) {
            r = TRUE;
        }
        return r;
    }
    return FALSE;
}

void SpNpcCornimerTalk::onMessageEnd(u32) {
    CornimerMsgEndLocals buf;
    PlayerSpNpcRecord *g = (PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord();
    u32 k;
    buf.v[0] = 0xfff1;
    k = 0xff;
    switch (msgIndex) {
    case 2:
    case 3:
        if (MenuCtrl_BuildPocketMask(SpNpcCornimer_IsAcorn)) {
            s32 i = 0;
            u32 cnt = 0;
            while (i < 15) {
                buf.v[0] = Pocket_GetItem(i);
                if (Unk_ov087_02271478_Rng(&buf.v[0], 0x1542, 0x1546)) {
                    cnt++;
                }
                i++;
            }
            setNumberSlot(cnt, 2, 3, 0, 0);
            k = 5;
        } else if (g->getAcornPrizeStep() >= 12) {
            k = 0x17;
        } else {
            u32 a = g->getAcornPrizeStep();
            u32 b = g->getAcornsDelivered();
            s32 d = sSpNpcCornimerPrizeTable[a].acornsNeeded - b;
            if (d > 0) {
                setNumberSlot(d, 1, 3, 0, 0);
                k = 4;
            } else {
                k = 0x16;
            }
        }
        break;
    case 7:
    case 8:
    case 9:
        setNumberSlot(g->getAcornsDelivered(), 0, 3, 0, 0);
        if (g->getAcornPrizeStep() >= 12) {
            k = 0x16;
        } else {
            k = 0xa;
        }
        break;
    case 10: {
        u32 t = g->getAcornsDelivered();
        if (t >= sSpNpcCornimerPrizeTable[g->getAcornPrizeStep()].acornsNeeded) {
            buf.v[1] = sSpNpcCornimerPrizeTable[g->getAcornPrizeStep()].item;
            setItemNameSlot(&buf.v[1], 0, 7);
            k = 0xb;
        } else {
            u32 a = g->getAcornPrizeStep();
            u32 b = g->getAcornsDelivered();
            s32 d = sSpNpcCornimerPrizeTable[a].acornsNeeded;
            d -= b;
            setNumberSlot(d, 1, 3, 0, 0);
            k = 0xf;
        }
        break;
    }
    case 11:
    case 13:
        buf.v[2] = sSpNpcCornimerPrizeTable[g->getAcornPrizeStep()].item;
        if (Unk_ov087_02271670_Z(Pocket_AddItem(&buf.v[2], 0))) {
            k = 0xc;
        } else {
            g->advanceAcornPrizeStep();
            buf.v[3] = sSpNpcCornimerPrizeTable[g->getAcornPrizeStep()].item;
            requestGiveItem(&buf.v[3], 0, 5, 0);
            if (g->getAcornPrizeStep() < 12) {
                u32 b = g->getAcornsDelivered();
                if (b >= sSpNpcCornimerPrizeTable[g->getAcornPrizeStep()].acornsNeeded) {
                    buf.v[4] = sSpNpcCornimerPrizeTable[g->getAcornPrizeStep()].item;
                    setItemNameSlot(&buf.v[4], 0, 7);
                    k = 0xd;
                    break;
                }
            }
            k = 0xe;
        }
        break;
    case 20:
        buf.v[5] = 0x1565;
        requestGiveItem(&buf.v[5], 0, 5, 0);
        k = 0x15;
        break;
    }
    if (k != 0xff) {
        buf.t = k;
        window->setNextMessage(&buf.t, (u8 *)"sp_npc_acorn");
    }
}

void SpNpcCornimerTalk::onChoice(u32) {
    CornimerChoiceLocals buf;
    u8 *sa = (u8 *)"sp_npc_acorn";
    s32 t5 = getChoiceList()->getResult();
    PlayerData *g8 = PlayerData_GetCurrent();
    s32 k = 0xff;
    switch (msgIndex) {
    case 5:
        if (t5 == 0) {
            PlayerSpNpcRecord *g = (PlayerSpNpcRecord *)g8->getSpNpcRecord();
            s32 cntB;
            s32 cntA;
            buf.s[0] = 0xfff1;
            k = 0;
            cntB = 0;
            cntA = 0;
            for (; k < 15; k++) {
                buf.s[0] = Pocket_GetItem(k);
                if (Unk_ov087_02271478_Rng(&buf.s[0], 0x1542, 0x1546)) {
                    if (Unk_ov087_02271478_Chk(&buf.s[0], &buf.s[2], 0x1546)) {
                        cntA++;
                    } else {
                        cntB++;
                    }
                    Pocket_RemoveItem(k);
                }
            }
            buf.s[0] = 0x1542;
            if (cntA == 0) {
                k = (u8)(Random_GlobalBelow(3) + 7);
                cntA = 1;
                while (cntB > 0) {
                    g->addAcornsDelivered(cntA);
                    cntB--;
                }
            } else if (cntB != 0) {
                buf.s[0] = 0x1546;
                k = 0x18;
            } else {
                k = 0x19;
            }
            requestTakeItem(&buf.s[0], 0, 5, 0);
        }
        break;
    case 16:
        if (t5 == 0) {
            k = 0x12;
            if (Inventory_FindEmptyLetter() != -1) {
                Letter *obj = Inventory_GetEmptyLetter();
                if (obj != NULL) {
                    k = 0x13;
                    buf.a = 2;
                    MsgString33 o;
                    u32 n = Random_GlobalBelow(4) + 4;
                    s32 i = 0;
                    u32 r6 = n;
                    const Unk_ov087_02271cc4_Ent *ent;
                loop16:
                    buf.a = (u8)r6;
                    ent = &sSpNpcCornimerFortuneLines[i];
                    String_Load(&o, &buf.a, sSpNpcCornimerFortuneLines[i].a);
                    MailText_SetSlot(ent->b, &o);
                    r6 = (n - 4) * 4;
                    r6 += Random_GlobalBelow(4);
                    r6 += i * 16;
                    i++;
                    if (i < 4) goto loop16;
                    buf.a = 2;
                    Letter_ComposeFromMail((LetterView *)obj, &buf.a, "ev_fortune", &data_ov087_02271d84, &data_ov087_02271d80,
                                           g8->getPlayerId());
                    if (g8 != NULL) {
                        buf.s[1] = Item_MakePaper(0x1d, 4);
                        Catalog_AddItem(g8->getCatalog(), &buf.s[1], 0);
                    }
                    Talk_CheckAndSetPlayerFlag(0x1a, 1);
                }
            }
        }
        break;
    }
    if (k != 0xff) {
        buf.v = k;
        window->setNextMessage(&buf.v, sa);
    }
}

BOOL SpNpcCornimer::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcCornimer::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
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

HOST_OVERLAY_VARS(unk_ov087_022713c0) {
    HOST_OVERLAY_VAR(data_ov087_02271d84),
    HOST_OVERLAY_VAR(sSpNpcCornimerTexturePath),
    HOST_OVERLAY_VAR(sSpNpcCornimerProfile),
    HOST_OVERLAY_VAR(sSpNpcCornimerFortuneStrKey),
    HOST_OVERLAY_VAR(sSpNpcCornimerActTable),
    HOST_OVERLAY_VAR(sSpNpcCornimerModelPath),
    HOST_OVERLAY_VAR(sSpNpcCornimerFortuneStr2Key),
    HOST_OVERLAY_VAR(data_ov087_02271d80),
    HOST_OVERLAY_VARS_END
};

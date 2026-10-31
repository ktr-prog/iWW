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
#include "talk/MsgString9B.h"
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
#include "item/ItemPickSpec.h"
#include "npc/VillagerId.h"
#include "player/PlayerData.h"
#include "player/PlayerId.h"
#include "player/PlayerSpNpcRecord.h"
#include "save/ContestRecord.h"
#include "save/SaveData.h"
#include "save/VillagerData.h"
#include "sys/ClockDateTime.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_0204f134.h"
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov081/unk_ov081_022713c0.h"


class ActorTalkRequest;
class SpNpcTortimerFishingTourney;
class SpNpcTortimerFishingTourneyTalk;
struct FishSpawnTable;





struct SpNpcTortimerFishingTourneyEntryLocal {
    u16 entryFish;
    u16 contestItem;
    s32 x;
    s32 y;
    ClockDateTimeWords date;
    SpNpcTortimerFishingTourneyEntryLocal() {}
};

extern "C" {
s32 FishPick_PickAnyHour(u16 *a, s32 *b, s32 *c, s32 d, FishSpawnTable *e);
void TalkRequest_SetTargetDone(void *p);
void Clock_GetDateTime(ClockDateTime *p);
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
void *SaveVillagers_PickRandomExcept(u8 *base, void **arr, s32 n);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
#define gContestRecord HOST_LABEL(u8 (*)[], gContestRecord)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern SaveData gSaveData;
}






class SpNpcTortimerFishingTourneyTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcTortimerFishingTourneyTalk::*Fn)();

    SpNpcTortimerFishingTourneyTalk();
    virtual ~SpNpcTortimerFishingTourneyTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    s32 getRecordHolder();
    void attachOwner(SpNpcTortimerFishingTourney *owner);
    void scriptCloseItemSelect();
    void scriptCatchChosen();
    void setNextScript(s32 i);
    void setScript(s32 i);
    void pickScript(Fn *slot, s32 i);

    SpNpcTortimerFishingTourney *ownerNpc;
    Fn script;
    Fn nextScript;
    u16 entryItem;
    u8 beatOwnRecord;
    s32 massageChairSlot;
};








class SpNpcTortimerFishingTourney : public SpNpcActor {
public:
    SpNpcTortimerFishingTourney() {}
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
    SpNpcTortimerFishingTourneyTalk talk;
    s32 entrySize;
};

struct SpNpcTortimerFishingTourneyActEntry {
    BOOL (SpNpcTortimerFishingTourney::*enter)();
    BOOL (SpNpcTortimerFishingTourney::*exit)();
};

static inline BOOL Unk_ov081_InRange(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 h = *p;
    u32 l = *p;
    if (l >= lo && h <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov081_Neg(s32 v) {
    if (v < 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" {
}


extern "C" ActorProfile sSpNpcTortimerFishingTourneyProfile;

SpNpcTortimerFishingTourney *SpNpcTortimerFishingTourney_Create() {
    return new SpNpcTortimerFishingTourney();
}

BOOL SpNpcTortimerFishingTourney::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcTortimerFishingTourney::onCreate() {
    SpNpcTortimerFishingTourneyEntryLocal l;
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    ContestRecord *g = (ContestRecord *)gContestRecord;
    ContestRecord_BeginContestDay(g, 1);
    ContestRecord_GetItem(&l.contestItem, g);
    if (!Unk_ov081_InRange(&l.contestItem, 0x12e8, 0x131f)) {
        g->getHolderPlayer();
        s32 r6 = Random_GlobalBelow(2);
        l.x = 0;
        l.y = 0;
        l.date.words[0] = 0;
        l.date.words[1] = 0;
        l.entryFish = 0xfff1;
        Clock_GetDateTime(&l.date.dt);
        u32 month = l.date.dt.month;
        u32 day = l.date.dt.day;
        FishSpawnTable *t = (FishSpawnTable *)FishTable_GetForDate(month, FishTable_IsLateMonth(day));
        if (t != NULL) {
            if (FishPick_PickAnyHour(&l.entryFish, &l.x, &l.y, r6, t) == 0) {
                FishPick_PickAnyHour(&l.entryFish, &l.x, &l.y, (r6 + 1) & 1, t);
            }
        }
        ContestRecord_SetItem(g, &l.entryFish);
        entrySize = Contest_GetCatchSize(&l.entryFish);
        g->setSize(*(volatile s32 *)&entrySize);
        VillagerData *v = (VillagerData *)SaveVillagers_PickRandomExcept(gSaveVillagers, NULL, 0);
        if (v != NULL) {
            g->setHolderVillager(v->getVillagerId());
            g->setKind(1);
            gSaveData.setFlag(0xf);
        }
    }
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    return TRUE;
}

u8 *SpNpcTortimerFishingTourney::getTexturePath() { return sSpNpcTortimerFishingTourneyTexturePath; }

u8 *SpNpcTortimerFishingTourney::getModelPath() { return sSpNpcTortimerFishingTourneyModelPath; }

BOOL SpNpcTortimerFishingTourney::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcTortimerFishingTourneyActTable[act].exit != NULL) {
        result = (this->*sSpNpcTortimerFishingTourneyActTable[act].exit)();
    }
    return result;
}

void SpNpcTortimerFishingTourney::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimerFishingTourneyActTable[state].enter != NULL) {
        ok = (this->*sSpNpcTortimerFishingTourneyActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimerFishingTourney::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimerFishingTourney::mainAct00() { return TRUE; }

BOOL SpNpcTortimerFishingTourney::setupAct01() {
    Character *p = talk.getTalkPlayer();
    s32 x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, x, 0);
    return TRUE;
}

BOOL SpNpcTortimerFishingTourney::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcTortimerFishingTourney::mainAct02() { return TRUE; }

void SpNpcTortimerFishingTourneyTalk::onTaskDone(u32) {
    if (script) {
        (this->*script)();
        Fn t = NULL;
        script = t;
        if (nextScript) {
            script = nextScript;
            nextScript = t;
        }
    }
}

extern "C" ActorProfile sSpNpcTortimerFishingTourneyProfile = {(void *(*)())SpNpcTortimerFishingTourney_Create, 0x57, 0x5e, 2, 0x5000, 0x5000, 0x3e800};

void SpNpcTortimerFishingTourneyTalk::pickScript(Fn *slot, s32 i) {
    static Fn tbl[2] = {&SpNpcTortimerFishingTourneyTalk::scriptCatchChosen, &SpNpcTortimerFishingTourneyTalk::scriptCloseItemSelect};
    *slot = tbl[i];
}

extern "C" u8 sSpNpcTortimerFishingTourneyTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'l', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};

SpNpcTortimerFishingTourneyActEntry sSpNpcTortimerFishingTourneyActTable[3] = {
    {&SpNpcTortimerFishingTourney::setupAct00, &SpNpcTortimerFishingTourney::mainAct00},
    {&SpNpcTortimerFishingTourney::setupAct01, &SpNpcTortimerFishingTourney::mainAct01},
    {NULL, &SpNpcTortimerFishingTourney::mainAct02},
};

extern "C" u8 sSpNpcTortimerFishingTourneyModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'l', '.', 'n', 's', 'b', 'm', 'd', 0};



void SpNpcTortimerFishingTourneyTalk::setScript(s32 i) {
    pickScript(&script, i);
}

void SpNpcTortimerFishingTourneyTalk::setNextScript(s32 i) {
    pickScript(&nextScript, i);
}

extern "C" BOOL SpNpcTortimerFishingTourney_IsFish(u16 *p, s32 x) {
    if (x == 0) {
        BOOL r = FALSE;
        u32 v = *p;
        if (v >= 0x12e8 && v <= 0x131f) {
            r = TRUE;
        }
        return r;
    }
    return FALSE;
}

void SpNpcTortimerFishingTourneyTalk::scriptCatchChosen() {
    TalkWindowState *p = window;
    u8 m;
    entryItem = 0xfff1;
    ownerNpc->entrySize = 0;
    m = 0xc;
    if (MenuCtrl_IsResultOk() != 0) {
        s32 r4 = MenuCtrl_GetIndex();
        entryItem = Pocket_GetItem(r4);
        ownerNpc->entrySize = Contest_GetCatchSize(&entryItem);
        requestTakeItem(&entryItem, 0, 4, 0);
        setNextScript(1);
        setItemNameSlot(&entryItem, 2, 7);
        setFixedPointSlot(ownerNpc->entrySize, 4, 1);
        if (r4 >= 0) {
            Pocket_RemoveItem(r4);
        }
        m = 0xd;
    } else {
        requestReopenWindow();
    }
    p->setNextMessage(&m, (void *)"sp_npc_turtle1");
}

void SpNpcTortimerFishingTourneyTalk::scriptCloseItemSelect() {
    requestReopenWindow();
}

SpNpcTortimerFishingTourneyTalk::SpNpcTortimerFishingTourneyTalk() {
    entryItem = 0xfff1;
}

SpNpcTortimerFishingTourneyTalk::~SpNpcTortimerFishingTourneyTalk() {}

void SpNpcTortimerFishingTourneyTalk::attachOwner(SpNpcTortimerFishingTourney *owner) {
    resetMsg();
    ownerNpc = owner;
    beatOwnRecord = 0;
    massageChairSlot = -1;
}

void SpNpcTortimerFishingTourneyTalk::start(TalkStartMsg *out) {
    struct {
        u16 h[5];
        ClockDateTimeWords o;
    } l;
    PlayerData_GetCurrent()->getErrands();
    out->msgKey = "sp_npc_turtle1";
    l.o.words[0] = 0;
    l.o.words[1] = 0;
    Clock_GetDateTime(&l.o.dt);
    if (massageChairSlot == -1) {
        l.h[2] = 0x37e0;
        massageChairSlot = Pocket_FindItem(&l.h[2]);
        if (massageChairSlot >= 0) {
            out->msgKey = "sp_npc_turtle";
            out->msgIndex = 0;
            return;
        }
    }
    {
        u32 v = l.o.dt.hour;
        if (v < 0xc || v >= 0x12) {
            out->msgIndex = 2;
            return;
        }
    }
    l.h[0] = 0x1374;
    PlayerActor_GetSlotHeldItem(&l.h[1], PlayerActor_GetLocalSessionSlot());
    out->msgIndex = 3;
    if (Talk_CheckAndSetPlayerFlag(0x1b, 0) == 0) {
        l.h[3] = 0x1374;
        BOOL n1 = Pocket_FindItem(&l.h[3]) < 0 ? TRUE : FALSE;
        if (n1 != 0) {
            BOOL f1 = FALSE;
            volatile u16 *pv = l.h;
            u32 a = pv[1];
            u32 b = pv[1];
            if (b >= 0x1374 && a <= 0x1374) {
                f1 = TRUE;
            }
            if (f1 == 0) {
                l.h[4] = 0x1375;
                BOOL n2 = Pocket_FindItem(&l.h[4]) < 0 ? TRUE : FALSE;
                if (n2 != 0) {
                    BOOL f2 = FALSE;
                    volatile u16 *pw = l.h;
                    u32 c = pw[1];
                    u32 d = pw[1];
                    if (d >= 0x1375 && c <= 0x1375) {
                        f2 = TRUE;
                    }
                    if (f2 == 0) {
                        if (Pocket_FindEmpty() >= 0) {
                            out->msgIndex = 1;
                        } else {
                            out->msgIndex = 0;
                        }
                        return;
                    }
                }
            }
        }
    }
    if (Talk_CheckAndSetPlayerFlag(0x1b, 1) != 0) {
        out->msgIndex = 8;
    }
}

s32 SpNpcTortimerFishingTourneyTalk::getRecordHolder() {
    u16 h[2];
    ContestRecord *g = (ContestRecord *)gContestRecord;
    VillagerId *r4;
    PlayerId *r6;
    u16 *p5;
    u16 *p4;
    ContestRecord_GetItem(&h[0], g);
    {
        BOOL r = FALSE;
        volatile u16 *pv = &h[0];
        u32 a = *pv;
        u32 b = *pv;
        if (b >= 0x12e8 && a <= 0x131f) {
            r = TRUE;
        }
        if (r != 0) {
            r6 = (PlayerId *)g->getHolderPlayer();
            r4 = g->getHolderVillager();
            ContestRecord_GetItem(&h[1], g);
            setItemNameSlot(&h[1], 1, 7);
            setFixedPointSlot(g->getSize(), 0, 1);
            if (r6->isValid() != 0) {
                setPlayerNameSlot((PlayerId *)g->getHolderPlayer(), 1);
                p4 = (u16 *)PlayerData_GetCurrent()->getPlayerId();
                p5 = (u16 *)g->getHolderPlayer();
                if (p5[0] == p4[0] && memcmp(p5 + 1, p4 + 1, 8) == 0 && ((PlayerId *)(p5))->equals((PlayerId *)(p4)) != 0) {
                    goto ret0;
                }
                return 1;
            ret0:
                return 0;
            } else if (r4->isValid() != 0) {
                MsgString9B o;
                r4->getName(&o);
                window->setSlot(1, &o);
                return 2;
            }
        }
    }
    return -1;
}

void SpNpcTortimerFishingTourneyTalk::onMessageEnd(u32) {
    u8 m1;
    u8 m2;
    u16 h0, h1, h2, h3, h4, h5;
    ContestRecord *g;
    u8 *s;
    u8 msg;
    s = (u8 *)"sp_npc_turtle1";
    msg = 0xff;
    if (massageChairSlot >= 0) {
        if (msgIndex == 1 || msgIndex == 4) {
            massageChairSlot = -2;
        }
        if (msgIndex == 2) {
            h1 = 0x1559;
            requestGiveItem(&h1, 0, 5, 0);
            h2 = 0x1559;
            Pocket_AddItem(&h2, 0);
            m1 = 4;
            window->setNextMessage(&m1, (void *)"sp_npc_turtle");
        }
    } else {
        switch (msgIndex) {
        case 0xd:
        case 0x10:
        case 0x13:
            h0 = 0xfff1;
            g = (ContestRecord *)gContestRecord;
            switch (msgIndex) {
            case 0xd:
                requestKeepItem();
                ((PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord())->setEnteredFishingTourney(1);
                if (((ownerNpc->entrySize * 10) >> 12) > ((g->getSize() * 10) >> 12)) {
                    msg = 0x10;
                } else if (getRecordHolder() == 0) {
                    msg = 0x16;
                } else if (getRecordHolder() > 0) {
                    msg = 0xe;
                }
                break;
            case 0x10:
                if (getRecordHolder() == 0) {
                    msg = 0x11;
                    beatOwnRecord = 1;
                } else if (getRecordHolder() > 0) {
                    msg = 0x12;
                    beatOwnRecord = 0;
                }
                break;
            case 0x13:
                if (beatOwnRecord != 0) {
                    msg = 0x14;
                } else {
                    msg = 0x15;
                }
                ContestRecord_SetItem(g, &entryItem);
                g->setSize(ownerNpc->entrySize);
                g->setHolderPlayer((Unk_02085810_Base *)(PlayerData_GetCurrent()->getPlayerId()));
                g->setKind(1);
                gSaveData.setFlag(0xf);
                {
                    ItemPickSpec o;
                    o.set(0, 0);
                    ItemPick_One(&h3, &o, NULL, NULL, 1, 1, NULL);
                    h0 = h3;
                }
                requestGiveItem(&h0, 0, 5, 0);
                setItemNameSlot(&h0, 0, 7);
                Pocket_AddItem(&h0, 0);
                break;
            }
            break;
        }
        switch (msgIndex) {
        case 1:
            h4 = 0x1374;
            requestGiveItem(&h4, 0, 5, 0);
            h5 = 0x1374;
            Pocket_AddItem(&h5, 0);
            msg = 4;
            Talk_CheckAndSetPlayerFlag(0x1b, 1);
            break;
        case 0xb:
            setPocketFilter(SpNpcTortimerFishingTourney_IsFish, 0xd, 1);
            openSubScene(0);
            setScript(0);
            break;
        }
        if (msg != 0xff) {
            m2 = msg;
            window->setNextMessage(&m2, s);
        }
    }
}

void SpNpcTortimerFishingTourneyTalk::onChoice(u32) {
    u8 b1;
    u8 b2;
    u16 h;
    s32 t = getChoiceList()->getResult();
    u8 msg;
    u8 *s;
    s = (u8 *)"sp_npc_turtle1";
    msg = 0xff;
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
            b1 = msg;
            window->setNextMessage(&b1, s);
        }
    } else {
        if (msgIndex == 8) {
            if (t != 0) {
                if (getRecordHolder() == 0) {
                    msg = 9;
                } else if (getRecordHolder() > 0) {
                    msg = 0xa;
                }
            } else {
                msg = 0xb;
            }
        }
        if (msg != 0xff) {
            b2 = msg;
            window->setNextMessage(&b2, s);
        }
    }
}

BOOL SpNpcTortimerFishingTourney::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcTortimerFishingTourney::onInteractionEvent(u32 v, u8) {
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

HOST_OVERLAY_VARS(unk_ov081_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcTortimerFishingTourneyProfile),
    HOST_OVERLAY_VAR(sSpNpcTortimerFishingTourneyTexturePath),
    HOST_OVERLAY_VAR(sSpNpcTortimerFishingTourneyActTable),
    HOST_OVERLAY_VAR(sSpNpcTortimerFishingTourneyModelPath),
    HOST_OVERLAY_VARS_END
};

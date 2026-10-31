#include "uptr.h"
#include "host_labels.h"
#include "types.h"
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
#include "proto/main/unk_02060b9c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206269c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/ov082/unk_ov082_022713c0.h"


class ActorTalkRequest;
class SpNpcTortimerBugOff;
class SpNpcTortimerBugOffTalk;




struct Unk_0202c92c_Ent;

extern "C" {
void TalkRequest_SetTargetDone(void *p);
void Clock_GetDateTime(ClockDateTime *p);
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
s32 InsectPick_PickAnyHour(u16 *a, s32 *b, s32 *c, s32 d, Unk_0202c92c_Ent *tbl, s32 *arr, s32 cnt);
void *SaveVillagers_PickRandomExcept(u8 *base, void **arr, s32 n);
void ThreeLayerAnimModel_AssignJointsToLayer2(void *p, s32 a, s32 b);
extern u16 data_020c6cc8;
#define gContestRecord HOST_LABEL(u8 (*)[], gContestRecord)
extern SaveData gSaveData;
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
}






class SpNpcTortimerBugOffTalk : public SpNpcTalkRequest {
public:
    typedef void (SpNpcTortimerBugOffTalk::*Fn)();

    SpNpcTortimerBugOffTalk();
    virtual ~SpNpcTortimerBugOffTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void onTaskDone(u32 id);

    s32 getRecordHolder();
    void attachOwner(SpNpcTortimerBugOff *owner);
    void scriptCloseItemSelect();
    void scriptCatchChosen();
    void setNextScript(s32 i);
    void setScript(s32 i);
    void pickScript(Fn *slot, s32 i);

    SpNpcTortimerBugOff *ownerNpc;
    Fn script;
    Fn nextScript;
    u16 entryItem;
    u8 beatOwnRecord;
    s32 massageChairSlot;
};








class SpNpcTortimerBugOff : public SpNpcActor {
public:
    SpNpcTortimerBugOff() {}
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
    SpNpcTortimerBugOffTalk talk;
    s32 entrySize;
};

struct SpNpcTortimerBugOffActEntry {
    BOOL (SpNpcTortimerBugOff::*enter)();
    BOOL (SpNpcTortimerBugOff::*exit)();
};

static inline BOOL Unk_ov082_InRange(volatile u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    u32 h = *p;
    u32 l = *p;
    if (l >= lo && h <= hi) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov082_Neg(s32 v) {
    if (v < 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" {
}


SpNpcTortimerBugOff *SpNpcTortimerBugOff_Create() {
    return new SpNpcTortimerBugOff();
}

BOOL SpNpcTortimerBugOff::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcTortimerBugOff::onCreate() {
    struct {
        u16 w0;
        u16 s2;
        u16 s4;
        u16 s6;
        s32 x;
        s32 y;
        ClockDateTimeWords date;
    } l;
    ContestRecord *g;
    s32 rnd;
    Unk_0202c92c_Ent *tbl;
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    g = (ContestRecord *)gContestRecord;
    ContestRecord_BeginContestDay(g, 2);
    ContestRecord_GetItem(&l.s2, g);
    if (!Unk_ov082_InRange(&l.s2, 0x12b0, 0x12e7)) {
        g->getHolderPlayer();
        rnd = Random_GlobalBelow(2);
        l.x = 0;
        l.y = 0;
        l.date.words[0] = 0;
        l.date.words[1] = 0;
        l.w0 = 0xfff1;
        Clock_GetDateTime(&l.date.dt);
        tbl = (Unk_0202c92c_Ent *)Insect_GetSpawnTable(l.date.dt.month - 1);
        if (tbl != NULL) {
            if (InsectPick_PickAnyHour(&l.w0, &l.x, &l.y, rnd, tbl, NULL, 0) == 0) {
                InsectPick_PickAnyHour(&l.w0, &l.x, &l.y, rnd, tbl, NULL, 0);
            }
        }
        ContestRecord_SetItem(g, &l.w0);
        ContestRecord_GetItem(&l.s4, g);
        if (Unk_ov082_InRange(&l.s4, 0x12b0, 0x12e7)) {
            VillagerData *v = (VillagerData *)SaveVillagers_PickRandomExcept(gSaveVillagers, NULL, 0);
            if (v != NULL) {
                g->setHolderVillager(v->getVillagerId());
                g->setKind(2);
                gSaveData.setFlag(0xf);
            }
        }
        entrySize = Contest_GetCatchSize(&l.w0);
        g->setSize(entrySize);
    }
    animCtrl.playAnim((NpcActor *)(this), 0x140, 0, 0, 0x1000, 0, 1);
    ThreeLayerAnimModel_AssignJointsToLayer2(&model, 0xc, 0xe);
    collider.groups |= 2;
    return TRUE;
}

u8 *SpNpcTortimerBugOff::getTexturePath() { return sSpNpcTortimerBugOffTexturePath; }

u8 *SpNpcTortimerBugOff::getModelPath() { return sSpNpcTortimerBugOffModelPath; }

BOOL SpNpcTortimerBugOff::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcTortimerBugOffActTable[act].exit != NULL) {
        result = (this->*sSpNpcTortimerBugOffActTable[act].exit)();
    }
    return result;
}

void SpNpcTortimerBugOff::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimerBugOffActTable[state].enter != NULL) {
        ok = (this->*sSpNpcTortimerBugOffActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimerBugOff::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimerBugOff::mainAct00() { return TRUE; }

BOOL SpNpcTortimerBugOff::setupAct01() {
    Character *p = talk.getTalkPlayer();
    u32 r = 0;
    if (p != NULL) {
        r = getAngleTo((NpcActor *)(p));
    }
    talkCtrl.requestTurnAndTalk(0, r, 0);
    return TRUE;
}

BOOL SpNpcTortimerBugOff::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcTortimerBugOff::mainAct02() { return TRUE; }

void SpNpcTortimerBugOffTalk::onTaskDone(u32) {
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

extern "C" u8 sSpNpcTortimerBugOffTexturePath[];
extern "C" ActorProfile sSpNpcTortimerBugOffProfile;
extern "C" u8 sSpNpcTortimerBugOffModelPath[];

extern "C" ActorProfile sSpNpcTortimerBugOffProfile = {(void *(*)())SpNpcTortimerBugOff_Create, 0x58, 0x5f, 2, 0x5000, 0x5000, 0x3e800};

extern "C" u8 sSpNpcTortimerBugOffTexturePath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'l', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};


extern "C" u8 sSpNpcTortimerBugOffModelPath[] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'l', '.', 'n', 's', 'b', 'm', 'd', 0};

SpNpcTortimerBugOffActEntry sSpNpcTortimerBugOffActTable[3] = {
    {&SpNpcTortimerBugOff::setupAct00, &SpNpcTortimerBugOff::mainAct00},
    {&SpNpcTortimerBugOff::setupAct01, &SpNpcTortimerBugOff::mainAct01},
    {NULL, &SpNpcTortimerBugOff::mainAct02},
};

void SpNpcTortimerBugOffTalk::pickScript(Fn *slot, s32 i) {
    static Fn tbl[2] = {&SpNpcTortimerBugOffTalk::scriptCatchChosen, &SpNpcTortimerBugOffTalk::scriptCloseItemSelect};
    *slot = tbl[i];
}

void SpNpcTortimerBugOffTalk::setScript(s32 i) {
    pickScript(&script, i);
}

void SpNpcTortimerBugOffTalk::setNextScript(s32 i) {
    pickScript(&nextScript, i);
}

extern "C" BOOL SpNpcTortimerBugOff_IsInsect(u16 *p, s32 x) {
    if (x == 0) {
        BOOL r = FALSE;
        u32 v = *p;
        if (v >= 0x12b0 && v <= 0x12e7) {
            r = TRUE;
        }
        return r;
    }
    return FALSE;
}

void SpNpcTortimerBugOffTalk::scriptCatchChosen() {
    TalkWindowState *r6 = window;
    u8 b;
    entryItem = 0xfff1;
    ownerNpc->entrySize = 0;
    b = 0xc;
    if (MenuCtrl_IsResultOk()) {
        s32 r4 = MenuCtrl_GetIndex();
        entryItem = Pocket_GetItem(r4);
        ownerNpc->entrySize = Contest_GetCatchSize(&entryItem);
        requestTakeItem(&entryItem, 0, 4, 0);
        setNextScript(1);
        setItemNameSlot(&entryItem, 2, 7);
        setNumberSlot(ownerNpc->entrySize >> 12, 4, 3, 0, 0);
        if (r4 >= 0) {
            Pocket_RemoveItem(r4);
        }
        b = 0xd;
    } else {
        requestReopenWindow();
    }
    r6->setNextMessage(&b, (void *)"sp_npc_turtle2");
}

void SpNpcTortimerBugOffTalk::scriptCloseItemSelect() {
    requestReopenWindow();
}

SpNpcTortimerBugOffTalk::SpNpcTortimerBugOffTalk() {
    entryItem = 0xfff1;
}

SpNpcTortimerBugOffTalk::~SpNpcTortimerBugOffTalk() {}

void SpNpcTortimerBugOffTalk::attachOwner(SpNpcTortimerBugOff *owner) {
    resetMsg();
    ownerNpc = owner;
    beatOwnRecord = 0;
    massageChairSlot = -1;
}

void SpNpcTortimerBugOffTalk::start(TalkStartMsg *out) {
    u16 x[4];
    ClockDateTimeWords rec;
    PlayerData_GetCurrent()->getErrands();
    out->msgKey = "sp_npc_turtle2";
    rec.words[0] = 0;
    rec.words[1] = 0;
    Clock_GetDateTime(&rec.dt);
    if (massageChairSlot == -1) {
        x[1] = 0x37e0;
        massageChairSlot = Pocket_FindItem(&x[1]);
        if (massageChairSlot >= 0) {
            out->msgKey = "sp_npc_turtle";
            out->msgIndex = 0;
            return;
        }
    }
    u8 t = rec.dt.hour;
    if (!(t >= 0xc && t < 0x12)) {
        out->msgIndex = 2;
    } else {
        out->msgIndex = 3;
        PlayerActor_GetSlotHeldItem(&x[0], PlayerActor_GetLocalSessionSlot());
        if (!Talk_CheckAndSetPlayerFlag(0x1c, 0)) {
            x[2] = 0x1376;
            if (Unk_ov082_Neg(Pocket_FindItem(&x[2]))) {
                if (!Unk_ov082_InRange(&x[0], 0x1376, 0x1376)) {
                    x[3] = 0x1377;
                    if (Unk_ov082_Neg(Pocket_FindItem(&x[3]))) {
                        if (!Unk_ov082_InRange(&x[0], 0x1377, 0x1377)) {
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
        if (Talk_CheckAndSetPlayerFlag(0x1c, 1)) {
            out->msgIndex = 8;
        }
    }
}

s32 SpNpcTortimerBugOffTalk::getRecordHolder() {
    u16 v, w;
    ContestRecord *r7 = (ContestRecord *)gContestRecord;
    ContestRecord_GetItem(&v, r7);
    if (Unk_ov082_InRange(&v, 0x12b0, 0x12e7)) {
        PlayerId *r6 = (PlayerId *)r7->getHolderPlayer();
        VillagerId *r4 = r7->getHolderVillager();
        ContestRecord_GetItem(&w, r7);
        setItemNameSlot(&w, 1, 7);
        setNumberSlot(r7->getSize() >> 12, 0, 3, 0, 0);
        if (r6->isValid()) {
            setPlayerNameSlot((PlayerId *)r7->getHolderPlayer(), 1);
            u16 *q = (u16 *)PlayerData_GetCurrent()->getPlayerId();
            u16 *p = (u16 *)r7->getHolderPlayer();
            if (p[0] != q[0] || memcmp(p + 1, q + 1, 8) != 0 || ((PlayerId *)(p))->equals((PlayerId *)(q)) == 0) {
                return 1;
            }
            return 0;
        }
        if (r4->isValid()) {
            MsgString9B o;
            r4->getName(&o);
            window->setSlot(1, &o);
            return 2;
        }
    }
    return -1;
}

void SpNpcTortimerBugOffTalk::onMessageEnd(u32) {
    u8 b1, b2;
    u16 h0, ha, hb, x14, h16, hc, hd;
    ContestRecord *r6;
    u8 *r7 = (u8 *)"sp_npc_turtle2";
    u32 msg = 0xff;
    if (massageChairSlot >= 0) {
        if (msgIndex == 1 || msgIndex == 4) {
            massageChairSlot = -2;
        }
        if (msgIndex == 2) {
            ha = 0x1559;
            requestGiveItem(&ha, 0, 5, 0);
            hb = 0x1559;
            Pocket_AddItem(&hb, 0);
            b1 = 4;
            window->setNextMessage(&b1, (void *)"sp_npc_turtle");
        }
        return;
    }
    if (msgIndex == 0xd || msgIndex == 0x10 || msgIndex == 0x13 || msgIndex == 0x16) {
        h0 = 0xfff1;
        r6 = (ContestRecord *)gContestRecord;
        switch (msgIndex) {
        case 0xd:
            requestKeepItem();
            ContestRecord_GetItem(&x14, r6);
            if (!Unk_ov082_InRange(&x14, 0x12b0, 0x12e7)) {
                msg = 0x16;
                break;
            }
            ((PlayerSpNpcRecord *)PlayerData_GetCurrent()->getSpNpcRecord())->setEnteredBugOff(1);
            {
                s32 v = r6->getSize();
                if ((ownerNpc->entrySize >> 12) > (v >> 12)) {
                    msg = 0x10;
                    break;
                }
            }
            if (getRecordHolder() == 0) {
                msg = 0x1d;
            } else if (getRecordHolder() > 0) {
                msg = 0xe;
            }
            break;
        case 0xe:
        case 0xf:
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
        case 0x11:
        case 0x12:
        case 0x14:
        case 0x15:
            break;
        case 0x13:
        case 0x16:
            if (beatOwnRecord != 0) {
                msg = 0x14;
            } else {
                msg = 0x15;
            }
            ContestRecord_SetItem(r6, &entryItem);
            r6->setSize(ownerNpc->entrySize);
            r6->setHolderPlayer((Unk_02085810_Base *)(PlayerData_GetCurrent()->getPlayerId()));
            r6->setKind(2);
            gSaveData.setFlag(0xf);
            {
                ItemPickSpec o;
                o.set(0, 0);
                ItemPick_One(&h16, &o, NULL, NULL, 1, 1, NULL);
                h0 = h16;
            }
            requestGiveItem(&h0, 0, 5, 0);
            setItemNameSlot(&h0, 0, 7);
            Pocket_AddItem(&h0, 0);
            break;
        }
    }
    switch (msgIndex) {
    case 1:
        hc = 0x1376;
        requestGiveItem(&hc, 0, 5, 0);
        hd = 0x1376;
        Pocket_AddItem(&hd, 0);
        msg = 4;
        Talk_CheckAndSetPlayerFlag(0x1c, 1);
        break;
    case 0xb:
        setPocketFilter(SpNpcTortimerBugOff_IsInsect, 0xd, 1);
        openSubScene(0);
        setScript(0);
        break;
    }
    if (msg != 0xff) {
        b2 = msg;
        window->setNextMessage(&b2, r7);
    }
}

void SpNpcTortimerBugOffTalk::onChoice(u32) {
    u8 b1, b2;
    u16 h;
    s32 t = getChoiceList()->getResult();
    u8 *s = (u8 *)"sp_npc_turtle2";
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
            b1 = msg;
            window->setNextMessage(&b1, s);
        }
    } else {
        if (msgIndex == 8) {
            if (t != 0) {
                s32 r = getRecordHolder();
                if (r == 0) {
                    msg = 9;
                } else if (r > 0) {
                    msg = 0xa;
                } else {
                    msg = 0x1e;
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

BOOL SpNpcTortimerBugOff::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (talkCtrl.isBusy() == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcTortimerBugOff::onInteractionEvent(u32 v, u8) {
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

HOST_OVERLAY_VARS(unk_ov082_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcTortimerBugOffProfile),
    HOST_OVERLAY_VAR(sSpNpcTortimerBugOffTexturePath),
    HOST_OVERLAY_VAR(sSpNpcTortimerBugOffModelPath),
    HOST_OVERLAY_VAR(sSpNpcTortimerBugOffActTable),
    HOST_OVERLAY_VARS_END
};

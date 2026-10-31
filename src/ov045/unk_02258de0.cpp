#include "types.h"
#include "Unk_020d8c7c.h"
#include "talk/MsgStringBase.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "npc/NpcActionCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "talk/EncodedString.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/MsgString.h"
#include "actor/ActorProfile.h"
#include "net/CommManager.h"
#include "npc/VillagerId.h"
#include "player/PlayerData.h"
#include "talk/ChoiceList.h"
#include "save/SaveData.h"
#include "save/VillagerData.h"
#include "npc/VillagerState.h"
#include "sys/ClockDateTime.h"
#include "gfx/Mtx43.h"
#include "proto/main/unk_020119cc.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov004/unk_ov004_02228dcc.h"
#include "proto/ov045/unk_02258de0.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_0204cc1c.h"

class SpNpcKatrina;
class SpNpcKatrinaTalk;

extern "C" {
BOOL TalkRequest_SetTargetDone(Character *c);
BOOL TalkRequest_AddPlayerTalk6(Character *c, s32 b);
void Clock_GetDateTime(ClockDateTime *p);
BOOL EncodedString_SetRaw(EncodedString *buf, const void *src, s32 len);
BOOL Talk_CheckAndSetPlayerFlag(u32 a, BOOL flag);
void SaveVillagers_ApplyGoodFortune(void *villagers, void *playerId);
void SaveVillagers_ApplyBadFortune(void *villagers);
VillagerData *SaveVillagers_FindByName(u8 *villagers, u8 *name, s32 len, void *playerId);
s32 Villager_FindMemoryIndex(VillagerMemory *t, void *id);
VillagerMemory *Villager_GetMemory(VillagerMemory *t, u32 i);
VillagerState *Villager_GetState(VillagerData *a);
u32 VillagerState_GetMood(VillagerState *e);
void VillagerState_AddMoodTimer(VillagerState *e, s32 v);
void VillagerState_SetMoodTimer(VillagerState *e, u16 v);
void VillagerState_SetMood(VillagerState *e, u32 v);
BOOL Model_GetJointWorldMtx(void *model, Mtx43 *out, s32 joint);
u8 Math_CountDownU8(u8 *p);
extern u16 data_020c6cc8;
extern SaveData gSaveData;
extern CommManager *gCommManager;
}





class KatrinaMsgString17 : public MsgString {
public:
    KatrinaMsgString17();
    virtual ~KatrinaMsgString17();
    virtual u32 capacity();
    virtual u8 *data();

    u8 unk_12[0x24 - 0x12];
};

class KatrinaEncodedString16 : public EncodedString {
public:
    KatrinaEncodedString16();
    virtual ~KatrinaEncodedString16();
    virtual u32 capacity();
    virtual u8 *data();

    u8 unk_0e[0x24 - 0xe];
};


class SpNpcKatrinaTalk : public ActorTalkRequest {
public:
    SpNpcKatrinaTalk();
    virtual ~SpNpcKatrinaTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void onEventTag(u32 id);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void scriptReadPartnerName();
    void setScript(s32 v);
    void attachOwner(SpNpcKatrina *o);

    s32 script;
    SpNpcKatrina *owner;
};




class ActorTalkRequest;





struct KatrinaFortuneCard {
    u8 a;
    s32 b;
};

class SpNpcKatrina : public SpNpcActor {
public:
    SpNpcKatrina() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    s32 getFortuneKind();
    void drawFortuneCard();
    BOOL isClosingTime();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    s32 effectHandle;
    s32 act;
    Mtx43 jointMtx;
    SpNpcKatrinaTalk talk;
    u8 fortuneMsg;
    u8 traitMsg;
    u8 pad_742[2];
    s32 readingMode;
    u8 card;
    u8 pad_749[3];
    s32 inverted;
    u8 *partnerName;
    u8 effectTimer;
    u8 pad_755[3];
};

typedef void (SpNpcKatrinaTalk::*SpNpcKatrinaTalkScriptFn)();

struct SpNpcKatrinaTalkScript {
    SpNpcKatrinaTalkScriptFn fn;
    u8 flag;
    u8 pad[3];
};

struct SpNpcKatrinaActEntry {
    BOOL (SpNpcKatrina::*enter)();
    BOOL (SpNpcKatrina::*exit)();
};


extern "C" {
extern const KatrinaFortuneCard sSpNpcKatrinaGoodFortuneCards[17];
extern const KatrinaFortuneCard sSpNpcKatrinaBadFortuneCards[21];
}







extern "C" SpNpcKatrina *SpNpcKatrina_Create() { return new SpNpcKatrina; }

u8 sSpNpcKatrinaModelPath[23] = "npc_sp/model/bpt.nsbmd";
u8 sSpNpcKatrinaTexturePath[27] = "npc_sp/model/bpt_tex.nsbtx";
const KatrinaFortuneCard sSpNpcKatrinaGoodFortuneCards[17] = {
    {0x00, 0}, {0x01, 0}, {0x02, 0}, {0x03, 0}, {0x04, 0}, {0x05, 0}, {0x06, 0}, {0x07, 0}, {0x08, 0},
    {0x0a, 0}, {0x0b, 0}, {0x0e, 0}, {0x11, 0}, {0x12, 1}, {0x13, 0}, {0x14, 0}, {0x15, 0},
};
void *sSpNpcKatrinaMsgKey = sSpNpcKatrinaKey;
u8 sSpNpcKatrinaKey[15] = "sp_npc_panther";
SpNpcKatrinaTalkScript sSpNpcKatrinaTalkScripts[2] = {
    {NULL, 0},
    {&SpNpcKatrinaTalk::scriptReadPartnerName, 0},
};
SpNpcKatrinaActEntry sSpNpcKatrinaActTable[4] = {
    {&SpNpcKatrina::setupAct00, &SpNpcKatrina::mainAct00},
    {&SpNpcKatrina::setupAct01, &SpNpcKatrina::mainAct01},
    {&SpNpcKatrina::setupAct02, &SpNpcKatrina::mainAct02},
    {&SpNpcKatrina::setupAct03, &SpNpcKatrina::mainAct03},
};
const KatrinaFortuneCard sSpNpcKatrinaBadFortuneCards[21] = {
    {0x00, 1}, {0x01, 1}, {0x02, 1}, {0x03, 1}, {0x04, 1}, {0x05, 1}, {0x06, 1}, {0x08, 1}, {0x09, 1}, {0x0a, 1},
    {0x0c, 0}, {0x0c, 1}, {0x0d, 0}, {0x0e, 1}, {0x0f, 0}, {0x10, 0}, {0x10, 1}, {0x12, 0}, {0x13, 1}, {0x14, 1},
    {0x15, 1},
};
SpNpcKatrina *sSpNpcKatrinaInstance;
extern "C" ActorProfile sSpNpcKatrinaProfile = {(void *(*)())SpNpcKatrina_Create, 0x70, 0x76, 2, 0x5000, 0x5000, 0x3e800};
BOOL SpNpcKatrina::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    setCollisionRadius(0x100);
    setInteractionRange(0x5000);
    effectHandle = -1;
    effectTimer = 0;
    return TRUE;
}

BOOL SpNpcKatrina::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    sSpNpcKatrinaInstance = this;
    changeAct(0);
    collider.groups |= 2;
    fortuneMsg = 0xff;
    traitMsg = 0xff;
    return TRUE;
}

BOOL SpNpcKatrina::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    sSpNpcKatrinaInstance = 0;
    return TRUE;
}

BOOL SpNpcKatrina::onDraw() {
    if (!NpcActor::onDraw()) {
        return FALSE;
    }
    Model_GetJointWorldMtx(&model, &jointMtx, 0xe);
    TarotProps_Draw();
    return TRUE;
}

u8 *SpNpcKatrina::getTexturePath() { return sSpNpcKatrinaTexturePath; }

u8 *SpNpcKatrina::getModelPath() { return sSpNpcKatrinaModelPath; }

BOOL SpNpcKatrina::updateAct() {
    s32 t = actionCtrl.getEmotionId();
    if (t != 0x1e && t != 0x20) {
    } else if (actionCtrl.isActionDone()) {
        talk.onEventTag(0);
    }
    if (effectHandle == -1) {
        if (t == 0x21 && ((((u32)model.curFrame << 4) >> 16)) >= 0x12) {
            effectHandle = Effect_Create(0x3d, &jointPos[0], 0, 0);
            effectTimer = 0x16;
        }
    } else if (Math_CountDownU8(&effectTimer) == 0) {
        Effect_End(effectHandle);
        effectHandle = -1;
    } else {
        Effect_SetPosition(effectHandle, &jointPos[0], 0, 0);
    }
    BOOL r = FALSE;
    if (sSpNpcKatrinaActTable[act].exit) {
        r = (this->*sSpNpcKatrinaActTable[act].exit)();
    }
    return r;
}

void SpNpcKatrina::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcKatrinaActTable[state].enter) {
        ok = (this->*sSpNpcKatrinaActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcKatrina::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcKatrina::mainAct00() {
    if (isClosingTime()) {
        TalkRequest_AddPlayerTalk6(this, 0);
    }
    return TRUE;
}

BOOL SpNpcKatrina::setupAct01() {
    NpcActor *p = (NpcActor *)talk.getTalkPlayer();
    if (p) {
        getAngleTo(p);
    }
    talkCtrl.requestTalk(1, 0);
    return TRUE;
}

BOOL SpNpcKatrina::mainAct01() {
    if (!talkCtrl.isBusy()) {
        TalkRequest_SetTargetDone(this);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcKatrina::setupAct03() { return TRUE; }

BOOL SpNpcKatrina::mainAct03() {
    if (!talkCtrl.isBusy()) {
        SceneWarp_RequestExit(Scene_GetWarpRequest(), 0);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcKatrina::setupAct02() { return TRUE; }

BOOL SpNpcKatrina::mainAct02() { return TRUE; }

SpNpcKatrinaTalk::SpNpcKatrinaTalk() {}

SpNpcKatrinaTalk::~SpNpcKatrinaTalk() {}

void SpNpcKatrinaTalk::onEventTag(u32 a_) {
    s32 a = (s32)a_;
    if (a != owner->actionCtrl.getEmotionId() || owner->actionCtrl.getAction() != 8) {
        switch (a) {
        case 0x1e:
            TarotProps_StartAct01();
            break;
        case 0x1f:
            Bgm_ReleasePriority(0x10);
            TarotProps_StartAct02();
            break;
        case 0x20:
            TarotProps_StartAct03();
            break;
        }
    }
    ActorTalkRequest::onEventTag(a);
}

void SpNpcKatrinaTalk::attachOwner(SpNpcKatrina *o) {
    resetMsg();
    owner = o;
}

void SpNpcKatrinaTalk::start(TalkStartMsg *arg) {
    TalkStartMsg *out = arg;
    out->msgKey = (const char *)sSpNpcKatrinaMsgKey;
    s32 a = Talk_CheckAndSetPlayerFlag(4, 0);
    s32 b = Talk_CheckAndSetPlayerFlag(5, 0);
    s32 c = Talk_CheckAndSetPlayerFlag(6, 0);
    if (b == 0 || a == 0) {
        if (b == 0) {
            out->msgIndex = 1;
        } else {
            out->msgIndex = 5;
        }
    } else {
        if (c == 0) {
            out->msgIndex = 0x11;
        } else {
            out->msgIndex = 0x19;
        }
    }
    if (owner->isClosingTime()) {
        out->msgIndex = 0x13;
    }
}

void SpNpcKatrinaTalk::onMessageEnd(u32) {
    PlayerData *h = PlayerData_GetCurrent();
    u8 *villagers = gSaveData.villagers;
    u32 sel = 0xff;
    switch (msgIndex) {
    case 9:
    case 11:
        setSubSceneKind(0x13, 0);
        openSubScene(2);
        setScript(1);
        break;
    case 14:
        owner->drawFortuneCard();
        sel = owner->fortuneMsg;
        break;
    case 16:
        if (NpcActor_CanPlayerPay(owner, 0x64)) {
            NpcActor_ChargePlayer(owner, 0x64);
        }
        sel = 0x16;
        break;
    case 19:
        owner->changeAct(3);
        break;
    case 24:
        if (NpcActor_CanPlayerPay(owner, 10000)) {
            NpcActor_ChargePlayer(owner, 10000);
        }
        h->setFortune(0);
        Talk_CheckAndSetPlayerFlag(6, 1);
        sel = 0x16;
        break;
    case 10:
    case 12:
    case 13:
    case 15:
    case 17:
    case 18:
    case 20:
    case 21:
    case 22:
    case 23:
        break;
    }
    u32 cur = owner->traitMsg;
    if (cur != 0xff) {
        if (cur == msgIndex) {
            s32 kind;
            void *arg;
            VillagerData *p;
            s32 q;
            VillagerMemory *w;
            VillagerState *r5;
            sel = 0x10;
            kind = owner->getFortuneKind();
            arg = PlayerData_GetCurrent()->getPlayerId();
            switch (owner->readingMode) {
            case 0:
                h->setFortune(kind);
                if (kind == 1) {
                    SaveVillagers_ApplyGoodFortune(villagers, arg);
                } else if (kind == 2) {
                    SaveVillagers_ApplyBadFortune(villagers);
                }
                break;
            case 1:
                p = SaveVillagers_FindByName(villagers, owner->partnerName, 10, h->getPlayerId());
                if (p != 0) {
                    q = Villager_FindMemoryIndex(p->memories, arg);
                    w = Villager_GetMemory(p->memories, q);
                    if (p->getVillagerId()->isValid() != 0) {
                        r5 = Villager_GetState(p);
                    } else {
                        r5 = 0;
                    }
                    if (w != 0) {
                        switch (kind) {
                        case 1: {
                            CommManager *g = gCommManager;
                            if (g->isSlotActive(g->myAid) == 0 && r5 != 0) {
                                if (VillagerState_GetMood(r5) == 1) {
                                    VillagerState_AddMoodTimer(r5, 0xe10);
                                } else {
                                    VillagerState_SetMoodTimer(r5, 0xe10);
                                }
                                VillagerState_SetMood(r5, 1);
                            }
                            w->addFriendship(10);
                            VillagerSync_Friendship(p, q, w->getFriendship());
                            break;
                        }
                        case 2: {
                            CommManager *g = gCommManager;
                            if (g->isSlotActive(g->myAid) == 0 && r5 != 0) {
                                if (VillagerState_GetMood(r5) == 4) {
                                    VillagerState_AddMoodTimer(r5, 0x4b0);
                                } else {
                                    VillagerState_SetMoodTimer(r5, 0x4b0);
                                }
                                VillagerState_SetMood(r5, 4);
                            }
                            w->addFriendship(-3);
                            VillagerSync_Friendship(p, q, w->getFriendship());
                            break;
                        }
                        }
                    }
                }
                break;
            }
            owner->traitMsg = 0xff;
            owner->fortuneMsg = 0xff;
        }
        if (owner->fortuneMsg == msgIndex) {
            sel = owner->traitMsg;
        }
    }
    if (sel != 0xff) {
        u8 buf = sel;
        window->setNextMessage(&buf, sSpNpcKatrinaMsgKey);
    }
}

void SpNpcKatrinaTalk::onMessageStart(u32) {
    if (msgIndex == 0xe || msgIndex == 0x17) {
        Bgm_RequestSilence(0x10, 0, 0);
    }
}

void SpNpcKatrinaTalk::onChoice(u32) {
    u8 buf;
    u32 sel;
    s32 st;
    st = getChoiceList()->getResult();
    sel = 0xff;
    switch (msgIndex) {
    case 1:
    case 3:
    case 5:
        if (st == 0) {
            if (NpcActor_CanPlayerPay(owner, 0x64) == 0) {
                sel = 6;
            } else {
                sel = 7;
            }
        } else if (msgIndex == 5 && st == 1) {
            sel = 0x14;
        }
        break;
    case 7:
    case 8:
        if (st == 0) {
            if (Talk_CheckAndSetPlayerFlag(5, 0)) {
                sel = 8;
            } else {
                sel = 0xd;
                owner->readingMode = 0;
                Talk_CheckAndSetPlayerFlag(5, 1);
            }
        } else if (st == 1) {
            if (Talk_CheckAndSetPlayerFlag(4, 0)) {
                sel = 8;
            } else {
                sel = 9;
            }
        }
        break;
    case 10:
        if (st == 0) {
            sel = 0xc;
            owner->readingMode = 1;
            Talk_CheckAndSetPlayerFlag(4, 1);
        } else {
            sel = 0xb;
        }
        break;
    case 0x14:
        if (st == 0) {
            if (NpcActor_CanPlayerPay(owner, 10000) == 0) {
                sel = 0x15;
            } else {
                sel = 0x17;
            }
        }
        break;
    }
    if (sel != 0xff) {
        buf = sel;
        window->setNextMessage(&buf, sSpNpcKatrinaMsgKey);
    }
}

void SpNpcKatrinaTalk::update() {
    s32 i = script;
    if (sSpNpcKatrinaTalkScripts[i].flag != 0) {
        if (sSpNpcKatrinaTalkScripts[i].fn != 0) {
            (this->*sSpNpcKatrinaTalkScripts[i].fn)();
        }
    }
}

void SpNpcKatrinaTalk::onTaskDone(u32) {
    s32 i = script;
    if (sSpNpcKatrinaTalkScripts[i].flag == 0) {
        if (sSpNpcKatrinaTalkScripts[i].fn != 0) {
            (this->*sSpNpcKatrinaTalkScripts[i].fn)();
            setScript(0);
        }
    }
}

void SpNpcKatrinaTalk::setScript(s32 v) {
    script = v;
}


void SpNpcKatrinaTalk::scriptReadPartnerName() {
    u8 msg;
    TalkWindowState *o = window;
    msg = 0xb;
    if (MenuCtrl_IsResultOk()) {
        owner->partnerName = (u8 *)MenuCtrl_GetText();
        KatrinaMsgString17 src;
        KatrinaEncodedString16 dst;
        EncodedString_SetRaw(&dst, owner->partnerName, 0x10);
        src.fromEncoded(&dst, 0, 0);
        window->setSlot(0, &src);
        msg = 0xa;
    }
    o->setNextMessage(&msg, sSpNpcKatrinaMsgKey);
}

BOOL SpNpcKatrina::acceptsInteraction(void *) {
    BOOL r = FALSE;
    VecFx32 *src = (VecFx32 *)PlayerActor_GetBodyPos(4);
    VecFx32 rec;
    s32 bx, by;
    rec.x = src->x;
    rec.y = src->y;
    rec.z = src->z;
    bx = r;
    by = r;
    FieldPos_ToUnit(&bx, &by, &rec);
    if (act == 0) {
        s32 x = position.x;
        if (rec.x > x - 0x1000 && rec.x < x + 0x1000) {
            s32 z = position.z;
            if (rec.z > z + 0x2000 && rec.z < z + 0x4000) {
                r = TRUE;
            }
        }
    }
    return r;
}

void SpNpcKatrina::onInteractionEvent(u32 cmd, u8 b) {
    switch (cmd) {
    case 0:
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL SpNpcKatrina::isClosingTime() {
    ClockDateTime t = {0, 0, 0, 0, 0, 0, 0, 0};
    Clock_GetDateTime(&t);
    if (t.hour < 6) {
        return TRUE;
    }
    return FALSE;
}

extern "C" Mtx43 *SpNpcKatrina_GetJointMtx() {
    return &sSpNpcKatrinaInstance->jointMtx;
}

extern "C" u32 SpNpcKatrina_GetAnimFrame() {
    return (u16)(sSpNpcKatrinaInstance->model.curFrame >> 12);
}

void SpNpcKatrina::drawFortuneCard() {
    card = Random_GlobalBelow(0x16);
    if (Random_GlobalBelow(2) == 0) {
        inverted = 0;
    } else {
        inverted = 1;
    }
    s32 t = Random_GlobalBelow(2);
    s32 k = card * 2 + 0x1a;
    k += t;
    fortuneMsg = k + inverted * 0x2c;
    traitMsg = card + 0x72 + inverted * 0x16;
}


s32 SpNpcKatrina::getFortuneKind() {
    u8 i;
    for (i = 0; i < 0x11; i++) {
        if (card == sSpNpcKatrinaGoodFortuneCards[i].a && inverted == sSpNpcKatrinaGoodFortuneCards[i].b) {
            return 1;
        }
    }
    for (i = 0; i < 0x15; i++) {
        if (card == sSpNpcKatrinaBadFortuneCards[i].a && inverted == sSpNpcKatrinaBadFortuneCards[i].b) {
            return 2;
        }
    }
    return 0;
}

KatrinaMsgString17::KatrinaMsgString17() {}

KatrinaMsgString17::~KatrinaMsgString17() {}

u32 KatrinaMsgString17::capacity() { return 0x11; }

u8 *KatrinaMsgString17::data() { return unk_12; }

KatrinaEncodedString16::KatrinaEncodedString16() {}


KatrinaEncodedString16::~KatrinaEncodedString16() {}

u32 KatrinaEncodedString16::capacity() { return 0x10; }

u8 *KatrinaEncodedString16::data() { return unk_0e; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_02258de0) {
    HOST_OVERLAY_VAR(sSpNpcKatrinaModelPath),
    HOST_OVERLAY_VAR(sSpNpcKatrinaTexturePath),
    HOST_OVERLAY_VAR(sSpNpcKatrinaMsgKey),
    HOST_OVERLAY_VAR(sSpNpcKatrinaKey),
    HOST_OVERLAY_VAR(sSpNpcKatrinaTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcKatrinaActTable),
    HOST_OVERLAY_VAR(sSpNpcKatrinaInstance),
    HOST_OVERLAY_VAR(sSpNpcKatrinaProfile),
    HOST_OVERLAY_VARS_END
};

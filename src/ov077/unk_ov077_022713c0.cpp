#include "types.h"
#include "gfx/VecFx32.h"
#include "talk/TalkStartMsg.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveAnimSet.h"
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
#include "actor/ActorProfile.h"
#include "player/PlayerData.h"
#include "player/PlayerSpNpcRecord.h"
#include "town/ResettiVisitFlag.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020850e0.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov077/unk_ov077_022713c0.h"
#include "proto/main/unk_0204cc1c.h"


class ActorTalkRequest;
class SpNpcResetti;
class SpNpcResettiTalk;



extern "C" {
void TalkRequestFlags_ClearResetti();
void TalkRequestFlags_SetResetti();
BOOL Math_IsInRange(s32 v, s32 a, s32 b);
u8 Math_CountDownU8(u8 *p);
BOOL TalkRequest_SetTargetDone(Character *c);
void TalkRequest_AddPlayerTalk7(void *p, s32 a);
void PlayerActor_LocalPlayAnim99();
extern u16 data_020c6cc8;
extern u8 gFieldSceneKind;
extern BlockMap *gSceneBlockMap;
}






struct SpNpcResettiTalkScript {
    void (SpNpcResettiTalk::*fn)();
    u32 flag;
};

class SpNpcResettiTalk : public SpNpcTalkRequest {
public:
    SpNpcResettiTalk();
    virtual ~SpNpcResettiTalk();
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void onSignalTag(s32 a);
    virtual void onWindowClose();
    virtual void onTalkEnd();
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void attachOwner(SpNpcResetti *owner);
    void scriptCheckApology();
    void scriptWaitForTip();
    void setScript(s32 state);

    s32 script;
    u8 waitTimer;
    u8 pad_b1[3];
    SpNpcResetti *ownerNpc;
    u8 bgmSwitched;
    u8 pad_b9[3];
};

static inline u32 SpNpcResetti_FrameInt(s32 frame) {
    return ((u32)frame >> 12) & 0xffff;
}







struct Unk_ov077_02271a84_Pt {
    s32 x, y;
    constexpr Unk_ov077_02271a84_Pt(s32 a, s32 b) : x(a), y(b) {}
};

class SpNpcResetti : public SpNpcActor {
public:
    SpNpcResetti() : houseUnitX(0), houseUnitZ(0) {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct05();
    BOOL setupAct05();
    BOOL mainAct04();
    BOOL setupAct04();
    BOOL mainAct03();
    BOOL setupAct03();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct01();
    void changeAct(s32 state);
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();

    s32 act;
    SpNpcResettiTalk talk;
    u8 lastApologyPhrase;
    u8 pad_715[3];
    s32 houseUnitX;
    s32 houseUnitZ;
    s32 effectHandle;
};

struct SpNpcResettiActEntry {
    BOOL (SpNpcResetti::*enter)();
    BOOL (SpNpcResetti::*exit)();
};

extern "C" {
extern const u8 sSpNpcResettiOffenseMsgs[5];
extern u8 sSpNpcResettiKey[13];
extern u8 *sSpNpcResettiMsgKey;
extern u8 sSpNpcResettiModelPath[23];
extern u8 sSpNpcResettiTexturePath[27];
extern SpNpcResettiTalkScript sSpNpcResettiTalkScripts[3];
extern SpNpcResettiActEntry sSpNpcResettiActTable[6];
SpNpcResetti *SpNpcResetti_Create();
}

u8 sSpNpcResettiKey[13] = {'s','p','_','n','p','c','_','r','e','s','e','t',0};
const u8 sSpNpcResettiOffenseMsgs[5] = {0x00, 0x04, 0x09, 0x13, 0x1b};
u8 *sSpNpcResettiMsgKey = sSpNpcResettiKey;
u8 sSpNpcResettiModelPath[23] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','m','o','l','.','n','s','b','m','d',0};
u8 sSpNpcResettiTexturePath[27] = {'n','p','c','_','s','p','/','m','o','d','e','l','/','m','o','l','_','t','e','x','.','n','s','b','t','x',0};

ActorProfile sSpNpcResettiProfile = {(void *(*)())SpNpcResetti_Create, 0x65, 0x6b, 2, 0x5000, 0x5000, 0x3e800};




SpNpcResettiTalkScript sSpNpcResettiTalkScripts[3] = {
    {NULL, 0},
    {&SpNpcResettiTalk::scriptCheckApology, 0},
    {&SpNpcResettiTalk::scriptWaitForTip, 1},
};

SpNpcResettiActEntry sSpNpcResettiActTable[6] = {
    {&SpNpcResetti::setupAct00, &SpNpcResetti::mainAct00},
    {&SpNpcResetti::setupAct01, &SpNpcResetti::mainAct01},
    {&SpNpcResetti::setupAct02, &SpNpcResetti::mainAct02},
    {&SpNpcResetti::setupAct03, &SpNpcResetti::mainAct03},
    {&SpNpcResetti::setupAct04, &SpNpcResetti::mainAct04},
    {&SpNpcResetti::setupAct05, &SpNpcResetti::mainAct05},
};

static inline BOOL Unk_ov077_02271bf4_IsZero(u8 v) { return v == 0 ? TRUE : FALSE; }

SpNpcResetti *SpNpcResetti_Create() {
    return new SpNpcResetti();
}

BOOL SpNpcResetti::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    lastApologyPhrase = 0xff;
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    ((NpcMoveAnimSet *)(&moveAnimSet))->setStandAnim(0xfc);
    ((NpcMoveAnimSet *)(&moveAnimSet))->setWalkAnim(0xfc);
    shadowEnabled = 0;
    collisionEnabled = 0;
    return TRUE;
}

BOOL SpNpcResetti::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    collider.groups |= 2;
    setInteractionRange(0);
    changeAct(3);
    clearTalkStartMode();
    TalkRequestFlags_SetResetti();
    return TRUE;
}

BOOL SpNpcResetti::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    TalkRequestFlags_ClearResetti();
    return TRUE;
}

BOOL SpNpcResetti::onDraw() {
    if (act != 3) {
        NpcActor::onDraw();
    }
    return TRUE;
}

u8 *SpNpcResetti::getTexturePath() { return sSpNpcResettiTexturePath; }

u8 *SpNpcResetti::getModelPath() { return sSpNpcResettiModelPath; }

BOOL SpNpcResetti::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcResettiActTable[act].exit != NULL) {
        r = (this->*sSpNpcResettiActTable[act].exit)();
    }
    return r;
}

void SpNpcResetti::changeAct(s32 state) {
    BOOL r = TRUE;
    if (sSpNpcResettiActTable[state].enter != NULL) {
        r = (this->*sSpNpcResettiActTable[state].enter)();
    }
    if (r) {
        act = state;
    }
}

BOOL SpNpcResetti::setupAct00() { return TRUE; }

BOOL SpNpcResetti::mainAct00() { return TRUE; }

BOOL SpNpcResetti::setupAct01() {
    void *p = talk.getTalkPlayer();
    s16 v = 0;
    if (p != NULL) {
        v = ((NpcActor *)(this))->getAngleTo((NpcActor *)(p));
    }
    ((NpcTalkCtrl *)(&talkCtrl))->requestTurnAndTalk(0, v, 0);
    return TRUE;
}

BOOL SpNpcResetti::mainAct01() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0) {
        return TRUE;
    }
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        changeAct(5);
    }
    return TRUE;
}

BOOL SpNpcResetti::setupAct02() { return TRUE; }

BOOL SpNpcResetti::mainAct02() { return TRUE; }

BOOL SpNpcResetti::setupAct03() {
    BlockMap *g;
    s32 a, b, c, d;
    u16 u0, u1;
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xfd, 1, 0, 0);
    if (Unk_ov077_02271bf4_IsZero(gFieldSceneKind)) {
        g = gSceneBlockMap;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        if (g != NULL) {
            u0 = 0x5014;
            u1 = 0x501a;
            if (BlockMap_FindItemAllAttr(g, &a, &b, &c, &d, &u0, &u1, 1, 0)) {
                FieldUnit_FromBlockUnit(&houseUnitX, &houseUnitZ, a, b, c, d);
            }
        }
    }
    return TRUE;
}

Unk_ov077_02271a84_Pt SpNpcResetti_mainAct03_tbl1[5] = {
        Unk_ov077_02271a84_Pt(0, 3), Unk_ov077_02271a84_Pt(-1, 3), Unk_ov077_02271a84_Pt(-1, 2),
        Unk_ov077_02271a84_Pt(1, 3), Unk_ov077_02271a84_Pt(1, 2)
    };
Unk_ov077_02271a84_Pt SpNpcResetti_mainAct03_tbl2[2] = { Unk_ov077_02271a84_Pt(-2, 2), Unk_ov077_02271a84_Pt(2, 2) };
BOOL SpNpcResetti::mainAct03() {
    Character *pl = (Character *)PlayerActor_GetCharacter(4);
    s32 dx, dz;
    s32 ax, az;
    VecFx32 v;
    s32 i;
    if (pl == NULL) {
        ProcBase_RequestDelete(this);
        return TRUE;
    }
    model.frameStep = 0;
    model.curFrame = 0;
    {
        VecFx32 *pv = &pl->position;
        v.x = pv->x;
        v.y = pv->y;
        v.z = pv->z;
    }
    ax = 0;
    az = 0;
    FieldPos_ToUnit(&ax, &az, &v);
    dx = ax - houseUnitX;
    dz = az - houseUnitZ;
    {
        s16 w = ((NpcActor *)(this))->getAngleTo((NpcActor *)((void *)pl));
        rotY = w;
        moveAngleY = w;
    }
    i = 0;
    Unk_ov077_02271a84_Pt pb = SpNpcResetti_mainAct03_tbl2[1];
    Unk_ov077_02271a84_Pt pa = SpNpcResetti_mainAct03_tbl2[0];
    for (; i < 5; i++) {
        BOOL hit = FALSE;
        s32 tx = SpNpcResetti_mainAct03_tbl1[i].x;
        if (tx == dx) {
            s32 ty = SpNpcResetti_mainAct03_tbl1[i].y;
            if (ty == dz) {
                hit = TRUE;
            }
        }
        if (hit) {
            s32 x, z;
            if (i <= 2) {
                x = pb.x + houseUnitX;
                z = pb.y + houseUnitZ;
            } else {
                x = pa.x + houseUnitX;
                z = pa.y + houseUnitZ;
            }
            FieldPos_FromUnitCenter(&position, x, z);
            TalkRequest_AddPlayerTalk7(this, 0);
        }
    }
    return TRUE;
}

BOOL SpNpcResetti::setupAct04() {
    model.frameStep = 0x1000;
    effectHandle = Effect_Create(0x30, &position, 0, 0);
    Snd_SeEmitterPlayOneShotAlt(&seEmitter, 0x7e6, 0x7f, 0);
    collisionEnabled = 1;
    Bgm_RequestSilence(0x17, 0xf, 0);
    return TRUE;
}

BOOL SpNpcResetti::mainAct04() {
    Character *r = (Character *)PlayerActor_GetCharacter(4);
    s16 v = ((NpcActor *)(this))->getAngleTo((NpcActor *)(r));
    rotY = v;
    moveAngleY = v;
    if ((s16)SpNpcResetti_FrameInt(model.curFrame) == 0xc) {
        Effect_End(effectHandle);
        effectHandle = -1;
    }
    if (animCtrl.isPlayingAnim(0xfd, &moveAnimSet)) {
        if (actionCtrl.isActionDone()) {
            if (effectHandle != -1) {
                Effect_End(effectHandle);
                effectHandle = -1;
            }
            changeAct(1);
            return TRUE;
        }
    }
    return TRUE;
}

BOOL SpNpcResetti::setupAct05() {
    ((NpcActionCtrl *)(&actionCtrl))->requestPlayAnim(1, 0xfe, 1, data_020c6cc8, 0);
    Snd_SeEmitterPlayOneShotAlt(&seEmitter, 0x7e7, 0x7f, 0);
    return TRUE;
}

BOOL SpNpcResetti::mainAct05() {
    Character *r = (Character *)PlayerActor_GetCharacter(4);
    s32 f;
    s16 v = ((NpcActor *)(this))->getAngleTo((NpcActor *)(r));
    rotY = v;
    moveAngleY = v;
    f = (s16)SpNpcResetti_FrameInt(model.curFrame);
    if (f == 2) {
        effectHandle = Effect_Create(0x30, &position, 0, 0);
    }
    if (f == 0xc) {
        if (effectHandle != -1) {
            Effect_End(effectHandle);
            effectHandle = -1;
        }
    }
    if (animCtrl.isPlayingAnim(0xfe, &moveAnimSet)) {
        if (actionCtrl.isActionDone()) {
            TalkRequest_SetTargetDone(this);
            TownSessionState_GetResettiFlag(TownSessionState_Get())->set(0);
            ProcBase_RequestDelete(this);
            if (effectHandle != -1) {
                Effect_End(effectHandle);
                effectHandle = -1;
            }
            return TRUE;
        }
    }
    return TRUE;
}

void SpNpcResettiTalk::update() {
    if (sSpNpcResettiTalkScripts[script].flag != 0) {
        if (sSpNpcResettiTalkScripts[script].fn != NULL) {
            (this->*sSpNpcResettiTalkScripts[script].fn)();
        }
    }
}

void SpNpcResettiTalk::onTaskDone(u32) {
    if (sSpNpcResettiTalkScripts[script].flag == 0) {
        if (sSpNpcResettiTalkScripts[script].fn != NULL) {
            (this->*sSpNpcResettiTalkScripts[script].fn)();
            setScript(0);
        }
    }
}

void SpNpcResettiTalk::setScript(s32 state) {
    script = state;
    waitTimer = 0x5a;
}

void SpNpcResettiTalk::scriptWaitForTip() {
    if (Math_CountDownU8(&waitTimer) == 0) {
        u8 v = 0x10;
        window->setNextMessage(&v, sSpNpcResettiMsgKey);
        requestReopenWindow();
        setScript(0);
    }
}

void SpNpcResettiTalk::scriptCheckApology() {
    TalkWindowState *m = window;
    if (MenuCtrl_IsFinished()) {
        u8 v = 0x18;
        if (MenuCtrl_IsResultOk()) {
            if (Random_GlobalBelow(2) == 0) {
                v = 0x1a;
            } else {
                v = 0x19;
            }
        }
        m->setNextMessage(&v, sSpNpcResettiMsgKey);
        setScript(0);
    }
}

SpNpcResettiTalk::SpNpcResettiTalk() {}

SpNpcResettiTalk::~SpNpcResettiTalk() {}

void SpNpcResettiTalk::onTalkEnd() {
    if (bgmSwitched == 0) {
        Bgm_ReleasePriority(0x17);
        Bgm_Request(0x18, 0x43, 0x7f, 1);
        bgmSwitched = 1;
    }
}

void SpNpcResettiTalk::onWindowClose() {
    switch (msgIndex) {
    case 3:
    case 8:
    case 0x12:
    case 0x1a:
    case 0x23:
        Bgm_Release(0x43);
        Bgm_RequestSilence(0x17, 0x16, 0x20);
        break;
    }
}

void SpNpcResettiTalk::attachOwner(SpNpcResetti *owner) {
    resetMsg();
    ownerNpc = owner;
}

void SpNpcResettiTalk::onSignalTag(s32 a) {
    switch (a) {
    case 0:
        PlayerActor_LocalPlayAnim99();
        break;
    case 1:
        Snd_SeEmitterPlayOneShotAlt(&ownerNpc->seEmitter, 0x7f4, 0x7f, 0);
        break;
    case 2:
        Snd_SeEmitterPlayOneShotAlt(&ownerNpc->seEmitter, 0x7f5, 0x7f, 0);
        break;
    }
}

void SpNpcResettiTalk::start(TalkStartMsg *out) {
    s32 t = ((PlayerSpNpcRecord *)(PlayerData_GetCurrent()->getSpNpcRecord()))->getResetCount() - 1;
    if (t < 0) {
        t = 0;
    } else if (t > 5) {
        t = 5;
    }
    if (t == 5) {
        t = Random_GlobalBelow(4) + 1;
    }
    if (t < 0) {
        t = 0;
    } else if (t > 4) {
        t = 4;
    }
    out->msgIndex = sSpNpcResettiOffenseMsgs[t];
    out->msgKey = (const char *)sSpNpcResettiMsgKey;
}

void SpNpcResettiTalk::onMessageStart(u32) {
    if (msgIndex == 0x17) {
        u8 n = Random_GlobalBelow(0x10);
        u8 c;
        if (n == ownerNpc->lastApologyPhrase) {
            n = n + 1;
            if (n == 0x10) {
                n = 0;
            }
        }
        ownerNpc->lastApologyPhrase = n;
        c = ownerNpc->lastApologyPhrase;
        ((TalkWindowState *)(window))->setSlotFromString(0, &c, "st_general");
    }
}

void SpNpcResettiTalk::onMessageEnd(u32) {
    switch (msgIndex) {
    case 0xf:
        window->openMode = 0;
        setScript(2);
        break;
    case 0x17:
        setSubSceneKindArg(0xc, ownerNpc->lastApologyPhrase, 0);
        openSubScene(3);
        setScript(1);
        break;
    }
}

void SpNpcResettiTalk::onChoice(u32) {
    u8 cmd;
    s32 r = getChoiceList()->getResult();
    cmd = 0xff;
    switch (msgIndex) {
    case 0xb:
        if (r == 0) {
            cmd = Random_GlobalBelow(2) == 0 ? 0xe : 0xd;
        } else {
            cmd = Random_GlobalBelow(2) == 0 ? 0xe : 0xc;
        }
        break;
    case 0x1f:
    case 0x20:
    case 0x21: {
        u32 n = Random_GlobalBelow(0xd);
        if (Math_IsInRange(getChoiceList()->getSliderValue(), n, n + 5) != 0) {
            cmd = 0x22;
        } else {
            cmd = Random_GlobalBelow(2) == 0 ? 0x20 : 0x21;
        }
        break;
    }
    }
    if (cmd != 0xff) {
        u8 buf = cmd;
        window->setNextMessage(&buf, sSpNpcResettiMsgKey);
    }
}

BOOL SpNpcResetti::acceptsInteraction(void *) { return TRUE; }

void SpNpcResetti::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 1:
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(4);
        break;
    case 8:
        changeAct(2);
        break;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov077_022713c0) {
    HOST_OVERLAY_VAR(sSpNpcResettiKey),
    HOST_OVERLAY_VAR(sSpNpcResettiMsgKey),
    HOST_OVERLAY_VAR(sSpNpcResettiModelPath),
    HOST_OVERLAY_VAR(sSpNpcResettiTexturePath),
    HOST_OVERLAY_VAR(sSpNpcResettiProfile),
    HOST_OVERLAY_VAR(sSpNpcResettiTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcResettiActTable),
    HOST_OVERLAY_VAR(SpNpcResetti_mainAct03_tbl1),
    HOST_OVERLAY_VAR(SpNpcResetti_mainAct03_tbl2),
    HOST_OVERLAY_VARS_END
};

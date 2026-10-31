#include "types.h"
#include "host_overlay_vars.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "item/ItemId.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcLookAt.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/NpcMoveAnimSet.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "npc/NpcActionCtrl.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcTalkCtrl.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcFaceAnim.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "actor/NpcActor.h"
#include "game/CollisionState.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "player/PlayerData.h"
#include "room/HouseData.h"
#include "save/SaveData.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/ov068/unk_ov068_02266b44.h"


class FieldVillager;
class SpNpcNookIntro;
class SpNpcNookIntroTalk;

extern "C" {
BOOL TalkRequest_AddPlayerTalk6(Character *a, s32 b);
BOOL TalkRequest_SetTargetDone(Character *x);
u32 NookShop_GetLevel(void *p);
u8 Math_CountDownU8(u8 *p);
BOOL Camera_SetModeDefault(void);
BOOL Camera_FocusOnPoint(VecFx32 *a);
extern u16 data_020c6cc8;
extern u8 gU8None;
extern u8 gTalkMsgIndexEnd;
extern SaveData gSaveData;
}

class SpNpcNookIntroTalk : public SpNpcTalkRequest {
public:
    SpNpcNookIntroTalk();
    virtual ~SpNpcNookIntroTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void runWalkScript();
    void setScript(s32 a);
    void attachOwner(SpNpcNookIntro *o);

    /* 0xac */ s32 script;
    /* 0xb0 */ u8 scriptStep;
    /* 0xb1 */ u8 pad_b1[3];
    /* 0xb4 */ SpNpcNookIntro *owner;
};

typedef BOOL (SpNpcNookIntro::*SpNpcNookIntroActFn)();
struct SpNpcNookIntroActEntry {
    SpNpcNookIntroActFn enter;
    SpNpcNookIntroActFn exit;
};
typedef void (SpNpcNookIntroTalk::*SpNpcNookIntroTalkScriptFn)();
struct SpNpcNookIntroTalkScript {
    SpNpcNookIntroTalkScriptFn fn;
    u8 flag;
    u8 pad[3];
};

class SpNpcNookIntro : public SpNpcActor {
public:
    SpNpcNookIntro() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
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
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    /* 0x654 */ u32 act;
    SpNpcNookIntroTalk talk;
    u16 startAngle;
    u8 pad_712[2];
    VecFx32 walkTarget;
    u8 actTimer;
    u8 pad_721[3];
};

extern "C" char sNookTexRcd[0x1c] = "npc_sp/model/rcd_tex.nsbtx";
extern "C" SpNpcNookIntroTalkScript sNookIntroTalkScripts[2] = {{NULL, 0}, {&SpNpcNookIntroTalk::runWalkScript, 1}};

extern "C" SpNpcNookIntro *SpNpcNookIntro_Create() {
    return new SpNpcNookIntro();
}

ItemId SpNpcNookIntro_preCreate_tbl[4];
u8 SpNpcNookIntro_preCreate_tbl_init;
BOOL SpNpcNookIntro::preCreate() {
    if (!SpNpcNookIntro_preCreate_tbl_init) {
        HOST_STATIC_INIT_ARRAY(SpNpcNookIntro_preCreate_tbl, {
        ItemId(0xd019), ItemId(0xd01a),
        ItemId(0xd01b), ItemId(0xd01c)
    });
        SpNpcNookIntro_preCreate_tbl_init = 1;
    }
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setNpcHandle(&SpNpcNookIntro_preCreate_tbl[NookShop_GetLevel(gSaveData.nookShop)].id);
    setTalkRequest(&talk);
    talk.attachOwner(this);
    moveCtrl.setSpeedPreset(2, 0x399, 0x133, 0x199);
    return TRUE;
}

extern "C" const char *sNookModelPaths[4] = {sNookModelRcn, sNookModelRcc, sNookModelRcs,
                                                 sNookModelRcd};
extern "C" char sNookModelRcn[0x18] = "npc_sp/model/rcn.nsbmd";
extern "C" SpNpcNookIntroActEntry sSpNpcNookIntroActTable[6] = {
    {&SpNpcNookIntro::setupAct00, &SpNpcNookIntro::mainAct00},
    {&SpNpcNookIntro::setupAct01, &SpNpcNookIntro::mainAct01},
    {&SpNpcNookIntro::setupAct02, &SpNpcNookIntro::mainAct02},
    {&SpNpcNookIntro::setupAct03, &SpNpcNookIntro::mainAct03},
    {&SpNpcNookIntro::setupAct04, &SpNpcNookIntro::mainAct04},
    {&SpNpcNookIntro::setupAct05, &SpNpcNookIntro::mainAct05}};
extern "C" char sNookModelRcc[0x18] = "npc_sp/model/rcc.nsbmd";
extern "C" char sNookModelRcd[0x18] = "npc_sp/model/rcd.nsbmd";
extern "C" char sNookTexRcn[0x1c] = "npc_sp/model/rcn_tex.nsbtx";
extern "C" char sNookTexRcc[0x1c] = "npc_sp/model/rcc_tex.nsbtx";
extern "C" char sNookIntroMsgFile[0x14] = "sp_etc_sequence4";
extern "C" char sNookModelRcs[0x18] = "npc_sp/model/rcs.nsbmd";
extern "C" const char *sNookTexPaths[4] = {sNookTexRcn, sNookTexRcc, sNookTexRcs,
                                                 sNookTexRcd};
extern "C" void *sNookIntroMsgFilePtr = sNookIntroMsgFile;
extern "C" char sNookTexRcs[0x1c] = "npc_sp/model/rcs_tex.nsbtx";
extern "C" ActorProfile sSpNpcNookIntroProfile = {(void *(*)())SpNpcNookIntro_Create, 0x7d, 0x81, 2, 0x5000, 0x5000, 0x3e800};

BOOL SpNpcNookIntro::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    changeAct(0);
    startAngle = rotY;
    collider.groups |= 2;
    PlayerData *p = PlayerData_GetCurrent();
    if (p != NULL) {
        if (!GameStart_IsNewResident()) {
            if (!GameStart_IsNewTown()) {
                p->clearFlag(1);
            }
        }
    }
    Bgm_RequestSilence(0x13, 0xf, 0);
    return TRUE;
}

u8 *SpNpcNookIntro::getTexturePath() {
    return (u8 *)sNookTexPaths[NookShop_GetLevel(gSaveData.nookShop)];
}

u8 *SpNpcNookIntro::getModelPath() {
    return (u8 *)sNookModelPaths[NookShop_GetLevel(gSaveData.nookShop)];
}

BOOL SpNpcNookIntro::updateAct() {
    BOOL result = FALSE;
    if (sSpNpcNookIntroActTable[act].exit != NULL) {
        result = (this->*sSpNpcNookIntroActTable[act].exit)();
    }
    return result;
}

void SpNpcNookIntro::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcNookIntroActTable[state].enter != NULL) {
        ok = (this->*sSpNpcNookIntroActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcNookIntro::setupAct00() {
    return TRUE;
}

BOOL SpNpcNookIntro::mainAct00() {
    if (TalkRequest_AddPlayerTalk6(this, 0)) {
        PlayerActor_SetNoFaceTalkTarget(1, 4);
    }
    return TRUE;
}

BOOL SpNpcNookIntro::setupAct01() {
    u32 x;
    Character *p = talk.getTalkPlayer();
    x = 0;
    if (p != NULL) {
        x = getAngleTo((NpcActor *)p);
    }
    talkCtrl.requestTurnAndTalk(0, x, 1);
    return TRUE;
}

BOOL SpNpcNookIntro::mainAct01() {
    if (talkCtrl.isBusy() == 0) {
        Camera_SetModeDefault();
        Bgm_RequestSilence(0x13, 0x3c, 0);
        Bgm_Release(0x47);
        changeAct(3);
    }
    return TRUE;
}

BOOL SpNpcNookIntro::setupAct02() {
    VecFx32Ctor v;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    v.z += 0x2000;
    PlayerActor_RequestWalkTo(&v, 0x400, 4);
    return TRUE;
}

BOOL SpNpcNookIntro::mainAct02() {
    if (PlayerActor_IsScriptedWalking(4) == 0) {
        talk.resetMsg();
        talk.setTalkPlayer(getPlayerActor(4));
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcNookIntro::setupAct03() {
    actionCtrl.requestAction(3, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcNookIntro::mainAct03() {
    if (actionCtrl.getAction() == 3) {
        if (actionCtrl.isActionDone()) {
            changeAct(4);
        }
    }
    return TRUE;
}

BOOL SpNpcNookIntro::setupAct04() {
    walkTarget.x = position.x;
    walkTarget.y = position.y;
    walkTarget.z = position.z;
    walkTarget.x -= 0x2000;
    walkTarget.z += 0xa000;
    actionCtrl.requestAction(2, 1, walkTarget.x, walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0);
    actTimer = 0x3c;
    return TRUE;
}

BOOL SpNpcNookIntro::mainAct04() {
    if (actionCtrl.isActionDone() != 0 || Math_CountDownU8(&actTimer) == 0) {
        TalkRequest_SetTargetDone(this);
        if (PlayerData_GetCurrent()) {
            GameStart_Clear();
        }
    }
    return TRUE;
}

BOOL SpNpcNookIntro::setupAct05() {
    actTimer = 10;
    return TRUE;
}

BOOL SpNpcNookIntro::mainAct05() {
    if (Math_CountDownU8(&actTimer) == 0) {
        Bgm_ReleasePriority(0x13);
        Bgm_RequestSilence(0x12, 5, 5);
        ProcBase_RequestDelete(this);
    }
    return TRUE;
}

SpNpcNookIntroTalk::SpNpcNookIntroTalk() {}

SpNpcNookIntroTalk::~SpNpcNookIntroTalk() {
}

void SpNpcNookIntroTalk::attachOwner(SpNpcNookIntro *o) {
    resetMsg();
    owner = o;
}

void SpNpcNookIntroTalk::start(TalkStartMsg *out_) {
    TalkStartMsg *out = (TalkStartMsg *)out_;
    PlayerData *p = PlayerData_GetCurrent();
    if (p != NULL) {
        p->clearFlag(0x23);
    }
    out->msgKey = (const char *)sNookIntroMsgFilePtr;
    out->msgIndex = 0x22;
}

void SpNpcNookIntroTalk::onMessageEnd(u32) {
    TalkWindowState *sc = (TalkWindowState *)window;
    volatile u8 buf = gU8None;
    buf = 0;
    switch (msgIndex) {
    case 0x22:
        sc->setNextMessage(&gTalkMsgIndexEnd, 0);
        sc->openMode = 0;
        setScript(1);
        break;
    case 10:
    case 13: {
        s32 debt = ((HouseData *)gSaveData.house)->getDebt();
        if (debt == 0) {
            buf = 0xf;
        } else {
            setNumberSlot(debt, 1, 0xa, 1, 0);
            if (GameStart_IsNewTown() != 0) {
                buf = 0x1c;
            } else if (PlayerDataArray_CountUsed(gSaveData.players) <= 1) {
                buf = 0x27;
            } else {
                buf = 0xb;
            }
        }
        break;
    }
    case 11:
    case 0x1c:
    case 0x27:
        if (GameStart_IsNewResident() == 0 && GameStart_IsNewTown() == 0) {
            buf = 0xe;
        } else {
            buf = 0xc;
        }
        break;
    case 15:
        if (GameStart_IsNewResident() == 0 && GameStart_IsNewTown() == 0) {
            buf = 0x10;
        } else {
            buf = 0x11;
        }
        break;
    }
    if (buf != 0) {
        sc->setNextMessage((u8 *)&buf, sNookIntroMsgFilePtr);
    }
}

void SpNpcNookIntroTalk::onChoice(u32) {
}

void SpNpcNookIntroTalk::update() {
    if (sNookIntroTalkScripts[script].flag != 0) {
        if (sNookIntroTalkScripts[script].fn) {
            (this->*sNookIntroTalkScripts[script].fn)();
        }
    }
}

void SpNpcNookIntroTalk::onTaskDone(u32) {
    if (sNookIntroTalkScripts[script].flag == 0) {
        if (sNookIntroTalkScripts[script].fn) {
            (this->*sNookIntroTalkScripts[script].fn)();
            setScript(0);
        }
    }
}

void SpNpcNookIntroTalk::setScript(s32 a) {
    script = a;
    scriptStep = 0;
}

void SpNpcNookIntroTalk::runWalkScript() {
    switch (scriptStep) {
    case 0:
        if (window->state == 5) {
            Bgm_ReleasePriority(0x13);
            Bgm_Request(0x15, 0x47, 0x7f, 1);
            PlayerActor_SetNoFaceTalkTarget(0, 4);
            SpNpcNookIntro *o = owner;
            VecFx32 *pv = &o->position;
            VecFx32 *pd = &o->walkTarget;
            pd->x = pv->x;
            pd->y = pv->y;
            pd->z = pv->z;
            o = owner;
            o->walkTarget.x += 0x6000;
            o = owner;
            o->actionCtrl.requestAction(2, 2, o->walkTarget.x, o->walkTarget.z, 0, 0, 0, 0, data_020c6cc8, 0);
            scriptStep = 1;
        }
        break;
    case 1: {
        SpNpcNookIntro *o = owner;
        if (o->actionCtrl.isActionDone() != 0) {
            o = owner;
            if (o->actionCtrl.getAction() == 2) {
                o = owner;
                o->actionCtrl.requestAction(0, 2, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
                scriptStep = 2;
            }
        }
        break;
    }
    case 2: {
        SpNpcNookIntro *o = owner;
        if (o->actionCtrl.isActionDone() != 0) {
            o = owner;
            if (o->actionCtrl.getAction() == 0) {
                TalkWindowState *sc = (TalkWindowState *)window;
                volatile u8 buf = gU8None;
                if (GameStart_IsNewTown() != 0) {
                    buf = 0xd;
                } else {
                    buf = 0xa;
                }
                sc->setNextMessage((u8 *)&buf, sNookIntroMsgFilePtr);
                sc->nextState = 1;
                o = owner;
                VecFx32 t;
                VecFx32 *pt = &o->position;
                t.x = pt->x;
                t.y = pt->y;
                t.z = pt->z;
                t.y += 0x2000;
                Camera_FocusOnPoint(&t);
                setScript(0);
            }
        }
        break;
    }
    }
}

BOOL SpNpcNookIntro::acceptsInteraction(void *) {
    BOOL r = FALSE;
    if (act == 0) {
        r = TRUE;
    }
    return r;
}

void SpNpcNookIntro::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 1:
        changeAct(2);
        break;
    case 8:
        changeAct(5);
        break;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_02266b44) {
    HOST_OVERLAY_VAR(sNookTexRcd),
    HOST_OVERLAY_VAR(sNookIntroTalkScripts),
    HOST_OVERLAY_VAR(SpNpcNookIntro_preCreate_tbl),
    HOST_OVERLAY_VAR(SpNpcNookIntro_preCreate_tbl_init),
    HOST_OVERLAY_VAR(sNookModelPaths),
    HOST_OVERLAY_VAR(sNookModelRcn),
    HOST_OVERLAY_VAR(sSpNpcNookIntroActTable),
    HOST_OVERLAY_VAR(sNookModelRcc),
    HOST_OVERLAY_VAR(sNookModelRcd),
    HOST_OVERLAY_VAR(sNookTexRcn),
    HOST_OVERLAY_VAR(sNookTexRcc),
    HOST_OVERLAY_VAR(sNookIntroMsgFile),
    HOST_OVERLAY_VAR(sNookModelRcs),
    HOST_OVERLAY_VAR(sNookTexPaths),
    HOST_OVERLAY_VAR(sNookIntroMsgFilePtr),
    HOST_OVERLAY_VAR(sNookTexRcs),
    HOST_OVERLAY_VAR(sSpNpcNookIntroProfile),
    HOST_OVERLAY_VARS_END
};

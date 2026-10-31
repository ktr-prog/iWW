#include "types.h"
#include "host_mem.h"
#include "host_labels.h"
#include "sdk_linker_symbols.h"
#include "uptr.h"
#include "item/ItemId.h"
#include "talk/TalkStartMsg.h"
#include "save/TownExchangeRecord.h"
#include "talk/TalkWindowState.h"
#include "npc/NpcAnimCtrl.h"
#include "npc/NpcSpeechState.h"
#include "npc/NpcResHandle.h"
#include "npc/NpcObstacleProbe.h"
#include "npc/NpcMoveCtrl.h"
#include "npc/Unk_0201ad18.h"
#include "npc/NpcFootstepFx.h"
#include "sys/ProcBase.h"
#include "snd/SndSeEmitterKind1.h"
#include "npc/NpcTalkCtrl.h"
#include "item/ReceivedLetterBlock.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/ThreeLayerAnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/ActorTalkRequest.h"
#include "actor/NpcActor.h"
#include "actor/SpNpcActor.h"
#include "talk/ActorTalkRequest.h"
#include "talk/SpNpcTalkRequest.h"
#include "actor/ActorProfile.h"
#include "npc/NpcActionCtrl.h"
#include "talk/ChoiceList.h"
#include "gfx/ScreenTransition.h"
#include "sys/OverlayHandle.h"
#include "proto/main/unk_020b4828.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_0208f0b0.h"
#include "proto/main/unk_0209eb94.h"
#include "proto/main/unk_020afeb4.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_020742f4.h"
#include "proto/ov055/unk_ov055_02258de0.h"



class ActorTalkRequest;
class SpNpcRover;
















extern "C" {
#define data_021ecfa8 HOST_LABEL(u8 (*)[], data_021ecfa8)
extern u16 data_020c6cc8;
extern u16 gPad[];
extern const void *sSpNpcRoverMsgKey;

void OverlayHandle_Unload(void *p);
void *MI_CpuCopy8(void *dst, void *src, u32 n);
void *MI_CpuFill8(void *p, s32 v, u32 n);
void TalkRequestFlags_ClearSceneHold();
void TalkRequestFlags_SetSceneHold();
void Camera_SetMode20At(void *p);
}
class SpNpcRoverTalk;
typedef void (SpNpcRoverTalk::*SpNpcRoverTalkScriptFn)();

class SpNpcRoverTalk : public SpNpcTalkRequest {
public:
    SpNpcRoverTalk();
    virtual ~SpNpcRoverTalk();
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);
    virtual void start(TalkStartMsg *out);
    virtual void update();
    virtual void onTaskDone(u32 id);

    void waitTagModeStop();
    void waitLidOpen();
    void runTagMode();
    void attachOwner(SpNpcRover *owner);
    void setScript(s32 v);

    /* 0xac */ SpNpcRover *ownerNpc;
    /* 0xb0 */ s32 script;
};

struct SpNpcRoverTalkScript {
    SpNpcRoverTalkScriptFn fn;
    u8 flag;
    u8 pad[3];
};




struct SpNpcRoverTransfer {
    SpNpcRoverTransfer() {}
    /* 0x000 */ TownExchangeRecord record;
    /* 0x84c */ ReceivedLetterBlock letters;
};

class SpNpcRover;
typedef BOOL (SpNpcRover::*SpNpcRoverActFn)();

struct SpNpcRoverActEntry {
    SpNpcRoverActFn enter;
    SpNpcRoverActFn exit;
};

class SpNpcRover : public SpNpcActor {
public:
    SpNpcRover() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL acceptsInteraction(void *other);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL acceptsSelfRequestedInteraction(void *a);
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    void restoreOv068();
    void loadTagModeOverlay();
    void saveTagData();
    void prepareTagData();
    void restoreOwnTransfer();
    void applyReceivedData();
    BOOL mainAct02();
    BOOL setupAct02();
    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    /* 0x654 */ s32 act;
    /* 0x658 */ SpNpcRoverTalk talk;
    /* 0x70c */ u8 saveFailed;
    /* 0x70d */ u8 lidClosed;
    /* 0x70e */ u8 pad_70e[2];
    /* 0x710 */ SpNpcRoverTransfer send;
    /* 0x1058 */ SpNpcRoverTransfer recv;
};


extern "C" {
extern SpNpcRoverActEntry sSpNpcRoverActTable[3];
extern SpNpcRoverTalkScript sSpNpcRoverTalkScripts[4];
extern ActorProfile sSpNpcRoverProfile;
}

extern "C" char sSpNpcRoverKey[] = "sp_etc_sequence1";
extern "C" const void *sSpNpcRoverMsgKey = sSpNpcRoverKey;
extern "C" u8 sSpNpcRoverModelPath[] = "npc_sp/model/xct.nsbmd";
extern "C" u8 sSpNpcRoverTexturePath[] = "npc_sp/model/xct_tex.nsbtx";
extern "C" ActorProfile sSpNpcRoverProfile = {(void *(*)())SpNpcRover_Create, 0x5e, 0x65, 2, 0x5000, 0x5000, 0x3e800};
extern "C" SpNpcRoverTalkScript sSpNpcRoverTalkScripts[4] = {
    {0, 0},
    {&SpNpcRoverTalk::runTagMode, 1},
    {&SpNpcRoverTalk::waitLidOpen, 1},
    {&SpNpcRoverTalk::waitTagModeStop, 1},
};
extern "C" SpNpcRoverActEntry sSpNpcRoverActTable[3] = {
    {&SpNpcRover::setupAct00, &SpNpcRover::mainAct00},
    {&SpNpcRover::setupAct01, &SpNpcRover::mainAct01},
    {&SpNpcRover::setupAct02, &SpNpcRover::mainAct02},
};
extern "C" SpNpcRover *sSpNpcRoverInstance = 0;

static inline BOOL Unk_ov055_02259484_IsTwo(u8 v) { return v == 2 ? TRUE : FALSE; }

static inline BOOL Unk_ov055_0225915c_Both() {
    return (gTouchHeld != 0 && gTouchChanged != 0) ? TRUE : FALSE;
}

extern "C" SpNpcRover *SpNpcRover_Create() { return new SpNpcRover; }

BOOL SpNpcRover::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    setTalkRequest((ActorTalkRequest *)&talk);
    talk.attachOwner(this);
    return TRUE;
}

BOOL SpNpcRover::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    sSpNpcRoverInstance = this;
    loadTagModeOverlay();
    changeAct(0);
    Camera_SetMode20At(&position);
    TalkRequestFlags_SetSceneHold();
    prepareTagData();
    return TRUE;
}

BOOL SpNpcRover::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    sSpNpcRoverInstance = 0;
    restoreOv068();
    TalkRequestFlags_ClearSceneHold();
    saveTagData();
    return TRUE;
}

u8 *SpNpcRover::getTexturePath() { return sSpNpcRoverTexturePath; }

u8 *SpNpcRover::getModelPath() { return sSpNpcRoverModelPath; }

BOOL SpNpcRover::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcRoverActTable[act].exit) {
        r = (this->*sSpNpcRoverActTable[act].exit)();
    }
    return r;
}

void SpNpcRover::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcRoverActTable[state].enter) {
        ok = (this->*sSpNpcRoverActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcRover::setupAct00() {
    ((NpcActionCtrl *)(&actionCtrl))->requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcRover::mainAct00() {
    if (Unk_ov055_02259484_IsTwo(gScreenTransition.state)) {
        changeAct(1);
    }
    return TRUE;
}

BOOL SpNpcRover::setupAct01() {
    ((NpcTalkCtrl *)(&talkCtrl))->requestTalk(0, 1);
    return TRUE;
}

BOOL SpNpcRover::mainAct01() {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() == 0) {
        SceneWarp_RequestFade(Scene_GetWarpRequest(), 0x2c, 2, 2);
        changeAct(2);
    }
    return TRUE;
}

BOOL SpNpcRover::setupAct02() { return TRUE; }

BOOL SpNpcRover::mainAct02() { return TRUE; }

SpNpcRoverTalk::SpNpcRoverTalk() {}

SpNpcRoverTalk::~SpNpcRoverTalk() {}

void SpNpcRoverTalk::attachOwner(SpNpcRover *owner) {
    resetMsg();
    ownerNpc = owner;
}

void SpNpcRoverTalk::start(TalkStartMsg *out) {
    out->msgKey = (const char *)sSpNpcRoverMsgKey;
    out->msgIndex = 0x38;
}

void SpNpcRoverTalk::onMessageEnd(u32) {
    u8 m[4];
    TalkWindowState *r6 = window;
    switch (msgIndex) {
    case 0x39:
        if ((NetOverlay_AssertOv067(), Net_WlxIsReady(NULL)) == 0) {
            if (ownerNpc->saveFailed != 0) {
                m[0] = 0x36;
                r6->setNextMessage((u8 *)(&m[0]), (void *)sSpNpcRoverMsgKey);
                break;
            }
            Comm_StartOv067Mode();
            MI_CpuFill8(&ownerNpc->recv, 0, sizeof(SpNpcRoverTransfer));
            SpNpcRover *r4 = ownerNpc;
            NetOverlay_AssertOv067();
            Net_StartOv067(&r4->send, &r4->recv, sizeof(SpNpcRoverTransfer));
            (NetOverlay_AssertOv067(), Net_WlxStartExchange(NULL));
        }
        (NetOverlay_AssertOv067(), Net_WlxStartExchange(NULL));
        r6->lockAdvance();
        setScript(1);
        break;
    case 0x3c:
        ownerNpc->applyReceivedData();
        break;
    case 0x3b:
        ownerNpc->restoreOwnTransfer();
        break;
    }
}

void SpNpcRoverTalk::onChoice(u32) {
    s32 t = ((ChoiceList *)(window->getChoiceList()))->getResult();
    if (msgIndex == 0x3a && t == 1) {
        Comm_EndOv067Mode();
    }
}

void SpNpcRoverTalk::update() {
    u32 i = script;
    if (sSpNpcRoverTalkScripts[i].flag != 0) {
        if (sSpNpcRoverTalkScripts[i].fn) {
            (this->*sSpNpcRoverTalkScripts[i].fn)();
        }
    }
}

void SpNpcRoverTalk::onTaskDone(u32) {
    u32 i = script;
    if (sSpNpcRoverTalkScripts[i].flag == 0) {
        if (sSpNpcRoverTalkScripts[i].fn) {
            (this->*sSpNpcRoverTalkScripts[i].fn)();
            setScript(0);
        }
    }
}

void SpNpcRoverTalk::setScript(s32 v) { script = v; }

void SpNpcRoverTalk::runTagMode() {
    u8 m[2];
    BOOL k;
    if (((*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15) != 0) {
        k = TRUE;
    } else {
        k = FALSE;
    }
    BOOL r5 = FALSE;
    SpNpcRover *own = ownerNpc;
    if (own->lidClosed == 1 && k == 0) {
        r5 = TRUE;
    }
    own->lidClosed = k;
    if ((NetOverlay_AssertOv067(), Net_WlxIsExchangeDone(NULL))) {
        Comm_EndOv067Mode();
        m[0] = 0x3c;
        window->setNextMessage((u8 *)(&m[0]), (void *)sSpNpcRoverMsgKey);
        setScript(2);
    } else {
        if ((gPad[1] & 1) == 0 && !Unk_ov055_0225915c_Both() && r5 == 0) {
            return;
        }
        (NetOverlay_AssertOv067(), Net_WlxStopExchange(NULL));
        m[1] = 0x3a;
        window->setNextMessage((u8 *)(&m[1]), (void *)sSpNpcRoverMsgKey);
        setScript(3);
    }
}

void SpNpcRoverTalk::waitLidOpen() {
    if (((*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15) == 0) {
        Snd_PlaySe(0x69);
        window->unlockAdvance();
        setScript(0);
    }
}


void SpNpcRoverTalk::waitTagModeStop() {
    TalkWindowState *r4 = window;
    if (((*HW_SYSWORK(volatile u16, buttonXY) & 0x8000) >> 15) == 0) {
        if ((NetOverlay_AssertOv067(), Net_WlxIsExchangeDone(NULL))) {
            Snd_PlaySe(0x69);
            Comm_EndOv067Mode();
            u8 m = 0x3c;
            window->setNextMessage((u8 *)(&m), (void *)sSpNpcRoverMsgKey);
        } else {
            if ((NetOverlay_AssertOv067(), Net_WlxIsReady(NULL)) != 1) {
                (NetOverlay_AssertOv067(), Net_WlxStopExchange(NULL));
                return;
            }
        }
        r4->unlockAdvance();
        setScript(0);
    }
}

void SpNpcRover::applyReceivedData() {
    TownExchangeRecord *r4 = static_cast<TownExchangeRecord *>(TownExchange_GetForAid(4));
    u32 st = recv.letters.exchangeKind;
    if (st == 2) {
        MI_CpuCopy8(&recv.letters, data_021ecfa8, 0xf8);
        restoreOwnTransfer();
    } else if (st == 1) {
        MI_CpuCopy8(&recv.record, r4, sizeof(TownExchangeRecord));
        r4->incrementCounter();
        r4->setUnkFlag(1);
    }
}

void SpNpcRover::restoreOwnTransfer() {
    MI_CpuCopy8(&send.record, TownExchange_GetForAid(4), sizeof(TownExchangeRecord));
}

BOOL SpNpcRover::acceptsInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

BOOL SpNpcRover::acceptsSelfRequestedInteraction(void *) {
    if (((NpcTalkCtrl *)(&talkCtrl))->isBusy() != 0 || netIsTalkLocked() != 0) {
        return FALSE;
    }
    return TRUE;
}

void SpNpcRover::onInteractionEvent(u32 a, u8) {
    switch (a) {
    case 0:
        talk.resetMsg();
        ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 1:
        talk.resetMsg();
        ((ActorTalkRequest *)(&talk))->setTalkPlayer(getPlayerActor(4));
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

void SpNpcRover::prepareTagData() {
    Constellation_PrepareExchange();
    TownExchangeRecord *r4 = static_cast<TownExchangeRecord *>(TownExchange_GetForAid(4));
    MI_CpuCopy8(r4, &send.record, sizeof(TownExchangeRecord));
    send.letters.exchangeKind = 1;
    TownExchange_Clear(r4);
    if (saveFailed == 0) {
        s32 r = Save_WriteVillagerTransfer();
        if (r == 1 || r == 4) {
            saveFailed = 1;
        }
    }
}

void SpNpcRover::saveTagData() {
    if (saveFailed == 0) {
        TownExchange_GetForAid(4);
        s32 r = Save_WriteVillagerTransfer();
        if (r == 1 || r == 4) {
            saveFailed = 1;
        }
    }
}

void SpNpcRover::loadTagModeOverlay() {
    OverlayHandle_Unload(&gOverlayHandle);
    OverlayHandle_Load(reinterpret_cast<OverlayHandleView *>(&gOverlayHandle), OVERLAY_67_ID);
}

void SpNpcRover::restoreOv068() {
    OverlayHandle_Unload(&gOverlayHandle);
    OverlayHandle_Load(reinterpret_cast<OverlayHandleView *>(&gOverlayHandle), OVERLAY_68_ID);
}


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov055_02258de0) {
    HOST_OVERLAY_VAR(sSpNpcRoverKey),
    HOST_OVERLAY_VAR(sSpNpcRoverMsgKey),
    HOST_OVERLAY_VAR(sSpNpcRoverModelPath),
    HOST_OVERLAY_VAR(sSpNpcRoverTexturePath),
    HOST_OVERLAY_VAR(sSpNpcRoverProfile),
    HOST_OVERLAY_VAR(sSpNpcRoverTalkScripts),
    HOST_OVERLAY_VAR(sSpNpcRoverActTable),
    HOST_OVERLAY_VAR(sSpNpcRoverInstance),
    HOST_OVERLAY_VARS_END
};

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
#include "proto/main/unk_0209eb94.h"
#include "proto/ov004/unk_ov004_0221e3a4.h"


class ActorTalkRequest;















class SpNpcTortimer2;

struct SpNpcTortimer2ActEntry {
    BOOL (SpNpcTortimer2::*enter)();
    BOOL (SpNpcTortimer2::*exit)();
};

extern "C" {
extern u16 data_020c6cc8;
extern SpNpcTortimer2ActEntry sSpNpcTortimer2ActTable[];
u8 Math_CountDownU8(u8 *p);
}

class SpNpcTortimer2 : public SpNpcActor {
public:
    SpNpcTortimer2() {}
    virtual BOOL onCreate();
    virtual BOOL preCreate();
    virtual BOOL onDelete();
    virtual BOOL updateAct();
    virtual u8 *getTexturePath();
    virtual u8 *getModelPath();

    BOOL mainAct01();
    BOOL setupAct01();
    BOOL mainAct00();
    BOOL setupAct00();
    void changeAct(s32 state);

    /* 0x654 */ s32 act;
    /* 0x658 */ u8 idleLoops;
};


extern "C" SpNpcTortimer2 *SpNpcTortimer2_Create() { return new SpNpcTortimer2; }

BOOL SpNpcTortimer2::preCreate() {
    if (!SpNpcActor::preCreate()) {
        return FALSE;
    }
    moveAnimSet.setStandAnim(0xff);
    return TRUE;
}

BOOL SpNpcTortimer2::onCreate() {
    if (!SpNpcActor::onCreate()) {
        return FALSE;
    }
    sSpNpcTortimer2 = this;
    changeAct(0);
    collider.groups |= 2;
    collisionEnabled = 0;
    return TRUE;
}

BOOL SpNpcTortimer2::onDelete() {
    if (!SpNpcActor::onDelete()) {
        return FALSE;
    }
    sSpNpcTortimer2 = 0;
    return TRUE;
}

u8 *SpNpcTortimer2::getTexturePath() { return sSpNpcTortimer2TexturePath; }

u8 *SpNpcTortimer2::getModelPath() { return sSpNpcTortimer2ModelPath; }

BOOL SpNpcTortimer2::updateAct() {
    BOOL r = FALSE;
    if (sSpNpcTortimer2ActTable[act].exit) {
        r = (this->*sSpNpcTortimer2ActTable[act].exit)();
    }
    return r;
}

void SpNpcTortimer2::changeAct(s32 state) {
    BOOL ok = TRUE;
    if (sSpNpcTortimer2ActTable[state].enter) {
        ok = (this->*sSpNpcTortimer2ActTable[state].enter)();
    }
    if (ok) {
        act = state;
    }
}

BOOL SpNpcTortimer2::setupAct00() {
    actionCtrl.requestAction(0, 1, 0, 0, 0, 0, 0, 0, data_020c6cc8, 0);
    idleLoops = 0xa;
    return TRUE;
}

BOOL SpNpcTortimer2::mainAct00() {
    if (((u32)model.curFrame << 4) >> 16 == (((u32)model.numFrames << 4) >> 16) - 1) {
        if (Math_CountDownU8(&idleLoops) == 0 && SaveManager_IsIdle()) {
            changeAct(1);
        }
    }
    return TRUE;
}

BOOL SpNpcTortimer2::setupAct01() {
    actionCtrl.requestPlayAnim(1, 0x100, 1, data_020c6cc8, 0);
    return TRUE;
}

BOOL SpNpcTortimer2::mainAct01() {
    if (animCtrl.isPlayingAnim(0x100, &moveAnimSet) && actionCtrl.isActionDone()) {
        actionCtrl.requestPlayAnim(1, 0x101, 1, data_020c6cc8, 0);
    }
    if (animCtrl.isPlayingAnim(0x101, &moveAnimSet) && actionCtrl.isActionDone()) {
        changeAct(0);
    }
    return TRUE;
}


extern "C" BOOL SpNpcTortimer2_IsIdle() {
    SpNpcTortimer2 *y = sSpNpcTortimer2;
    if (y) {
        if (y->animCtrl.isPlayingAnim(0xff, &y->moveAnimSet) && sSpNpcTortimer2->act == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

extern "C" u8 sSpNpcTortimer2ModelPath[23] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'i', '.', 'n', 's', 'b', 'm', 'd', 0};
extern "C" u8 sSpNpcTortimer2TexturePath[27] = {'n', 'p', 'c', '_', 's', 'p', '/', 'm', 'o', 'd', 'e', 'l', '/', 't', 't', 'i', '_', 't', 'e', 'x', '.', 'n', 's', 'b', 't', 'x', 0};
extern "C" ActorProfile sSpNpcTortimer2Profile = {(void *(*)())SpNpcTortimer2_Create, 0x5d, 0x64, 2, 0x5000, 0x5000, 0x3e800};
extern "C" SpNpcTortimer2ActEntry sSpNpcTortimer2ActTable[2] = {
    {&SpNpcTortimer2::setupAct00, &SpNpcTortimer2::mainAct00},
    {&SpNpcTortimer2::setupAct01, &SpNpcTortimer2::mainAct01},
};
extern "C" SpNpcTortimer2 *volatile sSpNpcTortimer2 = 0;

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0221e3a4) {
    HOST_OVERLAY_VAR(sSpNpcTortimer2ModelPath),
    HOST_OVERLAY_VAR(sSpNpcTortimer2TexturePath),
    HOST_OVERLAY_VAR(sSpNpcTortimer2Profile),
    HOST_OVERLAY_VAR(sSpNpcTortimer2ActTable),
    HOST_OVERLAY_VAR(sSpNpcTortimer2),
    HOST_OVERLAY_VARS_END
};

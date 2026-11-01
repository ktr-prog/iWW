#include "types.h"
#include "host_tick.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "field/Unk_ov003_02214494_Views.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "game/ReddPassword.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "town/ReddTent.h"
#include "gfx/DebugColor.h"
#include "game/ReddShop.h"
#include "talk/ReddPasswordString.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_02214494.h"
#include "proto/main/unk_020b4828.h"

extern "C" DebugColor data_ov003_02235144(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov003_02235160(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov003_0223514c(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov003_02235158(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov003_0223515c(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov003_02235148(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sReddTentProfile = {(void *(*)())ReddTent_Create, 0x1b, 0x21, 0, 0xc8000, 0x12c000, 0x258000};














extern "C" {
BOOL TalkRequest_SetTargetDone(void *p);
BOOL TalkRequest_AddPlayerTalk6(void *p, u32 a);
s32 Scene_GetCurrent();
s32 Ground_GetDefaultY(u32 a);
s32 ReddPassword_LearnCurrentPlayer();
s32 ReddPassword_CurrentPlayerKnows();
#define data_021ed2c0 HOST_LABEL(ReddShop *, data_021ed2c0)
void Clock_GetDateTime(ClockDateTime *p);
}


extern "C" void *ReddTent_Create() {
    return new ReddTent;
}


ReddTent::ReddTent() {
}


ReddTent::~ReddTent() {
}


BOOL ReddTent::initBuilding() {
    ClockDateTimeWords l;
    l.words[0] = 0;
    l.words[1] = 0;
    Clock_GetDateTime(&l.dt);
    createHour = l.dt.hour;
    return TRUE;
}


BOOL ReddTent::onExecute() {
    updateTentState();
    return TRUE;
}


BOOL ReddTent::isOpen() {
    ClockDateTimeWords l;
    l.words[0] = 0;
    l.words[1] = 0;
    Clock_GetDateTime(&l.dt);
    if (l.dt.hour < 6) {
        goto no;
    }
    if (createHour >= 6) {
        goto yes;
    }
    return FALSE;
yes:
    return TRUE;
no:
    return FALSE;
}


void ReddTent::onMessageStart(u32) {
    if (msgIndex == 2) {
        ReddPasswordString obj;
        if (data_021ed2c0.getPassword()->getPromptText(&obj)) {
            window->setSlot(0, &obj);
        }
    }
}


void ReddTent::onMessageEnd(u32) {
    switch (msgIndex) {
    case 2:
        window->openMode = 1;
        setTentState(4);
        break;
    case 3:
    case 0x32:
        setTentState(6);
        break;
    }
}


void ReddTent::onChoice(u32) {
}


BOOL ReddTent::getVoiceType() {
    return FALSE;
}


BOOL ReddTent::setTentState(s32 i) {
    static BOOL (ReddTent::*tbl[10])() = {
        &ReddTent::enterTentIdle, &ReddTent::enterTentCheck,
        &ReddTent::enterTentTalkOpen, &ReddTent::enterTentTalk,
        &ReddTent::enterTentMenuWait, &ReddTent::enterTentMenu,
        &ReddTent::enterTentGoIn, &ReddTent::enterTentEntry07,
        &ReddTent::enterTentWalkIn, &ReddTent::enterTentWarp,
    };
    if (i < 10) {
        if ((this->*tbl[i])()) {
            tentState = i;
            return TRUE;
        }
    }
    return FALSE;
}


void ReddTent::updateTentState() {
    static void (ReddTent::*tbl[10])() = {
        &ReddTent::execTentIdle, &ReddTent::execTentCheck,
        &ReddTent::execTentTalkOpen, &ReddTent::execTentTalk,
        &ReddTent::execTentMenuWait, &ReddTent::execTentMenu,
        &ReddTent::execTentGoIn, &ReddTent::execTentEntry07,
        &ReddTent::execTentWalkIn, &ReddTent::execTentWarp,
    };
    s32 i = tentState;
    if (i < 10) {
        (this->*tbl[i])();
    }
}


BOOL ReddTent::enterTentIdle() {
    return TRUE;
}


void ReddTent::execTentIdle() {
    if (colliderFlags & 4) {
        TalkRequest_AddPlayerTalk6(this, 0);
    }
}


BOOL ReddTent::enterTentCheck() {
    BuildingOccupancy_RequestEnter(itemId);
    entryFlags.f1 = 0;
    return TRUE;
}


void ReddTent::execTentCheck() {
    u32 r = BuildingOccupancy_GetAnswer(itemId);
    if (r != 0) {
        u8 s;
        if (r == 2) {
            s = 1;
        } else {
            s = 0;
        }
        entryFlags.f1 = s;
        setTentState(2);
    }
}


BOOL ReddTent::enterTentTalkOpen() {
    StackPad8 pad;
    ((Character *)(this))->attachTalkRequest(this);
    setFileName("sp_npc_fox");
    if (isOpen() == 0) {
        msgIndex = 0x34;
        if (entryFlags.f1 == 0) {
            BuildingOccupancy_Leave(itemId, 0);
        }
    } else {
        if (entryFlags.f1) {
            msgIndex = 0x31;
        } else if (ReddPassword_CurrentPlayerKnows()) {
            msgIndex = 0x32;
        } else {
            msgIndex = 0;
        }
    }
    window->nextState = 1;
    setNoSpeakerName(0);
    return TRUE;
}


void ReddTent::execTentTalkOpen() {
    TalkWindowState *t = window;
    if (t) {
        if (t->state != 0) {
            setTentState(3);
        }
    }
}


BOOL ReddTent::enterTentTalk() {
    return TRUE;
}


void ReddTent::execTentTalk() {
    TalkWindowState *t = window;
    if (t) {
        if (t->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}


BOOL ReddTent::enterTentMenuWait() {
    return TRUE;
}


void ReddTent::execTentMenuWait() {
    if (window->state == 5) {
        MenuCtrl_OpenLauncherWithIndex(0xe, data_021ed2c0.getPassword()->getAnswerIndex());
        setTentState(5);
    }
}


BOOL ReddTent::enterTentMenu() {
    return TRUE;
}


void ReddTent::execTentMenu() {
    if (MenuCtrl_IsFinished()) {
        u8 r[2];
        if (MenuCtrl_IsResultOk()) {
            ReddPassword_LearnCurrentPlayer();
            r[0] = 3;
            window->setNextMessage(&r[0], (void *)("sp_npc_fox"));
            window->nextState = 1;
            setTentState(3);
        } else {
            r[1] = 4;
            window->setNextMessage(&r[1], (void *)("sp_npc_fox"));
            window->nextState = 1;
            setTentState(3);
            BuildingOccupancy_Leave(itemId, 0);
        }
    }
}


BOOL ReddTent::enterTentGoIn() {
    return TRUE;
}


void ReddTent::execTentGoIn() {
    TalkWindowState *t = window;
    if (t) {
        if (t->state == 0) {
            setTentState(7);
        }
    }
}


BOOL ReddTent::enterTentEntry07() {
    PlayerActor_RequestStowThenAct10(0);
    return TRUE;
}


void ReddTent::execTentEntry07() {
    if (PlayerActor_IsStowFinished()) {
        if (setTentState(8)) {
            ((Character *)(this))->detachTalkRequest(this);
        }
    }
}


BOOL ReddTent::enterTentWalkIn() {
    doorEnterRequested = 0;
    return TRUE;
}


void ReddTent::execTentWalkIn() {
    if (PlayerActor_IsEnteringDoor()) {
        setTentState(9);
    } else if (doorEnterRequested == 0) {
        s16 ang;
        VecFx32 v;
        if (getDoorPos(&v, &ang)) {
            if (PlayerActor_LocalRequestDoorEnter(2, &v.x, &v.z, ang)) {
                doorEnterRequested = 1;
            }
        }
    }
}


BOOL ReddTent::enterTentWarp() {
    warpFrames = 0;
    return TRUE;
}


void ReddTent::execTentWarp() {
    if (PlayerActor_IsStowFinished()) {
        warpFrames += TICK_STEP_ENDS() ? 1 : 0;
    }
    u32 lim;
    if (getEntranceType() == 2) {
        lim = 0x14;
    } else {
        lim = 0xf;
    }
    if (getEntranceType() == 1) {
        lim += 0xc;
    }
    if (warpFrames >= lim) {
        s32 t = getInteriorScene();
        s16 ang;
        VecFx32 v;
        if (getDoorPos(&v, &ang)) {
            if (SceneWarp_RequestExit(Scene_GetWarpRequest(), t)) {
                v.y = Ground_GetDefaultY(0);
                v.z = v.z + 0x1000;
                SceneWarp *o = Scene_GetWarpRequest();
                s32 r = Scene_GetCurrent();
                Scene_SetTownReturnPos(o, r, &v, 0xf000000, (s16)(ang + 0x8000), gridX, gridZ);
                entryFlags.f0 = 1;
            }
        }
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02214494) {
    HOST_OVERLAY_VAR(data_ov003_02235144),
    HOST_OVERLAY_VAR(data_ov003_02235160),
    HOST_OVERLAY_VAR(data_ov003_0223514c),
    HOST_OVERLAY_VAR(data_ov003_02235158),
    HOST_OVERLAY_VAR(data_ov003_0223515c),
    HOST_OVERLAY_VAR(data_ov003_02235148),
    HOST_OVERLAY_VAR(sReddTentProfile),
    HOST_OVERLAY_VARS_END
};

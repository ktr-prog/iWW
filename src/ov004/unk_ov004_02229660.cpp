#include "types.h"
#include "host_overlay_vars.h"
#include "proto/main/unk_020b4828.h"
#include "gfx/VecFx32.h"
#include "room/RoomTelephoneActEntry.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/V3.h"
#include "room/RoomTelephoneTypes.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "talk/TalkWindowState.h"
#include "room/PhoneChoiceSet.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "room/RoomTelephone.h"
#include "net/CommManager.h"
#include "game/TouchPickSphere.h"
#include "game/TouchPicker.h"
#include "gfx/TwoLayerAnimModel.h"
#include "save/SaveData.h"
#include "talk/ChoiceList.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_020411dc.h"
#include "gfx/ScreenTransition.h"
#include "proto/main/unk_0203c92c.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0208eeac.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020b5e5c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov004/unk_ov004_02229660.h"















class TouchPicker;
class ChoiceList;


extern "C" {
extern CommManager *gCommManager;
extern u8 gSaveData[];
extern u8 gTalkMsgIndexNone[];

u32 Scene_GetCurrent();
void TalkRequest_AddPlayerTalk6(void *p, s32 a);
void TalkRequest_SetTargetDone(void *p);
s32 Vec_DistXZ(s32 *a, s32 *b);
}



typedef void (RoomTelephone::*RoomTelephoneActFn)();




extern "C" {
extern const u8 sRoomTelephoneChoiceMsgs[3];
extern const u8 sRoomTelephoneChoiceMsgsScene6[4];
extern const s32 sRoomTelephonePos[3];
extern const char sRoomTelephoneMsgFile[];
extern const char *data_ov004_0224e178;
extern PhoneChoiceSet data_ov004_0224e298;
extern PhoneChoiceSet data_ov004_0224e2a0;
extern PhoneChoiceSet data_ov004_0224e2a8;
}


extern "C" DebugColor data_ov004_02251294(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov004_02251284(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_0225128c(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_02251280(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_0225127c(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_02251290(0x14, 0x18, 0x18, 0x1f);

extern "C" { RoomTelephoneActEntry sRoomTelephoneActTable[15]; }

extern "C" void StaticInit_unk_ov004_02229660(void) {
    HOST_STATIC_INIT_ARRAY(sRoomTelephoneActTable, {
        { (RoomTelephoneActFn)&RoomTelephone::enterAct00, (RoomTelephoneActFn)&RoomTelephone::execAct00 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct01, (RoomTelephoneActFn)&RoomTelephone::execAct01 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct02, (RoomTelephoneActFn)&RoomTelephone::execAct02 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct03, (RoomTelephoneActFn)&RoomTelephone::execAct03 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct04, (RoomTelephoneActFn)&RoomTelephone::execAct04 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct05, (RoomTelephoneActFn)&RoomTelephone::execAct05 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct06, (RoomTelephoneActFn)&RoomTelephone::execAct06 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct07, (RoomTelephoneActFn)&RoomTelephone::execAct07 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct08, (RoomTelephoneActFn)&RoomTelephone::execAct08 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct09, (RoomTelephoneActFn)&RoomTelephone::execAct09 },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct0A, (RoomTelephoneActFn)&RoomTelephone::execAct0A },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct0B, (RoomTelephoneActFn)&RoomTelephone::execAct0B },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct0C, (RoomTelephoneActFn)&RoomTelephone::execAct0C },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct0D, (RoomTelephoneActFn)&RoomTelephone::execAct0D },
        { (RoomTelephoneActFn)&RoomTelephone::enterAct0E, (RoomTelephoneActFn)&RoomTelephone::execAct0E },
    });
}
#undef FN

extern "C" {
extern const u8 sRoomTelephoneChoiceMsgs[3] = { 0x1b, 0x17, 0x20 };
extern const u8 sRoomTelephoneChoiceMsgsScene6[4] = { 0x0f, 0x1b, 0x17, 0x20 };
extern const s32 sRoomTelephonePos[3] = { 0x11000, 0, 0x11000 };
extern const char sRoomTelephoneMsgFile[] = "sp_etc_sequence1";
u8 data_ov004_0224e16c[2] = { 0x14, 0x15 };
u8 data_ov004_0224e170[3] = { 0x08, 0x11, 0x17 };
u8 data_ov004_0224e174[4] = { 0x07, 0x08, 0x11, 0x17 };
char sRoomTelephoneMsgFile2[] = "sp_etc_sequence1";
const char *data_ov004_0224e178 = sRoomTelephoneMsgFile2;
PhoneChoiceSet data_ov004_0224e298 = { data_ov004_0224e174, 4 };
PhoneChoiceSet data_ov004_0224e2a0 = { data_ov004_0224e170, 3 };
PhoneChoiceSet data_ov004_0224e2a8 = { data_ov004_0224e16c, 2 };
char sRoomTelephoneArcPath[] = "/roomObj/obj_telephone.arc";
char sRoomTelephoneTexPath[] = "/roomObj/obj_telephone.nsbtx";
RoomTelephone *volatile sRoomTelephone;
}
extern "C" ActorProfile sRoomTelephoneProfile = { (void *(*)())RoomTelephone_Create, 0x2d, 0x33, 0, 0xc8000, 0x12c000, 0x258000 };

extern "C" void RoomTelephone_PlayAnimHold() {
    RoomTelephone *g = sRoomTelephone;
    if (g) {
        ((BlendAnimModel *)(&sRoomTelephone->model))->initAnim(RoomObjRes_GetBca(&g->res, 0), 1, 0x1000, ((Unk_ov004_02229660_Bits *)&g->model.numFrames)->mid, 0);
    }
}

extern "C" void RoomTelephone_PlayAnimHangUp() {
    RoomTelephone *g = sRoomTelephone;
    if (g) {
        ((BlendAnimModel *)(&sRoomTelephone->model))->initAnim(RoomObjRes_GetBca(&g->res, 0), 3, 0x1000, ((Unk_ov004_02229660_Bits *)&g->model.numFrames)->mid, 0);
    }
}

extern "C" void RoomTelephone_PlayAnimPickUp() {
    RoomTelephone *g = sRoomTelephone;
    if (g) {
        ((BlendAnimModel *)(&sRoomTelephone->model))->initAnim(RoomObjRes_GetBca(&g->res, 0), 1, 0x1000, 0, 0);
    }
}

extern "C" BOOL RoomTelephone_StartAct0A() {
    RoomTelephone *g = sRoomTelephone;
    if (g) {
        g->changeAct(10);
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL RoomTelephone_IsTalking() {
    RoomTelephone *g = sRoomTelephone;
    if (g) {
        if (g->isTalking) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void RoomTelephone::openTalk(const char *name, u32 flag) {
    TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
    resetMsg();
    setFileName(name);
    msgIndex = flag;
    (p)->attachRequest(this);
    p->nextState = 1;
}

void RoomTelephone::execAct0E() {
    if (MenuCtrl_IsFinished()) {
        TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
        u8 c = 0x10;
        if (!MenuCtrl_IsResultOk()) {
            c = 0x18;
        }
        (p)->setNextMessage(&c, (void *)(void *)(sRoomTelephoneMsgFile2));
        p->nextState = 1;
        if (Scene_GetCurrent() == 6) {
            changeAct(0xc);
        } else {
            changeAct(4);
        }
    }
}

void RoomTelephone::enterAct0E() {}

void RoomTelephone::execAct0D() {
    TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
    if (p->state == 5) {
        MenuCtrl_OpenLauncher(0x30);
        changeAct(0xe);
    }
}

void RoomTelephone::enterAct0D() {}

void RoomTelephone::execAct0C() {
    TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
    if (p->state == 0) {
        (p)->detachRequest();
        isTalking = 0;
        changeAct(7);
    }
}

void RoomTelephone::enterAct0C() {}

void RoomTelephone::execAct0B() {
    TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
    if (p->state == 0) {
        (p)->detachRequest();
        isTalking = 0;
        changeAct(7);
    }
}

void RoomTelephone::enterAct0B() {}

void RoomTelephone::execAct0A() {
    if (window) {
        if (window->state) {
            changeAct(0xb);
        }
    }
}

void RoomTelephone::enterAct0A() {
    openTalk(sRoomTelephoneMsgFile2, 0xe);
    isTalking = 1;
}

void RoomTelephone::execAct09() {
    TalkWindowState *p = (TalkWindowState *)TalkWindow_Get(0);
    if (p->state == 0) {
        (p)->detachRequest();
        isTalking = 0;
        changeAct(7);
    }
}

void RoomTelephone::enterAct09(const char *name, u32 flag) {
    openTalk(sRoomTelephoneMsgFile2, 0x22);
}

void RoomTelephone::execAct08() {
    BOOL f;
    if (gScreenTransition.state == 2) {
        f = TRUE;
    } else {
        f = FALSE;
    }
    if (f) {
        changeAct(9);
    }
}

void RoomTelephone::enterAct08() {
    isTalking = 1;
}

void RoomTelephone::execAct07() {
    VecFx32 out;
    s32 a;
    u8 b;
    BOOL f;
    if (gScreenTransition.state == 2) {
        f = TRUE;
    } else {
        f = FALSE;
    }
    if (f) {
        Scene_GetTouchPicker()->pushBox(&touchBox);
        if (Scene_GetCurrent() == 6) {
            if (gCommManager->localSlot != 4) {
                return;
            }
        }
        if (InputMode_IsTouch()) {
            if (gTouchPrevHeld && gTouchPrevChanged) {
                f = TRUE;
            } else {
                f = FALSE;
            }
            if (f) {
                if (TouchPickResult_GetTarget(Scene_GetTouchPicker(), &out, &a, &b)) {
                    if (a == 0xd) {
                        changeAct(0xa);
                    }
                }
            }
        }
    }
}

void RoomTelephone::enterAct07() {}
void RoomTelephone::execAct06() {}
void RoomTelephone::enterAct06() {}

void RoomTelephone::execAct05() {
    if (model.isFinished()) {
        ((Character *)(this))->detachTalkRequest(this);
        TalkRequest_SetTargetDone(this);
        changeAct(6);
    }
}

void RoomTelephone::enterAct05() {
    PlayerActor_LocalRequestPhoneHangUp();
    RoomObj_PlaySe(&se, 0x4d5);
}

void RoomTelephone::execAct04() {
    if (window) {
        if (!window->state) {
            changeAct(5);
        }
    }
}

void RoomTelephone::enterAct04() {}

void RoomTelephone::execAct03() {
    if (window) {
        if (!window->state) {
            changeAct(5);
        }
    }
}

void RoomTelephone::enterAct03() {}

void RoomTelephone::execAct02() {
    if (window) {
        if (window->state) {
            changeAct(3);
        }
    }
}

void RoomTelephone::enterAct02() {
    StackPad8 pad;
    ((Character *)(this))->attachTalkRequest(this);
    setFileName(data_ov004_0224e178);
    if (gCommManager->isOnline()) {
        msgIndex = 0x1d;
    } else {
        msgIndex = 0xe;
    }
    window->nextState = 1;
}

void RoomTelephone::execAct01() {
    if (model.isFinished()) {
        changeAct(2);
    }
}

void RoomTelephone::enterAct01() {
    PlayerActor_LocalRequestPhonePickUp();
    RoomObj_PlaySe(&se, 0x4d4);
}

void RoomTelephone::execAct00() {
    void *r5 = TouchPick_GetTappedObject(Scene_GetTouchPicker(), 0, 0);
    void *r0 = PlayerActor_GetActor(4);
    if (r5 && r0 && r5 == r0) {
        if (acceptsInteraction(PlayerActor_GetCharacter(4))) {
            TalkRequest_AddPlayerTalk6(this, 0);
            return;
        }
    }
    Scene_GetTouchPicker()->pushBox(&touchBox);
}

void RoomTelephone::enterAct00() {}

void RoomTelephone::changeAct(s32 state) {
    if (sRoomTelephoneActTable[state].enter) {
        (this->*sRoomTelephoneActTable[state].enter)();
    }
    act = state;
}

void RoomTelephone::openChoices(PhoneChoiceSet *p, s32 v) {
    TalkWindowState *m = window;
    ChoiceList *o = (m)->getChoiceList();
    const u8 *s = p->choiceMsgs;
    u8 n = p->numChoices;
    s32 i;
    s32 m1 = -1;
    if (v != m1) {
        (o)->reset(n, v);
    } else {
        (o)->reset(n, m1);
    }
    s32 c0 = 0;
    for (i = 0; i < n; i++) {
        s32 c = c0;
        u32 b = s[i];
        if ((u8)(b + 0xec) <= 1) {
            c = 3;
        }
        u8 bb = b;
        (o)->setEntry(i, (const u8 *)(&bb), 1, (const u8 *)(gTalkMsgIndexNone), NULL, c);
    }
    (o)->loadTexts();
    (m)->openChoices(1);
}

void RoomTelephone::onMessageEnd(u32) {
    TalkWindowState *m = window;
    switch (msgIndex) {
    case 0x1b:
        openChoices(&data_ov004_0224e2a8, -1);
        break;
    case 0xe:
    case 0x1f:
        if (Scene_GetCurrent() == 6) {
            openChoices(&data_ov004_0224e298, 3);
        } else {
            openChoices(&data_ov004_0224e2a0, 2);
        }
        break;
    case 0xf:
        m->openMode = 1;
        changeAct(0xd);
        break;
    case 0x20:
        m->voice.clearVoiceOverride();
        break;
    case 0x2a:
    case 0x2b:
    case 0x2c:
        m->voice.clearMsgModeOverride();
        break;
    }
}

void RoomTelephone::onMessageStart(u32) {
    TalkWindowState *m = window;
    switch (msgIndex) {
    case 0xe:
        m->voice.setVoiceOverride(0);
        break;
    case 0x2a:
    case 0x2b:
    case 0x2c:
        m->voice.setMsgModeOverride(0);
        break;
    }
}

VecFx32 *RoomTelephone::getInteractionPos() {
    return (VecFx32 *)sRoomTelephonePos;
}

void RoomTelephone::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
    case 1:
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL RoomTelephone::acceptsInteraction(void *a) {
    Character *o = (Character *)a;
    if (o) {
        if (Vec_DistXZ(&o->position.x, (s32 *)sRoomTelephonePos) < 0x2333) {
            u32 d = (u16)(o->rotY - (rotY + 0x8000));
            if (d < 0x1000 || d >= 0xf000) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}

BOOL RoomTelephone::onDelete() {
    releaseResources();
    sRoomTelephone = 0;
    return TRUE;
}

BOOL RoomTelephone::onDraw() {
    model.drawAnimated(0);
    return TRUE;
}

BOOL RoomTelephone::onExecute() {
    if (sRoomTelephoneActTable[act].exec) {
        (this->*sRoomTelephoneActTable[act].exec)();
    }
    model.stepAnim();
    return TRUE;
}

BOOL RoomTelephone::onCreate() {
    sRoomTelephone = this;
    position.x = sRoomTelephonePos[0]; position.y = sRoomTelephonePos[1]; position.z = sRoomTelephonePos[2];
    setCharId(0);
    loadResources(sRoomTelephoneArcPath, sRoomTelephoneTexPath);
    if (RoomObjRes_GetBca(&res, 0)) {
        if (model.allocAnmObj(gBgHeap)) {
            void *r = RoomObjRes_GetBca(&res, 0);
            ((BlendAnimModel *)(&model))->initAnim(r, 3, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    V3Arr v;
    v.v[0] = sRoomTelephonePos[0];
    v.v[1] = sRoomTelephonePos[1];
    v.v[2] = sRoomTelephonePos[2];
    Scene_GetTouchPicker()->addBox(&touchBox, (VecFx32 *)v.v, 0x2000, 0x2000, 0x2000, 0, 0xd, 0xff);
    u8 *const g = gSaveData;
    if (Scene_GetCurrent() == 6) {
        if (((SaveData *)(g))->testFlag(0) == 0) {
            changeAct(8);
            ((SaveData *)(g))->setFlag(0);
        } else {
            changeAct(7);
        }
    } else {
        changeAct(0);
    }
    return TRUE;
}

RoomTelephone::~RoomTelephone() {
}

RoomTelephone::RoomTelephone() {
}

extern "C" RoomTelephone *RoomTelephone_GetInstance() {
    return sRoomTelephone;
}

extern "C" RoomTelephone *RoomTelephone_Create() {
    return new RoomTelephone;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02229660) {
    HOST_OVERLAY_VAR(data_ov004_02251294),
    HOST_OVERLAY_VAR(data_ov004_02251284),
    HOST_OVERLAY_VAR(data_ov004_0225128c),
    HOST_OVERLAY_VAR(data_ov004_02251280),
    HOST_OVERLAY_VAR(data_ov004_0225127c),
    HOST_OVERLAY_VAR(data_ov004_02251290),
    HOST_OVERLAY_VAR(sRoomTelephoneActTable),
    HOST_OVERLAY_VAR(data_ov004_0224e16c),
    HOST_OVERLAY_VAR(data_ov004_0224e170),
    HOST_OVERLAY_VAR(data_ov004_0224e174),
    HOST_OVERLAY_VAR(sRoomTelephoneMsgFile2),
    HOST_OVERLAY_VAR(data_ov004_0224e178),
    HOST_OVERLAY_VAR(data_ov004_0224e298),
    HOST_OVERLAY_VAR(data_ov004_0224e2a0),
    HOST_OVERLAY_VAR(data_ov004_0224e2a8),
    HOST_OVERLAY_VAR(sRoomTelephoneArcPath),
    HOST_OVERLAY_VAR(sRoomTelephoneTexPath),
    HOST_OVERLAY_VAR(sRoomTelephone),
    HOST_OVERLAY_VAR(sRoomTelephoneProfile),
    HOST_OVERLAY_VARS_END
};

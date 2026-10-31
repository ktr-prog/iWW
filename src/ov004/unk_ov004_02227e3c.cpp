#include "game/BoxCollider.h"
#include "host_overlay_vars.h"
#include "proto/main/unk_020b4828.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "gfx/CachedModel.h"
#include "game/TouchPicker.h"
#include "talk/MsgRequest.h"
#include "gfx/AnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "room/RoomObjActor.h"
#include "game/TouchPickTriangle.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0205b7b0.h"
#include "snd/BgmManager.h"
#include "proto/main/unk_0209c3e0.h"
#include "proto/ov004/unk_ov004_02227e3c.h"

struct RecycleBoxStackPad {
    s32 v[2];
    RecycleBoxStackPad() {}
    ~RecycleBoxStackPad() {}
};






class RecycleBox : public RoomObjActor, public TalkMsgRequest {
public:
    RecycleBox();
    virtual ~RecycleBox();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL changeSyncState(u32 idx);
    virtual void onMessageStart(u32 attr);
    virtual void onMessageEnd(u32 attr);
    virtual void onChoice(u32 attr);

    void removeCollision();
    void initCollision();
    void execAct05();
    void enterAct05();
    void execAct04();
    BOOL enterAct04();
    void execAct03();
    void enterAct03();
    void execAct02();
    BOOL enterAct02();
    void execAct01();
    BOOL enterAct01();
    void execAct00();
    BOOL enterAct00();
    void execAct();
    BOOL changeAct(s32 m);
    void updateState03();
    BOOL enterState03();
    void updateState02();
    BOOL enterState02();
    void updateState01();
    BOOL enterState01();
    void updateState00();
    BOOL enterState00();
    void updateState();

    /* 0x2d4 */ BoxCollider collider;
    /* 0x370 */ TouchPickBox touchBox;
    /* 0x618 */ s32 act;
};

typedef void (RecycleBox::*Unk_ov004_02228008_Fn)();
typedef void (RecycleBox::*Unk_ov004_02228168_Fn)();
typedef BOOL (RecycleBox::*Unk_ov004_022280b0_Fn)();

extern "C" {
extern BgmManager *data_021c1b3c;
extern s32 gGfxMainOnTop;
s32 BoxCollider_Unregister(BoxCollider *);
s32 BoxCollider_Register(BoxCollider *, s32, s32, s32, VecFx32 *, s16, VecFx32 *);
s32 TalkRequest_SetTargetDone(void *);
s32 Vec_DistXZ(s32 *a, s32 *b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
void RoomObj_PlaySe(void *, s32);
}
extern "C" { extern DebugColor data_ov004_02250e70; }
extern "C" { extern DebugColor data_ov004_02250e64; }
extern "C" { extern DebugColor data_ov004_02250e60; }
extern "C" { extern DebugColor data_ov004_02250e6c; }
extern "C" { extern DebugColor data_ov004_02250e5c; }
extern "C" { extern DebugColor data_ov004_02250e4c; }
extern "C" { extern ActorProfile sRecycleBoxProfile; }
extern "C" { extern char sRecycleBoxMsgFile[0x10]; }
extern "C" { extern char *sRecycleBoxMsgFilePtr; }
extern "C" { extern RecycleBox *sRecycleBox; }

extern "C" DebugColor data_ov004_02250e70(31, 20, 20, 31);

extern "C" DebugColor data_ov004_02250e64(20, 20, 31, 31);

extern "C" DebugColor data_ov004_02250e60(31, 31, 20, 31);

extern "C" DebugColor data_ov004_02250e6c(20, 31, 20, 31);

extern "C" DebugColor data_ov004_02250e5c(20, 31, 31, 31);

extern "C" DebugColor data_ov004_02250e4c(20, 24, 24, 31);

extern "C" ActorProfile sRecycleBoxProfile = {(void *(*)())RecycleBox_Create, 0x12, 0x16, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" char sRecycleBoxMsgFile[0x10] = "sp_npc_trash";

extern "C" char *sRecycleBoxMsgFilePtr = sRecycleBoxMsgFile;

extern "C" RecycleBox *sRecycleBox = 0;

extern "C" RecycleBox *RecycleBox_Create() {
    return new RecycleBox;
}

extern "C" RecycleBox *RecycleBox_GetInstance() {
    return sRecycleBox;
}

RecycleBox::RecycleBox() {
}

RecycleBox::~RecycleBox() {
}

BOOL RecycleBox::onCreate() {
    sRecycleBox = this;
    setSyncSlot(0);
    loadResourcesByName("obj_r_box");
    initCollision();
    if (RoomObjRes_GetBca(&res, 0)) {
        if (model.allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)(&model))->initAnim(RoomObjRes_GetBca(&res, 0), 1, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    changeAct(0);
    changeSyncState(getSyncState());
    return TRUE;
}

BOOL RecycleBox::onExecute() {
    updateState();
    execAct();
    Scene_GetTouchPicker()->pushBox(&touchBox);
    return TRUE;
}

BOOL RecycleBox::onDraw() {
    model.drawAnimated(0);
    return TRUE;
}

BOOL RecycleBox::onDelete() {
    removeCollision();
    releaseResources();
    sRecycleBox = 0;
    return TRUE;
}

BOOL RecycleBox::acceptsInteraction(void *a) {
    Character *o = (Character *)a;
    if (o) {
        if (Vec_DistXZ(&o->position.x, &position.x) < 0x299a) {
            if (Math_AngleDiffAbs((s16)(rotY + 0x8000), o->rotY) < 0x1200) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void RecycleBox::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL RecycleBox::changeSyncState(u32 idx) {
    static Unk_ov004_022280b0_Fn tbl[4] = {
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterState00,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterState01,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterState02,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterState03,
    };
    if (idx < 4) {
        if ((this->*tbl[idx])()) {
            if (((RoomObjActor *)(this))->storeSyncState(idx)) {
                tex.syncState = idx;
                return TRUE;
            }
        }
    }
    return FALSE;
}

void RecycleBox::updateState() {
    static Unk_ov004_02228168_Fn tbl[4] = {
        &RecycleBox::updateState00,
        &RecycleBox::updateState01,
        &RecycleBox::updateState02,
        &RecycleBox::updateState03,
    };
    u32 i = tex.syncState;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL RecycleBox::enterState00() {
    ((BlendAnimModel *)(&model))->initAnim(RoomObjRes_GetBca(&res, 0), 1, 0x1000, 0, 0);
    return TRUE;
}

void RecycleBox::updateState00() {}

BOOL RecycleBox::enterState01() {
    ((BlendAnimModel *)(&model))->initAnim(RoomObjRes_GetBca(&res, 0), 1, 0x1000, 0, 0);
    RoomObj_PlaySe(&se, 0x4d6);
    return TRUE;
}

void RecycleBox::updateState01() {
    if (model.isFinished()) {
        changeSyncState(2);
    } else {
        model.stepAnim();
    }
}

BOOL RecycleBox::enterState02() {
    ((BlendAnimModel *)(&model))->initAnim(RoomObjRes_GetBca(&res, 1), 1, 0x1000, 0, 0);
    return TRUE;
}

void RecycleBox::updateState02() {}

BOOL RecycleBox::enterState03() {
    ((BlendAnimModel *)(&model))->initAnim(RoomObjRes_GetBca(&res, 1), 1, 0x1000, 0, 0);
    RoomObj_PlaySe(&se, 0x4d7);
    return TRUE;
}

void RecycleBox::updateState03() {
    if (model.isFinished()) {
        changeSyncState(0);
    } else {
        model.stepAnim();
    }
}

Unk_ov004_022280b0_Fn RecycleBox_changeAct_tbl[6];
u8 RecycleBox_changeAct_tbl_init;
BOOL RecycleBox::changeAct(s32 m) {
    if (!RecycleBox_changeAct_tbl_init) {
        HOST_STATIC_INIT_ARRAY(RecycleBox_changeAct_tbl, {
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterAct00,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterAct01,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterAct02,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterAct03,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterAct04,
        (Unk_ov004_022280b0_Fn)&RecycleBox::enterAct05,
    });
        RecycleBox_changeAct_tbl_init = 1;
    }
    if (m < 6) {
        if ((this->*RecycleBox_changeAct_tbl[m])()) {
            act = m;
            return TRUE;
        }
    }
    return FALSE;
}

void RecycleBox::execAct() {
    static Unk_ov004_02228008_Fn tbl[6] = {
        &RecycleBox::execAct00,
        &RecycleBox::execAct01,
        &RecycleBox::execAct02,
        &RecycleBox::execAct03,
        &RecycleBox::execAct04,
        &RecycleBox::execAct05,
    };
    if (act < 6) {
        (this->*tbl[act])();
    }
}

BOOL RecycleBox::enterAct00() {
    return TRUE;
}

void RecycleBox::execAct00() {}

BOOL RecycleBox::enterAct01() {
    RecycleBoxStackPad pad;
    ((Character *)(this))->attachTalkRequest((TalkMsgRequest *)this);
    MsgRequest::setFileName(sRecycleBoxMsgFilePtr);
    MsgRequest::msgIndex = 0;
    TalkMsgRequest::window->nextState = 1;
    return TRUE;
}

void RecycleBox::execAct01() {
    if (TalkMsgRequest::window != 0) {
        if (TalkMsgRequest::window->state != 0) {
            changeAct(2);
        }
    }
}

BOOL RecycleBox::enterAct02() {
    return TRUE;
}

void RecycleBox::execAct02() {
    if (TalkMsgRequest::window != 0) {
        if (TalkMsgRequest::window->state == 0) {
            ((Character *)(this))->detachTalkRequest((TalkMsgRequest *)this);
            changeAct(3);
        }
    }
}

void RecycleBox::enterAct03() {
    RoomObjSync_ChangeState(this, 1);
}

void RecycleBox::execAct03() {
    if (tex.syncState == 2) {
        changeAct(4);
    }
}

BOOL RecycleBox::enterAct04() {
    if (MenuCtrl_OpenLauncher(0x20) != 0) {
        return TRUE;
    }
    return FALSE;
}

void RecycleBox::execAct04() {
    if (gGfxMainOnTop == 0) {
        if (MenuCtrl_IsFinished() != 0) {
            changeAct(5);
        }
    }
}

void RecycleBox::enterAct05() {
    RoomObjSync_ChangeState(this, 3);
}

void RecycleBox::execAct05() {
    if (tex.syncState == 0) {
        TalkRequest_SetTargetDone(this);
    }
}

void RecycleBox::onMessageStart(u32) {}

void RecycleBox::onMessageEnd(u32) {
    data_021c1b3c->mixer.talkDuckHold = 0x1a;
}

void RecycleBox::onChoice(u32 a) {}

void RecycleBox::initCollision() {
    BoxCollider_Register(&collider, 0x2000, 0x4000, 0x2000, &position, 0, 0);
    Scene_GetTouchPicker()->addBox(&touchBox, &position, 0x2000, 0x4000, 0x2000, 0, 0xc, 0xff);
}

void RecycleBox::removeCollision() {
    BoxCollider_Unregister(&collider);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02227e3c) {
    HOST_OVERLAY_VAR(data_ov004_02250e70),
    HOST_OVERLAY_VAR(data_ov004_02250e64),
    HOST_OVERLAY_VAR(data_ov004_02250e60),
    HOST_OVERLAY_VAR(data_ov004_02250e6c),
    HOST_OVERLAY_VAR(data_ov004_02250e5c),
    HOST_OVERLAY_VAR(data_ov004_02250e4c),
    HOST_OVERLAY_VAR(sRecycleBoxProfile),
    HOST_OVERLAY_VAR(sRecycleBoxMsgFile),
    HOST_OVERLAY_VAR(sRecycleBoxMsgFilePtr),
    HOST_OVERLAY_VAR(sRecycleBox),
    HOST_OVERLAY_VAR(RecycleBox_changeAct_tbl),
    HOST_OVERLAY_VAR(RecycleBox_changeAct_tbl_init),
    HOST_OVERLAY_VARS_END
};

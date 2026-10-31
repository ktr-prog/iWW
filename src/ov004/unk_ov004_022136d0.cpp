#include "types.h"
#include "proto/main/unk_020b4828.h"
#include "Unk_020d8c7c.h"
#include "gfx/DebugColor.h"
#include "actor/ActorProfile.h"
#include "gfx/VecFx32.h"
#include "talk/TalkWindowState.h"
#include "talk/MsgRequest.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "game/TouchPickSphere.h"
#include "game/TouchPicker.h"
#include "proto/ov004/unk_ov004_022136d0.h"








class TouchPicker;

extern "C" {
BOOL TalkRequest_SetTargetDone(void *p);
s32 Vec_DistXZ(s32 *a, s32 *b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
u32 Scene_GetCurrent();
}

class RoomBoardSign : public Character, public TalkMsgRequest {
public:
    RoomBoardSign();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~RoomBoardSign();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);

    void mainAct02();
    BOOL setupAct02();
    void mainAct01();
    BOOL setupAct01();
    void mainAct00();
    BOOL setupAct00();
    void execAct();
    BOOL changeAct(s32 m);
    BOOL unregisterSelf();
    BOOL registerSelf();

    /* 0x130 */ s32 act;
    /* 0x134 */ alignas(TouchPickSphere) u8 touchSphere[sizeof(TouchPickSphere)];
    /* 0x150 */ u8 index;
    /* 0x151 */ u8 pad_151;
    /* 0x152 */ s16 signMsgIndex;
    /* 0x154 */ s32 radius;
};

typedef void (RoomBoardSign::*Unk_022137c4_Fn)();
typedef BOOL (RoomBoardSign::*Unk_02213840_Fn)();




extern "C" s16 sRoomBoardSignSpawnMsg;
extern "C" u8 sRoomBoardSignCount;
extern "C" DebugColor data_ov004_02250174;
extern "C" DebugColor data_ov004_02250180;
extern "C" DebugColor data_ov004_0225017c(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov004_02250184(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov004_02250188(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov004_02250170(0x14, 0x1f, 0x14, 0x1f);
extern "C" {
void *sRoomBoardSigns[0x40];
}
extern "C" ActorProfile sRoomBoardSignProfile = { (void *(*)())RoomBoardSign_Create, 0x17, 0x1c, 0, 0xc8000, 0x12c000, 0x258000 };
extern "C" {
s32 sRoomBoardSignSpawnRadius;
}

struct BoardSignStackPad {
    s32 v[2];
    BoardSignStackPad() {}
    ~BoardSignStackPad() {}
};

extern "C" RoomBoardSign *RoomBoardSign_Create() {
    return new RoomBoardSign;
}

RoomBoardSign::RoomBoardSign() {
    new ((TouchPickSphere *)touchSphere) TouchPickSphere();
}

RoomBoardSign::~RoomBoardSign() {
    ((TouchPickSphere *)((void *)((TouchPickSphere *)touchSphere)))->~TouchPickSphere();
}

BOOL RoomBoardSign::onCreate() {
    RoomBoardSign_ClearRegistry();
    signMsgIndex = sRoomBoardSignSpawnMsg;
    radius = sRoomBoardSignSpawnRadius;
    if (registerSelf()) {
        u32 t = Scene_GetCurrent();
        setCharId((u16)(index | (t << 8)));
        changeAct(0);
        return TRUE;
    }
    return FALSE;
}

BOOL RoomBoardSign::onExecute() {
    execAct();
    Scene_GetTouchPicker()->addSphere((TouchPickSphere *)touchSphere, (VecFx32 *)(&position), radius, 0x10, index);
    return TRUE;
}

BOOL RoomBoardSign::onDraw() {
    return TRUE;
}

BOOL RoomBoardSign::onDelete() {
    unregisterSelf();
    return TRUE;
}

extern "C" void RoomBoardSign_ClearRegistry() {
    if (sRoomBoardSignCount == 0) {
        u32 i;
        for (i = 0; i < 0x40; i++) {
            sRoomBoardSigns[i] = 0;
        }
    }
}

BOOL RoomBoardSign::registerSelf() {
    index = sRoomBoardSignCount;
    u32 i = index;
    if (i < 0x40) {
        sRoomBoardSigns[i] = this;
        sRoomBoardSignCount++;
        return TRUE;
    }
    return FALSE;
}

BOOL RoomBoardSign::unregisterSelf() {
    u32 i = index;
    if (i < 0x40) {
        sRoomBoardSigns[i] = 0;
        sRoomBoardSignCount--;
        index = 0xff;
        return TRUE;
    }
    return FALSE;
}

BOOL RoomBoardSign::acceptsInteraction(void *a) {
    Character *o = (Character *)a;
    s32 lim = radius + 0x2ccd;
    if (o) {
        if (Vec_DistXZ(&o->position.x, &position.x) < lim) {
            if (Math_AngleDiffAbs((s16)(rotY + 0x8000), o->rotY) < 0x1300) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void RoomBoardSign::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL RoomBoardSign::changeAct(s32 m) {
    static Unk_02213840_Fn tbl[3] = { (Unk_02213840_Fn)&RoomBoardSign::setupAct00, (Unk_02213840_Fn)&RoomBoardSign::setupAct01, (Unk_02213840_Fn)&RoomBoardSign::setupAct02 };
    if (m < 3) {
        if ((this->*tbl[m])()) {
            act = m;
            return TRUE;
        }
    }
    return FALSE;
}

void RoomBoardSign::execAct() {
    static Unk_022137c4_Fn tbl[3] = { &RoomBoardSign::mainAct00, &RoomBoardSign::mainAct01, &RoomBoardSign::mainAct02 };
    if (act < 3) {
        (this->*tbl[act])();
    }
}

extern "C" s16 sRoomBoardSignSpawnMsg = -1;
extern "C" DebugColor data_ov004_02250180(0x14, 0x1f, 0x1f, 0x1f);
extern "C" {
u8 sRoomBoardSignCount;
}
extern "C" DebugColor data_ov004_02250174(0x14, 0x18, 0x18, 0x1f);

BOOL RoomBoardSign::setupAct00() {
    return TRUE;
}

void RoomBoardSign::mainAct00() {}

BOOL RoomBoardSign::setupAct01() {
    BoardSignStackPad pad;
    ((Character *)(this))->attachTalkRequest(this);
    setFileName("obj_etc_board");
    msgIndex = signMsgIndex;
    window->nextState = 1;
    return TRUE;
}

void RoomBoardSign::mainAct01() {
    if (window) {
        if (window->state) {
            changeAct(2);
        }
    }
}

BOOL RoomBoardSign::setupAct02() {
    return TRUE;
}

void RoomBoardSign::mainAct02() {
    if (window) {
        if (window->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

extern "C" void *RoomBoardSign_GetByIndex(s32 i) {
    if (i >= 0 && (u32)i < 0x40) {
        return sRoomBoardSigns[i];
    }
    return 0;
}

extern "C" void RoomBoardSign_Spawn(void *a, s32 b, s32 c, s32 d) {
    u16 loc[3];
    sRoomBoardSignSpawnMsg = d;
    sRoomBoardSignSpawnRadius = b;
    loc[0] = 0;
    loc[1] = c;
    loc[2] = 0;
    Actor::spawn(0x17, 0, a, loc, 0);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_022136d0) {
    HOST_OVERLAY_VAR(data_ov004_0225017c),
    HOST_OVERLAY_VAR(data_ov004_02250184),
    HOST_OVERLAY_VAR(data_ov004_02250188),
    HOST_OVERLAY_VAR(data_ov004_02250170),
    HOST_OVERLAY_VAR(sRoomBoardSigns),
    HOST_OVERLAY_VAR(sRoomBoardSignProfile),
    HOST_OVERLAY_VAR(sRoomBoardSignSpawnRadius),
    HOST_OVERLAY_VAR(sRoomBoardSignSpawnMsg),
    HOST_OVERLAY_VAR(data_ov004_02250180),
    HOST_OVERLAY_VAR(sRoomBoardSignCount),
    HOST_OVERLAY_VAR(data_ov004_02250174),
    HOST_OVERLAY_VARS_END
};

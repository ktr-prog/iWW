#include "types.h"
#include "host_labels.h"
#include "proto/main/unk_020b4828.h"
#include "sys/StackPad.h"
#include "actor/ActorProfile.h"
#include "npc/VillagerId.h"
#include "save/VillagerData.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "game/TouchPickSphere.h"
#include "gfx/DebugColor.h"
#include "game/TouchPicker.h"
#include "proto/ov003/unk_ov003_022048c0.h"












struct TouchPicker;

extern "C" {
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
u8 *SaveVillagers_Get(u8 *p, s32 i);
BOOL TalkRequest_SetTargetDone(void *p);
s32 Vec_DistXZ(s32 *a, s32 *b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
}

class VillagerBoard;

class VillagerBoard : public Character, public TalkMsgRequest {
public:
    VillagerBoard();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~VillagerBoard();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);

    void mainReadEnd();
    BOOL setupReadEnd();
    void mainRead();
    BOOL setupRead();
    void mainIdle();
    BOOL setupIdle();
    void runAct();
    BOOL changeAct(s32 m);

    /* 0x130 */ s32 act;
    /* 0x134 */ alignas(TouchPickSphere) u8 touchSphere[sizeof(TouchPickSphere)];
};

typedef void (VillagerBoard::*Unk_022049a8_Fn)();
typedef BOOL (VillagerBoard::*Unk_02204a24_Fn)();


extern "C" VillagerBoard *sVillagerBoards[8];

extern "C" DebugColor data_ov003_02234f80(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov003_02234f64(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov003_02234f68(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov003_02234f70(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov003_02234f6c(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov003_02234f74(0x14, 0x18, 0x18, 0x1f);
extern "C" {
u8 sVillagerBoardCount;
}

extern "C" VillagerBoard *VillagerBoard_Create() {
    return new VillagerBoard;
}

VillagerBoard::VillagerBoard() {
    new ((TouchPickSphere *)touchSphere) TouchPickSphere();
}

VillagerBoard::~VillagerBoard() {
    ((TouchPickSphere *)((void *)((TouchPickSphere *)touchSphere)))->~TouchPickSphere();
}

BOOL VillagerBoard::onCreate() {
    VillagerBoard_ResetTable();
    setCharId((u16)param);
    changeAct(0);
    sVillagerBoards[param] = this;
    sVillagerBoardCount++;
    return TRUE;
}

BOOL VillagerBoard::onExecute() {
    runAct();
    Scene_GetTouchPicker()->addSphere((TouchPickSphere *)touchSphere, (VecFx32 *)(void *)(&position.x), 0xc00, 9, param);
    return TRUE;
}

BOOL VillagerBoard::onDraw() {
    return TRUE;
}

BOOL VillagerBoard::onDelete() {
    sVillagerBoards[param] = 0;
    sVillagerBoardCount--;
    return TRUE;
}

extern "C" void VillagerBoard_ResetTable() {
    if (sVillagerBoardCount == 0) {
        u32 i;
        for (i = 0; i < 8; i++) {
            sVillagerBoards[i] = 0;
        }
    }
}

BOOL VillagerBoard::acceptsInteraction(void *a) {
    clearTalkStartMode();
    Character *o = (Character *)a;
    if (o) {
        if (Vec_DistXZ(&o->position.x, &position.x) < 0x2333) {
            if (Math_AngleDiffAbs(-0x8000, o->rotY) <= 0x1100) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void VillagerBoard::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
        changeAct(1);
        break;
    case 8:
        changeAct(0);
        break;
    }
}

BOOL VillagerBoard::changeAct(s32 m) {
    static Unk_02204a24_Fn tbl[3] = { (Unk_02204a24_Fn)&VillagerBoard::setupIdle, (Unk_02204a24_Fn)&VillagerBoard::setupRead, (Unk_02204a24_Fn)&VillagerBoard::setupReadEnd };
    if (m < 3) {
        if ((this->*tbl[m])()) {
            act = m;
            return TRUE;
        }
    }
    return FALSE;
}

void VillagerBoard::runAct() {
    static Unk_022049a8_Fn tbl[3] = { &VillagerBoard::mainIdle, &VillagerBoard::mainRead, &VillagerBoard::mainReadEnd };
    if (act < 3) {
        (this->*tbl[act])();
    }
}

extern "C" ActorProfile sVillagerBoardProfile = {(void *(*)())VillagerBoard_Create, 0x18, 0x1d, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" {
VillagerBoard *sVillagerBoards[8];
}

BOOL VillagerBoard::setupIdle() {
    return TRUE;
}

void VillagerBoard::mainIdle() {}

BOOL VillagerBoard::setupRead() {
    StackPad4 pad;
    ((Character *)(this))->attachTalkRequest(this);
    setFileName("obj_etc_board");
    msgIndex = 0;
    ((TalkWindowState *)window)->nextState = 1;
    MsgString9B buf;
    ((VillagerData *)SaveVillagers_Get(gSaveVillagers, param))->getVillagerId()->getName(&buf);
    ((TalkWindowState *)window)->setSlot(0, &buf);
    return TRUE;
}

void VillagerBoard::mainRead() {
    if (window) {
        if (((TalkWindowState *)window)->state) {
            changeAct(2);
        }
    }
}

BOOL VillagerBoard::setupReadEnd() {
    return TRUE;
}

void VillagerBoard::mainReadEnd() {
    if (window) {
        if (((TalkWindowState *)window)->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}

extern "C" VillagerBoard *VillagerBoard_Get(s32 i) {
    if (i >= 0 && i < 8) {
        return sVillagerBoards[i];
    }
    return 0;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_022048c0) {
    HOST_OVERLAY_VAR(data_ov003_02234f80),
    HOST_OVERLAY_VAR(data_ov003_02234f64),
    HOST_OVERLAY_VAR(data_ov003_02234f68),
    HOST_OVERLAY_VAR(data_ov003_02234f70),
    HOST_OVERLAY_VAR(data_ov003_02234f6c),
    HOST_OVERLAY_VAR(data_ov003_02234f74),
    HOST_OVERLAY_VAR(sVillagerBoardCount),
    HOST_OVERLAY_VAR(sVillagerBoardProfile),
    HOST_OVERLAY_VAR(sVillagerBoards),
    HOST_OVERLAY_VARS_END
};

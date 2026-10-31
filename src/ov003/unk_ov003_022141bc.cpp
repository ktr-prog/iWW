#include "types.h"
#include "host_overlay_vars.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "gfx/DebugColor.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/ov003/unk_ov003_022141bc.h"













extern "C" {
BOOL TalkRequest_SetTargetDone(void *p);
s32 Math_AngleDiffAbs(s32 a, s32 b);
}

class BulletinBoard : public BuildingActor {
public:
    BulletinBoard();
    virtual ~BulletinBoard();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL acceptsInteraction(void *a);
    virtual void onInteractionEvent(u32 a, u8 b);
    virtual BOOL initBuilding();

    void updateBoardState();
    BOOL setBoardState(s32 m);
    void execBoardRead();
    BOOL enterBoardRead();
    BOOL execBoardOpen();
    BOOL enterBoardOpen();
    void execBoardIdle();
    BOOL enterBoardIdle();

    /* 0x2b0 */ s32 boardState;
};


typedef void (BulletinBoard::*Unk_02214208_Fn)();
typedef BOOL (BulletinBoard::*Unk_02214284_Fn)();

extern "C" DebugColor data_ov003_02235110(0x1f, 0x14, 0x14, 0x1f);
extern "C" DebugColor data_ov003_02235100(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov003_02235104(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov003_022350fc(0x14, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov003_022350f8(0x14, 0x1f, 0x1f, 0x1f);
extern "C" DebugColor data_ov003_022350f4(0x14, 0x18, 0x18, 0x1f);
extern "C" ActorProfile sBulletinBoardProfile = {(void *(*)())BulletinBoard_Create, 0x22, 0x28, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" void *BulletinBoard_Create() {
    return new BulletinBoard;
}

BulletinBoard::BulletinBoard() {}

BulletinBoard::~BulletinBoard() {}

BOOL BulletinBoard::initBuilding() {
    setBoardState(0);
    return TRUE;
}

BOOL BulletinBoard::onExecute() {
    updateBoardState();
    return TRUE;
}

BOOL BulletinBoard::onDraw() {
    return TRUE;
}

BOOL BulletinBoard::onDelete() {
    return TRUE;
}

BOOL BulletinBoard::acceptsInteraction(void *other) {
    Character *a = (Character *)other;
    if (colliderFlags & 8) {
        if (a) {
            if (Math_AngleDiffAbs((s16)(rotY + 0x8000), a->rotY) < 0x1300) {
                clearTalkStartMode();
                return TRUE;
            }
        }
    }
    return FALSE;
}

void BulletinBoard::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
    case 1:
        setBoardState(1);
        break;
    case 8:
        setBoardState(0);
        break;
    }
}

BOOL BulletinBoard::setBoardState(s32 m) {
    static Unk_02214284_Fn tbl[3] = { &BulletinBoard::enterBoardIdle, &BulletinBoard::enterBoardOpen, &BulletinBoard::enterBoardRead };
    if (m < 3) {
        if ((this->*tbl[m])()) {
            boardState = m;
            return TRUE;
        }
    }
    return FALSE;
}

Unk_02214208_Fn BulletinBoard_updateBoardState_tbl[3];
u8 BulletinBoard_updateBoardState_tbl_init;
void BulletinBoard::updateBoardState() {
    if (!BulletinBoard_updateBoardState_tbl_init) {
        HOST_STATIC_INIT_ARRAY(BulletinBoard_updateBoardState_tbl, { (Unk_02214208_Fn)&BulletinBoard::execBoardIdle, (Unk_02214208_Fn)&BulletinBoard::execBoardOpen, (Unk_02214208_Fn)&BulletinBoard::execBoardRead });
        BulletinBoard_updateBoardState_tbl_init = 1;
    }
    if (boardState < 3) {
        (this->*BulletinBoard_updateBoardState_tbl[boardState])();
    }
}

BOOL BulletinBoard::enterBoardIdle() {
    return TRUE;
}

void BulletinBoard::execBoardIdle() {}

BOOL BulletinBoard::enterBoardOpen() {
    if (MenuCtrl_OpenLauncher(0)) {
        return TRUE;
    }
    return FALSE;
}

BOOL BulletinBoard::execBoardOpen() {
    return setBoardState(2);
}

BOOL BulletinBoard::enterBoardRead() {
    return TRUE;
}

void BulletinBoard::execBoardRead() {
    if (MenuCtrl_IsFinished()) {
        TalkRequest_SetTargetDone(this);
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_022141bc) {
    HOST_OVERLAY_VAR(data_ov003_02235110),
    HOST_OVERLAY_VAR(data_ov003_02235100),
    HOST_OVERLAY_VAR(data_ov003_02235104),
    HOST_OVERLAY_VAR(data_ov003_022350fc),
    HOST_OVERLAY_VAR(data_ov003_022350f8),
    HOST_OVERLAY_VAR(data_ov003_022350f4),
    HOST_OVERLAY_VAR(sBulletinBoardProfile),
    HOST_OVERLAY_VAR(BulletinBoard_updateBoardState_tbl),
    HOST_OVERLAY_VAR(BulletinBoard_updateBoardState_tbl_init),
    HOST_OVERLAY_VARS_END
};

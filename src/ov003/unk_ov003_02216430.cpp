#include "types.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/Model.h"
#include "gfx/G3dResAccess.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "gfx/NNSG3dRS.h"
#include "proto/ov003/unk_ov003_02216430.h"
















extern "C" {
}

extern "C" void TownHall_NodeCallback(NNSG3dRS *a);
extern "C" void JointCb_RotateClockHourHand(NNSG3dRS *rs);
extern "C" void JointCb_RotateClockMinuteHand(NNSG3dRS *rs);

class TownHall : public BuildingActor {
public:
    TownHall();
    virtual ~TownHall();

    virtual void onJointCalcPost(u32 a, void *p);
    virtual BOOL initBuilding();
    virtual BOOL playsDoorMelody();

    /* 0x2b0 */ s8 hourHandNode;
    /* 0x2b1 */ s8 minuteHandNode;
    /* 0x2b2 */ u8 pad_2b2[2];
};


extern "C" ActorProfile sTownHallProfile = { (void *(*)())TownHall_Create, 0x1e, 0x24, 0, 0xc8000, 0x12c000, 0x258000 };

extern "C" void *TownHall_Create() {
    return new TownHall();
}

extern "C" void TownHall_NodeCallback(NNSG3dRS *a) {
    BuildingActor *o = (BuildingActor *)a->pRenderObj->ptrUser;
    if (o) {
        o->onJointCalcPost(a->c[1], a);
    }
}

TownHall::TownHall() {
    minuteHandNode = -1;
    hourHandNode = minuteHandNode;
}

TownHall::~TownHall() {
}

BOOL TownHall::initBuilding() {
    hourHandNode = ((G3dResAccess *)model.resMdl)->findNodeIdx("kh_j");
    minuteHandNode = ((G3dResAccess *)model.resMdl)->findNodeIdx("km_j");
    if (hourHandNode != -1 && minuteHandNode != -1) {
        model.setCallback(TownHall_NodeCallback, 6, 2, this, 0);
    }
    return TRUE;
}

void TownHall::onJointCalcPost(u32 a, void *p) {
    if ((s32)a == hourHandNode) {
        JointCb_RotateClockHourHand((NNSG3dRS *)p);
    } else if ((s32)a == minuteHandNode) {
        JointCb_RotateClockMinuteHand((NNSG3dRS *)p);
    }
}

BOOL TownHall::playsDoorMelody() {
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02216430) {
    HOST_OVERLAY_VAR(sTownHallProfile),
    HOST_OVERLAY_VARS_END
};

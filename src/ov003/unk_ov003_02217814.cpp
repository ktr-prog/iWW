#include "types.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "proto/main/unk_02082d74.h"
#include "proto/ov003/unk_ov003_02217814.h"

extern "C" {
s32 Scene_GetCurrent();
}

class GulliverShip : public BuildingActor {
public:
    GulliverShip();
    virtual ~GulliverShip();

    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL initBuilding();
};

extern "C" void *GulliverShip_Create() {
    return new GulliverShip;
}

GulliverShip::GulliverShip() {
}

GulliverShip::~GulliverShip() {
}

BOOL GulliverShip::initBuilding() {
    Visitor_ScheduleLow(&sGulliverShipVisitorProfile, Scene_GetCurrent(), &position);
    return TRUE;
}

BOOL GulliverShip::onExecute() {
    return TRUE;
}

BOOL GulliverShip::onDraw() {
    return TRUE;
}

BOOL GulliverShip::onDelete() {
    return TRUE;
}

extern "C" u16 sGulliverShipVisitorProfile = 0x60;
extern "C" ActorProfile sGulliverShipProfile = {(void *(*)())GulliverShip_Create, 0x27, 0x2d, 0, 0xc8000, 0x12c000, 0x258000};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02217814) {
    HOST_OVERLAY_VAR(sGulliverShipVisitorProfile),
    HOST_OVERLAY_VAR(sGulliverShipProfile),
    HOST_OVERLAY_VARS_END
};

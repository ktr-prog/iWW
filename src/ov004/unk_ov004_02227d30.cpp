#include "types.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "gfx/CachedModel.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "room/RoomObjActor.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/ov004/unk_ov004_02227d30.h"

class BarberPole : public RoomObjActor {
public:
    BarberPole();
    virtual ~BarberPole();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
};

extern "C" ActorProfile sBarberPoleProfile = {(void *(*)())BarberPole_Create, 0x16, 0x1a, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" BarberPole *BarberPole_Create() {
    return new BarberPole();
}

BarberPole::BarberPole() {}

BarberPole::~BarberPole() {}

BOOL BarberPole::onCreate() {
    loadResourcesByName("obj_b_pole");
    if (RoomObjRes_GetBca(&res, 0) != 0) {
        if (model.allocAnmObj(gBgHeap) != 0) {
            ((BlendAnimModel *)&model)->initAnim(RoomObjRes_GetBca(&res, 0), 0, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    return TRUE;
}

BOOL BarberPole::onExecute() {
    model.stepAnim();
    return TRUE;
}

BOOL BarberPole::onDraw() {
    model.drawAnimated(0);
    return TRUE;
}

BOOL BarberPole::onDelete() {
    releaseResources();
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02227d30) {
    HOST_OVERLAY_VAR(sBarberPoleProfile),
    HOST_OVERLAY_VARS_END
};

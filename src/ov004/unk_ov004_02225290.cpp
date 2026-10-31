#include "types.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "actor/CharacterListNode.h"
#include "gfx/AnimFrameCtrl.h"
#include "room/RoomObjRes.h"
#include "room/RoomObjTex.h"
#include "game/BoxCollider.h"
#include "gfx/CachedModel.h"
#include "talk/MsgRequest.h"
#include "gfx/AnimModel.h"
#include "talk/TalkMsgRequest.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "room/RoomObjActor.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0209c3e0.h"
#include "proto/ov004/unk_ov004_02225290.h"

class BarberMachine;

extern "C" {
BOOL BoxCollider_Unregister(BoxCollider *p);
BOOL BoxCollider_Register(BoxCollider *p, s32 a, s32 b, s32 c, VecFx32 *pos, s16 angle, VecFx32 *scale);
}

class BarberMachine : public RoomObjActor, public TalkMsgRequest {
public:
    BarberMachine();
    virtual ~BarberMachine();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL changeSyncState(u32 v);
    virtual void getSoundPos(VecFx32 *out);

    void removeCollision();
    void initCollision();
    void updateState03();
    void updateState02();
    void updateState01();
    void updateState00();
    void updateState();
    BOOL enterState03();
    BOOL enterState02();
    BOOL enterState01();
    BOOL enterState00();

    /* 0x2d4 */ BoxCollider collider;
    /* 0x370 */ u8 isStartedLocally;
};

typedef RoomObjActor M;
typedef VecFx32 Vec;


extern "C" ActorProfile sBarberMachineProfile;
extern "C" BarberMachine *volatile sBarberMachine;

struct BarberSoundStackPad {
    s32 v[4];
    BarberSoundStackPad() {}
    ~BarberSoundStackPad() {}
};

extern "C" BarberMachine *BarberMachine_Create() {
    return new BarberMachine;
}

BarberMachine::BarberMachine() {
}

BarberMachine::~BarberMachine() {
}

BOOL BarberMachine::onCreate() {
    sBarberMachine = this;
    isStartedLocally = 0;
    loadResources("/roomObj/obj_b_machine.arc", "/roomObj/obj_b_machine.nsbtx");
    initCollision();
    if (RoomObjRes_GetBca(&res, 0) != 0) {
        if (model.allocAnmObj(gBgHeap) != 0) {
            void *r = RoomObjRes_GetBca(&res, 0);
            ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    return TRUE;
}

BOOL BarberMachine::onExecute() {
    updateState();
    return TRUE;
}

BOOL BarberMachine::onDraw() {
    model.drawAnimated(0);
    return TRUE;
}

BOOL BarberMachine::onDelete() {
    removeCollision();
    releaseResources();
    sBarberMachine = 0;
    return TRUE;
}

void BarberMachine::getSoundPos(Vec *out) {
    BarberSoundStackPad pad;
    out->x = 0xc000;
    out->y = 0;
    out->z = 0x17000;
}

extern "C" ActorProfile sBarberMachineProfile = {(void *(*)())BarberMachine_Create, 0x15, 0x19, 0, 0xc8000, 0x12c000, 0x258000};

extern "C" BarberMachine *volatile sBarberMachine = 0;

BOOL BarberMachine::changeSyncState(u32 idx) {
    typedef BOOL (BarberMachine::*Fn)();
    static Fn tbl[4] = {&BarberMachine::enterState00, &BarberMachine::enterState01, &BarberMachine::enterState02,
                        &BarberMachine::enterState03};
    if (idx < 4) {
        if ((this->*tbl[idx])() != 0) {
            tex.syncState = idx;
            return TRUE;
        }
    }
    return FALSE;
}

void BarberMachine::updateState() {
    typedef void (BarberMachine::*Fn)();
    static Fn tbl[4] = {&BarberMachine::updateState00, &BarberMachine::updateState01, &BarberMachine::updateState02,
                        &BarberMachine::updateState03};
    u32 i = tex.syncState;
    if (i < 4) {
        (this->*tbl[i])();
    }
}

BOOL BarberMachine::enterState00() {
    void *r = RoomObjRes_GetBca(&res, 0);
    ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
    return TRUE;
}

void BarberMachine::updateState00() {
}

BOOL BarberMachine::enterState01() {
    void *r = RoomObjRes_GetBca(&res, 0);
    ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
    RoomObj_PlaySe(&se, 0x4d8);
    return TRUE;
}

void BarberMachine::updateState01() {
    if (model.isFinished() != 0) {
        if (isStartedLocally == 0) {
            changeSyncState(2);
        } else {
            RoomObjSync_ChangeState(this, 2);
        }
    } else {
        model.stepAnim();
    }
}

BOOL BarberMachine::enterState02() {
    void *r = RoomObjRes_GetBca(&res, 1);
    ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
    return TRUE;
}

void BarberMachine::updateState02() {
    if (model.isFinished() != 0) {
        if (isStartedLocally == 0) {
            changeSyncState(3);
        } else {
            RoomObjSync_ChangeState(this, 3);
        }
    } else {
        model.stepAnim();
    }
}

BOOL BarberMachine::enterState03() {
    void *r = RoomObjRes_GetBca(&res, 2);
    ((BlendAnimModel *)(&model))->initAnim(r, 1, 0x1000, 0, 0);
    RoomObj_PlaySe(&se, 0x4d9);
    isStartedLocally = 0;
    return TRUE;
}

void BarberMachine::updateState03() {
    if (model.isFinished() != 0) {
        changeSyncState(0);
    } else {
        model.stepAnim();
    }
}

void BarberMachine::initCollision() {
    BoxCollider_Register(&collider, 0x2000, 0x4000, 0x2000, &position, 0, NULL);
}

void BarberMachine::removeCollision() {
    BoxCollider_Unregister(&collider);
}

extern "C" void BarberMachine_Start() {
    if (RoomObjSync_ChangeState(sBarberMachine, 1) != 0) {
        sBarberMachine->isStartedLocally = 1;
    }
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02225290) {
    HOST_OVERLAY_VAR(sBarberMachineProfile),
    HOST_OVERLAY_VAR(sBarberMachine),
    HOST_OVERLAY_VARS_END
};

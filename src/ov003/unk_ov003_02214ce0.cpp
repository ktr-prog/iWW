#include "types.h"
#include "field/Unk_ov003_02214494_Views.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_02082d74.h"
#include "proto/ov003/unk_ov003_02214ce0.h"

extern "C" {
void Clock_GetDateTime(ClockDateTime *p);
void MI_CpuCopy8(void *, void *, s32);
s32 Event_GetState(u32, void *, u32);
s32 Scene_GetCurrent();
}

class GracieCar : public BuildingActor {
public:
    GracieCar();
    virtual ~GracieCar();
    virtual BOOL initBuilding();
};


extern "C" u16 sGracieCarVisitorProfile = 0x6c;
extern "C" ActorProfile sGracieCarProfile = { (void *(*)())GracieCar_Create, 0x29, 0x2f, 0, 0xc8000, 0x12c000, 0x258000 };

static inline BOOL Unk_ov003_02214ce0_Chk(void *m) {
    if (Event_GetState(0x40, m, 0)) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void *GracieCar_Create() {
    return new GracieCar;
}

GracieCar::GracieCar() {
}

GracieCar::~GracieCar() {
}

BOOL GracieCar::initBuilding() {
    ClockDateTimeWords l;
    ClockDateTime m;
    l.words[0] = 0;
    l.words[1] = 0;
    Clock_GetDateTime(&l.dt);
    MI_CpuCopy8(&l, &m, 8);
    if (Unk_ov003_02214ce0_Chk(&m)) {
        Visitor_ScheduleLow(&sGracieCarVisitorProfile, Scene_GetCurrent(), &position);
    }
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02214ce0) {
    HOST_OVERLAY_VAR(sGracieCarVisitorProfile),
    HOST_OVERLAY_VAR(sGracieCarProfile),
    HOST_OVERLAY_VARS_END
};

#include "types.h"
#include "sys/ClockDateTime.h"
#include "talk/MsgString9B.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "town/KatrinaTent.h"
#include "proto/ov003/unk_ov003_02215ad8.h"
















extern "C" {
void Clock_GetDateTime(void *p);
void Npc_GetName(void *p, void *q);
}



extern "C" ActorProfile sKatrinaTentProfile = { (void *(*)())KatrinaTent_Create, 0x28, 0x2e, 0, 0xc8000, 0x12c000, 0x258000 };

extern "C" void *KatrinaTent_Create() {
    return new KatrinaTent;
}

KatrinaTent::KatrinaTent() {
}

KatrinaTent::~KatrinaTent() {
}

BOOL KatrinaTent::initBuilding() {
    struct {
        s32 a, b;
    } d;
    d.a = 0;
    d.b = 0;
    Clock_GetDateTime(&d);
    createHour = *((u8 *)&d + 2);
    return TRUE;
}

BOOL KatrinaTent::onExecute() {
    return TRUE;
}

BOOL KatrinaTent::isOpen() {
    ClockDateTime t;
    ((u32 *)&t)[0] = 0;
    ((u32 *)&t)[1] = 0;
    Clock_GetDateTime(&t);
    BOOL r;
    if (t.hour >= 6) {
        if (createHour < 6) r = FALSE;
        else r = TRUE;
    } else {
        r = FALSE;
    }
    return r;
}

void KatrinaTent::setupTalkMsg() {
    setFileName("sp_npc_panther");
    if (isOpen() == 0) {
        msgIndex = 0xf;
    } else {
        msgIndex = 0x12;
    }
    MsgString9B name;
    u16 v[2];
    v[1] = 0xd00a;
    Npc_GetName(&name, &v[1]);
    setSpeakerName(name.data(), 1);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02215ad8) {
    HOST_OVERLAY_VAR(sKatrinaTentProfile),
    HOST_OVERLAY_VARS_END
};

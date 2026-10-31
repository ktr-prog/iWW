#include "types.h"
#include "host_labels.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "game/Unk_02095774_Ent.h"
#include "item/ItemName.h"
#include "proto/main/unk_020abea8.h"
#include "proto/ov003/unk_ov003_022173a4.h"
#include "proto/ov003/unk_ov003_022187fc.h"













extern "C" {
#define data_021ed150 HOST_LABEL(SaveTownStateView *, data_021ed150)

}


class TownSign : public BuildingActor {
public:
    TownSign();
    virtual ~TownSign();

    virtual BOOL onDraw();
    virtual BOOL initBuilding();
    virtual void setupTalkMsg();
    virtual BOOL isOpen();

    /* 0x2b0 */ u16 signIndex;
    /* 0x2b2 */ u16 pad_2b2;
};

extern "C" void *TownSign_Create() {
    return new TownSign;
}

TownSign::TownSign() {
}

TownSign::~TownSign() {
}

BOOL TownSign::initBuilding() {
    signIndex = Field_GetSpawnedKind1Count();
    return TRUE;
}

BOOL TownSign::onDraw() {
    ObjShadow_DrawSign(&position);
    return TRUE;
}

void TownSign::setupTalkMsg() {
    u16 v[2];
    setFileName("obj_etc_board");
    msgIndex = signIndex % 14 + 1;
    u16 w;
    if (data_021ed150.nativeFruit < 5) {
        w = data_021ed150.nativeFruit + 0x1518;
    } else {
        w = 0x1518;
    }
    v[1] = w;
    ItemName obj(&v[1]);
    window->setSlot(1, &obj);
}

BOOL TownSign::isOpen() {
    return FALSE;
}

extern "C" ActorProfile sTownSignProfile = {(void *(*)())TownSign_Create, 0x20, 0x26, 0, 0xc8000, 0x12c000, 0x258000};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_022173a4) {
    HOST_OVERLAY_VAR(sTownSignProfile),
    HOST_OVERLAY_VARS_END
};

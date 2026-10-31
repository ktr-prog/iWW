#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "room/HouseData.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02097444.h"
#include "proto/ov003/unk_ov003_022165d0.h"
#include "proto/ov003/unk_ov003_022187fc.h"

extern "C" {
#define gSaveHouse HOST_LABEL(HouseData *, gSaveHouse)
extern const s8 sHexDigits[];

void *NNS_G3dGetTex(void *p);
BOOL Gfx3d_LoadTex(void *p, u32 a);
void *Gfx3d_CopyTex(void *p, void *a);
void NNS_G3dBindMdlTex(void *a, void *b);
void NNS_G3dBindMdlPltt(void *a, void *b);

}

class PlayerHouse : public BuildingActor {
public:
    PlayerHouse();
    virtual ~PlayerHouse();
    virtual BOOL onDraw();
    virtual BOOL initBuilding();
    virtual BOOL isOpen();
    virtual BOOL usesDoorApproach();
    virtual BOOL playsDoorMelody();
    virtual BOOL areLightsOn();

    void bindHouseTex();
    void loadHouseTex();

    /* 0x2b0 */ void *roofTex;
    /* 0x2b4 */ void *extraTex;
};


extern "C" const s8 sHexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
extern "C" ActorProfile sPlayerHouseProfile = { (void *(*)())PlayerHouse_Create, 0x1f, 0x25, 0, 0xc8000, 0x12c000, 0x258000 };
extern "C" {
char data_ov003_02235358[0x20];
}

extern "C" void *PlayerHouse_Create() {
    return new PlayerHouse();
}

PlayerHouse::PlayerHouse() {}

PlayerHouse::~PlayerHouse() {}

BOOL PlayerHouse::initBuilding() {
    VecFx32 v;
    s16 ang;
    loadHouseTex();
    bindHouseTex();
    if (getDoorPos(&v, &ang)) {
        v.x -= 0x2000;
        v.z += 0x1000;
        Actor::spawn(0x24, 0x501d, &v, NULL, NULL);
    }
    return TRUE;
}

BOOL PlayerHouse::onDraw() {
    BuildingActor *o = BuildingList_FindByItem(0x501d);
    if (o) {
        o->updateMatrix();
    }
    return TRUE;
}

extern "C" u8 PlayerHouse_GetTexIndex() { return gSaveHouse.getRoofColor(); }

extern "C" char *PlayerHouse_GetTexPath() {
    u32 i = PlayerHouse_GetTexIndex();
    u32 c = Field_GetStructureTexSuffix();
    Str_SPrintf(data_ov003_02235358, "/str/plHsTex/home%c%c.nsbtx", sHexDigits[i & 0xf], c);
    return data_ov003_02235358;
}

void PlayerHouse::loadHouseTex() {
    void *r4 = File_LoadAlloc(PlayerHouse_GetTexPath(), gCurrentHeap, -4, 0);
    roofTex = NNS_G3dGetTex(r4);
    if (Gfx3d_LoadTex(roofTex, 0)) {
        roofTex = Gfx3d_CopyTex(roofTex, gFieldStructureHeap);
    }
    Mem_Free(r4);
}

void PlayerHouse::bindHouseTex() {
    if (roofTex) {
        NNS_G3dBindMdlTex(model.resMdl, roofTex);
    }
    if (extraTex) {
        NNS_G3dBindMdlTex(model.resMdl, extraTex);
        NNS_G3dBindMdlPltt(model.resMdl, extraTex);
    }
}

BOOL PlayerHouse::usesDoorApproach() {
    if (PlayerData_IsResidentIndex(PlayerData_GetCurrentIndex()) == 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL PlayerHouse::areLightsOn() { return gSaveHouse.hasRoomFlags(); }

BOOL PlayerHouse::isOpen() { return TRUE; }

BOOL PlayerHouse::playsDoorMelody() { return TRUE; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_022165d0) {
    HOST_OVERLAY_VAR(sPlayerHouseProfile),
    HOST_OVERLAY_VAR(data_ov003_02235358),
    HOST_OVERLAY_VARS_END
};

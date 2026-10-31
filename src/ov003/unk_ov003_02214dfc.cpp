#include "types.h"
#include "host_labels.h"
#include "actor/ActorProfile.h"
#include "talk/TalkWindowState.h"
#include "sys/ProcBase.h"
#include "gfx/MatTexVramTask.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "gfx/AnimModel.h"
#include "town/TownFlag.h"
#include "proto/main/unk_0203c638.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_02214dfc.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/main/unk_0204cc1c.h"

struct GateHouseFlagTexture {
    GateHouseFlagTexture();
    ~GateHouseFlagTexture();
    BOOL apply(void *res, void *b);
    void cancelUpload();

    /* 0x00 */ MatTexVramTask vramTask;
    /* 0x28 */ u32 clothTex[0x2c4 / 4];
};

extern "C" {
#define gSaveTownFlag HOST_LABEL(TownStyleRecordView *, gSaveTownFlag)
BOOL Ground_SetQuadrantsBlocked(s32, s32, s32);
}

class GateHouse : public BuildingActor {
public:
    GateHouse();
    virtual ~GateHouse();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL initBuilding();
    virtual BOOL alignsPlayerToDoor();
    virtual char *getArcPath();
    virtual char *getTexPath();
    virtual char *getLightTexPath();

    /* 0x2b0 */ GateHouseFlagTexture flagTexture;
};


extern "C" {
char data_ov003_02235228[0x24];
char data_ov003_0223524c[0x24];
char data_ov003_02235204[0x24];
}

extern "C" ActorProfile sGateHouseProfile;
extern "C" char data_ov003_022312a4[12];
extern "C" char *sGateHouseModelNames[3];
extern "C" char data_ov003_022312b0[12];
extern "C" char data_ov003_022312bc[12];

extern "C" void *GateHouse_Create() {
    return new GateHouse;
}

GateHouse::GateHouse() {
}

GateHouse::~GateHouse() {
}

BOOL GateHouse::initBuilding() {
    void *t = model.resMdl;
    flagTexture.apply(t, TownFlag_GetPattern(gSaveTownFlag.getTownFlag()));
    s32 x;
    s32 y;
    FieldPos_ToUnit(&x, &y, &position);
    s32 i;
    for (i = -2; i <= 2; i++) {
        Ground_SetQuadrantsBlocked(x + i, y - 1, 0xf);
    }
    return TRUE;
}

BOOL GateHouse::onExecute() {
    model.stepAnim();
    return TRUE;
}

BOOL GateHouse::onDraw() {
    return TRUE;
}

BOOL GateHouse::onDelete() {
    flagTexture.cancelUpload();
    return TRUE;
}

extern "C" s32 GateHouse_GetDesign() {
    return ((TownFlag *)gSaveTownFlag.getTownFlag())->getGateDesign();
}

extern "C" char *GateHouse_GetModelName() {
    return sGateHouseModelNames[GateHouse_GetDesign()];
}

extern "C" ActorProfile sGateHouseProfile = { (void *(*)())GateHouse_Create, 0x1c, 0x22, 0, 0xc8000, 0x12c000, 0x258000 };

char *GateHouse::getArcPath() {
    char *x = GateHouse_GetModelName();
    s32 y = Field_GetStructureTexSuffix();
    Str_SPrintf(data_ov003_02235228, "/str/chkp/%s%c.arc", x, y);
    return data_ov003_02235228;
}

char *GateHouse::getTexPath() {
    char *x = GateHouse_GetModelName();
    s32 y = Field_GetStructureTexSuffix();
    Str_SPrintf(data_ov003_02235204, "/str/chkp/%s%c.nsbtx", x, y);
    return data_ov003_02235204;
}

char *GateHouse::getLightTexPath() {
    char *x = GateHouse_GetModelName();
    s32 y = Field_GetStructureTexSuffix();
    Str_SPrintf(data_ov003_0223524c, "/str/chkp/%s%c_lt.nsbtx", x, y);
    return data_ov003_0223524c;
}

BOOL GateHouse::alignsPlayerToDoor() {
    return FALSE;
}

extern "C" BOOL GateHouse_ApplyTownFlag(GateHouse *self) {
    void *t = self->model.resMdl;
    self->flagTexture.apply(t, TownFlag_GetPattern(gSaveTownFlag.getTownFlag()));
    return TRUE;
}

GateHouseFlagTexture::GateHouseFlagTexture() {
    ClothTex_Construct();
}

GateHouseFlagTexture::~GateHouseFlagTexture() {
    ClothTex_Destruct();
}

BOOL GateHouseFlagTexture::apply(void *res, void *b) {
    if (ClothTex_LoadPattern(clothTex, b)) {
        if (vramTask.request(res, "w", ClothTex_GetTex(clothTex), 0, 0)) {
            TownFlag_SetPattern(gSaveTownFlag.getTownFlag(), b);
            return TRUE;
        }
    }
    return FALSE;
}

void GateHouseFlagTexture::cancelUpload() {
    vramTask.cancel();
}

extern "C" char *sGateHouseModelNames[3] = { data_ov003_022312bc, data_ov003_022312b0, data_ov003_022312a4 };
extern "C" char data_ov003_022312a4[12] = "obj_check2";
extern "C" char data_ov003_022312b0[12] = "obj_check1";
extern "C" char data_ov003_022312bc[12] = "obj_check0";

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02214dfc) {
    HOST_OVERLAY_VAR(data_ov003_02235228),
    HOST_OVERLAY_VAR(data_ov003_0223524c),
    HOST_OVERLAY_VAR(data_ov003_02235204),
    HOST_OVERLAY_VAR(sGateHouseProfile),
    HOST_OVERLAY_VAR(sGateHouseModelNames),
    HOST_OVERLAY_VAR(data_ov003_022312a4),
    HOST_OVERLAY_VAR(data_ov003_022312b0),
    HOST_OVERLAY_VAR(data_ov003_022312bc),
    HOST_OVERLAY_VARS_END
};

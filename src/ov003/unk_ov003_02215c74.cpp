#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "actor/ActorProfile.h"
#include "gfx/AnimFrameCtrl.h"
#include "talk/TalkWindowState.h"
#include "game/FxVec3.h"
#include "sys/ProcBase.h"
#include "gfx/ModelAnim.h"
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "town/BuildingActor.h"
#include "gfx/Model.h"
#include "net/CommManager.h"
#include "npc/VillagerId.h"
#include "npc/VillagerData.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_02003008.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov003/unk_ov003_02215c74.h"
#include "proto/ov003/unk_ov003_022187fc.h"

extern "C" {
#define gSaveVillagers HOST_LABEL(SaveVillagers *, gSaveVillagers)
extern CommManager *gCommManager;
extern const u8 sVillagerHouseClosedMsgs[];
extern const u8 sVillagerHouseClosedMsgsAlt[];

BOOL Building_IsNight();
u8 *SaveVillagers_Get(u8 *base, s32 idx);
BOOL Villager_IsHouseAvailable();
s32 Villager_GetWhereabouts(VillagerData *a);
s32 SceneId_GetVillagerHouse(u32 a);

void NNS_G3dBindMdlTex(void *a, void *b);
void NNS_G3dBindMdlPltt(void *a, void *b);
}

static inline VillagerData *SaveVillager(s32 idx) {
    return (VillagerData *)SaveVillagers_Get((u8 *)&gSaveVillagers, idx);
}

static inline s32 Unk_ov003_02215c7c_Idx(BuildingActor *o) {
    BOOL r = FALSE;
    u16 v = o->itemId;
    if (v < 0x5001 || v > 0x5008) {
    } else {
        r = TRUE;
    }
    if (r) {
        return v - 0x5001;
    }
    return -1;
}

struct VillagerHouseStyleBits {
    u8 f : 5;
};


class VillagerHouse : public BuildingActor {
public:
    VillagerHouse();
    virtual ~VillagerHouse();

    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual void *getDoorInAnim();
    virtual void *getDoorOutAnim();
    virtual BOOL initBuilding();
    virtual void setupTalkMsg();
    virtual BOOL isOpen();
    virtual BOOL usesDoorApproach();
    virtual BOOL playsDoorMelody();
    virtual BOOL areLightsOn();
    virtual char *getArcPath();
    virtual char *getTexPath();
    virtual char *getLightTexPath();

    char *getModelName();
    u8 getHouseVariant();
    s32 getHouseStyle();

    /* 0x2b0 */ AnimModel lightUpModel;
    /* 0x368 */ ModelAnim lightUpAnim;
};

extern "C" {
char data_ov003_022352d4[0x14];
BuildingActor *sVillagerHouses[8];
char data_ov003_02235308[0x28];
char data_ov003_02235330[0x28];
}

extern "C" void *VillagerHouse_Create() {
    return new VillagerHouse;
}

VillagerHouse::VillagerHouse() {
    for (u32 i = 0; i < 8; i++) {
        sVillagerHouses[i] = 0;
    }
}

VillagerHouse::~VillagerHouse() {
}
extern "C" const u8 sVillagerHouseClosedMsgsAlt[8];
extern "C" ActorProfile sVillagerHouseProfile;
extern "C" const u8 sVillagerHouseClosedMsgs[8];

extern "C" const u8 sVillagerHouseClosedMsgsAlt[8] = { 0x0a, 0x0b, 0x0c, 0x08, 0x09, 0x0d, 0, 0 };
extern "C" const u8 sVillagerHouseClosedMsgs[8] = { 0x10, 0x11, 0x12, 0x0e, 0x0f, 0x13, 0, 0 };

extern "C" ActorProfile sVillagerHouseProfile = { (void *(*)())VillagerHouse_Create, 0x1d, 0x23, 0, 0xc8000, 0x12c000, 0x258000 };

FxVec3 VillagerHouse_initBuilding_v(-0x2000, 0x1000, 0x2000);
BOOL VillagerHouse::initBuilding() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    VecFx32 tmp;
    Vec_Add(&tmp, &position, &VillagerHouse_initBuilding_v);
    Actor::spawn(0x18, idx, &tmp, NULL, this);
    sVillagerHouses[idx] = this;
    s32 k = getHouseVariant();
    void *r7 = VillagerHouseTex_GetHouseTex(FieldStructureMgr_GetVillagerHouseTex(), k);
    void *r4 = VillagerHouseTex_GetLightTex(FieldStructureMgr_GetVillagerHouseTex(), k);
    void *g = model.resMdl;
    if (r7) {
        NNS_G3dBindMdlTex(g, r7);
    }
    if (r4) {
        NNS_G3dBindMdlTex(g, r4);
        NNS_G3dBindMdlPltt(g, r4);
    }
    if (HouseLightUpDeco_IsLoaded(FieldStructureMgr_GetLightUpDeco())) {
        s32 q = getHouseStyle() >> 2;
        if (lightUpModel.setResource((NNSG3dResMdl *)HouseLightUpDeco_GetModel(FieldStructureMgr_GetLightUpDeco(), q), 0)) {
            void *a = HouseLightUpDeco_GetModel(FieldStructureMgr_GetLightUpDeco(), q);
            NNS_G3dBindMdlTex(a, HouseLightUpDeco_GetTex(FieldStructureMgr_GetLightUpDeco()));
            void *b = HouseLightUpDeco_GetModel(FieldStructureMgr_GetLightUpDeco(), q);
            NNS_G3dBindMdlPltt(b, HouseLightUpDeco_GetTex(FieldStructureMgr_GetLightUpDeco()));
            if (lightUpAnim.allocMatAnm(lightUpModel.resMdl, gFieldStructureHeap)) {
                void *c = HouseLightUpDeco_GetTexPattern(FieldStructureMgr_GetLightUpDeco());
                void *d = HouseLightUpDeco_GetTex(FieldStructureMgr_GetLightUpDeco());
                lightUpAnim.initWithTex(c, d, 0, 0x1000, 0);
                lightUpAnim.addToRenderObj(lightUpModel.getRenderObj());
                lightUpModel.mtx = model.mtx;
            }
        }
    }
    return TRUE;
}

BOOL VillagerHouse::onExecute() {
    if (HouseLightUpDeco_IsLoaded(FieldStructureMgr_GetLightUpDeco())) {
        lightUpModel.mtx = model.mtx;
        if ((colliderFlags & 1) == 0) {
            lightUpAnim.step();
            *(u32 *)lightUpAnim.anmObj = lightUpAnim.curFrame;
        }
    }
    return TRUE;
}

BOOL VillagerHouse::onDraw() {
    if (HouseLightUpDeco_IsLoaded(FieldStructureMgr_GetLightUpDeco())) {
        lightUpModel.drawAnimated(0);
    }
    return TRUE;
}

BOOL VillagerHouse::onDelete() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    sVillagerHouses[idx] = 0;
    return TRUE;
}

s32 VillagerHouse::getHouseStyle() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    VillagerHouseStyleBits *r = (VillagerHouseStyleBits *)SaveVillager(idx)->getInfo28();
    return r->f;
}

u8 VillagerHouse::getHouseVariant() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    VillagerHouseStyleBits *r = (VillagerHouseStyleBits *)SaveVillager(idx)->getInfo28();
    return r->f & 3;
}

char *VillagerHouse::getModelName() {
    s32 t = getHouseStyle();
    Str_SPrintf(data_ov003_022352d4, "obj_house%d_%d", t >> 2, t & 3);
    return data_ov003_022352d4;
}

char *VillagerHouse::getArcPath() {
    s32 a = getHouseStyle();
    char *s = getModelName();
    s32 e = Field_GetStructureTexSuffix();
    Str_SPrintf(data_ov003_02235308, "/str/npcHs/%d/%s%c.arc", a >> 2, s, e);
    return data_ov003_02235308;
}

char *VillagerHouse::getTexPath() {
    s32 a = getHouseStyle();
    char *s = getModelName();
    s32 e = Field_GetStructureTexSuffix();
    Str_SPrintf(data_ov003_02235330, "/str/npcHs/%d/%s%c.nsbtx", a >> 2, s, e);
    return data_ov003_02235330;
}

char *VillagerHouse::getLightTexPath() {
    return 0;
}

void *VillagerHouse::getDoorInAnim() {
    return VillagerHouseTex_GetDoorInAnim(FieldStructureMgr_GetVillagerHouseTex());
}

void *VillagerHouse::getDoorOutAnim() {
    return VillagerHouseTex_GetDoorOutAnim(FieldStructureMgr_GetVillagerHouseTex());
}

void VillagerHouse::setupTalkMsg() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    VillagerData *p = SaveVillager(idx);
    setFileName("obj_etc_closed");
    if (Villager_IsHouseAvailable() == 0) {
        msgIndex = 6;
    } else if (entryFlags.f1) {
        setFileName("obj_etc_error");
        msgIndex = 0;
    } else if (VillagerId *q = (VillagerId *)p->getVillagerId()) {
        if (visitRefused == 0) {
            msgIndex = sVillagerHouseClosedMsgs[VillagerId_GetPersonality(q)];
        } else {
            msgIndex = sVillagerHouseClosedMsgsAlt[VillagerId_GetPersonality(q)];
        }
    }
    MsgString9B name;
    ((VillagerId *)p->getVillagerId())->getName(&name);
    window->setSlot(0, &name);
}

BOOL VillagerHouse::isOpen() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    VillagerData *p = SaveVillager(idx);
    if (p) {
        if (Villager_IsHouseAvailable() == 0) {
            return FALSE;
        }
        if (Villager_GetWhereabouts(p) == 0 || Villager_GetWhereabouts(p) == 3 || Villager_GetWhereabouts(p) == 4 || Villager_GetWhereabouts(p) == 5 ||
            Villager_GetWhereabouts(p) == 6 || Villager_GetWhereabouts(p) == 7) {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

BOOL VillagerHouse::areLightsOn() {
    s32 idx = Unk_ov003_02215c7c_Idx(this);
    if (Building_IsNight()) {
        VillagerData *p = SaveVillager(idx);
        if (p) {
            if (Villager_IsHouseAvailable() == 0) {
                return FALSE;
            }
            if (Villager_GetWhereabouts(p) == 0 || Villager_GetWhereabouts(p) == 3 || Villager_GetWhereabouts(p) == 4 || Villager_GetWhereabouts(p) == 5 ||
                Villager_GetWhereabouts(p) == 6 || Villager_GetWhereabouts(p) == 7) {
                return FALSE;
            }
            if (Villager_GetWhereabouts(p) == 2) {
                u8 a, b, c;
                u32 i = 0;
                CommManager *g = gCommManager;
                for (; i < 4; i++) {
                    if (g->isSlotActive(i)) {
                        NetArea_GetSlotStatus(i, &a, &b, &c);
                        if (idx == SceneId_GetVillagerHouse(a)) {
                            return TRUE;
                        }
                    }
                }
                return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL VillagerHouse::usesDoorApproach() {
    return TRUE;
}

BOOL VillagerHouse::playsDoorMelody() {
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02215c74) {
    HOST_OVERLAY_VAR(data_ov003_022352d4),
    HOST_OVERLAY_VAR(sVillagerHouses),
    HOST_OVERLAY_VAR(data_ov003_02235308),
    HOST_OVERLAY_VAR(data_ov003_02235330),
    HOST_OVERLAY_VAR(sVillagerHouseProfile),
    HOST_OVERLAY_VAR(VillagerHouse_initBuilding_v),
    HOST_OVERLAY_VARS_END
};

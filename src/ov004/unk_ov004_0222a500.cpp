#include "game/BoxCollider.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_0202fa70.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "item/ItemId.h"
#include "gfx/G3dResAccess.h"
#include "gfx/MatTexBinder.h"
#include "game/FxVec3.h"
#include "gfx/MatTexVramTask.h"
#include "game/TouchPickCylinder.h"
#include "gfx/AnimModel.h"
#include "gfx/ModelAnim.h"
#include "sys/ProcProfile.h"
#include "gfx/Rgb555.h"
#include "gfx/Mtx43.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/NNSG3dResMatData.h"
#include "gfx/BgModelCache.h"
#include "town/Unk_0204e858_Grid.h"
#include "game/GroundInfo.h"
#include "game/GroundInfoBase.h"
#include "game/TouchPicker.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/Model.h"
#include "gfx/TwoLayerAnimModel.h"
#include "room/HouseData.h"
#include "room/HouseRoom.h"
#include "snd/SndEnvChannel.h"
#include "gfx/PatternTexCache.h"
#include "nnsys/g3d_rt.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203a0cc.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_020b8cd0.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/main/unk_02034048.h"
#include "proto/main/unk_0203c23c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_02088b98.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/main/unk_020abea8.h"
#include "proto/main/unk_020b8d98.h"
#include "proto/ov004/unk_ov004_022136d0.h"
#include "proto/ov004/unk_ov004_0222a500.h"



extern "C" {
}

struct CarpetTexBuf {
    u8 pad[0x20f0 - 0x2c];
    CarpetTexBuf() {
        CarpetTex_Init(this);
    }
};

struct WallpaperTexBuf {
    u8 pad[0x10f0 - 0x2c];
    WallpaperTexBuf() {
        WallpaperTexBuf_Init(this);
    }
};









struct RoomShellStackPad {
    s32 v[2];
    RoomShellStackPad() {}
    ~RoomShellStackPad() {}
};


struct Unk_ov004_0222b954_Pair {
    volatile u16 a;
    volatile u16 b;
};

class RoomShellMatAnim : public ModelAnim {
public:
    RoomShellMatAnim();
    virtual ~RoomShellMatAnim();
};

class RoomCarpet {
public:
    RoomCarpet();
    ~RoomCarpet();
    void release();
    BOOL setCarpet(u16 *q, G3dResAccess *a, s32 key);
    void saveToHouseRoom(u16 *q, u32 key);
    BOOL applyDefault(u16 v, G3dResAccess *a, s32 key);
    BOOL bindMaterial(u8 *buf, u8 *p);
    u32 getDesignKey();
    u16 *getPrevItem();
    u16 *getItem();

    /* 0x0000 */ u16 prevItem;
    /* 0x0002 */ u16 item;
    /* 0x0004 */ MatTexVramTask texTask;
    /* 0x002c */ CarpetTexBuf texBuf;
    /* 0x20f0 */ s32 designKey;
    /* 0x20f4 */ MatTexBinder matBinder;
    /* 0x20fc */ u8 *texRes;
};

class RoomWallpaper {
public:
    RoomWallpaper();
    ~RoomWallpaper();

    void applyDefault(u16 v, void *a, s32 b);
    BOOL bindMaterial(u8 *a, u8 *b);
    u32 getDesignKey();
    u16 *getPrevItem();
    u16 *getItem();

    /* 0x0000 */ u16 prevItem;
    /* 0x0002 */ u16 item;
    /* 0x0004 */ MatTexVramTask texTask;
    /* 0x002c */ WallpaperTexBuf texBuf;
    /* 0x10f0 */ s32 designKey;
    /* 0x10f4 */ MatTexBinder matBinder;
    /* 0x10fc */ u8 *texRes;
public:
    void release();
    BOOL setWallpaper(u16 *q, G3dResAccess *a, s32 key);
};


class RoomScene22Shape : public TouchPickCylinder {
public:
    RoomScene22Shape();
    ~RoomScene22Shape();
    void release();
    void update();
    void init();

    /* 0x20 */ u8 isActive;
};

class RoomEntranceColliders {
public:
    RoomEntranceColliders();
    ~RoomEntranceColliders();
    BOOL release();
    BOOL init();

    BoxCollider colliders[2];
};

class RoomScene0ACollider {
public:
    void release();
    void init();

    BoxCollider collider;
};

class RoomShell : public GameProc {
public:
    RoomShell();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~RoomShell();
    virtual void onNodeDescCallback(s32 a, NNSG3dRS *b);
    virtual void onMatCallback(s32 idx, NNSG3dRS *o);

    void setMatLightFlags(u8 *p);
    void storeBaseMtx();
    void initAnims();
    void initWallAndFloor();
    void calcRoomSize();

    /* 0x0050 */ AnimModel model;
    /* 0x0108 */ RoomShellMatAnim matAnim[1];
    /* 0x0128 */ RoomWallpaper wallpaper;
    /* 0x1228 */ RoomCarpet carpet;
    /* 0x3328 */ RoomEntranceColliders entranceColliders;
    /* 0x3460 */ RoomScene0ACollider scene0ACollider;
    /* 0x34fc */ RoomScene22Shape scene22Shape;
    /* 0x3520 */ s8 hourHandNode;
    /* 0x3521 */ s8 minuteHandNode;
    /* 0x3522 */ s8 roomSize;
    /* 0x3523 */ s8 hasuNode;
    /* 0x3524 */ u32 pad_3524;
    /* 0x3528 */ VecFx32 clockPos;
    /* 0x3534 */ SndEnvChannel clockSe;
    /* 0x3540 */ s8 wdMatIdx;
};


extern "C" {
u32 Scene_GetCurrent(void);
s32 Scene_InHouseRoom(void);
s32 Scene_InUnk6To8(void);
s32 Scene_InNookShop(void);
void JointCb_RotateClockHourHand(NNSG3dRS *rs);
void JointCb_RotateClockMinuteHand(NNSG3dRS *rs);
BOOL Item_IsFurniture(u16 *p);
u32 Item_GetFurnitureIndex(u16 *p);
u32 Item_GetDesignPlayer(u16 *p);
u32 Item_GetDesignSlot(u16 *p);
BOOL Wallpaper_LoadTexture(void *o, u16 *p);
s32 FX_Div(s32 a, s32 b);
void Mtx43_SetTranslate(void *m, s32 a, s32 b, s32 c);
u32 SceneLights_GetMatLightMask2();
void *SaveVillagers_Get(void *self, s32 i);
u32 Villager_GetWallpaper(void *self);
u32 Villager_GetCarpet(void *self);
void NNS_G3dMdlSetMdlDiff(void *a, s32 b, u32 c);
u16 *Sky_GetCurrentPalette();
u16 Sky_GetLightColor(u32 v);

#define gSaveHouse HOST_LABEL(u8 (*)[], gSaveHouse)
#define gSaveVillagers HOST_LABEL(u8 (*)[], gSaveVillagers)
extern Mtx43 data_021f47e0;
extern u32 data_020c8cc0;
extern Unk_0204e858_Grid *gSceneBlockMap;

}


extern "C" RoomShell *sRoomShell;
extern "C" char sRoomWallpaperMatNameStr[];
extern "C" char sRoomCarpetMatNameStr[];

extern "C" const char *sRoomCarpetMatName;
extern "C" const char *sRoomWallpaperMatName;
extern "C" FxVec3 sRoomHasuPos;
extern "C" ItemId sRoomNoItem;
extern "C" ProcProfile sRoomShellProfile = { (void *(*)())RoomShell_Create, 0xe, 0xa };
extern "C" {
FxVec3 sRoomHasuPos(0, 0, 0);
RoomShell *sRoomShell;
}


extern "C" RoomShell *RoomShell_Create() {
    return new RoomShell;
}

RoomShell::RoomShell() {
    hourHandNode = minuteHandNode = wdMatIdx = -1;
}

RoomShell::~RoomShell() {
}

BOOL RoomShell::onCreate() {
    sRoomShell = this;
    entranceColliders.init();
    scene0ACollider.init();
    scene22Shape.init();
    calcRoomSize();
    initAnims();
    setMatLightFlags((u8 *)model.resMdl);
    storeBaseMtx();
    initWallAndFloor();
    hourHandNode = ((G3dResAccess *)model.resMdl)->findNodeIdx("kh_j");
    minuteHandNode = ((G3dResAccess *)model.resMdl)->findNodeIdx("km_j");
    hasuNode = ((G3dResAccess *)model.resMdl)->findNodeIdx("hasu1");
    wdMatIdx = ((G3dResAccess *)model.resMdl)->findMatIdx("wd");
    model.setInitCallback((void (*)(NNSG3dRS *))RoomShell_InitRenderObj, this);
    RoomShell_SpawnBoardSigns(this);
    clockSe.callReset();
    return TRUE;
}

BOOL RoomShell::onExecute() {
    if (((BlendAnimModel *)&model)->getAnmObj()) {
        model.stepAnim();
    }
    RoomShellMatAnim *e = matAnim;
    if (RoomShellMatAnim_GetAnmObj(e)) {
        e->step();
        ((G3dAnmObj *)matAnim[0].anmObj)->frame = matAnim[0].curFrame;
    }
    if (clockPos.x != 0) {
        s32 id = FtrMgr_GetCycleCounter();
        if (id == 9 || id == 0x1d) {
            clockSe.callRequestSustained(0x4d1);
        }
    }
    VecFx32 v = clockPos;
    clockSe.callUpdateRelative(&v);
    scene22Shape.update();
    data_021ce63c = 0;
    return TRUE;
}

BOOL RoomShell::onDraw() {
    ObjShadow_Update();
    CharaShadow_UpdateColor();
    if (wdMatIdx != -1) {
        Unk_ov004_0222b954_Pair t;
        t.a = RoomShell_CalcWdColor(this);
        t.b = t.a;
        NNS_G3dMdlSetMdlDiff((u8 *)model.resMdl, wdMatIdx, t.b);
    }
    model.drawAnimated(0);
    return TRUE;
}

BOOL RoomShell::onDelete() {
    wallpaper.release();
    scene22Shape.release();
    scene0ACollider.release();
    carpet.release();
    entranceColliders.release();
    model.clearResource();
    sRoomShell = 0;
    clockSe.callRelease();
    return TRUE;
}

void RoomShell::calcRoomSize() {
    s32 cnt = 0;
    s32 i;
    for (i = 0; i < 16; i++) {
        GroundInfo g;
        g.initAtUnit(i, 10, 0, 0);
        if (g.getHeight(0) == 0) {
            cnt++;
        }
    }
    roomSize = cnt;
}

static inline BOOL Unk_ov004_0222b610_InA(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x1100 && *p <= 0x1143) {
        r = TRUE;
    }
    return r;
}

static inline BOOL Unk_ov004_0222b610_InB(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x1144 && *p <= 0x1187) {
        r = TRUE;
    }
    return r;
}

ItemId RoomShell_GetSceneWallFloor_t[6];
u8 RoomShell_GetSceneWallFloor_t_init;
ItemId RoomShell_GetSceneWallFloor_t_2[6];
u8 RoomShell_GetSceneWallFloor_t_2_init;
extern "C" void RoomShell_GetSceneWallFloor(void *self, u16 *a, s32 *b, u16 *c, s32 *d) {
    s32 r = Scene_GetCurrent();
    *d = 0;
    *b = *d;
    if (SceneId_IsHouseRoom(r)) {
        HouseRoom *o = ((HouseData *)gSaveHouse)->getRoom(SceneId_GetHouseRoom(r));
        if (o != NULL) {
            *a = *o->getWallpaper(b);
            *c = *o->getCarpet(d);
        }
    } else if (SceneId_IsVillagerHouse(r)) {
        void *o = SaveVillagers_Get(gSaveVillagers, SceneId_GetVillagerHouse(r));
        if (o != NULL) {
            u32 t = Villager_GetWallpaper(o);
            *a = t < 0x44 ? (u16)(t + 0x1100) : 0x1100;
            t = Villager_GetCarpet(o);
            *c = t < 0x44 ? (u16)(t + 0x1144) : 0x1144;
        }
    } else if (SceneId_IsNookShop(r)) {
        s32 i = SceneId_GetNookShop(r);
        u16 *p = RoomWallFloor_GetSceneWallpaper(r);
        if (Unk_ov004_0222b610_InA(p)) {
            *a = *p;
        } else {
            if (!RoomShell_GetSceneWallFloor_t_init) {
                HOST_STATIC_INIT_ARRAY(RoomShell_GetSceneWallFloor_t, {
                ItemId(0x1140), ItemId(0x1141), ItemId(0x1142),
                ItemId(0x1143), ItemId(0x1143), ItemId(0x1143)
            });
                RoomShell_GetSceneWallFloor_t_init = 1;
            }
            *a = RoomShell_GetSceneWallFloor_t[i].id;
        }
        p = RoomWallFloor_GetSceneCarpet(r);
        if (Unk_ov004_0222b610_InB(p)) {
            *c = *p;
        } else {
            if (!RoomShell_GetSceneWallFloor_t_2_init) {
                HOST_STATIC_INIT_ARRAY(RoomShell_GetSceneWallFloor_t_2, {
                ItemId(0x1184), ItemId(0x1185), ItemId(0x1186),
                ItemId(0x1187), ItemId(0x1187), ItemId(0x1187)
            });
                RoomShell_GetSceneWallFloor_t_2_init = 1;
            }
            *c = RoomShell_GetSceneWallFloor_t_2[i].id;
        }
    }
}

static inline BOOL Unk_ov004_0222b510_Range(volatile u16 *p) {
    BOOL r = FALSE;
    u32 a = *p;
    u32 b = *p;
    if (b >= 0x1188 && a <= 0x11a7) {
        r = TRUE;
    }
    return r;
}

void RoomShell::initWallAndFloor() {
    Unk_0204e858_Grid *g = gSceneBlockMap;
    TownBlockCell *c;
    if (g->width != 0 && g->height != 0 && g->blocks != NULL) {
        c = g->blocks;
    } else {
        c = NULL;
    }
    BgAcreModel *r = c->bgModel;
    wallpaper.bindMaterial((u8 *)model.resMdl, (u8 *)r->tex);
    carpet.bindMaterial((u8 *)model.resMdl, (u8 *)r->tex);
    volatile u16 h[2];
    s32 w8;
    s32 w12;
    h[0] = 0xfff1;
    h[1] = 0xfff1;
    RoomShell_GetSceneWallFloor(this, (u16 *)&h[0], &w8, (u16 *)&h[1], &w12);
    if (Unk_ov004_0222b510_Range(&h[0])) {
        wallpaper.applyDefault(0x1124, (u8 *)model.resMdl, w8);
    }
    if (Unk_ov004_0222b510_Range(&h[1])) {
        carpet.applyDefault(0x1182, (G3dResAccess *)model.resMdl, w12);
    }
    wallpaper.setWallpaper((u16 *)&h[0], (G3dResAccess *)model.resMdl, w8);
    carpet.setCarpet((u16 *)&h[1], (G3dResAccess *)model.resMdl, w12);
}

void RoomShell::initAnims() {
    Unk_0204e858_Grid *g = gSceneBlockMap;
    TownBlockCell *c;
    if (g->width != 0 && g->height != 0 && g->blocks != NULL) {
        c = g->blocks;
    } else {
        c = NULL;
    }
    BgAcreModel *r = c->bgModel;
    model.setResourceAndBind((NNSG3dResMdl *)(r->mdl), (NNSG3dResTex *)(r->tex));
    if (r->jntAnm != 0) {
        if (model.allocAnmObj(gBgHeap)) {
            ((BlendAnimModel *)(&model))->initAnim(r->jntAnm, 0, 0x1000, 0, 0);
            model.attachAnim();
        }
    }
    if (r->texSrtAnm != 0) {
        if (matAnim[0].allocMatAnm(model.resMdl, gBgHeap)) {
            matAnim[0].init(r->texSrtAnm, 0, 0x1000, 0);
            matAnim[0].addToRenderObj(model.getRenderObj());
        }
    }
}

void RoomShell::storeBaseMtx() {
    Mtx43_SetTranslate(&data_021f47e0, 0, 0, 0);
    model.mtx = data_021f47e0;
}

void RoomShell::setMatLightFlags(u8 *p) {
    u32 n = p[0x18];
    u8 *q = p + *(u32 *)(p + 8);
    u32 i;
    for (i = 0; i < n; i++) {
        u8 *a = q + 4;
        u32 off = *(u16 *)(q + 0xa);
        u8 *t = a + off;
        u32 stride = *(u16 *)t;
        u8 *e = q + *(u32 *)(t + stride * i + 4);
        NNSG3dResMatData *en = (NNSG3dResMatData *)e;
        if ((en->polyAttr & 0xf) != 0) {
            en->polyAttr &= ~0xf;
            en->polyAttr |= SceneLights_GetMatLightMask2();
        }
    }
}

RoomWallpaper::RoomWallpaper() : prevItem(0xfff1), item(0xfff1) {
    prevItem = 0xfff1;
    item = 0xfff1;
    designKey = 0;
}

RoomWallpaper::~RoomWallpaper() {
}

u16 *RoomWallpaper::getItem() {
    return &item;
}

u16 *RoomWallpaper::getPrevItem() {
    return &prevItem;
}

u32 RoomWallpaper::getDesignKey() {
    return designKey;
}

BOOL RoomWallpaper::bindMaterial(u8 *a, u8 *b) {
    if (b != 0) {
        matBinder.setMaterialByName(a, sRoomWallpaperMatNameStr);
        texRes = b;
        return TRUE;
    }
    return FALSE;
}

void RoomWallpaper::applyDefault(u16 v, void *a, s32 b) {
    u16 t = v;
    setWallpaper(&t, (G3dResAccess *)a, b);
}

extern "C" void RoomWallpaper_SaveToHouseRoom(void *self, u16 *a, u32 b) {
    if (Scene_InHouseRoom()) {
        HouseRoom *r = ((HouseData *)gSaveHouse)->getRoom(Scene_GetHouseRoom());
        if (r != NULL) {
            r->setWallpaper(a, b);
        }
    }
}

BOOL RoomWallpaper::setWallpaper(u16 *q, G3dResAccess *a, s32 key) {
    BOOL same;
    if (a->findMatIdx(sRoomWallpaperMatName) == -1) return FALSE;
    if (Item_IsFurniture(&item) != 0) {
        u32 x = Item_GetFurnitureIndex(&item);
        u32 y = Item_GetFurnitureIndex(q);
        if (x == y) same = TRUE;
        else same = FALSE;
    } else {
        if (item == *q) same = TRUE;
        else same = FALSE;
    }
    if (same != FALSE && designKey == key) {
        goto done;
    }
    {
        BOOL in = FALSE;
        u16 v = *q;
        if (v >= 0x1100 && v <= 0x1143) in = TRUE;
        if (in != FALSE) {
            if (Wallpaper_LoadTexture(&texBuf, q) == 0) goto fail;
            if (Scene_InNookShop() == 0) {
                matBinder.bindByName(texRes, "dummy_wall", "dummy_wall_pl");
            }
            void *r = Wallpaper_GetTex((u8 *)&texBuf);
            if (texTask.request(a, (const char *)(sRoomWallpaperMatName), r, 0, 0) == 0) goto fail;
            prevItem = item;
            item = *q;
            RoomWallpaper_SaveToHouseRoom(this, &item, key);
            RoomWallFloor_SetSceneWallpaper(Scene_GetCurrent(), &item);
            return TRUE;
        } else if (v >= 0x1188 && v <= 0x11a7) {
            u32 t7 = Item_GetDesignPlayer(q);
            u32 t8 = Item_GetDesignSlot(q);
            u8 *idx = PatternTexCache_Get()->getPlayerTexKey((u8)t7, (u8)t8);
            matBinder.bindByIdx(idx, 0, 0);
            prevItem = item;
            item = *q;
            designKey = key;
            RoomWallpaper_SaveToHouseRoom(this, &item, key);
            RoomWallFloor_SetSceneWallpaper(Scene_GetCurrent(), &item);
            return TRUE;
        }
    }
fail:
    return FALSE;
done:
    prevItem = item;
    item = *q;
    designKey = key;
    RoomWallpaper_SaveToHouseRoom(this, &item, key);
    RoomWallFloor_SetSceneWallpaper(Scene_GetCurrent(), &item);
    return TRUE;
}

void RoomWallpaper::release() {
    texTask.cancel();
}

RoomCarpet::RoomCarpet() : prevItem(0xfff1), item(0xfff1) {
    prevItem = 0xfff1;
    item = 0xfff1;
    designKey = 0;
}

RoomCarpet::~RoomCarpet() {
}

u16 *RoomCarpet::getItem() {
    return &item;
}

u16 *RoomCarpet::getPrevItem() {
    return &prevItem;
}

u32 RoomCarpet::getDesignKey() {
    return designKey;
}

BOOL RoomCarpet::bindMaterial(u8 *buf, u8 *p) {
    if (p != 0) {
        matBinder.setMaterialByName(buf, sRoomCarpetMatNameStr);
        texRes = p;
        return TRUE;
    }
    return FALSE;
}

BOOL RoomCarpet::applyDefault(u16 v, G3dResAccess *a, s32 key) {
    u16 t = v;
    return setCarpet(&t, a, key);
}

void RoomCarpet::saveToHouseRoom(u16 *q, u32 key) {
    if (Scene_InHouseRoom() != 0) {
        u32 t = Scene_GetHouseRoom();
        HouseRoom *o = ((HouseData *)gSaveHouse)->getRoom(t);
        if (o != 0) {
            o->setCarpet(q, key);
        }
    }
}

BOOL RoomCarpet::setCarpet(u16 *q, G3dResAccess *a, s32 key) {
    BOOL same;
    if (a->findMatIdx(sRoomCarpetMatName) == -1) return FALSE;
    if (Item_IsFurniture(&item) != 0) {
        u32 x = Item_GetFurnitureIndex(&item);
        u32 y = Item_GetFurnitureIndex(q);
        if (x == y) same = TRUE;
        else same = FALSE;
    } else {
        if (item == *q) same = TRUE;
        else same = FALSE;
    }
    if (same != FALSE && designKey == key) {
        goto done;
    }
    {
        BOOL in = FALSE;
        u16 v = *q;
        if (v >= 0x1144 && v <= 0x1187) in = TRUE;
        if (in != FALSE) {
            if (CarpetTex_Load(&texBuf, q) == 0) goto fail;
            if (Scene_InNookShop() == 0) {
                matBinder.bindByName(texRes, "dummy_floor", "dummy_floor_pl");
            }
            void *r = CarpetTex_GetTex(&texBuf);
            if (texTask.request(a, (const char *)(sRoomCarpetMatName), r, 0, 0) == 0) goto fail;
            prevItem = item;
            item = *q;
            saveToHouseRoom(&item, key);
            RoomWallFloor_SetSceneCarpet(Scene_GetCurrent(), &item);
            return TRUE;
        } else if (v >= 0x1188 && v <= 0x11a7) {
            u32 t7 = Item_GetDesignPlayer(q);
            u32 t8 = Item_GetDesignSlot(q);
            u8 *idx = PatternTexCache_Get()->getPlayerTexKey((u8)t7, (u8)t8);
            matBinder.bindByIdx(idx, 0, 0);
            prevItem = item;
            item = *q;
            designKey = key;
            saveToHouseRoom(&item, key);
            RoomWallFloor_SetSceneCarpet(Scene_GetCurrent(), &item);
            return TRUE;
        }
    }
fail:
    return FALSE;
done:
    prevItem = item;
    item = *q;
    designKey = key;
    saveToHouseRoom(&item, key);
    RoomWallFloor_SetSceneCarpet(Scene_GetCurrent(), &item);
    return TRUE;
}

void RoomCarpet::release() {
    texTask.cancel();
}

RoomShellMatAnim::RoomShellMatAnim() {
}

RoomShellMatAnim::~RoomShellMatAnim() {
}

extern "C" NNSG3dAnmObj *RoomShellMatAnim_GetAnmObj(ModelAnim *o) {
    return o->anmObj;
}

RoomEntranceColliders::RoomEntranceColliders() {
}

RoomEntranceColliders::~RoomEntranceColliders() {
}

extern "C" BOOL RoomEntranceColliders_InHouseScene() {
    if (Scene_InHouseRoom() != 0 || Scene_InUnk6To8() != 0) return TRUE;
    return FALSE;
}

BOOL RoomEntranceColliders::init() {
    if (RoomEntranceColliders_InHouseScene() != 0) {
        VecFx32 a;
        VecFx32 b;
        a.x = 0xd000;
        a.y = 0;
        a.z = 0x1c000;
        b.x = 0x13000;
        b.y = 0;
        b.z = 0x1c000;
        BOOL r0 = BoxCollider_Register(&colliders[0], 0x2000, 0, 0x4000, &a, 0, 0);
        BOOL r1 = BoxCollider_Register(&colliders[1], 0x2000, 0, 0x4000, &b, 0, 0);
        if (r0 != 0 && r1 != 0) return TRUE;
        return FALSE;
    }
    return FALSE;
}

BOOL RoomEntranceColliders::release() {
    if (RoomEntranceColliders_InHouseScene() != 0) {
        BoxCollider_Unregister(&colliders[0]);
        BoxCollider_Unregister(&colliders[1]);
    }
    return TRUE;
}

extern "C" char sRoomCarpetMatNameStr[] = "m_dummy_floor";
extern "C" const char *sRoomCarpetMatName = sRoomCarpetMatNameStr;
extern "C" {
ItemId sRoomNoItem(0xfff1);
}

FxVec3 RoomScene0ACollider_init_s;
u8 RoomScene0ACollider_init_s_init;
void RoomScene0ACollider::init() {
    if (Scene_GetCurrent() == 0xa) {
        if (!RoomScene0ACollider_init_s_init) {
            HOST_STATIC_INIT(RoomScene0ACollider_init_s, FxVec3(0xe000, 0, data_020c8cc0 + 0x1000));
            RoomScene0ACollider_init_s_init = 1;
        }
        BoxCollider_Register(&collider, 0x8000, 0x2000, 0x1000, &RoomScene0ACollider_init_s, 0, 0);
    }
}

extern "C" char sRoomWallpaperMatNameStr[] = "m_dummy_wall";
extern "C" const char *sRoomWallpaperMatName = sRoomWallpaperMatNameStr;

void RoomScene0ACollider::release() {
    if (Scene_GetCurrent() == 0xa) {
        BoxCollider_Unregister(&collider);
    }
}

RoomScene22Shape::RoomScene22Shape() {
    isActive = 0;
}

RoomScene22Shape::~RoomScene22Shape() {
}

void RoomScene22Shape::init() {
    VecFx32 v;
    if (Scene_GetCurrent() == 0x22) {
        isActive = 1;
    }
    if (isActive != 0) {
        v.x = 0x108f6;
        v.y = 0;
        v.z = 0x1351e;
        Scene_GetTouchPicker()->addCylinder(this, &v, 0xf33, 0x6000, 0x16, 0xff);
    }
}

void RoomScene22Shape::update() {
    if (isActive != 0) {
        Scene_GetTouchPicker()->pushCylinder(this);
    }
}

void RoomScene22Shape::release() {
}

static inline BOOL Unk_ov004_0222aacc_R1(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

extern "C" u16 *RoomShell_SetWallpaper(u16 *p, s32 key, u32 flag) {
    BOOL r = Unk_ov004_0222aacc_R1(p, 0x1100, 0x1143);
    if (r != FALSE || (*p >= 0x1188 && *p <= 0x11a7)) {
        RoomShell *g = sRoomShell;
        if (g != 0) {
            if (((RoomWallpaper *)&g->wallpaper)->setWallpaper(p, (G3dResAccess *)g->model.resMdl, key) != 0) {
                if (flag != 0) {
                    if (Scene_InNookShop() != 0) Snd_PlaySe(0x50);
                }
                BOOL r2 = Unk_ov004_0222aacc_R1(sRoomShell->wallpaper.getPrevItem(), 0x1100, 0x1143);
                if (r2 != FALSE) return sRoomShell->wallpaper.getPrevItem();
                return (u16 *)&sRoomNoItem;
            }
        }
    }
    return (u16 *)&sRoomNoItem;
}

extern "C" u16 *RoomShell_SetCarpet(u16 *p, s32 key, u32 flag) {
    BOOL r = Unk_ov004_0222aacc_R1(p, 0x1144, 0x1187);
    if (r != FALSE || (*p >= 0x1188 && *p <= 0x11a7)) {
        RoomShell *g = sRoomShell;
        if (g != 0) {
            if (g->carpet.setCarpet(p, (G3dResAccess *)g->model.resMdl, key) != 0) {
                if (flag != 0) {
                    if (Scene_InNookShop() != 0) Snd_PlaySe(0x50);
                }
                BOOL r2 = Unk_ov004_0222aacc_R1(sRoomShell->carpet.getPrevItem(), 0x1144, 0x1187);
                if (r2 != FALSE) return sRoomShell->carpet.getPrevItem();
                return (u16 *)&sRoomNoItem;
            }
        }
    }
    return (u16 *)&sRoomNoItem;
}

extern "C" u16 *RoomShell_GetCarpet() {
    RoomShell *g = sRoomShell;
    if (g != 0) {
        return g->carpet.getItem();
    }
    return (u16 *)&sRoomNoItem;
}

extern "C" u16 *RoomShell_GetPrevCarpet() {
    RoomShell *g = sRoomShell;
    if (g != 0) {
        return g->carpet.getPrevItem();
    }
    return (u16 *)&sRoomNoItem;
}

extern "C" u16 *RoomShell_GetWallpaper() {
    RoomShell *g = sRoomShell;
    if (g != 0) {
        return g->wallpaper.getItem();
    }
    return (u16 *)&sRoomNoItem;
}

extern "C" u16 *RoomShell_GetPrevWallpaper() {
    RoomShell *g = sRoomShell;
    if (g != 0) {
        return g->wallpaper.getPrevItem();
    }
    return (u16 *)&sRoomNoItem;
}

void RoomShell::onNodeDescCallback(s32 a, NNSG3dRS *b) {
    RoomShellStackPad pad;
    if (hourHandNode == a) {
        JointCb_RotateClockHourHand(b);
        VecFx32 *pv = (VecFx32 *)&b->pJntAnmResult->trans;
        VecFx32 v;
        v.y = pv->y;
        v.z = pv->z;
        v.x = pv->x;
        clockPos.x = v.x;
        clockPos.y = v.y;
        clockPos.z = v.z;
    } else if (minuteHandNode == a) {
        JointCb_RotateClockMinuteHand(b);
    } else if (hasuNode == a) {
        if (b != 0) {
            NNSG3dJntAnmResult *p = b->pJntAnmResult;
            s32 z = p->trans.z;
            s32 x = p->trans.x;
            sRoomHasuPos.x = x;
            sRoomHasuPos.y = 0x3700;
            sRoomHasuPos.z = z;
        }
    }
}

static inline BOOL Unk_ov004_0222a6c0_Rng(u16 *p) {
    BOOL r = FALSE;
    if (*p >= 0x1188 && *p <= 0x11a7) {
        r = TRUE;
    }
    return r;
}

void RoomShell::onMatCallback(s32 idx, NNSG3dRS *o) {
    u8 *h = o->pResMat;
    u8 *t = h + 4;
    u32 off = *(u16 *)(h + 0xa);
    u32 stride = *(u16 *)(t + off);
    NNSG3dResMatData *rec = (NNSG3dResMatData *)(h + *(u32 *)(t + off + stride * idx + 4));
    BOOL a;
    BOOL b;
    s32 v8, vc, v10;
    if (idx == wallpaper.matBinder.getMaterial()) {
        a = TRUE;
    } else {
        a = FALSE;
    }
    if (idx == carpet.matBinder.getMaterial()) {
        b = TRUE;
    } else {
        b = FALSE;
    }
    if (a && Unk_ov004_0222a6c0_Rng(wallpaper.getItem())) {
    } else if (b && Unk_ov004_0222a6c0_Rng(carpet.getItem())) {
    } else {
        return;
    }
    o->pMatAnmResult->prmTexImage &= 0x3fffffff;
    o->pMatAnmResult->prmTexImage &= 0xfffbffff;
    o->pMatAnmResult->prmTexImage &= 0xfff7ffff;
    o->pMatAnmResult->prmTexImage &= 0xfffeffff;
    o->pMatAnmResult->prmTexImage &= 0xfffdffff;
    o->pMatAnmResult->prmTexImage |= 0x40000000;
    s32 k;
    if (a) {
        k = wallpaper.getDesignKey();
    } else {
        k = carpet.getDesignKey();
    }
    o->pMatAnmResult->prmTexImage |= 0x10000;
    o->pMatAnmResult->prmTexImage |= 0x20000;
    if (k == 1) {
        o->pMatAnmResult->prmTexImage |= 0x40000;
        o->pMatAnmResult->prmTexImage |= 0x80000;
    }
    o->pMatAnmResult->flag |= 8;
    o->pMatAnmResult->origWidth = rec->origWidth;
    o->pMatAnmResult->origHeight = rec->origHeight;
    o->pMatAnmResult->magW = rec->magW;
    o->pMatAnmResult->magH = rec->magH;
    o->pMatAnmResult->flag &= ~1;
    o->pMatAnmResult->flag |= 6;
    if (a) {
        switch (roomSize) {
        case 4:
            v8 = FX_Div(0, 0x64000) + 0x2000;
            vc = FX_Div(0, 0x64000) + 0x4000;
            break;
        case 6:
            v8 = FX_Div(0, 0x64000) + 0x2000;
            vc = FX_Div(0, 0x64000) + 0x4000;
            break;
        case 8:
            v8 = FX_Div(0, 0x64000) + 0x2000;
            vc = FX_Div(0, 0x64000) + 0x4000;
            break;
        }
        o->pMatAnmResult->scaleS = v8;
        o->pMatAnmResult->scaleT = vc;
    } else {
        switch (roomSize) {
        case 4:
            v10 = FX_Div(0, 0x64000) + 0x2000;
            break;
        case 6:
            v10 = FX_Div(0, 0x64000) + 0x3000;
            break;
        case 8:
            v10 = FX_Div(0, 0x64000) + 0x4000;
            break;
        }
        o->pMatAnmResult->scaleS = v10;
        o->pMatAnmResult->scaleT = v10;
    }
    o->flag &= 0xfffffeff;
}

struct RoomBoardSignDef {
    s16 posX;
    s16 posY;
    s16 posZ;
    s16 radius;
    u8 dir;
    u8 msgIndex;
};

extern "C" void RoomShell_SpawnBoardSigns(void *self) {
    Unk_0204e858_Grid *g = gSceneBlockMap;
    TownBlockCell *c;
    if (g->width != 0 && g->height != 0 && g->blocks != 0) {
        c = g->blocks;
    } else {
        c = 0;
    }
    BgAcreModel *o = c->bgModel;
    if (o != 0) {
        RoomBoardSignDef *e = (RoomBoardSignDef *)o->mgt;
        if (e != 0) {
            if ((u32)o->mgtCount != 0) {
                u32 i;
                for (i = 0; i < (u32)o->mgtCount; e++, i++) {
                    VecFx32Ctor v((e->posX << 12) >> 4, (e->posY << 12) >> 4, (e->posZ << 12) >> 4);
                    RoomBoardSign_Spawn(&v, (e->radius << 12) >> 4, ((s32)(e->dir << 30)) >> 16, e->msgIndex);
                }
            }
        }
    }
}

extern "C" s16 RoomShell_CalcWdColor(void *self) {
    Rgb555 a;
    Rgb555 c;
    Rgb555 b;
    u16 *p = Sky_GetCurrentPalette();
    *(u16 *)&c = 0xffff;
    if (p != 0) {
        *(u16 *)&a = Sky_GetLightColor(0);
        b = a;
        *(u16 *)&c = p[5];
        s32 r = c.r + b.r / 3;
        s32 g = c.g + b.g / 3;
        s32 l = c.b + b.b / 3;
        if (r > 0x1f) {
            r = 0x1f;
        } else if (r < 0) {
            r = 0;
        }
        if (g > 0x1f) {
            g = 0x1f;
        } else if (g < 0) {
            g = 0;
        }
        if (l > 0x1f) {
            l = 0x1f;
        } else if (l < 0) {
            l = 0;
        }
        c.r = r;
        c.g = g;
        c.b = l;
    }
    return *(s16 *)&c;
}

extern "C" void RoomShell_MatCallback(void *p) {
    NNSG3dRS *self = (NNSG3dRS *)p;
    RoomShell *t = (RoomShell *)self->pRenderObj->ptrUser;
    if (t != 0) {
        t->onMatCallback(self->c[1], self);
    }
}

extern "C" void RoomShell_NodeDescCallback(void *p) {
    NNSG3dRS *self = (NNSG3dRS *)p;
    RoomShell *t = (RoomShell *)self->pRenderObj->ptrUser;
    if (t != 0) {
        t->onNodeDescCallback(self->c[1], self);
    }
}

extern "C" void RoomShell_InitRenderObj(void *p) {
    NNSG3dRS *self = (NNSG3dRS *)p;
    self->cbVecFunc[4] = (void *)RoomShell_MatCallback;
    self->cbVecTiming[4] = 2;
    self->cbVecFunc[6] = (void *)RoomShell_NodeDescCallback;
    self->cbVecTiming[6] = 2;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_0222a500) {
    HOST_OVERLAY_VAR(sRoomShellProfile),
    HOST_OVERLAY_VAR(sRoomHasuPos),
    HOST_OVERLAY_VAR(sRoomShell),
    HOST_OVERLAY_VAR(RoomShell_GetSceneWallFloor_t),
    HOST_OVERLAY_VAR(RoomShell_GetSceneWallFloor_t_init),
    HOST_OVERLAY_VAR(RoomShell_GetSceneWallFloor_t_2),
    HOST_OVERLAY_VAR(RoomShell_GetSceneWallFloor_t_2_init),
    HOST_OVERLAY_VAR(sRoomCarpetMatNameStr),
    HOST_OVERLAY_VAR(sRoomCarpetMatName),
    HOST_OVERLAY_VAR(sRoomNoItem),
    HOST_OVERLAY_VAR(RoomScene0ACollider_init_s),
    HOST_OVERLAY_VAR(RoomScene0ACollider_init_s_init),
    HOST_OVERLAY_VAR(sRoomWallpaperMatNameStr),
    HOST_OVERLAY_VAR(sRoomWallpaperMatName),
    HOST_OVERLAY_VARS_END
};

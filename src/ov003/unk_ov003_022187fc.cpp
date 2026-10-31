#include "types.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "town/TownState.h"
#include "town/BlockMap.h"
#include "gfx/VecFx32.h"
#include "sys/ProcProfile.h"
#include "sys/NNSFndArchive.h"
#include "town/BuildingActor.h"
#include "town/BuildingInfo.h"
#include "town/BlockMap.h"
#include "town/MapBlock.h"
#include "town/TownMap.h"
#include "town/TownBlockMap.h"
#include "town/Unk_0204e858_Grid.h"
#include "save/TownStyleRecordView.h"
#include "actor/Actor.h"
#include "game/StrBSizeData.h"
#include "net/CommManager.h"
#include "field/FieldStructureMgr.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02101048.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020b0e60.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/main/unk_0204cc1c.h"

#pragma opt_loop_invariants off

struct NNSG3dResTex;
struct TexVramSlot;

extern "C" {
#define gSaveTownFlag HOST_LABEL(TownStyleRecordView *, gSaveTownFlag)
extern BlockMap *gSceneBlockMap;
extern BuildingInfo data_020d0a7c[];
extern CommManager *gCommManager;
#define gSaveTownState HOST_LABEL(u8 (*)[], gSaveTownState)
}

extern "C" {
BOOL MapBlock_SetItem(void *cell, u16 *t, u32 x, u32 y, u8 z);
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
s32 Scene_InTown();
u8 *NNS_G3dGetTex(u8 *p);
u8 *NNS_G3dGetMdlSet(u8 *p);
BOOL Gfx3d_LoadTex(NNSG3dResTex *a, TexVramSlot *b);
BOOL Gfx3d_LoadPltt(NNSG3dResTex *a, TexVramSlot *b);
BOOL Gfx3d_LoadTexAndPltt(NNSG3dResTex *a, TexVramSlot *b);
void *Gfx3d_CopyTex(void *a, void *heap);
u8 *func_021065dc(u8 *p);
u8 *func_021065f8(u8 *p, u32 a);
u8 *func_02106690(u8 *p);
u8 *func_021066ac(u8 *p, u32 a);
s32 Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
s32 GroundSeason_IsSnow();
BOOL Ground_SetQuadrantsBlocked(s32 x, s32 z, s32 mask);
s32 TownState_FindEvent(TownState *x, u32 id);
BOOL NNS_FndMountArchive(NNSFndArchive *arc, const char *name, u32 *binary);
BOOL NNS_FndUnmountArchive(NNSFndArchive *arc);
void BuildingInfo_Copy(BuildingInfo *dst, const BuildingInfo *src);
void BuildingInfo_Destroy(BuildingInfo *i);
}

extern "C" {
PlayerHouseTex sPlayerHouseTex;
VillagerHouseTex sVillagerHouseTex;
HouseLightUpDeco sHouseLightUpDeco;
ProcProfile sFieldStructureMgrProfile = {(void *(*)())FieldStructureMgr_Create, 0xc4, 0x1f};
u8 sDoorExitMode;
u16 sSpawnedBuildingCount1;
char data_ov003_02235888[0x28];
BuildingActor *sBuildingList[0x20];
const char sStructureTexSuffixes[3] = "sw";
}


extern "C" void *FieldStructureMgr_Create() {
    return new FieldStructureMgr;
}

FieldStructureMgr::FieldStructureMgr() {
    BuildingList_Init();
}

FieldStructureMgr::~FieldStructureMgr() {}

BOOL FieldStructureMgr::onCreate() {
    BuildingList_Init();
    Field_CacheExitedBuildingKey();
    FieldStructureMgr_Register(this);
    FieldStructureMgr_CreateHeap(this);
    PlayerHouseTex_Load(&sPlayerHouseTex);
    VillagerHouseTex_Load(&sVillagerHouseTex);
    HouseLightUpDeco_Load(&sHouseLightUpDeco);
    func_ov003_02219164(this);
    func_ov003_02219160(this);
    FieldStructureMgr_SpawnAll(this);
    GameProc_CreateChild(0xf, gActorDefaultParent, 0, 0);
    return TRUE;
}

BOOL FieldStructureMgr::onExecute() { return TRUE; }

BOOL FieldStructureMgr::onDraw() { return TRUE; }

BOOL FieldStructureMgr::onDelete() {
    BuildingList_Clear();
    FieldStructureMgr_Unregister();
    VillagerHouseTex_Clear(&sVillagerHouseTex);
    HouseLightUpDeco_Release(&sHouseLightUpDeco);
    PlayerHouseTex_Release(&sPlayerHouseTex);
    FieldStructureMgr_DestroyHeap(this);
    return TRUE;
}

extern "C" {

void func_ov003_02219164(FieldStructureMgr *self) {}

void func_ov003_02219160(FieldStructureMgr *self) {}

s32 FieldStructureMgr_SpawnAll(FieldStructureMgr *self) {
    BOOL go;
    u32 gw, gh;
    u32 ii, jj;
    s32 count;
    s32 r24;
    MapBlock *cell;
    BOOL a;
    u16 buf[3];
    BuildingInfo obj;
    s32 ax, ay;
    s32 bx, by;
    VecFx32 tl;
    u32 x, y;
    u16 *p;
    BlockMap *g;
    sSpawnedBuildingCount1 = 0;
    g = gSceneBlockMap;
    gw = g->width;
    gh = g->height;
    a = TRUE;
    if (Taxi_IsArriving() == 0) {
        if (Taxi_IsLeaving() == 0) {
            a = FALSE;
        }
    }
    count = 0;
    for (y = 0; y < gh; y++) {
        for (x = 0; x < gw; x++) {
            if (x < g->width && y < g->height && g->blocks != 0) {
                cell = (MapBlock *)g->blocks + (x + y * g->width);
            } else {
                cell = 0;
            }
            s32 t = reinterpret_cast<MapBlockAcre *>(cell)->getAcreId();
            switch (t) {
            case 0x1a:
            case 0x1b:
            case 0x1c:
                buf[1] = 0x500b;
                MapBlock_SetItem(cell, &buf[1], 7, 0, 0);
            }
            for (jj = 0; jj < 0x10; jj++) {
                for (ii = 0; ii < 0x10; ii++) {
                    p = MapBlock_GetItemPtr(cell, ii, jj, 0);
                    if (p != 0) {
                        BOOL f = FALSE;
                        if (*p >= 0x5000 && *p <= 0x5021) {
                            f = TRUE;
                        }
                        if (f) {
                            u32 idx;
                            FieldUnit_FromBlockUnit(&ax, &ay, x, y, ii, jj);
                            BOOL f2 = FALSE;
                            u32 v = *p;
                            if (v >= 0x5000 && v <= 0x5021) {
                                f2 = TRUE;
                            }
                            if (f2) {
                                idx = v & 0xfff;
                            } else {
                                idx = -1;
                            }
                            BuildingInfo *q;
                            if (idx < 0x22) {
                                q = &data_020d0a7c[idx];
                            } else {
                                q = data_020d0a7c;
                            }
                            BuildingInfo_Copy(&obj, q);
                            r24 = BuildingInfo_GetKind(&obj);
                            if (a == 0 || r24 != 2) {
                                go = 1;
                            } else {
                                go = 0;
                            }
                            BOOL m;
                            if (Item_IsFurniture(p) != 0) {
                                buf[2] = 0x501e;
                                s32 k = Item_GetFurnitureIndex(p);
                                m = (k == Item_GetFurnitureIndex(&buf[2])) ? 1 : 0;
                            } else {
                                m = (*p == 0x501e) ? 1 : 0;
                            }
                            if (m) {
                                if (GroundSeason_IsSnow() == 0) {
                                    go = 0;
                                }
                            }
                            if (go) {
                                if (FieldStructureMgr_SpawnBuilding(self, p, ax, ay, 1)) {
                                    if (r24 == 1) {
                                        sSpawnedBuildingCount1 = sSpawnedBuildingCount1 + 1;
                                    }
                                    count++;
                                }
                            }
                            BuildingInfo_Destroy(&obj);
                        }
                    }
                }
            }
        }
    }
    if (Scene_InTown()) {
        if (!gCommManager->isSlotActive(gCommManager->myAid)) {
            TownBlockMap *k = TownBlockMap_Get();
            if (Taxi_IsArriving() != 0 || Taxi_IsLeaving() != 0) {
                if (Town_FindTownHallFront(k, &tl, &bx, &by)) {
                    buf[0] = 0x501b;
                    FieldStructureMgr_SpawnBuilding(self, &buf[0], bx, by + 1, 0);
                }
            }
        }
    }
    return count;
}

s32 FieldStructureMgr_SpawnBuilding(FieldStructureMgr *self, u16 *pv, s32 x, s32 y, u8 flag) {
    VecFx32 vec;
    BuildingInfo obj;
    u32 idx;
    vec.x = 0;
    vec.y = 0;
    vec.z = 0;
    FieldPos_FromUnitCenter(&vec, x, y);
    BOOL f = FALSE;
    u32 v = *pv;
    if (v >= 0x5000 && v <= 0x5021) {
        f = TRUE;
    }
    if (f) {
        idx = v & 0xfff;
    } else {
        idx = -1;
    }
    BuildingInfo *q;
    if (idx < 0x22) {
        q = &data_020d0a7c[idx];
    } else {
        q = data_020d0a7c;
    }
    BuildingInfo_Copy(&obj, q);
    if (Actor::spawn(BuildingInfo_GetProfile(&obj), *pv, &vec, 0, 0) != 0) {
        if (flag != 0) {
            ((BlockMap *)gSceneBlockMap)->placeStructure(pv, x, y, 0);
            FieldStructureMgr_ApplyFootprint(self, pv, x, y);
        }
        BuildingInfo_Destroy(&obj);
        return 1;
    }
    BuildingInfo_Destroy(&obj);
    return 0;
}

s32 FieldStructureMgr_ApplyFootprint(FieldStructureMgr *self, u16 *b, s32 x, s32 y) {
    s32 va, vb, vc;
    StrBSizeData *p = StrBSize_Get(b);
    if (p != 0) {
        u32 n = p->getSolidUnitCount();
        u32 i;
        for (i = 0; i < n; i++) {
            if (p->getSolidUnit(&vc, &va, &vb, i)) {
                Ground_SetQuadrantsBlocked(x + va, y + vb, (u8)vc);
            }
        }
    }
    return 1;
}

void FieldStructureMgr_CreateHeap(FieldStructureMgr *self) { FieldStructureHeap_Create(0x1f000, 0); }

void FieldStructureMgr_DestroyHeap(FieldStructureMgr *self) { FieldStructureHeap_Destroy(); }

s32 Field_GetStructureTexSuffix() { return ((s8 *)sStructureTexSuffixes)[GroundSeason_IsSnow()]; }

u32 Field_GetSpawnedKind1Count() { return sSpawnedBuildingCount1; }

PlayerHouseTex *FieldStructureMgr_GetPlayerHouseTex() { return &sPlayerHouseTex; }

VillagerHouseTex *FieldStructureMgr_GetVillagerHouseTex() { return &sVillagerHouseTex; }

HouseLightUpDeco *FieldStructureMgr_GetLightUpDeco() { return &sHouseLightUpDeco; }

u32 Field_GetDoorExitMode() { return sDoorExitMode; }

void Field_SetDoorExitMode(u32 v) { sDoorExitMode = v; }

s32 Building_OpenDoorForEntryAt(VecFx32 *a) {
    BuildingActor *r = Building_FindNearPos(a);
    if (r != 0) {
        return r->openDoorForEntry();
    }
    return 0;
}

s32 Building_OpenDoorForExitAt(VecFx32 *a) {
    BuildingActor *r = Building_FindNearPos(a);
    if (r != 0) {
        return r->openDoorForExit();
    }
    return 0;
}

s32 VillagerHouse_TryOpenDoorForEntry(s32 a) {
    BuildingActor *r = BuildingList_FindByItem((u16)(a + 0x5001));
    if (r != 0) {
        return r->tryOpenDoorForEntry();
    }
    return 0;
}

s32 VillagerHouse_TryOpenDoorForExit(s32 a) {
    BuildingActor *r = BuildingList_FindByItem((u16)(a + 0x5001));
    if (r != 0) {
        return r->tryOpenDoorForExit();
    }
    return 0;
}

BuildingActor *Building_FindNearPos(VecFx32 *a) {
    BlockMap *g = gSceneBlockMap;
    s32 xy[2];
    if (g != 0) {
        FieldPos_ToUnit(&xy[0], &xy[1], a);
        for (s32 y = xy[1]; y >= xy[1] - 5; y--) {
            for (s32 x = xy[0] - 3; x <= xy[0] + 3; x++) {
                s32 hx = x >> 4;
                s32 hy = y >> 4;
                u16 *cell = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
                if (cell != 0) {
                    BOOL f = FALSE;
                    u16 v = *cell;
                    if (v >= 0x5000 && v <= 0x5021) {
                        f = TRUE;
                    }
                    if (f) {
                        BuildingActor *r = BuildingList_FindByItem(v);
                        if (r != 0) {
                            return r;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

s32 BuildingList_Add(void *p) {
    s32 i;
    for (i = 0; (u32)i < 0x20; i++) {
        if (sBuildingList[i] == 0) {
            sBuildingList[i] = (BuildingActor *)p;
            return 1;
        }
    }
    return 0;
}


s32 BuildingList_Remove(void *p) {
    s32 i = BuildingList_IndexOf(p);
    s32 m = -1;
    if (i != m) {
        sBuildingList[i] = 0;
        return 1;
    }
    return 0;
}

BuildingActor *BuildingList_FindByGrid(s32 a, s32 b) {
    s32 i;
    for (i = 0; (u32)i < 0x20; i++) {
        BuildingActor *e = sBuildingList[i];
        if (e != 0 && e->gridX == a && e->gridZ == b) {
            return e;
        }
    }
    return 0;
}

void *BuildingList_GetAt(s32 i) {
    if (i >= 0 && (u32)i < 0x20) {
        return sBuildingList[i];
    }
    return 0;
}

BuildingActor *BuildingList_FindByItem(u32 id) {
    s32 i;
    s32 z0 = 0;
    s32 z1 = 0;
    for (i = 0; (u32)i < 0x20; i++) {
        BuildingActor *e = sBuildingList[i];
        if (e != 0) {
            u16 *r = e->getItemId();
            BOOL ok;
            if (Item_IsFurniture(r) != 0) {
                u16 tmp;
                tmp = id;
                s32 a = Item_GetFurnitureIndex(r);
                ok = (a == Item_GetFurnitureIndex(&tmp)) ? 1 : z0;
            } else {
                ok = (*r == id) ? 1 : z1;
            }
            if (ok != 0) {
                return e;
            }
        }
    }
    return 0;
}

s32 BuildingList_IndexOf(void *p) {
    s32 i;
    for (i = 0; (u32)i < 0x20; i++) {
        if (p == sBuildingList[i]) {
            return i;
        }
    }
    return -1;
}

void BuildingList_Init() {
    u32 i;
    for (i = 0; i < 0x20; i++) {
        sBuildingList[i] = 0;
    }
}

void BuildingList_Clear() {
    u32 i;
    for (i = 0; i < 0x20; i++) {
        sBuildingList[i] = 0;
    }
}

}

VillagerHouseTex::VillagerHouseTex() {
    VillagerHouseTex_Clear(this);
}

VillagerHouseTex::~VillagerHouseTex() {}

extern "C" {

s32 VillagerHouseTex_Load(VillagerHouseTex *self) {
    u8 *str;
    void *heap = gFieldStructureHeap;
    u8 i = 0;
    s32 m3 = -4;
    do {
        s32 v = TownStyle_GetVillagerHouseStyle((u8 *)gSaveTownFlag.getHouseStyles(), i);
        s32 c = (s8)(v / 5 + 0x41);
        s32 rem = v % 5;
        Heap *h2 = gCurrentHeap;
        s32 a = Field_GetStructureTexSuffix();
        str = (u8 *)File_LoadAllocF(h2, m3, "/str/npcHsTex/%c/house_%c%d%c.nsbtx", c, c, rem, a);
        self->houseTextures[i] = (NNSG3dResTex *)NNS_G3dGetTex(str);
        if (Gfx3d_LoadTex(self->houseTextures[i], NULL)) {
            self->houseTextures[i] = (NNSG3dResTex *)Gfx3d_CopyTex(self->houseTextures[i], gFieldStructureHeap);
        }
        Mem_Free(str);
        str = (u8 *)File_LoadAllocF(gCurrentHeap, m3, "/str/npcHsTex/%c/light_%c%d.nsbtx", c, c, rem);
        self->lightTextures[i] = (NNSG3dResTex *)NNS_G3dGetTex(str);
        if (Gfx3d_LoadTexAndPltt(self->lightTextures[i], NULL)) {
            self->lightTextures[i] = (NNSG3dResTex *)Gfx3d_CopyTex(self->lightTextures[i], heap);
        }
        Mem_Free(str);
        i = i + 1;
    } while (i < 4);
    self->doorInAnim = func_021065f8(func_021065dc((u8 *)File_LoadAlloc("/str/obj_house_i.nsbca", heap, 4, 0)), 0);
    self->doorOutAnim = func_021065f8(func_021065dc((u8 *)File_LoadAlloc("/str/obj_house_o.nsbca", heap, 4, 0)), 0);
    return 1;
}

void VillagerHouseTex_Clear(VillagerHouseTex *o) {
    u32 i;
    for (i = 0; i < 4; i++) {
        o->houseTextures[i] = NULL;
        o->lightTextures[i] = NULL;
    }
    o->doorOutAnim = NULL;
    o->doorInAnim = o->doorOutAnim;
}

void *VillagerHouseTex_GetHouseTex(VillagerHouseTex *o, u32 i) { return o->houseTextures[i & 3]; }

void *VillagerHouseTex_GetLightTex(VillagerHouseTex *o, u32 i) { return o->lightTextures[i & 3]; }

void *VillagerHouseTex_GetDoorInAnim(VillagerHouseTex *o) { return o->doorInAnim; }

void *VillagerHouseTex_GetDoorOutAnim(VillagerHouseTex *o) { return o->doorOutAnim; }

}

HouseLightUpDeco::HouseLightUpDeco() {
    HouseLightUpDeco_Clear(this);
}

HouseLightUpDeco::~HouseLightUpDeco() {}

extern "C" {

void HouseLightUpDeco_Clear(HouseLightUpDeco *o) {
    u32 i;
    for (i = 0; i < 5; i++) {
        o->models[i] = NULL;
    }
    o->tex = NULL;
    o->texPattern = NULL;
    o->isLoaded = 0;
}

s32 HouseLightUpDeco_Load(HouseLightUpDeco *r) {
    NNSFndArchive arc;
    u32 i;
    BOOL z;
    HouseLightUpDeco_Clear(r);
    s32 c = TownState_FindEvent(NULL, 0x11);
    z = FALSE;
    if (c == ~z) {
        return z;
    }
    void *t = File_LoadAlloc("/str/npcHsX.arc", gFieldStructureHeap, 4, NULL);
    if (NNS_FndMountArchive(&arc, "STR", (u32 *)t) != 0) {
        for (i = 0; i < 5; i++) {
            Str_SPrintf(data_ov003_02235888, "STR:a/obj_x_house%d.nsbmd", i);
            u8 *p = NNS_G3dGetMdlSet((u8 *)NNS_FndGetArchiveFileByName(data_ov003_02235888));
            r->models[i] = p + *(s32 *)(p + *(u16 *)(p + 0xe) + 0xc);
        }
        r->tex = (NNSG3dResTex *)NNS_G3dGetTex((u8 *)NNS_FndGetArchiveFileByName("STR:a/obj_x_house0.nsbtx"));
        Gfx3d_LoadTexAndPltt(r->tex, NULL);
        r->texPattern = func_021066ac(func_02106690((u8 *)NNS_FndGetArchiveFileByName("STR:a/obj_x_deco.nsbtp")), 0);
        r->isLoaded = 1;
        NNS_FndUnmountArchive(&arc);
    }
    return 1;
}

void HouseLightUpDeco_Release(HouseLightUpDeco *p) {
    HouseLightUpDeco_Clear(p);
}

void *HouseLightUpDeco_GetTex(HouseLightUpDeco *p) {
    return p->tex;
}

void *HouseLightUpDeco_GetModel(HouseLightUpDeco *r, u32 idx) {
    if (idx < 5) {
        return r->models[idx];
    }
    return 0;
}

void *HouseLightUpDeco_GetTexPattern(HouseLightUpDeco *r) {
    return r->texPattern;
}

u8 HouseLightUpDeco_IsLoaded(HouseLightUpDeco *r) {
    return r->isLoaded;
}

}

PlayerHouseTex::PlayerHouseTex() {
    tex = NULL;
}

PlayerHouseTex::~PlayerHouseTex() {}

extern "C" {

s32 PlayerHouseTex_Load(PlayerHouseTex *self) {
    Heap *r4 = gCurrentHeap;
    s32 r3 = Field_GetStructureTexSuffix();
    void *t = File_LoadAllocF(r4, -4, "/str/house_pl/house_pl_%c.nsbtx", r3);
    if (t != 0) {
        self->tex = (NNSG3dResTex *)NNS_G3dGetTex((u8 *)t);
        Gfx3d_LoadPltt(self->tex, NULL);
        self->tex = (NNSG3dResTex *)Gfx3d_CopyTex(self->tex, gFieldStructureHeap);
        Mem_Free(t);
        return 1;
    }
    return 0;
}

void PlayerHouseTex_Release(PlayerHouseTex *p) {
}

}

extern "C" void StaticInit_unk_ov003_022187fc(void) {
    HOST_STATIC_CONSTRUCT(sPlayerHouseTex);
    HOST_STATIC_CONSTRUCT(sVillagerHouseTex);
    HOST_STATIC_CONSTRUCT(sHouseLightUpDeco);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_022187fc) {
    HOST_OVERLAY_VAR(sPlayerHouseTex),
    HOST_OVERLAY_VAR(sVillagerHouseTex),
    HOST_OVERLAY_VAR(sHouseLightUpDeco),
    HOST_OVERLAY_VAR(sFieldStructureMgrProfile),
    HOST_OVERLAY_VAR(sDoorExitMode),
    HOST_OVERLAY_VAR(sSpawnedBuildingCount1),
    HOST_OVERLAY_VAR(data_ov003_02235888),
    HOST_OVERLAY_VAR(sBuildingList),
    HOST_OVERLAY_VARS_END
};

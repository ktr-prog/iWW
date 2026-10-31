#include "types.h"
#include "gfx/VecFx32.h"
#include "town/TownBlockCell.h"
#include "town/SceneMapInfo.h"
#include "game/SceneInfo.h"
#include "net/CommManager.h"
#include "field/LooseSnowballs.h"
#include "field/SnowmanRecords.h"
#include "game/SceneWarp.h"
#include "save/SaveData.h"
#include "player/PlayerData.h"
#include "sys/ClockDateTime.h"
#include "town/TownBlockMap.h"
#include "town/TownMap.h"
#include "proto/main/unk_020b4828.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_02093ff0.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020af514.h"
#include "proto/main/unk_020afeb4.h"
#include "proto/main/unk_0204cc1c.h"

extern "C" {
BOOL GroundSeason_IsSnowPhase(s32 season);
void Clock_GetDateTime(ClockDateTime *p);
void DateTime_SubDays(ClockDateTime *p, s32 n);
s32 Date_DaysBetween(u8 *a, u8 *b);
s32 FX_Div(s32, s32);
s32 func_01ffcb0c(s32, s32);
u16 *MapBlock_GetItemPtr(void *cell, u32 x, u32 y, u32 z);
BOOL Item_IsSnowman(u16 *p);
s32 Item_GetSnowmanIndex(u16 *p);
}

extern SaveData gSaveData;


typedef BOOL (*EntryFn)(SceneSpawnGroup *, u8 *, u64);
extern "C" EntryFn sSceneSpawnGroupHandlers[];


struct EntryPair {
    u16 a;
    u16 b;
};


struct Vec3s {
    s16 x, y, z;
};

inline void SetVec(VecFx32 *v, s32 x, s32 y, s32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

extern "C" {
u32 Scene_GetCurrent();
BOOL Scene_InUnk6Or7();
BOOL Scene_InTown();
void Vec_RotateY(VecFx32 *, s32);

extern CommManager *gCommManager;
}

class ScenePlayerSpawn {
public:
    BOOL getSpawn(u32 i, BOOL mode, VecFx32 *pos, Vec3s *rot, u32 *out);
    inline void get(VecFx32 *pos, Vec3s *r, u32 *out) {
        Vec3s *q = &rot;
        SetVec(pos, x << 12 >> 4, y << 12 >> 4, z << 12 >> 4);
        r->x = q->x;
        r->y = q->y;
        r->z = q->z;
        *out = spawnParam;
    }

    u16 unk_00;
    s16 x;
    s16 y;
    s16 z;
    Vec3s rot;
    u16 unk_0e;
    u32 spawnParam;
};


BOOL ScenePlayerSpawn::getSpawn(u32 i, BOOL mode, VecFx32 *pos, Vec3s *rot_, u32 *out) {
    if (mode) {
        s32 idx = PlayerSession_GetDataIndex(i);
        if (idx < 4 && PlayerDataArray_IsUsed(gSaveData.players, PlayerSession_GetDataIndex(i))) {
            if (!gCommManager->isLocalSlot(i) || SceneWarp_HasNoPos(Scene_GetWarpRequest())) {
                (this + idx)->get(pos, rot_, out);
            } else {
                VecFx32 *v = SceneWarp_GetPos(Scene_GetWarpRequest());
                pos->x = v->x;
                pos->y = v->y;
                pos->z = v->z;
                s32 t = SceneWarp_GetAngle(Scene_GetWarpRequest());
                rot_->x = 0;
                rot_->y = t;
                rot_->z = 0;
                *out = SceneWarp_GetSpawnParam(Scene_GetWarpRequest());
            }
            return TRUE;
        }
    } else {
        if (gCommManager->isLocalSlot(i)) {
            if (SceneWarp_HasNoPos(Scene_GetWarpRequest())) {
                get(pos, rot_, out);
            } else {
                VecFx32 v;
                v.x = 0;
                v.y = 0;
                v.z = 0;
                if (!Scene_InTown() && SceneWarp_GetSpawnParam(Scene_GetWarpRequest()) == 0x800000) {
                    i &= 3;
                    v.x = (i << 10) - 0x800;
                    v.y = 0;
                    v.z = 0;
                    Vec_RotateY(&v, SceneWarp_GetAngle(Scene_GetWarpRequest()));
                }
                VecFx32 t;
                Vec_Add(&t, SceneWarp_GetPos(Scene_GetWarpRequest()), &v);
                pos->x = t.x;
                pos->y = t.y;
                pos->z = t.z;
                s32 u = SceneWarp_GetAngle(Scene_GetWarpRequest());
                rot_->x = 0;
                rot_->y = u;
                rot_->z = 0;
                *out = SceneWarp_GetSpawnParam(Scene_GetWarpRequest());
            }
            return TRUE;
        }
    }
    return FALSE;
}

BOOL SceneSpawnGroup::spawnPlayersAndCamera(u8 *idx, u64 start) {
    ScenePlayerSpawn *items = (ScenePlayerSpawn *)list;
    if (items != NULL && Scene_GetCurrent() != 0xd && Scene_GetCurrent() != 0xe && Scene_GetCurrent() != 0x2f) {
        if (Scene_InUnk6Or7()) {
            gCommManager->isSlotActive(gCommManager->myAid);
            for (u32 i = 0; i < 4; i++) {
                Vec3s rot;
                u32 v;
                VecFx32 pos;
                if (items->getSpawn(i, TRUE, &pos, &rot, &v)) {
                    PlayerActor_Spawn(i, &pos, &rot, v);
                }
            }
        } else {
            for (u32 i = 0; i < 4; i++) {
                Vec3s rot;
                u32 v;
                VecFx32 pos;
                if (items->getSpawn(i, FALSE, &pos, &rot, &v)) {
                    PlayerSession_SetGfxSlot(i, PlayerSession_FindFreeGfxSlot());
                    PlayerActor_Spawn(i, &pos, &rot, v);
                }
            }
        }
    }
    GameProc_CreateChild(0xb, gActorDefaultParent, 0, 0);
    return TRUE;
}

BOOL SceneSpawnGroup::createProcs(u8 *idx, u64 start) {
    u32 i = idx != NULL ? *idx : 0;
    EntryPair *p = (EntryPair *)list + i;
    BOOL ok = TRUE;
    for (;;) {
        GameProc_CreateChild(p->a, gActorDefaultParent, p->b, 0);
        p++;
        i = (u8)(i + 1);
        if (idx != NULL) {
            (*idx)++;
        }
        if (i >= count) {
            break;
        }
        if (idx != NULL) {
            u32 ms = ((OS_GetTick() - start) * 64) / 0x82ea;
            if (ms > 0x28) {
                ok = FALSE;
                break;
            }
        }
    }
    if (ok) {
        return TRUE;
    }
    return FALSE;
}

BOOL SceneSpawnList::run(u8 *entryIdx, u8 *subIdx, u64 start) {
    s32 i = entryIdx != NULL ? *entryIdx : 0;
    SceneSpawnGroup *e = groups + i;
    BOOL result = TRUE;
    for (; i < count;) {
        BOOL r = result;
        EntryFn f = sSceneSpawnGroupHandlers[e->kind];
        if (f != NULL) {
            r = f(e, subIdx, start);
        }
        if (r) {
            e++;
            i++;
            if (subIdx != NULL) {
                *subIdx = 0;
            }
            if (entryIdx != NULL) {
                (*entryIdx)++;
            }
            if (i >= count) {
                break;
            }
            if (entryIdx != NULL) {
                u32 ms = ((OS_GetTick() - start) * 64) / 0x82ea;
                if (ms > 0x28) {
                    result = FALSE;
                    break;
                }
            }
        } else {
            result = FALSE;
            break;
        }
    }
    if (result) {
        return TRUE;
    }
    return FALSE;
}

void SceneMapInfo::createMapModule() {
    GameProc_CreateChild(0xc, gActorDefaultParent, moduleParam, 0);
}

void SceneInfo::createSceneMapModule() {
    mapInfo->createMapModule();
}

BOOL SceneInfo::runSpawnList(u8 *entryIdx, u8 *subIdx, u64 start) {
    return spawnList->run(entryIdx, subIdx, start);
}

LooseSnowball::LooseSnowball() {
    posX = 0;
    posY = 0;
    posZ = 0;
    radius = 0x800;
}

LooseSnowball::~LooseSnowball() {}

LooseSnowballs::~LooseSnowballs() {}

SnowmanRecord::SnowmanRecord() {}

SnowmanRecord::~SnowmanRecord() {}

void SnowmanRecord::clear() {
    a0 = 0;
    a1 = 0;
    a2 = 0;
    b0 = 0;
    b1 = 0;
    b2 = 0;
    c5 = 0;
}

BOOL SnowmanRecord::isUsed() {
    if (b0 != 0 && b1 != 0) {
        return TRUE;
    }
    return FALSE;
}

void SnowmanRecord::build(u32 x, u32 y, u32 z) {
    b0 = x >> 7;
    b1 = y >> 7;
    b2 = z;
    c4 = 0;
    ClockDateTimeWords d;
    d.words[0] = 0;
    d.words[1] = 0;
    Clock_GetDateTime(&d.dt);
    if (d.dt.hour < 6) {
        DateTime_SubDays(&d.dt, 1);
    }
    a0 = d.dt.year;
    a1 = d.dt.month;
    a2 = d.dt.day;
    c5 = 1;
}

s32 SnowmanRecord::getHeadSize() {
    s32 t = b0 << 7;
    if (t == 0) {
        t = 0x1000;
    }
    s32 u = 0x1000;
    if (c4 == 1) {
        u = FX_Div(0x3000, 0x4000);
    } else if (c4 == 2) {
        u = FX_Div(u, 0x2000);
    }
    if (u > 0x1000) {
        u = 0x1000;
    }
    return func_01ffcb0c(t, u);
}

s32 SnowmanRecord::getBodySize() {
    s32 t = b1 << 7;
    if (t == 0) {
        t = 0x1000;
    }
    s32 u = 0x1000;
    if (c4 == 1) {
        u = FX_Div(0x3000, 0x4000);
    } else if (c4 == 2) {
        u = FX_Div(u, 0x2000);
    }
    if (u > 0x1000) {
        u = 0x1000;
    }
    return func_01ffcb0c(t, u);
}

u32 SnowmanRecord::getRank() {
    return b2;
}

s32 SnowmanRecord::getDaysSinceBuilt() {
    ClockDateTimeWords d;
    d.words[0] = 0;
    d.words[1] = 0;
    u8 e[4];
    u8 f[4];
    Clock_GetDateTime(&d.dt);
    if (d.dt.hour < 6) {
        DateTime_SubDays(&d.dt, 1);
    }
    e[2] = d.dt.year;
    e[1] = d.dt.month;
    e[0] = d.dt.day;
    f[2] = a0;
    f[1] = a1;
    f[0] = a2;
    return Date_DaysBetween(e, f);
}

SnowmanRecords::SnowmanRecords() {}

SnowmanRecords::~SnowmanRecords() {}

extern "C" BOOL Snowman_FindInTown(s32 *a, s32 *b, u32 idx) {
    TownBlockCell *cell;
    TownBlockMap *g = TownBlockMap_Get();
    for (s32 y = 1; y <= 4; y++) {
        for (s32 x = 1; x <= 4; x++) {
            if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                cell = &((TownBlockCell *)g->blocks)[y * g->width + x];
            } else {
                cell = NULL;
            }
            if (cell != NULL) {
                for (s32 j = 0; j < 16; j++) {
                    for (s32 i = 0; i < 16; i++) {
                        u16 *o = MapBlock_GetItemPtr(cell, i, j, 0);
                        if (o != NULL && Item_IsSnowman(o) && idx == (u32)Item_GetSnowmanIndex(o)) {
                            FieldUnit_FromBlockUnit(a, b, x, y, i, j);
                            return TRUE;
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

extern "C" BOOL Snowman_RemoveFromTown(u32 idx) {
    s32 a, b;
    if (Snowman_FindInTown(&a, &b, idx)) {
        TownBlockMap *p = TownBlockMap_Get();
        u16 h = 0xfff1;
        BlockMap_SetItemAtUnit(p, &h, a, b, 0);
        return TRUE;
    } else {
        return TRUE;
    }
}

void SnowmanRecords::updateDaily() {
    BOOL flag = FALSE;
    u32 v = GroundSeason_IsSnowPhase(((TownMap *)gSaveData.townMap)->groundSeason);
    for (u32 i = 0; i < 3; i++) {
        if (v == 0) {
            if (Snowman_RemoveFromTown(i)) {
                e[i].clear();
            }
        } else {
            SnowmanRecord *r = &e[i];
            if (r->isUsed()) {
                s32 n = r->getDaysSinceBuilt();
                BOOL x = r->c5 ? TRUE : flag;
                if (!x) {
                    if (n != 0) {
                        r->clear();
                    }
                } else if (n >= 3 || n < 0) {
                    if (Snowman_RemoveFromTown(i)) {
                        r->clear();
                    }
                } else {
                    r->c4 = n;
                }
            }
        }
    }
}

void SnowmanRecords::clearAll() {
    u32 i = 0;
    do {
        e[i].clear();
        i++;
    } while (i < 3);
}

BOOL SnowmanRecords::remove(u32 idx) {
    if (idx < 3) {
        SnowmanRecord *r = &e[idx];
        if (r->isUsed()) {
            r->clear();
            return TRUE;
        }
    }
    return FALSE;
}

s32 SnowmanRecords::add(u32 a, u32 b, u32 c) {
    for (u32 i = 0; i < 3; i++) {
        SnowmanRecord *r = &e[i];
        if (!r->isUsed()) {
            r->build(a, b, c);
            return i;
        }
    }
    return -1;
}

BOOL SnowmanRecords::getInfo(u32 idx, u32 *a, u32 *b, u32 *c, u8 *d, u8 *ee, u8 *f) {
    if (idx < 3) {
        SnowmanRecord *r = &e[idx];
        if (r->isUsed()) {
            if (a != NULL) {
                *a = r->getHeadSize();
            }
            if (b != NULL) {
                *b = r->getBodySize();
            }
            if (c != NULL) {
                *c = r->getRank();
            }
            if (d != NULL) {
                *d = r->a0;
            }
            if (ee != NULL) {
                *ee = r->a1;
            }
            if (f != NULL) {
                *f = r->a2;
            }
            return TRUE;
        }
    }
    return FALSE;
}

BOOL SnowmanRecords::isFull() {
    for (u32 i = 0; i < 3; i++) {
        if (!e[i].isUsed()) {
            return FALSE;
        }
    }
    return TRUE;
}

void SnowmanRecords::markUnplaced(u32 idx) {
    if (idx < 3) {
        if (e[idx].isUsed()) {
            e[idx].c5 = 0;
        }
    }
}

void LooseSnowballs::reset() {
    for (u32 i = 0; i < 2; i++) {
        items[i].posX = 0;
        items[i].posY = 0;
        items[i].posZ = 0;
        items[i].radius = 0x800;
    }
}

static BOOL SceneSpawnGroup_SpawnPlayers(SceneSpawnGroup *g, u8 *idx, u64 start) { return g->spawnPlayersAndCamera(idx, start); }
static BOOL SceneSpawnGroup_CreateProcs(SceneSpawnGroup *g, u8 *idx, u64 start) { return g->createProcs(idx, start); }

EntryFn sSceneSpawnGroupHandlers[3] = {SceneSpawnGroup_SpawnActors, SceneSpawnGroup_SpawnPlayers, SceneSpawnGroup_CreateProcs};

LooseSnowballs gLooseSnowballs;

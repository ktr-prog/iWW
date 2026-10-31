#include "types.h"
#include "host_labels.h"
#include "gfx/VecFx32.h"
#include "room/RoomFtrState.h"
#include "room/FtrActor.h"
#include "net/CommManager.h"
#include "room/FtrSwitch.h"
#include "room/HouseData.h"
#include "room/HouseRoom.h"
#include "room/FtrActorGrid.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020514a4.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_02060034.h"
#include "proto/main/unk_020a427c.h"
#include "proto/ov004/unk_ov004_02233074.h"
#include "proto/main/unk_0204cc1c.h"


class SpotReservation {
public:
    u8 active;
    VecFx32 pos;
    u8 sceneId;
    SpotReservation();
    ~SpotReservation();
    BOOL release();
    BOOL set(u32 tag, VecFx32 *p);
    void clear();
};

class SpotReservationTable {
public:
    SpotReservation slots[4];
    ~SpotReservationTable();
    BOOL tryReserve(s32 idx, u32 tag, VecFx32 *p);
    BOOL isFree(s32 idx, u32 tag, VecFx32 *p);
    BOOL release(s32 idx);
    BOOL set(s32 idx, u32 tag, VecFx32 *p);
};


class Unk_02052134_W { public: u32 a:1, b:4, c:4, d:1, e:1, f:16; };
class Unk_020520a8_W { public: u32 a:4, b:4, c:16; };
class Unk_0205218c_B { public: u8 a:6, b:1, c:1; };
class Unk_02051fcc_W { public: u16 a:6, b:1, c:4, d:4; };
class FtrStateRecord { public: u32 a:6, b:1, c:1, d:4, e:4, f:5, g:8, n:1, o:1, p:1; };
struct Unk_0205242c_Item {
    s16 a, b;
    Unk_0205242c_Item() { a = 0; b = 0; }
    Unk_0205242c_Item(s16 x, s16 y) { a = x; b = y; }
};
struct FtrFootprintShape { Unk_0205242c_Item *rows[4]; u8 count; };
class Unk_0205242c_Self { public: s32 a; s32 b; };
class FtrPlaceRecord {
public:
    u32 x : 4;
    u32 y : 4;
    u32 beat : 4;
    u32 layer : 1;
    u32 switchOn : 1;
    u32 isGyroid : 1;
    u32 item : 16;
    u32 pad : 1;
};

extern u8 gFieldSceneKind;
extern CommManager *gCommManager;
extern BlockMap *gSceneBlockMap;
#define gSaveHouse HOST_LABEL(u8 (*)[], gSaveHouse)
extern const FtrFootprintShape sFtrFootprint1x1;
extern const FtrFootprintShape sFtrFootprint2x1;
extern const FtrFootprintShape sFtrFootprint2x2;

inline BOOL IsOne(u8 v) { return v == 1 ? TRUE : FALSE; }
inline BOOL Range(u16 *p, u32 lo, u32 hi) {
    BOOL r = FALSE;
    if (*p >= lo && *p <= hi) r = TRUE;
    return r;
}

extern "C" {
u8 FtrActor_GetLayer(FtrActor *a);
s32 FtrActor_PredIsStereo(void *p);

u32 Scene_GetCurrent();
BlockMap *BlockMap_GetForArea(s32 a);
s32 Item_GetFurnitureIndex(void *p);
s32 Item_GetFurnitureDirection(void *p);
s32 SceneId_IsHouseRoom(u32 id);
s32 SceneId_GetHouseRoom(u32 id);
s32 SceneId_IsVillagerHouse(u32 id);
s32 SceneId_GetVillagerHouse(u32 id);
s32 SceneId_IsNookShop(u32 id);
s32 SceneId_GetNookShop(u32 id);

void FtrFootprint_Destruct(Unk_0205242c_Self *p);
}

extern "C" {
extern u8 data_020d0c08;
}

RoomFtrState sVillagerHouseFtrStates[8];
RoomFtrState sNookShopFtrStates[6];
RoomFtrState sScene10FtrState;
SpotReservationTable sSpotReservations;

extern const FtrFootprintShape *sFtrFootprintTables[3];


SpotReservation::SpotReservation() { clear(); }

SpotReservation::~SpotReservation() {}

SpotReservationTable::~SpotReservationTable() {}

void SpotReservation::clear() {
    active = 0;
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    sceneId = 0;
}

BOOL SpotReservation::set(u32 tag, VecFx32 *p) {
    active = 1;
    pos.x = p->x;
    pos.y = p->y;
    pos.z = p->z;
    sceneId = tag;
    return TRUE;
}

BOOL SpotReservation::release() {
    active = 0;
    return TRUE;
}

BOOL SpotReservationTable::set(s32 idx, u32 tag, VecFx32 *p) {
    if (idx < 4) return slots[idx].set(tag, p);
    return TRUE;
}

BOOL SpotReservationTable::release(s32 idx) {
    if (idx < 4) return slots[idx].release();
    return FALSE;
}

BOOL SpotReservationTable::isFree(s32 idx, u32 tag, VecFx32 *p) {
    if (idx < 4) {
        for (u32 i = 0; i < 4; i++) {
            SpotReservation *e = &slots[i];
            if ((s32)i != idx && e->active != 0 && tag == e->sceneId) {
                if (Vec_DistSq(&e->pos, p) < 0x2400) return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL SpotReservationTable::tryReserve(s32 idx, u32 tag, VecFx32 *p) {
    if (isFree(idx, tag, p)) return set(idx, tag, p);
    return FALSE;
}

FtrSwitchGrid::FtrSwitchGrid() { reset(); }

FtrSwitchGrid::~FtrSwitchGrid() {}

void FtrSwitchGrid::reset() {
    for (u32 i = 0; i < 16; i++) rows[i] = 0xffff;
}

BOOL FtrSwitchGrid::test(u32 x, u32 y) {
    x &= 0xf; y &= 0xf;
    s32 v = rows[y];
    if ((v >> x) & 1) return TRUE;
    return FALSE;
}

void FtrSwitchGrid::set(u32 x, u32 y, u32 set) {
    s32 xx = x & 0xf;
    s32 yy = y & 0xf;
    if (set) rows[yy] |= 1 << xx;
    else rows[yy] &= ~(1 << xx);
}

GyroidBeatTable::GyroidBeatTable() { clear(); }

GyroidBeatTable::~GyroidBeatTable() {}

void GyroidBeatTable::clear() {
    for (u32 i = 0; i < 4; i++) {
        positions[i].lo = 0;
        positions[i].hi = 0;
    }
    usedMask[0] = 0;
    for (u32 j = 0; j < 2; j++) beats[j] = 0;
}

s32 GyroidBeatTable::get(u32 x, u32 y) {
    for (u32 i = 0; i < 4; i++) {
        if ((usedMask[i >> 3] >> (i & 7)) & 1) {
            if (x == positions[i].lo && y == positions[i].hi) {
                return (beats[i >> 1] >> ((i & 1) << 2)) & 0xf;
            }
        }
    }
    return -1;
}

BOOL GyroidBeatTable::remove(u32 x, u32 y) {
    for (u32 i = 0; i < 4; i++) {
        if ((usedMask[i >> 3] >> (i & 7)) & 1) {
            if (x == positions[i].lo && y == positions[i].hi) {
                positions[i].lo = 0;
                positions[i].hi = 0;
                usedMask[i >> 3] &= ~(1 << (i & 7));
                beats[i >> 1] &= ~(0xf << ((i & 1) << 2));
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL GyroidBeatTable::set(u32 x, u32 y, u32 val) {
    if (val >= 16) return FALSE;
    if (get(x, y) == -1) {
        for (u32 i = 0; i < 4; i++) {
            if (!((usedMask[i >> 3] >> (i & 7)) & 1)) {
                u32 sh = (i & 1) << 2;
                positions[i].lo = (u8)x;
                positions[i].hi = (u8)y;
                beats[i >> 1] &= ~(0xf << sh);
                { u32 t = *(volatile u8 *)&beats[i >> 1]; t |= (val <<= sh); beats[i >> 1] = t; }
                usedMask[i >> 3] |= 1 << (i & 7);
                return TRUE;
            }
        }
    } else {
        for (u32 i = 0; i < 4; i++) {
            if ((usedMask[i >> 3] >> (i & 7)) & 1) {
                if (x == positions[i].lo && y == positions[i].hi) {
                    u32 sh = (i & 1) << 2;
                    beats[i >> 1] &= ~(0xf << sh);
                    { u32 t = *(volatile u8 *)&beats[i >> 1]; t |= (val <<= sh); beats[i >> 1] = t; }
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

RoomFtrState::RoomFtrState() { reset(); }

RoomFtrState::~RoomFtrState() {}

void RoomFtrState::reset() {
    for (u32 i = 0; i < 2; i++) switchGrids[i].reset();
    gyroidBeats.clear();
}

BOOL RoomFtrState::getSwitch(u32 x, u32 y, u32 idx) { return switchGrids[idx].test(x, y); }

void RoomFtrState::setSwitch(u32 x, u32 y, u32 idx, u8 v) { switchGrids[idx].set(x, y, v); }

extern "C" void RoomFtrState_ResetAll() {
    for (u32 i = 0; i < 8; i++) sVillagerHouseFtrStates[i].reset();
    for (u32 i = 0; i < 6; i++) sNookShopFtrStates[i].reset();
    sScene10FtrState.reset();
}

extern "C" BOOL RoomFtrState_ResetScene(u32 v) {
    RoomFtrState *p = RoomFtrState_GetForScene(v);
    if (p) {
        p->reset();
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL RoomFtrState_ResetVillagerHouse(u32 idx) { return RoomFtrState_ResetScene((u8)(data_020d0c08 + idx)); }

s32 RoomFtrState::getGyroidBeat(u32 a, u32 b) { return gyroidBeats.get(a, b); }

BOOL RoomFtrState::setGyroidBeat(u32 a, u32 b, u32 c) { return gyroidBeats.set(a, b, c); }

BOOL RoomFtrState::removeGyroidBeat(u32 a, u32 b) { return gyroidBeats.remove(a, b); }


extern "C" RoomFtrState *RoomFtrState_GetForScene(u32 id) {
    if (SceneId_IsHouseRoom(id)) {
        HouseRoom *room = ((HouseData *)gSaveHouse)->getRoom(SceneId_GetHouseRoom(id));
        if (room) {
            return room->getFtrState();
        }
    } else if (SceneId_IsVillagerHouse(id)) {
        return &sVillagerHouseFtrStates[SceneId_GetVillagerHouse(id)];
    } else if (SceneId_IsNookShop(id)) {
        return &sNookShopFtrStates[SceneId_GetNookShop(id)];
    } else if (id == 10) {
        return &sScene10FtrState;
    }
    return 0;
}

extern "C" s32 RoomFtrState_GetSwitch(s32 a, s32 b, s32 c, u32 d) {
    RoomFtrState *r = RoomFtrState_GetForScene(d);
    if (r) return r->getSwitch(a, b, c);
    return 0;
}

extern "C" void RoomFtrState_SetSwitch(s32 a, s32 b, s32 c, u8 d, u8 e) {
    RoomFtrState *r = RoomFtrState_GetForScene(e);
    if (r) {
        r->setSwitch(a, b, c, d);
    }
}

extern "C" s32 RoomFtrState_GetGyroidBeat(s32 a, s32 b, u32 c) {
    RoomFtrState *r = RoomFtrState_GetForScene(c);
    if (r) return r->getGyroidBeat(a, b);
    return -1;
}

extern "C" s32 RoomFtrState_SetGyroidBeat(s32 a, s32 b, s32 c, u32 d) {
    RoomFtrState *r = RoomFtrState_GetForScene(d);
    if (r) return r->setGyroidBeat(a, b, c);
    return 0;
}

extern "C" s32 RoomFtrState_RemoveGyroidBeat(s32 a, s32 b, u32 c) {
    RoomFtrState *r = RoomFtrState_GetForScene(c);
    if (r) return r->removeGyroidBeat(a, b);
    return 0;
}

extern "C" Unk_0205242c_Self *FtrFootprint_Init(Unk_0205242c_Self *p, u16 *q) {
    p->a = -1;
    s32 r = Item_GetFurnitureIndex(q);
    s32 m = -1;
    if (r != m) {
        p->a = FtrInfo_GetUnk05(r);
        p->b = Item_GetFurnitureDirection(q);
    }
    return p;
}

extern "C" void FtrFootprint_Destruct(Unk_0205242c_Self *) {}

extern "C" s32 FtrFootprint_GetTileCount(Unk_0205242c_Self *p) {
    if (p->a < 3) {
        return sFtrFootprintTables[p->a]->count;
    }
    return 0;
}

extern "C" Unk_0205242c_Item *FtrFootprint_GetTileOffset(Unk_0205242c_Self *p, u32 idx) {
    if (p->a < 3 && idx < FtrFootprint_GetTileCount(p)) {
        return &sFtrFootprintTables[p->a]->rows[p->b][idx & 3];
    }
    static Unk_0205242c_Item dflt;
    return &dflt;
}

Unk_0205242c_Item data_021c4e34(0, 0);
Unk_0205242c_Item data_021c4e3c[2] = { Unk_0205242c_Item(0, 0), Unk_0205242c_Item(1, 0) };
const FtrFootprintShape *sFtrFootprintTables[3] = { &sFtrFootprint1x1, &sFtrFootprint2x1, &sFtrFootprint2x2 };
extern const FtrFootprintShape sFtrFootprint2x2 = { { data_021c4e8c, data_021c4e8c, data_021c4e8c, data_021c4e8c }, 4 };
extern const FtrFootprintShape sFtrFootprint2x1 = { { data_021c4e3c, data_021c4e44, data_021c4e54, data_021c4e4c }, 2 };
extern const FtrFootprintShape sFtrFootprint1x1 = { { &data_021c4e34, &data_021c4e34, &data_021c4e34, &data_021c4e34 }, 1 };
Unk_0205242c_Item data_021c4e44[2] = { Unk_0205242c_Item(0, 0), Unk_0205242c_Item(0, -1) };
Unk_0205242c_Item data_021c4e54[2] = { Unk_0205242c_Item(0, 0), Unk_0205242c_Item(-1, 0) };
s32 sSpotReserveResult;
Unk_0205242c_Item data_021c4e4c[2] = { Unk_0205242c_Item(0, 0), Unk_0205242c_Item(0, 1) };
Unk_0205242c_Item data_021c4e8c[4] = { Unk_0205242c_Item(0, 0), Unk_0205242c_Item(1, 0), Unk_0205242c_Item(0, 1), Unk_0205242c_Item(1, 1) };

extern "C" s32 FtrSync_ApplyState(u8 a, s32 b, s32 c, s32 d, u8 e, bool f, bool g, bool h, volatile u8 i) {
    if (IsOne(gFieldSceneKind) && a == Scene_GetCurrent()) {
        FtrActor *o = FtrActorGrid_GetInstance()->getActor(b, c, d);
        if (o) {
            return o->changeAct(e, i);
        }
    }
    BlockMap *t = BlockMap_GetForArea(a);
    if (t) {
        s32 hb = b >> 4;
        s32 hc = c >> 4;
        u16 *p = (u16 *)BlockMap_GetItemPtr(t, hb, hc, b - (hb << 4), c - (hc << 4), 0);
        if (p && Range(p, 0x45dc, 0x47d7)) {
            if (f) {
                RoomFtrState_SetGyroidBeat(b, c, (u8)(i & 0xf), a);
            } else {
                RoomFtrState_RemoveGyroidBeat(b, c, a);
            }
        }
    }
    RoomFtrState_SetSwitch(b, c, d, f, a);
    if (g) {
        if (f) {
            u32 t = i;
            u16 v = t < 0x46 ? (u16)(t + 0x1323) : 0x1323;
            HouseRoom_SetSongForScene(a, &v);
        } else if (!h) {
            HouseRoom_ClearSongForScene(a);
        }
    }
    return 1;
}

extern "C" void FtrSync_OnStateRecord(u32 *pp) {
    FtrStateRecord *p = (FtrStateRecord *)pp;
    if (p->n == 1) {
        FtrSync_ApplyState(p->a, p->d, p->e, (u8)p->b, p->f, p->c, p->o, p->p, p->g);
        u32 w = *pp;
        w &= 0xdfffffff;
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(&w), 4);
        g->endRecord(0x18, 4);
    } else {
        FtrSync_ApplyState(p->a, p->d, p->e, (u8)p->b, p->f, p->c, p->o, p->p, p->g);
    }
}

extern "C" void FtrSync_OnRoomLightRecord(Unk_0205218c_B *p) {
    u32 a = p->a;
    BOOL b = p->b ? 1 : 0;
    if (p->c == 1) {
        ((HouseData *)(gSaveHouse))->setRoomFlag(a, b);
        Unk_0205218c_B t;
        t = *p;
        t.c = 0;
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(&t), 1);
        g->endRecord(0x19, 4);
    } else {
        ((HouseData *)(gSaveHouse))->setRoomFlag(a, b);
    }
}

extern "C" void FtrSync_OnRemoveRecord(s32 a, Unk_02052134_W *w) {
    u16 t = w->f;
    BOOL e = w->e ? 1 : 0;
    BOOL d = w->d ? 1 : 0;
    FtrSync_RemoveFurniture(a, w->b, w->c, (u8)w->a, e, &t, d, 0);
}

extern "C" void FtrSync_OnPlaceRecord(s32 a, FtrPlaceRecord *w) {
    u16 t = w->item;
    BOOL j = w->switchOn ? 1 : 0;
    BOOL k = w->isGyroid ? 1 : 0;
    FtrSync_PlaceFurniture(a, w->x, w->y, (u8)w->layer, j, k, (u8)w->beat, &t, 0);
}

extern "C" void FtrSync_OnTopItemRecord(s32 a, Unk_020520a8_W *w) {
    u16 t = w->c;
    FtrSync_SetTopItem(a, w->a, w->b, &t, 0);
}

static BOOL FtrActor_IsGyroidPred(FtrActor *o) { return o->isGyroid(); }

extern "C" void FtrSync_ToggleGyroidAt(u8 a, s32 b, s32 c, u8 d, u8 e) {
    if (a == Scene_GetCurrent() && IsOne(gFieldSceneKind)) {
        {
            FtrActor *o = FtrActorGrid_GetInstance()->getActor(b, c, d);
            if (o) {
                if (o->switchState.isOn() == 0) {
                    if ((u32)FtrMgr_CountSwitchedOn(FtrActor_IsGyroidPred) >= 4) {
                        FtrActor *r = FtrMgr_SwitchOffRandom(FtrActor_IsGyroidPred, 0);
                        if (r) {
                            FtrSync_ChangeAct(r, 0, 0xff, e);
                        }
                    }
                    FtrSync_ChangeActAt(b, c, d, 1, 0xff, e, 1);
                } else {
                    FtrSync_ChangeActAt(b, c, d, 0, 0xff, e, 1);
                }
            }
        }
    }
}

extern "C" void FtrSync_OnToggleRecord(Unk_02051fcc_W *p) {
    FtrSync_ToggleGyroidAt(p->a, p->c, p->d, p->b, 1);
}

extern "C" void SpotSync_OnReserveRequest(u8 *p, s32 q) {
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    v.x = p[0] << 9;
    v.z = p[1] << 9;
    if (sSpotReservations.tryReserve(q, p[2], (VecFx32 *)&v)) {
        CommManager *g = gCommManager;
        g->beginRecord();
        g->endRecord(0x1f, q);
    } else {
        CommManager *g = gCommManager;
        g->beginRecord();
        g->endRecord(0x20, q);
    }
}

extern "C" void SpotSync_OnReserveReply(s32 x) {
    if (x) sSpotReserveResult = 1;
    else sSpotReserveResult = 2;
}

extern "C" s32 SpotSync_OnRelease(s32 x) {
    return sSpotReservations.release(x);
}

extern "C" s32 FtrSync_SendState(u32 a, u32 b, u32 c, u32 d, u8 e, u8 f, s32 g) {
    u32 w;
    u32 r5 = (g != 4) ? 1 : 0;
    FtrActor *o = FtrActorGrid_GetInstance()->getActor(a, b, c);
    if (!o) return 0;
    if (gCommManager->isOnline() && o && !((FtrActor *)(o))->isPreview()) {
        u32 t = o->getActSwitchState(d);
        w = (w & ~0x3f) | (Scene_GetCurrent() & 0x3f);
        c = c & 1;
        w = (w & ~0x40) | (c << 6);
        t = t & 1;
        w = (w & ~0x80) | (t << 7);
        a = a & 0xf;
        w = (w & 0xfffff0ff) | (a << 8);
        b = b & 0xf;
        w = (w & 0xffff0fff) | (b << 12);
        d = d & 0x1f;
        w = (w & 0xffe0ffff) | (d << 16);
        w = (w & 0xe01fffff) | ((e & 0xff) << 21);
        w = (w & 0x7fffffff) | ((f & 1) << 31);
        r5 = r5 & 1;
        w = (w & 0xdfffffff) | (r5 << 29);
        w = (w & 0xbfffffff) | ((FtrActor_PredIsStereo(o) & 1) << 30);
        CommManager *g2 = gCommManager;
        g2->beginRecord();
        g2->writeRecord((u8 *)(&w), 4);
        g2->endRecord(0x18, g);
    }
    return 1;
}

extern "C" s32 FtrSync_ChangeAct(FtrActor *a, s32 b, u8 c, u8 d) {
    s32 x, y;
    if (IsOne(gFieldSceneKind)) {
        if (a->findOwnTile(&x, &y, 0, 0)) {
            return FtrSync_ChangeActAt(x, y, FtrActor_GetLayer(a), b, c, d, 1);
        }
    }
    return 0;
}

extern "C" s32 FtrSync_ChangeActAt(s32 a, s32 b, s32 c, s32 d, u8 e, u8 f, u8 g) {
    if (!IsOne(gFieldSceneKind)) return 0;
    FtrActor *o = FtrActorGrid_GetInstance()->getActor(a, b, c);
    if (!o) return 0;
    o->changeAct(d, e);
    if (g) {
        return FtrSync_SendState(a, b, c, d, o->getActAid(), f, 4);
    }
    return 1;
}

extern "C" s32 FtrSync_RequestAct(FtrActor *a, s32 b, u8 c, u8 d) {
    s32 x, y;
    if (IsOne(gFieldSceneKind)) {
        if (a->findOwnTile(&x, &y, 0, 0)) {
            return FtrSync_RequestActAt(x, y, FtrActor_GetLayer(a), b, c, d, 1);
        }
    }
    return 0;
}

extern "C" s32 FtrSync_RequestActAt(s32 a, s32 b, s32 c, s32 d, u8 e, u8 f, u8 g) {
    CommManager *s = gCommManager;
    FtrActor *p;
    if (s->isOnline() == 0 || s->isMyAid(0) != 0) {
        return FtrSync_ChangeActAt(a, b, c, d, e, f, g);
    }
    if (!(gFieldSceneKind == 1 ? TRUE : FALSE)) {
        return 0;
    }
    p = FtrActorGrid_GetInstance()->getActor(a, b, c);
    if (p == NULL) {
        return 0;
    }
    if (g != 0) {
        if (FtrSync_SendState(a, b, c, d, e, f, 0) != 0) {
            p->netRequestPending = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

extern "C" void FtrSync_PlaceFurniture(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, u16 *h, u8 i) {
    BlockMap *o;
    u16 loc[3];
    Unk_0205242c_Self pk;
    FtrPlaceRecord bits;
    s32 x, y;
    s32 off;
    u32 idx;
    loc[0] = *h;
    if ((gFieldSceneKind == 1 ? TRUE : FALSE) && a == Scene_GetCurrent()) {
        o = gSceneBlockMap;
    } else {
        o = BlockMap_GetForArea(a);
    }
    if (o == NULL) {
        return;
    }
    FtrFootprint_Init(&pk, h);
    off = 0;
    for (idx = 0; idx < FtrFootprint_GetTileCount(&pk); idx++) {
        u16 *src;
        x = b + *(s16 *)((u8 *)FtrFootprint_GetTileOffset(&pk, idx) + off);
        y = c + ((s16 *)FtrFootprint_GetTileOffset(&pk, idx))[1];
        if (idx == 0) {
            src = &loc[0];
        } else {
            loc[2] = 0xf031;
            src = &loc[2];
        }
        loc[1] = *src;
        if (BlockMap_SetItemAtUnit(o, &loc[1], x, y, d) == 0) {
            FtrFootprint_Destruct(&pk);
            return;
        }
        ((void (*)(s32, s32, s32, s32, s32))RoomFtrState_SetSwitch)(x, y, d, e, a);
        if (f != 0 && e != 0 && idx == 0) {
            RoomFtrState_SetGyroidBeat(x, y, g, a);
        }
    }
    if (gCommManager->isOnline() != 0 && i != 0) {
        CommManager *t;
        bits.x = b;
        bits.y = c;
        bits.beat = g & 0xf;
        bits.layer = d;
        bits.switchOn = e;
        bits.isGyroid = f;
        bits.item = loc[0];
        t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)(&bits), 4);
        t->endRecord(0x1c, 4);
    }
    FtrFootprint_Destruct(&pk);
}

extern "C" void FtrSync_RemoveFurniture(s32 a, s32 b, s32 c, s32 d, s32 e, u16 *f, s32 g, u8 h) {
    BlockMap *o;
    u32 idx;
    s32 x, y;
    BOOL k;
    u16 loc[3];
    Unk_0205242c_Self pk;
    u32 bits;
    loc[0] = *f;
    if ((gFieldSceneKind == 1 ? TRUE : FALSE) && a == Scene_GetCurrent()) {
        o = gSceneBlockMap;
    } else {
        o = BlockMap_GetForArea(a);
    }
    if (o == NULL) {
        return;
    }
    FtrFootprint_Init(&pk, f);
    k = FALSE;
    if (*f >= 0x45dc && *f <= 0x47d7) {
        k = TRUE;
    }
    for (idx = 0; idx < FtrFootprint_GetTileCount(&pk); idx++) {
        x = b + ((s16 *)FtrFootprint_GetTileOffset(&pk, idx))[0];
        y = c + ((s16 *)FtrFootprint_GetTileOffset(&pk, idx))[1];
        loc[1] = 0xfff1;
        if (BlockMap_SetItemAtUnit(o, &loc[1], x, y, d) == 0 ? TRUE : FALSE) {
            FtrFootprint_Destruct(&pk);
            return;
        }
        if (g != 0 && d == 0) {
            loc[2] = 0xfff1;
            if (BlockMap_SetItemAtUnit(o, &loc[2], x, y, 1) == 0 ? TRUE : FALSE) {
                FtrFootprint_Destruct(&pk);
                return;
            }
        }
        ((void (*)(s32, s32, s32, s32, s32))RoomFtrState_SetSwitch)(x, y, d, e, a);
        if (g != 0 && d == 0) {
            ((void (*)(s32, s32, s32, s32, s32))RoomFtrState_SetSwitch)(x, y, 1, e, a);
        }
        if (k != 0 && e != 0) {
            RoomFtrState_RemoveGyroidBeat(x, y, a);
        }
    }
    if (gCommManager->isOnline() != 0 && h != 0) {
        CommManager *t;
        bits = (bits & ~1) | (d & 1);
        bits = (bits & ~0x1e) | ((b & 0xf) << 1);
        bits = (bits & 0xfffffe1f) | ((c & 0xf) << 5);
        bits = (bits & 0xfffffdff) | ((g & 1) << 9);
        bits = (bits & 0xfffffbff) | ((e & 1) << 10);
        bits = (bits & 0xf80007ff) | ((loc[0] & 0xffff) << 11);
        t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)(&bits), 4);
        t->endRecord(0x1b, 4);
    }
    FtrFootprint_Destruct(&pk);
}

extern "C" void FtrSync_SetTopItem(s32 a, s32 b, s32 c, u16 *d, u8 f) {
    BlockMap *o;
    if ((gFieldSceneKind == 1 ? TRUE : FALSE) && a == Scene_GetCurrent()) {
        o = gSceneBlockMap;
    } else {
        o = BlockMap_GetForArea(a);
    }
    if (o != NULL && BlockMap_SetItemAtUnit(o, d, b, c, 1) != 0 && f != 0 && gCommManager->isOnline() != 0) {
        u32 bits;
        CommManager *t;
        bits = (bits & ~0xf) | (b & 0xf);
        bits = (bits & ~0xf0) | ((c & 0xf) << 4);
        bits = (bits & 0xff0000ff) | ((*d & 0xffff) << 8);
        t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)(&bits), 4);
        t->endRecord(0x1a, 4);
    }
}

extern "C" void FtrSync_SendRoomLight(s32 a, s32 b, s32 c) {
    if (gCommManager->isOnline() != 0) {
        volatile u8 bits;
        BOOL f;
        CommManager *t;
        bits = (bits & ~0x3f) | (a & 0x3f);
        bits = (bits & ~0x40) | ((b & 1) << 6);
        f = TRUE;
        if (c == 4) {
            f = FALSE;
        }
        bits = (bits & ~0x80) | ((f & 1) << 7);
        t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)((void *)&bits), 1);
        t->endRecord(0x19, c);
    }
}

extern "C" void FtrSync_ApplyRoomLight(s32 a, s32 b) {
    ((HouseData *)(gSaveHouse))->setRoomFlag(a, b);
    FtrSync_SendRoomLight(a, b, 4);
}

extern "C" void FtrSync_SetRoomLight(s32 a, s32 b) {
    CommManager *s = gCommManager;
    if (s->isOnline() == 0 || s->isMyAid(0) != 0) {
        FtrSync_ApplyRoomLight(a, b);
    } else {
        FtrSync_SendRoomLight(a, b, 0);
    }
}

extern "C" void FtrSync_RequestToggleGyroidAt(s32 a, s32 b, s32 c, s32 d) {
    if (gCommManager->isOnline() == 0 || NetArea_IsLocalOwner() != 0) {
        ((void (*)(s32, s32, s32, s32, s32))FtrSync_ToggleGyroidAt)(a, b, c, d, 1);
    } else {
        volatile u16 bits;
        CommManager *t;
        u8 *q = (u8 *)FtrActorGrid_GetInstance()->getActor(b, c, d);
        if (q != NULL) {
            q[0x779] = 1;
        }
        bits = (bits & ~0x3f) | (a & 0x3f);
        bits = (bits & ~0x40) | ((d & 1) << 6);
        bits = (bits & ~0x780) | (((u16)b & 0xf) << 7);
        bits = (bits & ~0x7800) | (((u16)c & 0xf) << 11);
        t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)((void *)&bits), 2);
        t->endRecord(0x1d, 6);
    }
}

extern "C" void FtrSync_RequestToggleGyroid(s32 a, VecFx32 *b, s32 c) {
    s32 x, y;
    FieldPos_ToUnit(&x, &y, b);
    FtrSync_RequestToggleGyroidAt(a, x, y, c);
}

extern "C" void SpotSync_RequestReserve(s32 *p) {
    CommManager *s;
    u8 buf[3];
    sSpotReserveResult = 0;
    s = gCommManager;
    if (s->isOnline() == 0 || s->isMyAid(0) != 0) {
        if (sSpotReservations.tryReserve(0, Scene_GetCurrent(), (VecFx32 *)p) != 0) {
            sSpotReserveResult = 1;
        } else {
            sSpotReserveResult = 2;
        }
    } else {
        CommManager *t;
        buf[0] = p[0] >> 9;
        buf[1] = p[2] >> 9;
        buf[2] = Scene_GetCurrent();
        t = gCommManager;
        t->beginRecord();
        t->writeRecord((u8 *)(buf), 3);
        t->endRecord(0x1e, 0);
    }
}

extern "C" u32 SpotSync_GetReserveResult() {
    return sSpotReserveResult;
}

extern "C" void SpotSync_RequestStandUpSpot(s32 *p) { SpotSync_RequestReserve(p); }

extern "C" u32 SpotSync_GetStandUpSpotResult() { return SpotSync_GetReserveResult(); }

extern "C" void SpotSync_Release(s32 aid) {
    CommManager *s;
    sSpotReserveResult = 0;
    s = gCommManager;
    if (s->isOnline() == 0 || s->isMyAid(0) != 0 || s->isMyAid(4) != 0) {
        sSpotReservations.release(aid);
    } else {
        CommManager *t = gCommManager;
        t->beginRecord();
        t->endRecord(0x21, 0);
    }
}


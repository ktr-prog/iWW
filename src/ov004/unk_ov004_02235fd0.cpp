#include "uptr.h"
#include "host_labels.h"
#include "proto/main/unk_0202fa70.h"
#include "types.h"
#include "gfx/Mtx43.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "actor/ActorListNode.h"
#include "actor/Actor.h"
#include "room/HouseData.h"
#include "actor/ActorProfile.h"
#include "sys/ProcProfile.h"
#include "game/CollisionState.h"
#include "actor/ActorCollider.h"
#include "actor/ActorPlacedCollider.h"
#include "game/GroundInfo.h"
#include "game/GroundInfoBase.h"
#include "gfx/AnimModel.h"
#include "gfx/CachedModel.h"
#include "gfx/Model.h"
#include "gfx/TwoLayerAnimModel.h"
#include "snd/SndEnvChannel.h"
#include "sys/Heap.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/ov004/unk_ov004_02235fd0.h"
#include "game/BoxCollider.h"
#include "game/FxVec3.h"
#include "snd/CreatureSndChannel.h"
#include "town/BlockMap.h"
#include "proto/main/unk_0204cc1c.h"

#pragma opt_loop_invariants off

class HouseRoach : public Actor {
public:
    HouseRoach();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~HouseRoach();

    Actor *getNearestCharacter();
    void setProbePoints(s32 dist, s32 delta);
    u8 probeWalls();
    void playSe(u32 sel);
    BOOL release();
    BOOL draw();
    BOOL checkStomped();
    BOOL checkHeight();
    BOOL execute();
    void updateAppear();
    void updateCollision();
    void updateState();
    BOOL move();
    void updateHitBox();
    void updateCrawl();
    BOOL setup();
    void setSoundState(s32 v);
    s32 getSoundState();


    /* 0xd4 */ s32 crawlSpeed;
    /* 0xd8 */ s32 jumpSpeed;
    /* 0xdc */ CollisionState moveResult;
    /* 0x10c */ s32 roachState;
    /* 0x110 */ s32 lifeState;
    /* 0x114 */ CreatureSndChannel sound;
    /* 0x120 */ AnimModel model;
    /* 0x1d8 */ ActorPlacedCollider hitBox;
    /* 0x228 */ s16 spawnAngle;
    /* 0x22a */ u8 isJumping;
    /* 0x22b */ u8 pad_22b;
    /* 0x22c */ s16 stateTimer;
    /* 0x22e */ s16 jumpTimer;
    /* 0x230 */ FxVec3 probePoints[2];
    /* 0x248 */ FxVec3 probePrevPoints[2];
    /* 0x260 */ s8 wallProbe;
    /* 0x261 */ u8 pad_261;
    /* 0x262 */ u8 wallTurnDir;
    /* 0x263 */ u8 wantsCrawlSe;
    /* 0x264 */ s32 soundState;
};

class HouseRoachManager : public GameProc {
public:
    HouseRoachManager();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual ~HouseRoachManager();
};

extern "C" {
extern CommManager *gCommManager;
#define gSaveHouse HOST_LABEL(u8 (*)[], gSaveHouse)
extern BlockMap *gSceneBlockMap;
extern s16 data_02135f44[];

BOOL Scene_InHouseRoom();
s32 Scene_GetHouseRoom();
u8 *func_02106788(u8 *p);
u8 *func_021067a4(u8 *p, u32 i);
s32 Item_GetFurnitureIndex(u16 *p);
BOOL Item_IsFurniture(u16 *p);
s32 Vec_DistXZ(VecFx32 *a, VecFx32 *b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 FX_Div(s32 a, s32 b);
BOOL BoxCollider_Register(BoxCollider *n, s32 a, s32 b, s32 c, VecFx32 *pos, s16 angle, VecFx32 *scale);
BOOL BoxCollider_Unregister(BoxCollider *n);
void NNSi_G3dModifyPolygonAttrMask(u8 *res, BOOL on, u32 mask);
}

extern "C" ProcProfile sHouseRoachManagerProfile;
extern "C" char sHouseRoachModelPath[0x18];
extern "C" ActorProfile sHouseRoachProfile;
extern "C" s8 sHouseRoachTurnCounter;
extern "C" volatile u8 sHouseRoachActiveCount;
extern "C" HouseRoachManager *sHouseRoachManager;
extern "C" Actor *sHouseRoachVillager;
extern "C" volatile u8 sHouseRoachTotal;
extern "C" HouseRoach *sHouseRoaches[3];

extern "C" HouseRoachManager *HouseRoachManager_Create() {
    return new HouseRoachManager();
}

extern "C" HouseRoach *HouseRoach_Create() {
    return new HouseRoach();
}

HouseRoachManager::HouseRoachManager() {
}

HouseRoachManager::~HouseRoachManager() {
}

BOOL HouseRoachManager::onDelete() {
    if (!Scene_InHouseRoom() || gCommManager->isOnline()) return TRUE;
    ((HouseData *)gSaveHouse)->setRoachCount(sHouseRoachTotal);
    sHouseRoachManager = 0;
    return TRUE;
}

BOOL HouseRoachManager::onExecute() {
    if (!Scene_InHouseRoom() || gCommManager->isOnline()) return TRUE;
    u8 mask = 0;
    s8 last = 0;
    s32 i = 0;
    for (i = 0; i < 3; i++) {
        HouseRoach **s = &sHouseRoaches[i];
        if (*s != 0) {
            if (sHouseRoaches[i]->param == 0xffff) {
                (*s)->param = 0;
                (*s)->setSoundState(0);
                ProcBase_RequestDelete(*s);
                *s = 0;
                u32 c = sHouseRoachActiveCount;
                if (c != 0) {
                    sHouseRoachActiveCount = c - 1;
                    sHouseRoachTotal = sHouseRoachTotal - 1;
                }
            } else if (sHouseRoaches[i]->getSoundState() == 1) {
                mask = mask | (1 << i);
                last = last - 1;
            } else if ((*s)->getSoundState() == 2) {
                mask = 0xff;
            }
        }
    }
    if (mask != 0xff && mask != 0) {
        Actor *p = (Actor *)PlayerActor_GetActor(4);
        s32 best = 0xfffffff;
        if (p != 0) {
            VecFx32 *q = &p->position;
            for (i = 0; i < 3; i++) {
                HouseRoach *o = sHouseRoaches[i];
                if (o != 0 && ((mask >> i) & 1) != 0) {
                    if (last == -1) {
                        last = (s8)i;
                        break;
                    }
                    s32 d = Vec_DistXZ(q, &o->position);
                    if (best > d) {
                        best = d;
                        last = (s8)i;
                    }
                }
            }
        }
        sHouseRoaches[last]->setSoundState(2);
    }
    return TRUE;
}

BOOL HouseRoachManager::onCreate() {
    if (!Scene_InHouseRoom() || gCommManager->isOnline()) return TRUE;
    sHouseRoachManager = this;
    if (!HouseRoach_LoadCount(this)) return TRUE;
    HouseRoach_SpawnInitial(this);
    return TRUE;
}

extern "C" BOOL HouseRoach_SpawnFromFurniture(void *pos, u16 *angle) {
    BOOL r = FALSE;
    if (gCommManager->isOnline()) return r;
    u32 c = sHouseRoachActiveCount;
    if (c < 3) {
        s32 d = sHouseRoachTotal - c;
        if (d > 0) {
            s32 i;
            for (i = 0; i < 3; i++) {
                HouseRoach **s = &sHouseRoaches[i];
                if (*s == 0) {
                    *s = (HouseRoach *)Actor::spawn(0xc0, 0, pos, angle, sHouseRoachManager);
                    sHouseRoachActiveCount = sHouseRoachActiveCount + 1;
                    r = TRUE;
                    break;
                }
            }
        }
    }
    return r;
}

extern "C" BOOL HouseRoach_SpawnInitial(HouseRoachManager *owner) {
    s32 x2;
    s32 y2;
    u8 cnt = 0;
    BlockMap *g = gSceneBlockMap;
    u32 rows[32];
    s32 x;
    s32 y;
    s32 hx;
    s32 hy;
    u32 *row;
    u16 *cell;
    BOOL ok;
    u8 i;
    VecFx32 loc;
    u32 *row2;
    u8 k;
    u32 t;
    s32 w;
    u32 b;
    for (y = 0; y < g->unitsZ; y++) {
        row = &rows[y];
        rows[y] = 0;
        x = 0;
        goto xt0;
    xl0:
        if (g == 0) goto xn0;
        if (g->canPlaceItem(x, y) == 0) goto xn0;
        hx = x >> 4;
        hy = y >> 4;
        cell = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (cell == 0) goto xn0;
        if (Item_IsFurniture(cell) != 0) {
            u16 tmp = 0xfff1;
            s32 a = Item_GetFurnitureIndex(cell);
            s32 bb = Item_GetFurnitureIndex(&tmp);
            ok = (a == bb) ? TRUE : FALSE;
        } else {
            if (*cell == 0xfff1) ok = TRUE;
            else ok = FALSE;
        }
        if (ok) {
            cnt = (u8)(cnt + 1);
            *row = *row | (1 << x);
        }
    xn0:
        x++;
    xt0:
        if (x < g->unitsX) goto xl0;
    }
    for (i = 0; i < 3 && sHouseRoachActiveCount < sHouseRoachTotal; i++) {
        if (cnt == 0) break;
        loc.x = 0;
        loc.y = 0;
        loc.z = 0;
        t = cnt;
        cnt = (u8)(t - 1);
        k = (u8)(Random_GlobalBelow(t) + 1);
        y2 = 0;
        goto yt1;
    yl1:
        x2 = 0;
        row2 = &rows[y2];
        w = g->unitsX;
        goto xt1;
    xl1:
        b = *row2;
        b = b >> x2;
        b = b & 1;
        if (b) k = (u8)(k - 1);
        if (k == 0) {
            *row2 -= 1 << x2;
            FieldPos_FromUnitCenter(&loc, x2, y2);
            loc.y = 0x200;
            y2 = g->unitsZ;
            goto yn1;
        }
        x2++;
    xt1:
        if (x2 < w) goto xl1;
    yn1:
        y2++;
    yt1:
        if (y2 < g->unitsZ) goto yl1;
        sHouseRoaches[i] = (HouseRoach *)Actor::spawn(0xc0, 0x1f, &loc, 0, owner);
        sHouseRoachActiveCount = sHouseRoachActiveCount + 1;
    }
    return TRUE;
}

extern "C" BOOL HouseRoach_LoadCount(HouseRoachManager *self) {
    sHouseRoachTotal = ((HouseData *)gSaveHouse)->getRoachCount();
    if (sHouseRoachTotal != 0) return TRUE;
    return FALSE;
}

HouseRoach::HouseRoach() {
    crawlSpeed = 0x614;
    jumpSpeed = 0x6b8;
    lifeState = 1;
    wallProbe = 0;
    wallTurnDir = 0;
    jumpTimer = 0;
    roachState = 3;
}

HouseRoach::~HouseRoach() {
}

extern "C" void HouseRoach_FindVillager(void *) {
    u8 i;
    for (i = 0; i < 8; i++) {
        NpcActor *r = NpcRegistry_FindVillager(i);
        if (r) sHouseRoachVillager = (Actor *)r;
    }
}

s32 HouseRoach::getSoundState() {
    return soundState;
}

void HouseRoach::setSoundState(s32 v) {
    soundState = v;
}

BOOL HouseRoach::setup() {
    model.loadCached(0x474f4b49, sHouseRoachModelPath);
    Heap *h = FrameHeap_CreateAsCurrent(0x5000, gCurrentHeap);
    ProcBase_SetHeap(this, h);
    model.allocAnmObj(0);
    u8 *t = (u8 *)File_Load("/insect/51/bug52.nsbva");
    h->adjust();
    Heap_RestoreCurrent();
    u8 *r = func_021067a4(func_02106788(t), 0);
    static_cast<BlendAnimModel *>(&model)->initAnim(r, 0, 0x1000, 0, 0);
    model.attachAnim();
    sound.callReset();
    moveAngleY = rotY;
    spawnAngle = moveAngleY;
    gravity = -819;
    speed = crawlSpeed;
    isJumping = 0;
    wantsCrawlSe = 0;
    soundState = 0;
    return TRUE;
}

void HouseRoach::updateState() {
    VecFx32 v;
    if (roachState != 2) {
        updateCollision();
    }
    switch (roachState) {
    case 0:
        updateCrawl();
        break;
    case 1:
        speed = crawlSpeed;
        if (stateTimer-- > 0) {
            break;
        }
        if (isJumping != 0) {
            break;
        }
        roachState = 0;
        stateTimer = (Random_GlobalBelow(10) + 3) * 20;
        break;
    case 2:
        Effect_PlayById(0x50, &position, 0, 0);
        param = param - 1;
        lifeState = 2;
        playSe(2);
        break;
    case 3:
        if (Random_GlobalBelow(100) > 0x32) {
            roachState = 0;
            stateTimer = (Random_GlobalBelow(10) + 3) * 20;
        } else {
            roachState = 1;
            stateTimer = (Random_GlobalBelow(4) + 3) * 20;
        }
        break;
    }
    VecFx32 *pv = &position;
    v.x = position.x;
    v.y = pv->y;
    v.z = pv->z;
    sound.callUpdateRelative(&v);
}

void HouseRoach::updateCollision() {
    s32 ang;
    VecFx32 *p;
    BoxCollider colliders[4];
    u8 fr[4];
    u8 fm[4];
    VecFx32 v[4];
    s32 z1;
    s32 z2;
    u32 n;
    u8 i;
    s32 t;
    p = &position;
    n = 1;
    ang = rotY;
    t = FX_Div(0x1000, 0x2000);
    switch (Scene_GetHouseRoom()) {
    case 1:
    case 4:
        v[0].x = func_01ffcb0c(0x20000, t);
        v[0].z = func_01ffcb0c(0x39000, t);
        fm[0] = n;
        break;
    case 2:
        v[0].x = func_01ffcb0c(0x13000, t);
        v[0].z = func_01ffcb0c(0x35000, t);
        fm[0] = 0;
        break;
    case 3:
        v[0].x = func_01ffcb0c(0x2c000, t);
        v[0].z = func_01ffcb0c(0x37000, t);
        fm[0] = 0;
        break;
    case 0:
        n = 4;
        v[0].x = func_01ffcb0c(0xf000, t);
        v[0].z = func_01ffcb0c(0x34000, t);
        fm[0] = 0;
        v[1].x = func_01ffcb0c(0x31000, t);
        v[1].z = func_01ffcb0c(0x34000, t);
        fm[1] = 0;
        v[2].x = func_01ffcb0c(0x20000, t);
        v[2].z = func_01ffcb0c(0x39000, t);
        fm[2] = 1;
        v[3].x = func_01ffcb0c(0x20000, t);
        v[3].z = func_01ffcb0c(0x17000, t);
        fm[3] = 1;
        break;
    }
    z1 = 0;
    z2 = z1;
    for (i = 0; i < n; i++) {
        if (fm[i] != 0) {
            s32 a = func_01ffcb0c(0x4000, 0x1000);
            s32 b = func_01ffcb0c(0xa000, 0x1000);
            fr[i] = BoxCollider_Register(&colliders[i], a, 0x1000, b, &v[i], z2, NULL);
        } else {
            s32 a = func_01ffcb0c(0x4000, 0x1000);
            s32 b = func_01ffcb0c(0xa000, 0x1000);
            fr[i] = BoxCollider_Register(&colliders[i], 0x1000, a, b, &v[i], z1, NULL);
        }
    }
    if (roachState != 0) {
        move();
    }
    updatePosition((ActorCollider *)&hitBox);
    Collision_Move(&moveResult, p, &prevPosition, ang, 0x666, this, 0xf);
    for (i = 0; i < n; i++) {
        if (fr[i] != 0) {
            BoxCollider_Unregister(&colliders[i]);
        }
    }
}

void HouseRoach::updateAppear() {
    VecFx32 v;
    speed = crawlSpeed;
    updateCollision();
    position.y = prevPosition.y;
    VecFx32 *pv = &position;
    v.x = position.x;
    v.y = pv->y;
    v.z = pv->z;
    sound.callUpdateRelative(&v);
}

BOOL HouseRoach::execute() {
    u32 t;
    wantsCrawlSe = 0;
    t = param;
    if (t >= 0x1f) {
        if (lifeState == 1) {
            if (sHouseRoachVillager == NULL) {
                HouseRoach_FindVillager(this);
            }
            checkStomped();
            updateHitBox();
            updateState();
            checkHeight();
            if (isJumping != 0) {
                model.stepAnim();
            }
        } else {
            param = t - 1;
        }
    } else {
        if (lifeState == 1) {
            param = t + 2;
            updateAppear();
        } else {
            param = t - 1;
        }
    }
    if (param != 0) {
        Mtx43 buf;
        drawTilt = WorldCurve_ToCurved(&drawPos, &position);
        calcModelMatrix(&buf);
        model.mtx = buf;
    } else {
        release();
    }
    if (wantsCrawlSe == 0) {
        setSoundState(0);
    }
    return TRUE;
}

BOOL HouseRoach::checkHeight() {
    if (position.y >= 0xc00) {
        position.y = prevPosition.y;
        if ((moveResult.flags & 1) != 0) {
            GroundInfo g;
            roachState = 2;
            g.initAtPos(&position, 0, 0);
            position.y = g.getHeight(1);
            return TRUE;
        }
    }
    return FALSE;
}

BOOL HouseRoach::checkStomped() {
    Actor *pl = (Actor *)PlayerActor_GetActor(4);
    if (hitBox.isHit != 0) {
        if (isJumping == 0) {
            if (pl != NULL) {
                if (pl->speed > 0) {
                    if (hitBox.isHitByGroup(4) != 0) {
                        roachState = 2;
                        return TRUE;
                    }
                }
            }
            if (sHouseRoachVillager != NULL) {
                if (sHouseRoachVillager->speed > 0) {
                    if (hitBox.isHitByGroup(8) != 0) {
                        roachState = 2;
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

BOOL HouseRoach::draw() {
    if (lifeState != 4) {
        VecFx32 *pv = &position;
        if (param > 0x1f) {
            param = 0x1f;
        }
        model.setPolygonId(3);
        NNSi_G3dModifyPolygonAttrMask((u8 *)model.resMdl, 1, 0x1f0000);
        model.setAlpha((u8)param);
        model.drawAnimated((void *)(0));
        if (param >= 0x1f && lifeState == 1) {
            CharaShadow_Draw(pv, 0x400, 0x4000, 0x1000);
        }
    }
    return TRUE;
}

BOOL HouseRoach::release() {
    model.release();
    lifeState = 4;
    param = 0xffff;
    sound.callRelease();
    return TRUE;
}

void HouseRoach::playSe(u32 sel) {
    switch (sel) {
    case 0:
        wantsCrawlSe = 1;
        if (getSoundState() == 2) {
            sound.callRequest(0x1d2);
        } else {
            setSoundState(1);
        }
        break;
    case 1:
        sound.callRequestSustained(0x1d3);
        break;
    default:
        sound.callRequestSustained(0x1d4);
        break;
    }
}

u8 HouseRoach::probeWalls() {
    u8 r6 = 0;
    VecFx32 *r4r = &probePoints[0];
    CollisionState o1;
    GroundInfo o2;
    GroundInfo o3;
    volatile s32 t1;
    s16 t2;
    s16 t1v;
    s16 ang;
    o2.initAtPos(r4r, r6, r6);
    ang = rotY;
    if (probePrevPoints[0].x == 0 || probePrevPoints[0].z == 0) {
        probePrevPoints[0].x = probePoints[0].x;
        probePrevPoints[0].y = probePoints[0].y;
        probePrevPoints[0].z = probePoints[0].z;
    }
    Collision_Move(&o1, r4r, &probePrevPoints[0], ang, 0x19a, this, 0xf);
    t1 = (s16)(u16)o1.contacts.numContacts;
    if (o2.getHeight(1) > 0x200 || r4r->y > 0x1000 || t1 > 0) {
        r6++;
    }
    o3.initAtPos(r4r + 1, 0, 0);
    if (probePrevPoints[1].x == 0 || probePrevPoints[1].z == 0) {
        probePrevPoints[1].x = probePoints[1].x;
        probePrevPoints[1].y = probePoints[1].y;
        probePrevPoints[1].z = probePoints[1].z;
    }
    Collision_Move(&o1, r4r + 1, &probePrevPoints[1], ang, 0x19a, this, 0xf);
    t2 = (s16)(u16)o1.contacts.numContacts;
    if (o3.getHeight(1) > 0x200 || r4r[1].y > 0x1000 || t2 > 0) {
        r6 += 2;
    }
    return r6;
}

void HouseRoach::setProbePoints(s32 dist, s32 delta) {
    VecFx32 *pv = &position;
    s16 ang = rotY;
    u32 idx;
    probePoints[0].x = position.x;
    probePoints[0].y = pv->y;
    probePoints[0].z = pv->z;
    probePoints[1].x = position.x;
    probePoints[1].y = pv->y;
    probePoints[1].z = pv->z;
    probePrevPoints[0].x = probePoints[0].x;
    probePrevPoints[0].y = probePoints[0].y;
    probePrevPoints[0].z = probePoints[0].z;
    probePrevPoints[1].x = probePoints[1].x;
    probePrevPoints[1].y = probePoints[1].y;
    probePrevPoints[1].z = probePoints[1].z;
    idx = ((u16)(s16)(ang + delta) >> 4) * 2;
    probePoints[0].x += (dist * data_02135f44[idx]) / 100;
    probePoints[0].z += (dist * data_02135f44[idx + 1]) / 100;
    probePoints[0].y = 0x200;
    idx = ((u16)(s16)(ang - delta) >> 4) * 2;
    probePoints[1].x += (dist * data_02135f44[idx]) / 100;
    probePoints[1].z += (dist * data_02135f44[idx + 1]) / 100;
    probePoints[1].y = 0x200;
}

Actor *HouseRoach::getNearestCharacter() {
    s32 d4, d3, d2, d1;
    Actor *p;
    Actor *g;
    VecFx32 *a;
    VecFx32 *b;
    VecFx32 *c;
    p = (Actor *)PlayerActor_GetActor(4);
    g = sHouseRoachVillager;
    if (g != NULL) {
        if (p != NULL) {
            a = &position;
            b = &p->position;
            c = &g->position;
            d1 = position.x - p->position.x;
            if (d1 < 0) d1 = -d1;
            d2 = a->z - b->z;
            if (d2 < 0) d2 = -d2;
            d3 = position.x - c->x;
            if (d3 < 0) d3 = -d3;
            d4 = a->z - c->z;
            if (d4 < 0) d4 = -d4;
            if (d1 + d2 > d3 + d4) goto retg;
            return p;
        }
        retg:
        return g;
    }
    return p;
}

void HouseRoach::updateCrawl() {
    VecFx32 *self0 = &position;
    s32 res = 0;
    u8 i;
    s32 zero = 0;
    for (i = 0; i < 2; i++) {
        Actor *o;
        if (i == 0) {
            o = (Actor *)PlayerActor_GetActor(4);
        } else {
            o = sHouseRoachVillager;
        }
        if (o != 0 && res == 0) {
            VecFx32 *q = &o->position;
            stateTimer = stateTimer - 1;
            speed = zero;
            if (stateTimer <= 0) {
                roachState = 1;
                stateTimer = (Random_GlobalBelow(4) + 1) * 20;
                res = 1;
            } else if (o->speed > 0) {
                s32 d = Vec_DistXZ(self0, q);
                if (d < func_01ffcb0c(0x1000, 0x4000)) {
                    stateTimer = (Random_GlobalBelow(4) + 2) * 20;
                    roachState = 1;
                    res = 2;
                }
            }
        }
    }
    if (res == 2) {
        Actor *t = getNearestCharacter();
        if (t) {
            moveAngleY = Math_AngleXZ(&t->position, self0);
            rotY = moveAngleY;
        }
    }
}

void HouseRoach::updateHitBox() {
    hitBox.setupForActorAt(this, &position, 0x19a, 0x333, 0x81, 0xc, 0, 0xff, 0x1000);
    hitBox.submit();
}

BOOL HouseRoach::move() {
    s32 a = rotY;
    VecFx32 *p6 = &position;
    s32 hit = 0;
    u8 i;
    setProbePoints(0x3c, 0xe38);
    wallProbe = probeWalls();
    for (i = 0; i < 2; i++) {
        Actor *o;
        if (i == 0) {
            o = (Actor *)PlayerActor_GetActor(4);
        } else {
            o = sHouseRoachVillager;
        }
        if (o != 0 && hit == 0) {
            VecFx32 *q = &o->position;
            if (Vec_DistXZ(p6, q) < 0x1800) {
                s32 d = Math_AngleXZ(p6, q);
                if ((d >= 0 && a >= 0) || (d <= 0 && a <= 0)) {
                    s32 t = d - a;
                    if (t < 0) {
                        t = -t;
                    }
                    if (t < 0x2aaa) {
                        jumpTimer = jumpTimer + 1;
                        isJumping = 1;
                        hit = 1;
                        speed = jumpSpeed;
                        playSe(1);
                    }
                }
            }
        }
    }
    s32 c = jumpTimer;
    if (c > 0) {
        s32 k = c << 12;
        s32 r = func_01ffcb0c(0xcd, k);
        p6->y = func_01ffcb0c(0x99a - r, k);
        if (p6->y < 3) {
            p6->y = 3;
            jumpTimer = 0;
            isJumping = 0;
            model.setFrame(0);
        } else {
            jumpTimer = jumpTimer + 1;
            model.stepAnim();
        }
    } else {
        s32 m = wallProbe;
        if (m > 0) {
            if (m == 3) {
                if (wallTurnDir == 1 || wallTurnDir == 10) {
                    a = (s16)(a - 0xaaa);
                } else {
                    a = (s16)(a + 0xaaa);
                }
            } else if (m == 1 || wallTurnDir == 1) {
                a = (s16)(a - 0xaaa);
                wallTurnDir = 1;
            } else if (m == 2 || wallTurnDir == 2) {
                a = (s16)(a + 0xaaa);
                wallTurnDir = 2;
            }
        } else {
            if (sHouseRoachTurnCounter == 4) {
                a = (s16)(a + 0xaaa);
                sHouseRoachTurnCounter = -1;
            } else if (sHouseRoachTurnCounter == 2) {
                a = (s16)(a - 0xaaa);
            }
            sHouseRoachTurnCounter = sHouseRoachTurnCounter + 1;
            if (wallTurnDir < 10) {
                wallTurnDir = wallTurnDir * 10;
            }
        }
        playSe(m > 0 ? 0 : 0);
    }
    moveAngleY = a;
    rotY = moveAngleY;
    return TRUE;
}

BOOL HouseRoach::onDraw() {
    return draw();
}


BOOL HouseRoach::onCreate() {
    if (Scene_InHouseRoom()) {
        return setup();
    }
    return 1;
}

BOOL HouseRoach::onExecute() {
    return execute();
}

BOOL HouseRoach::onDelete() {
    return release();
}


extern "C" ProcProfile sHouseRoachManagerProfile = {(void *(*)())HouseRoachManager_Create, 0xbf, 0xc2};

extern "C" char sHouseRoachModelPath[0x18] = "/insect/51/bug52.nsbmd";

extern "C" ActorProfile sHouseRoachProfile = {(void *(*)())HouseRoach_Create, 0xc0, 0xc3, 2, 0x50000, 0x50000, 0x140000};

extern "C" s8 sHouseRoachTurnCounter = 0;

extern "C" volatile u8 sHouseRoachActiveCount = 0;

extern "C" HouseRoachManager *sHouseRoachManager = 0;

extern "C" Actor *sHouseRoachVillager = 0;

extern "C" volatile u8 sHouseRoachTotal = 0;

extern "C" HouseRoach *sHouseRoaches[3] = {0};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02235fd0) {
    HOST_OVERLAY_VAR(sHouseRoachManagerProfile),
    HOST_OVERLAY_VAR(sHouseRoachModelPath),
    HOST_OVERLAY_VAR(sHouseRoachProfile),
    HOST_OVERLAY_VAR(sHouseRoachTurnCounter),
    HOST_OVERLAY_VAR(sHouseRoachActiveCount),
    HOST_OVERLAY_VAR(sHouseRoachManager),
    HOST_OVERLAY_VAR(sHouseRoachVillager),
    HOST_OVERLAY_VAR(sHouseRoachTotal),
    HOST_OVERLAY_VAR(sHouseRoaches),
    HOST_OVERLAY_VARS_END
};

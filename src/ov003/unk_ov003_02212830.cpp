#include "types.h"
#include "host_labels.h"
#include "proto/main/unk_0202fa70.h"
#include "sys/StackPad.h"
#include "gfx/VecFx32.h"
#include "gfx/Mtx43.h"
#include "actor/ActorProfile.h"
#include "actor/ActorCollider.h"
#include "talk/TalkWindowState.h"
#include "game/CollisionState.h"
#include "gfx/CachedModel.h"
#include "actor/ActorFollowCollider.h"
#include "sys/ProcBase.h"
#include "talk/MsgString9B.h"
#include "actor/Actor.h"
#include "actor/Character.h"
#include "talk/MsgRequest.h"
#include "talk/TalkMsgRequest.h"
#include "talk/MsgString256.h"
#include "field/Snowball.h"
#include "gfx/Model.h"
#include "snd/SndSeEmitter.h"
#include "field/LooseSnowballs.h"
#include "field/SnowmanRecords.h"
#include "game/GroundInfo.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/itcm/unk_01ffcfc0.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02039c08.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/ov003/unk_ov003_02212830.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/main/unk_0204cc1c.h"









typedef VecFx32Ctor V3;

typedef void (Snowball::*Unk_02212954_Fn)();
typedef BOOL (Snowball::*Unk_022129d0_Fn)();
typedef void (Snowball::*Fn0)();
typedef BOOL (Snowball::*Fn1)();

extern "C" {
extern BlockMap *gSceneBlockMap;
extern void *gCamera;
extern VecFx32Ctor gCameraLookAt;
extern s32 data_020c8cbc;
extern u32 gFrameCounter;
extern s32 data_020d0584[4];
#define data_021ed2e6 HOST_LABEL(SnowmanRecords *, data_021ed2e6)
extern s16 data_02135f44[];
extern const s16 sSnowmanNeighbourOffsets[16];
#define data_ov003_0222efba (&sSnowmanNeighbourOffsets[1])

s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 VEC_Mag(void *v);
void MTX_Concat43(void *a, void *b, void *out);
s32 Vec_DistXZ(void *a, void *b);
s16 Math_Atan2(s32 a, s32 b);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s32 Vec_Sub(void *out, void *a, void *b);
s32 Math_ApproachS32Max(void *p, s32 a, s32 b, s32 c);
s32 Vec_MagXZ(void *v);
s32 Math_ApproachS16Div(s16 *p, s32 a, s32 b, s32 c);
void Vec_Scale(void *v, s32 ang);
void Mtx43_SetTranslate(void *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(void *m, s32 a);
BOOL Item_IsFurniture(u16 *p);
s32 Item_GetFurnitureIndex(u16 *p);
BOOL Item_IsNormalItem(u16 *p);
u16 Item_MakeSnowman(u32 x);
s32 Item_IsSnowman(u16 *c);
s32 Collision_GetUnitShape(s32 x, s32 y, s32 *a, s32 *b, s32 *c);
s32 Ground_CanPlaceItem(s32 x, s32 y);
s32 Ground_GetDigKind(s32 x, s32 y);
BOOL Item_IsMarker(void *p);
s32 Scene_InTown();
BOOL TalkRequest_SetTargetDone(void *p);
void TalkRequest_AddPlayerTalk6(void *self, s32 a);


BOOL Snowball_ChangeState(Snowball *o, s32 st);
BOOL Snowball_IsLooseBall(Snowball *o);
BOOL Snowball_IsSnowmanPart(Snowball *o);
BOOL Snowball_IsSnowmanHead(Snowball *o);
BOOL Snowball_IsSnowmanBody(Snowball *o);
BOOL Snowball_CanBuildSnowmanAt(VecFx32 *pos);
BOOL Snowball_PlaceSnowmanAt(u32 a, VecFx32 *pos, u16 *out);
BOOL Snowball_IsInBallState(Snowball *o);
void Snowball_InitState(Snowball *o);
void Snowball_RunState(Snowball *o);
void Snowball_UpdateCarry(Snowball *o);
void Snowball_UpdateRolling(Snowball *o);
void Snowball_UpdateMatrix(Snowball *o, s32 a, s32 b);
s32 Snowball_Break(Snowball *o, s32 a);
}
static inline u16 *Unk_ov003_02213058_Cell(BlockMap *g, s32 x, s32 y) {
    s32 hx = x >> 4;
    s32 hy = y >> 4;
    return BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
}

typedef void (Snowball::*Fn0)();
typedef BOOL (Snowball::*Fn1)();

extern "C" void *Snowball_Create() {
    return new Snowball;
}

SnowballCollider::SnowballCollider() {
    hitThisFrame = 0;
}

SnowballCollider::~SnowballCollider() {
    hitThisFrame = 0;
}

void SnowballCollider::onCollide(u32 a, u32 b, u32 c) {
    if (c & 4) {
        hitThisFrame = 1;
    }
}

Snowball::Snowball() {
    displacedItem = 0xfff1;
}

Snowball::~Snowball() {
}

extern "C" s32 Snowball_GetMinRadius() { return 0x800; }

extern "C" s32 Snowball_GetMaxRadius() { return 0x1400; }

void *Snowball::operator new(size_t size) {
    void *p = Heap_Alloc((Heap *)gBgHeap, size);
    memset(p, 0, size);
    return p;
}

void Snowball::operator delete(void *p) {
    Heap *h = (Heap *)gBgHeap;
    if (h) {
        Heap_Free(h, p);
    }
}

BOOL Snowball::onCreate() {
    u32 k = 0xfff1;
    displacedItem = k;
    rotationQuat.x = data_020d0584[0];
    rotationQuat.y = data_020d0584[1];
    rotationQuat.z = data_020d0584[2];
    rotationQuat.w = data_020d0584[3];
    ((CachedModel *)(&ballModel))->loadCached(0x534e5730, (void *)(void *)("/snowman/snowball1.nsbmd"));
    ((CachedModel *)(&faceModel))->loadCached(0x534e5731, (void *)(void *)("/snowman/snow_face.nsbmd"));
    if (Snowball_IsLooseBall(this) != 0) {
        u32 i = param & 1;
        LooseSnowball *r = LooseSnowballs_Get()->items;
        radius = r[i & 1].radius;
        i = param & 1;
        r = LooseSnowballs_Get()->items;
        r[i & 1].posX = position.x;
        r[i & 1].posY = position.y;
        r[i & 1].posZ = position.z;
        s32 sv = radius;
        i = param & 1;
        r = LooseSnowballs_Get()->items;
        r[i & 1].radius = sv;
    }
    setCharId((u16)param);
    changeTalkAct(0);
    Snowball_InitState(this);
    prevPosition.x = position.x;
    prevPosition.y = position.y;
    prevPosition.z = position.z;
    VecFx32 *pv = &prevPosition;
    lastFramePos.x = prevPosition.x;
    lastFramePos.y = pv->y;
    lastFramePos.z = pv->z;
    Collision_Move(&collisionState, &position, &prevPosition, 0, collisionRadius, this, 0xb);
    prevPosition.x = position.x;
    prevPosition.y = position.y;
    prevPosition.z = position.z;
    pv = &prevPosition;
    lastFramePos.x = prevPosition.x;
    lastFramePos.y = pv->y;
    lastFramePos.z = pv->z;
    prevContactCount = collisionState.contacts.numContacts;
    Snowball_UpdateMatrix(this, 0, 0);
    seEmitter.callInit();
    clearTalkStartMode();
    return Snowball_Register(this);
}

BOOL Snowball::onExecute() {
    s32 t = FX_Div(0xa000, 0x64000);
    if (snowballFlags.e == 0) pushSpeed = t;
    prevPosition.x = lastFramePos.x;
    prevPosition.y = lastFramePos.y;
    prevPosition.z = lastFramePos.z;
    Snowball_UpdateCarry(this);
    Snowball_RunState(this);
    runTalkAct();
    Snowball_UpdateRolling(this);
    SnowballFlags *fl = &snowballFlags;
    fl->f = fl->e;
    fl->e = 0;
    fl->h = 0;
    fl->i = 0;
    collider.hitThisFrame = 0;
    prevPosition.x = position.x;
    prevPosition.y = position.y;
    prevPosition.z = position.z;
    VecFx32 *pv = &prevPosition;
    lastFramePos.x = prevPosition.x;
    lastFramePos.y = pv->y;
    lastFramePos.z = pv->z;
    VecFx32 sp = position;
    seEmitter.callUpdateRelative(&sp);
    return TRUE;
}

BOOL Snowball::onDraw() {
    if (gCamera != 0) {
        if (Vec_DistXZ(&gCameraLookAt, &position) <= data_020c8cbc) {
            s32 s = FX_Div(radius, 0x1000);
            VecFx32 v;
            v.x = s;
            v.y = s;
            v.z = s;
            if (snowballState == 0xb) {
                faceModel.drawScaled((s32 *)&v);
            } else {
                ballModel.drawScaled((s32 *)&v);
            }
            CharaShadow_Draw(&position, radius, 0x4000, 0x1000);
        }
    }
    return TRUE;
}

BOOL Snowball::onDelete() {
    if (snowballState == 9) {
        BlockMap *g = gSceneBlockMap;
        volatile s32 x, y;
        FieldPos_ToUnit((s32 *)&x, (s32 *)&y, &position);
        s32 lx = x;
        s32 ly = y;
        s32 hx = lx >> 4;
        s32 hy = ly >> 4;
        u16 *c = BlockMap_GetItemPtr(g, hx, hy, lx - (hx << 4), ly - (hy << 4), 0);
        if (c != 0 && Item_IsSnowman(c) != 0) {
            u16 v = 0xfff1;
            BlockMap_SetItemAtUnit(g, &v, x, y, 0);
        }
        if (Snowball_PlaceSnowmanAt(snowballFlags.a, &position, &displacedItem) == 0) {
            if (Snowball_PlaceSnowmanNearby(snowballFlags.a, &position, &displacedItem) == 0) {
                data_021ed2e6.markUnplaced(snowballFlags.a);
            }
        }
        Snowball_DropDisplacedItem(&displacedItem);
    }
    if (talkAct == 0 && snowballState == 0) {
        u32 i = param & 1;
        LooseSnowball *r = LooseSnowballs_Get()->items;
        r[i & 1].posX = position.x;
        r[i & 1].posY = position.y;
        r[i & 1].posZ = position.z;
        s32 sv = radius;
        i = param & 1;
        r = LooseSnowballs_Get()->items;
        r[i & 1].radius = sv;
    }
    seEmitter.callStop();
    return Snowball_Unregister(this);
}

extern "C" void Snowball_UpdateMatrix(Snowball *o, s32 a, s32 b)
{
    VecFx32 v1;
    Quat q;
    VecFx32 pv;
    VecFx32 ex;
    Mtx43 m;
    Mtx43 m2;
    if (a != 0) {
        s32 t = ((u16)b >> 4) * 2;
        v1.x = data_02135f44[t + 1];
        v1.y = 0;
        v1.z = -data_02135f44[t];
        s32 u = ((s32)((u32)(a << 15) >> 16) >> 4) * 2;
        Vec_Scale(&v1, data_02135f44[u]);
        q.x = v1.x;
        q.y = v1.y;
        q.z = v1.z;
        q.w = data_02135f44[u + 1];
        Quat_Mul(&q.x, &o->rotationQuat.x, &o->rotationQuat.x);
        if ((gFrameCounter & 7) == o->param) {
            Quat_Normalize(&o->rotationQuat.x);
        }
    }
    Vec_Add(&ex, &o->position, &o->drawOffset);
    ex.y = ex.y + o->radius;
    ex.y = ex.y - 0x400;
    s32 ang = WorldCurve_ToCurved(&pv, &ex);
    Mtx43_SetTranslate(&m, pv.x, pv.y, pv.z);
    Mtx43_RotateX(&m, ang);
    Quat_ToMtx43(&o->rotationQuat.x, m2.m);
    MTX_Concat43(&m2, &m, &m);
    o->ballModel.mtx = m;
    o->faceModel.mtx = m;
}

extern "C" void Snowball_UpdateCarry(Snowball *o)
{
    if (o->collider.isHit != 0) {
        if (o->snowballFlags.h == 0) {
            o->position.x = o->position.x + o->collider.pushX;
            o->position.z = o->position.z + o->collider.pushZ;
        }
        if (o->collider.isHitByGroup(4) != 0 && o->radius < 0xa00) {
            if (o->hitSeLatch == 0) {
                Snd_SeEmitterPlayOneShot(&o->seEmitter, 0x81c, 0x7f, 0);
            }
            o->hitSeLatch = 1;
        } else {
            o->hitSeLatch = 0;
        }
    } else {
        o->hitSeLatch = 0;
    }
    o->colliderWeight = (func_01ffcb0c(FX_Div(o->radius - 0x800, 0xc00), 0x10cd) + 0xdec) << 2;
}

extern "C" void Snowball_UpdateRolling(Snowball *o)
{
    s32 kind = o->snowballFlags.c != 0 ? 0xb : 0;
    GroundInfo loc;
    VecFx32 d;
    s32 yaw;
    if (o->talkAct == 0 && o->snowballState == 0) {
        o->position.y -= 0x200;
    }
    Collision_Move(&o->collisionState, &o->position, &o->prevPosition, 0, o->collisionRadius, o, kind);
    u32 cur = o->collisionState.contacts.numContacts;
    if (cur > o->prevContactCount && o->talkAct == 0 && o->snowballState == 0) {
        Snd_SeEmitterPlayOneShot(&o->seEmitter, 0x81d, 0x7f, 0);
    }
    o->prevContactCount = cur;
    u32 fa = 0x20;
    if (o->snowballFlags.d != 0) fa |= 2;
    u32 fb = 0x12;
    u8 id = o->param;
    if (o->snowballState == 0xb) fb = 0x11;
    s32 s = FX_Div(0x41000, 0x64000);
    s32 t = o->radius;
    if (t < 0xa00) {
        s = 0x1000;
    } else if (t < 0xe00) {
        s = FX_Div((0x64 - ((FX_Div(t - 0xa00, 0x400) * 0x23) >> 12)) << 12, 0x64000);
    }
    s32 t2 = o->radius;
    s32 r2 = func_01ffcb0c(t2, s);
    o->collider.setupForActor(o, r2, t2 * 2, fa, 0x2fc, fb, id, o->colliderWeight);
    o->collider.submit();
    Vec_Sub(&d, &o->position, &o->prevPosition);
    s32 len = VEC_Mag(&d);
    s32 ang = (s16)((FX_Div(len, func_01ffcb0c(0x323d, o->radius)) >> 1) << 4);
    yaw = Math_Atan2(d.x, d.z);
    if (Snowball_IsInBallState(o)) {
        s32 n = VEC_Mag(&d);
        if (n == 0) {
            o->rollVelX = 0;
            o->rollVelZ = 0;
        } else {
            s32 v;
            s32 m = 0;
            s32 w = o->talkAct;
            if (w == 0 && o->snowballState == 1) m = 1;
            if (m) {
                v = n - FX_Div(0x2000, 0xa5000);
            } else if (w == 0 && o->snowballState == 5) {
                v = n - 0x155;
            } else {
                s32 q = o->collisionState.flags;
                if (q & 1) {
                    if (o->snowballFlags.e != 0) {
                        v = n - 0x155;
                    } else {
                        v = n - 0x28;
                    }
                } else if (q & 2) {
                    v = n - 0xaa;
                } else {
                    v = n - FX_Div(0x2000, 0xa0000);
                }
            }
            if (v < 0) v = 0;
            if (v > 0x400) v = 0x400;
            n = FX_Div(v, n);
            o->rollVelX = func_01ffcb0c(d.x, n);
            o->rollVelZ = func_01ffcb0c(d.z, n);
        }
    } else {
        o->rollVelX = 0;
        o->rollVelZ = 0;
    }
    loc.initAtPos(&o->position, 0, 0);
    if (loc.attr == 3) {
        if (o->snowballFlags.i == 0) {
            o->radius = func_01ffcb0c(o->radius, (len >> 7) + 0x1000);
            if (o->radius > 0x1400) o->radius = 0x1400;
        }
    } else {
        s32 m = 0;
        s32 w = o->talkAct;
        if (w == 0 && o->snowballState == 2) m = 1;
        if (!m) {
            if (w == 0 && o->snowballState == 6) {
            } else {
                o->radius = func_01ffcb0c(o->radius, 0x1000 - (len >> 9));
                if (o->radius < 0x800) o->radius = 0x800;
            }
        }
    }
    Snowball_UpdateMatrix(o, ang, yaw);
}

extern "C" BOOL Snowball_TrySetPos(Snowball *o, VecFx32 *v)
{
    if (o->snowballFlags.i == 0 && o->snowballFlags.e == 0 && o->collider.hitThisFrame == 0) {
        o->position.x = v->x;
        o->position.y = v->y;
        o->position.z = v->z;
        o->snowballFlags.i = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 Snowball_GetRadius(Snowball *o)
{
    return o->radius;
}

extern "C" s32 Snowball_Break(Snowball *o, s32 a)
{
    if (o->snowballState < 7) {
        return Snowball_ChangeState(o, 3);
    }
    return 0;
}

extern "C" BOOL Snowball_TryPush(Snowball *o, VecFx32 *outPos, s16 *outAng, s32 *outVal, s32 speed, s32 ang) {
    Actor *p;
    s32 v0c, v10, v14;
    s16 h[2];
    V3 pv[3];
    s32 ox, oz;
    s32 dist;
    ang = ang;
    p = (Actor *)PlayerActor_GetActor(4);
    if (!Scene_InTown()) return FALSE;
    if (!p) return FALSE;
    if (o->talkAct != 0 || o->snowballState != 0) return FALSE;
    if (o->radius < 0xa00) return FALSE;
    if (speed > 0xc32) speed = 0xc32;
    if (o->collider.isHit != 0) {
        o->position.x += o->collider.pushX;
        o->position.z += o->collider.pushZ;
        o->snowballFlags.h = 1;
    }
    h[0] = ang;
    if (o->snowballFlags.f) {
        h[0] = o->pushAngle;
        Math_ApproachS16Div(&h[0], ang, 5, 0x2000);
    }
    ox = o->rollVelX;
    oz = o->rollVelZ;
    if (!o->snowballFlags.f) {
        o->rollVelX = ox >> 4;
        o->rollVelZ >>= 4;
    }
    v0c = func_01ffcb0c(func_01ffcb0c(speed, 0x1b6), o->pushSpeed);
    v10 = func_01ffcb0c(v0c, data_02135f44[((u16)h[0] >> 4) * 2]);
    v14 = func_01ffcb0c(v0c, data_02135f44[((u16)h[0] >> 4) * 2 + 1]);
    o->rollVelX += v10;
    o->rollVelZ += v14;
    o->position.x += o->rollVelX;
    o->position.z += o->rollVelZ;
    h[1] = p->rotY;
    Math_ApproachS16Div(&h[1], ang, 8, 0x2000);
    VecFx32 *q = &p->position;
    pv[0].x = p->position.x;
    pv[0].y = q->y;
    pv[0].z = q->z;
    pv[1].x = pv[0].x + v10;
    pv[1].y = pv[0].y;
    pv[1].z = pv[0].z + v14;
    dist = Math_Atan2(o->position.x - pv[1].x, o->position.z - pv[1].z);
    if ((u32)Vec_DistXZ(&o->prevPosition, &pv[1]) > (u32)(o->radius + 0x1000)) {
        o->position.x -= o->rollVelX;
        o->position.z -= o->rollVelZ;
        o->rollVelX = ox;
        o->rollVelZ = oz;
        return FALSE;
    }
    s32 r0v = (s16)Math_AngleDiffAbs(dist, ang);
    s32 lim = o->snowballFlags.f ? 0x471c : 0x1000;
    if (r0v > (s16)lim) {
        o->position.x -= o->rollVelX;
        o->position.z -= o->rollVelZ;
        o->rollVelX = ox;
        o->rollVelZ = oz;
        return FALSE;
    }
    if ((s16)Math_AngleDiffAbs(h[1], h[0]) > 0x471c) {
        o->position.x -= o->rollVelX;
        o->position.z -= o->rollVelZ;
        o->rollVelX = ox;
        o->rollVelZ = oz;
        return FALSE;
    }
    Vec_Sub(&pv[2], &o->position, &pv[1]);
    *outAng = Math_Atan2(pv[2].x, pv[2].z);
    outPos->x = pv[1].x;
    outPos->y = pv[1].y;
    outPos->z = pv[1].z;
    o->snowballFlags.e = 1;
    o->pushAngle = h[0];
    Snd_SeEmitterPlayHeld(&o->seEmitter, 0x820, 0x7f, 0);
    {
        s32 t = FX_Div(o->radius - 0xa00, 0xa00);
        s32 r = func_01ffcb0c(0xc00, 0x1000 - t) + 0x200;
        Math_ApproachS32Max(&o->pushSpeed, 0x1000, r, 0x1000);
    }
    V3 d(o->rollVelX, 0, o->rollVelZ);
    *outVal = Vec_MagXZ(&d) >> 1;
    return TRUE;
}

extern "C" BOOL Snowball_IsInBallState(Snowball *o) {
    if (o->snowballState < 7) return TRUE;
    return FALSE;
}

extern "C" BOOL Snowball_IsLooseBall(Snowball *o) {
    if (o->param < 2) return TRUE;
    return FALSE;
}

extern "C" BOOL Snowball_IsSnowmanPart(Snowball *o) {
    StackPad4 pad;
    if (!Snowball_IsLooseBall(o)) return TRUE;
    return FALSE;
}

extern "C" BOOL Snowball_IsSnowmanHead(Snowball *o) {
    if (Snowball_IsSnowmanPart(o)) {
        if ((o->param - 2) & 1) return FALSE;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Snowball_IsSnowmanBody(Snowball *o) {
    if (Snowball_IsSnowmanPart(o)) {
        if (!Snowball_IsSnowmanHead(o)) return TRUE;
        return FALSE;
    }
    return FALSE;
}

extern "C" void Snowball_InitState(Snowball *o) {
    u32 s10, s14, s18;
    s32 r;
    if (Snowball_IsLooseBall(o)) {
        Snowball_ChangeState(o, 0);
    } else {
        r = Snowball_IsSnowmanBody(o);
        o->snowballFlags.a = (o->param - 2) >> 1;
        if (data_021ed2e6.getInfo(o->snowballFlags.a, &s10, &s14, &s18, 0, 0, 0)) {
            o->snowballFlags.b = (u16)s18;
            if (r) {
                o->radius = s14;
                Snowball_ChangeState(o, 9);
            } else {
                o->radius = s10;
                o->position.y = s14 * 2 - (s14 >> 3) - (s10 >> 3) - 0x400;
                Snowball_ChangeState(o, 11);
            }
        }
    }
}

extern "C" BOOL Snowball_CanBuildSnowmanAt(VecFx32 *pos) {
    BlockMap *g = gSceneBlockMap;
    if (g) {
        s32 px0, py0;
        s32 s18, s1c, s20;
        s32 x, y;
        s32 hx, hy, lx, ly;
        s32 t, r;
        s32 i, j;
        Actor *a;
        void *c;
        px0 = -1;
        py0 = -1;
        a = (Actor *)PlayerActor_GetActor(4);
        if (a) FieldPos_ToUnit(&px0, &py0, &a->position);
        FieldPos_ToUnit(&x, &y, pos);
        lx = *(volatile s32 *)&x;
        ly = *(volatile s32 *)&y;
        hx = lx >> 4;
        hy = ly >> 4;
        c = BlockMap_GetItemPtr(g, hx, hy, lx - (hx << 4), ly - (hy << 4), 0);
        if (c) {
            if (Item_IsMarker(c)) return FALSE;
        }
        t = Collision_GetUnitShape(x, y, &s18, &s1c, &s20);
        if (x != px0 || y != py0) {
            if (Ground_CanPlaceItem(x, y)) {
                if (t == 0 || (t != 0 && s20 == 2)) {
                    r = Ground_GetDigKind(x, y);
                    switch (r) {
                    case 0:
                    case 1:
                        for (i = -1; i <= 1; i++) {
                            for (j = -1; j <= 1; j++) {
                                s32 py, px, u;
                                if (i == 0 && j == 0) continue;
                                py = y + j;
                                px = x + i;
                                u = Collision_GetUnitShape(px, py, &s18, &s1c, &s20);
                                if (Ground_CanPlaceItem(px, py) && (u == 0 || s20 == 2)) continue;
                                return FALSE;
                            }
                        }
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

extern "C" BOOL Snowball_PlaceSnowmanAt(u32 a, VecFx32 *pos, u16 *out) {
    *out = 0xfff1;
    if (Snowball_CanBuildSnowmanAt(pos)) {
        BlockMap *g = gSceneBlockMap;
        if (g) {
            u16 t;
            s32 x, y;
            s32 hx, hy, lx, ly;
            u16 *c;
            t = Item_MakeSnowman(a);
            FieldPos_ToUnit(&x, &y, pos);
            lx = *(volatile s32 *)&x;
            ly = *(volatile s32 *)&y;
            hx = lx >> 4;
            hy = ly >> 4;
            c = (u16 *)BlockMap_GetItemPtr(g, hx, hy, lx - (hx << 4), ly - (hy << 4), 0);
            if (c) *out = *c;
            if (BlockMap_SetItemAtUnit(g, &t, x, y, 0)) return TRUE;
        }
    }
    return FALSE;
}

extern "C" BOOL Snowball_PlaceSnowmanNearby(u32 a, VecFx32 *pos, u16 *out) {
    BlockMap *g = gSceneBlockMap;
    if (g) {
        volatile u16 t[1];
        s32 x, y;
        VecFx32 p;
        VecFx32 q;
        u8 mask;
        s32 n;
        s32 k;
        u32 A;
        s32 C;
        s32 j;
        t[0] = Item_MakeSnowman(a);
        FieldPos_ToUnit(&x, &y, pos);
        mask = 0;
        n = 0;
        for (A = 0; A < 8; A++) {
            const s16 *e = &sSnowmanNeighbourOffsets[A * 2];
            FieldPos_FromUnitCenter(&p, x + sSnowmanNeighbourOffsets[A * 2], y + e[1]);
            if (Snowball_CanBuildSnowmanAt(&p)) {
                mask |= 1 << A;
                n++;
            }
        }
        if (n != 0) {
            k = Random_GlobalBelow(n);
            C = 0;
            j = 0;
            for (; (u32)j < 8; j++) {
                if ((mask >> j) & 1) {
                    if (C == k) {
                        FieldPos_FromUnitCenter(&q, x + sSnowmanNeighbourOffsets[j * 2], y + data_ov003_0222efba[j * 2]);
                        if (Snowball_PlaceSnowmanAt(a, &q, out)) return TRUE;
                        return FALSE;
                    }
                    C++;
                }
            }
        }
    }
    return FALSE;
}

extern "C" BOOL Snowball_ClearItemAt(VecFx32 *p) {
    BlockMap *g = gSceneBlockMap;
    if (g) {
        s32 x, y;
        u16 t;
        FieldPos_ToUnit(&x, &y, p);
        t = 0xfff1;
        if (BlockMap_SetItemAtUnit(g, &t, x, y, 0)) return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Snowball_DropDisplacedItem(u16 *p) {
    BOOL ok;
    if (Item_IsFurniture(p)) {
        u16 t = 0xfff1;
        ok = Item_GetFurnitureIndex(p) == Item_GetFurnitureIndex(&t) ? TRUE : FALSE;
    } else {
        ok = *p == 0xfff1 ? TRUE : FALSE;
    }
    if (!ok) {
        if (Item_IsNormalItem(p) || Item_IsFurniture(p)) {
            LostAndFound_Add(*p);
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" ActorProfile sSnowballProfile = {(void *(*)())Snowball_Create, 0xbd, 0x10, 0, 0xc8000, 0x12c000, 0x258000};
extern "C" const s16 sSnowmanNeighbourOffsets[16] = {-1, -1, 0, -1, 0, -1, -1, 0, 1, 0, -1, 1, 0, 1, 1, 1};

extern "C" BOOL Snowball_ChangeState(Snowball *o, s32 st) {
    static Fn1 tbl[14] = {
        (Fn1)&Snowball::enterSnowballRoll, (Fn1)&Snowball::enterSnowballFall, (Fn1)&Snowball::enterSnowballSink, (Fn1)&Snowball::enterSnowballBreak,
        (Fn1)&Snowball::enterSnowballHole, (Fn1)&Snowball::enterSnowball05, (Fn1)&Snowball::enterSnowballSplash, (Fn1)&Snowball::enterSnowballToSnowman,
        (Fn1)&Snowball::enterSnowballStack, (Fn1)&Snowball::enterSnowmanBody, (Fn1)&Snowball::enterSnowballSettle, (Fn1)&Snowball::enterSnowmanHead,
        (Fn1)&Snowball::enterSnowballCrumble, (Fn1)&Snowball::enterSnowballCrumble2};
    if (st < 0xe) {
        if ((o->*tbl[st])()) {
            o->snowballState = st;
            return TRUE;
        }
    }
    return FALSE;
}

extern "C" void Snowball_RunState(Snowball *o) {
    static Fn0 tbl[14] = {
        (Fn0)&Snowball::execSnowballRoll, (Fn0)&Snowball::execSnowballFall, (Fn0)&Snowball::execSnowballSink, (Fn0)&Snowball::execSnowballBreak,
        (Fn0)&Snowball::execSnowballHole, (Fn0)&Snowball::execSnowball05, (Fn0)&Snowball::execSnowballSplash, (Fn0)&Snowball::execSnowballToSnowman,
        (Fn0)&Snowball::execSnowballStack, (Fn0)&Snowball::execSnowmanBody, (Fn0)&Snowball::execSnowballSettle, (Fn0)&Snowball::execSnowmanHead,
        (Fn0)&Snowball::execSnowballCrumble, (Fn0)&Snowball::execSnowballCrumble2};
    if (o->snowballState < 0xe) (o->*tbl[o->snowballState])();
}

BOOL Snowball::enterSnowmanBody() {
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    return TRUE;
}

void Snowball::execSnowmanBody() {
    collisionRadius = radius;
    if (collider.isHit != 0) {
        Actor *p = collider.getHitActor();
        if (p) {
            if (p->speed > 0x666) {
                Snowball_Break(this, 1);
            }
        }
    }
}

BOOL Snowball::enterSnowmanHead() {
    s32 *d = data_020d0584;
    snowballFlags.c = 0;
    snowballFlags.d = 1;
    rotationQuat.x = d[0];
    rotationQuat.y = d[1];
    rotationQuat.z = d[2];
    rotationQuat.w = d[3];
    return TRUE;
}

void Snowball::execSnowmanHead() {
    collisionRadius = radius;
    if (collider.isHit != 0) {
        Actor *p = collider.getHitActor();
        if (p) {
            if (p->speed > 0x666) {
                Snowball_Break(this, 1);
                return;
            }
        }
    }
    if (snowballFlags.g) TalkRequest_AddPlayerTalk6(this, 0);
}

BOOL Snowball::acceptsInteraction(void *a) {
    s32 lim;
    BOOL r;
    clearTalkStartMode();
    lim = func_01ffcb0c(0x2000, FX_Div(0x7d000, 0x64000));
    if (a) {
        if (Vec_DistXZ(&((Actor *)a)->position, &position) < lim) {
            if (snowballState == 11) return TRUE;
        }
    }
    return FALSE;
}

void Snowball::onInteractionEvent(u32 a, u8 b) {
    switch (a) {
    case 0:
        changeTalkAct(1);
        break;
    case 1:
        changeTalkAct(1);
        snowballFlags.g = 0;
        break;
    case 8:
        changeTalkAct(0);
        break;
    }
}

BOOL Snowball::changeTalkAct(s32 m) {
    static Unk_022129d0_Fn tbl[3] = { (Unk_022129d0_Fn)&Snowball::setupTalkIdle, (Unk_022129d0_Fn)&Snowball::setupTalk, (Unk_022129d0_Fn)&Snowball::setupTalkEnd };
    if (m < 3) {
        if ((this->*tbl[m])()) {
            talkAct = m;
            return TRUE;
        }
    }
    return FALSE;
}

void Snowball::runTalkAct() {
    static Unk_02212954_Fn tbl[3] = { &Snowball::mainTalkIdle, &Snowball::mainTalk, &Snowball::mainTalkEnd };
    if (talkAct < 3) {
        (this->*tbl[talkAct])();
    }
}

BOOL Snowball::setupTalkIdle() {
    return TRUE;
}

void Snowball::mainTalkIdle() {}

BOOL Snowball::setupTalk() {
    ((Character *)(this))->attachTalkRequest(this);
    s32 r;
    if (snowballFlags.g) {
        r = (snowballFlags.b & 3) * 3 + Random_GlobalBelow(3);
    } else {
        r = (snowballFlags.b & 3) * 3 + 12 + Random_GlobalBelow(3);
    }
    setFileName("sp_npc_snowman");
    msgIndex = r;
    ((TalkWindowState *)window)->nextState = 1;
    u8 c = 0x26;
    MsgString256 buf;
    String_Load(&buf, &c, "st_spnpc_name");
    static_cast<TalkMsgRequest &>(*this).setSpeakerName(buf.data(), 0);
    snowballFlags.g = 0;
    return TRUE;
}

void Snowball::mainTalk() {
    if (window) {
        if (((TalkWindowState *)window)->state) {
            changeTalkAct(2);
        }
    }
}

BOOL Snowball::setupTalkEnd() {
    return TRUE;
}

void Snowball::mainTalkEnd() {
    if (window) {
        if (((TalkWindowState *)window)->state == 0) {
            ((Character *)(this))->detachTalkRequest(this);
            TalkRequest_SetTargetDone(this);
        }
    }
}


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02212830) {
    HOST_OVERLAY_VAR(sSnowballProfile),
    HOST_OVERLAY_VARS_END
};

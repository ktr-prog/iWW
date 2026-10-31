#include "uptr.h"
#include "gfx/SplReal.h"

#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "gfx/SPLResource.h"
#include "gfx/EffectSlot.h"
#include "gfx/EffectSplEmitter.h"
#include "gfx/P.h"
#include "game/GroundInfo.h"
#include "gfx/Rgb555.h"
#include "game/GroundInfoBase.h"
#include "proto/autoload_2/unk_020e7500.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_0208f268.h"
#include "proto/main/unk_02090268.h"



class EffectManager {
public:
    void end(s32 id);
    u32 getKind(s32 id);
    s32 create(u32 kind, VecFx32 *pos, s16 *angle, s16 *param, s32 id);
    void reset();
    void setLife(s32 id, s16 v);
    void setPosition(s32 id, VecFx32 *pos, s16 *a, s16 *b);
    EffectSlot *findSlot(s32 id, EffectSlot *e, s32 n);
    void clearSlots();

    /* 0x000 */ EffectSlot slots[32];
    /* 0x380 */ EffectSlot scratchSlot;
    /* 0x39c */ u16 nextHandle;
};

struct EffectKindEntry {
    s32 (*fn)(s32 kind, VecFx32 *pos, s16 *angle, s16 *param, s32 id);
    void (*end)(s32 id);
};


struct Unk_020932bc_V32 {
    s32 x, y, z;
    void Set(s32 a, s32 b, s32 c)
    {
        x = a;
        y = b;
        z = c;
    }
};

class EffectModel;

class EffectModelObj {
public:
    void initAtSlot(s32 s);

    /* 0x00 */ s32 active;
    /* 0x04 */ Unk_020932bc_V32 position;
    /* 0x10 */ Unk_020932bc_V32 scale;
    /* 0x1c */ Unk_020932bc_V16 rotation;
};

static inline EffectModelObj *EffectModel_Obj(EffectModel *m) { return (EffectModelObj *)m; }

extern "C" {
void MI_CpuCopy8(const void *src, void *dst, u32 n);
void MI_CpuFill8(void *dst, u32 v, u32 n);
s32 FX_Div(s32 numer, s32 denom);
s32 func_01ffcb0c(s32 v1, s32 v2);
s32 _s32_div_f(s32 a, s32 b);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern const s16 data_02135f44[4096 * 2];
s32 Weather_GetFallingPrecip(void);
s16 Sky_GetLightColor(s32 i);
BOOL GroundSeason_IsSnow();
extern u8 gFieldSceneKind;
}

static inline BOOL Unk_020935e8_IsOne(u8 v)
{
    return v == 1 ? TRUE : FALSE;
}










extern const VecFx32 data_020d021c;
extern const VecFx32 data_020d0228;
extern const VecFx32 data_020d0234;
extern const VecFx32 data_020d0240;
extern const VecFx32 data_020d024c;
extern const VecFx32 data_020d0258;
extern const VecFx32 data_020d0264;
extern const VecFx32 data_020d0270;
extern const VecFx32 data_020d027c;
extern const VecFx32 data_020d0288;
extern const VecFx32 data_020d0294;
extern const VecFx32 data_020d02a0;
extern const VecFx32 data_020d02ac;
extern const VecFx32 data_020d02b8;
extern const VecFx32 data_020d02c4;
extern const VecFx32 data_020d02d0;
extern const VecFx32 data_020d02dc;
extern const VecFx32 data_020d02e8;
extern const VecFx32 data_020d02f4;
extern const VecFx32 data_020d0300;
extern const VecFx32 data_020d030c;
extern const VecFx32 data_020d0318;
extern const VecFx32 data_020d0324;
extern const VecFx32 data_020d0330;
extern const VecFx32 data_020d033c;
extern const VecFx32 data_020d0348;
extern const VecFx32 data_020d0354;
extern const VecFx32 data_020d0360;
extern const VecFx32 data_020d036c;
extern const VecFx32 data_020d0378;
extern const VecFx32 data_020d0384;
extern const VecFx32 data_020d0390;
extern const VecFx32 data_020d039c;
extern const VecFx32 data_020d03a8;
extern const VecFx32 data_020d03b4;
extern const VecFx32 data_020d03c0;

extern "C" void EffectCb_TintOnly(EffectSplEmitter *o)
{
    EffectSpl_ApplySceneTint(o);
}

extern "C" void EffectCb_InitOneShot(EffectSplEmitter *o)
{
    o->posX = gEffectManager.scratchSlot.x + o->resource->p_base->pos.x;
    o->posY = gEffectManager.scratchSlot.y + o->resource->p_base->pos.y;
    o->posZ = gEffectManager.scratchSlot.z + o->resource->p_base->pos.z;
    EffectSpl_ApplySceneTint(o);
}

extern "C" void EffectCb_PlaceFacing(EffectSplEmitter *o, EffectSlot *e)
{
    s32 idx;
    u16 ang = e->angle;
    o->posX = e->x + o->resource->p_base->pos.x;
    o->posY = e->y + o->resource->p_base->pos.y;
    o->posZ = e->z + o->resource->p_base->pos.z;
    idx = (ang >> 4) * 2;
    o->axis.x = data_02135f44[idx];
    o->axis.y = 0;
    o->axis.z = data_02135f44[idx + 1];
    EffectSpl_ApplySceneTint(o);
}

extern "C" void EffectCb_InitOneShotFacing(EffectSplEmitter *o)
{
    EffectCb_PlaceFacing(o, &gEffectManager.scratchSlot);
}

extern "C" void EffectCb_PlaceFacingBack(EffectSplEmitter *o, EffectSlot *e)
{
    s16 ang = (s16)(e->angle + 0x8000);
    s32 idx;
    o->posX = e->x + o->resource->p_base->pos.x;
    o->posY = e->y + o->resource->p_base->pos.y;
    o->posZ = e->z + o->resource->p_base->pos.z;
    idx = ((u16)ang >> 4) * 2;
    o->axis.x = data_02135f44[idx];
    o->axis.y = 0;
    o->axis.z = data_02135f44[idx + 1];
    EffectSpl_ApplySceneTint(o);
}

extern "C" void EffectCb_InitOneShotFacingBack(EffectSplEmitter *o)
{
    EffectCb_PlaceFacingBack(o, &gEffectManager.scratchSlot);
}

extern "C" void EffectCb_InitOneShotSetUnk54(EffectSplEmitter *o, s32 x)
{
    EffectCb_InitOneShot(o);
    o->baseScale = x;
}

extern "C" void EffectCb_PlaceEmitter(EffectSplEmitter *o, EffectSlot *e, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 pos;
    VecFx32 v1;
    VecFx32 v2;
    pos.x = e->x;
    pos.y = e->y;
    pos.z = e->z;
    if (a != NULL) {
        v1.x = a->x;
        v1.y = a->y;
        v1.z = a->z;
        Vec_RotateY(&v1, e->angle);
        VEC_Add(&pos, &v1, &pos);
    }
    o->posX = pos.x + o->resource->p_base->pos.x;
    o->posY = pos.y + o->resource->p_base->pos.y;
    o->posZ = pos.z + o->resource->p_base->pos.z;
    if (b != NULL) {
        v2.x = b->x;
        v2.y = b->y;
        v2.z = b->z;
        Vec_RotateY(&v2, e->angle);
        if (Vec_SafeNormalize(&v2) != 0) {
            s32 y = v2.y;
            s32 z = v2.z;
            s32 x = v2.x;
            o->axis.x = x;
            o->axis.y = y;
            o->axis.z = z;
        }
    }
}

extern "C" void EffectCb_InitOneShotOffset(EffectSplEmitter *o, const VecFx32 *a, const VecFx32 *b)
{
    EffectCb_PlaceEmitter(o, &gEffectManager.scratchSlot, a, b);
    EffectSpl_ApplySceneTint(o);
}

extern "C" s32 Effect_StartOneShot(s32 p0, s32 p1, VecFx32 *p2, s16 *p3, s16 *e, EffectOneShotCb const *f)
{
    EffectOneShotCb const *t = f;
    s32 r;
    if (t == NULL) t = sEffectDefaultOneShotCbs;
    r = 3;
    gEffectManager.scratchSlot.set(-1, p1, p2, p3, e, -1);
    if (EffectSpl_CreateOneShot(p0, p2, p3, t)) r = 1;
    return r;
}

extern "C" void Effect_EndDefault(s32 id)
{
    gEffectManager.setLife(id, 0);
}

extern "C" s32 EffectCb_CountdownTracked(EffectEmitterEntry *o)
{
    EffectEmitterTag h = o->tag;
    EffectSlot *e = &gEffectManager.slots[h.poolIndex];
    BOOL r = FALSE;
    if (e->handle != -1 && e->life != 0) {
        if (e->life > 0) e->life--;
        r = TRUE;
    }
    if (r == 0) e->clear();
    return r;
}

extern "C" void EffectCb_InitTrackedOffset(EffectEmitterEntry *o, const VecFx32 *a, const VecFx32 *b)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    EffectEmitterTag h = o->tag;
    EffectCb_PlaceEmitter(o->emitter, g, a, b);
    EffectSpl_ApplySceneTint(o->emitter);
    MI_CpuCopy8(g, &gEffectManager.slots[h.poolIndex], sizeof(EffectSlot));
}

extern "C" s32 EffectCb_FollowTrackedOffset(EffectEmitterEntry *o, const VecFx32 *a, const VecFx32 *b)
{
    EffectEmitterTag h = o->tag;
    BOOL r;
    EffectSlot *e = &gEffectManager.slots[h.poolIndex];
    r = FALSE;
    if (e->handle != -1 && e->life != 0) {
        EffectCb_PlaceEmitter(o->emitter, e, a, b);
        if (e->life > 0) e->life--;
        r = TRUE;
    }
    if (r == 0) e->clear();
    return r;
}

extern "C" void EffectCb_InitTracked(EffectEmitterEntry *o)
{
    EffectCb_InitTrackedOffset(o, NULL, NULL);
}

extern "C" s32 EffectCb_FollowTracked(EffectEmitterEntry *o)
{
    return EffectCb_FollowTrackedOffset(o, NULL, NULL);
}

extern "C" s32 Effect_StartTracked(s32 p0, s32 p1, VecFx32 *p2, s16 *p3, s16 *e, EffectEmitterCbs *f)
{
    EffectEmitterCbs *t = f;
    s32 r;
    if (t == NULL) t = sEffectDefaultTrackedCbs;
    r = 3;
    EffectSlot *const g = &gEffectManager.scratchSlot;
    g->set(gEffectManager.nextHandle, p1, p2, p3, e, -1);
    if (EffectSpl_CreateTracked(p0, p2, p3, t)) r = 0;
    g->clear();
    return r;
}

extern "C" s32 Effect_SpawnParticleLandings(EffectSplEmitter *o, s32 p1, EffectOneShotCb const *p2, s32 p3,
                                            EffectOneShotCb const *s0, s32 p5, EffectOneShotCb const *s2, s32 p6,
                                            EffectOneShotCb const *s4)
{
    P *n;
    VecFx32 pos;
    BOOL result;
    n = o->particles;
    pos = gVec3Zero;
    result = FALSE;
    if (n != NULL) {
        result = TRUE;
        while (n != NULL) {
            GroundInfo g;
            pos.x = n->pos.x + n->epos.x;
            pos.y = n->pos.y + n->epos.y;
            pos.z = n->pos.z + n->epos.z;
            g.initAtPos(&pos, 0, 0);
            if (g.waterKind != 0) {
                if (pos.y <= g.waterSurfaceY) {
                    pos.y = g.waterSurfaceY;
                    if (p1 != -1) Effect_StartOneShot(p1, 100, &pos, 0, 0, p2);
                    if (p3 != -1) Effect_StartOneShot(p3, 100, &pos, 0, 0, s0);
                    n->age = n->life;
                }
            } else if (pos.y <= 0) {
                if (p5 != -1) {
                    pos.y = 0;
                    Effect_StartOneShot(p5, 100, &pos, 0, 0, s2);
                }
                if (p6 != -1) {
                    pos.y = 0;
                    Effect_StartOneShot(p6, 100, &pos, 0, 0, s4);
                }
                n->age = n->life;
            }
            n = n->next;
        }
    }
    return result;
}

s32 EffectSplEmitter::spawnLandingEffects(s32 id1, EffectOneShotCb const *d1, s32 id2, EffectOneShotCb const *d2, s32 id3,
        EffectOneShotCb const *d3, s32 id4, EffectOneShotCb const *d4)
{
    VecFx32 v;
    BOOL result;
    P *n;
    n = particles;
    v.x = gVec3Zero.x;
    v.y = gVec3Zero.y;
    v.z = gVec3Zero.z;
    result = FALSE;
    if (n) {
        result = TRUE;
        for (; n;) {
            GroundInfo o;
            v.x = n->pos.x + n->epos.x;
            v.y = n->pos.y + n->epos.y;
            v.z = n->pos.z + n->epos.z;
            o.initAtPos(&v, 0, 0);
            if (o.waterKind != 0) {
                s32 h = ((GroundInfoBase *)(&o))->getWaterSurfaceY();
                if (v.y <= h) {
                    v.y = h;
                    if (id1 != -1) {
                        Effect_StartOneShot(id1, 0x64, &v, 0, 0, d1);
                    }
                    if (id2 != -1) {
                        Effect_StartOneShot(id2, 0x64, &v, 0, 0, d2);
                    }
                    n->age = n->life;
                }
            } else if (v.y <= 0) {
                if (id3 != -1) {
                    v.y = 0;
                    Effect_StartOneShot(id3, 0x64, &v, 0, 0, d3);
                }
                if (id4 != -1) {
                    v.y = 0;
                    Effect_StartOneShot(id4, 0x64, &v, 0, 0, d4);
                }
                n->age = n->life;
            }
            n = n->next;
        }
    }
    return result;
}

s32 EffectEmitterEntry::updateLanding(s32 id1, EffectOneShotCb const *d1, s32 id2, EffectOneShotCb const *d2, s32 id3,
        EffectOneShotCb const *d3, s32 id4, EffectOneShotCb const *d4)
{
    EffectEmitterTag id = tag;
    BOOL r;
    EffectSlot *e;
    e = &gEffectManager.slots[id.poolIndex];
    r = FALSE;
    if (e->handle != -1) {
        if (e->life == -1) {
            if (emitter->particleCount > 0) {
                e->life = 0;
            }
            r = TRUE;
        }
        if (e->life == 0) {
            r = Effect_SpawnParticleLandings(emitter, id1, d1, id2, d2, id3, d3, id4, d4);
        }
    }
    if (!r) {
        e->clear();
    }
    return r;
}

extern "C" void EffectModel_InitDefault(EffectModel *m)
{
    EffectModelObj *self = EffectModel_Obj(m);
    EffectSlot *g = &gEffectManager.scratchSlot;
    Unk_020932bc_V32 *p = &self->position;
    p->x = g->x;
    p->y = g->y;
    p->z = g->z;
    Unk_020932bc_V32 *q = &self->scale;
    q->x = 0x1000;
    q->y = 0x1000;
    q->z = 0x1000;
    Unk_020932bc_V16 *r = &self->rotation;
    r->x = 0;
    r->y = 0;
    r->z = 0;
}

extern "C" s32 Effect_StartModel(s32 kind, s32 a, VecFx32 *b, s16 *c, s16 *d, void (*fn)(EffectModel *))
{
    void (*f)(EffectModel *) = fn;
    if (f == 0) {
        f = EffectModel_InitDefault;
    }
    gEffectManager.scratchSlot.set(-1, a, b, c, d, -1);
    EffectModel_Start(kind, f);
    return 1;
}

extern "C" s32 Effect_CreateKind00(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 t, result, kind;
    EffectOneShotCb const *p;
    o.initAtPos(b, 0, 0);
    t = o.attr;
    p = data_020e1480;
    result = 3;
    kind = 2;
    if (Unk_020935e8_IsOne(gFieldSceneKind)) {
        if (t == 9 || t == 3) {
            result = Effect_StartOneShot(2, a, b, c, d, p);
        }
    } else {
        if (t == 0x16) {
            kind = 0x21;
            if (c != 0) *c = 0;
            p = data_020e16d4;
        } else if (Weather_GetFallingPrecip() == 1) {
            kind = 0x20;
            if (c != 0) *c = 0;
            p = data_020e16d4;
        } else if (t != 3) {
            if (t == 0x13) kind = 0x17;
        } else if (GroundSeason_IsSnow() != 0) {
            kind = 0x18;
            p = 0;
        }
        result = Effect_StartOneShot(kind, a, b, c, d, p);
    }
    return result;
}

void EffectEmitterEntry::initAxisUpForward()
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    EffectEmitterTag id = tag;
    VecFx32 v;
    EffectSplEmitter *p;
    v.x = 0;
    v.y = 0xb50;
    v.z = 0xb50;
    p = emitter;
    p->posX = g->x + p->resource->p_base->pos.x;
    p->posY = g->y + p->resource->p_base->pos.y;
    p->posZ = g->z + p->resource->p_base->pos.z;
    EffectSpl_ApplySceneTint(emitter);
    Vec_RotateY(&v, g->angle);
    s32 ty = v.y;
    s32 tz = v.z;
    p = emitter;
    s32 tx = v.x;
    p->axis.Set(tx, ty, tz);
    MI_CpuCopy8(g, &gEffectManager.slots[id.poolIndex], sizeof(EffectSlot));
}

s32 EffectEmitterEntry::updateLanding1F1D()
{
    return updateLanding(0x1f, data_020e16d4, 0x1d, data_020e16d4, 0x1d, data_020e16d4, -1, 0);
}

s32 EffectEmitterEntry::updateLanding1F1EB()
{
    return updateLanding(0x1f, data_020e16d4, 0x1e, data_020e16d4, 0x1e, data_020e16d4, -1, 0);
}

extern "C" s32 Effect_CreateKind01(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 t, result;
    o.initAtPos(b, 0, 0);
    t = o.attr;
    result = 3;
    if (Unk_020935e8_IsOne(gFieldSceneKind)) {
        if (t == 9 || t == 3) {
            result = Effect_StartOneShot(0x19, a, b, c, d, data_020e14b4);
        }
    } else if (t == 0x16 || Weather_GetFallingPrecip() == 1) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, 0, -1);
        if (EffectSpl_CreateTracked(0x1b, b, c, data_020e14d4) != 0) {
            result = 2;
        }
    } else if (t == 3 && GroundSeason_IsSnow() != 0) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, 0, -1);
        if (EffectSpl_CreateTracked(0x1c, b, c, data_020e14ec) != 0) {
            result = 2;
        }
    } else {
        s32 kind;
        if (t == 0x13) {
            kind = 0x1a;
        } else {
            kind = 0x19;
        }
        result = Effect_StartOneShot(kind, a, b, c, d, data_020e14b4);
    }
    return result;
}

void EffectSplEmitter::initKind02()
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    s32 ang = (s16)(g->angle + 0x8000);
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0x1000;
    posX = g->x + resource->p_base->pos.x;
    posY = g->y + resource->p_base->pos.y;
    posZ = g->z + resource->p_base->pos.z;
    simpleCollisionY = g->y + 0x333;
    Vec_RotateX(&v, 0xffffe000);
    Vec_RotateY(&v, ang);
    s32 ty = v.y;
    s32 tz = v.z;
    s32 tx = v.x;
    axis.Set(tx, ty, tz);
    EffectSpl_ApplySceneTint(this);
}

extern "C" s32 Effect_CreateKind02(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartOneShot(0x29, a, b, c, d, data_020e1474);
}

extern "C" s32 Effect_CreateKind03(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartOneShot(0x2a, a, b, c, d, data_020e150c);
}

extern "C" s32 Effect_CreateKind06(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 r, kind;
    o.initAtPos(b, 0, 0);
    if (o.attr == 0x13) {
        kind = 0x2d;
    } else {
        kind = 0x2b;
    }
    r = Effect_StartOneShot(kind, a, b, c, d, 0);
    return r;
}

extern "C" void EffectKind07_InitEmitter0(EffectSplEmitter *a)
{
    EffectCb_InitOneShotOffset(a, 0, &data_020d0390);
}

extern "C" void EffectKind07_InitEmitter1(EffectSplEmitter *a)
{
    EffectCb_InitOneShotOffset(a, 0, &data_020d0318);
}

extern "C" s32 Effect_CreateKind07(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 r, kind;
    o.initAtPos(b, 0, 0);
    if (o.attr == 0x13) {
        kind = 0x2e;
    } else {
        kind = 0x2c;
    }
    r = Effect_StartOneShot(kind, a, b, c, d, data_020e15c4);
    return r;
}

extern "C" s32 Effect_CreateKind08(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 r, kind;
    o.initAtPos(b, 0, 0);
    if (o.attr == 0x13) {
        kind = 0x30;
    } else {
        kind = 0x2f;
    }
    r = Effect_StartOneShot(kind, a, b, c, d, 0);
    return r;
}

extern "C" void EffectKind09_InitEmitter0(EffectSplEmitter *a)
{
    EffectCb_InitOneShotOffset(a, &data_020d027c, &data_020d02f4);
}

extern "C" s32 Effect_CreateKind09(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 r, kind;
    o.initAtPos(b, 0, 0);
    if (o.attr == 0x13) {
        kind = 0x32;
    } else {
        kind = 0x31;
    }
    r = Effect_StartOneShot(kind, a, b, c, d, data_020e1608);
    return r;
}

extern "C" s32 Effect_CreateKind0A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 t, result;
    o.initAtPos(b, 0, 0);
    t = o.attr;
    result = 3;
    if (Weather_GetFallingPrecip() == 1) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x36, b, c, data_020e1594) != 0) {
            result = 2;
        }
    } else if (GroundSeason_IsSnow() != 0 && t == 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, 0, -1);
        if (EffectSpl_CreateTracked(0x35, b, c, data_020e15e4) != 0) {
            result = 2;
        }
    } else {
        s32 kind;
        if (t == 0x13) {
            kind = 0x34;
        } else {
            kind = 0x33;
        }
        result = Effect_StartOneShot(kind, a, b, c, d, 0);
    }
    return result;
}

void EffectModelObj::initAtSlot(s32 s)
{
    EffectSlot *g = &gEffectManager.scratchSlot;
    Unk_020932bc_V32 *p = &position;
    p->x = g->x;
    p->y = g->y;
    p->z = g->z;
    Unk_020932bc_V32 *q = &scale;
    q->x = s;
    q->y = s;
    q->z = s;
    Unk_020932bc_V16 *r = &rotation;
    r->x = 0;
    r->y = 0;
    r->z = 0;
}

extern "C" void EffectModel_InitUnitScale(EffectModel *m)
{
    EffectModel_Obj(m)->initAtSlot(0x1000);
}

s32 EffectEmitterEntry::updateLanding1F1E()
{
    return updateLanding(0x1f, data_020e16d4, 0x1e, data_020e16d4, 0x1e, data_020e16d4, -1, 0);
}

extern "C" s32 Effect_StartWaterColumn(s32 a, VecFx32 *b, s16 *c, s16 *d, EffectEmitterCbs *e, EffectOneShotCb const *f,
                                       void (*fn)(EffectModel *))
{
    VecFx32 *v = b;
    GroundInfo o;
    s32 result;
    o.initAtPos(v, 0, 0);
    result = 3;
    if (o.waterKind != 0) {
        v->y = o.waterSurfaceY;
    }
    if (Effect_StartOneShot(0x4a, a, v, c, d, f) < 3) {
        Effect_StartModel(2, a, v, c, d, fn);
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, v, c, d, -1);
        if (EffectSpl_CreateTracked(0x45, v, c, e) != 0) {
            result = 2;
        }
    }
    gEffectManager.scratchSlot.clear();
    return result;
}

extern "C" s32 Effect_CreateKind0B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartWaterColumn(a, b, c, d, data_020e152c, 0, EffectModel_InitUnitScale);
}

s32 EffectEmitterEntry::updateLanding5F()
{
    return updateLanding(0x5f, data_020e16d4, -1, 0, -1, 0, -1, 0);
}

extern "C" s32 Effect_CreateKind0C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x37, a, b, c, d, 0);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x5e, b, c, data_020e15ec) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" s32 Effect_CreateKind0D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x38, a, b, c, d, 0);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x5e, b, c, data_020e14fc) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" s32 Effect_CreateKind0F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0x3a, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind10(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x3b, a, b, c, d, 0);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x5e, b, c, data_020e15dc) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" void EffectKind0E_InitEmitter0(EffectEmitterEntry *p) {
    EffectEmitterTag id;
    GroundInfo o;
    VecFx32 v;
    VecFx32 pos;
    EffectSplEmitter *b;
    EffectSlot *const g = &gEffectManager.scratchSlot;
    id = p->tag;
    b = p->emitter;
    b->posX = g->x + b->resource->p_base->pos.x;
    b->posY = g->y + b->resource->p_base->pos.y;
    b->posZ = g->z + b->resource->p_base->pos.z;
    EffectSpl_ApplySceneTint(p->emitter);
    pos.x = g->x;
    pos.y = g->y;
    pos.z = g->z;
    o.initAtPos(&pos, 0, 0);
    if (o.waterKind != 0) {
        v.x = o.flowDir;
        v.y = o.flowDirY;
        v.z = o.flowDirZ;
        if (Vec_SafeNormalize(&v) != 0) {
            s32 vy = v.y;
            s32 vz = v.z;
            EffectSplEmitter *b2 = p->emitter;
            b2->axis.x = v.x;
            b2->axis.y = vy;
            b2->axis.z = vz;
        }
    }
    MI_CpuCopy8(g, &gEffectManager.slots[id.poolIndex], sizeof(EffectSlot));
}

extern "C" s32 EffectKind0E_UpdateEmitter0(EffectEmitterEntry *p) {
    EffectEmitterTag id;
    GroundInfo o;
    VecFx32 v;
    VecFx32 pos;
    s32 s;
    EffectSlot *r;
    id = p->tag;
    r = &gEffectManager.slots[id.poolIndex];
    s = 0;
    s32 m1 = -1;
    if (r->handle != m1 && r->life != 0) {
        EffectSplEmitter *b = p->emitter;
        b->posX = r->x + b->resource->p_base->pos.x;
        b->posY = r->y + b->resource->p_base->pos.y;
        b->posZ = r->z + b->resource->p_base->pos.z;
        pos.x = r->x;
        pos.y = r->y;
        pos.z = r->z;
        o.initAtPos(&pos, 0, 0);
        if (o.waterKind != 0) {
            v.x = o.flowDir;
            v.y = o.flowDirY;
            v.z = o.flowDirZ;
            if (Vec_SafeNormalize(&v) != 0) {
                s32 vy = v.y;
                s32 vz = v.z;
                EffectSplEmitter *b2 = p->emitter;
                b2->axis.x = v.x;
                b2->axis.y = vy;
                b2->axis.z = vz;
            }
        }
        if (r->life > 0) r->life--;
        s = 1;
    }
    if (s == 0) r->clear();
    return s;
}

extern "C" s32 Effect_CreateKind0E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x39, a, b, c, d, data_020e1504); }

extern "C" s32 EffectKind11_UpdateEmitter2(EffectEmitterEntry *p) {
    EffectEmitterTag id;
    s32 s;
    EffectSlot *r;
    id = p->tag;
    r = &gEffectManager.slots[id.poolIndex];
    s = 0;
    s32 m1 = -1;
    if (r->handle != m1 && r->life != 0) {
        EffectSplEmitter *b = p->emitter;
        b->posX = r->x + b->resource->p_base->pos.x;
        b->posY = r->y + b->resource->p_base->pos.y;
        b->posZ = r->z + b->resource->p_base->pos.z;
        Effect_SpawnParticleLandings(p->emitter, 0x5f, data_020e16d4, m1, 0, m1, 0, m1, 0);
        if (r->life > 0) r->life--;
        s = 1;
    }
    if (s == 0) {
        p->emitter->stateFlags |= 2;
        EffectSplEmitter *b = p->emitter;
        if (b->particleCount > 0) s = Effect_SpawnParticleLandings(b, 0x5f, data_020e16d4, -1, 0, -1, 0, -1, 0);
    }
    if (s == 0) r->clear();
    return s;
}

extern "C" s32 Effect_CreateKind11(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x3c, a, b, c, d, data_020e16a4); }

extern "C" s32 Effect_CreateKind12(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x46, a, b, c, d, 0);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x5e, b, c, data_020e1584) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" void EffectKind13_InitEmitter0(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x1ccd); }

extern "C" void EffectKind13_InitEmitter1(EffectSplEmitter *p) { EffectCb_InitOneShot(p); }

extern "C" s32 EffectKind13_UpdateEmitter0(EffectEmitterEntry *p) { return ((EffectEmitterEntry *)p)->updateLanding(0x5f, data_020e16d4, -1, 0, -1, 0, -1, 0); }

extern "C" s32 Effect_CreateKind13(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x47, a, b, c, d, data_020e15a4);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x75, b, c, data_020e157c) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" void EffectKind14_InitEmitter0B(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x1800); }

extern "C" void EffectKind14_InitEmitter2(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x1333); }

extern "C" void EffectKind14_InitEmitter0A(EffectEmitterEntry *p) { EffectCb_InitTracked(p); p->emitter->baseScale = 0x1333; }

extern "C" s32 Effect_CreateKind14(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x48, a, b, c, d, data_020e1614);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x75, b, c, data_020e15b4) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" void EffectKind15_InitEmitter0(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x2000); }

extern "C" void EffectKind15_InitEmitter2(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x199a); }

extern "C" s32 Effect_CreateKind15(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    s32 t = Effect_StartOneShot(0x49, a, b, c, d, data_020e1620);
    if (t < 3) {
        gEffectManager.scratchSlot.set(gEffectManager.nextHandle, a, b, c, d, -1);
        if (EffectSpl_CreateTracked(0x75, b, c, data_020e151c) != 0) r = 2;
    }
    gEffectManager.scratchSlot.clear();
    return r;
}

extern "C" void EffectKind16_InitEmitter0B(EffectEmitterEntry *p) { EffectCb_InitTracked(p); p->emitter->initVelMagAxis = 0x800; }

extern "C" void EffectKind16_InitEmitter0A(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x119a); }

extern "C" void EffectKind16_InitModel(EffectModel *m) {
    EffectModel_Obj(m)->initAtSlot(0xccd);
}

extern "C" s32 Effect_CreateKind16(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartWaterColumn(a, b, c, d, data_020e1574, data_020e147c, EffectKind16_InitModel);
}

extern "C" void EffectKind17_InitEmitter0B(EffectEmitterEntry *p) { EffectCb_InitTracked(p); p->emitter->initVelMagAxis = 0x99a; }

extern "C" void EffectKind17_InitEmitter0A(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x14cd); }

extern "C" void EffectKind17_InitModel(EffectModel *m) {
    EffectModel_Obj(m)->initAtSlot(0x119a);
}

extern "C" s32 Effect_CreateKind17(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartWaterColumn(a, b, c, d, data_020e1524, data_020e14bc, EffectKind17_InitModel);
}

extern "C" void EffectKind19_InitEmitter0B(EffectEmitterEntry *p) { EffectCb_InitTracked(p); p->emitter->initVelMagAxis = 0xc00; }

extern "C" void EffectKind19_InitEmitter0A(EffectSplEmitter *p) { EffectCb_InitOneShotSetUnk54(p, 0x1ccd); }

extern "C" void EffectKind19_InitModel(EffectModel *m) {
    EffectModel_Obj(m)->initAtSlot(0x14cd);
}

extern "C" s32 Effect_CreateKind19(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartWaterColumn(a, b, c, d, data_020e15f4, data_020e1494, EffectKind19_InitModel);
}

extern "C" void EffectKind1A_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, 0, 0); p->emitter->baseScale = 0x4cd; }

extern "C" s32 Effect_CreateKind1A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, data_020e1534); }

extern "C" void EffectKind1B_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, 0, 0); p->emitter->baseScale = 0x666; }

extern "C" s32 Effect_CreateKind1B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, data_020e153c); }

extern "C" void EffectKind1C_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, 0, 0); p->emitter->baseScale = 0x800; }

extern "C" s32 Effect_CreateKind1C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, data_020e15ac); }

extern "C" void EffectKind1D_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, 0, 0); p->emitter->baseScale = 0x99a; }

extern "C" s32 Effect_CreateKind1D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, data_020e154c); }

extern "C" void EffectKind1E_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, 0, 0); p->emitter->baseScale = 0xb33; }

extern "C" s32 Effect_CreateKind1E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, data_020e14e4); }

extern "C" void EffectKind1F_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, 0, 0); p->emitter->baseScale = 0xccd; }

extern "C" s32 Effect_CreateKind1F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, data_020e14dc); }

extern "C" s32 Effect_CreateKind21(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x73, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind22(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    GroundInfo o;
    s32 r;
    o.initAtPos(b, 0, 0);
    u32 t = o.attr;
    r = 3;
    if (Unk_020935e8_IsOne(gFieldSceneKind)) {
        if (t == 9 || t == 3) {
            r = Effect_StartOneShot(0x4b, a, b, c, d, 0);
        }
    } else if (t == 0x16 || Weather_GetFallingPrecip() == 1) {
        r = Effect_StartOneShot(0x4d, a, b, c, d, 0);
    } else if (t == 3 && GroundSeason_IsSnow()) {
        r = Effect_StartOneShot(0x4e, a, b, c, d, 0);
    } else {
        r = Effect_StartOneShot(t == 0x13 ? 0x4c : 0x4b, a, b, c, d, 0);
    }
    return r;
}

extern "C" void EffectKind23_InitEmitter0(EffectSplEmitter *a) {
    EffectCb_InitOneShotOffset(a, 0, &data_020d033c);
}

extern "C" s32 Effect_CreateKind23(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    GroundInfo o;
    o.initAtPos(b, 0, 0);
    s32 id;
    if (o.attr == 0x13) {
        id = 0x6f;
    } else {
        id = 0x6e;
    }
    s32 res = Effect_StartOneShot(id, a, b, c, d, data_020e14c4);
    return res;
}

extern "C" void EffectKind24_InitEmitter0(EffectSplEmitter *a) {
    EffectCb_InitOneShotOffset(a, 0, &data_020d0348);
}

extern "C" void EffectKind24_InitModel(EffectModel *m) {
    EffectModelObj *o = EffectModel_Obj(m);
    EffectSlot *const d = &gEffectManager.scratchSlot;
    Unk_020932bc_V32 *pv = &o->position;
    pv->x = d->x;
    pv->y = d->y;
    pv->z = d->z;
    Unk_020932bc_V32 *ps = &o->scale;
    ps->x = 0x1000;
    ps->y = 0x1000;
    ps->z = 0x1000;
    o->rotation.x = 0;
    o->rotation.y = d->angle;
    o->rotation.z = 0;
}

extern "C" s32 Effect_CreateKind24(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    if (Effect_StartOneShot(0x59, a, b, c, d, data_020e165c) < 3) {
        Effect_StartModel(r, a, b, c, d, EffectKind24_InitModel);
        r = 1;
    }
    return r;
}

extern "C" s32 EffectKind25_UpdateEmitter0(EffectEmitterEntry *o) {
    if (EffectCb_FollowTrackedOffset(o, 0, 0) == 0) {
        for (P *n = o->emitter->particles; n != 0; n = n->next) {
            n->age = n->life;
        }
        return 0;
    }
    return 1;
}

extern "C" s32 Effect_CreateKind25(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x5a, a, b, c, d, data_020e175c);
}

extern "C" void EffectKind26_InitEmitter0(EffectEmitterEntry *a) {
    EffectCb_InitTrackedOffset(a, 0, &data_020d02c4);
}

extern "C" s32 EffectKind26_UpdateEmitter0(EffectEmitterEntry *o) {
    s32 r;
    EffectEmitterTag idx;
    VecFx32 vec;
    idx = o->tag;
    EffectSlot *e = &gEffectManager.slots[idx.poolIndex];
    r = 0;
    if (e->handle != -1 && e->life != 0) {
        vec.x = r;
        vec.y = r;
        vec.z = 0x1000;
        EffectSplEmitter *in = o->emitter;
        in->posX = e->x + in->resource->p_base->pos.x;
        in->posY = e->y + in->resource->p_base->pos.y;
        in->posZ = e->z + in->resource->p_base->pos.z;
        Vec_RotateY(&vec, e->angle);
        s32 ty = vec.y;
        s32 tz = vec.z;
        EffectSplEmitter *p = o->emitter;
        s32 tx = vec.x;
        p->axis.x = tx;
        p->axis.y = ty;
        p->axis.z = tz;
        o->emitter->spawnLandingEffects(0x71, data_020e16d4, -1, NULL, 0x71, data_020e16d4, 0x72, data_020e16d4);
        if (e->life > 0) {
            e->life = e->life - 1;
        }
        r = 1;
    }
    if (r == 0) {
        o->emitter->stateFlags |= 2;
        if (o->emitter->particleCount > 0) {
            r = o->emitter->spawnLandingEffects(0x71, data_020e16d4, -1, NULL, 0x71, data_020e16d4, 0x72, data_020e16d4);
        }
    }
    if (r == 0) {
        e->clear();
    }
    return r;
}

extern "C" s32 Effect_CreateKind26(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x70, a, b, c, d, data_020e15bc);
}

extern "C" s32 Effect_CreateKind27(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    GroundInfo o;
    o.initAtPos(b, 0, 0);
    u32 t = o.attr;
    if (t == 0x13 || (GroundSeason_IsSnow() && t == 3)) {
        s32 res = Effect_StartOneShot(0x55, a, b, c, d, data_020e16d4);
        return res;
    }
    return 3;
}

extern "C" s32 Effect_CreateKind28(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    GroundInfo o;
    o.initAtPos(b, 0, 0);
    u32 t = o.attr;
    if (t == 0x13 || (GroundSeason_IsSnow() && t == 3)) {
        s32 res = Effect_StartOneShot(0x56, a, b, c, d, data_020e16d4);
        return res;
    }
    return 3;
}

extern "C" void EffectCb_AlignFirstParticle(EffectSplEmitter *o, s32 flag) {
    if (flag == 1) {
        P *n = o->particles;
        if (n != 0) {
            n->rot0 = Math_Atan2(o->axis.x, o->axis.z);
            o->callback = 0;
        }
    }
}

extern "C" void EffectCb_PlaceRotatedOffset(EffectSplEmitter *o, const VecFx32 *v, s32 ang) {
    EffectSlot *const d = &gEffectManager.scratchSlot;
    s16 a = (s16)(*(volatile s16 *)&d->angle + ang);
    VecFx32 t;
    t.x = v->x;
    t.y = v->y;
    t.z = v->z;
    Vec_RotateY(&t, *(volatile s16 *)&d->angle);
    VEC_Add(&t, &d->pos, &t);
    s32 idx = ((u16)a >> 4) * 2;
    o->posX = t.x + o->resource->p_base->pos.x;
    o->posY = t.y + o->resource->p_base->pos.y;
    o->posZ = t.z + o->resource->p_base->pos.z;
    o->axis.x = data_02135f44[idx];
    o->axis.y = 0;
    o->axis.z = data_02135f44[idx + 1];
    EffectSpl_ApplySceneTint(o);
    o->callback = EffectCb_AlignFirstParticle;
}

extern "C" void EffectKind29_InitEmitter0(EffectSplEmitter *o) {
    EffectCb_PlaceRotatedOffset(o, &data_020d0354, -0x7530);
}

extern "C" s32 Effect_StartOnSandOrSnow(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 e, EffectOneShotCb const *f) {
    GroundInfo o;
    o.initAtPos(b, 0, 0);
    u32 t = o.attr;
    s32 r = -1;
    if (t == 0x13 || (GroundSeason_IsSnow() && t == 3)) {
        r = e;
    }
    if (r != -1) {
        s32 res = Effect_StartOneShot(e, a, b, c, d, f);
        return res;
    }
    return 3;
}

extern "C" s32 Effect_CreateKind29(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOnSandOrSnow(a, b, c, d, 0x58, data_020e1484);
}

extern "C" void EffectKind2A_InitEmitter0(EffectSplEmitter *o) {
    EffectCb_PlaceRotatedOffset(o, &data_020d0360, 0);
}

extern "C" s32 Effect_CreateKind2A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOnSandOrSnow(a, b, c, d, 0x58, data_020e14ac);
}

extern "C" void EffectKind2B_InitEmitter0B(EffectSplEmitter *o) {
    EffectCb_PlaceRotatedOffset(o, &data_020d036c, 0);
}

extern "C" void EffectKind2B_InitEmitter0A(EffectSplEmitter *o) {
    EffectCb_PlaceRotatedOffset(o, &data_020d0378, 0);
}

extern "C" s32 Effect_CreateKind2B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    if (Effect_StartOnSandOrSnow(a, b, c, d, 0x57, data_020e14a4) == 1) {
        return Effect_StartOnSandOrSnow(a, b, c, d, 0x57, data_020e1478);
    }
    return 3;
}

extern "C" void EffectKind2C_InitEmitter0B(EffectSplEmitter *o) {
    EffectCb_PlaceRotatedOffset(o, &data_020d0228, 0);
}

extern "C" void EffectKind2C_InitEmitter0A(EffectSplEmitter *o) {
    EffectCb_PlaceRotatedOffset(o, &data_020d0234, 0);
}

extern "C" s32 Effect_CreateKind2C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    if (Effect_StartOnSandOrSnow(a, b, c, d, 0x57, data_020e1488) == 1) {
        return Effect_StartOnSandOrSnow(a, b, c, d, 0x57, data_020e14b0);
    }
    return 3;
}

extern "C" void EffectKind2D_InitEmitter0(EffectSplEmitter *a) {
    EffectCb_InitOneShotOffset(a, 0, &data_020d0270);
}

extern "C" s32 Effect_CreateKind2D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    s32 r = 3;
    gEffectManager.scratchSlot.set(-1, a, b, c, d, -1);
    if (EffectSpl_CreateOneShot(0x76, b, c, data_020e14c0) && EffectSpl_CreateOneShot(0x54, b, c, sEffectDefaultOneShotCbs)) {
        r = 1;
    }
    return r;
}

extern "C" void EffectKind2E_InitEmitter0(EffectSplEmitter *a) {
    EffectCb_InitOneShotOffset(a, &data_020d0288, 0);
}

extern "C" void EffectKind2E_InitEmitter1(EffectSplEmitter *a) {
    EffectCb_InitOneShotOffset(a, &data_020d0294, 0);
}

extern "C" void EffectKind2E_InitEmitter2(EffectSplEmitter *a) {
    EffectCb_InitOneShotOffset(a, &data_020d02ac, 0);
}

extern "C" s32 EffectKind2E_Start(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 e) {
    gEffectManager.scratchSlot.set(-1, a, b, c, d, -1);
    if (EffectSpl_CreateOneShot(e, b, c, data_020e14c0) != 0) {
        for (s32 i = 0; i < 3; i++) {
            if (EffectSpl_CreateOneShot(0x54, b, c, data_020e15fc + i) == 0) {
                return 3;
            }
        }
        return 1;
    }
    return 3;
}

extern "C" s32 Effect_CreateKind2E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return EffectKind2E_Start(a, b, c, d, 0x77);
}

extern "C" s32 Effect_CreateKind2F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return EffectKind2E_Start(a, b, c, d, 0x78);
}

extern "C" s32 Effect_CreateKind30(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x79, a, b, c, d, data_020e159c);
}

extern "C" void EffectKind31_InitEmitter0(EffectEmitterEntry *a) {
    EffectCb_InitTrackedOffset(a, 0, &data_020d02c4);
}

extern "C" s32 EffectKind31_UpdateEmitter0(EffectEmitterEntry *a) {
    VecFx32 v;
    v.x = 0;
    v.y = 0;
    v.z = 0x1000;
    return EffectCb_FollowTrackedOffset(a, 0, &v);
}

extern "C" s32 Effect_CreateKind31(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x7a, a, b, c, d, data_020e14f4);
}

extern "C" void EffectKind32_InitEmitter0(EffectSplEmitter *p) {
    Rgb555 col[4];
    EffectCb_InitOneShot(p);
    *(u16 *)&col[0] = Sky_GetLightColor(3);
    col[3] = col[0];
    col[1] = col[3];
    *(u16 *)&col[2] = 0x7fff;
    col[1].r = _s32_div_f(col[2].r * col[1].r, 31);
    col[1].g = _s32_div_f(col[2].g * col[1].g, 31);
    col[1].b = _s32_div_f(col[2].b * col[1].b, 31);
    p->color = *(u16 *)&col[1];
}

extern "C" s32 Effect_CreateKind32(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x63, a, b, c, d, data_020e149c);
}

extern "C" void EffectKind33_InitEmitter0(EffectEmitterEntry *a) {
    EffectCb_InitTrackedOffset(a, 0, &data_020d02dc);
}

extern "C" s32 EffectKind33_UpdateEmitter0(EffectEmitterEntry *a) {
    return EffectCb_FollowTrackedOffset(a, 0, &data_020d02dc);
}

extern "C" s32 Effect_CreateKind33(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    if (Weather_GetFallingPrecip() == 1) {
        return Effect_StartTracked(0x74, a, b, c, d, data_020e15cc);
    }
    return 3;
}

extern "C" s32 Effect_CreateKind34(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x52, a, b, c, d, 0);
}

extern "C" void EffectKind35_InitParams(EffectEmitterEntry *o, u8 a, s32 b, s32 c) {
    EffectCb_InitTrackedOffset(o, 0, &data_020d02c4);
    o->emitter->genInterval = a;
    o->emitter->initVelMagPos = b;
    o->emitter->initVelMagAxis = c;
}

extern "C" void EffectKind35_InitEmitter1(EffectEmitterEntry *o) {
    EffectKind35_InitParams(o, 5, 0xcd, 0x200);
}

extern "C" void EffectKind35_InitEmitter3(EffectEmitterEntry *o) {
    EffectKind35_InitParams(o, 5, 0xe1, 0x266);
}

extern "C" void EffectKind35_InitEmitter4(EffectEmitterEntry *o) {
    EffectCb_InitTrackedOffset(o, 0, &data_020d02c4);
    o->emitter->baseAlpha = 0;
    o->emitter->initVelMagPos = 0x3d;
    o->emitter->initVelMagAxis = 0x466;
}

extern "C" s32 EffectKind35_UpdateRamp(EffectEmitterEntry *p, s32 a, s32 b, s32 c, s32 d0, s16 e1, s16 e2, s16 e3, s32 d4, s16 e5, s16 e6, s16 e7)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    VecFx32 v2;
    BOOL ok;
    v2.x = data_020d02c4.x;
    v2.y = data_020d02c4.y;
    v2.z = data_020d02c4.z;
    ok = FALSE;
    if (r->handle != -1 && r->life != 0) {
        volatile VecFx32 v;
        s32 t0 = r->x;
        v.x = t0;
        v.y = r->y;
        v.z = r->z;
        s32 t = ((volatile EffectSlot *)r)->life;
        EffectSplEmitter *o = p->emitter;
        o->posX = t0 + o->resource->p_base->pos.x;
        o->posY = v.y + o->resource->p_base->pos.y;
        o->posZ = v.z + o->resource->p_base->pos.z;
        Vec_RotateY(&v2, r->angle);
        s32 vy = v2.y;
        s32 vz = v2.z;
        o = p->emitter;
        o->axis.x = v2.x;
        o->axis.y = vy;
        o->axis.z = vz;
        if (t > 0) {
            r->life = r->life - 1;
            p->emitter->genInterval = 5;
            p->emitter->initVelMagPos = d0;
            p->emitter->initVelMagAxis = d4;
        } else if (t < -1) {
            u16 x8;
            s16 b16, c16;
            r->life = r->life + 1;
            s32 q = r->life;
            if (q <= -0xa1) {
                s32 w;
                x8 = a + 1 + ((b * (-0xa1 - q)) >> 12);
                w = q + 0xb4;
                b16 = d0 + (s16)(e2 * w);
                c16 = d4 + (s16)(e6 * w);
            } else if (q <= -0x3d) {
                x8 = a;
                b16 = e1;
                c16 = e5;
            } else {
                x8 = a + 1 + ((c * (q + 0x3c)) >> 12);
                q = -q;
                b16 = d0 + (s16)(e3 * q);
                c16 = d4 + (s16)(e7 * q);
            }
            p->emitter->genInterval = x8;
            p->emitter->initVelMagPos = b16;
            p->emitter->initVelMagAxis = c16;
        } else {
            p->emitter->genInterval = 5;
            p->emitter->initVelMagPos = d0;
            p->emitter->initVelMagAxis = d4;
        }
        ok = TRUE;
    }
    if (!ok) {
        r->clear();
    }
    return ok;
}

extern "C" s32 EffectKind35_UpdateEmitter1(EffectEmitterEntry *p)
{
    return EffectKind35_UpdateRamp(p, 2, 0x266, 0xcd, 0xcd, 0x19a, 0xa, 3, 0x200, 0x400, 0x1a, 9);}

extern "C" s32 EffectKind35_UpdateEmitter3(EffectEmitterEntry *p)
{
    return EffectKind35_UpdateRamp(p, 1, 0x333, 0x111, 0xe1, 0x1c3, 0xb, 4, 0x266, 0x4cd, 0x1f, 0xa);}

extern "C" s32 EffectKind35_UpdateEmitter4(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    BOOL ok = FALSE;
    if (r->handle != -1 && r->life != 0) {
        volatile VecFx32 v;
        VecFx32 v2;
        s32 t0 = r->x;
        v.x = t0;
        v.y = r->y;
        v.z = r->z;
        s32 t = ((volatile EffectSlot *)r)->life;
        v2.x = data_020d02c4.x;
        v2.y = data_020d02c4.y;
        v2.z = data_020d02c4.z;
        EffectSplEmitter *o = p->emitter;
        o->posX = t0 + o->resource->p_base->pos.x;
        o->posY = v.y + o->resource->p_base->pos.y;
        o->posZ = v.z + o->resource->p_base->pos.z;
        Vec_RotateY(&v2, r->angle);
        s32 vy = v2.y;
        s32 vz = v2.z;
        o = p->emitter;
        o->axis.x = v2.x;
        o->axis.y = vy;
        o->axis.z = vz;
        if (t > 0) {
            r->life = r->life - 1;
            p->emitter->baseScale = 0;
            p->emitter->initVelMagPos = 0x3d;
            p->emitter->initVelMagAxis = 0x466;
        } else if (t < -1) {
            u8 a8;
            s16 b16, c16;
            r->life = r->life + 1;
            s32 q = r->life;
            if (q <= -0xa1) {
                s32 w = q + 0xb4;
                a8 = (w * 0xc00) >> 12;
                b16 = (s16)(w * 3) + 0x3d;
                c16 = (s16)(w * 0x38) + 0x466;
            } else if (q <= -0x3d) {
                a8 = 0xf;
                b16 = 0x7b;
                c16 = 0x8cd;
            } else {
                q = -q;
                a8 = (q * 0x400) >> 12;
                b16 = (s16)q + 0x3d;
                c16 = (s16)(q * 0x13) + 0x466;
            }
            p->emitter->baseAlpha = a8;
            p->emitter->initVelMagPos = b16;
            p->emitter->initVelMagAxis = c16;
        } else {
            p->emitter->baseAlpha = 0;
            p->emitter->initVelMagPos = 0x3d;
            p->emitter->initVelMagAxis = 0x466;
        }
        ok = TRUE;
    }
    if (!ok) {
        r->clear();
    }
    return ok;
}

extern "C" s32 Effect_CreateKind35(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    EffectSlot *e = &gEffectManager.scratchSlot;
    s32 r = 3;
    e->set(gEffectManager.nextHandle, a, b, c, d, -0xb5);
    if (EffectSpl_CreateTracked(0x7e, b, c, data_020e1734) != 0) {
        r = 0;
    }
    e->clear();
    return r;
}

extern "C" void EffectKind36_InitEmitter2(EffectEmitterEntry *p)
{
    EffectCb_InitTracked(p);
    p->emitter->genInterval = 1;
}

extern "C" s32 EffectKind36_UpdateEmitter2(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    BOOL ok = FALSE;
    if (r->handle != -1 && r->life != 0) {
        volatile VecFx32 v;
        s32 t0 = r->x;
        v.x = t0;
        v.y = r->y;
        v.z = r->z;
        s32 t = ((volatile EffectSlot *)r)->life;
        EffectSplEmitter *o = p->emitter;
        o->posX = t0 + o->resource->p_base->pos.x;
        o->posY = v.y + o->resource->p_base->pos.y;
        o->posZ = v.z + o->resource->p_base->pos.z;
        if (t > 0) {
            r->life = r->life - 1;
            p->emitter->genInterval = 5;
        } else if (t < -1) {
            u16 val;
            r->life = r->life + 1;
            s32 q = r->life;
            if (q <= -0x29) {
                val = 1;
            } else {
                val = ((q + 0x28) * 0x19a >> 12) + 1;
            }
            p->emitter->genInterval = val;
        } else {
            p->emitter->genInterval = 5;
        }
        ok = TRUE;
    }
    if (!ok) {
        r->clear();
    }
    return ok;
}

extern "C" s32 Effect_CreateKind36(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    EffectSlot *e = &gEffectManager.scratchSlot;
    s32 r = 3;
    e->set(gEffectManager.nextHandle, a, b, c, d, -0xb5);
    if (EffectSpl_CreateTracked(0x7f, b, c, data_020e1784) != 0) {
        r = 0;
    }
    e->clear();
    return r;
}

extern "C" void EffectCb_AlignFirstParticle2(EffectSplEmitter *o, s32 k)
{
    if (k == 1) {
        P *n = o->particles;
        if (n != NULL) {
            n->rot0 = Math_Atan2(o->axis.x, o->axis.z);
            o->callback = NULL;
        }
    }
}

extern "C" void EffectKind37_InitEmitter0(EffectSplEmitter *p)
{
    EffectSlot *const e = &gEffectManager.scratchSlot;
    u32 ang = (u16)e->angle;
    p->posX = e->x + p->resource->p_base->pos.x;
    p->posY = e->y + p->resource->p_base->pos.y;
    p->posZ = e->z + p->resource->p_base->pos.z;
    s32 idx = ((s32)ang >> 4) * 2;
    p->axis.x = data_02135f44[idx];
    p->axis.y = 0;
    p->axis.z = data_02135f44[idx + 1];
    EffectSpl_ApplySceneTint(p);
    p->callback = EffectCb_AlignFirstParticle2;
}

extern "C" s32 Effect_CreateKind37(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 k;
    s32 id;
    s32 r;
    o.initAtPos(b, 0, 0);
    k = o.attr;
    id = -1;
    if (GroundSeason_IsSnow() != 0 && k == 3) {
        id = 0x88;
    } else if (k == 0x13) {
        id = 0x87;
    }
    if (id != -1) {
        r = Effect_StartOneShot(id, a, b, c, d, data_020e14a0);
        return r;
    }
    return 3;
}

extern "C" s32 Effect_CreateKind38(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 k;
    s32 id;
    s32 r;
    o.initAtPos(b, 0, 0);
    k = o.attr;
    id = -1;
    if (GroundSeason_IsSnow() != 0 && k == 3) {
        id = 0x8a;
    } else if (k == 0x13) {
        id = 0x89;
    }
    if (id != -1) {
        r = Effect_StartOneShot(id, a, b, c, d, data_020e14a0);
        return r;
    }
    return 3;
}

extern "C" void EffectKind39_InitEmitter0(EffectEmitterEntry *p)
{
    EffectCb_InitTrackedOffset(p, NULL, &data_020d030c);
}

extern "C" s32 EffectKind39_UpdateEmitter0B(EffectEmitterEntry *p)
{
    return ((EffectEmitterEntry *)(p))->updateLanding(0x1f, data_020e16d4, 0x1d, data_020e16d4, 0x1d, data_020e16d4, -1, NULL);
}

extern "C" s32 EffectKind39_UpdateEmitter0A(EffectEmitterEntry *p)
{
    return ((EffectEmitterEntry *)(p))->updateLanding(0x1f, data_020e16d4, 0x1d, data_020e16d4, 0x1d, data_020e16d4, -1, NULL);
}

extern "C" s32 Effect_CreateKind39(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    GroundInfo o;
    s32 result;
    s32 k;
    o.initAtPos(b, 0, 0);
    k = o.attr;
    result = 3;
    if (k == 0x16 || Weather_GetFallingPrecip() == 1) {
        if (Effect_StartTracked(0x85, a, b, c, d, data_020e155c) == 0) {
            result = 2;
        }
    } else if (k == 3 && GroundSeason_IsSnow() != 0) {
        if (Effect_StartTracked(0x86, a, b, c, d, data_020e1554) == 0) {
            result = 2;
        }
    } else if (k == 0x13) {
        result = Effect_StartOneShot(0x84, a, b, c, d, NULL);
    } else {
        result = Effect_StartOneShot(0x83, a, b, c, d, NULL);
    }
    return result;
}

extern "C" void EffectKind3A_InitEmitter0(EffectEmitterEntry *p)
{
    EffectSlot *const e = &gEffectManager.scratchSlot;
    EffectEmitterTag i = p->tag;
    volatile VecFx32 v;
    s32 t = e->x;
    v.x = t;
    v.y = e->y;
    v.z = e->z;
    EffectSplEmitter *o = p->emitter;
    o->posX = t + o->resource->p_base->pos.x;
    o->posY = v.y + o->resource->p_base->pos.y;
    o->posZ = v.z + o->resource->p_base->pos.z;
    EffectSpl_ApplySceneTint(p->emitter);
    MI_CpuCopy8(e, &gEffectManager.slots[i.poolIndex], sizeof(EffectSlot));
}

extern "C" s32 EffectKind3A_UpdateEmitter0(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    BOOL ok = FALSE;
    if (r->handle != -1 && r->life != 0) {
        volatile VecFx32 v;
        s32 t0 = r->x;
        v.x = t0;
        v.y = r->y;
        v.z = r->z;
        EffectSplEmitter *o = p->emitter;
        o->posX = t0 + o->resource->p_base->pos.x;
        o->posY = v.y + o->resource->p_base->pos.y;
        o->posZ = v.z + o->resource->p_base->pos.z;
        if (r->life > 0) {
            r->life = r->life - 1;
        }
        p->emitter->baseScale = r->param;
        P *n;
        for (n = p->emitter->particles; n != NULL; n = n->next) {
            n->w30 = r->param;
        }
        ok = TRUE;
    }
    if (!ok) {
        P *n;
        for (n = p->emitter->particles; n != NULL; n = n->next) {
            n->age = n->life;
        }
        r->clear();
    }
    return ok;
}

extern "C" s32 Effect_CreateKind3A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartTracked(0x8d, a, b, c, d, data_020e1544);
}

extern "C" void EffectKind3B_InitEmitter0(EffectEmitterEntry *p)
{
    EffectCb_InitTrackedOffset(p, &data_020d0324, NULL);
}

extern "C" s32 EffectKind3B_UpdateEmitter0(EffectEmitterEntry *p)
{
    return EffectCb_FollowTrackedOffset(p, &data_020d0324, NULL);
}

extern "C" s32 Effect_CreateKind3B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartTracked(0x4f, a, b, c, d, data_020e156c);
}

extern "C" s32 Effect_CreateKind3C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartTracked(0x92, a, b, c, d, data_020e164c);
}

extern "C" void EffectKind3D_InitEmitter0(EffectEmitterEntry *p)
{
    EffectCb_InitTrackedOffset(p, NULL, NULL);
}

extern "C" s32 EffectKind3D_UpdateEmitter0(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    BOOL ok = FALSE;
    if (r->handle != -1 && r->life != 0) {
        EffectSplEmitter *o = p->emitter;
        o->posX = r->x + o->resource->p_base->pos.x;
        o->posY = r->y + o->resource->p_base->pos.y;
        o->posZ = r->z + o->resource->p_base->pos.z;
        if (r->life > 0) {
            p->emitter->baseAlpha = (r->life * 0x2955) >> 12;
            r->life = r->life - 1;
        }
        ok = TRUE;
    }
    if (!ok) {
        r->clear();
    }
    return ok;
}

extern "C" s32 Effect_CreateKind3D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    return Effect_StartTracked(0x53, a, b, c, d, data_020e166c);
}

extern "C" void Effect_EndKind3D(s32 id)
{
    gEffectManager.setLife(id, 0xb);
}

extern "C" void EffectKind3E_InitEmitter0B(EffectSplEmitter *o)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    s32 a, b, c;
    s32 f = g->param;
    if (f < 0xc00) {
        s32 t = FX_Div(f - 0x600, 0x600);
        a = (s16)((s16)func_01ffcb0c(0x266, t) + 0x266);
        c = (s16)((s16)func_01ffcb0c(0x400, t) + 0x400);
        b = (s16)((s16)func_01ffcb0c(0x52, t) + 0xcd);
    } else {
        s32 t = FX_Div(f - 0xc00, 0xc00);
        a = (s16)((s16)func_01ffcb0c(0x800, t) + 0x4cd);
        c = (s16)((s16)func_01ffcb0c(0x4cd, t) + 0x800);
        b = (s16)((s16)func_01ffcb0c(0x52, t) + 0x11f);
    }
    o->radius = a;
    o->initVelMagPos = b;
    o->baseScale = c;
    o->posX = g->x + o->resource->p_base->pos.x;
    o->posY = g->y + o->resource->p_base->pos.y;
    o->posZ = g->z + o->resource->p_base->pos.z;
    EffectSpl_ApplySceneTint(o);
}

extern "C" void EffectKind3E_InitEmitter0A(EffectSplEmitter *o)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    s32 f = g->param;
    VecFx32CtorDtor v;
    v.x = g->x;
    v.y = g->y;
    v.z = g->z;
    s32 t = FX_Div(f - 0xc00, 0xc00);
    s32 a = (s16)((s16)func_01ffcb0c(0x4cd, t) + 0xb33);
    s32 c = (s16)((s16)func_01ffcb0c(0x19a, t) + 0x400);
    s32 b = (s16)((s16)func_01ffcb0c(0x19a, t) + 0x333);
    o->radius = a;
    o->initVelMagPos = b;
    o->baseScale = c;
    o->posX = v.x + o->resource->p_base->pos.x;
    o->posY = v.y + o->resource->p_base->pos.y;
    o->posZ = v.z + o->resource->p_base->pos.z;
    o->simpleCollisionY = 0x99a;
    EffectSpl_ApplySceneTint(o);
}

extern "C" s32 Effect_CreateKind3E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    s32 r = 3;
    if (d != 0) {
        Effect_StartOneShot(0x6c, a, b, c, d, data_020e148c);
        if (*d >= 0xc00) {
            Effect_StartOneShot(0x6d, a, b, c, d, data_020e1498);
        }
        r = 1;
    }
    return r;
}

extern "C" void EffectKind3F_InitEmitter0B(EffectEmitterEntry *o)
{
    s32 f = gEffectManager.scratchSlot.param;
    s32 a = (s16)((s16)func_01ffcb0c(0x1333, f) + 0x4cd);
    s32 b = (s16)((s16)func_01ffcb0c(0x3ae, f) + 0x800);
    EffectCb_InitTracked(o);
    o->emitter->radius = a;
    o->emitter->initVelMagAxis = b;
}

extern "C" void EffectKind3F_InitEmitter0A(EffectSplEmitter *p)
{
    s32 u = (s16)((s16)func_01ffcb0c(0x1e66, gEffectManager.scratchSlot.param) + 0xb33);
    EffectCb_InitOneShotSetUnk54(p, u);
}

extern "C" void EffectKind3F_InitModel(EffectModel *m)
{
    s32 t = func_01ffcb0c(0x2000, gEffectManager.scratchSlot.param) + 0x99a;
    EffectModel_Obj(m)->initAtSlot(t);
}

extern "C" s32 EffectKind3F_UpdateEmitter0(EffectEmitterEntry *p)
{
    return ((EffectEmitterEntry *)(p))->updateLanding(0x1f, data_020e16d4, 0x1e, data_020e16d4, 0x1e, data_020e16d4, -1, NULL);
}

extern "C" s32 Effect_CreateKind3F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32)
{
    if (d != 0) {
        s16 t = FX_Div(*d - 0x600, 0x1200);
        return Effect_StartWaterColumn(a, b, c, &t, data_020e15d4, data_020e14a8, EffectKind3F_InitModel);
    }
    return 3;
}

extern "C" void EffectKind40_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, &data_020d021c, 0); }

extern "C" s32 EffectKind40_UpdateEmitter0(EffectEmitterEntry *p) { return EffectCb_FollowTrackedOffset(p, &data_020d021c, 0); }

extern "C" s32 Effect_CreateKind40(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x95, a, b, c, d, data_020e14cc); }

extern "C" void EffectKind41_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, &data_020d0240, 0); }

extern "C" void EffectKind41_InitEmitter1(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, &data_020d0258, 0); }

extern "C" void EffectKind41_InitEmitter2(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, &data_020d02a0, 0); }

extern "C" s32 EffectKind41_UpdateEmitter0(EffectEmitterEntry *p) { return EffectCb_FollowTrackedOffset(p, &data_020d0240, 0); }

extern "C" s32 EffectKind41_UpdateEmitter1(EffectEmitterEntry *p) { return EffectCb_FollowTrackedOffset(p, &data_020d0258, 0); }

extern "C" s32 EffectKind41_UpdateEmitter2(EffectEmitterEntry *p) { return EffectCb_FollowTrackedOffset(p, &data_020d02a0, 0); }

extern "C" s32 Effect_CreateKind41(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x96, a, b, c, d, data_020e168c); }

extern "C" s32 Effect_CreateKind42(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x97, a, b, c, d, data_020e168c); }

extern "C" s32 Effect_CreateKind43(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind44(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x1, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind45(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0x3, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind46(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0x4, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind47(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0x5, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind48(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x6, a, b, c, d, data_020e17fc); }

extern "C" void EffectKind49_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, &data_020d02e8, 0); }

extern "C" s32 EffectKind49_UpdateEmitter0(EffectEmitterEntry *p) { return EffectCb_FollowTrackedOffset(p, &data_020d02e8, 0); }

extern "C" s32 Effect_CreateKind49(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x7, a, b, c, d, data_020e1514); }

extern "C" void EffectKind4A_InitEmitter0(EffectEmitterEntry *p) { EffectCb_InitTrackedOffset(p, &data_020d02c4, 0); }

extern "C" s32 EffectKind4A_UpdateEmitter0(EffectEmitterEntry *p) { return EffectCb_FollowTrackedOffset(p, &data_020d02c4, 0); }

extern "C" s32 Effect_CreateKind4A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x5b, a, b, c, d, data_020e158c); }

extern "C" s32 Effect_CreateKind4B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x5c, a, b, c, d, data_020e158c); }

extern "C" s32 Effect_CreateKind4C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x8, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind4D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x16, a, b, c, d, 0); }

extern "C" void EffectKind4E_InitEmitter0(EffectEmitterEntry *p)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    EffectEmitterTag i = p->tag;
    EffectCb_InitTrackedOffset(p, &data_020e183c[g->param], 0);
    MI_CpuCopy8(g, &gEffectManager.slots[i.poolIndex], sizeof(EffectSlot));
}

extern "C" void EffectKind4E_InitEmitter1(EffectEmitterEntry *p)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    EffectEmitterTag i = p->tag;
    EffectCb_InitTrackedOffset(p, &data_020e18a8[g->param], 0);
    MI_CpuCopy8(g, &gEffectManager.slots[i.poolIndex], sizeof(EffectSlot));
}

extern "C" s32 EffectKind4E_UpdateEmitter0(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    return EffectCb_FollowTrackedOffset(p, &data_020e183c[r->param], 0);}

extern "C" s32 EffectKind4E_UpdateEmitter1(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    return EffectCb_FollowTrackedOffset(p, &data_020e18a8[r->param], 0);}

extern "C" s32 Effect_CreateKind4E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0x9, a, b, c, d, data_020e16bc); }

extern "C" s32 Effect_CreateKind4F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0xa, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind50(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0xb, a, b, c, d, 0); }

extern "C" s32 Effect_CreateKind51(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0xc, a, b, c, d, 0); }

extern "C" void EffectKind52_InitEmitter0(EffectSplEmitter *o)
{
    VecFx32CtorDtor v;
    EffectSlot *const g = &gEffectManager.scratchSlot;
    v.x = g->x;
    v.y = g->y;
    v.z = g->z;
    v.y = 0;
    o->posX = v.x + o->resource->p_base->pos.x;
    o->posY = v.y + o->resource->p_base->pos.y;
    o->posZ = v.z + o->resource->p_base->pos.z;
    EffectSpl_ApplySceneTint(o);
}

extern "C" s32 Effect_CreateKind52(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartOneShot(0x5d, a, b, c, d, data_020e14b8); }

extern "C" s32 Effect_CreateKind53(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) { return Effect_StartTracked(0xd, a, b, c, d, data_020e167c); }

extern "C" void EffectKind54_InitEmitter0(EffectEmitterEntry *p)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    EffectEmitterTag i = p->tag;
    EffectCb_InitTrackedOffset(p, g->param != 3 ? &data_020d03b4 : &data_020d03c0, &data_020d0300);
    MI_CpuCopy8(g, &gEffectManager.slots[i.poolIndex], sizeof(EffectSlot));
}

extern "C" void EffectKind54_InitEmitter1(EffectEmitterEntry *p)
{
    EffectSlot *const g = &gEffectManager.scratchSlot;
    EffectEmitterTag i = p->tag;
    EffectCb_InitTrackedOffset(p, g->param != 3 ? &data_020d039c : &data_020d03a8, &data_020d02b8);
    MI_CpuCopy8(g, &gEffectManager.slots[i.poolIndex], sizeof(EffectSlot));
}

extern "C" s32 EffectKind54_UpdateEmitter0(EffectEmitterEntry *p)
{
    EffectEmitterTag i = p->tag;
    EffectSlot *r = &gEffectManager.slots[i.poolIndex];
    return EffectCb_FollowTrackedOffset(p, r->param != 3 ? &data_020d03b4 : &data_020d03c0, &data_020d0300);
}

s32 EffectEmitterEntry::updateKind54B() {
    EffectEmitterTag bytes = tag;
    EffectSlot *e = &gEffectManager.slots[bytes.poolIndex];
    return EffectCb_FollowTrackedOffset(this, e->param != 3 ? &data_020d039c : &data_020d03a8, &data_020d02b8);
}

extern "C" s32 Effect_CreateKind54(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0xe, a, b, c, d, data_020e162c);
}

extern "C" s32 Effect_CreateKind55(s32 p0, VecFx32 *p1, s16 *p2, s16 *p3, s32) {
    EffectSlot *e = &gEffectManager.scratchSlot;
    s32 r = 3;
    e->set(gEffectManager.nextHandle, p0, p1, p2, p3, 0xf);
    if (EffectSpl_CreateTracked(0xf, p1, p2, sEffectDefaultTrackedCbs)) {
        r = 2;
    }
    e->clear();
    return r;
}

BOOL EffectEmitterEntry::updateKind56Main() {
    EffectEmitterTag bytes = tag;
    EffectSlot *e = &gEffectManager.slots[bytes.poolIndex];
    BOOL r = FALSE;
    if (e->handle != -1) {
        if (e->life == -1) {
            EffectSplEmitter *b = emitter;
            b->posX = e->x + b->resource->p_base->pos.x;
            b->posY = e->y + b->resource->p_base->pos.y;
            b->posZ = e->z + b->resource->p_base->pos.z;
            r = TRUE;
        }
    }
    if (!r) {
        P *n = emitter->particles;
        for (; n; n = n->next) {
            n->age = n->life;
        }
        e->clear();
    }
    return r;
}

BOOL EffectEmitterEntry::updateKind56Fade() {
    EffectEmitterTag bytes = tag;
    EffectSlot *e = &gEffectManager.slots[bytes.poolIndex];
    BOOL r = FALSE;
    if (e->handle != -1) {
        if (e->life != 0) {
            EffectSplEmitter *b = emitter;
            b->posX = e->x + b->resource->p_base->pos.x;
            b->posY = e->y + b->resource->p_base->pos.y;
            b->posZ = e->z + b->resource->p_base->pos.z;
            if (e->life > 0) {
                emitter->baseAlpha = e->life * 6;
                e->life = e->life - 1;
            }
            r = TRUE;
        }
    }
    if (!r) {
        e->clear();
    }
    return r;
}

extern "C" s32 Effect_CreateKind56(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x10, a, b, c, d, data_020e1714);
}

extern "C" void Effect_EndKind56(s32 id) {
    gEffectManager.setLife(id, 4);
}

extern "C" s32 Effect_CreateKind57(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x11, a, b, c, d, NULL);
}

extern "C" s32 Effect_CreateKind58(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x12, a, b, c, d, NULL);
}

BOOL EffectEmitterEntry::updateKind59() {
    EffectEmitterTag bytes = tag;
    EffectSlot *e = &gEffectManager.slots[bytes.poolIndex];
    BOOL r = FALSE;
    if (e->handle != -1) {
        if (e->life != 0) {
            P *n = emitter->particles;
            u32 t = 0x30d4;
            if (e->angle < 0) {
                t = 0xffffcf2c;
            }
            u16 v = t;
            for (; n; n = n->next) {
                n->rot0 = v;
            }
            if (e->life > 0) {
                e->life--;
            }
            r = TRUE;
        }
    }
    if (!r) {
        e->clear();
    }
    return r;
}

extern "C" s32 Effect_CreateKind59(s32 p0, VecFx32 *p1, s16 *p2, s16 *p3, s32) {
    s32 r = 3;
    Effect_StartOneShot(0x13, p0, p1, p2, p3, NULL);
    EffectSlot *e = &gEffectManager.scratchSlot;
    e->set(gEffectManager.nextHandle, p0, p1, p2, p3, 0x25);
    if (EffectSpl_CreateTracked(0x62, p1, p2, data_020e163c)) {
        r = 2;
    }
    e->clear();
    return r;
}

extern "C" void EffectKind5A_InitEmitter0(EffectSplEmitter *x) {
    EffectCb_InitOneShotOffset(x, &data_020d0330, &data_020d02c4);
}

extern "C" s32 Effect_CreateKind5A(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x14, a, b, c, d, data_020e14c8);
}

extern "C" s32 Effect_CreateKind5B(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x82, a, b, c, d, data_020e14c8);
}

extern "C" s32 Effect_CreateKind5C(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x15, a, b, c, d, NULL);
}

extern "C" s32 Effect_CreateKind5D(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartModel(0, a, b, c, d, NULL);
}

extern "C" s32 Effect_CreateKind5E(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartModel(1, a, b, c, d, NULL);
}

extern "C" void EffectKind5F_InitEmitter0(EffectSplEmitter *x) {
    EffectCb_InitOneShotOffset(x, &data_020d0264, &data_020d02d0);
}

extern "C" s32 Effect_CreateKind5F(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x51, a, b, c, d, data_020e1564);
}

extern "C" void EffectKind60_InitEmitter0(EffectSplEmitter *x) {
    EffectCb_InitOneShotOffset(x, &data_020d0384, &data_020d024c);
}

extern "C" s32 Effect_CreateKind60(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x7b, a, b, c, d, data_020e1490);
}

extern "C" s32 Effect_CreateKind61(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartTracked(0x7c, a, b, c, d, NULL);
}

extern "C" s32 Effect_CreateKind62(s32 a, VecFx32 *b, s16 *c, s16 *d, s32) {
    return Effect_StartOneShot(0x7d, a, b, c, d, NULL);
}

extern "C" s32 Effect_CreateNone(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 id) {
    return 3;
}

extern "C" s32 Effect_CreateOneShotRes(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 id) {
    return Effect_StartOneShot(id, a, b, c, d, NULL);
}

extern "C" s32 Effect_CreateTrackedRes(s32 a, VecFx32 *b, s16 *c, s16 *d, s32 id) {
    return Effect_StartTracked(id, a, b, c, d, NULL);
}

void EffectSlot::clear() {
    MI_CpuFill8(this, 0, 0x14);
    life = -1;
    param = 0x1000;
    handle = -1;
    kind = 0x66;
}

void EffectSlot::set(s32 id, u32 type, VecFx32 *pos, s16 *a, s16 *b, s16 v) {
    clear();
    handle = id;
    kind = type;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    if (a) {
        angle = *a;
    }
    if (b) {
        param = *b;
    }
    life = v;
}

void EffectManager::clearSlots() {
    scratchSlot.clear();
    for (s32 i = 0; i < 0x20; i++) {
        slots[i].clear();
    }
}

EffectSlot *EffectManager::findSlot(s32 id, EffectSlot *e, s32 n) {
    EffectSlot *r = NULL;
    s32 i = 0;
    for (; i < n; e++, i++) {
        if (id == e->handle) {
            r = e;
            break;
        }
    }
    return r;
}

void EffectManager::setPosition(s32 id, VecFx32 *pos, s16 *a, s16 *b) {
    s32 i = 0;
    if (id != -1) {
        for (i = 0; i < 0x20; i++) {
            EffectSlot *e = &slots[i];
            if (id == e->handle) {
                e->x = pos->x;
                e->y = pos->y;
                e->z = pos->z;
                if (a) {
                    e->angle = *a;
                }
                if (b) {
                    e->param = *b;
                }
            }
        }
    }
}

void EffectManager::setLife(s32 id, s16 v) {
    s32 i = 0;
    if (id != -1) {
        for (i = 0; i < 0x20; i++) {
            if (slots[i].handle == id) {
                slots[i].life = v;
            }
        }
    }
}

void EffectManager::reset() {
    clearSlots();
    nextHandle = 0;
}

s32 EffectManager::create(u32 kind, VecFx32 *a, s16 *b, s16 *c, s32 d) {
    s32 r = -1;
    if (kind < 0x66) {
        EffectKindEntry *ent = &sEffectKindTable[kind];
        if (ent->fn) {
            s32 ret = ent->fn(kind, a, b, c, d);
            if (ret == 0) {
                r = nextHandle;
                nextHandle = r + 1;
            } else if (ret == 2) {
                nextHandle = nextHandle + 1;
            }
        }
    }
    return r;
}

void EffectManager::end(s32 id) {
    if (id != -1) {
        u32 t = getKind(id);
        if (t < 0x66) {
            void (*f)(s32) = sEffectKindTable[t].end;
            if (f) {
                f(id);
            }
        }
    }
}

u32 EffectManager::getKind(s32 id) {
    EffectSlot *e = findSlot(id, slots, 0x20);
    u32 r = 0x66;
    if (e) {
        r = e->kind;
    }
    return r;
}

extern "C" void Effect_ResetAll() {
    gEffectManager.reset();
}

extern "C" s32 Effect_Create(u32 kind, VecFx32 *a, s16 *b, s16 *c) {
    return gEffectManager.create(kind, a, b, c, -1);
}

extern "C" s32 Effect_CreateWithParam(u32 kind, s16 v0, VecFx32 *a, s16 *b) {
    s16 v = v0;
    return gEffectManager.create(kind, a, b, &v, -1);
}

extern "C" void Effect_End(s32 id) {
    gEffectManager.end(id);
}

extern "C" void Effect_SetPosition(s32 id, VecFx32 *pos, s16 *a, s16 *b) {
    gEffectManager.setPosition(id, pos, a, b);
}

extern "C" s32 Effect_PlayById(s32 a, VecFx32 *b, s16 *c, s16 *d) {
    return gEffectManager.create(0x64, b, c, d, a);
}

extern "C" s32 Effect_PlayById2(s32 a, VecFx32 *b, s16 *c, s16 *d) {
    return gEffectManager.create(0x64, b, c, d, a);
}

extern "C" s32 Effect_CreateById(s32 a, VecFx32 *b, s16 *c, s16 *d) {
    return gEffectManager.create(0x65, b, c, d, a);
}


static s32 EffectEmitterEntry_UpdateKind59(EffectEmitterEntry *o) { return o->updateKind59(); }
static s32 EffectEmitterEntry_UpdateKind56Fade(EffectEmitterEntry *o) { return o->updateKind56Fade(); }
static s32 EffectEmitterEntry_UpdateKind56Main(EffectEmitterEntry *o) { return o->updateKind56Main(); }
static s32 EffectEmitterEntry_UpdateKind54B(EffectEmitterEntry *o) { return o->updateKind54B(); }
static s32 EffectEmitterEntry_UpdateLanding5F(EffectEmitterEntry *o) { return o->updateLanding5F(); }
static s32 EffectEmitterEntry_UpdateLanding1F1E(EffectEmitterEntry *o) { return o->updateLanding1F1E(); }
static s32 EffectEmitterEntry_UpdateLanding1F1EB(EffectEmitterEntry *o) { return o->updateLanding1F1EB(); }
static s32 EffectEmitterEntry_UpdateLanding1F1D(EffectEmitterEntry *o) { return o->updateLanding1F1D(); }
static void EffectEmitterEntry_InitAxisUpForward(EffectEmitterEntry *o) { o->initAxisUpForward(); }
static void EffectSplEmitter_InitKind02(EffectSplEmitter *o) { o->initKind02(); }


EffectOneShotCb data_020e14a4[1] = {EffectKind2B_InitEmitter0B};
EffectOneShotCb data_020e147c[1] = {EffectKind16_InitEmitter0A};
EffectOneShotCb data_020e1490[1] = {EffectKind60_InitEmitter0};
EffectOneShotCb data_020e14a0[1] = {EffectKind37_InitEmitter0};
EffectOneShotCb data_020e148c[1] = {EffectKind3E_InitEmitter0B};
EffectOneShotCb data_020e1494[1] = {EffectKind19_InitEmitter0A};
EffectOneShotCb data_020e1484[1] = {EffectKind29_InitEmitter0};
EffectOneShotCb data_020e14bc[1] = {EffectKind17_InitEmitter0A};
EffectOneShotCb data_020e1474[1] = {EffectSplEmitter_InitKind02};
EffectOneShotCb data_020e149c[1] = {EffectKind32_InitEmitter0};
EffectOneShotCb data_020e14b4[1] = {EffectCb_InitOneShotFacing};
EffectOneShotCb data_020e14ac[1] = {EffectKind2A_InitEmitter0};
EffectOneShotCb data_020e14b0[1] = {EffectKind2C_InitEmitter0A};
EffectOneShotCb data_020e14c4[1] = {EffectKind23_InitEmitter0};
EffectOneShotCb data_020e14c8[1] = {EffectKind5A_InitEmitter0};
EffectOneShotCb data_020e14a8[1] = {EffectKind3F_InitEmitter0A};
EffectOneShotCb data_020e1478[1] = {EffectKind2B_InitEmitter0A};
EffectOneShotCb data_020e14c0[1] = {EffectKind2D_InitEmitter0};
EffectOneShotCb data_020e14b8[1] = {EffectKind52_InitEmitter0};
EffectOneShotCb data_020e1480[1] = {EffectCb_InitOneShotFacingBack};
EffectOneShotCb data_020e1498[1] = {EffectKind3E_InitEmitter0A};
EffectOneShotCb data_020e1488[1] = {EffectKind2C_InitEmitter0B};
EffectEmitterCbs data_020e15b4[1] = {{EffectKind14_InitEmitter0A, EffectKind13_UpdateEmitter0}};
EffectEmitterCbs data_020e14f4[1] = {{EffectKind31_InitEmitter0, EffectKind31_UpdateEmitter0}};
EffectEmitterCbs data_020e14fc[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding5F}};
EffectOneShotCb data_020e150c[2] = {EffectCb_InitOneShotFacingBack, EffectCb_InitOneShotFacingBack};
EffectEmitterCbs data_020e15f4[1] = {{EffectKind19_InitEmitter0B, EffectEmitterEntry_UpdateLanding1F1E}};
EffectOneShotCb data_020e1564[2] = {EffectKind5F_InitEmitter0, EffectKind5F_InitEmitter0};
EffectEmitterCbs data_020e152c[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding1F1E}};
EffectEmitterCbs data_020e1544[1] = {{EffectKind3A_InitEmitter0, EffectKind3A_UpdateEmitter0}};
EffectEmitterCbs data_020e1574[1] = {{EffectKind16_InitEmitter0B, EffectEmitterEntry_UpdateLanding1F1E}};
EffectEmitterCbs data_020e151c[1] = {{EffectKind14_InitEmitter0A, EffectKind13_UpdateEmitter0}};
EffectEmitterCbs data_020e157c[1] = {{EffectCb_InitTracked, EffectKind13_UpdateEmitter0}};
EffectEmitterCbs data_020e156c[1] = {{EffectKind3B_InitEmitter0, EffectKind3B_UpdateEmitter0}};
EffectEmitterCbs data_020e1514[1] = {{EffectKind49_InitEmitter0, EffectKind49_UpdateEmitter0}};
EffectEmitterCbs data_020e1524[1] = {{EffectKind17_InitEmitter0B, EffectEmitterEntry_UpdateLanding1F1E}};
EffectEmitterCbs data_020e154c[1] = {{EffectKind1D_InitEmitter0, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e155c[1] = {{EffectKind39_InitEmitter0, EffectKind39_UpdateEmitter0B}};
EffectEmitterCbs data_020e14ec[1] = {{EffectEmitterEntry_InitAxisUpForward, EffectEmitterEntry_UpdateLanding1F1D}};
EffectEmitterCbs data_020e1554[1] = {{EffectKind39_InitEmitter0, EffectKind39_UpdateEmitter0A}};
EffectEmitterCbs data_020e1534[1] = {{EffectKind1A_InitEmitter0, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e153c[1] = {{EffectKind1B_InitEmitter0, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e14e4[1] = {{EffectKind1E_InitEmitter0, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e1584[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding5F}};
EffectEmitterCbs data_020e158c[1] = {{EffectKind4A_InitEmitter0, EffectKind4A_UpdateEmitter0}};
EffectEmitterCbs data_020e1594[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding1F1EB}};
EffectEmitterCbs data_020e14dc[1] = {{EffectKind1F_InitEmitter0, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e159c[1] = {{EffectCb_InitTracked, EffectCb_CountdownTracked}};
EffectOneShotCb data_020e15a4[2] = {EffectKind13_InitEmitter0, EffectKind13_InitEmitter1};
EffectEmitterCbs data_020e15ac[1] = {{EffectKind1C_InitEmitter0, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e14d4[1] = {{EffectEmitterEntry_InitAxisUpForward, EffectEmitterEntry_UpdateLanding1F1EB}};
EffectEmitterCbs data_020e15bc[1] = {{EffectKind26_InitEmitter0, EffectKind26_UpdateEmitter0}};
EffectOneShotCb data_020e15c4[2] = {EffectKind07_InitEmitter0, EffectKind07_InitEmitter1};
EffectEmitterCbs data_020e15cc[1] = {{EffectKind33_InitEmitter0, EffectKind33_UpdateEmitter0}};
EffectEmitterCbs data_020e15d4[1] = {{EffectKind3F_InitEmitter0B, EffectKind3F_UpdateEmitter0}};
EffectEmitterCbs data_020e15dc[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding5F}};
EffectEmitterCbs data_020e15e4[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding1F1D}};
EffectEmitterCbs data_020e15ec[1] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateLanding5F}};
EffectEmitterCbs data_020e1504[1] = {{EffectKind0E_InitEmitter0, EffectKind0E_UpdateEmitter0}};
EffectEmitterCbs data_020e14cc[1] = {{EffectKind40_InitEmitter0, EffectKind40_UpdateEmitter0}};
extern const VecFx32 data_020d0228;
const VecFx32 data_020d0228 = {-512, 0, -246};
extern const VecFx32 data_020d0234;
const VecFx32 data_020d0234 = {737, 0, 2048};
extern const VecFx32 data_020d024c;
const VecFx32 data_020d024c = {0, -2048, 4096};
extern const VecFx32 data_020d0258;
const VecFx32 data_020d0258 = {6963, 0, 6963};
extern const VecFx32 data_020d0270;
const VecFx32 data_020d0270 = {1024, 4096, 0};
extern const VecFx32 data_020d027c;
const VecFx32 data_020d027c = {2744, 0, 0};
extern const VecFx32 data_020d0294;
const VecFx32 data_020d0294 = {-1843, 0, -2253};
extern const VecFx32 data_020d02a0;
const VecFx32 data_020d02a0 = {6963, 0, -6963};
extern const VecFx32 data_020d02b8;
const VecFx32 data_020d02b8 = {-4096, 4096, 0};
extern const VecFx32 data_020d02c4;
const VecFx32 data_020d02c4 = {0, 0, 4096};
extern const VecFx32 data_020d02dc;
const VecFx32 data_020d02dc = {0, 4096, -4096};
extern const VecFx32 data_020d02e8;
const VecFx32 data_020d02e8 = {0, 0, 3277};
extern const VecFx32 data_020d0300;
const VecFx32 data_020d0300 = {4096, 4096, 0};
extern const VecFx32 data_020d030c;
const VecFx32 data_020d030c = {0, 4096, 4096};
extern const VecFx32 data_020d0324;
const VecFx32 data_020d0324 = {0, 0, 3277};
extern const VecFx32 data_020d0330;
const VecFx32 data_020d0330 = {0, 3277, 3277};
extern const VecFx32 data_020d0348;
const VecFx32 data_020d0348 = {0, 3482, 2130};
extern const VecFx32 data_020d0354;
const VecFx32 data_020d0354 = {-1516, 0, -2130};
extern const VecFx32 data_020d036c;
const VecFx32 data_020d036c = {-1024, 0, 1229};
extern const VecFx32 data_020d0378;
const VecFx32 data_020d0378 = {901, 0, 2458};
extern const VecFx32 data_020d0384;
const VecFx32 data_020d0384 = {0, 0, 819};
extern const VecFx32 data_020d0390;
const VecFx32 data_020d0390 = {-614, 4096, -614};
extern const VecFx32 data_020d039c;
const VecFx32 data_020d039c = {-1638, 0, 2048};
extern const VecFx32 data_020d03a8;
const VecFx32 data_020d03a8 = {-1638, 1925, 0};
extern const VecFx32 data_020d03b4;
const VecFx32 data_020d03b4 = {1638, 0, 2048};
extern const VecFx32 data_020d03c0;
const VecFx32 data_020d03c0 = {1638, 1925, 0};
EffectOneShotCb data_020e15fc[3] = {EffectKind2E_InitEmitter0, EffectKind2E_InitEmitter1, EffectKind2E_InitEmitter2};
EffectOneShotCb data_020e1608[3] = {EffectKind09_InitEmitter0, EffectKind09_InitEmitter0, EffectKind09_InitEmitter0};
EffectOneShotCb data_020e1614[3] = {EffectKind14_InitEmitter0B, EffectKind14_InitEmitter0B, EffectKind14_InitEmitter2};
EffectOneShotCb data_020e1620[3] = {EffectKind15_InitEmitter0, EffectKind15_InitEmitter0, EffectKind15_InitEmitter2};
extern const VecFx32 data_020d021c;
const VecFx32 data_020d021c = {0, 0, 3277};
extern const VecFx32 data_020d0240;
const VecFx32 data_020d0240 = {-5734, 0, 6963};
extern const VecFx32 data_020d0264;
const VecFx32 data_020d0264 = {0, 0, 3359};
extern const VecFx32 data_020d0288;
const VecFx32 data_020d0288 = {2130, 0, 0};
extern const VecFx32 data_020d02ac;
const VecFx32 data_020d02ac = {-1843, 0, 1516};
extern const VecFx32 data_020d02d0;
const VecFx32 data_020d02d0 = {0, -2048, 4096};
extern const VecFx32 data_020d02f4;
const VecFx32 data_020d02f4 = {-4096, 4096, 0};
extern const VecFx32 data_020d0318;
const VecFx32 data_020d0318 = {-819, 4096, -1638};
extern const VecFx32 data_020d033c;
const VecFx32 data_020d033c = {0, 4096, 4096};
extern const VecFx32 data_020d0360;
const VecFx32 data_020d0360 = {1229, 0, -307};
EffectEmitterCbs data_020e162c[2] = {{EffectKind54_InitEmitter0, EffectKind54_UpdateEmitter0}, {EffectKind54_InitEmitter1, EffectEmitterEntry_UpdateKind54B}};
EffectEmitterCbs data_020e163c[2] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateKind59}, {EffectCb_InitTracked, EffectEmitterEntry_UpdateKind59}};
EffectEmitterCbs data_020e164c[2] = {{EffectKind3B_InitEmitter0, EffectKind3B_UpdateEmitter0}, {EffectKind3B_InitEmitter0, EffectKind3B_UpdateEmitter0}};
EffectOneShotCb data_020e165c[4] = {EffectKind24_InitEmitter0, EffectKind24_InitEmitter0, EffectKind24_InitEmitter0, EffectKind24_InitEmitter0};
EffectEmitterCbs data_020e166c[2] = {{EffectKind3D_InitEmitter0, EffectKind3D_UpdateEmitter0}, {EffectKind3D_InitEmitter0, EffectKind3D_UpdateEmitter0}};
EffectEmitterCbs data_020e167c[2] = {{EffectCb_InitTracked, EffectCb_CountdownTracked}, {EffectCb_InitTracked, EffectCb_CountdownTracked}};
EffectEmitterCbs data_020e168c[3] = {{EffectKind41_InitEmitter0, EffectKind41_UpdateEmitter0}, {EffectKind41_InitEmitter1, EffectKind41_UpdateEmitter1}, {EffectKind41_InitEmitter2, EffectKind41_UpdateEmitter2}};
EffectEmitterCbs data_020e16a4[3] = {{EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectKind11_UpdateEmitter2}};
EffectEmitterCbs data_020e16bc[3] = {{EffectKind4E_InitEmitter0, EffectKind4E_UpdateEmitter0}, {EffectKind4E_InitEmitter1, EffectKind4E_UpdateEmitter1}, {EffectCb_InitTracked, EffectCb_FollowTracked}};
EffectOneShotCb data_020e16d4[8] = {EffectCb_TintOnly, EffectCb_TintOnly, EffectCb_TintOnly, EffectCb_TintOnly, EffectCb_TintOnly, EffectCb_TintOnly, EffectCb_TintOnly, EffectCb_TintOnly};
EffectOneShotCb sEffectDefaultOneShotCbs[8] = {EffectCb_InitOneShot, EffectCb_InitOneShot, EffectCb_InitOneShot, EffectCb_InitOneShot, EffectCb_InitOneShot, EffectCb_InitOneShot, EffectCb_InitOneShot, EffectCb_InitOneShot};
EffectEmitterCbs data_020e1714[4] = {{EffectCb_InitTracked, EffectEmitterEntry_UpdateKind56Main}, {EffectCb_InitTracked, EffectEmitterEntry_UpdateKind56Fade}, {EffectCb_InitTracked, EffectEmitterEntry_UpdateKind56Fade}, {EffectCb_InitTracked, EffectEmitterEntry_UpdateKind56Fade}};
EffectEmitterCbs data_020e1734[5] = {{EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectKind35_InitEmitter1, EffectKind35_UpdateEmitter1}, {EffectKind35_InitEmitter1, EffectKind35_UpdateEmitter1}, {EffectKind35_InitEmitter3, EffectKind35_UpdateEmitter3}, {EffectKind35_InitEmitter4, EffectKind35_UpdateEmitter4}};
EffectEmitterCbs data_020e175c[5] = {{EffectCb_InitTracked, EffectKind25_UpdateEmitter0}, {EffectCb_InitTracked, EffectKind25_UpdateEmitter0}, {EffectCb_InitTracked, EffectKind25_UpdateEmitter0}, {EffectCb_InitTracked, EffectKind25_UpdateEmitter0}, {EffectCb_InitTracked, EffectKind25_UpdateEmitter0}};
EffectEmitterCbs data_020e1784[7] = {{EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectKind36_InitEmitter2, EffectKind36_UpdateEmitter2}, {EffectKind36_InitEmitter2, EffectKind36_UpdateEmitter2}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}};
EffectEmitterCbs sEffectDefaultTrackedCbs[8] = {{EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}};
EffectEmitterCbs data_020e17fc[8] = {{EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}, {EffectCb_InitTracked, EffectCb_FollowTracked}};
VecFx32 data_020e18a8[9] = {{-3277, 410, 1434}, {-3809, -778, 451}, {-2908, -410, -164}, {-3154, 1229, 0}, {-2867, -1638, -1229}, {-4096, 287, 1966}, {-2458, 1229, 614}, {-3482, 614, 1434}, {-3154, 1229, 0}};
VecFx32 data_020e183c[9] = {{819, -205, 3277}, {2294, -1679, 2580}, {1966, -778, 1679}, {2458, 410, 2048}, {2458, -2458, 778}, {1679, -819, 3809}, {1434, 614, 2048}, {1638, 205, 3277}, {2458, 410, 2048}};
EffectKindEntry sEffectKindTable[0x66] = {
    {Effect_CreateKind00, NULL},
    {Effect_CreateKind01, NULL},
    {Effect_CreateKind02, NULL},
    {Effect_CreateKind03, NULL},
    {Effect_CreateKind03, NULL},
    {Effect_CreateKind03, NULL},
    {Effect_CreateKind06, NULL},
    {Effect_CreateKind07, NULL},
    {Effect_CreateKind08, NULL},
    {Effect_CreateKind09, NULL},
    {Effect_CreateKind0A, NULL},
    {Effect_CreateKind0B, NULL},
    {Effect_CreateKind0C, NULL},
    {Effect_CreateKind0D, NULL},
    {Effect_CreateKind0E, Effect_EndDefault},
    {Effect_CreateKind0F, NULL},
    {Effect_CreateKind10, NULL},
    {Effect_CreateKind11, Effect_EndDefault},
    {Effect_CreateKind12, NULL},
    {Effect_CreateKind13, NULL},
    {Effect_CreateKind14, NULL},
    {Effect_CreateKind15, NULL},
    {Effect_CreateKind16, NULL},
    {Effect_CreateKind17, NULL},
    {Effect_CreateKind14, NULL},
    {Effect_CreateKind19, NULL},
    {Effect_CreateKind1A, Effect_EndDefault},
    {Effect_CreateKind1B, Effect_EndDefault},
    {Effect_CreateKind1C, Effect_EndDefault},
    {Effect_CreateKind1D, Effect_EndDefault},
    {Effect_CreateKind1E, Effect_EndDefault},
    {Effect_CreateKind1F, Effect_EndDefault},
    {Effect_CreateKind1B, Effect_EndDefault},
    {Effect_CreateKind21, Effect_EndDefault},
    {Effect_CreateKind22, NULL},
    {Effect_CreateKind23, NULL},
    {Effect_CreateKind24, NULL},
    {Effect_CreateKind25, Effect_EndDefault},
    {Effect_CreateKind26, Effect_EndDefault},
    {Effect_CreateKind27, NULL},
    {Effect_CreateKind28, NULL},
    {Effect_CreateKind29, NULL},
    {Effect_CreateKind2A, NULL},
    {Effect_CreateKind2B, NULL},
    {Effect_CreateKind2C, NULL},
    {Effect_CreateKind2D, NULL},
    {Effect_CreateKind2E, NULL},
    {Effect_CreateKind2F, NULL},
    {Effect_CreateKind30, Effect_EndDefault},
    {Effect_CreateKind31, Effect_EndDefault},
    {Effect_CreateKind32, NULL},
    {Effect_CreateKind33, Effect_EndDefault},
    {Effect_CreateKind34, Effect_EndDefault},
    {Effect_CreateKind35, Effect_EndDefault},
    {Effect_CreateKind36, Effect_EndDefault},
    {Effect_CreateKind37, NULL},
    {Effect_CreateKind38, NULL},
    {Effect_CreateKind39, NULL},
    {Effect_CreateKind3A, Effect_EndDefault},
    {Effect_CreateKind3B, Effect_EndDefault},
    {Effect_CreateKind3C, Effect_EndDefault},
    {Effect_CreateKind3D, Effect_EndKind3D},
    {Effect_CreateKind3E, NULL},
    {Effect_CreateKind3F, NULL},
    {Effect_CreateKind40, Effect_EndDefault},
    {Effect_CreateKind41, Effect_EndDefault},
    {Effect_CreateKind42, Effect_EndDefault},
    {Effect_CreateKind43, NULL},
    {Effect_CreateKind44, Effect_EndDefault},
    {Effect_CreateKind45, NULL},
    {Effect_CreateKind46, NULL},
    {Effect_CreateKind47, NULL},
    {Effect_CreateKind48, Effect_EndDefault},
    {Effect_CreateKind49, Effect_EndDefault},
    {Effect_CreateKind4A, Effect_EndDefault},
    {Effect_CreateKind4B, Effect_EndDefault},
    {Effect_CreateKind4C, Effect_EndDefault},
    {Effect_CreateKind4D, Effect_EndDefault},
    {Effect_CreateKind4E, Effect_EndDefault},
    {Effect_CreateKind4F, NULL},
    {Effect_CreateKind50, NULL},
    {Effect_CreateKind51, NULL},
    {Effect_CreateKind52, NULL},
    {Effect_CreateKind53, Effect_EndDefault},
    {Effect_CreateKind54, Effect_EndDefault},
    {Effect_CreateKind55, Effect_EndDefault},
    {Effect_CreateKind56, Effect_EndKind56},
    {Effect_CreateKind57, NULL},
    {Effect_CreateKind58, NULL},
    {Effect_CreateKind59, NULL},
    {Effect_CreateKind5A, NULL},
    {Effect_CreateKind5B, NULL},
    {Effect_CreateKind5C, NULL},
    {Effect_CreateKind5D, NULL},
    {Effect_CreateKind5E, NULL},
    {Effect_CreateKind5F, NULL},
    {Effect_CreateKind60, NULL},
    {Effect_CreateKind61, Effect_EndDefault},
    {Effect_CreateKind62, NULL},
    {Effect_CreateNone, NULL},
    {Effect_CreateOneShotRes, NULL},
    {Effect_CreateTrackedRes, Effect_EndDefault},
};
EffectManager gEffectManager;


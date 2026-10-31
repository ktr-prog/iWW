#include "types.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "gfx/VecFx32.h"
#include "net/CommManager.h"
#include "field/Snowball.h"
#include "actor/Actor.h"
#include "field/LooseSnowballs.h"
#include "field/SnowmanRecords.h"
#include "sys/ClockDateTime.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_020af3f4.h"
#include "proto/ov003/unk_ov003_02212830.h"
#include "proto/ov003/unk_ov003_0222e734.h"
#include "proto/main/unk_0204cc1c.h"

struct UnitMaskChunk {
    u16 bits[16];
    u16 cnt;
    UnitMaskChunk() {}
    ~UnitMaskChunk() {}
};

struct UnitMaskPool {
    UnitMaskChunk c[4][4];
};

extern "C" {
extern BlockMap *gSceneBlockMap;
extern CommManager *gCommManager;
#define data_021ed2e6 HOST_LABEL(SnowmanRecords *, data_021ed2e6)

BOOL Ground_IsFreeGrassOffPath(s32 a, s32 b);
BOOL Ground_IsFreeGrass(s32 a, s32 b);
void *MapBlock_GetItemPtr(void *c, u32 i, u32 j, s32 k);
void MapBlock_SetItem(void *c, u16 *p, u32 a, u32 b, u32 d);
BOOL Item_IsSnowman(u16 *p);
s32 Item_GetSnowmanIndex(u16 *p);
s32 GroundSeason_IsSnow();
s32 Scene_InTown();
void Clock_GetDateTime(ClockDateTime *p);
void DateTime_SubDays(ClockDateTime *p, s32 n);

void UnitMaskPool_Clear(UnitMaskPool *pool);
void UnitMaskChunk_Clear(UnitMaskChunk *c);
}

extern "C" {
Snowball *sSnowballs[8];
}


extern "C" void SnowballSpawner_SpawnLooseBalls(void *self) {
    if (gCommManager->isSlotActive(gCommManager->myAid) != 0 || GroundSeason_IsSnow() == 0) {
        LooseSnowballs_Get()->reset();
        return;
    }
    u8 year, month, day;
    u32 headSize, bodySize, rank;
    VecFx32 A, B;
    u32 i;
    for (i = 0; i < 3; i++) {
        ClockDateTimeWords now;
        now.words[0] = 0;
        now.words[1] = 0;
        Clock_GetDateTime(&now.dt);
        if (now.dt.hour < 6) {
            DateTime_SubDays(&now.dt, 1);
        }
        if (data_021ed2e6.getInfo(i, &headSize, &bodySize, &rank, &year, &month, &day) != 0) {
            if (year == now.dt.year && month == now.dt.month && day == now.dt.day) {
                LooseSnowballs_Get()->reset();
                return;
            }
        }
    }
    if (Scene_InTown() != 0) {
        if (data_021ed2e6.isFull() == 0) {
            if (LooseSnowballs_Get()->items[0].posX != 0) {
                LooseSnowball *s = &LooseSnowballs_Get()->items[0];
                A.x = s->posX;
                A.y = s->posY;
                A.z = s->posZ;
            } else {
                Snowball_FindSpawnPos(self, &A, 0, 1);
            }
            if (LooseSnowballs_Get()->items[1].posX != 0) {
                LooseSnowball *s = &LooseSnowballs_Get()->items[1];
                B.x = s->posX;
                B.y = s->posY;
                B.z = s->posZ;
            } else {
                Snowball_FindSpawnPos(self, &B, &A, 1);
            }
            if (Actor::spawn(0xbd, 0, &A, NULL, self)) {
                LooseSnowball *s = &LooseSnowballs_Get()->items[0];
                s->posX = A.x;
                s->posY = A.y;
                s->posZ = A.z;
            }
            if (Actor::spawn(0xbd, 1, &B, NULL, self)) {
                LooseSnowball *s = &LooseSnowballs_Get()->items[1];
                s->posX = B.x;
                s->posY = B.y;
                s->posZ = B.z;
            }
        }
    }
}

extern "C" void SnowballSpawner_SpawnSnowmen(void *self) {
    BlockMap *g = gSceneBlockMap;
    u32 by, bx;
    s32 lx, n;
    MapBlock *cell;
    for (by = 1; by <= 4; by++) {
        for (bx = 1; bx <= 4; bx++) {
            if (bx < g->width && by < g->height && g->blocks != 0) {
                cell = &g->blocks[by * g->width + bx];
            } else {
                cell = 0;
            }
            if (cell != 0) {
                s32 ly;
                for (ly = 0; ly < 16; ly++) {
                    for (lx = 0; lx < 16; lx++) {
                        u16 *t = (u16 *)MapBlock_GetItemPtr(cell, lx, ly, 0);
                        if (t != 0) {
                            if (Item_IsSnowman(t)) {
                                s32 v = Item_GetSnowmanIndex(t);
                                if (data_021ed2e6.getInfo(v, 0, 0, 0, 0, 0, 0) == 0) {
                                    u16 tmp[1];
                                    tmp[0] = 0xfff1;
                                    MapBlock_SetItem(cell, tmp, lx, ly, 0);
                                } else {
                                    n = v * 2 + 2;
                                    VecFx32 loc;
                                    FieldPos_FromBlockUnitCenter(&loc, bx, by, lx, ly);
                                    Actor::spawn(0xbd, n, &loc, NULL, self);
                                    Actor::spawn(0xbd, (n + 1), &loc, NULL, self);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

extern "C" BOOL Snowball_Register(Snowball *p) {
    Snowball **s = &sSnowballs[p->param & 7];
    if (*s != 0) {
        return FALSE;
    }
    *s = p;
    return TRUE;
}

extern "C" BOOL Snowball_Unregister(Snowball *p) {
    Snowball **s = &sSnowballs[p->param & 7];
    if (*s == p) {
        *s = 0;
        return TRUE;
    }
    return FALSE;
}

extern "C" Snowball *Snowball_FindByParam(u32 id) {
    u32 i;
    for (i = 0; i < 8; i++) {
        Snowball *p = sSnowballs[i];
        if (p != 0 && id == p->param) {
            return p;
        }
    }
    return 0;
}

extern "C" BOOL Snowball_TryPushAny(VecFx32 *outPos, s16 *outAng, s32 *outVal, s32 speed, s32 ang) {
    u32 i;
    for (i = 0; i < 8; i++) {
        if (sSnowballs[i] != 0) {
            if (Snowball_TryPush(sSnowballs[i], outPos, outAng, outVal, speed, ang)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

extern "C" Snowball *Snowball_GetLooseBall(u32 id) {
    Snowball *o = Snowball_FindByParam(id & 1);
    if (o != 0) {
        if (o->talkAct == 0) {
            if (o->snowballState == 0) {
                BOOL bit;
                if (o->snowballFlags.e) {
                    bit = TRUE;
                } else {
                    bit = FALSE;
                }
                if (bit == 0) {
                    if (o->collider.hitThisFrame == 0) {
                        return o;
                    }
                }
            }
        }
    }
    return 0;
}

extern "C" Snowball *Snowball_FindOtherInBallState(Snowball *self) {
    u32 i;
    for (i = 0; i < 8; i++) {
        Snowball *p = sSnowballs[i];
        if (p != 0 && p != self && Snowball_IsInBallState(p)) {
            return p;
        }
    }
    return 0;
}

extern "C" void UnitMaskChunk_Clear(UnitMaskChunk *c) {
    u32 i;
    for (i = 0; i < 16; i++) {
        c->bits[i] = 0;
    }
    c->cnt = 0x100;
}

extern "C" void UnitMaskChunk_Mark(UnitMaskChunk *c, s32 x, s32 y) {
    u8 ux = x & 15;
    u8 uy = y & 15;
    if (!UnitMaskChunk_IsMarked(c, x, y)) {
        c->bits[uy] |= 1 << ux;
        c->cnt--;
    }
}

extern "C" BOOL UnitMaskChunk_IsMarked(UnitMaskChunk *c, s32 x, s32 y) {
    s32 v = c->bits[(u8)(y & 15)];
    if ((v >> (u8)(x & 15)) & 1) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL UnitMaskChunk_PickRandom(UnitMaskChunk *c, s32 *ox, s32 *oy) {
    if (c->cnt != 0) {
        s32 r = Random_GlobalBelow(c->cnt);
        s32 n = 0;
        u32 i, j;
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 16; j++) {
                if (!UnitMaskChunk_IsMarked(c, j, i)) {
                    if (r == n) {
                        *ox = j;
                        *oy = i;
                        return TRUE;
                    }
                    n++;
                }
            }
        }
    }
    return FALSE;
}

extern "C" void UnitMaskPool_Clear(UnitMaskPool *pool) {
    u32 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            UnitMaskChunk_Clear(&pool->c[i][j]);
        }
    }
}

extern "C" s32 UnitMaskPool_CountFreeChunks(UnitMaskPool *pool) {
    s32 n = 0;
    u32 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (pool->c[i][j].cnt != 0) {
                n++;
            }
        }
    }
    return n;
}

extern "C" void UnitMaskPool_Mark(UnitMaskPool *pool, s32 x, s32 y) {
    UnitMaskChunk_Mark(&pool->c[((y - 16) >> 4) & 3][((x - 16) >> 4) & 3], x & 15, y & 15);
}

extern "C" BOOL UnitMaskPool_PickRandom(UnitMaskPool *pool, s32 *ox, s32 *oy) {
    s32 cnt = UnitMaskPool_CountFreeChunks(pool);
    if (cnt != 0) {
        s32 r = Random_GlobalBelow(cnt);
        s32 n = 0;
        u32 i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                UnitMaskChunk *c = &pool->c[i][j];
                if (c->cnt != 0) {
                    if (r == n) {
                        s32 px, py;
                        if (UnitMaskChunk_PickRandom(c, &px, &py)) {
                            *ox = ((j + 1) << 4) + px;
                            *oy = ((i + 1) << 4) + py;
                            return TRUE;
                        }
                        return FALSE;
                    }
                    n++;
                }
            }
        }
    }
    return FALSE;
}

UnitMaskPool Snowball_FindSpawnPos_pool;
u8 Snowball_FindSpawnPos_pool_init;
extern "C" BOOL Snowball_FindSpawnPos(void *a, VecFx32 *b, VecFx32 *c, s32 d) {
    BlockMap *g = gSceneBlockMap;
    if (!Snowball_FindSpawnPos_pool_init) {
        HOST_STATIC_CONSTRUCT(Snowball_FindSpawnPos_pool);
        Snowball_FindSpawnPos_pool_init = 1;
    }
    UnitMaskPool_Clear(&Snowball_FindSpawnPos_pool);
    u32 by, bx, ly, lx, k;
    for (by = 1; by < 6; by++) {
        for (bx = 1; bx < 6; bx++) {
            for (ly = 0; ly < 16; ly++) {
                for (lx = 0; lx < 16; lx++) {
                    s32 x, y;
                    FieldUnit_FromBlockUnit(&x, &y, bx, by, lx, ly);
                    if (!Ground_IsFreeGrassOffPath(x, y) || !Ground_IsFreeGrass(x, y + 1) || !Ground_IsFreeGrass(x, y + 2)) {
                        UnitMaskPool_Mark(&Snowball_FindSpawnPos_pool, x, y);
                    } else if (d != 0) {
                        s32 ex = *(volatile s32 *)&x;
                        s32 ey = *(volatile s32 *)&y;
                        s32 hx = ex >> 4;
                        s32 hy = ey >> 4;
                        u16 *cell = BlockMap_GetItemPtr(g, hx, hy, ex - (hx << 4), ey - (hy << 4), 0);
                        if (cell != 0 && *cell != 0xfff1) {
                            UnitMaskPool_Mark(&Snowball_FindSpawnPos_pool, x, y);
                        }
                    }
                }
            }
        }
    }
    if (c != 0) {
        s32 px, py;
        FieldPos_ToUnit(&px, &py, c);
        s32 yy, xx;
        for (yy = py - 7; yy <= py + 7; yy++) {
            for (xx = px - 7; xx <= px + 7; xx++) {
                UnitMaskPool_Mark(&Snowball_FindSpawnPos_pool, xx, yy);
            }
        }
    }
    s32 ox, oy;
    if (UnitMaskPool_PickRandom(&Snowball_FindSpawnPos_pool, &ox, &oy)) {
        FieldPos_FromUnitCenter(b, ox, oy);
        return TRUE;
    } else if (d != 0) {
        return Snowball_FindSpawnPos(a, b, c, 0);
    }
    return FALSE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_0222e734) {
    HOST_OVERLAY_VAR(sSnowballs),
    HOST_OVERLAY_VAR(Snowball_FindSpawnPos_pool),
    HOST_OVERLAY_VAR(Snowball_FindSpawnPos_pool_init),
    HOST_OVERLAY_VARS_END
};

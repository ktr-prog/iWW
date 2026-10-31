#include "types.h"
#include "gfx/VecFx32.h"
#include "gfx/Camera.h"
#include "gfx/CameraTownTour.h"
#include "actor/Actor.h"
#include "gfx/DebugColor.h"
#include "town/BlockMap.h"
#include "proto/itcm/unk_01ffcb2c.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_020943dc.h"
#include "proto/ov068/unk_ov068_0226647c.h"
#include "proto/main/unk_0204cc1c.h"

struct TownTourBuildingRange {
    u16 lo, hi;
};

extern "C" {
extern VecFx32 gVec3Zero;
extern BlockMap *gSceneBlockMap;
extern s16 data_02135f44[];
s32 func_01ffcb0c(s32 v1, s32 v2);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
BOOL Math_StepS32Alt(s32 *p, s32 target, s32 step);
s32 Math_ApproachVecXZ(VecFx32 *p, VecFx32 *target, s32 ratio, s32 max, s32 min);
BOOL Math_StepS16(s16 *p, s16 target, s16 step);
u16 Math_CountDownU16(u16 *p);
void Camera_StartBlend(void);
void Camera_FinishBlend(void);
}
extern const CameraSwayPattern kCameraSwayPatterns[4];

static inline void Camera_OrbitLookAtPoint(Camera *c) {
    VecFx32 v;
    c->updateBlend();
    Camera_GetLookAtPoint(&v, c);
    s32 a = c->getPitch();
    s32 b = c->getYaw();
    c->setLookAtOrbit(&v, a, b, c->getDistance());
}

extern "C" VecFx32 sTownTourOffsetPlayerHouse;
extern "C" VecFx32 sTownTourOffsetsNookShop[4];
extern "C" VecFx32 sTownTourOffsetMuseum;
extern "C" VecFx32 sTownTourOffsetAbleSisters;
extern "C" VecFx32 sTownTourOffsetTownHall;
extern "C" VecFx32 sTownTourOffsetGateHouse;
extern "C" VecFx32 sTownTourOffsetVillagerHouse;
extern "C" s32 data_ov068_0226fc48 = 0x100;
extern "C" VecFx32 *sTownTourOffsets[7] = {&sTownTourOffsetPlayerHouse, sTownTourOffsetsNookShop, &sTownTourOffsetVillagerHouse,
                                           &sTownTourOffsetMuseum, &sTownTourOffsetAbleSisters, &sTownTourOffsetTownHall,
                                           &sTownTourOffsetGateHouse};
extern "C" VecFx32 sTownTourOffsetVillagerHouse = {-0xc00, 0, 0x1c00};
extern "C" DebugColor data_ov068_02270fd4(0x1f, 0x14, 0x14, 0x1f);
extern "C" const u32 sTownTourBuildingAttrs[7] = {1, 2, 0, 0x800, 2, 0x200, 0x400};
extern "C" VecFx32 sTownTourOffsetsNookShop[4] = {{-0xc00, 0, 0x2400}, {-0xc00, 0, 0x1400},
                                                            {-0x2000, 0, 0x2400}, {-0x2c00, 0, 0x2400}};
extern "C" DebugColor data_ov068_02270fd0(0x14, 0x14, 0x1f, 0x1f);
extern "C" DebugColor data_ov068_02270fc4(0x1f, 0x1f, 0x14, 0x1f);
extern "C" DebugColor data_ov068_02270fc8(0x14, 0x1f, 0x14, 0x1f);
extern "C" VecFx32 sTownTourOffsetTownHall = {0, 0, 0x1c00};
extern "C" s32 data_ov068_0226fc44 = 0x80;
extern "C" VecFx32 sTownTourOffsetMuseum = {0, 0, 0xc00};
extern "C" DebugColor data_ov068_02270fd8(0x14, 0x1f, 0x1f, 0x1f);
extern "C" VecFx32 sTownTourOffsetAbleSisters = {-0xc00, 0, 0x2400};
extern "C" VecFx32 sTownTourOffsetPlayerHouse = {0, 0, 0x1c00};
extern "C" VecFx32 sTownTourOffsetGateHouse = {0x1000, 0, 0x1000};
extern "C" TownTourBuildingRange sTownTourBuildings[7] = {{0x5014, 0x501a}, {0x500d, 0x500d}, {0x5001, 0x5001}, {0x5011, 0x5011},
                                                           {0x500c, 0x500c}, {0x5000, 0x5000}, {0x500b, 0x500b}};
extern "C" s32 data_ov068_0226fc40 = 1;
extern "C" DebugColor data_ov068_02270fcc(0x14, 0x18, 0x18, 0x1f);

extern "C" BOOL CameraEventModes_InitModeFollowTarget(Camera *c) {
    c->loadPose(0, NULL);
    c->setBlendPreset(0);
    Camera_FinishBlend();
    return TRUE;
}

extern "C" void CameraEventModes_UpdateModeFollowTarget(Camera *c) {
    VecFx32 d;
    Actor *o = c->followTarget;
    d.x = 0;
    d.y = 0;
    d.z = 0;
    if (o) {
        VecFx32 *pv = &o->position;
        d.x = pv->x;
        d.y = pv->y;
        d.z = pv->z;
    }
    c->dragFocusTo(&d);
    Camera_OrbitLookAtPoint(c);
}

extern "C" BOOL CameraEventModes_InitModeTownTour(Camera *c) {
    u16 e[2];
    c->loadPose(0, NULL);
    c->setBlendPreset(0);
    Camera_FinishBlend();
    BlockMap *g = gSceneBlockMap;
    s32 bx = 0, bz = 0, ux = 0, uz = 0;
    CameraTownTourState *s = &c->townTour;
    s->holdTimer = 0x3c;
    s->buildingIndex = 0;
    if (g) {
        e[0] = 0x5014;
        e[1] = 0x501a;
        if (BlockMap_FindItemAllAttr(g, &bx, &bz, &ux, &uz, &e[0], &e[1], 1, 0) == 1) {
            VecFx32 pos;
            FieldPos_FromBlockUnitCenter(&pos, bx, bz, ux, uz);
            s->offset = sTownTourOffsets[0];
            c->targetFocus.x = pos.x;
            c->targetFocus.y = pos.y;
            c->targetFocus.z = pos.z;
        }
    }
    s->building.x = c->targetFocus.x;
    s->building.y = c->targetFocus.y;
    s->building.z = c->targetFocus.z;
    c->targetFocus.x += s->offset->x;
    c->targetFocus.y += s->offset->y;
    c->targetFocus.z += s->offset->z;
    s->speed = 0;
    return TRUE;
}

extern "C" void CameraEventModes_UpdateModeTownTour(Camera *c) {
    CameraTownTourState *s = &c->townTour;
    VecFx32 v;
    v.x = s->building.x;
    v.y = s->building.y;
    v.z = s->building.z;
    VEC_Add(&v, s->offset, &v);
    Math_StepS32Alt(&s->speed, data_ov068_0226fc48, data_ov068_0226fc40);
    if (Math_ApproachVecXZ(&c->targetFocus, &v, data_ov068_0226fc44, s->speed, 8) == 0) {
        if (Math_StepS16((s16 *)&s->holdTimer, 0, 1) != 0) {
            s->holdTimer = 0x3c;
            if (Math_StepS16(&s->buildingIndex, 7, 1) != 0) {
                s->buildingIndex = 0;
            }
            BlockMap *g = gSceneBlockMap;
            s32 cnt = 0;
            struct { u16 a, b; } out;
            s32 bx = 0, bz = 0, ux = 0, uz = 0;
            if (g != NULL) {
                TownTourBuildingRange *tbl = sTownTourBuildings;
                do {
                    TownTourBuildingRange *e = &tbl[s->buildingIndex];
                    u16 t = e->lo;
                    BOOL r1;
                    if (t >= 0x5001 && t <= 0x5008) {
                        r1 = TRUE;
                    } else {
                        r1 = FALSE;
                    }
                    if (r1) {
                        e->lo++;
                        if (tbl[s->buildingIndex].lo > 0x5008) {
                            tbl[s->buildingIndex].lo = 0x5001;
                        }
                        tbl[s->buildingIndex].hi = tbl[s->buildingIndex].lo;
                    } else {
                        BOOL r2;
                        if (t >= 0x500d && t <= 0x5010) {
                            r2 = TRUE;
                        } else {
                            r2 = FALSE;
                        }
                        if (r2) {
                            e->lo++;
                            if (tbl[s->buildingIndex].lo > 0x5010) {
                                tbl[s->buildingIndex].lo = 0x500d;
                            }
                            tbl[s->buildingIndex].hi = tbl[s->buildingIndex].lo;
                            cnt = tbl[s->buildingIndex].lo - 0x500d;
                        }
                    }
                    out.a = tbl[s->buildingIndex].lo;
                    out.b = tbl[s->buildingIndex].hi;
                } while (BlockMap_FindItemAllAttr(g, &bx, &bz, &ux, &uz, &out.a, &out.b, sTownTourBuildingAttrs[s->buildingIndex], 0) == 0);
                VecFx32 pos;
                FieldPos_FromBlockUnitCenter(&pos, bx, bz, ux, uz);
                s->building.x = pos.x;
                s->building.y = pos.y;
                s->building.z = pos.z;
                s->offset = &sTownTourOffsets[s->buildingIndex][cnt];
                s->speed = 0;
            }
        }
    }
    Camera_OrbitLookAtPoint(c);
}

extern "C" BOOL CameraEventModes_InitMode13(Camera *c) {
    c->loadPose(0x1a, NULL);
    Camera_FinishBlend();
    return TRUE;
}

extern "C" void CameraEventModes_UpdateMode13(Camera *c) {
    VecFx32 d;
    d = gVec3Zero;
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p) {
        d = *p;
    }
    c->dragFocusTo(&d);
    Camera_OrbitLookAtPoint(c);
}

extern "C" BOOL CameraEventModes_InitModeSway(Camera *c) {
    c->loadPose(0x10, NULL);
    c->setBlendPreset(0);
    if (c->prevMode == 2) {
        Camera_StartBlend();
    } else {
        Camera_FinishBlend();
    }
    c->setFovy(0x1c71);
    Camera_SetSwayPattern(c, 0);
    return TRUE;
}

extern "C" void CameraEventModes_UpdateModeSway(Camera *c) {
    c->targetFocus.x = gVec3Zero.x;
    c->targetFocus.y = gVec3Zero.y;
    c->targetFocus.z = gVec3Zero.z;
    c->targetFocus.y += Camera_UpdateSway(c);
    Camera_OrbitLookAtPoint(c);
}

extern "C" void Camera_SetSwayPattern(Camera *c, s32 idx) {
    c->sway.bobPattern = idx;
    if (c->sway.bobPattern >= 4) {
        c->sway.bobPattern = 0;
    }
    c->sway.bobTimer = kCameraSwayPatterns[c->sway.bobPattern].duration;
    c->sway.bobTimer += Random_GlobalBelow(kCameraSwayPatterns[c->sway.bobPattern].durationRand);
    c->sway.bobPhase = 0;
}

extern "C" void Camera_SetSwayPattern2(Camera *c, s32 idx) {
    c->sway.rollPattern = idx;
    if (c->sway.rollPattern >= 4) {
        c->sway.rollPattern = 0;
    }
    c->sway.rollTimer = kCameraSwayPatterns[c->sway.rollPattern].duration;
    c->sway.rollTimer += Random_GlobalBelow(kCameraSwayPatterns[c->sway.rollPattern].durationRand);
    c->sway.rollPhase = 0;
}

extern "C" s32 Camera_UpdateSway(Camera *c) {
    if (Math_CountDownU16(&c->sway.bobTimer) == 0) {
        s16 a = c->sway.bobPhase;
        if (a < 0) {
            a = -a;
        }
        if (a < 0x100) {
            u8 s = c->sway.bobPattern;
            if (s == 0) {
                if (Random_GlobalBelow(100) < 80) {
                    c->sway.bobPattern = 1;
                } else {
                    c->sway.bobPattern = 2;
                }
            } else if (s == 2) {
                c->sway.bobPattern = 1;
            } else {
                c->sway.bobPattern = 0;
            }
            Camera_SetSwayPattern(c, c->sway.bobPattern);
        }
    }
    if (Math_CountDownU16(&c->sway.rollTimer) == 0) {
        s16 a = c->sway.rollPhase;
        if (a < 0) {
            a = -a;
        }
        if (a < 0x100) {
            u8 s = c->sway.rollPattern;
            if (s == 0) {
                c->sway.rollPattern = 1;
            } else if (s == 2) {
                c->sway.rollPattern = 1;
            } else {
                c->sway.rollPattern = 0;
            }
            Camera_SetSwayPattern2(c, c->sway.rollPattern);
        }
    }
    s32 d = kCameraSwayPatterns[c->sway.rollPattern].phaseStep;
    if (d != 0) {
        c->sway.rollPhase = c->sway.rollPhase + d;
        u32 idx = ((u16)c->sway.rollPhase >> 4) * 2;
        c->roll = func_01ffcb0c(data_02135f44[idx], kCameraSwayPatterns[c->sway.rollPattern].amplitude);
    }
    d = kCameraSwayPatterns[c->sway.bobPattern].phaseStep;
    if (d != 0) {
        c->sway.bobPhase = c->sway.bobPhase + d;
        u32 idx = ((u16)c->sway.bobPhase >> 4) * 2;
        return func_01ffcb0c(data_02135f44[idx], kCameraSwayPatterns[c->sway.bobPattern].amplitude);
    }
    return 0;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov068_0226647c) {
    HOST_OVERLAY_VAR(data_ov068_0226fc48),
    HOST_OVERLAY_VAR(sTownTourOffsets),
    HOST_OVERLAY_VAR(sTownTourOffsetVillagerHouse),
    HOST_OVERLAY_VAR(data_ov068_02270fd4),
    HOST_OVERLAY_VAR(sTownTourOffsetsNookShop),
    HOST_OVERLAY_VAR(data_ov068_02270fd0),
    HOST_OVERLAY_VAR(data_ov068_02270fc4),
    HOST_OVERLAY_VAR(data_ov068_02270fc8),
    HOST_OVERLAY_VAR(sTownTourOffsetTownHall),
    HOST_OVERLAY_VAR(data_ov068_0226fc44),
    HOST_OVERLAY_VAR(sTownTourOffsetMuseum),
    HOST_OVERLAY_VAR(data_ov068_02270fd8),
    HOST_OVERLAY_VAR(sTownTourOffsetAbleSisters),
    HOST_OVERLAY_VAR(sTownTourOffsetPlayerHouse),
    HOST_OVERLAY_VAR(sTownTourOffsetGateHouse),
    HOST_OVERLAY_VAR(sTownTourBuildings),
    HOST_OVERLAY_VAR(data_ov068_0226fc40),
    HOST_OVERLAY_VAR(data_ov068_02270fcc),
    HOST_OVERLAY_VARS_END
};

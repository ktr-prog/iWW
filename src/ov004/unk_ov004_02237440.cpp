#include "ds_div.h"
#include "host_tick.h"
#include "host_labels.h"
#include "host_overlay_vars.h"
#include "uptr.h"
#include "proto/main/unk_0202fa70.h"
#include "types.h"
#include "gfx/Mtx43.h"
#include "Unk_020d8c7c.h"
#include "gfx/VecFx32.h"
#include "game/GroundInfoBase.h"
#include "gfx/ModelAnim.h"
#include "gfx/AnimModel.h"
#include "game/CollisionState.h"
#include "snd/CreatureSndChannel.h"
#include "actor/StaticCollider.h"
#include "game/GroundInfo.h"
#include "sys/ProcProfile.h"
#include "actor/ActorCollider.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/CachedModel.h"
#include "gfx/ModelSlotPool.h"
#include "gfx/PooledModel.h"
#include "gfx/TwoLayerAnimModel.h"
#include "save/MuseumData.h"
#include "snd/SndEnvChannel.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_02133d04.h"
#include "proto/main/unk_02000c2c.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0208f268.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_0209c08c.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/ov004/unk_ov004_02213b90.h"
#include "proto/ov004/unk_ov004_02237440.h"
#include "gfx/Model.h"
#include "game/BoxCollider.h"
#include "actor/Actor.h"
#include "game/FxVec3.h"





class MuseumInsectAnim : public ModelAnim {
public:
    MuseumInsectAnim();
    virtual ~MuseumInsectAnim();
};

struct MuseumInsectPlayerInfo;

struct MuseumInsectBehavior {
    void (*setup)(MuseumInsect *);
    void (*update)(MuseumInsect *);
};

struct MinuteHour {
    u8 minute;
    u8 hour;
};


struct MuseumInsectParam {
    u8 useVisAnim;
    u8 pad_01;
    s16 radius;
};

struct Unk_ov004_0223b1e8_Bits {
    u32 lo : 12;
    u32 mid : 16;
    u32 hi : 4;
};

class MuseumInsect {
public:
    MuseumInsect();
    ~MuseumInsect();

    void setupLanternFly();
    void setupEveningCicada();
    void setupWalkerCicada();
    void setupRobustCicada();
    void setupBrownCicada();
    void updateCicada();
    void setupOakSilkMoth();
    void setupWalkingstick();
    void setupGoliathBeetle();
    void setupScarabBeetle();
    void setupRainbowStag();
    void setupLonghornBeetle();
    void setupFruitBeetle();
    void setupJewelBeetle();
    void setupGiantBeetle();
    void setupStagBeetle();
    void setupSawStagBeetle();
    void setupDynastidBeetle();
    void setupAtlasBeetle();
    void setupElephantBeetle();
    void setupHerculesBeetle();
    void updatePerched();
    void setupPerched(s32 a, s32 b);
    void updateMosquito();
    void setupMosquito();
    void updateFirefly();
    void setupFirefly();
    void setupMoth();
    void updateMoth();
    void setupBirdwing();
    void setupAgrias();
    void setupEmperor();
    void setupMonarch();
    void setupPeacock();
    void setupTigerButterfly();
    void setupYellowButterfly();
    void setupCommonButterfly();
    void setupFlyer(s32 a, s32 b, s32 c, s32 d, s32 e);
    void updateButterfly();
    void init(u32 a, s32 b, s32 c, s16 d, s32 e, s32 f);
    void setBoundsAroundPos();
    void setBounds(s32 *a, s32 *b);
    void wander();
    void reactToPlayer(u16 *out);
    void runWalker();

    void runCicada();
    void sidestep(volatile s16 *p);
    void crawlDown(volatile s16 *p);
    void crawlUp(volatile s16 *p);
    void animSilkMoth();
    void runPerched();
    BOOL swing(s16 *p);
    BOOL isPlayerNear();
    void runSpider();
    s32 crawl();
    void scurry(MuseumInsectPlayerInfo *v);

    /* 0x000 */ MuseumInsectAnim matAnim;
    /* 0x020 */ u8 isBumped;
    /* 0x021 */ u8 isFighting;
    /* 0x022 */ u8 isActive;
    /* 0x023 */ u8 pad_23;
    /* 0x024 */ CreatureSndChannel sound;
    /* 0x030 */ u16 unk_30;
    /* 0x032 */ u8 pad_32[2];
    /* 0x034 */ VecFx32 targetPos;
    /* 0x040 */ VecFx32 homePos;
    union {
        /* 0x04c */ s32 speciesWork;
        /* 0x04c */ s32 flyAnimSpeed;
        /* 0x04c */ s32 hasBitten;
    };
    union {
        /* 0x050 */ u8 cooldown;
        /* 0x050 */ u8 wanderThreshold;
        /* 0x050 */ u8 steerSide;
    };
    /* 0x051 */ u8 pad_51[3];
    /* 0x054 */ s32 targetHeight;
    /* 0x058 */ Vec2 boundsMin;
    /* 0x060 */ Vec2 boundsMax;
    /* 0x068 */ CollisionState moveResult;
    /* 0x098 */ s16 subCounter;
    /* 0x09a */ u8 isAlerted;
    /* 0x09b */ u8 pad_9b;
    /* 0x09c */ s16 alertLevel;
    /* 0x09e */ s16 alertThreshold;
    /* 0x0a0 */ s32 alertRange;
    /* 0x0a4 */ u8 travelDistance;
    /* 0x0a5 */ u8 pad_a5[3];
    /* 0x0a8 */ s32 baseHeight;
    /* 0x0ac */ s16 targetAngle;
    union {
        /* 0x0ae */ u8 sideDir;
        /* 0x0ae */ u8 isPerched;
    };
    /* 0x0af */ u8 pad_af;
    /* 0x0b0 */ AnimModel model;
    /* 0x168 */ s16 stateCounter;
    /* 0x16a */ s16 flapPeriod;
    /* 0x16c */ s32 moveSpeed;
    /* 0x170 */ u8 dirFlag;
    /* 0x171 */ u8 pad_171;
    /* 0x172 */ s16 moveState;
    /* 0x174 */ s32 stateTimer;
    /* 0x178 */ FxVec3 probePoints[2];
    /* 0x190 */ s16 pitch;
    /* 0x192 */ s16 yaw;
    /* 0x194 */ s16 roll;
    /* 0x196 */ s8 insectIndex;
    /* 0x197 */ u8 pad_197;
    /* 0x198 */ s32 loadState;
    /* 0x19c */ StaticCollider hitBox;
    /* 0x1e8 */ CachedModel cachedModel;
    /* 0x284 */ ModelSlotHandle modelSlot;
    /* 0x288 */ PooledModel pooledModel;
    /* 0x2c8 */ VecFx32 position;
    /* 0x2d4 */ void (*updateFn)(MuseumInsect *);
};

typedef VecFx32 V3_7690;


struct MuseumInsectPlaceStackPad {
    u32 v[0xa9];
    MuseumInsectPlaceStackPad() {}
    ~MuseumInsectPlaceStackPad() {}
};

struct MuseumFireflyStackPad {
    s32 v[3];
    MuseumFireflyStackPad() {}
    ~MuseumFireflyStackPad() {}
};

struct MuseumInsectPlayerInfo {
    VecFx32 playerPos;
    s32 playerSpeed;
    s32 playerDist;
    u8 hasPlayer;
};


typedef VecFx32 V3_b1e8;

static inline s32 Abs_c8d4(s32 x) { if (x < 0) return -x; return x; }

struct V3z_c8d4 { s32 x, y, z; V3z_c8d4() {} ~V3z_c8d4() {} };

typedef VecFx32 V3_d800;


class MuseumInsectRoom : public GameProc {
public:
    MuseumInsectRoom();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual ~MuseumInsectRoom();

    void releaseInsect(s32 idx);
    BOOL getInsectRoom(u32 idx);
    void spawnDonatedInsects();
    BOOL hasShadow(MuseumInsect *e);
    void updateObstacles();
    BOOL hasHitBox(u32 id, u8 flag);
    void updateInsect(MuseumInsect *e);

    /* 0x050 */ StaticCollider obstacleHitBoxes[4];
    /* 0x180 */ ModelSlotPool modelPool;
    /* 0x198 */ void *dungBeetleAnimFile;
    /* 0x19c */ void *dungBallAnimFile;
};

extern "C" {
#define data_021ed0a0 HOST_LABEL(MuseumData *, data_021ed0a0)
u8 *func_02106788(u8 *p);
u8 *func_021067a4(u8 *p, u32 i);
u8 *func_021065dc(u8 *p);
u8 *func_021065f8(u8 *p, u32 i);
u8 *func_02106654(u8 *p);
u8 *func_02106670(u8 *p, u32 i);
u32 NNS_G3dMdlGetMdlAlpha(void *res, u32 i);
BOOL BoxCollider_Register(BoxCollider *n, s32 a, s32 b, s32 c, VecFx32 *pos, s16 angle, VecFx32 *scale);
BOOL BoxCollider_Unregister(BoxCollider *n);
s32 Vec_DistXZ(void *a, void *b);
s32 Model_GetJointWorldMtx(void *obj, void *buf, s32 z);
void Mtx43_SetTranslate(void *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(void *m, s16 a);
void Mtx43_RotateY(void *m, s32 a);
void Mtx43_RotateZ(void *m, s32 a);
extern V3_7690 sMuseumFleaDrawScale;
extern Mtx43 data_021f47e0;
s32 func_01ffcb0c(s32 a, s32 b);
void NNS_G3dMdlSetMdlAlpha(void *c, s32 i, s32 v);
#define data_02136744 HOST_LABEL(s16 (*)[], data_02136744)
void Vec_Sub(void *out, void *a, void *b);
s32 Vec_SafeNormalize(void *v);
s32 Vec_DotXZ(void *a, void *b);
s32 Math_StepAngle(void *p, s32 target, s32 step);
extern s16 data_02135f44[];
s32 Math_ApproachS32(void *v, s32 a, s32 b, s32 c, s32 d);
void Vec_ScaleTo(void *out, void *in, s32 s);
void VEC_Subtract(void *a, void *b, void *c);
void VEC_Add(void *a, void *b, void *c);
s32 Math_ApproachVecXZ(void *a, void *b, s32 c, s32 d, s32 e);
s32 FX_Div(s32, s32);
s32 Math_ApproachVec(void *a, void *b, s32 c, s32 d, s32 e);
void Vec_RotateY(void *v, s32 a);
void Clock_GetMinuteHour(MinuteHour *out);
}



extern "C" ProcProfile sMuseumInsectRoomProfile = {MuseumInsectRoom_Create, 0xbe, 0xc1};
extern "C" s8 sMuseumScorpionSlot = -1;
extern "C" s8 sMuseumDungBallSlot = -1;
extern "C" V3_7690 sMuseumFleaDrawScale = {0x2000, 0x2000, 0x2000};
extern "C" MuseumInsectParam sMuseumInsectParams[57] = {
    {0, 0, 0x514},
    {0, 0, 0x514},
    {0, 0, 0x6a4},
    {0, 0, 0x6a4},
    {0, 0, 0x6a4},
    {0, 0, 0x708},
    {0, 0, 0x640},
    {0, 0, 0x898},
    {0, 0, 0x6a4},
    {0, 0, 0x960},
    {1, 0, 0x44c},
    {1, 0, 0x708},
    {1, 0, 0x640},
    {1, 0, 0x514},
    {0, 0, 0x578},
    {0, 0, 0x514},
    {1, 0, 0x514},
    {1, 0, 0x514},
    {1, 0, 0x4b0},
    {1, 0, 0x4b0},
    {0, 0, 0x578},
    {1, 0, 0x578},
    {1, 0, 0x708},
    {1, 0, 0x898},
    {0, 0, 0x0},
    {1, 0, 0x514},
    {1, 0, 0x3e8},
    {1, 0, 0x44c},
    {1, 0, 0x3e8},
    {1, 0, 0x4b0},
    {1, 0, 0x3e8},
    {1, 0, 0x514},
    {1, 0, 0x3e8},
    {1, 0, 0x4b0},
    {1, 0, 0x4b0},
    {0, 0, 0x400},
    {1, 0, 0x640},
    {0, 0, 0x44c},
    {1, 0, 0x4b0},
    {1, 0, 0x514},
    {1, 0, 0x578},
    {1, 0, 0x578},
    {1, 0, 0x578},
    {1, 0, 0x514},
    {1, 0, 0x578},
    {1, 0, 0x640},
    {1, 0, 0x640},
    {1, 0, 0x708},
    {1, 0, 0x3e8},
    {1, 0, 0x190},
    {1, 0, 0x3e8},
    {1, 0, 0x514},
    {1, 0, 0x514},
    {0, 0, 0x3e8},
    {0, 0, 0x7d0},
    {0, 0, 0x7d0},
    {0, 0, 0xb00},
};
template <void (MuseumInsect::*M)()> static void MuseumInsect_Call(MuseumInsect *o) { (o->*M)(); }

extern "C" MuseumInsectBehavior sMuseumInsectBehaviors[57] = {
    {MuseumInsect_Call<&MuseumInsect::setupCommonButterfly>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupYellowButterfly>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupTigerButterfly>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupPeacock>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupMonarch>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupEmperor>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupAgrias>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupBirdwing>, MuseumInsect_Call<&MuseumInsect::updateButterfly>},
    {MuseumInsect_Call<&MuseumInsect::setupMoth>, MuseumInsect_Call<&MuseumInsect::updateMoth>},
    {MuseumInsect_Call<&MuseumInsect::setupOakSilkMoth>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_SetupHoneybee, MuseumInsect_UpdateHoneybee},
    {MuseumInsect_SetupBee, MuseumInsect_UpdateBee},
    {MuseumInsect_SetupLongLocust, MuseumInsect_UpdateHopper},
    {MuseumInsect_SetupMigratoryLocust, MuseumInsect_UpdateHopper},
    {MuseumInsect_SetupMantis, MuseumInsect_UpdateWalker},
    {MuseumInsect_SetupOrchidMantis, MuseumInsect_UpdateWalker},
    {MuseumInsect_Call<&MuseumInsect::setupBrownCicada>, MuseumInsect_Call<&MuseumInsect::updateCicada>},
    {MuseumInsect_Call<&MuseumInsect::setupRobustCicada>, MuseumInsect_Call<&MuseumInsect::updateCicada>},
    {MuseumInsect_Call<&MuseumInsect::setupWalkerCicada>, MuseumInsect_Call<&MuseumInsect::updateCicada>},
    {MuseumInsect_Call<&MuseumInsect::setupEveningCicada>, MuseumInsect_Call<&MuseumInsect::updateCicada>},
    {MuseumInsect_Call<&MuseumInsect::setupLanternFly>, MuseumInsect_Call<&MuseumInsect::updateCicada>},
    {MuseumInsect_SetupRedDragonfly, MuseumInsect_UpdateDragonfly},
    {MuseumInsect_SetupDarnerDragonfly, MuseumInsect_UpdateDragonfly},
    {MuseumInsect_SetupBandedDragonfly, MuseumInsect_UpdateDragonfly},
    {MuseumInsect_SetupAnt, MuseumInsect_UpdateAnt},
    {MuseumInsect_SetupPondSkater, MuseumInsect_UpdatePondSkater},
    {MuseumInsect_SetupSnail, MuseumInsect_UpdateWalker},
    {MuseumInsect_SetupCricket, MuseumInsect_UpdateHopper},
    {MuseumInsect_SetupBellCricket, MuseumInsect_UpdateHopper},
    {MuseumInsect_SetupGrasshopper, MuseumInsect_UpdateHopper},
    {MuseumInsect_SetupMoleCricket, MuseumInsect_UpdateMoleCricket},
    {MuseumInsect_Call<&MuseumInsect::setupWalkingstick>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_SetupLadybug, MuseumInsect_UpdateWalker},
    {MuseumInsect_Call<&MuseumInsect::setupFruitBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupScarabBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_SetupDungBeetle, MuseumInsect_UpdateDungBeetle},
    {MuseumInsect_Call<&MuseumInsect::setupGoliathBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupFirefly>, MuseumInsect_Call<&MuseumInsect::updateFirefly>},
    {MuseumInsect_Call<&MuseumInsect::setupJewelBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupLonghornBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupSawStagBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupStagBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupGiantBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupRainbowStag>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupDynastidBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupAtlasBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupElephantBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_Call<&MuseumInsect::setupHerculesBeetle>, MuseumInsect_Call<&MuseumInsect::updatePerched>},
    {MuseumInsect_SetupFlea, MuseumInsect_UpdateFlea},
    {MuseumInsect_SetupPillBug, MuseumInsect_UpdatePillBug},
    {MuseumInsect_Call<&MuseumInsect::setupMosquito>, MuseumInsect_Call<&MuseumInsect::updateMosquito>},
    {MuseumInsect_SetupFly, MuseumInsect_UpdateFly},
    {MuseumInsect_SetupCockroach, MuseumInsect_UpdateCockroach},
    {MuseumInsect_SetupSpider, MuseumInsect_UpdateSpider},
    {MuseumInsect_SetupTarantula, MuseumInsect_UpdateArachnid},
    {MuseumInsect_SetupScorpion, MuseumInsect_UpdateArachnid},
    {MuseumInsect_SetupDungBeetle, MuseumInsect_UpdateDungBeetle},
};
extern "C" {
u8 sMuseumInsectFrame;
}
MuseumInsect sMuseumInsects[0x20];

extern "C" u8 MuseumInsect_CheckFloorAhead(void *o_) {
    MuseumInsect *o = (MuseumInsect *)o_;
    MuseumInsect_SetProbePoints(o);
    return MuseumInsect_ProbeFloor(o);
}

extern "C" u8 MuseumInsect_CheckWallsAhead(void *o_) {
    MuseumInsect *o = (MuseumInsect *)o_;
    MuseumInsect_SetProbePoints(o);
    return MuseumInsect_ProbeWalls(o);
}

extern "C" u8 MuseumInsect_ProbeFloor(MuseumInsect *o) {
    u8 b = o->insectIndex;
    u8 r = 0;
    V3_d800 *p = &o->probePoints[0];
    s32 d;
    {
        GroundInfo g;
        g.initAtPos((VecFx32 *)(p), 0, 1);
        d = g.getHeight(1);
    }
    if (d <= 0 || d > p->y || (b == 0x1e && MuseumInsect_ClampToBounds(o, p) != 0)) {
        r++;
    }
    {
        GroundInfo g;
        g.initAtPos((VecFx32 *)(p + 1), 0, 1);
        d = g.getHeight(1);
    }
    if (d <= 0 || d > p[1].y || (b == 0x1e && MuseumInsect_ClampToBounds(o, p + 1) != 0)) {
        r = r + 2;
    }
    return r;
}

extern "C" u8 MuseumInsect_ProbeWalls(MuseumInsect *o) {
    u8 r = 0;
    V3_d800 *p = &o->probePoints[0];
    s32 lim = o->position.y;
    CollisionState buf;
    s16 ang = o->yaw;
    Collision_Move(&buf, p, p, ang, 0x266, NULL, 0xb);
    if (p->y > lim) {
        r++;
    }
    Collision_Move(&buf, p + 1, p + 1, ang, 0x266, NULL, 0xb);
    if (p[1].y > lim) {
        r = r + 2;
    }
    return r;
}

extern "C" void MuseumInsect_SetProbePoints(MuseumInsect *o) {
    V3_d800 *b = &o->position;
    s32 a = o->yaw;
    V3_d800 *out = o->probePoints;
    s32 i = (u16)(s16)(a + 0xe38) >> 4;
    s32 z = b->z + data_02135f44[i * 2 + 1];
    s32 y = b->y;
    s32 x = b->x + data_02135f44[i * 2];
    out[0].x = x;
    out[0].y = y;
    out[0].z = z;
    i = (u16)(s16)(a - 0xe38) >> 4;
    z = b->z + data_02135f44[i * 2 + 1];
    y = b->y;
    x = b->x + data_02135f44[i * 2];
    out[1].x = x;
    out[1].y = y;
    out[1].z = z;
}

extern "C" void MuseumInsect_MakeStepDir(void *v_, s32 a) {
    V3_d800 *v = (V3_d800 *)v_;
    v->x = 0;
    v->y = 0;
    v->z = 0x29;
    Vec_RotateY(v, a);
}

extern "C" s16 MuseumInsect_RandHeading() {
    u32 r = (u8)Random_GlobalBelow(0x10);
    if (r > 8) {
        r = -(r - 8);
    }
    return (s16)(r * 0xaaa);
}

extern "C" void MuseumInsect_PointAtAngle(void *out_, void *base_, u32 ang, s32 rad) {
    V3_d800 *out = (V3_d800 *)out_;
    V3_d800 *base = (V3_d800 *)base_;
    s32 z;
    s32 i = ((u16)ang >> 4) * 2;
    z = base->z + func_01ffcb0c(rad, data_02135f44[i + 1]);
    s32 x = base->x + func_01ffcb0c(rad, data_02135f44[i]);
    out->x = x;
    out->y = 0;
    out->z = z;
}

extern "C" void MuseumInsect_FlapWings(void *o_) {
    MuseumInsect *o = (MuseumInsect *)o_;
    AnimModel *p = &o->model;
    if (((Unk_ov004_0223b1e8_Bits &)p->curFrame).mid == 1) {
        ((AnimModel *)(p))->setFrame(2);
    } else {
        ((AnimModel *)(p))->setFrame(1);
    }
}

extern "C" BOOL MuseumInsect_RevertIfOffFloor(void *o_, void *v_) {
    V3_d800 *o = (V3_d800 *)o_;
    V3_d800 *v = (V3_d800 *)v_;
    BOOL r = TRUE;
    BOOL far;
    {
        VecFx32Ctor a(o->x, 0, v->z);
        GroundInfo g;
        g.initAtPos((VecFx32 *)(&a), 0, 0);
        if (g.getHeight(0) > 0x200) {
            far = r;
        } else {
            far = FALSE;
        }
    }
    if (far) {
        o->x = v->x;
        r = FALSE;
    }
    {
        VecFx32Ctor a(v->x, 0, o->z);
        GroundInfo g;
        g.initAtPos((VecFx32 *)(&a), 0, 0);
        if (g.getHeight(0) > 0x200) {
            far = TRUE;
        } else {
            far = FALSE;
        }
    }
    if (far) {
        o->z = v->z;
        r = FALSE;
    }
    return r;
}

extern "C" u8 MuseumInsect_ClampToBounds(void *o_, void *v_) {
    MuseumInsect *o = (MuseumInsect *)o_;
    V3_d800 *v = (V3_d800 *)v_;
    u8 r;
    s32 *q;
    s32 *p;
    q = &o->boundsMax.x;
    p = &o->boundsMin.x;
    r = 0;
    if (v->x < o->boundsMin.x) {
        v->x = o->boundsMin.x;
        r = 1;
    } else if (v->x > q[0]) {
        v->x = q[0];
        r |= 2;
    }
    if (v->z < p[1]) {
        v->z = p[1];
        r |= 4;
    } else if (v->z > q[1]) {
        v->z = q[1];
        r |= 8;
    }
    return r;
}

extern "C" void MuseumInsect_ApproachHome(void *self_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    if (MuseumInsect_TickTimer(self) != 0) {
        VecFx32 *r4 = &self->position;
        s16 a;
        s32 b;
        VecFx32 c;
        MuseumInsect_GetHomeDelta(self, &a, &b, &c);
        if (b <= 0x400 && r4->y <= c.y + 0x200 && r4->y >= c.y - 0x200) {
            self->moveState = 6;
            self->stateTimer = (s16)((Random_GlobalBelow(10) + 10) * 20);
            self->stateCounter = 0;
        } else {
            s32 r6 = self->wanderThreshold;
            if (Random_GlobalBelow(100) > r6 - 0x14) {
                if (b <= 0x3000) {
                    self->targetHeight = c.y;
                } else {
                    self->targetHeight = self->baseHeight;
                }
                self->yaw = a + self->yaw;
                VEC_Subtract(&c, r4, &c);
                MuseumInsect_ClampStep(&c, &c, 1);
                VEC_Add(r4, &c, r4);
            }
        }
    } else {
        self->targetHeight = self->baseHeight;
    }
}

extern "C" void MuseumInsect_StateRest(void *self_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    u8 st = (u8)self->insectIndex;
    MuseumInsect_CheckScared(self);
    if (MuseumInsect_TickTimer(self) == 0 || self->isActive == 0) {
        if (self->isAlerted == 0) {
            if (st == 0xa || st == 0x33) {
                if (((Unk_ov004_0223b1e8_Bits &)self->model.curFrame).mid != 0) {
                    ((AnimModel *)(&self->model))->setFrame(0);
                }
            } else if (((Unk_ov004_0223b1e8_Bits &)self->model.numFrames).mid < 0xc) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(0x11, 1, 0x1000, 9);
            } else if (((Unk_ov004_0223b1e8_Bits &)self->model.curFrame).mid == 0x10) {
                if (self->isActive != 0 || sMuseumInsectFrame % 10 == 0) {
                    if (Random_GlobalBelow(100) > 0x5f) {
                        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(0x11, 1, 0x1000, 9);
                    }
                }
            }
            return;
        }
    }
    self->moveState = 0x19;
    self->targetHeight = self->baseHeight;
    self->stateTimer = (Random_GlobalBelow(10) + 0x10) * 20;
    if (st != 0xa && st != 0x33) {
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(9, 0, self->flyAnimSpeed, 0);
    } else {
        ((AnimModel *)(&self->model))->setFrame(1);
    }
}

extern "C" s32 MuseumInsect_TickTimer(void *self_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    s32 t = (s16)self->stateTimer;
    if (t > 0) {
        self->stateTimer = t - 1;
        return 0;
    }
    return 1;
}

extern "C" BOOL MuseumInsect_PlaySe(void *self_, s32 b) {
    MuseumInsect *self = (MuseumInsect *)self_;
    s32 id = MuseumInsect_GetSe(self->insectIndex, b);
    if (id >= 0) {
        if (b == 1) {
            ((SndEnvChannel *)(&self->sound))->callRequestSustained(id);
        } else {
            ((SndEnvChannel *)(&self->sound))->callRequest(id);
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 MuseumInsect_GetSe(s32 a, s32 b) {
    switch (a) {
    case 0xa: return 0x831;
    case 0x33: return 0x823;
    case 0x1d: return 0x825;
    case 0x1b: return 0x826;
    case 0x1c: return 0x82c;
    case 0x10: return 0x822;
    case 0x11: return 0x827;
    case 0x12: return 0x82e;
    case 0x13: return 0x824;
    case 0x32: return 0x828;
    case 0x1e:
        if (b == 0) return 0x829;
        return 0x82a;
    case 0x36: return 0x833;
    case 0x37: return 0x835;
    case 0x34:
        switch (b) {
        case 0: return 0x1d2;
        case 1: return 0x1d3;
        }
        break;
    }
    return -1;
}

extern "C" void MuseumInsect_Wander(void *self_, s32 a, s32 b, u32 c) {
    MuseumInsect *self = (MuseumInsect *)self_;
    s32 r6 = self->yaw;
    u8 r7 = self->sideDir;
    u32 rnd = (u8)Random_GlobalBelow(100);
    VecFx32 *v = &self->position;
    VecFx32 o;
    if (DS_MOD(sMuseumInsectFrame, b) == 0 && rnd > c) {
        if (r7 == 0) {
            r7 = 1;
        } else {
            r7 = 0;
        }
        self->sideDir = r7;
    }
    if (rnd > self->wanderThreshold) {
        if (r7 != 0) {
            r6 = (s16)(r6 + a);
        } else {
            r6 = (s16)(r6 - a);
        }
    }
    MuseumInsect_MakeStepDir(&o, r6);
    self->yaw = r6;
    if (self->isAlerted != 0) {
        v->x = v->x + func_01ffcb0c(func_01ffcb0c(0x1800, self->moveSpeed << 12), o.x);
        v->z = v->z + func_01ffcb0c(func_01ffcb0c(0x1800, self->moveSpeed << 12), o.z);
    } else {
        v->x = v->x + func_01ffcb0c(self->moveSpeed << 12, o.x);
        v->z = v->z + func_01ffcb0c(self->moveSpeed << 12, o.z);
    }
}

extern "C" void MuseumInsect_BobHeight(void *self_, u32 a, s32 b, s32 c) {
    MuseumInsect *self = (MuseumInsect *)self_;
    s32 r5;
    VecFx32 *v = &self->position;
    s32 idx = ((u16)a >> 4) * 2;
    r5 = FX_Div(data_02135f44[idx], c);
    s32 r7 = b;
    if (self->targetHeight != self->baseHeight) {
        r7 = func_01ffcb0c(r7, 0x800);
    }
    if (r5 > 0 && v->y + r5 < r7 + self->targetHeight || r5 < 0 && v->y + r5 > self->targetHeight - r7) {
        v->y = v->y + r5;
    }
}

extern "C" s32 MuseumInsect_CheckScared(void *self_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    MuseumInsectPlayerInfo rec;
    s32 r = MuseumInsect_UpdateAlertLevel(self, &rec);
    if (rec.hasPlayer != 0 && self->isAlerted == 0 && self->alertLevel >= self->alertThreshold) {
        self->targetAngle = Math_AngleXZ(&rec.playerPos, &self->position);
        self->stateTimer = (Random_GlobalBelow(4) + 10) * 20;
        self->moveState = 7;
        self->isAlerted = 1;
        self->targetHeight = self->baseHeight;
    }
    return r;
}

extern "C" void MuseumInsect_GetHomeDelta(MuseumInsect *self, s16 *a, s32 *b, VecFx32 *c) {
    VecFx32 *p6 = &self->position;
    VecFx32 *pv = &self->homePos;
    c->x = pv->x;
    c->y = pv->y;
    c->z = pv->z;
    s32 r7 = self->yaw;
    *a = Math_AngleXZ(p6, c) - r7;
    s16 t = *a;
    if (t > 0x38e) {
        *a = 0x38e;
    } else if (t < -0x38e) {
        *a = -0x38e;
    }
    *b = Vec_DistXZ(c, p6);
}

extern "C" s32 MuseumInsect_GetEscapeHeading(s32 a, s32 b) {
    s32 orig = a;
    u32 r = (u8)Random_GlobalBelow(100);
    if (b == 3) {
        a = (s16)(a + 0x8000);
        if (r < 5) {
            a = (s16)(a + 0x2aaa);
        } else if (r < 10) {
            a = (s16)(a - 0x2aaa);
        }
    } else {
        if (b == 1 && (a < -0x4000 || (a >= 0 && a < 0x4000)) || b == 2 && (a > 0x4000 || (a <= 0 && a > -0x4000))) {
            a = (s16)(-a);
        } else if (a >= 0) {
            a = (s16)(0x8000 - a);
        } else {
            a = (s16)(-0x8000 - a);
        }
    }
    if (r > 0x50) {
        if (a - orig >= 0) {
            a = (s16)(a + 0x1554);
        } else {
            a = (s16)(a - 0x1554);
        }
    }
    if (a == orig) {
        if (a >= 0) {
            a = (s16)(a + 0xaaa);
        } else {
            a = (s16)(a - 0xaaa);
        }
    }
    return a;
}

extern "C" void MuseumInsect_TurnToTarget(void *self_, u32 a, s32 b) {
    MuseumInsect *self = (MuseumInsect *)self_;
    s16 sv[2];
    sv[0] = self->yaw;
    if (Math_StepAngle(sv, self->targetAngle, 0xe38) != 0) {
        self->moveState = b;
        self->dirFlag = a;
    }
    self->yaw = sv[0];
}

extern "C" s32 MuseumInsect_TickAlert(void *self_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    MuseumInsectPlayerInfo rec;
    return MuseumInsect_UpdateAlertLevel(self, &rec);
}

extern "C" s32 MuseumInsect_UpdateAlertLevel(void *self_, void *out_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    MuseumInsectPlayerInfo *out = (MuseumInsectPlayerInfo *)out_;
    volatile s32 old;
    s16 r4 = self->alertLevel;
    old = r4;
    s32 r7 = self->alertThreshold;
    Actor *p = (Actor *)PlayerActor_GetActor(4);
    if (p != 0) {
        out->hasPlayer = 1;
        out->playerSpeed = p->speed;
        VecFx32 *pv = &p->position;
        out->playerPos.x = pv->x;
        out->playerPos.y = pv->y;
        out->playerPos.z = pv->z;
        out->playerDist = Vec_DistXZ(&self->position, &out->playerPos);
        s32 t = out->playerDist;
        if (t < 0x2000) {
            r4 += 0x19;
        } else if (t > self->alertRange || out->playerSpeed == 0) {
            r4 -= 1;
        } else if (out->playerSpeed <= 0x3e8) {
            r4 += 1;
        } else if (out->playerSpeed <= 0x44c) {
            r4 = r4 + 3;
        } else if (out->playerSpeed <= 0x490) {
            r4 = r4 + 5;
        } else if (out->playerSpeed == 0x491) {
            r4 = r4 + 8;
        } else {
            r4 += 0xf;
        }
        if (r4 < 0) {
            r4 = 0;
        } else if (r4 > 0xff) {
            r4 = 0xff;
        }
        self->alertLevel = (u8)r4;
        if (r7 <= r4) {
            if (r7 > old) {
                return 1;
            }
            return 3;
        } else if (r7 > r4 && r7 <= old) {
            return 2;
        }
    } else {
        out->hasPlayer = 0;
        return -1;
    }
    return 0;
}

extern "C" void MuseumInsect_RunButterfly(void *self_) {
    MuseumInsect *self = (MuseumInsect *)self_;
    switch (self->moveState) {
    case 0:
        MuseumInsect_ButterflyFly(self);
        break;
    case 6:
        MuseumInsect_StateRest(self);
        break;
    default:
        self->isAlerted = 0;
        self->moveState = 0;
        self->alertLevel = 0;
        break;
    }
}

extern "C" void MuseumInsect_ButterflyFly(MuseumInsect *self) {
    VecFx32 *v = &self->position;
    s16 *pa = &self->stateCounter;
    s32 t = *pa;
    t = t * (0x44 - t * 5);
    AnimModel *sb = &self->model;
    if (((Unk_ov004_0223b1e8_Bits &)sb->numFrames).mid > 9) {
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*sb))->setup(9, 0, self->flyAnimSpeed, 0);
    }
    if (self->dirFlag != 0 && t >= 0) {
        t = func_01ffcb0c(t, 0x2000);
    } else if (t < -0x333) {
        t = -0x333;
    }
    v->y += t;
    MuseumInsect_ButterflyFlapHeight(self, pa);
    *pa = *pa + 4;
    MuseumInsect_ApproachHome(self);
    MuseumInsect_Wander(self, 0xaaa, 0x14, 0x3c);
}

extern "C" void MuseumInsect_ButterflyFlapHeight(MuseumInsect *self, s16 *p) {
    s32 hi = 0x300;
    s32 a = self->baseHeight;
    u8 flag = self->dirFlag;
    VecFx32 *v = &self->position;
    s32 b = self->targetHeight;
    if (a != b) {
        a = b;
    }
    hi += a;
    if (self->flapPeriod < *p) {
        *p = 0;
        if (flag != 0) {
            *p = 0;
            self->flapPeriod = 0x10;
        } else {
            *p = 8;
            self->flapPeriod = 0x14;
        }
    }
    if (flag != 0 && v->y > hi) {
        self->dirFlag = 0;
    } else {
        s32 y = v->y;
        if (y < a) {
            if (y > a - 0x320) {
                v->y = a;
            }
            self->dirFlag = 1;
        }
    }
}

extern "C" void MuseumInsect_RunDragonfly(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    u8 st = (u8)o->moveState;
    if (st != 0x19) {
        MuseumInsect_FlapWings(o);
    }
    switch (st) {
    case 19:
        MuseumInsect_TurnToTarget(o, 0, 5);
        break;
    case 3:
    case 15:
        MuseumInsect_TurnToTarget(o, 0, 4);
        break;
    case 4:
        if (MuseumInsect_TickTimer(o) != 0 && MuseumInsect_DragonflyPickPerch(o) < 0x5000) {
            o->targetAngle = Math_AngleXZ(&o->position, &o->homePos);
            o->moveState = 14;
            if (o->insectIndex != 0x17) {
                o->stateCounter = (Random_GlobalBelow(5) + 2) * 10;
            }
        } else {
            MuseumInsect_DragonflyFlyTo(o);
        }
        MuseumInsect_DragonflyAvoidWall(o);
        break;
    case 5:
        MuseumInsect_DragonflyLand(o);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
        MuseumInsect_DragonflyHover(o);
        break;
    case 7: {
        s32 a, rn;
        o->moveState = 15;
        o->alertLevel = 0;
        o->stateTimer = 0xa0;
        o->isAlerted = 0;
        o->isPerched = 0;
        a = o->targetAngle;
        rn = Random_GlobalBelow(3);
        MuseumInsect_PointAtAngle(&o->targetPos, &o->position, a, (o->travelDistance + rn) << 12);
        o->targetAngle = Math_AngleXZ(&o->position, &o->targetPos);
        break;
    }
    case 0:
    case 1:
    case 2:
    case 6:
    case 8:
    case 9:
    case 10:
    case 16:
    case 17:
    case 18:
    default:
        if (o->isBumped != 0) {
            o->moveState = 7;
        } else if (o->isPerched != 0) {
            if (sMuseumInsectFrame % 20 == 0) {
                u32 r = (u8)Random_GlobalBelow(100);
                if (((Unk_ov004_0223b1e8_Bits &)o->model.curFrame).mid == 0 && r > 0x5c) {
                    ((AnimModel *)(&o->model))->setFrame(2);
                } else if (r > 0x32) {
                    ((AnimModel *)(&o->model))->setFrame(0);
                }
            } else if (((Unk_ov004_0223b1e8_Bits &)o->model.curFrame).mid != 0) {
                MuseumInsect_FlapWings(o);
            }
            MuseumInsect_CheckScared(o);
            if (o->isActive != 0 && MuseumInsect_TickTimer(o) != 0) {
                o->isPerched = 0;
                o->moveState = 11;
                o->stateTimer = 0xa0;
                if (o->insectIndex == 0x17) {
                    o->stateCounter = 0;
                } else {
                    o->stateCounter = (Random_GlobalBelow(5) + 2) * 10;
                }
            }
        } else {
            o->moveState = 11;
            if (o->insectIndex == 0x17) {
                o->stateCounter = 0;
            } else {
                o->stateCounter = (Random_GlobalBelow(5) + 2) * 10;
            }
        }
        break;
    }
    o->isBumped = 0;
}

extern "C" void MuseumInsect_DragonflyLand(MuseumInsect *o)
{
    VecFx32 *r4 = &o->position;
    VecFx32 *r6 = &o->homePos;
    s32 a, b;
    switch (o->insectIndex) {
    case 0x15:
        a = 0x148;
        b = 0x40;
        break;
    case 0x16:
        a = 0x19a;
        b = 0x49;
        break;
    default:
        a = 0x19a;
        b = 0x4e;
        break;
    }
    if (!Math_ApproachVec(r4, r6, b, 0x1000, a)) {
        o->moveState = 25;
        o->stateTimer = (Random_GlobalBelow(5) + 5) * 20;
        o->isPerched = 1;
    } else {
        o->yaw = Math_AngleXZ(r4, r6);
    }
}

extern "C" void MuseumInsect_DragonflyHover(MuseumInsect *o)
{
    s16 *r6 = &o->stateCounter;
    VecFx32 *r4 = &o->position;
    if (*r6 <= 0) {
        s16 t = o->moveState;
        if ((u16)(s16)(t - 12) <= 1) {
            o->moveState = 15;
        } else if (t == 14) {
            o->moveState = 19;
        } else {
            s32 a, rn;
            if (o->insectIndex == 0x17) {
                s32 t = o->yaw;
                a = MuseumInsect_RandTurn(4);
                a += t;
                o->targetAngle = a;
            } else {
                s32 t = o->yaw;
                a = MuseumInsect_RandTurn(12);
                a += t;
                o->targetAngle = a;
            }
            o->moveState = 3;
            a = o->targetAngle;
            rn = Random_GlobalBelow(3);
            MuseumInsect_PointAtAngle(&o->targetPos, r4, a, (o->travelDistance + rn) << 12);
            o->targetAngle = Math_AngleXZ(&o->position, &o->targetPos);
        }
    } else {
        if (*r6 % 10 < 5) {
            s32 y = r4->y;
            if (y < o->baseHeight + 0x800) {
                r4->y = y + 0x80;
            }
        } else {
            s32 y = r4->y;
            if (y > o->baseHeight - 0x1000) {
                r4->y = y - 0x80;
            }
        }
        *r6 = *r6 - 1;
    }
}

extern "C" void MuseumInsect_DragonflyFlyTo(MuseumInsect *o)
{
    VecFx32 *r7 = &o->targetPos;
    VecFx32 *r4 = &o->position;
    s32 r6 = o->moveSpeed;
    if (!Math_ApproachVecXZ(r4, r7, r6, 0x1000, o->speciesWork)) {
        o->moveState = 25;
    } else {
        o->yaw = Math_AngleXZ(r4, r7);
    }
    if (o->dirFlag) {
        Math_ApproachS32(&r4->y, o->baseHeight, r6, 0x1000, 0xcd);
    } else {
        if (!Math_ApproachS32(&r4->y, o->baseHeight - 0x1000, r6, 0x1000, 0xcd)) {
            o->dirFlag = 1;
        }
    }
}

extern "C" void MuseumInsect_DragonflyAvoidWall(MuseumInsect *o)
{
    s32 r = MuseumInsect_CheckWallsAhead(o);
    if (r != 0) {
        s32 t, rn;
        o->targetAngle = MuseumInsect_GetEscapeHeading(o->yaw, r);
        t = o->targetAngle;
        rn = Random_GlobalBelow(3);
        MuseumInsect_PointAtAngle(&o->targetPos, &o->position, t, (o->travelDistance + rn) << 12);
        o->targetAngle = Math_AngleXZ(&o->position, &o->targetPos);
        if (o->isAlerted != 0) {
            o->moveState = 15;
        } else {
            o->moveState = 12;
            if (o->insectIndex == 0x17) {
                o->stateCounter = 0;
            } else {
                o->stateCounter = (Random_GlobalBelow(5) + 2) * 10;
            }
        }
    }
}

extern "C" s32 MuseumInsect_DragonflyPickPerch(MuseumInsect *o)
{
    V3z_c8d4 a, b;
    VecFx32 *p;
    s32 r5, r4, r3, r2, s0, s4;
    s32 d1, d2;
    p = &o->position;
    switch (o->insectIndex) {
    case 0x15:
        r5 = 0x16c00;
        s0 = 0x1400;
        r4 = 0xd200;
        r3 = 0x1a600;
        s4 = 0x1400;
        r2 = 0x13c00;
        break;
    case 0x16:
        r5 = 0x13200;
        s0 = 0x1400;
        r4 = 0x10d00;
        r3 = 0x16600;
        s4 = 0x1400;
        r2 = 0x14200;
        break;
    default:
        r5 = 0x17800;
        s0 = 0x1400;
        r4 = 0x12200;
        r3 = 0x12b00;
        s4 = 0x1a00;
        r2 = 0xda00;
        break;
    }
    d1 = Abs_c8d4(p->x - r5) + Abs_c8d4(p->z - r4);
    d2 = Abs_c8d4(p->x - r3) + Abs_c8d4(p->z - r2);
    if (d1 < d2) {
        VecFx32 *q = &o->homePos;
        q->x = r5;
        q->y = s0;
        q->z = r4;
        return d1;
    }
    {
        VecFx32 *q = &o->homePos;
        q->x = r3;
        q->y = s4;
        q->z = r2;
    }
    return d2;
}

extern "C" void MuseumInsect_RunHopper(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    switch (o->moveState) {
    case 3:
    case 15:
        MuseumInsect_TurnToTarget(o, 1, 4);
        break;
    case 4:
        MuseumInsect_HopperHop(o);
        break;
    default: {
        s16 *r4 = &o->stateCounter;
        s16 *r6;
        if (o->isActive) {
            MuseumInsect_HopperChirp(o);
        }
        if (MuseumInsect_HopperAvoidWall(o, r4) != 0) {
            break;
        }
        r6 = &o->subCounter;
        if (MuseumInsect_TickAlert(o) == 1) {
            *r4 = *r6 * 5;
        } else if (o->isActive == 0 && *r4 == 0) {
            *r6 = *r6 * 5;
        }
        *r4 = *r4 + 1;
        if (*r4 >= *r6 || o->isBumped != 0) {
            s32 a, rn;
            s32 t = o->yaw;
            a = MuseumInsect_RandTurn(12);
            a += t;
            o->targetAngle = a;
            a = o->targetAngle;
            rn = Random_GlobalBelow(3);
            MuseumInsect_PointAtAngle(&o->targetPos, &o->position, a, (o->travelDistance + rn) << 12);
            o->targetAngle = Math_AngleXZ(&o->position, &o->targetPos);
            o->moveState = 3;
            *r4 = 0;
            o->alertLevel = 0;
        }
        break;
    }
    }
    o->isBumped = 0;
}

extern "C" void MuseumInsect_HopperHop(MuseumInsect *o)
{
    VecFx32 *r6 = &o->targetPos;
    VecFx32 *r4 = &o->position;
    volatile VecFx32 sv;
    s32 t;
    s32 r7;
    sv.x = r4->x;
    sv.y = r4->y;
    sv.z = r4->z;
    r7 = o->moveSpeed;
    if (MuseumInsect_CheckFloorAhead(o) == 0 || o->isBumped != 0) {
        if (Math_ApproachVecXZ(r4, r6, r7, 0x1000, 0x333)) {
            if (MuseumInsect_ClampToBounds(o, r4)) {
                r4->x = sv.x;
                r4->y = sv.y;
                r4->z = sv.z;
                *r6 = *r4;
            } else {
                o->yaw = Math_AngleXZ(r4, r6);
            }
        }
    } else {
        *r6 = *r4;
    }
    if (o->dirFlag) {
        if (!Math_ApproachS32(&r4->y, 0x1400, r7, 0x1000, 0xcd)) {
            o->dirFlag = 0;
        }
    } else {
        {
            GroundInfo loc;
            loc.initAtPos((VecFx32 *)(r4), 0, 1);
            t = loc.getHeight(0);
        }
        if (!Math_ApproachS32(&r4->y, t, r7, 0x1000, 0x266)) {
            o->subCounter = (Random_GlobalBelow(9) + 2) * 20;
            o->moveState = 25;
            ((AnimModel *)(&o->model))->setFrame(0);
            *r6 = *r4;
            if (o->isAlerted != 0) {
                o->alertLevel = (u8)(o->alertThreshold - 10);
                o->isAlerted = 0;
            }
        }
    }
}

extern "C" s32 MuseumInsect_HopperAvoidWall(MuseumInsect *o, s16 *p)
{
    s32 r = MuseumInsect_CheckFloorAhead(o);
    if (r != 0) {
        s32 t, rn;
        o->targetAngle = MuseumInsect_GetEscapeHeading(o->yaw, r);
        t = o->targetAngle;
        rn = Random_GlobalBelow(3);
        MuseumInsect_PointAtAngle(&o->targetPos, &o->position, t, (o->travelDistance + rn) << 12);
        o->targetAngle = Math_AngleXZ(&o->position, &o->targetPos);
        o->moveState = 15;
        o->speciesWork++;
        *p = 0;
    }
    return r;
}

extern "C" void MuseumInsect_HopperChirp(MuseumInsect *o)
{
    switch (o->insectIndex) {
    case 0x1b:
    case 0x1c:
    case 0x1d:
        if (o->alertLevel < 5) {
            MuseumInsect_PlaySe(o, 0);
        }
        break;
    }
}

extern "C" void MuseumInsect_RunPondSkater(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    switch (o->moveState) {
    case 3:
    case 15:
        MuseumInsect_PondSkaterStartGlide(o, &o->stateCounter);
        break;
    case 4:
        MuseumInsect_PondSkaterGlide(o, &o->stateCounter);
        break;
    default: {
        s16 *p = &o->subCounter;
        if (*p <= 0) {
            o->moveState = 3;
        } else {
            *p = *p - 1;
        }
        o->isAlerted = 0;
        break;
    }
    }
}

extern "C" void MuseumInsect_PondSkaterStartGlide(MuseumInsect *o, s16 *p)
{
    s16 a, t;
    s16 r4;
    t = o->yaw;
    a = t;
    r4 = 0;
    if (o->moveState == 15) {
        r4 = (s16)(t + o->targetAngle);
        o->moveState = 4;
    } else {
        u8 n = (u8)Random_GlobalBelow(5);
        u8 i;
        for (i = 0; i < n; i++) {
            r4 = (s16)(r4 + 0xaaa);
        }
        if (Random_GlobalBelow(100) > 50) {
            r4 = (s16)-r4;
        }
        r4 += a;
        o->moveState = 4;
    }
    if (o->moveState == 4) {
        VecFx32 v;
        o->yaw = r4;
        *p = Random_GlobalBelow(8) + 8;
        VecFx32 *sp_ = &o->position;
        v.x = sp_->x;
        v.y = sp_->y;
        v.z = sp_->z;
        a = 0;
        Effect_PlayById2(0x1f, &v, &a, 0);
    }
}

extern "C" void MuseumInsect_PondSkaterGlide(void *self_, s16 *p)
{
    MuseumInsect *self = (MuseumInsect *)self_;
    VecFx32 d;
    volatile VecFx32 saved;
    VecFx32 *v = &self->position;
    saved.x = v->x;
    saved.y = v->y;
    saved.z = v->z;
    s32 *hi = &self->boundsMax.x;
    s32 *lo = &self->boundsMin.x;
    MuseumInsect_MakeStepDir(&d, self->yaw);
    self->position.x += func_01ffcb0c((*p * self->moveSpeed) << 12, d.x);
    v->z += func_01ffcb0c((*p * self->moveSpeed) << 12, d.z);
    v->y = 0x200;
    *p = *p - 1;
    if (self->position.x < self->boundsMin.x || self->position.x > hi[0] || v->z < lo[1] || v->z > hi[1]) {
        s32 base = -0x8000;
        v->x = saved.x;
        v->y = saved.y;
        v->z = saved.z;
        base += MuseumInsect_RandTurn8(8);
        self->targetAngle = base;
        self->moveState = 15;
        *p = 0;
    } else if (*p <= 0) {
        self->moveState = 25;
        if (self->isActive != 0) {
            self->subCounter = Random_GlobalBelow(60);
        } else {
            self->subCounter = Random_GlobalBelow(0x12c);
        }
    }
}

extern "C" s32 MuseumInsect_RandTurn8(s32 n)
{
    s32 r;
    switch (Random_GlobalBelow(n)) {
    case 0:
        r = 0xaaa;
        break;
    case 1:
        r = 0x1554;
        break;
    case 2:
        r = 0x2000;
        break;
    case 3:
        r = 0x2aaa;
        break;
    case 4:
        r = -0xaaa;
        break;
    case 5:
        r = -0x1554;
        break;
    case 6:
        r = -0x2000;
        break;
    default:
        r = -0x2aaa;
        break;
    }
    return r;
}

extern "C" void MuseumInsect_RunMosquito(void *self_)
{
    MuseumInsect *self = (MuseumInsect *)self_;
    MuseumInsect_FlapWings(self);
    MuseumInsect_PlaySe(self, 0);
    if (self->moveState == 0) {
        MuseumInsect_MosquitoChase(self, &self->stateCounter);
    } else {
        self->moveState = 0;
    }
}

extern "C" void MuseumInsect_MosquitoChase(MuseumInsect *self, s16 *p)
{
    Actor *b;
    struct {
        s16 t;
        s16 pad;
    } l;
    VecFx32 d;
    b = (Actor *)PlayerActor_GetActor(4);
    if (b != 0) {
        VecFx32 *v = &self->position;
        s32 dist;
        VecFx32 *pb = &b->position;
        dist = Vec_DistXZ(pb, v);
        l.t = self->yaw;
        Math_StepAngle(&l.t, Math_AngleXZ(v, pb), 0x38e);
        *p = *p + 0xaaa;
        if (self->isAlerted != 0) {
            s32 c = self->alertLevel;
            if (dist > 0x3000) {
                self->isAlerted = 0;
            } else if (c < 60) {
                self->alertLevel = (u8)(s16)(c + 1);
            } else if (self->hasBitten == 0 && dist < 0x1000 && PlayerActor_RequestAct79() != 0) {
                self->isAlerted = 0;
                self->moveState = 0;
                self->hasBitten = 1;
                *p = 0;
            }
        }
        if (dist < 0x2000) {
            if (dist < 0x1000 && self->isAlerted == 0) {
                self->isAlerted = 1;
                self->alertLevel = 0;
            }
            if (Random_GlobalBelow(100) > 30) {
                if (l.t > 0) {
                    l.t += 0x5b0;
                } else if (l.t < 0) {
                    l.t -= 0x5b0;
                }
            }
        }
        self->yaw = l.t;
        MuseumInsect_MakeStepDir(&d, l.t);
        v->x += func_01ffcb0c(d.x, 0x8000);
        v->z += func_01ffcb0c(d.z, 0x8000);
        MuseumInsect_BobHeight(self, *p, 0x2800, (Random_GlobalBelow(4) + 0x12) << 12);
    }
}

extern "C" void MuseumInsect_RunFirefly(void *self_)
{
    MuseumInsect *self = (MuseumInsect *)self_;
    if (self->isActive == 0) {
        ((MuseumInsect *)(self))->runPerched();
    } else if (self->moveState == 0) {
        MuseumInsect_FireflyWander(self);
        MuseumInsect_ClampToBounds(self, &self->position);
    } else {
        self->isAlerted = 0;
        self->moveState = 0;
    }
}

extern "C" void MuseumInsect_FireflyWander(MuseumInsect *self)
{
    MuseumInsect_Wander(self, 0x38e, 0x28, 0x50);
    s32 r = Random_GlobalBelow(4);
    self->stateCounter = self->stateCounter + (s16)FX_Div(0x2000, (r + 5) << 12);
    MuseumInsect_BobHeight(self, self->stateCounter, 0x1000, (Random_GlobalBelow(4) + 10) << 12);
}

extern "C" void MuseumInsect_RunFlyingInsect(void *self_)
{
    MuseumInsect *self = (MuseumInsect *)self_;
    switch (self->moveState) {
    case 0:
        MuseumInsect_PlaySe(self, 0);
        MuseumInsect_FlyingInsectFly(self);
        break;
    case 6:
        if (self->insectIndex == 10) {
            ((MuseumInsect *)(self))->wander();
        }
        MuseumInsect_StateRest(self);
        break;
    case 7:
        self->moveState = 0;
        if (self->isAlerted != 0) {
            self->yaw = self->yaw + self->targetAngle;
        }
        break;
    default:
        self->isAlerted = 0;
        self->moveState = 0;
        if (self->insectIndex == 0x33) {
            VecFx32 *p = &self->homePos;
            if (Random_GlobalBelow(100) > 50) {
                p->x = 0xef00;
                p->z = 0xc900;
            } else {
                p->x = 0xf700;
                p->z = 0x15200;
            }
            p->y = 0x1300;
        }
        break;
    }
}

extern "C" void MuseumInsect_FlyingInsectFly(MuseumInsect *self)
{
    s16 *q = &self->subCounter;
    MuseumInsect_FlapWings(self);
    if (MuseumInsect_CheckScared(self) == 2) {
        self->isAlerted = 0;
    }
    if (self->isAlerted != 0) {
        MuseumInsect_Wander(self, 0xaaa, 10, 0x46);
    } else {
        MuseumInsect_ApproachHome(self);
        MuseumInsect_Wander(self, 0xaaa, 20, 0x50);
    }
    if (self->insectIndex == 0x33) {
        MuseumInsect_BobHeight(self, *q, 0x19a, (Random_GlobalBelow(8) + 0x12) << 12);
        *q = *q + 0x1554;
    } else {
        MuseumInsect_BobHeight(self, *q, 0x1200, (Random_GlobalBelow(8) + 10) << 12);
        *q = *q + 0xaaa;
    }
}

extern "C" void MuseumInsect_RunFlea(void *self_)
{
    MuseumInsect *self = (MuseumInsect *)self_;
    if (self->moveState == 4) {
        MuseumInsect_FleaJump(self);
    } else if (MuseumInsect_TickTimer(self) != 0) {
        Actor *p = (Actor *)PlayerActor_GetActor(4);
        if (p != 0) {
            u8 r = Random_GlobalBelow(0x21) + 0x10;
            VecFx32 *v = &self->position;
            VecFx32 *pp = &p->position;
            if (Vec_DistXZ(pp, v) > 0x6000) {
                r += 0x10;
            }
            self->yaw = Math_AngleXZ(v, pp);
            s32 ang = self->yaw;
            MuseumInsect_PointAtAngle(&self->targetPos, v, ang, func_01ffcb0c(r << 12, 0x100));
            self->subCounter = 1;
            self->moveState = 4;
        }
    }
}

extern "C" void MuseumInsect_FleaJump(MuseumInsect *self)
{
    s16 *q = &self->subCounter;
    VecFx32 *v = &self->position;
    VecFx32 saved;
    saved.x = v->x;
    saved.y = v->y;
    saved.z = v->z;
    Math_ApproachVecXZ(v, &self->targetPos, 0xaa, 0x1000, 0x333);
    if (self->subCounter > 0) {
        s32 k = self->subCounter << 12;
        v->y = func_01ffcb0c(0x99a - func_01ffcb0c(0x7b, k), k);
        if (v->y < 0) {
            Actor *p = (Actor *)PlayerActor_GetActor(4);
            s32 n = 20;
            if (p != 0) {
                if (Vec_DistXZ(&p->position, v) > 0x6000) {
                    n = 0;
                }
            }
            self->stateTimer = (s16)(Random_GlobalBelow(n * 2 + 20) + 20) >> 1;
            self->moveState = 25;
            *q = 0;
        } else {
            *q = *q + 1;
        }
    }
    MuseumInsect_RevertIfOffFloor(v, &saved);
}

extern "C" void MuseumInsect_RunMoleCricket(void *self_)
{
    MuseumInsect *self = (MuseumInsect *)self_;
    switch (self->moveState) {
    case 4:
        MuseumInsect_PlaySe(self, 2);
        MuseumInsect_MoleCricketCrawl(self, &self->stateCounter);
        break;
    case 5:
        MuseumInsect_MoleCricketJump(self, &self->stateCounter);
        break;
    case 3: {
        s16 t = self->yaw;
        if (Math_StepAngle(&t, self->targetAngle, 0x38e) != 0) {
            self->moveState = 4;
        }
        MuseumInsect_PlaySe(self, 2);
        self->yaw = t;
        break;
    }
    case 16:
        if (MuseumInsect_TickTimer(self) != 0) {
            self->moveState = 25;
            VecFx32 *sp = &self->targetPos;
            VecFx32 *dp = &self->position;
            dp->x = self->targetPos.x;
            dp->y = sp->y;
            dp->z = sp->z;
        }
        break;
    default:
        MuseumInsect_MoleCricketCheckEmerge(self);
        break;
    }
}

extern "C" void MuseumInsect_MoleCricketCheckEmerge(MuseumInsect *self)
{
    u32 idx;
    s32 c;
    VecFx32 *v;
    MuseumInsectPlayerInfo o;
    v = &self->position;
    idx = (u8)self->alertLevel;
    MuseumInsect_UpdateAlertLevel(self, &o);
    if (o.hasPlayer != 0) {
        if (o.playerDist < 0x5000) {
            self->cooldown = 60;
        }
        c = self->cooldown;
        if (c > 0) {
            MuseumInsect_PlaySe(self, 0);
            self->cooldown = c - 1;
        }
        if ((s32)idx > self->alertThreshold) {
            self->moveState = 5;
            EffectSpl_CreateOneShot(0x80, v, NULL, gEffectSplDefaultInitCbs);
            self->subCounter = (Random_GlobalBelow(11) + 5) * 20;
            self->yaw = Math_AngleXZ(&o.playerPos, v);
            NNS_G3dMdlSetMdlAlpha(self->pooledModel.getModel(), 0, 31);
            VecFx32 *sp = &self->position;
            VecFx32 *dp = &self->targetPos;
            self->targetPos.x = sp->x;
            dp->y = sp->y;
            dp->z = sp->z;
        }
    }
}

extern "C" void MuseumInsect_MoleCricketJump(MuseumInsect *self, s16 *p)
{
    VecFx32 *v = &self->position;
    s32 k = (self->moveSpeed + 2) << 12;
    VecFx32 d;
    MuseumInsect_MakeStepDir(&d, self->yaw);
    self->position.x += func_01ffcb0c(k, d.x);
    v->z += func_01ffcb0c(k, d.z);
    v->y += (25 - *p) * (*p * 4);
    BOOL ok;
    {
        GroundInfo g;
        g.initAtPos((VecFx32 *)(v), 0, 1);
        if (v->y > g.getHeight(0)) {
            ok = FALSE;
        } else {
            ok = TRUE;
        }
    }
    if (ok && *p > 0) {
        self->moveState = 4;
        self->alertLevel = 0;
        *p = 0;
        self->pitch = 0;
    } else {
        *p = *p + 2;
    }
}

extern "C" void MuseumInsect_MoleCricketCrawl(MuseumInsect *self, s16 *p)
{
    s16 *q = &self->subCounter;
    if (self->subCounter > 0) {
        *q = self->subCounter - 1;
        ((MuseumInsect *)(self))->crawl();
        MuseumInsect_ClampToBounds(self, &self->position);
        if (*q > 5) {
            if (sMuseumInsectFrame % 8 == 0) {
                if (Random_GlobalBelow(100) > 50) {
                    s32 t = self->yaw;
                    self->targetAngle = t + MuseumInsect_RandTurn(12);
                    self->moveState = 3;
                }
            }
        } else if (*q == 5) {
            EffectSpl_CreateOneShot(0x80, &self->position, NULL, gEffectSplDefaultInitCbs);
        }
    } else {
        self->moveState = 16;
        NNS_G3dMdlSetMdlAlpha(self->pooledModel.getModel(), 0, 0);
        self->stateTimer = 60;
        *p = 0;
    }
}

extern "C" s32 MuseumInsect_SteerFromEdges(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    u8 r4 = o->steerSide;
    u32 r0;
    s16 r1;
    if (o->insectIndex == 0x34) {
        r0 = MuseumInsect_CheckWallsAhead(o);
    } else {
        r0 = MuseumInsect_CheckFloorAhead(o);
    }
    if (r0 != 0) {
        r1 = o->yaw;
        if (r0 == 3) {
            if (r4 == 1 || r4 == 10) {
                r1 -= 0xaaa;
            } else {
                r1 += 0xaaa;
            }
        } else if (r0 == 1 || r4 == 1) {
            r1 -= 0x38e;
            r4 = 1;
        } else if (r0 == 2 || r4 == 2) {
            r1 += 0x38e;
            r4 = 2;
        }
        o->yaw = r1;
    } else if (r4 < 10) {
        r4 = r4 * 10;
    }
    o->steerSide = r4;
    return r0;
}

extern "C" void MuseumInsect_RunPillBug(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    switch (o->moveState) {
    case 3:
        if (MuseumInsect_PillBugCheckCurl(o)) {
            s16 v = o->yaw;
            if (Math_StepAngle(&v, o->targetAngle, 0x38e)) {
                o->moveState = 4;
            }
            o->yaw = v;
        }
        break;
    case 4:
        MuseumInsect_PillBugWalk(o);
        break;
    default:
        if (MuseumInsect_TickTimer(o) && MuseumInsect_PillBugCheckCurl(o)) {
            if (((Unk_ov004_0223b1e8_Bits &)o->model.curFrame).mid != 1) {
                ((AnimModel *)(&o->model))->setFrame(1);
            }
            o->stateCounter = 0;
            o->moveState = 4;
            o->stateTimer = (Random_GlobalBelow(9) + 4) * 20;
        }
        break;
    }
}

extern "C" BOOL MuseumInsect_PillBugCheckCurl(MuseumInsect *o)
{
    s32 r4 = o->cooldown;
    MuseumInsect_TickAlert(o);
    if (o->alertLevel < o->alertThreshold && r4 < 2) {
        ((AnimModel *)(&o->model))->setFrame(1);
        goto yes;
    }
    if (r4 == 0) {
        o->cooldown = 0x3c;
    } else if (r4 > 1) {
        o->cooldown = r4 - 1;
    }
    ((AnimModel *)(&o->model))->setFrame(0);
    return FALSE;
yes:
    return TRUE;
}

extern "C" void MuseumInsect_PillBugWalk(MuseumInsect *o)
{
    if (!MuseumInsect_PillBugCheckCurl(o)) {
        return;
    }
    {
        V3_b1e8 *r4 = &o->position;
        V3_b1e8 *r6 = &o->targetPos;
        if (MuseumInsect_TickTimer(o) == 0) {
            if (Math_ApproachVecXZ(r4, r6, 0x40, 0x1000, 0x29) == 0) {
                MuseumInsect_PillBugNextWaypoint(o);
                o->targetAngle = Math_AngleXZ(r4, r6);
                o->moveState = 3;
            } else {
                s32 t = (s16)o->stateTimer;
                o->yaw = Math_AngleXZ(r4, r6);
                if (t % 8 == 0) {
                    o->yaw = o->yaw + 0xaaa;
                } else if (t % 4 == 0) {
                    o->yaw = o->yaw - 0xaaa;
                }
            }
        } else {
            o->stateTimer = (Random_GlobalBelow(3) + 2) * 20;
            o->moveState = 0x19;
        }
    }
}

extern "C" void MuseumInsect_PillBugNextWaypoint(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    u32 st = (u8)o->speciesWork;
    u32 nx;
    if (st == 0 && o->dirFlag == 0) {
        o->dirFlag = 1;
        nx = 1;
    } else if (st == 4 && o->dirFlag != 0) {
        nx = 3;
        o->dirFlag = 0;
    } else if (Random_GlobalBelow(100) > 70 && st != 0 && st != 4) {
        if (o->dirFlag != 0) {
            nx = (u8)(st - 1);
            o->dirFlag = 0;
        } else {
            nx = (u8)(st + 1);
            o->dirFlag = 1;
        }
    } else {
        if (o->dirFlag != 0) {
            nx = (u8)(st + 1);
        } else {
            nx = (u8)(st - 1);
        }
    }
    o->speciesWork = nx;
    MuseumInsect_GetPillBugWaypoint(&o->targetPos, nx);
}

extern "C" void MuseumInsect_GetPillBugWaypoint(void *v_, s32 k)
{
    V3_b1e8 *v = (V3_b1e8 *)v_;
    switch (k) {
    case 0:
        v->x = 0x11e00;
        v->y = 0x800;
        v->z = 0xda00;
        break;
    case 1:
        v->x = 0x12300;
        v->y = 0x800;
        v->z = 0xf400;
        break;
    case 2:
        v->x = 0x13800;
        v->y = 0x800;
        v->z = 0xf600;
        break;
    case 3:
        v->x = 0x14100;
        v->y = 0x800;
        v->z = 0xe800;
        break;
    default:
        v->x = 0x14000;
        v->y = 0x800;
        v->z = 0xd900;
        break;
    }
}

extern "C" void MuseumInsect_RunMoth(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    if (o->moveState == 0) {
        MuseumInsect_MothHover(o);
    } else if (o->isActive != 0) {
        o->isAlerted = 0;
        o->moveState = 0;
        o->stateCounter = 0;
    } else if (sMuseumInsectFrame % 40 == 0) {
        if (Random_GlobalBelow(100) > 80) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(8, 1, 0x1000, 0);
        }
    }
}

extern "C" void MuseumInsect_MothHover(MuseumInsect *o)
{
    u8 r6 = o->sideDir;
    V3_b1e8 *r4 = &o->position;
    V3_b1e8 *tp = &o->homePos;
    volatile s32 c;
    u8 r7;
    VecFx32Ctor sv;
    r7 = o->dirFlag;
    *(V3_b1e8 *)&sv = *r4;
    if (Random_GlobalBelow(100) > 30) {
        s32 t = sMuseumInsectFrame;
        c = t;
        if (t % 10 == 0) {
            o->dirFlag = (r7 == 0) ? 1 : 0;
        } else if (c % 5 == 0) {
            o->sideDir = (r6 == 0) ? 1 : 0;
        }
    }
    if (r6) {
        r4->x = r4->x + o->moveSpeed * 0x30;
    } else {
        r4->x = r4->x - o->moveSpeed * 0x30;
    }
    if (r7) {
        r4->y = r4->y + o->moveSpeed * 0x30;
    } else {
        r4->y = r4->y - o->moveSpeed * 0x30;
    }
    {
        s32 d = r4->x - tp->x;
        if (d < 0) d = -d;
        if (d > 0x1000) {
            o->sideDir = (r6 == 0) ? 1 : 0;
            r4->x = sv.x;
        }
    }
    {
        s32 d = r4->y - tp->y;
        if (d < 0) d = -d;
        if (d > 0x800) {
            o->dirFlag = (r7 == 0) ? 1 : 0;
            r4->y = sv.y;
        }
    }
}

extern "C" void MuseumInsect_RunArachnid(void *o_)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    if (o->isFighting != 0) {
        if (!MuseumInsect_UpdateFight(o)) {
            return;
        }
    } else {
        if (MuseumInsect_ArachnidFacePlayer(o) == 1) {
            return;
        }
        if (o->insectIndex == 0x37) {
            u32 t = ((Unk_ov004_0223b1e8_Bits &)o->model.curFrame).mid;
            if (t > 3) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(3, 3, 0x1000, t);
            } else if (t == 3) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(3, 0, 0x1000, 0);
            }
        }
    }
    switch (o->moveState) {
    case 20:
        MuseumInsect_FightSkirmish(o);
        return;
    case 21:
        MuseumInsect_FightCircleOther(o);
        return;
    case 22:
        MuseumInsect_FightCircleSelf(o);
        return;
    case 23:
        MuseumInsect_FightClash(o);
        return;
    case 24:
        MuseumInsect_FightPause(o);
        return;
    case 4:
        MuseumInsect_ArachnidWalk(o);
        return;
    case 3:
    case 15: {
        s32 r = MuseumInsect_CheckFloorAhead(o);
        if (r != 0 && o->moveState == 3) {
            o->targetAngle = MuseumInsect_GetEscapeHeading(o->yaw, r);
            o->moveState = 15;
            return;
        }
        {
            s16 v = o->yaw;
            if (Math_StepAngle(&v, o->targetAngle, 0x71c)) {
                o->moveState = 4;
            }
            o->yaw = v;
        }
        return;
    }
    default:
        if (MuseumInsect_TickTimer(o)) {
            s32 t;
            s32 c;
            o->isAlerted = 0;
            o->moveState = 3;
            t = (Random_GlobalBelow(3) + 1) * 20;
            o->stateTimer = (s16)t;
            c = o->yaw;
            s32 t2 = MuseumInsect_RandTurn(0x10);
            t2 += c;
            o->targetAngle = t2;
        }
        return;
    }
}

extern "C" void MuseumInsect_WiggleHeading(void *o_, s32 a, s32 b)
{
    MuseumInsect *o = (MuseumInsect *)o_;
    if (b % 4 == 0) {
        o->yaw = a + 0x71c;
    } else if (b % 2 == 0) {
        o->yaw = a - 0x71c;
    }
    MuseumInsect_PlaySe(o, 0);
}

extern "C" BOOL MuseumInsect_FaceEachOther(MuseumInsect *a, MuseumInsect *b)
{
    s16 v[2];
    u8 r;
    v[0] = a->yaw;
    v[1] = b->yaw;
    r = Math_StepAngle(&v[1], Math_AngleXZ(&b->position, &a->position), 0xaaa);
    r &= Math_StepAngle(&v[0], Math_AngleXZ(&a->position, &b->position), 0xaaa);
    a->yaw = v[0];
    b->yaw = v[1];
    if (r) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MuseumInsect_UpdateFight(MuseumInsect *o)
{
    MuseumInsect_ClampToBounds(o, &o->position);
    if (o->insectIndex == 0x37) {
        AnimModel *b = &o->model;
        s32 t = (s32)b->numFrames >> 12;
        if ((u16)t < 11 && ((Unk_ov004_0223b1e8_Bits &)b->curFrame).mid <= 2) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*b))->setup(11, 1, 0x1000, 3);
        } else if ((u16)t < 14 && ((Unk_ov004_0223b1e8_Bits &)b->curFrame).mid < 11) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*b))->setup(14, 0, 0x1000, 10);
        } else if ((u16)t > 11 && ((Unk_ov004_0223b1e8_Bits &)b->curFrame).mid == 13) {
            ((AnimModel *)(b))->setFrame(10);
        }
        return FALSE;
    }
    if (o->moveState == 0x19) {
        MuseumInsect *p = ((MuseumInsect *)MuseumInsect_FindScorpion());
        u32 r = (u8)Random_GlobalBelow(100);
        s16 *q = &o->subCounter;
        if (!MuseumInsect_FaceEachOther(o, p)) {
            return FALSE;
        }
        if (r < 20) {
            o->stateTimer = (Random_GlobalBelow(8) + 2) * 20;
            o->moveState = 20;
        } else if (r < 35) {
            o->stateTimer = (Random_GlobalBelow(4) + 1) * 20;
            o->moveState = 21;
            {
                V3_b1e8 *sv = &p->position;
                V3_b1e8 *dv = &p->targetPos;
                dv->x = sv->x;
                dv->y = sv->y;
                dv->z = sv->z;
            }
            if (Random_GlobalBelow(100) > 50) {
                o->dirFlag = 0;
            } else {
                o->dirFlag = 1;
            }
        } else if (r < 50) {
            o->stateTimer = (Random_GlobalBelow(4) + 1) * 20;
            o->moveState = 22;
            {
                V3_b1e8 *sv = &o->position;
                V3_b1e8 *dv = &o->targetPos;
                dv->x = sv->x;
                dv->y = sv->y;
                dv->z = sv->z;
            }
            if (Random_GlobalBelow(100) > 50) {
                o->dirFlag = 0;
            } else {
                o->dirFlag = 1;
            }
        } else if (r < 70) {
            o->stateTimer = (Random_GlobalBelow(4) + 1) * 20;
            o->moveState = 23;
        } else {
            o->stateTimer = (Random_GlobalBelow(8) + 1) * 20;
            o->moveState = 24;
            p->model.frameStep = 0;
        }
        o->speciesWork = 0;
        *q = Random_GlobalBelow(5) + 5;
        if (Random_GlobalBelow(100) > 50) {
            *q = -*q;
        }
        p->stateCounter = 0;
        p->moveState = o->moveState;
        MuseumInsect_ClampToBounds(p, &p->position);
    }
    return TRUE;
}

extern "C" void MuseumInsect_FightSkirmish(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsect *o = ((MuseumInsect *)MuseumInsect_FindScorpion());
    VecFx32 *rp = &r->position;
    VecFx32 *op = &o->position;
    s32 a1 = Math_AngleXZ(op, rp);
    s32 v4c;
    s32 dist;
    s32 f1;
    s32 f2;
    s16 *cnt;
    cnt = &r->stateCounter;
    v4c = r->speciesWork;
    dist = Vec_DistXZ(rp, op);
    f1 = 1;
    f2 = 1;
    s16 *pw = &r->subCounter;
    VecFx32 v1, v2;
    MuseumInsect_MakeStepDir(&v1, a1);
    s32 a2 = Math_AngleXZ(rp, op);
    MuseumInsect_MakeStepDir(&v2, a2);
    if (sMuseumInsectFrame % 15 == 0) {
        v4c = Random_GlobalBelow(100);
        r->speciesWork = v4c;
        *pw = Random_GlobalBelow(5) + 5;
        if (Random_GlobalBelow(100) > 0x32) {
            *pw = -*pw;
        }
    }
    s32 t = *pw;
    if (t > 0) {
        *pw = t - 1;
    } else if (t < 0) {
        *pw = t + 1;
    }
    if (v4c < 0x1e && dist < 0xccd) {
        f1 = 0;
        if (*pw <= 0) {
            VecFx32 w;
            Vec_ScaleTo(&w, &v2, 0x2000);
            VEC_Add(rp, &w, rp);
        } else {
            VecFx32 w;
            Vec_ScaleTo(&w, &v1, 0x2000);
            VEC_Subtract(op, &w, op);
        }
    } else if (v4c < 0x3c && dist < 0xccd) {
        f2 = 0;
        if (*pw <= 0) {
            VecFx32 w;
            Vec_ScaleTo(&w, &v2, 0x2000);
            VEC_Subtract(rp, &w, rp);
        } else {
            VecFx32 w;
            Vec_ScaleTo(&w, &v1, 0x2000);
            VEC_Add(op, &w, op);
        }
    } else if ((dist > 0x5800 || v4c < 0x50) && dist > 0x99a) {
        if (*pw <= 0) {
            VecFx32 w;
            Vec_ScaleTo(&w, &v2, 0xa000);
            VEC_Add(rp, &w, rp);
        } else {
            VecFx32 w;
            Vec_ScaleTo(&w, &v1, 0xa000);
            VEC_Add(op, &w, op);
        }
    } else if (dist < 0x5800) {
        if (v4c < 0x5a) {
            if (*pw <= 0) {
                VEC_Subtract(rp, &v2, rp);
            } else {
                VEC_Subtract(op, &v1, op);
            }
        } else if (v4c < 0x64) {
            if (*pw <= 0) {
                VecFx32 w;
                Vec_ScaleTo(&w, &v2, 0x5000);
                VEC_Subtract(rp, &w, rp);
            } else {
                VecFx32 w;
                Vec_ScaleTo(&w, &v1, 0x5000);
                VEC_Subtract(op, &w, op);
            }
        }
    }
    if (f2 != 0) {
        MuseumInsect_WiggleHeading(r, Math_AngleXZ(rp, op), *cnt);
    } else {
        r->yaw = Math_AngleXZ(rp, op);
    }
    if (f1 != 0) {
        MuseumInsect_WiggleHeading(o, a1, *cnt);
    } else {
        o->yaw = Math_AngleXZ(op, rp);
    }
    *cnt = *cnt + 1;
    if (MuseumInsect_TickTimer(r) != 0) {
        r->moveState = 0x19;
        *cnt = 0;
    }
}

extern "C" void MuseumInsect_FightCircleOther(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsect *o = ((MuseumInsect *)MuseumInsect_FindScorpion());
    VecFx32 *a = &r->position;
    VecFx32 *b = &o->position;
    VecFx32 *c = &o->targetPos;
    s32 ang = Math_AngleXZ(a, b);
    s16 *cnt = &r->stateCounter;
    s32 v4c = r->speciesWork;
    if (sMuseumInsectFrame % 10 == 0) {
        if (Random_GlobalBelow(100) > 0x32) {
            r->dirFlag = 1;
        } else {
            r->dirFlag = 0;
        }
    }
    u32 f = r->dirFlag;
    if (f != 0 && v4c < 0x1554) {
        ang = (s16)(ang + 0xb6);
        v4c += 0xb6;
    } else if (f == 0 && v4c > 0) {
        ang = (s16)(ang - 0xb6);
        v4c -= 0xb6;
    } else if (f != 0) {
        r->dirFlag = 0;
    } else {
        r->dirFlag = 1;
    }
    s32 d = Vec_DistXZ(c, a);
    s32 idx = ((u16)ang >> 4) * 2;
    b->x = a->x + func_01ffcb0c(data_02135f44[idx], d);
    b->z = a->z + func_01ffcb0c(data_02135f44[idx + 1], d);
    r->yaw = ang;
    s32 res = Math_AngleXZ(b, a);
    o->yaw = res;
    MuseumInsect_WiggleHeading(o, res, *cnt);
    r->speciesWork = v4c;
    *cnt = *cnt + 1;
    if (MuseumInsect_TickTimer(r) != 0) {
        r->moveState = 0x19;
        *cnt = 0;
    }
}

extern "C" void MuseumInsect_FightCircleSelf(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsect *o = ((MuseumInsect *)MuseumInsect_FindScorpion());
    VecFx32 *a = &r->position;
    VecFx32 *b = &o->position;
    VecFx32 *c = &r->targetPos;
    s32 ang = Math_AngleXZ(b, a);
    s16 *cnt = &r->stateCounter;
    s32 v4c = r->speciesWork;
    if (sMuseumInsectFrame % 10 == 0) {
        if (Random_GlobalBelow(100) > 0x32) {
            r->dirFlag = 1;
        } else {
            r->dirFlag = 0;
        }
    }
    u32 f = r->dirFlag;
    if (f != 0 && v4c < 0x1554) {
        ang = (s16)(ang + 0xb6);
        v4c += 0xb6;
    } else if (f == 0 && v4c > 0) {
        ang = (s16)(ang - 0xb6);
        v4c -= 0xb6;
    } else if (f != 0) {
        r->dirFlag = 0;
    } else {
        r->dirFlag = 1;
    }
    s32 d = Vec_DistXZ(c, b);
    s32 idx = ((u16)ang >> 4) * 2;
    a->x = b->x + func_01ffcb0c(data_02135f44[idx], d);
    a->z = b->z + func_01ffcb0c(data_02135f44[idx + 1], d);
    o->yaw = ang;
    s32 res = Math_AngleXZ(a, b);
    r->yaw = res;
    MuseumInsect_WiggleHeading(r, res, *cnt);
    r->speciesWork = v4c;
    *cnt = *cnt + 1;
    if (MuseumInsect_TickTimer(r) != 0) {
        r->moveState = 0x19;
        *cnt = 0;
    }
}

extern "C" void MuseumInsect_FightPause(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    if (MuseumInsect_TickTimer(r) != 0) {
        r->moveState = 0x19;
        ((MuseumInsect *)MuseumInsect_FindScorpion())->model.frameStep = 0x1000;
        r->stateCounter = 0;
    }
}

extern "C" void MuseumInsect_FightClash(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsect *o = ((MuseumInsect *)MuseumInsect_FindScorpion());
    VecFx32 *a = &r->position;
    VecFx32 *b = &o->position;
    s16 *cnt = &r->stateCounter;
    if (Vec_DistXZ(a, b) < 0x2000) {
        VecFx32 v1, v2, w1, w2;
        s32 ang1 = Math_AngleXZ(b, a);
        o->yaw = ang1;
        MuseumInsect_MakeStepDir(&v1, ang1);
        MuseumInsect_WiggleHeading(o, ang1, *cnt);
        s32 ang2 = Math_AngleXZ(a, b);
        r->yaw = ang2;
        MuseumInsect_MakeStepDir(&v2, ang2);
        MuseumInsect_WiggleHeading(r, ang2, *cnt);
        Vec_ScaleTo(&w1, &v2, 0x4000);
        VEC_Subtract(a, &w1, a);
        Vec_ScaleTo(&w2, &v1, 0x4000);
        VEC_Subtract(b, &w2, b);
        *cnt = *cnt + 1;
    } else if (MuseumInsect_TickTimer(r) != 0) {
        r->moveState = 0x19;
        *cnt = 0;
    }
}

extern "C" void MuseumInsect_ArachnidWalk(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    s32 p = r->crawl();
    if (MuseumInsect_ClampToBounds(r, &r->position) != 0) {
        r->moveState = 3;
        return;
    }
    if (MuseumInsect_TickTimer(r) != 0) {
        if (p != 0) {
            r->targetAngle = MuseumInsect_GetEscapeHeading(r->yaw, p);
        } else {
            r->targetAngle = MuseumInsect_RandTurn(0x10);
        }
        r->isAlerted = 0;
        r->moveState = 0x19;
        if (r->isActive != 0) {
            s16 v = (Random_GlobalBelow(6) + 1) * 0x14;
            r->stateTimer = v;
        } else {
            s16 v = (Random_GlobalBelow(0x1e) + 5) * 0x14;
            r->stateTimer = v;
        }
    }
}

extern "C" BOOL MuseumInsect_ArachnidFacePlayer(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsectPlayerInfo l;
    s16 ang;
    s32 t = MuseumInsect_UpdateAlertLevel(r, &l);
    VecFx32 *pos = &r->position;
    s16 *pw = &r->subCounter;
    if (l.hasPlayer != 0 && (t == 3 || *pw != 0)) {
        s32 a = Math_AngleXZ(pos, &l.playerPos);
        ang = r->yaw;
        AnimModel *s = &r->model;
        Math_StepAngle(&ang, a, 0x38e);
        r->yaw = ang;
        if ((s8)r->insectIndex == 0x37) {
            s32 x = (s32)s->numFrames >> 12;
            if ((u16)x < 0xb && ((Unk_ov004_0223b1e8_Bits &)s->curFrame).mid <= 2) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*s))->setup(0xb, 1, 0x1000, 3);
            } else if ((u16)x < 0xe && ((Unk_ov004_0223b1e8_Bits &)s->curFrame).mid < 0xa) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*s))->setup(0xe, 0, 0x1000, 0xa);
            } else if (((Unk_ov004_0223b1e8_Bits &)s->curFrame).mid == 0xd && (u16)x > 0xa) {
                ((AnimModel *)(s))->setFrame(0xa);
            }
        }
        if (*pw > 0) {
            *pw = *pw - 1;
        } else {
            *pw = 0x3c;
        }
        return TRUE;
    }
    return FALSE;
}

extern "C" void MuseumInsect_RunDungBeetle(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsect *p;
    u8 c = r->insectIndex;
    if (c == 0x23) {
        p = ((MuseumInsect *)MuseumInsect_FindDungBall());
    }
    switch (r->moveState) {
    case 4: {
        u32 tmp = r->model.frameStep;
        if (Math_ApproachS32(&tmp, 0x1000, 0x66, 0x1000, 0x29) == 0) {
            r->moveState = 5;
        }
        r->model.frameStep = tmp;
        break;
    }
    case 5:
        if (MuseumInsect_TickTimer(r) != 0) {
            r->moveState = 0x19;
            r->model.frameStep = 0;
            if (c == 0x23) {
                s16 v = (Random_GlobalBelow(3) + 2) * 0x14;
                if (r->isActive == 0) {
                    v = v * 3;
                }
                r->stateTimer = v;
                p->subCounter = v;
            } else {
                r->stateTimer = r->subCounter;
            }
        }
        break;
    default:
        if (MuseumInsect_TickTimer(r) != 0) {
            r->moveState = 4;
            if (c == 0x23) {
                s16 v = (Random_GlobalBelow(9) + 2) * 0x14;
                r->stateTimer = v;
                p->subCounter = v;
            } else {
                s32 v = r->subCounter;
                if (v > 0) {
                    r->stateTimer = v;
                }
            }
        }
        break;
    }
}

extern "C" void MuseumInsect_RunCockroach(void *r_) {
    MuseumInsect *r = (MuseumInsect *)r_;
    MuseumInsectPlayerInfo l;
    s16 ang;
    s32 t = MuseumInsect_UpdateAlertLevel(r, &l);
    if (r->alertLevel > 0x50) {
        r->alertLevel = 0x50;
    }
    switch (r->moveState) {
    case 4:
        r->scurry(&l);
        break;
    case 3:
        ang = r->yaw;
        if (Math_StepAngle(&ang, r->targetAngle, 0x2000) != 0) {
            r->moveState = 4;
        }
        r->yaw = ang;
        break;
    default:
        if (t == 3) {
            r->targetAngle = Math_AngleXZ(&l.playerPos, &r->position);
            r->stateTimer = (Random_GlobalBelow(4) + 2) * 0x14;
            r->moveState = 3;
        } else if (MuseumInsect_TickTimer(r) != 0) {
            r->moveState = 4;
            r->stateTimer = (Random_GlobalBelow(4) + 1) * 0x14;
        }
        break;
    }
    if (r->speciesWork == 0) {
        if (l.hasPlayer != 0) {
            if (l.hasPlayer != 0) {
                if (l.playerSpeed > 0) {
                    if (r->subCounter == 0) {
                        if (Vec_DistXZ(&l, &r->position) < 0xe66) {
                            MuseumExhibitInfo_SpawnAutoTalk();
                            r->speciesWork = 1;
                        }
                    }
                }
            }
        }
    }
}

void MuseumInsect::scurry(MuseumInsectPlayerInfo *v) {
    s16 *cnt = &subCounter;
    VecFx32 *pos = &position;
    s32 res = crawl();
    s16 ang = yaw;
    VecFx32 d1;
    Vec_Sub(&d1, &v->playerPos, &position);
    VecFx32 d0;
    MuseumInsect_MakeStepDir(&d0, ang);
    Vec_SafeNormalize(&d0);
    Vec_SafeNormalize(&d1);
    s32 dot = Vec_DotXZ(&d0, &d1);
    if (v->hasPlayer != 0 && dot > 0) {
        if (Vec_DistXZ(pos, &v->playerPos) < 0x1800) {
            if (dot > data_02136744[1]) {
                *cnt = *cnt + 1;
            }
        } else if (Vec_DistXZ(pos, &v->playerPos) < 0x2800) {
            if (res == 0) {
                Math_StepAngle(&ang, Math_AngleXZ(&v->playerPos, pos), 0xaaa);
                yaw = ang;
            }
        }
    }
    s32 c = *cnt;
    if (c > 0) {
        s32 m = c << 12;
        pos->y = func_01ffcb0c(0x99a - func_01ffcb0c(0xcd, m), m);
        if (pos->y < 3) {
            pos->y = 3;
            *cnt = 0;
        } else {
            *cnt = *cnt + 1;
        }
        MuseumInsect_FlapWings(this);
        MuseumInsect_PlaySe(this, 1);
    } else {
        MuseumInsect_PlaySe(this, 0);
        if (((Unk_ov004_0223b1e8_Bits &)model.curFrame).mid != 0) {
            ((AnimModel *)(&model))->setFrame(0);
        }
    }
    if (MuseumInsect_TickTimer(this) != 0 && *cnt == 0) {
        stateTimer = (Random_GlobalBelow(10) + 3) * 20;
        moveState = 0x19;
    }
}

s32 MuseumInsect::crawl() {
    VecFx32 *pos = &position;
    VecFx32 saved;
    saved.x = pos->x;
    saved.y = pos->y;
    saved.z = pos->z;
    s16 *cnt = &stateCounter;
    s32 speed = 5;
    s32 res = MuseumInsect_SteerFromEdges(this);
    u32 st = (u8)insectIndex;
    VecFx32 dir;
    s32 hit, a, c, mul, k;
    MuseumInsect_MakeStepDir(&dir, yaw);
    if (st == 0x1e) {
        speed = 4;
    }
    if (res == 0 || st == 0x34) {
        mul = (speed + moveSpeed) << 12;
        pos->x = pos->x + func_01ffcb0c(mul, dir.x);
        pos->z = pos->z + func_01ffcb0c(mul, dir.z);
        if (st == 0x34 || st == 0x30) {
            {
                GroundInfo g;
                g.initAtPos(pos, 0, 0);
                if (g.getHeight(0) > 0x200) {
                    hit = 1;
                } else {
                    hit = 0;
                }
            }
            if (hit != 0) {
                if (res == 0 && st == 0x34) {
                    if (Random_GlobalBelow(100) < 0x32) {
                        yaw = yaw + 0x38e;
                    } else {
                        yaw = yaw - 0x38e;
                    }
                }
                pos->x = saved.x;
                pos->y = saved.y;
                pos->z = saved.z;
            }
        }
        if (st == 0x37) {
            k = 0x71c;
        } else {
            k = 0xaaa;
        }
        c = *cnt;
        if (c == 0) {
            a = yaw;
            yaw = a + func_01ffcb0c(k, 0x800);
        } else if (c % 4 == 0) {
            yaw = k + yaw;
        } else if (c % 2 == 0) {
            yaw = yaw - k;
        }
        *cnt = *cnt + 1;
        if ((u8)(st + 0xca) <= 1) {
            MuseumInsect_PlaySe(this, 0);
        }
        return res;
    }
    return res;
}

extern "C" void MuseumInsect_ClampStep(void *out_, void *in_, s32 lim) {
    VecFx32 *out = (VecFx32 *)out_;
    VecFx32 *in = (VecFx32 *)in_;
    s32 l = func_01ffcb0c(lim << 12, 0x40);
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    out->y = 0;
    s32 x = in->x;
    if (x > l) {
        out->x = l;
    } else if (x < -l) {
        out->x = -l;
    }
    s32 z = in->z;
    if (z > l) {
        out->z = l;
    } else if (z < -l) {
        out->z = -l;
    }
}

void MuseumInsect::runSpider() {
    s16 *cnt = &subCounter;
    switch (moveState) {
    case 2: {
        if (dirFlag != 0) {
            dirFlag = 0;
            roll = 0x5b;
        } else {
            dirFlag = 1;
            roll = -0x5b;
        }
        if (((Unk_ov004_0223b1e8_Bits &)model.curFrame).mid == 0x38) {
            moveState = 0x19;
            roll = 0;
            position.x = speciesWork;
            NNS_G3dMdlSetMdlAlpha(pooledModel.getModel(), 0, 0);
            subCounter = (Random_GlobalBelow(4) + 3) * 20;
        }
        break;
    }
    case 1:
        if (((Unk_ov004_0223b1e8_Bits &)model.curFrame).mid == 0x20) {
            subCounter = (Random_GlobalBelow(3) + 2) * 20;
            moveState = 0x12;
            stateCounter = 0;
        }
        break;
    case 0x12:
        if (swing(&stateCounter) && *cnt <= 0) {
            yaw = 0;
            moveState = 2;
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(0x39, 1, 0x1000, 0x20);
        } else {
            *cnt = *cnt - 1;
        }
        break;
    default:
        if (isPlayerNear()) {
            if (*cnt > 0) {
                *cnt = *cnt - 1;
            } else {
                moveState = 1;
                alertLevel = 0;
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(0x21, 1, 0x1000, 0);
                NNS_G3dMdlSetMdlAlpha(pooledModel.getModel(), 0, 0x1f);
            }
        } else {
            model.playMode = 1;
        }
        break;
    }
}

BOOL MuseumInsect::isPlayerNear() {
    Actor *r = (Actor *)PlayerActor_GetActor(4);
    if (r != NULL) {
        if (Vec_DistXZ(&r->position, &position) < 0x4800) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL MuseumInsect::swing(s16 *p) {
    s32 a = yaw;
    if (*p == 0) {
        if (Random_GlobalBelow(100) > 0x32) {
            dirFlag = 0;
        } else {
            dirFlag = 1;
        }
    }
    if (dirFlag != 0) {
        if (a > 0xaaa) {
            dirFlag = 0;
        }
    } else if (a < (s32)0xfffff556) {
        dirFlag = 1;
    }
    if (dirFlag != 0) {
        yaw = a + 0x222;
    } else {
        yaw = a - 0x222;
    }
    *p = *p + 1;
    return TRUE;
}

void MuseumInsect::runPerched() {
    switch (moveState) {
    case 3:
        sidestep(&stateCounter);
        break;
    case 2:
        crawlUp(&stateCounter);
        break;
    case 1:
        crawlDown(&stateCounter);
        break;
    default:
        if (insectIndex == 9) {
            animSilkMoth();
        } else if (isActive != 0) {
            if (sMuseumInsectFrame % 0x14 == 0) {
                if (Random_GlobalBelow(100) < 0x46) {
                } else {
                    goto pick;
                }
            }
        } else if (sMuseumInsectFrame % 0x28 == 0) {
            if (Random_GlobalBelow(100) >= 0x55) {
            pick:
                if (Random_GlobalBelow(100) < 0x32) {
                    moveState = 3;
                } else {
                    moveState = 2;
                }
            }
        }
        break;
    }
}

void MuseumInsect::animSilkMoth() {
    u32 r = ((Unk_ov004_0223b1e8_Bits &)model.curFrame).mid;
    if (r == 0xd || r < 9) {
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(9, 1, 0, 9);
    }
    if (sMuseumInsectFrame > 0x50) {
        if (isActive != 0) {
            if (Random_GlobalBelow(100) > 0x5c) {
                if (r < 0xa) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(0xe, 1, 0x1000, 9);
                }
            }
        } else if (sMuseumInsectFrame % 5 == 0) {
            if (Random_GlobalBelow(100) > 0x5c) {
                if (r < 0xa) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(0xe, 1, 0x1000, 9);
                }
            }
        }
    }
}

void MuseumInsect::crawlUp(volatile s16 *p) {
    s32 lim = baseHeight + 0x400;
    VecFx32 *pos = &position;
    s32 v = *p;
    if ((v >= 0 && v < 2) || (v >= 6 && v < 8)) {
        *p = *p + 1;
        yaw = yaw + 0x2aa;
        pitch = pitch + 0xaa;
        pos->y = pos->y + 0x20;
    } else if (v >= 2 && v < 6) {
        *p = *p + 1;
        yaw = yaw - 0x2aa;
        pitch = pitch - 0xaa;
        pos->y = pos->y + 0x20;
    } else {
        if (Random_GlobalBelow(100) > 0x46) {
            moveState = 1;
            *p = 0;
        } else {
            if (*p >= 8) {
                *p = 0;
            }
        }
    }
    if (pos->y > lim) {
        pos->y = lim;
    }
}

void MuseumInsect::crawlDown(volatile s16 *p) {
    s32 lim = baseHeight - 0x100;
    VecFx32 *pos = &position;
    s32 v = *p;
    if ((v >= 0 && v < 2) || (v >= 6 && v < 8)) {
        *p = *p + 1;
        yaw = yaw + 0x2aa;
        pitch = pitch + 0xaa;
        pos->y = pos->y - 0x20;
    } else if (v >= 2 && v < 6) {
        *p = *p + 1;
        yaw = yaw - 0x2aa;
        pitch = pitch - 0xaa;
        pos->y = pos->y - 0x20;
    } else {
        if (Random_GlobalBelow(100) > 0x46) {
            moveState = 0x19;
            *p = 0;
        } else {
            if (*p >= 8) {
                *p = 0;
            }
        }
    }
    if (pos->y < lim) {
        pos->y = lim;
    }
}

void MuseumInsect::sidestep(volatile s16 *p) {
    s32 a = yaw;
    s32 v = *p;
    if (v == 0) {
        if (Random_GlobalBelow(100) < 0x32) {
            *p = *p + 1;
        } else {
            *p = *p - 1;
        }
    } else {
        if ((v > 0 && v <= 6) || (v > 0x12 && v <= 0x18) || (v < -6 && v >= -0x12)) {
            if (v > 0) {
                *p = *p + 1;
                pitch = pitch + 0xb6;
            } else {
                *p = *p - 1;
                pitch = pitch - 0xb6;
            }
            a = (s16)(a + 0x16b);
        } else if ((v > 6 && v <= 0x12) || (v < 0 && v >= -6) || (v < -0x12 && v >= -0x18)) {
            if (v > 0) {
                *p = *p + 1;
                pitch = pitch - 0xb6;
            } else {
                *p = *p - 1;
                pitch = pitch + 0xb6;
            }
            a = (s16)(a - 0x16b);
        } else {
            *p = 0;
            moveState = 0x19;
        }
    }
    yaw = a;
}

void MuseumInsect::runCicada() {
    MuseumInsect_TickAlert(this);
    if (insectIndex == 0x14) {
        AnimModel *p = &model;
        if (alertLevel >= alertThreshold || cooldown != 0) {
            if (((Unk_ov004_0223b1e8_Bits &)p->curFrame).mid == 0) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*p))->setup(4, 1, 0x1000, 0);
                cooldown = 0x3c;
            } else if (cooldown != 0) {
                cooldown = cooldown - (TICK_STEP_ENDS() ? 1 : 0);
            }
        } else {
            s32 v = p->curFrame >> 12;
            if ((u16)v != 0 || ((Unk_ov004_0223b1e8_Bits &)p->numFrames).mid != 0) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*p))->setup(0, 3, 0x1000, (u16)v);
            }
        }
    }
    if (isActive != 0) {
        if (alertLevel < alertThreshold) {
            if (cooldown == 0) {
                MuseumInsect_PlaySe(this, 0);
            } else {
                cooldown = cooldown - (TICK_STEP_ENDS() ? 1 : 0);
            }
        } else {
            cooldown = 0x3c;
        }
    }
}

void MuseumInsect::runWalker()
{
    volatile s16 *p = &stateCounter;
    s32 v;
    reactToPlayer((u16 *)p);
    stateCounter = stateCounter + 1;
    if (moveState == 4) {
        wander();
        if (insectIndex == 0x1a) {
            if ((v = *p) > 0x140 || (v % 0x14 == 0 && Random_GlobalBelow(100) > 0x5a && *p > 0xa0)) {
                moveState = 0x19;
                *p = 0;
            }
        } else {
            if ((v = *p) > 0xa0 || (v % 0x14 == 0 && Random_GlobalBelow(100) > 0x5a && *p > 0x50)) {
                moveState = 0x19;
                *p = 0;
            }
        }
    } else if (insectIndex == 0x1a) {
        if (isActive != 0 && (u32)(model.curFrame << 4) >> 16 == 2) {
            if ((v = *p) > 0xa0 || (v % 0x14 == 0 && Random_GlobalBelow(100) > 0x55 && *p >= 0x28)) {
                *p = 0;
                moveState = 4;
            }
        }
    } else if (isActive) {
        if ((v = *p) > 0x50 || (v % 0x14 == 0 && Random_GlobalBelow(100) > 0x55)) {
            moveState = 4;
            *p = 0;
        }
    } else {
        if ((v = *p) > 0x320 || (v % 100 == 0 && Random_GlobalBelow(100) > 0x5a)) {
            moveState = 4;
            *p = 0;
        }
    }
}

void MuseumInsect::reactToPlayer(u16 *out)
{
    MuseumInsectPlayerInfo buf;
    MuseumInsect_UpdateAlertLevel(this, &buf);
    if (buf.hasPlayer == 0) return;
    s32 r6 = alertLevel;
    AnimModel *r4 = &model;
    if (buf.playerDist <= 0xccd) {
        *out = 0;
        return;
    }
    s32 c = insectIndex;
    u8 n;
    if ((u8)(s8)(c - 0xe) <= 1) {
        if (cooldown != 0) {
            yaw = Math_AngleXZ(&position, &buf.playerPos);
            moveState = 0x19;
        }
        if (r6 > 0x14) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*r4))->setup(9, 1, 0x1000, (u32)(r4->curFrame << 4) >> 16);
            cooldown = 0x3c;
        } else if ((n = cooldown) != 0) {
            cooldown = n - 1;
        } else if (buf.playerDist < alertRange) {
            u32 t = (u32)(r4->curFrame << 4) >> 16;
            if (t == 0) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*r4))->setup(4, 1, 0x1000, 0);
                cooldown = 0x3c;
            } else if (t > 4) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*r4))->setup(4, 3, 0x1000, t);
            }
        } else {
            u32 t = (u32)(r4->curFrame << 4) >> 16;
            if (t != 0) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*r4))->setup(0, 3, 0x1000, t);
            }
        }
    } else if (c == 0x1a) {
        if (r6 > 0x14 || isActive == 0) {
            u32 t = (u32)(r4->curFrame << 4) >> 16;
            if (t == 2) {
                ((AnimModel *)(r4))->setFrame(1);
            } else if (t == 1) {
                ((AnimModel *)(r4))->setFrame(0);
                moveState = 0x19;
                cooldown = 0x3c;
            }
        } else {
            s32 h = (s32)r4->curFrame >> 12;
            if ((u16)h == 0 && cooldown == 0) {
                ((AnimModel *)(r4))->setFrame(1);
            } else if ((u16)h == 1) {
                ((AnimModel *)(r4))->setFrame(2);
            } else if ((n = cooldown) != 0) {
                cooldown = n - 1;
            }
        }
    }
}

void MuseumInsect::wander()
{
    s32 *p60 = &boundsMax.x;
    s32 *p58 = &boundsMin.x;
    s32 ang = yaw;
    u32 flip = sideDir;
    VecFx32 *pos = &position;
    struct {
        VecFx32 v;
        VecFx32 sv;
    } l;
    l.sv.x = pos->x;
    l.sv.y = pos->y;
    l.sv.z = pos->z;
    if (Random_GlobalBelow(100) > 0x50) {
        if (sMuseumInsectFrame % 0x14 == 0) {
            if (flip == 0) flip = 1; else flip = 0;
            sideDir = flip;
        }
        if (flip) {
            ang = (s16)(ang + (s16)speciesWork);
        } else {
            ang = (s16)(ang - (s16)speciesWork);
        }
    }
    MuseumInsect_MakeStepDir(&l.v, ang);
    yaw = ang;
    pos->z += func_01ffcb0c(func_01ffcb0c(moveSpeed << 12, l.v.z), 0x80);
    pos->x += func_01ffcb0c(func_01ffcb0c(moveSpeed << 12, l.v.x), 0x80);
    s32 x = pos->x;
    if (x < p58[0] || x > p60[0]) pos->x = l.sv.x;
    s32 z = pos->z;
    if (z < p58[1] || z > p60[1]) pos->z = l.sv.z;
    s32 sz = l.sv.z;
    s32 nz = pos->z;
    if (nz != sz) pos->y = pos->y - (nz - sz);
    s32 y = pos->y;
    if (y < 0x900 && y > 0x1000) pos->y = l.sv.y;
}

extern "C" s32 MuseumInsect_RandTurn(s32 n)
{
    return (s16)func_01ffcb0c(0x38e, (Random_GlobalBelow(n * 2 + 1) - n) << 12);
}

void MuseumInsect::setBounds(s32 *a, s32 *b)
{
    s32 y1 = func_01ffcb0c(a[1] << 12, 0x100);
    s32 x1 = func_01ffcb0c(a[0] << 12, 0x100);
    Vec2 *a2 = &boundsMin;
    a2->x = x1;
    a2->y = y1;
    s32 y2 = func_01ffcb0c(b[1] << 12, 0x100);
    s32 x2 = func_01ffcb0c(b[0] << 12, 0x100);
    Vec2 *b2 = &boundsMax;
    b2->x = x2;
    b2->y = y2;
}

void MuseumInsect::setBoundsAroundPos()
{
    VecFx32 *o = &position;
    s32 ay = o->z - 0x200;
    Vec2 *a = &boundsMin;
    a->x = o->x - 0x900;
    a->y = ay;
    s32 by = o->z + 0x500;
    Vec2 *b = &boundsMax;
    b->x = o->x + 0x900;
    b->y = by;
}

void MuseumInsect::init(u32 a, s32 b, s32 c, s16 d, s32 e, s32 f)
{
    VecFx32 *o = &position;
    VecFx32 *dv = &targetPos;
    dv->x = o->x;
    dv->y = o->y;
    dv->z = o->z;
    moveState = 0x19;
    yaw = d;
    pitch = c;
    alertThreshold = a;
    alertRange = func_01ffcb0c(b << 12, 0x100);
    speciesWork = 0;
    moveSpeed = f;
    unk_30 = 0;
    alertLevel = 0;
    s32 t = func_01ffcb0c(e << 12, 0x100);
    baseHeight = o->y + t;
    targetHeight = baseHeight;
    isAlerted = 0;
}

void MuseumInsect::updateButterfly() { MuseumInsect_RunButterfly(this); }

void MuseumInsect::setupFlyer(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    s32 t = func_01ffcb0c((c + 8) << 12, 0x1000);
    s32 r = func_01ffcb0c(t, 0x100);
    VecFx32 *s = &position;
    VecFx32 *dst = &homePos;
    dst->x = s->x;
    dst->y = s->y;
    dst->z = s->z;
    init(a, b, 0, 0, 0, d);
    cooldown = 0x28;
    stateTimer = (Random_GlobalBelow(10) + 0x10) * 0x14;
    flapPeriod = (u8)Random_GlobalBelow(0x12);
    dirFlag = 1;
    speciesWork = e;
    subCounter = 0;
    baseHeight = r;
    targetHeight = r;
    if (isActive == 0) {
        moveState = 6;
        s32 c2 = insectIndex;
        if (c2 != 0xa && c2 != 0x33) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(0x11, 1, 0x1000, 9);
        } else {
            ((AnimModel *)(&model))->setFrame(0);
        }
    }
}

void MuseumInsect::setupCommonButterfly() { setupFlyer(0xc8, 0x50, 0x25, 6, 0x119a); }

void MuseumInsect::setupYellowButterfly() { setupFlyer(0xc8, 0x50, 0x25, 6, 0x119a); }

void MuseumInsect::setupTigerButterfly() { setupFlyer(0xc8, 0x50, 0x28, 7, 0x1000); }

void MuseumInsect::setupPeacock() { setupFlyer(0xc8, 0x50, 0x28, 7, 0x1000); }

void MuseumInsect::setupMonarch() { setupFlyer(0xc8, 0x50, 0x2d, 7, 0xe66); }

void MuseumInsect::setupEmperor() { setupFlyer(0xc8, 0x50, 0x14, 9, 0x1000); }

void MuseumInsect::setupAgrias() { setupFlyer(0xc8, 0x50, 0x2d, 0xf, 0x1000); }

void MuseumInsect::setupBirdwing() { setupFlyer(0xc8, 0x50, 0x2d, 8, 0x1000); }

void MuseumInsect::updateMoth() { MuseumInsect_RunMoth(this); }

void MuseumInsect::setupMoth()
{
    VecFx32 *d = &homePos;
    init(0x96, 0x28, 1, (s16)0x8000, 0, 9);
    if (isActive == 0) {
        pitch = 0x2aa8;
    }
    cooldown = 0x3c;
    flapPeriod = (u8)Random_GlobalBelow(0x12);
    dirFlag = 1;
    targetHeight = 0;
    VecFx32 *s = &position;
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
    if (isActive == 0) {
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup(8, 1, 0x1000, 0);
    }
}

void MuseumInsect::setupFirefly()
{
    MuseumFireflyStackPad pad;
    if (isActive) {
        VecFx32 *v = &position;
        v->x = 0x7a00;
        v->y = 0x2d00;
        v->z = 0x12c00;
        init(0x5a, 0x50, 0, 0, 0, 4);
        cooldown = 0x3c;
        s32 a[2];
        s32 b[2];
        a[0] = 0;
        a[1] = 0xac;
        b[0] = 0x96;
        b[1] = 0x1ac;
        setBounds(a, b);
    } else {
        init(0x5a, 0x50, 0x3556, 0x6000, 0, 4);
    }
}

void MuseumInsect::updateFirefly() { MuseumInsect_RunFirefly(this); }

void MuseumInsect::setupMosquito() { init(0, 0, 0, 0, 0, 0xb); }

void MuseumInsect::updateMosquito() { MuseumInsect_RunMosquito(this); }

void MuseumInsect::setupPerched(s32 a, s32 b)
{
    init(a, b, 0x3556, (s16)0x8000, 0, 0);
    cooldown = 0;
}

void MuseumInsect::updatePerched() { ((MuseumInsect *)(this))->runPerched(); }

void MuseumInsect::setupHerculesBeetle() { setupPerched(0x5a, 0x3c); }

void MuseumInsect::setupElephantBeetle() { setupPerched(0x5a, 0x3c); }

void MuseumInsect::setupAtlasBeetle() { setupPerched(0x5a, 0x3c); }

void MuseumInsect::setupDynastidBeetle() { setupPerched(0x64, 0x3c); }

void MuseumInsect::setupSawStagBeetle() { setupPerched(0x64, 0x3c); }

void MuseumInsect::setupStagBeetle() { setupPerched(0x64, 0x3c); }

void MuseumInsect::setupGiantBeetle() { setupPerched(0x5a, 0x3c); }

void MuseumInsect::setupJewelBeetle() { setupPerched(0x82, 0x3c); }

void MuseumInsect::setupFruitBeetle() { setupPerched(0x82, 0x3c); }

void MuseumInsect::setupLonghornBeetle() { setupPerched(0x82, 0x3c); }

void MuseumInsect::setupRainbowStag() { setupPerched(0x82, 0x3c); }

void MuseumInsect::setupScarabBeetle() { setupPerched(0x5a, 0x3c); }

void MuseumInsect::setupGoliathBeetle() { setupPerched(0x5a, 0x3c); }

void MuseumInsect::setupWalkingstick() { setupPerched(0x28, 0x78); }

void MuseumInsect::setupOakSilkMoth()
{
    setupPerched(0x96, 0x46);
    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)model))->setup((u32)(model.numFrames << 4) >> 16, 1, 0x1000, 0);
}

void MuseumInsect::updateCicada() { ((MuseumInsect *)(this))->runCicada(); }

void MuseumInsect::setupBrownCicada() { setupPerched(0xc8, 0x3c); }

void MuseumInsect::setupRobustCicada() { setupPerched(0xc8, 0x3c); }

void MuseumInsect::setupWalkerCicada() { setupPerched(0xc8, 0x3c); }

void MuseumInsect::setupEveningCicada() { setupPerched(0xc8, 0x3c); }

void MuseumInsect::setupLanternFly()
{
    setupPerched(0xc8, 0x50);
    model.frameStep = 0;
}

extern "C" void MuseumInsect_SetupHopper(MuseumInsect *o, s32 a, s32 b, s32 c, u8 d) {
    s32 t = MuseumInsect_RandHeading();
    ((MuseumInsect *)(o))->init(a, b, 0, t, 0, DS_DIV(0x1000, c));
    o->subCounter = (Random_GlobalBelow(9) + 2) * 20;
    o->travelDistance = d;
}

extern "C" void MuseumInsect_UpdateHopper(MuseumInsect *o) { MuseumInsect_RunHopper(o); }

extern "C" void MuseumInsect_SetupGrasshopper(MuseumInsect *o) {
    MuseumInsect_SetupHopper(o, 0x3c, 0x46, 6, 1);
    s32 a[2], b[2];
    a[0] = 0x104;
    a[1] = 0xc2;
    b[0] = 0x1be;
    b[1] = 0x15a;
    ((MuseumInsect *)(o))->setBounds(a, b);
}

extern "C" void MuseumInsect_SetupCricket(MuseumInsect *o) {
    MuseumInsect_SetupHopper(o, 0x3c, 0x46, 6, 1);
    s32 a[2], b[2];
    a[0] = 0x104;
    a[1] = 0xc2;
    b[0] = 0x1be;
    b[1] = 0x15a;
    ((MuseumInsect *)(o))->setBounds(a, b);
}

extern "C" void MuseumInsect_SetupLongLocust(MuseumInsect *o) {
    MuseumInsect_SetupHopper(o, 0x3c, 0x50, 8, 2);
    s32 a[2], b[2];
    a[0] = 0x104;
    a[1] = 0xc2;
    b[0] = 0x1be;
    b[1] = 0x15a;
    ((MuseumInsect *)(o))->setBounds(a, b);
}

extern "C" void MuseumInsect_SetupMigratoryLocust(MuseumInsect *o) {
    MuseumInsect_SetupHopper(o, 0x3c, 0x50, 8, 3);
    s32 a[2], b[2];
    a[0] = 0x104;
    a[1] = 0xc2;
    b[0] = 0x1be;
    b[1] = 0x15a;
    ((MuseumInsect *)(o))->setBounds(a, b);
}

extern "C" void MuseumInsect_SetupBellCricket(MuseumInsect *o) {
    MuseumInsect_SetupHopper(o, 0x3c, 0x46, 8, 1);
    s32 a[2], b[2];
    a[0] = 0x104;
    a[1] = 0xc2;
    b[0] = 0x1be;
    b[1] = 0x15a;
    ((MuseumInsect *)(o))->setBounds(a, b);
}

extern "C" void MuseumInsect_SetupCockroach(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x3c, 0x46, 0, MuseumInsect_RandHeading(), 0, 0x26);
    o->stateTimer = (Random_GlobalBelow(10) + 3) * 20;
    o->subCounter = 0;
}

extern "C" void MuseumInsect_UpdateCockroach(MuseumInsect *o) { MuseumInsect_RunCockroach(o); }

extern "C" void MuseumInsect_UpdateDragonfly(MuseumInsect *o) { MuseumInsect_RunDragonfly(o); }

extern "C" void MuseumInsect_SetupDragonfly(MuseumInsect *o, s32 a, s32 b, s32 c, u8 d, u8 e, s32 f) {
    s32 t = MuseumInsect_RandHeading();
    ((MuseumInsect *)(o))->init(a, b, 0, t, c, DS_DIV(0x1000, d));
    o->travelDistance = e;
    o->speciesWork = f;
    VecFx32 *sv = &o->position;
    VecFx32 *dv = &o->homePos;
    dv->x = sv->x;
    dv->y = sv->y;
    dv->z = sv->z;
    if (o->isActive != 0) {
        if (Random_GlobalBelow(100) > 50) {
            o->stateTimer = 100;
            return;
        }
    }
    o->isPerched = 1;
}

extern "C" void MuseumInsect_SetupRedDragonfly(MuseumInsect *o) {
    if (Random_GlobalBelow(100) > 50) {
        VecFx32 *v = &o->position;
        v->x = 0x1a600;
        v->y = 0x1400;
        v->z = 0x13c00;
    }
    MuseumInsect_SetupDragonfly(o, 0xc8, 0x3c, 0x28, 0x14, 1, 0xcd);
}

extern "C" void MuseumInsect_SetupDarnerDragonfly(MuseumInsect *o) {
    if (Random_GlobalBelow(100) > 50) {
        VecFx32 *v = &o->position;
        v->x = 0x16600;
        v->y = 0x1400;
        v->z = 0x14200;
    }
    MuseumInsect_SetupDragonfly(o, 0xc8, 0x28, 0x2d, 0x1e, 3, 0x19a);
}

extern "C" void MuseumInsect_SetupBandedDragonfly(MuseumInsect *o) {
    if (Random_GlobalBelow(100) > 50) {
        VecFx32 *v = &o->position;
        v->x = 0x12b00;
        v->y = 0x1a00;
        v->z = 0xda00;
    }
    MuseumInsect_SetupDragonfly(o, 0x64, 0x28, 0x32, 0x78, 0x1e, 0x266);
}

extern "C" void MuseumInsect_SetupPondSkater(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x28, 0x50, 0, 0, 0, 1);
    s32 a[2], b[2];
    a[0] = 0x62;
    a[1] = 0x11a;
    b[0] = 0x92;
    b[1] = 0x13e;
    ((MuseumInsect *)(o))->setBounds(a, b);
    if (o->isActive != 0) {
        s32 t = Random_GlobalBelow(0x14);
        t *= Random_GlobalBelow(3);
        o->subCounter = t;
    } else {
        s32 t = Random_GlobalBelow(0x14);
        t *= Random_GlobalBelow(0xf);
        o->subCounter = t;
    }
}

extern "C" void MuseumInsect_UpdatePondSkater(MuseumInsect *o) { MuseumInsect_RunPondSkater(o); }

extern "C" void MuseumInsect_UpdateWalker(MuseumInsect *o) { ((MuseumInsect *)(o))->runWalker(); }

extern "C" void MuseumInsect_SetupSnail(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0xc8, 0x3c, 0, MuseumInsect_RandHeading(), 0, 1);
    ((MuseumInsect *)(o))->setBoundsAroundPos();
    o->speciesWork = 0x38e;
}

extern "C" void MuseumInsect_SetupLadybug(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x50, 0x3c, 0, MuseumInsect_RandHeading(), 0, 0x20);
    ((MuseumInsect *)(o))->setBoundsAroundPos();
    o->speciesWork = 0x71c;
}

extern "C" void MuseumInsect_SetupMantis(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0xa0, 0x3c, 0, MuseumInsect_RandHeading(), 0, 0x20);
    ((MuseumInsect *)(o))->setBoundsAroundPos();
    o->speciesWork = 0x71c;
}

extern "C" void MuseumInsect_SetupOrchidMantis(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0xa0, 0x46, 0, MuseumInsect_RandHeading(), 0, 0x20);
    ((MuseumInsect *)(o))->setBoundsAroundPos();
    o->speciesWork = 0x71c;
}

extern "C" void MuseumInsect_SetupMoleCricket(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0xc8, 0x3c, 0, 0, 0, 0);
    NNS_G3dMdlSetMdlAlpha(o->pooledModel.getModel(), 0, 0);
    s32 a[2], b[2];
    a[0] = 0xa6;
    a[1] = 0x106;
    b[0] = 0xfc;
    b[1] = 0x150;
    ((MuseumInsect *)(o))->setBounds(a, b);
}

extern "C" void MuseumInsect_UpdateMoleCricket(MuseumInsect *o) { MuseumInsect_RunMoleCricket(o); }

extern "C" void MuseumInsect_SetupPillBug(MuseumInsect *o) {
    u8 t = Random_GlobalBelow(5);
    if (Random_GlobalBelow(100) > 50) {
        o->dirFlag = 0;
    } else {
        o->dirFlag = 1;
    }
    o->speciesWork = t;
    ((MuseumInsect *)(o))->init(0x50, 0x50, 0, 0, 0, 1);
    MuseumInsect_GetPillBugWaypoint(&o->position, t);
    MuseumInsect_PillBugNextWaypoint(o);
    o->cooldown = 0;
    if (Random_GlobalBelow(100) > 50) {
        o->stateTimer = (Random_GlobalBelow(9) + 4) * 20;
        o->moveState = 4;
    } else {
        o->stateTimer = (Random_GlobalBelow(3) + 2) * 20;
        o->moveState = 0x19;
    }
}

extern "C" void MuseumInsect_UpdatePillBug(MuseumInsect *o) { MuseumInsect_RunPillBug(o); }

extern "C" void MuseumInsect_SetupHoneybee(MuseumInsect *o) {
    ((MuseumInsect *)(o))->setupFlyer(0x78, 0x3c, 0x25, 8, 0x1000);
    ((MuseumInsect *)(o))->setBoundsAroundPos();
}

extern "C" void MuseumInsect_UpdateHoneybee(MuseumInsect *o) { MuseumInsect_RunFlyingInsect(o); }

extern "C" void MuseumInsect_SetupFly(MuseumInsect *o) {
    ((MuseumInsect *)(o))->setupFlyer(0x1e, 0x14, 0x28, 0xf, 0x1000);
    o->speciesWork = 0x71c;
    VecFx32 *sv = &o->position;
    VecFx32 *dv = &o->homePos;
    dv->x = sv->x;
    dv->y = sv->y;
    dv->z = sv->z;
    o->homePos.y = 0xb00;
}

extern "C" void MuseumInsect_UpdateFly(MuseumInsect *o) { MuseumInsect_RunFlyingInsect(o); }

extern "C" void MuseumInsect_SetupSpider(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x5a, 0x40, 0, 0, 0, 0xf);
    o->speciesWork = o->position.x;
}

extern "C" void MuseumInsect_UpdateSpider(MuseumInsect *o) { ((MuseumInsect *)(o))->runSpider(); }

extern "C" void MuseumInsect_UpdateArachnid(MuseumInsect *o) { MuseumInsect_RunArachnid(o); }

extern "C" void MuseumInsect_SetupTarantula(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x50, 0x50, 0, MuseumInsect_RandHeading(), 0, 5);
    o->dirFlag = 0;
    MuseumInsect *p = ((MuseumInsect *)MuseumInsect_FindScorpion());
    if (p != 0) {
        s32 a[2], b[2];
        o->isFighting = 1;
        p->isFighting = 1;
        a[0] = 0x110;
        a[1] = 0x10c;
        b[0] = 0x14c;
        b[1] = 0x148;
        ((MuseumInsect *)(o))->setBounds(a, b);
    } else {
        s32 a[2], b[2];
        if (o->isActive != 0) {
            o->stateTimer = (s16)((Random_GlobalBelow(6) + 1) * 20);
        } else {
            o->stateTimer = (s16)((Random_GlobalBelow(0x1e) + 5) * 20);
        }
        a[0] = 0x104;
        a[1] = 0xc2;
        b[0] = 0x1be;
        b[1] = 0x15a;
        ((MuseumInsect *)(o))->setBounds(a, b);
    }
}

extern "C" void MuseumInsect_SetupScorpion(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x50, 0x50, 0, MuseumInsect_RandHeading(), 0, 5);
    o->dirFlag = 0;
    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(3, 0, 0x1000, 0);
    s32 a[2], b[2];
    a[0] = 0x104;
    a[1] = 0xc2;
    b[0] = 0x1be;
    b[1] = 0x15a;
    ((MuseumInsect *)(o))->setBounds(a, b);
    if (o->isActive != 0) {
        o->stateTimer = (s16)((Random_GlobalBelow(6) + 1) * 20);
    } else {
        o->stateTimer = (s16)((Random_GlobalBelow(0x1e) + 5) * 20);
    }
}

extern "C" void MuseumInsect_SetupBee(MuseumInsect *o) { ((MuseumInsect *)(o))->setupPerched(0x5a, 0x3c); }

extern "C" void MuseumInsect_UpdateBee(MuseumInsect *o) { ((MuseumInsect *)(o))->runPerched(); }

extern "C" void MuseumInsect_SetupFlea(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x28, 0x1e, 0, 0, 0, 0xf);
    o->stateTimer = (s16)Random_GlobalBelow(0x1e) + 10;
}

extern "C" void MuseumInsect_UpdateFlea(MuseumInsect *o) { MuseumInsect_RunFlea(o); }

extern "C" void MuseumInsect_SetupAnt(MuseumInsect *o) {
    ((MuseumInsect *)(o))->init(0x28, 0x1e, 0, 0, 0, 0xf);
    if (o->isActive == 0) {
        o->matAnim.frameStep = 0x666;
    }
}

extern "C" void MuseumInsect_UpdateAnt(MuseumInsect *o) {}

extern "C" void MuseumInsect_SetupDungBeetle(MuseumInsect *o) {
    if (o->insectIndex == 0x23) {
        MuseumInsect *p = ((MuseumInsect *)MuseumInsect_FindDungBall());
        if (Random_GlobalBelow(100) > 50) {
            s32 v = (s16)((Random_GlobalBelow(9) + 4) * 20);
            o->stateTimer = v;
            p->stateTimer = v;
            o->moveState = 4;
            p->moveState = 4;
        } else {
            s32 v = (s16)((Random_GlobalBelow(3) + 2) * 20);
            if (o->isActive == 0) {
                v = (s16)(v * 3);
            }
            o->stateTimer = v;
            p->stateTimer = v;
            o->model.frameStep = 0;
            o->moveState = 0x19;
            p->moveState = 0x19;
        }
    } else if (o->moveState == 0x19) {
        o->model.frameStep = 0;
    }
}

extern "C" void MuseumInsect_UpdateDungBeetle(MuseumInsect *o) { MuseumInsect_RunDungBeetle(o); }

extern "C" void MuseumInsect_InitPlacement(MuseumInsectRoom *m, MuseumInsect *s) {
    MuseumInsectPlaceStackPad pad;
    s32 *v = &s->position.x;
    u32 r = MuseumInsect_GetTimeOfDayBit();
    switch (s->insectIndex) {
    case 0x0:
        v[0] = 0x176; v[1] = 0x13; v[2] = 0x71;
        s->isActive = r & 0xc;
        break;
    case 0x1:
        v[0] = 0x170; v[1] = 0x13; v[2] = 0x9c;
        s->isActive = r & 0xc;
        break;
    case 0x2:
        v[0] = 0x17f; v[1] = 0x13; v[2] = 0x85;
        s->isActive = r & 0xc;
        break;
    case 0x3:
        v[0] = 0x177; v[1] = 0x13; v[2] = 0xd0;
        s->isActive = r & 0xc;
        break;
    case 0x4:
        v[0] = 0x184; v[1] = 0x13; v[2] = 0xb5;
        s->isActive = r & 0xc;
        break;
    case 0x5:
        v[0] = 0x187; v[1] = 0x13; v[2] = 0xe4;
        s->isActive = r & 0xc;
        break;
    case 0x6:
        v[0] = 0x178; v[1] = 0x13; v[2] = 0xfb;
        s->isActive = r & 0xc;
        break;
    case 0x7:
        v[0] = 0x170; v[1] = 0x13; v[2] = 0x123;
        s->isActive = r & 0xc;
        break;
    case 0x8:
        v[0] = 0x128; v[1] = 0x40; v[2] = 0x66;
        s->isActive = r & 0x21;
        break;
    case 0x9:
        v[0] = 0x82; v[1] = 0x1c; v[2] = 0x1aa;
        s->isActive = r & 0x21;
        break;
    case 0xa:
        v[0] = 0xd0; v[1] = 0x13; v[2] = 0xfc;
        s->isActive = r & 0xc;
        break;
    case 0xb:
        v[0] = 0x86; v[1] = 0x26; v[2] = 0x1a6;
        s->isActive = r & 0xe;
        break;
    case 0xc:
        v[0] = 0x146; v[1] = 0x8; v[2] = 0xf6;
        s->isActive = r & 0x1c;
        break;
    case 0xd:
        v[0] = 0x185; v[1] = 0x8; v[2] = 0x140;
        s->isActive = r & 0x1c;
        break;
    case 0xe:
        v[0] = 0xb5; v[1] = 0x13; v[2] = 0x141;
        s->isActive = r & 0xc;
        break;
    case 0xf:
        v[0] = 0x181; v[1] = 0x13; v[2] = 0x13f;
        s->isActive = r & 0xc;
        break;
    case 0x10:
        v[0] = 0x8e; v[1] = 0x24; v[2] = 0xd1;
        s->isActive = r & 0xc;
        break;
    case 0x11:
        v[0] = 0x8a; v[1] = 0x1a; v[2] = 0xd5;
        s->isActive = r & 0xc;
        break;
    case 0x12:
        v[0] = 0xbe; v[1] = 0x1a; v[2] = 0x4d;
        s->isActive = r & 0xc;
        break;
    case 0x13:
        v[0] = 0xb8; v[1] = 0x22; v[2] = 0x4b;
        s->isActive = r & 0x1a;
        break;
    case 0x14:
        v[0] = 0xf1; v[1] = 0x24; v[2] = 0x3d;
        s->isActive = r & 0x1b;
        break;
    case 0x15:
        v[0] = 0x16c; v[1] = 0x14; v[2] = 0xd2;
        s->isActive = r & 0x1c;
        break;
    case 0x16:
        v[0] = 0x132; v[1] = 0x14; v[2] = 0x10d;
        s->isActive = r & 0xc;
        break;
    case 0x17:
        v[0] = 0x178; v[1] = 0x14; v[2] = 0x122;
        s->isActive = r & 0xc;
        break;
    case 0x18:
        v[0] = 0x89; v[1] = 0x9; v[2] = 0x104;
        s->isActive = r & 0xc;
        break;
    case 0x19:
        v[0] = 0x7a; v[1] = 0x0; v[2] = 0x12c;
        s->isActive = r & 0x1c;
        break;
    case 0x1a:
        v[0] = 0xaa; v[1] = 0x13; v[2] = 0xfa;
        s->isActive = r & 0x1c;
        break;
    case 0x1b:
        v[0] = 0x15e; v[1] = 0x8; v[2] = 0x118;
        s->isActive = r & 0x33;
        break;
    case 0x1c:
        v[0] = 0x19f; v[1] = 0x8; v[2] = 0x11a;
        s->isActive = r & 0x33;
        break;
    case 0x1d:
        v[0] = 0x16f; v[1] = 0x8; v[2] = 0xf2;
        s->isActive = r & 0xc;
        break;
    case 0x1e:
        v[0] = 0xe2; v[1] = 0x8; v[2] = 0x13e;
        s->isActive = r & 0x3f;
        break;
    case 0x1f:
        v[0] = 0x1a2; v[1] = 0x24; v[2] = 0x4c;
        s->isActive = r & 0x1e;
        break;
    case 0x20:
        v[0] = 0x91; v[1] = 0x13; v[2] = 0xdf;
        s->isActive = r & 0xc;
        break;
    case 0x21:
        v[0] = 0x82; v[1] = 0x18; v[2] = 0x65;
        s->isActive = r & 0x33;
        break;
    case 0x22:
        v[0] = 0x88; v[1] = 0x22; v[2] = 0x62;
        s->isActive = r & 0x3;
        break;
    case 0x23: case 0x38:
        v[0] = 0x165; v[1] = 0x8; v[2] = 0xec;
        s->isActive = r & 0x23;
        break;
    case 0x24:
        v[0] = 0xae; v[1] = 0x2a; v[2] = 0xcd;
        s->isActive = r & 0x23;
        break;
    case 0x25:
        v[0] = 0x53; v[1] = 0x13; v[2] = 0x146;
        s->isActive = r & 0x21;
        break;
    case 0x26:
        v[0] = 0xeb; v[1] = 0x16; v[2] = 0x42;
        s->isActive = r & 0xc;
        break;
    case 0x27:
        v[0] = 0x122; v[1] = 0x22; v[2] = 0x52;
        s->isActive = r & 0xc;
        break;
    case 0x28:
        v[0] = 0x128; v[1] = 0x18; v[2] = 0x55;
        s->isActive = r & 0x23;
        break;
    case 0x29:
        v[0] = 0x15e; v[1] = 0x16; v[2] = 0x47;
        s->isActive = r & 0x23;
        break;
    case 0x2a:
        v[0] = 0x164; v[1] = 0x20; v[2] = 0x43;
        s->isActive = r & 0x3;
        break;
    case 0x2b:
        v[0] = 0x82; v[1] = 0x21; v[2] = 0x138;
        s->isActive = r & 0x23;
        break;
    case 0x2c:
        v[0] = 0x19c; v[1] = 0x16; v[2] = 0x51;
        s->isActive = r & 0x23;
        break;
    case 0x2d:
        v[0] = 0xaa; v[1] = 0x1a; v[2] = 0xd3;
        s->isActive = r & 0x23;
        break;
    case 0x2e:
        v[0] = 0x79; v[1] = 0x1a; v[2] = 0xe8;
        s->isActive = r & 0x23;
        break;
    case 0x2f:
        v[0] = 0x7d; v[1] = 0x2a; v[2] = 0xe2;
        s->isActive = r & 0x3;
        break;
    case 0x30:
        v[0] = 0x12c; v[1] = 0x0; v[2] = 0x12c;
        s->isActive = r & 0x3f;
        break;
    case 0x31:
        v[0] = 0x0; v[1] = 0x0; v[2] = 0x0;
        s->isActive = r & 0x3f;
        break;
    case 0x32:
        v[0] = 0xb4; v[1] = 0x19; v[2] = 0xfa;
        s->isActive = r & 0x3f;
        break;
    case 0x33:
        v[0] = 0x118; v[1] = 0x23; v[2] = 0xf0;
        s->isActive = r & 0x3f;
        break;
    case 0x34:
        v[0] = 0x14a; v[1] = 0x0; v[2] = 0xb4;
        s->isActive = r & 0x3f;
        break;
    case 0x35:
        v[0] = 0x96; v[1] = 0x29; v[2] = 0x133;
        s->isActive = r & 0x3f;
        break;
    case 0x36:
        v[0] = 0x134; v[1] = 0x8; v[2] = 0x11e;
        s->isActive = r & 0x21;
        break;
    case 0x37:
        v[0] = 0x128; v[1] = 0x8; v[2] = 0x136;
        s->isActive = r & 0x21;
        break;
    }
    v[0] = func_01ffcb0c(v[0] << 12, 0x100);
    v[1] = func_01ffcb0c(v[1] << 12, 0x100);
    v[2] = func_01ffcb0c(v[2] << 12, 0x100);
}

extern "C" void *MuseumInsectRoom_Create() {
    void *m = ProcBase::operator new(sizeof(MuseumInsectRoom));
    if (m) ::new (m) MuseumInsectRoom;
    return m;
}

extern "C" s32 MuseumInsectRoom_FindFreeSlot() {
    MuseumInsect *p = sMuseumInsects;
    u8 i;
    for (i = 0; i < 0x20; p++, i++) {
        if (p->loadState == 0) return i;
    }
    return -1;
}

extern "C" BOOL MuseumInsectRoom_AddInsect(MuseumInsectRoom *m, s8 v) {
    s32 i = MuseumInsectRoom_FindFreeSlot();
    BOOL z = FALSE;
    MuseumInsect *p;
    if (i != -1) {
    p = &sMuseumInsects[i];
    p->insectIndex = v;
    p->loadState = 1;
    m->modelPool.acquire(&p->modelSlot.index);
    p->pooledModel.reset();
    MuseumInsect_InitPlacement(m, p);
    p->matAnim.anmObj = 0;
    p->matAnim.resMdl = 0;
    return TRUE;
    }
    return z;
}

BOOL MuseumInsectRoom::onCreate() {
    modelPool.init(0x20, 0x400, 0x40, 0x9c4, (ModelSlotAllocFunc)MuseumInsectHeap_Create, MuseumInsectHeap_Destroy);
    spawnDonatedInsects();
    return TRUE;
}

extern "C" void MuseumInsectRoom_LoadInsect(MuseumInsectRoom *m, MuseumInsect *s) {
    void *sp8;
    ModelSlot *res;
    void *sp10;
    PooledModel *mdl;
    MuseumInsectParam *rec;
    void *sp1c;
    res = m->modelPool.acquire(&s->modelSlot.index);
    mdl = &s->pooledModel;
    char nm[0x10];
    char pth[0x18];
    char buf3[0x24];
    void *tmp;
    AnimModel *r6;
    BOOL ok;
    s32 t;

    func_02133ef8(nm, 0x11);
    func_02133ef8(pth + 1, 0x17);
    t = s->insectIndex;
    if (t == 0x25 && s->isActive == 0) {
        Str_SPrintf(nm, "/insect/51/bug57");
        sMuseumInsectParams[t].useVisAnim = 1;
    } else if (t == 0x18) {
        Str_SPrintf(nm, "/insect/61/bug%d", 0x3c);
    } else if (t == 0x23) {
        Str_SPrintf(nm, "/insect/61/bug61");
    } else if (t == 0x38) {
        Str_SPrintf(nm, "/insect/61/bug62");
    } else if (t < 10) {
        Str_SPrintf(nm, "/insect/01/bug0%d", t);
    } else if (t < 0x14) {
        Str_SPrintf(nm, "/insect/11/bug%d", t);
    } else if (t < 0x1e) {
        Str_SPrintf(nm, "/insect/21/bug%d", t);
    } else if (t < 0x28) {
        Str_SPrintf(nm, "/insect/31/bug%d", t);
    } else if (t < 0x32) {
        Str_SPrintf(nm, "/insect/41/bug%d", t);
    } else {
        Str_SPrintf(nm, "/insect/51/bug%d", t);
    }
    Str_SPrintf(pth + 1, "%s.nsbmd", nm);
    if (File_Exists(pth + 1)) {
        if (mdl->loadFromSlot(res, (const char *)(pth + 1))) {
            r6 = &s->model;
            ((Model *)(r6))->setResource((NNSG3dResMdl *)mdl->getModel(), NULL);
            rec = &sMuseumInsectParams[t];
            if (rec->useVisAnim) {
                Str_SPrintf(pth + 1, "%s.nsbva", nm);
            } else {
                Str_SPrintf(pth + 1, "%s.nsbca", nm);
            }
            if (File_Exists(pth + 1)) {
                sp10 = res->getHeap();
                if (t == 0x38) {
                    tmp = m->dungBallAnimFile = File_LoadAlloc(pth + 1, gCurrentHeap, 4, 0);
                } else if (t == 0x23) {
                    tmp = m->dungBeetleAnimFile = File_LoadAlloc(pth + 1, gCurrentHeap, 4, 0);
                } else {
                    tmp = File_LoadAlloc(pth + 1, sp10, 4, 0);
                }
                if (tmp) {
                    ok = TRUE;
                    if (rec->useVisAnim) {
                        sp8 = func_021067a4(func_02106788((u8 *)tmp), 0);
                    } else {
                        sp8 = func_021065f8(func_021065dc((u8 *)tmp), 0);
                    }
                    if (r6->allocAnmObj(sp10)) {
                        s32 k = 0x1000;
                        if (t == 0x35 || t == 9) k = 0;
                        ((BlendAnimModel *)(r6))->initAnim(sp8, 0, k, 0, 0);
                        r6->attachAnim();
                    }
                    if (t == 0x18) {
                        Str_SPrintf(buf3, "/insect/61/bug%d.nsbta", 0x3c);
                        ok = FALSE;
                        if (File_Exists(buf3)) {
                            void *file = File_LoadAlloc(buf3, sp10, 4, NULL);
                            if (file) {
                                sp1c = func_02106670(func_02106654((u8 *)file), ok);
                                if (s->matAnim.allocMatAnm(r6->resMdl, sp10)) {
                                    s->matAnim.init(sp1c, ok, 0x1000, ok);
                                    s->matAnim.addToRenderObj(r6->getRenderObj());
                                    ok = TRUE;
                                }
                            }
                        }
                    }
                    if (ok) {
                        sMuseumInsectBehaviors[t].setup(s);
                        ((SndEnvChannel *)(&s->sound))->callReset();
                        s->updateFn = sMuseumInsectBehaviors[t].update;
                        s->loadState = 2;
                    }
                }
            }
        }
    }
}

extern "C" void MuseumInsect_RevertOutOfBounds(MuseumInsectRoom *m, MuseumInsect *s, VecFx32 *p) {
    Vec2 *hi = &s->boundsMax;
    Vec2 *lo = &s->boundsMin;
    VecFx32 *v = &s->position;
    if (v->x < lo->x || v->x > hi->x) v->x = p->x;
    if (v->z < lo->y || v->z > hi->y) v->z = p->z;
}

void MuseumInsectRoom::updateInsect(MuseumInsect *e) {
    V3_7690 prev;
    V3_7690 p2;
    Mtx43 buf;
    V3_7690 t;
    V3_7690 out;
    V3_7690 q;
    u32 mode;
    s32 a;
    if (e->updateFn != 0) {
        StaticCollider *obj = &e->hitBox;
        V3_7690 *pos = &e->position;
        u8 id = e->insectIndex;
        prev = *pos;
        if (obj->isHit != 0) {
            pos->x = pos->x + obj->pushX;
            pos->z = pos->z + obj->pushZ;
            MuseumInsect_RevertOutOfBounds(this, e, &prev);
            if (((ActorCollider *)(obj))->isHitByGroup(0x40)) {
                V3_7690 *pv = &e->targetPos;
                *pv = *pos;
                if (id == 0x17) {
                    e->isBumped = 1;
                }
            } else if (((ActorCollider *)(obj))->isHitByGroup(0x80)) {
                e->isBumped = 1;
            }
        }
        e->updateFn(e);
        if (hasHitBox(id, e->moveState)) {
            p2 = *pos;
            if (id == 0x38) {
                if (Model_GetJointWorldMtx(&e->model, &buf, 0)) {
                    q = *(V3_7690 *)&buf.m[9];
                    WorldCurve_FromCurved(&p2, &q);
                }
                mode = 0x42;
                a = 0x1200;
            } else {
                switch (id) {
                case 0x0e:
                case 0x0f:
                case 0x1a:
                case 0x20:
                    mode = 0x82;
                    break;
                case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07:
                case 0x0a:
                case 0x25:
                case 0x33:
                    if (e->moveState != 0) {
                        mode = 0x82;
                        break;
                    }
                default:
                    mode = 0x80;
                }
                a = sMuseumInsectParams[id].radius;
            }
            Collision_Move(&e->moveResult, pos, &prev, e->yaw, sMuseumInsectParams[id].radius, 0, 0xb);
            ((StaticCollider *)(obj))->setupAtPos((VecFx32 *)(&p2), sMuseumInsectParams[id].radius, a, mode, 0xc0, 0, 0xff, 0x1000);
            ((ActorCollider *)(obj))->submit();
        }
        if (sMuseumInsectParams[id].useVisAnim == 0) {
            ((AnimModel *)(&e->model))->stepAnim();
            if (id == 0x18) {
                e->matAnim.step();
                *(s32 *)e->matAnim.anmObj = e->matAnim.curFrame;
            }
        }
        if (MuseumInsect_GetSe((s8)id, 0) > 0) {
            t = *pos;
            ((SndEnvChannel *)(&e->sound))->callUpdateRelative((VecFx32 *)(&t));
        }
        s32 r = WorldCurve_ToCurved(&out, &e->position);
        Mtx43_SetTranslate(&data_021f47e0, out.x, out.y, out.z);
        Mtx43_RotateX(&data_021f47e0, r + e->pitch);
        Mtx43_RotateY(&data_021f47e0, e->yaw);
        Mtx43_RotateZ(&data_021f47e0, e->roll);
        e->model.mtx = data_021f47e0;
    }
}

BOOL MuseumInsectRoom::hasHitBox(u32 id, u8 flag) {
    switch (id) {
    case 0x9: case 0xb: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x19:
    case 0x1f: case 0x21: case 0x22: case 0x23: case 0x24: case 0x26: case 0x27: case 0x28:
    case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x31:
    case 0x35:
        return FALSE;
    case 0x1e:
        if (flag != 4 && flag != 3) {
            return FALSE;
        }
        break;
    }
    return TRUE;
}

BOOL MuseumInsectRoom::onExecute() {
    u8 r[6];
    V3_7690 rect[3];
    BoxCollider obj[3];
    u8 n;
    s32 k = 0;
    s32 z = 0;
    u8 i = 0;
    u8 *q;
    if ((s32)param == 0) {
        rect[0].x = 0x3800;
        rect[0].z = 0x8000;
        r[3] = 0;
        rect[1].x = 0x3800;
        rect[1].z = 0x1a000;
        r[4] = 0;
        rect[2].x = 0x16000;
        rect[2].z = 0x1c800;
        r[5] = 1;
        n = 3;
    } else {
        rect[0].x = 0x1c800;
        rect[0].z = 0x8000;
        r[3] = 0;
        rect[1].x = 0x1c800;
        rect[1].z = 0x1a000;
        r[4] = 0;
        n = 2;
    }
    q = &r[3];
    for (i = 0; i < n; i++) {
        if (q[i]) {
            r[i] = BoxCollider_Register(&obj[i], 0x4000, 0x1000, 0x6000, &rect[i], k, NULL);
        } else {
            r[i] = BoxCollider_Register(&obj[i], 0x1000, 0x4000, 0x6000, &rect[i], z, NULL);
        }
    }
    MuseumInsect *e = sMuseumInsects;
    sMuseumInsectFrame++;
    updateObstacles();
    for (i = 0; i < 0x20; e++, i++) {
        switch (e->loadState) {
        case 1:
            MuseumInsectRoom_LoadInsect(this, e);
            break;
        case 2:
            updateInsect(e);
            break;
        }
    }
    for (i = 0; i < n; i++) {
        if (r[i]) {
            BoxCollider_Unregister(&obj[i]);
        }
    }
    return TRUE;
}

void MuseumInsectRoom::updateObstacles() {
    V3_7690 pos[4];
    s32 sb[4];
    s32 sc[4];
    s32 z = 0;
    u8 n;
    u8 i;
    if ((s32)param == 1) {
        pos[0].x = 0x13000;
        pos[0].y = 0x800;
        pos[0].z = 0xe300;
        sb[0] = 0x1000;
        sc[0] = 0x1000;
        pos[1].x = 0x19400;
        pos[1].y = 0x800;
        pos[1].z = 0xf300;
        sb[1] = 0x1000;
        sc[1] = 0x1000;
        pos[2].x = 0x10800;
        pos[2].y = 0x600;
        pos[2].z = 0xc600;
        sb[2] = 0xc00;
        sc[2] = 0x600;
        pos[3].x = 0x10800;
        pos[3].y = 0x600;
        pos[3].z = 0x15700;
        sb[3] = 0xc00;
        sc[3] = 0x600;
        n = 4;
    } else {
        pos[0].x = 0x7900;
        pos[0].y = 0x800;
        pos[0].z = 0xe100;
        sb[0] = 0x3c00;
        sc[0] = 0x800;
        pos[1].x = 0xaa00;
        pos[1].y = 0x800;
        pos[1].z = 0xcd00;
        sb[1] = 0x3c00;
        sc[1] = 0x800;
        n = 2;
    }
    for (i = 0; i < n; i++) {
        obstacleHitBoxes[i].setupAtPos(&pos[i], sc[i], sb[i], 0x42, 0x80, z, 0xff, 0x1000);
        obstacleHitBoxes[i].submit();
    }
}

BOOL MuseumInsectRoom::onDraw() {
    MuseumInsect *e = sMuseumInsects;
    s32 z0 = 0;
    s32 z1 = 0;
    u8 i = 0;
    for (; i < 0x20; e++, i++) {
        if (e->loadState == 2) {
            s8 id = e->insectIndex;
            AnimModel *obj = &e->model;
            if (id == 0x30) {
                V3_7690 v = sMuseumFleaDrawScale;
                obj->drawAnimated(&v);
            } else {
                obj->drawAnimated(NULL);
            }
            if (hasShadow(e)) {
                u32 r = NNS_G3dMdlGetMdlAlpha(e->pooledModel.getModel(), z1);
                CharaShadow_DrawFaded(&e->position, sMuseumInsectParams[id].radius, 0x9000, (u8)r);
            }
        }
    }
    return TRUE;
}

BOOL MuseumInsectRoom::hasShadow(MuseumInsect *e) {
    switch (e->insectIndex) {
    case 0x9: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x18: case 0x19:
    case 0x1f: case 0x21: case 0x22: case 0x23: case 0x24: case 0x26: case 0x27: case 0x28:
    case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x30:
    case 0x32: case 0x33: case 0x38:
        return FALSE;
    case 0x1e:
        if (e->moveState == 0x19) {
            return FALSE;
        }
        return TRUE;
    }
    return TRUE;
}

BOOL MuseumInsectRoom::onDelete() {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        releaseInsect(i);
    }
    modelPool.destroy();
    return TRUE;
}

void MuseumInsectRoom::spawnDonatedInsects() {
    u32 v = (s32)param;
    v = (u8)v;
    BOOL flag = FALSE;
    u8 i = flag;
    for (; i < 0x39; i++) {
        if (v == getInsectRoom(i)) {
            u16 tmp;
            u16 t;
            if (i < 0x38) {
                t = 0x12b0 + i;
            } else {
                t = 0x12b0;
            }
            tmp = t;
            if (i == 0x38) {
                if (flag) {
                    MuseumInsectRoom_AddInsect(this, i);
                }
            } else if (data_021ed0a0.isDonated(&tmp)) {
                MuseumInsectRoom_AddInsect(this, i);
                if (i == 0x23) {
                    flag = TRUE;
                }
            }
        }
    }
}

BOOL MuseumInsectRoom::getInsectRoom(u32 idx) {
    switch (idx) {
    case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7:
    case 0x8: case 0xa: case 0xe: case 0xf: case 0x19: case 0x1a: case 0x1e: case 0x20:
    case 0x24: case 0x25: case 0x2d: case 0x2e: case 0x2f: case 0x30: case 0x32: case 0x33:
    case 0x34:
        return FALSE;
    }
    return TRUE;
}

extern "C" MuseumInsect *MuseumInsect_FindScorpion() {
    s32 i = sMuseumScorpionSlot;
    if (i >= 0) {
        return &sMuseumInsects[i];
    }
    MuseumInsect *e = sMuseumInsects;
    u8 j;
    for (j = 0; j < 0x20; e++, j++) {
        if (e->insectIndex == 0x37 && e->loadState != 0) {
            sMuseumScorpionSlot = j;
            return e;
        }
    }
    return 0;
}

extern "C" MuseumInsect *MuseumInsect_FindDungBall() {
    s32 i = sMuseumDungBallSlot;
    if (i >= 0) {
        return &sMuseumInsects[i];
    }
    MuseumInsect *e = sMuseumInsects;
    u8 j;
    for (j = 0; j < 0x20; e++, j++) {
        if (e->insectIndex == 0x38 && e->loadState != 0) {
            sMuseumDungBallSlot = j;
            return e;
        }
    }
    return 0;
}

MuseumInsect::MuseumInsect() {
    insectIndex = -1;
    pooledModel.reset();
    updateFn = 0;
    loadState = 0;
}

MuseumInsect::~MuseumInsect() {
}

void MuseumInsectRoom::releaseInsect(s32 idx) {
    if (idx >= 0 && idx < 0x20) {
        MuseumInsect *r = (MuseumInsect *)&sMuseumInsects[idx];
        s32 t = r->insectIndex;
        if (t == 0x38) {
            Mem_Free((void *)dungBallAnimFile);
            dungBallAnimFile = 0;
        } else if (t == 0x23) {
            Mem_Free((void *)dungBeetleAnimFile);
            dungBeetleAnimFile = 0;
        }
        if (sMuseumInsectParams[t].useVisAnim != 0) {
            ((AnimModel *)(&r->model))->detachVisAnim();
        } else {
            ((AnimModel *)(&r->model))->detachJointAnim();
        }
        r->matAnim.anmObj = 0;
        r->matAnim.resMdl = 0;
        ((SndEnvChannel *)(&r->sound))->callRelease();
        r->insectIndex = -1;
        r->yaw = 0;
        r->loadState = 0;
        r->stateCounter = 0;
        r->moveState = 0x19;
        r->pooledModel.unload();
        modelPool.release(&r->modelSlot.index);
        r->updateFn = 0;
    }
}

MuseumInsectRoom::MuseumInsectRoom() {
}

MuseumInsectRoom::~MuseumInsectRoom() {
}

MuseumInsectAnim::MuseumInsectAnim() {
}

MuseumInsectAnim::~MuseumInsectAnim() {
}

extern "C" u32 MuseumInsect_GetTimeOfDayBit() {
    MinuteHour o;
    Clock_GetMinuteHour(&o);
    u32 v = o.hour;
    if (v >= 4 && v <= 7) return 2;
    if (v >= 8 && v <= 0xf) return 4;
    if (v == 0x10) return 8;
    if ((u8)(v + 0xef) <= 1) return 0x10;
    if (v >= 0x13 && v <= 0x16) return 0x20;
    return 1;
}


extern "C" void StaticInit_unk_ov004_02237440(void) {
    HOST_STATIC_CONSTRUCT(sMuseumInsects);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov004_02237440) {
    HOST_OVERLAY_VAR(sMuseumInsectRoomProfile),
    HOST_OVERLAY_VAR(sMuseumScorpionSlot),
    HOST_OVERLAY_VAR(sMuseumDungBallSlot),
    HOST_OVERLAY_VAR(sMuseumFleaDrawScale),
    HOST_OVERLAY_VAR(sMuseumInsectParams),
    HOST_OVERLAY_VAR(sMuseumInsectBehaviors),
    HOST_OVERLAY_VAR(sMuseumInsectFrame),
    HOST_OVERLAY_VAR(sMuseumInsects),
    HOST_OVERLAY_VARS_END
};

#include "ds_div.h"
#include "host_tick.h"
#include "host_overlay_vars.h"
#include "uptr.h"
#include "proto/ov003/unk_ov003_022187fc.h"
#include "proto/main/unk_0202fa70.h"
#include "proto/main/unk_02002b1c.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/ModelSlotPool.h"
#include "snd/SndEnvChannel.h"
#include "game/GroundInfoBase.h"
#include "game/CollisionState.h"
#include "game/FxVec3.h"
#include "gfx/ModelAnim.h"
#include "game/GroundInfo.h"
#include "snd/CreatureSndChannel.h"
#include "gfx/AnimModel.h"
#include "game/BugNetTarget.h"
#include "gfx/PooledModel.h"
#include "town/BuildingActor.h"
#include "actor/VillagerActor.h"
#include "sys/ProcProfile.h"
#include "field/Insect.h"
#include "field/InsectSpawnList.h"
#include "field/InsectNetSync.h"
#include "field/Snowball.h"
#include "game/StrBSizeData.h"
#include "gfx/Model.h"
#include "gfx/TwoLayerAnimModel.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0208f268.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/ov003/unk_ov003_0222e5e0.h"
#include "proto/main/unk_0204cc1c.h"

extern "C" {
void GroundInfo_Destruct(void *obj);
s32 Ground_GetDefaultY(void);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
s32 Math_ApproachS32(s32 *p, s32 target, s32 ratio, s32 max, s32 min);
s32 Math_ApproachVecXZ(VecFx32 *p, VecFx32 *target, s32 ratio, s32 max, s32 min);
void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
s32 _s32_div_f(s32 a, s32 b);
}









class InsectManager : public GameProc, public InsectNetSync {
public:
    InsectManager();
    virtual ~InsectManager();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    BOOL allocFieldInsect(Insect *e);
    BOOL allocSpecialInsect(s32 id, s32 idx);
    BOOL allocHeldInsect(Insect *e);
    void freeInsect(Insect *e, s32 mode);

    /* 0x50 */ ModelSlotPool fieldInsectPool;
    /* 0x68 */ ModelSlotPool specialInsectPool;
    /* 0x80 */ ModelSlotPool heldInsectPool;
    /* 0x98 */ void *specialAnimFiles[2];
};


extern "C" { Insect sFieldInsects[8]; }
extern "C" { u16 data_ov003_02258f10; }
extern "C" { u8 sWateringActive; }
extern "C" { u16 sInsectSpawnMaskDry[4][4][16]; }
extern "C" { Insect sSpecialInsects[2]; }
extern "C" { s8 sTrashFlySpawnEnabled; }
extern "C" { u8 sAntSpawnEnabled; }
extern "C" { Insect sHeldInsects[4]; }
extern "C" { u8 data_ov003_02258f08; }
extern "C" { u8 data_ov003_02258f04; }
extern "C" { u8 sInsectSpawnTimer; }
extern "C" { u16 sInsectSpawnMaskLand[4][4][16]; }
struct InsectModelParams {
    u8 hasVisAnim;
    u8 unk_01;
    u16 collisionRadius;
    u16 netRadius;
};
extern "C" InsectModelParams sInsectModelParams[60] = {
    {0x0, 0x0, 0x514, 0x640}, {0x0, 0x0, 0x514, 0x640},
    {0x0, 0x0, 0x6a4, 0x6a4}, {0x0, 0x0, 0x6a4, 0x6a4},
    {0x0, 0x0, 0x6a4, 0x6a4}, {0x0, 0x0, 0x708, 0x708},
    {0x0, 0x0, 0x640, 0x640}, {0x0, 0x0, 0x898, 0x898},
    {0x0, 0x0, 0x6a4, 0x6a4}, {0x0, 0x0, 0x960, 0xbb8},
    {0x1, 0x0, 0x44c, 0x640}, {0x1, 0x0, 0x4b0, 0x578},
    {0x1, 0x0, 0x640, 0x640}, {0x1, 0x0, 0x514, 0x514},
    {0x0, 0x0, 0x578, 0x898}, {0x0, 0x0, 0x514, 0x640},
    {0x1, 0x0, 0x514, 0x9c4}, {0x1, 0x0, 0x514, 0x9c4},
    {0x1, 0x0, 0x4b0, 0x9c4}, {0x1, 0x0, 0x4b0, 0x9c4},
    {0x0, 0x0, 0x578, 0x9c4}, {0x1, 0x0, 0x578, 0x578},
    {0x1, 0x0, 0x708, 0x708}, {0x1, 0x0, 0x898, 0x898},
    {0x1, 0x0, 0x514, 0x3e8}, {0x1, 0x0, 0x514, 0xaf0},
    {0x1, 0x0, 0x3e8, 0x578}, {0x1, 0x0, 0x44c, 0x44c},
    {0x1, 0x0, 0x3e8, 0x3e8}, {0x1, 0x0, 0x4b0, 0x578},
    {0x1, 0x0, 0x3e8, 0x708}, {0x1, 0x0, 0x514, 0xaf0},
    {0x1, 0x0, 0x3e8, 0x578}, {0x1, 0x0, 0x4b0, 0x9c4},
    {0x1, 0x0, 0x4b0, 0x9c4}, {0x1, 0x0, 0x4b0, 0x898},
    {0x1, 0x0, 0x640, 0xa28}, {0x0, 0x0, 0x44c, 0x640},
    {0x1, 0x0, 0x4b0, 0x9c4}, {0x1, 0x0, 0x514, 0x9c4},
    {0x1, 0x0, 0x578, 0x9c4}, {0x1, 0x0, 0x578, 0x9c4},
    {0x1, 0x0, 0x578, 0x9c4}, {0x1, 0x0, 0x514, 0x9c4},
    {0x1, 0x0, 0x578, 0x9c4}, {0x1, 0x0, 0x640, 0xa28},
    {0x1, 0x0, 0x640, 0xa28}, {0x1, 0x0, 0x708, 0xaf0},
    {0x1, 0x0, 0x708, 0x708}, {0x1, 0x0, 0x190, 0x640},
    {0x1, 0x0, 0x1, 0x4b0}, {0x1, 0x0, 0x3e8, 0x4b0},
    {0x1, 0x0, 0x514, 0x9c4}, {0x0, 0x0, 0x3e8, 0x578},
    {0x0, 0x0, 0x7d0, 0x9c4}, {0x0, 0x0, 0x7d0, 0x9c4},
    {0x0, 0x0, 0x3e8, 0x3e8}, {0x1, 0x0, 0x44c, 0x640},
    {0x0, 0x0, 0xbb8, 0xbb8}, {0x0, 0x0, 0x7d0, 0x9c4},
};
extern "C" s32 Insect_CheckObstacle(Insect * o, s32 a, s32 b);
extern "C" u32 Insect_TestFeelers(Insect * o);
extern "C" u32 Insect_TestFeelersHole(Insect * o);
extern "C" s32 Insect_SetFeelers(Insect * o, s32 a, s32 b);
extern "C" void Insect_GetDirVec(VecFx32Ctor * o, s32 a);
extern "C" s32 Insect_IsOverWater(VecFx32 * v);
extern "C" void Insect_CheckTurnCount(Insect * o, s32 n);
extern "C" s32 Insect_SetMoveTarget(Insect * o, u32 ang, s32 d);
extern "C" s32 Insect_SetGroundMoveTarget(Insect * o, u32 ang, s32 n);
extern "C" Actor * Insect_FindNearestPlayer(VecFx32 * pos);
extern "C" void Insect_UpdateRest(Insect * o);
extern "C" s32 Insect_LikesFlower(s32 a, u16 * b);
extern "C" s32 Insect_SplashIfWater(Insect * o);
extern "C" s32 Insect_CheckDigHit(Insect * o, VecFx32Ctor * a);
extern "C" void Insect_PlaySe(Insect * o, s32 a, s32 b);
extern "C" s32 Insect_GetSeId(s32 a, s32 b);
extern "C" void Insect_FlutterPullBack(Insect * self, VecFx32Ctor * p, s32 a);
extern "C" void Insect_SetFlutterTurnDelay(Insect * self);
extern "C" s32 Insect_GetFlutterLeash(Insect * self);
extern "C" s32 Insect_GetFlutterRange(Insect * self);
extern "C" s32 Insect_GetFlutterTargetSpeed(Insect * self);
extern "C" void Insect_FlutterSteer(Insect * self, s16 * p, s32 a, s32 b, u8 e, s32 f);
extern "C" void Insect_FlutterBob(Insect * self, s32 a, s32 b, s32 c);
extern "C" s32 Insect_CheckAlarm(Insect * self);
extern "C" void Insect_FleeIfAlarmed(Insect * self, VecFx32Ctor * p);
extern "C" void Insect_FlapWings(Insect * self);
extern "C" void Butterfly_Update(Insect * self);
extern "C" void Insect_FlutterFlight(Insect * self);
extern "C" s32 Insect_TickTimer(Insect * self);
extern "C" void Insect_FlyAwayArc(Insect * self, s32 a);
extern "C" void Insect_FlutterAltitude(Insect * self, s16 * cnt);
extern "C" s32 Insect_GetFlowerSpeciesMask(s32 a);
extern "C" void Dragonfly_Update(Insect * self);
extern "C" void Dragonfly_Hover(Insect * self, s16 * cnt);
extern "C" void Dragonfly_FlyToTarget(Insect * self);
extern "C" void Dragonfly_FlyOff(Insect * self, s16 * cnt);
extern "C" void Dragonfly_CheckObstacle(Insect * self);
extern "C" s32 Insect_ReflectAngle(s32 a, s32 mode);
extern "C" s32 Insect_TurnToTarget(Insect * self, u32 a);
extern "C" void Insect_AccumAlarm(Insect * o, VecFx32Ctor * out, s32 * dist, u8 * flag, u8 a, u8 b);
extern "C" s32 Insect_UpdateAlarm(Insect * o, VecFx32Ctor * out);
extern "C" void Hopper_Update(Insect * o);
extern "C" void Hopper_Rest(Insect * o, s16 * p);
extern "C" s16 Insect_RandomTurn(s32 a, s32 b);
extern "C" void Hopper_Jump(Insect * o);
extern "C" s32 Hopper_CheckObstacle(Insect * o, s16 * p);
extern "C" void Locust_PlaySe(Insect * o);
extern "C" void Cricket_Chirp(Insect * o);
extern "C" void Pondskater_Update(Insect * o);
extern "C" void Mosquito_Update(Insect * o);
extern "C" void Firefly_Update(Insect * o);
extern "C" void Firefly_Wander(Insect * o);
extern "C" void Bee_Update(Insect * o);
extern "C" void Hoverer_Update(Insect * self);
extern "C" void Ant_Update(Insect * self);
extern "C" void MoleCricket_Update(Insect * self);
extern "C" void MoleCricket_CheckDugUp(Insect * self, s16 * cnt);
extern "C" void Insect_HopArc(Insect * self, s16 * cnt);
extern "C" void Insect_EscapeRun(Insect * self, s16 * cnt);
extern "C" void MoleCricket_Burrow(Insect * self, s16 * cnt);
extern "C" s32 Insect_SteerAroundObstacle(Insect * self);
extern "C" void PillBug_Update(Insect * self);
extern "C" void PillBug_Curled(Insect * self);
extern "C" void PillBug_Walk(Insect * self);
extern "C" s32 Insect_CheckRockStrike(Insect * self, s16 * out);
extern "C" void Moth_Update(Insect * self);
extern "C" void Flea_Update(Insect * self);
extern "C" void Stinger_Update(Insect * self);
extern "C" void DungBeetle_Update(Insect * self);
extern "C" s32 Insect_FadeOut(Insect * self, s32 a);
extern "C" s32 Insect_GroundWalk(Insect * self);
extern "C" s32 Insect_GroundWalkNet(Insect * self);
extern "C" void Insect_ClampStepXZ(VecFx32Ctor * out, VecFx32Ctor * in, s32 c);
extern "C" void Spider_Update(Insect * self);
extern "C" void TreeBug_Update(Insect * self);
extern "C" void TreeBug_Idle(Insect * self, s16 * cnt);
extern "C" void TreeBug_ClimbUp(Insect * self, s16 * cnt);
extern "C" void TreeBug_ClimbDown(Insect * self, s16 * cnt);
extern "C" void TreeBug_Wiggle(Insect * self, s16 * cnt);
extern "C" void TreeBug_FlyOff(Insect * self, s16 * cnt);
extern "C" void TreeBug_DropAndFly(Insect * o, s16 * p);
extern "C" void Walkingstick_CheckAlarm(Insect * o, s16 * p);
extern "C" void TreeBug_CheckAlarm(Insect * o, s16 * p);
extern "C" void Crawler_Update(Insect * o);
extern "C" s32 Insect_IsOnFlower(VecFx32 * pp);
extern "C" void Crawler_Watch(Insect * o, s16 * p);
extern "C" void Crawler_Wander(Insect * o);
extern "C" void Insect_PlaceOnPlantSide(Insect * o);
extern "C" void Insect_SetWanderBox(Insect * self);
extern "C" void Insect_Despawn(Insect * self);
extern "C" void Crawler_Escape(Insect * self, s16 * pp);
extern "C" void Insect_InitBehavior(Insect * self, s16 a1, s32 a2, s32 a3, s16 s0, s16 s1, s32 s2, s32 s3, u32 s4, u32 s5);
extern "C" s16 Insect_RandomAngle();
extern "C" void Insect_UpdateButterfly(Insect * self);
extern "C" void Insect_InitFlutter(Insect * self, s32 a, s32 b, s32 c, u8 d, s32 e);
extern "C" void Insect_InitButterfly(Insect * self);
extern "C" void Insect_UpdateMoth(Insect * self);
extern "C" void Insect_InitMoth(Insect * self);
extern "C" void Insect_InitFirefly(Insect * self);
extern "C" void Insect_UpdateFirefly(Insect * self);
extern "C" void Insect_InitMosquito(Insect * self);
extern "C" void Insect_UpdateMosquito(Insect * self);
extern "C" void Insect_PlaceOnTrunk(Insect * self, s32 a, s32 b, s32 c, s32 d);
extern "C" void Insect_UpdateTreeBug(Insect * self);
extern "C" void Insect_InitTreeBug(Insect * self);
extern "C" void Insect_InitHop(Insect * self, s32 a, s32 b, s32 c, u8 d);
extern "C" void Insect_UpdateHopper(Insect * self);
extern "C" void Insect_InitHopper(Insect * self);
extern "C" void Insect_InitDragonflyParams(Insect * a, s32 x, s32 y, s32 z, u8 p4, u8 p5);
extern "C" void Insect_InitDragonfly(Insect * a);
extern "C" void Insect_UpdateDragonfly(Insect * a);
extern "C" void Insect_InitPondskater(Insect * a);
extern "C" void Insect_UpdatePondskater(Insect * a);
extern "C" void Insect_InitOnPlant(Insect * a, s32 x, s32 y, s32 z, s16 w);
extern "C" void Insect_UpdateCrawler(Insect * a);
extern "C" void Insect_InitCrawler(Insect * a);
extern "C" void Insect_InitBurrower(Insect * a);
extern "C" void Insect_UpdateMoleCricket(Insect * a);
extern "C" void Insect_UpdatePillBug(Insect * a);
extern "C" void Insect_InitBee(Insect * a);
extern "C" void Insect_UpdateBee(Insect * a);
extern "C" void Insect_InitHoneybee(Insect * a);
extern "C" void Insect_UpdateHoneybee(Insect * a);
extern "C" void Insect_InitFly(Insect * a);
extern "C" void Insect_UpdateFly(Insect * a);
extern "C" void Insect_InitFlea(Insect * a);
extern "C" void Insect_UpdateFlea(Insect * a);
extern "C" void Insect_InitSpider(Insect * a);
extern "C" void Insect_UpdateSpider(Insect * a);
extern "C" void Insect_UpdateStinger(Insect * a);
extern "C" void Insect_InitTarantula(Insect * a);
extern "C" void Insect_InitScorpion(Insect * a);
extern "C" void Insect_InitAnt(Insect * a);
extern "C" void Insect_UpdateAnt(Insect * a);
extern "C" void Insect_InitDungBeetle(Insect * a);
extern "C" void Insect_UpdateDungBeetle(Insect * a);
extern "C" void Insect_InitKind38(Insect * a);
extern "C" void Insect_UpdateKind38(Insect * a);
extern "C" void * InsectManager_Create();
extern "C" void Insect_LoadModel(InsectManager * a, Insect * e, s32 mode);
extern "C" void Insect_UpdateHideTimer(InsectManager * a, Insect * e);
extern "C" void Insect_Update(InsectManager * a, Insect * e, s32 flags, s32 kind);
extern "C" void Insect_CheckDisturbance(InsectManager * a, Insect * e);
extern "C" s32 FieldInsect_GetKindAndAlarm(u8 * out, u32 idx);
extern "C" s32 FieldInsect_IsTreeKind(u32 idx);
extern "C" s32 FieldInsect_GetPosAndKind(VecFx32Ctor * out, u32 idx);
extern "C" void Insect_UpdateSpawning(InsectManager * self);
extern "C" void FieldInsect_UpdateAll(InsectManager * a);
extern "C" s32 Insect_IsNetKindMismatch(InsectManager * a, Insect * o, s32 c, s32 d, s32 e);
extern "C" s32 Insect_IsTreeStillThere(InsectManager * a, Insect * o);
extern "C" void SpecialInsect_UpdateAll(InsectManager * a);
extern "C" void HeldInsect_UpdateAll(InsectManager * a);
extern "C" s32 Insect_UsesCollisionMove(InsectManager * a, Insect * o);
extern "C" void HeldInsect_Release(s32 idx, s32 v);
extern "C" u32 HeldInsect_GetStage(s32 idx);
extern "C" s32 InsectPool_Draw(InsectManager * a, Insect * o, s32 n);
extern "C" s32 Insect_IsTreeKindForCulling(InsectManager * a, s32 t);
extern "C" VecFx32Ctor * HeldInsect_GetPos(s32 idx);
extern "C" void HeldInsect_Start(s32 t, s32 idx);
extern "C" void Insect_OnNetRemove(s32 id);
extern "C" s32 Insect_CanHopAway(s32 t);
extern "C" void Insect_OnClaimGranted(s32 id);
extern "C" void HeldInsect_Remove(u8 id, s32 flag);
extern "C" s32 Insect_FinishCatch(u8 id);
extern "C" s32 Insect_GetCatchResult(s32 id);
extern "C" void Insect_CancelCatch(s32 id);
extern "C" s32 Insect_TryCatch(u8 id);
extern "C" void Insect_SetScale(Insect * o, s32 v);
extern "C" void Insect_Draw(InsectManager * a, Insect * o);
extern "C" s32 Insect_HasShadow(InsectManager * a, Insect * o);
extern "C" void Insect_SetModelMatrix(InsectManager * a, Insect * o, s32 flag);
extern "C" void InsectPool_UpdateInViewOfPlayer(InsectManager * obj, s32 flag, s32 idx, s32 x, s32 z);
extern "C" void InsectPool_UpdateInView(InsectManager * obj, s32 flag);
extern "C" void Insect_EnableTrashFlies();
extern "C" s32 Insect_Spawn(void * obj, s32 kind, u8 sub, s32 flag);
extern "C" s32 Insect_TrySpawnRandom(InsectManager * a, s32 b, u8 c, u32 d);
extern "C" void Insect_SpawnBeeSwarm(VecFx32Ctor * v);
extern "C" s32 HeldInsect_SetHandMatrix(s32 idx, s16 * p, Mtx43 * q, s32 flag);
extern "C" s32 Insect_NetClaim(s32 x);
extern "C" s32 Insect_IsBeeSwarmOut();
extern "C" s32 Insect_IsAtWateringPoint(VecFx32 * p);
extern "C" s32 Insect_RollKind(u8 * out);
extern "C" s32 Insect_GetTimeSlot();
extern "C" void Insect_TickFrame(Insect * self);
extern "C" void Insect_SetAnimSpeed(Insect * self, u32 v);
extern "C" s32 Insect_PickSpecialSpawn(s8 * a, s8 * b, s32 c);
extern "C" s32 Insect_IsAllowedOnline(s32 a);
extern "C" s32 Insect_RollFromSpawnTable(u32 a, u32 b, u8 * out);
extern "C" void FieldInsect_PurgeStale();
extern "C" s32 Insect_GetWeatherReaction(s32 a, s32 b);
extern "C" void InsectSpawn_CopyMask(void * p, s32 t);
extern "C" s32 InsectSpawn_PickPos(Insect * self, u16 * a, s32 code, u32 flag);
extern "C" void InsectSpawn_BuildLightMask(u16 (*arr)[4][16]);
extern "C" void InsectSpawn_ClearLitUnits(u16 (*arr)[4][16]);

extern "C" { u16 sFieldInsectPurgeTimer; }
extern "C" { u8 sInsectCatchResult; }
extern "C" ProcProfile sInsectManagerProfile = {(void *(*)())InsectManager_Create, 0xbc, 0xc0};
struct InsectBehavior {
    void (*init)(Insect *o);
    void (*update)(Insect *o);
};
extern "C" InsectBehavior sInsectBehaviors[60] = {
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitButterfly, Insect_UpdateButterfly},
    {Insect_InitMoth, Insect_UpdateMoth},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitHoneybee, Insect_UpdateHoneybee},
    {Insect_InitBee, Insect_UpdateBee},
    {Insect_InitHopper, Insect_UpdateHopper},
    {Insect_InitHopper, Insect_UpdateHopper},
    {Insect_InitCrawler, Insect_UpdateCrawler},
    {Insect_InitCrawler, Insect_UpdateCrawler},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitDragonfly, Insect_UpdateDragonfly},
    {Insect_InitDragonfly, Insect_UpdateDragonfly},
    {Insect_InitDragonfly, Insect_UpdateDragonfly},
    {Insect_InitAnt, Insect_UpdateAnt},
    {Insect_InitPondskater, Insect_UpdatePondskater},
    {Insect_InitCrawler, Insect_UpdateCrawler},
    {Insect_InitHopper, Insect_UpdateHopper},
    {Insect_InitHopper, Insect_UpdateHopper},
    {Insect_InitHopper, Insect_UpdateHopper},
    {Insect_InitBurrower, Insect_UpdateMoleCricket},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitCrawler, Insect_UpdateCrawler},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitDungBeetle, Insect_UpdateDungBeetle},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitFirefly, Insect_UpdateFirefly},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitFlea, Insect_UpdateFlea},
    {Insect_InitBurrower, Insect_UpdatePillBug},
    {Insect_InitMosquito, Insect_UpdateMosquito},
    {Insect_InitFly, Insect_UpdateFly},
    {Insect_InitTreeBug, Insect_UpdateTreeBug},
    {Insect_InitSpider, Insect_UpdateSpider},
    {Insect_InitTarantula, Insect_UpdateStinger},
    {Insect_InitScorpion, Insect_UpdateStinger},
    {Insect_InitKind38, Insect_UpdateKind38},
    {Insect_InitFirefly, Insect_UpdateFirefly},
    {Insect_InitBee, Insect_UpdateBee},
    {Insect_InitAnt, Insect_UpdateAnt},
};

extern "C" { FxVec3NoCtor sWateringPos; }

#define func_02133150 _s32_div_f
namespace s00 {


struct MinuteHour {
    u8 minute;
    u8 hour;
};

struct DayMonth {
    u8 day;
    u8 month;
};

extern "C" {
extern u8 sAntSpawnEnabled;
extern u8 sWateringActive;
extern u8 data_ov003_02258f04;
extern u8 data_ov003_02258f08;
extern u16 data_ov003_02258f10;
extern u16 sFieldInsectPurgeTimer;
extern Insect sFieldInsects[];
extern InsectSpawnList *gInsectSpawnTables[];
extern CommManager *gCommManager;
extern u8 data_0213b91c[];
extern u8 data_0213b954[];
void *__cxa_vec_ctor(void *, s32, s32, void *(*)(void *), void *(*)(void *));
void *__cxa_vec_cleanup(void *, s32, s32, void *(*)(void *));
void *FxVec3_Construct(void *);
void *func_02000c8c(void *);
u16 Item_MakeBuilding(u32 a);
void *StrBSize_Get(u16 *p);
BOOL InsectSpawn_FindUnitInBlock(void *a, s32 code, s32 *x, s32 *y, void *obj, s32 flag);
Actor *PlayerActor_GetActor(u32 n);
s32 Vec_DistXZ(void *a, void *b);
s32 Weather_GetFallingPrecip();
BOOL Town_GetRafflesiaPos(void *buf);
void Clock_GetMinuteHour(void *p);
void Clock_GetDayMonth(void *p);
void func_0209c128(void *p);
void func_0209c140(void *p);
void func_0209c0c8(void *p);
void func_02088b6c(void *p);
void func_02088b7c(void *p);
void func_020548a0(void *p);
void func_020548d0(void *p);
void func_0203239c(void *p);
void func_020323b0(void *p);
}


}

#undef func_02133150

namespace s01 {


struct InsectSpawnMask {
    u16 rows[4][4][16];
};


typedef Insect Rec;


typedef InsectSpawnMask Buf;

extern "C" {
extern CommManager *gCommManager;
extern void *gCamera;
extern VecFx32Ctor gCameraLookAt;
extern s16 data_02135f44[];
extern Rec sFieldInsects[];
extern Rec sSpecialInsects[];
extern Rec sHeldInsects[];
u32 NNS_G3dMdlGetMdlAlpha(void *res, u32 i);
s32 func_01ffcb0c(s32 a, s32 b);
s32 Weather_GetFallingPrecip(void);
s32 NetArea_IsLocalOwner(void);
u8 Insect_GetHabitat(u8 v);
Actor *PlayerActor_GetActor(u32 n);
s32 PlayerActor_GetSlotPosXZ(u8 *a, s32 *b, s32 *c, s32 d, s32 e);
s32 Vec_DistXZ(void *a, void *b);
void Mem_Free(void *p);
void Town_ClearBeesReleased(void);
void SpawnMask_MarkRect(u16 *buf, s32 x, s32 y, s32 rad, u8 a, u8 b);
Snowball *Snowball_GetLooseBall(u32 id);
s32 Snowball_GetRadius(Snowball *o);
}

}


namespace s02 {

typedef VecFx32Ctor V3;

typedef Mtx43 Blk;


typedef Insect Obj;

extern "C" {
extern Obj sFieldInsects[];
extern Obj sSpecialInsects[];
extern Obj sHeldInsects[];
extern u8 sInsectCatchResult;
extern CommManager *gCommManager;
extern Blk data_021f47e0;
extern s16 data_02135f44[];
s32 Mtx43_SetTranslate(void *m, s32 x, s32 y, s32 z);
s32 Mtx43_RotateY(void *m, s32 a);
s32 Mtx43_RotateZ(void *m, s32 a);
s32 Mtx43_RotateX(void *m, s32 a);
s32 func_01ffcb0c(s32 a, s32 b);
s32 FX_Div(s32 a, s32 b);
void MTX_MultVec43(V3 *a, Blk *b, V3 *c);
u32 NNS_G3dMdlGetMdlAlpha(void *res, u32 i);
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
void CharaShadow_DrawFaded(void *p, s32 a, u32 b, u8 c);
BOOL NetArea_IsLocalOwner();
Actor *PlayerActor_GetActor(u32 n);
s32 func_ov003_02226a5c(Obj *self);
}

}


namespace s03 {

typedef VecFx32Ctor V3;


typedef Insect Rec;


struct FieldInsectUpdateLocals {
    s8 netKind;
    u8 index;
    u8 netAlarm;
};

extern "C" {
extern CommManager *gCommManager;
extern Rec sFieldInsects[];
extern Rec sSpecialInsects[];
extern Rec sHeldInsects[];
s32 NetArea_IsLocalOwner(void);
s32 Weather_GetFallingPrecip(void);
s32 PlayerActor_GetAction(s32 v);
BOOL Camera_IsBlockingFocusView(void *p, s32 a, s32 b);
s32 Vec_DistXZ(void *a, void *b);
void func_020728c4(CommManager *g, s32 a, s32 b);
}

static inline BOOL Unk_ov003_022277c0_Chk(u16 *p) {
    BOOL f9 = TRUE, f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v >= 0x26 && v <= 0x2a) f1 = TRUE;
    if (!f1) {
        if (v < 0x5d || v > 0x61) f2 = FALSE;
    }
    if (!f2) {
        if (v < 0x2f || v > 0x56) f3 = FALSE;
    }
    if (!f3) {
        if (v < 0x57 || v > 0x5b) f4 = FALSE;
    }
    if (!f4) {
        if (v < 0x66 || v > 0x68) f5 = FALSE;
    }
    if (!f5) {
        if (v != 0x69) f6 = FALSE;
    }
    if (!f6) {
        if (v < 0x6a || v > 0x6c) f7 = FALSE;
    }
    if (!f7) {
        if (v != 0x6d) f8 = FALSE;
    }
    if (!f8) {
        if (v < 0xc8 || v > 0xcf) f9 = FALSE;
    }
    return f9;
}

}


#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {

typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
extern Rec sFieldInsects[];
extern u8 sInsectSpawnTimer;
extern u8 sAntSpawnEnabled;
extern void *gCurrentHeap;
BOOL NetArea_IsLocalOwner();
s32 PlayerActor_GetSlotPosXZ(u8 *a, s32 *b, s32 *c, s32 d, s32 e);
Actor *PlayerActor_GetActor(u32 n);
s32 Vec_DistXZ(void *a, void *b);
void func_02133ef8(void *p, s32 n);
void *func_02106788(void *r);
void *func_021067a4(void *a, u32 b);
void *func_021065dc(void *r);
void *func_021065f8(void *a, u32 b);
void *func_02106654(void *p);
void *func_02106670(void *a, u32 b);
BOOL PlayerActor_TestSlotFlag9(s32 a);
}

}

#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

namespace s05 {
extern "C" {
extern CommManager *gCommManager;
void FieldInsectHeap_Create();
void FieldInsectHeap_Destroy();
void SpecialInsectHeap_Create();
void SpecialInsectHeap_Destroy();
void HeldInsectHeap_Create();
void HeldInsectHeap_Destroy();
void InsectSpawn_BuildMasks();
void TownJunkInsects_Refresh();
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
}

}


namespace s06 {
typedef Insect Rec;


typedef GroundInfoBase Buf;

extern "C" {
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
}

}


namespace s07 {
typedef VecFx32Ctor V3;

typedef Insect Rec;

extern "C" {
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
Actor *PlayerActor_GetActor(u32 n);
s32 Vec_DistXZ(void *a, void *b);
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
}

static inline BOOL Unk_ov003_02229dcc_Chk(u16 *p) {
    BOOL f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE;
    BOOL f1 = FALSE;
    u32 v = *p;
    if (v <= 5) {
        f1 = TRUE;
    }
    if (f1 == FALSE) {
        if (v < 6 || v > 0xb) {
            f2 = FALSE;
        }
    }
    if (f2 == FALSE) {
        if (v < 0xc || v > 0x11) {
            f3 = FALSE;
        }
    }
    if (f3 == FALSE) {
        if (v < 0x12 || v > 0x19) {
            if (v != 0x1c) {
                f4 = FALSE;
            }
        }
    }
    if (f4 == FALSE) {
        if (v < 0x8a || v > 0x8f) {
            if (v < 0x90 || v > 0x95) {
                if (v < 0x96 || v > 0x9b) {
                    if (v < 0x9c || v > 0xa3) {
                        if (v != 0xa5) {
                            f5 = FALSE;
                        }
                    }
                }
            }
        }
    }
    if (f5 == FALSE) {
        if (v != 0x1a) {
            f6 = FALSE;
        }
    }
    if (f6 == FALSE) {
        if (v != 0xa4) {
            f7 = FALSE;
        }
    }
    if (f7 == FALSE) {
        if (v != 0x1d) {
            f8 = FALSE;
        }
    }
    return f8;
}

}


#define func_02133150 _s32_div_f
namespace s08 {

typedef VecFx32Ctor V3;


typedef Insect Rec;


extern "C" {
extern s16 data_02135f44[];
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
u32 NNS_G3dMdlGetMdlAlpha(void *res, u32 i);
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
s32 NetArea_IsLocalOwner(void);
}

static inline BOOL Unk_ov003_0222a8d0_Chk(u16 *p) {
    BOOL f9 = TRUE, f8 = TRUE, f7 = TRUE, f6 = TRUE, f5 = TRUE, f4 = TRUE, f3 = TRUE, f2 = TRUE, f1 = FALSE;
    u32 v = *p;
    if (v >= 0x26 && v <= 0x2a) {
        f1 = TRUE;
    }
    if (!f1) {
        if (v < 0x5d || v > 0x61) {
            f2 = FALSE;
        }
    }
    if (!f2) {
        if (v < 0x2f || v > 0x56) {
            f3 = FALSE;
        }
    }
    if (!f3) {
        if (v < 0x57 || v > 0x5b) {
            f4 = FALSE;
        }
    }
    if (!f4) {
        if (v < 0x66 || v > 0x68) {
            f5 = FALSE;
        }
    }
    if (!f5) {
        if (v != 0x69) {
            f6 = FALSE;
        }
    }
    if (!f6) {
        if (v < 0x6a || v > 0x6c) {
            f7 = FALSE;
        }
    }
    if (!f7) {
        if (v != 0x6d) {
            f8 = FALSE;
        }
    }
    if (!f8) {
        if (v < 0xc8 || v > 0xcf) {
            f9 = FALSE;
        }
    }
    return f9;
}

}

#undef func_02133150

namespace s09 {

typedef VecFx32Ctor V3;


typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
BOOL NetArea_IsLocalOwner();
s32 MenuCtrl_IsMenuOpen();
u32 NNS_G3dMdlGetMdlAlpha(void *res, u32 i);
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 Math_StepAngle(s16 *a, s32 b, s32 c);
BOOL PlayerActor_LocalHoldsNet();
s32 PlayerActor_GetStrikeCountdownAt(V3 *a, s32 b);
s32 Stinger_UpdateChase(Rec *o, s16 *p);
void Stinger_Walk(Rec *o, s16 *p, s32 r);
void Moth_CircleLight(Rec *o);
}

}


namespace s10 {
typedef VecFx32Ctor V3;

typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
BOOL NetArea_IsLocalOwner();
BOOL Ground_GetDigKind(s32 x, s32 y);
void NNS_G3dMdlSetMdlAlpha(void *res, u32 i, u32 v);
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 Vec_DistXZ(void *a, void *b);
void TownJunkInsects_Refresh();
}

}


#define func_02133150 _s32_div_f
namespace s11 {

typedef VecFx32Ctor V3;


typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
BOOL NetArea_IsLocalOwner();
s32 FX_Div(s32 a, s32 b);
s32 Math_StepAngle(s16 *a, s32 b, s32 c);
s32 Vec_DistXZ(void *a, void *b);
Actor *PlayerActor_GetActor(u32 n);
void Bee_StingAndLeave(Rec *o);
void Bee_StretchSwarm(V3 *p, s32 a);
void Pondskater_CheckObstacle(Rec *o, s16 *p);
void Pondskater_StartSkate(Rec *o, s16 *p);
void Pondskater_Skate(Rec *o, s16 *p);
void Insect_AccumAlarmOffline(Rec *o, u8 *a, VecFx32Ctor *out);
}


}

#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
typedef VecFx32Ctor V3;

typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
BOOL NetArea_IsLocalOwner();
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
s32 Math_StepAngle(s16 *a, s32 b, s32 c);
void Dragonfly_FlyToPerch(Rec *self);
void Dragonfly_FindPerch(Rec *self);
}

extern "C" {
enum Unk_ov003_0222d1f0_K { K_300 = 0x300 };
}

}

#undef func_02133150

#define func_021329d0 _ffix
namespace s13 {

typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
extern s16 data_02135f44[];
BOOL NetArea_IsLocalOwner();
Actor *PlayerActor_GetActor(u32 n);
s32 FX_Div(s32 a, s32 b);
s32 func_01ffcb0c(s32 a, s32 b);
void VEC_Subtract(void *a, void *b, void *out);
void Vec_Sub(VecFx32Ctor *out, void *a, void *b);
s32 Vec_MagXZ(VecFx32Ctor *v);
s32 Math_StepAngle(s16 *a, s32 b, s32 c);
s32 func_021329d0(s32 a);
s32 Insect_ApproachFlower(Rec *self, s16 *p);
s32 Moth_SteerToLight(Rec *self, s16 *p, VecFx32Ctor *out);
}


static inline BOOL Gt(s32 a, s32 b) {
    if (a > b) return TRUE;
    return FALSE;
}

}

#undef func_021329d0

#define func_02133150 _s32_div_f
namespace s14 {
typedef VecFx32Ctor V3;

typedef Insect Rec;


extern "C" {
extern CommManager *gCommManager;
extern s16 data_02135f44[];
extern u8 data_ov003_0225b470[];
extern u8 data_ov003_0225b474[];
extern u8 data_ov003_0225b475[];
BOOL NetArea_IsLocalOwner();
s32 func_01ffcb0c(s32 a, s32 b);
Actor *PlayerActor_GetActor(u32 n);
s32 Flower_GetColor(u16 *p);
s32 Flower_GetSpecies(u16 *p);
s32 Ground_GetWaterKind(s32 x, s32 y);
void Vec_RotateY(V3 *o, s32 a);
void NetBuf_UnpackPair20(void *p, s32 *a, s32 *b);
void NetBuf_PackPair20(void *p, s32 a, s32 b);
s32 CommSyncVar_GetVarSize(s32 a);
void *__cxa_vec_cleanup(void *, s32, s32, void *(*)(void *));
s32 PlayerActor_GetDigCountdownAt(VecFx32Ctor *a, s32 b);
}

}

#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" s32 Insect_CheckObstacle(Rec *o, s32 a, s32 b) {
    if (!gCommManager->isSlotActive(gCommManager->myAid) || NetArea_IsLocalOwner() || o->state == 9 || o->state == 0xb) {
        Insect_SetFeelers(o, a, b);
        if ((u8)(s8)(o->kind - 0x36) <= 1 && o->state == 4) {
            return Insect_TestFeelersHole(o);
        }
        return Insect_TestFeelers(o);
    }
    return 0;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" u32 Insect_TestFeelers(Rec *o) {
    u8 r = 0;
    V3 *p = (V3 *)&o->feelers[0];
    s32 y = o->position.y;
    GroundInfo g0;
    GroundInfo g1;
    g0.initAtPos((VecFx32 *)(p), 0, 0);
    if (g0.getHeight(1) > y) r++;
    g1.initAtPos((VecFx32 *)(p + 1), 0, 0);
    if (g1.getHeight(1) > y) r += 2;
    return r;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" u32 Insect_TestFeelersHole(Rec *o) {
    u8 r = 0;
    V3 *p = (V3 *)&o->feelers[0];
    s32 y = o->position.y;
    GroundInfo g0;
    GroundInfo g1;
    s32 v;
    g0.initAtPos((VecFx32 *)(p), 0, 0);
    v = g0.getHeight(1);
    if (v < 0 || v > y) r++;
    g1.initAtPos((VecFx32 *)(p + 1), 0, 0);
    v = g1.getHeight(1);
    if (v < 0 || v > y) r += 2;
    return r;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_SetFeelers(Rec *o, s32 a, s32 b) {
    V3 *out;
    V3 *pos = &o->position;
    s32 h;
    if (o->kind == 0x35) {
        h = o->rotZ;
    } else {
        h = o->rotY;
    }
    out = (V3 *)&o->feelers[0];
    *out = *pos;
    s32 i = ((u16)(s16)(h + b) >> 4) * 2;
    out->x += func_02133150(a * data_02135f44[i], 100);
    out->z += func_02133150(a * data_02135f44[i + 1], 100);
    out[1] = *pos;
    s32 j = ((u16)(s16)(h - b) >> 4) * 2;
    out[1].x += func_02133150(a * data_02135f44[j], 100);
    out[1].z += func_02133150(a * data_02135f44[j + 1], 100);
    return TRUE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" void Insect_GetDirVec(V3 *o, s32 a) {
    o->x = 0;
    o->y = 0;
    o->z = 0x29;
    Vec_RotateY(o, a);
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_IsOverWater(VecFx32 *v) {
    s32 x = 0;
    s32 y = 0;
    FieldPos_ToUnit(&x, &y, v);
    if (Ground_GetWaterKind(x, y)) return TRUE;
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" void Insect_CheckTurnCount(Rec *o, s32 n) {
    s32 t = o->behaviorWork & 0xf;
    if (t > n) o->state = 9;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_SetMoveTarget(Rec *o, u32 ang, s32 d) {
    V3 *dst;
    V3 *src;
    switch (o->kind) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
    case 0x25:
        return Insect_SetGroundMoveTarget(o, ang, (u8)(d >> 12));
    case 0x1e:
    case 0x31:
        return Insect_SetGroundMoveTarget(o, ang, (u8)(d >> 12));
    case 0xc: case 0xd:
    case 0x1b: case 0x1c: case 0x1d:
        if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
            return Insect_SetGroundMoveTarget(o, ang, (u8)(d >> 12));
        }
    default:
        break;
    }
    dst = &o->targetPos;
    src = &o->position;
    s32 idx = ((u16)ang >> 4) * 2;
    dst->x = src->x + func_01ffcb0c(d, data_02135f44[idx]);
    dst->z = src->z + func_01ffcb0c(d, data_02135f44[idx + 1]);
    return TRUE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_SetGroundMoveTarget(Rec *o, u32 ang, s32 n) {
    s32 lim;
    u8 i;
    s32 sx;
    s32 sz;
    V3 *dst;
    s32 n1;
    V3 *src;
    BOOL bad;
    s32 idx = ((u16)ang >> 4) * 2;
    sx = data_02135f44[idx];
    sz = data_02135f44[idx + 1];
    dst = &o->targetPos;
    src = &o->position;
    lim = src->y;
    if (lim < Ground_GetDefaultY()) lim = Ground_GetDefaultY();
    i = 1;
    n1 = n + 1;
    for (; i < n1; i++) {
        V3 t;
        s32 off = i << 12;
        t.x = src->x + func_01ffcb0c(off, sx);
        t.z = src->z + func_01ffcb0c(off, sz);
        {
            GroundInfo g;
            g.initAtPos((VecFx32 *)(&t), 0, 0);
            if (g.getHeight(1) > lim) {
                bad = 1;
            } else {
                bad = 0;
            }
        }
        if (bad != 0) break;
    }
    u8 c = i - 1;
    if (c != 0) {
        s32 f = c << 12;
        dst->x = src->x + func_01ffcb0c(f, sx);
        dst->z = src->z + func_01ffcb0c(f, sz);
        Insect_SetFlutterTurnDelay(o);
        return TRUE;
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" Actor *Insect_FindNearestPlayer(VecFx32 *pos) {
    Actor *best = 0;
    s32 bestd = 0xfffffff;
    u8 i;
    for (i = 0; i < 4; i++) {
        s32 dx, dz, d;
        Actor *p;
        VecFx32 *q;
        p = PlayerActor_GetActor(i);
        if (p != 0) {
            q = &p->position;
            dx = pos->x - p->position.x;
            if (dx < 0) dx = -dx;
            dz = pos->z - q->z;
            if (dz < 0) dz = -dz;
            d = dx + dz;
            if (d < bestd) {
                bestd = d;
                best = p;
            }
        }
    }
    return best;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" void Insect_UpdateRest(Rec *o) {
    Insect_CheckAlarm(o);
    if (Insect_TickTimer(o) == 0) {
        s32 st = o->kind;
        if (st == 0xa || st == 0x33) {
            if ((((u32)o->model.curFrame << 4) >> 16) != 0) ((AnimModel *)(&o->model))->setFrame(0);
            Crawler_Wander(o);
        } else if (st == 0x33) {
        } else {
            if (Insect_IsOnFlower(&o->position) == 0) o->alarm = 0xfe;
            if (((o->model.numFrames << 4) >> 16) < 0xc) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(0x11, 1, 0x1000, 9);
            } else if ((((u32)o->model.curFrame << 4) >> 16) == 0x10) {
                if (Random_GlobalBelow(100) > 0x5f) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(0x11, 1, 0x1000, 9);
                }
            }
        }
    } else {
        o->state = 0x13;
        o->targetHeight = o->baseHeight;
        o->waitTimer = (Random_GlobalBelow(6) + 7) * 20;
        s32 st = o->kind;
        if (st != 0xa && st != 0x33) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(9, 0, o->behaviorWork, 0);
        } else {
            ((AnimModel *)(&o->model))->setFrame(1);
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_LikesFlower(s32 a, u16 *b) {
    u32 t = Flower_GetColor(b);
    u32 c = Flower_GetSpecies(b);
    if (a == 0xf) {
        if (c == 0 || c == 3) {
            if (t == 2) return TRUE;
        } else if (c == 4 || t == 1) {
            return TRUE;
        }
    } else if (a == 3) {
        if (c == 0) {
            if (t - 5 <= 1) return TRUE;
        } else if (c == 1) {
            if (t == 4 || t == 6) return TRUE;
        } else if (c == 2) {
            if (t == 6) return TRUE;
        } else if (c == 3) {
            if (t - 6 <= 2) return TRUE;
        }
    } else if (a == 2) {
        if (c == 0) {
            if (t == 1 || t == 4) return TRUE;
        } else if (c == 1) {
            if (t == 3) return TRUE;
        } else if (c == 2) {
            if (t == 2 || t == 4) return TRUE;
        } else if (c == 3) {
            if (t == 1 || t == 4) return TRUE;
        }
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_SplashIfWater(Rec *o) {
    V3 v;
    GroundInfo g;
    V3 *pv = &o->position;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    g.initAtPos((VecFx32 *)(&v), 0, 1);
    if (g.waterKind != 0) {
        v.y = g.waterSurfaceY + 0x100;
        ((SndEnvChannel *)(&o->seEmitter))->callRequestSustained(0x7e5);
        switch (o->kind) {
        case 0xc:
        case 0xd:
        case 0x1e:
        case 0x1f:
            Effect_Create(0x13, &v, 0, 0);
            break;
        case 0x36:
        case 0x37:
            Effect_Create(0x14, &v, 0, 0);
            break;
        default:
            Effect_Create(0x12, &v, 0, 0);
            break;
        }
        return TRUE;
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" BOOL Insect_CheckDigHit(Rec *o, VecFx32Ctor *a) {
    s8 i;
    s8 *p = &o->hitCountdown;
    if (*p <= 0) {
        if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
            for (i = 0; i < 4; i++) {
                *p = PlayerActor_GetDigCountdownAt(a, i);
                if (*p > 0) break;
            }
        } else {
            *p = PlayerActor_GetDigCountdownAt(a, 4);
        }
    }
    if (*p > 0) {
        *p = *p - 1;
        if (*p == 0) return TRUE;
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s14 {
extern "C" void Insect_PlaySe(Rec *o, s32 a, s32 b) {
    s32 r = Insect_GetSeId(o->kind, a);
    if (r >= 0) {
        if (b != 0) {
            ((SndEnvChannel *)(&o->seEmitter))->callRequest(r);
        } else {
            ((SndEnvChannel *)(&o->seEmitter))->callRequestSustained(r);
        }
    }
}
}
#undef func_02133150

#define func_021329d0 _ffix
namespace s13 {
extern "C" s32 Insect_GetSeId(s32 a, s32 b) {
    switch (a) {
    case 51:
        return 0x823;
    case 11: case 58:
        if (b == 0) return 0x830;
        return 0x837;
    case 54:
        if (b == 1) return 0x834;
        return 0x833;
    case 55:
        if (b == 1) return 0x836;
        return 0x835;
    case 10:
        return 0x831;
    case 50:
        return 0x828;
    case 29:
        return 0x825;
    case 27:
        return 0x826;
    case 28:
        return 0x82c;
    case 12:
        return 0x82b;
    case 13:
        return 0x82d;
    case 15: case 25: case 32: case 57:
        return 0x812;
    case 14: case 33: case 34: case 35: case 38: case 39: case 40: case 41: case 42: case 43: case 44: case 52:
        return 0x811;
    case 36: case 45: case 46: case 47:
        return 0x810;
    case 20:
        if (b != 0) return 0x811;
        return -1;
    case 16:
        if (b == 0) return 0x822;
        return 0x80f;
    case 17:
        if (b == 0) return 0x827;
        return 0x80f;
    case 18:
        if (b == 0) return 0x82e;
        return 0x80f;
    case 19:
        if (b == 0) return 0x824;
        return 0x80f;
    case 30:
        if (b == 0) return 0x829;
        return 0x82a;
    }
    return -1;
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_FlutterPullBack(Rec *self, VecFx32Ctor *p, s32 a) {
    s16 ang;
    VecFx32Ctor v;
    VecFx32Ctor *r6;
    ang = self->rotY;
    v = *p;
    r6 = &self->position;
    Math_StepAngle(&ang, Math_AngleXZ(r6, p), a);
    self->rotY = ang;
    VEC_Subtract(&v, r6, &v);
    Insect_ClampStepXZ(&v, &v, 1);
    VEC_Add(r6, &v, r6);
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_SetFlutterTurnDelay(Rec *self) {
    switch (self->kind) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
    case 0x25:
        self->turnDelay = 0x14;
        break;
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" s32 Insect_GetFlutterLeash(Rec *self) {
    switch (self->kind) {
    case 0:
    case 1:
    case 2:
    case 3:
        return 0xccd;
    case 4:
        return 0xb33;
    case 5:
        return 0xccd;
    case 6:
        return 0xb33;
    case 7:
    case 0x25:
        return 0xccd;
    }
    return 0;
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" s32 Insect_GetFlutterRange(Rec *self) {
    switch (self->kind) {
    case 0:
    case 1:
        return 0x5000;
    case 2:
    case 3:
        return 0x4600;
    case 4:
        return 0x7800;
    case 5:
    case 6:
        return 0x5000;
    case 7:
        return 0xc800;
    case 0x25:
        return 0x3c00;
    }
    return 0;
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" s32 Insect_GetFlutterTargetSpeed(Rec *self) {
    switch (self->kind) {
    case 0:
    case 1:
    case 2:
    case 3:
        return 0xf6;
    case 4:
        return 0x171;
    case 5:
        return 0x1ec;
    case 6:
        return 0x2b8;
    case 7:
        return 0x266;
    case 0x25:
        return 0xcd;
    }
    return 0;
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_FlutterSteer(Rec *self, s16 *p, s32 a, s32 b, u8 e, s32 f) {
    s32 rnd;
    VecFx32Ctor *r6 = &self->homePos;
    VecFx32Ctor *r10 = &self->targetPos;
    VecFx32Ctor *r4 = &self->position;
    s32 hit = Insect_CheckObstacle(self, 0x50, 0xe38);
    u32 flag = self->unk_24b;
    rnd = Random_GlobalBelow(100);
    VecFx32Ctor t;
    VecFx32Ctor d;
    if (hit != 0) {
        self->rotY = Insect_ReflectAngle(self->rotY, hit);
        *r6 = *r4;
        {
            s32 q = self->rotY;
            Insect_SetMoveTarget(self, q, Insect_GetFlutterRange(self));
        }
        return;
    }
    if (DS_MOD(self->frameCounter, b) == 0 && rnd > e) {
        self->unk_24b = flag == 0 ? 1 : 0;
    }
    if (rnd > self->cooldownTimer) {
        if (flag != 0) {
            *p = *p + a;
            self->rotY = *p;
        } else {
            *p = *p - a;
            self->rotY = *p;
        }
    }
    Insect_GetDirVec(&t, *p);
    if (self->isAlarmed != 0) {
        s32 m = func_021329d0(0x45a00400);
        r4->x = r4->x + func_01ffcb0c(func_01ffcb0c(f, t.x), m);
        r4->z = r4->z + func_01ffcb0c(func_01ffcb0c(f, t.z), m);
    } else {
        r4->x = r4->x + func_01ffcb0c(f, t.x);
        r4->z = r4->z + func_01ffcb0c(f, t.z);
    }
    Vec_Sub(&d, r6, r4);
    s32 len = Vec_MagXZ(&d);
    if (Gt(len, Insect_GetFlutterLeash(self))) {
        Insect_FlutterPullBack(self, r6, 0xaaa);
    }
    {
        s32 k = Insect_GetFlutterTargetSpeed(self);
        if (Math_ApproachVecXZ(r6, r10, 0x28, k + 0x19a, Insect_GetFlutterTargetSpeed(self)) == 0) {
            if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
                if (NetArea_IsLocalOwner() == 0) {
                    return;
                }
            }
            u8 *q253 = &self->turnDelay;
            if (*q253 == 0) {
                s32 s = self->rotY;
                self->rotY = s + Insect_RandomTurn(6, 1);
                *r6 = *r4;
                if (self->isAlarmed != 0) {
                    Actor *e2;
                    if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
                        e2 = Insect_FindNearestPlayer(r4);
                    } else {
                        e2 = PlayerActor_GetActor(4);
                    }
                    if (e2 != NULL) {
                        self->rotY = Math_AngleXZ(&e2->position, r4);
                    }
                }
                {
                    s32 q = self->rotY;
                    Insect_SetMoveTarget(self, q, Insect_GetFlutterRange(self));
                }
            } else {
                *q253 = *q253 - 1;
            }
        }
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_FlutterBob(Rec *self, s32 a, s32 b, s32 c) {
    VecFx32Ctor *r6 = &self->position;
    s32 r4 = FX_Div(data_02135f44[((u16)a >> 4) * 2], c);
    if (self->targetHeight != self->baseHeight) {
        b = FX_Div(b, 0x2000);
    }
    if ((r4 > 0 && r6->y + r4 < b + self->targetHeight) || (r4 < 0 && r6->y + r4 > self->targetHeight - b)) {
        r6->y = r6->y + r4;
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" s32 Insect_CheckAlarm(Rec *self) {
    VecFx32Ctor v;
    s32 r = Insect_UpdateAlarm(self, &v);
    if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
        Insect_FleeIfAlarmed(self, &v);
    } else {
        (self)->insectFleeFrom(&v);
    }
    return r;
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_FleeIfAlarmed(Rec *self, VecFx32Ctor *p) {
    s32 c = self->alarm;
    if (NetArea_IsLocalOwner()) {
        if (p->x != 0 && self->isAlarmed == 0 && c >= self->alarmThreshold) {
            self->turnAngle = Math_AngleXZ(p, &self->position);
            self->state = 7;
            self->isAlarmed = 1;
        }
    } else {
        if (self->isAlarmed == 0 && c >= self->alarmThreshold) {
            self->isAlarmed = 1;
            self->state = 7;
        }
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_FlapWings(Rec *self) {
    if ((((u32)self->model.curFrame << 4) >> 16) == 1) {
        ((AnimModel *)(&self->model))->setFrame(2);
    } else {
        ((AnimModel *)(&self->model))->setFrame(1);
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Butterfly_Update(Rec *self) {
    s32 c = self->auxTimer;
    if (c > 0x8c) {
        self->state = 9;
    } else if (Insect_CheckObstacle(self, 0x50, 0xe38) != 0) {
        self->auxTimer = c + 1;
    } else {
        self->auxTimer = 0;
    }
    switch (self->state) {
    case 0:
        Insect_FlutterFlight(self);
        break;
    case 6:
        Insect_UpdateRest(self);
        break;
    case 9:
    case 11:
        if (((self->model.numFrames << 4) >> 16) > 9) {
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(9, 0, 0x1000, 0);
        }
        Insect_FlyAwayArc(self, 0x1ccd);
        break;
    case 7: {
        s32 t;
        VecFx32Ctor *src;
        VecFx32Ctor *dst;
        self->state = 0;
        self->rotY = self->rotY + self->turnAngle;
        t = self->rotY;
        if (Insect_SetMoveTarget(self, t, Insect_GetFlutterRange(self)) != 0) {
            src = &self->position;
            dst = &self->homePos;
            *dst = *src;
        }
        break;
    }
    case 0x13: {
        s32 t;
        VecFx32Ctor *src;
        VecFx32Ctor *dst;
        self->isAlarmed = 0;
        self->state = 0;
        t = self->rotY;
        if (Insect_SetMoveTarget(self, t, Insect_GetFlutterRange(self)) != 0) {
            src = &self->position;
            dst = &self->homePos;
            *dst = *src;
        }
        break;
    }
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" void Insect_FlutterFlight(Rec *self) {
    s16 ang;
    VecFx32Ctor v;
    VecFx32Ctor w;
    VecFx32Ctor *r7;
    s16 *r4;
    s32 r6;

    ang = self->rotY;
    r7 = &self->position;
    r4 = &self->stateTimer;
    if (self->kind != 8 && ((self->model.numFrames << 4) >> 16) > 9) {
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(9, 0, self->behaviorWork, 0);
    }
    if (Insect_CheckAlarm(self) == 2) {
        if (self->kind != 8) {
            Insect_SetAnimSpeed(self, self->behaviorWork);
        } else {
            Insect_SetAnimSpeed(self, 0x1000);
        }
        self->isAlarmed = 0;
    }
    if (self->isAlarmed != 0) {
        if (self->kind != 8) {
            s32 t = func_01ffcb0c(self->behaviorWork, 0x1333);
            if (t != self->model.frameStep) {
                Insect_SetAnimSpeed(self, t);
            }
        } else {
            Actor *e = PlayerActor_GetActor(4);
            if (e != NULL) {
                Vec_Sub(&w, r7, &e->position);
                v = w;
                Insect_ClampStepXZ(&v, &v, 3);
                VEC_Add(r7, &v, r7);
            }
        }
    } else {
        if (self->kind == 8) {
            if (Moth_SteerToLight(self, r4, &v) == 0) {
                return;
            }
        } else {
            if (self->behaviorWork != self->model.frameStep) {
                Insect_SetAnimSpeed(self, self->behaviorWork);
            }
            if ((gCommManager)->isSlotActive(gCommManager->myAid) == 0) {
                Insect_ApproachFlower(self, &ang);
            }
        }
    }
    r6 = *r4;
    r6 = r6 * 0x44 + (r6 * r6 * -10) / 2;
    if (self->unk_24c != 0 && r6 >= 0) {
        func_01ffcb0c(r6, 0x2000);
    } else if (r6 < -0x333) {
        r6 = -0x333;
    }
    *r4 = *r4 + 4;
    Insect_FlutterAltitude(self, r4);
    r7->y = r7->y + r6;
    if (self->kind == 8) {
        (self)->insectWanderSteer(&ang, 0xaaa, 0x14, 0x3c, self->moveSpeed << 12);
    } else {
        Insect_FlutterSteer(self, &ang, 0x38e, 0x14, 0x3c, self->moveSpeed << 12);
    }
}
}
#undef func_021329d0

#define func_021329d0 _ffix
namespace s13 {
extern "C" BOOL Insect_TickTimer(Rec *self) {
    if (self->waitTimer > 0) {
        self->waitTimer -= TICK_STEP_ENDS() ? 1 : 0;
    } else {
        return TRUE;
    }
    return FALSE;
}
}
#undef func_021329d0

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Insect_FlyAwayArc(Rec *self, s32 a) {
    V3 *p = &self->position;
    s16 *cnt = &self->stateTimer;
    V3 v;
    Insect_GetDirVec(&v, self->rotY);
    if (Insect_FadeOut(self, 1) != 0) {
        Insect_Despawn(self);
    }
    s32 c = *cnt;
    s32 t = func_01ffcb0c(a, (c * 0x44) << 12);
    v.y = t >> (FX_Div((c * c) << 12, 0x1000) + 12);
    if (Insect_CheckObstacle(self, 0x50, 0xe38) == 0) {
        v.x = func_01ffcb0c(v.x, 0x10000);
        v.z = func_01ffcb0c(v.z, 0x10000);
    }
    (*cnt)++;
    VEC_Add(p, &v, p);
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Insect_FlutterAltitude(Rec *self, s16 *cnt) {
    s32 top;
    Unk_ov003_0222d1f0_K base = K_300;
    s32 a = self->baseHeight;
    u8 flag = self->unk_24c;
    V3 *p = &self->position;
    u8 *c = &self->unk_256;
    s32 b = self->targetHeight;
    if (a != b) {
        top = base + b;
        a = b;
    } else {
        top = base + a;
    }
    if (*c < *cnt) {
        if (flag != 0) {
            *cnt = 0;
            *c = 0x10;
        } else {
            *cnt = 8;
            *c = 0x14;
        }
    }
    if (flag != 0) {
        if (p->y > top) {
            self->unk_24c = 0;
        }
    }
    if (p->y < a) {
        if (p->y > a - 0x320) {
            p->y = a;
        }
        self->unk_24c = 1;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" s32 Insect_GetFlowerSpeciesMask(s32 a) {
    if (a == 2) {
        return 0xf;
    }
    if (a == 3) {
        return 0xf;
    }
    return 0x3f;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Dragonfly_Update(Rec *self) {
    s16 *cnt = &self->stateTimer;
    s32 lvl = ((s32)self->behaviorWork & 0xf0) >> 4;
    BOOL flag = FALSE;
    if (lvl > 0 && self->state == 0x13) {
        if (self->frameCounter % 0x14 == 0) {
            s32 r = Random_GlobalBelow(100);
            if ((((u32)self->model.curFrame << 4) >> 16) == 0 && r > 0x5c) {
                ((AnimModel *)(&self->model))->setFrame(2);
            } else if (r > 0x32) {
                ((AnimModel *)(&self->model))->setFrame(0);
            }
        } else if ((((u32)self->model.curFrame << 4) >> 16) != 0) {
            Insect_FlapWings(self);
        }
    } else {
        Insect_FlapWings(self);
    }
    if (self->state != 0xb && self->state != 9) {
        Insect_CheckAlarm(self);
    }
    Insect_CheckTurnCount(self, 5);
    u8 *st = &self->state;
    switch (*st) {
    case 15:
        flag = TRUE;
    case 3:
        if (Insect_TurnToTarget(self, 0) != 0) {
            if (flag != FALSE) {
                self->state = 0x12;
            }
        }
        break;
    case 4:
        if (lvl > 0) {
            Dragonfly_FlyToPerch(self);
        } else {
            Dragonfly_FlyToTarget(self);
        }
        Dragonfly_CheckObstacle(self);
        *cnt = 0;
        break;
    case 12:
    case 13:
    case 14:
        if (self->kind == 0x17) {
            *cnt = 100;
        }
        Dragonfly_Hover(self, cnt);
        break;
    case 7: {
        *st = 3;
        V3 *s = &self->position;
        V3 *d = &self->targetPos;
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
        self->behaviorWork |= 0xf00;
        break;
    }
    case 9:
    case 11:
        Dragonfly_FlyOff(self, cnt);
        break;
    default:
        if (lvl > 0) {
            (*cnt)++;
            if ((*cnt > 0x28 && *cnt % 10 == 0 && Random_GlobalBelow(100) > 0x50) || *cnt > 0xc8) {
                self->behaviorWork &= 0xff0f;
                *cnt = 0;
                self->state = 0xc;
                self->waitTimer = 100;
            }
        } else {
            s32 r = Insect_TickTimer(self);
            *cnt = 0;
            if (self->isAlarmed == 0 && r != 0 && gCommManager->isSlotActive(gCommManager->myAid) == 0) {
                Dragonfly_FindPerch(self);
            }
            if (self->state == 0x12) {
                self->state = 4;
            } else {
                self->isAlarmed = 0;
                self->state = 0xc;
                self->behaviorWork &= 0xfff0;
            }
        }
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Dragonfly_Hover(Rec *self, s16 *cnt) {
    V3 *p = &self->position;
    s32 r = Random_GlobalBelow(100);
    if ((gCommManager)->isSlotActive(gCommManager->myAid) != 0 && NetArea_IsLocalOwner() == 0) {
        V3 *q = &self->targetPos;
        if (q->x != p->x || q->z != p->z) {
            self->state = 4;
            *cnt = 0;
            return;
        }
    } else {
        s32 c = *cnt;
        if ((c == 0 && r > 0x5f) || (c == 10 && r > 0x50) || ((c == 0x14 || c == 0x1e) && r > 0x32) || c >= 0x28) {
            if (self->state != 0xd && self->state != 0xe) {
                s32 m;
                if (self->kind == 0x17) {
                    m = 5;
                } else {
                    m = 0xd;
                }
                s32 old = self->rotY;
                s32 g = Insect_RandomTurn(m, 1);
                self->turnAngle = g + old;
                V3 *s = &self->position;
                V3 *d = &self->targetPos;
                d->x = s->x;
                d->y = s->y;
                d->z = s->z;
            }
            self->state = 3;
            self->behaviorWork |= 0xf00;
            *cnt = 0;
            return;
        }
    }
    if (*cnt % 10 < 5) {
        if (p->y < self->baseHeight + 0x800) {
            p->y += 0x80;
        }
    } else {
        if (p->y > self->baseHeight - 0x800) {
            p->y -= 0x80;
        }
    }
    (*cnt)++;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Dragonfly_FlyToTarget(Rec *self) {
    s32 r6, s;
    V3 *q = &self->targetPos;
    V3 *p = &self->position;
    r6 = func_02133150(0x1000, self->moveSpeed);
    s8 t = self->kind;
    switch (t) {
    case 0x15:
        s = 0xcd;
        break;
    case 0x16:
        s = 0x266;
        break;
    default:
        s = 0x385;
        break;
    }
    if (self->isAlarmed != 0) {
        s = func_01ffcb0c(s, 0x2000);
    }
    if (Math_ApproachVecXZ(p, q, r6, 0x1000, s) == 0) {
        self->state = 0x13;
    } else {
        s32 x, y;
        self->rotY = Math_AngleXZ(p, q);
        if ((gCommManager)->isSlotActive(gCommManager->myAid) != 0) {
            if (NetArea_IsLocalOwner() == 0) {
                FieldPos_ToUnit(&x, &y, p);
                if (x < 0x10 || x > 0x4f || y < 0x10) {
                    self->state = 0x13;
                }
            }
        }
    }
    if (self->unk_24c != 0) {
        Math_ApproachS32(&p->y, self->baseHeight, r6, 0x1ec, 0xcd);
    } else {
        if (Math_ApproachS32(&p->y, self->baseHeight - 0x1000, r6, 0x333, 0xcd) == 0) {
            self->unk_24c = 1;
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Dragonfly_FlyOff(Rec *self, s16 *cnt) {
    V3 *p = &self->position;
    s32 t;
    V3 v;
    if (self->state == 0xb && Insect_CheckObstacle(self, 0x50, 0xe38) == 0) {
        Insect_GetDirVec(&v, self->rotY);
        p->x += func_01ffcb0c(v.x, 0x10000);
        p->z += func_01ffcb0c(v.z, 0x10000);
    }
    t = *cnt << 12;
    s32 a = func_01ffcb0c(0x44000, t);
    s32 b = func_01ffcb0c(t, t);
    s32 c = FX_Div(b, 0x2000);
    p->y += (a >> 12) + (c >> 12);
    (*cnt)++;
    if (Insect_FadeOut(self, 1) != 0) {
        Insect_Despawn(self);
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" void Dragonfly_CheckObstacle(Rec *self) {
    s32 m = Insect_CheckObstacle(self, 0x50, 0xe38);
    if (m != 0) {
        if (self->isAlarmed != 0) {
            self->state = 0xf;
            self->behaviorWork |= 0xf00;
        } else {
            self->state = 0xd;
        }
        self->turnAngle = Insect_ReflectAngle(self->rotY, m);
        self->behaviorWork++;
        self->stateTimer = 0;
        V3 *s = &self->position;
        V3 *d = &self->targetPos;
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" s32 Insect_ReflectAngle(s32 a, s32 mode) {
    s32 orig = a;
    if (mode == 3) {
        s32 r = Random_GlobalBelow(100);
        a = (s16)(a + 0x8000);
        if (r < 5) {
            a = (s16)(a + 0x2aaa);
        } else if (r < 10) {
            a = (s16)(a - 0x2aaa);
        }
    } else {
        if (mode == 1) {
            if (a < -0x4000) goto neg;
            if (a >= 0 && a < 0x4000) goto neg;
        }
        if (mode == 2) {
            if (a > 0x4000) goto neg;
            if (a <= 0 && a > -0x4000) {
            neg:
                a = (s16)-a;
                goto tail;
            }
        }
        if (a >= 0) {
            a = (s16)(0x8000 - a);
        } else {
            a = (s16)(-0x8000 - a);
        }
    }
tail:
    if (Random_GlobalBelow(100) < 10) {
        if (a >= 0) {
            a = (s16)(a + 0xaaa);
        } else {
            a = (s16)(a - 0xaaa);
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
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s12 {
extern "C" s32 Insect_TurnToTarget(Rec *self, u32 a) {
    BOOL result = FALSE;
    s16 ang = self->rotY;
    if (self->state != 0xb) {
        if (NetArea_IsLocalOwner() == 0 && gCommManager->isSlotActive(gCommManager->myAid) != 0) {
            if (self->position.x != self->targetPos.x && self->position.z != self->targetPos.z) {
                self->state = 4;
                self->unk_24c = a;
            }
        } else {
            V3 *p = &self->position;
            V3 *q = &self->targetPos;
            u32 fl = self->behaviorWork;
            if ((p->x == q->x && p->z == q->z) || (fl & 0xf00) != 0) {
                u8 n = self->moveTargetDist;
                n = n + Random_GlobalBelow(3);
                if (self->isAlarmed != 0) {
                    n = n + (u8)(Random_GlobalBelow(2) + 2);
                }
                if (Insect_SetMoveTarget(self, self->turnAngle, n << 12) != 0) {
                    self->turnAngle = Math_AngleXZ(&self->position, &self->targetPos);
                    fl &= 0xf0ff;
                    self->behaviorWork = fl;
                } else {
                    fl &= 0xf0ff;
                    self->behaviorWork = fl;
                }
            }
            if (Math_StepAngle(&ang, self->turnAngle, 0xe38) != 0) {
                self->state = 4;
                self->unk_24c = a;
                result = TRUE;
            }
            self->rotY = ang;
        }
    } else {
        Insect_SetMoveTarget(self, self->rotY, ((u32)(self->moveTargetDist << 25) >> 24) << 12);
        self->unk_24c = a;
    }
    return result;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Insect_AccumAlarm(Rec *o, V3 *out, s32 *dist, u8 *flag, u8 a, u8 b) {
    Actor *p = PlayerActor_GetActor(a);
    if (p) {
        s32 r5 = o->alarm;
        s32 lim = o->disturbRadius;
        s32 r4 = p->speed;
        VecFx32 *pv = &p->position;
        out->x = p->position.x;
        out->y = pv->y;
        out->z = pv->z;
        *dist = Vec_DistXZ(out, &o->position);
        if (b) {
            *flag = 0;
            if (*dist < 0x2000) {
                r5 = (s16)(r5 + 0x19);
            } else if (*dist > lim || r4 == 0) {
                *flag = 1;
            } else if (r4 <= 0x3e8) {
                r5 = (s16)(r5 + 1);
            } else if (r4 <= 0x44c) {
                r5 = (s16)(r5 + 3);
            } else if (r4 <= 0x490) {
                r5 = (s16)(r5 + 5);
            } else if (r4 == 0x491) {
                r5 = (s16)(r5 + 8);
            } else {
                r5 = (s16)(r5 + 0xf);
            }
            if (r5 > 0xfe) r5 = 0xfe;
            o->alarm = r5;
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" s32 Insect_UpdateAlarm(Rec *o, VecFx32Ctor *out) {
    s32 r = 0;
    s32 best;
    s32 flagC;
    u32 i;
    u32 s14;
    s32 zero;
    u8 b[2];
    s32 dist;
    V3 v;
    u32 r4;
    best = 0xfffffff;
    flagC = 1;
    b[0] = 1;
    b[1] = 1;
    s14 = o->alarm;
    r4 = o->alarmThreshold;
    out->x = 0;
    if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
        if (NetArea_IsLocalOwner() == 0) {
            flagC = r;
        }
        i = 0;
        zero = 0;
        do {
            Insect_AccumAlarm(o, &v, &dist, &b[1], i, flagC);
            b[0] = (b[0] & b[1]) ? 1 : zero;
            if (best > dist) {
                out->x = v.x;
                out->y = v.y;
                out->z = v.z;
                best = dist;
            }
            i = (u8)(i + 1);
        } while (i < 4);
    } else {
        Insect_AccumAlarmOffline(o, b, out);
    }
    if (flagC) {
        u8 *pc = &o->alarm;
        u32 r2 = *pc;
        if (b[0] && r2) {
            r2 = (u8)(r2 - 1);
            *pc = r2;
        }
        if (r4 <= r2) {
            if (r4 > s14) {
                r = 1;
            } else {
                r = 3;
            }
        } else if (r4 > r2) {
            if (r4 <= s14) {
                r = 2;
            }
        }
    }
    return r;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Hopper_Update(Rec *o) {
    s16 *p = &o->stateTimer;
    u32 st = o->state;
    if (st != 0xb && st != 9 && st != 4) {
        Insect_CheckAlarm(o);
    }
    Insect_CheckTurnCount(o, 4);
    switch (st) {
    case 3:
    case 0xf:
        Insect_TurnToTarget(o, 1);
        break;
    case 7:
        o->state = 0xf;
        o->behaviorWork |= 0xf00;
        Hopper_CheckObstacle(o, p);
        break;
    case 9:
    case 0xb:
        o->isAlarmed = 1;
    case 4:
    case 0x11:
        Hopper_Jump(o);
        break;
    case 0x13:
        Cricket_Chirp(o);
        if ((((u32)o->model.curFrame << 4) >> 16) != 0) {
            o->model.setFrame(0);
        }
        if (Hopper_CheckObstacle(o, p) == 0) {
            Hopper_Rest(o, p);
            o->behaviorWork = 0;
        }
        break;
    case 0:
    case 1:
    case 2:
    case 5:
    case 6:
    case 8:
    case 10:
    case 12:
    case 13:
    case 14:
    case 16:
    case 18:
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Hopper_Rest(Rec *o, s16 *p) {
    *p = *p + 1;
    if ((gCommManager)->isSlotActive(gCommManager->myAid) && !NetArea_IsLocalOwner()) {
        V3 *a = &o->position;
        V3 *b = &o->targetPos;
        if (a->x != b->x || a->z != b->z) {
            o->state = 4;
            *p = 0;
            o->unk_24c = 1;
        }
    } else {
        if (*p >= o->auxTimer) {
            s16 t = o->rotY;
            s32 g = Insect_RandomTurn(0xc, 1);
            o->turnAngle = g + t;
            o->behaviorWork |= 0xf00;
            o->state = 3;
            *p = 0;
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" s16 Insect_RandomTurn(s32 a, s32 b) {
    u8 r = Random_GlobalBelow(a);
    if (r != 0) {
        if (b != 0 && Random_GlobalBelow(100) > 0x32) {
            return (s16)(r * -0x38e);
        }
        return (s16)(r * 0x38e);
    }
    return 0;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Hopper_Jump(Rec *o) {
    u32 st;
    V3 *dst = &o->targetPos;
    V3 *src = &o->position;
    s32 q = func_02133150(0x1000, o->moveSpeed);
    s32 flag = 0;
    st = o->state;
    if (o->isAlarmed) {
        Insect_FlapWings(o);
        Locust_PlaySe(o);
    }
    if (Insect_CheckObstacle(o, 0x50, 0xe38) == 0) {
        if (Math_ApproachVecXZ(src, dst, q, 0x14000, 0x333) == 0) {
            flag = 1;
        } else {
            o->rotY = Math_AngleXZ(src, dst);
        }
    } else {
        flag = 1;
        dst->x = src->x;
        dst->y = src->y;
        dst->z = src->z;
    }
    if (o->unk_24c) {
        if (!Math_ApproachS32(&src->y, 0x1400, q, 0x1000, 0xcd)) {
            o->unk_24c = 0;
        }
    } else {
        GroundInfo g;
        s32 v;
        g.initAtPos((VecFx32 *)(src), 0, 1);
        if (g.waterKind != 0) {
            v = g.waterSurfaceY;
            if (o->state == 0x11) {
                Insect_SplashIfWater(o);
                o->stateTimer = 0;
                Insect_Despawn(o);
                return;
            }
        } else {
            v = g.getHeight(1);
            if (v > 0x4000) {
                v = Ground_GetDefaultY();
            } else {
                v += Ground_GetDefaultY();
            }
        }
        if (!Math_ApproachS32(&src->y, v, q, 0x1000, 0x266) && flag != 0 && st != 0xb && st != 9) {
            o->auxTimer = (Random_GlobalBelow(9) + 2) * 0x14;
            o->state = 0x13;
            o->model.setFrame(0);
            if (v < 0) {
                Insect_SplashIfWater(o);
                o->stateTimer = 0;
                Insect_Despawn(o);
            } else if (o->isAlarmed) {
                o->alarm = o->alarmThreshold - 10;
                o->isAlarmed = 0;
            }
        }
    }
    if (st == 9 || st == 0xb) {
        if (Insect_FadeOut(o, 1)) {
            Insect_Despawn(o);
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" s32 Hopper_CheckObstacle(Rec *o, s16 *p) {
    if (!gCommManager->isSlotActive(gCommManager->myAid) || NetArea_IsLocalOwner()) {
        s32 r = Insect_CheckObstacle(o, 0x50, 0xe38);
        if (r) {
            *p = 0;
            o->state = 0xf;
            o->turnAngle = Insect_ReflectAngle(o->rotY, r);
            o->behaviorWork |= 0xf00;
            o->behaviorWork++;
        }
        return r;
    }
    return 0;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Locust_PlaySe(Rec *o) {
    s32 t = o->kind;
    switch (t) {
    case 0xc:
    case 0xd:
        Insect_PlaySe(o, 0, 1);
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Cricket_Chirp(Rec *o) {
    s32 t = o->kind;
    switch (t) {
    case 0x1b:
    case 0x1c:
    case 0x1d:
        if (o->alarm < 5) {
            Insect_PlaySe(o, 0, 1);
        }
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Pondskater_Update(Rec *o) {
    s16 *p = &o->stateTimer;
    u8 *st = &o->state;
    switch (*st) {
    case 3:
    case 0xf:
        Pondskater_StartSkate(o, p);
        break;
    case 4:
        Pondskater_Skate(o, p);
        Pondskater_CheckObstacle(o, p);
        break;
    case 0xb:
        Crawler_Escape(o, p);
        *p = *p + 1;
        break;
    case 0x13:
        if (o->auxTimer <= 0) {
            *st = 3;
        } else {
            o->auxTimer = o->auxTimer - (TICK_STEP_ENDS() ? 1 : 0);
        }
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Mosquito_Update(Rec *o) {
    s16 *p = &o->stateTimer;
    switch (o->state) {
    case 0:
        (o)->mosquitoChase((s16 *)(void *)((V3 *)p));
        break;
    case 0xf: {
        s16 t = o->rotY;
        if (Math_StepAngle(&t, o->turnAngle, 0x5b0)) {
            o->state = 0;
        }
        Insect_PlaySe(o, 0, 1);
        o->rotY = t;
        break;
    }
    case 9:
    case 0xb:
        Crawler_Escape(o, p);
        *p = *p + 1;
        break;
    case 0x13:
        o->state = 0;
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Firefly_Update(Rec *o) {
    switch (o->state) {
    case 0:
        Firefly_Wander(o);
        break;
    case 9:
    case 0xb:
        if (o->stateTimer == 0) {
            Insect_PlaySe(o, 1, 0);
        }
        TreeBug_FlyOff(o, &o->stateTimer);
        break;
    case 7:
        o->state = 0;
        o->rotY = o->rotY + o->turnAngle;
        break;
    case 0x13: {
        o->isAlarmed = 0;
        o->state = 0;
        s16 t = o->rotY;
        Insect_SetMoveTarget(o, t, Insect_GetFlutterRange(o));
        V3 *s = &o->position;
        V3 *d = &o->homePos;
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
        break;
    }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Firefly_Wander(Rec *o) {
    s16 t = o->rotY;
    s16 *p = &o->stateTimer;
    if (!gCommManager->isSlotActive(gCommManager->myAid) || NetArea_IsLocalOwner()) {
        if (Insect_CheckAlarm(o) == 2) {
            Insect_SetAnimSpeed(o, 0x1000);
            o->isAlarmed = 0;
        }
    }
    Insect_FlutterSteer(o, &t, 0x38e, 0x28, 0x50, o->moveSpeed << 12);
    s32 r = Random_GlobalBelow(4);
    r = FX_Div(0x2000, (r + 5) << 12);
    *p = *p + (s16)r;
    Insect_FlutterBob(o, *p, 0x1000, (Random_GlobalBelow(4) + 10) << 12);
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s11 {
extern "C" void Bee_Update(Rec *o) {
    switch (o->state) {
    case 0:
        Insect_PlaySe(o, 0, 1);
        (o)->beeChasePlayer();
        break;
    case 2:
        Insect_PlaySe(o, 0, 1);
        (o)->beeSwarmDescend();
        break;
    case 3:
    case 7:
    case 8:
        Bee_StretchSwarm(&o->scale, 0);
        Bee_StingAndLeave(o);
        break;
    case 0xb:
        Insect_PlaySe(o, 0, 1);
        Insect_FlapWings(o);
        Insect_FlyAwayArc(o, 0x1333);
        break;
    case 4:
        (o)->beeEnterSwarm();
        break;
    case 1:
    case 5:
    case 6:
    case 9:
    case 10:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    }
    o->inView = 1;
}
}
#undef func_02133150

namespace s10 {
extern "C" void Hoverer_Update(Rec *self) {
    switch (self->state) {
    case 0:
        (self)->hovererFly();
        break;
    case 6:
        Crawler_Wander(self);
        Insect_UpdateRest(self);
        break;
    case 9:
    case 11:
        Insect_FlapWings(self);
        Insect_PlaySe(self, 0, 1);
        Insect_FlyAwayArc(self, 0x1ccd);
        break;
    case 7:
        self->state = 0;
        if (self->isAlarmed != 0) {
            self->rotY = self->rotY + self->turnAngle;
        }
        break;
    case 19:
        self->isAlarmed = 0;
        self->state = 0;
        break;
    }
}
}

namespace s10 {
extern "C" void Ant_Update(Rec *self) {
    switch (self->state) {
    case 11:
        Insect_HopArc(self, &self->stateTimer);
        break;
    case 9:
        Insect_EscapeRun(self, &self->stateTimer);
        break;
    case 7:
    case 8:
        if (Insect_FadeOut(self, 4)) {
            NNS_G3dMdlSetMdlAlpha((void *)((PooledModel *)(&self->pooledModel))->getModel(), 0, 0);
            self->state = 0x13;
            V3 *p = &self->position;
            p->x = 0;
            p->y = 0;
            p->z = 0;
            TownJunkInsects_Refresh();
        }
        break;
    case 18: {
        BlockMap *g = TownBlockMap_Get();
        V3 *pos = &self->position;
        s32 x, y;
        FieldPos_ToUnit(&x, &y, pos);
        s32 lx = *(volatile s32 *)&x;
        s32 ly = *(volatile s32 *)&y;
        s32 hx = lx >> 4;
        s32 hy = ly >> 4;
        u16 *p = BlockMap_GetItemPtr(g, hx, hy, lx - (hx << 4), ly - (hy << 4), 0);
        BOOL r = FALSE;
        u32 v = *p;
        if (v >= 0x154a && v <= 0x1553) {
            r = TRUE;
        }
        if (r == 0 || Insect_IsAtWateringPoint(pos) != 0) {
            self->state = 7;
        }
        break;
    }
    }
}
}

namespace s10 {
extern "C" void MoleCricket_Update(Rec *self) {
    s16 *cnt = &self->stateTimer;
    switch (self->state) {
    case 4:
    case 17:
        Insect_PlaySe(self, 1, 1);
        MoleCricket_Burrow(self, cnt);
        break;
    case 5:
    case 11:
        Insect_HopArc(self, cnt);
        break;
    case 9:
        Insect_EscapeRun(self, cnt);
        break;
    case 19:
        MoleCricket_CheckDugUp(self, cnt);
        break;
    }
}
}

namespace s10 {
extern "C" void MoleCricket_CheckDugUp(Rec *self, s16 *cnt) {
    V3 *pos = &self->position;
    Actor *o = Insect_FindNearestPlayer(pos);
    if (Insect_CheckDigHit(self, pos)) {
        if (o != 0) {
            s32 a = Math_AngleXZ(pos, &o->position);
            self->state = 5;
            NNS_G3dMdlSetMdlAlpha((void *)((PooledModel *)(&self->pooledModel))->getModel(), 0, 0x1f);
            self->rotY = a + 0x8000;
            *cnt = 0;
        }
    } else {
        if (o != 0) {
            if (Vec_DistXZ(pos, &o->position) < 0x5000) {
                self->cooldownTimer = 0x3c;
            }
        }
        s32 t = self->cooldownTimer;
        if (t > 0) {
            Insect_PlaySe(self, 0, 1);
            self->cooldownTimer = t - 1;
        }
    }
}
}

namespace s10 {
extern "C" void Insect_HopArc(Rec *self, s16 *cnt) {
    V3 *pos = &self->position;
    volatile V3 saved;
    saved.x = pos->x;
    saved.y = pos->y;
    saved.z = pos->z;
    V3 v;
    s32 lim;
    GroundInfo g;
    g.initAtPos((VecFx32 *)(pos), 0, 1);
    if (self->kind == 0x35) {
        self->rotY = 0;
        Insect_GetDirVec(&v, self->rotZ);
    } else {
        Insect_GetDirVec(&v, self->rotY);
    }
    if (self->state == 5 || Insect_CheckObstacle(self, 0x50, 0xe38) == 0) {
        pos->x += TICK_PART(func_01ffcb0c((self->moveSpeed + 2) << 12, v.x));
        pos->z += TICK_PART(func_01ffcb0c((self->moveSpeed + 2) << 12, v.z));
    }
    if (self->state == 9 || self->state == 11) {
        switch (self->kind) {
        case 0x1f:
        case 0x18:
        case 0x35:
        case 0x36:
        case 0x37: {
            s32 n = *cnt;
            pos->y = pos->y - n * (n * 10);
            break;
        }
        default: {
            s32 n = *cnt;
            pos->y = pos->y + n * (160 - n * 11);
            break;
        }
        }
    } else {
        s32 n = *cnt;
        pos->y = pos->y + n * (200 - n * 11);
    }
    if (g.waterKind != 0) {
        lim = g.waterSurfaceY;
    } else {
        lim = g.getHeight(0);
        if (lim > 0x4000) {
            lim = 0;
            pos->x = saved.x;
            pos->z = saved.z;
        }
    }
    if (pos->y <= lim && *cnt > 0) {
        if (g.isBelowWaterSurface(pos->y)) {
            Insect_Despawn(self);
            Insect_SplashIfWater(self);
        } else {
            if (self->state == 0xb) {
                if (self->kind == 0x1f) {
                    self->moveSpeed = 4;
                } else if (self->kind == 0x31) {
                    self->auxTimer = 0;
                    if ((((u32)self->model.curFrame << 4) >> 16) != 1) {
                        ((AnimModel *)(&self->model))->setFrame(1);
                    }
                }
                self->state = 9;
            } else {
                self->state = 4;
                if (self->kind == 0x31) {
                    ((AnimModel *)(&self->model))->setFrame(1);
                }
                if (self->kind == 0x31 || self->kind == 0x1e) {
                    if ((gCommManager)->isSlotActive(gCommManager->myAid) && NetArea_IsLocalOwner()) {
                        Insect_SetMoveTarget(self, self->rotY, 0xc000);
                    }
                }
            }
            self->alarm = 0;
            *cnt = 0;
            pos->y = lim + Ground_GetDefaultY();
            if (self->kind != 0x35) {
                self->rotX = 0;
            }
        }
    } else {
        *cnt = *cnt + 2;
    }
}
}

namespace s10 {
extern "C" void Insect_EscapeRun(Rec *self, s16 *cnt) {
    V3 *pos = &self->position;
    s32 mul = 2;
    s8 r7 = self->kind;
    V3 v;
    s16 r6;
    GroundInfo g;
    g.initAtPos((VecFx32 *)(pos), 0, 1);
    if (Insect_FadeOut(self, 1)) {
        Insect_Despawn(self);
    }
    if (Insect_SteerAroundObstacle(self)) {
        return;
    }
    if (g.waterKind != 0) {
        if (g.isBelowWaterSurface(pos->y)) {
            Insect_Despawn(self);
            Insect_SplashIfWater(self);
        } else {
            pos->y = pos->y - 0x100;
        }
        return;
    }
    pos->y = pos->y - 0x200;
    if (r7 == 0x35) {
        r6 = self->rotZ;
        Insect_GetDirVec(&v, r6);
    } else {
        if ((u8)(s8)(r7 - 0x36) <= 1) {
            mul = 4;
        }
        r6 = self->rotY;
        Insect_GetDirVec(&v, r6);
    }
    if (r7 == 0x1f) {
        s32 c = *cnt;
        if (c == 0) {
            r6 = r6 + FX_Div(0x2000, 0x6000);
        } else if (c % 16 == 0) {
            r6 = r6 + 0x71c;
        } else if (c % 8 == 0) {
            r6 = r6 - 0x71c;
        }
    } else {
        s32 c = *cnt;
        if (c == 0) {
            r6 = r6 + FX_Div(0x2000, 0x6000);
        } else if (c % 4 == 0) {
            r6 = r6 + 0xaaa;
        } else if (c % 2 == 0) {
            r6 = r6 - 0xaaa;
        }
    }
    if (r7 == 0x35) {
        self->rotZ = r6;
        self->rotY = 0;
    } else {
        self->rotY = r6;
    }
    if (r7 == 0x1a) {
        pos->z += TICK_PART(func_01ffcb0c(func_01ffcb0c(self->moveSpeed << 12, v.z), 0x400));
        pos->x += TICK_PART(func_01ffcb0c(func_01ffcb0c(self->moveSpeed << 12, v.x), 0x400));
    } else {
        pos->x += TICK_PART(func_01ffcb0c(v.x, (mul * self->moveSpeed) << 12));
        s32 vz = *(volatile s32 *)&v.z;
        mul = mul * self->moveSpeed;
        pos->z += TICK_PART(func_01ffcb0c(vz, mul << 12));
    }
    *cnt = *cnt + 1;
}
}

namespace s10 {
extern "C" void MoleCricket_Burrow(Rec *self, s16 *cnt) {
    s32 r4 = self->auxTimer;
    if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
        if (Insect_GroundWalkNet(self) != 0) {
            return;
        }
    } else {
        if (Insect_GroundWalk(self) == 0) {
            return;
        }
    }
    self->auxTimer = r4 - 1;
    if (r4 == 5) {
        s32 x, y;
        FieldPos_ToUnit(&x, &y, &self->position);
        if (Ground_GetDigKind(x, y) == 0 && gCommManager->isSlotActive(gCommManager->myAid) == 0) {
            EffectSpl_CreateOneShot(0x80, &self->position, 0, gEffectSplDefaultInitCbs);
        } else {
            self->state = 9;
        }
    } else if (r4 <= 0) {
        s32 c = *cnt;
        if (c < 2) {
            self->rotY = self->rotY - 0xaaa;
        } else {
            r4 = c + 1;
            if (r4 % 4 == 0) {
                self->rotY = self->rotY + 0xaaa;
            } else if (r4 % 2 == 0) {
                self->rotY = self->rotY - 0xaaa;
            }
        }
        *cnt = 0;
        Insect_Despawn(self);
    }
}
}

namespace s10 {
extern "C" s32 Insect_SteerAroundObstacle(Rec *self) {
    s32 t = Insect_CheckObstacle(self, 0x50, 0xe38);
    s32 ret = 0;
    u32 c = self->cooldownTimer;
    if (t != 0) {
        s16 r;
        s32 m = self->kind;
        if (m == 0x35) {
            r = self->rotZ;
        } else {
            r = self->rotY;
        }
        if (t == 3) {
            if (c == 1 || c == 10) {
                r -= 0xaaa;
            } else {
                r += 0xaaa;
            }
        } else if (t == 1 || c == 1) {
            r -= 0x38e;
            c = 1;
        } else if (t == 2 || c == 2) {
            r += 0x38e;
            c = 2;
        }
        if (m == 0x35) {
            self->rotZ = r;
        } else {
            self->rotY = r;
        }
        ret = 1;
    } else if (c < 10) {
        c = (u8)(c * 10);
    }
    self->cooldownTimer = c;
    return ret;
}
}

namespace s10 {
extern "C" void PillBug_Update(Rec *self) {
    s16 *cnt = &self->stateTimer;
    switch (self->state) {
    case 4:
    case 17:
        PillBug_Walk(self);
        break;
    case 11:
        if ((((u32)self->model.curFrame << 4) >> 16) == 1) {
            ((AnimModel *)(&self->model))->setFrame(0);
        }
    case 5:
        Insect_HopArc(self, cnt);
        break;
    case 9:
        Insect_EscapeRun(self, cnt);
        break;
    case 7:
        PillBug_Curled(self);
        break;
    case 19:
        Insect_CheckRockStrike(self, cnt);
        if ((((u32)self->model.curFrame << 4) >> 16) != 0) {
            ((AnimModel *)(&self->model))->setFrame(0);
        }
        break;
    }
}
}

namespace s09 {
extern "C" void PillBug_Curled(Rec *self) {
    s32 r4 = self->auxTimer;
    V3 *pos = &self->position;
    if (Insect_CheckDigHit(self, pos)) {
        r4 = 1;
    }
    if (r4 <= 0) {
        if (Insect_FadeOut(self, 1)) {
            Insect_Despawn(self);
        }
    } else {
        V3 out;
        Insect_UpdateAlarm(self, &out);
        if (out.x != 0) {
            self->auxTimer = r4 - 1;
            if (self->alarm < self->alarmThreshold) {
                self->state = 4;
                ((AnimModel *)(&self->model))->setFrame(1);
                s32 a = Math_AngleXZ(pos, &out);
                self->rotY = a + 0x8000;
                if ((gCommManager)->isSlotActive(gCommManager->myAid) && NetArea_IsLocalOwner()) {
                    Insect_SetMoveTarget(self, self->rotY, 0xc000);
                }
            }
        }
    }
}
}

namespace s09 {
extern "C" void PillBug_Walk(Rec *self) {
    V3 *pos = &self->position;
    s32 r4 = self->auxTimer;
    if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
        if (Insect_GroundWalkNet(self) != 0) {
            return;
        }
    } else {
        if (Insect_GroundWalk(self) == 0) {
            return;
        }
    }
    V3 out;
    Insect_UpdateAlarm(self, &out);
    if (self->alarm >= self->alarmThreshold &&
        ((gCommManager)->isSlotActive(gCommManager->myAid) == 0 || NetArea_IsLocalOwner() != 0 ||
         (self->targetPos.x == self->position.x && self->targetPos.z == self->position.z))) {
        self->state = 7;
        ((AnimModel *)(&self->model))->setFrame(0);
        if ((gCommManager)->isSlotActive(gCommManager->myAid) && NetArea_IsLocalOwner()) {
            V3 *src = &self->position;
            V3 *dst = &self->targetPos;
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    } else if (r4 <= 0) {
        if (Insect_FadeOut(self, 1)) {
            Insect_Despawn(self);
        }
    } else {
        if (Insect_CheckDigHit(self, pos)) {
            r4 = 1;
        }
        self->auxTimer = r4 - 1;
    }
}
}

namespace s09 {
extern "C" BOOL Insect_CheckRockStrike(Rec *self, s16 *out) {
    s8 *p = &self->hitCountdown;
    V3 *sub = &self->position;
    if (*p <= 0) {
        if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
            s8 i;
            for (i = 0; i < 4; i++) {
                *p = PlayerActor_GetStrikeCountdownAt(sub, i);
                if (*p > 0) {
                    break;
                }
            }
        } else {
            *p = PlayerActor_GetStrikeCountdownAt(sub, 4);
        }
    }
    s8 c = *p;
    if (c > 0) {
        c--;
        *p = c;
        if (*p == 0) {
            Actor *o = Insect_FindNearestPlayer(sub);
            if (o) {
                s32 v = Math_AngleXZ(sub, &o->position);
                self->state = 5;
                NNS_G3dMdlSetMdlAlpha((void *)((PooledModel *)(&self->pooledModel))->getModel(), 0, 0x1f);
                self->rotY = v + 0x8000;
                *out = 0;
                return TRUE;
            }
        }
    }
    return FALSE;
}
}

namespace s09 {
extern "C" void Moth_Update(Rec *self) {
    u8 *p;
    p = &self->state;
    switch (*p) {
    case 0:
        Moth_CircleLight(self);
        break;
    case 9:
    case 11:
        Insect_FlyAwayArc(self, 0x1ccd);
        break;
    case 7:
        Insect_FlutterFlight(self);
        break;
    case 0x13:
        self->isAlarmed = 0;
        *p = 0;
        break;
    }
}
}

namespace s09 {
extern "C" void Flea_Update(Rec *self) {
    u32 st = self->state;
    switch (st) {
    case 6:
        Insect_SteerAroundObstacle(self);
        if (Insect_TickTimer(self)) {
            self->state = 0xb;
        }
        break;
    case 11: {
        s16 *p = &self->stateTimer;
        V3 *pos = &self->position;
        s32 rnd, d1, d2;
        volatile V3 save;
        save.x = pos->x;
        save.y = pos->y;
        save.z = pos->z;
        s32 y0 = self->baseHeight;
        GroundInfo g;
        g.initAtPos((VecFx32 *)(pos), 0, 1);
        Insect_SetScale(self, 200);
        if (Insect_SteerAroundObstacle(self) == 0) {
            V3 v;
            Insect_GetDirVec(&v, self->rotY);
            pos->x += TICK_PART(func_01ffcb0c(self->moveSpeed << 12, v.x));
            pos->z += TICK_PART(func_01ffcb0c(self->moveSpeed << 12, v.z));
        }
        if (y0 > 0x1000) {
            d1 = *p << 12;
            pos->y = y0 + func_01ffcb0c(0x59a - func_01ffcb0c(0xcd, d1), d1);
        } else {
            d2 = *p << 12;
            pos->y = y0 + func_01ffcb0c(0x99a - func_01ffcb0c(0xcd, d2), d2);
        }
        if (g.waterKind != 0) {
            y0 = g.waterSurfaceY;
        } else {
            y0 = g.getHeight(1);
            y0 += Ground_GetDefaultY();
            if (y0 > 0x1000) {
                if (y0 > 0x4000) {
                    y0 = Ground_GetDefaultY();
                } else {
                    pos->x = save.x;
                    pos->z = save.z;
                }
            }
        }
        if (pos->y < y0) {
            rnd = Random_GlobalBelow(3);
            *p = 0;
            pos->y = y0;
            if (g.isBelowWaterSurface(pos->y)) {
                Insect_Despawn(self);
                Insect_SplashIfWater(self);
            } else {
                self->state = 6;
                self->waitTimer = 4;
                self->baseHeight = y0;
                s32 t;
                if (Random_GlobalBelow(100) > 0x32 && (t = self->behaviorWork - rnd) > 0) {
                    self->moveSpeed = t;
                } else {
                    self->moveSpeed = rnd + self->behaviorWork;
                }
            }
        } else {
            *p = *p + 1;
        }
        if (Insect_FadeOut(self, 1)) {
            Insect_Despawn(self);
        }
        break;
    }
    }
}
}

namespace s09 {
extern "C" void Stinger_Update(Rec *self) {
    s32 r = 0;
    u8 st = self->state;
    V3 *pos = &self->position;
    s16 *p23e = &self->unk_23e;
    AnimModel *sub = &self->model;
    if (MenuCtrl_IsMenuOpen() == 0) {
        if (PlayerActor_LocalHoldsNet()) {
            self->playerHoldsNet = 1;
        } else {
            self->playerHoldsNet = 0;
        }
    }
    if (self->unk_24c == 0 && st != 0xb && st != 9) {
        r = Stinger_UpdateChase(self, &self->despawnTimer);
        if (self->state != 5) {
            if (r == 1) {
                return;
            }
            if (self->kind == 0x37 && r == 0) {
                u32 m = ((u32)sub->curFrame << 4) >> 16;
                if (m > 3) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*sub))->setup(3, 3, 0x1000, m);
                } else if (m == 3) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)*sub))->setup(3, 0, 0x1000, 0);
                }
            }
        }
    }
    switch (st) {
    case 4:
    case 5:
    case 7:
        Stinger_Walk(self, &self->unk_23e, r);
        break;
    case 11:
        Insect_HopArc(self, &self->stateTimer);
        break;
    case 9:
        Insect_PlaySe(self, 0, 1);
        Insect_EscapeRun(self, &self->stateTimer);
        break;
    case 3: {
        volatile u32 w32;
        *(volatile s16 *)&w32 = self->rotY;
        if (Math_StepAngle((s16 *)&w32, self->turnAngle, 0x666)) {
            self->state = 4;
        }
        self->rotY = *(volatile s16 *)&w32;
        break;
    }
    case 0x13:
        if (self->unk_24c != 0) {
            s32 k = *p23e;
            if (k == 0 || self->kind == 0x37) {
                self->state = 3;
                self->waitTimer = 100;
                s32 j = self->rotY;
                s32 t = Insect_RandomTurn(8, 1);
                self->turnAngle = t + j + 0x8000;
                *p23e = 0;
            } else if (pos->y > 0 && self->kind == 0x36) {
                s32 t = func_01ffcb0c(FX_Div(0x1000, 0x12000), k << 12);
                pos->y += TICK_PART(t + k * k * -10);
                *p23e = *p23e + 3;
                if (pos->y <= 0) {
                    *p23e = 0;
                }
            }
        } else if (Insect_TickTimer(self)) {
            self->state = 3;
            self->waitTimer = Random_GlobalBelow(3) * 20;
            s32 j = self->rotY;
            s32 t = Insect_RandomTurn(16, 1);
            self->turnAngle = t + j;
        }
        break;
    }
}
}

namespace s09 {
extern "C" void DungBeetle_Update(Rec *self) {
    switch (self->state) {
    case 4:
        (self)->dungBeetlePushSnowball();
        break;
    case 5:
        (self)->dungBeetleWalk();
        break;
    case 9:
    case 11:
        TreeBug_FlyOff(self, &self->stateTimer);
        break;
    case 0x13:
        ((AnimModel *)(&self->model))->setFrame(3);
        self->state = 4;
        break;
    }
}
}

namespace s09 {
extern "C" BOOL Insect_FadeOut(Rec *self, s32 a) {
    PooledModel *p = &self->pooledModel;
    s32 t = NNS_G3dMdlGetMdlAlpha(p->getModel(), 0);
    if (t > 7) {
        NNS_G3dMdlSetMdlAlpha(p->getModel(), 0, t - a);
    } else {
        return TRUE;
    }
    return FALSE;
}
}

namespace s09 {
extern "C" BOOL Insect_GroundWalk(Rec *self) {
    BOOL result;
    s16 *cnt;
    V3 v;
    GroundInfo g;
    V3 *pos = &self->position;
    cnt = &self->stateTimer;
    s32 r6 = 2;
    result = TRUE;
    g.initAtPos((VecFx32 *)(pos), 0, result);
    s8 r7 = self->kind;
    Insect_GetDirVec(&v, self->rotY);
    if (g.waterKind != 0) {
        if (g.isBelowWaterSurface(pos->y)) {
            Insect_Despawn(self);
            Insect_SplashIfWater(self);
            result = FALSE;
        } else {
            pos->y -= TICK_PART(0x200);
        }
    } else {
        pos->y -= TICK_PART(0x200);
    }
    if (Insect_SteerAroundObstacle(self)) {
        self->unk_24b = 0;
        return TRUE;
    }
    if ((u8)(s8)(r7 - 0x36) <= 1) {
        if (self->state == 5) {
            if (self->unk_23e > 0 && r7 != 0x37) {
                r6 = 12;
            } else {
                r6 = 7;
            }
        } else {
            r6 = 4;
        }
    }
    s32 o;
    s32 sp;
    if (self->kind == 0x37) {
        sp = 0x71c;
    } else {
        sp = 0xaaa;
    }
    s32 c = *cnt;
    if (c == 0) {
        o = self->rotY;
        self->rotY = o + FX_Div(sp, 0x2000);
    } else if (c % 4 == 0) {
        self->rotY = sp + self->rotY;
    } else if (c % 2 == 0) {
        self->rotY = self->rotY - sp;
    }
    pos->x += TICK_PART(func_01ffcb0c(v.x, (r6 * self->moveSpeed) << 12));
    pos->z += TICK_PART(func_01ffcb0c(v.z, (r6 * self->moveSpeed) << 12));
    *cnt = *cnt + 1;
    self->unk_24b = 1;
    return result;
}
}

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" s32 Insect_GroundWalkNet(Rec *self) {
    V3 *pos = &self->position;
    s16 *cnt = &self->stateTimer;
    s32 ret = 0;
    GroundInfo o;
    o.initAtPos(pos, ret, 1);
    V3 *vel = &self->targetPos;
    V3 dir;
    Insect_GetDirVec(&dir, self->rotY);
    s32 nang;
    if (NetArea_IsLocalOwner() != 0 || self->state == 0x11) {
        if (o.waterKind != 0) {
            if (o.isBelowWaterSurface(pos->y) != 0) {
                Insect_Despawn(self);
                Insect_SplashIfWater(self);
                ret = 2;
            } else {
                pos->y = pos->y - 0x200;
                ret = 1;
            }
        }
    }
    if (Insect_SteerAroundObstacle(self) != 0) {
        self->unk_24b = 0;
        s32 c = *cnt;
        if (c < 2) {
            nang = (s16)(self->rotY - 0xaaa);
        } else {
            s32 n = c + 1;
            if (n % 4 == 0) {
                nang = (s16)(self->rotY + 0xaaa);
            } else if (n % 2 == 0) {
                nang = (s16)(self->rotY - 0xaaa);
            }
        }
        Insect_SetMoveTarget(self, nang, 0xc000);
        return 0;
    }
    s32 r;
    if (self->kind == 0x1e) {
        r = Math_ApproachVecXZ(pos, vel, 0x28, 0x1000, 0x19a);
    } else {
        r = Math_ApproachVecXZ(pos, vel, 8, 0x1000, 0x52);
    }
    if (r == 0) {
        if (NetArea_IsLocalOwner() != 0) {
            if (Insect_SetMoveTarget(self, self->rotY, 0xc000) == 0) {
                vel->x += data_02135f44[((u16)self->rotY >> 4) * 2];
                vel->z += data_02135f44[(((u16)self->rotY >> 4) * 2 + 1)];
                return 0;
            }
        }
    } else {
        self->rotY = Math_AngleXZ(pos, vel);
    }
    s32 c = *cnt;
    if (c == 0) {
        s32 a = self->rotY;
        self->rotY = a + FX_Div(0x2000, 0x6000);
    } else if (c % 4 == 0) {
        self->rotY = self->rotY + 0xaaa;
    } else if (c % 2 == 0) {
        self->rotY = self->rotY - 0xaaa;
    }
    (*cnt)++;
    self->unk_24b = 1;
    return ret;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void Insect_ClampStepXZ(V3 *out, V3 *in, s32 c) {
    s32 lim = FX_Div(c << 12, 0x40000);
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    out->y = 0;
    s32 x = in->x;
    if (x >= 0) {
        if (x > lim) {
            out->x = lim;
        }
    } else {
        s32 n = -lim;
        if (x < n) {
            out->x = n;
        }
    }
    s32 z = in->z;
    if (z >= 0) {
        if (z > lim) {
            out->z = lim;
        }
    } else {
        lim = -lim;
        if (z < lim) {
            out->z = lim;
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void Spider_Update(Rec *self) {
    s16 *cnt = &self->stateTimer;
    NNS_G3dMdlGetMdlAlpha(((PooledModel *)(&self->pooledModel))->getModel(), 0);
    s32 st = self->state;
    if (st != 0xb && st != 9) {
        s32 xy[2];
        V3 q(self->behaviorWork, 0, self->position.z + 0x3e8);
        FieldPos_ToUnit(&xy[0], &xy[1], &q);
        BlockMap *g = TownBlockMap_Get();
        if (g) {
            s32 x = *(volatile s32 *)&xy[0];
            s32 y = *(volatile s32 *)&xy[1];
            s32 hx = x >> 4;
            s32 hy = y >> 4;
            u16 *cell = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
            if (cell) {
                if (!Unk_ov003_0222a8d0_Chk(cell)) {
                    if (Insect_FadeOut(self, 3)) {
                        Insect_Despawn(self);
                        return;
                    }
                }
            }
        }
    }
    switch (st) {
    case 2:
        if (self->unk_24c != 0) {
            self->unk_24c = 0;
            self->rotZ = 0x6b;
        } else {
            self->unk_24c = 1;
            self->rotZ = -0x6b;
        }
        if ((((u32)self->model.curFrame << 4) >> 16) == 0x38) {
            self->state = 0x13;
            self->rotZ = 0;
            self->position.x = self->behaviorWork;
            NNS_G3dMdlSetMdlAlpha(((PooledModel *)(&self->pooledModel))->getModel(), 0, 0);
        }
        break;
    case 1:
        if ((((u32)self->model.curFrame << 4) >> 16) == 0x20) {
            self->auxTimer = (Random_GlobalBelow(4) + 0xc) * 0x14;
            self->state = 0x12;
            *cnt = 0;
        }
        break;
    case 11:
        Insect_HopArc(self, cnt);
        break;
    case 9:
        Insect_EscapeRun(self, cnt);
        break;
    case 0x12:
        if ((self)->spiderSway()) {
            self->rotY = 0;
            self->state = 2;
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(0x39, 1, 0x1000, 0x20);
        }
        break;
    case 0x13:
        if ((self)->spiderCheckPlayerHit()) {
            self->state = 1;
            self->alarm = 0;
            ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(0x21, 1, 0x1000, 0);
            NNS_G3dMdlSetMdlAlpha(((PooledModel *)(&self->pooledModel))->getModel(), 0, 0x1f);
        } else {
            self->model.playMode = 1;
        }
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void TreeBug_Update(Rec *self) {
    s16 *cnt = &self->stateTimer;
    u32 st = self->state;
    if (st != 0xb && st != 9 && st != 7) {
        if (self->kind == 0x1f) {
            Walkingstick_CheckAlarm(self, cnt);
        } else {
            TreeBug_CheckAlarm(self, cnt);
            self->isAlarmed = 0;
        }
    }
    switch (st) {
    case 3:
        TreeBug_Wiggle(self, cnt);
        break;
    case 2:
        TreeBug_ClimbUp(self, cnt);
        break;
    case 1:
        TreeBug_ClimbDown(self, cnt);
        break;
    case 9:
        Insect_EscapeRun(self, cnt);
        (*cnt)++;
        break;
    case 11:
        if (self->kind != 0x1f) {
            TreeBug_FlyOff(self, cnt);
        } else {
            Insect_HopArc(self, cnt);
        }
        break;
    case 7:
        self->isAlarmed = 1;
        TreeBug_DropAndFly(self, cnt);
        break;
    case 8:
        if (Insect_FadeOut(self, 2)) {
            Insect_Despawn(self);
        }
        break;
    case 0:
    case 4:
    case 5:
    case 6:
    case 10:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        break;
    case 19:
        TreeBug_Idle(self, cnt);
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void TreeBug_Idle(Rec *self, s16 *cnt) {
    if ((u8)(s8)(self->kind - 0x10) <= 4) {
        u8 f = self->canSing;
        if (f != 0 && self->alarm < 10) {
            u8 c = self->cooldownTimer;
            if (c == 0 && f != 0) {
                Insect_PlaySe(self, 0, 1);
            } else {
                self->cooldownTimer = c - 1;
            }
        } else {
            self->cooldownTimer = 0x3c;
        }
    } else {
        u8 rnd = Random_GlobalBelow(100);
        if (self->kind == 9) {
            u32 st = ((u32)self->model.curFrame << 4) >> 16;
            if (st == 0xd || st < 9) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(9, 1, 0, 9);
            }
            if (*cnt > 0x50) {
                if (rnd > 0x5c && st < 0xa) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(0xe, 1, 0x1000, 9);
                }
                if (*cnt > 0xa0) {
                    *cnt = 0;
                }
            }
            (*cnt)++;
        } else if (rnd > 0x46) {
            (*cnt)++;
            if (*cnt % 0x14 == 0) {
                if (rnd < 0x55) {
                    self->state = 3;
                } else {
                    self->state = 2;
                }
                *cnt = 0;
            }
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void TreeBug_ClimbUp(Rec *self, s16 *cnt) {
    s32 ang = self->rotY;
    s32 lim = self->baseHeight + 0x400;
    V3 *pos = &self->position;
    s32 c = *cnt;
    if (c >= 8) {
        if (Random_GlobalBelow(100) > 0x46) {
            self->state = 1;
        }
        *cnt = 0;
    } else {
        if (c >= 2 && c < 6) {
            ang = (s16)(ang - 0x16b);
            self->rotX -= 0xb6;
        } else {
            ang = (s16)(ang + 0x16b);
            self->rotX += 0xb6;
        }
        pos->y += TICK_PART(0x20);
        (*cnt)++;
        if (pos->y > lim) {
            pos->y = lim;
        }
    }
    self->rotY = ang;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void TreeBug_ClimbDown(Rec *self, s16 *cnt) {
    s32 ang = self->rotY;
    s32 lim = self->baseHeight - 0x100;
    V3 *pos = &self->position;
    s32 c = *cnt;
    if (c >= 8) {
        if (Random_GlobalBelow(100) > 0x46) {
            self->state = 0x13;
        }
        *cnt = 0;
    } else {
        if (c >= 2 && c < 6) {
            ang = (s16)(ang - 0x16b);
            self->rotX -= 0xb6;
        } else {
            ang = (s16)(ang + 0x16b);
            self->rotX += 0xb6;
        }
        pos->y -= TICK_PART(0x20);
        (*cnt)++;
        if (pos->y < lim) {
            pos->y = lim;
        }
    }
    self->rotY = ang;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void TreeBug_Wiggle(Rec *self, s16 *cnt) {
    s32 ang = self->rotY;
    s32 c = *cnt;
    if (c == 0) {
        if (Random_GlobalBelow(100) < 0x32) {
            *cnt = 1;
        } else {
            *cnt = -1;
        }
    } else if ((c > 0 && c <= 6) || (c > 0x12 && c <= 0x18) || !(c >= -6 || c < -0x12)) {
        if (c > 0) {
            (*cnt)++;
            self->rotX += 0xb6;
        } else {
            (*cnt)--;
            self->rotX -= 0xb6;
        }
        ang = (s16)(ang + 0x16b);
    } else if ((c > 6 && c <= 0x12) || (c < 0 && c >= -6) || !(c >= -0x12 || c < -0x18)) {
        if (c > 0) {
            (*cnt)++;
            self->rotX -= 0xb6;
        } else {
            (*cnt)--;
            self->rotX += 0xb6;
        }
        ang = (s16)(ang - 0x16b);
    } else {
        *cnt = 0;
        self->state = 0x13;
    }
    self->rotY = ang;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s08 {
extern "C" void TreeBug_FlyOff(Rec *self, s16 *cnt) {
    s32 t, mode;
    V3 *pos;
    u32 st;
    pos = &self->position;
    st = ((u32)self->model.curFrame << 4) >> 16;
    mode = self->kind;
    t = FX_Div(*cnt << 12, 0x4000);
    AnimModel *s = &self->model;
    V3 v;
    Insect_GetDirVec(&v, self->rotY);
    if (*cnt == 0) {
        Insect_PlaySe(self, 1, 0);
    }
    v.y = func_01ffcb0c(func_01ffcb0c(0x100, t), t);
    if (Insect_CheckObstacle(self, 0x50, 0xe38) == 0) {
        v.x = v.x << 4;
        v.z = v.z << 4;
    }
    VEC_Add(pos, &v, pos);
    (*cnt)++;
    if (mode == 0x14) {
        if ((((u32)s->numFrames << 4) >> 16) < 0x18) {
            s->AnimFrameCtrl::setup(0x1a, 0, 0x1000, 0x18);
        } else if ((((u32)s->curFrame << 4) >> 16) < 0x18) {
            s->curFrame = 0x18000;
        }
    } else if (self->kind == 9) {
        if (s->playMode != 0) {
            s->AnimFrameCtrl::setup(9, 0, 0x1000, 0);
        }
    } else {
        s->setFrame(st == 1 ? 2 : 1);
    }
    if (Insect_FadeOut(self, 1)) {
        Insect_Despawn(self);
    }
}
}
#undef func_02133150

namespace s07 {
extern "C" void TreeBug_DropAndFly(Rec *o, s16 *p) {
    V3 *pos = &o->position;
    s32 st = o->kind;
    if (st != 0x10 && st != 0x11 && st != 0x12 && st != 0x13) {
        Insect_PlaySe(o, 0, 1);
    }
    if (o->rotY >= 0) {
        pos->x += TICK_PART(0x200);
    } else {
        pos->x -= TICK_PART(0x200);
    }
    if (Insect_FadeOut(o, 1)) {
        Insect_Despawn(o);
    } else {
        s32 t = FX_Div(*p << 12, 0x4000);
        pos->y += TICK_PART(func_01ffcb0c(func_01ffcb0c(0x100, t), t));
        *p = *p + 1;
        if (o->state == 0xb && (o->rotY == 0x6001 || o->rotY == -0x6001)) {
            pos->z -= TICK_PART(0x100);
        } else {
            pos->z += TICK_PART(0x100);
        }
        if (st == 0x14) {
            if (((o->model.numFrames << 4) >> 16) < 0x18) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(0x1a, 0, 0x1000, 0x18);
            } else if ((((u32)o->model.curFrame << 4) >> 16) < 0x18) {
                *(u32 *)&o->model.curFrame = 0x18000;
            }
        } else {
            Insect_FlapWings(o);
        }
    }
}
}

namespace s07 {
extern "C" void Walkingstick_CheckAlarm(Rec *o, s16 *p) {
    if (o->alarm == 0xfe) {
        o->state = 8;
    } else {
        V3 tv;
        Insect_UpdateAlarm(o, &tv);
        if (tv.x != 0) {
            s16 v = DS_DIV(((o->alarmThreshold - o->alarm) * 31), o->alarmThreshold);
            if (v <= 0) {
                Insect_Despawn(o);
                o->isAlarmed = 1;
                *p = 0;
            } else {
                if (v > 0x1f) {
                    v = 0x1f;
                }
                NNS_G3dMdlSetMdlAlpha(o->pooledModel.getModel(), 0, v);
            }
        }
    }
}
}

namespace s07 {
extern "C" void TreeBug_CheckAlarm(Rec *o, s16 *p) {
    V3 *pos = &o->position;
    s32 n = o->alarm;
    V3 tv;
    Insect_UpdateAlarm(o, &tv);
    if (tv.x != 0 && o->isAlarmed == 0) {
        s32 lim = o->alarmThreshold;
        if (n >= lim) {
            s32 a;
            if (tv.x > pos->x) {
                a = (s16)0xffff9554;
            } else {
                a = 0x6aac;
            }
            o->rotY = a;
            o->rotX = 0xd55;
            o->state = 7;
            o->isAlarmed = 1;
            ((AnimModel *)(&o->model))->setFrame(1);
            s32 z = 0;
            *p = z;
            Insect_PlaySe(o, 1, z);
            if (o->kind == 9) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(9, 0, 0x1000, 0);
            }
        } else if (o->kind == 0x14) {
            if (n * 2 >= lim || o->cooldownTimer != 0) {
                if ((((u32)o->model.curFrame << 4) >> 16) == 0) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(4, 1, 0x1000, 0);
                    o->cooldownTimer = 0x3c;
                } else if (o->cooldownTimer != 0) {
                    o->cooldownTimer -= TICK_STEP_ENDS() ? 1 : 0;
                }
            } else {
                s32 m = (s32)(*(u32 *)&o->model.curFrame) >> 12;
                if ((u16)m != 0 || ((o->model.numFrames << 4) >> 16) != 0) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(0, 3, 0x1000, (u16)m);
                }
            }
        }
    }
}
}

namespace s07 {
extern "C" void Crawler_Update(Rec *o) {
    s16 *p = &o->stateTimer;
    if ((u8)(s8)(o->kind - 0xe) <= 1 && (((u32)o->model.curFrame << 4) >> 16) != 0) {
        if (o->state == 4 || o->state == 0x13) {
            Actor *r = PlayerActor_GetActor(4);
            if (r != 0) {
                o->rotY = Math_AngleXZ(&o->position, &r->position);
            }
            o->state = 0x13;
        }
    }
    switch (o->state) {
    case 4:
        Crawler_Wander(o);
        if (o->kind == 0x1a) {
            if (*p > 0x140 || (*p % 20 == 0 && Random_GlobalBelow(100) > 0x5a && *p > 0xa0)) {
                o->state = 0x13;
                *p = 0;
            }
        } else {
            if (*p > 0xa0 || (*p % 20 == 0 && Random_GlobalBelow(100) > 0x5a && *p > 0x50)) {
                o->state = 0x13;
                *p = 0;
            }
        }
        Crawler_Watch(o, p);
        break;
    case 7:
        o->state = 9;
        o->rotY = o->turnAngle;
        *p = 0;
    case 9:
        Crawler_Escape(o, p);
        break;
    case 11:
        if (o->kind == 0x1a) {
            Insect_HopArc(o, p);
        } else {
            Crawler_Escape(o, p);
        }
        break;
    case 0x13:
        if (o->kind == 0x1a) {
            if ((((u32)o->model.curFrame << 4) >> 16) == 2) {
                if (*p > 0xa0 || (*p % 20 == 0 && Random_GlobalBelow(100) > 0x55 && *p >= 0x28)) {
                    *p = 0;
                    o->state = 4;
                }
            }
        } else {
            if (*p > 0x38 || (*p % 5 == 0 && Random_GlobalBelow(100) > 0x55 && *p > 0)) {
                o->state = 4;
                *p = 0;
            }
        }
        Crawler_Watch(o, p);
        break;
    }
    *p = *p + 1;
}
}

namespace s07 {
extern "C" BOOL Insect_IsOnFlower(VecFx32 *pp) {
    BlockMap *g = TownBlockMap_Get();
    if (g != 0) {
        s32 xy[2];
        FieldPos_ToUnit(&xy[0], &xy[1], pp);
        s32 hy, hx, x, y;
        x = *(volatile s32 *)&xy[0];
        y = *(volatile s32 *)&xy[1];
        hx = x >> 4;
        hy = y >> 4;
        u16 *c = BlockMap_GetItemPtr(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
        if (c != 0) {
            if (Unk_ov003_02229dcc_Chk(c)) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
}

namespace s07 {
extern "C" void Crawler_Watch(Rec *o, s16 *p) {
    Actor *r4 = PlayerActor_GetActor(4);
    V3 *q = &o->position;
    if (Insect_IsOnFlower(q) == 0) {
        o->alarm = 0xfe;
    }
    o->isAlarmed = 0;
    Insect_CheckAlarm(o);
    if (r4 != 0) {
        s32 d = Vec_DistXZ(&r4->position, q);
        s32 n = o->alarm;
        s32 st;
        if (d <= 0xccd) {
            o->state = 9;
            *p = 0;
        } else if (st = o->kind, (u8)(s8)(st - 0xe) <= 1) {
            if (n > 0x14) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(9, 1, 0x1000, (((u32)o->model.curFrame << 4) >> 16));
                o->cooldownTimer = 0x3c;
            } else if (o->cooldownTimer != 0) {
                o->cooldownTimer -= TICK_STEP_ENDS() ? 1 : 0;
            } else if (d < o->disturbRadius) {
                u32 m = (((u32)o->model.curFrame << 4) >> 16);
                if (m == 0) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(4, 1, 0x1000, 0);
                } else if (m > 4) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(4, 3, 0x1000, m);
                }
            } else {
                u32 m = (((u32)o->model.curFrame << 4) >> 16);
                if (m != 0) {
                    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)o->model))->setup(0, 3, 0x1000, m);
                }
            }
        } else if (st == 0x1a) {
            if (n > 0x14) {
                u32 m = (((u32)o->model.curFrame << 4) >> 16);
                if (m == 2) {
                    ((AnimModel *)(&o->model))->setFrame(1);
                } else if (m == 1) {
                    ((AnimModel *)(&o->model))->setFrame(0);
                    o->state = 0x13;
                    o->cooldownTimer = 0x3c;
                }
            } else {
                s32 t = (s32)(*(u32 *)&o->model.curFrame) >> 12;
                if ((u16)t == 0 && o->cooldownTimer == 0) {
                    ((AnimModel *)(&o->model))->setFrame(1);
                } else if ((u16)t == 1) {
                    ((AnimModel *)(&o->model))->setFrame(2);
                } else if (o->cooldownTimer != 0) {
                    o->cooldownTimer -= TICK_STEP_ENDS() ? 1 : 0;
                }
            }
        }
    }
}
}

namespace s07 {
extern "C" void Crawler_Wander(Rec *o) {
    V3 *hi = &o->wanderBoxMax;
    V3 *lo = &o->wanderBoxMin;
    s16 a = o->rotY;
    u8 flip = o->unk_24b;
    struct { V3 d; V3 save; } l;
    l.d.x = 0;
    l.d.y = 0;
    l.d.z = 0;
    V3 *p = &o->position;
    l.save.x = p->x;
    l.save.y = p->y;
    l.save.z = p->z;
#define d l.d
#define save l.save
    if (Random_GlobalBelow(100) > 0x50) {
        if (o->frameCounter % 20 == 0) {
            if (flip == 0) {
                flip = 1;
            } else {
                flip = 0;
            }
            o->unk_24b = flip;
        }
        if (flip != 0) {
            if (o->kind == 0x33) {
                a = a + (s16)o->behaviorWork;
            } else {
                a = a + 0xaaa;
            }
        } else {
            if (o->kind == 0x33) {
                a = a + 0xaaa;
            } else {
                a = a - (s16)o->behaviorWork;
            }
        }
    }
    Insect_GetDirVec(&d, a);
    o->rotY = a;
    p->z += FX_Div(func_01ffcb0c(o->moveSpeed << 12, d.z), 0x20000);
    p->x += FX_Div(func_01ffcb0c(o->moveSpeed << 12, d.x), 0x20000);
    if (p->x < lo->x || p->x > hi->x) {
        p->x = save.x;
    }
    if (p->z < lo->z || p->z > hi->z) {
        p->z = save.z;
    }
    if (o->kind != 0x33) {
        if (p->z != save.z) {
            p->y = p->y - (p->z - save.z);
        }
        if (p->y < lo->y && p->y > hi->y) {
            p->y = save.y;
        }
    }
}
#undef d
#undef save
}

namespace s07 {
extern "C" void Insect_PlaceOnPlantSide(Rec *o) {
    V3 *p = &o->position;
    if (Random_GlobalBelow(2) == 0) {
        p->x += FX_Div(0x7000, 0x10000);
        p->y = FX_Div(0xc000, 0x10000);
        p->z += FX_Div(0x3000, 0x10000);
    } else {
        p->x -= FX_Div(0x7000, 0x10000);
        p->y = FX_Div(0xc000, 0x10000);
        p->z += FX_Div(0x3000, 0x10000);
    }
}
}

namespace s06 {
extern "C" void Insect_SetWanderBox(Rec *self) {
    VecFx32Ctor *r5 = &self->position;
    VecFx32Ctor *r4 = &self->wanderBoxMin;
    VecFx32Ctor *r6 = &self->wanderBoxMax;
    if (self->kind == 0x33) {
        r4->x = r5->x - FX_Div(0x6000, 0x10000);
        r4->y = FX_Div(0xa000, 0x10000);
        r4->z = r5->z - FX_Div(0x4000, 0x10000);
        r6->x = r5->x + FX_Div(0x6000, 0x10000);
        r6->y = FX_Div(0xc000, 0x10000);
        r6->z = r5->z + FX_Div(0x4000, 0x10000);
    } else if (self->kind == 0x19) {
        r4->x = r5->x - 0x6000;
        r4->z = r5->z + 0x6000;
        r6->x = r5->x + 0x6000;
        r6->z = r5->z - 0x6000;
    } else {
        r4->x = r5->x - FX_Div(0x9000, 0x10000);
        r4->y = FX_Div(0x9000, 0x10000);
        r4->z = r5->z - FX_Div(0x2000, 0x10000);
        r6->x = r5->x + FX_Div(0x9000, 0x10000);
        r6->y = 0x1000;
        r6->z = r5->z + FX_Div(0x5000, 0x10000);
    }
}
}

namespace s06 {
extern "C" void Insect_Despawn(Rec *self) {
    self->lifeState = 4;
    NNS_G3dMdlSetMdlAlpha(self->pooledModel.getModel(), 0, 0);
}
}

namespace s06 {
extern "C" void Crawler_Escape(Rec *self, s16 *pp) {
    if (self->kind != 0x1a) {
        VecFx32Ctor *r6 = &self->position;
        VecFx32Ctor v;
        if (Insect_CheckObstacle(self, 0x50, 0xe38) == 0) {
            Insect_GetDirVec(&v, self->rotY);
            if (self->state == 0xb) {
                v.x = func_01ffcb0c(v.x, 0xa000);
                v.z = func_01ffcb0c(v.z, 0xa000);
            } else {
                v.x = func_01ffcb0c(v.x, 0xf000);
                v.z = func_01ffcb0c(v.z, 0xf000);
            }
        } else {
            v.x = 0;
            v.z = 0;
        }
        s32 t = *pp;
        v.y = t * ((t + 0xc) * 2);
        if ((u8)(s8)(self->kind - 0xe) <= 1) {
            if (((self->model.numFrames << 4) >> 16) != 0xb) {
                ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(0xb, 0, 0x1000, 9);
            } else if ((((u32)self->model.curFrame << 4) >> 16) < 9) {
                *(u32 *)&self->model.curFrame = 0x9000;
            }
        } else {
            Insect_FlapWings(self);
        }
        if (*pp == 0) {
            Insect_PlaySe(self, 1, 0);
        }
        if (Insect_FadeOut(self, 1)) {
            Insect_Despawn(self);
        }
        VEC_Add(r6, &v, r6);
    } else {
        Insect_EscapeRun(self, pp);
        u32 m = (((u32)self->model.curFrame << 4) >> 16);
        if (m == 0) {
            self->model.setFrame(1);
        } else if (m == 1) {
            self->model.setFrame(2);
        }
    }
}
}

namespace s06 {
extern "C" void Insect_InitBehavior(Rec *self, s16 a1, s32 a2, s32 a3, s16 s0, s16 s1, s32 s2, s32 s3, u32 s4, u32 s5) {
    GroundInfo b;
    VecFx32Ctor *p = &self->position;
    b.initAtPos(p, 0, 0);
    VecFx32Ctor *q = &self->scale;
    s32 r6 = FX_Div(s2 << 12, 0x10000);
    s32 r0 = FX_Div(a3 << 12, 0x10000);
    if (self->state != 0xb && self->state != 0x10) {
        self->state = 0x13;
        self->rotY = s1;
        VecFx32Ctor *d = &self->targetPos;
        d->x = p->x;
        d->y = p->y;
        d->z = p->z;
        if (*(u8 *)&s5) {
            p->y = r6 + b.waterSurfaceY;
        } else {
            p->y = r6;
        }
    }
    self->rotX = s0;
    self->alarmThreshold = a2;
    self->disturbRadius = r0;
    if (self->kind != 0x23) {
        self->behaviorWork = 0;
    }
    self->moveSpeed = *(u8 *)&s4;
    self->unk_23e = 0;
    self->alarm = 0;
    self->baseHeight = p->y + s3;
    self->waitTimer = a1;
    q->x = 0x1000;
    q->y = 0x1000;
    q->z = 0x1000;
    self->targetHeight = self->baseHeight;
    self->despawnTimer = 0;
    self->hitCountdown = 0;
}
}

namespace s06 {
extern "C" s16 Insect_RandomAngle() {
    u32 r = (u8)Random_GlobalBelow(0x10);
    if (r > 8) {
        r = -(r - 8);
    }
    return (s16)(r * 0xaaa);
}
}

namespace s06 {
extern "C" void Insect_UpdateButterfly(Rec *self) {
    Butterfly_Update(self);
}
}

namespace s06 {
extern "C" void Insect_InitFlutter(Rec *self, s32 a, s32 b, s32 c, u8 d, s32 e) {
    s32 r = Random_GlobalBelow(3);
    Insect_InitBehavior(self, (s16)((r + 5) * 0x14), a, b, 0, Insect_RandomAngle(), c, 0, d, 0);
    self->cooldownTimer = 0x28;
    self->unk_256 = Random_GlobalBelow(0x12);
    self->unk_24c = 1;
    self->behaviorWork = e;
    self->auxTimer = 0;
}
}

namespace s06 {
extern "C" void Insect_InitButterfly(Rec *self) {
    switch (self->kind) {
    case 0:
        Insect_InitFlutter(self, 0x64, 0x50, 0x25, 8, 0x119a);
        break;
    case 1:
        Insect_InitFlutter(self, 0x64, 0x50, 0x25, 8, 0x119a);
        break;
    case 2:
        Insect_InitFlutter(self, 0x50, 0x50, 0x28, 9, 0x1000);
        break;
    case 3:
        Insect_InitFlutter(self, 0x50, 0x50, 0x28, 9, 0x1000);
        break;
    case 4:
        Insect_InitFlutter(self, 0x3c, 0x50, 0x2f, 0xa, 0xe66);
        break;
    case 5:
        Insect_InitFlutter(self, 0x46, 0x50, 0x14, 0xc, 0x1000);
        break;
    case 6:
        Insect_InitFlutter(self, 0x64, 0x1e, 0x32, 0xf, 0x1000);
        break;
    case 7:
        Insect_InitFlutter(self, 0x3c, 0x50, 0x34, 0xc, 0x1000);
        break;
    default:
        Insect_InitFlutter(self, 0x3c, 0x50, 0x2d, 0xa, 0x1000);
        break;
    }
}
}

namespace s06 {
extern "C" void Insect_UpdateMoth(Rec *self) {
    Moth_Update(self);
}
}

namespace s06 {
extern "C" void Insect_InitMoth(Rec *self) {
    VecFx32Ctor *d = &self->perchPos;
    Insect_InitBehavior(self, 0x384, 0xc8, 0x28, 1, -0x8000, 0x2f, 0, 0xa, 0);
    self->cooldownTimer = 0x3c;
    self->unk_256 = Random_GlobalBelow(0x12);
    self->unk_24c = 1;
    self->targetHeight = 0;
    VecFx32Ctor *s = &self->position;
    self->perchPos.x = s->x;
    d->y = s->y;
    d->z = s->z;
    Insect_SetAnimSpeed(self, 0x1000);
}
}

namespace s06 {
extern "C" void Insect_InitFirefly(Rec *self) {
    s32 t = self->behaviorWork;
    Insect_InitBehavior(self, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 6, 1);
    self->behaviorWork = t;
    self->cooldownTimer = 0x3c;
}
}

namespace s06 {
extern "C" void Insect_UpdateFirefly(Rec *self) {
    Firefly_Update(self);
}
}

namespace s06 {
extern "C" void Insect_InitMosquito(Rec *self) {
    Insect_InitBehavior(self, 0, 0, 0, 0, 0, 0x19, 0, 0x19, 0);
}
}

namespace s06 {
extern "C" void Insect_UpdateMosquito(Rec *self) {
    Mosquito_Update(self);
}
}

namespace s06 {
extern "C" void Insect_PlaceOnTrunk(Rec *self, s32 a, s32 b, s32 c, s32 d) {
    VecFx32Ctor *v = &self->position;
    if (self->kind == 0x1f && self->state == 0xb) {
        Insect_InitBehavior(self, 0, a, b, 0, 0, 0, 0, 0, 0);
    } else {
        Insect_InitBehavior(self, 0, a, b, 0x3556, -0x8000, c, 0, 0, 0);
        v->z += d;
        self->canSing = 1;
    }
}
}

namespace s06 {
extern "C" void Insect_UpdateTreeBug(Rec *self) {
    TreeBug_Update(self);
}
}

namespace s06 {
extern "C" void Insect_InitTreeBug(Rec *self) {
    switch (self->kind) {
    case 0x2f:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x2e:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x2d:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x2c:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x28:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x29:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x2a:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x26:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x21:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x27:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x2b:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x22:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x24:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    case 0x1f:
        Insect_PlaceOnTrunk(self, 0xfa, 0x50, 0x16, 0x1f4);
        self->moveSpeed = 1;
        break;
    case 9:
        Insect_PlaceOnTrunk(self, 0x96, 0x46, 0x18, 0x3e8);
        self->moveSpeed = 0xa;
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)self->model))->setup(((self->model.numFrames << 4) >> 16), 1, 0x1000, 0);
        break;
    case 0x10:
        Insect_PlaceOnTrunk(self, 0x64, 0x50, 0x19, 0x3e8);
        break;
    case 0x11:
        Insect_PlaceOnTrunk(self, 0x64, 0x50, 0x19, 0x3e8);
        break;
    case 0x12:
        Insect_PlaceOnTrunk(self, 0x64, 0x50, 0x19, 0x3e8);
        break;
    case 0x13:
        Insect_PlaceOnTrunk(self, 0x64, 0x50, 0x19, 0x3e8);
        break;
    case 0x14:
        Insect_PlaceOnTrunk(self, 0x64, 0x50, 0x19, 0x3e8);
        self->cooldownTimer = 0;
        break;
    case 0x34:
        Insect_PlaceOnTrunk(self, 0x82, 0x3c, 0x16, 0x3e8);
        break;
    default:
        Insect_PlaceOnTrunk(self, 0x64, 0x50, 0x19, 0x3e8);
        break;
    }
}
}

namespace s06 {
extern "C" void Insect_InitHop(Rec *self, s32 a, s32 b, s32 c, u8 d) {
    Insect_InitBehavior(self, 0x3b6, a, b, 0, Insect_RandomAngle(), 0, 0, c, 0);
    self->auxTimer = (Random_GlobalBelow(9) + 2) * 0x14;
    self->moveTargetDist = d;
    self->position.y = 0;
}
}

namespace s06 {
extern "C" void Insect_UpdateHopper(Rec *self) {
    Hopper_Update(self);
}
}

namespace s06 {
extern "C" void Insect_InitHopper(Rec *self) {
    switch (self->kind) {
    case 0x1d:
        Insect_InitHop(self, 0x3c, 0x46, 6, 1);
        break;
    case 0x1b:
        Insect_InitHop(self, 0x3c, 0x46, 6, 1);
        break;
    case 0xc:
        Insect_InitHop(self, 0x3c, 0x50, 8, 2);
        break;
    case 0xd:
        Insect_InitHop(self, 0x3c, 0x50, 8, 3);
        break;
    case 0x1c:
        Insect_InitHop(self, 0x3c, 0x46, 8, 1);
        break;
    }
}
}

namespace s05 {
extern "C" void Insect_InitDragonflyParams(Insect *a, s32 x, s32 y, s32 z, u8 p4, u8 p5) {
    s16 r = Insect_RandomAngle();
    Insect_InitBehavior(a, 0, x, y, 0, r, z, 0, p4, 0);
    a->moveTargetDist = p5;
}
}

namespace s05 {
extern "C" void Insect_InitDragonfly(Insect *a) {
    switch (a->kind) {
    case 0x15:
        Insect_InitDragonflyParams(a, 0xc8, 0x3c, 0x28, 0x14, 1);
        break;
    case 0x16:
        Insect_InitDragonflyParams(a, 0xc8, 0x28, 0x2d, 0x1e, 3);
        break;
    case 0x17:
        Insect_InitDragonflyParams(a, 0x64, 0x46, 0x32, 0x78, 0x1e);
        break;
    }
}
}

namespace s05 {
extern "C" void Insect_UpdateDragonfly(Insect *a) {
    Dragonfly_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitPondskater(Insect *a) {
    Insect_InitBehavior(a, 0, 0x28, 0x50, 0, 0, 0, 0, 3, 1);
    Insect_SetWanderBox(a);
    a->auxTimer = Random_GlobalBelow(0x14) * 3;
}
}

namespace s05 {
extern "C" void Insect_UpdatePondskater(Insect *a) {
    Pondskater_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitOnPlant(Insect *a, s32 x, s32 y, s32 z, s16 w) {
    s16 r = Insect_RandomAngle();
    Insect_InitBehavior(a, 0, x, y, 0, r, 0xe, 0, z, 0);
    Insect_SetWanderBox(a);
    if (a->state != 0xb) {
        Insect_PlaceOnPlantSide(a);
    }
    a->behaviorWork = w;
}
}

namespace s05 {
extern "C" void Insect_UpdateCrawler(Insect *a) {
    Crawler_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitCrawler(Insect *a) {
    switch (a->kind) {
    case 0x1a:
        Insect_InitOnPlant(a, 0xc8, 0x3c, 4, 0x38e);
        break;
    case 0x20:
        Insect_InitOnPlant(a, 0x82, 0x3c, 0x10, 0x71c);
        break;
    case 0xe:
        Insect_InitOnPlant(a, 0x96, 0x32, 0x18, 0x71c);
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)a->model))->setup(0, 3, 0x1000, 1);
        break;
    case 0xf:
        Insect_InitOnPlant(a, 0x96, 0x32, 0x18, 0x71c);
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)a->model))->setup(0, 3, 0x1000, 1);
        break;
    }
}
}

namespace s05 {
extern "C" void Insect_InitBurrower(Insect *a) {
    if (a->kind == 0x1e) {
        Insect_InitBehavior(a, 0, 0x28, 0x50, 0, 0, 0, 0, 4, 0);
    } else {
        Insect_InitBehavior(a, 0, 0xdc, 0x3c, 0, 0, 0, 0, 1, 0);
    }
    a->auxTimer = 0x168;
    if (a->state != 0xb && a->state != 0x10) {
        NNS_G3dMdlSetMdlAlpha(a->pooledModel.getModel(), 0, 0);
    }
}
}

namespace s05 {
extern "C" void Insect_UpdateMoleCricket(Insect *a) {
    MoleCricket_Update(a);
}
}

namespace s05 {
extern "C" void Insect_UpdatePillBug(Insect *a) {
    PillBug_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitBee(Insect *a) {
    if (a->state == 0x13) {
        NNS_G3dMdlSetMdlAlpha(a->pooledModel.getModel(), 0, 0);
    }
    Insect_InitBehavior(a, 0, 0x5a, 0x3c, 0, 0, 2, 0, 0, 0);
    a->behaviorWork = 0;
}
}

namespace s05 {
extern "C" void Insect_UpdateBee(Insect *a) {
    Bee_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitHoneybee(Insect *a) {
    Insect_InitFlutter(a, 0xc8, 0x3c, 0x25, 9, 0x1000);
    Insect_SetWanderBox(a);
}
}

namespace s05 {
extern "C" void Insect_UpdateHoneybee(Insect *a) {
    Hoverer_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitFly(Insect *a) {
    Insect_InitFlutter(a, 0x96, 0x1e, 0x25, 0x12, 0x1000);
    Insect_SetWanderBox(a);
}
}

namespace s05 {
extern "C" void Insect_UpdateFly(Insect *a) {
    Hoverer_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitFlea(Insect *a) {
    Insect_InitBehavior(a, 0, 0x5a, 0x3c, 0, 0, 0x3c, 0, 8, 1);
    a->behaviorWork = a->moveSpeed;
    a->baseHeight = a->position.y;
}
}

namespace s05 {
extern "C" void Insect_UpdateFlea(Insect *a) {
    Flea_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitSpider(Insect *a) {
    s16 t = Random_GlobalBelow(0xb) + 5;
    VecFx32Ctor *p = &a->position;
    t = t * 0x14;
    Insect_InitBehavior(a, t, 0x5a, 0x40, 0, 0, 0x28, 0, 3, 0);
    if (a->state != 0xb && a->state != 0x10) {
        a->behaviorWork = p->x;
        NNS_G3dMdlSetMdlAlpha(a->pooledModel.getModel(), 0, 0);
        p->z -= 0x7d0;
    } else {
        a->rotX = (s16)0xc000;
        a->rotZ = a->rotY;
    }
}
}

namespace s05 {
extern "C" void Insect_UpdateSpider(Insect *a) {
    Spider_Update(a);
}
}

namespace s05 {
extern "C" void Insect_UpdateStinger(Insect *a) {
    Stinger_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitTarantula(Insect *a) {
    Insect_InitBehavior(a, 0, 0x64, 0x5a, 0, 0, 0, 0, 4, 0);
    a->unk_24c = 0;
}
}

namespace s05 {
extern "C" void Insect_InitScorpion(Insect *a) {
    Insect_InitBehavior(a, 0, 0x64, 0x50, 0, 0, 0, 0, 5, 0);
    a->unk_24c = 0;
    ((AnimFrameCtrl *)(&(AnimFrameCtrl &)a->model))->setup(3, 0, 0x1000, 0);
}
}

namespace s05 {
extern "C" void Insect_InitAnt(Insect *a) {
    Insect_InitBehavior(a, 0, 0x50, 0x50, 0, 0, 0, 0, 1, 0);
}
}

namespace s05 {
extern "C" void Insect_UpdateAnt(Insect *a) {
    Ant_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitDungBeetle(Insect *a) {
    Insect_InitBehavior(a, 0, 0x50, 0x50, 0, 0, 0, 0, 3, 0);
}
}

namespace s05 {
extern "C" void Insect_UpdateDungBeetle(Insect *a) {
    DungBeetle_Update(a);
}
}

namespace s05 {
extern "C" void Insect_InitKind38(Insect *a) {
    Insect_InitTreeBug(a);
}
}

namespace s05 {
extern "C" void Insect_UpdateKind38(Insect *a) {
    TreeBug_Update(a);
}
}

namespace s05 {
extern "C"
void *InsectManager_Create() {
    return new InsectManager;
}
}

InsectManager::InsectManager() { using namespace s05;
    sWateringActive = 0;
}

InsectManager::~InsectManager() { using namespace s05;
}

BOOL InsectManager::allocHeldInsect(Insect *e) { using namespace s05;
    if (e->lifeState != 0) {
        s8 a = e->kind;
        u8 b = e->state;
        VecFx32Ctor v;
        VecFx32Ctor w;
        VecFx32Ctor *pv = &e->position;
        v.x = pv->x;
        v.y = pv->y;
        v.z = pv->z;
        pv = &e->targetPos;
        w.x = pv->x;
        w.y = pv->y;
        w.z = pv->z;
        s16 c = e->rotY;
        freeInsect(e, 3);
        e->kind = a;
        e->state = b;
        pv = &e->position;
        pv->x = v.x;
        pv->y = v.y;
        pv->z = v.z;
        e->rotY = c;
        pv = &e->targetPos;
        pv->x = w.x;
        pv->y = w.y;
        pv->z = w.z;
    }
    e->lifeState = 2;
    ((ModelSlotPool *)(&heldInsectPool))->acquire((u16 *)(&e->modelSlot));
    ((PooledModel *)(&e->pooledModel))->reset();
    e->inView = 1;
    return TRUE;
}

BOOL InsectManager::allocSpecialInsect(s32 id, s32 idx) { using namespace s05;
    Insect *e = &sSpecialInsects[idx];
    if (e->lifeState == 0) {
        ((ModelSlotPool *)(&specialInsectPool))->acquire((u16 *)(&e->modelSlot));
        ((PooledModel *)(&e->pooledModel))->reset();
        e->inView = 1;
        e->matAnim.anmObj = 0;
        e->matAnim.resMdl = 0;
        e->kind = (s8)id;
        e->lifeState = 2;
        return TRUE;
    }
    return FALSE;
}

BOOL InsectManager::allocFieldInsect(Insect *e) { using namespace s05;
    if (e->lifeState == 0) {
        e->lifeState = 2;
        ((ModelSlotPool *)(&fieldInsectPool))->acquire((u16 *)(&e->modelSlot));
        ((PooledModel *)(&e->pooledModel))->reset();
        e->inView = 0;
        return TRUE;
    }
    return FALSE;
}

void InsectManager::freeInsect(Insect *e, s32 mode) { using namespace s05;
    VecFx32Ctor *p = &e->position;
    VecFx32Ctor *q = &e->targetPos;
    if (e->kind == 0x33) {
        TownJunkInsects_Refresh();
    }
    if (e->kind >= 0) {
        ((AnimModel *)(&e->model))->detachAnim();
    }
    e->lifeState = 0;
    e->behaviorWork = 0;
    ((SndEnvChannel *)(&e->seEmitter))->callRelease();
    p->x = 1;
    p->y = 1;
    p->z = 1;
    q->x = 1;
    q->y = 1;
    q->z = 1;
    e->inUse = 0;
    e->inView = 0;
    e->inViewMask = 0;
    e->kind = -1;
    e->rotY = 0;
    e->stateTimer = 0;
    e->state = 0x13;
    ((PooledModel *)(&e->pooledModel))->unload();
    e->matAnim.anmObj = 0;
    e->matAnim.resMdl = 0;
    e->alarm = 0;
    e->isAlarmed = 0;
    e->despawnTimer = 0;
    if (mode == 1) {
        ((ModelSlotPool *)(&fieldInsectPool))->release((u16 *)(&e->modelSlot));
    } else if (mode == 2) {
        ((ModelSlotPool *)(&specialInsectPool))->release((u16 *)(&e->modelSlot));
    } else {
        ((ModelSlotPool *)(&heldInsectPool))->release((u16 *)(&e->modelSlot));
    }
    e->updateFn = 0;
}

BOOL InsectManager::onCreate() { using namespace s05;
    ((ModelSlotPool *)(&fieldInsectPool))->init(8, 0x400, 0x40, 0x9c4, (ModelSlotAllocFunc)((void *)FieldInsectHeap_Create), (ModelSlotFreeFunc)((void *)FieldInsectHeap_Destroy));
    ((ModelSlotPool *)(&specialInsectPool))->init(2, 0x400, 0x40, 0x6e8, (ModelSlotAllocFunc)((void *)SpecialInsectHeap_Create), (ModelSlotFreeFunc)((void *)SpecialInsectHeap_Destroy));
    ((ModelSlotPool *)(&heldInsectPool))->init(4, 0x400, 0x40, 0x9c4, (ModelSlotAllocFunc)((void *)HeldInsectHeap_Create), (ModelSlotFreeFunc)((void *)HeldInsectHeap_Destroy));
    CommManager *g = gCommManager;
    if (g->isSlotActive(g->myAid) == 0) {
        allocSpecialInsect(0x3a, 0);
        allocSpecialInsect(0x3b, 1);
    }
    InsectSpawn_BuildMasks();
    return TRUE;
}

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" void Insect_LoadModel(InsectManager *a, Rec *e, s32 mode) {
    struct { char name[0x11]; char path[0x17]; } l;
    void *m;
    void *h2;
    BOOL ok;
    void *p130;
    u8 *obj;
    InsectModelParams *rec;
    func_02133ef8(l.name, 0x11);
    func_02133ef8(l.path, 0x17);
    s32 t4 = e->kind;
    if (t4 < 0 || t4 >= 0x3c) {
        return;
    }
    if (t4 < 10) {
        Str_SPrintf(l.name, sInsectPathFmt0x, t4);
    } else if (t4 < 0x14) {
        Str_SPrintf(l.name, sInsectPathFmt1x, t4);
    } else if (t4 < 0x1e) {
        Str_SPrintf(l.name, sInsectPathFmt2x, t4);
    } else if (t4 < 0x28) {
        Str_SPrintf(l.name, sInsectPathFmt3x, t4);
    } else if (t4 < 0x32) {
        Str_SPrintf(l.name, sInsectPathFmt4x, t4);
    } else {
        Str_SPrintf(l.name, sInsectPathFmt5x, t4);
    }
    Str_SPrintf(l.path, sInsectModelExtFmt, l.name);
    if (!File_Exists(l.path)) {
        return;
    }
    void *h;
    if (mode == 0) {
        h = ((ModelSlotPool *)(&a->fieldInsectPool))->acquire((u16 *)(&e->modelSlot));
    } else if (mode == 1) {
        h = ((ModelSlotPool *)(&a->specialInsectPool))->acquire((u16 *)(&e->modelSlot));
    } else {
        h = ((ModelSlotPool *)(&a->heldInsectPool))->acquire((u16 *)(&e->modelSlot));
    }
    p130 = &e->pooledModel;
    if (!((PooledModel *)(p130))->loadFromSlot((ModelSlot *)(h), (const char *)(l.path))) {
        return;
    }
    obj = (u8 *)&e->model;
    ((Model *)(obj))->setResource((NNSG3dResMdl *)(((PooledModel *)(p130))->getModel()), NULL);
    rec = &sInsectModelParams[t4];
    if (rec->hasVisAnim != 0) {
        Str_SPrintf(l.path, sInsectVisAnimExtFmt, l.name);
    } else {
        Str_SPrintf(l.path, sInsectJointAnimExtFmt, l.name);
    }
    if (!File_Exists(l.path)) {
        return;
    }
    h2 = ((ModelSlot *)(h))->getHeap();
    void *r7;
    if (mode == 1) {
        if (t4 == 0x3a) {
            a->specialAnimFiles[0] = File_LoadAlloc(l.path, gCurrentHeap, 4, 0);
            r7 = a->specialAnimFiles[0];
        } else {
            a->specialAnimFiles[1] = File_LoadAlloc(l.path, gCurrentHeap, 4, 0);
            r7 = a->specialAnimFiles[1];
        }
    } else {
        r7 = File_LoadAlloc(l.path, h2, 4, 0);
    }
    if (r7 == 0) {
        return;
    }
    if (rec->hasVisAnim != 0) {
        m = func_021067a4(func_02106788(r7), 0);
    } else {
        m = func_021065f8(func_021065dc(r7), 0);
    }
    if (!((AnimModel *)(obj))->allocAnmObj(h2)) {
        return;
    }
    ok = TRUE;
    s32 sc = 0x1000;
    if (t4 == 0x35 || t4 == 9) {
        sc = 0;
    }
    ((BlendAnimModel *)(obj))->initAnim(m, 0, sc, 0, 0);
    ((AnimModel *)(obj))->attachAnim();
    if (t4 == 9) {
        ((AnimFrameCtrl *)(&(AnimFrameCtrl &)e->model))->setup(9, 1, 0, 9);
    }
    if ((u32)(t4 - 0x3a) <= 1) {
        Str_SPrintf(l.path, sInsectTexAnimPathFmt, t4);
        ok = FALSE;
        if (File_Exists(l.path)) {
            void *tex = File_LoadAlloc(l.path, h2, 4, 0);
            if (r7 != 0) {
                r7 = func_02106670(func_02106654(tex), 0);
                if (((ModelAnim *)(void *)(e))->allocMatAnm((NNSG3dResMdl *)(((Model *)obj)->resMdl), h2)) {
                    ((ModelAnim *)(e))->init(r7, 0, 0x1000, 0);
                    ((ModelAnim *)(void *)(e))->addToRenderObj(((Model *)(obj))->getRenderObj());
                    ok = TRUE;
                }
            }
        }
    }
    if (ok) {
        VecFx32Ctor *pv = &e->scale;
        VecFx32 sv = *(VecFx32 *)pv;
        ((SndEnvChannel *)(&e->seEmitter))->callReset();
        sInsectBehaviors[t4].init(e);
        e->updateFn = sInsectBehaviors[t4].update;
        e->lifeState = 3;
        e->isAlarmed = 0;
        Insect_SetModelMatrix(a, e, 0);
        if (mode == 2) {
            pv = &e->scale;
            pv->x = sv.x;
            pv->y = sv.y;
            pv->z = sv.z;
        }
    }
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" void Insect_UpdateHideTimer(InsectManager *a, Rec *e) {
    if (e->updateFn != 0) {
        s32 t = e->kind;
        switch (t) {
        case 0x1e:
            if (e->state == 4 || e->state == 5 || e->state == 0x11) {
                s32 v = e->auxTimer;
                if (v > 5) {
                    e->auxTimer = v - 1;
                } else {
                    Insect_Despawn(e);
                }
            }
            break;
        case 0x31:
            switch (e->state) {
            case 4:
            case 5:
            case 7:
            case 0x11: {
                s32 v = e->auxTimer;
                if (v > 0) {
                    e->auxTimer = v - 1;
                } else {
                    Insect_Despawn(e);
                }
                break;
            }
            }
            break;
        case 0x36:
        case 0x37: {
            s16 *p = &e->despawnTimer;
            s32 v = *p;
            if (v > 0 && v <= 0x12c) {
                if (v > 0x1f) {
                    *p = v - 1;
                } else {
                    Insect_Despawn(e);
                }
            }
            break;
        }
        }
    }
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" void Insect_Update(InsectManager *a, Rec *e, s32 flags, s32 kind) {
    u8 r4 = e->inView;
    s32 r7 = gCommManager->isSlotActive(gCommManager->myAid);
    if (r7 != 0 && e->inViewMask != 0) {
        r4 = 1;
    }
    if (r4 == 0) {
        Insect_UpdateHideTimer(a, e);
    }
    if (kind == 1) {
        if (r7 == 0 || NetArea_IsLocalOwner() != 0) {
            s16 *p = &e->outOfViewTimer;
            if (r4 != 0) {
                *p = 0x4b0;
            } else if (*p > 0) {
                s32 v = *p - 1;
                *p = v;
                if (*p == 0) {
                    e->lifeState = 4;
                    return;
                }
            }
        }
    }
    if (e->updateFn == 0) {
        return;
    }
    if (r4 == 0 && (u32)(kind - 2) > 1) {
        return;
    }
    s32 t4 = e->kind;
    u32 t7 = e->state;
    Insect_TickFrame(e);
    if (t7 == 0x10 || t4 < 0) {
        goto L258;
    }
    if (t7 == 0xa) {
        goto L226;
    }
    {
        volatile BOOL big;
        void *volatile pp;
        VecFx32Ctor v1, v2;
        VecFx32Ctor *pv = &e->position;
        v1.x = pv->x;
        v1.y = pv->y;
        v1.z = pv->z;
        pp = &e->bugNetTarget;
        Insect_CheckDisturbance(a, e);
        e->updateFn(e);
        if (Insect_UsesCollisionMove(a, e) != 0) {
            if (kind == 3) {
                {
                    struct { u8 b[0x44]; } w;
                    ((GroundInfo *)(&w))->initAtPos((VecFx32 *)(&e->position), 0, 0);
                    if (((GroundInfoBase *)(&w))->getHeight(0) > 0x4000) {
                        big = TRUE;
                    } else {
                        big = FALSE;
                    }
                    ((GroundInfo *)(&w))->~GroundInfo();
                }
                if (big) {
                    Collision_Move(&e->collisionState, &e->position, &v1, e->rotY, sInsectModelParams[t4].collisionRadius, 0, 0xa);
                    goto after;
                }
            }
            Collision_Move(&e->collisionState, &e->position, &v1, e->rotY, sInsectModelParams[t4].collisionRadius, 0, 0xb);
        }
    after:
        if (e->kind == 0x33 && flags == 0) {
            e->behaviorWork = 1;
        }
        flags |= 1 << (kind + 3);
        pv = &e->position;
        v2.x = pv->x;
        v2.y = pv->y;
        v2.z = pv->z;
        if (e->kind == 0x35) {
            u32 bits = ((u32)e->model.curFrame << 4) >> 16;
            if (bits >= 0x1e && bits < 0x28) {
                v2.y = v2.y - 0x1800;
            }
        }
        ((BugNetTarget *)pp)->submit(&v2, sInsectModelParams[t4].netRadius, 0xd48, (u8)flags);
    }
L226:
    if (sInsectModelParams[t4].hasVisAnim == 0) {
        ((AnimModel *)(&e->model))->stepAnim();
        if ((u8)(s8)(t4 - 0x3a) <= 1) {
            ((AnimFrameCtrl *)(e))->step();
            *(s32 *)e->matAnim.anmObj = e->matAnim.curFrame;
        }
    }
    goto L268;
L258:
    if (t4 == 0x14 || t4 == 0x37) {
        ((AnimModel *)(&e->model))->stepAnim();
    }
L268:
    if (t7 == 0xa) {
        ((InsectManager *)(a))->freeInsect(e, kind);
        return;
    }
    if (kind == 3 && t7 == 0x10) {
        Insect_SetModelMatrix(a, e, 1);
    } else {
        Insect_SetModelMatrix(a, e, 0);
    }
    {
        VecFx32Ctor v3;
        VecFx32Ctor *pv = &e->position;
        v3.x = pv->x;
        v3.y = pv->y;
        v3.z = pv->z;
        ((SndEnvChannel *)(&e->seEmitter))->callUpdateRelative((VecFx32 *)(&v3));
    }
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
BOOL InsectManager::onExecute() { using namespace s04;
    FieldInsect_UpdateAll(this);
    if ((gCommManager)->isSlotActive(gCommManager->myAid) == 0) {
        SpecialInsect_UpdateAll(this);
    }
    HeldInsect_UpdateAll(this);
    Insect_UpdateSpawning(this);
    return TRUE;
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" void Insect_CheckDisturbance(InsectManager *a, Rec *e) {
    VillagerActor *o;
    u8 ok;
    s32 px, py;
    if ((gCommManager)->isSlotActive(gCommManager->myAid) != 0) {
        if (NetArea_IsLocalOwner() != 0) {
            u8 i;
            s32 z0 = 0, z1 = 0;
            for (i = 0; i < 4; i++) {
                if (PlayerActor_GetSlotPosXZ(&ok, &px, &py, -1, i) && ok == 0 && PlayerActor_TestSlotFlag9(i)) {
                    VecFx32Ctor v;
                    v.x = px;
                    v.y = z0;
                    v.z = py;
                    s32 lim = e->disturbRadius;
                    BOOL t;
                    if (Vec_DistXZ(&e->position, &v) < lim) {
                        t = TRUE;
                    } else {
                        t = z1;
                    }
                    if (t) {
                        e->alarm = 0xfe;
                    }
                }
            }
        }
    } else {
        if (PlayerActor_TestSlotFlag9(4)) {
            Actor *p = PlayerActor_GetActor(4);
            if (p) {
                s32 lim = e->disturbRadius;
                if (Vec_DistXZ(&e->position, &p->position) < lim) {
                    e->alarm = 0xfe;
                }
            }
        } else {
            u8 i;
            void *pv = &e->position;
            for (i = 0; i < 8; i++) {
                o = (VillagerActor *)NpcRegistry_FindVillager(i);
                if (o) {
                    s32 lim = e->disturbRadius;
                    if (Vec_DistXZ(pv, &o->position) < lim) {
                        if (o->vfunc_ac()) {
                            e->alarm = 0xfe;
                        }
                    }
                }
            }
        }
    }
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" s32 FieldInsect_GetKindAndAlarm(u8 *out, u32 idx) {
    Rec *e = &sFieldInsects[(u8)(idx & 0xf)];
    s32 r = e->kind;
    if (r >= 0) {
        if (e->alarm >= e->alarmThreshold) {
            *out = 1;
        } else {
            *out = 0;
        }
    }
    return r;
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" BOOL FieldInsect_IsTreeKind(u32 idx) {
    Rec *e = &sFieldInsects[(u8)(idx & 0xf)];
    switch (e->kind) {
    case 9:
    case 16: case 17: case 18: case 19: case 20:
    case 31:
    case 33: case 34:
    case 36:
    case 38: case 39: case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47:
    case 52:
        return TRUE;
    case 10: case 11: case 12: case 13: case 14: case 15:
    case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
    case 32:
    case 35:
    case 37:
    case 48: case 49: case 50: case 51:
        break;
    }
    return FALSE;
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" s32 FieldInsect_GetPosAndKind(VecFx32Ctor *out, u32 idx) {
    Rec *e = &sFieldInsects[(u8)(idx & 0xf)];
    VecFx32Ctor *v = &e->position;
    out->x = v->x;
    out->y = v->y;
    out->z = v->z;
    return e->kind;
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

#define sInsectPathFmt0x "/insect/01/bug0%d"
#define sInsectPathFmt1x "/insect/11/bug%d"
#define sInsectPathFmt2x "/insect/21/bug%d"
#define sInsectPathFmt3x "/insect/31/bug%d"
#define sInsectPathFmt4x "/insect/41/bug%d"
#define sInsectPathFmt5x "/insect/51/bug%d"
#define sInsectModelExtFmt "%s.nsbmd"
#define sInsectVisAnimExtFmt "%s.nsbva"
#define sInsectJointAnimExtFmt "%s.nsbca"
#define sInsectTexAnimPathFmt "/insect/51/bug%d.nsbta"
namespace s04 {
extern "C" void Insect_UpdateSpawning(InsectManager *self) {
    s8 b[8];
    s32 px, py;
    s32 r4 = gCommManager->isSlotActive(gCommManager->myAid);
    if (r4 == 0 || NetArea_IsLocalOwner() != 0) {
        if (sInsectSpawnTimer % 20 == 0) {
            FieldInsect_PurgeStale();
        }
        sInsectSpawnTimer += TICK_STEP_ENDS() ? 1 : 0;
        u32 c = sInsectSpawnTimer;
        if (c == 0x3c) {
            Insect_TrySpawnRandom(self, 1, 0, -1);
            sInsectSpawnTimer = 0;
        } else if (c == 0x28 && r4 == 0) {
            b[0] = 0;
            b[1] = -1;
            if (Insect_PickSpecialSpawn(&b[0], &b[1], 1)) {
                if (Insect_TrySpawnRandom(self, 1, b[0], b[1])) {
                    sInsectSpawnTimer = 0;
                }
            }
        } else if (c == 0x14 && r4 == 0) {
            b[2] = 0;
            b[3] = -1;
            if (Insect_PickSpecialSpawn(&b[2], &b[3], 0)) {
if (Insect_Spawn(self, b[2], (u8)b[3], 2)) {
                    sSpecialInsects[1].antsAppear();
                    sAntSpawnEnabled = 0;
                }
            }
        }
    }
    if (r4 != 0) {
        u8 i;
        for (i = 0; i < 4; i++) {
            if (PlayerActor_GetSlotPosXZ((u8 *)&b[4], &px, &py, -1, i) && (u8)b[4] == 0) {
                InsectPool_UpdateInViewOfPlayer(self, 1, i, px, py);
            }
        }
    } else {
        InsectPool_UpdateInView(self, 1);
        InsectPool_UpdateInView(self, 2);
    }
}
}
#undef sInsectPathFmt0x
#undef sInsectPathFmt1x
#undef sInsectPathFmt2x
#undef sInsectPathFmt3x
#undef sInsectPathFmt4x
#undef sInsectPathFmt5x
#undef sInsectModelExtFmt
#undef sInsectVisAnimExtFmt
#undef sInsectJointAnimExtFmt
#undef sInsectTexAnimPathFmt

namespace s03 {
extern "C" void FieldInsect_UpdateAll(InsectManager *a) {
    u32 k;
    CommManager *g;
    FieldInsectUpdateLocals l;
    s32 v18, v1c;
    V3 t1, t2;
    Rec *o = sFieldInsects;
    v18 = 0;
    v1c = 0;
    l.index = 0;
    g = gCommManager;
    s32 neg = -1;
    goto test0;
loop0:
    {
        k = o->lifeState;
        V3 *p204;
        V3 *p1d4;
        if ((g)->isSlotActive(g->myAid)) {
            p204 = &o->position;
            p1d4 = &o->targetPos;
            l.netKind = neg;
            if (InsectNetSync_Set(a, l.index, o->kind, &p1d4->x, o->alarm, 1) == 0) {
                l.netAlarm = 0;
                if (InsectNetSync_Get(a, l.index, &l.netKind, &v18, &v1c, &l.netAlarm)) {
                    if (k == 0) {
                        if (v18 > 1) {
                            s32 t = l.netKind;
                            if (t >= 0) {
                                p204->x = v18;
                                p204->z = v1c;
                                p1d4->x = p204->x;
                                p1d4->y = p204->y;
                                p1d4->z = p204->z;
                                o->kind = t;
                                o->inUse = 1;
                                o->inView = 0;
                                { V3 *q = &o->homePos;
                                o->homePos.x = p204->x;
                                q->y = p204->y;
                                q->z = p204->z; }
                                o->lifeState = 2;
                            }
                        }
                    } else {
                        u32 c = l.netAlarm;
                        if (c == 0xff || v18 == 1) {
                            if (l.netKind == 0x1e) {
                                u32 st = o->state;
                                if (st == 9 || st == 0x11) goto sw0;
                            }
                            ((InsectManager *)(a))->freeInsect(o, 1);
                        } else {
                            if (p1d4->x == v18 && p1d4->z == v1c) {
                            } else {
                                p1d4->x = v18;
                                p1d4->z = v1c;
                                { V3 *q = &o->homePos;
                                o->homePos.x = p204->x;
                                q->y = p204->y;
                                q->z = p204->z; }
                            }
                            o->alarm = c;
                        }
                    }
                }
            }
        }
    sw0:
        switch (k) {
        case 2:
            if (NetArea_IsLocalOwner() == 0 && g->isSlotActive(g->myAid)) {
                if (l.netKind != o->kind && v18 > 0) {
                    ((InsectManager *)(a))->freeInsect(o, 1);
                } else {
                    if (Insect_IsTreeStillThere(a, o)) Insect_LoadModel(a, o, 0);
                }
            } else {
                Insect_LoadModel(a, o, 0);
            }
            break;
        case 3:
            if ((g)->isSlotActive(g->myAid)) {
                if (NetArea_IsLocalOwner() == 0) {
                    if (Insect_IsNetKindMismatch(a, o, l.netKind, v18, v1c)) {
                        o->state = 10;
                        ((InsectManager *)(a))->freeInsect(o, 1);
                    }
                }
                s32 kind = o->kind;
                if (Insect_GetWeatherReaction(kind, Weather_GetFallingPrecip()) == 5) {
                    o->canSing = 0;
                } else {
                    o->canSing = 1;
                }
            }
            Insect_Update(a, o, l.index, 1);
            break;
        case 4:
            if ((g)->isSlotActive(g->myAid) == 0) {
                o->state = 10;
                ((InsectManager *)(a))->freeInsect(o, 1);
            } else if (NetArea_IsLocalOwner()) {
                s16 *cnt = &o->stateTimer;
                V3 *pv = &o->position;
                t1.x = pv->x;
                t1.y = pv->y;
                t1.z = pv->z;
                ((SndEnvChannel *)(&o->seEmitter))->callUpdateRelative((VecFx32 *)(void *)(&t1));
                if (o->alarm != 0xff) {
                    o->alarm = 0xff;
                    l.index |= 0x10;
                    V3 *q1 = &o->targetPos;
                    o->targetPos.x = 1;
                    q1->y = 1;
                    q1->z = 1;
                    V3 *q2 = &o->position;
                    o->position.x = 1;
                    q2->y = 1;
                    q2->z = 1;
                    (g)->beginRecord();
                    (g)->writeRecord((u8 *)(&l.index), 1);
                    (g)->endRecord(0x30, 7);
                }
                *cnt = *cnt + 1;
                if (*cnt > 0xc8) {
                    o->state = 10;
                    ((InsectManager *)(a))->freeInsect(o, 1);
                }
            } else {
                V3 *pw = &o->position;
                t2.x = pw->x;
                t2.y = pw->y;
                t2.z = pw->z;
                ((SndEnvChannel *)(&o->seEmitter))->callUpdateRelative((VecFx32 *)(void *)(&t2));
                if (o->alarm == 0xff) o->state = 10;
                if (o->state == 10) ((InsectManager *)(a))->freeInsect(o, 1);
            }
            break;
        }
    }
    o++;
    l.index++;
test0:
    if (l.index < 8) goto loop0;
}
}

namespace s03 {
extern "C" BOOL Insect_IsNetKindMismatch(InsectManager *a, Rec *o, s32 c, s32 d, s32 e) {
    s32 t = o->kind;
    if (d == 0) return FALSE;
    if (t < 0 || t != c) return TRUE;
    V3 v(d, 0, e);
    Vec_DistXZ(&o->position, &v);
    return FALSE;
}
}

namespace s03 {
extern "C" BOOL Insect_IsTreeStillThere(InsectManager *a, Rec *o) {
    if (o->kind < 0) return FALSE;
    switch (o->kind) {
    case 0x9: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x1f: case 0x21: case 0x22: case 0x23: case 0x24: case 0x26: case 0x27: case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x34:
    {
        s32 x = 0, y = 0;
        FieldPos_ToUnit(&x, &y, &o->position);
        BlockMap *grid = TownBlockMap_Get();
        if (grid == 0) goto yes;
        s32 px = *(volatile s32 *)&x, py = *(volatile s32 *)&y;
        s32 hx = px >> 4;
        s32 hy = py >> 4;
        u16 *p = BlockMap_GetItemPtr(grid, hx, hy, px - (hx << 4), py - (hy << 4), 0);
        if (p == 0) return FALSE;
        if (Unk_ov003_022277c0_Chk(p)) goto yes;
        return FALSE;
    }
    default:
        break;
    }
yes:
    return TRUE;
}
}

namespace s03 {
extern "C" void SpecialInsect_UpdateAll(InsectManager *a) {
    Rec *o = sSpecialInsects;
    u8 i = 0;
    do {
        switch (o->lifeState) {
        case 2:
            Insect_LoadModel(a, o, 1);
            break;
        case 3:
            if (o->position.x > 0x1000) Insect_Update(a, o, i, 2);
            break;
        case 4:
            o->state = 10;
            ((InsectManager *)(a))->freeInsect(o, 2);
            break;
        }
        o++;
        i++;
    } while (i < 2);
}
}

namespace s03 {
extern "C" void HeldInsect_UpdateAll(InsectManager *a) {
    CommManager *g = gCommManager;
    u32 cur = g->myAid;
    if (cur == 4) cur = 0;
    Rec *o = sHeldInsects;
    u8 i = 0;
    s32 neg = -1;
    s32 zero = 0;
    do {
        s32 r = PlayerActor_GetAction(i);
        if (cur != i && o->state != 0xb && r != 0x57 && r != 0x58 && r != 0x76 && r != 6) {
            if (o->kind == 0x39) {
                Effect_End(o->effectHandle);
                o->effectHandle = neg;
            }
            ((InsectManager *)(a))->freeInsect(o, 3);
        } else {
            switch (o->lifeState) {
            case 0:
                break;
            case 1:
                ((InsectManager *)(a))->allocHeldInsect(o);
                break;
            case 2:
                Insect_LoadModel(a, o, 2);
                Collision_Move(&o->collisionState, &o->position, &o->position, o->rotY, sInsectModelParams[o->kind].collisionRadius, NULL, 10);
                break;
            case 3:
                Insect_Update(a, o, i, 3);
                break;
            case 4:
                o->state = 10;
                ((InsectManager *)(a))->freeInsect(o, 3);
                break;
            }
        }
        o++;
        i++;
    } while (i < 4);
}
}

namespace s03 {
extern "C" BOOL Insect_UsesCollisionMove(InsectManager *a, Rec *o) {
    s32 t;
    u32 st;
    st = o->state;
    t = o->kind;
    if (st == 9 || st == 0xb) goto yes;
    if (t != 0x3a && t != 0x3b) {
        CommManager *g = gCommManager;
        if ((g)->isSlotActive(g->myAid) == 0) goto cont;
        if (NetArea_IsLocalOwner() != 0) goto cont;
    }
    return FALSE;
cont:
    if (st == 7) goto yes;
    switch (t) {
    case 0x9: case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x1f: case 0x21: case 0x22: case 0x24: case 0x26: case 0x27: case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f: case 0x32: case 0x34: case 0x35:
        return FALSE;
    case 0x33:
        if (o->targetHeight == o->baseHeight) goto yes;
        return FALSE;
    case 0x31:
        if (st != 6) goto yes;
        return FALSE;
    default:
        break;
    }
yes:
    return TRUE;
}
}

namespace s03 {
extern "C" void HeldInsect_Release(s32 idx, s32 v) {
    Rec *o = &sHeldInsects[idx];
    o->state = 0xb;
    o->rotX = 0;
    o->rotZ = 0;
    Insect_SetScale(o, 100);
    o->rotY = v;
    s32 st = o->kind;
    if (st >= 0 && st < 0x3c) {
        sInsectBehaviors[st].init(o);
        switch (o->kind) {
        case 0xc:
        case 0xd:
        case 0x1b:
        case 0x1c:
        case 0x1d:
            Insect_TurnToTarget(o, 1);
            break;
        case 0x39:
            if (o->effectHandle != -1) {
                Effect_End(o->effectHandle);
                o->effectHandle = -1;
            }
            break;
        }
    } else {
        HeldInsect_Remove(idx, 0);
        o->lifeState = 4;
    }
}
}

namespace s03 {
extern "C" u32 HeldInsect_GetStage(s32 idx) {
    Rec *o = &sHeldInsects[idx];
    if (o->kind < 0) {
        o->state = 10;
        o->lifeState = 0;
    }
    return o->lifeState;
}
}

namespace s03 {
extern "C" s32 InsectPool_Draw(InsectManager *a, Rec *o, s32 n) {
    s32 i = 0;
    goto test0;
loop0:
    if (o->lifeState == 3 && o->inView != 0) {
        if (n == 8) {
            if (Insect_IsTreeKindForCulling(a, *(u8 *)&o->kind) == 0 || Camera_IsBlockingFocusView(&o->position, 0x2000, 0x2000) == 0) {
                Insect_Draw(a, o);
            }
        } else {
            Insect_Draw(a, o);
        }
    }
    o++;
    i++;
test0:
    if (i < n) goto loop0;
    return TRUE;
}
}

namespace s02 {
extern "C" BOOL Insect_IsTreeKindForCulling(InsectManager *a, s32 t) {
    switch (t) {
    case 9:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 31:
    case 33:
    case 34:
    case 35:
    case 36:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 52:
    case 53:
        return TRUE;
    }
    return FALSE;
}
}

namespace s02 {
extern "C" V3 *HeldInsect_GetPos(s32 idx) {
    Obj *o = &sHeldInsects[idx];
    return &o->position;
}
}

namespace s02 {
extern "C" void HeldInsect_Start(s32 t, s32 idx) {
    Obj *o = &sHeldInsects[idx];
    Actor *e = PlayerActor_GetActor(idx);
    if (e != 0) {
        VecFx32 *pv = &e->position;
        V3 *d = &o->position;
        d->x = e->position.x;
        d->y = pv->y;
        d->z = pv->z;
        d->y += 0x1b34;
        s16 ang = e->rotY;
        o->rotY = ang;
        s32 a = ((u16)ang >> 4) * 2;
        o->position.x += func_01ffcb0c(0xfae, data_02135f44[a * 1]);
        d->z += func_01ffcb0c(0xfae, data_02135f44[a + 1]);
    }
    o->lifeState = 1;
    o->state = 0x10;
    switch (t) {
    case 0x25:
        o->kind = 0x39;
        break;
    case 0x3a:
        o->kind = 0xb;
        break;
    case 0x3b:
        o->kind = 0x18;
        break;
    default:
        o->kind = t;
        break;
    }
}
}

namespace s02 {
extern "C" void Insect_OnNetRemove(s32 id) {
    Obj *o;
    s32 idx = (u8)(id & 0xf);
    if ((id >> 4) & 1) o = &sFieldInsects[idx];
    else if ((id >> 5) & 1) o = &sSpecialInsects[idx];
    o->stateTimer = 0;
    u32 st = o->state;
    if (Insect_CanHopAway(o->kind) && o->lifeState != 4 && st != 0x10 && st != 10) {
        if (st != 0x11 && o->auxTimer > 6) {
            o->auxTimer = 6;
            o->state = 0x11;
        }
    } else {
        o->lifeState = 4;
    }
}
}

namespace s02 {
extern "C" BOOL Insect_CanHopAway(s32 t) {
    switch (t) {
    case 0xc:
    case 0xd:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x31:
        return TRUE;
    }
    return FALSE;
}
}

namespace s02 {
extern "C" void Insect_OnClaimGranted(s32 id) {
    Obj *o;
    s32 idx = (u8)(id & 0xf);
    if ((id >> 4) & 1) o = &sFieldInsects[idx];
    else if ((id >> 5) & 1) o = &sSpecialInsects[idx];
    if (o->lifeState == 3) {
        NNS_G3dMdlSetMdlAlpha(o->pooledModel.getModel(), 0, 0);
    }
    o->state = 0x10;
}
}

namespace s02 {
extern "C" void HeldInsect_Remove(u8 id, s32 flag) {
    Obj *o = &sHeldInsects[id];
    CommManager *g = gCommManager;
    if (((CommManager *)(g))->isSlotActive(g->myAid) && flag && ((CommManager *)(g))->isMyAid(id)) {
        CommManager *g2 = gCommManager;
        ((CommManager *)(g2))->beginRecord();
        ((CommManager *)(g2))->writeRecord((u8 *)(&id), 1);
        ((CommManager *)(g2))->endRecord(0x30, 4);
    }
    if (o->effectHandle != -1) {
        Effect_End(o->effectHandle);
        o->effectHandle = -1;
    }
    o->state = 10;
}
}

namespace s02 {
extern "C" s32 Insect_FinishCatch(u8 id) {
    Obj *o;
    s32 idx = (u8)(id & 0xf);
    if ((id >> 4) & 1) o = &sFieldInsects[idx];
    else if ((id >> 5) & 1) o = &sSpecialInsects[idx];
    o->stateTimer = 0;
    o->lifeState = 4;
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        CommManager *g = gCommManager;
        ((CommManager *)(g))->beginRecord();
        ((CommManager *)(g))->writeRecord((u8 *)(&id), 1);
        ((CommManager *)(g))->endRecord(0x30, 4);
    }
    s32 c = o->kind;
    switch (c) {
    case 0x3a:
        o->state = 8;
        o->lifeState = 3;
        return 0xb;
    case 0x3b:
        o->state = 8;
        o->lifeState = 3;
        return 0x18;
    }
    return c;
}
}

namespace s02 {
extern "C" s32 Insect_GetCatchResult(s32 id) {
    Obj *o = 0;
    s32 r = 0;
    s32 idx = (u8)(id & 0xf);
    if ((id >> 4) & 1) o = &sFieldInsects[idx];
    else if ((id >> 5) & 1) o = &sSpecialInsects[idx];
    else r = 1;
    if (o == 0) r = 1;
    if (r != 1) {
        if (gCommManager->isSlotActive(gCommManager->myAid)) {
            if (!NetArea_IsLocalOwner()) r = sInsectCatchResult;
        }
    }
    if (r == 1) {
        u8 b;
        Insect_CancelCatch(id);
        b = id;
        if (gCommManager->isSlotActive(gCommManager->myAid)) {
            if (!NetArea_IsLocalOwner()) {
                CommManager *g = gCommManager;
                ((CommManager *)(g))->beginRecord();
                ((CommManager *)(g))->writeRecord((u8 *)(&b), 1);
                ((CommManager *)(g))->endRecord(0x2f, 4);
            }
        }
    }
    return (u8)r;
}
}

namespace s02 {
extern "C" void Insect_CancelCatch(s32 id) {
    Obj *o;
    s32 idx = (u8)(id & 0xf);
    if ((id >> 4) & 1) o = &sFieldInsects[idx];
    else if ((id >> 5) & 1) o = &sSpecialInsects[idx];
    if (o->state == 0x10 && o->kind >= 0) {
        o->state = 0x13;
        NNS_G3dMdlSetMdlAlpha(o->pooledModel.getModel(), 0, 0x1f);
    }
}
}

namespace s02 {
extern "C" s32 Insect_TryCatch(u8 id) {
    Obj *o;
    s32 idx = (u8)(id & 0xf);
    if ((id >> 4) & 1) o = &sFieldInsects[idx];
    else if ((id >> 5) & 1) o = &sSpecialInsects[idx];
    else return 0;
    u32 t6 = o->state;
    u32 c4 = (u8)o->kind;
    if (c4 == -1 || o->lifeState != 3 || t6 == 0xb || t6 == 9 || t6 == 0x10) return 0;
    if (c4 == 0x31 || c4 == 0x1e || c4 == 0x35) {
        if (NNS_G3dMdlGetMdlAlpha(o->pooledModel.getModel(), 0) < 0x1f) return 0;
    }
    if (c4 == 0x35 && t6 == 0x13) return 0;
    s32 c = o->kind;
    if (c != 0x3a && c != 0x3b) {
        NNS_G3dMdlSetMdlAlpha(o->pooledModel.getModel(), 0, 0);
        o->state = 0x10;
    }
    if (gCommManager->isSlotActive(gCommManager->myAid)) {
        if (!NetArea_IsLocalOwner()) {
            sInsectCatchResult = 2;
            CommManager *g = gCommManager;
            ((CommManager *)(g))->beginRecord();
            ((CommManager *)(g))->writeRecord((u8 *)(&id), 1);
            ((CommManager *)(g))->endRecord(0x28, 6);
        }
    }
    return 1;
}
}

namespace s02 {
extern "C" void Insect_SetScale(Obj *o, s32 v) {
    if (v == 100) {
        o->scale.x = 0x1000;
        o->scale.y = 0x1000;
        o->scale.z = 0x1000;
    } else {
        s32 *p = &o->scale.x;
        *p = FX_Div(v << 12, 0x64000);
        o->scale.y = *p;
        o->scale.z = *p;
    }
}
}

namespace s02 {
extern "C" void Insect_Draw(InsectManager *a, Obj *o) {
    s32 *p = &o->scale.x;
    if (*p > 0) {
        void *t = o->pooledModel.getModel();
        s32 r = NNS_G3dMdlGetMdlAlpha(t, 0);
        u32 c;
        r = (31 - r) << 1;
        if (r > 31) c = 0;
        else c = 31 - r;
        ((AnimModel *)(&o->model))->drawAnimated(p);
        if (Insect_HasShadow(a, o)) {
            CharaShadow_DrawFaded(&o->position, sInsectModelParams[o->kind].collisionRadius, 0x9000, (u8)c);
        }
    }
}
}

namespace s02 {
extern "C" BOOL Insect_HasShadow(InsectManager *a, Obj *o) {
    s32 idx = o->kind;
    if (sInsectModelParams[idx].collisionRadius <= 1) return FALSE;
    switch (idx) {
    case 0x1e:
    case 0x31:
        if (o->state == 0x13) return FALSE;
        return TRUE;
    case 0x18:
    case 0x30:
    case 0x32:
    case 0x33:
    case 0x3a:
    case 0x3b:
        return FALSE;
    }
    return TRUE;
}
}

namespace s02 {
extern "C" void Insect_SetModelMatrix(InsectManager *a, Obj *o, s32 flag) {
    V3 v;
    s32 r6 = WorldCurve_ToCurved(&v, &o->position);
    if (flag) {
        data_021f47e0 = o->handMtx;
        Mtx43_RotateX(&data_021f47e0, o->rotX);
    } else {
        Mtx43_SetTranslate(&data_021f47e0, v.x, v.y, v.z);
        Mtx43_RotateX(&data_021f47e0, (s16)(r6 + o->rotX));
    }
    if (o->rotY != 0) Mtx43_RotateY(&data_021f47e0, o->rotY);
    if (o->rotZ != 0) Mtx43_RotateZ(&data_021f47e0, o->rotZ);
    o->model.mtx = data_021f47e0;
    if (flag && o->kind == 0x39) {
        Blk m = data_021f47e0;
        V3 pos;
        pos.x = m.m[9];
        pos.y = m.m[10];
        pos.z = m.m[11];
        s32 *h = &o->effectHandle;
        m.m[11] = 0;
        m.m[10] = 0;
        m.m[9] = 0;
        Blk m2 = m;
        V3 vin;
        V3 vout;
        s16 arr[2];
        vin.y = 0;
        vin.x = 0;
        vin.z = func_01ffcb0c(o->scale.x, -0x333);
        MTX_MultVec43(&vin, &m2, &vout);
        pos.x += vout.x;
        pos.y += vout.y;
        pos.z += vout.z;
        WorldCurve_FromCurved(&pos, &pos);
        if (o->behaviorWork == 0) {
            arr[0] = o->scale.x;
            *h = Effect_Create(0x3a, &pos, 0, &arr[0]);
            o->behaviorWork = 1;
        } else {
            arr[1] = o->scale.x;
            s32 t = *h;
            if (t != -1) Effect_SetPosition(t, &pos, 0, &arr[1]);
        }
    }
}
}

#define sFieldInsects (*(Obj (*)[1])&::sFieldInsects)
#define sSpecialInsects (*(Obj (*)[1])&::sSpecialInsects)
#define sHeldInsects (*(Obj (*)[1])&::sHeldInsects)
BOOL InsectManager::onDraw() { using namespace s02;
    s32 r = InsectPool_Draw(this, sFieldInsects, 8);
    r &= InsectPool_Draw(this, sSpecialInsects, 2);
    r &= InsectPool_Draw(this, sHeldInsects, 4);
    return r;
}
#undef sFieldInsects

#undef sSpecialInsects

#undef sHeldInsects


#define sFieldInsects (*(Rec (*)[1])&::sFieldInsects)
#define sSpecialInsects (*(Rec (*)[1])&::sSpecialInsects)
#define sHeldInsects (*(Rec (*)[1])&::sHeldInsects)
BOOL InsectManager::onDelete() { using namespace s01;
    InsectManager *obj = this;
    Rec *pa = sFieldInsects;
    Rec *pb = sSpecialInsects;
    Rec *pc = sHeldInsects;
    s32 i, j, k;
    for (i = 0; i < 8; i++) {
        ((InsectManager *)(obj))->freeInsect(pa++, 1);
    }
    j = 0;
    for (i = 0; i < 2; i++) {
        Rec *q = pb;
        pb++;
        ((InsectManager *)(obj))->freeInsect(q, 2);
        Mem_Free(obj->specialAnimFiles[i]);
        obj->specialAnimFiles[i] = 0;
    }
    for (k = 0; k < 4; k++) {
        Rec *q = pc;
        pc++;
        ((InsectManager *)(obj))->freeInsect(q, 3);
    }
    ((ModelSlotPool *)(&obj->fieldInsectPool))->destroy();
    ((ModelSlotPool *)(&obj->specialInsectPool))->destroy();
    ((ModelSlotPool *)(&obj->heldInsectPool))->destroy();
    Town_ClearBeesReleased();
    return TRUE;
}
#undef sFieldInsects

#undef sSpecialInsects

#undef sHeldInsects


namespace s01 {
extern "C" void InsectPool_UpdateInViewOfPlayer(InsectManager *obj, s32 flag, s32 idx, s32 x, s32 z) {
    Rec *e;
    s32 n;
    if (flag == 1) {
        e = sFieldInsects;
        n = 8;
    } else {
        e = sSpecialInsects;
        n = 2;
    }
    s32 x0 = x - 0x10000;
    s32 z0 = z - 0x1c000;
    s32 x1 = x + 0x10000;
    s32 z1 = z + 0xc000;
    s32 h = Weather_GetFallingPrecip();
    u8 i = 0;
    s32 m = 1;
    m = m << idx;
    s32 nm = ~(m & 0xf);
    for (; i < n; e++, i++) {
        if (e->inUse != 0 && e->kind >= 0) {
            s32 r;
            VecFx32Ctor *p = &e->position;
            u32 bits = e->inViewMask;
            r = Insect_GetWeatherReaction(e->kind, h);
            if (NetArea_IsLocalOwner() == 0 && r == 4) {
                r = 3;
            }
            u32 t = e->inView;
            if (t == 0 && r == 4) {
                obj->freeInsect(e, flag);
            } else if (x0 < p->x && x1 > p->x && z0 < p->z && z1 > p->z) {
                if (t == 0) {
                    e->inView = 1;
                    e->inViewMask = bits | m;
                }
            } else if (((s32)bits >> idx) & 1) {
                e->inViewMask = bits & nm;
            } else if (t != 0 && bits == 0 && flag == 1) {
                e->inView = 0;
            }
        }
    }
}
}

namespace s01 {
extern "C" void InsectPool_UpdateInView(InsectManager *obj, s32 flag) {
    void *c = gCamera;
    Rec *e;
    s32 n;
    if (flag == 1) {
        e = sFieldInsects;
        n = 8;
    } else {
        e = sSpecialInsects;
        n = 2;
    }
    if (c) {
        VecFx32CtorDtor cp;
        VecFx32Ctor *g = &gCameraLookAt;
        cp.x = g->x;
        cp.y = g->y;
        cp.z = g->z;
        s32 x0 = cp.x - 0x10000;
        s32 z0 = cp.z - 0x1c000;
        s32 x1 = cp.x + 0x10000;
        s32 z1 = cp.z + 0xc000;
        s32 h = Weather_GetFallingPrecip();
        u8 i;
        for (i = 0; i < n; e++, i++) {
            if (e->inUse != 0 && e->kind >= 0) {
                VecFx32Ctor *p = &e->position;
                s32 r = Insect_GetWeatherReaction(e->kind, h);
                if (e->inView == 0 && r == 4) {
                    obj->freeInsect(e, flag);
                } else {
                    if (r == 5) {
                        e->canSing = 0;
                    } else {
                        e->canSing = 1;
                    }
                    if (x0 < p->x && x1 > p->x && z0 < p->z && z1 > p->z) {
                        e->inView = 1;
                    } else {
                        e->inView = 0;
                    }
                }
            }
        }
    }
}
}

namespace s01 {
extern "C" void Insect_EnableTrashFlies(void) {
    sTrashFlySpawnEnabled = 1;
}
}

namespace s01 {
extern "C" BOOL Insect_Spawn(void *obj, s32 kind, u8 sub, s32 flag) {
    Rec *e = sFieldInsects;
    s32 found = -1;
    Buf buf;
    if (kind != 8) {
        InsectSpawn_CopyMask(&buf, sub);
    } else {
        InsectSpawn_BuildLightMask(buf.rows);
    }
    if (flag == 1) {
        u8 i;
        for (i = 0; i < 8; e++, i++) {
            if (e->inUse != 0) {
                if (kind != 0x33) {
                    VecFx32Ctor *v = &e->position;
                    if (kind == 0x23 && e->kind == 0x23) {
                        return FALSE;
                    }
                    if (kind != 8) {
                        SpawnMask_MarkRect(buf.rows[0][0], v->x, v->z, 1, 1, 1);
                    }
                }
            } else if (found < 0) {
                found = (s8)i;
            }
        }
    }
    if (found < 0 && flag != 2) {
        goto fail;
    }
    Actor *q;
    q = PlayerActor_GetActor(4);
    if (q != 0 && flag == 1 && kind != 0x33) {
        if ((gCommManager)->isSlotActive(gCommManager->myAid)) {
            s32 k;
            u8 b0;
            s32 px, pz;
            for (k = 0; k < 4; k++) {
                if (PlayerActor_GetSlotPosXZ(&b0, &px, &pz, -1, k) && b0 == 0) {
                    SpawnMask_MarkRect(buf.rows[0][0], px, pz, 5, 8, 5);
                }
            }
        } else {
            VecFx32 *pp = &q->position;
            SpawnMask_MarkRect(buf.rows[0][0], pp->x, pp->z, 5, 8, 5);
        }
    }
    Rec *cur;
    if (flag == 1) {
        cur = sFieldInsects + found;
    } else {
        cur = &sSpecialInsects[1];
    }
    if (kind == 0x23 && !gCommManager->isSlotActive(gCommManager->myAid)) {
        u8 j;
        for (j = 0; j < 2; j++) {
            Snowball *o = Snowball_GetLooseBall(j);
            if (o) {
                VecFx32 *pos = &o->position;
                VecFx32Ctor *dst = &cur->position;
                s32 s24 = Snowball_GetRadius(o);
                s32 s28 = Insect_RandomTurn(0x20, 1);
                if (q) {
                    if (Vec_DistXZ(&q->position, pos) > 0xc000) {
                        dst->x = pos->x;
                        dst->y = pos->y;
                        dst->z = pos->z;
                        s32 idx = ((u16)s28 >> 4) * 2;
                        dst->x += func_01ffcb0c(data_02135f44[idx], s24);
                        dst->z += func_01ffcb0c(data_02135f44[idx + 1], s24);
                        cur->rotY = Math_AngleXZ(pos, dst);
                        cur->inUse = 1;
                        cur->kind = kind;
                        cur->inView = 0;
                        cur->behaviorWork = j;
                        static_cast<InsectManager *>(obj)->allocFieldInsect(cur);
                        return TRUE;
                    }
                }
            }
        }
        goto fail;
    } else {
        if (!InsectSpawn_PickPos(cur, buf.rows[0][0], kind, sub)) {
            goto fail;
        }
        cur->inUse = 1;
        cur->kind = kind;
        cur->inView = 0;
        VecFx32Ctor *s = &cur->position;
        VecFx32Ctor *d = &cur->homePos;
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
        if (flag == 1) {
            static_cast<InsectManager *>(obj)->allocFieldInsect(cur);
        }
        return TRUE;
    }
fail:
    return FALSE;
}
}

namespace s01 {
extern "C" s32 Insect_TrySpawnRandom(InsectManager *a, s32 b, u8 c, u32 d) {
    Rec *e;
    s32 r;
    u8 i;
    r = 0;
    e = sFieldInsects;
    for (i = 0; i < 8; e++, i++) {
        if (e->inUse == 0) {
            if (c == 0x33) {
                r = Insect_Spawn(a, c, (u8)d, b);
            } else if (Insect_RollKind(&c)) {
                r = Insect_Spawn(a, c, Insect_GetHabitat(c), b);
            }
            if (r == 0 && c != 0x33) {
                e->inUse = 1;
                e->kind = -10;
            }
            return r;
        }
    }
    return 0;
}
}

namespace s01 {
extern "C" void Insect_SpawnBeeSwarm(VecFx32Ctor *v) {
    Insect *bees = &sSpecialInsects[0];
    bees->inView = 1;
    bees->position = *v;
    bees->state = 4;
}
}

namespace s01 {
extern "C" BOOL HeldInsect_SetHandMatrix(s32 idx, s16 *p, Mtx43 *q, s32 flag) {
    Rec *e = sHeldInsects + idx;
    VecFx32Ctor *v = &e->position;
    BOOL ret = TRUE;
    e->handMtx = *q;
    s32 *b = (s32 *)&e->handMtx;
    Insect_SetScale(e, *p);
    v->x = b[9];
    v->y = b[10];
    v->z = b[11];
    WorldCurve_FromCurved(v, v);
    if (e->state != 0xb) {
        s32 t = e->kind;
        if (t == 0x1a) {
            e->rotX = 0;
            e->rotY = func_01ffcb0c(0xb6, 0xc8000);
            e->rotZ = func_01ffcb0c(0xb6, 0x1e000);
        } else if (t == 0xc || t == 0xd || t == 0x1d) {
            e->rotX = func_01ffcb0c(0xb6, 0x91000);
            e->rotY = func_01ffcb0c(0xb6, 0xc8000);
            e->rotZ = func_01ffcb0c(0xb6, 0x96000);
        } else if (t == 0x35) {
            e->rotX = func_01ffcb0c(0xb6, 0x91000);
            e->rotY = func_01ffcb0c(0xb6, 0x64000);
            e->rotZ = 0;
        } else {
            e->rotX = func_01ffcb0c(0xb6, 0x35000);
            e->rotY = func_01ffcb0c(0xb6, 0xc8000);
            e->rotZ = func_01ffcb0c(0xb6, 0x54000);
            if (e->lifeState == 3) {
                AnimModel *s = &e->model;
                if (t == 0x14 && (((u32)s->curFrame << 4) >> 16) == 0) {
                    s->AnimFrameCtrl::setup(4, 1, 0x1000, 0);
                    s->curFrame = 0x4000;
                } else if ((u16)(s16)(t - 10) <= 1) {
                    if ((((u32)s->curFrame << 4) >> 16) == 0) {
                        s->setFrame(1);
                    } else {
                        s->setFrame(0);
                    }
                } else if (t == 0x37) {
                    s32 w = (s32)s->numFrames >> 12;
                    if ((u16)w == 0xe && (((u32)s->curFrame << 4) >> 16) == 0xd) {
                        s->curFrame = 0xa000;
                    } else if ((u16)w != 0xe) {
                        s->AnimFrameCtrl::setup(0xe, 0, 0x1000, 0xa);
                    }
                }
            }
        }
    }
    if (e->lifeState == 2 || e->lifeState == 0) {
        ret = FALSE;
    }
    if (flag != 0) {
        e->state = 0xa;
        if (e->kind == 0x39) {
            s32 t = e->effectHandle;
            s32 m1 = -1;
            if (t != m1) {
                Effect_End(t);
                e->effectHandle = -1;
            }
        }
    }
    return ret;
}
}

namespace s01 {
extern "C" BOOL Insect_NetClaim(s32 x) {
    u8 idx = x & 0xf;
    Rec *r;
    if ((x >> 4) & 1) {
        r = sFieldInsects + idx;
    } else if ((x >> 5) & 1) {
        r = sSpecialInsects + idx;
    } else {
        return TRUE;
    }
    u32 t = r->state;
    if (t != 0xa && t != 0xb && t != 9 && t != 0x10 && r->lifeState == 3) {
        r->state = 0x10;
        return FALSE;
    }
    return TRUE;
}
}

namespace s01 {
extern "C" BOOL Insect_IsBeeSwarmOut(void) {
    CommManager *p = gCommManager;
    if ((p)->isSlotActive(p->myAid) == 0) {
        Rec *e = sSpecialInsects;
        if (NNS_G3dMdlGetMdlAlpha(e->pooledModel.getModel(), 0) > 0x1e && e->lifeState == 3 && e->kind != 0x13) {
            return TRUE;
        }
    }
    return FALSE;
}
}

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" BOOL Insect_IsAtWateringPoint(VecFx32 *p)
{
    s32 c, d;
    s32 a, b;
    if (sWateringActive != 0) {
        FieldPos_ToUnit(&a, &b, p);
        FieldPos_ToUnit(&c, &d, &sWateringPos);
        if (c == a && d == b) {
            return TRUE;
        }
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" BOOL Insect_RollKind(u8 *out)
{
    DayMonth l;
    u8 v;
    Clock_GetDayMonth(&l);
    v = l.month - 1;
    if (v > 11) {
        v = 0;
    }
    if (Insect_RollFromSpawnTable(v, Insect_GetTimeSlot(), out)) {
        return TRUE;
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" s32 Insect_GetTimeSlot()
{
    MinuteHour l;
    u32 b;
    Clock_GetMinuteHour(&l);
    b = l.hour;
    if (b >= 4 && b <= 7) {
        return 1;
    }
    if (b >= 8 && b <= 15) {
        return 2;
    }
    if (b == 16) {
        return 3;
    }
    if ((u8)(b + 0xef) <= 1) {
        return 4;
    }
    if (b >= 19 && b <= 22) {
        return 5;
    }
    return 0;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" void Insect_TickFrame(Insect *self)
{
    u8 *p = &self->frameCounter;
    (*p)++;
    if (*p > 0x50) {
        *p = 0;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
Insect::Insect()
{ using namespace s00;
    pooledModel.reset();
    state = 0x13;
    frameCounter = 0;
    rotY = 0;
    rotZ = 0;
    rotX = 0;
    kind = -1;
    lifeState = 0;
    updateFn = 0;
    unk_24c = 1;
    stateTimer = 0;
    unk_24b = 1;
    isAlarmed = 0;
    inUse = 0;
    inView = 0;
    cooldownTimer = 0;
    effectHandle = -1;
}
#undef func_02133150

#define func_02133150 _s32_div_f
Insect::~Insect() { using namespace s00;}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" void Insect_SetAnimSpeed(Insect *self, u32 v)
{
    self->model.frameStep = v;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" BOOL Insect_PickSpecialSpawn(s8 *a, s8 *b, s32 c)
{
    s32 r = Weather_GetFallingPrecip();
    u8 buf[16];
    if (c != 0) {
        if (r == 0) {
            if (Town_GetRafflesiaPos(buf)) {
                *a = 0x33;
                *b = 8;
                return TRUE;
            }
            if (sTrashFlySpawnEnabled > 0) {
                if (Random_GlobalBelow(100) < 20) {
                    *a = 0x33;
                    *b = 7;
                    return TRUE;
                }
            }
        }
    } else {
        if (r != 1) {
            Insect *ants = &sSpecialInsects[1];
            if (sAntSpawnEnabled != 0) {
                if (ants->lifeState == 3 && ants->state == 0x13) {
                    *a = 0x3b;
                    *b = 7;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" BOOL Insect_IsAllowedOnline(s32 a)
{
    CommManager *p = gCommManager;
    if (!((CommManager *)(p))->isSlotActive(p->myAid)) {
        return TRUE;
    }
    switch (a) {
    case 8:
    case 10:
    case 25:
    case 35:
    case 48:
    case 50:
    case 51:
    case 53:
    case 54:
    case 55:
    case 58:
    case 59:
        return FALSE;
    }
    return TRUE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" BOOL Insect_RollFromSpawnTable(u32 a, u32 b, u8 *out)
{
    u8 r;
    InsectSpawnList *t;
    u32 cnt;
    s32 v;
    u8 i;
    InsectSpawnList *ent;
    r = Random_GlobalBelow(100);
    t = gInsectSpawnTables[a];
    if (t == 0) {
        return FALSE;
    }
    cnt = t[b].entryCount;
    v = Weather_GetFallingPrecip();
    i = 0;
    ent = &t[b];
    for (; i < cnt; i++) {
        InsectSpawnEntry *pp = ent->entries;
        u8 first = pp[i].kind;
        u8 second = pp[i].cumulativeChance;
        if (second > r) {
            if (first != 0x30 && Insect_IsAllowedOnline(first) && Insect_GetWeatherReaction((s8)first, v) != 4) {
                *out = first;
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" void FieldInsect_PurgeStale()
{
    Insect *e;
    s32 i;
    sFieldInsectPurgeTimer += TICK_STEP_ENDS() ? 1 : 0;
    if (sFieldInsectPurgeTimer > 0x78) {
        e = sFieldInsects;
        sFieldInsectPurgeTimer = 0;
        for (i = 0; i < 8; e++, i++) {
            if (e->kind == -10) {
                e->kind = -1;
                e->inUse = 0;
            } else if (e->inView == 0 && e->outOfViewTimer == 0 && e->lifeState == 3) {
                e->lifeState = 4;
                e->state = 10;
            }
        }
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" s32 Insect_GetWeatherReaction(s32 a, s32 b)
{
    switch (a) {
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        if ((u32)(b - 1) <= 1) {
            return 5;
        }
        break;
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
    case 10:
    case 12: case 13: case 14: case 15:
    case 21: case 22: case 23:
    case 25:
    case 27: case 28: case 29:
    case 32:
    case 37:
    case 50: case 51:
    case 54: case 55:
        if ((u32)(b - 1) <= 1) {
            return 4;
        }
        break;
    case 59:
        if (b == 1) {
            return 4;
        }
        break;
    case 26:
        if (b != 1) {
            return 4;
        }
        break;
    case 9: case 11: case 24: case 30: case 31: case 33: case 34: case 35: case 36:
    case 38: case 39: case 40: case 41: case 42: case 43: case 44: case 45: case 46:
    case 47: case 48: case 49: case 52: case 53: case 56: case 57: case 58:
    default:
        return 3;
    }
    return 3;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
InsectMatAnim::InsectMatAnim() { using namespace s00;}
#undef func_02133150

#define func_02133150 _s32_div_f
InsectMatAnim::~InsectMatAnim() { using namespace s00;}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" void InsectSpawn_CopyMask(void *p, s32 t)
{
    switch (t) {
    case 0:
    case 5:
    case 6:
        MI_CpuCopy8(sInsectSpawnMaskLand, p, 0x200);
        break;
    default:
        MI_CpuCopy8(sInsectSpawnMaskDry, p, 0x200);
        break;
    }
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" s32 InsectSpawn_PickPos(Insect *self, u16 *a, s32 code, u32 flag)
{
    u32 mask = 0;
    s32 x = 0;
    s32 y = 0;
    BOOL found;
    s32 rndD;
    s32 rnd33;
    u32 n;
    BlockMap *obj = TownBlockMap_Get();
    if (obj == 0) {
        return 0;
    }
    if (code == 0x3b) {
        s32 rnd;
        s32 k;
        rnd = Random_GlobalBelow(16 - data_ov003_02258f08);
        Actor *b;
        n = 0;
        k = n;
        mask = data_ov003_02258f10;
        for (; k < 16; n++, k++) {
            if ((((s32)mask >> k) & 1) == 0) {
                if (rnd-- == 0) {
                    data_ov003_02258f10 |= 1 << k;
                    break;
                }
            }
        }
        x = n >> 2;
        y = n & 3;
        data_ov003_02258f08++;
        if (InsectSpawn_FindUnitInBlock(a, code, &x, &y, obj, (u8)flag)) {
            b = PlayerActor_GetActor(4);
            data_ov003_02258f04 = 1;
            if (b) {
                VecFx32 v;
                v.x = x;
                v.y = 0;
                v.z = y;
                if (Vec_DistXZ(&b->position, &v) > 0x10000) {
                    self->position.x = x;
                    self->position.z = y;
                    data_ov003_02258f10 = 0;
                    data_ov003_02258f08 = 0;
                    data_ov003_02258f04 = 0;
                    return 1;
                }
            }
        }
        if (data_ov003_02258f08 >= 0x10) {
            data_ov003_02258f10 = 0;
            data_ov003_02258f08 = 0;
            if (data_ov003_02258f04 != 0) {
                data_ov003_02258f04 = 0;
            } else {
                sAntSpawnEnabled = 0;
            }
        }
    } else if (code == 0x33) {
        found = FALSE;
        s32 i;
        u32 zero = 0;
        for (i = 0; i < 16; i++) {
            rnd33 = Random_GlobalBelow(16 - i);
            s32 k;
            n = 0;
            for (k = n; k < 16; n++, k++) {
                if (((mask >> k) & 1) == 0) {
                    if (rnd33-- == 0) {
                        mask |= 1 << k;
                        break;
                    }
                }
            }
            x = n >> 2;
            y = n & 3;
            if (InsectSpawn_FindUnitInBlock(a, code, &x, &y, obj, (u8)flag)) {
                Actor *b = PlayerActor_GetActor(4);
                if (b) {
                    VecFx32 v;
                    v.x = x;
                    v.y = zero;
                    v.z = y;
                    if (Vec_DistXZ(&b->position, &v) > 0x10000) {
                        self->position.x = x;
                        self->position.z = y;
                        return 1;
                    }
                }
                found = TRUE;
            }
        }
        if (!found) {
            sTrashFlySpawnEnabled = 0;
        }
    } else {
        s32 i;
        for (i = 0; i < 16; i++) {
            rndD = Random_GlobalBelow(16 - i);
            s32 k;
            n = 0;
            for (k = n; k < 16; n++, k++) {
                if (((mask >> k) & 1) == 0) {
                    if (rndD-- == 0) {
                        mask |= 1 << k;
                        break;
                    }
                }
            }
            x = n >> 2;
            y = n & 3;
            if (InsectSpawn_FindUnitInBlock(a, code, &x, &y, obj, (u8)flag)) {
                self->position.x = x;
                self->position.z = y;
                return 1;
            }
        }
    }
    return 0;
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" void InsectSpawn_BuildLightMask(u16 (*arr)[4][16])
{
    s32 i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 16; j++) {
            for (k = 0; k < 4; k++) {
                arr[i][k][j] = 0xffff;
            }
        }
    }
    InsectSpawn_ClearLitUnits(arr);
}
}
#undef func_02133150

#define func_02133150 _s32_div_f
namespace s00 {
extern "C" void InsectSpawn_ClearLitUnits(u16 (*arr)[4][16])
{
    u32 i;
    for (i = 0; i < 0x22; i++) {
        u16 id;
        void *p;
        u32 n;
        BuildingActor *o;
        id = Item_MakeBuilding(i);
        p = StrBSize_Get(&id);
        if (p != 0) {
            n = ((StrBSizeData *)(p))->getLightUnitCount();
            if (n != 0) {
                o = BuildingList_FindByItem(id);
                if (o != 0) {
                    u32 j;
                    for (j = 0; j < n; j++) {
                        s32 xy[2];
                        if (((StrBSizeData *)(p))->getLightUnit(&xy[0], &xy[1], j)) {
                            if (o->callIsLit() == 1) {
                                s32 px = xy[0] + o->getGridX();
                                s32 py = xy[1] + o->getGridZ();
                                s32 bx = (px - 16) / 16;
                                s32 by = (py - 16) / 16;
                                u16 *c = (u16 *)((u8 *)arr + bx * 32 + by * 128);
                                c[py % 16] &= 0xffff - (1 << (px % 16));
                            }
                        }
                    }
                }
            }
        }
    }
}
}
#undef func_02133150


extern "C" void StaticInit_unk_ov003_02225800(void) {
    HOST_STATIC_CONSTRUCT(sFieldInsects);
    HOST_STATIC_CONSTRUCT(sSpecialInsects);
    HOST_STATIC_CONSTRUCT(sHeldInsects);
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_02225800) {
    HOST_OVERLAY_VAR(sFieldInsects),
    HOST_OVERLAY_VAR(data_ov003_02258f10),
    HOST_OVERLAY_VAR(sWateringActive),
    HOST_OVERLAY_VAR(sInsectSpawnMaskDry),
    HOST_OVERLAY_VAR(sSpecialInsects),
    HOST_OVERLAY_VAR(sTrashFlySpawnEnabled),
    HOST_OVERLAY_VAR(sAntSpawnEnabled),
    HOST_OVERLAY_VAR(sHeldInsects),
    HOST_OVERLAY_VAR(data_ov003_02258f08),
    HOST_OVERLAY_VAR(data_ov003_02258f04),
    HOST_OVERLAY_VAR(sInsectSpawnTimer),
    HOST_OVERLAY_VAR(sInsectSpawnMaskLand),
    HOST_OVERLAY_VAR(sInsectModelParams),
    HOST_OVERLAY_VAR(sFieldInsectPurgeTimer),
    HOST_OVERLAY_VAR(sInsectCatchResult),
    HOST_OVERLAY_VAR(sInsectManagerProfile),
    HOST_OVERLAY_VAR(sInsectBehaviors),
    HOST_OVERLAY_VAR(sWateringPos),
    HOST_OVERLAY_VARS_END
};

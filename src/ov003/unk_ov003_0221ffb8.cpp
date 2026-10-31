#include "ds_div.h"
#include "host_overlay_vars.h"
#include "gfx/Model.h"
#include "proto/main/unk_0202fa70.h"
#include "snd/SndSeEmitter.h"
#include "uptr.h"
#include "types.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "field/BottleThrow.h"
#include "gfx/ModelSlotPool.h"
#include "gfx/ModelAnim.h"
#include "game/GroundInfo.h"
#include "actor/Character.h"
#include "gfx/AnimModel.h"
#include "gfx/PooledModel.h"
#include "sys/ProcProfile.h"
#include "town/TownBlockCell.h"
#include "gfx/NNSG3dResMatData.h"
#include "town/Unk_0204e858_Grid.h"
#include "player/FishBobber.h"
#include "field/FishShadow.h"
#include "game/CollisionState.h"
#include "gfx/AnimFrameCtrl.h"
#include "gfx/CachedModel.h"
#include "gfx/TwoLayerAnimModel.h"
#include "net/CommManager.h"
#include "snd/SndEnvChannel.h"
#include "game/FxVec3.h"
#include "item/FishInfo.h"
#include "player/FishBobber.h"
#include "actor/Actor.h"
#include "town/MapBlock.h"
#include "town/BlockMap.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e92f4.h"
#include "proto/main/unk_02002b1c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0203ecec.h"
#include "proto/main/unk_0204f134.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205ef08.h"
#include "proto/main/unk_0205f284.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_020943dc.h"
#include "proto/main/unk_02094810.h"
#include "proto/ov003/unk_ov003_02204ce8.h"
#include "proto/ov003/unk_ov003_0221ffb8.h"
#include "proto/main/unk_0204cc1c.h"




static inline s32 FishAngleXZ(VecFx32 *a, VecFx32 *b) {
    return Math_AngleXZ(a, b);
}

static inline BOOL Unk_ov003_022203f8_Chk(s32 v) {
    if ((u32)(v - 0x34) <= 2) {
        return TRUE;
    }
    return FALSE;
}

typedef VecFx32Ctor V3_f3;



class FieldFishManager;
typedef FieldFishManager O_f3;

typedef FishShadow E_f3;



struct FishCatch {
    FishCatch();
    ~FishCatch();
    /* 0x00 */ SndSeEmitter seEmitter;
    /* 0x40 */ s32 state;
    /* 0x44 */ s32 displayHandle;
    /* 0x48 */ s32 mode;
    /* 0x4c */ s32 gravity;
    /* 0x50 */ s32 ySpeed;
    /* 0x54 */ VecFx32 position;
    /* 0x60 */ VecFx32 arcPointA;
    /* 0x6c */ VecFx32 arcPointB;
    /* 0x78 */ s8 shadowIndex;
    /* 0x79 */ u8 pad_79[3];
    /* 0x7c */ s32 moveFrame;
    /* 0x80 */ u8 isLanded;
    /* 0x81 */ u8 pad_81[3];
    /* 0x84 */ VecFx32 scale;
    /* 0x90 */ s32 fishId;
    /* 0x94 */ u8 swimAwayPending;
    /* 0x95 */ u8 pad_95;
    /* 0x96 */ s16 rotX;
    /* 0x98 */ s16 rotY;
    /* 0x9a */ s16 rotZ;
    /* 0x9c */ s32 effectHandle;
    /* 0xa0 */ u8 storedSent;
    /* 0xa1 */ u8 pad_a1[3];
};



class FieldFishManager : public GameProc {
public:
    FieldFishManager();
    virtual ~FieldFishManager();
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();

    /* 0x50 */ ModelSlotPool shadowModelPool;
    /* 0x68 */ ModelSlotPool finModelPool;
    /* 0x80 */ void *shadowAnimFile;
    /* 0x84 */ u8 spawnAttempted;
    /* 0x85 */ u8 pad_85[3];
};

typedef void (FieldFishManager::*Unk_ov003_0222144c_Fn_f4)(FishShadow *, s32 idx);

struct FishShadowStateEntry {
    Unk_ov003_0222144c_Fn_f4 enter;
    Unk_ov003_0222144c_Fn_f4 exec;
};



typedef VecFx32 V3_f5;

typedef Mtx43 T48_f5;

typedef Character Ent_f5;

typedef FishCatch Self_f5;

#define CP(d, s) do { (d).x = (s).x; (d).y = (s).y; (d).z = (s).z; } while (0)

static inline BOOL Unk_ov003_02222490_Bit(u32 f, u32 m) {
    return (f & m) ? TRUE : FALSE;
}

typedef VecFx32 V3_f6;

typedef FishCatch Ent_f6;



typedef void (FishCatch::*Fn_f6)(u32 playerIdx);

struct FishCatchStateEntry {
    Fn_f6 f;
};

typedef FishShadow Obj_f6;


static inline BOOL R74(volatile u16 *p)
{
    u32 a = *p;
    u32 b = *p;
    BOOL r = FALSE;
    if (b >= 0x1374 && a <= 0x1374) {
        r = TRUE;
    }
    return r;
}

#define COPY() \
    do { \
        self->position.x = self->prevPosition.x; \
        self->position.y = self->prevPosition.y; \
        self->position.z = self->prevPosition.z; \
    } while (0)

typedef VecFx32 V3_f7;


typedef FishCatch Rec_f7;

typedef FishShadow Obj_f7;



typedef VecFx32 V3_f8;


typedef s32 (FishShadow::*Fn_f8)();

struct FishBiteStateEntry {
    Fn_f8 f;
};


typedef FishShadow Obj_f8;




typedef VecFx32Copy V3_f9;

typedef VecFx32CopyDtor V3d_f9;

typedef void (FishShadow::*Fn_f9)();

struct FishMoveStateEntry {
    Fn_f9 f;
};

struct FishAiStateEntry {
    Fn_f9 appear;
    Fn_f9 think;
};

typedef FishShadow Obj_f9;


typedef BottleThrow E_f9;

class BottleThrowStateOwner;

typedef void (BottleThrowStateOwner::*StFn_f9)(E_f9 *);

struct BottleThrowStateEntry {
    StFn_f9 f;
};




typedef VecFx32 V3_f10;


static inline BOOL Unk_ov003_02224bc4_Bit(u32 f, u32 m)
{
    if ((f & m) != 0) return TRUE;
    return FALSE;
}




class FishFinMatAnim : public ModelAnim {
public:
    virtual ~FishFinMatAnim() {}
};

class BottleThrowStateOwner {
public:
    BottleThrowStateOwner();
    ~BottleThrowStateOwner();
};




class FishFinModel {
public:
    FishFinModel();
    ~FishFinModel();
    /* 0x000 */ u32 attachState;
    /* 0x004 */ ModelSlotHandle modelSlot;
    /* 0x006 */ u8 pad_06[2];
    /* 0x008 */ PooledModel pooledModel;
    /* 0x048 */ VecFx32Ctor position;
    /* 0x054 */ s16 rotY;
    /* 0x056 */ u8 pad_56[2];
    /* 0x058 */ AnimModel model;
    /* 0x110 */ u8 pad_110[0xc];
    /* 0x11c */ FishFinMatAnim matAnim;
};

class Camera;
class MapBlock;
class BlockMap;
extern Camera *gCamera;
extern FxVec3 gCameraLookAt;
extern BlockMap *gSceneBlockMap;
extern CommManager *const gCommManager;
extern Mtx43 data_021f47e0;
extern const s16 data_02135f44[4096 * 2];
extern const s32 data_020c7c1c;
extern "C" {
fx32 func_01ffcb0c(fx32 v1, fx32 v2);
s32 _s32_div_f(s32 a, s32 b);
u8 *func_021065dc(u8 *p);
u8 *func_021065f8(u8 *p, u32 i);
u8 *func_02106654(u8 *p);
u8 *func_02106670(u8 *p, u32 i);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void Mtx43_SetTranslate(Mtx43 *m, s32 x, s32 y, s32 z);
void Mtx43_RotateX(Mtx43 *m, s32 angle);
void Mtx43_RotateY(Mtx43 *m, s32 angle);
s32 Ground_GetWaterKind(s32 x, s32 y);
BOOL Ground_IsPond(s32 x, s32 y);
BOOL Ground_FindWaterAhead(VecFx32 *out, VecFx32 *pos, s32 dir, u32 dist, u32 s5, s32 s6);
void GroundInfo_Destruct(void *obj);
u32 MapBlock_GetAttr(MapBlock *o);
s32 FieldAction_FindDropUnit(u32 kind, Vec2 *p, u8 *out);
void FishDisplay_PostRequest(u32 a, u32 b, s32 c, u32 d, u32 e);
u32 FishDisplay_GetRequestKind(u32 i);
u32 FishDisplay_GetRequestFish(u32 i);
BOOL FishDisplay_GetRequestPos(u32 *a, u32 *b, u32 i);
s32 FishDisplay_Acquire(void);
BOOL FishDisplay_SetEntry(s32 idx, s32 id, VecFx32 *pos, VecFx32 *vec, s16 a5, s16 a6, s16 a7, u8 a8, u8 a9, u32 a10);
void FishDisplay_Release(s32 idx);
BOOL FishDisplay_HasPassedFrame(s32 idx, s32 unused);
s32 Weather_GetFallingPrecip(void);
void Field_DrawItemModel(u32 item, VecFx32Copy a, VecFx32Copy b, s32 c, s16 d, s16 e);
void PlayerActor_ApplyHoldOffset(Mtx43 *b, VecFx32 *v);
s32 Math_AngleDiffAbs(s32 a, s32 b);
s16 Math_Atan2(s32 x, s32 y);
u16 Math_CountDownU16(u16 *p);
}

#ifndef HOST64
static_assert(sizeof(FishShadow) == 0x24c && __builtin_offsetof(FishShadow, model) == 0x144 && __builtin_offsetof(FishShadow, croak) == 0x248, "FishShadow");
static_assert(sizeof(FishCatch) == 0xa4 && __builtin_offsetof(FishCatch, storedSent) == 0xa0, "FishCatch");
static_assert(sizeof(BottleThrow) == 0x60 && sizeof(FieldFishManager) == 0x88, "BottleThrow / FieldFishManager");
static_assert(sizeof(FishInfo) == 6, "FishInfo");
#endif

struct FishBiteWindow {
    u8 b[4];
    s32 v;
};

struct FishSight {
    u16 dist;
    s16 angle;
};

struct FishRodParams {
    FishSight *sight;
    FishBiteWindow *bite;
};

struct FishSizeClassParams {
    u8 a0, a1, a2, a3;
    u8 b0, b1, b2, b3;
    u16 c0;
    u16 c1;
    u16 d;
    u8 shadowScaleX, shadowScaleZ;
    u16 g;
    u16 h;
};

extern "C" {
void *FieldFishManager_Create();
void BottleThrow_SetTarget(V3_f10 *v, s32 i);
BOOL BottleThrow_IsActive(s32 i);
s32 BottleThrow_Start(s32 i);
V3_f10 *BottleThrow_GetPos(s32 i);
s32 BottleThrow_GetSeCue(s32 i);
s32 BottleThrow_IsOffscreen(E_f9 *e);
void BottleThrow_Run(BottleThrowStateOwner *self, E_f9 *e);
void BottleThrow_StateIdle();
void BottleThrow_StateFly(void *self, E_f9 *e);
void BottleThrow_StateDrift(void *self, E_f9 *e);
void FieldFish_AddSinX(s32 *p, s32 a, s32 ang);
void FieldFish_AddCosZ(s32 *p, s32 a, s32 ang);
void FieldFish_MoveXZ(VecFx32 *p, s32 a, s32 ang);
void FishShadow_RunAppearAi(Obj_f9 *o);
void FishShadow_RunAi(Obj_f9 *o);
void FishShadow_AppearFree(Obj_f9 *o);
void FishShadow_ThinkFree(Obj_f9 *o);
void FishShadow_MoveStart(Obj_f9 *o);
void FishShadow_MoveAccelerate(Obj_f9 *o);
void FishShadow_MoveCruise(Obj_f9 *o);
void FishShadow_MoveDecelerate(Obj_f9 *o);
void FishShadow_MoveRest(Obj_f9 *o);
void FishShadow_MoveFlee(Obj_f8 *self);
void FishShadow_AppearAttached();
void FishShadow_ThinkBobber(Obj_f8 *self);
s32 FishShadow_BiteIdle(Obj_f8 *self);
s32 FishShadow_BiteApproach(Obj_f8 *self);
s32 FishShadow_BiteInspect(Obj_f8 *self);
s32 FishShadow_BiteNibble(Obj_f8 *self);
s32 FishShadow_BiteTug(Obj_f8 *self);
BOOL FishShadow_BiteHooked(Obj_f7 *o);
BOOL FishShadow_BiteFlee(Obj_f7 *o);
void FishShadow_OnRodPulled(Obj_f7 *o);
BOOL FishShadow_TryHook(Obj_f7 *o);
s32 FishShadow_CheckReelResult(Obj_f7 *o);
BOOL FishCatch_IsLandedForShadow(Obj_f7 *o);
BOOL FishCatch_EndForShadow(Obj_f7 *o);
void Fish_GetDisplayScale(V3_f7 *out, s32 idx);
BOOL FishCatch_SetDisplayPosScale(Obj_f7 *o, V3_f7 *a, V3_f7 *b);
BOOL FishCatch_StartLift(s32 idx, s32 flag);
BOOL FishCatch_IsActive(s32 idx);
V3_f7 *FishCatch_GetPos(s32 idx);
BOOL FishCatch_NetSendStored(s32 idx);
BOOL FishCatch_IsDisplayReady(Rec_f7 *self, u32 a);
void FishCatch_SetModelAngles(Rec_f7 *self, s32 a, s32 t);
BOOL FishShadow_FleeFromPlayer(Obj_f7 *self);
BOOL FishShadow_TryNoticeBobber(Obj_f7 *self);
BOOL FishShadow_CanSeeBobber(VecFx32 *self, s32 a1, s32 a2, s32 a3);
void FieldFish_StartCastSplash();
BOOL FieldFish_IsCastSplashActive();
void FieldFish_TickCastSplash();
BOOL FishShadow_Land(Obj_f6 *self, u32 k);
BOOL FishShadow_LoseBobber(Obj_f6 *self);
s32 FishShadow_GetEdgeColumn(Obj_f6 *self);
BOOL FishShadow_IsSeaNorth(Obj_f6 *self);
s32 FishShadow_CheckWaterBounds(Obj_f6 *self);
BOOL FishShadow_IsProbeOutOfWater(Obj_f6 *self);
void FishShadow_GetProbeGroundKinds(Obj_f6 *self, s32 *o1, s32 *o2, s32 *o3);
void FishCroak_Update(FishCroak *s, Obj_f6 *o);
void FishCroak_Idle(FishCroak *s, Obj_f6 *o);
void FishCroak_Listen(FishCroak *s, Obj_f6 *o);
void FishCroak_Croak(FishCroak *s, Obj_f6 *o);
void FishCroak_Clear(FishCroak *s);
void FishShadow_ResetCroak(Obj_f6 *self);
void FishCatch_Update(FishCatch *self, s32 arg);
s32 FishCatch_StateIdle();
BOOL FishCatch_StateStart(Self_f5 *self, u32 a);
BOOL FishCatch_SetupLine(Self_f5 *self, u32 a);
BOOL FishCatch_StateHold(Self_f5 *self, u32 a);
BOOL FishCatch_StateUpdate(Self_f5 *self, u32 a);
BOOL FishCatch_UpdateLocalReel(Self_f5 *self, u32 a);
BOOL FishCatch_UpdateRemoteReel(Self_f5 *self, u32 a);
BOOL FishCatch_StateEnd(Self_f5 *self, s32 a);
BOOL FishCatch_DetachShadow(Self_f5 *self);
void FishCatch_Reset(Self_f5 *self, s32 a);
void FishCatch_StartSwimAway(Self_f5 *self, s32 a);
void FishCatch_UpdateArc(Self_f5 *self, BOOL flag);
BOOL FieldFish_StepParabola(V3_f5 *p, V3_f5 *a, V3_f5 *b, s32 n, s32 k, s32 m);
BOOL FishCatch_UpdateSwimAway(Self_f5 *self, V3_f5 *p);
void FishCatch_GetLineEnd(Self_f5 *self, Ent_f5 *ent, V3_f5 *out);
void FishCatch_PollRemote(O_f3 *a);
void FishCatch_StartRemoteHook(O_f3 *a, s32 idx);
BOOL FishCatch_EndRemote(O_f3 *a, u8 idx);
BOOL FishCatch_StartRemoteReel(O_f3 *a, u8 idx, u32 v, VecFx32 *p);
BOOL FishCatch_StartRemoteLift(O_f3 *a, u8 idx);
void FishCroak_Init(FishCroak *p);
void FishCroak_Destroy(FishCroak *p);
BOOL FishShadow_SetAppearing(O_f3 *a, s32 idx);
void FishShadow_Despawn(O_f3 *a, s32 idx);
BOOL FishFinModel_Attach(O_f3 *a);
void FishFinModel_Release(O_f3 *a);
void FishShadow_Run(O_f3 *a, FishShadow *b, s32 c);
void FishShadow_ChangeState(O_f3 *a, s32 idx, FishShadow *b, s32 c);
void FishShadow_EnterSpawn();
void FishShadow_ExecSpawn(O_f3 *a, FishShadow *b, s32 c);
void FishShadow_EnterWaitInView();
void FishShadow_ExecWaitInView(O_f3 *a, FishShadow *b, s32 c);
void FishShadow_EnterAppear();
void FishShadow_ExecAppear(O_f3 *o, E_f3 *e);
void FishShadow_EnterOutOfView(void);
void FishShadow_ExecOutOfView(O_f3 *o, E_f3 *e, s32 idx);
void FishShadow_EnterSwim(void);
void FishShadow_ExecSwim(O_f3 *o, E_f3 *e, s32 x);
void FishShadow_UpdateFin(O_f3 *o, E_f3 *e);
void FieldFish_SetModelMatrix(O_f3 *a, VecFx32 *b, Model *dst, s32 ang);
void FieldFishManager_UpdatePlayers(O_f3 *o);
void FieldFishManager_FreeShadows(O_f3 *o);
void FieldFishManager_FreeCatches(O_f3 *a);
void FieldFishManager_ResetBottles(O_f3 *a);
BOOL FieldFish_ScareAround(VecFx32 *a, s32 b);
void FishShadow_UpdateVisibility(O_f3 *o, E_f3 *e, s32 idx);
void FishShadow_UpdateFade(O_f3 *o, E_f3 *e, s32 idx);
BOOL FishShadow_CheckPlayerScare(O_f3 *a, E_f3 *e);
BOOL FieldFish_IsPlayerApproaching(O_f3 *a, s32 b, E_f3 *e);
BOOL FishShadow_TryFlee(E_f3 *e, VecFx32 *a);
BOOL FishShadow_StartFlee(E_f3 *e, VecFx32 *a);
void FishShadow_CheckOffscreen(O_f3 *o, E_f3 *e, s32 idx);
void FieldWater_ApplyFlow(VecFx32 *p, s32 b);
BOOL FieldFish_IsPlayerRunning(s32 idx);
BOOL FieldFish_IsPlayerNear(O_f3 *self, VecFx32 *b, s32 idx);
BOOL FishShadow_TrySpawn(O_f3 *self, FishShadow *e, s32 flag);
BOOL FieldFish_CollectHabitatBlocks(O_f3 *self, u8 *out, s32 *cnt, s32 mode);
BOOL FieldFish_PickSpawnUnit(O_f3 *self, s32 *ox, s32 *oz, s32 *a3, s32 *a4, s32 mode, s32 flag, FishShadow *e);
BOOL FishShadow_CanSpawnFish(O_f3 *self, FishShadow *e, s32 id);
BOOL FieldFish_IsRainOrSnow(O_f3 *self);
void FishShadow_TickRespawnTimer(FishShadow *self);
BOOL FieldFish_IsInBox(VecFx32 *a, VecFx32 *b, s32 c, s32 d, s32 e);
BOOL FieldFish_HasPassed(VecFx32 *a, VecFx32 *b, VecFx32 *c);
BOOL FieldFish_HasPassed1D(s32 a, s32 b, s32 c);
s32 FieldFish_RandRange(s32 a, u16 b);
s32 FieldFish_RandRangeSigned(s32 a, u16 b);
BOOL FishCatch_GetReelTarget(VecFx32 *out, s32 idx);
BOOL FishCatch_StartRelease(s32 idx, u16 id0, VecFx32 *pos);
void FishShadow_SetAnimSpeed(FishShadow *self, s32 v);
BOOL FishShadow_LoadModel(FishShadow *self, void *p, ModelSlotPool *q);
BOOL FishFinModel_Load(FishFinModel *self, ModelSlotPool *a);
FishShadow *FishShadow_GetActive(s32 i);
s32 FishShadow_GetFishId(s32 id);
BOOL FishShadow_GetPos(VecFx32 *out, s32 id);
}

extern "C" {
FishShadow sFishShadows[6];
FishFinModel sFishFinModel;
FishCatch sFishCatches[4];
void *data_ov003_02257a7c;
BottleThrowStateOwner sBottleThrowStateOwner;
BottleThrow sBottleThrows[4];
BottleThrowStateEntry sBottleThrowStates[3];
FishSizeClassParams sFishSizeClassParams[8];
FishCatchStateEntry sFishCatchStates[5];
char *sFishShadowAnimPath = sFishShadowAnimPathStr;
char *sFishFinTexAnimPath = sFishFinTexAnimPathStr;
void *data_ov003_02234820[2] = {(void *)FishShadow_BiteIdle, 0};
void *data_ov003_022347b0[2] = {(void *)FishCatch_StateIdle, 0};
FishAiStateEntry sFishShadowAiTable[2];
s32 sBottleDriftSpeed = 0x11f;
FishMoveStateEntry sFishShadowMoveStates[6];
void *data_ov003_02234830[2] = {(void *)FishShadow_BiteApproach, 0};
void *data_ov003_02234838[2] = {(void *)FishShadow_AppearFree, 0};
void *data_ov003_02234898[2] = {(void *)FishShadow_BiteTug, 0};
void *data_ov003_022348a0[2] = {(void *)BottleThrow_StateIdle, 0};
void *data_ov003_022348a8[2] = {(void *)BottleThrow_StateDrift, 0};
FishBiteStateEntry sFishBiteStates[8];
void *data_ov003_022347a0[2] = {(void *)FishShadow_BiteNibble, 0};
s32 sBottleSinkStep = 0x14;
void *data_ov003_02234888[2] = {(void *)FishCatch_StateHold, 0};
char sFishShadowAnimPathStr[] = "/fish/03/fish_shadow.nsbca";
extern FishBiteWindow sFishBiteWindowFishingRod;
extern FishBiteWindow sFishBiteWindowGoldenRod;
FishRodParams sFishRodParams[2] = {
    {sFishSightFishingRod, &sFishBiteWindowFishingRod},
    {sFishSightGoldenRod, &sFishBiteWindowGoldenRod},
};
void *data_ov003_02234870[2] = {(void *)FishShadow_EnterWaitInView, 0};
void *data_ov003_022347c8[2] = {(void *)FishShadow_MoveRest, 0};
ProcProfile sFieldFishManagerProfile = {(void *(*)())FieldFishManager_Create, 0xc1, 7};
void *data_ov003_02234858[2] = {(void *)FishShadow_BiteInspect, 0};
void *data_ov003_02234850[2] = {(void *)FishShadow_EnterSwim, 0};
char sFishFinAnimPathStr[] = "/fish/03/fish_hire.nsbca";
FishSight sFishSightGoldenRod[5] = {{0x16, 0x2000}, {0x16, 0x2aa8}, {0x1a, 0x3556}, {0x1e, 0x4000}, {0x22, 0x5550}};
void *data_ov003_02234798[2] = {(void *)FishShadow_ExecOutOfView, 0};
void *data_ov003_022347b8[2] = {(void *)FishShadow_MoveDecelerate, 0};
FishBiteWindow sFishBiteWindowGoldenRod = {{9, 0xb, 0xd, 0x11}, 0x2a};
FishBiteWindow sFishBiteWindowFishingRod = {{8, 0xa, 0xb, 0xe}, 0x20};
u16 sFishCastSplashTimer;
char sFishShadowModelPathStr[] = "/fish/03/fish_shadow.nsbmd";
void *data_ov003_02234790[2] = {(void *)FishShadow_ExecAppear, 0};
void *data_ov003_02234800[2] = {(void *)FishShadow_ThinkBobber, 0};
void *data_ov003_022347f8[2] = {(void *)FishShadow_BiteFlee, 0};
void *data_ov003_02234890[2] = {(void *)FishCatch_StateStart, 0};
void *data_ov003_022347e8[2] = {(void *)FishShadow_MoveAccelerate, 0};
void *data_ov003_022347e0[2] = {(void *)FishShadow_MoveCruise, 0};
void *data_ov003_022347d8[2] = {(void *)FishShadow_ExecSpawn, 0};
void *data_ov003_022347d0[2] = {(void *)FishShadow_MoveFlee, 0};
void *data_ov003_02234880[2] = {(void *)FishCatch_StateUpdate, 0};
s32 sFishPullJitter;
void *data_ov003_02234808[2] = {(void *)FishShadow_AppearAttached, 0};
char *sFishFinAnimPath = sFishFinAnimPathStr;
char sFishFinTexAnimPathStr[] = "/fish/03/fish_hire.nsbta";
void *data_ov003_02234828[2] = {(void *)FishShadow_EnterAppear, 0};
void *data_ov003_022347a8[2] = {(void *)FishShadow_ExecWaitInView, 0};
void *data_ov003_022347c0[2] = {(void *)FishShadow_EnterSpawn, 0};
char *sFishShadowModelPath = sFishShadowModelPathStr;
void *data_ov003_022347f0[2] = {(void *)FishShadow_MoveStart, 0};
FishSight sFishSightFishingRod[5] = {{0x14, 0x1554}, {0x14, 0x1c72}, {0x16, 0x238e}, {0x19, 0x2aa8}, {0x1e, 0x4000}};
char sFishFinModelPathStr[] = "/fish/03/fish_hire.nsbmd";
void *data_ov003_02234818[2] = {(void *)FishShadow_ExecSwim, 0};
void *data_ov003_02234848[2] = {(void *)FishShadow_EnterOutOfView, 0};
FishShadowStateEntry sFishShadowStates[5];

extern "C" void StaticInit_unk_ov003_0221ffb8(void) {
    HOST_STATIC_CONSTRUCT(sFishShadows);
    HOST_STATIC_CONSTRUCT(sFishFinModel);
    HOST_STATIC_CONSTRUCT(sFishCatches);
    data_ov003_02257a7c = (void *)gSceneBlockMap;
    HOST_STATIC_CONSTRUCT(sBottleThrows);
    HOST_STATIC_INIT_ARRAY(sBottleThrowStates, {
        {*(StFn_f9 *)data_ov003_022348a0},
        {*(StFn_f9 *)data_ov003_02234868},
        {*(StFn_f9 *)data_ov003_022348a8},
    });
    HOST_STATIC_INIT_ARRAY(sFishSizeClassParams, {
        {0x3c, 0x40, 0xa, 0x14, 0x28, 0x64, 0x14, 0xa, 0x5, 0x3e, 0x5d, data_ov003_022348b0[0], data_ov003_022348b0[1], 0xdc, 0x8c},
        {0x3c, 0x42, 0xf, 0x1e, 0x28, 0x64, 0x14, 0xa, 0x5, 0x48, 0x69, data_ov003_022348b0[2], data_ov003_022348b0[3], 0xe6, 0x82},
        {0x46, 0x48, 0x14, 0x28, 0x28, 0x64, 0x14, 0xa, 0x5, 0x50, 0x85, data_ov003_022348b0[4], data_ov003_022348b0[5], 0xf0, 0x82},
        {0x55, 0x56, 0x19, 0x32, 0x28, 0x64, 0x14, 0xa, 0x5, 0x55, 0x96, data_ov003_022348b0[6], data_ov003_022348b0[7], 0xff, 0x78},
        {0x6e, 0x70, 0x1e, 0x3c, 0x28, 0x64, 0x14, 0xa, 0x5, 0x5c, 0xb7, data_ov003_022348b0[8], data_ov003_022348b0[9], 0x109, 0x78},
        {0x7d, 0x80, 0x23, 0x46, 0x28, 0x64, 0x14, 0xa, 0x5, 0x64, 0xc3, data_ov003_022348b0[10], data_ov003_022348b0[11], 0x113, 0x78},
        {0x96, 0x9a, 0x28, 0x50, 0x28, 0x64, 0x14, 0xa, 0x5, 0x6e, 0xd5, data_ov003_022348b0[12], data_ov003_022348b0[13], 0x11d, 0x78},
        {0x55, 0x56, 0x19, 0x32, 0x28, 0x64, 0x14, 0xa, 0x5, 0x5d, 0x9b, data_ov003_022348b0[14], data_ov003_022348b0[15], 0xff, 0x78},
    });
    HOST_STATIC_INIT_ARRAY(sFishCatchStates, {
        {*(Fn_f6 *)data_ov003_022347b0},
        {*(Fn_f6 *)data_ov003_02234890},
        {*(Fn_f6 *)data_ov003_02234888},
        {*(Fn_f6 *)data_ov003_02234880},
        {*(Fn_f6 *)data_ov003_02234878},
    });
    HOST_STATIC_INIT_ARRAY(sFishShadowAiTable, {
        {*(Fn_f9 *)data_ov003_02234838, *(Fn_f9 *)data_ov003_02234840},
        {*(Fn_f9 *)data_ov003_02234808, *(Fn_f9 *)data_ov003_02234800},
    });
    HOST_STATIC_INIT_ARRAY(sFishShadowMoveStates, {
        {*(Fn_f9 *)data_ov003_022347f0},
        {*(Fn_f9 *)data_ov003_022347e8},
        {*(Fn_f9 *)data_ov003_022347e0},
        {*(Fn_f9 *)data_ov003_022347b8},
        {*(Fn_f9 *)data_ov003_022347c8},
        {*(Fn_f9 *)data_ov003_022347d0},
    });
    HOST_STATIC_INIT_ARRAY(sFishBiteStates, {
        {*(Fn_f8 *)data_ov003_02234820},
        {*(Fn_f8 *)data_ov003_02234830},
        {*(Fn_f8 *)data_ov003_02234858},
        {*(Fn_f8 *)data_ov003_022347a0},
        {*(Fn_f8 *)data_ov003_02234898},
        {*(Fn_f8 *)data_ov003_02234810},
        {*(Fn_f8 *)data_ov003_022347f8},
    });
    HOST_STATIC_INIT_ARRAY(sFishShadowStates, {
        {*(Unk_ov003_0222144c_Fn_f4 *)data_ov003_022347c0, *(Unk_ov003_0222144c_Fn_f4 *)data_ov003_022347d8},
        {*(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234870, *(Unk_ov003_0222144c_Fn_f4 *)data_ov003_022347a8},
        {*(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234828, *(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234790},
        {*(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234850, *(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234818},
        {*(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234848, *(Unk_ov003_0222144c_Fn_f4 *)data_ov003_02234798},
    });
}
char *sFishFinModelPath = sFishFinModelPathStr;
u8 data_ov003_022348b0[16] = {0x1b, 0x21, 0x25, 0x35, 0x2f, 0x41, 0x39, 0x55, 0x3e, 0x5f, 0x48, 0x6b, 0x5e, 0x87, 0x23, 0x55};
void *data_ov003_02234878[2] = {(void *)FishCatch_StateEnd, 0};
void *data_ov003_02234840[2] = {(void *)FishShadow_ThinkFree, 0};
void *data_ov003_02234810[2] = {(void *)FishShadow_BiteHooked, 0};
void *data_ov003_02234868[2] = {(void *)BottleThrow_StateFly, 0};
}

extern "C" void *FieldFishManager_Create()
{
    return new FieldFishManager;
}


BottleThrowStateOwner::BottleThrowStateOwner() {}


BottleThrowStateOwner::~BottleThrowStateOwner() {}


BottleThrow::BottleThrow()
{
    BottleThrow *p = this;
    p->state = 0;
    p->position.x = 0x1000;
    p->position.y = 0x1000;
    p->position.z = 0x1000;
    p->startPos.x = 0x1000;
    p->startPos.y = 0x1000;
    p->startPos.z = 0x1000;
    p->targetPos.x = 0x1000;
    p->targetPos.y = 0x1000;
    p->targetPos.z = 0x1000;
    p->stateTimer = 0;
}


BottleThrow::~BottleThrow()
{
}


extern "C" void BottleThrow_SetTarget(V3_f10 *v, s32 i)
{
    if (i >= 0 && i < 4) {
        BottleThrow *e = &sBottleThrows[i];
        V3_f10 *pv = &e->targetPos;
        pv->x = v->x;
        pv->y = v->y;
        pv->z = v->z;
    }
}


extern "C" BOOL BottleThrow_IsActive(s32 i)
{
    if (i < 0 || i >= 4) {
        return FALSE;
    }
    BottleThrow *e = &sBottleThrows[i];
    u32 st = e->state;
    if (st == 0) goto zero;
    if (st == 2) {
        if (e->stateTimer > 0x64) goto zero;
    }
    if (BottleThrow_IsOffscreen(e) == 0) goto one;
zero:
    return FALSE;
one:
    return TRUE;
}


extern "C" s32 BottleThrow_Start(s32 i)
{
    BottleThrow *e;
    Character *p;
    CommManager *s;
    V3_f10 t;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &sBottleThrows[i];
    if (e->state != 0) {
        return 1;
    }
    p = (Character *)PlayerActor_GetCharacter(i);
    if (p == 0) {
        return 0;
    }
    s = gCommManager;
    if (s->isOnline()) {
        if (s->isMyAid(i)) {
            e->isLocal = 1;
        } else {
            e->isLocal = 0;
        }
        u32 f = p->actorFlags;
        if (Unk_ov003_02224bc4_Bit(f, 4) && Unk_ov003_02224bc4_Bit(f, 2)) {
            { VecFx32 *ps = &p->position; V3_f10 *pd = &e->startPos; pd->x = ps->x; pd->y = ps->y; pd->z = ps->z; }
        } else if (p->getHeldItemPos(&t)) {
            { V3_f10 *pd = &e->startPos; pd->x = t.x; pd->y = t.y; pd->z = t.z; }
        } else {
            { VecFx32 *ps = &p->position; V3_f10 *pd = &e->startPos; pd->x = ps->x; pd->y = ps->y; pd->z = ps->z; }
        }
    } else {
        e->isLocal = 1;
        if (p->getHeldItemPos(&t)) {
            { V3_f10 *pd = &e->startPos; pd->x = t.x; pd->y = t.y; pd->z = t.z; }
        } else {
            { VecFx32 *ps = &p->position; V3_f10 *pd = &e->startPos; pd->x = ps->x; pd->y = ps->y; pd->z = ps->z; }
        }
    }
    e->state = 1;
    { V3_f10 *pd = &e->position; pd->x = t.x; pd->y = t.y; pd->z = t.z; }
    e->stateTimer = 0;
    e->targetPos.y = -0x3800;
    return 2;
}


extern "C" V3_f10 *BottleThrow_GetPos(s32 i)
{
    if (i < 0 || i >= 4) {
        return &sBottleThrows[0].position;
    }
    return &sBottleThrows[i].position;
}


extern "C" s32 BottleThrow_GetSeCue(s32 i)
{
    s32 r = 0;
    if (i < 0 || i >= 4) {
        return 0;
    }
    E_f9 *e = &sBottleThrows[i];
    if (e->state == 1) {
        if (e->stateTimer == 0) {
            r = 1;
        } else if (e->stateTimer == 0xf) {
            r = 2;
        }
    }
    return r;
}


extern "C" s32 BottleThrow_IsOffscreen(E_f9 *e)
{
    s32 r = 0;
    if (gCamera == NULL) {
        return 1;
    }
    V3_f9 v(gCameraLookAt);
    if (FieldFish_IsInBox(&e->position, &v, 0x8000, 0x6000, 0x6000) == 0) {
        r = 1;
    }
    return r;
}


extern "C" void BottleThrow_Run(BottleThrowStateOwner *self, E_f9 *e)
{
    if (sBottleThrowStates[e->state].f) {
        (self->*sBottleThrowStates[e->state].f)(e);
    }
}


extern "C" void BottleThrow_StateIdle()
{
}


extern "C" void BottleThrow_StateFly(void *self, E_f9 *e)
{
    V3_f9 *pos = (V3_f9 *)&e->position;
    s32 *cnt = &e->stateTimer;
    V3d_f9 *pa = (V3d_f9 *)&e->startPos;
    V3d_f9 a(*pa);
    V3d_f9 *pb = (V3d_f9 *)&e->targetPos;
    V3d_f9 b(*pb);
    V3_f9 c30(*pos);
    V3_f9 c3c(*(V3_f9 *)&a);
    V3_f9 c48(*(V3_f9 *)&b);
    if (FieldFish_HasPassed(&c30, &c3c, &c48) != 0) {
        e->state = 2;
        *cnt = 0;
        if (e->isLocal != 0) {
            FieldFish_ScareAround(pos, 0x2800);
        }
    } else {
        V3_f9 x1(*(V3_f9 *)&a);
        V3_f9 x2(*(V3_f9 *)&b);
        s32 ok = FieldFish_StepParabola(pos, &x1, &x2, *cnt, 0x14cd, 0xf) == 0 ? 1 : 0;
        if (ok != 0) {
            e->state = 2;
            *cnt = 0;
            if (e->isLocal != 0) {
                FieldFish_ScareAround(pos, 0x2800);
            }
        }
        s32 t = (*cnt * 0x199a) >> 5;
        if (t > 0x199a) t = 0x199a;
        Collision_Move(&e->collisionState, pos, pos, FishAngleXZ(&e->targetPos, &e->startPos), t, 0, 0xb);
        Field_DrawItemModel(0x1520, V3_f9(*pos), V3_f9(0x1000, 0x1000, 0x1000), 0, 0, 0);
        *cnt = *cnt + 1;
    }
}


extern "C" void BottleThrow_StateDrift(void *self, E_f9 *e)
{
    VecFx32 *pos = &e->position;
    s32 *cnt = &e->stateTimer;
    V3_f9 a1, b, a2;
    s32 t;
    if (e->stateTimer < 0x64) {
        a1.x = pos->x;
        a1.y = pos->y;
        a1.z = pos->z;
        b.x = 0x1000;
        b.y = 0x1000;
        b.z = 0x1000;
        Field_DrawItemModel(0x1520, a1, b, 0, 0, 0);
        if (BottleThrow_IsOffscreen(e) != 0) {
            *cnt = 0x64;
        }
    } else if ((e->stateTimer & 1) != 0) {
        a2.x = pos->x;
        a2.y = pos->y;
        a2.z = pos->z;
        b.x = 0x1000;
        b.y = 0x1000;
        b.z = 0x1000;
        Field_DrawItemModel(0x1520, a2, b, 0, 0, 0);
    }
    FieldWater_ApplyFlow(pos, sBottleDriftSpeed);
    pos->y = pos->y - sBottleSinkStep;
    t = (*cnt * 0x199a) >> 5;
    if (t > 0x199a) t = 0x199a;
    Collision_Move(&e->collisionState, pos, pos, FishAngleXZ(&e->targetPos, &e->startPos), t, 0, 0xb);
    *cnt = *cnt + 1;
    if (*cnt >= 0x78) {
        e->state = 0;
        VecFx32 *v = &e->targetPos;
        e->targetPos.x = 0x1000;
        v->y = 0x1000;
        v->z = 0x1000;
    }
}


extern "C" void FieldFish_AddSinX(s32 *p, s32 a, s32 ang)
{
    *p += func_01ffcb0c(a, data_02135f44[((u16)ang >> 4) * 2]);
}


extern "C" void FieldFish_AddCosZ(s32 *p, s32 a, s32 ang)
{
    *p += func_01ffcb0c(a, data_02135f44[((u16)ang >> 4) * 2 + 1]);
}


extern "C" void FieldFish_MoveXZ(VecFx32 *p, s32 a, s32 ang)
{
    FieldFish_AddSinX(&p->x, a, ang);
    FieldFish_AddCosZ(&p->z, a, ang);
}


extern "C" void FishShadow_RunAppearAi(Obj_f9 *o)
{
    (o->*sFishShadowAiTable[o->aiMode].appear)();
}


extern "C" void FishShadow_RunAi(Obj_f9 *o)
{
    (o->*sFishShadowAiTable[o->aiMode].think)();
}


extern "C" void FishShadow_AppearFree(Obj_f9 *o)
{
    s32 r;
    o->position.x = o->spawnPos.x;
    o->position.y = o->spawnPos.y;
    o->position.z = o->spawnPos.z;
    (o->*sFishShadowMoveStates[o->moveState].f)();
    r = FishShadow_CheckWaterBounds(o);
    if (r != 0 && r != 5) {
        if (o->spawnState == 0) {
            o->rotY = o->rotY + 0x2aa8;
        } else {
            o->rotY = FieldFish_RandRangeSigned(0, 0xaaa);
        }
        o->appearCount = 0;
    } else {
        o->appearCount = o->appearCount + 1;
    }
    o->stateTimer = o->stateTimer + 2;
}


extern "C" void FishShadow_ThinkFree(Obj_f9 *o)
{
    s32 r;
    s32 x, y;
    if (o->fishId == 0xb) {
        FishCroak_Update(&o->croak, o);
    }
    (o->*sFishShadowMoveStates[o->moveState].f)();
    if (o->moveState == 5) {
        r = 0;
    } else {
        r = FishShadow_CheckWaterBounds(o);
    }
    switch (r) {
    case 0:
        o->appearCount = 0;
        break;
    case 1:
    case 3:
        if (o->turnDir != 0) {
            o->rotY = o->rotY + 0x222;
        } else {
            o->rotY = o->rotY - 0x222;
        }
        break;
    case 2:
    case 4:
        if (o->moveState == 1) {
            if (o->turnDir != 0) {
                o->rotY = o->rotY + 0x222;
            } else {
                o->rotY = o->rotY - 0x222;
            }
        }
        break;
    case 6:
        if (o->moveState != 4) {
            s32 t = *(volatile s16 *)&o->rotY;
            if (t < 0x3556 || t > 0x4aaa) {
                o->rotY = o->rotY - 0x555;
            }
        }
        break;
    case 7:
        if (o->moveState != 4) {
            s32 t = *(volatile s16 *)&o->rotY;
            if (t > -0x3556 || t < -0x4aaa) {
                o->rotY = o->rotY + 0x555;
            }
        }
        break;
    case 5:
        if ((u8)(o->moveState + 0xff) <= 1) {
            s32 t = *(volatile s16 *)&o->rotY;
            if (t < 0) t = -t;
            if (t < 0x7556) {
                if (o->turnDir != 0) {
                    o->rotY = o->rotY + 0x555;
                } else {
                    o->rotY = o->rotY - 0x555;
                }
            }
        }
        break;
    }
    o->stateTimer = o->stateTimer + 1;
    if (o->biteState != 7 && o->moveState != 5) {
        if (FishShadow_TryNoticeBobber(o) != 0) {
            o->stateTimer = 0;
            o->biteState = 0;
        }
    } else {
        o->biteState = 0;
        switch (o->habitat) {
        case 0:
        case 1:
        case 2:
        case 3:
            FieldPos_ToUnit(&x, &y, &o->position);
            if (Ground_GetWaterKind(x, y) == 1) {
                FishShadow_TryFlee(o, &o->prevPosition);
            }
            break;
        case 4:
            break;
        case 5:
        case 6:
            FieldPos_ToUnit(&x, &y, &o->position);
            if (Ground_GetWaterKind(x, y) == 2) {
                FishShadow_TryFlee(o, &o->prevPosition);
            }
            break;
        }
    }
}


extern "C" void FishShadow_MoveStart(Obj_f9 *o)
{
    o->rotY = o->rotY + (s16)FieldFish_RandRangeSigned(0, 0x2aa8);
    o->stateTimer = 0;
    o->cruiseTimer = (u8)FieldFish_RandRange(1, 3);
    o->wobblePhase = FieldFish_RandRangeSigned(0xaaa, 0x2000);
    o->turnDir = FieldFish_RandRangeSigned(0, 2) != 0 ? 1 : 0;
    o->moveState = 1;
}


extern "C" void FishShadow_MoveAccelerate(Obj_f9 *o)
{
    s32 t;
    s32 a, b, x, q, z, c, d;
    t = o->stateTimer << 3;
    o->wobblePhase = o->wobblePhase + 0x2000;
    a = data_02135f44[((u16)o->wobblePhase >> 4) * 2];
    b = data_02135f44[((u16)o->rotY >> 4) * 2];
    q = t >> 2;
    x = func_01ffcb0c(t, b) + func_01ffcb0c(q, a);
    c = data_02135f44[((u16)o->wobblePhase >> 4) * 2];
    d = data_02135f44[((u16)o->rotY >> 4) * 2 + 1];
    z = func_01ffcb0c(t, d) + func_01ffcb0c(q, c);
    o->position.x += x;
    o->position.z += z;
    if (o->stateTimer >= 10) {
        FishShadow_SetAnimSpeed(o, 0x20);
    } else {
        FishShadow_SetAnimSpeed(o, 0x10);
    }
    if (t > 0x19a) {
        o->moveState = 2;
    }
}


extern "C" void FishShadow_MoveCruise(Obj_f9 *o)
{
    FieldFish_MoveXZ(&o->position, 0x19a, o->rotY);
    FishShadow_SetAnimSpeed(o, 0x20);
    o->cruiseTimer--;
    if (o->cruiseTimer == 0) {
        o->stateTimer = 0;
        o->moveState = 3;
    }
}


extern "C" void FishShadow_MoveDecelerate(Obj_f9 *o)
{
    s32 t = 0x19a - (o->stateTimer << 3);
    FieldFish_MoveXZ(&o->position, t, o->rotY);
    if (o->stateTimer >= 10) {
        FishShadow_SetAnimSpeed(o, 3);
    } else {
        FishShadow_SetAnimSpeed(o, 0x10);
    }
    if (t <= 0) {
        o->stateTimer = 0;
        o->moveState = 4;
    }
}


extern "C" void FishShadow_MoveRest(Obj_f9 *o)
{
    FishShadow_SetAnimSpeed(o, 10);
    FieldWater_ApplyFlow(&o->position, 0x40);
    if (FieldFish_RandRange(0, 0x64) == 1 || o->stateTimer > 0x64) {
        o->moveState = 0;
    }
}


extern "C" void FishShadow_MoveFlee(Obj_f8 *self)
{
    s32 a, x, y, sq;
    s32 t, s142, s138;
    u16 *pf;
    a = self->stateTimer << 7;
    if (a > 0x215) {
        a = 0x215;
    }
    pf = (u16 *)&self->wobblePhase;
    *pf = (s16)*pf + 0x2000;
    s142 = data_02135f44[(*pf >> 4) * 2];
    s138 = *(volatile s16 *)&data_02135f44[((u16)self->rotY >> 4) * 2];
    sq = a >> 5;
    t = func_01ffcb0c(a, s138);
    x = t + func_01ffcb0c(sq, s142);
    s142 = data_02135f44[((u16)self->wobblePhase >> 4) * 2];
    s138 = *(volatile s16 *)&data_02135f44[(((u16)self->rotY >> 4) * 2) + 1];
    t = func_01ffcb0c(a, s138);
    y = t + func_01ffcb0c(sq, s142);
    self->position.x += x;
    self->position.z += y;
    if (self->hasFin) {
        if (self->stateTimer >= 10) {
            FishShadow_SetAnimSpeed(self, 3);
        } else if (self->stateTimer >= 5) {
            FishShadow_SetAnimSpeed(self, 0x10);
        } else {
            FishShadow_SetAnimSpeed(self, 0x20);
        }
    } else {
        FishShadow_SetAnimSpeed(self, 0x20);
    }
    {
        V3_f8 v;
        v.x = self->position.x;
        v.y = self->position.y;
        v.z = self->position.z;
        v.y = data_020c7c1c;
        Effect_SetPosition(self->effectHandle, &v, 0, 0);
    }
}


extern "C" void FishShadow_AppearAttached()
{
}


extern "C" void FishShadow_ThinkBobber(Obj_f8 *self)
{
    if ((self->*sFishBiteStates[self->biteState].f)() == 0) {
        FishShadow_FleeFromPlayer(self);
    }
    self->stateTimer = self->stateTimer + 1;
}


extern "C" s32 FishShadow_BiteIdle(Obj_f8 *self)
{
    if (self->bobber == 0) {
        return 0;
    }
    self->biteState = 1;
    return 1;
}


extern "C" s32 FishShadow_BiteApproach(Obj_f8 *self)
{
    FishBobber *p = self->bobber;
    s32 dv, s;
    if (p == 0) {
        return 0;
    }
    VecFx32 *q = &p->pos;
    dv = ((s32)sFishSizeClassParams[self->sizeClass].a0 << 12) / 100;
    s = self->biteStepTimer << 4;
    if (s >= 0x100) {
        s = 0x100;
    }
    self->rotY = FishAngleXZ(&self->position, q);
    FieldFish_MoveXZ(&self->position, s, (s16)self->rotY);
    FishShadow_SetAnimSpeed(self, 0x18);
    if (FieldFish_IsInBox(&self->position, q, dv, dv, dv)) {
        s32 r = FieldFish_RandRange(0, 100);
        s32 lim = 0x5f;
        s32 a, b;
        FieldPos_ToUnit(&a, &b, q);
        switch (self->habitat) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (Ground_GetWaterKind(a, b) == 1) {
                lim = 0x64;
            }
            break;
        case 4:
            break;
        case 5:
        case 6:
            if (Ground_GetWaterKind(a, b) == 2) {
                lim = 0x64;
            }
            break;
        }
        if (r <= lim) {
            self->biteDelay = FieldFish_RandRange(4, 0xb4);
            self->stateTimer = 0;
            self->biteStepTimer = 0;
            self->biteStep = 3;
            self->biteState = 3;
            self->rotY = FishAngleXZ(&self->position, q);
        } else {
            self->biteStepTimer = 0;
            self->biteStep = 0;
            self->biteState = 2;
            self->rotY = FishAngleXZ(&self->position, q);
        }
    }
    self->biteStepTimer = self->biteStepTimer + 1;
    return 1;
}


extern "C" s32 FishShadow_BiteInspect(Obj_f8 *self)
{
    FishBobber *p = self->bobber;
    VecFx32 *q;
    if (p == 0) {
        return 0;
    }
    q = &p->pos;
    switch (self->biteStep) {
    case 0: {
        s32 s, dv;
        dv = ((s32)sFishSizeClassParams[self->sizeClass].a0 << 12) / 100;
        s = self->biteStepTimer << 4;
        if (s >= 0x100) {
            s = 0x100;
        }
        self->rotY = FishAngleXZ(&self->position, q);
        FieldFish_MoveXZ(&self->position, s, (s16)self->rotY);
        if (FieldFish_IsInBox(&self->position, q, dv, dv, dv)) {
            self->biteStepTimer = 0;
            p->nudge();
            self->biteStep = 1;
        }
        break;
    }
    case 1: {
        s32 lim = FieldFish_RandRange(10, 15);
        if (FieldFish_RandRange(0, 100) < 0x32) {
            self->rotY = FishAngleXZ(q, &self->position);
        } else {
            self->rotY = FishAngleXZ(&self->position, q);
        }
        FieldFish_MoveXZ(&self->position, 0x100, (s16)self->rotY);
        self->rotY = FishAngleXZ(&self->position, q);
        if (self->biteStepTimer > lim) {
            self->biteStepTimer = 0;
            self->rotY = (s16)self->rotY + (s16)(FieldFish_RandRangeSigned(1, 2) * 0x1554);
            self->biteStep = 2;
        }
        break;
    }
    case 2: {
        s32 dv = ((s32)sFishSizeClassParams[self->sizeClass].d << 12) / 100;
        FieldFish_MoveXZ(&self->position, 0x14c, (s16)self->rotY);
        if (FieldFish_IsInBox(&self->position, q, dv, dv, dv) == 0) {
            if (FishShadow_LoseBobber(self) == 0) {
                FishShadow_FleeFromPlayer(self);
            }
        }
        break;
    }
    }
    FishShadow_SetAnimSpeed(self, 0x18);
    self->biteStepTimer = self->biteStepTimer + 1;
    return 1;
}


extern "C" s32 FishShadow_BiteNibble(Obj_f8 *self)
{
    BOOL r = FALSE;
    FishBobber *p = self->bobber;
    VecFx32 *q;
    s32 base;
    s32 dv, sq, ang;
    if (p == 0) {
        return r;
    }
    q = &p->pos;
    if (self->stateTimer >= self->biteDelay) {
        s32 dv = ((s32)sFishSizeClassParams[self->sizeClass].a0 << 12) / 100;
        if (FieldFish_IsInBox(&self->position, q, dv, dv, dv)) {
            self->stateTimer = r;
            p->setState(5);
            Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x84f, 0x7f, r);
            {
                s32 t = self->fishId;
                if (t != 0x38 && t != 0x39 && t != 0x3a) {
                    goto plain;
                }
                {
                    Vec2 arr;
                    arr.y = arr.x = 0;
                    if (FieldAction_FindDropUnit(0x10, &arr, NULL)) {
                        self->biteState = 4;
                        self->biteStep = 6;
                        r = TRUE;
                    }
                }
                goto done;
            plain:
                self->biteState = 4;
                self->biteStep = 6;
                r = TRUE;
            done:;
            }
            return r;
        }
    }
    base = (u32)sFishSizeClassParams[self->sizeClass].a0 << 12;
    switch (self->biteStep) {
    case 3: {
        dv = base / 100;
        s32 s = self->biteStepTimer << 4;
        s64 d;
        if (s >= 0x100) {
            s = 0x100;
        }
        FieldFish_MoveXZ(&self->position, s, FishAngleXZ(&self->position, q));
        d = Vec_DistSqXZ(&self->position, q);
        if ((s64)func_01ffcb0c(dv, dv) >= d) {
            self->biteStepTimer = 0;
            p->nudge();
            self->biteStep = 4;
        }
        FishShadow_SetAnimSpeed(self, 0x18);
        break;
    }
    case 4: {
        s32 lim = FieldFish_RandRange(10, 0x14);
        if (FieldFish_RandRange(0, 100) < 0x32) {
            ang = FishAngleXZ(q, &self->position);
        } else {
            ang = FishAngleXZ(&self->position, q);
            if (FieldFish_RandRange(0, 100) < 5) {
                p->nudge();
            }
        }
        FieldFish_MoveXZ(&self->position, 0x100, ang);
        if (self->biteStepTimer > lim) {
            self->biteStepTimer = 0;
            self->biteStep = 5;
        }
        break;
    }
    case 5: {
        s32 dv = ((s32)sFishSizeClassParams[self->sizeClass].d << 12) / 100;
        s32 s = 0x100 - (self->biteStepTimer << 4);
        if (s < 0) {
            s = 0;
        }
        FieldFish_MoveXZ(&self->position, s, FishAngleXZ(q, &self->position));
        if (s == 0 || FieldFish_IsInBox(&self->position, q, dv, dv, dv) == 0) {
            self->biteStepTimer = 0;
            self->biteStep = 3;
        }
        FishShadow_SetAnimSpeed(self, 0x10);
        break;
    }
    }
    {
        sq = base >> 9;
        s64 d = Vec_DistSqXZ(&self->position, q);
        if (d >= (s64)func_01ffcb0c(sq, sq)) {
            self->rotY = FishAngleXZ(&self->position, q);
        }
    }
    self->biteStepTimer = self->biteStepTimer + 1;
    return 1;
}


extern "C" s32 FishShadow_BiteTug(Obj_f8 *self)
{
    FishBobber *p = self->bobber;
    VecFx32 *q;
    s32 idx;
    if (p == 0) {
        return 0;
    }
    if (self->playerIdx == -1) {
        return 0;
    }
    q = &p->pos;
    FishShadow_SetAnimSpeed(self, 0x18);
    {
        u16 out[2];
        BOOL ok;
        u16 a, b;
        PlayerActor_GetSlotHeldItem(out, self->playerIdx);
        ok = FALSE;
        {
            volatile u16 *pv = &out[0];
            a = *pv;
            b = *pv;
        }
        if (b >= 0x1374 && a <= 0x1374) {
            ok = TRUE;
        }
        if (ok) {
            idx = 0;
        } else if (a >= 0x1375 && a <= 0x1375) {
            idx = 1;
        } else {
            return 0;
        }
    }
    {
        s32 cur = self->stateTimer;
        FishBiteWindow *lim = sFishRodParams[idx].bite;
        if (cur >= lim->b[gFishInfo[self->fishId].timingClass]) {
            self->stateTimer = 0;
            p->setState(4);
            return 0;
        }
    }
    switch (self->biteStep - 6) {
    case 0: {
        s32 dv = ((s32)sFishSizeClassParams[self->sizeClass].a0 << 12) / 100;
        s32 ang = FishAngleXZ(&self->position, q);
        FieldFish_MoveXZ(&self->position, 0x180, ang);
        FieldFish_MoveXZ(&self->position, 0xc0, (s16)(ang + 0x4000));
        if (FieldFish_IsInBox(&self->position, q, dv, dv, dv)) {
            self->biteStep = 8;
        } else {
            self->biteStep = 7;
        }
        break;
    }
    case 1: {
        s32 dv = ((s32)sFishSizeClassParams[self->sizeClass].a0 << 12) / 100;
        s32 ang = FishAngleXZ(&self->position, q);
        FieldFish_MoveXZ(&self->position, 0x180, ang);
        FieldFish_MoveXZ(&self->position, 0xc0, (s16)(ang - 0x4000));
        if (FieldFish_IsInBox(&self->position, q, dv, dv, dv)) {
            self->biteStep = 8;
        } else {
            self->biteStep = 6;
        }
        break;
    }
    case 2: {
        s32 dv = ((s32)sFishSizeClassParams[self->sizeClass].a1 << 12) / 100;
        s32 r;
        s32 ang = FishAngleXZ(q, &self->position);
        FieldFish_MoveXZ(&self->position, 0x180, ang);
        r = FieldFish_RandRange(0, 100);
        if (FieldFish_IsInBox(&self->position, q, dv, dv, dv) == 0) {
            if (r >= 0x46) {
                self->biteStep = 6;
            } else {
                self->biteStep = 9;
            }
        }
        break;
    }
    case 3:
        if (FieldFish_RandRange(0, 100) <= 0x32) {
            self->biteStep = 7;
        }
        break;
    }
    self->rotY = FishAngleXZ(&self->position, q);
    return 1;
}


extern "C" BOOL FishShadow_BiteHooked(Obj_f7 *o) {
    FishBobber *e = o->bobber;
    if (e == NULL) {
        return FALSE;
    }
    s32 step;
    s32 ang;
    if (o->sizeClass >= 3) {
        step = 0x1000;
    } else {
        step = 0x1249;
    }
    if (o->pullDir != 0) {
        if (o->model.hasPassedFrame(4)) {
            o->model.curFrame = 0x3000;
        }
        o->rotY = o->rotY + step;
        ang = (s16)(o->rotY - 0x4000);
    } else {
        if (o->model.hasPassedFrame(0xb)) {
            o->model.curFrame = 0xa000;
        }
        o->rotY = o->rotY - step;
        ang = (s16)(o->rotY + 0x4000);
    }
    s32 d = FieldFish_RandRangeSigned(3, 10);
    s32 s = sFishPullJitter + d;
    sFishPullJitter = s;
    if (s < -12) {
        sFishPullJitter = -12;
    } else if (s > 0x14) {
        sFishPullJitter = 0x14;
    }
    s32 d2 = FieldFish_RandRangeSigned(0, 0xf);
    s32 sum = sFishPullJitter + d2 + sFishSizeClassParams[o->sizeClass].c1;
    s32 sc = _s32_div_f(sum << 12, 100);
    V3_f7 v;
    V3_f7 *ps = &e->pos;
    v.x = e->pos.x;
    v.y = ps->y;
    v.z = ps->z;
    o->position.x = v.x;
    o->position.z = v.z;
    FieldFish_MoveXZ(&o->position, sc, ang);
    VecFx32 *m = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (m != NULL) {
        s32 a2 = FishAngleXZ(m, &v);
        FieldFish_MoveXZ(&o->position, 0xa00, a2);
    }
    return TRUE;
}


extern "C" BOOL FishShadow_BiteFlee(Obj_f7 *o) {
    FishShadow_SetAnimSpeed(o, 0x1c);
    s32 c = o->stateTimer;
    s32 v = (c + 10) * 25;
    if (v >= 0x180) {
        v = 0x180;
    }
    if (o->hasFin != 0) {
        if (c >= 0x14) {
            FishShadow_SetAnimSpeed(o, 3);
        } else if (c >= 0xf) {
            FishShadow_SetAnimSpeed(o, 0x10);
        } else {
            FishShadow_SetAnimSpeed(o, 0x20);
        }
    }
    FieldFish_MoveXZ(&o->position, v, o->rotY);
    V3_f7 t;
    t.x = o->position.x;
    t.y = o->position.y;
    t.z = o->position.z;
    t.y = data_020c7c1c;
    Effect_SetPosition(o->effectHandle, &t, 0, 0);
    return TRUE;
}


extern "C" void FishShadow_OnRodPulled(Obj_f7 *o) {
    if (o->aiMode == 1) {
        switch (o->biteState) {
        case 3:
        case 4:
        case 5:
            FishShadow_FleeFromPlayer(o);
            break;
        case 6:
            break;
        default:
            if (FishShadow_LoseBobber(o) == 0) {
                FishShadow_FleeFromPlayer(o);
            }
            break;
        }
    }
}


extern "C" BOOL FishShadow_TryHook(Obj_f7 *o) {
    BOOL r = FALSE;
    if (o == NULL) {
        return r;
    }
    FishBobber *e = o->bobber;
    if (e == NULL) {
        FishShadow_FleeFromPlayer(o);
        return r;
    }
    switch (o->biteState) {
    case 4: {
        u16 buf[1];
        PlayerActor_GetSlotHeldItem(buf, o->playerIdx);
        u32 k = 0;
        u32 a = *(volatile u16 *)buf;
        u32 b = *(volatile u16 *)buf;
        s32 m;
        if (b >= 0x1374 && a <= 0x1374) {
            k = 1;
        }
        if (k) {
            m = 0;
        } else if (a >= 0x1375 && a <= 0x1375) {
            m = 1;
        } else {
            FishShadow_FleeFromPlayer(o);
            return FALSE;
        }
        if (gTouchHeld == 0) {
            s32 cur = o->stateTimer;
            FishBiteWindow *tbl = sFishRodParams[m].bite;
            if (cur > tbl->b[gFishInfo[o->fishId].timingClass] - 1) {
                FishShadow_FleeFromPlayer(o);
                return FALSE;
            }
        }
        o->biteState = 5;
        o->biteStep = 10;
        o->stateTimer = 0;
        e->setState(6);
        o->pullDir = FieldFish_RandRange(0, 2) != 0;
        o->reelGoal = FieldFish_RandRange(sFishSizeClassParams[o->sizeClass].a2, sFishSizeClassParams[o->sizeClass].a3);
        V3_f7 *ps = &e->pos;
        V3_f7 *pd = &o->hookPos;
        pd->x = e->pos.x;
        pd->y = ps->y;
        pd->z = ps->z;
        if (o->pullDir != 0) {
            o->rotY = o->rotY - 0x4000;
        } else {
            o->rotY = o->rotY + 0x4000;
        }
        r = TRUE;
        break;
    }
    case 3:
        FishShadow_FleeFromPlayer(o);
        break;
    case 6:
        break;
    default:
        if (FishShadow_LoseBobber(o) == 0) {
            FishShadow_FleeFromPlayer(o);
        }
        break;
    }
    return r;
}


extern "C" s32 FishShadow_CheckReelResult(Obj_f7 *o) {
    s32 r = 0;
    if (o == NULL) {
        return r;
    }
    if (o->biteState != 5) {
        return r;
    }
    if (o->stateTimer >= o->reelGoal) {
        if (FishShadow_Land(o, o->slotIndex)) {
            r = 2;
        } else {
            FishShadow_FleeFromPlayer(o);
            r = 1;
        }
    }
    return r;
}


extern "C" BOOL FishCatch_IsLandedForShadow(Obj_f7 *o) {
    BOOL r = FALSE;
    if (o == NULL) {
        return r;
    }
    s32 i = o->playerIdx;
    if (i == -1) {
        return r;
    }
    Rec_f7 *p = &sFishCatches[i];
    if (p->isLanded != 0) {
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishCatch_EndForShadow(Obj_f7 *o) {
    if (o == NULL) {
        return FALSE;
    }
    s32 i = o->playerIdx;
    BOOL r = FALSE;
    if (i != -1) {
        Rec_f7 *p = &sFishCatches[i];
        p->state = 4;
        r = TRUE;
    }
    return r;
}


extern "C" void Fish_GetDisplayScale(V3_f7 *out, s32 idx) {
    if (idx < 0 || idx >= 0x3b) {
        out->x = 0x1000;
        out->y = 0x1000;
        out->z = 0x1000;
    } else {
        s32 v = _s32_div_f((u8)sFishSizeClassParams[gFishInfo[idx].sizeClass].h << 12, 100);
        out->x = v;
        out->y = v;
        out->z = v;
    }
}


extern "C" BOOL FishCatch_SetDisplayPosScale(Obj_f7 *o, V3_f7 *a, V3_f7 *b) {
    if (o == NULL) {
        return FALSE;
    }
    s32 i = o->playerIdx;
    if (i == -1) {
        return FALSE;
    }
    Rec_f7 *r = &sFishCatches[i];
    V3_f7 *pd = &r->position;
    pd->x = a->x;
    pd->y = a->y;
    pd->z = a->z;
    pd = &r->scale;
    pd->x = b->x;
    pd->y = b->y;
    pd->z = b->z;
    return TRUE;
}


extern "C" BOOL FishCatch_StartLift(s32 idx, s32 flag) {
    s32 t;
    s32 ang;
    V3_f7 *pos;
    if (idx < 0 || idx > 3) {
        return FALSE;
    }
    Actor *ob = (Actor *)PlayerActor_GetActor(idx);
    if (ob == NULL) {
        return FALSE;
    }
    pos = &ob->position;
    Rec_f7 *rec = &sFishCatches[idx];
    t = rec->fishId;
    if ((u32)(t - 0x38) <= 2) {
        if (flag != 0) {
            return TRUE;
        }
        rec->state = 4;
        return TRUE;
    }
    V3_f7 *q = &rec->arcPointA;
    ang = FishAngleXZ(&rec->arcPointB, q);
    V3_f7 tmp;
    if (Ground_FindWaterAhead(&tmp, pos, ang, 0x7800, 0x2000, 0xc)) {
        q->x = tmp.x;
        q->y = tmp.y;
        q->z = tmp.z;
    }
    FishCatch_SetModelAngles(rec, ang, t);
    if (flag != 0) {
        rec->state = 1;
    }
    rec->mode = 3;
    CommManager *g = gCommManager;
    if (g->isOnline()) {
        if (g->isMyAid(idx)) {
            u8 b = 2;
            g = gCommManager;
            g->beginRecord();
            g->writeRecord((u8 *)(&b), 1);
            g->endRecord(0x2a, 4);
        }
    }
    return TRUE;
}


extern "C" BOOL FishCatch_IsActive(s32 idx) {
    if (idx < 0 || idx >= 4) {
        return TRUE;
    }
    Rec_f7 *p = &sFishCatches[idx];
    if (p->state != 0) {
        return TRUE;
    }
    return FALSE;
}


extern "C" V3_f7 *FishCatch_GetPos(s32 idx) {
    if (idx < 0 || idx >= 4) {
        return &sFishCatches[0].position;
    }
    return &sFishCatches[idx].position;
}


extern "C" BOOL FishCatch_NetSendStored(s32 idx) {
    BOOL r = FALSE;
    if (idx < 0 || idx >= 4) {
        return FALSE;
    }
    Rec_f7 *p = &sFishCatches[idx];
    if (p->state != 3 && p->state != 2) {
        return r;
    }
    if (p->storedSent == 0) {
        u8 b = 1;
        CommManager *g = gCommManager;
        g->beginRecord();
        g->writeRecord((u8 *)(&b), 1);
        g->endRecord(0x2a, 4);
        r = TRUE;
        p->storedSent = r;
    }
    return r;
}


extern "C" BOOL FishCatch_IsDisplayReady(Rec_f7 *self, u32 a) {
    BOOL r = FALSE;
    if (FishDisplay_HasPassedFrame(self->displayHandle, 1)) {
        r = TRUE;
    }
    return r;
}


extern "C" void FishCatch_SetModelAngles(Rec_f7 *self, s32 a, s32 t) {
    s16 *p96 = &self->rotX;
    s16 *p98 = &self->rotY;
    s16 *p9a = &self->rotZ;
    switch (t) {
    case 0xa:
    case 0xb:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
        *p9a = *p9a + 0x7fff;
        *p98 = -a;
        *p96 = *p96 + 0x4000;
        break;
    case 0xf:
        *p9a = *p9a + 0x6000;
        *p98 = a;
        *p96 = *p96 + 0x4000;
        break;
    case 0x23:
    case 0x24:
    case 0x25:
        *p98 = a;
        break;
    case 0x35:
    case 0x36:
        *p96 = *p96 + 0x4000;
        *p98 = a;
        break;
    default:
        *p9a = *p9a + 0x4000;
        *p96 = a;
        *p96 = *p96 + 0x4000;
        break;
    }
}


extern "C" BOOL FishShadow_FleeFromPlayer(Obj_f7 *self) {
    BOOL r = FALSE;
    if (self == NULL) {
        return r;
    }
    VecFx32 *p = (VecFx32 *)PlayerActor_GetBodyPos(4);
    if (p == NULL) {
        return r;
    }
    if (FishShadow_StartFlee(self, p)) {
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishShadow_TryNoticeBobber(Obj_f7 *self) {
    s32 res = 0;
    FishBobber *e = FishBobber_GetFloating(0);
    s32 who;
    Obj_f7 *p;
    s32 ok;
    s32 i;
    if (e == NULL) {
        return FALSE;
    }
    CommManager *g = gCommManager;
    if (g->isOnline()) {
        s32 t = e->ownerAid;
        if (t < 0) {
            return FALSE;
        }
        who = g->myAid;
        if (t != who) {
            return FALSE;
        }
    } else {
        who = 0;
    }
    p = sFishShadows;
    ok = 1;
    for (i = 0; i < 6; p++, i++) {
        if (self != p && who == p->playerIdx) {
            ok = 0;
            break;
        }
    }
    if (ok != 0) {
        V3_f7 v8;
        V3_f7 v14;
        V3_f7 *p120 = &self->position;
        v14.x = p120->x;
        v14.y = p120->y;
        v14.z = p120->z;
        if (FishShadow_CanSeeBobber(&v14, self->rotY, who, self->fishId)) {
            s32 sc = _s32_div_f(sFishSizeClassParams[self->sizeClass].a0 << 12, 100);
            V3_f7 *pv = &e->pos;
            v8.x = e->pos.x;
            v8.y = pv->y;
            v8.z = pv->z;
            if (FieldFish_IsCastSplashActive() && FieldFish_IsInBox(&self->position, &v8, sc, sc, sc)) {
                if (self->moveState != 2) {
                    self->moveState = 2;
                }
                s32 r = FieldFish_RandRangeSigned(0x5000, 0x7fff);
                self->rotY = self->rotY + (s16)r;
                self->cruiseTimer = 0x14;
            } else {
                self->playerIdx = (s8)who;
                self->bobber = e;
                e->setFish(self);
                res = 1;
                self->aiMode = 1;
            }
        }
        FieldFish_TickCastSplash();
    }
    return res;
}


extern "C" BOOL FishShadow_CanSeeBobber(VecFx32 *self, s32 a1, s32 a2, s32 a3)
{
    volatile BOOL result = FALSE;
    FishBobber *p;
    VecFx32 *p2;
    u16 vw;
    volatile u16 *pp;
    BOOL k;
    u32 a, b;
    s32 idx;
    s32 val;
    FishSight *t;

    p = FishBobber_GetFloating(0);
    if (p == NULL) {
        return FALSE;
    }
    PlayerActor_GetSlotHeldItem(&vw, a2);
    k = FALSE;
    pp = &vw;
    a = *pp;
    b = *pp;
    if (b >= 0x1374 && a <= 0x1374) {
        k = TRUE;
    }
    if (k) {
        idx = 0;
    } else if (a >= 0x1375 && a <= 0x1375) {
        idx = 1;
    } else {
        return FALSE;
    }
    p2 = &p->pos;
    t = &sFishRodParams[idx].sight[gFishInfo[a3].rodClass];
    val = ((u8)t->dist << 12) / 10;
    if (FieldFish_IsInBox(self, p2, val, val, val)) {
        s32 lim = t->angle;
        if (Math_AngleDiffAbs(FishAngleXZ(self, p2), a1) <= lim) {
            result = TRUE;
        }
    }
    return result;
}


extern "C" void FieldFish_StartCastSplash()
{
    sFishCastSplashTimer = 10;
}


extern "C" BOOL FieldFish_IsCastSplashActive()
{
    if (sFishCastSplashTimer != 0) {
        return TRUE;
    }
    return FALSE;
}


extern "C" void FieldFish_TickCastSplash()
{
    if (sFishCastSplashTimer != 0) {
        sFishCastSplashTimer--;
    }
}


extern "C" BOOL FishShadow_Land(Obj_f6 *self, u32 k)
{
    s32 idx;
    Ent_f6 *e;
    V3_f6 *pv;
    V3_f6 loc;
    u8 buf[7];
    u8 tmp[5];
    CommManager *s;
    u32 sel;
    s32 h;
    V3_f6 *q;
    BOOL z;

    self->alpha = 1;
    idx = self->playerIdx;
    z = FALSE;
    if (idx == -1) {
        return z;
    }
    e = &sFishCatches[idx];
    e->state = 1;
    e->mode = 1;
    pv = &self->position;
    q = &e->arcPointA;
    q->x = pv->x;
    q->y = pv->y;
    q->z = pv->z;
    e->shadowIndex = k;
    h = self->fishId;
    e->fishId = h;
    sel = self->sizeClass;
    loc.x = pv->x;
    loc.y = pv->y;
    loc.z = pv->z;
    switch (sel) {
    case 0:
        Effect_Create(0x12, &loc, NULL, NULL);
        break;
    case 1:
        Effect_Create(0x13, &loc, NULL, NULL);
        break;
    case 2:
        Effect_Create(0x14, &loc, NULL, NULL);
        break;
    case 3:
        Effect_Create(0x15, &loc, NULL, NULL);
        break;
    case 4:
        Effect_Create(0x16, &loc, NULL, NULL);
        break;
    case 5:
        Effect_Create(0x17, &loc, NULL, NULL);
        break;
    case 6:
        Effect_Create(0x19, &loc, NULL, NULL);
        break;
    case 7:
        Effect_Create(0x18, &loc, NULL, NULL);
        break;
    }
    buf[0] = 0;
    buf[1] = h;
    NetBuf_PackPair20(tmp, self->position.x, self->position.z);
    MI_CpuCopy8(tmp, &buf[2], 5);
    s = gCommManager;
    s->beginRecord();
    s->writeRecord((u8 *)(buf), 7);
    s->endRecord(0x2a, 4);
    return TRUE;
}


extern "C" BOOL FishShadow_LoseBobber(Obj_f6 *self)
{
    FishBobber *p = self->bobber;
    if (p == NULL) {
        return FALSE;
    }
    self->biteStepTimer = 0;
    self->playerIdx = -1;
    p->setFish(NULL);
    self->bobber = 0;
    self->aiMode = 0;
    self->biteState = 7;
    self->stateTimer = 0;
    return TRUE;
}


extern "C" s32 FishShadow_GetEdgeColumn(Obj_f6 *self)
{
    s32 r = 2;
    s32 t = self->position.x >> 17;
    if (t == 0) {
        r = 0;
    } else if (t == 5) {
        r = 1;
    }
    return r;
}


extern "C" BOOL FishShadow_IsSeaNorth(Obj_f6 *self)
{
    BOOL r = FALSE;
    s32 x, y;
    V3_f6 p;
    V3_f6 *pv = &self->position;
    p.x = pv->x;
    p.y = pv->y;
    p.z = pv->z;
    p.z = p.z - 0x2000;
    FieldPos_ToUnit(&x, &y, &p);
    if (Ground_GetWaterKind(x, y) == 1) {
        r = TRUE;
    }
    return r;
}


extern "C" s32 FishShadow_CheckWaterBounds(Obj_f6 *self)
{
    s32 r = 0;
    s32 x, y;
    FieldPos_ToUnit(&x, &y, &self->position);
    switch (self->habitat) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (FishShadow_IsProbeOutOfWater(self)) {
            COPY();
            r = 1;
        } else if (Ground_GetWaterKind(x, y) == 1) {
            COPY();
            r = 3;
        }
        break;
    case 4:
        goto dflt;
    case 5:
    case 6: {
        s32 t = FishShadow_GetEdgeColumn(self);
        if (t == 0) {
            r = 6;
        } else if (t == 1) {
            r = 7;
        } else if (FishShadow_IsProbeOutOfWater(self)) {
            COPY();
            r = 2;
        } else if (Ground_GetWaterKind(x, y) != 1) {
            COPY();
            r = 4;
        } else if (FishShadow_IsSeaNorth(self)) {
            r = 5;
        }
        break;
    }
    default:
    dflt:
        if (Ground_GetWaterKind(x, y) == 2) {
            if (FishShadow_IsProbeOutOfWater(self)) {
                COPY();
                r = 1;
            }
        } else if (Ground_GetWaterKind(x, y) == 1) {
            s32 t = FishShadow_GetEdgeColumn(self);
            if (t == 0) {
                r = 6;
            } else if (t == 1) {
                r = 7;
            } else if (FishShadow_IsProbeOutOfWater(self)) {
                COPY();
                r = 2;
            } else if (FishShadow_IsSeaNorth(self)) {
                r = 5;
            }
        } else {
            COPY();
            r = 1;
        }
        break;
    }
    return r;
}


extern "C" BOOL FishShadow_IsProbeOutOfWater(Obj_f6 *self)
{
    BOOL r = TRUE;
    s32 a, b, c;
    FishShadow_GetProbeGroundKinds(self, &a, &b, &c);
    switch (self->habitat) {
    case 0:
    case 1:
    case 2:
    case 3:
        if ((a >= 0xb && a <= 0x12) || a == 7 || a == 0x14) {
            if ((b >= 0xb && b <= 0x12) || b == 7 || b == 0x14) {
                if ((c >= 0xb && c <= 0x12) || c == 7 || c == 0x14) {
                    r = FALSE;
                }
            }
        }
        break;
    case 4:
        goto dflt;
    case 5:
    case 6:
        if (a == 8 || a == 0x17) {
            if (b == 8 || b == 0x17) {
                if (c == 8 || c == 0x17) {
                    r = FALSE;
                }
            }
        }
        break;
    default:
    dflt:
        if ((a >= 0xb && a <= 0x12) || a == 8 || a == 7 || a == 0x14) {
            if ((b >= 0xb && b <= 0x12) || b == 8 || b == 7 || b == 0x14) {
                if ((c >= 0xb && c <= 0x12) || c == 8 || c == 7 || c == 0x14) {
                    r = FALSE;
                }
            }
        }
        break;
    }
    return r;
}


extern "C" void FishShadow_GetProbeGroundKinds(Obj_f6 *self, s32 *o1, s32 *o2, s32 *o3)
{
    V3_f6 v0, v1, v2;
    GroundInfo g0, g1, g2;
    s16 ang;
    s32 r;
    s32 z0, z1, z2;
    s32 i0, i1, i2;

    ang = self->rotY;
    i0 = ((u16)(s16)(ang + 0x2000) >> 4) * 2;
    r = sFishSizeClassParams[self->sizeClass].g;
    z0 = self->position.z + (r * data_02135f44[i0 + 1]) / 100;
    v0.x = self->position.x + (r * data_02135f44[i0]) / 100;
    v0.y = -0x1333;
    v0.z = z0;
    i1 = ((u16)(s16)(ang - 0x2000) >> 4) * 2;
    z1 = self->position.z + (r * data_02135f44[i1 + 1]) / 100;
    v1.x = self->position.x + (r * data_02135f44[i1]) / 100;
    v1.y = -0x1333;
    v1.z = z1;
    i2 = ((u16)self->rotY >> 4) * 2;
    z2 = self->position.z + (r * data_02135f44[i2 + 1]) / 100;
    v2.x = self->position.x + (r * data_02135f44[i2]) / 100;
    v2.y = -0x1333;
    v2.z = z2;
    g0.initAtPos(&v0, 0, 0);
    g1.initAtPos(&v1, 0, 0);
    g2.initAtPos(&v2, 0, 0);
    *o1 = g0.attr;
    *o2 = g1.attr;
    *o3 = g2.attr;
}


extern "C" void FishCroak_Update(FishCroak *s, Obj_f6 *o)
{
    switch (s->b3) {
    case 0:
        FishCroak_Idle(s, o);
        break;
    case 1:
        FishCroak_Listen(s, o);
        break;
    case 2:
        FishCroak_Croak(s, o);
        break;
    }
}


extern "C" void FishCroak_Idle(FishCroak *s, Obj_f6 *o)
{
    VecFx32 *t;
    if (s->b0 != 0) {
        s->b0 = s->b0 - 3;
        if (s->b0 < 0xa) {
            s->b0 = 0;
        }
    }
    if (s->b2 != 0) {
        s->b2 = s->b2 - 1;
    }
    t = (VecFx32 *)PlayerActor_GetBodyPos(0);
    if (t != NULL) {
        if (Vec_DistXZ(t, &o->position) < 0x8000) {
            s->b3 = 1;
        }
    }
}


extern "C" void FishCroak_Listen(FishCroak *s, Obj_f6 *o)
{
    VecFx32 *t;
    if (s->b2 != 0) {
        s->b2 = s->b2 - 1;
    }
    t = (VecFx32 *)PlayerActor_GetBodyPos(0);
    if (t != NULL) {
        if (Vec_DistXZ(t, &o->position) >= 0x8000) {
            s->b3 = 0;
            return;
        }
    }
    if (FieldFish_IsPlayerRunning(0)) {
        s->b0 = s->b0 + 1;
        if (s->b0 >= 0xc8) {
            s->b0 = 0xc8;
        }
    } else {
        if (s->b0 != 0) {
            s->b0 = s->b0 - 1;
        }
        if (s->b0 <= 0x96) {
            if (s->b2 == 0) {
                s->b1 = FieldFish_RandRange(0x3c, 0x8c);
                s->b3 = 2;
            }
        }
    }
}


extern "C" void FishCroak_Croak(FishCroak *s, Obj_f6 *o)
{
    if (s->b1 != 0) {
        s->b1 = s->b1 - 1;
        o->envChannel.callRequest(0x82f);
    } else {
        s->b2 = FieldFish_RandRange(0x14, 0x50);
        s->b3 = 1;
    }
    if (FieldFish_IsPlayerRunning(0)) {
        s->b2 = FieldFish_RandRange(0x14, 0x28);
        s->b3 = 1;
        s->b1 = 0;
        s->b0 = s->b0 + 1;
        if (s->b0 >= 0xc8) {
            s->b0 = 0xc8;
        }
    } else if (s->b0 != 0) {
        s->b0 = s->b0 - 1;
    }
}


extern "C" void FishCroak_Clear(FishCroak *s)
{
    s->b0 = 0;
    s->b1 = 0;
    s->b2 = 0;
    s->b3 = 0;
}


extern "C" void FishShadow_ResetCroak(Obj_f6 *self)
{
    FishCroak_Clear(&self->croak);
}


extern "C" void FishCatch_Update(FishCatch *self, s32 arg)
{
    V3_f6 a, b;
    if (BottleThrow_IsActive(arg)) {
        V3_f6 *p = BottleThrow_GetPos(arg);
        a.x = p->x;
        a.y = p->y;
        a.z = p->z;
        b = a;
        self->seEmitter.callUpdateRelative(&a);
        if (BottleThrow_GetSeCue(arg) == 1) {
            Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e0, 0x7f, 0);
        } else if (BottleThrow_GetSeCue(arg) == 2) {
            Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e1, 0x7f, 0);
            b.y = data_020c7c1c;
            Effect_Create(0x15, &b, NULL, NULL);
        }
    } else {
        a.x = self->position.x;
        a.y = self->position.y;
        a.z = self->position.z;
        self->seEmitter.callUpdateRelative(&a);
    }
    if (sFishCatchStates[self->state].f) {
        (self->*sFishCatchStates[self->state].f)(arg);
    }
    {
        CommManager *s = gCommManager;
        if (s->isOnline()) {
            if (s->isMyAid(arg) == 0) {
                if (self->state == 4) {
                    FishDisplay_PostRequest(arg, 8, -1, 0, 0);
                }
            }
        }
    }
}


extern "C" s32 FishCatch_StateIdle()
{
    return 1;
}


extern "C" BOOL FishCatch_StateStart(Self_f5 *self, u32 a) {
    if (self->displayHandle != -1) {
        return FALSE;
    }
    self->displayHandle = FishDisplay_Acquire();
    if (self->mode != 5) {
        Fish_GetDisplayScale(&self->scale, self->fishId);
    }
    if (self->mode == 1) {
        if (!FishCatch_SetupLine(self, a)) {
            return FALSE;
        }
    } else if (self->mode == 2) {
        if (!FishCatch_SetupLine(self, a)) {
            return FALSE;
        }
        Ent_f5 *e = (Ent_f5 *)PlayerActor_GetActor(a);
        if (e != NULL) {
            u32 f = e->actorFlags;
            if (Unk_ov003_02222490_Bit(f, 4) && Unk_ov003_02222490_Bit(f, 2)) {
                self->state = 2;
                return TRUE;
            }
        }
    }
    self->state = 3;
    return TRUE;
}


extern "C" BOOL FishCatch_SetupLine(Self_f5 *self, u32 a) {
    struct {
        VecFx32Ctor dead;
        T48_f5 t;
        V3_f5 d, w;
        T48_f5 blk;
        V3_f5 y, z;
    } l;
    if (a >= 4) {
        self->state = 4;
        return FALSE;
    }
    if (PlayerActor_GetCharacter(a) == NULL) {
        self->state = 4;
        return FALSE;
    }
    PlayerActor_GetHandMtx(&l.blk, a);
    l.t = l.blk;
    l.d.x = 0x800;
    l.d.y = 0;
    l.d.z = 0;
    PlayerActor_ApplyHoldOffset(&l.t, &l.d);
    l.w.x = l.t.m[9];
    l.w.y = l.t.m[10];
    l.w.z = l.t.m[11];
    WorldCurve_FromCurved(&l.w, &l.w);
    CP(l.dead, l.w);
    CP(l.y, l.w);
    CP(l.z, self->arcPointA);
    Fishing_CalcArcSpeed(&l.y, &l.z, &self->gravity, &self->ySpeed, 3);
    CP(self->position, self->arcPointA);
    return TRUE;
}


extern "C" BOOL FishCatch_StateHold(Self_f5 *self, u32 a) {
    BOOL r = FALSE;
    struct Pad {
        s32 v[3];
        Pad() {}
        ~Pad() {}
    } pad;
    Ent_f5 *e = (Ent_f5 *)PlayerActor_GetCharacter(a);
    if (e == NULL) {
        self->state = 4;
        return r;
    }
    u32 f = e->actorFlags;
    if (Unk_ov003_02222490_Bit(f, 4) && Unk_ov003_02222490_Bit(f, 2)) {
        V3_f5 v;
        V3_f5 *pv = &e->position;
        v.x = pv->x;
        v.y = pv->y;
        v.z = pv->z;
        CP(self->position, v);
        CP(self->arcPointB, v);
    } else {
        r = TRUE;
        self->isLanded = r;
        self->state = 3;
    }
    return r;
}


extern "C" BOOL FishCatch_StateUpdate(Self_f5 *self, u32 a) {
    s32 r5 = 0x1e;
    BOOL r6 = FALSE;
    switch (self->mode) {
    case 0:
        break;
    case 1:
        FishCatch_UpdateLocalReel(self, a);
        r6 = TRUE;
        break;
    case 2:
        FishCatch_UpdateRemoteReel(self, a);
        r6 = TRUE;
        break;
    case 3:
        FishCatch_UpdateArc(self, TRUE);
        break;
    case 4:
        FishCatch_UpdateArc(self, r6);
        break;
    case 5: {
        Ent_f5 *e = (Ent_f5 *)PlayerActor_GetActor(a);
        if (e == NULL) {
            self->state = 4;
            return r6;
        }
        FishCatch_UpdateSwimAway(self, &e->position);
        r5 = r5 - self->moveFrame;
        if (r5 < 1) {
            r5 = 1;
        }
        break;
    }
    }
    FishDisplay_SetEntry(self->displayHandle, self->fishId, &self->position, &self->scale, self->rotX, self->rotY, self->rotZ, 1, r6, r5);
    return TRUE;
}


extern "C" BOOL FishCatch_UpdateLocalReel(Self_f5 *self, u32 a) {
    BOOL r = FALSE;
    if (self->isLanded == 0) {
        Ent_f5 *e = (Ent_f5 *)PlayerActor_GetCharacter(a);
        if (e == NULL) {
            self->state = 4;
            return r;
        }
        V3_f5 t;
        FishCatch_GetLineEnd(self, e, &t);
        r = TRUE;
        V3_f5 u;
        CP(u, t);
        if (Fishing_StepArc(&u, self->gravity, &self->position, &self->ySpeed, r)) {
            self->isLanded = r;
            CP(self->arcPointB, t);
        }
    } else if (self->storedSent == 0) {
        FishCatch_IsDisplayReady(self, a);
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishCatch_UpdateRemoteReel(Self_f5 *self, u32 a) {
    BOOL r;
    struct {
        V3_f5 t;
        T48_f5 tt;
        V3_f5 w, u;
        T48_f5 blk;
    } l;
    Ent_f5 *e = (Ent_f5 *)PlayerActor_GetCharacter(a);
    if (e == NULL) {
        self->state = 4;
        return FALSE;
    }
    if (self->isLanded == 0) {
        FishCatch_GetLineEnd(self, e, &l.t);
        r = TRUE;
        CP(l.u, l.t);
        if (Fishing_StepArc(&l.u, self->gravity, &self->position, &self->ySpeed, r)) {
            self->isLanded = r;
            CP(self->arcPointB, l.t);
        }
    } else {
        FishCatch_IsDisplayReady(self, a);
        PlayerActor_GetHandMtx(&l.blk, a);
        l.tt = l.blk;
        PlayerActor_ApplyHoldOffset(&l.tt, 0);
        l.w.x = l.tt.m[9];
        l.w.y = l.tt.m[10];
        l.w.z = l.tt.m[11];
        WorldCurve_FromCurved(&l.w, &l.w);
        CP(self->position, l.w);
        CP(self->arcPointB, l.w);
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishCatch_StateEnd(Self_f5 *self, s32 a) {
    if (self->mode == 1 || self->mode == 3) {
        FishCatch_DetachShadow(self);
    }
    FishCatch_Reset(self, a);
    return TRUE;
}


extern "C" BOOL FishCatch_DetachShadow(Self_f5 *self) {
    BOOL r = FALSE;
    s32 i = self->shadowIndex;
    if (i != -1) {
        FishShadow *p = &sFishShadows[i];
        if (p->bobber != NULL) {
            p->bobber = NULL;
        }
        p->playerIdx = -1;
        p->aiMode = 0;
        p->biteState = 0;
        r = TRUE;
    }
    return r;
}


extern "C" void FishCatch_Reset(Self_f5 *self, s32 a) {
    FishDisplay_Release(self->displayHandle);
    self->displayHandle = -1;
    self->state = 0;
    self->shadowIndex = -1;
    self->isLanded = 0;
    self->storedSent = 0;
    self->moveFrame = 0;
    self->scale.x = 0x1333;
    self->scale.y = 0x1333;
    self->scale.z = 0x1333;
    self->rotX = 0;
    self->rotY = 0;
    self->rotZ = 0;
    Effect_End(self->effectHandle);
    self->effectHandle = -1;
    if (self->swimAwayPending) {
        FishCatch_StartSwimAway(self, a);
    }
}


extern "C" void FishCatch_StartSwimAway(Self_f5 *self, s32 a) {
    self->state = 1;
    self->swimAwayPending = 0;
    const FishInfo *info = &gFishInfo[self->fishId];
    s32 t = info->sizeClass;
    self->scale.x = (sFishSizeClassParams[t].shadowScaleX << 12) / 100;
    self->scale.y = 0x1000;
    self->scale.z = (sFishSizeClassParams[t].shadowScaleZ << 12) / 100;
    self->position.y = data_020c7c1c;
    self->fishId = 0x3b;
    V3_f5 v;
    v.x = self->position.x;
    v.y = self->position.y;
    v.z = self->position.z;
    s32 *h = &self->effectHandle;
    switch (t) {
    case 0:
        Effect_Create(0x12, &v, NULL, NULL);
        *h = Effect_Create(0x1a, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e2, 0x7f, 0);
        break;
    case 1:
        Effect_Create(0x13, &v, NULL, NULL);
        *h = Effect_Create(0x1b, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e2, 0x7f, 0);
        break;
    case 2:
        Effect_Create(0x14, &v, NULL, NULL);
        *h = Effect_Create(0x1c, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e2, 0x7f, 0);
        break;
    case 3:
        Effect_Create(0x15, &v, NULL, NULL);
        *h = Effect_Create(0x1d, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e3, 0x7f, 0);
        break;
    case 4:
        Effect_Create(0x16, &v, NULL, NULL);
        *h = Effect_Create(0x1e, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e3, 0x7f, 0);
        break;
    case 5:
        Effect_Create(0x17, &v, NULL, NULL);
        *h = Effect_Create(0x1f, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e4, 0x7f, 0);
        break;
    case 6:
        Effect_Create(0x19, &v, NULL, NULL);
        *h = Effect_Create(0x21, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e4, 0x7f, 0);
        break;
    case 7:
        Effect_Create(0x18, &v, NULL, NULL);
        *h = Effect_Create(0x20, &v, NULL, NULL);
        Snd_SeEmitterPlayOneShot(&self->seEmitter, 0x7e3, 0x7f, 0);
        break;
    }
    self->mode = 5;
    CommManager *g = gCommManager;
    if (g->isOnline()) {
        if (g->isMyAid(a)) {
            FieldFish_ScareAround(&v, ((u8)sFishRodParams[0].sight[info->rodClass].dist << 12) / 10);
        }
    } else {
        FieldFish_ScareAround(&v, ((u8)sFishRodParams[0].sight[info->rodClass].dist << 12) / 10);
    }
}


extern "C" void FishCatch_UpdateArc(Self_f5 *self, BOOL flag) {
    struct {
        V3_f5 a, b, c, a2, b2, a3, b3;
    } l;
    s32 n;
    if (flag) {
        CP(l.a, self->arcPointB);
        CP(l.b, self->arcPointA);
        l.b.y = l.b.y - 0x1800;
        n = 0x14;
    } else {
        CP(l.a, self->arcPointA);
        CP(l.b, self->arcPointB);
        l.b.y = l.b.y - l.a.y;
        n = 0x14;
    }
    CP(l.c, self->position);
    CP(l.a2, l.a);
    CP(l.b2, l.b);
    if (FieldFish_HasPassed(&l.c, &l.a2, &l.b2)) {
        self->state = 4;
        self->swimAwayPending = 1;
    } else {
        CP(l.a3, l.a);
        CP(l.b3, l.b);
        if (!FieldFish_StepParabola(&self->position, &l.a3, &l.b3, self->moveFrame, 0x14cd, n)) {
            self->state = 4;
            self->swimAwayPending = 1;
        }
        self->moveFrame = self->moveFrame + 1;
    }
}


extern "C" BOOL FieldFish_StepParabola(V3_f5 *p, V3_f5 *a, V3_f5 *b, s32 n, s32 k, s32 m) {
    s32 mm, y, ang;
    volatile s32 t, d;
    if (m <= n) {
        return FALSE;
    }
    y = b->y;
    mm = m * m;
    t = DS_DIV(((k - (y >> 1)) << 3), mm);
    d = Vec_DistXZ(a, b);
    ang = FishAngleXZ(a, b);
    s32 nn = n * n;
    p->y = a->y + (n * (DS_DIV((y + ((mm * t) >> 1)), m)) - ((nn * t) >> 1));
    FieldFish_MoveXZ(p, DS_DIV(d, m), ang);
    return TRUE;
}


extern "C" BOOL FishCatch_UpdateSwimAway(Self_f5 *self, V3_f5 *p) {
    s32 c = self->moveFrame;
    s32 t = (c + 2) << 7;
    if (c == 0) {
        self->rotY = FishAngleXZ(p, &self->position);
    } else if (c >= 0x1e) {
        self->state = 4;
    }
    if (t > 0x214) {
        t = 0x214;
    }
    FieldFish_MoveXZ(&self->position, t, self->rotY);
    self->moveFrame = self->moveFrame + 1;
    V3_f5 v;
    v.x = self->position.x;
    v.y = self->position.y;
    v.z = self->position.z;
    v.y = data_020c7c1c;
    Effect_SetPosition(self->effectHandle, &v, 0, 0);
    return TRUE;
}


extern "C" void FishCatch_GetLineEnd(Self_f5 *self, Ent_f5 *ent, V3_f5 *out) {
    if (ent->getHeldItemPos((VecFx32 *)out) == 0) {
        V3_f5 *pv = &ent->position;
        out->x = pv->x;
        out->y = pv->y;
        out->z = pv->z;
    } else {
        s32 ang = Math_Atan2(self->position.x - out->x, self->position.z - out->z);
        s32 idx = ((u16)ang >> 4) * 2;
        out->x += func_01ffcb0c(0x4cd, data_02135f44[idx]);
        out->z += func_01ffcb0c(0x4cd, data_02135f44[idx + 1]);
    }
}


extern "C" void FishCatch_PollRemote(O_f3 *a) {
    s32 i = 0;
    CommManager *net = gCommManager;
    volatile s32 zero = 0;
    s32 m1 = -1;
    s32 z = 0;
    for (; i < 4; i++) {
        if (net->isMyAid(i) == 0) {
            u32 t = FishDisplay_GetRequestKind(i);
            if (t == 9) {
                t = 1;
            }
            switch (t) {
            case 0:
                FishCatch_StartRemoteHook(a, i);
                break;
            case 6:
                sFishCatches[i].isLanded = 1;
                FishCatch_StartRemoteHook(a, i);
                break;
            case 1:
                if (FishCatch_EndRemote(a, i)) {
                    FishDisplay_PostRequest(i, 8, m1, z, z);
                } else {
                    sFishCatches[i].state = 4;
                }
                break;
            case 2:
                if (FishCatch_StartRemoteLift(a, i)) {
                    FishDisplay_PostRequest(i, 8, m1, zero, zero);
                } else {
                    sFishCatches[i].state = 4;
                }
                break;
            case 3:
            case 4:
            case 5:
            case 7:
            case 8:
            case 9:
                break;
            }
        }
    }
}


extern "C" void FishCatch_StartRemoteHook(O_f3 *a, s32 idx) {
    u32 r = FishDisplay_GetRequestFish(idx);
    VecFx32 v;
    v.y = -0x1333;
    if (FishDisplay_GetRequestPos((u32 *)&v.x, (u32 *)&v.z, idx)) {
        if (FishCatch_StartRemoteReel(a, idx, r, &v)) {
            FishDisplay_PostRequest(idx, 3, -1, 0, 0);
        } else {
            FishCatch *e = sFishCatches + idx;
            e->state = 4;
        }
    }
}


extern "C" BOOL FishCatch_EndRemote(O_f3 *a, u8 idx) {
    if (idx >= 4) {
        return FALSE;
    }
    FishCatch *e = sFishCatches + idx;
    e->state = 4;
    return TRUE;
}


extern "C" BOOL FishCatch_StartRemoteReel(O_f3 *a, u8 idx, u32 v, VecFx32 *p) {
    if (idx >= 4) {
        return FALSE;
    }
    FishCatch *e = &sFishCatches[idx];
    if (e->state != 0) {
        return FALSE;
    }
    VecFx32 *d = &e->arcPointA;
    d->x = p->x;
    d->y = p->y;
    d->z = p->z;
    s32 *p90 = &e->fishId;
    *p90 = v;
    e->state = 1;
    e->mode = 2;
    return TRUE;
}


extern "C" BOOL FishCatch_StartRemoteLift(O_f3 *a, u8 idx) {
    if (idx >= 4) {
        return FALSE;
    }
    FishCatch *e = &sFishCatches[idx];
    volatile VecFx32 v;
    VecFx32 *pv = &e->arcPointA;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    s32 st = e->state;
    if (st == 3) {
        if (FishCatch_StartLift(idx, 0) == 0) {
            e->state = 4;
            return FALSE;
        }
    } else if (st == 0) {
        if (FishCatch_StartLift(idx, 1) == 0) {
            e->state = 4;
            return FALSE;
        }
    } else if (st == 2) {
        e->state = 3;
        if (FishCatch_StartLift(idx, 0) == 0) {
            e->state = 4;
            return FALSE;
        }
    }
    return TRUE;
}


FishShadow::FishShadow()
{
    spawnBlock.x = 0;
    spawnBlock.y = 0;
    FishCroak_Init(&croak);
    fishId = -1;
    despawnTimer = -1;
    state = 0;
    spawnState = 2;
    appearCount = 0;
    effectHandle = -1;
    playerIdx = -1;
    bobber = NULL;
    biteState = 0;
    aiMode = 0;
    position.x = 0x1000;
    position.y = 0x1000;
    position.z = 0x1000;
}


FishShadow::~FishShadow()
{
    FishCroak_Destroy(&croak);
}


FishFinModel::FishFinModel()
{
    attachState = 0;
    pooledModel.reset();
}


FishFinModel::~FishFinModel()
{
}


extern "C" void FishCroak_Init(FishCroak *p) {
    p->b0 = 0;
    p->b1 = 0;
    p->b2 = 0;
    p->b3 = 0;
}


extern "C" void FishCroak_Destroy(FishCroak *p) {
}


FishCatch::FishCatch()
{
    FishCatch *a = this;
    a->state = 0;
    a->displayHandle = -1;
    a->mode = 0;
    a->shadowIndex = -1;
    a->isLanded = 0;
    a->moveFrame = 0;
    a->scale.x = 0x1333;
    a->scale.y = 0x1333;
    a->scale.z = 0x1333;
    a->swimAwayPending = 0;
    a->rotX = 0;
    a->rotY = 0;
    a->rotZ = 0;
    a->effectHandle = -1;
    a->storedSent = 0;
    a->position.x = 0x1000;
    a->position.y = 0x1000;
    a->position.z = 0x1000;
}


FishCatch::~FishCatch()
{
}


FieldFishManager::FieldFishManager() {
    shadowAnimFile = NULL;
}


FieldFishManager::~FieldFishManager() {
}


extern "C" BOOL FishShadow_SetAppearing(O_f3 *a, s32 idx) {
    BOOL r = FALSE;
    if (idx >= 0 && idx < 6) {
        FishShadow *s = sFishShadows + idx;
        s->state = 2;
        r = TRUE;
    }
    return r;
}


extern "C" void FishShadow_Despawn(O_f3 *a, s32 idx) {
    if (idx >= 0 && idx < 6) {
        FishShadow *s = &sFishShadows[idx];
        s->state = 0;
        Effect_End(s->effectHandle);
        s->effectHandle = -1;
        if (s->spawnState == 0) {
            s->spawnState = 3;
        } else if (s->spawnState == 1) {
            s->spawnState = 4;
        }
        s->spawnBlock.x = idx;
        s->spawnBlock.y = 0;
        if (s->bobber != NULL) {
            FishCatch *ent = sFishCatches + s->playerIdx;
            if (ent->state != 1) {
                s->bobber->setFish(NULL);
                s->bobber = NULL;
                s->playerIdx = -1;
                s->aiMode = 0;
            }
            s->biteState = 0;
        }
    }
}


extern "C" BOOL FishFinModel_Attach(O_f3 *a) {
    sFishFinModel.attachState = 2;
    a->finModelPool.acquire(&sFishFinModel.modelSlot.index);
    sFishFinModel.pooledModel.reset();
    return TRUE;
}


extern "C" void FishFinModel_Release(O_f3 *a) {
    sFishFinModel.attachState = 0;
    sFishFinModel.model.detachJointAnim();
    sFishFinModel.model.release();
    sFishFinModel.pooledModel.unload();
    a->finModelPool.release(&sFishFinModel.modelSlot.index);
    sFishFinModel.matAnim.anmObj = 0;
    sFishFinModel.matAnim.resMdl = 0;
}


BOOL FieldFishManager::onCreate() {
    shadowModelPool.init(6, 0, 0, 0x800, (ModelSlotAllocFunc)FishShadowHeap_Create, FishShadowHeap_Destroy);
    finModelPool.init(1, 0x400, 0x80, 0x800, (ModelSlotAllocFunc)FishFinHeap_Create, FishFinHeap_Destroy);
    shadowAnimFile = File_LoadAlloc(sFishShadowAnimPath, gCurrentHeap, 4, NULL);
    FishShadow *s = sFishShadows;
    s32 i = 0;
    s32 z = 0;
    do {
        FishShadow_LoadModel(s, shadowAnimFile, &shadowModelPool);
        if (i < 3) {
            s->spawnState = 3;
        } else if (i < 6) {
            s->spawnState = 4;
        }
        s->spawnBlock.x = i;
        s->spawnBlock.y = z;
        s->slotIndex = i;
        s->respawnTimer = i * 0x190 + 0x960;
        s->seEmitter.callInit();
        s->envChannel.callReset();
        s++;
        i++;
    } while (i < 6);
    FishCatch *q = sFishCatches;
    s32 k = 0;
    CommManager *net = gCommManager;
    for (; k < 4; k++) {
        if (net->isOnline() && !net->isMyAid(k) && FishDisplay_GetRequestKind(k) == 3) {
            FishDisplay_PostRequest(k, 6, -1, z, z);
        }
        q->seEmitter.callInit();
        q++;
    }
    return TRUE;
}


extern "C" void FishShadow_Run(O_f3 *a, FishShadow *b, s32 c) {
    VecFx32 v1;
    VecFx32 *pv = &b->position;
    v1.x = pv->x;
    v1.y = pv->y;
    v1.z = pv->z;
    b->seEmitter.callUpdateRelative(&v1);
    VecFx32 v2;
    pv = &b->position;
    v2.x = pv->x;
    v2.y = pv->y;
    v2.z = pv->z;
    b->envChannel.callUpdateRelative(&v2);
    if (sFishShadowStates[b->state].exec) {
        (a->*(sFishShadowStates[b->state].exec))(b, c);
    }
    FishShadow_TickRespawnTimer(b);
}


extern "C" void FishShadow_ChangeState(O_f3 *a, s32 idx, FishShadow *b, s32 c) {
    if (idx >= 0 && idx < 5) {
        b->state = idx;
        s32 i = *(volatile s32 *)&b->state;
        FishShadowStateEntry *e = &sFishShadowStates[i];
        if (e->enter) {
            (a->*(e->enter))(b, c);
        }
    }
}


extern "C" void FishShadow_EnterSpawn() {
}


extern "C" void FishShadow_ExecSpawn(O_f3 *a, FishShadow *b, s32 c) {
    if (a->spawnAttempted == 0) {
        u32 t = b->spawnState;
        if (t == 3) {
            if (b->aiMode == 0) {
                if (FishShadow_TrySpawn(a, b, 0) != 0) {
                    FishShadow_ChangeState(a, 1, b, c);
                }
                a->spawnAttempted = 1;
            }
        } else if (t == 4) {
            if (b->aiMode == 0) {
                if (FishShadow_TrySpawn(a, b, 1) != 0) {
                    FishShadow_ChangeState(a, 1, b, c);
                }
                a->spawnAttempted = 1;
            }
        }
    }
}


extern "C" void FishShadow_EnterWaitInView() {
}


extern "C" void FishShadow_ExecWaitInView(O_f3 *a, FishShadow *b, s32 c) {
    if (gCamera != NULL) {
        VecFx32 v;
        v = gCameraLookAt;
        if (FieldFish_IsInBox(&b->spawnPos, &v, 0xa000, 0x10000, 0xa000)) {
            FishShadow_SetAppearing(a, c);
            if (b->hasFin != 0) {
                FishFinModel_Attach(a);
            }
        }
    }
}


extern "C" void FishShadow_EnterAppear() {
}


extern "C" void FishShadow_ExecAppear(O_f3 *o, E_f3 *e) {
    s32 ang;
    V3_f3 *pv;
    if (e->hasFin != 0) {
        FishFinModel *p = &sFishFinModel;
        if (FishFinModel_Load(p, &o->finModelPool) != 0) {
            FishShadow_RunAppearAi(e);
            e->state = 3;
            e->alpha = 0x1f;
            pv = &e->position;
            ang = e->rotY;
            FieldFish_SetModelMatrix(o, pv, &e->model, ang);
            FieldFish_SetModelMatrix(o, pv, &p->model, ang);
        }
    } else {
        FishShadow_RunAppearAi(e);
        if (e->appearCount > 3 || e->moveState == 3) {
            e->state = 3;
            e->alpha = 0x1f;
            e->appearCount = 0;
            FieldFish_SetModelMatrix(o, &e->position, &e->model, e->rotY);
            if (e->fishId == 11) {
                FishShadow_ResetCroak(e);
            }
        }
    }
}


extern "C" void FishShadow_EnterOutOfView(void) {
}


extern "C" void FishShadow_ExecOutOfView(O_f3 *o, E_f3 *e, s32 idx) {
    if (gCamera != NULL) {
        V3_f3 v(gCameraLookAt.x, gCameraLookAt.y, gCameraLookAt.z);
        if (FieldFish_IsInBox(&e->position, &v, 0xa000, 0x10000, 0xa000) != 0) {
            e->state = 3;
            e->despawnTimer = -1;
        } else {
            s32 t = e->despawnTimer;
            s32 m = -1;
            if (t != m) {
                if (t == 0) {
                    if (e->hasFin != 0) {
                        FishFinModel_Release(o);
                    }
                    FishShadow_Despawn(o, idx);
                } else {
                    e->despawnTimer = t - 1;
                }
            }
        }
    }
}


extern "C" void FishShadow_EnterSwim(void) {
}


extern "C" void FishShadow_ExecSwim(O_f3 *o, E_f3 *e, s32 x) {
    FishShadow_RunAi(e);
    V3_f3 *pb = &e->prevPosition;
    V3_f3 *pa = &e->position;
    s32 t = _s32_div_f((u8)sFishSizeClassParams[e->sizeClass].c0 << 12, 10);
    Collision_Move(&e->collisionState, pa, pb, e->rotY, t, 0, 0xb);
    pb->x = e->position.x;
    pb->y = pa->y;
    pb->z = pa->z;
    V3_f3 v;
    v.x = e->position.x;
    v.y = pa->y;
    v.z = pa->z;
    v.y = -0x1333;
    FieldFish_SetModelMatrix(o, &v, &e->model, e->rotY);
    if (e->hasFin != 0) {
        FishShadow_UpdateFin(o, e);
    } else {
        e->model.stepAnim();
    }
    FishShadow_UpdateVisibility(o, e, x);
}


extern "C" void FishShadow_UpdateFin(O_f3 *o, E_f3 *e) {
    FishFinModel *p = &sFishFinModel;
    V3_f3 *pv = &e->position;
    p->position.x = pv->x;
    p->position.y = pv->y;
    p->position.z = pv->z;
    s16 ang = e->rotY;
    p->rotY = ang;
    AnimModel *q = &p->model;
    q->frameStep = e->model.frameStep;
    q->curFrame = (u32)(u16)((((u32)e->model.curFrame >> 12) & 0xffff) + 1) << 12;
    FieldFish_SetModelMatrix(o, pv, q, ang);
    e->model.stepAnim();
    q->stepAnim();
    FishFinMatAnim *r = &p->matAnim;
    r->step();
    ((G3dAnmObj *)r->anmObj)->frame = r->curFrame;
}


extern "C" void FieldFish_SetModelMatrix(O_f3 *a, VecFx32 *b, Model *dst, s32 ang) {
    V3_f3 v;
    s32 r = WorldCurve_Apply(&v, b);
    Mtx43_SetTranslate(&data_021f47e0, v.x, v.y, v.z);
    Mtx43_RotateX(&data_021f47e0, r);
    Mtx43_RotateY(&data_021f47e0, ang);
    dst->mtx = data_021f47e0;
}


BOOL FieldFishManager::onExecute() {
    O_f3 *o = this;
    E_f3 *e = sFishShadows;
    s32 i;
    for (i = 0; i < 6; e++, i++) {
        FishShadow_Run(o, e, i);
    }
    o->spawnAttempted = 0;
    FieldFishManager_UpdatePlayers(o);
    return TRUE;
}


extern "C" void FieldFishManager_UpdatePlayers(O_f3 *o) {
    if (gCommManager->isOnline() != 0) {
        FishCatch_PollRemote(o);
    }
    s32 i;
    FishCatch *p = sFishCatches;
    BottleThrow *q = sBottleThrows;
    for (i = 0; i < 4; i++) {
        FishCatch_Update(p, (u8)i);
        p++;
        BottleThrow_Run(&sBottleThrowStateOwner, q);
        q++;
    }
}


BOOL FieldFishManager::onDraw() {
    E_f3 *e = sFishShadows;
    s32 i;
    for (i = 0; i < 6; i++) {
        if (e->state == 3) {
            FishSizeClassParams *rec = &sFishSizeClassParams[e->sizeClass];
            V3_f3 v;
            v.x = _s32_div_f(rec->shadowScaleX << 12, 100);
            v.y = 0x1000;
            v.z = _s32_div_f(rec->shadowScaleZ << 12, 100);
            u8 *p0 = (u8 *)e->model.resMdl;
            u8 *b = p0 + *(s32 *)(p0 + 8);
            u8 *c = b + *(u16 *)(b + 0xa);
            NNSG3dResMatData *q = (NNSG3dResMatData *)(b + *(s32 *)(c + 8));
            s32 n = e->alpha;
            if (q != NULL && n > 0) {
                q->polyAttr = q->polyAttr & 0xffe0ffff;
                q->polyAttr = q->polyAttr | ((n & 0x1f) << 16);
            }
            e->model.drawAnimated(&v);
            if (e->hasFin != 0) {
                V3_f3 v2;
                v2.x = _s32_div_f(rec->shadowScaleX << 12, 100);
                v2.y = 0x1000;
                v2.z = _s32_div_f(rec->shadowScaleZ << 12, 100);
                sFishFinModel.model.drawAnimated(&v2);
            }
        }
        e++;
    }
    return TRUE;
}


BOOL FieldFishManager::onDelete() {
    O_f3 *o = this;
    FieldFishManager_FreeShadows(o);
    FieldFishManager_FreeCatches(o);
    FieldFishManager_ResetBottles(o);
    return TRUE;
}


extern "C" void FieldFishManager_FreeShadows(O_f3 *o) {
    BOOL f = FALSE;
    E_f3 *e = sFishShadows;
    s32 i;
    for (i = 0; i < 6; i++) {
        if (e->hasFin != 0) {
            f = TRUE;
        }
        FishShadow_Despawn(o, i);
        o->shadowModelPool.release(&e->modelSlot.index);
        e->seEmitter.callStop();
        e->envChannel.callRelease();
        e++;
    }
    Mem_Free(o->shadowAnimFile);
    o->shadowModelPool.destroy();
    if (f != FALSE) {
        FishFinModel_Release(o);
    }
    o->finModelPool.destroy();
}


extern "C" void FieldFishManager_FreeCatches(O_f3 *a) {
    FishCatch *p = sFishCatches;
    s32 i;
    for (i = 0; i < 4; i++) {
        FishCatch_StateEnd(p, (u8)i);
        p->seEmitter.callStop();
        p++;
    }
}


extern "C" void FieldFishManager_ResetBottles(O_f3 *a) {
    BottleThrow *p = sBottleThrows;
    s32 i;
    for (i = 0; i < 4; i++) {
        p->state = 0;
        p->stateTimer = 0;
        p++;
    }
}


extern "C" BOOL FieldFish_ScareAround(VecFx32 *a, s32 b) {
    s32 i;
    E_f3 *e;
    BOOL r = FALSE;
    e = sFishShadows;
    i = 0;
    for (; i < 6; i++) {
        V3_f3 *pv = &e->position;
        V3_f3 v = *pv;
        if (Vec_DistXZ(&v, a) <= b) {
            if (FishShadow_TryFlee(e, a) != 0) {
                r = TRUE;
            }
        }
        e++;
    }
    return r;
}


extern "C" void FishShadow_UpdateVisibility(O_f3 *o, E_f3 *e, s32 idx) {
    FishShadow_UpdateFade(o, e, idx);
    FishShadow_CheckOffscreen(o, e, idx);
}


extern "C" void FishShadow_UpdateFade(O_f3 *o, E_f3 *e, s32 idx) {
    u32 t = e->alpha;
    if (t == 0x1f) {
        FishShadow_CheckPlayerScare(o, e);
    } else if (t != 0x1f) {
        if (e->hasFin == 0) {
            e->alpha = t - 1;
        }
    }
    if (e->alpha <= 1) {
        e->alpha = 0x1f;
        if (FishShadow_CheckReelResult(e) == 2) {
            if (e->hasFin != 0) {
                FishFinModel_Release(o);
            }
        }
        FishShadow_Despawn(o, idx);
    }
}


extern "C" BOOL FishShadow_CheckPlayerScare(O_f3 *a, E_f3 *e) {
    BOOL r = FALSE;
    if (FieldFish_IsPlayerApproaching(a, 4, e) != 0) {
        VecFx32 *t = (VecFx32 *)PlayerActor_GetBodyPos(4);
        if (t == NULL) {
            return r;
        }
        FishShadow_TryFlee(e, t);
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FieldFish_IsPlayerApproaching(O_f3 *a, s32 b, E_f3 *e) {
    BOOL r = FALSE;
    if (FieldFish_IsPlayerNear(a, &e->position, b) != 0) {
        if (PlayerActor_TestSlotFlag9(b) != 0) {
            r = TRUE;
        } else if (FieldFish_IsPlayerRunning(b) != 0) {
            u8 *pc = &e->scareDelay;
            u32 t = *pc;
            if (t != 0) {
                *pc = t - 1;
            } else {
                r = TRUE;
            }
        } else {
            e->scareDelay = 6;
        }
    } else {
        e->scareDelay = 6;
    }
    return r;
}


extern "C" BOOL FishShadow_TryFlee(E_f3 *e, VecFx32 *a) {
    BOOL r = FALSE;
    if (e == NULL) {
        return r;
    }
    if (e->aiMode == 1) {
        return r;
    }
    if (FishShadow_StartFlee(e, a) != 0) {
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishShadow_StartFlee(E_f3 *e, VecFx32 *a) {
    if (e == NULL) {
        return FALSE;
    }
    if (e->moveState == 5 || e->biteState == 6 || e->state != 3) {
        return FALSE;
    }
    if (e->aiMode == 0) {
        e->moveState = 5;
    } else {
        e->biteState = 6;
    }
    e->alpha = 0x1e;
    e->stateTimer = 0;
    u16 *pa = (u16 *)&e->rotY;
    V3_f3 *pv = &e->position;
    V3_f3 v = *pv;
    if (e->hasFin != 0) {
        *pa = 0;
    } else {
        *pa = FishAngleXZ(a, &v);
    }
    u32 k = e->sizeClass;
    s32 *pr = &e->effectHandle;
    V3_f3 w = v;
    w.y = data_020c7c1c;
    switch (k) {
    case 0: *pr = Effect_Create(0x1a, &w, NULL, NULL); break;
    case 1: *pr = Effect_Create(0x1b, &w, NULL, NULL); break;
    case 2: *pr = Effect_Create(0x1c, &w, NULL, NULL); break;
    case 3: *pr = Effect_Create(0x1d, &w, NULL, NULL); break;
    case 4: *pr = Effect_Create(0x1e, &w, NULL, NULL); break;
    case 5: *pr = Effect_Create(0x1f, &w, NULL, NULL); break;
    case 6: *pr = Effect_Create(0x21, &w, NULL, NULL); break;
    case 7: *pr = Effect_Create(0x20, &w, NULL, NULL); break;
    }
    return TRUE;
}


extern "C" void FishShadow_CheckOffscreen(O_f3 *o, E_f3 *e, s32 idx) {
    if (e->aiMode == 0 || e->biteState == 6) {
        if (gCamera != NULL) {
            V3_f3 v(gCameraLookAt.x, gCameraLookAt.y, gCameraLookAt.z);
            if (FieldFish_IsInBox(&e->position, &v, 0xa000, 0x10000, 0xa000) == 0) {
                if (e->moveState == 5 || e->biteState == 6) {
                    if (e->hasFin != 0) {
                        FishFinModel_Release(o);
                    }
                    FishShadow_Despawn(o, idx);
                } else {
                    if ((u32)(e->habitat - 4) <= 2) {
                        if (FishShadow_IsSeaNorth(e) != 0) {
                            e->despawnTimer = 0x12c;
                        } else {
                            e->despawnTimer = 0x4b0;
                        }
                    } else {
                        e->despawnTimer = 0x4b0;
                    }
                    e->state = 4;
                }
            }
        }
    }
}


extern "C" void FieldWater_ApplyFlow(VecFx32 *p, s32 b) {
    GroundInfoBase buf;
    static_cast<GroundInfo *>(&buf)->initAtPos(p, 0, 0);
    p->x += func_01ffcb0c(b, buf.flowDir);
    p->z += func_01ffcb0c(b, buf.flowDirZ);
    GroundInfo_Destruct(&buf);
}


extern "C" BOOL FieldFish_IsPlayerRunning(s32 idx) {
    BOOL r = FALSE;
    Actor *o = (Actor *)PlayerActor_GetActor(idx);
    if (o != NULL) {
        if (o->speed > 0x548) {
            r = TRUE;
        }
    }
    return r;
}


extern "C" BOOL FieldFish_IsPlayerNear(O_f3 *self, VecFx32 *b, s32 idx) {
    Actor *o = (Actor *)PlayerActor_GetActor(idx);
    if (o == NULL) {
        return FALSE;
    }
    if (Vec_DistSqXZ(&o->position, b) <= 0x135c3) {
        return TRUE;
    }
    return FALSE;
}


extern "C" BOOL FishShadow_TrySpawn(O_f3 *self, FishShadow *e, s32 flag) {
    BOOL r = FALSE;
    s32 a = -1, b = -1;
    Vec2 cd;
    cd.x = -1;
    cd.y = -1;
    s32 x, y;
    VecFx32 v;
    s32 fl;
    switch (flag) {
    case 0:
        fl = 0;
        break;
    default:
        fl = 1;
        break;
    }
    if (FishTable_PickNow(&x, &y, fl)) {
        if (FieldFish_PickSpawnUnit(self, &a, &b, &cd.x, &cd.y, y, flag, e)) {
            if (FishShadow_CanSpawnFish(self, e, x)) {
                FieldPos_FromUnitCenter(&v, a, b);
                v.y = -0x1333;
                s32 t = x;
                e->fishId = t;
                e->hasFin = (u32)(t - 0x34) <= 2 ? 1 : 0;
                e->habitat = y;
                e->sizeClass = gFishInfo[x].sizeClass;
                e->rotY = -0x8000;
                e->spawnPos.x = v.x;
                e->spawnPos.y = v.y;
                e->spawnPos.z = v.z;
                e->spawnState = flag;
                r = TRUE;
                e->state = r;
                e->moveState = 0;
                VecFx32 *pv = &e->prevPosition;
                *pv = v;
                s32 db = cd.y;
                Vec2 *pp = &e->spawnBlock;
                pp->x = cd.x;
                pp->y = db;
                e->despawnTimer = -1;
            }
        } else if (flag == 0) {
            e->spawnState = 3;
        } else if (flag == 1) {
            e->spawnState = 4;
        }
    } else if (flag == 0) {
        e->spawnState = 5;
    } else if (flag == 1) {
        e->spawnState = 6;
    }
    return r;
}


extern "C" BOOL FieldFish_CollectHabitatBlocks(O_f3 *self, u8 *out, s32 *cnt, s32 mode) {
    BOOL result = FALSE;
    BlockMap *g = gSceneBlockMap;
    if (g != NULL) {
        s32 x, y;
        for (x = 1; x < g->height - 1; x++) {
            for (y = 1; y < g->width - 1; y++) {
                MapBlock *c;
                if ((u32)x < (u32)g->width && (u32)y < (u32)g->height && g->blocks != NULL) {
                    c = &((MapBlock *)g->blocks)[y * g->width + x];
                } else {
                    c = NULL;
                }
                if (c == NULL) {
                    continue;
                }
                switch (mode) {
                case 6:
                    if ((MapBlock_GetAttr(c) & 8) != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                case 0:
                    if ((MapBlock_GetAttr(c) & 0x7f000) != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                case 1:
                    if ((MapBlock_GetAttr(c) & 0x100) != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                case 2:
                    if ((MapBlock_GetAttr(c) & 0x80000) != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                case 3:
                    if (((MapBlockAcre *)c)->hasPond() != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                case 4: {
                    u32 t = MapBlock_GetAttr(c);
                    if ((t & 0x7f000) != 0 && (t & 8) != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                }
                case 5:
                    if ((MapBlock_GetAttr(c) & 8) != 0) {
                        out[*cnt * 2] = x;
                        (&out[*cnt * 2])[1] = y;
                        (*cnt)++;
                    }
                    break;
                }
            }
        }
    }
    if (*cnt > 0) {
        result = TRUE;
    }
    return result;
}


extern "C" BOOL FieldFish_PickSpawnUnit(O_f3 *self, s32 *ox, s32 *oz, s32 *a3, s32 *a4, s32 mode, s32 flag, FishShadow *e) {
    s32 z = 0;
    s32 cnt = z;
    s32 sx, sz;
    u8 grid[0x20];
    VecFx32 v44;
    VecFx32 v50;
    VecFx32 v5c;
    u8 cand[0x204];
    s32 x, y;
    if (gCamera == NULL) {
        return z;
    }
    v44 = gCameraLookAt;
    FieldPos_SnapToUnitCenter(&v50, &v44);
    if (FieldFish_CollectHabitatBlocks(self, grid, &cnt, mode) == 0) {
        return z;
    }
    s32 k = FieldFish_RandRange(z, (u16)cnt);
    s32 k2 = k * 2;
    *a3 = ((s8 *)grid)[k2];
    *a4 = ((s8 *)&grid[1])[k2];
    s32 ax = *a3;
    s32 az = *a4;
    if (flag == 0) {
        FishShadow *p;
        s32 i;
        p = sFishShadows;
        for (i = z; i < 3; p++, i++) {
            if (e != p) {
                Vec2 *q = &p->spawnBlock;
                if (ax == p->spawnBlock.x && az == q->y) {
                    return FALSE;
                }
            }
        }
    } else if (flag == 1) {
        FishShadow *p;
        s32 i;
        p = &sFishShadows[3];
        for (i = 3; i < 6; p++, i++) {
            if (e != p) {
                Vec2 *q = &p->spawnBlock;
                if (ax == p->spawnBlock.x && az == q->y) {
                    return FALSE;
                }
            }
        }
    }
    FieldUnit_FromBlockUnit(&sx, &sz, ax, az, 0, 0);
    s32 xlim = sx + 0x10;
    s32 zlim = sz + 0x10;
    for (x = sx; x < xlim; x++) {
        for (y = sz; y < zlim; y++) {
            switch (mode) {
            case 5:
            case 6:
                if (Ground_GetWaterKind(x, y) == 1) {
                    cand[z * 2] = x;
                    (&cand[z * 2])[1] = y;
                    z++;
                }
                break;
            case 0:
            case 1:
                if (Ground_GetWaterKind(x, y) == 2) {
                    cand[z * 2] = x;
                    (&cand[z * 2])[1] = y;
                    z++;
                }
                break;
            case 2:
                if (y < sz + 3) {
                    if (Ground_GetWaterKind(x, y) == 2) {
                        cand[z * 2] = x;
                        (&cand[z * 2])[1] = y;
                        z++;
                    }
                }
                break;
            case 3:
                if (Ground_IsPond(x, y) != 0) {
                    cand[z * 2] = x;
                    (&cand[z * 2])[1] = y;
                    z++;
                }
                break;
            case 4:
                if (Ground_GetWaterKind(x, y) == 2 || Ground_GetWaterKind(x, y) == 1) {
                    cand[z * 2] = x;
                    (&cand[z * 2])[1] = y;
                    z++;
                }
                break;
            }
        }
    }
    if (z == 0) {
        *ox = -1;
        *oz = -1;
        return FALSE;
    }
    s32 kk = (s16)FieldFish_RandRange(0, (u16)z) * 2;
    s8 *cq = (s8 *)&cand[1];
    s32 rx, ry;
    ry = cq[kk];
    rx = ((s8 *)cand)[kk];
    FieldPos_FromUnitCenter(&v5c, rx, ry);
    if (FieldFish_IsInBox(&v5c, &v50, 0xa000, 0x10000, 0xa000)) {
        *ox = -1;
        *oz = -1;
        return FALSE;
    }
    *ox = rx;
    *oz = ry;
    return TRUE;
}


extern "C" BOOL FishShadow_CanSpawnFish(O_f3 *self, FishShadow *e, s32 id) {
    BOOL ok = Unk_ov003_022203f8_Chk(id);
    if (ok) {
        if (PlayerActor_GetActor(4) == NULL) {
            return FALSE;
        }
        s32 i;
        FishShadow *p;
        p = &sFishShadows[3];
        i = 3;
        for (; i < 6; p++, i++) {
            if (e != p && p->hasFin != 0) {
                return FALSE;
            }
        }
    } else if (id == 0x37) {
        if (FieldFish_IsRainOrSnow(self) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}


extern "C" BOOL FieldFish_IsRainOrSnow(O_f3 *self) {
    BOOL r = FALSE;
    u32 t = Weather_GetFallingPrecip() - 1;
    if (t <= 1) {
        r = TRUE;
    }
    return r;
}


extern "C" void FishShadow_TickRespawnTimer(FishShadow *self) {
    if (Math_CountDownU16(&self->respawnTimer) == 0) {
        if ((u32)self->state <= 1) {
            self->state = 0;
            u32 b = self->slotIndex;
            if (b < 3) {
                self->spawnState = 3;
            } else if (b < 6) {
                self->spawnState = 4;
            }
        }
        self->respawnTimer = 0x960;
    }
}


extern "C" BOOL FieldFish_IsInBox(VecFx32 *a, VecFx32 *b, s32 c, s32 d, s32 e) {
    BOOL r = FALSE;
    s32 dx = b->x - a->x;
    if (dx < 0) {
        dx = -dx;
    }
    if (dx > c) {
        return FALSE;
    }
    s32 az = a->z;
    s32 bz = b->z;
    s32 dz = bz - az;
    if (dz >= 0) {
        if (dz <= d) {
            r = TRUE;
        }
    } else {
        if (az - bz <= e) {
            r = TRUE;
        }
    }
    return r;
}


extern "C" BOOL FieldFish_HasPassed(VecFx32 *a, VecFx32 *b, VecFx32 *c) {
    if (FieldFish_HasPassed1D(a->x, b->x, c->x)) {
        if (FieldFish_HasPassed1D(a->z, b->z, c->z)) {
            return TRUE;
        }
    }
    return FALSE;
}


extern "C" BOOL FieldFish_HasPassed1D(s32 a, s32 b, s32 c) {
    BOOL r = FALSE;
    a = a - b;
    if (a < 0) {
        a = -a;
    }
    b = c - b;
    if (b < 0) {
        b = -b;
    }
    if (a >= b) {
        r = TRUE;
    }
    return r;
}


extern "C" s32 FieldFish_RandRange(s32 a, u16 b) {
    return a + Random_GlobalBelow(b - a);
}


extern "C" s32 FieldFish_RandRangeSigned(s32 a, u16 b) {
    s32 r = FieldFish_RandRange(a, b);
    if (Random_GlobalBelow(2) == 0) {
        r *= -1;
    }
    return r;
}


extern "C" BOOL FishCatch_GetReelTarget(VecFx32 *out, s32 idx) {
    BOOL r = FALSE;
    if (idx < 0 || idx >= 4) {
        return FALSE;
    }
    FishCatch *rec = &sFishCatches[idx];
    if (rec->mode == 1) {
        VecFx32 *pv = &rec->arcPointA;
        *out = *pv;
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishCatch_StartRelease(s32 idx, u16 id0, VecFx32 *pos) {
    volatile u16 id = id0;
    BOOL ok = FALSE;
    u32 v0 = id;
    u32 v1 = id;
    if (v1 >= 0x12e8 && v0 <= 0x131f) {
        ok = TRUE;
    }
    if (!ok) {
        return FALSE;
    }
    if (idx < 0 || idx >= 4) {
        return FALSE;
    }
    FishCatch *rec = &sFishCatches[idx];
    if (rec->state != 0) {
        return FALSE;
    }
    Actor *ob = (Actor *)PlayerActor_GetActor(idx);
    if (ob == NULL) {
        return FALSE;
    }
    VecFx32 v;
    VecFx32 *ps = &ob->position;
    v = *ps;
    s32 r6 = (u16)id - 0x12e8;
    rec->fishId = r6;
    FishCatch_SetModelAngles(rec, FishAngleXZ(&v, pos), r6);
    VecFx32 *pd = &rec->arcPointA;
    *pd = v;
    pd = &rec->arcPointB;
    *pd = *pos;
    pd = &rec->position;
    *pd = v;
    rec->moveFrame = 0;
    rec->mode = 4;
    rec->state = 1;
    return TRUE;
}


extern "C" void FishShadow_SetAnimSpeed(FishShadow *self, s32 v) {
    self->model.frameStep = (v << 12) >> 4;
}


extern "C" BOOL FishShadow_LoadModel(FishShadow *self, void *p, ModelSlotPool *q) {
    BOOL r = FALSE;
    AnimModel *o = &self->model;
    o->loadCached(0x66736477, sFishShadowModelPath);
    if (p == NULL) {
        return r;
    }
    ModelSlot *slot = q->acquire(&self->modelSlot.index);
    void *t = slot->getHeap();
    u8 *u = func_021065f8(func_021065dc((u8 *)p), r);
    if (o->allocAnmObj(t)) {
        static_cast<BlendAnimModel *>(o)->initAnim(u, r, 0x1000, 1, r);
        o->attachAnim();
        r = TRUE;
    }
    return r;
}


extern "C" BOOL FishFinModel_Load(FishFinModel *self, ModelSlotPool *a)
{
    BOOL ok = FALSE;
    ModelSlot *res = a->acquire(&self->modelSlot.index);
    PooledModel *m = &self->pooledModel;
    if (m->loadFromSlot(res, sFishFinModelPath)) {
        AnimModel *r4 = &self->model;
        r4->setResource((NNSG3dResMdl *)m->getModel(), NULL);
        void *nm = res->getHeap();
        u8 *v = func_021065f8(func_021065dc((u8 *)File_LoadAlloc(sFishFinAnimPath, nm, 4, NULL)), 0);
        if (r4->allocAnmObj(nm)) {
            static_cast<BlendAnimModel *>(r4)->initAnim(v, 0, 0x1000, 1, 0);
            r4->attachAnim();
        } else {
            return FALSE;
        }
        u8 *w = func_02106670(func_02106654((u8 *)File_LoadAlloc(sFishFinTexAnimPath, nm, 4, NULL)), 0);
        if (self->matAnim.allocMatAnm(r4->resMdl, nm)) {
            self->matAnim.init(w, 0, 0x1000, 1);
            self->matAnim.addToRenderObj(r4->getRenderObj());
        } else {
            return FALSE;
        }
        ok = TRUE;
    }
    return ok;
}


extern "C" FishShadow *FishShadow_GetActive(s32 i)
{
    if (i < 0 || i >= 6) {
        return NULL;
    }
    FishShadow *p = &sFishShadows[i];
    if ((u32)(p->state - 3) > 1) {
        p = NULL;
    }
    return p;
}


extern "C" s32 FishShadow_GetFishId(s32 id)
{
    FishShadow *p = FishShadow_GetActive(id);
    if (p == NULL) {
        return -1;
    }
    return p->fishId;
}


extern "C" BOOL FishShadow_GetPos(VecFx32 *out, s32 id)
{
    FishShadow *p = FishShadow_GetActive(id);
    if (p == NULL) {
        return FALSE;
    }
    VecFx32 *q = &p->position;
    out->x = q->x;
    out->y = q->y;
    out->z = q->z;
    return TRUE;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov003_0221ffb8) {
    HOST_OVERLAY_VAR(sFishShadows),
    HOST_OVERLAY_VAR(sFishFinModel),
    HOST_OVERLAY_VAR(sFishCatches),
    HOST_OVERLAY_VAR(data_ov003_02257a7c),
    HOST_OVERLAY_VAR(sBottleThrowStateOwner),
    HOST_OVERLAY_VAR(sBottleThrows),
    HOST_OVERLAY_VAR(sBottleThrowStates),
    HOST_OVERLAY_VAR(sFishSizeClassParams),
    HOST_OVERLAY_VAR(sFishCatchStates),
    HOST_OVERLAY_VAR(sFishShadowAnimPath),
    HOST_OVERLAY_VAR(sFishFinTexAnimPath),
    HOST_OVERLAY_VAR(data_ov003_02234820),
    HOST_OVERLAY_VAR(data_ov003_022347b0),
    HOST_OVERLAY_VAR(sFishShadowAiTable),
    HOST_OVERLAY_VAR(sBottleDriftSpeed),
    HOST_OVERLAY_VAR(sFishShadowMoveStates),
    HOST_OVERLAY_VAR(data_ov003_02234830),
    HOST_OVERLAY_VAR(data_ov003_02234838),
    HOST_OVERLAY_VAR(data_ov003_02234898),
    HOST_OVERLAY_VAR(data_ov003_022348a0),
    HOST_OVERLAY_VAR(data_ov003_022348a8),
    HOST_OVERLAY_VAR(sFishBiteStates),
    HOST_OVERLAY_VAR(data_ov003_022347a0),
    HOST_OVERLAY_VAR(sBottleSinkStep),
    HOST_OVERLAY_VAR(data_ov003_02234888),
    HOST_OVERLAY_VAR(sFishShadowAnimPathStr),
    HOST_OVERLAY_VAR(sFishRodParams),
    HOST_OVERLAY_VAR(data_ov003_02234870),
    HOST_OVERLAY_VAR(data_ov003_022347c8),
    HOST_OVERLAY_VAR(sFieldFishManagerProfile),
    HOST_OVERLAY_VAR(data_ov003_02234858),
    HOST_OVERLAY_VAR(data_ov003_02234850),
    HOST_OVERLAY_VAR(sFishFinAnimPathStr),
    HOST_OVERLAY_VAR(sFishSightGoldenRod),
    HOST_OVERLAY_VAR(data_ov003_02234798),
    HOST_OVERLAY_VAR(data_ov003_022347b8),
    HOST_OVERLAY_VAR(sFishBiteWindowGoldenRod),
    HOST_OVERLAY_VAR(sFishBiteWindowFishingRod),
    HOST_OVERLAY_VAR(sFishCastSplashTimer),
    HOST_OVERLAY_VAR(sFishShadowModelPathStr),
    HOST_OVERLAY_VAR(data_ov003_02234790),
    HOST_OVERLAY_VAR(data_ov003_02234800),
    HOST_OVERLAY_VAR(data_ov003_022347f8),
    HOST_OVERLAY_VAR(data_ov003_02234890),
    HOST_OVERLAY_VAR(data_ov003_022347e8),
    HOST_OVERLAY_VAR(data_ov003_022347e0),
    HOST_OVERLAY_VAR(data_ov003_022347d8),
    HOST_OVERLAY_VAR(data_ov003_022347d0),
    HOST_OVERLAY_VAR(data_ov003_02234880),
    HOST_OVERLAY_VAR(sFishPullJitter),
    HOST_OVERLAY_VAR(data_ov003_02234808),
    HOST_OVERLAY_VAR(sFishFinAnimPath),
    HOST_OVERLAY_VAR(sFishFinTexAnimPathStr),
    HOST_OVERLAY_VAR(data_ov003_02234828),
    HOST_OVERLAY_VAR(data_ov003_022347a8),
    HOST_OVERLAY_VAR(data_ov003_022347c0),
    HOST_OVERLAY_VAR(sFishShadowModelPath),
    HOST_OVERLAY_VAR(data_ov003_022347f0),
    HOST_OVERLAY_VAR(sFishSightFishingRod),
    HOST_OVERLAY_VAR(sFishFinModelPathStr),
    HOST_OVERLAY_VAR(data_ov003_02234818),
    HOST_OVERLAY_VAR(data_ov003_02234848),
    HOST_OVERLAY_VAR(sFishShadowStates),
    HOST_OVERLAY_VAR(sFishFinModelPath),
    HOST_OVERLAY_VAR(data_ov003_022348b0),
    HOST_OVERLAY_VAR(data_ov003_02234878),
    HOST_OVERLAY_VAR(data_ov003_02234840),
    HOST_OVERLAY_VAR(data_ov003_02234810),
    HOST_OVERLAY_VAR(data_ov003_02234868),
    HOST_OVERLAY_VARS_END
};

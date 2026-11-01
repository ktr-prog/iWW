#include "types.h"
#include "host_labels.h"
#include "sdk_linker_symbols.h"
#include "gfx/VecFx32.h"
#include "Unk_020d8c7c.h"
#include "gfx/GfxFrameHooks.h"
#include "gfx/ViewFrustum.h"
#include "game/FxVec3.h"
#include "game/TouchPicker.h"
#include "sys/SceneBase.h"
#include "game/SceneWarp.h"
#include "game/SceneInfo.h"
#include "net/CommManager.h"
#include "sys/ProcProfile.h"
#include "nitro/io_access.h"
#include "gfx/BgModelCache.h"
#include "player/PlayerData.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_0210fa84.h"
#include "proto/autoload_2/unk_02110c98.h"
#include "proto/itcm/unk_01ff8ad4.h"
#include "proto/itcm/unk_01ffa4a0.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02036c58.h"
#include "proto/main/unk_02037734.h"
#include "proto/main/unk_02038474.h"
#include "proto/main/unk_020407fc.h"
#include "proto/main/unk_020411dc.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_02052b50.h"
#include "proto/main/unk_020536dc.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_0205c66c.h"
#include "proto/main/unk_0205c91c.h"
#include "proto/main/unk_0205ce0c.h"
#include "proto/main/unk_0205d1f8.h"
#include "proto/main/unk_0205d340.h"
#include "proto/main/unk_0205d480.h"
#include "proto/main/unk_0205d7d8.h"
#include "proto/main/unk_0205dfa4.h"
#include "proto/main/unk_0205edfc.h"
#include "proto/main/unk_0205ef08.h"
#include "proto/main/unk_0205f284.h"
#include "proto/main/unk_02060b7c.h"
#include "proto/main/unk_02070560.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_020815f8.h"
#include "proto/main/unk_02081cc0.h"
#include "proto/main/unk_02088b98.h"
#include "proto/main/unk_0208e6d8.h"
#include "proto/main/unk_02090268.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_0209c08c.h"
#include "proto/main/unk_0209c4a8.h"
#include "proto/main/unk_020a427c.h"
#include "proto/main/unk_020abbcc.h"
#include "proto/main/unk_020abea8.h"
#include "proto/main/unk_020b4828.h"
#include "proto/main/unk_020b7f7c.h"
#include "proto/main/unk_0204cc1c.h"

#define reg_4000358 (*(u32 *)0x4000358)
#define reg_4000008 (*(u16 *)0x4000008)



static inline void setVec(VecFx32* o, s32 x, s32 y, s32 z) {
    o->x = x;
    o->y = y;
    o->z = z;
}

struct Bits14 {
    u8 pad : 2;
    u8 v : 6;
};

static inline BOOL is0(u8 v) {
    if (v == 0) return TRUE;
    return FALSE;
}
static inline BOOL is1(u8 v) {
    if (v == 1) return TRUE;
    return FALSE;
}

struct ScenePos {
    ScenePos();
    ~ScenePos();
    VecFx32 pos;
    u32 spawnParam;
    s16 angle;
    u8 scene;
    s8 unitX;
    s8 unitZ;
};


struct S394 {
    u8 b[0x20];
    u8 m20;
    u8 m21;
    u16 h22;
    u16 h24;
    u8 m26;
    u8 pad27;
};

struct GroundSeasonDate {
    u8 month;
    u8 day;
    u8 unk_02[2];
    u32 phase;
};

struct B5890 { u8 pad[0x14]; u8 lo : 2; u8 idx : 6; };




class FieldScene : public SceneBase {
public:
    FieldScene() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onExecute();
    virtual BOOL onDraw();
    virtual BOOL onDeleteRequest();

    BOOL stepEnterScene(u64 start);
    BOOL stepSetupSystems(u64 start);
    BOOL stepLoadResources(u64 start);
    BOOL stepCreateSceneProc(u64 start);
    BOOL stepRunSceneEntries(u64 start);
    BOOL stepFinish(u64 start);
};



extern "C" {
extern s32 data_020c8cc0;
extern CommManager *gCommManager;
#define data_021e5890 HOST_LABEL(u8 (*)[], data_021e5890)
extern u8 data_ov006_0225b7b4[];
extern u8 data_ov005_0225b79c[];

u32 PlayerActor_GetResumeTransform(VecFx32* a, s16* b);
void Clock_GetDayMonth(u8 *out);
void TouchPick_Cast(TouchPicker *self, s32 sx, s32 sy, u8 flag);
void ItemInfo_LoadIndoor(s32);
s32 ResCache_Destroy();
void ResCache_Init();
void VramQueue2d_Init();
void VramQueueTex_Init();
void GX_SetBankForSubBG(u32);
void GX_SetBankForSubOBJ(u32);
void G3X_SetFog(u32, u32, u32, u32);
void FieldScene_DebugDraw();
void Collision_UpdateDigHoles();
void Field_UpdateActions();
void Character_ResetList();
void TalkRequestQueue_StartInitial();
void NpcHeapPools_DestroyAll();
void ItemInfo_FreeIndoor();
void NpcHeapPools_CreateAll();
void NookShop_OnSceneLoad();
}

extern "C" {
BOOL Scene_NoPlayerInUnsharedScene(void);
u8 Scene_GetMaxFurniture(u32 i);
u8 Scene_GetMaxSpNpcs(u32 i);
u8 Scene_GetMaxCharacters(u32 i);
u8 Scene_GetMaxPlayers(u32 i);
SceneWarp *Scene_GetWarpRequest(void);
u8 SceneWarp_GetFadeIn(SceneWarp* e);
void SceneWarp_SetFadeOut(SceneWarp* e, u8 v);
u8 SceneWarp_GetFadeOut(SceneWarp* e);
BOOL SceneWarp_HasNoPos(SceneWarp* e);
u32 SceneWarp_GetSpawnParam(SceneWarp* e);
s32 SceneWarp_GetAngle(SceneWarp* e);
VecFx32* SceneWarp_GetPos(SceneWarp* e);
void FieldScene_Request(s32 a, s32 b);
u8 Scene_GetRequestedScene();
u8 SceneWarp_GetScene(SceneWarp *e);
void SceneWarp_Clear(SceneWarp *e);
void Scene_ResetTownReturnPos(SceneWarp *unused);
BOOL Scene_SetTownReturnPos(SceneWarp *unused, s32 id, VecFx32* pos, u32 w, s16 s, s32 p, s32 q);
BOOL Scene_SetSavedPos(SceneWarp *unused, s32 id, VecFx32* pos, u32 w, s16 s, s32 p, s32 q);
BOOL SceneExit_GetDoor(SceneWarp *unused, s32 id, u32* type, s16* s);
BOOL SceneExit_SnapPos(SceneWarp *a, s32 id, VecFx32* out, VecFx32* in);
BOOL SceneWarp_RequestAt(SceneWarp* e, u8 id, VecFx32* v, u32 w, s16 s, u8 p, u8 q);
BOOL SceneWarp_RequestFade(SceneWarp* e, u8 id, u8 p, u8 q);
BOOL SceneWarp_RequestScene(SceneWarp* e, u8 id);
void SceneWarp_Init(SceneWarp* e, u8 id, VecFx32* v, u32 w, s16 s, u8 p, u8 q, s16 r, u8 t);
BOOL SceneId_IsValid(u32 id);
s32 ScenePos_GetUnitZ(ScenePos* i);
s32 ScenePos_GetUnitX(ScenePos* i);
u8 ScenePos_GetScene(ScenePos* i);
s32 ScenePos_GetAngle(ScenePos* i);
u32 ScenePos_GetSpawnParam(ScenePos* i);
VecFx32* ScenePos_GetPos(ScenePos* i);
void ScenePos_Set(ScenePos* i, s32 id, VecFx32* v, u32 w, s16 s, s32 p, s32 q);
void ScenePos_Reset(ScenePos* i);
TouchPicker *Scene_GetTouchPicker();
BOOL GroundSeason_IsSnow();
BOOL GroundSeason_IsSnowPhase(s32 a);
u8 Scene_GetPrevious();
u32 Scene_GetCurrent();
BOOL Scene_AllowsLetterDelivery();
BOOL SceneId_AllowsLetterDelivery(u32 a);
BOOL Scene_InTownUnk31();
BOOL SceneId_IsTownUnk31(u32 a);
BOOL Scene_InTown();
BOOL SceneId_IsTown(u32 a);
BOOL Scene_InVillagerHouse();
BOOL SceneId_IsVillagerHouse(u32 a);
s32 Scene_GetVillagerHouse();
s32 SceneId_GetVillagerHouse(u32 a);
BOOL Scene_InMuseumRoom();
BOOL SceneId_IsMuseumRoom(u32 a);
s32 Scene_GetMuseumRoom();
s32 SceneId_GetMuseumRoom(u32 a);
BOOL Scene_InNookShop();
BOOL SceneId_IsNookShop(u32 a);
void Scene_SavePlayerPos(SceneWarp *unused, s32 add);
s32 SceneExit_ResolveSpecial(SceneWarp *a, s32 id, u8* type, VecFx32* pos, u32* w, s16* s, s32* x, s32* y, u8* p, u8* q);
s32 SceneExit_Resolve(SceneWarp *a, s32 id, u8* type, VecFx32* pos, u32* w, s16* s, u8* p, u8* q, s32* ox, s32* oy);
BOOL SceneWarp_RequestExit(SceneWarp *a, s32 id);
s32 Scene_GetNookShop(void);
s32 SceneId_GetNookShop(u32 x);
BOOL Scene_InUnk6Or7(void);
BOOL SceneId_IsUnk6Or7(s32 x);
BOOL Scene_InUnk6To8(void);
BOOL SceneId_IsUnk6To8(s32 x);
BOOL Scene_InHouseRoom(void);
BOOL SceneId_IsHouseRoom(s32 x);
s32 Scene_GetHouseRoom(void);
s32 SceneId_GetHouseRoom(u32 x);
SceneMapInfo *Scene_GetMapInfo(void);
u8 Scene_GetSkyKind(BOOL a);
void Fog_SetTable(FieldScene *unused, u8* src);
void Fog_SetOffset(u16 v);
void Fog_SetAlpha(u32 v);
s32 Scene_ShutdownGraphics(void);
void Scene_SetupGraphics(void);
void Fog_Apply(FieldScene *unused);
void Fog_InitDefault(FieldScene *a);
u16 GroundSeason_GetColor(void);
u32 GroundSeason_CalcPhase(void);
void FieldScene_ReleaseOverlays(void);
void FieldScene_AcquireOverlays(void);
void FieldScene_ReleaseInfoOverlays(void);
void FieldScene_AcquireInfoOverlays(u8 *obj);
void FieldScene_ReleaseOv002(void);
void FieldScene_AcquireOv002(void);
FieldScene *FieldScene_Create(void);
}

extern const u16 sGroundSeasonColors[12];
extern const u8 sSceneMaxFurniture[0x34];
extern const u8 sSceneMaxPlayers[0x34];
extern const u8 sSceneSkyKinds[0x34];
extern const u8 sSceneMaxCharacters[0x34];
extern const u8 sSceneMaxSpNpcs[0x34];
extern const GroundSeasonDate sGroundSeasonDates[13];
extern u8 sDefaultFogTable[0x20];
extern u8 sSceneFieldKinds[0x34];
extern s32 sSceneOverlayIds[51];
extern u8 gFieldSceneKind;
extern u8 sCurSceneId;
extern u8 sPrevSceneId;
extern s32 sInfoOverlayA;
extern s32 sFieldOverlay;
extern s32 sInfoOverlayB;
extern s32 sSceneOverlay;
extern u32 sFieldOverlayIds[2];
extern SceneInfo *sSceneInfoTable[51];
extern SceneInfo *gCurSceneInfo;
extern u8 data_021ef2d4;
extern GfxFrameHooks sFieldGfxFrameHooks;
extern u32 sOverlaySceneId;
extern ScenePos sSavedScenePos;
extern ScenePos gTownReturnPos;
extern SceneWarp sSceneWarpRequest;
extern S394 sFogState;
extern TouchPicker sTouchPicker;
extern ViewFrustum gViewFrustum;































u8 sDefaultFogTable[0x20] = {
    0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x06, 0x08, 0x0c, 0x10, 0x15, 0x19, 0x1d, 0x21, 0x25,
    0x2a, 0x2e, 0x32, 0x36, 0x3a, 0x3f, 0x43, 0x47, 0x49, 0x4b, 0x4d, 0x4d, 0x4e, 0x4e, 0x4f, 0x4f,
};

GfxFrameHooks sFieldGfxFrameHooks;

ViewFrustum gViewFrustum;

extern "C" SceneInfo data_ov005_0225b7b4;
extern "C" SceneInfo data_ov006_0225b79c;
extern "C" SceneInfo data_ov007_0225b7a8;
extern "C" SceneInfo data_ov008_0225b79c;
extern "C" SceneInfo data_ov010_02258a40;
extern "C" SceneInfo data_ov011_02258a34;
extern "C" SceneInfo data_ov012_02258a2c;
extern "C" SceneInfo data_ov013_02258aa8;
extern "C" SceneInfo data_ov014_02258a84;
extern "C" SceneInfo data_ov015_02258af8;
extern "C" SceneInfo data_ov016_02258ab4;
extern "C" SceneInfo data_ov017_02258a88;
extern "C" SceneInfo data_ov018_02258acc;
extern "C" SceneInfo data_ov019_02258aa4;
extern "C" SceneInfo data_ov020_02258aa8;
extern "C" SceneInfo data_ov021_02258c4c;
extern "C" SceneInfo data_ov022_02258b18;
extern "C" SceneInfo data_ov023_02258ad8;
extern "C" SceneInfo data_ov024_02258af4;
extern "C" SceneInfo data_ov025_02258a94;
extern "C" SceneInfo data_ov026_02258b1c;
extern "C" SceneInfo data_ov027_02258ad8;
extern "C" SceneInfo data_ov028_02258aa8;
extern "C" SceneInfo data_ov029_02258bd0;
extern "C" SceneInfo data_ov030_02258a44;
extern "C" SceneInfo data_ov031_02258a94;
extern "C" SceneInfo data_ov032_02258c34;
extern "C" SceneInfo data_ov033_02258a94;
extern "C" SceneInfo data_ov034_02258a94;
extern "C" SceneInfo data_ov035_02258ad4;
extern "C" SceneInfo data_ov036_02258a78;
extern "C" SceneInfo data_ov037_02258ad4;
extern "C" SceneInfo data_ov038_02258a88;
extern "C" SceneInfo data_ov039_02258a88;
extern "C" SceneInfo data_ov040_02258a88;
extern "C" SceneInfo data_ov041_02258b10;
extern "C" SceneInfo data_ov042_02258ad0;
extern "C" SceneInfo data_ov043_02258a88;
extern "C" SceneInfo data_ov044_02258a88;
SceneInfo *sSceneInfoTable[51] = {
    &data_ov005_0225b7b4,
    &data_ov032_02258c34,
    &data_ov031_02258a94,
    &data_ov034_02258a94,
    &data_ov033_02258a94,
    &data_ov035_02258ad4,
    &data_ov011_02258a34,
    &data_ov012_02258a2c,
    &data_ov010_02258a40,
    &data_ov036_02258a78,
    &data_ov043_02258a88,
    &data_ov015_02258af8,
    &data_ov015_02258af8,
    &data_ov015_02258af8,
    &data_ov015_02258af8,
    &data_ov014_02258a84,
    &data_ov017_02258a88,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov029_02258bd0,
    &data_ov038_02258a88,
    &data_ov039_02258a88,
    &data_ov040_02258a88,
    &data_ov041_02258b10,
    &data_ov042_02258ad0,
    &data_ov013_02258aa8,
    &data_ov021_02258c4c,
    &data_ov020_02258aa8,
    &data_ov019_02258aa4,
    &data_ov022_02258b18,
    &data_ov023_02258ad8,
    &data_ov024_02258af4,
    &data_ov025_02258a94,
    &data_ov026_02258b1c,
    &data_ov027_02258ad8,
    &data_ov028_02258aa8,
    &data_ov007_0225b7a8,
    &data_ov008_0225b79c,
    &data_ov006_0225b79c,
    &data_ov044_02258a88,
    &data_ov037_02258ad4,
    &data_ov016_02258ab4,
    &data_ov030_02258a44,
    &data_ov005_0225b7b4,
    &data_ov018_02258acc,
};

s32 sSceneOverlayIds[51] = {
    5, 32, 31, 34, 33, 35, 11, 12,
    10, 36, 43, 15, 15, 15, 15, 14,
    17, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 38, 39, 40, 41, 42, 13,
    21, 20, 19, 22, 23, 24, 25, 26,
    27, 28, 7, 8, 6, 44, 37, 16,
    30, 5, 18,
};

TouchPicker sTouchPicker;

SceneInfo *gCurSceneInfo;

SceneWarp sSceneWarpRequest;

const u16 sGroundSeasonColors[12] = {
    0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fdd,
    0x7fba, 0x7f98, 0x7f98, 0x7bbc,
};

u32 sFieldOverlayIds[2] = {3, 4};

s32 sInfoOverlayB = -1;

s32 sFieldOverlay = -1;

u8 sPrevSceneId = 0x3f;

const u8 sSceneMaxCharacters[0x34] = {
    0x05, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x05, 0x05, 0x05, 0x05, 0x05, 0x02,
    0x02, 0x05, 0x05, 0x00,
};

const u8 sSceneMaxSpNpcs[0x34] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,
    0x01, 0x01, 0x01, 0x00,
};

s32 sSceneOverlay = -1;

u32 sOverlaySceneId;

u8 sCurSceneId = 0x3f;

ScenePos sSavedScenePos;

S394 sFogState;

ScenePos gTownReturnPos;

const u8 sSceneMaxFurniture[0x34] = {
    0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x08, 0x08, 0x01, 0x0e, 0x01, 0x01, 0x01, 0x01, 0x0a,
    0x01, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x05,
    0x01, 0x04, 0x04, 0x01, 0x01, 0x1c, 0x1c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x01, 0x00,
};

u8 data_021ef2d4;

const u8 sSceneMaxPlayers[0x34] = {
    0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x02, 0x04, 0x02,
    0x01, 0x04, 0x04, 0x00,
};

u8 sSceneFieldKinds[0x34] = {
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x01, 0x00,
};

ProcProfile sFieldSceneProfile = {(void *(*)())FieldScene_Create, 6, 0xd4};

const u8 sSceneSkyKinds[0x34] = {
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00,
};

u8 gFieldSceneKind = 2;

s32 sInfoOverlayA = -1;

const GroundSeasonDate sGroundSeasonDates[13] = {
    {2, 0x03, {0, 0}, 9}, {2, 0x11, {0, 0}, 0xa}, {2, 0x18, {0, 0}, 0xb}, {3, 0x1f, {0, 0}, 0},
    {7, 0x16, {0, 0}, 1}, {9, 0x0f, {0, 0}, 2}, {9, 0x1e, {0, 0}, 3}, {0xa, 0x10, {0, 0}, 4},
    {0xa, 0x1e, {0, 0}, 5}, {0xb, 0x0d, {0, 0}, 6}, {0xb, 0x19, {0, 0}, 7}, {0xc, 0x0a, {0, 0}, 8},
    {0xc, 0x1f, {0, 0}, 9},
};

extern "C" FieldScene *FieldScene_Create(void) {
    return new FieldScene();
}


extern "C" void FieldScene_AcquireOv002(void) { OverlayMgr_Acquire(OVERLAY_2_ID); }

extern "C" void FieldScene_ReleaseOv002(void) { OverlayMgr_Release(OVERLAY_2_ID); }

extern "C" void FieldScene_AcquireInfoOverlays(u8 *obj) {
    s32 a = ((SceneInfo *)obj)->infoOverlayA;
    sInfoOverlayA = a;
    sInfoOverlayB = ((SceneInfo *)obj)->infoOverlayB;
    if (a != -1) {
        OverlayMgr_Acquire(a);
    }
    if (sInfoOverlayB != -1) {
        OverlayMgr_Acquire(sInfoOverlayB);
    }
}

extern "C" void FieldScene_ReleaseInfoOverlays(void) {
    if (sInfoOverlayA != -1) {
        OverlayMgr_Release(sInfoOverlayA);
        sInfoOverlayA = -1;
    }
    if (sInfoOverlayB != -1) {
        OverlayMgr_Release(sInfoOverlayB);
        sInfoOverlayB = -1;
    }
}

extern "C" void FieldScene_AcquireOverlays(void) {
    u8 idx = sSceneFieldKinds[sOverlaySceneId];
    u32 v = sFieldOverlayIds[idx];
    OverlayMgr_Acquire(v);
    sFieldOverlay = v;
    gFieldSceneKind = idx;
    if (sSceneOverlayIds[sOverlaySceneId] != -1) {
        OverlayMgr_Acquire(sSceneOverlayIds[sOverlaySceneId]);
        sSceneOverlay = sSceneOverlayIds[sOverlaySceneId];
    }
}

extern "C" void FieldScene_ReleaseOverlays(void) {
    FieldScene_ReleaseInfoOverlays();
    if (sSceneOverlay != -1) {
        OverlayMgr_Release(sSceneOverlay);
        sSceneOverlay = -1;
    }
    if (sFieldOverlay != -1) {
        OverlayMgr_Release(sFieldOverlay);
        sFieldOverlay = -1;
    }
}

extern "C" u32 GroundSeason_CalcPhase(void) {
    u8 buf[2];
    Clock_GetDayMonth(buf);
    u32 a = buf[1];
    u32 b = buf[0];
    for (u32 i = 0; i < 13; i++) {
        u32 t = sGroundSeasonDates[i].month;
        if (a < t) {
            return sGroundSeasonDates[i].phase;
        }
        if (a == t && b <= sGroundSeasonDates[i].day) {
            return sGroundSeasonDates[i].phase;
        }
    }
    return 0;
}

extern "C" u16 GroundSeason_GetColor(void) {
    s32 idx = ((struct B5890*)data_021e5890)->idx;
    if (idx < 0xc) return sGroundSeasonColors[idx];
    return sGroundSeasonColors[0];
}

BOOL FieldScene::stepEnterScene(u64) {
    ScreenTransition_ShowCover();
    u8 m = sCurSceneId;
    u8 r0 = NetSession_GetActiveSyncKind();
    if (m == 0x2e || m == 0xd || m == 0xc || m == 0xe || m == 0x2f) {
        if (r0 != 4) NetSession_SetActiveSyncKind(4);
    }
    Character_ResetList();
    sPrevSceneId = sCurSceneId;
    sCurSceneId = SceneWarp_GetScene(&sSceneWarpRequest);
    FieldScene_AcquireOv002();
    gGfxFrameHooks = &sFieldGfxFrameHooks;
    Scene_GetTouchPicker()->reset();
    data_021ef2d4 = 0;
    sOverlaySceneId = sCurSceneId;
    FieldScene_AcquireOverlays();
    gCurSceneInfo = sSceneInfoTable[sCurSceneId];
    FieldScene_AcquireInfoOverlays((u8 *)gCurSceneInfo);
    return TRUE;
}

BOOL FieldScene::stepSetupSystems(u64) {
    Scene_SetupGraphics();
    ScreenTransition_ShowCover();
    TransitionCommIcon_ResumeWinOut();
    Snd_CreateScene();
    CommManager *p = gCommManager;
    s32 i;
    if ((p)->isSlotActive(p->myAid)) {
        for (i = 0; i < 4; i++) PlayerSession_SetGfxSlot(i, 4);
    } else if (Scene_InUnk6Or7()) {
        ((CommManager *)(p))->setMemberCount(4);
        for (i = 0; i < 4; i++) PlayerSession_SetGfxSlot(i, i);
    } else {
        ((CommManager *)(p))->setMemberCount(1);
        for (i = 0; i < 4; i++) PlayerSession_SetGfxSlot(i, 4);
    }
    if (Scene_InUnk6Or7()) {
        if (Scene_GetCurrent() == 6) {
            p->localSlot = 4;
            for (i = 3; i >= 0; i--) PlayerSession_SetDataIndex(i, i);
        } else if (Scene_GetCurrent() == 7) {
            s32 a = p->localSlot;
            s32 b = PlayerSession_GetDataIndex(a);
            s32 c = 0;
            for (i = 3; i >= 0; i--) {
                if (i != a) {
                    if (c == b) c++;
                    PlayerSession_SetDataIndex(i, c);
                    c++;
                }
            }
        }
    } else if (Scene_GetCurrent() == 0x2c) {
        CommManager *q = gCommManager;
        q->myAid = 4;
        q->localSlot = 4;
        for (i = 3; i >= 0; i--) PlayerSession_ClearDataIndex(i);
    }
    return TRUE;
}

BOOL FieldScene::stepLoadResources(u64) {
    BgModelCache_Get()->setup(gCurSceneInfo->isOutdoor == 1 ? TRUE : FALSE);
    FtrInfo_LoadIndoor(gCurSceneInfo->isOutdoor == 1 ? TRUE : FALSE);
    ItemInfo_LoadIndoor(gCurSceneInfo->isOutdoor == 1 ? TRUE : FALSE);
    PatternTexCache_Get()->load();
    CharaAnimCache_Create(gCurrentHeap);
    CharaClothTexPool_Create(gCurrentHeap);
    PlayerFaceTexPool_Create(gCurrentHeap);
    CharaFaceAnimPool_Create(gCurrentHeap);
    CharaFaceAnimWorkPool_Create(gCurrentHeap);
    PlayerBodyWorkPool_Create(gCurrentHeap);
    PlayerBodyModelPool_Create(gCurrentHeap);
    PlayerHeadBank_Init(gCurrentHeap);
    PlayerPalettePool_Create(gCurrentHeap);
    PlayerGlassesModelPool_Create(gCurrentHeap);
    HeldItemModels_Init(gCurrentHeap);
    FishBobberPool_Create(gCurrentHeap);
    ObjShadow_Init(gCurSceneInfo->isOutdoor == 1 ? TRUE : FALSE);
    CharaShadow_Load();
    NpcHeapPools_CreateAll();
    NpcResPools_ClearOnSceneCreate();
    NpcRegistry_Clear();
    PlayerActorHeap_Create(gCurrentHeap);
    RoomEntry_OnSceneLoad();
    if (Scene_GetCurrent() == 0x2c || Scene_GetCurrent() == 0x2d) {
        Scene_ResetTownReturnPos(Scene_GetWarpRequest());
    }
    NookShop_OnSceneLoad();
    return TRUE;
}

BOOL FieldScene::stepCreateSceneProc(u64) {
    gCurSceneInfo->createSceneMapModule();
    return TRUE;
}

BOOL FieldScene::stepRunSceneEntries(u64 start) {
    return gCurSceneInfo->runSpawnList(&data_021eda50, &data_021eda58, start);
}

BOOL FieldScene::stepFinish(u64) {
    Fog_InitDefault(this);
    Effect_ResetAll();
    IO_W(&reg_4000008, (IO_R(&reg_4000008) & ~3) | 2);
    ActorCollider_InitList();
    data_021ce63c = 0;
    SceneWarp_Clear(&sSceneWarpRequest);
    gVBlanksPerFrame = 3;
    TalkRequestQueue_StartInitial();
    if (Scene_GetCurrent() == 0x2e || Scene_GetCurrent() == 0xd || Scene_GetCurrent() == 0x2f)
        ChatBalloon_DismissAll();
    Bgm_StartSceneBgm();
    return TRUE;
}

BOOL FieldScene::onCreate() {
    typedef BOOL (FieldScene::*M)(u64);
    static M tbl[6] = {
        &FieldScene::stepEnterScene, &FieldScene::stepSetupSystems, &FieldScene::stepLoadResources,
        &FieldScene::stepCreateSceneProc, &FieldScene::stepRunSceneEntries, &FieldScene::stepFinish,
    };
    u64 start = OS_GetTick();
    u32 fail = 0;
    for (;;) {
        u32 idx = gSceneCreating - 1;
        if (idx >= 6) break;
        if ((this->*tbl[idx])(start)) {
            gSceneCreating++;
            if (gSceneCreating > 6) break;
            u64 now = OS_GetTick();
            u64 d = (now - start) << 6;
            if ((u32)(d / 0x82ea) > 0x28) {
                fail = 1;
                break;
            }
        } else {
            fail = 1;
            break;
        }
    }
    if (fail) {
        Comm_ProcessReceived(0);
        NetSession_Update();
        Field_UpdateActions();
        return -1;
    }
    return 1;
}

BOOL FieldScene::onDelete() {
    Bgm_EndSceneBgm();
    Scene_GetTouchPicker()->reset();
    gGfxFrameHooks = NULL;
    PlayerActorHeap_Destroy();
    NpcResPools_ClearOnSceneDelete();
    NpcHeapPools_DestroyAll();
    NpcRegistry_Clear();
    FishBobberPool_Destroy();
    HeldItemModels_Destroy();
    PlayerPalettePool_Destroy();
    PlayerGlassesModelPool_Destroy();
    PlayerHeadBank_Destroy();
    PlayerBodyModelPool_Destroy();
    PlayerBodyWorkPool_Destroy();
    CharaFaceAnimWorkPool_Destroy();
    CharaFaceAnimPool_Destroy();
    PlayerFaceTexPool_Destroy();
    CharaClothTexPool_Destroy();
    CharaAnimCache_Destroy();
    PatternTexCache_Get()->unload();
    FtrInfo_FreeIndoor();
    ItemInfo_FreeIndoor();
    CharaShadow_Unload();
    ObjShadow_Exit();
    BgModelCache_Get()->reset();
    Scene_ShutdownGraphics();
    data_021ce63c = 0;
    if (Scene_GetCurrent() == 6) {
        u32 i = 0;
        CommManager *p = gCommManager;
        for (; i < 4; i++) {
            if (i == 0) {
                PlayerSession_SetDataIndex(0, p->localSlot);
                p->localSlot = 0;
            } else {
                PlayerSession_ClearDataIndex(i);
            }
        }
    } else if (Scene_GetCurrent() == 7) {
        s32 i = 2;
        for (; i >= 0; i--) PlayerSession_ClearDataIndex(i + 1);
    } else if (Scene_GetCurrent() == 0xe) {
        s32 v = NetSession_GetLastSyncSlot();
        if (v > 0 && v < 4) {
            void *pd = (void *)PlayerData_Get(v + 3);
            if (pd) ((PlayerData *)(pd))->reset();
            PlayerSession_ClearDataIndex(v);
        }
        NetSession_SetLastSyncSlot(4);
    }
    FieldScene_ReleaseOverlays();
    gCurSceneInfo = 0;
    FieldScene_ReleaseOv002();
    gFieldSceneKind = 2;
    return TRUE;
}

BOOL FieldScene::onExecute() {
    Collision_UpdateDigHoles();
    ActorCollider_ClearList();
    BOOL b;
    if (gScreenTransition.state == 2) b = TRUE; else b = FALSE;
    if (!b && data_021c3cb8 == 0) return TRUE;
    if (SceneId_IsValid(SceneWarp_GetScene(&sSceneWarpRequest))) {
        s32 r4 = SceneWarp_GetFadeOut(Scene_GetWarpRequest());
        FieldScene_Request(r4, SceneWarp_GetFadeIn(Scene_GetWarpRequest()));
    }
    return TRUE;
}

BOOL FieldScene::onDraw() {
    Fog_Apply(this);
    NNS_G3dGeFlushBuffer();
    TouchPick_Cast(Scene_GetTouchPicker(), (u8)gTouchX, (u8)gTouchY, gTouchHeld ? 1 : 0);
    FieldScene_DebugDraw();
    ActorCollider_ResolveAll();
    return TRUE;
}

BOOL FieldScene::onDeleteRequest() { return TRUE; }

extern "C" void Fog_InitDefault(FieldScene *a) {
    Fog_SetTable(a, sDefaultFogTable);
    BOOL b;
    if (gFieldSceneKind == 1) b = TRUE; else b = FALSE;
    if (b) sFogState.m20 = 0;
    else sFogState.m20 = 1;
    sFogState.m21 = 8;
    sFogState.h22 = 0xd2;
    sFogState.h24 = 0x7fff;
    sFogState.m26 = 0;
    Fog_Apply(a);
}

extern "C" void Fog_Apply(FieldScene *unused) {
    S394* a = &sFogState;
    G3X_SetFog(a->m20, 1, a->m21, a->h22);
    IO_W(&reg_4000358, a->h24 | (a->m26 << 16));
    G3X_SetFogTable(a);
}

extern "C" void Scene_SetupGraphics(void) {
    Gfx_ResetScene();
    VramQueue2d_Init();
    VramQueueTex_Init();
    Gfx_DisableAllBanks();
    GX_SetBankForTex(7);
    GX_SetBankForTexPltt(0x10);
    GX_SetBankForBG(0x20);
    GX_SetBankForOBJ(0x40);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    IO_W((volatile u32 *)0x4000000, IO_R((volatile u32 *)0x4000000) & 0xffcfffef);
    IO_W((volatile u32 *)0x4001000, IO_R((volatile u32 *)0x4001000) & 0xffcfffef);
    Gfx2d_SetMainBgMode(0);
    Gfx2d_SetSubBgMode(1);
    IO_W((volatile u32 *)0x4000000, IO_R((volatile u32 *)0x4000000) & 0xc7ffffff);
    TexVram_InitManagers();
    Gfx2d_ShowMainPlanes(0x11);
    Gfx2d_ShowSubPlanes(0x10);
    ResCache_Init();
    CommCaution_Init();
}

extern "C" s32 Scene_ShutdownGraphics(void) { CommCaution_Release(); return ResCache_Destroy(); }

extern "C" void Fog_SetAlpha(u32 v) { sFogState.m26 = v & 0x1f; }

extern "C" void Fog_SetOffset(u16 v) { sFogState.h22 = v; }

extern "C" void Fog_SetTable(FieldScene *unused, u8* src) {
    u8* dst = (u8*)&sFogState;
    s32 i;
    for (i = 0; i < 0x20; i++) {
        *dst = *src;
        dst++; src++;
    }
}

void GfxFrameHooks::onVBlank() {}

extern "C" u8 Scene_GetSkyKind(BOOL a) {
    u8 r = 0;
    if (gActorDefaultParent != NULL) {
        u16 x = gActorDefaultParent->profile;
        BOOL c3 = TRUE;
        BOOL c2 = TRUE;
        u8 m = gFieldSceneKind;
        BOOL A = (m == 0) ? TRUE : FALSE;
        if (!A) {
            BOOL B = (m == 1) ? TRUE : FALSE;
            if (!B) c2 = FALSE;
        }
        if (!c2) {
            if (!a || x != 5) c3 = FALSE;
        }
        if (c3) {
            s32 idx = Scene_GetCurrent();
            if (SceneId_IsValid(idx)) r = sSceneSkyKinds[idx];
        }
    }
    return r;
}

extern "C" SceneMapInfo *Scene_GetMapInfo(void) {
    SceneMapInfo *r = NULL;
    if (gCurSceneInfo != NULL) r = gCurSceneInfo->mapInfo;
    return r;
}

extern "C" s32 SceneId_GetHouseRoom(u32 x) {
    if (x >= 1 && x <= 5) return x - 1;
    return -1;
}

extern "C" s32 Scene_GetHouseRoom(void) { return SceneId_GetHouseRoom(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsHouseRoom(s32 x) {
    s32 v = SceneId_GetHouseRoom(x);
    BOOL r = FALSE;
    if (v != -1) r = TRUE;
    return r;
}

extern "C" BOOL Scene_InHouseRoom(void) { return SceneId_IsHouseRoom(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsUnk6To8(s32 x) {
    if ((u8)(x + 0xfa) <= 2) return TRUE;
    return FALSE;
}

extern "C" BOOL Scene_InUnk6To8(void) { return SceneId_IsUnk6To8(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsUnk6Or7(s32 x) {
    switch (x) {
    case 6:
    case 7:
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL Scene_InUnk6Or7(void) { return SceneId_IsUnk6Or7(Scene_GetCurrent()); }

extern "C" s32 SceneId_GetNookShop(u32 x) {
    if (x >= 0x1a && x <= 0x1f) return x - 0x1a;
    return -1;
}

extern "C" s32 Scene_GetNookShop(void) { return SceneId_GetNookShop(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsNookShop(u32 a) {
    if (SceneId_GetNookShop(a) != -1) return TRUE;
    return FALSE;
}

extern "C" BOOL Scene_InNookShop() { return SceneId_IsNookShop(Scene_GetCurrent()); }

extern "C" s32 SceneId_GetMuseumRoom(u32 a) {
    if (a >= 0x20 && a <= 0x29) return a - 0x20;
    return -1;
}

extern "C" s32 Scene_GetMuseumRoom() { return SceneId_GetMuseumRoom(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsMuseumRoom(u32 a) {
    if (SceneId_GetMuseumRoom(a) != -1) return TRUE;
    return FALSE;
}

extern "C" BOOL Scene_InMuseumRoom() { return SceneId_IsMuseumRoom(Scene_GetCurrent()); }

extern "C" s32 SceneId_GetVillagerHouse(u32 a) {
    if (a >= 0x11 && a <= 0x18) return a - 0x11;
    return -1;
}

extern "C" s32 Scene_GetVillagerHouse() { return SceneId_GetVillagerHouse(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsVillagerHouse(u32 a) {
    if (SceneId_GetVillagerHouse(a) != -1) return TRUE;
    return FALSE;
}

extern "C" BOOL Scene_InVillagerHouse() { return SceneId_IsVillagerHouse(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsTown(u32 a) {
    if (a == 0) return TRUE;
    return FALSE;
}

extern "C" BOOL Scene_InTown() { return SceneId_IsTown(Scene_GetCurrent()); }

extern "C" BOOL SceneId_IsTownUnk31(u32 a) {
    if (a == 0x31) return TRUE;
    return FALSE;
}

extern "C" BOOL Scene_InTownUnk31() { return SceneId_IsTownUnk31(Scene_GetCurrent()); }

extern "C" BOOL SceneId_AllowsLetterDelivery(u32 a) {
    if (SceneId_IsUnk6To8(a) || a == 0x2c || a == 0x2d || a == 0x2e || a == 0x2f || (u8)(a + 0xf4) <= 2) return FALSE;
    return TRUE;
}

extern "C" BOOL Scene_AllowsLetterDelivery() {
    u8 v = gFieldSceneKind;
    if (is0(v) || is1(v)) return SceneId_AllowsLetterDelivery(Scene_GetCurrent());
    return FALSE;
}

extern "C" u32 Scene_GetCurrent() { return sCurSceneId; }

extern "C" u8 Scene_GetPrevious() { return sPrevSceneId; }

extern "C" BOOL GroundSeason_IsSnowPhase(s32 a) {
    if (a < 9) return FALSE;
    return TRUE;
}

extern "C" BOOL GroundSeason_IsSnow() { return GroundSeason_IsSnowPhase(((Bits14*)&data_021e5890[0x14])->v); }

extern "C" TouchPicker *Scene_GetTouchPicker() { return &sTouchPicker; }

ScenePos::ScenePos() { ScenePos_Reset(this); }

ScenePos::~ScenePos() {}


extern "C" void ScenePos_Reset(ScenePos* i) {
    static FxVec3 v(0x30000, 0, 0x30000);
    ScenePos_Set(i, 0, (VecFx32*)&v, 0x800000, 0, -1, -1);
}

extern "C" void ScenePos_Set(ScenePos* i, s32 id, VecFx32* v, u32 w, s16 s, s32 p, s32 q) {
    i->scene = id;
    i->pos.x = v->x;
    i->pos.y = v->y;
    i->pos.z = v->z;
    i->spawnParam = w;
    i->angle = s;
    i->unitX = p;
    i->unitZ = q;
}

extern "C" VecFx32* ScenePos_GetPos(ScenePos* i) { return &i->pos; }

extern "C" u32 ScenePos_GetSpawnParam(ScenePos* i) { return i->spawnParam; }

extern "C" s32 ScenePos_GetAngle(ScenePos* i) { return i->angle; }

extern "C" u8 ScenePos_GetScene(ScenePos* i) { return i->scene; }

extern "C" s32 ScenePos_GetUnitX(ScenePos* i) { return i->unitX; }

extern "C" s32 ScenePos_GetUnitZ(ScenePos* i) { return i->unitZ; }

extern "C" BOOL SceneId_IsValid(u32 id) {
    if (id < 0x33) return TRUE;
    return FALSE;
}

SceneWarp::SceneWarp() {
    type = 0x3f;
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    spawnParam = 0;
    angle = 0;
    flag = 1;
    fadeOut = 2;
    fadeIn = 2;
    exitAngle = 0;
    exitKind = 0;
}

extern "C" void SceneWarp_Init(SceneWarp* e, u8 id, VecFx32* v, u32 w, s16 s, u8 p, u8 q, s16 r, u8 t) {
    e->type = id;
    e->pos.x = v->x;
    e->pos.y = v->y;
    e->pos.z = v->z;
    e->spawnParam = w;
    e->angle = s;
    e->fadeOut = p;
    e->fadeIn = q;
    e->exitAngle = r;
    e->exitKind = t;
}

extern "C" BOOL SceneWarp_RequestScene(SceneWarp* e, u8 id) {
    if (e->type == 0x3f) {
        e->type = id;
        e->flag = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL SceneWarp_RequestFade(SceneWarp* e, u8 id, u8 p, u8 q) {
    if (e->type == 0x3f) {
        e->type = id;
        e->fadeOut = p;
        e->fadeIn = q;
        e->flag = 1;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL SceneWarp_RequestAt(SceneWarp* e, u8 id, VecFx32* v, u32 w, s16 s, u8 p, u8 q) {
    if (e->type == 0x3f) {
        e->type = id;
        e->pos.x = v->x;
        e->pos.y = v->y;
        e->pos.z = v->z;
        e->spawnParam = w;
        e->angle = s;
        e->flag = 0;
        e->fadeOut = p;
        e->fadeIn = q;
        return TRUE;
    }
    return FALSE;
}

extern "C" s32 SceneExit_ResolveSpecial(SceneWarp *a, s32 id, u8* type, VecFx32* pos, u32* w, s16* s, s32* x, s32* y, u8* p, u8* q) {
    if (id != -1) {
        SceneInfo* d = gCurSceneInfo;
        if (d) {
            SceneWarpList* t = d->warps;
            if (t) {
                SceneWarp* entries = t->warps;
                if (entries) {
                    u8 n = t->count;
                    if (id >= 0 && id < n) {
                        SceneWarp* e = &entries[id];
                        BlockMap * o = TownBlockMap_Get();
                        s32 va, vb;
                        VecFx32 v;
                        switch (entries[id].type) {
                        case 0x3e:
                            if (Town_FindPlayerHouse(o, &v, &va, &vb)) {
                                v.z += 0x1000;
                                *type = 0;
                                pos->x = v.x;
                                pos->y = v.y;
                                pos->z = v.z;
                                *w = 0xf000000;
                                *s = 0;
                                *x = va;
                                *y = vb;
                                *p = e->fadeOut;
                                *q = e->fadeIn;
                            }
                            return 3;
                        case 0x3d:
                            if (Town_FindGateHouse(o, &v, &va, &vb)) {
                                v.z += 0x1000;
                                *type = 0;
                                pos->x = v.x;
                                pos->y = v.y;
                                pos->z = v.z;
                                *w = 0xf000000;
                                *s = 0;
                                *x = va;
                                *y = vb;
                                *p = e->fadeOut;
                                *q = e->fadeIn;
                            }
                            return 3;
                        case 0x3f:
                            *type = ScenePos_GetScene(&sSavedScenePos);
                            {
                                VecFx32* src = ScenePos_GetPos(&sSavedScenePos);
                                pos->x = src->x;
                                pos->y = src->y;
                                pos->z = src->z;
                            }
                            *w = ScenePos_GetSpawnParam(&sSavedScenePos);
                            *s = ScenePos_GetAngle(&sSavedScenePos);
                            *x = ScenePos_GetUnitX(&sSavedScenePos);
                            *y = ScenePos_GetUnitZ(&sSavedScenePos);
                            *p = e->fadeOut;
                            *q = e->fadeIn;
                            return 2;
                        case 0x3c:
                            *type = ScenePos_GetScene(&gTownReturnPos);
                            {
                                VecFx32* src = ScenePos_GetPos(&gTownReturnPos);
                                pos->x = src->x;
                                pos->y = src->y;
                                pos->z = src->z;
                            }
                            *w = ScenePos_GetSpawnParam(&gTownReturnPos);
                            *s = ScenePos_GetAngle(&gTownReturnPos);
                            *x = ScenePos_GetUnitX(&gTownReturnPos);
                            *y = ScenePos_GetUnitZ(&gTownReturnPos);
                            *p = e->fadeOut;
                            *q = e->fadeIn;
                            return 3;
                        default:
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

extern "C" s32 SceneExit_Resolve(SceneWarp *a, s32 id, u8* type, VecFx32* pos, u32* w, s16* s, u8* p, u8* q, s32* ox, s32* oy) {
    s32 x, y;
    s32 r = SceneExit_ResolveSpecial(a, id, type, pos, w, s, &x, &y, p, q);
    if (ox) *ox = x;
    if (oy) *oy = y;
    if (r == 1) {
        if (id != -1) {
            SceneInfo* d = gCurSceneInfo;
            if (d) {
                SceneWarpList* t = d->warps;
                if (t) {
                    SceneWarp* entries = t->warps;
                    if (entries) {
                        u8 n = t->count;
                        if (id >= 0 && id < n) {
                            SceneWarp* e = &entries[id];
                            u8 ty = e->type;
                            if (e->pos.y == 0) e->pos.y = 0x200;
                            if ((gCommManager)->isSlotActive(gCommManager->myAid) && ty == 7) ty = 8;
                            *type = ty;
                            pos->x = e->pos.x;
                            pos->y = e->pos.y;
                            pos->z = e->pos.z;
                            *w = e->spawnParam;
                            *s = e->angle;
                            *p = e->fadeOut;
                            *q = e->fadeIn;
                            return r;
                        }
                    }
                }
            }
        }
        return 0;
    }
    return r;
}

extern "C" BOOL SceneWarp_RequestExit(SceneWarp *a, s32 id) {
    u8 t, u, v;
    s16 s;
    s32 w, x, y;
    VecFx32 vec;
    s32 r = SceneExit_Resolve(a, id, &t, &vec, (u32*)&w, &s, &u, &v, &x, &y);
    switch (r) {
    case 0:
        goto fail;
    case 2:
        ScenePos_Set(&sSavedScenePos, t, &vec, w, s, x, y);
        break;
    case 3:
        ScenePos_Set(&gTownReturnPos, t, &vec, w, s, x, y);
        break;
    }
    if (SceneWarp_RequestAt(a, t, &vec, w, s, u, v)) return TRUE;
fail:
    return FALSE;
}

extern "C" BOOL SceneExit_GetDoor(SceneWarp *unused, s32 id, u32* type, s16* s) {
    *type = 0;
    *s = 0;
    if (id != -1) {
        SceneInfo* d = gCurSceneInfo;
        if (d) {
            SceneWarpList* t = d->warps;
            if (t) {
                SceneWarp* e = t->warps;
                if (e) {
                    u8 n = t->count;
                    if (id >= 0 && id < n) {
                        SceneWarp* p = &e[id];
                        if (type) *type = p->exitKind;
                        if (s) *s = p->exitAngle;
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

extern "C" BOOL SceneExit_SnapPos(SceneWarp *a, s32 id, VecFx32* out, VecFx32* in) {
    u32 type;
    s16 s;
    VecFx32 t;
    if (SceneExit_GetDoor(a, id, &type, &s)) {
        FieldPos_SnapToUnitCenter(&t, in);
        setVec(out, t.x, in->y, t.z);
        if (s == 0 || s == -0x8000) {
            out->x = in->x;
            return TRUE;
        } else if (s == 0x4000 || s == -0x4000) {
            out->z = in->z;
            return TRUE;
        }
        return TRUE;
    }
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
    return FALSE;
}

extern "C" BOOL Scene_SetSavedPos(SceneWarp *unused, s32 id, VecFx32* pos, u32 w, s16 s, s32 p, s32 q) {
    if (SceneId_IsValid(id)) {
        ScenePos_Set(&sSavedScenePos, id, pos, w, s, p, q);
        return TRUE;
    }
    return FALSE;
}


extern "C" void Scene_SavePlayerPos(SceneWarp *unused, s32 add) {
    static s32 minZ = data_020c8cc0 + 0x1000;
    s16 s;
    s32 p, q;
    VecFx32 v;
    u32 r = PlayerActor_GetResumeTransform(&v, &s);
    p = 0;
    q = 0;
    FieldPos_ToUnit(&p, &q, &v);
    if (Scene_GetCurrent() == 0xb && v.z < minZ) v.z = minZ;
    v.z += add;
    Scene_SetSavedPos(Scene_GetWarpRequest(), Scene_GetCurrent(), &v, (r << 22) & 0x3fc00000, s, p, q);
}


extern "C" BOOL Scene_SetTownReturnPos(SceneWarp *unused, s32 id, VecFx32* pos, u32 w, s16 s, s32 p, s32 q) {
    if (SceneId_IsValid(id)) {
        ScenePos_Set(&gTownReturnPos, id, pos, w, s, p, q);
        return TRUE;
    }
    return FALSE;
}

extern "C" void Scene_ResetTownReturnPos(SceneWarp *unused) { ScenePos_Reset(&gTownReturnPos); }

extern "C" void SceneWarp_Clear(SceneWarp *e) { e->type = 0x3f; }

extern "C" u8 SceneWarp_GetScene(SceneWarp *e) { return e->type; }

extern "C" u8 Scene_GetRequestedScene() { return SceneWarp_GetScene(Scene_GetWarpRequest()); }

extern "C" void FieldScene_Request(s32 a, s32 b) {
    if (gNextSceneProfile != 5) {
        Scene_Request(5, a, 3, 1);
        Scene_SaveFadeIn(b);
    }
}

extern "C" VecFx32* SceneWarp_GetPos(SceneWarp* e) { return &e->pos; }

extern "C" s32 SceneWarp_GetAngle(SceneWarp* e) { return e->angle; }

extern "C" u32 SceneWarp_GetSpawnParam(SceneWarp* e) { return e->spawnParam; }

extern "C" BOOL SceneWarp_HasNoPos(SceneWarp* e) {
    if (e->flag != 0) return TRUE;
    return FALSE;
}

extern "C" u8 SceneWarp_GetFadeOut(SceneWarp* e) { return e->fadeOut; }

extern "C" void SceneWarp_SetFadeOut(SceneWarp* e, u8 v) { e->fadeOut = v; }

extern "C" u8 SceneWarp_GetFadeIn(SceneWarp* e) { return e->fadeIn; }

extern "C" SceneWarp *Scene_GetWarpRequest(void) { return &sSceneWarpRequest; }

extern "C" u8 Scene_GetMaxPlayers(u32 i) { return sSceneMaxPlayers[i]; }

extern "C" u8 Scene_GetMaxCharacters(u32 i) { return sSceneMaxCharacters[i]; }

extern "C" u8 Scene_GetMaxSpNpcs(u32 i) { return sSceneMaxSpNpcs[i]; }

extern "C" u8 Scene_GetMaxFurniture(u32 i) { return sSceneMaxFurniture[i]; }


extern "C" BOOL Scene_NoPlayerInUnsharedScene(void) {
    u32 v;
    s32 i;
    CommManager *p = gCommManager;
    if (!(p)->isSlotActive(p->myAid)) {
        v = Scene_GetCurrent();
        if (v == 12 || v == 13 || v == 14 || (u8)(v + 0xd2) <= 1) return FALSE;
    } else {
        for (i = 3; i >= 0; i--) {
            if ((p)->isSlotActive(i) && !(p)->isMyAid(i)) {
                v = NetArea_GetSlotScene(i);
                if (v == 12 || v == 13 || v == 14 || (u8)(v + 0xd2) <= 1) return FALSE;
            }
        }
    }
    return TRUE;
}


#ifdef HOST64
extern "C" int Scene_HostIsOutdoor(void) { return gCurSceneInfo && gCurSceneInfo->isOutdoor == 1; }
extern "C" int Scene_HostWarp(u32 id, s32 x, s32 z) {
    VecFx32 v;
    v.x = x, v.y = 0, v.z = z;
    return SceneWarp_RequestAt(Scene_GetWarpRequest(), (u8)id, &v, 0x400000, 0, 2, 2);
}
#endif

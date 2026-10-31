#ifndef PROTO_PROTO_MAIN_UNK_020B4828_H
#define PROTO_PROTO_MAIN_UNK_020B4828_H


#include "types.h"
#include "sys/ProcProfile.h"
struct S394;
struct ScenePos;
#ifndef __cplusplus
typedef struct S394 S394;
typedef struct ScenePos ScenePos;
#endif
#ifdef __cplusplus
#include "game/SceneInfo.h"
#include "game/SceneWarp.h"
#include "game/TouchPicker.h"
#include "gfx/GfxFrameHooks.h"
#include "gfx/VecFx32.h"
#include "gfx/ViewFrustum.h"
#include "town/SceneMapInfo.h"
class FieldScene;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_FieldScene_AcquireOv002
void FieldScene_AcquireOv002(void);
#endif
#ifndef PROTO_LOCAL_FieldScene_ReleaseOv002
void FieldScene_ReleaseOv002(void);
#endif
#ifndef PROTO_LOCAL_FieldScene_AcquireInfoOverlays
void FieldScene_AcquireInfoOverlays(u8 *obj);
#endif
#ifndef PROTO_LOCAL_FieldScene_ReleaseInfoOverlays
void FieldScene_ReleaseInfoOverlays(void);
#endif
#ifndef PROTO_LOCAL_FieldScene_AcquireOverlays
void FieldScene_AcquireOverlays(void);
#endif
#ifndef PROTO_LOCAL_FieldScene_ReleaseOverlays
void FieldScene_ReleaseOverlays(void);
#endif
#ifndef PROTO_LOCAL_GroundSeason_CalcPhase
u32 GroundSeason_CalcPhase(void);
#endif
#ifndef PROTO_LOCAL_GroundSeason_GetColor
u16 GroundSeason_GetColor(void);
#endif
#ifndef PROTO_LOCAL_Scene_SetupGraphics
void Scene_SetupGraphics(void);
#endif
#ifndef PROTO_LOCAL_Scene_ShutdownGraphics
s32 Scene_ShutdownGraphics(void);
#endif
#ifndef PROTO_LOCAL_Fog_SetAlpha
void Fog_SetAlpha(u32 v);
#endif
#ifndef PROTO_LOCAL_Fog_SetOffset
void Fog_SetOffset(u16 v);
#endif
#ifndef PROTO_LOCAL_Scene_GetSkyKind
u8 Scene_GetSkyKind(BOOL a);
#endif
#ifndef PROTO_LOCAL_SceneId_GetHouseRoom
s32 SceneId_GetHouseRoom(u32 x);
#endif
#ifndef PROTO_LOCAL_Scene_GetHouseRoom
s32 Scene_GetHouseRoom(void);
#endif
#ifndef PROTO_LOCAL_SceneId_IsHouseRoom
BOOL SceneId_IsHouseRoom(s32 x);
#endif
#ifndef PROTO_LOCAL_Scene_InHouseRoom
BOOL Scene_InHouseRoom(void);
#endif
#ifndef PROTO_LOCAL_SceneId_IsUnk6To8
BOOL SceneId_IsUnk6To8(s32 x);
#endif
#ifndef PROTO_LOCAL_Scene_InUnk6To8
BOOL Scene_InUnk6To8(void);
#endif
#ifndef PROTO_LOCAL_SceneId_IsUnk6Or7
BOOL SceneId_IsUnk6Or7(s32 x);
#endif
#ifndef PROTO_LOCAL_Scene_InUnk6Or7
BOOL Scene_InUnk6Or7(void);
#endif
#ifndef PROTO_LOCAL_SceneId_GetNookShop
s32 SceneId_GetNookShop(u32 x);
#endif
#ifndef PROTO_LOCAL_Scene_GetNookShop
s32 Scene_GetNookShop(void);
#endif
#ifndef PROTO_LOCAL_SceneId_IsNookShop
BOOL SceneId_IsNookShop(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_InNookShop
BOOL Scene_InNookShop();
#endif
#ifndef PROTO_LOCAL_SceneId_GetMuseumRoom
s32 SceneId_GetMuseumRoom(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_GetMuseumRoom
s32 Scene_GetMuseumRoom();
#endif
#ifndef PROTO_LOCAL_SceneId_IsMuseumRoom
BOOL SceneId_IsMuseumRoom(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_InMuseumRoom
BOOL Scene_InMuseumRoom();
#endif
#ifndef PROTO_LOCAL_SceneId_GetVillagerHouse
s32 SceneId_GetVillagerHouse(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_GetVillagerHouse
s32 Scene_GetVillagerHouse();
#endif
#ifndef PROTO_LOCAL_SceneId_IsVillagerHouse
BOOL SceneId_IsVillagerHouse(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_InVillagerHouse
BOOL Scene_InVillagerHouse();
#endif
#ifndef PROTO_LOCAL_SceneId_IsTown
BOOL SceneId_IsTown(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_InTown
BOOL Scene_InTown();
#endif
#ifndef PROTO_LOCAL_SceneId_IsTownUnk31
BOOL SceneId_IsTownUnk31(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_InTownUnk31
BOOL Scene_InTownUnk31();
#endif
#ifndef PROTO_LOCAL_SceneId_AllowsLetterDelivery
BOOL SceneId_AllowsLetterDelivery(u32 a);
#endif
#ifndef PROTO_LOCAL_Scene_AllowsLetterDelivery
BOOL Scene_AllowsLetterDelivery();
#endif
#ifndef PROTO_LOCAL_GroundSeason_IsSnowPhase
BOOL GroundSeason_IsSnowPhase(s32 a);
#endif
#ifndef PROTO_LOCAL_GroundSeason_IsSnow
BOOL GroundSeason_IsSnow();
#endif
#ifndef PROTO_LOCAL_SceneId_IsValid
BOOL SceneId_IsValid(u32 id);
#endif
#ifndef PROTO_LOCAL_Scene_GetRequestedScene
u8 Scene_GetRequestedScene();
#endif
#ifndef PROTO_LOCAL_FieldScene_Request
void FieldScene_Request(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Scene_GetMaxPlayers
u8 Scene_GetMaxPlayers(u32 i);
#endif
#ifndef PROTO_LOCAL_Scene_GetMaxCharacters
u8 Scene_GetMaxCharacters(u32 i);
#endif
#ifndef PROTO_LOCAL_Scene_GetMaxSpNpcs
u8 Scene_GetMaxSpNpcs(u32 i);
#endif
#ifndef PROTO_LOCAL_Scene_GetMaxFurniture
u8 Scene_GetMaxFurniture(u32 i);
#endif
#ifndef PROTO_LOCAL_Scene_NoPlayerInUnsharedScene
BOOL Scene_NoPlayerInUnsharedScene(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_FieldScene_Create
FieldScene *FieldScene_Create(void);
#endif
#ifndef PROTO_LOCAL_Fog_InitDefault
void Fog_InitDefault(FieldScene *a);
#endif
#ifndef PROTO_LOCAL_Fog_Apply
void Fog_Apply(FieldScene *unused);
#endif
#ifndef PROTO_LOCAL_Fog_SetTable
void Fog_SetTable(FieldScene *unused, u8* src);
#endif
#ifndef PROTO_LOCAL_Scene_GetMapInfo
SceneMapInfo *Scene_GetMapInfo(void);
#endif
#ifndef PROTO_LOCAL_Scene_GetTouchPicker
TouchPicker *Scene_GetTouchPicker();
#endif
#ifndef PROTO_LOCAL_ScenePos_Reset
void ScenePos_Reset(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_ScenePos_Set
void ScenePos_Set(ScenePos* i, s32 id, VecFx32* v, u32 w, s16 s, s32 p, s32 q);
#endif
#ifndef PROTO_LOCAL_ScenePos_GetPos
VecFx32* ScenePos_GetPos(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_ScenePos_GetSpawnParam
u32 ScenePos_GetSpawnParam(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_ScenePos_GetAngle
s32 ScenePos_GetAngle(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_ScenePos_GetScene
u8 ScenePos_GetScene(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_ScenePos_GetUnitX
s32 ScenePos_GetUnitX(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_ScenePos_GetUnitZ
s32 ScenePos_GetUnitZ(ScenePos* i);
#endif
#ifndef PROTO_LOCAL_SceneWarp_Init
void SceneWarp_Init(SceneWarp* e, u8 id, VecFx32* v, u32 w, s16 s, u8 p, u8 q, s16 r, u8 t);
#endif
#ifndef PROTO_LOCAL_SceneWarp_RequestScene
BOOL SceneWarp_RequestScene(SceneWarp* e, u8 id);
#endif
#ifndef PROTO_LOCAL_SceneWarp_RequestFade
BOOL SceneWarp_RequestFade(SceneWarp* e, u8 id, u8 p, u8 q);
#endif
#ifndef PROTO_LOCAL_SceneWarp_RequestAt
BOOL SceneWarp_RequestAt(SceneWarp* e, u8 id, VecFx32* v, u32 w, s16 s, u8 p, u8 q);
#endif
#ifndef PROTO_LOCAL_SceneExit_ResolveSpecial
s32 SceneExit_ResolveSpecial(SceneWarp *a, s32 id, u8* type, VecFx32* pos, u32* w, s16* s, s32* x, s32* y, u8* p, u8* q);
#endif
#ifndef PROTO_LOCAL_SceneExit_Resolve
s32 SceneExit_Resolve(SceneWarp *a, s32 id, u8* type, VecFx32* pos, u32* w, s16* s, u8* p, u8* q, s32* ox, s32* oy);
#endif
#ifndef PROTO_LOCAL_SceneWarp_RequestExit
BOOL SceneWarp_RequestExit(SceneWarp *a, s32 id);
#endif
#ifndef PROTO_LOCAL_SceneExit_GetDoor
BOOL SceneExit_GetDoor(SceneWarp *unused, s32 id, u32* type, s16* s);
#endif
#ifndef PROTO_LOCAL_SceneExit_SnapPos
BOOL SceneExit_SnapPos(SceneWarp *a, s32 id, VecFx32* out, VecFx32* in);
#endif
#ifndef PROTO_LOCAL_Scene_SetSavedPos
BOOL Scene_SetSavedPos(SceneWarp *unused, s32 id, VecFx32* pos, u32 w, s16 s, s32 p, s32 q);
#endif
#ifndef PROTO_LOCAL_Scene_SavePlayerPos
void Scene_SavePlayerPos(SceneWarp *unused, s32 add);
#endif
#ifndef PROTO_LOCAL_Scene_SetTownReturnPos
BOOL Scene_SetTownReturnPos(SceneWarp *unused, s32 id, VecFx32* pos, u32 w, s16 s, s32 p, s32 q);
#endif
#ifndef PROTO_LOCAL_Scene_ResetTownReturnPos
void Scene_ResetTownReturnPos(SceneWarp *unused);
#endif
#ifndef PROTO_LOCAL_SceneWarp_Clear
void SceneWarp_Clear(SceneWarp *e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_GetScene
u8 SceneWarp_GetScene(SceneWarp *e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_GetPos
VecFx32* SceneWarp_GetPos(SceneWarp* e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_GetAngle
s32 SceneWarp_GetAngle(SceneWarp* e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_GetSpawnParam
u32 SceneWarp_GetSpawnParam(SceneWarp* e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_HasNoPos
BOOL SceneWarp_HasNoPos(SceneWarp* e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_GetFadeOut
u8 SceneWarp_GetFadeOut(SceneWarp* e);
#endif
#ifndef PROTO_LOCAL_SceneWarp_GetFadeIn
u8 SceneWarp_GetFadeIn(SceneWarp* e);
#endif
#ifndef PROTO_LOCAL_Scene_GetWarpRequest
SceneWarp *Scene_GetWarpRequest(void);
#endif
}
#ifndef PROTO_LOCAL_sDefaultFogTable
extern u8 sDefaultFogTable[0x20];
#endif
#ifndef PROTO_LOCAL_sFieldGfxFrameHooks
extern GfxFrameHooks sFieldGfxFrameHooks;
#endif
#ifndef PROTO_LOCAL_gViewFrustum
extern ViewFrustum gViewFrustum;
#endif
#ifndef PROTO_LOCAL_sSceneInfoTable
extern SceneInfo *sSceneInfoTable[51];
#endif
#ifndef PROTO_LOCAL_sSceneOverlayIds
extern s32 sSceneOverlayIds[51];
#endif
#ifndef PROTO_LOCAL_sTouchPicker
extern TouchPicker sTouchPicker;
#endif
#ifndef PROTO_LOCAL_gCurSceneInfo
extern SceneInfo *gCurSceneInfo;
#endif
#ifndef PROTO_LOCAL_sSceneWarpRequest
extern SceneWarp sSceneWarpRequest;
#endif
#ifndef PROTO_LOCAL_sFieldOverlayIds
extern u32 sFieldOverlayIds[2];
#endif
#ifndef PROTO_LOCAL_sInfoOverlayB
extern s32 sInfoOverlayB;
#endif
#ifndef PROTO_LOCAL_sFieldOverlay
extern s32 sFieldOverlay;
#endif
#ifndef PROTO_LOCAL_sPrevSceneId
extern u8 sPrevSceneId;
#endif
#ifndef PROTO_LOCAL_sSceneOverlay
extern s32 sSceneOverlay;
#endif
#ifndef PROTO_LOCAL_sOverlaySceneId
extern u32 sOverlaySceneId;
#endif
#ifndef PROTO_LOCAL_sCurSceneId
extern u8 sCurSceneId;
#endif
#ifndef PROTO_LOCAL_sSavedScenePos
extern ScenePos sSavedScenePos;
#endif
#ifndef PROTO_LOCAL_sFogState
extern S394 sFogState;
#endif
#ifndef PROTO_LOCAL_gTownReturnPos
extern ScenePos gTownReturnPos;
#endif
#ifndef PROTO_LOCAL_data_021ef2d4
extern u8 data_021ef2d4;
#endif
#ifndef PROTO_LOCAL_sSceneFieldKinds
extern u8 sSceneFieldKinds[0x34];
#endif
#ifndef PROTO_LOCAL_sFieldSceneProfile
extern ProcProfile sFieldSceneProfile;
#endif
#ifndef PROTO_LOCAL_sInfoOverlayA
extern s32 sInfoOverlayA;
#endif
#endif

#endif

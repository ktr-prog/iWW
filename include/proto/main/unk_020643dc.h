#ifndef PROTO_PROTO_MAIN_UNK_020643DC_H
#define PROTO_PROTO_MAIN_UNK_020643DC_H


#include "types.h"
#include "gfx/Mtx43.h"
#include "nitro/mtx.h"
#include "sys/ListNode.h"
#include "sys/ProcProfile.h"
struct IdListNode;
struct LightSwitchState;
#ifndef __cplusplus
typedef struct IdListNode IdListNode;
typedef struct LightSwitchState LightSwitchState;
#endif
#ifdef __cplusplus
#include "gfx/DebugColor.h"
#include "gfx/VecFx32.h"
#include "sys/PrioListNode.h"
class SceneLights;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PrioList_Init
void PrioList_Init(List *list);
#endif
#ifndef PROTO_LOCAL_PrioList_PushBack
BOOL PrioList_PushBack(List *list, ListNode *node);
#endif
#ifndef PROTO_LOCAL_SceneLights_GetMatLightMask
s32 SceneLights_GetMatLightMask(void);
#endif
#ifndef PROTO_LOCAL_SceneLights_GetMatLightMask2
s32 SceneLights_GetMatLightMask2(void);
#endif
#ifndef PROTO_LOCAL_SceneLights_GetFlashColor
s16 SceneLights_GetFlashColor(void);
#endif
#ifndef PROTO_LOCAL_SceneLights_GetBaseColor
s16 SceneLights_GetBaseColor(void);
#endif
#ifndef PROTO_LOCAL_SceneLights_GetRoomColor
s16 SceneLights_GetRoomColor(void);
#endif
#ifndef PROTO_LOCAL_SceneLights_GetLightParam
u8 SceneLights_GetLightParam(u32 x);
#endif
#ifndef PROTO_LOCAL_SceneLights_StartFlash
void SceneLights_StartFlash(u32 v);
#endif
#ifndef PROTO_LOCAL_SceneLight_InitStub
void SceneLight_InitStub(void *);
#endif
#ifndef PROTO_LOCAL_LightSwitch_SetOn
void LightSwitch_SetOn(s32 i, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_LightSwitch_SetOff
void LightSwitch_SetOff(s32 i, u32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PrioList_Insert
BOOL PrioList_Insert(List *list, PrioListNode *node);
#endif
#ifndef PROTO_LOCAL_PrioList_FindById
IdListNode *PrioList_FindById(List *list, s32 key);
#endif
#ifndef PROTO_LOCAL_SceneLights_Create
SceneLights *SceneLights_Create(void);
#endif
#ifndef PROTO_LOCAL_Light_GetViewRotation
void Light_GetViewRotation(Mtx43 *a, MtxFx33 *b);
#endif
#ifndef PROTO_LOCAL_Light_ClampDir
void Light_ClampDir(VecFx32 *in, VecFx32 *out);
#endif
}
#ifndef PROTO_LOCAL_data_021c9f58
extern DebugColor data_021c9f58;
#endif
#ifndef PROTO_LOCAL_sSceneLightsProfile
extern ProcProfile sSceneLightsProfile;
#endif
#ifndef PROTO_LOCAL_data_021c9f54
extern DebugColor data_021c9f54;
#endif
#ifndef PROTO_LOCAL_data_021c9f50
extern DebugColor data_021c9f50;
#endif
#ifndef PROTO_LOCAL_data_021c9f48
extern DebugColor data_021c9f48;
#endif
#ifndef PROTO_LOCAL_sLightSwitchState
extern LightSwitchState sLightSwitchState;
#endif
#ifndef PROTO_LOCAL_data_021c9f4c
extern DebugColor data_021c9f4c;
#endif
#ifndef PROTO_LOCAL_data_021c9f40
extern DebugColor data_021c9f40;
#endif
#ifndef PROTO_LOCAL_gSceneLights
extern SceneLights *gSceneLights;
#endif
#endif

#endif

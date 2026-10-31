#ifndef PROTO_PROTO_MAIN_UNK_020116E0_H
#define PROTO_PROTO_MAIN_UNK_020116E0_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/HudObjGfx.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HudObjGfx_LoadForScene
void HudObjGfx_LoadForScene(void);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_LoadForSceneSub
void HudObjGfx_LoadForSceneSub(void);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_LoadKind
void HudObjGfx_LoadKind(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_LoadCameraButton
void HudObjGfx_LoadCameraButton(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_SetCountdownVariant
void HudObjGfx_SetCountdownVariant(u8 v);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_GetCountdownVariant
u8 HudObjGfx_GetCountdownVariant(void);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_LoadLinkIcon
void HudObjGfx_LoadLinkIcon(u32 a);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_LoadSlideIcon
void HudObjGfx_LoadSlideIcon(u32 a);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_FlushCameraButton
void HudObjGfx_FlushCameraButton(void);
#endif
#ifndef PROTO_LOCAL_Hud_GetSceneHudKind
s32 Hud_GetSceneHudKind(void);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_IsMsgUiActive
u8 HudObjGfx_IsMsgUiActive(void);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_SetMsgUiActive
void HudObjGfx_SetMsgUiActive(void);
#endif
#ifndef PROTO_LOCAL_HudObjGfx_ClearMsgUiActive
void HudObjGfx_ClearMsgUiActive(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HudObjGfx_InitFile
void HudObjGfx_InitFile(HudObjGfx *p);
#endif
}
#ifndef PROTO_LOCAL_sHudObjGfx
extern HudObjGfx sHudObjGfx;
#endif
#endif

#endif

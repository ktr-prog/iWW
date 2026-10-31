#ifndef PROTO_PROTO_MAIN_UNK_0203A0CC_H
#define PROTO_PROTO_MAIN_UNK_0203A0CC_H


#include "types.h"
#include "sys/ProcProfile.h"
struct CameraModeEntry;
#ifndef __cplusplus
typedef struct CameraModeEntry CameraModeEntry;
#endif
#ifdef __cplusplus
#include "gfx/Camera.h"
#include "gfx/CameraSetup.h"
#include "gfx/DebugColor.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CarpetTex_GetTex
void *CarpetTex_GetTex(void *p);
#endif
#ifndef PROTO_LOCAL_Camera_SetModeDefault
BOOL Camera_SetModeDefault(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode1
s32 Camera_SetMode1(void);
#endif
#ifndef PROTO_LOCAL_Camera_StartShake
void Camera_StartShake(s32 a);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode19
void Camera_SetMode19(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode3
void Camera_SetMode3(void);
#endif
#ifndef PROTO_LOCAL_Camera_RestorePrevMode
s32 Camera_RestorePrevMode(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode4
void Camera_SetMode4(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode5
void Camera_SetMode5(void);
#endif
#ifndef PROTO_LOCAL_Camera_GetCloseUpFactor
s32 Camera_GetCloseUpFactor(void);
#endif
#ifndef PROTO_LOCAL_Camera_IsBlending
BOOL Camera_IsBlending(void);
#endif
#ifndef PROTO_LOCAL_Camera_FinishBlend
void Camera_FinishBlend(void);
#endif
#ifndef PROTO_LOCAL_Camera_StartBlend
void Camera_StartBlend(void);
#endif
#ifndef PROTO_LOCAL_Camera_GetBlendFramesLeft
u8 Camera_GetBlendFramesLeft(void);
#endif
#ifndef PROTO_LOCAL_Camera_SaveView
void Camera_SaveView(void);
#endif
#ifndef PROTO_LOCAL_Camera_RestoreView
void Camera_RestoreView(void);
#endif
#ifndef PROTO_LOCAL_Camera_IsViewPushed
BOOL Camera_IsViewPushed(void);
#endif
#ifndef PROTO_LOCAL_Camera_PushView
BOOL Camera_PushView(void);
#endif
#ifndef PROTO_LOCAL_Camera_PopView
BOOL Camera_PopView(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetSwayPattern3
void Camera_SetSwayPattern3(void);
#endif
#ifndef PROTO_LOCAL_Camera_LockFocusYaw
void Camera_LockFocusYaw(void);
#endif
#ifndef PROTO_LOCAL_Camera_MuteSe
void Camera_MuteSe(void);
#endif
#ifndef PROTO_LOCAL_Camera_UnmuteSe
void Camera_UnmuteSe(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetPresetCell
BOOL Camera_SetPresetCell(s32 a, s32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Camera_Create
Camera *Camera_Create();
#endif
#ifndef PROTO_LOCAL_Camera_GetLookAtBlock
void Camera_GetLookAtBlock(Camera *a, s32 *x, s32 *z);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateModeShake
void Camera_UpdateModeShake(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode19
BOOL Camera_InitMode19(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode19
void Camera_UpdateMode19(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_CalcPointSpan
s32 Camera_CalcPointSpan(VecFx32 *a, VecFx32 *b, VecFx32 *c, s32 *d);
#endif
#ifndef PROTO_LOCAL_Camera_CalcTriangleSpan
s32 Camera_CalcTriangleSpan(VecFx32 *a, VecFx32 *b, VecFx32 *c, VecFx32 *d, s32 *e);
#endif
#ifndef PROTO_LOCAL_Camera_FocusOnPoint
BOOL Camera_FocusOnPoint(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_Camera_FocusOnPair
void Camera_FocusOnPair(VecFx32 *a, VecFx32 *b);
#endif
#ifndef PROTO_LOCAL_Camera_RetargetFocus
BOOL Camera_RetargetFocus(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Camera_IsBlockingFocusView
BOOL Camera_IsBlockingFocusView(VecFx32 *v, s32 unused, s32 h);
#endif
#ifndef PROTO_LOCAL_Camera_SnapToFocus
void Camera_SnapToFocus(VecFx32 *a);
#endif
#ifndef PROTO_LOCAL_Camera_PlaySe
void Camera_PlaySe(Camera *o, s32 a);
#endif
#ifndef PROTO_LOCAL_Camera_ProjectToScreen
BOOL Camera_ProjectToScreen(s32 *x, s32 *y, VecFx32 *p);
#endif
#ifndef PROTO_LOCAL_Camera_ProjectCurvedToScreen
BOOL Camera_ProjectCurvedToScreen(s32 *x, s32 *y, VecFx32 *p);
#endif
}
#ifndef PROTO_LOCAL_data_021c3060
extern DebugColor data_021c3060;
#endif
#ifndef PROTO_LOCAL_data_021c3074
extern DebugColor data_021c3074;
#endif
#ifndef PROTO_LOCAL_data_021c3064
extern DebugColor data_021c3064;
#endif
#ifndef PROTO_LOCAL_data_021c305c
extern DebugColor data_021c305c;
#endif
#ifndef PROTO_LOCAL_data_021c3058
extern DebugColor data_021c3058;
#endif
#ifndef PROTO_LOCAL_data_021c306c
extern DebugColor data_021c306c;
#endif
#ifndef PROTO_LOCAL_sCameraSavedSetup
extern CameraSetup sCameraSavedSetup;
#endif
#ifndef PROTO_LOCAL_sCameraModeTable
extern CameraModeEntry sCameraModeTable[21];
#endif
#ifndef PROTO_LOCAL_gCameraDistance
extern s32 gCameraDistance;
#endif
#ifndef PROTO_LOCAL_sCameraProfile
extern ProcProfile sCameraProfile;
#endif
#endif

#endif

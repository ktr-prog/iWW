#ifndef PROTO_PROTO_OV004_UNK_OV004_0223F43C_H
#define PROTO_PROTO_OV004_UNK_OV004_0223F43C_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/Camera.h"
#include "gfx/DebugColor.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Camera_GetShopTier
s32 Camera_GetShopTier();
#endif
#ifndef PROTO_LOCAL_Camera_SetMode11
BOOL Camera_SetMode11();
#endif
#ifndef PROTO_LOCAL_Camera_SetMode12
BOOL Camera_SetMode12();
#endif
#ifndef PROTO_LOCAL_Camera_SetMode14
void Camera_SetMode14(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode15
void Camera_SetMode15(void);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode18
void Camera_SetMode18(void);
#endif
#ifndef PROTO_LOCAL_RoomCamera_KkShowWideShot
void RoomCamera_KkShowWideShot(void);
#endif
#ifndef PROTO_LOCAL_RoomCamera_KkShowPickShot
void RoomCamera_KkShowPickShot(void);
#endif
#ifndef PROTO_LOCAL_RoomCamera_KkShowResetShot
void RoomCamera_KkShowResetShot(void);
#endif
#ifndef PROTO_LOCAL_RoomCamera_StartBlendToPlayer
void RoomCamera_StartBlendToPlayer(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Camera_UpdateRoomFocus
void Camera_UpdateRoomFocus(Camera *self);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode10
BOOL Camera_InitMode10(Camera *self);
#endif
#ifndef PROTO_LOCAL_Camera_StartBlendToPlayer
BOOL Camera_StartBlendToPlayer(Camera *self);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode10
void Camera_UpdateMode10(Camera *self);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode11
BOOL Camera_InitMode11(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode11
void Camera_UpdateMode11(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode12
BOOL Camera_InitMode12(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode12
void Camera_UpdateMode12(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode16At
BOOL Camera_SetMode16At(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode16
BOOL Camera_InitMode16(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode16
void Camera_UpdateMode16(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode14
BOOL Camera_InitMode14(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode14
void Camera_UpdateMode14(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode15
BOOL Camera_InitMode15(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode15
void Camera_UpdateMode15(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode20
BOOL Camera_InitMode20(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode20
void Camera_UpdateMode20(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_SetMode20At
void Camera_SetMode20At(VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_Camera_InitMode18
BOOL Camera_InitMode18(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateMode18
void Camera_UpdateMode18(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_KkShowWideShot
void Camera_KkShowWideShot(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_KkShowPickShot
void Camera_KkShowPickShot(Camera *o);
#endif
#ifndef PROTO_LOCAL_Camera_KkShowResetShot
void Camera_KkShowResetShot(Camera *o);
#endif
}
#ifndef PROTO_LOCAL_data_ov004_022589a4
extern DebugColor data_ov004_022589a4;
#endif
#ifndef PROTO_LOCAL_data_ov004_02258994
extern DebugColor data_ov004_02258994;
#endif
#ifndef PROTO_LOCAL_data_ov004_02258990
extern DebugColor data_ov004_02258990;
#endif
#ifndef PROTO_LOCAL_data_ov004_022589a0
extern DebugColor data_ov004_022589a0;
#endif
#ifndef PROTO_LOCAL_data_ov004_02258998
extern DebugColor data_ov004_02258998;
#endif
#ifndef PROTO_LOCAL_data_ov004_0225899c
extern DebugColor data_ov004_0225899c;
#endif
#endif

#endif

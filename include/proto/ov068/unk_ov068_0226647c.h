#ifndef PROTO_PROTO_OV068_UNK_OV068_0226647C_H
#define PROTO_PROTO_OV068_UNK_OV068_0226647C_H


#include "types.h"
struct TownTourBuildingRange;
#ifndef __cplusplus
typedef struct TownTourBuildingRange TownTourBuildingRange;
#endif
#ifdef __cplusplus
#include "gfx/Camera.h"
#include "gfx/DebugColor.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov068_0226fc48
extern s32 data_ov068_0226fc48;
#endif
#ifndef PROTO_LOCAL_data_ov068_0226fc44
extern s32 data_ov068_0226fc44;
#endif
#ifndef PROTO_LOCAL_data_ov068_0226fc40
extern s32 data_ov068_0226fc40;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sTownTourOffsets
extern VecFx32 *sTownTourOffsets[7];
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetVillagerHouse
extern VecFx32 sTownTourOffsetVillagerHouse;
#endif
#ifndef PROTO_LOCAL_data_ov068_02270fd4
extern DebugColor data_ov068_02270fd4;
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetsNookShop
extern VecFx32 sTownTourOffsetsNookShop[4];
#endif
#ifndef PROTO_LOCAL_data_ov068_02270fd0
extern DebugColor data_ov068_02270fd0;
#endif
#ifndef PROTO_LOCAL_data_ov068_02270fc4
extern DebugColor data_ov068_02270fc4;
#endif
#ifndef PROTO_LOCAL_data_ov068_02270fc8
extern DebugColor data_ov068_02270fc8;
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetTownHall
extern VecFx32 sTownTourOffsetTownHall;
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetMuseum
extern VecFx32 sTownTourOffsetMuseum;
#endif
#ifndef PROTO_LOCAL_data_ov068_02270fd8
extern DebugColor data_ov068_02270fd8;
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetAbleSisters
extern VecFx32 sTownTourOffsetAbleSisters;
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetPlayerHouse
extern VecFx32 sTownTourOffsetPlayerHouse;
#endif
#ifndef PROTO_LOCAL_sTownTourOffsetGateHouse
extern VecFx32 sTownTourOffsetGateHouse;
#endif
#ifndef PROTO_LOCAL_sTownTourBuildings
extern TownTourBuildingRange sTownTourBuildings[7];
#endif
#ifndef PROTO_LOCAL_data_ov068_02270fcc
extern DebugColor data_ov068_02270fcc;
#endif
#ifndef PROTO_LOCAL_CameraEventModes_InitModeFollowTarget
BOOL CameraEventModes_InitModeFollowTarget(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_UpdateModeFollowTarget
void CameraEventModes_UpdateModeFollowTarget(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_InitModeTownTour
BOOL CameraEventModes_InitModeTownTour(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_UpdateModeTownTour
void CameraEventModes_UpdateModeTownTour(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_InitMode13
BOOL CameraEventModes_InitMode13(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_UpdateMode13
void CameraEventModes_UpdateMode13(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_InitModeSway
BOOL CameraEventModes_InitModeSway(Camera *c);
#endif
#ifndef PROTO_LOCAL_CameraEventModes_UpdateModeSway
void CameraEventModes_UpdateModeSway(Camera *c);
#endif
#ifndef PROTO_LOCAL_Camera_SetSwayPattern
void Camera_SetSwayPattern(Camera *c, s32 idx);
#endif
#ifndef PROTO_LOCAL_Camera_SetSwayPattern2
void Camera_SetSwayPattern2(Camera *c, s32 idx);
#endif
#ifndef PROTO_LOCAL_Camera_UpdateSway
s32 Camera_UpdateSway(Camera *c);
#endif
}
#endif

#endif

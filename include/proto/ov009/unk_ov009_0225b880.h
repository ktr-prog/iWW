#ifndef PROTO_PROTO_OV009_UNK_OV009_0225B880_H
#define PROTO_PROTO_OV009_UNK_OV009_0225B880_H


#include "types.h"
#include "gfx/Mtx43.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#include "gfx/NNSG3dRS.h"
#include "gfx/VecFx32.h"
#include "town/BuildingResources.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_BuildingActor_Create
void *BuildingActor_Create();
#endif
#ifndef PROTO_LOCAL_Building_GetFirstAnm
void *Building_GetFirstAnm(void *res);
#endif
#ifndef PROTO_LOCAL_Building_IsNight
BOOL Building_IsNight();
#endif
#ifndef PROTO_LOCAL_sBuildingDefaultMsgFile
extern char sBuildingDefaultMsgFile[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e3ec
extern char data_ov009_0225e3ec[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e3fc
extern char data_ov009_0225e3fc[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e40c
extern char data_ov009_0225e40c[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e41c
extern char data_ov009_0225e41c[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e42c
extern char data_ov009_0225e42c[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e43c
extern char data_ov009_0225e43c[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e44c
extern char data_ov009_0225e44c[16];
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e45c
extern char data_ov009_0225e45c[24];
#endif
#ifndef PROTO_LOCAL_sBuildingLightTexPathFmt
extern char sBuildingLightTexPathFmt[32];
#endif
#ifndef PROTO_LOCAL_sBuildingTexPathFmt
extern char sBuildingTexPathFmt[28];
#endif
#ifndef PROTO_LOCAL_sBuildingArcPathFmt
extern char sBuildingArcPathFmt[24];
#endif
#ifndef PROTO_LOCAL_sBuildingArcPath
extern char sBuildingArcPath[32];
#endif
#ifndef PROTO_LOCAL_sBuildingTexPath
extern char sBuildingTexPath[32];
#endif
#ifndef PROTO_LOCAL_sBuildingLightTexPath
extern char sBuildingLightTexPath[32];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Building_LocalToWorld
void Building_LocalToWorld(VecFx32 *p, const VecFx32 *a, const Mtx43 *b);
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e4fc
extern DebugColor data_ov009_0225e4fc;
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e4e0
extern DebugColor data_ov009_0225e4e0;
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e4f4
extern DebugColor data_ov009_0225e4f4;
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e4f0
extern DebugColor data_ov009_0225e4f0;
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e500
extern DebugColor data_ov009_0225e500;
#endif
#ifndef PROTO_LOCAL_data_ov009_0225e4f8
extern DebugColor data_ov009_0225e4f8;
#endif
#ifndef PROTO_LOCAL_sBuildingResources
extern BuildingResources sBuildingResources[0x22];
#endif
#ifndef PROTO_LOCAL_BuildingResources_IsLoaded
BOOL BuildingResources_IsLoaded(BuildingResources *e);
#endif
#ifndef PROTO_LOCAL_Building_ModelCallback
void Building_ModelCallback(NNSG3dRS *a);
#endif
#ifndef PROTO_LOCAL_Building_InitModelCallback
void Building_InitModelCallback(NNSG3dRS *o);
#endif
#ifndef PROTO_LOCAL_Building_GetFirstMdl
NNSG3dResMdl *Building_GetFirstMdl(void *res);
#endif
#ifndef PROTO_LOCAL_sBuildingActorProfile
extern ActorProfile sBuildingActorProfile;
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV003_UNK_OV003_022187F8_H
#define PROTO_PROTO_OV003_UNK_OV003_022187F8_H


#include "types.h"
#ifdef __cplusplus
#include "field/FieldStructureMgr.h"
#include "game/FxVec3.h"
#include "game/SceneInfo.h"
#include "game/SceneWarp.h"
class PlayerHouseTex;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sFieldSceneProfiles
extern u32 sFieldSceneProfiles[14];
#endif
#ifndef PROTO_LOCAL_sFieldSceneProfileCount
extern u32 sFieldSceneProfileCount;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov003_022355a0
extern FxVec3 data_ov003_022355a0;
#endif
#ifndef PROTO_LOCAL_sFieldSceneObjects
extern SceneWarp sFieldSceneObjects[21];
#endif
#ifndef PROTO_LOCAL_sFieldSceneObjectList
extern SceneWarpList sFieldSceneObjectList;
#endif
#ifndef PROTO_LOCAL_PlayerHouseTex_Get
NNSG3dResTex *PlayerHouseTex_Get(PlayerHouseTex *p);
#endif
}
#endif

#endif

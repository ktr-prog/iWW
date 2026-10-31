#ifndef PROTO_PROTO_MAIN_UNK_0204C50C_H
#define PROTO_PROTO_MAIN_UNK_0204C50C_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "town/BlockMap.h"
#include "town/SceneMapModule.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SceneMapModule_New
SceneMapModule *SceneMapModule_New();
#endif
#ifndef PROTO_LOCAL_BlockMap_GetForArea
BlockMap *BlockMap_GetForArea(s32 a);
#endif
#ifndef PROTO_LOCAL_Town_ClearBorderTrees
void Town_ClearBorderTrees(BlockMap *p);
#endif
}
#ifndef PROTO_LOCAL_data_020da3c4
extern ProcProfile data_020da3c4;
#endif
#endif

#endif

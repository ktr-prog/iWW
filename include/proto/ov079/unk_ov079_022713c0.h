#ifndef PROTO_PROTO_OV079_UNK_OV079_022713C0_H
#define PROTO_PROTO_OV079_UNK_OV079_022713C0_H


#include "types.h"
struct SpNpcWendellActEntry;
#ifndef __cplusplus
typedef struct SpNpcWendellActEntry SpNpcWendellActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "game/FxVec3.h"
#include "gfx/DebugColor.h"
class SpNpcWendell;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcWendellTexturePath
extern u8 sSpNpcWendellTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcWendellModelPath
extern u8 sSpNpcWendellModelPath[];
#endif
#ifndef PROTO_LOCAL_SpNpcWendell_AcceptAnyItem
BOOL SpNpcWendell_AcceptAnyItem(u16 *p, s32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcWendell_Create
SpNpcWendell *SpNpcWendell_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcWendellProfile
extern ActorProfile sSpNpcWendellProfile;
#endif
#ifndef PROTO_LOCAL_data_ov079_02272b80
extern DebugColor data_ov079_02272b80;
#endif
#ifndef PROTO_LOCAL_data_ov079_02272b8c
extern DebugColor data_ov079_02272b8c;
#endif
#ifndef PROTO_LOCAL_data_ov079_02272b94
extern DebugColor data_ov079_02272b94;
#endif
#ifndef PROTO_LOCAL_data_ov079_02272b98
extern DebugColor data_ov079_02272b98;
#endif
#ifndef PROTO_LOCAL_data_ov079_02272b88
extern DebugColor data_ov079_02272b88;
#endif
#ifndef PROTO_LOCAL_data_ov079_02272b90
extern DebugColor data_ov079_02272b90;
#endif
#ifndef PROTO_LOCAL_sSpNpcWendellActTable
extern SpNpcWendellActEntry sSpNpcWendellActTable[5];
#endif
#ifndef PROTO_LOCAL_sSpNpcWendellSideStepOffsets
extern FxVec3 sSpNpcWendellSideStepOffsets[2];
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV070_UNK_022713C0_H
#define PROTO_PROTO_OV070_UNK_022713C0_H


#include "types.h"
struct SpNpcGracieActEntry;
#ifndef __cplusplus
typedef struct SpNpcGracieActEntry SpNpcGracieActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
class SpNpcGracie;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov070_022726e4
extern u32 data_ov070_022726e4[1];
#endif
#ifndef PROTO_LOCAL_sSpNpcGracieTexturePath
extern u8 sSpNpcGracieTexturePath[];
#endif
#ifndef PROTO_LOCAL_data_ov070_022726e0
extern u32 data_ov070_022726e0[1];
#endif
#ifndef PROTO_LOCAL_sSpNpcGracieModelPath
extern u8 sSpNpcGracieModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcGracieKey
extern u8 sSpNpcGracieKey[];
#endif
#ifndef PROTO_LOCAL_SpNpcGracie_CountUnaskedQuestions
s32 SpNpcGracie_CountUnaskedQuestions(void *unused, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_SpNpcGracie_PickUnaskedQuestion
s32 SpNpcGracie_PickUnaskedQuestion(void *unused, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_SpNpcGracie_ScoreByPrice
u8 SpNpcGracie_ScoreByPrice(void *unused, s32 a, s32 kind);
#endif
#ifndef PROTO_LOCAL_SpNpcGracie_IsEmptyItem
BOOL SpNpcGracie_IsEmptyItem(u16 *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcGracie_Create
SpNpcGracie *SpNpcGracie_Create();
#endif
#ifndef PROTO_LOCAL_data_ov070_022728c0
extern DebugColor data_ov070_022728c0;
#endif
#ifndef PROTO_LOCAL_data_ov070_022728c8
extern DebugColor data_ov070_022728c8;
#endif
#ifndef PROTO_LOCAL_data_ov070_022728d8
extern DebugColor data_ov070_022728d8;
#endif
#ifndef PROTO_LOCAL_data_ov070_022728d4
extern DebugColor data_ov070_022728d4;
#endif
#ifndef PROTO_LOCAL_data_ov070_022728cc
extern DebugColor data_ov070_022728cc;
#endif
#ifndef PROTO_LOCAL_data_ov070_022728c4
extern DebugColor data_ov070_022728c4;
#endif
#ifndef PROTO_LOCAL_sSpNpcGracieProfile
extern ActorProfile sSpNpcGracieProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcGracieActTable
extern SpNpcGracieActEntry sSpNpcGracieActTable[3];
#endif
}
#endif

#endif

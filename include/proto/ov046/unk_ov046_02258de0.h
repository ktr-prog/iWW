#ifndef PROTO_PROTO_OV046_UNK_OV046_02258DE0_H
#define PROTO_PROTO_OV046_UNK_OV046_02258DE0_H


#include "types.h"
struct SpNpcCelesteActEntry;
#ifndef __cplusplus
typedef struct SpNpcCelesteActEntry SpNpcCelesteActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "gfx/DebugColor.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcCeleste_Create
void *SpNpcCeleste_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcCelesteModelPath
extern u8 sSpNpcCelesteModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcCelesteTexturePath
extern u8 sSpNpcCelesteTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcCelesteKey
extern u8 sSpNpcCelesteKey[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov046_0225ae04
extern DebugColor data_ov046_0225ae04;
#endif
#ifndef PROTO_LOCAL_data_ov046_0225ae08
extern DebugColor data_ov046_0225ae08;
#endif
#ifndef PROTO_LOCAL_data_ov046_0225ae20
extern DebugColor data_ov046_0225ae20;
#endif
#ifndef PROTO_LOCAL_data_ov046_0225ae10
extern DebugColor data_ov046_0225ae10;
#endif
#ifndef PROTO_LOCAL_data_ov046_0225ae00
extern DebugColor data_ov046_0225ae00;
#endif
#ifndef PROTO_LOCAL_data_ov046_0225ae0c
extern DebugColor data_ov046_0225ae0c;
#endif
#ifndef PROTO_LOCAL_sSpNpcCelesteProfile
extern ActorProfile sSpNpcCelesteProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcCelesteActTable
extern SpNpcCelesteActEntry sSpNpcCelesteActTable[5];
#endif
#endif

#endif

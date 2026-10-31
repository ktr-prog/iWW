#ifndef PROTO_PROTO_OV053_UNK_OV053_02258DE0_H
#define PROTO_PROTO_OV053_UNK_OV053_02258DE0_H


#include "types.h"
struct SpNpcHarrietActEntry;
#ifndef __cplusplus
typedef struct SpNpcHarrietActEntry SpNpcHarrietActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcHarriet;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcHarrietTexturePath
extern u8 sSpNpcHarrietTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcHarrietKey
extern char sSpNpcHarrietKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcHarrietModelPath
extern u8 sSpNpcHarrietModelPath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcHarrietProfile
extern ActorProfile sSpNpcHarrietProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcHarrietActTable
extern SpNpcHarrietActEntry sSpNpcHarrietActTable[11];
#endif
#ifndef PROTO_LOCAL_SpNpcHarriet_Create
SpNpcHarriet *SpNpcHarriet_Create();
#endif
}
#endif

#endif

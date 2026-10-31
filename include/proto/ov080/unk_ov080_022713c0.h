#ifndef PROTO_PROTO_OV080_UNK_OV080_022713C0_H
#define PROTO_PROTO_OV080_UNK_OV080_022713C0_H


#include "types.h"
struct SpNpcTortimerActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimerActEntry SpNpcTortimerActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimer;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerTexturePath
extern u8 sSpNpcTortimerTexturePath[27];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerModelPath
extern u8 sSpNpcTortimerModelPath[23];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcTortimerProfile
extern ActorProfile sSpNpcTortimerProfile;
#endif
#ifndef PROTO_LOCAL_SpNpcTortimer_Create
SpNpcTortimer *SpNpcTortimer_Create();
#endif
}
#ifndef PROTO_LOCAL_sSpNpcTortimerActTable
extern SpNpcTortimerActEntry sSpNpcTortimerActTable[3];
#endif
#endif

#endif

#ifndef PROTO_PROTO_OV085_UNK_OV085_022713C0_H
#define PROTO_PROTO_OV085_UNK_OV085_022713C0_H


#include "types.h"
struct SpNpcTortimerBrightNightsActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimerBrightNightsActEntry SpNpcTortimerBrightNightsActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimerBrightNights;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerBrightNightsTexturePath
extern u8 sSpNpcTortimerBrightNightsTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerBrightNightsModelPath
extern u8 sSpNpcTortimerBrightNightsModelPath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcTortimerBrightNightsProfile
extern ActorProfile sSpNpcTortimerBrightNightsProfile;
#endif
#ifndef PROTO_LOCAL_SpNpcTortimerBrightNights_Create
SpNpcTortimerBrightNights *SpNpcTortimerBrightNights_Create();
#endif
}
#ifndef PROTO_LOCAL_sSpNpcTortimerBrightNightsActTable
extern SpNpcTortimerBrightNightsActEntry sSpNpcTortimerBrightNightsActTable[3];
#endif
#endif

#endif

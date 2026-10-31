#ifndef PROTO_PROTO_OV083_UNK_OV083_022713C0_H
#define PROTO_PROTO_OV083_UNK_OV083_022713C0_H


#include "types.h"
struct SpNpcTortimerFlowerFestActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimerFlowerFestActEntry SpNpcTortimerFlowerFestActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimerFlowerFest;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerFlowerFestTexturePath
extern u8 sSpNpcTortimerFlowerFestTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerFlowerFestModelPath
extern u8 sSpNpcTortimerFlowerFestModelPath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcTortimerFlowerFestProfile
extern ActorProfile sSpNpcTortimerFlowerFestProfile;
#endif
#ifndef PROTO_LOCAL_SpNpcTortimerFlowerFest_Create
SpNpcTortimerFlowerFest *SpNpcTortimerFlowerFest_Create();
#endif
}
#ifndef PROTO_LOCAL_sSpNpcTortimerFlowerFestActTable
extern SpNpcTortimerFlowerFestActEntry sSpNpcTortimerFlowerFestActTable[3];
#endif
#endif

#endif

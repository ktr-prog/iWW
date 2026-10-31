#ifndef PROTO_PROTO_OV081_UNK_OV081_022713C0_H
#define PROTO_PROTO_OV081_UNK_OV081_022713C0_H


#include "types.h"
struct SpNpcTortimerFishingTourneyActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimerFishingTourneyActEntry SpNpcTortimerFishingTourneyActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimerFishingTourney;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerFishingTourneyTexturePath
extern u8 sSpNpcTortimerFishingTourneyTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerFishingTourneyModelPath
extern u8 sSpNpcTortimerFishingTourneyModelPath[];
#endif
#ifndef PROTO_LOCAL_SpNpcTortimerFishingTourney_IsFish
BOOL SpNpcTortimerFishingTourney_IsFish(u16 *p, s32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcTortimerFishingTourney_Create
SpNpcTortimerFishingTourney *SpNpcTortimerFishingTourney_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerFishingTourneyProfile
extern ActorProfile sSpNpcTortimerFishingTourneyProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcTortimerFishingTourneyActTable
extern SpNpcTortimerFishingTourneyActEntry sSpNpcTortimerFishingTourneyActTable[3];
#endif
#endif

#endif

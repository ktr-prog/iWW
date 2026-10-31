#ifndef PROTO_PROTO_OV004_UNK_OV004_02216CCC_H
#define PROTO_PROTO_OV004_UNK_OV004_02216CCC_H


#include "types.h"
struct HouseOwnerAiState;
struct HouseOwnerStepDir;
#ifndef __cplusplus
typedef struct HouseOwnerAiState HouseOwnerAiState;
typedef struct HouseOwnerStepDir HouseOwnerStepDir;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class HouseOwnerVillager;
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sHouseOwnerVillagerProfile
extern ActorProfile sHouseOwnerVillagerProfile;
#endif
#ifndef PROTO_LOCAL_HouseOwnerVillager_Create
HouseOwnerVillager *HouseOwnerVillager_Create();
#endif
#ifndef PROTO_LOCAL_sHouseOwnerAiStates
extern HouseOwnerAiState sHouseOwnerAiStates[5];
#endif
#ifndef PROTO_LOCAL_sHouseOwnerStepDirs
extern HouseOwnerStepDir sHouseOwnerStepDirs[4];
#endif
}
#endif

#endif

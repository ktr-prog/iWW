#ifndef PROTO_PROTO_OV004_UNK_OV004_02235FD0_H
#define PROTO_PROTO_OV004_UNK_OV004_02235FD0_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "actor/Actor.h"
#include "actor/ActorProfile.h"
class HouseRoach;
class HouseRoachManager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_HouseRoach_SpawnFromFurniture
BOOL HouseRoach_SpawnFromFurniture(void *pos, u16 *angle);
#endif
#ifndef PROTO_LOCAL_HouseRoach_FindVillager
void HouseRoach_FindVillager(void *);
#endif
#ifndef PROTO_LOCAL_sHouseRoachModelPath
extern char sHouseRoachModelPath[0x18];
#endif
#ifndef PROTO_LOCAL_sHouseRoachTurnCounter
extern s8 sHouseRoachTurnCounter;
#endif
#ifndef PROTO_LOCAL_sHouseRoachActiveCount
extern volatile u8 sHouseRoachActiveCount;
#endif
#ifndef PROTO_LOCAL_sHouseRoachTotal
extern volatile u8 sHouseRoachTotal;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_HouseRoachManager_Create
HouseRoachManager *HouseRoachManager_Create();
#endif
#ifndef PROTO_LOCAL_HouseRoach_Create
HouseRoach *HouseRoach_Create();
#endif
#ifndef PROTO_LOCAL_HouseRoach_SpawnInitial
BOOL HouseRoach_SpawnInitial(HouseRoachManager *owner);
#endif
#ifndef PROTO_LOCAL_HouseRoach_LoadCount
BOOL HouseRoach_LoadCount(HouseRoachManager *self);
#endif
#ifndef PROTO_LOCAL_sHouseRoachManagerProfile
extern ProcProfile sHouseRoachManagerProfile;
#endif
#ifndef PROTO_LOCAL_sHouseRoachProfile
extern ActorProfile sHouseRoachProfile;
#endif
#ifndef PROTO_LOCAL_sHouseRoachManager
extern HouseRoachManager *sHouseRoachManager;
#endif
#ifndef PROTO_LOCAL_sHouseRoachVillager
extern Actor *sHouseRoachVillager;
#endif
#ifndef PROTO_LOCAL_sHouseRoaches
extern HouseRoach *sHouseRoaches[3];
#endif
}
#endif

#endif

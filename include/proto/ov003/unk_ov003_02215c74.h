#ifndef PROTO_PROTO_OV003_UNK_OV003_02215C74_H
#define PROTO_PROTO_OV003_UNK_OV003_02215C74_H


#include "types.h"
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#include "town/BuildingActor.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov003_022352d4
extern char data_ov003_022352d4[0x14];
#endif
#ifndef PROTO_LOCAL_data_ov003_02235308
extern char data_ov003_02235308[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov003_02235330
extern char data_ov003_02235330[0x28];
#endif
#ifndef PROTO_LOCAL_VillagerHouse_Create
void *VillagerHouse_Create();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sVillagerHouses
extern BuildingActor *sVillagerHouses[8];
#endif
#ifndef PROTO_LOCAL_sVillagerHouseProfile
extern ActorProfile sVillagerHouseProfile;
#endif
}
#endif

#endif

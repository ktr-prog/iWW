#ifndef PROTO_PROTO_OV004_UNK_OV004_0221A218_H
#define PROTO_PROTO_OV004_UNK_OV004_0221A218_H


#include "types.h"
struct CafeVillagerActEntry;
#ifndef __cplusplus
typedef struct CafeVillagerActEntry CafeVillagerActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class CafeVillager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_022508e0
extern char data_ov004_022508e0[0x28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sCafeVillagerProfile
extern ActorProfile sCafeVillagerProfile;
#endif
#ifndef PROTO_LOCAL_sCafeVillagerActTable
extern CafeVillagerActEntry sCafeVillagerActTable[3];
#endif
#ifndef PROTO_LOCAL_CafeVillager_Create
CafeVillager *CafeVillager_Create();
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV004_UNK_OV004_0221789C_H
#define PROTO_PROTO_OV004_UNK_OV004_0221789C_H


#include "types.h"
struct FleaMarketSellerActEntry;
#ifndef __cplusplus
typedef struct FleaMarketSellerActEntry FleaMarketSellerActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class FleaMarketSellerVillager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_022506c8
extern u8 data_ov004_022506c8[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov004_022506f0
extern u8 data_ov004_022506f0[0x28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sFleaMarketSellerVillagerProfile
extern ActorProfile sFleaMarketSellerVillagerProfile;
#endif
#ifndef PROTO_LOCAL_sFleaMarketSellerActTable
extern FleaMarketSellerActEntry sFleaMarketSellerActTable[8];
#endif
#ifndef PROTO_LOCAL_FleaMarketSellerVillager_Create
FleaMarketSellerVillager *FleaMarketSellerVillager_Create();
#endif
}
#endif

#endif

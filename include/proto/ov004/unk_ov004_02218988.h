#ifndef PROTO_PROTO_OV004_UNK_OV004_02218988_H
#define PROTO_PROTO_OV004_UNK_OV004_02218988_H


#include "types.h"
struct FleaMarketBuyerActEntry;
struct FleaMarketBuyerTalkScript;
#ifndef __cplusplus
typedef struct FleaMarketBuyerActEntry FleaMarketBuyerActEntry;
typedef struct FleaMarketBuyerTalkScript FleaMarketBuyerTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class FleaMarketBuyerVillager;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_02250828
extern u8 data_ov004_02250828[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov004_022507b0
extern u8 data_ov004_022507b0[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov004_022507d8
extern u8 data_ov004_022507d8[0x28];
#endif
#ifndef PROTO_LOCAL_data_ov004_02250800
extern u8 data_ov004_02250800[0x28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sFleaMarketBuyerVillagerProfile
extern ActorProfile sFleaMarketBuyerVillagerProfile;
#endif
#ifndef PROTO_LOCAL_sFleaMarketBuyerTalkScripts
extern FleaMarketBuyerTalkScript sFleaMarketBuyerTalkScripts[2];
#endif
#ifndef PROTO_LOCAL_sFleaMarketBuyerActTable
extern FleaMarketBuyerActEntry sFleaMarketBuyerActTable[9];
#endif
#ifndef PROTO_LOCAL_FleaMarketBuyerVillager_Create
FleaMarketBuyerVillager *FleaMarketBuyerVillager_Create();
#endif
}
#endif

#endif

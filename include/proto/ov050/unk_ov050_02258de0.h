#ifndef PROTO_PROTO_OV050_UNK_OV050_02258DE0_H
#define PROTO_PROTO_OV050_UNK_OV050_02258DE0_H


#include "types.h"
struct Unk_ov050_0225d1d4_Ent;
#ifndef __cplusplus
typedef struct Unk_ov050_0225d1d4_Ent Unk_ov050_0225d1d4_Ent;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcNookShop;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopDramaKey
extern char sSpNpcNookShopDramaKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopTexturePaths
extern char *sSpNpcNookShopTexturePaths[5];
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopModelPaths
extern char *sSpNpcNookShopModelPaths[5];
#endif
#ifndef PROTO_LOCAL_SpNpcNookShop_IsDeliveryParcel
BOOL SpNpcNookShop_IsDeliveryParcel(u16 *p, s32 m);
#endif
#ifndef PROTO_LOCAL_SpNpcNookShop_GetHouseUpgradeMsg
s32 SpNpcNookShop_GetHouseUpgradeMsg(void *self);
#endif
#ifndef PROTO_LOCAL_SpNpcNookShop_IsEmptyItem
BOOL SpNpcNookShop_IsEmptyItem(u16 *p);
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopKey
extern char sSpNpcNookShopKey[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e2d0
extern char data_ov050_0225e2d0[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e2ec
extern char data_ov050_0225e2ec[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e308
extern char data_ov050_0225e308[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e324
extern char data_ov050_0225e324[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e340
extern char data_ov050_0225e340[];
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopTwinsKey
extern char sSpNpcNookShopTwinsKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopSequence5_1Key
extern char sSpNpcNookShopSequence5_1Key[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e210
extern char data_ov050_0225e210[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e240
extern char data_ov050_0225e240[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e258
extern char data_ov050_0225e258[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e270
extern char data_ov050_0225e270[];
#endif
#ifndef PROTO_LOCAL_data_ov050_0225e228
extern char data_ov050_0225e228[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcNookShop_Create
SpNpcNookShop *SpNpcNookShop_Create();
#endif
#ifndef PROTO_LOCAL_SpNpcNookShop_CreateTimmy
SpNpcNookShop *SpNpcNookShop_CreateTimmy();
#endif
#ifndef PROTO_LOCAL_SpNpcNookShop_CreateTommy
SpNpcNookShop *SpNpcNookShop_CreateTommy();
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopActTable
extern Unk_ov050_0225d1d4_Ent sSpNpcNookShopActTable[19];
#endif
#ifndef PROTO_LOCAL_sSpNpcNookShopProfile
extern ActorProfile sSpNpcNookShopProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcTimmyProfile
extern ActorProfile sSpNpcTimmyProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcTommyProfile
extern ActorProfile sSpNpcTommyProfile;
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV004_UNK_OV004_0221B498_H
#define PROTO_PROTO_OV004_UNK_OV004_0221B498_H


#include "types.h"
struct SpNpcSableActEntry;
#ifndef __cplusplus
typedef struct SpNpcSableActEntry SpNpcSableActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcSable;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcSable_GetTalkCount
u32 SpNpcSable_GetTalkCount(void *unused);
#endif
#ifndef PROTO_LOCAL_SpNpcSable_SetTalkCount
void SpNpcSable_SetTalkCount(void *unused, u32 a);
#endif
#ifndef PROTO_LOCAL_data_ov004_0224cd04
extern u8 data_ov004_0224cd04[14];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224cd14
extern u8 data_ov004_0224cd14[15];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224cd24
extern u8 data_ov004_0224cd24[17];
#endif
#ifndef PROTO_LOCAL_sSpNpcSableModelPath
extern u8 sSpNpcSableModelPath[23];
#endif
#ifndef PROTO_LOCAL_sSpNpcSableTexturePath
extern u8 sSpNpcSableTexturePath[27];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcSable_Create
SpNpcSable *SpNpcSable_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcSableProfile
extern ActorProfile sSpNpcSableProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcSableActTable
extern SpNpcSableActEntry sSpNpcSableActTable[7];
#endif
}
#endif

#endif

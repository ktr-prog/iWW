#ifndef PROTO_PROTO_OV004_UNK_OV004_0221D748_H
#define PROTO_PROTO_OV004_UNK_OV004_0221D748_H


#include "types.h"
struct SpNpcBookerActEntry;
struct SpNpcBookerTalkScript;
#ifndef __cplusplus
typedef struct SpNpcBookerActEntry SpNpcBookerActEntry;
typedef struct SpNpcBookerTalkScript SpNpcBookerTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcBooker;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d1e0
extern u8 data_ov004_0224d1e0[19];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d1f4
extern u8 data_ov004_0224d1f4[23];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224d224
extern u8 data_ov004_0224d224[27];
#endif
#ifndef PROTO_LOCAL_sSpNpcBookerModelPath
extern u8 *sSpNpcBookerModelPath;
#endif
#ifndef PROTO_LOCAL_sSpNpcBookerTexturePath
extern u8 *sSpNpcBookerTexturePath;
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcBooker_Create
SpNpcBooker *SpNpcBooker_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcBookerProfile
extern ActorProfile sSpNpcBookerProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcBookerTalkScripts
extern SpNpcBookerTalkScript sSpNpcBookerTalkScripts[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcBookerActTable
extern SpNpcBookerActEntry sSpNpcBookerActTable[7];
#endif
}
#endif

#endif

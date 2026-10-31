#ifndef PROTO_PROTO_OV087_UNK_OV087_022713C0_H
#define PROTO_PROTO_OV087_UNK_OV087_022713C0_H


#include "types.h"
struct SpNpcCornimerActEntry;
#ifndef __cplusplus
typedef struct SpNpcCornimerActEntry SpNpcCornimerActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcCornimer;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov087_02271d84
extern u32 data_ov087_02271d84;
#endif
#ifndef PROTO_LOCAL_sSpNpcCornimerTexturePath
extern u8 sSpNpcCornimerTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcCornimerFortuneStrKey
extern char sSpNpcCornimerFortuneStrKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcCornimerModelPath
extern u8 sSpNpcCornimerModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcCornimerFortuneStr2Key
extern char sSpNpcCornimerFortuneStr2Key[];
#endif
#ifndef PROTO_LOCAL_data_ov087_02271d80
extern u32 data_ov087_02271d80;
#endif
#ifndef PROTO_LOCAL_SpNpcCornimer_IsAcorn
BOOL SpNpcCornimer_IsAcorn(u16 *p, s32 m);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcCornimerProfile
extern ActorProfile sSpNpcCornimerProfile;
#endif
#ifndef PROTO_LOCAL_SpNpcCornimer_Create
SpNpcCornimer *SpNpcCornimer_Create();
#endif
}
#ifndef PROTO_LOCAL_sSpNpcCornimerActTable
extern SpNpcCornimerActEntry sSpNpcCornimerActTable[3];
#endif
#endif

#endif

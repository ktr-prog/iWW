#ifndef PROTO_PROTO_OV086_UNK_OV086_022713C0_H
#define PROTO_PROTO_OV086_UNK_OV086_022713C0_H


#include "types.h"
struct SpNpcTortimerCountdownActEntry;
#ifndef __cplusplus
typedef struct SpNpcTortimerCountdownActEntry SpNpcTortimerCountdownActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcTortimerCountdown;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov086_02271c24
extern u32 data_ov086_02271c24;
#endif
#ifndef PROTO_LOCAL_data_ov086_02271c20
extern u32 data_ov086_02271c20;
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerCountdownFortuneStrKey
extern char sSpNpcTortimerCountdownFortuneStrKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerCountdownFortuneStr2Key
extern char sSpNpcTortimerCountdownFortuneStr2Key[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerCountdownModelPath
extern u8 sSpNpcTortimerCountdownModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcTortimerCountdownTexturePath
extern u8 sSpNpcTortimerCountdownTexturePath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcTortimerCountdownProfile
extern ActorProfile sSpNpcTortimerCountdownProfile;
#endif
#ifndef PROTO_LOCAL_SpNpcTortimerCountdown_Create
SpNpcTortimerCountdown *SpNpcTortimerCountdown_Create();
#endif
}
#ifndef PROTO_LOCAL_sSpNpcTortimerCountdownActTable
extern SpNpcTortimerCountdownActEntry sSpNpcTortimerCountdownActTable[3];
#endif
#endif

#endif

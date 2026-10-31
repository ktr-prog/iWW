#ifndef PROTO_PROTO_OV068_UNK_OV068_0226C2E0_H
#define PROTO_PROTO_OV068_UNK_OV068_0226C2E0_H


#include "types.h"
struct SpNpcRoostGuestActEntry;
struct SpNpcRoostGuestTalkScript;
#ifndef __cplusplus
typedef struct SpNpcRoostGuestActEntry SpNpcRoostGuestActEntry;
typedef struct SpNpcRoostGuestTalkScript SpNpcRoostGuestTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcRoostGuest;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sRoostTexMof
extern char sRoostTexMof[27];
#endif
#ifndef PROTO_LOCAL_sRoostTexEnd
extern char sRoostTexEnd[27];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf3
extern char sRoostMsgCf3[11];
#endif
#ifndef PROTO_LOCAL_sRoostTexPga
extern char sRoostTexPga[27];
#endif
#ifndef PROTO_LOCAL_sRoostModelPga
extern char sRoostModelPga[23];
#endif
#ifndef PROTO_LOCAL_sKkMouthM5
extern char sKkMouthM5[4];
#endif
#ifndef PROTO_LOCAL_sKkMouthM4
extern char sKkMouthM4[4];
#endif
#ifndef PROTO_LOCAL_sRoostTexPgb
extern char sRoostTexPgb[27];
#endif
#ifndef PROTO_LOCAL_sRoostModelPgb
extern char sRoostModelPgb[23];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf4
extern char sRoostMsgCf4[11];
#endif
#ifndef PROTO_LOCAL_sRoostModelWip
extern char sRoostModelWip[23];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf2
extern char sRoostMsgCf2[11];
#endif
#ifndef PROTO_LOCAL_sRoostTexWip
extern char sRoostTexWip[27];
#endif
#ifndef PROTO_LOCAL_sRoostModelEnd
extern char sRoostModelEnd[23];
#endif
#ifndef PROTO_LOCAL_sKkMouthM2
extern char sKkMouthM2[4];
#endif
#ifndef PROTO_LOCAL_sKkMouthM1
extern char sKkMouthM1[4];
#endif
#ifndef PROTO_LOCAL_sRoostModelMof
extern char sRoostModelMof[23];
#endif
#ifndef PROTO_LOCAL_sRoostMsgDog
extern char sRoostMsgDog[11];
#endif
#ifndef PROTO_LOCAL_sRoostModelOtt
extern char sRoostModelOtt[23];
#endif
#ifndef PROTO_LOCAL_sRoostTexPoo
extern char sRoostTexPoo[27];
#endif
#ifndef PROTO_LOCAL_sRoostTexOtt
extern char sRoostTexOtt[27];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf7
extern char sRoostMsgCf7[11];
#endif
#ifndef PROTO_LOCAL_sKkMouthM3
extern char sKkMouthM3[4];
#endif
#ifndef PROTO_LOCAL_sRoostTexXct
extern char sRoostTexXct[27];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf1
extern char sRoostMsgCf1[11];
#endif
#ifndef PROTO_LOCAL_sKkMouthTextures
extern char *sKkMouthTextures[6];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf6
extern char sRoostMsgCf6[11];
#endif
#ifndef PROTO_LOCAL_sRoostMsgCf5
extern char sRoostMsgCf5[11];
#endif
#ifndef PROTO_LOCAL_sRoostModelXct
extern char sRoostModelXct[23];
#endif
#ifndef PROTO_LOCAL_sKkMouthM0
extern char sKkMouthM0[4];
#endif
#ifndef PROTO_LOCAL_sRoostModelPoo
extern char sRoostModelPoo[23];
#endif
#ifndef PROTO_LOCAL_RoostGuest_PickKKSong
u16 RoostGuest_PickKKSong(void *self);
#endif
#ifndef PROTO_LOCAL_SpNpcRoostGuest_GetGuest
s32 SpNpcRoostGuest_GetGuest(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcRoostGuest_Create
SpNpcRoostGuest *SpNpcRoostGuest_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcRoostGuestProfile
extern ActorProfile sSpNpcRoostGuestProfile;
#endif
#ifndef PROTO_LOCAL_sKkShowScripts
extern SpNpcRoostGuestTalkScript sKkShowScripts[6];
#endif
#ifndef PROTO_LOCAL_sSpNpcRoostGuestActTable
extern SpNpcRoostGuestActEntry sSpNpcRoostGuestActTable[5];
#endif
}
#endif

#endif

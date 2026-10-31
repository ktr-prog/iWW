#ifndef PROTO_PROTO_OV004_UNK_OV004_0221C01C_H
#define PROTO_PROTO_OV004_UNK_OV004_0221C01C_H


#include "types.h"
struct SpNpcBrewsterActEntry;
struct SpNpcBrewsterTalkScript;
#ifndef __cplusplus
typedef struct SpNpcBrewsterActEntry SpNpcBrewsterActEntry;
typedef struct SpNpcBrewsterTalkScript SpNpcBrewsterTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcBrewster;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcBrewster_GetJointMtxE
void *SpNpcBrewster_GetJointMtxE();
#endif
#ifndef PROTO_LOCAL_SpNpcBrewster_GetJointMtxB
void *SpNpcBrewster_GetJointMtxB();
#endif
#ifndef PROTO_LOCAL_SpNpcBrewster_GetAnimFrame
u32 SpNpcBrewster_GetAnimFrame();
#endif
#ifndef PROTO_LOCAL_SpNpcBrewster_GetAnimState
s32 SpNpcBrewster_GetAnimState();
#endif
#ifndef PROTO_LOCAL_data_ov004_0224cec8
extern u8 data_ov004_0224cec8[4];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224cf6c
extern u8 data_ov004_0224cf6c[12];
#endif
#ifndef PROTO_LOCAL_data_ov004_0224cf78
extern u8 data_ov004_0224cf78[17];
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewsterModelPath
extern u8 sSpNpcBrewsterModelPath[23];
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewsterTexturePath
extern u8 sSpNpcBrewsterTexturePath[27];
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewsterMsgFiles
extern u8 *sSpNpcBrewsterMsgFiles[2];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcBrewster_Create
SpNpcBrewster *SpNpcBrewster_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewsterProfile
extern ActorProfile sSpNpcBrewsterProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewsterTalkScripts
extern SpNpcBrewsterTalkScript sSpNpcBrewsterTalkScripts[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewsterActTable
extern SpNpcBrewsterActEntry sSpNpcBrewsterActTable[8];
#endif
#ifndef PROTO_LOCAL_sSpNpcBrewster
extern SpNpcBrewster *sSpNpcBrewster;
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV055_UNK_OV055_02258DE0_H
#define PROTO_PROTO_OV055_UNK_OV055_02258DE0_H


#include "types.h"
struct SpNpcRoverActEntry;
struct SpNpcRoverTalkScript;
#ifndef __cplusplus
typedef struct SpNpcRoverActEntry SpNpcRoverActEntry;
typedef struct SpNpcRoverTalkScript SpNpcRoverTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcRover;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcRoverKey
extern char sSpNpcRoverKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcRoverModelPath
extern u8 sSpNpcRoverModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcRoverTexturePath
extern u8 sSpNpcRoverTexturePath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcRoverProfile
extern ActorProfile sSpNpcRoverProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcRoverTalkScripts
extern SpNpcRoverTalkScript sSpNpcRoverTalkScripts[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcRoverActTable
extern SpNpcRoverActEntry sSpNpcRoverActTable[3];
#endif
#ifndef PROTO_LOCAL_sSpNpcRoverInstance
extern SpNpcRover *sSpNpcRoverInstance;
#endif
#ifndef PROTO_LOCAL_SpNpcRover_Create
SpNpcRover *SpNpcRover_Create();
#endif
}
#endif

#endif

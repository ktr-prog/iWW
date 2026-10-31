#ifndef PROTO_PROTO_OV045_UNK_02258DE0_H
#define PROTO_PROTO_OV045_UNK_02258DE0_H


#include "types.h"
#include "gfx/Mtx43.h"
struct SpNpcKatrinaActEntry;
struct SpNpcKatrinaTalkScript;
#ifndef __cplusplus
typedef struct SpNpcKatrinaActEntry SpNpcKatrinaActEntry;
typedef struct SpNpcKatrinaTalkScript SpNpcKatrinaTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcKatrina;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcKatrina_GetJointMtx
Mtx43 *SpNpcKatrina_GetJointMtx();
#endif
#ifndef PROTO_LOCAL_SpNpcKatrina_GetAnimFrame
u32 SpNpcKatrina_GetAnimFrame();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcKatrina_Create
SpNpcKatrina *SpNpcKatrina_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaProfile
extern ActorProfile sSpNpcKatrinaProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcKatrinaModelPath
extern u8 sSpNpcKatrinaModelPath[23];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaTexturePath
extern u8 sSpNpcKatrinaTexturePath[27];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaMsgKey
extern void *sSpNpcKatrinaMsgKey;
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaKey
extern u8 sSpNpcKatrinaKey[15];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaTalkScripts
extern SpNpcKatrinaTalkScript sSpNpcKatrinaTalkScripts[2];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaActTable
extern SpNpcKatrinaActEntry sSpNpcKatrinaActTable[4];
#endif
#ifndef PROTO_LOCAL_sSpNpcKatrinaInstance
extern SpNpcKatrina *sSpNpcKatrinaInstance;
#endif
#endif

#endif

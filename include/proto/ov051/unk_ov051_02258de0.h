#ifndef PROTO_PROTO_OV051_UNK_OV051_02258DE0_H
#define PROTO_PROTO_OV051_UNK_OV051_02258DE0_H


#include "types.h"
struct SpNpcKappnActEntry;
#ifndef __cplusplus
typedef struct SpNpcKappnActEntry SpNpcKappnActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcKappn;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcKappnTexturePath
extern u8 sSpNpcKappnTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKappnModelPath
extern u8 sSpNpcKappnModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKappnKey
extern u8 sSpNpcKappnKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcKappnMsgKey
extern char *sSpNpcKappnMsgKey;
#endif
#ifndef PROTO_LOCAL_SpNpcKappn_GetAnimFrame
u32 SpNpcKappn_GetAnimFrame();
#endif
#ifndef PROTO_LOCAL_SpNpcKappn_GetAnimState
s32 SpNpcKappn_GetAnimState();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcKappn_Create
SpNpcKappn *SpNpcKappn_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcKappnProfile
extern ActorProfile sSpNpcKappnProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcKappnActTable
extern SpNpcKappnActEntry sSpNpcKappnActTable[5];
#endif
#ifndef PROTO_LOCAL_sSpNpcKappnInstance
extern SpNpcKappn *sSpNpcKappnInstance;
#endif
#endif

#endif

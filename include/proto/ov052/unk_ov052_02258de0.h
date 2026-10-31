#ifndef PROTO_PROTO_OV052_UNK_OV052_02258DE0_H
#define PROTO_PROTO_OV052_UNK_OV052_02258DE0_H


#include "types.h"
struct SpNpcReddActEntry;
#ifndef __cplusplus
typedef struct SpNpcReddActEntry SpNpcReddActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcRedd;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcRedd_CountUnusedFlags
s32 SpNpcRedd_CountUnusedFlags(void *self, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_SpNpcRedd_PickUnusedFlag
s32 SpNpcRedd_PickUnusedFlag(void *self, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_SpNpcRedd_IsSoldOut
BOOL SpNpcRedd_IsSoldOut(void *self);
#endif
#ifndef PROTO_LOCAL_sSpNpcReddKey
extern char sSpNpcReddKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcReddModelPath
extern u8 sSpNpcReddModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcReddTexturePath
extern u8 sSpNpcReddTexturePath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcRedd_Create
SpNpcRedd *SpNpcRedd_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcReddProfile
extern ActorProfile sSpNpcReddProfile;
#endif
#ifndef PROTO_LOCAL_sSpNpcReddActTable
extern SpNpcReddActEntry sSpNpcReddActTable[11];
#endif
}
#endif

#endif

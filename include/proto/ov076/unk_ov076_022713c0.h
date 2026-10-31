#ifndef PROTO_PROTO_OV076_UNK_OV076_022713C0_H
#define PROTO_PROTO_OV076_UNK_OV076_022713C0_H


#include "types.h"
struct SpNpcPascalActEntry;
#ifndef __cplusplus
typedef struct SpNpcPascalActEntry SpNpcPascalActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcPascal;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcPascal_IsScallop
BOOL SpNpcPascal_IsScallop(u16 *p, s32 x);
#endif
#ifndef PROTO_LOCAL_sSpNpcPascalKey
extern u8 sSpNpcPascalKey[16];
#endif
#ifndef PROTO_LOCAL_sSpNpcPascalModelPath
extern u8 sSpNpcPascalModelPath[24];
#endif
#ifndef PROTO_LOCAL_sSpNpcPascalTexturePath
extern u8 sSpNpcPascalTexturePath[28];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SpNpcPascal_Create
SpNpcPascal *SpNpcPascal_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcPascalProfile
extern ActorProfile sSpNpcPascalProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcPascalActTable
extern SpNpcPascalActEntry sSpNpcPascalActTable[6];
#endif
#endif

#endif

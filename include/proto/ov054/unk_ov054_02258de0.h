#ifndef PROTO_PROTO_OV054_UNK_OV054_02258DE0_H
#define PROTO_PROTO_OV054_UNK_OV054_02258DE0_H


#include "types.h"
struct SpNpcPellyPhyllisActEntry;
struct SpNpcPellyPhyllisTalkScript;
#ifndef __cplusplus
typedef struct SpNpcPellyPhyllisActEntry SpNpcPellyPhyllisActEntry;
typedef struct SpNpcPellyPhyllisTalkScript SpNpcPellyPhyllisTalkScript;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
class SpNpcPellyPhyllis;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisMsgKeys
extern char *sSpNpcPellyPhyllisMsgKeys[2][3];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyDramaKey
extern char sSpNpcPellyDramaKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisMenus
extern void *sSpNpcPellyPhyllisMenus[5];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyTexturePath
extern u8 sSpNpcPellyTexturePath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisTexturePaths
extern u8 *sSpNpcPellyPhyllisTexturePaths[2];
#endif
#ifndef PROTO_LOCAL_sSpNpcPhyllisTexturePath
extern u8 sSpNpcPhyllisTexturePath[];
#endif
#ifndef PROTO_LOCAL_SpNpcPellyPhyllis_IsDeliveryItem
BOOL SpNpcPellyPhyllis_IsDeliveryItem(u16 *p, s32 k);
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisModelPaths
extern u8 *sSpNpcPellyPhyllisModelPaths[2];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyKey
extern char sSpNpcPellyKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyModelPath
extern u8 sSpNpcPellyModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPhyllisKey
extern char sSpNpcPhyllisKey[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPhyllisModelPath
extern u8 sSpNpcPhyllisModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisSequence4Key
extern char sSpNpcPellyPhyllisSequence4Key[];
#endif
#ifndef PROTO_LOCAL_sSpNpcPhyllisDramaKey
extern char sSpNpcPhyllisDramaKey[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisTalkScripts
extern SpNpcPellyPhyllisTalkScript sSpNpcPellyPhyllisTalkScripts[16];
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisActTable
extern SpNpcPellyPhyllisActEntry sSpNpcPellyPhyllisActTable[12];
#endif
#ifndef PROTO_LOCAL_SpNpcPellyPhyllis_Create
SpNpcPellyPhyllis *SpNpcPellyPhyllis_Create();
#endif
#ifndef PROTO_LOCAL_sSpNpcPellyPhyllisProfile
extern ActorProfile sSpNpcPellyPhyllisProfile;
#endif
}
#endif

#endif

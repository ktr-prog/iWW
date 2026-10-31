#ifndef PROTO_PROTO_OV047_UNK_OV047_02258DE0_H
#define PROTO_PROTO_OV047_UNK_OV047_02258DE0_H


#include "types.h"
struct SpNpcBlathersActEntry;
#ifndef __cplusplus
typedef struct SpNpcBlathersActEntry SpNpcBlathersActEntry;
#endif
#ifdef __cplusplus
#include "actor/ActorProfile.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SpNpcBlathers_Create
void *SpNpcBlathers_Create();
#endif
#ifndef PROTO_LOCAL_SpNpcBlathers_IsDonatableItem
BOOL SpNpcBlathers_IsDonatableItem(u16 *p, s32 m);
#endif
#ifndef PROTO_LOCAL_SpNpcBlathers_IsUnidentifiedFossil
BOOL SpNpcBlathers_IsUnidentifiedFossil(u16 *p, s32 m);
#endif
#ifndef PROTO_LOCAL_SpNpcBlathers_IsDeliveryItem
BOOL SpNpcBlathers_IsDeliveryItem(u16 *p, s32 m);
#endif
#ifndef PROTO_LOCAL_sSpNpcBlathersModelPath
extern u8 sSpNpcBlathersModelPath[];
#endif
#ifndef PROTO_LOCAL_sSpNpcBlathersTexturePath
extern u8 sSpNpcBlathersTexturePath[];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSpNpcBlathersProfile
extern ActorProfile sSpNpcBlathersProfile;
#endif
}
#ifndef PROTO_LOCAL_sSpNpcBlathersActTable
extern SpNpcBlathersActEntry sSpNpcBlathersActTable[9];
#endif
#endif

#endif

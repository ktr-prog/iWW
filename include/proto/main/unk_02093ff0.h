#ifndef PROTO_PROTO_MAIN_UNK_02093FF0_H
#define PROTO_PROTO_MAIN_UNK_02093FF0_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PlayerSession_RemovePitfallOnClimbOut
void PlayerSession_RemovePitfallOnClimbOut(s32 *a, u8 *b, s32 *c, s32 *d, s32 *e, s32 *f);
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetLocalSessionSlot
s32 PlayerActor_GetLocalSessionSlot();
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetObjectSize
s32 PlayerActor_GetObjectSize();
#endif
#ifndef PROTO_LOCAL_PlayerActor_GetObjectAlign
s32 PlayerActor_GetObjectAlign();
#endif
#ifndef PROTO_LOCAL_PlayerId_ListContainsId
BOOL PlayerId_ListContainsId(u16 v, u16 *arr, s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerId_GenerateUniqueId
u16 PlayerId_GenerateUniqueId(u16 *arr, s32 n);
#endif
#ifndef PROTO_LOCAL_PlayerId_GenerateRandomId
u16 PlayerId_GenerateRandomId();
#endif
#ifndef PROTO_LOCAL_PlayerId_GetTownId
void *PlayerId_GetTownId(void *p);
#endif
#ifndef PROTO_LOCAL_PlayerId_FindResidentIndex
s32 PlayerId_FindResidentIndex(void *x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_PlayerActor_Spawn
void *PlayerActor_Spawn(u32 slot, VecFx32 *pos, void *rot, u32 param);
#endif
}
#endif

#endif

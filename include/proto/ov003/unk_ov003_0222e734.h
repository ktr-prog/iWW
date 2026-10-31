#ifndef PROTO_PROTO_OV003_UNK_OV003_0222E734_H
#define PROTO_PROTO_OV003_UNK_OV003_0222E734_H


#include "types.h"
struct UnitMaskChunk;
struct UnitMaskPool;
#ifndef __cplusplus
typedef struct UnitMaskChunk UnitMaskChunk;
typedef struct UnitMaskPool UnitMaskPool;
#endif
#ifdef __cplusplus
#include "field/Snowball.h"
#include "gfx/VecFx32.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SnowballSpawner_SpawnLooseBalls
void SnowballSpawner_SpawnLooseBalls(void *self);
#endif
#ifndef PROTO_LOCAL_SnowballSpawner_SpawnSnowmen
void SnowballSpawner_SpawnSnowmen(void *self);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSnowballs
extern Snowball *sSnowballs[8];
#endif
#ifndef PROTO_LOCAL_Snowball_Register
BOOL Snowball_Register(Snowball *p);
#endif
#ifndef PROTO_LOCAL_Snowball_Unregister
BOOL Snowball_Unregister(Snowball *p);
#endif
#ifndef PROTO_LOCAL_Snowball_FindByParam
Snowball *Snowball_FindByParam(u32 id);
#endif
#ifndef PROTO_LOCAL_Snowball_TryPushAny
BOOL Snowball_TryPushAny(VecFx32 *outPos, s16 *outAng, s32 *outVal, s32 speed, s32 ang);
#endif
#ifndef PROTO_LOCAL_Snowball_GetLooseBall
Snowball *Snowball_GetLooseBall(u32 id);
#endif
#ifndef PROTO_LOCAL_Snowball_FindOtherInBallState
Snowball *Snowball_FindOtherInBallState(Snowball *self);
#endif
#ifndef PROTO_LOCAL_UnitMaskChunk_Clear
void UnitMaskChunk_Clear(UnitMaskChunk *c);
#endif
#ifndef PROTO_LOCAL_UnitMaskChunk_Mark
void UnitMaskChunk_Mark(UnitMaskChunk *c, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_UnitMaskChunk_IsMarked
BOOL UnitMaskChunk_IsMarked(UnitMaskChunk *c, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_UnitMaskChunk_PickRandom
BOOL UnitMaskChunk_PickRandom(UnitMaskChunk *c, s32 *ox, s32 *oy);
#endif
#ifndef PROTO_LOCAL_UnitMaskPool_Clear
void UnitMaskPool_Clear(UnitMaskPool *pool);
#endif
#ifndef PROTO_LOCAL_UnitMaskPool_CountFreeChunks
s32 UnitMaskPool_CountFreeChunks(UnitMaskPool *pool);
#endif
#ifndef PROTO_LOCAL_UnitMaskPool_Mark
void UnitMaskPool_Mark(UnitMaskPool *pool, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_UnitMaskPool_PickRandom
BOOL UnitMaskPool_PickRandom(UnitMaskPool *pool, s32 *ox, s32 *oy);
#endif
#ifndef PROTO_LOCAL_Snowball_FindSpawnPos
BOOL Snowball_FindSpawnPos(void *a, VecFx32 *b, VecFx32 *c, s32 d);
#endif
}
#endif

#endif

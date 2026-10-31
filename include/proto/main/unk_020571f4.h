#ifndef PROTO_PROTO_MAIN_UNK_020571F4_H
#define PROTO_PROTO_MAIN_UNK_020571F4_H


#include "types.h"
#include "sys/ProcProfile.h"
struct FishHoldOffsets;
struct HandOverItemAct;
#ifndef __cplusplus
typedef struct FishHoldOffsets FishHoldOffsets;
typedef struct HandOverItemAct HandOverItemAct;
#endif
#ifdef __cplusplus
#include "actor/Actor.h"
#include "actor/Character.h"
#include "game/FxVec3.h"
#include "gfx/VecFx32.h"
#include "sys/ProcBase.h"
class HandOverItem;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_021c5a30
extern u8 data_021c5a30[4];
#endif
#ifndef PROTO_LOCAL_data_021c5a2c
extern u8 data_021c5a2c[4];
#endif
#ifndef PROTO_LOCAL_data_021c5a28
extern u8 data_021c5a28[4];
#endif
#ifndef PROTO_LOCAL_data_021c5a24
extern u8 data_021c5a24[4];
#endif
#ifndef PROTO_LOCAL_data_021c5ae8
extern s32 data_021c5ae8[4];
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetFishScale
u32 HandOverItem_GetFishScale(u32 i);
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetNextMode
u8 HandOverItem_GetNextMode(void);
#endif
#ifndef PROTO_LOCAL_HandOverItem_IsModeActive
BOOL HandOverItem_IsModeActive(u32 a);
#endif
#ifndef PROTO_LOCAL_HandOverItem_IsActive
BOOL HandOverItem_IsActive(void);
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetItem
void HandOverItem_GetItem(u16 *out);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sHandOverItem
extern HandOverItem *sHandOverItem;
#endif
#ifndef PROTO_LOCAL_sHandOverItemActs
extern HandOverItemAct sHandOverItemActs[12][2];
#endif
#ifndef PROTO_LOCAL_sPutDownOffset
extern FxVec3 sPutDownOffset;
#endif
#ifndef PROTO_LOCAL_data_021c5acc
extern FxVec3 data_021c5acc;
#endif
#ifndef PROTO_LOCAL_data_021c5a84
extern FxVec3 data_021c5a84;
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetFishHoldOffsetSet
u32 HandOverItem_GetFishHoldOffsetSet(ProcBase *o);
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetFishHoldOffset
VecFx32 *HandOverItem_GetFishHoldOffset(ProcBase *o, u32 idx);
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetFishHoldOffset2
VecFx32 *HandOverItem_GetFishHoldOffset2(ProcBase *o, u32 idx);
#endif
#ifndef PROTO_LOCAL_HandOverItem_Create
HandOverItem *HandOverItem_Create();
#endif
#ifndef PROTO_LOCAL_HandOverItem_DrawItem
void HandOverItem_DrawItem(HandOverItem *self, u16 *id, VecFx32 *p, VecFx32 *q, s16 *ang);
#endif
#ifndef PROTO_LOCAL_HandOverItem_DrawIcon
void HandOverItem_DrawIcon(void *unused, u32 id, VecFx32 *p, VecFx32 *q, s16 *ang);
#endif
#ifndef PROTO_LOCAL_HandOverItem_Begin
s32 HandOverItem_Begin(u16 *item, s32 b, u8 c, s32 d, Character *master, Character *partner);
#endif
#ifndef PROTO_LOCAL_HandOverItem_IsMaster
s32 HandOverItem_IsMaster(Character *a);
#endif
#ifndef PROTO_LOCAL_HandOverItem_RequestMode
s32 HandOverItem_RequestMode(u8 a, Character *b);
#endif
#ifndef PROTO_LOCAL_HandOverItem_End
void HandOverItem_End(Character *a);
#endif
#ifndef PROTO_LOCAL_HandOverItem_CanTake
BOOL HandOverItem_CanTake(Actor *p);
#endif
#ifndef PROTO_LOCAL_HandOverItem_GetPos
BOOL HandOverItem_GetPos(VecFx32 *out);
#endif
#ifndef PROTO_LOCAL_HandOverItem_SwitchMaster
s32 HandOverItem_SwitchMaster(Character *a);
#endif
#ifndef PROTO_LOCAL_HandOverItem_SetNextMode
s32 HandOverItem_SetNextMode(u8 a, Character *b);
#endif
}
#ifndef PROTO_LOCAL_sHandOverItemProfile
extern ProcProfile sHandOverItemProfile;
#endif
#ifndef PROTO_LOCAL_sFishHoldOffsetSets
extern FishHoldOffsets *sFishHoldOffsetSets[6];
#endif
#endif

#endif

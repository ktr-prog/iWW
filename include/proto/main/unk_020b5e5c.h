#ifndef PROTO_PROTO_MAIN_UNK_020B5E5C_H
#define PROTO_PROTO_MAIN_UNK_020B5E5C_H


#include "types.h"
#ifdef __cplusplus
#include "gfx/VecFx32.h"
struct TouchPickResult;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveNone
void *TouchTarget_ResolveNone(void);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolvePlayer
void *TouchTarget_ResolvePlayer(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveVillager
void *TouchTarget_ResolveVillager(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveSpNpc
void *TouchTarget_ResolveSpNpc(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveBuilding
void *TouchTarget_ResolveBuilding(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveBuildingAlt
void *TouchTarget_ResolveBuildingAlt(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveFurniture
void *TouchTarget_ResolveFurniture(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveVillagerBoard
void *TouchTarget_ResolveVillagerBoard(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveAtm
void *TouchTarget_ResolveAtm(void);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveMuseumInfo
void *TouchTarget_ResolveMuseumInfo(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveRecycleBox
void *TouchTarget_ResolveRecycleBox(void);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolvePhone
void *TouchTarget_ResolvePhone(void);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveBoardSign
void *TouchTarget_ResolveBoardSign(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_ResolveSnowball
void *TouchTarget_ResolveSnowball(s32 a);
#endif
#ifndef PROTO_LOCAL_TouchTarget_Resolve
void *TouchTarget_Resolve(s32 idx, s32 arg);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TouchPickResult_GetTarget
BOOL TouchPickResult_GetTarget(TouchPickResult *obj, VecFx32 *out, s32 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_TouchPick_GetTargetObject
void *TouchPick_GetTargetObject(TouchPickResult *a, s32 *pa, u8 *pb);
#endif
#ifndef PROTO_LOCAL_TouchPick_GetTappedObject
void *TouchPick_GetTappedObject(TouchPickResult *a, s32 *pa, u8 *pb);
#endif
}
#endif

#endif

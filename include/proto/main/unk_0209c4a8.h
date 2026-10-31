#ifndef PROTO_PROTO_MAIN_UNK_0209C4A8_H
#define PROTO_PROTO_MAIN_UNK_0209C4A8_H


#include "types.h"
struct SceneOccupantBits;
#ifndef __cplusplus
typedef struct SceneOccupantBits SceneOccupantBits;
#endif
#ifdef __cplusplus
#include "gfx/VecFx32.h"
class RoomEntryRequest;
class SceneOccupantTable;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_RoomEntry_Reset
void RoomEntry_Reset();
#endif
#ifndef PROTO_LOCAL_RoomEntry_IsExclusiveScene
u32 RoomEntry_IsExclusiveScene(u32 v);
#endif
#ifndef PROTO_LOCAL_RoomEntry_IsExclusiveExit
s32 RoomEntry_IsExclusiveExit(u32 exitId);
#endif
#ifndef PROTO_LOCAL_RoomEntry_Request
BOOL RoomEntry_Request(u32 id);
#endif
#ifndef PROTO_LOCAL_RoomEntry_GetRequest
void *RoomEntry_GetRequest();
#endif
#ifndef PROTO_LOCAL_RoomEntry_Leave
void RoomEntry_Leave(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_RoomEntry_OnSceneLoad
void RoomEntry_OnSceneLoad();
#endif
#ifndef PROTO_LOCAL_RoomEntry_RecvEnterRequest
void RoomEntry_RecvEnterRequest(u8 *p, u32 x);
#endif
#ifndef PROTO_LOCAL_RoomEntry_RecvEnterReply
void RoomEntry_RecvEnterReply(u8 *p);
#endif
#ifndef PROTO_LOCAL_RoomEntry_RecvLeave
void RoomEntry_RecvLeave(u8 *p, u32 x);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SceneOccupants_Clear
void SceneOccupants_Clear(SceneOccupantBits *t);
#endif
#ifndef PROTO_LOCAL_SceneOccupants_Add
void SceneOccupants_Add(SceneOccupantBits *t, u32 i);
#endif
#ifndef PROTO_LOCAL_SceneOccupants_Remove
void SceneOccupants_Remove(SceneOccupantBits *t, u32 i);
#endif
#ifndef PROTO_LOCAL_SceneOccupants_Has
u32 SceneOccupants_Has(SceneOccupantBits *t, u32 i);
#endif
#ifndef PROTO_LOCAL_SceneOccupants_Count
s32 SceneOccupants_Count(SceneOccupantBits *t);
#endif
#ifndef PROTO_LOCAL_SceneOccupants_CountWith
s32 SceneOccupants_CountWith(SceneOccupantBits *t, u32 b);
#endif
#ifndef PROTO_LOCAL_SceneOccupantTable_Clear
void SceneOccupantTable_Clear(SceneOccupantBits *t);
#endif
#ifndef PROTO_LOCAL_SceneOccupantTable_Add
void SceneOccupantTable_Add(SceneOccupantBits *t, u32 i, u32 b);
#endif
#ifndef PROTO_LOCAL_SceneOccupantTable_Remove
void SceneOccupantTable_Remove(SceneOccupantBits *t, u32 i, u32 b);
#endif
#ifndef PROTO_LOCAL_SceneOccupantTable_CountWith
s32 SceneOccupantTable_CountWith(SceneOccupantBits *t, u32 i, u32 b);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_Init
void RoomEntryRequest_Init(RoomEntryRequest *t);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_GetResult
u32 RoomEntryRequest_GetResult(RoomEntryRequest *t);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_GetDoorKind
u32 RoomEntryRequest_GetDoorKind(RoomEntryRequest *t);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_GetPos
void *RoomEntryRequest_GetPos(RoomEntryRequest *t);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_GetRetreatPos
void *RoomEntryRequest_GetRetreatPos(RoomEntryRequest *t);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetResult
void RoomEntryRequest_SetResult(RoomEntryRequest *t, u32 v);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetExitId
void RoomEntryRequest_SetExitId(RoomEntryRequest *t, u32 v);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetDoorKind
void RoomEntryRequest_SetDoorKind(RoomEntryRequest *t, u32 v);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetScene
void RoomEntryRequest_SetScene(RoomEntryRequest *t, u32 v);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetPos
void RoomEntryRequest_SetPos(RoomEntryRequest *t, VecFx32 *v);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetAngle
void RoomEntryRequest_SetAngle(RoomEntryRequest *t, u32 v);
#endif
#ifndef PROTO_LOCAL_RoomEntryRequest_SetRetreatPos
void RoomEntryRequest_SetRetreatPos(RoomEntryRequest *t, VecFx32 *v);
#endif
}
#ifndef PROTO_LOCAL_sRoomEntryRequest
extern RoomEntryRequest sRoomEntryRequest;
#endif
#ifndef PROTO_LOCAL_sSceneOccupantTable
extern SceneOccupantTable sSceneOccupantTable;
#endif
#endif

#endif

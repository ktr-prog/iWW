#ifndef PROTO_PROTO_MAIN_UNK_020A427C_H
#define PROTO_PROTO_MAIN_UNK_020A427C_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "net/NetSessionState.h"
#include "sys/ProcBase.h"
#include "sys/SceneBase.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NetArea_GetSlotScene
s32 NetArea_GetSlotScene(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_IsSlotOwner
s32 NetArea_IsSlotOwner(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_IsSlotMoving
s32 NetArea_IsSlotMoving(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_IsLocalOwner
s32 NetArea_IsLocalOwner();
#endif
#ifndef PROTO_LOCAL_NetArea_IsLocalMoving
s32 NetArea_IsLocalMoving();
#endif
#ifndef PROTO_LOCAL_NetArea_FindOwner
s32 NetArea_FindOwner(u32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_ResolveRoute
s32 NetArea_ResolveRoute(s32 a, s32 b, u32 c, u8 *d);
#endif
#ifndef PROTO_LOCAL_NetArea_SendStateA
void NetArea_SendStateA(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_SendStateB
void NetArea_SendStateB(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_FindSlotInScene
s32 NetArea_FindSlotInScene(u32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_SendMoveTarget
void NetArea_SendMoveTarget();
#endif
#ifndef PROTO_LOCAL_NetSession_SetSyncState
void NetSession_SetSyncState(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NetSession_GetSyncState
s32 NetSession_GetSyncState(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_SetSyncMemberMask
void NetSession_SetSyncMemberMask(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_GetSyncMemberMask
u16 NetSession_GetSyncMemberMask();
#endif
#ifndef PROTO_LOCAL_NetSession_SetSyncRequester
void NetSession_SetSyncRequester(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_SetMemberSyncReply
void NetSession_SetMemberSyncReply(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NetSession_SetSyncKind
void NetSession_SetSyncKind(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_GetSyncKind
s32 NetSession_GetSyncKind();
#endif
#ifndef PROTO_LOCAL_NetSession_SetActiveSyncKind
void NetSession_SetActiveSyncKind(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_GetActiveSyncKind
s32 NetSession_GetActiveSyncKind();
#endif
#ifndef PROTO_LOCAL_NetSession_GetLastSyncSlot
s32 NetSession_GetLastSyncSlot();
#endif
#ifndef PROTO_LOCAL_NetSession_SetLastSyncSlot
void NetSession_SetLastSyncSlot(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_SetMoveState
void NetArea_SetMoveState(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_GetMoveState
s32 NetArea_GetMoveState();
#endif
#ifndef PROTO_LOCAL_NetArea_SetMemberAck
void NetArea_SetMemberAck(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_NetArea_SetStateRequester
void NetArea_SetStateRequester(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_SetOwnerAck
void NetArea_SetOwnerAck(s32 a);
#endif
#ifndef PROTO_LOCAL_NetArea_GetSlotStatus
void NetArea_GetSlotStatus(s32 idx, u8 *a, u8 *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_NetArea_OnStateAReceived
void NetArea_OnStateAReceived();
#endif
#ifndef PROTO_LOCAL_NetArea_ApplyStateB
void NetArea_ApplyStateB();
#endif
#ifndef PROTO_LOCAL_NetArea_SendStateToNewOwner
void NetArea_SendStateToNewOwner();
#endif
#ifndef PROTO_LOCAL_NetArea_SendStateToRequester
void NetArea_SendStateToRequester();
#endif
#ifndef PROTO_LOCAL_NetSession_SetCtrl07Received
void NetSession_SetCtrl07Received(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_GetCtrl07Received
u8 NetSession_GetCtrl07Received();
#endif
#ifndef PROTO_LOCAL_NetArea_IsUnsharedScene
BOOL NetArea_IsUnsharedScene(s32 v);
#endif
#ifndef PROTO_LOCAL_NetSession_Init
void NetSession_Init();
#endif
#ifndef PROTO_LOCAL_NetSession_Exit
void NetSession_Exit();
#endif
#ifndef PROTO_LOCAL_NetSession_OnBeginHost
void NetSession_OnBeginHost();
#endif
#ifndef PROTO_LOCAL_NetSession_Reset
void NetSession_Reset();
#endif
#ifndef PROTO_LOCAL_NetSession_RemoveSlot
void NetSession_RemoveSlot(s32 a);
#endif
#ifndef PROTO_LOCAL_NetSession_Update
void NetSession_Update();
#endif
#ifndef PROTO_LOCAL_NetSession_PostUpdate
void NetSession_PostUpdate();
#endif
#ifndef PROTO_LOCAL_SceneBase_SetupGraphics
void SceneBase_SetupGraphics(void);
#endif
#ifndef PROTO_LOCAL_Scene_Request
void Scene_Request(u32 a, u32 b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Scene_RequestBoot
void Scene_RequestBoot(void);
#endif
#ifndef PROTO_LOCAL_Scene_CreateRequested
BOOL Scene_CreateRequested(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SceneBase_Create
SceneBase *SceneBase_Create(void);
#endif
#ifndef PROTO_LOCAL_Scene_CheckExit
void Scene_CheckExit(ProcBase *p);
#endif
}
#ifndef PROTO_LOCAL_sSceneFadeInType
extern u8 sSceneFadeInType;
#endif
#ifndef PROTO_LOCAL_data_021eda58
extern u8 data_021eda58;
#endif
#ifndef PROTO_LOCAL_gNetSessionState
extern NetSessionState gNetSessionState;
#endif
#ifndef PROTO_LOCAL_sSceneBaseProfile
extern ProcProfile sSceneBaseProfile;
#endif
#ifndef PROTO_LOCAL_gNextSceneProfile
extern u16 gNextSceneProfile;
#endif
#ifndef PROTO_LOCAL_gActorDefaultParent
extern ProcBase *gActorDefaultParent;
#endif
#ifndef PROTO_LOCAL_sSceneFadeOutType
extern u8 sSceneFadeOutType;
#endif
#ifndef PROTO_LOCAL_sSceneFadeInDelay
extern volatile u8 sSceneFadeInDelay;
#endif
#ifndef PROTO_LOCAL_gSceneCreating
extern u8 gSceneCreating;
#endif
#ifndef PROTO_LOCAL_sSceneExists
extern u8 sSceneExists;
#endif
#ifndef PROTO_LOCAL_data_021eda50
extern u8 data_021eda50;
#endif
#endif

#endif

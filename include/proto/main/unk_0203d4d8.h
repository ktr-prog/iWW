#ifndef PROTO_PROTO_MAIN_UNK_0203D4D8_H
#define PROTO_PROTO_MAIN_UNK_0203D4D8_H


#include "types.h"
#include "sys/ProcProfile.h"
struct TalkRequestList;
#ifndef __cplusplus
typedef struct TalkRequestList TalkRequestList;
#endif
#ifdef __cplusplus
#include "actor/Character.h"
#include "talk/TalkMsgRequest.h"
#include "talk/TalkRequestEntry.h"
#include "talk/TalkRequestQueue.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_TalkRequestQueue_Reset
void TalkRequestQueue_Reset(void);
#endif
#ifndef PROTO_LOCAL_TalkRequestQueue_StartInitial
void TalkRequestQueue_StartInitial(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsActive
BOOL TalkRequest_IsActive(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunMenu
u32 TalkRequest_RunMenu(u32 a);
#endif
#ifndef PROTO_LOCAL_TalkRequest_EndMenu
BOOL TalkRequest_EndMenu(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsCurrentKind
BOOL TalkRequest_IsCurrentKind(u32 x);
#endif
#ifndef PROTO_LOCAL_TalkRequest_Add
BOOL TalkRequest_Add(u32 a, u32 b, u32 c, u32 d, u8 e);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddLeaveRoom
BOOL TalkRequest_AddLeaveRoom();
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishLeaveRoom
BOOL TalkRequest_FinishLeaveRoom();
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddMenu
BOOL TalkRequest_AddMenu(u8 x);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddEventWarp
BOOL TalkRequest_AddEventWarp();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_IsEventWarpStarted
BOOL TalkRequestFlags_IsEventWarpStarted();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_IsEventWarpReady
BOOL TalkRequestFlags_IsEventWarpReady();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_SetEventWarpStarted
void TalkRequestFlags_SetEventWarpStarted();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_SetEventWarpReady
void TalkRequestFlags_SetEventWarpReady();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_IsSceneHold
BOOL TalkRequestFlags_IsSceneHold();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_SetSceneHold
void TalkRequestFlags_SetSceneHold();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_ClearSceneHold
void TalkRequestFlags_ClearSceneHold();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_IsResetti
BOOL TalkRequestFlags_IsResetti();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_SetResetti
void TalkRequestFlags_SetResetti();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_ClearResetti
void TalkRequestFlags_ClearResetti();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_IsEventWarpBlock
BOOL TalkRequestFlags_IsEventWarpBlock();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_SetEventWarpBlock
void TalkRequestFlags_SetEventWarpBlock();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_ClearEventWarpBlock
void TalkRequestFlags_ClearEventWarpBlock();
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_Test
BOOL TalkRequestFlags_Test(u32 mask);
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_Set
void TalkRequestFlags_Set(u32 mask);
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_Clear
void TalkRequestFlags_Clear(u32 mask);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddPlayerExclusive
BOOL TalkRequest_AddPlayerExclusive(u32 x);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsExclusiveRunning
BOOL TalkRequest_IsExclusiveRunning(u32 x);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishExclusive
BOOL TalkRequest_FinishExclusive(u32 x);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddSaveMenu
BOOL TalkRequest_AddSaveMenu(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsSaveMenuRunning
BOOL TalkRequest_IsSaveMenuRunning(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishSaveMenu
BOOL TalkRequest_FinishSaveMenu(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddCameraView
BOOL TalkRequest_AddCameraView(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsCameraViewRunning
BOOL TalkRequest_IsCameraViewRunning(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishCameraView
BOOL TalkRequest_FinishCameraView(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddPlayerMessage
BOOL TalkRequest_AddPlayerMessage(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishPlayerMessage
BOOL TalkRequest_FinishPlayerMessage(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsPlayerMessage
BOOL TalkRequest_IsPlayerMessage(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddSlingshot
BOOL TalkRequest_AddSlingshot(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishSlingshot
BOOL TalkRequest_FinishSlingshot(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishSceneEntry
BOOL TalkRequest_FinishSceneEntry(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_IsTalking
BOOL TalkRequest_IsTalking(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_SetTalkTarget
void TalkRequest_SetTalkTarget(u32 p);
#endif
#ifndef PROTO_LOCAL_TalkRequest_FinishCurrent
void TalkRequest_FinishCurrent(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_BeginNetSyncHold
BOOL TalkRequest_BeginNetSyncHold(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_EndNetSyncHold
BOOL TalkRequest_EndNetSyncHold(void);
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_IsTitleTimeout
s32 TalkRequestFlags_IsTitleTimeout(void);
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_SetTitleTimeout
void TalkRequestFlags_SetTitleTimeout(void);
#endif
#ifndef PROTO_LOCAL_TalkRequestFlags_ClearTitleTimeout
void TalkRequestFlags_ClearTitleTimeout(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_TalkRequestQueue_Create
TalkRequestQueue *TalkRequestQueue_Create(void);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartMenu
BOOL TalkRequest_StartMenu(TalkRequestEntry *s);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AcquireHostLock
BOOL TalkRequest_AcquireHostLock(TalkRequestEntry *s);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AcquireAreaTarget
BOOL TalkRequest_AcquireAreaTarget(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AcquireTarget
BOOL TalkRequest_AcquireTarget(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_NotifyTarget
void TalkRequest_NotifyTarget(Character *o, u32 v);
#endif
#ifndef PROTO_LOCAL_TalkRequest_ReleaseTarget
void TalkRequest_ReleaseTarget(TalkRequestEntry *t, u32 v);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartTalk
BOOL TalkRequest_StartTalk(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_BeginTalk
BOOL TalkRequest_BeginTalk(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartTalk6
BOOL TalkRequest_StartTalk6(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunTalk
BOOL TalkRequest_RunTalk(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_EndTalk
BOOL TalkRequest_EndTalk(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartTalk7
BOOL TalkRequest_StartTalk7(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartSceneExit
BOOL TalkRequest_StartSceneExit(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartEventWarp
BOOL TalkRequest_StartEventWarp(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_BeginEventWarp
BOOL TalkRequest_BeginEventWarp(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_BeginSceneEntryChar
BOOL TalkRequest_BeginSceneEntryChar(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_EndSceneEntryChar
BOOL TalkRequest_EndSceneEntryChar(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunSceneEntry
BOOL TalkRequest_RunSceneEntry(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartExclusive
BOOL TalkRequest_StartExclusive(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunExclusive
BOOL TalkRequest_RunExclusive(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_EndExclusive
BOOL TalkRequest_EndExclusive(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartLeaveRoom
BOOL TalkRequest_StartLeaveRoom(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunLeaveRoom
BOOL TalkRequest_RunLeaveRoom(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StartSimple
BOOL TalkRequest_StartSimple(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunSimple
BOOL TalkRequest_RunSimple(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_RunNetSyncHold
BOOL TalkRequest_RunNetSyncHold(TalkRequestEntry *t);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StepUnused
BOOL TalkRequest_StepUnused(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StepPass
BOOL TalkRequest_StepPass(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_StepBlock
BOOL TalkRequest_StepBlock(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequestQueue_StartNext
void TalkRequestQueue_StartNext(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequestQueue_StepBegin
void TalkRequestQueue_StepBegin(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequestQueue_StepRun
void TalkRequestQueue_StepRun(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequestQueue_StepEnd
void TalkRequestQueue_StepEnd(TalkRequestEntry *);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddSceneExit
BOOL TalkRequest_AddSceneExit(Character *o, s32 v);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddTalk
BOOL TalkRequest_AddTalk(Character *a, Character *b);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddPlayerTalk6
BOOL TalkRequest_AddPlayerTalk6(Character *a, s32 b);
#endif
#ifndef PROTO_LOCAL_TalkRequest_AddPlayerTalk7
BOOL TalkRequest_AddPlayerTalk7(Character *a, s32 b);
#endif
#ifndef PROTO_LOCAL_TalkRequest_SetTargetDone
BOOL TalkRequest_SetTargetDone(Character *x);
#endif
#ifndef PROTO_LOCAL_TalkRequest_GetTalkTarget
Character *TalkRequest_GetTalkTarget(void);
#endif
#ifndef PROTO_LOCAL_Talk_AttachRequestToWindow0
void Talk_AttachRequestToWindow0(TalkMsgRequest *x);
#endif
#ifndef PROTO_LOCAL_Talk_DetachRequest
void Talk_DetachRequest(TalkMsgRequest *p);
#endif
}
#ifndef PROTO_LOCAL_data_020d9520
extern ProcProfile data_020d9520;
#endif
#ifndef PROTO_LOCAL_sTalkRequestFlags
extern u32 sTalkRequestFlags;
#endif
#ifndef PROTO_LOCAL_gTalkRequestCurrent
extern TalkRequestEntry *gTalkRequestCurrent;
#endif
#ifndef PROTO_LOCAL_sTalkRequestList
extern TalkRequestList sTalkRequestList;
#endif
#ifndef PROTO_LOCAL_sTalkTargetId
extern u32 sTalkTargetId;
#endif
#endif

#endif

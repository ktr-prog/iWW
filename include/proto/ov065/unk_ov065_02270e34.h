#ifndef PROTO_PROTO_OV065_UNK_OV065_02270E34_H
#define PROTO_PROTO_OV065_UNK_OV065_02270E34_H


#include "types.h"
#include "net/DwcControl.h"
#include "net/DwcFriendControl.h"
#include "net/DwcUserData.h"
#include "net/gp.h"
#include "net/gpiInfo.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sDwcLoginDoneCallback
extern DwcNasLoginCallback sDwcLoginDoneCallback;
#endif
#ifndef PROTO_LOCAL_sDwcLoginControl
extern DwcLoginControl *sDwcLoginControl;
#endif
#ifndef PROTO_LOCAL_sDwcLoginDoneArg
extern u32 sDwcLoginDoneArg;
#endif
#ifndef PROTO_LOCAL_sDwcErrorCode
extern s32 sDwcErrorCode;
#endif
#ifndef PROTO_LOCAL_sDwcErrorClass
extern s32 sDwcErrorClass;
#endif
#ifndef PROTO_LOCAL_sDwcFriendControl
extern DwcFriendControl *sDwcFriendControl;
#endif
#ifndef PROTO_LOCAL_DwcFriend_GetStatus
s32 DwcFriend_GetStatus(void *a, u8 *p1, u8 *p2, char *dst);
#endif
#ifndef PROTO_LOCAL_DwcFriend_GetStatusData
s32 DwcFriend_GetStatusData(void *a, u8 *b, u8 *c, char *d, s32 *out);
#endif
#ifndef PROTO_LOCAL_DwcFriend_CountValid
s32 DwcFriend_CountValid(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcFriend_SetStatusData
BOOL DwcFriend_SetStatusData(void *a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_IsIdle
BOOL DwcFriend_IsIdle();
#endif
#ifndef PROTO_LOCAL_DwcFriend_DeleteFriend
void DwcFriend_DeleteFriend(void *p);
#endif
#ifndef PROTO_LOCAL_DwcFriend_InitControl
void DwcFriend_InitControl(DwcFriendControl *a, GPConnection *b, char *c, DwcFriendData *d, s32 e);
#endif
#ifndef PROTO_LOCAL_DwcFriend_Process
void DwcFriend_Process();
#endif
#ifndef PROTO_LOCAL_DwcFriend_StartUpdate
void DwcFriend_StartUpdate(char *a, char *b, void (*c)(s32, u32, s32), s32 d, DwcFriendStatusCallback e, s32 f, DwcFriendDeleteCallback g, s32 h);
#endif
#ifndef PROTO_LOCAL_DwcFriend_Fail
void DwcFriend_Fail(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_OnBuddyRequest
void DwcFriend_OnBuddyRequest(GPConnection *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_HandleAuthorizedMessage
s32 DwcFriend_HandleAuthorizedMessage(GPConnection *a, GPRecvBuddyMessageArg *b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_OnBuddyStatus
void DwcFriend_OnBuddyStatus(GPConnection *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_GetProfileId
s32 DwcFriend_GetProfileId(s32 i);
#endif
#ifndef PROTO_LOCAL_DwcFriend_FindIndexByProfileId
s32 DwcFriend_FindIndexByProfileId(s32 v);
#endif
#ifndef PROTO_LOCAL_DwcFriend_ResetTimer
void DwcFriend_ResetTimer();
#endif
#ifndef PROTO_LOCAL_DwcFriend_SetOwnStatus
s32 DwcFriend_SetOwnStatus(s32 a, const char *b, const char *c);
#endif
#ifndef PROTO_LOCAL_DwcFriend_NotifyAdded
void DwcFriend_NotifyAdded(s32 idx);
#endif
#ifndef PROTO_LOCAL_DwcFriend_ClearControl
void DwcFriend_ClearControl();
#endif
#ifndef PROTO_LOCAL_DwcFriend_Tick
s32 DwcFriend_Tick(void);
#endif
#ifndef PROTO_LOCAL_DwcFriend_Abort
void DwcFriend_Abort(void);
#endif
#ifndef PROTO_LOCAL_DwcFriend_SyncList
void DwcFriend_SyncList(DwcFriendData *arr, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcFriend_FinishUpdate
void DwcFriend_FinishUpdate(void);
#endif
#ifndef PROTO_LOCAL_DwcFriend_DeleteEntry
void DwcFriend_DeleteEntry(DwcFriendData *arr, s32 i, s32 j);
#endif
#ifndef PROTO_LOCAL_DwcFriend_MergeDuplicate
s32 DwcFriend_MergeDuplicate(DwcFriendData *arr, s32 n, s32 id);
#endif
#ifndef PROTO_LOCAL_DwcFriend_RemoveDuplicates
s32 DwcFriend_RemoveDuplicates(DwcFriendData *arr, s32 n, s32 id);
#endif
#ifndef PROTO_LOCAL_DwcFriend_SendBuddyRequest
s32 DwcFriend_SendBuddyRequest(s32 a);
#endif
#ifndef PROTO_LOCAL_DwcFriend_GetBuddyStatus
s32 DwcFriend_GetBuddyStatus(void *a, GPBuddyStatus *b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_HandleGpResult
s32 DwcFriend_HandleGpResult(s32 r);
#endif
#ifndef PROTO_LOCAL_DwcFriend_OnProfileSearch
void DwcFriend_OnProfileSearch(GPConnection *x, GPProfileSearchResponseArg *p, s32 idx);
#endif
#ifndef PROTO_LOCAL_DwcFriend_GetControlField20
u32 DwcFriend_GetControlField20(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_InitControl
void DwcLogin_InitControl(void *mem, DwcUserData *a, GPConnection *b, u32 c, u32 d, DwcLoginResultCallback e, u32 f);
#endif
#ifndef PROTO_LOCAL_DwcLogin_Begin
void DwcLogin_Begin(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_Process
void DwcLogin_Process(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_GetUserData
void *DwcLogin_GetUserData(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_Fail
void DwcLogin_Fail(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcLogin_Shutdown
void DwcLogin_Shutdown(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_ResetState
void DwcLogin_ResetState(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_HandleGpResult
s32 DwcLogin_HandleGpResult(s32 r);
#endif
#ifndef PROTO_LOCAL_DwcLogin_OnGpConnected
void DwcLogin_OnGpConnected(GPConnection *a0, GPConnectResponseArg *x);
#endif
#ifndef PROTO_LOCAL_DwcLogin_OnNasAuthDone
void DwcLogin_OnNasAuthDone(const char *a, const char *b, u32 arg);
#endif
#ifndef PROTO_LOCAL_DwcLogin_GpConnect
void DwcLogin_GpConnect(const char *a, const char *b, void *c, s32 d);
#endif
#ifndef PROTO_LOCAL_DwcLogin_StartNasAuth
void DwcLogin_StartNasAuth(DwcNasLoginCallback cb, u32 arg);
#endif
#ifndef PROTO_LOCAL_DwcLogin_PollNasAuth
void DwcLogin_PollNasAuth(void);
#endif
#ifndef PROTO_LOCAL_DwcLogin_IsLoggedIn
BOOL DwcLogin_IsLoggedIn(void);
#endif
#ifndef PROTO_LOCAL_DwcCore_GetLastError
s32 DwcCore_GetLastError(s32 *out);
#endif
#ifndef PROTO_LOCAL_DwcCore_ClearError
void DwcCore_ClearError(void);
#endif
#ifndef PROTO_LOCAL_DwcCore_HasError
BOOL DwcCore_HasError(void);
#endif
#ifndef PROTO_LOCAL_DwcCore_SetError
void DwcCore_SetError(s32 a, s32 b);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_DwcFriend_OnBuddyRequestInfo
void DwcFriend_OnBuddyRequestInfo(GPConnection *x, GPGetInfoResponseArg *p);
#endif
#ifndef PROTO_LOCAL_DwcFriend_OnAuthorizedInfo
void DwcFriend_OnAuthorizedInfo(GPConnection *x, GPGetInfoResponseArg *p);
#endif
#ifndef PROTO_LOCAL_DwcLogin_OnGpProfileInfo
void DwcLogin_OnGpProfileInfo(GPConnection *a0, GPGetInfoResponseArg *x);
#endif
}
#endif

#endif

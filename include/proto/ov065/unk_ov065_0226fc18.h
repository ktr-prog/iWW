#ifndef PROTO_PROTO_OV065_UNK_OV065_0226FC18_H
#define PROTO_PROTO_OV065_UNK_OV065_0226FC18_H


#include "types.h"
#include "net/DwcConnInfo.h"
#include "net/DwcControl.h"
#include "net/DwcFriendControl.h"
#include "net/DwcMatchControl.h"
#include "net/DwcUserData.h"
#include "net/gp.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sDwcControl
extern DwcControl *sDwcControl;
#endif
#ifndef PROTO_LOCAL_data_ov065_02290674
extern u32 data_ov065_02290674;
#endif
#ifndef PROTO_LOCAL_sDwcConnTable
extern void *sDwcConnTable[32];
#endif
#ifndef PROTO_LOCAL_sDwcConnInfo
extern DwcConnInfo sDwcConnInfo[32];
#endif
#ifndef PROTO_LOCAL_DwcCore_Init
void DwcCore_Init(DwcControl *g, DwcUserData *a1, u32 productId, const char *a3, const char *a4, s32 sendBufSize, s32 recvBufSize, DwcFriendData *friendList, s32 friendListLen);
#endif
#ifndef PROTO_LOCAL_DwcCore_Shutdown
void DwcCore_Shutdown(void);
#endif
#ifndef PROTO_LOCAL_DwcCore_CheckFatalError
s32 DwcCore_CheckFatalError(void);
#endif
#ifndef PROTO_LOCAL_DwcCore_Nop
void DwcCore_Nop(void);
#endif
#ifndef PROTO_LOCAL_DwcCore_Process
void DwcCore_Process();
#endif
#ifndef PROTO_LOCAL_DwcLogin_Start
void DwcLogin_Start(s32 a, s32 b, DwcDoneCallback c, s32 d);
#endif
#ifndef PROTO_LOCAL_DwcFriend_UpdateServersAsync
s32 DwcFriend_UpdateServersAsync(char *s, DwcDoneCallback f1, s32 f2, DwcFriendStatusCallback f3, s32 p5, DwcFriendDeleteCallback p6, s32 p7);
#endif
#ifndef PROTO_LOCAL_DwcMatch_SetupGameServer
void DwcMatch_SetupGameServer(s32 a, DwcMatchedScCallback b, void *c, DwcNewClientCallback d, void *e);
#endif
#ifndef PROTO_LOCAL_DwcMatch_ConnectToFriendServer
void DwcMatch_ConnectToFriendServer(s32 a, DwcMatchedScCallback cb, void *arg, DwcNewClientCallback d, void *e);
#endif
#ifndef PROTO_LOCAL_DwcConn_SetClosedCallback
void DwcConn_SetClosedCallback(DwcConnectionClosedCallback a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcConn_CloseAllConnections
s32 DwcConn_CloseAllConnections();
#endif
#ifndef PROTO_LOCAL_DwcConn_CloseConnection
s32 DwcConn_CloseConnection(u32 a);
#endif
#ifndef PROTO_LOCAL_DwcConn_GetConnectionCount
s32 DwcConn_GetConnectionCount();
#endif
#ifndef PROTO_LOCAL_DwcConn_GetMyAid
u32 DwcConn_GetMyAid();
#endif
#ifndef PROTO_LOCAL_DwcConn_GetAidList
s32 DwcConn_GetAidList(u8 **out);
#endif
#ifndef PROTO_LOCAL_DwcConn_GetAidBitmap
u32 DwcConn_GetAidBitmap();
#endif
#ifndef PROTO_LOCAL_DwcConn_IsAidValid
u32 DwcConn_IsAidValid(u32 bit);
#endif
#ifndef PROTO_LOCAL_DwcCore_GetState
s32 DwcCore_GetState();
#endif
#ifndef PROTO_LOCAL_DwcConn_CreateGt2Socket
s32 DwcConn_CreateGt2Socket();
#endif
#ifndef PROTO_LOCAL_DwcConn_FindConnectionByAid
void *DwcConn_FindConnectionByAid(u32 v);
#endif
#ifndef PROTO_LOCAL_DwcConn_GetAid
u32 DwcConn_GetAid(void *v);
#endif
#ifndef PROTO_LOCAL_DwcConn_GetSlotIndex
u32 DwcConn_GetSlotIndex(void *v);
#endif
#ifndef PROTO_LOCAL_DwcConn_FindFreeSlot
s32 DwcConn_FindFreeSlot();
#endif
#ifndef PROTO_LOCAL_DwcConn_ClearTables
void DwcConn_ClearTables();
#endif
#ifndef PROTO_LOCAL_DwcConn_GetSlot
void **DwcConn_GetSlot(u32 idx);
#endif
#ifndef PROTO_LOCAL_DwcConn_FindSlotByProfileId
void **DwcConn_FindSlotByProfileId(u32 key, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcConn_GetConnInfo
DwcConnInfo *DwcConn_GetConnInfo(u32 idx);
#endif
#ifndef PROTO_LOCAL_DwcConn_IsAidConnected
u32 DwcConn_IsAidConnected(u32 v);
#endif
#ifndef PROTO_LOCAL_DwcCore_SetState
void DwcCore_SetState(s32 s);
#endif
#ifndef PROTO_LOCAL_DwcConn_RemoveAid
u32 DwcConn_RemoveAid(u32 c);
#endif
#ifndef PROTO_LOCAL_DwcConn_AidListToBitmap
u32 DwcConn_AidListToBitmap(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcCore_HandleGpResult
s32 DwcCore_HandleGpResult(s32 x);
#endif
#ifndef PROTO_LOCAL_DwcConn_HandleGt2Result
s32 DwcConn_HandleGt2Result(s32 x);
#endif
#ifndef PROTO_LOCAL_DwcLogin_OnLoginDone
void DwcLogin_OnLoginDone(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcFriend_OnUpdateDone
void DwcFriend_OnUpdateDone(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcMatch_OnMatchDone
void DwcMatch_OnMatchDone(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
#endif
#ifndef PROTO_LOCAL_DwcCore_OnGpError
void DwcCore_OnGpError(s32 a, GPErrorArg *b);
#endif
#ifndef PROTO_LOCAL_DwcMatch_OnGpBuddyMessage
void DwcMatch_OnGpBuddyMessage(GPConnection *a, GPRecvBuddyMessageArg *b, void *c);
#endif
#ifndef PROTO_LOCAL_DwcConn_OnGt2Receive
void DwcConn_OnGt2Receive(void *a, void *b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_DwcConn_OnGt2Closed
void DwcConn_OnGt2Closed(void *a0, s32 a1);
#endif
#ifndef PROTO_LOCAL_DwcConn_OnGt2Ping
void DwcConn_OnGt2Ping(void *a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcConn_OnGt2SocketError
void DwcConn_OnGt2SocketError(void *socket);
#endif
#ifdef __cplusplus
}
#endif

#endif

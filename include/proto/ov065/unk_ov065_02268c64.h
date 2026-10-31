#ifndef PROTO_PROTO_OV065_UNK_OV065_02268C64_H
#define PROTO_PROTO_OV065_UNK_OV065_02268C64_H


#include "types.h"
#include "net/WifiLinkConfig.h"
#include "net/WifiLinkSendState.h"
#include "nitro/wm.h"
#include "sys/OSThread.h"
#include "uptr.h"
#ifdef __cplusplus
#include "net/WifiLinkEvent.h"
#include "net/WifiLinkWork.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWifiLinkWork
extern struct WifiLinkWork *volatile sWifiLinkWork;
#endif
#ifndef PROTO_LOCAL_sWifiLinkSendWaitQueue
extern OSThreadQueue sWifiLinkSendWaitQueue;
#endif
#ifndef PROTO_LOCAL_sWifiLinkSendLock
extern OSMutex sWifiLinkSendLock;
#endif
#ifndef PROTO_LOCAL_WifiLink_InitSendState
void WifiLink_InitSendState();
#endif
#ifndef PROTO_LOCAL_WifiLink_SendKeepAlive
void WifiLink_SendKeepAlive();
#endif
#ifndef PROTO_LOCAL_WifiLink_GetConnectedBssid
u8 *WifiLink_GetConnectedBssid();
#endif
#ifndef PROTO_LOCAL_WifiLink_GetConnectedSsid
u8 *WifiLink_GetConnectedSsid(u16 *out);
#endif
#ifndef PROTO_LOCAL_WifiLink_SendFrame
s32 WifiLink_SendFrame(u8 *a, void *b, u32 c);
#endif
#ifndef PROTO_LOCAL_WifiLink_OnSendDone
void WifiLink_OnSendDone(WMMsg *p);
#endif
#ifndef PROTO_LOCAL_WifiLink_OnKeepAliveSent
void WifiLink_OnKeepAliveSent(void);
#endif
#ifndef PROTO_LOCAL_WifiLink_TryLockFromIrq
BOOL WifiLink_TryLockFromIrq(OSMutex *m);
#endif
#ifndef PROTO_LOCAL_WifiLink_UnlockFromIrq
void WifiLink_UnlockFromIrq(OSMutex *m);
#endif
#ifndef PROTO_LOCAL_WifiLink_ClearApList
void WifiLink_ClearApList(void);
#endif
#ifndef PROTO_LOCAL_WifiLink_GetApListCount
u32 WifiLink_GetApListCount(void);
#endif
#ifndef PROTO_LOCAL_WifiLink_LockApList
BOOL WifiLink_LockApList(BOOL a);
#endif
#ifndef PROTO_LOCAL_WifiLink_GetApListEntry
void *WifiLink_GetApListEntry(u32 id);
#endif
#ifndef PROTO_LOCAL_WifiLink_Init
s32 WifiLink_Init(void *a, u32 b);
#endif
#ifndef PROTO_LOCAL_WifiLink_Finish
s32 WifiLink_Finish(void);
#endif
#ifndef PROTO_LOCAL_WifiLink_CleanupAsync
s32 WifiLink_CleanupAsync(void);
#endif
#ifndef PROTO_LOCAL_WifiLink_SearchAsync
s32 WifiLink_SearchAsync(const u8 *a, const u8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_WifiLink_BeginSearchAsync
s32 WifiLink_BeginSearchAsync(const u8 *a, const u8 *b, s32 c);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWifiLinkSendState
extern WifiLinkSendState sWifiLinkSendState;
#endif
#ifndef PROTO_LOCAL_WifiApList_AllocEntry
WifiApListEntry *WifiApList_AllocEntry(void);
#endif
#ifndef PROTO_LOCAL_WifiApList_GetOldest
WifiApListEntry *WifiApList_GetOldest(void);
#endif
#ifndef PROTO_LOCAL_WifiApList_FindByBssid
WifiApListEntry *WifiApList_FindByBssid(void *key);
#endif
#ifndef PROTO_LOCAL_WifiApList_FindById
WifiApListEntry *WifiApList_FindById(u32 id);
#endif
#ifndef PROTO_LOCAL_WifiApList_MoveToTail
void WifiApList_MoveToTail(WifiApListEntry *node);
#endif
#ifndef PROTO_LOCAL_WifiLink_StartupAsync
s32 WifiLink_StartupAsync(WifiLinkConfig *a, WifiLinkNotifyCallback b);
#endif
}
namespace N_97ec {
extern "C" {
#ifndef PROTO_LOCAL_WifiLink_ConnectAsync
s32 WifiLink_ConnectAsync(u8 *a, u8 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_WifiLink_DisconnectAsync
s32 WifiLink_DisconnectAsync();
#endif
#ifndef PROTO_LOCAL_WifiLink_TerminateAsync
s32 WifiLink_TerminateAsync();
#endif
#ifndef PROTO_LOCAL_WifiLink_GetPhase
u32 WifiLink_GetPhase();
#endif
#ifndef PROTO_LOCAL_WifiLink_UpdateOptions
u32 WifiLink_UpdateOptions(u32 v);
#endif
#ifndef PROTO_LOCAL_WifiLink_GetWork
WifiLinkWork *WifiLink_GetWork();
#endif
#ifndef PROTO_LOCAL_WifiLink_ApplyConfig
void WifiLink_ApplyConfig(WifiLinkConfig *p, WifiLinkNotifyCallback arg);
#endif
#ifndef PROTO_LOCAL_WifiLink_SetDefaultOptions
void WifiLink_SetDefaultOptions();
#endif
#ifndef PROTO_LOCAL_WifiLink_NextAllowedChannel
u32 WifiLink_NextAllowedChannel(s32 a);
#endif
#ifndef PROTO_LOCAL_WifiLink_NotifyRequest
void WifiLink_NotifyRequest(s32 a, void *b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_WifiLink_Notify
void WifiLink_Notify(s32 a, s32 b, uptr c, uptr d, s32 e);
#endif
#ifndef PROTO_LOCAL_WifiLink_SetPhase
void WifiLink_SetPhase(s32 st);
#endif
#ifndef PROTO_LOCAL_WifiLink_RestartKeepAliveAlarm
void WifiLink_RestartKeepAliveAlarm();
#endif
#ifndef PROTO_LOCAL_WifiLink_OnKeepAliveAlarm
void WifiLink_OnKeepAliveAlarm();
#endif
#ifndef PROTO_LOCAL_WifiLink_ResetOnError
void WifiLink_ResetOnError();
#endif
}
}
#endif

#endif

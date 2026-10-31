#ifndef PROTO_PROTO_OV066_UNK_OV066_0225F1A0_H
#define PROTO_PROTO_OV066_UNK_OV066_0225F1A0_H


#include "types.h"
#include "nitro/wm.h"
struct LocalWlBeacon;
struct LocalWlBeaconList;
struct LocalWlConfig;
struct LocalWlEventMsg;
struct LocalWlMpFrame;
struct LocalWlMpFramePayload;
struct LocalWlMpRecord;
struct LocalWlMpWork;
struct LocalWlScanWork;
struct LocalWlSession;
struct LocalWlWork;
#ifndef __cplusplus
typedef struct LocalWlBeacon LocalWlBeacon;
typedef struct LocalWlBeaconList LocalWlBeaconList;
typedef struct LocalWlConfig LocalWlConfig;
typedef struct LocalWlEventMsg LocalWlEventMsg;
typedef struct LocalWlMpFrame LocalWlMpFrame;
typedef struct LocalWlMpFramePayload LocalWlMpFramePayload;
typedef struct LocalWlMpRecord LocalWlMpRecord;
typedef struct LocalWlMpWork LocalWlMpWork;
typedef struct LocalWlScanWork LocalWlScanWork;
typedef struct LocalWlSession LocalWlSession;
typedef struct LocalWlWork LocalWlWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sLocalWlPowerApis
extern s32 (*sLocalWlPowerApis[4]) (void *);
#endif
#ifndef PROTO_LOCAL_data_ov066_022647c4
extern u32 data_ov066_022647c4;
#endif
#ifndef PROTO_LOCAL_data_ov066_022647c0
extern u32 data_ov066_022647c0;
#endif
#ifndef PROTO_LOCAL_data_ov066_022647bc
extern u32 data_ov066_022647bc;
#endif
#ifndef PROTO_LOCAL_sLocalWlRandSeed
extern u32 sLocalWlRandSeed;
#endif
#ifndef PROTO_LOCAL_sLocalWlAllocHook
extern void *(*sLocalWlAllocHook) (u32, u32);
#endif
#ifndef PROTO_LOCAL_sLocalWlErrorHook
extern void (*sLocalWlErrorHook) (u32);
#endif
#ifndef PROTO_LOCAL_sLocalWlFreeHook
extern void (*sLocalWlFreeHook) (void *);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_AllocRing
void *LocalWlMp_AllocRing(s32 n);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_Start
void LocalWlMp_Start(u8 *msg);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_Shutdown
void LocalWlMp_Shutdown(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_IsReadyToSend
s32 LocalWlMp_IsReadyToSend(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_Send
s32 LocalWlMp_Send(u8 *a, u32 b, u32 c, void (*d)(u32));
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnIndicationStub
void LocalWlMp_OnIndicationStub(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_FinishSend
void LocalWlMp_FinishSend(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnChildPacketSent
void LocalWlMp_OnChildPacketSent(WMPortSendCallback *w);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnFrameSent
void LocalWlMp_OnFrameSent(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_BuildChildPacket
void LocalWlMp_BuildChildPacket(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_ReceiveRecord
void LocalWlMp_ReceiveRecord(u32 idx, u8 *msg);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_ParentSendStep
void LocalWlMp_ParentSendStep(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_ChildSendStep
void LocalWlMp_ChildSendStep(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnMemberLeft
void LocalWlMp_OnMemberLeft(u32 idx);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_SetMpData
s32 LocalWlMp_SetMpData(u32 port, void *data, u32 size, u32 destMask, void *done);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_SendControl
void LocalWlMp_SendControl(u8 *data, u32 size, u32 destMask, void (*done)(void));
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnSetMpData
void LocalWlMp_OnSetMpData(WMPortSendCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_StoreChildPacket
void LocalWlMp_StoreChildPacket(u32 idx, void *src, u32 size);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnPacket
void LocalWlMp_OnPacket(WMPortRecvCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnDataDisconnectStub
void LocalWlMp_OnDataDisconnectStub(WMPortRecvCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_OnDataRecv
void LocalWlMp_OnDataRecv(WMPortRecvCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_Reset
void LocalWlMp_Reset(void);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_SetRecvBuffer
s32 LocalWlMp_SetRecvBuffer(s32 idx, u8 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_OnExpire
void LocalWlBcn_OnExpire(void *arg);
#endif
#ifndef PROTO_LOCAL_LocalWl_MeasureNextChannel
s32 LocalWl_MeasureNextChannel(u32 i);
#endif
#ifndef PROTO_LOCAL_LocalWl_UpdateAllowedChannels
void LocalWl_UpdateAllowedChannels(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_NextAllowedChannel
u32 LocalWl_NextAllowedChannel(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_MeasureChannel
s32 LocalWl_MeasureChannel(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnMeasureChannel
void LocalWl_OnMeasureChannel(WMMeasureChannelCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartMeasureChannels
void LocalWl_StartMeasureChannels(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_PickChannel
s32 LocalWl_PickChannel(u32 start);
#endif
#ifndef PROTO_LOCAL_LocalWl_ResetSessionInfo
void LocalWl_ResetSessionInfo(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_AllocBuffers
void LocalWl_AllocBuffers(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_InitWm
void LocalWl_InitWm(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_FinishWm
void LocalWl_FinishWm(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartSession
void LocalWl_StartSession(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_Rand
u32 LocalWl_Rand(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetMyAid
u32 LocalWl_GetMyAid(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetConnectedMask
u32 LocalWl_GetConnectedMask(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_IsReadyToSend
s32 LocalWl_IsReadyToSend(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_Send
s32 LocalWl_Send(u8 *a, u32 b, u32 c, void (*d)(u32));
#endif
#ifndef PROTO_LOCAL_LocalWl_BuildGameInfo
void LocalWl_BuildGameInfo(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_LocalWl_BuildParentParameter
void LocalWl_BuildParentParameter(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_BeginParent
void LocalWl_BeginParent(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_ConnectToSelected
void LocalWl_ConnectToSelected(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_ConnectToBeacon
void LocalWl_ConnectToBeacon(u8 *p, u32 v);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetGameInfo
s32 LocalWl_SetGameInfo(void *a, u32 n);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetMember
void LocalWl_SetMember(u32 idx, u8 *src);
#endif
#ifndef PROTO_LOCAL_LocalWl_SendReady
void LocalWl_SendReady(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_SendMemberTable
void LocalWl_SendMemberTable(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnMemberTableSent
void LocalWl_OnMemberTableSent(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_MergeMemberTable
void LocalWl_MergeMemberTable(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_LocalWl_CountMembers
void LocalWl_CountMembers(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_ClearMembers
void LocalWl_ClearMembers(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnControlRecv
void LocalWl_OnControlRecv(WMPortRecvCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_CallMemberLeftCb
void LocalWl_CallMemberLeftCb(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnBeaconSent
void LocalWl_OnBeaconSent(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnParentControl
void LocalWl_OnParentControl(WMPortRecvCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildReady
void LocalWl_OnChildReady(u32 idx, u8 *src);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildEvent8Stub
void LocalWl_OnChildEvent8Stub(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnParentLost
void LocalWl_OnParentLost(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildControl
void LocalWl_OnChildControl(WMPortRecvCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_ApplyMemberTable
void LocalWl_ApplyMemberTable(void *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_RequestEnd
void LocalWl_RequestEnd(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_CheckEndRequest
s32 LocalWl_CheckEndRequest(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetParentParameter
void LocalWl_SetParentParameter(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartParentNow
void LocalWl_StartParentNow(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_EndParent
void LocalWl_EndParent(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartConnect
void LocalWl_StartConnect(void *a);
#endif
#ifndef PROTO_LOCAL_LocalWl_Disconnect
s32 LocalWl_Disconnect(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_UpdateGameInfo
void LocalWl_UpdateGameInfo(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartMp
void LocalWl_StartMp(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_EndMp
void LocalWl_EndMp(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetEntry
void LocalWl_SetEntry(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnConnectFailReset
void LocalWl_OnConnectFailReset(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_ReadBe32
u32 LocalWl_ReadBe32(u8 *p);
#endif
#ifndef PROTO_LOCAL_LocalWl_CompareMac
s32 LocalWl_CompareMac(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartParent
void LocalWl_StartParent(u32 v);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartScanMode
void LocalWl_StartScanMode(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_NextRoleTurn
void LocalWl_NextRoleTurn(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_JoinBestParent
BOOL LocalWl_JoinBestParent(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepAuto
void LocalWl_StepAuto(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetMemberCount
u8 LocalWl_GetMemberCount(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_IsMacSet
BOOL LocalWl_IsMacSet(u8 *p);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetRecvCallback
void LocalWl_SetRecvCallback(void (*v)(u32, u8 *, u32));
#endif
#ifndef PROTO_LOCAL_LocalWl_AllocScanWork
void LocalWl_AllocScanWork(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_FreeScanWork
void LocalWl_FreeScanWork(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetBeaconFilter
void LocalWl_SetBeaconFilter(s32 (*v)(void *));
#endif
#ifndef PROTO_LOCAL_LocalWl_GetScanChannel
u32 LocalWl_GetScanChannel(u32 idx);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartScanLoop
void LocalWl_StartScanLoop(s32 t);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnScanTimer
void LocalWl_OnScanTimer(void *);
#endif
#ifndef PROTO_LOCAL_LocalWl_ScanNextChannel
void LocalWl_ScanNextChannel(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StopScanLoop
void LocalWl_StopScanLoop(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetupScanParam
void LocalWl_SetupScanParam(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnBeaconFound
void LocalWl_OnBeaconFound(WMStartScanCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnScanStopTimer
void LocalWl_OnScanStopTimer(void *);
#endif
#ifndef PROTO_LOCAL_LocalWl_StopScanSoon
void LocalWl_StopScanSoon(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_FilterBeacon
s32 LocalWl_FilterBeacon(void *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetBeaconCount
s32 LocalWl_GetBeaconCount(u32 idx);
#endif
#ifndef PROTO_LOCAL_LocalWl_StartScan
void LocalWl_StartScan(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnScan
void LocalWl_OnScan(WMStartScanCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_EndScan
s32 LocalWl_EndScan(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnEndScan
void LocalWl_OnEndScan(WMStartScanCallback *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetState
s32 LocalWl_GetState(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_ResetSettings
void LocalWl_ResetSettings(u32 a);
#endif
#ifndef PROTO_LOCAL_LocalWl_Init
s32 LocalWl_Init(u32 a, void *(*b)(u32, u32), void (*c)(void *), void (*d)(u32));
#endif
#ifndef PROTO_LOCAL_LocalWl_Finish
s32 LocalWl_Finish(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_IsModeReached
s32 LocalWl_IsModeReached(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_RequestMode
s32 LocalWl_RequestMode(s32 a, void (*b)(u32), u32 c);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepReady
void LocalWl_StepReady(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepEnabled
void LocalWl_StepEnabled(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepIdle
void LocalWl_StepIdle(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepParentWaiting
void LocalWl_StepParentWaiting(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepScanning
void LocalWl_StepScanning(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepConnecting
void LocalWl_StepConnecting(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepMeasuring
void LocalWl_StepMeasuring(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepParentMp
void LocalWl_StepParentMp(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_StepChildMp
void LocalWl_StepChildMp(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_Step
void LocalWl_Step(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_Abort
void LocalWl_Abort(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_IsAborting
s32 LocalWl_IsAborting(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_ResetIfActive
void LocalWl_ResetIfActive(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetLinkLevel
s32 LocalWl_GetLinkLevel(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_IsBeaconValid
u32 LocalWl_IsBeaconValid(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_Advance
void LocalWl_Advance(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnPowerApiDone
void LocalWl_OnPowerApiDone(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_CallPowerApi
void LocalWl_CallPowerApi(u32 idx);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnEnable
void LocalWl_OnEnable(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnDisable
void LocalWl_OnDisable(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnPowerOn
void LocalWl_OnPowerOn(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnPowerOff
void LocalWl_OnPowerOff(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_Reset
void LocalWl_Reset(void *p);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnReset
void LocalWl_OnReset(WMMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_ClearResetFlag
void LocalWl_ClearResetFlag(void);
#endif
#ifndef PROTO_LOCAL_LocalWl_Alloc
s32 LocalWl_Alloc(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_LocalWl_Free
void LocalWl_Free(void *p);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetError
void LocalWl_SetError(u32 v);
#endif
#ifndef PROTO_LOCAL_LocalWl_CallEventCallback
void LocalWl_CallEventCallback(void *p);
#endif
#ifndef PROTO_LOCAL_LocalWl_PostEvent
void LocalWl_PostEvent(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_LocalWl_SetEventCallback
s32 LocalWl_SetEventCallback(void (*fn)(void *));
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sLocalWlSession
extern LocalWlSession *sLocalWlSession;
#endif
#ifndef PROTO_LOCAL_sLocalWlMp
extern LocalWlMpWork *sLocalWlMp;
#endif
#ifndef PROTO_LOCAL_sLocalWl
extern LocalWlWork *sLocalWl;
#endif
#ifndef PROTO_LOCAL_sLocalWlScan
extern LocalWlScanWork *sLocalWlScan;
#endif
#ifndef PROTO_LOCAL_LocalWl_ApplyConfig
void LocalWl_ApplyConfig(LocalWlConfig *in);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_ClearRing
void LocalWlMp_ClearRing(LocalWlMpFrame *p, s32 n);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_PutSendRecord
u16 LocalWlMp_PutSendRecord(LocalWlMpRecord *rec);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_PutParentRecord
void LocalWlMp_PutParentRecord(LocalWlMpFrame *o);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_DeliverFrame
void LocalWlMp_DeliverFrame(LocalWlMpFramePayload *p);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_MergeFrame
s32 LocalWlMp_MergeFrame(LocalWlMpFrame *dst, LocalWlMpFrame *src);
#endif
#ifndef PROTO_LOCAL_LocalWlMp_FindFrame
LocalWlMpFrame *LocalWlMp_FindFrame(u32 id, LocalWlMpFrame *head);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_Init
void LocalWlBcn_Init(LocalWlBeaconList *o, u32 id, s32 n);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_Free
void LocalWlBcn_Free(LocalWlBeaconList *o);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_Add
s32 LocalWlBcn_Add(LocalWlBeaconList *o, s32 a, u8 *b, u32 c, u16 d, void *e);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_Count
u32 LocalWlBcn_Count(LocalWlBeaconList *o);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_Get
LocalWlBeacon *LocalWlBcn_Get(LocalWlBeaconList *o, u32 i);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_CancelAlarms
void LocalWlBcn_CancelAlarms(LocalWlBeaconList *o);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_Clear
void LocalWlBcn_Clear(LocalWlBeaconList *o);
#endif
#ifndef PROTO_LOCAL_LocalWlBcn_RefreshTimeouts
void LocalWlBcn_RefreshTimeouts(LocalWlBeaconList *o, s32 x);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildJoined
void LocalWl_OnChildJoined(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildLeft
void LocalWl_OnChildLeft(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildConnected
void LocalWl_OnChildConnected(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnSetParentParameter
void LocalWl_OnSetParentParameter(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnParentEvent
void LocalWl_OnParentEvent(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnEndParent
void LocalWl_OnEndParent(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnChildConnectEvent
void LocalWl_OnChildConnectEvent(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnDisconnect
void LocalWl_OnDisconnect(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnSetGameInfo
void LocalWl_OnSetGameInfo(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnMpEvent
void LocalWl_OnMpEvent(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnEndMp
void LocalWl_OnEndMp(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_OnSetEntry
void LocalWl_OnSetEntry(LocalWlEventMsg *m);
#endif
#ifndef PROTO_LOCAL_LocalWl_ConnectToParent
s32 LocalWl_ConnectToParent(LocalWlBeacon *p, void (*a)(u32), u32 b);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetBeacon
LocalWlBeacon *LocalWl_GetBeacon(u32 idx, u32 b);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetBeaconGameInfoSize
s32 LocalWl_GetBeaconGameInfoSize(LocalWlBeacon *r);
#endif
#ifndef PROTO_LOCAL_LocalWl_GetBeaconGameInfo
void *LocalWl_GetBeaconGameInfo(LocalWlBeacon *r);
#endif
}
#endif

#endif

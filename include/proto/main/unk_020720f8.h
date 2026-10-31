#ifndef PROTO_PROTO_MAIN_UNK_020720F8_H
#define PROTO_PROTO_MAIN_UNK_020720F8_H


#include "types.h"
#ifdef __cplusplus
#include "net/CommManager.h"
#include "sys/Heap.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Comm_ResetPeerState
void Comm_ResetPeerState(s32 r4);
#endif
#ifndef PROTO_LOCAL_Comm_EnterCritical
void Comm_EnterCritical();
#endif
#ifndef PROTO_LOCAL_Comm_LeaveCritical
void Comm_LeaveCritical();
#endif
#ifndef PROTO_LOCAL_Comm_OnReceive
void Comm_OnReceive(u32 a, u8 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Comm_IsSeqAtOrBefore
s32 Comm_IsSeqAtOrBefore(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Comm_IsSeqConfirmed
s32 Comm_IsSeqConfirmed(s32 a);
#endif
#ifndef PROTO_LOCAL_Comm_WriteAckHeaders
void Comm_WriteAckHeaders();
#endif
#ifndef PROTO_LOCAL_Comm_WriteSyncVars
s32 Comm_WriteSyncVars(u8 *dst, void *src, s32 n);
#endif
#ifndef PROTO_LOCAL_Comm_CollectRecordsFor
u32 Comm_CollectRecordsFor(u8 *dst, u32 id);
#endif
#ifndef PROTO_LOCAL_Comm_IsSyncFinished
s32 Comm_IsSyncFinished(u32 a);
#endif
#ifndef PROTO_LOCAL_Comm_WriteSyncReply
s32 Comm_WriteSyncReply(u32 a);
#endif
#ifndef PROTO_LOCAL_Comm_RemoveMember
void Comm_RemoveMember(s32 a);
#endif
#ifndef PROTO_LOCAL_Comm_Start
void Comm_Start(s32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Comm_StartOv067Mode
void Comm_StartOv067Mode();
#endif
#ifndef PROTO_LOCAL_Comm_End
s32 Comm_End();
#endif
#ifndef PROTO_LOCAL_Comm_EndOv067Mode
void Comm_EndOv067Mode();
#endif
#ifndef PROTO_LOCAL_Comm_DestroyHeap
void Comm_DestroyHeap();
#endif
#ifndef PROTO_LOCAL_Comm_ProcessReceived
void Comm_ProcessReceived(s32 x);
#endif
#ifndef PROTO_LOCAL_Comm_Update
void Comm_Update(s32 a);
#endif
#ifndef PROTO_LOCAL_Comm_SendEmpty
BOOL Comm_SendEmpty();
#endif
#ifndef PROTO_LOCAL_Comm_SetRecvBuffersAsHost
void Comm_SetRecvBuffersAsHost();
#endif
#ifndef PROTO_LOCAL_Comm_BeginHostSession
void Comm_BeginHostSession();
#endif
#ifndef PROTO_LOCAL_Comm_PrepareJoin
void Comm_PrepareJoin(u32 a);
#endif
#ifndef PROTO_LOCAL_Comm_ResetNetSession
void Comm_ResetNetSession();
#endif
#ifndef PROTO_LOCAL_Comm_SetRecvBuffers
void Comm_SetRecvBuffers(u32 a);
#endif
#ifndef PROTO_LOCAL_Comm_RequestSync
BOOL Comm_RequestSync(u8 a);
#endif
#ifndef PROTO_LOCAL_Comm_GetSyncState
s32 Comm_GetSyncState();
#endif
#ifndef PROTO_LOCAL_Comm_ClearSyncState
void Comm_ClearSyncState();
#endif
#ifndef PROTO_LOCAL_Comm_GetRemoteMask
u32 Comm_GetRemoteMask();
#endif
#ifndef PROTO_LOCAL_Comm_GetMemberMask
u32 Comm_GetMemberMask();
#endif
#ifndef PROTO_LOCAL_Comm_Shutdown
s32 Comm_Shutdown();
#endif
#ifndef PROTO_LOCAL_Comm_SetLostFlag
void Comm_SetLostFlag();
#endif
#ifndef PROTO_LOCAL_Comm_IsConnectionLost
BOOL Comm_IsConnectionLost(s32 a);
#endif
#ifndef PROTO_LOCAL_Comm_QueueRecords
BOOL Comm_QueueRecords(void *unused, u8 *buf, u32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Comm_CreateHeap
void Comm_CreateHeap(Heap *a);
#endif
}
#ifndef PROTO_LOCAL_Comm_CountNoAckFrames
void Comm_CountNoAckFrames(CommManager *self);
#endif
#ifndef PROTO_LOCAL_Comm_AnyPeerTimedOut
BOOL Comm_AnyPeerTimedOut();
#endif
#ifndef PROTO_LOCAL_NetOverlay_AssertWifi
void NetOverlay_AssertWifi();
#endif
#ifndef PROTO_LOCAL_NetOverlay_AssertWireless
void NetOverlay_AssertWireless();
#endif
#ifndef PROTO_LOCAL_NetOverlay_AssertOv067
void NetOverlay_AssertOv067();
#endif
#ifndef PROTO_LOCAL_NetOverlay_AssertAny
void NetOverlay_AssertAny();
#endif
#ifndef PROTO_LOCAL_sCommAckPackets
extern u8 sCommAckPackets[4];
#endif
#ifndef PROTO_LOCAL_gCommManagerInstance
extern CommManager gCommManagerInstance;
#endif
#endif

#endif

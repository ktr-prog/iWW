#ifndef PROTO_PROTO_OV065_UNK_OV065_02277140_H
#define PROTO_PROTO_OV065_UNK_OV065_02277140_H


#include "types.h"
#include "net/DwcNetChannel.h"
#include "nitro/math.h"
#ifdef __cplusplus
#include "net/DwcNetChannelTable.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sDwcNetRandState
extern MATHRandContext32 sDwcNetRandState;
#endif
#ifndef PROTO_LOCAL_DwcNet_Rand32
u32 DwcNet_Rand32(u32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_CanSendReliable
BOOL DwcNet_CanSendReliable(s32 id);
#endif
#ifndef PROTO_LOCAL_DwcNet_CanSend
BOOL DwcNet_CanSend(s32 id, s32 m);
#endif
#ifndef PROTO_LOCAL_DwcNet_SendReliable
BOOL DwcNet_SendReliable(s32 id, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_SendData
BOOL DwcNet_SendData(s32 m, s32 id, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_SetRecvBuffer
BOOL DwcNet_SetRecvBuffer(s32 id, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_PingAid
void DwcNet_PingAid(s32 id);
#endif
#ifndef PROTO_LOCAL_DwcNet_SetSendDoneCallback
void DwcNet_SetSendDoneCallback(void *cb);
#endif
#ifndef PROTO_LOCAL_DwcNet_SetRecvCallback
void DwcNet_SetRecvCallback(void *cb);
#endif
#ifndef PROTO_LOCAL_DwcNet_SetPingCallback
void DwcNet_SetPingCallback(void *cb);
#endif
#ifndef PROTO_LOCAL_DwcNet_SetMaxChunkSize
void DwcNet_SetMaxChunkSize(u32 v);
#endif
#ifndef PROTO_LOCAL_DwcNet_BuildHeader
void DwcNet_BuildHeader(void *p, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_DwcNet_ParseHeader
u32 DwcNet_ParseHeader(void *src);
#endif
#ifndef PROTO_LOCAL_DwcNet_GetHeaderSize
s32 DwcNet_GetHeaderSize(s32 m);
#endif
#ifndef PROTO_LOCAL_DwcNet_InitChannelTable
void DwcNet_InitChannelTable(void *p);
#endif
#ifndef PROTO_LOCAL_DwcNet_OnReceive
void DwcNet_OnReceive(void *a, void *b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_DwcNet_OnPing
void DwcNet_OnPing(void *a, s32 b);
#endif
#ifndef PROTO_LOCAL_DwcNet_ProcessSend
void DwcNet_ProcessSend(void);
#endif
#ifndef PROTO_LOCAL_DwcNet_ResetChannel
void DwcNet_ResetChannel(s32 id);
#endif
#ifndef PROTO_LOCAL_DwcNet_ClearChannelTable
void DwcNet_ClearChannelTable(void);
#endif
#ifndef PROTO_LOCAL_DwcNet_IsSending
u32 DwcNet_IsSending(s32 id);
#endif
#ifndef PROTO_LOCAL_DwcNet_GetRecvState
u32 DwcNet_GetRecvState(s32 id);
#endif
#ifndef PROTO_LOCAL_DwcNet_SendToAid
void DwcNet_SendToAid(s32 id, void *buf, s32 n, s32 f);
#endif
#ifndef PROTO_LOCAL_DwcNet_RecvReliable
void DwcNet_RecvReliable(void *a, void *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_RecvUnreliable
void DwcNet_RecvUnreliable(void *a, void *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_RecvHeader
void DwcNet_RecvHeader(s32 id, void *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_RecvBodyChunk
void DwcNet_RecvBodyChunk(s32 id, void *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcNet_RecvControlBody
void DwcNet_RecvControlBody(s32 a, void *b, s32 c);
#endif
#ifndef PROTO_LOCAL_DwcNet_GetSendSpace
s32 DwcNet_GetSendSpace(s32 id);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sDwcNetChannels
extern DwcNetChannelTable *sDwcNetChannels;
#endif
#ifndef PROTO_LOCAL_DwcNet_GetChannel
DwcNetChannel *DwcNet_GetChannel(s32 id);
#endif
}
#endif

#endif

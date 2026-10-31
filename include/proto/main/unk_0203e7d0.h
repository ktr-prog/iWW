#ifndef PROTO_PROTO_MAIN_UNK_0203E7D0_H
#define PROTO_PROTO_MAIN_UNK_0203E7D0_H


#include "types.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CharInteractSync_Reset
void CharInteractSync_Reset(void);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_SendReply
void CharInteractSync_SendReply(u8 a, u32 aid, ...);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_IsFree
u32 CharInteractSync_IsFree(u32 idx, u32 id);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_ClearLock
void CharInteractSync_ClearLock(u32 idx);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_Check
s32 CharInteractSync_Check(u32 id);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_RequestLock
void CharInteractSync_RequestLock(u32 id);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_ReleaseLock
void CharInteractSync_ReleaseLock(void);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_CheckArea
s32 CharInteractSync_CheckArea(void);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_SendQuery
void CharInteractSync_SendQuery(u32 id, u8 x);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_SendEvent
void CharInteractSync_SendEvent(u32 id, u8 x);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_SendCharMsg
void CharInteractSync_SendCharMsg(u32 id, u8 x, u8 mode);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_OnLockRequest
void CharInteractSync_OnLockRequest(u8 *msg, u32 aid);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_OnReply
void CharInteractSync_OnReply(u8 *msg);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_OnRelease
void CharInteractSync_OnRelease(void *msg, u32 aid);
#endif
#ifndef PROTO_LOCAL_CharInteractSync_OnCharMsg
void CharInteractSync_OnCharMsg(u8 *msg, u32 aid);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sCharInteractSyncResult
extern u8 sCharInteractSyncResult;
#endif
#ifndef PROTO_LOCAL_sCharInteractReservedId
extern u32 sCharInteractReservedId;
#endif
#ifndef PROTO_LOCAL_sCharInteractLockIds
extern u32 sCharInteractLockIds[4];
#endif
#endif

#endif

#ifndef PROTO_PROTO_OV065_UNK_OV065_0225F378_H
#define PROTO_PROTO_OV065_UNK_OV065_0225F378_H


#include "types.h"
#include "sys/OSMessageQueue.h"
#ifdef __cplusplus
#include "net/SockCoreCommand.h"
#include "net/SockCoreSocket.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSockMsgPool
extern void *sSockMsgPool;
#endif
#ifndef PROTO_LOCAL_sSockMsgFreeQueue
extern OSMessageQueue sSockMsgFreeQueue;
#endif
#ifndef PROTO_LOCAL_SockCore_CreateMsgPool
s32 SockCore_CreateMsgPool(s32 n);
#endif
#ifndef PROTO_LOCAL_SockCore_DestroyMsgPool
s32 SockCore_DestroyMsgPool(void);
#endif
#ifndef PROTO_LOCAL_SockCore_FreeMsg
void SockCore_FreeMsg(void *m);
#endif
#ifndef PROTO_LOCAL_SockCore_CommandThreadMain
void SockCore_CommandThreadMain(void *q);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SockCore_TakeFreeMsg
SockCoreCommand *SockCore_TakeFreeMsg(s32 c);
#endif
#ifndef PROTO_LOCAL_SockCore_AllocMsg
SockCoreCommand *SockCore_AllocMsg(void *fn, SockCoreSocket *o, s32 c);
#endif
#ifndef PROTO_LOCAL_SockCore_GetCommandQueue
void *SockCore_GetCommandQueue(SockCoreSocket *o);
#endif
#ifndef PROTO_LOCAL_SockCore_PostCommand
s32 SockCore_PostCommand(void *q, SockCoreCommand *m);
#endif
#ifndef PROTO_LOCAL_SockCore_PostCommandAsync
s32 SockCore_PostCommandAsync(SockCoreSocket *o, SockCoreCommand *m);
#endif
#ifndef PROTO_LOCAL_SockCore_PostCommandAndWait
s32 SockCore_PostCommandAndWait(void *q, SockCoreCommand *m);
#endif
#ifndef PROTO_LOCAL_SockCore_ExecOnRecvSide
s32 SockCore_ExecOnRecvSide(SockCoreSocket *o, SockCoreCommand *m);
#endif
#ifndef PROTO_LOCAL_SockCore_ExecOnSendSide
s32 SockCore_ExecOnSendSide(SockCoreSocket *o, SockCoreCommand *m);
#endif
#ifndef PROTO_LOCAL_SockCore_ExecCommand
s32 SockCore_ExecCommand(SockCoreSocket *o, SockCoreCommand *m);
#endif
}
#endif

#endif

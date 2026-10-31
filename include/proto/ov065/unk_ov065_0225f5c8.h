#ifndef PROTO_PROTO_OV065_UNK_OV065_0225F5C8_H
#define PROTO_PROTO_OV065_UNK_OV065_0225F5C8_H


#include "types.h"
#include "net/SockUdpDropCounters.h"
#include "sys/OSMessageQueue.h"
#include "sys/OSThread.h"
#include "uptr.h"
#ifdef __cplusplus
#include "net/SockCoreSocket.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSockConnectInProgressError
extern s32 sSockConnectInProgressError;
#endif
#ifndef PROTO_LOCAL_SockCore_CarveBuffer
u8 *SockCore_CarveBuffer(u8 *base, u8 **buf, u32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSockUdpDropCount
extern SockUdpDropCounters sSockUdpDropCount;
#endif
#ifndef PROTO_LOCAL_SockCore_Create
sptr SockCore_Create(SockCreateParams *p);
#endif
#ifndef PROTO_LOCAL_SockCore_CalcSize
u32 SockCore_CalcSize(SockCreateParams *p);
#endif
#ifndef PROTO_LOCAL_SockCore_CalcThreadAreaSize
u32 SockCore_CalcThreadAreaSize(SockThreadParams *t);
#endif
#ifndef PROTO_LOCAL_SockCore_StartCommandThread
u8 *SockCore_StartCommandThread(u8 *area, OSMessageQueue *queue, OSThread *thread, OSMutex *mutex, void *pipe, SockThreadParams *c);
#endif
}
#endif

#endif

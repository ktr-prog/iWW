#ifndef PROTO_PROTO_OV065_UNK_OV065_0227931C_H
#define PROTO_PROTO_OV065_UNK_OV065_0227931C_H


#include "types.h"
#include "net/ghttpBuffer.h"
#include "net/ghttpConnection.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ghiThrottleBufferSize
extern s32 ghiThrottleBufferSize;
#endif
#ifndef PROTO_LOCAL_ghiThrottleTimeDelay
extern u32 ghiThrottleTimeDelay;
#endif
#ifndef PROTO_LOCAL_ghiConnections
extern GHIConnection **ghiConnections;
#endif
#ifndef PROTO_LOCAL_ghiNextUniqueID
extern s32 ghiNextUniqueID;
#endif
#ifndef PROTO_LOCAL_ghiNumConnections
extern s32 ghiNumConnections;
#endif
#ifndef PROTO_LOCAL_ghiConnectionsLen
extern s32 ghiConnectionsLen;
#endif
#ifndef PROTO_LOCAL_ghiProxyAddress
extern char *ghiProxyAddress;
#endif
#ifndef PROTO_LOCAL_ghiProxyPort
extern u32 ghiProxyPort;
#endif
#ifndef PROTO_LOCAL_ghiReferenceCount
extern s32 ghiReferenceCount;
#endif
#ifndef PROTO_LOCAL_ghttpStartup
void ghttpStartup();
#endif
#ifndef PROTO_LOCAL_ghttpCleanup
void ghttpCleanup();
#endif
#ifndef PROTO_LOCAL_ghttpGetA
s32 ghttpGetA(const char *a, s32 b, ghttpCompletedCallback c, void *d);
#endif
#ifndef PROTO_LOCAL_ghttpGetExA
s32 ghttpGetExA(const char *a, const char *b, char *c, s32 d, GHIPost *e, u32 f, s32 g, ghttpProgressCallback h, ghttpCompletedCallback i, void *j);
#endif
#ifndef PROTO_LOCAL_ghttpPostA
s32 ghttpPostA(const char *a, GHIPost *b, s32 c, ghttpCompletedCallback d, void *e);
#endif
#ifndef PROTO_LOCAL_ghttpPostExA
s32 ghttpPostExA(const char *a, const char *b, GHIPost *c, u32 d, s32 e, ghttpProgressCallback f, ghttpCompletedCallback g, void *h);
#endif
#ifndef PROTO_LOCAL_ghttpThink
void ghttpThink();
#endif
#ifndef PROTO_LOCAL_ghttpNewPost
GHIPost *ghttpNewPost();
#endif
#ifndef PROTO_LOCAL_ghttpPostAddStringA
s32 ghttpPostAddStringA(GHIPost *a, const char *b, const char *c);
#endif
#ifndef PROTO_LOCAL_ghiFindFreeSlot
s32 ghiFindFreeSlot();
#endif
#ifndef PROTO_LOCAL_ghiNewConnection
GHIConnection *ghiNewConnection();
#endif
#ifndef PROTO_LOCAL_ghiFreeConnection
BOOL ghiFreeConnection(GHIConnection *s);
#endif
#ifndef PROTO_LOCAL_ghiEnumConnections
void ghiEnumConnections(BOOL (*cb)(GHIConnection *));
#endif
#ifndef PROTO_LOCAL_ghiRedirectConnection
void ghiRedirectConnection(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiCleanupConnections
void ghiCleanupConnections();
#endif
#ifndef PROTO_LOCAL_ghiCreateLock
void ghiCreateLock();
#endif
#ifndef PROTO_LOCAL_ghiFreeLock
void ghiFreeLock();
#endif
#ifndef PROTO_LOCAL_ghiLock
void ghiLock();
#endif
#ifndef PROTO_LOCAL_ghiUnlock
void ghiUnlock();
#endif
#ifndef PROTO_LOCAL_ghiDecryptReceivedData
BOOL ghiDecryptReceivedData(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoReceive
s32 ghiDoReceive(GHIConnection *self, char *buf, s32 *plen);
#endif
#ifndef PROTO_LOCAL_ghiDoSend
s32 ghiDoSend(GHIConnection *self, const char *buf, s32 len);
#endif
#ifndef PROTO_LOCAL_ghiTrySendThenBuffer
s32 ghiTrySendThenBuffer(GHIConnection *self, const char *buf, s32 len);
#endif
#ifndef PROTO_LOCAL_ghiCallCompletedCallback
void ghiCallCompletedCallback(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiCallProgressCallback
void ghiCallProgressCallback(GHIConnection *self, char *p1, u32 p2);
#endif
#ifndef PROTO_LOCAL_ghiCallPostCallback
void ghiCallPostCallback(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiResizeBuffer
s32 ghiResizeBuffer(GHIBuffer *o, s32 n);
#endif
#ifndef PROTO_LOCAL_ghiInitBuffer
s32 ghiInitBuffer(GHIConnection *ow, GHIBuffer *o, s32 size, s32 grow);
#endif
#ifndef PROTO_LOCAL_ghiInitFixedBuffer
s32 ghiInitFixedBuffer(GHIConnection *ow, GHIBuffer *o, char *buf, s32 size);
#endif
#ifndef PROTO_LOCAL_ghiFreeBuffer
void ghiFreeBuffer(GHIBuffer *o);
#endif
#ifndef PROTO_LOCAL_ghiAppendDataToBuffer
s32 ghiAppendDataToBuffer(GHIBuffer *o, const char *s, s32 len);
#endif
#ifdef __cplusplus
}
#endif

#endif

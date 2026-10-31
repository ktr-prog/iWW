#ifndef PROTO_PROTO_OV065_UNK_OV065_02283F34_H
#define PROTO_PROTO_OV065_UNK_OV065_02283F34_H


#include "types.h"
#ifdef __cplusplus
#include "net/gt2Main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_0228e14c
extern u8 data_ov065_0228e14c[4];
#endif
#ifndef PROTO_LOCAL_gti2CloseAllConnectionsHardMap
s32 gti2CloseAllConnectionsHardMap(void *elem, void *arg);
#endif
#ifndef PROTO_LOCAL_gti2VerifyChallenge
BOOL gti2VerifyChallenge(u8 *p);
#endif
#ifndef PROTO_LOCAL_gti2GetChallenge
char *gti2GetChallenge(u8 *out);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gti2HandlePong
BOOL gti2HandlePong(GTI2Connection *c, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2HandleClosed
BOOL gti2HandleClosed(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gti2HandleUnreliableMessage
BOOL gti2HandleUnreliableMessage(GTI2Connection *c, s32 t, u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_gti2HandleMessage
s32 gti2HandleMessage(GTI2Socket *s, u8 *data, s32 n, s32 addr, s32 port);
#endif
#ifndef PROTO_LOCAL_gti2HandleConnectionReset
s32 gti2HandleConnectionReset(GTI2Socket *s, s32 addr, u32 port);
#endif
#ifndef PROTO_LOCAL_gti2ReceiveMessages
s32 gti2ReceiveMessages(GTI2Socket *s);
#endif
#ifndef PROTO_LOCAL_gti2StoreOutgoingReliableMessageInfo
s32 gti2StoreOutgoingReliableMessageInfo(GTI2Connection *o, u32 seq, s32 need);
#endif
#ifndef PROTO_LOCAL_gti2BeginReliableMessage
s32 gti2BeginReliableMessage(GTI2Connection *o, u32 type, s32 need, s32 *out);
#endif
#ifndef PROTO_LOCAL_gti2EndReliableMessage
s32 gti2EndReliableMessage(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendAppReliable
s32 gti2SendAppReliable(GTI2Connection *o, u8 *a, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2SendClientChallenge
s32 gti2SendClientChallenge(GTI2Connection *o, u8 *a);
#endif
#ifndef PROTO_LOCAL_gti2SendServerChallenge
s32 gti2SendServerChallenge(GTI2Connection *o, u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_gti2SendClientResponse
s32 gti2SendClientResponse(GTI2Connection *o, u8 *a, u8 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2SendAccept
s32 gti2SendAccept(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendReject
s32 gti2SendReject(GTI2Connection *o, u8 *a, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2SendClose
s32 gti2SendClose(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendKeepAlive
s32 gti2SendKeepAlive(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendAppUnreliable
s32 gti2SendAppUnreliable(GTI2Connection *o, u8 *data, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2SendAck
s32 gti2SendAck(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendNack
s32 gti2SendNack(GTI2Connection *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_gti2SendPing
s32 gti2SendPing(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendPong
s32 gti2SendPong(GTI2Connection *o, u8 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2SendClosed
s32 gti2SendClosed(GTI2Connection *o);
#endif
#ifndef PROTO_LOCAL_gti2SendClosedOnSocket
s32 gti2SendClosedOnSocket(GTI2Socket *a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_gti2ResendMessage
s32 gti2ResendMessage(GTI2Connection *o, GTI2OutgoingBufferMessage *m);
#endif
#ifndef PROTO_LOCAL_gti2Send
void gti2Send(GTI2Connection *o, u8 *a, s32 b, s32 mode);
#endif
#ifndef PROTO_LOCAL_gt2CreateSocket
s32 gt2CreateSocket(GTI2Socket **a, char *b, s32 c, s32 d, gt2SocketErrorCallback e);
#endif
#ifndef PROTO_LOCAL_gt2CloseSocket
void gt2CloseSocket(GTI2Socket *o);
#endif
#ifndef PROTO_LOCAL_gt2Think
void gt2Think(GTI2Socket *s);
#endif
#ifndef PROTO_LOCAL_gt2Listen
void gt2Listen(GTI2Socket *p, gt2ConnectAttemptCallback callback);
#endif
#ifndef PROTO_LOCAL_gt2Accept
s32 gt2Accept(GTI2Connection *o, GsTransportConnCallbacks *x);
#endif
#ifndef PROTO_LOCAL_gt2Reject
void gt2Reject(GTI2Connection *o, u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_gt2Connect
s32 gt2Connect(GTI2Socket *s, GTI2Connection **out, char *host, u8 *p3, s32 p4, s32 p5, GsTransportConnCallbacks *p6, s32 p7);
#endif
#ifndef PROTO_LOCAL_gt2Send
void gt2Send(GTI2Connection *c, u8 *msg, s32 len, s32 p3);
#endif
#ifndef PROTO_LOCAL_gt2Ping
s32 gt2Ping(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gt2CloseConnectionHard
void gt2CloseConnectionHard(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gt2CloseAllConnectionsHard
void gt2CloseAllConnectionsHard(GTI2Socket *s);
#endif
#ifndef PROTO_LOCAL_gt2GetConnectionState
s32 gt2GetConnectionState(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gt2GetLocalPort
u32 gt2GetLocalPort(GTI2Socket *c);
#endif
#ifndef PROTO_LOCAL_gt2GetOutgoingBufferFreeSpace
s32 gt2GetOutgoingBufferFreeSpace(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gt2GetRemoteIP
s32 gt2GetRemoteIP(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gt2SetUnrecognizedMessageCallback
void gt2SetUnrecognizedMessageCallback(GTI2Socket *c, gt2UnrecognizedMessageCallback v);
#endif
#ifndef PROTO_LOCAL_gt2SetConnectionData
void gt2SetConnectionData(GTI2Connection *c, void *v);
#endif
#ifndef PROTO_LOCAL_gt2GetConnectionData
void *gt2GetConnectionData(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gti2NewOutgoingConnection
s32 gti2NewOutgoingConnection(GTI2Socket *s, GTI2Connection **pc, u32 ip, u32 port);
#endif
#ifndef PROTO_LOCAL_gti2NewIncomingConnection
s32 gti2NewIncomingConnection(GTI2Socket *s, GTI2Connection **pc, u32 ip, u32 port);
#endif
#ifndef PROTO_LOCAL_gti2StartConnectionAttempt
s32 gti2StartConnectionAttempt(GTI2Connection *c, u8 *msg, s32 len, GsTransportConnCallbacks *x);
#endif
#ifndef PROTO_LOCAL_gti2AcceptConnection
s32 gti2AcceptConnection(GTI2Connection *c, GsTransportConnCallbacks *x);
#endif
#ifndef PROTO_LOCAL_gti2RejectConnection
void gti2RejectConnection(GTI2Connection *c, u8 *msg, s32 len);
#endif
#ifndef PROTO_LOCAL_gti2ConnectionSendData
s32 gti2ConnectionSendData(GTI2Connection *c, u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_gti2CheckTimeout
s32 gti2CheckTimeout(GTI2Connection *c, u32 t);
#endif
#ifndef PROTO_LOCAL_gti2SendRetries
s32 gti2SendRetries(GTI2Connection *c, u32 t);
#endif
#ifndef PROTO_LOCAL_gti2CheckPendingAck
s32 gti2CheckPendingAck(GTI2Connection *c, u32 t);
#endif
#ifndef PROTO_LOCAL_gti2CheckKeepAlive
s32 gti2CheckKeepAlive(GTI2Connection *c, u32 t);
#endif
#ifndef PROTO_LOCAL_gti2ConnectionThink
s32 gti2ConnectionThink(GTI2Connection *c, u32 t);
#endif
#ifndef PROTO_LOCAL_gti2CloseConnection
void gti2CloseConnection(GTI2Connection *c, s32 x);
#endif
#ifndef PROTO_LOCAL_gti2ConnectionClosed
void gti2ConnectionClosed(GTI2Connection *c, ...);
#endif
#ifndef PROTO_LOCAL_gti2ConnectionCleanup
void gti2ConnectionCleanup(GTI2Connection *c);
#endif
#ifndef PROTO_LOCAL_gti2SocketErrorCallback
s32 gti2SocketErrorCallback(GTI2Socket *s);
#endif
#ifndef PROTO_LOCAL_gti2ConnectAttemptCallback
s32 gti2ConnectAttemptCallback(GTI2Socket *s, GTI2Connection *c, s32 a, s32 b, s32 p4, u8 *p5, s32 p6);
#endif
#ifndef PROTO_LOCAL_gti2ConnectedCallback
s32 gti2ConnectedCallback(GTI2Connection *c, s32 a, u8 *b, s32 d);
#endif
#ifndef PROTO_LOCAL_gti2ReceivedCallback
s32 gti2ReceivedCallback(GTI2Connection *c, u8 *a, s32 b, s32 d);
#endif
#ifndef PROTO_LOCAL_gti2ClosedCallback
s32 gti2ClosedCallback(GTI2Connection *c, s32 a);
#endif
#ifndef PROTO_LOCAL_gti2PingCallback
s32 gti2PingCallback(GTI2Connection *c, s32 a);
#endif
#ifndef PROTO_LOCAL_gti2SendFilterCallback
s32 gti2SendFilterCallback(GTI2Connection *c, s32 a, u8 *msg, u32 len, u32 rel);
#endif
#ifndef PROTO_LOCAL_gti2ReceiveFilterCallback
s32 gti2ReceiveFilterCallback(GTI2Connection *c, s32 a, u8 *msg, u32 len, u32 rel);
#endif
#ifndef PROTO_LOCAL_gti2DumpCallback
s32 gti2DumpCallback(GTI2Socket *o, GTI2Connection *x, s32 u2, s32 u3, s32 s4, u8 *s5, s32 s6, s32 s7);
#endif
#ifndef PROTO_LOCAL_gti2UnrecognizedMessageCallback
s32 gti2UnrecognizedMessageCallback(GTI2Socket *o, s32 a1, s32 a2, u8 *a3, s32 a4, s32 *out);
#endif
#ifndef PROTO_LOCAL_gti2AllocateBuffer
s32 gti2AllocateBuffer(GTI2Buffer *b, s32 size);
#endif
#ifndef PROTO_LOCAL_gti2GetBufferFreeSpace
s32 gti2GetBufferFreeSpace(GTI2Buffer *b);
#endif
#ifndef PROTO_LOCAL_gti2BufferWriteByte
void gti2BufferWriteByte(GTI2Buffer *b, s32 v);
#endif
#ifndef PROTO_LOCAL_gti2BufferWriteUShort
void gti2BufferWriteUShort(GTI2Buffer *b, s32 v);
#endif
#ifndef PROTO_LOCAL_gti2BufferWriteData
void gti2BufferWriteData(GTI2Buffer *b, const u8 *s, s32 n);
#endif
#ifndef PROTO_LOCAL_gti2BufferShorten
void gti2BufferShorten(GTI2Buffer *b, s32 pos, s32 n);
#endif
}
#endif

#endif

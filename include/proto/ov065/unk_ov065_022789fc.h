#ifndef PROTO_PROTO_OV065_UNK_OV065_022789FC_H
#define PROTO_PROTO_OV065_UNK_OV065_022789FC_H


#include "types.h"
#include "net/GsSocket.h"
#include "net/SockAddrIn.h"
#include "net/SockHostEnt.h"
#ifdef __cplusplus
#include "net/ghttpBuffer.h"
#include "net/ghttpConnection.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_randomnum
extern s32 randomnum;
#endif
#ifndef PROTO_LOCAL_GSINitroErrno
extern s32 GSINitroErrno;
#endif
#ifndef PROTO_LOCAL_data_ov065_0229107c
extern u8 data_ov065_0229107c[4];
#endif
#ifndef PROTO_LOCAL_current_time
u32 current_time();
#endif
#ifndef PROTO_LOCAL_msleep
void msleep(s32 ms);
#endif
#ifndef PROTO_LOCAL_SocketStartUp
void SocketStartUp();
#endif
#ifndef PROTO_LOCAL_SocketShutDown
void SocketShutDown();
#endif
#ifndef PROTO_LOCAL_goastrdup
char *goastrdup(const char *s);
#endif
#ifndef PROTO_LOCAL__strlwr
char *_strlwr(char *s);
#endif
#ifndef PROTO_LOCAL_SetSockBlocking
s32 SetSockBlocking(s32 sock, s32 flag);
#endif
#ifndef PROTO_LOCAL_SetReceiveBufferSize
s32 SetReceiveBufferSize(s32 sock, s32 val);
#endif
#ifndef PROTO_LOCAL_SetSendBufferSize
s32 SetSendBufferSize(s32 sock, s32 val);
#endif
#ifndef PROTO_LOCAL_GetReceiveBufferSize
s32 GetReceiveBufferSize(s32 sock);
#endif
#ifndef PROTO_LOCAL_GetSendBufferSize
s32 GetSendBufferSize(s32 sock);
#endif
#ifndef PROTO_LOCAL_GSISocketSelect
s32 GSISocketSelect(s32 sock, s32 *rd, s32 *wr, s32 *ex);
#endif
#ifndef PROTO_LOCAL_CanReceiveOnSocket
s32 CanReceiveOnSocket(s32 a);
#endif
#ifndef PROTO_LOCAL_CanSendOnSocket
s32 CanSendOnSocket(s32 a);
#endif
#ifndef PROTO_LOCAL_IsPrivateIP
s32 IsPrivateIP(u32 *p);
#endif
#ifndef PROTO_LOCAL_CheckRcode
s32 CheckRcode(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_socket
s32 socket(s32 a, s32 b, s32 protocol);
#endif
#ifndef PROTO_LOCAL_closesocket
s32 closesocket(s32 a);
#endif
#ifndef PROTO_LOCAL_shutdown
s32 shutdown(s32 a, s32 how);
#endif
#ifndef PROTO_LOCAL_listen
s32 listen(s32 a, s32 backlog);
#endif
#ifndef PROTO_LOCAL_accept
s32 accept(s32 a, u8 *sa, s32 *len);
#endif
#ifndef PROTO_LOCAL_recv
s32 recv(s32 a, void *b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_recvfrom
s32 recvfrom(s32 a, void *b, s32 c, u32 d, SockAddrIn *sa, s32 *len);
#endif
#ifndef PROTO_LOCAL_send
s32 send(s32 a, const void *b, s32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_getsockopt
s32 getsockopt(s32 a, s32 b, s32 c, void *val, s32 *len);
#endif
#ifndef PROTO_LOCAL_setsockopt
s32 setsockopt(s32 a, s32 b, s32 c, const void *d, s32 e);
#endif
#ifndef PROTO_LOCAL_getsockname
s32 getsockname(s32 a, SockAddrIn *p1, s32 *p2);
#endif
#ifndef PROTO_LOCAL_inet_addr
s32 inet_addr(const char *a);
#endif
#ifndef PROTO_LOCAL_GOAGetLastError
s32 GOAGetLastError(s32 s);
#endif
#ifndef PROTO_LOCAL_time
s32 time(s32 *timer);
#endif
#ifndef PROTO_LOCAL_nextlongrand
u32 nextlongrand(u32 x);
#endif
#ifndef PROTO_LOCAL_longrand
s32 longrand(void);
#endif
#ifndef PROTO_LOCAL_Util_RandSeed
void Util_RandSeed(u32 seed);
#endif
#ifndef PROTO_LOCAL_Util_RandInt
s32 Util_RandInt(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_TripToQuart
void TripToQuart(char *in, char *out, s32 n);
#endif
#ifndef PROTO_LOCAL_B64Encode
void B64Encode(char *in, char *out, s32 n, s32 mode);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_localhost
extern SockHostEnt localhost;
#endif
#ifndef PROTO_LOCAL_data_ov065_02291094
extern GsHostAddr data_ov065_02291094;
#endif
#ifndef PROTO_LOCAL_data_ov065_022910a8
extern GsHostAddrList data_ov065_022910a8;
#endif
#ifndef PROTO_LOCAL_ghiAppendHeaderToBuffer
s32 ghiAppendHeaderToBuffer(GHIBuffer *o, char *a, char *b);
#endif
#ifndef PROTO_LOCAL_ghiAppendCharToBuffer
s32 ghiAppendCharToBuffer(GHIBuffer *o, u8 c);
#endif
#ifndef PROTO_LOCAL_ghiAppendIntToBuffer
s32 ghiAppendIntToBuffer(GHIBuffer *o, s32 x);
#endif
#ifndef PROTO_LOCAL_ghiResetBuffer
void ghiResetBuffer(GHIBuffer *o);
#endif
#ifndef PROTO_LOCAL_ghiSendBufferedData
s32 ghiSendBufferedData(GHIConnection *o);
#endif
#ifndef PROTO_LOCAL_ghiReadDataFromBuffer
s32 ghiReadDataFromBuffer(GHIBuffer *o, char *dst, s32 *len);
#endif
#ifndef PROTO_LOCAL_getlocalhost
SockHostEnt *getlocalhost();
#endif
#ifndef PROTO_LOCAL_bind
s32 bind(s32 a, const SockAddrIn *src, u32 len);
#endif
#ifndef PROTO_LOCAL_connect
s32 connect(s32 a, const SockAddrIn *src, u32 len);
#endif
#ifndef PROTO_LOCAL_sendto
s32 sendto(s32 a, const void *b, s32 c, u32 d, const SockAddrIn *addr, u32 len);
#endif
}
#endif

#endif

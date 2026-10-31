#ifndef PROTO_PROTO_OV065_UNK_OV065_02283720_H
#define PROTO_PROTO_OV065_UNK_OV065_02283720_H


#include "types.h"
#include "net/darray.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gti2GetResponse
u8 *gti2GetResponse(u8 *out, u8 *in);
#endif
#ifndef PROTO_LOCAL_sGsPersistXorKey
extern char *sGsPersistXorKey;
#endif
#ifndef PROTO_LOCAL_rcvmax
extern s32 rcvmax;
#endif
#ifndef PROTO_LOCAL_gti2CheckResponse
BOOL gti2CheckResponse(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_data_ov065_0228df7c
extern u8 data_ov065_0228df7c[16];
#endif
#ifndef PROTO_LOCAL_CloseStatsConnection
void CloseStatsConnection();
#endif
#ifndef PROTO_LOCAL_data_ov065_02291104
extern char data_ov065_02291104[0x100];
#endif
#ifndef PROTO_LOCAL_PersistThink
s32 PersistThink();
#endif
#ifndef PROTO_LOCAL_rcvlen
extern s32 rcvlen;
#endif
#ifndef PROTO_LOCAL_xcode_buf
void xcode_buf(char *p, s32 n);
#endif
#ifndef PROTO_LOCAL_value_for_key
char *value_for_key(char *s, char *key);
#endif
#ifndef PROTO_LOCAL_enc1
extern u8 enc1[16];
#endif
#ifndef PROTO_LOCAL_value_for_key_safe
char *value_for_key_safe(char *s, char *key);
#endif
#ifndef PROTO_LOCAL_SocketReadable
s32 SocketReadable(s32 a);
#endif
#ifndef PROTO_LOCAL_FindFinal
char *FindFinal(char *s, s32 len);
#endif
#ifndef PROTO_LOCAL_FindRequest
s32 FindRequest(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_enc3
extern u8 enc3[16];
#endif
#ifndef PROTO_LOCAL_ProcessPlayerAuth
void ProcessPlayerAuth(char *s, s32 len);
#endif
#ifndef PROTO_LOCAL_ProcessGetPid
void ProcessGetPid(char *s, s32 len);
#endif
#ifndef PROTO_LOCAL_stats_initstate
extern s32 stats_initstate;
#endif
#ifndef PROTO_LOCAL_ProcessGetData
void ProcessGetData(char *s, s32 len);
#endif
#ifndef PROTO_LOCAL_ProcessSetData
void ProcessSetData(char *s, s32 len);
#endif
#ifndef PROTO_LOCAL_data_ov065_02291304
extern char data_ov065_02291304[0x200];
#endif
#ifndef PROTO_LOCAL_ProcessStatement
void ProcessStatement(char *s, s32 len);
#endif
#ifndef PROTO_LOCAL_sGsPersistSocket
extern s32 sGsPersistSocket;
#endif
#ifndef PROTO_LOCAL_ProcessInBuffer
s32 ProcessInBuffer(char *p, s32 n);
#endif
#ifndef PROTO_LOCAL_CallReqCallback
void CallReqCallback(s32 idx, s32 a, s32 b, void *p3, s32 p4);
#endif
#ifndef PROTO_LOCAL_data_ov065_022910fc
extern volatile s32 data_ov065_022910fc;
#endif
#ifndef PROTO_LOCAL_rcvbuffer
extern char *rcvbuffer;
#endif
#ifndef PROTO_LOCAL_ClosePendingCallbacks
void ClosePendingCallbacks(void);
#endif
#ifndef PROTO_LOCAL_strzcpy
void strzcpy(char *dst, const char *src, s32 n);
#endif
#ifndef PROTO_LOCAL_gpiDebug
void gpiDebug(void *h, const char *fmt, ...);
#endif
#ifndef PROTO_LOCAL_data_ov065_02291204
extern char data_ov065_02291204[0x100];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_serverreqs
extern DArrayImplementation *serverreqs;
#endif
}
#endif

#endif

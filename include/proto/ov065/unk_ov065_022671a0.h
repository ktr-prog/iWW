#ifndef PROTO_PROTO_OV065_UNK_OV065_022671A0_H
#define PROTO_PROTO_OV065_UNK_OV065_022671A0_H


#include "types.h"
#include "net/SslConnection.h"
#include "net/SslMd5Context.h"
#include "net/SslRootCa.h"
#include "net/SslSession.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSslMd5WordIndex
extern u8 sSslMd5WordIndex[0x40];
#endif
#ifndef PROTO_LOCAL_sSslMd5Padding
extern u8 sSslMd5Padding[0x40];
#endif
#ifndef PROTO_LOCAL_sSslMd5SineTable
extern u32 sSslMd5SineTable[0x40];
#endif
#ifndef PROTO_LOCAL_sSslSessionCache
extern SslSession sSslSessionCache[4];
#endif
#ifndef PROTO_LOCAL_SslMd5_Transform
void SslMd5_Transform(SslMd5Context *ctx, const u8 *block);
#endif
#ifndef PROTO_LOCAL_SslMd5_Init
void SslMd5_Init(SslMd5Context *ctx);
#endif
#ifndef PROTO_LOCAL_SslMd5_Update
void SslMd5_Update(SslMd5Context *ctx, const u8 *data, u32 n);
#endif
#ifndef PROTO_LOCAL_SslMd5_Final
void SslMd5_Final(SslMd5Context *ctx, void *out);
#endif
#ifndef PROTO_LOCAL_SslSession_FindById
SslSession *SslSession_FindById(const void *p);
#endif
#ifndef PROTO_LOCAL_SslSession_FindByPeer
SslSession *SslSession_FindByPeer(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_SslSession_Add
SslSession *SslSession_Add(const void *src);
#endif
#ifndef PROTO_LOCAL_Ssl_GetUnixTime
u32 Ssl_GetUnixTime(void);
#endif
#ifndef PROTO_LOCAL_Ssl_SetRootCaList
void Ssl_SetRootCaList(SslRootCa **a, s32 b);
#endif
#ifndef PROTO_LOCAL_SslCert_FindRootCa
SslRootCa *SslCert_FindRootCa(SslConnection *o, const char *name);
#endif
#ifndef PROTO_LOCAL_SslCert_ReadDerLength
s32 SslCert_ReadDerLength(u8 **pp);
#endif
#ifndef PROTO_LOCAL_SslCert_AppendName
void SslCert_AppendName(char *p, const char *src, s32 n);
#endif
#ifndef PROTO_LOCAL_SslCert_ParseTime
u32 SslCert_ParseTime(const u8 *p, s32 mode);
#endif
#ifdef __cplusplus
}
#endif

#endif

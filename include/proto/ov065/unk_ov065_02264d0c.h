#ifndef PROTO_PROTO_OV065_UNK_OV065_02264D0C_H
#define PROTO_PROTO_OV065_UNK_OV065_02264D0C_H


#include "types.h"
#include "net/IpSocket.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SslCert_LabelLength
s32 SslCert_LabelLength(char *s);
#endif
#ifndef PROTO_LOCAL_SslCert_MatchHostName
s32 SslCert_MatchHostName(char *a, char *b);
#endif
#ifndef PROTO_LOCAL_Ssl_ListContains
s32 Ssl_ListContains(u8 *p, s32 cnt, s32 size, u32 key);
#endif
#ifndef PROTO_LOCAL_Ssl_ChooseCipherSuite
u32 Ssl_ChooseCipherSuite(u8 *p, s32 cnt, s32 size);
#endif
#ifndef PROTO_LOCAL_Ssl_IsVersion3
s32 Ssl_IsVersion3(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Ssl_IncrementSeqNum
void Ssl_IncrementSeqNum(u8 *p);
#endif
#ifndef PROTO_LOCAL_SslRand_GetNonZeroBytes
void SslRand_GetNonZeroBytes(u8 *out, s32 n);
#endif
#ifndef PROTO_LOCAL_SslRand_AddSeed
void SslRand_AddSeed(u8 *p, u32 n);
#endif
#ifndef PROTO_LOCAL_Ssl_Read
u8 *Ssl_Read(u32 *out, IpSocket *o);
#endif
#ifndef PROTO_LOCAL_Ssl_Consume
void Ssl_Consume(u32 n, IpSocket *o);
#endif
#ifndef PROTO_LOCAL_Ssl_ReceiveRecordPart
void Ssl_ReceiveRecordPart(IpSocket *o);
#endif
#ifndef PROTO_LOCAL_Ssl_GetReadLength
s32 Ssl_GetReadLength(IpSocket *o);
#endif
#ifndef PROTO_LOCAL_Ssl_Write
u32 Ssl_Write(u8 *p1, u32 n1, u8 *p2, u32 n2, IpSocket *o);
#endif
#ifndef PROTO_LOCAL_Ssl_Shutdown
void Ssl_Shutdown(IpSocket *o);
#endif
#ifndef PROTO_LOCAL_Ssl_EnableOnCurrentSocket
void Ssl_EnableOnCurrentSocket(u32 v);
#endif
#ifndef PROTO_LOCAL_Ssl_ExpireSessions
void Ssl_ExpireSessions(s32 now);
#endif
#ifndef PROTO_LOCAL_Ssl_ClearSessionCache
void Ssl_ClearSessionCache(void);
#endif
#ifndef PROTO_LOCAL_sSslNoSession
extern u8 sSslNoSession[0x5c];
#endif
#ifndef PROTO_LOCAL_sSslRandPool
extern u8 sSslRandPool[0x14];
#endif
#ifndef PROTO_LOCAL_sSslSessionIdCounter
extern u32 sSslSessionIdCounter;
#endif
#ifndef PROTO_LOCAL_sSslOidNone
extern u8 sSslOidNone[4];
#endif
#ifndef PROTO_LOCAL_sSslOidCommonName
extern u8 sSslOidCommonName[4];
#endif
#ifndef PROTO_LOCAL_gSslRsaThreadPriority
extern u32 gSslRsaThreadPriority;
#endif
#ifndef PROTO_LOCAL_sSslCipherSuites
extern u16 sSslCipherSuites[2];
#endif
#ifndef PROTO_LOCAL_sSslOidRsaX500
extern u8 sSslOidRsaX500[8];
#endif
#ifndef PROTO_LOCAL_sSslOidRsaEncryption
extern u8 sSslOidRsaEncryption[12];
#endif
#ifndef PROTO_LOCAL_sSslOidMd5WithRsa
extern u8 sSslOidMd5WithRsa[12];
#endif
#ifndef PROTO_LOCAL_sSslRandSeeded
extern u8 sSslRandSeeded;
#endif
#ifndef PROTO_LOCAL_sSslOidSha1WithRsa
extern u8 sSslOidSha1WithRsa[12];
#endif
#ifndef PROTO_LOCAL_sSslCertOidTable
extern char *sSslCertOidTable[6];
#endif
#ifdef __cplusplus
}
#endif

#endif

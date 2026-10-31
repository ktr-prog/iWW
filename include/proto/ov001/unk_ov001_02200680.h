#ifndef PROTO_PROTO_OV001_UNK_OV001_02200680_H
#define PROTO_PROTO_OV001_UNK_OV001_02200680_H


#include "types.h"
#include "net/AossParam.h"
#include "net/SockAddrIn.h"
struct AossPollFd;
struct AossRandState;
struct AossRc4State;
struct AossScanList;
struct AossSession;
struct AossSocConfig;
#ifndef __cplusplus
typedef struct AossPollFd AossPollFd;
typedef struct AossRandState AossRandState;
typedef struct AossRc4State AossRc4State;
typedef struct AossScanList AossScanList;
typedef struct AossSession AossSession;
typedef struct AossSocConfig AossSocConfig;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Aoss_Run
s32 Aoss_Run(AossParam *a);
#endif
#ifndef PROTO_LOCAL_Aoss_RunProtocol
s32 Aoss_RunProtocol(u8 *o);
#endif
#ifndef PROTO_LOCAL_Aoss_PickHostAddress
u32 Aoss_PickHostAddress(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Aoss_FreeScanBuffers
void Aoss_FreeScanBuffers();
#endif
#ifndef PROTO_LOCAL_Aoss_InitSession
void Aoss_InitSession(u8 *p);
#endif
#ifndef PROTO_LOCAL_Aoss_SetError
void Aoss_SetError(s32 v);
#endif
#ifndef PROTO_LOCAL_Aoss_GetError
s32 Aoss_GetError();
#endif
#ifndef PROTO_LOCAL_Aoss_StoreResult
s32 Aoss_StoreResult(u8 *o);
#endif
#ifndef PROTO_LOCAL_Aoss_IsPrintable
s32 Aoss_IsPrintable(u8 *s, s32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_BuildAossApConfig
s32 Aoss_BuildAossApConfig(AossApConfig *p);
#endif
#ifndef PROTO_LOCAL_Aoss_InitNonces
void Aoss_InitNonces(s32 n, u8 *p, void *x);
#endif
#ifndef PROTO_LOCAL_Aoss_SetProgress
s32 Aoss_SetProgress(s32 x);
#endif
#ifndef PROTO_LOCAL_Aoss_HandleRecvPacket
s32 Aoss_HandleRecvPacket(s32 a, u8 *b, s32 *cnt, void *c, s32 sock);
#endif
#ifndef PROTO_LOCAL_Aoss_HandleStartReply
s32 Aoss_HandleStartReply(s32 a, u8 *b, s32 *cnt, void *c);
#endif
#ifndef PROTO_LOCAL_Aoss_HandleKeyReply
s32 Aoss_HandleKeyReply(s32 mode, u8 *q, s32 *cnt, u8 *r3);
#endif
#ifndef PROTO_LOCAL_Aoss_HandleFinishReply
s32 Aoss_HandleFinishReply(s32 mode, u8 *q, s32 *cnt, u8 *r3);
#endif
#ifndef PROTO_LOCAL_Aoss_ValidateRecvPacket
s32 Aoss_ValidateRecvPacket(u8 *p);
#endif
#ifndef PROTO_LOCAL_Aoss_CheckSessionId
s32 Aoss_CheckSessionId(s32 a, u8 *b);
#endif
#ifndef PROTO_LOCAL_Aoss_CheckReplyNonce
s32 Aoss_CheckReplyNonce(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_Aoss_ParseStartReply
s32 Aoss_ParseStartReply(u8 *p, u8 *dst);
#endif
#ifndef PROTO_LOCAL_Aoss_ReadLE
u32 Aoss_ReadLE(u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_ParseWepTlvs
s32 Aoss_ParseWepTlvs(u8 *p, u8 *dst);
#endif
#ifndef PROTO_LOCAL_Aoss_ParsePskTlvs
s32 Aoss_ParsePskTlvs(u8 *p, u8 *dst);
#endif
#ifndef PROTO_LOCAL_Aoss_ParseTlv70
s32 Aoss_ParseTlv70(u8 *p, void *dst);
#endif
#ifndef PROTO_LOCAL_Aoss_ParseKeyBlock
s32 Aoss_ParseKeyBlock(s32 idx, u8 *p, s32 len, u8 *base, u8 *extra);
#endif
#ifndef PROTO_LOCAL_Aoss_IsFlag10Set
BOOL Aoss_IsFlag10Set(u32 x);
#endif
#ifndef PROTO_LOCAL_Aoss_SendForStage
s32 Aoss_SendForStage(s32 sel, void *a, u8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_SendStartRequest
s32 Aoss_SendStartRequest(void *unused, u8 *src, s32 arg);
#endif
#ifndef PROTO_LOCAL_Aoss_SendKeyRequest
s32 Aoss_SendKeyRequest(void *a, u8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_SendFinishRequest
s32 Aoss_SendFinishRequest(void *a, u8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_BuildClientInfoTlv
s32 Aoss_BuildClientInfoTlv(u8 *out);
#endif
#ifndef PROTO_LOCAL_Aoss_WriteBody
void Aoss_WriteBody(s32 mode, u8 *out, u8 *in, s16 *len, u16 *flag, u8 *crcout);
#endif
#ifndef PROTO_LOCAL_Aoss_WriteHeader
void Aoss_WriteHeader(u16 *out, u32 x, u32 y, u32 z, s8 a5, s8 a6, u8 *in);
#endif
#ifndef PROTO_LOCAL_Aoss_SendPacket
s32 Aoss_SendPacket(const void *a, s32 b, s32 n, s32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_EncryptPayload
s32 Aoss_EncryptPayload(u8 *a, u8 *b, u32 n, u8 *out, u8 *x, u8 *y, s32 z);
#endif
#ifndef PROTO_LOCAL_Aoss_DecryptPayload
s32 Aoss_DecryptPayload(u8 *a, u8 *b, u32 n, u32 crc, u8 *x, u8 *y, s32 z);
#endif
#ifndef PROTO_LOCAL_Aoss_CalcCrc32Low8
u8 Aoss_CalcCrc32Low8(u8 *data, s32 len);
#endif
#ifndef PROTO_LOCAL_Aoss_UpdateCrc32
u32 Aoss_UpdateCrc32(u32 crc, u8 *data, s32 len, s32 init, u32 *tbl);
#endif
#ifndef PROTO_LOCAL_Aoss_InitCrc32Table
void Aoss_InitCrc32Table(u32 unused, u32 *t);
#endif
#ifndef PROTO_LOCAL_Aoss_Scramble
s32 Aoss_Scramble(u8 *out, s32 n, u8 *key, s32 klen);
#endif
#ifndef PROTO_LOCAL_Aoss_MakeRoundKey
void Aoss_MakeRoundKey(s32 x, char *b, s32 n, char *key, s32 klen);
#endif
#ifndef PROTO_LOCAL_Aoss_XorHalf
void Aoss_XorHalf(char *a, u8 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_SwapHalves
void Aoss_SwapHalves(u8 *a, s32 n, u8 *t);
#endif
#ifndef PROTO_LOCAL_Aoss_SocAlloc
s32 Aoss_SocAlloc(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Aoss_SocFree
s32 Aoss_SocFree(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_Aoss_NetStartup
s32 Aoss_NetStartup(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_NetCleanup
s32 Aoss_NetCleanup();
#endif
#ifndef PROTO_LOCAL_Aoss_Memcmp
s32 Aoss_Memcmp(u8 *a, u8 *b, s32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_Memcpy
void Aoss_Memcpy(void *dst, void *src, u32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_Memset
void *Aoss_Memset(void *p, u32 v, u32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_RecvFrom
s32 Aoss_RecvFrom(s32 a, void *b, s32 c, s32 d, SockAddrIn *p, s32 *q);
#endif
#ifndef PROTO_LOCAL_Aoss_SendTo
s32 Aoss_SendTo(s32 a, const void *b, s32 c, s32 d, SockAddrIn *p, u32 v);
#endif
#ifndef PROTO_LOCAL_Aoss_SetSockOpt
s32 Aoss_SetSockOpt(s32 s, s32 l, s32 o, void *v, s32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_SocketCreate
s32 Aoss_SocketCreate(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_SocketBind
s32 Aoss_SocketBind(s32 a, u8 *b, s32 c);
#endif
#ifndef PROTO_LOCAL_Aoss_SocketClose
s32 Aoss_SocketClose(s32 s);
#endif
#ifndef PROTO_LOCAL_Aoss_Htonl
u32 Aoss_Htonl(u32 v);
#endif
#ifndef PROTO_LOCAL_Aoss_Htons
u16 Aoss_Htons(s32 v);
#endif
#ifndef PROTO_LOCAL_Aoss_Ntohl
u32 Aoss_Ntohl(u32 v);
#endif
#ifndef PROTO_LOCAL_Aoss_Ntohs
s32 Aoss_Ntohs(s32 v);
#endif
#ifndef PROTO_LOCAL_Aoss_Strlen
s32 Aoss_Strlen(char *s);
#endif
#ifndef PROTO_LOCAL_Aoss_Rand16
u16 Aoss_Rand16(void);
#endif
#ifndef PROTO_LOCAL_sAossError
extern s32 sAossError;
#endif
#ifndef PROTO_LOCAL_sAossRc4Key
extern u8 sAossRc4Key[0x64];
#endif
#ifndef PROTO_LOCAL_sAossRandSeeded
extern u32 sAossRandSeeded;
#endif
#ifndef PROTO_LOCAL_sAossCrcTable
extern u32 sAossCrcTable[0x100];
#endif
#ifndef PROTO_LOCAL_sAossConnectResult
extern AossConnectResult *sAossConnectResult;
#endif
#ifndef PROTO_LOCAL_sAossSessionId
extern u8 sAossSessionId[8];
#endif
#ifndef PROTO_LOCAL_sAossScanList
extern void *sAossScanList;
#endif
#ifndef PROTO_LOCAL_sAossPacketBuf
extern u8 *sAossPacketBuf;
#endif
#ifndef PROTO_LOCAL_sAossProgress
extern s32 sAossProgress;
#endif
#ifndef PROTO_LOCAL_sAossDefaultRetry
extern s16 sAossDefaultRetry[2];
#endif
#ifndef PROTO_LOCAL_sAossKeyBlockTags
extern u8 sAossKeyBlockTags[4];
#endif
#ifndef PROTO_LOCAL_sAossEncryptFlag
extern s32 sAossEncryptFlag;
#endif
#ifndef PROTO_LOCAL_sAossKeyBuf
extern u8 sAossKeyBuf[0x6a0];
#endif
#ifndef PROTO_LOCAL_sAossSocket
extern s32 sAossSocket;
#endif
#ifndef PROTO_LOCAL_sAossNameBuf
extern u8 sAossNameBuf[0x280];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_Aoss_FindAossAp
s32 Aoss_FindAossAp(AossScanList *p);
#endif
#ifndef PROTO_LOCAL_Aoss_Rc4Init
void Aoss_Rc4Init(AossRc4State *st, u8 *key, u32 klen, u32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_Rc4Crypt
void Aoss_Rc4Crypt(AossRc4State *st, u8 *out, u8 *in, u32 n);
#endif
#ifndef PROTO_LOCAL_Aoss_Rc4NextByte
u32 Aoss_Rc4NextByte(AossRc4State *st);
#endif
#ifndef PROTO_LOCAL_Aoss_Select
s32 Aoss_Select(s32 a, AossPollFd *p, s32 c, s32 d, s32 *q);
#endif
#ifndef PROTO_LOCAL_Aoss_FdZero
void Aoss_FdZero(AossPollFd *s);
#endif
#ifndef PROTO_LOCAL_Aoss_FdSet
void Aoss_FdSet(u32 v, AossPollFd *s);
#endif
#ifndef PROTO_LOCAL_sAossSocConfig
extern AossSocConfig sAossSocConfig;
#endif
#ifndef PROTO_LOCAL_sAossRand
extern AossRandState sAossRand;
#endif
#ifndef PROTO_LOCAL_sAossSession
extern AossSession sAossSession;
#endif
}
#endif

#endif

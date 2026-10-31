#ifndef PROTO_PROTO_OV001_UNK_OV001_02203B1C_H
#define PROTO_PROTO_OV001_UNK_OV001_02203B1C_H


#include "types.h"
#include "net/SimpleStart.h"
#include "net/SockAddrIn.h"
#include "net/SockStartupConfig.h"
#include "net/WifiLinkConfig.h"
#include "sys/OSThread.h"
#include "uptr.h"
struct SimpleStartApList;
struct SimpleStartMd5Ctx;
struct SimpleStartSessionId;
#ifndef __cplusplus
typedef struct SimpleStartApList SimpleStartApList;
typedef struct SimpleStartMd5Ctx SimpleStartMd5Ctx;
typedef struct SimpleStartSessionId SimpleStartSessionId;
#endif
#ifdef __cplusplus
#include "net/WifiLinkEvent.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c898
extern u8 *data_ov001_0222c898;
#endif
#ifndef PROTO_LOCAL_sSimpleStartStackSize
extern s32 sSimpleStartStackSize;
#endif
#ifndef PROTO_LOCAL_sSimpleStartAllocFunc
extern SimpleStartAllocFunc sSimpleStartAllocFunc;
#endif
#ifndef PROTO_LOCAL_sSimpleStartStep
extern s32 sSimpleStartStep;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c864
extern u32 data_ov001_0222c864;
#endif
#ifndef PROTO_LOCAL_sSimpleStartSetupSsid
extern u8 sSimpleStartSetupSsid[7];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222a548
extern u8 data_ov001_0222a548[7];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222a550
extern char data_ov001_0222a550[12];
#endif
#ifndef PROTO_LOCAL_sSimpleStartMd5Padding
extern u8 sSimpleStartMd5Padding[64];
#endif
#ifndef PROTO_LOCAL_sSimpleStartSocConfig
extern SockStartupConfig sSimpleStartSocConfig;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c850
extern u8 data_ov001_0222c850;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c894
extern u8 *data_ov001_0222c894;
#endif
#ifndef PROTO_LOCAL_sSimpleStartDeadline
extern u32 sSimpleStartDeadline;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c89c
extern u8 *data_ov001_0222c89c;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c868
extern s32 data_ov001_0222c868;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222a52c
extern u8 *data_ov001_0222a52c;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222a53c
extern s32 data_ov001_0222a53c;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c884
extern u32 data_ov001_0222c884;
#endif
#ifndef PROTO_LOCAL_sSimpleStartWcmNotifyCb
extern SimpleStartWcmNotifyFunc sSimpleStartWcmNotifyCb;
#endif
#ifndef PROTO_LOCAL_sSimpleStartStatusCb
extern SimpleStartStatusFunc sSimpleStartStatusCb;
#endif
#ifndef PROTO_LOCAL_sSimpleStartResultCode
extern s32 sSimpleStartResultCode;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8c4
extern s32 data_ov001_0222c8c4;
#endif
#ifndef PROTO_LOCAL_sSimpleStartMaxAps
extern s32 sSimpleStartMaxAps;
#endif
#ifndef PROTO_LOCAL_sSimpleStartMsgTail
extern s32 sSimpleStartMsgTail;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8b4
extern s32 data_ov001_0222c8b4;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222a530
extern s32 data_ov001_0222a530;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8ac
extern u8 *data_ov001_0222c8ac;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c870
extern s32 data_ov001_0222c870;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8a8
extern s32 data_ov001_0222c8a8;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8a4
extern u8 *data_ov001_0222c8a4;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8a0
extern s32 data_ov001_0222c8a0;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c858
extern WifiLinkConfig *data_ov001_0222c858;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c874
extern s32 data_ov001_0222c874;
#endif
#ifndef PROTO_LOCAL_sSimpleStartCancel
extern s32 sSimpleStartCancel;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c890
extern u8 *data_ov001_0222c890;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c88c
extern u8 *data_ov001_0222c88c;
#endif
#ifndef PROTO_LOCAL_sSimpleStartState
extern s32 sSimpleStartState;
#endif
#ifndef PROTO_LOCAL_sSimpleStartFreeFunc
extern SimpleStartFreeFunc sSimpleStartFreeFunc;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c880
extern u8 *data_ov001_0222c880;
#endif
#ifndef PROTO_LOCAL_sSimpleStartWcmState
extern s32 sSimpleStartWcmState;
#endif
#ifndef PROTO_LOCAL_sSimpleStartMsgHead
extern s32 sSimpleStartMsgHead;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c878
extern u8 *data_ov001_0222c878;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8b0
extern s32 data_ov001_0222c8b0;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8d4
extern u8 data_ov001_0222c8d4[6];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8dc
extern u8 data_ov001_0222c8dc[6];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8e4
extern u8 data_ov001_0222c8e4[8];
#endif
#ifndef PROTO_LOCAL_sSimpleStartMsgQueue
extern u32 sSimpleStartMsgQueue[4];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c8fc
extern u8 data_ov001_0222c8fc[0x10];
#endif
#ifndef PROTO_LOCAL_sSimpleStartAllocMutex
extern OSMutex sSimpleStartAllocMutex;
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c944
extern u8 data_ov001_0222c944[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c924
extern u8 data_ov001_0222c924[0x20];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222c964
extern u8 data_ov001_0222c964[0x24];
#endif
#ifndef PROTO_LOCAL_sSimpleStartThread
extern OSThread sSimpleStartThread;
#endif
#ifndef PROTO_LOCAL_sSimpleStartResult
extern u32 sSimpleStartResult[58];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222cb30
extern u32 data_ov001_0222cb30[149];
#endif
#ifndef PROTO_LOCAL_sSimpleStartTlvBuf
extern u8 sSimpleStartTlvBuf[0x800];
#endif
#ifndef PROTO_LOCAL_sSimpleStartPacketBuf
extern u8 sSimpleStartPacketBuf[0x800];
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmToIdle
s32 SimpleStart_WcmToIdle(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmReadApList
s32 SimpleStart_WcmReadApList(u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmStartSearch
s32 SimpleStart_WcmStartSearch(u8 *a, u8 *b, s32 c, s32 d);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmDisconnect
s32 SimpleStart_WcmDisconnect(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmCleanup
s32 SimpleStart_WcmCleanup(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmConnect
s32 SimpleStart_WcmConnect(void *p, void *x, s32 y);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmInit
s32 SimpleStart_WcmInit(SimpleStartWcmNotifyFunc cb, u8 *buf, s32 size);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WcmGetState
s32 SimpleStart_WcmGetState(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_SocAlloc
void *SimpleStart_SocAlloc(s32 a, u32 size);
#endif
#ifndef PROTO_LOCAL_SimpleStart_SocFree
void SimpleStart_SocFree(s32 a, void *p, u32 size);
#endif
#ifndef PROTO_LOCAL_SimpleStart_ClearMsgQueue
void SimpleStart_ClearMsgQueue(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_PopMsg
s32 SimpleStart_PopMsg(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_PushMsg
void SimpleStart_PushMsg(u32 v, u32 w);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AlarmCallback
void SimpleStart_AlarmCallback(void *arg);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WlanStartup
s32 SimpleStart_WlanStartup(s32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_WlanShutdown
s32 SimpleStart_WlanShutdown(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_ConnectAp
s32 SimpleStart_ConnectAp(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Disconnect
void SimpleStart_Disconnect(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_SearchAp
s32 SimpleStart_SearchAp();
#endif
#ifndef PROTO_LOCAL_SimpleStart_SendTo
s32 SimpleStart_SendTo(sptr a, SockAddrIn *hdr, u8 *out, u8 *d, u32 e);
#endif
#ifndef PROTO_LOCAL_SimpleStart_SendBroadcast
s32 SimpleStart_SendBroadcast(sptr a, u8 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_SimpleStart_SendPacket
s32 SimpleStart_SendPacket(sptr a, SockAddrIn *b, u8 *c, u32 d);
#endif
#ifndef PROTO_LOCAL_SimpleStart_CheckPacket
u8 *SimpleStart_CheckPacket(u8 *pkt, s32 *type, s32 *len);
#endif
#ifndef PROTO_LOCAL_SimpleStart_NextTlv
u8 *SimpleStart_NextTlv(u8 **cur, u8 *end, s32 *type, s32 *len);
#endif
#ifndef PROTO_LOCAL_SimpleStart_FirstTlv
u8 *SimpleStart_FirstTlv(u8 *pkt, s32 *a, s32 *b);
#endif
#ifndef PROTO_LOCAL_SimpleStart_BuildPacket
s32 SimpleStart_BuildPacket(u8 *pkt, u32 type, u8 *hdr, u32 len, u8 *extra);
#endif
#ifndef PROTO_LOCAL_SimpleStart_PutTlv
u8 *SimpleStart_PutTlv(u8 *out, u32 id0, u8 *data, u32 len);
#endif
#ifndef PROTO_LOCAL_SimpleStart_BuildTlvBlock
s32 SimpleStart_BuildTlvBlock(u8 *p, u32 id, u8 *data, u32 len);
#endif
#ifndef PROTO_LOCAL_SimpleStart_ParseHelloReply
BOOL SimpleStart_ParseHelloReply(u8 *pkt, s32 *out);
#endif
#ifndef PROTO_LOCAL_SimpleStart_RecvPacket
s32 SimpleStart_RecvPacket(u8 *pkt, s32 type, u8 *dst, u8 *extra);
#endif
#ifndef PROTO_LOCAL_SimpleStart_BuildHelloPacket
u32 SimpleStart_BuildHelloPacket(u8 *pkt);
#endif
#ifndef PROTO_LOCAL_SimpleStart_GetOwnMac
BOOL SimpleStart_GetOwnMac(u8 *mac);
#endif
#ifndef PROTO_LOCAL_SimpleStart_ParseConfigTlvs
s32 SimpleStart_ParseConfigTlvs(u8 *p);
#endif
#ifndef PROTO_LOCAL_SimpleStart_ParseHex
s32 SimpleStart_ParseHex(u8 *dst, s8 *src, s32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_BuildResult
s32 SimpleStart_BuildResult();
#endif
#ifndef PROTO_LOCAL_SimpleStart_RunProtocol
s32 SimpleStart_RunProtocol();
#endif
#ifndef PROTO_LOCAL_SimpleStart_ThreadMain
void SimpleStart_ThreadMain(void *arg);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AesKeyWrap
s32 SimpleStart_AesKeyWrap(u8 *out, const u8 *in, u32 inlen, const u8 *key, s32 keylen);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AesKeyUnwrap
s32 SimpleStart_AesKeyUnwrap(u8 *out, const u8 *in, u32 inlen, const u8 *key, s32 keylen);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Xor8
void SimpleStart_Xor8(const u8 *a, const u8 *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AesKeySetupEnc
s32 SimpleStart_AesKeySetupEnc(u32 *rk, const u8 *cipherKey, s32 keyBits);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AesKeySetupDec
s32 SimpleStart_AesKeySetupDec(u32 *rk, const u8 *key, s32 bits);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AesEncryptBlock
void SimpleStart_AesEncryptBlock(const u32 *rk, s32 Nr, const u8 *ct, u8 *pt);
#endif
#ifndef PROTO_LOCAL_SimpleStart_AesDecryptBlock
void SimpleStart_AesDecryptBlock(const u32 *rk, s32 Nr, const u8 *ct, u8 *pt);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Transform
void SimpleStart_Md5Transform(u32 *state, u8 *block);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Encode
void SimpleStart_Md5Encode(u8 *dst, u32 *src, u32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Decode
void SimpleStart_Md5Decode(u32 *dst, u8 *src, u32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Memcpy
void SimpleStart_Md5Memcpy(u8 *dst, u8 *src, u32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Memset
void SimpleStart_Md5Memset(void *p, s32 c, u32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5
void SimpleStart_Md5(void *out, void *p, u32 n);
#endif
#ifndef PROTO_LOCAL_SimpleStart_GetMilliseconds
u32 SimpleStart_GetMilliseconds();
#endif
#ifndef PROTO_LOCAL_SimpleStart_Calloc
void *SimpleStart_Calloc(u32 n, u32 m);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Free
void SimpleStart_Free(void *p);
#endif
#ifndef PROTO_LOCAL_SimpleStart_FormatHexByte
s32 SimpleStart_FormatHexByte(char *buf, u32 v);
#endif
#ifndef PROTO_LOCAL_SimpleStart_FormatMac
s32 SimpleStart_FormatMac(char *dst, s8 *src);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Start
s32 SimpleStart_Start(u32 a0, s32 a1, SimpleStartStatusFunc a2, SimpleStartAllocFunc a3, SimpleStartFreeFunc a4, s32 a5);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Stop
s32 SimpleStart_Stop(void);
#endif
#ifndef PROTO_LOCAL_SimpleStart_GetStatus
s32 SimpleStart_GetStatus(SimpleStartStatus *out);
#endif
#ifndef PROTO_LOCAL_SimpleStart_GetResult
s32 SimpleStart_GetResult(void *dst);
#endif
#ifndef PROTO_LOCAL_SimpleStart_NotifyStatus
void SimpleStart_NotifyStatus(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_SimpleStart_WcmCallback
void SimpleStart_WcmCallback(WifiLinkEvent *p);
#endif
#ifndef PROTO_LOCAL_SimpleStart_FindSetupAp
BOOL SimpleStart_FindSetupAp(SimpleStartApList *a, SimpleStartApList *b, s32 *out);
#endif
#ifndef PROTO_LOCAL_SimpleStart_BuildSessionId
s32 SimpleStart_BuildSessionId(SimpleStartSessionId *out, void *unused);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Init
void SimpleStart_Md5Init(SimpleStartMd5Ctx *ctx);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Update
void SimpleStart_Md5Update(SimpleStartMd5Ctx *ctx, const u8 *data, u32 len);
#endif
#ifndef PROTO_LOCAL_SimpleStart_Md5Final
void SimpleStart_Md5Final(u8 *out, SimpleStartMd5Ctx *ctx);
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV065_UNK_OV065_02289444_H
#define PROTO_PROTO_OV065_UNK_OV065_02289444_H


#include "types.h"
#ifdef __cplusplus
#include "net/sb_internal.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_0228e954
extern char *data_ov065_0228e954;
#endif
#ifndef PROTO_LOCAL_SBOverrideMasterServer
extern char *SBOverrideMasterServer;
#endif
#ifndef PROTO_LOCAL_IntKeyCompare
s32 IntKeyCompare(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_FloatKeyCompare
s32 FloatKeyCompare(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_StrCaseKeyCompare
s32 StrCaseKeyCompare(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_StrNoCaseKeyCompare
s32 StrNoCaseKeyCompare(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_NTSLengthSB
s32 NTSLengthSB(const u8 *s, s32 n);
#endif
#ifndef PROTO_LOCAL_StringHash__sb_serverlist
u32 StringHash__sb_serverlist(const char *s, u32 n);
#endif
#ifndef PROTO_LOCAL_BufferAddNTS
void BufferAddNTS(u8 **p, const char *s, s32 *n);
#endif
#ifndef PROTO_LOCAL_BufferAddByte
void BufferAddByte(u8 **p, u8 c, s32 *n);
#endif
#ifndef PROTO_LOCAL_BufferAddInt
void BufferAddInt(u8 **cur, u32 v, s32 *len);
#endif
#ifndef PROTO_LOCAL_BufferAddData
void BufferAddData(u8 **cur, const void *src, s32 n, s32 *len);
#endif
#ifndef PROTO_LOCAL_ServerSizeForFlags
s32 ServerSizeForFlags(u32 flags);
#endif
#ifndef PROTO_LOCAL_FullRulesPresent
s32 FullRulesPresent(u8 *buf, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_g_sortserverlist
extern SBServerList *g_sortserverlist;
#endif
#ifndef PROTO_LOCAL_SBNullServer
extern _SBServer *SBNullServer;
#endif
#ifndef PROTO_LOCAL_SBServerListSort
void SBServerListSort(SBServerList *c, s32 a, char *b, u32 mode);
#endif
#ifndef PROTO_LOCAL_SBServerListAppendServer
void SBServerListAppendServer(SBServerList *c, _SBServer *a);
#endif
#ifndef PROTO_LOCAL_SBServerListFindServer
s32 SBServerListFindServer(SBServerList *c, _SBServer *key);
#endif
#ifndef PROTO_LOCAL_SBServerListFindServerByIP
s32 SBServerListFindServerByIP(SBServerList *c, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_AddServerToDeadlist
void AddServerToDeadlist(SBServerList *c, _SBServer *x);
#endif
#ifndef PROTO_LOCAL_SBServerListRemoveAt
void SBServerListRemoveAt(SBServerList *c, s32 i);
#endif
#ifndef PROTO_LOCAL_SBServerListCount
s32 SBServerListCount(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_SBServerListNth
_SBServer *SBServerListNth(SBServerList *c, s32 i);
#endif
#ifndef PROTO_LOCAL_SBFreeDeadList
void SBFreeDeadList(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_SBServerListClear
void SBServerListClear(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_SBAllocateServerList
void SBAllocateServerList(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_SBRefStr
char *SBRefStr(SBServerList *c, const char *key);
#endif
#ifndef PROTO_LOCAL_SBReleaseStr
void SBReleaseStr(SBServerList *c, const char *key);
#endif
#ifndef PROTO_LOCAL_SBServerListInit
void SBServerListInit(SBServerList *c, char *a, char *b, char *d, s32 e, s32 f, void *g, void *h);
#endif
#ifndef PROTO_LOCAL_ErrorDisconnect
void ErrorDisconnect(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_ServerListConnect
s32 ServerListConnect(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_SetupListChallenge
void SetupListChallenge(SBServerList *ctx);
#endif
#ifndef PROTO_LOCAL_SendWithRetry
s32 SendWithRetry(SBServerList *ctx, const void *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_SBServerListConnectAndQuery
s32 SBServerListConnectAndQuery(SBServerList *ctx, const char *user, const char *pass, u32 flags, u32 extra);
#endif
#ifndef PROTO_LOCAL_FreePopularValues
void FreePopularValues(SBServerList *ctx);
#endif
#ifndef PROTO_LOCAL_FreeKeyList
void FreeKeyList(SBServerList *ctx);
#endif
#ifndef PROTO_LOCAL_SBServerListDisconnect
void SBServerListDisconnect(SBServerList *ctx);
#endif
#ifndef PROTO_LOCAL_SBServerListCleanup
void SBServerListCleanup(SBServerList *ctx);
#endif
#ifndef PROTO_LOCAL_InitCryptKey
void InitCryptKey(SBServerList *ctx, const u8 *key, s32 n);
#endif
#ifndef PROTO_LOCAL_AllKeysPresent
s32 AllKeysPresent(SBServerList *ctx, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_ParseServerIPPort
void ParseServerIPPort(SBServerList *ctx, u8 *buf, s32 n, u32 *ip, u16 *volatile port);
#endif
#ifndef PROTO_LOCAL_ParseServer
s32 ParseServer(SBServerList *ctx, _SBServer *ent, u8 *buf, s32 n, s32 flag);
#endif
#ifndef PROTO_LOCAL_IncomingListParseServer
s32 IncomingListParseServer(SBServerList *ctx, u8 *buf, s32 n);
#endif
#ifndef PROTO_LOCAL_SBSetLastListErrorPtr
void SBSetLastListErrorPtr(SBServerList *ctx, const char *v);
#endif
#ifndef PROTO_LOCAL_ProcessMainListData
s32 ProcessMainListData(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_ProcessPushKeyList
s32 ProcessPushKeyList(SBServerList *c, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ProcessPlayerSearch
s32 ProcessPlayerSearch(SBServerList *c, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ProcessMaploop
s32 ProcessMaploop(SBServerList *c, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ProcessDeleteServer
s32 ProcessDeleteServer(SBServerList *c, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ProcessPushServer
s32 ProcessPushServer(SBServerList *c, u8 *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ProcessAdHocData
s32 ProcessAdHocData(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_ProcessIncomingData
s32 ProcessIncomingData(SBServerList *c);
#endif
#ifndef PROTO_LOCAL_SBSendMessageToServer
s32 SBSendMessageToServer(SBServerList *c, u32 a1, u32 a2, u8 *data, s32 len);
#endif
#ifndef PROTO_LOCAL_SBSendNatNegotiateCookieToServer
s32 SBSendNatNegotiateCookieToServer(SBServerList *c, u32 a1, u32 a2, u32 ip);
#endif
#ifndef PROTO_LOCAL_ProcessLanData
s32 ProcessLanData(SBServerList *s);
#endif
#ifndef PROTO_LOCAL_SBListThink
s32 SBListThink(SBServerList *sub);
#endif
#ifndef PROTO_LOCAL_ListCallback
void ListCallback(SBServerList *s, s32 code, _SBServer *p, _ServerBrowser *o);
#endif
#ifndef PROTO_LOCAL_EngineCallback
void EngineCallback(void *a, s32 code, _SBServer *p, _ServerBrowser *o);
#endif
#ifndef PROTO_LOCAL_ServerBrowserNewA
_ServerBrowser *ServerBrowserNewA(char *a, char *b, char *c, s32 d, s32 s5, s32 s6, s32 s7, void *s8, void *s9);
#endif
#ifndef PROTO_LOCAL_ServerBrowserFree
void ServerBrowserFree(_ServerBrowser *o);
#endif
}
#endif

#endif

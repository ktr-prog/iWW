#ifndef PROTO_PROTO_OV065_UNK_OV065_02286934_H
#define PROTO_PROTO_OV065_UNK_OV065_02286934_H


#include "types.h"
#include "net/SockAddrIn.h"
#include "net/darray.h"
#include "net/natneg.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Matchup1Hostname
extern char *Matchup1Hostname;
#endif
#ifndef PROTO_LOCAL_matchup1ip
extern u32 matchup1ip;
#endif
#ifndef PROTO_LOCAL_AddNegotiator
void *AddNegotiator(void);
#endif
#ifndef PROTO_LOCAL_RemoveNegotiator
void RemoveNegotiator(void *key);
#endif
#ifndef PROTO_LOCAL_NNFreeNegotiateList
void NNFreeNegotiateList(void);
#endif
#ifndef PROTO_LOCAL_CheckMagic
BOOL CheckMagic(void *p);
#endif
#ifndef PROTO_LOCAL_data_ov065_02291548
extern u8 data_ov065_02291548[0x200];
#endif
#ifndef PROTO_LOCAL_SendPacket__natneg
s32 SendPacket__natneg(s32 sock, u32 ip, s32 port, void *buf, s32 len);
#endif
#ifndef PROTO_LOCAL_GetLocalIP
u32 GetLocalIP();
#endif
#ifndef PROTO_LOCAL_NNMagicData
extern u8 NNMagicData[6];
#endif
#ifndef PROTO_LOCAL_GetLocalPort
u32 GetLocalPort(s32 fd);
#endif
#ifndef PROTO_LOCAL_NameToIp
u32 NameToIp(const char *name);
#endif
#ifndef PROTO_LOCAL_ResolveServer
u32 ResolveServer(const char *name, const char *s);
#endif
#ifndef PROTO_LOCAL_ResolveServers
s32 ResolveServers();
#endif
#ifndef PROTO_LOCAL_NNBeginNegotiationWithSocket
s32 NNBeginNegotiationWithSocket(u32 a, u32 b, s32 c, NegotiateProgressFunc d, NegotiateCompletedFunc e, void *f);
#endif
#ifndef PROTO_LOCAL_matchup2ip
extern u32 matchup2ip;
#endif
#ifndef PROTO_LOCAL_NNCancel
void NNCancel(u32 cookie);
#endif
#ifndef PROTO_LOCAL_NNThink
void NNThink();
#endif
#ifndef PROTO_LOCAL_Matchup2Hostname
extern char *Matchup2Hostname;
#endif
#ifndef PROTO_LOCAL_NNProcessData
void NNProcessData(u8 *pkt, s32 len, SockAddrIn *sa);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_negotiateList
extern DArrayImplementation *negotiateList;
#endif
#ifndef PROTO_LOCAL_SendInitPackets
void SendInitPackets(_NATNegotiator *ctx);
#endif
#ifndef PROTO_LOCAL_SendPingPacket
void SendPingPacket(_NATNegotiator *ctx);
#endif
#ifndef PROTO_LOCAL_NegotiateThink
void NegotiateThink(_NATNegotiator *ctx);
#endif
#ifndef PROTO_LOCAL_SendConnectAck
void SendConnectAck(_NATNegotiator *ctx, SockAddrIn *sa);
#endif
#ifndef PROTO_LOCAL_ProcessConnectPacket
void ProcessConnectPacket(_NATNegotiator *ctx, u8 *pkt, SockAddrIn *sa);
#endif
#ifndef PROTO_LOCAL_ProcessPingPacket
void ProcessPingPacket(_NATNegotiator *ctx, u8 *pkt, SockAddrIn *sa);
#endif
#ifndef PROTO_LOCAL_ProcessInitPacket
void ProcessInitPacket(_NATNegotiator *ctx, u8 *pkt, SockAddrIn *sa);
#endif
}
#endif

#endif

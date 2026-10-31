#ifndef PROTO_PROTO_OV065_UNK_OV065_02261638_H
#define PROTO_PROTO_OV065_UNK_OV065_02261638_H


#include "types.h"
#include "net/IpFragEntry.h"
#include "net/IpHeader.h"
#include "net/IpSocket.h"
#include "net/IpStackConfig.h"
#include "nitro/math.h"
#include "sys/OSThread.h"
struct ArpCacheEntry;
#ifndef __cplusplus
typedef struct ArpCacheEntry ArpCacheEntry;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_0228f3c0
extern u8 data_ov065_0228f3c0[0x800];
#endif
#ifndef PROTO_LOCAL_sIpRecvThreadStack
extern u8 sIpRecvThreadStack[0x800];
#endif
#ifndef PROTO_LOCAL_sTimerThreadTxBuf
extern u8 sTimerThreadTxBuf[0x180];
#endif
#ifndef PROTO_LOCAL_sTimerThreadRxBuf
extern u8 sTimerThreadRxBuf[0x180];
#endif
#ifndef PROTO_LOCAL_sIpTimerThread
extern OSThread sIpTimerThread;
#endif
#ifndef PROTO_LOCAL_sIpRecvThread
extern OSThread sIpRecvThread;
#endif
#ifndef PROTO_LOCAL_sTimerThreadSoc
extern IpSocket sTimerThreadSoc;
#endif
#ifndef PROTO_LOCAL_sTcpResetSoc
extern IpSocket sTcpResetSoc;
#endif
#ifndef PROTO_LOCAL_data_ov065_0228ec1c
extern u8 data_ov065_0228ec1c[0x3c];
#endif
#ifndef PROTO_LOCAL_sIpRandState
extern MATHRandContext32 sIpRandState;
#endif
#ifndef PROTO_LOCAL_sLlcSnapHeader
extern u8 sLlcSnapHeader[12];
#endif
#ifndef PROTO_LOCAL_sDhcpHostName
extern char sDhcpHostName[];
#endif
#ifndef PROTO_LOCAL_sDnsServers
extern u32 sDnsServers[2];
#endif
#ifndef PROTO_LOCAL_sBroadcastMac
extern u8 sBroadcastMac[8];
#endif
#ifndef PROTO_LOCAL_sOwnMac
extern u8 sOwnMac[6];
#endif
#ifndef PROTO_LOCAL_sRecvRingSize
extern u32 sRecvRingSize;
#endif
#ifndef PROTO_LOCAL_sDhcpServerId
extern u32 sDhcpServerId;
#endif
#ifndef PROTO_LOCAL_sRecvRingWaiter
extern OSThread *sRecvRingWaiter;
#endif
#ifndef PROTO_LOCAL_sDhcpRequestedIp
extern u32 sDhcpRequestedIp;
#endif
#ifndef PROTO_LOCAL_sDhcpLeaseTime
extern u32 sDhcpLeaseTime;
#endif
#ifndef PROTO_LOCAL_sAddrConfiguredCallback
extern void (*sAddrConfiguredCallback) (void);
#endif
#ifndef PROTO_LOCAL_sIpTimerStopRequest
extern u32 sIpTimerStopRequest;
#endif
#ifndef PROTO_LOCAL_sIpFree
extern void (*sIpFree) (void *);
#endif
#ifndef PROTO_LOCAL_sIpIdleCallback
extern void (*sIpIdleCallback) (void);
#endif
#ifndef PROTO_LOCAL_sRecvRingWrite
extern u32 sRecvRingWrite;
#endif
#ifndef PROTO_LOCAL_sGateway
extern u32 sGateway;
#endif
#ifndef PROTO_LOCAL_sDhcpRetryTime
extern u32 sDhcpRetryTime;
#endif
#ifndef PROTO_LOCAL_sRecvRingRead
extern u32 sRecvRingRead;
#endif
#ifndef PROTO_LOCAL_sRecvRingBuf
extern u8 *sRecvRingBuf;
#endif
#ifndef PROTO_LOCAL_sIpStackStatus
extern u32 sIpStackStatus;
#endif
#ifndef PROTO_LOCAL_sIcmpEchoReplyEnabled
extern u32 sIcmpEchoReplyEnabled;
#endif
#ifndef PROTO_LOCAL_sIpLinkCheckCallback
extern s32 (*sIpLinkCheckCallback) (void);
#endif
#ifndef PROTO_LOCAL_sIpThreadPriority
extern u32 sIpThreadPriority;
#endif
#ifndef PROTO_LOCAL_sNetmask
extern u32 sNetmask;
#endif
#ifndef PROTO_LOCAL_sIpStackFlags
extern u32 sIpStackFlags;
#endif
#ifndef PROTO_LOCAL_sIpAlloc
extern void *(*sIpAlloc) (u32);
#endif
#ifndef PROTO_LOCAL_gOwnIp
extern u32 gOwnIp;
#endif
#ifndef PROTO_LOCAL_sIpYieldMode
extern u32 sIpYieldMode;
#endif
#ifndef PROTO_LOCAL_sIpIdCounter
extern u16 sIpIdCounter;
#endif
#ifndef PROTO_LOCAL_sIcmpSeq
extern u16 sIcmpSeq;
#endif
#ifndef PROTO_LOCAL_sMss
extern u16 sMss;
#endif
#ifndef PROTO_LOCAL_sNextEphemeralPort
extern u16 sNextEphemeralPort;
#endif
#ifndef PROTO_LOCAL_sLinkSendError
extern u8 sLinkSendError;
#endif
#ifndef PROTO_LOCAL_sArpConflict
extern u8 sArpConflict;
#endif
#ifndef PROTO_LOCAL_IpStack_ResetAddress
void IpStack_ResetAddress(u32 a);
#endif
#ifndef PROTO_LOCAL_IpStack_Yield
void IpStack_Yield(void);
#endif
#ifndef PROTO_LOCAL_IpStack_Nop
void IpStack_Nop(void);
#endif
#ifndef PROTO_LOCAL_IpStack_ReturnTrue
s32 IpStack_ReturnTrue(void);
#endif
#ifndef PROTO_LOCAL_IpStack_RequestStop
s32 IpStack_RequestStop(void);
#endif
#ifndef PROTO_LOCAL_IpStack_SetIdleCallback
void IpStack_SetIdleCallback(void (*f)(void));
#endif
#ifndef PROTO_LOCAL_IpStack_Shutdown
void IpStack_Shutdown(void);
#endif
#ifndef PROTO_LOCAL_IpStack_SetThreadPriority
void IpStack_SetThreadPriority(u32 a);
#endif
#ifndef PROTO_LOCAL_Ip_ChecksumAdd
u32 Ip_ChecksumAdd(u8 *p, u32 len, u32 sum);
#endif
#ifndef PROTO_LOCAL_Ip_ChecksumFinish
u32 Ip_ChecksumFinish(u32 x);
#endif
#ifndef PROTO_LOCAL_Ip_Checksum
u32 Ip_Checksum(u8 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_Ip_VerifyPseudoChecksum
s32 Ip_VerifyPseudoChecksum(u8 *a, u32 b, u8 *c, u32 d);
#endif
#ifndef PROTO_LOCAL_Ip_IsOnLocalNet
s32 Ip_IsOnLocalNet(u32 a);
#endif
#ifndef PROTO_LOCAL_Ip_GetNextHop
u32 Ip_GetNextHop(u32 a);
#endif
#ifndef PROTO_LOCAL_Ip_IsBroadcast
s32 Ip_IsBroadcast(u32 ip);
#endif
#ifndef PROTO_LOCAL_Ip_IsMulticast
s32 Ip_IsMulticast(u32 ip);
#endif
#ifndef PROTO_LOCAL_Ip_IsForMe
s32 Ip_IsForMe(u32 ip);
#endif
#ifndef PROTO_LOCAL_Eth_MacDiffers
s32 Eth_MacDiffers(const void *pa, const void *pb);
#endif
#ifndef PROTO_LOCAL_Eth_SendFrame
void Eth_SendFrame(u8 *hdr, u32 hlen, u8 *data, u32 n);
#endif
#ifndef PROTO_LOCAL_Eth_EnqueueFrame
void Eth_EnqueueFrame(u8 *a, u8 *b, u8 *c, u32 d, u8 *data, u32 n);
#endif
#ifndef PROTO_LOCAL_Eth_OnFrameReceived
void Eth_OnFrameReceived(u8 *a, u8 *b, u8 *c, u32 d);
#endif
#ifndef PROTO_LOCAL_Eth_WaitFrame
u8 *Eth_WaitFrame(u32 *out);
#endif
#ifndef PROTO_LOCAL_Eth_PopFrame
void Eth_PopFrame();
#endif
#ifndef PROTO_LOCAL_Arp_Lookup
u8 *Arp_Lookup(u32 ip);
#endif
#ifndef PROTO_LOCAL_Arp_SendRequest
void Arp_SendRequest(u32 ip);
#endif
#ifndef PROTO_LOCAL_Arp_Resolve
u8 *Arp_Resolve(u32 ip);
#endif
#ifndef PROTO_LOCAL_Arp_UpdateCache
void Arp_UpdateCache(u8 *mac, u32 ip, u32 flag);
#endif
#ifndef PROTO_LOCAL_Eth_SendIp
void Eth_SendIp(u8 *p, u32 off, u8 *data, u32 n, u32 x, u16 w);
#endif
#ifndef PROTO_LOCAL_Ip_SendPacket
void Ip_SendPacket(u8 *p, u32 off, u8 *data, u32 n, u32 x, u32 w);
#endif
#ifndef PROTO_LOCAL_Ip_Send
void Ip_Send(u8 *p, u32 len, u8 *data, u32 n, u32 x, u8 flag);
#endif
#ifndef PROTO_LOCAL_Icmp_SendEchoRequest
void Icmp_SendEchoRequest(u8 *a, u32 b, IpSocket *c);
#endif
#ifndef PROTO_LOCAL_Udp_Send
void Udp_Send(u8 *a, u32 b, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_Tcp_SendSegment
void Tcp_SendSegment(u8 *x, u32 y, IpSocket *s, u32 flags, u32 z);
#endif
#ifndef PROTO_LOCAL_Arp_SendReply
void Arp_SendReply(u8 *a);
#endif
#ifndef PROTO_LOCAL_Arp_Input
void Arp_Input(u8 *a, u32 len);
#endif
#ifndef PROTO_LOCAL_Icmp_SendEchoReply
void Icmp_SendEchoReply(u8 *a, u8 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Icmp_DeliverEchoReply
void Icmp_DeliverEchoReply(u8 *a, u8 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Ip_AreAddrsValid
s32 Ip_AreAddrsValid(u32 x, u32 y);
#endif
#ifndef PROTO_LOCAL_Icmp_Input
void Icmp_Input(u8 *a, u8 *b, u32 c);
#endif
#ifndef PROTO_LOCAL_Tcp_FindListener
IpSocket *Tcp_FindListener(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_Tcp_MatchConnection
s32 Tcp_MatchConnection(u8 *a, u8 *b, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_Tcp_FindConnection
IpSocket *Tcp_FindConnection(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_Tcp_ParseOptions
void Tcp_ParseOptions(u8 *a, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_Ip_IsNextHopResolved
s32 Ip_IsNextHopResolved(u32 x);
#endif
#ifndef PROTO_LOCAL_Tcp_SendControl
void Tcp_SendControl(IpSocket *s, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_Tcp_SendAck
void Tcp_SendAck(IpSocket *s, u32 x);
#endif
#ifndef PROTO_LOCAL_Tcp_SendFinAck
void Tcp_SendFinAck(IpSocket *s, u32 x);
#endif
#ifndef PROTO_LOCAL_Tcp_SendReset
void Tcp_SendReset(u8 *a, u8 *b, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_Tcp_AcceptSyn
void Tcp_AcceptSyn(u8 *a, u8 *b, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_Ip_Input
void Ip_Input(u8 *p, u32 len);
#endif
#ifndef PROTO_LOCAL_IpStack_RecvThreadMain
void IpStack_RecvThreadMain();
#endif
#ifndef PROTO_LOCAL_IpSoc_AllocEphemeralPort
u16 IpSoc_AllocEphemeralPort();
#endif
#ifndef PROTO_LOCAL_IpStack_Rand32
u32 IpStack_Rand32();
#endif
#ifndef PROTO_LOCAL_IpSoc_Use
void IpSoc_Use(IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_Unuse
void IpSoc_Unuse();
#endif
#ifndef PROTO_LOCAL_IpSoc_SetUdp
void IpSoc_SetUdp();
#endif
#ifndef PROTO_LOCAL_IpSoc_Bind
void IpSoc_Bind(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_IpSoc_Init
void IpSoc_Init();
#endif
#ifndef PROTO_LOCAL_IpSoc_Release
void IpSoc_Release();
#endif
#ifndef PROTO_LOCAL_IpSoc_ShareWithThread
void IpSoc_ShareWithThread(OSThread *t);
#endif
#ifndef PROTO_LOCAL_Tcp_Listen
void Tcp_Listen(IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_SetUdpCallback
void IpSoc_SetUdpCallback(IpSocketUdpCallback v);
#endif
#ifndef PROTO_LOCAL_IpSoc_TcpListen
void IpSoc_TcpListen();
#endif
#ifndef PROTO_LOCAL_Tcp_Connect
s32 Tcp_Connect(IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_TcpConnect
s32 IpSoc_TcpConnect();
#endif
#ifndef PROTO_LOCAL_IpSoc_GetPeer
u32 IpSoc_GetPeer(u16 *a, u32 *b);
#endif
#ifndef PROTO_LOCAL_Tcp_Shutdown
void Tcp_Shutdown(IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_TcpShutdown
void IpSoc_TcpShutdown();
#endif
#ifndef PROTO_LOCAL_IpSoc_TcpWaitClosed
void IpSoc_TcpWaitClosed();
#endif
#ifndef PROTO_LOCAL_IpSoc_WaitDatagram
u8 *IpSoc_WaitDatagram(u32 *out, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_Tcp_Read
u8 *Tcp_Read(u32 *out, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_Read
u8 *IpSoc_Read(u32 *out);
#endif
#ifndef PROTO_LOCAL_Tcp_Consume
void Tcp_Consume(u32 a, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_Consume
void IpSoc_Consume(u32 a);
#endif
#ifndef PROTO_LOCAL_Tcp_SendSegments
u32 Tcp_SendSegments(u8 *a, u32 b, IpSocket *s, u32 flag);
#endif
#ifndef PROTO_LOCAL_Tcp_SendTwoBuffers
void Tcp_SendTwoBuffers(u8 *a, u32 b, u8 *c, u32 d, IpSocket *s, u32 flag);
#endif
#ifndef PROTO_LOCAL_Tcp_Write
u32 Tcp_Write(u8 *a, u32 b, u8 *c, u32 d, IpSocket *s);
#endif
#ifndef PROTO_LOCAL_IpSoc_WriteTwo
u32 IpSoc_WriteTwo(u8 *a, u32 b, u8 *c, u32 d);
#endif
#ifndef PROTO_LOCAL_IpSoc_Write
u32 IpSoc_Write(const u8 *a, u32 b);
#endif
#ifndef PROTO_LOCAL_IpSoc_GetReadLength
s32 IpSoc_GetReadLength();
#endif
#ifndef PROTO_LOCAL_IpSoc_FlushPending
void IpSoc_FlushPending();
#endif
#ifndef PROTO_LOCAL_Arp_ProbeAddressConflict
void Arp_ProbeAddressConflict();
#endif
#ifndef PROTO_LOCAL_IpStack_TimerThreadMain
void IpStack_TimerThreadMain(void);
#endif
#ifndef PROTO_LOCAL_Dhcp_BuildHeader
u8 *Dhcp_BuildHeader(u8 *buf, u32 msgtype, u32 *xidout);
#endif
#ifndef PROTO_LOCAL_Dhcp_PadTo
u8 *Dhcp_PadTo(u32 a, u32 size, u8 *dst, u32 used);
#endif
#ifndef PROTO_LOCAL_Dhcp_SendDiscover
u32 Dhcp_SendDiscover(void);
#endif
#ifndef PROTO_LOCAL_Dhcp_SendRequest
u32 Dhcp_SendRequest(u32 mode);
#endif
#ifndef PROTO_LOCAL_Dhcp_WaitReply
s32 Dhcp_WaitReply(u32 xid, s32 i);
#endif
#ifndef PROTO_LOCAL_Dhcp_Discover
s32 Dhcp_Discover(void);
#endif
#ifndef PROTO_LOCAL_Dhcp_Request
s32 Dhcp_Request(u32 *out, s32 mode);
#endif
#ifndef PROTO_LOCAL_Dhcp_SendRelease
void Dhcp_SendRelease(void);
#endif
#ifndef PROTO_LOCAL_Dns_SkipName
u8 *Dns_SkipName(u8 *p);
#endif
#ifndef PROTO_LOCAL_Dns_Query
s32 Dns_Query(const u8 *name, u32 type, s32 xid);
#endif
#ifndef PROTO_LOCAL_IpAddr_ParseDecimal
u32 IpAddr_ParseDecimal(const u8 *p, const u8 **end);
#endif
#ifndef PROTO_LOCAL_IpAddr_Parse
s32 IpAddr_Parse(const u8 *s, u32 *out);
#endif
#ifndef PROTO_LOCAL_Dns_QueryServer
s32 Dns_QueryServer(const u8 *a, u32 server, s32 c);
#endif
#ifndef PROTO_LOCAL_Dns_Resolve
s32 Dns_Resolve(const char *self);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sIpFragTable
extern IpFragEntry sIpFragTable[8];
#endif
#ifndef PROTO_LOCAL_sArpCache
extern ArpCacheEntry sArpCache[8];
#endif
#ifndef PROTO_LOCAL_IpStack_Init
void IpStack_Init(IpStackConfig *c);
#endif
#ifndef PROTO_LOCAL_Tcp_InputSynExisting
s32 Tcp_InputSynExisting(IpHeader *p, TcpHeader *q, u32 r);
#endif
#ifndef PROTO_LOCAL_Tcp_InputSyn
void Tcp_InputSyn(IpHeader *p, TcpHeader *q, u32 r);
#endif
#ifndef PROTO_LOCAL_Tcp_InputSynAck
void Tcp_InputSynAck(IpHeader *p, TcpHeader *q, u32 r);
#endif
#ifndef PROTO_LOCAL_Tcp_InputAck
void Tcp_InputAck(IpHeader *p, TcpHeader *q, u32 r);
#endif
#ifndef PROTO_LOCAL_Tcp_InputFin
void Tcp_InputFin(IpHeader *p, TcpHeader *q, u32 r);
#endif
#ifndef PROTO_LOCAL_Tcp_InputRst
void Tcp_InputRst(IpHeader *p, TcpHeader *q);
#endif
#ifndef PROTO_LOCAL_Tcp_Input
void Tcp_Input(IpHeader *p, TcpHeader *q, u32 r);
#endif
#ifndef PROTO_LOCAL_Udp_Input
void Udp_Input(IpHeader *p, UdpHeader *q, u32 c);
#endif
#ifndef PROTO_LOCAL_Ip_Reassemble
u8 *Ip_Reassemble(IpHeader *p, s32 *out);
#endif
}
#endif

#endif

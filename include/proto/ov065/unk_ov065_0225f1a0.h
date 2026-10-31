#ifndef PROTO_PROTO_OV065_UNK_OV065_0225F1A0_H
#define PROTO_PROTO_OV065_UNK_OV065_0225F1A0_H


#include "types.h"
#include "net/IpStackConfig.h"
#include "net/SockCoreConfig.h"
#ifdef __cplusplus
#include "net/SockCoreSocket.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sSockCoreState
extern u32 sSockCoreState;
#endif
#ifndef PROTO_LOCAL_sSockLastHostIp
extern u32 sSockLastHostIp;
#endif
#ifndef PROTO_LOCAL_sSockYieldMode
extern u32 sSockYieldMode;
#endif
#ifndef PROTO_LOCAL_SockCore_CreateMsgPoolAndDefaultSocket
s32 SockCore_CreateMsgPoolAndDefaultSocket(void);
#endif
#ifndef PROTO_LOCAL_SockCore_SetupStackConfig
void SockCore_SetupStackConfig(void);
#endif
#ifndef PROTO_LOCAL_SockCore_OnStaticAddressReady
void SockCore_OnStaticAddressReady(void);
#endif
#ifndef PROTO_LOCAL_SockCore_OnDhcpAddressReady
void SockCore_OnDhcpAddressReady(void);
#endif
#ifndef PROTO_LOCAL_SockCore_IsLinkUp
BOOL SockCore_IsLinkUp(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sSockDefaultSocket
extern SockCoreSocket *sSockDefaultSocket;
#endif
#ifndef PROTO_LOCAL_sSockCoreConfig
extern SockCoreConfig *sSockCoreConfig;
#endif
#ifndef PROTO_LOCAL_sIpStackParams
extern IpStackConfig sIpStackParams;
#endif
#ifndef PROTO_LOCAL_SockCore_Startup
s32 SockCore_Startup(SockCoreConfig *cfg);
#endif
}
#endif

#endif

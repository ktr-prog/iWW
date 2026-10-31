#ifndef PROTO_PROTO_OV065_UNK_OV065_0226CB18_H
#define PROTO_PROTO_OV065_UNK_OV065_0226CB18_H


#include "types.h"
#include "net/WifiApContext.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWifiApUsbKey1
extern s8 sWifiApUsbKey1[16];
#endif
#ifndef PROTO_LOCAL_sWifiApUsbKey2
extern s8 sWifiApUsbKey2[16];
#endif
#ifndef PROTO_LOCAL_sWifiApNdwcshapPermTable
extern u8 sWifiApNdwcshapPermTable[24];
#endif
#ifndef PROTO_LOCAL_sWifiApNdwcshapKey2
extern s8 sWifiApNdwcshapKey2[28];
#endif
#ifndef PROTO_LOCAL_sWifiApNdwcshapKey1
extern s8 sWifiApNdwcshapKey1[28];
#endif
#ifndef PROTO_LOCAL_sWifiApNdwcshapKey1Ptr
extern s8 *sWifiApNdwcshapKey1Ptr;
#endif
#ifndef PROTO_LOCAL_sWifiApUsbKey1Ptr
extern s8 *sWifiApUsbKey1Ptr;
#endif
#ifndef PROTO_LOCAL_sWifiApNdwcshapKey2Ptr
extern s8 *sWifiApNdwcshapKey2Ptr;
#endif
#ifndef PROTO_LOCAL_sWifiApUsbKey2Ptr
extern s8 *sWifiApUsbKey2Ptr;
#endif
#ifndef PROTO_LOCAL_WifiAp_IsNdwcshapAp
s32 WifiAp_IsNdwcshapAp(u8 *a);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetNdwcshapWepKey
void WifiAp_GetNdwcshapWepKey(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetNdwcshapApInfo
void WifiAp_GetNdwcshapApInfo(u8 *a, void *dst);
#endif
#ifndef PROTO_LOCAL_WifiAp_IsUsbConnectorAp
s32 WifiAp_IsUsbConnectorAp(void *p);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetUsbApWepKey
void WifiAp_GetUsbApWepKey(u8 *p, u8 *out);
#endif
#ifndef PROTO_LOCAL_WifiAp_DecodeNdwcshapSsid
void WifiAp_DecodeNdwcshapSsid(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_WifiAp_DeriveNdwcshapWepKey
void WifiAp_DeriveNdwcshapWepKey(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_WifiAp_DeriveUsbApWepKey
void WifiAp_DeriveUsbApWepKey(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_WifiAp_Base64Value
s32 WifiAp_Base64Value(u32 c);
#endif
#ifndef PROTO_LOCAL_WifiAp_Base64Decode
s32 WifiAp_Base64Decode(u8 *in, u8 *out, u32 len, u32 max);
#endif
#ifndef PROTO_LOCAL_WifiAp_ProcessNetSetup
s32 WifiAp_ProcessNetSetup(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepStartSockets
s32 WifiAp_StepStartSockets(WifiApContext *c);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepWaitAddress
s32 WifiAp_StepWaitAddress(WifiApContext *c);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepStartNetCheck
s32 WifiAp_StepStartNetCheck(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepWaitNetCheck
s32 WifiAp_StepWaitNetCheck(WifiApContext *c);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepConnected
s32 WifiAp_StepConnected(WifiApContext *c);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepStopSockets
s32 WifiAp_StepStopSockets(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

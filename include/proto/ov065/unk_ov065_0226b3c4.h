#ifndef PROTO_PROTO_OV065_UNK_OV065_0226B3C4_H
#define PROTO_PROTO_OV065_UNK_OV065_0226B3C4_H


#include "types.h"
#include "net/WifiApContext.h"
#include "net/WifiApControl.h"
#include "nitro/wm.h"
#ifdef __cplusplus
#include "net/WifiLinkEvent.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWifiApSsidUsbConnector
extern char sWifiApSsidUsbConnector[12];
#endif
#ifndef PROTO_LOCAL_sWifiApHostName
extern char sWifiApHostName[12];
#endif
#ifndef PROTO_LOCAL_WifiAp_BuildSocketConfig
void WifiAp_BuildSocketConfig(u8 *a, WifiApContext *b, u8 *c);
#endif
#ifndef PROTO_LOCAL_WifiAp_ReadAddress
u32 WifiAp_ReadAddress(u8 *p);
#endif
#ifndef PROTO_LOCAL_WifiAp_PrefixToNetmask
u32 WifiAp_PrefixToNetmask(s32 n);
#endif
#ifndef PROTO_LOCAL_WifiAp_ApplyStaticDns
void WifiAp_ApplyStaticDns(WifiApContext *c);
#endif
#ifndef PROTO_LOCAL_WifiAp_ProcessStartup
s32 WifiAp_ProcessStartup(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_ProcessSearch
s32 WifiAp_ProcessSearch(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_AddFoundChannel
void WifiAp_AddFoundChannel(u32 v);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetNthFoundChannel
s32 WifiAp_GetNthFoundChannel(u32 n);
#endif
#ifndef PROTO_LOCAL_WifiAp_RescanForState
void WifiAp_RescanForState(u32 r);
#endif
#ifndef PROTO_LOCAL_WifiAp_BeginSearch
s32 WifiAp_BeginSearch(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepScanAllChannels
s32 WifiAp_StepScanAllChannels(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_RestartSearch
s32 WifiAp_RestartSearch(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepScanSsids
s32 WifiAp_StepScanSsids(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepScanFoundChannels
s32 WifiAp_StepScanFoundChannels(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_FinishSearchPass
s32 WifiAp_FinishSearchPass(WifiApContext *ctx, s32 s);
#endif
#ifndef PROTO_LOCAL_WifiAp_CheckSearchResult
s32 WifiAp_CheckSearchResult(WifiApContext *ctx, s32 s);
#endif
#ifndef PROTO_LOCAL_WifiAp_NextSearchPass
s32 WifiAp_NextSearchPass(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_StartScan
void WifiAp_StartScan(void *a, void *b, s32 n, u32 flags);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepRecoverLink
s32 WifiAp_StepRecoverLink(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_BuildSearchList
s32 WifiAp_BuildSearchList(s32 mode);
#endif
#ifndef PROTO_LOCAL_WifiAp_IsFreespot
s32 WifiAp_IsFreespot(WMBssDesc *rec);
#endif
#ifndef PROTO_LOCAL_WifiAp_BuildSearchWithFreespot
s32 WifiAp_BuildSearchWithFreespot(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_BuildSearchWithHotspots
s32 WifiAp_BuildSearchWithHotspots(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_BuildSearchFromSettings
u8 WifiAp_BuildSearchFromSettings(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_BuildSearchFromFound
u32 WifiAp_BuildSearchFromFound(s32 n, WifiApFoundInfo *p, WifiApSearchEntry *out, WMBssDesc *rec);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepFailedCleanup
s32 WifiAp_StepFailedCleanup(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetErrorCode2
s32 WifiAp_GetErrorCode2(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_MapStartupError
s32 WifiAp_MapStartupError(u32 r);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetWirelessOffError
s32 WifiAp_GetWirelessOffError(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_CleanupStep
s32 WifiAp_CleanupStep(u8 *p);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepLinkShutdown
s32 WifiAp_StepLinkShutdown(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_StopSocketLayer
s32 WifiAp_StopSocketLayer(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_ProcessConnect
s32 WifiAp_ProcessConnect(void);
#endif
#ifndef PROTO_LOCAL_WifiAp_PrepareConnect
s32 WifiAp_PrepareConnect(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_StepConnect
s32 WifiAp_StepConnect(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_SelectApType
u32 WifiAp_SelectApType(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetPowerOption
u32 WifiAp_GetPowerOption(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetAuthOption
u32 WifiAp_GetAuthOption(WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetWepSetting
BOOL WifiAp_GetWepSetting(WifiApContext *ctx, u32 idx, u8 *out);
#endif
#ifndef PROTO_LOCAL_WifiAp_OnApFound
void WifiAp_OnApFound(WMBssDesc *rec);
#endif
#ifndef PROTO_LOCAL_WifiAp_MatchSpecialSsid
s32 WifiAp_MatchSpecialSsid(WMBssDesc *rec);
#endif
#ifndef PROTO_LOCAL_WifiAp_MatchSearchEntry
s32 WifiAp_MatchSearchEntry(WMBssDesc *rec, s32 n, WifiApSearchEntry *e);
#endif
#ifndef PROTO_LOCAL_WifiAp_AddFoundAp
s32 WifiAp_AddFoundAp(u32 a, WMBssDesc *rec, WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_StoreNewFoundAp
void WifiAp_StoreNewFoundAp(u32 a, WMBssDesc *rec, WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_UpdateFoundAp
void WifiAp_UpdateFoundAp(u32 a, WMBssDesc *rec, WifiApContext *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_SortFoundAp
void WifiAp_SortFoundAp(u32 n, WifiApContext *ctx);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_WifiAp_GetNoApErrorCode
s32 WifiAp_GetNoApErrorCode(WifiApControl *p);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetErrorCodeForState
s32 WifiAp_GetErrorCodeForState(WifiApControl *o);
#endif
#ifndef PROTO_LOCAL_WifiAp_OnLinkNotify
void WifiAp_OnLinkNotify(WifiLinkEvent *m);
#endif
}
#endif

#endif

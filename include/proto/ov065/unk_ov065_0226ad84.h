#ifndef PROTO_PROTO_OV065_UNK_OV065_0226AD84_H
#define PROTO_PROTO_OV065_UNK_OV065_0226AD84_H


#include "types.h"
#include "net/WifiApConfig.h"
#include "net/WifiApContext.h"
#include "net/WifiApControl.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWifiApAllocator
extern WifiApAllocator *sWifiApAllocator;
#endif
#ifndef PROTO_LOCAL_sWifiApSocketConfig
extern void *sWifiApSocketConfig;
#endif
#ifndef PROTO_LOCAL_sWifiApLinkWork
extern void *sWifiApLinkWork;
#endif
#ifndef PROTO_LOCAL_sWifiApContext
extern WifiApContext *sWifiApContext;
#endif
#ifndef PROTO_LOCAL_WifiAp_Init
s32 WifiAp_Init(WifiApConfig *cfg);
#endif
#ifndef PROTO_LOCAL_WifiAp_Process
s32 WifiAp_Process();
#endif
#ifndef PROTO_LOCAL_WifiAp_GetStatus
s32 WifiAp_GetStatus();
#endif
#ifndef PROTO_LOCAL_WifiAp_GetConnectedApType
u32 WifiAp_GetConnectedApType();
#endif
#ifndef PROTO_LOCAL_WifiAp_RequestCleanup
s32 WifiAp_RequestCleanup();
#endif
#ifndef PROTO_LOCAL_WifiAp_SetApEntry
void WifiAp_SetApEntry(u32 idx, void *dst);
#endif
#ifndef PROTO_LOCAL_WifiAp_AllocBlock
void *WifiAp_AllocBlock(u32 m, u32 a);
#endif
#ifndef PROTO_LOCAL_WifiAp_FreeBlock
void WifiAp_FreeBlock(u32 m, void *a, u32 b);
#endif
#ifndef PROTO_LOCAL_WifiAp_FreeAll
void WifiAp_FreeAll();
#endif
#ifndef PROTO_LOCAL_WifiAp_GetBlock
void *WifiAp_GetBlock(u32 m);
#endif
#ifndef PROTO_LOCAL_WifiAp_SetState
void WifiAp_SetState(u8 v);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetState
u8 WifiAp_GetState();
#endif
#ifndef PROTO_LOCAL_WifiAp_SetError
void WifiAp_SetError(u32 v);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetErrorCode
u32 WifiAp_GetErrorCode();
#endif
#ifndef PROTO_LOCAL_WifiAp_SetConnectedApType
void WifiAp_SetConnectedApType(u32 v);
#endif
#ifndef PROTO_LOCAL_WifiAp_FoldApIndex
u32 WifiAp_FoldApIndex(u32 x);
#endif
#ifndef PROTO_LOCAL_WifiAp_FreeContext
void WifiAp_FreeContext();
#endif
#ifndef PROTO_LOCAL_WifiAp_GetConnectResultKind
s32 WifiAp_GetConnectResultKind();
#endif
#ifndef PROTO_LOCAL_WifiAp_HashReset
void WifiAp_HashReset(void *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_HashSetSource
void WifiAp_HashSetSource(void *ctx, const void *data, u32 len);
#endif
#ifndef PROTO_LOCAL_WifiAp_HashGetDigest
void WifiAp_HashGetDigest(u8 *out, void *ctx);
#endif
#ifndef PROTO_LOCAL_WifiAp_MacEquals
BOOL WifiAp_MacEquals(u8 *a, u8 *b);
#endif
#ifndef PROTO_LOCAL_WifiAp_GetLinkLevel
s32 WifiAp_GetLinkLevel();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWifiApControl
extern WifiApControl *sWifiApControl;
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV065_UNK_OV065_0227F2A4_H
#define PROTO_PROTO_OV065_UNK_OV065_0227F2A4_H


#include "types.h"
#include "net/gpiBuffer.h"
#include "net/gpiInfo.h"
#ifdef __cplusplus
#include "net/gp.h"
#include "net/gpiCallback.h"
#include "net/gpiOperation.h"
#include "net/gpiProfile.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gpiIntToDate
s32 gpiIntToDate(void *ctx, s32 packed, s32 *pa, s32 *pb, s32 *pc);
#endif
#ifndef PROTO_LOCAL_gpiSendLocalInfo
s32 gpiSendLocalInfo(GPConnection *h, char *a, char *b);
#endif
#ifndef PROTO_LOCAL_gpiSendUserInfo
s32 gpiSendUserInfo(GPConnection *h, char *a, char *b);
#endif
#ifndef PROTO_LOCAL_gpiSetInfoi
s32 gpiSetInfoi(GPConnection *h, s32 code, s32 val);
#endif
#ifndef PROTO_LOCAL_Unk_ov065_0227f54c_pool_order
__declspec(weak) void Unk_ov065_0227f54c_pool_order(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiInfoCacheToArg
void gpiInfoCacheToArg(GPIInfoCache *s, GPGetInfoResponseArg *d);
#endif
#ifndef PROTO_LOCAL_gpiProcessGetInfo
s32 gpiProcessGetInfo(GPConnection *h, GPIOperation *req, char *str);
#endif
#ifndef PROTO_LOCAL_gpiAddLocalInfo
s32 gpiAddLocalInfo(GPConnection *h, GPIBuffer *p);
#endif
#ifndef PROTO_LOCAL_gpiSetInfos
s32 gpiSetInfos(GPConnection *h, s32 cmd, char *val);
#endif
#ifndef PROTO_LOCAL_gpiSendGetInfo
s32 gpiSendGetInfo(GPConnection *h, s32 a1, s32 a2);
#endif
#ifndef PROTO_LOCAL_gpiGetInfo
s32 gpiGetInfo(GPConnection *h, s32 a1, s32 a2, s32 a3, GPCallback a4, void *a5);
#endif
#ifndef PROTO_LOCAL_gpiSetInfoCache
s32 gpiSetInfoCache(GPConnection *h, GPIProfile *p, GPIInfoCache *q);
#endif
#ifndef PROTO_LOCAL_gpiFreeInfoCache
void gpiFreeInfoCache(GPIProfile *p);
#endif
}
#endif

#endif

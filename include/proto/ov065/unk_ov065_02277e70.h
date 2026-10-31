#ifndef PROTO_PROTO_OV065_UNK_OV065_02277E70_H
#define PROTO_PROTO_OV065_UNK_OV065_02277E70_H


#include "types.h"
#include "net/DwcGsHttpCallbackCtx.h"
#include "net/ghttpConnection.h"
struct GsAvailQuery;
#ifndef __cplusplus
typedef struct GsAvailQuery GsAvailQuery;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_SendPacket
void SendPacket();
#endif
#ifndef PROTO_LOCAL_GSIStartAvailableCheckA
void GSIStartAvailableCheckA(char *url);
#endif
#ifndef PROTO_LOCAL_HandlePacket
s32 HandlePacket(s8 *b, s32 n, u8 *addr, u32 *out);
#endif
#ifndef PROTO_LOCAL_GSIAvailableCheckThink
s32 GSIAvailableCheckThink();
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_Startup
s32 DwcGsHttp_Startup();
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_Cleanup
s32 DwcGsHttp_Cleanup();
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_Process
s32 DwcGsHttp_Process();
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_OnRequestDone
s32 DwcGsHttp_OnRequestDone(u32 request, u32 e, char *c, u32 d, void *param);
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_PostCreate
void DwcGsHttp_PostCreate(GHIPost **p);
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_PostAddString
s32 DwcGsHttp_PostAddString(GHIPost **p, const char *name, const char *value);
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_Post
s32 DwcGsHttp_Post(const char *a, GHIPost **pa, DwcGsHttpCallback cb, void *ud);
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_Get
s32 DwcGsHttp_Get(const char *a, DwcGsHttpCallback cb, void *ud);
#endif
#ifndef PROTO_LOCAL_DwcGsHttp_ReportError
s32 DwcGsHttp_ReportError(s32 e);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_AC
extern GsAvailQuery AC;
#endif
}
#endif

#endif

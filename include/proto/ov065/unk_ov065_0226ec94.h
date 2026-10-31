#ifndef PROTO_PROTO_OV065_UNK_OV065_0226EC94_H
#define PROTO_PROTO_OV065_UNK_OV065_0226EC94_H


#include "types.h"
#include "net/DwcHttp.h"
#include "net/NasAuthParams.h"
#include "net/NetCheck.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sNetCheckUrlPtr
extern char *sNetCheckUrlPtr;
#endif
#ifndef PROTO_LOCAL_sNetCheckHttp
extern DwcHttp *sNetCheckHttp;
#endif
#ifndef PROTO_LOCAL_sNetCheckUrl
extern char sNetCheckUrl[0x24];
#endif
#ifndef PROTO_LOCAL_sNetCheck
extern NetCheckWork *sNetCheck;
#endif
#ifndef PROTO_LOCAL_sNetCheckHttpParams
extern DwcHttpParams sNetCheckHttpParams;
#endif
#ifndef PROTO_LOCAL_sNetCheckNasConfig
extern NasAuthParams sNetCheckNasConfig;
#endif
#ifndef PROTO_LOCAL_NetCheck_Start
s32 NetCheck_Start(NetCheckParams *cfg);
#endif
#ifndef PROTO_LOCAL_NetCheck_Destroy
void NetCheck_Destroy();
#endif
#ifndef PROTO_LOCAL_NetCheck_StartThread
void NetCheck_StartThread();
#endif
#ifndef PROTO_LOCAL_NetCheck_Abort
void NetCheck_Abort();
#endif
#ifndef PROTO_LOCAL_NetCheck_ThreadMain
void NetCheck_ThreadMain(void);
#endif
#ifndef PROTO_LOCAL_NetCheck_GetState
s32 NetCheck_GetState(void);
#endif
#ifndef PROTO_LOCAL_NetCheck_SetState
void NetCheck_SetState(s32 v);
#endif
#ifndef PROTO_LOCAL_NetCheck_GetErrorCode
s32 NetCheck_GetErrorCode(void);
#endif
#ifndef PROTO_LOCAL_Unk_ov065_0226ecfc_pool_order
__declspec(weak) void Unk_ov065_0226ecfc_pool_order(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

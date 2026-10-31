#ifndef PROTO_PROTO_OV065_UNK_OV065_0226DE0C_H
#define PROTO_PROTO_OV065_UNK_OV065_0226DE0C_H


#include "types.h"
#include "net/DwcHttp.h"
#include "net/SslConnection.h"
#include "net/SslRootCa.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sDwcHttpRootCaList
extern SslRootCa *sDwcHttpRootCaList[11];
#endif
#ifndef PROTO_LOCAL_sDwcHttpTestServer
extern s32 sDwcHttpTestServer;
#endif
#ifndef PROTO_LOCAL_DwcHttp_Init
s32 DwcHttp_Init(DwcHttp *c, DwcHttpParams *cfg);
#endif
#ifndef PROTO_LOCAL_DwcHttp_FinishHeaders
s32 DwcHttp_FinishHeaders(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_StartThread
void DwcHttp_StartThread(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_Abort
void DwcHttp_Abort(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_CheckNotAborted
s32 DwcHttp_CheckNotAborted(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_ThreadMain
void DwcHttp_ThreadMain(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_Destroy
void DwcHttp_Destroy(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_BuildRequestLine
s32 DwcHttp_BuildRequestLine(DwcHttp *c);
#endif
#ifndef PROTO_LOCAL_DwcHttp_AddHeader
s32 DwcHttp_AddHeader(DwcHttp *c, const char *a1, const char *a2);
#endif
#ifndef PROTO_LOCAL_DwcHttp_AddFormParam
s32 DwcHttp_AddFormParam(DwcHttp *c, const char *a1, void *a2, s32 a3);
#endif
#ifndef PROTO_LOCAL_DwcHttp_AppendBody
s32 DwcHttp_AppendBody(DwcHttp *c, const char *s);
#endif
#ifndef PROTO_LOCAL_DwcHttp_CertCallback
u32 DwcHttp_CertCallback(u32 v, SslConnection *ssl, s32 depth);
#endif
#ifndef PROTO_LOCAL_DwcHttp_AllocBuffer
s32 DwcHttp_AllocBuffer(DwcHttp *c, DwcHttpBuffer *b, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcHttp_FreeBuffer
void DwcHttp_FreeBuffer(DwcHttp *c, DwcHttpBuffer *b);
#endif
#ifndef PROTO_LOCAL_DwcHttp_GrowBuffer
s32 DwcHttp_GrowBuffer(DwcHttp *c, DwcHttpBuffer *b, s32 n);
#endif
#ifndef PROTO_LOCAL_DwcHttp_ParseUrl
s32 DwcHttp_ParseUrl(DwcHttp *c, char *s);
#endif
#ifndef PROTO_LOCAL_DwcHttp_AddField
s32 DwcHttp_AddField(DwcHttpFieldList *l, const char *k, char *v);
#endif
#ifndef PROTO_LOCAL_DwcHttp_ParseResponse
s32 DwcHttp_ParseResponse(DwcHttpField *tbl, s32 n, s32 flag, char *text);
#endif
#ifndef PROTO_LOCAL_DwcHttp_FindField
char *DwcHttp_FindField(DwcHttpField *tbl, s32 n, const char *key);
#endif
#ifndef PROTO_LOCAL_DwcHttp_GetFieldDecoded
s32 DwcHttp_GetFieldDecoded(DwcHttpField *tbl, s32 n, const char *key, char *dst, u32 size);
#endif
#ifndef PROTO_LOCAL_DwcHttp_GetFieldString
s32 DwcHttp_GetFieldString(DwcHttpField *tbl, s32 n, const char *key, char *dst, s32 size);
#endif
#ifdef __cplusplus
}
#endif

#endif

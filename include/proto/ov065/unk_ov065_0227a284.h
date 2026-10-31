#ifndef PROTO_PROTO_OV065_UNK_OV065_0227A284_H
#define PROTO_PROTO_OV065_UNK_OV065_0227A284_H


#include "types.h"
#include "net/ghttpConnection.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_0228ca58
extern char data_ov065_0228ca58[4];
#endif
#ifndef PROTO_LOCAL_data_ov065_022910e4
extern volatile s32 data_ov065_022910e4;
#endif
#ifndef PROTO_LOCAL_data_ov065_022910e0
extern volatile s32 data_ov065_022910e0;
#endif
#ifndef PROTO_LOCAL_data_ov065_022910dc
extern volatile s32 data_ov065_022910dc;
#endif
#ifndef PROTO_LOCAL_data_ov065_022910e8
extern volatile s32 data_ov065_022910e8;
#endif
#ifndef PROTO_LOCAL_ghiParseURL
BOOL ghiParseURL(GHIConnection *u);
#endif
#ifndef PROTO_LOCAL_ghiDoHostLookup
void ghiDoHostLookup(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoConnecting
void ghiDoConnecting(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoSecuringSession
void ghiDoSecuringSession(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoSendingRequest
void ghiDoSendingRequest(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoPosting
void ghiDoPosting(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoWaiting
void ghiDoWaiting(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiParseStatus
s32 ghiParseStatus(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDoReceivingStatus
void ghiDoReceivingStatus(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiDeliverIncomingFileData
s32 ghiDeliverIncomingFileData(GHIConnection *self, char *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ghiParseChunkSize
s32 ghiParseChunkSize(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiAppendToChunkHeaderBuffer
void ghiAppendToChunkHeaderBuffer(GHIConnection *self, char *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ghiProcessIncomingFileData
s32 ghiProcessIncomingFileData(GHIConnection *self, char *p, s32 n);
#endif
#ifndef PROTO_LOCAL_ghiDoReceivingHeaders
void ghiDoReceivingHeaders(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_Unk_ov065_0227ae94_pool_order
__declspec(weak) void Unk_ov065_0227ae94_pool_order(void);
#endif
#ifndef PROTO_LOCAL_ghiDoReceivingFile
void ghiDoReceivingFile(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiPostDataFree
void ghiPostDataFree(GHIPostData *r);
#endif
#ifndef PROTO_LOCAL_ghiIsPostAutoFree
s32 ghiIsPostAutoFree(GHIPost *t);
#endif
#ifndef PROTO_LOCAL_ghiFreePost
void ghiFreePost(GHIPost *t);
#endif
#ifndef PROTO_LOCAL_ghiPostAddString
s32 ghiPostAddString(GHIPost *self, char *a, char *b);
#endif
#ifndef PROTO_LOCAL_ghiPostGetContentType
char *ghiPostGetContentType(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiPostGetNoFilesContentLength
s32 ghiPostGetNoFilesContentLength(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiPostGetHasFilesContentLength
s32 ghiPostGetHasFilesContentLength(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiPostGetContentLength
s32 ghiPostGetContentLength(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiPostStateInit
s32 ghiPostStateInit(GHIPostState *it);
#endif
#ifndef PROTO_LOCAL_ghiPostStateCleanup
void ghiPostStateCleanup(GHIPostState *it);
#endif
#ifndef PROTO_LOCAL_ghiPostInitState
s32 ghiPostInitState(GHIConnection *self);
#endif
#ifndef PROTO_LOCAL_ghiPostStringStateDoPosting
s32 ghiPostStringStateDoPosting(GHIPostState *st, GHIConnection *c);
#endif
#ifndef PROTO_LOCAL_ghiPostFileDiskStateDoPosting
s32 ghiPostFileDiskStateDoPosting(GHIPostState *st, GHIConnection *c);
#endif
#ifndef PROTO_LOCAL_ghiPostFileMemoryStateDoPosting
s32 ghiPostFileMemoryStateDoPosting(GHIPostState *st, GHIConnection *c);
#endif
#ifndef PROTO_LOCAL_ghiPostStateDoPosting
s32 ghiPostStateDoPosting(GHIPostState *st, GHIConnection *c, s32 first);
#endif
#ifndef PROTO_LOCAL_ghiPostDoPosting
s32 ghiPostDoPosting(GHIConnection *c);
#endif
#ifndef PROTO_LOCAL_ghiHandleStatus
void ghiHandleStatus(GHIConnection *c);
#endif
#ifndef PROTO_LOCAL_ghiProcessConnection
s32 ghiProcessConnection(GHIConnection *c);
#endif
#ifdef __cplusplus
}
#endif

#endif

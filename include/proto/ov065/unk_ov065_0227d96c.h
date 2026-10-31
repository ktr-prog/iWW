#ifndef PROTO_PROTO_OV065_UNK_OV065_0227D96C_H
#define PROTO_PROTO_OV065_UNK_OV065_0227D96C_H


#include "types.h"
#include "net/gpiBuffer.h"
#ifdef __cplusplus
#include "net/gp.h"
#include "net/gpiPeer.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_Unk_ov065_0227dc00_pool_order
__declspec(weak) void Unk_ov065_0227dc00_pool_order(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiAppendCharToBuffer
s32 gpiAppendCharToBuffer(GPConnection *h, GPIBuffer *b, char c);
#endif
#ifndef PROTO_LOCAL_gpiAppendStringToBufferLen
s32 gpiAppendStringToBufferLen(GPConnection *h, GPIBuffer *b, const char *s, s32 n);
#endif
#ifndef PROTO_LOCAL_gpiAppendStringToBuffer
s32 gpiAppendStringToBuffer(GPConnection *h, GPIBuffer *b, const char *s);
#endif
#ifndef PROTO_LOCAL_gpiAppendIntToBuffer
s32 gpiAppendIntToBuffer(GPConnection *h, GPIBuffer *b, s32 n);
#endif
#ifndef PROTO_LOCAL_gpiSendData
s32 gpiSendData(GPConnection *h, s32 fd, char *buf, s32 len, s32 *pflag, s32 *pcnt, const char *str);
#endif
#ifndef PROTO_LOCAL_gpiSendOrBufferChar
s32 gpiSendOrBufferChar(GPConnection *h, GPIPeer *c, char ch);
#endif
#ifndef PROTO_LOCAL_gpiSendOrBufferStringLen
s32 gpiSendOrBufferStringLen(GPConnection *h, GPIPeer *c, const char *s, s32 n);
#endif
#ifndef PROTO_LOCAL_gpiSendOrBufferString
s32 gpiSendOrBufferString(GPConnection *h, GPIPeer *c, const char *s);
#endif
#ifndef PROTO_LOCAL_gpiRecvToBuffer
s32 gpiRecvToBuffer(GPConnection *h, s32 fd, GPIBuffer *b, s32 *pout, s32 *pflag, const char *str);
#endif
#ifndef PROTO_LOCAL_gpiSendFromBuffer
s32 gpiSendFromBuffer(GPConnection *h, s32 fd, GPIBuffer *b, s32 *pout, s32 compact, const char *str);
#endif
#ifndef PROTO_LOCAL_gpiReadMessageFromBuffer
s32 gpiReadMessageFromBuffer(void *h, GPIBuffer *b, char **pp, s32 *plen, s32 *pval);
#endif
#ifndef PROTO_LOCAL_gpiClipBufferToPosition
s32 gpiClipBufferToPosition(void *h, GPIBuffer *b);
#endif
}
#endif

#endif

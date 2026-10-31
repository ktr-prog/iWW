#ifndef PROTO_PROTO_OV065_UNK_OV065_0227CD34_H
#define PROTO_PROTO_OV065_UNK_OV065_0227CD34_H


#include "types.h"
#ifdef __cplusplus
#include "net/gp.h"
#include "net/gpiProfile.h"
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiSendAuthBuddyRequest
s32 gpiSendAuthBuddyRequest(GPConnection *h, GPIProfile *a);
#endif
#ifndef PROTO_LOCAL_gpiProcessRecvBuddyMessage
s32 gpiProcessRecvBuddyMessage(GPConnection *h, const char *s);
#endif
#ifndef PROTO_LOCAL_gpiSendServerBuddyMessage
s32 gpiSendServerBuddyMessage(GPConnection *h, s32 a, s32 b, const char *s);
#endif
#ifndef PROTO_LOCAL_gpiSendBuddyMessage
s32 gpiSendBuddyMessage(GPConnection *h, s32 id, s32 b, const char *t);
#endif
#ifndef PROTO_LOCAL_gpiAuthBuddyRequest
s32 gpiAuthBuddyRequest(GPConnection *h, s32 id);
#endif
#ifndef PROTO_LOCAL_gpiFixBuddyIndices
s32 gpiFixBuddyIndices(GPConnection *h, GPIProfile *n, void *data);
#endif
#ifndef PROTO_LOCAL_gpiDeleteBuddy
s32 gpiDeleteBuddy(GPConnection *h, s32 x);
#endif
}
#endif

#endif

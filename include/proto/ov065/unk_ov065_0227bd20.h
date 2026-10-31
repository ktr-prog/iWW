#ifndef PROTO_PROTO_OV065_UNK_OV065_0227BD20_H
#define PROTO_PROTO_OV065_UNK_OV065_0227BD20_H


#include "types.h"
#include "net/gp.h"
#ifdef __cplusplus
#include "net/gpiCallback.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gpInitialize
s32 gpInitialize(GPConnection *h, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_gpDestroy
void gpDestroy(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpProcess
s32 gpProcess(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpDisconnect
void gpDisconnect(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpSetInfosA
s32 gpSetInfosA(GPConnection *h, s32 a, char *b);
#endif
#ifndef PROTO_LOCAL_gpSendBuddyRequestA
s32 gpSendBuddyRequestA(GPConnection *h, s32 v, const char *s);
#endif
#ifndef PROTO_LOCAL_gpAuthBuddyRequest
s32 gpAuthBuddyRequest(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpDenyBuddyRequest
s32 gpDenyBuddyRequest(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpGetNumBuddies
s32 gpGetNumBuddies(GPConnection *h, s32 *out);
#endif
#ifndef PROTO_LOCAL_gpGetBuddyStatus
s32 gpGetBuddyStatus(GPConnection *h, s32 idx, GPBuddyStatus *out);
#endif
#ifndef PROTO_LOCAL_gpGetBuddyIndex
s32 gpGetBuddyIndex(GPConnection *h, s32 a, s32 *out);
#endif
#ifndef PROTO_LOCAL_gpIsBuddy
s32 gpIsBuddy(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpDeleteBuddy
s32 gpDeleteBuddy(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpSetStatusA
s32 gpSetStatusA(GPConnection *h, s32 v, const char *s1, const char *s2);
#endif
#ifndef PROTO_LOCAL_gpSendBuddyMessageA
s32 gpSendBuddyMessageA(GPConnection *h, s32 a, const char *b);
#endif
#ifndef PROTO_LOCAL_Unk_ov065_0227bd20_pool_order
__declspec(weak) void Unk_ov065_0227bd20_pool_order(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpSetCallback
s32 gpSetCallback(GPConnection *h, s32 i, GPCallback x, void *y);
#endif
}
#endif

#endif

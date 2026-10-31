#ifndef PROTO_PROTO_OV065_UNK_OV065_0228176C_H
#define PROTO_PROTO_OV065_UNK_OV065_0228176C_H


#include "types.h"
#include "net/gp.h"
#ifdef __cplusplus
#include "net/gpiOperation.h"
#include "net/gpiProfile.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gpiGetProfile
s32 gpiGetProfile(GPConnection *h, s32 a, void *out);
#endif
#ifndef PROTO_LOCAL_gpiRemoveProfileByID
void gpiRemoveProfileByID(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpiRemoveProfile
s32 gpiRemoveProfile(GPConnection *h, void *n);
#endif
#ifndef PROTO_LOCAL_gpiFindBuddy
void *gpiFindBuddy(GPConnection *h, s32 a);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiProcessNewProfile
s32 gpiProcessNewProfile(GPConnection *h, GPIOperation *n, char *s);
#endif
#ifndef PROTO_LOCAL_gpiProfileListAdd
GPIProfile *gpiProfileListAdd(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpiCheckProfileForUser
s32 gpiCheckProfileForUser(GPConnection *, GPIProfile *n, void *arg);
#endif
#ifndef PROTO_LOCAL_gpiFindProfileByUser
s32 gpiFindProfileByUser(GPConnection *h, char *a, char *b, GPIProfile **out);
#endif
#ifndef PROTO_LOCAL_gpiProfileMapCallback
s32 gpiProfileMapCallback(GPIProfile *n, void *p);
#endif
#ifndef PROTO_LOCAL_gpiCheckForBuddy
s32 gpiCheckForBuddy(GPConnection *, GPIProfile *n, void *arg);
#endif
#ifndef PROTO_LOCAL_gpiCanFreeProfile
s32 gpiCanFreeProfile(GPIProfile *e);
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV065_UNK_OV065_0227E160_H
#define PROTO_PROTO_OV065_UNK_OV065_0227E160_H


#include "types.h"
#ifdef __cplusplus
#include "net/gp.h"
#include "net/gpiCallback.h"
#include "net/gpiOperation.h"
#include "net/gpiProfile.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_0228d1a4
extern char data_ov065_0228d1a4[0x40];
#endif
#ifndef PROTO_LOCAL_randomString
void randomString(char *buf, s32 n);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiStartConnect
s32 gpiStartConnect(GPConnection *h, GPIOperation *n);
#endif
#ifndef PROTO_LOCAL_gpiConnect
s32 gpiConnect(GPConnection *h, const char *a1, const char *a2, const char *a3, const char *a4, const char *a5, const char *a6, const char *a7, s32 mode, s32 a9, s32 a10, GPCallback a11, void *a12);
#endif
#ifndef PROTO_LOCAL_gpiSendLogin
s32 gpiSendLogin(GPConnection *h, GPIConnectData *req);
#endif
#ifndef PROTO_LOCAL_gpiSendNewuser
s32 gpiSendNewuser(GPConnection *h, GPIConnectData *req);
#endif
#ifndef PROTO_LOCAL_gpiProcessConnect
s32 gpiProcessConnect(GPConnection *h, GPIOperation *n, char *line);
#endif
#ifndef PROTO_LOCAL_gpiCheckConnect
s32 gpiCheckConnect(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpiDisconnectCleanupProfile
s32 gpiDisconnectCleanupProfile(GPConnection *h, GPIProfile *n);
#endif
#ifndef PROTO_LOCAL_gpiDisconnect
void gpiDisconnect(GPConnection *h, s32 a);
#endif
#ifndef PROTO_LOCAL_gpiCallErrorCallback
void gpiCallErrorCallback(GPConnection *h, s32 a, s32 b);
#endif
}
#endif

#endif

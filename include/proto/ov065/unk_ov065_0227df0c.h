#ifndef PROTO_PROTO_OV065_UNK_OV065_0227DF0C_H
#define PROTO_PROTO_OV065_UNK_OV065_0227DF0C_H


#include "types.h"
#include "net/gp.h"
#ifdef __cplusplus
#include "net/gpiCallback.h"
#include "net/gpiOperation.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gpiProcessCallbacks
s32 gpiProcessCallbacks(GPConnection *h, s32 key);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiAddCallback
s32 gpiAddCallback(GPConnection *h, GPICallbackCopy p, void *m, GPIOperation *g, s32 k);
#endif
#ifndef PROTO_LOCAL_gpiCallCallback
s32 gpiCallCallback(GPConnection *h, GPICallbackData *n);
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV065_UNK_OV065_02280740_H
#define PROTO_PROTO_OV065_UNK_OV065_02280740_H


#include "types.h"
#include "net/gp.h"
#ifdef __cplusplus
#include "net/gpiCallback.h"
#include "net/gpiOperation.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_gpiOperationsAreBlocking
s32 gpiOperationsAreBlocking(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpiIsValidDate
s32 gpiIsValidDate(s32 day, s32 mon, s32 year);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiFailedOpCallback
s32 gpiFailedOpCallback(void *h, GPIOperation *n);
#endif
#ifndef PROTO_LOCAL_gpiAddOperation
s32 gpiAddOperation(GPConnection *h, s32 a, void *b, GPIOperation **out, s32 e, GPCallback f, void *g);
#endif
#ifndef PROTO_LOCAL_gpiDestroyOperation
void gpiDestroyOperation(GPConnection *h, GPIOperation *n);
#endif
#ifndef PROTO_LOCAL_gpiRemoveOperation
void gpiRemoveOperation(GPConnection *h, GPIOperation *n);
#endif
#ifndef PROTO_LOCAL_gpiFindOperationByID
s32 gpiFindOperationByID(GPConnection *h, GPIOperation **out, s32 id);
#endif
#ifndef PROTO_LOCAL_gpiProcessOperation
s32 gpiProcessOperation(void *h, GPIOperation *n, char *x);
#endif
}
#endif

#endif

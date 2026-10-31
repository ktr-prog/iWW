#ifndef PROTO_PROTO_OV003_UNK_OV003_0222E5E0_H
#define PROTO_PROTO_OV003_UNK_OV003_0222E5E0_H


#include "types.h"
struct InsectNetSyncRec;
#ifndef __cplusplus
typedef struct InsectNetSyncRec InsectNetSyncRec;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_InsectNetSync_Set
BOOL InsectNetSync_Set(void *unused, s32 idx, s32 v, s32 *p, u8 e, s32 f);
#endif
#ifndef PROTO_LOCAL_InsectNetSync_PackVar
void InsectNetSync_PackVar(void *dst, s32 idx);
#endif
#ifndef PROTO_LOCAL_InsectNetSync_Get
BOOL InsectNetSync_Get(void *a, s32 b, s8 *c, s32 *d, s32 *e, u8 *f);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sInsectNetSync
extern InsectNetSyncRec sInsectNetSync[8];
#endif
#endif

#endif

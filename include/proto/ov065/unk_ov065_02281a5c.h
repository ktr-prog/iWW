#ifndef PROTO_PROTO_OV065_UNK_OV065_02281A5C_H
#define PROTO_PROTO_OV065_UNK_OV065_02281A5C_H


#include "types.h"
#ifdef __cplusplus
#include "net/gp.h"
#include "net/gpiCallback.h"
#include "net/gpiOperation.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_0228dadc
extern char data_ov065_0228dadc[0x40];
#endif
#ifndef PROTO_LOCAL_gpiStartProfileSearch
s32 gpiStartProfileSearch(void *h0, void *o0);
#endif
#ifndef PROTO_LOCAL_gpiInitSearchData
s32 gpiInitSearchData(void *h0, void *out, s32 p2);
#endif
#ifndef PROTO_LOCAL_gpiProfilesTableHash
s32 gpiProfilesTableHash(void *elem, s32 n);
#endif
#ifndef PROTO_LOCAL_gpiProfilesTableCompare
s32 gpiProfilesTableCompare(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_gpiProfilesTableFree
void gpiProfilesTableFree(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gpiStartSearch
s32 gpiStartSearch(void *h0, void *cn, s32 p2, GPCallback p3, void *p4);
#endif
#ifndef PROTO_LOCAL_gpiProfileSearch
s32 gpiProfileSearch(GPConnection *h, char *a, char *b, char *c, char *d, char *e, s32 f, s32 g, s32 p8, GPCallback p9, void *p10);
#endif
#ifndef PROTO_LOCAL_gpiProcessSearch
s32 gpiProcessSearch(GPConnection *h, GPIOperation *node);
#endif
#ifndef PROTO_LOCAL_gpiProcessSearches
s32 gpiProcessSearches(GPConnection *h);
#endif
#ifndef PROTO_LOCAL_gpiInitProfiles
s32 gpiInitProfiles(GPConnection *h);
#endif
}
#endif

#endif

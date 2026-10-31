#ifndef PROTO_PROTO_OV065_UNK_OV065_02285778_H
#define PROTO_PROTO_OV065_UNK_OV065_02285778_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov065_02291504
extern s32 data_ov065_02291504;
#endif
#ifndef PROTO_LOCAL_data_ov065_02291508
extern char data_ov065_02291508[0x2c];
#endif
#ifndef PROTO_LOCAL_gt2AddressToString
char *gt2AddressToString(u32 ip, u16 port, char *buf);
#endif
#ifndef PROTO_LOCAL_gt2StringToAddress
BOOL gt2StringToAddress(char *s, u32 *pip, u16 *pport);
#endif
#ifndef PROTO_LOCAL_gti2MessageCheck
void gti2MessageCheck(u8 **s, s32 *len);
#endif
#ifndef PROTO_LOCAL_gti2CreateConnectionObject
void *gti2CreateConnectionObject();
#endif
#ifndef PROTO_LOCAL_gti2UShortFromBuffer
u32 gti2UShortFromBuffer(u8 *buf, s32 off);
#endif
#ifndef PROTO_LOCAL_gti2UShortToBuffer
void gti2UShortToBuffer(u8 *buf, s32 off, s32 v);
#endif
#ifndef PROTO_LOCAL_gti2SNDiff
s16 gti2SNDiff(u32 a, u32 b);
#endif
#ifdef __cplusplus
}
#endif

#endif

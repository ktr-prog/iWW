#ifndef PROTO_PROTO_ITCM_UNK_01FF8AD4_H
#define PROTO_PROTO_ITCM_UNK_01FF8AD4_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_NNS_G3dGeWaitSendDL
void NNS_G3dGeWaitSendDL(void);
#endif
#ifndef PROTO_LOCAL_NNS_G3dGeSendDL
void NNS_G3dGeSendDL(const void *src, u32 szByte);
#endif
#ifndef PROTO_LOCAL_NNS_G3dGeFlushBuffer
void NNS_G3dGeFlushBuffer(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

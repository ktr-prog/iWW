#ifndef PROTO_PROTO_ITCM_UNK_01FF9E10_H
#define PROTO_PROTO_ITCM_UNK_01FF9E10_H


#include "types.h"
#include "uptr.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MIi_FIFOCallback
void MIi_FIFOCallback(void);
#endif
#ifndef PROTO_LOCAL_MIi_DmaSetParams
void MIi_DmaSetParams(u32 dmaNo, uptr src, uptr dest, u32 ctrl);
#endif
#ifndef PROTO_LOCAL_MIi_DMACallback
void MIi_DMACallback(void *arg);
#endif
#ifndef PROTO_LOCAL_MIi_CheckDma0SourceAddress
void MIi_CheckDma0SourceAddress(u32 dmaNo, uptr src, u32 size, u32 dir);
#endif
#ifndef PROTO_LOCAL_MI_WaitDma
void MI_WaitDma(u32 dmaNo);
#endif
#ifndef PROTO_LOCAL_MI_SendGXCommandAsync
void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 commandLength, void (*callback)(void *), void *arg);
#endif
#ifndef PROTO_LOCAL_AlarmCallback__stream
void AlarmCallback__stream(void *p);
#endif
#ifdef __cplusplus
}
#endif

#endif

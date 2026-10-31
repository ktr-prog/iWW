#ifndef PROTO_PROTO_ITCM_UNK_01FFA4A0_H
#define PROTO_PROTO_ITCM_UNK_01FFA4A0_H


#include "types.h"
#include "types64.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OS_GetTick
u64 OS_GetTick(void);
#endif
#ifndef PROTO_LOCAL_PXIi_HandlerRecvFifoNotEmpty
void PXIi_HandlerRecvFifoNotEmpty(void);
#endif
#ifndef PROTO_LOCAL_OSi_IdleThreadProc
void OSi_IdleThreadProc(void);
#endif
#ifndef PROTO_LOCAL_OSi_EnterDmaCallback
void OSi_EnterDmaCallback(u32 dmaNo, void (*callback)(void *), void *arg);
#endif
#ifdef __cplusplus
}
#endif

#endif

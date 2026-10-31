#ifndef PROTO_PROTO_ITCM_UNK_01FFD784_H
#define PROTO_PROTO_ITCM_UNK_01FFD784_H


#include "types.h"
#include "uptr.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MIi_DmaSetParams_wait
void MIi_DmaSetParams_wait(u32 dmaNo, uptr src, uptr dest, u32 ctrl);
#endif
#ifndef PROTO_LOCAL_MIi_DmaSetParams_noInt
void MIi_DmaSetParams_noInt(u32 dmaNo, uptr src, uptr dest, u32 ctrl);
#endif
#ifndef PROTO_LOCAL_MIi_DmaSetParams_wait_noInt
void MIi_DmaSetParams_wait_noInt(u32 dmaNo, uptr src, uptr dest, u32 ctrl);
#endif
#ifndef PROTO_LOCAL_OSi_DoResetSystem
void OSi_DoResetSystem(void);
#endif
#ifndef PROTO_LOCAL_OSi_ReloadRomData
void OSi_ReloadRomData(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

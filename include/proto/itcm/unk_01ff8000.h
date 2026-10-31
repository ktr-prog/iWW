#ifndef PROTO_PROTO_ITCM_UNK_01FF8000_H
#define PROTO_PROTO_ITCM_UNK_01FF8000_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OS_IrqDummy
void OS_IrqDummy(void);
#endif
#ifndef PROTO_LOCAL_OS_EnableIrqMask
u32 OS_EnableIrqMask(u32 intr);
#endif
#ifndef PROTO_LOCAL_OS_DisableIrqMask
u32 OS_DisableIrqMask(u32 intr);
#endif
#ifdef __cplusplus
}
#endif

#endif

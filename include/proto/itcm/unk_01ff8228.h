#ifndef PROTO_PROTO_ITCM_UNK_01FF8228_H
#define PROTO_PROTO_ITCM_UNK_01FF8228_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_simpleUnlock_
void simpleUnlock_(void *arg);
#endif
#ifndef PROTO_LOCAL_OSi_IrqTimer3
void OSi_IrqTimer3(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqTimer2
void OSi_IrqTimer2(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqTimer1
void OSi_IrqTimer1(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqTimer0
void OSi_IrqTimer0(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqDma3
void OSi_IrqDma3(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqDma2
void OSi_IrqDma2(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqDma1
void OSi_IrqDma1(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqDma0
void OSi_IrqDma0(void);
#endif
#ifndef PROTO_LOCAL_OSi_IrqCallback
void OSi_IrqCallback(int index);
#endif
#ifndef PROTO_LOCAL_OS_SetIrqMask
u32 OS_SetIrqMask(u32 intr);
#endif
#ifdef __cplusplus
}
#endif

#endif

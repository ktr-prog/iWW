#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02112458_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02112458_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OS_InitLock
void OS_InitLock(void);
#endif
#ifndef PROTO_LOCAL_OSi_AllocateCartridgeBus
void OSi_AllocateCartridgeBus(void);
#endif
#ifndef PROTO_LOCAL_OSi_FreeCartridgeBus
void OSi_FreeCartridgeBus(void);
#endif
#ifndef PROTO_LOCAL_OSi_AllocateCardBus
void OSi_AllocateCardBus(void);
#endif
#ifndef PROTO_LOCAL_OSi_FreeCardBus
void OSi_FreeCardBus(void);
#endif
#ifndef PROTO_LOCAL_OSi_WaitByLoop
void OSi_WaitByLoop(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

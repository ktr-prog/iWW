#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02114410_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02114410_H


#include "types.h"
#include "sys/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OS_InitMutex
void OS_InitMutex(OSMutex *mutex);
#endif
#ifndef PROTO_LOCAL_OS_LockMutex
void OS_LockMutex(OSMutex *mutex);
#endif
#ifndef PROTO_LOCAL_OS_UnlockMutex
void OS_UnlockMutex(OSMutex *mutex);
#endif
#ifdef __cplusplus
}
#endif

#endif

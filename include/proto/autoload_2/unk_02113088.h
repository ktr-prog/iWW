#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02113088_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02113088_H


#include "types.h"
#include "sys/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OS_ExitThread
void OS_ExitThread(void);
#endif
#ifndef PROTO_LOCAL_OSi_ExitThread
void OSi_ExitThread(void *arg);
#endif
#ifndef PROTO_LOCAL_OSi_ExitThread_Destroy
void OSi_ExitThread_Destroy(void);
#endif
#ifndef PROTO_LOCAL_OS_SleepThread
void OS_SleepThread(OSThreadQueue *q);
#endif
#ifndef PROTO_LOCAL_OS_WakeupThread
void OS_WakeupThread(OSThreadQueue *q);
#endif
#ifndef PROTO_LOCAL_OSi_RescheduleThread
void OSi_RescheduleThread(void);
#endif
#ifndef PROTO_LOCAL_OS_YieldThread
void OS_YieldThread(void);
#endif
#ifndef PROTO_LOCAL_OSi_SleepAlarmCallback
void OSi_SleepAlarmCallback(void *arg);
#endif
#ifdef __cplusplus
}
#endif

#endif

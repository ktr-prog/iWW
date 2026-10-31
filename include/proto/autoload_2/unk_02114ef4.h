#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_02114EF4_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_02114EF4_H


#include "types.h"
#include "nitro/os_alarm.h"
#include "types64.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_OSi_SetTimer
void OSi_SetTimer(OSAlarm *alarm);
#endif
#ifndef PROTO_LOCAL_OS_InitAlarm
void OS_InitAlarm(void);
#endif
#ifndef PROTO_LOCAL_OS_CreateAlarm
void OS_CreateAlarm(OSAlarm *alarm);
#endif
#ifndef PROTO_LOCAL_OSi_InsertAlarm
void OSi_InsertAlarm(OSAlarm *alarm, u64 fire);
#endif
#ifndef PROTO_LOCAL_OS_SetAlarm
void OS_SetAlarm(OSAlarm *alarm, u64 tick, void (*handler)(void *), void *arg);
#endif
#ifndef PROTO_LOCAL_OS_CancelAlarm
void OS_CancelAlarm(OSAlarm *alarm);
#endif
#ifndef PROTO_LOCAL_OSi_ArrangeTimer
void OSi_ArrangeTimer(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

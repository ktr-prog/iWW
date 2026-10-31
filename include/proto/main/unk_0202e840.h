#ifndef PROTO_PROTO_MAIN_UNK_0202E840_H
#define PROTO_PROTO_MAIN_UNK_0202E840_H


#include "types.h"
#ifdef __cplusplus
#include "sys/ProcBase.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_LowBattery_Poll
BOOL LowBattery_Poll();
#endif
#ifndef PROTO_LOCAL_LowBattery_SetWarned
void LowBattery_SetWarned();
#endif
#ifndef PROTO_LOCAL_LowBattery_Reset
void LowBattery_Reset();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_GameProc_CreateChild
ProcBase *GameProc_CreateChild(u32 a, void *parent, u32 c, u32 d);
#endif
#ifndef PROTO_LOCAL_GameProc_CreateRoot
ProcBase *GameProc_CreateRoot(u32 a, u32 b, u32 c);
#endif
}
#ifndef PROTO_LOCAL_sLowBatteryWarned
extern u8 sLowBatteryWarned;
#endif
#ifndef PROTO_LOCAL_sLowBatteryPollTimer
extern s32 sLowBatteryPollTimer;
#endif
#endif

#endif

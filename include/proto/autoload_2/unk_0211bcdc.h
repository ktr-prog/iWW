#ifndef PROTO_PROTO_AUTOLOAD_2_UNK_0211BCDC_H
#define PROTO_PROTO_AUTOLOAD_2_UNK_0211BCDC_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PMi_ReadRegister
u32 PMi_ReadRegister(u32 type, u16 *out);
#endif
#ifndef PROTO_LOCAL_PMi_SetLED
u32 PMi_SetLED(u32 a);
#endif
#ifndef PROTO_LOCAL_PM_SetBackLight
u32 PM_SetBackLight(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PM_ForceToPowerOff
u32 PM_ForceToPowerOff(void);
#endif
#ifndef PROTO_LOCAL_PM_GetBattery
u32 PM_GetBattery(u32 *p);
#endif
#ifndef PROTO_LOCAL_PM_GetBackLight
u32 PM_GetBackLight(u32 *p1, u32 *p2);
#endif
#ifndef PROTO_LOCAL_PMi_SendPxiData
void PMi_SendPxiData(u32 data);
#endif
#ifndef PROTO_LOCAL_PMi_SetLCDPower
u32 PMi_SetLCDPower(u32 mode, u32 target, u32 noWait, u32 sync);
#endif
#ifndef PROTO_LOCAL_PM_SetLCDPower
u32 PM_SetLCDPower(u32 a);
#endif
#ifndef PROTO_LOCAL_PMi_SendLEDPatternCommand
u32 PMi_SendLEDPatternCommand(u32 a);
#endif
#ifndef PROTO_LOCAL_PM_GetLEDPattern
u32 PM_GetLEDPattern(u32 *out);
#endif
#ifndef PROTO_LOCAL_TPi_TpCallback
void TPi_TpCallback(u32 tag, u32 data, u32 err);
#endif
#ifndef PROTO_LOCAL_TP_Init
void TP_Init(void);
#endif
#ifdef __cplusplus
}
#endif

#endif

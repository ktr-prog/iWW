#ifndef PROTO_PROTO_OV065_UNK_OV065_0226ACA8_H
#define PROTO_PROTO_OV065_UNK_OV065_0226ACA8_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWifiRssiCount
extern volatile u8 sWifiRssiCount[4];
#endif
#ifndef PROTO_LOCAL_sWifiRssiSamples
extern u8 sWifiRssiSamples[16];
#endif
#ifndef PROTO_LOCAL_WifiLink_GetAverageRssi
u8 WifiLink_GetAverageRssi();
#endif
#ifndef PROTO_LOCAL_WifiLink_GetLinkLevel
u32 WifiLink_GetLinkLevel();
#endif
#ifndef PROTO_LOCAL_WifiLink_AddRssiSample
void WifiLink_AddRssiSample(s32 v);
#endif
#ifdef __cplusplus
}
#endif

#endif

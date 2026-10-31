#ifndef PROTO_PROTO_OV001_UNK_OV001_0221F6A0_H
#define PROTO_PROTO_OV001_UNK_OV001_0221F6A0_H


#include "types.h"
#include "nitro/wm.h"
struct WfcUsbScanWork;
#ifndef __cplusplus
typedef struct WfcUsbScanWork WfcUsbScanWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_Start
s32 WfcUsbScan_Start(void (*cb)(s32));
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_StartScan
s32 WfcUsbScan_StartScan();
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_Stop
s32 WfcUsbScan_Stop();
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_SetCallback
void WfcUsbScan_SetCallback(void (*cb)(s32));
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_WmCallback
void WfcUsbScan_WmCallback(WMMsg *msg);
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_CollectAps
void WfcUsbScan_CollectAps(WMStartScanExCallback *a);
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_CheckGranted
void WfcUsbScan_CheckGranted(WMStartScanExCallback *a);
#endif
#ifndef PROTO_LOCAL_WfcUsbScan_TimeoutTask
void WfcUsbScan_TimeoutTask(void *task, void *work);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcUsbScan
extern WfcUsbScanWork *sWfcUsbScan;
#endif
}
#endif

#endif

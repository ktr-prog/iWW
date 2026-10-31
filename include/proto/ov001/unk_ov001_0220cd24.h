#ifndef PROTO_PROTO_OV001_UNK_OV001_0220CD24_H
#define PROTO_PROTO_OV001_UNK_OV001_0220CD24_H


#include "types.h"
#include "net/WfcMoveParams.h"
#include "net/WfcTransfer.h"
struct WfcTransferWork;
#ifndef __cplusplus
typedef struct WfcTransferWork WfcTransferWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aa60
extern char data_ov001_0222aa60[0x14];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aa8c
extern char data_ov001_0222aa8c[0x18];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aa74
extern char data_ov001_0222aa74[0x18];
#endif
#ifndef PROTO_LOCAL_WfcTransfer_Start
void WfcTransfer_Start(WfcTransferCallback a);
#endif
#ifndef PROTO_LOCAL_WfcTransfer_RequestEnd
void WfcTransfer_RequestEnd();
#endif
#ifndef PROTO_LOCAL_WfcTransfer_EndTask
void WfcTransfer_EndTask(void *task);
#endif
#ifndef PROTO_LOCAL_WfcTransfer_IsFinished
BOOL WfcTransfer_IsFinished();
#endif
#ifndef PROTO_LOCAL_WfcTransfer_SetCallback
void WfcTransfer_SetCallback(WfcTransferCallback f);
#endif
#ifndef PROTO_LOCAL_WfcTransfer_StartSend
void WfcTransfer_StartSend();
#endif
#ifndef PROTO_LOCAL_WfcTransfer_GetChildUser
u8 *WfcTransfer_GetChildUser();
#endif
#ifndef PROTO_LOCAL_WfcTransfer_Task
void WfcTransfer_Task(void *task);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_data_ov001_0222aaa4
extern WfcMoveParams data_ov001_0222aaa4;
#endif
}
#ifndef PROTO_LOCAL_sWfcTransfer
extern WfcTransferWork *sWfcTransfer;
#endif
#endif

#endif

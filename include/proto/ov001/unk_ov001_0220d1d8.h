#ifndef PROTO_PROTO_OV001_UNK_OV001_0220D1D8_H
#define PROTO_PROTO_OV001_UNK_OV001_0220D1D8_H


#include "types.h"
#include "net/SimpleStart.h"
struct WfcMsgBank;
#ifndef __cplusplus
typedef struct WfcMsgBank WfcMsgBank;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov001_0222ab10
extern char data_ov001_0222ab10[16];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aae0
extern char data_ov001_0222aae0[16];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aaf0
extern char data_ov001_0222aaf0[16];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aac0
extern char data_ov001_0222aac0[16];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aad0
extern char data_ov001_0222aad0[16];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222ab00
extern char data_ov001_0222ab00[16];
#endif
#ifndef PROTO_LOCAL_sWfcMsgFileNames
extern void *sWfcMsgFileNames[6];
#endif
#ifndef PROTO_LOCAL_sWfcSimpleStartStatus
extern SimpleStartStatus *sWfcSimpleStartStatus;
#endif
#ifndef PROTO_LOCAL_WfcBoot_Enter
void WfcBoot_Enter();
#endif
#ifndef PROTO_LOCAL_WfcBoot_FadeIn
void WfcBoot_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcBoot_Dispatch
void WfcBoot_Dispatch();
#endif
#ifndef PROTO_LOCAL_WfcUtil_QuitFadeOut
void WfcUtil_QuitFadeOut();
#endif
#ifndef PROTO_LOCAL_WfcUtil_Quit
void WfcUtil_Quit();
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_Begin
void WfcSimpleStart_Begin();
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_End
void WfcSimpleStart_End();
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_GetState
s32 WfcSimpleStart_GetState();
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_ApplyResult
void WfcSimpleStart_ApplyResult();
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_StatusCallback
void WfcSimpleStart_StatusCallback(SimpleStartStatus *p);
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_Alloc
void *WfcSimpleStart_Alloc(u32 a);
#endif
#ifndef PROTO_LOCAL_WfcSimpleStart_Free
void WfcSimpleStart_Free(void *p);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_gWfcMsgBank
extern WfcMsgBank *gWfcMsgBank;
#endif
}
#endif

#endif

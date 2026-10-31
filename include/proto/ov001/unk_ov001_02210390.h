#ifndef PROTO_PROTO_OV001_UNK_OV001_02210390_H
#define PROTO_PROTO_OV001_UNK_OV001_02210390_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTransferFailedTopShown
extern u8 sWfcTransferFailedTopShown;
#endif
#ifndef PROTO_LOCAL_sWfcTransferFailedRetry
extern u8 sWfcTransferFailedRetry;
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_Enter
void WfcTransferFailed_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_LoadBg
void WfcTransferFailed_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_FadeIn
void WfcTransferFailed_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_WaitFadeIn
void WfcTransferFailed_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_WaitButtonBar
void WfcTransferFailed_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_Update
void WfcTransferFailed_Update();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_HandleInput
void WfcTransferFailed_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_Idle
void WfcTransferFailed_Idle();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_HandleResult
void WfcTransferFailed_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_StartExit
void WfcTransferFailed_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_FadeOut
void WfcTransferFailed_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcTransferFailed_Exit
void WfcTransferFailed_Exit();
#endif
#ifdef __cplusplus
}
#endif

#endif

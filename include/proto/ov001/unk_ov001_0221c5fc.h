#ifndef PROTO_PROTO_OV001_UNK_OV001_0221C5FC_H
#define PROTO_PROTO_OV001_UNK_OV001_0221C5FC_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcUsbWaitResult
extern u8 sWfcUsbWaitResult;
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_IsLidClosed
s32 WfcUsbWait_IsLidClosed();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_Enter
void WfcUsbWait_Enter();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_LoadBg
void WfcUsbWait_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_FadeIn
void WfcUsbWait_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_WaitFadeIn
void WfcUsbWait_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_WaitButtonBar
void WfcUsbWait_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_Update
void WfcUsbWait_Update();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_HandleInput
void WfcUsbWait_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_Idle
void WfcUsbWait_Idle();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_HandleResult
void WfcUsbWait_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_StartExit
void WfcUsbWait_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_FadeOut
void WfcUsbWait_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_Exit
void WfcUsbWait_Exit();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_OnScanResult
void WfcUsbWait_OnScanResult(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_NotFoundDialog
void WfcUsbWait_NotFoundDialog();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_WaitNotFoundClosed
void WfcUsbWait_WaitNotFoundClosed();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_GrantedDialog
void WfcUsbWait_GrantedDialog();
#endif
#ifndef PROTO_LOCAL_WfcUsbWait_WaitGrantedClosed
void WfcUsbWait_WaitGrantedClosed();
#endif
#ifdef __cplusplus
}
#endif

#endif

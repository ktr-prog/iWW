#ifndef PROTO_PROTO_OV001_UNK_OV001_022111C8_H
#define PROTO_PROTO_OV001_UNK_OV001_022111C8_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcAossSetupSucceeded
extern volatile u8 sWfcAossSetupSucceeded;
#endif
#ifndef PROTO_LOCAL_sWfcAossSetupTimer
extern volatile u16 sWfcAossSetupTimer;
#endif
#ifndef PROTO_LOCAL_sWfcAossSetupUiTask
extern void *sWfcAossSetupUiTask;
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_IsLidClosed
BOOL WfcAossSetup_IsLidClosed();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_Enter
void WfcAossSetup_Enter();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_LoadBg
void WfcAossSetup_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_FadeIn
void WfcAossSetup_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_WaitFadeIn
void WfcAossSetup_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_StartAoss
void WfcAossSetup_StartAoss();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_RunAoss
void WfcAossSetup_RunAoss();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_HandleInput
void WfcAossSetup_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_Idle
void WfcAossSetup_Idle();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_HandleResult
void WfcAossSetup_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_StartExit
void WfcAossSetup_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_FadeOut
void WfcAossSetup_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_Exit
void WfcAossSetup_Exit();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_UiTask
void WfcAossSetup_UiTask();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_WaitErrorDialog
void WfcAossSetup_WaitErrorDialog();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_WaitDialogClosed
void WfcAossSetup_WaitDialogClosed();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_WaitAfterSuccess
void WfcAossSetup_WaitAfterSuccess();
#endif
#ifndef PROTO_LOCAL_WfcAossSetup_Cancel
void WfcAossSetup_Cancel();
#endif
#ifdef __cplusplus
}
#endif

#endif

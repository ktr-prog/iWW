#ifndef PROTO_PROTO_OV001_UNK_OV001_02210CC0_H
#define PROTO_PROTO_OV001_UNK_OV001_02210CC0_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTransferWaitResult
extern u8 sWfcTransferWaitResult;
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_IsLidClosed
BOOL WfcTransferWait_IsLidClosed();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_Enter
void WfcTransferWait_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_LoadBg
void WfcTransferWait_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_FadeIn
void WfcTransferWait_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_WaitFadeIn
void WfcTransferWait_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_WaitButtonBar
void WfcTransferWait_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_Update
void WfcTransferWait_Update();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_HandleInput
void WfcTransferWait_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_Idle
void WfcTransferWait_Idle();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_HandleResult
void WfcTransferWait_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_StartExit
void WfcTransferWait_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_FadeOut
void WfcTransferWait_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_Exit
void WfcTransferWait_Exit();
#endif
#ifndef PROTO_LOCAL_WfcTransferWait_OnTransferEvent
void WfcTransferWait_OnTransferEvent(u32 a);
#endif
#ifdef __cplusplus
}
#endif

#endif

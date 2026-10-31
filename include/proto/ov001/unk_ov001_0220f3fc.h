#ifndef PROTO_PROTO_OV001_UNK_OV001_0220F3FC_H
#define PROTO_PROTO_OV001_UNK_OV001_0220F3FC_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTransferSendResult
extern u8 sWfcTransferSendResult;
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_Enter
void WfcTransferDone_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_SetupBg
void WfcTransferDone_SetupBg();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_FadeIn
void WfcTransferDone_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_WaitFadeIn
void WfcTransferDone_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_WaitButtonBar
void WfcTransferDone_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_Update
void WfcTransferDone_Update();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_HandleInput
void WfcTransferDone_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_Idle
void WfcTransferDone_Idle();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_HandleResult
void WfcTransferDone_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_StartExit
void WfcTransferDone_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_FadeOut
void WfcTransferDone_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcTransferDone_PowerOff
void WfcTransferDone_PowerOff();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_Enter
void WfcTransferSend_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_LoadBg
void WfcTransferSend_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_FadeIn
void WfcTransferSend_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_WaitFadeIn
void WfcTransferSend_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_Update
void WfcTransferSend_Update();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_Nop1
void WfcTransferSend_Nop1();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_Nop2
void WfcTransferSend_Nop2();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_FadeOut
void WfcTransferSend_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_Exit
void WfcTransferSend_Exit();
#endif
#ifndef PROTO_LOCAL_WfcTransferSend_OnResult
void WfcTransferSend_OnResult(u32 a);
#endif
#ifdef __cplusplus
}
#endif

#endif

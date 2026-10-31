#ifndef PROTO_PROTO_OV001_UNK_OV001_0221962C_H
#define PROTO_PROTO_OV001_UNK_OV001_0221962C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcApSearchResult
extern u8 sWfcApSearchResult;
#endif
#ifndef PROTO_LOCAL_sWfcApSearchTimer
extern volatile u16 sWfcApSearchTimer;
#endif
#ifndef PROTO_LOCAL_WfcApSearch_Enter
void WfcApSearch_Enter();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_LoadBg
void WfcApSearch_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_FadeIn
void WfcApSearch_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_WaitFadeIn
void WfcApSearch_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_WaitButtonBar
void WfcApSearch_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_Update
void WfcApSearch_Update();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_CheckResults
void WfcApSearch_CheckResults();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_HandleInput
void WfcApSearch_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_Idle
void WfcApSearch_Idle();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_HandleResult
void WfcApSearch_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_StartExit
void WfcApSearch_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_FadeOut
void WfcApSearch_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_Exit
void WfcApSearch_Exit();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_ResultDialog
void WfcApSearch_ResultDialog();
#endif
#ifndef PROTO_LOCAL_WfcApSearch_WaitDialogClosed
void WfcApSearch_WaitDialogClosed();
#endif
#ifdef __cplusplus
}
#endif

#endif

#ifndef PROTO_PROTO_OV001_UNK_OV001_0220DE1C_H
#define PROTO_PROTO_OV001_UNK_OV001_0220DE1C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcEraseConfirmed
extern volatile u8 sWfcEraseConfirmed;
#endif
#ifndef PROTO_LOCAL_WfcErase_Enter
void WfcErase_Enter();
#endif
#ifndef PROTO_LOCAL_WfcErase_LoadBg
void WfcErase_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcErase_FadeIn
void WfcErase_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcErase_WaitFadeIn
void WfcErase_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcErase_WaitButtonBar
void WfcErase_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcErase_Update
void WfcErase_Update();
#endif
#ifndef PROTO_LOCAL_WfcErase_HandleInput
void WfcErase_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcErase_Idle
void WfcErase_Idle();
#endif
#ifndef PROTO_LOCAL_WfcErase_HandleResult
void WfcErase_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcErase_StartExit
void WfcErase_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcErase_FadeOut
void WfcErase_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcErase_Exit
void WfcErase_Exit();
#endif
#ifndef PROTO_LOCAL_WfcErase_WaitConfirmDialog
void WfcErase_WaitConfirmDialog();
#endif
#ifndef PROTO_LOCAL_WfcErase_WaitDialogClosed
void WfcErase_WaitDialogClosed();
#endif
#ifdef __cplusplus
}
#endif

#endif

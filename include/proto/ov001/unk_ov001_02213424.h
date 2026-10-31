#ifndef PROTO_PROTO_OV001_UNK_OV001_02213424_H
#define PROTO_PROTO_OV001_UNK_OV001_02213424_H


#include "types.h"
#ifdef __cplusplus
#include "ui/WfcTextEdit.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTextEditTitleMsgs
extern u8 sWfcTextEditTitleMsgs[4];
#endif
#ifndef PROTO_LOCAL_sWfcTextEditConfirmMsgs
extern u32 sWfcTextEditConfirmMsgs[2];
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_Enter
void WfcTextEdit_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_LoadBg
void WfcTextEdit_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_FadeIn
void WfcTextEdit_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_OpenKeyboard
void WfcTextEdit_OpenKeyboard();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_WaitKeyboard
void WfcTextEdit_WaitKeyboard();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_Update
void WfcTextEdit_Update();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_HandleKey
void WfcTextEdit_HandleKey();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_Idle
void WfcTextEdit_Idle();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_StartExit
void WfcTextEdit_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_CloseKeyboard
void WfcTextEdit_CloseKeyboard();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_WaitKeyboardClosed
void WfcTextEdit_WaitKeyboardClosed();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_Exit
void WfcTextEdit_Exit();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_DrawText
void WfcTextEdit_DrawText();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_UpdateCaret
void WfcTextEdit_UpdateCaret();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_WaitConfirmDialog
void WfcTextEdit_WaitConfirmDialog();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_ApplyAndExit
void WfcTextEdit_ApplyAndExit();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_ValidateInput
BOOL WfcTextEdit_ValidateInput();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_WaitErrorDialog
void WfcTextEdit_WaitErrorDialog();
#endif
#ifndef PROTO_LOCAL_WfcTextEdit_ReturnToInput
void WfcTextEdit_ReturnToInput();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcTextEdit
extern WfcTextEdit *sWfcTextEdit;
#endif
}
#endif

#endif

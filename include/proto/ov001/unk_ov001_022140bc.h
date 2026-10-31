#ifndef PROTO_PROTO_OV001_UNK_OV001_022140BC_H
#define PROTO_PROTO_OV001_UNK_OV001_022140BC_H


#include "types.h"
struct WfcAddrEdit;
#ifndef __cplusplus
typedef struct WfcAddrEdit WfcAddrEdit;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov001_0222af7c
extern u8 data_ov001_0222af7c[4];
#endif
#ifndef PROTO_LOCAL_sWfcAddrEditTitleMsgs
extern u8 sWfcAddrEditTitleMsgs[8];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222af88
extern u16 data_ov001_0222af88[4];
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_Enter
void WfcAddrEdit_Enter();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_LoadBg
void WfcAddrEdit_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_FadeIn
void WfcAddrEdit_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_OpenKeypad
void WfcAddrEdit_OpenKeypad();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_WaitKeypad
void WfcAddrEdit_WaitKeypad();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_Update
void WfcAddrEdit_Update();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_HandleKey
void WfcAddrEdit_HandleKey();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_IsOctetFull
s32 WfcAddrEdit_IsOctetFull(s32 n);
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_Idle
void WfcAddrEdit_Idle();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_StartExit
void WfcAddrEdit_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_CloseKeypad
void WfcAddrEdit_CloseKeypad();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_WaitKeypadClosed
void WfcAddrEdit_WaitKeypadClosed();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_Exit
void WfcAddrEdit_Exit();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_DrawText
void WfcAddrEdit_DrawText();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_UpdateCaret
void WfcAddrEdit_UpdateCaret();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_WaitConfirmDialog
void WfcAddrEdit_WaitConfirmDialog();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_ApplyAndExit
void WfcAddrEdit_ApplyAndExit();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_NormalizeOctets
void WfcAddrEdit_NormalizeOctets();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_ValidateAddress
s32 WfcAddrEdit_ValidateAddress();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_WaitErrorDialog
void WfcAddrEdit_WaitErrorDialog();
#endif
#ifndef PROTO_LOCAL_WfcAddrEdit_ReturnToInput
void WfcAddrEdit_ReturnToInput();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcAddrEdit
extern WfcAddrEdit *sWfcAddrEdit;
#endif
}
#endif

#endif

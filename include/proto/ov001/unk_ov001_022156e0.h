#ifndef PROTO_PROTO_OV001_UNK_OV001_022156E0_H
#define PROTO_PROTO_OV001_UNK_OV001_022156E0_H


#include "types.h"
struct WfcManualSetupWork;
#ifndef __cplusplus
typedef struct WfcManualSetupWork WfcManualSetupWork;
#endif
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcManualSetupToggleItems
extern u8 sWfcManualSetupToggleItems[4];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b050
extern u8 data_ov001_0222b050[14];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b060
extern char data_ov001_0222b060[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b078
extern char data_ov001_0222b078[];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b090
extern char data_ov001_0222b090[];
#endif
#ifndef PROTO_LOCAL_sWfcAddressFormat
extern u16 sWfcAddressFormat[16];
#endif
#ifndef PROTO_LOCAL_sWfcManualSetupCursorItem
extern u8 sWfcManualSetupCursorItem;
#endif
#ifndef PROTO_LOCAL_sWfcManualSetupMode
extern u8 sWfcManualSetupMode;
#endif
#ifndef PROTO_LOCAL_sWfcManualSetupCursorRow
extern u8 sWfcManualSetupCursorRow;
#endif
#ifndef PROTO_LOCAL_sWfcManualSetupScroll
extern u16 sWfcManualSetupScroll;
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_Enter
void WfcManualSetup_Enter();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_LoadBg
void WfcManualSetup_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_ResetCursor
void WfcManualSetup_ResetCursor();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_FadeIn
void WfcManualSetup_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_WaitFadeIn
void WfcManualSetup_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_Update
void WfcManualSetup_Update();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_HandleKeys
void WfcManualSetup_HandleKeys();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_HandleTouch
BOOL WfcManualSetup_HandleTouch();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_SelectItem
void WfcManualSetup_SelectItem(u32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_SetAutoIp
void WfcManualSetup_SetAutoIp(u32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_SetAutoDns
void WfcManualSetup_SetAutoDns(u32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_HandleScrollBar
void WfcManualSetup_HandleScrollBar();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_StartExit
void WfcManualSetup_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_FadeOut
void WfcManualSetup_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_Exit
void WfcManualSetup_Exit();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_Redraw
void WfcManualSetup_Redraw();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_DrawRowValue
void WfcManualSetup_DrawRowValue(s32 idx, s32 arg);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_DrawRowButtons
void WfcManualSetup_DrawRowButtons(s32 idx, s32 arg);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_IsItemEnabled
s32 WfcManualSetup_IsItemEnabled(s32 idx);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_SetRowButton
void WfcManualSetup_SetRowButton(s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_DrawString
void WfcManualSetup_DrawString(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_DrawAddress
void WfcManualSetup_DrawAddress(u8 *a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_PlaceObjs
void WfcManualSetup_PlaceObjs();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_HitTest
s32 WfcManualSetup_HitTest();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_GetScreenRow
s32 WfcManualSetup_GetScreenRow(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_GetListRow
s32 WfcManualSetup_GetListRow(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_ScrollUpTask
void WfcManualSetup_ScrollUpTask(void *task);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_ScrollDownTask
void WfcManualSetup_ScrollDownTask(void *task);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_ScrollBgTask
void WfcManualSetup_ScrollBgTask();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_DrawCursor
void WfcManualSetup_DrawCursor();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_UpdateCursorItem
void WfcManualSetup_UpdateCursorItem();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_SetCursor
void WfcManualSetup_SetCursor(u32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_MoveCursor
void WfcManualSetup_MoveCursor(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_HighlightButton
void WfcManualSetup_HighlightButton();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_ToggleFlashTask
void WfcManualSetup_ToggleFlashTask();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_FlashToggle
void WfcManualSetup_FlashToggle();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_ValidateSettings
BOOL WfcManualSetup_ValidateSettings();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_InvalidDialog
void WfcManualSetup_InvalidDialog();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_WaitDialogClosed
void WfcManualSetup_WaitDialogClosed();
#endif
#ifndef PROTO_LOCAL_WfcManualSetup_SetMode
void WfcManualSetup_SetMode(u32 v);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcManualSetup
extern WfcManualSetupWork *sWfcManualSetup;
#endif
}
#endif

#endif

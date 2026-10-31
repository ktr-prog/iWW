#ifndef PROTO_PROTO_OV001_UNK_OV001_02219C3C_H
#define PROTO_PROTO_OV001_UNK_OV001_02219C3C_H


#include "types.h"
#include "menu/WfcConnSelectWork.h"
#ifdef __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcConnSelectCursor
extern u8 sWfcConnSelectCursor;
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_Enter
void WfcConnSelect_Enter();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_LoadBg
void WfcConnSelect_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_CreateSlotButtons
void WfcConnSelect_CreateSlotButtons();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_FadeIn
void WfcConnSelect_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_WaitFadeIn
void WfcConnSelect_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_WaitButtonBar
void WfcConnSelect_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_Update
void WfcConnSelect_Update();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_HandleInput
void WfcConnSelect_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_Idle
void WfcConnSelect_Idle();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_HandleSelection
void WfcConnSelect_HandleSelection();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_StartExit
void WfcConnSelect_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_FadeOut
void WfcConnSelect_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_Exit
void WfcConnSelect_Exit();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_DrawCursor
void WfcConnSelect_DrawCursor();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_MoveCursor
void WfcConnSelect_MoveCursor(u32 a);
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_PressEraseButton
void WfcConnSelect_PressEraseButton();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_EraseDialog
void WfcConnSelect_EraseDialog();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_WaitDialogClosed
void WfcConnSelect_WaitDialogClosed();
#endif
#ifndef PROTO_LOCAL_WfcConnSelect_HighlightSelection
void WfcConnSelect_HighlightSelection();
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b244
extern u8 data_ov001_0222b244[4];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b240
extern u8 data_ov001_0222b240[4];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b260
extern char data_ov001_0222b260[22];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sWfcConnSelect
extern WfcConnSelectWork *sWfcConnSelect;
#endif
}
#endif

#endif

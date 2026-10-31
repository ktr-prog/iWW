#ifndef PROTO_PROTO_OV001_UNK_OV001_02211B2C_H
#define PROTO_PROTO_OV001_UNK_OV001_02211B2C_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov001_0222aea8
extern u8 data_ov001_0222aea8;
#endif
#ifndef PROTO_LOCAL_sWfcApListCursor
extern u8 sWfcApListCursor;
#endif
#ifndef PROTO_LOCAL_sWfcApListScroll
extern u16 sWfcApListScroll;
#endif
#ifndef PROTO_LOCAL_WfcApList_Enter
void WfcApList_Enter();
#endif
#ifndef PROTO_LOCAL_WfcApList_LoadBg
void WfcApList_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcApList_InitScrollBar
void WfcApList_InitScrollBar();
#endif
#ifndef PROTO_LOCAL_WfcApList_CreateRowIcons
void WfcApList_CreateRowIcons();
#endif
#ifndef PROTO_LOCAL_WfcApList_FadeIn
void WfcApList_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcApList_WaitFadeIn
void WfcApList_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcApList_WaitButtonBar
void WfcApList_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcApList_Update
void WfcApList_Update();
#endif
#ifndef PROTO_LOCAL_WfcApList_HandleInput
void WfcApList_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcApList_HandleScrollBar
void WfcApList_HandleScrollBar();
#endif
#ifndef PROTO_LOCAL_WfcApList_HandleResult
void WfcApList_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcApList_StartExit
void WfcApList_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcApList_FadeOut
void WfcApList_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcApList_Exit
void WfcApList_Exit();
#endif
#ifndef PROTO_LOCAL_WfcApList_Redraw
void WfcApList_Redraw();
#endif
#ifndef PROTO_LOCAL_WfcApList_DrawSsid
void WfcApList_DrawSsid(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcApList_SetRowIcons
void WfcApList_SetRowIcons(s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_WfcApList_LayoutRows
void WfcApList_LayoutRows();
#endif
#ifndef PROTO_LOCAL_WfcApList_ScrollUpTask
void WfcApList_ScrollUpTask(void *task);
#endif
#ifndef PROTO_LOCAL_WfcApList_ScrollDownTask
void WfcApList_ScrollDownTask(void *task);
#endif
#ifndef PROTO_LOCAL_WfcApList_ApplyBgScrollTask
void WfcApList_ApplyBgScrollTask();
#endif
#ifndef PROTO_LOCAL_WfcApList_UpdateCursor
void WfcApList_UpdateCursor();
#endif
#ifndef PROTO_LOCAL_WfcApList_MoveCursor
void WfcApList_MoveCursor(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcApList_ScrollUp
void WfcApList_ScrollUp();
#endif
#ifndef PROTO_LOCAL_WfcApList_ScrollDown
void WfcApList_ScrollDown();
#endif
#ifndef PROTO_LOCAL_WfcApList_HighlightSearchButton
void WfcApList_HighlightSearchButton();
#endif
#ifndef PROTO_LOCAL_WfcApList_WaitErrorDialog
void WfcApList_WaitErrorDialog();
#endif
#ifndef PROTO_LOCAL_WfcApList_WaitDialogClosed
void WfcApList_WaitDialogClosed();
#endif
#ifdef __cplusplus
}
#endif

#endif

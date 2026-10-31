#ifndef PROTO_PROTO_OV001_UNK_OV001_0220D760_H
#define PROTO_PROTO_OV001_UNK_OV001_0220D760_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcTopMenuSel
extern volatile u8 sWfcTopMenuSel;
#endif
#ifndef PROTO_LOCAL_sWfcTopMenuPalette
extern void *sWfcTopMenuPalette;
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_Enter
void WfcTopMenu_Enter();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_LoadBg
void WfcTopMenu_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_FadeIn
void WfcTopMenu_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_WaitFadeIn
void WfcTopMenu_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_WaitButtonBar
void WfcTopMenu_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_Update
void WfcTopMenu_Update();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_HandleInput
void WfcTopMenu_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_Idle
void WfcTopMenu_Idle();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_HandleResult
void WfcTopMenu_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_StartExit
void WfcTopMenu_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_FadeOut
void WfcTopMenu_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_Exit
void WfcTopMenu_Exit();
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_MoveCursor
void WfcTopMenu_MoveCursor(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcTopMenu_HighlightSelection
void WfcTopMenu_HighlightSelection();
#endif
#ifdef __cplusplus
}
#endif

#endif

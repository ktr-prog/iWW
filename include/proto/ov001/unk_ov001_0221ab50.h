#ifndef PROTO_PROTO_OV001_UNK_OV001_0221AB50_H
#define PROTO_PROTO_OV001_UNK_OV001_0221AB50_H


#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcSetupMethodColumn
extern s8 sWfcSetupMethodColumn;
#endif
#ifndef PROTO_LOCAL_sWfcSetupMethodChosen
extern u8 sWfcSetupMethodChosen;
#endif
#ifndef PROTO_LOCAL_sWfcSetupMethodCursor
extern s8 sWfcSetupMethodCursor;
#endif
#ifndef PROTO_LOCAL_sWfcSetupMethodPalette
extern void *sWfcSetupMethodPalette;
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_Enter
void WfcSetupMethod_Enter();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_LoadBg
void WfcSetupMethod_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_FadeIn
void WfcSetupMethod_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_WaitFadeIn
void WfcSetupMethod_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_WaitButtonBar
void WfcSetupMethod_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_Update
void WfcSetupMethod_Update();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_HandleInput
void WfcSetupMethod_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_Idle
void WfcSetupMethod_Idle();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_HandleResult
void WfcSetupMethod_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_StartExit
void WfcSetupMethod_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_FadeOut
void WfcSetupMethod_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_Exit
void WfcSetupMethod_Exit();
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_MoveCursor
void WfcSetupMethod_MoveCursor(s32 p);
#endif
#ifndef PROTO_LOCAL_WfcSetupMethod_HighlightOption
void WfcSetupMethod_HighlightOption();
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b2d0
extern u8 data_ov001_0222b2d0[4];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b304
extern char data_ov001_0222b304[24];
#endif
#ifndef PROTO_LOCAL_data_ov001_0222b2ec
extern char data_ov001_0222b2ec[24];
#endif
#ifdef __cplusplus
}
#endif

#endif

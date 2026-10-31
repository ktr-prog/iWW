#ifndef PROTO_PROTO_OV001_UNK_OV001_0220EB90_H
#define PROTO_PROTO_OV001_UNK_OV001_0220EB90_H


#include "types.h"
#include "nitro/gxoam.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_sWfcOptionsChosen
extern u8 sWfcOptionsChosen;
#endif
#ifndef PROTO_LOCAL_sWfcOptionsPalette
extern void *sWfcOptionsPalette;
#endif
#ifndef PROTO_LOCAL_sWfcOptionsSel
extern u8 sWfcOptionsSel;
#endif
#ifndef PROTO_LOCAL_sWfcOptionsSprite
extern GXOamAttr *sWfcOptionsSprite;
#endif
#ifndef PROTO_LOCAL_WfcOptions_Enter
void WfcOptions_Enter();
#endif
#ifndef PROTO_LOCAL_WfcOptions_LoadBg
void WfcOptions_LoadBg();
#endif
#ifndef PROTO_LOCAL_WfcOptions_FadeIn
void WfcOptions_FadeIn();
#endif
#ifndef PROTO_LOCAL_WfcOptions_WaitFadeIn
void WfcOptions_WaitFadeIn();
#endif
#ifndef PROTO_LOCAL_WfcOptions_WaitButtonBar
void WfcOptions_WaitButtonBar();
#endif
#ifndef PROTO_LOCAL_WfcOptions_Update
void WfcOptions_Update();
#endif
#ifndef PROTO_LOCAL_WfcOptions_HandleInput
void WfcOptions_HandleInput();
#endif
#ifndef PROTO_LOCAL_WfcOptions_Idle
void WfcOptions_Idle();
#endif
#ifndef PROTO_LOCAL_WfcOptions_HandleResult
void WfcOptions_HandleResult();
#endif
#ifndef PROTO_LOCAL_WfcOptions_StartExit
void WfcOptions_StartExit();
#endif
#ifndef PROTO_LOCAL_WfcOptions_FadeOut
void WfcOptions_FadeOut();
#endif
#ifndef PROTO_LOCAL_WfcOptions_Exit
void WfcOptions_Exit();
#endif
#ifndef PROTO_LOCAL_WfcOptions_MoveCursor
void WfcOptions_MoveCursor(s32 a);
#endif
#ifndef PROTO_LOCAL_WfcOptions_HighlightSelection
void WfcOptions_HighlightSelection();
#endif
#ifdef __cplusplus
}
#endif

#endif

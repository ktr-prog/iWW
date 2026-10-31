#ifndef PROTO_PROTO_MAIN_UNK_0206DB88_H
#define PROTO_PROTO_MAIN_UNK_0206DB88_H


#include "types.h"
union Slot16;
union Slot8;
union SlotS16;
#ifdef __cplusplus
#include "gfx/BgVramTask.h"
#include "gfx/HBlankTask.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_MenuScreen_WipeInVBlank
void MenuScreen_WipeInVBlank(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_WipeOutVBlank
void MenuScreen_WipeOutVBlank(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_StopWipe
void MenuScreen_StopWipe(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_StartWipeIn
void MenuScreen_StartWipeIn(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_StartWipeOut
void MenuScreen_StartWipeOut(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_IsWiping
BOOL MenuScreen_IsWiping(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_IsOpen
BOOL MenuScreen_IsOpen(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_IsClosed
BOOL MenuScreen_IsClosed(void);
#endif
#ifndef PROTO_LOCAL_MenuScreen_SetupMainBg
void MenuScreen_SetupMainBg();
#endif
#ifndef PROTO_LOCAL_MenuScreen_SetupSubBg
void MenuScreen_SetupSubBg();
#endif
#ifndef PROTO_LOCAL_MenuScreen_LoadStdBackground
BOOL MenuScreen_LoadStdBackground(u32 arg);
#endif
#ifndef PROTO_LOCAL_MenuScreen_LoadBackground
BOOL MenuScreen_LoadBackground(u32 arg);
#endif
#ifndef PROTO_LOCAL_MenuScreen_BeginClose
void MenuScreen_BeginClose();
#endif
#ifndef PROTO_LOCAL_MenuScreen_BeginOpen
void MenuScreen_BeginOpen();
#endif
#ifndef PROTO_LOCAL_MenuScreen_ReleaseCloseHold
void MenuScreen_ReleaseCloseHold();
#endif
#ifndef PROTO_LOCAL_MenuScreen_ClearState
void MenuScreen_ClearState();
#endif
#ifndef PROTO_LOCAL_MenuScreen_Reset
void MenuScreen_Reset();
#endif
#ifndef PROTO_LOCAL_MenuScreen_Update
void MenuScreen_Update();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct00
BOOL MenuScreen_StepAct00();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepNop
BOOL MenuScreen_StepNop();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct01
BOOL MenuScreen_StepAct01();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct02
BOOL MenuScreen_StepAct02();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct03
BOOL MenuScreen_StepAct03();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct04
BOOL MenuScreen_StepAct04();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct05
BOOL MenuScreen_StepAct05();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct06
BOOL MenuScreen_StepAct06();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct08
BOOL MenuScreen_StepAct08();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct09
BOOL MenuScreen_StepAct09();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct0A
BOOL MenuScreen_StepAct0A();
#endif
#ifndef PROTO_LOCAL_MenuScreen_StepAct0B
BOOL MenuScreen_StepAct0B();
#endif
#ifndef PROTO_LOCAL_Gfx_LightenPalette16
void Gfx_LightenPalette16(u16 *src, u16 *dst);
#endif
#ifndef PROTO_LOCAL_MenuScreen_SetFlags
void MenuScreen_SetFlags(u32 a);
#endif
#ifndef PROTO_LOCAL_MenuScreen_ClearFlags
void MenuScreen_ClearFlags(u32 a);
#endif
#ifndef PROTO_LOCAL_MenuScreen_HasFlags
BOOL MenuScreen_HasFlags(u32 a);
#endif
#ifndef PROTO_LOCAL_MenuScreen_SetBackgroundKind
void MenuScreen_SetBackgroundKind(u32 a);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MenuScreen_UploadClothPattern
void MenuScreen_UploadClothPattern(u16 *p, BgVramTaskPair *x, u8 *img, u16 *pal);
#endif
}
#ifndef PROTO_LOCAL_sMenuScreenFlags
extern Slot8 sMenuScreenFlags;
#endif
#ifndef PROTO_LOCAL_sMenuScreenProgress
extern s32 sMenuScreenProgress;
#endif
#ifndef PROTO_LOCAL_sMenuScreenProgressStep
extern s32 sMenuScreenProgressStep;
#endif
#ifndef PROTO_LOCAL_sMenuScreenState
extern Slot16 sMenuScreenState;
#endif
#ifndef PROTO_LOCAL_sMenuWipePos
extern SlotS16 sMenuWipePos;
#endif
#ifndef PROTO_LOCAL_sMenuScreenScroll
extern Slot16 sMenuScreenScroll;
#endif
#ifndef PROTO_LOCAL_sMenuScreenWipeFlags
extern Slot8 sMenuScreenWipeFlags;
#endif
#ifndef PROTO_LOCAL_sMenuScreenBgKind
extern Slot8 sMenuScreenBgKind;
#endif
#ifndef PROTO_LOCAL_sMenuWipeHBlankTask
extern HBlankTask sMenuWipeHBlankTask;
#endif
#ifndef PROTO_LOCAL_sMenuScreenSteps
extern BOOL (*sMenuScreenSteps[]) ();
#endif
#endif

#endif

#ifndef PROTO_PROTO_MAIN_UNK_020411DC_H
#define PROTO_PROTO_MAIN_UNK_020411DC_H


#include "types.h"
#include "gfx/ScreenTransition.h"
#ifdef __cplusplus
#include "gfx/HBlankTask.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_ScreenFade_Begin
void ScreenFade_Begin();
#endif
#ifndef PROTO_LOCAL_ScreenFade_End
void ScreenFade_End();
#endif
#ifndef PROTO_LOCAL_ScreenFade_Update
void ScreenFade_Update();
#endif
#ifndef PROTO_LOCAL_ScreenFade_VBlank
void ScreenFade_VBlank();
#endif
#ifndef PROTO_LOCAL_IrisWipe_HBlank
void IrisWipe_HBlank();
#endif
#ifndef PROTO_LOCAL_IrisWipe_VBlankRegs
void IrisWipe_VBlankRegs();
#endif
#ifndef PROTO_LOCAL_IrisWipe_SetupLayers
void IrisWipe_SetupLayers();
#endif
#ifndef PROTO_LOCAL_IrisWipe_Begin
void IrisWipe_Begin();
#endif
#ifndef PROTO_LOCAL_IrisWipe_End
void IrisWipe_End();
#endif
#ifndef PROTO_LOCAL_IrisWipe_Update
void IrisWipe_Update();
#endif
#ifndef PROTO_LOCAL_IrisWipe_SwapTables
void IrisWipe_SwapTables();
#endif
#ifndef PROTO_LOCAL_CutTransition_Begin
void CutTransition_Begin();
#endif
#ifndef PROTO_LOCAL_CutTransition_End
void CutTransition_End();
#endif
#ifndef PROTO_LOCAL_CutTransition_Update
void CutTransition_Update();
#endif
#ifndef PROTO_LOCAL_CutTransition_VBlank
void CutTransition_VBlank();
#endif
#ifndef PROTO_LOCAL_ScreenTransition_Init
void ScreenTransition_Init();
#endif
#ifndef PROTO_LOCAL_ScreenTransition_StartFadeOut
BOOL ScreenTransition_StartFadeOut(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_ScreenTransition_StartFadeIn
BOOL ScreenTransition_StartFadeIn(u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_ScreenTransition_Update
void ScreenTransition_Update();
#endif
#ifndef PROTO_LOCAL_ScreenTransition_VBlank
void ScreenTransition_VBlank();
#endif
#ifndef PROTO_LOCAL_ScreenTransition_OnHidden
void ScreenTransition_OnHidden();
#endif
#ifndef PROTO_LOCAL_ScreenTransition_HideCover
void ScreenTransition_HideCover();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef PROTO_LOCAL_sIrisWipeFlags
extern u8 sIrisWipeFlags;
#endif
#ifndef PROTO_LOCAL_data_021c3cb8
extern u8 data_021c3cb8;
#endif
#ifndef PROTO_LOCAL_sIrisWipeActiveTable
extern u16 *sIrisWipeActiveTable;
#endif
#ifndef PROTO_LOCAL_gScreenTransition
extern ScreenTransition gScreenTransition;
#endif
#ifndef PROTO_LOCAL_sIrisWipeHBlankTask
extern HBlankTask sIrisWipeHBlankTask;
#endif
#ifndef PROTO_LOCAL_sIrisWipeTableA
extern u16 sIrisWipeTableA[];
#endif
#ifndef PROTO_LOCAL_sIrisWipeTableB
extern u16 sIrisWipeTableB[];
#endif
#endif

#endif

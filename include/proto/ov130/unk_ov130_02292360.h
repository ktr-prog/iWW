#ifndef PROTO_PROTO_OV130_UNK_OV130_02292360_H
#define PROTO_PROTO_OV130_UNK_OV130_02292360_H


#include "types.h"
#include "nitro/gxoam.h"
#ifdef __cplusplus
#include "menu/NumberPad.h"
#include "ui/LabelString.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov130_02293568
extern GXOamAttr data_ov130_02293568[8];
#endif
#ifndef PROTO_LOCAL_data_ov130_022935a8
extern GXOamAttr data_ov130_022935a8[8];
#endif
#ifndef PROTO_LOCAL_data_ov130_022935e8
extern GXOamAttr data_ov130_022935e8[8];
#endif
#ifndef PROTO_LOCAL_sSeparatorCellsWide
extern GXOamAttr sSeparatorCellsWide[6];
#endif
#ifndef PROTO_LOCAL_data_ov130_022934d8
extern GXOamAttr data_ov130_022934d8[4];
#endif
#ifndef PROTO_LOCAL_sSeparatorCells
extern GXOamAttr sSeparatorCells[4];
#endif
#ifndef PROTO_LOCAL_data_ov130_02293518
extern GXOamAttr data_ov130_02293518[4];
#endif
#ifndef PROTO_LOCAL_data_ov130_022934a0
extern char data_ov130_022934a0[];
#endif
#ifndef PROTO_LOCAL_data_ov130_022934bc
extern char data_ov130_022934bc[];
#endif
#ifndef PROTO_LOCAL_data_ov130_02293458
extern char data_ov130_02293458[];
#endif
#ifndef PROTO_LOCAL_data_ov130_02293430
extern char data_ov130_02293430[];
#endif
#ifndef PROTO_LOCAL_data_ov130_0229341c
extern char data_ov130_0229341c[];
#endif
#ifndef PROTO_LOCAL_data_ov130_022933e0
extern char data_ov130_022933e0[];
#endif
#ifndef PROTO_LOCAL_data_ov130_022933f4
extern char data_ov130_022933f4[];
#endif
#ifndef PROTO_LOCAL_data_ov130_02293408
extern char data_ov130_02293408[];
#endif
#ifndef PROTO_LOCAL_data_ov130_02293444
extern char data_ov130_02293444[];
#endif
#ifndef PROTO_LOCAL_data_ov130_022933b8
extern char data_ov130_022933b8[];
#endif
#ifndef PROTO_LOCAL_data_ov130_02293368
extern char data_ov130_02293368[];
#endif
#ifndef PROTO_LOCAL_data_ov130_022933cc
extern char data_ov130_022933cc[];
#endif
#ifndef PROTO_LOCAL_data_ov130_0229337c
extern char data_ov130_0229337c[];
#endif
#ifndef PROTO_LOCAL_sNumberPadKeySeIds
extern u16 sNumberPadKeySeIds[10];
#endif
#ifndef PROTO_LOCAL_data_ov130_022933a4
extern char data_ov130_022933a4[];
#endif
#ifndef PROTO_LOCAL_sTitleObjCharFiles
extern char *sTitleObjCharFiles[2];
#endif
#ifndef PROTO_LOCAL_NumberPad_LoadBgGraphics
void NumberPad_LoadBgGraphics(s32 x);
#endif
#ifndef PROTO_LOCAL_NumberPad_LoadObjGraphics
void NumberPad_LoadObjGraphics(s32 n);
#endif
#ifndef PROTO_LOCAL_NumberPad_DrawKeypadFrame
void NumberPad_DrawKeypadFrame(s32 y);
#endif
#ifndef PROTO_LOCAL_NumberPad_PlayKeySe
void NumberPad_PlayKeySe(u32 idx);
#endif
#ifndef PROTO_LOCAL_NumberPad_PlayCancelSe
void NumberPad_PlayCancelSe();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_NumberPad_HitTestKey
u32 NumberPad_HitTestKey(NumberPad *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_NumberPad_PressKey
void NumberPad_PressKey(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_StopKeyRepeat
void NumberPad_StopKeyRepeat(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_TickKeyRepeat
BOOL NumberPad_TickKeyRepeat(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_ResetKeyPalettes
void NumberPad_ResetKeyPalettes(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_SetKeyPalette
void NumberPad_SetKeyPalette(NumberPad *s, u32 idx, s32 n);
#endif
#ifndef PROTO_LOCAL_NumberPad_HighlightKey
void NumberPad_HighlightKey(NumberPad *s, u32 idx);
#endif
#ifndef PROTO_LOCAL_NumberPad_UnhighlightKey
void NumberPad_UnhighlightKey(NumberPad *s, u32 idx);
#endif
#ifndef PROTO_LOCAL_NumberPad_GetCursorX
u32 NumberPad_GetCursorX(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_GetCursorY
u32 NumberPad_GetCursorY(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_IsCursorOnButton
BOOL NumberPad_IsCursorOnButton(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_MoveCursor
BOOL NumberPad_MoveCursor(NumberPad *s, u32 p);
#endif
#ifndef PROTO_LOCAL_NumberPad_PressCursorKey
BOOL NumberPad_PressCursorKey(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_IsCursorOnOk
BOOL NumberPad_IsCursorOnOk(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_Draw
void NumberPad_Draw(NumberPad *s, s32 y);
#endif
#ifndef PROTO_LOCAL_NumberPad_SetAmounts
void NumberPad_SetAmounts(NumberPad *s, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_NumberPad_GetValue
s32 NumberPad_GetValue(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_GetTopAmount
s32 NumberPad_GetTopAmount(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_GetBottomAmount
s32 NumberPad_GetBottomAmount(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_ClearValue
BOOL NumberPad_ClearValue(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_ApplyKey
void NumberPad_ApplyKey(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_RedrawValues
void NumberPad_RedrawValues(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_FillLargeDigits
void NumberPad_FillLargeDigits(NumberPad *s, s32 idx, s32 x, s32 y, s32 n);
#endif
#ifndef PROTO_LOCAL_NumberPad_PrintLargeNumber
void NumberPad_PrintLargeNumber(NumberPad *s, s32 val, s32 x, s32 y, s32 n);
#endif
#ifndef PROTO_LOCAL_NumberPad_PutLargeDigit
void NumberPad_PutLargeDigit(NumberPad *s, s32 idx, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_NumberPad_FillSmallDigits
void NumberPad_FillSmallDigits(NumberPad *s, s32 idx, s32 x, s32 y, s32 n);
#endif
#ifndef PROTO_LOCAL_NumberPad_PrintSmallNumber
void NumberPad_PrintSmallNumber(NumberPad *s, s32 val, s32 x, s32 y, s32 n);
#endif
#ifndef PROTO_LOCAL_NumberPad_PutSmallDigit
void NumberPad_PutSmallDigit(NumberPad *s, s32 idx, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_NumberPad_ReleaseLabels
void NumberPad_ReleaseLabels(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_AllocLabel
LabelString *NumberPad_AllocLabel(NumberPad *s);
#endif
#ifndef PROTO_LOCAL_NumberPad_TestFlags
BOOL NumberPad_TestFlags(NumberPad *s, u32 m);
#endif
#ifndef PROTO_LOCAL_NumberPad_SetFlags
void NumberPad_SetFlags(NumberPad *s, u32 m);
#endif
#ifndef PROTO_LOCAL_NumberPad_ClearFlags
void NumberPad_ClearFlags(NumberPad *s, u32 m);
#endif
}
#endif

#endif

#ifndef PROTO_PROTO_OV114_UNK_OV114_02294C40_H
#define PROTO_PROTO_OV114_UNK_OV114_02294C40_H


#include "types.h"
#include "nitro/gxoam.h"
#ifdef __cplusplus
#include "menu/CreatureBookPanel.h"
#include "ui/LabelString.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_data_ov114_02296580
extern GXOamAttr data_ov114_02296580;
#endif
#ifndef PROTO_LOCAL_data_ov114_02296588
extern GXOamAttr data_ov114_02296588;
#endif
#ifndef PROTO_LOCAL_data_ov114_02296590
extern GXOamAttr data_ov114_02296590;
#endif
#ifndef PROTO_LOCAL_data_ov114_02296598
extern GXOamAttr data_ov114_02296598;
#endif
#ifndef PROTO_LOCAL_data_ov114_022965a0
extern GXOamAttr data_ov114_022965a0;
#endif
#ifndef PROTO_LOCAL_data_ov114_022965c0
extern GXOamAttr data_ov114_022965c0[4];
#endif
#ifndef PROTO_LOCAL_data_ov114_022965e0
extern GXOamAttr data_ov114_022965e0[9];
#endif
#ifndef PROTO_LOCAL_sCreaturePicDir
extern char *sCreaturePicDir;
#endif
#ifndef PROTO_LOCAL_sCreatureBgPaletteName
extern char *sCreatureBgPaletteName;
#endif
#ifndef PROTO_LOCAL_sCreaturePicPath
extern char sCreaturePicPath[0x38];
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_CreatureBook_UpdateScrollTouch
void CreatureBook_UpdateScrollTouch(CreatureBookPanel *s, s32 a);
#endif
#ifndef PROTO_LOCAL_CreatureBook_EndScrollTouch
void CreatureBook_EndScrollTouch(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_WaitScrollHoldStart
s32 CreatureBook_WaitScrollHoldStart(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_UpdateScrollHold
void CreatureBook_UpdateScrollHold(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ReleaseKnob
void CreatureBook_ReleaseKnob(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_FinishScrollHold
BOOL CreatureBook_FinishScrollHold(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ApplyScrollInertia
void CreatureBook_ApplyScrollInertia(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_LoadDescription
void CreatureBook_LoadDescription(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_CountDescPages
u8 CreatureBook_CountDescPages(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ShowDescPage
void CreatureBook_ShowDescPage(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_NextDescPage
BOOL CreatureBook_NextDescPage(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_PrevDescPage
BOOL CreatureBook_PrevDescPage(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_SetBgFadeColor
void CreatureBook_SetBgFadeColor(CreatureBookPanel *s, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_CreatureBook_CancelIconTasks
void CreatureBook_CancelIconTasks(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_AllocIconTask
u32 CreatureBook_AllocIconTask(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ClearLabels
void CreatureBook_ClearLabels(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_AllocLabel
LabelString *CreatureBook_AllocLabel(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_SetNameLabel
void CreatureBook_SetNameLabel(CreatureBookPanel *s, u32 a);
#endif
#ifndef PROTO_LOCAL_CreatureBook_DrawRows
void CreatureBook_DrawRows(CreatureBookPanel *s, s32 a);
#endif
#ifndef PROTO_LOCAL_CreatureBook_SetScroll
BOOL CreatureBook_SetScroll(CreatureBookPanel *s, s32 v);
#endif
#ifndef PROTO_LOCAL_CreatureBook_RefreshRowIcons
void CreatureBook_RefreshRowIcons(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_TouchRow
BOOL CreatureBook_TouchRow(CreatureBookPanel *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_CreatureBook_InitRows
void CreatureBook_InitRows(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_SetRowIcon
void CreatureBook_SetRowIcon(CreatureBookPanel *s, u16 *item, s32 idx);
#endif
#ifndef PROTO_LOCAL_CreatureBook_InitPictureView
void CreatureBook_InitPictureView(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_StopPictureFade
void CreatureBook_StopPictureFade(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ShowSelected
void CreatureBook_ShowSelected(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_LoadPicture
void CreatureBook_LoadPicture(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_UpdatePictureFade
void CreatureBook_UpdatePictureFade(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_SelectEntry
void CreatureBook_SelectEntry(CreatureBookPanel *s, u8 v);
#endif
#ifndef PROTO_LOCAL_CreatureBook_GetFocusX
s32 CreatureBook_GetFocusX(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_GetFocusY
s32 CreatureBook_GetFocusY(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_GetFocusedTab
s32 CreatureBook_GetFocusedTab(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_IsFocusOnPageArrow
BOOL CreatureBook_IsFocusOnPageArrow(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ClampFocusToView
void CreatureBook_ClampFocusToView(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_GetRowFocusAtCursor
u8 CreatureBook_GetRowFocusAtCursor(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ActivateFocus
BOOL CreatureBook_ActivateFocus(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_BuildCaughtMask
void CreatureBook_BuildCaughtMask(CreatureBookPanel *s);
#endif
#ifndef PROTO_LOCAL_CreatureBook_IsCaught
BOOL CreatureBook_IsCaught(CreatureBookPanel *s, s32 i);
#endif
#ifndef PROTO_LOCAL_CreatureBook_HasFlags
BOOL CreatureBook_HasFlags(CreatureBookPanel *s, u32 m);
#endif
#ifndef PROTO_LOCAL_CreatureBook_SetFlags
void CreatureBook_SetFlags(CreatureBookPanel *s, u32 m);
#endif
#ifndef PROTO_LOCAL_CreatureBook_ClearFlags
void CreatureBook_ClearFlags(CreatureBookPanel *s, u32 m);
#endif
}
#ifndef PROTO_LOCAL_CreatureBook_MoveFocus
BOOL CreatureBook_MoveFocus(CreatureBookPanel *s, u32 pad);
#endif
#endif

#endif

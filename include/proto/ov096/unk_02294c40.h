#ifndef PROTO_PROTO_OV096_UNK_02294C40_H
#define PROTO_PROTO_OV096_UNK_02294C40_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "item/LetterView.h"
#include "menu/PocketMenu.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_PocketMenu_GetPlayerSlot
u32 PocketMenu_GetPlayerSlot();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sPocketMenuProfile
extern ProcProfile sPocketMenuProfile;
#endif
#ifndef PROTO_LOCAL_PocketMenu_Create
PocketMenu *PocketMenu_Create();
#endif
#ifndef PROTO_LOCAL_PocketMenu_TickOptionDecide
s32 PocketMenu_TickOptionDecide(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_EnterTouchIdle
void PocketMenu_EnterTouchIdle(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_EnterButtonIdle
void PocketMenu_EnterButtonIdle(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_ReturnToIdle
void PocketMenu_ReturnToIdle(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_EnterAddresseeTouch
void PocketMenu_EnterAddresseeTouch(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_EnterAddresseeButtons
void PocketMenu_EnterAddresseeButtons(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_EnterAddresseeInput
void PocketMenu_EnterAddresseeInput(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_PrepareTouchOptions
void PocketMenu_PrepareTouchOptions(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_BeginTouchOnTarget
void PocketMenu_BeginTouchOnTarget(PocketMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenu_StartTouchDrag
void PocketMenu_StartTouchDrag(PocketMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenu_StartButtonDrag
void PocketMenu_StartButtonDrag(PocketMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_PocketMenu_FlyHandTo
void PocketMenu_FlyHandTo(PocketMenu *s, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PocketMenu_FlyItemTo
void PocketMenu_FlyItemTo(PocketMenu *s, u32 a, u32 b, u32 c, u8 d);
#endif
#ifndef PROTO_LOCAL_PocketMenu_ShowMessage
void PocketMenu_ShowMessage(PocketMenu *s, u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_PocketMenu_StartRemoveBlink
void PocketMenu_StartRemoveBlink(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_CancelVramTasks
void PocketMenu_CancelVramTasks(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_IsPocketTarget
u32 PocketMenu_IsPocketTarget(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_IsLetterTarget
u32 PocketMenu_IsLetterTarget(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_IsTabTarget
u32 PocketMenu_IsTabTarget(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_IsSpecialTarget
u32 PocketMenu_IsSpecialTarget(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_MoveCursorToTab
void PocketMenu_MoveCursorToTab(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_TargetToGridIndex
u32 PocketMenu_TargetToGridIndex(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_PocketIndexToTarget
u32 PocketMenu_PocketIndexToTarget(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitPocket
u32 PocketMenu_HitPocket(PocketMenu *s, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PocketMenu_DropItemAt
s32 PocketMenu_DropItemAt(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_SetSlotItem
void PocketMenu_SetSlotItem(PocketMenu *s, u32 id, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_PocketMenu_ClearSlotItem
void PocketMenu_ClearSlotItem(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_ClearLetter
void PocketMenu_ClearLetter(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_FindEmptyPocket
u32 PocketMenu_FindEmptyPocket(PocketMenu *s);
#endif
#ifndef PROTO_LOCAL_PocketMenu_TargetToLetterIndex
u32 PocketMenu_TargetToLetterIndex(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_LetterIndexToTarget
u32 PocketMenu_LetterIndexToTarget(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitLetter
u32 PocketMenu_HitLetter(PocketMenu *s, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_PocketMenu_DropLetterAt
s32 PocketMenu_DropLetterAt(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_SetLetter
void PocketMenu_SetLetter(PocketMenu *s, u32 id, void *p);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitShirtBox
BOOL PocketMenu_HitShirtBox(PocketMenu *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitSpecialTarget
s32 PocketMenu_HitSpecialTarget(PocketMenu *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitPlayer
BOOL PocketMenu_HitPlayer(PocketMenu *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitWalletIcon
BOOL PocketMenu_HitWalletIcon(PocketMenu *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_PocketMenu_HitWalletAmount
s32 PocketMenu_HitWalletAmount(PocketMenu *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_PocketMenu_GetTargetX
s32 PocketMenu_GetTargetX(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_GetTargetY
s32 PocketMenu_GetTargetY(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_IsSlotDisabled
s32 PocketMenu_IsSlotDisabled(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_IsSlotEmpty
s32 PocketMenu_IsSlotEmpty(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_GetItem
u32 PocketMenu_GetItem(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_GetItemFlags
s32 PocketMenu_GetItemFlags(PocketMenu *s, u32 id);
#endif
#ifndef PROTO_LOCAL_PocketMenu_GetLetter
LetterView *PocketMenu_GetLetter(PocketMenu *s, u32 id);
#endif
}
#endif

#endif

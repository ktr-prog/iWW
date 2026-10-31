#ifndef PROTO_PROTO_OV110_UNK_OV110_02294C40_H
#define PROTO_PROTO_OV110_UNK_OV110_02294C40_H


#include "types.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
class LostFoundRecycleMenu;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_SetupBgLayers
void LostFoundRecycleMenu_SetupBgLayers();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sLostFoundRecycleMenuProfile
extern ProcProfile sLostFoundRecycleMenuProfile;
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_Create
LostFoundRecycleMenu *LostFoundRecycleMenu_Create();
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_Init
void LostFoundRecycleMenu_Init(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_Exit
void LostFoundRecycleMenu_Exit(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PreInputUpdate
void LostFoundRecycleMenu_PreInputUpdate(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PostInputUpdate
void LostFoundRecycleMenu_PostInputUpdate(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PreStateUpdate
void LostFoundRecycleMenu_PreStateUpdate(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PostStateUpdate
void LostFoundRecycleMenu_PostStateUpdate(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_LoadInventoryBg
void LostFoundRecycleMenu_LoadInventoryBg(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_LoadTopBg
void LostFoundRecycleMenu_LoadTopBg(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_LoadObjGraphics
void LostFoundRecycleMenu_LoadObjGraphics(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_StartTouchInput
void LostFoundRecycleMenu_StartTouchInput(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_StartButtonInput
void LostFoundRecycleMenu_StartButtonInput(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ResumeInput
void LostFoundRecycleMenu_ResumeInput(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_TouchItem
void LostFoundRecycleMenu_TouchItem(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PickUpWithTouch
void LostFoundRecycleMenu_PickUpWithTouch(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PickUpWithHand
void LostFoundRecycleMenu_PickUpWithHand(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_StartFlyHeldItem
void LostFoundRecycleMenu_StartFlyHeldItem(LostFoundRecycleMenu *s, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_FlyHeldToFreeSlot
void LostFoundRecycleMenu_FlyHeldToFreeSlot(LostFoundRecycleMenu *s, u32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_QuickMove
void LostFoundRecycleMenu_QuickMove(LostFoundRecycleMenu *s, u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_FindFreePocket
u32 LostFoundRecycleMenu_FindFreePocket(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_FindFreeBoxSlot
u32 LostFoundRecycleMenu_FindFreeBoxSlot(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_CancelUploads
void LostFoundRecycleMenu_CancelUploads(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_IsPocketSlot
BOOL LostFoundRecycleMenu_IsPocketSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_IsBoxSlot
BOOL LostFoundRecycleMenu_IsBoxSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_IsButtonSlot
BOOL LostFoundRecycleMenu_IsButtonSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ToGridSlot
u32 LostFoundRecycleMenu_ToGridSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GridToPocketSlot
u32 LostFoundRecycleMenu_GridToPocketSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_FindSlotAt
u32 LostFoundRecycleMenu_FindSlotAt(LostFoundRecycleMenu *s, u32 a, u32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_DropHeldItem
BOOL LostFoundRecycleMenu_DropHeldItem(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_SetSlotItem
void LostFoundRecycleMenu_SetSlotItem(LostFoundRecycleMenu *s, u32 a, u32 b, u32 c);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GridToBoxSlotOr0F
u32 LostFoundRecycleMenu_GridToBoxSlotOr0F(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GridToBoxSlot
u32 LostFoundRecycleMenu_GridToBoxSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GetSlotX
u32 LostFoundRecycleMenu_GetSlotX(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GetSlotY
s32 LostFoundRecycleMenu_GetSlotY(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_IsItemRejected
BOOL LostFoundRecycleMenu_IsItemRejected(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_DisableRejectedItems
void LostFoundRecycleMenu_DisableRejectedItems(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_IsSlotDisabled
BOOL LostFoundRecycleMenu_IsSlotDisabled(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_IsSlotEmpty
BOOL LostFoundRecycleMenu_IsSlotEmpty(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GetSlotItem
u32 LostFoundRecycleMenu_GetSlotItem(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GetSlotFlags
u32 LostFoundRecycleMenu_GetSlotFlags(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ClearCursorSlots
void LostFoundRecycleMenu_ClearCursorSlots(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_SetCursorSlot
void LostFoundRecycleMenu_SetCursorSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ClearMarks
void LostFoundRecycleMenu_ClearMarks(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_MarkSlot
void LostFoundRecycleMenu_MarkSlot(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_HasTouchMoved
BOOL LostFoundRecycleMenu_HasTouchMoved(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PlaceNameBalloon
void LostFoundRecycleMenu_PlaceNameBalloon(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_UpdateNameBalloon
void LostFoundRecycleMenu_UpdateNameBalloon(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_DrawHeldItem
void LostFoundRecycleMenu_DrawHeldItem(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_TrackTouch
void LostFoundRecycleMenu_TrackTouch(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_TrackCursor
void LostFoundRecycleMenu_TrackCursor(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_TrackFlyingItem
void LostFoundRecycleMenu_TrackFlyingItem(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PickUpItem
void LostFoundRecycleMenu_PickUpItem(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ReleaseHeldItem
void LostFoundRecycleMenu_ReleaseHeldItem(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ExchangeHeldItem
void LostFoundRecycleMenu_ExchangeHeldItem(LostFoundRecycleMenu *s, u32 a);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_ShowCursor
void LostFoundRecycleMenu_ShowCursor(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GetCursorTargetX
s32 LostFoundRecycleMenu_GetCursorTargetX(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_GetCursorTargetY
s32 LostFoundRecycleMenu_GetCursorTargetY(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_HideCursor
void LostFoundRecycleMenu_HideCursor(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_MoveCursorToTarget
void LostFoundRecycleMenu_MoveCursorToTarget(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_MoveCursorToChoice
void LostFoundRecycleMenu_MoveCursorToChoice(LostFoundRecycleMenu *s);
#endif
#ifndef PROTO_LOCAL_LostFoundRecycleMenu_PickCancelChoice
void LostFoundRecycleMenu_PickCancelChoice(LostFoundRecycleMenu *s);
#endif
}
#endif

#endif

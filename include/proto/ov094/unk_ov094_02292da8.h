#ifndef PROTO_PROTO_OV094_UNK_OV094_02292DA8_H
#define PROTO_PROTO_OV094_UNK_OV094_02292DA8_H


#include "types.h"
#ifdef __cplusplus
#include "menu/InventoryGridTypes.h"
#include "menu/InventoryItemGrid.h"
#include "ui/LabelBalloon.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetIconPalette
u8 InventoryItemGrid_GetIconPalette(void *o, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetScale
u32 InventoryItemGrid_GetScale(u32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_ClearBits
void InventoryItemGrid_ClearBits(u32 *bits);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_SetBit
void InventoryItemGrid_SetBit(u32 *bits, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_ClearBit
void InventoryItemGrid_ClearBit(u32 *bits, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_TestBit
BOOL InventoryItemGrid_TestBit(u32 *bits, s32 i);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sHeldItemSprite
extern OamObjTemplate sHeldItemSprite;
#endif
#ifndef PROTO_LOCAL_sItemGridMarkSprites
extern OamObjTemplate sItemGridMarkSprites[3];
#endif
#ifndef PROTO_LOCAL_sItemGridSlotSprites
extern OamObjTemplate sItemGridSlotSprites[34];
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_Init
void InventoryItemGrid_Init(InventoryItemGrid *o, u32 a);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_PreUpdate
void InventoryItemGrid_PreUpdate(InventoryItemGrid *o);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_Exit
void InventoryItemGrid_Exit(InventoryItemGrid *o);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_FindPocketSlotAt
u32 InventoryItemGrid_FindPocketSlotAt(InventoryItemGrid *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_FindBoxSlotAt
u32 InventoryItemGrid_FindBoxSlotAt(InventoryItemGrid *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_HitTestSlot21
s32 InventoryItemGrid_HitTestSlot21(InventoryItemGrid *o, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_FindSlotInRange
u32 InventoryItemGrid_FindSlotInRange(InventoryItemGrid *o, s32 a, s32 b, s32 c, s32 d, u8 s, u8 e);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_HitTestSlot
s32 InventoryItemGrid_HitTestSlot(InventoryItemGrid *o, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_LoadSlotIcon
void InventoryItemGrid_LoadSlotIcon(InventoryItemGrid *o, s32 k, u16 *p, s32 a);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_LoadPockets
void InventoryItemGrid_LoadPockets(InventoryItemGrid *o);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_LoadBox
void InventoryItemGrid_LoadBox(InventoryItemGrid *o, u16 *arr);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetIconIndex
s32 InventoryItemGrid_GetIconIndex(InventoryItemGrid *o, u16 *p, s32 mode);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_SetBalloonItemName
void InventoryItemGrid_SetBalloonItemName(InventoryItemGrid *o, LabelBalloon *dst, u16 *p, s32 mode);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_ShowSlotName
void InventoryItemGrid_ShowSlotName(InventoryItemGrid *o, LabelBalloon *dst, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetSlotX
s32 InventoryItemGrid_GetSlotX(InventoryItemGrid *o, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetSlotY
s32 InventoryItemGrid_GetSlotY(InventoryItemGrid *o, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_IsCursorSlot
BOOL InventoryItemGrid_IsCursorSlot(InventoryItemGrid *o, s32 v);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetCursorLift
s32 InventoryItemGrid_GetCursorLift(InventoryItemGrid *o);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_ClearCursorSlot
void InventoryItemGrid_ClearCursorSlot(InventoryItemGrid *o);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_SetCursorSlot
void InventoryItemGrid_SetCursorSlot(InventoryItemGrid *o, u32 v);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_ClearMarks
void InventoryItemGrid_ClearMarks(InventoryItemGrid *s);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_MarkSlot
void InventoryItemGrid_MarkSlot(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetSlotItem
u16 InventoryItemGrid_GetSlotItem(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetSlotFlags
u32 InventoryItemGrid_GetSlotFlags(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_ClearSlot
void InventoryItemGrid_ClearSlot(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_SetSlotItem
void InventoryItemGrid_SetSlotItem(InventoryItemGrid *s, s32 i, u32 v, s32 x);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_RefreshSlot
void InventoryItemGrid_RefreshSlot(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_SetHeldItem
void InventoryItemGrid_SetHeldItem(InventoryItemGrid *s, u32 item, s32 m);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_SetSpriteItem
void InventoryItemGrid_SetSpriteItem(InventoryItemGrid *s, OamObjTemplate *r, u32 v, s32 m);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_UploadIcon
void InventoryItemGrid_UploadIcon(InventoryItemGrid *s, OamObjTemplate *r, u8 *dst, s32 c);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_IsSlotDisabled
BOOL InventoryItemGrid_IsSlotDisabled(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DisableSlotRange
void InventoryItemGrid_DisableSlotRange(InventoryItemGrid *s, u8 i, u8 e);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DisableSlot
void InventoryItemGrid_DisableSlot(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawPockets
void InventoryItemGrid_DrawPockets(InventoryItemGrid *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawPocketsClipped
void InventoryItemGrid_DrawPocketsClipped(InventoryItemGrid *s, s32 x, s32 y, s32 w);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawBox
void InventoryItemGrid_DrawBox(InventoryItemGrid *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawExtraMarks
void InventoryItemGrid_DrawExtraMarks(InventoryItemGrid *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawHeldItem
void InventoryItemGrid_DrawHeldItem(InventoryItemGrid *s, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_IsSlotEmpty
BOOL InventoryItemGrid_IsSlotEmpty(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawMark
void InventoryItemGrid_DrawMark(InventoryItemGrid *s, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawUnderlay
void InventoryItemGrid_DrawUnderlay(InventoryItemGrid *s, s32 a, s32 b, s32 c);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawFocus
void InventoryItemGrid_DrawFocus(InventoryItemGrid *s, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_DrawSlot
void InventoryItemGrid_DrawSlot(InventoryItemGrid *s, OamObjTemplate *e, s32 idx, s32 x, s32 y);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetSlotSprite
OamObjTemplate *InventoryItemGrid_GetSlotSprite(InventoryItemGrid *s, s32 i);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_CancelUploads
void InventoryItemGrid_CancelUploads(InventoryItemGrid *s);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_AllocUpload
u32 InventoryItemGrid_AllocUpload(InventoryItemGrid *s);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_StartPresentAnim
void InventoryItemGrid_StartPresentAnim(InventoryItemGrid *s, u32 v, s32 m);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_EndPresentAnim
void InventoryItemGrid_EndPresentAnim(InventoryItemGrid *s);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_UpdatePresentAnim
BOOL InventoryItemGrid_UpdatePresentAnim(InventoryItemGrid *s);
#endif
#ifndef PROTO_LOCAL_InventoryItemGrid_GetPresentAnimScale
s32 InventoryItemGrid_GetPresentAnimScale(InventoryItemGrid *s);
#endif
}
#endif

#endif

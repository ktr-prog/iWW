#ifndef PROTO_PROTO_OV094_UNK_OV094_02292360_H
#define PROTO_PROTO_OV094_UNK_OV094_02292360_H


#include "types.h"
#ifdef __cplusplus
#include "menu/InventoryBg.h"
#include "menu/InventoryGridTypes.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_InventoryBg_LoadObjGraphics
void InventoryBg_LoadObjGraphics();
#endif
#ifndef PROTO_LOCAL_InventoryBg_GetTotalBells
s32 InventoryBg_GetTotalBells();
#endif
#ifndef PROTO_LOCAL_InvItem_IsTurnipFishOrInsect
BOOL InvItem_IsTurnipFishOrInsect(u32 v);
#endif
#ifndef PROTO_LOCAL_InvItem_IsDeliveryItem
BOOL InvItem_IsDeliveryItem(u32 v);
#endif
#ifndef PROTO_LOCAL_InvItem_IsDeliveryParcel
BOOL InvItem_IsDeliveryParcel(u32 v);
#endif
#ifndef PROTO_LOCAL_InvItem_IsNonTransferable
BOOL InvItem_IsNonTransferable(u32 v);
#endif
#ifndef PROTO_LOCAL_InvItem_IsNotFishInsectOrFlower
BOOL InvItem_IsNotFishInsectOrFlower(u32 v);
#endif
#ifndef PROTO_LOCAL_Inventory_PlayPutDownSe
void Inventory_PlayPutDownSe();
#endif
#ifndef PROTO_LOCAL_Inventory_PlayTouchSe
void Inventory_PlayTouchSe();
#endif
#ifndef PROTO_LOCAL_Inventory_PlayPickUpSe
void Inventory_PlayPickUpSe();
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_sInventoryBgSprite
extern OamObjTemplate sInventoryBgSprite;
#endif
#ifndef PROTO_LOCAL_InventoryBg_Init
void InventoryBg_Init(InventoryBg *p, u32 v);
#endif
#ifndef PROTO_LOCAL_InventoryBg_Load
void InventoryBg_Load(InventoryBg *p, s32 flag);
#endif
#ifndef PROTO_LOCAL_InventoryBg_LoadBg
void InventoryBg_LoadBg(InventoryBg *p, s32 flag);
#endif
#ifndef PROTO_LOCAL_InventoryBg_LoadGraphics
void InventoryBg_LoadGraphics(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_SetupTextWindows
void InventoryBg_SetupTextWindows(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_PreUpdate
void InventoryBg_PreUpdate(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_Update
void InventoryBg_Update(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_Exit
void InventoryBg_Exit(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_CancelUploads
void InventoryBg_CancelUploads(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_ClearTextWindows
void InventoryBg_ClearTextWindows(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_UploadScreen
void InventoryBg_UploadScreen(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_PaintNormal
void InventoryBg_PaintNormal(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_PaintHighlight0
void InventoryBg_PaintHighlight0(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_PaintHighlight1
void InventoryBg_PaintHighlight1(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_LoadPictureForHeldItem
void InventoryBg_LoadPictureForHeldItem(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_LoadPicture
void InventoryBg_LoadPicture(InventoryBg *p, s32 a, s32 b);
#endif
#ifndef PROTO_LOCAL_InventoryBg_UploadPicture
void InventoryBg_UploadPicture(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_UploadPalette
void InventoryBg_UploadPalette(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_DrawSprite
void InventoryBg_DrawSprite(InventoryBg *p, s32 y);
#endif
#ifndef PROTO_LOCAL_InventoryBg_StartBlink
void InventoryBg_StartBlink(InventoryBg *p, u32 v);
#endif
#ifndef PROTO_LOCAL_InventoryBg_UpdateBlink
BOOL InventoryBg_UpdateBlink(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_StopBlink
void InventoryBg_StopBlink(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_StartBellRoll
void InventoryBg_StartBellRoll(InventoryBg *p, u32 v);
#endif
#ifndef PROTO_LOCAL_InventoryBg_SetBellsPanelMode
void InventoryBg_SetBellsPanelMode(InventoryBg *p, u32 n);
#endif
#ifndef PROTO_LOCAL_InventoryBg_ResetBells
void InventoryBg_ResetBells(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_UpdateBells
void InventoryBg_UpdateBells(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_UpdateHighlight
void InventoryBg_UpdateHighlight(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_SetHighlight
void InventoryBg_SetHighlight(InventoryBg *p, u32 v);
#endif
#ifndef PROTO_LOCAL_InventoryBg_ResetHighlight
void InventoryBg_ResetHighlight(InventoryBg *p);
#endif
#ifndef PROTO_LOCAL_InventoryBg_IsDirty
s32 InventoryBg_IsDirty(InventoryBg *p, u32 m);
#endif
#ifndef PROTO_LOCAL_InventoryBg_SetDirty
void InventoryBg_SetDirty(InventoryBg *p, u32 m);
#endif
#ifndef PROTO_LOCAL_InventoryBg_ClearDirty
void InventoryBg_ClearDirty(InventoryBg *p, u32 m);
#endif
}
#endif

#endif

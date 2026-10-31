#include "host_shared_calls.h"

extern const HostSharedCall gSharedCall_BarberMachine_Start;
extern const HostSharedCall gSharedCall_BuildingList_FindByItem;
extern const HostSharedCall gSharedCall_CreatureBook_ActivateFocus;
extern const HostSharedCall gSharedCall_CreatureBook_DrawRows;
extern const HostSharedCall gSharedCall_CreatureBook_EndScrollTouch;
extern const HostSharedCall gSharedCall_CreatureBook_GetFocusX;
extern const HostSharedCall gSharedCall_CreatureBook_GetFocusY;
extern const HostSharedCall gSharedCall_CreatureBook_GetFocusedTab;
extern const HostSharedCall gSharedCall_CreatureBook_IsFocusOnPageArrow;
extern const HostSharedCall gSharedCall_CreatureBook_RefreshRowIcons;
extern const HostSharedCall gSharedCall_CreatureBook_WaitScrollHoldStart;
extern const HostSharedCall gSharedCall_DateTimePicker_BeginFrame;
extern const HostSharedCall gSharedCall_DateTimePicker_CancelList;
extern const HostSharedCall gSharedCall_DateTimePicker_DecideList;
extern const HostSharedCall gSharedCall_DateTimePicker_EndHandDrag;
extern const HostSharedCall gSharedCall_DateTimePicker_GrabHand;
extern const HostSharedCall gSharedCall_DateTimePicker_HitTestList;
extern const HostSharedCall gSharedCall_DateTimePicker_UpdateHandAnim;
extern const HostSharedCall gSharedCall_DateTimePicker_UpdateListClose;
extern const HostSharedCall gSharedCall_DateTimePicker_UpdateListOpen;
extern const HostSharedCall gSharedCall_DwcFriend_GetProfileId;
extern const HostSharedCall gSharedCall_DwcFriend_IsIdle;
extern const HostSharedCall gSharedCall_FieldInsect_GetPosAndKind;
extern const HostSharedCall gSharedCall_FieldObj_FreeCedarFileBufs;
extern const HostSharedCall gSharedCall_FieldObj_LoadIconModels;
extern const HostSharedCall gSharedCall_FieldObj_LoadStones;
extern const HostSharedCall gSharedCall_FieldObjectManager_Create;
extern const HostSharedCall gSharedCall_Field_GetStructureTexSuffix;
extern const HostSharedCall gSharedCall_FishCatch_Reset;
extern const HostSharedCall gSharedCall_FishCatch_StateStart;
extern const HostSharedCall gSharedCall_FishShadow_EnterSpawn;
extern const HostSharedCall gSharedCall_FishShadow_RunAi;
extern const HostSharedCall gSharedCall_GeneralMenuHeader_GetStyle;
extern const HostSharedCall gSharedCall_InvItem_IsDeliveryItem;
extern const HostSharedCall gSharedCall_InvItem_IsNonTransferable;
extern const HostSharedCall gSharedCall_InvItem_IsNotFishInsectOrFlower;
extern const HostSharedCall gSharedCall_InvItem_IsTurnipFishOrInsect;
extern const HostSharedCall gSharedCall_InventoryBg_DrawSprite;
extern const HostSharedCall gSharedCall_InventoryBg_Init;
extern const HostSharedCall gSharedCall_InventoryBg_LoadBg;
extern const HostSharedCall gSharedCall_InventoryBg_LoadPictureForHeldItem;
extern const HostSharedCall gSharedCall_InventoryBg_PreUpdate;
extern const HostSharedCall gSharedCall_InventoryBg_ResetHighlight;
extern const HostSharedCall gSharedCall_InventoryBg_SetBellsPanelMode;
extern const HostSharedCall gSharedCall_InventoryBg_StartBlink;
extern const HostSharedCall gSharedCall_InventoryItemGrid_ClearMarks;
extern const HostSharedCall gSharedCall_InventoryItemGrid_ClearSlot;
extern const HostSharedCall gSharedCall_InventoryItemGrid_DisableSlotRange;
extern const HostSharedCall gSharedCall_InventoryItemGrid_DrawExtraMarks;
extern const HostSharedCall gSharedCall_InventoryItemGrid_Exit;
extern const HostSharedCall gSharedCall_InventoryItemGrid_FindBoxSlotAt;
extern const HostSharedCall gSharedCall_InventoryItemGrid_GetSlotItem;
extern const HostSharedCall gSharedCall_InventoryItemGrid_HitTestSlot21;
extern const HostSharedCall gSharedCall_InventoryItemGrid_IsSlotDisabled;
extern const HostSharedCall gSharedCall_InventoryItemGrid_LoadPockets;
extern const HostSharedCall gSharedCall_InventoryItemGrid_SetCursorSlot;
extern const HostSharedCall gSharedCall_InventoryItemGrid_SetHeldItem;
extern const HostSharedCall gSharedCall_InventoryItemGrid_ShowSlotName;
extern const HostSharedCall gSharedCall_InventoryItemGrid_StartPresentAnim;
extern const HostSharedCall gSharedCall_InventoryItemGrid_UpdatePresentAnim;
extern const HostSharedCall gSharedCall_Inventory_PlayPickUpSe;
extern const HostSharedCall gSharedCall_Keyboard_ClearHighlight;
extern const HostSharedCall gSharedCall_Keyboard_DeleteRange;
extern const HostSharedCall gSharedCall_Keyboard_DisableModifierKeys;
extern const HostSharedCall gSharedCall_Keyboard_DrawCopyPasteKeys;
extern const HostSharedCall gSharedCall_Keyboard_DrawCopyPasteKeysChat;
extern const HostSharedCall gSharedCall_Keyboard_EnableKey;
extern const HostSharedCall gSharedCall_Keyboard_EnterTabRowAtX;
extern const HostSharedCall gSharedCall_Keyboard_EnterTabRowAtX2;
extern const HostSharedCall gSharedCall_Keyboard_GetSelectedEmotion;
extern const HostSharedCall gSharedCall_Keyboard_GetTypedRunLength;
extern const HostSharedCall gSharedCall_Keyboard_HandleModeKey;
extern const HostSharedCall gSharedCall_Keyboard_HighlightKey;
extern const HostSharedCall gSharedCall_Keyboard_InsertCharMultiline;
extern const HostSharedCall gSharedCall_Keyboard_IsOnButtonKey;
extern const HostSharedCall gSharedCall_Keyboard_LoadEmotionIcons;
extern const HostSharedCall gSharedCall_Keyboard_LoadLetterChars;
extern const HostSharedCall gSharedCall_Keyboard_MarkScreenDirty;
extern const HostSharedCall gSharedCall_Keyboard_ModifyCharKey104;
extern const HostSharedCall gSharedCall_Keyboard_PlayCopySe;
extern const HostSharedCall gSharedCall_Keyboard_PressCursorKey;
extern const HostSharedCall gSharedCall_Keyboard_Reload;
extern const HostSharedCall gSharedCall_Keyboard_ReplaceCharBeforeCursor;
extern const HostSharedCall gSharedCall_Keyboard_ResetTypedRun;
extern const HostSharedCall gSharedCall_Keyboard_RestoreLastPage;
extern const HostSharedCall gSharedCall_Keyboard_SelectEmotionByCode;
extern const HostSharedCall gSharedCall_Keyboard_SelectSendKey;
extern const HostSharedCall gSharedCall_Keyboard_SetTextFieldPos;
extern const HostSharedCall gSharedCall_Keyboard_TickKeyRepeat;
extern const HostSharedCall gSharedCall_Keyboard_TouchKey;
extern const HostSharedCall gSharedCall_Keyboard_TouchSendKey;
extern const HostSharedCall gSharedCall_LetterGrid_GetSlotY;
extern const HostSharedCall gSharedCall_LetterGrid_LoadPocketLetters;
extern const HostSharedCall gSharedCall_LetterGrid_SetLetters0A;
extern const HostSharedCall gSharedCall_LetterGrid_SetLetters2D;
extern const HostSharedCall gSharedCall_LetterGrid_UpdatePopAnim;
extern const HostSharedCall gSharedCall_LocalWl_SetEventCallback;
extern const HostSharedCall gSharedCall_NumberPad_Draw;
extern const HostSharedCall gSharedCall_NumberPad_DrawKeypadFrame;
extern const HostSharedCall gSharedCall_NumberPad_GetCursorX;
extern const HostSharedCall gSharedCall_NumberPad_GetValue;
extern const HostSharedCall gSharedCall_NumberPad_HitTestKey;
extern const HostSharedCall gSharedCall_NumberPad_IsCursorOnButton;
extern const HostSharedCall gSharedCall_NumberPad_PlayCancelSe;
extern const HostSharedCall gSharedCall_NumberPad_PressCursorKey;
extern const HostSharedCall gSharedCall_NumberPad_SetAmounts;
extern const HostSharedCall gSharedCall_PlayerActor_EndAct3C;
extern const HostSharedCall gSharedCall_PlayerActor_EndFillHole;
extern const HostSharedCall gSharedCall_PlayerActor_EndFishWait;
extern const HostSharedCall gSharedCall_PlayerActor_EndShovelStrike;
extern const HostSharedCall gSharedCall_PlayerActor_EndTreeShake;
extern const HostSharedCall gSharedCall_PlayerActor_EndUmbrellaSpin;
extern const HostSharedCall gSharedCall_PlayerActor_GetTrackTarget;
extern const HostSharedCall gSharedCall_PlayerActor_LocalEndWatch;
extern const HostSharedCall gSharedCall_PlayerActor_LocalRequestDoorApproach;
extern const HostSharedCall gSharedCall_PlayerActor_MainAct5C;
extern const HostSharedCall gSharedCall_PlayerActor_MainMailboxWait;
extern const HostSharedCall gSharedCall_PlayerActor_MainReleaseCreature;
extern const HostSharedCall gSharedCall_PlayerActor_MainShovelStrike;
extern const HostSharedCall gSharedCall_PlayerActor_MainThrowBottle;
extern const HostSharedCall gSharedCall_PlayerActor_NetAct12;
extern const HostSharedCall gSharedCall_PlayerActor_NetAct82;
extern const HostSharedCall gSharedCall_PlayerActor_NetAxeBreak;
extern const HostSharedCall gSharedCall_PlayerActor_NetAxeFollowThrough;
extern const HostSharedCall gSharedCall_PlayerActor_NetFishWait;
extern const HostSharedCall gSharedCall_PlayerActor_NetFtrPushMove;
extern const HostSharedCall gSharedCall_PlayerActor_RequestAct3C;
extern const HostSharedCall gSharedCall_PlayerActor_RoomInteractAt;
extern const HostSharedCall gSharedCall_PlayerActor_SetupAct3C;
extern const HostSharedCall gSharedCall_PlayerActor_SetupAxeFollowThrough;
extern const HostSharedCall gSharedCall_PlayerActor_SetupFirework;
extern const HostSharedCall gSharedCall_PlayerActor_SetupFishEscape;
extern const HostSharedCall gSharedCall_PlayerActor_SetupStorageClose;
extern const HostSharedCall gSharedCall_PlayerActor_SetupTreeShakeRelease;
extern const HostSharedCall gSharedCall_PocketMenu_CanEditRoom;
extern const HostSharedCall gSharedCall_PocketMenu_GetPlayerSlot;
extern const HostSharedCall gSharedCall_PocketMenu_SetSlotItem;
extern const HostSharedCall gSharedCall_PocketMenu_StartRemoveBlink;
extern const HostSharedCall gSharedCall_PopupChoice_Update;
extern const HostSharedCall gSharedCall_RoomObjTex_Construct;
extern const HostSharedCall gSharedCall_Room_PickRandomWalkTarget;
extern const HostSharedCall gSharedCall_Sock_Bind;
extern const HostSharedCall gSharedCall_Sock_Startup;
extern const HostSharedCall gSharedCall_SpNpcKappn_GetAnimState;
extern const HostSharedCall gSharedCall_StarSky_CancelUpload;
extern const HostSharedCall gSharedCall_StarSky_DrawArrows;
extern const HostSharedCall gSharedCall_StarSky_FindConstellationByLine;
extern const HostSharedCall gSharedCall_StarSky_HitArrow;
extern const HostSharedCall gSharedCall_StarSky_IsConstellationFree;
extern const HostSharedCall gSharedCall_StarSky_RebuildScreen;
extern const HostSharedCall gSharedCall_StarSky_ScreenToCell;
extern const HostSharedCall gSharedCall_StarSky_ScreenToCellInScope;
extern const HostSharedCall gSharedCall_StarSky_ScrollInDir;
extern const HostSharedCall gSharedCall_StarSky_ScrollX;
extern const HostSharedCall gSharedCall_StarSky_SetScroll;
extern const HostSharedCall gSharedCall_StarSky_SetScrollTarget;
extern const HostSharedCall gSharedCall_TownMapImage_AllocGlobal;
extern const HostSharedCall gSharedCall_TownMapImage_BuildMarkersGlobal;
extern const HostSharedCall gSharedCall_TownMapImage_FinishGlobal;
extern const HostSharedCall gSharedCall_TownMapMarkers_Clear;
extern const HostSharedCall gSharedCall_TownMapMarkers_Get;
extern const HostSharedCall gSharedCall_Wlx_StartExchange;
extern const HostSharedCall gSharedCall_Wlx_Stop;

void Shared_BarberMachine_Start(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_BarberMachine_Start))();
}

void * Shared_BuildingList_FindByItem(unsigned int a0) {
    return ((void * (*)(unsigned int))Modern_SharedResolve(&gSharedCall_BuildingList_FindByItem))(a0);
}

int Shared_CreatureBook_ActivateFocus(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_ActivateFocus))(a0);
}

void Shared_CreatureBook_DrawRows(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_CreatureBook_DrawRows))(a0, a1);
}

void Shared_CreatureBook_EndScrollTouch(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_EndScrollTouch))(a0);
}

int Shared_CreatureBook_GetFocusX(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_GetFocusX))(a0);
}

int Shared_CreatureBook_GetFocusY(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_GetFocusY))(a0);
}

int Shared_CreatureBook_GetFocusedTab(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_GetFocusedTab))(a0);
}

int Shared_CreatureBook_IsFocusOnPageArrow(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_IsFocusOnPageArrow))(a0);
}

void Shared_CreatureBook_RefreshRowIcons(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_RefreshRowIcons))(a0);
}

int Shared_CreatureBook_WaitScrollHoldStart(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_CreatureBook_WaitScrollHoldStart))(a0);
}

void Shared_DateTimePicker_BeginFrame(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_BeginFrame))(a0);
}

void Shared_DateTimePicker_CancelList(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_CancelList))(a0);
}

void Shared_DateTimePicker_DecideList(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_DecideList))(a0);
}

int Shared_DateTimePicker_EndHandDrag(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_EndHandDrag))(a0);
}

int Shared_DateTimePicker_GrabHand(void * a0, unsigned int a1, unsigned int a2) {
    return ((int (*)(void *, unsigned int, unsigned int))Modern_SharedResolve(&gSharedCall_DateTimePicker_GrabHand))(a0, a1, a2);
}

int Shared_DateTimePicker_HitTestList(void * a0, int a1, int a2) {
    return ((int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_DateTimePicker_HitTestList))(a0, a1, a2);
}

int Shared_DateTimePicker_UpdateHandAnim(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_UpdateHandAnim))(a0);
}

int Shared_DateTimePicker_UpdateListClose(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_UpdateListClose))(a0);
}

int Shared_DateTimePicker_UpdateListOpen(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_DateTimePicker_UpdateListOpen))(a0);
}

int Shared_DwcFriend_GetProfileId(int a0) {
    return ((int (*)(int))Modern_SharedResolve(&gSharedCall_DwcFriend_GetProfileId))(a0);
}

int Shared_DwcFriend_IsIdle(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_DwcFriend_IsIdle))();
}

int Shared_FieldInsect_GetPosAndKind(void * a0, unsigned int a1) {
    return ((int (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_FieldInsect_GetPosAndKind))(a0, a1);
}

void Shared_FieldObj_FreeCedarFileBufs(void * a0, void * a1, void * a2, void * a3) {
    ((void (*)(void *, void *, void *, void *))Modern_SharedResolve(&gSharedCall_FieldObj_FreeCedarFileBufs))(a0, a1, a2, a3);
}

int Shared_FieldObj_LoadIconModels(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_FieldObj_LoadIconModels))(a0);
}

int Shared_FieldObj_LoadStones(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_FieldObj_LoadStones))();
}

void * Shared_FieldObjectManager_Create(void) {
    return ((void * (*)(void))Modern_SharedResolve(&gSharedCall_FieldObjectManager_Create))();
}

int Shared_Field_GetStructureTexSuffix(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_Field_GetStructureTexSuffix))();
}

void Shared_FishCatch_Reset(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_FishCatch_Reset))(a0, a1);
}

int Shared_FishCatch_StateStart(void * a0, unsigned int a1) {
    return ((int (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_FishCatch_StateStart))(a0, a1);
}

void Shared_FishShadow_EnterSpawn(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_FishShadow_EnterSpawn))();
}

void Shared_FishShadow_RunAi(void * a0, int a1, int a2, int a3) {
    ((void (*)(void *, int, int, int))Modern_SharedResolve(&gSharedCall_FishShadow_RunAi))(a0, a1, a2, a3);
}

int Shared_GeneralMenuHeader_GetStyle(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_GeneralMenuHeader_GetStyle))();
}

int Shared_InvItem_IsDeliveryItem(unsigned int a0) {
    return ((int (*)(unsigned int))Modern_SharedResolve(&gSharedCall_InvItem_IsDeliveryItem))(a0);
}

int Shared_InvItem_IsNonTransferable(unsigned int a0) {
    return ((int (*)(unsigned int))Modern_SharedResolve(&gSharedCall_InvItem_IsNonTransferable))(a0);
}

int Shared_InvItem_IsNotFishInsectOrFlower(unsigned int a0) {
    return ((int (*)(unsigned int))Modern_SharedResolve(&gSharedCall_InvItem_IsNotFishInsectOrFlower))(a0);
}

int Shared_InvItem_IsTurnipFishOrInsect(unsigned int a0) {
    return ((int (*)(unsigned int))Modern_SharedResolve(&gSharedCall_InvItem_IsTurnipFishOrInsect))(a0);
}

void Shared_InventoryBg_DrawSprite(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_InventoryBg_DrawSprite))(a0, a1);
}

void Shared_InventoryBg_Init(void * a0, unsigned int a1) {
    ((void (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_InventoryBg_Init))(a0, a1);
}

void Shared_InventoryBg_LoadBg(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_InventoryBg_LoadBg))(a0, a1);
}

void Shared_InventoryBg_LoadPictureForHeldItem(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryBg_LoadPictureForHeldItem))(a0);
}

void Shared_InventoryBg_PreUpdate(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryBg_PreUpdate))(a0);
}

void Shared_InventoryBg_ResetHighlight(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryBg_ResetHighlight))(a0);
}

void Shared_InventoryBg_SetBellsPanelMode(void * a0, unsigned int a1) {
    ((void (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_InventoryBg_SetBellsPanelMode))(a0, a1);
}

void Shared_InventoryBg_StartBlink(void * a0, unsigned int a1) {
    ((void (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_InventoryBg_StartBlink))(a0, a1);
}

void Shared_InventoryItemGrid_ClearMarks(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_ClearMarks))(a0);
}

void Shared_InventoryItemGrid_ClearSlot(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_ClearSlot))(a0, a1);
}

void Shared_InventoryItemGrid_DisableSlotRange(void * a0, unsigned char a1, unsigned char a2) {
    ((void (*)(void *, unsigned char, unsigned char))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_DisableSlotRange))(a0, a1, a2);
}

void Shared_InventoryItemGrid_DrawExtraMarks(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_DrawExtraMarks))(a0, a1, a2);
}

void Shared_InventoryItemGrid_Exit(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_Exit))(a0);
}

unsigned int Shared_InventoryItemGrid_FindBoxSlotAt(void * a0, int a1, int a2) {
    return ((unsigned int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_FindBoxSlotAt))(a0, a1, a2);
}

unsigned short Shared_InventoryItemGrid_GetSlotItem(void * a0, int a1) {
    return ((unsigned short (*)(void *, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_GetSlotItem))(a0, a1);
}

int Shared_InventoryItemGrid_HitTestSlot21(void * a0, int a1, int a2) {
    return ((int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_HitTestSlot21))(a0, a1, a2);
}

int Shared_InventoryItemGrid_IsSlotDisabled(void * a0, int a1) {
    return ((int (*)(void *, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_IsSlotDisabled))(a0, a1);
}

void Shared_InventoryItemGrid_LoadPockets(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_LoadPockets))(a0);
}

void Shared_InventoryItemGrid_SetCursorSlot(void * a0, unsigned int a1) {
    ((void (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_SetCursorSlot))(a0, a1);
}

void Shared_InventoryItemGrid_SetHeldItem(void * a0, unsigned int a1, int a2) {
    ((void (*)(void *, unsigned int, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_SetHeldItem))(a0, a1, a2);
}

void Shared_InventoryItemGrid_ShowSlotName(void * a0, void * a1, int a2) {
    ((void (*)(void *, void *, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_ShowSlotName))(a0, a1, a2);
}

void Shared_InventoryItemGrid_StartPresentAnim(void * a0, unsigned int a1, int a2) {
    ((void (*)(void *, unsigned int, int))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_StartPresentAnim))(a0, a1, a2);
}

int Shared_InventoryItemGrid_UpdatePresentAnim(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_InventoryItemGrid_UpdatePresentAnim))(a0);
}

void Shared_Inventory_PlayPickUpSe(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_Inventory_PlayPickUpSe))();
}

void Shared_Keyboard_ClearHighlight(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_ClearHighlight))(a0);
}

int Shared_Keyboard_DeleteRange(void * a0, void * a1, int a2, int a3, int a4) {
    return ((int (*)(void *, void *, int, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_DeleteRange))(a0, a1, a2, a3, a4);
}

void Shared_Keyboard_DisableModifierKeys(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_DisableModifierKeys))(a0);
}

void Shared_Keyboard_DrawCopyPasteKeys(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_DrawCopyPasteKeys))(a0, a1, a2);
}

void Shared_Keyboard_DrawCopyPasteKeysChat(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_DrawCopyPasteKeysChat))(a0, a1, a2);
}

void Shared_Keyboard_EnableKey(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_EnableKey))(a0, a1);
}

void Shared_Keyboard_EnterTabRowAtX(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_EnterTabRowAtX))(a0, a1);
}

void Shared_Keyboard_EnterTabRowAtX2(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_EnterTabRowAtX2))(a0, a1);
}

int Shared_Keyboard_GetSelectedEmotion(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_GetSelectedEmotion))(a0);
}

unsigned char Shared_Keyboard_GetTypedRunLength(void * a0) {
    return ((unsigned char (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_GetTypedRunLength))(a0);
}

int Shared_Keyboard_HandleModeKey(void * a0, int a1, int a2) {
    return ((int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_HandleModeKey))(a0, a1, a2);
}

void Shared_Keyboard_HighlightKey(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_HighlightKey))(a0, a1);
}

int Shared_Keyboard_InsertCharMultiline(void * a0, void * a1, int a2, void * a3, int a4, int a5, int a6, int a7, int a8, int a9) {
    return ((int (*)(void *, void *, int, void *, int, int, int, int, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_InsertCharMultiline))(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

int Shared_Keyboard_IsOnButtonKey(void * a0, int a1) {
    return ((int (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_IsOnButtonKey))(a0, a1);
}

void Shared_Keyboard_LoadEmotionIcons(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_LoadEmotionIcons))(a0);
}

void Shared_Keyboard_LoadLetterChars(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_LoadLetterChars))(a0, a1);
}

void Shared_Keyboard_MarkScreenDirty(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_MarkScreenDirty))(a0);
}

int Shared_Keyboard_ModifyCharKey104(void * a0, int a1) {
    return ((int (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_ModifyCharKey104))(a0, a1);
}

void Shared_Keyboard_PlayCopySe(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_Keyboard_PlayCopySe))();
}

int Shared_Keyboard_PressCursorKey(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_PressCursorKey))(a0);
}

void Shared_Keyboard_Reload(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_Reload))(a0, a1);
}

int Shared_Keyboard_ReplaceCharBeforeCursor(void * a0, void * a1, int a2, int a3) {
    return ((int (*)(void *, void *, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_ReplaceCharBeforeCursor))(a0, a1, a2, a3);
}

void Shared_Keyboard_ResetTypedRun(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_ResetTypedRun))(a0);
}

void Shared_Keyboard_RestoreLastPage(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_RestoreLastPage))(a0, a1);
}

void Shared_Keyboard_SelectEmotionByCode(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_Keyboard_SelectEmotionByCode))(a0, a1);
}

void Shared_Keyboard_SelectSendKey(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_SelectSendKey))(a0);
}

void Shared_Keyboard_SetTextFieldPos(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_Keyboard_SetTextFieldPos))(a0, a1, a2);
}

int Shared_Keyboard_TickKeyRepeat(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_Keyboard_TickKeyRepeat))(a0);
}

int Shared_Keyboard_TouchKey(void * a0, int a1, unsigned int a2) {
    return ((int (*)(void *, int, unsigned int))Modern_SharedResolve(&gSharedCall_Keyboard_TouchKey))(a0, a1, a2);
}

int Shared_Keyboard_TouchSendKey(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_Keyboard_TouchSendKey))();
}

int Shared_LetterGrid_GetSlotY(void * a0, int a1) {
    return ((int (*)(void *, int))Modern_SharedResolve(&gSharedCall_LetterGrid_GetSlotY))(a0, a1);
}

void Shared_LetterGrid_LoadPocketLetters(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_LetterGrid_LoadPocketLetters))(a0);
}

void Shared_LetterGrid_SetLetters0A(void * a0, void * a1) {
    ((void (*)(void *, void *))Modern_SharedResolve(&gSharedCall_LetterGrid_SetLetters0A))(a0, a1);
}

void Shared_LetterGrid_SetLetters2D(void * a0, void * a1) {
    ((void (*)(void *, void *))Modern_SharedResolve(&gSharedCall_LetterGrid_SetLetters2D))(a0, a1);
}

int Shared_LetterGrid_UpdatePopAnim(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_LetterGrid_UpdatePopAnim))(a0);
}

int Shared_LocalWl_SetEventCallback(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_LocalWl_SetEventCallback))(a0);
}

void Shared_NumberPad_Draw(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_NumberPad_Draw))(a0, a1);
}

void Shared_NumberPad_DrawKeypadFrame(int a0) {
    ((void (*)(int))Modern_SharedResolve(&gSharedCall_NumberPad_DrawKeypadFrame))(a0);
}

unsigned int Shared_NumberPad_GetCursorX(void * a0) {
    return ((unsigned int (*)(void *))Modern_SharedResolve(&gSharedCall_NumberPad_GetCursorX))(a0);
}

int Shared_NumberPad_GetValue(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_NumberPad_GetValue))(a0);
}

unsigned int Shared_NumberPad_HitTestKey(void * a0, int a1, int a2) {
    return ((unsigned int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_NumberPad_HitTestKey))(a0, a1, a2);
}

int Shared_NumberPad_IsCursorOnButton(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_NumberPad_IsCursorOnButton))(a0);
}

void Shared_NumberPad_PlayCancelSe(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_NumberPad_PlayCancelSe))();
}

int Shared_NumberPad_PressCursorKey(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_NumberPad_PressCursorKey))(a0);
}

void Shared_NumberPad_SetAmounts(void * a0, int a1, int a2, int a3) {
    ((void (*)(void *, int, int, int))Modern_SharedResolve(&gSharedCall_NumberPad_SetAmounts))(a0, a1, a2, a3);
}

void Shared_PlayerActor_EndAct3C(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_PlayerActor_EndAct3C))(a0, a1);
}

void Shared_PlayerActor_EndFillHole(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_EndFillHole))(a0);
}

void Shared_PlayerActor_EndFishWait(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_PlayerActor_EndFishWait))(a0, a1);
}

void Shared_PlayerActor_EndShovelStrike(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_EndShovelStrike))(a0);
}

void Shared_PlayerActor_EndTreeShake(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_EndTreeShake))(a0);
}

void Shared_PlayerActor_EndUmbrellaSpin(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_EndUmbrellaSpin))(a0);
}

void * Shared_PlayerActor_GetTrackTarget(unsigned int a0) {
    return ((void * (*)(unsigned int))Modern_SharedResolve(&gSharedCall_PlayerActor_GetTrackTarget))(a0);
}

int Shared_PlayerActor_LocalEndWatch(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_PlayerActor_LocalEndWatch))();
}

int Shared_PlayerActor_LocalRequestDoorApproach(void * a0, void * a1, void * a2) {
    return ((int (*)(void *, void *, void *))Modern_SharedResolve(&gSharedCall_PlayerActor_LocalRequestDoorApproach))(a0, a1, a2);
}

void Shared_PlayerActor_MainAct5C(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_MainAct5C))(a0);
}

void Shared_PlayerActor_MainMailboxWait(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_MainMailboxWait))(a0);
}

void Shared_PlayerActor_MainReleaseCreature(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_MainReleaseCreature))(a0);
}

void Shared_PlayerActor_MainShovelStrike(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_MainShovelStrike))(a0);
}

void Shared_PlayerActor_MainThrowBottle(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_MainThrowBottle))(a0);
}

void Shared_PlayerActor_NetAct12(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_PlayerActor_NetAct12))();
}

int Shared_PlayerActor_NetAct82(void * a0, int a1) {
    return ((int (*)(void *, int))Modern_SharedResolve(&gSharedCall_PlayerActor_NetAct82))(a0, a1);
}

void Shared_PlayerActor_NetAxeBreak(void * a0, short a1) {
    ((void (*)(void *, short))Modern_SharedResolve(&gSharedCall_PlayerActor_NetAxeBreak))(a0, a1);
}

int Shared_PlayerActor_NetAxeFollowThrough(void * a0, short a1) {
    return ((int (*)(void *, short))Modern_SharedResolve(&gSharedCall_PlayerActor_NetAxeFollowThrough))(a0, a1);
}

void Shared_PlayerActor_NetFishWait(void * a0, short a1) {
    ((void (*)(void *, short))Modern_SharedResolve(&gSharedCall_PlayerActor_NetFishWait))(a0, a1);
}

void Shared_PlayerActor_NetFtrPushMove(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_PlayerActor_NetFtrPushMove))();
}

int Shared_PlayerActor_RequestAct3C(void * a0, int a1, int a2) {
    return ((int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_PlayerActor_RequestAct3C))(a0, a1, a2);
}

int Shared_PlayerActor_RoomInteractAt(void * a0, int a1, int a2) {
    return ((int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_PlayerActor_RoomInteractAt))(a0, a1, a2);
}

void Shared_PlayerActor_SetupAct3C(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_SetupAct3C))(a0);
}

void Shared_PlayerActor_SetupAxeFollowThrough(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_SetupAxeFollowThrough))(a0);
}

void Shared_PlayerActor_SetupFirework(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_SetupFirework))(a0);
}

void Shared_PlayerActor_SetupFishEscape(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PlayerActor_SetupFishEscape))(a0);
}

void Shared_PlayerActor_SetupStorageClose(void * a0, void * a1) {
    ((void (*)(void *, void *))Modern_SharedResolve(&gSharedCall_PlayerActor_SetupStorageClose))(a0, a1);
}

void Shared_PlayerActor_SetupTreeShakeRelease(void * a0, void * a1) {
    ((void (*)(void *, void *))Modern_SharedResolve(&gSharedCall_PlayerActor_SetupTreeShakeRelease))(a0, a1);
}

int Shared_PocketMenu_CanEditRoom(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_PocketMenu_CanEditRoom))();
}

unsigned int Shared_PocketMenu_GetPlayerSlot(void) {
    return ((unsigned int (*)(void))Modern_SharedResolve(&gSharedCall_PocketMenu_GetPlayerSlot))();
}

void Shared_PocketMenu_SetSlotItem(void * a0, unsigned int a1, unsigned int a2, unsigned int a3) {
    ((void (*)(void *, unsigned int, unsigned int, unsigned int))Modern_SharedResolve(&gSharedCall_PocketMenu_SetSlotItem))(a0, a1, a2, a3);
}

void Shared_PocketMenu_StartRemoveBlink(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PocketMenu_StartRemoveBlink))(a0);
}

void Shared_PopupChoice_Update(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_PopupChoice_Update))(a0);
}

void Shared_RoomObjTex_Construct(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_RoomObjTex_Construct))(a0);
}

int Shared_Room_PickRandomWalkTarget(void * a0, void * a1, int a2) {
    return ((int (*)(void *, void *, int))Modern_SharedResolve(&gSharedCall_Room_PickRandomWalkTarget))(a0, a1, a2);
}

int Shared_Sock_Bind(long a0, void * a1) {
    return ((int (*)(long, void *))Modern_SharedResolve(&gSharedCall_Sock_Bind))(a0, a1);
}

int Shared_Sock_Startup(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_Sock_Startup))(a0);
}

int Shared_SpNpcKappn_GetAnimState(void) {
    return ((int (*)(void))Modern_SharedResolve(&gSharedCall_SpNpcKappn_GetAnimState))();
}

void Shared_StarSky_CancelUpload(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_StarSky_CancelUpload))(a0);
}

void Shared_StarSky_DrawArrows(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_StarSky_DrawArrows))(a0, a1, a2);
}

int Shared_StarSky_FindConstellationByLine(unsigned short a0) {
    return ((int (*)(unsigned short))Modern_SharedResolve(&gSharedCall_StarSky_FindConstellationByLine))(a0);
}

int Shared_StarSky_HitArrow(void * a0, int a1, int a2) {
    return ((int (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_StarSky_HitArrow))(a0, a1, a2);
}

int Shared_StarSky_IsConstellationFree(void * a0) {
    return ((int (*)(void *))Modern_SharedResolve(&gSharedCall_StarSky_IsConstellationFree))(a0);
}

void Shared_StarSky_RebuildScreen(void * a0, unsigned int a1, int a2) {
    ((void (*)(void *, unsigned int, int))Modern_SharedResolve(&gSharedCall_StarSky_RebuildScreen))(a0, a1, a2);
}

int Shared_StarSky_ScreenToCell(void * a0, int a1, int a2, void * a3, void * a4) {
    return ((int (*)(void *, int, int, void *, void *))Modern_SharedResolve(&gSharedCall_StarSky_ScreenToCell))(a0, a1, a2, a3, a4);
}

int Shared_StarSky_ScreenToCellInScope(void * a0, int a1, int a2, void * a3, void * a4) {
    return ((int (*)(void *, int, int, void *, void *))Modern_SharedResolve(&gSharedCall_StarSky_ScreenToCellInScope))(a0, a1, a2, a3, a4);
}

void Shared_StarSky_ScrollInDir(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_StarSky_ScrollInDir))(a0, a1, a2);
}

void Shared_StarSky_ScrollX(void * a0, int a1) {
    ((void (*)(void *, int))Modern_SharedResolve(&gSharedCall_StarSky_ScrollX))(a0, a1);
}

void Shared_StarSky_SetScroll(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_StarSky_SetScroll))(a0, a1, a2);
}

void Shared_StarSky_SetScrollTarget(void * a0, int a1, int a2) {
    ((void (*)(void *, int, int))Modern_SharedResolve(&gSharedCall_StarSky_SetScrollTarget))(a0, a1, a2);
}

void Shared_TownMapImage_AllocGlobal(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_TownMapImage_AllocGlobal))();
}

void Shared_TownMapImage_BuildMarkersGlobal(unsigned int a0) {
    ((void (*)(unsigned int))Modern_SharedResolve(&gSharedCall_TownMapImage_BuildMarkersGlobal))(a0);
}

void Shared_TownMapImage_FinishGlobal(void * a0, void * a1) {
    ((void (*)(void *, void *))Modern_SharedResolve(&gSharedCall_TownMapImage_FinishGlobal))(a0, a1);
}

void Shared_TownMapMarkers_Clear(void * a0) {
    ((void (*)(void *))Modern_SharedResolve(&gSharedCall_TownMapMarkers_Clear))(a0);
}

void * Shared_TownMapMarkers_Get(void * a0, unsigned int a1) {
    return ((void * (*)(void *, unsigned int))Modern_SharedResolve(&gSharedCall_TownMapMarkers_Get))(a0, a1);
}

void Shared_Wlx_StartExchange(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_Wlx_StartExchange))();
}

void Shared_Wlx_Stop(void) {
    ((void (*)(void))Modern_SharedResolve(&gSharedCall_Wlx_Stop))();
}

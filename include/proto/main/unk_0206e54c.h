#ifndef PROTO_PROTO_MAIN_UNK_0206E54C_H
#define PROTO_PROTO_MAIN_UNK_0206E54C_H


#include "types.h"
#include "sys/ListNode.h"
#include "sys/ProcProfile.h"
#ifdef __cplusplus
#include "item/Letter.h"
#include "sys/ProcBase.h"
class MenuManager;
class Unk_021cb4f0;
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifndef PROTO_LOCAL_CommSub_StartCountdown
void CommSub_StartCountdown(u8 *o);
#endif
#ifndef PROTO_LOCAL_CommSub_RecvClearPendingUnit
void CommSub_RecvClearPendingUnit(u8 *o);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_AddOpenMenu
void MenuCtrl_AddOpenMenu(ListNode *v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_RemoveOpenMenu
void MenuCtrl_RemoveOpenMenu(ListNode *o);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ReleaseClosedMenus
void MenuCtrl_ReleaseClosedMenus();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_CreateRequestedMenu
BOOL MenuCtrl_CreateRequestedMenu();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_LoadRequestedOverlays
BOOL MenuCtrl_LoadRequestedOverlays();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ReleaseOverlays
BOOL MenuCtrl_ReleaseOverlays(u32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ResetFlags
void MenuCtrl_ResetFlags();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsIdle
BOOL MenuCtrl_IsIdle();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsMenuOpen
BOOL MenuCtrl_IsMenuOpen();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_RequestOpen
BOOL MenuCtrl_RequestOpen(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_RequestOpenNested
BOOL MenuCtrl_RequestOpenNested(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_RequestOpenMenu12
BOOL MenuCtrl_RequestOpenMenu12(void *v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsLoaded
BOOL MenuCtrl_IsLoaded(s32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetLoaded
void MenuCtrl_SetLoaded(s32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearLoaded
void MenuCtrl_ClearLoaded(s32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsReleasePending
BOOL MenuCtrl_IsReleasePending(s32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetReleasePending
void MenuCtrl_SetReleasePending(s32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearReleasePending
void MenuCtrl_ClearReleasePending(s32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetFlags
void MenuCtrl_SetFlags(u32 m);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearFlags
void MenuCtrl_ClearFlags(u32 m);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_HasFlags
BOOL MenuCtrl_HasFlags(u32 m);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearMenuOnTop
void MenuCtrl_ClearMenuOnTop();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetMenuOnTop
void MenuCtrl_SetMenuOnTop();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsMenuOnTop
BOOL MenuCtrl_IsMenuOnTop();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetTouch
void MenuCtrl_SetTouch();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetButtons
void MenuCtrl_SetButtons();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsTouch
BOOL MenuCtrl_IsTouch();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsButtons
BOOL MenuCtrl_IsButtons();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SyncFromInputMode
void MenuCtrl_SyncFromInputMode();
#endif
#ifndef PROTO_LOCAL_Menu_GetIconCharIndex
s32 Menu_GetIconCharIndex(s32 v);
#endif
#ifndef PROTO_LOCAL_BgScreen_SetRectPalette
void BgScreen_SetRectPalette(u16 *tbl, s32 x0, s32 y0, s32 x1, s32 y1, u32 to);
#endif
#ifndef PROTO_LOCAL_BgScreen_ReplaceRectPalette
void BgScreen_ReplaceRectPalette(u16 *tbl, s32 x0, s32 y0, s32 x1, s32 y1, u32 from, u32 to);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetTransitionProgress
void MenuCtrl_SetTransitionProgress(s32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetTransitionProgress
s32 MenuCtrl_GetTransitionProgress();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetTransitionProgressOrFull
s32 MenuCtrl_GetTransitionProgressOrFull();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsTransitionActive
BOOL MenuCtrl_IsTransitionActive();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetTransitionActive
void MenuCtrl_SetTransitionActive();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearTransitionActive
void MenuCtrl_ClearTransitionActive();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsScreenChanging
BOOL MenuCtrl_IsScreenChanging();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetScreenChanging
void MenuCtrl_SetScreenChanging();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearScreenChanging
void MenuCtrl_ClearScreenChanging();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetArg
void *MenuCtrl_GetArg();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetArg
void MenuCtrl_SetArg(void *v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetMode
u32 MenuCtrl_GetMode();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetMode
void MenuCtrl_SetMode(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetIndex
u32 MenuCtrl_GetIndex();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetIndex
void MenuCtrl_SetIndex(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsResultOk
BOOL MenuCtrl_IsResultOk();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsResultDuplicateName
BOOL MenuCtrl_IsResultDuplicateName();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetResult
void MenuCtrl_SetResult(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetText
void *MenuCtrl_GetText();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetText
void MenuCtrl_SetText(const void *a, u32 b);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenLauncher
BOOL MenuCtrl_OpenLauncher(u32 a);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenLauncherWithIndex
BOOL MenuCtrl_OpenLauncherWithIndex(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsFinished
BOOL MenuCtrl_IsFinished();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearSavedSlot
void MenuCtrl_ClearSavedSlot();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetSavedSlot
void MenuCtrl_SetSavedSlot(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetSavedSlot
u32 MenuCtrl_GetSavedSlot();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_BackupPockets
void MenuCtrl_BackupPockets();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_RestorePockets
void MenuCtrl_RestorePockets();
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetChosenItems
void MenuCtrl_SetChosenItems(u16 *src);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetChosenItems
u16 *MenuCtrl_GetChosenItems(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ReturnChosenItems
void MenuCtrl_ReturnChosenItems(BOOL returnItems);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ReplaceBackupItem
void MenuCtrl_ReplaceBackupItem(u32 key, u16 val);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenPocketSelect
BOOL MenuCtrl_OpenPocketSelect(u32 a, u32 b);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_BuildPocketMask
u16 MenuCtrl_BuildPocketMask(BOOL (*cb)(u16 *, s32));
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPocketSelectMask
u16 MenuCtrl_GetPocketSelectMask(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPocketSelectLabel
u8 MenuCtrl_GetPocketSelectLabel(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenPostOffice
BOOL MenuCtrl_OpenPostOffice(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetPostOfficeResult
void MenuCtrl_SetPostOfficeResult(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetFutureLetter
void MenuCtrl_SetFutureLetter(void *a);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_StoreFutureLetter
void MenuCtrl_StoreFutureLetter(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ReturnFutureLetter
void MenuCtrl_ReturnFutureLetter(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPostOfficeOutcome
u32 MenuCtrl_GetPostOfficeOutcome(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_PostOfficeHadBadAddress
BOOL MenuCtrl_PostOfficeHadBadAddress(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPostOfficeFullMailboxes
u8 MenuCtrl_GetPostOfficeFullMailboxes(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_PostOfficeWasRejected
BOOL MenuCtrl_PostOfficeWasRejected(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_PostOfficeHadNoLetter
BOOL MenuCtrl_PostOfficeHadNoLetter(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_PostOfficeLettersSent
BOOL MenuCtrl_PostOfficeLettersSent(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetHandBells
u32 MenuCtrl_GetHandBells(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetHandBells
void MenuCtrl_SetHandBells(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetAmount
u32 MenuCtrl_GetAmount(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetAmount
void MenuCtrl_SetAmount(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetDateTime
void MenuCtrl_SetDateTime(void *a);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetDateTime
void MenuCtrl_GetDateTime(void *a);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenNearbyTowns
BOOL MenuCtrl_OpenNearbyTowns(void *a, void *b);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearPtrArgs
void MenuCtrl_ClearPtrArgs(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPtrArg0
void *MenuCtrl_GetPtrArg0(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPtrArg1
void *MenuCtrl_GetPtrArg1(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsClockMovedBack
BOOL MenuCtrl_IsClockMovedBack(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsClockMovedForward
BOOL MenuCtrl_IsClockMovedForward(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsClockEdited
BOOL MenuCtrl_IsClockEdited(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetClockMovedBack
void MenuCtrl_SetClockMovedBack(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetClockMovedForward
void MenuCtrl_SetClockMovedForward(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetClockEdited
void MenuCtrl_SetClockEdited(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearClockChangeFlags
void MenuCtrl_ClearClockChangeFlags(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenPocketsFullInsect
BOOL MenuCtrl_OpenPocketsFullInsect(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenPocketsFullFish
BOOL MenuCtrl_OpenPocketsFullFish(u32 a, void *b);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenPocketsFullPickUp
BOOL MenuCtrl_OpenPocketsFullPickUp(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenPocketsFullDug
BOOL MenuCtrl_OpenPocketsFullDug(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetPocketsFullItem
u16 MenuCtrl_GetPocketsFullItem(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetPocketsFullItem
void MenuCtrl_SetPocketsFullItem(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetCatalogItem
void MenuCtrl_SetCatalogItem(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetCatalogItem
u16 MenuCtrl_GetCatalogItem(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetSongItem
void MenuCtrl_SetSongItem(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetSongItem
u16 MenuCtrl_GetSongItem(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_OpenLauncherWithText
BOOL MenuCtrl_OpenLauncherWithText(u32 a, const void *b, u32 c);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_InitKeyboardState
void MenuCtrl_InitKeyboardState(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetKeyboardPage
u8 MenuCtrl_GetKeyboardPage(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetKeyboardPage
void MenuCtrl_SetKeyboardPage(u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetKeyboardPageMode
u8 MenuCtrl_GetKeyboardPageMode(u32 i);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetKeyboardPageMode
void MenuCtrl_SetKeyboardPageMode(u32 i, u32 v);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_RequestForceClose
void MenuCtrl_RequestForceClose(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ResetForceClose
void MenuCtrl_ResetForceClose(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_TickForceClose
void MenuCtrl_TickForceClose(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsForceCloseDue
s32 MenuCtrl_IsForceCloseDue(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetSyncMsgMenu
void MenuCtrl_SetSyncMsgMenu(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearSyncMsgMenu
void MenuCtrl_ClearSyncMsgMenu(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsSyncMsgMenu
BOOL MenuCtrl_IsSyncMsgMenu(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_IsFriendPageFromIndex
BOOL MenuCtrl_IsFriendPageFromIndex(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetFriendPageFromIndex
void MenuCtrl_SetFriendPageFromIndex(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearFriendPageFromIndex
void MenuCtrl_ClearFriendPageFromIndex(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_GetChatDraft
void *MenuCtrl_GetChatDraft(void);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_SetChatDraft
void MenuCtrl_SetChatDraft(const void *a);
#endif
#ifndef PROTO_LOCAL_MenuCtrl_ClearChatDraft
void MenuCtrl_ClearChatDraft(void);
#endif
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#ifndef PROTO_LOCAL_MenuManager_Create
MenuManager *MenuManager_Create();
#endif
}
#ifndef PROTO_LOCAL_sMenuIndex
extern u8 sMenuIndex;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList18
extern u32 kMenuOverlayList18[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList28
extern u32 kMenuOverlayList28[3];
#endif
#ifndef PROTO_LOCAL_sOpenMenuList
extern List sOpenMenuList;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList03
extern u32 kMenuOverlayList03[2];
#endif
#ifndef PROTO_LOCAL_sMenuMode
extern u8 sMenuMode;
#endif
#ifndef PROTO_LOCAL_sFutureLetter
extern Letter sFutureLetter;
#endif
#ifndef PROTO_LOCAL_sPocketBackupItems
extern u16 sPocketBackupItems[16];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList06
extern u32 kMenuOverlayList06[3];
#endif
#ifndef PROTO_LOCAL_sMenuArg
extern void *sMenuArg;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList13
extern u32 kMenuOverlayList13[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList23
extern u32 kMenuOverlayList23[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList1A
extern u32 kMenuOverlayList1A[3];
#endif
#ifndef PROTO_LOCAL_sMenuTransitionProgress
extern s32 sMenuTransitionProgress;
#endif
#ifndef PROTO_LOCAL_sMenuPtrArg1
extern void *sMenuPtrArg1;
#endif
#ifndef PROTO_LOCAL_sChatDraft
extern u8 sChatDraft[32];
#endif
#ifndef PROTO_LOCAL_sMenuHandBells
extern u32 sMenuHandBells;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList2A
extern u32 kMenuOverlayList2A[3];
#endif
#ifndef PROTO_LOCAL_sMenuManagerProfile
extern ProcProfile sMenuManagerProfile;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList00
extern u32 kMenuOverlayList00[2];
#endif
#ifndef PROTO_LOCAL_sMenuSavedSlot
extern u8 sMenuSavedSlot;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList2D
extern u32 kMenuOverlayList2D[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList1B
extern u32 kMenuOverlayList1B[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList2B
extern u32 kMenuOverlayList2B[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList08
extern u32 kMenuOverlayList08[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList0A
extern u32 kMenuOverlayList0A[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList17
extern u32 kMenuOverlayList17[3];
#endif
#ifndef PROTO_LOCAL_sPocketSelectLabel
extern u8 sPocketSelectLabel;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList0D
extern u32 kMenuOverlayList0D[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList04
extern u32 kMenuOverlayList04[4];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList0B
extern u32 kMenuOverlayList0B[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList05
extern u32 kMenuOverlayList05[4];
#endif
#ifndef PROTO_LOCAL_sKeyboardPageModes
extern u8 sKeyboardPageModes[4];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList25
extern u32 kMenuOverlayList25[2];
#endif
#ifndef PROTO_LOCAL_sPocketSelectMask
extern u16 sPocketSelectMask;
#endif
#ifndef PROTO_LOCAL_sForceCloseDelay
extern u8 sForceCloseDelay;
#endif
#ifndef PROTO_LOCAL_sKeyboardPage
extern u8 sKeyboardPage;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList15
extern u32 kMenuOverlayList15[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList09
extern u32 kMenuOverlayList09[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList0F
extern u32 kMenuOverlayList0F[4];
#endif
#ifndef PROTO_LOCAL_sMenuReleaseMask
extern u32 sMenuReleaseMask[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList29
extern u32 kMenuOverlayList29[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList2C
extern u32 kMenuOverlayList2C[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList01
extern u32 kMenuOverlayList01[4];
#endif
#ifndef PROTO_LOCAL_sMenuLoadedMask
extern u32 sMenuLoadedMask[3];
#endif
#ifndef PROTO_LOCAL_sMenuFlags
extern u16 sMenuFlags;
#endif
#ifndef PROTO_LOCAL_sMenuChosenItems
extern u16 sMenuChosenItems[16];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList1C
extern u32 kMenuOverlayList1C[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList1E
extern u32 kMenuOverlayList1E[3];
#endif
#ifndef PROTO_LOCAL_sMenuText
extern u8 sMenuText[16];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList1F
extern u32 kMenuOverlayList1F[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList07
extern u32 kMenuOverlayList07[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList0C
extern u32 kMenuOverlayList0C[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList21
extern u32 kMenuOverlayList21[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList22
extern u32 kMenuOverlayList22[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList0E
extern u32 kMenuOverlayList0E[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList11
extern u32 kMenuOverlayList11[3];
#endif
#ifndef PROTO_LOCAL_gMenuManager
extern GameProc *gMenuManager;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList14
extern u32 kMenuOverlayList14[3];
#endif
#ifndef PROTO_LOCAL_sPostOfficeResult
extern u16 sPostOfficeResult;
#endif
#ifndef PROTO_LOCAL_sMenuDateTime
extern Unk_021cb4f0 sMenuDateTime;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList02
extern u32 kMenuOverlayList02[4];
#endif
#ifndef PROTO_LOCAL_sMenuItem
extern u16 sMenuItem;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList19
extern u32 kMenuOverlayList19[3];
#endif
#ifndef PROTO_LOCAL_sMenuPtrArg0
extern void *sMenuPtrArg0;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList20
extern u32 kMenuOverlayList20[3];
#endif
#ifndef PROTO_LOCAL_sMenuAmount
extern u32 sMenuAmount;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList10
extern u32 kMenuOverlayList10[3];
#endif
#ifndef PROTO_LOCAL_sMenuResult
extern u8 sMenuResult;
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList16
extern u32 kMenuOverlayList16[3];
#endif
#ifndef PROTO_LOCAL_sMenuRequest
extern u8 sMenuRequest[4];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList26
extern u32 kMenuOverlayList26[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList24
extern u32 kMenuOverlayList24[2];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayLists
extern u32 *kMenuOverlayLists[46];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList12
extern u32 kMenuOverlayList12[3];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList27
extern u32 kMenuOverlayList27[2];
#endif
#ifndef PROTO_LOCAL_sPocketBackupFlags
extern u8 sPocketBackupFlags[16];
#endif
#ifndef PROTO_LOCAL_kMenuProfileIds
extern u16 kMenuProfileIds[46];
#endif
#ifndef PROTO_LOCAL_kMenuOverlayList1D
extern u32 kMenuOverlayList1D[3];
#endif
#endif

#endif

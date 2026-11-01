#include "uptr.h"
#include "host_tick.h"
#include "types.h"
#include "menu/MenuProc.h"
#include "sys/ListNode.h"
#include "Unk_020d8c7c.h"
#include "item/Letter.h"
#include "sys/ProcProfile.h"
#include "item/FutureLetter.h"
#include "player/PlayerData.h"
#include "player/PlayerInventory.h"
#include "sys/ClockDateTime.h"
#include "proto/autoload_2/unk_020e7500.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/main/unk_020116e0.h"
#include "proto/main/unk_0202e840.h"
#include "proto/main/unk_0203cbc0.h"
#include "proto/main/unk_0204eeb4.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206db88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f4f0.h"
#include "proto/main/unk_0208eeac.h"
#include "proto/main/unk_02096c10.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_0209c390.h"
#include "proto/main/unk_020b7d84.h"


extern "C" void func_020044dc();
class Unk_021cb4f0 {
public:
    Unk_021cb4f0() {
        w.words[0] = 0;
        w.words[1] = 0;
    }
    ~Unk_021cb4f0() { func_020044dc(); }
    ClockDateTimeWords w;
};

class MenuManager : public GameProc {
public:
    MenuManager() {}
    BOOL onCreate();
    BOOL onDelete();
    BOOL onExecute();
    BOOL onDraw();
};

extern "C" {

extern u16 gPad[];

void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 Scene_GetCurrent();
BOOL TalkRequest_IsActive();
void TalkRequest_AddMenu(u32);
void PrioList_Init(List *list);
void PendingUnit_ClearActiveOfAid(u32);
}


u8 sMenuIndex;
u32 kMenuOverlayList18[3] = {0x6b, 0x5e, 0xffffffff};
u32 kMenuOverlayList28[3] = {0x6c, 0x5e, 0xffffffff};
List sOpenMenuList;
u32 kMenuOverlayList03[2] = {0x79, 0xffffffff};
u8 sMenuMode;
Letter sFutureLetter;
u16 sPocketBackupItems[16];
u32 kMenuOverlayList06[3] = {0x6f, 0x5f, 0xffffffff};
void *sMenuArg;
u32 kMenuOverlayList13[3] = {0x66, 0x5e, 0xffffffff};
u32 kMenuOverlayList23[2] = {0x8e, 0xffffffff};
u32 kMenuOverlayList1A[3] = {0x81, 0x7f, 0xffffffff};
s32 sMenuTransitionProgress;
void *sMenuPtrArg1;
u8 sChatDraft[32];
u32 sMenuHandBells;
u32 kMenuOverlayList2A[3] = {0x8a, 0x86, 0xffffffff};
ProcProfile sMenuManagerProfile = {(void *(*)())MenuManager_Create, 0x8e, 0x92};
u32 kMenuOverlayList00[2] = {0x5a, 0xffffffff};
u8 sMenuSavedSlot;
u32 kMenuOverlayList2D[2] = {0x92, 0xffffffff};
u32 kMenuOverlayList1B[3] = {0x78, 0x75, 0xffffffff};
u32 kMenuOverlayList2B[3] = {0x85, 0x82, 0xffffffff};
u32 kMenuOverlayList08[3] = {0x7a, 0x5f, 0xffffffff};
u32 kMenuOverlayList0A[3] = {0x70, 0x5f, 0xffffffff};
u32 kMenuOverlayList17[3] = {0x6a, 0x5e, 0xffffffff};
u8 sPocketSelectLabel;
u32 kMenuOverlayList0D[2] = {0x7b, 0xffffffff};
u32 kMenuOverlayList04[4] = {0x73, 0x72, 0x5e, 0xffffffff};
u32 kMenuOverlayList0B[2] = {0x71, 0xffffffff};
u32 kMenuOverlayList05[4] = {0x74, 0x72, 0x5e, 0xffffffff};
u8 sKeyboardPageModes[4];
u32 kMenuOverlayList25[2] = {0x8f, 0xffffffff};
u16 sPocketSelectMask;
u8 sForceCloseDelay;
u8 sKeyboardPage;
u32 kMenuOverlayList15[3] = {0x68, 0x5e, 0xffffffff};
u32 kMenuOverlayList09[2] = {0x5c, 0xffffffff};
u32 kMenuOverlayList0F[4] = {0x7c, 0x7e, 0x5f, 0xffffffff};
u32 sMenuReleaseMask[3];
u32 kMenuOverlayList29[3] = {0x6d, 0x5e, 0xffffffff};
u32 kMenuOverlayList2C[3] = {0x6e, 0x5e, 0xffffffff};
u32 kMenuOverlayList01[4] = {0x60, 0x61, 0x5e, 0xffffffff};
u32 sMenuLoadedMask[3];
u16 sMenuFlags;
u16 sMenuChosenItems[16];
u32 kMenuOverlayList1C[3] = {0x87, 0x86, 0xffffffff};
u32 kMenuOverlayList1E[3] = {0x89, 0x86, 0xffffffff};
u8 sMenuText[16];
u32 kMenuOverlayList1F[3] = {0x83, 0x82, 0xffffffff};
u32 kMenuOverlayList07[3] = {0x76, 0x75, 0xffffffff};
u32 kMenuOverlayList0C[2] = {0x5b, 0xffffffff};
u32 kMenuOverlayList21[3] = {0x8c, 0x8b, 0xffffffff};
u32 kMenuOverlayList22[3] = {0x8d, 0x8b, 0xffffffff};
u32 kMenuOverlayList0E[3] = {0x7c, 0x7d, 0xffffffff};
u32 kMenuOverlayList11[3] = {0x64, 0x5e, 0xffffffff};
GameProc *gMenuManager;
u32 kMenuOverlayList14[3] = {0x67, 0x5e, 0xffffffff};
u16 sPostOfficeResult;
Unk_021cb4f0 sMenuDateTime;
u32 kMenuOverlayList02[4] = {0x60, 0x62, 0x5e, 0xffffffff};
u16 sMenuItem;
u32 kMenuOverlayList19[3] = {0x80, 0x7f, 0xffffffff};
void *sMenuPtrArg0;
u32 kMenuOverlayList20[3] = {0x84, 0x82, 0xffffffff};
u32 sMenuAmount;
u32 kMenuOverlayList10[3] = {0x63, 0x5e, 0xffffffff};
u8 sMenuResult;
u32 kMenuOverlayList16[3] = {0x69, 0x5e, 0xffffffff};
u8 sMenuRequest[4] = {0, 0x2e, 0, 0};
u32 kMenuOverlayList26[2] = {0x90, 0xffffffff};
u32 kMenuOverlayList24[2] = {0x77, 0xffffffff};
u32 *kMenuOverlayLists[46] = {
    kMenuOverlayList00, kMenuOverlayList01, kMenuOverlayList02, kMenuOverlayList03, kMenuOverlayList04, kMenuOverlayList05, kMenuOverlayList06,
    kMenuOverlayList07, kMenuOverlayList08, kMenuOverlayList09, kMenuOverlayList0A, kMenuOverlayList0B, kMenuOverlayList0C, kMenuOverlayList0D,
    kMenuOverlayList0E, kMenuOverlayList0F, kMenuOverlayList10, kMenuOverlayList11, kMenuOverlayList12, kMenuOverlayList13, kMenuOverlayList14,
    kMenuOverlayList15, kMenuOverlayList16, kMenuOverlayList17, kMenuOverlayList18, kMenuOverlayList19, kMenuOverlayList1A, kMenuOverlayList1B,
    kMenuOverlayList1C, kMenuOverlayList1D, kMenuOverlayList1E, kMenuOverlayList1F, kMenuOverlayList20, kMenuOverlayList21, kMenuOverlayList22,
    kMenuOverlayList23, kMenuOverlayList24, kMenuOverlayList25, kMenuOverlayList26, kMenuOverlayList27, kMenuOverlayList28, kMenuOverlayList29,
    kMenuOverlayList2A, kMenuOverlayList2B, kMenuOverlayList2C, kMenuOverlayList2D,
};
u32 kMenuOverlayList12[3] = {0x65, 0x5e, 0xffffffff};
u32 kMenuOverlayList27[2] = {0x91, 0xffffffff};
u8 sPocketBackupFlags[16];
u16 kMenuProfileIds[46] = {
    0x008f, 0x0091, 0x0091, 0x00a4, 0x009f, 0x00a0, 0x009e, 0x00a1, 0x00a5, 0x0090, 0x00a6, 0x00a7,
    0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099,
    0x009a, 0x00ac, 0x00ad, 0x00a3, 0x00ae, 0x00af, 0x00b0, 0x00b2, 0x00b3, 0x00b5, 0x00b6, 0x00b7,
    0x00a2, 0x00b8, 0x00b9, 0x00ba, 0x009b, 0x009c, 0x00b1, 0x00b4, 0x009d, 0x00bb,
};
u32 kMenuOverlayList1D[3] = {0x88, 0x86, 0xffffffff};

extern "C" void CommSub_StartCountdown(u8 *o) { HudCountdown_StartWithSe(o[0] - 0x12); }

extern "C" void CommSub_RecvClearPendingUnit(u8 *o) { PendingUnit_ClearActiveOfAid(o[1]); }

extern "C" MenuManager *MenuManager_Create() { return new MenuManager; }





BOOL MenuManager::onCreate() {
    MenuHeap_Create(0x8c00, 0);
    sMenuLoadedMask[0] = sMenuLoadedMask[1] = sMenuLoadedMask[2] = 0;
    sMenuReleaseMask[0] = sMenuReleaseMask[1] = sMenuReleaseMask[2] = 0;
    sMenuRequest[1] = 0x2e;
    sMenuRequest[0] = 1;
    gMenuManager = this;
    sMenuFlags = 0;
    MenuCtrl_ResetFlags();
    MenuScreen_ClearState();
    sMenuArg = 0;
    Text_BuildCharWidthTable();
    sMenuHandBells = 0;
    return TRUE;
}

BOOL MenuManager::onDelete() {
    sMenuReleaseMask[0] |= sMenuLoadedMask[0];
    sMenuReleaseMask[1] |= sMenuLoadedMask[1];
    sMenuReleaseMask[2] |= sMenuLoadedMask[2];
    MenuCtrl_ReleaseClosedMenus();
    MenuScreen_Reset();
    MenuHeap_Destroy();
    PrioList_Init(&sOpenMenuList);
    sMenuRequest[1] = 0x2e;
    sMenuRequest[0] = 0;
    gMenuManager = NULL;
    return TRUE;
}

BOOL MenuManager::onExecute() {
    u32 k;
    BOOL r;
    MenuCtrl_ReleaseClosedMenus();
    MenuCtrl_LoadRequestedOverlays();
    MenuCtrl_CreateRequestedMenu();
    MenuScreen_Update();
    if (Stub_ReturnFalse()) return TRUE;
    if (Scene_GetCurrent() == 6) return TRUE;
    if (gSoftResetRequested) return TRUE;
    if (TalkRequest_IsActive()) return TRUE;
    if (MenuCtrl_IsIdle()) {
        if (gTouchHeld && gTouchChanged) r = TRUE;
        else r = FALSE;
        if (r && gTouchCurY <= 0x10 && gTouchCurX >= 0xe8) {
            TalkRequest_AddMenu(0);
            sMenuMode = 0;
            MenuCtrl_SetTouch();
            return TRUE;
        }
        k = gPad[1];
        if (k & 4) {
            TalkRequest_AddMenu(0);
            sMenuMode = 4;
            MenuCtrl_SetButtons();
            return TRUE;
        }
        if (k & 0x800) {
            TalkRequest_AddMenu(0);
            sMenuMode = 0;
            MenuCtrl_SetButtons();
            return TRUE;
        }
        if (Hud_GetSceneHudKind() != 2 && (gPad[1] & 0x400)) {
            TalkRequest_AddMenu(0);
            sMenuMode = 5;
            MenuCtrl_SetButtons();
            return TRUE;
        }
    }
    return TRUE;
}

BOOL MenuManager::onDraw() { return TRUE; }

struct OpenMenuLink {
    ListNode link;
    MenuProc *owner;
};

extern "C" void MenuCtrl_AddOpenMenu(ListNode *v) { List_PushBack(&sOpenMenuList, v); }

extern "C" void MenuCtrl_RemoveOpenMenu(ListNode *o) {
    List_Remove(&sOpenMenuList, o);
    MenuCtrl_SetReleasePending(((OpenMenuLink *)o)->owner->menuId);
}

extern "C" void MenuCtrl_ReleaseClosedMenus() {
    u8 i;
    if (sMenuReleaseMask[0] != 0 || sMenuReleaseMask[1] != 0 || sMenuReleaseMask[2] != 0) {
        for (i = 0; i < 0x2e; i++) {
            if (MenuCtrl_IsReleasePending(i)) MenuCtrl_ReleaseOverlays(i);
        }
    }
}

extern "C" BOOL MenuCtrl_CreateRequestedMenu() {
    GameProc *t;
    if (sMenuRequest[0] != 3) return FALSE;
    if (sOpenMenuList.head != NULL) t = ((OpenMenuLink *)sOpenMenuList.head)->owner;
    else t = gMenuManager;
    MenuCtrl_ResetForceClose();
    if (!GameProc_CreateChild(kMenuProfileIds[sMenuRequest[1]], t, sMenuRequest[1], 4)) return FALSE;
    sMenuRequest[0] = 1;
    return TRUE;
}

extern "C" BOOL MenuCtrl_LoadRequestedOverlays() {
    if (sMenuRequest[0] != 2) return FALSE;
    u32 *e = kMenuOverlayLists[sMenuRequest[1]];
    s32 n = 0;
    while (e[n] != (u32)-1) {
        OverlayMgr_Acquire(e[n]);
        n++;
    }
    sMenuRequest[0] = 3;
    MenuCtrl_SetLoaded(sMenuRequest[1]);
    return TRUE;
}

extern "C" BOOL MenuCtrl_ReleaseOverlays(u32 i) {
    u32 *e;
    s32 n;
    e = kMenuOverlayLists[i];
    n = 0;
    while (e[n] != (u32)-1) {
        OverlayMgr_Release(e[n]);
        n++;
    }
    MenuCtrl_ClearLoaded(i);
    MenuCtrl_ClearReleasePending(i);
    return TRUE;
}

extern "C" void MenuCtrl_ResetFlags() {
    sMenuFlags = 0;
    sMenuTransitionProgress = 0;
}

extern "C" BOOL MenuCtrl_IsIdle() {
    if (sMenuRequest[0] != 1) return FALSE;
    if (sOpenMenuList.head == NULL) return TRUE;
    return FALSE;
}

extern "C" BOOL MenuCtrl_IsMenuOpen() {
    if (sMenuRequest[0] == 0) return FALSE;
    if (sOpenMenuList.head != NULL) return TRUE;
    return FALSE;
}

extern "C" BOOL MenuCtrl_RequestOpen(u32 v) {
    if (!MenuCtrl_IsIdle()) return FALSE;
    sMenuRequest[1] = v;
    sMenuRequest[0] = 2;
    return TRUE;
}

extern "C" BOOL MenuCtrl_RequestOpenNested(u32 v) {
    if (sMenuRequest[0] != 1) return FALSE;
    if (sOpenMenuList.head == NULL) return FALSE;
    if (MenuCtrl_IsLoaded(v)) return FALSE;
    sMenuRequest[1] = v;
    sMenuRequest[0] = 2;
    return TRUE;
}

extern "C" BOOL MenuCtrl_RequestOpenMenu12(void *v) {
    BOOL r = MenuCtrl_RequestOpen(12);
    if (r) MenuCtrl_SetArg(v);
    return r;
}

extern "C" BOOL MenuCtrl_IsLoaded(s32 i) {
    BOOL r = TRUE;
    if (!((1 << (i & 0x1f)) & sMenuLoadedMask[i >> 5])) r = FALSE;
    return r;
}

extern "C" void MenuCtrl_SetLoaded(s32 i) { sMenuLoadedMask[i >> 5] |= (1 << (i & 0x1f)); }

extern "C" void MenuCtrl_ClearLoaded(s32 i) { sMenuLoadedMask[i >> 5] &= ~(1 << (i & 0x1f)); }

extern "C" BOOL MenuCtrl_IsReleasePending(s32 i) {
    BOOL r = TRUE;
    if (!((1 << (i & 0x1f)) & sMenuReleaseMask[i >> 5])) r = FALSE;
    return r;
}

extern "C" void MenuCtrl_SetReleasePending(s32 i) { sMenuReleaseMask[i >> 5] |= (1 << (i & 0x1f)); }

extern "C" void MenuCtrl_ClearReleasePending(s32 i) { sMenuReleaseMask[i >> 5] &= ~(1 << (i & 0x1f)); }

extern "C" void MenuCtrl_SetFlags(u32 m) { sMenuFlags |= m; }

extern "C" void MenuCtrl_ClearFlags(u32 m) { sMenuFlags &= ~m; }

extern "C" BOOL MenuCtrl_HasFlags(u32 m) {
    if (m == (m & sMenuFlags)) return TRUE;
    return FALSE;
}

extern "C" void MenuCtrl_ClearMenuOnTop() { MenuCtrl_ClearFlags(1); }

extern "C" void MenuCtrl_SetMenuOnTop() { MenuCtrl_SetFlags(1); }

extern "C" BOOL MenuCtrl_IsMenuOnTop() { return MenuCtrl_HasFlags(1); }

extern "C" void MenuCtrl_SetTouch() {
    MenuCtrl_ClearFlags(2);
    InputMode_SetTouch();
}

extern "C" void MenuCtrl_SetButtons() {
    MenuCtrl_SetFlags(2);
    InputMode_SetButtons();
}

extern "C" BOOL MenuCtrl_IsTouch() {
    if (MenuCtrl_HasFlags(2)) return FALSE;
    return TRUE;
}

extern "C" BOOL MenuCtrl_IsButtons() { return MenuCtrl_HasFlags(2); }

extern "C" void MenuCtrl_SyncFromInputMode() {
    if (InputMode_IsButtons()) MenuCtrl_SetButtons();
    else MenuCtrl_SetTouch();
}

extern "C" s32 Menu_GetIconCharIndex(s32 v) {
    return (v & 0xf) * 2 + (v >> 4) * 64;
}

extern "C" void BgScreen_SetRectPalette(u16 *tbl, s32 x0, s32 y0, s32 x1, s32 y1, u32 to) {
    s32 y, x, idx;
    u32 t = (to << 28) >> 16;
    for (y = y0; y <= y1; y++) {
        for (x = x0, idx = x0 + y * 32; x <= x1; idx++, x++) {
            u16 *p = &tbl[idx];
            u32 v = *p;
            *p = t | (v & 0xfff);
        }
    }
}

extern "C" void BgScreen_ReplaceRectPalette(u16 *tbl, s32 x0, s32 y0, s32 x1, s32 y1, u32 from, u32 to) {
    s32 y, x, idx;
    u32 f = (from << 28) >> 16;
    u32 t = (to << 28) >> 16;
    for (y = y0; y <= y1; y++) {
        for (x = x0, idx = x0 + y * 32; x <= x1; idx++, x++) {
            u16 *p = &tbl[idx];
            u32 v = *p;
            u32 k = v & 0xf000;
            if (f == k) {
                *p = t | (v & 0xfff);
            }
        }
    }
}

extern "C" void MenuCtrl_SetTransitionProgress(s32 v) { sMenuTransitionProgress = v; }

extern "C" s32 MenuCtrl_GetTransitionProgress() {
    if (MenuCtrl_IsTransitionActive()) return sMenuTransitionProgress;
    return 0;
}

extern "C" s32 MenuCtrl_GetTransitionProgressOrFull() {
    if (MenuCtrl_IsTransitionActive()) return sMenuTransitionProgress;
    return 0x1000;
}

extern "C" BOOL MenuCtrl_IsTransitionActive() { return MenuCtrl_HasFlags(4); }

extern "C" void MenuCtrl_SetTransitionActive() { return MenuCtrl_SetFlags(4); }

extern "C" void MenuCtrl_ClearTransitionActive() { return MenuCtrl_ClearFlags(4); }

extern "C" BOOL MenuCtrl_IsScreenChanging() { return MenuCtrl_HasFlags(0x10); }

extern "C" void MenuCtrl_SetScreenChanging() { return MenuCtrl_SetFlags(0x10); }

extern "C" void MenuCtrl_ClearScreenChanging() { return MenuCtrl_ClearFlags(0x10); }

extern "C" void *MenuCtrl_GetArg() { return sMenuArg; }

extern "C" void MenuCtrl_SetArg(void *v) { sMenuArg = v; }

extern "C" u32 MenuCtrl_GetMode() { return sMenuMode; }

extern "C" void MenuCtrl_SetMode(u32 v) { sMenuMode = v; }

extern "C" u32 MenuCtrl_GetIndex() { return sMenuIndex; }

extern "C" void MenuCtrl_SetIndex(u32 v) { sMenuIndex = v; }

extern "C" BOOL MenuCtrl_IsResultOk() {
    if (sMenuResult == 1) return TRUE;
    return FALSE;
}

extern "C" BOOL MenuCtrl_IsResultDuplicateName() {
    if (sMenuResult == 2) return TRUE;
    return FALSE;
}

extern "C" void MenuCtrl_SetResult(u32 v) { sMenuResult = v; }

extern "C" void *MenuCtrl_GetText() { return sMenuText; }

extern "C" void MenuCtrl_SetText(const void *a, u32 b) {
    Mem_Clear(sMenuText, 16);
    Mem_Copy(a, sMenuText, b);
}

extern "C" BOOL MenuCtrl_OpenLauncher(u32 a) {
    if (!MenuCtrl_IsIdle()) return FALSE;
    sMenuMode = a;
    return MenuCtrl_RequestOpen(9);
}

extern "C" BOOL MenuCtrl_OpenLauncherWithIndex(u32 a, u32 b) {
    if (MenuCtrl_OpenLauncher(a)) {
        sMenuIndex = b;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MenuCtrl_IsFinished() {
    if (MenuCtrl_IsIdle()) return TRUE;
    return FALSE;
}

extern "C" void MenuCtrl_ClearSavedSlot() { sMenuSavedSlot = 0; }

extern "C" void MenuCtrl_SetSavedSlot(u32 v) { sMenuSavedSlot = v; }

extern "C" u32 MenuCtrl_GetSavedSlot() { return sMenuSavedSlot; }

extern "C" void MenuCtrl_BackupPockets() {
    PlayerInventory *p;
    s32 i;
    p = (PlayerInventory *)PlayerData_GetCurrent()->getInventory();
    for (i = 0; i < 15; i++) {
        sPocketBackupItems[i] = *p->getPocket(i);
        sPocketBackupFlags[i] = p->getPocketFlags(i);
    }
}

extern "C" void MenuCtrl_RestorePockets() {
    u16 tmp[1];
    s32 i;
    PlayerData_GetCurrent()->getInventory();
    tmp[0] = 0xfff1;
    for (i = 0; i < 15; i++) {
        tmp[0] = sPocketBackupItems[i];
        Pocket_SetItem(tmp, sPocketBackupFlags[i], i);
    }
}

extern "C" void MenuCtrl_SetChosenItems(u16 *src) {
    s32 i;
    for (i = 0; i < 15; i++) {
        sMenuChosenItems[i] = src[i];
    }
}

extern "C" u16 *MenuCtrl_GetChosenItems(void) { return sMenuChosenItems; }

extern "C" void MenuCtrl_ReturnChosenItems(BOOL returnItems) {
    if (returnItems) {
        s32 i;
        for (i = 0; i < 15; i++) {
            u32 c = sMenuChosenItems[i];
            s32 idx;
            if (c >= 0x38e4 && c <= 0x3933) {
                idx = ((s32)c - 0x38e4) >> 2;
            } else {
                idx = -1;
            }
            if (idx >= 0) {
                u32 v;
                if ((u32)idx < 20) {
                    v = 0x3934 + idx * 4;
                } else {
                    v = 0x3934;
                }
                MenuCtrl_ReplaceBackupItem(c, v);
            }
        }
    }
    MenuCtrl_RestorePockets();
}

extern "C" void MenuCtrl_ReplaceBackupItem(u32 key, u16 val) {
    s32 i;
    for (i = 0; i < 15; i++) {
        if (key == sPocketBackupItems[i] && sPocketBackupFlags[i] == 0) {
            sPocketBackupItems[i] = val;
            break;
        }
    }
}

extern "C" BOOL MenuCtrl_OpenPocketSelect(u32 a, u32 b) {
    if (MenuCtrl_OpenLauncher(0x21)) {
        sPocketSelectLabel = b;
        sPocketSelectMask = a;
        return TRUE;
    }
    return FALSE;
}

extern "C" u16 MenuCtrl_BuildPocketMask(BOOL (*cb)(u16 *, s32)) {
    PlayerData *a = PlayerData_GetCurrent();
    u16 *p = ((PlayerInventory *)(((PlayerData *)(a))->getInventory()))->getPocket(0);
    s32 i;
    u16 mask = 0;
    for (i = 0; i < 15; i++) {
        if (cb(p + i, ((PlayerInventory *)(((PlayerData *)(a))->getInventory()))->getPocketFlags(i))) {
            mask |= 1 << i;
        }
    }
    return mask;
}

extern "C" u16 MenuCtrl_GetPocketSelectMask(void) { return sPocketSelectMask; }

extern "C" u8 MenuCtrl_GetPocketSelectLabel(void) { return sPocketSelectLabel; }

extern "C" BOOL MenuCtrl_OpenPostOffice(void) {
    if (MenuCtrl_OpenLauncher(0x25)) {
        sPostOfficeResult = 0;
        return TRUE;
    }
    return FALSE;
}

extern "C" void MenuCtrl_SetPostOfficeResult(u32 v) { sPostOfficeResult = v; }

extern "C" void MenuCtrl_SetFutureLetter(void *a) {
    Letter_Copy((LetterView *)&sFutureLetter, (LetterView *)a);
}

extern "C" void MenuCtrl_StoreFutureLetter(void) {
    PlayerData *a = PlayerData_GetCurrent();
    LetterView *p = (LetterView *)FutureLetter_GetLetter(PlayerData_GetFutureLetter(a));
    u8 *q;
    Letter_Copy(p, (LetterView *)&sFutureLetter);
    Letter_MarkSent(p);
    q = ((FutureLetter *)(PlayerData_GetFutureLetter(a)))->getDeliveryDate();
    q[0] = 1;
    q[1] = 1;
    q[2] = 0;
    q[3] = 0;
    q[0] = sMenuDateTime.w.dt.day;
    q[1] = sMenuDateTime.w.dt.month;
    q[2] = sMenuDateTime.w.dt.year;
}

extern "C" void MenuCtrl_ReturnFutureLetter(void) {
    LetterView *p = (LetterView *)Inventory_GetEmptyLetter();
    if (p) {
        Letter_Copy(p, (LetterView *)&sFutureLetter);
    }
}

extern "C" u32 MenuCtrl_GetPostOfficeOutcome(void) {
    u32 v = sPostOfficeResult;
    if (v & 2) {
        return 2;
    }
    if (v & 1) {
        return 1;
    }
    if (v & 0x800) {
        return 3;
    }
    return 0;
}

extern "C" BOOL MenuCtrl_PostOfficeHadBadAddress(void) {
    if (sPostOfficeResult & 8) {
        return TRUE;
    }
    return FALSE;
}

extern "C" u8 MenuCtrl_GetPostOfficeFullMailboxes(void) {
    return (sPostOfficeResult >> 6) & 3;
}

extern "C" BOOL MenuCtrl_PostOfficeWasRejected(void) {
    if (sPostOfficeResult & 0x400) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MenuCtrl_PostOfficeHadNoLetter(void) {
    if (sPostOfficeResult & 0x100) {
        return FALSE;
    }
    return TRUE;
}

extern "C" BOOL MenuCtrl_PostOfficeLettersSent(void) {
    if (sPostOfficeResult & 0x200) {
        return TRUE;
    }
    return FALSE;
}

extern "C" u32 MenuCtrl_GetHandBells(void) { return sMenuHandBells; }

extern "C" void MenuCtrl_SetHandBells(u32 v) { sMenuHandBells = v; }

extern "C" u32 MenuCtrl_GetAmount(void) { return sMenuAmount; }

extern "C" void MenuCtrl_SetAmount(u32 v) { sMenuAmount = v; }

extern "C" void MenuCtrl_SetDateTime(void *a) {
    MI_CpuCopy8(a, &sMenuDateTime, 8);
}

extern "C" void MenuCtrl_GetDateTime(void *a) {
    MI_CpuCopy8(&sMenuDateTime, a, 8);
}

extern "C" BOOL MenuCtrl_OpenNearbyTowns(void *a, void *b) {
    if (MenuCtrl_OpenLauncher(0x3d)) {
        sMenuPtrArg0 = a;
        sMenuPtrArg1 = b;
        return TRUE;
    }
    return FALSE;
}

extern "C" void MenuCtrl_ClearPtrArgs(void) {
    sMenuPtrArg0 = 0;
    sMenuPtrArg1 = 0;
}

extern "C" void *MenuCtrl_GetPtrArg0(void) { return sMenuPtrArg0; }

extern "C" void *MenuCtrl_GetPtrArg1(void) { return sMenuPtrArg1; }

extern "C" BOOL MenuCtrl_IsClockMovedBack(void) { return MenuCtrl_HasFlags(8); }

extern "C" BOOL MenuCtrl_IsClockMovedForward(void) { return MenuCtrl_HasFlags(0x20); }

extern "C" BOOL MenuCtrl_IsClockEdited(void) { return MenuCtrl_HasFlags(0x40); }

extern "C" void MenuCtrl_SetClockMovedBack(void) { MenuCtrl_SetFlags(8); }

extern "C" void MenuCtrl_SetClockMovedForward(void) { MenuCtrl_SetFlags(0x20); }

extern "C" void MenuCtrl_SetClockEdited(void) { MenuCtrl_SetFlags(0x40); }

extern "C" void MenuCtrl_ClearClockChangeFlags(void) {
    MenuCtrl_ClearFlags(8);
    MenuCtrl_ClearFlags(0x20);
    MenuCtrl_ClearFlags(0x40);
}

extern "C" BOOL MenuCtrl_OpenPocketsFullInsect(u32 v) {
    if (MenuCtrl_OpenLauncher(0x2b)) {
        sMenuItem = v;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MenuCtrl_OpenPocketsFullFish(u32 a, void *b) {
    if (MenuCtrl_OpenLauncher(0x2c)) {
        sMenuPtrArg0 = b;
        sMenuItem = a;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MenuCtrl_OpenPocketsFullPickUp(u32 v) {
    if (MenuCtrl_OpenLauncher(0x29)) {
        sMenuItem = v;
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL MenuCtrl_OpenPocketsFullDug(u32 v) {
    if (MenuCtrl_OpenLauncher(0x2a)) {
        sMenuItem = v;
        return TRUE;
    }
    return FALSE;
}

extern "C" u16 MenuCtrl_GetPocketsFullItem(void) { return sMenuItem; }

extern "C" void MenuCtrl_SetPocketsFullItem(u32 v) { sMenuItem = v; }

extern "C" void MenuCtrl_SetCatalogItem(u32 v) { sMenuItem = v; }

extern "C" u16 MenuCtrl_GetCatalogItem(void) { return sMenuItem; }

extern "C" void MenuCtrl_SetSongItem(u32 v) { sMenuItem = v; }

extern "C" u16 MenuCtrl_GetSongItem(void) { return sMenuItem; }

extern "C" BOOL MenuCtrl_OpenLauncherWithText(u32 a, const void *b, u32 c) {
    if (MenuCtrl_OpenLauncher(a)) {
        MenuCtrl_SetText(b, c);
        return TRUE;
    }
    return FALSE;
}

extern "C" void MenuCtrl_InitKeyboardState(void) {
    sKeyboardPage = 1;
    sKeyboardPageModes[0] = 0;
    sKeyboardPageModes[1] = 2;
    sKeyboardPageModes[2] = 6;
    sKeyboardPageModes[3] = 7;
    MenuCtrl_ClearChatDraft();
}

extern "C" u8 MenuCtrl_GetKeyboardPage(void) {
    return sKeyboardPage;
}

extern "C" void MenuCtrl_SetKeyboardPage(u32 v) {
    sKeyboardPage = v;
}

extern "C" u8 MenuCtrl_GetKeyboardPageMode(u32 i) {
    if (i == 0xff) {
        i = sKeyboardPage;
    }
    return sKeyboardPageModes[i];
}

extern "C" void MenuCtrl_SetKeyboardPageMode(u32 i, u32 v) {
    sKeyboardPageModes[i] = v;
}

extern "C" void MenuCtrl_RequestForceClose(void) { MenuCtrl_SetFlags(0x80); }

extern "C" void MenuCtrl_ResetForceClose(void) {
    MenuCtrl_ClearFlags(0x80);
    sForceCloseDelay = 0x37;
}

extern "C" void MenuCtrl_TickForceClose(void) {
    if (MenuCtrl_HasFlags(0x80)) {
        if (sForceCloseDelay != 0) {
            sForceCloseDelay -= TICK_STEP_ENDS() ? 1 : 0;
        }
    }
}

extern "C" s32 MenuCtrl_IsForceCloseDue(void) {
    if (sForceCloseDelay != 0) {
        return 0;
    }
    return MenuCtrl_HasFlags(0x80);
}

extern "C" void MenuCtrl_SetSyncMsgMenu(void) { MenuCtrl_SetFlags(0x100); }

extern "C" void MenuCtrl_ClearSyncMsgMenu(void) { MenuCtrl_ClearFlags(0x100); }

extern "C" BOOL MenuCtrl_IsSyncMsgMenu(void) { return MenuCtrl_HasFlags(0x100); }

extern "C" BOOL MenuCtrl_IsFriendPageFromIndex(void) { return MenuCtrl_HasFlags(0x200); }

extern "C" void MenuCtrl_SetFriendPageFromIndex(void) { MenuCtrl_SetFlags(0x200); }

extern "C" void MenuCtrl_ClearFriendPageFromIndex(void) { MenuCtrl_ClearFlags(0x200); }

extern "C" void *MenuCtrl_GetChatDraft(void) {
    return sChatDraft;
}

extern "C" void MenuCtrl_SetChatDraft(const void *a) {
    Mem_Copy(a, sChatDraft, 0x20);
}


extern "C" void MenuCtrl_ClearChatDraft(void) {
    Mem_Clear(sChatDraft, 0x20);
}

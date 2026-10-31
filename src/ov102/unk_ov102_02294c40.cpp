#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "ui/CursorMotion.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuCursor.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_02087e0c.h"
#include "proto/main/unk_02039c08.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_02085940.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02098e90.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov102/unk_ov102_02294c40.h"
#include "proto/main/unk_02097444.h"

extern "C" {
BOOL Clock_GetWeekday();
void MI_CpuCopy8(void *a, void *b, u32 c);
BOOL PopupChoice_MoveCursor(void *p, s32 a, void *q, s32 b);
BOOL PopupChoice_TickDecideDelay(void *p);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *a);
void PopupChoice_Update(void *a);
void PopupChoice_Close(void *p, s32 x);
extern CommManager *gCommManager;
extern u8 gSaveLostAndFound[];
extern u8 gSaveRecycleBin[];
extern u16 gPad[];
}

class ChestMenu;



















typedef void (ChestMenu::*Unk_ov102_02297520_Fn)();

class ChestMenu : public MenuProc {
public:
    ChestMenu()
        : vramTask(), itemGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), errorMessage(), textLabels() {}
    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32);
    void setFlags(u32);
    BOOL testFlags(u32);
    s32 handlePageKeys();
    void startPageSwitch();
    BOOL hitTestPageTab(s32, s32);
    void drawPageTabs();
    void confirm(s32);
    void setOkLabel(s32);
    LabelString * allocTextLabel();
    void resetTextLabels();
    BOOL moveCursorByPad(u32, u32);
    void moveCursorOnTabs(u32, u32);
    void moveCursorOnButtons(u32);
    void moveCursorInBox(u32, u32);
    void moveCursorInPockets(u32, u32);
    void startExchange(u32);
    void startPutDown(u32);
    void startPickUp();
    void releaseCursor();
    void pressCursor();
    void mainAct0F();
    void mainAct0E();
    void mainAct0D();
    void mainAct0C();
    void mainAct0B();
    void mainAct0A();
    void mainAct09();
    void mainAct08();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void loadObjGraphics();
    void loadPage();
    void loadTopBg();
    void loadInventoryBg();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initMembers();
    void transitionAct09();
    void transitionAct08();
    void transitionAct07();
    void transitionAct06();
    void transitionAct05();
    void transitionAct04();
    void startSlideOut();
    void transitionAct03();
    void transitionAct02();
    void transitionAct01();
    void transitionAct00();
    void showPage();
    void runMainState();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ BgVramTaskPair vramTask[1];
    /* 0xcc */ InventoryItemGrid itemGrid;
    /* 0xb2c */ LetterGrid letterGrid;
    /* 0xb54 */ InventoryBg inventoryBg;
    /* 0x2134 */ TouchPromptBalloon nameBalloon;
    /* 0x21f4 */ CursorMotion flyMotion;
    /* 0x220c */ MenuCursorBuf0 cursor;
    /* 0x2270 */ MenuErrorMessage errorMessage;
    /* 0x2378 */ LabelString textLabels[2];
    /* 0x23f8 */ u32 stateFlags;
    /* 0x23fc */ s32 pocketsSlideY;
    /* 0x2400 */ s32 boxSlideY;
    /* 0x2404 */ s32 grabOffsetX;
    /* 0x2408 */ s32 grabOffsetY;
    /* 0x240c */ s32 heldX;
    /* 0x2410 */ s32 heldY;
    /* 0x2414 */ u16 storageItems[0x5a];
    /* 0x24c8 */ u16 heldItem;
    /* 0x24ca */ u8 heldItemFlags;
    /* 0x24cb */ u8 heldKind;
    /* 0x24cc */ u8 touchedSlot;
    /* 0x24cd */ u8 balloonSlot;
    /* 0x24ce */ u8 pickUpSlot;
    /* 0x24cf */ u8 pickUpPage;
    /* 0x24d0 */ u8 pickUpOriginSlot;
    /* 0x24d1 */ u8 cursorSlot;
    /* 0x24d2 */ u8 actionSlot;
    /* 0x24d3 */ u8 returnState;
    /* 0x24d4 */ u8 numTextLabels;
    /* 0x24d5 */ u8 delayTimer;
    /* 0x24d6 */ u8 currentPage;
};

typedef ChestMenu S;



struct Unk_ov102_02297580_Ent {
    u32 a;
    u32 b;
};
extern "C" Unk_ov102_02297580_Ent sChestPageTabSprites[18];
extern "C" const u16 sChestPageSe[6];

extern "C" void ChestMenu_RefreshCursor(S *s);
extern "C" void ChestMenu_MoveCursorToTarget(S *s);
extern "C" void ChestMenu_HideCursor(S *s);
extern "C" s32 ChestMenu_GetCursorTargetY(S *s);
extern "C" s32 ChestMenu_GetCursorTargetX(S *s);
extern "C" void ChestMenu_ShowCursor(S *s);
extern "C" void ChestMenu_ExchangeHeldItem(S *s, u32 a);
extern "C" void ChestMenu_ReleaseHeldItem(S *s, u32 a);
extern "C" void ChestMenu_PickUpItem(S *s, u32 a);
extern "C" void ChestMenu_TrackFlyingItem(S *s);
extern "C" void ChestMenu_TrackCursor(S *s);
extern "C" void ChestMenu_TrackTouch(S *s);
extern "C" void ChestMenu_DrawHeldItem(S *s);
extern "C" void ChestMenu_UpdateNameBalloon(S *s);
extern "C" void ChestMenu_PlaceNameBalloon(S *s);
extern "C" BOOL ChestMenu_HasTouchMoved(S *s);
extern "C" void ChestMenu_MarkSlot(S *s, u32 a);
extern "C" void ChestMenu_ClearMarks(S *s);
extern "C" void ChestMenu_SetCursorSlot(S *s, u32 a);
extern "C" void ChestMenu_ClearCursorSlots(S *s);
extern "C" u32 ChestMenu_GetSlotFlags(S *s, u32 a);
extern "C" u32 ChestMenu_GetSlotItem(S *s, u32 a);
extern "C" BOOL ChestMenu_IsSlotEmpty(S *s, u32 a);
extern "C" BOOL ChestMenu_IsSlotDisabled(S *s, u32 a);
extern "C" void ChestMenu_DisableRejectedItems(S *s);
extern "C" BOOL ChestMenu_IsItemRejected(S *s, u32 a);
extern "C" s32 ChestMenu_GetSlotY(S *s, u32 a);
extern "C" s32 ChestMenu_GetSlotX(S *s, u32 a);
extern "C" u16 *ChestMenu_GetPageItems(S *s);
extern "C" void ChestMenu_SetSlotItem(S *s, u32 a, u32 b, u32 c);
extern "C" BOOL ChestMenu_DropHeldItem(S *s, u32 a);
extern "C" u32 ChestMenu_FindSlotAt(S *s, u32 a, u32 b, u32 c);
extern "C" u32 ChestMenu_GridToBoxSlot(S *s, u32 a);
extern "C" u32 ChestMenu_GridToBoxSlotOr0F(S *s, u32 a);
extern "C" u32 ChestMenu_GridToPocketSlot(S *s, u32 v);
extern "C" u32 ChestMenu_ToGridSlot(S *s, u32 v);
extern "C" BOOL ChestMenu_IsButtonSlot(S *s, u32 v);
extern "C" BOOL ChestMenu_IsTabSlot(S *s, u32 v);
extern "C" BOOL ChestMenu_IsBoxSlot(S *s, u32 v);
extern "C" BOOL ChestMenu_IsPocketSlot(S *s, u32 v);
extern "C" void ChestMenu_CancelUploads(S *s);
extern "C" u32 ChestMenu_FindFreeBoxSlot(S *s);
extern "C" u32 ChestMenu_FindFreePocket(S *s);
extern "C" void ChestMenu_QuickMove(S *s, u8 a, u32 b);
extern "C" void ChestMenu_FlyHeldToFreeSlot(S *s, u32 a, s32 c);
extern "C" void ChestMenu_StartFlyHeldItem(S *s, u32 a, u32 b);
extern "C" void ChestMenu_PickUpWithHand(S *s, u8 a);
extern "C" void ChestMenu_PickUpWithTouch(S *s, u8 a);
extern "C" void ChestMenu_TouchItem(S *s, u32 a);
extern "C" void ChestMenu_ResumeInput(S *s);
extern "C" void ChestMenu_StartButtonInput(S *s);
extern "C" void ChestMenu_StartTouchInput(S *s);

static inline BOOL Unk_ov102_022969bc_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) return TRUE;
    return FALSE;
}

extern "C" ChestMenu *ChestMenu_Create() { return new ChestMenu(); }

BOOL ChestMenu::onCreate() {
    initMembers();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL ChestMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL ChestMenu::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    ChestMenu_DrawHeldItem(this);
    if (testFlags(0x80)) {
        InventoryItemGrid_DrawBox(&itemGrid, 0, boxSlideY);
        drawPageTabs();
    }
    if (testFlags(2)) {
        InventoryItemGrid_DrawPockets(&itemGrid, 0, pocketsSlideY);
        letterGrid.drawPocketLetters(0, pocketsSlideY);
        Shared_InventoryBg_DrawSprite(&inventoryBg, pocketsSlideY);
    }
    return TRUE;
}
extern "C" ProcProfile sChestMenuProfile;
extern "C" const u16 sChestPageSe[6];
extern "C" Unk_ov102_02297580_Ent sChestPageTabSprites[18];

extern "C" ProcProfile sChestMenuProfile = {(void *(*)())ChestMenu_Create, 0x95, 0x99};

extern "C" const u16 sChestPageSe[6] = {0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23};

BOOL ChestMenu::execTransition() {
    static Unk_ov102_02297520_Fn tbl[10] = {
        &ChestMenu::transitionAct00, &ChestMenu::transitionAct01,
        &ChestMenu::transitionAct02, &ChestMenu::transitionAct03,
        &ChestMenu::transitionAct04, &ChestMenu::transitionAct05,
        &ChestMenu::transitionAct06, &ChestMenu::transitionAct07,
        &ChestMenu::transitionAct08, &ChestMenu::transitionAct09};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void ChestMenu::runMainState() {
    static Unk_ov102_02297520_Fn tbl[16] = {
        &ChestMenu::mainAct00, &ChestMenu::mainAct01,
        &ChestMenu::mainAct02, &ChestMenu::mainAct03,
        &ChestMenu::mainAct04, &ChestMenu::updateCursorMove,
        &ChestMenu::updateCursorPress, &ChestMenu::updateCursorRelease,
        &ChestMenu::mainAct08, &ChestMenu::mainAct09,
        &ChestMenu::mainAct0A, &ChestMenu::mainAct0B,
        &ChestMenu::mainAct0C, &ChestMenu::mainAct0D,
        &ChestMenu::mainAct0E, &ChestMenu::mainAct0F};
    (this->*tbl[mainState])();
}

BOOL ChestMenu::execMain() {
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        u32 s = mainState;
        if (s == 0 || s == 1 || s == 3) {
            ChestMenu_HideCursor(this);
            nameBalloon.hide(0);
            confirm(0);
        }
    }
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL ChestMenu::execPhase3() {
    return TRUE;
}

BOOL ChestMenu::execPhase4() {
    return TRUE;
}

BOOL ChestMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void ChestMenu::showPage() {
    loadPage();
    beginSubSlideIn(2, 0, 1, 0x30);
    setSlideExtent(0x90);
    setFlags(0x80);
    Gfx2d_ShowLayer(4);
    applySlideOffset(4, 0, 0);
    boxSlideY = getSlideOffsetY();
}

void ChestMenu::transitionAct00() {
    ChestMenu_SetupBgLayers();
    loadInventoryBg();
    setTransitionState(1);
}

void ChestMenu::transitionAct01() {
    loadObjGraphics();
    Shared_InventoryItemGrid_LoadPockets(&itemGrid);
    ChestMenu_DisableRejectedItems(this);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    letterGrid.highlightLetterKinds(0xf);
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    pocketsSlideY = getSlideOffsetY();
}

void ChestMenu::transitionAct02() {
    s32 r = stepSlideIn(0);
    applySlideOffset(6, 0, 0);
    pocketsSlideY = getSlideOffsetY();
    if (r != 0) {
        loadTopBg();
        showPage();
        setTransitionState(3);
    }
}

void ChestMenu::transitionAct03() {
    if (stepSlideIn(0)) {
        setPhase(2);
        ChestMenu_ResumeInput(this);
        clearFlags(0x40);
        if (heldKind != 0 && MenuCtrl_IsButtons()) {
            if (cursorSlot < 0x1e || cursorSlot > 0x23) {
                cursor.setAnimAtEnd(4);
            }
            cursor.update();
            ChestMenu_TrackCursor(this);
            setMainState(4);
        }
    }
    applySlideOffset(4, 0, 0);
    boxSlideY = getSlideOffsetY();
}

void ChestMenu::startSlideOut() {
    nameBalloon.hide(1);
    ChestMenu_HideCursor(this);
    beginSubSlideOut(2, 4, 1, 0x30);
    setSlideExtent(0x90);
    applySlideOffset(4, 0, 0);
    boxSlideY = getSlideOffsetY();
}

void ChestMenu::transitionAct04() {
    startSlideOut();
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    setTransitionState(5);
}

void ChestMenu::transitionAct05() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        clearFlags(0x80);
        beginSubSlideOut(8, 0, 0, 0x30);
        applySlideOffset(6, 0, 0);
        setTransitionState(6);
        transitionAct06();
    } else {
        applySlideOffset(4, 0, 0);
        boxSlideY = getSlideOffsetY();
    }
}

void ChestMenu::transitionAct06() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        setPhase(5);
        clearFlags(1);
        clearFlags(2);
    } else {
        applySlideOffset(6, 0, 0);
    }
    pocketsSlideY = getSlideOffsetY();
}

void ChestMenu::transitionAct07() {
    startSlideOut();
    setTransitionState(8);
    delayTimer = 4;
    transitionAct08();
}

void ChestMenu::transitionAct08() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        if (delayTimer != 0) {
            delayTimer--;
        } else {
            showPage();
            setTransitionState(9);
        }
    } else {
        applySlideOffset(4, 0, 0);
        boxSlideY = getSlideOffsetY();
    }
}

void ChestMenu::transitionAct09() {
    transitionAct03();
}

void ChestMenu::initMembers() {
    stateFlags = 0;
    InventoryItemGrid_Init(&itemGrid, 1);
    letterGrid.init(2);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonSlot = 0x25;
    flyMotion.reset();
    heldKind = 0;
    cursorSlot = 0;
    numTextLabels = 0;
    MI_CpuCopy8((void *)ChestStorage_GetItems((u16 *)PlayerData_GetDresser(PlayerData_GetCurrent())), storageItems, 0xb4);
    MenuCtrl_BackupPockets();
    currentPage = 0;
}

void ChestMenu::releaseResources() {
    ChestMenu_CancelUploads(this);
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&itemGrid);
    resetTextLabels();
}

void ChestMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void ChestMenu::postInputUpdate() {
    postStateUpdate();
}

void ChestMenu::preStateUpdate() {
    ChestMenu_CancelUploads(this);
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&itemGrid);
    letterGrid.updateCursorLift();
    resetTextLabels();
}

void ChestMenu::postStateUpdate() {
    InventoryBg_Update(&inventoryBg);
    if (nameBalloon.updatePrompt()) {
        ChestMenu_PlaceNameBalloon(this);
    }
}

extern "C" void ChestMenu_SetupBgLayers() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void ChestMenu::loadInventoryBg() {
    InventoryBg_Load(&inventoryBg, 0);
}

void ChestMenu::loadTopBg() {
    void *h = gCurrentHeap;
    Gfx2d_LoadScreenFile("menu/inventory/b_itm_bg_tra0.bsc", h, 4);
    Gfx2d_LoadCharFile("menu/inventory/b_itm_chest.bch", h, 4, 0x1b9, 0x1b9, 0x238);
    setOkLabel(0);
}

void ChestMenu::loadPage() {
    char buf[0x24];
    void *h = gCurrentHeap;
    Str_SPrintf(buf, "menu/inventory/ten%d.bpl", currentPage);
    Gfx2d_LoadPaletteFile(buf, h, 4, 3, 3, 5);
    InventoryItemGrid_LoadBox(&itemGrid, ChestMenu_GetPageItems(this));
}

void ChestMenu::loadObjGraphics() {
    InventoryBg_LoadObjGraphics();
}

void ChestMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        ChestMenu_StartButtonInput(this);
    } else {
        if (Unk_ov102_022969bc_Both()) {
            s32 x = gTouchCurX;
            s32 y = gTouchCurY;
            s32 r = ChestMenu_FindSlotAt(this, x, y, 1);
            if (r != 0x25) {
                ChestMenu_TouchItem(this, r);
            } else if (x >= 0xc8 && x <= 0xf8 && y >= 0x68 && y <= 0x78) {
                confirm(1);
            } else if (hitTestPageTab(x, y)) {
                startPageSwitch();
            }
        }
    }
}

void ChestMenu::mainAct01() {
    if (gTouchHeld == 0) {
        setMainState(0);
        nameBalloon.setAutoCloseTimer(0x3c);
    } else if (testFlags(4) && ChestMenu_HasTouchMoved(this)) {
        ChestMenu_PickUpWithTouch(this, touchedSlot);
    } else {
        nameBalloon.commitOpen();
    }
}

void ChestMenu::mainAct02() {
    if (MenuCtrl_IsForceCloseDue()) {
        ChestMenu_ReleaseHeldItem(this, pickUpSlot);
        ChestMenu_HideCursor(this);
        nameBalloon.hide(0);
        confirm(0);
    } else {
        s32 a, r;
        ChestMenu_TrackTouch(this);
        ChestMenu_ClearMarks(this);
        a = heldY + 8;
        r = ChestMenu_FindSlotAt(this, heldX + 8, a, 0);
        if (r != 0x25) {
            if (gTouchHeld == 0) {
                if (ChestMenu_IsSlotDisabled(this, r)) {
                    ChestMenu_FlyHeldToFreeSlot(this, pickUpSlot, a);
                } else {
                    s32 q = ChestMenu_DropHeldItem(this, r);
                    if (q == 0) {
                        ChestMenu_FlyHeldToFreeSlot(this, pickUpSlot, a);
                    } else {
                        Inventory_PlayPutDownSe();
                        ChestMenu_ResumeInput(this);
                    }
                }
            } else {
                ChestMenu_MarkSlot(this, r);
            }
        } else if (gTouchHeld == 0) {
            ChestMenu_FlyHeldToFreeSlot(this, pickUpSlot, a);
        }
    }
}

void ChestMenu::mainAct03() {
    if (checkSwitchToTouch()) {
        ChestMenu_StartTouchInput(this);
        nameBalloon.hide(1);
    } else {
        u32 v = takeRepeatedKeys();
        if (moveCursorByPad(v, 0)) {
            ChestMenu_UpdateNameBalloon(this);
            ChestMenu_MoveCursorToTarget(this);
            nameBalloon.hide(0);
        } else {
            if (ChestMenu_IsSlotDisabled(this, cursorSlot)) goto tail;
            {
                u32 k = gPad[1];
                if (k & 1) {
                    if (ChestMenu_IsPocketSlot(this, cursorSlot) || ChestMenu_IsBoxSlot(this, cursorSlot)) {
                        if (!ChestMenu_IsSlotEmpty(this, cursorSlot)) {
                            startPickUp();
                        }
                    } else if (ChestMenu_IsButtonSlot(this, cursorSlot)) {
                        pressCursor();
                    } else if (ChestMenu_IsTabSlot(this, cursorSlot)) {
                        pressCursor();
                    }
                } else if (k & 0x800) {
                    if (ChestMenu_IsPocketSlot(this, cursorSlot) || ChestMenu_IsBoxSlot(this, cursorSlot)) {
                        if (!ChestMenu_IsSlotEmpty(this, cursorSlot)) {
                            u32 r = ChestMenu_IsPocketSlot(this, cursorSlot) ? ChestMenu_FindFreeBoxSlot(this) : ChestMenu_FindFreePocket(this);
                            if (r != 0x25) {
                                ChestMenu_QuickMove(this, cursorSlot, r);
                                nameBalloon.hide(1);
                            }
                        }
                    }
                } else {
                    goto tail;
                }
            }
            return;
tail:
            {
                u32 k = gPad[1];
                if ((k & 8) || (k & 2)) {
                    ChestMenu_HideCursor(this);
                    confirm(1);
                    nameBalloon.hide(0);
                } else if (!handlePageKeys()) {
                    nameBalloon.commitOpen();
                }
            }
        }
    }
}

void ChestMenu::mainAct04() {
    if (MenuCtrl_IsForceCloseDue()) {
        ChestMenu_ReleaseHeldItem(this, pickUpSlot);
        ChestMenu_HideCursor(this);
        nameBalloon.hide(0);
        confirm(0);
    } else {
        u32 v = takeRepeatedKeys();
        if (moveCursorByPad(v, 1)) {
            ChestMenu_UpdateNameBalloon(this);
            ChestMenu_MoveCursorToTarget(this);
            nameBalloon.hide(0);
        } else {
            u32 k = gPad[1];
            if (k & 1) {
                if (ChestMenu_IsPocketSlot(this, cursorSlot) || ChestMenu_IsBoxSlot(this, cursorSlot)) {
                    if (!ChestMenu_IsSlotDisabled(this, cursorSlot)) {
                        if (ChestMenu_IsSlotEmpty(this, cursorSlot)) {
                            startPutDown(cursorSlot);
                        } else {
                            startExchange(cursorSlot);
                        }
                    }
                } else if (ChestMenu_IsTabSlot(this, cursorSlot)) {
                    pressCursor();
                }
            } else if (k & 2) {
                u32 t;
                if (ChestMenu_IsBoxSlot(this, pickUpSlot) && (t = pickUpPage, t != currentPage)) {
                    ChestMenu_StartFlyHeldItem(this, (u8)(t + 0x1e), 4);
                } else if (cursor.getAnim() == 1) {
                    ChestMenu_StartFlyHeldItem(this, pickUpSlot, 4);
                } else {
                    startPutDown(pickUpSlot);
                }
            } else {
                if (!handlePageKeys()) {
                    ChestMenu_TrackCursor(this);
                    nameBalloon.commitOpen();
                }
            }
        }
    }
}

void ChestMenu::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        if ((u8)(returnState + 0xfd) <= 1) {
            ChestMenu_SetCursorSlot(this, cursorSlot);
        }
        runMainState();
    }
    ChestMenu_TrackCursor(this);
}

void ChestMenu::updateCursorPress() {
    if (cursor.isAnimDone()) {
        if (ChestMenu_IsTabSlot(this, cursorSlot)) {
            u32 v = (u8)(cursorSlot - 0x1e);
            if (v == currentPage) {
                releaseCursor();
            } else {
                currentPage = v;
                startPageSwitch();
            }
        } else if (cursorSlot == 0x24) {
            confirm(1);
        } else {
            releaseCursor();
        }
    }
}

void ChestMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        ChestMenu_RefreshCursor(this);
        if (heldKind == 1) {
            setMainState(4);
        } else {
            setMainState(3);
        }
    }
}

void ChestMenu::mainAct08() {
    if (cursor.isGripping()) {
        ChestMenu_PickUpWithHand(this, cursorSlot);
        setMainState(9);
    }
}

void ChestMenu::mainAct09() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    ChestMenu_TrackCursor(this);
}

void ChestMenu::mainAct0A() {
    if (!cursor.isGripping()) {
        u32 a = actionSlot;
        if (cursorSlot == a) {
            ChestMenu_DropHeldItem(this, a);
            ChestMenu_UpdateNameBalloon(this);
            setMainState(3);
            Inventory_PlayPutDownSe();
        } else {
            ChestMenu_StartFlyHeldItem(this, a, 4);
        }
    } else {
        ChestMenu_TrackCursor(this);
    }
}

void ChestMenu::mainAct0B() {
    if (!cursor.func_ov002_022028fc()) {
        ChestMenu_ExchangeHeldItem(this, actionSlot);
        setFlags(0x40);
        setMainState(0xc);
        ChestMenu_UpdateNameBalloon(this);
    } else {
        setMainState(3);
    }
}

void ChestMenu::mainAct0C() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    if (cursor.isGripping()) {
        if (testFlags(0x40)) {
            clearFlags(0x40);
            Shared_Inventory_PlayPickUpSe();
        }
        ChestMenu_TrackCursor(this);
    }
}

void ChestMenu::mainAct0D() {
    if (flyMotion.update()) {
        if (testFlags(0x200)) {
            clearFlags(0x200);
            ChestMenu_TrackFlyingItem(this);
        } else {
            ChestMenu_ReleaseHeldItem(this, pickUpSlot);
            ChestMenu_ResumeInput(this);
            Inventory_PlayPutDownSe();
        }
    } else {
        ChestMenu_TrackFlyingItem(this);
    }
}

void ChestMenu::mainAct0E() {
    if (errorMessage.update(1)) {
        setMainState(returnState);
        cursor.enableObjWindow();
    }
}

void ChestMenu::mainAct0F() {
    if (delayTimer != 0) {
        delayTimer--;
    } else {
        transitionState = 4;
        setPhase(1);
        nameBalloon.hide(1);
        ChestMenu_HideCursor(this);
    }
}

void ChestMenu_StartTouchInput(S *s) {
    ChestMenu_HideCursor(s);
    ChestMenu_ClearCursorSlots(s);
    s->setMainState(0);
}

void ChestMenu_StartButtonInput(S *s) {
    s->balloonSlot = 0x25;
    ChestMenu_ShowCursor(s);
    s->restartKeyRepeat();
    ChestMenu_UpdateNameBalloon(s);
    s->setMainState(3);
    ChestMenu_SetCursorSlot(s, s->cursorSlot);
}

void ChestMenu_ResumeInput(S *s) {
    if (MenuCtrl_IsTouch()) {
        ChestMenu_StartTouchInput(s);
    } else {
        ChestMenu_StartButtonInput(s);
    }
}

void ChestMenu_TouchItem(S *s, u32 a) {
    s->touchedSlot = a;
    s->setMainState(1);
    u32 r6 = gTouchCurX;
    u32 r7 = gTouchCurY;
    s->grabOffsetX = ChestMenu_GetSlotX(s, s->touchedSlot) - r6;
    s->grabOffsetY = ChestMenu_GetSlotY(s, s->touchedSlot) - r7;
    s->balloonSlot = a;
    s->nameBalloon.queueOpen();
    if (ChestMenu_IsSlotDisabled(s, a)) {
        s->clearFlags(4);
    } else {
        s->setFlags(4);
        Inventory_PlayTouchSe();
    }
}

void ChestMenu_PickUpWithTouch(S *s, u8 a) {
    s->pickUpSlot = a;
    s->pickUpOriginSlot = a;
    s->pickUpPage = s->currentPage;
    s->nameBalloon.hide(1);
    ChestMenu_PickUpItem(s, a);
    if (s->heldKind == 1) {
        s->setMainState(2);
    }
    ChestMenu_TrackTouch(s);
    Shared_Inventory_PlayPickUpSe();
}

void ChestMenu_PickUpWithHand(S *s, u8 a) {
    s->pickUpSlot = a;
    s->pickUpOriginSlot = a;
    s->pickUpPage = s->currentPage;
    s->nameBalloon.hide(1);
    ChestMenu_PickUpItem(s, a);
    if (s->heldKind == 1) {
        s->returnState = 4;
    }
    ChestMenu_TrackCursor(s);
    Shared_Inventory_PlayPickUpSe();
}

void ChestMenu_StartFlyHeldItem(S *s, u32 a, u32 b) {
    s->pickUpSlot = a;
    s->flyMotion.setPos(s->heldX, s->heldY);
    s32 t = ChestMenu_GetSlotY(s, a);
    if (ChestMenu_IsTabSlot(s, a)) {
        t -= 8;
    }
    s32 u = ChestMenu_GetSlotX(s, a);
    s->flyMotion.startLinear(u, t, b);
    s->flyMotion.update();
    ChestMenu_TrackFlyingItem(s);
    if (ChestMenu_IsTabSlot(s, a)) {
        s->setFlags(0x200);
    } else {
        s->clearFlags(0x200);
    }
    s->setMainState(0xd);
}

void ChestMenu_FlyHeldToFreeSlot(S *s, u32 a, s32 c) {
    u32 r = 0x25;
    if (c >= 0x6c) {
        if (ChestMenu_IsBoxSlot(s, a)) {
            r = ChestMenu_FindFreePocket(s);
        }
    } else {
        if (ChestMenu_IsPocketSlot(s, a)) {
            r = ChestMenu_FindFreeBoxSlot(s);
        }
    }
    if (r != 0x25) {
        a = r;
    }
    ChestMenu_StartFlyHeldItem(s, a, 4);
}

void ChestMenu_QuickMove(S *s, u8 a, u32 b) {
    ChestMenu_PickUpItem(s, a);
    s->heldX = ChestMenu_GetSlotX(s, a);
    s->heldY = ChestMenu_GetSlotY(s, a);
    ChestMenu_StartFlyHeldItem(s, b, 4);
}

u32 ChestMenu_FindFreePocket(S *s) {
    s32 r = Pocket_FindEmpty();
    if (r == -1) {
        return 0x25;
    }
    return (u8)r;
}

u32 ChestMenu_FindFreeBoxSlot(S *s) {
    u16 *p = ChestMenu_GetPageItems(s);
    s32 i;
    for (i = 0; i < 15; i++) {
        if (p[i] == 0xfff1) {
            return (u8)(i + 0xf);
        }
    }
    return 0x25;
}

void ChestMenu_CancelUploads(S *s) {
    ((BgVramTask *)s->vramTask)->cancel();
}

BOOL ChestMenu_IsPocketSlot(S *s, u32 v) {
    if (v <= 0xe) {
        return TRUE;
    }
    return FALSE;
}

BOOL ChestMenu_IsBoxSlot(S *s, u32 v) {
    if (v >= 0xf && v <= 0x1d) {
        return TRUE;
    }
    return FALSE;
}

BOOL ChestMenu_IsTabSlot(S *s, u32 v) {
    if (v >= 0x1e && v <= 0x23) {
        return TRUE;
    }
    return FALSE;
}

BOOL ChestMenu_IsButtonSlot(S *s, u32 v) {
    if (v == 0x24) {
        return TRUE;
    }
    return FALSE;
}

u32 ChestMenu_ToGridSlot(S *s, u32 v) {
    if (ChestMenu_IsPocketSlot(s, v)) {
        return (u8)v;
    }
    if (ChestMenu_IsBoxSlot(s, v)) {
        return ChestMenu_GridToBoxSlotOr0F(s, v);
    }
    return 0;
}

u32 ChestMenu_GridToPocketSlot(S *s, u32 v) {
    if (v <= 0xe) {
        return (u8)v;
    }
    return 0x25;
}

u32 ChestMenu_FindSlotAt(S *s, u32 a, u32 b, u32 c)
{
    u32 r = InventoryItemGrid_FindPocketSlotAt(&s->itemGrid, a, b);
    if (r != 0x23) {
        if (c != 0 && InventoryItemGrid_IsSlotEmpty(&s->itemGrid, r)) {
            return 0x25;
        }
        return ChestMenu_GridToPocketSlot(s, r);
    }
    r = Shared_InventoryItemGrid_FindBoxSlotAt(&s->itemGrid, a, b);
    if (r == 0x23) {
        goto fail;
    }
    if (c != 0 && InventoryItemGrid_IsSlotEmpty(&s->itemGrid, r)) {
        return 0x25;
    }
    return ChestMenu_GridToBoxSlot(s, r);
fail:
    return 0x25;
}

BOOL ChestMenu_DropHeldItem(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        u32 t = ChestMenu_GetSlotItem(s, a);
        if (t != 0xfff1) {
            u32 u = ChestMenu_GetSlotFlags(s, a);
            ChestMenu_SetSlotItem(s, s->pickUpSlot, t, u);
        }
        ChestMenu_ReleaseHeldItem(s, a);
        return TRUE;
    }
    return FALSE;
}

void ChestMenu_SetSlotItem(S *s, u32 a, u32 b, u32 c)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        u32 t = ChestMenu_ToGridSlot(s, a);
        InventoryItemGrid_SetSlotItem(&s->itemGrid, t, b, c);
        InventoryItemGrid_RefreshSlot(&s->itemGrid, t);
    } else if (ChestMenu_IsTabSlot(s, a)) {
        s32 t = (s->pickUpPage - 1) * 0xf;
        s->storageItems[t + s->pickUpOriginSlot] = b;
    }
}

u32 ChestMenu_GridToBoxSlotOr0F(S *s, u32 a)
{
    if (ChestMenu_IsBoxSlot(s, a)) {
        return (u8)a;
    }
    return 0xf;
}

u32 ChestMenu_GridToBoxSlot(S *s, u32 a)
{
    if (a >= 0xf && a <= 0x1d) {
        return (u8)a;
    }
    return 0x25;
}

u16 *ChestMenu_GetPageItems(S *s)
{
    return s->storageItems + s->currentPage * 0xf;
}

s32 ChestMenu_GetSlotX(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_GetSlotX(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
    if (ChestMenu_IsButtonSlot(s, a)) {
        return 0xc4;
    }
    if (ChestMenu_IsTabSlot(s, a)) {
        return Oam_GetObjX(&sChestPageTabSprites[(a - 0x1e) * 3].a) + 0x80;
    }
    return 0;
}

s32 ChestMenu_GetSlotY(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_GetSlotY(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
    if (ChestMenu_IsButtonSlot(s, a)) {
        return 0x70;
    }
    if (ChestMenu_IsTabSlot(s, a)) {
        return Oam_GetObjY((s8 *)&sChestPageTabSprites[(a - 0x1e) * 3]) + 0x68;
    }
    return 0;
}

BOOL ChestMenu_IsItemRejected(S *s, u32 a)
{
    if (ChestMenu_IsSlotEmpty(s, a)) {
        return FALSE;
    }
    if (ChestMenu_GetSlotFlags(s, a)) {
        return TRUE;
    }
    u32 t = ChestMenu_GetSlotItem(s, a);
    if (Shared_InvItem_IsTurnipFishOrInsect(t)) {
        return TRUE;
    }
    if (Shared_InvItem_IsNonTransferable(t)) {
        return TRUE;
    }
    return FALSE;
}

void ChestMenu_DisableRejectedItems(S *s)
{
    u32 i = 0;
    do {
        if (ChestMenu_IsItemRejected(s, i)) {
            InventoryItemGrid_DisableSlot(&s->itemGrid, ChestMenu_ToGridSlot(s, i));
        }
        i = (u8)(i + 1);
    } while (i <= 0xe);
}

BOOL ChestMenu_IsSlotDisabled(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        return Shared_InventoryItemGrid_IsSlotDisabled(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
    return FALSE;
}

BOOL ChestMenu_IsSlotEmpty(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_IsSlotEmpty(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
    return TRUE;
}

u32 ChestMenu_GetSlotItem(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        return Shared_InventoryItemGrid_GetSlotItem(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
    return 0xfff1;
}

u32 ChestMenu_GetSlotFlags(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        return InventoryItemGrid_GetSlotFlags(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
    return 0xf1;
}

void ChestMenu_ClearCursorSlots(S *s)
{
    InventoryItemGrid_ClearCursorSlot(&s->itemGrid);
    s->letterGrid.clearCursorSlot();
}

void ChestMenu_SetCursorSlot(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        Shared_InventoryItemGrid_SetCursorSlot(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
        s->letterGrid.clearCursorSlot();
    } else {
        ChestMenu_ClearCursorSlots(s);
    }
}

void ChestMenu_ClearMarks(S *s)
{
    Shared_InventoryItemGrid_ClearMarks(&s->itemGrid);
    s->letterGrid.clearMarks();
}

void ChestMenu_MarkSlot(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        InventoryItemGrid_MarkSlot(&s->itemGrid, ChestMenu_ToGridSlot(s, a));
    }
}

BOOL ChestMenu_HasTouchMoved(S *s)
{
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}

void ChestMenu_PlaceNameBalloon(S *s)
{
    s32 a = ChestMenu_GetSlotX(s, s->balloonSlot) - 0x6d;
    s32 b = ChestMenu_GetSlotY(s, s->balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) {
        b -= 8;
    }
    if (b < -0x5c) {
        s->nameBalloon.setPopDownward();
        b = ChestMenu_GetSlotY(s, s->balloonSlot) - 0x50;
    } else {
        s->nameBalloon.setPopUpward();
    }
    s->nameBalloon.setPos(a, b);
    if (ChestMenu_IsPocketSlot(s, s->balloonSlot) || ChestMenu_IsBoxSlot(s, s->balloonSlot)) {
        u32 t = ChestMenu_ToGridSlot(s, s->balloonSlot);
        Shared_InventoryItemGrid_ShowSlotName(&s->itemGrid, &s->nameBalloon, t);
    }
}

void ChestMenu_UpdateNameBalloon(S *s)
{
    if (ChestMenu_IsPocketSlot(s, s->cursorSlot) || ChestMenu_IsBoxSlot(s, s->cursorSlot)) {
        if (ChestMenu_IsSlotEmpty(s, s->cursorSlot)) {
            s->nameBalloon.cancelQueuedOpen();
        } else {
            s->balloonSlot = s->cursorSlot;
            s->nameBalloon.queueOpen();
        }
    } else {
        s->nameBalloon.cancelQueuedOpen();
    }
}

void ChestMenu_DrawHeldItem(S *s)
{
    if (!s->testFlags(0x40)) {
        u32 t = s->heldKind;
        if (t != 0) {
            if (t == 1) {
                InventoryItemGrid_DrawHeldItem(&s->itemGrid, s->heldX, s->heldY);
            }
        }
    }
}

void ChestMenu_TrackTouch(S *s)
{
    s->heldX = s->grabOffsetX + gTouchCurX;
    s->heldY = s->grabOffsetY + gTouchCurY;
}

void ChestMenu_TrackCursor(S *s)
{
    s->heldX = s->cursor.getFrameScreenX() - 2;
    s->heldY = s->cursor.getFrameScreenY() - 4;
    if (s->cursor.getAnim() == 1) {
        s->heldY -= 0x16;
    }
}

void ChestMenu_TrackFlyingItem(S *s)
{
    s->heldX = s->flyMotion.getX();
    s->heldY = s->flyMotion.getY();
}

void ChestMenu_PickUpItem(S *s, u32 a)
{
    if (ChestMenu_IsPocketSlot(s, a) || ChestMenu_IsBoxSlot(s, a)) {
        u32 t = ChestMenu_ToGridSlot(s, a);
        s->heldKind = 1;
        s->heldItem = Shared_InventoryItemGrid_GetSlotItem(&s->itemGrid, t);
        s->heldItemFlags = InventoryItemGrid_GetSlotFlags(&s->itemGrid, t);
        Shared_InventoryItemGrid_ClearSlot(&s->itemGrid, t);
        Shared_InventoryItemGrid_SetHeldItem(&s->itemGrid, s->heldItem, s->heldItemFlags);
    }
}

void ChestMenu_ReleaseHeldItem(S *s, u32 a)
{
    if (s->heldKind == 1) {
        ChestMenu_SetSlotItem(s, a, s->heldItem, s->heldItemFlags);
    }
    s->heldKind = 0;
}

void ChestMenu_ExchangeHeldItem(S *s, u32 a)
{
    if (s->heldKind == 1) {
        u32 h = s->heldItem;
        u32 b = s->heldItemFlags;
        ChestMenu_PickUpItem(s, a);
        ChestMenu_SetSlotItem(s, a, h, b);
    }
}

void ChestMenu_ShowCursor(S *s)
{
    s32 a = ChestMenu_GetCursorTargetX(s);
    s32 b = ChestMenu_GetCursorTargetY(s);
    s->cursor.warpTo(a, b);
    if (ChestMenu_IsButtonSlot(s, s->cursorSlot)) {
        s->cursor.setAnimIfChanged(7);
    } else {
        s->cursor.setAnimIfChanged(1);
    }
    ChestMenu_RefreshCursor(s);
}

s32 ChestMenu_GetCursorTargetX(S *s)
{
    s32 r = ChestMenu_GetSlotX(s, s->cursorSlot);
    if (s->testFlags(0x20)) {
        r += 0x100;
    } else if (s->testFlags(0x10)) {
        r -= 0x100;
    }
    r += 8;
    return r;
}

s32 ChestMenu_GetCursorTargetY(S *s)
{
    return ChestMenu_GetSlotY(s, s->cursorSlot);
}

void ChestMenu_HideCursor(S *s)
{
    s->cursor.setAnimIfChanged(0);
    s->cursor.update();
}

void ChestMenu_MoveCursorToTarget(S *s)
{
    if (s->testFlags(8)) {
        s32 a = ChestMenu_GetCursorTargetX(s);
        s32 b = ChestMenu_GetCursorTargetY(s);
        s->cursor.warpTo(a, b);
        s->clearFlags(8);
    } else {
        s32 a = ChestMenu_GetCursorTargetX(s);
        s32 b = ChestMenu_GetCursorTargetY(s);
        s->cursor.moveToEase(a, b, 3, 1);
        s->returnState = s->mainState;
        s->setMainState(5);
        if (s->testFlags(0x100)) {
            s->cursor.update();
            s->clearFlags(0x100);
        }
    }
}

void ChestMenu_RefreshCursor(S *s)
{
    s->cursor.setPoseIdle();
    s->cursor.update();
}

void ChestMenu::pressCursor() {
    cursor.setPosePress();
    setMainState(6);
}

void ChestMenu::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(7);
}

void ChestMenu::startPickUp() {
    cursor.setAnimIfChanged(4);
    setMainState(8);
}

void ChestMenu::startPutDown(u32 v) {
    nameBalloon.hide(1);
    actionSlot = v;
    cursor.setAnimIfChanged(5);
    setMainState(0xa);
}

void ChestMenu::startExchange(u32 v) {
    nameBalloon.hide(1);
    returnState = mainState;
    actionSlot = v;
    cursor.setAnimIfChanged(6);
    setMainState(0xb);
}

void ChestMenu::moveCursorInPockets(u32 pad, u32 b) {
    s32 col = cursorSlot;
    s32 row = 0;
    while (col >= 5) {
        col -= 5;
        row++;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (!MenuKeys_HasUp(pad) || row == 0) {
            if (col == 0) {
                if (b == 1) {
                    cursorSlot = cursorSlot + 4;
                } else {
                    cursorSlot = 0x24;
                }
                setFlags(0x10);
                return;
            } else {
                cursorSlot = cursorSlot - 1;
                col = col - 1;
                goto next;
            }
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (!MenuKeys_HasDown(pad)) {
            if (col == 4) {
                if (b == 1) {
                    cursorSlot = cursorSlot - 4;
                    setFlags(0x20);
                } else {
                    cursorSlot = 0x24;
                }
                return;
            }
            cursorSlot = cursorSlot + 1;
            col = col + 1;
        }
    }
next:
    if (MenuKeys_HasUp(pad)) {
        if (row > 0) {
            cursorSlot = cursorSlot - 5;
        } else {
            cursorSlot = col + 0x19;
        }
    } else if (MenuKeys_HasDown(pad)) {
        if (row < 2) {
            cursorSlot = cursorSlot + 5;
        }
    }
}

void ChestMenu::moveCursorInBox(u32 pad, u32 b) {
    s32 col = cursorSlot - 0xf;
    s32 row = 0;
    while (col >= 5) {
        col -= 5;
        row++;
    }
    if (MenuKeys_HasLeft(pad)) {
        if (!MenuKeys_HasUp(pad) || row == 0) {
            if (col == 0) {
                switch (row) {
                case 0:
                    cursorSlot = 0x20;
                    break;
                case 1:
                    cursorSlot = 0x23;
                    break;
                case 2:
                default:
                    if (b == 1) {
                        cursorSlot = cursorSlot + 4;
                    } else {
                        cursorSlot = 0x24;
                    }
                    break;
                }
                setFlags(0x10);
                return;
            } else {
                cursorSlot = cursorSlot - 1;
                col = col - 1;
                goto next;
            }
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (!MenuKeys_HasDown(pad)) {
            if (col == 4) {
                switch (row) {
                case 0:
                    cursorSlot = 0x1e;
                    break;
                case 1:
                    cursorSlot = 0x21;
                    break;
                case 2:
                default:
                    if (b == 1) {
                        cursorSlot = cursorSlot - 4;
                        setFlags(0x20);
                    } else {
                        cursorSlot = 0x24;
                    }
                    break;
                }
                return;
            }
            cursorSlot = cursorSlot + 1;
            col = col + 1;
        }
    }
next:
    if (MenuKeys_HasUp(pad)) {
        if (row > 0) {
            cursorSlot = cursorSlot - 5;
        }
    } else if (MenuKeys_HasDown(pad)) {
        if (row < 2) {
            cursorSlot = cursorSlot + 5;
        } else {
            cursorSlot = col;
        }
    }
}

void ChestMenu::moveCursorOnButtons(u32 pad) {
    if (MenuKeys_HasUp(pad)) {
        cursorSlot = 0x21;
    }
    if (MenuKeys_HasRight(pad)) {
        cursorSlot = 0;
        setFlags(0x20);
    } else if (MenuKeys_HasLeft(pad)) {
        cursorSlot = 4;
    }
}

void ChestMenu::moveCursorOnTabs(u32 pad, u32 b) {
    s32 col = cursorSlot - 0x1e;
    s32 row = 0;
    while (col >= 3) {
        col -= 3;
        row++;
    }
    if (MenuKeys_HasRight(pad)) {
        if (col < 2) {
            cursorSlot = cursorSlot + 1;
        } else {
            setFlags(0x20);
            cursorSlot = row * 5 + 0xf;
            return;
        }
    } else if (MenuKeys_HasLeft(pad)) {
        if (col > 0) {
            cursorSlot = cursorSlot - 1;
        } else {
            cursorSlot = row * 5 + 0x13;
            return;
        }
    }
    if (MenuKeys_HasUp(pad)) {
        if (row > 0) {
            cursorSlot = cursorSlot - 3;
        }
    } else if (MenuKeys_HasDown(pad)) {
        if (row < 1) {
            cursorSlot = cursorSlot + 3;
        } else if (b != 1) {
            cursorSlot = 0x24;
        }
    }
}

BOOL ChestMenu::moveCursorByPad(u32 pad, u32 b) {
    u8 old = cursorSlot;
    clearFlags(0x30);
    clearFlags(0x100);
    if (pad == 0) {
        return FALSE;
    }
    if (ChestMenu_IsPocketSlot(this, cursorSlot)) {
        moveCursorInPockets(pad, b);
    } else if (ChestMenu_IsBoxSlot(this, cursorSlot)) {
        moveCursorInBox(pad, b);
        if (b == 1) {
            if (ChestMenu_IsTabSlot(this, cursorSlot)) {
                cursor.setAnimIfChanged(1);
            }
        }
    } else if (ChestMenu_IsButtonSlot(this, cursorSlot)) {
        moveCursorOnButtons(pad);
    } else if (ChestMenu_IsTabSlot(this, cursorSlot)) {
        moveCursorOnTabs(pad, b);
        if (b == 1) {
            if (!ChestMenu_IsTabSlot(this, cursorSlot)) {
                cursor.setAnimAtEnd(4);
            }
        }
    }
    if (ChestMenu_IsButtonSlot(this, cursorSlot) != ChestMenu_IsButtonSlot(this, old)) {
        if (ChestMenu_IsButtonSlot(this, cursorSlot)) {
            cursor.switchToAnim07();
        } else {
            cursor.switchToAnim01();
        }
        setFlags(0x100);
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void ChestMenu::resetTextLabels() {
    s32 i;
    numTextLabels = 0;
    for (i = 0; i < 2; i++) {
        ((LabelString *)&textLabels[i])->destroyLabel();
    }
}

LabelString *ChestMenu::allocTextLabel() {
    if (numTextLabels >= 2) {
        return &textLabels[1];
    }
    numTextLabels = numTextLabels + 1;
    return &textLabels[numTextLabels - 1];
}

void ChestMenu::setOkLabel(s32 v) {
    u8 c = 1;
    if (v) {
        c = 0xf;
    }
    LabelString *o = allocTextLabel();
    o->createLabel(4, 0x1d6, 6, c, 9, 0);
    String_Load2dMenu(o, 0x88);
    o->redrawAligned(1, 0);
}

void ChestMenu::confirm(s32 v) {
    Snd_PlaySe(0x27);
    if (v) {
        delayTimer = 5;
    } else {
        delayTimer = 0;
    }
    setMainState(0xf);
    setOkLabel(1);
    MenuCtrl_SetResult(1);
    MI_CpuCopy8(storageItems, (u8 *)ChestStorage_GetItems((u16 *)PlayerData_GetDresser(PlayerData_GetCurrent())), 0xb4);
}

void ChestMenu::drawPageTabs() {
    u32 p0 = boxSlideY + 0x60;
    s32 i = 0, j = 0;
    s32 m = -1;
    do {
        u32 p;
        u32 q;
        if (i == currentPage) {
            p = p0 + 2;
            q = 4;
        } else {
            p = p0;
            q = 5;
        }
        Oam_DrawObj(1, &sChestPageTabSprites[j], 0x80, p, m, 1, NULL);
        Oam_DrawObj(1, &sChestPageTabSprites[j + 1], 0x80, p, q, 1, NULL);
        Oam_DrawObj(1, &sChestPageTabSprites[j + 2], 0x80, p0, m, 1, NULL);
        i++;
        j += 3;
    } while (i < 6);
}

BOOL ChestMenu::hitTestPageTab(s32 x, s32 y) {
    s32 i, j;
    s32 px = x - 0x80;
    s32 py = y - 0x60;
    for (i = 0, j = 0; i < 6; i++, j += 3) {
        if (i != currentPage) {
            if (Cell_HitTest(&sChestPageTabSprites[j], px, py, 2, 2)) {
                currentPage = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}

void ChestMenu::startPageSwitch() {
    nameBalloon.hide(1);
    ChestMenu_HideCursor(this);
    transitionState = 7;
    setPhase(1);
    Snd_PlaySe(sChestPageSe[currentPage]);
    setFlags(0x40);
}

s32 ChestMenu::handlePageKeys() {
    s32 dir = 0;
    u32 keys = gPad[1];
    if (keys & 0x200) {
        dir = -1;
    } else if (keys & 0x100) {
        dir = 1;
    }
    if (dir) {
        dir = dir + currentPage;
        if (dir < 0) {
            dir = 5;
        } else if (dir >= 6) {
            dir = 0;
        }
        currentPage = dir;
        startPageSwitch();
    }
    return 0;
}

BOOL ChestMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void ChestMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }

void ChestMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

extern "C" Unk_ov102_02297580_Ent sChestPageTabSprites[18] = {
    {0x402e00ac, 0x000061c6},
    {0x402e00ac, 0x0000411e},
    {0x402e00ae, 0x0000111e},
    {0x404200ac, 0x000061c8},
    {0x404200ac, 0x0000511e},
    {0x404200ae, 0x0000111e},
    {0x405600ac, 0x000061ca},
    {0x405600ac, 0x0000511e},
    {0x405600ae, 0x0000111e},
    {0x403800bf, 0x000061cc},
    {0x403800bf, 0x0000511e},
    {0x403800c1, 0x0000111e},
    {0x404c00bf, 0x000061ce},
    {0x404c00bf, 0x0000511e},
    {0x404c00c1, 0x0000111e},
    {0x406000bf, 0x000061d0},
    {0x406000bf, 0x0000511e},
    {0x406000c1, 0xffff111e},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov102_02294c40) {
    HOST_OVERLAY_VAR(sChestMenuProfile),
    HOST_OVERLAY_VAR(sChestPageTabSprites),
    HOST_OVERLAY_VARS_END
};

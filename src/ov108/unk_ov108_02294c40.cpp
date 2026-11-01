#include "types.h"
#include "host_tick.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "ui/CursorMotion.h"
#include "item/Letter.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02065330.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov108/unk_ov108_02294c40.h"

extern "C" {
extern u16 gPad[];

BOOL PopupChoice_MoveCursor(void *p, s32 a, void *b, s32 c);
BOOL PopupChoice_TickDecideDelay(void *p);
u8 PopupChoice_DecideCancel(void *p, s32 x);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *p);
void PopupChoice_Draw(void *p);
void PopupChoice_Update(void *p);
void PopupChoice_Close(void *p, u32 v);
void PopupChoice_Open(void *p, u32 v);
}





struct PopupChoiceIdList;



















class LetterGiveMenu;
typedef void (LetterGiveMenu::*Unk_ov108_02296b58_Fn)();

static inline BOOL Unk_ov108_022961d8_Both()
{
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

class LetterGiveMenu : public MenuProc {
public:
    LetterGiveMenu()
        : heldLetter(), swapLetter(), bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(), errorMessage(), bottomButtons() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32 mask);
    void setFlags(u32 mask);
    BOOL testFlags(u32 mask);
    BOOL moveCursorByPad(u32 keys, u32 x);
    void moveCursorInGrid(u32 keys, u32 x);
    void openLetterChoice(u32 idx, u32 x);
    void cancelChoice();
    void openPopup(u32 x);
    void onPopupChoice();
    void beginSwapAtSlot(u32 v);
    void beginPutBack(u32 v);
    void pressCloseButton();
    void refreshCursor();
    void showCursorAtSlot();
    void cursorToPopupTop();
    void cancelPopup();
    void moveCursorToPopupRow();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void swapCarriedLetter(u32 a);
    void dropCarriedLetter(u32 a);
    void pickUpLetter(u32 a);
    void setCarryPosFromMover();
    void setCarryPosFromCursor();
    void setCarryPosFromTouch();
    void drawCarriedLetter();
    void updateNameLabel();
    void refreshNameLabel();

    void setDropHighlight(u32 b);
    void clearDropHighlight();
    void showSlotFocus(u32 b);
    void hideSlotFocus();
    s32 isSlotEmpty(u32 b);
    s32 isSlotDisabled(u32 b);
    void setupLetterPanels();
    s32 getSlotY(u32 b);
    s32 getSlotX(u32 b);
    Letter *getLetter(u32 b);
    void setLetter(u32 b, Letter *c);
    BOOL dropOnSlot(u32 b);
    u32 hitTestSlot(u32 a, u32 b, u32 c);
    u32 letterIndexToSlot(u32 b);
    u32 slotToLetterIndex(u32 b);
    BOOL isLetterSlot(u32 b);
    void cancelBgTask();
    void startClose();
    void confirmGiveLetter();
    void flyLetterBack(u32 a, u32 c);
    void carryFromSlot(u32 b);
    void beginTouchSlot(u32 b);
    void resumeInput();
    void startButtonInput();
    void startTouchInput();

    void mainAct17();
    void mainAct16();
    void mainAct15();
    void mainAct14();
    void mainAct13();
    void mainAct12();
    void mainAct11();
    void mainAct10();
    void mainAct0F();
    void mainAct0E();
    void mainAct0D();
    void mainAct0C();
    void mainAct0B();
    void updateCursorMove();
    void mainAct09();
    void mainAct08();
    void mainAct07();
    void updateButtons();
    void mainAct05();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void updateTouch();

    void startPanels();
    void resetPanelUnk();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initLetterGive();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void stateLoad();
    void runMainState();

    /* 0x094 */ u32 stateFlags;
    /* 0x098 */ s32 slideY;
    /* 0x09c */ s32 dragOffsetX;
    /* 0x0a0 */ s32 dragOffsetY;
    /* 0x0a4 */ s32 handX;
    /* 0x0a8 */ s32 handY;
    /* 0x0ac */ Letter heldLetter;
    /* 0x1a0 */ Letter swapLetter;
    /* 0x294 */ u8 handKind;
    /* 0x295 */ u8 touchedSlot;
    /* 0x296 */ u8 balloonSlot;
    /* 0x297 */ u8 heldSlot;
    /* 0x298 */ u8 cursorSlot;
    /* 0x299 */ u8 selectedSlot;
    /* 0x29a */ u8 targetSlot;
    /* 0x29b */ u8 returnState;
    /* 0x29c */ u8 popupChoice;
    /* 0x29d */ u8 popupRow;
    /* 0x29e */ u8 touchHoldDelay;
    /* 0x29f */ u8 pad_29f;
    /* 0x2a0 */ BgVramTaskPair bgTasks[1];
    /* 0x2d8 */ InventoryItemGrid pocketGrid;
    /* 0xd38 */ LetterGrid letterGrid;
    /* 0xd60 */ InventoryBg inventoryBg;
    /* 0x2340 */ TouchPromptBalloon nameBalloon;
    /* 0x2400 */ CursorMotion flyMotion;
    /* 0x2418 */ MenuCursorBuf0 cursor;
    /* 0x247c */ PopupChoiceMenu popup;
    /* 0x2770 */ PopupChoiceIdList choiceList;
    /* 0x277b */ u8 pad_277b[1];
    /* 0x277c */ MenuErrorMessage errorMessage;
    /* 0x2884 */ MenuBottomButtons bottomButtons;
};

extern "C" LetterGiveMenu *LetterGiveMenu_Create() { return new LetterGiveMenu(); }


extern "C" ProcProfile sLetterGiveMenuProfile = {(void *(*)())LetterGiveMenu_Create, 0x9b, 0x9f};

BOOL LetterGiveMenu::onCreate() {
    initLetterGive();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL LetterGiveMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL LetterGiveMenu::onDraw() {
    s32 t;
    PopupChoice_Draw(&popup);
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)&cursor)->drawWrapped();
    }
    drawCarriedLetter();
    if (testFlags(2)) {
        bottomButtons.drawAt(slideY);
        t = slideY - 0x10;
        InventoryItemGrid_DrawPockets(&pocketGrid, 0, t);
        letterGrid.drawPocketLetters(0, t);
        Shared_InventoryBg_DrawSprite(&inventoryBg, t);
    }
    return TRUE;
}

BOOL LetterGiveMenu::execTransition() {
    static Unk_ov108_02296b58_Fn tbl[5] = {
        &LetterGiveMenu::stateLoad, &LetterGiveMenu::stateOpen,
        &LetterGiveMenu::stateOpening, &LetterGiveMenu::stateClose,
        &LetterGiveMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void LetterGiveMenu::runMainState() {
    static Unk_ov108_02296b58_Fn tbl[24] = {
        &LetterGiveMenu::updateTouch, &LetterGiveMenu::mainAct01,
        &LetterGiveMenu::mainAct02, &LetterGiveMenu::mainAct03,
        &LetterGiveMenu::mainAct04, &LetterGiveMenu::mainAct05,
        &LetterGiveMenu::updateButtons, &LetterGiveMenu::mainAct07,
        &LetterGiveMenu::mainAct08, &LetterGiveMenu::mainAct09,
        &LetterGiveMenu::updateCursorMove, &LetterGiveMenu::mainAct0B,
        &LetterGiveMenu::mainAct0C, &LetterGiveMenu::mainAct0D,
        &LetterGiveMenu::mainAct0E, &LetterGiveMenu::mainAct0F,
        &LetterGiveMenu::mainAct10, &LetterGiveMenu::mainAct11,
        &LetterGiveMenu::mainAct12, &LetterGiveMenu::mainAct13,
        &LetterGiveMenu::mainAct14, &LetterGiveMenu::mainAct15,
        &LetterGiveMenu::mainAct16, &LetterGiveMenu::mainAct17};
    (this->*tbl[mainState])();
}

BOOL LetterGiveMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL LetterGiveMenu::execPhase3() { return TRUE; }

BOOL LetterGiveMenu::execPhase4() { return TRUE; }

BOOL LetterGiveMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void LetterGiveMenu::stateLoad() {
    setupBgLayers();
    resetPanelUnk();
    setTransitionState(1);
}

void LetterGiveMenu::stateOpen() {
    startPanels();
    bottomButtons.setLayoutSingle05(0x65);
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    setupLetterPanels();
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, -16);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    slideY = getSlideOffsetY();
}

void LetterGiveMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    applySlideOffset(6, 0, -16);
    slideY = getSlideOffsetY();
}

void LetterGiveMenu::stateClose() {
    nameBalloon.hide(1);
    hideCursor();
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(8, 0, 0, 0x30);
    applySlideOffset(6, 0, -16);
    setTransitionState(4);
    slideY = getSlideOffsetY();
}

void LetterGiveMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        clearFlags(2);
        clearFlags(1);
        setPhase(5);
    } else {
        applySlideOffset(6, 0, -16);
    }
    slideY = getSlideOffsetY();
}

void LetterGiveMenu::initLetterGive() {
    stateFlags = 0;
    InventoryItemGrid_Init(&pocketGrid, 2);
    letterGrid.init(2);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonSlot = 0x16;
    flyMotion.reset();
    handKind = 0;
    cursorSlot = 0xb;
    popup.init(3, 1, 0);
    touchHoldDelay = 0;
}

void LetterGiveMenu::releaseResources() {
    cancelBgTask();
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&pocketGrid);
    PopupChoice_ForceClose(&popup);
    bottomButtons.freeTexts();
}

void LetterGiveMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void LetterGiveMenu::postInputUpdate() {
    postStateUpdate();
}

void LetterGiveMenu::preStateUpdate() {
    cancelBgTask();
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&pocketGrid);
    letterGrid.updateCursorLift();
    bottomButtons.freeTexts();
}

void LetterGiveMenu::postStateUpdate() {
    Shared_PopupChoice_Update(&popup);
    InventoryBg_Update(&inventoryBg);
    if (nameBalloon.updatePrompt()) {
        refreshNameLabel();
    }
}

void LetterGiveMenu::setupBgLayers() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void LetterGiveMenu::resetPanelUnk() {
    InventoryBg_Load(&inventoryBg, 0);
}

void LetterGiveMenu::startPanels() {
    InventoryBg_LoadObjGraphics();
    MenuButtons_LoadTextColors();
}

void LetterGiveMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov108_022961d8_Both()) {
            s32 r = hitTestSlot(gTouchCurX, gTouchCurY + 0x10, 1);
            if (r != 0x16) {
                beginTouchSlot(r);
            } else {
                if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(9)) {
                    startClose();
                }
            }
        }
    }
}

void LetterGiveMenu::mainAct01() {
    if (gTouchHeld == 0) {
        if (testFlags(4)) {
            setMainState(3);
            runMainState();
        } else {
            setMainState(0);
            nameBalloon.setAutoCloseTimer(0x3c);
        }
    } else {
        if (testFlags(4) && nameBalloon.isOpenOrOpening()) {
            if (touchHoldDelay != 0) {
                touchHoldDelay -= TICK_STEP_ENDS() ? 1 : 0;
            } else {
                openLetterChoice(touchedSlot, 1);
                setMainState(2);
            }
        } else {
            nameBalloon.commitOpen();
        }
    }
}

void LetterGiveMenu::mainAct02() {
    if (gTouchHeld == 0) {
        setMainState(5);
    }
}

void LetterGiveMenu::mainAct03() {
    if (nameBalloon.isOpenOrOpening()) {
        if (touchHoldDelay != 0) {
            touchHoldDelay -= TICK_STEP_ENDS() ? 1 : 0;
        } else {
            openLetterChoice(touchedSlot, 1);
            setMainState(2);
        }
    }
}

void LetterGiveMenu::mainAct04() {
    setCarryPosFromTouch();
    clearDropHighlight();
    s32 r = hitTestSlot(handX + 8, handY + 8, 0);
    if (r != 0x16) {
        if (gTouchHeld == 0) {
            if (isSlotDisabled(r) != 0 || dropOnSlot(r) == 0) {
                flyLetterBack(heldSlot, 4);
            } else {
                resumeInput();
            }
        } else {
            setDropHighlight(r);
        }
    } else {
        if (gTouchHeld == 0) {
            flyLetterBack(heldSlot, 4);
        }
    }
}

void LetterGiveMenu::mainAct05() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (checkSwitchToButtons(1)) {
            cancelChoice();
        } else if (Unk_ov108_022961d8_Both()) {
            s32 r = ((PopupChoiceMenuBody *)&popup)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
            if (r >= 0) {
                PopupChoice_DecideRow(&popup, r, 1);
                popupChoice = choiceList.values[r];
                setMainState(0x14);
            }
        }
    }
}

void LetterGiveMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        nameBalloon.hide(1);
    } else if (moveCursorByPad(takeRepeatedKeys(), 0)) {
        updateNameLabel();
        moveCursorToTarget();
        nameBalloon.hide(0);
    } else if (isSlotDisabled(cursorSlot) == 0 && (gPad[1] & 1) != 0) {
        if (isLetterSlot(cursorSlot)) {
            if (isSlotEmpty(cursorSlot) == 0) {
                openLetterChoice(cursorSlot, 0);
            }
        } else {
            pressCloseButton();
        }
    } else if ((gPad[1] & 2) != 0) {
        hideCursor();
        startClose();
        nameBalloon.hide(0);
    } else {
        nameBalloon.commitOpen();
    }
}

void LetterGiveMenu::mainAct07() {
    if (moveCursorByPad(takeRepeatedKeys(), 1)) {
        updateNameLabel();
        moveCursorToTarget();
        nameBalloon.hide(0);
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            if (isSlotEmpty(cursorSlot)) {
                beginPutBack(cursorSlot);
            } else {
                beginSwapAtSlot(cursorSlot);
            }
        } else if ((f & 2) != 0) {
            beginPutBack(heldSlot);
        } else {
            setCarryPosFromCursor();
            nameBalloon.commitOpen();
        }
    }
}

void LetterGiveMenu::mainAct08() {
    if (checkSwitchToTouch()) {
        cancelChoice();
    } else if (PopupChoice_MoveCursor(&popup, takeRepeatedKeys(), &popupRow, 0)) {
        moveCursorToPopupRow();
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            ((MenuCursor *)&cursor)->setPosePress();
            setMainState(9);
        } else if ((f & 2) != 0) {
            cancelPopup();
        }
    }
}

void LetterGiveMenu::mainAct09() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        PopupChoice_DecideRow(&popup, popupRow, 1);
        popupChoice = choiceList.values[popupRow];
        setMainState(0x14);
    }
}

void LetterGiveMenu::updateCursorMove() {
    if (((MenuCursorBase *)&cursor)->isMoving() == 0) {
        setMainState(returnState);
        if (returnState == 6) {
            showSlotFocus(cursorSlot);
        }
        runMainState();
    }
    setCarryPosFromCursor();
}

void LetterGiveMenu::mainAct0B() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
        setMainState(0x17);
    }
}

void LetterGiveMenu::mainAct0C() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        refreshCursor();
        setMainState(6);
    }
}

void LetterGiveMenu::mainAct0D() {
    if (((MenuCursorBase *)&cursor)->isGripping()) {
        carryFromSlot(cursorSlot);
        setMainState(0xe);
    }
}

void LetterGiveMenu::mainAct0E() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        setMainState(returnState);
    }
    setCarryPosFromCursor();
}

void LetterGiveMenu::mainAct0F() {
    if (((MenuCursorBase *)&cursor)->isGripping() == 0) {
        u32 a = targetSlot;
        if (cursorSlot == a) {
            dropOnSlot(a);
            updateNameLabel();
            setMainState(6);
        } else {
            flyLetterBack(a, 4);
        }
    } else {
        setCarryPosFromCursor();
    }
}

void LetterGiveMenu::mainAct10() {
    if (((MenuCursorBase *)&cursor)->func_ov002_022028fc() == 0) {
        swapCarriedLetter(targetSlot);
        setFlags(0x40);
        setMainState(0x11);
        updateNameLabel();
    } else {
        setMainState(6);
    }
}

void LetterGiveMenu::mainAct11() {
    if (((HandCursor *)&cursor)->isAnimDone()) {
        setMainState(returnState);
    }
    if (((MenuCursorBase *)&cursor)->isGripping()) {
        clearFlags(0x40);
        setCarryPosFromCursor();
    }
}

void LetterGiveMenu::mainAct12() {
    if (flyMotion.update()) {
        dropCarriedLetter(heldSlot);
        resumeInput();
    } else {
        setCarryPosFromMover();
    }
}

void LetterGiveMenu::mainAct13() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            cursorToPopupTop();
            setMainState(8);
        } else {
            setMainState(5);
        }
    }
}

void LetterGiveMenu::mainAct14() {
    if (PopupChoice_TickDecideDelay(&popup)) {
        PopupChoice_Close(&popup, 0);
        nameBalloon.hide(1);
        if (((HandCursor *)&cursor)->getAnim()) {
            showCursorAtSlot();
        }
        setMainState(0x15);
    }
}

void LetterGiveMenu::mainAct15() {
    if (((PopupChoiceMenuBody *)&popup)->isClosed()) {
        onPopupChoice();
    }
}

void LetterGiveMenu::mainAct16() {
    if (errorMessage.update(0)) {
        setMainState(returnState);
        ((HandCursor *)&cursor)->enableObjWindow();
    }
}

void LetterGiveMenu::mainAct17() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (((HandCursor *)&cursor)->getAnim()) {
            s32 r4 = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 r6 = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 r2 = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            ((MenuCursorBase *)&cursor)->warpTo(r4 + r6, r4 + r2);
        }
    } else {
        MenuCtrl_SetResult(0);
        transitionState = 3;
        setPhase(1);
        nameBalloon.hide(1);
        hideCursor();
    }
}

void LetterGiveMenu::startTouchInput() {
    hideCursor();
    hideSlotFocus();
    setMainState(0);
}

void LetterGiveMenu::startButtonInput() {
    balloonSlot = 0x16;
    showCursor();
    restartKeyRepeat();
    updateNameLabel();
    setMainState(6);
    showSlotFocus(cursorSlot);
}

void LetterGiveMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void LetterGiveMenu::beginTouchSlot(u32 b) {
    touchedSlot = b;
    setMainState(1);
    u32 r6 = gTouchCurX;
    u32 r7 = gTouchCurY;
    dragOffsetX = getSlotX(touchedSlot) - r6;
    dragOffsetY = getSlotY(touchedSlot) - r7;
    balloonSlot = b;
    nameBalloon.queueOpen();
    nameBalloon.commitOpen();
    touchHoldDelay = 2;
    if (isSlotDisabled(b)) {
        clearFlags(4);
    } else {
        setFlags(4);
    }
}

void LetterGiveMenu::carryFromSlot(u32 b) {
    heldSlot = b;
    nameBalloon.hide(1);
    pickUpLetter(b);
    if (handKind == 1) {
        returnState = 7;
    }
    setCarryPosFromCursor();
}

void LetterGiveMenu::flyLetterBack(u32 a, u32 c) {
    heldSlot = a;
    flyMotion.setPos(handX, handY);
    s32 r7 = getSlotX(a);
    s32 r2 = getSlotY(a);
    flyMotion.startLinear(r7, r2, c);
    flyMotion.update();
    setCarryPosFromMover();
    setMainState(0x12);
}

void LetterGiveMenu::confirmGiveLetter() {
    MenuCtrl_SetIndex((u8)(selectedSlot - 0xb));
    MenuCtrl_SetResult(1);
    transitionState = 3;
    setPhase(1);
    nameBalloon.hide(1);
    hideCursor();
}

void LetterGiveMenu::startClose() {
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
    setMainState(0x17);
    Snd_PlaySe(0x28);
}

void LetterGiveMenu::cancelBgTask() {
    ((BgVramTask *)&bgTasks)->cancel();
}

BOOL LetterGiveMenu::isLetterSlot(u32 b) {
    if (b >= 0xb && b <= 0x14) {
        return TRUE;
    }
    return FALSE;
}

u32 LetterGiveMenu::slotToLetterIndex(u32 b) {
    if (b >= 0xb && b <= 0x14) {
        return (u8)(b - 0xb);
    }
    return 0;
}

u32 LetterGiveMenu::letterIndexToSlot(u32 b) {
    if (b <= 9) {
        return (u8)(b + 0xb);
    }
    return 0x16;
}

u32 LetterGiveMenu::hitTestSlot(u32 a, u32 b, u32 c) {
    u32 r6 = letterGrid.findPocketLetterAt(a, b);
    if (r6 != 0x37) {
        if (c != 0) {
            if (LetterGrid_IsSlotEmpty(&letterGrid, r6) != 0) {
                return 0x16;
            }
        }
        return letterIndexToSlot(r6);
    }
    return 0x16;
}

BOOL LetterGiveMenu::dropOnSlot(u32 b) {
    if (isSlotEmpty(b) == 0) {
        Letter_Copy((LetterView *)&swapLetter, (LetterView *)getLetter(b));
        setLetter(heldSlot, &swapLetter);
    }
    dropCarriedLetter(b);
    return TRUE;
}

void LetterGiveMenu::setLetter(u32 b, Letter *c) {
    if (isLetterSlot(b)) {
        letterGrid.setLetter(slotToLetterIndex(b), c);
    }
}

Letter *LetterGiveMenu::getLetter(u32 b) {
    if (isLetterSlot(b)) {
        return (Letter *)letterGrid.getLetter(slotToLetterIndex(b));
    }
    return 0;
}

s32 LetterGiveMenu::getSlotX(u32 b) {
    if (isLetterSlot(b)) {
        return LetterGrid_GetSlotX(&letterGrid, slotToLetterIndex(b));
    }
    if (b == 0x15) {
        return 0xbc;
    }
    return 0;
}

s32 LetterGiveMenu::getSlotY(u32 b) {
    if (isLetterSlot(b)) {
        return Shared_LetterGrid_GetSlotY(&letterGrid, slotToLetterIndex(b)) - 0x10;
    }
    if (b == 0x15) {
        return 0xb6;
    }
    return 0;
}

void LetterGiveMenu::setupLetterPanels() {
    Shared_InventoryItemGrid_DisableSlotRange(&pocketGrid, 0, 0xe);
    letterGrid.highlightLetterKinds(3);
}

s32 LetterGiveMenu::isSlotDisabled(u32 b) {
    if (isLetterSlot(b)) {
        return letterGrid.isHighlighted(slotToLetterIndex(b));
    }
    return 0;
}

s32 LetterGiveMenu::isSlotEmpty(u32 b) {
    if (isLetterSlot(b)) {
        return LetterGrid_IsSlotEmpty(&letterGrid, slotToLetterIndex(b));
    }
    return 1;
}

void LetterGiveMenu::hideSlotFocus() {
    InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    letterGrid.clearCursorSlot();
}

void LetterGiveMenu::showSlotFocus(u32 b) {
    if (isLetterSlot(b)) {
        letterGrid.setCursorSlot(slotToLetterIndex(b));
        InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    } else {
        hideSlotFocus();
    }
}

void LetterGiveMenu::clearDropHighlight() {
    Shared_InventoryItemGrid_ClearMarks(&pocketGrid);
    letterGrid.clearMarks();
}

void LetterGiveMenu::setDropHighlight(u32 b) {
    if (isLetterSlot(b)) {
        letterGrid.markSlot(slotToLetterIndex(b));
    }
}

void LetterGiveMenu::refreshNameLabel() {
    s32 a = getSlotX(balloonSlot) - 0x6d;
    s32 b = getSlotY(balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) {
        b -= 8;
    }
    ((LabelBalloon *)&nameBalloon)->setPos(a, b);
    if (isLetterSlot(balloonSlot)) {
        s32 c = slotToLetterIndex(balloonSlot);
        letterGrid.showLetterName(&nameBalloon, c);
    }
}

void LetterGiveMenu::updateNameLabel() {
    if (isLetterSlot(cursorSlot)) {
        if (isSlotEmpty(cursorSlot)) {
            nameBalloon.cancelQueuedOpen();
        } else {
            balloonSlot = cursorSlot;
            nameBalloon.queueOpen();
        }
    } else {
        nameBalloon.cancelQueuedOpen();
    }
}

void LetterGiveMenu::drawCarriedLetter() {
    if (!testFlags(0x40)) {
        if (handKind != 0) {
            if (handKind == 1) {
                letterGrid.drawHeldLetter(handX, handY, &heldLetter);
            }
        }
    }
}

void LetterGiveMenu::setCarryPosFromTouch() {
    handX = dragOffsetX + gTouchCurX;
    handY = dragOffsetY + gTouchCurY;
}

void LetterGiveMenu::setCarryPosFromCursor() {
    handX = ((MenuCursorBase *)&cursor)->getFrameScreenX() - 2;
    handY = ((MenuCursorBase *)&cursor)->getFrameScreenY() - 4;
}

void LetterGiveMenu::setCarryPosFromMover() {
    handX = flyMotion.getX();
    handY = flyMotion.getY();
}

void LetterGiveMenu::pickUpLetter(u32 a) {
    if (isLetterSlot(a)) {
        s32 r4 = slotToLetterIndex(a);
        handKind = 1;
        Letter_Copy((LetterView *)&heldLetter, (LetterView *)letterGrid.getLetter(r4));
        letterGrid.clearLetter(r4);
    }
}

void LetterGiveMenu::dropCarriedLetter(u32 a) {
    if (handKind == 1) {
        setLetter(a, &heldLetter);
    }
    handKind = 0;
}

void LetterGiveMenu::swapCarriedLetter(u32 a) {
    if (handKind == 1) {
        Letter_Copy((LetterView *)&swapLetter, (LetterView *)&heldLetter);
        pickUpLetter(a);
        setLetter(a, &swapLetter);
    }
}

void LetterGiveMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
    if (cursorSlot == 0x15) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 LetterGiveMenu::getCursorTargetX() {
    s32 r = getSlotX(cursorSlot);
    if (testFlags(0x20)) {
        r += 0x100;
    } else if (testFlags(0x10)) {
        r -= 0x100;
    }
    return r + 8;
}

s32 LetterGiveMenu::getCursorTargetY() { return getSlotY(cursorSlot); }

void LetterGiveMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void LetterGiveMenu::moveCursorToTarget() {
    if (cursorSlot == 0x15) {
        ((MenuCursor *)&cursor)->switchToAnim07();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(0xa);
}

void LetterGiveMenu::moveCursorToPopupRow() {
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    ((MenuCursorBase *)&cursor)->moveToLinear(a, b, 2);
    returnState = mainState;
    setMainState(0xa);
}

void LetterGiveMenu::cancelPopup() {
    popupChoice = 1;
    popupRow = PopupChoice_DecideCancel(&popup, 1);
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
    ((HandCursor *)&cursor)->setAnimAtEnd(8);
    setMainState(0x14);
}

void LetterGiveMenu::cursorToPopupTop() {
    popupRow = 0;
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
}

void LetterGiveMenu::showCursorAtSlot() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
}

void LetterGiveMenu::refreshCursor() {
    ((MenuCursorBase *)&cursor)->setPoseIdle();
    cursor.update();
}

void LetterGiveMenu::pressCloseButton() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(0xb);
}

void LetterGiveMenu::beginPutBack(u32 v) {
    nameBalloon.hide(1);
    targetSlot = v;
    ((MenuCursor *)&cursor)->setAnimIfChanged(5);
    setMainState(0xf);
}

void LetterGiveMenu::beginSwapAtSlot(u32 v) {
    nameBalloon.hide(1);
    returnState = mainState;
    targetSlot = v;
    ((MenuCursor *)&cursor)->setAnimIfChanged(6);
    setMainState(0x10);
}

void LetterGiveMenu::onPopupChoice() {
    switch (popupChoice) {
    case 0:
        confirmGiveLetter();
        break;
    case 1:
    default:
        resumeInput();
        break;
    }
}

void LetterGiveMenu::openPopup(u32 x) {
    ((PopupChoiceMenuBody *)&popup)->setRowsFromIds(&choiceList, 0);
    s32 a = getSlotX(selectedSlot);
    s32 b = getSlotY(selectedSlot);
    if (x != 0) {
        popup.placeAboveBalloon((LabelBalloon *)&nameBalloon);
    } else {
        popup.placeNearPoint(a, b);
    }
    PopupChoice_Open(&popup, 0);
    setMainState(0x13);
}

void LetterGiveMenu::cancelChoice() {
    popupChoice = 1;
    showCursorAtSlot();
    PopupChoice_Close(&popup, 0);
    setMainState(0x15);
}

void LetterGiveMenu::openLetterChoice(u32 idx, u32 x) {
    selectedSlot = idx;
    ChoiceIdList_Clear((u8 *)&choiceList, 1);
    getLetter(idx);
    ChoiceIdList_Add((u8 *)&choiceList, 0xd, 0);
    ChoiceIdList_Add((u8 *)&choiceList, 2, 1);
    hideCursor();
    if (x == 0) {
        nameBalloon.hide(1);
    }
    openPopup(x);
}

void LetterGiveMenu::moveCursorInGrid(u32 pad, u32 x) {
    s32 r4 = cursorSlot - 0xb;
    s32 r6 = r4 >> 1;
    if (MenuKeys_HasLeft(pad)) {
        if ((r4 & 1) > 0) {
            cursorSlot = cursorSlot - 1;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if ((r4 & 1) < 1) {
            cursorSlot = cursorSlot + 1;
        }
    }
    if (isLetterSlot(cursorSlot)) {
        if (!testFlags(0x30)) {
            if (MenuKeys_HasUp(pad)) {
                if (r6 > 0) {
                    cursorSlot = cursorSlot - 2;
                }
            } else if (MenuKeys_HasDown(pad)) {
                if (r6 < 4) {
                    cursorSlot = cursorSlot + 2;
                } else {
                    cursorSlot = 0x15;
                }
            }
        }
    }
}

BOOL LetterGiveMenu::moveCursorByPad(u32 pad, u32 x) {
    u8 old = cursorSlot;
    clearFlags(0x30);
    if (pad == 0) {
        return FALSE;
    }
    if (isLetterSlot(cursorSlot)) {
        moveCursorInGrid(pad, x);
    } else if (cursorSlot == 0x15) {
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 0x13;
        }
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL LetterGiveMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void LetterGiveMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }


void LetterGiveMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov108_02294c40) {
    HOST_OVERLAY_VAR(sLetterGiveMenuProfile),
    HOST_OVERLAY_VARS_END
};

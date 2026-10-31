#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "ui/CursorMotion.h"
#include "menu/PopupChoiceIdList.h"
#include "ui/UiWidget.h"
#include "item/Letter.h"
#include "menu/InventoryItemGrid.h"
#include "menu/LetterGrid.h"
#include "menu/InventoryBg.h"
#include "ui/LetterRenderer.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "item/LetterView.h"
#include "ui/LabelButton.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelBalloon.h"
#include "gfx/BgVramTask.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuCursor.h"
#include "menu/PopupChoiceMenu.h"
#include "menu/MenuErrorMessage.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020b7d10.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov094/unk_ov094_02292360.h"
#include "proto/ov094/unk_ov094_02292da8.h"
#include "proto/ov094/unk_ov094_02293b90.h"
#include "proto/ov103/unk_ov103_02294c40.h"

extern "C" {
extern u16 gPad[];


BOOL PopupChoice_MoveCursor(void *p, s32 a, void *b, s32 c);
BOOL PopupChoice_TickDecideDelay(void *p);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *p);
void PopupChoice_Draw(void *p);
void PopupChoice_Update(void *p);
void PopupChoice_Close(void *p, s32 v);
void PopupChoice_Open(void *p, u32 v);

}








struct LetterView;



















class PocketLettersMenu;
typedef void (PocketLettersMenu::*Unk_ov103_02296da0_Fn)();

class PocketLettersMenu : public MenuProc {
public:
    PocketLettersMenu()
        : bgTasks(), pocketGrid(), letterGrid(), inventoryBg(), nameBalloon(), flyMotion(), cursor(), popup(), errorMessage(), letterView(), letterCloseButton(), heldLetter(), swapLetter() {}

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
    void closeLetterView();
    void startReadLetter();
    BOOL moveCursorByPad(u32 pad, u32 x);
    void moveCursorInGrid(u32 pad, u32 x);
    void selectLetter(u32 idx);
    void cancelPopupForButtons();
    void openPopup();
    void onPopupChoice();
    void beginSwapAt(u32 v);
    void beginPutDownAt(u32 v);
    void beginMoveFromPopup();
    void releaseCursor();
    void refreshCursor();
    void showCursorAtSlot();
    void cursorToPopupTop();
    void moveCursorToPopupRow();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void exchangeHeldWith(u32 idx);
    void releaseHeldTo(u32 idx);
    void pickUpFrom(u32 idx);
    void getFlyPos();
    void getHandPos();
    void getDragPos();
    void drawHeldItem();
    void updateBalloonForCursor();
    void placeBalloon();
    BOOL isTouchHeldFor(s32 a);
    BOOL hasTouchMoved();
    void setHoverSlot(u32 a);
    void clearHoverSlot();
    void setFocusSlot(u32 a);
    void clearFocusSlot();
    BOOL isSlotEmpty(u32 a);
    BOOL isSlotDisabled(u32 a);
    void disableAllPockets();
    s32 getSlotY(u32 a);
    s32 getSlotX(u32 a);
    LetterView *getSlotLetter(u32 a);
    void putLetterInSlot(u32 a, void *b);
    BOOL dropHeldOnSlot(u32 a);
    u32 getSlotAt(u32 a, u32 b, s32 c);
    u32 toSlotOrNone(u32 a);
    u32 toLetterIndex(u32 a);
    BOOL isLetterSlot(u32 a);
    void cancelBgTasks();
    void flyHeldTo(u32 a, u32 b);
    void pickUpAtSlot(u32 a);
    void beginDragFromSlot(u32 a);
    void beginTouchOnSlot(u32 a);
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void mainAct18();
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
    void mainAct0A();
    void mainAct09();
    void mainAct08();
    void mainAct07();
    void mainAct06();
    void mainAct05();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void loadObjGraphics();
    void loadInventoryBg();
    void setupBgLayer6();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initParts();
    void transitionAct08();
    void transitionAct07();
    void transitionAct06();
    void transitionAct05();
    void transitionAct04();
    void transitionAct03();
    void transitionAct02();
    void transitionAct01();
    void transitionAct00();
    void runMainState();

    /* 0x0094 */ BgVramTaskPair bgTasks[1];
    /* 0x00cc */ InventoryItemGrid pocketGrid;
    /* 0x0b2c */ LetterGrid letterGrid;
    /* 0x0b54 */ InventoryBg inventoryBg;
    /* 0x2134 */ TouchPromptBalloon nameBalloon;
    /* 0x21f4 */ CursorMotion flyMotion;
    /* 0x220c */ MenuCursorBuf0 cursor;
    /* 0x2270 */ PopupChoiceMenu popup;
    /* 0x2564 */ PopupChoiceIdList choiceList;
    /* 0x256f */ u8 pad_256f[1];
    /* 0x2570 */ MenuErrorMessage errorMessage;
    /* 0x2678 */ LetterRenderer letterView;
    /* 0x2888 */ MenuLabelButton letterCloseButton;
    /* 0x28f8 */ u32 stateFlags;
    /* 0x28fc */ s32 slideY;
    /* 0x2900 */ s32 dragOffsetX;
    /* 0x2904 */ s32 dragOffsetY;
    /* 0x2908 */ s32 handX;
    /* 0x290c */ s32 handY;
    /* 0x2910 */ Letter heldLetter;
    /* 0x2a04 */ Letter swapLetter;
    /* 0x2af8 */ u8 handKind;
    /* 0x2af9 */ u8 touchedSlot;
    /* 0x2afa */ u8 balloonSlot;
    /* 0x2afb */ u8 heldSlot;
    /* 0x2afc */ u8 cursorSlot;
    /* 0x2afd */ u8 selectedSlot;
    /* 0x2afe */ u8 targetSlot;
    /* 0x2aff */ u8 returnState;
    /* 0x2b00 */ u8 popupChoice;
    /* 0x2b01 */ u8 popupRow;
};

#ifndef HOST64
typedef char TouchPromptBalloon_SizeCheck[(sizeof(TouchPromptBalloon) == 0xc0) ? 1 : -1];
#endif
#ifndef HOST64
typedef char MenuCursorBuf0_SizeCheck[(sizeof(MenuCursorBuf0) == 0x64) ? 1 : -1];
#endif
#ifndef HOST64
typedef char Letter_SizeCheck[(sizeof(Letter) == 0xf4) ? 1 : -1];
#endif
#ifndef HOST64
typedef char InventoryBg_SizeCheck[(sizeof(InventoryBg) == 0x15e0) ? 1 : -1];
#endif
#ifndef HOST64
typedef char CursorMotion_SizeCheck[(sizeof(CursorMotion) == 0x18) ? 1 : -1];
#endif
#ifndef HOST64
typedef char InventoryItemGrid_SizeCheck[(sizeof(InventoryItemGrid) == 0xa60) ? 1 : -1];
#endif
#ifndef HOST64
typedef char LetterGrid_SizeCheck[(sizeof(LetterGrid) == 0x28) ? 1 : -1];
#endif
#ifndef HOST64
typedef char BgVramTaskPair_SizeCheck[(sizeof(BgVramTaskPair) == 0x38) ? 1 : -1];
#endif

static inline BOOL Unk_ov103_02295f10_Both()
{
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}


extern "C" PocketLettersMenu *PocketLettersMenu_Create() { return new PocketLettersMenu(); }

BOOL PocketLettersMenu::onCreate() {
    initParts();
    setTransitionState(0);
    setPhase(0);
    return TRUE;
}

BOOL PocketLettersMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL PocketLettersMenu::onDraw() {
    PopupChoice_Draw(&popup);
    if (!testFlags(1)) {
        return TRUE;
    }
    nameBalloon.draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    drawHeldItem();
    if (testFlags(2)) {
        InventoryItemGrid_DrawPockets(&pocketGrid, 0, slideY);
        letterGrid.drawPocketLetters(0, slideY);
        Shared_InventoryBg_DrawSprite(&inventoryBg, slideY);
    }
    if (testFlags(0x80)) {
        s32 r = getSlideOffsetY();
        letterCloseButton.setPos(0, r);
        letterCloseButton.draw();
    }
    return TRUE;
}
extern "C" ProcProfile sPocketLettersMenuProfile;


extern "C" ProcProfile sPocketLettersMenuProfile = {(void *(*)())PocketLettersMenu_Create, 0x96, 0x9a};

BOOL PocketLettersMenu::execTransition() {
    static Unk_ov103_02296da0_Fn tbl[9] = {
        &PocketLettersMenu::transitionAct00, &PocketLettersMenu::transitionAct01,
        &PocketLettersMenu::transitionAct02, &PocketLettersMenu::transitionAct03,
        &PocketLettersMenu::transitionAct04, &PocketLettersMenu::transitionAct05,
        &PocketLettersMenu::transitionAct06, &PocketLettersMenu::transitionAct07,
        &PocketLettersMenu::transitionAct08};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void PocketLettersMenu::runMainState() {
    static Unk_ov103_02296da0_Fn tbl[25] = {
        &PocketLettersMenu::mainAct00, &PocketLettersMenu::mainAct01,
        &PocketLettersMenu::mainAct02, &PocketLettersMenu::mainAct03,
        &PocketLettersMenu::mainAct04, &PocketLettersMenu::mainAct05,
        &PocketLettersMenu::mainAct06, &PocketLettersMenu::mainAct07,
        &PocketLettersMenu::mainAct08, &PocketLettersMenu::mainAct09,
        &PocketLettersMenu::mainAct0A, &PocketLettersMenu::mainAct0B,
        &PocketLettersMenu::mainAct0C, &PocketLettersMenu::mainAct0D,
        &PocketLettersMenu::mainAct0E, &PocketLettersMenu::mainAct0F,
        &PocketLettersMenu::mainAct10, &PocketLettersMenu::mainAct11,
        &PocketLettersMenu::mainAct12, &PocketLettersMenu::mainAct13,
        &PocketLettersMenu::mainAct14, &PocketLettersMenu::mainAct15,
        &PocketLettersMenu::mainAct16, &PocketLettersMenu::mainAct17,
        &PocketLettersMenu::mainAct18};
    (this->*tbl[mainState])();
}

BOOL PocketLettersMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL PocketLettersMenu::execPhase3() { return TRUE; }

BOOL PocketLettersMenu::execPhase4() { return TRUE; }

BOOL PocketLettersMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void PocketLettersMenu::transitionAct00() {
    setupBgLayer6();
    loadInventoryBg();
    setTransitionState(1);
}

void PocketLettersMenu::transitionAct01() {
    loadObjGraphics();
    Shared_InventoryItemGrid_LoadPockets(&pocketGrid);
    Shared_LetterGrid_LoadPocketLetters(&letterGrid);
    disableAllPockets();
    beginSubSlideIn(8, 0, 0, 0x30);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0);
    setTransitionState(2);
    setFlags(1);
    setFlags(2);
    slideY = getSlideOffsetY();
}

void PocketLettersMenu::transitionAct02() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void PocketLettersMenu::transitionAct03() {
    nameBalloon.hide(1);
    hideCursor();
    if (testFlags(0x100) == 0) {
        ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    }
    beginSubSlideOut(8, 0, 0, 0x30);
    applySlideOffset(6, 0, 0);
    setTransitionState(4);
    slideY = getSlideOffsetY();
}

void PocketLettersMenu::transitionAct04() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        clearFlags(2);
        if (testFlags(0x100)) {
            setTransitionState(5);
            transitionAct05();
        } else {
            clearFlags(1);
            setPhase(5);
        }
    } else {
        applySlideOffset(6, 0, 0);
    }
    slideY = getSlideOffsetY();
}

void PocketLettersMenu::transitionAct05() {
    LetterView *t = getSlotLetter(selectedSlot);
    Letter_MarkRead(t);
    letterView.show(t, 3, 4, 1);
    beginSubSlideIn(3, 0, 0, 0x30);
    Gfx2d_ShowLayer(3);
    applySlideOffset(3, 0, 0);
    Gfx2d_ShowLayer(4);
    applySlideOffset(4, 0, 0);
    setTransitionState(6);
    letterCloseButton.showDefault(0x88);
    setFlags(0x80);
}

void PocketLettersMenu::transitionAct06() {
    if (stepSlideIn(0)) {
        setPhase(2);
        if (MenuCtrl_IsTouch()) {
            setMainState(3);
        } else {
            setMainState(7);
        }
    } else {
        applySlideOffset(3, 0, 0);
        applySlideOffset(4, 0, 0);
    }
}

void PocketLettersMenu::transitionAct07() {
    beginSubSlideOut(3, 0, 0, 0x30);
    applySlideOffset(3, 0, 0);
    applySlideOffset(4, 0, 0);
    setTransitionState(8);
}

void PocketLettersMenu::transitionAct08() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(3);
        Gfx2d_ResetLayer(4);
        clearFlags(0x80);
        transitionAct00();
    } else {
        applySlideOffset(3, 0, 0);
        applySlideOffset(4, 0, 0);
    }
}

void PocketLettersMenu::initParts() {
    stateFlags = 0;
    InventoryItemGrid_Init(&pocketGrid, 2);
    letterGrid.init(2);
    Shared_InventoryBg_Init(&inventoryBg, 6);
    balloonSlot = 0x15;
    flyMotion.reset();
    handKind = 0;
    cursorSlot = 0xb;
    popup.init(3, 1, 0);
    letterView.setLayer(3);
}

void PocketLettersMenu::releaseResources() {
    cancelBgTasks();
    InventoryBg_Exit(&inventoryBg);
    Shared_InventoryItemGrid_Exit(&pocketGrid);
    PopupChoice_ForceClose(&popup);
    letterView.release();
}

void PocketLettersMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void PocketLettersMenu::postInputUpdate() {
    postStateUpdate();
}

void PocketLettersMenu::preStateUpdate() {
    cancelBgTasks();
    Shared_InventoryBg_PreUpdate(&inventoryBg);
    InventoryItemGrid_PreUpdate(&pocketGrid);
    letterGrid.updateCursorLift();
}

void PocketLettersMenu::postStateUpdate() {
    Shared_PopupChoice_Update(&popup);
    InventoryBg_Update(&inventoryBg);
    if (nameBalloon.updatePrompt()) {
        placeBalloon();
    }
}

void PocketLettersMenu::setupBgLayer6() {
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void PocketLettersMenu::loadInventoryBg() {
    InventoryBg_Load(&inventoryBg, 0);
}

void PocketLettersMenu::loadObjGraphics() {
    InventoryBg_LoadObjGraphics();
}

void PocketLettersMenu::mainAct00() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov103_02295f10_Both()) {
            s32 r = getSlotAt(gTouchCurX, gTouchCurY, 1);
            if (r != 0x15) {
                beginTouchOnSlot(r);
            }
        }
    }
}

void PocketLettersMenu::mainAct01() {
    if (gTouchHeld == 0) {
        setMainState(0);
        nameBalloon.setAutoCloseTimer(0x3c);
    } else {
        if (testFlags(4)) {
            if (hasTouchMoved()) {
                beginDragFromSlot(touchedSlot);
                return;
            }
            if (isTouchHeldFor(9)) {
                selectLetter(touchedSlot);
                return;
            }
        }
        nameBalloon.commitOpen();
    }
}

void PocketLettersMenu::mainAct02() {
    getDragPos();
    clearHoverSlot();
    s32 r = getSlotAt(handX + 8, handY + 8, 0);
    if (r != 0x15) {
        if (gTouchHeld == 0) {
            if (isSlotDisabled(r) != 0 || dropHeldOnSlot(r) == 0) {
                flyHeldTo(heldSlot, 4);
            } else {
                resumeInput();
            }
        } else {
            setHoverSlot(r);
        }
    } else if (gTouchHeld == 0) {
        flyHeldTo(heldSlot, 4);
    }
}

void PocketLettersMenu::mainAct03() {
    if (checkSwitchToButtons(1)) {
        setMainState(7);
    } else {
        if (letterCloseButton.isTouched()) {
            closeLetterView();
        }
    }
}

void PocketLettersMenu::mainAct04() {
    if (checkSwitchToButtons(1)) {
        cancelPopupForButtons();
    } else {
        if (Unk_ov103_02295f10_Both()) {
            s32 t = ((PopupChoiceMenuBody *)&popup)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
            if (t >= 0) {
                PopupChoice_DecideRow(&popup, t, 1);
                popupChoice = choiceList.values[t];
                setMainState(0x15);
            }
        }
    }
}

void PocketLettersMenu::mainAct05() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        nameBalloon.hide(1);
    } else if (moveCursorByPad(takeRepeatedKeys(), 0)) {
        updateBalloonForCursor();
        moveCursorToTarget();
        nameBalloon.hide(0);
    } else if (isSlotDisabled(cursorSlot) == 0 && (gPad[1] & 1) != 0) {
        if (isLetterSlot(cursorSlot)) {
            if (isSlotEmpty(cursorSlot) == 0) {
                selectLetter(cursorSlot);
            }
        }
    } else {
        if ((gPad[1] & 0x800) != 0) {
            transitionState = 3;
            setPhase(1);
            nameBalloon.hide(1);
            hideCursor();
            clearFlags(0x100);
        } else {
            nameBalloon.commitOpen();
        }
    }
}

void PocketLettersMenu::mainAct06() {
    if (moveCursorByPad(takeRepeatedKeys(), 1)) {
        updateBalloonForCursor();
        moveCursorToTarget();
        nameBalloon.hide(0);
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            if (isSlotEmpty(cursorSlot)) {
                beginPutDownAt(cursorSlot);
            } else {
                beginSwapAt(cursorSlot);
            }
        } else if ((f & 2) != 0) {
            beginPutDownAt(heldSlot);
        } else {
            getHandPos();
            nameBalloon.commitOpen();
        }
    }
}

void PocketLettersMenu::mainAct07() {
    if (cursor.getAnim() == 0) {
        s32 a = letterCloseButton.getAnchorX(1);
        s32 b = letterCloseButton.getAnchorY(1);
        cursor.warpTo(a, b);
        cursor.setAnimIfChanged(1);
    }
    if (checkSwitchToTouch()) {
        hideCursor();
        setMainState(3);
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0 || (f & 2) != 0) {
            cursor.setPosePress();
            setMainState(8);
        }
    }
}

void PocketLettersMenu::mainAct08() {
    if (cursor.isAnimDone()) {
        closeLetterView();
    }
}

void PocketLettersMenu::mainAct09() {
    if (checkSwitchToTouch()) {
        cancelPopupForButtons();
    } else if (PopupChoice_MoveCursor(&popup, takeRepeatedKeys(), &popupRow, 0)) {
        moveCursorToPopupRow();
    } else {
        u16 f = gPad[1];
        if ((f & 1) != 0) {
            cursor.setPosePress();
            setMainState(0xa);
        } else if ((f & 2) != 0) {
            cancelPopupForButtons();
        }
    }
}

void PocketLettersMenu::mainAct0A() {
    if (cursor.isAnimDone()) {
        PopupChoice_DecideRow(&popup, popupRow, 1);
        popupChoice = choiceList.values[popupRow];
        setMainState(0x15);
    }
}

void PocketLettersMenu::mainAct0B() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        if (returnState == 5) {
            setFocusSlot(cursorSlot);
        }
        runMainState();
    }
    getHandPos();
}

void PocketLettersMenu::mainAct0C() {
    if (cursor.isAnimDone()) {
        releaseCursor();
    }
}

void PocketLettersMenu::mainAct0D() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(5);
    }
}

void PocketLettersMenu::mainAct0E() {
    if (cursor.isGripping()) {
        pickUpAtSlot(cursorSlot);
        setMainState(0xf);
    }
}

void PocketLettersMenu::mainAct0F() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    getHandPos();
}

void PocketLettersMenu::mainAct10() {
    if (!cursor.isGripping()) {
        u32 a = targetSlot;
        if (cursorSlot == a) {
            dropHeldOnSlot(a);
            updateBalloonForCursor();
            setMainState(5);
        } else {
            flyHeldTo(a, 4);
        }
    } else {
        getHandPos();
    }
}

void PocketLettersMenu::mainAct11() {
    if (!cursor.func_ov002_022028fc()) {
        exchangeHeldWith(targetSlot);
        setFlags(0x40);
        setMainState(0x12);
        updateBalloonForCursor();
    } else {
        setMainState(5);
    }
}

void PocketLettersMenu::mainAct12() {
    if (cursor.isAnimDone()) {
        setMainState(returnState);
    }
    if (cursor.isGripping()) {
        clearFlags(0x40);
        getHandPos();
    }
}

void PocketLettersMenu::mainAct13() {
    if (flyMotion.update()) {
        releaseHeldTo(heldSlot);
        resumeInput();
    } else {
        getFlyPos();
    }
}

void PocketLettersMenu::mainAct14() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            cursorToPopupTop();
            setMainState(9);
        } else {
            setMainState(4);
        }
    }
}

void PocketLettersMenu::mainAct15() {
    if (PopupChoice_TickDecideDelay(&popup)) {
        PopupChoice_Close(&popup, 0);
        if (cursor.getAnim()) {
            showCursorAtSlot();
        }
        setMainState(0x16);
    }
}

void PocketLettersMenu::mainAct16() {
    if (((PopupChoiceMenuBody *)&popup)->isClosed()) {
        onPopupChoice();
    }
}

void PocketLettersMenu::mainAct17() {
    if (errorMessage.update(0)) {
        setMainState(returnState);
        cursor.enableObjWindow();
    }
}

void PocketLettersMenu::mainAct18() {
    if (letterCloseButton.stepAnim()) {
        if (cursor.getAnim()) {
            s32 r4 = letterCloseButton.getAnchorX(1);
            s32 r2 = letterCloseButton.getAnchorY(1);
            cursor.warpTo(r4, r2);
        }
    } else {
        hideCursor();
        setTransitionState(7);
        setPhase(1);
    }
}

void PocketLettersMenu::startTouchInput() {
    hideCursor();
    clearFocusSlot();
    setMainState(0);
}

void PocketLettersMenu::startButtonInput() {
    balloonSlot = 0x15;
    showCursor();
    restartKeyRepeat();
    updateBalloonForCursor();
    setMainState(5);
    setFocusSlot(cursorSlot);
}

void PocketLettersMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void PocketLettersMenu::beginTouchOnSlot(u32 a) {
    u32 r6, r7;
    touchedSlot = a;
    setMainState(1);
    r6 = gTouchCurX;
    r7 = gTouchCurY;
    dragOffsetX = getSlotX(touchedSlot) - r6;
    dragOffsetY = getSlotY(touchedSlot) - r7;
    balloonSlot = a;
    nameBalloon.queueOpen();
    if (isSlotDisabled(a)) {
        clearFlags(4);
    } else {
        setFlags(4);
    }
}

void PocketLettersMenu::beginDragFromSlot(u32 a) {
    heldSlot = a;
    nameBalloon.hide(1);
    pickUpFrom(a);
    if (handKind == 1) setMainState(2);
    getDragPos();
}

void PocketLettersMenu::pickUpAtSlot(u32 a) {
    heldSlot = a;
    nameBalloon.hide(1);
    pickUpFrom(a);
    if (handKind == 1) returnState = 6;
    getHandPos();
}

void PocketLettersMenu::flyHeldTo(u32 a, u32 b) {
    heldSlot = a;
    flyMotion.setPos(handX, handY);
    s32 x = getSlotX(a);
    flyMotion.startLinear(x, getSlotY(a), b);
    flyMotion.update();
    getFlyPos();
    setMainState(0x13);
}

void PocketLettersMenu::cancelBgTasks() {
    bgTasks->cancel();
}

BOOL PocketLettersMenu::isLetterSlot(u32 a) {
    if (a >= 0xb && a <= 0x14) return TRUE;
    return FALSE;
}

u32 PocketLettersMenu::toLetterIndex(u32 a) {
    if (a >= 0xb && a <= 0x14) return (u8)(a - 11);
    return 0;
}

u32 PocketLettersMenu::toSlotOrNone(u32 a) {
    if (a <= 9) return (u8)(a + 11);
    return 0x15;
}

u32 PocketLettersMenu::getSlotAt(u32 a, u32 b, s32 c) {
    u32 t = letterGrid.findPocketLetterAt(a, b);
    if (t != 0x37) {
        if (c != 0) {
            if (LetterGrid_IsSlotEmpty(&letterGrid, t)) return 0x15;
        }
        return toSlotOrNone(t);
    }
    return 0x15;
}

BOOL PocketLettersMenu::dropHeldOnSlot(u32 a) {
    if (!isSlotEmpty(a)) {
        Letter_Copy((LetterView *)&swapLetter, (const LetterView *)getSlotLetter(a));
        putLetterInSlot(heldSlot, &swapLetter);
    }
    releaseHeldTo(a);
    return TRUE;
}

void PocketLettersMenu::putLetterInSlot(u32 a, void *b) {
    if (isLetterSlot(a)) {
        letterGrid.setLetter(toLetterIndex(a), b);
    }
}

LetterView *PocketLettersMenu::getSlotLetter(u32 a) {
    if (isLetterSlot(a)) {
        return (LetterView *)letterGrid.getLetter(toLetterIndex(a));
    }
    return NULL;
}

s32 PocketLettersMenu::getSlotX(u32 a) {
    if (isLetterSlot(a)) {
        return LetterGrid_GetSlotX(&letterGrid, toLetterIndex(a));
    }
    return 0;
}

s32 PocketLettersMenu::getSlotY(u32 a) {
    if (isLetterSlot(a)) {
        return Shared_LetterGrid_GetSlotY(&letterGrid, toLetterIndex(a));
    }
    return 0;
}

void PocketLettersMenu::disableAllPockets() {
    Shared_InventoryItemGrid_DisableSlotRange(&pocketGrid, 0, 0xe);
}

BOOL PocketLettersMenu::isSlotDisabled(u32 a) {
    if (isLetterSlot(a)) {
        return letterGrid.isHighlighted(toLetterIndex(a));
    }
    return FALSE;
}

BOOL PocketLettersMenu::isSlotEmpty(u32 a) {
    if (isLetterSlot(a)) {
        return LetterGrid_IsSlotEmpty(&letterGrid, toLetterIndex(a));
    }
    return TRUE;
}

void PocketLettersMenu::clearFocusSlot() {
    InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    letterGrid.clearCursorSlot();
}

void PocketLettersMenu::setFocusSlot(u32 a) {
    if (isLetterSlot(a)) {
        letterGrid.setCursorSlot(toLetterIndex(a));
        InventoryItemGrid_ClearCursorSlot(&pocketGrid);
    } else {
        clearFocusSlot();
    }
}

void PocketLettersMenu::clearHoverSlot() {
    Shared_InventoryItemGrid_ClearMarks(&pocketGrid);
    letterGrid.clearMarks();
}

void PocketLettersMenu::setHoverSlot(u32 a) {
    if (isLetterSlot(a)) {
        letterGrid.markSlot(toLetterIndex(a));
    }
}

BOOL PocketLettersMenu::hasTouchMoved() {
    s32 d = gTouchPressX - gTouchCurX;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    d = gTouchPressY - gTouchCurY;
    if (d < 0) d = -d;
    if (d > 8) return TRUE;
    return FALSE;
}

BOOL PocketLettersMenu::isTouchHeldFor(s32 a) {
    if (gTouchHoldFrames < a) return FALSE;
    return TRUE;
}

void PocketLettersMenu::placeBalloon() {
    s32 r6 = getSlotX(balloonSlot) - 0x6d;
    s32 r4 = getSlotY(balloonSlot) - 0x78;
    if (MenuCtrl_IsButtons()) r4 -= 8;
    nameBalloon.setPos(r6, r4);
    if (isLetterSlot(balloonSlot)) {
        letterGrid.showLetterName(&nameBalloon, toLetterIndex(balloonSlot));
    }
}

void PocketLettersMenu::updateBalloonForCursor() {
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

void PocketLettersMenu::drawHeldItem() {
    if (!testFlags(0x40)) {
        switch (handKind) {
        case 0:
            break;
        case 1:
            letterGrid.drawHeldLetter(handX, handY, &heldLetter);
            break;
        }
    }
}

void PocketLettersMenu::getDragPos() {
    handX = dragOffsetX + gTouchCurX;
    handY = dragOffsetY + gTouchCurY;
}

void PocketLettersMenu::getHandPos() {
    handX = cursor.getFrameScreenX() - 2;
    handY = cursor.getFrameScreenY() - 4;
}

void PocketLettersMenu::getFlyPos() {
    handX = flyMotion.getX();
    handY = flyMotion.getY();
}

void PocketLettersMenu::pickUpFrom(u32 idx) {
    if (isLetterSlot(idx)) {
        s32 r4 = toLetterIndex(idx);
        handKind = 1;
        void *r = letterGrid.getLetter(r4);
        Letter_Copy((LetterView *)&heldLetter, (const LetterView *)r);
        letterGrid.clearLetter(r4);
    }
}

void PocketLettersMenu::releaseHeldTo(u32 idx) {
    if (handKind == 1) {
        putLetterInSlot(idx, &heldLetter);
    }
    handKind = 0;
}

void PocketLettersMenu::exchangeHeldWith(u32 idx) {
    if (handKind == 1) {
        Letter_Copy((LetterView *)&swapLetter, (const LetterView *)&heldLetter);
        pickUpFrom(idx);
        putLetterInSlot(idx, &swapLetter);
    }
}

void PocketLettersMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    cursor.setAnimIfChanged(1);
    refreshCursor();
}

s32 PocketLettersMenu::getCursorTargetX() {
    s32 r = getSlotX(cursorSlot);
    if (testFlags(0x20)) {
        r += 0x100;
    } else if (testFlags(0x10)) {
        r -= 0x100;
    }
    return r + 8;
}

s32 PocketLettersMenu::getCursorTargetY() { return getSlotY(cursorSlot); }

void PocketLettersMenu::hideCursor() {
    cursor.setAnimIfChanged(0);
    cursor.update();
}

void PocketLettersMenu::moveCursorToTarget() {
    if (testFlags(8)) {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.warpTo(a, b);
        clearFlags(8);
    } else {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.moveToEase(a, b, 3, 1);
        returnState = mainState;
        setMainState(0xb);
    }
}

void PocketLettersMenu::moveCursorToPopupRow() {
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    cursor.moveToLinear(a, b, 2);
    returnState = mainState;
    setMainState(0xb);
}

void PocketLettersMenu::cursorToPopupTop() {
    popupRow = 0;
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    cursor.warpTo(a, b);
    cursor.setAnimIfChanged(7);
}

void PocketLettersMenu::showCursorAtSlot() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    cursor.setAnimIfChanged(1);
}

void PocketLettersMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void PocketLettersMenu::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(0xd);
}

void PocketLettersMenu::beginMoveFromPopup() {
    cursor.setAnimIfChanged(4);
    setMainState(0xe);
}

void PocketLettersMenu::beginPutDownAt(u32 v) {
    nameBalloon.hide(1);
    targetSlot = v;
    cursor.setAnimIfChanged(5);
    setMainState(0x10);
}

void PocketLettersMenu::beginSwapAt(u32 v) {
    nameBalloon.hide(1);
    returnState = mainState;
    targetSlot = v;
    cursor.setAnimIfChanged(6);
    setMainState(0x11);
}

void PocketLettersMenu::onPopupChoice() {
    switch (popupChoice) {
    case 0:
        beginMoveFromPopup();
        break;
    case 1:
        startReadLetter();
        break;
    case 3:
    default:
        resumeInput();
        break;
    }
}

void PocketLettersMenu::openPopup() {
    ((PopupChoiceMenuBody *)&popup)->setRowsFromIds(&choiceList, 0);
    s32 a = getSlotX(selectedSlot);
    s32 b = getSlotY(selectedSlot);
    popup.placeNearPoint(a, b);
    PopupChoice_Open(&popup, 0);
    setMainState(0x14);
}

void PocketLettersMenu::cancelPopupForButtons() {
    popupChoice = 3;
    showCursorAtSlot();
    PopupChoice_Close(&popup, 0);
    setMainState(0x16);
}

void PocketLettersMenu::selectLetter(u32 idx) {
    selectedSlot = idx;
    ChoiceIdList_Clear((u8 *)&choiceList, 3);
    LetterView *r6 = getSlotLetter(idx);
    if (MenuCtrl_IsButtons()) {
        ChoiceIdList_Add((u8 *)&choiceList, 0, 0);
    }
    s32 r4 = r6->getState();
    if (r4 != 0) {
        if (r4 == 7) {
            ChoiceIdList_Add((u8 *)&choiceList, 0x17, 1);
        } else {
            ChoiceIdList_Add((u8 *)&choiceList, 0x14, 1);
        }
    }
    if (r6->getPresent() != 0xfff1 && r4 == 3 || r4 == 6 || r4 == 1) {
        ChoiceIdList_Add((u8 *)&choiceList, 0x15, 2);
    }
    ChoiceIdList_Add((u8 *)&choiceList, 2, 3);
    hideCursor();
    nameBalloon.hide(1);
    openPopup();
}

void PocketLettersMenu::moveCursorInGrid(u32 pad, u32 x) {
    s32 col = cursorSlot - 0xb;
    s32 row = col >> 1;
    if (MenuKeys_HasLeft(pad)) {
        if ((col & 1) > 0) {
            cursorSlot = cursorSlot - 1;
        }
    } else if (MenuKeys_HasRight(pad)) {
        if ((col & 1) < 1) {
            cursorSlot = cursorSlot + 1;
        }
    }
    if (isLetterSlot(cursorSlot)) {
        if (!testFlags(0x30)) {
            if (MenuKeys_HasUp(pad)) {
                if (row > 0) {
                    cursorSlot = cursorSlot - 2;
                }
            } else if (MenuKeys_HasDown(pad)) {
                if (row < 4) {
                    cursorSlot = cursorSlot + 2;
                }
            }
        }
    }
}

BOOL PocketLettersMenu::moveCursorByPad(u32 pad, u32 x) {
    u8 old = cursorSlot;
    clearFlags(0x30);
    if (pad == 0) {
        return FALSE;
    }
    if (isLetterSlot(cursorSlot)) {
        moveCursorInGrid(pad, x);
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void PocketLettersMenu::startReadLetter() {
    setTransitionState(3);
    setPhase(1);
    setFlags(0x100);
}

void PocketLettersMenu::closeLetterView() {
    setMainState(0x18);
    letterCloseButton.setState(2);
}

BOOL PocketLettersMenu::testFlags(u32 mask) {
    if (stateFlags & mask) {
        return TRUE;
    }
    return FALSE;
}

void PocketLettersMenu::setFlags(u32 mask) { stateFlags = stateFlags | mask; }

void PocketLettersMenu::clearFlags(u32 mask) { stateFlags = stateFlags & ~mask; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov103_02294c40) {
    HOST_OVERLAY_VAR(sPocketLettersMenuProfile),
    HOST_OVERLAY_VARS_END
};

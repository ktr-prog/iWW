#include "types.h"
#include "host_labels.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/NumberPad.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "player/PlayerData.h"
#include "player/PlayerInventory.h"
#include "room/HouseData.h"
#include "ui/HandCursor.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02097110.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov130/unk_ov130_02292360.h"
#include "proto/ov131/unk_022936c0.h"

extern "C" {
extern u16 gPad[];
}
#define gSaveHouse HOST_LABEL(HouseData *, gSaveHouse)

static inline BOOL func_ov131_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

class AmountEntryMenu;
typedef void (AmountEntryMenu::*Unk_ov131_022942f0_Fn)();

class AmountEntryMenu : public MenuProc {
public:
    AmountEntryMenu() : cursor(), bottomButtons(), numberPad() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void setFlags(u32 mask);
    BOOL testFlags(u32 mask);
    void commitAmount();
    void setupAmounts();
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void startCursorMove(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void cancel();
    BOOL confirm();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void stateExit();
    void stateButtonRepeat();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateButtons();
    void stateTouchRepeat();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initPad();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x91 */ u8 unk_91[3];
    /* 0x94 */ MenuCursorBuf0 cursor;
    /* 0xf8 */ MenuBottomButtons bottomButtons;
    /* 0x25c */ NumberPad numberPad;
    /* 0x1410 */ u16 flags;
    /* 0x1412 */ u8 returnState;
};

extern "C" AmountEntryMenu *AmountEntryMenu_Create() { return new AmountEntryMenu(); }


extern "C" ProcProfile sAmountEntryMenuProfile = {(void *(*)())AmountEntryMenu_Create, 0xb2, 0xb6};

BOOL AmountEntryMenu::onCreate() {
    initPad();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL AmountEntryMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL AmountEntryMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)&cursor)->drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    bottomButtons.drawAt(getSlideOffsetY());
    Shared_NumberPad_Draw(&numberPad, getSlideOffsetY());
    return TRUE;
}

BOOL AmountEntryMenu::execTransition() {
    static Unk_ov131_022942f0_Fn tbl[4] = {
        &AmountEntryMenu::stateOpen,
        &AmountEntryMenu::stateOpening,
        &AmountEntryMenu::stateClose,
        &AmountEntryMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void AmountEntryMenu::runMainState() {
    static Unk_ov131_022942f0_Fn tbl[8] = {
        &AmountEntryMenu::updateTouch,
        &AmountEntryMenu::stateTouchRepeat,
        &AmountEntryMenu::updateButtons,
        &AmountEntryMenu::updateCursorMove,
        &AmountEntryMenu::updateCursorPress,
        &AmountEntryMenu::updateCursorRelease,
        &AmountEntryMenu::stateButtonRepeat,
        &AmountEntryMenu::stateExit};
    (this->*tbl[mainState])();
}

BOOL AmountEntryMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL AmountEntryMenu::execPhase3() { return TRUE; }

BOOL AmountEntryMenu::execPhase4() { return TRUE; }

BOOL AmountEntryMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void AmountEntryMenu::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    beginSubSlideIn(10, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    setFlags(1);
    bottomButtons.setLayoutConfirmAnd06(0x65);
    setTransitionState(1);
}

void AmountEntryMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void AmountEntryMenu::stateClose() {
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(10, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(3);
}

void AmountEntryMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void AmountEntryMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
}

void AmountEntryMenu::initPad() {
    numberPad.init((u8)(MenuCtrl_GetMode() - 0x34), 6, 4);
    setupAmounts();
    flags = 0;
}

void AmountEntryMenu::releaseResources() {
    bottomButtons.freeTexts();
    numberPad.shutdown();
}

void AmountEntryMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void AmountEntryMenu::postInputUpdate() { postStateUpdate(); }

void AmountEntryMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    numberPad.update();
}

void AmountEntryMenu::postStateUpdate() {
    numberPad.flushScreens();
    if (Shared_NumberPad_GetValue(&numberPad) == 0) {
        ((MenuBottomButtonsBody *)&bottomButtons)->disableButton(6);
    } else {
        ((MenuBottomButtonsBody *)&bottomButtons)->enableButton(6);
    }
}

void AmountEntryMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void AmountEntryMenu::loadBgGfx() { numberPad.loadBg(); }

void AmountEntryMenu::loadObjGfx() {
    numberPad.loadObj();
    MenuButtons_LoadTextColors();
}

void AmountEntryMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (func_ov131_Both()) {
            if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6)) {
                confirm();
            } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(7)) {
                cancel();
            } else {
                if (Shared_NumberPad_HitTestKey(&numberPad, gTouchCurX, gTouchCurY) != 0xd) {
                    NumberPad_PressKey(&numberPad);
                    setMainState(1);
                }
            }
        }
    }
}

void AmountEntryMenu::stateTouchRepeat() {
    if (gTouchHeld == 0) {
        NumberPad_StopKeyRepeat(&numberPad);
        setMainState(0);
    } else {
        NumberPad_TickKeyRepeat(&numberPad);
    }
}

void AmountEntryMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else if (NumberPad_MoveCursor(&numberPad, takeRepeatedKeys())) {
        moveCursorToTarget();
    } else {
        u32 k = gPad[1];
        if (k & 8) {
            if (confirm()) {
                hideCursor();
            }
        } else if (k & 1) {
            pressCursor();
        } else if (k & 2) {
            if (!NumberPad_ClearValue(&numberPad)) {
                hideCursor();
                cancel();
            }
        }
    }
}

void AmountEntryMenu::updateCursorMove() {
    if (!((MenuCursorBase *)&cursor)->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void AmountEntryMenu::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (Shared_NumberPad_PressCursorKey(&numberPad)) {
            setMainState(6);
        } else if (NumberPad_IsCursorOnOk(&numberPad)) {
            if (!confirm()) {
                setMainState(2);
                releaseCursor();
            }
        } else {
            cancel();
        }
    }
}

void AmountEntryMenu::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void AmountEntryMenu::stateButtonRepeat() {
    if ((gPad[0] & 1) == 0) {
        NumberPad_StopKeyRepeat(&numberPad);
        setMainState(2);
        releaseCursor();
    } else {
        NumberPad_TickKeyRepeat(&numberPad);
    }
}

void AmountEntryMenu::stateExit() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (((HandCursor *)(&cursor))->getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            ((MenuCursorBase *)&cursor)->warpTo(a + b, a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void AmountEntryMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void AmountEntryMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(2);
}

void AmountEntryMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

BOOL AmountEntryMenu::confirm() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->isButtonDisabled(6)) {
        return FALSE;
    }
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setTransitionState(2);
    setMainState(7);
    MenuCtrl_SetResult(1);
    MenuCtrl_SetAmount(Shared_NumberPad_GetValue(&numberPad));
    commitAmount();
    return TRUE;
}

void AmountEntryMenu::cancel() {
    Snd_PlaySe(0x2a);
    MenuCtrl_SetResult(0);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(7);
    setTransitionState(2);
    setMainState(7);
}

void AmountEntryMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
    if (Shared_NumberPad_IsCursorOnButton(&numberPad)) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 AmountEntryMenu::getCursorTargetX() { return Shared_NumberPad_GetCursorX(&numberPad); }

s32 AmountEntryMenu::getCursorTargetY() { return NumberPad_GetCursorY(&numberPad); }

void AmountEntryMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void AmountEntryMenu::moveCursorToTarget() {
    if (Shared_NumberPad_IsCursorOnButton(&numberPad)) {
        ((MenuCursor *)&cursor)->switchToAnim07();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    startCursorMove(a, b);
}

void AmountEntryMenu::startCursorMove(s32 a, s32 b) {
    ((MenuCursorBase *)&cursor)->moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(3);
}

void AmountEntryMenu::refreshCursor() {
    ((MenuCursorBase *)&cursor)->setPoseIdle();
    cursor.update();
}

void AmountEntryMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(4);
}

void AmountEntryMenu::releaseCursor() {
    ((MenuCursorBase *)&cursor)->setPoseRelease();
    returnState = mainState;
    setMainState(5);
}

void AmountEntryMenu::setupAmounts() {
    s32 hi;
    s32 lo;
    s32 m = MenuCtrl_GetMode();
    PlayerData *p = PlayerData_GetCurrent();
    PlayerBank *q = p->getBankAccount();
    switch (m) {
    case 0x38:
        hi = 0x98967f;
        break;
    case 0x3a:
        hi = 99;
        break;
    case 0x36:
        hi = PlayerBank_GetBalance(q);
        break;
    default:
        hi = ((PlayerInventory *)p->getInventory())->getTotalBells(1);
        break;
    }
    lo = 0;
    switch (m) {
    case 0x34:
        lo = gSaveHouse.getDebt();
        break;
    case 0x35:
        lo = PlayerBank_GetBalance(q);
        break;
    case 0x36:
        lo = ((PlayerInventory *)p->getInventory())->getTotalBells(1);
        break;
    }
    volatile s32 mx = hi;
    switch (m) {
    case 0x34:
        if (lo < hi) {
            mx = lo;
        }
        break;
    case 0x35: {
        s32 t = 0x3b9ac9ff - lo;
        if (t < hi) {
            mx = t;
        }
        break;
    }
    case 0x36: {
        s32 t = PlayerInventory_GetBellsRoom((u8 *)p->getInventory(), 1, 0);
        if (t < hi) {
            mx = t;
        }
        break;
    }
    }
    Shared_NumberPad_SetAmounts(&numberPad, mx, hi, lo);
}

void AmountEntryMenu::commitAmount() {
    s32 a = Shared_NumberPad_GetValue(&numberPad);
    s32 b = NumberPad_GetTopAmount(&numberPad);
    s32 c = NumberPad_GetBottomAmount(&numberPad);
    PlayerData *p = PlayerData_GetCurrent();
    PlayerBank *q = p->getBankAccount();
    s32 m = MenuCtrl_GetMode();
    switch (m) {
    case 0x36:
        PlayerBank_SetBalance(q, b - a);
        break;
    case 0x37:
    default:
        PlayerInventory_AddBells((u8 *)p->getInventory(), -a, 1);
        break;
    case 0x38:
    case 0x39:
    case 0x3a:
        break;
    }
    switch (m) {
    case 0x34:
        gSaveHouse.setDebt(c - a);
        break;
    case 0x35:
        PlayerBank_SetBalance(q, c + a);
        break;
    case 0x36:
        PlayerInventory_AddBells((u8 *)p->getInventory(), a, 1);
        break;
    }
}

BOOL AmountEntryMenu::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void AmountEntryMenu::setFlags(u32 mask) { flags = flags | mask; }


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_022936c0) {
    HOST_OVERLAY_VAR(sAmountEntryMenuProfile),
    HOST_OVERLAY_VARS_END
};

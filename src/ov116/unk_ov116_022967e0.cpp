#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "ui/UiWidget.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/LabelString.h"
#include "menu/MenuCursor.h"
#include "menu/CreatureBookPanel.h"
#include "menu/MenuTabBar.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov090/unk_ov090_022918e0.h"
#include "proto/ov114/unk_ov114_02294c40.h"
#include "proto/ov116/unk_ov116_022967e0.h"

extern "C" {
extern u16 gPad[];


}


class InsectBookTab;











typedef void (InsectBookTab::*Unk_ov116_02297378_Fn)();

class InsectBookTab : public MenuProc {
public:
    InsectBookTab() : cursor(), bookPanel(), textLabels() {}

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
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void hideCursor();
    void showCursor();
    void resetTextLabels();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void mainAct08();
    void mainAct07();
    void mainAct06();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateButtons();
    void mainAct01();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initInsectBook();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    BOOL requestTab(s32 v);
    BOOL handleTabSwitch();
    void runMainState();

    /* 0x0091 */ u8 unk_91[0x3];
    /* 0x0094 */ MenuCursorBuf0 cursor;
    /* 0x00f8 */ CreatureBookPanel bookPanel;
    /* 0x1394 */ LabelString textLabels[1];
    /* 0x13d4 */ s32 slideY;
    /* 0x13d8 */ u16 flags;
    /* 0x13da */ u8 labelCount;
    /* 0x13db */ u8 unk_13db;
    /* 0x13dc */ u8 returnState;
};

static inline BOOL Unk_ov116_02296ce8_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" InsectBookTab *InsectBookTab_Create() { return new InsectBookTab(); }

BOOL InsectBookTab::onCreate() {
    initInsectBook();
    setTransitionState(0);
    setPhase(1);
    return TRUE;
}

BOOL InsectBookTab::onDelete() {
    ((MenuTabBar *)ProcBase_GetParent(this))->onTabMenuClosed();
    releaseResources();
    return TRUE;
}

BOOL InsectBookTab::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    bookPanel.placeScrollKnob(slideY);
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    bookPanel.drawButtons(slideY);
    Shared_CreatureBook_DrawRows(&bookPanel, slideY);
    bookPanel.drawScrollKnob();
    return TRUE;
}

extern "C" ProcProfile sInsectBookTabProfile;

extern "C" ProcProfile sInsectBookTabProfile = {(void *(*)())InsectBookTab_Create, 0xa0, 0xa4};

BOOL InsectBookTab::execTransition() {
    static Unk_ov116_02297378_Fn tbl[4] = {
        &InsectBookTab::stateOpen,
        &InsectBookTab::stateOpening,
        &InsectBookTab::stateClose,
        &InsectBookTab::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void InsectBookTab::runMainState() {
    static Unk_ov116_02297378_Fn tbl[9] = {
        &InsectBookTab::updateTouch,
        &InsectBookTab::mainAct01,
        &InsectBookTab::updateButtons,
        &InsectBookTab::updateCursorMove,
        &InsectBookTab::updateCursorPress,
        &InsectBookTab::updateCursorRelease,
        &InsectBookTab::mainAct06,
        &InsectBookTab::mainAct07,
        &InsectBookTab::mainAct08};
    (this->*tbl[mainState])();
}

BOOL InsectBookTab::execMain() {
    if (handleTabSwitch()) {
        return TRUE;
    }
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL InsectBookTab::execPhase3() { return TRUE; }

BOOL InsectBookTab::execPhase4() { return TRUE; }

BOOL InsectBookTab::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

BOOL InsectBookTab::handleTabSwitch() {
    s32 r;
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        return requestTab(7);
    }
    if (mainState != 0 && mainState != 2) {
        return FALSE;
    }
    r = -1;
    if (MenuCtrl_IsTouch()) {
        r = MenuTabBar_HitTestTouch();
    } else {
        u32 m = gPad[1];
        if (m & 2) {
            r = 7;
        } else if (m & 0x800) {
            r = 0;
        } else if (m & 0x400) {
            r = 5;
        } else if (m & 4) {
            r = 4;
        }
    }
    return requestTab(r);
}

BOOL InsectBookTab::requestTab(s32 v) {
    void *h = ProcBase_GetParent(this);
    if (v != -1 && v != 3) {
        ((MenuTabBar *)h)->selectTab((u8)v);
        transitionState = 2;
        setPhase(1);
        return TRUE;
    }
    return FALSE;
}

void InsectBookTab::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    beginSubSlideIn(0xb, 0, 0, 0x30);
    Gfx2d_ShowLayer(3);
    Gfx2d_ShowLayer(6);
    setFlags(1);
    updateLayerSlide();
    setTransitionState(1);
}

void InsectBookTab::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void InsectBookTab::stateClose() {
    hideCursor();
    beginSubSlideOut(0xb, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(3);
    CreatureBook_StopPictureFade(&bookPanel);
}

void InsectBookTab::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(3);
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void InsectBookTab::updateLayerSlide() {
    applySlideOffset(3, 0, 0);
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
    slideY = getSlideOffsetY();
}

void InsectBookTab::initInsectBook() {
    flags = 0;
    bookPanel.init(3, 6, 4, 1);
}

void InsectBookTab::releaseResources() {
    bookPanel.cleanup();
    resetTextLabels();
}

void InsectBookTab::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void InsectBookTab::postInputUpdate() {
    postStateUpdate();
}

void InsectBookTab::preStateUpdate() {
    bookPanel.preUpdate();
    resetTextLabels();
}

void InsectBookTab::postStateUpdate() {
    bookPanel.postUpdate();
}

void InsectBookTab::setupBgLayers() {
    Gfx2d_SetLayerPriority(3, 1);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void InsectBookTab::loadBgGfx() {
    bookPanel.loadBgGraphics();
    CreatureBook_InitPictureView(&bookPanel);
}

void InsectBookTab::loadObjGfx() {
    bookPanel.loadObjGraphics();
    Shared_CreatureBook_RefreshRowIcons(&bookPanel);
}

void InsectBookTab::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov116_02296ce8_Both()) {
        u32 a = gTouchCurX;
        u32 b = gTouchCurY;
        if (bookPanel.hitDescPageButtons(a, b) == 0) {
            if (bookPanel.beginScrollTouch(a, b)) {
                setMainState(1);
            } else if (CreatureBook_TouchRow(&bookPanel, a, b) != 0) {
                return;
            }
        }
    }
}

void InsectBookTab::mainAct01() {
    if (gTouchHeld != 0) {
        CreatureBook_UpdateScrollTouch(&bookPanel, gTouchCurX);
    } else {
        Shared_CreatureBook_EndScrollTouch(&bookPanel);
        setMainState(0);
    }
}

void InsectBookTab::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        u32 k = takeRepeatedKeys();
        if (CreatureBook_MoveFocus(&bookPanel, k)) {
            moveCursorToTarget();
        } else {
            u32 m = gPad[1];
            if (m & 1) {
                pressCursor();
            } else if (m & 0x100) {
                requestTab(MenuTabBar_NextTab(3));
            } else if (m & 0x200) {
                requestTab(MenuTabBar_PrevTab(3));
            }
        }
    }
}

void InsectBookTab::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void InsectBookTab::updateCursorPress() {
    if (cursor.isAnimDone()) {
        s32 r = Shared_CreatureBook_GetFocusedTab(&bookPanel);
        if (r != -1) {
            if (requestTab(r) != 0) {
                return;
            }
            goto bea;
        } else {
            if (Shared_CreatureBook_ActivateFocus(&bookPanel) == 0) {
                goto bea;
            }
            setMainState(6);
            return;
        }
        return;
    bea:
        setMainState(2);
        releaseCursor();
    }
}

void InsectBookTab::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void InsectBookTab::mainAct06() {
    if (Shared_CreatureBook_WaitScrollHoldStart(&bookPanel)) {
        setMainState(7);
    }
    bookPanel.placeScrollKnob(slideY);
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
}

void InsectBookTab::mainAct07() {
    if (gPad[0] & 1) {
        CreatureBook_UpdateScrollHold(&bookPanel);
    } else {
        CreatureBook_ReleaseKnob(&bookPanel);
        setMainState(8);
    }
    bookPanel.placeScrollKnob(slideY);
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
}

void InsectBookTab::mainAct08() {
    if (CreatureBook_FinishScrollHold(&bookPanel)) {
        setMainState(2);
        releaseCursor();
    }
    bookPanel.placeScrollKnob(slideY);
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
}

void InsectBookTab::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void InsectBookTab::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(2);
}

void InsectBookTab::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void InsectBookTab::resetTextLabels() {
    labelCount = 0;
    textLabels[0].destroyLabel();
}

void InsectBookTab::showCursor() {
    CreatureBook_ClampFocusToView(&bookPanel);
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    s32 r = Shared_CreatureBook_GetFocusedTab(&bookPanel);
    if (r != -1 || Shared_CreatureBook_IsFocusOnPageArrow(&bookPanel) != 0) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(0xd);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 InsectBookTab::getCursorTargetX() {
    return Shared_CreatureBook_GetFocusX(&bookPanel);
}

s32 InsectBookTab::getCursorTargetY() {
    return Shared_CreatureBook_GetFocusY(&bookPanel);
}

void InsectBookTab::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void InsectBookTab::moveCursorToTarget() {
    s32 r = Shared_CreatureBook_GetFocusedTab(&bookPanel);
    if (r != -1 || Shared_CreatureBook_IsFocusOnPageArrow(&bookPanel) != 0) {
        ((MenuCursor *)&cursor)->switchToAnim0D();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    moveCursorTo(a, b);
}

void InsectBookTab::moveCursorTo(s32 a, s32 b) {
    cursor.moveToEase(a, b, 3, 1);
    returnState = mainState;
    setMainState(3);
}

void InsectBookTab::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void InsectBookTab::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(4);
}

void InsectBookTab::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(5);
}

BOOL InsectBookTab::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void InsectBookTab::setFlags(u32 mask) {
    flags |= mask;
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov116_022967e0) {
    HOST_OVERLAY_VAR(sInsectBookTabProfile),
    HOST_OVERLAY_VARS_END
};

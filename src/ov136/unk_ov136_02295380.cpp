#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/DateTimePicker.h"
#include "sys/ClockDateTime.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "ui/HandCursor.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov134/unk_ov134_02291f60.h"
#include "proto/ov136/unk_ov136_02295380.h"

extern "C" {
extern const u8 sTimeSelectCursorRightTable[3];
extern const u8 sTimeSelectCursorLeftTable[3];
extern const u8 sTimeSelectCursorDownTable[3];
extern const u8 sTimeSelectCursorUpTable[3];
extern const s32 sTimeSelectCursorXTable[3];
extern const s32 sTimeSelectCursorYTable[3];
extern u16 gPad[];

}

class TimeSelectMenu;
typedef void (TimeSelectMenu::*Unk_ov136_022963b0_Fn)();

class TimeSelectMenu : public MenuProc {
public:
    TimeSelectMenu() : cursor(), bottomButtons(), picker() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void clearFlags(u32 m);
    void setFlags(u32 m);
    BOOL testFlags(u32 m);
    BOOL moveCursorByPad(u32 pad);
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void startCursorMove(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void enterListInputMode();
    void enterListButtonMode();
    void enterListTouchMode();
    void cancelList();
    void decideList();
    void openFieldList(u32 a);
    void confirm();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void stateListClosing();
    void stateListOpening();
    void stateExit();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void stateListKnobRelease();
    void stateListKnobHold();
    void stateListButtons();
    void updateButtons();
    void stateListTrackDrag();
    void stateListKnobDrag();
    void stateListTouch();
    void stateHandAnim();
    void stateHandDrag();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initPicker();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ MenuCursorBuf0 cursor;
    /* 0x0f8 */ MenuBottomButtons bottomButtons;
    /* 0x25c */ DateTimePicker picker;
    /* 0x2820 */ u16 flags;
    /* 0x2822 */ u8 returnState;
    /* 0x2823 */ u8 cursorSlot;
};

extern "C" ProcProfile sTimeSelectMenuProfile;

static inline BOOL Unk_ov136_02295c0c_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL Unk_ov136_02295d1c_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" TimeSelectMenu *TimeSelectMenu_Create() { return new TimeSelectMenu(); }

BOOL TimeSelectMenu::onCreate() {
    initPicker();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL TimeSelectMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL TimeSelectMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)&cursor)->drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    s32 r = getSlideOffsetY();
    DateTimePicker_Draw(&picker, 0, r);
    bottomButtons.drawAt(getSlideOffsetY());
    return TRUE;
}
extern "C" ProcProfile sTimeSelectMenuProfile;
extern "C" const s32 sTimeSelectCursorXTable[3];
extern "C" const s32 sTimeSelectCursorYTable[3];
extern "C" const u8 sTimeSelectCursorLeftTable[3];
extern "C" const u8 sTimeSelectCursorRightTable[3];
extern "C" const u8 sTimeSelectCursorUpTable[3];
extern "C" const u8 sTimeSelectCursorDownTable[3];

extern "C" ProcProfile sTimeSelectMenuProfile = {(void *(*)())TimeSelectMenu_Create, 0xaf, 0xb3};

BOOL TimeSelectMenu::execTransition() {
    static Unk_ov136_022963b0_Fn tbl[4] = {
        &TimeSelectMenu::stateOpen, &TimeSelectMenu::stateOpening,
        &TimeSelectMenu::stateClose, &TimeSelectMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void TimeSelectMenu::runMainState() {
    static Unk_ov136_022963b0_Fn tbl[16] = {
        &TimeSelectMenu::updateTouch, &TimeSelectMenu::stateHandDrag,
        &TimeSelectMenu::stateHandAnim, &TimeSelectMenu::stateListTouch,
        &TimeSelectMenu::stateListKnobDrag, &TimeSelectMenu::stateListTrackDrag,
        &TimeSelectMenu::updateButtons, &TimeSelectMenu::stateListButtons,
        &TimeSelectMenu::stateListKnobHold, &TimeSelectMenu::stateListKnobRelease,
        &TimeSelectMenu::updateCursorMove, &TimeSelectMenu::updateCursorPress,
        &TimeSelectMenu::updateCursorRelease, &TimeSelectMenu::stateExit,
        &TimeSelectMenu::stateListOpening, &TimeSelectMenu::stateListClosing};
    (this->*tbl[mainState])();
}

BOOL TimeSelectMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL TimeSelectMenu::execPhase3() { return TRUE; }

BOOL TimeSelectMenu::execPhase4() { return TRUE; }

BOOL TimeSelectMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void TimeSelectMenu::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    beginSubSlideIn(0xa, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    setFlags(1);
    bottomButtons.setLayoutSingle05(0x21);
    setTransitionState(1);
}

void TimeSelectMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void TimeSelectMenu::stateClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(0xa, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(3);
}

void TimeSelectMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void TimeSelectMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
}

void TimeSelectMenu::initPicker() {
    DateTimePicker_Init(&picker, 1, 6, 4, 3);
    cursorSlot = 0;
    flags = 0;
}

void TimeSelectMenu::releaseResources() {
    DateTimePicker_Shutdown(&picker);
    bottomButtons.freeTexts();
}

void TimeSelectMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void TimeSelectMenu::postInputUpdate() { postStateUpdate(); }

void TimeSelectMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    Shared_DateTimePicker_BeginFrame(&picker);
}

void TimeSelectMenu::postStateUpdate() { DateTimePicker_EndFrame(&picker); }

void TimeSelectMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 1);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void TimeSelectMenu::loadBgGfx() {
    DateTimePicker_LoadBgGraphics(&picker);
    DateTimePicker_DrawTitleAndFields(&picker, 0x8b);
}

void TimeSelectMenu::loadObjGfx() {
    DateTimePicker_LoadObjGraphics(&picker);
    MenuButtons_LoadTextColors();
}

void TimeSelectMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov136_02295d1c_Both()) {
        if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6)) {
            confirm();
        } else {
            u32 a = gTouchCurX;
            u32 b = gTouchCurY;
            if (Shared_DateTimePicker_GrabHand(&picker, a, b)) {
                setMainState(1);
            }
            s32 r = DateTimePicker_HitTestTimeField(&picker, a, b);
            if (r != 6) {
                openFieldList(r);
            }
        }
    }
}

void TimeSelectMenu::stateHandDrag() {
    if (gTouchHeld == 0) {
        if (Shared_DateTimePicker_EndHandDrag(&picker)) {
            setMainState(2);
        } else {
            setMainState(0);
        }
    } else {
        DateTimePicker_UpdateHandDrag(&picker, gTouchCurX, gTouchCurY);
    }
}

void TimeSelectMenu::stateHandAnim() {
    if (Shared_DateTimePicker_UpdateHandAnim(&picker)) {
        setMainState(0);
    }
}

void TimeSelectMenu::stateListTouch() {
    if (checkSwitchToButtons(1)) {
        enterListButtonMode();
        return;
    }
    if (Unk_ov136_02295c0c_Both()) {
        s32 r = Shared_DateTimePicker_HitTestList(&picker, gTouchCurX, gTouchCurY);
        switch (r) {
        case 0:
            decideList();
            break;
        case 1:
            cancelList();
            break;
        case 3:
            setMainState(4);
            break;
        case 2:
            setMainState(5);
            break;
        }
    }
}

void TimeSelectMenu::stateListKnobDrag() {
    if (gTouchHeld) {
        picker.dragKnob(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(3);
    }
}

void TimeSelectMenu::stateListTrackDrag() {
    if (gTouchHeld) {
        picker.dragKnobToward(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(3);
    }
}

void TimeSelectMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        return;
    }
    s32 x = takeRepeatedKeys();
    if (moveCursorByPad(x)) {
        moveCursorToTarget();
        return;
    }
    u32 v = gPad[1];
    if (v & 1) {
        pressCursor();
    } else if (v & 8) {
        hideCursor();
        confirm();
    }
}

void TimeSelectMenu::stateListButtons() {
    if (checkSwitchToTouch()) {
        enterListTouchMode();
        return;
    }
    s32 r = picker.navigateList(takeRepeatedKeys());
    switch (r) {
    case 2:
        setFlags(4);
        goto rest;
    case 3: {
        s32 b = getCursorTargetX();
        s32 c = getCursorTargetY();
        ((MenuCursorBase *)&cursor)->warpTo(b, c);
        return;
    }
    default:
    rest:
        moveCursorToTarget();
        return;
    case 0: {
        u32 v = gPad[1];
        if (v & 1) {
            pressCursor();
        } else if (v & 2) {
            cancelList();
        }
        return;
    }
    }
}

void TimeSelectMenu::stateListKnobHold() {
    if (gPad[0] & 1) {
        picker.moveKnobByPad();
        s32 b = getCursorTargetX();
        s32 c = getCursorTargetY();
        ((MenuCursorBase *)&cursor)->warpTo(b, c);
    } else {
        picker.releaseKnob();
        setMainState(9);
    }
}

void TimeSelectMenu::stateListKnobRelease() {
    if (picker.finishKnobRelease()) {
        setMainState(7);
        releaseCursor();
    }
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(b, c);
}

void TimeSelectMenu::updateCursorMove() {
    if (!((MenuCursorBase *)&cursor)->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void TimeSelectMenu::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (testFlags(2)) {
            if (picker.grabKnobByCursor()) {
                setMainState(8);
            } else if (picker.pickListCursorRow()) {
                decideList();
            } else {
                setMainState(7);
                releaseCursor();
            }
        } else {
            u32 v = cursorSlot;
            if (v == 2) {
                confirm();
            } else {
                openFieldList(v + 3);
            }
        }
    }
}

void TimeSelectMenu::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void TimeSelectMenu::stateExit() {
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

void TimeSelectMenu::stateListOpening() {
    if (Shared_DateTimePicker_UpdateListOpen(&picker)) {
        enterListInputMode();
    }
}

void TimeSelectMenu::stateListClosing() {
    if (Shared_DateTimePicker_UpdateListClose(&picker)) {
        s32 r = DateTimePicker_GetCursorField(&picker);
        if (r == 6) {
            cursorSlot = 2;
        } else {
            cursorSlot = r - 3;
        }
        resumeInput();
    }
}

void TimeSelectMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void TimeSelectMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(6);
}

void TimeSelectMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void TimeSelectMenu::confirm() {
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setTransitionState(2);
    setMainState(0xd);
    ClockDateTimeWords v;
    v.words[0] = 0;
    v.words[1] = 0;
    DateTimePicker_GetDateTime(&picker, &v.dt);
    MenuCtrl_SetDateTime(&v);
    MenuCtrl_SetResult(1);
}

void TimeSelectMenu::openFieldList(u32 a) {
    hideCursor();
    DateTimePicker_OpenList(&picker, a);
    setMainState(0xe);
}

void TimeSelectMenu::decideList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_DecideList(&picker);
    setMainState(0xf);
}

void TimeSelectMenu::cancelList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_CancelList(&picker);
    setMainState(0xf);
}

void TimeSelectMenu::enterListTouchMode() {
    hideCursor();
    setMainState(3);
}

void TimeSelectMenu::enterListButtonMode() {
    s32 t = picker.getListCursorY();
    picker.setListCursorFromY(t);
    setFlags(2);
    showCursor();
    restartKeyRepeat();
    setMainState(7);
}

void TimeSelectMenu::enterListInputMode() {
    if (MenuCtrl_IsTouch()) {
        enterListTouchMode();
    } else {
        enterListButtonMode();
    }
}

void TimeSelectMenu::showCursor() {
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(b, c);
    if (testFlags(2) != 0 || cursorSlot != 2) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    }
    refreshCursor();
}

s32 TimeSelectMenu::getCursorTargetX() {
    if (testFlags(2)) {
        return picker.getListCursorX();
    }
    u32 c = cursorSlot;
    if (c == 2) {
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(6);
    }
    return sTimeSelectCursorXTable[c];
}

s32 TimeSelectMenu::getCursorTargetY() {
    if (testFlags(2)) {
        return picker.getListCursorY();
    }
    u32 c = cursorSlot;
    if (c == 2) {
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(6);
    }
    return sTimeSelectCursorYTable[c];
}

void TimeSelectMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void TimeSelectMenu::moveCursorToTarget() {
    if (testFlags(2) != 0 || cursorSlot != 2) {
        ((MenuCursor *)&cursor)->switchToAnim01();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim07();
    }
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    startCursorMove(b, c);
}

void TimeSelectMenu::startCursorMove(s32 a, s32 b) {
    if (testFlags(4)) {
        ((MenuCursorBase *)&cursor)->moveToEase(a, b, 2, 1);
    } else {
        ((MenuCursorBase *)&cursor)->moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(0xa);
    clearFlags(4);
}

void TimeSelectMenu::refreshCursor() {
    ((MenuCursorBase *)&cursor)->setPoseIdle();
    cursor.update();
}

void TimeSelectMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(0xb);
}

void TimeSelectMenu::releaseCursor() {
    ((MenuCursorBase *)&cursor)->setPoseRelease();
    returnState = mainState;
    setMainState(0xc);
}

BOOL TimeSelectMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (MenuKeys_HasLeft(pad)) {
        cursorSlot = sTimeSelectCursorLeftTable[cursorSlot];
    } else if (MenuKeys_HasRight(pad)) {
        cursorSlot = sTimeSelectCursorRightTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    if (MenuKeys_HasUp(pad)) {
        cursorSlot = sTimeSelectCursorUpTable[cursorSlot];
    } else if (MenuKeys_HasDown(pad)) {
        cursorSlot = sTimeSelectCursorDownTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL TimeSelectMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void TimeSelectMenu::setFlags(u32 m) { flags = flags | m; }

void TimeSelectMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" const s32 sTimeSelectCursorXTable[3] = {0x6e, 0xae, 0};

extern "C" const s32 sTimeSelectCursorYTable[3] = {0x88, 0x88, 0};

extern "C" const u8 sTimeSelectCursorLeftTable[3] = {0, 0, 2};

extern "C" const u8 sTimeSelectCursorRightTable[3] = {1, 1, 2};

extern "C" const u8 sTimeSelectCursorUpTable[3] = {0, 1, 1};

extern "C" const u8 sTimeSelectCursorDownTable[3] = {2, 2, 2};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov136_02295380) {
    HOST_OVERLAY_VAR(sTimeSelectMenuProfile),
    HOST_OVERLAY_VARS_END
};

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
#include "proto/ov138/unk_ov138_02295380.h"

extern "C" {
extern const u8 sDateSelectCursorLeftTable[5];
extern const u8 sDateSelectCursorRightTable[5];
extern const u8 sDateSelectCursorDownTable[5];
extern const u8 sDateSelectCursorUpTable[5];
extern const s32 sDateSelectCursorXTable[5];
extern const s32 sDateSelectCursorYTable[5];
extern u16 gPad[];

}

class DateSelectMenu;
typedef void (DateSelectMenu::*Unk_ov138_02296380_Fn)();

static inline BOOL Unk_ov138_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

class DateSelectMenu : public MenuProc {
public:
    DateSelectMenu() : cursor(), bottomButtons(), picker() {}

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
    void cancel();
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

    /* 0x091 */ u8 pad_91;
    /* 0x092 */ u16 flags;
    /* 0x094 */ u8 returnState;
    /* 0x095 */ u8 cursorSlot;
    /* 0x096 */ u8 unk_96[2];
    /* 0x098 */ MenuCursorBuf0 cursor;
    /* 0x0fc */ MenuBottomButtons bottomButtons;
    /* 0x260 */ DateTimePicker picker;
};

extern "C" DateSelectMenu *DateSelectMenu_Create() { return new DateSelectMenu(); }

BOOL DateSelectMenu::onCreate() {
    initPicker();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL DateSelectMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL DateSelectMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)&cursor)->drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    s32 r = getSlideOffsetY();
    DateTimePicker_Draw(&picker, 0, r);
    s32 r2 = getSlideOffsetY();
    bottomButtons.drawAt(r2);
    return TRUE;
}
extern "C" const s32 sDateSelectCursorXTable[5];
extern "C" const u8 sDateSelectCursorDownTable[5];
extern "C" const u8 sDateSelectCursorUpTable[5];
extern "C" const u8 sDateSelectCursorLeftTable[5];
extern "C" const u8 sDateSelectCursorRightTable[5];
extern "C" const s32 sDateSelectCursorYTable[5];
extern "C" ProcProfile sDateSelectMenuProfile;

extern "C" const s32 sDateSelectCursorXTable[5] = {0xd6, 0x68, 0xa6, 0, 0};

BOOL DateSelectMenu::execTransition() {
    static Unk_ov138_02296380_Fn tbl[4] = {
        &DateSelectMenu::stateOpen,
        &DateSelectMenu::stateOpening,
        &DateSelectMenu::stateClose,
        &DateSelectMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void DateSelectMenu::runMainState() {
    static Unk_ov138_02296380_Fn tbl[14] = {
        &DateSelectMenu::updateTouch,
        &DateSelectMenu::stateListTouch,
        &DateSelectMenu::stateListKnobDrag,
        &DateSelectMenu::stateListTrackDrag,
        &DateSelectMenu::updateButtons,
        &DateSelectMenu::stateListButtons,
        &DateSelectMenu::stateListKnobHold,
        &DateSelectMenu::stateListKnobRelease,
        &DateSelectMenu::updateCursorMove,
        &DateSelectMenu::updateCursorPress,
        &DateSelectMenu::updateCursorRelease,
        &DateSelectMenu::stateExit,
        &DateSelectMenu::stateListOpening,
        &DateSelectMenu::stateListClosing};
    (this->*tbl[mainState])();
}

BOOL DateSelectMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL DateSelectMenu::execPhase3() { return TRUE; }

BOOL DateSelectMenu::execPhase4() { return TRUE; }

BOOL DateSelectMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void DateSelectMenu::stateOpen() {
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

void DateSelectMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void DateSelectMenu::stateClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(10, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(3);
}

void DateSelectMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void DateSelectMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
}

void DateSelectMenu::initPicker() {
    DateTimePicker_Init(&picker, 3, 6, 4, 3);
    DateTimePicker_EnableMinLimit(&picker);
    cursorSlot = 0;
    flags = 0;
}

void DateSelectMenu::releaseResources() {
    DateTimePicker_Shutdown(&picker);
    bottomButtons.freeTexts();
}

void DateSelectMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void DateSelectMenu::postInputUpdate() {
    postStateUpdate();
}

void DateSelectMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    Shared_DateTimePicker_BeginFrame(&picker);
}

void DateSelectMenu::postStateUpdate() {
    DateTimePicker_EndFrame(&picker);
}

void DateSelectMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 1);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void DateSelectMenu::loadBgGfx() {
    DateTimePicker_LoadBgGraphics(&picker);
    DateTimePicker_DrawTitleAndFields(&picker, 0x6c);
}

void DateSelectMenu::loadObjGfx() {
    DateTimePicker_LoadObjGraphics(&picker);
    MenuButtons_LoadTextColors();
}

void DateSelectMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov138_Both()) {
            if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6)) {
                confirm();
            } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(7)) {
                cancel();
            } else {
                s32 r = DateTimePicker_HitTestDateField(&picker, gTouchCurX, gTouchCurY);
                if (r != 6) {
                    openFieldList(r);
                }
            }
        }
    }
}

void DateSelectMenu::stateListTouch() {
    if (checkSwitchToButtons(1)) {
        enterListButtonMode();
        return;
    }
    BOOL ok;
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        ok = TRUE;
    } else {
        ok = FALSE;
    }
    if (ok) {
        switch (Shared_DateTimePicker_HitTestList(&picker, gTouchCurX, gTouchCurY)) {
        case 0:
            decideList();
            break;
        case 1:
            cancelList();
            break;
        case 3:
            setMainState(2);
            break;
        case 2:
            setMainState(3);
            break;
        }
    }
}

void DateSelectMenu::stateListKnobDrag() {
    if (gTouchHeld) {
        picker.dragKnob(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(1);
    }
}

void DateSelectMenu::stateListTrackDrag() {
    if (gTouchHeld) {
        picker.dragKnobToward(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(1);
    }
}

void DateSelectMenu::updateButtons() {
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
    } else if (v & 2) {
        hideCursor();
        cancel();
    }
}

void DateSelectMenu::stateListButtons() {
    if (checkSwitchToTouch()) {
        enterListTouchMode();
        return;
    }
    s32 r = picker.navigateList(takeRepeatedKeys());
    switch (r) {
    case 2:
        setFlags(4);
        goto dflt;
    case 3: {
        s32 b = getCursorTargetX();
        s32 c = getCursorTargetY();
        ((MenuCursorBase *)&cursor)->warpTo(b, c);
        return;
    }
    default:
    dflt:
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

void DateSelectMenu::stateListKnobHold() {
    if (gPad[0] & 1) {
        picker.moveKnobByPad();
        s32 b = getCursorTargetX();
        s32 c = getCursorTargetY();
        ((MenuCursorBase *)&cursor)->warpTo(b, c);
    } else {
        picker.releaseKnob();
        setMainState(7);
    }
}

void DateSelectMenu::stateListKnobRelease() {
    if (picker.finishKnobRelease()) {
        setMainState(5);
        releaseCursor();
    }
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(b, c);
}

void DateSelectMenu::updateCursorMove() {
    if (!((MenuCursorBase *)&cursor)->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void DateSelectMenu::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (testFlags(2)) {
            if (picker.grabKnobByCursor()) {
                setMainState(6);
            } else if (picker.pickListCursorRow()) {
                decideList();
            } else {
                setMainState(5);
                releaseCursor();
            }
        } else {
            u32 v = cursorSlot;
            if (v == 3) {
                confirm();
            } else if (v == 4) {
                cancel();
            } else {
                openFieldList(v);
            }
        }
    }
}

void DateSelectMenu::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void DateSelectMenu::stateExit() {
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

void DateSelectMenu::stateListOpening() {
    if (Shared_DateTimePicker_UpdateListOpen(&picker)) {
        enterListInputMode();
    }
}

void DateSelectMenu::stateListClosing() {
    if (Shared_DateTimePicker_UpdateListClose(&picker)) {
        s32 r = DateTimePicker_GetCursorField(&picker);
        if (r == 6) {
            cursorSlot = 3;
        } else {
            cursorSlot = r;
        }
        resumeInput();
    }
}

void DateSelectMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void DateSelectMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(4);
}

void DateSelectMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void DateSelectMenu::confirm() {
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setTransitionState(2);
    setMainState(0xb);
    ClockDateTimeWords v;
    v.words[0] = 0;
    v.words[1] = 0;
    DateTimePicker_GetDateTime(&picker, &v.dt);
    MenuCtrl_SetDateTime(&v);
    MenuCtrl_SetResult(1);
}

void DateSelectMenu::cancel() {
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(7);
    setTransitionState(2);
    setMainState(0xb);
    MenuCtrl_SetResult(0);
}

void DateSelectMenu::openFieldList(u32 a) {
    hideCursor();
    DateTimePicker_OpenList(&picker, a);
    setMainState(0xc);
}

void DateSelectMenu::decideList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_DecideList(&picker);
    setMainState(0xd);
}

void DateSelectMenu::cancelList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_CancelList(&picker);
    setMainState(0xd);
}

void DateSelectMenu::enterListTouchMode() {
    hideCursor();
    setMainState(1);
}

void DateSelectMenu::enterListButtonMode() {
    s32 t = picker.getListCursorY();
    picker.setListCursorFromY(t);
    setFlags(2);
    showCursor();
    restartKeyRepeat();
    setMainState(5);
}

void DateSelectMenu::enterListInputMode() {
    if (MenuCtrl_IsTouch()) {
        enterListTouchMode();
    } else {
        enterListButtonMode();
    }
}

void DateSelectMenu::showCursor() {
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    ((MenuCursorBase *)&cursor)->warpTo(b, c);
    if (testFlags(2) != 0) {
        goto els;
    }
    {
        u32 v = cursorSlot;
        if (v == 3) {
            goto hit;
        }
        if (v == 4) {
            goto hit;
        }
    }
els:
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    goto out;
hit:
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
out:
    refreshCursor();
}

s32 DateSelectMenu::getCursorTargetX() {
    if (testFlags(2)) {
        return picker.getListCursorX();
    }
    switch (cursorSlot) {
    case 3:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(6);
    case 4:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(7);
    default:
        return sDateSelectCursorXTable[cursorSlot];
    }
}

s32 DateSelectMenu::getCursorTargetY() {
    if (testFlags(2)) {
        return picker.getListCursorY();
    }
    switch (cursorSlot) {
    case 3:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(6);
    case 4:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(7);
    default:
        return sDateSelectCursorYTable[cursorSlot];
    }
}

void DateSelectMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void DateSelectMenu::moveCursorToTarget() {
    if (testFlags(2) != 0) {
        goto els;
    }
    {
        u32 c = cursorSlot;
        if (c == 3) {
            goto hit;
        }
        if (c == 4) {
            goto hit;
        }
    }
els:
    ((MenuCursor *)&cursor)->switchToAnim01();
    goto out;
hit:
    ((MenuCursor *)&cursor)->switchToAnim07();
out:
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    startCursorMove(b, c);
}

void DateSelectMenu::startCursorMove(s32 a, s32 b) {
    if (testFlags(4)) {
        ((MenuCursorBase *)&cursor)->moveToEase(a, b, 2, 1);
    } else {
        ((MenuCursorBase *)&cursor)->moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(8);
    clearFlags(4);
}

void DateSelectMenu::refreshCursor() {
    ((MenuCursorBase *)&cursor)->setPoseIdle();
    cursor.update();
}

void DateSelectMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(9);
}

void DateSelectMenu::releaseCursor() {
    ((MenuCursorBase *)&cursor)->setPoseRelease();
    returnState = mainState;
    setMainState(0xa);
}

BOOL DateSelectMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (MenuKeys_HasLeft(pad)) {
        cursorSlot = sDateSelectCursorLeftTable[cursorSlot];
    } else if (MenuKeys_HasRight(pad)) {
        cursorSlot = sDateSelectCursorRightTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    if (MenuKeys_HasUp(pad)) {
        cursorSlot = sDateSelectCursorUpTable[cursorSlot];
    } else if (MenuKeys_HasDown(pad)) {
        cursorSlot = sDateSelectCursorDownTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL DateSelectMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void DateSelectMenu::setFlags(u32 m) { flags = flags | m; }

void DateSelectMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" const u8 sDateSelectCursorDownTable[5] __attribute__((aligned(4))) = {3, 3, 3, 3, 4};

extern "C" const u8 sDateSelectCursorUpTable[5] __attribute__((aligned(4))) = {0, 1, 2, 0, 2};

extern "C" const u8 sDateSelectCursorLeftTable[5] __attribute__((aligned(4))) = {2, 1, 1, 4, 4};

extern "C" const u8 sDateSelectCursorRightTable[5] __attribute__((aligned(4))) = {0, 2, 0, 3, 3};

extern "C" const s32 sDateSelectCursorYTable[5] = {0x70, 0x70, 0x70, 0, 0};

extern "C" ProcProfile sDateSelectMenuProfile = {(void *(*)())DateSelectMenu_Create, 0xb1, 0xb5};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov138_02295380) {
    HOST_OVERLAY_VAR(sDateSelectMenuProfile),
    HOST_OVERLAY_VARS_END
};

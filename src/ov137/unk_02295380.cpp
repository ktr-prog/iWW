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
#include "player/PlayerData.h"
#include "ui/HandCursor.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov134/unk_ov134_02291f60.h"
#include "proto/ov137/unk_02295380.h"

extern "C" {
extern const u8 sBirthdayCursorRightTable[4];
extern const u8 sBirthdayCursorLeftTable[4];
extern const u8 sBirthdayCursorDownTable[4];
extern const u8 sBirthdayCursorUpTable[4];
extern const s32 sBirthdayCursorXTable[3];
extern const s32 sBirthdayCursorYTable[3];
extern u16 gPad[];

}

class BirthdayMenu;
typedef void (BirthdayMenu::*Unk_ov137_022962e0_Fn)();

class BirthdayMenu : public MenuProc {
public:
    BirthdayMenu() : cursor(), bottomButtons(), picker() {}

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
    BOOL moveCursorByPad(u32 a);
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

#define U94A ((MenuCursorBase *)&cursor)
#define U94B ((MenuCursor *)&cursor)

static inline BOOL Unk_ov137_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BirthdayMenu *BirthdayMenu_Create() { return new BirthdayMenu(); }

BOOL BirthdayMenu::onCreate() {
    initPicker();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL BirthdayMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL BirthdayMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        U94A->drawWrapped();
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

extern "C" const u8 sBirthdayCursorLeftTable[4];
extern "C" const s32 sBirthdayCursorXTable[3];
extern "C" const s32 sBirthdayCursorYTable[3];
extern "C" const u8 sBirthdayCursorUpTable[4];
extern "C" const u8 sBirthdayCursorDownTable[4];
extern "C" ProcProfile sBirthdayMenuProfile;
extern "C" const u8 sBirthdayCursorRightTable[4];
extern "C" const s32 sBirthdayCursorXTable[3];
extern "C" const u8 sBirthdayCursorRightTable[4];
extern "C" const u8 sBirthdayCursorLeftTable[4];
extern "C" const u8 sBirthdayCursorUpTable[4];
extern "C" const u8 sBirthdayCursorDownTable[4];
extern "C" const s32 sBirthdayCursorYTable[3];
extern "C" ProcProfile sBirthdayMenuProfile;

extern "C" const s32 sBirthdayCursorXTable[3] = {0x60, 0xac, 0};

BOOL BirthdayMenu::execTransition() {
    static Unk_ov137_022962e0_Fn tbl[4] = {
        &BirthdayMenu::stateOpen,
        &BirthdayMenu::stateOpening,
        &BirthdayMenu::stateClose,
        &BirthdayMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void BirthdayMenu::runMainState() {
    static Unk_ov137_022962e0_Fn tbl[14] = {
        &BirthdayMenu::updateTouch,
        &BirthdayMenu::stateListTouch,
        &BirthdayMenu::stateListKnobDrag,
        &BirthdayMenu::stateListTrackDrag,
        &BirthdayMenu::updateButtons,
        &BirthdayMenu::stateListButtons,
        &BirthdayMenu::stateListKnobHold,
        &BirthdayMenu::stateListKnobRelease,
        &BirthdayMenu::updateCursorMove,
        &BirthdayMenu::updateCursorPress,
        &BirthdayMenu::updateCursorRelease,
        &BirthdayMenu::stateExit,
        &BirthdayMenu::stateListOpening,
        &BirthdayMenu::stateListClosing};
    (this->*tbl[mainState])();
}

BOOL BirthdayMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL BirthdayMenu::execPhase3() { return TRUE; }

BOOL BirthdayMenu::execPhase4() { return TRUE; }

BOOL BirthdayMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void BirthdayMenu::stateOpen() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    beginSubSlideIn(10, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    setFlags(1);
    bottomButtons.setLayoutSingle05(0x21);
    setTransitionState(1);
}

void BirthdayMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void BirthdayMenu::stateClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(10, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(3);
}

void BirthdayMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void BirthdayMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
}

void BirthdayMenu::initPicker() {
    DateTimePicker_Init(&picker, 2, 6, 4, 3);
    cursorSlot = 0;
    flags = 0;
}

void BirthdayMenu::releaseResources() {
    DateTimePicker_Shutdown(&picker);
    bottomButtons.freeTexts();
}

void BirthdayMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void BirthdayMenu::postInputUpdate() {
    postStateUpdate();
}

void BirthdayMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    Shared_DateTimePicker_BeginFrame(&picker);
}

void BirthdayMenu::postStateUpdate() {
    DateTimePicker_EndFrame(&picker);
}

void BirthdayMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 1);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void BirthdayMenu::loadBgGfx() {
    DateTimePicker_LoadBgGraphics(&picker);
    DateTimePicker_DrawTitleAndFields(&picker, 0x6d);
}

void BirthdayMenu::loadObjGfx() {
    DateTimePicker_LoadObjGraphics(&picker);
    MenuButtons_LoadTextColors();
}

void BirthdayMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov137_Both()) {
            if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6)) {
                confirm();
            } else {
                s32 r = DateTimePicker_HitTestMonthDayField(&picker, gTouchCurX, gTouchCurY);
                if (r != 6) {
                    openFieldList(r);
                }
            }
        }
    }
}

void BirthdayMenu::stateListTouch() {
    if (checkSwitchToButtons(1)) {
        enterListButtonMode();
        return;
    }
    if (Unk_ov137_Both()) {
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

void BirthdayMenu::stateListKnobDrag() {
    if (gTouchHeld != 0) {
        picker.dragKnob(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(1);
    }
}

void BirthdayMenu::stateListTrackDrag() {
    if (gTouchHeld != 0) {
        picker.dragKnobToward(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(1);
    }
}

void BirthdayMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        s32 r = takeRepeatedKeys();
        if (moveCursorByPad(r)) {
            moveCursorToTarget();
        } else {
            u32 t = gPad[1];
            if (t & 1) {
                pressCursor();
            } else if (t & 8) {
                hideCursor();
                confirm();
            }
        }
    }
}

void BirthdayMenu::stateListButtons() {
    if (checkSwitchToTouch()) {
        enterListTouchMode();
    } else {
        s32 r = picker.navigateList(takeRepeatedKeys());
        switch (r) {
        case 2:
            setFlags(4);
            goto dflt;
        case 3: {
            s32 a = getCursorTargetX();
            s32 b = getCursorTargetY();
            U94A->warpTo(a, b);
            break;
        }
        default:
        dflt:
            moveCursorToTarget();
            break;
        case 0: {
            u32 t = gPad[1];
            if (t & 1) {
                pressCursor();
            } else if (t & 2) {
                cancelList();
            }
            break;
        }
        }
    }
}

void BirthdayMenu::stateListKnobHold() {
    if (gPad[0] & 1) {
        picker.moveKnobByPad();
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        U94A->warpTo(a, b);
    } else {
        picker.releaseKnob();
        setMainState(7);
    }
}

void BirthdayMenu::stateListKnobRelease() {
    if (picker.finishKnobRelease()) {
        setMainState(5);
        releaseCursor();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    U94A->warpTo(a, b);
}

void BirthdayMenu::updateCursorMove() {
    if (!U94A->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void BirthdayMenu::updateCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (testFlags(2)) {
            if (picker.grabKnobByCursor()) {
                setMainState(6);
            } else {
                picker.pickListCursorRow();
                decideList();
            }
        } else {
            u32 s = cursorSlot;
            if (s == 2) {
                confirm();
            } else {
                openFieldList(s + 1);
            }
        }
    }
}

void BirthdayMenu::updateCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void BirthdayMenu::stateExit() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (((HandCursor *)(&cursor))->getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            U94A->warpTo(a + b, a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void BirthdayMenu::stateListOpening() {
    if (Shared_DateTimePicker_UpdateListOpen(&picker)) {
        enterListInputMode();
    }
}

void BirthdayMenu::stateListClosing() {
    if (Shared_DateTimePicker_UpdateListClose(&picker)) {
        s32 r = DateTimePicker_GetCursorField(&picker);
        if (r == 6) {
            cursorSlot = 2;
        } else {
            cursorSlot = r - 1;
        }
        resumeInput();
    }
}

void BirthdayMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void BirthdayMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(4);
}

void BirthdayMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void BirthdayMenu::confirm() {
    ClockDateTimeWords w;
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setTransitionState(2);
    setMainState(0xb);
    PlayerData *obj = PlayerData_GetCurrent();
    w.words[0] = 0;
    w.words[1] = 0;
    DateTimePicker_GetDateTime(&picker, &w.dt);
    obj->setBirthday(w.dt.month, w.dt.day);
}

void BirthdayMenu::openFieldList(u32 a) {
    hideCursor();
    DateTimePicker_OpenList(&picker, a);
    setMainState(0xc);
}

void BirthdayMenu::decideList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_DecideList(&picker);
    setMainState(0xd);
}

void BirthdayMenu::cancelList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_CancelList(&picker);
    setMainState(0xd);
}

void BirthdayMenu::enterListTouchMode() {
    hideCursor();
    setMainState(1);
}

void BirthdayMenu::enterListButtonMode() {
    s32 t = picker.getListCursorY();
    picker.setListCursorFromY(t);
    setFlags(2);
    showCursor();
    restartKeyRepeat();
    setMainState(5);
}

void BirthdayMenu::enterListInputMode() {
    if (MenuCtrl_IsTouch()) {
        enterListTouchMode();
    } else {
        enterListButtonMode();
    }
}

void BirthdayMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    U94A->warpTo(a, b);
    if (testFlags(2) || cursorSlot != 2) {
        U94B->setAnimIfChanged(1);
    } else {
        U94B->setAnimIfChanged(7);
    }
    refreshCursor();
}

s32 BirthdayMenu::getCursorTargetX() {
    if (testFlags(2)) {
        return picker.getListCursorX();
    }
    if (cursorSlot == 2) {
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(6);
    }
    return sBirthdayCursorXTable[cursorSlot];
}

s32 BirthdayMenu::getCursorTargetY() {
    if (testFlags(2)) {
        return picker.getListCursorY();
    }
    if (cursorSlot == 2) {
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(6);
    }
    return sBirthdayCursorYTable[cursorSlot];
}

void BirthdayMenu::hideCursor() {
    U94B->setAnimIfChanged(0);
    cursor.update();
}

void BirthdayMenu::moveCursorToTarget() {
    if (testFlags(2) || cursorSlot != 2) {
        U94B->switchToAnim01();
    } else {
        U94B->switchToAnim07();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    startCursorMove(a, b);
}

void BirthdayMenu::startCursorMove(s32 a, s32 b) {
    if (testFlags(4)) {
        U94A->moveToEase(a, b, 2, 1);
    } else {
        U94A->moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(8);
    clearFlags(4);
}

void BirthdayMenu::refreshCursor() {
    U94A->setPoseIdle();
    cursor.update();
}

void BirthdayMenu::pressCursor() {
    U94B->setPosePress();
    setMainState(9);
}

void BirthdayMenu::releaseCursor() {
    U94A->setPoseRelease();
    returnState = mainState;
    setMainState(10);
}

BOOL BirthdayMenu::moveCursorByPad(u32 a) {
    u8 old = cursorSlot;
    if (MenuKeys_HasLeft(a)) {
        cursorSlot = sBirthdayCursorLeftTable[cursorSlot];
    } else if (MenuKeys_HasRight(a)) {
        cursorSlot = sBirthdayCursorRightTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    if (MenuKeys_HasUp(a)) {
        cursorSlot = sBirthdayCursorUpTable[cursorSlot];
    } else if (MenuKeys_HasDown(a)) {
        cursorSlot = sBirthdayCursorDownTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL BirthdayMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void BirthdayMenu::setFlags(u32 m) { flags = flags | m; }

void BirthdayMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" const u8 sBirthdayCursorRightTable[4] = {1, 1, 2, 0};

extern "C" const u8 sBirthdayCursorLeftTable[4] = {0, 0, 2, 0};

extern "C" const u8 sBirthdayCursorUpTable[4] = {0, 1, 1, 0};

extern "C" const u8 sBirthdayCursorDownTable[4] = {2, 2, 2, 0};

extern "C" const s32 sBirthdayCursorYTable[3] = {0x78, 0x78, 0};

extern "C" ProcProfile sBirthdayMenuProfile = {(void *(*)())BirthdayMenu_Create, 0xb0, 0xb4};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_02295380) {
    HOST_OVERLAY_VAR(sBirthdayMenuProfile),
    HOST_OVERLAY_VARS_END
};

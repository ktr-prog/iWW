#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/DateTimePicker.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "save/SaveData.h"
#include "sys/ClockDateTime.h"
#include "sys/ClockOffset.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov134/unk_ov134_02291f60.h"
#include "proto/ov135/unk_ov135_02295380.h"

extern "C" {
extern const u8 sClockAdjustCursorLeftTable[7];
extern const u8 sClockAdjustCursorRightTable[7];
extern const u8 sClockAdjustCursorDownTable[7];
extern const u8 sClockAdjustCursorUpTable[7];
extern const s32 sClockAdjustCursorXTable[7];
extern const s32 sClockAdjustCursorYTable[7];
extern u16 gPad[];

void MI_CpuCopy8(const void *src, void *dst, u32 n);
s32 ClockOffset_CalcMinutes(void *unused, u64 *b);
s32 ClockOffset_CalcSeconds(void *unused, u8 *b);
void Clock_Init();
}
extern SaveData gSaveData;









class ClockAdjustMenu;
typedef void (ClockAdjustMenu::*Unk_ov135_022964b0_Fn)();

static inline BOOL Unk_ov135_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

class ClockAdjustMenu : public MenuProc {
public:
    ClockAdjustMenu() : cursor(), bottomButtons(), picker() {}

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
    void runMainState();
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

    /* 0x091 */ u8 pad_91;
    /* 0x092 */ u16 flags;
    /* 0x094 */ u8 returnState;
    /* 0x095 */ u8 cursorSlot;
    /* 0x096 */ u8 unk_96[2];
    /* 0x098 */ MenuCursorBuf0 cursor;
    /* 0x0fc */ MenuBottomButtons bottomButtons;
    /* 0x260 */ DateTimePicker picker;
};

extern "C" ClockAdjustMenu *ClockAdjustMenu_Create() { return new ClockAdjustMenu(); }


extern "C" ProcProfile sClockAdjustMenuProfile = {(void *(*)())ClockAdjustMenu_Create, 0xae, 0xb2};

BOOL ClockAdjustMenu::onCreate() {
    initPicker();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL ClockAdjustMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL ClockAdjustMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
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

BOOL ClockAdjustMenu::execTransition() {
    static Unk_ov135_022964b0_Fn tbl[4] = {
        &ClockAdjustMenu::stateOpen,
        &ClockAdjustMenu::stateOpening,
        &ClockAdjustMenu::stateClose,
        &ClockAdjustMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void ClockAdjustMenu::runMainState() {
    static Unk_ov135_022964b0_Fn tbl[16] = {
        &ClockAdjustMenu::updateTouch,
        &ClockAdjustMenu::stateHandDrag,
        &ClockAdjustMenu::stateHandAnim,
        &ClockAdjustMenu::stateListTouch,
        &ClockAdjustMenu::stateListKnobDrag,
        &ClockAdjustMenu::stateListTrackDrag,
        &ClockAdjustMenu::updateButtons,
        &ClockAdjustMenu::stateListButtons,
        &ClockAdjustMenu::stateListKnobHold,
        &ClockAdjustMenu::stateListKnobRelease,
        &ClockAdjustMenu::updateCursorMove,
        &ClockAdjustMenu::updateCursorPress,
        &ClockAdjustMenu::updateCursorRelease,
        &ClockAdjustMenu::stateExit,
        &ClockAdjustMenu::stateListOpening,
        &ClockAdjustMenu::stateListClosing};
    (this->*tbl[mainState])();
}

BOOL ClockAdjustMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL ClockAdjustMenu::execPhase3() { return TRUE; }

BOOL ClockAdjustMenu::execPhase4() { return TRUE; }

BOOL ClockAdjustMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void ClockAdjustMenu::stateOpen() {
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

void ClockAdjustMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void ClockAdjustMenu::stateClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(10, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(3);
}

void ClockAdjustMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void ClockAdjustMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
}

void ClockAdjustMenu::initPicker() {
    DateTimePicker_Init(&picker, 0, 6, 4, 3);
    if (MenuCtrl_GetMode() == 0x33) {
        DateTimePicker_EnableMinLimit(&picker);
    }
    cursorSlot = 0;
    flags = 0;
}

void ClockAdjustMenu::releaseResources() {
    DateTimePicker_Shutdown(&picker);
    bottomButtons.freeTexts();
}

void ClockAdjustMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void ClockAdjustMenu::postInputUpdate() {
    postStateUpdate();
}

void ClockAdjustMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    Shared_DateTimePicker_BeginFrame(&picker);
}

void ClockAdjustMenu::postStateUpdate() {
    DateTimePicker_EndFrame(&picker);
}

void ClockAdjustMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 1);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 1);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void ClockAdjustMenu::loadBgGfx() {
    DateTimePicker_LoadBgGraphics(&picker);
    DateTimePicker_DrawTitleAndFields(&picker, 0x6b);
}

void ClockAdjustMenu::loadObjGfx() {
    DateTimePicker_LoadObjGraphics(&picker);
    MenuButtons_LoadTextColors();
}

void ClockAdjustMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        if (Unk_ov135_Both()) {
            if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6)) {
                confirm();
            } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(7)) {
                cancel();
            } else {
                u32 a = gTouchCurX;
                u32 b = gTouchCurY;
                if (Shared_DateTimePicker_GrabHand(&picker, a, b)) {
                    MenuCtrl_SetClockEdited();
                    setMainState(1);
                }
                s32 r = DateTimePicker_HitTestField(&picker, a, b);
                if (r != 6) {
                    openFieldList(r);
                }
            }
        }
    }
}

void ClockAdjustMenu::stateHandDrag() {
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

void ClockAdjustMenu::stateHandAnim() {
    if (Shared_DateTimePicker_UpdateHandAnim(&picker)) {
        setMainState(0);
    }
}

void ClockAdjustMenu::stateListTouch() {
    if (checkSwitchToButtons(1)) {
        enterListButtonMode();
    } else {
        if (Unk_ov135_Both()) {
            switch (Shared_DateTimePicker_HitTestList(&picker, gTouchCurX, gTouchCurY)) {
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
}

void ClockAdjustMenu::stateListKnobDrag() {
    if (gTouchHeld) {
        picker.dragKnob(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(3);
    }
}

void ClockAdjustMenu::stateListTrackDrag() {
    if (gTouchHeld) {
        picker.dragKnobToward(gTouchCurY);
    } else {
        picker.releaseKnob();
        setMainState(3);
    }
}

void ClockAdjustMenu::updateButtons() {
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

void ClockAdjustMenu::stateListButtons() {
    if (checkSwitchToTouch()) {
        enterListTouchMode();
        return;
    }
    s32 r = picker.navigateList(takeRepeatedKeys());
    switch (r) {
    case 0:
        goto zero;
    case 2:
        setFlags(4);
        break;
    case 3: {
        s32 b = getCursorTargetX();
        s32 c = getCursorTargetY();
        cursor.warpTo(b, c);
        return;
    }
    default:
        break;
    }
    moveCursorToTarget();
    return;
zero: {
        u32 v = gPad[1];
        if (v & 1) {
            pressCursor();
        } else if (v & 2) {
            cancelList();
        }
    }
}

void ClockAdjustMenu::stateListKnobHold() {
    if (gPad[0] & 1) {
        picker.moveKnobByPad();
        s32 b = getCursorTargetX();
        s32 c = getCursorTargetY();
        cursor.warpTo(b, c);
    } else {
        picker.releaseKnob();
        setMainState(9);
    }
}

void ClockAdjustMenu::stateListKnobRelease() {
    if (picker.finishKnobRelease()) {
        setMainState(7);
        releaseCursor();
    }
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    cursor.warpTo(b, c);
}

void ClockAdjustMenu::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void ClockAdjustMenu::updateCursorPress() {
    if (cursor.isAnimDone()) {
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
            if (v == 5) {
                confirm();
            } else if (v == 6) {
                cancel();
            } else {
                openFieldList(v);
            }
        }
    }
}

void ClockAdjustMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void ClockAdjustMenu::stateExit() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (cursor.getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            cursor.warpTo(a + b, a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void ClockAdjustMenu::stateListOpening() {
    if (Shared_DateTimePicker_UpdateListOpen(&picker)) {
        enterListInputMode();
    }
}

void ClockAdjustMenu::stateListClosing() {
    if (Shared_DateTimePicker_UpdateListClose(&picker)) {
        s32 r = DateTimePicker_GetCursorField(&picker);
        if (r == 6) {
            cursorSlot = 5;
        } else {
            cursorSlot = r;
        }
        resumeInput();
    }
}

void ClockAdjustMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void ClockAdjustMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(6);
}

void ClockAdjustMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void ClockAdjustMenu::confirm() {
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setTransitionState(2);
    setMainState(0xd);
    MenuCtrl_SetResult(1);
    ClockDateTimeWords v;
    v.words[0] = 0;
    v.words[1] = 0;
    DateTimePicker_GetDateTime(&picker, &v.dt);
    MenuCtrl_SetDateTime(&v);
    ClockOffset *offset = (ClockOffset *)gSaveData.clockOffset;
    if (DateTimePicker_IsBeforeStart(&picker)) {
        MenuCtrl_SetClockMovedBack();
    } else {
        MenuCtrl_SetClockMovedForward();
    }
    u64 a;
    MI_CpuCopy8(&v, &a, 8);
    s32 r4 = ClockOffset_CalcMinutes(offset, &a);
    u8 b[8];
    MI_CpuCopy8(&v, b, 8);
    u16 r = ClockOffset_CalcSeconds(offset, b);
    offset->minutes = r4;
    offset->seconds = r;
    Clock_Init();
}

void ClockAdjustMenu::cancel() {
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(7);
    setTransitionState(2);
    setMainState(0xd);
    MenuCtrl_SetResult(0);
}

void ClockAdjustMenu::openFieldList(u32 a) {
    hideCursor();
    DateTimePicker_OpenList(&picker, a);
    setMainState(0xe);
    MenuCtrl_SetClockEdited();
}

void ClockAdjustMenu::decideList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_DecideList(&picker);
    setMainState(0xf);
}

void ClockAdjustMenu::cancelList() {
    hideCursor();
    clearFlags(2);
    Shared_DateTimePicker_CancelList(&picker);
    setMainState(0xf);
}

void ClockAdjustMenu::enterListTouchMode() {
    hideCursor();
    setMainState(3);
}

void ClockAdjustMenu::enterListButtonMode() {
    s32 t = picker.getListCursorY();
    picker.setListCursorFromY(t);
    setFlags(2);
    showCursor();
    restartKeyRepeat();
    setMainState(7);
}

void ClockAdjustMenu::enterListInputMode() {
    if (MenuCtrl_IsTouch()) {
        enterListTouchMode();
    } else {
        enterListButtonMode();
    }
}

void ClockAdjustMenu::showCursor() {
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    cursor.warpTo(b, c);
    u32 v;
    if (testFlags(2) != 0 || ((v = cursorSlot) != 5 && v != 6)) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    }
    refreshCursor();
}

s32 ClockAdjustMenu::getCursorTargetX() {
    if (testFlags(2)) {
        return picker.getListCursorX();
    }
    switch (cursorSlot) {
    case 5:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(6);
    case 6:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(7);
    default:
        return sClockAdjustCursorXTable[cursorSlot];
    }
}

s32 ClockAdjustMenu::getCursorTargetY() {
    if (testFlags(2)) {
        return picker.getListCursorY();
    }
    switch (cursorSlot) {
    case 5:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(6);
    case 6:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(7);
    default:
        return sClockAdjustCursorYTable[cursorSlot];
    }
}

void ClockAdjustMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void ClockAdjustMenu::moveCursorToTarget() {
    u32 k;
    if (testFlags(2) != 0 || ((k = cursorSlot) != 5 && k != 6)) {
        ((MenuCursor *)&cursor)->switchToAnim01();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim07();
    }
    s32 b = getCursorTargetX();
    s32 c = getCursorTargetY();
    startCursorMove(b, c);
}

void ClockAdjustMenu::startCursorMove(s32 a, s32 b) {
    if (testFlags(4)) {
        cursor.moveToEase(a, b, 2, 1);
    } else {
        cursor.moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(0xa);
    clearFlags(4);
}

void ClockAdjustMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void ClockAdjustMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(0xb);
}

void ClockAdjustMenu::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(0xc);
}

BOOL ClockAdjustMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (MenuKeys_HasLeft(pad)) {
        cursorSlot = sClockAdjustCursorLeftTable[cursorSlot];
    } else if (MenuKeys_HasRight(pad)) {
        cursorSlot = sClockAdjustCursorRightTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    if (MenuKeys_HasUp(pad)) {
        cursorSlot = sClockAdjustCursorUpTable[cursorSlot];
    } else if (MenuKeys_HasDown(pad)) {
        cursorSlot = sClockAdjustCursorDownTable[cursorSlot];
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL ClockAdjustMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void ClockAdjustMenu::setFlags(u32 m) { flags = flags | m; }

void ClockAdjustMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" const s32 sClockAdjustCursorXTable[7] = {0xd6, 0x68, 0xa6, 0x68, 0xb0, 0};

extern "C" const s32 sClockAdjustCursorYTable[7] = {0x70, 0x70, 0x70, 0x90, 0x90, 0};

extern "C" const u8 sClockAdjustCursorLeftTable[7] = {2, 1, 1, 3, 3, 6, 6};

extern "C" const u8 sClockAdjustCursorRightTable[7] = {0, 2, 0, 4, 4, 5, 5};

extern "C" const u8 sClockAdjustCursorUpTable[7] = {0, 1, 2, 1, 2, 4, 3};

extern "C" const u8 sClockAdjustCursorDownTable[7] = {4, 3, 4, 6, 5, 5, 6};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov135_02295380) {
    HOST_OVERLAY_VAR(sClockAdjustMenuProfile),
    HOST_OVERLAY_VARS_END
};

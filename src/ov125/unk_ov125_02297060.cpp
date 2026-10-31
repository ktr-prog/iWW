#include "talk/EncodedString16Buf.h"
#include "host_shared_calls.h"
#include "talk/LabelBalloonText.h"
#include "types.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuCursor.h"
#include "menu/GeneralMenuHeader.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "sys/ProcProfile.h"
#include "player/PlayerData.h"
#include "save/Pattern.h"
#include "ui/LabelBalloon.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov125/unk_ov125_02297060.h"


extern "C" {
extern volatile u16 gPad[];
void MIi_CpuCopy16(const void *src, void *dest, u32 size);

BOOL PopupChoice_MoveCursor(void *p, s32 a, u8 *pos, u32 n);
BOOL PopupChoice_TickDecideDelay(void *p);
u8 PopupChoice_DecideCancel(void *p, s32 x);
void PopupChoice_DecideRow(void *p, s32 a, s32 b);
void PopupChoice_ForceClose(void *p);
void PopupChoice_Update(void *p);
void PopupChoice_Close(void *p, s32 v);
void PopupChoice_Open(void *p, s32 v);
void PopupChoice_LoadChoiceBg(void *p);

extern const u8 sPatternSelectSlotX[9];
extern const u8 sPatternSelectSlotY[9];
}














class PatternSelectMenu;
typedef void (PatternSelectMenu::*Unk_ov125_02298478_Fn)();

class PatternSelectMenu : public MenuProc {
public:
    PatternSelectMenu() : header(), popup(), nameBalloon(), cursor(), bottomButtons() {}

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
    BOOL moveCursorByPad(u32 pad);
    BOOL cursorRowDown(u32 lo, u32 hi, u32 to);
    BOOL cursorRowUp(u32 lo, u32 hi, u32 to);
    BOOL stepCursorLeft(u32 lo, u32 hi);
    BOOL stepCursorRight(u32 lo, u32 hi);
    void refreshCursor();
    void cursorToPopupTop();
    void showCursorAtSlot();
    void cancelPopup();
    void moveCursorToPopupRow();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void onPopupChoice();
    void openPopup();
    u32 getPopupRowValue(u32 i);
    void setPopupChoices();
    void updateNameLabel();
    void refreshNameLabel();
    u32 findTouchedSlot();
    s32 getSlotY(u32 i);
    s32 getSlotX(u32 i);
    void closeWithoutChoice();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updateBarTransition();
    void updatePopupDone();
    void updatePopupClose();
    void updatePopupOpen();
    void updateQuitPress();
    void updateCursorMove();
    void updatePopupPress();
    void updatePopupButtons();
    void updateButtons();
    void updatePopupTouch();
    void updateTouch();
    void loadPatternIcons();
    void loadHeaderBg();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initPatternSelect();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void stateLoad();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ GeneralMenuHeader header;
    /* 0x128 */ PopupChoiceMenu popup;
    /* 0x41c */ PopupChoiceIdList choiceList;
    /* 0x427 */ u8 pad_427[1];
    /* 0x428 */ TouchPromptBalloon nameBalloon;
    /* 0x4e8 */ MenuCursorBuf0 cursor;
    /* 0x54c */ MenuBottomButtons bottomButtons;
    /* 0x6b0 */ s32 slideY;
    /* 0x6b4 */ u16 flags;
    /* 0x6b6 */ u8 balloonSlot;
    /* 0x6b7 */ u8 selectedSlot;
    /* 0x6b8 */ u8 cursorSlot;
    /* 0x6b9 */ u8 popupChoice;
    /* 0x6ba */ u8 popupRow;
    /* 0x6bb */ u8 returnState;
};

extern "C" ProcProfile sPatternSelectMenuProfile = {(void *(*)())PatternSelectMenu_Create, 0xaa, 0xae};
extern "C" u16 sPatternSelectIconCell[4] = {0x00f0, 0x81f0, 0x40c0, 0xffff};

static inline BOOL Unk_ov125_02297bd4_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" PatternSelectMenu *PatternSelectMenu_Create() { return new PatternSelectMenu(); }

BOOL PatternSelectMenu::onCreate() {
    initPatternSelect();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL PatternSelectMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL PatternSelectMenu::onDraw() {
    s32 r7 = slideY;
    if (!testFlags(1)) {
        return FALSE;
    }
    TouchPromptBalloon *p = &nameBalloon;
    p->draw();
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    bottomButtons.drawAt(getSlideOffsetY());
    header.drawPlain(0, r7);
    u8 i = 0;
    s32 j = 0;
    do {
        sPatternSelectIconCell[2] = (sPatternSelectIconCell[2] & 0xfffffc00) | ((u16)(j * 4 + 0xc0) & 0x3ff);
        s32 y = r7 + getSlotY(i);
        Oam_DrawObj(1, sPatternSelectIconCell, getSlotX(i), y, j + 5, 2, NULL);
        i++;
        j++;
    } while (j < 8);
    return TRUE;
}

BOOL PatternSelectMenu::execTransition() {
    static Unk_ov125_02298478_Fn tbl[5] = {
        &PatternSelectMenu::stateLoad,
        &PatternSelectMenu::stateOpen,
        &PatternSelectMenu::stateOpening,
        &PatternSelectMenu::stateClose,
        &PatternSelectMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void PatternSelectMenu::runMainState() {
    static Unk_ov125_02298478_Fn tbl[11] = {
        &PatternSelectMenu::updateTouch,
        &PatternSelectMenu::updatePopupTouch,
        &PatternSelectMenu::updateButtons,
        &PatternSelectMenu::updatePopupButtons,
        &PatternSelectMenu::updatePopupPress,
        &PatternSelectMenu::updateCursorMove,
        &PatternSelectMenu::updateQuitPress,
        &PatternSelectMenu::updatePopupOpen,
        &PatternSelectMenu::updatePopupClose,
        &PatternSelectMenu::updatePopupDone,
        &PatternSelectMenu::updateBarTransition};
    (this->*tbl[mainState])();
}

BOOL PatternSelectMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL PatternSelectMenu::execPhase3() { return TRUE; }

BOOL PatternSelectMenu::execPhase4() { return TRUE; }

BOOL PatternSelectMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void PatternSelectMenu::stateLoad() {
    PatternSelect_SetupBgLayers();
    loadHeaderBg();
    setTransitionState(1);
}

void PatternSelectMenu::stateOpen() {
    PopupChoice_LoadChoiceBg(&popup);
    loadPatternIcons();
    beginSubSlideIn(0xa, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    updateLayerSlide();
    bottomButtons.setLayoutSingle05(0x65);
    setFlags(1);
    setTransitionState(2);
}

void PatternSelectMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void PatternSelectMenu::stateClose() {
    hideCursor();
    MenuLauncher *r4 = (MenuLauncher *)ProcBase_GetParent(this);
    s32 r6 = MenuCtrl_GetMode();
    if (testFlags(0x10)) {
        r4->setNextRequest(0x44, 1);
    } else if (r6 == 4) {
        r4->setNextRequest(2, 1);
    } else {
        r4->setNextRequest(0x44, 1);
    }
    beginSubSlideOut(0xa, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(4);
}

void PatternSelectMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        clearFlags(1);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void PatternSelectMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0);
    slideY = getSlideOffsetY();
}

void PatternSelectMenu::initPatternSelect() {
    flags = 0;
    popup.init(3, 1, 0);
    balloonSlot = 9;
    selectedSlot = 9;
    u32 z = 0;
    cursorSlot = z;
    MenuCtrl_SetResult(z);
    nameBalloon.setPriority(2);
}

void PatternSelectMenu::releaseResources() {
    PopupChoice_ForceClose(&popup);
    header.resetFrame();
    bottomButtons.freeTexts();
}

void PatternSelectMenu::preInputUpdate() {
    preStateUpdate();
    MenuCursorBuf0 *p = &cursor;
    p->update();
}

void PatternSelectMenu::postInputUpdate() {
    postStateUpdate();
}

void PatternSelectMenu::preStateUpdate() {
    bottomButtons.freeTexts();
    header.resetFrame();
}

void PatternSelectMenu::postStateUpdate() {
    Shared_PopupChoice_Update(&popup);
    if (nameBalloon.updatePrompt()) {
        refreshNameLabel();
    }
}

extern "C" void PatternSelect_SetupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 1);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void PatternSelectMenu::loadHeaderBg() {
    header.loadTitleBg(6, 4);
}

extern "C" void PatternSelect_LoadPatternIcons() {
    Heap *heap = gCurrentHeap;
    u32 *buf = (u32 *)Heap_AllocTail(heap, 0x1000);
    PlayerPatterns *obj = (PlayerPatterns *)PlayerData_GetCurrent()->getPatterns();
    u8 i = 0;
    do {
        u8 *t = obj->getPatternByOrder(i)->getPixels();
        Gfx2d_LinearToTilesInRow32((u32 *)t, buf, i * 4, 4, 4);
        i++;
    } while (i < 8);
    Gfx2d_LoadCharRange((u8 *)buf, 8, 0xc0, 0xc0, 0x13f);
    Heap_Free(heap, buf);
    u16 *buf2 = (u16 *)Heap_AllocTail(heap, 0x100);
    s32 off = 0;
    u8 k = 0;
    do {
        u8 *t = obj->getPatternByOrder(k)->getInfo()->getPaletteData();
        MIi_CpuCopy16(t, buf2 + off, 0x20);
        off += 0x10;
        k++;
    } while (k < 8);
    Gfx2d_LoadPaletteRange((u8 *)buf2, 8, 5, 5, 0xc);
    Heap_Free(heap, buf2);
}

void PatternSelectMenu::loadPatternIcons() {
    PatternSelect_LoadPatternIcons();
    header.loadObjGfx(4);
    MenuButtons_LoadTextColors();
}

void PatternSelectMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov125_02297bd4_Both()) {
        s32 r = findTouchedSlot();
        if (r == 8) {
            ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
            setMainState(10);
        } else if (r != 9) {
            setPopupChoices();
            selectedSlot = r;
            openPopup();
        }
    }
}

void PatternSelectMenu::updatePopupTouch() {
    if (checkSwitchToButtons(1)) {
        cursorToPopupTop();
        setMainState(3);
        cursorSlot = selectedSlot;
    } else if (Unk_ov125_02297bd4_Both()) {
        s32 r = ((PopupChoiceMenuBody *)&popup)->hitTestRowOrLast(gTouchCurX, gTouchCurY);
        if (r >= 0) {
            PopupChoice_DecideRow(&popup, r, 1);
            popupChoice = getPopupRowValue(r);
            setMainState(8);
        }
    }
}

void PatternSelectMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
        nameBalloon.hide(1);
    } else {
        if (moveCursorByPad(takeRepeatedKeys())) {
            updateNameLabel();
            moveCursorToTarget();
            nameBalloon.hide(0);
        } else {
            u32 t = gPad[1];
            if (t & 1) {
                if (cursorSlot == 8) {
                    ((MenuCursor *)&cursor)->setPosePress();
                    setMainState(6);
                } else {
                    nameBalloon.hide(1);
                    setPopupChoices();
                    selectedSlot = cursorSlot;
                    openPopup();
                    hideCursor();
                }
            } else if (t & 2) {
                hideCursor();
                ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
                setMainState(10);
                nameBalloon.hide(1);
            } else {
                nameBalloon.commitOpen();
            }
        }
    }
}

void PatternSelectMenu::updatePopupButtons() {
    if (checkSwitchToTouch()) {
        hideCursor();
        setMainState(1);
    } else {
        if (PopupChoice_MoveCursor(&popup, takeRepeatedKeys(), &popupRow, 0)) {
            moveCursorToPopupRow();
        }
        u32 t = gPad[1];
        if (t & 1) {
            ((MenuCursor *)&cursor)->setPosePress();
            setMainState(4);
        } else if (t & 2) {
            cancelPopup();
        }
    }
}

void PatternSelectMenu::updatePopupPress() {
    if (cursor.isAnimDone()) {
        PopupChoice_DecideRow(&popup, popupRow, 1);
        popupChoice = getPopupRowValue(popupRow);
        setMainState(8);
    }
}

void PatternSelectMenu::updateCursorMove() {
    if (cursor.isMoving() == 0) {
        setMainState(returnState);
        runMainState();
    }
}

void PatternSelectMenu::updateQuitPress() {
    if (cursor.isAnimDone()) {
        ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(9);
        setMainState(10);
    }
}

void PatternSelectMenu::updatePopupOpen() {
    if (((PopupChoiceMenuBody *)&popup)->isOpen()) {
        if (MenuCtrl_IsButtons()) {
            cursorToPopupTop();
            setMainState(3);
        } else {
            setMainState(1);
        }
    }
}

void PatternSelectMenu::updatePopupClose() {
    if (PopupChoice_TickDecideDelay(&popup)) {
        PopupChoice_Close(&popup, 0);
        if (cursor.getAnim()) {
            showCursorAtSlot();
        }
        setMainState(9);
    }
}

void PatternSelectMenu::updatePopupDone() {
    if (((PopupChoiceMenuBody *)&popup)->isClosed()) {
        onPopupChoice();
    }
}

void PatternSelectMenu::updateBarTransition() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (cursor.getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            cursor.warpTo(a + b, a + c);
        }
    } else {
        closeWithoutChoice();
    }
}

void PatternSelectMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void PatternSelectMenu::startButtonInput() {
    balloonSlot = 9;
    showCursor();
    restartKeyRepeat();
    updateNameLabel();
    setMainState(2);
}

void PatternSelectMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void PatternSelectMenu::closeWithoutChoice() {
    hideCursor();
    nameBalloon.hide(1);
    setFlags(0x10);
    transitionState = 3;
    MenuCtrl_SetResult(0);
    setPhase(1);
    Snd_PlaySe(0x28);
}

s32 PatternSelectMenu::getSlotX(u32 i) { return sPatternSelectSlotX[i]; }

s32 PatternSelectMenu::getSlotY(u32 i) { return sPatternSelectSlotY[i] - 0x10; }

u32 PatternSelectMenu::findTouchedSlot() {
    u8 i;
    if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(9)) {
        return 8;
    }
    s32 x = gTouchCurX;
    s32 y = gTouchCurY;
    s32 xlo = x - 0x10;
    s32 xhi = x + 0x10;
    s32 ylo = y - 0x10;
    s32 yhi = y + 0x10;
    for (i = 0; i < 8; i++) {
        s32 a = getSlotX(i);
        if (xlo < a && a < xhi) {
            s32 b = getSlotY(i);
            if (ylo < b && b < yhi) {
                return i;
            }
        }
    }
    return 9;
}

void PatternSelectMenu::refreshNameLabel() {
    s32 x = getSlotY(balloonSlot);
    x -= 0x84;
    if (MenuCtrl_IsButtons()) {
        x -= 0xa;
    }
    ((LabelBalloon *)(&nameBalloon))->setPos(getSlotX(balloonSlot) - 0x78, x);
    EncodedString16Buf a;
    ((PlayerPatterns *)PlayerData_GetCurrent()->getPatterns())->getPatternByOrder(balloonSlot)->getInfo()->getTitleEncoded(&a);
    LabelBalloonText b;
    StrBuf_GameToAscii((StrBuf *)&b, (StrBuf *)&a);
    ((LabelBalloon *)(&nameBalloon))->setText((StrBuf *)&b);
}

void PatternSelectMenu::updateNameLabel() {
    u32 v = cursorSlot;
    if (v <= 7) {
        balloonSlot = v;
        nameBalloon.queueOpen();
    } else {
        nameBalloon.hide(1);
    }
}

void PatternSelectMenu::setPopupChoices() {
    ChoiceIdList_Clear(choiceList.msgIds, 1);
    switch (MenuCtrl_GetMode()) {
    case 5:
    case 8:
    case 9:
        ChoiceIdList_Add(choiceList.msgIds, 0x91, 0);
        break;
    case 4:
    case 7:
    case 10:
        ChoiceIdList_Add(choiceList.msgIds, 0x72, 0);
        break;
    default:
        ChoiceIdList_Add(choiceList.msgIds, 0x28, 0);
        break;
    }
    ChoiceIdList_Add(choiceList.msgIds, 2, 1);
}

u32 PatternSelectMenu::getPopupRowValue(u32 i) { return choiceList.values[i]; }

void PatternSelectMenu::openPopup() {
    ((PopupChoiceMenuBody *)&popup)->setRowsFromIds(&choiceList, 0);
    s32 a = getSlotX(selectedSlot) - 0x18;
    s32 b = getSlotY(selectedSlot) - 0x10;
    popup.placeAbove(a, b);
    PopupChoice_Open(&popup, 0);
    setMainState(7);
}

void PatternSelectMenu::onPopupChoice() {
    switch (popupChoice) {
    case 0:
        MenuCtrl_SetIndex(selectedSlot);
        MenuCtrl_SetResult(1);
        transitionState = 3;
        nameBalloon.hide(1);
        setPhase(1);
        break;
    case 1:
    default:
        resumeInput();
        break;
    }
}

void PatternSelectMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    if (cursorSlot == 8) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 PatternSelectMenu::getCursorTargetX() {
    s32 t = getSlotX(cursorSlot);
    if (testFlags(8)) {
        t += 0x100;
    } else if (testFlags(4)) {
        t -= 0x100;
    }
    t += 0xb;
    return t;
}

s32 PatternSelectMenu::getCursorTargetY() { return getSlotY(cursorSlot) - 0xb; }

void PatternSelectMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void PatternSelectMenu::moveCursorToTarget() {
    if (testFlags(2)) {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.warpTo(a, b);
        clearFlags(2);
    } else {
        s32 a = getCursorTargetX();
        s32 b = getCursorTargetY();
        cursor.moveToEase(a, b, 3, 1);
        returnState = mainState;
        setMainState(5);
    }
}

void PatternSelectMenu::moveCursorToPopupRow() {
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    cursor.moveToLinear(a, b, 2);
    returnState = mainState;
    setMainState(5);
}

void PatternSelectMenu::cancelPopup() {
    popupChoice = 1;
    popupRow = PopupChoice_DecideCancel(&popup, 1);
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    cursor.warpTo(a, b);
    cursor.setAnimAtEnd(8);
    setMainState(8);
}

void PatternSelectMenu::showCursorAtSlot() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(1);
}

void PatternSelectMenu::cursorToPopupTop() {
    popupRow = 0;
    s32 a = ((PopupChoiceMenuBody *)&popup)->getRowX();
    s32 b = ((PopupChoiceMenuBody *)&popup)->getRowY(popupRow);
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
}

void PatternSelectMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

BOOL PatternSelectMenu::stepCursorRight(u32 lo, u32 hi) {
    u32 v = cursorSlot;
    if (v >= lo && v <= hi) {
        if (v == hi) {
            setFlags(8);
            cursorSlot = lo;
        } else {
            cursorSlot = v + 1;
        }
        return TRUE;
    }
    return FALSE;
}

BOOL PatternSelectMenu::stepCursorLeft(u32 lo, u32 hi) {
    u32 v = cursorSlot;
    if (v >= lo && v <= hi) {
        if (v == lo) {
            cursorSlot = hi;
            setFlags(4);
        } else {
            cursorSlot = v - 1;
        }
        return TRUE;
    }
    return FALSE;
}

BOOL PatternSelectMenu::cursorRowUp(u32 lo, u32 hi, u32 to) {
    u32 v = cursorSlot;
    if (v >= lo && v <= hi) {
        cursorSlot = v + (to - lo);
        return TRUE;
    }
    return FALSE;
}

BOOL PatternSelectMenu::cursorRowDown(u32 lo, u32 hi, u32 to) {
    u32 v = cursorSlot;
    if (v >= lo && v <= hi) {
        cursorSlot = v + (to - lo);
        return TRUE;
    }
    return FALSE;
}

BOOL PatternSelectMenu::moveCursorByPad(u32 pad) {
    u32 prev = cursorSlot;
    clearFlags(0xc);
    if (MenuKeys_HasLeft(pad)) {
        if (!stepCursorLeft(0, 3)) {
            stepCursorLeft(4, 7);
        }
    } else if (MenuKeys_HasRight(pad)) {
        if (!stepCursorRight(0, 3)) {
            stepCursorRight(4, 7);
        }
    }
    if (!testFlags(0xc)) {
        if (MenuKeys_HasUp(pad)) {
            if (!cursorRowUp(4, 7, 0)) {
                if (cursorSlot == 8) {
                    cursorSlot = 7;
                    ((MenuCursor *)&cursor)->switchToAnim01();
                }
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (!cursorRowDown(0, 3, 4)) {
                u32 t = cursorSlot;
                if (t >= 4 && t <= 7) {
                    cursorSlot = 8;
                    ((MenuCursor *)&cursor)->switchToAnim07();
                }
            }
        }
    }
    if (prev != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

BOOL PatternSelectMenu::testFlags(u32 mask) {
    if (flags & mask) {
        return TRUE;
    }
    return FALSE;
}

void PatternSelectMenu::setFlags(u32 mask) { flags = flags | mask; }

void PatternSelectMenu::clearFlags(u32 mask) { flags = flags & ~mask; }

extern "C" const u8 sPatternSelectSlotX[9] = {0x28, 0x60, 0x98, 0xd0, 0x38, 0x70, 0xa8, 0xe0, 0xb9};
extern "C" const u8 sPatternSelectSlotY[9] = {0x7c, 0x7c, 0x7c, 0x7c, 0xa4, 0xa4, 0xa4, 0xa4, 0xd1};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov125_02297060) {
    HOST_OVERLAY_VAR(sPatternSelectMenuProfile),
    HOST_OVERLAY_VAR(sPatternSelectIconCell),
    HOST_OVERLAY_VARS_END
};

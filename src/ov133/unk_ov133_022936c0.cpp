#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "net/CommManager.h"
#include "player/PlayerId.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "player/PlayerData.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuErrorMessage.h"
#include "menu/MenuTabBar.h"
#include "sys/ProcProfile.h"
#include "net/FriendEntry.h"
#include "net/DwcFriendControl.h"
#include "nitro/gxoam.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020742f4.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/main/unk_02087e70.h"
#include "proto/ov130/unk_ov130_02292360.h"
#include "proto/ov133/unk_ov133_022936c0.h"

extern "C" {
extern const u8 sKeyDigits[12];
extern const u32 sKeyColumnX[3];
extern const u8 sFriendCodeTouchKeyMap[12];
extern const s32 sFriendCodeCursorYTable[12];
extern const u32 sKeyRowY[12];
extern const s32 sFriendCodeCursorXTable[12];
extern u8 gU8None;
extern u16 gPad[];

FriendEntry *FriendList_GetEntries(FriendEntry *p);
BOOL DwcFriendData_Compare(DwcFriendData *self, void *src);
}




extern "C" CommManager *gCommManager;












class FriendCodeMenu;
typedef void (FriendCodeMenu::*Unk_ov133_022952bc_Fn)();

class FriendCodeMenu : public MenuProc {
public:
    FriendCodeMenu() : labels(), cursor(), bottomButtons(), screenTasks(), errorMessage() {}

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
    void unhighlightKey(s32 idx);
    void highlightKey(s32 idx);
    void setKeyPalette(s32 idx, u32 to);
    void resetKeyPalettes();
    BOOL tickKeyRepeat();
    void stopKeyRepeat();
    BOOL pressCursorKey();
    void flushScreens();
    void drawSelection();
    void drawCodeDigits();
    s32 getCodeLength();
    BOOL insertDigit(u8 v);
    void deleteSelection();
    BOOL deleteBackward(s32 f);
    void clearCode();
    void loadEntryCode();
    void extendSelection(s32 x);
    void setCaret(u8 x);
    s32 getCaretFromTouch();
    BOOL moveCaretByPad(u32 key);
    BOOL applyKey(s32 a);
    s32 activateCursorKey();
    void cancel();
    void confirm();
    BOOL isOwnFriendCode();
    BOOL isDuplicateFriend(DwcFriendData *a);
    FriendEntry *getFriendEntry();
    u32 hitTest(s32 x, s32 y);
    BOOL moveCursorByPad(u32 keys);
    void refreshCursor();
    void releaseCursor();
    void pressCursor();
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    LabelString *allocLabel();
    void releaseLabels();
    void showMessage(u8 v, s32 b);
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void stateRetryAddFriend();
    void stateMessage();
    void stateExit();
    void stateCaretSelect();
    void stateBackspaceRepeat();
    void stateButtonRepeat();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateButtons();
    void stateTouchDragCaret();
    void stateTouchRepeat();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postInputUpdate();
    void preInputUpdate();
    void postStateUpdate();
    void preStateUpdate();
    void releaseResources();
    void initState();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void stateLoad();
    BOOL notifyParent(u32 v);
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideY;
    /* 0x098 */ u16 flags;
    /* 0x09a */ u8 labelCount;
    /* 0x09b */ u8 returnState;
    /* 0x09c */ u8 cursorSlot;
    /* 0x09d */ u8 repeatTimer;
    /* 0x09e */ u8 highlightTimer;
    /* 0x09f */ u8 caretPos;
    /* 0x0a0 */ u8 pressedKey;
    /* 0x0a1 */ u8 caretBlinkTimer;
    /* 0x0a2 */ u8 selectionEnd;
    /* 0x0a3 */ u8 selectionAnchor;
    /* 0x0a4 */ u8 codeDigits[12];
    /* 0x0b0 */ LabelString labels[1];
    /* 0x0f0 */ MenuCursorBuf0 cursor;
    /* 0x154 */ MenuBottomButtons bottomButtons;
    /* 0x2b8 */ BgVramTask screenTasks[2];
    /* 0x300 */ u16 keypadScreen[0x400];
    /* 0xb00 */ u16 codeScreen[0x400];
    /* 0x1300 */ MenuErrorMessage errorMessage;
};


extern "C" FriendCodeMenu *FriendCodeMenu_Create() { return new FriendCodeMenu(); }

BOOL FriendCodeMenu::onCreate() {
    initState();
    setTransitionState(0);
    setPhase(1);
    return TRUE;
}

BOOL FriendCodeMenu::onDelete() {
    MenuTabBar *p = (MenuTabBar *)ProcBase_GetParent(this);
    if (p->onTabMenuClosed() == 6) {
        p->showTabs();
    }
    releaseResources();
    return TRUE;
}

BOOL FriendCodeMenu::onDraw() {
    if (!testFlags(1)) {
        return TRUE;
    }
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    bottomButtons.drawAt(slideY);
    Shared_NumberPad_DrawKeypadFrame(slideY);
    if (caretBlinkTimer & 0x10) {
        Oam_DrawCell(1, sCaretCells, (caretPos << 4) + 0x20, slideY + 0x40, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    return TRUE;
}
extern "C" u16 sFriendCodeKeySeIds[10];
extern "C" GXOamAttr sCaretCells[1];
extern "C" const u32 sKeyColumnX[3];
extern "C" const s32 sFriendCodeCursorXTable[12];
extern "C" const u8 sKeyDigits[12];
extern "C" const u8 sFriendCodeTouchKeyMap[12];
extern "C" const s32 sFriendCodeCursorYTable[12];
extern "C" const u32 sKeyRowY[12];
extern "C" ProcProfile sFriendCodeMenuProfile;

BOOL FriendCodeMenu::execTransition() {
    static Unk_ov133_022952bc_Fn tbl[5] = {
        &FriendCodeMenu::stateLoad,
        &FriendCodeMenu::stateOpen,
        &FriendCodeMenu::stateOpening,
        &FriendCodeMenu::stateClose,
        &FriendCodeMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}
extern "C" u16 sFriendCodeKeySeIds[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

extern "C" GXOamAttr sCaretCells[1] = {{0x000080f8, 0x181, 0, 0x5, 0xffff}};

extern "C" const u32 sKeyColumnX[3] = {9, 0xe, 0x12};

extern "C" const s32 sFriendCodeCursorXTable[12] = {0x60, 0x80, 0xa0, 0x60, 0x80, 0xa0, 0x60, 0x80, 0xa0, 0x60, 0x80, 0xa0};

void FriendCodeMenu::runMainState() {
    static Unk_ov133_022952bc_Fn tbl[13] = {
        &FriendCodeMenu::updateTouch,
        &FriendCodeMenu::stateTouchRepeat,
        &FriendCodeMenu::stateTouchDragCaret,
        &FriendCodeMenu::updateButtons,
        &FriendCodeMenu::updateCursorMove,
        &FriendCodeMenu::updateCursorPress,
        &FriendCodeMenu::updateCursorRelease,
        &FriendCodeMenu::stateButtonRepeat,
        &FriendCodeMenu::stateBackspaceRepeat,
        &FriendCodeMenu::stateCaretSelect,
        &FriendCodeMenu::stateExit,
        &FriendCodeMenu::stateMessage,
        &FriendCodeMenu::stateRetryAddFriend};
    MenuCtrl_TickForceClose();
    if (MenuCtrl_IsForceCloseDue()) {
        switch (mainState) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 7:
        case 8:
        case 9:
            hideCursor();
            setTransitionState(3);
            notifyParent(7);
            if (MenuCtrl_GetMode() == 0xe) {
                FriendEntry_Clear(getFriendEntry());
            }
            setPhase(1);
            break;
        case 4:
        case 5:
        case 6:
            break;
        }
    }
    (this->*tbl[mainState])();
}

BOOL FriendCodeMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL FriendCodeMenu::execPhase3() { return TRUE; }

BOOL FriendCodeMenu::execPhase4() { return TRUE; }

BOOL FriendCodeMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

BOOL FriendCodeMenu::notifyParent(u32 v) {
    ((MenuTabBar *)ProcBase_GetParent(this))->selectTab((u8)v);
    return TRUE;
}

void FriendCodeMenu::stateLoad() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    setTransitionState(1);
    bottomButtons.setLayoutConfirmAnd06(0x65);
    stateOpen();
}

void FriendCodeMenu::stateOpen() {
    beginSubSlideIn(0xa, 0, 0, 0x30);
    Gfx2d_ShowLayer(4);
    applySlideOffset(4, 0, 0);
    Gfx2d_ShowLayer(6);
    applySlideOffset(6, 0, 0);
    setFlags(1);
    slideY = getSlideOffsetY();
    setTransitionState(2);
}

void FriendCodeMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    applySlideOffset(4, 0, 0);
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void FriendCodeMenu::stateClose() {
    hideCursor();
    beginSubSlideOut(0xa, 0, 0, 0x30);
    applySlideOffset(4, 0, 0);
    applySlideOffset(6, 0, 0);
    setTransitionState(4);
    slideY = getSlideOffsetY();
}

void FriendCodeMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(4);
        Gfx2d_ResetLayer(6);
        clearFlags(1);
        setPhase(5);
    } else {
        applySlideOffset(4, 0, 0);
        applySlideOffset(6, 0, 0);
        slideY = getSlideOffsetY();
    }
}

void FriendCodeMenu::initState() {
    labelCount = 0;
    flags = 0;
    cursorSlot = 0xb;
    highlightTimer = 0;
    repeatTimer = 0;
    void *p = PlayerData_GetCurrent();
    if (p != 0) {
        if (((PlayerId *)((PlayerData *)p)->getPlayerId())->getGender() == 0) {
            Snd_SetKeySeMode(0);
            return;
        }
    }
    Snd_SetKeySeMode(1);
}

void FriendCodeMenu::releaseResources() {
    screenTasks[0].cancel();
    screenTasks[1].cancel();
    releaseLabels();
    bottomButtons.freeTexts();
}

void FriendCodeMenu::preStateUpdate() {
    screenTasks[0].cancel();
    screenTasks[1].cancel();
    releaseLabels();
    bottomButtons.freeTexts();
    if (highlightTimer != 0) {
        highlightTimer = highlightTimer - 1;
        if (highlightTimer == 0) {
            if (repeatTimer != 0) {
                highlightTimer = 1;
            } else {
                unhighlightKey(pressedKey);
            }
        }
    }
    caretBlinkTimer = caretBlinkTimer + 1;
}

void FriendCodeMenu::postStateUpdate() { flushScreens(); }

void FriendCodeMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void FriendCodeMenu::postInputUpdate() { postStateUpdate(); }

void FriendCodeMenu::setupBgLayers() {
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void FriendCodeMenu::loadBgGfx() {
    NumberPad_LoadBgGraphics(4);
    File_LoadToBuffer("menu/bank/g0_bg.bsc", codeScreen, 0x800);
    File_LoadToBuffer("menu/bank/g1_bg.bsc", keypadScreen, 0x800);
    loadEntryCode();
    setFlags(2);
    setFlags(4);
}

void FriendCodeMenu::loadObjGfx() {
    NumberPad_LoadObjGraphics(7);
    LabelString *p = allocLabel();
    String_Load2dMenu(p, 0xd7);
    p->createLabel(8, 0x14c, 0xe, 0xf, 0, 0);
    p->redrawAligned(1, 0);
    MenuButtons_LoadTextColors();
}

void FriendCodeMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else {
        BOOL ok;
        if (gTouchHeld != 0 && gTouchChanged != 0) {
            ok = TRUE;
        } else {
            ok = FALSE;
        }
        if (ok) {
            if (((MenuBottomButtonsBody *)&bottomButtons)->isButtonDisabled(6) == 0 && ((MenuBottomButtonsBody *)&bottomButtons)->isTouched(6) != 0) {
                confirm();
            } else if (((MenuBottomButtonsBody *)&bottomButtons)->isTouched(7)) {
                cancel();
            } else {
                u32 r = hitTest(gTouchCurX, gTouchCurY);
                if (r == 0xc) {
                    u32 t = getCaretFromTouch();
                    setCaret((u8)t);
                    setMainState(2);
                } else if (r != 0xf) {
                    if (pressCursorKey()) {
                        setMainState(1);
                    }
                }
            }
        }
    }
}

void FriendCodeMenu::stateTouchRepeat() {
    if (gTouchHeld == 0) {
        stopKeyRepeat();
        setMainState(0);
    } else {
        if (tickKeyRepeat()) {
            applyKey(0);
        }
    }
}

void FriendCodeMenu::stateTouchDragCaret() {
    if (gTouchHeld == 0) {
        setMainState(0);
    } else {
        u32 r = getCaretFromTouch();
        extendSelection((u8)r);
    }
}

void FriendCodeMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        u32 k = takeRepeatedKeys();
        if (moveCursorByPad(k)) {
            moveCursorToTarget();
        } else {
            u32 t = gPad[1];
            if (t & 1) {
                pressCursor();
            } else if (t & 2) {
                if (deleteBackward(0)) {
                    repeatTimer = 0xd;
                    setMainState(8);
                    if (cursorSlot == 0xc) {
                        s32 x = getCursorTargetX();
                        s32 y = getCursorTargetY();
                        cursor.warpTo(x, y);
                    }
                } else {
                    cancel();
                    hideCursor();
                }
            } else if (t & 8) {
                if (!((MenuBottomButtonsBody *)&bottomButtons)->isButtonDisabled(6)) {
                    confirm();
                    hideCursor();
                }
            }
        }
    }
}

void FriendCodeMenu::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void FriendCodeMenu::updateCursorPress() {
    if (cursor.isAnimDone()) {
        s32 r = activateCursorKey();
        switch (r) {
        case 1:
            break;
        case 2:
            releaseCursor();
            break;
        default:
            releaseCursor();
            break;
        }
    }
}

void FriendCodeMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(3);
    }
}

void FriendCodeMenu::stateButtonRepeat() {
    if ((gPad[0] & 1) == 0) {
        stopKeyRepeat();
        setMainState(3);
        releaseCursor();
    } else {
        if (tickKeyRepeat()) {
            applyKey(0);
        }
    }
}

void FriendCodeMenu::stateBackspaceRepeat() {
    if ((gPad[0] & 2) == 0) {
        stopKeyRepeat();
        setMainState(3);
    } else {
        if (tickKeyRepeat()) {
            if (deleteBackward(1)) {
                if (cursorSlot == 0xc) {
                    s32 x = getCursorTargetX();
                    s32 y = getCursorTargetY();
                    cursor.warpTo(x, y);
                }
            }
        }
    }
}

void FriendCodeMenu::stateCaretSelect() {
    if ((gPad[0] & 1) == 0) {
        setMainState(3);
        releaseCursor();
    } else {
        u32 k = takeRepeatedKeys();
        if (moveCaretByPad(k)) {
            extendSelection(caretPos);
        }
    }
}

void FriendCodeMenu::stateExit() {
    if (((MenuBottomButtonsBody *)&bottomButtons)->stepPress()) {
        if (cursor.getAnim()) {
            s32 a = ((MenuBottomButtonsBody *)&bottomButtons)->getPressOffset();
            s32 b = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(-1);
            s32 c = ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(-1);
            cursor.warpTo(a + (b - 6), a + c);
        }
    } else {
        hideCursor();
        setPhase(1);
    }
}

void FriendCodeMenu::stateMessage() {
    if (errorMessage.update(1)) {
        resumeInput();
    }
}

void FriendCodeMenu::stateRetryAddFriend() {
    FriendEntry *r = getFriendEntry();
    s32 idx = MenuCtrl_GetIndex();
    void *t = DwcFriendData_GetBytes(FriendEntry_GetFriendData(r));
    if (Net_WifiAddFriend((u8)idx, t)) {
        setMainState(10);
    }
}

void FriendCodeMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void FriendCodeMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(3);
}

void FriendCodeMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void FriendCodeMenu::showMessage(u8 v, s32 b) {
    u8 l;
    u8 *p = &l;
    *p = gU8None;
    *p = v;
    errorMessage.open(p, b, 0);
    setMainState(0xb);
    hideCursor();
}

void FriendCodeMenu::releaseLabels() {
    labelCount = 0;
    labels[0].destroyLabel();
}

LabelString *FriendCodeMenu::allocLabel() {
    if (labelCount >= 1) {
        return &labels[0];
    }
    labelCount = labelCount + 1;
    return &labels[labelCount - 1];
}

void FriendCodeMenu::showCursor() {
    s32 x = getCursorTargetX();
    s32 y = getCursorTargetY();
    cursor.warpTo(x, y);
    if ((u8)(cursorSlot + 0xf3) <= 1) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 FriendCodeMenu::getCursorTargetX() {
    u32 v = cursorSlot;
    if (v <= 0xb) {
        return sFriendCodeCursorXTable[v];
    }
    switch (v) {
    case 0xc:
        return (caretPos << 4) + 0x20;
    case 0xd:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(6);
    case 0xe:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetX(7);
    default:
        return 0x80;
    }
}

s32 FriendCodeMenu::getCursorTargetY() {
    u32 v = cursorSlot;
    if (v <= 0xb) {
        return sFriendCodeCursorYTable[v];
    }
    switch (v) {
    case 0xc:
        return 0x40;
    case 0xd:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(6);
    case 0xe:
        return ((MenuBottomButtonsBody *)&bottomButtons)->getTargetY(7);
    default:
        return 0x60;
    }
}

void FriendCodeMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void FriendCodeMenu::moveCursorToTarget() {
    if ((u8)(cursorSlot + 0xf3) <= 1) {
        ((MenuCursor *)&cursor)->switchToAnim07();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    s32 x = getCursorTargetX();
    s32 y = getCursorTargetY();
    cursor.moveToEase(x, y, 3, 1);
    returnState = mainState;
    setMainState(4);
}

void FriendCodeMenu::pressCursor() {
    if (cursorSlot == 0xc) {
        setMainState(9);
    } else {
        ((MenuCursor *)&cursor)->setPosePress();
        setMainState(5);
    }
}

void FriendCodeMenu::releaseCursor() {
    cursor.setPoseRelease();
    setMainState(6);
}

void FriendCodeMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

BOOL FriendCodeMenu::moveCursorByPad(u32 keys) {
    u32 old = cursorSlot;
    if (keys == 0) {
        return FALSE;
    }
    if (old <= 0xb) {
        if (MenuKeys_HasLeft(keys)) {
            if ((s32)cursorSlot % 3 > 0) {
                cursorSlot = cursorSlot - 1;
            }
        } else if (MenuKeys_HasRight(keys)) {
            if ((s32)cursorSlot % 3 < 2) {
                cursorSlot = cursorSlot + 1;
            } else {
                cursorSlot = 0xd;
            }
        }
        if (cursorSlot <= 0xb) {
            if (MenuKeys_HasUp(keys)) {
                if (cursorSlot <= 2) {
                    cursorSlot = 0xc;
                } else {
                    cursorSlot = cursorSlot - 3;
                }
            } else if (MenuKeys_HasDown(keys)) {
                u32 v = cursorSlot;
                if (v < 9 || v > 0xb) {
                    cursorSlot = cursorSlot + 3;
                } else {
                    cursorSlot = 0xe;
                }
            }
        }
    } else if (old == 0xc) {
        if (MenuKeys_HasDown(keys)) {
            s32 r = cursor.getScreenX();
            if (r <= 0x70) {
                cursorSlot = 0;
            } else if (r <= 0x90) {
                cursorSlot = 1;
            } else {
                cursorSlot = 2;
            }
        } else if (moveCaretByPad(keys)) {
            Snd_PlaySe(0xb);
            setCaret(caretPos);
        }
    } else if (old == 0xd) {
        if (MenuKeys_HasLeft(keys)) {
            cursorSlot = 0xe;
        } else if (MenuKeys_HasUp(keys)) {
            cursorSlot = 0xb;
        }
    } else if (old == 0xe) {
        if (MenuKeys_HasRight(keys)) {
            cursorSlot = 0xd;
        } else if (MenuKeys_HasUp(keys)) {
            cursorSlot = 0xa;
        }
    }
    if (old == cursorSlot) {
        return FALSE;
    }
    return TRUE;
}

u32 FriendCodeMenu::hitTest(s32 x0, s32 y) {
    s32 x = x0 - 0x50;
    s32 t = y - 0x60;
    if (x >= 0 && x < 0x60 && t >= 0 && t < 0x40) {
        cursorSlot = sFriendCodeTouchKeyMap[(x >> 5) + (t >> 4) * 3];
        return cursorSlot;
    }
    if (y >= 0x40 && y <= 0x50) {
        cursorSlot = 0xc;
        return cursorSlot;
    }
    return 0xf;
}

FriendEntry *FriendCodeMenu::getFriendEntry() {
    FriendList *h = (FriendList *)PlayerData_GetCurrent()->getFriendList();
    s32 idx = MenuCtrl_GetIndex();
    return FriendList_GetEntries(h->entries) + idx;
}

BOOL FriendCodeMenu::isDuplicateFriend(DwcFriendData *a) {
    PlayerData *h = PlayerData_GetCurrent();
    s32 idx = MenuCtrl_GetIndex();
    FriendEntry *p = FriendList_GetEntries(((FriendList *)h->getFriendList())->entries);
    s32 i;
    for (i = 0; i < 0x20; p++, i++) {
        if (DwcFriendData_IsValid(FriendEntry_GetFriendData(p)) && i != idx) {
            if (DwcFriendData_Compare(a, FriendEntry_GetFriendData(p))) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL FriendCodeMenu::isOwnFriendCode() {
    PlayerData *h = PlayerData_GetCurrent();
    s64 sum = 0;
    s32 i;
    for (i = 0; i < 12; i++) {
        sum = sum * 10 + (s64)(u32)codeDigits[i];
    }
    return PlayerWifiData_GetFriendCode(h->getWifiUserData()) == sum;
}

void FriendCodeMenu::confirm() {
    PlayerData *h = PlayerData_GetCurrent();
    DwcFriendData l;
    DwcFriendData_Clear(&l);
    if (!DwcFriendData_FromCodeDigits(&l, codeDigits, PlayerWifiData_GetDwcUserData(h->getWifiUserData()))) {
        showMessage(0x19, 0);
        Snd_PlaySe(0x73);
        return;
    }
    if (isOwnFriendCode()) {
        showMessage(0x1d, 0);
        Snd_PlaySe(0x73);
        return;
    }
    if (isDuplicateFriend(&l)) {
        showMessage(0x14, 0);
        Snd_PlaySe(0x73);
        return;
    }
    FriendEntry *s = getFriendEntry();
    void *t = FriendEntry_GetFriendData(s);
    DwcFriendData_FromCodeDigits(t, codeDigits, PlayerWifiData_GetDwcUserData(h->getWifiUserData()));
    MenuCtrl_SetResult(1);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(6);
    setTransitionState(3);
    setMainState(10);
    Snd_PlaySe(0x29);
    if (MenuCtrl_GetMode() == 0xe) {
        notifyParent(0xc);
    } else {
        ((MenuTabBar *)ProcBase_GetParent(this))->requestSaveOnClose();
        notifyParent(6);
        MenuCtrl_SetFriendPageFromIndex();
        if (gCommManager->isSlotActive(gCommManager->myAid)) {
            switch (Net_GetMode()) {
            case 3:
            case 4: {
                s32 pl = MenuCtrl_GetIndex();
                void *x = DwcFriendData_GetBytes(FriendEntry_GetFriendData(s));
                if (!Net_WifiAddFriend((u8)pl, x)) {
                    setMainState(0xc);
                    return;
                }
            }
            }
        }
    }
}

void FriendCodeMenu::cancel() {
    MenuCtrl_SetResult(0);
    ((MenuBottomButtonsBody *)&bottomButtons)->setSelected(7);
    setTransitionState(3);
    setMainState(10);
    notifyParent(6);
    if (MenuCtrl_GetMode() == 0xe) {
        FriendEntry_Clear(getFriendEntry());
    }
    Snd_PlaySe(0x28);
}

s32 FriendCodeMenu::activateCursorKey() {
    u32 st = cursorSlot;
    if (st <= 11) {
        if (pressCursorKey()) {
            setMainState(7);
            return 1;
        }
        return 2;
    }
    switch (st) {
    case 12:
        break;
    case 13:
        if (!((MenuBottomButtonsBody *)&bottomButtons)->isButtonDisabled(6)) {
            confirm();
            return 1;
        }
        return 0;
    case 14:
        cancel();
        return 1;
    }
    return 0;
}

BOOL FriendCodeMenu::applyKey(s32 a) {
    u32 st = cursorSlot;
    switch (st) {
    case 11:
        if (a) {
            clearCode();
            Shared_NumberPad_PlayCancelSe();
        }
        repeatTimer = 0;
        return FALSE;
    case 10:
        deleteBackward(1);
        return TRUE;
    default:
        if (st <= 9) {
            u8 v = sKeyDigits[st];
            if (insertDigit(v)) {
                Snd_PlayKeySe(sFriendCodeKeySeIds[v]);
            }
        }
        return TRUE;
    }
}

BOOL FriendCodeMenu::moveCaretByPad(u32 key) {
    u32 old = caretPos;
    if (MenuKeys_HasLeft(key)) {
        if (caretPos != 0) {
            caretPos = caretPos - 1;
        }
    } else if (MenuKeys_HasRight(key)) {
        if (getCodeLength() > caretPos) {
            caretPos = caretPos + 1;
        }
    }
    if (old != caretPos) {
        s32 x = getCursorTargetX();
        s32 y = getCursorTargetY();
        cursor.warpTo(x, y);
        return TRUE;
    }
    return FALSE;
}

s32 FriendCodeMenu::getCaretFromTouch() {
    s32 v = gTouchCurX - 0x18;
    if (v < 0) {
        v = 0;
    }
    s32 r = v >> 4;
    s32 n = getCodeLength();
    if (r > n) {
        r = n;
    }
    return r;
}

void FriendCodeMenu::setCaret(u8 x) {
    caretPos = x;
    caretBlinkTimer = 0x10;
    selectionEnd = x;
    selectionAnchor = x;
    setFlags(0x10);
}

void FriendCodeMenu::extendSelection(s32 x) {
    caretPos = x;
    caretBlinkTimer = 0x10;
    if (selectionEnd != x) {
        Snd_PlaySe(0x15);
    }
    selectionEnd = x;
    setFlags(0x10);
}

void FriendCodeMenu::loadEntryCode() {
    if (DwcFriendData_ToCodeDigits(FriendEntry_GetFriendData(getFriendEntry()), codeDigits)) {
        setCaret(0);
        setFlags(8);
    } else {
        clearCode();
    }
}

void FriendCodeMenu::clearCode() {
    s32 i;
    for (i = 0; i < 12; i++) {
        codeDigits[i] = 10;
    }
    setCaret(0);
    setFlags(8);
}

BOOL FriendCodeMenu::deleteBackward(s32 f) {
    s32 i;
    if (selectionEnd != selectionAnchor) {
        deleteSelection();
        Snd_PlaySe(0x35);
        return TRUE;
    }
    if (caretPos == 0) {
        if (codeDigits[0] != 10) {
            caretPos = 1;
        } else {
            if (f) {
                Snd_PlaySe(0x34);
            }
            return FALSE;
        }
    }
    for (i = caretPos; i < 12; i++) {
        codeDigits[i - 1] = codeDigits[i];
    }
    codeDigits[11] = 10;
    setFlags(8);
    setCaret(caretPos - 1);
    Snd_PlaySe(0x35);
    return TRUE;
}

void FriendCodeMenu::deleteSelection() {
    u32 b = selectionAnchor;
    u32 a = selectionEnd;
    s32 lo, hi;
    if (a < b) {
        lo = a;
        hi = b;
    } else {
        lo = b;
        hi = a;
    }
    setCaret(lo);
    for (; hi < 12; lo++, hi++) {
        codeDigits[lo] = codeDigits[hi];
    }
    for (; lo < 12; lo++) {
        codeDigits[lo] = 10;
    }
    setFlags(8);
}

BOOL FriendCodeMenu::insertDigit(u8 v) {
    s32 i;
    if (caretPos == 12 && selectionEnd == selectionAnchor) {
        Snd_PlaySe(0x34);
        return FALSE;
    }
    u32 b = selectionAnchor;
    u32 a = selectionEnd;
    if (a == b && codeDigits[11] != 10) {
        Snd_PlaySe(0x34);
        return FALSE;
    }
    if (a != b) {
        deleteSelection();
    }
    for (i = 11; i > caretPos; i--) {
        codeDigits[i] = codeDigits[i - 1];
    }
    codeDigits[caretPos] = v;
    setCaret(caretPos + 1);
    setFlags(8);
    return TRUE;
}

s32 FriendCodeMenu::getCodeLength() {
    s32 i;
    for (i = 0; i < 12; i++) {
        if (codeDigits[i] == 10) {
            return i;
        }
    }
    return 12;
}

void FriendCodeMenu::drawCodeDigits() {
    s32 i;
    u16 *p = codeScreen;
    p += 0xe4;
    for (i = 0; i < 12; p += 2, i++) {
        u32 c = codeDigits[i];
        if (c == 10) {
            p[0] = (p[0] & 0xfc00) | 0x176;
            p[1] = (p[1] & 0xfc00) | 0x176;
            p[0x20] = (p[0x20] & 0xfc00) | 0x176;
            p[0x21] = (p[0x21] & 0xfc00) | 0x176;
        } else {
            u32 v = c * 4 + 0x84;
            p[0] = (p[0] & 0xfc00) | v;
            p[1] = (p[1] & 0xfc00) | (v + 1);
            p[0x20] = (p[0x20] & 0xfc00) | (v + 2);
            p[0x21] = (p[0x21] & 0xfc00) | (v + 3);
        }
    }
    if (((MenuBottomButtonsBody *)&bottomButtons)->isButtonDisabled(6)) {
        if (codeDigits[11] != 10) {
            ((MenuBottomButtonsBody *)&bottomButtons)->enableButton(6);
        }
    } else if (codeDigits[11] == 10) {
        ((MenuBottomButtonsBody *)&bottomButtons)->disableButton(6);
    }
}

void FriendCodeMenu::drawSelection() {
    BgScreen_SetRectPalette(codeScreen, 4, 7, 0x1b, 8, 4);
    u32 b = selectionAnchor;
    u32 a = selectionEnd;
    if (a != b) {
        u32 lo, hi;
        if (a > b) {
            lo = b;
            hi = a;
        } else {
            lo = a;
            hi = b;
        }
        lo = lo * 2 + 4;
        hi = hi * 2 + 3;
        BgScreen_SetRectPalette(codeScreen, lo, 7, hi, 8, 8);
    }
}

void FriendCodeMenu::flushScreens() {
    if (testFlags(8)) {
        drawCodeDigits();
        clearFlags(8);
        setFlags(4);
    }
    if (testFlags(0x10)) {
        drawSelection();
        clearFlags(0x10);
        setFlags(4);
    }
    if (testFlags(2)) {
        if (screenTasks[0].requestScreen(keypadScreen, 4, 0x800, 0)) {
            clearFlags(2);
        }
    }
    if (testFlags(4)) {
        if (screenTasks[1].requestScreen(codeScreen, 6, 0x800, 0)) {
            clearFlags(4);
        }
    }
}

BOOL FriendCodeMenu::pressCursorKey() {
    resetKeyPalettes();
    pressedKey = cursorSlot;
    highlightKey(pressedKey);
    repeatTimer = 0xd;
    highlightTimer = 5;
    return applyKey(1);
}

void FriendCodeMenu::stopKeyRepeat() { repeatTimer = 0; }

BOOL FriendCodeMenu::tickKeyRepeat() {
    if (repeatTimer != 0) {
        repeatTimer = repeatTimer - 1;
        if (repeatTimer == 0) {
            repeatTimer = 2;
            return TRUE;
        }
    }
    return FALSE;
}

void FriendCodeMenu::resetKeyPalettes() {
    BgScreen_SetRectPalette(keypadScreen, 9, 0xc, 0x15, 0x14, 2);
    unhighlightKey(0xb);
    unhighlightKey(0xa);
    setFlags(2);
}

void FriendCodeMenu::setKeyPalette(s32 idx, u32 to) {
    s32 m = idx % 3;
    u32 x0 = sKeyColumnX[m];
    u32 x1;
    if (m == 0) {
        x1 = x0 + 4;
    } else {
        x1 = x0 + 3;
    }
    u32 y0 = sKeyRowY[idx];
    BgScreen_SetRectPalette(keypadScreen, x0, y0, x1, y0 + 1, to);
    setFlags(2);
}

void FriendCodeMenu::highlightKey(s32 idx) { setKeyPalette(idx, 3); }

void FriendCodeMenu::unhighlightKey(s32 idx) {
    u32 to;
    if ((u8)(idx + 0xf6) <= 1) {
        to = 1;
    } else {
        to = 2;
    }
    setKeyPalette(idx, to);
}

BOOL FriendCodeMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void FriendCodeMenu::setFlags(u32 m) { flags = flags | m; }

void FriendCodeMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" const u8 sKeyDigits[12] = {7, 8, 9, 4, 5, 6, 1, 2, 3, 0, 0, 0};

extern "C" const u8 sFriendCodeTouchKeyMap[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

extern "C" const s32 sFriendCodeCursorYTable[12] = {0x68, 0x68, 0x68, 0x78, 0x78, 0x78, 0x88, 0x88, 0x88, 0x98, 0x98, 0x98};

extern "C" const u32 sKeyRowY[12] = {0xc, 0xc, 0xc, 0xe, 0xe, 0xe, 0x10, 0x10, 0x10, 0x12, 0x12, 0x12};

extern "C" ProcProfile sFriendCodeMenuProfile = {(void *(*)())FriendCodeMenu_Create, 0xb4, 0xb8};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov133_022936c0) {
    HOST_OVERLAY_VAR(sFriendCodeKeySeIds),
    HOST_OVERLAY_VAR(sCaretCells),
    HOST_OVERLAY_VAR(sFriendCodeMenuProfile),
    HOST_OVERLAY_VARS_END
};

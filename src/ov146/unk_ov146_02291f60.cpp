#include "types.h"
#include "host_overlay_vars.h"
#include "Unk_020d8c7c.h"
#include "talk/MsgStringBase.h"
#include "net/Net.h"
#include "talk/MsgStringAttr.h"
#include "talk/EncodedStringBase.h"
#include "talk/MsgString.h"
#include "menu/MenuProc.h"
#include "talk/EncodedString.h"
#include "talk/MsgString9C.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "talk/EncodedString8B.h"
#include "menu/MenuTitleBalloon.h"
#include "menu/MenuScrollKnob.h"
#include "menu/MenuCursor.h"
#include "sys/ProcProfile.h"
#include "menu/MenuLauncher.h"
#include "ui/HandCursor.h"
#include "ui/LabelBalloon.h"
#include "ui/ScrollKnob.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov146/unk_ov146_02291f60.h"


class WfcFriendListMenu;
typedef void (WfcFriendListMenu::*Unk_ov146_02294080_Fn)();





class MsgString;






extern "C" {
extern u16 gPad[];

void MIi_CpuCopy16(void *dst, void *src, u32 n);
void MIi_CpuClear16(u32 v, void *dst, u32 n);
void MI_CpuFill8(void *dst, s32 v, s32 n);
void MI_CpuCopy8(const void *src, void *dst, s32 n);
BOOL EncodedString_SetRaw(void *dst, const void *src, s32 n);
s32 _s32_div_f(s32 a, s32 b);
BOOL Math_StepS32(s32 *p, s32 target, s32 step);
}






class WfcFriendListMenu : public MenuProc {
public:
    WfcFriendListMenu()
        : cursor(), textPool(), vramTasks(), title(), knob() {}

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
    void updateRowColors();
    void fadeRowColor(s32 a, s32 t, s32 b);
    void cancelVramTasks();
    void targetFromCursorY();
    void targetLastVisibleRow();
    BOOL moveTargetByKeys(u32 pad);
    BOOL decideTarget(u32 k);
    void syncKnobFromScroll();
    void syncScrollFromKnob();
    void placeKnob();
    BOOL finishKnobRelease();
    void moveKnobByKeys();
    void releaseKnob();
    void dragKnob(s32 v, BOOL c);
    BOOL tryGrabKnob(s32 x, s32 y);
    BOOL stepScroll();
    void buildListScreen();
    void setScroll(s32 v);
    void flushVram();
    BOOL isFriendSelectable(s32 idx);
    BOOL isFriendOnline(NetWifiFriendStatus *p);
    BOOL rebuildOrder();
    void refreshFriendStatus();
    void initFriendStatus();
    NetWifiFriends *getFriendList();
    void drawStaticLabelsOnce();
    void drawStaticLabels();
    void renderRows();
    void resetTextPool();
    LabelString *allocText();
    void startCursorRelease();
    void startCursorPress();
    void setCursorIdle();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getTargetY();
    s32 getTargetX();
    void snapCursorToTarget();
    void decideQuit();
    void decideConfirm();
    void enterInputMode();
    void enterButtonMode();
    void enterTouchMode();
    void execExitDelay();
    void execCursorRelease();
    void execCursorPress();
    void execCursorMove();
    void execKnobRelease();
    void execKnobKeys();
    void execButtons();
    void execJumpKnob();
    void execDragKnob();
    void execTouch();
    void loadObjGraphics();
    void loadBgGraphics();
    void setupLayers();
    void updateList();
    void beginFrame();
    void endFrame();
    void beginMainFrame();
    void releaseResources();
    void initState();
    void applySlide();
    void execSlideOut();
    void startClose();
    void execSlideIn();
    void enterOpen();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideOffsetY;
    /* 0x098 */ s32 knobPos;
    /* 0x09c */ s32 knobGrabOffset;
    /* 0x0a0 */ s32 knobTickPos;
    /* 0x0a4 */ s32 scrollY;
    /* 0x0a8 */ s32 scrollTargetY;
    /* 0x0ac */ u16 flags;
    /* 0x0ae */ s16 topRow;
    /* 0x0b0 */ u8 confirmButtonPal;
    /* 0x0b1 */ u8 quitButtonPal;
    /* 0x0b2 */ u8 cursorTarget;
    /* 0x0b3 */ u8 returnState;
    /* 0x0b4 */ u8 numTextsUsed;
    /* 0x0b5 */ u8 staticLabelsDrawn;
    /* 0x0b6 */ u8 numOnline;
    /* 0x0b7 */ u8 iconAnim[3];
    /* 0x0ba */ u8 exitDelay;
    /* 0x0bb */ u8 selectedFriend;
    /* 0x0bc */ u8 rowFriends[7];
    /* 0x0c3 */ u8 rowColorKeys[7];
    /* 0x0ca */ u8 listStatus[0xea - 0xca];
    /* 0x0ea */ u8 listOrder[0x20];
    /* 0x10a */ u8 friendFade[0x20];
    /* 0x12a */ NetWifiFriendStatus friendRecords[0x20];
    /* 0x38a */ u16 listScreenSrc[0x400];
    /* 0xb8a */ u16 listScreen[0x400];
    /* 0x138a */ u16 rowPaletteSrc[16];
    /* 0x13aa */ u16 rowPalette[16];
    /* 0x13ca */ u8 unk_13ca[2];
    /* 0x13cc */ MenuCursorBuf0 cursor;
    /* 0x1430 */ LabelString textPool[0x14];
    /* 0x1930 */ BgVramTask vramTasks[2];
    /* 0x1978 */ MenuTitleBalloon title;
    /* 0x1a34 */ MenuScrollKnob knob;
};



static inline BOOL Unk_ov146_022933bc_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

extern "C" WfcFriendListMenu *WfcFriendListMenu_Create() { return new WfcFriendListMenu(); }

BOOL WfcFriendListMenu::onCreate() {
    initState();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL WfcFriendListMenu::onDelete() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->onChildClosed();
    releaseResources();
    return TRUE;
}
extern "C" ProcProfile sWfcFriendListMenuProfile;

extern "C" GXOamAttr data_ov146_02293e18[1] = {
    {0x804040d8, 0x1c0, 2, 0xc, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293e98[2] = {
    {0x0198003b, 0x1d4, 1, 0xd, 0x0},
    {0x01a0403b, 0x1f4, 1, 0xd, 0xffff},
};

BOOL WfcFriendListMenu::onDraw() {
    s32 i;
    s32 y;
    s32 y2;
    s32 idx;
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)(&cursor))->drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    knob.draw();
    ((LabelBalloon *)(&title))->setPos(0, slideOffsetY);
    title.draw();
    y = slideOffsetY + 0x60;
    y2 = y - (scrollY & 0xf);
    for (i = 0; i < 7; y2 += 0x10, i++) {
        idx = i + topRow;
        if (idx < 0x20 && selectedFriend < 0x20 && selectedFriend == listOrder[idx]) {
            Oam_DrawCell(1, sWfcRowCellsSelected, 0x80, y2, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            Oam_DrawCell(1, sWfcRowCells, 0x80, y2, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        idx = i + topRow;
        if (idx < 0x20) {
            GXOamAttr *tb[5] = {0, data_ov146_02293e18, data_ov146_02293e78, data_ov146_02293e20, data_ov146_02293e48};
            GXOamAttr *h = tb[listStatus[idx]];
            if (h != 0) {
                Oam_DrawCell(1, h, 0x80, y2, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
            }
        }
    }
    Oam_DrawCell(1, sWfcFrameCells, 0x80, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, sWfcQuitButtonCells, 0x80, y, quitButtonPal, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, sWfcConfirmButtonCells, 0x80, y, confirmButtonPal, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, data_ov146_02293e98, 0x80, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    GXOamAttr *tc[5] = {data_ov146_02293f90, data_ov146_02293ed0, data_ov146_02293ef0, data_ov146_02293f10, data_ov146_02293f30};
    if (iconAnim[0] != 0) {
        iconAnim[0] = *(volatile u8 *)&iconAnim[0] - 1;
    } else {
        iconAnim[1] = iconAnim[1] + 1;
        if (iconAnim[1] >= 5) {
            iconAnim[1] = 0;
        }
        iconAnim[0] = 10;
    }
    Oam_DrawCell(1, tc[iconAnim[1]], 0x80, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    return TRUE;
}
extern "C" GXOamAttr sWfcRowCellsSelected[7] = {
    {0x403c40e6, 0xc6, 2, 0x5, 0x0},
    {0x402040e6, 0xc6, 2, 0x5, 0x0},
    {0x419400d7, 0x86, 2, 0x5, 0x0},
    {0x400040e6, 0xc6, 2, 0x5, 0x0},
    {0x41d840e6, 0xc6, 2, 0x5, 0x0},
    {0x41b840e6, 0xc6, 2, 0x5, 0x0},
    {0x419840e6, 0xc6, 2, 0x5, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293e48[1] = {
    {0x804040d8, 0x1cc, 2, 0xd, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293f90[4] = {
    {0x0006003a, 0x1d5, 1, 0xc, 0x0},
    {0x01ff003a, 0x1d5, 1, 0xc, 0x0},
    {0x01f8003a, 0x1d5, 1, 0xc, 0x0},
    {0x01f1003a, 0x1d5, 1, 0xd, 0xffff},
};

extern "C" ProcProfile sWfcFriendListMenuProfile = {(void *(*)())WfcFriendListMenu_Create, 0xbb, 0xbf};

extern "C" GXOamAttr sWfcRowCells[6] = {
    {0x403c40e6, 0xe6, 2, 0x4, 0x0},
    {0x402040e6, 0xe6, 2, 0x4, 0x0},
    {0x400040e6, 0xe6, 2, 0x4, 0x0},
    {0x41d840e6, 0xe6, 2, 0x4, 0x0},
    {0x41b840e6, 0xe6, 2, 0x4, 0x0},
    {0x419840e6, 0xe6, 2, 0x4, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293f10[4] = {
    {0x0006003a, 0x1d5, 1, 0xd, 0x0},
    {0x01ff003a, 0x1d5, 1, 0xd, 0x0},
    {0x01f8003a, 0x1d5, 1, 0xd, 0x0},
    {0x01f1003a, 0x1d5, 1, 0xd, 0xffff},
};

BOOL WfcFriendListMenu::execTransition() {
    static Unk_ov146_02294080_Fn tbl[4] = {
        &WfcFriendListMenu::enterOpen,
        &WfcFriendListMenu::execSlideIn,
        &WfcFriendListMenu::startClose,
        &WfcFriendListMenu::execSlideOut};
    beginFrame();
    (this->*tbl[transitionState])();
    updateList();
    return TRUE;
}
extern "C" GXOamAttr sWfcConfirmButtonCells[4] = {
    {0x8011404a, 0x8d, 1, 0x8, 0x0},
    {0x4031004a, 0x91, 1, 0x8, 0x0},
    {0x80270043, 0x82, 1, 0x8, 0x0},
    {0x800b0043, 0x80, 1, 0x8, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293e78[1] = {
    {0x804040d8, 0x1c4, 2, 0xc, 0xffff},
};

void WfcFriendListMenu::runMainState() {
    static Unk_ov146_02294080_Fn tbl[10] = {
        &WfcFriendListMenu::execTouch,
        &WfcFriendListMenu::execDragKnob,
        &WfcFriendListMenu::execJumpKnob,
        &WfcFriendListMenu::execButtons,
        &WfcFriendListMenu::execKnobKeys,
        &WfcFriendListMenu::execKnobRelease,
        &WfcFriendListMenu::execCursorMove,
        &WfcFriendListMenu::execCursorPress,
        &WfcFriendListMenu::execCursorRelease,
        &WfcFriendListMenu::execExitDelay};
    (this->*tbl[mainState])();
}

BOOL WfcFriendListMenu::execMain() {
    beginMainFrame();
    runMainState();
    endFrame();
    return TRUE;
}

BOOL WfcFriendListMenu::execPhase3() { return TRUE; }

BOOL WfcFriendListMenu::execPhase4() { return TRUE; }

BOOL WfcFriendListMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void WfcFriendListMenu::enterOpen() {
    setupLayers();
    loadBgGraphics();
    rebuildOrder();
    setScroll(0);
    scrollTargetY = 0;
    loadObjGraphics();
    beginSubSlideIn(0xa, 4, 0, 0x28);
    Gfx2d_ShowLayer(6);
    Gfx2d_ShowLayer(4);
    applySlide();
    setFlags(1);
    setTransitionState(1);
}

void WfcFriendListMenu::execSlideIn() {
    if (stepSlideIn(0)) {
        setPhase(2);
        enterInputMode();
    } else {
        drawStaticLabelsOnce();
    }
    applySlide();
}

void WfcFriendListMenu::startClose() {
    ((MenuLauncher *)(ProcBase_GetParent(this)))->setNextRequest(0x44, 1);
    beginSubSlideOut(0xa, 0, 0, 0x28);
    applySlide();
    setTransitionState(3);
}

void WfcFriendListMenu::execSlideOut() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        Gfx2d_ResetLayer(4);
        setPhase(5);
    } else {
        applySlide();
    }
}

void WfcFriendListMenu::applySlide() {
    applySlideOffset(6, 0, 0);
    applySlideOffset(4, 0, 0x38 - scrollY);
    slideOffsetY = getSlideOffsetY();
    placeKnob();
}

void WfcFriendListMenu::initState() {
    s32 i;
    s32 j;
    flags = 0;
    cursorTarget = 3;
    confirmButtonPal = 9;
    quitButtonPal = 8;
    ((MenuTitleBalloon *)(&title))->hideNow();
    ((MenuTitleBalloon *)(&title))->showText(0x7f, 0x90, 0x10);
    ((LabelBalloon *)(&title))->showLayer2();
    staticLabelsDrawn = 0;
    ((MenuScrollKnob *)(&knob))->show();
    for (i = 0; i < 7; i++) {
        rowFriends[i] = 0x21;
        rowColorKeys[i] = 0xff;
    }
    for (j = 0; j < 0x20; j++) {
        listOrder[j] = 0x20;
        friendFade[j] = 0;
    }
    initFriendStatus();
    numOnline = 0x21;
    iconAnim[0] = 10;
    iconAnim[1] = 0;
    iconAnim[2] = 10;
    selectedFriend = 0x20;
}

void WfcFriendListMenu::releaseResources() {
    resetTextPool();
    cancelVramTasks();
}

void WfcFriendListMenu::beginMainFrame() {
    beginFrame();
    cursor.update();
}

void WfcFriendListMenu::endFrame() { updateList(); }

void WfcFriendListMenu::beginFrame() {
    resetTextPool();
    cancelVramTasks();
    knob.update();
}

void WfcFriendListMenu::updateList() {
    if (!testFlags(0x40)) {
        refreshFriendStatus();
        if (rebuildOrder()) {
            setFlags(4);
        }
        if (isFriendSelectable(selectedFriend)) {
            confirmButtonPal = 8;
        } else {
            confirmButtonPal = 9;
        }
    }
    stepScroll();
    if (testFlags(4)) {
        renderRows();
        clearFlags(4);
    }
    updateRowColors();
    flushVram();
    ((MenuScrollKnob *)(&knob))->updateRelease();
}

void WfcFriendListMenu::setupLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
}

void WfcFriendListMenu::loadBgGraphics() {
    void *p = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/wfc/bg.bch", p, 6, 0x11, 0x11, 0x5c);
    Gfx2d_LoadPaletteFile("menu/wfc/bg.bpl", p, 6, 1, 1, 8);
    File_LoadToBuffer("menu/wfc/bg7.bpl", rowPaletteSrc, 0x20);
    MIi_CpuCopy16(rowPaletteSrc, rowPalette, 0x20);
    Gfx2d_LoadScreenFile("menu/wfc/a_bg.bsc", p, 6);
    File_LoadToBuffer("menu/wfc/b_bg.bsc", listScreenSrc, 0x800);
    BgScreen_SetRectPalette(listScreenSrc, 5, 7, 0xe, 0x14, 7);
    BgScreen_SetRectPalette(listScreenSrc, 0x10, 7, 0x17, 0x14, 7);
}

void WfcFriendListMenu::loadObjGraphics() {
    void *p = gCurrentHeap;
    Gfx2d_LoadCharFile("menu/wfc/obj0.bch", p, 8, 0x80, 0x80, 0xff);
    Gfx2d_LoadCharFile("menu/wfc/obj1.bch", p, 8, 0x160, 0x160, 0x1ff);
    Gfx2d_LoadPaletteFile("menu/wfc/obj.bpl", p, 8, 4, 4, 0xd);
}

void WfcFriendListMenu::execTouch() {
    s32 x;
    s32 y;
    if (checkSwitchToButtons(1)) {
        enterButtonMode();
        return;
    }
    if (Unk_ov146_022933bc_Both()) {
        x = gTouchCurX;
        y = gTouchCurY;
        if (y >= 0xa9 && y <= 0xbc && x >= 0x39) {
            if (x < 0x75) {
                decideQuit();
                return;
            }
            if (x >= 0x8b && x < 0xc7 && confirmButtonPal == 8) {
                decideConfirm();
                return;
            }
        }
        if (x >= 0x18 && x <= 0xe0 && y >= 0x38 && y < 0x98) {
            s32 idx = topRow + ((y - (0x38 - (scrollTargetY & 0xf))) >> 4);
            if (idx < 0x20) {
                x = listOrder[idx];
                if (isFriendSelectable(x)) {
                    if (selectedFriend != x) {
                        selectedFriend = x;
                        Snd_PlaySe(0x29);
                    }
                }
            }
        } else if (tryGrabKnob(x, y)) {
            setMainState(1);
        } else if (x >= 0xe6 && x <= 0xee && y >= 0x38 && y <= 0x88) {
            ((MenuScrollKnob *)(&knob))->grab();
            setMainState(2);
        }
    }
}

void WfcFriendListMenu::execDragKnob() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 0);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void WfcFriendListMenu::execJumpKnob() {
    if (gTouchHeld != 0) {
        dragKnob(gTouchCurY, 1);
    } else {
        releaseKnob();
        setMainState(0);
    }
}

void WfcFriendListMenu::execButtons() {
    if (checkSwitchToTouch()) {
        enterTouchMode();
    } else if (moveTargetByKeys(takeRepeatedKeys())) {
        moveCursorToTarget();
    } else {
        u32 k = gPad[1];
        if (k & 1) {
            startCursorPress();
        } else if (k & 2) {
            hideCursor();
            decideQuit();
        }
    }
}

void WfcFriendListMenu::execKnobKeys() {
    u32 a;
    u32 b;
    if (gPad[0] & 1) {
        moveKnobByKeys();
        a = getTargetX();
        b = getTargetY();
        ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    } else {
        releaseKnob();
        setMainState(5);
    }
}

void WfcFriendListMenu::execKnobRelease() {
    u32 a;
    u32 b;
    if (finishKnobRelease()) {
        setMainState(3);
        startCursorRelease();
    }
    a = getTargetX();
    b = getTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
}

void WfcFriendListMenu::execCursorMove() {
    if (!((MenuCursorBase *)(&cursor))->isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void WfcFriendListMenu::execCursorPress() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        if (!decideTarget(cursorTarget)) {
            setMainState(3);
            startCursorRelease();
        }
    }
}

void WfcFriendListMenu::execCursorRelease() {
    if (((HandCursor *)(&cursor))->isAnimDone()) {
        setCursorIdle();
        setMainState(returnState);
        if (testFlags(0x10)) {
            clearFlags(0x10);
            cursorTarget = 1;
            moveCursorToTarget();
        }
    }
}

void WfcFriendListMenu::execExitDelay() {
    if (exitDelay != 0) {
        exitDelay = *(volatile u8 *)&exitDelay - 1;
    } else {
        hideCursor();
        setPhase(1);
    }
}

void WfcFriendListMenu::enterTouchMode() {
    hideCursor();
    setMainState(0);
}

void WfcFriendListMenu::enterButtonMode() {
    snapCursorToTarget();
    restartKeyRepeat();
    setMainState(3);
}

void WfcFriendListMenu::enterInputMode() {
    if (MenuCtrl_IsTouch()) {
        enterTouchMode();
    } else {
        enterButtonMode();
    }
}

void WfcFriendListMenu::decideConfirm() {
    MenuCtrl_SetResult(1);
    MenuCtrl_SetIndex(selectedFriend);
    confirmButtonPal = 10;
    setFlags(0x40);
    exitDelay = 5;
    setTransitionState(2);
    setMainState(9);
    Snd_PlaySe(0x27);
}

void WfcFriendListMenu::decideQuit() {
    MenuCtrl_SetResult(0);
    quitButtonPal = 10;
    exitDelay = 5;
    setTransitionState(2);
    setMainState(9);
    Snd_PlaySe(0x28);
}

void WfcFriendListMenu::snapCursorToTarget() {
    s32 a, b;
    if (cursorTarget == 3) {
        u32 t = scrollTargetY & 0xf;
        if (t != 0) {
            scrollTargetY = *(volatile s32 *)&scrollTargetY - t;
        }
    }
    a = getTargetX();
    b = getTargetY();
    ((MenuCursorBase *)(&cursor))->warpTo(a, b);
    if (cursorTarget == 2) {
        ((MenuCursor *)(&cursor))->setAnimIfChanged(1);
    } else {
        ((MenuCursor *)(&cursor))->setAnimIfChanged(7);
    }
    setCursorIdle();
}

s32 WfcFriendListMenu::getTargetX() {
    u32 m = cursorTarget;
    if (m >= 3 && m <= 9) {
        return 0x1c;
    }
    switch (m) {
    case 0:
        return 0x47;
    case 1:
        return 0x99;
    case 2:
        return ((MenuScrollKnob *)(&knob))->getGripX();
    default:
        return 0x80;
    }
}

s32 WfcFriendListMenu::getTargetY() {
    u32 m = cursorTarget;
    if (m >= 3 && m <= 9) {
        return ((m - 3) << 4) + 0x40 - (scrollTargetY & 0xf);
    }
    switch (m) {
    case 0:
    case 1:
        return 0xad;
    case 2:
        return ((MenuScrollKnob *)(&knob))->getGripY();
    default:
        return 0x60;
    }
}

void WfcFriendListMenu::hideCursor() {
    ((MenuCursor *)(&cursor))->setAnimIfChanged(0);
    cursor.update();
}

void WfcFriendListMenu::moveCursorToTarget() {
    s32 a, b;
    if (cursorTarget == 2) {
        ((MenuCursor *)(&cursor))->switchToAnim01();
    } else {
        ((MenuCursor *)(&cursor))->switchToAnim07();
    }
    a = getTargetX();
    b = getTargetY();
    moveCursorTo(a, b);
}

void WfcFriendListMenu::moveCursorTo(s32 a, s32 b) {
    if (testFlags(0x20)) {
        ((MenuCursorBase *)(&cursor))->moveToEase(a, b, 3, 0);
        clearFlags(0x20);
    } else {
        ((MenuCursorBase *)(&cursor))->moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(6);
}

void WfcFriendListMenu::setCursorIdle() {
    ((MenuCursorBase *)(&cursor))->setPoseIdle();
    cursor.update();
}

void WfcFriendListMenu::startCursorPress() {
    ((MenuCursor *)(&cursor))->setPosePress();
    setMainState(7);
}

void WfcFriendListMenu::startCursorRelease() {
    ((MenuCursorBase *)(&cursor))->setPoseRelease();
    returnState = mainState;
    setMainState(8);
}

LabelString *WfcFriendListMenu::allocText() {
    if (numTextsUsed >= 0x14) {
        return &textPool[0x13];
    }
    numTextsUsed = *(volatile u8 *)&numTextsUsed + 1;
    return &textPool[numTextsUsed - 1];
}

void WfcFriendListMenu::resetTextPool() {
    s32 i;
    numTextsUsed = 0;
    for (i = 0; i < 0x14; i++) {
        textPool[i].destroyLabel();
    }
}
extern "C" GXOamAttr data_ov146_02293e20[1] = {
    {0x804040d8, 0x1c8, 2, 0xc, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293ed0[4] = {
    {0x0006003a, 0x1d5, 1, 0xc, 0x0},
    {0x01ff003a, 0x1d5, 1, 0xc, 0x0},
    {0x01f8003a, 0x1d5, 1, 0xd, 0x0},
    {0x01f1003a, 0x1d5, 1, 0xd, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293ef0[4] = {
    {0x0006003a, 0x1d5, 1, 0xc, 0x0},
    {0x01ff003a, 0x1d5, 1, 0xd, 0x0},
    {0x01f8003a, 0x1d5, 1, 0xd, 0x0},
    {0x01f1003a, 0x1d5, 1, 0xd, 0xffff},
};

extern "C" GXOamAttr data_ov146_02293f30[4] = {
    {0x0006003a, 0x1d5, 1, 0xc, 0x0},
    {0x01ff003a, 0x1d5, 1, 0xc, 0x0},
    {0x01f8003a, 0x1d5, 1, 0xc, 0x0},
    {0x01f1003a, 0x1d5, 1, 0xc, 0xffff},
};

extern "C" GXOamAttr sWfcFrameCells[12] = {
    {0x81a800a0, 0x17b, 1, 0xb, 0x0},
    {0x41c880a0, 0x17f, 1, 0xb, 0x0},
    {0x41a840c0, 0x1fb, 1, 0xb, 0x0},
    {0x01c800c0, 0x1ff, 1, 0xb, 0x0},
    {0x41ac40cd, 0xcd, 1, 0x5, 0x0},
    {0x01cc40cd, 0xd1, 1, 0x5, 0x0},
    {0x400440cd, 0xed, 1, 0x5, 0x0},
    {0x002440cd, 0xf1, 1, 0x5, 0x0},
    {0x901840cc, 0x88, 1, 0x5, 0x0},
    {0x800040cc, 0x88, 1, 0x5, 0x0},
    {0x91c040cc, 0x88, 1, 0x5, 0x0},
    {0x81a840cc, 0x88, 1, 0x5, 0xffff},
};

EncodedString8B WfcFriendListMenu_renderRows_sa;
u8 WfcFriendListMenu_renderRows_sa_init;
MsgString9C WfcFriendListMenu_renderRows_sb;
u8 WfcFriendListMenu_renderRows_sb_init;
void WfcFriendListMenu::renderRows() {
    if (!WfcFriendListMenu_renderRows_sa_init) {
        HOST_STATIC_CONSTRUCT(WfcFriendListMenu_renderRows_sa);
        WfcFriendListMenu_renderRows_sa_init = 1;
    }
    if (!WfcFriendListMenu_renderRows_sb_init) {
        HOST_STATIC_CONSTRUCT(WfcFriendListMenu_renderRows_sb);
        WfcFriendListMenu_renderRows_sb_init = 1;
    }
    LabelString *w1;
    LabelString *w2;
    s32 j;
    s32 idx;
    s32 col;
    getFriendList();
    idx = topRow;
    col = idx % 7;
    for (j = 0; j < 7; j++) {
        if (idx >= 0x20) {
            rowFriends[col] = 0x20;
        } else {
            s32 e = listOrder[idx];
            if (e == rowFriends[col]) {
                w1 = 0;
            } else if (e >= 0x20) {
                w1 = allocText();
                w1->clear();
                w2 = allocText();
                w2->clear();
                rowFriends[col] = 0x20;
            } else {
                rowFriends[col] = e;
                w1 = allocText();
                EncodedString_SetRaw(&WfcFriendListMenu_renderRows_sa, friendRecords[e].statusString + 8, 8);
                WfcFriendListMenu_renderRows_sb.fromEncoded(&WfcFriendListMenu_renderRows_sa, 0, 0);
                String_SetSlot(0, &WfcFriendListMenu_renderRows_sb);
                String_Load2dMenu(w1, 0x66);
                w2 = allocText();
                String_FromEncodedBytes(w2, (u8 *)friendRecords[e].statusString, 8);
            }
            if (w1) {
                w1->createLabel(4, col * 0x14 + 0x11e, 10, 0xe - col, 0xf, 0);
                w1->redrawAligned(0, 0);
                w2->createLabel(4, col * 0x10 + 0x1d2, 8, 0xe - col, 0xf, 0);
                w2->redrawAligned(0, 0);
            }
        }
        idx++;
        col++;
        if (col >= 7) {
            col = 0;
        }
    }
}

void WfcFriendListMenu::drawStaticLabels() {
    LabelString *w;
    w = allocText();
    String_Load2dMenu(w, 0x65);
    w->createLabel(8, 0x93, 6, 0xf, 0, 0);
    w->redrawAligned(1, 0);
    w = allocText();
    String_Load2dMenu(w, 0xc2);
    w->createLabel(8, 0x8d, 6, 0xf, 0, 0);
    w->redrawAligned(1, 0);
    w = allocText();
    String_Load2dMenu(w, 0xc1);
    w->createLabel(8, 0x99, 6, 0xf, 0, 0);
    w->redrawAligned(1, 0);
    w = allocText();
    String_Load2dMenu(w, 0xbc);
    w->createSmallLabel(8, 0xcd, 6, 0xe, 0, 0);
    w->redrawAligned(1, 0);
    w = allocText();
    String_Load2dMenu(w, 0xbd);
    w->createSmallLabel(8, 0xed, 6, 0xe, 0, 0);
    w->redrawAligned(1, 0);
}

void WfcFriendListMenu::drawStaticLabelsOnce() {
    if (staticLabelsDrawn == 0) {
        drawStaticLabels();
        staticLabelsDrawn = staticLabelsDrawn + 1;
    }
}

NetWifiFriends *WfcFriendListMenu::getFriendList() { return (NetWifiFriends *)Net_GetWifiFriendList(); }

void WfcFriendListMenu::initFriendStatus() {
    s32 i;
    NetWifiFriends *tbl;
    s32 z;
    MI_CpuFill8(friendRecords, 0, sizeof(friendRecords));
    tbl = getFriendList();
    i = 0;
    z = 0;
    do {
        NetWifiFriendStatus *rec = &tbl->status[i];
        if (isFriendOnline(rec)) {
            MI_CpuCopy8(rec, &friendRecords[i], sizeof(NetWifiFriendStatus));
            friendFade[i] = 0x14;
        } else {
            friendFade[i] = z;
        }
        i++;
    } while (i < 0x20);
}

void WfcFriendListMenu::refreshFriendStatus() {
    NetWifiFriends *tbl = getFriendList();
    s32 i;
    s32 cnt = 0;
    for (i = 0; i < 0x20; i++) {
        if (isFriendOnline(&tbl->status[i])) {
            if (friendRecords[i].status == 6) {
                if (friendFade[i] < 0x14) {
                    friendFade[i]++;
                }
            } else {
                friendFade[i] = 0;
                MI_CpuCopy8(&tbl->status[i], &friendRecords[i], sizeof(NetWifiFriendStatus));
            }
            cnt++;
        } else {
            if (friendRecords[i].status == 6) {
                if (friendFade[i] != 0) {
                    friendFade[i]--;
                } else {
                    friendRecords[i].status = 0;
                }
            }
        }
    }
    if (cnt != numOnline) {
        u8 buf[3];
        LabelString *w;
        numOnline = cnt;
        w = allocText();
        if (numOnline < 10) {
            buf[0] = numOnline + 0x35;
            buf[1] = 0;
            buf[2] = 0;
        } else {
            buf[0] = numOnline / 10 + 0x35;
            buf[1] = numOnline % 10 + 0x35;
            buf[2] = 0;
        }
        String_FromEncodedBytes(w, buf, 3);
        w->createSmallLabel(8, 0x1f4, 2, 9, 0, 1);
        w->redrawAligned(0, 0);
    }
}

BOOL WfcFriendListMenu::rebuildOrder() {
    s32 i;
    s32 cnt = 0;
    BOOL changed = FALSE;
    NetWifiFriends *tbl;
    tbl = getFriendList();
    for (i = 0; i < 0x20; i++) {
        if (friendRecords[i].status == 6) {
            if (i != listOrder[cnt]) {
                changed = TRUE;
                listOrder[cnt] = i;
            }
            if (isFriendOnline(&tbl->status[i])) {
                friendRecords[i].c = tbl->status[i].c;
            }
            listStatus[cnt] = tbl->status[i].c;
            cnt++;
        }
    }
    for (; cnt < 0x20; cnt++) {
        if (listOrder[cnt] != 0x20) {
            changed = TRUE;
            listOrder[cnt] = 0x20;
            listStatus[cnt] = 0;
        }
    }
    return changed;
}

BOOL WfcFriendListMenu::isFriendOnline(NetWifiFriendStatus *p) {
    if (p->status == 6 && p->statusString[0] != 0) {
        return TRUE;
    }
    return FALSE;
}

BOOL WfcFriendListMenu::isFriendSelectable(s32 idx) {
    if (idx >= 0x20) {
        return FALSE;
    }
    NetWifiFriends *g = getFriendList();
    if (isFriendOnline(&g->status[idx])) {
        if (g->status[idx].c < 4) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

void WfcFriendListMenu::flushVram() {
    if (testFlags(2)) {
        if (vramTasks[0].requestScreen(listScreen, 4, 0x800, 0)) {
            clearFlags(2);
        }
    }
    if (testFlags(8)) {
        if (vramTasks[1].requestPalette(rowPalette, 4, 7)) {
            clearFlags(8);
        }
    }
}

void WfcFriendListMenu::setScroll(s32 v) {
    scrollY = v;
    Gfx2d_SetLayerOffset(4, 0, scrollY - 0x38);
    topRow = v >> 4;
    buildListScreen();
    setFlags(4);
}

void WfcFriendListMenu::buildListScreen() {
    volatile u16 z = 0x10;
    MIi_CpuClear16(z, listScreen, 0x800);
    for (s32 i = 0; i < 7; i++) {
        s32 v = topRow + i;
        s32 m = v % 7;
        MIi_CpuCopy16(&listScreenSrc[(m * 2 + 7) << 5], &listScreen[(v & 0xf) << 6], 0x80);
    }
    setFlags(2);
}

BOOL WfcFriendListMenu::stepScroll() {
    if (scrollY != scrollTargetY) {
        if (scrollY > scrollTargetY) {
            scrollY = scrollY - 6;
            if (scrollY < scrollTargetY) {
                scrollY = scrollTargetY;
            }
        } else {
            scrollY = scrollY + 6;
            if (scrollY > scrollTargetY) {
                scrollY = scrollTargetY;
            }
        }
        setScroll(scrollY);
        syncKnobFromScroll();
        return TRUE;
    }
    return FALSE;
}

BOOL WfcFriendListMenu::tryGrabKnob(s32 x, s32 y) {
    if (((MenuScrollKnob *)(&knob))->hitTest(x, y)) {
        knobGrabOffset = knobPos - y;
        ((MenuScrollKnob *)(&knob))->grab();
        knobTickPos = knobPos;
        return TRUE;
    }
    return FALSE;
}

void WfcFriendListMenu::dragKnob(s32 v, BOOL c) {
    if (c) {
        v = v - 0x40;
    } else {
        v = v + knobGrabOffset;
    }
    if (v < 0) {
        v = 0;
    }
    if (v > 0x50) {
        v = 0x50;
    }
    if (c) {
        Math_StepS32(&knobPos, v, 8);
    } else {
        knobPos = v;
    }
    syncScrollFromKnob();
    placeKnob();
    s32 d = knobTickPos - knobPos;
    if (d >= 4 || d <= -4) {
        Menu_PlayScrollTickSe();
        knobTickPos = knobPos;
    }
}

void WfcFriendListMenu::releaseKnob() { ((MenuScrollKnob *)(&knob))->release(); }

void WfcFriendListMenu::moveKnobByKeys() {
    s32 old = knobPos;
    u32 k = gPad[0];
    if (k & 0x40) {
        knobPos = knobPos - 4;
        if (knobPos < 0) {
            knobPos = 0;
        }
    } else if (k & 0x80) {
        knobPos = knobPos + 4;
        if (knobPos > 0x50) {
            knobPos = 0x50;
        }
    }
    if (old != knobPos) {
        syncScrollFromKnob();
        placeKnob();
        Menu_PlayScrollTickSe();
    }
}

BOOL WfcFriendListMenu::finishKnobRelease() {
    if (((ScrollKnob *)(&knob))->areAnimsDone()) {
        ((MenuScrollKnob *)(&knob))->show();
        return TRUE;
    }
    return FALSE;
}

void WfcFriendListMenu::placeKnob() {
    ((ScrollKnob *)(&knob))->moveTo(0x62, slideOffsetY + (knobPos - 0x28));
}

void WfcFriendListMenu::syncScrollFromKnob() {
    s32 v = _s32_div_f(knobPos * 0x1a0, 0x50);
    if (v < 0) {
        v = 0;
    }
    if (v > 0x1a0) {
        v = 0x1a0;
    }
    setScroll(v);
    scrollTargetY = v;
}

void WfcFriendListMenu::syncKnobFromScroll() {
    knobPos = _s32_div_f(scrollY * 0x50, 0x1a0);
    placeKnob();
}

BOOL WfcFriendListMenu::decideTarget(u32 k) {
    if (k >= 3 && k <= 9) {
        s32 idx = topRow + k - 3;
        if (idx >= 0x20) {
            return FALSE;
        }
        u8 c = listOrder[idx];
        if (isFriendSelectable(c)) {
            selectedFriend = c;
            Snd_PlaySe(0x29);
            setFlags(0x10);
            setFlags(0x20);
        }
        return FALSE;
    }
    switch (k) {
    case 2:
        ((MenuScrollKnob *)(&knob))->grab();
        Menu_PlayScrollGrabSe();
        setMainState(4);
        return TRUE;
    case 1:
        if (confirmButtonPal == 8) {
            decideConfirm();
            return TRUE;
        }
        return FALSE;
    case 0:
        decideQuit();
        return TRUE;
    }
    return FALSE;
}

BOOL WfcFriendListMenu::moveTargetByKeys(u32 pad) {
    u32 old = cursorTarget;
    if (old >= 3 && old <= 9) {
        if (MenuKeys_HasRight(pad)) {
            cursorTarget = 2;
        } else if (MenuKeys_HasUp(pad)) {
            if (cursorTarget > 3) {
                cursorTarget = *(volatile u8 *)&cursorTarget - 1;
                if (cursorTarget == 3) {
                    s32 r = scrollTargetY & 0xf;
                    if (r != 0) {
                        scrollTargetY = scrollTargetY - r;
                    }
                }
                return TRUE;
            } else if (scrollTargetY >= 0x10) {
                scrollTargetY = scrollTargetY - 0x10;
                return TRUE;
            } else if (scrollTargetY > 0) {
                scrollTargetY = 0;
                return TRUE;
            }
        } else if (MenuKeys_HasDown(pad)) {
            u32 cur = cursorTarget;
            if ((s32)(cur - 3) + topRow >= (s32)numOnline - 1) {
                cursorTarget = 0;
            } else if (cur < 8) {
                cursorTarget = *(volatile u8 *)&cursorTarget + 1;
            } else {
                s32 t = scrollTargetY;
                s32 r = t & 0xf;
                if (r != 0) {
                    scrollTargetY = scrollTargetY + (0x10 - r);
                    return TRUE;
                } else if (t <= 0x190) {
                    scrollTargetY = scrollTargetY + 0x10;
                    return TRUE;
                } else {
                    cursorTarget = 0;
                }
            }
        }
    } else {
        switch (old) {
        case 0:
            if (MenuKeys_HasUp(pad)) {
                if (numOnline != 0) {
                    targetLastVisibleRow();
                }
            } else if (MenuKeys_HasRight(pad)) {
                cursorTarget = 1;
            }
            break;
        case 1:
            if (MenuKeys_HasUp(pad)) {
                if (numOnline != 0) {
                    targetLastVisibleRow();
                } else {
                    cursorTarget = 2;
                }
            } else if (MenuKeys_HasLeft(pad)) {
                cursorTarget = 0;
            } else if (MenuKeys_HasRight(pad)) {
                cursorTarget = 2;
            }
            break;
        case 2:
            if (MenuKeys_HasDown(pad)) {
                cursorTarget = 1;
            } else if (MenuKeys_HasLeft(pad)) {
                targetFromCursorY();
            }
            break;
        }
    }
    if (old != cursorTarget) {
        return TRUE;
    }
    return FALSE;
}

void WfcFriendListMenu::targetLastVisibleRow() {
    cursorTarget = 8;
    s32 r = scrollTargetY & 0xf;
    if (r != 0) {
        scrollTargetY = scrollTargetY - r;
    }
}

void WfcFriendListMenu::targetFromCursorY() {
    if (numOnline == 0) {
        cursorTarget = 1;
    } else {
        s32 v = ((MenuCursorBase *)(&cursor))->getScreenY();
        if (v < 0x38) {
            v = 0x38;
        }
        if (v > 0xa7) {
            v = 0xa7;
        }
        cursorTarget = ((v - (0x38 - (scrollTargetY & 0xf))) >> 4) + 3;
    }
}

void WfcFriendListMenu::cancelVramTasks() {
    s32 i = 0;
    for (; i < 2; i++) {
        vramTasks[i].cancel();
    }
}

void WfcFriendListMenu::fadeRowColor(s32 a, s32 t, s32 b) {
    u16 y = rowPaletteSrc[15];
    u8 rr = y & 0x1f;
    u8 rg = (y & 0x3e0) >> 5;
    u8 rb = (y & 0x7c00) >> 10;
    s32 n = 20 - t;
    u16 x = rowPaletteSrc[b];
    rr = ((u8)(x & 0x1f) * t + rr * n) / 20;
    rg = ((u8)((x & 0x3e0) >> 5) * t + rg * n) / 20;
    rb = ((u8)((x & 0x7c00) >> 10) * t + rb * n) / 20;
    rowPalette[(u8)(14 - a)] = rr | (rg << 5) | (rb << 10);
    setFlags(8);
}

void WfcFriendListMenu::updateRowColors() {
    s32 i;
    for (i = 0; i < 7; i++) {
        s32 idx = rowFriends[i];
        if (idx < 0x20) {
            u32 v;
            u32 base;
            u32 sel;
            if (friendRecords[idx].c >= 4) {
                base = friendFade[idx];
                v = (u8)(base | 0x40);
                sel = 7;
            } else {
                base = friendFade[idx];
                v = base;
                sel = 0xe;
            }
            if (v != rowColorKeys[i]) {
                fadeRowColor(i, base, sel);
                rowColorKeys[i] = v;
            }
        }
    }
}

BOOL WfcFriendListMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void WfcFriendListMenu::setFlags(u32 m) { flags = flags | m; }

void WfcFriendListMenu::clearFlags(u32 m) { flags = flags & ~m; }

extern "C" GXOamAttr sWfcQuitButtonCells[4] = {
    {0x81bf404a, 0x93, 1, 0x8, 0x0},
    {0x41df004a, 0x97, 1, 0x8, 0x0},
    {0x81d50043, 0x82, 1, 0x8, 0x0},
    {0x81b90043, 0x80, 1, 0x8, 0xffff},
};

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov146_02291f60) {
    HOST_OVERLAY_VAR(data_ov146_02293e18),
    HOST_OVERLAY_VAR(data_ov146_02293e98),
    HOST_OVERLAY_VAR(sWfcRowCellsSelected),
    HOST_OVERLAY_VAR(data_ov146_02293e48),
    HOST_OVERLAY_VAR(data_ov146_02293f90),
    HOST_OVERLAY_VAR(sWfcFriendListMenuProfile),
    HOST_OVERLAY_VAR(sWfcRowCells),
    HOST_OVERLAY_VAR(data_ov146_02293f10),
    HOST_OVERLAY_VAR(sWfcConfirmButtonCells),
    HOST_OVERLAY_VAR(data_ov146_02293e78),
    HOST_OVERLAY_VAR(data_ov146_02293e20),
    HOST_OVERLAY_VAR(data_ov146_02293ed0),
    HOST_OVERLAY_VAR(data_ov146_02293ef0),
    HOST_OVERLAY_VAR(data_ov146_02293f30),
    HOST_OVERLAY_VAR(sWfcFrameCells),
    HOST_OVERLAY_VAR(WfcFriendListMenu_renderRows_sa),
    HOST_OVERLAY_VAR(WfcFriendListMenu_renderRows_sa_init),
    HOST_OVERLAY_VAR(WfcFriendListMenu_renderRows_sb),
    HOST_OVERLAY_VAR(WfcFriendListMenu_renderRows_sb_init),
    HOST_OVERLAY_VAR(sWfcQuitButtonCells),
    HOST_OVERLAY_VARS_END
};

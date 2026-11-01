#include "types.h"
#include "host_tick.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuTownListPanel.h"
#include "sys/ProcProfile.h"
#include "net/Net.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02051218.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov140/unk_02292900.h"

class DistantTownsMenu;

extern "C" {
extern u16 gPad[];
}











typedef void (DistantTownsMenu::*Unk_ov140_02293e04_Fn)();

class DistantTownsMenu : public MenuProc {
public:
    DistantTownsMenu() : listPanel(), cursor(), bottomButtons(), screenTask(), textLabels() {}

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
    void drawPageIndex();
    void drawLastPageIndex();
    void drawTownCount();
    void resetTextLabels();
    LabelString *allocTextLabel();
    NetWifiFriends *getFriendList();
    void fadeRows(s32 t);
    BOOL isListedFriend(NetWifiFriendStatus *p);
    void initList();
    s32 countListedFriends();
    void refreshPage();
    BOOL refreshRowIcons();
    void selectRow(s32 v);
    void resetRowScreen();
    void flushBgScreen();
    BOOL moveCursorByPad(u32 pad);
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void moveCursorTo(s32 a, s32 b);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void nextPage();
    void startQuit();
    void startConfirm();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updatePageFadeIn();
    void updatePageFadeOut();
    void updateCloseDelay();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateButtons();
    void updateTouch();
    void refreshFriendStatus();
    void loadObjGfx();
    void loadBgGfx();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initDistantTowns();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void stateLoad();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ s32 slideY;
    /* 0x098 */ s32 buttonsSlideY;
    /* 0x09c */ s32 selectedRow;
    /* 0x0a0 */ s32 confirmButtonPal;
    /* 0x0a4 */ s32 quitButtonPal;
    /* 0x0a8 */ s32 moreButtonPal;
    /* 0x0ac */ u16 bgScreen[0x400];
    /* 0x8ac */ u16 flags;
    /* 0x8ae */ u8 returnState;
    /* 0x8af */ u8 rowFilled[6];
    /* 0x8b5 */ u8 listFriendIds[0x20];
    /* 0x8d5 */ u8 rowFriendIds[6];
    /* 0x8db */ u8 delayTimer;
    /* 0x8dc */ u8 cursorSlot;
    /* 0x8dd */ u8 page;
    /* 0x8de */ u8 lastPage;
    /* 0x8df */ u8 townCount;
    /* 0x8e0 */ u8 rowIcons[6];
    /* 0x8e6 */ u8 labelCount;
    /* 0x8e7 */ u8 pad_8e7;
    /* 0x8e8 */ MenuTownListPanel listPanel;
    /* 0xf0c */ MenuCursorBuf0 cursor;
    /* 0xf70 */ MenuBottomButtons bottomButtons;
    /* 0x10d4 */ BgVramTask screenTask;
    /* 0x10f8 */ u8 unk_10f8[0x16a0 - 0x10f8];
    /* 0x16a0 */ LabelString textLabels[3];
};


static inline BOOL Unk_ov140_02293450_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}



extern "C" GXOamAttr data_ov140_02293e64[42] = {
    {0x81a800a8, 0x17b, 0, 0xb, 0x0},
    {0x41c880a8, 0x17f, 0, 0xb, 0x0},
    {0x41a840c8, 0x1fb, 0, 0xb, 0x0},
    {0x01c800c8, 0x1ff, 0, 0xb, 0x0},
    {0x4028403e, 0xe6, 2, 0x4, 0x0},
    {0x4008403e, 0xe6, 2, 0x4, 0x0},
    {0x41e0403e, 0xe6, 2, 0x4, 0x0},
    {0x41c0403e, 0xe6, 2, 0x4, 0x0},
    {0x41a0403e, 0xe6, 2, 0x4, 0x0},
    {0x4028402e, 0xe6, 2, 0x4, 0x0},
    {0x4008402e, 0xe6, 2, 0x4, 0x0},
    {0x41e0402e, 0xe6, 2, 0x4, 0x0},
    {0x41c0402e, 0xe6, 2, 0x4, 0x0},
    {0x41a0402e, 0xe6, 2, 0x4, 0x0},
    {0x4028401e, 0xe6, 2, 0x4, 0x0},
    {0x4008401e, 0xe6, 2, 0x4, 0x0},
    {0x41e0401e, 0xe6, 2, 0x4, 0x0},
    {0x41c0401e, 0xe6, 2, 0x4, 0x0},
    {0x41a0401e, 0xe6, 2, 0x4, 0x0},
    {0x4028400e, 0xe6, 2, 0x4, 0x0},
    {0x4008400e, 0xe6, 2, 0x4, 0x0},
    {0x41e0400e, 0xe6, 2, 0x4, 0x0},
    {0x41c0400e, 0xe6, 2, 0x4, 0x0},
    {0x41a0400e, 0xe6, 2, 0x4, 0x0},
    {0x402840fe, 0xe6, 2, 0x4, 0x0},
    {0x400840fe, 0xe6, 2, 0x4, 0x0},
    {0x41e040fe, 0xe6, 2, 0x4, 0x0},
    {0x41c040fe, 0xe6, 2, 0x4, 0x0},
    {0x41a040fe, 0xe6, 2, 0x4, 0x0},
    {0x402840ee, 0xe6, 2, 0x4, 0x0},
    {0x400840ee, 0xe6, 2, 0x4, 0x0},
    {0x41e040ee, 0xe6, 2, 0x4, 0x0},
    {0x41c040ee, 0xe6, 2, 0x4, 0x0},
    {0x41a040ee, 0xe6, 2, 0x4, 0x0},
    {0x41b440d6, 0xcd, 2, 0x5, 0x0},
    {0x01d440d6, 0xd1, 2, 0x5, 0x0},
    {0x400c40d6, 0xed, 2, 0x5, 0x0},
    {0x002c40d6, 0xf1, 2, 0x5, 0x0},
    {0x902040d5, 0x88, 2, 0x5, 0x0},
    {0x800840d5, 0x88, 2, 0x5, 0x0},
    {0x91c840d5, 0x88, 2, 0x5, 0x0},
    {0x81b040d5, 0x88, 2, 0x5, 0xffff},
};

extern "C" ProcProfile sDistantTownsMenuProfile = {(void *(*)())DistantTownsMenu_Create, 0xb5, 0xb9};

extern "C" GXOamAttr data_ov140_02293d80[1] = {
    {0x804840e0, 0x1c8, 0, 0xc, 0xffff},
};

extern "C" GXOamAttr data_ov140_02293d40[1] = {
    {0x804840e0, 0x1c0, 0, 0xc, 0xffff},
};

extern "C" GXOamAttr data_ov140_02293d00[1] = {
    {0x804840e0, 0x1c4, 0, 0xc, 0xffff},
};

extern "C" GXOamAttr data_ov140_02293d88[1] = {
    {0x804840e0, 0x1cc, 0, 0xd, 0xffff},
};

extern "C" GXOamAttr data_ov140_02293dcc[6] = {
    {0x402840ee, 0xc6, 2, 0x5, 0x0},
    {0x419c00df, 0x86, 2, 0x5, 0x0},
    {0x400840ee, 0xc6, 2, 0x5, 0x0},
    {0x41e040ee, 0xc6, 2, 0x5, 0x0},
    {0x41c040ee, 0xc6, 2, 0x5, 0x0},
    {0x41a040ee, 0xc6, 2, 0x5, 0xffff},
};

extern "C" DistantTownsMenu *DistantTownsMenu_Create() { return new DistantTownsMenu(); }

BOOL DistantTownsMenu::onCreate() {
    initDistantTowns();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL DistantTownsMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL DistantTownsMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    if (testFlags(1) == 0) {
        return FALSE;
    }
    bottomButtons.drawAt(buttonsSlideY);
    s32 base = slideY + 0x60;
    Oam_DrawCell(1, data_ov140_02293da4, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    GXOamAttr *a = (GXOamAttr *)listPanel.getCellList(5);
    GXOamAttr *b = (GXOamAttr *)listPanel.getCellList(6);
    GXOamAttr *c = (GXOamAttr *)listPanel.getCellList(7);
    s32 v = selectedRow;
    if (v != -1) {
        Oam_DrawCell(1, data_ov140_02293dcc, 0x80, base + (v << 4), -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    Oam_DrawCell(1, data_ov140_02293e64, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, a, 0x80, base, moreButtonPal, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, b, 0x80, base, quitButtonPal, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, c, 0x80, base, confirmButtonPal, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    listPanel.drawTitle(0, slideY);
    if (testFlags(0x20) == 0) {
        GXOamAttr *tbl[5] = {0, data_ov140_02293d40, data_ov140_02293d00, data_ov140_02293d80, data_ov140_02293d88};
        s32 z = 0;
        s32 i;
        for (i = 0; i < 6; base += 0x10, i++) {
            GXOamAttr *t = tbl[rowIcons[i]];
            if (t != 0) {
                Oam_DrawCell(1, t, 0x80, base, -1, 2, 0x1000, 0x1000, z, -1, z, z);
            }
        }
    }
    return TRUE;
}

extern "C" GXOamAttr data_ov140_02293da4[5] = {
    {0x005040d7, 0x1f4, 0, 0x8, 0x0},
    {0x004880d4, 0x1d0, 0, 0xc, 0x0},
    {0x01a600d7, 0x1f3, 0, 0x8, 0x0},
    {0x019a00d7, 0x1f2, 0, 0x8, 0x0},
    {0x01a000d7, 0x1f1, 0, 0x8, 0xffff},
};

BOOL DistantTownsMenu::execTransition() {
    static Unk_ov140_02293e04_Fn tbl[5] = {
        &DistantTownsMenu::stateLoad,
        &DistantTownsMenu::stateOpen,
        &DistantTownsMenu::stateOpening,
        &DistantTownsMenu::stateClose,
        &DistantTownsMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void DistantTownsMenu::runMainState() {
    static Unk_ov140_02293e04_Fn tbl[8] = {
        &DistantTownsMenu::updateTouch,
        &DistantTownsMenu::updateButtons,
        &DistantTownsMenu::updateCursorMove,
        &DistantTownsMenu::updateCursorPress,
        &DistantTownsMenu::updateCursorRelease,
        &DistantTownsMenu::updateCloseDelay,
        &DistantTownsMenu::updatePageFadeOut,
        &DistantTownsMenu::updatePageFadeIn};
    (this->*tbl[mainState])();
}

BOOL DistantTownsMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL DistantTownsMenu::execPhase3() { return TRUE; }

BOOL DistantTownsMenu::execPhase4() { return TRUE; }

BOOL DistantTownsMenu::execClosed() {
    if (testFlags(2)) {
        MenuCtrl_SetResult(0);
    } else {
        MenuCtrl_SetResult(1);
        MenuCtrl_SetIndex(rowFriendIds[selectedRow]);
    }
    MenuCtrl_ClearPtrArgs();
    ProcBase_RequestDelete(this);
    return TRUE;
}

void DistantTownsMenu::stateLoad() {
    DistantTownsMenu_SetupBgLayers();
    loadBgGfx();
    loadObjGfx();
    listPanel.createLabels();
    setTransitionState(1);
}

void DistantTownsMenu::stateOpen() {
    initList();
    refreshPage();
    fadeRows(5);
    beginSubSlideIn(8, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    updateLayerSlide();
    setFlags(1);
    setTransitionState(2);
}

void DistantTownsMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
    }
    updateLayerSlide();
}

void DistantTownsMenu::stateClose() {
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(8, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(4);
}

void DistantTownsMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void DistantTownsMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void DistantTownsMenu::initDistantTowns() {
    flags = 0;
    listPanel.init(6, 0x7f);
    s32 i;
    for (i = 0; i < 6; i++) {
        rowFilled[i] = 0;
        rowIcons[i] = 0;
    }
    for (i = 0; i < 0x20; i++) {
        listFriendIds[i] = 0xff;
    }
    selectRow(-1);
    quitButtonPal = 8;
    moreButtonPal = 9;
    cursorSlot = 0;
    page = 0;
    lastPage = 0;
}

void DistantTownsMenu::releaseResources() {
    bottomButtons.freeTexts();
    listPanel.release();
    screenTask.cancel();
    resetTextLabels();
}

void DistantTownsMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void DistantTownsMenu::postInputUpdate() { postStateUpdate(); }

void DistantTownsMenu::preStateUpdate() {
    screenTask.cancel();
    bottomButtons.freeTexts();
    listPanel.preStateUpdate();
    resetTextLabels();
}

void DistantTownsMenu::postStateUpdate() {
    flushBgScreen();
    listPanel.flushPalette();
}

extern "C" void DistantTownsMenu_SetupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 2);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void DistantTownsMenu::loadBgGfx() {
    listPanel.loadBgGfx();
    listPanel.clearAllRows();
    File_LoadToBuffer("menu/res/d0_bg.bsc", bgScreen, 0x800);
    resetRowScreen();
}

void DistantTownsMenu::loadObjGfx() {
    listPanel.loadObjGfx();
    MenuButtons_LoadTextColors();
}

void DistantTownsMenu::refreshFriendStatus() {
    u32 c = countListedFriends();
    if (c != townCount) {
        townCount = c;
        drawTownCount();
        refreshPage();
        fadeRows(5);
    } else if (refreshRowIcons()) {
        fadeRows(5);
    }
}

void DistantTownsMenu::updateTouch() {
    refreshFriendStatus();
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (Unk_ov140_02293450_Both()) {
        s32 x = gTouchCurX;
        s32 y = gTouchCurY - 0x10;
        if (x >= 0x28 && x < 0xd0 && y >= 0x30 && y < 0x90) {
            s32 i = (y - 0x30) >> 4;
            if (rowFilled[i] != 0 && rowIcons[i] != 4) {
                selectRow(i);
                Snd_PlaySe(0x29);
            }
        } else if (y >= 0x96 && y < 0xa7) {
            if (x >= 0x5e && x < 0x9a) {
                startQuit();
            } else if (x >= 0x9f && x < 0xdb) {
                if (confirmButtonPal == 8) {
                    startConfirm();
                }
            } else if (x >= 0x1d && x < 0x59) {
                if (moreButtonPal == 8) {
                    nextPage();
                }
            }
        }
    }
}

void DistantTownsMenu::updateButtons() {
    refreshFriendStatus();
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        s32 v = takeRepeatedKeys();
        if (moveCursorByPad(v)) {
            moveCursorToTarget();
        } else {
            u16 t = gPad[1];
            if ((u32)t & 1) {
                pressCursor();
            } else if ((u32)t & 2) {
                startQuit();
                hideCursor();
            }
        }
    }
}

void DistantTownsMenu::updateCursorMove() {
    if (cursor.isMoving() == 0) {
        setMainState(returnState);
        runMainState();
    }
}

void DistantTownsMenu::updateCursorPress() {
    if (cursor.isAnimDone()) {
        u32 c = cursorSlot;
        if (c == 6) {
            if (moreButtonPal != 8) {
                goto tail;
            }
            nextPage();
        } else if (c == 8) {
            if (confirmButtonPal != 8) {
                goto tail;
            }
            startConfirm();
        } else if (c == 7) {
            startQuit();
        } else {
            if (rowFilled[c] == 0 || rowIcons[c] == 4) {
                goto tail;
            }
            selectRow(c);
            Snd_PlaySe(0x29);
            setFlags(8);
            setFlags(0x10);
        tail:
            setMainState(1);
            releaseCursor();
        }
    }
}

void DistantTownsMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
        if (testFlags(8)) {
            clearFlags(8);
            cursorSlot = 8;
            moveCursorToTarget();
        }
    }
}

void DistantTownsMenu::updateCloseDelay() {
    if (delayTimer != 0) {
        delayTimer = delayTimer - (TICK_STEP_ENDS() ? 1 : 0);
    } else {
        hideCursor();
        setPhase(1);
    }
}

void DistantTownsMenu::updatePageFadeOut() {
    if (delayTimer > 1) {
        delayTimer = delayTimer - (TICK_STEP_ENDS() ? 1 : 0);
        fadeRows(delayTimer);
    } else {
        fadeRows(0);
        refreshPage();
        setMainState(7);
    }
}

void DistantTownsMenu::updatePageFadeIn() {
    u32 t = delayTimer;
    if (t < 5) {
        fadeRows(t);
        delayTimer += TICK_STEP_ENDS() ? 1 : 0;
    } else {
        fadeRows(5);
        moreButtonPal = 8;
        if (MenuCtrl_IsTouch()) {
            startTouchInput();
        } else {
            setMainState(1);
            releaseCursor();
        }
        clearFlags(0x20);
    }
}

void DistantTownsMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void DistantTownsMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(1);
}

void DistantTownsMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void DistantTownsMenu::startConfirm() {
    clearFlags(2);
    confirmButtonPal = 10;
    delayTimer = 5;
    setTransitionState(3);
    setMainState(5);
    Snd_PlaySe(0x27);
}

void DistantTownsMenu::startQuit() {
    setFlags(2);
    quitButtonPal = 10;
    delayTimer = 5;
    setTransitionState(3);
    setMainState(5);
    Snd_PlaySe(0x28);
}

void DistantTownsMenu::nextPage() {
    setFlags(0x20);
    setMainState(6);
    delayTimer = 5;
    page++;
    if (page > lastPage) {
        page = 0;
    }
    drawPageIndex();
    moreButtonPal = 10;
    selectRow(-1);
    Snd_PlaySe(0xc);
}

void DistantTownsMenu::showCursor() {
    s32 x = getCursorTargetX();
    s32 y = getCursorTargetY();
    cursor.warpTo(x, y);
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    refreshCursor();
}

s32 DistantTownsMenu::getCursorTargetX() {
    u32 v = cursorSlot;
    if (v == 7) {
        return 0x6a;
    }
    if (v == 8) {
        return 0xab;
    }
    if (v == 6) {
        return 0x29;
    }
    return 0x24;
}

s32 DistantTownsMenu::getCursorTargetY() {
    u32 v = cursorSlot;
    if ((u8)(v + 0xfa) <= 2) {
        return 0xae;
    }
    return v * 16 + 0x46;
}

void DistantTownsMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void DistantTownsMenu::moveCursorToTarget() {
    s32 x = getCursorTargetX();
    s32 y = getCursorTargetY();
    moveCursorTo(x, y);
}

void DistantTownsMenu::moveCursorTo(s32 a, s32 b) {
    if (testFlags(0x10)) {
        cursor.moveToEase(a, b, 3, 0);
        clearFlags(0x10);
    } else {
        cursor.moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(2);
}

void DistantTownsMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void DistantTownsMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(3);
}

void DistantTownsMenu::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(4);
}

BOOL DistantTownsMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (old <= 5) {
        if (MenuKeys_HasUp(pad)) {
            if (cursorSlot != 0) {
                cursorSlot--;
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (cursorSlot < 5) {
                cursorSlot++;
            } else {
                cursorSlot = 6;
            }
        }
    } else {
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 5;
        } else if (MenuKeys_HasLeft(pad)) {
            if (cursorSlot > 6) {
                cursorSlot--;
            }
        } else if (MenuKeys_HasRight(pad)) {
            if (cursorSlot < 8) {
                cursorSlot++;
            }
        }
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void DistantTownsMenu::flushBgScreen() {
    if (testFlags(4)) {
        if (screenTask.requestScreen(bgScreen, 6, 0x800, 0)) {
            clearFlags(4);
        }
    }
}

void DistantTownsMenu::resetRowScreen() {
    BgScreen_SetRectPalette(bgScreen, 6, 8, 0xf, 0x13, 7);
    BgScreen_SetRectPalette(bgScreen, 0x11, 8, 0x18, 0x13, 7);
    setFlags(4);
}

void DistantTownsMenu::selectRow(s32 v) {
    selectedRow = v;
    if (v == -1) {
        confirmButtonPal = 9;
    } else {
        confirmButtonPal = 8;
    }
}

BOOL DistantTownsMenu::refreshRowIcons() {
    s32 i, k;
    BOOL changed = FALSE;
    NetWifiFriends *tbl = getFriendList();
    k = page * 6;
    i = 0;
    s32 z = 0;
    do {
        s32 v;
        if (isListedFriend(&tbl->status[k]) == 0) {
            v = z;
        } else {
            v = tbl->status[k].c;
        }
        if (v != rowIcons[i]) {
            changed = TRUE;
            rowIcons[i] = v;
        }
        k++;
        i++;
    } while (i < 6);
    return changed;
}

void DistantTownsMenu::refreshPage() {
    struct { u8 a[8]; u8 b[8]; u8 pad[8]; } l;
    u32 id;
    NetWifiFriendStatus *rec;
    s32 z1 = 0, z2 = 0;
    resetRowScreen();
    Mem_Clear(l.a, 8);
    Mem_Clear(l.b, 8);
    s32 j = page * 6;
    NetWifiFriends *tbl = getFriendList();
    s32 i = 0;
    for (; i < 6; j++, i++) {
        if (j < 0x20) {
            id = listFriendIds[j];
            if (id == 0xff || (rec = &tbl->status[id], !isListedFriend(rec))) {
                rowFilled[i] = z1;
                rowIcons[i] = z1;
                listPanel.clearRow(i);
            } else {
                rowFriendIds[i] = id;
                rowFilled[i] = 1;
                rowIcons[i] = rec->c;
                Mem_Copy(rec->statusString + 8, l.a, 8);
                Mem_Copy(rec->statusString, l.b, 8);
                listPanel.setRow(i, l.a);
            }
        } else {
            rowFilled[i] = z2;
            rowIcons[i] = z2;
            listPanel.clearRow(i);
        }
    }
}

s32 DistantTownsMenu::countListedFriends() {
    s32 i, cnt;
    NetWifiFriends *tbl = getFriendList();
    cnt = 0;
    i = 0;
    do {
        if (isListedFriend(&tbl->status[i])) {
            cnt++;
        }
        i++;
    } while (i < 0x20);
    return cnt;
}

void DistantTownsMenu::initList() {
    NetWifiFriends *tbl = getFriendList();
    s32 cnt = 0;
    s32 i = 0;
    do {
        if (isListedFriend(&tbl->status[i])) {
            cnt++;
        }
        listFriendIds[i] = i;
        i++;
    } while (i < 0x20);
    page = 0;
    lastPage = 5;
    townCount = cnt;
    drawLastPageIndex();
    drawTownCount();
    drawPageIndex();
    if (lastPage != 0) {
        moreButtonPal = 8;
    }
}

BOOL DistantTownsMenu::isListedFriend(NetWifiFriendStatus *p) {
    if (p->status == 6 && p->statusString[0] != 0) {
        return TRUE;
    }
    return FALSE;
}

void DistantTownsMenu::fadeRows(s32 t) {
    s32 i;
    for (i = 0; i < 6; i++) {
        s32 col;
        if (rowIcons[i] == 4) {
            col = 8;
        } else {
            col = 0xe;
        }
        listPanel.setRowFadeColor(i, t, 5, col);
    }
}

NetWifiFriends *DistantTownsMenu::getFriendList() { return (NetWifiFriends *)Net_GetWifiFriendList(); }

LabelString *DistantTownsMenu::allocTextLabel() {
    u32 c = labelCount;
    if (c >= 3) {
        return &textLabels[2];
    }
    labelCount = c + 1;
    return &textLabels[labelCount - 1];
}

void DistantTownsMenu::resetTextLabels() {
    s32 i;
    labelCount = 0;
    for (i = 0; i < 3; i++) {
        textLabels[i].destroyLabel();
    }
}

void DistantTownsMenu::drawTownCount() {
    LabelString *w = allocTextLabel();
    u8 buf[3];
    u32 v = townCount;
    if (v < 10) {
        buf[0] = v + 0x35;
        buf[1] = 0;
        buf[2] = 0;
    } else {
        buf[0] = (s32)v / 10 + 0x35;
        buf[1] = townCount % 10 + 0x35;
        buf[2] = 0;
    }
    String_FromEncodedBytes(w, buf, 3);
    w->createSmallLabel(8, 0x1f4, 2, 0xf, 0, 1);
    w->redrawAligned(0, 0);
}

void DistantTownsMenu::drawLastPageIndex() {
    LabelString *w = allocTextLabel();
    u8 buf[2];
    buf[0] = lastPage + 0x35;
    buf[1] = 0;
    String_FromEncodedBytes(w, buf, 2);
    w->createSmallLabel(8, 0x1f3, 1, 0xf, 0, 1);
    w->redrawAligned(0, 0);
}

void DistantTownsMenu::drawPageIndex() {
    LabelString *w = allocTextLabel();
    u8 buf[2];
    buf[0] = page + 0x35;
    buf[1] = 0;
    String_FromEncodedBytes(w, buf, 2);
    w->createSmallLabel(8, 0x1f2, 1, 0xf, 0, 1);
    w->redrawAligned(0, 0);
}

BOOL DistantTownsMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void DistantTownsMenu::setFlags(u32 m) { flags = flags | m; }

void DistantTownsMenu::clearFlags(u32 m) { flags = flags & ~m; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_02292900) {
    HOST_OVERLAY_VAR(data_ov140_02293e64),
    HOST_OVERLAY_VAR(sDistantTownsMenuProfile),
    HOST_OVERLAY_VAR(data_ov140_02293d80),
    HOST_OVERLAY_VAR(data_ov140_02293d40),
    HOST_OVERLAY_VAR(data_ov140_02293d00),
    HOST_OVERLAY_VAR(data_ov140_02293d88),
    HOST_OVERLAY_VAR(data_ov140_02293dcc),
    HOST_OVERLAY_VAR(data_ov140_02293da4),
    HOST_OVERLAY_VARS_END
};

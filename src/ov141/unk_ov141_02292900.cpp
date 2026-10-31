#include "types.h"
#include "Unk_020d8c7c.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "gfx/BgVramTask.h"
#include "menu/MenuCursor.h"
#include "menu/MenuBottomButtons.h"
#include "menu/MenuTownListPanel.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020e9a08.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_020720f8.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_02202fac.h"
#include "proto/ov141/unk_ov141_02292900.h"

class NearbyTownsMenu;

extern "C" {
extern u16 gPad[];

void MI_CpuCopy8(void *a, void *b, u32 n);
}











static inline BOOL Unk_ov141_02293194_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}

struct NearbyTownBeaconInfo {
    u8 b[0x10];
    u8 flag;
};

typedef void (NearbyTownsMenu::*Unk_ov141_02293968_Fn)();

class NearbyTownsMenu : public MenuProc {
public:
    NearbyTownsMenu() : listPanel(), cursor(), bottomButtons(), screenTask() {}

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
    BOOL selectRow(s32 v);
    void onStartClose();
    void onOpened();
    void storeTown(s32 idx, void *src);
    s32 findFreeRow();
    s32 findRowByAddress(u8 *e);
    void updateRowFades();
    void scanTowns();
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
    void startQuit();
    void startConfirm();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void updateCloseDelay();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void updateButtons();
    void updateTouch();
    void loadObjGfx();
    void loadBgGfx();
    void setupBgLayers();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initNearbyTowns();
    void updateLayerSlide();
    void stateClosing();
    void stateClose();
    void stateOpening();
    void stateOpen();
    void stateLoad();
    void runMainState();

    /* 0x091 */ u8 unk_91[3];
    /* 0x094 */ MenuTownListPanel listPanel;
    /* 0x6b8 */ MenuCursorBuf0 cursor;
    /* 0x71c */ MenuBottomButtons bottomButtons;
    /* 0x880 */ BgVramTask screenTask;
    /* 0x8a4 */ u8 rowScanEntries[6][0xe0];
    /* 0xde4 */ u8 rowUserData[6][0x11];
    /* 0xe4a */ u8 unk_e4a[2];
    /* 0xe4c */ s32 slideY;
    /* 0xe50 */ s32 buttonsSlideY;
    /* 0xe54 */ s32 selectedRow;
    /* 0xe58 */ s32 confirmButtonPal;
    /* 0xe5c */ s32 quitButtonPal;
    /* 0xe60 */ u16 bgScreen[0x400];
    /* 0x1660 */ u16 flags;
    /* 0x1662 */ u8 returnState;
    /* 0x1663 */ u8 rowStates[6];
    /* 0x1669 */ u8 rowFadeLevels[6];
    /* 0x166f */ u8 delayTimer;
    /* 0x1670 */ u8 cursorSlot;
};

extern "C" ProcProfile sNearbyTownsMenuProfile = {(void *(*)())NearbyTownsMenu_Create, 0xb6, 0xba};

extern "C" NearbyTownsMenu *NearbyTownsMenu_Create() { return new NearbyTownsMenu(); }

BOOL NearbyTownsMenu::onCreate() {
    initNearbyTowns();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL NearbyTownsMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL NearbyTownsMenu::onDraw() {
    if (MenuCtrl_IsButtons()) {
        cursor.drawWrapped();
    }
    if (!testFlags(1)) {
        return FALSE;
    }
    bottomButtons.drawAt(buttonsSlideY);
    s32 base = slideY + 0x60;
    GXOamAttr *h0 = (GXOamAttr *)listPanel.getCellList(0);
    GXOamAttr *h1 = (GXOamAttr *)listPanel.getCellList(1);
    GXOamAttr *h2 = (GXOamAttr *)listPanel.getCellList(2);
    GXOamAttr *h3 = (GXOamAttr *)listPanel.getCellList(3);
    s32 t = selectedRow;
    if (t != -1) {
        Oam_DrawCell(1, h1, 0x80, base + (t << 4), -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    Oam_DrawCell(1, h0, 0x80, base, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, h2, 0x80, base, quitButtonPal, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    Oam_DrawCell(1, h3, 0x80, base, confirmButtonPal, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    listPanel.drawTitle(0, slideY);
    return TRUE;
}

BOOL NearbyTownsMenu::execTransition() {
    static Unk_ov141_02293968_Fn tbl[5] = {
        &NearbyTownsMenu::stateLoad,
        &NearbyTownsMenu::stateOpen,
        &NearbyTownsMenu::stateOpening,
        &NearbyTownsMenu::stateClose,
        &NearbyTownsMenu::stateClosing};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void NearbyTownsMenu::runMainState() {
    static Unk_ov141_02293968_Fn tbl[6] = {
        &NearbyTownsMenu::updateTouch,
        &NearbyTownsMenu::updateButtons,
        &NearbyTownsMenu::updateCursorMove,
        &NearbyTownsMenu::updateCursorPress,
        &NearbyTownsMenu::updateCursorRelease,
        &NearbyTownsMenu::updateCloseDelay};
    (this->*tbl[mainState])();
}

BOOL NearbyTownsMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL NearbyTownsMenu::execPhase3() { return TRUE; }

BOOL NearbyTownsMenu::execPhase4() { return TRUE; }

BOOL NearbyTownsMenu::execClosed() {
    if (testFlags(2)) {
        MenuCtrl_SetResult(0);
    } else {
        MenuCtrl_SetResult(1);
        void *s = MenuCtrl_GetPtrArg0();
        if (s) {
            MI_CpuCopy8(rowScanEntries[selectedRow], s, 0xe0);
        }
        s = MenuCtrl_GetPtrArg1();
        if (s) {
            MI_CpuCopy8(rowUserData[selectedRow], s, 0x11);
        }
    }
    MenuCtrl_ClearPtrArgs();
    ProcBase_RequestDelete(this);
    return TRUE;
}

void NearbyTownsMenu::stateLoad() {
    setupBgLayers();
    loadBgGfx();
    loadObjGfx();
    setTransitionState(1);
}

void NearbyTownsMenu::stateOpen() {
    listPanel.createLabels();
    beginSubSlideIn(8, 4, 0, 0x30);
    Gfx2d_ShowLayer(6);
    updateLayerSlide();
    setFlags(1);
    setTransitionState(2);
}

void NearbyTownsMenu::stateOpening() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
        onOpened();
    }
    updateLayerSlide();
}

void NearbyTownsMenu::stateClose() {
    onStartClose();
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(8, 0, 0, 0x30);
    updateLayerSlide();
    setTransitionState(4);
}

void NearbyTownsMenu::stateClosing() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(6);
        setPhase(5);
    } else {
        updateLayerSlide();
    }
}

void NearbyTownsMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void NearbyTownsMenu::initNearbyTowns() {
    s32 i;
    flags = 0;
    listPanel.init(6, 0x7e);
    for (i = 0; i < 6; i++) {
        rowStates[i] = 0;
    }
    selectRow(-1);
    quitButtonPal = 8;
    cursorSlot = 0;
}

void NearbyTownsMenu::releaseResources() {
    bottomButtons.freeTexts();
    listPanel.release();
    screenTask.cancel();
}

void NearbyTownsMenu::preInputUpdate() {
    preStateUpdate();
    cursor.update();
}

void NearbyTownsMenu::postInputUpdate() {
    postStateUpdate();
}

void NearbyTownsMenu::preStateUpdate() {
    screenTask.cancel();
    bottomButtons.freeTexts();
    listPanel.preStateUpdate();
}

void NearbyTownsMenu::postStateUpdate() {
    flushBgScreen();
    listPanel.flushPalette();
}

void NearbyTownsMenu::setupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(6, 2);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
    Gfx2d_SetLayerPriority(4, 2);
    Gfx2d_SetLayerControl(4, 0, 0, 0);
    Gfx2d_SetLayerPriority(3, 2);
    Gfx2d_SetLayerControl(3, 0, 0, 0);
}

void NearbyTownsMenu::loadBgGfx() {
    listPanel.loadBgGfx();
    listPanel.clearAllRows();
    File_LoadToBuffer("menu/res/b0_bg.bsc", bgScreen, 0x800);
    BgScreen_SetRectPalette(bgScreen, 7, 8, 0x10, 0x13, 7);
    BgScreen_SetRectPalette(bgScreen, 0x12, 8, 0x19, 0x13, 7);
    setFlags(4);
    Gfx2d_LoadPaletteFile("menu/res/ten0.bpl", gCurrentHeap, 6, 3, 3, 3);
}

void NearbyTownsMenu::loadObjGfx() {
    listPanel.loadObjGfx();
    MenuButtons_LoadTextColors();
}

void NearbyTownsMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
        return;
    }
    if (Unk_ov141_02293194_Both()) {
        s32 x = gTouchCurX;
        s32 y = gTouchCurY - 0x10;
        if (x >= 0x28 && x < 0xd0 && y >= 0x30 && y < 0x90) {
            s32 i = (y - 0x30) >> 4;
            if (rowStates[i] != 0) {
                if (selectRow(i)) {
                    Snd_PlaySe(0x29);
                }
            }
        } else if (y >= 0x96 && y < 0xa7) {
            if (x >= 0x37 && x < 0x7b) {
                startQuit();
            } else if (x >= 0x89 && x < 0xc5) {
                if (confirmButtonPal == 8) {
                    startConfirm();
                }
            }
        }
    } else {
        scanTowns();
    }
}

void NearbyTownsMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else if (moveCursorByPad(takeRepeatedKeys())) {
        moveCursorToTarget();
    } else {
        u32 t = gPad[1];
        if (t & 1) {
            pressCursor();
        } else if (t & 2) {
            hideCursor();
            startQuit();
        } else if ((t & 8) && confirmButtonPal == 8) {
            hideCursor();
            startConfirm();
        } else {
            scanTowns();
        }
    }
}

void NearbyTownsMenu::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void NearbyTownsMenu::updateCursorPress() {
    if (cursor.isAnimDone()) {
        u32 c = cursorSlot;
        if (c == 7) {
            if (confirmButtonPal == 8) {
                startConfirm();
                return;
            }
        } else if (c == 6) {
            startQuit();
            return;
        } else if (rowStates[c] != 0) {
            selectRow(c);
            Snd_PlaySe(0x29);
            setFlags(8);
            setFlags(0x10);
        }
        setMainState(1);
        releaseCursor();
    }
}

void NearbyTownsMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
        if (testFlags(8)) {
            clearFlags(8);
            cursorSlot = 7;
            moveCursorToTarget();
        }
    }
}

void NearbyTownsMenu::updateCloseDelay() {
    if (delayTimer != 0) {
        delayTimer--;
    } else {
        hideCursor();
        setPhase(1);
    }
}

void NearbyTownsMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void NearbyTownsMenu::startButtonInput() {
    showCursor();
    restartKeyRepeat();
    setMainState(1);
}

void NearbyTownsMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void NearbyTownsMenu::startConfirm() {
    clearFlags(2);
    confirmButtonPal = 10;
    delayTimer = 5;
    setTransitionState(3);
    setMainState(5);
    Snd_PlaySe(0x27);
}

void NearbyTownsMenu::startQuit() {
    setFlags(2);
    quitButtonPal = 10;
    delayTimer = 5;
    setTransitionState(3);
    setMainState(5);
    Snd_PlaySe(0x28);
}

void NearbyTownsMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    ((MenuCursor *)&cursor)->setAnimIfChanged(7);
    refreshCursor();
}

s32 NearbyTownsMenu::getCursorTargetX() {
    u32 c = cursorSlot;
    if (c == 6) {
        return 0x43;
    }
    if (c == 7) {
        return 0x95;
    }
    return 0x2c;
}

s32 NearbyTownsMenu::getCursorTargetY() {
    u32 c = cursorSlot;
    if ((u8)(c + 0xfa) <= 1) {
        return 0xae;
    }
    return c * 16 + 0x46;
}

void NearbyTownsMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void NearbyTownsMenu::moveCursorToTarget() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    moveCursorTo(a, b);
}

void NearbyTownsMenu::moveCursorTo(s32 a, s32 b) {
    if (testFlags(0x10)) {
        cursor.moveToEase(a, b, 3, 0);
        clearFlags(0x10);
    } else {
        cursor.moveToEase(a, b, 3, 1);
    }
    returnState = mainState;
    setMainState(2);
}

void NearbyTownsMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void NearbyTownsMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(3);
}

void NearbyTownsMenu::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(4);
}

BOOL NearbyTownsMenu::moveCursorByPad(u32 pad) {
    u32 old = cursorSlot;
    if (old <= 5) {
        if (MenuKeys_HasUp(pad)) {
            if (cursorSlot != 0) {
                cursorSlot = cursorSlot - 1;
            }
        } else if (MenuKeys_HasDown(pad)) {
            if (cursorSlot < 5) {
                cursorSlot = cursorSlot + 1;
            } else {
                cursorSlot = 6;
            }
        }
    } else {
        if (MenuKeys_HasUp(pad)) {
            cursorSlot = 5;
        } else if (MenuKeys_HasLeft(pad)) {
            cursorSlot = 6;
        } else if (MenuKeys_HasRight(pad)) {
            cursorSlot = 7;
        }
    }
    if (old != cursorSlot) {
        return TRUE;
    }
    return FALSE;
}

void NearbyTownsMenu::flushBgScreen() {
    if (testFlags(4)) {
        if (screenTask.requestScreen(bgScreen, 6, 0x800, 0)) {
            clearFlags(4);
        }
    }
}

void NearbyTownsMenu::scanTowns() {
    s32 cnt;
    void **list;
    s32 n2;
    s32 z[3];
    NearbyTownBeaconInfo buf;
    s32 i;
    Comm_SendEmpty();
    cnt = Net_CountHostCandidates();
    for (i = 0; i < 6; i++) {
        if (rowStates[i] == 1) {
            rowStates[i] = 2;
        }
    }
    NetOverlay_AssertWireless();
    list = Net_GetScanResults();
    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    for (u8 j = 0; j < cnt; j = j + 1) {
        void *e = list[j];
        if (e != NULL) {
            NetOverlay_AssertWireless();
            u32 n = Net_GetBeaconGameInfoSize(e);
            if (n == 0x11) {
                NetOverlay_AssertWireless();
                MI_CpuCopy8(Net_GetBeaconGameInfo(e), &buf, n);
                if (buf.flag == 0) {
                    s32 idx = findRowByAddress((u8 *)e);
                    if (idx == ~z[1]) {
                        s32 idx2 = findFreeRow();
                        if (idx2 != ~z[2]) {
                            storeTown(idx2, e);
                            NetOverlay_AssertWireless();
                            n2 = Net_GetBeaconGameInfoSize(e);
                            NetOverlay_AssertWireless();
                            void *q = Net_GetBeaconGameInfo(e);
                            u8 *dst = rowUserData[idx2];
                            MI_CpuCopy8(q, dst, n2);
                            listPanel.setRow(idx2, dst);
                            rowFadeLevels[idx2] = z[0];
                        }
                    } else {
                        storeTown(idx, e);
                    }
                }
            }
        }
    }
    updateRowFades();
}

void NearbyTownsMenu::updateRowFades() {
    s32 i;
    s32 none = -1;
    u32 zero = 0;
    for (i = 0; i < 6; i++) {
        switch (rowStates[i]) {
        case 1:
            if (rowFadeLevels[i] < 5) {
                rowFadeLevels[i] = rowFadeLevels[i] + 1;
                listPanel.setRowFadeColor(i, rowFadeLevels[i], 5, 0xe);
            }
            break;
        case 2:
            if (rowFadeLevels[i] > 1) {
                rowFadeLevels[i]--;
                listPanel.setRowFadeColor(i, rowFadeLevels[i], 5, 0xe);
            } else {
                rowStates[i] = zero;
                listPanel.clearRow(i);
                if (selectedRow == i) {
                    selectRow(none);
                }
            }
            break;
        }
    }
}

s32 NearbyTownsMenu::findRowByAddress(u8 *e) {
    for (s32 i = 0; i < 6; i++) {
        if (rowStates[i] == 2) {
            BOOL fE = FALSE, fD = FALSE, fC = FALSE, fB = FALSE, fA = FALSE;
            u8 *s = rowScanEntries[i] + 2;
            if (e[2] == s[0] && e[3] == s[1]) {
                fA = TRUE;
            }
            if (fA && e[4] == s[2]) {
                fB = TRUE;
            }
            if (fB && e[5] == s[3]) {
                fC = TRUE;
            }
            if (fC && e[6] == s[4]) {
                fD = TRUE;
            }
            if (fD && e[7] == s[5]) {
                fE = TRUE;
            }
            if (fE) {
                return i;
            }
        }
    }
    return -1;
}

s32 NearbyTownsMenu::findFreeRow() {
    for (s32 i = 0; i < 6; i++) {
        if (rowStates[i] == 0) {
            return i;
        }
    }
    return -1;
}

void NearbyTownsMenu::storeTown(s32 idx, void *src) {
    MI_CpuCopy8(src, rowScanEntries[idx], 0xe0);
    rowStates[idx] = 1;
}

void NearbyTownsMenu::onOpened() {}

void NearbyTownsMenu::onStartClose() {}

BOOL NearbyTownsMenu::selectRow(s32 v) {
    BOOL changed = selectedRow != v ? TRUE : FALSE;
    selectedRow = v;
    if (v == -1) {
        confirmButtonPal = 9;
    } else {
        confirmButtonPal = 8;
    }
    return changed;
}

BOOL NearbyTownsMenu::testFlags(u32 m) {
    if (flags & m) {
        return TRUE;
    }
    return FALSE;
}

void NearbyTownsMenu::setFlags(u32 m) { flags = flags | m; }

void NearbyTownsMenu::clearFlags(u32 m) { flags = flags & ~m; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov141_02292900) {
    HOST_OVERLAY_VAR(sNearbyTownsMenuProfile),
    HOST_OVERLAY_VARS_END
};

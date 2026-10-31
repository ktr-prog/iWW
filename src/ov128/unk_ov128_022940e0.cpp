#include "types.h"
#include "host_shared_calls.h"
#include "Unk_020d8c7c.h"
#include "gfx/StarTwinkle.h"
#include "game/StarSkyView.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "menu/MenuLauncher.h"
#include "ui/LabelString.h"
#include "menu/MenuTextButton.h"
#include "menu/MenuCursor.h"
#include "sys/ProcProfile.h"
#include "game/ConstellationRecord.h"
#include "nitro/gxoam.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_02034438.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02094810.h"
#include "proto/main/unk_020b0774.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov004/unk_ov004_0221e7a8.h"
#include "proto/ov127/unk_ov127_02291f60.h"
#include "proto/ov128/unk_ov128_022940e0.h"

extern "C" {
extern u16 gPad[];
extern const u32 sNameLabelAnimY[4];
extern GXOamAttr data_ov128_02295540[16];
extern GXOamAttr data_ov128_022955c0[16];

ConstellationRecord *Constellation_GetRecord(s32 i);
}

static inline BOOL Unk_ov128_02294b44_Both() {
    if (gTouchHeld != 0 && gTouchChanged != 0) {
        return TRUE;
    }
    return FALSE;
}






class StargazingMenu;
typedef void (StargazingMenu::*Unk_ov128_022954e0_Fn)();


class StargazingMenu : public MenuProc {
public:
    StargazingMenu()
        : closeButton(), cursor(), twinkle(), skyView(), nameLabel() {}

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
    void updateNameLabelAnim();
    void trackCenterConstellation();
    void hideNameLabel();
    void refreshNameLabel();
    void setupNameLabel();
    void drawNameLabel();
    void findCenterConstellation();
    void resetNameLabel();
    u32 getPadDirection();
    void updateSkyScroll();
    void drawScrollStrips(s32 y);
    void releaseCursor();
    void pressCursor();
    void refreshCursor();
    void moveCursorToPos(s32 x, s32 y);
    void moveCursorToTarget();
    void hideCursor();
    s32 getCursorTargetY();
    s32 getCursorTargetX();
    void showCursor();
    void requestClose();
    void resumeInput();
    void startButtonInput();
    void startTouchInput();
    void mainAct0A();
    void updateCursorRelease();
    void updateCursorPress();
    void updateCursorMove();
    void mainAct06();
    void mainAct05();
    void mainAct04();
    void mainAct03();
    void mainAct02();
    void mainAct01();
    void mainAct00();
    void setupSkyView();
    void postStateUpdate();
    void preStateUpdate();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initMembers();
    void updateSlideWindow();
    void updateLayerSlide();
    void transitionAct03();
    void transitionAct02();
    void transitionAct01();
    void transitionAct00();
    void runMainState();

    /* 0x0091 */ u8 unk_91[3];
    /* 0x0094 */ MenuTextButton closeButton;
    /* 0x00e4 */ MenuCursorBuf0 cursor;
    /* 0x0148 */ StarTwinkle twinkle;
    /* 0x0478 */ StarSkyView skyView;
    /* 0x2cb0 */ LabelString nameLabel;
    /* 0x2cf0 */ s32 pointerX;
    /* 0x2cf4 */ s32 pointerY;
    /* 0x2cf8 */ s32 slideY;
    /* 0x2cfc */ s32 scrollFineX;
    /* 0x2d00 */ s32 scrollFineY;
    /* 0x2d04 */ s32 centerConstellation;
    /* 0x2d08 */ s32 shownConstellation;
    /* 0x2d0c */ s32 labelConstellation;
    /* 0x2d10 */ u16 stateFlags;
    /* 0x2d12 */ u8 returnState;
    /* 0x2d13 */ u8 scrollDir;
    /* 0x2d14 */ u8 cursorTarget;
    /* 0x2d15 */ u8 nameLabelAnimStep;
    /* 0x2d16 */ u8 nameLabelState;
    /* 0x2d17 */ u8 nameLabelHoldTimer;
    /* 0x2d18 */ u8 nameLabelWidth;
};

extern "C" StargazingMenu *StargazingMenu_Create() { return new StargazingMenu(); }

BOOL StargazingMenu::onCreate() {
    initMembers();
    transitionState = 0;
    setPhase(0);
    return TRUE;
}

BOOL StargazingMenu::onDelete() {
    ((MenuLauncher *)ProcBase_GetParent(this))->onChildClosed();
    releaseResources();
    return TRUE;
}

BOOL StargazingMenu::onDraw() {
    MenuCtrl_IsButtons();
    drawNameLabel();
    if (testFlags(1)) {
        closeButton.drawAt(0, slideY >> 2, 1);
        Shared_StarSky_DrawArrows(&skyView, slideY, 6);
    }
    if (testFlags(1)) {
        drawScrollStrips(slideY);
    }
    return TRUE;
}

extern "C" GXOamAttr data_ov128_022955c0[16] = {{0x8080, 0x11f, 0, 0x5, 0x0}, {0x8090, 0x11f, 0, 0x5, 0x0}, {0x80a0, 0x11f, 0, 0x5, 0x0}, {0x80b0, 0x11f, 0, 0x5, 0x0}, {0x80c0, 0x11f, 0, 0x5, 0x0}, {0x80d0, 0x11f, 0, 0x5, 0x0}, {0x80e0, 0x11f, 0, 0x5, 0x0}, {0x80f0, 0x11f, 0, 0x5, 0x0}, {0x8000, 0x11f, 0, 0x5, 0x0}, {0x8010, 0x11f, 0, 0x5, 0x0}, {0x8020, 0x11f, 0, 0x5, 0x0}, {0x8030, 0x11f, 0, 0x5, 0x0}, {0x8040, 0x11f, 0, 0x5, 0x0}, {0x8050, 0x11f, 0, 0x5, 0x0}, {0x8060, 0x11f, 0, 0x5, 0x0}, {0x8070, 0x11f, 0, 0x5, 0xffff}};
extern "C" GXOamAttr data_ov128_022952b8[4] = {{0x4188004c, 0xc6, 0, 0x5, 0x0}, {0x198804c, 0xc8, 0, 0x5, 0x0}, {0x9188404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" u8 sArrowCursorX[4] = {0x10, 0xf0, 0x80, 0x80};
extern "C" GXOamAttr data_ov128_022953e0[7] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x81a8404c, 0xca, 0, 0x5, 0x0}, {0x81c8404c, 0xce, 0, 0x5, 0x0}, {0x91d0404c, 0x106, 0, 0x8, 0x0}, {0x81bd404c, 0x107, 0, 0x8, 0x0}, {0x819f404c, 0x107, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_02295280[3] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x9190404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_022953b0[6] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x81a8404c, 0xca, 0, 0x5, 0x0}, {0x41c8004c, 0xce, 0, 0x5, 0x0}, {0x81a0404c, 0x107, 0, 0x8, 0x0}, {0x91c0404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_022952d8[4] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x41a8004c, 0xca, 0, 0x5, 0x0}, {0x91a0404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_02295498[8] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x81a8404c, 0xca, 0, 0x5, 0x0}, {0x41c8004c, 0xce, 0, 0x5, 0x0}, {0x1d8804c, 0xd0, 0, 0x5, 0x0}, {0x81b1404c, 0x107, 0, 0x8, 0x0}, {0x819d404c, 0x107, 0, 0x8, 0x0}, {0x91c8404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" u8 sArrowCursorY[4] = {0x60, 0x60, 0xb8, 0x08};
extern "C" GXOamAttr data_ov128_02295458[8] = {{0x8044404b, 0xd3, 0, 0x5, 0x0}, {0x4064004b, 0xd7, 0, 0x5, 0x0}, {0x8047404b, 0x111, 0, 0x8, 0x0}, {0x903a404b, 0x112, 0, 0x8, 0x0}, {0x805d404b, 0x112, 0, 0x8, 0x0}, {0x903c404d, 0x112, 0, 0x1, 0x0}, {0x805f404d, 0x112, 0, 0x1, 0x0}, {0x8049404d, 0x111, 0, 0x1, 0xffff}};
extern "C" GXOamAttr data_ov128_02295540[16] = {{0x7040f8, 0x104, 0, 0x5, 0x0}, {0x6040f8, 0x104, 0, 0x5, 0x0}, {0x5040f8, 0x104, 0, 0x5, 0x0}, {0x4040f8, 0x104, 0, 0x5, 0x0}, {0x3040f8, 0x104, 0, 0x5, 0x0}, {0x2040f8, 0x104, 0, 0x5, 0x0}, {0x1040f8, 0x104, 0, 0x5, 0x0}, {0x40f8, 0x104, 0, 0x5, 0x0}, {0x1f040f8, 0x104, 0, 0x5, 0x0}, {0x1e040f8, 0x104, 0, 0x5, 0x0}, {0x1d040f8, 0x104, 0, 0x5, 0x0}, {0x1c040f8, 0x104, 0, 0x5, 0x0}, {0x1b040f8, 0x104, 0, 0x5, 0x0}, {0x1a040f8, 0x104, 0, 0x5, 0x0}, {0x19040f8, 0x104, 0, 0x5, 0x0}, {0x18040f8, 0x104, 0, 0x5, 0xffff}};
extern "C" GXOamAttr *sNameLabelFrames[12] = {data_ov128_02295268, data_ov128_022952b8, data_ov128_02295280, data_ov128_02295298, data_ov128_022952d8, data_ov128_02295350, data_ov128_022952f8, data_ov128_02295380, data_ov128_022953b0, data_ov128_02295498, data_ov128_022953e0, data_ov128_02295418};
extern "C" GXOamAttr data_ov128_02295298[4] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x1a8804c, 0xca, 0, 0x5, 0x0}, {0x9198404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_02295350[6] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x41a8004c, 0xca, 0, 0x5, 0x0}, {0x1b8804c, 0xcc, 0, 0x5, 0x0}, {0x419b004c, 0x109, 0, 0x5, 0x0}, {0x91a8404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" const u32 sNameLabelAnimY[4] = {0x20, 0x11, 2, 0};
extern "C" GXOamAttr data_ov128_02295380[6] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x81a8404c, 0xca, 0, 0x5, 0x0}, {0x1c8804c, 0xce, 0, 0x5, 0x0}, {0x91b8404c, 0x106, 0, 0x8, 0x0}, {0x819c404c, 0x107, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_02295268[3] = {{0x4188004c, 0xc6, 0, 0x5, 0x0}, {0x5190004c, 0x106, 0, 0x8, 0x0}, {0x4180004c, 0x106, 0, 0x8, 0xffff}};
extern "C" GXOamAttr data_ov128_02295418[8] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x81a8404c, 0xca, 0, 0x5, 0x0}, {0x81c8404c, 0xce, 0, 0x5, 0x0}, {0x1e8804c, 0xd2, 0, 0x5, 0x0}, {0x81b9404c, 0x107, 0, 0x8, 0x0}, {0x819c404c, 0x107, 0, 0x8, 0x0}, {0x91d8404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};
extern "C" ProcProfile sStargazingMenuProfile = {(void *(*)())StargazingMenu_Create, 0xac, 0xb0};
extern "C" GXOamAttr data_ov128_022952f8[5] = {{0x8188404c, 0xc6, 0, 0x5, 0x0}, {0x81a8404c, 0xca, 0, 0x5, 0x0}, {0x8198404c, 0x107, 0, 0x8, 0x0}, {0x91b0404c, 0x106, 0, 0x8, 0x0}, {0x8180404c, 0x106, 0, 0x8, 0xffff}};

BOOL StargazingMenu::execTransition() {
    static Unk_ov128_022954e0_Fn tbl[4] = {
        &StargazingMenu::transitionAct00,
        &StargazingMenu::transitionAct01,
        &StargazingMenu::transitionAct02,
        &StargazingMenu::transitionAct03};
    preStateUpdate();
    (this->*tbl[transitionState])();
    postStateUpdate();
    return TRUE;
}

void StargazingMenu::runMainState() {
    static Unk_ov128_022954e0_Fn tbl[11] = {
        &StargazingMenu::mainAct00,
        &StargazingMenu::mainAct01,
        &StargazingMenu::mainAct02,
        &StargazingMenu::mainAct03,
        &StargazingMenu::mainAct04,
        &StargazingMenu::mainAct05,
        &StargazingMenu::mainAct06,
        &StargazingMenu::updateCursorMove,
        &StargazingMenu::updateCursorPress,
        &StargazingMenu::updateCursorRelease,
        &StargazingMenu::mainAct0A};
    (this->*tbl[mainState])();
}

BOOL StargazingMenu::execMain() {
    preInputUpdate();
    runMainState();
    postInputUpdate();
    return TRUE;
}

BOOL StargazingMenu::execPhase3() { return TRUE; }

BOOL StargazingMenu::execPhase4() { return TRUE; }

BOOL StargazingMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void StargazingMenu::transitionAct00() {
    ::StargazingMenu_SetupBgLayers();
    setupSkyView();
    beginSubSlideIn(9, 4, 0, 0x30);
    Gfx2d_ShowLayer(3);
    Gfx2d_ShowLayer(6);
    setFlags(1);
    Gfx2d_SetSubWin1Planes(0x1e, 1);
    updateSlideWindow();
    updateLayerSlide();
    setTransitionState(1);
}

void StargazingMenu::transitionAct01() {
    if (stepSlideIn(0)) {
        setPhase(2);
        resumeInput();
        setFlags(4);
    } else {
        updateSlideWindow();
    }
    updateLayerSlide();
}

void StargazingMenu::transitionAct02() {
    ((MenuLauncher *)ProcBase_GetParent(this))->setNextRequest(0x44, 1);
    beginSubSlideOut(9, 0, 0, 0x30);
    Gfx2d_SetSubWin1Planes(0x1e, 1);
    updateSlideWindow();
    updateLayerSlide();
    setTransitionState(3);
}

void StargazingMenu::transitionAct03() {
    if (stepSlideOut(0)) {
        Gfx2d_ResetLayer(3);
        Gfx2d_ResetLayer(6);
        Gfx2d_DisableSubWindows(2);
        setPhase(5);
    } else {
        updateSlideWindow();
        updateLayerSlide();
    }
}

void StargazingMenu::updateLayerSlide() {
    applySlideOffset(6, 0, 0);
    slideY = getSlideOffsetY();
}

void StargazingMenu::updateSlideWindow() {
    s32 a = getSlideOffsetY() - 0x40;
    if (a < 0) {
        a = 0;
    }
    s32 b = getSlideOffsetY() - 0x30;
    if (b <= 0) {
        Gfx2d_DisableSubWindows(2);
    } else {
        Gfx2d_EnableSubWindows(2);
        Gfx2d_SetWindowRect(3, 0, a, 0xff, b);
    }
}

void StargazingMenu::initMembers() {
    stateFlags = 0;
    StarSky_Reset(&skyView);
    pointerX = 0x80;
    pointerY = 0x60;
    cursorTarget = 1;
    resetNameLabel();
    PlayerActor_LocalRequestAct12();
    BgmTracks_FadeOutScene22();
}

void StargazingMenu::releaseResources() {
    StarTwinkle_Stop(&twinkle);
    Shared_StarSky_CancelUpload(&skyView);
    closeButton.freeText();
    nameLabel.destroyLabel();
    PlayerActor_RequestAct10();
    BgmTracks_FadeInScene22();
    Gfx2d_LoadCharFile("menu/inventory/b_itm0.bch", gCurrentHeap, 3, 0, 0x10, 0x10);
}

void StargazingMenu::preInputUpdate() { preStateUpdate(); }

void StargazingMenu::postInputUpdate() {
    trackCenterConstellation();
    postStateUpdate();
}

void StargazingMenu::preStateUpdate() {
    nameLabel.destroyLabel();
    StarTwinkle_Update(&twinkle);
    closeButton.freeText();
}

void StargazingMenu::postStateUpdate() {
    StarSky_Update(&skyView);
    updateNameLabelAnim();
}

extern "C" void StargazingMenu_SetupBgLayers() {
    Gfx2d_SetSubBgModeState(0);
    Gfx2d_SetLayerPriority(3, 2);
    Gfx2d_SetLayerControl(3, 1, 0, 0);
    Gfx2d_SetLayerPriority(6, 1);
    Gfx2d_SetLayerControl(6, 0, 0, 0);
}

void StargazingMenu::setupSkyView() {
    StarSky_LoadSkyBg(&skyView, 3);
    StarSky_LoadScopeBg(&skyView, 6);
    StarTwinkle_Init(&twinkle, 3);
    StarSky_LoadObjGraphics();
    closeButton.setup(data_ov128_02295458, 6, 2);
    closeButton.setLabelWithShadow(0x69);
    updateSkyScroll();
}

void StargazingMenu::mainAct00() {
    if (checkSwitchToButtons(0)) {
        startButtonInput();
    } else if (Unk_ov128_02294b44_Both()) {
        s32 x = gTouchCurX;
        s32 y = gTouchCurY;
        scrollDir = Shared_StarSky_HitArrow(&skyView, x, y);
        if (scrollDir != 4) {
            Shared_StarSky_ScrollInDir(&skyView, scrollDir, 1);
            updateSkyScroll();
            setMainState(1);
        } else if (x >= 0xc0 && y > 0xab) {
            requestClose();
        }
    }
}

void StargazingMenu::mainAct01() {
    if (gTouchHeld == 0) {
        setMainState(2);
        StarSky_StartBounce(&skyView, scrollDir);
        updateSkyScroll();
    } else {
        Shared_StarSky_ScrollInDir(&skyView, scrollDir, 1);
        updateSkyScroll();
    }
}

void StargazingMenu::mainAct02() {
    if (StarSky_UpdateBounce(&skyView)) {
        if (gTouchHeld != 0) {
            scrollDir = Shared_StarSky_HitArrow(&skyView, gTouchPressX, gTouchPressY);
            if (scrollDir != 4) {
                Shared_StarSky_ScrollInDir(&skyView, scrollDir, 1);
                updateSkyScroll();
                setMainState(1);
                return;
            }
        }
        setMainState(0);
    }
    updateSkyScroll();
}

void StargazingMenu::mainAct03() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        u32 k1 = gPad[1];
        if (k1 & 1) {
            pressCursor();
        } else if (k1 & 0x800) {
            clearFlags(2);
            setMainState(4);
            moveCursorToTarget();
        } else {
            s32 ox = pointerX;
            s32 oy = pointerY;
            u32 k0 = gPad[0];
            if (k0 & 0x20) {
                pointerX = ox - 4;
            } else if (k0 & 0x10) {
                pointerX = ox + 4;
            }
            u32 k2 = *(volatile u16 *)&gPad[0];
            if (k2 & 0x40) {
                s32 *py = &pointerY;
                *py = *py - 4;
            } else if (k2 & 0x80) {
                s32 *py = &pointerY;
                *py = *py + 4;
            }
            s32 nx = pointerX;
            if (ox != nx || oy != pointerY) {
                if (nx < 0x30) {
                    pointerX = 0x30;
                    Shared_StarSky_ScrollX(&skyView, -4);
                    updateSkyScroll();
                } else if (nx > 0xd0) {
                    pointerX = 0xd0;
                    Shared_StarSky_ScrollX(&skyView, 4);
                    updateSkyScroll();
                }
                s32 ny = pointerY;
                if (ny < 0x20) {
                    pointerY = 0x20;
                    StarSky_ScrollY(&skyView, -4, 0);
                    updateSkyScroll();
                } else if (ny > 0xa0) {
                    pointerY = 0xa0;
                    StarSky_ScrollY(&skyView, 4, 0);
                    updateSkyScroll();
                }
                cursor.warpTo(pointerX, pointerY);
            }
        }
    }
}

void StargazingMenu::mainAct04() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        u32 k = gPad[1];
        if ((k & 2) || (k & 8)) {
            requestClose();
        } else {
            u8 *q = &scrollDir;
            *q = getPadDirection();
            if (*q != 4) {
                Shared_StarSky_ScrollInDir(&skyView, *q, 1);
                updateSkyScroll();
                setMainState(5);
            }
        }
    }
}

void StargazingMenu::mainAct05() {
    u32 k = getPadDirection();
    if (k != scrollDir) {
        setMainState(6);
        StarSky_StartBounce(&skyView, scrollDir);
        updateSkyScroll();
    } else {
        Shared_StarSky_ScrollInDir(&skyView, scrollDir, 1);
        updateSkyScroll();
    }
}

void StargazingMenu::mainAct06() {
    if (StarSky_UpdateBounce(&skyView)) {
        setMainState(4);
    }
    updateSkyScroll();
}

void StargazingMenu::updateCursorMove() {
    if (!cursor.isMoving()) {
        setMainState(returnState);
        runMainState();
    }
}

void StargazingMenu::updateCursorPress() {
    if (cursor.isAnimDone() && testFlags(2)) {
        setMainState(3);
        releaseCursor();
    }
}

void StargazingMenu::updateCursorRelease() {
    if (cursor.isAnimDone()) {
        refreshCursor();
        setMainState(returnState);
    }
}

void StargazingMenu::mainAct0A() {
    if (!closeButton.stepPress()) {
        setPhase(1);
    }
}

void StargazingMenu::startTouchInput() {
    hideCursor();
    setMainState(0);
}

void StargazingMenu::startButtonInput() {
    clearFlags(2);
    setMainState(4);
    showCursor();
    restartKeyRepeat();
}

void StargazingMenu::resumeInput() {
    if (MenuCtrl_IsTouch()) {
        startTouchInput();
    } else {
        startButtonInput();
    }
}

void StargazingMenu::requestClose() {
    setTransitionState(2);
    setMainState(0xa);
    clearFlags(4);
    hideNameLabel();
    hideCursor();
}

void StargazingMenu::showCursor() {
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    cursor.warpTo(a, b);
    if (testFlags(2)) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    } else if (cursorTarget == 3) {
        ((MenuCursor *)&cursor)->setAnimIfChanged(0xd);
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
    }
    refreshCursor();
}

s32 StargazingMenu::getCursorTargetX() {
    if (testFlags(2)) {
        return pointerX;
    }
    return sArrowCursorX[cursorTarget];
}

s32 StargazingMenu::getCursorTargetY() {
    if (testFlags(2)) {
        return pointerY;
    }
    return sArrowCursorY[cursorTarget];
}

void StargazingMenu::hideCursor() {
    ((MenuCursor *)&cursor)->setAnimIfChanged(0);
    cursor.update();
}

void StargazingMenu::moveCursorToTarget() {
    if (testFlags(2)) {
        ((MenuCursor *)&cursor)->switchToAnim01();
    } else if (cursorTarget == 3) {
        ((MenuCursor *)&cursor)->switchToAnim0D();
    } else {
        ((MenuCursor *)&cursor)->switchToAnim01();
    }
    s32 a = getCursorTargetX();
    s32 b = getCursorTargetY();
    moveCursorToPos(a, b);
}

void StargazingMenu::moveCursorToPos(s32 x, s32 y) {
    cursor.moveToEase(x, y, 3, 1);
    returnState = mainState;
    setMainState(7);
}

void StargazingMenu::refreshCursor() {
    cursor.setPoseIdle();
    cursor.update();
}

void StargazingMenu::pressCursor() {
    ((MenuCursor *)&cursor)->setPosePress();
    setMainState(8);
}

void StargazingMenu::releaseCursor() {
    cursor.setPoseRelease();
    returnState = mainState;
    setMainState(9);
}

void StargazingMenu::drawScrollStrips(s32 y) {
    s32 t = y + 0x60;
    Oam_DrawCell(1, data_ov128_022955c0, 0x80, t - scrollFineY, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    s32 x = t + (s32)StarSky_GetOverscroll(&skyView);
    Oam_DrawCell(1, data_ov128_02295540, 0x80 - scrollFineX, x, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void StargazingMenu::updateSkyScroll() {
    s32 a = StarSky_GetScrollX(&skyView);
    s32 b = StarSky_GetScrollY(&skyView);
    scrollFineX = a & 0xf;
    scrollFineY = b & 0xf;
    findCenterConstellation();
}

u32 StargazingMenu::getPadDirection() {
    u32 r = 4;
    u32 k = gPad[0];
    if (k & 0x20) {
        return 0;
    }
    if (k & 0x10) {
        return 1;
    }
    if (k & 0x40) {
        return 3;
    }
    if (k & 0x80) {
        r = 2;
    }
    return r;
}

void StargazingMenu::resetNameLabel() {
    centerConstellation = -1;
    shownConstellation = -1;
    labelConstellation = -1;
    nameLabelState = 0;
    nameLabelAnimStep = 0;
    nameLabelWidth = 2;
}

void StargazingMenu::findCenterConstellation() {
    s32 a, b;
    s32 y = StarSky_GetOverscroll(&skyView) + 0x60;
    if (Shared_StarSky_ScreenToCell(&skyView, 0x80, y, &a, &b)) {
        s32 r = StarSky_GetLineAt(a, b);
        if (r != -1) {
            centerConstellation = Shared_StarSky_FindConstellationByLine((u16)r);
        }
    }
}

void StargazingMenu::drawNameLabel() {
    if (nameLabelState != 0) {
        Oam_DrawCell(1, sNameLabelFrames[nameLabelWidth - 2], 0x80, sNameLabelAnimY[nameLabelAnimStep] + 0x60, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void StargazingMenu::setupNameLabel() {
    s32 t = shownConstellation;
    if (t == -1) {
        nameLabelState = 0;
    } else {
        nameLabelState = 1;
        s32 u = shownConstellation;
        if (u != labelConstellation) {
            ConstellationRecord *r = Constellation_GetRecord(u);
            String_FromEncodedBytes(&nameLabel, r->name, 0x10);
            nameLabelWidth = ((s32)nameLabel.getTextWidth() + 7) >> 3;
            if (nameLabelWidth < 2) {
                nameLabelWidth = 2;
            }
            nameLabel.createLabel(8, 0xc6, nameLabelWidth, 0xf, 0, 0);
            nameLabel.redrawAligned(1, 0);
            labelConstellation = shownConstellation;
        }
    }
}

void StargazingMenu::refreshNameLabel() {
    s32 t = shownConstellation;
    if (t != -1 && t == labelConstellation) {
        setupNameLabel();
    } else {
        nameLabelState = 3;
    }
}

void StargazingMenu::hideNameLabel() {
    shownConstellation = -1;
    nameLabelState = 3;
}

void StargazingMenu::trackCenterConstellation() {
    s32 t = centerConstellation;
    if (t != -1) {
        if (shownConstellation != t) {
            shownConstellation = t;
            refreshNameLabel();
        }
    }
}

void StargazingMenu::updateNameLabelAnim() {
    switch (nameLabelState) {
    case 1:
        if (nameLabelAnimStep < 3) {
            nameLabelAnimStep = nameLabelAnimStep + 1;
        } else {
            nameLabelState = 2;
            nameLabelHoldTimer = 0x14;
        }
        break;
    case 2:
        if (centerConstellation == -1) {
            if (nameLabelHoldTimer != 0) {
                nameLabelHoldTimer = nameLabelHoldTimer - 1;
            } else {
                hideNameLabel();
            }
        } else {
            nameLabelHoldTimer = 0x14;
        }
        break;
    case 3:
        if (nameLabelAnimStep != 0) {
            nameLabelAnimStep = nameLabelAnimStep - 1;
        } else {
            setupNameLabel();
        }
        break;
    }
}

BOOL StargazingMenu::testFlags(u32 m) {
    if (stateFlags & m) {
        return TRUE;
    }
    return FALSE;
}

void StargazingMenu::setFlags(u32 m) { stateFlags = stateFlags | m; }

void StargazingMenu::clearFlags(u32 m) { stateFlags = stateFlags & ~m; }

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov128_022940e0) {
    HOST_OVERLAY_VAR(data_ov128_022955c0),
    HOST_OVERLAY_VAR(data_ov128_022952b8),
    HOST_OVERLAY_VAR(sArrowCursorX),
    HOST_OVERLAY_VAR(data_ov128_022953e0),
    HOST_OVERLAY_VAR(data_ov128_02295280),
    HOST_OVERLAY_VAR(data_ov128_022953b0),
    HOST_OVERLAY_VAR(data_ov128_022952d8),
    HOST_OVERLAY_VAR(data_ov128_02295498),
    HOST_OVERLAY_VAR(sArrowCursorY),
    HOST_OVERLAY_VAR(data_ov128_02295458),
    HOST_OVERLAY_VAR(data_ov128_02295540),
    HOST_OVERLAY_VAR(sNameLabelFrames),
    HOST_OVERLAY_VAR(data_ov128_02295298),
    HOST_OVERLAY_VAR(data_ov128_02295350),
    HOST_OVERLAY_VAR(data_ov128_02295380),
    HOST_OVERLAY_VAR(data_ov128_02295268),
    HOST_OVERLAY_VAR(data_ov128_02295418),
    HOST_OVERLAY_VAR(sStargazingMenuProfile),
    HOST_OVERLAY_VAR(data_ov128_022952f8),
    HOST_OVERLAY_VARS_END
};

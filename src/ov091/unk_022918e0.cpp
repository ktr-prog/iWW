#include "types.h"
#include "Unk_020d8c7c.h"
#include "ui/UiWidget.h"
#include "snd/BgmVolumeMixer.h"
#include "snd/BgmManager.h"
#include "ui/LetterRenderer.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/LabelButton.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuCursor.h"
#include "sys/ProcProfile.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/ov091/unk_022918e0.h"

extern "C" {
extern BgmManager *data_021c1b3c;
extern u16 gPad[];
}

class LetterViewMenu;

struct LetterView;












typedef void (LetterViewMenu::*Unk_ov091_02291ef0_Fn)();

class LetterViewMenu : public MenuProc {
public:
    LetterViewMenu()
        : letterRenderer(), closeButton(), cursor() {}

    virtual BOOL onCreate();
    virtual BOOL onDelete();
    virtual BOOL onDraw();
    virtual BOOL execTransition();
    virtual BOOL execMain();
    virtual BOOL execPhase3();
    virtual BOOL execPhase4();
    virtual BOOL execClosed();

    void updateButtons();
    void updateTouch();
    void stateWaitSlideOut();
    void stateSlideOut();
    void stateWaitButton();
    void statePressButton();
    void stateWaitSlideIn();
    void stateLoad();
    void startButtonInput();
    void startTouchInput();
    void postInputUpdate();
    void preInputUpdate();
    void releaseResources();
    void initLetterView();

    /* 0x094 */ LetterRenderer letterRenderer;
    /* 0x2a4 */ MenuLabelButtonStyle1 closeButton;
    /* 0x314 */ MenuCursorBuf1 cursor;
};

extern "C" LetterViewMenu *LetterViewMenu_Create() { return new LetterViewMenu(); }


extern "C" ProcProfile sLetterViewMenuProfile = {(void *(*)())LetterViewMenu_Create, 0xa8, 0xac};

BOOL LetterViewMenu::onCreate() {
    initLetterView();
    setTransitionState(0);
    setPhase(1);
    Snd_BeginMenuDuck();
    return TRUE;
}

BOOL LetterViewMenu::onDelete() {
    releaseResources();
    Snd_EndMenuDuck();
    return TRUE;
}

BOOL LetterViewMenu::onDraw() {
    cursor.update();
    s32 r = getSlideOffsetY();
    closeButton.setPos(0, r);
    closeButton.draw();
    if (MenuCtrl_IsButtons()) {
        ((MenuCursorBase *)&cursor)->drawWrapped();
    }
    return TRUE;
}

BOOL LetterViewMenu::execTransition() {
    static Unk_ov091_02291ef0_Fn tbl[6] = {
        &LetterViewMenu::stateLoad, &LetterViewMenu::stateWaitSlideIn,
        &LetterViewMenu::statePressButton, &LetterViewMenu::stateWaitButton,
        &LetterViewMenu::stateSlideOut, &LetterViewMenu::stateWaitSlideOut};
    (this->*tbl[transitionState])();
    return TRUE;
}

BOOL LetterViewMenu::execMain() {
    preInputUpdate();
    static Unk_ov091_02291ef0_Fn tbl[2] = {&LetterViewMenu::updateTouch,
                                           &LetterViewMenu::updateButtons};
    (this->*tbl[mainState])();
    postInputUpdate();
    return TRUE;
}

BOOL LetterViewMenu::execPhase3() { return TRUE; }

BOOL LetterViewMenu::execPhase4() { return TRUE; }

BOOL LetterViewMenu::execClosed() {
    ProcBase_RequestDelete(this);
    return TRUE;
}

void LetterViewMenu::stateLoad() {
    Snd_PlaySe(1);
    data_021c1b3c->mixer.setMenuDuck(0);
    Gfx2d_SetMainBgModeState(0);
    letterRenderer.show((LetterView *)MenuCtrl_GetArg(), 0, 2, 1);
    beginMainSlideIn(0xa, 0, 0, 0x30);
    Gfx2d_ShowLayer(0);
    applySlideOffset(0, 0, 0);
    Gfx2d_SetLayerControl(0, 0, 0, 0);
    Gfx2d_ShowLayer(2);
    applySlideOffset(2, 0, 0);
    Gfx2d_SetLayerControl(2, 0, 0, 0);
    setTransitionState(1);
}

void LetterViewMenu::stateWaitSlideIn() {
    if (stepSlideIn(1)) {
        setPhase(2);
        ((MenuCursor *)&cursor)->setAnimIfChanged(1);
        if (MenuCtrl_IsTouch()) {
            setMainState(0);
        } else {
            setMainState(1);
        }
    }
    applySlideOffset(0, 0, 0);
    applySlideOffset(2, 0, 0);
}

void LetterViewMenu::statePressButton() {
    if (cursor.isAnimDone()) {
        closeButton.setState(2);
        setTransitionState(3);
        Snd_PlaySe(0x27);
    }
}

void LetterViewMenu::stateWaitButton() {
    if (((MenuLabelButton *)&closeButton)->stepAnim()) {
        if (cursor.getAnim()) {
            s32 a = ((MenuLabelButton *)&closeButton)->getAnchorX(1);
            s32 b = ((MenuLabelButton *)&closeButton)->getAnchorY(1);
            ((MenuCursorBase *)&cursor)->warpTo(a, b);
        }
    } else {
        ((MenuCursor *)&cursor)->setAnimIfChanged(0);
        setTransitionState(4);
    }
}

void LetterViewMenu::stateSlideOut() {
    Snd_PlaySe(2);
    data_021c1b3c->mixer.endMenuDuck();
    beginMainSlideOut(0xa, 0, 0, 0x30);
    applySlideOffset(0, 0, 0);
    applySlideOffset(2, 0, 0);
    setTransitionState(5);
}

void LetterViewMenu::stateWaitSlideOut() {
    if (stepSlideOut(1)) {
        Gfx2d_ResetLayer(0);
        Gfx2d_ResetLayer(2);
        setPhase(5);
    } else {
        applySlideOffset(0, 0, 0);
        applySlideOffset(2, 0, 0);
    }
}

void LetterViewMenu::initLetterView() {
    letterRenderer.setLayer(0);
    ((MenuLabelButton *)&closeButton)->showDefault(0x65);
    s32 a = ((MenuLabelButton *)&closeButton)->getAnchorX(1);
    s32 b = ((MenuLabelButton *)&closeButton)->getAnchorY(1);
    ((MenuCursorBase *)&cursor)->warpTo(a, b);
}

void LetterViewMenu::releaseResources() { letterRenderer.release(); }

void LetterViewMenu::preInputUpdate() {}

void LetterViewMenu::postInputUpdate() {}

void LetterViewMenu::updateTouch() {
    if (checkSwitchToButtons(1)) {
        startButtonInput();
    } else if (((MenuLabelButton *)&closeButton)->isTouched()) {
        closeButton.setState(2);
        transitionState = 3;
        setPhase(1);
        Snd_PlaySe(0x27);
    }
}

void LetterViewMenu::updateButtons() {
    if (checkSwitchToTouch()) {
        startTouchInput();
    } else {
        u16 v = gPad[1];
        if ((v & 1) != 0 || (v & 2) != 0) {
            ((MenuCursor *)&cursor)->setPosePress();
            transitionState = 2;
            setPhase(1);
        }
    }
}

void LetterViewMenu::startTouchInput() { setMainState(0); }

void LetterViewMenu::startButtonInput() { setMainState(1); }


#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_022918e0) {
    HOST_OVERLAY_VAR(sLetterViewMenuProfile),
    HOST_OVERLAY_VARS_END
};

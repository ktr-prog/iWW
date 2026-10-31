#include "types.h"
#include "Unk_020d8c7c.h"
#include "text/Unk_02050288.h"
#include "talk/MsgStringBase.h"
#include "talk/MsgStringAttr.h"
#include "ui/CursorMotion.h"
#include "sys/KeyRepeat.h"
#include "menu/MenuTween.h"
#include "menu/PopupChoiceIdList.h"
#include "ui/AddresseePageArg.h"
#include "nitro/gxoam.h"
#include "talk/TalkWindowState.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "talk/LabelBalloonText.h"
#include "menu/MenuSlide.h"
#include "talk/MsgString.h"
#include "talk/MsgRequest.h"
#include "menu/MenuProc.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "ui/LabelButton.h"
#include "ui/LabelString.h"
#include "ui/LabelBalloon.h"
#include "ui/TouchPromptBalloon.h"
#include "menu/MenuTitleBalloon.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuCursor.h"
#include "menu/MenuScrollKnob.h"
#include "menu/PopupChoiceRow.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "talk/TalkMsgRequest.h"
#include "menu/MenuErrorMessage.h"


extern "C" {

void GXS_LoadOBJPltt(const void *p, u32 a, u32 b);

extern volatile u16 gPad[];
extern u8 gTalkMsgIndexEnd[];
}




#include "menu/MenuTextButton.h"
#include "proto/autoload_2/unk_020e7fd4.h"
#include "proto/autoload_2/unk_020e8558.h"
#include "proto/autoload_2/unk_020ec848.h"
#include "proto/autoload_2/unk_02128030.h"
#include "proto/main/unk_0200137c.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0205b7b0.h"
#include "proto/main/unk_02063904.h"
#include "proto/main/unk_02063f3c.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02065e88.h"
#include "proto/main/unk_0206db88.h"
#include "proto/main/unk_0206e54c.h"
#include "proto/main/unk_0206f834.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02097444.h"
#include "proto/main/unk_020b2c50.h"
#include "proto/main/unk_020b7d84.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov002/unk_ov002_02202fac.h"

extern "C" GXOamAttr sButtonCellsW8[5] = {
    {0x81f440a0, 0x14c, 0, 0xc, 0x0},
    {0x801440a0, 0x150, 0, 0xc, 0x0},
    {0x800440a0, 0xd0, 0, 0xb, 0x0},
    {0x901c40a0, 0xcf, 0, 0xb, 0x0},
    {0x81ec40a0, 0xcf, 0, 0xb, 0xffff},
};
extern "C" const u8 sBottomButtonTargetY[12] = {0xb6, 0x9e, 0xb2, 0xa9, 0xa9, 0xb6, 0xb6, 0xb6, 0xb6, 0xb6, 0x00, 0x00};
extern "C" GXOamAttr sButtonCellsW4A[3] = {
    {0x80204044, 0x146, 0, 0xc, 0x0},
    {0x90284044, 0xcf, 0, 0xb, 0x0},
    {0x80184044, 0xcf, 0, 0xb, 0xffff},
};
extern "C" GXOamAttr sButtonCellsW6A[6] = {
    {0x80084000, 0x14, 1, 0x0, 0x0},
    {0x40280000, 0x18, 1, 0x0, 0x0},
    {0x90204000, 0x5b, 1, 0x0, 0x0},
    {0x80004000, 0x5b, 1, 0x0, 0xffff},
    {0x90244004, 0x5b, 1, 0x1, 0x0},
    {0x80044004, 0x5b, 1, 0x1, 0xffff},
};
extern "C" const u8 sBottomButtonOfTarget[12] = {0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00};
extern "C" GXOamAttr sButtonCellsW6B[6] = {
    {0x80084000, 0x1a, 1, 0x0, 0x0},
    {0x40280000, 0x1e, 1, 0x0, 0x0},
    {0x90204000, 0x5b, 1, 0x0, 0x0},
    {0x80004000, 0x5b, 1, 0x0, 0xffff},
    {0x90244004, 0x5b, 1, 0x1, 0x0},
    {0x80044004, 0x5b, 1, 0x1, 0xffff},
};
extern "C" const u8 sTextButtonPressOffsets[4] = {0x00, 0x02, 0x03, 0x00};
extern "C" const u8 sBottomButtonTargetX[12] = {0x58, 0xca, 0xca, 0x62, 0xc2, 0x3e, 0xc4, 0x7c, 0x74, 0xc4, 0x00, 0x00};
extern "C" GXOamAttr sButtonCellsW12[7] = {
    {0x81d440a0, 0x14c, 0, 0xc, 0x0},
    {0x81f440a0, 0x150, 0, 0xc, 0x0},
    {0x801440a0, 0x154, 0, 0xc, 0x0},
    {0x800040a0, 0xd0, 0, 0xb, 0x0},
    {0x81e840a0, 0xd0, 0, 0xb, 0x0},
    {0x901c40a0, 0xcf, 0, 0xb, 0x0},
    {0x81cc40a0, 0xcf, 0, 0xb, 0xffff},
};
extern "C" GXOamAttr sButtonCellsW6Single[4] = {
    {0x804840a0, 0x140, 0, 0xc, 0x0},
    {0x406800a0, 0x144, 0, 0xc, 0x0},
    {0x905e40a0, 0xcf, 0, 0xb, 0x0},
    {0x804040a0, 0xcf, 0, 0xb, 0xffff},
};
extern "C" GXOamAttr sButtonCellsW4B[3] = {
    {0x81c04044, 0x142, 0, 0xc, 0x0},
    {0x91c84044, 0xcf, 0, 0xb, 0x0},
    {0x81b84044, 0xcf, 0, 0xb, 0xffff},
};
extern "C" const u8 sMenuButtonTextColors[4] = {0x5f, 0x7d, 0xc0, 0x50};

MenuErrorMessage::MenuErrorMessage() {
    state = 3;
    isFatal = 0;
}

MenuErrorMessage::~MenuErrorMessage() {}

void MenuErrorMessage::open(u8 *a, s32 b, u32 c) {
    isFatal = c;
    startTalk(a, b);
    LabelString s;
    String_Load2dMenu(&s, 0x64);
    prompt.setText((StrBuf *)&s);
    prompt.setPos(0, 0x40);
    prompt.queueOpen();
    prompt.enableObjWindow();
    prompt.setPriority(0);
}

void MenuErrorMessage::openHigh(u8 *a, s32 b, u32 c) {
    isFatal = c;
    startTalk(a, b);
    LabelString s;
    String_Load2dMenu(&s, 0x64);
    prompt.setText((StrBuf *)&s);
    prompt.setPos(0, 0x30);
    prompt.queueOpen();
    prompt.enableObjWindow();
    prompt.setPriority(0);
}

BOOL MenuErrorMessage::update(s32 a) {
    switch (state) {
    case 0:
        if (isTalkWaiting()) {
            state = 1;
            prompt.commitOpen();
            if (isFatal != 0) dimSubScreen();
        }
        break;
    case 1:
        if (isFatal != 0) for (;;) {}
        if (a == 0 || !MenuCtrl_IsForceCloseDue()) {
            BOOL k;
            if (gTouchHeld != 0 && gTouchChanged != 0) k = TRUE; else k = FALSE;
            if (!k) {
                u16 v = gPad[1];
                if ((v & 1) == 0 && (v & 2) == 0 && (v & 0x400) == 0 && (v & 0x800) == 0) break;
            }
        }
        advanceTalk();
        state = 2;
        prompt.hide(0);
        break;
    case 2:
        if (finishTalk()) {
            restoreBrightness();
            state = 3;
        }
        break;
    case 3:
        return TRUE;
    }
    prompt.updatePrompt();
    if (isFatal == 0) {
        TouchPromptBalloon *p = &prompt;
        p->draw();
    }
    return FALSE;
}

void MenuErrorMessage::startTalk(u8 *a, s32 b) {
    TalkWindowState *p = TalkWindow_Get(1);
    talk.resetMsg();
    talk.setFileName("obj_etc_error");
    talk.msgIndex = *a;
    p->attachRequest(&talk);
    p->disableInput();
    if (b == 0) p->setKeepSe();
    p->nextState = 1;
    p->lockAdvance();
    state = 0;
    if (isFatal == 0) dimSubScreen();
}

BOOL MenuErrorMessage::stepOpen() {
    if (state == 0) {
        if (isTalkWaiting()) {
            state = 1;
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

void MenuErrorMessage::beginClose() {
    advanceTalk();
    state = 2;
}

BOOL MenuErrorMessage::stepClose() {
    if (state == 2) {
        if (finishTalk()) {
            restoreBrightness();
            state = 3;
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

void MenuErrorMessage::showPromptOnly() {
    LabelString s;
    String_Load2dMenu(&s, 0x64);
    prompt.setText((StrBuf *)&s);
    prompt.setPos(0, 0x40);
    prompt.queueOpen();
    prompt.enableObjWindow();
    prompt.setPriority(0);
    dimSubScreen();
    prompt.commitOpen();
}

void MenuErrorMessage::updatePromptBalloon() {
    prompt.updatePrompt();
    TouchPromptBalloon *p = &prompt;
    p->draw();
}

void MenuErrorMessage::hidePromptBalloon() { prompt.hide(0); }

void MenuErrorMessage::undim() { restoreBrightness(); }

BOOL MenuErrorMessage::isTalkWaiting() {
    TalkWindowState *p = TalkWindow_Get(1);
    if (p->state == 2) return TRUE;
    return FALSE;
}

void MenuErrorMessage::advanceTalk() {
    TalkWindowState *p = TalkWindow_Get(1);
    p->setNextMessageIfUnset(gTalkMsgIndexEnd, 0);
    p->setAdvancePending();
    p->unlockAdvance();
}

BOOL MenuErrorMessage::finishTalk() {
    TalkWindowState *o = talk.window;
    if (o->state == 0) {
        o->detachRequest();
        return TRUE;
    }
    return FALSE;
}

void MenuErrorMessage::dimSubScreen() {
    Gfx2d_BeginSubObjWinBrightness();
    Gfx2d_SetSubBrightness(-10);
}

void MenuErrorMessage::restoreBrightness() { Gfx2d_EndSubObjWinBrightness(); }

MenuLabelButtonBase::MenuLabelButtonBase(u8 a, s32 b) : LabelButton(a, b) {}

MenuLabelButtonBase::~MenuLabelButtonBase() {}

void MenuLabelButtonBase::setOrigin(s32 a, s32 b) { UiWidget::setOrigin(a - 0x80, b - 0x60); }

s32 MenuLabelButton::getAnchorX(s32 k) {
    s32 r = getOriginX();
    s32 x, y;
    if (getState() == 2) {
        getAnimOffset(&x, &y);
        r += x;
    }
    switch (k) {
    case 0:
    case 2:
        r += 0x10;
        break;
    case 1:
    case 3:
        r += 0x20;
    }
    return r;
}

s32 MenuLabelButton::getAnchorY(s32 k) {
    s32 r = getOriginY();
    s32 x, y;
    if (getState() == 2) {
        getAnimOffset(&x, &y);
        r += y;
    }
    switch (k) {
    case 0:
    case 1:
        r += 8;
        break;
    case 2:
        break;
    case 3:
        r += 8;
    }
    return r;
}

BOOL MenuLabelButton::stepAnim() {
    if (isAnimDone() == 0) {
        update();
        return TRUE;
    }
    return FALSE;
}

void MenuLabelButton::setLabel2d(s32 v) {
    LabelString s;
    String_Load2dMenu(&s, v);
    ((LabelButton *)(this))->setLabelText((MsgString *)(&s));
}

void MenuLabelButton::showDefault(s32 v) {
    showAt(v, 0x98, 0xac);
}

void MenuLabelButton::showAt(s32 v, s32 x, s32 y) {
    setLabel2d(v);
    setOrigin(x, y);
    setPos(0, 0);
    showLayer2();
    setState(1);
    update();
}

BOOL MenuLabelButton::isTouched() {
    BOOL c;
    if (gTouchHeld != 0 && gTouchChanged != 0) c = TRUE; else c = FALSE;
    if (c) {
        s32 a = gTouchPressX;
        s32 x = a - getOriginX();
        s32 b = gTouchPressY;
        s32 y = b - getOriginY();
        if (x >= 0 && x <= 0x40 && y >= 0 && y <= 0x18) return TRUE;
    }
    return FALSE;
}

MenuLabelButton::MenuLabelButton() : MenuLabelButtonBase(0, 0) {}

MenuLabelButton::~MenuLabelButton() {}

MenuLabelButtonStyle1::MenuLabelButtonStyle1() : MenuLabelButtonBase(1, 0) {}

MenuLabelButtonStyle1::~MenuLabelButtonStyle1() {}

MenuTextButton::MenuTextButton() {
    cells = 0;
    pressStep = 0;
    flags = 0;
}

MenuTextButton::~MenuTextButton() { caption.destroyLabel(); }

void MenuTextButton::setup(GXOamAttr *p, u8 a, u8 b) {
    cells = p;
    widthTiles = a;
    frameCellCount = b;
}

void MenuTextButton::setLabel(u8 v) {
    msgId = v;
    renderText(0xf, 0);
}

void MenuTextButton::setLabelWithShadow(u8 v) {
    setLabel(v);
    pressStep = 0;
    clearFlags(1);
}

void MenuTextButton::setLabelNoShadow(u8 v) {
    setLabel(v);
    pressStep = 0;
    setFlags(1);
}

void MenuTextButton::renderText(u8 a, u8 b) {
    String_Load2dMenu(&caption, msgId);
    caption.createLabel(8, cells->charNo, widthTiles, a, b, 0);
    caption.redrawAligned(1, 0);
}

BOOL MenuTextButton::testFlags(u32 m) {
    if ((flags & m) != 0) {
        return TRUE;
    }
    return FALSE;
}

void MenuTextButton::setFlags(u32 m) { flags = flags | m; }

void MenuTextButton::clearFlags(u32 m) { flags = flags & ~m; }

void MenuTextButton::freeText() { caption.destroyLabel(); }

u32 MenuTextButton::getPressOffset() { return sTextButtonPressOffsets[pressStep]; }

void MenuTextButton::drawAt(s32 x, s32 y, s32 c) {
    u32 off = getPressOffset();
    s32 pal = -1;
    if (testFlags(4)) {
        pal = 2;
    }
    s32 yy = y + 0x60 + off;
    s32 xx = x + 0x80 + off;
    Oam_DrawCell(1, cells, xx, yy, pal, c, 0x1000, 0x1000, 0, -1, 0, 0);
    if (testFlags(2)) {
        Oam_DrawCell(1, cells, xx, yy, -1, c, 0x1000, 0x1000, 0, 2, 0, 0);
    }
    if (!testFlags(1)) {
        if (pressStep + 1 != 3) {
            x += 0x83;
            y += 0x63;
            Oam_DrawCell(1, cells + frameCellCount, x, y, 1, c, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}

BOOL MenuTextButton::stepPress() {
    if (pressStep == 0) {
        renderText(0xe, 0);
    }
    if (pressStep + 1 < 3) {
        pressStep++;
        goto yes;
    }
    return FALSE;
yes:
    return TRUE;
}

void MenuTextButton::enableObjWindow() { setFlags(2); }

void MenuTextButton::disableObjWindow() { clearFlags(2); }

void MenuTextButton::setDisabled() { setFlags(4); }

void MenuTextButton::setEnabled() { clearFlags(4); }

BOOL MenuTextButton::isDisabled() { return testFlags(4); }

MenuTitleBalloon::MenuTitleBalloon() : LabelBalloon(0) { disablePopAnim(); }

MenuTitleBalloon::~MenuTitleBalloon() {}

void MenuTitleBalloon::setOrigin(s32 a, s32 b) { UiWidget::setOrigin(a - 0x80, b - 0x60); }

void MenuTitleBalloon::showText(u8 a, s32 b, s32 c) {
    setOrigin(b, c);
    setPos(0, 0);
    LabelString t;
    String_Load2dMenu(&t, a);
    setText((StrBuf *)&t);
    disablePopAnim();
    requestOpen();
    update();
    update();
}

void MenuTitleBalloon::hideNow() {
    requestClose();
    update();
    update();
}

MenuBottomButtons::MenuBottomButtons() { layout = 0; }

MenuBottomButtons::~MenuBottomButtons() {}

extern "C" void MenuButtons_LoadTextColors() { GXS_LoadOBJPltt(sMenuButtonTextColors, 0x1c, 4); }

void MenuBottomButtons::freeTexts() {
    for (s32 i = 0; i < 2; i++) {
        buttons[i].freeText();
    }
}

void MenuBottomButtons::drawAt(s32 a) {
    switch (layout) {
    case 0:
        break;
    case 1:
        buttons[1].drawAt(0, a + 0xac, -1);
        break;
    case 2:
        buttons[0].drawAt(0, a + 0xac, -1);
        buttons[1].drawAt(0, a + 0xac, -1);
        break;
    case 3:
        buttons[1].drawAt(0x3c, a + 0x35, -1);
        buttons[0].drawAt(0x3c, a + 0x48, -1);
        break;
    case 4:
        buttons[1].drawAt(0x3c, a + 0x4c, -1);
        buttons[0].drawAt(-0x7c, a + 0x4c, -1);
        break;
    case 5:
        buttons[1].drawAt(0x3c, a + 0x4c, -1);
        break;
    case 6:
        buttons[1].drawAt(0x3c, a + 0x4c, -1);
        buttons[0].drawAt(-0xc, a + 0x4c, -1);
        break;
    case 7:
    case 9:
    case 10: {
        if (layout != 10) {
            title.setPos(0, -(a >> 2));
            title.draw();
        }
        s32 b = a >> 2;
        if (layout == 7) {
            buttons[0].drawAt(0, b, -1);
            buttons[1].drawAt(0, b, -1);
        } else {
            buttons[0].drawAt(-0x50, b + 0x44, -1);
            buttons[1].drawAt(0x10, b + 0x44, -1);
        }
        break;
    }
    case 8: {
        s32 t = -(a >> 2);
        if (layout != 10) {
            title.setPos(0, t - 8);
            title.draw();
        }
        a = (a >> 1) - 0x1e;
        buttons[0].drawAt(0, a, -1);
        buttons[1].drawAt(0, a, -1);
        break;
    }
    case 11: {
        s32 b = a >> 1;
        title.setPos(0, -b);
        title.draw();
        buttons[0].drawAt(-0x50, b + 0x44, -1);
        buttons[1].drawAt(0x10, b + 0x44, -1);
        break;
    }
    case 12: {
        s32 b = a >> 1;
        title.setPos(0, -b);
        title.draw();
        buttons[0].drawAt(-0x50, b + 0x24, -1);
        buttons[1].drawAt(0x10, b + 0x24, -1);
        break;
    }
    case 13: {
        s32 b = a >> 1;
        title.setPos(0, -b);
        title.draw();
        buttons[0].drawAt(-0x50, b + 0x36, -1);
        buttons[1].drawAt(0x10, b + 0x36, -1);
        break;
    }
    }
}

void MenuBottomButtons::hide() { layout = 0; }

void MenuBottomButtons::setLayoutNeverMindConfirm() {
    buttons[0].setup(sButtonCellsW8, 8, 2);
    buttons[0].setLabelWithShadow(2);
    buttons[1].setup(sButtonCellsW6Single, 6, 1);
    buttons[1].setLabelWithShadow(0x21);
    layout = 2;
}

void MenuBottomButtons::setLayoutChangeAddressee() {
    buttons[0].setup(sButtonCellsW12, 0xc, 3);
    buttons[0].setLabelWithShadow(0x20);
    buttons[1].setup(sButtonCellsW6Single, 6, 1);
    buttons[1].setLabelWithShadow(0x21);
    layout = 2;
}

void MenuBottomButtons::setLayoutConfirm() {
    buttons[1].setup(sButtonCellsW6Single, 6, 1);
    buttons[1].setLabelWithShadow(0x21);
    layout = 1;
}

void MenuBottomButtons::setLayoutConfirmQuit03() {
    buttons[1].setup(sButtonCellsW6A, 6, 2);
    buttons[1].setLabelWithShadow(0x21);
    buttons[0].setup(sButtonCellsW6B, 6, 2);
    buttons[0].setLabelWithShadow(0x65);
    layout = 3;
}

void MenuBottomButtons::setLayoutConfirmQuit04() {
    buttons[1].setup(sButtonCellsW6A, 6, 2);
    buttons[1].setLabelWithShadow(0x21);
    buttons[0].setup(sButtonCellsW6B, 6, 2);
    buttons[0].setLabelWithShadow(0x65);
    layout = 4;
}

void MenuBottomButtons::setLayoutSingle05(s32 v) {
    buttons[1].setup(sButtonCellsW6A, 6, 2);
    buttons[1].setLabelWithShadow(v);
    layout = 5;
}

void MenuBottomButtons::setLayoutConfirmAnd06(u8 v) {
    buttons[1].setup(sButtonCellsW6A, 6, 2);
    buttons[1].setLabelWithShadow(0x21);
    buttons[0].setup(sButtonCellsW6B, 6, 2);
    buttons[0].setLabelWithShadow(v);
    layout = 6;
}

void MenuBottomButtonsBody::setLayoutYesNo07(s32 x) {
    title.hideNow();
    ((MenuTitleBalloon *)(&title))->showText(x, 0x80, 4);
    title.hideLayer2();
    buttons[0].setup(sButtonCellsW4B, 4, 1);
    buttons[0].setLabelWithShadow(4);
    buttons[1].setup(sButtonCellsW4A, 4, 1);
    buttons[1].setLabelWithShadow(0x13);
    layout = 7;
}

void MenuBottomButtonsBody::setLayoutYesNo08(s32 x) {
    title.hideNow();
    ((MenuTitleBalloon *)(&title))->showText(x, 0x80, 0x11);
    title.hideLayer2();
    buttons[0].setup(sButtonCellsW4B, 4, 1);
    buttons[0].setLabelWithShadow(4);
    buttons[1].setup(sButtonCellsW4A, 4, 1);
    buttons[1].setLabelWithShadow(0x13);
    layout = 8;
}

void MenuBottomButtonsBody::setYesNoButtons() {
    buttons[0].setup(sButtonCellsW6A, 6, 2);
    buttons[0].setLabelWithShadow(4);
    buttons[1].setup(sButtonCellsW6B, 6, 2);
    buttons[1].setLabelWithShadow(0x13);
}

void MenuBottomButtonsBody::setLayoutYesNo09(s32 x) {
    title.hideNow();
    ((MenuTitleBalloon *)(&title))->showText(x, 0x80, 4);
    title.hideLayer2();
    setYesNoButtons();
    layout = 9;
}

void MenuBottomButtonsBody::setLayoutTossKeep() {
    buttons[0].setup(sButtonCellsW6A, 6, 2);
    buttons[0].setLabelWithShadow(0x15);
    buttons[1].setup(sButtonCellsW6B, 6, 2);
    buttons[1].setLabelWithShadow(0x19);
    layout = 0xa;
}

void MenuBottomButtonsBody::setLayoutYesNo0B(s32 x) {
    title.hideNow();
    ((MenuTitleBalloon *)(&title))->showText(x, 0x80, 0x22);
    title.hideLayer2();
    setYesNoButtons();
    layout = 0xb;
}

void MenuBottomButtonsBody::setLayoutYesNo0C(s32 x) {
    title.hideNow();
    ((MenuTitleBalloon *)(&title))->showText(x, 0x80, 0x2a);
    title.showLayer2();
    setYesNoButtons();
    layout = 0xc;
}

void MenuBottomButtonsBody::setLayoutYesNo0D(s32 x) {
    title.hideNow();
    ((MenuTitleBalloon *)(&title))->showText(x, 0x80, 0x12);
    title.showLayer2();
    setYesNoButtons();
    layout = 0xd;
}

void MenuBottomButtonsBody::showTitleLayer2() {
    title.showLayer2();
}

BOOL MenuBottomButtonsBody::hitTest(s32 idx, s32 x, s32 y) {
    switch (idx) {
    case 1:
        if (x >= 0xc0 && y >= 0x95 && y < 0xa5) {
            return TRUE;
        }
        return FALSE;
    case 2:
        if (x >= 0xc0 && y >= 0xa9 && y < 0xb9) {
            return TRUE;
        }
        return FALSE;
    case 0:
        if (x >= 0x52 && x <= 0xba && y >= 0xac && y <= 0xc0) {
            return TRUE;
        }
        return FALSE;
    case 3:
        if (y >= 0xa4 && y < 0xb4 && x >= 0x38 && x <= 0x68) {
            return TRUE;
        }
        return FALSE;
    case 4:
        if (y >= 0xa4 && y < 0xb4 && x >= 0x98 && x <= 0xc8) {
            return TRUE;
        }
        return FALSE;
    case 5:
        if (y >= 0xac && y <= 0xc0 && x >= 0 && x <= 0x40) {
            return TRUE;
        }
        return FALSE;
    case 6:
        if (y >= 0xac && y <= 0xc0 && x >= 0xc0 && x <= 0x100) {
            return TRUE;
        }
        return FALSE;
    case 7:
        if (y >= 0xac && y <= 0xc0 && x >= 0x78 && x <= 0xb8) {
            return TRUE;
        }
        return FALSE;
    case 8:
        if (x >= 0x6a && x <= 0xbc && y >= 0xac && y <= 0xc0) {
            return TRUE;
        }
        return FALSE;
    case 9:
        if (x >= 0xc0 && y >= 0 && y >= 0xac && y <= 0xc0) {
            return TRUE;
        }
        return FALSE;
    default:
        return FALSE;
    }
}

BOOL MenuBottomButtonsBody::isTouched(s32 idx) {
    s32 x = gTouchCurX;
    s32 y = gTouchCurY;
    switch (layout) {
    case 8:
        y += 0x1e;
        break;
    case 0xc:
        y += 0x20;
        break;
    case 0xd:
        y += 0xe;
        break;
    }
    return hitTest(idx, x, y);
}

s32 MenuBottomButtonsBody::getTargetX(s32 idx) {
    if (idx == -1) {
        idx = selectedTarget;
    }
    return sBottomButtonTargetX[idx];
}

s32 MenuBottomButtonsBody::getTargetY(s32 idx) {
    if (idx == -1) {
        idx = selectedTarget;
    }
    s32 v = sBottomButtonTargetY[idx];
    switch (layout) {
    case 8:
        v -= 0x1e;
        break;
    case 0xc:
        v -= 0x20;
        break;
    case 0xd:
        v -= 0xe;
        break;
    }
    return v;
}

void MenuBottomButtonsBody::setSelected(u8 v) {
    selectedTarget = v;
}

BOOL MenuBottomButtonsBody::stepPress() {
    return buttons[getButtonOfTarget(-1)].stepPress();
}

s32 MenuBottomButtonsBody::getPressOffset() {
    return buttons[getButtonOfTarget(-1)].getPressOffset();
}

void MenuBottomButtonsBody::enableObjWindow() {
    title.enableObjWindow();
    for (s32 i = 0; i < 2; i++) {
        buttons[i].enableObjWindow();
    }
}

void MenuBottomButtonsBody::disableObjWindow() {
    title.disableObjWindow();
    for (s32 i = 0; i < 2; i++) {
        buttons[i].disableObjWindow();
    }
}

s32 MenuBottomButtonsBody::getButtonOfTarget(s32 idx) {
    if (idx == -1) {
        idx = selectedTarget;
    }
    return sBottomButtonOfTarget[idx];
}

void MenuBottomButtonsBody::disableButton(s32 idx) {
    buttons[getButtonOfTarget(idx)].setDisabled();
}

void MenuBottomButtonsBody::enableButton(s32 idx) {
    buttons[getButtonOfTarget(idx)].setEnabled();
}

BOOL MenuBottomButtonsBody::isButtonDisabled(s32 idx) {
    return buttons[getButtonOfTarget(idx)].isDisabled();
}

#include "host_overlay_vars.h"

HOST_OVERLAY_VARS(unk_ov002_02202fac) {
    HOST_OVERLAY_VAR(sButtonCellsW8),
    HOST_OVERLAY_VAR(sButtonCellsW4A),
    HOST_OVERLAY_VAR(sButtonCellsW6A),
    HOST_OVERLAY_VAR(sButtonCellsW6B),
    HOST_OVERLAY_VAR(sButtonCellsW12),
    HOST_OVERLAY_VAR(sButtonCellsW6Single),
    HOST_OVERLAY_VAR(sButtonCellsW4B),
    HOST_OVERLAY_VARS_END
};

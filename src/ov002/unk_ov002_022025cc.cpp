#include "ds_div.h"
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
#include "menu/MenuTextButton.h"
#include "menu/MenuTitleBalloon.h"
#include "menu/MenuLabelButton.h"
#include "menu/MenuCursor.h"
#include "menu/MenuScrollKnob.h"
#include "menu/PopupChoiceRow.h"
#include "menu/MenuBottomButtons.h"
#include "menu/PopupChoiceMenu.h"
#include "talk/TalkMsgRequest.h"
#include "menu/MenuErrorMessage.h"
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


extern "C" void Menu_PlayScrollTickSe() { Snd_PlaySe(0x19); }

extern "C" void Menu_PlayScrollGrabSe() { Snd_PlaySe(0x33); }

extern "C" void Menu_LoadPaperBg(s32 a, u32 b) {
    Heap *h = gCurrentHeap;
    char buf[0x20];
    Str_SPrintf(buf, "menu/paper/chr/%03d.bch", a);
    Gfx2d_LoadCharFile(buf, h, b, 0x10, 0x10, 0x74);
    Str_SPrintf(buf, "menu/paper/scr/%03d.bsc", a);
    Gfx2d_LoadScreenFile(buf, h, b);
    Str_SPrintf(buf, "menu/paper/plt/%03d.bpl", a, a);
    Gfx2d_LoadPaletteFile(buf, h, b, 0xc, 0xc, 0xe);
}

MenuCursor::MenuCursor(BOOL flag) : MenuCursorBase(flag) {
    setAnim(0);
    motion.reset();
    priority = 0;
    enableObjWindow();
}

MenuCursor::~MenuCursor() {}

void MenuCursor::setAnimIfChanged(s32 idx) {
    if (idx != getAnim() || idx == 6 || idx == 0xc) {
        setAnim(idx);
    }
}

void MenuCursor::switchToAnim07() {
    if (getAnim() == 1) {
        s32 a = getFrameScreenX();
        s32 b = getFrameScreenY();
        warpTo(a + 0x10, b);
    } else if (getAnim() == 0xd) {
        s32 a = getFrameScreenX();
        s32 b = getFrameScreenY();
        warpTo(a + 4, b + 0x18);
    }
    setAnimIfChanged(7);
}

void MenuCursor::switchToAnim01() {
    if (getAnim() == 7) {
        s32 a = getFrameScreenX();
        s32 b = getFrameScreenY();
        warpTo(a - 0x10, b);
    } else if (getAnim() == 0xd) {
        s32 a = getFrameScreenX();
        s32 b = getFrameScreenY();
        warpTo(a - 0xc, b + 0x18);
    }
    setAnimIfChanged(1);
}

void MenuCursor::switchToAnim0D() {
    if (getAnim() == 1) {
        s32 a = getFrameScreenX();
        s32 b = getFrameScreenY();
        warpTo(a + 0xc, b - 0x18);
    } else if (getAnim() == 7) {
        s32 a = getFrameScreenX();
        s32 b = getFrameScreenY();
        warpTo(a - 4, b - 0x18);
    }
    setAnimIfChanged(0xd);
}

void MenuCursor::setPosePress() {
    switch (getAnim()) {
    case 0:
        break;
    case 1:
    case 2:
    case 3:
        setAnim(2);
        break;
    case 7:
    case 8:
    case 9:
        setAnim(8);
        break;
    case 13:
    case 14:
    case 15:
        setAnim(0xe);
        break;
    case 16:
    case 17:
    case 18:
        setAnim(0x11);
        break;
    case 4:
    case 5:
    case 6:
    case 10:
    case 11:
    case 12:
    default:
        setAnim(8);
        break;
    }
}

void MenuCursorBase::setPoseRelease() {
    switch (getAnim()) {
    case 0:
        break;
    case 1:
    case 2:
    case 3:
        setAnim(3);
        break;
    case 7:
    case 8:
    case 9:
        setAnim(9);
        break;
    case 13:
    case 14:
    case 15:
        setAnim(0xf);
        break;
    case 16:
    case 17:
    case 18:
        setAnim(0x12);
        break;
    default:
        setAnim(9);
        break;
    }
}

void MenuCursorBase::setPoseIdle() {
    switch (getAnim()) {
    case 0:
        break;
    case 1:
    case 2:
    case 3:
        setAnim(1);
        break;
    case 7:
    case 8:
    case 9:
        setAnim(7);
        break;
    case 13:
    case 14:
    case 15:
        setAnim(0xd);
        break;
    case 16:
    case 17:
    case 18:
        setAnim(0x10);
        break;
    default:
        setAnim(9);
        break;
    }
}

void MenuCursorBase::setScreenPos(s32 x, s32 y) {
    setPos(x - 0x80, y - 0x60);
}

void MenuCursorBase::warpTo(s32 x, s32 y) {
    motion.stop();
    motion.setPos(x, y);
    setScreenPos(x, y);
}

void MenuCursorBase::moveToLinear(s32 x, s32 y, s32 n) {
    Snd_PlaySe(0xb);
    motion.startLinear(x, y, n);
}

void MenuCursorBase::moveToEase(s32 x, s32 y, s32 n, s32 f) {
    if (f != 0) {
        Snd_PlaySe(0xb);
    }
    motion.startEase(x, y, n);
}

void MenuCursorBase::moveToNear(s32 x, s32 y, s32 n, u8 e) {
    s32 dx = x - (posX + getOriginX());
    Snd_PlaySe(0xb);
    if (dx >= -0x30 && dx <= 0x30) {
        s32 dy = y - (posY + getOriginY());
        if (dy >= -0x30 && dy <= 0x30) {
            n = e;
        }
    }
    motion.startEase(x, y, n);
}

BOOL MenuCursorBase::isGripping() {
    switch (getAnim()) {
    case 4:
    case 10:
        if (layer1.getFrameIndex() >= 4) {
            return TRUE;
        }
        return FALSE;
    case 5:
    case 11:
        if (layer1.getFrameIndex() < 3) {
            return TRUE;
        }
        return FALSE;
    case 6:
    case 12:
        return TRUE;
    case 7:
    case 8:
    case 9:
    default:
        return FALSE;
    }
}

BOOL MenuCursorBase::func_ov002_022028fc() {
    s32 t = getAnim();
    if (t == 6 || t == 0xc) {
        if (layer1.getFrameIndex() == 2) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

BOOL MenuCursorBase::isMoving() {
    return motion.isMoving();
}

s32 MenuCursorBase::getFrameScreenX() {
    s32 t = layer1.getFrameX(-1);
    return t + (posX + getOriginX());
}

s32 MenuCursorBase::getFrameScreenY() {
    s32 t = layer1.getFrameY(-1);
    return t + (posY + getOriginY());
}

s32 MenuCursorBase::getScreenX() {
    return posX + getOriginX();
}

s32 MenuCursorBase::getScreenY() {
    return posY + getOriginY();
}

void MenuCursorBase::drawWrapped() {
    HandCursor::draw();
    s32 old = posX;
    if (old + getOriginX() > 0xe0) {
        posX -= 0x100;
        HandCursor::draw();
        posX = old;
    }
}

void MenuCursorBase::update() {
    motion.update();
    s32 x = motion.getX();
    s32 y = motion.getY();
    setScreenPos(x, y);
    if (isAnimDone()) {
        if (getAnim() == 5) {
            setAnim(1);
        } else if (getAnim() == 0xb) {
            setAnim(7);
        }
    }
    HandCursor::update();
}

CursorMotion::CursorMotion() {}

CursorMotion::~CursorMotion() {}

void CursorMotion::reset() {
    mode = 0;
}

BOOL CursorMotion::update() {
    if (mode != 2 && mode != 3) {
        return TRUE;
    }
    if (framesLeft != 0) {
        framesLeft--;
        switch (mode) {
        case 2:
            posX += stepX;
            posY += stepY;
            break;
        case 3:
            posX += stepX;
            posY += stepY;
            if (framesLeft > 1) {
                stepX >>= 1;
                stepY >>= 1;
            }
            break;
        }
        while (posX < 0) {
            posX += 0x1000;
        }
        while (posX > 0x1000) {
            posX -= 0x1000;
        }
    }
    if (framesLeft == 0) {
        return TRUE;
    }
    return FALSE;
}

s32 CursorMotion::getX() {
    return posX >> 4;
}

s32 CursorMotion::getY() {
    return posY >> 4;
}

void CursorMotion::stop() {
    mode = 1;
}

void CursorMotion::setPos(s32 x, s32 y) {
    posX = x << 4;
    posY = y << 4;
}

void CursorMotion::startLinear(s32 x, s32 y, s32 n) {
    mode = 2;
    x = x << 4;
    stepX = DS_DIV((x - posX), n);
    y = y << 4;
    stepY = DS_DIV((y - posY), n);
    framesLeft = n;
}

void CursorMotion::startEase(s32 x, s32 y, s32 n) {
    if (n == 1) {
        startLinear(x, y, 1);
    } else {
        mode = 3;
        s32 t = x << 4;
        stepX = (t - posX) >> 1;
        y = y << 4;
        stepY = (y - posY) >> 1;
        framesLeft = n;
    }
}

BOOL CursorMotion::isMoving() {
    BOOL r = FALSE;
    BOOL m = TRUE;
    if (mode != 2 && mode != 3) {
        m = FALSE;
    }
    if (m && framesLeft != 0) {
        r = TRUE;
    }
    return r;
}


MenuCursorBuf0::MenuCursorBuf0() : MenuCursor(0) {}

MenuCursorBuf0::~MenuCursorBuf0() {}

MenuCursorBuf1::MenuCursorBuf1() : MenuCursor(1) {}

MenuCursorBuf1::~MenuCursorBuf1() {}

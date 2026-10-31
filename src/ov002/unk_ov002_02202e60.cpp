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
#include "proto/ov002/unk_ov002_02202e60.h"
#include "proto/ov002/unk_ov002_02202fac.h"


void operator delete(void *p);


MenuScrollKnob::MenuScrollKnob() : ScrollKnob(0) {
    setState(0);
}

MenuScrollKnob::~MenuScrollKnob() {
}

BOOL MenuScrollKnob::hitTest(s32 x, s32 y) {
    s32 dx = x - getScreenX();
    s32 dy = y - getScreenY();
    BOOL r;
    if (dx < 0 || dx > 0x10) {
        r = FALSE;
    } else if (dy < 0 || dy > 0x10) {
        r = FALSE;
    } else {
        r = TRUE;
    }
    return r;
}

void MenuScrollKnob::show() { setState(1); }

void MenuScrollKnob::grab() { setState(2); }

void MenuScrollKnob::release() { setState(3); }

void MenuScrollKnob::updateRelease() {
    if (getState() == 3) {
        if (areAnimsDone()) {
            show();
        }
    }
}

s32 MenuScrollKnob::getScreenX() {
    return layer1 + getOriginX();
}

s32 MenuScrollKnob::getScreenY() {
    return posY + getOriginY();
}

s32 MenuScrollKnob::getGripX() {
    s32 a, b;
    getAnimOffset(&a, &b);
    s32 t = getScreenX();
    return a + t + 7;
}

s32 MenuScrollKnob::getGripY() {
    s32 a, b;
    getAnimOffset(&a, &b);
    s32 t = getScreenY();
    return b + t + 7;
}

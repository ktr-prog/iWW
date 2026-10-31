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
#include "proto/ov002/unk_ov002_02200680.h"
#include "proto/ov002/unk_ov002_02200840.h"
#include "proto/ov002/unk_ov002_022013ac.h"
#include "proto/ov002/unk_ov002_022025cc.h"
#include "proto/ov002/unk_ov002_02202fac.h"


void operator delete(void *p);


TouchPromptBalloon::TouchPromptBalloon() : LabelBalloon(0) {
    promptState = 0;
    setClampToScreen(1);
    enableCenterText();
    openQueued = 0;
    autoCloseTimer = 0;
}

TouchPromptBalloon::~TouchPromptBalloon() {}

s32 TouchPromptBalloon::updatePrompt() {
    s32 r = 0;
    if (autoCloseTimer != 0) {
        autoCloseTimer = autoCloseTimer - 1;
        if (autoCloseTimer == 0) {
            if (promptState == 3) {
                hide(r);
            }
        }
    }
    switch (promptState) {
    case 1:
        if (getState() != 0) {
            requestClose();
        } else {
            r = 1;
            promptState = 2;
        }
        break;
    case 2:
        if (requestOpen() != 0) {
            promptState = 3;
        }
        break;
    case 4:
        if (getState() == 0 || requestClose() != 0) {
            promptState = 0;
        }
        break;
    }
    LabelBalloon::update();
    return r;
}

BOOL TouchPromptBalloon::hide(s32 a) {
    autoCloseTimer = 0;
    if (a != 0) {
        cancelQueuedOpen();
    }
    if (getState() == 0) {
        promptState = 0;
        return TRUE;
    }
    promptState = 4;
    return FALSE;
}

void TouchPromptBalloon::commitOpen() {
    autoCloseTimer = 0;
    if (openQueued != 0) {
        promptState = 1;
    }
    openQueued = 0;
}

void TouchPromptBalloon::queueOpen() { openQueued = 1; }

void TouchPromptBalloon::cancelQueuedOpen() { openQueued = 0; }

void TouchPromptBalloon::setPriority(s32 v) { priority = v; }

void TouchPromptBalloon::setAutoCloseTimer(u8 v) { autoCloseTimer = v; }


BOOL TouchPromptBalloon::isOpenOrOpening() {
    if (getState() == 2 || getState() == 1) {
        return TRUE;
    }
    return FALSE;
}

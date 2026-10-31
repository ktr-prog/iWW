#include "types.h"
#include "save/TownExchangeRecord.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "item/Letter.h"
#include "item/ReceivedLetterBlock.h"
#include "ui/InputModeIcon.h"
#include "item/LetterView.h"
#include "proto/main/unk_02065330.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0208eeac.h"


InputModeIcon sInputModeIcon;


ReceivedLetterBlock::ReceivedLetterBlock() {}

ReceivedLetterBlock::~ReceivedLetterBlock() {}

extern "C" void ReceivedLetter_Clear(void *p) { Letter_Clear((LetterView *)p); }

extern "C" BOOL ReceivedLetter_HasLetter(void *p) {
    if (((LetterView *)(p))->getState()) {
        return TRUE;
    }
    return FALSE;
}

void TownExchangeRecord::setChecksumByte(u32 v) { constellation[0] = v; }

u8 TownExchangeRecord::getChecksumByte() { return constellation[0]; }

extern "C" void *ReceivedLetter_GetLetter(void *p) { return p; }

extern "C" void InputMode_Clear() { sInputModeIcon.inputMode = 0; }

extern "C" void InputMode_SetButtons() { sInputModeIcon.inputMode = 1; }

extern "C" void InputMode_SetTouch() { sInputModeIcon.inputMode = 2; }

extern "C" BOOL InputMode_IsButtons() {
    if (sInputModeIcon.inputMode == 1) {
        return TRUE;
    }
    return FALSE;
}

extern "C" BOOL InputMode_IsTouch() {
    if (sInputModeIcon.inputMode == 2) {
        return TRUE;
    }
    return FALSE;
}

extern "C" void InputModeIcon_Init() { sInputModeIcon.init(); }

extern "C" void InputModeIcon_Exit() { sInputModeIcon.exit(); }

extern "C" void InputModeIcon_Update() { sInputModeIcon.update(); }

extern "C" void InputModeIcon_Draw() { sInputModeIcon.draw(); }

void InputModeIcon::draw() {
    if (isVisible != 0) {
        if (!isDrawBlocked()) {
            GXOamAttr *h = anim.getCell();
            s32 x = getOriginX() + anim.getFrameX(-1);
            s32 y = getOriginY() + anim.getFrameY(-1);
            Oam_DrawCell(3, h, x, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}

void InputModeIcon::update() {
    if (isVisible != 0) {
        anim.update();
    }
    if (inputMode != shownMode) {
        startModeAnim();
        shownMode = inputMode;
    }
}

InputModeIcon::InputModeIcon() : inputMode(0), shownMode(0) {
    isVisible = 0;
}

InputModeIcon::~InputModeIcon() {
}


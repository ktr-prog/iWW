#include "types.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/TalkArrow.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02089330.h"

TalkArrow::TalkArrow(u8 flag) {
    state = 0;
    offsetX = 0;
    offsetY = 0;
    useAltStyle = 0;
    unk_41 = flag;
    setState(0);
}

TalkArrow::~TalkArrow() {}

void TalkArrow::draw() {
    if (state != 0) {
        GXOamAttr *a = anim.getCell();
        GXOamAttr *b = subAnim.getCell();
        s32 ox0 = anim.getFrameX(-1);
        s32 oy0 = anim.getFrameY(-1);
        s32 ox1 = subAnim.getFrameX(-1);
        s32 oy1 = subAnim.getFrameY(-1);
        s32 x = offsetX + getOriginX();
        s32 y = offsetY + getOriginY();
        if (unk_41 != 0) {
            Oam_DrawCell(0, a, x + ox0, y + oy0, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            Oam_DrawCell(0, b, x + ox1, y + oy1, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            Oam_DrawCell(1, a, x + ox0, y + oy0, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            Oam_DrawCell(1, b, x + ox1, y + oy1, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}

void TalkArrow::update() {
    if (state != 0) {
        anim.update();
        subAnim.update();
    }
}


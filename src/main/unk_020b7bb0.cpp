#include "types.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/LabelBalloon.h"
#include "ui/FieldInfoLabelBalloon.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_020b7bb0.h"

FieldInfoLabelBalloon::FieldInfoLabelBalloon() : LabelBalloon(1) {
    blinkFrame = 0;
    markerRequest = 0;
    markerShown = 0;
    markerDrawn = 0;
    markerDrawnPrev = 0;
    blinkEnabled = 0;
}

FieldInfoLabelBalloon::~FieldInfoLabelBalloon() {
}

void FieldInfoLabelBalloon::draw() {
    s32 x, y;
    s32 drawn = 0;
    if (blinkFrame < 0x19) {
        if (markerShown != 0) {
            GXOamAttr *cell = markerAnim.getCell();
            SpriteAnim *anim = getAnim();
            x = getDrawX();
            s32 b = getDrawY();
            x = x + anim->getFrameX(-1) + markerAnim.getFrameX(-1);
            y = b + anim->getFrameY(-1) + markerAnim.getFrameY(-1);
            Oam_DrawCell(0, cell, x, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
            drawn = 1;
        }
        LabelBalloon::draw();
    }
    markerDrawn = drawn;
}

void FieldInfoLabelBalloon::update() {
    markerDrawnPrev = markerDrawn;
    LabelBalloon::update();
    updateBlink();
}

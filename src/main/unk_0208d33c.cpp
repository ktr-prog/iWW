#include "types.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/HandCursor.h"
#include "talk/ChatBalloonText.h"
#include "ui/NameLabelBalloon.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0208d33c.h"

extern u8 sNameLabelBalloonKind4Color[];
extern s32 kNameLabelBalloonKindAnims[];
extern s32 sHandCursorAnimSeqIds[];
extern u8 sHandCursorAnimLoops[];
extern u8 sHandCursorAnimHasLayer2[];
extern s32 sScrollKnobSeqIds[];
extern s32 sScrollKnobPlayOnce[];
extern u8 data_020d5b0c[];


s32 HandCursor::getAnim() {
    return anim;
}

BOOL HandCursor::isAnimDone() {
    BOOL r = FALSE;
    if (layer1.isFinished()) {
        BOOL t;
        if (hasLayer2 != 0) {
            t = layer2.isFinished();
        } else {
            t = TRUE;
        }
        if (t) {
            r = TRUE;
        }
    }
    return r;
}

NameLabelBalloon::NameLabelBalloon() : kind(0), seqIndex(10), offsetX(0), offsetY(0), slideY(0), alignX(0) {
    textLabel = 0;
    state = 0;
    showRequested = 0;
    stateTimer = 0;
    isVisible = 0;
}

NameLabelBalloon::~NameLabelBalloon() {
    release();
}

void NameLabelBalloon::draw() {
    if (isVisible != 0) {
        GXOamAttr *h = anim.getCell();
        s32 a = getOriginX();
        s32 b = anim.getFrameX(-1);
        s32 x = alignX + (offsetX + a);
        x += b;
        s32 c = getOriginY();
        s32 d = anim.getFrameY(-1);
        s32 y = slideY + (offsetY + c);
        y += d;
        Oam_DrawCell(0, h, x, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void NameLabelBalloon::update() {
    Fn p0 = &NameLabelBalloon::updateShown;
    static Fn tbl[4] = {&NameLabelBalloon::updateHidden, &NameLabelBalloon::updateAppearing, &NameLabelBalloon::updateShown, &NameLabelBalloon::updateHiding};
    Fn q0 = &NameLabelBalloon::updateShown;
    Fn q1 = &NameLabelBalloon::updateShown;
    Fn q2 = &NameLabelBalloon::updateShown;
    (this->*tbl[state])();
    if (state != 0) {
        anim.update();
    }
}



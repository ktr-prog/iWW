#include "types.h"
#include "host_tick.h"
#include "text/Unk_02050288.h"
#include "talk/MsgStringBase.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "talk/LabelBalloonText.h"
#include "ui/LabelBalloon.h"
#include "proto/main/unk_020501d4.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_02089508.h"
#include "proto/main/unk_020d5ce4.h"

extern "C" {
TextLabel *MsgTextLabel_CreateVram(u32 a, s32 b, s32 c);
void MsgTextLabel_Destroy(TextLabel *obj);
}


typedef void (LabelBalloon::*Unk_020e0d98_Fn)();

void UiWidget::setOrigin(s32 a, s32 b) {
    originX = a + 0x80;
    originY = b + 0x60;
}

s32 UiWidget::getOriginX() { return originX; }

s32 UiWidget::getOriginY() { return originY; }

LabelBalloonText::LabelBalloonText() { StrBuf_Clear((StrBuf *)this); }

LabelBalloonText::~LabelBalloonText() {}

u32 LabelBalloonText::capacity() { return 0x21; }


u8 *LabelBalloonText::data() { return unk_04; }

LabelBalloon::LabelBalloon(s32 flag)
    : state(0), animTimer(0), x(0), posY(0), priority(-1), popOffsetX(0), popOffsetY(0), clampOffsetX(0), openRequest(0),
      closeRequest(0), onBufferA(flag), clampToScreen(0), objWindow(0), noPopAnim(0), popDownward(0), layer2Visible(0), centerText(0), label(0),
      label2(0), textMode(0) {
    initAnims();
    enterClosed();
}

LabelBalloon::~LabelBalloon() { freeLabels(); }

void LabelBalloon::draw() {
    if (state != 0) {
        GXOamAttr *h0 = layer1.getCell();
        GXOamAttr *h1 = layer2.getCell();
        s32 base = getDrawX();
        s32 base2 = getDrawY();
        s32 x0 = base + layer1.getFrameX(-1);
        s32 y0 = base2 + layer1.getFrameY(-1);
        s32 x1 = base + layer2.getFrameX(-1);
        s32 y1 = base2 + layer2.getFrameY(-1);
        if (onBufferA != 0) {
            Oam_DrawCell(0, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            if (layer2Visible != 0) {
                Oam_DrawCell(0, h1, x1, y1, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            }
            if (objWindow != 0) {
                Oam_DrawCell(0, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                if (layer2Visible != 0) {
                    Oam_DrawCell(0, h1, x1, y1, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                }
            }
        } else {
            Oam_DrawCell(1, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            if (layer2Visible != 0) {
                Oam_DrawCell(1, h1, x1, y1, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            }
            if (objWindow != 0) {
                Oam_DrawCell(1, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                if (layer2Visible != 0) {
                    Oam_DrawCell(1, h1, x1, y1, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                }
            }
        }
    }
}

void LabelBalloon::update() {
    static Unk_020e0d98_Fn tbl[4] = {&LabelBalloon::updateClosed, &LabelBalloon::updateOpening,
                                     &LabelBalloon::updateOpen, &LabelBalloon::updateClosing};
    (this->*tbl[state])();
    if (state != 0) {
        layer1.update();
        layer2.update();
        updateScreenClamp();
    }
}

void LabelBalloon::enableObjWindow() { objWindow = 1; }

void LabelBalloon::disableObjWindow() { objWindow = 0; }

void LabelBalloon::disablePopAnim() { noPopAnim = 1; }

void LabelBalloon::setPopDownward() { popDownward = 1; }

void LabelBalloon::setPopUpward() { popDownward = 0; }

void LabelBalloon::showLayer2() { layer2Visible = 1; }

void LabelBalloon::hideLayer2() { layer2Visible = 0; }

void LabelBalloon::setPos(s32 a, s32 b) {
    x = a;
    posY = b;
}

void LabelBalloon::setText(StrBuf *src) {
    StrBuf_Copy((StrBuf *)&text, src);
    textMode = 1;
}

void LabelBalloon::enableCenterText() { centerText = 1; }

void LabelBalloon::setClampToScreen(u8 v) { clampToScreen = v; }

void LabelBalloon::refreshText(s32 flag) {
    TextLabel *p = label;
    if (p) {
        p->textStart = text.data();
        label->requestRedraw();
    }
    p = label2;
    if (p) {
        p->textStart = text2.data();
        label2->requestRedraw();
    }
    if (flag) {
        fitToText();
    }
}

BOOL LabelBalloon::requestOpen() {
    BOOL r = state == 0 ? TRUE : FALSE;
    if (r) {
        openRequest = 1;
    }
    return r;
}

BOOL LabelBalloon::requestClose() {
    BOOL r = state == 2 ? TRUE : FALSE;
    if (r) {
        closeRequest = 1;
    }
    return r;
}

void LabelBalloon::enterClosed() { state = 0; }

void LabelBalloon::updateClosed() {
    if (openRequest != 0) {
        openRequest = 0;
        createLabels();
        fitToText();
        enterOpening();
    }
}

void LabelBalloon::enterOpening() {
    if (noPopAnim != 0) {
        animTimer = 1;
        popOffsetX = 0;
        popOffsetY = 0;
    } else {
        animTimer = 3;
        popOffsetX = -5;
        s32 v = -5;
        if (popDownward == 0) {
            v = 5;
        }
        popOffsetY = v;
    }
    state = 1;
}

void LabelBalloon::updateOpening() {
    if (noPopAnim == 0) {
        if (animTimer > 2) {
            popOffsetX += 6;
            s32 d;
            if (popDownward != 0) {
                d = 6;
            } else {
                d = -6;
            }
            popOffsetY += TICK_PART(d);
        } else {
            popOffsetX -= 1;
            s32 d;
            if (popDownward != 0) {
                d = -1;
            } else {
                d = 1;
            }
            popOffsetY += TICK_PART(d);
        }
    }
    animTimer -= TICK_STEP_ENDS() ? 1 : 0;
    if (animTimer <= 0) {
        popOffsetX = 0;
        popOffsetY = 0;
        enterOpen();
    }
}

void LabelBalloon::enterOpen() { state = 2; }

void LabelBalloon::updateOpen() {
    if (closeRequest != 0) {
        closeRequest = 0;
        enterClosing();
    }
}

void LabelBalloon::enterClosing() {
    if (noPopAnim != 0) {
        animTimer = 1;
    } else {
        animTimer = 2;
    }
    state = 3;
}

void LabelBalloon::updateClosing() {
    if (noPopAnim == 0) {
        popOffsetX -= 11;
        s32 d;
        if (popDownward != 0) {
            d = -11;
        } else {
            d = 11;
        }
        popOffsetY += TICK_PART(d);
    }
    animTimer -= TICK_STEP_ENDS() ? 1 : 0;
    if (animTimer <= 0) {
        freeLabels();
        enterClosed();
    }
}

s32 LabelBalloon::getState() { return state; }

SpriteAnim *LabelBalloon::getAnim() { return &layer1; }

s32 LabelBalloon::getDrawX() { return clampOffsetX + (popOffsetX + (x + getOriginX())); }

s32 LabelBalloon::getDrawY() { return popOffsetY + (posY + getOriginY()); }

s32 LabelBalloon::getPosX() { return x; }

s32 LabelBalloon::getPosY() { return posY; }

s32 LabelBalloon::getWidth() { return layer1.getFrameIndex() * 8 + 0x18; }

void LabelBalloon::reset() {
    state = 0;
    animTimer = 0;
    x = 0;
    posY = 0;
    priority = -1;
    popOffsetX = 0;
    popOffsetY = 0;
    clampOffsetX = 0;
    openRequest = 0;
    closeRequest = 0;
    clampToScreen = 0;
    objWindow = 0;
    noPopAnim = 0;
    popDownward = 0;
    layer2Visible = 0;
    centerText = 0;
    StrBuf_Clear((StrBuf *)&text);
    StrBuf_Clear((StrBuf *)&text2);
    textMode = 0;
    freeLabels();
}

void LabelBalloon::initAnims() {
    layer1.setSeq(data_020d5ce4);
    layer1.setPlayOnce(1);
    layer1.setSpeed(0);
    layer2.setSeq(data_020d5cec);
    layer2.setPlayOnce(1);
    layer2.setSpeed(0);
}

void LabelBalloon::fitToText() {
    u32 w0;
    u32 w1;
    u32 n;
    s32 hi;
    s32 lo;
    if (label != NULL) {
        w0 = label->measureWidth();
    } else {
        w0 = 0;
    }
    if (label2 != NULL) {
        u32 t1 = label2->measureWidth();
        w1 = t1;
    } else {
        w1 = 0;
    }
    n = (w0 + 7) >> 3;
    n = n > ((w1 + 7) >> 3) ? n : ((w1 + 7) >> 3);
    hi = layer1.getSeq()->frameCount - 1;
    lo = n - 1;
    if (lo < 0) {
        hi = 0;
    } else if (lo <= hi) {
        hi = lo;
    }
    layer1.setFrame(hi, 0);
    layer2.setFrame(hi, 0);
    if (centerText != 0) {
        u32 full = n * 8;
        if (label != NULL) {
            label->xOffset = full > w0 ? (full - w0) >> 1 : 0;
        }
        if (label2 != NULL) {
            label2->xOffset = full > w1 ? (full - w1) >> 1 : 0;
        }
    } else {
        if (label != NULL) {
            label->xOffset = 0;
        }
        if (label2 != NULL) {
            label2->xOffset = 0;
        }
    }
}

void LabelBalloon::createLabels() {
    BOOL two;
    if (textMode == 2) {
        two = TRUE;
    } else {
        two = FALSE;
    }
    if (label == NULL) {
        label = MsgTextLabel_CreateVram(0x41, 0x14, 2);
        if (label != NULL) {
            label->vramLoader = 4;
            TextLabel *t = label;
            t->textStart = ((StrBuf *)&text)->data();
            label->group = 1;
            if (onBufferA != 0) {
                label->copyMode = 2;
            }
            if (two) {
                label->font = (GameFontDesc *)&gFontB;
            } else {
                label->font = (GameFontDesc *)&gFontA;
            }
            label->rowStride1K = 1;
            label->bgColor = 0;
            label->fgColor = 3;
            label->requestRedraw();
        }
    }
    if (label2 == NULL && two) {
        label2 = MsgTextLabel_CreateVram(0x61, 0x14, 2);
        if (label2 != NULL) {
            label2->vramLoader = 4;
            TextLabel *t = label2;
            t->textStart = ((StrBuf *)&text2)->data();
            label2->group = 1;
            if (onBufferA != 0) {
                label2->copyMode = 2;
            }
            label2->font = (GameFontDesc *)&gFontB;
            label2->rowStride1K = 1;
            label2->bgColor = 0;
            label2->fgColor = 3;
            label2->requestRedraw();
        }
    }
}

void LabelBalloon::freeLabels() {
    if (label != NULL) {
        MsgTextLabel_Destroy(label);
        label = NULL;
    }
    if (label2 != NULL) {
        MsgTextLabel_Destroy(label2);
        label2 = NULL;
    }
}

void LabelBalloon::updateScreenClamp() {
    if (clampToScreen != 0) {
        s32 w = layer1.getFrameIndex() * 4 + 12;
        s32 c = x + popOffsetX;
        s32 lo = c - w + 0x80;
        s32 hi = w + c - 0x80;
        if (lo < 0) {
            clampOffsetX = -lo;
        } else if (hi > 0) {
            clampOffsetX = -hi;
        } else {
            clampOffsetX = 0;
        }
    } else {
        clampOffsetX = 0;
    }
}


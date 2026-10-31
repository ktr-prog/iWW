#include "types.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/HandCursor.h"
#include "ui/ScrollKnob.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0208d64c.h"

s32 ScrollKnob::getState() {
    return state;
}

BOOL ScrollKnob::areAnimsDone() {
    BOOL r;
    if (layerAnim1.isFinished() && priority.isFinished()) {
        r = TRUE;
    } else {
        r = FALSE;
    }
    return r;
}

HandCursor::HandCursor(BOOL flag) : posX(0), posY(0), priority(-1) {
    anim = 0;
    unk_44 = 0x16;
    onBufferA = flag;
    hasLayer2 = 1;
    objWindow = 0;
    setAnim(0);
}

HandCursor::~HandCursor() {
}

void HandCursor::draw() {
    GXOamAttr *h0;
    s32 x, y, y0, x0;
    if (anim != 0) {
        h0 = layer1.getCell();
        GXOamAttr *h1;
        if (hasLayer2 != 0) {
            h1 = layer2.getCell();
        } else {
            h1 = NULL;
        }
        s32 ax = layer1.getFrameX(-1);
        s32 ay = layer1.getFrameY(-1);
        s32 bx = layer2.getFrameX(-1);
        s32 by = layer2.getFrameY(-1);
        x = posX + getOriginX();
        y = posY + getOriginY();
        x0 = x + ax;
        y0 = y + ay;
        x += bx;
        y += by;
        if (onBufferA != 0) {
            Oam_DrawCell(0, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            if (h1 != NULL) {
                Oam_DrawCell(0, h1, x, y, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            }
            if (objWindow != 0) {
                Oam_DrawCell(0, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                if (h1 != NULL) {
                    Oam_DrawCell(0, h1, x, y, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                }
            }
        } else {
            Oam_DrawCell(1, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            if (h1 != NULL) {
                Oam_DrawCell(1, h1, x, y, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
            }
            if (objWindow != 0) {
                Oam_DrawCell(1, h0, x0, y0, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                if (h1 != NULL) {
                    Oam_DrawCell(1, h1, x, y, -1, priority, 0x1000, 0x1000, 0, 2, 0, 0);
                }
            }
        }
    }
}

void HandCursor::update() {
    if (anim != 0) {
        layer1.update();
        if (hasLayer2 != 0) {
            layer2.update();
        }
    }
}


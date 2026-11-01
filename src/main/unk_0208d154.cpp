#include "types.h"
#include "host_tick.h"
#include "text/Unk_02050288.h"
#include "ui/NameLabelBalloonView.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/NameLabelBalloon.h"
#include "talk/MsgString.h"

extern "C" {
void GX_LoadOBJPltt(void *a, u32 b, u32 c);
}

extern const s32 kNameLabelBalloonKindAnims[];
extern u8 sNameLabelBalloonKind4Color[];
extern void *const gSpriteSeqTable[45];

struct SpriteAnimSeq;








void NameLabelBalloon::setKind(s32 a) {
    kind = a;
    seqIndex = kNameLabelBalloonKindAnims[a];
    applyKindAnim();
}

void NameLabelBalloon::release() {
    ((NameLabelBalloonView *)this)->freeLabel();
}

void NameLabelBalloon::setOffset(s32 a, s32 b) {
    offsetX = a;
    offsetY = b;
}

void NameLabelBalloon::setText(void *p) {
    text.copy((MsgString *)p);
}

BOOL NameLabelBalloon::requestShow() {
    BOOL r;
    if (state == 0) {
        r = TRUE;
    } else {
        r = FALSE;
    }
    if (r) {
        showRequested = 2;
    }
    return r;
}

BOOL NameLabelBalloon::requestHide() {
    BOOL r;
    if (state != 0) {
        r = TRUE;
    } else {
        r = FALSE;
    }
    if (r) {
        showRequested = 0;
    }
    return r;
}

void NameLabelBalloon::loadKind4Palette() {
    GX_LoadOBJPltt(sNameLabelBalloonKind4Color, 0xbc, 2);
}

void NameLabelBalloon::enterHidden() {
    state = 0;
    isVisible = 0;
}

void NameLabelBalloon::updateHidden() {
    if (showRequested != 0) {
        if (kind == 4) {
            loadKind4Palette();
        }
        ((NameLabelBalloonView *)this)->createLabel();
        fitToLabel();
        enterAppearing();
    }
}

void NameLabelBalloon::enterAppearing() {
    state = 1;
    isVisible = 1;
    stateTimer = 3;
    slideY = 5;
}

void NameLabelBalloon::updateAppearing() {
    if (stateTimer > 2) {
        slideY -= TICK_PART(6);
    } else {
        slideY += TICK_PART(2);
    }
    stateTimer = stateTimer - (TICK_STEP_ENDS() ? 1 : 0);
    if (stateTimer <= 0) {
        slideY = 0;
        enterShown();
    }
}

void NameLabelBalloon::enterShown() {
    state = 2;
    isVisible = 1;
    stateTimer = 2;
}

void NameLabelBalloon::updateShown() {
    if (showRequested == 0) {
        enterHiding();
    }
}

void NameLabelBalloon::enterHiding() {
    state = 3;
    isVisible = 1;
}

void NameLabelBalloon::updateHiding() {
    slideY += TICK_PART(11);
    stateTimer = stateTimer - (TICK_STEP_ENDS() ? 1 : 0);
    if (stateTimer <= 0) {
        ((NameLabelBalloonView *)this)->freeLabel();
        enterHidden();
    }
}

void NameLabelBalloon::applyKindAnim() {
    anim.setSeq((SpriteAnimSeq *)gSpriteSeqTable[seqIndex]);
    anim.setPlayOnce(1);
    anim.setSpeed(0);
}

void NameLabelBalloon::fitToLabel() {
    if (textLabel != 0) {
        s32 len = textLabel->measureWidth();
        u32 n = (u32)(len + 7) >> 3;
        s32 idx = anim.getSeq()->frameCount - 1;
        s32 t = n - 1;
        if (t < 0) {
            idx = 0;
        } else if (t <= idx) {
            idx = t;
        }
        anim.setFrame(idx, 0);
        textLabel->xOffset = (u32)(n * 8 - len) >> 1;
        if (kind == 0) {
            alignX = 0;
        } else {
            s32 q = idx << 2;
            q = -q;
            alignX = q + 0x24;
        }
    }
}


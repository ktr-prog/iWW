#include "types.h"
extern void *const gSpriteSeqTable5b0c[71];
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/TalkArrow.h"





extern const u32 sTalkArrowPlayOnce[];
extern const u32 sTalkArrowSeqIds[];
extern u8 data_020d5b0c[];


enum Unk_020892b0_E { Unk_020892b0_E0 = 0 };

void TalkArrow::setAltStyle() { useAltStyle = 1; }

void TalkArrow::setOffset(s32 x, s32 y) {
    offsetX = x;
    offsetY = y;
}

void TalkArrow::setState(s32 idx) {
    Unk_020892b0_E a;
    Unk_020892b0_E b;
    u32 c;
    a = (Unk_020892b0_E)((u32 *)sTalkArrowSeqIds)[idx];
    if (useAltStyle != 0) {
        a = (Unk_020892b0_E)(a + 6);
    }
    b = (Unk_020892b0_E)(a + 1);
    c = ((u32 *)sTalkArrowPlayOnce)[idx];
    state = idx;
    anim.setSeq((SpriteAnimSeq *)gSpriteSeqTable5b0c[a]);
    anim.setPlayOnce(c);
    anim.restart();
    subAnim.setSeq((SpriteAnimSeq *)gSpriteSeqTable5b0c[b]);
    subAnim.setPlayOnce(c);
    subAnim.restart();
}

s32 TalkArrow::getState() { return state; }

BOOL TalkArrow::isAnimDone() {
    if (anim.isFinished() && subAnim.isFinished()) {
        return TRUE;
    }
    return FALSE;
}

SpriteAnim::SpriteAnim() {
    seq = 0;
    frameIndex = 0;
    frameTime = 0;
    speed = 0x1000;
    playOnce = 0;
}

SpriteAnim::~SpriteAnim() {}

void SpriteAnim::setSeq(SpriteAnimSeq *v) { seq = v; }

void SpriteAnim::setPlayOnce(s32 v) { playOnce = v; }

void SpriteAnim::setSpeed(s32 v) { speed = v; }

void SpriteAnim::setFrame(s32 a, s32 b) {
    frameIndex = a;
    frameTime = b;
}

GXOamAttr *SpriteAnim::getCell() { return seq->frames[frameIndex].cell; }

s32 SpriteAnim::getFrameIndex() { return frameIndex; }

SpriteAnimSeq *SpriteAnim::getSeq() { return seq; }

s32 SpriteAnim::getFrameX(s32 v) {
    if (v < 0) {
        v = frameIndex;
    }
    return seq->frames[v].x;
}

s32 SpriteAnim::getFrameY(s32 v) {
    if (v < 0) {
        v = frameIndex;
    }
    return seq->frames[v].y;
}

BOOL SpriteAnim::isFinished() {
    BOOL r = FALSE;
    if (playOnce == 1) {
        SpriteAnimSeq *t = seq;
        s32 i = frameIndex;
        if (i >= t->frameCount - 1) {
            s32 f = frameTime >> 12;
            if (f >= t->frames[i].duration - 1) {
                r = TRUE;
            }
        }
    }
    return r;
}

void SpriteAnim::pause() { speed = 0; }

void SpriteAnim::restart() {
    speed = 0x1000;
    setFrame(0, 0);
}

const u32 sTalkArrowPlayOnce[] = {0, 0, 1, 1};
const u32 sTalkArrowSeqIds[] = {0x23, 0x23, 0x25, 0x27};

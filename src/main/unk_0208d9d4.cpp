#include "types.h"
extern void *const gSpriteSeqTable5b0c[71];
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/ScrollKnob.h"

extern "C" {
extern u8 data_020d5b0c[];
}

extern const s32 sScrollKnobPlayOnce[4];
extern const s32 sScrollKnobSeqIds[4];

struct SpriteAnimSeq;




enum Unk_0208d9d4_E { Unk_0208d9d4_E0 = 0 };

void ScrollKnob::getAnimOffset(s32 *a, s32 *b) {
    s32 x = 0;
    s32 y = 0;
    if (state == 2) {
        x = layerAnim1.getFrameX(-1);
        x -= layerAnim1.getFrameX(0);
        s32 t = layerAnim1.getFrameY(-1);
        y = t - layerAnim1.getFrameY(0);
    } else if (state == 3) {
        x = layerAnim1.getFrameX(0);
        x -= layerAnim1.getFrameX(-1);
        s32 t = layerAnim1.getFrameY(0);
        y = t - layerAnim1.getFrameY(-1);
    }
    *a = x;
    *b = y;
}

void ScrollKnob::setState(s32 idx) {
    Unk_0208d9d4_E a;
    Unk_0208d9d4_E n;
    s32 f;
    a = (Unk_0208d9d4_E)sScrollKnobSeqIds[idx];
    n = (Unk_0208d9d4_E)(a + 1);
    f = sScrollKnobPlayOnce[idx];
    state = idx;
    layerAnim1.setSeq((SpriteAnimSeq *)gSpriteSeqTable5b0c[a]);
    layerAnim1.setPlayOnce(f);
    layerAnim1.restart();
    priority.setSeq((SpriteAnimSeq *)gSpriteSeqTable5b0c[n]);
    priority.setPlayOnce(f);
    priority.restart();
    if (idx == 1) {
        layerAnim1.setSpeed(0);
        priority.setSpeed(0);
    }
}

extern const s32 sScrollKnobPlayOnce[4] = {1, 1, 1, 1};
extern const s32 sScrollKnobSeqIds[4] = {0x2f, 0x2f, 0x2f, 0x31};

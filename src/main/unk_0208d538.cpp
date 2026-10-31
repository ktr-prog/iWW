#include "types.h"
extern void *const gSpriteSeqTable5b0c[71];
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/HandCursor.h"
#include "proto/main/unk_020039ec.h"
#include "proto/main/unk_0208d538.h"

extern "C" {
}

extern u8 data_020d5b0c[];

extern const u8 sHandCursorAnimHasLayer2[0x14];
extern const u8 sHandCursorAnimLoops[0x14];
extern const s32 sHandCursorAnimSeqIds[0x13];


struct SpriteAnimSeq;




void HandCursor::enableObjWindow() {
    objWindow = 1;
}

void HandCursor::disableObjWindow() {
    objWindow = 0;
}

void HandCursor::setPos(s32 a, s32 b) {
    posX = a;
    posY = b;
    if (anim != 0) {
        s32 v = posX + getOriginX();
        if (v < 0) {
            v = 0;
        }
        if (v > 0xff) {
            v = 0xff;
        }
        Snd_SetPanIfChanged(v);
    }
}

void HandCursor::setAnim(s32 idx) {
    s32 a = sHandCursorAnimSeqIds[idx];
    s32 n = a + 1;
    BOOL f;
    switch (sHandCursorAnimLoops[idx]) {
    default:
        f = FALSE;
        break;
    case 0:
        f = TRUE;
    }
    anim = idx;
    layer1.setSeq((SpriteAnimSeq *)gSpriteSeqTable5b0c[a]);
    layer1.setPlayOnce(f);
    layer1.restart();
    hasLayer2 = sHandCursorAnimHasLayer2[idx];
    if (hasLayer2 != 0) {
        layer2.setSeq((SpriteAnimSeq *)gSpriteSeqTable5b0c[n]);
        layer2.setPlayOnce(f);
        layer2.restart();
    }
}

void HandCursor::setAnimAtEnd(s32 idx) {
    setAnim(idx);
    SpriteAnimSeq *p = layer1.getSeq();
    layer1.setFrame(p->frameCount - 1, 0);
    if (hasLayer2 != 0) {
        SpriteAnimSeq *q = layer2.getSeq();
        layer2.setFrame(q->frameCount - 1, 0);
    }
}

extern const u8 sHandCursorAnimLoops[0x14];
extern const u8 sHandCursorAnimHasLayer2[0x14];
extern const s32 sHandCursorAnimSeqIds[0x13];

extern const u8 sHandCursorAnimLoops[0x14] = {1,1,0,0, 0,0,0,1, 0,0,0,0, 0,1,0,0, 1,0,0,0};

extern const u8 sHandCursorAnimHasLayer2[0x14] = {1,1,1,1, 1,1,0,1, 1,1,1,1, 0,0,0,0, 0,0,0,0};

extern const s32 sHandCursorAnimSeqIds[0x13] = {1,1,3,5,7,9,11,12,14,16,18,20,22,23,25,27,29,31,33};

extern const u8 sNameLabelBalloonKind4Color[4] = {0x7b, 0x6f, 0x00, 0x00};

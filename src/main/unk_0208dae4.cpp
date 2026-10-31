#include "types.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/ScrollKnob.h"
#include "ui/HudUnkIcon.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0208dae4.h"
#include "proto/main/unk_02094810.h"

extern "C" {
s32 TalkRequest_IsActive();
s32 Scene_GetCurrent();
}

extern s32 gGfxMainOnTop;
extern u8 data_020d4694[];
extern u8 data_020d468c[];

struct SpriteAnimSeq;

void HudUnkIcon::updateHidden() {
    if (HudUnkIcon_CanShow() != 0) {
        state = 1;
        anim.setSeq((SpriteAnimSeq *)data_020d468c);
        anim.setPlayOnce(1);
        anim.restart();
    }
}

void HudUnkIcon::updateAppearing() {
    anim.update();
    if (anim.isFinished()) {
        state = 2;
    }
}

void HudUnkIcon::updateShown() {
    if (HudUnkIcon_CanShow() == 0) {
        state = 3;
        anim.setSeq((SpriteAnimSeq *)data_020d4694);
        anim.setPlayOnce(1);
        anim.restart();
    }
}

void HudUnkIcon::updateHiding() {
    anim.update();
    if (anim.isFinished()) {
        state = 0;
    }
}

extern "C" BOOL HudUnkIcon_CanShow() {
    BOOL a, b, c;
    long d, e;
    s32 v;
    a = gGfxMainOnTop == 0 ? TRUE : FALSE;
    b = TalkRequest_IsActive() == 0 ? TRUE : FALSE;
    c = Scene_GetCurrent() == 6 ? TRUE : FALSE;
    v = PlayerActor_GetAction(4);
    d = (u32)(v - 8) <= 7 ? TRUE : FALSE;
    e = (u32)(v - 0x24) <= 8 ? TRUE : FALSE;
    if (a && b && !c && !d && !e) {
        return TRUE;
    }
    return FALSE;
}

ScrollKnob::ScrollKnob(u32 flag) : layer1(0), posY(0) {
    state = 0;
    anim = flag;
    drawPriority = -1;
    setState(0);
}

ScrollKnob::~ScrollKnob() {
}

void ScrollKnob::draw() {
    if (state != 0) {
        GXOamAttr *h0 = layerAnim1.getCell();
        GXOamAttr *h1 = priority.getCell();
        s32 a = layerAnim1.getFrameX(-1);
        s32 b = layerAnim1.getFrameY(-1);
        s32 c = priority.getFrameX(-1);
        s32 d = priority.getFrameY(-1);
        s32 bx = layer1 + getOriginX();
        s32 by = posY + getOriginY();
        if (anim != 0) {
            Oam_DrawCell(0, h0, bx + a, by + b, -1, drawPriority, 0x1000, 0x1000, 0, -1, 0, 0);
            Oam_DrawCell(0, h1, bx + c, by + d, -1, drawPriority, 0x1000, 0x1000, 0, -1, 0, 0);
        } else {
            Oam_DrawCell(1, h0, bx + a, by + b, -1, drawPriority, 0x1000, 0x1000, 0, -1, 0, 0);
            Oam_DrawCell(1, h1, bx + c, by + d, -1, drawPriority, 0x1000, 0x1000, 0, -1, 0, 0);
        }
    }
}

void ScrollKnob::update() {
    if (state != 0) {
        layerAnim1.update();
        priority.update();
    }
}

void ScrollKnob::moveTo(s32 x, s32 y) { layer1 = x; posY = y; }

void ScrollKnob::setPriority(s32 v) { drawPriority = v; }


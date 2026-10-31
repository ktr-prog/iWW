#include "types.h"
#include "text/Unk_02050288.h"
#include "gfx/SpriteAnim.h"
#include "ui/UiWidget.h"
#include "ui/ScrollKnob.h"
#include "ui/LabelButton.h"
#include "ui/HudUnkIcon.h"
#include "proto/main/unk_02087e70.h"
#include "proto/main/unk_0208de68.h"
#include "proto/main/unk_0208dff4.h"
#include "proto/main/unk_02094810.h"

extern s32 gGfxMainOnTop;
extern u8 data_020d4694[];
extern u8 data_020d468c[];
extern SpriteAnimSeq data_020d5b0c[];
extern u8 sLabelButtonKindTextColors[];
extern u32 sLabelButtonKindLabelVram[];
extern u8 sLabelButtonKindSeqOffsets[];
extern s32 sLabelButtonStateSeqIds[];
extern s32 sLabelButtonStatePlayOnce[];

HudUnkIcon sHudUnkIcon;


HudUnkIcon::HudUnkIcon() {
    state = 0;
}

HudUnkIcon::~HudUnkIcon() {
}

void HudUnkIcon::draw() {
    if (state != 0) {
        GXOamAttr *h = anim.getCell();
        s32 x = getOriginX() + anim.getFrameX(-1);
        s32 y = getOriginY() + anim.getFrameY(-1);
        Oam_DrawCell(0, h, x, y, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

void HudUnkIcon::update() {
    typedef void (HudUnkIcon::*Fn)();
    static Fn tbl[4] = {&HudUnkIcon::updateHidden, &HudUnkIcon::updateAppearing, &HudUnkIcon::updateShown, &HudUnkIcon::updateHiding};
    (this->*tbl[state])();
}

extern "C" void HudUnkIcon_Reset() { sHudUnkIcon.state = 0; }

extern "C" void HudUnkIcon_Exit() {}

extern "C" void HudUnkIcon_Update() { sHudUnkIcon.update(); }

extern "C" void HudUnkIcon_Draw() { sHudUnkIcon.draw(); }


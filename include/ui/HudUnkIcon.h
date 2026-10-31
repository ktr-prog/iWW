#ifndef UI_HUDUNKICON_H
#define UI_HUDUNKICON_H

#include "types.h"
#include "ui/UiWidget.h"
#include "gfx/SpriteAnim.h"

class HudUnkIcon : public UiWidget {
public:
    HudUnkIcon();
    virtual ~HudUnkIcon();
    virtual void draw();
    virtual void update();

    void updateHiding();
    void updateShown();
    void updateAppearing();
    void updateHidden();

    /* 0x0c */ SpriteAnim anim;
    /* 0x20 */ s32 state;
};

#endif
